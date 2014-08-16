"""Add

Add an excentury configuration file to excentury.

"""

import textwrap
import os.path as pth
from excentury.command import error, trace
from excentury.command.config import _read_config

DESC = """
Adds an excentury configuration file to the list of the users
projects. A valid excentury project must have two files:

    xcpp.config
    .xcpprc

Furthermore, the `xcpp.config` file must have the key

    xcpp.name

"""


def add_parser(subp, raw):
    """Add a parser to the main subparser. """
    tmpp = subp.add_parser('add', help='add an excentury project',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('path', type=str,
                      help='project path')


def get_entries():
    """Read the projects file. """
    pfile = pth.expandvars('$HOME/.excentury/projects')
    try:
        content = list()
        with open(pfile, 'r') as epf:
            for line in epf:
                if line.strip() == '':
                    continue
                key, val = line.split(':')
                content.append((key.strip(), val.strip()))
        return content
    except IOError:
        return list()


def set_entries(data):
    """Write the projects file. """
    pfile = pth.expandvars('$HOME/.excentury/projects')
    with open(pfile, 'w') as epf:
        for entry in data:
            epf.write('%s: %s\n' % (entry[0], entry[1]))


def append_entry(data, name, path):
    """Append an entry if it doesn't have it. Returns true if an
    entry was appened, false otherwise. """
    found = False
    for entry in data:
        if path == entry[1]:
            found = True
            break
    if not found:
        data.append((name, path))
        return True
    return False


def update_entries(path):
    """Updates the projects entries. Checks to see if the
    `xcpp.config` and `.xcpprc` files exists. """
    data = get_entries()
    path = pth.abspath(path)
    try:
        config = _read_config('%s/xcpp.config' % path)
    except IOError:
        error("ERROR: `xcpp.config` not found in %r\n" % path)
    if not pth.exists('%s/.xcpprc' % path):
        error("ERROR: `xcpprc` not found in %r\n" % path)
    if 'xcpp' not in config:
        error("ERROR: Missing `xcpp` section in `xcpp.config`\n")
    if 'name' not in config['xcpp']:
        error("ERROR: Missing `xcpp.name` value in `xcpp.config`\n")
    if not append_entry(data, config['xcpp']['name'], path):
        trace("%r has been previously added\n" % path)
    set_entries(data)


def run(arg):
    """Run the command. """
    update_entries(arg.path)
