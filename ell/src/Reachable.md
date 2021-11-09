(*
 *	ell2 - a redesign of ell
 *
 *	$RCSfile: Reachable.md,v $
 *	
 *	purpose:	check reachability of the nonterminals
 *
 *	$Author: grosch $
 *	$Date: 1991/02/06 16:16:02 $
 *)


DEFINITION MODULE Reachable;

FROM Idents	IMPORT	tIdent;

PROCEDURE WindThrough (start: tIdent);
PROCEDURE IsReachable (nonterm: tIdent): BOOLEAN;

END Reachable.
