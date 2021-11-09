(*
 *	"CodeM2.md"
 *	generated with estra/8906
 *	from "CodeM2.aftermpp"
 *
 *	estra 
 *	was written by Bertram Vielsack in june 1989
 *
 *)

DEFINITION MODULE CodeM2;

IMPORT Tree;

VAR CodeM2TabName: ARRAY [0..127] OF CHAR;

PROCEDURE BeginCodeM2;
PROCEDURE DoCodeM2 (yyt: Tree.tTree);
PROCEDURE CloseCodeM2;
END CodeM2.
