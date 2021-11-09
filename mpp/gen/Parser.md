DEFINITION MODULE Parser;

(* '../src/mpp.ell' line 3 *)

FROM Strings	IMPORT	tString;

TYPE tParsAttribute = tString;


VAR
  ParsAttribute	: tParsAttribute;
  ParsTabName	: ARRAY [0..128] OF CHAR;

PROCEDURE Parser (): INTEGER;
PROCEDURE CloseParser ();
PROCEDURE xxTokenName (Token: CARDINAL; VAR Name: ARRAY OF CHAR);

END Parser.
