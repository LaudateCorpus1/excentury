# File generated on Tue Apr 15, 2014 11:14:30 AM by xcpp.
"""Armadillo Test

Collection of sample functions showing how to use the
[Armadillo](http://arma.sourceforge.net/) library."""
from excentury import TextParser, TextDumper, XCStruct
from ctypes import c_char, c_size_t, c_char_p
import ctypes

LIB = ctypes.cdll.LoadLibrary("arma_pylib.so")

DEFS = {
}
def xc_struct(name):
    """Return an XCStruct object using the entries of the dictionary
    DEFS in this module."""
    return XCStruct(name, DEFS[name])


LIB.ex1_py.restype = None
LIB.ex1_py_clear.restype = None
def ex1(A, unpack=True):
    """Armadillo example 1

    parameters:

      `A`: Input Matrix
    """
    tdump = TextDumper()
    tdump.dump(A, "A", ['T', ['R', '8']])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.ex1_py(c_size_t(len_in),
               c_char_p(in_str),
               ctypes.byref(len_out),
               ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.ex1_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


