(* $Id: Dfa.mi,v 3.1 1991/11/21 14:41:19 grosch rel $ *) 

(* $Log: Dfa.mi,v $ 
 * Revision 3.1  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.0  91/04/04  18:06:48  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 1.4  91/03/26  18:26:41  grosch 
 * improved generation time 
 * introduced options n and o to control table size and generation time 
 * increased limitation for table size from 64K to 256K 
 * 
 * Revision 1.3  90/06/11  11:27:24  grosch 
 * extended character range to 8 bits, ChRange -> CHAR 
 * 
 * Revision 1.2  89/11/06  12:36:12  grosch 
 * renamed module Rex to GenTabs to avoid name clash with rex under VMS 
 * 
 * Revision 1.1  89/02/23  15:55:10  grosch 
 * corrected confusion between RuleCount and PatternCount 
 * improved notion of compatibility in Minimize 
 * 
 * Revision 1.0  88/10/04  11:59:32  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE MODULE Dfa 


; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT SHORTCARD , SHORTINT 

; FROM General IMPORT Max 

; FROM DynArray IMPORT MakeArray , ExtendArray , ReleaseArray 

; FROM Sets 
  IMPORT tSet , MakeSet , WriteSet , Intersection , Complement , IsEmpty 
  , Extract 
  , Exclude , IsElement , Include , Card , IsStrictSubset , Assign 
  , AssignEmpty , Minimum , IsSubset , Union , ReleaseSet , Maximum 
  , AssignElmt 
  , Select 

; FROM ReuseIO IMPORT StdOutput , WriteT , WriteNl , WriteC , WriteI 

; FROM Layout IMPORT WriteChar , WriteSpace 

; FROM GenTabs 
  IMPORT PatternCount , StartStateCount , PatternTablePtr , VariableContext 

; FROM Classes IMPORT ToClass 

; CONST InitialTableSize = 256 

; TYPE RowType = UNTRACED BRANDED REF ARRAY CHAR OF DStateRange 
  ; DStateInfo 
    = RECORD 
        Row : RowType
      ; RowSize : M2LONGINT 
      ; Semantics : tSet 
      ; Default : DStateRange 
      ; StartSet : tSet 
      ; EobTrans : DStateRange 
      ; FirstElmt : CHAR 
      ; LastElmt : CHAR 
      END (* RECORD *) 
  ; DStateTable = ARRAY [ 0 .. 100000 ] OF DStateInfo 
  ; SuccSet = ARRAY [ 0 .. 100000 ] OF tSet 

; VAR TablePtr : UNTRACED BRANDED REF DStateTable 
  ; TableSize : M2LONGINT 
  ; SuccSetPtr : UNTRACED BRANDED REF SuccSet 
  ; SuccSetSize : M2LONGINT 

; PROCEDURE MakeDState ( ) : DStateRange 

  = BEGIN (* MakeDState *) 
      INC ( DStateCount ) 
    ; IF LOOPHOLE ( DStateCount , SHORTINT ) = TableSize 
      THEN 
        ExtendArray 
          ( LOOPHOLE ( TablePtr , ADDRESS ) 
          , TableSize 
          , BYTESIZE ( DStateInfo ) 
          ) 
      END (* IF *) 
    ; WITH With_5 = TablePtr ^ [ DStateCount ] 
      DO With_5 . RowSize := ORD ( LastCh ) + 1 
      ; MakeArray 
          ( (*OUT*) LOOPHOLE ( With_5 . Row , ADDRESS ) 
          , (*INOUT*) With_5 . RowSize 
          , BYTESIZE ( DStateRange ) 
          )
      ; FOR Ch := '\000' TO LastCh 
        DO With_5 . Row ^ [ Ch ] := DNoState 
        END (* FOR *) 
      ; MakeSet ( With_5 . Semantics , PatternCount ) 
      ; With_5 . Default := DNoState 
      ; MakeSet ( With_5 . StartSet , StartStateCount ) 
      ; With_5 . EobTrans := DNoState 
      ; With_5 . FirstElmt := LastCh 
      ; With_5 . LastElmt := FirstCh 
      END (* WITH *) 
    ; RETURN DStateCount 
    END MakeDState 

; PROCEDURE ReleaseDState ( State : DStateRange ) 

  = BEGIN (* ReleaseDState *) 
      DEC ( DStateCount ) 
    ; WITH With_5a = TablePtr ^ [ State ]  
      DO ReleaseArray 
           ( With_5a . Row , With_5a . RowSize , BYTESIZE ( DStateRange ) ) 
      ; ReleaseSet ( With_5a . Semantics ) 
      ; ReleaseSet ( With_5a . StartSet )
      END (* WITH *)
    END ReleaseDState 

; PROCEDURE GetEobTrans ( State : DStateRange ) : DStateRange

  = BEGIN (* GetEobTrans *) 
      RETURN TablePtr ^ [ State ] . EobTrans 
    END GetEobTrans 

; PROCEDURE GetDefault ( State : DStateRange ) : DStateRange 

  = BEGIN (* GetDefault *) 
      RETURN TablePtr ^ [ State ] . Default 
    END GetDefault 

; PROCEDURE PutDefault ( State , DefaultState : DStateRange ) 

  = BEGIN (* PutDefault *) 
      TablePtr ^ [ State ] . Default := DefaultState 
    END PutDefault 

; PROCEDURE GetDSemantics ( State : DStateRange ; VAR Semantics : tSet ) 

  = BEGIN (* GetDSemantics *) 
      Assign ( Semantics , TablePtr ^ [ State ] . Semantics ) 
    END GetDSemantics 

; PROCEDURE PutDSemantics ( State : DStateRange ; Semantics : tSet ) 

  = BEGIN (* PutDSemantics *) 
      Assign ( TablePtr ^ [ State ] . Semantics , Semantics ) 
    END PutDSemantics 

; PROCEDURE GetStartSet ( State : DStateRange ; VAR StartSet : tSet ) 

  = BEGIN (* GetStartSet *) 
      Assign ( StartSet , TablePtr ^ [ State ] . StartSet ) 
    END GetStartSet 

; PROCEDURE PutStartSet ( State : DStateRange ; StartSet : tSet ) 

  = BEGIN (* PutStartSet *) 
      Assign ( TablePtr ^ [ State ] . StartSet , StartSet ) 
    END PutStartSet 

; PROCEDURE GetTable ( State : DStateRange ; Ch : CHAR ) : DStateRange 

  = VAR NextState : DStateRange 

  ; BEGIN (* GetTable *) 
      REPEAT 
        NextState := TablePtr ^ [ State ] . Row ^ [ Ch ] 
      ; IF NextState # DNoState THEN RETURN NextState END (* IF *) 
      ; State := TablePtr ^ [ State ] . Default 
      UNTIL State = DNoState 
    ; RETURN DNoState 
    END GetTable 

; PROCEDURE PutTable 
    ( State : DStateRange ; Ch : CHAR ; NextState : DStateRange ) 

  = BEGIN (* PutTable *) 
      WITH With_6 = TablePtr ^ [ State ] 
      DO With_6 . Row ^ [ Ch ] := NextState 
      ; IF NextState # DNoState 
        THEN                                            (* Include *) 
          IF Ch < With_6 . FirstElmt 
          THEN 
            With_6 . FirstElmt := Ch 
          END (* IF *) 
        ; IF Ch > With_6 . LastElmt THEN With_6 . LastElmt := Ch END (* IF *) 
        ELSE                                            (* Exclude *) 
          IF ( Ch = With_6 . FirstElmt ) AND ( Ch < LastCh ) 
          THEN 
            INC ( With_6 . FirstElmt ) 
          END (* IF *) 
        ; IF ( Ch = With_6 . LastElmt ) AND ( Ch > FirstCh ) 
          THEN 
            DEC ( With_6 . LastElmt ) 
          END (* IF *) 
(* 
          ; IF Ch = FirstElmt THEN 
               WHILE (FirstElmt < LastElmt) AND (Row^[FirstElmt] = DNoState) DO 
                  INC (FirstElmt) 
               END 
            END 
          ; IF Ch = LastElmt THEN 
               WHILE (LastElmt > FirstElmt) AND (Row^[LastElmt] = DNoState) DO 
                  DEC (LastElmt) 
               END 
            END 
*) 
        END (* IF *) 
      END (* WITH *) 
    END PutTable 

; PROCEDURE GetTableNoDef ( State : DStateRange ; Ch : CHAR ) : DStateRange 

  = BEGIN (* GetTableNoDef *) 
      RETURN TablePtr ^ [ State ] . Row ^ [ Ch ] 
    END GetTableNoDef 

; PROCEDURE GetFirst ( State : DStateRange ) : CHAR 

  = BEGIN (* GetFirst *) 
      RETURN TablePtr ^ [ State ] . FirstElmt 
    END GetFirst 

; PROCEDURE GetLast ( State : DStateRange ) : CHAR 

  = BEGIN (* GetLast *) 
      RETURN TablePtr ^ [ State ] . LastElmt 
    END GetLast 

; PROCEDURE WriteDfa ( ) 

  = VAR Count : INTEGER 

  ; BEGIN (* WriteDfa *) 
      WriteT ( StdOutput , "DFA :" ) 
    ; WriteNl ( StdOutput ) 
    ; WriteNl ( StdOutput ) 
    ; FOR State := 1 TO DStateCount 
      DO WriteT 
           ( StdOutput , "State, Default, EobTrans, Semantics, StartSet =" ) 
      ; WriteI ( StdOutput , State , 5 ) 
      ; WriteI ( StdOutput , TablePtr ^ [ State ] . Default , 5 ) 
      ; WriteI ( StdOutput , TablePtr ^ [ State ] . EobTrans , 5 ) 
      ; WriteSpace ( StdOutput ) 
      ; WriteSet ( StdOutput , TablePtr ^ [ State ] . Semantics ) 
      ; WriteSpace ( StdOutput ) 
      ; WriteSet ( StdOutput , TablePtr ^ [ State ] . StartSet ) 
      ; WriteNl ( StdOutput ) 
      ; Count := 0 
      ; FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
        DO IF GetTableNoDef ( State , Ch ) # DNoState 
           THEN 
             IF Count = 10 
             THEN 
               WriteNl ( StdOutput ) 
             ; Count := 0 
             END (* IF *) 
           ; INC ( Count ) 
           ; WriteChar ( StdOutput , Ch ) 
           ; WriteSpace ( StdOutput ) 
           ; WriteI ( StdOutput , GetTable ( State , Ch ) , 1 ) 
           ; WriteC ( StdOutput , ',' ) 
           ; WriteSpace ( StdOutput ) 
           END (* IF *) 
        END (* FOR *) 
      ; WriteNl ( StdOutput ) 
      ; WriteNl ( StdOutput ) 
      END (* FOR *) 
    END WriteDfa 

; PROCEDURE MinimizeDfa ( ) 

  = TYPE BlockRange = DStateRange 
    ; DBElmt 
      = RECORD 
          Partition : DStateRange 
        ; Card : SHORTCARD 
        ; Semantics : tSet 
        ; Used : BOOLEAN 
        ; MapBlockToBlock : BlockRange 
        ; MapStateToBlock : BlockRange 
        ; NewMapStateToBlock : BlockRange 
        ; NextMember : DStateRange 
        ; Location : DStateRange 
        END (* RECORD *) 
    ; DB = ARRAY [ 0 .. 100000 ] OF DBElmt 

  ; VAR DBPtr : UNTRACED BRANDED REF DB 
    ; DBSize : M2LONGINT 
    ; BlockCount : BlockRange 
    ; OldBlockCount : BlockRange 
    ; Block : BlockRange 
    ; TargetBlock : BlockRange 
    ; TargetBlockCount : BlockRange 
    ; Gap : BlockRange 
    ; InitGap : BlockRange 
    ; NextGap : BlockRange 
    ; BlockSet : tSet 
    ; dSemantics : tSet 
    ; State : DStateRange 
    ; NextState : DStateRange 
    ; dStates : tSet 
    ; InitGapRow : RowType 

  ; 
   <*UNUSED*> 
    PROCEDURE WritePartition ( ) 

    = BEGIN (* WritePartition *) 
        FOR Block := 1 TO BlockCount 
        DO WriteI ( StdOutput , Block , 3 ) 
        ; WriteC ( StdOutput , ':' ) 
        ; State := DBPtr ^ [ Block ] . Partition 
        ; WHILE State # DNoState 
          DO WriteI ( StdOutput , State , 3 ) 
          ; State := DBPtr ^ [ State ] . NextMember 
          END (* WHILE *) 
        ; WriteNl ( StdOutput ) 
        END (* FOR *) 
      END WritePartition 

  ; BEGIN (* MinimizeDfa *) 
      DBSize := DStateCount + 2                 (* add room for InitGap *) 
    ; MakeArray ( LOOPHOLE ( DBPtr , ADDRESS ) , DBSize , BYTESIZE ( DBElmt ) ) 
    ; MakeSet ( dSemantics , PatternCount ) 
    ; MakeSet ( dStates , DStateCount ) 
    ; DBPtr ^ [ DNoState ] . MapStateToBlock := 0  (* initialize *) 

                        (* start state i -> block i of partition *) 
    ; FOR State := 1 TO StartStateCount 
      DO Block := State 
      ; DBPtr ^ [ Block ] . Partition := State 
      ; DBPtr ^ [ Block ] . Card := 1 
      ; DBPtr ^ [ State ] . NextMember := DNoState 
      ; DBPtr ^ [ State ] . MapStateToBlock := Block 
      END (* FOR *) 
    ; BlockCount := StartStateCount 
                                                (* non start states *) 
    ; FOR State := StartStateCount + 1 TO DStateCount 
      DO Block := StartStateCount + 1 
      ; LOOP            (* same semantics -> same block of partition *) 
          IF Block > BlockCount 
          THEN 
            INC ( BlockCount ) 
          ; Block := BlockCount 
          ; DBPtr ^ [ Block ] . Partition := DNoState 
          ; DBPtr ^ [ Block ] . Card := 0 
          ; MakeSet ( DBPtr ^ [ Block ] . Semantics , PatternCount ) 
          ; GetDSemantics ( State , DBPtr ^ [ Block ] . Semantics ) 
          ; EXIT 
          END (* IF *) 
        ; GetDSemantics ( State , dSemantics ) 
     (* ; IF IsEqual (dSemantics, DBPtr^[Block].Semantics) THEN EXIT END *)  
        ; IF ( IsEmpty ( dSemantics ) 
               AND IsEmpty ( DBPtr ^ [ Block ] . Semantics ) 
             ) 
             OR ( ( NOT IsEmpty ( dSemantics ) ) 
                  AND ( NOT IsEmpty ( DBPtr ^ [ Block ] . Semantics ) ) 
                  AND ( Minimum ( dSemantics ) 
                        = Minimum ( DBPtr ^ [ Block ] . Semantics ) 
                      ) 
                ) 
          THEN 
            EXIT 
          END (* IF *) 
        ; INC ( Block ) 
        END (* LOOP *) 
      ; DBPtr ^ [ State ] . NextMember := DBPtr ^ [ Block ] . Partition 
      ; DBPtr ^ [ Block ] . Partition := State 
      ; INC ( DBPtr ^ [ Block ] . Card ) 
      ; DBPtr ^ [ State ] . MapStateToBlock := Block 
      END (* FOR *) 

    ; FOR Block := StartStateCount + 1 TO BlockCount 
      DO ReleaseSet ( DBPtr ^ [ Block ] . Semantics ) 
      END (* FOR *) 

    ; REPEAT                                    (* minimize *) 
        OldBlockCount := BlockCount 
      ; Block := StartStateCount + 1 
      ; WHILE Block <= BlockCount 
        DO IF DBPtr ^ [ Block ] . Card > 1 
           THEN 
             FOR Ch := FirstCh TO LastCh 
             DO 

                TargetBlockCount := 0           (* check block *) 
             ; FOR i := 0 TO BlockCount 
               DO DBPtr ^ [ i ] . Used := FALSE 
               END (* FOR *) 
             ; State := DBPtr ^ [ Block ] . Partition 
             ; WHILE State # DNoState 
               DO TargetBlock 
                    := DBPtr ^ [ GetTableNoDef ( State , Ch ) ] . MapStateToBlock 
               ; IF NOT DBPtr ^ [ TargetBlock ] . Used 
                 THEN 
                   IF TargetBlockCount = 0 
                   THEN 
                     DBPtr ^ [ TargetBlock ] . MapBlockToBlock := Block 
                   ELSE 
                     INC ( BlockCount ) 
                   ; DBPtr ^ [ BlockCount ] . Partition := DNoState 
                   ; DBPtr ^ [ BlockCount ] . Card := 0 
                   ; DBPtr ^ [ TargetBlock ] . MapBlockToBlock := BlockCount 
                   END (* IF *) 
                 ; DBPtr ^ [ TargetBlock ] . Used := TRUE 
                 ; INC ( TargetBlockCount ) 
                 END (* IF *) 
               ; DBPtr ^ [ State ] . NewMapStateToBlock 
                   := DBPtr ^ [ TargetBlock ] . MapBlockToBlock 
               ; State := DBPtr ^ [ State ] . NextMember 
               END (* WHILE *) 

             ; IF TargetBlockCount > 1 
               THEN                             (* split block *) 
                 State := DBPtr ^ [ Block ] . Partition 
               ; DBPtr ^ [ Block ] . Partition := DNoState 
               ; DBPtr ^ [ Block ] . Card := 0 
               ; WHILE State # DNoState 
                 DO NextState := DBPtr ^ [ State ] . NextMember 
                 ; TargetBlock := DBPtr ^ [ State ] . NewMapStateToBlock 
                 ; DBPtr ^ [ State ] . NextMember 
                     := DBPtr ^ [ TargetBlock ] . Partition 
                 ; DBPtr ^ [ TargetBlock ] . Partition := State 
                 ; INC ( DBPtr ^ [ TargetBlock ] . Card ) 
                 ; DBPtr ^ [ State ] . MapStateToBlock := TargetBlock 
                 ; State := NextState 
                 END (* WHILE *) 
               END (* IF *) 
             END (* FOR *) 
           END (* IF *) 
        ; INC ( Block ) 
        END (* WHILE *) 
      UNTIL OldBlockCount = BlockCount 

    ; FOR Block := 1 TO BlockCount 
      DO                                        (* renumber table *) 
         State := DBPtr ^ [ Block ] . Partition 
      ; FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
        DO NextState := GetTableNoDef ( State , Ch ) 
        ; IF NextState # DNoState 
          THEN 
            PutTable ( State , Ch , DBPtr ^ [ NextState ] . MapStateToBlock ) 
          END (* IF *) 
        END (* FOR *) 
      END (* FOR *) 

    ; MakeSet ( BlockSet , BlockCount )         (* permute rows of table *) 
    ; Complement ( BlockSet ) 
    ; Exclude ( BlockSet , DNoState ) 
    ; FOR State := 1 TO DStateCount 
      DO DBPtr ^ [ State ] . Location := State 
      END (* FOR *) 
    ; InitGap := MakeDState ( ) 
    ; InitGapRow := TablePtr ^ [ InitGap ] . Row 

    ; WHILE NOT IsEmpty ( BlockSet ) 
      DO Block := Extract ( BlockSet ) 
      ; IF Block # DBPtr ^ [ Block ] . Partition 
        THEN 
          TablePtr ^ [ InitGap ] . Row := TablePtr ^ [ Block ] . Row 
        ; TablePtr ^ [ InitGap ] . FirstElmt 
            := TablePtr ^ [ Block ] . FirstElmt 
        ; TablePtr ^ [ InitGap ] . LastElmt 
            := TablePtr ^ [ Block ] . LastElmt 
        ; GetDSemantics ( Block , dSemantics ) 
        ; PutDSemantics ( InitGap , dSemantics ) 
        ; DBPtr ^ [ Block ] . Location := InitGap 
        ; Gap := Block 
        ; REPEAT 
            NextGap := DBPtr ^ [ DBPtr ^ [ Gap ] . Partition ] . Location 
          ; TablePtr ^ [ Gap ] . Row := TablePtr ^ [ NextGap ] . Row 
          ; TablePtr ^ [ Gap ] . FirstElmt 
              := TablePtr ^ [ NextGap ] . FirstElmt 
          ; TablePtr ^ [ Gap ] . LastElmt 
              := TablePtr ^ [ NextGap ] . LastElmt 
          ; GetDSemantics ( NextGap , dSemantics ) 
          ; PutDSemantics ( Gap , dSemantics ) 
          ; Exclude ( BlockSet , Gap ) 
          ; Gap := NextGap 
          UNTIL Gap > BlockCount 
        ; InitGap := Gap 
        END (* IF *) 
      END (* WHILE *) 
    ; TablePtr ^ [ InitGap ] . Row := InitGapRow 

    ; FOR Pattern := 1 TO PatternCount - 2 
      DO                                        (* context *) 
         IF PatternTablePtr ^ [ Pattern ] . ContextLng = VariableContext 
         THEN 
           Assign ( dStates , PatternTablePtr ^ [ Pattern ] . DContext ) 
         ; AssignEmpty ( PatternTablePtr ^ [ Pattern ] . DContext ) 
         ; WHILE NOT IsEmpty ( dStates ) 
           DO State := DBPtr ^ [ Extract ( dStates ) ] . MapStateToBlock 
           ; Include ( PatternTablePtr ^ [ Pattern ] . DContext , State ) 
           END (* WHILE *) 
         END (* IF *) 
      END (* FOR *) 

    ; MinimizeSavings := DStateCount - BlockCount 
    ; ReleaseSet ( BlockSet ) 
    ; ReleaseSet ( dSemantics ) 
    ; ReleaseSet ( dStates ) 
    ; FOR State := DStateCount TO BlockCount + 1 BY - 1 
      DO ReleaseDState ( State ) 
      END (* FOR *) 
    ; ReleaseArray ( DBPtr , DBSize , BYTESIZE ( DBElmt ) ) 
    END MinimizeDfa 

; PROCEDURE ComputeSuccGraph ( ) 

  = VAR NextState : DStateRange 

  ; BEGIN (* ComputeSuccGraph *) 
      SuccSetSize := DStateCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( SuccSetPtr , ADDRESS ) , SuccSetSize , BYTESIZE ( tSet ) ) 
    ; FOR State := 1 TO DStateCount 
      DO MakeSet ( SuccSetPtr ^ [ State ] , DStateCount ) 
      ; FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
        DO NextState := GetTableNoDef ( State , Ch ) 
        ; IF NextState # DNoState 
          THEN 
            Include ( SuccSetPtr ^ [ State ] , NextState ) 
          END (* IF *) 
        END (* FOR *) 
      END (* FOR *) 
    END ComputeSuccGraph 

; PROCEDURE ComputeAmbiguousStates ( ) 

  = TYPE PredCount = ARRAY [ 0 .. 100000 ] OF SHORTCARD 

  ; VAR PredCountPtr : UNTRACED BRANDED REF PredCount 
    ; PredCountSize : M2LONGINT 
    ; PredCount2Ptr : UNTRACED BRANDED REF PredCount 
    ; PredCount2Size : M2LONGINT 
    ; State : DStateRange 
    ; Successor : DStateRange 
    ; UnambiguousStates : tSet 

  ; BEGIN (* ComputeAmbiguousStates *) 
      PredCountSize := DStateCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( PredCountPtr , ADDRESS ) 
        , PredCountSize 
        , BYTESIZE ( SHORTCARD ) 
        ) 
    ; PredCount2Size := DStateCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( PredCount2Ptr , ADDRESS ) 
        , PredCount2Size 
        , BYTESIZE ( SHORTCARD ) 
        ) 
    ; MaxAmbiguousState := DStateCount 
    ; MakeSet ( UnambiguousStates , MaxAmbiguousState ) 
    ; MakeSet ( AmbiguousStates , MaxAmbiguousState ) 

    ; FOR State := 0 TO DStateCount 
      DO                                                (* initialize *) 
         PredCountPtr ^ [ State ] := 0 
      END (* FOR *) 

    ; FOR State := 1 TO StartStateCount 
      DO                                                (* start states *) 
         FOR State2 := 0 TO DStateCount 
         DO PredCount2Ptr ^ [ State2 ] := 0 
         END (* FOR *) 
      ; FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
        DO Successor := GetTableNoDef ( State , Ch ) 
        ; IF Successor # DNoState 
          THEN 
            INC ( PredCount2Ptr ^ [ Successor ] ) 
          END (* IF *) 
        END (* FOR *) 
      ; FOR State2 := 0 TO DStateCount 
        DO PredCountPtr ^ [ State2 ] 
             := Max ( PredCountPtr ^ [ State2 ] , PredCount2Ptr ^ [ State2 ] ) 
        END (* FOR *) 
      END (* FOR *) 

    ; FOR State := StartStateCount + 1 TO DStateCount 
      DO (* other states *) 
         FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
         DO Successor := GetTableNoDef ( State , Ch ) 
         ; IF Successor # DNoState 
           THEN 
             INC ( PredCountPtr ^ [ Successor ] ) 
           END (* IF *) 
         END (* FOR *) 
      END (* FOR *) 

    ; FOR State := 1 TO StartStateCount 
      DO Include ( UnambiguousStates , State ) 
      END (* FOR *) 
    ; Complement ( AmbiguousStates ) 
    ; Exclude ( AmbiguousStates , DNoState ) 

    ; WHILE NOT IsEmpty ( UnambiguousStates ) 
      DO State := Extract ( UnambiguousStates ) 
      ; Exclude ( AmbiguousStates , State ) 
      ; FOR Successor := 1 TO DStateCount 
        DO IF IsElement ( Successor , SuccSetPtr ^ [ State ] ) 
           THEN 
             IF PredCountPtr ^ [ Successor ] = 1 
             THEN 
               Include ( UnambiguousStates , Successor ) 
             END (* IF *) 
           END (* IF *) 
        END (* FOR *) 
      END (* WHILE *) 

    ; ReleaseSet ( UnambiguousStates ) 
    ; ReleaseArray ( PredCountPtr , PredCountSize , BYTESIZE ( SHORTCARD ) ) 
    ; ReleaseArray ( PredCount2Ptr , PredCount2Size , BYTESIZE ( SHORTCARD ) ) 
    END ComputeAmbiguousStates 

; PROCEDURE ComputeCyclicStates ( ) 

  = TYPE Succ = ARRAY [ 0 .. 100000 ] OF tSet 

  ; VAR SuccPtr : UNTRACED BRANDED REF Succ 
    ; SuccSize : M2LONGINT 

  ; BEGIN (* ComputeCyclicStates *) 
      SuccSize := DStateCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( SuccPtr , ADDRESS ) , SuccSize , BYTESIZE ( tSet ) ) 
    ; FOR State := 1 TO DStateCount 
      DO MakeSet ( SuccPtr ^ [ State ] , DStateCount ) 
      ; Assign ( SuccPtr ^ [ State ] , SuccSetPtr ^ [ State ] ) 
      END (* FOR *) 

    ; FOR j := 1 TO DStateCount 
      DO                                        (* Warshall *) 
         FOR i := 1 TO DStateCount 
         DO IF IsElement ( j , SuccPtr ^ [ i ] ) 
            THEN 
              Union ( SuccPtr ^ [ i ] , SuccPtr ^ [ j ] ) 
            END (* IF *) 
         END (* FOR *) 
      END (* FOR *) 

    ; MakeSet ( CyclicStates , DStateCount ) 
    ; FOR State := 1 TO DStateCount 
      DO IF IsElement ( State , SuccPtr ^ [ State ] ) 
         THEN 
           Include ( CyclicStates , State ) 
         END (* IF *) 
      ; ReleaseSet ( SuccPtr ^ [ State ] ) 
      END (* FOR *) 
    ; ReleaseArray ( SuccPtr , SuccSize , BYTESIZE ( tSet ) ) 
    END ComputeCyclicStates 

; PROCEDURE ComputeStartSets ( ) 

  = VAR State1 : DStateRange 
    ; StartSet1 , StartSet2 , WorkingSet : tSet 

  ; BEGIN (* ComputeStartSets *) 
      MakeSet ( StartSet1 , StartStateCount ) 
    ; MakeSet ( StartSet2 , StartStateCount ) 
    ; MakeSet ( WorkingSet , DStateCount ) 

    ; FOR State1 := 1 TO StartStateCount 
      DO FOR State2 := 1 TO DStateCount 
         DO IF IsElement ( State2 , SuccSetPtr ^ [ State1 ] ) 
            THEN 
              GetStartSet ( State2 , StartSet2 ) 
            ; Include ( StartSet2 , State1 ) 
            ; PutStartSet ( State2 , StartSet2 ) 
            END (* IF *) 
         END (* FOR *) 
      ; Union ( WorkingSet , SuccSetPtr ^ [ State1 ] ) 
      END (* FOR *) 

    ; WHILE NOT IsEmpty ( WorkingSet ) 
      DO State1 := Extract ( WorkingSet ) 
      ; GetStartSet ( State1 , StartSet1 ) 
      ; FOR State2 := 1 TO DStateCount 
        DO IF IsElement ( State2 , SuccSetPtr ^ [ State1 ] ) 
           THEN 
             GetStartSet ( State2 , StartSet2 ) 
           ; IF NOT IsSubset ( StartSet1 , StartSet2 ) 
             THEN 
               Union ( StartSet2 , StartSet1 ) 
             ; PutStartSet ( State2 , StartSet2 ) 
             ; Include ( WorkingSet , State2 ) 
             END (* IF *) 
           END (* IF *) 
        END (* FOR *) 
      END (* WHILE *) 

    ; ReleaseSet ( StartSet1 ) 
    ; ReleaseSet ( StartSet2 ) 
    ; ReleaseSet ( WorkingSet ) 
    END ComputeStartSets 

; PROCEDURE SaveEobTransitions ( ) 

  = BEGIN (* SaveEobTransitions *) 
      FOR State := 1 TO DStateCount 
      DO TablePtr ^ [ State ] . EobTrans 
           := GetTable ( State , ToClass [ EobCh ] ) 
      END (* FOR *) 
    ; FOR State := 1 TO MaxAmbiguousState 
      DO PutTable ( State , ToClass [ EobCh ] , EobState ) 
      END (* FOR *) 
    ; FOR State := MaxAmbiguousState + 1 TO DStateCount 
      DO PutTable ( State , ToClass [ EobCh ] , DNoState ) 
      END (* FOR *) 
    END SaveEobTransitions 

; PROCEDURE ComputeDefaults ( From , To : DStateRange ) (* compute default states *) 

  = TYPE DBElmt 
      = RECORD 
          Domain : tSet 
        ; Defaults : tSet (* optimal defaults   *) 
        ; Users : tSet 
        ; Savings : SHORTCARD (* optimal savings    *) 
        ; DFN : SHORTCARD (* depth-first-number *) 
        ; DFNToState : SHORTCARD 
        END (* RECORD *) 
    ; DB = ARRAY [ 0 .. 100000 ] OF DBElmt 

  ; VAR DBPtr : UNTRACED BRANDED REF DB 
    ; DBSize : M2LONGINT 
    ; State , State1 , State2 , DefaultState : DStateRange 
    ; DefaultCard : SHORTCARD 
    ; Domain1 , Domain2 : tSet 
    ; Marked , WorkingSet : tSet 
    ; Cyclics , Current : tSet 
    ; Next , Successors : tSet 
    ; DFN : SHORTCARD (* depth-first-number *) 

  ; PROCEDURE DepthFirstTraversal ( State : DStateRange ) 

    = BEGIN (* DepthFirstTraversal *) 
        Exclude ( WorkingSet , State ) 
      ; Include ( Marked , State ) 
      ; FOR State2 := From TO To 
        DO IF IsElement ( State2 , DBPtr ^ [ State ] . Defaults ) 
              AND ( NOT IsElement ( State2 , Marked ) ) 
           THEN 
             DepthFirstTraversal ( State2 ) 
           END (* IF *) 
        END (* FOR *) 
      ; INC ( DFN ) 
      ; DBPtr ^ [ State ] . DFN := DFN 
      ; DBPtr ^ [ DFN ] . DFNToState := State 
      END DepthFirstTraversal 

  ; BEGIN (* ComputeDefaults *) 
      DBSize := To + 1 
    ; MakeArray ( LOOPHOLE ( DBPtr , ADDRESS ) , DBSize , BYTESIZE ( DBElmt ) ) 
    ; MakeSet ( Domain1 , ORD ( LastCh ) ) 
    ; MakeSet ( Domain2 , ORD ( LastCh ) ) 
    ; MakeSet ( Marked , To ) 
    ; MakeSet ( WorkingSet , To ) 
    ; MakeSet ( Cyclics , To ) 
    ; MakeSet ( Current , To ) 
    ; MakeSet ( Next , To ) 
    ; MakeSet ( Successors , To ) 
    ; DefaultSavings := 0 

    ; FOR State := From TO To 
      DO                                (* compute domain of all states *) 
         MakeSet ( DBPtr ^ [ State ] . Domain , ORD ( LastCh ) ) 
      ; FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
        DO IF GetTable ( State , Ch ) # DNoState 
           THEN 
             Include ( DBPtr ^ [ State ] . Domain , ORD ( Ch ) ) 
           END (* IF *) 
        END (* FOR *) 
      END (* FOR *) 

    ; FOR State1 := From TO To 
      DO                                (* compute default relation *) 
         MakeSet ( DBPtr ^ [ State1 ] . Defaults , To ) 
      ; MakeSet ( DBPtr ^ [ State1 ] . Users , To ) 
      ; DBPtr ^ [ State1 ] . Savings := 0 
      ; IF NOT IsEmpty ( DBPtr ^ [ State1 ] . Domain ) 
        THEN 
          Assign ( Domain1 , DBPtr ^ [ State1 ] . Domain ) 

        ; FOR State2 := From TO To 
          DO IF State1 # State2 
             THEN 
               Assign ( Domain2 , DBPtr ^ [ State2 ] . Domain ) 
             ; IF IsSubset ( Domain2 , Domain1 ) 
               THEN 
                  (* IF Card (Domain2) >= DBPtr^[State1].Savings THEN *) 
                 IF Card ( DBPtr ^ [ State2 ] . Domain ) 
                    >= DBPtr ^ [ State1 ] . Savings 
                 THEN 
                   FOR Ch := GetFirst ( State2 ) TO GetLast ( State2 ) 
                   DO State := GetTable ( State2 , Ch ) 
                   ; IF ( State # DNoState ) 
                        AND ( State # GetTable ( State1 , Ch ) ) 
                     THEN 
                       Exclude ( Domain2 , ORD ( Ch ) ) 
                     END (* IF *) 
                   END (* FOR *) 

                 ; DefaultCard := Card ( Domain2 ) 
                 ; IF DefaultCard > 0 
                   THEN 
                     IF DefaultCard = DBPtr ^ [ State1 ] . Savings 
                     THEN 
                       Include ( DBPtr ^ [ State1 ] . Defaults , State2 ) 
                     ELSIF DefaultCard > DBPtr ^ [ State1 ] . Savings 
                     THEN 
                       AssignElmt ( DBPtr ^ [ State1 ] . Defaults , State2 ) 
                     ; DBPtr ^ [ State1 ] . Savings := DefaultCard 
                     END (* IF *) 
                   END (* IF *) 
                 END (* IF *) 
               END (* IF *) 
             END (* IF *) 
          END (* FOR *) 
        END (* IF *) 
      END (* FOR *) 

    ; FOR State1 := From TO To 
      DO                                (* compute inverse relation *) 
         FOR State2 := From TO To 
         DO IF IsElement ( State2 , DBPtr ^ [ State1 ] . Defaults ) 
            THEN 
              Include ( DBPtr ^ [ State2 ] . Users , State1 ) 
            END (* IF *) 
         END (* FOR *) 
      END (* FOR *) 

    ; DFN := From - 1                   (* compute depth first numbers *) 
    ; Complement ( WorkingSet ) 
    ; FOR State := 0 TO From - 1 
      DO Exclude ( WorkingSet , State ) 
      END (* FOR *) 
    ; IF ( From <= EobDefaultState ) AND ( EobDefaultState <= To ) 
      THEN 
        DepthFirstTraversal ( EobDefaultState ) (* minimal DFN *) 
      END (* IF *) 
    ; WHILE NOT IsEmpty ( WorkingSet ) 
      DO DepthFirstTraversal ( Select ( WorkingSet ) ) 
      END (* WHILE *) 

    ; FOR State1 := From TO To 
      DO                                (* compute cyclic states in relation *) 
         State2 := State1 + 1 
      ; LOOP 
          IF State2 > To THEN EXIT END (* IF *) 
        ; IF IsElement ( State2 , DBPtr ^ [ State1 ] . Defaults ) 
             AND IsElement ( State1 , DBPtr ^ [ State2 ] . Defaults ) 
          THEN 
            Include ( Cyclics , State1 ) 
          ; Include ( Cyclics , State2 ) 
          ; EXIT 
          END (* IF *) 
        ; INC ( State2 ) 
        END (* LOOP *) 
      END (* FOR *) 

    ; AssignEmpty ( Marked )            (* compute default states *) 
    ; AssignEmpty ( WorkingSet ) 
    ; Complement ( WorkingSet ) 
    ; FOR State := 0 TO From - 1 
      DO Exclude ( WorkingSet , State ) 
      END (* FOR *) 

    ; WHILE NOT IsEmpty ( WorkingSet ) 
      DO                                        (* breadth first traversal *) 
         State := DBPtr ^ [ Select ( WorkingSet ) ] . DFNToState (* ASSERT Select = Min *) 
      ; Assign ( Current , DBPtr ^ [ State ] . Defaults ) (* compute cycle     *) 
      ; Intersection ( Current , Cyclics ) 
      ; Include ( Current , State ) 
      ; Assign ( Next , Current ) 
   (* ; Intersection (Next, CyclicStates) *) 
      ; FOR i := Minimum ( Next ) TO Maximum ( Next ) 
        DO IF NOT IsElement ( i , CyclicStates ) 
           THEN 
             Exclude ( Next , i ) 
           END (* IF *) 
        END (* FOR *) 
      ; IF ( From <= EobDefaultState ) 
           AND ( EobDefaultState <= To ) 
           AND IsElement ( EobDefaultState , Current ) 
        THEN 
          State := EobDefaultState              (* prefer eob def. state *) 
        ELSIF NOT IsEmpty ( Next ) 
        THEN 
          State := Select ( Next )              (* prefer cyclic state  *) 
        ELSE 
          State := Select ( Current )           (* prefer small state   *) 
        END (* IF *) 
      ; AssignElmt ( Current , State ) 
      ; Include ( Marked , State ) 

      ; WHILE NOT IsEmpty ( Current ) 
        DO AssignEmpty ( Next ) 
        ; WHILE NOT IsEmpty ( Current ) 
          DO State1 := Extract ( Current ) 
          ; Exclude ( WorkingSet , DBPtr ^ [ State1 ] . DFN ) 
          ; Assign ( Successors , DBPtr ^ [ State1 ] . Users ) 
          ; WHILE NOT IsEmpty ( Successors ) 
            DO State2 := Extract ( Successors ) 
            ; IF NOT IsElement ( State2 , Marked ) 
              THEN 
                PutDefault ( State2 , State1 ) 
              ; Include ( Next , State2 ) 
              ; Include ( Marked , State2 ) 
              END (* IF *) 
            END (* WHILE *) 
          END (* WHILE *) 
        ; Assign ( Current , Next ) 
        END (* WHILE *) 
      END (* WHILE *) 

    ; FOR State1 := From TO To 
      DO                                (* compute miss. default relation *) 
         IF GetDefault ( State1 ) = DNoState 
         THEN 
           DBPtr ^ [ State1 ] . Savings := 0 
         ; IF NOT IsEmpty ( DBPtr ^ [ State1 ] . Domain ) 
           THEN 
             Assign ( Domain1 , DBPtr ^ [ State1 ] . Domain ) 

           ; FOR State2 := From TO To 
             DO IF State1 # State2 
                THEN 
                  Assign ( Domain2 , DBPtr ^ [ State2 ] . Domain ) 
                ; IF IsStrictSubset ( Domain2 , Domain1 ) 
                  THEN 
                     (* IF Card (Domain2) >= DBPtr^[State1].Savings THEN *) 
                    IF Card ( DBPtr ^ [ State2 ] . Domain ) 
                       >= DBPtr ^ [ State1 ] . Savings 
                    THEN 
                      FOR Ch := GetFirst ( State2 ) TO GetLast ( State2 ) 
                      DO State := GetTable ( State2 , Ch ) 
                      ; IF ( State # DNoState ) 
                           AND ( State # GetTable ( State1 , Ch ) ) 
                        THEN 
                          Exclude ( Domain2 , ORD ( Ch ) ) 
                        END (* IF *) 
                      END (* FOR *) 

                    ; DefaultCard := Card ( Domain2 ) 
                    ; IF DefaultCard > 0 
                      THEN 
                        IF DefaultCard = DBPtr ^ [ State1 ] . Savings 
                        THEN 
                          Include ( Current , State2 ) 
                        ELSIF DefaultCard > DBPtr ^ [ State1 ] . Savings 
                        THEN 
                          AssignElmt ( Current , State2 ) 
                        ; DBPtr ^ [ State1 ] . Savings := DefaultCard 
                        END (* IF *) 
                      END (* IF *) 
                    END (* IF *) 
                  END (* IF *) 
                END (* IF *) 
             END (* FOR *) 

           ; IF DBPtr ^ [ State1 ] . Savings > 0 
             THEN 
               Assign ( Next , Current ) 
          (* ; Intersection (Next, CyclicStates) *) 
             ; FOR i := Minimum ( Next ) TO Maximum ( Next ) 
               DO IF NOT IsElement ( i , CyclicStates ) 
                  THEN 
                    Exclude ( Next , i ) 
                  END (* IF *) 
               END (* FOR *) 
             ; IF ( From <= EobDefaultState ) 
                  AND ( EobDefaultState <= To ) 
                  AND IsElement ( EobDefaultState , Current ) 
               THEN 
                 State := EobDefaultState       (* prefer eob def. state *) 
               ELSIF NOT IsEmpty ( Next ) 
               THEN 
                 State := Select ( Next )       (* prefer cyclic state  *) 
               ELSE 
                 State := Select ( Current ) (* prefer small state   *) 
               END (* IF *) 
             ; PutDefault ( State1 , State ) 
             END (* IF *) 
           END (* IF *) 
         END (* IF *) 
      END (* FOR *) 

    ; FOR State1 := From TO To 
      DO                                        (* adjust tables *) 
         DefaultState := GetDefault ( State1 ) 
      ; IF DefaultState # DNoState 
        THEN 
          FOR Ch := GetFirst ( State1 ) TO GetLast ( State1 ) 
          DO State := GetTable ( DefaultState , Ch ) 
          ; IF ( State # DNoState ) AND ( State = GetTable ( State1 , Ch ) ) 
            THEN 
              PutTable ( State1 , Ch , DNoState ) 
            END (* IF *) 
          END (* FOR *) 
        ; INC ( DefaultSavings , DBPtr ^ [ State1 ] . Savings ) 
        END (* IF *) 
      END (* FOR *) 

    ; FOR State := From TO To 
      DO                                        (* clean up *) 
         ReleaseSet ( DBPtr ^ [ State ] . Domain ) 
      ; ReleaseSet ( DBPtr ^ [ State ] . Defaults ) 
      ; ReleaseSet ( DBPtr ^ [ State ] . Users ) 
      END (* FOR *) 
    ; ReleaseSet ( Domain1 ) 
    ; ReleaseSet ( Domain2 ) 
    ; ReleaseSet ( Marked ) 
    ; ReleaseSet ( WorkingSet ) 
    ; ReleaseSet ( Cyclics ) 
    ; ReleaseSet ( Current ) 
    ; ReleaseSet ( Next ) 
    ; ReleaseSet ( Successors ) 
    ; ReleaseArray ( DBPtr , DBSize , BYTESIZE ( DBElmt ) ) 
    END ComputeDefaults 

; BEGIN (* Dfa *) 
    LastCh := '\177' 
  ; DStateCount := 0 
  ; TableSize := InitialTableSize 
  ; MakeArray 
      ( LOOPHOLE ( TablePtr , ADDRESS ) , TableSize , BYTESIZE ( DStateInfo ) ) 
  END Dfa 
. 

