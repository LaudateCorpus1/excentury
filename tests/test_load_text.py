"""LOAD TEXT TEST

To run:

    nosetests -vs test_load_text

For a single test:

    nosetests -vs test_load_text:name_of_test

"""

import os
from build import run_cmd, build_run, build_cpp, str_eq

MATLAB_EXP_OUT = """array_obj =     [1x1 Point]    [1x1 Point]

line_obj =   <a href="matlab:helpPopup Line" \
style="font-weight:bold">Line</a> with properties:

    a: [1x1 Point]
    b: [1x1 Point]

point_obj =   <a href="matlab:helpPopup Point" \
style="font-weight:bold">Point</a> with properties:

    x: 34.1000
    y: 4

tensor_obj =      1     2     3
     4     5     6

v_byte =    127

v_char = A
v_double =     0.0070

v_float =     3.1400

v_int =     10

v_long =             123456789

v_short =      2

v_str = hello world
v_ubyte =    255

v_uint =     10

v_ulong =             123456789

v_ushort =      2

"""

def test_matlab_load_text():
    """[MATLAB] load_text.m: """
    cmd = 'matlab -nodisplay -nosplash'
    run_cmd("%s < matlab/load_text.m > /dev/null" % cmd, "", "")
    str_eq(open("tmp_ml_out.txt", "r").read(), MATLAB_EXP_OUT)
    os.remove("tmp_ml_out.txt")


def test_matlab_parse_string():
    """[MATLAB] parse_string.m: """
    cmd = 'matlab -nodisplay -nosplash'
    run_cmd("%s < matlab/parse_string.m > /dev/null" % cmd, "", "")
    str_eq(open("tmp_ml_out.txt", "r").read(), MATLAB_EXP_OUT)
    os.remove("tmp_ml_out.txt")
    os.remove("tmp.xc")


EXP_OUT = """array_obj: [Point(1.000000, 0.000000) Point(2.000000, 4.000000)]
line_obj: Line(Point(100.000000, 200.000000), Point(300.000000, 400.000000))
point_obj: Point(34.100000, 4.000000)
tensor_obj: [[ 1.  2.  3.]
 [ 4.  5.  6.]]
v_byte: 127
v_char: A
v_double: 0.007
v_float: 3.14
v_int: 10
v_long: 123456789
v_short: 2
v_str: hello world
v_ubyte: 255
v_uint: 10
v_ulong: 123456789
v_ushort: 2
"""

def test_python_load_text():
    """[PYTHON] load_text.py: """
    run_cmd("python python/load_text.py", "", EXP_OUT)

def test_cpp_load_text():
    """[CPP] load_text.cpp: """
    build_run('load_text', "", """v_char: A
(int)v_byte: 127
(int)v_ubyte: 255
v_short: 2
v_int: 10
v_long: 123456789
v_ushort: 2
v_uint: 10
v_ulong: 123456789
v_float: 3.14
v_double: 0.007
v_str: hello world
point_obj: Point(34.100000, 4.000000)
line_obj: [Point(100.000000, 200.000000), Point(300.000000, 400.000000)]
array_obj: 
  Point(1.000000, 0.000000)
  Point(2.000000, 4.000000)
tensor_obj: 
  1.000000
  2.000000
  3.000000
  4.000000
""")

def test_cpp_load_text_str():
    """[CPP] load_text_str.cpp: """
    build_cpp('load_text_str')
    run_cmd('load_text_str.run "`< tmp.xc`"', "", """v_char: A
(int)v_byte: 127
(int)v_ubyte: 255
v_short: 2
v_int: 10
v_long: 123456789
v_ushort: 2
v_uint: 10
v_ulong: 123456789
v_float: 3.14
v_double: 0.007
v_str: hello world
point_obj: Point(34.100000, 4.000000)
line_obj: [Point(100.000000, 200.000000), Point(300.000000, 400.000000)]
array_obj: 
  Point(1.000000, 0.000000)
  Point(2.000000, 4.000000)
tensor_obj: 
  1.000000
  2.000000
  3.000000
  4.000000
""")
    os.remove('tmp.xc')
