import excentury as xc
import objects as obj
import numpy as np

point_obj = obj.Point(34.1, 4)
line_obj = obj.Line(100, 200, 300, 400)
tensor_obj = np.array([[1.0,2,3],[4,5,6]])
array_obj = np.array([obj.Point(1,0), obj.Point(2,4)])

xc.dump_text("tmp.xc",
    ('A', "v_char"),
    (127, "v_byte", "byte"),
    (255, "v_ubyte", "ubyte"),
    (2, "v_short", "short"),
    (10, "v_int", "int"),
    (123456789, "v_long", "long"),
    (2, "v_ushort", "ushort"),
    (10, "v_uint", "uint"),
    (123456789, "v_ulong", "ulong"),
    (3.14, "v_float", "float"),
    (0.007, "v_double", "double"),
    ('hello world', "v_str"),
    (point_obj, "point_obj"),
    (line_obj, "line_obj"),
    array_obj=array_obj,
    tensor_obj=tensor_obj
)
