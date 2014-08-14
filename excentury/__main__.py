"""Command line use of excentury

To run excentury from the command line do the following:

    python -m excentury ...

Use the option --help for more information.

"""

import sys
import argparse
import textwrap
from os import listdir
from os.path import split, abspath, isfile, join, splitext
from glob import iglob
from excentury.__version__ import VERSION
from excentury.command import import_mod
from excentury.command.config import get_cfg
try:
    import argcomplete
except ImportError:
    pass


def valid_files(parsed_args, **_):
    """Return a list of valid files to edit."""
    cfg = get_cfg(parsed_args, 'xcpp')
    root = cfg['xcpp']['root']
    paths = cfg['xcpp']['path'].split(':')
    choices = []
    for path in paths:
        if path == '.' or path[0] in ['/']:
            abs_path = path
        else:
            abs_path = '%s/%s' % (root, path)
        try:
            choices.extend([fname for fname in listdir(abs_path)
                            if isfile(join(abs_path, fname))])
        except OSError:
            pass
    return choices


#pylint: disable=W0212
def get_argparse_options(argp):
    """Helper function to preparse the arguments. """
    opt = dict()
    for action in argp._optionals._actions:
        for key in action.option_strings:
            if action.type is None:
                opt[key] = 1
            else:
                opt[key] = 2
    return opt


def preparse_args(argp, subp):
    """Pre-parse the arguments to be able to have a default subparser
    based on the filename provided. """
    opt = get_argparse_options(argp)
    parsers = subp.choices.keys()
    index = 1
    arg = None
    try:
        while sys.argv[index] in opt:
            index += opt[sys.argv[index]]
        if index == 1 and sys.argv[index][0] == '-':
            sys.argv.insert(index, 'view')
            sys.argv.insert(index, '_')
            return
        arg = sys.argv[index]
        _, ext = splitext(arg)
        if ext == '.xcpp':
            default = 'to'
        else:
            default = 'view'
        if arg == 'defaults':
            sys.argv.insert(index, '_')
        if sys.argv[index+1] in parsers:
            return
        if arg not in parsers:
            sys.argv.insert(index+1, default)
    except IndexError:
        if not arg:
            default = 'view'
        if arg not in parsers:
            sys.argv.append(default)
    if arg in parsers:
        sys.argv.insert(index, '_')


def parse_options(mod):
    """Interpret the command line inputs and options. """
    desc = """
This script can perform various commands. Use the help option with a
command for more information.

"""
    ver = "excentury %s" % VERSION
    epi = """
shortcuts:

    excentury file.xcpp lang <==> xcpp fle.xcpp to lang
    excentury file.xc <==> xcpp file.xc view

more info:
  http://excentury.readthedocs.org

version:
  excentury %s

""" % VERSION
    raw = argparse.RawDescriptionHelpFormatter
    argp = argparse.ArgumentParser(formatter_class=raw,
                                   description=textwrap.dedent(desc),
                                   epilog=textwrap.dedent(epi))
    argp.add_argument('-v', '--version', action='version', version=ver)
    argp.add_argument('inputfile', type=str, default='_', nargs='?',
                      help='input file to process').completer = valid_files
    argp.add_argument('--cfg', type=str, default='.',
                      help='configuration file directory')
    subp = argp.add_subparsers(title='subcommands',
                               dest='parser_name',
                               help='additional help',
                               metavar="<command>")

    names = sorted(mod.keys())
    for name in names:
        mod[name].add_parser(subp, raw)
    try:
        argcomplete.autocomplete(argp)
    except NameError:
        pass
    preparse_args(argp, subp)
    return argp.parse_args()


def run():
    """Run excentury from the command line. """
    mod = dict()
    rootpath = split(abspath(__file__))[0]

    mod_names = [name for name in iglob('%s/command/*.py' % rootpath)]
    for name in mod_names:
        tmp_name = split(name)[1][:-3]
        tmp_mod = import_mod('excentury.command.%s' % tmp_name)
        if hasattr(tmp_mod, 'add_parser'):
            mod[tmp_name] = tmp_mod

    arg = parse_options(mod)
    mod[arg.parser_name].run(arg)


if __name__ == '__main__':
    run()
