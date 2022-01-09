(* $Id: General.mi,v 1.3 1992/01/30 13:23:29 grosch rel $ *)

(* $Log: General.mi,v $

 * RMB 93/10/13 Added MinSHORTCARD and MaxSHORTCARD.

 * RMB 93/10/11 type conversions/transfers in call to System.PutArgs
     for WRL compatibility.

 * Revision 1.3  1992/01/30  13:23:29  grosch
 * redesign of interface to operating system
 *
 * Revision 1.2  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/03/02  17:36:06  grosch
 * automized handling of machine independent alignment
 * 
 * Revision 1.0  88/10/04  11:46:54  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

(* General Subroutines: minimum, maximum, binary logarithm, and power of 2 *)

 UNSAFE MODULE General;


IMPORT Word;
FROM SYSTEM IMPORT M2LONGINT;
FROM SYSTEM IMPORT BITSET, SHORTCARD;
(* FROM Arguments	IMPORT ArgTable, GetArgs;
   FROM System	IMPORT PutArgs;
*)
VAR
   ForAlign	: RECORD char: CHAR; longreal: LONGREAL; END;
   argc		: INTEGER;
(*   argv		: ArgTable; *)


(* Returns the minimum of 'a' and 'b'.		*)

PROCEDURE Min		(a, b: INTEGER)			: INTEGER =
   BEGIN
      IF a <= b THEN
	 RETURN a;
      ELSE
	 RETURN b;
      END;
   END Min;

(* Returns the maximum of 'a' and 'b'.		*)

PROCEDURE Max		(a, b: INTEGER)			: INTEGER =
   BEGIN
      IF a >= b THEN
	 RETURN a;
      ELSE
	 RETURN b;
      END;
   END Max;

PROCEDURE MinSHORTCARD	(a, b: SHORTCARD)		: SHORTCARD =
   BEGIN
      IF a <= b THEN
	 RETURN a;
      ELSE
	 RETURN b;
      END;
   END MinSHORTCARD;

PROCEDURE MaxSHORTCARD	(a, b: SHORTCARD)		: SHORTCARD =
   BEGIN
      IF a >= b THEN
	 RETURN a;
      ELSE
	 RETURN b;
      END;
   END MaxSHORTCARD;

(* Returns the logarithm to the base 2 of 'x'.	*)

PROCEDURE Log2		(x: M2LONGINT)			: Word.T =
   VAR y: Word.T;
   BEGIN
      y := 0;
      IF x >= 65536 THEN INC (y, 16); x := x DIV 65536; END;
      IF x >=   256 THEN INC (y,  8); x := x DIV   256; END;
      IF x >=    16 THEN INC (y,  4); x := x DIV    16; END;
      IF x >=     4 THEN INC (y,  2); x := x DIV     4; END;
      IF x >=     2 THEN INC (y,  1); x := x DIV     2; END;
      RETURN y;
   END Log2;

(* Returns the number of the lowest bit set in 'x'.	*)

PROCEDURE AntiLog	(x: M2LONGINT)			: Word.T =
   VAR y: Word.T;
   BEGIN
      y := 0;
      IF (x MOD 65536) = 0 THEN INC (y, 16); x := x DIV 65536; END;
      IF (x MOD   256) = 0 THEN INC (y,  8); x := x DIV   256; END;
      IF (x MOD    16) = 0 THEN INC (y,  4); x := x DIV    16; END;
      IF (x MOD     4) = 0 THEN INC (y,  2); x := x DIV     4; END;
      IF (x MOD     2) = 0 THEN INC (y,  1); x := x DIV     2; END;
      RETURN y;
   END AntiLog;

(* Returns 2 to the power of 'x'.		*)

PROCEDURE Exp2		(x: Word.T)			: M2LONGINT =
   VAR y: M2LONGINT;
   BEGIN
      y := 1;
      IF x >= 16 THEN DEC (x, 16); y := y * 65536; END;
      IF x >=  8 THEN DEC (x,  8); y := y *   256; END;
      IF x >=  4 THEN DEC (x,  4); y := y *    16; END;
      IF x >=  2 THEN DEC (x,  2); y := y *     4; END;
      IF x >=  1 THEN DEC (x,  1); y := y *     2; END;
      RETURN y;
   END Exp2;

(* Returns 10 to the power of 'x'.		*)

PROCEDURE Exp10		(x: INTEGER)			: REAL =
   VAR
      y		: REAL;
      negative	: BOOLEAN;
   BEGIN
      negative := x < 0;
      x := ABS (x);
      y := 1.0;
   (* IF x >= 64 THEN DEC (x, 64); y := y * 1.0E64; END; too big *)
   (* IF x >= 32 THEN DEC (x, 32); y := y * 1.0E32; END; PCS10 compatibility *)
      IF x >= 16 THEN DEC (x, 16); y := y * 1.0E16; END;
      IF x >= 16 THEN DEC (x, 16); y := y * 1.0E16; END;
      IF x >=  8 THEN DEC (x,  8); y := y * 1.0E8 ; END;
      IF x >=  4 THEN DEC (x,  4); y := y * 1.0E4 ; END;
      IF x >=  2 THEN DEC (x,  2); y := y * 1.0E2 ; END;
      IF x >=  1 THEN DEC (x,  1); y := y * 1.0E1 ; END;
      IF negative
      THEN RETURN 1.0 / y;
      ELSE RETURN       y;
      END;
   END Exp10;

BEGIN
   MaxAlign := LOOPHOLE (ADR (ForAlign.longreal(* $$ m2tom3 warning: unhandled ADR parameter 'longreal' in line 147
 $$ *)),Word.T) - LOOPHOLE (ADR (ForAlign.char),Word.T);

   AlignMasks [1] := -1 (*16_0FFFFFFFF*);
   AlignMasks [2] := -2 (*16_0FFFFFFFE*);
   AlignMasks [3] := -1 (*16_0FFFFFFFF*);
   AlignMasks [4] := -4 (*16_0FFFFFFFC*);
   AlignMasks [5] := -1 (*16_0FFFFFFFF*);
   AlignMasks [6] := -1 (*16_0FFFFFFFF*);
   AlignMasks [7] := -1 (*16_0FFFFFFFF*);
   AlignMasks [8] := -8 (*16_0FFFFFFF8*);

(*
   GetArgs (argc, argv);
   PutArgs (argc, LOOPHOLE(argv,ADDRESS));
*)
END General.


