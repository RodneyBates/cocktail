(*
 *	"CodeC.md"
 *	generated with estra/8906
 *	from "CodeC.aftermpp"
 *
 *	estra 
 *	was written by Bertram Vielsack in june 1989
 *
 *)

DEFINITION MODULE CodeC;

IMPORT Tree;

VAR CodeCTabName: ARRAY [0..127] OF CHAR;

PROCEDURE BeginCodeC;
PROCEDURE DoCodeC (yyt: Tree.tTree);
PROCEDURE CloseCodeC;
END CodeC.
