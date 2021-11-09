(* $Id: SysIODrv.mi,v 1.2 1992/01/30 13:23:29 grosch rel $ *)

(* $Log: SysIODrv.mi,v $
 * Revision 1.2  1992/01/30  13:23:29  grosch
 * redesign of interface to operating system
 *
 * Revision 1.1  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  11:47:28  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

UNSAFE MODULE SysIODrv EXPORTS Main;



FROM System	IMPORT 
   tFile	, OpenInput	, OpenOutput	, Read		,
   Write	, Close		;

FROM Checks	IMPORT
   ErrorCheck	;

VAR
   b	: ARRAY [0..1023] OF CHAR;
   f	: tFile;
   n	: INTEGER;

BEGIN
   f := OpenInput (ARRAY [0..8] OF CHAR{'M','a','k','e','f','i','l','e','\000'});
   ErrorCheck (ARRAY [0..9] OF CHAR{'O','p','e','n','I','n','p','u','t','\000'}, f);
   n := Read (f, ADR (b[FIRST(b)]), 1024);
   ErrorCheck (ARRAY [0..4] OF CHAR{'R','e','a','d','\000'}, n);
   Close (f);

   f := OpenOutput ('t');
   ErrorCheck (ARRAY [0..10] OF CHAR{'O','p','e','n','O','u','t','p','u','t','\000'}, f);
   n := Write (f, ADR (b[FIRST(b)]), 1024);
   ErrorCheck (ARRAY [0..5] OF CHAR{'W','r','i','t','e','\000'}, n);
   Close (f);
END SysIODrv.

