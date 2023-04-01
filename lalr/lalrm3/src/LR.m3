(* compute LR(0) automaton *)

(* $Id: LR.mi,v 1.1 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: LR.mi,v $
 * Revision 1.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  14:36:34  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE LR;

  IMPORT IntSets;

  FROM Automaton IMPORT
    tStateIndex,
    MakeFirstState,
    GotoSet,
    Goto;
  
  FROM Sets IMPORT
    tSet,
    MakeSet, ReleaseSet,
    IsEmpty,
    Extract;

  FROM TokenTab IMPORT
    MAXNonTerm,
    Vocabulary;
  

  PROCEDURE ComputeLR() =

  VAR 
    s : tStateIndex;

  BEGIN
    s := MakeFirstState();
    ComputeNext (s);
  END ComputeLR;


  PROCEDURE ComputeNext
    (s : tStateIndex) =

  VAR 
    t : tStateIndex;
    g : IntSets.T;
    v : Vocabulary;
    n : BOOLEAN;

  BEGIN
    g := IntSets.Empty();
    GotoSet (s,g);
    WHILE NOT IntSets.IsEmpty (g) DO
      v := IntSets.ExtractArbitraryMember ((*(VAR*)g);
      t := Goto(s,v,n);
      IF n THEN
        ComputeNext (t);
      END;
    END;
    g := NIL;
  END ComputeNext;


BEGIN
END LR.

