(* :Title: Excentury *) 
(* :Author: jmlopez *)
(* :Email: jmlopez.rod@gmail.com *)
(* :Summary: This package provides functions to read files created by excentury *)
(* :Context: Excentury`Excentury` *)
(* :Package version: 0.1 *)
(* :History:  Version 0.1 July 15 2013 *)
(* :Mathematica version: 8.0 for Mac OS X x86 (64-bit) (February 23, 2011) *)
(* :Discussion: The function ExcenturyRead returns a list containing two lists. 
                The first list is the names of the variables in the file. The
			    second is the values of those variables. *)


BeginPackage["Excentury`Excentury`"];

Unprotect[ExcenturyRead];
ClearAll[ExcenturyRead];

(* :Usage Messages: *)

ExcenturyRead::usage = 
"ExcenturyRead[\!\(\*
StyleBox[\"fileName\", \"TI\"]\)] Reads the given file and returns \
the variables contained in the file.";


(* :Error Messages: *)

ExcenturyRead::argerr =
"A filename was expected.";

Begin["`Private`"];

(* Helper Functions for ExcenturyRead. *)
ExcenturyReadInfo[str_] := Module[{type, numbytes, name},
    type = Read[str, Word];
    Switch[type, 
        "I"|"N"|"R", 
            {type, Read[str, Number]},
        "T", 
            {type, ExcenturyReadInfo[str]}
    ]
]
ExcenturyReadData[str_, info_] := Module[{i, sub, rm, ndim, dim, data},
    Switch[info[[1]],
        "I"|"N"|"R", 
            Read[str, Number],
        "T", 
            rm = Read[str, Number];
            ndim = Read[str, Number];
            dim = ReadList[str, Number, ndim];
            sub =info[[2]];
            Switch[sub[[1]],
                "I"|"N"|"R", 
                    data = ReadList[str, Number, Times@@dim];
                    data = ArrayReshape[data, Reverse@dim];
                    If[ndim == 1,
                        Return@data
                    ];
                    If[rm == 0,
                        Transpose[data],
                        data
                    ],
                "T",
                    data =Range[Times@@dim];
                    For[i=1, i<= Length[data],i++,
                        data[[i]]=ExcenturyReadData[str, sub];
                    ];
                    data
            ]
    ]
]
(* ExcenturyRead: *)
ExcenturyRead[args___] := (Message[ExcenturyRead::argerr];$Failed)
ExcenturyRead[fname_] := Module[{i, ndict, nvars, str, var, val, info},
    str =  OpenRead[fname];
    ndict = Read[str, Number];
    nvars = Read[str, Number];
    var = Range[nvars];
    val = Range[nvars];
    For[i=1, i<=nvars, i++,
        var[[i]] = Read[str, Word];
        info = ExcenturyReadInfo[str];
        val[[i]] = ExcenturyReadData[str, info];
    ];
    {var, val}
]

End[];


Protect[ExcenturyRead];


EndPackage[];
