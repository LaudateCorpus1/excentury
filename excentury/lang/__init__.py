"""Lang

This module provides functions and parsers that are common for
all languages.

"""

import os
import re
import sys
import textwrap
from excentury.command import error, trace, date, exec_cmd
from excentury.core.load_text import TextParser


# pylint: disable=R0902, R0903
class Function(object):
    """Object to store a function defined in a xcpp file. """
    def __init__(self, name, num):
        self.name = name
        self.num = num
        self.param = None
        self.body = None
        self.ret = None
        self.doc = None
        self.out = None
        self.preamble = ''
        self.epilog = ''


class XCFile(object):
    """Object to store the information of an xcpp file. """
    def __init__(self):
        self.docstring = None
        self.pre_xc = None
        self.preamble = None
        self.function = None
        self.epilog = ''


def split_at(delimiter, text, opens='<(', closes='>)', quotes='"\''):
    """Custom function to split at commas. Taken from stackoverflow
    http://stackoverflow.com/a/20599372/788553"""
    result = []
    buff = ""
    level = 0
    is_quoted = False
    for char in text:
        if char in delimiter and level == 0 and not is_quoted:
            result.append(buff)
            buff = ""
        else:
            buff += char
            if char in opens:
                level += 1
            elif char in closes:
                level -= 1
            elif char in quotes:
                is_quoted = not is_quoted
    if not buff == "":
        result.append(buff)
    return result


def clean_param(par):
    """Returns a dictionary containing the parameter's 'type',
    'name', 'desc', and an optional key 'sample'. """
    param = {'type': par[0], 'desc': par[2][1:-1]}
    index = par[1].find('(')
    if index == -1:
        param['name'] = '`%s`' % par[1]
        param['ctor'] = ''
    else:
        param['name'] = '`%s`' % par[1][:index]
        param['ctor'] = par[1][index:]
    if len(par) > 3:
        param['sample'] = par[3]
    return param


class FileParser(object):
    """Object designed to parse an xcpp file. """

    def __init__(self, fname):
        self.fname = fname
        self.num = 0
        self.text = open(fname, 'r').read()
        self.caret = 0
        self.end = len(self.text)
        self.pos = [1, 1]
        self.tmp = ''
        self.wrapper = textwrap.TextWrapper(width=70,
                                            break_long_words=False)

    def update(self, index):
        """Changes the position of the `caret` and updates `pos`.
        This function assumes that you are moving forward. Do not
        update to an index which is less than the current position of
        the caret. """
        if index == self.caret:
            return
        nlines = self.text.count('\n', self.caret, index)
        self.pos[0] += nlines
        if nlines > 0:
            self.pos[1] = index - self.text.rfind('\n', self.caret, index)
        else:
            self.pos[1] += index - self.caret
        self.caret = index

    def move_caret(self, num):
        """Move the caret num spaces. """
        self.update(self.caret+num)

    def error(self, pos, msg):
        """Exit with a message. """
        name = self.fname
        tmp = 'ERROR in Line %d, Column %d ' \
              'in %s: \n    ' % (pos[0], pos[1], name)
        sys.stderr.write(tmp)
        tmp = re.sub("\\s+", " ", msg)
        sys.stderr.write('\n    '.join(self.wrapper.wrap(tmp)))
        sys.stderr.write('\n\n')
        sys.exit(1)

    def str(self, num):
        """Return num characters from the parser current position. """
        return self.text[self.caret:self.caret+num]

    def find(self, txt, dt_=0):
        """Find the sting txt from the current position plus dt. """
        return self.text.find(txt, self.caret+dt_)

    def get_preamble(self):
        """Read the preamble. To be called right after the docstring.
        """
        if self.text[self.caret:self.caret+3] == '---':
            index = self.find('\n')
            if index == -1:
                index = self.end
            self.update(index+1)
            return ''
        index = self.find('\n---')
        if index == -1:
            msg = 'did not find `\\n---` in xcpp file, this is the ' \
                  'starting point for function definitions\n'
            self.error(self.pos, msg)
        preamble = self.text[self.caret:index+1].strip()
        self.update(index+1)
        index = self.find('\n')
        if index == -1:
            index = self.end
        self.update(index+1)
        if preamble != "":
            preamble += "\n"
        return preamble

    def get_func_preamble(self):
        """Read the function preamble. """
        if self.text[self.caret] == '@':
            return ''
        index = self.find('\n@')
        if index == -1:
            index = self.end
        preamble = self.text[self.caret:index+1].strip()
        self.update(index+1)
        if preamble != "":
            preamble += "\n"
        return preamble

    def _skip_and_update(self):
        """Skip a line. """
        index = self.find('\n')
        if index == -1:
            index = self.end
        self.update(index+1)

    def get_func_epilog(self):
        """Read the function epilog. """
        if self.text[self.caret:self.caret+3] == '---':
            self._skip_and_update()
            return ''
        index = self.find('\n---')
        def_index = self.find('@def{')
        if index == -1:
            if def_index != -1:
                self.error(self.pos, "Missing `---` before `@def`.")
            self.error(self.pos, "Missing `---` for function epilog.")
        elif def_index == -1:
            epilog = self.text[self.caret:index+1].strip()
            self.update(index+1)
            self._skip_and_update()
            self.tmp = self.text[self.caret:self.end].strip()
            self.update(self.end)
            return epilog
        elif def_index < index:
            self.error(self.pos, "`---` must appear before `@def`.")
        epilog = self.text[self.caret:index+1].strip()
        self.update(index+1)
        self._skip_and_update()
        return epilog

    def skip_space(self):
        """Skip white spaces. """
        index = self.caret
        while self.text[index:index+1] in [' ', '\t', '\n']:
            index += 1
        self.update(index)

    def in_between(self, start, end, msg_start, msg_end):
        """Given a string start and string end it returns the
        contents between <start>...<end>. If the current position
        does not begin with start then it raises an error. If
        msg_start is None then the function returns None in case the
        text does not start with start. """
        if self.str(len(start)) != start:
            if msg_start is None:
                return None
            else:
                self.error(self.pos, msg_start)
        self.move_caret(len(start))
        index = self.find(end)
        if index == -1:
            self.error(self.pos, msg_end)
        content = self.text[self.caret:index]
        self.update(index+len(end))
        return content

    def get_function_name(self):
        """Read the name. """
        msg_start = "@def{function_name} expected..."
        msg_end = "Missing '}' while reading name..."
        name = self.in_between('@def{', '}', msg_start, msg_end)
        self.skip_space()
        return name

    def get_docstring(self):
        """Read a documentation string. """
        msg_start = "docstring expected..."
        msg_end = 'Missing \'"""\' while reading docstring...'
        docstring = self.in_between('"""', '"""', msg_start, msg_end)
        self.skip_space()
        return docstring.strip()

    def get_pre_xc(self):
        """Read a block after the docstring that starts with [[ and
        ends with ]]. This is code that will be placed before the
        inclusion of excentury. """
        if self.text[self.caret:self.caret+2] != '[[':
            return ''
        msg_end = "Missing ']]' while reading pre-xc..."
        content = self.in_between('[[', ']]', "", msg_end).strip()
        self.skip_space()
        if content != "":
            content += '\n'
        return content

    def get_params(self):
        """Read a parameter. """
        params = list()
        msg_end = "Missing '}' while reading param..."
        pos = list(self.pos)
        param = self.in_between('@param{', '}', None, msg_end)
        while param is not None:
            self.skip_space()
            par = split_at(',', param)
            if len(par) < 3:
                self.error(pos, "3 arguments expected...")
            params.append(clean_param([ele.strip() for ele in par]))
            pos = list(self.pos)
            param = self.in_between('@param{', '}', None, msg_end)
        return params

    def get_body(self):
        """Read the function body. """
        msg_start = "@body[[ expected..."
        msg_end = "Missing ']]' while body..."
        body = self.in_between('@body[[', ']]', msg_start, msg_end)
        self.skip_space()
        return body

    def get_ret(self):
        """Read the return body. """
        msg_end = "Missing '}' while ret..."
        out = self.in_between('@ret{', '}', None, msg_end)
        msg_end = "Missing ']]' while ret..."
        if out is None:
            msg_start = "@ret[[ expected..."
            ret = self.in_between('@ret[[', ']]', msg_start, msg_end)
            out = 'stdout'
        else:
            msg_start = "[[ expected..."
            ret = self.in_between('[[', ']]', msg_start, msg_end)
        return out, ret

    def get_function(self):
        """Read a function from the file. """
        self.num += 1
        func = Function(self.get_function_name(), self.num)
        func.doc = self.get_docstring()
        func.param = self.get_params()
        func.body = self.get_body()
        func.out, func.ret = self.get_ret()
        return func

    def parse(self):
        """Return the information stored in the xcpp file. """
        xcfile = XCFile()
        xcfile.docstring = self.get_docstring()
        xcfile.pre_xc = self.get_pre_xc()
        xcfile.preamble = self.get_preamble()
        xcfile.function = list()
        while self.caret < self.end:
            preamble = self.get_func_preamble()
            func = self.get_function()
            func.preamble = preamble
            func.epilog = self.get_func_epilog()
            xcfile.function.append(func)
        xcfile.epilog = self.tmp
        return xcfile


def format_input(param):
    """Return a string with all the inputs property formatted. """
    tmp1 = '    {type} {var}{ctor}; XC_LI_.load({var});\n'
    tmp2 = '    {type} {var}{ctor}; XC_LI_.load({var}, {sample});\n'
    inputs = ''
    for par in param:
        if 'sample' in par:
            inputs += tmp2.format(type=par['type'],
                                  var=par['name'][1:-1],
                                  ctor=par['ctor'],
                                  sample=par['sample'])
        else:
            inputs += tmp1.format(type=par['type'],
                                  var=par['name'][1:-1],
                                  ctor=par['ctor'])
    return inputs


def format_return(ret):
    """Given the return statement, replace all instances of @ret with
    XC_DI_. """
    ret = ret.strip()
    res = ''
    caret = 0
    index = ret.find('@ret{', caret)
    while index != -1:
        res += ret[caret:index]
        caret = index + 5
        res += 'XC_DI_.dump('
        index_end = ret.find('}', caret)
        if index == -1:
            index = len(ret)
        args = [ele.strip() for ele in ret[caret:index_end].split(',')]
        if len(args) == 2 and args[1][0] not in ['"', "'"]:
            args.insert(1, '"%s"' % args[0])
        elif len(args) == 1:
            args.append('"%s"' % args[0].strip())
        res += '%s);' % ', '.join(args)
        caret = index_end+1
        index = ret.find('@ret{', caret)
    res += ret[caret:]
    return res


def gen_cmd(cfg, lang, debug=None):
    """Given the configuration dictionary, it generates most of the
    command to compile a cpp program. """
    root = cfg['xcpp']['root']
    cxx = cfg[lang]['cxx']
    opt = '%s ' % cfg[lang]['opt'].strip()
    if debug is None or debug == 0:
        if cfg[lang]['debug'] == '0':
            dbg = ''
        else:
            dbg = '-DDEBUG=%s ' % cfg[lang]['debug']
    else:
        dbg = '-DDEBUG=%d ' % debug
    tmpl = [i if i[0:1] != '/' else os.path.join(root, i)
            for i in cfg[lang].get('cxxinc', '').split(':')]
    inc = ['-I%s/%s' % (root, i) for i in tmpl]
    inc = ' '.join(inc)
    inc = '' if inc == '-I' else '%s ' % inc
    tmpl = [i if i[0:1] != '/' else os.path.join(root, i)
            for i in cfg[lang].get('cxxlib', '').split(':')]
    lib = ['-L%s/%s' % (root, i) for i in tmpl]
    lib = ' '.join(lib)
    lib = '' if lib == '-L' else '%s ' % lib
    return '%s %s%s%s%s' % (cxx, dbg, opt, inc, lib)


def gen_input_file(xcfile, filename):
    """Generate the input file and return the name of the file it
    prints along with a dictionary containing the datatypes it
    contains. """
    funcpre = ''.join([func.preamble for func in xcfile.function])
    cont = """// Temporary file generated on {date} by xcpp.
{pre_xc}#include <excentury/excentury.h>
{preamble}{funcpre}
int main() {{
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
{tmp}    XC_DI_.close();
}}
""".format(date=date(), pre_xc=xcfile.pre_xc, tmp='{XC-INPUTS}',
           preamble=xcfile.preamble, funcpre=funcpre)
    var = dict()
    num = 1
    tmp1 = '    {type} {var}{ctor}; XC_DI_.dump({var}, "{var}");\n'
    tmp2 = '    {type} {var}{ctor}; XC_DI_.dump({var}, "{var}", {sample});\n'
    inputs = ''
    for func in xcfile.function:
        for par in func.param:
            if par['type'] not in var:
                vname = 'var%d_%s' % (num, par['name'][1:-1])
                var[par['type']] = vname
                if 'sample' in par:
                    sample = par['sample'].replace(par['name'][1:-1],
                                                   vname)
                    inputs += tmp2.format(type=par['type'], var=vname,
                                          ctor=par['ctor'],
                                          sample=sample)
                else:
                    inputs += tmp1.format(type=par['type'], var=vname,
                                          ctor=par['ctor'])
                num += 1
    fname = 'inputs-%s.cpp' % filename
    trace('+ writing temporary file %s ... ' % fname)
    with open(fname, 'w') as tmp:
        tmp.write(cont.replace('{XC-INPUTS}', inputs))
    trace('done\n')
    return fname, var


def _make_map(var, fvar):
    """Helper function to collect the input map. """
    info = dict()
    for key, val in var.iteritems():
        for fkey, fval in fvar.iteritems():
            if key == fval:
                info[fkey] = val
                break
    return info


def extract_name(filename):
    """Obtain the name of the file. """
    return os.path.splitext(os.path.basename(filename))[0]


def check_inputs(xcfile, cfg, lang):
    """Make an executable with all the inputs the xcpp file uses
    and make sure that all of them are valid. Return a dictionary
    with the info on all the inputs. """
    fname = cfg['xcpp']['filename']
    fname, fvar = gen_input_file(xcfile, fname)
    cmd = '%s%s ' % (gen_cmd(cfg, lang, 1), fname)
    trace('  - compiling %s ... ' % fname)
    out, err, _ = exec_cmd(cmd)
    if err != '':
        msg = "ERROR: The command\n%s\n\nreturned the following " \
              "error:\n%s" % (str(cmd), str(err))
        error(msg)
    trace('done\n')
    trace('  - running executable ... ')
    out, err, _ = exec_cmd('./a.out')
    if err != '':
        msg = "\nERROR: The command `%s` returned the following " \
              "error:\n%s" % ('./a.out', str(err))
        error(msg)
    trace('done\n')
    var, defs = TextParser(out).parse_info()
    info = _make_map(var, fvar)
    os.remove('a.out')
    os.remove(fname)
    return info, defs


def write_file(in_fname, contents):
    """Helper function to write contents to in_fname. """
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
