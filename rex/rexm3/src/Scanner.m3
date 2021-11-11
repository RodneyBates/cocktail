
(* $Id: Scanner.mi,v 2.11 1992/09/24 13:14:00 grosch rel $ *)

(* Modified Rodney M. Bates 
   Mar 94 to compile under WRL 
   Mar 96 to fix a bug in PROCEDURE input 
   Mar 96 to add functions UpperCase and LowerCase, to exploit
          the arrays yyToUpper and yyToLower, already there.
   Apr 96 to add yyTotalLineCount and TotalLineCount. 
*) 

 UNSAFE MODULE Scanner;
 
FROM SYSTEM IMPORT SHORTCARD;
IMPORT Word, SYSTEM, Checks, System, General, Positions, ReuseIO. DynArray, Strings, Source;
(* line 84 "../src/rex.rex" *)



FROM Strings	IMPORT tString, Concatenate, Char, SubString,
			StringToInt, AssignEmpty, Length;
FROM Texts	IMPORT MakeText, Append;
FROM StringMem	IMPORT tStringRef, PutString;
FROM Idents	IMPORT tIdent, MakeIdent, NoIdent;
FROM Errors	IMPORT ErrorMessage, Error;
FROM ScanGen	IMPORT Language, tLanguage;
FROM Positions	IMPORT tPosition;

CONST
   SymIdent		= 1	;
   SymNumber		= 2	;
   SymString		= 3	;
   SymChar		= 4	;
   SymTargetcode	= 5	;
   SymScanner		= 37	;
   SymExport		= 32	;
   SymGlobal		= 6	;
   SymLocal		= 31	;
   SymBegin		= 7	;
   SymClose		= 8	;
   SymEof		= 34	;
   SymDefault		= 36	;
   SymDefine		= 9	;
   SymStart		= 10	;
   SymRules		= 11	;
   SymNot		= 30	;
   SymDot		= 12	;
   SymComma		= 13	;
   SymEqual		= 14	;
   SymColon		= 15	;
   SymColonMinus	= 35	;
   SymNrSign		= 33	;
   SymSlash		= 16	;
   SymBar		= 17	;
   SymPlus		= 18	;
   SymMinus		= 19	;
   SymAsterisk		= 20	;
   SymQuestion		= 21	;
   SymLParen		= 22	;
   SymRParen		= 23	;
   SymLBracket		= 24	;
   SymRBracket		= 25	;
   SymLBrace		= 26	;
   SymRBrace		= 27	;
   SymLess		= 28	;
   SymGreater		= 29	;

   BraceMissing		= 13	;
   UnclosedComment	= 14	;
   UnclosedString	= 16	;

VAR
   BraceNestingLevel , CommentNestingLevel	: INTEGER	;
   string	: tString	;
   NoString	: tStringRef	;
   TargetPos	: tPosition	;
   CommentPos	: tPosition	;
   StringPos	: tPosition	;
   PrevState	: SHORTCARD	;
   InsideTarget : BOOLEAN       ; 

PROCEDURE ErrorAttribute (Token: Word.T; VAR Attribute: tScanAttribute) =
   BEGIN
      CASE Token OF
      |  SymIdent	=> Attribute.Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 84
 $$ *)  := NoIdent;
      |  SymNumber	=> Attribute.Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 85
 $$ *) := 0;
      |  SymString	=> Attribute.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 86
 $$ *) := NoString;
      |  SymChar	=> Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 87
 $$ *)	   := '?';
      |  SymTargetcode	=> MakeText (Attribute.Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 88
 $$ *));
      ELSE
      END;
   END ErrorAttribute;

 
CONST
   yyTabSpace		= 8;
   yyDNoState		= 0;
   yyFileStackSize	= 16;
   yyInitBufferSize	= (1024 * 8) + 256;
yyFirstCh	= '\000';
yyLastCh	= '\377';
yyEolCh	= '\012';
yyEobCh	= '\177';
yyDStateCount	= 182;
yyTableSize	= 4468;
yyEobState	= 52;
yyDefaultState	= 53;
STD	= 1;
targetcode	= 3;
set	= 5;
rules	= 7;
CComment	= 9;
M2Comment	= 11;
Str1	= 13;
Str2	= 15;
CStr1	= 17;
CStr2	= 19;
 
TYPE
   yyTableElmt		= SHORTCARD;
   yyStateRange		= yyTableElmt [0 .. yyDStateCount];
   yyTableRange		= yyTableElmt [0 .. yyTableSize];
   yyCombType		= RECORD Check, Next: yyStateRange; END;
   yyCombTypePtr	= UNTRACED BRANDED REF  yyCombType;
   yytChBufferPtr	= UNTRACED BRANDED REF  ARRAY [0 .. 1000000] OF CHAR;
   yyChRange		= [yyFirstCh .. yyLastCh];
   yyFileStackPtrTyp    = SHORTCARD;
   yyFileStackSubscript = yyFileStackPtrTyp [1 .. yyFileStackSize];

VAR
   yyBasePtr		: ARRAY yyStateRange	OF M2LONGCARD	;
   yyDefault		: ARRAY yyStateRange	OF yyStateRange	;
   yyComb		: ARRAY yyTableRange	OF yyCombType	;
   yyEobTrans		: ARRAY yyStateRange	OF yyStateRange	;
   yyToLower, yyToUpper	: ARRAY yyChRange	OF CHAR		;

   yyStateStack		: UNTRACED BRANDED REF  ARRAY [0 .. 1000000] OF yyStateRange;
   yyStateStackSize	: M2LONGINT;
   yyStartState		: yyStateRange;
   yyPreviousStart	: yyStateRange;
   yyCh			: CHAR;
 
   yySourceFile		: System.tFile;
   yyEof		: BOOLEAN;
   yyChBufferPtr	: yytChBufferPtr;
   yyChBufferStart	: INTEGER;
   yyChBufferSize	: M2LONGINT;
   yyChBufferIndex	: INTEGER;
   yyBytesRead		: INTEGER;
   yyLineCount		: SHORTCARD; (* Number of the current line,
                                        of the current file. *) 
   yyTotalLineCount	: Word.T;  (* Number of lines already read,
                                        of all files. *) 
   yyLineStart		: INTEGER;

   yyFileStackPtr	: yyFileStackPtrTyp;
   yyFileStack		: ARRAY yyFileStackSubscript OF RECORD
   			     SourceFile		: System.tFile;
			     Eof		: BOOLEAN;
   			     ChBufferPtr	: yytChBufferPtr;
			     ChBufferStart	: INTEGER;
			     ChBufferSize	: M2LONGINT;
   			     ChBufferIndex	: INTEGER;
   			     BytesRead		: INTEGER;
   			     LineCount		: SHORTCARD;
   			     LineStart		: INTEGER;
			  END;

PROCEDURE GetToken (): INTEGER =
   VAR
      yyState		: yyStateRange;
      yyTablePtr	: yyCombTypePtr;
      yyRestartFlag	: BOOLEAN;
      yyi, yySource, yyTarget : INTEGER;
      yyChBufferFree	: M2LONGINT;

(* line 163 "../src/rex.rex" *)
 VAR TargetCode, String, Word: tString; 

    PROCEDURE AccumComment ( )  = 
    BEGIN
      IF InsideTarget AND ( BraceNestingLevel > 0 )
      THEN 
        GetWord (Word);
        Concatenate (TargetCode, Word);
      END (* IF *) 
    END AccumComment; 

  
BEGIN
   LOOP
      yyState		:= yyStartState;
      TokenLength 	:= 0;
 
      (* ASSERT yyChBuffer [yyChBufferIndex] = first character *)
 
      LOOP		(* eventually restart after sentinel *)
	 LOOP		(* execute as many state transitions as possible *)
	    					(* determine next state *)
	    yyTablePtr := LOOPHOLE (yyBasePtr [yyState] +
	       (VAL(ORD (yyChBufferPtr^ [yyChBufferIndex]),M2LONGCARD )
               * VAL( SYSTEM.BYTESIZE (yyCombType),M2LONGCARD)) ,yyCombTypePtr);
	    IF yyTablePtr^.Check # yyState THEN
	       yyState := yyDefault [yyState];
	       IF yyState = yyDNoState THEN EXIT; END;
	    ELSE
	       yyState := yyTablePtr^.Next;
	       INC (TokenLength);
	       yyStateStack^ [TokenLength] := yyState;	(* push state *)
	       INC (yyChBufferIndex);		(* get next character *)
	    END;
	 END;
 
	 LOOP					(* search for last final state *)
CASE yyStateStack^ [TokenLength] OF
|182
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 223 "../src/rex.rex" *)

			   IF BraceNestingLevel = 0 THEN
			      MakeText (Attribute.Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 222
 $$ *));
			      AssignEmpty (TargetCode);
			      TargetPos := Attribute.Position;
                              InsideTarget := TRUE; 
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			   INC (BraceNestingLevel);
			
yyRestartFlag := FALSE; EXIT;
|181
=>
(* line 236 "../src/rex.rex" *)

			   DEC (BraceNestingLevel);
			   IF BraceNestingLevel = 0 THEN
			      yyStart (PrevState);
                              InsideTarget := FALSE; 
			      Append (Attribute.Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 241
 $$ *), TargetCode);
			      Attribute.Position := TargetPos;
			      RETURN SymTargetcode;
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			
yyRestartFlag := FALSE; EXIT;
|34
,45
,57
,65
,73
,164
,170
=>
(* line 251 "../src/rex.rex" *)

			   IF BraceNestingLevel > 0 THEN
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			
yyRestartFlag := FALSE; EXIT;
|180
=>
(* line 258 "../src/rex.rex" *)

			   IF BraceNestingLevel > 0 THEN
			      Strings.Append (TargetCode, '\011');
			   END;
			   yyTab();
			
yyRestartFlag := FALSE; EXIT;
|179
=>
(* line 265 "../src/rex.rex" *)

			   IF BraceNestingLevel > 0 THEN
			      Append (Attribute.Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 281
 $$ *), TargetCode);
			      AssignEmpty (TargetCode);
			   END;
			   yyEol (0);
			
yyRestartFlag := FALSE; EXIT;
|35
=>
(* line 273 "../src/rex.rex" *)

			   IF BraceNestingLevel > 0 THEN
			      GetWord (Word);
			      Strings.Append (TargetCode, Char (Word, 2));
			   END;
			
yyRestartFlag := FALSE; EXIT;
|32
=>
(* line 280 "../src/rex.rex" *)

			   IF BraceNestingLevel > 0 THEN
			      Strings.Append (TargetCode, '\');
			   END;
			
yyRestartFlag := FALSE; EXIT;
|178
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 288 "../src/rex.rex" *)

			   GetWord (String);
                           StringPos := Attribute.Position;
			   IF Language = tLanguage.C
			   THEN yyStart (CStr1);
			   ELSE yyStart (Str1);
			   END;
			
yyRestartFlag := FALSE; EXIT;
|177
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 297 "../src/rex.rex" *)

			   GetWord (String);
                           StringPos := Attribute.Position;
			   IF Language = tLanguage.C
			   THEN yyStart (CStr2);
			   ELSE yyStart (Str2);
			   END;
			
yyRestartFlag := FALSE; EXIT;
|24
,60
,68
,76
=>
(* line 309 "../src/rex.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|23
,61
,69
,77
=>
(* line 309 "../src/rex.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|22
,38
,48
,62
,70
,78
=>
(* line 309 "../src/rex.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|21
,37
,47
,63
,71
,79
=>
(* line 309 "../src/rex.rex" *)
GetWord (Word); Concatenate (String, Word);
yyRestartFlag := FALSE; EXIT;
|176
=>
(* line 312 "../src/rex.rex" *)
GetWord (Word); Concatenate (String, Word); yyEol (0);
yyRestartFlag := FALSE; EXIT;
|175
=>
(* line 312 "../src/rex.rex" *)
GetWord (Word); Concatenate (String, Word); yyEol (0);
yyRestartFlag := FALSE; EXIT;
|174
=>
(* line 315 "../src/rex.rex" *)
Strings.Append (String, Char (String, 1));
			    yyPrevious(); Concatenate (TargetCode, String);
			
yyRestartFlag := FALSE; EXIT;
|173
=>
(* line 315 "../src/rex.rex" *)
Strings.Append (String, Char (String, 1));
			    yyPrevious(); Concatenate (TargetCode, String);
			
yyRestartFlag := FALSE; EXIT;
|172
=>
(* line 319 "../src/rex.rex" *)
Strings.Append (String, '\011'); yyTab();
yyRestartFlag := FALSE; EXIT;
|171
=>
(* line 321 "../src/rex.rex" *)
ErrorMessage (UnclosedString, Error, StringPos);
			    Strings.Append (String, Char (String, 1));
			    yyEol (0); yyPrevious(); Concatenate (TargetCode, String);
			
yyRestartFlag := FALSE; EXIT;
|169
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 329 "../src/rex.rex" *)
 yyStart (M2Comment)	;
       AccumComment ( ) ; 
       CommentNestingLevel := 1 ; 
       CommentPos := Attribute.Position; 
     
yyRestartFlag := FALSE; EXIT;
|168
=>
(* line 335 "../src/rex.rex" *)
 INC ( CommentNestingLevel ) ; AccumComment ( ) ; 
yyRestartFlag := FALSE; EXIT;
|166
=>
(* line 337 "../src/rex.rex" *)
 AccumComment ( ) ; 
                             DEC ( CommentNestingLevel ) ; 
                             IF CommentNestingLevel = 0 THEN yyPrevious ( ) END ; 
                           
yyRestartFlag := FALSE; EXIT;
|25
,39
,59
,67
,75
,165
,167
=>
(* line 342 "../src/rex.rex" *)
 AccumComment ( ) ; 
yyRestartFlag := FALSE; EXIT;
|163
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 347 "../src/rex.rex" *)
 yyStart (CComment)	;
       AccumComment ( ) ; 
       CommentPos := Attribute.Position; 
     
yyRestartFlag := FALSE; EXIT;
|161
=>
(* line 352 "../src/rex.rex" *)
 AccumComment ( ) ; yyPrevious() ; 
yyRestartFlag := FALSE; EXIT;
|26
,40
,58
,66
,74
=>
(* line 354 "../src/rex.rex" *)
 AccumComment ( ) ; 
yyRestartFlag := FALSE; EXIT;
|160
=>
(* line 359 "../src/rex.rex" *)

			   IF InsideTarget AND ( BraceNestingLevel > 0 ) 
                           THEN
			      Strings.Append (TargetCode, '\011');
			   END;
			   yyTab();
			
yyRestartFlag := FALSE; EXIT;
|159
=>
(* line 368 "../src/rex.rex" *)

			   IF InsideTarget AND ( BraceNestingLevel > 0 ) 
                           THEN
			      Append (Attribute.Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 483
 $$ *), TargetCode);
			      AssignEmpty (TargetCode);
			   END;
			   yyEol (0);
			
yyRestartFlag := FALSE; EXIT;
|158
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 377 "../src/rex.rex" *)
PrevState := STD; yyStart (targetcode); RETURN SymExport	;
yyRestartFlag := FALSE; EXIT;
|153
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 378 "../src/rex.rex" *)
PrevState := STD; yyStart (targetcode); RETURN SymGlobal	;
yyRestartFlag := FALSE; EXIT;
|147
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 379 "../src/rex.rex" *)
PrevState := STD; yyStart (targetcode); RETURN SymLocal	;
yyRestartFlag := FALSE; EXIT;
|142
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 380 "../src/rex.rex" *)
PrevState := STD; yyStart (targetcode); RETURN SymBegin	;
yyRestartFlag := FALSE; EXIT;
|137
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 381 "../src/rex.rex" *)
PrevState := STD; yyStart (targetcode); RETURN SymClose	;
yyRestartFlag := FALSE; EXIT;
|132
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 382 "../src/rex.rex" *)
PrevState := STD; yyStart (targetcode); RETURN SymDefault	;
yyRestartFlag := FALSE; EXIT;
|128
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 383 "../src/rex.rex" *)
PrevState := STD; yyStart (targetcode); RETURN SymEof	;
yyRestartFlag := FALSE; EXIT;
|125
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 384 "../src/rex.rex" *)
RETURN SymScanner	;
yyRestartFlag := FALSE; EXIT;
|119
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 385 "../src/rex.rex" *)
RETURN SymDefine	;
yyRestartFlag := FALSE; EXIT;
|113
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 386 "../src/rex.rex" *)
RETURN SymStart	;
yyRestartFlag := FALSE; EXIT;
|36
,46
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 387 "../src/rex.rex" *)
yyStart (rules);	RETURN SymRules		;
yyRestartFlag := FALSE; EXIT;
|108
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 388 "../src/rex.rex" *)
RETURN SymNot	;
yyRestartFlag := FALSE; EXIT;
|28
,43
,49
,50
,106
,107
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
,129
,130
,131
,133
,134
,135
,136
,138
,139
,140
,141
,143
,144
,145
,146
,148
,149
,150
,151
,152
,154
,155
,156
,157
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 390 "../src/rex.rex" *)

			   GetWord (Word);
			   Attribute.Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 626
 $$ *)  := MakeIdent (Word);
			   RETURN SymIdent;
			
yyRestartFlag := FALSE; EXIT;
|29
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 396 "../src/rex.rex" *)

			   GetWord (Word);
			   Attribute.Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 637
 $$ *) := StringToInt (Word);
			   RETURN SymNumber;
			
yyRestartFlag := FALSE; EXIT;
|33
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 402 "../src/rex.rex" *)

			   GetWord (Word);
			   SubString (Word, 2, Length (Word) - 1, TargetCode);
			   Attribute.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 649
 $$ *) := PutString (TargetCode);
			   RETURN SymString;
			
yyRestartFlag := FALSE; EXIT;
|105
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 409 "../src/rex.rex" *)
RETURN SymDot	;
yyRestartFlag := FALSE; EXIT;
|104
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 410 "../src/rex.rex" *)
RETURN SymEqual	;
yyRestartFlag := FALSE; EXIT;
|103
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 411 "../src/rex.rex" *)
yyPrevious();		RETURN SymRBrace	;
yyRestartFlag := FALSE; EXIT;
|102
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 412 "../src/rex.rex" *)
RETURN SymMinus	;
yyRestartFlag := FALSE; EXIT;
|101
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 413 "../src/rex.rex" *)
RETURN SymComma	;
yyRestartFlag := FALSE; EXIT;
|100
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 414 "../src/rex.rex" *)
RETURN SymBar	;
yyRestartFlag := FALSE; EXIT;
|99
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 415 "../src/rex.rex" *)
RETURN SymPlus	;
yyRestartFlag := FALSE; EXIT;
|98
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 416 "../src/rex.rex" *)
RETURN SymAsterisk	;
yyRestartFlag := FALSE; EXIT;
|97
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 417 "../src/rex.rex" *)
RETURN SymQuestion	;
yyRestartFlag := FALSE; EXIT;
|96
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 418 "../src/rex.rex" *)
RETURN SymLParen	;
yyRestartFlag := FALSE; EXIT;
|95
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 419 "../src/rex.rex" *)
RETURN SymRParen	;
yyRestartFlag := FALSE; EXIT;
|94
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 420 "../src/rex.rex" *)
RETURN SymLBracket	;
yyRestartFlag := FALSE; EXIT;
|93
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 421 "../src/rex.rex" *)
RETURN SymRBracket	;
yyRestartFlag := FALSE; EXIT;
|92
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 422 "../src/rex.rex" *)
yyStart (set);	RETURN SymLBrace	;
yyRestartFlag := FALSE; EXIT;
|91
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 423 "../src/rex.rex" *)
RETURN SymNrSign	;
yyRestartFlag := FALSE; EXIT;
|90
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 424 "../src/rex.rex" *)
RETURN SymSlash	;
yyRestartFlag := FALSE; EXIT;
|89
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 425 "../src/rex.rex" *)
RETURN SymLess	;
yyRestartFlag := FALSE; EXIT;
|88
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 426 "../src/rex.rex" *)
RETURN SymGreater	;
yyRestartFlag := FALSE; EXIT;
|86
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 427 "../src/rex.rex" *)
PrevState := rules; yyStart (targetcode); RETURN SymColon;
yyRestartFlag := FALSE; EXIT;
|87
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 428 "../src/rex.rex" *)
PrevState := rules; yyStart (targetcode); RETURN SymColonMinus;
yyRestartFlag := FALSE; EXIT;
|85
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 430 "../src/rex.rex" *)
Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 798
 $$ *) := '\012'; RETURN SymChar;
yyRestartFlag := FALSE; EXIT;
|84
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 431 "../src/rex.rex" *)
Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 805
 $$ *) := '\011'; RETURN SymChar;
yyRestartFlag := FALSE; EXIT;
|83
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 432 "../src/rex.rex" *)
Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 812
 $$ *) := '\013'; RETURN SymChar;
yyRestartFlag := FALSE; EXIT;
|82
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 433 "../src/rex.rex" *)
Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 819
 $$ *) := '\010'; RETURN SymChar;
yyRestartFlag := FALSE; EXIT;
|81
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 434 "../src/rex.rex" *)
Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 826
 $$ *) := '\015'; RETURN SymChar;
yyRestartFlag := FALSE; EXIT;
|80
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 435 "../src/rex.rex" *)
Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 833
 $$ *) := '\014'; RETURN SymChar;
yyRestartFlag := FALSE; EXIT;
|31
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 437 "../src/rex.rex" *)

			   GetWord (Word);
			   SubString (Word, 2, Length (Word), TargetCode);
			   Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 843
 $$ *) := VAL (LOOPHOLE (StringToInt (TargetCode),Word.T),CHAR);
	  		   RETURN SymChar;
			
yyRestartFlag := FALSE; EXIT;
|30
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 444 "../src/rex.rex" *)

			   GetWord (Word);
			   Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 854
 $$ *) := Char (Word, 2);
	  		   RETURN SymChar;
			
yyRestartFlag := FALSE; EXIT;
|27
,41
,42
,162
=>
Attribute.Position.Line   := yyLineCount;
Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart - TokenLength,SHORTCARD);
(* line 450 "../src/rex.rex" *)

			   GetWord (Word);
			   Attribute.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 868
 $$ *) := Char (Word, 1);
	  		   RETURN SymChar;
			
yyRestartFlag := FALSE; EXIT;
|72
=>
(* line 456 "../src/rex.rex" *)

yyRestartFlag := FALSE; EXIT;
|64
=>
(* line 457 "../src/rex.rex" *)

yyRestartFlag := FALSE; EXIT;
|56
=>
(* BlankAction *)
WHILE yyChBufferPtr^ [yyChBufferIndex] = ' ' DO INC (yyChBufferIndex); END;
yyRestartFlag := FALSE; EXIT;
|55
=>
(* TabAction *)
DEC (yyLineStart, 7 - ((yyChBufferIndex - yyLineStart - 2) MOD 8));
yyRestartFlag := FALSE; EXIT;
|54
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
,44
,51
=>
	    (* non final states *)
		  DEC (yyChBufferIndex);	(* return character *)
		  DEC (TokenLength)		(* pop state *)
 
| 53=>
		  Attribute.Position.Line   := yyLineCount;
		  Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart,SHORTCARD);
		  INC (yyChBufferIndex);
		  TokenLength := 1;
ReuseIO.WriteC (ReuseIO.StdOutput, yyChBufferPtr^ [yyChBufferIndex-1]);
	          yyRestartFlag := FALSE; EXIT;

	    |  yyDNoState	=>		(* automatic initialization *)
		  yyGetTables();
		  yyStateStack^ [0] := yyDefaultState; (* stack underflow sentinel *)
		  IF yyFileStackPtr = 0 THEN
		     yyInitialize();
		     yySourceFile := System.StdInput;
		  END;
	          yyRestartFlag := FALSE; EXIT;

| 52=>
		  DEC (yyChBufferIndex);	(* undo last state transition *)
		  DEC (TokenLength);		(* get previous state *)
		  IF TokenLength = 0 THEN
		     yyState := yyStartState;
		  ELSE
		     yyState := yyStateStack^ [TokenLength];
		  END;

		  IF yyChBufferIndex # (yyChBufferStart + yyBytesRead) THEN
		     yyState := yyEobTrans [yyState];	(* end of buffer sentinel in buffer *)
		     IF yyState # yyDNoState THEN
			INC (yyChBufferIndex);
			INC (TokenLength);
			yyStateStack^ [TokenLength] := yyState;
			yyRestartFlag := TRUE; EXIT;
		     END;
		  ELSE				(* end of buffer reached *)

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

		     IF NOT yyEof THEN		(* read buffer and restart *)
			yyChBufferFree 
                          := VAL(  
                                 General.Exp2 
                                  (General.Log2 
                                     (yyChBufferSize - 4 - VAL(General.MaxAlign,M2LONGINT) -VAL( TokenLength,M2LONGINT))
                                  ),M2LONGINT
                                );
			IF yyChBufferFree < (yyChBufferSize DIV 8) THEN
			   DynArray.ExtendArray (yyChBufferPtr, yyChBufferSize, SYSTEM.BYTESIZE (CHAR));
			   IF yyChBufferPtr = NIL THEN yyErrorMessage (1); END;
			   yyChBufferFree 
                             := VAL ( 
                                     General.Exp2 
                                        (General.Log2 
                                           (yyChBufferSize - 4 - VAL(General.MaxAlign,M2LONGINT) - VAL(TokenLength,M2LONGINT))
                                        ),M2LONGINT
                                    );
			   IF yyStateStackSize < yyChBufferSize THEN
			      DynArray.ExtendArray (yyStateStack, yyStateStackSize, SYSTEM.BYTESIZE (yyStateRange));
			      IF yyStateStack = NIL THEN yyErrorMessage (1); END;
			   END;
			END;
			yyChBufferIndex := yyChBufferStart;
			yyBytesRead := Source.GetLine 
                                 (yySourceFile
                                  , SYSTEM.ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1001
 $$ *) (yyChBufferPtr^ [yyChBufferIndex])
                                  , VAL ( Word.T  yyChBufferFree, )
                                  );
			IF yyBytesRead <= 0 THEN yyBytesRead := 0; yyEof := TRUE; END;
			yyChBufferPtr^ [yyChBufferStart + yyBytesRead    ] := yyEobCh;
			yyChBufferPtr^ [yyChBufferStart + yyBytesRead + 1] := '\000';
			yyRestartFlag := TRUE; EXIT;
		     END;

		     IF TokenLength = 0 THEN	(* end of file reached *)
			Attribute.Position.Line   := yyLineCount;
			Attribute.Position.Column := VAL(yyChBufferIndex - yyLineStart,SHORTCARD);
			CloseFile();
			IF yyFileStackPtr = 0 THEN
(* line 184 "../src/rex.rex" *)

   CASE yyStartState OF
   | targetcode	, set	
     => ErrorMessage ( BraceMissing , Error , TargetPos );
   | CComment , M2Comment	
     => ErrorMessage ( UnclosedComment , Error , CommentPos );
       IF InsideTarget 
       THEN 
         ErrorMessage ( BraceMissing , Error , TargetPos ) 
       END (* IF *) ; 
   | CStr1, CStr2, Str1, Str2
     => ErrorMessage ( UnclosedString , Error , StringPos );
       IF InsideTarget 
       THEN 
         ErrorMessage ( BraceMissing , Error , TargetPos ) 
       END (* IF *) ; 
   ELSE
   END;
   yyStart (STD);

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
      IF yyStateStack^ [0] = yyDNoState THEN	(* have tables been read in ? *)
	 yyGetTables();
	 yyStateStack^ [0] := yyDefaultState;	(* stack underflow sentinel *)
      END;
      yyInitialize();
      yySourceFile := Source.BeginSource (FileName);
      IF yySourceFile < 0 THEN yyErrorMessage (5); END;
   END BeginFile;

PROCEDURE yyInitialize() =
   BEGIN
      IF yyFileStackPtr >= yyFileStackSize THEN yyErrorMessage (3); END;
      INC (yyFileStackPtr);			(* push file *)
      WITH m2tom3_with_11=yyFileStack [yyFileStackPtr] DO
	 m2tom3_with_11.SourceFile	:= yySourceFile		;
	 m2tom3_with_11.Eof		:= yyEof		;
	 m2tom3_with_11.ChBufferPtr	:= yyChBufferPtr	;
	 m2tom3_with_11.ChBufferStart	:= yyChBufferStart	;
	 m2tom3_with_11.ChBufferSize	:= yyChBufferSize	;
	 m2tom3_with_11.ChBufferIndex	:= yyChBufferIndex	;
	 m2tom3_with_11.BytesRead	:= yyBytesRead		;
	 m2tom3_with_11.LineCount	:= yyLineCount		;
	 m2tom3_with_11.LineStart	:= yyLineStart		;
      END;
						(* initialize file state *)
      yyChBufferSize	:= yyInitBufferSize;
      DynArray.MakeArray (yyChBufferPtr, yyChBufferSize, SYSTEM.BYTESIZE (CHAR));
      IF yyChBufferPtr = NIL THEN yyErrorMessage (1); END;
      yyChBufferStart	:= General.MaxAlign;
      yyChBufferPtr^ [yyChBufferStart - 1] := yyEolCh; (* begin of line indicator *)
      yyChBufferPtr^ [yyChBufferStart    ] := yyEobCh; (* end of buffer sentinel *)
      yyChBufferPtr^ [yyChBufferStart + 1] := '\000';
      yyChBufferIndex	:= yyChBufferStart;
      yyEof		:= FALSE;
      yyBytesRead	:= 0;
      yyLineCount	:= 1;
      yyTotalLineCount	:= 0;
      yyLineStart	:= yyChBufferStart - 1;
   END yyInitialize;

PROCEDURE CloseFile() =
   BEGIN
      IF yyFileStackPtr = 0 THEN yyErrorMessage (4); END;
      Source.CloseSource (yySourceFile);
      DynArray.ReleaseArray (yyChBufferPtr, yyChBufferSize, SYSTEM.BYTESIZE (CHAR));
      WITH m2tom3_with_12=yyFileStack [yyFileStackPtr] DO	(* pop file *)
	 yySourceFile	:= m2tom3_with_12.SourceFile		;
	 yyEof		:= m2tom3_with_12.Eof			;
	 yyChBufferPtr	:= m2tom3_with_12.ChBufferPtr		;
	 yyChBufferStart:= m2tom3_with_12.ChBufferStart	;
	 yyChBufferSize	:= m2tom3_with_12.ChBufferSize		;
	 yyChBufferIndex:= m2tom3_with_12.ChBufferIndex	;
	 yyBytesRead	:= m2tom3_with_12.BytesRead		;
	 yyLineCount	:= m2tom3_with_12.LineCount		;
	 yyLineStart	:= m2tom3_with_12.LineStart		;
      END;
      DEC (yyFileStackPtr);		
   END CloseFile;

PROCEDURE GetWord (VAR Word: Strings.tString) =
   VAR i, WordStart	: INTEGER;
   BEGIN
      WordStart := yyChBufferIndex - TokenLength - 1;
      FOR i := 1 TO TokenLength DO
	 Word.Chars [VAL(i,Strings.tStringIndex)] 
           := yyChBufferPtr^ [WordStart + i];
      END;
      Word.Length := VAL(TokenLength,SHORTCARD);
   END GetWord;
 
PROCEDURE GetLower (VAR Word: Strings.tString) =
   VAR i, WordStart	: INTEGER;
   BEGIN
      WordStart := yyChBufferIndex - TokenLength - 1;
      FOR i := 1 TO TokenLength DO
	 Word.Chars [VAL(i,Strings.tStringIndex)] 
           := yyToLower [yyChBufferPtr^ [WordStart + i]];
      END;
      Word.Length := VAL(TokenLength,SHORTCARD);
   END GetLower;
 
PROCEDURE GetUpper (VAR Word: Strings.tString) =
   VAR i, WordStart	: INTEGER;
   BEGIN
      WordStart := yyChBufferIndex - TokenLength - 1;
      FOR i := 1 TO TokenLength DO
	 Word.Chars [VAL(i,Strings.tStringIndex)] 
           := yyToUpper [yyChBufferPtr^ [WordStart + i]];
      END;
      Word.Length := VAL(TokenLength,SHORTCARD);
   END GetUpper;
 
PROCEDURE yyStart (State: yyStateRange) =
   BEGIN
      yyPreviousStart	:= yyStartState;
      yyStartState	:= State;
   END yyStart;
 
PROCEDURE yyPrevious() =
   VAR s	: yyStateRange;
   BEGIN
      s		      := yyStartState;
      yyStartState    := yyPreviousStart;
      yyPreviousStart := s;
   END yyPrevious;
 
PROCEDURE yyEcho() =
   VAR i	: INTEGER;
   BEGIN
      FOR i := yyChBufferIndex - TokenLength TO yyChBufferIndex - 1 DO
	 ReuseIO.WriteC (ReuseIO.StdOutput, yyChBufferPtr^ [i]);
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
      yyChBufferPtr^ [yyChBufferIndex] := c;
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
                    , VAL(Word.TGeneral.Exp2 (General.Log2 (yyChBufferSize)),)
                    );
	    IF yyBytesRead <= 0 THEN yyBytesRead := 0; yyEof := TRUE; END;
	    yyChBufferPtr^ [yyBytesRead    ] := yyEobCh;
	    yyChBufferPtr^ [yyBytesRead + 1] := '\000';
	 END;
      END;
      IF yyChBufferIndex = (yyChBufferStart + yyBytesRead) THEN
	 RETURN '\000';
      ELSE
	 INC (yyChBufferIndex);
	 RETURN yyChBufferPtr^ [yyChBufferIndex - 1];
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
(* line 177 "../src/rex.rex" *)
 BraceNestingLevel := 0;
    CommentNestingLevel := 0;
    AssignEmpty (string);
    NoString := PutString (string);
  
   END BeginScanner;
 
PROCEDURE CloseScanner() =
   BEGIN
   END CloseScanner;
 
PROCEDURE yyGetTables() =
   VAR
      BlockSize, j, n	: Word.T;
      TableFile	: System.tFile;
      i		: yyStateRange;
      Base	: ARRAY yyStateRange OF yyTableRange;
   BEGIN
      BlockSize	:= 64000 DIV SYSTEM.BYTESIZE (yyCombType);
      TableFile := System.OpenInput (ScanTabName);
      Checks.ErrorCheck (ARRAY [0..21] OF CHAR{'y','y','G','e','t','T','a','b','l','e','s','.','O','p','e','n','I','n','p','u','t','\000'}, TableFile);
      IF ((yyGetTable (TableFile, SYSTEM.ADR (Base[FIRST(Base)]      )) DIV SYSTEM.BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount) OR
         ((yyGetTable (TableFile, SYSTEM.ADR (yyDefault[FIRST(yyDefault)] )) DIV SYSTEM.BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount) OR
         ((yyGetTable (TableFile, SYSTEM.ADR (yyEobTrans[FIRST(yyEobTrans)])) DIV SYSTEM.BYTESIZE (yyTableElmt) - 1) 
         # yyDStateCount)
	 THEN
	 yyErrorMessage (2);
      END;
      n := 0;
      j := 0;
      WHILE j <= yyTableSize DO
         INC (n, yyGetTable (TableFile, SYSTEM.ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1284
 $$ *) (yyComb [VAL(j,SHORTCARD)])) DIV SYSTEM.BYTESIZE (yyCombType));
         INC (j, BlockSize);
      END;
      IF n # (yyTableSize + 1) THEN yyErrorMessage (2); END;
      System.Close (TableFile);

      FOR i := 0 TO yyDStateCount DO
	 yyBasePtr [i] := LOOPHOLE (SYSTEM.ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1291
 $$ *) (yyComb [Base [i]]),M2LONGCARD);
      END;
   END yyGetTables;
 
PROCEDURE yyGetTable (TableFile: System.tFile; Address: SYSTEM.ADDRESS): Word.T =
   VAR
      N		: INTEGER;
      Length	: yyTableElmt;
   BEGIN
      N := System.Read (TableFile, SYSTEM.ADR (Length), SYSTEM.BYTESIZE (yyTableElmt));
      Checks.ErrorCheck (ARRAY [0..16] OF CHAR{'y','y','G','e','t','T','a','b','l','e','.','R','e','a','d','1','\000'}, N);
      N := System.Read (TableFile, Address, VAL(Length,INTEGER));
      Checks.ErrorCheck (ARRAY [0..16] OF CHAR{'y','y','G','e','t','T','a','b','l','e','.','R','e','a','d','2','\000'}, N);
      RETURN VAL(Word.TLength,);
   END yyGetTable;
 
PROCEDURE yyErrorMessage (ErrorCode: SHORTCARD) =
   BEGIN
      Positions.WritePosition (ReuseIO.StdError, Attribute.Position);
      CASE ErrorCode OF
   | 0=> ReuseIO.WriteS (ReuseIO.StdError, ARRAY [0..25] OF CHAR{':',' ','S','c','a','n','n','e','r',':',' ','i','n','t','e','r','n','a','l',' ','e','r','r','o','r','\000'});
   | 1=> ReuseIO.WriteS (ReuseIO.StdError, ARRAY [0..24] OF CHAR{':',' ','S','c','a','n','n','e','r',':',' ','o','u','t',' ','o','f',' ','m','e','m','o','r','y','\000'});
   | 2=> ReuseIO.WriteS (ReuseIO.StdError, ARRAY [0..25] OF CHAR{':',' ','S','c','a','n','n','e','r',':',' ','t','a','b','l','e',' ','m','i','s','m','a','t','c','h','\000'});
   | 3=> ReuseIO.WriteS (ReuseIO.StdError, ARRAY [0..40] OF CHAR{':',' ','S','c','a','n','n','e','r',':',' ','t','o','o',' ','m','a','n','y',' ','n','e','s','t','e','d',' ','i','n','c','l','u','d','e',' ','f','i','l','e','s','\000'});
   | 4=> ReuseIO.WriteS (ReuseIO.StdError, ARRAY [0..61] OF CHAR{':',' ','S','c','a','n','n','e','r',':',' ','f','i','l','e',' ','s','t','a','c','k',' ','u','n','d','e','r','f','l','o','w',' ','(','t','o','o',' ','m','a','n','y',' ','c','a','l','l','s',' ','o','f',' ','C','l','o','s','e','F','i','l','e',')','\000'});
   | 5=> ReuseIO.WriteS (ReuseIO.StdError, ARRAY [0..33] OF CHAR{':',' ','S','c','a','n','n','e','r',':',' ','c','a','n','n','o','t',' ','o','p','e','n',' ','i','n','p','u','t',' ','f','i','l','e','\000'});
      END;
      ReuseIO.WriteNl (ReuseIO.StdError); Exit();
   END yyErrorMessage;
 
PROCEDURE yyExit() =
   BEGIN
      ReuseIO.CloseReuseIO.); System.Exit (1);
   END yyExit;

BEGIN
   SUBARRAY(ScanTabName		, 0, 11) := ARRAY [0..10] OF CHAR{'S','c','a','n','n','e','r','.','T','a','b'};
IF NUMBER(ScanTabName) > 11 THEN ScanTabName[FIRST(ScanTabName) + 11] := '\000'; END
;
   Exit			:= yyExit;
   yyFileStackPtr	:= 0;
   yyStartState		:= 1;			(* set up for auto init *)
   yyPreviousStart	:= 1;
   yyBasePtr [yyStartState] := LOOPHOLE (SYSTEM.ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1332
 $$ *) (yyComb [0]),M2LONGCARD);
   yyDefault [yyStartState] := yyDNoState;
   yyComb [0].Check	:= yyDNoState;
   yyChBufferPtr	:= SYSTEM.ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1335
 $$ *) (yyComb [0]);	(* dirty trick *)
   yyChBufferIndex	:= 1;				(* dirty trick *)
   yyStateStackSize	:= yyInitBufferSize;
   DynArray.MakeArray (yyStateStack, yyStateStackSize, SYSTEM.BYTESIZE (yyStateRange));
   yyStateStack^ [0]	:= yyDNoState;
   
   FOR yyCh := yyFirstCh TO yyLastCh DO yyToLower [yyCh] := yyCh; END;
   yyToUpper := yyToLower;
   FOR yyCh := 'A' TO 'Z' DO
      yyToLower [yyCh] := VAL (ORD (yyCh) - ORD ('A') + ORD ('a'),CHAR);
   END;
   FOR yyCh := 'a' TO 'z' DO
      yyToUpper [yyCh] := VAL (ORD (yyCh) - ORD ('a') + ORD ('A'),CHAR);
   END;
END Scanner.

