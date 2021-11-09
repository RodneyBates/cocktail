(* $Id: DefTable.md,v 1.0 88/10/04 11:59:29 grosch rel Locker: grosch $ *)

(* $Log:	DefTable.md,v $
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Dec. 1990 *)

DEFINITION MODULE DefTable;

FROM Idents	IMPORT tIdent	;

CONST
   NoDef	= 0	;

TYPE
   DefRange	= LONGINT;
   tKind	= (NoKind, Ident, Start);

VAR
   DefCount	: DefRange;

PROCEDURE MakeIdentDef	( pIdent	: tIdent	);
PROCEDURE MakeStartDef	( pIdent	: tIdent	);
PROCEDURE GetDef	( pIdent	: tIdent	): DefRange;
PROCEDURE GetKind	( pDef		: DefRange	): tKind;

END DefTable.
