(* compute default states *)

(* $Id: Default.mi,v 1.2 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Default.mi,v $
 * Revision 1.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/12  16:54:01  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0	 88/10/04  14:36:10  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE Default;

FROM SYSTEM IMPORT M2LONGINT, SHORTCARD;
IMPORT IntSets;
FROM Automaton	IMPORT tStateIndex;
FROM DynArray	IMPORT MakeArray;
FROM Gen	IMPORT tTableLine, FirstTerminal, LastTerminal, FirstSymbol, LastSymbol, LastReadState;
FROM Memory	IMPORT Alloc;
FROM Sets	IMPORT tSet, MakeSet, IsEqual, IsSubset, Include, Card;
 
FROM TokenTab	IMPORT Vocabulary;

  CONST NoState	 = 0;

  TYPE
    tTrans  = UNTRACED BRANDED REF  tTran;		   (* Uebergange *)

    tTran   = RECORD			   (* Uebergang*)
		Voc   : Vocabulary;
		State : tStateIndex;	   (* Folgezustand *)
		Next  : tTrans;		   (* weitere Uebergaenge *)
	      END;

    tLine   = RECORD
		Transitions: tTrans;	   (* Uebergaenge sortiert nach Voc *)
		Terms	   : IntSets.T;	   (* Terminale fuer die es einen Uebergang gibt *)
		Succ	   : tStateIndex;  (* Nachfolger in sortierter Liste *)
		DefaultState : tStateIndex;(* Defaultzustand *)
		Saving	   : SHORTCARD;	   (* Einsparung durch Defaultzustand *)
		NontermCount : SHORTCARD;
		ToTest	   : BOOLEAN;
		InTest	   : BOOLEAN;
	      END;

  VAR
    TablePtr : REF  ARRAY (* tStateIndex*) OF tLine;
	       (* TablePtr^[NoState] bildet den Anker *)
    TableSize : M2LONGINT;

    TSorting  : REF  ARRAY OF tStateIndex;
    TSortingSize : M2LONGINT;

    NSorting  : REF  ARRAY OF tStateIndex;
    NSortingSize : M2LONGINT;

  PROCEDURE CreateDefaultList() =

  (* Erzeugen / Initialisieren der Datenstruktur zur Berechnug der Defaultzustaende *)

  VAR State : tStateIndex;
  BEGIN
    TableSize := LastReadState + 1;
    TablePtr := NEW (REF ARRAY OF tLine, TableSize);
(*WAS:    MakeArray (TablePtr, TableSize, BYTESIZE (tLine));*)
    TSortingSize := LastReadState + 1;
    TSorting := NEW (REF ARRAY OF tStateIndex, TSortingSize);
(*WAS:    MakeArray (TSorting, TSortingSize, BYTESIZE (tStateIndex));*)
    NSortingSize := LastReadState + 1;
    NSorting := NEW (REF ARRAY OF tStateIndex, NSortingSize);
(*WAS:    MakeArray (NSorting, NSortingSize, BYTESIZE (tStateIndex));*)
    FOR State := 0 TO LastReadState DO
      WITH m2tom3_with_1=TablePtr^[State] DO
	m2tom3_with_1.Transitions := NIL;
        m2tom3_with_1.Terms := IntSets.Empty();
	m2tom3_with_1.Succ := NoState;
	m2tom3_with_1.DefaultState := NoState;
	m2tom3_with_1.Saving := 0;
	m2tom3_with_1.NontermCount := 0;
	m2tom3_with_1.ToTest := TRUE;
	m2tom3_with_1.InTest := FALSE;
      END;
      TSorting^[State] := State;
      NSorting^[State] := State;
    END;
  END CreateDefaultList;

  PROCEDURE PutInDefaultList (ReadState: tStateIndex; VAR TableLine: tTableLine) = (* read only *)

  (* Eintragen der in TableLine enthaltenen Zeile in die Datenstruktur *)

  VAR
    Trans : tTrans;
    TransSucc : tTrans;
    Voc	  : Vocabulary;
    State : tStateIndex;
    Elements : SHORTCARD;
    Continue : BOOLEAN;
  BEGIN
    WITH m2tom3_with_2=TablePtr^[ReadState] DO
      m2tom3_with_2.Transitions := NIL;
      FOR Voc := LastSymbol TO FirstSymbol BY -1 DO
	IF TableLine [Voc] # NoState THEN
	  Trans := Alloc (BYTESIZE (tTran));
	  Trans^.Voc   := Voc;
	  Trans^.State := TableLine [Voc];
	  Trans^.Next  := m2tom3_with_2.Transitions;
	  m2tom3_with_2.Transitions := Trans;
	  IF (Voc >= FirstTerminal) AND (Voc <= LastTerminal) THEN
	    m2tom3_with_2.Terms := IntSets.Include (m2tom3_with_2.Terms, Voc);
	  ELSE
	    INC (m2tom3_with_2.NontermCount);
	  END;
	END;
      END;

      (* Einsortieren *)

      State := NoState;
      Elements := IntSets.Card (m2tom3_with_2.Terms);

      (* Suche Element vor (State) bzw. nach (Succ) dem einzufuegenden Element *)

      LOOP
	m2tom3_with_2.Succ := TablePtr^[State].Succ;
	IF m2tom3_with_2.Succ = NoState THEN EXIT; END;
	IF Elements > IntSets.Card (TablePtr^[m2tom3_with_2.Succ].Terms) THEN EXIT;
	ELSIF Elements = IntSets.Card (TablePtr^[m2tom3_with_2.Succ].Terms) THEN
	  Trans := m2tom3_with_2.Transitions;
	  TransSucc := TablePtr^[m2tom3_with_2.Succ].Transitions;
	  Continue := TRUE;
	  WHILE (Trans # NIL) AND (TransSucc # NIL) AND Continue DO
	    IF Trans^.Voc > TransSucc^.Voc THEN 
	      EXIT;
	    ELSIF Trans^.Voc < TransSucc^.Voc THEN 
	      Continue := FALSE;
	    END;
	    Trans := Trans^.Next;
	    TransSucc := TransSucc^.Next;
	  END;
	END;
	State := m2tom3_with_2.Succ;
      END;

      (* Einketten *)

      (* Als Nachfolger beim Vorgaenger eintragen *)
      TablePtr^[State].Succ := ReadState;
      (* Nachfolger ist bereits eingetragen *)
    END;
  END PutInDefaultList;

  PROCEDURE ComputeDefaults() =

  (* Berechnung der variablen Defaultzustaende und entfernen, der dadurch
     in der Tabelle (Datenstruktur) ueberfluessigen Eintraege *)

  BEGIN
    IF NoDefault THEN RETURN END;
    ComputeBestDefaults();
    EliminateCycles();
  END ComputeDefaults;

  PROCEDURE ComputeBestDefaults() =

  (* Berechnug des besten Defaultzustandes ohne Ruecksicht auf Zyklen *)

  VAR
    LastState : tStateIndex;
    State     : tStateIndex;
    DefState  : tStateIndex;
    DefSaving : SHORTCARD;
    backwards : BOOLEAN;
  BEGIN
    LastState := NoState;
    State     := TablePtr^[LastState].Succ;
    
    WHILE State # NoState DO
      IF NOT IntSets. Equal (TablePtr^[LastState].Terms, TablePtr^[State].Terms) THEN
	LastState := State;
      END;

      (* Suche Defaultzustand *)

      DefState := LastState;
      backwards := TRUE;
      LOOP
	(* kein Default zu sich selbst *)
	IF DefState = State THEN
	  DefState :=  TablePtr^[DefState].Succ;
	  backwards := FALSE;
	END;

	(* Listenende erreicht *)
	IF DefState = NoState THEN EXIT; END;

	(* keine Aussicht auf besseren Defaultzustand *)
	IF IntSets.Card (TablePtr^[DefState].Terms) < 
	   TablePtr^[State].Saving THEN EXIT; END;

	DefSaving := ComputeSaving (State, DefState);

	IF (DefSaving > 0) AND (DefSaving >= TablePtr^[State].Saving) THEN
	  TablePtr^[State].DefaultState := DefState;
	  TablePtr^[State].Saving  := DefSaving;
	  TablePtr^[State].ToTest  := backwards;
	END;

	DefState :=  TablePtr^[DefState].Succ;
      END;

      State	:= TablePtr^[State].Succ;
    END;

  END ComputeBestDefaults;

  PROCEDURE ComputeSaving (State: tStateIndex; DefState: tStateIndex): SHORTCARD =
  VAR
    DefSaving : SHORTCARD;
    Trans, DefTrans : tTrans;
  BEGIN
    DefSaving := 0;

    (* ist DefState als Defaultzustand brauchbar ? *)
    IF IntSets.IsSubset (TablePtr^[DefState].Terms, TablePtr^[State].Terms) THEN

      (* Berechne Einsparung *)
      Trans := TablePtr^[State].Transitions;
      DefTrans := TablePtr^[DefState].Transitions;

      WHILE (DefTrans # NIL) AND (DefTrans^.Voc < LastTerminal) DO

	(* Zeichen, fuer die DefState keinen Eintrag hat,
	   in State ueberlesen *)
	WHILE Trans^.Voc # DefTrans^.Voc DO
	  Trans := Trans^.Next;
	END;

	IF Trans^.State = DefTrans^.State THEN
	  INC (DefSaving);
	END;

	DefTrans := DefTrans^.Next;
	Trans := Trans^.Next;
      END;
    END;
    RETURN DefSaving;
  END ComputeSaving;

  PROCEDURE EliminateCycles() =
  VAR
    State	: tStateIndex;
    WorstState	: tStateIndex;
    WorstSaving : SHORTCARD;
    ActState	: tStateIndex;
    FirstState	: tStateIndex;
    DefState	: tStateIndex;
    DefSaving	: SHORTCARD;
  BEGIN

    (* Pruefe alle Zustaende *)

    State := GetNextState (NoState);
    WHILE State # NoState DO

      (* Zustand noch nicht geprueft *)

      IF TablePtr^[State].ToTest THEN
	TablePtr^[State].ToTest := FALSE;
	WorstSaving := TablePtr^[State].Saving;
	WorstState  := State;

	(* Pruefe ob Zyklus vorhanden *)

	TablePtr^[State].InTest := TRUE;
	ActState := TablePtr^[State].DefaultState;
	WHILE (ActState # NoState) AND (NOT TablePtr^[ActState].InTest) DO
	  TablePtr^[ActState].InTest := TRUE;
	  ActState := TablePtr^[ActState].DefaultState;
	END;

	FirstState := ActState;

	(* Flags zuruecksetzen *)

	TablePtr^[State].InTest := FALSE;
	ActState := TablePtr^[State].DefaultState;
	WHILE (ActState # NoState) AND TablePtr^[ActState].InTest DO
	  TablePtr^[ActState].InTest := FALSE;
	  ActState := TablePtr^[ActState].DefaultState;
	END;

	(* Falls Zyklus erkannt diesen aufbrechen *)

	IF FirstState = NoState THEN

	  (* kein Zyklus - Zustand fortschalten *)
	  State := GetNextState (State);

	ELSE
	  WorstState  := FirstState;
	  WorstSaving := TablePtr^[WorstState].Saving;

	  ActState := TablePtr^[FirstState].DefaultState;
	  WHILE ActState # FirstState DO
	    IF TablePtr^[ActState].Saving < WorstSaving THEN
	      WorstState  := ActState;
	      WorstSaving := TablePtr^[WorstState].Saving;
	    END;
	    ActState := TablePtr^[ActState].DefaultState;
	  END;

	  (* Anfang fuer neu Defaultsuche festhalten *)

	  DefState := TablePtr^[WorstState].DefaultState;
	  DefState := TablePtr^[DefState].Succ;

	  TablePtr^[WorstState].DefaultState := NoState;
	  TablePtr^[WorstState].Saving := 0;


	  (* Neuen Defaultzustand berechnen *)
	  
	  LOOP
	    (* kein Default zu sich selbst *)
	    IF DefState = WorstState THEN
	      DefState :=  TablePtr^[DefState].Succ;
	    END;

	    (* Listenende erreicht *)
	    IF DefState = NoState THEN EXIT; END;

	    (* keine Aussicht auf besseren Defaultzustand *)
	    IF IntSets.Card (TablePtr^[DefState].Terms) < 
	       TablePtr^[WorstState].Saving THEN EXIT; END;

	    DefSaving := ComputeSaving (WorstState, DefState);

	    IF (DefSaving > 0) AND (DefSaving >= TablePtr^[WorstState].Saving) THEN
	      TablePtr^[WorstState].DefaultState := DefState;
	      TablePtr^[WorstState].Saving  := DefSaving;

	    END;

	    DefState :=	 TablePtr^[DefState].Succ;
	  END;

	  IF TablePtr^[WorstState].DefaultState # NoState THEN

	    (* im naechsten Durchlauf noch einmal auf Zyklus pruefen *)
	    TablePtr^[State].ToTest  := TRUE;

	  END;
	END;
      ELSE
	State := GetNextState (State);
      END;
    END;
  END EliminateCycles;

  PROCEDURE GetNextState (State: tStateIndex): tStateIndex =
  
  (* Fortschalten des Zustandes nach festgelegter Strategie *)
  (* Strategie : Zuerst Zustaende mit vielen Eintraegen *)

  BEGIN
    RETURN TablePtr^[State].Succ;
  END GetNextState;

  PROCEDURE GetTSortState (State: tStateIndex): tStateIndex =
  
  (* Fortschalten des Zustandes nach festgelegter Strategie *)
  (* Strategie : Zuerst Zustaende mit vielen Eintraegen *)

  BEGIN
    RETURN TSorting^[State];
  END GetTSortState;

  PROCEDURE GetNSortState (State: tStateIndex): tStateIndex =
  
  (* Fortschalten des Zustandes nach festgelegter Strategie *)
  (* Strategie : Zuerst Zustaende mit vielen Eintraegen *)

  BEGIN
    RETURN NSorting^[State];
  END GetNSortState;

  PROCEDURE GetDefaultTableLine (ReadState: tStateIndex; VAR TableLine: tTableLine; VAR Default: tStateIndex) =

  (* Auslesen der durch 'ReadState' bezeichneten Zeile aus der Datenstruktur *)

  VAR
    Voc : Vocabulary;
    Trans : tTrans;
  BEGIN
    FOR Voc := FirstSymbol TO LastSymbol DO
      TableLine [Voc] := NoState;
    END;
    WITH m2tom3_with_3=TablePtr^[ReadState] DO
      Default := m2tom3_with_3.DefaultState;
      Trans := m2tom3_with_3.Transitions;
      WHILE Trans # NIL DO
	TableLine [Trans^.Voc] := Trans^.State;
	Trans := Trans^.Next;
      END;
    END;

    (* Werte Default aus *)

    WITH m2tom3_with_4=TablePtr^[Default] DO
      Trans := m2tom3_with_4.Transitions;
      WHILE (Trans # NIL) AND (Trans^.Voc <= LastTerminal) DO
	IF TableLine [Trans^.Voc] = Trans^.State THEN
	  TableLine [Trans^.Voc] := NoState;
	END;
	Trans := Trans^.Next;
      END;
    END;
  END GetDefaultTableLine;

  PROCEDURE SortTStates() =
  VAR
    sorted : BOOLEAN;
    I	   : tStateIndex;
    State  : tStateIndex;
    Key, LastKey : SHORTCARD;
  BEGIN
    LOOP
      sorted := TRUE;
      State := TSorting^[1];
      LastKey := IntSets.Card (TablePtr^[State].Terms) - TablePtr^[State].Saving;
      FOR I := 2 TO LastReadState DO
	State := TSorting^[I];
	Key := IntSets.Card (TablePtr^[State].Terms) - TablePtr^[State].Saving;
	IF LastKey < Key THEN
	  sorted := FALSE;
	  TSorting^[I] := TSorting^ [I-1];
	  TSorting^[I-1] := State;
	ELSE
	  LastKey := Key;
	END;
      END;

      IF sorted THEN EXIT; END;

      sorted := TRUE;
      State := TSorting^[LastReadState];
      LastKey := IntSets.Card (TablePtr^[State].Terms) - TablePtr^[State].Saving;
      FOR I := LastReadState - 1 TO 1 BY -1 DO
	State := TSorting^[I];
	Key := IntSets.Card (TablePtr^[State].Terms) - TablePtr^[State].Saving;
	IF LastKey > Key THEN
	  sorted := FALSE;
	  TSorting^[I] := TSorting^[I+1];
	  TSorting^[I+1] := State;
	ELSE
	  LastKey := Key;
	END;
      END;

      IF sorted THEN EXIT; END;
    END;
  END SortTStates;

  PROCEDURE SortNStates() =
  VAR
    sorted : BOOLEAN;
    I	   : tStateIndex;
    State  : tStateIndex;
    Key, LastKey : SHORTCARD;
  BEGIN
    LOOP
      sorted := TRUE;
      State := NSorting^[1];
      LastKey := TablePtr^[State].NontermCount;
      FOR I := 2 TO LastReadState DO
	State := NSorting^[I];
	Key := TablePtr^[State].NontermCount;
	IF LastKey < Key THEN
	  sorted := FALSE;
	  NSorting^[I] := NSorting^[I-1];
	  NSorting^[I-1] := State;
	ELSE
	  LastKey := Key;
	END;
      END;

      IF sorted THEN EXIT; END;

      sorted := TRUE;
      State := NSorting^[LastReadState];
      LastKey := TablePtr^[State].NontermCount;
      FOR I := LastReadState - 1 TO 1 BY -1 DO
	State := NSorting^[I];
	Key := TablePtr^[State].NontermCount;
	IF LastKey > Key THEN
	  sorted := FALSE;
	  NSorting^[I] := NSorting^[I+1];
	  NSorting^[I+1] := State;
	ELSE
	  LastKey := Key;
	END;
      END;

      IF sorted THEN EXIT; END;
    END;
  END SortNStates;

BEGIN
  NoDefault := FALSE;
END Default.

