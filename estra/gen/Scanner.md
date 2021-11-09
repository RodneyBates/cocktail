
(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

(* Modified Rodney M. Bates 
   Mar 96 to add functions UpperCase and LowerCase. 
   Apr 96 to add TotalLineCount 
*)

DEFINITION MODULE Scanner;

IMPORT Strings;

(* line 4 "../src/Estral.rex" *)

FROM	Idents		IMPORT	tIdent;
FROM	StringMem	IMPORT	tStringRef;
FROM	Positions	IMPORT	tPosition;

CONST
  SymLParent		=  1	;
  SymRParent		=  2	;
  SymComma		=  3	;
  SymDot		=  4	;
  SymSlash		=  5	;
  SymColon		=  6	;
  SymSemiColon		=  7	;
  SymEqual		=  8	;
  SymBar		= 11	;
  SymLBrace		= 12	;
  SymRBrace		= 13	;

  SymRArrow		= 15	;

  SymBEGIN		= 21	;
  SymCLOSE		= 22	;
  SymCONDITION		= 23	;
  SymCOSTS		= 24	;
  SymDECLARE		= 25	;
  SymEXPORT		= 26	;
  SymGLOBAL		= 27	;
  SymGRAMMAR		= 28	;
  SymLOCAL		= 29	;
  SymFUNCTION		= 30	;
  SymTRANSFORMATION	= 31	;

  SymIdent		= 41	;
  SymNumber		= 42	;
  SymString		= 43	;

  SymCodeLBrace		= 51	;
  SymCodeRBrace		= 52	;
  SymCodeDot		= 53	;
  SymCodeLParent	= 54	;
  SymCodeRParent	= 55	;
  SymCodeIdent		= 56	;
  SymCodeString		= 57	;
  SymCodeSpace		= 58	;
  SymCodeComment	= 59	;
  SymCodeRest		= 60	;
  SymCodeComma		= 61	;
  
TYPE
  tScanAttribute	= RECORD
			    Position: tPosition;
			    CASE :INTEGER OF
			    | SymIdent, SymString, SymCodeIdent, SymCodeString:
				ident: tIdent;
			    | SymCodeSpace .. SymCodeRest, SymCodeComma:
				ref: tStringRef;
			    | SymNumber:
				val: INTEGER;
			    END;
			  END;

CONST
  NoValue	= -1;

VAR
  NoIdent	: tIdent;
  MaxIdent	: tIdent;
  NoStringRef	: tStringRef;
  MaxValue	: INTEGER;


PROCEDURE ErrorAttribute (Symbol: INTEGER; VAR Attribute: tScanAttribute);



CONST EofToken	= 0;

VAR TokenLength	: INTEGER;
VAR Attribute	: tScanAttribute;
VAR ScanTabName	: ARRAY [0 .. 127] OF CHAR;
VAR Exit	: PROC;

PROCEDURE BeginScanner	;
PROCEDURE BeginFile	(FileName: ARRAY OF CHAR);
PROCEDURE GetToken	(): INTEGER;
PROCEDURE GetWord	(VAR Word: Strings.tString);
PROCEDURE GetLower	(VAR Word: Strings.tString);
PROCEDURE GetUpper	(VAR Word: Strings.tString);
PROCEDURE CloseFile	;
PROCEDURE CloseScanner	;
PROCEDURE UpperCase ( Ch : CHAR ) : CHAR ; 
PROCEDURE LowerCase ( Ch : CHAR ) : CHAR ; 
PROCEDURE TotalLineCount ( ) : CARDINAL ; 
  (* line count including all files read. *) 

END Scanner.
