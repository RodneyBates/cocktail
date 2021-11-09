
(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

(* Modified Rodney M. Bates 
   Mar 96 to add functions UpperCase and LowerCase. 
   Apr 96 to add TotalLineCount 
*)

DEFINITION MODULE Scanner;

IMPORT Strings;

(* line 19 "puma.rex" *)

FROM StringMem  IMPORT tStringRef;
FROM Idents     IMPORT tIdent   ;
FROM Texts      IMPORT tText    ;
FROM Positions  IMPORT tPosition;
FROM Strings    IMPORT tString; 

TYPE
yyIdent = RECORD Ident: tIdent; 
END;
yyOperator = RECORD Ident: tIdent; 
END;
yyIncOperator = RECORD Ident: tIdent; 
END;
yyCompoundOperator = RECORD Ident: tIdent; 
END;
yyTargetBlock = RECORD Text: tText; 
END;
yyString = RECORD StringRef: tStringRef; 
END;
yyNumber = RECORD StringRef: tStringRef; 
END;
yyTargetCode = RECORD StringRef: tStringRef; 
END;
yyWhiteSpace = RECORD StringRef: tStringRef; 
END;
(* '::' *) yy10 = RECORD StringRef: tStringRef; 
END;
(* '.' *) yy11 = RECORD StringRef: tStringRef; 
END;
(* '->' *) yy12 = RECORD StringRef: tStringRef; 
END;

tScanAttribute = RECORD
Position: tPosition;
CASE : SHORTCARD OF
| 1: Ident: yyIdent;
| 2: Operator: yyOperator;
| 3: IncOperator: yyIncOperator;
| 4: CompoundOperator: yyCompoundOperator;
| 5: TargetBlock: yyTargetBlock;
| 6: String: yyString;
| 7: Number: yyNumber;
| 8: TargetCode: yyTargetCode;
| 9: WhiteSpace: yyWhiteSpace;
| 10: (* '::' *) yy10: yy10;
| 11: (* '.' *) yy11: yy11;
| 12: (* '->' *) yy12: yy12;
 END ;
END ;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR pAttribute: tScanAttribute);
 

PROCEDURE Error         (Text: ARRAY OF CHAR; Position: tPosition);
PROCEDURE StringError   (Text: tString; Position: tPosition);
PROCEDURE ErrorI        (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
PROCEDURE Warning       (Text: ARRAY OF CHAR; Position: tPosition);
PROCEDURE StringWarning (Text: tString; Position: tPosition);
PROCEDURE WarningI      (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);


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
