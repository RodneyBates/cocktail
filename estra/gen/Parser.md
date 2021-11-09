(* $Id: Parser.md,v 2.1 1992/08/07 15:28:42 grosch rel $ *)

DEFINITION MODULE Parser;

(* line 3 "../src/Estral.lalr" *)

FROM	Tree		IMPORT	tTree;

VAR AST : tTree;


VAR ParsTabName	: ARRAY [0..128] OF CHAR;

PROCEDURE TokenName (Token: SHORTCARD; VAR Name: ARRAY OF CHAR);

PROCEDURE Parser (): CARDINAL;
PROCEDURE CloseParser;

END Parser.
