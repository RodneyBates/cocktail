(* test program for parser *)

(* $Id: Pars.mi,v 1.4 1992/08/07 15:13:51 grosch rel $ *)

(* $Log: Pars.mi,v $
 * Revision 1.4  1992/08/07  15:13:51  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.3  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/11  18:45:08  grosch
 * layout improvements
 * 
 * Revision 1.1	 89/02/24  13:59:39  vielsack
 * BeginSource is no longer called
 * 
 * Revision 1.0	 88/10/04  14:26:57  vielsack
 * Initial revision
 * 
 *)

UNSAFE MODULE Pars EXPORTS Main;

IMPORT Word, WriteTok, Character, Path, FrontChecks;

FROM FrontErrors	IMPORT BeginErrors, CloseErrors;
FROM Parser	IMPORT Parser;
FROM Idents	IMPORT InitIdents;
FROM Scanner	IMPORT BeginScanner;
FROM StringMem	IMPORT InitStringMemory;
FROM TokenTab	IMPORT InitTokenTable;

VAR errors	: Word.T;

BEGIN
  InitStringMemory();
  InitIdents();
  BeginErrors();
  BeginScanner();
  InitTokenTable();
  errors := Parser ();
  CloseErrors();
END Pars.

