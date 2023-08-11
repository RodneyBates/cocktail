(* handle and log errors *)

(* $Id: Errors.md,v 2.2 1992/08/07 15:13:51 grosch rel $ *)

(* $Log: Errors.md,v $
 * Revision 2.2  1992/08/07  15:13:51  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:26:15  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/11  18:44:44  grosch
 * layout improvements
 * 
 * Revision 1.0  88/10/04  14:26:43  vielsack
 * Initial revision
 * 
 *)

INTERFACE  FrontErrors;


IMPORT Word;
FROM SYSTEM IMPORT SHORTCARD;
FROM Positions  IMPORT tPosition;

CONST
   NoText               = 0     ;
   SyntaxError          = 1     ;       (* error codes          *)
   ExpectedTokens       = 2     ;
   RestartPoint         = 3     ;
   TokenInserted        = 4     ;
   WrongParseTable      = 5     ;
   OpenParseTable       = 6     ;
   ReadParseTable       = 7     ;
   NotReach             = 8;
   NoProd               = 9;
   NotTerm              = 10;

(* Error codes from front scanner, from input.rex. *) 
   eEolString    = 11;
   eUnClAction   = 12;
   eUnClComment  = 13;
   eUnClString   = 14;
   eCharIgnored  = 15;



(* Error codes from lalr. *)
    eState              = 70;
    eReadRed            = 71;
    eRedRed             = 72;
    eReadRedRed         = 73;
    eRepReadRed         = 74;
    eRepRedRed          = 75;
    eRepReadRedRed      = 76;
    eARepReadRed        = 77;
    eARepRedRed         = 78;
    eARepReadRedRed     = 79;
    eOffRHS             = 80;

CONST   (* info classes *)
  eInteger      =       1; (* UNTRACED ... *) 
  eShort        =       2;
  eLong         =       3;
  eReal         =       4;
  eBoolean      =       5;
  eCharacter    =       6;
  eString       =       7;
  eArray        =       8;
  eSet          =       9;
  eIdent        =       10;
  eTermSet      =       11;
  eTokSet       =       12; (* <: REFANY *) 
  eText         =       13; (* <: REFANY *) 

(* These constants and the identically-numbered redundant ones below
   are used mixedly in front and lalr, including the lalr Parser skeleton.
   There could be lots of places required to unravel this. 
*)
CONST (* error classes *)
   Fatal                = 1     ;       
   Restriction          = 2     ;
   Error                = 3     ;
   Warning              = 4     ;
   Repair               = 5     ;
   Note                 = 6     ;
   Information          = 7     ;

CONST   (* error classes *)
  eFatal        =       1;
  eRestriction  =       2;
  eError        =       3;
  eWarning      =       4;
  eRepair       =       5;
  eNote         =       6;
  eInformation  =       7;

CONST MaxErrorClass     = 7;
TYPE ErrorClassSet      = SET OF [0 .. MaxErrorClass];

CONST
  SysOffset     =       100;
  eInternal     =       15;

TYPE tReportMode        = {eImmediate, eNoListing, eListing};


VAR ErrorCount  : ARRAY [0..MaxErrorClass] OF SHORTCARD;

PROCEDURE ErrorMessage  (ErrorCode, ErrorClass: Word.T; Position: tPosition);

PROCEDURE ErrorMessageI (ErrorCode, ErrorClass: Word.T; Position: tPosition;
                         InfoClass: Word.T; Info: ADDRESS);
(* ^Useful for InfoClass values that do not correspond to <: REFANY. *)

PROCEDURE ErrorMessageTraced
  (ErrorCode, ErrorClass: Word.T; Position: tPosition;
                         InfoClass: Word.T; InfoTraced: REFANY);
(* ^Useful for InfoClass values that correspond to <: REFANY. *)

PROCEDURE CrashT (a: TEXT);

PROCEDURE BeginErrors   ();

PROCEDURE SetReportMode (mode: tReportMode);

PROCEDURE CloseErrors   ();

VAR ErrorTableT := "Error.Tab";

VAR
  ReportClass : ErrorClassSet;

END FrontErrors.

