"""Config

This module is in charge of providing all the necessary settings to
the rest of the modules in excentury.

"""

import os
import textwrap
import configparser
from excentury.command import error, import_mod

DESC = """Edit a configuration file for excentury.

Some actions performed by excentury can be overwritten by using
configuration files.

To see the values that the configuration file can overwrite use the
`defaults` command. This will print a list of the keys and values
excentury uses for the given command.

"""


def add_parser(subp, raw):
    "Add a parser to the main subparser. "
    tmpp = subp.add_parser('config', help='configure excentury',
                           formatter_class=raw,
                           description=textwrap.dedent(DESC))
    tmpp.add_argument('var', type=str,
                      help='Must be in the form of sec.key')
    tmpp.add_argument('value', type=str,  nargs='?', default=None,
                      help='var value')
    tmpp.add_argument('-v', action='store_true',
                      help='print config file location')


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
    config = configparser.ConfigParser(allow_no_value=True)
    config.read('%s/xcpp.config' % path)
    return config


def write_config(config, arg):
    """Write the configuration file. """
    with open('%s/xcpp.config' % arg.cfg, 'w') as cfile:
        config.write(cfile)


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
        config.add_section(command)
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
