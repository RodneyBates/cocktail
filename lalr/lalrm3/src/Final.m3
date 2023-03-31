(* map final states to productions *)

(* $Id: Final.mi,v 2.1 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Final.mi,v $
 * Revision 2.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:31:41  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/12  16:54:07  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0  88/10/04  14:36:14  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE Final;

  FROM Automaton IMPORT
    tProduction,
    ProdArrayPtr,
    tStateKind,
    tStateIndex,
    StateArrayPtr, StateIndex,
    tItemIndex,
    ItemArrayPtr;

  FROM DynArray IMPORT MakeArray;

  FROM Gen IMPORT
    TableElmt,
    ElmtSize,
    NoState,
    ReduceOffset,
    FinalToProd,
    FinalToProdCount,
    FirstReadTermState,
    LastReadNonTermState;
  
  

  PROCEDURE MakeFinalToProd() =
    VAR
      state, maxState : tStateIndex;
      prod : tProduction;
    BEGIN
      FinalToProdCount := LastReadNonTermState-FirstReadTermState+1;
      FinalToProd := (REF ARRAY OF TableElmt, FinalToProdCount);
(*WAS:MakeArray (FinalToProd,FinalToProdCount,ElmtSize);*)
      FOR state := FirstReadTermState TO LastReadNonTermState DO
        FinalToProd^[state-FirstReadTermState] := NoState;
      END;

      (* Betrachte alle Zustaende *)

      maxState := StateIndex;
      FOR state := 1 TO maxState DO
      WITH m2tom3_with_1=StateArrayPtr^[state] DO

        (* Final Zustaende *)

        IF (* ((Kind = sTerm) OR (Kind = sNonterm)) AND *)
           (FirstReadTermState <= m2tom3_with_1.NewNumber) AND
           (m2tom3_with_1.NewNumber <= LastReadNonTermState) THEN

          prod := ADR (ProdArrayPtr^[ItemArrayPtr^[m2tom3_with_1.Items].Prod]);
          FinalToProd^[m2tom3_with_1.NewNumber-FirstReadTermState] := prod^.ProdNo + ReduceOffset;
        END;

      END;
      END;

    END MakeFinalToProd;

BEGIN
END Final.

