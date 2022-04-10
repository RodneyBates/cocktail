(* File Scanner.i30 *)

INTERFACE Scanner

; IMPORT Strings 

(* User export declarations ($E): *)
(* line 2 "rexm3.rex" *)


; IMPORT Word 

; FROM Idents IMPORT tIdent 
; FROM StringMem IMPORT tStringRef 
; FROM Texts IMPORT tText  
; FROM Positions IMPORT tPosition 
; TYPE tScanAttribute 
    = RECORD 
        Position : tPosition 
      ; Ident : tIdent 
      ; Number : INTEGER 
      ; String : tStringRef 
      ; Ch : CHAR 
      ; Text : tText 
      END (* RECORD *) 

; PROCEDURE ErrorAttribute 
    ( Token : Word . T ; VAR Attribute : tScanAttribute )


(* End of line 2 "rexm3.rex" *)
(* End of user export declarations ($E): *)

; CONST EofToken        = 0

; VAR TokenLength : INTEGER
; VAR Attribute : tScanAttribute
; VAR ScanTabName : TEXT 
; VAR Exit : PROCEDURE ( ) 

; PROCEDURE BeginScanner ( ) 
; PROCEDURE BeginFile ( FileName : TEXT ) 
; PROCEDURE GetToken ( ) : INTEGER
; PROCEDURE GetWord ( VAR Word : Strings . tString ) 
; PROCEDURE GetLower ( VAR Word : Strings . tString ) 
; PROCEDURE GetUpper ( VAR Word : Strings . tString ) 
; PROCEDURE CloseFile ( ) 
; PROCEDURE CloseScanner ( ) 
; PROCEDURE UpperCase ( Ch : CHAR ) : CHAR  
; PROCEDURE LowerCase ( Ch : CHAR ) : CHAR  
; PROCEDURE TotalLineCount ( ) : CARDINAL  
  (* line count including all files read. *) 

; END Scanner.
