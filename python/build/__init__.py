"""Build

Provides functions to compile c++ files and for unit testing.

"""

import os
import sys
from subprocess import Popen, PIPE
from nose.tools import eq_

def exec_cmd(cmd, verbose=False):
    "Run a subprocess and return its output and errors. "
    if verbose:
        out = sys.stdout
        err = sys.stderr
    else:
        out = PIPE
        err = PIPE
    process = Popen(cmd, shell=True, stdout=out, stderr=err)
    out, err = process.communicate()
    return out, err, process.returncode

def build_cpp(name, debug=None):
    """Compile a file and place it in bin. """
    root = os.environ['XCROOT']
    if debug is None:
        out = '-o %s/main/bin/%s.run' % (root, name)
    else:
        out = '-DDEBUG=%s -o %s/main/bin/%s.run%s' % (debug, root,
                                                 name, debug)
    cmd = 'g++ -O3 %s %s/main/cpp/%s.cpp' % (out, root, name)
    out, err, _ = exec_cmd(cmd)
    eq_(err, "", "Build Error -->\n%s\n%s" % (cmd, err))

def run_cmd(cmd, exp_err, exp_out):
    """Run a command and compare the expected output and error."""
    out, err, _ = exec_cmd(cmd)
    hline = '_'*60
    msg = "%s stderr -->\n%s\n%s\n%s\n\
%s expected stderr -->\n%s\n%s\n%s\n" % (cmd, hline, err, hline,
                                         cmd, hline, exp_err, hline)
    eq_(err, exp_err, msg)
    msg = "%s stdout -->\n%s\n%s\n%s\n\
%s expected stdout -->\n%s\n%s\n%s\n" % (cmd, hline, out, hline,
                                         cmd, hline, exp_out, hline)
    eq_(out, exp_out, msg)

def build_run(prog, exp_err, exp_out, debug=None):
    """Build and run. """
    build_cpp(prog, debug)
    if debug is None:
        cmd = '%s.run' % prog
    else:
        cmd = '%s.run%d' % (prog, debug)
    run_cmd(cmd, exp_err, exp_out)

def str_eq(str1, str2):
    """Compare two strings. """
    hline = '_'*60
    msg = "str1 -->\n%s\n%s\n%s\n\
str2 -->\n%s\n%s\n%s\n" % (hline, str1, hline,
                           hline, str2, hline)
    eq_(str1, str2, msg)
