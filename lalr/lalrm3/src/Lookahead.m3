(* compute LALR(1) lookahead sets *)

(* $Id: Lookahead.mi,v 2.3 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Lookahead.mi,v $
 * Revision 2.3  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.1  91/09/23  11:48:22  grosch
 * renamed module LALR to Lookahead
 * 
 * Revision 2.0  91/03/08  18:31:46  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/12  16:54:24  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0  88/10/04  14:36:29  vielsack
 * Initial revision * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE Lookahead;

IMPORT Word;
IMPORT IntSets;
IMPORT ExpArrays_tItemIndex;

FROM Limits     IMPORT MaxShortCard;
FROM FrontErrors
  IMPORT eFatal, eInformation, eString, eInternal, ErrorMessage, CrashT;
FROM DynArray   IMPORT MakeArray, ExtendArray;
FROM Sets       IMPORT tSet, MakeSet, ReleaseSet, AssignEmpty, Include, Exclude,
                        Extract, Union, Assign, IsElement, IsEmpty, ForallDo;
FROM Strings    IMPORT tString, ArrayToString;
FROM Automaton  IMPORT tIndex, tStateIndex, tItemIndex, tProdIndex, tItemIndexList,
                        tProduction, tRep, tItem, StartSymbol, ItemIndex, ItemArrayPtr,
                        ProdList, ProdArrayPtr, StateIndex, StateArrayPtr;
FROM Check      IMPORT CheckForConflicts;
FROM Positions  IMPORT NoPosition;
FROM TokenTab   IMPORT MINTerm, MAXTerm, MINNonTerm, MAXNonTerm, Vocabulary, Terminal,
                        NonTerminal, TokenError, TokenType, GetTokenType, TokenToSymbol;

  CONST
    eConflict   = 64;
    eNotLRk     = 62;

  VAR
    Nullables           : IntSets.T;
    reportedError       : BOOLEAN;

  PROCEDURE ComputeLALR() =
    BEGIN
      ComputeNullables();                       (* A *)
      MarkRep(); 
      ComputeDR();                      (* B *)
      ComputeReads();                   (* C *)
      Digraph (TreatReadConflict);      (* D *)
      CheckReadSets();
      ComputeIncludesAndLookback();     (* E *)
      Digraph (TreatFollowConflict);    (* F *)
      ComputeLA();                      (* G *)
      CheckForConflicts (NoConflict);   (* H *)
    END ComputeLALR;

  PROCEDURE ComputeNullables() =

  (* Berechne die Nichtterminale welche nullable sind *)

    VAR
      todo      : IntSets.T;         (* noch zu ueberpruefende Nichterminale *)
      success   : BOOLEAN;      (* hatte der letzte Schritt Erfolg *)
      t         : Terminal;
      nt        : NonTerminal;

    PROCEDURE IsYetNullable (nt: Word.T) =
      VAR
        u, i    : tIndex;
        pn      : tProdIndex;
        prodADR : (*tProduction*) ADDRESS;
        prod    : tProduction;
        ri      : Vocabulary;
        t       : Terminal;
        localsuccess    : BOOLEAN;
      BEGIN 
        WITH m2tom3_with_1=ProdList[nt] DO
          u := m2tom3_with_1.Used;

          (* Betrachte alle Produktionen mit linker Seite nt *)

          localsuccess := FALSE;
          pn := 1;
          WHILE (pn <= u) AND (NOT localsuccess) DO

            (* Auswahl der einzelnen Produktion *)

            prodADR := ADR(ProdArrayPtr^[m2tom3_with_1.PilArray^[pn].Index]);
            prod := LOOPHOLE (prodADR, tProduction);
            WITH m2tom3_with_2=prod^ DO

              (* Pruefe ob rechte Seite in Nullables* liegt *)

              localsuccess := TRUE;
              i := 1;

              WHILE (i <= m2tom3_with_2.Len) AND localsuccess DO
                ri := m2tom3_with_2.Right [i];
                localsuccess := IntSets.IsElement (ri,Nullables);
                INC (i);
              END;
            END;
            INC (pn);
          END;
        END;

        IF localsuccess THEN
          Nullables := IntSets.Include (Nullables, nt);
          todo := IntSets.Exclude (todo, nt);
          success := TRUE;
        END;
      END IsYetNullable;

    BEGIN
      todo := IntSets.Empty();
      Nullables := IntSets.Empty();

      (* todo = Menge aller Nichtterminale *)

      FOR nt := MINNonTerm TO MAXNonTerm DO
        IF GetTokenType (nt) = TokenType.NonTerm THEN
          todo := IntSets.Include (todo,nt);
        END;
      END;

      (* Nullables := { } *)

      REPEAT
        success := FALSE;

        (* Pruefe ob jetzt ein weiteres *)
        (* Nichtterminal terminalisierbar ist *)

        FOR nt := MINNonTerm TO MAXNonTerm DO
          IF IntSets.IsElement (nt, todo) THEN
            IsYetNullable (nt);
          END;
        END;
      UNTIL NOT success;    (* solange bis sich nichts aendert *)
      todo := NIL;
    END ComputeNullables;
  
  PROCEDURE MarkRep() =

  (* Markiert Items die eine Uebergang oder eine Reduktion repraesentieren *)

    VAR 
      si,s      : tStateIndex;
      pADR      : (*tProduction*) ADDRESS;
      p         : tProduction;
      reps      : IntSets.T;
      i         : tItemIndex;
      RepArray  : ARRAY Vocabulary OF tItemIndex;
      voc       : Vocabulary;
    BEGIN
      reps := IntSets.Empty();
      si := StateIndex;
      FOR s:=1 TO si DO
        reps := IntSets.Empty();
        WITH m2tom3_with_4=StateArrayPtr^[s] DO
          FOR i := m2tom3_with_4.Items TO m2tom3_with_4.Items + m2tom3_with_4.Size - 1 DO
            WITH m2tom3_with_5=ItemArrayPtr^[i] DO 
              pADR := ADR(ProdArrayPtr^[m2tom3_with_5.Prod]);
              p := LOOPHOLE (pADR, tProduction);
              IF m2tom3_with_5.Pos >= p^.Len THEN
                m2tom3_with_5.RepNo := i;
                m2tom3_with_5.Rep := tRep.RedRep;
              ELSE
                (* wird in Automaton beim Einrichten erledigt 
                *** voc := p^.Right[Pos+1];
                *** Read := voc;
                *)
                voc := m2tom3_with_5.Read;
                IF IntSets.IsElement (voc,reps) THEN
                  m2tom3_with_5.Rep := tRep.NoRep;
                  m2tom3_with_5.RepNo := RepArray [voc];
                ELSIF (voc >= MINTerm) AND (voc <= MAXTerm) THEN
                  RepArray [voc] := i;
                  m2tom3_with_5.RepNo := i;
                  m2tom3_with_5.Rep := tRep.TermRep;
                  reps := IntSets.Include (reps,voc);
                ELSE (* NonTerminal *)
                  RepArray [voc] := i;
                  m2tom3_with_5.RepNo := i;
                  m2tom3_with_5.Rep := tRep.NonTermRep;
                  reps := IntSets.Include (reps,voc);
                END;
              END;

              (* nur fuer diese Items werden Sets benoetigt *)

              IF (m2tom3_with_5.Rep = tRep.RedRep) OR (m2tom3_with_5.Rep=tRep.NonTermRep) THEN
                m2tom3_with_5.Set:= IntSets.Empty();
              END;
            END;
          END;
        END;
      END;
      reps := NIL;
    END MarkRep;

  PROCEDURE ComputeDR() =

  (* Berechnung der "direct read symbols" (DR) *)
  (* DR (p,A) := { t in T | p -A-> r -t-> }    *)
    
    VAR
      maxItem   : tItemIndex;
      pAIndex   : tItemIndex;
      pA        : tItem;
      pAProdADR : (*tProduction*) ADDRESS;
      r         : tStateIndex;
      ir        : tItemIndex;
    BEGIN
      maxItem := ItemIndex;
      FOR pAIndex := 1 TO maxItem DO 
        
        (* fuer alle Item - ein Item entspricht (p,A) *)

        pA := ItemArrayPtr^[pAIndex];

        (* pruefe ob pA einen Nichtterminaluebergang  repraesentiert *)

        pAProdADR := ADR(ProdArrayPtr^[pA.Prod]);  (* zugh. Produktion *)
(* CHECK ^ of what use? *) 

        IF (pA.Rep = tRep.NonTermRep) THEN
        
          (* Bestimme r *)

          r := pA.Next;

          (* Berechne DR (p,A) als Menge aller in r lesbaren Terminale *)

          WITH m2tom3_with_7=StateArrayPtr^[r] DO   (* Zustand r *)
            FOR ir := m2tom3_with_7.Items TO m2tom3_with_7.Items + m2tom3_with_7.Size - 1 DO 
              WITH m2tom3_with_8=ItemArrayPtr^[ir] DO    (* ein Item von r *)
                IF m2tom3_with_8.Rep = tRep.TermRep THEN
                  ItemArrayPtr^[pAIndex].Set
                    := IntSets.Include (ItemArrayPtr^[pAIndex].Set,m2tom3_with_8.Read);
                END;
              END;              (* ein Item von r *)
            END;              (* Zustand r *)
          END;
        END;
      END;
    END ComputeDR;


  PROCEDURE ComputeReads() =

  (* (p,A) reads (r,C)  falls  p -A-> r -C-> and  C => epsilon *)

    VAR
      pA, rC    : tItemIndex;
      r         : tStateIndex;
      maxItem   : tItemIndex;
    BEGIN

      (* fuer alle Items die einen Nichterminaluebergang repraesentiren *)

      maxItem := ItemIndex;
      FOR pA := 1 TO maxItem DO
        IF ItemArrayPtr^[pA].Rep = tRep.NonTermRep THEN

          (* Berechne r *)

          r := ItemArrayPtr^[pA].Next;

          (* Berechne zugh. rC's *)

          FOR rC := StateArrayPtr^[r].Items TO 
                    StateArrayPtr^[r].Items + StateArrayPtr^[r].Size - 1 DO
            
            IF ItemArrayPtr^[rC].Rep = tRep.NonTermRep THEN     

              (* Pruefe ob C => Epsilon *)

              IF IntSets.IsElement (ItemArrayPtr^[rC].Read,Nullables) THEN

                (* gueltiges rC gefunden *)
                (* Fuege rC zur Relation hinzu *)

                PutInRelation (pA, rC);
              
              END;
            END;
          END;
        END;
      END;
    END ComputeReads;

  PROCEDURE CheckReadSets() =
    VAR Item, MaxItem   : tItemIndex;
    BEGIN
      MaxItem := ItemIndex;
      FOR Item := 1 TO MaxItem DO
        WITH m2tom3_with_10=ItemArrayPtr^[Item] DO
          IF m2tom3_with_10.Rep = tRep.NonTermRep THEN
            IF IntSets.IsEmpty (m2tom3_with_10.Set) THEN
              m2tom3_with_10.EmptyReadSet := TRUE;
            ELSE
              m2tom3_with_10.EmptyReadSet := FALSE;
              m2tom3_with_10.ReadSet:= IntSets.Empty();
              m2tom3_with_10.ReadSet := m2tom3_with_10.Set;
            END;
          END;
        END;
      END;
    END CheckReadSets;

  PROCEDURE Digraph (TreatConflict: ConflictProc) =
    VAR x, maxItem      : tItemIndex;
    BEGIN

      (* let S be an initially empty stack OF elements of X *)

      ClearItemStack();

      (* let N be an ARRAY OF zeros indexd by elements of X *)

      ClearNumbers();

      (* for x in X such that N x = 0 DO *)

      maxItem := ItemIndex;
      FOR x := 1 TO maxItem DO
        WITH m2tom3_with_11=ItemArrayPtr^[x] DO
          IF m2tom3_with_11.Number = 0 THEN
            Traverse (x,TreatConflict);
          END;
        END;
      END;
    END Digraph;

  PROCEDURE Traverse ( x: tItemIndex; TreatConflict: ConflictProc) =
    VAR
      d         : Word.T;
      ArrayIndex: tIndex;
      yIndex    : tItemIndex;
      u         : tIndex;
      Top       : tItemIndex;
      EmptyCycle,
      cyclic    : BOOLEAN;
    BEGIN
      WITH m2tom3_with_12=ItemArrayPtr^[x] DO
      
        (* Push x on S *)

        PushItem (x);

        (* con d: Depth of S *)

        d := ItemDepth();

        (* N x <- d ;   F x <- F' x *)

        m2tom3_with_12.Number := d;

        (* for all y in X such that x R y DO *)

        WITH m2tom3_with_13=m2tom3_with_12.Relation DO
          u := m2tom3_with_13.Used;
          FOR ArrayIndex := 1 TO u DO
            yIndex := m2tom3_with_13.IilArray^[ArrayIndex];

            (* if Ny = 0 then call Traverse y *)

            IF ItemArrayPtr^[yIndex].Number = 0 THEN
              Traverse (yIndex,TreatConflict);
            END;

            (* assign N x <- Min (N x, N y) ;  F x := F x union F y *)

            IF ItemArrayPtr^[yIndex].Number < m2tom3_with_12.Number THEN
              m2tom3_with_12.Number := ItemArrayPtr^[yIndex].Number; 
            END;

            m2tom3_with_12.Set := IntSets.Union (m2tom3_with_12.Set,ItemArrayPtr^[yIndex].Set);
          END;
        END;

        (* IF N x = d *)

        IF m2tom3_with_12.Number = d THEN
          cyclic := FALSE;
          EmptyCycle := TRUE;

          (* then repeat *) 

          REPEAT
            (* assign N (Top OF S) <- Infinity) ; F(Top OF S) <- F x *)

            Top := TopItem();
            ItemArrayPtr^[Top].Number := MaxShortCard;

            IF Top # x THEN
              ItemArrayPtr^[Top].Set := m2tom3_with_12.Set;
              cyclic := TRUE;
              EmptyCycle := EmptyCycle AND ItemArrayPtr^[Top].EmptyReadSet;
            END

          (* until (Pop OF S) = x *)

          UNTIL PopItem() = x;

          IF cyclic THEN
            EmptyCycle := EmptyCycle AND m2tom3_with_12.EmptyReadSet;
            TreatConflict (EmptyCycle);
          END;
        END;
      END;
    END Traverse;

  PROCEDURE ComputeIncludesAndLookback() =
    VAR
      State, maxState   : tStateIndex;
      Transition, Item, RepItem : tItemIndex;
      TransItem         : tItem;
      ProductionADR     : (*tProduction*) ADDRESS;
      Production        : tProduction;
      nullable          : BOOLEAN;
    BEGIN
      (* loesche bisherige Relation fuer neue Includesrelation *)

      ClearRelation();

      (* Betrachte alle States *)

      maxState := StateIndex;
      FOR State := 1 TO maxState DO
        WITH m2tom3_with_15=StateArrayPtr^[State] DO
          
          (* Betrachte alle Nichterminaluebergaenge *)

          FOR Transition := m2tom3_with_15.Items TO m2tom3_with_15.Items + m2tom3_with_15.Size - 1 DO
            TransItem := ItemArrayPtr^[Transition];
            IF TransItem.Rep = tRep.NonTermRep THEN

              (* Finde Situationen deren Produktion mit dem *)
              (* zur Transition gehoerigen Nichterminal beginnen *)

              FOR Item := m2tom3_with_15.Items TO m2tom3_with_15.Items + m2tom3_with_15.Size - 1 DO
                WITH m2tom3_with_16=ItemArrayPtr^[Item] DO
                  ProductionADR := ADR(ProdArrayPtr^[m2tom3_with_16.Prod]);
                  Production := LOOPHOLE (ProductionADR, tProduction);
                  IF (m2tom3_with_16.Pos = 0) AND (Production^.Left = TransItem.Read) THEN
                    IF m2tom3_with_16.Pos < Production^.Len THEN
                      WindThrough (m2tom3_with_16.Next,m2tom3_with_16.Prod,m2tom3_with_16.Pos+1,Transition,nullable);
                      IF nullable THEN
                        (* Repraesentant beschaffen *)
                        RepItem := m2tom3_with_16.RepNo;
                        (* pruefen ob Nichtterminaluebergang *)
                        IF ItemArrayPtr^[RepItem].Rep = tRep.NonTermRep THEN
                          (* Include zu sich selbst ausfiltern, *)
                          (* da nicht konstruktiv bei Followberechnung *)
                          IF (RepItem # Transition) THEN 
                            PutInRelation (RepItem,Transition); (* In Include eintragen *)
                          END;
                        END;
                      END;
                    ELSE
                      PutInRelation (Item,Transition); (* In Lookback eintragen *)
                    END;
                  END;
                END;
              END;
            END;
          END;
        END;
      END;
    END ComputeIncludesAndLookback;
  
  PROCEDURE WindThrough (MyState: tStateIndex; MyProd: tProdIndex; MyPos: tIndex; Trans: tItemIndex; VAR nullable: BOOLEAN) =
    VAR
      Item              : tItemIndex;
      ProductionADR     : (*tProduction*) ADDRESS;
      Production        : tProduction;
    BEGIN
      WITH m2tom3_with_18=StateArrayPtr^[MyState] DO

        (* finde zugehoeriges Item *)

        Item := m2tom3_with_18.Items;
        LOOP
          WITH m2tom3_with_19=ItemArrayPtr^[Item] DO
            IF (m2tom3_with_19.Prod = MyProd) AND (m2tom3_with_19.Pos = MyPos) THEN
              EXIT;
            END;
            INC (Item);
          END;
        END;

        WITH m2tom3_with_20=ItemArrayPtr^[Item] DO

          (* eindeutigen Repraesentanten beschaffen *)
          (* jedoch mit speziellen (WITH-Statement) weiterarbeiten *)

          Item := ItemArrayPtr^[Item].RepNo;

          (* zugehoerige Production beschaffen *)

          ProductionADR := ADR(ProdArrayPtr^[m2tom3_with_20.Prod]);
          Production := LOOPHOLE (ProductionADR, tProduction);
          IF m2tom3_with_20.Pos < Production^.Len THEN 

            (* Ende noch nicht ereicht *)

            WindThrough (m2tom3_with_20.Next, m2tom3_with_20.Prod, m2tom3_with_20.Pos+1, Trans, nullable);
            IF nullable THEN 
              IF ItemArrayPtr^[Item].Rep = tRep.NonTermRep THEN

                (* Include zu sich selbst ausfiltern, *)
                (* da nicht konstruktiv bei Followberechnung *)

                IF (Item # Trans) THEN 

                  (* In Include eintragen *)

                  PutInRelation (Item,Trans);
                END;
              END;
              nullable := IntSets.IsElement (m2tom3_with_20.Read, Nullables);
            END;
          ELSE

            (* Ende der Produktion wurde erreicht *)

            nullable := TRUE;
            PutInRelation (Item, Trans);
          END;
        END;
      END;
    END WindThrough;

  PROCEDURE ComputeLA() =
    VAR 
      Index     : tIndex;
      Item      : tItemIndex;
      maxItem   : tItemIndex;
      lookbackindex     : tItemIndex;
      u         : tIndex;
    BEGIN
      
      (* fuer alle Items, die eine Reduktion darstellen *)

      maxItem := ItemIndex;
      FOR Item :=1 TO maxItem DO
        WITH m2tom3_with_23=ItemArrayPtr^[Item] DO
          IF m2tom3_with_23.Rep = tRep.RedRep THEN

            (* Berechne Look Ahead Set *)

            (* fuer alle Item in Lookback *)

            WITH m2tom3_with_24=m2tom3_with_23.Relation DO
              u := m2tom3_with_24.Used;
              FOR Index := 1 TO u DO
                lookbackindex := m2tom3_with_24.IilArray^[Index];
                
                (* fuege Follow(lookback) hinzu *)

                m2tom3_with_23.Set
                  := IntSets.Union (m2tom3_with_23.Set, ItemArrayPtr^[lookbackindex].Set);
              END;
            END;
          END;
        END;
      END;
    END ComputeLA;
  
  PROCEDURE TreatReadConflict (empty: BOOLEAN) =
  BEGIN
    IF NOT reportedError THEN
      (* do not report this fact
      ErrorMessage (eNotLRk,eInformation,0,0);
      *)
      reportedError := TRUE;
    END;
  END TreatReadConflict;

  PROCEDURE TreatFollowConflict (empty: BOOLEAN) =
  BEGIN
    IF NOT empty THEN
      IF NOT reportedError THEN
        (* do not report this fact
        ErrorMessage (eNotLRk,eInformation,0,0);
        *)
        reportedError := TRUE;
      END;
    END;
  END TreatFollowConflict;

  PROCEDURE ClearRelation() =
    VAR Item, maxItem   : tItemIndex;
    BEGIN
      maxItem := ItemIndex;
      FOR Item := 1 TO maxItem DO
        ItemArrayPtr^[Item].Relation.Used := 0;
      END;
    END ClearRelation;

  PROCEDURE PutInRelation (Rel: tItemIndex; NT: tItemIndex) =
    VAR i, u    : tIndex;
    BEGIN

      (* zu bearbeitende Relation auswaehlen *)

      WITH m2tom3_with_26=ItemArrayPtr^[Rel].Relation DO

        (* pruefen ob Eintrag bereits vorhanden *)

        u := m2tom3_with_26.Used;
        FOR i := 1 TO u DO
          IF m2tom3_with_26.IilArray^[i] = NT THEN RETURN; END;
        END;
        
        (* eventuell Speicher beschaffen *)

        i := m2tom3_with_26.Used;
        IF i = 0 THEN
          m2tom3_with_26.IilArray
            := NEW (REF ARRAY OF tIndex, m2tom3_with_26.Count+1);
          m2tom3_with_26.Count := NUMBER (m2tom3_with_26.IilArray^);
(* See note in Debug.SearchPathC about MakeArray. *) 
(*WAS:    MakeArray (m2tom3_with_26.IilArray,m2tom3_with_26.Count,BYTESIZE(tIndex));
        ELSIF m2tom3_with_26.Used >= m2tom3_with_26.Count THEN
          ExtendArray (m2tom3_with_26.IilArray,m2tom3_with_26.Count,BYTESIZE(tIndex));*)
        ELSE
          ExpArrays_tItemIndex.Expand (m2tom3_with_26.IilArray, i+2, i+6);
          m2tom3_with_26.Count := NUMBER (m2tom3_with_26.IilArray^);
        END;
        INC (m2tom3_with_26.Used);
        m2tom3_with_26.IilArray^[m2tom3_with_26.Used] := NT; 
      END;
    END PutInRelation;

(*UNSAFE MODULE ItemStack; Was nested in Modula-2.*)

(* IMPORT tItemIndexList, tItemIndex, BYTESIZE, MakeArray, ExtendArray, eInternal, eFatal, ERROR;*)

    

   CONST InitItemStackCount = 10;

   VAR Stack    : tItemIndexList;

    PROCEDURE ClearItemStack() =
      BEGIN
        Stack.Used := 0;
      END ClearItemStack;

    PROCEDURE PushItem (Item: tItemIndex) =
      BEGIN
        WITH m2tom3_with_27=Stack DO
          INC (Stack.Used);
          IF Stack.Used > Stack.Count THEN
            IF Stack.Count = 0 THEN
              Stack.Count := InitItemStackCount;
              Stack.IilArray := NEW (REF ARRAY OF tItemIndex, Stack.Count+1);
(* See note in Debug.SearchPathC about MakeArray. *) 
(*WAS:        MakeArray (Array,Count,BYTESIZE(tItemIndex));*)
            ELSE
              (*ExtendArray (Array,Count,BYTESIZE(tItemIndex));*)
            END;
          END;
          Stack.IilArray^[Stack.Used] := Item;
        END;
      END PushItem;

    PROCEDURE PopItem ():tItemIndex =
      VAR Item  : tItemIndex;
      BEGIN
        WITH m2tom3_with_28=Stack DO
          IF Stack.Used < 1 THEN
            CrashT ("PopItem on empty Stack");
          END;
          Item := Stack.IilArray^[Stack.Used];
          DEC (Stack.Used);
          RETURN Item;
        END;
      END PopItem;

    PROCEDURE TopItem ():tItemIndex =
      BEGIN
        WITH m2tom3_with_29=Stack DO
          RETURN Stack.IilArray^[Stack.Used];
        END;
      END TopItem;

    PROCEDURE ItemDepth ():Word.T =
      BEGIN
        RETURN Stack.Used;
      END ItemDepth;

(*
    BEGIN
      Stack.Used := 0;
      Stack.Count :=0;
    END ItemStack;
*)

  PROCEDURE ClearNumbers() =
  VAR i, maxi   : tItemIndex;
    BEGIN
      maxi := ItemIndex;
      FOR i:=1 TO maxi DO
        WITH m2tom3_with_30=ItemArrayPtr^[i] DO
          IF m2tom3_with_30.Rep = tRep.NonTermRep THEN
            m2tom3_with_30.Number := 0;
          ELSE
            m2tom3_with_30.Number := MaxShortCard;
          END;
        END;
      END;
    END ClearNumbers;
  
BEGIN 
  reportedError := FALSE;
  Stack.Used := 0;
  Stack.Count :=0;
END Lookahead.

