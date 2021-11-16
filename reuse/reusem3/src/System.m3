(* Ich, Dr. Rodney Bates, Informatiker, Nov., 2021. *)

UNSAFE MODULE  System
(* In Modula2, this was an interface for machine dependencies,implemented
   by C code.  This version uses Modula3 libraries, while preserving
   function.  *)

; FROM SYSTEM IMPORT M2LONGINT
; IMPORT Rd
; IMPORT Stdio
; IMPORT Wr 
; IMPORT Word

; IMPORT OSError 

; CONST cMaxFile     = 32
; CONST StdInput     = 0
; CONST StdOutput    = 1
; CONST StdError     = 2

; CONST FirstDynFile = 3

; TYPE tFile      = [-1 .. cMaxFile]

(* Binary IO. *)

; VAR InMap := ARRAY tFile OF Rd . T { NIL , .. }  

; VAR OutMap := ARRAY tFile OF Wr . T { NIL , .. } 

; PROCEDURE NewWrFileNo ( ) : tFile  

(*EXPORTED*)
; PROCEDURE OpenInput ( READONLY FileName : ARRAY OF CHAR ) : tFile
    RAISES { OSError . E , TooManyFiles } 
  = VAR FileNameText : TEXT
  ; VAR RdT : Rd . T
  ; VAR Result : tFile
  ; BEGIN
      LResult := FirstDynFile
    ; LOOP
        IF LResult > LAST ( InMap ) THEN RAISE TooManyFiles END 
      ; IF InMap [ LResult ] = NIL AND OutMap [ LResult ] = NIL THEN EXIT END
      ; INC ( LResult ) 
      END (*LOOP*)
    ; FileNameText := Text . FromChars ( FileName )
    ; RdT := FileRd . Open ( FileNameText )
    ; InMap [ LResult := RdT ]
    ; RETURN RdT 
    END OpenInput
  
(*EXPORTED*)
; PROCEDURE OpenOutput    (READONLY FileName: ARRAY OF CHAR): tFile
    RAISES { OSError . E , TooManyFiles } 
  = VAR FileNameText : TEXT
  ; VAR WrT : Wr . t
  ; VAR Result : tFile
  ; BEGIN
      LResult := FirstDynFile
    ; LOOP
        IF LResult > LAST ( InMap ) THEN RAISE TooManyFiles END 
      ; IF InMap [ LResult ] = NIL AND OutMap [ LResult ] = NIL THEN EXIT END
      ; INC ( LResult ) 
      END (*LOOP*)
    ; FileNameText := Text . FromChars ( FileName )
    ; WrT := FileRd . Open ( FileNameText )
    ; OutMap [ LResult := WrT ]
    ; RETURN WrT 
    END OpenIutput
  
(*EXPORTED*)
; PROCEDURE Read          (File: tFile; Buffer: ADDRESS; Size: INTEGER): INTEGER
  = BEGIN
    END Re<d 
  
(*EXPORTED*)
; PROCEDURE Write         (File: tFile; Buffer: ADDRESS; Size: INTEGER): INTEGER
(*EXPORTED*)
  = BEGIN
    END Write 
  
(*EXPORTED*)
; PROCEDURE Close         (File: tFile)
  = BEGIN
    END Close 
  
(*EXPORTED*)
; PROCEDURE IsCharacterSpecial (File: tFile): BOOLEAN
  = BEGIN
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


