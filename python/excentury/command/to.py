"""To

Converts an xcpp file to a c++ file that will be compatible with
the language specifed.

"""

import os
import textwrap
import argparse
from excentury.command import error, import_mod
from excentury.command.config import get_cfg

DESC = """
Converts and builds an xcpp file to a c++ file that will be
compatible with the language specifed.

"""


EPI = """
To see the default values for each of the optional arguments
use the command `defaults` with the positional argument `%s`

"""


def get_lang_names():
    """Obtains the names of the languages available. """
    dirpath = os.path.split(os.path.abspath(__file__))[0]
    dirpath += '/../lang'
    lang_names = [name for name in os.listdir(dirpath)
                  if os.path.isdir(os.path.join(dirpath, name))]
    return lang_names


def add_parser(subp, raw):
    "Add a parser to the main subparser. "
    lang_names = get_lang_names()
    tmpp = subp.add_parser('to', help='convert xcpp file',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('lang', type=str, metavar='lang',
                      choices=lang_names,
                      help='target language: ' + ', '.join(lang_names))
    tmpp.add_argument('options', nargs=argparse.REMAINDER,
                      help='language options')


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
    mod = import_mod('excentury.lang.%s' % arg.lang)
    usage = 'xcpp inputfile [to] %s [optional argument]' % arg.lang
    raw = argparse.RawDescriptionHelpFormatter
    argp = argparse.ArgumentParser(formatter_class=raw,
                                   usage=usage,
                                   description=textwrap.dedent(mod.DESC),
                                   epilog=textwrap.dedent(EPI % arg.lang))
    mod.add_options(argp)
    argp.parse_args(arg.options, arg)
    filename = _get_filename(arg)
    mod.process_file(arg, filename)
