# File generated on Fri Aug 22, 2014 10:37:05 AM by xcpp.
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


LIB.inverse_det_py.restype = None
LIB.inverse_det_py_clear.restype = None
def inverse_det(A, unpack=True):
    """Find the inverse and determinant of a square matrix using
    the armadillo library.

    parameters:

      `A`: input matrix
    """
    tdump = TextDumper()
    tdump.dump(A, "A", ['T', ['R', '8']])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.inverse_det_py(c_size_t(len_in),
                       c_char_p(in_str),
                       ctypes.byref(len_out),
                       ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.inverse_det_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.qr_py.restype = None
LIB.qr_py_clear.restype = None
def qr(X, unpack=True):
    """Decomposition of X into an orthogonal matrix Q and a right
    triangular matrix R, such that Q*R = X.

    parameters:

      `X`: input matrix
    """
    tdump = TextDumper()
    tdump.dump(X, "X", ['T', ['R', '8']])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.qr_py(c_size_t(len_in),
              c_char_p(in_str),
              ctypes.byref(len_out),
              ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.qr_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.solve_py.restype = None
LIB.solve_py_clear.restype = None
def solve(A, B, unpack=True):
    """Solve a system of linear equations, A*X = B, where X is
    unknown; similar functionality to the \\ operator in
    Matlab/Octave, ie. X = A \\ B

    parameters:

      `A`: matrix A
      `B`: matrix B
    """
    tdump = TextDumper()
    tdump.dump(A, "A", ['T', ['R', '8']])
    tdump.dump(B, "B", ['T', ['R', '8']])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.solve_py(c_size_t(len_in),
                 c_char_p(in_str),
                 ctypes.byref(len_out),
                 ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.solve_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


