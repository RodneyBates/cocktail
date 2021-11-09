/* $Id: rex.rex,v 3.7 1992/09/29 19:02:45 grosch rel $ */

/* Rodney M. Bates 
   RMB Oct 96 - Added Modula-2 style comments (* ... *) , including
                nesting thereof.  
              - Changed to scan comments inside target code blocks properly.
                (previously, a quote inside a comment inside target
                 code gave a spurious "unclosed string" message.) 
   RMB July, 1999 Fixed failure to compute position of comment.
*/ 

/* $Log: rex.rex,v $
 * Revision 3.7  1992/09/29  19:02:45  grosch
 * abort execution upon errors during scanning
 *
 * Revision 3.6  1992/09/29  14:38:55  grosch
 * abort execution upon errors during scanning
 *
 * Revision 3.5  1992/08/11  11:51:51  grosch
 * moved PrevState from LOCAL to GLOBAL
 *
 * Revision 3.4  1992/08/07  15:11:08  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 3.3  1991/12/04  16:16:58  grosch
 * unified escape conventions for all tools
 *
 * Revision 3.2  1991/11/21  14:42:27  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.1  91/06/06  15:29:42  grosch
 * fixed bug in EOF secton: yyStart (STD);
 * 
 * Revision 3.0  91/04/04  18:08:10  grosch
 * introduced partitioning of character set
 * 
 * Revision 2.0  91/03/08  18:18:14  grosch
 * turned tables into initialized arrays (in C)
 * reduced case size
 * changed interface for source position
 * 
 * Revision 1.4  90/08/22  17:33:38  grosch
 * fixed bug with backslash in comments
 * 
 * Revision 1.3  90/05/17  11:17:47  grosch
 * allow RULE or RULES
 * 
 * Revision 1.2  89/02/23  15:56:12  grosch
 * added DEFAULT section
 * 
 * Revision 1.1  89/01/17  15:01:58  grosch
 * correction and redesign of source position handling
 * 
 * Revision 1.0  88/10/04  11:59:58  grosch
 * Initial revision
 * 
 */

/* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 */

EXPORT	{

FROM Idents	IMPORT tIdent	;
FROM StringMem	IMPORT tStringRef;
FROM Texts	IMPORT tText	;
FROM Positions	IMPORT tPosition;

TYPE
   tScanAttribute	= RECORD
	      Position	: tPosition	;
	 CASE : INTEGER OF
	 | 1: Ident	: tIdent	;
	 | 2: Number	: SHORTCARD	;
	 | 3: String	: tStringRef	;
	 | 4: Ch	: CHAR		;
	 | 5: Text	: tText		;
	 END;
      END;

PROCEDURE ErrorAttribute (Token: CARDINAL; VAR Attribute: tScanAttribute);
}

GLOBAL	{

FROM SYSTEM	IMPORT ADDRESS;
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

PROCEDURE ErrorAttribute (Token: CARDINAL; VAR Attribute: tScanAttribute);
   BEGIN
      CASE Token OF
      |  SymIdent	: Attribute.Ident  := NoIdent;
      |  SymNumber	: Attribute.Number := 0;
      |  SymString	: Attribute.String := NoString;
      |  SymChar	: Attribute.Ch	   := '?';
      |  SymTargetcode	: MakeText (Attribute.Text);
      ELSE
      END;
   END ErrorAttribute;
}

LOCAL	
  { VAR TargetCode, String, Word: tString; 

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
    AssignEmpty (string);
    NoString := PutString (string);
  }

EOF	
{
   CASE yyStartState OF
   | targetcode	, set	
     : ErrorMessage ( BraceMissing , Error , TargetPos );
   | CComment , M2Comment	
     : ErrorMessage ( UnclosedComment , Error , CommentPos );
       IF InsideTarget 
       THEN 
         ErrorMessage ( BraceMissing , Error , TargetPos ) 
       END (* IF *) ; 
   | CStr1, CStr2, Str1, Str2
     : ErrorMessage ( UnclosedString , Error , StringPos );
       IF InsideTarget 
       THEN 
         ErrorMessage ( BraceMissing , Error , TargetPos ) 
       END (* IF *) ; 
   ELSE
   END;
   yyStart (STD);
}

DEFINE
   letter	= {A-Z a-z}	.
   digit	= {0-9}		.
   string	= - {"\n}	.
   CCmtCh	= - {*\t\n}	.
   M2CmtCh	= - {*(\t\n}	.
   code		= - {\\\t\n{\}'"(/} .
   StrCh1	= - {'\t\n}	.
   StrCh2	= - {"\t\n}	.
   CStrCh1	= - {'\t\n\\}	.
   CStrCh2	= - {"\t\n\\}	.

START targetcode, set, rules, CComment, M2Comment, Str1, Str2, CStr1, CStr2

RULES

/* Target code: */ 

#targetcode#	"{"	: {
			   IF BraceNestingLevel = 0 THEN
			      MakeText (Attribute.Text);
			      AssignEmpty (TargetCode);
			      TargetPos := Attribute.Position;
                              InsideTarget := TRUE; 
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			   INC (BraceNestingLevel);
			}

#targetcode#	"}"	:- {
			   DEC (BraceNestingLevel);
			   IF BraceNestingLevel = 0 THEN
			      yyStart (PrevState);
                              InsideTarget := FALSE; 
			      Append (Attribute.Text, TargetCode);
			      Attribute.Position := TargetPos;
			      RETURN SymTargetcode;
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			}

#targetcode#	code +	| "(" | "/" 
                     :- {
			   IF BraceNestingLevel > 0 THEN
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			}

#targetcode#	\t	:- {
			   IF BraceNestingLevel > 0 THEN
			      Strings.Append (TargetCode, 11C);
			   END;
			   yyTab;
			}

#targetcode#	\n	:- {
			   IF BraceNestingLevel > 0 THEN
			      Append (Attribute.Text, TargetCode);
			      AssignEmpty (TargetCode);
			   END;
			   yyEol (0);
			}

#targetcode#	\\ ANY	:- {
			   IF BraceNestingLevel > 0 THEN
			      GetWord (Word);
			      Strings.Append (TargetCode, Char (Word, 2));
			   END;
			}

#targetcode#	\\	:- {
			   IF BraceNestingLevel > 0 THEN
			      Strings.Append (TargetCode, '\');
			   END;
			}

/* Strings: */ 

#targetcode#	'	: {
			   GetWord (String);
                           StringPos := Attribute.Position;
			   IF Language = C
			   THEN yyStart (CStr1);
			   ELSE yyStart (Str1);
			   END;
			}

#targetcode#	\"	: {
			   GetWord (String);
                           StringPos := Attribute.Position;
			   IF Language = C
			   THEN yyStart (CStr2);
			   ELSE yyStart (Str2);
			   END;
			}

#Str1#	StrCh1 +	,
#Str2#	StrCh2 +	,
#CStr1#	CStrCh1 + | \\ ANY ? ,
#CStr2#	CStrCh2 + | \\ ANY ? :- {GetWord (Word); Concatenate (String, Word);}

#CStr1#	\\ \n		,
#CStr2#	\\ \n		:- {GetWord (Word); Concatenate (String, Word); yyEol (0);}

#Str1, CStr1# '		,
#Str2, CStr2# \"	:- {Strings.Append (String, Char (String, 1));
			    yyPrevious; Concatenate (TargetCode, String);
			}

#Str1, Str2, CStr1, CStr2# \t :- {Strings.Append (String, 11C); yyTab;}

#Str1, Str2, CStr1, CStr2# \n :- {ErrorMessage (UnclosedString, Error, StringPos);
			    Strings.Append (String, Char (String, 1));
			    yyEol (0); yyPrevious; Concatenate (TargetCode, String);
			}

/* Modula2-style comments: */ 

#STD, rules, targetcode#	"(*"	
  :  { yyStart (M2Comment)	;
       AccumComment ( ) ; 
       CommentNestingLevel := 1 ; 
       CommentPos := Attribute.Position; 
     }

#M2Comment#	"(*"	:- { INC ( CommentNestingLevel ) ; AccumComment ( ) ; }

#M2Comment#	"*)"	:- { AccumComment ( ) ; 
                             DEC ( CommentNestingLevel ) ; 
                             IF CommentNestingLevel = 0 THEN yyPrevious ( ) END ; 
                           }

#M2Comment#	"*" | "(" | M2CmtCh +	:- { AccumComment ( ) ; }

/* C-style comments: */ 

#STD, rules, targetcode#	"/*"	
  :  { yyStart (CComment)	;
       AccumComment ( ) ; 
       CommentPos := Attribute.Position; 
     }

#CComment#	"*/"	:- { AccumComment ( ) ; yyPrevious ; }

#CComment#	"*" | CCmtCh +	:- { AccumComment ( ) ; }

/* Inside both styles of comments: */ 

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
			      Append (Attribute.Text, TargetCode);
			      AssignEmpty (TargetCode);
			   END;
			   yyEol (0);
			}

#STD#		EXPORT	: {PrevState := STD; yyStart (targetcode); RETURN SymExport	;}
#STD#		GLOBAL	: {PrevState := STD; yyStart (targetcode); RETURN SymGlobal	;}
#STD#		LOCAL	: {PrevState := STD; yyStart (targetcode); RETURN SymLocal	;}
#STD#		BEGIN	: {PrevState := STD; yyStart (targetcode); RETURN SymBegin	;}
#STD#		CLOSE	: {PrevState := STD; yyStart (targetcode); RETURN SymClose	;}
#STD#		DEFAULT	: {PrevState := STD; yyStart (targetcode); RETURN SymDefault	;}
#STD#		EOF	: {PrevState := STD; yyStart (targetcode); RETURN SymEof	;}
#STD#		SCANNER	: {RETURN SymScanner	;}
#STD#		DEFINE	: {RETURN SymDefine	;}
#STD#		START	: {RETURN SymStart	;}
#STD#		RULE S ?: {yyStart (rules);	RETURN SymRules		;}
#rules#		\NOT	: {RETURN SymNot	;}

#STD, rules#	letter (letter | digit | _) * : {
			   GetWord (Word);
			   Attribute.Ident  := MakeIdent (Word);
			   RETURN SymIdent;
			}

#STD, rules#	digit +	: {
			   GetWord (Word);
			   Attribute.Number := StringToInt (Word);
			   RETURN SymNumber;
			}

#STD, rules#	\" string * \" : {
			   GetWord (Word);
			   SubString (Word, 2, Length (Word) - 1, TargetCode);
			   Attribute.String := PutString (TargetCode);
			   RETURN SymString;
			}

#STD#		"."	: {RETURN SymDot	;}
#STD#		"="	: {RETURN SymEqual	;}
#STD, set#	"}"	: {yyPrevious;		RETURN SymRBrace	;}
#STD, set, rules# "-"	: {RETURN SymMinus	;}
#STD, rules#	","	: {RETURN SymComma	;}
#STD, rules#	"|"	: {RETURN SymBar	;}
#STD, rules#	"+"	: {RETURN SymPlus	;}
#STD, rules#	"*"	: {RETURN SymAsterisk	;}
#STD, rules#	"?"	: {RETURN SymQuestion	;}
#STD, rules#	"("	: {RETURN SymLParen	;}
#STD, rules#	")"	: {RETURN SymRParen	;}
#STD, rules#	"["	: {RETURN SymLBracket	;}
#STD, rules#	"]"	: {RETURN SymRBracket	;}
#STD, rules#	"{"	: {yyStart (set);	RETURN SymLBrace	;}
#rules#		"#"	: {RETURN SymNrSign	;}
#rules#		"/"	: {RETURN SymSlash	;}
#rules#		"<"	: {RETURN SymLess	;}
#rules#		">"	: {RETURN SymGreater	;}
#rules#		":"	: {PrevState := rules; yyStart (targetcode); RETURN SymColon;}
#rules#		":-"	: {PrevState := rules; yyStart (targetcode); RETURN SymColonMinus;}

#STD, set, rules# \\ n	: {Attribute.Ch := 012C; RETURN SymChar;}
#STD, set, rules# \\ t	: {Attribute.Ch := 011C; RETURN SymChar;}
#STD, set, rules# \\ v	: {Attribute.Ch := 013C; RETURN SymChar;}
#STD, set, rules# \\ b	: {Attribute.Ch := 010C; RETURN SymChar;}
#STD, set, rules# \\ r	: {Attribute.Ch := 015C; RETURN SymChar;}
#STD, set, rules# \\ f	: {Attribute.Ch := 014C; RETURN SymChar;}

#STD, set, rules# \\ digit + : {
			   GetWord (Word);
			   SubString (Word, 2, Length (Word), TargetCode);
			   Attribute.Ch := CHR (CARDINAL (StringToInt (TargetCode)));
	  		   RETURN SymChar;
			}

#STD, set, rules# \\ ANY : {
			   GetWord (Word);
			   Attribute.Ch := Char (Word, 2);
	  		   RETURN SymChar;
			}

#STD, set, rules# - {\t\n\ \f\r} : {
			   GetWord (Word);
			   Attribute.Ch := Char (Word, 1);
	  		   RETURN SymChar;
			}

\f			:- {}
\r			:- {}


