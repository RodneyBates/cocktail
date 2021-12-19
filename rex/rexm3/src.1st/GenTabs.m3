(* $Id: GenTabs.mi,v 3.2 1991/11/21 14:41:19 grosch rel $ *)

(* Rodney M. Bates
    Apr. 1999 Minor changes to compile, after changes to Sets
*) 

(* $Log: GenTabs.mi,v $
 * Revision 3.2  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.1  91/04/26  18:19:08  grosch
 * fixed bug in computing ControlSize
 * 
 * Revision 3.0  91/04/04  18:06:59  grosch
 * introduced partitioning of character set
 * 
 * Revision 2.1  91/03/26  18:26:46  grosch
 * improved generation time
 * introduced options n and o to control table size and generation time
 * increased limitation for table size from 64K to 256K
 * 
 * Revision 2.0  91/03/08  18:17:46  grosch
 * turned tables into initialized arrays (in C)
 * reduced case size
 * changed interface for source position
 * 
 * Revision 1.9  91/02/13  11:34:34  grosch
 * moved tables from file to initialization in C; reduced case size
 * 
 * Revision 1.8  90/09/04  19:35:39  grosch
 * fixed bug in AddConstantRE with StartSets
 * 
 * Revision 1.7  90/06/11  11:27:29  grosch
 * extended character range to 8 bits, ChRange -> CHAR
 * 
 * Revision 1.6  90/05/17  11:20:32  grosch
 * extend character range to 8 bits
 * 
 * Revision 1.5  90/04/11  18:27:36  grosch
 * added missing ) in message
 * 
 * Revision 1.4  89/11/06  12:38:36  grosch
 * renamed module Rex to GenTabs to avoid name clash with rex under VMS
 * 
 * Revision 1.3  89/06/01  18:09:36  grosch
 * fixed bug at optional right context
 * 
 * Revision 1.2  89/02/23  15:55:34  grosch
 * corrected confusion between RuleCount and PatternCount
 * corrected debug procedure WritePattern
 * improved handling of right context
 * added completeness check for the automaton
 * 
 * Revision 1.1  89/01/17  15:01:15  grosch
 * correction and redesign of source position handling
 * 
 * Revision 1.0  88/10/04  11:59:40  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

 UNSAFE MODULE GenTabs;


FROM SYSTEM IMPORT M2LONGINT;
FROM SYSTEM IMPORT HALT, SHORTINT, SHORTCARD;
FROM General    IMPORT Min;
FROM Memory     IMPORT Alloc, Free, MemoryUsed;
FROM DynArray   IMPORT MakeArray, ExtendArray, ReleaseArray;
FROM Strings    IMPORT tString, Char, Length, Concatenate, Append;
FROM StringMem  IMPORT GetString;
FROM Times      IMPORT WriteStepTime;

FROM Sets       IMPORT
   tSet         , tElement      , MakeSet       , ReleaseSet    , Union         ,
   Intersection , Include       , Exclude       , Minimum       ,
   Extract      , IsEqual       , IsElement     , IsEmpty       ,
   Assign       , AssignElmt    , AssignEmpty   , ForallDo      ,
   Maximum      , IsSubset      , WriteSet      ;

FROM ReuseIO         IMPORT WriteS, WriteNl, WriteI, WriteC, StdOutput, StdError;
FROM DefTable   IMPORT GetKind, DefCount, GetStartDef, tKind;

FROM Tree       IMPORT
   nAlternative , nSequence     , nRepetition   , nOption       ,
   nChar        , nSet          , nString       ,
   tTree        , NoTree        ;

FROM Nfa        IMPORT
   NStateRange  , TransitionRange, NStateCount  , TransitionCount,
   PutNSemantics, GetNSemantics , PutTransitions, GetTransitions,
   MakeNState   , MakeTransition, IsLastTransition, NextTransition,
   GetCh        , GetNextState  , NoTransition  , WriteNfa      ,
   AddTransition, CopyTransitions, UniteTransitions, BeginNfa, FinalizeNfa;

FROM Dfa        IMPORT
   DNoState     , DStateRange   , DStateCount   , MakeDState    ,
   GetTable     , PutTable      , GetDSemantics , PutDSemantics ,
   GetStartSet  , PutStartSet   , ComputeStartSets, WriteDfa    ,
   GetDefault   , PutDefault    , GetFirst      , GetLast       ,
   EobState     , EobDefaultState, FirstCh      , LastCh        , OldLastCh,
   EobCh        , CyclicStates  , AmbiguousStates, MaxAmbiguousState,
   ComputeSuccGraph, ComputeCyclicStates, ComputeAmbiguousStates,
   MinimizeDfa  , MinimizeSavings, SaveEobTransitions, ComputeDefaults,
   DefaultSavings;

FROM Traces     IMPORT
   InitTraces   , ResetTraces   , RecordTrace   , RecordedTrace ,
   FinalizeTraces;

FROM ScanTabs   IMPORT
   NoRule       , TableSize     , TableEntries  , MakeTables    ,
   CompressTables, PutTables    , QueryTables   , WriteTables   ;

FROM ScanGen    IMPORT Language, tLanguage;
FROM Classes    IMPORT ClassCount, ToClass, ClassMemPtr, ToChar, Unused;

IMPORT Word, Strings, Idents;

TYPE
   SetOfNInfoPtr        = UNTRACED BRANDED REF  SetOfNInfo                 ;
   SetOfNInfo           = RECORD
                             Next       : SetOfNInfoPtr ;
                             Set        : tSet          ;
                             DState     : DStateRange   ;
                          END;
   MapDToSetOfN         = ARRAY [0 .. 100000] OF SetOfNInfoPtr  ;
   HashDToSetOfN        = ARRAY [0 .. 100000] OF SetOfNInfoPtr  ;
   Stack                = ARRAY [0 .. 100000] OF DStateRange    ;

VAR
   MapDToSetOfNPtr      : UNTRACED BRANDED REF  MapDToSetOfN;
   MapDToSetOfNSize     : M2LONGINT       ;

   HashDToSetOfNPtr     : UNTRACED BRANDED REF  HashDToSetOfN;
   HashDToSetOfNSize    : M2LONGINT       ;

   StackPtr             : UNTRACED BRANDED REF  Stack;
   StackSize            : M2LONGINT       ;
   StackTop             : DStateRange   ;

   StartSet             ,
   dSemantics           : tSet          ;
   SentinelSavings      : INTEGER       ;

   IsComputedNContext   : BOOLEAN       ;
   IsComputedDContext   : BOOLEAN       ;
   IsComputedFinals     : BOOLEAN       ;

PROCEDURE ComputeNfa() =
   VAR
      t1, t2            : TransitionRange;
      f1, f2            : tSet          ;
      o1, o2            : BOOLEAN       ;
      ruleList          : tTree         ;
      rule              : tTree         ;
      patternList       : tTree         ;
      pattern           : tTree         ;
      RuleNr            : SHORTCARD     ;
      length            : SHORTINT      ;
   BEGIN
      BeginNfa();
      FOR NState := 1 TO StartStateCount DO
         IF MakeNState (NoTransition) # NState THEN HALT(); END;  (* ASSERT *)
      END;

      MakeSet (f1, LeafCount);
      MakeSet (f2, LeafCount);
      ruleList := Root;

      WHILE ruleList # NoTree DO
         rule := ruleList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 175
 $$ *).Son2;
         RuleNr := rule^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 176
 $$ *).RuleNr;
         RuleToCodePtr^[RuleNr].Text     := rule^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 177
 $$ *).TargetCode;
         RuleToCodePtr^[RuleNr].TextLine := rule^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 178
 $$ *).Line;
         RuleToCodePtr^[RuleNr].CodeMode := rule^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 179
 $$ *).CodeMode;
         patternList := rule^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 180
 $$ *).Patterns;

         WHILE patternList # NoTree DO
            pattern := patternList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 183
 $$ *).Son2;
            PatternNr := pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 184
 $$ *).PatternNr;
            WITH m2tom3_with_7=PatternTablePtr^[PatternNr] DO
               m2tom3_with_7.Rule             := RuleNr;
               m2tom3_with_7.ContextLng       := NoContext;
               m2tom3_with_7.Position         := pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 188
 $$ *).Position;
            END;
            IF NOT pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 190
 $$ *).IsConstantRE THEN
               AttributeEvaluator (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 191
 $$ *).RegExpr, t1, f1, o1);
               AttributeEvaluator (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 192
 $$ *).RightContext, t2, f2, o2);
               tt := t1;
               ForallDo (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 194
 $$ *).StartStates, ExtendTransitions);
               IF o2 THEN
                  ForallDo (f1, EnterNSemantics);
               END;
               tt := t2;
               ForallDo (f1, ExtendTransitions);
               ForallDo (f2, EnterNSemantics);
                                             (* context *)
               length := ComputeLength (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 202
 $$ *).RightContext);
               IF length # VariableContext THEN
                  PatternTablePtr^[PatternNr].ContextLng := length;
               ELSE
                  length := ComputeLength (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 206
 $$ *).RegExpr);
                  IF length # VariableContext THEN
                     PatternTablePtr^[PatternNr].ContextLng := - length;
                  ELSE
                     PatternTablePtr^[PatternNr].ContextLng := VariableContext;
                     MakeSet (PatternTablePtr^[PatternNr].NContext, LeafCount);
                     Assign (PatternTablePtr^[PatternNr].NContext, f1);
                  END;
               END;
            END;
            patternList := patternList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 216
 $$ *).Son1;
         END;
         ruleList := ruleList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 218
 $$ *).Son1;
      END;

      IsComputedNContext := TRUE;
      ReleaseSet (f1);
      ReleaseSet (f2);
   END ComputeNfa;

PROCEDURE ComputeLength (t: tTree): SHORTINT =
   VAR
      l1, l2    : SHORTINT;
      string    : tString;
   BEGIN
      IF t = NoTree THEN RETURN NoContext; END;

      CASE t^.vNode0(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode0' in line 233
 $$ *).Rule OF
      |  nAlternative   => l1 := ComputeLength (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 234
 $$ *).Son1);
                          l2 := ComputeLength (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 235
 $$ *).Son2);
                          IF l1 = l2 THEN
                             RETURN l1;
                          ELSE
                             RETURN VariableContext;
                          END;

      |  nSequence      => l1 := ComputeLength (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 242
 $$ *).Son1);
                          l2 := ComputeLength (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 243
 $$ *).Son2);
                          IF (l1 # VariableContext) AND (l2 # VariableContext) THEN
                             RETURN l1 + l2;
                          ELSE
                             RETURN VariableContext;
                          END;

      |  nRepetition    ,
         nOption        => RETURN VariableContext;

      |  nChar          ,
         nSet           => RETURN 1;

      |  nString        => GetString (t^.vNodeString(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeString' in line 256
 $$ *).String, string);
                          RETURN Length (string);
      END;
   END ComputeLength;

PROCEDURE AttributeEvaluator (
          t             : tTree         ;
      VAR Transitions   : TransitionRange;
      VAR FinalStates   : tSet          ;
      VAR IsOptional    : BOOLEAN       ) =
   VAR
      t1, t2            : TransitionRange;
      f1, f2            : tSet;
      o1, o2            : BOOLEAN;
      NState            : NStateRange;
      string            : tString;
   BEGIN
      IF t = NoTree THEN
         Transitions := NoTransition;
         AssignEmpty (FinalStates);
         IsOptional := TRUE;
         RETURN;
      END;

      CASE t^.vNode0(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode0' in line 281
 $$ *).Rule OF

      |  nAlternative   => (* regExpr = Alternative (regExpr regExpr) *)
            MakeSet (f1, LeafCount);
            MakeSet (f2, LeafCount);
            AttributeEvaluator (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 286
 $$ *).Son1, t1, f1, o1);
            AttributeEvaluator (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 287
 $$ *).Son2, t2, f2, o2);
            Transitions := UniteTransitions (t1, t2);
            Assign (FinalStates, f1);
            Union (FinalStates, f2);
            IsOptional := o1 OR o2;
            ReleaseSet (f1);
            ReleaseSet (f2);

      |  nSequence      => (* regExpr = Sequence (regExpr regExpr) *)
            MakeSet (f1, LeafCount);
            MakeSet (f2, LeafCount);
            AttributeEvaluator (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 298
 $$ *).Son1, t1, f1, o1);
            AttributeEvaluator (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 299
 $$ *).Son2, t2, f2, o2);
            tt := t2;
            ForallDo (f1, ExtendTransitions);
            IF o1 THEN
               Transitions := UniteTransitions (t1, t2);
            ELSE
               Transitions := t1;
            END;
            IF o2 THEN
               Assign (FinalStates, f1);
               Union (FinalStates, f2);
            ELSE
               Assign (FinalStates, f2);
            END;
            IsOptional := o1 AND o2;
            ReleaseSet (f1);
            ReleaseSet (f2);

      |  nRepetition    => (* regExpr = Repetition (regExpr) *)
            MakeSet (f1, LeafCount);
            AttributeEvaluator (t^.vNode1(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode1' in line 319
 $$ *).Son1, t1, f1, o1);
            tt := t1;
            ForallDo (f1, ExtendTransitions);
            Transitions := t1;
            Assign (FinalStates, f1);
            IsOptional := o1;
            ReleaseSet (f1);

      |  nOption        => (* regExpr = Option (regExpr) *)
            MakeSet (f1, LeafCount);
            AttributeEvaluator (t^.vNode1(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode1' in line 329
 $$ *).Son1, t1, f1, o1);
            Transitions := t1;
            Assign (FinalStates, f1);
            IsOptional := TRUE;
            ReleaseSet (f1);

      |  nChar  => (* regExpr = Char *)
            NState := MakeNState (NoTransition);
            Transitions := MakeTransition (t^.vNodeCh(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeCh' in line 337
 $$ *).Ch, NState);
            AssignElmt (FinalStates, NState);
            IsOptional := FALSE;

      |  nSet   => (* regExpr = Set *)
            MakeSet (f1, ORD (LastCh));
            Assign (f1, t^.vNodeSet(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeSet' in line 343
 $$ *).Set);
            NState := MakeNState (NoTransition);
            Transitions := NoTransition;
            WHILE NOT IsEmpty (f1) DO
               Transitions := AddTransition (MakeTransition (
                              VAL (Extract (f1),CHAR), NState), Transitions);
            END;
            AssignElmt (FinalStates, NState);
            IsOptional := FALSE;
            ReleaseSet (f1);

      |  nString        => (* regExpr = String *)
            GetString (t^.vNodeString(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeString' in line 355
 $$ *).String, string);
            NState := MakeNState (NoTransition);
            Transitions := MakeTransition (Char (string, Length (string)), NState);
            AssignElmt (FinalStates, NState);
            FOR i := Length (string) - 1 TO 1 BY -1 DO
               NState := MakeNState (Transitions);
               Transitions := MakeTransition (Char (string, i), NState);
            END;
            IsOptional := FALSE;
      END;
   END AttributeEvaluator;

VAR tt          : TransitionRange;
VAR PatternNr   : SHORTCARD;

PROCEDURE ExtendTransitions (NState: tElement ) =
   BEGIN
      PutTransitions (NState, UniteTransitions (
      GetTransitions (NState), CopyTransitions (tt)));
   END ExtendTransitions;

PROCEDURE EnterNSemantics (NState: tElement ) =
   BEGIN
      PutNSemantics (NState, PatternNr);
   END EnterNSemantics;

PROCEDURE MapSetOfNToD (t: tSet): DStateRange =
   VAR
      DState    : DStateRange;
      Hash      : Word.T;
      Current   : SetOfNInfoPtr;
   BEGIN
      Hash := Maximum (t) MOD LOOPHOLE (NStateCount,Word.T);
      Current := HashDToSetOfNPtr^[Hash];
      WHILE Current # NIL DO                    (* t IN S' ? *)
         IF IsEqual (Current^.Set, t) THEN
            RETURN Current^.DState;             (* yes *)
         END;
         Current := Current^.Next;
      END;

      DState := MakeDState ();                  (* no: S' := S' UNION {t} *)
      IF DState = MapDToSetOfNSize THEN
         ExtendArray (LOOPHOLE(MapDToSetOfNPtr,ADDRESS), MapDToSetOfNSize, BYTESIZE (SetOfNInfoPtr));
      END;
      MapDToSetOfNPtr^[DState] := Alloc (BYTESIZE (SetOfNInfo));
      MakeSet (MapDToSetOfNPtr^[DState]^.Set, NStateCount);
      Assign (MapDToSetOfNPtr^[DState]^.Set, t);
      MapDToSetOfNPtr^[DState]^.DState := DState;
      MapDToSetOfNPtr^[DState]^.Next := HashDToSetOfNPtr^[Hash];
      HashDToSetOfNPtr^[Hash] := MapDToSetOfNPtr^[DState];

      INC (StackTop);                           (* push (y) *)
      IF StackTop = StackSize THEN
         ExtendArray (LOOPHOLE(StackPtr,ADDRESS), StackSize, BYTESIZE (DStateRange));
      END;
      StackPtr^[StackTop] := DState;
      RETURN DState;
   END MapSetOfNToD;

PROCEDURE ComputeDfa() =
   CONST InitialStackSize = 64;
   VAR
      DState    : DStateRange;
      x         : tSet;
      y         : ARRAY CHAR OF tSet;
      Transition: TransitionRange;
      Ch        : CHAR;
      CharSet   : tSet;
      nStates   : tSet;
   BEGIN
      StackSize         := InitialStackSize;    (* initialize *)
      MakeArray (LOOPHOLE(StackPtr,ADDRESS), StackSize, BYTESIZE (DStateRange));
      StackTop          := 0;
      MapDToSetOfNSize  := LeafCount;
      MakeArray (LOOPHOLE(MapDToSetOfNPtr,ADDRESS), MapDToSetOfNSize, BYTESIZE (SetOfNInfoPtr));
      HashDToSetOfNSize := NStateCount;
      MakeArray (LOOPHOLE(HashDToSetOfNPtr,ADDRESS), HashDToSetOfNSize, BYTESIZE (SetOfNInfoPtr));
      FOR NState := 0 TO NStateCount - 1 DO
         HashDToSetOfNPtr^[NState] := NIL;
      END;
      MakeSet (x, NStateCount);
      FOR Ch := FirstCh TO LastCh DO
         MakeSet (y [Ch], NStateCount);
      END;
      MakeSet (CharSet, ORD (LastCh));
      MakeSet (nStates, LeafCount);

      FOR NState := 1 TO StartStateCount DO     (* FORALL start states *)
         AssignElmt (x, NState);                (* map+push (start state) *)
         DState := MapSetOfNToD (x);
         IF DState # NState THEN HALT(); END;     (* ASSERT *)
      END;

      WHILE StackTop > 0 DO
         DState := StackPtr^[StackTop];         (* DState := pop () *)
         DEC (StackTop);
         Assign (x, MapDToSetOfNPtr^[DState]^.Set);
         AssignEmpty (CharSet);

         FOR NState := 1 TO NStateCount DO
            IF IsElement (NState, x) THEN
               Transition := GetTransitions (NState);
               WHILE NOT IsLastTransition (Transition) DO
                  Ch := GetCh (Transition);
                  Include (y [Ch], GetNextState (Transition));
                  Include (CharSet, ORD (Ch));
                  Transition := NextTransition (Transition);
               END;
            END;
         END;

         WHILE NOT IsEmpty (CharSet) DO
            Ch := VAL (Extract (CharSet),CHAR);
            PutTable (DState, Ch, MapSetOfNToD (y [Ch]));
            AssignEmpty (y [Ch]);
         END;
      END;

      INC (NodeCount, DStateCount + 3);
      FOR Pattern := 1 TO PatternCount - 2 DO   (* context *)
         IF PatternTablePtr^[Pattern].ContextLng = VariableContext THEN
            MakeSet (PatternTablePtr^[Pattern].DContext, NodeCount);
            FOR DState := 1 TO DStateCount DO
               Assign (nStates, PatternTablePtr^[Pattern].NContext);
               Intersection (nStates, MapDToSetOfNPtr^[DState]^.Set);
               IF NOT IsEmpty (nStates) THEN
                  Include (PatternTablePtr^[Pattern].DContext, DState);
               END;
            END;
            ReleaseSet (PatternTablePtr^[Pattern].NContext);
         END;
      END;
      IsComputedNContext := FALSE;
      IsComputedDContext := TRUE;

      FOR DState := 1 TO DStateCount DO         (* semantics *)
         dState := DState;
         AssignEmpty (dSemantics);
         ForallDo (MapDToSetOfNPtr^[DState]^.Set, EnterDSemantics);
         Exclude (dSemantics, NoRule);
         PutDSemantics (DState, dSemantics);
      END;

      FOR DState := 1 TO DStateCount DO         (* clean up *)
         ReleaseSet (MapDToSetOfNPtr^[DState]^.Set);
         Free (BYTESIZE (SetOfNInfo), MapDToSetOfNPtr^[DState]);
      END;
      ReleaseSet (x);
      FOR Ch := FirstCh TO LastCh DO
         ReleaseSet (y [Ch]);
      END;
      ReleaseSet (CharSet);
      ReleaseSet (nStates);
      ReleaseArray (StackPtr, StackSize, BYTESIZE (DStateRange));
      ReleaseArray (MapDToSetOfNPtr, MapDToSetOfNSize, BYTESIZE (SetOfNInfoPtr));
      ReleaseArray (HashDToSetOfNPtr, HashDToSetOfNSize, BYTESIZE (SetOfNInfoPtr));
      FinalizeNfa();
   END ComputeDfa;

VAR dState      : DStateRange;

PROCEDURE EnterDSemantics (NState: tElement ) =
   BEGIN
      Include (dSemantics, GetNSemantics (NState));
   END EnterDSemantics;

PROCEDURE SaveSentinels() =
   VAR
      Default   : DStateRange;
      Success   : BOOLEAN;
      Ch, LastCh: CHAR;
      Defaults  : tSet;
   BEGIN

      (* no end of buffer sentinel necessary for absolute final states: *)
      (* - state must have semantics (to be final state)                *)
      (* - may not use a default state (except EobDefaultState)         *)
      (* - may not be used as default state                             *)
      (* - no transitions may be defined (except on EobCh)              *)

      SentinelSavings := 0;
      MakeSet (Defaults, DStateCount);
      FOR DState := 1 TO DStateCount DO
         Include (Defaults, GetDefault (DState));
      END;

      FOR DState := 1 TO DStateCount DO
         GetDSemantics (DState, dSemantics);
         Default := GetDefault (DState);
         IF (NOT IsEmpty (dSemantics)) AND          (* final state ?         *)
            ((Default = DNoState) OR              (* don't use default ?   *)
             (Default = EobDefaultState)) AND
            (NOT IsElement (DState, Defaults)) THEN (* not used as default ? *)

            Success := TRUE;                      (* check transitions     *)
            Ch      := GetFirst (DState);
            LastCh  := GetLast  (DState);
            IF Ch <= LastCh THEN
               LOOP
                  IF (Ch # ToClass [EobCh]) AND (GetTable (DState, Ch) # DNoState) THEN
                     Success := FALSE;
                     EXIT;
                  END;
                  IF Ch = LastCh THEN EXIT; END;
                  INC (Ch);
               END;
            END;

            IF Success THEN                     (* absolute final state ? *)
               PutTable (DState, ToClass [EobCh], DNoState);
               PutDefault (DState, DNoState);
               INC (SentinelSavings);
            END;
         END;
      END;
      ReleaseSet (Defaults);
   END SaveSentinels;

PROCEDURE AddConstantREs() =
   VAR
      ruleList          : tTree         ;
      rule              : tTree         ;
      patternList       : tTree         ;
      pattern           : tTree         ;
      string1, string2  : tString       ;
      PatternNr         : SHORTCARD     ;
   BEGIN
      InitTraces();
      MakeSet (StartSet, StartStateCount);
      ruleList := Root;
      WHILE ruleList # NoTree DO
         rule := ruleList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 591
 $$ *).Son2;
         patternList := rule^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 592
 $$ *).Patterns;

         WHILE patternList # NoTree DO
            pattern := patternList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 595
 $$ *).Son2;
            IF pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 596
 $$ *).IsConstantRE THEN
               PatternNr := pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 597
 $$ *).PatternNr;
               PatternTablePtr^[PatternNr].ContextLng :=
                  ComputeLength (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 599
 $$ *).RightContext);
               ComputeConstantRE (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 600
 $$ *).RegExpr, string1); 
               ComputeConstantRE (pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 601
 $$ *).RightContext, string2);
               Concatenate (string1, string2);
               ResetTraces (Length (string1));
               FOR StartState := 1 TO StartStateCount DO
                  IF IsElement (StartState, pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 605
 $$ *).StartStates) THEN
                     AddConstantRE (StartState, string1, PatternNr,
                        pattern^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 607
 $$ *).StartStates);
                  END;
               END;
            END;
            patternList := patternList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 611
 $$ *).Son1;
         END;
         ruleList := ruleList^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 613
 $$ *).Son1;
      END;
      ReleaseSet (StartSet);
      FinalizeTraces();
   END AddConstantREs;

PROCEDURE ComputeConstantRE (t: tTree; VAR String: tString) =
   VAR string2  : tString;
   BEGIN
      IF t = NoTree THEN
         Strings.AssignEmpty (String);
      ELSE
         CASE t^.vNode0(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode0' in line 625
 $$ *).Rule OF
         |  nSequence   => ComputeConstantRE (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 626
 $$ *).Son1, String);
                          ComputeConstantRE (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 627
 $$ *).Son2, string2);
                          Concatenate (String, string2);
         |  nChar       => Strings.AssignEmpty (String);
                          Append (String, t^.vNodeCh(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeCh' in line 630
 $$ *).Ch);
         |  nString     => GetString (t^.vNodeString(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeString' in line 631
 $$ *).String, String);
         END;
      END;
   END ComputeConstantRE;

PROCEDURE AddConstantRE (StartState: DStateRange; READONLY String: tString;
                        PatternNr: SHORTCARD; StartStates: tSet) =
   VAR
      Ch                : CHAR          ;
      State             ,
      Successor         ,
      NewState          ,
      PrevState         : DStateRange   ;
      ChIndex           : SHORTCARD     ;
      StringLength      : SHORTCARD     ;
      EndOfInput        : BOOLEAN       ;

   PROCEDURE GetCh (): CHAR =
      BEGIN
         IF ChIndex = StringLength THEN
            EndOfInput := TRUE;
            RETURN FirstCh;
         ELSE
            INC (ChIndex);
            RETURN Char (String, ChIndex);
         END;
      END GetCh;

   BEGIN
      StringLength      := Length (String);
      ChIndex           := 0;
      EndOfInput        := FALSE;
      State             := StartState;
      Ch                := GetCh ();
      PrevState         := State;

      LOOP                                      (* trace and do nothing *)
         IF EndOfInput THEN EXIT; END;
         Successor := GetTable (State, Ch);
         IF Successor = DNoState THEN EXIT; END;
         IF (Successor <= MaxAmbiguousState) AND
            IsElement (Successor, AmbiguousStates) THEN EXIT; END;
         GetStartSet (Successor, StartSet);
         IF NOT IsSubset (StartSet, StartStates) THEN EXIT; END;

         State := Successor;
         NewState := RecordedTrace (ChIndex, State);
         IF NewState # DNoState THEN
            PutTable (PrevState, Ch, NewState);
         ELSE
            RecordTrace (ChIndex, State, State);
            NewState := State;
         END;
         GetStartSet (NewState, StartSet);
         Include (StartSet, StartState);
         PutStartSet (NewState, StartSet);
         PrevState := NewState;
         Ch := GetCh ();
      END;

   (* INV EndOfInput OR
          Table [State, Ch] = DNoState OR
          Table [State, Ch] IN AmbiguousStates *)

      LOOP                                      (* trace and duplicate the path *)
         IF EndOfInput THEN EXIT END;
         Successor := GetTable (State, Ch);
         IF Successor # DNoState THEN
            State := Successor;
            NewState := RecordedTrace (ChIndex, State);
            IF NewState = DNoState THEN
               NewState := MakeDState ();
               GetDSemantics (State, dSemantics);
               PutDSemantics (NewState, dSemantics);
               PutDefault (NewState, State);
               RecordTrace (ChIndex, State, NewState);
            END;
            PutTable (PrevState, Ch, NewState);
            GetStartSet (NewState, StartSet);
            Include (StartSet, StartState);
            PutStartSet (NewState, StartSet);
            PrevState := NewState;
            Ch := GetCh ();
         ELSE
            IF GetDefault (State) = DNoState THEN EXIT END;
            State := GetDefault (State);
         END;
      END;

   (* INV EndOfInput OR Table [State, Ch] = DNoState *)

      LOOP                                      (* extend the path *)
         IF EndOfInput THEN EXIT END;
         NewState := RecordedTrace (ChIndex, DNoState);
         IF NewState = DNoState THEN
            NewState := MakeDState ();
            PutDefault (NewState, EobDefaultState);
            RecordTrace (ChIndex, DNoState, NewState);
         END;
         PutTable (PrevState, Ch, NewState);
         GetStartSet (NewState, StartSet);
         Include (StartSet, StartState);
         PutStartSet (NewState, StartSet);
         PrevState := NewState;
         Ch := GetCh ();
      END;

   (* INV EndOfInput *)

      GetDSemantics (PrevState, dSemantics);    (* process final state *)
      Include (dSemantics, PatternNr);
      PutDSemantics (PrevState, dSemantics);
   END AddConstantRE;

PROCEDURE UpdateContext() =
   VAR
      Max       : DStateRange   ;
   BEGIN
      IF DStateCount > NodeCount THEN
         WriteS (StdError, ARRAY [0..38] OF CHAR{'i','n','t','e','r','n','a','l',' ','E','r','r','o','r',':',' ','S','t','a','t','e','C','o','u','n','t',' ','>',' ','N','o','d','e','C','o','u','n','t','\000'}); WriteNl (StdError);
      END;

      FOR Pattern := 0 TO PatternCount - 2 DO
         IF PatternTablePtr^[Pattern].ContextLng = VariableContext THEN
            Max := Maximum (PatternTablePtr^[Pattern].DContext);
            FOR State1 := 1 TO Max DO
               IF IsElement (State1, PatternTablePtr^[Pattern].DContext) THEN
                  FOR State2 := 1 TO DStateCount DO
                     IF State1 = GetDefault (State2) THEN
                        Include (PatternTablePtr^[Pattern].DContext, State2);
                     END;
                  END;
               END;
            END;
         END;
      END;
   END UpdateContext;

PROCEDURE InvertMapping() =
   VAR
      Pattern   : SHORTCARD     ;
   BEGIN
      FOR Pattern := 0 TO PatternCount DO
         MakeSet (PatternTablePtr^[Pattern].Finals, DStateCount);
      END;

      FOR State := 1 TO DStateCount DO
         GetDSemantics (State, dSemantics);
         IF IsEmpty (dSemantics) THEN
            Include (PatternTablePtr^[0].Finals, State);
         ELSE
            Pattern := Minimum (dSemantics);
            Include (PatternTablePtr^[Pattern].Finals, State);
         END;
      END;
      IsComputedFinals := TRUE;
   END InvertMapping;

PROCEDURE CheckTables() =          (* check automaton for completeness *)
   VAR
      Ident     : Idents.tIdent ;
      StartState: SHORTCARD     ;
   BEGIN
      FOR Definition := 1 TO DefCount DO        (* FORALL StartStates *)
         IF GetKind (Definition) = tKind.Start THEN
            GetStartDef (Definition, Ident, StartState);
            CheckStartState (StartState, Ident, FALSE);
            IF LeftJustUsed THEN
               CheckStartState (StartState + 1, Ident, TRUE);
            END;
         END;
      END;
   END CheckTables;

PROCEDURE CheckStartState (StartState: SHORTCARD; Ident: Idents.tIdent; LeftJust: BOOLEAN) =
   VAR
      Ch        : CHAR          ;
      DState    : DStateRange   ;
      Undefined ,
      Semantics : tSet          ;
      String    : tString       ;
      Count     : INTEGER       ;
   BEGIN
      MakeSet (Undefined, ORD (OldLastCh));
      MakeSet (Semantics, PatternCount);
      Union (Undefined, Unused);

      FOR Ch := FirstCh TO LastCh DO
         DState := GetTable (StartState, Ch);
         IF DState = DNoState THEN
            IF Ch <= ClassCount THEN
               Union (Undefined, ClassMemPtr^[Ch]);
            ELSE
               Include (Undefined, ORD (ToChar [Ch]));
            END;
         ELSE
            GetDSemantics (DState, Semantics);
            IF IsEmpty (Semantics) THEN
               IF Ch <= ClassCount THEN
                  Union (Undefined, ClassMemPtr^[Ch]);
               ELSE
                  Include (Undefined, ORD (ToChar [Ch]));
               END;
            END;
         END;
      END;

      IF NOT IsEmpty (Undefined) THEN
         WriteS (StdError, ARRAY [0..24] OF CHAR{'W','a','r','n','i','n','g',':',' ','i','n',' ','s','t','a','r','t',' ','s','t','a','t','e',' ','\000'});
         Idents.GetString (Ident, String);
         Strings.WriteS (StdError, String);
         IF LeftJust THEN
            WriteS (StdError, ARRAY [0..57] OF CHAR{' ','t','h','e',' ','d','e','f','a','u','l','t',' ','a','c','t','i','o','n',' ','m','a','y',' ','b','e',' ','t','r','i','g','g','e','r','e','d',' ','b','y',' ','(','l','e','f','t',' ','j','u','s','t','i','f','i','e','d',')',':','\000'});
         ELSE
            WriteS (StdError, ARRAY [0..40] OF CHAR{' ','t','h','e',' ','d','e','f','a','u','l','t',' ','a','c','t','i','o','n',' ','m','a','y',' ','b','e',' ','t','r','i','g','g','e','r','e','d',' ','b','y',':','\000'});
         END;
         WriteNl (StdError);

         Count := 0;
         WHILE NOT IsEmpty (Undefined) DO
            Ch := VAL (Extract (Undefined),CHAR);
            WriteC (StdError, ' ');
            IF ('!' <= Ch) AND (Ch <= '~') THEN
               WriteC (StdError, '\'');
               WriteC (StdError, Ch);
               WriteC (StdError, '\'');
            ELSE
               WriteC (StdError, '\'');
               WriteI (StdError, ORD (Ch), 0);
            END;
            INC (Count);
            IF Count = 16 THEN WriteNl (StdError); Count := 0; END;
         END;
         WriteNl (StdError);
      END;

      ReleaseSet (Semantics);
      ReleaseSet (Undefined);
   END CheckStartState;

PROCEDURE WritePattern() =
   BEGIN
      FOR Pattern := 0 TO PatternCount - 2 DO
         IF PatternTablePtr^[Pattern].ContextLng # NoContext THEN
            WriteS (StdOutput, ARRAY [0..19] OF CHAR{'P','a','t','t','e','r','n',',',' ','C','o','n','t','e','x','t','L','n','g','\000'});
            WriteI (StdOutput, Pattern, 5);
            WriteI (StdOutput, PatternTablePtr^[Pattern].ContextLng, 5);
            IF PatternTablePtr^[Pattern].ContextLng = VariableContext THEN
               IF IsComputedNContext THEN
                  WriteS (StdOutput, ARRAY [0..10] OF CHAR{' ','N','C','o','n','t','e','x','t',' ','\000'});
                  WriteSet (StdOutput, PatternTablePtr^[Pattern].NContext);
               END;
               IF IsComputedDContext THEN
                  WriteS (StdOutput, ARRAY [0..10] OF CHAR{' ','D','C','o','n','t','e','x','t',' ','\000'});
                  WriteSet (StdOutput, PatternTablePtr^[Pattern].DContext);
               END;
            END;
            IF IsComputedFinals THEN
               WriteS (StdOutput, ARRAY [0..8] OF CHAR{' ','F','i','n','a','l','s',' ','\000'});
               WriteSet (StdOutput, PatternTablePtr^[Pattern].Finals);
            END;
            WriteNl (StdOutput);
         END;
      END;
   END WritePattern;

PROCEDURE WriteStatistics() =
   BEGIN
      WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'S','t','a','r','t',' ','S','t','a','t','e','s',' ',' ','\000'});
      WriteI (StdOutput, StartStateCount, 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'D','e','f','i','n','i','t','i','o','n','s',' ',' ',' ','\000'});
      WriteI (StdOutput, DefCount       , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'R','u','l','e','s',' ',' ',' ',' ',' ',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, RuleCount      , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'P','a','t','t','e','r','n','s',' ',' ',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, PatternCount   , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..22] OF CHAR{'C','l','a','s','s','e','s',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, ORD (ClassCount), 6);  WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..22] OF CHAR{'L','a','s','t','C','h',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, ORD (LastCh)   , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'T','r','a','n','s','i','t','i','o','n','s',' ',' ',' ','\000'});
      WriteI (StdOutput, TransitionCount, 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'L','e','a','f','s',' ',' ',' ',' ',' ',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, LeafCount      , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'N','F','A',' ','S','t','a','t','e','s',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, NStateCount    , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..16] OF CHAR{'M','i','n','i','m','i','z','e',' ','S','a','v','i','n','g','s','\000'});
      WriteI (StdOutput, MinimizeSavings, 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..16] OF CHAR{'A','m','b','i','g','u','o','u','s',' ','S','t','a','t','e','s','\000'});
      WriteI (StdOutput, MaxAmbiguousState, 6); WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'N','o','d','e','s',' ',' ',' ',' ',' ',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, NodeCount      , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'D','F','A',' ','S','t','a','t','e','s',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, DStateCount    , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..16] OF CHAR{'S','e','n','t','i','n','e','l',' ','S','a','v','i','n','g','s','\000'});
      WriteI (StdOutput, SentinelSavings, 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..22] OF CHAR{'D','e','f','a','u','l','t',' ','S','a','v','i','n','g','s',' ',' ',' ',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, DefaultSavings , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'T','a','b','l','e',' ','E','n','t','r','i','e','s',' ','\000'});
      WriteI (StdOutput, TableEntries   , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'T','a','b','l','e',' ','S','i','z','e',' ',' ',' ',' ','\000'});
      WriteI (StdOutput, TableSize      , 6);   WriteNl (StdOutput);
      WriteS (StdOutput, ARRAY [0..14] OF CHAR{'M','e','m','o','r','y',' ','u','s','e','d',' ',' ',' ','\000'});
      WriteI (StdOutput, MemoryUsed     , 6);   WriteNl (StdOutput);
   END WriteStatistics;

PROCEDURE GenerateTables (DebugLevel: SHORTCARD; ReduceCaseSize, Warnings: BOOLEAN; Optimize: SHORTINT) =
VAR i: SHORTINT;
BEGIN
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'S','t','a','r','t',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\000'}); END;
   IsComputedNContext   := FALSE;
   IsComputedDContext   := FALSE;
   IsComputedFinals     := FALSE;
   INC (RuleCount); INC (PatternCount); EobAction       := PatternCount;
   INC (RuleCount); INC (PatternCount); DefaultAction   := PatternCount;
   RuleToCodeSize       := RuleCount + 1;
   MakeArray            (LOOPHOLE(RuleToCodePtr,ADDRESS), RuleToCodeSize, BYTESIZE (CodeInfo));
   PatternTableSize     := PatternCount + 1;
   MakeArray            (LOOPHOLE(PatternTablePtr,ADDRESS), PatternTableSize, BYTESIZE (PatternInfo));
   PatternTablePtr^[0].ContextLng := NoContext;

   MakeSet              (dSemantics, PatternCount);
   ComputeNfa();          IF DebugLevel >= 15 THEN WriteNfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','u','t','e','N','f','a',' ',' ',' ',' ',' ',' ','\000'}); END;
   ComputeDfa();          IF DebugLevel >= 14 THEN WriteDfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','u','t','e','D','f','a',' ',' ',' ',' ',' ',' ','\000'}); END;
   MinimizeDfa();         IF DebugLevel >= 13 THEN WriteDfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'M','i','n','i','m','i','z','e','D','f','a',' ',' ',' ',' ',' ','\000'}); END;

   EobDefaultState      := MakeDState ();       (* has to be ambiguous *)
   ComputeSuccGraph();
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','u','t','e','S','u','c','c','G','r','a','p','h','\000'}); END;
   ComputeAmbiguousStates();
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','u','t','e','A','m','b','i','g','u','o','u','s','\000'}); END;
   ComputeCyclicStates(); IF DebugLevel >= 12 THEN
                           WriteSet (StdOutput, AmbiguousStates );
                           WriteNl  (StdOutput);
                           WriteSet (StdOutput, CyclicStates    );
                           WriteNl  (StdOutput);
                        END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','u','t','e','C','y','c','l','i','c','S','t','a','\000'}); END;

   ComputeStartSets();    IF DebugLevel >= 11 THEN WriteDfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','u','t','e','S','t','a','r','t','S','e','t','s','\000'}); END;

   EobState             := MakeDState ();
   AssignElmt           (dSemantics, EobAction);
   PutDSemantics        (EobState, dSemantics);
   AssignElmt           (dSemantics, DefaultAction);    (* default state *)
   PutDSemantics        (MakeDState (), dSemantics);

   AddConstantREs();      IF DebugLevel >= 10 THEN WriteDfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'A','d','d','C','o','n','s','t','a','n','t','R','E','s',' ',' ','\000'}); END;
   UpdateContext();       IF DebugLevel >= 9 THEN WriteDfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'U','p','d','a','t','e','C','o','n','t','e','x','t',' ',' ',' ','\000'}); END;
   SaveEobTransitions();  IF DebugLevel >= 8 THEN WriteDfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'S','a','v','e','E','o','b','T','r','a','n','s','i','t','i','o','\000'}); END;
   SaveSentinels();       IF DebugLevel >= 7 THEN WriteDfa(); WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'S','a','v','e','S','e','n','t','i','n','e','l','s',' ',' ',' ','\000'}); END;
IF Optimize > 0 THEN
   i := 1;
   WHILE i <= MaxAmbiguousState DO
      ComputeDefaults   (i, Min (MaxAmbiguousState, i + Optimize - 1));
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','u','t','e','D','e','f','a','u','l','t','s',' ','\000'}); END;
      INC (i, Optimize);
   END;
END;
                        IF DebugLevel >= 6 THEN WriteDfa(); WritePattern(); END;
   InvertMapping();       IF DebugLevel >= 5 THEN WritePattern(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'I','n','v','e','r','t','M','a','p','p','i','n','g',' ',' ',' ','\000'}); END;
   MakeTables (ReduceCaseSize);
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'M','a','k','e','T','a','b','l','e','s',' ',' ',' ',' ',' ',' ','\000'}); END;
   CompressTables (Optimize);
                        IF DebugLevel >= 4 THEN WriteTables(); END;
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','o','m','p','r','e','s','s','T','a','b','l','e','s',' ',' ','\000'}); END;
IF Language = tLanguage.Modula THEN
   PutTables (ReduceCaseSize);
                        IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'P','u','t','T','a','b','l','e','s',' ',' ',' ',' ',' ',' ',' ','\000'}); END;
END;
                        IF DebugLevel >= 3 THEN QueryTables(); END;
IF Warnings THEN
   CheckTables();         IF DebugLevel >= 2 THEN WriteStepTime (ARRAY [0..16] OF CHAR{'C','h','e','c','k','T','a','b','l','e','s',' ',' ',' ',' ',' ','\000'}); END;
END;
                        IF DebugLevel >= 1 THEN WriteStatistics(); END;
END GenerateTables;

BEGIN
END GenTabs.

