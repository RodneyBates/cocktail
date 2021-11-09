(*
 *	ell2 - a redesign of ell
 *
 *	$RCSfile: Derivable.md,v $
 *	
 *	purpose:	check derivability of each nonterminal
 *
 *	$Author: grosch $
 *	$Date: 1991/02/06 16:15:36 $
 *)

DEFINITION MODULE Derivable;

FROM Idents	IMPORT	tIdent;

PROCEDURE TestDerivable;
PROCEDURE IsDerivable	(Nonterm: tIdent): BOOLEAN;
PROCEDURE IsNullable	(Nonterm: tIdent): BOOLEAN;

END Derivable.
