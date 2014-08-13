"""PYTHON WRAPPER

Helper module for writing python wrappers for communications with
python.

"""

from excentury.command import trace, date
from excentury.lang import write_file


def _format_help(func):
    """Generate the help string for python functions. """
    msg = func.doc
    if func.param:
        msg += '\n\n    parameters:\n\n'
        tmp = '      {0}: {1}\n'
        for par in func.param:
            msg += tmp.format(par['name'], par['desc'])
        msg += '    '
    else:
        msg += '\n    '
    return msg


def _inputs(param):
    """Return a string with all the inputs property formatted. """
    if not param:
        return ''
    return '%s, ' % ', '.join([par['name'][1:-1] for par in param])


def _format_input(param, in_map):
    """Return a string with all the inputs property formatted. """
    inputs = ''
    tmp = '    tdump.dump({name}, "{name}", {sample})\n'
    for par in param:
        var_name = par['name'][1:-1]
        sample = str(in_map[par['type']])
        inputs += tmp.format(name=var_name, sample=sample)
    return inputs


PY_FUNC = """
LIB.{name}_py.restype = None
LIB.{name}_py_clear.restype = None
def {name}({arg}unpack=True):
    \"\"\"{doc}\"\"\"
    tdump = {dump}Dumper()
{inputs}    in_str = tdump.close()
    len_in = len(in_str)
    out_str = ctypes.POINTER(c_char)()
    len_out = c_size_t(0)
    LIB.{name}_py(c_size_t(len_in),
{space}c_char_p(in_str),
{space}ctypes.byref(len_out),
{space}ctypes.byref(out_str))
    if out_str[:1] == 'E':
        xc_error_msg = out_str[1:len_out.value]
        raise RuntimeError(xc_error_msg)
    val = {load}Parser(out_str[:len_out.value]).parse()
    LIB.{name}_py_clear()
    if unpack:
        if val:
            return val.values()[0] if len(val) == 1 else val.values()
        return None
    else:
        return val

"""


def _fm_py_func(func, cfg, in_map):
    """Given a Function object from .xcpp it will create the a valid
    string with the python function. """
    return PY_FUNC.format(name=func.name, arg=_inputs(func.param),
                          doc=_format_help(func),
                          dump=cfg['python']['dump'].capitalize(),
                          inputs=_format_input(func.param, in_map),
                          space=' '*(len(func.name)+12),
                          load=cfg['python']['load'].capitalize())


def _write_py_file(contents, cfg):
    """Helper function for process_function. """
    root = cfg['xcpp']['root']
    dest_dir = cfg['python']['wrapper']
    if dest_dir[0] == '/':
        base = dest_dir
    else:
        base = '%s/%s' % (root, dest_dir)
    filename = cfg['xcpp']['filename']
    in_fname = '%s/%s.py' % (base, filename)
    trace('+ inspecting %s.py ... ' % filename)
    write_file(in_fname, contents)
    return in_fname


def _format_defs(defs):
    """Write a dictionary with all the definitions used in the
    module. """
    ans = 'DEFS = {\n'
    for key in defs:
        ans += "'%s': [\n" % key
        for item in defs[key]:
            ans += '    %s,\n' % repr(item)
        ans += '],\n'
    ans += '}'
    return ans

PY_FILE = """# File generated on {date} by xcpp.
\"""{doc}\"""
from excentury import {load}Parser, {dump}Dumper, XCStruct
from ctypes import c_char, c_size_t, c_char_p
import ctypes

LIB = ctypes.cdll.LoadLibrary("{mod}_pylib.so")

{defs}
def xc_struct(name):
    \"""Return an XCStruct object using the entries of the dictionary
    DEFS in this module.\"""
    return XCStruct(name, DEFS[name])

{body}
"""


def write_python_file(xcf, cfg, in_map, defs):
    """Writes the py file. """
    body = ''.join([_fm_py_func(func, cfg, in_map) for func in xcf.function])
    content = PY_FILE.format(date=date(), doc=xcf.docstring,
                             load=cfg['python']['load'].capitalize(),
                             dump=cfg['python']['dump'].capitalize(),
                             mod=cfg['xcpp']['filename'],
                             defs=_format_defs(defs),
                             body=body)
    _write_py_file(content, cfg)
