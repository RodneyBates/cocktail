(* compute LR(0) automaton *)

(* $Id: LR.md,v 1.1 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: LR.md,v $
 * Revision 1.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  14:36:32  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  LR;

  PROCEDURE ComputeLR();

END LR.

