
(* Ich, Doktor Josef Grosch, Informatiker, 20.3.1989 *)
(* Rodney M. Bates Feb 96. Added SPECWITH and BODYWITH sections. *)
(* RMB Jun 96 Added Modula-2 style comments (* ... *) , including
              nesting thereof.  
   RMB Oct 96 Changed to scan comments inside target code blocks properly.
              (previously, a quote inside a comment inside target
               code gave a spurious "unclosed string" message.) 
   RMB Apr 97 Added Ada expression operators. 
   RMB Jun 97 Added CompoundOperator for the THEN/ELSE of Ada 
              AND THEN and OR ELSE 
   RMB Sep 98 Changed to deliver tokens '.' and '->' in state expr,
              so parser can distinguish occurences of Ident following them
   RMB July 1999 Fixed a bug in postion of comments
   RMB Aug 1999 Added StringError and StringWarning
       
*) 

EXPORT  {
FROM StringMem  IMPORT tStringRef;
FROM Idents     IMPORT tIdent   ;
FROM Texts      IMPORT tText    ;
FROM Positions  IMPORT tPosition;
FROM Strings    IMPORT tString; 

TYPE
yyIdent = RECORD Ident: tIdent; 
END;
yyOperator = RECORD Ident: tIdent; 
END;
yyIncOperator = RECORD Ident: tIdent; 
END;
yyCompoundOperator = RECORD Ident: tIdent; 
END;
yyTargetBlock = RECORD Text: tText; 
END;
yyString = RECORD StringRef: tStringRef; 
END;
yyNumber = RECORD StringRef: tStringRef; 
END;
yyTargetCode = RECORD StringRef: tStringRef; 
END;
yyWhiteSpace = RECORD StringRef: tStringRef; 
END;
(* '::' *) yy10 = RECORD StringRef: tStringRef; 
END;
(* '.' *) yy11 = RECORD StringRef: tStringRef; 
END;
(* '->' *) yy12 = RECORD StringRef: tStringRef; 
END;

tScanAttribute = RECORD
Position: tPosition;
CASE : SHORTCARD OF
| 1: Ident: yyIdent;
| 2: Operator: yyOperator;
| 3: IncOperator: yyIncOperator;
| 4: CompoundOperator: yyCompoundOperator;
| 5: TargetBlock: yyTargetBlock;
| 6: String: yyString;
| 7: Number: yyNumber;
| 8: TargetCode: yyTargetCode;
| 9: WhiteSpace: yyWhiteSpace;
| 10: (* '::' *) yy10: yy10;
| 11: (* '.' *) yy11: yy11;
| 12: (* '->' *) yy12: yy12;
 END ;
END ;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR pAttribute: tScanAttribute);
 

PROCEDURE Error         (Text: ARRAY OF CHAR; Position: tPosition);
PROCEDURE StringError   (Text: tString; Position: tPosition);
PROCEDURE ErrorI        (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
PROCEDURE Warning       (Text: ARRAY OF CHAR; Position: tPosition);
PROCEDURE StringWarning (Text: tString; Position: tPosition);
PROCEDURE WarningI      (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
}

GLOBAL  {
FROM SYSTEM     IMPORT ADR;
FROM StringMem  IMPORT PutString;
FROM Strings    IMPORT tString, Concatenate, Char, SubString,
                        AssignEmpty, Length, WriteL;
FROM Idents     IMPORT tIdent, MakeIdent, NoIdent, GetStringRef ;
  (* NOTE: The references to GetStringRef (and no doubt others) 
           come from code in puma.pars, but they are generated 
           into Scanner.mi, whose imports come from here! *) 
FROM Texts      IMPORT MakeText, Append;
FROM Sets       IMPORT IsElement;
FROM Tree       IMPORT Options, ErrorCount;
FROM Positions  IMPORT tPosition;

IMPORT Errors;

VAR BraceNestingLevel , CommentNestingLevel : INTEGER; 
VAR CommentPos, StringPos, TargetPos : tPosition;
VAR InsideTarget , InsideExpr : BOOLEAN ; 

PROCEDURE ErrorAttribute (Token: INTEGER; VAR pAttribute: tScanAttribute);
BEGIN
 pAttribute.Position := Attribute.Position;
 CASE Token OF
 | (* Ident *) 1: 
 pAttribute.Ident.Ident       := NoIdent      ;
 ;
 | (* Operator *) 2: 
 pAttribute.Operator.Ident       := NoIdent      ;
 ;
 | (* IncOperator *) 3: 
 pAttribute.IncOperator.Ident       := NoIdent      ;
 ;
 | (* CompoundOperator *) 4: 
 pAttribute.CompoundOperator.Ident       := NoIdent      ;
 ;
 | (* TargetBlock *) 5: 
 MakeText (pAttribute.TargetBlock.Text); ;
 ;
 | (* String *) 6: 
 pAttribute.String.StringRef   := GetStringRef (NoIdent);
 ;
 | (* Number *) 7: 
 pAttribute.Number.StringRef   := GetStringRef (NoIdent);
 ;
 | (* TargetCode *) 8: 
 pAttribute.TargetCode.StringRef   := GetStringRef (NoIdent);
 ;
 | (* WhiteSpace *) 9: 
 pAttribute.WhiteSpace.StringRef   := GetStringRef (NoIdent);
 ;
 | (* '::' *) 10: 
 pAttribute.yy10.StringRef   := GetStringRef (NoIdent);
 ;
 | (* '.' *) 11: 
 pAttribute.yy11.StringRef   := GetStringRef (NoIdent);
 ;
 | (* '->' *) 12: 
 pAttribute.yy12.StringRef   := GetStringRef (NoIdent);
 ;
 ELSE
 END;
END ErrorAttribute;
 

PROCEDURE Error (Text: ARRAY OF CHAR; Position: tPosition);
   BEGIN
      Errors.Message (Text, Errors.Error, Position);
      INC (ErrorCount);
   END Error;

PROCEDURE StringError (Text: tString; Position: tPosition);
   BEGIN
       Errors.StringMessage (Text, Errors.Error, Position);
      INC (ErrorCount);
   END StringError;

PROCEDURE ErrorI (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
   BEGIN
      Errors.MessageI (Text, Errors.Error, Position, Errors.Ident, ADR (Ident));
      INC (ErrorCount);
   END ErrorI;

PROCEDURE Warning (Text: ARRAY OF CHAR; Position: tPosition);
   BEGIN
      IF NOT IsElement (ORD ('s'), Options) THEN
         Errors.Message (Text, Errors.Warning, Position);
      END;
   END Warning;

PROCEDURE StringWarning (Text: tString; Position: tPosition);
   BEGIN
      IF NOT IsElement (ORD ('s'), Options) THEN
         Errors.StringMessage (Text, Errors.Warning, Position);
      END;
   END StringWarning;

PROCEDURE WarningI (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
   BEGIN
      IF NOT IsElement (ORD ('s'), Options) THEN
         Errors.MessageI (Text, Errors.Warning, Position, Errors.Ident, ADR (Ident));
      END;
   END WarningI;
}

LOCAL   
  { VAR Word, String, TargetCode: tString; 

    PROCEDURE AccumComment ( ) ; 
    BEGIN
      IF InsideTarget AND ( BraceNestingLevel > 0 )
      THEN 
        GetWord (Word);
        Concatenate (TargetCode, Word);
      END (* IF *) 
    END AccumComment; 

  }

BEGIN   
  { BraceNestingLevel := 0; 
    CommentNestingLevel := 0; 
    InsideTarget := FALSE; 
    InsideExpr := FALSE; 
  }

DEFAULT 
  { GetWord (Word);
    Errors.MessageI 
      ( "illegal character", Errors.Error
      , Attribute.Position, Errors.String, ADR (Word)
      );
  }

EOF     {
   CASE yyStartState OF
   | CComment , M2Comment : Error ("unclosed comment", CommentPos);
     IF InsideTarget OR InsideExpr 
     THEN Error ("unclosed target code", TargetPos);
     END (* IF *) 
   | expr       ,
     targetcode : Error ("unclosed target code", TargetPos);
   | CStr1, CStr2,
     Str1, Str2 : Error ("unclosed string", StringPos);
     IF InsideTarget OR InsideExpr 
     THEN Error ("unclosed target code", TargetPos);
     END (* IF *) 
   ELSE
   END;
   BraceNestingLevel := 0; 
   CommentNestingLevel := 0; 
}

DEFINE  letter  =   {A-Z a-z _} .
        digit   =   {0-9}       .
        CCmtCh  = - {*\t\n}     .
        M2CmtCh  = - {*(\t\n}   .
        StrCh1  = - {'\t\n}     .
        StrCh2  = - {"\t\n}     .
        CStrCh1 = - {'\t\n\\}   .
        CStrCh2 = - {"\t\n\\}   .
        code    = - {\\\t\n{\}'"(/} .
        anyExpr = - {\\\t\n{\}'":\ (/\.\-a-zA-Z} .

START   CComment , M2Comment, Str1, Str2, CStr1, CStr2, targetcode, expr

RULE

#targetcode#    "{"     : {
                           IF BraceNestingLevel = 0 THEN
                              MakeText (Attribute.TargetBlock.Text);
                              AssignEmpty (TargetCode);
                              TargetPos := Attribute.Position;
                              InsideTarget := TRUE; 
                           ELSE
                              GetWord (Word);
                              Concatenate (TargetCode, Word);
                           END;
                           INC (BraceNestingLevel);
                        }

#targetcode#    "}"     :- {
                           DEC (BraceNestingLevel);
                           IF BraceNestingLevel = 0 THEN
                              yyStart (STD);
                              InsideTarget := FALSE; 
                              Append (Attribute.TargetBlock.Text, TargetCode);
                              Attribute.Position := TargetPos;
                              RETURN 5;
                           ELSE
                              GetWord (Word);
                              Concatenate (TargetCode, Word);
                           END;
                        }

#targetcode#    code +  | "/" | "(" 
                        :- {
                           IF BraceNestingLevel > 0 THEN
                              GetWord (Word);
                              Concatenate (TargetCode, Word);
                           END;
                        }

#targetcode#    \t      :- {
                           IF BraceNestingLevel > 0 THEN
                              Strings.Append (TargetCode, 11C);
                           END;
                           yyTab;
                        }

#targetcode#    \n      :- {
                           IF BraceNestingLevel > 0 THEN
                              Append (Attribute.TargetBlock.Text, TargetCode);
                              AssignEmpty (TargetCode);
                           END;
                           yyEol (0);
                        }

#targetcode#    \\ ANY  :- {
                           IF BraceNestingLevel > 0 THEN
                              GetWord (Word);
                              Strings.Append (TargetCode, Char (Word, 2));
                           END;
                        }

#targetcode#    \\      :- {
                           IF BraceNestingLevel > 0 THEN
                              Strings.Append (TargetCode, '\');
                           END;
                        }

#STD, expr, targetcode#  
             "(*"  :  { AccumComment ( );
                        CommentNestingLevel := 1; 
                        CommentPos := Attribute.Position; 
                        yyStart (M2Comment);
                      }

#M2Comment#  "(*"  :- { INC (CommentNestingLevel); AccumComment ( ); }
#M2Comment#  "*)"  :- { AccumComment ( ); DEC (CommentNestingLevel); 
                        IF CommentNestingLevel = 0 THEN yyPrevious; END;
                      }
#M2Comment#  "(" | "*" | M2CmtCh + :- { AccumComment ( ); }

#STD, expr, targetcode# 
           "/*"   :  { AccumComment ( ); 
                       yyStart (CComment); 
                       CommentPos := Attribute.Position;
                     }
#CComment# "*/"    :- { AccumComment ( ); yyPrevious;}
#CComment# "*" | CCmtCh + :- { AccumComment ( ); }

#M2Comment, CComment#   
              \t     :- {
                           IF InsideTarget AND ( BraceNestingLevel > 0 ) 
                           THEN
                              Strings.Append (TargetCode, 11C);
                           END;
                           yyTab;
                        }

#M2Comment, CComment#   
              \n     :- {
                           IF InsideTarget AND ( BraceNestingLevel > 0 ) 
                           THEN
                              Append (Attribute.TargetBlock.Text, TargetCode);
                              AssignEmpty (TargetCode);
                           END;
                           yyEol (0);
                        }

#STD# \f | \r           :- {}

#STD# (digit + "." digit * | digit * "." digit +) ({Ee} {+\-} ? digit +) ? 
      | digit +
                        :  {GetWord (Word);
                            Attribute.Number.StringRef := PutString (Word);
                            RETURN 7;}

#STD, expr, targetcode# ' :{GetWord (String);
                            StringPos := Attribute.Position;
                            IF IsElement (ORD ('c'), Options)
                            THEN yyStart (CStr1);
                            ELSE yyStart (Str1);
                            END;}

#STD, expr, targetcode# \":{GetWord (String);
                            StringPos := Attribute.Position;
                            IF IsElement (ORD ('c'), Options)
                            THEN yyStart (CStr2);
                            ELSE yyStart (Str2);
                            END;}

#Str1#  StrCh1 +        ,
#Str2#  StrCh2 +        ,
#CStr1# CStrCh1 + | \\ ANY ? ,
#CStr2# CStrCh2 + | \\ ANY ? :- {GetWord (Word); Concatenate (String, Word);}

#CStr1# \\ \n           ,
#CStr2# \\ \n           :- {GetWord (Word); Concatenate (String, Word); yyEol (0);}

#Str1, CStr1# '         ,
#Str2, CStr2# \"        :- {Strings.Append (String, Char (String, 1));
                            yyPrevious;
                            IF yyStartState = targetcode THEN
                               Concatenate (TargetCode, String);
                            ELSE
                               Attribute.String.StringRef := PutString (String);
                               RETURN 6;
                            END;}

#Str1, Str2, CStr1, CStr2# \t :- {Strings.Append (String, 11C); yyTab;}

#Str1, Str2, CStr1, CStr2# \n :- {Error ("unclosed string", Attribute.Position);
                            Strings.Append (String, Char (String, 1));
                            yyEol (0); yyPrevious;
                            IF yyStartState = targetcode THEN
                               Concatenate (TargetCode, String);
                            ELSE
                               Attribute.String.StringRef := PutString (String);
                               RETURN 6;
                            END;}

(* The following 3 tokens don't get inserted, even though they
   appear in puma.pars.  A possible reason?: they are declared
   there as subtokens of 'String' *) 
#STD# "::"              : {RETURN 10                  ;}

#STD# "."               : {RETURN 11                   ;}

#STD# "->"              : {RETURN 12                  ;}

#STD# "{"               : {IF BraceNestingLevel = 0 
                           THEN TargetPos := Attribute.Position; 
                           END;
                           yyStart (expr); 
                           InsideExpr := TRUE; 
                           INC (BraceNestingLevel); 
                           RETURN 39;}

#expr# anyExpr * | "(" | "/" 
                        : {GetWord (Word);
                           Attribute.TargetCode.StringRef := PutString (Word);
                           RETURN 8            ;}

#expr# "{"              : {INC (BraceNestingLevel);
                           GetWord (Word);
                           Attribute.TargetCode.StringRef := PutString (Word);
                           RETURN 8            ;}

#expr# "}"              : {DEC (BraceNestingLevel);
                           IF BraceNestingLevel = 0 THEN
                              yyStart (STD);
                              InsideExpr := FALSE; 
                              RETURN 40;
                           ELSE
                              GetWord (Word);
                              Attribute.TargetCode.StringRef := PutString (Word);
                              RETURN 8;
                           END                          ;}

#expr# ":"              : {GetWord (Word);
                           Attribute.TargetCode.StringRef := PutString (Word);
                           RETURN 8            ;}

#expr# "::"             : {GetWord (Word);
                           Attribute.yy10.StringRef := PutString (Word);
                           RETURN 10                  ;}

#expr# "."              : {GetWord (Word);
                           Attribute.yy11.StringRef := PutString (Word);
                           RETURN 11                   ;}

#expr# "->"             : {GetWord (Word);
                           Attribute.yy12.StringRef := PutString (Word);
                           RETURN 12                  ;}

#expr# "-"              : {GetWord (Word);
                           Attribute.TargetCode.StringRef := PutString (Word);
                           RETURN 8            ;}

#expr# " " +            : {GetWord (Word);
                           Attribute.WhiteSpace.StringRef := PutString (Word);
                           RETURN 9            ;}

#expr# \n               : {GetWord (Word);
                           Attribute.WhiteSpace.StringRef := PutString (Word);
                           yyEol (0);
                           RETURN 9            ;}

#expr# \t               : {GetWord (Word);
                           Attribute.WhiteSpace.StringRef := PutString (Word);
                           yyTab;
                           RETURN 9            ;}

#expr# \\ ANY           : {GetWord (Word);
                           SubString (Word, 2, 2, String);
                           Attribute.TargetCode.StringRef 
                             := PutString (String);
                           RETURN 8            ;}

#expr# \\               : {GetWord (Word);
                           Attribute.TargetCode.StringRef := PutString (Word);
                           RETURN 8            ;}

#STD# SPECWITH          : {yyStart (targetcode); RETURN 19;}
#STD# BODYWITH          : {yyStart (targetcode); RETURN 20;}
#STD# BEGIN             : {yyStart (targetcode); RETURN 24;}
#STD# CLOSE             : {yyStart (targetcode); RETURN 25;}
#STD# EXPORT            : {yyStart (targetcode); RETURN 21;}
#STD# GLOBAL            : {yyStart (targetcode); RETURN 23;}
#STD# IMPORT            : {yyStart (targetcode); RETURN 22;}
#STD# LOCAL             : {yyStart (targetcode); RETURN 34;}

#STD# 
  "!"
| "!="
| "#"
| "%"
| "&"
| "&&"
| "*"
| "+"
| "-"
| "/"
| "<"
| "<<"
| "<="
| "<>"
| "="
| "=="
| ">"
| ">="
| ">>"
| "|"
| "||"
| "~"
| "**" 
| "/=" 
| DIV
| in | iN | In | IN
| or | oR | Or | OR
| and | anD | aNd | aND | And | AnD | ANd | AND 
| mod | moD | mOd | mOD | Mod | MoD | MOd | MOD  
| not | noT | nOt | nOT | Not | NoT | NOt | \NOT 
| abs | abS | aBs | aBS | Abs | AbS | ABs | ABS 
| rem | reM | rEm | rEM | Rem | ReM | REm | REM 
| xor | xoR | xOr | xOR | Xor | XoR | XOr | XOR 
                        : {GetWord (Word);
                           Attribute.Operator.Ident := MakeIdent (Word);
                           RETURN 2              ;}

#STD# 
  then | theN | thEn | thEN | tHen | tHeN | tHEn | tHEN 
| Then | TheN | ThEn | ThEN | THen | THeN | THEn | THEN 
| else | elsE | elSe | elSE | eLse | eLsE | eLSe | eLSE 
| Else | ElsE | ElSe | ElSE | ELse | ELsE | ELSe | ELSE 
                        : {GetWord (Word);
                           Attribute.Operator.Ident := MakeIdent (Word);
                           RETURN 4              ;}

#STD# "++" | "--"       : {GetWord (Word);
                           Attribute.IncOperator.Ident := MakeIdent (Word);
                           RETURN 3           ;}

#STD# \\ - {\ \t\n} +   : {GetWord (Word);
                           SubString (Word, 2, Length (Word), String);
                           Attribute.Operator.Ident := MakeIdent (String);
                           RETURN 2              ;}

 #STD#TRAFO	: { RETURN 13; }
 #STD#TREE	: { RETURN 14; }
 #STD#\,	: { RETURN 15; }
 #STD#PUBLIC	: { RETURN 16; }
 #STD#EXTERN	: { RETURN 17; }
 #STD#\;	: { RETURN 18; }
 #STD#SPECWITH	: { RETURN 19; }
 #STD#BODYWITH	: { RETURN 20; }
 #STD#EXPORT	: { RETURN 21; }
 #STD#IMPORT	: { RETURN 22; }
 #STD#GLOBAL	: { RETURN 23; }
 #STD#BEGIN	: { RETURN 24; }
 #STD#CLOSE	: { RETURN 25; }
 #STD#PROCEDURE	: { RETURN 26; }
 #STD#\(	: { RETURN 27; }
 #STD#REF	: { RETURN 28; }
 #STD#\:	: { RETURN 29; }
 #STD#\[	: { RETURN 30; }
 #STD#\]	: { RETURN 31; }
 #STD#\=\>	: { RETURN 32; }
 #STD#\)	: { RETURN 33; }
 #STD#LOCAL	: { RETURN 34; }
 #STD#\.\.	: { RETURN 35; }
 #STD#\:\>	: { RETURN 36; }
 #STD#NIL	: { RETURN 37; }
 #STD#_	: { RETURN 38; }
 #STD#\{	: { RETURN 39; }
 #STD#\}	: { RETURN 40; }
 #STD#\^	: { RETURN 41; }
 #STD#\:\=	: { RETURN 42; }
 #STD#\?	: { RETURN 43; }
 #STD#REJECT	: { RETURN 44; }
 #STD#FAIL	: { RETURN 45; }
 #STD#VAR	: { RETURN 46; }
 #STD#NL	: { RETURN 47; }
 #STD#RETURN	: { RETURN 48; }
 #STD#FUNCTION	: { RETURN 49; }
 #STD#PREDICATE	: { RETURN 50; }
 

#STD# "..."             : {RETURN 35                  ;}
#STD# ":-"              : {RETURN 43                   ;}

#STD, expr# letter (letter | digit) *
                        : {GetWord (Word);
                           Attribute.Ident.Ident := MakeIdent (Word);
                           RETURN 1                 ;}
