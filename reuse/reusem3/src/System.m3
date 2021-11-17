(* Ich, Dr. Rodney Bates, Informatiker, Nov., 2021. *)

UNSAFE MODULE System
(* In Modula2, this was an interface for machine dependencies,implemented
   by C code.  This version uses Modula3 libraries, while preserving
   function. *)

; FROM SYSTEM IMPORT M2LONGINT  

; IMPORT FileRd 
; IMPORT FileWr 
; IMPORT Rd
; IMPORT Stdio
; IMPORT Text 
; IMPORT Thread 
; IMPORT Wr 
; IMPORT Word

; IMPORT OSError 

; CONST CharSpecFiles = SET OF tFile { StdInput , StdOutput , StdError }
; CONST FirstDynFile = 3

; CONST FakeArrayLast = 100000

; TYPE CharsRef = UNTRACED REF ARRAY [ 0 .. FakeArrayLast ] OF CHAR

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
; PROCEDURE OpenInput ( READONLY FileName : ARRAY OF CHAR ) : tFile
    RAISES { OSError . E , FileNoError (*No available tFile value.*) } 
  = VAR FileNameText : TEXT
  ; VAR RdT : Rd . T
  ; VAR LResult : tFile
  ; BEGIN
      LResult := NewFileNo ( ) 
    ; FileNameText := Text . FromChars ( FileName )
    ; RdT := FileRd . Open ( FileNameText )
    ; InMap [ LResult ] := RdT 
    ; RETURN LResult  
    END OpenInput
  
(*EXPORTED*)
; PROCEDURE OpenOutput ( READONLY FileName : ARRAY OF CHAR ) : tFile
    RAISES { OSError . E , FileNoError (*No available tFile value.*)} 
  = VAR FileNameText : TEXT
  ; VAR WrT : Wr . T
  ; VAR LResult : tFile
  ; BEGIN
      LResult := NewFileNo ( ) 
    ; FileNameText := Text . FromChars ( FileName )
    ; WrT := FileWr . Open ( FileNameText )
    ; OutMap [ LResult ] := WrT 
    ; RETURN LResult  
    END OpenOutput
  
(*EXPORTED*)
; PROCEDURE Read ( File : tFile ; Buffer : ADDRESS ; Size : INTEGER ) : INTEGER 
    RAISES 
      { Thread.Alerted , Rd.Failure
      , FileNoError (*File not open for reading.*)
      }
  = VAR LRdT : Rd . T
  ; VAR LResult : INTEGER
  ; BEGIN
      IF InMap [ File ] = NIL THEN RAISE FileNoError END
    ; LRdT :=  InMap [ File ] 
    ; IF LRdT = NIL THEN RAISE FileNoError END
    ; LResult
        := Rd . GetSub
	     ( LRdT , SUBARRAY ( LOOPHOLE ( Buffer , CharsRef ) ^ , 0 , Size ) )
    ; RETURN LResult     
    END Read 
  
(*EXPORTED*)
; PROCEDURE Write ( File : tFile ; Buffer : ADDRESS ; Size : INTEGER )
    RAISES
      { Thread.Alerted , Wr.Failure
      , FileNoError (*File not open for writing.*)
      }
  = VAR LWrT : Wr . T
  ; BEGIN
      IF OutMap [ File ] = NIL THEN RAISE FileNoError END
    ; LWrT :=  OutMap [ File ] 
    ; IF LWrT = NIL THEN RAISE FileNoError END
    ; Wr . PutString
        ( LWrT , SUBARRAY ( LOOPHOLE ( Buffer , CharsRef ) ^ , 0 , Size ) )
    END Write 
  
(*EXPORTED*)
; PROCEDURE Close ( File : tFile )
    RAISES
      { Thread.Alerted, Rd.Failure, Wr.Failure
      , FileNoError (* File is char special or not open.*)
      }
  = BEGIN
      IF File IN CharSpecFiles THEN RAISE FileNoError END 
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
; PROCEDURE SysAlloc      (ByteCount: M2LONGINT): ADDRESS
  = BEGIN
    END SysAlloc 
  
(*EXPORTED*)
; PROCEDURE Time          (): M2LONGINT
  = BEGIN
    END Time 
  
(*EXPORTED*)
; PROCEDURE GetArgCount   (): Word.T
  = BEGIN
    END GetArgCount 
  
(*EXPORTED*)
; PROCEDURE GetArgument   (ArgNum: INTEGER; VAR Argument: ARRAY OF CHAR)
  = BEGIN
    END GetArgument 
  
(*EXPORTED*)
; PROCEDURE PutArgs       (Argc: INTEGER; Argv: ADDRESS)
  = BEGIN
    END PutArgs 
  
(*EXPORTED*)
; PROCEDURE ErrNum        (): INTEGER
  = BEGIN
    END ErrNum 
  
(*EXPORTED*)
; PROCEDURE System        (VAR String: ARRAY OF CHAR): INTEGER
  = BEGIN
    END System 
  
(*EXPORTED*)
; PROCEDURE Exit          (Status: INTEGER)
  = BEGIN
    END Exit 
  
; BEGIN
    InMap [ StdInput ] := Stdio . stdin 
  ; OutMap [ StdOutput ] := Stdio . stdout 
  ; OutMap [ StdError ] := Stdio . stderr 
  END System
.
