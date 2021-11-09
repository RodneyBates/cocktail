(* $Id: Complete.md,v 2.2 1992/08/07 15:47:31 grosch rel $ *)

DEFINITION MODULE Complete;

FROM	Environs	IMPORT	tFunction;
FROM	Idents		IMPORT	tIdent;
FROM	Positions	IMPORT	tPosition;

VAR IsComplete: BOOLEAN;

PROCEDURE FunctionComplete (function: tFunction; ident: tIdent; pos: tPosition);

END Complete.
