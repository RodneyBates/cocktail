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

UNSAFE MODULE GenTabs 


; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT HALT , SHORTINT , SHORTCARD 

; FROM General IMPORT Min 

; FROM Memory IMPORT Alloc , Free , MemoryUsed 

; FROM DynArray IMPORT MakeArray , ExtendArray , ReleaseArray 

; FROM Strings IMPORT tString , Char , Length , Concatenate , Append 

; FROM StringMem IMPORT GetString 

; FROM Times IMPORT WriteStepTime 

; FROM Sets 
  IMPORT tSet , tElement , MakeSet , ReleaseSet , Union , Intersection 
  , Include 
  , Exclude , Minimum , Extract , IsEqual , IsElement , IsEmpty , Assign 
  , AssignElmt 
  , AssignEmpty , ForallDo , Maximum , IsSubset , WriteSet 

; FROM ReuseIO 
  IMPORT WriteT , WriteNl , WriteI , WriteC , StdOutput , StdError 

; FROM DefTable IMPORT GetKind , DefCount , GetStartDef , tKind 

; FROM Tree 
  IMPORT nAlternative , nSequence , nRepetition , nOption , nChar , nSet 
  , nString 
  , tTree , NoTree 

; FROM Nfa 
  IMPORT NStateRange , TransitionRange , NStateCount , TransitionCount 
  , PutNSemantics 
  , GetNSemantics , PutTransitions , GetTransitions , MakeNState 
  , MakeTransition 
  , IsLastTransition , NextTransition , GetCh , GetNextState , NoTransition 
  , WriteNfa 
  , AddTransition , CopyTransitions , UniteTransitions , BeginNfa 
  , FinalizeNfa 

; FROM Dfa 
  IMPORT DNoState , DStateRange , DStateCount , MakeDState , GetTable 
  , PutTable 
  , GetDSemantics , PutDSemantics , GetStartSet , PutStartSet 
  , ComputeStartSets , WriteDfa , GetDefault , PutDefault , GetFirst 
  , GetLast 
  , EobState , EobDefaultState , FirstCh , LastCh , OldLastCh , EobCh 
  , CyclicStates 
  , AmbiguousStates , MaxAmbiguousState , ComputeSuccGraph 
  , ComputeCyclicStates , ComputeAmbiguousStates , MinimizeDfa 
  , MinimizeSavings 
  , SaveEobTransitions , ComputeDefaults , DefaultSavings 

; FROM Traces 
  IMPORT InitTraces , ResetTraces , RecordTrace , RecordedTrace 
  , FinalizeTraces 

; FROM ScanTabs 
  IMPORT NoRule , TableSize , TableEntries , MakeTables , CompressTables 
  , PutTables 
  , QueryTables , WriteTables 

; FROM ScanGen IMPORT Language , tLanguage 

; FROM Classes IMPORT ClassCount , ToClass , ClassMemPtr , ToChar , Unused 

; IMPORT Word , Strings , Idents 

; TYPE SetOfNInfoPtr = UNTRACED BRANDED REF SetOfNInfo 
  ; SetOfNInfo 
    = RECORD 
        Next : SetOfNInfoPtr 
      ; Set : tSet 
      ; DState : DStateRange 
      END (* RECORD *) 
  ; MapDToSetOfN = ARRAY [ 0 .. 100000 ] OF SetOfNInfoPtr 
  ; HashDToSetOfN = ARRAY [ 0 .. 100000 ] OF SetOfNInfoPtr 
  ; Stack = ARRAY [ 0 .. 100000 ] OF DStateRange 

; VAR MapDToSetOfNPtr : UNTRACED BRANDED REF MapDToSetOfN 
  ; MapDToSetOfNSize : M2LONGINT 

  ; HashDToSetOfNPtr : UNTRACED BRANDED REF HashDToSetOfN 
  ; HashDToSetOfNSize : M2LONGINT 

  ; StackPtr : UNTRACED BRANDED REF Stack 
  ; StackSize : M2LONGINT 
  ; StackTop : DStateRange 

  ; StartSet , dSemantics : tSet 
  ; SentinelSavings : INTEGER 

  ; IsComputedNContext : BOOLEAN 
  ; IsComputedDContext : BOOLEAN 
  ; IsComputedFinals : BOOLEAN 

; PROCEDURE ComputeNfa ( ) 

  = VAR t1 , t2 : TransitionRange 
    ; f1 , f2 : tSet 
    ; o1 , o2 : BOOLEAN 
    ; ruleList : tTree 
    ; rule : tTree 
    ; patternList : tTree 
    ; pattern : tTree 
    ; RuleNr : SHORTCARD 
    ; length : SHORTINT 

  ; BEGIN (* ComputeNfa *) 
      BeginNfa ( ) 
    ; FOR NState := 1 TO StartStateCount 
      DO IF MakeNState ( NoTransition ) # NState THEN HALT ( ) END (* IF *) 
                                                                  (* ASSERT *) 
      END (* FOR *) 

    ; MakeSet ( f1 , LeafCount ) 
    ; MakeSet ( f2 , LeafCount ) 
    ; ruleList := Root 

    ; WHILE ruleList # NoTree 
      DO rule := ruleList ^ . vNode2 . Son2 
      ; RuleNr := rule ^ . vNodeRule . RuleNr 
      ; RuleToCodePtr ^ [ RuleNr ] . Text := rule ^ . vNodeRule . TargetCode 
      ; RuleToCodePtr ^ [ RuleNr ] . TextLine := rule ^ . vNodeRule . Line 
      ; RuleToCodePtr ^ [ RuleNr ] . CodeMode 
          := rule ^ . vNodeRule . CodeMode 
      ; patternList := rule ^ . vNodeRule . Patterns 

      ; WHILE patternList # NoTree 
        DO pattern := patternList ^ . vNode2 . Son2 
        ; PatternNr := pattern ^ . vNodePattern . PatternNr 
        ; WITH With_7 = PatternTablePtr ^ [ PatternNr ] 
          DO With_7 . Rule := RuleNr 
          ; With_7 . ContextLng := NoContext 
          ; With_7 . Position := pattern ^ . vNodePattern . Position 
          END (* WITH *) 
        ; IF NOT pattern ^ . vNodePattern . IsConstantRE 
          THEN 
            AttributeEvaluator 
              ( pattern ^ . vNodePattern . RegExpr , t1 , f1 , o1 ) 
          ; AttributeEvaluator 
              ( pattern ^ . vNodePattern . RightContext , t2 , f2 , o2 ) 
          ; tt := t1 
          ; ForallDo 
              ( pattern ^ . vNodePattern . StartStates , ExtendTransitions ) 
          ; IF o2 THEN ForallDo ( f1 , EnterNSemantics ) END (* IF *) 
          ; tt := t2 
          ; ForallDo ( f1 , ExtendTransitions ) 
          ; ForallDo ( f2 , EnterNSemantics ) 
                                             (* context *) 
          ; length 
              := ComputeLength ( pattern ^ . vNodePattern . RightContext ) 
          ; IF length # VariableContext 
            THEN 
              PatternTablePtr ^ [ PatternNr ] . ContextLng := length 
            ELSE 
              length := ComputeLength ( pattern ^ . vNodePattern . RegExpr ) 
            ; IF length # VariableContext 
              THEN 
                PatternTablePtr ^ [ PatternNr ] . ContextLng := - length 
              ELSE 
                PatternTablePtr ^ [ PatternNr ] . ContextLng 
                  := VariableContext 
              ; MakeSet 
                  ( PatternTablePtr ^ [ PatternNr ] . NContext , LeafCount ) 
              ; Assign ( PatternTablePtr ^ [ PatternNr ] . NContext , f1 ) 
              END (* IF *) 
            END (* IF *) 
          END (* IF *) 
        ; patternList := patternList ^ . vNode2 . Son1 
        END (* WHILE *) 
      ; ruleList := ruleList ^ . vNode2 . Son1 
      END (* WHILE *) 

    ; IsComputedNContext := TRUE 
    ; ReleaseSet ( f1 ) 
    ; ReleaseSet ( f2 ) 
    END ComputeNfa 

; PROCEDURE ComputeLength ( t : tTree ) : SHORTINT 

  = VAR l1 , l2 : SHORTINT 
    ; string : tString 

  ; BEGIN (* ComputeLength *) 
      IF t = NoTree THEN RETURN NoContext END (* IF *) 

    ; CASE t ^ . Rule 
      OF nAlternative 
      => l1 := ComputeLength ( t ^ . vNode2 . Son1 ) 
      ; l2 := ComputeLength ( t ^ . vNode2 . Son2 ) 
      ; IF l1 = l2 THEN RETURN l1 ELSE RETURN VariableContext END (* IF *) 

      | nSequence 
      => l1 := ComputeLength ( t ^ . vNode2 . Son1 ) 
      ; l2 := ComputeLength ( t ^ . vNode2 . Son2 ) 
      ; IF ( l1 # VariableContext ) AND ( l2 # VariableContext ) 
        THEN 
          RETURN l1 + l2 
        ELSE 
          RETURN VariableContext 
        END (* IF *) 

      | nRepetition , nOption 
      => RETURN VariableContext 

      | nChar , nSet 
      => RETURN 1 

      | nString 
      => GetString ( t ^ . vNodeString . String , string ) 
      ; RETURN Length ( string ) 
      END (* CASE *) 
    END ComputeLength 

; PROCEDURE AttributeEvaluator 
    ( t : tTree 
    ; VAR Transitions : TransitionRange 
    ; VAR FinalStates : tSet 
    ; VAR IsOptional : BOOLEAN 
    ) 

  = VAR t1 , t2 : TransitionRange 
    ; f1 , f2 : tSet 
    ; o1 , o2 : BOOLEAN 
    ; NState : NStateRange 
    ; string : tString 

  ; BEGIN (* AttributeEvaluator *) 
      IF t = NoTree 
      THEN 
        Transitions := NoTransition 
      ; AssignEmpty ( FinalStates ) 
      ; IsOptional := TRUE 
      ; RETURN 
      END (* IF *) 

    ; CASE t ^ . Rule 

      OF nAlternative 
      => (* regExpr = Alternative (regExpr regExpr) *) 
         MakeSet ( f1 , LeafCount ) 
      ; MakeSet ( f2 , LeafCount ) 
      ; AttributeEvaluator ( t ^ . vNode2 . Son1 , t1 , f1 , o1 ) 
      ; AttributeEvaluator ( t ^ . vNode2 . Son2 , t2 , f2 , o2 ) 
      ; Transitions := UniteTransitions ( t1 , t2 ) 
      ; Assign ( FinalStates , f1 ) 
      ; Union ( FinalStates , f2 ) 
      ; IsOptional := o1 OR o2 
      ; ReleaseSet ( f1 ) 
      ; ReleaseSet ( f2 ) 

      | nSequence 
      => (* regExpr = Sequence (regExpr regExpr) *) 
         MakeSet ( f1 , LeafCount ) 
      ; MakeSet ( f2 , LeafCount ) 
      ; AttributeEvaluator ( t ^ . vNode2 . Son1 , t1 , f1 , o1 ) 
      ; AttributeEvaluator ( t ^ . vNode2 . Son2 , t2 , f2 , o2 ) 
      ; tt := t2 
      ; ForallDo ( f1 , ExtendTransitions ) 
      ; IF o1 
        THEN 
          Transitions := UniteTransitions ( t1 , t2 ) 
        ELSE 
          Transitions := t1 
        END (* IF *) 
      ; IF o2 
        THEN 
          Assign ( FinalStates , f1 ) 
        ; Union ( FinalStates , f2 ) 
        ELSE 
          Assign ( FinalStates , f2 ) 
        END (* IF *) 
      ; IsOptional := o1 AND o2 
      ; ReleaseSet ( f1 ) 
      ; ReleaseSet ( f2 ) 

      | nRepetition 
      => (* regExpr = Repetition (regExpr) *) 
         MakeSet ( f1 , LeafCount ) 
      ; AttributeEvaluator ( t ^ . vNode1 . Son1 , t1 , f1 , o1 ) 
      ; tt := t1 
      ; ForallDo ( f1 , ExtendTransitions ) 
      ; Transitions := t1 
      ; Assign ( FinalStates , f1 ) 
      ; IsOptional := o1 
      ; ReleaseSet ( f1 ) 

      | nOption 
      => (* regExpr = Option (regExpr) *) 
         MakeSet ( f1 , LeafCount ) 
      ; AttributeEvaluator ( t ^ . vNode1 . Son1 , t1 , f1 , o1 ) 
      ; Transitions := t1 
      ; Assign ( FinalStates , f1 ) 
      ; IsOptional := TRUE 
      ; ReleaseSet ( f1 ) 

      | nChar 
      => (* regExpr = Char *) 
         NState := MakeNState ( NoTransition ) 
      ; Transitions := MakeTransition ( t ^ . vNodeCh . Ch , NState ) 
      ; AssignElmt ( FinalStates , NState ) 
      ; IsOptional := FALSE 

      | nSet 
      => (* regExpr = Set *) 
         MakeSet ( f1 , ORD ( LastCh ) ) 
      ; Assign ( f1 , t ^ . vNodeSet . Set ) 
      ; NState := MakeNState ( NoTransition ) 
      ; Transitions := NoTransition 
      ; WHILE NOT IsEmpty ( f1 ) 
        DO Transitions 
             := AddTransition 
                  ( MakeTransition ( VAL ( Extract ( f1 ) , CHAR ) , NState ) 
                  , Transitions 
                  ) 
        END (* WHILE *) 
      ; AssignElmt ( FinalStates , NState ) 
      ; IsOptional := FALSE 
      ; ReleaseSet ( f1 ) 

      | nString 
      => (* regExpr = String *) 
         GetString ( t ^ . vNodeString . String , string ) 
      ; NState := MakeNState ( NoTransition ) 
      ; Transitions 
          := MakeTransition ( Char ( string , Length ( string ) ) , NState ) 
      ; AssignElmt ( FinalStates , NState ) 
      ; FOR i := Length ( string ) - 1 TO 1 BY - 1 
        DO NState := MakeNState ( Transitions ) 
        ; Transitions := MakeTransition ( Char ( string , i ) , NState ) 
        END (* FOR *) 
      ; IsOptional := FALSE 
      END (* CASE *) 
    END AttributeEvaluator 

; VAR tt : TransitionRange 
; VAR PatternNr : SHORTCARD 

; PROCEDURE ExtendTransitions ( NState : tElement ) 

  = BEGIN (* ExtendTransitions *) 
      PutTransitions 
        ( NState 
        , UniteTransitions 
            ( GetTransitions ( NState ) , CopyTransitions ( tt ) ) 
        ) 
    END ExtendTransitions 

; PROCEDURE EnterNSemantics ( NState : tElement ) 

  = BEGIN (* EnterNSemantics *) 
      PutNSemantics ( NState , PatternNr ) 
    END EnterNSemantics 

; PROCEDURE MapSetOfNToD ( t : tSet ) : DStateRange 

  = VAR DState : DStateRange 
    ; Hash : Word . T 
    ; Current : SetOfNInfoPtr 

  ; BEGIN (* MapSetOfNToD *) 
      Hash := Maximum ( t ) MOD LOOPHOLE ( NStateCount , Word . T ) 
    ; Current := HashDToSetOfNPtr ^ [ Hash ] 
    ; WHILE Current # NIL 
      DO                                        (* t IN S' ? *) 
         IF IsEqual ( Current ^ . Set , t ) 
         THEN 
           RETURN Current ^ . DState            (* yes *) 
         END (* IF *) 
      ; Current := Current ^ . Next 
      END (* WHILE *) 

    ; DState := MakeDState ( )                  (* no: S' := S' UNION {t} *) 
    ; IF DState = MapDToSetOfNSize 
      THEN 
        ExtendArray 
          ( LOOPHOLE ( MapDToSetOfNPtr , ADDRESS ) 
          , MapDToSetOfNSize 
          , BYTESIZE ( SetOfNInfoPtr ) 
          ) 
      END (* IF *) 
    ; MapDToSetOfNPtr ^ [ DState ] := Alloc ( BYTESIZE ( SetOfNInfo ) ) 
    ; MakeSet ( MapDToSetOfNPtr ^ [ DState ] ^ . Set , NStateCount ) 
    ; Assign ( MapDToSetOfNPtr ^ [ DState ] ^ . Set , t ) 
    ; MapDToSetOfNPtr ^ [ DState ] ^ . DState := DState 
    ; MapDToSetOfNPtr ^ [ DState ] ^ . Next := HashDToSetOfNPtr ^ [ Hash ] 
    ; HashDToSetOfNPtr ^ [ Hash ] := MapDToSetOfNPtr ^ [ DState ] 

    ; INC ( StackTop )                          (* push (y) *) 
    ; IF StackTop = StackSize 
      THEN 
        ExtendArray 
          ( LOOPHOLE ( StackPtr , ADDRESS ) 
          , StackSize 
          , BYTESIZE ( DStateRange ) 
          ) 
      END (* IF *) 
    ; StackPtr ^ [ StackTop ] := DState 
    ; RETURN DState 
    END MapSetOfNToD 

; PROCEDURE ComputeDfa ( ) 

  = CONST InitialStackSize = 64 

  ; VAR DState : DStateRange 
    ; x : tSet 
    ; y : ARRAY CHAR OF tSet 
    ; Transition : TransitionRange 
    ; Ch : CHAR 
    ; CharSet : tSet 
    ; nStates : tSet 

  ; BEGIN (* ComputeDfa *) 
      StackSize := InitialStackSize             (* initialize *) 
    ; MakeArray 
        ( LOOPHOLE ( StackPtr , ADDRESS ) 
        , StackSize 
        , BYTESIZE ( DStateRange ) 
        ) 
    ; StackTop := 0 
    ; MapDToSetOfNSize := LeafCount 
    ; MakeArray 
        ( LOOPHOLE ( MapDToSetOfNPtr , ADDRESS ) 
        , MapDToSetOfNSize 
        , BYTESIZE ( SetOfNInfoPtr ) 
        ) 
    ; HashDToSetOfNSize := NStateCount 
    ; MakeArray 
        ( LOOPHOLE ( HashDToSetOfNPtr , ADDRESS ) 
        , HashDToSetOfNSize 
        , BYTESIZE ( SetOfNInfoPtr ) 
        ) 
    ; FOR NState := 0 TO NStateCount - 1 
      DO HashDToSetOfNPtr ^ [ NState ] := NIL 
      END (* FOR *) 
    ; MakeSet ( x , NStateCount ) 
    ; FOR Ch := FirstCh TO LastCh 
      DO MakeSet ( y [ Ch ] , NStateCount ) 
      END (* FOR *) 
    ; MakeSet ( CharSet , ORD ( LastCh ) ) 
    ; MakeSet ( nStates , LeafCount ) 

    ; FOR NState := 1 TO StartStateCount 
      DO                                        (* FORALL start states *) 
         AssignElmt ( x , NState )              (* map+push (start state) *) 
      ; DState := MapSetOfNToD ( x ) 
      ; IF DState # NState THEN HALT ( ) END (* IF *)  (* ASSERT *) 
      END (* FOR *) 

    ; WHILE StackTop > 0 
      DO DState := StackPtr ^ [ StackTop ]      (* DState := pop () *) 
      ; DEC ( StackTop ) 
      ; Assign ( x , MapDToSetOfNPtr ^ [ DState ] ^ . Set ) 
      ; AssignEmpty ( CharSet ) 

      ; FOR NState := 1 TO NStateCount 
        DO IF IsElement ( NState , x ) 
           THEN 
             Transition := GetTransitions ( NState ) 
           ; WHILE NOT IsLastTransition ( Transition ) 
             DO Ch := GetCh ( Transition ) 
             ; Include ( y [ Ch ] , GetNextState ( Transition ) ) 
             ; Include ( CharSet , ORD ( Ch ) ) 
             ; Transition := NextTransition ( Transition ) 
             END (* WHILE *) 
           END (* IF *) 
        END (* FOR *) 

      ; WHILE NOT IsEmpty ( CharSet ) 
        DO Ch := VAL ( Extract ( CharSet ) , CHAR ) 
        ; PutTable ( DState , Ch , MapSetOfNToD ( y [ Ch ] ) ) 
        ; AssignEmpty ( y [ Ch ] ) 
        END (* WHILE *) 
      END (* WHILE *) 

    ; INC ( NodeCount , DStateCount + 3 ) 
    ; FOR Pattern := 1 TO PatternCount - 2 
      DO                                        (* context *) 
         IF PatternTablePtr ^ [ Pattern ] . ContextLng = VariableContext 
         THEN 
           MakeSet ( PatternTablePtr ^ [ Pattern ] . DContext , NodeCount ) 
         ; FOR DState := 1 TO DStateCount 
           DO Assign ( nStates , PatternTablePtr ^ [ Pattern ] . NContext ) 
           ; Intersection ( nStates , MapDToSetOfNPtr ^ [ DState ] ^ . Set ) 
           ; IF NOT IsEmpty ( nStates ) 
             THEN 
               Include ( PatternTablePtr ^ [ Pattern ] . DContext , DState ) 
             END (* IF *) 
           END (* FOR *) 
         ; ReleaseSet ( PatternTablePtr ^ [ Pattern ] . NContext ) 
         END (* IF *) 
      END (* FOR *) 
    ; IsComputedNContext := FALSE 
    ; IsComputedDContext := TRUE 

    ; FOR DState := 1 TO DStateCount 
      DO                                        (* semantics *) 
         dState := DState 
      ; AssignEmpty ( dSemantics ) 
      ; ForallDo ( MapDToSetOfNPtr ^ [ DState ] ^ . Set , EnterDSemantics ) 
      ; Exclude ( dSemantics , NoRule ) 
      ; PutDSemantics ( DState , dSemantics ) 
      END (* FOR *) 

    ; FOR DState := 1 TO DStateCount 
      DO                                        (* clean up *) 
         ReleaseSet ( MapDToSetOfNPtr ^ [ DState ] ^ . Set ) 
      ; Free ( BYTESIZE ( SetOfNInfo ) , MapDToSetOfNPtr ^ [ DState ] ) 
      END (* FOR *) 
    ; ReleaseSet ( x ) 
    ; FOR Ch := FirstCh TO LastCh DO ReleaseSet ( y [ Ch ] ) END (* FOR *) 
    ; ReleaseSet ( CharSet ) 
    ; ReleaseSet ( nStates ) 
    ; ReleaseArray ( StackPtr , StackSize , BYTESIZE ( DStateRange ) ) 
    ; ReleaseArray 
        ( MapDToSetOfNPtr , MapDToSetOfNSize , BYTESIZE ( SetOfNInfoPtr ) ) 
    ; ReleaseArray 
        ( HashDToSetOfNPtr , HashDToSetOfNSize , BYTESIZE ( SetOfNInfoPtr ) ) 
    ; FinalizeNfa ( ) 
    END ComputeDfa 

; VAR dState : DStateRange 

; PROCEDURE EnterDSemantics ( NState : tElement ) 

  = BEGIN (* EnterDSemantics *) 
      Include ( dSemantics , GetNSemantics ( NState ) ) 
    END EnterDSemantics 

; PROCEDURE SaveSentinels ( ) 

  = VAR Default : DStateRange 
    ; Success : BOOLEAN 
    ; Ch , LastCh : CHAR 
    ; Defaults : tSet 

  ; BEGIN (* SaveSentinels *) 

      (* no end of buffer sentinel necessary for absolute final states: *) 
      (* - state must have semantics (to be final state)                *) 
      (* - may not use a default state (except EobDefaultState)         *) 
      (* - may not be used as default state                             *) 
      (* - no transitions may be defined (except on EobCh)              *) 

      SentinelSavings := 0 
    ; MakeSet ( Defaults , DStateCount ) 
    ; FOR DState := 1 TO DStateCount 
      DO Include ( Defaults , GetDefault ( DState ) ) 
      END (* FOR *) 

    ; FOR DState := 1 TO DStateCount 
      DO GetDSemantics ( DState , dSemantics ) 
      ; Default := GetDefault ( DState ) 
      ; IF ( NOT IsEmpty ( dSemantics ) ) 
           AND                                      (* final state ?         *) 
               ( ( Default = DNoState ) 
                 OR                               (* don't use default ?   *) 
                    ( Default = EobDefaultState ) 
               ) 
           AND ( NOT IsElement ( DState , Defaults ) ) 
        THEN (* not used as default ? *) 

          Success := TRUE                         (* check transitions     *) 
        ; Ch := GetFirst ( DState ) 
        ; LastCh := GetLast ( DState ) 
        ; IF Ch <= LastCh 
          THEN 
            LOOP 
              IF ( Ch # ToClass [ EobCh ] ) 
                 AND ( GetTable ( DState , Ch ) # DNoState ) 
              THEN 
                Success := FALSE 
              ; EXIT 
              END (* IF *) 
            ; IF Ch = LastCh THEN EXIT END (* IF *) 
            ; INC ( Ch ) 
            END (* LOOP *) 
          END (* IF *) 

        ; IF Success 
          THEN                                  (* absolute final state ? *) 
            PutTable ( DState , ToClass [ EobCh ] , DNoState ) 
          ; PutDefault ( DState , DNoState ) 
          ; INC ( SentinelSavings ) 
          END (* IF *) 
        END (* IF *) 
      END (* FOR *) 
    ; ReleaseSet ( Defaults ) 
    END SaveSentinels 

; PROCEDURE AddConstantREs ( ) 

  = VAR ruleList : tTree 
    ; rule : tTree 
    ; patternList : tTree 
    ; pattern : tTree 
    ; string1 , string2 : tString 
    ; PatternNr : SHORTCARD 

  ; BEGIN (* AddConstantREs *) 
      InitTraces ( ) 
    ; MakeSet ( StartSet , StartStateCount ) 
    ; ruleList := Root 
    ; WHILE ruleList # NoTree 
      DO rule := ruleList ^ . vNode2 . Son2 
      ; patternList := rule ^ . vNodeRule . Patterns 

      ; WHILE patternList # NoTree 
        DO pattern := patternList ^ . vNode2 . Son2 
        ; IF pattern ^ . vNodePattern . IsConstantRE 
          THEN 
            PatternNr := pattern ^ . vNodePattern . PatternNr 
          ; PatternTablePtr ^ [ PatternNr ] . ContextLng 
              := ComputeLength ( pattern ^ . vNodePattern . RightContext ) 
          ; ComputeConstantRE ( pattern ^ . vNodePattern . RegExpr , string1 ) 
          ; ComputeConstantRE 
              ( pattern ^ . vNodePattern . RightContext , string2 ) 
          ; Concatenate ( string1 , string2 ) 
          ; ResetTraces ( Length ( string1 ) ) 
          ; FOR StartState := 1 TO StartStateCount 
            DO IF IsElement 
                    ( StartState , pattern ^ . vNodePattern . StartStates ) 
               THEN 
                 AddConstantRE 
                   ( StartState 
                   , string1 
                   , PatternNr 
                   , pattern ^ . vNodePattern . StartStates 
                   ) 
               END (* IF *) 
            END (* FOR *) 
          END (* IF *) 
        ; patternList := patternList ^ . vNode2 . Son1 
        END (* WHILE *) 
      ; ruleList := ruleList ^ . vNode2 . Son1 
      END (* WHILE *) 
    ; ReleaseSet ( StartSet ) 
    ; FinalizeTraces ( ) 
    END AddConstantREs 

; PROCEDURE ComputeConstantRE ( t : tTree ; VAR String : tString ) 

  = VAR string2 : tString 

  ; BEGIN (* ComputeConstantRE *) 
      IF t = NoTree 
      THEN 
        Strings . AssignEmpty ( String ) 
      ELSE 
        CASE t ^ . Rule 
        OF nSequence 
        => ComputeConstantRE ( t ^ . vNode2 . Son1 , String ) 
        ; ComputeConstantRE ( t ^ . vNode2 . Son2 , string2 ) 
        ; Concatenate ( String , string2 ) 
        | nChar 
        => Strings . AssignEmpty ( String ) 
        ; Append ( String , t ^ . vNodeCh . Ch ) 
        | nString 
        => GetString ( t ^ . vNodeString . String , String ) 
        END (* CASE *) 
      END (* IF *) 
    END ComputeConstantRE 

; PROCEDURE AddConstantRE 
    ( StartState : DStateRange 
    ; READONLY String : tString 
    ; PatternNr : SHORTCARD 
    ; StartStates : tSet 
    ) 

  = VAR Ch : CHAR 
    ; State , Successor , NewState , PrevState : DStateRange 
    ; ChIndex : SHORTCARD 
    ; StringLength : SHORTCARD 
    ; EndOfInput : BOOLEAN 

  ; PROCEDURE GetCh ( ) : CHAR 

    = BEGIN (* GetCh *) 
        IF ChIndex = StringLength 
        THEN 
          EndOfInput := TRUE 
        ; RETURN FirstCh 
        ELSE 
          INC ( ChIndex ) 
        ; RETURN Char ( String , ChIndex ) 
        END (* IF *) 
      END GetCh 

  ; BEGIN (* AddConstantRE *) 
      StringLength := Length ( String ) 
    ; ChIndex := 0 
    ; EndOfInput := FALSE 
    ; State := StartState 
    ; Ch := GetCh ( ) 
    ; PrevState := State 

    ; LOOP                                      (* trace and do nothing *) 
        IF EndOfInput THEN EXIT END (* IF *) 
      ; Successor := GetTable ( State , Ch ) 
      ; IF Successor = DNoState THEN EXIT END (* IF *) 
      ; IF ( Successor <= MaxAmbiguousState ) 
           AND IsElement ( Successor , AmbiguousStates ) 
        THEN 
          EXIT 
        END (* IF *) 
      ; GetStartSet ( Successor , StartSet ) 
      ; IF NOT IsSubset ( StartSet , StartStates ) THEN EXIT END (* IF *) 

      ; State := Successor 
      ; NewState := RecordedTrace ( ChIndex , State ) 
      ; IF NewState # DNoState 
        THEN 
          PutTable ( PrevState , Ch , NewState ) 
        ELSE 
          RecordTrace ( ChIndex , State , State ) 
        ; NewState := State 
        END (* IF *) 
      ; GetStartSet ( NewState , StartSet ) 
      ; Include ( StartSet , StartState ) 
      ; PutStartSet ( NewState , StartSet ) 
      ; PrevState := NewState 
      ; Ch := GetCh ( ) 
      END (* LOOP *) 

   (* INV EndOfInput OR 
          Table [State, Ch] = DNoState OR 
          Table [State, Ch] IN AmbiguousStates *) 

    ; LOOP                                      (* trace and duplicate the path *) 
        IF EndOfInput THEN EXIT END (* IF *) 
      ; Successor := GetTable ( State , Ch ) 
      ; IF Successor # DNoState 
        THEN 
          State := Successor 
        ; NewState := RecordedTrace ( ChIndex , State ) 
        ; IF NewState = DNoState 
          THEN 
            NewState := MakeDState ( ) 
          ; GetDSemantics ( State , dSemantics ) 
          ; PutDSemantics ( NewState , dSemantics ) 
          ; PutDefault ( NewState , State ) 
          ; RecordTrace ( ChIndex , State , NewState ) 
          END (* IF *) 
        ; PutTable ( PrevState , Ch , NewState ) 
        ; GetStartSet ( NewState , StartSet ) 
        ; Include ( StartSet , StartState ) 
        ; PutStartSet ( NewState , StartSet ) 
        ; PrevState := NewState 
        ; Ch := GetCh ( ) 
        ELSE 
          IF GetDefault ( State ) = DNoState THEN EXIT END (* IF *) 
        ; State := GetDefault ( State ) 
        END (* IF *) 
      END (* LOOP *) 

   (* INV EndOfInput OR Table [State, Ch] = DNoState *) 

    ; LOOP                                      (* extend the path *) 
        IF EndOfInput THEN EXIT END (* IF *) 
      ; NewState := RecordedTrace ( ChIndex , DNoState ) 
      ; IF NewState = DNoState 
        THEN 
          NewState := MakeDState ( ) 
        ; PutDefault ( NewState , EobDefaultState ) 
        ; RecordTrace ( ChIndex , DNoState , NewState ) 
        END (* IF *) 
      ; PutTable ( PrevState , Ch , NewState ) 
      ; GetStartSet ( NewState , StartSet ) 
      ; Include ( StartSet , StartState ) 
      ; PutStartSet ( NewState , StartSet ) 
      ; PrevState := NewState 
      ; Ch := GetCh ( ) 
      END (* LOOP *) 

   (* INV EndOfInput *) 

    ; GetDSemantics ( PrevState , dSemantics )  (* process final state *) 
    ; Include ( dSemantics , PatternNr ) 
    ; PutDSemantics ( PrevState , dSemantics ) 
    END AddConstantRE 

; PROCEDURE UpdateContext ( ) 

  = VAR Max : DStateRange 

  ; BEGIN (* UpdateContext *) 
      IF DStateCount > NodeCount 
      THEN 
        WriteT ( StdError , "internal Error: StateCount > NodeCount" ) 
      ; WriteNl ( StdError ) 
      END (* IF *) 

    ; FOR Pattern := 0 TO PatternCount - 2 
      DO IF PatternTablePtr ^ [ Pattern ] . ContextLng = VariableContext 
         THEN 
           Max := Maximum ( PatternTablePtr ^ [ Pattern ] . DContext ) 
         ; FOR State1 := 1 TO Max 
           DO IF IsElement 
                   ( State1 , PatternTablePtr ^ [ Pattern ] . DContext ) 
              THEN 
                FOR State2 := 1 TO DStateCount 
                DO IF State1 = GetDefault ( State2 ) 
                   THEN 
                     Include 
                       ( PatternTablePtr ^ [ Pattern ] . DContext , State2 ) 
                   END (* IF *) 
                END (* FOR *) 
              END (* IF *) 
           END (* FOR *) 
         END (* IF *) 
      END (* FOR *) 
    END UpdateContext 

; PROCEDURE InvertMapping ( ) 

  = VAR Pattern : SHORTCARD 

  ; BEGIN (* InvertMapping *) 
      FOR Pattern := 0 TO PatternCount 
      DO MakeSet ( PatternTablePtr ^ [ Pattern ] . Finals , DStateCount ) 
      END (* FOR *) 

    ; FOR State := 1 TO DStateCount 
      DO GetDSemantics ( State , dSemantics ) 
      ; IF IsEmpty ( dSemantics ) 
        THEN 
          Include ( PatternTablePtr ^ [ 0 ] . Finals , State ) 
        ELSE 
          Pattern := Minimum ( dSemantics ) 
        ; Include ( PatternTablePtr ^ [ Pattern ] . Finals , State ) 
        END (* IF *) 
      END (* FOR *) 
    ; IsComputedFinals := TRUE 
    END InvertMapping 

; PROCEDURE CheckTables ( )        (* check automaton for completeness *) 

  = VAR Ident : Idents . tIdent 
    ; StartState : SHORTCARD 

  ; BEGIN (* CheckTables *) 
      FOR Definition := 1 TO DefCount 
      DO                                        (* FORALL StartStates *) 
         IF GetKind ( Definition ) = tKind . Start 
         THEN 
           GetStartDef ( Definition , Ident , StartState ) 
         ; CheckStartState ( StartState , Ident , FALSE ) 
         ; IF LeftJustUsed 
           THEN 
             CheckStartState ( StartState + 1 , Ident , TRUE ) 
           END (* IF *) 
         END (* IF *) 
      END (* FOR *) 
    END CheckTables 

; PROCEDURE CheckStartState 
    ( StartState : SHORTCARD ; Ident : Idents . tIdent ; LeftJust : BOOLEAN ) 

  = VAR Ch : CHAR 
    ; DState : DStateRange 
    ; Undefined , Semantics : tSet 
    ; String : tString 
    ; Count : INTEGER 

  ; BEGIN (* CheckStartState *) 
      MakeSet ( Undefined , ORD ( OldLastCh ) ) 
    ; MakeSet ( Semantics , PatternCount ) 
    ; Union ( Undefined , Unused ) 

    ; FOR Ch := FirstCh TO LastCh 
      DO DState := GetTable ( StartState , Ch ) 
      ; IF DState = DNoState 
        THEN 
          IF Ch <= ClassCount 
          THEN 
            Union ( Undefined , ClassMemPtr ^ [ Ch ] ) 
          ELSE 
            Include ( Undefined , ORD ( ToChar [ Ch ] ) ) 
          END (* IF *) 
        ELSE 
          GetDSemantics ( DState , Semantics ) 
        ; IF IsEmpty ( Semantics ) 
          THEN 
            IF Ch <= ClassCount 
            THEN 
              Union ( Undefined , ClassMemPtr ^ [ Ch ] ) 
            ELSE 
              Include ( Undefined , ORD ( ToChar [ Ch ] ) ) 
            END (* IF *) 
          END (* IF *) 
        END (* IF *) 
      END (* FOR *) 

    ; IF NOT IsEmpty ( Undefined ) 
      THEN 
        WriteT ( StdError , "Warning: in start state " ) 
      ; Idents . GetString ( Ident , String ) 
      ; Strings . WriteS ( StdError , String ) 
      ; IF LeftJust 
        THEN 
          WriteT 
            ( StdError 
            , " the default action may be triggered by (left justified):" 
            ) 
        ELSE 
          WriteT ( StdError , " the default action may be triggered by:" ) 
        END (* IF *) 
      ; WriteNl ( StdError ) 

      ; Count := 0 
      ; WHILE NOT IsEmpty ( Undefined ) 
        DO Ch := VAL ( Extract ( Undefined ) , CHAR ) 
        ; WriteC ( StdError , ' ' ) 
        ; IF ( '!' <= Ch ) AND ( Ch <= '~' ) 
          THEN 
            WriteC ( StdError , '\'' ) 
          ; WriteC ( StdError , Ch ) 
          ; WriteC ( StdError , '\'' ) 
          ELSE 
            WriteC ( StdError , '\'' ) 
          ; WriteI ( StdError , ORD ( Ch ) , 0 ) 
          END (* IF *) 
        ; INC ( Count ) 
        ; IF Count = 16 THEN WriteNl ( StdError ) ; Count := 0 END (* IF *) 
        END (* WHILE *) 
      ; WriteNl ( StdError ) 
      END (* IF *) 

    ; ReleaseSet ( Semantics ) 
    ; ReleaseSet ( Undefined ) 
    END CheckStartState 

; PROCEDURE WritePattern ( ) 

  = BEGIN (* WritePattern *) 
      FOR Pattern := 0 TO PatternCount - 2 
      DO IF PatternTablePtr ^ [ Pattern ] . ContextLng # NoContext 
         THEN 
           WriteT ( StdOutput , "Pattern, ContextLng" ) 
         ; WriteI ( StdOutput , Pattern , 5 ) 
         ; WriteI 
             ( StdOutput , PatternTablePtr ^ [ Pattern ] . ContextLng , 5 ) 
         ; IF PatternTablePtr ^ [ Pattern ] . ContextLng = VariableContext 
           THEN 
             IF IsComputedNContext 
             THEN 
               WriteT ( StdOutput , " NContext " ) 
             ; WriteSet 
                 ( StdOutput , PatternTablePtr ^ [ Pattern ] . NContext ) 
             END (* IF *) 
           ; IF IsComputedDContext 
             THEN 
               WriteT ( StdOutput , " DContext " ) 
             ; WriteSet 
                 ( StdOutput , PatternTablePtr ^ [ Pattern ] . DContext ) 
             END (* IF *) 
           END (* IF *) 
         ; IF IsComputedFinals 
           THEN 
             WriteT ( StdOutput , " Finals " ) 
           ; WriteSet ( StdOutput , PatternTablePtr ^ [ Pattern ] . Finals ) 
           END (* IF *) 
         ; WriteNl ( StdOutput ) 
         END (* IF *) 
      END (* FOR *) 
    END WritePattern 

; PROCEDURE WriteStatistics ( ) 

  = BEGIN (* WriteStatistics *) 
      WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Start States  " ) 
    ; WriteI ( StdOutput , StartStateCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Definitions   " ) 
    ; WriteI ( StdOutput , DefCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Rules         " ) 
    ; WriteI ( StdOutput , RuleCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Patterns      " ) 
    ; WriteI ( StdOutput , PatternCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Classes               " ) 
    ; WriteI ( StdOutput , ORD ( ClassCount ) , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "LastCh                " ) 
    ; WriteI ( StdOutput , ORD ( LastCh ) , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Transitions   " ) 
    ; WriteI ( StdOutput , TransitionCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Leafs         " ) 
    ; WriteI ( StdOutput , LeafCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "NFA States    " ) 
    ; WriteI ( StdOutput , NStateCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Minimize Savings" ) 
    ; WriteI ( StdOutput , MinimizeSavings , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Ambiguous States" ) 
    ; WriteI ( StdOutput , MaxAmbiguousState , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Nodes         " ) 
    ; WriteI ( StdOutput , NodeCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "DFA States    " ) 
    ; WriteI ( StdOutput , DStateCount , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Sentinel Savings" ) 
    ; WriteI ( StdOutput , SentinelSavings , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Default Savings       " ) 
    ; WriteI ( StdOutput , DefaultSavings , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Table Entries " ) 
    ; WriteI ( StdOutput , TableEntries , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Table Size    " ) 
    ; WriteI ( StdOutput , TableSize , 6 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteT ( StdOutput , "Memory used   " ) 
    ; WriteI ( StdOutput , MemoryUsed , 6 ) 
    ; WriteNl ( StdOutput ) 
    END WriteStatistics 

; PROCEDURE GenerateTables 
    ( DebugLevel : SHORTCARD 
    ; ReduceCaseSize , Warnings : BOOLEAN 
    ; Optimize : SHORTINT 
    ) 

  = VAR i : SHORTINT 

  ; BEGIN (* GenerateTables *) 
      IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "Start           " ) 
      END (* IF *) 
    ; IsComputedNContext := FALSE 
    ; IsComputedDContext := FALSE 
    ; IsComputedFinals := FALSE 
    ; INC ( RuleCount ) 
    ; INC ( PatternCount ) 
    ; EobAction := PatternCount 
    ; INC ( RuleCount ) 
    ; INC ( PatternCount ) 
    ; DefaultAction := PatternCount 
    ; RuleToCodeSize := RuleCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( RuleToCodePtr , ADDRESS ) 
        , RuleToCodeSize 
        , BYTESIZE ( CodeInfo ) 
        ) 
    ; PatternTableSize := PatternCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( PatternTablePtr , ADDRESS ) 
        , PatternTableSize 
        , BYTESIZE ( PatternInfo ) 
        ) 
    ; PatternTablePtr ^ [ 0 ] . ContextLng := NoContext 

    ; MakeSet ( dSemantics , PatternCount ) 
    ; ComputeNfa ( ) 
    ; IF DebugLevel >= 15 THEN WriteNfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "ComputeNfa      " ) 
      END (* IF *) 
    ; ComputeDfa ( ) 
    ; IF DebugLevel >= 14 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "ComputeDfa      " ) 
      END (* IF *) 
    ; MinimizeDfa ( ) 
    ; IF DebugLevel >= 13 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "MinimizeDfa     " ) 
      END (* IF *) 

    ; EobDefaultState := MakeDState ( )         (* has to be ambiguous *) 
    ; ComputeSuccGraph ( ) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "ComputeSuccGraph" ) 
      END (* IF *) 
    ; ComputeAmbiguousStates ( ) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "ComputeAmbiguous" ) 
      END (* IF *) 
    ; ComputeCyclicStates ( ) 
    ; IF DebugLevel >= 12 
      THEN 
        WriteSet ( StdOutput , AmbiguousStates ) 
      ; WriteNl ( StdOutput ) 
      ; WriteSet ( StdOutput , CyclicStates ) 
      ; WriteNl ( StdOutput ) 
      END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "ComputeCyclicSta" ) 
      END (* IF *) 

    ; ComputeStartSets ( ) 
    ; IF DebugLevel >= 11 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "ComputeStartSets" ) 
      END (* IF *) 

    ; EobState := MakeDState ( ) 
    ; AssignElmt ( dSemantics , EobAction ) 
    ; PutDSemantics ( EobState , dSemantics ) 
    ; AssignElmt ( dSemantics , DefaultAction )         (* default state *) 
    ; PutDSemantics ( MakeDState ( ) , dSemantics ) 

    ; AddConstantREs ( ) 
    ; IF DebugLevel >= 10 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "AddConstantREs  " ) 
      END (* IF *) 
    ; UpdateContext ( ) 
    ; IF DebugLevel >= 9 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "UpdateContext   " ) 
      END (* IF *) 
    ; SaveEobTransitions ( ) 
    ; IF DebugLevel >= 8 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "SaveEobTransitio" ) 
      END (* IF *) 
    ; SaveSentinels ( ) 
    ; IF DebugLevel >= 7 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "SaveSentinels   " ) 
      END (* IF *) 
    ; IF Optimize > 0 
      THEN 
        i := 1 
      ; WHILE i <= MaxAmbiguousState 
        DO ComputeDefaults ( i , Min ( MaxAmbiguousState , i + Optimize - 1 ) ) 
        ; IF DebugLevel >= 2 
          THEN 
            WriteStepTime ( "ComputeDefaults " ) 
          END (* IF *) 
        ; INC ( i , Optimize ) 
        END (* WHILE *) 
      END (* IF *) 
    ; IF DebugLevel >= 6 THEN WriteDfa ( ) ; WritePattern ( ) END (* IF *) 
    ; InvertMapping ( ) 
    ; IF DebugLevel >= 5 THEN WritePattern ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "InvertMapping   " ) 
      END (* IF *) 
    ; MakeTables ( ReduceCaseSize ) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "MakeTables      " ) 
      END (* IF *) 
    ; CompressTables ( Optimize ) 
    ; IF DebugLevel >= 4 THEN WriteTables ( ) END (* IF *) 
    ; IF DebugLevel >= 2 
      THEN 
        WriteStepTime ( "CompressTables  " ) 
      END (* IF *) 
    ; IF Language = tLanguage . Modula 
      THEN 
        PutTables ( ReduceCaseSize ) 
      ; IF DebugLevel >= 2 
        THEN 
          WriteStepTime ( "PutTables       " ) 
        END (* IF *) 
      END (* IF *) 
    ; IF DebugLevel >= 3 THEN QueryTables ( ) END (* IF *) 
    ; IF Warnings 
      THEN 
        CheckTables ( ) 
      ; IF DebugLevel >= 2 
        THEN 
          WriteStepTime ( "CheckTables     " ) 
        END (* IF *) 
      END (* IF *) 
    ; IF DebugLevel >= 1 THEN WriteStatistics ( ) END (* IF *) 
    END GenerateTables 

; BEGIN (* GenTabs *) 
  END GenTabs 
. 

