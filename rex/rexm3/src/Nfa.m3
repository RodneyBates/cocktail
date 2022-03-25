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

UNSAFE MODULE Nfa 


; FROM SYSTEM IMPORT M2LONGINT 

; FROM DynArray IMPORT MakeArray , ExtendArray , ReleaseArray 

; FROM ReuseIO IMPORT WriteC , WriteI , WriteNl , WriteT , StdOutput 

; FROM Layout IMPORT WriteChar , WriteSpace 

; FROM ScanTabs IMPORT RuleType , NoRule 

; FROM GenTabs IMPORT LeafCount 


; CONST InitialTransitionTableSize = 4096 

; TYPE Transition 
    = RECORD 
        Ch : CHAR 
      ; NextState : NStateRange 
      ; NextTrans : TransitionRange 
      END (* RECORD *) 

  ; NStateInfo 
    = RECORD 
        Transitions : TransitionRange 
      ; Semantics : RuleType 
      END (* RECORD *) 

  ; NStateTable = ARRAY [ 0 .. 100000 ] OF NStateInfo 
  ; TransitionTable = ARRAY [ 0 .. 100000 ] OF Transition 
(* necessary to force index arithmetic to be done with long integers *) 

; VAR NStateTablePtr : UNTRACED BRANDED REF NStateTable 
  ; NStateTableSize : M2LONGINT 

  ; TransitionTablePtr : UNTRACED BRANDED REF TransitionTable 
  ; TransitionTableSize : M2LONGINT 

; PROCEDURE MakeNState ( pTransitions : TransitionRange ) : NStateRange 

  = BEGIN (* MakeNState *) 
      INC ( NStateCount ) 
    ; IF NStateCount = NStateTableSize 
      THEN 
        ExtendArray 
          ( LOOPHOLE ( NStateTablePtr , ADDRESS ) 
          , NStateTableSize 
          , BYTESIZE ( NStateInfo ) 
          ) 
      END (* IF *) 
    ; WITH With_8 = NStateTablePtr ^ [ NStateCount ] 
      DO With_8 . Transitions := pTransitions 
      ; With_8 . Semantics := NoRule 
      END (* WITH *) 
    ; RETURN NStateCount 
    END MakeNState 

; PROCEDURE PutNSemantics ( State : NStateRange ; pSemantics : RuleType ) 

  = BEGIN (* PutNSemantics *) 
      NStateTablePtr ^ [ State ] . Semantics := pSemantics 
    END PutNSemantics 

; PROCEDURE GetNSemantics ( State : NStateRange ) : RuleType 

  = BEGIN (* GetNSemantics *) 
      RETURN NStateTablePtr ^ [ State ] . Semantics 
    END GetNSemantics 

; PROCEDURE PutTransitions 
    ( State : NStateRange ; Transitions : TransitionRange ) 

  = BEGIN (* PutTransitions *) 
      NStateTablePtr ^ [ State ] . Transitions := Transitions 
    END PutTransitions 

; PROCEDURE GetTransitions ( State : NStateRange ) : TransitionRange 

  = BEGIN (* GetTransitions *) 
      RETURN NStateTablePtr ^ [ State ] . Transitions 
    END GetTransitions 

; PROCEDURE IsLastTransition ( Transition : TransitionRange ) : BOOLEAN 

  = BEGIN (* IsLastTransition *) 
      RETURN Transition = NoTransition 
    END IsLastTransition 

; PROCEDURE NextTransition ( Transition : TransitionRange ) : TransitionRange 

  = BEGIN (* NextTransition *) 
      RETURN TransitionTablePtr ^ [ Transition ] . NextTrans 
    END NextTransition 

; PROCEDURE MakeTransition 
    ( pCh : CHAR ; State : NStateRange ) : TransitionRange 

  = BEGIN (* MakeTransition *) 
      INC ( TransitionCount ) 
    ; IF TransitionCount = TransitionTableSize 
      THEN 
        ExtendArray 
          ( LOOPHOLE ( TransitionTablePtr , ADDRESS ) 
          , TransitionTableSize 
          , BYTESIZE ( Transition ) 
          ) 
      END (* IF *) 
    ; WITH With_9 = TransitionTablePtr ^ [ TransitionCount ] 
      DO With_9 . Ch := pCh 
      ; With_9 . NextState := State 
      ; With_9 . NextTrans := NoTransition 
      END (* WITH *) 
    ; RETURN TransitionCount 
    END MakeTransition 

; PROCEDURE AddTransition 
    ( Transition , Transitions : TransitionRange ) : TransitionRange 

  = BEGIN (* AddTransition *) 
      TransitionTablePtr ^ [ Transition ] . NextTrans := Transitions 
    ; RETURN Transition 
    END AddTransition 

; PROCEDURE GetCh ( Transition : TransitionRange ) : CHAR 

  = BEGIN (* GetCh *) 
      RETURN TransitionTablePtr ^ [ Transition ] . Ch 
    END GetCh 

; PROCEDURE GetNextState ( Transition : TransitionRange ) : NStateRange 

  = BEGIN (* GetNextState *) 
      RETURN TransitionTablePtr ^ [ Transition ] . NextState 
    END GetNextState 

; PROCEDURE UniteTransitions ( t1 , t2 : TransitionRange ) : TransitionRange 

  = VAR t : TransitionRange 

  ; BEGIN (* UniteTransitions *) 
      IF t1 = NoTransition THEN RETURN t2 END (* IF *) (* IsLastTransition *) 
    ; WHILE t2 # NoTransition 
      DO                                        (* NOT IsLastTransition *) 
         t := TransitionTablePtr ^ [ t2 ] . NextTrans (* NextTransition *) 
      ; t1 := AddTransition ( t2 , t1 ) 
      ; t2 := t 
      END (* WHILE *) 
    ; RETURN t1 
    END UniteTransitions 

; PROCEDURE CopyTransitions ( t1 : TransitionRange ) : TransitionRange 

  = VAR t2 : TransitionRange 

  ; BEGIN (* CopyTransitions *) 
      t2 := NoTransition 
    ; WHILE t1 # NoTransition 
      DO                                        (* NOT IsLastTransition *) 
         WITH With_10 = TransitionTablePtr ^ [ t1 ] 
         DO (* GetCh + GetNextState *) 
            t2 
              := AddTransition 
                   ( MakeTransition ( With_10 . Ch , With_10 . NextState ) 
                   , t2 
                   ) 
         ; t1 := With_10 . NextTrans                     (* NextTransition *) 
         END (* WITH *) 
      END (* WHILE *) 
    ; RETURN t2 
    END CopyTransitions 

; PROCEDURE WriteNfa ( ) 

  = BEGIN (* WriteNfa *) 
      WriteT ( StdOutput , "NFA :" ) 
    ; WriteNl ( StdOutput ) 
    ; WriteNl ( StdOutput ) 
    ; FOR State := 1 TO NStateCount 
      DO WriteT ( StdOutput , "State, Semantics =" ) 
      ; WriteI ( StdOutput , State , 5 ) 
      ; WriteI ( StdOutput , GetNSemantics ( State ) , 5 ) 
      ; WriteNl ( StdOutput ) 
      ; WriteTransitions ( GetTransitions ( State ) ) 
      ; WriteNl ( StdOutput ) 
      ; WriteNl ( StdOutput ) 
      END (* FOR *) 
    ; WriteNl ( StdOutput ) 
    END WriteNfa 

; PROCEDURE WriteTransitions ( Transition : TransitionRange ) 

  = VAR Count : INTEGER 

  ; BEGIN (* WriteTransitions *) 
      Count := 0 
    ; WHILE NOT IsLastTransition ( Transition ) 
      DO IF Count = 10 THEN WriteNl ( StdOutput ) ; Count := 0 END (* IF *) 
      ; INC ( Count ) 
      ; WriteChar ( StdOutput , GetCh ( Transition ) ) 
      ; WriteSpace ( StdOutput ) 
      ; WriteI ( StdOutput , GetNextState ( Transition ) , 1 ) 
      ; WriteC ( StdOutput , ',' ) 
      ; WriteSpace ( StdOutput ) 
      ; Transition := NextTransition ( Transition ) 
      END (* WHILE *) 
    END WriteTransitions 

; PROCEDURE FinalizeNfa ( ) 

  = BEGIN (* FinalizeNfa *) 
      ReleaseArray 
        ( NStateTablePtr , NStateTableSize , BYTESIZE ( NStateInfo ) ) 
    ; ReleaseArray 
        ( TransitionTablePtr , TransitionTableSize , BYTESIZE ( Transition ) ) 
    END FinalizeNfa 

; PROCEDURE BeginNfa ( ) 

  = BEGIN (* BeginNfa *) 
      NStateTableSize := LeafCount + 1 
    ; MakeArray 
        ( LOOPHOLE ( NStateTablePtr , ADDRESS ) 
        , NStateTableSize 
        , BYTESIZE ( NStateInfo ) 
        ) 
    ; NStateCount := 0 

    ; TransitionTableSize := InitialTransitionTableSize 
    ; MakeArray 
        ( LOOPHOLE ( TransitionTablePtr , ADDRESS ) 
        , TransitionTableSize 
        , BYTESIZE ( Transition ) 
        ) 
    ; TransitionCount := 0 
    END BeginNfa 

; BEGIN (* Nfa *) 
  END Nfa 
. 

