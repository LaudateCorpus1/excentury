"""PYTHON

Module to make python modules that communicate with cpp.

"""

import site
from excentury.command.config import get_cfg
from excentury.lang import FileParser, check_inputs, extract_name
from excentury.lang.python.cpp_writer import write_cpp_file
from excentury.lang.python.python_writer import write_python_file


DESC = """
Creates a shared library from the xcpp file and a python
module which communicates with said library.

"""

DEFAULTS = {
    'dir': site.getuserbase()+'/lib/excentury/cpp',
    'lib': site.getuserbase()+'/lib/excentury/lib',
    'wrapper': site.getuserbase()+'/lib/excentury/python',
    'dump': 'text',
    'load': 'text',
    'cxx': 'g++',
    'cxxlib': '',
    'cxxinc': '',
    'opt': '-O3',
    'debug': '0',
    'epilog': '',
    'verbose': 'false',
}


def add_options(argp):
    "Add options to the parser. "
    argp.add_argument('--dir', type=str, metavar='',
                      help='directory for cpp files')
    argp.add_argument('--lib', type=str, metavar='',
                      help='directory for shared libraries')
    argp.add_argument('--wrapper', type=str, metavar='',
                      help='directory for python modules')
    argp.add_argument('--dump', type=str, metavar='',
                      choices=['text', 'binary'],
                      help='method for dumping data: text, binary ')
    argp.add_argument('--load', type=str, metavar='',
                      choices=['text', 'binary'],
                      help='method for loading data: text, binary ')
    argp.add_argument('--cxx', type=str, metavar='',
                      help='c++ compiler')
    argp.add_argument('--cxxlib', type=str, metavar='',
                      help='paths to libraries for the compiler')
    argp.add_argument('--cxxinc', type=str, metavar='',
                      help='paths to include for the compiler')
    argp.add_argument('--opt', type=str, metavar='',
                      help='compiler options')
    argp.add_argument('--debug', type=str, choices=['0', '1', '2', '3'],
                      metavar='', help='debug level: 0, 1, 2, 3')
    argp.add_argument('--epilog', type=str, metavar='',
                      help='enter other options such as libraries '
                           'at the end of the command')
    argp.add_argument('--verbose', '-v', action='store_true',
                      default=None,
                      help='display commands issued by xcpp')


def process_file(arg, filename):
    """Process the xcpp file. """
    cfg = get_cfg(arg, 'python', DEFAULTS)
    cfg['xcpp']['filename'] = extract_name(filename)
    xcfile = FileParser(filename).parse()
    in_map, defs = check_inputs(xcfile, cfg, 'python')
    write_cpp_file(xcfile, cfg)
    write_python_file(xcfile, cfg, in_map, defs)
