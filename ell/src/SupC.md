(*
 *	ell2 - a redesign of ell
 *
 *	$RCSfile: SupC.md,v $
 *	
 *	purpose:	generate supported modules (C)
 *
 *	$Author: grosch $
 *	$Date: 1991/02/06 16:16:33 $
 *)

DEFINITION MODULE SupC;

PROCEDURE ErrC;			(* produce error handler *)
PROCEDURE ScaC;			(* produce scanner *)
PROCEDURE ParC;			(* produce parser driver *)

END SupC.
