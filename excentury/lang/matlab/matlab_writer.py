"""MATLAB WRAPPER

Helper module for writing matlab wrappers for communications with
matlab.

"""

from excentury.command import trace, date
from excentury.lang import write_file


def _format_help(func, pkg):
    """Generate the help string for matlab functions. """
    msg = '%% %s.%s generated on %s by xcpp\n\n    %s'
    msg = msg % (pkg, func.name.upper(), date(), func.doc)
    if func.param:
        msg += '\n\n    parameters:\n\n'
    tmp = '      {0}: {1}\n'
    for par in func.param:
        msg += tmp.format(par['name'], par['desc'])
    msg += '    '
    msg = msg.split('\n')
    msg = '\n% '.join(msg)
    return msg


def _args(param):
    """Return a string with all the inputs property formatted. """
    if not param:
        return ''
    return '%s, ' % ', '.join([par['name'][1:-1] for par in param])


def _format_input(param, in_map):
    """Return a string with all the inputs property formatted. """
    inputs = ''
    tmp = "    tdump.dump({var}, '{var}', {info});\n"
    for par in param:
        var_name = par['name'][1:-1]
        info = str(in_map[par['type']]).replace('[', '{')
        info = info.replace(']', '}')
        inputs += tmp.format(var=var_name, info=info)
    return inputs


M_FILE = """{doc}
function varargout = {name}({args}varargin)
    tdump = excentury.dump.{dump}dumper;
{inputs}    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = {pkg}.{name}_mex(len_in, in_str);
    [val, order] = excentury.load.{load}parser(out_str).parse;
    if isempty(varargin)
        nout = length(order);
        varargout = cell(1, nout);
        for num=1:nout;
            varargout{{num}} = val(order{{num}});
        end
    else
        varargout{{1}} = val;
    end
end
"""


def write_matlab_file(func, cfg, in_map):
    """Writes the m file. """
    pkg = cfg['xcpp']['filename']
    content = M_FILE.format(doc=_format_help(func, pkg), pkg=pkg,
                            name=func.name, args=_args(func.param),
                            load=cfg['matlab']['load'],
                            dump=cfg['matlab']['dump'],
                            inputs=_format_input(func.param, in_map))
    base = cfg['matlab']['pkg']
    pkg = cfg['xcpp']['filename']
    in_fname = '%s/%s.m' % (base, func.name)
    trace('  + inspecting +%s/%s.m ... ' % (pkg, func.name))
    write_file(in_fname, content)


def _format_defs(defs):
    """Write a dictionary with all the definitions used in the
    module. """
    msg = ''
    for key in defs:
        msg += "defs('%s') = { ...\n" % key
        for item in defs[key]:
            tmp = repr(item).replace('[', '{')
            tmp = tmp.replace(']', '}')
            msg += '            %s, ...\n' % tmp
        msg += '        };\n'
    return msg


DEF_FILE = """%% %s.XC_DEF was generated on %s by xcpp
%%
%% Provides the definition of the objects that the functions in
%% this package return. Provide no arguments to obtain the whole
%% map. If you need only one definition then provide the key.
%%
function obj = xc_def(varargin)
    persistent defs;
    if isempty(defs)
        defs = containers.Map;
        %s    end
    if isempty(varargin)
        obj = defs;
    else
        obj = defs(varargin{1});
    end
end
"""


XC_STRUCT_FILE = """% {pkg}.XC_STRUCT was generated on {date} by xcpp
%
% Return an excentury.xc_strut object using the entries of the
% containers.Map provided by this package ({pkg}.xc_def).
%
% The following are equivalent:
%
%     p = excentury.xc_struct('classname', {pkg}.xc_def('classname'));
%
%     p = {pkg}.xc_struct('classname');
%
% {inputs}
%
function obj = xc_struct(name)
    obj = excentury.xc_struct(name, {pkg}.xc_def(name));
end

"""


def write_matlab_defs(cfg, defs):
    """Write a file containing the definition used in the package. """
    contents = DEF_FILE % (cfg['xcpp']['filename'], date(),
                           _format_defs(defs))
    base = cfg['matlab']['pkg']
    pkg = cfg['xcpp']['filename']
    in_fname = '%s/xc_def.m' % base
    trace('* inspecting +%s/xc_def.m ... ' % pkg)
    write_file(in_fname, contents)
    if defs.keys():
        inputs = 'The posible inputs are: \n%%\n%%    %s'
        inputs = inputs % '\n%%    '.join(defs.keys())
    else:
        inputs = ''
    contents = XC_STRUCT_FILE.format(pkg=pkg, date=date(), inputs=inputs)
    in_fname = '%s/xc_struct.m' % base
    trace('* inspecting +%s/xc_struct.m ... ' % pkg)
    write_file(in_fname, contents)
