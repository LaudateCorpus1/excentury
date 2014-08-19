"""CPP WRITER for MATLAB

Helper module for writing cpp for communications with matlab.

"""

import os
import re
from excentury.command import error, trace, exec_cmd, date
from excentury.lang import format_input, format_return, gen_cmd
from datetime import datetime


def _write_cpp_file(contents, func, cfg):
    """Helper function """
    root = cfg['xcpp']['root']
    cppdir = cfg['matlab']['dir']
    if cppdir[0] == '/':
        base = cppdir
    else:
        base = '%s/%s' % (root, cppdir)
    filename = cfg['xcpp']['filename']
    in_fname = '%s/%s-%s_mex.cpp' % (base, filename, func.name)
    msg = '[%d] inspecting %s-%s_mex.cpp ... '
    trace(msg % (func.num, filename, func.name))
    make_new = True
    if os.path.exists(in_fname):
        tmp = open(in_fname, 'r').read()
        if tmp[tmp.find('\n'):] == contents[contents.find('\n'):]:
            make_new = False
    if make_new:
        with open(in_fname, 'w') as tmp:
            tmp.write(contents)
        trace('[NEW CONTENT]\n')
    else:
        trace('[NO CHANGE]\n')
    return in_fname


def _compile_cpp_file(in_fname, func, cfg):
    """Helper function """
    out_fname = '%s/%s_mex' % (cfg['matlab']['pkg'], func.name)
    mexbin, _, _ = exec_cmd('mexext')
    mexbin = '%s.%s' % (out_fname, mexbin.strip())
    force = cfg['matlab']['force']
    epilog = cfg['matlab']['epilog']
    verbose = cfg['matlab']['verbose']
    make_new = True
    if isinstance(force, list) and (len(force) == 0 or func.num in force):
        pass
    elif force in ['True', 'true']:
        pass
    elif os.path.exists(mexbin):
        date_in = datetime.fromtimestamp(os.path.getmtime(in_fname))
        date_out = datetime.fromtimestamp(os.path.getmtime(mexbin))
        if date_in < date_out:
            make_new = False
            trace('  - skipping compilation\n')
    if make_new:
        cmd = gen_cmd(cfg, 'matlab', int(cfg['matlab']['debug']))
        cmd = '%s%s -output %s %s' % (cmd, in_fname, out_fname, epilog)
        trace('  - compiling %s ... ' % in_fname)
        if verbose is True or verbose in ['true', 'True']:
            cmd += ' -v'
            trace('\n    * command:\n    %s\n    * ' % str(cmd))
            exec_cmd(cmd, True)
        else:
            _, err, _ = exec_cmd(cmd)
            if err == '':
                pass
            elif (len(err.strip().split('\n')) > 1 or
                  re.match('Configured with:.*?\n', err) is None):
                msg = "\nERROR: The command\n%s\n\nreturned the following " \
                      "error:\n%s" % (str(cmd), str(err))
                error(msg)
        trace('done\n')


FILE = """// File generated on {date} by xcpp.
#define XC_MATLAB
{preamble}{funcpre}void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::S{load}Interface<excentury::load_mode> XC_LI_(pcin_, ncin_);
{inputs}    XC_LI_.close();
{body}
    excentury::S{dump}Interface<excentury::dump_mode> XC_DI_;
    {outputs}
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}}{funcepi}{epilog}
"""


def write_cpp_function(xcf, func, cfg):
    """Writes the cpp file and compiles it. """
    fepi = func.epilog
    if fepi != '':
        fepi = '\n' + fepi
    if xcf.epilog != '':
        fepi += '\n'
    content = FILE.format(date=date(),
                          preamble=xcf.preamble,
                          load=cfg['matlab']['load'].capitalize(),
                          inputs=format_input(func.param),
                          body=func.body, funcpre=func.preamble,
                          dump=cfg['matlab']['dump'].capitalize(),
                          outputs=format_return(func.ret),
                          funcepi=fepi, epilog=xcf.epilog)
    in_fname = _write_cpp_file(content, func, cfg)
    _compile_cpp_file(in_fname, func, cfg)
