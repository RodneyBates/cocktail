(* Ich, Dr. Rodney Bates, Informatiker, Nov., 2021. *)

UNSAFE MODULE System
(* In Modula2, this was an interface for machine dependencies,implemented
   by C code.  This version uses Modula3 libraries, while preserving
   function. *)

; FROM SYSTEM IMPORT M2LONGINT  

; IMPORT FileRd 
; IMPORT FileWr
; IMPORT Params
; IMPORT Process 
; IMPORT Rd
; IMPORT Stdio
; IMPORT Text
; IMPORT Time AS M3Time 
; IMPORT Thread 
; IMPORT Wr 
; IMPORT Word

; IMPORT OSError 

; CONST CharSpecFiles = SET OF tFile { StdInput , StdOutput , StdError }
; CONST FirstDynFile = 3

; CONST FakeArrayLast = 1000000

; TYPE CharsRefTyp = UNTRACED REF ARRAY [ 0 .. FakeArrayLast ] OF CHAR

(* Binary IO. *)

; VAR InMap := ARRAY tFile OF Rd . T { NIL , .. }  

; VAR OutMap := ARRAY tFile OF Wr . T { NIL , .. } 

; PROCEDURE NewFileNo ( ) : tFile  
    RAISES { FileNoError (*No available tFile value.*)} 
  = VAR LResult : tFile
  ; BEGIN
      LResult := FirstDynFile
    ; LOOP
        IF LResult > LAST ( InMap ) THEN RAISE FileNoError END 
      ; IF InMap [ LResult ] = NIL AND OutMap [ LResult ] = NIL
        THEN RETURN LResult
        END (*IF*)
      ; INC ( LResult ) 
      END (*LOOP*)
    END NewFileNo

(*EXPORTED*)
; PROCEDURE OpenInputT (FileNameText: TEXT) : tFile
    RAISES { OSError . E , FileNoError (*No available tFile value.*) } 
  = VAR RdT : Rd . T
  ; VAR LResult : tFile
  ; BEGIN
      LResult := NewFileNo ( ) 
    ; RdT := FileRd . Open ( FileNameText )
    ; InMap [ LResult ] := RdT 
    ; RETURN LResult  
    END OpenInputT
    
(* TODO: Rename this OpenInputA. *)  
(*EXPORTED*)
; PROCEDURE OpenInput ( READONLY FileName : ARRAY OF CHAR ) : tFile
    RAISES { OSError . E , FileNoError (*No available tFile value.*) } 
  = VAR LResult : tFile
  ; BEGIN
      RETURN OpenInputT (Text . FromChars ( FileName ));
    END OpenInput
  
(*EXPORTED*)
; PROCEDURE OpenOutputT (FileNameText: TEXT) : tFile
    RAISES { OSError . E , FileNoError (*No available tFile value.*)} 
  = VAR WrT : Wr . T
  ; VAR LResult : tFile
  ; BEGIN
      LResult := NewFileNo ( ) 
    ; WrT := FileWr . Open ( FileNameText )
    ; OutMap [ LResult ] := WrT 
    ; RETURN LResult  
    END OpenOutputT

(* TODO: Rename this OpenOutputA. *)  
(*EXPORTED*)
; PROCEDURE OpenOutput ( READONLY FileName : ARRAY OF CHAR ) : tFile
    RAISES { OSError . E , FileNoError (*No available tFile value.*)} 
  = VAR LResult : tFile
  ; BEGIN
      RETURN OpenOutputT (Text . FromChars ( FileName ));
    END OpenOutput

; PROCEDURE Test ( VAR Form : ARRAY OF CHAR )
  = VAR Adr := ADR ( Form )
  ; VAR First := ADR ( Form )
  ; VAR Last := LAST ( Form )
  ; VAR Number := NUMBER ( Form )
  ; BEGIN
      EVAL First 
    END Test 
  
(*EXPORTED*)
; PROCEDURE Read ( File : tFile ; Buffer : ADDRESS ; Size : INTEGER ) : INTEGER 
    RAISES 
      { Thread.Alerted , Rd.Failure
      , FileNoError (*File not open for reading.*)
      }
  = VAR LRdT : Rd . T
  ; VAR LResult : INTEGER
  ; VAR LCharsRef : CharsRefTyp
; VAR LCharsRef2 : UNTRACED REF ARRAY [ 0 .. 18000 ] OF CHAR 
  ; BEGIN
      IF InMap [ File ] = NIL THEN RAISE FileNoError END
    ; LRdT :=  InMap [ File ] 
    ; IF LRdT = NIL THEN RAISE FileNoError END
    ; LCharsRef := LOOPHOLE ( Buffer , CharsRefTyp ) 
; LCharsRef2 := LOOPHOLE ( Buffer , UNTRACED REF ARRAY [ 0 .. 18000 ] OF CHAR )
; Test ( LCharsRef2 ^ ) 
; Test ( SUBARRAY ( LCharsRef2 ^ , 0 , 16 ) ) 
; Test ( LCharsRef ^ ) 
; Test ( SUBARRAY ( LCharsRef ^ , 0 , 16 ) ) 
    ; LResult := Rd . GetSub ( LRdT , SUBARRAY ( LCharsRef ^ , 0 , Size ) )
    ; RETURN LResult     
    END Read 
  
(*EXPORTED*)
; PROCEDURE Write ( File : tFile ; Buffer : ADDRESS ; Size : INTEGER )
  : INTEGER (* What's this ????? *) 
    RAISES
      { Thread.Alerted , Wr.Failure
      , FileNoError (*File not open for writing.*)
      }
  = VAR LWrT : Wr . T
  ; VAR LCharsRef : CharsRefTyp 
  ; BEGIN
      IF OutMap [ File ] = NIL THEN RAISE FileNoError END
    ; LWrT :=  OutMap [ File ] 
    ; IF LWrT = NIL THEN RAISE FileNoError END
    ; LCharsRef := LOOPHOLE ( Buffer , CharsRefTyp ) 
    ; Wr . PutString ( LWrT , SUBARRAY ( LCharsRef ^ , 0 , Size ) )
    ; RETURN Size (* Huh? *)
    END Write 
  
(*EXPORTED*)
; PROCEDURE Close ( File : tFile )
    RAISES
      { Thread.Alerted, Rd.Failure, Wr.Failure
      , FileNoError (* File is char special or not open.*)
      }
  = BEGIN
      IF File IN CharSpecFiles THEN (*RAISE FileNoError*) END 
    ; IF InMap [ File ] # NIL
      THEN Rd . Close ( InMap [ File ] ) 
      ELSIF OutMap [ File ] # NIL
      THEN Wr . Close ( OutMap [ File ] ) 
      ELSE RAISE FileNoError 
      END (*IF*)
    ; InMap [ File ] := NIL 
    ; OutMap [ File ] := NIL 
    END Close 
  
(*EXPORTED*)
; PROCEDURE IsCharacterSpecial ( File : tFile ) : BOOLEAN
  = BEGIN
      RETURN File IN CharSpecFiles 
    END IsCharacterSpecial 
  
(*EXPORTED*)
; PROCEDURE SysAlloc (ByteCount: M2LONGINT): ADDRESS
  (* Not used or implemented. *)
  = BEGIN
      <*ASSERT FALSE *>
    END SysAlloc
  
(*EXPORTED*)
; PROCEDURE Time ( ) : M2LONGINT 
  (* WARNING: This is wall-clock time in seconds.  It appears Cocktail
     wants CPU time, but I don't easily see how to get that. *)
  = VAR LLRTime : LONGREAL
  ; BEGIN
      LLRTime := M3Time . Now ( )
    ; RETURN ROUND ( LLRTime ) 
    END Time 
  
(*EXPORTED*)
; PROCEDURE GetArgCount ( ) : CARDINAL 
  = BEGIN
      RETURN Params . Count
    END GetArgCount 

; PROCEDURE TextToChars
    ( T : TEXT ; VAR Ct : CARDINAL (* Not counting added nul char. *)
    ; VAR Chars : ARRAY OF CHAR
    )

  = VAR LCharsNum , LTextNum , LMinNum : CARDINAL 
  ; BEGIN
      LCharsNum := NUMBER ( Chars )
    ; IF LCharsNum <= 0 THEN Ct := 0 ; RETURN END 
    ; IF T = NIL THEN LTextNum := 0
      ELSE
        LTextNum := Text . Length ( T )
      ; Text . SetChars ( Chars , T , start := 0 )
      END (*IF*)
    ; LMinNum := MIN ( LCharsNum , LTextNum )
    ; IF LMinNum < LCharsNum THEN Chars [ LMinNum ] := '\000' END
    ; Ct := LMinNum 
    END TextToChars 

(*EXPORTED*)
; PROCEDURE GetArgument ( ArgNum : CARDINAL ; VAR Argument : ARRAY OF CHAR )
  = VAR LText : TEXT
  ; VAR LCt : CARDINAL 
  ; BEGIN
      LText := Params . Get ( ArgNum )
    ; TextToChars ( LText , LCt , Argument ) 
    END GetArgument 
  
(*EXPORTED*)
; PROCEDURE PutArgs       (Argc: INTEGER; Argv: ADDRESS)
  = BEGIN
    END PutArgs 
  
(*EXPORTED*)
; PROCEDURE ErrNum ( ) : INTEGER
  = BEGIN
      RETURN UnknownErrNum 
    END ErrNum 
  
(*EXPORTED*)
; PROCEDURE System ( VAR String : ARRAY OF CHAR ) : INTEGER
  = BEGIN
      <*ASSERT FALSE*> 
    END System 
  
(*EXPORTED*)
; PROCEDURE Exit ( Status : INTEGER )
  = BEGIN
      Process . Exit ( Status ) 
    END Exit 
  
; BEGIN
    InMap [ StdInput ] := Stdio . stdin 
  ; OutMap [ StdOutput ] := Stdio . stdout 
  ; OutMap [ StdError ] := Stdio . stderr 
  END System
.
