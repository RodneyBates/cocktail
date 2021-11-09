/*
 *	ell2 - a redesign of ell
 *
 *	$RCSfile: ell.rex,v $
 *	
 *	purpose:	scanner specification
 *
 *	$Author: grosch $
 *	$Date: 1992/08/07 15:32:36 $
 */

EXPORT { 
FROM Idents	IMPORT tIdent;
FROM StringMem	IMPORT tStringRef;
FROM Positions	IMPORT tPosition;

TYPE tScanAttribute = RECORD
		     Position : tPosition;
		     CASE :INTEGER OF
		     | 0 : value : INTEGER;
		     | 1 : ident : tIdent;
		     | 2 : ref   : tStringRef;
		     END;
		   END;

CONST NoValue = -1;

VAR
  Epsilon	: tIdent;
  EndOfToken	: tIdent;
  NoIdent	: tIdent;
  NoString	: tStringRef;

PROCEDURE ErrorAttribute (Token : INTEGER; VAR Attribute : tScanAttribute);
}

GLOBAL {
FROM Strings	IMPORT tString, Concatenate, AssignEmpty, ArrayToString,
		       StringToInt, SubString, Append, Length, Char;
FROM Idents	IMPORT MakeIdent;
FROM StringMem	IMPORT PutString;
FROM Errors	IMPORT ErrorMessage;
FROM ArgCheck	IMPORT tLanguage, LANGUAGE;

CONST
  SymEqual	= 1;
  SymColon	= 2;
  SymPoint	= 3;
  SymOr		= 4;
  SymStar	= 5;
  SymPlus	= 6;
  SymList	= 7;
  SymLBrace	= 8;
  SymRBrace	= 9;
  SymLBracket	= 10;
  SymRBracket	= 11;
  SymEXPORT	= 12;
  SymGLOBAL	= 13;
  SymLOCAL	= 14;
  SymBEGIN	= 15;
  SymCLOSE	= 16;
  SymTOKEN	= 17;
  SymOPER	= 18;
  SymNONE	= 19;
  SymLEFT	= 20;
  SymRIGHT	= 21;
  SymRULE	= 22;
  SymPREC	= 23;
  SymNumber	= 24;
  SymAction	= 25;
  SymActionEnd	= 26;
  SymIdent	= 27;
  SymString	= 28;
  SymSCANNER	= 29;
  SymPARSER	= 30;

  eStringExceedsInput	= 20;
  eCommentNotClosed	= 21;
  eActionNotClosed	= 22;
  eStringExceedsLine	= 23;
  eBackSlashInAct	= 24;
  eIllegalChar		= 25;

  eError		= 3;

VAR 
  Level		: INTEGER;
  TargetCode, s	: tString;

PROCEDURE ErrorAttribute (Token : INTEGER; VAR Attribute : tScanAttribute);
  BEGIN
    CASE Token OF
    | SymNumber : Attribute.value := NoValue;
    | SymAction, SymActionEnd : Attribute.ref := NoString;
    | SymIdent, SymString : Attribute.ident := NoIdent;
    ELSE
    END;
  END ErrorAttribute;
}

LOCAL { VAR String, Word: tString; }

BEGIN {
ArrayToString ('_Epsilon'	, s); Epsilon	:= MakeIdent (s);
ArrayToString ('_EndOfFile'	, s); EndOfToken:= MakeIdent (s);
ArrayToString ('_ErrorId'	, s); NoIdent	:= MakeIdent (s);
ArrayToString ('_ErrorStr'	, s); NoString	:= PutString (s);
}

EOF {
CASE yyStartState OF
| CStr1, CStr2, Str1, Str2 :
    ErrorMessage (eStringExceedsInput, eError, Attribute.Position);
    Append (String, Char (String, 1));
    Attribute.ident := MakeIdent (String);
    yyStart (STD);
    yyEol (0);
    RETURN SymString;
| Comment1, Comment2 :
    ErrorMessage (eCommentNotClosed, eError, Attribute.Position);
| Action :
    ErrorMessage (eActionNotClosed, eError, Attribute.Position);
    Attribute.ref := PutString (TargetCode);
    yyStart (STD);
    RETURN (SymActionEnd);
ELSE
END;
}

DEFINE 
  letter	= {A-Z a-z _}	.
  digit		= {0-9}		.
  StrCh1	= - {'\t\n}	.
  StrCh2	= - {"\t\n}	.
  CStrCh1	= - {'\t\n\\}	.
  CStrCh2	= - {"\t\n\\}	.

START Action, Str1, Str2, CStr1, CStr2, Comment1, Comment2

RULES

#STD# "="	: { RETURN SymEqual	; }
#STD# ":"	: { RETURN SymColon	; }
#STD# "."	: { RETURN SymPoint	; }
#STD# "|"	: { RETURN SymOr	; }
#STD# "*"	: { RETURN SymStar	; }
#STD# "+"	: { RETURN SymPlus	; }
#STD# "||"	: { RETURN SymList	; }
#STD# "("	: { RETURN SymLBrace	; }
#STD# ")"	: { RETURN SymRBrace	; }
#STD# "["	: { RETURN SymLBracket	; }
#STD# "]"	: { RETURN SymRBracket	; }
#STD# "BEGIN"	: { RETURN SymBEGIN	; }
#STD# "CLOSE"	: { RETURN SymCLOSE	; }
#STD# "EXPORT"	: { RETURN SymEXPORT	; }
#STD# "GLOBAL"	: { RETURN SymGLOBAL	; }
#STD# "LEFT"	: { RETURN SymLEFT	; }
#STD# "LOCAL"	: { RETURN SymLOCAL	; }
#STD# "NONE"	: { RETURN SymNONE	; }
#STD# "OPER"	: { RETURN SymOPER	; }
#STD# "PARSER"	: { RETURN SymPARSER	; }
#STD# "PREC"	: { RETURN SymPREC	; }
#STD# "RIGHT"	: { RETURN SymRIGHT	; }
#STD# "RULE"	: { RETURN SymRULE	; }
#STD# "SCANNER"	: { RETURN SymSCANNER	; }
#STD# "TOKEN"	: { RETURN SymTOKEN	; }

#STD# digit + :	{
		GetWord (Word);
		Attribute.value := StringToInt (Word);
		RETURN SymNumber;
		}

#STD# \\ letter (letter | digit) * : {
		GetWord (Word);
		SubString (Word, 2, Length (Word), String);
		Attribute.ident := MakeIdent (String);
		RETURN SymIdent;
		}

#STD# letter (letter | digit) * : {
		GetWord (Word);
		Attribute.ident := MakeIdent (Word);
		RETURN SymIdent;
		}

#STD# \f | \r	:- {}

#STD# "{"	: { Level := 0; yyStart (Action); AssignEmpty (TargetCode); }
#STD# "(*"	: { Level := 0; yyStart (Comment1); }
#STD# "/*"	: { yyStart (Comment2); }
#STD# -{\n\t\ '"}:{ ErrorMessage (eIllegalChar, eError, Attribute.Position); }

#STD, Action# ' : { GetWord (String);
		    IF LANGUAGE = C
		    THEN yyStart (CStr1);
		    ELSE yyStart (Str1);
		    END;}

#STD, Action# \": { GetWord (String);
		    IF LANGUAGE = C
		    THEN yyStart (CStr2);
		    ELSE yyStart (Str2);
		    END;}

#Str1#	StrCh1  + | "''" +	,
#Str2#	StrCh2  + | \"\" +	,
#CStr1#	CStrCh1 + | \\ ANY ?	,
#CStr2#	CStrCh2 + | \\ ANY ? :- {GetWord (Word); Concatenate (String, Word);}

#CStr1#	\\ \n		,
#CStr2#	\\ \n		:- {GetWord (Word); Concatenate (String, Word); yyEol (0);}

#Str1, CStr1# '		,
#Str2, CStr2# \"	:- {Append (String, Char (String, 1));
			    yyPrevious;
			    IF yyStartState = Action THEN
			       Concatenate (TargetCode, String);
			    ELSE
			       Attribute.ident := MakeIdent (String);
			       RETURN SymString;
			    END;}

#Str1, Str2, CStr1, CStr2# \t :- {Append (String, 11C); yyTab;}

#Str1, Str2, CStr1, CStr2# \n :- {
			    ErrorMessage (eStringExceedsLine, eError, Attribute.Position);
			    Append (String, Char (String, 1));
			    yyEol (0); yyPrevious;
			    IF yyStartState = Action THEN
			       Concatenate (TargetCode, String);
			    ELSE
			       Attribute.ident := MakeIdent (String);
			       RETURN SymString;
			    END;}

#Action# - {\n\t\\\{\}'"} + :- { GetWord (Word); Concatenate (TargetCode, Word); }

#Action# \n	:- {
		GetWord (Word);
		Concatenate (TargetCode, Word);
		Attribute.ref := PutString (TargetCode);
		AssignEmpty (TargetCode);
		yyEol (0);
		RETURN (SymAction);
		}

#Action# \t	:- { yyTab; GetWord (Word); Concatenate (TargetCode, Word); }

#Action# \\ ANY :- { GetWord (Word); Append (TargetCode, Char (Word, 2)); }

#Action# \\	:- { ErrorMessage (eBackSlashInAct, eError, Attribute.Position); }

#Action# \{	:- { INC (Level); GetWord (Word); Concatenate (TargetCode, Word); }

#Action# \}	:- {
		IF Level = 0 THEN
		  Attribute.ref := PutString (TargetCode);
		  yyStart (STD);
		  RETURN (SymActionEnd);
		ELSE
		  DEC (Level);
		  GetWord (Word);
		  Concatenate (TargetCode, Word);
		END;
		}

#Comment1# ( - { \n \t \( \* } ) +	:- {}
#Comment1# "("		:- {}
#Comment1# "*"		:- {}
#Comment1# "(*"		:- { INC (Level); }
#Comment1# "*)"		:- { IF Level = 0 THEN yyStart (STD); ELSE DEC (Level); END; }

#Comment2# ( - { \n \t \* } ) +	:- {}
#Comment2# "*"		:- {}
#Comment2# "*/"		:- { yyStart (STD); }
