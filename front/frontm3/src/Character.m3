(* handle strings with open character arrays *)

(* $Id: Character.mi,v 1.3 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: Character.mi,v $
 * Revision 1.3  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/11  18:44:41  grosch
 * layout improvements
 * 
 * Revision 1.1	 89/01/12  18:05:43  vielsack
 * supply procedure Assign to assign a character string
 * 
 * Revision 1.0	 88/10/04  14:26:38  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE Character;

IMPORT Word;
PROCEDURE IsEqual (READONLY c1, c2: ARRAY OF CHAR): BOOLEAN =
  VAR
    pos: Word.T;
    len: Word.T;
  BEGIN
    pos := 0;
    len := Length (c1);
    IF len # Length (c2) THEN RETURN FALSE; END;
    pos := 0;
    LOOP
      IF pos >= len THEN EXIT; END;
      IF c1 [pos] # c2 [pos] THEN EXIT; END;
      INC (pos);
    END;
    RETURN pos = len;
  END IsEqual;

PROCEDURE Length (READONLY c: ARRAY OF CHAR): Word.T =
  VAR len: Word.T;
  BEGIN
    len := 0;
    LOOP
      IF len > LAST (c) THEN EXIT; END;
      IF c [len] = '\000' THEN EXIT; END;
      INC (len);
    END;
    RETURN len;
  END Length;

PROCEDURE Assign (VAR s1: ARRAY OF CHAR;READONLY  s2: ARRAY OF CHAR) =
  VAR i: Word.T;
  BEGIN
    FOR i := 0 TO Length (s2) DO
      s1 [i] := s2 [i];
    END;
  END Assign;

BEGIN
END Character.

