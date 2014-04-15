"""Config

This module is in charge of providing all the necessary settings to
the rest of the modules in excentury.

"""

import os
import sys
import textwrap
import argparse
from collections import OrderedDict
from excentury.command import error, import_mod

DESC = """Edit a configuration file for excentury.

Some actions performed by excentury can be overwritten by using
configuration files.

To see the values that the configuration file can overwrite use the
`defaults` command. This will print a list of the keys and values
excentury uses for the given command.

"""


class ConfigDispAction(argparse.Action):  # pylint: disable=R0903
    """Derived argparse Action class to use when displaying the
    configuration file and location."""
    def __call__(self, parser, namespace, values, option_string=None):
        try:
            data = read_config(namespace)
        except IOError:
            print 'xcpp.config not found in %r' % namespace.cfg
        else:
            for sec in data:
                sys.stdout.write('[%s]\n' % sec)
                for key in data[sec]:
                    sys.stdout.write('%s = %s\n' % (key, data[sec][key]))
                sys.stdout.write('\n')
        exit(0)


def add_parser(subp, raw):
    "Add a parser to the main subparser. "
    tmpp = subp.add_parser('config', help='configure excentury',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('var', type=str,
                      help='Must be in the form of sec.key')
    tmpp.add_argument('value', type=str, nargs='?', default=None,
                      help='var value')
    tmpp.add_argument('-v', action='store_true',
                      help='print config file location')
    tmpp.add_argument('--display', action=ConfigDispAction,
                      nargs=0,
                      help='print config file and exit')


def _read_config(fname):
    """Simple parser to read configuration files. """
    data = OrderedDict()
    sec = None
    with open(fname, 'r') as fhandle:
        for line in fhandle:
            if line[0] == '[':
                sec = line[1:-2]
                data[sec] = OrderedDict()
            elif '=' in line:
                tmp = line.split('=', 1)
                key = tmp[0].strip()
                val = tmp[1].strip()
                data[sec][key] = val
    return data


def read_config(arg):
    """Read the configuration file xcpp.config"""
    path = arg.cfg
    if path == '.' and not os.path.exists('xcpp.config'):
        if 'XCPP_CONFIG_PATH' in os.environ:
            tmp_path = os.environ['XCPP_CONFIG_PATH']
            if os.path.exists('%s/xcpp.config' % tmp_path):
                path = tmp_path
    elif not os.path.exists('%s/xcpp.config' % path):
        error("ERROR: %s/xcpp.config does not exist\n" % path)
    arg.cfg = path
    try:
        config = _read_config('%s/xcpp.config' % path)
    except IOError:
        config = OrderedDict()
    return config


def write_config(data, arg):
    """Write the configuration file. """
    with open('%s/xcpp.config' % arg.cfg, 'w') as fhandle:
        for sec in data:
            fhandle.write('[%s]\n' % sec)
            for key in data[sec]:
                fhandle.write('%s = %s\n' % (key, data[sec][key]))
            fhandle.write('\n')


def run(arg):
    """Run command. """
    config = read_config(arg)
    try:
        command, var = arg.var.split('.', 1)
    except ValueError:
        error("ERROR: '%s' is not of the form sec.key\n" % arg.var)
    if arg.v:
        print 'path to xcpp.config: "%s"' % arg.cfg
    if arg.value is None:
        try:
            print config[command][var]
        except KeyError:
            pass
        return
    try:
        config[command][var] = arg.value
    except KeyError:
        config[command] = OrderedDict()
        config[command][var] = arg.value
    write_config(config, arg)


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
