""" Build

To run this script from the command line do the following:

    python -m build name [options]

this will try to compile the xcpp files. Or call the script located
in $XCROOT/python/bin

    build-cpp name [options]
    build-xcpp name lang [options]

Use the option --help for more information.

"""

import os
import sys
import glob
import optparse

# pylint: disable=R0904
class OptParse(optparse.OptionParser):
    """OptionsParser derived class to be able to overwrite the
    epilog format."""
    def format_epilog(self, formatter):
        """The epilog's format is plain (print all characters)."""
        return self.epilog


def _cpp_parse_options():
    """Function to parse the command line arguments for build-cpp.
    Returns a dictionary of options and a list of arguments. """
    usage = """%prog name [options] """
    desc = """build a c++ program in the excentury project."""
    epi = """
All the c++ source files to be build need to be placed in the
directory 'main/cpp'. To build the file filename.cpp:

    build-cpp filename

You can use the wild card descriptor to do multiple compilation

    build-cpp test*

Sometimes it may be necessary to surround the the filename with
quotes:

    build-cpp '*'

This compiles all files starting with test. Use the tab key after
typing build to see the available source files in main.

You can override the options given to g++ by using the option
`--options`

    build-cpp filename --options '-E -o pure_cpp.cpp'

"""
    parser = OptParse(usage=usage, description=desc, epilog=epi)
    parser.add_option("--options", dest="options",
                      default=None, metavar="OPTIONS",
                      help="Give extra options to g++")
    parser.add_option("--debug", default=None,
                      metavar="DEBUG", dest="debug",
                      help="Turn debug mode on.")
    (options, args) = parser.parse_args()
    if len(args) != 1:
        sys.stderr.write('ERROR: provide the name of a program\n')
        sys.exit(2)
    return {
        'files': glob.glob('%s/main/cpp/%s.cpp' %
                          (os.environ['XCROOT'], args[0])),
        'options': options.options,
        'debug': options.debug,
    }


def _xcpp_parse_options():
    """Function to parse the command line arguments for build-cpp.
    Returns a dictionary of options and a list of arguments. """
    usage = """%prog name [options] """
    desc = """build an xcpp program in the excentury project."""
    epi = """
All the xcpp source files to be build need to be placed in the
directory 'main/xcpp'. To build the file filename.xcpp:

    build-xcpp filename cpp

You can use the wild card descriptor to do multiple compilation

    build-xcpp test* cpp

Sometimes it may be necessary to surround the the filename with
quotes:

    build-xcpp '*' cpp

This compiles all files starting with test. Use the tab key after
typing build to see the available source files in main.

You can provide options given to xcpp by using the option --options.

"""
    parser = OptParse(usage=usage, description=desc, epilog=epi)
    parser.add_option("--options", dest="options",
                      default=None, metavar="OPTIONS",
                      help="Give extra options to g++")
    parser.add_option("--debug", default=None,
                      metavar="DEBUG", dest="debug",
                      help="Turn debug mode on.")
    (options, args) = parser.parse_args()
    if len(args) != 2:
        sys.stderr.write('ERROR: provide the name of a program ' \
                         'and target language\n')
        sys.exit(2)
    return {
        'files': glob.glob('%s/main/xcpp/%s.xcpp' %
                          (os.environ['XCROOT'], args[0])),
        'target': args[1],
        'options': options.options,
        'debug': options.debug,
    }


def run_cpp():
    """Run build-cpp"""
    options = _cpp_parse_options()
    if options['options'] is None:
        opt = '-O3'
    else:
        opt = options['options']
    if options['debug'] is not None:
        opt += ' -DDEBUG=%s' % options['debug']
    root = os.environ['XCROOT']
    for fname in options['files']:
        if options['options'] is None:
            name = os.path.basename(fname)[:-4]
            if options['debug'] is None:
                out = ' -o %s/main/bin/%s.run ' % (root, name)
            else:
                debug = options['debug']
                out = ' -o %s/main/bin/%s.run%s ' % (root, name, debug)
        else:
            out = ' '
        cmd = 'g++ %s%s%s ' % (opt, out, fname)
        print cmd
        os.system(cmd)

def run_xcpp():
    """Run build-xcpp"""
    options = _xcpp_parse_options()
    root = os.environ['XCROOT']
    config_path = '%s/main/xcpp' % root
    for fname in options['files']:
        name = os.path.basename(fname)[:-4]
        out = ''
        if options['debug']:
            out += '--debug %s' % (options['debug'])
        if options['options']:
            out += options['options']
        cmd = 'xcpp %s %s %s --config %s' % (fname, options['target'],
                                             out, config_path)
        print cmd
        os.system(cmd)

if __name__ == '__main__':
    run()
