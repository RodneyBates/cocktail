
(* $Id: Scanner.mi,v 2.11 1992/09/24 13:14:00 grosch rel $ *)

(* Modified Rodney M. Bates 
   Mar 94 to compile under WRL 
   Mar 96 to fix a bug in PROCEDURE input 
   Mar 96 to add functions UpperCase and LowerCase, to exploit
          the arrays yyToUpper and yyToLower, already there.
   Apr 96 to add yyTotalLineCount and TotalLineCount. 
*) 

 UNSAFE MODULE Scanner;
 
FROM SYSTEM IMPORT M2LONGCARD, SHORTCARD;
IMPORT Word, SYSTEM, FrontChecks, System, General, Positions, ReuseIO, DynArray, Strings, Source;
IMPORT Checks, Errors, Fmt, OSError, Text;
(* line 86 "../src/input.rex" *)



FROM Strings    IMPORT tString, TextToString, Concatenate, 
                       SubString, AssignEmpty, Assign, Char, Length;
FROM StringMem  IMPORT tStringRef, PutString;
FROM Idents     IMPORT MakeIdent;
FROM Lists      IMPORT tList, Append, MakeList;
FROM Limits     IMPORT MaxShortCard;
FROM WriteTok   IMPORT tLanguage, Language;
FROM FrontErrors     IMPORT eWarning, eError, eCharacter, eString, 
                       ErrorMessage, ErrorMessageI;
FROM Positions  IMPORT tPosition;

CONST
  eCharIgnored  = 10;
  eEolString    = 11;
  eUnClAction   = 12;
  eUnClComment  = 13;
  eUnClString   = 14;

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

PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attr: tScanAttribute) =
  VAR s : tString;
  BEGIN
    CASE Token OF
      SymNull => 
    | SymEqual..SymPREC 
      => Attr.Mode       := AttributeMode.Keys;
    | SymComment        
      => Attr.Mode       := AttributeMode.Comment;
        MakeList (Attr.Comm);
    | SymNumber         
      => Attr.Mode       := AttributeMode.Number;
        Attr.Value:= MaxShortCard;
    | SymAction
      => Attr.Mode       := AttributeMode.Action;
        MakeList (Attr.Act);
    | SymIdentifier , SymString 
      => Attr.Mode       := AttributeMode.Symbol;
        TextToString ("-error-", s);
        Attr.Sym        := MakeIdent (s);
    END;
  END ErrorAttribute;

PROCEDURE GetNumber (VAR AsChars: tString): Word.T =
  VAR i, n, d : Word.T;
   BEGIN
      i := 0;
      n := 0;
      WHILE i < Length (AsChars) DO
        i := i+1;
        d := (ORD(Char (AsChars, i))-ORD('0'));
        IF (n > (MaxShortCard DIV 10)) OR ((n*10) > (MaxShortCard - d)) THEN
          RETURN MaxShortCard;
        END;
        n := (n*10) + d;
      END;
      RETURN n;
   END GetNumber;

 
CONST
   yyTabSpace           = 8;
   yyDNoState           = 0;
   yyFileStackSize      = 32;
   yyInitBufferSize     = (1024 * 8) + 256;
yyFirstCh       = '\000';
yyLastCh        = '\177';
yyEolCh = '\012';
yyEobCh = '\177';
yyDStateCount   = 164;
yyTableSize     = 1743;
yyEobState      = 47;
yyDefaultState  = 48;
STD     = 1;
token   = 3;
rule    = 5;
code    = 7;
Str1    = 9;
Str2    = 11;
CStr1   = 13;
CStr2   = 15;
comment = 17;
comment2        = 19;
 
TYPE
   yyTableElmt          = SHORTCARD;
   yyStateRange         = (*yyTableElmt*) [0 .. yyDStateCount];
   yyTableRange         = (*yyTableElmt*) [0 .. yyTableSize];
   yyCombType           = RECORD Check, Next: yyStateRange; END;
   yyCombTypePtr        = UNTRACED BRANDED REF  yyCombType;
   yytChOpenBufferPtr   = REF ARRAY OF CHAR;
   yytChBufferPtr       = UNTRACED REF ARRAY [ 0 .. 16_7FFFFFF0 ] OF CHAR; 
   yyChRange            = [yyFirstCh .. yyLastCh];
   yyFileStackPtrTyp    = SHORTCARD;
   yyFileStackSubscript = (*yyFileStackPtrTyp*) [1 .. yyFileStackSize];

VAR
   yyBasePtr            : ARRAY yyStateRange    OF M2LONGCARD     ;
   yyDefault            : ARRAY yyStateRange    OF yyStateRange ;
   yyComb               : ARRAY yyTableRange    OF yyCombType   ;
   yyEobTrans           : ARRAY yyStateRange    OF yyStateRange ;
   yyToLower, yyToUpper : ARRAY yyChRange       OF CHAR         ;

   yyStateStack         : REF  ARRAY OF yyStateRange;
   yyStateStackSize     : INTEGER;
   yyStartState         : yyStateRange;
   yyPreviousStart      : yyStateRange;
   yyCh                 : CHAR;
 
   yySourceFile         : System.tFile;
   yyEof                : BOOLEAN;
   yyChOpenBufferPtr    : yytChOpenBufferPtr;
   yyChBufferPtr        : yytChBufferPtr;
   yyChBufferStart      : INTEGER;
   yyChBufferSize       : INTEGER;
   yyChBufferIndex      : INTEGER;
   yyBytesRead          : INTEGER;
   yyLineCount          : SHORTCARD; (* Number of the current line,
                                        of the current file. *) 
   yyTotalLineCount     : Word.T;  (* Number of lines already read,
                                        of all files. *) 
   yyLineStart          : INTEGER;

   yyFileStackPtr       : yyFileStackPtrTyp;
   yyFileStack          : ARRAY yyFileStackSubscript OF RECORD
                             SourceFile         : System.tFile;
                             Eof                : BOOLEAN;
                             ChOpenBufferPtr    : yytChOpenBufferPtr;
                             ChBufferPtr        : yytChBufferPtr;
                             ChBufferStart      : INTEGER;
                             ChBufferSize       : INTEGER;
                             ChBufferIndex      : INTEGER;
                             BytesRead          : INTEGER;
                             LineCount          : SHORTCARD;
                             LineStart          : INTEGER;
                          END; 

PROCEDURE ExtendChArray ( VAR ArrRef: REF ARRAY OF CHAR ) =
  VAR LOldArrRef : REF ARRAY OF CHAR;
  VAR LNumber: INTEGER; 
BEGIN
  LOldArrRef := ArrRef;
  LNumber := NUMBER (ArrRef ^); 
  ArrRef := NEW ( REF ARRAY OF CHAR , LNumber * 2 );
  SUBARRAY ( ArrRef ^, 0 , LNumber) := LOldArrRef ^;
END ExtendChArray; 

PROCEDURE ExtendStateArray ( VAR ArrRef: REF ARRAY OF yyStateRange ) =
  VAR LOldArrRef : REF ARRAY OF yyStateRange;
  VAR LNumber: INTEGER; 
BEGIN
  LOldArrRef := ArrRef;
  LNumber := NUMBER (ArrRef ^); 
  ArrRef := NEW ( REF ARRAY OF yyStateRange , LNumber * 2 );
  SUBARRAY ( ArrRef ^, 0 , LNumber) := LOldArrRef ^;
END ExtendStateArray; 

PROCEDURE GetToken (): INTEGER =
   VAR
      yyState           : yyStateRange;
      yyTablePtr        : yyCombTypePtr;
      yyRestartFlag     : BOOLEAN;
      yyi, yySource, yyTarget : INTEGER;
      yyChBufferFree    : INTEGER;

(* line 184 "../src/input.rex" *)
 VAR Word, String, LastWord: tString; c: CHAR; PrevState: SHORTCARD; 
  
BEGIN
   LOOP
      yyState           := yyStartState;
      TokenLength       := 0;
 
      (* ASSERT yyChBuffer [yyChBufferIndex] = first character *)
 
      LOOP              (* eventually restart after sentinel *)
         LOOP           (* execute as many state transitions as possible *)
                                                (* determine next state *)
            yyTablePtr := LOOPHOLE (yyBasePtr [yyState] +
               (VAL(ORD (yyChBufferPtr^ [yyChBufferIndex]),M2LONGCARD )
               * VAL( BYTESIZE (yyCombType),M2LONGCARD)) ,yyCombTypePtr);
            IF yyTablePtr^.Check # yyState THEN
               yyState := yyDefault [yyState];
               IF yyState = yyDNoState THEN EXIT; END;
            ELSE
               yyState := yyTablePtr^.Next;
               INC (TokenLength);
               yyStateStack^ [TokenLength] := yyState;  (* push state *)
               INC (yyChBufferIndex);           (* get next character *)
            END;
         END;
 
         LOOP                                   (* search for last final state *)
CASE yyStateStack^ [TokenLength] OF
|164
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 230 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymEqual     ; 
yyRestartFlag := FALSE; EXIT;
|163
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 231 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymOPER      ; 
yyRestartFlag := FALSE; EXIT;
|159
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 232 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymNONE      ; 
yyRestartFlag := FALSE; EXIT;
|155
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 233 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymLEFT      ; 
yyRestartFlag := FALSE; EXIT;
|152
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 234 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymRIGHT     ; 
yyRestartFlag := FALSE; EXIT;
|148
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 235 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; yyStart (rule); RETURN SymRULE      ; 
yyRestartFlag := FALSE; EXIT;
|30
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 237 "../src/input.rex" *)

  Attribute.Mode := AttributeMode.Number;
  GetWord (Word);
  Attribute.Sym := MakeIdent (Word);
  Attribute.Value := GetNumber (Word);
  RETURN SymNumber;

yyRestartFlag := FALSE; EXIT;
|144
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 248 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymColon     ; 
yyRestartFlag := FALSE; EXIT;
|143
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 249 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymPoint     ; 
yyRestartFlag := FALSE; EXIT;
|139
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 250 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymOr        ; 
yyRestartFlag := FALSE; EXIT;
|142
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 251 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymStar      ; 
yyRestartFlag := FALSE; EXIT;
|141
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 252 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymPlus      ; 
yyRestartFlag := FALSE; EXIT;
|140
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 253 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymList      ; 
yyRestartFlag := FALSE; EXIT;
|74
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 254 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymLBrace    ; 
yyRestartFlag := FALSE; EXIT;
|138
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 255 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymRBrace    ; 
yyRestartFlag := FALSE; EXIT;
|137
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 256 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymLBracket  ; 
yyRestartFlag := FALSE; EXIT;
|136
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 257 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymRBracket  ; 
yyRestartFlag := FALSE; EXIT;
|135
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 258 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymPREC      ; 
yyRestartFlag := FALSE; EXIT;
|132
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 262 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymScanner   ; 
yyRestartFlag := FALSE; EXIT;
|125
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 263 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymParser    ; 
yyRestartFlag := FALSE; EXIT;
|119
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 264 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymEXPORT    ; 
yyRestartFlag := FALSE; EXIT;
|113
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 265 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymGLOBAL    ; 
yyRestartFlag := FALSE; EXIT;
|107
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 266 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymLOCAL     ; 
yyRestartFlag := FALSE; EXIT;
|102
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 267 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymBEGIN     ; 
yyRestartFlag := FALSE; EXIT;
|97
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 268 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; RETURN SymCLOSE     ; 
yyRestartFlag := FALSE; EXIT;
|92
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 269 "../src/input.rex" *)
 Attribute.Mode := AttributeMode.Keys; yyStart (token); RETURN SymTOKEN    ; 
yyRestartFlag := FALSE; EXIT;
|33
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 274 "../src/input.rex" *)

  Attribute.Mode := AttributeMode.Keys;
  GetWord (Word);
  SubString (Word, 2, Length (Word), String);
  Attribute.Sym := MakeIdent (String);
  RETURN SymIdentifier;

yyRestartFlag := FALSE; EXIT;
|31
,88
,89
,90
,91
,93
,94
,95
,96
,98
,99
,100
,101
,103
,104
,105
,106
,108
,109
,110
,111
,112
,114
,115
,116
,117
,118
,120
,121
,122
,123
,124
,126
,127
,128
,129
,130
,131
,133
,134
,145
,146
,147
,149
,150
,151
,153
,154
,156
,157
,158
,160
,161
,162
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 283 "../src/input.rex" *)

  Attribute.Mode := AttributeMode.Keys;
  GetWord (Word);
  Attribute.Sym := MakeIdent (Word);
  RETURN SymIdentifier;

yyRestartFlag := FALSE; EXIT;
|32
=>
(* line 290 "../src/input.rex" *)

yyRestartFlag := FALSE; EXIT;
|29
,42
,64
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 293 "../src/input.rex" *)

  GetWord (Word);
  c := Char (Word, 1);
  ErrorMessageI (eCharIgnored, eWarning, Attribute.Position, eCharacter, ADR (c));

yyRestartFlag := FALSE; EXIT;
|87
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 302 "../src/input.rex" *)

  PrevState := yyStartState;
  CodePos := Attribute.Position;
  yyStart (code);
  InsideCode := TRUE; 
  GetWord (LastWord);
  Attribute.Mode := AttributeMode.Action;
  MakeList (Attribute.Act);
  BraceNestingLevel := 1;

yyRestartFlag := FALSE; EXIT;
|28
,41
,52
,62
,72
=>
(* line 314 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);

yyRestartFlag := FALSE; EXIT;
|26
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 320 "../src/input.rex" *)

  c := '\\';
  ErrorMessageI (eCharIgnored, eWarning, Attribute.Position, eCharacter, ADR (c));

yyRestartFlag := FALSE; EXIT;
|86
=>
(* line 326 "../src/input.rex" *)

  yyTab();
  GetWord (Word);
  Concatenate (LastWord, Word);

yyRestartFlag := FALSE; EXIT;
|85
=>
(* line 333 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);
  Append (Attribute.Act, LOOPHOLE (PutString (LastWord),ADDRESS));
  AssignEmpty (LastWord);
  yyEol (0);

yyRestartFlag := FALSE; EXIT;
|84
=>
(* line 342 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);
  INC (BraceNestingLevel);

yyRestartFlag := FALSE; EXIT;
|83
=>
(* line 349 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);
  DEC (BraceNestingLevel);
  IF BraceNestingLevel = 0 THEN
    yyStart (PrevState);
    Attribute.Position := CodePos;
    Append (Attribute.Act, LOOPHOLE (PutString (LastWord),ADDRESS));
    InsideCode := FALSE; 
    RETURN SymAction;
  END;

yyRestartFlag := FALSE; EXIT;
|82
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 365 "../src/input.rex" *)
 GetWord (String);
      StringPos := Attribute.Position; 
      IF Language = tLanguage.C
      THEN yyStart (CStr1);
      ELSE yyStart (Str1);
      END;
    
yyRestartFlag := FALSE; EXIT;
|81
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 374 "../src/input.rex" *)
 GetWord (String);
      StringPos := Attribute.Position; 
      IF Language = tLanguage.C
      THEN yyStart (CStr2);
      ELSE yyStart (Str2);
      END;
    
yyRestartFlag := FALSE; EXIT;
|27
,40
,53
=>
(* line 386 "../src/input.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|25
,38
,54
=>
(* line 386 "../src/input.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|24
,37
,44
,55
=>
(* line 386 "../src/input.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|23
,36
,43
,56
=>
(* line 386 "../src/input.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|80
=>
(* line 388 "../src/input.rex" *)
GetWord (Word); Concatenate (String, Word); yyEol (0);
yyRestartFlag := FALSE; EXIT;
|45
,79
=>
(* line 392 "../src/input.rex" *)
 Strings.Append (String, Char (String, 1));
       yyPrevious();
       IF InsideCode THEN
         Concatenate (LastWord, String);
       ELSE
         Attribute.Mode := AttributeMode.Symbol;
         Attribute.Sym := MakeIdent (String);
         RETURN SymString;
       END;
     
yyRestartFlag := FALSE; EXIT;
|39
,78
=>
(* line 392 "../src/input.rex" *)
 Strings.Append (String, Char (String, 1));
       yyPrevious();
       IF InsideCode THEN
         Concatenate (LastWord, String);
       ELSE
         Attribute.Mode := AttributeMode.Symbol;
         Attribute.Sym := MakeIdent (String);
         RETURN SymString;
       END;
     
yyRestartFlag := FALSE; EXIT;
|77
=>
(* line 404 "../src/input.rex" *)
Strings.Append (String, '\011'); yyTab();
yyRestartFlag := FALSE; EXIT;
|76
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 407 "../src/input.rex" *)
 ErrorMessage (eEolString, eError, StringPos);
      Strings.Append (String, Char (String, 1));
      yyEol (0); 
      yyPrevious();
      IF InsideCode THEN
         Concatenate (LastWord, String);
      ELSE
         Attribute.Mode := AttributeMode.Symbol;
         Attribute.Sym := MakeIdent (String);
         RETURN SymString;
      END;
yyRestartFlag := FALSE; EXIT;
|75
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 422 "../src/input.rex" *)

  yyStart (comment);
  GetWord (LastWord);
  Attribute.Mode := AttributeMode.Comment;
  CommentPos := Attribute.Position; 
  MakeList (Attribute.Comm);
  CommentNestingLevel := 1;

yyRestartFlag := FALSE; EXIT;
|73
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 432 "../src/input.rex" *)

  yyStart (comment);
  GetWord (Word);
  Concatenate(LastWord, Word); 
  CommentPos := Attribute.Position; 
  CommentNestingLevel := 1;

yyRestartFlag := FALSE; EXIT;
|71
=>
(* line 441 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);
  INC (CommentNestingLevel);

yyRestartFlag := FALSE; EXIT;
|69
=>
(* line 448 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);
  DEC (CommentNestingLevel);
  IF CommentNestingLevel = 0 THEN
    yyPrevious ( ) ;
    IF NOT InsideCode 
    THEN 
      Append (Attribute.Comm, LOOPHOLE (PutString (LastWord),ADDRESS));
      RETURN SymComment;
    END (* IF *); 
  END;

yyRestartFlag := FALSE; EXIT;
|22
,35
,57
,68
,70
=>
(* line 463 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);

yyRestartFlag := FALSE; EXIT;
|67
=>
(* line 469 "../src/input.rex" *)

  yyTab();
  GetWord (Word);
  Concatenate (LastWord, Word);

yyRestartFlag := FALSE; EXIT;
|66
=>
(* line 476 "../src/input.rex" *)

  GetWord (Word);
  Concatenate (LastWord, Word);
  IF InsideCode
  THEN 
    Append (Attribute.Act, LOOPHOLE (PutString (LastWord),ADDRESS));
  ELSE 
    Append (Attribute.Comm, LOOPHOLE (PutString (LastWord),ADDRESS));
  END (* IF *); 
  AssignEmpty (LastWord);
  yyEol (0);

yyRestartFlag := FALSE; EXIT;
|65
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 492 "../src/input.rex" *)
 yyStart (comment2); 
    CommentPos := Attribute.Position; 
  
yyRestartFlag := FALSE; EXIT;
|63
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 497 "../src/input.rex" *)
 yyStart (comment2); 
  GetWord (Word);
  Concatenate(LastWord, Word); 
  CommentPos := Attribute.Position; 

yyRestartFlag := FALSE; EXIT;
|61
=>
(* line 504 "../src/input.rex" *)
 yyPrevious ( ) ; 
       IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
       END (* IF *);   
     
yyRestartFlag := FALSE; EXIT;
|21
,34
,58
=>
(* line 513 "../src/input.rex" *)
 IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
       END (* IF *);   
     
yyRestartFlag := FALSE; EXIT;
|60
=>
(* line 521 "../src/input.rex" *)
 IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
       END (* IF *) ;   
       yyTab ( ) ; 
     
yyRestartFlag := FALSE; EXIT;
|59
=>
(* line 530 "../src/input.rex" *)
 IF InsideCode 
       THEN 
         GetWord (Word);
         Concatenate (LastWord, Word);
         Append (Attribute.Act, LOOPHOLE (PutString (LastWord),ADDRESS));
       END (* IF *) ; 
       yyEol ( 0 ) ; 
     
yyRestartFlag := FALSE; EXIT;
|51
=>
(* BlankAction *)
WHILE yyChBufferPtr^ [yyChBufferIndex] = ' ' DO INC (yyChBufferIndex); END;
yyRestartFlag := FALSE; EXIT;
|50
=>
(* TabAction *)
DEC (yyLineStart, 7 - ((yyChBufferIndex - yyLineStart - 2) MOD 8));
yyRestartFlag := FALSE; EXIT;
|49
=>
(* EolAction *)
INC (yyLineCount);
yyLineStart := yyChBufferIndex - 1;
yyRestartFlag := FALSE; EXIT;
|1
,2
,3
,4
,5
,6
,7
,8
,9
,10
,11
,12
,13
,14
,15
,16
,17
,18
,19
,20
,46
=>
            (* non final states *)
                  DEC (yyChBufferIndex);        (* return character *)
                  DEC (TokenLength)             (* pop state *)
 
| 48=>
                  Attribute.Position.Line   := yyLineCount;
                  Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart,SHORTCARD);
                  INC (yyChBufferIndex);
                  TokenLength := 1;
ReuseIO.WriteC (ReuseIO.StdOutput, yyChBufferPtr^ [yyChBufferIndex-1]);
                  yyRestartFlag := FALSE; EXIT;

            |  yyDNoState       =>              (* automatic initialization *)
                  yyGetTables();
                  yyStateStack^ [0] := yyDefaultState; (* stack underflow sentinel *)
                  IF yyFileStackPtr = 0 THEN
                     yyInitialize();
                     yySourceFile := System.StdInput;
                  END;
                  yyRestartFlag := FALSE; EXIT;

| 47=>
                  DEC (yyChBufferIndex);        (* undo last state transition *)
                  DEC (TokenLength);            (* get previous state *)
                  IF TokenLength = 0 THEN
                     yyState := yyStartState;
                  ELSE
                     yyState := yyStateStack^ [TokenLength];
                  END;

                  IF yyChBufferIndex # (yyChBufferStart + yyBytesRead) THEN
                     yyState := yyEobTrans [yyState];   (* end of buffer sentinel in buffer *)
                     IF yyState # yyDNoState THEN
                        INC (yyChBufferIndex);
                        INC (TokenLength);
                        yyStateStack^ [TokenLength] := yyState;
                        yyRestartFlag := TRUE; EXIT;
                     END;
                  ELSE                          (* end of buffer reached *)

                     (* copy initial part of token in front of input buffer *)

                     yySource := yyChBufferIndex - TokenLength - 1;
                     yyTarget := General.MaxAlign - (TokenLength MOD General.MaxAlign) - 1;
                     IF yySource # yyTarget THEN
                        FOR yyi := 1 TO TokenLength DO
                           yyChBufferPtr^ [yyTarget + yyi] := yyChBufferPtr^ [yySource + yyi];
                        END;
                        DEC (yyLineStart, yySource - yyTarget);
                        yyChBufferStart := yyTarget + TokenLength + 1;
                     ELSE
                        yyChBufferStart := yyChBufferIndex;
                     END;

                     IF NOT yyEof THEN          (* read buffer and restart *)


                        yyChBufferFree 
                          := General.Exp2 
                                  (General.Log2 
                                     (yyChBufferSize - 4 - General.MaxAlign - TokenLength)
                                  );

(* WAS:                 yyChBufferFree 
                          := VAL(  
                                 General.Exp2 
                                  (General.Log2 
                                     (yyChBufferSize - 4 - VAL(General.MaxAlign,INTEGER) -VAL( TokenLength,LONGINT))
                                  ),LONGINT
                                );
*)

                        IF yyChBufferFree < (yyChBufferSize DIV 8) THEN
                           ExtendChArray (yyChOpenBufferPtr); 
                           yyChBufferPtr := LOOPHOLE(ADR (yyChOpenBufferPtr ^ [0]), yytChBufferPtr);
(* WAS:                    DynArray.ExtendArray (yyChBufferPtr, yyChBufferSize, BYTESIZE (CHAR)); *) 
                           IF yyChOpenBufferPtr = NIL THEN yyErrorMessage (1); END;

                           yyChBufferFree 
                             := General.Exp2 
                                  (General.Log2 
                                     (yyChBufferSize - 4 - General.MaxAlign - TokenLength)
                                  );

(* WAS:                    yyChBufferFree 
                             := VAL ( 
                                     General.Exp2 
                                        (General.Log2 
                                           (yyChBufferSize - 4 - VAL(General.MaxAlign,INTEGER) - VAL(TokenLength,LONGINT))
                                        ),LONGINT
                                    );
*)

                           IF yyStateStackSize < yyChBufferSize THEN
                              ExtendStateArray (yyStateStack); 
(* WAS:                       DynArray.ExtendArray (yyStateStack, yyStateStackSize, BYTESIZE (yyStateRange));*)
                              IF yyStateStack = NIL THEN yyErrorMessage (1); END;
                           END;
                        END;
                        yyChBufferIndex := yyChBufferStart;
                        yyBytesRead := Source.GetLine 
                                 (yySourceFile
                                  , ADR (yyChBufferPtr^ [yyChBufferIndex])
                                  , yyChBufferFree
                                  );
                        IF yyBytesRead <= 0 THEN yyBytesRead := 0; yyEof := TRUE; END;
                        yyChBufferPtr^ [yyChBufferStart + yyBytesRead    ] := yyEobCh;
                        yyChBufferPtr^ [yyChBufferStart + yyBytesRead + 1] := '\000';
                        yyRestartFlag := TRUE; EXIT;
                     END;

                     IF TokenLength = 0 THEN    (* end of file reached *)
                        Attribute.Position.Line   := yyLineCount;
                        Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart,SHORTCARD);
                        CloseFile();
                        IF yyFileStackPtr = 0 THEN
(* line 188 "../src/input.rex" *)

    CASE yyStartState OF
    | code                      
        => ErrorMessage (eUnClAction , eError, CodePos );
    | comment, comment2 
        => ErrorMessage (eUnClComment, eError, CommentPos ); 
          IF InsideCode 
          THEN
            ErrorMessage (eUnClAction , eError, CodePos );
          END (* IF *) 
    | Str1, Str2, CStr1, CStr2
        => ErrorMessage (eUnClString, eError, StringPos );
          IF InsideCode 
          THEN
            ErrorMessage (eUnClAction , eError, CodePos );
          END (* IF *) 
    ELSE
    END;
  
                        END;
                        IF yyFileStackPtr = 0 THEN RETURN EofToken; END;
                        yyRestartFlag := FALSE; EXIT;
                     END;
                  END;
            ELSE
               yyErrorMessage (0);
            END;
         END;
         IF yyRestartFlag THEN ELSE EXIT; END;
      END;
   END;
   END GetToken;
 
PROCEDURE BeginFile (READONLY FileName: ARRAY OF CHAR) =
   BEGIN
      IF yyStateStack^ [0] = yyDNoState THEN    (* have tables been read in ? *)
         yyGetTables();
         yyStateStack^ [0] := yyDefaultState;   (* stack underflow sentinel *)
      END;
      yyInitialize();
      yySourceFile := Source.BeginSource (FileName);
      IF yySourceFile < 0 THEN yyErrorMessage (5); END;
   END BeginFile;

PROCEDURE yyInitialize() =
   BEGIN
      IF yyFileStackPtr >= yyFileStackSize THEN yyErrorMessage (3); END;
      INC (yyFileStackPtr);                     (* push file *)
      WITH m2tom3_with_1=yyFileStack [yyFileStackPtr] DO
         m2tom3_with_1.SourceFile       := yySourceFile         ;
         m2tom3_with_1.Eof              := yyEof                ;
         m2tom3_with_1.ChOpenBufferPtr  := yyChOpenBufferPtr        ;
         m2tom3_with_1.ChBufferPtr      := yyChBufferPtr        ;
         m2tom3_with_1.ChBufferStart    := yyChBufferStart      ;
         m2tom3_with_1.ChBufferSize     := yyChBufferSize       ;
         m2tom3_with_1.ChBufferIndex    := yyChBufferIndex      ;
         m2tom3_with_1.BytesRead        := yyBytesRead          ;
         m2tom3_with_1.LineCount        := yyLineCount          ;
         m2tom3_with_1.LineStart        := yyLineStart          ;
      END;
                                                (* initialize file state *)
      yyChBufferSize    := yyInitBufferSize;
      yyChOpenBufferPtr := NEW ( REF ARRAY OF CHAR, yyChBufferSize); 
      yyChBufferPtr := LOOPHOLE(ADR (yyChOpenBufferPtr ^ [0]), yytChBufferPtr);
(* WAS:DynArray.MakeArray (yyChBufferPtr, yyChBufferSize, BYTESIZE (CHAR));*)
      IF yyChOpenBufferPtr = NIL THEN yyErrorMessage (1); END;
      yyChBufferStart   := General.MaxAlign;
      yyChBufferPtr^ [yyChBufferStart - 1] := yyEolCh; (* begin of line indicator *)
      yyChBufferPtr^ [yyChBufferStart    ] := yyEobCh; (* end of buffer sentinel *)
      yyChBufferPtr^ [yyChBufferStart + 1] := '\000';
      yyChBufferIndex   := yyChBufferStart;
      yyEof             := FALSE;
      yyBytesRead       := 0;
      yyLineCount       := 1;
      yyTotalLineCount  := 0;
      yyLineStart       := yyChBufferStart - 1;
   END yyInitialize;

PROCEDURE CloseFile() =
   BEGIN
      IF yyFileStackPtr = 0 THEN yyErrorMessage (4); END;
      Source.CloseSource (yySourceFile);
      yyChBufferPtr := NIL;
      yyChOpenBufferPtr := NIL;
(*WAS:DynArray.ReleaseArray (yyChBufferPtr, yyChBufferSize, BYTESIZE (CHAR));*) 
      WITH m2tom3_with_2=yyFileStack [yyFileStackPtr] DO        (* pop file *)
         yySourceFile   := m2tom3_with_2.SourceFile             ;
         yyEof          := m2tom3_with_2.Eof                    ;
         yyChOpenBufferPtr := m2tom3_with_2.ChOpenBufferPtr            ;
         yyChBufferPtr  := m2tom3_with_2.ChBufferPtr            ;
         yyChBufferStart:= m2tom3_with_2.ChBufferStart  ;
         yyChBufferSize := m2tom3_with_2.ChBufferSize           ;
         yyChBufferIndex:= m2tom3_with_2.ChBufferIndex  ;
         yyBytesRead    := m2tom3_with_2.BytesRead              ;
         yyLineCount    := m2tom3_with_2.LineCount              ;
         yyLineStart    := m2tom3_with_2.LineStart              ;
      END;
      DEC (yyFileStackPtr);             
   END CloseFile;

PROCEDURE GetWord (VAR Word: Strings.tString) =
   VAR i, WordStart     : INTEGER;
   BEGIN
      WordStart := yyChBufferIndex - TokenLength - 1;
      FOR i := 1 TO TokenLength DO
         Word.Chars [VAL(i,Strings.tStringIndex)] 
           := yyChOpenBufferPtr^ [WordStart + i];
      END;
      Word.Length := VAL(TokenLength,SHORTCARD);
   END GetWord;
 
PROCEDURE GetLower (VAR Word: Strings.tString) =
   VAR i, WordStart     : INTEGER;
   BEGIN
      WordStart := yyChBufferIndex - TokenLength - 1;
      FOR i := 1 TO TokenLength DO
         Word.Chars [VAL(i,Strings.tStringIndex)] 
           := yyToLower [yyChOpenBufferPtr^ [WordStart + i]];
      END;
      Word.Length := VAL(TokenLength,SHORTCARD);
   END GetLower;
 
PROCEDURE GetUpper (VAR Word: Strings.tString) =
   VAR i, WordStart     : INTEGER;
   BEGIN
      WordStart := yyChBufferIndex - TokenLength - 1;
      FOR i := 1 TO TokenLength DO
         Word.Chars [VAL(i,Strings.tStringIndex)] 
           := yyToUpper [yyChOpenBufferPtr^ [WordStart + i]];
      END;
      Word.Length := VAL(TokenLength,SHORTCARD);
   END GetUpper;
 
PROCEDURE yyStart (State: yyStateRange) =
   BEGIN
      yyPreviousStart   := yyStartState;
      yyStartState      := State;
   END yyStart;
 
PROCEDURE yyPrevious() =
   VAR s        : yyStateRange;
   BEGIN
      s               := yyStartState;
      yyStartState    := yyPreviousStart;
      yyPreviousStart := s;
   END yyPrevious;
 
PROCEDURE yyEcho() =
   VAR i        : INTEGER;
   BEGIN
      FOR i := yyChBufferIndex - TokenLength TO yyChBufferIndex - 1 DO
         ReuseIO.WriteC (ReuseIO.StdOutput, yyChOpenBufferPtr^ [i]);
      END;
   END yyEcho;
 
PROCEDURE yyLess (n: INTEGER) =
   BEGIN
      DEC (yyChBufferIndex, TokenLength - n);
      TokenLength := n;
   END yyLess;
 
PROCEDURE yyTab() =
   BEGIN
      DEC (yyLineStart, yyTabSpace - 1 - ((yyChBufferIndex - yyLineStart - 2) MOD yyTabSpace));
   END yyTab;

PROCEDURE yyTab1 (a: INTEGER) =
   BEGIN
      DEC (yyLineStart, yyTabSpace - 1 - ((yyChBufferIndex - yyLineStart - TokenLength + a - 1) MOD yyTabSpace));
   END yyTab1;

PROCEDURE yyTab2 (a, b: INTEGER) =
   BEGIN
      DEC (yyLineStart, yyTabSpace - 1 - ((yyChBufferIndex - yyLineStart - TokenLength + a - 1) MOD yyTabSpace));
   END yyTab2;

PROCEDURE yyEol (Column: INTEGER) =
   BEGIN
      INC (yyLineCount);
      INC (yyTotalLineCount);
      yyLineStart := yyChBufferIndex - 1 - Column;
   END yyEol;

PROCEDURE output (c: CHAR) =
   BEGIN
      ReuseIO.WriteC (ReuseIO.StdOutput, c);
   END output;

PROCEDURE unput (c: CHAR) =
   BEGIN
      DEC (yyChBufferIndex);
      yyChOpenBufferPtr^ [yyChBufferIndex] := c;
   END unput;

PROCEDURE input (): CHAR =
   BEGIN
      IF yyChBufferIndex = (yyChBufferStart + yyBytesRead) THEN
         IF NOT yyEof THEN
            DEC (yyLineStart, yyBytesRead);
            DEC (yyLineStart, yyChBufferStart); (* RMB *)
            yyChBufferIndex := 0;
            yyChBufferStart := 0;

            yyBytesRead := Source.GetLine 
                    (yySourceFile, yyChBufferPtr
                    , General.Exp2 (General.Log2 (yyChBufferSize))
                    );

(* WAS:      yyBytesRead := Source.GetLine 
                    (yySourceFile, yyChBufferPtr
                    , VAL(Word.TGeneral.Exp2 (General.Log2 (yyChBufferSize)),)
                    );
*)

            IF yyBytesRead <= 0 THEN yyBytesRead := 0; yyEof := TRUE; END;
            yyChOpenBufferPtr^ [yyBytesRead    ] := yyEobCh;
            yyChOpenBufferPtr^ [yyBytesRead + 1] := '\000';
         END;
      END;
      IF yyChBufferIndex = (yyChBufferStart + yyBytesRead) THEN
         RETURN '\000';
      ELSE
         INC (yyChBufferIndex);
         RETURN yyChOpenBufferPtr^ [yyChBufferIndex - 1];
      END
   END input;

(* VISIBLE: *) 
PROCEDURE UpperCase ( Ch : CHAR ) : CHAR  = 
   BEGIN
     RETURN yyToUpper [ Ch ]; 
   END UpperCase;

(* VISIBLE: *) 
PROCEDURE LowerCase ( Ch : CHAR ) : CHAR  = 
   BEGIN
     RETURN yyToLower [ Ch ]; 
   END LowerCase;

(* VISIBLE *) 
PROCEDURE TotalLineCount ( ) : Word.T  =  
   BEGIN
     RETURN yyTotalLineCount 
   END TotalLineCount;  

PROCEDURE BeginScanner() =
   BEGIN
(* line 209 "../src/input.rex" *)
 BraceNestingLevel := 0 ; CommentNestingLevel := 0 ; 
    InsideCode := FALSE ; 
  
   END BeginScanner;
 
PROCEDURE CloseScanner() =
   BEGIN
   END CloseScanner;
 
PROCEDURE yyGetTables() =
   VAR
      BlockSize, j, n   : Word.T;
      TableFile : System.tFile;
      Base      : ARRAY yyStateRange OF yyTableRange;
   BEGIN
      BlockSize := 64000 DIV BYTESIZE (yyCombType);

      TRY
        TableFile := System.OpenInputT (ScanTabName);
      EXCEPT
        OSError.E (code)
        => Errors.ErrLine ("Unable to open scanner table file " & ScanTabName );
      END;

      Checks.ErrorCheckT ("yyGetTables.OpenInput", TableFile);
      IF ((yyGetTable (TableFile, ADR (Base[FIRST(Base)]      )) DIV BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount) OR
         ((yyGetTable (TableFile, ADR (yyDefault[FIRST(yyDefault)] )) DIV BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount) OR
         ((yyGetTable (TableFile, ADR (yyEobTrans[FIRST(yyEobTrans)])) DIV BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount)
         THEN
         yyErrorMessage (2);
      END;
      n := 0;
      j := 0;
      WHILE j <= yyTableSize DO
         INC (n, yyGetTable (TableFile, ADR (yyComb [VAL(j,SHORTCARD)])) DIV BYTESIZE (yyCombType));
         INC (j, BlockSize);
      END;
      IF n # (yyTableSize + 1) THEN yyErrorMessage (2); END;
      System.Close (TableFile);

      FOR i := 0 TO yyDStateCount DO
         yyBasePtr [i] := LOOPHOLE (ADR (yyComb [Base [i]]),M2LONGCARD);
      END;
   END yyGetTables;

(*As once was: ------------------------------------------------------------------**
PROCEDURE yyGetTables() =
   VAR
      BlockSize, j, n   : Word.T;
      TableFile : System.tFile;
      i         : yyStateRange;
      Base      : ARRAY yyStateRange OF yyTableRange;
   BEGIN
      BlockSize := 64000 DIV BYTESIZE (yyCombType);
      TableFile := System.OpenInputT (ScanTabName);
      FrontChecks.ErrorCheckT ("yyGetTables.OpenInput", TableFile);
      IF ((yyGetTable (TableFile, ADR (Base[FIRST(Base)]      )) DIV BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount) OR
         ((yyGetTable (TableFile, ADR (yyDefault[FIRST(yyDefault)] )) DIV BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount) OR
         ((yyGetTable (TableFile, ADR (yyEobTrans[FIRST(yyEobTrans)])) DIV BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount)
         THEN
         yyErrorMessage (2);
      END;
      n := 0;
      j := 0;
      WHILE j <= yyTableSize DO
         INC (n, yyGetTable (TableFile, ADR (yyComb [VAL(j,SHORTCARD)])) DIV BYTESIZE (yyCombType));
         INC (j, BlockSize);
      END;
      IF n # (yyTableSize + 1) THEN yyErrorMessage (2); END;
      System.Close (TableFile);

      FOR i := 0 TO yyDStateCount DO
         yyBasePtr [i] := LOOPHOLE (ADR (yyComb [Base [i]]),LONGCARD);
      END;
   END yyGetTables;
** -----------------------------------------------------------------------------*)
 
PROCEDURE yyGetTable (TableFile: System.tFile; Address: ADDRESS): Word.T =
   VAR
      N         : INTEGER;
      Length    : yyTableElmt;
   BEGIN
      N := System.Read (TableFile, ADR (Length), BYTESIZE (yyTableElmt));
      FrontChecks.ErrorCheckT ("yyGetTable.Read1", N);
      N := System.Read (TableFile, Address, VAL(Length,INTEGER));
      FrontChecks.ErrorCheckT ("yyGetTable.Read2", N);
      RETURN Length;
   END yyGetTable;
 
PROCEDURE yyErrorMessage (ErrorCode: SHORTCARD) =
   BEGIN
      Positions.WritePosition (ReuseIO.StdError, Attribute.Position);
      CASE ErrorCode OF
   | 0=> ReuseIO.WriteT (ReuseIO.StdError, ": Scanner: internal error");
   | 1=> ReuseIO.WriteT (ReuseIO.StdError, ": Scanner: out of memory");
   | 2=> ReuseIO.WriteT (ReuseIO.StdError, ": Scanner: table mismatch");
   | 3=> ReuseIO.WriteT (ReuseIO.StdError, ": Scanner: too many nested include files");
   | 4=> ReuseIO.WriteT (ReuseIO.StdError, ": Scanner: file stack underflow (too many calls of CloseFile)");
   | 5=> ReuseIO.WriteT (ReuseIO.StdError, ": Scanner: cannot open input file");
      END;
      ReuseIO.WriteNl (ReuseIO.StdError); Exit();
   END yyErrorMessage;
 
PROCEDURE yyExit() =
   BEGIN
      ReuseIO.CloseIO(); System.Exit (1);
   END yyExit;

BEGIN
   ScanTabName          := "Scanner.Tab";
   Exit                 := yyExit;
   yyFileStackPtr       := 0;
   yyStartState         := 1;                   (* set up for auto init *)
   yyPreviousStart      := 1;
   yyBasePtr [yyStartState] := LOOPHOLE (ADR (yyComb [0]),M2LONGCARD);
   yyDefault [yyStartState] := yyDNoState;
   yyComb [0].Check     := yyDNoState;
   yyChBufferPtr        := LOOPHOLE(ADR (yyComb [0]), yytChBufferPtr); (* dirty trick *)
   yyChBufferIndex      := 1; 
   yyStateStackSize     := yyInitBufferSize;
   yyStateStack := NEW ( REF ARRAY OF yyStateRange, yyChBufferSize); 
(* WAS: DynArray.MakeArray (yyStateStack, yyStateStackSize, BYTESIZE (yyStateRange)); *)
   yyStateStack^ [0]    := yyDNoState;
   
   FOR yyCh := yyFirstCh TO yyLastCh DO yyToLower [yyCh] := yyCh; END;
   yyToUpper := yyToLower;
   FOR yyCh := 'A' TO 'Z' DO
      yyToLower [yyCh] := VAL (ORD (yyCh) - ORD ('A') + ORD ('a'),CHAR);
   END;
   FOR yyCh := 'a' TO 'z' DO
      yyToUpper [yyCh] := VAL (ORD (yyCh) - ORD ('a') + ORD ('A'),CHAR);
   END;
   yyStateStack := NIL;
END Scanner.

