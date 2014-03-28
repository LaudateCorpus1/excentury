import os
import excentury as xc
import objects as obj
import numpy as np

var = xc.load_file("tmp.xc")
variables = ['array_obj', 'line_obj', 'point_obj', 'tensor_obj', 
    'v_byte', 'v_char', 'v_double', 'v_float', 'v_int', 'v_long',
    'v_short', 'v_str', 'v_ubyte', 'v_uint', 'v_ulong', 'v_ushort']
for name in variables:
    print '%s: %s' % (name, str(var[name]))
os.remove("tmp.xc")
