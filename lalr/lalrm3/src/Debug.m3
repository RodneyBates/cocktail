(* compute debugging information *)

(* 2001-02-15, Rodney M. Bates Added PrintItemSets. *) 

(* $Id: Debug.mi,v 1.6 1992/09/24 13:12:31 grosch rel $ *)

(* $Log: Debug.mi,v $
 * Revision 1.6  1992/09/24  13:12:31  grosch
 * added option -f
 *
 * Revision 1.5  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.4  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.3  90/06/12  16:53:54  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.2  89/05/02  14:35:37  vielsack
 * new option: -v (verbose)
 * NoTrace is used instead of NoDebug
 * 
 * Revision 1.1  89/01/12  18:11:43  vielsack
 * to supress the trace of a read reduce conflict
 * the left hand side must be the same too
 * 
 * Revision 1.0  88/10/04  14:36:05  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE Debug;

IMPORT Word;
FROM SYSTEM IMPORT M2LONGINT, SHORTCARD;
FROM Automaton  IMPORT tAss, tRep, tItem, tState, tIndex, tProduction, Infinite,
                        StartSymbol, ProdList, StateArrayPtr, tStateIndex, StateIndex,
                        ItemArrayPtr, tItemIndex, ItemIndex, ProdArrayPtr, tProdIndex;
FROM Continue   IMPORT Value;
FROM DynArray   IMPORT ExtendArray, MakeArray, ReleaseArray;
FROM ReuseIO         IMPORT tFile, WriteC, WriteT, WriteI, WriteNl;
(*FROM Sets       IMPORT tSet, Extract, Include, Exclude, MakeSet, ReleaseSet,
                        Assign, Intersection, IsElement, IsEmpty;
                        *)
IMPORT IntSets;
FROM Strings    IMPORT Length, Char, tString;
FROM Idents     IMPORT tIdent, GetString;

FROM TokenTab   IMPORT MINTerm, MAXTerm, MINNonTerm, MAXNonTerm, Terminal,
                        NonTerminal, Vocabulary, TokenError, TokenToSymbol;
  
  CONST
    InitTab = 0;
    MaxTabA = 40;
    MaxTabB = 30;
    MaxTabC = 50;
    MaxTabD = 40;
    InitChainLength = 50;

  TYPE
    tItemPath = RECORD
        count  : SHORTCARD;
        max    : M2LONGINT;
        path   : REF  ARRAY OF tItemIndex;
      END;
    
    tProdPathElmt = RECORD
        Prod : tProdIndex;
        Pos  : tIndex;
      END;

    tProdPath = RECORD
        count : SHORTCARD;
        max   : M2LONGINT;
        path  : REF ARRAY OF tProdPathElmt;
      END;

    tItemChainElmt = RECORD
        Item : tItemIndex;
        Last : tIndex;
      END;
    
    tItemChain = RECORD
        reached : IntSets.T;
        level   : M2LONGINT;
        count   : M2LONGINT;
        max     : M2LONGINT;
        chain   : REF  ARRAY OF tItemChainElmt;
      END;

  VAR
    PathA : tProdPath;
    PathC : tItemPath;
    PathB : tItemPath;
    ChainD: tItemChain;
    PathD : tProdPath;

PROCEDURE InformIgnored (Item: tItemIndex; t: Terminal) =
    BEGIN
      WriteT (dFile,"ignored                 ");
      WriteItem (Item,t);
    END InformIgnored;

PROCEDURE InformLowPri (Item: tItemIndex; t: Terminal) =
    BEGIN
      WriteT (dFile,"ignored (precedence)    ");
      WriteItem (Item,t);
    END InformLowPri;

PROCEDURE InformRightAss (Item: tItemIndex; t: Terminal) =
    BEGIN
      WriteT (dFile,"ignored (associativity) ");
      WriteItem (Item,t);
    END InformRightAss;

PROCEDURE InformLeftAss (Item: tItemIndex; t: Terminal) =
    BEGIN
      WriteT (dFile,"ignored (associativity) ");
      WriteItem (Item,t);
    END InformLeftAss;

PROCEDURE InformKept (Item: tItemIndex; t: Terminal) =
    BEGIN
      WriteT (dFile,"retained                ");
      WriteItem (Item,t);
    END InformKept;

PROCEDURE InformConflict (kind: tConflict) =
    BEGIN
      CASE kind OF
        tConflict.ShRed  => WriteT (dFile, "there is a read reduce conflict");
      | tConflict.RedRed         => WriteT (dFile, "there is a reduce reduce conflict");
      | tConflict.ShRedRed => WriteT (dFile, "there is a read-reduce-reduce conflict");
      ELSE
      END;
      WriteNl (dFile);
    END InformConflict;

PROCEDURE NewLine() =
    BEGIN
      WriteNl (dFile);
    END NewLine;
    
PROCEDURE WriteItem (Item: tItemIndex; t: Terminal) =
    VAR
      length : Word.T;
      i : tIndex;
      p : tProduction;
    BEGIN
      WITH m2tom3_with_1=ItemArrayPtr^[Item] DO
        p := ADR (ProdArrayPtr^[m2tom3_with_1.Prod]);
        WriteVoc (p^.Left,length);
        WriteT (dFile," -> ");
        length := 0;
        WITH m2tom3_with_2=p^ DO
          IF m2tom3_with_2.Len = 0 THEN
            WriteT (dFile,"-Epsilon-.");
          ELSE
            IF m2tom3_with_1.Pos = 0 THEN
              WriteC (dFile,'.');
            END;
            FOR i:=1 TO m2tom3_with_2.Len DO
              WriteVoc (m2tom3_with_2.Right[i],length);
              IF m2tom3_with_1.Pos = i THEN
                WriteC (dFile,'.');
              ELSE
                WriteC (dFile,' ');
              END;
            END;
          END;
        END;
        IF (m2tom3_with_1.Pos = p^.Len) AND (t # MINTerm) THEN
          WriteT (dFile," {");
          WriteVoc (t,length);
          WriteC (dFile,'}');
        END;

        WriteNl (dFile);
      END;
    END WriteItem;

PROCEDURE PrintItemSets ( )  = 
  VAR state : M2LONGINT;
  VAR item : tItemIndex; 
  BEGIN
    FOR state := 1 TO StateIndex
    DO
      WriteT (dFile,"State ");
      WriteI (dFile,state,1);
      WriteT (dFile," = { ");    
      WriteNl (dFile);
      FOR item := StateArrayPtr^[state].Items 
          TO StateArrayPtr^[state].Items + StateArrayPtr^[state].Size - 1
      DO
        WriteItem ( item , MINTerm )
      END;
      WriteT (dFile," } ");   
      WriteNl (dFile);
      WriteNl (dFile);
    END 
  END PrintItemSets;
    
PROCEDURE DebugHead (State: tStateIndex) =
    BEGIN
      IF NoTrace THEN RETURN END;
      WriteT (dFile,"State ");
      WriteI (dFile,State,1);
      WriteNl (dFile);
      WriteNl (dFile);
    END DebugHead;
  
PROCEDURE DebugEnd() =
    BEGIN
      IF NoTrace THEN RETURN END;
      WriteNl (dFile);
    END DebugEnd;

  PROCEDURE DebugState
    (     State : tStateIndex;         (* inconsistent State *)
      VAR CS    : IntSets.T) =              (* Conflict Set *)

  (* Erzeuge Zusatzinformation zum Zustand 'State' mit Konfliktmenge 'Set' *)
  (* wird fuer jeden inkonsitenten Zustand ausgefuehrt *)

    VAR
      Item : tItemIndex;
      s : IntSets.T;
      EI: IntSets.T;          (* Explained Items *)
    BEGIN
      IF NoTrace THEN RETURN END;
      WriteNl (dFile);
      s := IntSets.Empty();

      (* finde alle Reduktionen die an einem Konflikt beteiligt sind *)

      WITH m2tom3_with_4=StateArrayPtr^[State] DO
        EI := IntSets.Empty();
        FOR Item := m2tom3_with_4.Items TO m2tom3_with_4.Items+m2tom3_with_4.Size-1 DO
        WITH m2tom3_with_5=ItemArrayPtr^[Item] DO
          IF m2tom3_with_5.Rep = tRep.RedRep THEN

            s := IntSets.Intersection (CS, m2tom3_with_5.Set);
            IF NOT IntSets.IsEmpty (s) THEN

              (* Bearbeite konfliktbeladene Reduktion *)

              DebugRedItem (State, CS, Item, EI);
            END;
          END;
        END;
        END;
        EI := NIL;
      END;
      s  := NIL;
    END DebugState;

  PROCEDURE DebugRedItem 
    (     State : tStateIndex;     (* Zustand in dem der Konflikt auftritt *)
      VAR CS    : IntSets.T;            (* Conflict Set *)
          Item  : tItemIndex;      (* am Konflikt beteiligte Reduktion *)
      VAR EI    : IntSets.T) =          (* Explained Items *)
  
    VAR
      T : IntSets.T;
      cs : IntSets.T;
      i : tItemIndex;
      I : tItemIndex;
      d : Word.T;
      t : Terminal;
      prod : tProduction;
    BEGIN
      cs := CS; 
      FindPathC (cs,Item);    (* fuer Part C *)
      UnRepPathC();
      T := IntSets.Empty();

      i := PathC.path^[PathC.count];
      WHILE NOT IntSets.IsEmpty (cs) DO
        t := IntSets.ExtractArbitraryMember((*VAR*)cs);
        WITH m2tom3_with_7=ItemArrayPtr^[i] DO
          WITH m2tom3_with_8=StateArrayPtr^[m2tom3_with_7.Next] DO
            I := m2tom3_with_8.Items;
            LOOP
              IF I >= (m2tom3_with_8.Items+m2tom3_with_8.Size) THEN EXIT END;

              (* Pruefe ob Terminal t moeglich *)

              IF Possible (I,t) THEN
                
                d := InitTab;  (* akt. Randabstand *)

                IF NOT Fast THEN
                   (* wie kommt man von Startsymbol zum Problem *)
                   prod := ADR (ProdArrayPtr^[ItemArrayPtr^[I].Prod]);
                   WritePartA (d,prod^.Left);
                END;

                (* wie kommt man zu Vorschauzeichen *)
                WritePartB (d,I);

                (* wie kommt man zur linken Seite der Red *)
                WritePartC (d,Item,t);

                (* womit kollidiert die Reduktion *)
                WritePartD (d,State,t,Item,EI);

                WriteNl (dFile);
                WriteNl (dFile);

                PathB.path := NIL;
(*WAS:          ReleaseArray (PathB.path,PathB.max,BYTESIZE(tItemIndex));*)
                EXIT;

              END;
              INC (I);
            END;
          END;
        END;
      END;
      T  := NIL;
      cs  := NIL;
      PathC.path := NIL;
(*WAS:ReleaseArray (PathC.path,PathC.max,BYTESIZE(tItemIndex));*)
    END DebugRedItem;

PROCEDURE Possible (Item: tItemIndex; t: Terminal) : BOOLEAN =
    TYPE triaer = {yes,no,maybe};
    VAR 
      state : tStateIndex;
      prod  : tProdIndex;
      pos   : tIndex;
      reached : IntSets.T;
    
    PROCEDURE Poss (state: tStateIndex; prod: tProdIndex; pos: tIndex; depth: Word.T) : triaer =
      VAR
        res : triaer;
        nt  : NonTerminal;
        item : tItemIndex;
        Item : tItemIndex;
        production : tProduction;
      BEGIN

        (* finde zugh. item *)

        WITH m2tom3_with_10=StateArrayPtr^[state] DO
          Item := m2tom3_with_10.Items;
          LOOP
            WITH m2tom3_with_11=ItemArrayPtr^[Item] DO
              IF (m2tom3_with_11.Prod = prod) AND (m2tom3_with_11.Pos = pos) THEN
                EXIT;
              END;
              INC (Item);
            END;
          END;
        END;

        IF IntSets.IsElement (Item,reached) THEN RETURN triaer.no; END;

        reached := IntSets.Include (reached, Item);

        WITH m2tom3_with_13=ItemArrayPtr^[Item] DO
          CASE GetRep(Item) OF
          | tRep.TermRep=>
              IF t = m2tom3_with_13.Read THEN
                  PathB.count := depth;
                  PathB.max := depth;
                  PathB.path := NEW (REF ARRAY OF tItemIndex, PathB.max+1);
(* See note in SearchPathC about MakeArray. *) 
(*WAS:            MakeArray (PathB.path,PathB.max,BYTESIZE(tItemIndex));*)
                  PathB.path^[depth] := Item;
                reached := IntSets.Exclude (reached,Item);
                RETURN triaer.yes;
              ELSE
                reached := IntSets.Exclude (reached,Item);
                RETURN triaer.no;
              END;
          | tRep.RedRep=>
              reached := IntSets.Exclude (reached,Item);
              RETURN triaer.maybe;
          | tRep.NonTermRep=>
              res := triaer.no;
              nt := m2tom3_with_13.Read;
              WITH m2tom3_with_14=StateArrayPtr^[state] DO
                FOR item := m2tom3_with_14.Items TO m2tom3_with_14.Items+m2tom3_with_14.Size-1 DO
                  WITH m2tom3_with_15=ItemArrayPtr^[item] DO
                    production := ADR (ProdArrayPtr^[m2tom3_with_15.Prod]);
                    IF production^.Left = nt THEN
                      CASE Poss (state,m2tom3_with_15.Prod,m2tom3_with_15.Pos,depth+1) OF
                      | triaer.yes=>  
                         PathB.path^[depth] := Item;
                         reached := IntSets.Exclude (reached,Item);
                         RETURN triaer.yes;
                      | triaer.no=>
                         
                      | triaer.maybe=>
                         CASE Poss (ItemArrayPtr^[Item].Next,
                                    prod,pos+1,depth) OF
                         | triaer.yes=>
                           reached := IntSets.Exclude (reached,Item);
                           RETURN triaer.yes;
                         | triaer.no=>
                            
                         | triaer.maybe=>
                             res := triaer.maybe;
                         END;
                      END;
                    END;
                  END;
                END;
              END;
              reached := IntSets.Exclude (reached,Item);
              RETURN res;
          END;
        END;
      END Poss;
    
PROCEDURE GetRep (Item: tItemIndex) : tRep =
    
    (* Bestimme die zu Item gehoerige Repraesentantenart unabhaenig
       vom Eintrag, es muss TermRep, NonTermRep oder RedRep
       zurueckgeliefert werden, NoRep ist nicht zulaessig *)
       
      VAR prod : tProduction;
      BEGIN
        WITH m2tom3_with_19=ItemArrayPtr^[Item] DO
          prod := ADR (ProdArrayPtr^[m2tom3_with_19.Prod]);
          WITH m2tom3_with_20=prod^ DO
            IF m2tom3_with_19.Pos = m2tom3_with_20.Len THEN
              RETURN tRep.RedRep;
            ELSIF (m2tom3_with_20.Right [m2tom3_with_19.Pos+1] >= MINTerm) AND (m2tom3_with_20.Right[m2tom3_with_19.Pos+1] <= MAXTerm) THEN
              RETURN tRep.TermRep;
            ELSE
              RETURN tRep.NonTermRep;
            END;
          END;
        END;
      END GetRep;

    BEGIN
      WITH m2tom3_with_22=ItemArrayPtr^[Item] DO
        state := m2tom3_with_22.Number;
        prod := m2tom3_with_22.Prod;
        pos := m2tom3_with_22.Pos;
      END;
      reached := IntSets.Empty();
      IF (Poss (state,prod,pos,1) = triaer.yes) THEN
        reached  := NIL;
        RETURN TRUE;
      ELSE
        reached  := NIL;
        RETURN FALSE;
      END;
    END Possible;

  PROCEDURE FindPathC (VAR cs: IntSets.T; Item: tItemIndex) =
    VAR
      maxdepth : Word.T;
      found : BOOLEAN;
      i,u : tIndex;
    BEGIN
      maxdepth := 0;
      found := FALSE;
      REPEAT
        INC (maxdepth);
        WITH m2tom3_with_23=ItemArrayPtr^[Item].Relation DO
          i := 1;
          u := m2tom3_with_23.Used;
          WHILE (i <= u) AND (NOT found) DO
            SearchPathC (cs,maxdepth,0,m2tom3_with_23.Array^[i],found);
            INC (i);
          END;
        END;
      UNTIL found;
    END FindPathC;

PROCEDURE SearchPathC (VAR cs      : IntSets.T; maxdepth : Word.T; depth        : Word.T;
          Item: tItemIndex; VAR found: BOOLEAN) =
    VAR
      s : IntSets.T;
      i,u : tIndex;
    BEGIN
      WITH m2tom3_with_24=ItemArrayPtr^[Item] DO
        INC (depth);
        s := IntSets.Empty();
        IF NOT m2tom3_with_24.EmptyReadSet THEN
          s := m2tom3_with_24.ReadSet;
        END;
        s := IntSets.Intersection (s,cs);
        found := NOT IntSets.IsEmpty (s);
        IF found THEN
          cs := s;
        END;
        s  := NIL;
        IF found THEN
          PathC.count := depth;
          PathC.max := depth;
          PathC.path := NEW (REF ARRAY OF tItemIndex, PathC.max+1);
(* NOTE: There is some inconsistency about whether MakeArray gets the
         element count or max element number.  To avoid extensive vetting,
         I am just increasing the element count by one where MakeArray is
         replaced by Modula-3' NEW REF ARRAY ...
         In at least this instance, the original Modula-2 version was
         one too low, causing RT errors in the Modula-3 version.  It probably
         originally just went over harmlessly. *) 
(*WAS:    MakeArray (PathC.path,PathC.max,BYTESIZE(tItemIndex));*)
          PathC.path^[depth] := Item;
        ELSIF depth < maxdepth THEN
          WITH m2tom3_with_25=ItemArrayPtr^[Item].Relation DO
            i := 1;
            u := m2tom3_with_25.Used;
            WHILE (i <= u) AND (NOT found) DO
              SearchPathC (cs,maxdepth,depth,m2tom3_with_25.Array^[i],found);
              INC (i);
            END;
            IF found THEN
              PathC.path^[depth] := Item;
            END;
          END;
        END;
      END;
    END SearchPathC;

PROCEDURE UnRepPathC() =
    VAR
      State : tStateIndex;
      PathItem, Item : tItemIndex;
      i,j : Word.T;
      prod : tProduction;
      PathVal,val : tIndex;

    (* Waehle moeglichst kurz zu beendende Items aus *)

    BEGIN
      WITH m2tom3_with_27=PathC DO
        FOR i:=1 TO m2tom3_with_27.count-1 DO
          PathItem := m2tom3_with_27.path^[i];
          prod := ADR (ProdArrayPtr^[ItemArrayPtr^[PathItem].Prod]);
          PathVal := 0;
          FOR j := ItemArrayPtr^[PathItem].Pos+1 TO prod^.Len DO
            INC (PathVal,Value[prod^.Right[j]]);
          END;
          State := ItemArrayPtr^[PathItem].Number;
          WITH m2tom3_with_28=StateArrayPtr^[State] DO
            FOR Item := m2tom3_with_28.Items TO m2tom3_with_28.Items+m2tom3_with_28.Size-1 DO
              IF ItemArrayPtr^[Item].RepNo = ItemArrayPtr^[PathItem].RepNo THEN
                prod := ADR (ProdArrayPtr^[ItemArrayPtr^[Item].Prod]);
                val := 0;
                FOR j := ItemArrayPtr^[Item].Pos+1 TO prod^.Len DO
                  INC (val,Value[prod^.Right[j]]);
                END;
                IF val < PathVal THEN
                  PathItem := Item;
                  PathVal := val;
                END;
              END;
            END;
          END;
          m2tom3_with_27.path^[i] := PathItem;
        END;
      END;
    END UnRepPathC;

PROCEDURE WritePartA (VAR d: Word.T; N: NonTerminal) =
  
  (* Drucke den Trace vom Startsymbol zum Nichtterminal N *)

    VAR i,j : Word.T;
    BEGIN
      FindPathA (N);
      WITH m2tom3_with_30=PathA DO
        FOR i:=1 TO m2tom3_with_30.count DO
          WriteTab (d);
          WriteProd (m2tom3_with_30.path^[i].Prod,m2tom3_with_30.path^[i].Pos,d);
          WriteNl (dFile);
          IF (d > MaxTabA) OR ((i = m2tom3_with_30.count) AND (d > InitTab)) THEN 
            WriteTab(InitTab);
            FOR j:=InitTab+1 TO d DO
              WriteC (dFile,'.');
            END;
            WriteC  (dFile,':');
            WriteNl (dFile);
            d := InitTab;
            WriteTab (d);
            WriteC (dFile,':');
            WriteNl (dFile);
          END;
        END;
      END;
      PathA.path := NIL; 
(*WAS:ReleaseArray (PathA.path,PathA.max,BYTESIZE(tProdPathElmt));*)
    END WritePartA;

PROCEDURE FindPathA (N: NonTerminal) =
    VAR
      maxdepth : Word.T;
      found    : BOOLEAN;
      rNTs : IntSets.T;  (* reached Nonterminals *)
    BEGIN
      maxdepth := 0;
      found := FALSE;
      rNTs := IntSets.Empty();

      REPEAT
        INC (maxdepth);
        SearchPathA (StartSymbol,N,maxdepth,0,found,rNTs);
      UNTIL found;
      rNTs  := NIL;
    END FindPathA;
  
  PROCEDURE SearchPathA (From: NonTerminal; To: NonTerminal;
         maxdepth: Word.T; depth: Word.T; VAR found: BOOLEAN; VAR rNTs: IntSets.T) =
    VAR
      prod : tProduction;
      prodindex : tProdIndex;
      pos : tIndex;
      i,u : tIndex;
    BEGIN
      IF From = To THEN
        WITH m2tom3_with_31=PathA DO
          m2tom3_with_31.count := depth;
          m2tom3_with_31.max    := depth;
          m2tom3_with_31.path
            := NEW (REF ARRAY OF tProdPathElmt, m2tom3_with_31.max+1);
(* See note in SearchPathC about MakeArray. *) 
(*WAS:    MakeArray (m2tom3_with_31.path,m2tom3_with_31.max,BYTESIZE(tProdPathElmt));*)
          found := TRUE;
        END;
      ELSIF depth < maxdepth THEN

        (* Betrachte alle zu From gehoerige Produktionen *)

        WITH m2tom3_with_32=ProdList[From] DO
          u := m2tom3_with_32.Used;
          FOR i := 1 TO u DO
            
            (* Betrachte eine einzelne Produktion *)

            prodindex := m2tom3_with_32.Array^[i].Index;
            prod := ADR (ProdArrayPtr^[prodindex]);
            WITH m2tom3_with_33=prod^ DO
              FOR pos := 1 TO m2tom3_with_33.Len DO
                IF (m2tom3_with_33.Right[pos] >= MINNonTerm) 
                   AND (m2tom3_with_33.Right[pos] <= MAXNonTerm) THEN

                  (* Nichtterminale auf der rechten Seite weiterverfolgen *)

                  IF NOT IntSets.IsElement (m2tom3_with_33.Right[pos],rNTs) THEN

                    rNTs := IntSets.Include (rNTs,m2tom3_with_33.Right[pos]);
                    SearchPathA (m2tom3_with_33.Right[pos],To,maxdepth,depth+1,found,rNTs);
                    rNTs := IntSets.Exclude (rNTs,m2tom3_with_33.Right[pos]);

                  END;

                  IF found THEN
                    
                    (* Pfad festhalten *)

                    PathA.path^[depth+1].Prod := prodindex;

                    (* Position vor dem Nichtterminal angeben *)

                    PathA.path^[depth+1].Pos := pos-1;

                    RETURN;
                  END;
                END;
              END;
            END;
          END;
        END;
      END;
    END SearchPathA;

PROCEDURE WritePartB (VAR d: Word.T; I: tItemIndex) =
    VAR
      p : tProdIndex;
      l : tIndex;
      l1 : tIndex;
      length : Word.T;
      i,j : Word.T;
      d1 : Word.T;
      prodADR : (*tProduction*) ADDRESS;
      prod : tProduction;
    BEGIN
      p := ItemArrayPtr^[I].Prod;
      l := ItemArrayPtr^[I].Pos-1;
      l1 := ItemArrayPtr^[PathB.path^[1]].Pos;
      d1 := 0;
      WriteTab (d);

      prodADR := ADR(ProdArrayPtr^[p]);
      prod := LOOPHOLE (prodADR, tProduction);
      WITH m2tom3_with_35=prod^ DO
        FOR i:=1 TO m2tom3_with_35.Len DO
          WriteVoc (m2tom3_with_35.Right[i],length);
          WriteC (dFile,' ');
          IF i <= l THEN
            INC (d,length+1);
          ELSIF i <= l1 THEN
            INC (d1,length+1);
          END;
        END;
      END;

      DEC (d1);   (* Laenge von ':' *)
      WriteNl (dFile);

      WITH m2tom3_with_36=PathB DO
        FOR i:=2 TO m2tom3_with_36.count DO
          IF ((d+d1+1) > MaxTabB) AND (d1>1) THEN 
            WriteTab(d);
            WriteT (dFile,": ");
            FOR j:=2 TO d1 DO
              WriteC (dFile,'.');
            END;
            WriteC (dFile,':');
            WriteNl (dFile);
            WriteTab(d);
            WriteT (dFile,": :");
            WriteNl (dFile);
            d1 := 1;
          END;
          p := ItemArrayPtr^[m2tom3_with_36.path^[i]].Prod;
          l := ItemArrayPtr^[m2tom3_with_36.path^[i]].Pos;
          WriteTab (d);
          WriteC (dFile,':');
          WriteTab (d1);
          WriteProd (p,l,d1);
          WriteNl (dFile);
        END;
      END;
      WriteTab (d);
      WriteC (dFile,':');
      WriteNl (dFile);
    END WritePartB;

PROCEDURE WritePartC (VAR d: Word.T; I: tItemIndex; t: Terminal) =
    VAR
      i,j : Word.T;
      p : tProdIndex;
      l : Word.T;
      prod : tProduction;
      d1 : Word.T;
    BEGIN
      WITH m2tom3_with_37=PathC DO
        FOR i:=m2tom3_with_37.count-1 TO 1 BY -1 DO
          IF d > MaxTabC THEN 
            WriteTab(InitTab);
            FOR j:=InitTab+1 TO d DO
              WriteC (dFile,'.');
            END;
            WriteC  (dFile,':');
            WriteNl (dFile);
            d := InitTab;
            WriteTab (d);
            WriteC (dFile,':');
            WriteNl (dFile);
          END;
          p := ItemArrayPtr^[m2tom3_with_37.path^[i]].Prod;
          l := ItemArrayPtr^[m2tom3_with_37.path^[i]].Pos;
          WriteTab (d);
          WriteProd (p,l,d);
          WriteNl (dFile);
        END;
      END;

      (* Fortsetzung fuer Reduce *)

      prod := ADR (ProdArrayPtr^[ItemArrayPtr^[I].Prod]);
      d1 := d;
      p := ItemArrayPtr^[I].Prod;
      l := ItemArrayPtr^[I].Pos;
      WriteTab (d1);
      WriteProd (p,l,d1);
      WriteNl (dFile);

      (* erlaeutere Reduce *)

      l := VocLength (prod^.Left);
      IF d >= (4+7+l) THEN 
        DEC (d,4+7+l);      (* Laenge Text 'reduce ' + Laenge linke Seite *)
      ELSE                  (* = Laenge ' -> ' *)
        WriteTab (d);
        WriteC (dFile,':');
        FOR j:=d+1 TO 4+7+l DO
          WriteC (dFile,'.');
        END;
        WriteNl (dFile);
        WriteTab (4+7+l);
        WriteC (dFile,':');
        WriteNl (dFile);
        d := 0;
      END;

      WITH m2tom3_with_38=prod^ DO
        WriteTab (d);
        WriteT (dFile,"reduce ");
        WriteVoc (m2tom3_with_38.Left,l);
        WriteT (dFile," -> ");
        IF m2tom3_with_38.Len = 0 THEN
          WriteT (dFile,"-Epsilon-");
        ELSE
          FOR i:=1 TO m2tom3_with_38.Len DO
            WriteVoc (m2tom3_with_38.Right[i],l);
            IF i < m2tom3_with_38.Len THEN
              WriteC (dFile,' ');
            END;
          END;
        END;
        WriteT (dFile,". {");
        WriteVoc (t,l);
        WriteT (dFile,"} ?");
        WriteNl(dFile);
      END;
    END WritePartC;

PROCEDURE WritePartD
  (dist: Word.T; State: tStateIndex; t: Terminal; RedItem: tItemIndex; EI: IntSets.T) =
  VAR
      Item : tItemIndex;
      prod : tProduction;
      i,j,l   : Word.T;
      d : Word.T;
      RedProd : tProduction;
  BEGIN
    RedProd := ADR (ProdArrayPtr^ [ItemArrayPtr^ [RedItem].Prod]);
    WITH m2tom3_with_39=StateArrayPtr^[State] DO
      FOR Item := m2tom3_with_39.Items TO m2tom3_with_39.Items+m2tom3_with_39.Size-1 DO
        WITH m2tom3_with_40=ItemArrayPtr^[Item] DO
          IF (m2tom3_with_40.Read = t)
             AND (NOT IntSets.IsElement (Item-m2tom3_with_39.Items, EI)) THEN
            EI := IntSets.Include (EI, Item-m2tom3_with_39.Items);
            d := InitTab;

            prod := ADR (ProdArrayPtr^[m2tom3_with_40.Prod]);
            WITH m2tom3_with_41=prod^ DO
              IF (m2tom3_with_40.Pos # ItemArrayPtr^[RedItem].Pos) OR
                 (m2tom3_with_41.Left # RedProd^.Left) THEN
                (* Drucke Trace fuer Read - Ableitung von Startzustand *)

                WriteNl (dFile);
                FindPathD (m2tom3_with_41.Left,State);

                WITH m2tom3_with_42=PathD DO
                  FOR i:=1 TO m2tom3_with_42.count - 1 DO
                    WriteTab (d);
                    WriteProd (m2tom3_with_42.path^[i].Prod,m2tom3_with_42.path^[i].Pos,d);
                    WriteNl (dFile);
                    IF d > MaxTabD THEN 
                      WriteTab(InitTab);
                      FOR j:=InitTab+1 TO d DO
                        WriteC (dFile,'.');
                      END;
                      WriteC  (dFile,':');
                      WriteNl (dFile);
                      d := InitTab;
                      WriteTab (d);
                      WriteC (dFile,':');
                      WriteNl (dFile);
                    END;
                  END;
                END;
                PathD.path := NIL;
(*WAS:          ReleaseArray (PathD.path,PathD.max,BYTESIZE(tProdPathElmt));*)

                WriteTab (d);
                WriteProd (m2tom3_with_40.Prod,0,d);
                WriteNl (dFile);

                l := VocLength (m2tom3_with_41.Left);
                IF d >= (4+7+l) THEN 
                  DEC (d,4+7+l);      (* Laenge Text 'read   ' *)
                                      (* + Laenge linke Seite *)
                ELSE                  (* + Laenge ' -> ' *)
                  WriteTab (d);
                  WriteC (dFile,':');
                  FOR j:=d+1 TO 4+7+l DO
                    WriteC (dFile,'.');
                  END;
                  WriteNl (dFile);
                  WriteTab (4+7+l);
                  WriteC (dFile,':');
                  WriteNl (dFile);
                  d := 0;
                END;
              ELSE
                (* Trace der Reduktion passt zum Read *)
                (* selbe Distanz wie bei Reduktion verwenden *)

                d := dist;
              END;

              (* erlaeutere Read *)

              WriteTab (d);
              WriteT (dFile,"read   ");
              WriteVoc (m2tom3_with_41.Left,l);
              WriteT (dFile," -> ");
              IF m2tom3_with_40.Pos = 0 THEN
                WriteC (dFile,'.');
              END;
              FOR i:=1 TO m2tom3_with_41.Len DO
                WriteVoc (m2tom3_with_41.Right[i],l);
                IF i = m2tom3_with_40.Pos THEN
                  WriteC (dFile,'.');
                ELSIF i < m2tom3_with_41.Len THEN
                  WriteC (dFile,' ');
                END;
              END;
              WriteT (dFile," ?");
            END;
            WriteNl (dFile);
          END;
        END;
      END;
    END;
    END WritePartD;

PROCEDURE MakeChainD() =
  VAR
    LastCount : M2LONGINT;
    Item, I : tItemIndex;
    State : tStateIndex;
    read  : Vocabulary;
    prod  : tProduction;

    PROCEDURE PutInChain (Item: tItemIndex; Last: tIndex) =
    VAR
      prod  : tProduction;
      State : tStateIndex;
      I     : tItemIndex;
    BEGIN

      (* Zum Item gehoerige Produktion *)

      prod := ADR (ProdArrayPtr^[ItemArrayPtr^[Item].Prod]);

      (* Betrachte alle zur Produktion gehoerigen Items *)

      WHILE (ItemArrayPtr^[Item].Pos < prod^.Len) AND
            (NOT IntSets.IsElement (Item, ChainD.reached)) DO

        (* Item in Kette eintragen *)

        WITH m2tom3_with_49=ChainD DO
          INC (m2tom3_with_49.count);
          IF m2tom3_with_49.count > m2tom3_with_49.max THEN
            (*ExtendArray (m2tom3_with_49.chain, m2tom3_with_49.max, BYTESIZE (tItemChainElmt));*)
          END;
          m2tom3_with_49.chain^ [m2tom3_with_49.count].Last := Last;
          m2tom3_with_49.chain^ [m2tom3_with_49.count].Item := Item;
          m2tom3_with_49.reached := IntSets.Include (m2tom3_with_49.reached, Item);
        END;

        (* Punkt nach rechts schieben *)

        State := ItemArrayPtr^[Item].Next;    (* Folgezustand *)
        I := StateArrayPtr^[State].Items;     (* erstes Item *)

        (* suche Item mit selber Produktion und um 1 groesserer Position *)
        WHILE (ItemArrayPtr^[I].Prod # ItemArrayPtr^[Item].Prod) OR
              (ItemArrayPtr^[I].Pos # (ItemArrayPtr^[Item].Pos+1)) DO
          INC (I);
        END;
        Item := I;
      END;
    END PutInChain;

  BEGIN

    (* Chain initialisieren *)

    WITH m2tom3_with_50=ChainD DO
      m2tom3_with_50.max := InitChainLength;
      m2tom3_with_50.count := 0;
      m2tom3_with_50.level := 0;
      m2tom3_with_50.chain
        := NEW (REF ARRAY OF tItemChainElmt, m2tom3_with_50.max+1);
(* See note in SearchPathC about MakeArray. *) 
(*WAS:MakeArray (m2tom3_with_50.chain, m2tom3_with_50.max, BYTESIZE (tItemChainElmt));*)
      m2tom3_with_50.reached:= IntSets.Empty();
      PutInChain (1, 0);

      LOOP 
        WITH m2tom3_with_51=ChainD DO
          LastCount := m2tom3_with_51.count;

          IF m2tom3_with_51.level = LastCount THEN EXIT END;

          WHILE m2tom3_with_51.level < LastCount DO
            INC (m2tom3_with_51.level);
            Item := m2tom3_with_51.chain^ [m2tom3_with_51.level].Item;

            (* Falls Nichtterminal nach dem Punkt steht, wird
               weiterverfolgt *)

            read := ItemArrayPtr^[Item].Read;
            IF (read >= MINNonTerm) AND (read <= MAXNonTerm) THEN

              (* moegliche Fortsetzungen betrachten *)

              State := ItemArrayPtr^[Item].Number;
              FOR I := StateArrayPtr^[State].Items TO
                       StateArrayPtr^[State].Items + StateArrayPtr^[State].Size - 1 DO
                WITH m2tom3_with_52=ItemArrayPtr^ [I] DO
                  prod := ADR (ProdArrayPtr^[m2tom3_with_52.Prod]);
                  IF (prod^.Left = read) AND 
                     (ItemArrayPtr^[I].Pos = 0) THEN

                    PutInChain (I, m2tom3_with_51.level);
                   
                  END;
                END;
              END;
            END;
          END;
        END;
      END;
    END;
  END MakeChainD;

PROCEDURE FindPathD (NT: NonTerminal; EndState: tStateIndex) =
    VAR 
      last, level : M2LONGINT;
      prod : tProduction;
      I : tItemIndex;
      Depth : tIndex;
  BEGIN

    (* evtl. (d.h. beim ersten mal) Kette aufbauen *)

    IF ChainD.max = 0 THEN
      MakeChainD();
    END;

    WITH m2tom3_with_56=ChainD DO

      (* Item suchen *)

      last := 0;
      LOOP
        INC (last);
        I := m2tom3_with_56.chain^ [last].Item;
        IF (ItemArrayPtr^[I].Number = EndState) THEN
          prod := ADR (ProdArrayPtr^[ItemArrayPtr^[I].Prod]);
          IF NT = prod^.Left THEN
            EXIT;
          END;
        END;
      END;

      (* Tiefe bestimmen *)

      Depth := 0;
      m2tom3_with_56.level := last;

      WHILE m2tom3_with_56.level # 0 DO
        INC (Depth);
        m2tom3_with_56.level := m2tom3_with_56.chain^ [m2tom3_with_56.level].Last;
      END;

      (* Chain in Path uebertragen *)
   
      WITH m2tom3_with_57=PathD DO
        m2tom3_with_57.count := Depth;
        m2tom3_with_57.max   := Depth;
        m2tom3_with_57.path
          := NEW (REF ARRAY OF tProdPathElmt, m2tom3_with_57.max+1);
(* See note in SearchPathC about MakeArray. *) 
(*WAS:  MakeArray (m2tom3_with_57.path, m2tom3_with_57.max, BYTESIZE (tProdPathElmt));*)
      END;

      m2tom3_with_56.level := last;
      WHILE Depth > 0 DO
        I := m2tom3_with_56.chain^ [m2tom3_with_56.level].Item;
        PathD.path^ [Depth].Prod := ItemArrayPtr^[I].Prod;
        PathD.path^ [Depth].Pos  := ItemArrayPtr^[I].Pos;
        DEC (Depth);
        m2tom3_with_56.level := m2tom3_with_56.chain^[m2tom3_with_56.level].Last;
      END;
    END;
  END FindPathD;

PROCEDURE WriteProd (p: tProdIndex; l: tIndex; VAR d: Word.T) =
    VAR
      prodADR : (*tProduction*) ADDRESS;
      prod : tProduction;
      i : tIndex;
      length  : Word.T;
    BEGIN
      prodADR := ADR(ProdArrayPtr^[p]);
      prod := LOOPHOLE (prodADR, tProduction);
      WITH m2tom3_with_59=prod^ DO
        IF m2tom3_with_59.Len = 0 THEN
          WriteT (dFile,"-Epsilon-");
        ELSE
          FOR i:=1 TO m2tom3_with_59.Len DO
            WriteVoc (m2tom3_with_59.Right[i],length);
            WriteC (dFile,' ');
            IF i <= l THEN
              INC (d,length+1);
            END;
          END;
        END;
      END;
    END WriteProd;

PROCEDURE WriteVoc (voc: Vocabulary; VAR length: Word.T) =
    VAR
      sym : tIdent;
      str : tString;
      err : TokenError;
      i : Word.T;
    BEGIN
      sym := TokenToSymbol (voc,err);
      GetString (sym,str);
      length := Length (str);
      FOR i := 1 TO length DO
        WriteC (dFile,Char (str, i));
      END;
    END WriteVoc;

PROCEDURE VocLength (voc: Vocabulary): Word.T =
    VAR
      sym : tIdent;
      str : tString;
      err : TokenError;
    BEGIN
      sym := TokenToSymbol (voc,err);
      GetString (sym,str);
      RETURN Length (str);
    END VocLength;
    
PROCEDURE WriteTab (d: Word.T) =
    VAR i : Word.T;
    BEGIN
      FOR i := 1 TO d DO
        WriteC (dFile,' ');
      END;
    END WriteTab;

BEGIN
  NoTrace := FALSE;
  Fast := FALSE;
  ChainD.max := 0;
END Debug.

