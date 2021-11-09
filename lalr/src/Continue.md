(* compute continuation for error recovery *)

(* $Id: Continue.md,v 1.1 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Continue.md,v $
 * Revision 1.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  14:36:01  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Continue;

FROM Automaton IMPORT
  tIndex;

FROM TokenTab IMPORT
  Vocabulary;

  VAR
    Value : ARRAY Vocabulary OF tIndex;

  PROCEDURE ValueNonterms;

  PROCEDURE MakeContinuation;


END Continue.
