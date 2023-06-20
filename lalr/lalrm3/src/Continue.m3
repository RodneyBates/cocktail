(* compute continuation for error recovery *)

(* $Id: Continue.mi,v 1.3 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Continue.mi,v $
 * Revision 1.3  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  91/01/18  20:33:16  grosch
 * fixed problem with Continuation
 * 
 * Revision 1.1  90/06/12  16:53:51  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0  88/10/04  14:36:02  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

 UNSAFE MODULE Continue;

FROM Automaton  IMPORT tIndex, Infinite, tProduction, tProdIndex, ProdArrayPtr,
                        ProdIndex, NextProdIndex, tStateKind, tStateIndex,
                        StateArrayPtr, StateIndex, tRep, tItemIndex, ItemArrayPtr, ItemIndex;
FROM DynArray   IMPORT MakeArray;
FROM Gen        IMPORT ElmtSize, Continuation, ContinuationCount, LastReadState, TableElmt;
FROM Sets       IMPORT Select;
IMPORT IntSets; 

FROM TokenTab   IMPORT MINTerm, MAXTerm, MINNonTerm, MAXNonTerm, Vocabulary, NonTerminal;

  PROCEDURE MakeContinuation() =
    VAR
      state, maxState : tStateIndex;
      MinProdNo : tIndex;
      i : tIndex;
      item, BestItem : tItemIndex;
      prod : tProduction;
    BEGIN
      ContinuationCount := LastReadState+1;
      Continuation := NEW (REF ARRAY OF TableElmt, ContinuationCount+1);
(* See note in Debug.SearchPathC about MakeArray. *) 
(*WAS:MakeArray (Continuation,ContinuationCount,ElmtSize);*)
      Continuation^[0] := 0;

      (* Betrachte alle Zustaende *)

      maxState := StateIndex;
      FOR state := 1 TO maxState DO
      WITH m2tom3_with_1=StateArrayPtr^[state] DO
        IF m2tom3_with_1.Kind = tStateKind.sRead THEN   (* Read Zustaende *)
          MinProdNo := Infinite;
          item := m2tom3_with_1.Items;
          LOOP
            IF item >= (m2tom3_with_1.Items + m2tom3_with_1.Size) THEN EXIT; END;
            WITH m2tom3_with_2=ItemArrayPtr^[item] DO
            
              (* Nur Terminaluebergaenge und Reduktionen *)

              IF (ItemArrayPtr^[m2tom3_with_2.RepNo].Rep = tRep.TermRep) OR
                 (ItemArrayPtr^[m2tom3_with_2.RepNo].Rep = tRep.RedRep) THEN
                prod := ADR (ProdArrayPtr^[m2tom3_with_2.Prod]);
                WITH m2tom3_with_3=prod^ DO
                  IF m2tom3_with_3.ProdNo < MinProdNo THEN
                    MinProdNo := m2tom3_with_3.ProdNo;
                    BestItem := m2tom3_with_2.RepNo;
                    EXIT;
                  END;
                END;
              END;
            END;
            INC (item);
          END;

          WITH m2tom3_with_5=ItemArrayPtr^[BestItem] DO
            IF m2tom3_with_5.Rep = tRep.TermRep THEN
              Continuation^[m2tom3_with_1.NewNumber] := m2tom3_with_5.Read;
            ELSE        (* Waehle ein beliebiges Element aus *)
              Continuation^[m2tom3_with_1.NewNumber] := IntSets.ArbitraryMember (m2tom3_with_5.Set);
            END;
          END;
        END;
      END;
      END;
    END MakeContinuation;

  PROCEDURE ValueNonterms() =
    VAR
      voc : Vocabulary;
      prodADR : (*tProduction*) ADDRESS;
      prod : tProduction;
      index,maxIndex : tProdIndex;
      success : BOOLEAN;
      value : tIndex;
      i : tIndex;
    BEGIN
      FOR voc := MINNonTerm TO MAXNonTerm DO (* initialisieren *)
        Value[voc] := Infinite;
      END;
      FOR voc := MINTerm TO MAXTerm DO
        Value[voc] := 1;
      END;
      maxIndex := ProdIndex;

      REPEAT 
        success := FALSE;
        index := 0;
        WHILE index < maxIndex DO
          prodADR := ADR(ProdArrayPtr^[index]);
          prod := LOOPHOLE (prodADR, tProduction);
          value := 0;
          WITH m2tom3_with_9=prod^ DO
            FOR i := 1 TO m2tom3_with_9.Len DO
              voc := m2tom3_with_9.Right[i];
              IF (value = Infinite) OR (Value[voc] = Infinite) THEN
                value := Infinite;
              ELSE
                INC (value,Value[voc]);
              END;
            END;
            IF Value [m2tom3_with_9.Left] > value THEN
              Value [m2tom3_with_9.Left] := value;
              success := TRUE;
            END;
          END;
          index := NextProdIndex(index);
        END;
      UNTIL NOT success;
    END ValueNonterms;

BEGIN
END Continue.

