"""DUMP TEXT TEST

To run:

    nosetests -vs test_dump_text

For a single test:

    nosetests -vs test_dump_text:name_of_test

"""

from tests import run_cmd, str_eq, build_run

MATLAB_FILE_CONTENT = """2
Point x R 8 y R 8 
Line a S Point b S Point 
16
v_char C 1 A 
v_byte I 1 127 
v_ubyte N 1 255 
v_short I 2 2 
v_int I 4 10 
v_long I 8 123456789 
v_ushort N 2 2 
v_uint N 4 10 
v_ulong N 8 123456789 
v_float R 4 3.140000 
v_double R 8 0.007000 
v_str W 11 hello world 
point_obj S Point 34.100000 4.000000 
line_obj S Line 100.000000 200.000000 300.000000 400.000000 
array_obj T S Point 0 1 2 1.000000 0.000000 2.000000 4.000000 
tensor_obj T R 8 0 2 2 3 1.000000 4.000000 2.000000 5.000000 3.000000\
 6.000000 
"""


def test_matlab_to_text():
    """[MATLAB] to_text.m: """
    cmd = 'matlab -nodisplay -nosplash'
    run_cmd("%s < matlab/to_text.m > /dev/null" % cmd, "", "")
    str_eq(open("tmp.xc", "r").read(), MATLAB_FILE_CONTENT)


def test_matlab_dump_text():
    """[MATLAB] dump_text.m: """
    cmd = 'matlab -nodisplay -nosplash'
    run_cmd("%s < matlab/dump_text.m > /dev/null" % cmd, "", "")
    str_eq(open("tmp.xc", "r").read(), MATLAB_FILE_CONTENT)


PYTHON_FILE_CONTENT = """2
Point x R 8 y R 8 
Line a S Point b S Point 
16
v_char C 1 A 
v_byte I 1 127 
v_ubyte N 1 255 
v_short I 2 2 
v_int I 4 10 
v_long I 8 123456789 
v_ushort N 2 2 
v_uint N 4 10 
v_ulong N 8 123456789 
v_float R 4 3.140000 
v_double R 8 0.007000 
v_str W 11 hello world 
point_obj S Point 34.100000 4.000000 
line_obj S Line 100.000000 200.000000 300.000000 400.000000 
array_obj T S Point 0 1 2 1.000000 0.000000 2.000000 4.000000 
tensor_obj T R 8 1 2 2 3 1.000000 2.000000 3.000000 4.000000 5.000000\
 6.000000 
"""


def test_python_to_text():
    """[PYTHON] to_text.py: """
    run_cmd("python python/to_text.py", "", PYTHON_FILE_CONTENT)


def test_python_dump_text():
    """[PYTHON] dump_text.py: """
    run_cmd("python python/dump_text.py", "", "")
    str_eq(open("tmp.xc", "r").read(), PYTHON_FILE_CONTENT)


def test_cpp_to_text():
    """[CPP] to_text.cpp: """
    build_run("to_text", "", """2
Point x R 8 y R 8 
Line a S Point b S Point 
16
v_char C 1 A 
v_byte I 1 127 
v_ubyte N 1 255 
v_short I 2 2 
v_int I 4 10 
v_long I 8 123456789 
v_ushort N 2 2 
v_uint N 4 10 
v_ulong N 8 123456789 
v_float R 4 3.14 
v_double R 8 0.007 
v_str W 11 hello world 
point_obj S Point 34.1 4 
line_obj S Line 100 200 300 400 
array_obj T S Point 0 1 2 1 0 2 4 
tensor_obj T R 8 0 1 4 1 2 3 4 
""")


def test_cpp_dump_text():
    """[CPP] dump_text.cpp: """
    build_run("dump_text", "", "")
    str_eq(open("tmp.xc", "r").read(), """2
Point x R 8 y R 8 
Line a S Point b S Point 
16
v_char C 1 A 
v_byte I 1 127 
v_ubyte N 1 255 
v_short I 2 2 
v_int I 4 10 
v_long I 8 123456789 
v_ushort N 2 2 
v_uint N 4 10 
v_ulong N 8 123456789 
v_float R 4 3.140000 
v_double R 8 0.007000 
v_str W 11 hello world 
point_obj S Point 34.100000 4.000000 
line_obj S Line 100.000000 200.000000 300.000000 400.000000 
array_obj T S Point 0 1 2 1.000000 0.000000 2.000000 4.000000 
tensor_obj T R 8 0 1 4 1.000000 2.000000 3.000000 4.000000 
""")
