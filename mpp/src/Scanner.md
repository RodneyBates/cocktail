(* $Id: Scanner.md,v 1.3 1992/08/11 13:28:33 grosch rel $ *)

DEFINITION MODULE Scanner;

FROM Positions	IMPORT tPosition;

TYPE tScanAttribute	= RECORD Position: tPosition; Ch: CHAR; END;

VAR Attribute	: tScanAttribute;

PROCEDURE BeginScanner;
PROCEDURE CloseScanner;
PROCEDURE GetToken (): CARDINAL;
PROCEDURE ErrorAttribute (Symbol: CARDINAL; VAR Attribute: tScanAttribute);

END Scanner.
