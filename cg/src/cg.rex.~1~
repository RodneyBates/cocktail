/* Ich, Doktor Josef Grosch, Informatiker, 20.3.1989 */

EXPORT  {

FROM StringMem	IMPORT tStringRef	;
FROM Idents	IMPORT tIdent	;
FROM Texts	IMPORT tText	;
FROM Positions	IMPORT tPosition;

TYPE
   tScanAttribute = RECORD
	   Position	: tPosition	;
      CASE : INTEGER OF
      | 1: StringRef	: tStringRef	;
      | 2: Ident	: tIdent	;
      | 3: Integer	: INTEGER	;
      | 4: Text		: tText		;
      END;
   END;

VAR CurArg, ArgCount	: INTEGER;

PROCEDURE ErrorAttribute (Token: CARDINAL; VAR Attribute: tScanAttribute);
}

GLOBAL  {

FROM SYSTEM	IMPORT ADR;
FROM System	IMPORT GetArgument;
FROM StringMem	IMPORT PutString;
FROM Strings	IMPORT tString, Concatenate, Char, SubString, ArrayToString,
			StringToInt, AssignEmpty, Length;
FROM Idents	IMPORT MakeIdent, NoIdent, GetStringRef;
FROM Texts	IMPORT MakeText, Append;
FROM Tree	IMPORT Options, ErrorCount, SourceFile;
FROM Sets	IMPORT IsElement;
FROM Positions	IMPORT tPosition;

IMPORT Errors;

CONST
   TokIdentifier 	= 1;
   TokInteger 		= 2;
   TokString 		= 3;
   TokTargetCode	= 4;
   TokCode		= 5;
   TokWhiteSpace	= 7;

   TokAfter		= 24;
   TokBefore		= 25;
   TokBegin		= 10;
   TokCheck		= 26;
   TokClose		= 11;
   TokDeclare		= 12;
   TokDemand		= 28;
   TokEnd		= 13;
   TokEval		= 14;
   TokExport		= 15;
   TokFor		= 71;
   TokFunction		= 6;
   TokGlobal		= 16;
   TokIgnore		= 72;
   TokImport		= 30;
   TokInherited		= 34;
   TokInput		= 31;
   TokLeft		= 37;
   TokLocal		= 18;
   TokModule		= 19;
   TokNone		= 39;
   TokOutput		= 32;
   TokParser		= 35;
   TokPrec		= 36;
   TokProperty		= 70;
   TokRemote		= 76;
   TokReverse		= 21;
   TokRight		= 38;
   TokRule		= 22;
   TokScanner		= 77;
   TokSelect		= 74;
   TokStack		= 20;
   TokSubunit		= 75;
   TokSynthesized	= 33;
   TokThread		= 27;
   TokTree		= 23;
   TokView		= 78;
   TokVirtual		= 17;

   TokLParent		= 40;	(* '('			*)
   TokRParent		= 41;	(* ')'			*)
   TokLBracket		= 42;	(* '['			*)
   TokRBracket		= 43;	(* ']'			*)
   TokLBrace		= 44;	(* '{'			*)
   TokRBrace		= 45;	(* '}'			*)
   TokComma		= 46;	(* ','			*)
   TokSemiColon		= 47;	(* ';'			*)
   TokDot		= 48;	(* '.'			*)
   TokColon		= 49;	(* ':'			*)
   TokEqual		= 50;	(* '='			*)
   TokBar		= 51;	(* '|'			*) (* ? *)
   TokAssign		= 52;	(* ':='			*)
   TokPlus		= 53;	(* '+'			*) (* ? *)
   TokMinus		= 54;	(* '-'			*) (* ? *)
   TokAsterisk		= 55;	(* '*'			*) (* ? *)
   TokSlash		= 56;	(* '/'			*) (* ? *)
   TokLAngle		= 57;	(* '<'			*)
   TokRAngle		= 58;	(* '>'			*)
   TokRArrow		= 59;	(* '->'			*)
   TokCopy		= 60;	(* ':-'			*)
   TokArrow		= 61;	(* '==>'		*)
   TokLArrow		= 62;	(* '<-'			*)

PROCEDURE ErrorAttribute (Token: CARDINAL; VAR Attribute: tScanAttribute);
   BEGIN
      WITH Attribute DO
	 CASE Token OF
	 | TokIdentifier: Ident		:= NoIdent;
	 | TokInteger	: Integer	:= 0;
	 | TokTargetCode: MakeText (Text);
	 | TokString
   	 , TokCode
   	 , TokWhiteSpace: StringRef	:= GetStringRef (NoIdent);
	 ELSE
	 END;
      END;
   END ErrorAttribute;

VAR NestingLevel: INTEGER; Position: tPosition;
}

LOCAL	{
VAR
   String, Word, TargetCode: tString;
   Argument	: ARRAY [0..255] OF CHAR;
   j		: SHORTCARD;
   ch		: CHAR;
}

BEGIN	{ NestingLevel := 0; }

DEFAULT	{
   GetWord (Word);
   Errors.MessageI ("illegal character", Errors.Error, Attribute.Position, Errors.String, ADR (Word));
   INC (ErrorCount);
}

EOF     {
   CASE yyStartState OF
   | targetcode	,
     expr	: Errors.Message ("unclosed target code", Errors.Error, Attribute.Position);
		  INC (ErrorCount);

   | comment	: Errors.Message ("unclosed comment", Errors.Error, Attribute.Position);
		  INC (ErrorCount);

   | CStr1, CStr2,
     Str1, Str2	: Errors.Message ("unclosed string", Errors.Error, Attribute.Position);
		  INC (ErrorCount);
   ELSE
   END;
   yyStart (STD);
   INC (CurArg);
   IF CurArg <= ArgCount THEN
      GetArgument (CurArg, Argument);
      j := 0;
      REPEAT
	 ch := Argument [j];
	 SourceFile [j] := ch;
	 INC (j);
      UNTIL ch = 0C;
      BeginFile (SourceFile);
      ArrayToString (SourceFile, String);
      Attribute.Position.File := MakeIdent (String);
   END;
}

DEFINE  letter  = {A-Z a-z _}	.
        digit   = {0-9}		.
	CmtCh   = - {*\t\n}	.
	StrCh1	= - {'\t\n}	.
	StrCh2	= - {"\t\n}	.
	CStrCh1	= - {'\t\n\\}	.
	CStrCh2	= - {"\t\n\\}	.
	code	= - {{\}\t\n\\'"} .
	anyExpr	= - {\ \\\t\n/'":;={\}a-zA-Z} .

START	comment, Str1, Str2, CStr1, CStr2, targetcode, expr

RULES

#targetcode#	"{"	: {
			   IF NestingLevel = 0 THEN
			      MakeText (Attribute.Text);
			      AssignEmpty (TargetCode);
			      Position := Attribute.Position;
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			   INC (NestingLevel);
			}

#targetcode#	"}"	:- {
			   DEC (NestingLevel);
			   IF NestingLevel = 0 THEN
			      yyStart (STD);
			      Append (Attribute.Text, TargetCode);
			      Attribute.Position := Position;
			      RETURN TokTargetCode;
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			}

#targetcode#	code +	:- {
			   IF NestingLevel > 0 THEN
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			}

#targetcode#	\t	:- {
			   IF NestingLevel > 0 THEN
			      Strings.Append (TargetCode, 11C);
			   END;
			   yyTab;
			}

#targetcode#	\n	:- {
			   IF NestingLevel > 0 THEN
			      Append (Attribute.Text, TargetCode);
			      AssignEmpty (TargetCode);
			   END;
			   yyEol (0);
			}

#targetcode#	\\ ANY	:- {
			   IF NestingLevel > 0 THEN
			      GetWord (Word);
			      Strings.Append (TargetCode, Char (Word, 2));
			   END;
			}

#targetcode#	\\	:- {
			   IF NestingLevel > 0 THEN
			      Strings.Append (TargetCode, '\');
			   END;
			}

#STD, expr# "/*"	:- {yyStart (comment);}
#comment# "*/"		:- {yyPrevious;}
#comment# "*" | CmtCh +	:- {}

#STD# \f | \r		:- {}

#STD#	digit +		:  {GetWord (Word);
	                   Attribute.Integer := StringToInt (Word);
			   RETURN TokInteger;}

#STD, expr, targetcode# ' :{GetWord (String);
			    IF IsElement (ORD ('c'), Options)
			    THEN yyStart (CStr1);
			    ELSE yyStart (Str1);
			    END;}

#STD, expr, targetcode# \":{GetWord (String);
			    IF IsElement (ORD ('c'), Options)
			    THEN yyStart (CStr2);
			    ELSE yyStart (Str2);
			    END;}

#Str1#	StrCh1 +	,
#Str2#	StrCh2 +	,
#CStr1#	CStrCh1 + | \\ ANY ? ,
#CStr2#	CStrCh2 + | \\ ANY ? :- {GetWord (Word); Concatenate (String, Word);}

#CStr1#	\\ \n		,
#CStr2#	\\ \n		:- {GetWord (Word); Concatenate (String, Word); yyEol (0);}

#Str1, CStr1# '		,
#Str2, CStr2# \"	:- {Strings.Append (String, Char (String, 1));
			    yyPrevious;
			    IF yyStartState = targetcode THEN
			       Concatenate (TargetCode, String);
			    ELSE
			       Attribute.StringRef := PutString (String);
			       RETURN TokString;
			    END;}

#Str1, Str2, CStr1, CStr2# \t :- {Strings.Append (String, 11C); yyTab;}

#Str1, Str2, CStr1, CStr2# \n :- {
			    Errors.Message ("unclosed string", Errors.Error, Attribute.Position);
			    INC (ErrorCount);
			    Strings.Append (String, Char (String, 1));
			    yyEol (0); yyPrevious;
			    IF yyStartState = targetcode THEN
			       Concatenate (TargetCode, String);
			    ELSE
			       Attribute.StringRef := PutString (String);
			       RETURN TokString;
			    END;}

#STD# "(" 		: {RETURN TokLParent		;}
#STD# ")" 		: {RETURN TokRParent		;}
#STD# ","		: {RETURN TokComma		;}
#STD# "->"		: {RETURN TokRArrow		;}
#STD# "."		: {RETURN TokDot		;}
#STD# ":"		: {RETURN TokColon		;}
#STD# "<"		: {RETURN TokLAngle		;}
#STD# "<-"		: {RETURN TokLArrow		;}
#STD# "="		: {RETURN TokEqual		;}
#STD# ">"		: {RETURN TokRAngle		;}
#STD# "["		: {RETURN TokLBracket		;}
#STD# "]"		: {RETURN TokRBracket		;}
#STD# "{"		: {yyStart (expr); INC (NestingLevel); RETURN TokLBrace;}

#expr# AFTER		: {RETURN TokAfter		;}
#expr# BEFORE		: {RETURN TokBefore		;}
#expr# CHECK		: {RETURN TokCheck		;}
#expr# REMOTE		: {RETURN TokRemote		;}

#expr# anyExpr *	: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   RETURN TokCode;}

#STD, expr# ":="	: {IF NestingLevel <= 1 THEN
			      RETURN TokAssign;
			   ELSE
			      GetWord (Word);
			      Attribute.StringRef := PutString (Word);
			      RETURN TokCode;
			   END;}

#expr# ":-"		: {IF NestingLevel <= 1 THEN
			      RETURN TokCopy;
			   ELSE
			      GetWord (Word);
			      Attribute.StringRef := PutString (Word);
			      RETURN TokCode;
			   END;}

#expr# ";"		: {IF NestingLevel <= 1 THEN
			      RETURN TokSemiColon;
			   ELSE
			      GetWord (Word);
			      Attribute.StringRef := PutString (Word);
			      RETURN TokCode;
			   END;}

#expr# ":"		: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   RETURN TokColon;}

#expr# "=" ? "=>"	: {RETURN TokArrow;}

#expr# "{"		: {INC (NestingLevel);
			   IF NestingLevel <= 2 THEN
			      RETURN TokLBrace;
			   ELSE
			      GetWord (Word);
			      Attribute.StringRef := PutString (Word);
			      RETURN TokCode;
			   END;}

#expr# "}"		: {DEC (NestingLevel);
			   IF NestingLevel = 0 THEN yyStart (STD); END;
			   IF NestingLevel <= 1 THEN
			      RETURN TokRBrace;
			   ELSE
			      GetWord (Word);
			      Attribute.StringRef := PutString (Word);
			      RETURN TokCode;
			   END;}

#expr# "/"		: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   RETURN TokCode		;}

#expr# "="		: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   RETURN TokCode		;}

#expr# " " +		: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   RETURN TokWhiteSpace		;}

#expr# \n		: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   yyEol (0);
			   RETURN TokWhiteSpace		;}

#expr# \t		: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   yyTab;
			   RETURN TokWhiteSpace		;}

#expr# \\ ANY		: {GetWord (Word);
			   SubString (Word, 2, 2, String);
			   Attribute.StringRef := PutString (String);
			   RETURN TokCode		;}

#expr# \\ letter (letter | digit) *: {GetWord (Word);
			   SubString (Word, 2, Length (Word), String);
			   Attribute.StringRef := PutString (String);
			   RETURN TokCode		;}

#expr# \\		: {GetWord (Word);
			   Attribute.StringRef := PutString (Word);
			   RETURN TokCode		;}

#STD# BEGIN		: {yyStart (targetcode); RETURN TokBegin	;}
#STD# CLOSE		: {yyStart (targetcode); RETURN TokClose	;}
#STD# DECLARE		: {RETURN TokDeclare		;}
#STD# DEMAND		: {RETURN TokDemand		;}
#STD# END		: {RETURN TokEnd		;}
#STD# EVAL		: {RETURN TokEval		;}
#STD# EXPORT		: {yyStart (targetcode); RETURN TokExport	;}
#STD# FOR		: {RETURN TokFor		;}
#STD# FUNCTION		: {RETURN TokFunction		;}
#STD# GLOBAL		: {yyStart (targetcode); RETURN TokGlobal	;}
#STD# IGNORE		: {RETURN TokIgnore		;}
#STD# IMPORT		: {yyStart (targetcode); RETURN TokImport	;}
#STD# IN PUT ?		: {RETURN TokInput		;}
#STD# INH ERITED ?	: {RETURN TokInherited		;}
#STD# LEFT		: {RETURN TokLeft		;}
#STD# LOCAL		: {yyStart (targetcode); RETURN TokLocal	;}
#STD# MODULE		: {RETURN TokModule		;}
#STD# NONE		: {RETURN TokNone		;}
#STD# OUT PUT ?		: {RETURN TokOutput		;}
#STD# PARSER		: {RETURN TokParser		;}
#STD# PREC		: {RETURN TokPrec		;}
#STD# PROPERTY		: {RETURN TokProperty		;}
#STD# REV ERSE ?	: {RETURN TokReverse		;}
#STD# RIGHT		: {RETURN TokRight		;}
#STD# RULE		: {RETURN TokRule		;}
#STD# SCANNER		: {RETURN TokScanner		;}
#STD# SELECT		: {RETURN TokSelect		;}
#STD# STACK		: {RETURN TokStack		;}
#STD# SUBUNIT		: {RETURN TokSubunit		;}
#STD# SYN THESIZED ?	: {RETURN TokSynthesized	;}
#STD# THREAD		: {RETURN TokThread		;}
#STD# TREE		: {RETURN TokTree		;}
#STD# VIEW		: {RETURN TokView		;}
#STD# VIRTUAL | VOID	: {RETURN TokVirtual		;}

#STD, expr# letter (letter | digit) *	: {GetWord (Word);
	                   Attribute.Ident := MakeIdent (Word);
			   RETURN TokIdentifier;}

#STD# \\ letter (letter | digit) *	: {GetWord (Word);
			   SubString (Word, 2, Length (Word), String);
	                   Attribute.Ident := MakeIdent (String);
			   RETURN TokIdentifier;}
