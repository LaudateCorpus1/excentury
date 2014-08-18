"""DEBUG TEST

To run:

    nosetests -vs test_debug

For a single test:

    nosetests -vs test_debug:name_of_test

"""

import os
from tests import build_run


def test_nodebug():
    """debug.run: """
    exp_err = ""
    exp_out = """Hello world\nDebug was turned off...\n"""
    build_run('debug', exp_err, exp_out)


def test_debug1():
    """debug.run1: """
    exp_out = """Hello world\n"""
    exp_err = """\x1b[1;31mERROR CAUGHT BY\x1b[0m \x1b[36m\
%s/cpp/debug.cpp\x1b[0m \
line \x1b[1m7\x1b[0m executing: \n\n    \x1b[1mint main()\n\n\
\x1b[0mThe error occurred because:  \x1b[1mtrue\
\x1b[0m\n\n\x1b[1mThis is a test to check that DEBUG is \
on.\n\x1b[0m""" % os.path.dirname(__file__)
    build_run('debug', exp_err, exp_out, 1)


def test_debug2():
    """debug.run2: """
    exp_out = """Hello world\n"""
    exp_err = """This message is only seen with DEBUG set to 2\n\
\x1b[1;31mERROR CAUGHT BY\x1b[0m \x1b[36m\
%s/cpp/debug.cpp\x1b[0m \
line \x1b[1m7\x1b[0m executing: \n\n    \x1b[1mint main()\n\n\
\x1b[0mThe error occurred because:  \x1b[1mtrue\
\x1b[0m\n\n\x1b[1mThis is a test to check that DEBUG is \
on.\n\x1b[0m""" % os.path.dirname(__file__)
    build_run('debug', exp_err, exp_out, 2)


def test_debug3():
    """debug.run3: """
    exp_out = """Hello world\n"""
    exp_err = """This message is only seen with DEBUG set to 2\n\
This message is only seen with DEBUG set to 3\n\
\x1b[1;31mERROR CAUGHT BY\x1b[0m \x1b[36m\
%s/cpp/debug.cpp\x1b[0m \
line \x1b[1m7\x1b[0m executing: \n\n    \x1b[1mint main()\n\n\
\x1b[0mThe error occurred because:  \x1b[1mtrue\
\x1b[0m\n\n\x1b[1mThis is a test to check that DEBUG is \
on.\n\x1b[0m""" % os.path.dirname(__file__)
    build_run('debug', exp_err, exp_out, 3)
