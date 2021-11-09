(* compute LALR(1) lookahead sets *)

(* $Id: Lookahead.md,v 1.3 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Lookahead.md,v $
 * Revision 1.3  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  91/09/23  11:48:20  grosch
 * renamed module LALR to Lookahead
 * 
 * Revision 1.1  90/06/12  16:54:23  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0	 88/10/04  14:36:28  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Lookahead;

TYPE ConflictProc = PROCEDURE (BOOLEAN);

VAR NoConflict	: BOOLEAN;

PROCEDURE ComputeLALR;	(* Berechnung der LALR(1) LookAheadSets *)

END Lookahead.
