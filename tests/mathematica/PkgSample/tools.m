(* File generated on Fri Jan 03, 2014 02:42:36 PM by xcpp *)

BeginPackage["PkgSample`tools`"];
Unprotect[
    squareRoot,
    randArray,
    testRep
];
ClearAll[
    squareRoot,
    randArray,
    testRep
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

squareRoot::usage = `Developer`USAGE["squareRoot[`1`, `2`, `3`] \n\
\tCompute the square root of a number using Newton's method.\n\
\tThis function will print to stdout the amount of time it took to\n\
\texecute.\n\
\t\tparameters:\n\
\t\t`1`: the input to the square root function.\n\
\t\t`2`: initial guess.\n\
\t\t`3`: number of iterations.\n\
",
   `Developer`EMPH["x"],
   `Developer`EMPH["x0"],
   `Developer`EMPH["iter"],
   `Developer`LINK["paclet:tools"]
];

randArray::usage = `Developer`USAGE["randArray[`1`, `2`, `3`] \n\
\tGet an array of random numbers from a uniform distribution.\n\
\t\tparameters:\n\
\t\t`1`: amount of random numbers.\n\
\t\t`2`: the mean of the distribution.\n\
\t\t`3`: the standard deviation of the distribution.\n\
",
   `Developer`EMPH["n"],
   `Developer`EMPH["mean"],
   `Developer`EMPH["std"],
   `Developer`LINK["paclet:tools"]
];

testRep::usage = `Developer`USAGE["testRep[] \n\
\tThis function will do useless computation for the sake of\n\
\ttesting the reporter object which will print messages to\n\
\tstdout.", `Developer`LINK["paclet:tools"]];

tools::argerr = "Wrong arguments. ";

Begin["`Private`"];
squareRoot[args___] := (Message[tools::argerr]; $Failed)
randArray[args___] := (Message[tools::argerr]; $Failed)
testRep[args___] := (Message[tools::argerr]; $Failed)
End[];

Install[FileNameJoin[{`Developer`$BinDir, "tools.so"}]];

Protect[
    squareRoot,
    randArray,
    testRep
];
EndPackage[];
