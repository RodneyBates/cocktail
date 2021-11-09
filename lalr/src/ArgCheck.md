(* check arguments *)

(* $Id: ArgCheck.md,v 1.2 1992/08/07 15:22:49 grosch rel $ *)

(* Rodney M. Bates, modifications: 

    1-98 Change to not open /dev/null when -d (or -a) flag is not given. 

*) 

(* $Log: ArgCheck.md,v $
 * Revision 1.2  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  14:35:46  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE ArgCheck;

FROM	IO	IMPORT	tFile;
FROM	Strings	IMPORT	tString;
FROM	Idents	IMPORT	tIdent;

CONST
  Scanner	= 'Scanner';
  Parser	= 'Parser';

VAR
  LineFlag	,
  Generate	: BOOLEAN;
  Pars, Def	: tFile;
  TEST		: BOOLEAN;
  ExtDef, ExtImp: ARRAY [0..5] OF CHAR;
VAR MakeDef : BOOLEAN;

PROCEDURE ArgCheck;
PROCEDURE GenerateSupport;
PROCEDURE MakeFileName (Name: tIdent; Default, Ext: ARRAY OF CHAR; VAR array: ARRAY OF CHAR);
PROCEDURE ExpandLine (Out: tFile; Line: tString);
PROCEDURE CopyFile (In, Out: tFile);

END ArgCheck.
