(* File Scanner.m30. *) 

UNSAFE MODULE Scanner 

; FROM SYSTEM IMPORT SHORTCARD , M2LONGINT , M2LONGCARD

; IMPORT OSError 
; IMPORT Process

; IMPORT Checks 
  , System 
  , General 
  , Positions 
  , ReuseIO 
  , DynArray 
  , Strings
; IMPORT RexErrors

; IMPORT Source 
(* Global user declarations ($G): *) 
(* line 25 "rexm3.rex" *)


; IMPORT Word 

; FROM Strings 
  IMPORT tString , Concatenate , Char , SubString , StringToInt , AssignEmpty 
  , Length 
; FROM Texts IMPORT MakeText , Append 
; FROM StringMem IMPORT tStringRef , PutString 
; FROM Idents IMPORT tIdent , MakeIdent , NoIdent 
; FROM RexErrors IMPORT ErrorMessage , Error 
; FROM ScanGen IMPORT Language , tLanguage 
; FROM Positions IMPORT tPosition 

; CONST SymIdent = 1 
  ; SymNumber = 2 
  ; SymString = 3 
  ; SymChar = 4 
  ; SymTargetcode = 5 
  ; SymScanner = 37 
  ; SymExport = 32 
  ; SymGlobal = 6 
  ; SymLocal = 31 
  ; SymBegin = 7 
  ; SymClose = 8 
  ; SymEof = 34 
  ; SymDefault = 36 
  ; SymDefine = 9 
  ; SymStart = 10 
  ; SymRules = 11 
  ; SymNot = 30 
  ; SymDot = 12 
  ; SymComma = 13 
  ; SymEqual = 14 
  ; SymColon = 15 
  ; SymColonMinus = 35 
  ; SymNrSign = 33 
  ; SymSlash = 16 
  ; SymBar = 17 
  ; SymPlus = 18 
  ; SymMinus = 19 
  ; SymAsterisk = 20 
  ; SymQuestion = 21 
  ; SymLParen = 22 
  ; SymRParen = 23 
  ; SymLBracket = 24 
  ; SymRBracket = 25 
  ; SymLBrace = 26 
  ; SymRBrace = 27 
  ; SymLess = 28 
  ; SymGreater = 29 

  ; BraceMissing = 13 
  ; UnclosedComment = 14 
  ; UnclosedString = 16 

; VAR BraceNestingLevel , CommentNestingLevel : INTEGER 
  ; string : tString 
  ; NoString : tStringRef 
  ; TargetPos : tPosition 
  ; CommentPos : tPosition 
  ; StringPos : tPosition 
  ; PrevState : SHORTCARD 
  ; InsideTarget : BOOLEAN 

; PROCEDURE ErrorAttribute 
    ( Token : Word . T ; VAR Attribute : tScanAttribute ) 

  = BEGIN (* ErrorAttribute *) 
      CASE Token 
      OF SymIdent 
      => Attribute . Ident := NoIdent 
      | SymNumber 
      => Attribute . Number := 0 
      | SymString 
      => Attribute . String := NoString 
      | SymChar 
      => Attribute . Ch := '?' 
      | SymTargetcode 
      => MakeText ( Attribute . Text ) 
      ELSE 
      END (* CASE *) 
    END ErrorAttribute 

(* End of line 25 "rexm3.rex" *)
(* End of global user declarations ($G). *) 

; CONST yyTabSpace = 8 
; CONST yyDNoState = 0 
; CONST yyFileStackSize = 32 
; CONST yyInitBufferSize = ( 1024 * 8 ) + 256 
(* User constant declarations ($C): *) 
; yyFirstCh = '\000'
; yyLastCh = '\177'
; yyEolCh = '\012'
; yyEobCh = '\177'
; yyDStateCount = 182
; yyTableSize = 2281
; yyEobState = 52
; yyDefaultState = 53
; STD = 1
; targetcode = 3
; set = 5
; rules = 7
; CComment = 9
; M2Comment = 11
; Str1 = 13
; Str2 = 15
; CStr1 = 17
; CStr2 = 19
(* End of user constant declarations ($C). *) 

; TYPE yyTableElmt = SHORTCARD 
; TYPE yyStateRange (*yyTableElmt*) = [ 0 .. yyDStateCount ] 
; TYPE yyStateRangePacked = BITS BITSIZE ( yyTableElmt ) FOR yyStateRange 
; TYPE yyTableRange (*yyTableElmt*) = [ 0 .. yyTableSize ] 
; TYPE yyCombType = RECORD Check , Next : BITS 16 FOR yyStateRange END (* RECORD *) 
; TYPE yyCombTypePtr = UNTRACED BRANDED REF yyCombType 
; TYPE yytChBufferPtr = UNTRACED BRANDED REF ARRAY [ 0 .. 1000000 ] OF CHAR 
; TYPE yyChRange = [ yyFirstCh .. yyLastCh ] 
; TYPE yyFileStackPtrTyp = SHORTCARD 
; TYPE yyFileStackSubscript (*yyFileStackPtrTyp*) = [ 1 .. yyFileStackSize ] 

; VAR yyBasePtr : ARRAY yyStateRange OF M2LONGCARD 
; VAR yyDefault : ARRAY yyStateRange OF yyStateRangePacked
; VAR yyComb : ARRAY yyTableRange OF yyCombType 
; VAR yyEobTrans : ARRAY yyStateRange OF yyStateRangePacked
(* Only for ReduceCaseSize, #1 ($M): *)
(* End of only for ReduceCaseSize, #1 ($M): *)
; VAR yyToLower , yyToUpper : ARRAY yyChRange OF CHAR 

; VAR yyStateStack 
    : UNTRACED BRANDED REF ARRAY [ 0 .. 1000000 ] OF yyStateRange 
; VAR yyStateStackSize : M2LONGINT 
; VAR yyStartState : yyStateRange 
; VAR yyPreviousStart : yyStateRange 

; VAR yySourceFile : System . tFile 
; VAR yyEof : BOOLEAN 
; VAR yyChBufferPtr : yytChBufferPtr 
; VAR yyChBufferStart : INTEGER 
; VAR yyChBufferSize : M2LONGINT 
; VAR yyChBufferIndex : INTEGER 
; VAR yyBytesRead : INTEGER 
; VAR yyLineCount : SHORTCARD (* Number of the current line, 
                                        of the current file. *) 
; VAR yyTotalLineCount : Word . T    (* Number of lines already read, 
                                        of all files. *) 
; VAR yyLineStart : INTEGER 

; VAR yyFileStackPtr : yyFileStackPtrTyp 
; VAR yyFileStack 
    : ARRAY yyFileStackSubscript 
      OF RECORD 
           SourceFile : System . tFile 
         ; Eof : BOOLEAN 
         ; ChBufferPtr : yytChBufferPtr 
         ; ChBufferStart : INTEGER 
         ; ChBufferSize : M2LONGINT 
         ; ChBufferIndex : INTEGER 
         ; BytesRead : INTEGER 
         ; LineCount : SHORTCARD 
         ; LineStart : INTEGER 
         END (* RECORD *) 

; PROCEDURE GetToken ( ) : INTEGER 

  = VAR yyState : yyStateRange 
  ; VAR yyTablePtr : yyCombTypePtr 
  ; VAR yyRestartFlag : BOOLEAN 
  ; VAR yyi , yySource , yyTarget : INTEGER 
  ; VAR yyChBufferFree : M2LONGINT 

(* User local declarations ($L): *) 
(* line 111 "rexm3.rex" *)

  ; VAR TargetCode , String , Word : tString 

  ; PROCEDURE AccumComment ( ) 

    = BEGIN (* AccumComment *) 
        IF InsideTarget AND ( BraceNestingLevel > 0 ) 
        THEN 
          GetWord ( Word ) 
        ; Concatenate ( TargetCode , Word ) 
        END (* IF *) 
      END AccumComment 
  
(* End of line 111 "rexm3.rex" *)
(* End of user local declarations ($L). *)

  ; BEGIN (* GetToken *) 
      LOOP 
        yyState := yyStartState 
      ; TokenLength := 0 
(* Only for LeftJustUsed ($J): *)
(* End of only for LeftJustUsed ($J): *)

      (* ASSERT yyChBuffer [ yyChBufferIndex] = first character *) 

      ; LOOP (* eventually restart after sentinel *) 
          LOOP (* execute as many state transitions as possible *) 
            (* determine next state *) 
            yyTablePtr 
              := LOOPHOLE 
                   ( yyBasePtr [ yyState ] 
                     + ( VAL 
                           ( ORD ( yyChBufferPtr ^ [ yyChBufferIndex ] ) 
                           , M2LONGCARD 
                           ) 
                         * VAL ( BYTESIZE ( yyCombType ) , M2LONGCARD ) 
                       ) 
                   , yyCombTypePtr 
                   ) 
          ; IF yyTablePtr ^ . Check # yyState 
            THEN 
              yyState := yyDefault [ yyState ] 
            ; IF yyState = yyDNoState THEN EXIT END (* IF *) 
            ELSE 
              yyState := yyTablePtr ^ . Next 
            ; INC ( TokenLength ) 
            ; yyStateStack ^ [ TokenLength ] := yyState (* push state *) 
            ; INC ( yyChBufferIndex ) (* get next character *) 
            END (* IF *) 
          END (* LOOP *) 

        ; LOOP  (* search for last final state *)
(* Generated actions ($A): *)
 CASE yyStateStack^ [TokenLength] OF
| 182
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 170 "rexm3.rex" *)

                           ; IF BraceNestingLevel = 0 
                             THEN 
                               MakeText ( Attribute . Text ) 
                             ; AssignEmpty ( TargetCode ) 
                             ; TargetPos := Attribute . Position 
                             ; InsideTarget := TRUE 
                             ELSE 
                               GetWord ( Word ) 
                             ; Concatenate ( TargetCode , Word ) 
                             END (* IF *) 
                           ; INC ( BraceNestingLevel ) 
                        
(* End of line 170 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 181
=> 
(* line 184 "rexm3.rex" *)

              DEC ( BraceNestingLevel ) 
            ; IF BraceNestingLevel = 0 
              THEN 
                yyStart ( PrevState ) 
              ; InsideTarget := FALSE 
              ; Append ( Attribute . Text , TargetCode ) 
              ; Attribute . Position := TargetPos 
              ; RETURN SymTargetcode 
              ELSE 
                GetWord ( Word ) 
              ; Concatenate ( TargetCode , Word ) 
              END (* IF *)
                            
(* End of line 184 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 34
, 47
, 57
, 65
, 73
, 164
, 170
=> 
(* line 200 "rexm3.rex" *)

              IF BraceNestingLevel > 0 
              THEN 
                GetWord ( Word ) 
              ; Concatenate ( TargetCode , Word ) 
              END (* IF *) 

                        
(* End of line 200 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 180
=> 
(* line 209 "rexm3.rex" *)

               IF BraceNestingLevel > 0 
               THEN 
                 Strings . Append ( TargetCode , '\011' ) 
               END (* IF *) 
            ; yyTab ( ) 

                           
(* End of line 209 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 179
=> 
(* line 218 "rexm3.rex" *)

               IF BraceNestingLevel > 0 
               THEN 
                 Append ( Attribute . Text , TargetCode ) 
               ; AssignEmpty ( TargetCode ) 
               END (* IF *) 
            ; yyEol ( 0 ) 
                           
(* End of line 218 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 35
=> 
(* line 227 "rexm3.rex" *)

               IF BraceNestingLevel > 0 
               THEN 
                 GetWord ( Word ) 
               ; Strings . Append ( TargetCode , Char ( Word , 2 ) ) 
               END (* IF *) 
                           
(* End of line 227 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 42
=> 
(* line 235 "rexm3.rex" *)

               IF BraceNestingLevel > 0 
               THEN 
                 Strings . Append ( TargetCode , '\\' ) 
               END (* IF *) 
                           
(* End of line 235 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 178
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 244 "rexm3.rex" *)

            ; GetWord ( String ) 
            ; StringPos := Attribute . Position 
            ; IF Language = tLanguage . C 
              THEN yyStart ( CStr1 )
              ELSE yyStart ( Str1 ) 
              END (* IF *) 
                          
(* End of line 244 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 177
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 253 "rexm3.rex" *)

            ; GetWord ( String ) 
            ; StringPos := Attribute . Position 
            ; IF Language = tLanguage . C 
              THEN yyStart ( CStr2 ) 
              ELSE yyStart ( Str2 ) 
              END (* IF *) 
                          
(* End of line 253 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 24
, 60
, 68
, 76
=> 
(* line 265 "rexm3.rex" *)
 GetWord (Word)
                                  ; Concatenate (String, Word)
                                
(* End of line 265 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 23
, 61
, 69
, 77
=> 
(* line 265 "rexm3.rex" *)
 GetWord (Word)
                                  ; Concatenate (String, Word)
                                
(* End of line 265 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 22
, 38
, 50
, 62
, 70
, 78
=> 
(* line 265 "rexm3.rex" *)
 GetWord (Word)
                                  ; Concatenate (String, Word)
                                
(* End of line 265 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 21
, 37
, 49
, 63
, 71
, 79
=> 
(* line 265 "rexm3.rex" *)
 GetWord (Word)
                                  ; Concatenate (String, Word)
                                
(* End of line 265 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 176
=> 
(* line 270 "rexm3.rex" *)
   GetWord (Word)
                             ; Concatenate (String, Word)
                             ; yyEol (0)
                           
(* End of line 270 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 175
=> 
(* line 270 "rexm3.rex" *)
   GetWord (Word)
                             ; Concatenate (String, Word)
                             ; yyEol (0)
                           
(* End of line 270 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 174
=> 
(* line 276 "rexm3.rex" *)
Strings.Append (String, Char (String, 1))
                            ; yyPrevious ( ) 
                            ; Concatenate (TargetCode, String)
                        
(* End of line 276 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 173
=> 
(* line 276 "rexm3.rex" *)
Strings.Append (String, Char (String, 1))
                            ; yyPrevious ( ) 
                            ; Concatenate (TargetCode, String)
                        
(* End of line 276 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 172
=> 
(* line 281 "rexm3.rex" *)
   Strings.Append ( String , '\011' )
                                   ; yyTab ( ) 
                                 
(* End of line 281 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 171
=> 
(* line 286 "rexm3.rex" *)
    ErrorMessage ( UnclosedString , Error , StringPos )
                           ; Strings.Append ( String , Char ( String , 1 ) )
                           ; yyEol ( 0 )
                           ; yyPrevious  ( )
                           ; Concatenate ( TargetCode , String ) 
                        
(* End of line 286 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 169
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 296 "rexm3.rex" *)

            ; yyStart ( M2Comment ) 
            ; AccumComment ( ) 
            ; CommentNestingLevel := 1 
            ; CommentPos := Attribute . Position 
     
(* End of line 296 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 168
=> 
(* line 303 "rexm3.rex" *)
 INC ( CommentNestingLevel ) ; AccumComment ( ) 
(* End of line 303 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 166
=> 
(* line 305 "rexm3.rex" *)


               AccumComment ( ) 
            ; DEC ( CommentNestingLevel ) 
            ; IF CommentNestingLevel = 0 THEN yyPrevious ( ) END (* IF *) 
                           
(* End of line 305 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 25
, 39
, 59
, 67
, 75
, 165
, 167
=> 
(* line 312 "rexm3.rex" *)
 AccumComment ( ) 
(* End of line 312 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 163
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 317 "rexm3.rex" *)

            ; yyStart ( CComment ) 
            ; AccumComment ( ) 
            ; CommentPos := Attribute . Position 
     
(* End of line 317 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 161
=> 
(* line 323 "rexm3.rex" *)
 AccumComment ( ) ; yyPrevious ( ) 
(* End of line 323 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 26
, 40
, 58
, 66
, 74
=> 
(* line 325 "rexm3.rex" *)
 AccumComment ( ) 
(* End of line 325 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 160
=> 
(* line 330 "rexm3.rex" *)

               IF InsideTarget AND ( BraceNestingLevel > 0 ) 
               THEN 
                 Strings . Append ( TargetCode , '\011' ) 
               END (* IF *) 
            ; yyTab ( ) 
                        
(* End of line 330 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 159
=> 
(* line 339 "rexm3.rex" *)

               IF InsideTarget AND ( BraceNestingLevel > 0 ) 
               THEN 
                 Append ( Attribute . Text , TargetCode ) 
               ; AssignEmpty ( TargetCode ) 
               END (* IF *) 
            ; yyEol ( 0 ) 
                        
(* End of line 339 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 158
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 348 "rexm3.rex" *)
; PrevState := STD; yyStart (targetcode); RETURN SymExport     
(* End of line 348 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 153
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 349 "rexm3.rex" *)
; PrevState := STD; yyStart (targetcode); RETURN SymGlobal     
(* End of line 349 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 147
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 350 "rexm3.rex" *)
; PrevState := STD; yyStart (targetcode); RETURN SymLocal      
(* End of line 350 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 142
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 351 "rexm3.rex" *)
; PrevState := STD; yyStart (targetcode); RETURN SymBegin      
(* End of line 351 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 137
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 352 "rexm3.rex" *)
; PrevState := STD; yyStart (targetcode); RETURN SymClose      
(* End of line 352 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 132
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 353 "rexm3.rex" *)
; PrevState := STD; yyStart (targetcode); RETURN SymDefault    
(* End of line 353 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 128
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 354 "rexm3.rex" *)
; PrevState := STD; yyStart (targetcode); RETURN SymEof        
(* End of line 354 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 125
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 355 "rexm3.rex" *)
; RETURN SymScanner    
(* End of line 355 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 119
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 356 "rexm3.rex" *)
; RETURN SymDefine     
(* End of line 356 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 113
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 357 "rexm3.rex" *)
; RETURN SymStart      
(* End of line 357 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 36
, 48
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 358 "rexm3.rex" *)
; yyStart (rules);     RETURN SymRules         
(* End of line 358 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 108
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 359 "rexm3.rex" *)
; RETURN SymNot        
(* End of line 359 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 28
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 361 "rexm3.rex" *)

            ; GetWord ( Word ) 
            ; Attribute . Ident := MakeIdent ( Word ) 
            ; RETURN SymIdent 
                        
(* End of line 361 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 29
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 367 "rexm3.rex" *)

            ; GetWord ( Word ) 
            ; Attribute . Number := StringToInt ( Word ) 
            ; RETURN SymNumber 
                        
(* End of line 367 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 33
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 373 "rexm3.rex" *)

            ; GetWord ( Word ) 
            ; SubString ( Word , 2 , Length ( Word ) - 1 , TargetCode ) 
            ; Attribute . String := PutString ( TargetCode ) 
            ; RETURN SymString 
                        
(* End of line 373 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 105
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 380 "rexm3.rex" *)
; RETURN SymDot        
(* End of line 380 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 104
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 381 "rexm3.rex" *)
; RETURN SymEqual      
(* End of line 381 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 103
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 382 "rexm3.rex" *)
; yyPrevious ( ) ; RETURN SymRBrace        
(* End of line 382 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 102
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 383 "rexm3.rex" *)
; RETURN SymMinus      
(* End of line 383 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 101
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 384 "rexm3.rex" *)
; RETURN SymComma      
(* End of line 384 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 100
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 385 "rexm3.rex" *)
; RETURN SymBar        
(* End of line 385 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 99
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 386 "rexm3.rex" *)
; RETURN SymPlus       
(* End of line 386 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 98
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 387 "rexm3.rex" *)
; RETURN SymAsterisk   
(* End of line 387 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 97
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 388 "rexm3.rex" *)
; RETURN SymQuestion   
(* End of line 388 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 96
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 389 "rexm3.rex" *)
; RETURN SymLParen     
(* End of line 389 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 95
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 390 "rexm3.rex" *)
; RETURN SymRParen     
(* End of line 390 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 94
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 391 "rexm3.rex" *)
; RETURN SymLBracket   
(* End of line 391 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 93
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 392 "rexm3.rex" *)
; RETURN SymRBracket   
(* End of line 392 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 92
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 393 "rexm3.rex" *)
; yyStart (set);       RETURN SymLBrace        
(* End of line 393 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 91
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 394 "rexm3.rex" *)
; RETURN SymNrSign     
(* End of line 394 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 90
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 395 "rexm3.rex" *)
; RETURN SymSlash      
(* End of line 395 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 89
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 396 "rexm3.rex" *)
; RETURN SymLess       
(* End of line 396 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 88
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 397 "rexm3.rex" *)
; RETURN SymGreater    
(* End of line 397 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 86
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 398 "rexm3.rex" *)
; PrevState := rules; yyStart (targetcode); RETURN SymColon
(* End of line 398 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 87
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 399 "rexm3.rex" *)
; PrevState := rules; yyStart (targetcode); RETURN SymColonMinus
(* End of line 399 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 85
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 401 "rexm3.rex" *)
; Attribute.Ch := '\012' ;  RETURN SymChar
(* End of line 401 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 84
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 402 "rexm3.rex" *)
; Attribute.Ch := '\011' ; RETURN SymChar
(* End of line 402 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 83
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 403 "rexm3.rex" *)
; Attribute.Ch := '\013' ; RETURN SymChar
(* End of line 403 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 82
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 404 "rexm3.rex" *)
; Attribute.Ch := '\010' ; RETURN SymChar
(* End of line 404 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 81
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 405 "rexm3.rex" *)
; Attribute.Ch := '\015' ; RETURN SymChar
(* End of line 405 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 80
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 406 "rexm3.rex" *)
; Attribute.Ch := '\014' ; RETURN SymChar
(* End of line 406 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 32
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 408 "rexm3.rex" *)

            ; GetWord ( Word ) 
            ; SubString ( Word , 2 , Length ( Word ) , TargetCode ) 
            ; Attribute . Ch := VAL ( StringToInt ( TargetCode ) , CHAR ) 
            ; RETURN SymChar 
                        
(* End of line 408 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 31
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 415 "rexm3.rex" *)

            ; GetWord ( Word ) 
            ; Attribute . Ch := Char ( Word , 2 ) 
            ; RETURN SymChar 
                        
(* End of line 415 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 27
, 41
, 162
=> 
  Attribute.Position.Line   := yyLineCount 
; Attribute.Position.Column := yyChBufferIndex - yyLineStart - TokenLength 
(* line 421 "rexm3.rex" *)

            ; GetWord ( Word ) 
            ; Attribute . Ch := Char ( Word , 1 ) 
            ; RETURN SymChar 
                        
(* End of line 421 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 72
=> 
(* line 427 "rexm3.rex" *)
 EVAL Word (* Because ";" will follow. *) 
(* End of line 427 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 64
=> 
(* line 428 "rexm3.rex" *)
 EVAL Word (* Because ";" will follow. *) 
(* End of line 428 "rexm3.rex" *)
; yyRestartFlag := FALSE; EXIT 
| 56
=> 
(* BlankAction *)
  WHILE yyChBufferPtr^ [yyChBufferIndex] = ' ' DO INC (yyChBufferIndex) END 
; yyRestartFlag := FALSE; EXIT 
| 55
=> 
(* TabAction *)
  DEC ( yyLineStart , 7 - (yyChBufferIndex - yyLineStart - 2 ) MOD 8 ) 
; yyRestartFlag := FALSE; EXIT 
| 54
=> 
(* EolAction *)
 INC ( yyLineCount ) 
; yyLineStart := yyChBufferIndex - 1 
; yyRestartFlag := FALSE; EXIT 
(* End of generated actions ($A): *)
(* Non final states ($N): *)  
| 1
, 2
, 3
, 4
, 5
, 6
, 7
, 8
, 9
, 10
, 11
, 12
, 13
, 14
, 15
, 16
, 17
, 18
, 19
, 20
, 30
, 43
, 44
, 45
, 46
, 51
, 106
, 107
, 109
, 110
, 111
, 112
, 114
, 115
, 116
, 117
, 118
, 120
, 121
, 122
, 123
, 124
, 126
, 127
, 129
, 130
, 131
, 133
, 134
, 135
, 136
, 138
, 139
, 140
, 141
, 143
, 144
, 145
, 146
, 148
, 149
, 150
, 151
, 152
, 154
, 155
, 156
, 157
=> 
(* End of non final states ($N). *)  

            DEC ( yyChBufferIndex ) (* return character *) 
          ; DEC ( TokenLength ) (* pop state *) 

(* Only for ReduceCaseSize, #2 ($P): *)
| 53 => 
(* End of only for ReduceCaseSize, #2 ($P): *)
              Attribute . Position . Line := yyLineCount 
            ; Attribute . Position . Column 
                := VAL ( yyChBufferIndex - yyLineStart , SHORTCARD ) 
            ; INC ( yyChBufferIndex ) 
            ; TokenLength := 1
(* Only for default line ($D): *)            
; ReuseIO . WriteC     ( ReuseIO . StdOutput , yyChBufferPtr ^ [ yyChBufferIndex - 1 ] ) 
(* End of only for default line ($D). *)            
            ; yyRestartFlag := FALSE 
            ; EXIT 

            | yyDNoState 
            => (* automatic initialization *) 
               yyGetTables ( ) 
            ; yyStateStack ^ [ 0 ] := yyDefaultState (* stack underflow sentinel *) 
            ; IF yyFileStackPtr = 0 
              THEN 
                yyInitialize ( ) 
              ; yySourceFile := System . StdInput 
              END (* IF *) 
            ; yyRestartFlag := FALSE 
            ; EXIT 

(* Only for ReduceCaseSize, #3 ($O): *)
| 52 => 
(* End only for ReduceCaseSize, #3 ($O): *)
               DEC ( yyChBufferIndex ) (* undo last state transition *) 
            ; DEC ( TokenLength ) (* get previous state *) 
            ; IF TokenLength = 0 
              THEN 
                yyState := yyStartState 
(* Only for LeftJustUsed ($J): *)
(* End of only for LeftJustUsed ($J): *)
              ELSE 
                yyState := yyStateStack ^ [ TokenLength ] 
              END (* IF *) 

            ; IF yyChBufferIndex # ( yyChBufferStart + yyBytesRead ) 
              THEN 
                yyState := yyEobTrans [ yyState ] (* end of buffer sentinel in buffer *) 
              ; IF yyState # yyDNoState 
                THEN 
                  INC ( yyChBufferIndex ) 
                ; INC ( TokenLength ) 
                ; yyStateStack ^ [ TokenLength ] := yyState 
                ; yyRestartFlag := TRUE 
                ; EXIT 
                END (* IF *) 
              ELSE (* end of buffer reached *) 

                (* copy initial part of token in front of input buffer *) 
                yySource := yyChBufferIndex - TokenLength - 1 
              ; yyTarget 
                  := General . MaxAlign 
                     - ( TokenLength MOD General . MaxAlign ) 
                     - 1 
              ; IF yySource # yyTarget 
                THEN 
                  FOR yyi := 1 TO TokenLength 
                  DO yyChBufferPtr ^ [ yyTarget + yyi ] 
                       := yyChBufferPtr ^ [ yySource + yyi ] 
                  END (* FOR *) 
                ; DEC ( yyLineStart , yySource - yyTarget ) 
                ; yyChBufferStart := yyTarget + TokenLength + 1 
                ELSE 
                  yyChBufferStart := yyChBufferIndex 
                END (* IF *) 

              ; IF NOT yyEof 
                THEN (* read buffer and restart *) 
                  yyChBufferFree 
                    := VAL 
                         ( General . Exp2 
                             ( General . Log2 
                                 ( yyChBufferSize 
                                   - 4 
                                   - VAL ( General . MaxAlign , M2LONGINT ) 
                                   - VAL ( TokenLength , M2LONGINT ) 
                                 ) 
                             ) 
                         , M2LONGINT 
                         ) 
                ; IF yyChBufferFree < ( yyChBufferSize DIV 8 ) 
                  THEN 
                    DynArray . ExtendArray 
                      ( LOOPHOLE ( yyChBufferPtr , ADDRESS ) 
                      , yyChBufferSize 
                      , BYTESIZE ( CHAR ) 
                      ) 
                  ; IF yyChBufferPtr = NIL 
                    THEN 
                      yyErrorMessage ( 1 ) 
                    END (* IF *) 
                  ; yyChBufferFree 
                      := VAL 
                           ( General . Exp2 
                               ( General . Log2 
                                   ( yyChBufferSize 
                                     - 4 
                                     - VAL ( General . MaxAlign , M2LONGINT ) 
                                     - VAL ( TokenLength , M2LONGINT ) 
                                   ) 
                               ) 
                           , M2LONGINT 
                           ) 
                  ; IF yyStateStackSize < yyChBufferSize 
                    THEN 
                      DynArray . ExtendArray 
                        ( LOOPHOLE ( yyStateStack , ADDRESS )  
                        , yyStateStackSize 
                        , BYTESIZE ( yyStateRange ) 
                        ) 
                    ; IF yyStateStack = NIL 
                      THEN 
                        yyErrorMessage ( 1 ) 
                      END (* IF *) 
                    END (* IF *) 
                  END (* IF *) 
                ; yyChBufferIndex := yyChBufferStart 
                ; yyBytesRead 
               := Source . GetLine 
                         ( yySourceFile 
                         , ADR ( yyChBufferPtr ^ [ yyChBufferIndex ] ) 
                         , yyChBufferFree  
                         ) 
                ; IF yyBytesRead <= 0 
                  THEN 
                    yyBytesRead := 0 
                  ; yyEof := TRUE 
                  END (* IF *) 
                ; yyChBufferPtr ^ [ yyChBufferStart + yyBytesRead ] 
                    := yyEobCh 
                ; yyChBufferPtr ^ [ yyChBufferStart + yyBytesRead + 1 ] 
                    := '\000' 
                ; yyRestartFlag := TRUE 
                ; EXIT 
                END (* IF *) 

              ; IF TokenLength = 0 
                THEN (* end of file reached *) 
                  Attribute . Position . Line := yyLineCount 
                ; Attribute . Position . Column 
                    := VAL ( yyChBufferIndex - yyLineStart , SHORTCARD ) 
                ; CloseFile ( ) 
                ; IF yyFileStackPtr = 0 
                  THEN
(* Eof action ($E): *)
(* line 133 "rexm3.rex" *)

   CASE yyStartState OF
   | targetcode , set   
   => ErrorMessage ( BraceMissing , Error , TargetPos ) 
   | CComment , M2Comment       
   => ErrorMessage ( UnclosedComment , Error , CommentPos ) 
   ; IF InsideTarget 
     THEN ErrorMessage ( BraceMissing , Error , TargetPos ) 
     END (* IF *) ; 
   | CStr1, CStr2, Str1, Str2
   => ErrorMessage ( UnclosedString , Error , StringPos );
      IF InsideTarget 
      THEN ErrorMessage ( BraceMissing , Error , TargetPos ) 
      END (* IF *) ; 
   ELSE
   END (* CASE *) 
 ; yyStart (STD) 

(* End of line 133 "rexm3.rex" *)
(* End of Eof action ($E): *)
                  END (* IF *) 
                ; IF yyFileStackPtr = 0 THEN RETURN EofToken END (* IF *) 
                ; yyRestartFlag := FALSE 
                ; EXIT 
                END (* IF *) 
              END (* IF *) 
            ELSE 
              yyErrorMessage ( 0 ) 
            END (* CASE *) 
          END (* LOOP *) 
        ; IF yyRestartFlag THEN ELSE EXIT END (* IF *) 
        END (* LOOP *) 
      END (* LOOP *) 
    END GetToken 

; PROCEDURE BeginFile ( FileName : TEXT )  

  = BEGIN (* BeginFile *) 
      IF yyStateStack ^ [ 0 ] = yyDNoState 
      THEN (* have tables been read in ? *) 
        yyGetTables ( ) 
      ; yyStateStack ^ [ 0 ] := yyDefaultState (* stack underflow sentinel *) 
      END (* IF *) 
    ; yyInitialize ( ) 
 ; yySourceFile := Source . BeginSource ( FileName ) 
    ; IF yySourceFile < 0 THEN yyErrorMessage ( 5 ) END (* IF *) 
    END BeginFile 

; PROCEDURE yyInitialize ( ) 

  = BEGIN (* yyInitialize *) 
      IF yyFileStackPtr >= yyFileStackSize 
      THEN 
        yyErrorMessage ( 3 ) 
      END (* IF *) 
      (* push file *) 
    ; INC ( yyFileStackPtr ) 
    ; WITH m2tom3_with_1 = yyFileStack [ yyFileStackPtr ] 
      DO m2tom3_with_1 . SourceFile := yySourceFile 
      ; m2tom3_with_1 . Eof := yyEof 
      ; m2tom3_with_1 . ChBufferPtr := yyChBufferPtr 
      ; m2tom3_with_1 . ChBufferStart := yyChBufferStart 
      ; m2tom3_with_1 . ChBufferSize := yyChBufferSize 
      ; m2tom3_with_1 . ChBufferIndex := yyChBufferIndex 
      ; m2tom3_with_1 . BytesRead := yyBytesRead 
      ; m2tom3_with_1 . LineCount := yyLineCount 
      ; m2tom3_with_1 . LineStart := yyLineStart 
      END (* WITH *) 
      (* initialize file state *) 
    ; yyChBufferSize := yyInitBufferSize 
    ; DynArray . MakeArray
        ( LOOPHOLE ( yyChBufferPtr , ADDRESS ) 
        , yyChBufferSize 
        , BYTESIZE ( CHAR ) 
        ) 
    ; IF yyChBufferPtr = NIL THEN yyErrorMessage ( 1 ) END (* IF *) 
    ; yyChBufferStart := General . MaxAlign 
    ; yyChBufferPtr ^ [ yyChBufferStart - 1 ] := yyEolCh (* begin of line indicator *) 
    ; yyChBufferPtr ^ [ yyChBufferStart ] := yyEobCh (* end of buffer sentinel *) 
    ; yyChBufferPtr ^ [ yyChBufferStart + 1 ] := '\000' 
    ; yyChBufferIndex := yyChBufferStart 
    ; yyEof := FALSE 
    ; yyBytesRead := 0 
    ; yyLineCount := 1 
    ; yyTotalLineCount := 0 
    ; yyLineStart := yyChBufferStart - 1 
    END yyInitialize 

; PROCEDURE CloseFile ( ) 

  = BEGIN (* CloseFile *) 
      IF yyFileStackPtr = 0 THEN yyErrorMessage ( 4 ) END (* IF *) 
 ; Source . CloseSource ( yySourceFile ) 
    ; DynArray . ReleaseArray 
        ( yyChBufferPtr , yyChBufferSize , BYTESIZE ( CHAR ) ) 

      (* pop file *)
      ; WITH m2tom3_with_2 = yyFileStack [ yyFileStackPtr ] 
      DO 
        yySourceFile := m2tom3_with_2 . SourceFile 
      ; yyEof := m2tom3_with_2 . Eof 
      ; yyChBufferPtr := m2tom3_with_2 . ChBufferPtr 
      ; yyChBufferStart := m2tom3_with_2 . ChBufferStart 
      ; yyChBufferSize := m2tom3_with_2 . ChBufferSize 
      ; yyChBufferIndex := m2tom3_with_2 . ChBufferIndex 
      ; yyBytesRead := m2tom3_with_2 . BytesRead 
      ; yyLineCount := m2tom3_with_2 . LineCount 
      ; yyLineStart := m2tom3_with_2 . LineStart 
      END (* WITH *) 
    ; DEC ( yyFileStackPtr ) 
    END CloseFile 

; PROCEDURE GetWord ( VAR Word : Strings . tString ) 

  = VAR i , WordStart : INTEGER 

  ; BEGIN (* GetWord *) 
      WordStart := yyChBufferIndex - TokenLength - 1 
    ; FOR i := 1 TO TokenLength 
      DO Word . Chars [ VAL ( i , Strings . tStringIndex ) ] 
           := yyChBufferPtr ^ [ WordStart + i ] 
      END (* FOR *) 
    ; Word . Length := VAL ( TokenLength , SHORTCARD ) 
    END GetWord 

; PROCEDURE GetLower ( VAR Word : Strings . tString ) 

  = VAR i , WordStart : INTEGER 

  ; BEGIN (* GetLower *) 
      WordStart := yyChBufferIndex - TokenLength - 1 
    ; FOR i := 1 TO TokenLength 
      DO Word . Chars [ VAL ( i , Strings . tStringIndex ) ] 
           := yyToLower [ yyChBufferPtr ^ [ WordStart + i ] ] 
      END (* FOR *) 
    ; Word . Length := VAL ( TokenLength , SHORTCARD ) 
    END GetLower 

; PROCEDURE GetUpper ( VAR Word : Strings . tString ) 

  = VAR i , WordStart : INTEGER 

  ; BEGIN (* GetUpper *) 
      WordStart := yyChBufferIndex - TokenLength - 1 
    ; FOR i := 1 TO TokenLength 
      DO Word . Chars [ VAL ( i , Strings . tStringIndex ) ] 
           := yyToUpper [ yyChBufferPtr ^ [ WordStart + i ] ] 
      END (* FOR *) 
    ; Word . Length := VAL ( TokenLength , SHORTCARD ) 
    END GetUpper 

; PROCEDURE yyStart ( State : yyStateRange ) 

  = BEGIN (* yyStart *) 
      yyPreviousStart := yyStartState 
    ; yyStartState := State 
    END yyStart 

; PROCEDURE yyPrevious ( ) 

  = VAR s : yyStateRange 

  ; BEGIN (* yyPrevious *) 
      s := yyStartState 
    ; yyStartState := yyPreviousStart 
    ; yyPreviousStart := s 
    END yyPrevious 

; PROCEDURE yyEcho ( ) 

  = VAR i : INTEGER 

  ; BEGIN (* yyEcho *) 
      FOR i := yyChBufferIndex - TokenLength TO yyChBufferIndex - 1 
      DO ReuseIO . WriteC ( ReuseIO . StdOutput , yyChBufferPtr ^ [ i ] ) 
      END (* FOR *) 
    END yyEcho 

; PROCEDURE yyLess ( n : INTEGER ) 

  = BEGIN (* yyLess *) 
      DEC ( yyChBufferIndex , TokenLength - n )
    ; TokenLength := n 
    END yyLess 

; PROCEDURE yyTab ( ) 

  = BEGIN (* yyTab *) 
      DEC 
        ( yyLineStart 
        , yyTabSpace 
          - 1 
          - ( ( yyChBufferIndex - yyLineStart - 2 ) MOD yyTabSpace ) 
        ) 
    END yyTab 

; PROCEDURE yyTab1 ( a : INTEGER ) 

  = BEGIN (* yyTab1 *) 
      DEC 
        ( yyLineStart 
        , yyTabSpace 
          - 1 
          - ( ( yyChBufferIndex - yyLineStart - TokenLength + a - 1 ) 
              MOD yyTabSpace 
            ) 
        ) 
    END yyTab1 

; PROCEDURE yyTab2 ( a , b : INTEGER ) 

  = BEGIN (* yyTab2 *) 
      DEC 
        ( yyLineStart 
        , yyTabSpace 
          - 1 
          - ( ( yyChBufferIndex - yyLineStart - TokenLength + a - 1 ) 
              MOD yyTabSpace 
            ) 
        ) 
    END yyTab2 

; PROCEDURE yyEol ( Column : INTEGER ) 

  = BEGIN (* yyEol *) 
      INC ( yyLineCount ) 
    ; INC ( yyTotalLineCount ) 
    ; yyLineStart := yyChBufferIndex - 1 - Column 
    END yyEol 

; PROCEDURE output ( c : CHAR ) 

  = BEGIN (* output *) 
      ReuseIO . WriteC ( ReuseIO . StdOutput , c ) 
    END output 

; PROCEDURE unput ( c : CHAR ) 

  = BEGIN (* unput *) 
      DEC ( yyChBufferIndex ) 
    ; yyChBufferPtr ^ [ yyChBufferIndex ] := c 
    END unput 

; PROCEDURE input ( ) : CHAR 

  = BEGIN (* input *) 
      IF yyChBufferIndex = ( yyChBufferStart + yyBytesRead ) 
      THEN 
        IF NOT yyEof 
        THEN 
          DEC ( yyLineStart , yyBytesRead ) 
        ; DEC ( yyLineStart , yyChBufferStart ) (* RMB *) 
        ; yyChBufferIndex := 0 
        ; yyChBufferStart := 0 
        ; yyBytesRead 
           := Source . GetLine 
                 ( yySourceFile 
                 , yyChBufferPtr 
                 , General . Exp2 ( General . Log2 ( yyChBufferSize ) ) 
                 ) 
        ; IF yyBytesRead <= 0 
          THEN 
            yyBytesRead := 0 
          ; yyEof := TRUE 
          END (* IF *) 
        ; yyChBufferPtr ^ [ yyBytesRead ] := yyEobCh 
        ; yyChBufferPtr ^ [ yyBytesRead + 1 ] := '\000' 
        END (* IF *) 
      END (* IF *) 
    ; IF yyChBufferIndex = ( yyChBufferStart + yyBytesRead ) 
      THEN 
        RETURN '\000' 
      ELSE 
        INC ( yyChBufferIndex ) 
      ; RETURN yyChBufferPtr ^ [ yyChBufferIndex - 1 ] 
      END (* IF *) 
    END input 

(* VISIBLE: *) 
; PROCEDURE UpperCase ( Ch : CHAR ) : CHAR 

  = BEGIN (* UpperCase *) 
      RETURN yyToUpper [ Ch ] 
    END UpperCase 

(* VISIBLE: *) 
; PROCEDURE LowerCase ( Ch : CHAR ) : CHAR 

  = BEGIN (* LowerCase *) 
      RETURN yyToLower [ Ch ] 
    END LowerCase 

(* VISIBLE *) 
; PROCEDURE TotalLineCount ( ) : CARDINAL  

  = BEGIN (* TotalLineCount *) 
      RETURN yyTotalLineCount 
    END TotalLineCount 

; PROCEDURE BeginScanner ( ) 

  = BEGIN (* BeginScanner *)
(* User initialization code ($I): *)
(* line 126 "rexm3.rex" *)
   BraceNestingLevel := 0 
    ; CommentNestingLevel := 0 
    ; AssignEmpty (string) 
    ; NoString := PutString (string) 
  
(* End of line 126 "rexm3.rex" *)
(* End of user initialization code ($I): *)
    END BeginScanner 

; PROCEDURE CloseScanner ( ) 

  = BEGIN (* CloseScanner *) 
(* User finalization code ($F): *)
(* End of user finalization code ($F): *)
    END CloseScanner

(* From hand edited version, with $M lines inserted: *)
; PROCEDURE yyGetTables ( ) 

  = VAR BlockSize , j , n : Word . T 
    ; TableFile : System . tFile 
    ; Base : ARRAY yyStateRange OF yyTableRange 

  ; BEGIN (* yyGetTables *) 
      BlockSize := 64000 DIV BYTESIZE ( yyCombType )
    ; TRY 
        TableFile := System . OpenInputT ( ScanTabName ) 
      EXCEPT 
        OSError . E ( code ) 
        => RexErrors . ErrLine
             ( "Unable to open scanner table file " & ScanTabName ) 
        ; Process . Exit ( RexErrors . AbnormalTermination )  
      END (* EXCEPT *) 
    ; Checks . ErrorCheckT ( "Unable to open " & ScanTabName , TableFile ) 
    ; IF ( ( yyGetTable ( TableFile , ADR ( Base [ FIRST ( Base ) ] ) ) 
             DIV BYTESIZE ( yyTableElmt ) 
             - 1 
           ) 
           # yyDStateCount 
         ) 
         OR ( ( yyGetTable 
                  ( TableFile , ADR ( yyDefault [ FIRST ( yyDefault ) ] ) ) 
                DIV BYTESIZE ( yyTableElmt ) 
                - 1 
              ) 
              # yyDStateCount 
            ) 
         OR ( ( yyGetTable 
                  ( TableFile , ADR ( yyEobTrans [ FIRST ( yyEobTrans ) ] ) ) 
                DIV BYTESIZE ( yyTableElmt ) 
                - 1 
              ) 
              # yyDStateCount 
            ) 
(* Only for ReduceCaseSize ($M): *)
(* End of only for ReduceCaseSize ($M): *)
      THEN 
        yyErrorMessage ( 2 ) 
      END (* IF *) 
    ; n := 0 
    ; j := 0 

    ; WHILE j <= yyTableSize 
      DO INC 
           ( n 
           , yyGetTable 
               ( TableFile , ADR ( yyComb [ VAL ( j , SHORTCARD ) ] ) ) 
             DIV BYTESIZE ( yyCombType ) 
           ) 
      ; INC ( j , BlockSize ) 
      END (* WHILE *) 
    ; IF n # ( yyTableSize + 1 ) THEN yyErrorMessage ( 2 ) END (* IF *) 
    ; System . Close ( TableFile ) 

    ; FOR i := 0 TO yyDStateCount 
      DO yyBasePtr [ i ] 
           := LOOPHOLE ( ADR ( yyComb [ Base [ i ] ] ) , M2LONGCARD ) 
      END (* FOR *) 
    END yyGetTables 

(* Directly converted version: lacks manual fixes: 
; PROCEDURE yyGetTables ( ) 

  = VAR BlockSize , j , n : Word . T 
    ; TableFile : System . tFile 
    ; i : yyStateRange 
    ; Base : ARRAY yyStateRange OF yyTableRange 

  ; BEGIN (* yyGetTables *) 
      BlockSize := 64000 DIV BYTESIZE ( yyCombType ) 
    ; TableFile := System . OpenInputT ( ScanTabName ) 
    ; Checks . ErrorCheckT
        ( "Unable to open scanner table file " & ScanTabName, TableFile ) 
    ; IF ( ( yyGetTable 
               ( TableFile , ADR ( Base [ FIRST ( Base ) ] ) ) 
             DIV BYTESIZE ( yyTableElmt ) 
             - 1 
           ) 
           # yyDStateCount 
         ) 
         OR ( ( yyGetTable 
                  ( TableFile 
                  , ADR ( yyDefault [ FIRST ( yyDefault ) ] ) 
                  ) 
                DIV BYTESIZE ( yyTableElmt ) 
                - 1 
              ) 
              # yyDStateCount 
            ) 
         OR ( ( yyGetTable 
                  ( TableFile 
                  , ADR ( yyEobTrans [ FIRST ( yyEobTrans ) ] ) 
                  ) 
                DIV BYTESIZE ( yyTableElmt ) 
                - 1 
              ) 
              # yyDStateCount 
            ) 
(* Only for ReduceCaseSize ($M): *)
(* End of only for ReduceCaseSize ($M): *)
      THEN 
        yyErrorMessage ( 2 ) 
      END (* IF *) 
    ; n := 0 
    ; j := 0 
    ; WHILE j <= yyTableSize 
      DO INC 
           ( n 
           , yyGetTable 
               ( TableFile 
               , ADR ( yyComb [ VAL ( j , SHORTCARD ) ] ) 
               ) 
             DIV BYTESIZE ( yyCombType ) 
           ) 
      ; INC ( j , BlockSize ) 
      END (* WHILE *) 
    ; IF n # ( yyTableSize + 1 ) THEN yyErrorMessage ( 2 ) END (* IF *) 
    ; System . Close ( TableFile ) 

    ; FOR i := 0 TO yyDStateCount 
      DO yyBasePtr [ i ] 
           := LOOPHOLE ( ADR ( yyComb [ Base [ i ] ] ) , M2LONGCARD ) 
      END (* FOR *) 
    END yyGetTables
  End of directly converted version. *)

; PROCEDURE yyGetTable 
    ( TableFile : System . tFile ; Address : ADDRESS ) : Word . T 

  = VAR N : INTEGER 
    ; Length : yyTableElmt 
    ; LongLength : Word . T 

  ; BEGIN (* yyGetTable *) 
      N := System . Read 
             ( TableFile , ADR ( Length ) , BYTESIZE ( yyTableElmt ) ) 
    ; Checks . ErrorCheckT
        ( "Unable to read size in scanner table file " & ScanTabName , N )  
    ; IF N < 0 
      THEN 
        Process . Exit ( RexErrors . AbnormalTermination ) 
      END (* IF *) 
    ; LongLength := Length 
    ; N := System . Read ( TableFile , Address , LongLength ) 
    ; Checks . ErrorCheckT
        ( "Unable to read data in scanner table file " & ScanTabName , N )  
    ; IF N < 0 
      THEN 
        Process . Exit ( RexErrors . AbnormalTermination ) 
      END (* IF *) 
    ; RETURN LongLength 
    END yyGetTable 

; PROCEDURE yyErrorMessage ( ErrorCode : SHORTCARD ) 

  = BEGIN (* yyErrorMessage *) 
      Positions . WritePosition ( ReuseIO . StdError , Attribute . Position ) 
    ; CASE ErrorCode 
      OF 0 
      => ReuseIO . WriteT 
        ( ReuseIO . StdError , ": " & "Scanner" & ": internal error" ) 
      | 1 
      => ReuseIO . WriteT 
        ( ReuseIO . StdError , ": " & "Scanner" & ": out of memory" ) 
      | 2 
      => ReuseIO . WriteT 
        ( ReuseIO . StdError , ": " & "Scanner" & ": table mismatch" ) 
      | 3 
      => ReuseIO . WriteT 
           ( ReuseIO . StdError 
        , ": " & "Scanner" & ": too many nested include files"
           ) 
      | 4 
      => ReuseIO . WriteT 
           ( ReuseIO . StdError 
        , ": " & "Scanner" & ": file stack underflow (too many calls of CloseFile)"
           ) 
      | 5 
      => ReuseIO . WriteT 
           ( ReuseIO . StdError 
        , ": " & "Scanner" & ": unable to open input file. "
           ) 
      END (* CASE *) 
    ; ReuseIO . WriteNl ( ReuseIO . StdError ) 
    ; Exit ( ) 
    END yyErrorMessage 

; PROCEDURE yyExit ( ) 

  = BEGIN (* yyExit *) 
      ReuseIO . CloseIO ( ) 
    ; System . Exit ( 1 ) 
    END yyExit 

; BEGIN (* Name *)
    ScanTabName := "Scanner.Tab" 
  ; Exit := yyExit 
  ; yyFileStackPtr := 0 
  ; yyStartState := 1 (* set up for auto init *) 
  ; yyPreviousStart := 1 
  ; yyBasePtr [ yyStartState ] 
      := LOOPHOLE ( ADR ( yyComb [ 0 ] ) , M2LONGCARD ) 
  ; yyDefault [ yyStartState ] := yyDNoState 
  ; yyComb [ 0 ] . Check := yyDNoState 
  ; yyChBufferPtr := LOOPHOLE ( ADR ( yyComb [ 0 ] ) , yytChBufferPtr ) 
  ; yyChBufferIndex := 1 (* dirty trick *) 
  ; yyStateStackSize := yyInitBufferSize 
  ; DynArray . MakeArray 
      ( LOOPHOLE ( yyStateStack , ADDRESS ) 
      , yyStateStackSize 
      , BYTESIZE ( yyStateRange ) 
      ) 
(* FIXME:              ^ *) 
  ; yyStateStack ^ [ 0 ] := yyDNoState 

  ; FOR yyCh := yyFirstCh TO yyLastCh 
    DO yyToLower [ yyCh ] := yyCh 
    END (* FOR *) 
  ; yyToUpper := yyToLower 
  ; FOR yyCh := 'A' TO 'Z' 
    DO yyToLower [ yyCh ] 
         := VAL ( ORD ( yyCh ) - ORD ( 'A' ) + ORD ( 'a' ) , CHAR ) 
    END (* FOR *) 
  ; FOR yyCh := 'a' TO 'z' 
    DO yyToUpper [ yyCh ] 
         := VAL ( ORD ( yyCh ) - ORD ( 'a' ) + ORD ( 'A' ) , CHAR ) 
    END (* FOR *) 
END Scanner 
. 

