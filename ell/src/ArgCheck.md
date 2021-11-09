(*
 *	ell2 - a redesign of ell
 *
 *	$RCSfile: ArgCheck.md,v $
 *	
 *	purpose:	check arguments
 *
 *	$Author: grosch $
 *	$Date: 1992/10/15 18:26:55 $
 *)

DEFINITION MODULE ArgCheck;

TYPE tLanguage = (C, MODULA2);

VAR
  DEF, IMP, ERR, SCA, PAR, LINE: BOOLEAN;
  LANGUAGE: tLanguage;
  SourceFileName: ARRAY [0..127] OF CHAR;

  (* ARG_ *)
  TREE, TABLE, CODES, QUERY: BOOLEAN;
  (* _ARG *)

PROCEDURE CheckArgs;

END ArgCheck.
