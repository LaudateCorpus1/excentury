(* ::Package:: *)

(************************************************************************)
(* This file was generated automatically by the Mathematica front end.  *)
(* It contains Initialization cells from a Notebook file, which         *)
(* typically will have the same name as this file except ending in      *)
(* ".nb" instead of ".m".                                               *)
(*                                                                      *)
(* This file is intended to be loaded into the Mathematica kernel using *)
(* the package loading commands Get or Needs.  Doing so is equivalent   *)
(* to using the Evaluate Initialization Cells menu command in the front *)
(* end.                                                                 *)
(*                                                                      *)
(* DO NOT EDIT THIS FILE.  This entire file is regenerated              *)
(* automatically each time the parent Notebook file is saved in the     *)
(* Mathematica front end.  Any changes you make to this file will be    *)
(* overwritten.                                                         *)
(************************************************************************)



(* :Title: BistableDelay *) 
(* :Author: jmlopez *)
(* :Email: jmlopez@math.uh.edu *)
(* :Context: BistableDelay` *)
(* :History:  June 26 2012 *)
(* :Mathematica version: 8.0 for Mac OS X x86 (64-bit) (February 23, 2011) *)


BeginPackage["BistableDelay`"];


Unprotect[genSwitchRandPathDiff, genSwitchRandPath, genSwitchSubPath, genSwitchResidenceTimes, singleRandPath, singleSubPath, singleResidenceTimes, warrenSubPath, warrenRandPath, warrenResidenceTimes];
ClearAll[genSwitchRandPathDiff, genSwitchRandPath, genSwitchSubPath, genSwitchResidenceTimes, singleRandPath, singleSubPath, singleResidenceTimes, warrenSubPath, warrenRandPath, warrenResidenceTimes];


(* :Usage Messages: *)


genSwitchRandPath::usage = 
"genSwitchRandPath[\!\(\*
StyleBox[\"s\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"b\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"\[Eta]\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dy\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates a realization of the genSwitch model.";
genSwitchRandPathDiff::usage = 
"genSwitchRandPath[\!\(\*
StyleBox[\"s\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"b\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"\[Eta]\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dy\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates a realization of the genSwitchDiff model.";
genSwitchSubPath::usage = 
"genSwitchSubPath[\!\(\*
StyleBox[\"s\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"b\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"\[Eta]\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dy\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"time_limit\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates a realization of the genSwitch model.";
genSwitchResidenceTimes::usage = 
"genSwitchResidenceTimes[\!\(\*
StyleBox[\"s\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"b\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"\[Eta]\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"dy\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"r\", \"TI\"]\)] returns a list of times the genetic switch spends in each state.";

singleRandPath::usage = 
"singleRandPath[\!\(\*
StyleBox[\"s\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"b\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"\[Eta]\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"modelDx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"driverDx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"driverDy\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates a realization of the single model.";
singleSubPath::usage = 
"singleSubPath[\!\(\*
StyleBox[\"s\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"b\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"\[Eta]\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"modelDx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"driverDx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"driverDy\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"time_limit\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates a realization of the single model.";
singleResidenceTimes::usage = 
"singleResidenceTimes[\!\(\*
StyleBox[\"s\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"b\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"\[Eta]\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"modelDx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"driverDx\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"driverDy\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"r\", \"TI\"]\)] returns a list of times the single model spends in each state.";
warrenSubPath::usage = 
"warrenSubPath\!\(\*
StyleBox[\"[\", \"TI\"]\)\!\(\*
StyleBox[\"inputs\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"go\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"here\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"time_limit\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates a realization of the genSwitch model.";
warrenRandPath::usage = 
"warrenSubPath\!\(\*
StyleBox[\"[\", \"TI\"]\)\!\(\*
StyleBox[\"inputs\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"go\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"here\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"time_limit\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates a realization of the warren model.";
warrenResidenceTimes::usage = 
"warrenSubPath\!\(\*
StyleBox[\"[\", \"TI\"]\)\!\(\*
StyleBox[\"inputs\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"go\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"here\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"time_limit\", \"TI\"]\)\!\(\*
StyleBox[\",\", \"TI\"]\)\!\(\*
StyleBox[\" \", \"TI\"]\)\!\(\*
StyleBox[\"num_points\", \"TI\"]\)] generates residence times of the warren model.";


(* :Error Messages: *)


BistableDelay::argerr="Wrong arguments.";


Begin["`Private`"];


genSwitchRandPath[args___] := (Message[BistableDelay::argerr];$Failed)
genSwitchRandPathDiff[args___] := (Message[BistableDelay::argerr];$Failed)
genSwitchSubPath[args___] := (Message[BistableDelay::argerr];$Failed)
genSwitchResidenceTimes[args___] := (Message[BistableDelay::argerr];$Failed)

singleRandPath[args___] := (Message[BistableDelay::argerr];$Failed)
singleSubPath[args___] := (Message[BistableDelay::argerr];$Failed)
singleResidenceTimes[args___] := (Message[BistableDelay::argerr];$Failed)
warrenSubPath[args___] := (Message[BistableDelay::argerr];$Failed)
warrenRandPath[args___] := (Message[BistableDelay::argerr];$Failed)
warrenResidenceTimes[args___] := (Message[BistableDelay::argerr];$Failed)

Install["BistableDelay"];


End[];


Protect[genSwitchRandPathDiff, genSwitchRandPath, genSwitchSubPath, genSwitchResidenceTimes, singleRandPath, singleSubPath, singleResidenceTimes, warrenSubPath, warrenRandPath, warrenResidenceTimes];


EndPackage[];