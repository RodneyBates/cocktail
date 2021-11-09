(*
 *	ell2 - a redesign of ell
 *
 *	$RCSfile: Info.md,v $
 *	
 *	purpose:	save and print informations
 *
 *	$Author: grosch $
 *	$Date: 1992/08/07 15:32:36 $
 *)

DEFINITION MODULE Info;

FROM	IO		IMPORT	tFile;
FROM	Sets		IMPORT	tSet;
FROM	SYSTEM		IMPORT	ADDRESS;

PROCEDURE SaveInfo (InfoClass: INTEGER; Info: ADDRESS): ADDRESS;
PROCEDURE WriteInfo (InfoClass: INTEGER; Info: ADDRESS);

PROCEDURE WriteIdentSet (f: tFile; s: tSet);

END Info.
