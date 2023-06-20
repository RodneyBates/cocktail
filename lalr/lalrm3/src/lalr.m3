(* $Id: lalr.mi,v 2.4 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: lalr.mi,v $
 * Revision 2.4  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.3  1992/01/30  14:08:30  grosch
 * redesign of interface to operating system
 *
 * Revision 2.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.1  91/09/23  11:48:28  grosch
 * renamed module LALR to Lookahead
 * 
 * Revision 2.0  91/03/08  18:31:52  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.2  90/06/12  16:54:36  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.1  89/02/24  14:03:37  vielsack
 * BeginSource is no longer called
 * 
 * Revision 1.0  88/10/04  14:36:20  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE lalr EXPORTS Main;

FROM ArgCheck   IMPORT Generate, ArgCheck, GenerateSupport, Pars, Def, TEST;
FROM Automaton  IMPORT IsBnf, InitAutomaton;
FROM Check      IMPORT CheckForConflicts;
FROM FrontErrors  IMPORT eError, ErrorCount, ErrorMessage, BeginErrors,
                  CloseErrors;
FROM Gen        IMPORT GenDefaultActions, GenCode;
FROM Infos      IMPORT WriteInfo;
FROM ReuseIO    IMPORT tFile, StdOutput, WriteNl, CloseIO;
FROM Lookahead  IMPORT NoConflict, ComputeLALR;
FROM LR         IMPORT ComputeLR;
FROM Parser     IMPORT Parser;
FROM Reduce     IMPORT Reduced, TestReduced;
FROM Scanner    IMPORT BeginScanner;
FROM Strings    IMPORT tString, StringToInt;
FROM StringMem  IMPORT InitStringMemory;
FROM Idents     IMPORT InitIdents;
FROM System     IMPORT Exit;
FROM TokenTab   IMPORT InitTokenTable;
FROM WriteTok   IMPORT tLanguage, Language;

VAR
  errors : INTEGER;
  Status : INTEGER;
  GoOn   : BOOLEAN;

BEGIN
  InitStringMemory();
  InitIdents();
  ArgCheck();
  BeginErrors();
  GoOn := Generate;

  IF GoOn THEN
    GenDefaultActions();
    InitTokenTable();
    BeginScanner();
    errors := Parser ();
    GenerateSupport();
    GoOn := ErrorCount [eError] = 0;
  END;

  IF GoOn THEN
    InitAutomaton();
    GoOn := IsBnf;
  END;

  IF GoOn THEN
    TestReduced();
    GoOn := Reduced;
  END;

  IF GoOn THEN
    ComputeLR();
  END;

  IF GoOn THEN
    ComputeLALR();
    GoOn := NoConflict;
  END;

  IF GoOn THEN
    GenCode (Pars, Def);
    Status := 0;
  ELSE
    Status := 1;
  END;

  CloseErrors();
  IF TEST AND GoOn THEN WriteInfo (StdOutput); END;
  CloseIO();
  Exit (Status);
END lalr. 


