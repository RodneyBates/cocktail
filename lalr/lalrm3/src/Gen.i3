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
 * Revision 1.0  88/10/04  14:36:15  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  Gen;

IMPORT Word;
FROM SYSTEM IMPORT SHORTCARD;
FROM TokenTab   IMPORT Terminal;
FROM Automaton  IMPORT Infinite, tIndex, tStateIndex;
FROM ReuseIO         IMPORT tFile;
FROM TokenTab   IMPORT Vocabulary;

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
    NonTermOffset    : Word.T;

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
    StopState          : tStateIndex;
    ReduceOffset       : tStateIndex;

    ElmtSize : TableElmt;

    Length : REF  ARRAY  OF TableElmt;
    LengthCount : INTEGER;
    LeftHandSide : REF  ARRAY  OF TableElmt;
    LeftHandSideCount : INTEGER;
    Continuation : REF  ARRAY  OF TableElmt;
    ContinuationCount : INTEGER;
    FinalToProd : REF  ARRAY OF TableElmt;
    FinalToProdCount : INTEGER;

PROCEDURE GenDefaultActions();

  (* Erzeugen von Standardaktionen fuer die Deklaratioen *)

PROCEDURE GenCode (Pars: tFile; Def: tFile);

  (* Erzeuge den Code
     Pars  - enthaelt das Rahmenprogramm fuer den Parser *)

PROCEDURE StartState (): Word.T;

  (* liefert die Codierung des Startzustandes *)

END Gen.

