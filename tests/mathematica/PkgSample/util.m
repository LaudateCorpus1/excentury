(* File generated on Sat Jan 04, 2014 03:20:56 AM by xcpp *)

BeginPackage["PkgSample`util`"];
Unprotect[
    square,
    cube,
    movePoint,
    makeLine,
    scale,
    printMsg,
    genTensors,
    scaleArray
];
ClearAll[
    square,
    cube,
    movePoint,
    makeLine,
    scale,
    printMsg,
    genTensors,
    scaleArray
];

Begin["`Developer`"]
$AppDir = DirectoryName@$InputFileName;
$BinDir = FileNameJoin[{$AppDir, "Bin"}];
EMPH[a_, style_: "TI"] := Module[{},
    ToString[Style[a, style], StandardForm]
]
LINK[url_, label_:Style["\[RightSkeleton]", "SR"]] := Module[{},
    ToString[Hyperlink[label, url], StandardForm]
]
USAGE[str_, inputs__] := Module[{},
    ToString[StringForm[str, inputs], StandardForm]
]
End[]

square::usage = `Developer`USAGE["square[`1`] \n\
\treturn the square of the number.\n\
\t\tparameters:\n\
\t\t`1`: number to be squared.\n\
",
   `Developer`EMPH["x"],
   `Developer`LINK["paclet:util"]
];

cube::usage = `Developer`USAGE["cube[`1`] \n\
\tcube a number\n\
\t\tparameters:\n\
\t\t`1`: number to be cubed.\n\
",
   `Developer`EMPH["x"],
   `Developer`LINK["paclet:util"]
];

movePoint::usage = `Developer`USAGE["movePoint[`1`, `2`] \n\
\tAdds a number to each of the coordinates of a point.\n\
\t\tparameters:\n\
\t\t`1`: the point to be moved.\n\
\t\t`2`: the amount the point should be moved.\n\
",
   `Developer`EMPH["p"],
   `Developer`EMPH["x"],
   `Developer`LINK["paclet:util"]
];

makeLine::usage = `Developer`USAGE["makeLine[`1`, `2`] \n\
\tGiven two points, it constructs a line.\n\
\t\tparameters:\n\
\t\t`1`: the first point.\n\
\t\t`2`: the second point.\n\
",
   `Developer`EMPH["p1"],
   `Developer`EMPH["p2"],
   `Developer`LINK["paclet:util"]
];

scale::usage = `Developer`USAGE["scale[`1`, `2`] \n\
\tScalar multiplication.\n\
\t\tparameters:\n\
\t\t`1`: the vector to multiply. \n\
\t\t`2`: the scalar.\n\
",
   `Developer`EMPH["v"],
   `Developer`EMPH["alpha"],
   `Developer`LINK["paclet:util"]
];

printMsg::usage = `Developer`USAGE["printMsg[`1`] \n\
\tPrint a message to the standard error stream.\n\
\t\tparameters:\n\
\t\t`1`: the message to be printed.\n\
",
   `Developer`EMPH["msg"],
   `Developer`LINK["paclet:util"]
];

genTensors::usage = `Developer`USAGE["genTensors[] \n\
\tGenerate tensors of dimension 4.", `Developer`LINK["paclet:util"]];

scaleArray::usage = `Developer`USAGE["scaleArray[`1`, `2`] \n\
\tscale a one dimentional array.\n\
\t\tparameters:\n\
\t\t`1`: the array to be scaled.\n\
\t\t`2`: the scalar factor.\n\
",
   `Developer`EMPH["v"],
   `Developer`EMPH["s"],
   `Developer`LINK["paclet:util"]
];

util::argerr = "Wrong arguments. ";

Begin["`Private`"];
square[args___] := (Message[util::argerr]; $Failed)
cube[args___] := (Message[util::argerr]; $Failed)
movePoint[args___] := (Message[util::argerr]; $Failed)
makeLine[args___] := (Message[util::argerr]; $Failed)
scale[args___] := (Message[util::argerr]; $Failed)
printMsg[args___] := (Message[util::argerr]; $Failed)
genTensors[args___] := (Message[util::argerr]; $Failed)
scaleArray[args___] := (Message[util::argerr]; $Failed)
End[];

Install[FileNameJoin[{`Developer`$BinDir, "util.so"}]];

Protect[
    square,
    cube,
    movePoint,
    makeLine,
    scale,
    printMsg,
    genTensors,
    scaleArray
];
EndPackage[];
