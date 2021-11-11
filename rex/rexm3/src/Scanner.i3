
(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

(* Modified Rodney M. Bates 
   Mar 96 to add functions UpperCase and LowerCase. 
   Apr 96 to add TotalLineCount 
*)

UNSAFE INTERFACE  Scanner;

FROM SYSTEM IMPORT SHORTCARD;
IMPORT Word, Strings;

(* line 62 "../src/rex.rex" *)


FROM Idents	IMPORT tIdent	;
FROM StringMem	IMPORT tStringRef;
FROM Texts	IMPORT tText	;
FROM Positions	IMPORT tPosition;

TYPE
   tScanAttribute	= RECORD
	      Position	: tPosition	;
	  
	   Ident	: tIdent	;
	   Number	: SHORTCARD	;
	   String	: tStringRef	;
	   Ch	: CHAR		;
	   Text	: tText		;
	 
      END;

PROCEDURE ErrorAttribute (Token: Word.T; VAR Attribute: tScanAttribute);


CONST EofToken	= 0;

VAR TokenLength	: INTEGER;
VAR Attribute	: tScanAttribute;
VAR ScanTabName	: ARRAY [0 .. 127] OF CHAR;
VAR Exit	: PROC;

PROCEDURE BeginScanner()	;
PROCEDURE BeginFile	(READONLY FileName: ARRAY OF CHAR);
PROCEDURE GetToken	(): INTEGER;
PROCEDURE GetWord	(VAR Word: Strings.tString);
PROCEDURE GetLower	(VAR Word: Strings.tString);
PROCEDURE GetUpper	(VAR Word: Strings.tString);
PROCEDURE CloseFile()	;
PROCEDURE CloseScanner()	;
PROCEDURE UpperCase ( Ch : CHAR ) : CHAR ; 
PROCEDURE LowerCase ( Ch : CHAR ) : CHAR ; 
PROCEDURE TotalLineCount ( ) : Word.T ; 
  (* line count including all files read. *) 

END Scanner.

