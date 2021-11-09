(*
 *	ell2 - a redesign of ell
 *
 *	$RCSfile: SupM2.md,v $
 *	
 *	purpose:	generate supported modules (MODULA2)
 *
 *	$Author: grosch $
 *	$Date: 1991/02/06 16:16:39 $
 *)

DEFINITION MODULE SupM2;

PROCEDURE ErrM2;		(* produce error handler *)
PROCEDURE ScaM2;		(* produce scanner *)
PROCEDURE ParM2;		(* produce parser driver *)

END SupM2.
