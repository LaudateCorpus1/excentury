"""CPP

Module to convert xcpp files to cpp files which will become stand
alone executables.

"""

import site
from excentury.command.config import get_cfg
from excentury.lang import FileParser, check_inputs, extract_name
from excentury.lang.cpp.aux import process_function

DESC = """
Converts the xcpp file to a cpp file which will then be compiled
into a stand alone executable.

"""

DEFAULTS = {
    'dir': site.getuserbase()+'/lib/excentury/cpp',
    'bin': site.getuserbase()+'/lib/excentury/bin',
    'ext': 'run',
    'dump': 'text',
    'load': 'text',
    'cxx': 'g++',
    'cxxlib': '',
    'cxxinc': '',
    'opt': '-O3',
    'debug': '0',
    'force': 'false'
}


def add_options(argp):
    "Add options to the parser. "
    argp.add_argument('--force', type=int, metavar='N', nargs='*',
                      help='force compilation on functions')
    argp.add_argument('--dir', type=str, metavar='',
                      help='directory for cpp files')
    argp.add_argument('--bin', type=str, metavar='',
                      help='bin directory for executables')
    argp.add_argument('--ext', type=str, metavar='',
                      help='executable extension')
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


def process_file(arg, filename):
    """Process the xcpp file. """
    cfg = get_cfg(arg, 'cpp', DEFAULTS)
    cfg['xcpp']['filename'] = extract_name(filename)
    xcfile = FileParser(filename).parse()
    check_inputs(xcfile, cfg, 'cpp')
    for func in xcfile.function:
        process_function(xcfile, cfg, func)
