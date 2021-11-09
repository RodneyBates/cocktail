(* generate source parts of the parser *)

(* $Id: GenLang.md,v 1.2 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: GenLang.md,v $
 * Revision 1.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/12  16:54:15  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0	 88/10/04  14:36:22  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE GenLang;

FROM IO IMPORT tFile;

PROCEDURE WriteConstants	(f:tFile);
PROCEDURE WriteReduceCode	(f:tFile);

END GenLang.
