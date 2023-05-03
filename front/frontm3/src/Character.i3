(* handle strings with open character arrays *)

(* $Id: Character.md,v 1.3 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: Character.md,v $
 * Revision 1.3  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/11  18:44:40  grosch
 * layout improvements
 * 
 * Revision 1.1	 89/01/12  18:05:05  vielsack
 * supply procedure Assign to assign a character string
 * 
 * Revision 1.0	 88/10/04  14:26:37  vielsack
 * Initial revision
 * 
 *)

INTERFACE  Character;

IMPORT Word;
PROCEDURE IsEqual	(READONLY c1, c2: ARRAY OF CHAR): BOOLEAN;
PROCEDURE Length	(READONLY c: ARRAY OF CHAR): Word.T;
PROCEDURE Assign	(VAR s1: ARRAY OF CHAR;READONLY  s2: ARRAY OF CHAR);

END Character.

