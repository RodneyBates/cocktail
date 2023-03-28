
(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

(* Modified Rodney M. Bates 
   Mar 96 to add functions UpperCase and LowerCase. 
   Apr 96 to add TotalLineCount 
*)

UNSAFE INTERFACE  Scanner;

IMPORT Word, Strings;

(* line 49 "../src/input.rex" *)


FROM StringMem  IMPORT tStringRef;
FROM Idents     IMPORT tIdent;
FROM Rules      IMPORT Expression;
FROM Lists      IMPORT tList;
FROM Positions  IMPORT tPosition;

TYPE
   AttributeMode = {Keys, Comment, Number, Action, Symbol, Coding, PrioPart, RightSide, Empty};

   tScanAttribute=
      RECORD
         Position: tPosition;
          Mode: AttributeMode; 
           Comm        : tList;
           Value        : Word.T;
           Act  : tList;
           Sym  : tIdent;
          
             HasCoding  : BOOLEAN ;
             CodNumbPos : tPosition;
             CodValue   : Word.T;
          
             Expr:  Expression;
              HasPrio: BOOLEAN; 
               
                 PriSym : tIdent;
                 PriSymPos      : tPosition;
             
         
      END;
(* WAS tScanAttribute=
      RECORD
         Position: tPosition;
         Mode: AttributeMode; 
         Comm        : tList;
           Value        : Word.T;
           Act  : tList;
           Sym  : tIdent;
          
             HasCoding  : BOOLEAN ;
             CodNumbPos : tPosition;
             CodValue   : Word.T;
          
           AttributeMode.
             Expr:  Expression;
              HasPrio: BOOLEAN; 
               
                 PriSym : tIdent;
                 PriSymPos      : tPosition;
             
         
      END;
*)

PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attr: tScanAttribute);


CONST EofToken	= 0;

VAR TokenLength	: INTEGER;
VAR Attribute	: tScanAttribute;
VAR ScanTabName	: TEXT;
VAR Exit	: PROCEDURE ();

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

