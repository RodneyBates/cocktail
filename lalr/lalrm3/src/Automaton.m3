(* handle LR automaton *)

(* $Id: Automaton.mi,v 2.2 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Automaton.mi,v $
 * Revision 2.2  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:31:33  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.4  90/09/20  17:52:34  grosch
 * calmed down lint
 * 
 * Revision 1.3  90/09/10  16:25:43  grosch
 * added automatic alignment for ProdArray
 * 
 * Revision 1.2  90/06/12  16:53:36  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.1  89/01/12  18:08:51  vielsack
 * supply a line number for each action
 * 
 * Revision 1.0  88/10/04  14:35:50  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

 UNSAFE MODULE Automaton;

FROM SYSTEM IMPORT M2LONGINT;
IMPORT Word;
FROM Continue   IMPORT Value, ValueNonterms;
FROM DynArray   IMPORT MakeArray, ExtendArray;
FROM FrontErrors     IMPORT eFatal, eError, eWarning, eInformation, eIdent, eString,
                        eInternal, ErrorMessage, ErrorMessageI, CrashT;
FROM Lists      IMPORT MakeList, tList;
FROM Oper       IMPORT OperKind, InitPrioReading, GetPriority, GetOperator;
FROM Rules      IMPORT Operation, Expression, InitRulesReading, GetNodeOperation,
                        GetRule, GetBracketNode, GetUnaryNode, GetBinaryNode,
                        GetLeafNode, GetActionNode, NoExpression;
FROM Sets       IMPORT MakeSet, ReleaseSet, AssignEmpty, Include, Extract,
                        IsEmpty, IsElement, ForallDo, tSet;
IMPORT IntSets;
FROM Strings    IMPORT tString, TextToString, ArrayToString;
FROM Idents     IMPORT tIdent, MakeIdent;
FROM SYSTEM     IMPORT HALT, SHORTCARD, WORD  ;
FROM General    IMPORT MaxAlign;
FROM Positions  IMPORT NoPosition;
FROM TokenTab   IMPORT EndOfToken, MAXTerm, MINNonTerm, MAXNonTerm, cMAXNonTerm,
                        PosType, TokenError, Prio, Terminal, NonTerminal, Vocabulary,
                        TokenToSymbol, MakeVoc;

  CONST
    eNoBNF      = 60;
    eActInside  = 61;

    InitProdCount  = 1000;  (* Anfangsplatzgroesse fuer Produktionen in WORD *)
    InitItemCount  = 200;   (* Anfangsplatzgroesse fuer Items *)
    InitStateCount = 50;    (* Anfangsplatzgroesse fuer States *)
    InitListCount  = 4;     (* Anfangsplatzgroesse fuer ProdList *)
    InitHashListCount = 4;  (* Anfangsplatzgroesse fuer HashList *)
    InitStackCount = 10;    (* Anfangsplatzgroesse fuer ActionStack *)
    InitRelationListCount = 10; (* Anfagsplatxgroesse fuer Relationlisten *)

  TYPE
    HashIndex = [0..99];

    tDummyProduction =         (* vgl. tProduction in Def.-Module *)
      RECORD
        ProdNo  : tIndex;
        Reduce  : tIndexList;
        Act     : tList;
        ActPos  : PosType;
        Ass     : tAss;
        Pri     : Prio;
        Len     : tIndex;
        Left    : NonTerminal;
      END;
    
    tDummyRight4 = ARRAY [1..4] OF (*SHORTCARD*) [0..cMAXNonTerm];
    
    tStackElmt = RECORD
        Act     : tList;
        ActPos  : PosType;
        Voc     : Vocabulary; 
      END;

  VAR
    ProdElmtCount  : M2LONGINT;            (* aktuelle Feldgroesse *)
    ProductionADR  : (*tProduction*) ADDRESS;
    Production     : tProduction;        (* Index akt. bzw. naechsten P.*)
    ItemElmtCount  : M2LONGINT;            (* aktuelle Feldgroesse fuer I. *)
    StateElmtCount : M2LONGINT;            (* aktuelle Feldgroesse fuer S. *)
    StateHashList  : ARRAY               (* Hashtabelle fuer States     *)
                     HashIndex OF tIndexList;
    StackArrayPtr  : REF ARRAY         (* Stack fuer nichtbearbeitete *)
                     OF tStackElmt; (* NonTerminale, Aktionen *)
    StackElmtCount : M2LONGINT;            (* Stackgroesse *)
    StackIndex     : M2LONGINT;            (* Index Top of Stack *)
    
    i         : Word.T;  (* Schleifenzaehler *)
    prio      : Word.T;  (* Prioritaet der aktuellen Produktion
                              fuer InsertProductions und InsertRight *)
    NonTermNo : Word.T;
    ProdSet   : IntSets.T;

PROCEDURE InitAutomaton() =

  (* Initialisiert den Automat, d.h. die zur Automatenkonstruktion
     noetigen Daten werden vom Module Rules uebernommen *)

  BEGIN
    IsBnf := TRUE;
    InsertOperators();
    InsertProductions();
  END InitAutomaton;

PROCEDURE MakeFirstState (): tStateIndex =
  VAR 
    new : BOOLEAN;
    pi : tProdIndex;
    prod : tProduction;
    read : Vocabulary;
  BEGIN

    (* Bilde einen neun Zustand *)

    NextState();
    INC (StateArrayPtr^[StateIndex].Size);

    pi := ProdList[StartSymbol].Array^[1].Index;
    prod := ADR (ProdArrayPtr^[pi]);
    read := prod^.Right [1];

    (* Beschaffe neues Item *)

    NextItem (read);

    (* Trage die Produktion mit dem neuen Startsymbol ein *)

    ItemArrayPtr^[ItemIndex].Prod := pi;
    ItemArrayPtr^[ItemIndex].Pos  := 0;

    (* Hilfsmenge fuer Closure *)

    ProdSet := IntSets.Empty();

    (* Bilde Huelle *)

    Closure (read);
    RETURN UniqueState (new);
  END MakeFirstState;

PROCEDURE GotoSet (Index: tStateIndex; VAR Set: IntSets.T) =
  VAR
    v  : Vocabulary;
    i  : tItemIndex;
    pr : tProdIndex;
    po : tIndex;
    p : tProduction;
  BEGIN
    Set := IntSets . Empty();
    WITH m2tom3_with_1=StateArrayPtr^[Index] DO   (* State *)
      FOR i:= m2tom3_with_1.Items TO m2tom3_with_1.Items + m2tom3_with_1.Size - 1 DO

      (* Symbol nach dem Punkt ist zu bearbeiten *)

        v  := ItemArrayPtr^[i].Read;
        IF (v <= MAXNonTerm) THEN   (* gibt es ein naechstes Symbol *)
          Set := IntSets.Include(Set,v) (* trage es ein *);
        END;
      END;
    END;
  END GotoSet;

PROCEDURE Goto (Index: tStateIndex; Symbol: Vocabulary; VAR new: BOOLEAN): tStateIndex =
  VAR
    pADR : (*tProduction*) ADDRESS;
    p : tProduction;
    i : tItemIndex;
    pr: tProdIndex;
    po: tIndex;
    s : tStateIndex;
    prod : tProduction;
    read : Vocabulary;
  BEGIN
    (* Beschaffe neuen State *)

    NextState();

    (* Set fuer Closure initialisieren *)

    ProdSet := IntSets . Empty();

    WITH m2tom3_with_2=StateArrayPtr^[Index] DO   (* State *)

      (* Fuer alle Items *)

      FOR i:=m2tom3_with_2.Items TO m2tom3_with_2.Items + m2tom3_with_2.Size - 1 DO

        (* Mit Symbol nach den Punkt *)

        IF (ItemArrayPtr^[i].Read = Symbol) THEN

          pr := ItemArrayPtr^[i].Prod;
          po := ItemArrayPtr^[i].Pos;
          pADR := ADR(ProdArrayPtr^[pr]);
          p := LOOPHOLE (pADR, tProduction);

          (* erweitere den Zustand *)
          IF ((po+1) < p^.Len) THEN
            read :=  p^.Right[po+2];
          ELSE
            read := MAXNonTerm + 1;
          END;

          INC (StateArrayPtr^[StateIndex].Size);
          NextItem (read);

          ItemArrayPtr^[ItemIndex].Prod := pr;
          ItemArrayPtr^[ItemIndex].Pos  := po+1;

          IF (read >= MINNonTerm) AND (read <= MAXNonTerm) THEN
            Closure (p^.Right[po+2]);
          END;
        END;
      END;
    END;                          (* State *)

    s := UniqueState(new);

   (* Trage den berechneten State in Next ein *)

    WITH m2tom3_with_3=StateArrayPtr^[Index] DO   (* State *)

      (* Fuer alle Items *)

      FOR i:=m2tom3_with_3.Items TO m2tom3_with_3.Items + m2tom3_with_3.Size - 1 DO

      (* nach dem Punkt ist zu bearbeiten *)

        (* Mit Symbol nach den Punkt *)

        IF ItemArrayPtr^[i].Read = Symbol THEN
          
           (* Trage den Folgezustand ein *)

           ItemArrayPtr^[i].Next := s;
        END;
      END;
    END;                          (* State *)
    RETURN s;
  END Goto;

PROCEDURE Closure (Symbol: NonTerminal) =
  VAR
    i,u : tIndex;
    read : Vocabulary;
    pr : tProdIndex;
    po : tIndex;
    exists : BOOLEAN;
    p : tProduction;
  BEGIN
      WITH m2tom3_with_4=StateArrayPtr^[StateIndex] DO
        WITH m2tom3_with_5=ProdList[Symbol] DO    (* Production *) 
          u := m2tom3_with_5.Used;
          FOR i := 1 TO u DO
            
            (* Fuege ein Item hinzu, falls dies noch nicht vorhanden *)

            pr := m2tom3_with_5.Array^[i].Index;
            p := ADR (ProdArrayPtr^[pr]);

            IF NOT IntSets.IsElement (p^.ProdNo, ProdSet) THEN
              ProdSet := IntSets.Include (ProdSet, p^.ProdNo);
              INC(m2tom3_with_4.Size);

              (* read bestimmen *)

              WITH m2tom3_with_6=p^ DO
                IF m2tom3_with_6.Len > 0 THEN
                  read := m2tom3_with_6.Right [1];
                ELSE
                  read := MAXNonTerm + 1;
                END;
              END;

              NextItem (read);
              WITH m2tom3_with_7=ItemArrayPtr^[ItemIndex] DO    (* Item *)
                m2tom3_with_7.Prod := pr;
                m2tom3_with_7.Pos  := 0;
              END;                      (* Item *)

              (* Falls Punkt vor Nichtterminal steht
                 ist dieser auch zu bearbeiten *)
              
              IF (read >= MINNonTerm) AND (read <= MAXNonTerm) THEN
                Closure (read);
              END;
            END;
          END;
        END;               (* Production *)
      END;               (* State *)
  END Closure;

PROCEDURE UniqueState (VAR new: BOOLEAN): tStateIndex =
  VAR
    h: HashIndex;
    i: M2LONGINT;
  BEGIN
    h := HashCode (StateIndex);
    WITH m2tom3_with_13=StateHashList[h] DO
      
      (* Pruefe ob der State bereits vorhanden *)

      FOR i:=1 TO m2tom3_with_13.Used DO
        IF AreEqualStates (StateIndex,m2tom3_with_13.Array^[i]) THEN
          (* State ist bereits vorhanden *)

          (* Speicher freigeben *)

          (* Items freigeben *)
          DEC (ItemIndex, StateArrayPtr^[StateIndex].Size);

          (* State freigeben *)
          DEC (StateIndex);

          (* bereits bekannten State zurueckgeben *)

          new := FALSE;
          RETURN m2tom3_with_13.Array^[i];
        END;
      END;

      (* neuen State in Hashtabelle eintragen *)

      IF m2tom3_with_13.Used = 0 THEN
        m2tom3_with_13.Count := InitHashListCount;
        m2tom3_with_13.Array := NEW ( REF ARRAY OF tIndex, m2tom3_with_13.Count );
(*WAS: MakeArray (m2tom3_with_13.Array,m2tom3_with_13.Count,BYTESIZE(tIndex));*)
      ELSIF m2tom3_with_13.Used >= m2tom3_with_13.Count THEN
        (*ExtendArray (m2tom3_with_13.Array,m2tom3_with_13.Count,BYTESIZE(tIndex));*)
      END;
      INC (m2tom3_with_13.Used);
      m2tom3_with_13.Array^[m2tom3_with_13.Used] := StateIndex;
      new := TRUE;
      RETURN StateIndex;
    END;
  END UniqueState;
  
PROCEDURE InsertOperators() =

  (* Einlesen des Abschnitts Oper, es werden steigende Prioritaeten zugeordnet *)

  VAR
    o : tOper;
    t : Vocabulary;
    kn : OperKind;
    ps,cmp : PosType;
    cm : tList;
  BEGIN
    o.Pri := 0;
    InitPrioReading();
      WHILE GetPriority (kn,ps,cm,cmp) DO
        IF kn = OperKind.Left THEN
          o.Ass := tAss.left;
        ELSIF kn = OperKind.Right THEN
          o.Ass := tAss.right;
        ELSE
          o.Ass := tAss.nonassoc;
        END;
        INC (o.Pri);
        WHILE GetOperator (t,ps) DO
          OperArray [t] := o;
        END;
      END;
  END InsertOperators;

PROCEDURE InsertProductions() =

  (* Die Produktionen werden vom Module Rules eingelesen *)

  VAR
    left  : NonTerminal;
    lfp,clp,cmp,pnp,prp,prsp : PosType;
    right : Expression;
    cm    : tList;
    hpr   : BOOLEAN;
    prs   : Terminal;
    act   : tList;
    actpos: PosType;
    voc   : Vocabulary;
    index : tProdIndex;
    maxIndex : tProdIndex;
    value : SHORTCARD;
    prodADR      : (*tProduction*) ADDRESS;
    prod  : tProduction;
    i     : SHORTCARD;
  BEGIN

    (* Lese erste Regel *)

    InitRulesReading();
    IF NOT GetRule (left,lfp,clp,right,cm, cmp,pnp,hpr,prp,prs,prsp) THEN
      CrashT ("Automaton.InsertProduction");
    END;

    (* Fuehre ein neues Startsymbol ein *)

    WITH m2tom3_with_14=Production^ DO
      MakeList (m2tom3_with_14.Act);
      m2tom3_with_14.ActPos := NoPosition;
      m2tom3_with_14.Ass := tAss.none;
      m2tom3_with_14.Pri := 0;
      m2tom3_with_14.Len := 0;
    END;
    EnsureProdArray();
    WITH m2tom3_with_15=Production^ DO
      INC (m2tom3_with_15.Len);
      m2tom3_with_15.Right[m2tom3_with_15.Len] := left;
    END;
    EnsureProdArray();
    WITH m2tom3_with_16=Production^ DO
      INC (m2tom3_with_16.Len);
      m2tom3_with_16.Right[m2tom3_with_16.Len] := EndOfToken;
    END;
    StartSymbol := MakeNonTerm();
    Production^.Left := StartSymbol;
    NextProduction();

    (* Uebertrage die Regeln *)

    InitRulesReading();
    WHILE GetRule (left,lfp,clp,right,cm,cmp,pnp,hpr,prp,prs,prsp) DO
      WITH m2tom3_with_17=Production^ DO
        MakeList (m2tom3_with_17.Act);
        m2tom3_with_17.ActPos := NoPosition;
        m2tom3_with_17.Ass := tAss.none;         (* Initialisierung auf keine Associativitaet *)
        m2tom3_with_17.Pri := 0;         (* und minimale Prioritaet *)
        m2tom3_with_17.Len := 0;
      END;
      InsertRight (right,TRUE);
      WITH m2tom3_with_18=Production^ DO
        m2tom3_with_18.Left := left;
        prio := OperArray[prs].Pri;
        IF hpr THEN
          (* explizite Prioritaet geht vor *)
          m2tom3_with_18.Pri := OperArray[prs].Pri;
          m2tom3_with_18.Ass := OperArray[prs].Ass;
        END;
      END;
      NextProduction();
    END;

    (* Trage Regeln fuer innere semantische Ankopplungen nach *)

    WHILE PopAction (act,voc,actpos) DO
      WITH m2tom3_with_19=Production^ DO
        m2tom3_with_19.Act := act;
        m2tom3_with_19.ActPos := actpos;
        m2tom3_with_19.Pri := 0;
        m2tom3_with_19.Ass := tAss.none;
        m2tom3_with_19.Len := 0;
        m2tom3_with_19.Left := voc;
      END;
      NextProduction();
    END;

    ValueNonterms();

    maxIndex := ProdIndex;
    index := 0;
    WHILE index < maxIndex DO
      prodADR := ADR(ProdArrayPtr^[index]);
      prod := LOOPHOLE (prodADR, tProduction);
      value := 0;
      WITH m2tom3_with_20=prod^ DO
        FOR i := 1 TO m2tom3_with_20.Len DO
          INC (value, Value[m2tom3_with_20.Right[i]]);
        END;
      END;
      PutInProdList (index, value);
      index := NextProdIndex(index);
    END;
  END InsertProductions;

PROCEDURE InsertRight (Expr: Expression; Last: BOOLEAN) =
  
  (* Uebertrage einen Teilbaum in die rechte Seite der Regel 
     wenn eine Konstruktion angetroffen wird die nicht BNF 
     d.h., die nicht zulaessig ist wird eine Fehlermeldung ausgegeben
     und IsBnf auf false gesetzt *)

  VAR
    pos,secpos : PosType;
    son,rson,lson : Expression;
    art : Operation;
    voc : Vocabulary;
    act : tList;
    sym : tIdent;
    err : TokenError;
  BEGIN
    CASE GetNodeOperation(Expr) OF
      Operation.Plus, Operation.Star =>
        IsBnf := FALSE;
        GetUnaryNode (Expr,pos,son);
        InsertRight (son,Last);
        ErrorMessage (eNoBNF,eError,pos);
    |  Operation.Bracket =>
        GetBracketNode (Expr,pos,secpos,son);
        ErrorMessage (eNoBNF,eWarning,pos);
        InsertRight (son,Last);
    | Operation.Optional =>
        IsBnf := FALSE;
        GetBracketNode (Expr,pos,secpos,son);
        ErrorMessage (eNoBNF,eError,pos);
    | Operation.Sequence =>
        GetBinaryNode (Expr,pos,lson,rson);
        IF rson = NoExpression THEN
          InsertRight (lson,Last);
        ELSE
          InsertRight (lson,FALSE);
        END;
        InsertRight (rson,Last);
    | Operation.Separator, Operation.Alternative=>
        IsBnf := FALSE;
        GetBinaryNode (Expr,pos,lson,rson);
        InsertRight (lson,FALSE);
        ErrorMessage (eNoBNF,eError,pos);
        InsertRight (rson,FALSE);
    | Operation.TermLeaf=>
        IF IsBnf THEN
          EnsureProdArray();
          GetLeafNode (Expr,voc,pos);
          WITH m2tom3_with_21=Production^ DO
            INC (m2tom3_with_21.Len);
            m2tom3_with_21.Right[m2tom3_with_21.Len] := voc;
            IF OperArray [voc].Ass # tAss.none THEN
              (* der letzte Operator innerhalb der Regel gilt *)
              m2tom3_with_21.Ass := OperArray[voc].Ass;
              m2tom3_with_21.Pri := OperArray[voc].Pri;
            END;
          END;
        END;
    | Operation.NonTermLeaf=>
        IF IsBnf THEN
          EnsureProdArray();
          GetLeafNode (Expr,voc,pos);
          WITH m2tom3_with_22=Production^ DO
            INC (m2tom3_with_22.Len);
            m2tom3_with_22.Right[m2tom3_with_22.Len] := voc;
          END;
        END;
    | Operation.Action=>
        IF IsBnf THEN
          GetActionNode (Expr,act,pos);
          IF Last THEN
            Production^.Act := act;
            Production^.ActPos := pos;
          ELSE
            EnsureProdArray();
            voc := MakeNonTerm ();
            sym := TokenToSymbol (voc,err);
            ErrorMessageI (eActInside, eInformation, pos, eIdent, ADR (sym));
            WITH m2tom3_with_23=Production^ DO
              INC (m2tom3_with_23.Len);
              m2tom3_with_23.Right[m2tom3_with_23.Len] := voc;
            END;
            PushAction (act,voc,pos);
          END;
        END;
    | Operation.NoOperation=>
    END;
  END InsertRight;

PROCEDURE PutInProdList (index: tProdIndex; value: SHORTCARD) =

  (* Die angegebene  Produktion wird gem. ihrer linken Seite in die
     zugh. ProdList sortiert eingetragen *)
  
  VAR
    prod : tProduction;
    i    : tIndex;
  BEGIN
    prod := ADR (ProdArrayPtr^[index]);
    WITH m2tom3_with_24=ProdList[prod^.Left] DO
      IF m2tom3_with_24.Used = 0 THEN
        m2tom3_with_24.Count := InitListCount;
        m2tom3_with_24.Array := NEW (REF ARRAY OF tProdListElmt, m2tom3_with_24.Count);
(*WAS:  MakeArray (m2tom3_with_24.Array,m2tom3_with_24.Count,BYTESIZE(tProdListElmt));*)
        INC (m2tom3_with_24.Used);
        m2tom3_with_24.Array^[m2tom3_with_24.Used].Index := index; 
        m2tom3_with_24.Array^[m2tom3_with_24.Used].Value := value; 
      ELSE
        IF m2tom3_with_24.Used >= m2tom3_with_24.Count THEN
          (*ExtendArray (m2tom3_with_24.Array,m2tom3_with_24.Count,BYTESIZE(tProdListElmt));*)
        END;
        (* laengere Produktionen nach hinten verschieben *)
        i := m2tom3_with_24.Used;
        WHILE (i > 0) AND (m2tom3_with_24.Array^[i].Value > value) DO
          m2tom3_with_24.Array^[i+1].Index := m2tom3_with_24.Array^[i].Index;
          m2tom3_with_24.Array^[i+1].Value := m2tom3_with_24.Array^[i].Value;
          DEC (i);
        END;
        INC (i);
        (* neue Produktion eintragen *)
        m2tom3_with_24.Array^[i].Index := index;
        m2tom3_with_24.Array^[i].Value := value;
        INC (m2tom3_with_24.Used);
      END;
    END;
  END PutInProdList;

PROCEDURE NextProduction() =

  (* Schalte die aktuelle Produktion weiter *)
  (* wie immer nach dem ausfuellen einer Produktion aufgerufen *)

  BEGIN
    INC (ProdCount);
    WITH m2tom3_with_25=Production^ DO
      m2tom3_with_25.ProdNo := ProdCount;
      m2tom3_with_25.Reduce.Used := 0;
    END;
    ProdIndex := NextProdIndex(ProdIndex);
    IF (ProdIndex + ((BYTESIZE(tDummyProduction) + MaxAlign - 1) DIV MaxAlign * MaxAlign)) >= ProdElmtCount THEN
      (*ExtendArray (ProdArrayPtr, ProdElmtCount, BYTESIZE(WORD));*)
    END;
    ProductionADR := ADR(ProdArrayPtr^[ProdIndex]);
    Production := LOOPHOLE (ProductionADR, tProduction);
  END NextProduction;

PROCEDURE NextProdIndex (Index: tProdIndex): tProdIndex =
  VAR 
    diff : Word.T;
    prod : tProduction;
  BEGIN
    prod := ADR (ProdArrayPtr^[Index]);
            (* Platzbedarf fuer konstantlangen Teil *)
    diff := LOOPHOLE ((BYTESIZE(tDummyProduction) + MaxAlign - 1) DIV MaxAlign * MaxAlign,Word.T)
              (* Platzbedarf fuer variabellangen Teil *)
            + (((prod^.Len+3) DIV 4) * BYTESIZE(tDummyRight4));
    RETURN Index + ((diff-1) DIV BYTESIZE (WORD)) + 1;
  END NextProdIndex;

PROCEDURE EnsureProdArray() =

  (* stelle sicher, dass in die rechte Seite der Produktion noch um
     mindestes eins verlaengert werden kann *)

  VAR diff : M2LONGINT;
  BEGIN
            (* Platzbedarf fuer konstantlangen Teil *)
    diff := LOOPHOLE ((BYTESIZE(tDummyProduction) + MaxAlign - 1) DIV MaxAlign * MaxAlign,Word.T)
              (* Platzbedarf fuer variabellangen Teil *)
            + ((((Production^.Len+1)+3) DIV 4) * BYTESIZE(tDummyRight4));
    IF (ProdIndex + ((diff-1) DIV BYTESIZE(WORD)) + 1) >= ProdElmtCount THEN
      (*ExtendArray (ProdArrayPtr, ProdElmtCount, BYTESIZE(WORD));*)
      ProductionADR := ADR(ProdArrayPtr^[ProdIndex]);
      Production := LOOPHOLE (ProductionADR, tProduction);
    END;
  END EnsureProdArray;

PROCEDURE NextItem (ReadSym: Vocabulary) = (* Beschaffe das naechste Item *)
  BEGIN
    INC (ItemIndex);
    IF ItemIndex > ItemElmtCount THEN
      (*ExtendArray (ItemArrayPtr, ItemElmtCount, BYTESIZE(tItem));*)
      IF ItemArrayPtr = NIL THEN HALT(); END;
    END;
    WITH m2tom3_with_26=ItemArrayPtr^[ItemIndex] DO
      m2tom3_with_26.EmptyReadSet := TRUE;
      m2tom3_with_26.Relation.Used := 0;
      m2tom3_with_26.Relation.Count := InitRelationListCount;
      m2tom3_with_26.Read := ReadSym;
      m2tom3_with_26.Rep := tRep.NoRep;
      m2tom3_with_26.RepNo := Infinite;
      m2tom3_with_26.Next := Infinite;
      m2tom3_with_26.Number := 0;
    END;
  END NextItem;
      
PROCEDURE NextState () =

  (* Beschaffe den naechsten State und initialisiere ihn mit
     dem naechsten (aktuellen+1) Item *)

  BEGIN
    INC (StateIndex);
    IF StateIndex > StateElmtCount THEN
      (*ExtendArray (StateArrayPtr, StateElmtCount, BYTESIZE(tState));*)
    END;
    WITH m2tom3_with_27=StateArrayPtr^[StateIndex] DO
      m2tom3_with_27.Size := 0;
      m2tom3_with_27.Items := ItemIndex+1;
      m2tom3_with_27.NewNumber := Infinite;
      m2tom3_with_27.Kind := tStateKind.sNone;
    END;
  END NextState;
  
PROCEDURE MakeNonTerm (): NonTerminal = (* Erzeuge ein neues Nichtterminal *)
  VAR
    s : tString;
    max,i,j : Word.T;
    pos : PosType;
    voc : Vocabulary;
  BEGIN
    s.Chars[1] := '_';
    s.Length := 6;
    max := MAXNonTerm;
    REPEAT
      i := NonTermNo;
      FOR j:=5 TO 2 BY -1 DO
        s.Chars[j]:=VAL(ORD('0')+(i MOD 10),CHAR);
        i := i DIV 10;
      END;
      s.Chars[6] := '_';
      pos := NoPosition;
      INC(NonTermNo);
      voc := MakeVoc (MakeIdent (s),pos);
    UNTIL max < MAXNonTerm;
    RETURN voc;
  END MakeNonTerm;

PROCEDURE AreEqualStates (Index1, Index2: tStateIndex): BOOLEAN =

(* FIX: This algorithms depends on the items of set-equal item sets
        being in the same order.  The set construction does not ensure
        this. E.g., this grammar: S -> C | D | E | F 
                                  C -> c A
                                  D -> c B 
                                  E -> e B
                                  F -> e A
                                  A -> g a 
                                  B -> g b 
        which produces, among others, item sets
           { A -> g . a     and  { B -> g . b 
           , B -> g . b }        , A -> g . a } 
        This machine will still parse correctly, but has too many states. 
*) 
  VAR
    i1,i2 : tItemIndex;
    l1,l2 : tItemIndex;
  BEGIN
    i1 := StateArrayPtr^[Index1].Items;
    i2 := StateArrayPtr^[Index2].Items;
    l1 := StateArrayPtr^[Index1].Size;
    l2 := StateArrayPtr^[Index2].Size;
    IF l1 # l2 THEN RETURN FALSE END;
    INC (l1,i1);
    INC (l2,i2);
    WHILE (i1 < l1) AND (i2 < l2) DO
      IF ItemArrayPtr^[i1].Prod # ItemArrayPtr^[i2].Prod THEN RETURN FALSE; END;
      IF ItemArrayPtr^[i1].Pos  # ItemArrayPtr^[i2].Pos  THEN RETURN FALSE; END;
      INC (i1);
      INC (i2);
    END;
    IF    (i1 < l1) THEN RETURN ItemArrayPtr^[i1].Pos = 0;
    ELSIF (i2 < l2) THEN RETURN ItemArrayPtr^[i2].Pos = 0;
    ELSE RETURN TRUE;
    END;
  END AreEqualStates;

PROCEDURE HashCode (Index: tStateIndex): HashIndex =
  BEGIN
    WITH m2tom3_with_28=ItemArrayPtr^[StateArrayPtr^[Index].Items] DO
      RETURN ((m2tom3_with_28.Prod+m2tom3_with_28.Pos) MOD (LAST(HashIndex)-FIRST(HashIndex)+1)) + FIRST(HashIndex);
    END;
  END HashCode;
      
PROCEDURE PushAction (act: tList; voc: Vocabulary; actpos: PosType) =
  BEGIN
    INC (StackIndex);
    IF StackElmtCount = 0 THEN
      StackElmtCount := InitStackCount;
      StackArrayPtr := NEW (REF ARRAY OF tStackElmt, StackElmtCount);
(*WAS:MakeArray (StackArrayPtr,StackElmtCount,BYTESIZE(tStackElmt));*)
    ELSIF StackIndex > StackElmtCount THEN
      (*ExtendArray (StackArrayPtr,StackElmtCount,BYTESIZE(tStackElmt));*)
    END;
    StackArrayPtr^[StackIndex].Act := act;
    StackArrayPtr^[StackIndex].ActPos := actpos;
    StackArrayPtr^[StackIndex].Voc := voc;
  END PushAction;

PROCEDURE PopAction (VAR act: tList; VAR voc: Vocabulary; VAR actpos: PosType): BOOLEAN =
  BEGIN
    IF StackIndex < 1 THEN RETURN FALSE; END;
    act := StackArrayPtr^[StackIndex].Act;
    actpos := StackArrayPtr^[StackIndex].ActPos;
    voc := StackArrayPtr^[StackIndex].Voc;
    DEC (StackIndex);
    RETURN TRUE;
  END PopAction;

BEGIN
  ProdElmtCount := InitProdCount;
  ProdArrayPtr := NEW (REF ARRAY OF WORD, ProdElmtCount);
(*WAS:  MakeArray (ProdArrayPtr, ProdElmtCount, BYTESIZE(WORD));*)

  ItemElmtCount := InitItemCount;
  ItemArrayPtr := NEW(REF ARRAY OF tItem, ItemElmtCount);
(*WAS:  MakeArray (ItemArrayPtr, ItemElmtCount, BYTESIZE(tItem));*)

  StateElmtCount := InitStateCount;
  StateArrayPtr := NEW (REF ARRAY OF tState, StateElmtCount);
(*WAS:  MakeArray (StateArrayPtr, StateElmtCount, BYTESIZE(tState));*)

  FOR i := FIRST(NonTerminal) TO LAST(NonTerminal) DO
    ProdList[i].Used := 0;
  END;

  FOR i := FIRST(HashIndex) TO LAST(HashIndex) DO
    StateHashList[i].Used := 0;
  END;

  FOR i:= FIRST(Terminal) TO LAST (Terminal) DO
    WITH m2tom3_with_29=OperArray[i] DO
      m2tom3_with_29.Ass := tAss.none;
      m2tom3_with_29.Pri := 0;
    END;
  END;

  ProdCount := 0;
  ProdIndex := 0;
  ProductionADR := ADR(ProdArrayPtr^[ProdIndex]);
  Production := LOOPHOLE (ProductionADR, tProduction);
  ItemIndex := 0;
  StateIndex := 0;
  StackElmtCount := 0;
  StackIndex := 0;
END Automaton.

