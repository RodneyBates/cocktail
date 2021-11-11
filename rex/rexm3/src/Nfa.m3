(* $Id: Nfa.mi,v 3.1 1991/11/21 14:41:19 grosch rel $ *)

(* $Log: Nfa.mi,v $
 * Revision 3.1  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.0  91/04/04  18:07:25  grosch
 * introduced partitioning of character set
 * 
 * Revision 1.2  91/03/26  18:26:53  grosch
 * improved generation time
 * introduced options n and o to control table size and generation time
 * increased limitation for table size from 64K to 256K
 * 
 * Revision 1.1  90/05/17  11:17:13  grosch
 * added missing initialization
 * 
 * Revision 1.0  88/10/04  11:59:36  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

 UNSAFE MODULE Nfa;


FROM SYSTEM IMPORT M2LONGINT;
FROM DynArray   IMPORT MakeArray, ExtendArray, ReleaseArray;
FROM IO         IMPORT WriteC, WriteI, WriteNl, WriteS, StdOutput;
FROM Layout     IMPORT WriteChar, WriteSpace;
FROM ScanTabs   IMPORT RuleType, NoRule;
FROM GenTabs    IMPORT LeafCount;


CONST InitialTransitionTableSize = 4096;

TYPE
   Transition           = RECORD
                             Ch         : CHAR;
                             NextState  : NStateRange;
                             NextTrans  : TransitionRange;
                          END;

   NStateInfo           = RECORD
                             Transitions: TransitionRange;
                             Semantics  : RuleType;
                          END;

   NStateTable          = ARRAY [0 .. 100000] OF NStateInfo;
   TransitionTable      = ARRAY [0 .. 100000] OF Transition;
(* necessary to force index arithmetic to be done with long integers *)

VAR
   NStateTablePtr       : UNTRACED BRANDED REF  NStateTable;
   NStateTableSize      : M2LONGINT;

   TransitionTablePtr   : UNTRACED BRANDED REF  TransitionTable;
   TransitionTableSize  : M2LONGINT;

PROCEDURE MakeNState (pTransitions: TransitionRange): NStateRange =
   BEGIN
      INC (NStateCount);
      IF NStateCount = NStateTableSize THEN
         ExtendArray (NStateTablePtr, NStateTableSize, BYTESIZE (NStateInfo));
      END;
      WITH m2tom3_with_8=NStateTablePtr^[NStateCount] DO
         m2tom3_with_8.Transitions := pTransitions;
         m2tom3_with_8.Semantics   := NoRule;
      END;
      RETURN NStateCount;
   END MakeNState;

PROCEDURE PutNSemantics (State: NStateRange; pSemantics: RuleType) =
   BEGIN
      NStateTablePtr^[State].Semantics := pSemantics;
   END PutNSemantics;

PROCEDURE GetNSemantics (State: NStateRange): RuleType =
   BEGIN
      RETURN NStateTablePtr^[State].Semantics;
   END GetNSemantics;

PROCEDURE PutTransitions (State: NStateRange; Transitions: TransitionRange) =
   BEGIN
      NStateTablePtr^[State].Transitions := Transitions;
   END PutTransitions;

PROCEDURE GetTransitions (State: NStateRange): TransitionRange =
   BEGIN
      RETURN NStateTablePtr^[State].Transitions;
   END GetTransitions;

PROCEDURE IsLastTransition (Transition: TransitionRange): BOOLEAN =
   BEGIN
      RETURN Transition = NoTransition;
   END IsLastTransition;

PROCEDURE NextTransition (Transition: TransitionRange): TransitionRange =
   BEGIN
      RETURN TransitionTablePtr^[Transition].NextTrans;
   END NextTransition;

PROCEDURE MakeTransition (pCh: CHAR; State: NStateRange): TransitionRange =
   BEGIN
      INC (TransitionCount);
      IF TransitionCount = TransitionTableSize THEN
         ExtendArray (TransitionTablePtr, TransitionTableSize, BYTESIZE (Transition));
      END;
      WITH m2tom3_with_9=TransitionTablePtr^[TransitionCount] DO
         m2tom3_with_9.Ch          := pCh;
         m2tom3_with_9.NextState := State;
         m2tom3_with_9.NextTrans := NoTransition;
      END;
      RETURN TransitionCount;
   END MakeTransition;

PROCEDURE AddTransition (Transition, Transitions: TransitionRange): TransitionRange =
   BEGIN
      TransitionTablePtr^[Transition].NextTrans := Transitions;
      RETURN Transition;
   END AddTransition;

PROCEDURE GetCh (Transition: TransitionRange): CHAR =
   BEGIN
      RETURN TransitionTablePtr^[Transition].Ch;
   END GetCh;

PROCEDURE GetNextState (Transition: TransitionRange): NStateRange =
   BEGIN
      RETURN TransitionTablePtr^[Transition].NextState;
   END GetNextState;

PROCEDURE UniteTransitions (t1, t2: TransitionRange): TransitionRange =
   VAR t : TransitionRange;
   BEGIN
      IF t1 = NoTransition THEN RETURN t2; END; (* IsLastTransition *)
      WHILE t2 # NoTransition DO                (* NOT IsLastTransition *)
         t  := TransitionTablePtr^[t2].NextTrans; (* NextTransition *)
         t1 := AddTransition (t2, t1);
         t2 := t;
      END;
      RETURN t1;
   END UniteTransitions;

PROCEDURE CopyTransitions (t1: TransitionRange): TransitionRange =
   VAR t2 : TransitionRange;
   BEGIN
      t2 := NoTransition;
      WHILE t1 # NoTransition DO                (* NOT IsLastTransition *)
         WITH m2tom3_with_10=TransitionTablePtr^[t1] DO (* GetCh + GetNextState *)
            t2 := AddTransition (MakeTransition (m2tom3_with_10.Ch, m2tom3_with_10.NextState), t2);
            t1 := m2tom3_with_10.NextTrans;                     (* NextTransition *)
         END;
      END;
      RETURN t2;
   END CopyTransitions;

PROCEDURE WriteNfa() =
   VAR State    : NStateRange;
   BEGIN
      WriteS (StdOutput, ARRAY [0..5] OF CHAR{'N','F','A',' ',':','\000'});
      WriteNl (StdOutput);
      WriteNl (StdOutput);
      FOR State := 1 TO NStateCount DO
         WriteS (StdOutput, ARRAY [0..18] OF CHAR{'S','t','a','t','e',',',' ','S','e','m','a','n','t','i','c','s',' ','=','\000'});
         WriteI (StdOutput, State, 5);
         WriteI (StdOutput, GetNSemantics (State), 5);
         WriteNl (StdOutput);
         WriteTransitions (GetTransitions (State));
         WriteNl (StdOutput);
         WriteNl (StdOutput);
      END;
      WriteNl (StdOutput);
   END WriteNfa;

PROCEDURE WriteTransitions (Transition: TransitionRange) =
   VAR Count    : INTEGER;
   BEGIN
      Count := 0;
      WHILE NOT IsLastTransition (Transition) DO
         IF Count = 10 THEN
            WriteNl (StdOutput);
            Count := 0;
         END;
         INC (Count);
         WriteChar (StdOutput, GetCh (Transition));
         WriteSpace (StdOutput);
         WriteI (StdOutput, GetNextState (Transition), 1);
         WriteC (StdOutput, ',');
         WriteSpace (StdOutput);
         Transition := NextTransition (Transition);
      END;
   END WriteTransitions;

PROCEDURE FinalizeNfa() =
   BEGIN
      ReleaseArray (NStateTablePtr, NStateTableSize, BYTESIZE (NStateInfo));
      ReleaseArray (TransitionTablePtr, TransitionTableSize, BYTESIZE (Transition));
   END FinalizeNfa;

PROCEDURE BeginNfa() =
   BEGIN
      NStateTableSize   := LeafCount + 1;
      MakeArray (NStateTablePtr, NStateTableSize, BYTESIZE (NStateInfo));
      NStateCount               := 0;

      TransitionTableSize       := InitialTransitionTableSize;
      MakeArray (TransitionTablePtr, TransitionTableSize, BYTESIZE (Transition));
      TransitionCount   := 0;
   END BeginNfa;

BEGIN
END Nfa.

