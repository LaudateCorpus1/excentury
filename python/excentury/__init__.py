"""Excentury

Collection of functions to read and write files and strings in the
excentury format.

"""

import numpy as np
from .core import dump_tensor, dump_datatype, load_datatype, XCStruct
from .core.load_text import TextParser
from .core.dump_text import TextDumper


def parse_string(text, kind=None):
    """Utility function to read a string in text mode. """
    if kind is None:
        tmp = TextParser(text)
        return tmp.parse()
    else:
        pass


def load_file(fname, kind=None):
    """Utility function to read an excentury file in text mode. """
    return parse_string(open(fname, 'r').read(), kind)


#pylint: disable=W0142
def dump_text(fname, *obj, **keys):
    """Utility function to dump objects in a text file. You may
    do it in a list form:

        dump_text("filename.xc", (val1, "var1"), (val2, "var2"))

    or dictionary form:

        dump_text("filename.xc", var1=val1, var2=val2)

    or a combination of both. Make sure the list goes first and then
    the dictionary keys. """
    tdump = TextDumper(fname)
    for item in obj:
        tdump.dump(*item)
    for key in keys:
        tdump.dump(keys[key], key)
    tdump.close()


def to_text(*obj, **keys):
    """Utility function to dump objects to a string. You may
    do it in a list form:

        to_text((val1, "var1"), (val2, "var2"))

    or dictionary form:

        to_text(var1=val1, var2=val2)

    or a combination of both. Make sure the list goes first and then
    the dictionary keys. """
    tdump = TextDumper()
    for item in obj:
        tdump.dump(*item)
    for key in keys:
        tdump.dump(keys[key], key)
    return tdump.close()


def array(obj, row_major=0):
    """Wrapper around numpy.ndarray. It gives you the option of
    specifying the order of the contents. """
    if not isinstance(obj, np.ndarray):
        obj = np.array(obj)
    if row_major == 0:
        if obj.flags.f_contiguous:
            return obj
        else:
            dim = list(obj.shape)
            return obj.flatten(order='F').reshape(dim, order='F')
    else:
        if obj.flags.c_contiguous:
            return obj
        else:
            dim = list(obj.shape)
            return obj.flatten(order='C').reshape(dim, order='C')
