(* check arguments *)

(* $Id: ArgCheck.md,v 1.2 1992/08/07 15:22:49 grosch rel $ *)

(* Rodney M. Bates, modifications: 
    1-98 Change to not open /dev/null when -d (or -a) flag is not given.
    3-2023 Add generation of Module-3 code.
    Further changes in https://github.com/RodneyBates/cocktail
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

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  ArgCheck;

FROM    ReuseIO      IMPORT  tFile;
FROM    Strings IMPORT  tString;
FROM    Idents  IMPORT  tIdent;

CONST
  ScannerT       = "Scanner";
  ParserT        = "Parser";

VAR
  LineFlag      ,
  Generate      : BOOLEAN;
  Pars, Def     : tFile;
  TEST          : BOOLEAN;
  ExtDef, ExtImp: TEXT;
VAR MakeDef : BOOLEAN;

PROCEDURE ArgCheck();
PROCEDURE GenerateSupport();
PROCEDURE MakeFileName (Name: tIdent;READONLY  Default, Ext: ARRAY OF CHAR; VAR array: ARRAY OF CHAR);
PROCEDURE ExpandLine (Out: tFile; READONLY Line: tString);
PROCEDURE CopyFile (In, Out: tFile);

END ArgCheck.

