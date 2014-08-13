"""AUX CPP

Auxilary file for the cpp converter.

"""

import os
from excentury.command import error, trace, exec_cmd, date
from excentury.lang import format_input, format_return, gen_cmd
from excentury.lang import write_file
from datetime import datetime

TEMPLATE = """// File generated on {date} by xcpp.
{pre_xc}#include <excentury/excentury.h>
#include <excentury/hook/cpp.h>
{preamble}{funcpre}void xc_help() {{
    fprintf(stderr,
{help});
}}
void xc_input() {{
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
{param}    XC_DI_.close();
}}
int main(int argc, char** argv) {{
    /*{doc}*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::S{load}Interface<excentury::load_mode> XC_LI_(argv[1]);
{input}    XC_LI_.close();
{body}
    excentury::{dump}Interface<excentury::dump_mode> XC_DI_({out});
    {output}
    XC_DI_.close();
}}
{funcepi}{epilog}
"""


def _format_help(func, fname):
    """Generate the help string. """
    msg = '    "program: %s-%s\\n"\n' % (fname, func.name)
    msg += '    "\\ndescription:\\n"\n    "    '
    msg += '\\n"\n    "'.join(func.doc.split('\n'))
    if func.param:
        msg += '\\n"\n    "\\nparameters:\\n"\n'
        tmp = '    "    {0}: {1}\\n"\n'
        for par in func.param:
            msg += tmp.format(par['name'], par['desc'])
        msg += '    "\\n"'
    else:
        msg += '\\n"\n    "\\n"'
    return msg


def _format_input(param):
    """Return a string with all the inputs property formatted. """
    inputs = ''
    for par in param:
        tmp = '    {type} {var}{ctor}; XC_DI_.dump({var}, "{var}"'
        if 'sample' in par:
            tmp += ', %s);\n' % par['sample']
        else:
            tmp += ');\n'
        inputs += tmp.format(type=par['type'], var=par['name'][1:-1],
                             ctor=par['ctor'])
    return inputs


def _write_file(contents, func, cfg):
    """Helper function for process_function. """
    root = cfg['xcpp']['root']
    cppdir = cfg['cpp']['dir']
    if cppdir[0] == '/' or cppdir == '.':
        base = cppdir
    else:
        base = '%s/%s' % (root, cppdir)
    filename = cfg['xcpp']['filename']
    in_fname = '%s/%s-%s.cpp' % (base, filename, func.name)
    msg = '[%d] inspecting %s-%s.cpp ... '
    trace(msg % (func.num, filename, func.name))
    write_file(in_fname, contents)
    return in_fname


def _get_exec_name(func, cfg):
    """Helper function to process_function. """
    filename = cfg['xcpp']['filename']
    root = cfg['xcpp']['root']
    bindir = cfg['cpp']['bin']
    if bindir[0] == '/' or bindir == '.':
        base = bindir
    else:
        base = '%s/%s' % (root, bindir)
    dbg = cfg['cpp']['debug'] if cfg['cpp']['debug'] != '0' else ''
    ext = cfg['cpp']['ext']
    if ext == '':
        out_fname = '%s/%s-%s%s' % (base, filename, func.name, dbg)
    else:
        out_fname = '%s/%s-%s.%s%s' % (base, filename, func.name, ext, dbg)
    return out_fname


def process_function(xcf, cfg, func):
    """Given a Function object from .xcpp it will create the contents
    of a valid cpp file that can be compiled for a valid executable.
    """
    in_fname = cfg['xcpp']['filename']
    epilog = func.epilog
    if epilog != '':
        epilog += '\n'
    contents = TEMPLATE.format(date=date(), pre_xc=xcf.pre_xc,
                               preamble=xcf.preamble,
                               help=_format_help(func, in_fname),
                               param=_format_input(func.param),
                               doc=func.doc, body=func.body,
                               load=cfg['cpp']['load'].capitalize(),
                               dump=cfg['cpp']['dump'].capitalize(),
                               input=format_input(func.param),
                               output=format_return(func.ret),
                               out=func.out, funcpre=func.preamble,
                               funcepi=epilog, epilog=xcf.epilog)
    in_fname = _write_file(contents, func, cfg)
    out_fname = _get_exec_name(func, cfg)
    force = cfg['cpp']['force']
    make_new = True
    if isinstance(force, list) and (len(force) == 0 or func.num in force):
        pass
    elif force in ['True', 'true']:
        pass
    elif os.path.exists(out_fname):
        date_in = datetime.fromtimestamp(os.path.getmtime(in_fname))
        date_out = datetime.fromtimestamp(os.path.getmtime(out_fname))
        if date_in < date_out:
            make_new = False
            trace('  - skipping compilation\n')
    if make_new:
        cmd = gen_cmd(cfg, 'cpp', int(cfg['cpp']['debug']))
        cmd = '%s%s -o %s' % (cmd, in_fname, out_fname)
        trace('  - compiling %s ... ' % in_fname)
        _, err, _ = exec_cmd(cmd)
        if err != '':
            msg = "\nERROR: The command\n%s\n\nreturned the following " \
                  "error:\n%s" % (str(cmd), str(err))
            error(msg)
        trace('done\n')
