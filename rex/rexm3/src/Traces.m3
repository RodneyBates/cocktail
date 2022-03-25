(* $Id: Traces.mi,v 3.1 1991/11/21 14:41:19 grosch rel $ *) 

(* $Log: Traces.mi,v $ 
 * Revision 3.1  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.0  91/04/04  18:08:01  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 1.2  89/11/06  12:36:33  grosch 
 * renamed module Rex to GenTabs to avoid name clash with rex under VMS 
 * 
 * Revision 1.1  88/10/24  20:12:18  grosch 
 * fixed bug: ExtendArray in ResetTraces must be called earlier 
 * 
 * Revision 1.0  88/10/04  11:59:53  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE MODULE Traces 


; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT SHORTCARD 

; FROM Dfa IMPORT DStateRange , DNoState 

; FROM GenTabs IMPORT StartStateCount 

; FROM DynArray IMPORT MakeArray , ExtendArray , ReleaseArray 

; CONST InitialRELength = 16 

; TYPE TraceStepPtr = UNTRACED BRANDED REF TraceStep 
  ; TraceStep 
    = RECORD 
        TraceState : DStateRange 
      ; NewState : DStateRange 
      ; Next : TraceStepPtr 
      END (* RECORD *) 
  ; Trace = ARRAY [ 0 .. 100000 ] OF TraceStep 
  ; PosToTrace = ARRAY [ 0 .. 100000 ] OF TraceStepPtr 

; VAR TracePtr : UNTRACED BRANDED REF Trace 
  ; TraceSize : M2LONGINT 
  ; PosToTracePtr : UNTRACED BRANDED REF PosToTrace 
  ; PosToTraceSize : M2LONGINT 
  ; TraceCount : INTEGER 

; PROCEDURE InitTraces ( ) 

  = BEGIN (* InitTraces *) 
      PosToTraceSize := InitialRELength 
    ; MakeArray 
        ( LOOPHOLE ( PosToTracePtr , ADDRESS ) 
        , PosToTraceSize 
        , BYTESIZE ( TraceStepPtr ) 
        ) 
    ; TraceSize := StartStateCount * PosToTraceSize 
    ; MakeArray 
        ( LOOPHOLE ( TracePtr , ADDRESS ) 
        , TraceSize 
        , BYTESIZE ( TraceStep ) 
        ) 
    END InitTraces 

; PROCEDURE ResetTraces ( StringLength : INTEGER ) 

  = BEGIN (* ResetTraces *) 
      WHILE PosToTraceSize <= StringLength 
      DO ExtendArray 
           ( LOOPHOLE ( PosToTracePtr , ADDRESS ) 
           , PosToTraceSize 
           , BYTESIZE ( TraceStepPtr ) 
           ) 
      END (* WHILE *) 
    ; WHILE TraceSize <= ( StartStateCount * StringLength ) 
      DO ExtendArray 
           ( LOOPHOLE ( TracePtr , ADDRESS ) 
           , TraceSize 
           , BYTESIZE ( TraceStep ) 
           ) 
      END (* WHILE *) 
    ; TraceCount := 0 
    ; FOR i := 1 TO StringLength 
      DO PosToTracePtr ^ [ i ] := NIL 
      END (* FOR *) 
    END ResetTraces 

; PROCEDURE RecordTrace 
    ( Position : SHORTCARD ; pTraceState , pNewState : DStateRange ) 

  = BEGIN (* RecordTrace *) 
      INC ( TraceCount )                        (* record trace step *) 
    ; WITH With_15 = TracePtr ^ [ TraceCount ] 
      DO With_15 . TraceState := pTraceState 
      ; With_15 . NewState := pNewState 
      ; With_15 . Next := PosToTracePtr ^ [ Position ] 
      END (* WITH *) 
    ; PosToTracePtr ^ [ Position ] 
        := ADR        ( TracePtr ^ [ TraceCount ] ) 
    END RecordTrace 

; PROCEDURE RecordedTrace 
    ( Position : SHORTCARD ; pTraceState : DStateRange ) : DStateRange 

  = VAR ActTraceStep : TraceStepPtr 

  ; BEGIN (* RecordedTrace *) 
      ActTraceStep := PosToTracePtr ^ [ Position ] (* search previous traces *) 
    ; WHILE ActTraceStep # NIL 
      DO IF ActTraceStep ^ . TraceState = pTraceState 
         THEN 
           RETURN ActTraceStep ^ . NewState 
         END (* IF *) 
      ; ActTraceStep := ActTraceStep ^ . Next 
      END (* WHILE *) 
    ; RETURN DNoState 
    END RecordedTrace 

; PROCEDURE FinalizeTraces ( ) 

  = BEGIN (* FinalizeTraces *) 
      ReleaseArray ( TracePtr , TraceSize , BYTESIZE ( TraceStep ) ) 
    ; ReleaseArray 
        ( PosToTracePtr , PosToTraceSize , BYTESIZE ( TraceStepPtr ) ) 
    END FinalizeTraces 

; BEGIN (* Traces *) 
  END Traces 
. 

