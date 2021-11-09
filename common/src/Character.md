(* $Id: Character.md,v 1.1 1989/01/31 15:56:00 vielsack rel $ *)

(* $Log: Character.md,v $
Revision 1.1  1989/01/31  15:56:00  vielsack
Initial revision

 *)

DEFINITION MODULE Character;

PROCEDURE IsEqual (s1, s2: ARRAY OF CHAR): BOOLEAN;
PROCEDURE Length (s: ARRAY OF CHAR): INTEGER;
PROCEDURE Char	(s: ARRAY OF CHAR; i: INTEGER): CHAR;
PROCEDURE Append (s: ARRAY OF CHAR; c: CHAR);
PROCEDURE Concatenate (VAR s1: ARRAY OF CHAR; s2: ARRAY OF CHAR);
PROCEDURE SubString (s1: ARRAY OF CHAR; from,to: INTEGER; VAR s2:ARRAY OF CHAR);
PROCEDURE Assign (VAR s1: ARRAY OF CHAR; s2: ARRAY OF CHAR);
END Character.
