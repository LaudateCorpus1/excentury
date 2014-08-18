"""TEST XCPP

To run:

    nosetests -vs test_xcpp

For a single test:

    nosetests -vs test_xcpp:name_of_test

"""

from tests import run_cmd, exec_cmd, eq_
from excentury import to_text, load_file


def test_xcpp_cpp():
    """[XCPP-CPP]: """
    exec_cmd('excentury xc_test.xcpp to cpp')
    cmd = 'xc_test-timestwo.run "%s"' % to_text(x=2.0)
    exp_out = '0 1\nresult R 8 4.000000 \n'
    exp_err = ''
    run_cmd(cmd, exp_err, exp_out)
    cmd = 'xc_test-cube.run "%s"' % to_text(x=3)
    exp_out = '0 1\nresult I 4 27 \n'
    exp_err = ''
    run_cmd(cmd, exp_err, exp_out)


def test_xcpp_python():
    """[XCPP-PYTHON]: """
    exec_cmd('excentury xc_test.xcpp to python')
    xc = __import__("xc_test")
    eq_(xc.timestwo(2.0), 4, "Failed...")
    eq_(xc.cube(3), 27, "Failed...")


def test_xcpp_matlab():
    """[XCPP-MATLAB]: """
    exec_cmd('excentury xc_test.xcpp to matlab')
    cmd = 'matlab -nodisplay -nosplash'
    run_cmd("%s < matlab/xc_test.m > /dev/null" % cmd, "", "")
    data = load_file('tmp.xc')
    eq_(data['x'], 4, "Failed...")
    eq_(data['y'], 27, "Failed...")
