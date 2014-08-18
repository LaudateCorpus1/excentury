"""CPP WRITER for PYTHON

Helper module for writing cpp for communications with python.

"""

from excentury.command import error, trace, exec_cmd, date
from excentury.lang import format_input, format_return, gen_cmd
from excentury.lang import write_file


FUNC = """
{funcpre}std::string {name}_py_str;
void {name}_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {{
try {{
    excentury::S{load}Interface<excentury::load_mode> XC_LI_(pcin, ncin);
{inputs}    XC_LI_.close();
{body}
    excentury::S{dump}Interface<excentury::dump_mode> XC_DI_;
    {outputs}
    XC_DI_.close();
    {name}_py_str = XC_DI_.str();
    ncout = {name}_py_str.size();
    pcout = (char*){name}_py_str.data();
}} catch (excentury::RuntimeError& run_error) {{
    {name}_py_str = run_error.msg;
    ncout = {name}_py_str.size();
    pcout = (char*){name}_py_str.data();
}}
}}
void {name}_py_clear() {{
    {name}_py_str.clear();
}}
{funcepi}"""


def _fmt_func(func, cfg):
    """Given a Function object from .xcpp it will create the a valid
    string with the function. """
    epilog = func.epilog
    if epilog != '':
        epilog += '\n'
    return FUNC.format(name=func.name,
                       load=cfg['python']['load'].capitalize(),
                       inputs=format_input(func.param),
                       body=func.body,
                       dump=cfg['python']['dump'].capitalize(),
                       outputs=format_return(func.ret),
                       funcpre=func.preamble, funcepi=epilog)


def _write_cpp_file(contents, cfg):
    """Helper function. """
    root = cfg['xcpp']['root']
    cppdir = cfg['python']['dir']
    if cppdir[0] == '/':
        base = cppdir
    else:
        base = '%s/%s' % (root, cppdir)
    filename = cfg['xcpp']['filename']
    in_fname = '%s/%s_pylib.cpp' % (base, filename)
    trace('+ inspecting %s_pylib.cpp ... ' % filename)
    write_file(in_fname, contents)
    return in_fname


def _get_exec_name(cfg):
    """Helper function to process_function. """
    filename = cfg['xcpp']['filename']
    root = cfg['xcpp']['root']
    libdir = cfg['python']['lib']
    if libdir[0] == '/':
        base = libdir
    else:
        base = '%s/%s' % (root, libdir)
    out_fname = '%s/%s_pylib.so' % (base, filename)
    return out_fname


def _compile_cpp_file(in_fname, cfg):
    """Helper function. """
    out_fname = _get_exec_name(cfg)
    epilog = cfg['python']['epilog']
    verbose = cfg['python']['verbose']
    cmd = gen_cmd(cfg, 'python', int(cfg['python']['debug']))
    cmd = '%s --shared -fPIC %s -o %s %s' % (cmd, in_fname,
                                             out_fname, epilog)
    trace('  - compiling %s ... ' % in_fname)
    if verbose is True or verbose in ['true', 'True']:
        trace('\n    * command:\n    %s\n    * ' % str(cmd))
    _, err, _ = exec_cmd(cmd)
    if err != '':
        msg = "\nERROR: The command\n%s\n\nreturned the following " \
              "error:\n%s" % (str(cmd), str(err))
        error(msg)
    trace('done\n')

FILE = """// File generated on {date} by xcpp.
/*{doc}*/
#define XC_PYTHON
{preamble}
extern "C" {{
{extern}
}}
{body}{epilog}
"""


def write_cpp_file(xcf, cfg):
    """Writes the cpp file and compiles it. """
    tmp = '    void {name}_py(size_t, char*, size_t&, char*&);\n' \
          '    void {name}_py_clear();\n'
    extern = ''.join([tmp.format(name=func.name) for func in xcf.function])
    body = ''.join([_fmt_func(func, cfg) for func in xcf.function])
    epilog = xcf.epilog
    if epilog != '':
        epilog = '\n' + epilog
    content = FILE.format(date=date(), doc=xcf.docstring,
                          pre_xc=xcf.pre_xc, preamble=xcf.preamble,
                          extern=extern, body=body, epilog=epilog)
    in_fname = _write_cpp_file(content, cfg)
    _compile_cpp_file(in_fname, cfg)
