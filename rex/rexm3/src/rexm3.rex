
EXPORT  {

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

} 

GLOBAL  {

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
}

LOCAL   
  {
  ; VAR TargetCode , String , Word : tString 

  ; PROCEDURE AccumComment ( ) 

    = BEGIN (* AccumComment *) 
        IF InsideTarget AND ( BraceNestingLevel > 0 ) 
        THEN 
          GetWord ( Word ) 
        ; Concatenate ( TargetCode , Word ) 
        END (* IF *) 
      END AccumComment 
  }

BEGIN   
  {   BraceNestingLevel := 0 
    ; CommentNestingLevel := 0 
    ; AssignEmpty (string) 
    ; NoString := PutString (string) 
  }

EOF     
{
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
}

DEFINE
   letter       = {A-Z a-z}     .
   digit        = {0-9}         .
   string       = - {"\n}       .
   CCmtCh       = - {*\t\n}     .
   M2CmtCh      = - {*(\t\n}    .
   code         = - {\\\t\n{\}'"(/} .
   StrCh1       = - {'\t\n}     .
   StrCh2       = - {"\t\n}     .
   CStrCh1      = - {'\t\n\\}   .
   CStrCh2      = - {"\t\n\\}   .

START targetcode, set, rules, CComment, M2Comment, Str1, Str2, CStr1, CStr2

RULES

/* Target code: */ 

#targetcode#    "{"     : {
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
                        }

#targetcode#    "}"     :- {
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
                            } 

#targetcode#    code +  | "(" | "/" 
                     :- {
              IF BraceNestingLevel > 0 
              THEN 
                GetWord ( Word ) 
              ; Concatenate ( TargetCode , Word ) 
              END (* IF *) 

                        }

#targetcode#    \t      :- {
               IF BraceNestingLevel > 0 
               THEN 
                 Strings . Append ( TargetCode , '\011' ) 
               END (* IF *) 
            ; yyTab ( ) 

                           }

#targetcode#    \n      :- {
               IF BraceNestingLevel > 0 
               THEN 
                 Append ( Attribute . Text , TargetCode ) 
               ; AssignEmpty ( TargetCode ) 
               END (* IF *) 
            ; yyEol ( 0 ) 
                           }

#targetcode#    \\ ANY  :- {
               IF BraceNestingLevel > 0 
               THEN 
                 GetWord ( Word ) 
               ; Strings . Append ( TargetCode , Char ( Word , 2 ) ) 
               END (* IF *) 
                           }

#targetcode#    \\      :- {
               IF BraceNestingLevel > 0 
               THEN 
                 Strings . Append ( TargetCode , '\\' ) 
               END (* IF *) 
                           }

/* Strings: */ 

#targetcode#    '       : {
            ; GetWord ( String ) 
            ; StringPos := Attribute . Position 
            ; IF Language = tLanguage . C 
              THEN yyStart ( CStr1 )
              ELSE yyStart ( Str1 ) 
              END (* IF *) 
                          }

#targetcode#    \"      : {
            ; GetWord ( String ) 
            ; StringPos := Attribute . Position 
            ; IF Language = tLanguage . C 
              THEN yyStart ( CStr2 ) 
              ELSE yyStart ( Str2 ) 
              END (* IF *) 
                          }

#Str1#  StrCh1 +        ,
#Str2#  StrCh2 +        ,
#CStr1# CStrCh1 + | \\ ANY ? ,
#CStr2# CStrCh2 + | \\ ANY ? :- { GetWord (Word)
                                  ; Concatenate (String, Word)
                                }

#CStr1# \\ \n           ,
#CStr2# \\ \n           :- {   GetWord (Word)
                             ; Concatenate (String, Word)
                             ; yyEol (0)
                           }

#Str1, CStr1# '         ,
#Str2, CStr2# \"        :- {Strings.Append (String, Char (String, 1))
                            ; yyPrevious ( ) 
                            ; Concatenate (TargetCode, String)
                        }

#Str1, Str2, CStr1, CStr2# \t :- {   Strings.Append ( String , '\011' )
                                   ; yyTab ( ) 
                                 }

#Str1, Str2, CStr1, CStr2# \n :-
                        {    ErrorMessage ( UnclosedString , Error , StringPos )
                           ; Strings.Append ( String , Char ( String , 1 ) )
                           ; yyEol ( 0 )
                           ; yyPrevious  ( )
                           ; Concatenate ( TargetCode , String ) 
                        }

/* Modula2-style comments: */ 

#STD, rules, targetcode#        "(*"    
  :  {
            ; yyStart ( M2Comment ) 
            ; AccumComment ( ) 
            ; CommentNestingLevel := 1 
            ; CommentPos := Attribute . Position 
     }

#M2Comment#     "(*"    :- { INC ( CommentNestingLevel ) ; AccumComment ( ) }

#M2Comment#     "*)"    :- {

               AccumComment ( ) 
            ; DEC ( CommentNestingLevel ) 
            ; IF CommentNestingLevel = 0 THEN yyPrevious ( ) END (* IF *) 
                           }

#M2Comment#     "*" | "(" | M2CmtCh +   :- { AccumComment ( ) }

/* C-style comments: */ 

#STD, rules, targetcode#        "/*"    
  :  {
            ; yyStart ( CComment ) 
            ; AccumComment ( ) 
            ; CommentPos := Attribute . Position 
     }

#CComment#      "*/"    :- { AccumComment ( ) ; yyPrevious ( ) }

#CComment#      "*" | CCmtCh +  :- { AccumComment ( ) }

/* Inside both styles of comments: */ 

#M2Comment, CComment#   
              \t     :- {
               IF InsideTarget AND ( BraceNestingLevel > 0 ) 
               THEN 
                 Strings . Append ( TargetCode , '\011' ) 
               END (* IF *) 
            ; yyTab ( ) 
                        }

#M2Comment, CComment#   
              \n     :- {
               IF InsideTarget AND ( BraceNestingLevel > 0 ) 
               THEN 
                 Append ( Attribute . Text , TargetCode ) 
               ; AssignEmpty ( TargetCode ) 
               END (* IF *) 
            ; yyEol ( 0 ) 
                        }

#STD#           EXPORT  : {; PrevState := STD; yyStart (targetcode); RETURN SymExport     } 
#STD#           GLOBAL  : {; PrevState := STD; yyStart (targetcode); RETURN SymGlobal     } 
#STD#           LOCAL   : {; PrevState := STD; yyStart (targetcode); RETURN SymLocal      } 
#STD#           BEGIN   : {; PrevState := STD; yyStart (targetcode); RETURN SymBegin      } 
#STD#           CLOSE   : {; PrevState := STD; yyStart (targetcode); RETURN SymClose      } 
#STD#           DEFAULT : {; PrevState := STD; yyStart (targetcode); RETURN SymDefault    } 
#STD#           EOF     : {; PrevState := STD; yyStart (targetcode); RETURN SymEof        } 
#STD#           SCANNER : {; RETURN SymScanner    } 
#STD#           DEFINE  : {; RETURN SymDefine     } 
#STD#           START   : {; RETURN SymStart      } 
#STD#           RULE S ?: {; yyStart (rules);     RETURN SymRules         } 
#rules#         \NOT    : {; RETURN SymNot        } 

#STD, rules#    letter (letter | digit | _) * : {
            ; GetWord ( Word ) 
            ; Attribute . Ident := MakeIdent ( Word ) 
            ; RETURN SymIdent 
                        }

#STD, rules#    digit + : {
            ; GetWord ( Word ) 
            ; Attribute . Number := StringToInt ( Word ) 
            ; RETURN SymNumber 
                        }

#STD, rules#    \" string * \" : {
            ; GetWord ( Word ) 
            ; SubString ( Word , 2 , Length ( Word ) - 1 , TargetCode ) 
            ; Attribute . String := PutString ( TargetCode ) 
            ; RETURN SymString 
                        }

#STD#           "."     : {; RETURN SymDot        } 
#STD#           "="     : {; RETURN SymEqual      } 
#STD, set#      "}"     : {; yyPrevious ( ) ; RETURN SymRBrace        } 
#STD, set, rules# "-"   : {; RETURN SymMinus      } 
#STD, rules#    ","     : {; RETURN SymComma      } 
#STD, rules#    "|"     : {; RETURN SymBar        } 
#STD, rules#    "+"     : {; RETURN SymPlus       } 
#STD, rules#    "*"     : {; RETURN SymAsterisk   } 
#STD, rules#    "?"     : {; RETURN SymQuestion   } 
#STD, rules#    "("     : {; RETURN SymLParen     } 
#STD, rules#    ")"     : {; RETURN SymRParen     } 
#STD, rules#    "["     : {; RETURN SymLBracket   } 
#STD, rules#    "]"     : {; RETURN SymRBracket   } 
#STD, rules#    "{"     : {; yyStart (set);       RETURN SymLBrace        } 
#rules#         "#"     : {; RETURN SymNrSign     } 
#rules#         "/"     : {; RETURN SymSlash      } 
#rules#         "<"     : {; RETURN SymLess       } 
#rules#         ">"     : {; RETURN SymGreater    } 
#rules#         ":"     : {; PrevState := rules; yyStart (targetcode); RETURN SymColon} 
#rules#         ":-"    : {; PrevState := rules; yyStart (targetcode); RETURN SymColonMinus} 

#STD, set, rules# \\ n  : {; Attribute.Ch := '\012' ;  RETURN SymChar} 
#STD, set, rules# \\ t  : {; Attribute.Ch := '\011' ; RETURN SymChar} 
#STD, set, rules# \\ v  : {; Attribute.Ch := '\013' ; RETURN SymChar} 
#STD, set, rules# \\ b  : {; Attribute.Ch := '\010' ; RETURN SymChar} 
#STD, set, rules# \\ r  : {; Attribute.Ch := '\015' ; RETURN SymChar} 
#STD, set, rules# \\ f  : {; Attribute.Ch := '\014' ; RETURN SymChar} 

#STD, set, rules# \\ digit + : {
            ; GetWord ( Word ) 
            ; SubString ( Word , 2 , Length ( Word ) , TargetCode ) 
            ; Attribute . Ch := VAL ( StringToInt ( TargetCode ) , CHAR ) 
            ; RETURN SymChar 
                        }

#STD, set, rules# \\ ANY : {
            ; GetWord ( Word ) 
            ; Attribute . Ch := Char ( Word , 2 ) 
            ; RETURN SymChar 
                        }

#STD, set, rules# - {\t\n\ \f\r} : {
            ; GetWord ( Word ) 
            ; Attribute . Ch := Char ( Word , 1 ) 
            ; RETURN SymChar 
                        }

\f                      :- { EVAL Word (* Because ";" will follow. *) }
\r                      :- { EVAL Word (* Because ";" will follow. *) }


