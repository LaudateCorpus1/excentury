"""Dump Text

Interface designed to dump text files.

"""

import ctypes
from six.moves import cStringIO as StringIO
from excentury.core import XCStruct, XC_TYPES, CTYPES
from excentury.core import Communicator, data, xc_type, c_type

CHAR_MAP = {
    'C': '%c',
    'I': '%d',
    'N': '%d',
    'R': '%f'
}


class TextDumper(Communicator):
    """Class to dump data. """
    def __init__(self, fname=None):
        Communicator.__init__(self, self)
        self._fname = fname
        self._file = None
        self.open(fname)

    def open(self, fname=None):
        """Open a new file for writing. """
        self.close()
        self._fname = fname
        if fname is None:
            self._file = StringIO()
        else:
            self._file = open(fname, "w")

    def close(self):
        """Transmit the objects. """
        val = None
        if self._file is not None:
            Communicator.close(self)
            if self._fname is None:
                val = self._file.getvalue()
            self._file.close()
            self._file = None
            self._fname = None
        return val

    def info(self, obj):
        """Write the object info"""
        kind = xc_type(obj)
        self._file.write("%c " % kind)
        if kind in ['C', 'I', 'N', 'R']:
            self._file.write('%d ' % ctypes.sizeof(c_type(obj)))
        elif type(obj) is XCStruct:
            self._file.write('%s ' % obj.name())
        else:
            self._file.write('%s ' % type(obj).__name__)

    def data(self, obj, total=None):
        """Write the objects data. """
        if total is not None:
            tmp = '%s ' % CHAR_MAP.get(xc_type(obj[0]), None)
            if type(obj[0]) in XC_TYPES:
                for i in xrange(total):
                    self._file.write(tmp % obj[i].value)
            elif type(obj[0]) in CTYPES:
                for i in xrange(total):
                    self._file.write(tmp % obj[i])
            else:
                for i in xrange(total):
                    data(self, obj[i], "")
            return
        tmp = '%s ' % CHAR_MAP[xc_type(obj)]
        if type(obj) not in XC_TYPES:
            self._file.write(tmp % obj)
        else:
            self._file.write(tmp % obj.value)

    def trans_type(self, obj):
        """Transfer a character. """
        self._file.write("%c " % obj)

    def trans_byte(self, obj):
        """Transfer a byte. """
        self._file.write("%d " % obj)

    def trans_num(self, num):
        """Transfer an integer. """
        self._file.write("%d " % num)

    def trans_varname(self, varname):
        """Transfer a variable name. """
        self._file.write("%s " % varname)

    def trans_name(self, name):
        """Transfer a name. """
        self._file.write("%s " % name)

    def trans_num_objects(self):
        """Transfer the number of objects. """
        self._file.write("%d\n" % len(self.obj))

    def trans_num_classes(self):
        """Tranfer the number of objects in cls_obj. """
        if len(self.cls_obj) > 0:
            self._file.write("%d\n" % len(self.cls_obj))
        else:
            self._file.write("%d " % len(self.cls_obj))

    def trans_close(self):
        """Print character to denote when transfer of obj is done. """
        self._file.write("\n")
