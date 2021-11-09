EXPORT {
FROM	Positions	IMPORT	tPosition;

TYPE tScanAttribute	= RECORD Position: tPosition; END;

VAR InfoFileName	: ARRAY [0..255] OF CHAR;
}

GLOBAL {
FROM	System		IMPORT	GetArgument,	GetArgCount;
FROM	Strings		IMPORT	tString,	AssignEmpty,	Append,
				Concatenate,	Length,		Char,
				IntToString,	StringToArray,	WriteS,
				ReadL,		WriteL,		IsEqual,
				ArrayToString;
FROM	StringMem	IMPORT	tStringRef,	PutString,	GetString;
FROM	Idents		IMPORT	tIdent,		NoIdent,	MakeIdent,
				MaxIdent,	InitIdents;
FROM 	IO		IMPORT	StdInput,	StdOutput,	StdError,
				tFile,		ReadOpen,	ReadClose,
				ReadI,		ReadC,		WriteC,
				WriteI,		WriteNl,	EndOfFile,
				CloseIO;

CONST	MissingInfo	= "rpp: cannot access file <Scanner>.rpp";

VAR	Level, l	: CARDINAL;
	StartString	: tString;
	TheWord		: tString;
	IsCollecting	: BOOLEAN;
	BothFlag	: BOOLEAN;
	Returning	: BOOLEAN;
	InsText		: tString;
	InfoFile	: tFile;
	LastIdent	: tIdent;
	TokenCode	: ARRAY [0..1023] OF SHORTCARD;
	TokenSelector	: ARRAY [0..1023] OF tStringRef;
	Not1, Not2, Not3: tString;
	Any1, Any2, Any3: tString;
	Argument	: ARRAY [0 .. 127] OF CHAR;
	i		: SHORTCARD;
	Language	: (Modula, C);

PROCEDURE Skip;
BEGIN
  REPEAT
    ReadL (InfoFile, TheWord);
    l := Length (TheWord);
  UNTIL ((l = 2) OR (l = 3)) AND (Char (TheWord, 1) = '%') AND (Char (TheWord, 2) = '%');
END Skip;

PROCEDURE DoText;
BEGIN
  IF NOT IsCollecting THEN yyEcho;
  ELSIF Level > 0 THEN GetWord (TheWord); Concatenate (InsText, TheWord);
  END;
END DoText;

PROCEDURE DoIdent;
VAR i: tIdent;
BEGIN
  GetWord (TheWord);
  i := MakeIdent (TheWord);
  IF i <= LastIdent THEN
    IF Returning THEN
      IntToString (TokenCode [i], TheWord);
    ELSE
      GetString (TokenSelector [i], TheWord);
    END;
    IF IsCollecting THEN
      Concatenate (InsText, TheWord);
    ELSE
      WriteS (StdOutput, TheWord);
    END;
  ELSE
    IF IsCollecting THEN
      Concatenate (InsText, TheWord);
    ELSE
      yyEcho;
    END;
  END;
END DoIdent;

PROCEDURE CopyText;
BEGIN
  LOOP
    ReadL (InfoFile, TheWord);
    l := Length (TheWord);
    IF ((l = 2) OR (l = 3)) AND (Char (TheWord, 1) = '%') AND (Char (TheWord, 2) = '%') THEN EXIT; END;
    WriteL (StdOutput, TheWord);
  END;
END CopyText;

PROCEDURE GenPosition;
BEGIN
  CASE Language OF
  | Modula: IO.WriteS (StdOutput, "FROM Positions IMPORT tPosition;");
  | C	  : IO.WriteS (StdOutput, '# include "Positions.h"');
  ELSE
  END;
  WriteNl (StdOutput);
END GenPosition;

PROCEDURE GenScanAttr;
BEGIN
  InfoFile := ReadOpen (InfoFileName);
  ReadL (InfoFile, TheWord);
  CopyText;
  ReadClose (InfoFile);
END GenScanAttr;

PROCEDURE GenErrorAttr;
BEGIN
  InfoFile := ReadOpen (InfoFileName);
  Skip;
  CopyText;
  ReadClose (InfoFile);
END GenErrorAttr;

PROCEDURE ReadIdents;
VAR	t, i	: INTEGER;
	c	: CHAR;
	Ident	: tIdent;
	Selector: ARRAY [0..255] OF CHAR;
	String	: tString;
BEGIN
  InfoFile := ReadOpen (InfoFileName);
  IF InfoFile < 0 THEN
     IO.WriteS (StdError, MissingInfo); WriteNl (StdError); CloseIO; HALT;
  END;
  ReadL (InfoFile, TheWord);
  CASE Char (TheWord, 1) OF
  | 'm' : Language := Modula;
  | 'c' : Language := C;
  ELSE
  END;
  Skip;
  Skip;
  WHILE NOT EndOfFile (InfoFile) DO
    t := ReadI (InfoFile);
    c := ReadC (InfoFile);
    c := ReadC (InfoFile);
    c := ReadC (InfoFile);
    i := 0;
    REPEAT
       Selector [i] := ReadC (InfoFile);
       INC (i);
    UNTIL Selector [i-1] = ' ';
    Selector [i-1] := 0C;
    ArrayToString (Selector, String);
    ReadL (InfoFile, TheWord);
    Ident := MakeIdent (TheWord);
    TokenCode [Ident] := t;
    TokenSelector [Ident] := PutString (String);
  END;
  ReadClose (InfoFile);
  LastIdent := MaxIdent ();
END ReadIdents;

PROCEDURE InsertRules;
VAR	Code	: CARDINAL;
	c, Ch	: CHAR;
	Selector: ARRAY [0..255] OF CHAR;
	i	: CARDINAL;

  PROCEDURE WriteIdent (VAR TheWord : tString);
  VAR	s	: ARRAY [0..255] OF CHAR;
	j	: CARDINAL;
  BEGIN
    StringToArray (TheWord, s);
    s [Length (TheWord)] := "'";
    IF NOT BothFlag AND (
       IsEqual (TheWord, Not1) OR IsEqual (TheWord, Not2) OR IsEqual (TheWord, Not3) OR
       IsEqual (TheWord, Any1) OR IsEqual (TheWord, Any2) OR IsEqual (TheWord, Any3)) THEN
      WriteC (StdOutput, "\");
    END;
    IF (s [0] = "'") OR (s [0] = '"') THEN j := 1; ELSE j := 0; END;
    REPEAT
      IF BothFlag THEN
        CASE s [j] OF
	  'a'..'z' :
	    WriteC (StdOutput, "{");
	    WriteC (StdOutput, s [j]);
	    WriteC (StdOutput, CAP (s [j]));
	    WriteC (StdOutput, "}");
	| 'A'..'Z' :
	    WriteC (StdOutput, "{");
	    WriteC (StdOutput, CHR (ORD (s [j]) - ORD ('A') + ORD ('a')));
	    WriteC (StdOutput, s [j]);
	    WriteC (StdOutput, "}");
	| '0'..'9', '_' :
	    WriteC (StdOutput, s [j]);
	ELSE
	  WriteC (StdOutput, "\");
	  WriteC (StdOutput, s [j]);
	END;
      ELSE
	CASE s [j] OF
	  '0'..'9', 'A'..'Z', 'a'..'z', '_' : WriteC (StdOutput, s [j]);
	ELSE
	  WriteC (StdOutput, "\");
	  WriteC (StdOutput, s [j]);
	END;
      END;
      INC (j);
    UNTIL (s [j] = '"') OR (s [j] = "'");
  END WriteIdent;

BEGIN
  InfoFile := ReadOpen (InfoFileName);
  Skip;
  Skip;
  WHILE NOT EndOfFile (InfoFile) DO
    Code := ReadI (InfoFile);
    c := ReadC (InfoFile);
    Ch := ReadC (InfoFile);
    c := ReadC (InfoFile);
    i := 0;
    REPEAT
       Selector [i] := ReadC (InfoFile);
       INC (i);
    UNTIL Selector [i-1] = ' ';
    Selector [i-1] := 0C;
    ReadL (InfoFile, TheWord);
    IF Ch # 'S' THEN
       WriteS (StdOutput, StartString);
       WriteIdent (TheWord);
       WriteC (StdOutput, 11C);
       IO.WriteS (StdOutput, ": { ");
       WriteS (StdOutput, InsText);
       CASE Language OF
       | Modula	: IO.WriteS (StdOutput, "RETURN ");
       | C	: IO.WriteS (StdOutput, "return ");
       END;
       WriteI (StdOutput, Code, 0);
       IO.WriteS (StdOutput, "; }");
       WriteNl (StdOutput);
     END;
  END;
  ReadClose (InfoFile);
END InsertRules;
}

BEGIN {
InfoFileName := "Scanner.rpp";
Language := Modula;
IF GetArgCount () > 1 THEN GetArgument (1, ScanTabName); END;
IF GetArgCount () > 2 THEN GetArgument (2, InfoFileName); END;
IsCollecting := FALSE;
InitIdents;
ReadIdents;
AssignEmpty (InsText);
AssignEmpty (StartString);
ArrayToString ("NOT", Not1);
ArrayToString ("'NOT'", Not2);
ArrayToString ('"NOT"', Not3);
ArrayToString ("ANY", Any1);
ArrayToString ("'ANY'", Any2);
ArrayToString ('"ANY"', Any3);
}

DEFINE	letter	= {A-Z a-z _} .
	digit	= {0-9} .
	StartCh	= - {#\n} .
	StrCh1	= - {'\n} .
	StrCh2	= - {"\n} .
	WS	= {\ \t} + .

START	Return, Start, Action, Rules, Set

RULE

#STD#	 \{				:- { yyStart (Action); yyEcho; Level := 1; }
#STD#	 DEFINE | RULE			:- { yyStart (Rules); yyEcho; }

#Rules#	 \" StrCh2 + \"				:- { DoText; }
#Rules#	 INSERT WS RULES			:- { yyStart (Start); BothFlag := FALSE; }
#Rules#	 INSERT WS RULES WS CASE\-INSENSITIVE	:- { yyStart (Start); BothFlag := TRUE; }
#Rules#	 \: | \:\-				:- { yyStart (Action); yyEcho; Level := 0; }
#Rules#	 \{					:- { yyStart (Set); yyEcho; }

#Set#	 \}				:- { yyPrevious; yyEcho; }

#Start#  \n				:- { yyPrevious; InsertRules; }
#Start#	 "NOT" ? WS ? \# StartCh + \#	:- { yyPrevious; GetWord (StartString); InsertRules; }
#Start#  "NOT" ? WS ? \# StartCh + \# / WS ? \{	:- { GetWord (StartString);
			     yyStartState := Action; Level := 0; IsCollecting := TRUE; }
#Start#  WS ? / \{	:- { yyStartState := Action; Level := 0; IsCollecting := TRUE; }

#Action# INSERT WS tPosition		:- { GenPosition; }
#Action# INSERT WS tScanAttribute	:- { GenScanAttr; }
#Action# INSERT WS ErrorAttribute	:- { GenErrorAttr; }

#Action# \{				:- { DoText; INC (Level); }
#Action# \}				:- { DEC (Level);
					     IF Level > 0 THEN
					       DoText;
					     ELSE
					       yyPrevious;
					       IF IsCollecting THEN
						 InsertRules; IsCollecting := FALSE;
					       ELSE
						 yyEcho;
					       END;
					     END; }

#Action# Attribute\.		:- { yyStartState := Return; DoText; Returning := FALSE; }
#Action# RETURN | return	:- { yyStartState := Return; DoText; Returning := TRUE; }

#Return# (letter | digit) *		:- { yyStartState := Action; DoIdent; }
#Return# ' StrCh1 + ' | \" StrCh2 + \"	:- { yyStartState := Action; DoIdent; }

	 \\ ? ANY, WS, \n 		:- { DoText; }





