(* $Id: Positions.md,v 1.4 1991/11/21 14:33:17 grosch rel $ *)

(* $Log: Positions.md,v $
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Juli 1992 *)

DEFINITION MODULE Positions;

FROM IO		IMPORT tFile;
FROM Idents	IMPORT tIdent;

TYPE	  tPosition	= RECORD File: tIdent; Line, Column: SHORTCARD; END;

VAR	  NoPosition	: tPosition;
			(* A default position (0, 0).			*)

PROCEDURE Compare	(Position1, Position2: tPosition): INTEGER;
			(* Returns -1 if Position1 < Position2.		*)
			(* Returns  0 if Position1 = Position2.		*)
			(* Returns  1 if Position1 > Position2.		*)

PROCEDURE WritePosition	(File: tFile; Position: tPosition);
			(* The 'Position' is printed on the 'File'.	*)

END Positions.
