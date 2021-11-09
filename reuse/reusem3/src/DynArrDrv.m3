(* $Id: DynArrDrv.mi,v 1.1 1991/11/21 14:33:17 grosch rel $ *)

(* $Log: DynArrDrv.mi,v $
 * Revision 1.1  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  11:46:51  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

UNSAFE MODULE DynArrDrv EXPORTS Main;

FROM SYSTEM IMPORT M3LONGINT;
IMPORT Word;
FROM DynArray	IMPORT MakeArray, ExtendArray;
FROM IO		IMPORT StdOutput, WriteC, WriteI, WriteNl, WriteS, WriteLong, CloseIO;


VAR  i : M3LONGINT;
     j : Word.T;

TYPE t = ARRAY [1 .. 100000] OF M3LONGINT;
(* necessary to force index arithmetic to be done with long integers *)

VAR  p : UNTRACED BRANDED REF  t;
     s : M3LONGINT;

BEGIN
   s := 10;

   MakeArray (p, s, BYTESIZE (M3LONGINT));
   FOR i := 1 TO s DO
      p^[i] := i;
   END;

   FOR j := 1 TO 13 DO
      ExtendArray (p, s, BYTESIZE (M3LONGINT));

      IF p = NIL THEN
	 WriteS (StdOutput, ARRAY [0..12] OF CHAR{'E','x','t','e','n','d',' ','E','r','r','o','r','\000'}); WriteNl (StdOutput);
      END;

      FOR i := (s DIV 2) + 1 TO s DO
	 p^[i] := i;
      END;

      FOR i := 1 TO s DO
	 IF p^[i] # i THEN
	    WriteS (StdOutput, ARRAY [0..19] OF CHAR{'E','r','r','o','r',' ','j',',',' ','i',',',' ','p','^','[','i',']',' ','=','\000'});
	    WriteI (StdOutput, j, 5);
	    WriteLong (StdOutput, i, 5);
	    WriteLong (StdOutput, p^[i], 10);
	    WriteNl (StdOutput);
	 END;
      END;

      WriteS (StdOutput, ARRAY [0..10] OF CHAR{'j',',',' ','s','i','z','e',' ','=',' ','\000'});
      WriteI (StdOutput, j, 5);
      WriteLong (StdOutput, s, 10);
      WriteS (StdOutput, ARRAY [0..3] OF CHAR{' ','o','k','\000'});
      WriteNl (StdOutput);
   END;
   CloseIO();
END DynArrDrv.

