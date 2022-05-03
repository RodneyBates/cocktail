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

; IMPORT Sets 
(*
; FROM Sets 
  IMPORT tSet , MakeSet , WriteSet , Intersection , Complement , IsEmpty 
  , Extract 
  , Exclude , IsElement , Include , Card , IsStrictSubset , Assign 
  , AssignEmpty , Minimum , IsSubset , Union , ReleaseSet , Maximum 
  , AssignElmt 
  , Select 
*)
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
      ; Semantics : Sets . tSet 
      ; Default : DStateRange 
      ; StartSet : Sets . tSet 
      ; EobTrans : DStateRange 
      ; FirstElmt : CHAR 
      ; LastElmt : CHAR 
      END (* RECORD *) 
  ; DStateTable = ARRAY [ 0 .. 100000 ] OF DStateInfo 
  ; SuccSet = ARRAY [ 0 .. 100000 ] OF Sets . tSet 

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
      ; Sets . MakeSet ( With_5 . Semantics , PatternCount ) 
      ; With_5 . Default := DNoState 
      ; Sets . MakeSet ( With_5 . StartSet , StartStateCount ) 
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
      ; Sets . ReleaseSet ( With_5a . Semantics ) 
      ; Sets . ReleaseSet ( With_5a . StartSet )
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

; PROCEDURE GetDSemantics ( State : DStateRange ; VAR Semantics : Sets . tSet ) 

  = BEGIN (* GetDSemantics *) 
      Sets . Assign ( Semantics , TablePtr ^ [ State ] . Semantics ) 
    END GetDSemantics 

; PROCEDURE PutDSemantics ( State : DStateRange ; Semantics : Sets . tSet ) 

  = BEGIN (* PutDSemantics *) 
      Sets . Assign ( TablePtr ^ [ State ] . Semantics , Semantics ) 
    END PutDSemantics 

; PROCEDURE GetStartSet ( State : DStateRange ; VAR StartSet : Sets . tSet ) 

  = BEGIN (* GetStartSet *) 
      Sets . Assign ( StartSet , TablePtr ^ [ State ] . StartSet ) 
    END GetStartSet 

; PROCEDURE PutStartSet ( State : DStateRange ; StartSet : Sets . tSet ) 

  = BEGIN (* PutStartSet *) 
      Sets . Assign ( TablePtr ^ [ State ] . StartSet , StartSet ) 
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
      ; Sets . WriteSet ( StdOutput , TablePtr ^ [ State ] . Semantics ) 
      ; WriteSpace ( StdOutput ) 
      ; Sets . WriteSet ( StdOutput , TablePtr ^ [ State ] . StartSet ) 
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
        ; Semantics : Sets . tSet 
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
    ; BlockSet : Sets . tSet 
    ; dSemantics : Sets . tSet 
    ; State : DStateRange 
    ; NextState : DStateRange 
    ; dStates : Sets . tSet 
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
    ; Sets . MakeSet ( dSemantics , PatternCount ) 
    ; Sets . MakeSet ( dStates , DStateCount ) 
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
          ; Sets . MakeSet ( DBPtr ^ [ Block ] . Semantics , PatternCount ) 
          ; GetDSemantics ( State , DBPtr ^ [ Block ] . Semantics ) 
          ; EXIT 
          END (* IF *) 
        ; GetDSemantics ( State , dSemantics ) 
     (* ; IF IsEqual (dSemantics, DBPtr^[Block].Semantics) THEN EXIT END *)  
        ; IF ( Sets . IsEmpty ( dSemantics ) 
               AND Sets . IsEmpty ( DBPtr ^ [ Block ] . Semantics ) 
             ) 
             OR ( ( NOT Sets . IsEmpty ( dSemantics ) ) 
                  AND ( NOT Sets . IsEmpty ( DBPtr ^ [ Block ] . Semantics ) ) 
                  AND ( Sets . Minimum ( dSemantics ) 
                        = Sets . Minimum ( DBPtr ^ [ Block ] . Semantics ) 
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
      DO Sets . ReleaseSet ( DBPtr ^ [ Block ] . Semantics ) 
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

    ; Sets . MakeSet ( BlockSet , BlockCount )         (* permute rows of table *) 
    ; Sets . Complement ( BlockSet ) 
    ; Sets . Exclude ( BlockSet , DNoState ) 
    ; FOR State := 1 TO DStateCount 
      DO DBPtr ^ [ State ] . Location := State 
      END (* FOR *) 
    ; InitGap := MakeDState ( ) 
    ; InitGapRow := TablePtr ^ [ InitGap ] . Row 

    ; WHILE NOT Sets . IsEmpty ( BlockSet ) 
      DO Block := Sets . Extract ( BlockSet ) 
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
          ; Sets . Exclude ( BlockSet , Gap ) 
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
           Sets . Assign ( dStates , PatternTablePtr ^ [ Pattern ] . DContext ) 
         ; Sets . AssignEmpty ( PatternTablePtr ^ [ Pattern ] . DContext ) 
         ; WHILE NOT Sets . IsEmpty ( dStates ) 
           DO State := DBPtr ^ [ Sets . Extract ( dStates ) ] . MapStateToBlock 
           ; Sets . Include ( PatternTablePtr ^ [ Pattern ] . DContext , State ) 
           END (* WHILE *) 
         END (* IF *) 
      END (* FOR *) 

    ; MinimizeSavings := DStateCount - BlockCount 
    ; Sets . ReleaseSet ( BlockSet ) 
    ; Sets . ReleaseSet ( dSemantics ) 
    ; Sets . ReleaseSet ( dStates ) 
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
        ( LOOPHOLE ( SuccSetPtr , ADDRESS ) , SuccSetSize , BYTESIZE ( Sets . tSet ) ) 
    ; FOR State := 1 TO DStateCount 
      DO Sets . MakeSet ( SuccSetPtr ^ [ State ] , DStateCount ) 
      ; FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
        DO NextState := GetTableNoDef ( State , Ch ) 
        ; IF NextState # DNoState 
          THEN 
            Sets . Include ( SuccSetPtr ^ [ State ] , NextState ) 
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
    ; UnambiguousStates : Sets . tSet 

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
    ; Sets . MakeSet ( UnambiguousStates , MaxAmbiguousState ) 
    ; Sets . MakeSet ( AmbiguousStates , MaxAmbiguousState ) 

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
      DO Sets . Include ( UnambiguousStates , State ) 
      END (* FOR *) 
    ; Sets . Complement ( AmbiguousStates ) 
    ; Sets . Exclude ( AmbiguousStates , DNoState ) 

    ; WHILE NOT Sets . IsEmpty ( UnambiguousStates ) 
      DO State := Sets . Extract ( UnambiguousStates ) 
      ; Sets . Exclude ( AmbiguousStates , State ) 
      ; FOR Successor := 1 TO DStateCount 
        DO IF Sets . IsElement ( Successor , SuccSetPtr ^ [ State ] ) 
           THEN 
             IF PredCountPtr ^ [ Successor ] = 1 
             THEN 
               Sets . Include ( UnambiguousStates , Successor ) 
             END (* IF *) 
           END (* IF *) 
        END (* FOR *) 
      END (* WHILE *) 

    ; Sets . ReleaseSet ( UnambiguousStates ) 
    ; ReleaseArray ( PredCountPtr , PredCountSize , BYTESIZE ( SHORTCARD ) ) 
    ; ReleaseArray ( PredCount2Ptr , PredCount2Size , BYTESIZE ( SHORTCARD ) ) 
    END ComputeAmbiguousStates 

; PROCEDURE ComputeCyclicStates ( ) 

  = TYPE Succ = ARRAY [ 0 .. 100000 ] OF Sets . tSet 

  ; VAR SuccPtr : UNTRACED BRANDED REF Succ 
    ; SuccSize : M2LONGINT 

  ; BEGIN (* ComputeCyclicStates *) 
      SuccSize := DStateCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( SuccPtr , ADDRESS ) , SuccSize , BYTESIZE ( Sets . tSet ) ) 
    ; FOR State := 1 TO DStateCount 
      DO Sets . MakeSet ( SuccPtr ^ [ State ] , DStateCount ) 
      ; Sets . Assign ( SuccPtr ^ [ State ] , SuccSetPtr ^ [ State ] ) 
      END (* FOR *) 

    ; FOR j := 1 TO DStateCount 
      DO                                        (* Warshall *) 
         FOR i := 1 TO DStateCount 
         DO IF Sets . IsElement ( j , SuccPtr ^ [ i ] ) 
            THEN 
              Sets . Union ( SuccPtr ^ [ i ] , SuccPtr ^ [ j ] ) 
            END (* IF *) 
         END (* FOR *) 
      END (* FOR *) 

    ; Sets . MakeSet ( CyclicStates , DStateCount ) 
    ; FOR State := 1 TO DStateCount 
      DO IF Sets . IsElement ( State , SuccPtr ^ [ State ] ) 
         THEN 
           Sets . Include ( CyclicStates , State ) 
         END (* IF *) 
      ; Sets . ReleaseSet ( SuccPtr ^ [ State ] ) 
      END (* FOR *) 
    ; ReleaseArray ( SuccPtr , SuccSize , BYTESIZE ( Sets . tSet ) ) 
    END ComputeCyclicStates 

; PROCEDURE ComputeStartSets ( ) 

  = VAR State1 : DStateRange 
    ; StartSet1 , StartSet2 , WorkingSet : Sets . tSet 

  ; BEGIN (* ComputeStartSets *) 
      Sets . MakeSet ( StartSet1 , StartStateCount ) 
    ; Sets . MakeSet ( StartSet2 , StartStateCount ) 
    ; Sets . MakeSet ( WorkingSet , DStateCount ) 

    ; FOR State1 := 1 TO StartStateCount 
      DO FOR State2 := 1 TO DStateCount 
         DO IF Sets . IsElement ( State2 , SuccSetPtr ^ [ State1 ] ) 
            THEN 
              GetStartSet ( State2 , StartSet2 ) 
            ; Sets . Include ( StartSet2 , State1 ) 
            ; PutStartSet ( State2 , StartSet2 ) 
            END (* IF *) 
         END (* FOR *) 
      ; Sets . Union ( WorkingSet , SuccSetPtr ^ [ State1 ] ) 
      END (* FOR *) 

    ; WHILE NOT Sets . IsEmpty ( WorkingSet ) 
      DO State1 := Sets . Extract ( WorkingSet ) 
      ; GetStartSet ( State1 , StartSet1 ) 
      ; FOR State2 := 1 TO DStateCount 
        DO IF Sets . IsElement ( State2 , SuccSetPtr ^ [ State1 ] ) 
           THEN 
             GetStartSet ( State2 , StartSet2 ) 
           ; IF NOT Sets . IsSubset ( StartSet1 , StartSet2 ) 
             THEN 
               Sets . Union ( StartSet2 , StartSet1 ) 
             ; PutStartSet ( State2 , StartSet2 ) 
             ; Sets . Include ( WorkingSet , State2 ) 
             END (* IF *) 
           END (* IF *) 
        END (* FOR *) 
      END (* WHILE *) 

    ; Sets . ReleaseSet ( StartSet1 ) 
    ; Sets . ReleaseSet ( StartSet2 ) 
    ; Sets . ReleaseSet ( WorkingSet ) 
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
          Domain : Sets . tSet 
        ; Defaults : Sets . tSet (* optimal defaults   *) 
        ; Users : Sets . tSet 
        ; Savings : SHORTCARD (* optimal savings    *) 
        ; DFN : SHORTCARD (* depth-first-number *) 
        ; DFNToState : SHORTCARD 
        END (* RECORD *) 
    ; DB = ARRAY [ 0 .. 100000 ] OF DBElmt 

  ; VAR DBPtr : UNTRACED BRANDED REF DB 
    ; DBSize : M2LONGINT 
    ; State , State1 , State2 , DefaultState : DStateRange 
    ; DefaultCard : SHORTCARD 
    ; Domain1 , Domain2 : Sets . tSet 
    ; Marked , WorkingSet : Sets . tSet 
    ; Cyclics , Current : Sets . tSet 
    ; Next , Successors : Sets . tSet 
    ; DFN : SHORTCARD (* depth-first-number *) 

  ; PROCEDURE DepthFirstTraversal ( State : DStateRange ) 

    = BEGIN (* DepthFirstTraversal *) 
        Sets . Exclude ( WorkingSet , State ) 
      ; Sets . Include ( Marked , State ) 
      ; FOR State2 := From TO To 
        DO IF Sets . IsElement ( State2 , DBPtr ^ [ State ] . Defaults ) 
              AND ( NOT Sets . IsElement ( State2 , Marked ) ) 
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
    ; Sets . MakeSet ( Domain1 , ORD ( LastCh ) ) 
    ; Sets . MakeSet ( Domain2 , ORD ( LastCh ) ) 
    ; Sets . MakeSet ( Marked , To ) 
    ; Sets . MakeSet ( WorkingSet , To ) 
    ; Sets . MakeSet ( Cyclics , To ) 
    ; Sets . MakeSet ( Current , To ) 
    ; Sets . MakeSet ( Next , To ) 
    ; Sets . MakeSet ( Successors , To ) 
    ; DefaultSavings := 0 

    ; FOR State := From TO To 
      DO                                (* compute domain of all states *) 
         Sets . MakeSet ( DBPtr ^ [ State ] . Domain , ORD ( LastCh ) ) 
      ; FOR Ch := GetFirst ( State ) TO GetLast ( State ) 
        DO IF GetTable ( State , Ch ) # DNoState 
           THEN 
             Sets . Include ( DBPtr ^ [ State ] . Domain , ORD ( Ch ) ) 
           END (* IF *) 
        END (* FOR *) 
      END (* FOR *) 

    ; FOR State1 := From TO To 
      DO                                (* compute default relation *) 
         Sets . MakeSet ( DBPtr ^ [ State1 ] . Defaults , To ) 
      ; Sets . MakeSet ( DBPtr ^ [ State1 ] . Users , To ) 
      ; DBPtr ^ [ State1 ] . Savings := 0 
      ; IF NOT Sets . IsEmpty ( DBPtr ^ [ State1 ] . Domain ) 
        THEN 
          Sets . Assign ( Domain1 , DBPtr ^ [ State1 ] . Domain ) 

        ; FOR State2 := From TO To 
          DO IF State1 # State2 
             THEN 
               Sets . Assign ( Domain2 , DBPtr ^ [ State2 ] . Domain ) 
             ; IF Sets . IsSubset ( Domain2 , Domain1 ) 
               THEN 
                  (* IF Sets . Card (Domain2) >= DBPtr^[State1].Savings THEN *) 
                 IF Sets . Card ( DBPtr ^ [ State2 ] . Domain ) 
                    >= DBPtr ^ [ State1 ] . Savings 
                 THEN 
                   FOR Ch := GetFirst ( State2 ) TO GetLast ( State2 ) 
                   DO State := GetTable ( State2 , Ch ) 
                   ; IF ( State # DNoState ) 
                        AND ( State # GetTable ( State1 , Ch ) ) 
                     THEN 
                       Sets . Exclude ( Domain2 , ORD ( Ch ) ) 
                     END (* IF *) 
                   END (* FOR *) 

                 ; DefaultCard := Sets . Card ( Domain2 ) 
                 ; IF DefaultCard > 0 
                   THEN 
                     IF DefaultCard = DBPtr ^ [ State1 ] . Savings 
                     THEN 
                       Sets . Include ( DBPtr ^ [ State1 ] . Defaults , State2 ) 
                     ELSIF DefaultCard > DBPtr ^ [ State1 ] . Savings 
                     THEN 
                       Sets . AssignElmt ( DBPtr ^ [ State1 ] . Defaults , State2 ) 
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
         DO IF Sets . IsElement ( State2 , DBPtr ^ [ State1 ] . Defaults ) 
            THEN 
              Sets . Include ( DBPtr ^ [ State2 ] . Users , State1 ) 
            END (* IF *) 
         END (* FOR *) 
      END (* FOR *) 

    ; DFN := From - 1                   (* compute depth first numbers *) 
    ; Sets . Complement ( WorkingSet ) 
    ; FOR State := 0 TO From - 1 
      DO Sets . Exclude ( WorkingSet , State ) 
      END (* FOR *) 
    ; IF ( From <= EobDefaultState ) AND ( EobDefaultState <= To ) 
      THEN 
        DepthFirstTraversal ( EobDefaultState ) (* minimal DFN *) 
      END (* IF *) 
    ; WHILE NOT Sets . IsEmpty ( WorkingSet ) 
      DO DepthFirstTraversal ( Sets . Select ( WorkingSet ) ) 
      END (* WHILE *) 

    ; FOR State1 := From TO To 
      DO                                (* compute cyclic states in relation *) 
         State2 := State1 + 1 
      ; LOOP 
          IF State2 > To THEN EXIT END (* IF *) 
        ; IF Sets . IsElement ( State2 , DBPtr ^ [ State1 ] . Defaults ) 
             AND Sets . IsElement ( State1 , DBPtr ^ [ State2 ] . Defaults ) 
          THEN 
            Sets . Include ( Cyclics , State1 ) 
          ; Sets . Include ( Cyclics , State2 ) 
          ; EXIT 
          END (* IF *) 
        ; INC ( State2 ) 
        END (* LOOP *) 
      END (* FOR *) 

    ; Sets . AssignEmpty ( Marked )            (* compute default states *) 
    ; Sets . AssignEmpty ( WorkingSet ) 
    ; Sets . Complement ( WorkingSet ) 
    ; FOR State := 0 TO From - 1 
      DO Sets . Exclude ( WorkingSet , State ) 
      END (* FOR *) 

    ; WHILE NOT Sets . IsEmpty ( WorkingSet ) 
      DO                                        (* breadth first traversal *) 
         State := DBPtr ^ [ Sets . Select ( WorkingSet ) ] . DFNToState (* ASSERT Select = Min *) 
      ; Sets . Assign ( Current , DBPtr ^ [ State ] . Defaults ) (* compute cycle     *) 
      ; Sets . Intersection ( Current , Cyclics ) 
      ; Sets . Include ( Current , State ) 
      ; Sets . Assign ( Next , Current ) 
   (* ; Sets . Intersection (Next, CyclicStates) *) 
      ; FOR i := Sets . Minimum ( Next ) TO Sets . Maximum ( Next ) 
        DO IF NOT Sets . IsElement ( i , CyclicStates ) 
           THEN 
             Sets . Exclude ( Next , i ) 
           END (* IF *) 
        END (* FOR *) 
      ; IF ( From <= EobDefaultState ) 
           AND ( EobDefaultState <= To ) 
           AND Sets . IsElement ( EobDefaultState , Current ) 
        THEN 
          State := EobDefaultState              (* prefer eob def. state *) 
        ELSIF NOT Sets . IsEmpty ( Next ) 
        THEN 
          State := Sets . Select ( Next )              (* prefer cyclic state  *) 
        ELSE 
          State := Sets . Select ( Current )           (* prefer small state   *) 
        END (* IF *) 
      ; Sets . AssignElmt ( Current , State ) 
      ; Sets . Include ( Marked , State ) 

      ; WHILE NOT Sets . IsEmpty ( Current ) 
        DO Sets . AssignEmpty ( Next ) 
        ; WHILE NOT Sets . IsEmpty ( Current ) 
          DO State1 := Sets . Extract ( Current ) 
          ; Sets . Exclude ( WorkingSet , DBPtr ^ [ State1 ] . DFN ) 
          ; Sets . Assign ( Successors , DBPtr ^ [ State1 ] . Users ) 
          ; WHILE NOT Sets . IsEmpty ( Successors ) 
            DO State2 := Sets . Extract ( Successors ) 
            ; IF NOT Sets . IsElement ( State2 , Marked ) 
              THEN 
                PutDefault ( State2 , State1 ) 
              ; Sets . Include ( Next , State2 ) 
              ; Sets . Include ( Marked , State2 ) 
              END (* IF *) 
            END (* WHILE *) 
          END (* WHILE *) 
        ; Sets . Assign ( Current , Next ) 
        END (* WHILE *) 
      END (* WHILE *) 

    ; FOR State1 := From TO To 
      DO                                (* compute miss. default relation *) 
         IF GetDefault ( State1 ) = DNoState 
         THEN 
           DBPtr ^ [ State1 ] . Savings := 0 
         ; IF NOT Sets . IsEmpty ( DBPtr ^ [ State1 ] . Domain ) 
           THEN 
             Sets . Assign ( Domain1 , DBPtr ^ [ State1 ] . Domain ) 

           ; FOR State2 := From TO To 
             DO IF State1 # State2 
                THEN 
                  Sets . Assign ( Domain2 , DBPtr ^ [ State2 ] . Domain ) 
                ; IF Sets . IsStrictSubset ( Domain2 , Domain1 ) 
                  THEN 
                     (* IF Sets . Card (Domain2) >= DBPtr^[State1].Savings THEN *) 
                    IF Sets . Card ( DBPtr ^ [ State2 ] . Domain ) 
                       >= DBPtr ^ [ State1 ] . Savings 
                    THEN 
                      FOR Ch := GetFirst ( State2 ) TO GetLast ( State2 ) 
                      DO State := GetTable ( State2 , Ch ) 
                      ; IF ( State # DNoState ) 
                           AND ( State # GetTable ( State1 , Ch ) ) 
                        THEN 
                          Sets . Exclude ( Domain2 , ORD ( Ch ) ) 
                        END (* IF *) 
                      END (* FOR *) 

                    ; DefaultCard := Sets . Card ( Domain2 ) 
                    ; IF DefaultCard > 0 
                      THEN 
                        IF DefaultCard = DBPtr ^ [ State1 ] . Savings 
                        THEN 
                          Sets . Include ( Current , State2 ) 
                        ELSIF DefaultCard > DBPtr ^ [ State1 ] . Savings 
                        THEN 
                          Sets . AssignElmt ( Current , State2 ) 
                        ; DBPtr ^ [ State1 ] . Savings := DefaultCard 
                        END (* IF *) 
                      END (* IF *) 
                    END (* IF *) 
                  END (* IF *) 
                END (* IF *) 
             END (* FOR *) 

           ; IF DBPtr ^ [ State1 ] . Savings > 0 
             THEN 
               Sets . Assign ( Next , Current ) 
          (* ; Sets . Intersection (Next, CyclicStates) *) 
             ; FOR i := Sets . Minimum ( Next ) TO Sets . Maximum ( Next ) 
               DO IF NOT Sets . IsElement ( i , CyclicStates ) 
                  THEN 
                    Sets . Exclude ( Next , i ) 
                  END (* IF *) 
               END (* FOR *) 
             ; IF ( From <= EobDefaultState ) 
                  AND ( EobDefaultState <= To ) 
                  AND Sets . IsElement ( EobDefaultState , Current ) 
               THEN 
                 State := EobDefaultState       (* prefer eob def. state *) 
               ELSIF NOT Sets . IsEmpty ( Next ) 
               THEN 
                 State := Sets . Select ( Next )       (* prefer cyclic state  *) 
               ELSE 
                 State := Sets . Select ( Current ) (* prefer small state   *) 
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
         Sets . ReleaseSet ( DBPtr ^ [ State ] . Domain ) 
      ; Sets . ReleaseSet ( DBPtr ^ [ State ] . Defaults ) 
      ; Sets . ReleaseSet ( DBPtr ^ [ State ] . Users ) 
      END (* FOR *) 
    ; Sets . ReleaseSet ( Domain1 ) 
    ; Sets . ReleaseSet ( Domain2 ) 
    ; Sets . ReleaseSet ( Marked ) 
    ; Sets . ReleaseSet ( WorkingSet ) 
    ; Sets . ReleaseSet ( Cyclics ) 
    ; Sets . ReleaseSet ( Current ) 
    ; Sets . ReleaseSet ( Next ) 
    ; Sets . ReleaseSet ( Successors ) 
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

