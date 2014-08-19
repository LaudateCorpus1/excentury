"""Config

This module is in charge of providing all the necessary settings to
the rest of the modules in excentury.

"""

import os
import re
import sys
import textwrap
import argparse
from collections import OrderedDict
from excentury.command import error, trace, import_mod

DESC = """Edit a configuration file for excentury.

Some actions performed by excentury can be overwritten by using
configuration files.

To see the values that the configuration file can overwrite use the
`defaults` command. This will print a list of the keys and values
excentury uses for the given command.

"""

RE = re.compile(r'\${(?P<key>.*?)}')
RE_IF = re.compile(
    r'(?P<iftrue>.*?) IF\[\[(?P<cond>.*?)\]\]'
)
RE_IFELSE = re.compile(
    r'(?P<iftrue>.*?) IF\[\[(?P<cond>.*?)\]\]ELSE (?P<iffalse>.*)'
)


def disp(msg):
    """Wrapper around sys.stdout.write which is meant to behave as
    the print function but it does not add the newline character. """
    sys.stdout.write(msg)


def _replacer(*key_val):
    """Helper function for replace.

    Source: <http://stackoverflow.com/a/15221068/788553>
    """
    replace_dict = dict(key_val)
    replacement_function = lambda match: replace_dict[match.group(0)]
    pattern = re.compile("|".join([re.escape(k) for k, _ in key_val]), re.M)
    return lambda string: pattern.sub(replacement_function, string)


def replace(string, *key_val):
    """Replacement of strings done in one pass. Example:

        >>> replace("a < b && b < c", ('<', '&lt;'), ('&', '&amp;'))
        'a &lt; b &amp;&amp; b &lt; c'

    Source: <http://stackoverflow.com/a/15221068/788553>

    """
    return _replacer(*key_val)(string)


class ConfigDispAction(argparse.Action):  # pylint: disable=R0903
    """Derived argparse Action class to use when displaying the
    configuration file and location."""
    def __call__(self, parser, namespace, values, option_string=None):
        try:
            read_config(namespace)
        except IOError:
            disp('xcpp.config not found in %r\n' % namespace.cfg)
        else:
            disp('path to xcpp.config: "%s"\n' % namespace.cfg)
            with open('%s/xcpp.config' % namespace.cfg, 'r') as _fp:
                disp(_fp.read())
        exit(0)


def add_parser(subp, raw):
    "Add a parser to the main subparser. "
    tmpp = subp.add_parser('config', help='configure excentury',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('var', type=str, nargs='?', default=None,
                      help='Must be in the form of sec.key')
    tmpp.add_argument('-v', action='store_true',
                      help='print config file location')
    tmpp.add_argument('--print', action=ConfigDispAction,
                      nargs=0,
                      help='print config file and exit')


def _get_replacements(tokens, data, sec):
    """Helper function for _read_config. """
    replacements = list()
    for token in tokens:
        if ':' in token:
            tsec, tkey = token.split(':')
            tval = ''
            if tsec in data:
                if tkey in data[tsec]:
                    tval = data[tsec][tkey]
        else:
            if token in data[sec]:
                tval = data[sec][token]
        replacements.append(
            ('${%s}' % token, tval)
        )
    return replacements


# pylint: disable=invalid-name
# ARG and CFG are names that may be used in the configuration file.
# ARG gives us access to the command line arguments and CFG gives us
# access to the current configuration. Note that using CFG[key][sec]
# is equivalent to ${key:sec}. These names go against the convention
# so that they may be easy to spot in a configuration file.
def _eval_condition(cond, ARG, CFG, line_num, fname):
    """Evaluates a string using the eval function. It prints a
    warning if there are any errors. Returns the result of the
    evaluation and an error number: 0 if everything is fine, 1 if
    there was an error. """
    ARG.FILEPATH = '%s/%s/%s' % (ARG.cfg, CFG['xcpp']['path'], ARG.inputfile)
    try:
        # pylint: disable=eval-used
        # To be able to evaluate a condition without creating a whole
        # new parser we can use the eval function. We could have use
        # a python file as a configuration but then there would be
        # no simple structure to the files.
        cond = eval(cond)
        enum = 0
        # pylint: disable=broad-except
        # Anything can go wrong during the execution of the `eval`
        # function. For this reason we must try to catch anything that
        # may come our way so that we may give out a warning message
        # and ignore it.
    except Exception as exception:
        cond = None
        enum = 1
        trace(
            'WARNING: error in line %d of %r: %s\n' % (
                line_num, fname, exception.message
            )
        )
    return cond, enum


def _read_config(fname, arg):
    """Simple parser to read configuration files. """
    data = OrderedDict()
    sec = None
    line_num = 0
    with open(fname, 'r') as fhandle:
        for line in fhandle:
            line_num += 1
            if line[0] == '[':
                sec = line[1:-2]
                data[sec] = OrderedDict()
            elif '=' in line:
                tmp = line.split('=', 1)
                key = tmp[0].strip()
                val = tmp[1].strip()
                val = os.path.expandvars(val)
                replacements = _get_replacements(
                    RE.findall(val), data, sec
                )
                # pylint: disable=star-args
                if replacements:
                    val = replace(val, *replacements)
                match = RE_IFELSE.match(val)
                if match:
                    cond, enum = _eval_condition(
                        match.group('cond'), arg, data, line_num, fname
                    )
                    if enum == 1:
                        continue
                    groups = match.groups()
                    val = groups[0] if cond else groups[2]
                else:
                    match = RE_IF.match(val)
                    if match:
                        cond, enum = _eval_condition(
                            match.group('cond'), arg, data, line_num, fname
                        )
                        if enum == 1:
                            continue
                        if cond:
                            val = match.group('iftrue')
                        else:
                            continue
                data[sec][key] = val
    return data


def read_config(arg):
    """Read the configuration file xcpp.config"""
    path = arg.cfg
    if path == '.' and not os.path.exists('xcpp.config'):
        if 'XCPP_CONFIG_PATH' in os.environ:
            tmp_path = os.environ['XCPP_CONFIG_PATH']
            if os.path.exists('%s/xcpp.config' % tmp_path):
                trace("Configured with: '%s/xcpp.config'\n" % tmp_path)
                path = tmp_path
    elif not os.path.exists('%s/xcpp.config' % path):
        error("ERROR: %s/xcpp.config does not exist\n" % path)
    arg.cfg = path
    try:
        config = _read_config('%s/xcpp.config' % path, arg)
    except IOError:
        config = OrderedDict()
    return config


def run(arg):
    """Run command. """
    config = read_config(arg)
    if arg.v:
        disp('path to xcpp.config: "%s"\n' % arg.cfg)
    if arg.var is None:
        for sec in config:
            disp('[%s]\n' % sec)
            for key in config[sec]:
                disp('  %s = %s\n' % (key, config[sec][key]))
            disp('\n')
        return
    try:
        command, var = arg.var.split('.', 1)
    except ValueError:
        error("ERROR: '%s' is not of the form sec.key\n" % arg.var)
    try:
        disp(config[command][var]+'\n')
    except KeyError:
        pass
    return


def _update_single(cfg, name, defaults=None):
    "Helper function for get_cfg."
    if defaults:
        for var, val in defaults.iteritems():
            cfg[name][var] = os.path.expandvars(str(val))
    else:
        mod = import_mod('excentury.command.%s' % name)
        if hasattr(mod, "DEFAULTS"):
            for var, val in mod.DEFAULTS.iteritems():
                cfg[name][var] = os.path.expandvars(val)


def _update_from_file(cfg, name, cfg_file):
    "Helper function for get_cfg."
    if name in cfg_file:
        for var, val in cfg_file[name].iteritems():
            cfg[name][var] = os.path.expandvars(val)


def _update_from_arg(cfg, argdict, key):
    "Helper function for get_cfg."
    for var in cfg[key]:
        if var in argdict and argdict[var] is not None:
            cfg[key][var] = argdict[var]


def get_cfg(arg, names, defaults=None):
    """Obtain the settings for a command. """
    cfg = {
        'xcpp': {
            'root': '.',
            'path': '.'
        }
    }
    cfg_file = read_config(arg)
    if 'xcpp' in cfg_file:
        for var, val in cfg_file['xcpp'].iteritems():
            cfg['xcpp'][var] = os.path.expandvars(val)
    cfg['xcpp']['root'] = arg.cfg
    if isinstance(names, list):
        for name in names:
            cfg[name] = dict()
            _update_single(cfg, name)
            _update_from_file(cfg, name, cfg_file)
    else:
        if names != 'xcpp':
            cfg[names] = dict()
            _update_single(cfg, names, defaults)
            _update_from_file(cfg, names, cfg_file)
    argdict = vars(arg)
    if arg.parser_name in cfg:
        _update_from_arg(cfg, argdict, arg.parser_name)
    elif arg.parser_name == 'to' and arg.lang in cfg:
        _update_from_arg(cfg, argdict, arg.lang)
    _update_from_arg(cfg, argdict, 'xcpp')
    return cfg
