"""CPP WRITER for MATHEMATICA

Helper module for writing cpp for communications with mathematica.

"""

import os
from excentury.command import error, trace, exec_cmd, date
from excentury.lang import format_input, format_return, gen_cmd
from excentury.lang import write_file


def m_name(name):
    """Fix names since matlab does not allow _ in names. """
    word = name.split('_')
    last = [w[0:1].upper() + w[1:] for w in word[1:]]
    return '%s%s' % (word[0], ''.join(last))


def _format_param(par, in_map, test):
    """Helper fuction for _inputs. """
    condition = ''
    if test:
        condition = '_'
        if in_map[par['type']][0] in ['c', 'B', 'I', 'N', 'R']:
            condition = '_?NumberQ'
    return '%s%s' % (m_name(par['name'][1:-1]), condition)


def _inputs(param, in_map, test=False):
    """Return a string with all the inputs property formatted. """
    inputs = [_format_param(par, in_map, test) for par in param]
    return ', '.join(inputs)


TM_FUNC = r""":Begin:
:Function: {name}
:Pattern: {name}[{args}]
:Arguments: {{{inputs}}}
:ArgumentTypes: {{Manual}}
:ReturnType: Manual
:End:

"""


def write_tm_file(funcs, cfg, in_map):
    """Write the tm file and compile it with mprep. """
    fname = cfg['xcpp']['filename']
    contents = ':Evaluate: Begin["`Private`"]\n\n'
    for func in funcs:
        contents += TM_FUNC.format(name=m_name(func.name),
                                   args=_inputs(func.param, in_map, True),
                                   inputs=_inputs(func.param, in_map))
    contents += ':Evaluate: End[]\n'
    in_fname = 'tmp-%s.tm' % fname
    trace('+ writing temporary file %s ... ' % in_fname)
    with open(in_fname, 'w') as tmp:
        tmp.write(contents)
    trace('done\n')
    mma = cfg['mathematica']['mlink']
    # MPREP
    cmd = '%s/mprep %s -o %s' % (mma, in_fname, 'tmp-%s.cpp' % fname)
    trace('  - preparing %s ... ' % in_fname)
    _, err, _ = exec_cmd(cmd)
    if err != '':
        msg = "\nERROR: The command\n%s\n\nreturned the following " \
              "error:\n%s" % (str(cmd), str(err))
        error(msg)
    trace('done\n')
    # COMPILE_TM
    cmd = gen_cmd(cfg, 'mathematica', int(cfg['mathematica']['debug']))
    in_fname = 'tmp-%s.cpp' % fname
    out_fname = 'tmp-%s.o' % fname
    cmd = '%s%s -c -I%s -o %s' % (cmd, in_fname, mma, out_fname)
    trace('  - compiling %s ... ' % in_fname)
    _, err, _ = exec_cmd(cmd)
    if err != '':
        msg = "\nERROR: The command\n%s\n\nreturned the following " \
              "error:\n%s" % (str(cmd), str(err))
        error(msg)
    # CLEAN UP
    os.remove('tmp-%s.cpp' % fname)
    os.remove('tmp-%s.tm' % fname)
    trace('done\n')


FUNC = r"""{funcpre}void {name}() {{
    /*{doc}*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
{input}    XC_LI_.close();
{body}
    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    {output}
    XC_DI_.close();
}}{funcepi}
"""


def fmt_func(func):
    """Given a Function object from .xcpp it will create the a valid
    string with the function. """
    fepi = func.epilog
    if fepi != '':
        fepi = '\n' + fepi
    content = FUNC.format(name=m_name(func.name),
                          body=func.body, doc=func.doc,
                          input=format_input(func.param),
                          output=format_return(func.ret),
                          funcpre=func.preamble, funcepi=fepi)
    return content


def write_cpp_code(content, cfg):
    """Helper function for process_function. """
    root = cfg['xcpp']['root']
    cppdir = cfg['mathematica']['dir']
    if cppdir[0] == '/':
        base = cppdir
    else:
        base = '%s/%s' % (root, cppdir)
    filename = cfg['xcpp']['filename']
    in_fname = '%s/%s_mathlink.cpp' % (base, filename)
    trace('+ inspecting %s_mathlink.cpp ... ' % filename)
    write_file(in_fname, content)
    return in_fname


def _get_exec_name(cfg):
    """Helper function to process_function. """
    fname = cfg['xcpp']['filename']
    root = cfg['xcpp']['root']
    mmadir = cfg['mathematica']['mma']
    appdir = cfg['mathematica']['app']
    base = '%s/%s/%s' % (root, mmadir, appdir)
    out_fname = '%s/Bin' % base
    if not os.path.exists(out_fname):
        os.mkdir(out_fname)
    return out_fname + "/%s.so" % fname


FILE = r"""// File generated on {date} by xcpp.
/*{doc}*/
#define XC_MATHEMATICA
#include "mathlink.h"
{pre_xc}
#include <excentury/excentury.h>
{preamble}{functions}
int main(int argc, char* argv[]) {{
    return MLMain(argc, argv);
}}{epilog}
"""


def _compile(fname, mma, in_fname, cfg):
    """Helper function. """
    cmd = gen_cmd(cfg, 'mathematica', int(cfg['mathematica']['debug']))
    cmd = '%s%s -c -I%s -o %s.o' % (cmd, in_fname, mma, fname)
    trace('  - compiling %s ... ' % in_fname)
    _, err, _ = exec_cmd(cmd)
    if err != '':
        msg = "\nERROR: The command\n%s\n\nreturned the following " \
              "error:\n%s" % (str(cmd), str(err))
        error(msg)
    trace('done\n')


def _link(fname, mma, out_fname, cfg):
    """Helper function. """
    cmd = gen_cmd(cfg, 'mathematica', int(cfg['mathematica']['debug']))
    files = '%s.o tmp-%s.o' % (fname, fname)
    extras = '-lMLi3 -lstdc++ -framework Foundation'
    cmd = '%s%s -I%s -L%s %s -o %s' % (cmd, files, mma, mma, extras,
                                       out_fname)
    trace('  - preparing library ... ')
    _, err, _ = exec_cmd(cmd)
    if err != '':
        msg = "\nERROR: The command\n%s\n\nreturned the following " \
              "error:\n%s" % (str(cmd), str(err))
        error(msg)
    os.remove('%s.o' % fname)
    os.remove('tmp-%s.o' % fname)
    trace('done\n')


def write_cpp_file(xcf, cfg, in_map):
    """Writes the cpp file and compiles it. """
    write_tm_file(xcf.function, cfg, in_map)
    fncs = [fmt_func(func) for func in xcf.function]
    epi = xcf.epilog
    if epi != '':
        epi = '\n' + epi
    content = FILE.format(date=date(), preamble=xcf.preamble,
                          doc=xcf.docstring, pre_xc=xcf.pre_xc,
                          functions='\n'.join(fncs), epilog=epi)
    in_fname = write_cpp_code(content, cfg)
    out_fname = _get_exec_name(cfg)
    fname = cfg['xcpp']['filename']
    mma = cfg['mathematica']['mlink']
    # COMPILING CODE
    _compile(fname, mma, in_fname, cfg)
    # LINKING
    _link(fname, mma, out_fname, cfg)
