(* $Id: Convert.md,v 1.1 1989/07/05 15:56:35 grosch rel $ *)

DEFINITION MODULE Convert;

FROM Idents	IMPORT	tIdent;
FROM SYSTEM IMPORT	ADDRESS;

(* procedures to convert tIdent to ADDRESS and vice versa *)

PROCEDURE IdToAdr (id: tIdent): ADDRESS;
PROCEDURE AdrToId (adr: ADDRESS): tIdent;

END Convert.
