DEFINITION MODULE Parser;

(* '../src/ell.ell' line 12 *)

FROM Tree	IMPORT	tTree;

TYPE tParsAttribute = tTree;


VAR
  ParsAttribute	: tParsAttribute;
  ParsTabName	: ARRAY [0..128] OF CHAR;

PROCEDURE Parser (): INTEGER;
PROCEDURE CloseParser ();
PROCEDURE xxTokenName (Token: CARDINAL; VAR Name: ARRAY OF CHAR);

END Parser.
