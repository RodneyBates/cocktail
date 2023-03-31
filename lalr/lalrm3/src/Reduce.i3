(* check if the grammar is reduced *)

(* $Id: Reduce.md,v 1.1 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Reduce.md,v $
 * Revision 1.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  14:36:37  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  Reduce;

  VAR
    Reduced : BOOLEAN;

  PROCEDURE TestReduced();

  (* prueft ob die im Module Automaton bekannte Grammatik
     reduziert ist. Falls nein wird das Programm mittels einer
     Fehlermeldung abgebrochen *)

END Reduce.


