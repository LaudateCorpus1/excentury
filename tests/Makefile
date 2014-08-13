MATLABPATH := $(CURDIR)/matlab:$(MATLABPATH)

all: test_cpp \
	 test_tensor \
	 test_python \
	 test_matlab

test_cpp:
	nosetests -vs test_debug
	nosetests -vs test_dump_text:test_cpp_to_text
	nosetests -vs test_dump_text:test_cpp_dump_text
	nosetests -vs test_load_text:test_cpp_load_text
	nosetests -vs test_load_text:test_cpp_load_text_str

test_tensor:
	nosetests -vs test_tensor:test_static_tensor
	nosetests -vs test_tensor:test_dynamic_tensor

test_python:
	nosetests -vs test_dump_text:test_python_to_text
	nosetests -vs test_dump_text:test_python_dump_text
	nosetests -vs test_load_text:test_python_load_text

test_matlab:
	nosetests -vs test_dump_text:test_matlab_to_text
	nosetests -vs test_dump_text:test_matlab_dump_text
	nosetests -vs test_load_text:test_matlab_load_text
	nosetests -vs test_load_text:test_matlab_parse_string
