(* check i/o errors *)

(* $Id: Checks.mi,v 1.3 1992/02/05 08:00:00 grosch rel $ *)

(* Rodney M. Bates, modifications: 

    1-98 Change DevNull so it has a trailing null when passed

*) 

(* $Log: Checks.mi,v $
 * Revision 1.3  1992/02/05  08:00:00  grosch
 * renamed NULL to DevNull 
 *
 * Revision 1.2  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/11  18:44:43  grosch
 * layout improvements
 * 
 * Revision 1.0	 88/10/04  14:26:40  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE Checks;

FROM	IO		IMPORT	tFile, ReadOpen, WriteOpen;
FROM	Strings		IMPORT	tString, ArrayToString;
FROM	SysError	IMPORT	StatIsBad, SysErrorMessageI;

FROM	Errors		IMPORT	eInteger, eString, eFatal, eError, ErrorMessageI;

VAR DevNull : ARRAY [ 0 .. 15 ] OF CHAR; 

PROCEDURE ErrorCheck (READONLY a: ARRAY OF CHAR; n: INTEGER) =
  VAR s : tString;
  BEGIN
    IF StatIsBad (n) THEN 
      ArrayToString (a, s);
      SysErrorMessageI (n, eFatal, eString, ADR (s));
    END;
  END ErrorCheck;

PROCEDURE CheckReadOpen (VAR file: tFile;READONLY  a: ARRAY OF CHAR) =
  VAR s: tString;
  BEGIN
    IF StatIsBad (file) THEN
      ArrayToString (a, s);
      SysErrorMessageI (file, eError, eString, ADR(s));
      file := ReadOpen (DevNull);
      IF StatIsBad (file) THEN
	ArrayToString (DevNull, s);
	SysErrorMessageI (file, eFatal, eString, ADR(s));
      END;
    END;
  END CheckReadOpen;

PROCEDURE CheckWriteOpen (VAR file: tFile;READONLY  a: ARRAY OF CHAR) =
  VAR s: tString;
  BEGIN
    IF StatIsBad (file) THEN
      ArrayToString (a, s);
      SysErrorMessageI (file, eError, eString, ADR(s));
      file := WriteOpen (DevNull);
      IF StatIsBad (file) THEN
	ArrayToString (DevNull, s);
	SysErrorMessageI (file, eFatal, eString, ADR(s));
      END;
    END;
  END CheckWriteOpen;

BEGIN
  DevNull := "/dev/null";
END Checks.

