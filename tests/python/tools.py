# File generated on Wed Aug 13, 2014 04:27:46 PM by xcpp.
"""Tools

This collection of functions are examples of how to use the objects
in excentury/tools."""
from excentury import TextParser, TextDumper, XCStruct
from ctypes import c_char, c_size_t, c_char_p
import ctypes

LIB = ctypes.cdll.LoadLibrary("tools_pylib.so")

DEFS = {
}
def xc_struct(name):
    """Return an XCStruct object using the entries of the dictionary
    DEFS in this module."""
    return XCStruct(name, DEFS[name])


LIB.square_root_py.restype = None
LIB.square_root_py_clear.restype = None
def square_root(x, x0, iter, unpack=True):
    """Compute the square root of a number using Newton's method.
    This function will print to stdout the amount of time it took to
    execute.

    parameters:

      `x`: the input to the square root function.
      `x0`: initial guess.
      `iter`: number of iterations.
    """
    tdump = TextDumper()
    tdump.dump(x, "x", ['R', '8'])
    tdump.dump(x0, "x0", ['R', '8'])
    tdump.dump(iter, "iter", ['I', '4'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.square_root_py(c_size_t(len_in),
                       c_char_p(in_str),
                       ctypes.byref(len_out),
                       ctypes.byref(out_str))
    print 'FIRST: %r' % out_str[:1] 
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.square_root_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.rand_array_py.restype = None
LIB.rand_array_py_clear.restype = None
def rand_array(n, mean, std, unpack=True):
    """Get an array of random numbers from a uniform distribution.

    parameters:

      `n`: amount of random numbers.
      `mean`: the mean of the distribution.
      `std`: the standard deviation of the distribution.
    """
    tdump = TextDumper()
    tdump.dump(n, "n", ['I', '4'])
    tdump.dump(mean, "mean", ['R', '8'])
    tdump.dump(std, "std", ['R', '8'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.rand_array_py(c_size_t(len_in),
                      c_char_p(in_str),
                      ctypes.byref(len_out),
                      ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.rand_array_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.test_rep_py.restype = None
LIB.test_rep_py_clear.restype = None
def test_rep(unpack=True):
    """This function will do useless computation for the sake of
    testing the reporter object which will print messages to
    stdout.
    """
    tdump = TextDumper()
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.test_rep_py(c_size_t(len_in),
                    c_char_p(in_str),
                    ctypes.byref(len_out),
                    ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.test_rep_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.sin_vector_py.restype = None
LIB.sin_vector_py_clear.restype = None
def sin_vector(v, w, unpack=True):
    """Given a vector of values, it returns the sin of each of its
    elements.

    parameters:

      `v`: input vector
      `w`: input vector
    """
    tdump = TextDumper()
    tdump.dump(v, "v", ['T', ['R', '8']])
    tdump.dump(w, "w", ['T', ['R', '8']])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.sin_vector_py(c_size_t(len_in),
                      c_char_p(in_str),
                      ctypes.byref(len_out),
                      ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.sin_vector_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


