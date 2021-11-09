(*
 *	"Semantics.md"
 *	generated with estra/8906
 *	from "../src/Sem.estra"
 *
 *	estra 
 *	was written by Bertram Vielsack in june 1989
 *
 *)

DEFINITION MODULE Semantics;

IMPORT Tree;

VAR SemanticsTabName: ARRAY [0..127] OF CHAR;

PROCEDURE BeginSemantics;
PROCEDURE DoSemantics (yyt: Tree.tTree);
PROCEDURE CloseSemantics;
END Semantics.
