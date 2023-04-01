(* add path to file name *)

(* $Id: Path.md,v 1.1 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: Path.md,v $
 * Revision 1.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  14:27:05  vielsack
 * Initial revision
 * 
 *)

UNSAFE INTERFACE  FrontPath;

PROCEDURE InsertPathT (VAR T:TEXT);
PROCEDURE InsertPath (VAR a: ARRAY OF CHAR);

END FrontPath.

