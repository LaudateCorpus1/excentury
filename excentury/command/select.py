"""Select

Select an excentury project

"""

import textwrap
import os.path as pth
from excentury.command import error, disp
from excentury.command.add import get_entries
from excentury.command.install import excenturyrc_str


DESC = """
Enter a project name or an integer to select one of the bookmarked
projects. Use select with no arguments to view the entries.

The `~/.bash_profile` or `~/.bashrc` file must be sourced after the
call of this command in order for the chances to take effect.

"""


def add_parser(subp, raw):
    """Add a parser to the main subparser. """
    tmpp = subp.add_parser('select', help='select an excentury project',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('project', type=str, default=None, nargs='?',
                      help='project name or number')


def display():
    """Display the excentury projects. """
    data = get_entries()
    current = get_current()
    if current == '':
        disp('No project is currently selected\n')
    else:
        disp('  [0]: Select this entry for excenturys default use \n')
    for num, entry in enumerate(data):
        if current == entry[1]:
            disp('->[%d]: %s --> %s\n' % (num+1, entry[0], entry[1]))
        else:
            disp('  [%d]: %s --> %s\n' % (num+1, entry[0], entry[1]))


def get_current():
    """Read the file `~/.excentury/current` to obtain the current
    project."""
    fpath = pth.expandvars("$HOME/.excentury/current")
    try:
        with open(fpath, 'r') as _fp:
            content = _fp.read().strip()
    except IOError:
        content = ''
    return content


def set_current(path):
    """Write the current file. """
    fpath = pth.expandvars("$HOME/.excentury/current")
    with open(fpath, 'w') as _fp:
        _fp.write(path)


def set_project(name):
    """Sets a project. """
    rc_path = pth.expandvars('$HOME/.excentury/excenturyrc')
    if name == '0':
        with open(rc_path, 'w') as rcfile:
            rcfile.write(excenturyrc_str())
        set_current('')
        disp("Restart bash to clear previous project settings.\n")
        return
    data = get_entries()
    found = False
    for num, entry in enumerate(data):
        if name in [entry[0], str(num+1)]:
            set_current(entry[1])
            with open(rc_path, 'w') as rcfile:
                rcfile.write(excenturyrc_str())
                rcfile.write('source %s/.xcpprc\n' % entry[1])
            disp('Project %r has been set. Restart bash.\n' % name)
            found = True
            break
    if not found:
        error("ERROR: not a valid entry\n")


def run(arg):
    """Run the command. """
    if arg.project is None:
        display()
        return
    set_project(arg.project)
