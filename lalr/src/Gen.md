(* generate the parser *)

(* $Id: Gen.md,v 1.4 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Gen.md,v $
 * Revision 1.4  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.3  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/12/20  19:26:38  grosch
 * removed time stamp from tables
 * 
 * Revision 1.1  90/06/12  16:54:08  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0	 88/10/04  14:36:15  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Gen;

FROM TokenTab	IMPORT Terminal;
FROM Automaton	IMPORT Infinite, tIndex, tStateIndex;
FROM IO		IMPORT tFile;
FROM TokenTab	IMPORT Vocabulary;

CONST NoState = 0;

TYPE 
    TableElmt  = SHORTCARD;
    tTableLine = ARRAY Vocabulary OF tStateIndex;

VAR
    Trace : BOOLEAN;
    CaseFlag : BOOLEAN;
    CaseLabels : INTEGER;

    FirstSymbol,
    LastSymbol,
    FirstTerminal,
    LastTerminal     : Vocabulary;
    NonTermOffset    : CARDINAL;

    FirstState,
    LastState,
    FirstReadState,
    LastReadState,
    FirstReadTermState,
    LastReadTermState,
    FirstReadNonTermState,
    LastReadNonTermState,
    FirstReduceState,
    LastReduceState,
    StopState	       : tStateIndex;
    ReduceOffset       : tStateIndex;

    ElmtSize : TableElmt;

    Length : POINTER TO ARRAY [1..Infinite] OF TableElmt;
    LengthCount : LONGINT;
    LeftHandSide : POINTER TO ARRAY [1..Infinite] OF TableElmt;
    LeftHandSideCount : LONGINT;
    Continuation : POINTER TO ARRAY [0..Infinite] OF TableElmt;
    ContinuationCount : LONGINT;
    FinalToProd : POINTER TO ARRAY [0..Infinite] OF TableElmt;
    FinalToProdCount : LONGINT;

PROCEDURE GenDefaultActions;

  (* Erzeugen von Standardaktionen fuer die Deklaratioen *)

PROCEDURE GenCode (Pars: tFile; Def: tFile);

  (* Erzeuge den Code
     Pars  - enthaelt das Rahmenprogramm fuer den Parser *)

PROCEDURE StartState (): CARDINAL;

  (* liefert die Codierung des Startzustandes *)

END Gen.
