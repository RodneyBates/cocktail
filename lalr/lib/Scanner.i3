(* $Id: Scanner.md,v 2.2 1992/08/07 15:28:42 grosch rel $ *)

(* Modified from Scanner.md, to be in Modula-3.
   Rodney M. Bates, rodney.m.bates@acm.org.
*) 

$@ INTERFACE $;

FROM Positions	IMPORT tPosition;

TYPE tScanAttribute	= RECORD Position: tPosition; END;

VAR  Attribute		: tScanAttribute;

PROCEDURE GetToken ()	: CARDINAL;
PROCEDURE ErrorAttribute (Token: CARDINAL; VAR Attribute: tScanAttribute);

$@ END $.
