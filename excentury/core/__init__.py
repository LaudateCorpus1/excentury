"""Excentury Core

Contains functions that can be used by the binary and text interface
as well as the readers.

"""

import re
import six
import ctypes
import numpy as np

CHAR = ctypes.c_char
BYTE = ctypes.c_byte
UBYTE = ctypes.c_ubyte
SHORT = ctypes.c_short
USHORT = ctypes.c_ushort
INT = ctypes.c_int
UINT = ctypes.c_uint
LONG = ctypes.c_long
ULONG = ctypes.c_ulong
FLOAT = ctypes.c_float
DOUBLE = ctypes.c_double
VOIDP = ctypes.c_void_p

if six.PY3:
    long = int

CTYPES = {
    str: CHAR,
    int: INT,
    long: LONG,
    float: DOUBLE,
    np.intc: INT,
    np.intp: UINT,
    np.int8: BYTE,
    np.int16: SHORT,
    np.int32: INT,
    np.int64: LONG,
    np.int_: LONG,
    np.uint8: UBYTE,
    np.uint16: USHORT,
    np.uint32: UINT,
    np.uint64: ULONG,
    np.float16: FLOAT,
    np.float32: FLOAT,
    np.float64: DOUBLE,
    np.float_: DOUBLE,
}
XC_TYPES = {
    CHAR: 'C',
    BYTE: 'I',
    UBYTE: 'N',
    SHORT: 'I',
    USHORT: 'N',
    INT: 'I',
    UINT: 'N',
    LONG: 'I',
    ULONG: 'N',
    FLOAT: 'R',
    DOUBLE: 'R',
    VOIDP: 'P'
}
STR_TYPE = {
    'char': CHAR,
    'byte': BYTE,
    'ubyte': UBYTE,
    'short': SHORT,
    'ushort': USHORT,
    'int': INT,
    'uint': UINT,
    'long': LONG,
    'ulong': ULONG,
    'float': FLOAT,
    'double': DOUBLE,
    'voidp': VOIDP
}
INFO_TYPE = {
    'C1': 'char',
    'I1': 'byte',
    'N1': 'ubyte',
    'I2': 'short',
    'N2': 'ushort',
    'I4': 'int',
    'N4': 'uint',
    'I8': 'long',
    'N8': 'ulong',
    'R4': 'float',
    'R8': 'double'
}

COMMUNICATE_DUMP = dict()
TENSOR_INFO = dict()
TENSOR_GET_INFO = dict()
LOAD_DEFS = dict()
XC_OBJ = dict()
XC_TMP_FUNC = None


def xc_type(obj):
    """Return one of the following: 'C', 'I', 'N', 'R',
    'S', 'T', or 'P' or 'W'. """
    obj_type = type(obj)
    if obj_type is str and len(obj) > 1:
        return 'W'
    if obj_type in TENSOR_INFO:
        return 'T'
    if obj_type in XC_TYPES:
        return XC_TYPES[obj_type]
    return XC_TYPES.get(CTYPES.get(obj_type, None), 'S')


def c_type(obj):
    """Return the ctype of an object if it has it or None. """
    obj_type = type(obj)
    if obj_type in XC_TYPES:
        return obj_type
    if obj_type is str and len(obj) > 1:
        return None
    return CTYPES.get(obj_type, None)


def info_impl(interface, obj, varname):
    """Transmit the varname and info. This is used for the trans_def
    method in a DataType object since it calls info with 3
    parameters."""
    interface.trans_name(varname)
    info(interface, obj)


def info(interface, obj, varname=None):
    """Communicate the object information. """
    if varname is not None:
        COMMUNICATE_DUMP[type(obj)](info_impl, interface, obj, varname)
        return
    kind = xc_type(obj)
    if kind in ['C', 'I', 'N', 'R', 'S']:
        interface.info(obj)
    elif kind == 'W':
        interface.trans_type('W')
    else:
        TENSOR_INFO[type(obj)](info, interface, obj, "")


def get_info(obj):
    """Return the information of an object. """
    kind = xc_type(obj)
    if kind in ['C', 'I', 'N', 'R', 'S']:
        if kind in ['C', 'I', 'N', 'R']:
            return [kind, str(ctypes.sizeof(c_type(obj)))]
        elif type(obj) is XCStruct:
            return [kind, obj.name()]
        else:
            return [kind, type(obj).__name__]
    if kind == 'W':
        return ['W']
    if type(obj) in TENSOR_GET_INFO:
        return TENSOR_GET_INFO[type(obj)](obj)
    raise TypeError("No info for this type.")


def cmp_info(info1, info2):
    """Return true if the info objects are the same. """
    if info1[0] != info2[0]:
        return False
    if info1[0] == 'S':
        return info1[1] == info2[1]
    if info1[0] == 'W':
        return True
    if info1[0] == 'T':
        return cmp_info(info1[1], info2[1])
    return info1[1] == info2[1]


def data(interface, obj, _):
    """Communicate the object data. """
    kind = xc_type(obj)
    if kind in ['C', 'I', 'N', 'R']:
        interface.data(obj)
    elif kind == 'W':
        interface.trans_num(len(obj))
        interface.trans_name(obj)
    else:
        COMMUNICATE_DUMP[type(obj)](data, interface, obj, "")


def append_cls_impl(interface, obj, _):
    """Store possible objects which were not added to the interface.
    That is, perhaps an object contains a subject which is not on the
    list. Due to this, we must search for such objects. An example of
    this happens when a line is added but a point is not. """
    interface.store_cls(obj)


def append_cls(interface, obj):
    """Append objects to the the interface obj_cls list by using the
    function defined for a given type. """
    COMMUNICATE_DUMP[type(obj)](append_cls_impl, interface, obj, "")


class XCStruct(object):
    """Object designed to hold data from excentury files in case
    there is no python function describing how to read a variable in
    the file."""
    def __init__(self, name, info_):
        self.__dict__['__name__'] = name
        self.__dict__['__info__'] = info_
        for item in info_:
            key = ''.join(item[1])
            if key in INFO_TYPE:
                self.__dict__[item[0]] = STR_TYPE[INFO_TYPE[key]]()
            else:
                self.__dict__[item[0]] = None

    def __setattr__(self, name, value):
        if name in self.__dict__:
            if type(value) in XC_TYPES:
                value = value.value
            for item in self.__info__:
                if item[0] == name:
                    key = ''.join(item[1])
                    if key in INFO_TYPE:
                        value = STR_TYPE[INFO_TYPE[key]](value)
                    elif not cmp_info(get_info(value), item[1]):
                        raise ValueError("Expected %s" % str(item[1]))
                    break
        self.__dict__[name] = value

    def __getattribute__(self, name):
        val = object.__getattribute__(self, name)
        if type(val) in XC_TYPES:
            return val.value
        return val

    def __repr__(self):
        tstr = "%s@[0x%d] = \n" % (self.__name__, id(self))
        for item in self.__info__:
            val = object.__getattribute__(self, item[0])
            if type(val) in XC_TYPES:
                tstr += '  %s: %s\n' % (item[0], repr(val))
            else:
                tstr += '  %s: %s\n' % (item[0], item[1])
        return tstr

    def name(self):
        """Return the name of the structure. """
        return self.__dict__['__name__']

    def info(self):
        """Return a list of the information it contains. """
        return self.__dict__['__info__']


def xcstruct_communicate_func(func, interface, obj, _):
    """Communication function for the XCStruct object. """
    for item in obj.info():
        func(interface, obj.__dict__[item[0]], item[0])

COMMUNICATE_DUMP[XCStruct] = xcstruct_communicate_func


class DataType(object):
    """Common datatype for all objects. """
    def __init__(self, obj, name, interface):
        type_obj = type(obj)
        if type_obj is str:
            if len(obj) > 1:
                self.obj = obj
            else:
                self.obj = CHAR(obj)
        else:
            if type_obj in CTYPES:
                self.obj = CTYPES[type_obj](obj)
            else:
                self.obj = obj
        self.name = name
        self.interface = interface

    def communicate(self):
        """The communication process. """
        self.interface.trans_varname(self.name)
        info(self.interface, self.obj)
        data(self.interface, self.obj, self.name)
        self.interface.trans_close()

    def append_def(self):
        """Call the append class function. """
        append_cls(self.interface, self.obj)

    def trans_def(self):
        """Transmit its definition. """
        if type(self.obj) is XCStruct:
            self.interface.trans_name(self.obj.name())
        else:
            self.interface.trans_name(type(self.obj).__name__)
        info(self.interface, self.obj, self.name)
        self.interface.trans_close()

    def get_type_name(self):
        """Return the class name. """
        if type(self.obj) is XCStruct:
            return self.obj.name()
        return type(self.obj).__name__


class Communicator(object):
    """"A communicator is in charge of transmitting data. How it does
    it is up to the interface. """

    def __init__(self, interface):
        self.obj = list()
        self.cls_obj = list()
        self.interface = interface

    def store_cls(self, py_obj):
        """Append to the cls_obj list if its not there. """
        if xc_type(py_obj) == 'S':
            if type(py_obj) is XCStruct:
                name = py_obj.name()
            else:
                name = type(py_obj).__name__
            is_in = False
            for item in self.cls_obj:
                if item.get_type_name() == name:
                    is_in = True
                    break
            if not is_in:
                self.cls_obj.append(DataType(py_obj, "", self.interface))
                self.cls_obj[-1].append_def()

    def dump(self, py_obj, name, kind=None):
        """Dump the python object with the given name. You have the
        option of specifying the kind in case of simple datatypes.
        For instance, if you write 3, you can set kind to 'double' to
        store it as a double. """
        if kind is not None:
            if type(py_obj) in XC_TYPES:
                py_obj = py_obj.value
            tmp_info = get_info(py_obj)
            if isinstance(kind, list):
                if kind[0] in ['I', 'N', 'R']:
                    if tmp_info[0] in ['W', 'T', 'S', 'C']:
                        raise ValueError('Unable to cast py_obj')
                    else:
                        key = ''.join(kind)
                        py_obj = STR_TYPE[INFO_TYPE[key]](py_obj)
                elif not cmp_info(tmp_info, kind):
                    raise ValueError('%s != %s' % (str(kind),
                                                   str(tmp_info)))
            else:
                py_obj = STR_TYPE[kind](py_obj)
        self.obj.append(DataType(py_obj, name, self.interface))
        self.store_cls(py_obj)

    def __getitem__(self, index):
        """x.__getitem__[index] <==> x[index]"""
        if self.obj[index] in XC_TYPES:
            return self.obj[index].obj.value
        else:
            return self.obj[index].obj

    def __len__(self):
        """x.__len__() <==> len(x)"""
        return len(self.obj)

    def clear(self):
        """Remove all stored objects. """
        del self.obj[:]
        del self.cls_obj[:]

    def close(self):
        """Let the interface communicate. """
        self.interface.trans_num_classes()
        for item in self.cls_obj:
            item.trans_def()
        self.interface.trans_num_objects()
        for item in self.obj:
            item.communicate()
        self.clear()


def _replacer(key_val):
    """Helper function for replace. Source:
    <http://stackoverflow.com/a/15221068/788553>"""
    replace_dict = dict(key_val)
    replacement_function = lambda match: replace_dict[match.group(0)]
    pattern = re.compile("|".join([re.escape(k) for k, _ in key_val]), re.M)
    return lambda string: pattern.sub(replacement_function, string)


def replace(string, key_val):
    """Replacement of strings done in one pass. Example:

        >>> replace("a < b && b < c", ('<', '&lt;'), ('&', '&amp;'))
        'a &lt; b &amp;&amp; b &lt; c'

    Source: <http://stackoverflow.com/a/15221068/788553>"""
    return _replacer(key_val)(string)


# pylint: disable=W0122
def load_datatype(obj, content):
    """The definitions in the file should suffice to create the
    object but that won't call an actual type. Use this to define how
    to read the data into the new object. """
    cpp_map = [
        ('XC_LOAD(', 'fid.get_data(defs, '),
        (obj.__name__, 'XC_OBJ["%s"]' % obj.__name__)
    ]
    XC_OBJ[obj.__name__] = obj
    lines = [line for line in content.split('\n') if line.strip() != '']
    content = 'def XC_TMP_FUNC(fid, defs):\n'
    for line in lines:
        content += replace(line, cpp_map)+'\n'
    exec(content, globals())
    LOAD_DEFS[obj.__name__] = XC_TMP_FUNC


def dump_datatype(obj, var, content):
    """To simulate c++ XC_DUMP_DATATYPE you have to provide strings
    so that python can build the appropiate functions.

    C++ version:

        XC_DUMP_DATATYPE(Line, t) {
            XC_DUMP(t.a, "a");
            XC_DUMP(t.b, "b");
        }

    Python version:

        dump_datatype(Line, 't', '''
            XC_DUMP(t.a, "a");
            XC_DUMP(t.b, "b");
        ''')
    """
    cpp_map = [
        ('XC_DUMP(', 'func(interface, ')
    ]
    lines = [line for line in content.split('\n') if line.strip() != '']
    content = 'def XC_TMP_FUNC(func, interface, %s, varname):\n' % var
    for line in lines:
        content += replace(line, cpp_map)+'\n'
    exec(content, globals())
    COMMUNICATE_DUMP[obj] = XC_TMP_FUNC


def dump_tensor(obj, var, sample, content):
    """To simulate c++ XC_DUMP_TENSOR you have to provide strings
    so that python can build the appropiate functions.

    C++ version:

        XC_DUMP_TENSOR(Matrix, m, m.at(0)) {
            XC_RM(0);
            XC_SIZE(2);
            XC_ARRAY(m.size, 2);
            XC_ARRAY(m.data, m.size(1)*m.size(2));
        }

    Python version:

        dump_tensor(Matrix, 'm', 'm.at(0)', '''
            XC_RM(0)
            XC_SIZE(2)
            XC_DIMS(m.size, 2)
            XC_ARRAY(m.data, m.size(1)*m.size(2))
        ''')
    """
    cpp_map = [
        ('XC_BYTE(', 'interface.trans_byte('),
        ('XC_SIZE(', 'interface.trans_num('),
        ('XC_ARRAY(', 'interface.data(')
    ]
    lines = [line for line in content.split('\n') if line.strip() != '']
    content = 'def XC_TMP_FUNC(func, interface, %s, varname):\n' % var
    for line in lines:
        content += replace(line, cpp_map)+'\n'
    exec(content, globals())
    COMMUNICATE_DUMP[obj] = XC_TMP_FUNC
    content = 'def XC_TMP_FUNC(func, interface, %s, varname):\n' % var
    content += '    interface.trans_type("T")\n'
    content += '    info(interface, %s)\n' % sample
    exec(content, globals())
    TENSOR_INFO[obj] = XC_TMP_FUNC
    content = 'def XC_TMP_FUNC(%s):\n' % var
    content += '    return ["T", get_info(%s)]\n' % sample
    exec(content, globals())
    TENSOR_GET_INFO[obj] = XC_TMP_FUNC


dump_tensor(list, 'obj', 'obj[0]', '''
    XC_BYTE(0)
    XC_SIZE(1)
    XC_SIZE(len(obj))
    XC_ARRAY(obj, len(obj))
''')
dump_tensor(np.ndarray, 'obj', 'obj.item(0)', '''
    if obj.flags.f_contiguous:
        XC_BYTE(0)
    else:
        XC_BYTE(1)
    XC_SIZE(obj.ndim)
    XC_ARRAY(obj.shape, obj.ndim)
    total = reduce(lambda x, y: x*y, obj.shape)
    if obj.flags.f_contiguous:
        XC_ARRAY(obj.flatten('F'), total)
    else:
        XC_ARRAY(obj.flatten('C'), total)
''')
