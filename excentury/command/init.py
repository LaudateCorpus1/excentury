"""Init

Creates an excentury project.

"""

import textwrap
import os.path as pth
from excentury.command import disp, make_dir, append_variable
from excentury.command.add import update_entries


DESC = """
Creates an excentury configuration file along with directories to
store the files.

"""

XCPP_CONFIG = """[xcpp]
name = {name}
path = xcpp

[cpp]
dir = cpp
bin = bin
cxxinc = cpp
cxxlib = lib
opt = -O3 -Werror -Wfatal-errors -Wextra

[python]
dir = cpp
lib = lib
wrapper = python
cxxinc = cpp
cxxlib = lib
opt = -O3 -Werror -Wfatal-errors -Wextra

[matlab]
dir = cpp
lib = matlab
wrapper = matlab
cxxinc = cpp
cxxlib = lib
cxxopt = -O3 -Werror -Wfatal-errors -Wextra

"""


def add_parser(subp, raw):
    """Add a parser to the main subparser. """
    tmpp = subp.add_parser('init', help='initialize excentury project',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('name', type=str,
                      help='project name')


def make_directories():
    """Creates the project directories. """
    dirs = [
        'xcpp',
        'bin',
        'lib',
        'cpp',
        'matlab',
        'python',
    ]
    disp('Creating directories ... \n')
    for path in dirs:
        if make_dir(path):
            disp('  creating %r\n' % path)
        else:
            disp('  %r already exists\n' % path)


def make_config_file(arg):
    """Creates a configuration file. """
    if pth.exists('xcpp.config'):
        disp('xcpp.config already exists ...\n')
        return
    disp('creating xcpp.config ... ')
    with open('xcpp.config', 'w') as _fp:
        _fp.write(XCPP_CONFIG.format(name=arg.name))
    disp('done\n')


def make_bashrc(arg):
    """Create the bashrc file for the project. """
    if pth.exists('.xcpprc'):
        disp('.xcpprc already exists ...\n')
        return
    disp('creating .xcpprc ... ')
    with open('.xcpprc', 'w') as rcf:
        rcf.write("# %s bash configuration file\n" % arg.name)
        rcf.write('ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"\n')
        rcf.write('export XCPP_CONFIG_PATH=$ROOT\n')
        rcf.write(append_variable('PATH', '$ROOT/bin'))
        rcf.write(append_variable('LD_LIBRARY_PATH', '$ROOT/lib'))
        rcf.write(append_variable('MATLABPATH', '$ROOT/matlab'))
        rcf.write(append_variable('PYTHONPATH', '$ROOT/python'))
    disp('done\n')


def run(arg):
    """Run the command. """
    make_directories()
    make_config_file(arg)
    make_bashrc(arg)
    update_entries(pth.abspath('.'))
