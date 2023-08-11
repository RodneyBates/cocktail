/* $Id: input.rex,v 2.4 1992/10/13 16:05:28 grosch rel $ */

/* Rodney M. Bates 
   RMB Oct 96 - Changed to scan comments inside target code blocks properly.
                (previously, a quote inside a comment inside target
                 code gave a spurious "unclosed string" message.) 
              - Plus various minor improvements to be more consistent with
                other scanners in the Cocktail suite. 
              - Also make all tokens recognized in one of states 
                STD, token, rule recognized in all of these states, to 
                make many errors come out as syntax errors rather than 
                scanner unrecognized character messsages. 
   RMB July 1999 Fixed bug computing position of C-style comments. 
*/ 

/* $Log: input.rex,v $
 * Revision 2.4  1992/10/13  16:05:28  grosch
 * generate # line properly in case of strings in actions
 *
 * Revision 2.3  1992/08/07  15:15:11  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.2  1991/12/04  16:21:41  grosch
 * unified escape conventions for all tools
 *
 * Revision 2.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:26:49  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.3  90/06/11  18:47:51  grosch
 * allow keywords as token names, layout improvements
 * 
 * Revision 1.2  88/12/16  15:03:42  vielsack
 * identifier may now start with backslash ('\') which isn't significant
 * this can be used to define identifiers which are keywords
 * 
 * Revision 1.1  88/10/20  08:51:24  vielsack
 * use tScanAttribute instead of tAttribute
 * 
 * Revision 1.0  88/10/04  14:27:33  vielsack
 * Initial revision
 * 
 */

EXPORT  {

FROM StringMem  IMPORT tStringRef;
FROM Idents     IMPORT tIdent;
FROM Rules      IMPORT Expression;
FROM Lists      IMPORT tList;
FROM Positions  IMPORT tPosition;

TYPE
   AttributeMode = (Keys, Comment, Number, Action, Symbol, Coding, PrioPart, RightSide, Empty);

   tScanAttribute=
      RECORD
         Position: tPosition;
         CASE Mode: AttributeMode OF
         | Comment: Comm        : tList;
         | Number: Value        : CARDINAL;
         | Action: Act  : tList;
         | Symbol: Sym  : tIdent;
         | Coding:
             HasCoding  : BOOLEAN ;
             CodNumbPos : tPosition;
             CodValue   : CARDINAL;
         | PrioPart,
           RightSide:
             Expr:  Expression;
             CASE HasPrio: BOOLEAN OF
               TRUE:
                 PriSym : tIdent;
                 PriSymPos      : tPosition;
             END;
         END;
      END;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attr: tScanAttribute);
}

GLOBAL  {

FROM SYSTEM     IMPORT ADR, ADDRESS;
FROM Strings    IMPORT tString, ArrayToString, Concatenate, 
                       SubString, AssignEmpty, Assign, Char, Length;
FROM StringMem  IMPORT tStringRef, PutString;
FROM Idents     IMPORT MakeIdent;
FROM Lists      IMPORT tList, Append, MakeList;
FROM Limits     IMPORT MaxShortCard;
FROM WriteTok   IMPORT tLanguage, Language;
FROM Errors     IMPORT eWarning, eError, eCharacter, eString, 
                       ErrorMessage, ErrorMessageI;
FROM Positions  IMPORT tPosition;

FROM FrontErrors IMPORT 
  eEolString, eUnClAction, eUnClComment, eUnClString, eCharIgnored;

  SymNull       =  0;
  SymEqual      =  1;
  SymColon      =  2;
  SymPoint      =  3;
  SymOr         =  4;
  SymStar       =  5;
  SymPlus       =  6;
  SymList       =  7;
  SymLBrace     =  8;
  SymRBrace     =  9;
  SymLBracket   = 10;
  SymRBracket   = 11;
  SymEXPORT     = 12;
  SymGLOBAL     = 13;
  SymLOCAL      = 14;
  SymBEGIN      = 15;
  SymCLOSE      = 16;
  SymTOKEN      = 17;
  SymOPER       = 18;
  SymNONE       = 19;
  SymLEFT       = 20;
  SymRIGHT      = 21;
  SymRULE       = 22;
  SymPREC       = 23;
  SymComment    = 24; (* Schreibweise wie in MODULA-2           *)
  SymNumber     = 25; (* vorzeichenlose ganze Zahl              *)
  SymAction     = 26; (* in '{' und '}' eingeschlossene Aktion  *)
  SymIdentifier = 27; (* letter (digit | letter) *              *)
  SymString     = 28; (* durch "'" oder '"' begrenzte Zeichenkette *)
  SymScanner    = 29;
  SymParser     = 30;

VAR BraceNestingLevel , CommentNestingLevel : INTEGER; 
VAR CommentPos , StringPos , CodePos : tPosition;
VAR InsideCode : BOOLEAN ; 

PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attr: tScanAttribute);
  VAR s : tString;
  BEGIN
    CASE Token OF
      SymNull : ;
    | SymEqual..SymPREC 
      : Attr.Mode       := Keys;
    | SymComment        
      : Attr.Mode       := Comment;
        MakeList (Attr.Comm);
    | SymNumber         
      : Attr.Mode       := Number;
        Attr.Value:= MaxShortCard;
    | SymAction
      : Attr.Mode       := Action;
        MakeList (Attr.Act);
    | SymIdentifier , SymString 
      : Attr.Mode       := Symbol;
        ArrayToString ('-error-', s);
        Attr.Sym        := MakeIdent (s);
    END;
  END ErrorAttribute;

PROCEDURE GetNumber (VAR Word: tString): CARDINAL;
  VAR i, n, d : CARDINAL;
   BEGIN
      i := 0;
      n := 0;
      WHILE i < Length (Word) DO
        i := i+1;
        d := (ORD(Char (Word, i))-ORD('0'));
        IF (n > MaxShortCard DIV 10) OR (n*10 > MaxShortCard - d) THEN
          RETURN MaxShortCard;
        END;
        n := n*10 + d;
      END;
      RETURN n;
   END GetNumber;
}

LOCAL   
  { VAR Word, String, LastWord: tString; c: CHAR; PrevState: SHORTCARD; 
  }

EOF     
  {
    CASE yyStartState OF
    | code                      
        : ErrorMessage (eUnClAction , eError, CodePos );
    | comment, comment2 
        : ErrorMessage (eUnClComment, eError, CommentPos ); 
          IF InsideCode 
          THEN
            ErrorMessage (eUnClAction , eError, CodePos );
          END (* IF *) 
    | Str1, Str2, CStr1, CStr2
        : ErrorMessage (eUnClString, eError, StringPos );
          IF InsideCode 
          THEN
            ErrorMessage (eUnClAction , eError, CodePos );
          END (* IF *) 
    ELSE
    END;
  }

BEGIN
  { BraceNestingLevel := 0 ; CommentNestingLevel := 0 ; 
    InsideCode := FALSE ; 
  }

DEFINE
  digit         = {0-9}         .
  letter        = {a-z A-Z _}   .
  cmt           = - {*(\t\n}    .
  cmt2          = - {*\t\n}     .
  codechar      = - {\\{\}\t\n'"(/} .
  StrCh1        = - {'\t\n}     .
  StrCh2        = - {"\t\n}     .
  CStrCh1       = - {'\t\n\\}   .
  CStrCh2       = - {"\t\n\\}   .

START token, rule, code, Str1, Str2, CStr1, CStr2, comment, comment2

RULES

/* These were #token#: */

#STD, token, rule#      "="     : { Attribute.Mode := Keys; RETURN SymEqual     ; }
#STD, token, rule#      OPER    : { Attribute.Mode := Keys; RETURN SymOPER      ; }
#STD, token, rule#      NONE    : { Attribute.Mode := Keys; RETURN SymNONE      ; }
#STD, token, rule#      LEFT    : { Attribute.Mode := Keys; RETURN SymLEFT      ; }
#STD, token, rule#      RIGHT   : { Attribute.Mode := Keys; RETURN SymRIGHT     ; }
#STD, token, rule#      RULE    : { Attribute.Mode := Keys; yyStart (rule); RETURN SymRULE      ; }
#STD, token, rule#      digit + :
{
  Attribute.Mode := Number;
  GetWord (Word);
  Attribute.Sym := MakeIdent (Word);
  Attribute.Value := GetNumber (Word);
  RETURN SymNumber;
}


/* These were #rule#: */ 

#STD, token, rule#      ":"     : { Attribute.Mode := Keys; RETURN SymColon     ; }
#STD, token, rule#      "."     : { Attribute.Mode := Keys; RETURN SymPoint     ; }
#STD, token, rule#      "|"     : { Attribute.Mode := Keys; RETURN SymOr        ; }
#STD, token, rule#      "*"     : { Attribute.Mode := Keys; RETURN SymStar      ; }
#STD, token, rule#      "+"     : { Attribute.Mode := Keys; RETURN SymPlus      ; }
#STD, token, rule#      "||"    : { Attribute.Mode := Keys; RETURN SymList      ; }
#STD, token, rule#      "("     : { Attribute.Mode := Keys; RETURN SymLBrace    ; }
#STD, token, rule#      ")"     : { Attribute.Mode := Keys; RETURN SymRBrace    ; }
#STD, token, rule#      "["     : { Attribute.Mode := Keys; RETURN SymLBracket  ; }
#STD, token, rule#      "]"     : { Attribute.Mode := Keys; RETURN SymRBracket  ; }
#STD, token, rule#      PREC    : { Attribute.Mode := Keys; RETURN SymPREC      ; }

/* These were #STD#: */ 

#STD, token, rule#      \SCANNER: { Attribute.Mode := Keys; RETURN SymScanner   ; }
#STD, token, rule#      \PARSER : { Attribute.Mode := Keys; RETURN SymParser    ; }
#STD, token, rule#      \EXPORT : { Attribute.Mode := Keys; RETURN SymEXPORT    ; }
#STD, token, rule#      \GLOBAL : { Attribute.Mode := Keys; RETURN SymGLOBAL    ; }
#STD, token, rule#      \LOCAL  : { Attribute.Mode := Keys; RETURN SymLOCAL     ; }
#STD, token, rule#      \BEGIN  : { Attribute.Mode := Keys; RETURN SymBEGIN     ; }
#STD, token, rule#      \CLOSE  : { Attribute.Mode := Keys; RETURN SymCLOSE     ; }
#STD, token, rule#      TOKEN   : { Attribute.Mode := Keys; yyStart (token); RETURN SymTOKEN    ; }



#STD, token, rule#      \\ letter (letter | digit) *    :
{
  Attribute.Mode := Keys;
  GetWord (Word);
  SubString (Word, 2, Length (Word), String);
  Attribute.Sym := MakeIdent (String);
  RETURN SymIdentifier;
}

#STD, token, rule#      letter (letter | digit) *       :
{
  Attribute.Mode := Keys;
  GetWord (Word);
  Attribute.Sym := MakeIdent (Word);
  RETURN SymIdentifier;
}

#STD, token, rule# \f | \r :- {}

#STD, token, rule#      - {\t\n\ {'"}      :
{
  GetWord (Word);
  c := Char (Word, 1);
  ErrorMessageI (eCharIgnored, eWarning, Attribute.Position, eCharacter, ADR (c));
}

/* Target code */ 

#STD, token, rule#     "{"     :
{
  PrevState := yyStartState;
  CodePos := Attribute.Position;
  yyStart (code);
  InsideCode := TRUE; 
  GetWord (LastWord);
  Attribute.Mode := Action;
  MakeList (Attribute.Act);
  BraceNestingLevel := 1;
}

#code#  \\ ANY | "(" | "/" | codechar + :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#code#  \\      :
{
  c := '\';
  ErrorMessageI (eCharIgnored, eWarning, Attribute.Position, eCharacter, ADR (c));
}

#code#  \t      :-
{
  yyTab;
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#code#  \n      :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  Append (Attribute.Act, ADDRESS (PutString (LastWord)));
  AssignEmpty (LastWord);
  yyEol (0);
}

#code#  "{"     :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  INC (BraceNestingLevel);
}

#code#  "}"     :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  DEC (BraceNestingLevel);
  IF BraceNestingLevel = 0 THEN
    yyStart (PrevState);
    Attribute.Position := CodePos;
    Append (Attribute.Act, ADDRESS (PutString (LastWord)));
    InsideCode := FALSE; 
    RETURN SymAction;
  END;
}

/* Strings */ 

#STD, token, rule, code# '      
  : { GetWord (String);
      StringPos := Attribute.Position; 
      IF Language = C
      THEN yyStart (CStr1);
      ELSE yyStart (Str1);
      END;
    }

#STD, token, rule, code# \"     
  : { GetWord (String);
      StringPos := Attribute.Position; 
      IF Language = C
      THEN yyStart (CStr2);
      ELSE yyStart (Str2);
      END;
    }

#Str1#  StrCh1  + | \'\'        ,
#Str2#  StrCh2  + | \"\"        ,
#CStr1# CStrCh1 + | \\ ANY ?    ,
#CStr2# CStrCh2 + | \\ ANY ? 
  :- {GetWord (Word); Concatenate (String, Word);}

#CStr1, CStr2#  \\ \n   :- {GetWord (Word); Concatenate (String, Word); yyEol (0);}

#Str1, CStr1# '         ,
#Str2, CStr2# \"        
  :- { Strings.Append (String, Char (String, 1));
       yyPrevious;
       IF InsideCode THEN
         Concatenate (LastWord, String);
       ELSE
         Attribute.Mode := Symbol;
         Attribute.Sym := MakeIdent (String);
         RETURN SymString;
       END;
     }

#Str1, Str2, CStr1, CStr2# \t 
  :- {Strings.Append (String, 11C); yyTab;}

#Str1, Str2, CStr1, CStr2# \n 
  : { ErrorMessage (eEolString, eError, StringPos);
      Strings.Append (String, Char (String, 1));
      yyEol (0); 
      yyPrevious;
      IF InsideCode THEN
         Concatenate (LastWord, String);
      ELSE
         Attribute.Mode := Symbol;
         Attribute.Sym := MakeIdent (String);
         RETURN SymString;
      END;}

/* Modula2-style Comments */ 

#STD, token, rule# "(*" :
{
  yyStart (comment);
  GetWord (LastWord);
  Attribute.Mode := Comment;
  CommentPos := Attribute.Position; 
  MakeList (Attribute.Comm);
  CommentNestingLevel := 1;
}

#code#             "(*" :
{
  yyStart (comment);
  GetWord (Word);
  Concatenate(LastWord, Word); 
  CommentPos := Attribute.Position; 
  CommentNestingLevel := 1;
}

#comment#       "(*"    :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  INC (CommentNestingLevel);
}

#comment#       "*)"    :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  DEC (CommentNestingLevel);
  IF CommentNestingLevel = 0 THEN
    yyPrevious ( ) ;
    IF NOT InsideCode 
    THEN 
      Append (Attribute.Comm, ADDRESS (PutString (LastWord)));
      RETURN SymComment;
    END (* IF *); 
  END;
}

#comment#       "(" | "*" | cmt +       :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#comment#       \t      :-
{
  yyTab;
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#comment#       \n      :-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  IF InsideCode
  THEN 
    Append (Attribute.Act, ADDRESS (PutString (LastWord)));
  ELSE 
    Append (Attribute.Comm, ADDRESS (PutString (LastWord)));
  END (* IF *); 
  AssignEmpty (LastWord);
  yyEol (0);
}

/* C-style Comments */ 

#STD, token, rule# "/*" : 
  { yyStart (comment2); 
    CommentPos := Attribute.Position; 
  }

#code# "/*"     : 
{ yyStart (comment2); 
  GetWord (Word);
  Concatenate(LastWord, Word); 
  CommentPos := Attribute.Position; 
}

#comment2#      "*/"            
  :- { yyPrevious ( ) ; 
       IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
       END (* IF *);   
     }

#comment2#      "*" | cmt2 +    
  :- { IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
       END (* IF *);   
     }

#comment2#      \t 
  :- { IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
       END (* IF *) ;   
       yyTab ( ) ; 
     } 

#comment2#      \n 
  :- { IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
         Append (Attribute.Act, ADDRESS (PutString (LastWord)));
       END (* IF *) ; 
       yyEol ( 0 ) ; 
     } 

/* END of input.rex */ 





