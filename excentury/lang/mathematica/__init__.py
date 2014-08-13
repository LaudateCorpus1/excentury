"""MATHEMATICA

Module to make mathematica packages that communicate with cpp via
MathLink.

"""

from excentury.command.config import get_cfg
from excentury.lang import FileParser, check_inputs, extract_name
from excentury.lang.mathematica.cpp_writer import write_cpp_file
from excentury.lang.mathematica.m_writer import write_m_file


DESC = """
Creates a shared library from the xcpp file and a mathematica
package which communicates with said library.

"""

DEFAULTS = {
    'dir': '.',
    'mma': '.',
    'app': '.',
    'cxx': 'g++',
    'cxxlib': '',
    'cxxinc': '',
    'opt': '-O3',
    'debug': '0',
    'mlink': '$MLINK'
}


MLINK_HELP = """directory containing the mathlink tools.
This option should be set to the value returned by the
following Mathematica command: Print[$InstallationDirectory <>
"/SystemFiles/Links/MathLink/DeveloperKit/" <> $SystemID <>
"/CompilerAdditions"]."""


def add_options(argp):
    "Add options to the parser. "
    argp.add_argument('--dir', type=str, metavar='',
                      help='directory for cpp files')
    argp.add_argument('--mma', type=str, metavar='',
                      help='directory for mma packages')
    argp.add_argument('--app', type=str, metavar='',
                      help='application name where to place the package')
    argp.add_argument('--mlink', type=str, metavar='',
                      help=MLINK_HELP)
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
    cfg = get_cfg(arg, 'mathematica', DEFAULTS)
    cfg['xcpp']['filename'] = extract_name(filename)
    xcfile = FileParser(filename).parse()
    in_map, _ = check_inputs(xcfile, cfg, 'mathematica')
    write_cpp_file(xcfile, cfg, in_map)
    write_m_file(xcfile, cfg)
