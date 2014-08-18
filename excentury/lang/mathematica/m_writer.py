"""MATHEMATICA M FILE

Writes the mathematica package.

"""

import re
from excentury.command import trace, date
from excentury.lang import write_file


# pylint: disable=W0142
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


def m_name(name):
    """Fix names since matlab does not allow _ in names. """
    word = name.split('_')
    last = [w[0:1].upper() + w[1:] for w in word[1:]]
    return '%s%s' % (word[0], ''.join(last))


def _format_help(func, cfg):
    """Generate the help string for python functions. """
    fname = m_name(func.name)
    msg = '{0}::usage = `Developer`USAGE["{0}[{1}] \\n\\\n\\t'
    msg = msg.format(fname, ', '.join([par['name'] for par in func.param]))
    tmp = func.doc.replace('    ', '\\t').split('\n')
    msg += '\\n\\\n'.join(tmp)
    link = '`Developer`LINK["paclet:%s"]' % cfg['xcpp']['filename']
    num = '`%d`' % (len(func.param)+1)
    if func.param:
        map_ = [(par['name'], '`%d`' % (num+1))
                for num, par in enumerate(func.param)]
        msg += '\\n\\\n\\t\\tparameters:\\n\\\n'
        for par in func.param:
            msg += '\\t\\t%s: %s\\n\\\n' % (par['name'], par['desc'])
        msg = replace(msg, *map_)
        tmp = '`Developer`EMPH["%s"]'
        args = ',\n   '.join([tmp % par['name'][1:-1] for par in func.param])
        msg += '",\n   %s,\n   %s\n];' % (args, link)
    else:
        msg += '", %s];' % link
    #msg += 'More info %s",\n   %s,\n   %s]' % ('`%d`' % num, args, link)
    return msg


def _format_error(func, cfg):
    """Helper function. """
    msg = '{name}[args___] := (Message[{pkg}::argerr]; $Failed)'
    return msg.format(name=m_name(func.name),
                      pkg=cfg['xcpp']['filename'])


M_FILE = r"""(* File generated on {date} by xcpp *)

BeginPackage["{app}`{pkgname}`"];
Unprotect[
    {funcnames}
];
ClearAll[
    {funcnames}
];

Begin["`Developer`"]
$AppDir = DirectoryName@$InputFileName;
$BinDir = FileNameJoin[{{$AppDir, "Bin"}}];
EMPH[a_, style_: "TI"] := Module[{{}},
    ToString[Style[a, style], StandardForm]
]
LINK[url_, label_:Style["\[RightSkeleton]", "SR"]] := Module[{{}},
    ToString[Hyperlink[label, url], StandardForm]
]
USAGE[str_, inputs__] := Module[{{}},
    ToString[StringForm[str, inputs], StandardForm]
]
End[]

{usage}

{pkgname}::argerr = "Wrong arguments. ";

Begin["`Private`"];
{error}
End[];

Install[FileNameJoin[{{`Developer`$BinDir, "{pkgname}.so"}}]];

Protect[
    {funcnames}
];
EndPackage[];
"""


def write_m_file(xcf, cfg):
    """Writes the m file. """
    root = cfg['xcpp']['root']
    app = cfg['mathematica']['app']
    usage = '\n\n'.join([_format_help(func, cfg) for func in xcf.function])
    pkgname = cfg['xcpp']['filename']
    funcnames = ',\n    '.join([m_name(func.name) for func in xcf.function])
    errors = '\n'.join([_format_error(func, cfg) for func in xcf.function])
    content = M_FILE.format(date=date(), app=app, pkgname=pkgname,
                            error=errors, usage=usage,
                            funcnames=funcnames)
    dest_dir = '%s/%s' % (cfg['mathematica']['mma'], app)
    if dest_dir[0] == '/':
        base = dest_dir
    else:
        base = '%s/%s' % (root, dest_dir)
    filename = cfg['xcpp']['filename']
    in_fname = '%s/%s.m' % (base, filename)
    trace('+ inspecting %s/%s.m ... ' % (app, filename))
    write_file(in_fname, content)
