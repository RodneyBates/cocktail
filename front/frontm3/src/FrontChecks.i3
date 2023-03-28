(* check i/o errors *)

(* $Id: Checks.md,v 1.2 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: Checks.md,v $
 * Revision 1.2  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/11  18:44:42  grosch
 * layout improvements
 * 
 * Revision 1.0  88/10/04  14:26:39  vielsack
 * Initial revision
 * 
 *)

UNSAFE INTERFACE  FrontChecks;

FROM    ReuseIO              IMPORT  tFile;

PROCEDURE ErrorCheck     (READONLY s: ARRAY OF CHAR; n: INTEGER);
PROCEDURE ErrorCheckT    (a: TEXT; n: INTEGER);
PROCEDURE CheckReadOpen  (VAR f: tFile;READONLY  s: ARRAY OF CHAR);
PROCEDURE CheckWriteOpen (VAR f: tFile;READONLY  s: ARRAY OF CHAR);

END FrontChecks.

