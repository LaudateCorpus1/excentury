# File generated on Sat Aug 16, 2014 03:45:38 PM by xcpp.
"""XC TEST

This is a simple collection of functions to make sure that excentury
can compile and run the code from each of functions."""
from excentury import TextParser, TextDumper, XCStruct
from ctypes import c_char, c_size_t, c_char_p
import ctypes

LIB = ctypes.cdll.LoadLibrary("xc_test_pylib.so")

DEFS = {
}
def xc_struct(name):
    """Return an XCStruct object using the entries of the dictionary
    DEFS in this module."""
    return XCStruct(name, DEFS[name])


LIB.timestwo_py.restype = None
LIB.timestwo_py_clear.restype = None
def timestwo(x, unpack=True):
    """Take a scalar and double it.

    parameters:

      `x`: scalar to be doubled.
    """
    tdump = TextDumper()
    tdump.dump(x, "x", ['R', '8'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.timestwo_py(c_size_t(len_in),
                    c_char_p(in_str),
                    ctypes.byref(len_out),
                    ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.timestwo_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.cube_py.restype = None
LIB.cube_py_clear.restype = None
def cube(x, unpack=True):
    """cube an integer

    parameters:

      `x`: integer to be cubed.
    """
    tdump = TextDumper()
    tdump.dump(x, "x", ['I', '4'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.cube_py(c_size_t(len_in),
                c_char_p(in_str),
                ctypes.byref(len_out),
                ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.cube_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


