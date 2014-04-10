# File generated on Wed Apr 09, 2014 04:03:49 PM by xcpp.
"""Util

This collection of functions demostrate how to create functions
compatible with python and cpp."""
from excentury import TextParser, TextDumper, XCStruct
from ctypes import c_char, c_size_t, c_char_p
import ctypes

LIB = ctypes.cdll.LoadLibrary("util_pylib.so")

DEFS = {
'Point': [
    ['x', ['R', '8']],
    ['y', ['R', '8']],
],
}
def xc_struct(name):
    """Return an XCStruct object using the entries of the dictionary
    DEFS in this module."""
    return XCStruct(name, DEFS[name])


LIB.square_py.restype = None
LIB.square_py_clear.restype = None
def square(x, unpack=True):
    """return the square of the number.

    parameters:

      `x`: number to be squared.
    """
    tdump = TextDumper()
    tdump.dump(x, "x", ['R', '8'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.square_py(c_size_t(len_in),
                  c_char_p(in_str),
                  ctypes.byref(len_out),
                  ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.square_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.cube_py.restype = None
LIB.cube_py_clear.restype = None
def cube(x, unpack=True):
    """cube a number

    parameters:

      `x`: number to be cubed.
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


LIB.move_point_py.restype = None
LIB.move_point_py_clear.restype = None
def move_point(p, x, unpack=True):
    """Adds a number to each of the coordinates of a point.

    parameters:

      `p`: the point to be moved.
      `x`: the amount the point should be moved.
    """
    tdump = TextDumper()
    tdump.dump(p, "p", ['S', 'Point'])
    tdump.dump(x, "x", ['R', '8'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.move_point_py(c_size_t(len_in),
                      c_char_p(in_str),
                      ctypes.byref(len_out),
                      ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.move_point_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.make_line_py.restype = None
LIB.make_line_py_clear.restype = None
def make_line(p1, p2, unpack=True):
    """Given two points, it constructs a line.

    parameters:

      `p1`: the first point.
      `p2`: the second point.
    """
    tdump = TextDumper()
    tdump.dump(p1, "p1", ['S', 'Point'])
    tdump.dump(p2, "p2", ['S', 'Point'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.make_line_py(c_size_t(len_in),
                     c_char_p(in_str),
                     ctypes.byref(len_out),
                     ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.make_line_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.scale_py.restype = None
LIB.scale_py_clear.restype = None
def scale(v, alpha, unpack=True):
    """Scalar multiplication.

    parameters:

      `v`: the vector to multiply. 
      `alpha`: the scalar.
    """
    tdump = TextDumper()
    tdump.dump(v, "v", ['T', ['R', '8']])
    tdump.dump(alpha, "alpha", ['R', '8'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.scale_py(c_size_t(len_in),
                 c_char_p(in_str),
                 ctypes.byref(len_out),
                 ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.scale_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.print_msg_py.restype = None
LIB.print_msg_py_clear.restype = None
def print_msg(msg, unpack=True):
    """Print a message to the standard error stream.

    parameters:

      `msg`: the message to be printed.
    """
    tdump = TextDumper()
    tdump.dump(msg, "msg", ['W'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.print_msg_py(c_size_t(len_in),
                     c_char_p(in_str),
                     ctypes.byref(len_out),
                     ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.print_msg_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.gen_tensors_py.restype = None
LIB.gen_tensors_py_clear.restype = None
def gen_tensors(unpack=True):
    """Generate tensors of dimension 4.
    """
    tdump = TextDumper()
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.gen_tensors_py(c_size_t(len_in),
                       c_char_p(in_str),
                       ctypes.byref(len_out),
                       ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.gen_tensors_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


LIB.scale_array_py.restype = None
LIB.scale_array_py_clear.restype = None
def scale_array(v, s, unpack=True):
    """scale a one dimentional array.

    parameters:

      `v`: the array to be scaled.
      `s`: the scalar factor.
    """
    tdump = TextDumper()
    tdump.dump(v, "v", ['T', ['R', '8']])
    tdump.dump(s, "s", ['R', '8'])
    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.scale_array_py(c_size_t(len_in),
                       c_char_p(in_str),
                       ctypes.byref(len_out),
                       ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = TextParser(out_str[:len_out.value]).parse()
    LIB.scale_array_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val


