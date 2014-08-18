"""View

Reads excentury files and displays its content.

"""

import os
import textwrap
from excentury.command import error
from excentury.command.config import get_cfg
from excentury.core.load_text import TextParser

DESC = """
Read excentury files and display its content.

"""


def add_parser(subp, raw):
    "Add a parser to the main subparser. "
    tmpp = subp.add_parser('view', help='display xc files',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('--binary', '-b', action='store_true',
                      help='read in binary format')
    tmpp.add_argument('--defs', '-d', action='store_true',
                      help='print dictionary')
    tmpp.add_argument('--val', '-v', action='store_true',
                      help='print values')


def _get_filename(arg):
    """Helper function. """
    if arg.inputfile == '_':
        error("ERROR: Missing inputfile. Use -h to see usage.\n")
    cfg = get_cfg(arg, 'xcpp')
    root = cfg['xcpp']['root']
    paths = cfg['xcpp']['path'].split(':')

    is_file = False
    for path in paths:
        if path == '.' or path[0] in ['/']:
            abs_path = '%s/%s' % (path, arg.inputfile)
        else:
            abs_path = '%s/%s/%s' % (root, path, arg.inputfile)
        if os.path.exists(abs_path):
            is_file = True
            break
    if not is_file:
        fname = '`%s` in\n  %s' % (arg.inputfile, '\n  '.join(paths))
        error("ERROR: Unable to find %s\n" % fname)
    return abs_path


def run(arg):
    """Run command. """
    filename = _get_filename(arg)

    if arg.binary:
        error('Warning: Not yet done...\n')
    else:
        var, defs = TextParser(open(filename, 'r').read()).parse_info()
        if arg.val:
            varv = TextParser(open(filename, 'r').read()).parse()

    print 'Variables Stored in "%s":\n' % arg.inputfile
    if arg.val:
        for name, info in var.iteritems():
            print '  %s: %s = ' % (name, str(info))
            print '    %s\n' % repr(varv[name])
    else:
        for name, info in var.iteritems():
            print '  %s: %s' % (name, str(info))
    print ''

    if arg.defs:
        print 'Definitions Stored in "%s":\n' % arg.inputfile
        for key in defs:
            print "  %s: " % key
            for att, info in defs[key]:
                print '    %s: %s' % (att, str(info))
