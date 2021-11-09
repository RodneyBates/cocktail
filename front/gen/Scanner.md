
(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

(* Modified Rodney M. Bates 
   Mar 96 to add functions UpperCase and LowerCase. 
   Apr 96 to add TotalLineCount 
*)

DEFINITION MODULE Scanner;

IMPORT Strings;

(* line 49 "../src/input.rex" *)


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
