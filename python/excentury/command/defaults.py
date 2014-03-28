"""Defaults

Print the default values for each command and languages.

"""

import textwrap
from excentury.command import import_mod, error
from excentury.command.to import get_lang_names

DESC = """

View default values for a subcommand or a language.

"""


def add_parser(subp, raw):
    "Add a parser to the main subparser. "
    tmpp = subp.add_parser('defaults', help='print default values',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('name', type=str,
                      help='subcommand name or language')


def run(arg):
    """Run command. """
    name = arg.name
    if name in get_lang_names():
        mod = import_mod('excentury.lang.%s' % name)
    else:
        try:
            mod = import_mod('excentury.command.%s' % name)
        except ImportError:
            error('ERROR: invalid command or language: %r\n' % name)
    if hasattr(mod, 'DEFAULTS'):
        for key, val in mod.DEFAULTS.iteritems():
            print '%s = %r' % (key, val)
    else:
        print 'NO DEFAULTS'
