"""MATLAB

Module to make matlab communicate with cpp.

"""

import os
import site
from excentury.command.config import get_cfg
from excentury.lang import FileParser, check_inputs, extract_name
from excentury.lang.matlab.cpp_writer import write_cpp_function
from excentury.lang.matlab.matlab_writer import write_matlab_file
from excentury.lang.matlab.matlab_writer import write_matlab_defs


DESC = """
Creates a mex executable from the xcpp file and a matlab
function wrapper that calls the executable.

"""

DEFAULTS = {
    'dir': site.getuserbase()+'/lib/excentury/cpp',
    'wrapper': site.getuserbase()+'/lib/excentury/matlab',
    'dump': 'text',
    'load': 'text',
    'cxx': 'g++',
    'cxxlib': '',
    'cxxinc': '',
    'cxxopt': '-O3',
    'mexopt': '-largeArrayDims',
    'debug': '0',
    'force': 'false',
    'epilog': '',
    'verbose': 'false',
}


def add_options(argp):
    "Add options to the parser. "
    argp.add_argument('--force', type=int, metavar='N', nargs='*',
                      help='force compilation on functions')
    argp.add_argument('--dir', type=str, metavar='',
                      help='directory for cpp files')
    argp.add_argument('--wrapper', type=str, metavar='',
                      help='directory for matlab functions')
    argp.add_argument('--dump', type=str, metavar='',
                      choices=['text', 'binary'],
                      help='method for dumping data: text, binary ')
    argp.add_argument('--load', type=str, metavar='',
                      choices=['text', 'binary'],
                      help='method for loading data: text, binary ')
    argp.add_argument('--cxx', type=str, metavar='',
                      help='c++ compiler (used when gathering inputs)')
    argp.add_argument('--cxxlib', type=str, metavar='',
                      help='paths to libraries for the compiler')
    argp.add_argument('--cxxinc', type=str, metavar='',
                      help='paths to include for the compiler')
    argp.add_argument('--cxxopt', type=str, metavar='',
                      help='c++ compiler options')
    argp.add_argument('--mexopt', type=str, metavar='',
                      help='mex compiler options')
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
    cfg = get_cfg(arg, 'matlab', DEFAULTS)
    cfg['xcpp']['filename'] = extract_name(filename)
    xcfile = FileParser(filename).parse()
    cfg['matlab']['opt'] = cfg['matlab']['cxxopt']
    in_map, defs = check_inputs(xcfile, cfg, 'matlab')

    cfg['matlab']['cxx'] = 'mex'
    root = cfg['xcpp']['root']
    matlabdir = cfg['matlab']['wrapper']
    if matlabdir[0] == '/':
        base = matlabdir
    else:
        base = '%s/%s' % (root, matlabdir)
    cfg['matlab']['pkg'] = '%s/+%s' % (base, cfg['xcpp']['filename'])
    if not os.path.exists(cfg['matlab']['pkg']):
        os.mkdir(cfg['matlab']['pkg'])
    cfg['matlab']['opt'] = cfg['matlab']['mexopt']

    if defs:
        write_matlab_defs(cfg, defs)
    for func in xcfile.function:
        write_cpp_function(xcfile, func, cfg)
        write_matlab_file(func, cfg, in_map)
