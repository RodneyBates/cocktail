(* $Id: Errors.mi,v 3.4 1992/09/29 19:02:45 grosch rel $ *) 

(* $Log: Errors.mi,v $ 
 * Revision 3.4  1992/09/29  19:02:45  grosch 
 * abort execution upon errors during scanning 
 * 
 * Revision 3.3  1992/08/07  15:10:26  grosch 
 * allow several scanner and parsers; extend module Errors 
 * 
 * Revision 3.2  1991/12/04  16:16:58  grosch 
 * unified escape conventions for all tools 
 * 
 * Revision 3.1  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.0  91/04/04  18:06:55  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 2.0  91/03/08  18:17:43  grosch 
 * turned tables into initialized arrays (in C) 
 * reduced case size 
 * changed interface for source position 
 * 
 * Revision 1.3  91/02/13  11:34:31  grosch 
 * moved tables from file to initialization in C; reduced case size 
 * 
 * Revision 1.2  89/02/23  15:55:14  grosch 
 * added completeness check for the automaton 
 * 
 * Revision 1.1  89/01/17  15:00:23  grosch 
 * correction and redesign of source position handling 
 * 
 * Revision 1.0  88/10/04  11:59:34  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE MODULE RexErrors 

; IMPORT Stdio 
; IMPORT Text 
; IMPORT Wr 

; FROM SYSTEM IMPORT SHORTCARD , M2LONGINT , HALT 

; FROM ReuseIO 
  IMPORT StdError , WriteC , WriteNl , WriteI , WriteS , WriteT , WriteLong 
  , WriteB 
  , WriteR , CloseIO 

; FROM Strings IMPORT tString 

; FROM Idents IMPORT tIdent , WriteIdent 

; FROM Positions IMPORT tPosition , WritePosition 

; IMPORT Word , Strings 

; CONST IdentUndefined = 10 
  ; ImproperUse = 11 
  ; IdentDefBefore = 12 
  ; BraceMissing = 13 
  ; UnclosedComment = 14 
  ; PatternNoMatch = 15 
  ; UnclosedString = 16 

; PROCEDURE ErrorMessage 
    ( ErrorCode , ErrorClass : Word . T ; Position : tPosition ) 

  = BEGIN (* ErrorMessage *) 
      ErrorMessageI ( ErrorCode , ErrorClass , Position , None , NIL ) 
    END ErrorMessage 

; PROCEDURE ErrorMessageI 
    ( ErrorCode , ErrorClass : Word . T 
    ; Position : tPosition 
    ; InfoClass : Word . T 
    ; Info : ADDRESS 
    ) 

  = BEGIN (* ErrorMessageI *) 
      WriteErrorMessage ( ErrorCode , ErrorClass , Position ) 
    ; WriteInfo ( InfoClass , Info ) 
    ; WriteNl ( StdError ) 
    ; IF ErrorClass <= Error THEN INC ( ErrorCount ) END (* IF *) 
    ; IF ErrorClass = Fatal THEN CloseIO ( ) ; HALT ( ) END (* IF *) 
    END ErrorMessageI 

; PROCEDURE WriteErrorMessage 
    ( ErrorCode , ErrorClass : Word . T ; Position : tPosition ) 

  = BEGIN (* WriteErrorMessage *) 
      WritePosition ( StdError , Position ) 
    ; WriteT ( StdError , ": " ) 

    ; CASE ErrorClass 
      OF Fatal 
      => WriteT ( StdError , "Fatal       " ) 
      | Restriction 
      => WriteT ( StdError , "Restriction " ) 
      | Error 
      => WriteT ( StdError , "Error       " ) 
      | Warning 
      => WriteT ( StdError , "Warning     " ) 
      | Repair 
      => WriteT ( StdError , "Repair      " ) 
      | Note 
      => WriteT ( StdError , "Note        " ) 
      | Information 
      => WriteT ( StdError , "Information " ) 
      ELSE 
        WriteT ( StdError , "Error class: " ) 
      ; WriteI ( StdError , ErrorClass , 0 ) 
      END (* CASE *) 

    ; CASE ErrorCode 
      OF NoText 
      => 
      | SyntaxError 
      => WriteT ( StdError , "syntax error" ) 
      | ExpectedTokens 
      => WriteT ( StdError , "expected tokens" ) 
      | RestartPoint 
      => WriteT ( StdError , "restart point" ) 
      | TokenInserted 
      => WriteT ( StdError , "token inserted " ) 
      | WrongParseTable 
      => WriteT ( StdError , "parse table mismatch" ) 
      | OpenParseTable 
      => WriteT ( StdError , "cannot open parse table" ) 
      | ReadParseTable 
      => WriteT ( StdError , "cannot read parse table" ) 
      | IdentUndefined 
      => WriteT ( StdError , "identifier undefined" ) 
      | ImproperUse 
      => WriteT ( StdError , "improper use of identifier" ) 
      | IdentDefBefore 
      => WriteT ( StdError , "identifier already defined" ) 
      | BraceMissing 
      => WriteT ( StdError , "closing '}' missing" ) 
      | UnclosedComment 
      => WriteT ( StdError , "unclosed comment" ) 
      | PatternNoMatch 
      => WriteT ( StdError , "pattern will never match" ) 
      | UnclosedString 
      => WriteT ( StdError , "unclosed string" ) 
      ELSE 
        WriteT ( StdError , " error code: " ) 
      ; WriteI ( StdError , ErrorCode , 0 ) 
      END (* CASE *) 
    END WriteErrorMessage 

; PROCEDURE WriteInfo ( InfoClass : Word . T ; Info : ADDRESS ) 

  = VAR PtrToInteger : UNTRACED BRANDED REF INTEGER 
    ; PtrToShort : UNTRACED BRANDED REF SHORTCARD 
    ; PtrToLong : UNTRACED BRANDED REF M2LONGINT 
    ; PtrToReal : UNTRACED BRANDED REF REAL 
    ; PtrToBoolean : UNTRACED BRANDED REF BOOLEAN 
    ; PtrToCharacter : UNTRACED BRANDED REF CHAR 
    ; PtrToString : UNTRACED BRANDED REF tString 
    ; PtrToArray : UNTRACED BRANDED REF ARRAY [ 0 .. 1023 ] OF CHAR 
    ; PtrToIdent : UNTRACED BRANDED REF tIdent 

  ; BEGIN (* WriteInfo *) 
      IF InfoClass = None THEN RETURN END (* IF *) 
    ; WriteT ( StdError , ": " ) 
    ; CASE InfoClass 
      OF Integer 
      => PtrToInteger := Info 
      ; WriteI ( StdError , PtrToInteger ^ , 0 ) 
      | Short 
      => PtrToShort := Info 
      ; WriteI ( StdError , PtrToShort ^ , 0 ) 
      | Long 
      => PtrToLong := Info 
      ; WriteLong ( StdError , PtrToLong ^ , 0 ) 
      | Real 
      => PtrToReal := Info 
      ; WriteR ( StdError , PtrToReal ^ , 1 , 10 , 1 ) 
      | Boolean 
      => PtrToBoolean := Info 
      ; WriteB ( StdError , PtrToBoolean ^ ) 
      | Character 
      => PtrToCharacter := Info 
      ; WriteC ( StdError , PtrToCharacter ^ ) 
      | String 
      => PtrToString := Info 
      ; Strings . WriteS ( StdError , PtrToString ^ ) 
      | Array 
      => PtrToArray := Info 
      ; WriteS ( StdError , PtrToArray ^ ) 
      | Ident 
      => PtrToIdent := Info 
      ; WriteIdent ( StdError , PtrToIdent ^ ) 
      ELSE 
        WriteT ( StdError , "info class: " ) 
      ; WriteI ( StdError , InfoClass , 0 ) 
      END (* CASE *) 
    END WriteInfo 

; PROCEDURE ErrLine ( msg : TEXT ) 

  = BEGIN (* ErrLine *) 
      Wr . PutText ( Stdio . stderr , msg ) 
    ; Wr . PutText ( Stdio . stderr , Wr . EOL ) 
    ; Wr . Flush ( Stdio . stderr ) 
    END ErrLine 

; BEGIN (* RexErrors *) 
    ErrorCount := 0 
  END RexErrors 
. 

