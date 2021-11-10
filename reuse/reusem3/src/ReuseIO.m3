(* $Id: IO.mi,v 1.9 1992/01/30 13:23:29 grosch rel $ *)

(* $Log: IO.mi,v $

 * RMB 93/10/12 Various type conversions, removed VAR on parameter s
       of WriteS and FileName of ReadOpen and WriteOpen.

 * Revision 1.9  1992/01/30  13:23:29  grosch
 * redesign of interface to operating system
 *
 * Revision 1.8  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.7  91/06/07  12:19:51  grosch
 * decreased bounds of flexible arrays
 * 
 * Revision 1.6  91/06/07  11:37:42  grosch
 * increased bounds of flexible arrays
 * 
 * Revision 1.5  91/01/16  17:11:13  grosch
 * fixed range check problem with BytesRead
 * 
 * Revision 1.4  89/08/18  11:11:48  grosch
 * make Write work for Size = 0
 * 
 * Revision 1.3  89/07/14  16:27:15  grosch
 * made WriteN work for numbers with MSBit set
 * 
 * Revision 1.2  89/01/25  19:37:28  grosch
 * tuning: ReadC inline in Read and ReadS, WriteC inline in Write and WriteS
 * 
 * Revision 1.1  89/01/24  19:04:35  grosch
 * added procedure UnRead
 * 
 * Revision 1.0  88/10/04  11:46:58  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

 UNSAFE MODULE ReuseIO;			(* buffered IO		*)


FROM SYSTEM IMPORT M2LONGINT, M2LONGCARD;
FROM SYSTEM IMPORT SHORTINT;
FROM	General	IMPORT Exp10	;
FROM	Memory	IMPORT Alloc	, Free	;

IMPORT	Word, System;

CONST
   EolCh		= '\012';
   TabCh		= '\011';
   BufferSize		= 1024;
   MaxInt		= 2147483647;	(* 2 ** 31 - 1 *)
   MaxPow10		= 1000000000;
   MaxIntDiv10		= MaxInt DIV 10;

TYPE
   BufferDescriptor	= RECORD
	 Buffer		: UNTRACED BRANDED REF  ARRAY [0 .. BufferSize] OF CHAR;
	 BufferIndex	: SHORTINT;
	 BytesRead	: SHORTINT;
	 OpenForOutput	: BOOLEAN;
	 EndOfFile	: BOOLEAN;
	 FlushLine	: BOOLEAN;
      END;

   (* INV BufferIndex points before the character to be read next *)

VAR
   BufferPool	: ARRAY tFile OF BufferDescriptor;
   MyCHR	: ARRAY [0 .. 15] OF CHAR;

PROCEDURE FillBuffer	(f: tFile) =
   BEGIN
      WITH m2tom3_with_8=BufferPool [f] DO
	 IF m2tom3_with_8.FlushLine THEN
	    WriteFlush (StdOutput);
	    WriteFlush (StdError );
	 END;
	 m2tom3_with_8.BufferIndex := 0;
	 m2tom3_with_8.BytesRead 
           := VAL (   System.Read (f, ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 84
 $$ *) (m2tom3_with_8.Buffer^ [1]), BufferSize),SHORTINT );
	 IF m2tom3_with_8.BytesRead <= 0 THEN
	    m2tom3_with_8.BytesRead := 0;
	    m2tom3_with_8.EndOfFile := TRUE;
	 END;
      END;
   END FillBuffer;

PROCEDURE ReadOpen	(READONLY FileName: ARRAY OF CHAR): tFile =
   VAR						(* open  input file	*)
      f		: tFile;
   BEGIN
      f := System.OpenInput (FileName);
      WITH m2tom3_with_9=BufferPool [f] DO
	 m2tom3_with_9.Buffer		:= Alloc (BufferSize + 1);
	 m2tom3_with_9.BufferIndex	:= 0;
	 m2tom3_with_9.BytesRead	:= 0;
	 m2tom3_with_9.OpenForOutput	:= FALSE;
	 m2tom3_with_9.EndOfFile	:= FALSE;
      END;
      CheckFlushLine (f);
      RETURN f;
   END ReadOpen;

PROCEDURE ReadClose	(f: tFile) =		(* close input file	*)
   BEGIN
      System.Close (f);
      WITH m2tom3_with_10=BufferPool [f] DO
	 Free (BufferSize + 1, m2tom3_with_10.Buffer);
	 m2tom3_with_10.Buffer := NIL;
      END;
   END ReadClose;

PROCEDURE Read		(f: tFile; Buffer: ADDRESS; Size: Word.T): INTEGER =
   VAR						(* binary		*)
      BufferPtr : UNTRACED BRANDED REF  ARRAY [0 .. 100000000] OF CHAR;
      i		: Word.T;
   BEGIN
      BufferPtr := Buffer;
      WITH m2tom3_with_11=BufferPool [f] DO
	 i := 0;
	 LOOP
	    IF i = Size THEN RETURN i; END;
	    IF m2tom3_with_11.BufferIndex = m2tom3_with_11.BytesRead THEN	(* ReadC inline		*)
	       FillBuffer (f);
	       IF m2tom3_with_11.EndOfFile THEN m2tom3_with_11.Buffer^ [1] := '\000'; END;
	    END;
	    INC (m2tom3_with_11.BufferIndex);
	    BufferPtr^ [i] := m2tom3_with_11.Buffer^ [m2tom3_with_11.BufferIndex];
	    IF m2tom3_with_11.EndOfFile THEN RETURN i; END;
	    INC (i);
	 END;
      END;
   END Read;

PROCEDURE ReadC		(f: tFile): CHAR =	(* character		*)
   BEGIN
      WITH m2tom3_with_12=BufferPool [f] DO
	 IF m2tom3_with_12.BufferIndex = m2tom3_with_12.BytesRead THEN
	    FillBuffer (f);
	    IF m2tom3_with_12.EndOfFile THEN m2tom3_with_12.Buffer^ [1] := '\000'; END;
	 END;
	 INC (m2tom3_with_12.BufferIndex);
  	 RETURN m2tom3_with_12.Buffer^ [m2tom3_with_12.BufferIndex]; 
      END;
   END ReadC;

PROCEDURE ReadI		(f: tFile): INTEGER =	(* integer  number	*)
   VAR
      n		: INTEGER;
      ch	: CHAR;
      negative	: BOOLEAN;
   BEGIN
      REPEAT
         ch := ReadC (f);
      UNTIL (ch # ' ') AND (ch # TabCh) AND (ch # EolCh);
      CASE ch OF
      |  '+' => negative := FALSE; ch := ReadC (f);
      |  '-' => negative := TRUE ; ch := ReadC (f);
      ELSE     negative := FALSE;
      END;
      n := 0;
      WHILE ('0' <= ch) AND (ch <= '9') DO
	 n := (10 * n) + LOOPHOLE (ORD (ch) - ORD ('0'),INTEGER);
	 ch := ReadC (f);
      END;
      DEC (BufferPool [f].BufferIndex);
      IF negative
      THEN RETURN - n;
      ELSE RETURN   n;
      END;
   END ReadI;

PROCEDURE ReadR		(f: tFile): REAL =	(* real     number	*)
   VAR
      n			: REAL;
      Mantissa		: M2LONGCARD;
      Exponent		: INTEGER;
      MantissaNeg	: BOOLEAN;
      ExponentNeg	: BOOLEAN;
      FractionDigits	: Word.T;
      TruncatedDigits	: Word.T;
      ch		: CHAR;
   BEGIN
      MantissaNeg	:= FALSE;
      Mantissa		:= 0;
      Exponent		:= 0;
      FractionDigits	:= 0;
      TruncatedDigits	:= 0;

      REPEAT					(* skip white space	*)
	 ch := ReadC (f);
      UNTIL (ch # ' ') AND (ch # TabCh) AND (ch # EolCh);

      CASE ch OF				(* handle sign		*)
      | '+' => ch := ReadC (f);
      | '-' => ch := ReadC (f); MantissaNeg := TRUE;
      | 'E' => Mantissa := 1;
      ELSE
      END;

      WHILE ('0' <= ch) AND (ch <= '9') DO	(* integer part		*)
	 IF Mantissa <= MaxIntDiv10 THEN
	    Mantissa := 10 * Mantissa;
	    IF Mantissa 
               <= VAL (   MaxInt - (ORD (ch) - ORD ('0')),M2LONGCARD ) THEN
	       INC (Mantissa, ORD (ch) - ORD ('0'));
	    ELSE
	       INC (TruncatedDigits);
	    END;
	 ELSE
	    INC (TruncatedDigits);
	 END;
	 ch := ReadC (f);
      END;

      IF ch = '.' THEN ch := ReadC (f); END;	(* decimal point	*)

      WHILE ('0' <= ch) AND (ch <= '9') DO	(* fractional part	*)
	 IF Mantissa <= MaxIntDiv10 THEN
	    Mantissa := 10 * Mantissa;
	    IF Mantissa 
               <= VAL (   MaxInt - (ORD (ch) - ORD ('0')),M2LONGCARD ) THEN
	       INC (Mantissa, ORD (ch) - ORD ('0'));
	    ELSE
	       INC (TruncatedDigits);
	    END;
	 ELSE
	    INC (TruncatedDigits);
	 END;
	 INC (FractionDigits);
	 ch := ReadC (f);
      END;

      IF ch = 'E' THEN				(* exponent		*)
	 ch := ReadC (f);

	 CASE ch OF
	 |  '+' => ExponentNeg := FALSE; ch := ReadC (f);
	 |  '-' => ExponentNeg := TRUE ; ch := ReadC (f);
	 ELSE     ExponentNeg := FALSE;
	 END;

	 WHILE ('0' <= ch) AND (ch <= '9') DO
	    Exponent := (10 * Exponent) + LOOPHOLE (ORD (ch) - ORD ('0'),INTEGER);
	    ch := ReadC (f);
	 END;

	 IF ExponentNeg THEN
	    Exponent := - Exponent;
	 END;
      END;

      DEC (BufferPool [f].BufferIndex);
      DEC (Exponent, FractionDigits - TruncatedDigits);
      n := FLOAT (Mantissa) * Exp10 (Exponent);
      IF MantissaNeg
      THEN RETURN - n;
      ELSE RETURN   n;
      END;
   END ReadR;

PROCEDURE ReadB		(f: tFile): BOOLEAN =	(* boolean		*)
   BEGIN
      RETURN ReadC (f) = 'T';
   END ReadB;

PROCEDURE ReadN		(f: tFile; Base: INTEGER): INTEGER =
   VAR						(* number of base 'Base'*)
      n		: INTEGER;
      ch	: CHAR;
      digit	: INTEGER;
   BEGIN
      REPEAT
	 ch := ReadC (f);
      UNTIL (ch # ' ') AND (ch # TabCh) AND (ch # EolCh);
      n := 0;
      LOOP
	 IF ('0' <= ch) AND (ch <= '9') THEN
	    digit := ORD (ch) - ORD ('0');
	 ELSIF ('A' <= ch) AND (ch <= 'F') THEN
	    digit := ORD (ch) - ORD ('A') + 10;
	 ELSE
	    digit := 99;
	 END;
	 IF digit >= Base THEN EXIT; END;
	 n := (Base * n) + digit;
	 ch := ReadC (f);
      END;
      DEC (BufferPool [f].BufferIndex);
      RETURN n;
   END ReadN;

PROCEDURE ReadS		(f: tFile; VAR s: ARRAY OF CHAR) =
   BEGIN
      WITH m2tom3_with_13=BufferPool [f] DO
	 FOR i := 0 TO LAST (s) DO
	    IF m2tom3_with_13.BufferIndex = m2tom3_with_13.BytesRead THEN	(* ReadC inline		*)
	       FillBuffer (f);
	       IF m2tom3_with_13.EndOfFile THEN m2tom3_with_13.Buffer^ [1] := '\000'; END;
	    END;
	    INC (m2tom3_with_13.BufferIndex);
	    s [i] := m2tom3_with_13.Buffer^ [m2tom3_with_13.BufferIndex];
	 END;
      END;
   END ReadS;

PROCEDURE ReadShort	(f: tFile): SHORTINT =	(* shortint number	*)
   BEGIN
      RETURN VAL (   ReadI (f),SHORTINT );
   END ReadShort;

PROCEDURE ReadLong	(f: tFile): M2LONGINT =	(* longint  number	*)
   BEGIN
      RETURN VAL (   ReadI (f),M2LONGINT );
   END ReadLong;

PROCEDURE ReadCard	(f: tFile): Word.T =	(* cardinal number	*)
   BEGIN
      RETURN ReadI (f);
   END ReadCard;

PROCEDURE ReadNl	(f: tFile) =		(* new line		*)
   BEGIN
      REPEAT
      UNTIL ReadC (f) = EolCh;
   END ReadNl;

PROCEDURE UnRead	(f: tFile) =		(* backspace 1 char.	*)
   BEGIN
      DEC (BufferPool [f].BufferIndex);
   END UnRead;


PROCEDURE EndOfLine	(f: tFile): BOOLEAN =	(* end of line ?	*)
   BEGIN
      WITH m2tom3_with_14=BufferPool [f] DO
	 IF m2tom3_with_14.BufferIndex = m2tom3_with_14.BytesRead THEN
	    FillBuffer (f);
	    IF m2tom3_with_14.EndOfFile THEN m2tom3_with_14.Buffer^ [1] := '\000'; END;
	 END;
	 RETURN m2tom3_with_14.Buffer^ [m2tom3_with_14.BufferIndex + 1] = EolCh;
      END;
   END EndOfLine;

PROCEDURE EndOfFile	(f: tFile): BOOLEAN =	(* end of file ?	*)
   VAR ch : CHAR;
   BEGIN
      ch := ReadC (f);
      DEC (BufferPool [f].BufferIndex);
      RETURN BufferPool [f].EndOfFile;
   END EndOfFile;


PROCEDURE CheckFlushLine (f: tFile) =
   BEGIN
      BufferPool [f].FlushLine := System.IsCharacterSpecial (f);
   END CheckFlushLine;

PROCEDURE WriteOpen	(READONLY FileName: ARRAY OF CHAR): tFile =
   VAR						(* open  output file	*)
      f		: tFile;
   BEGIN
      f := System.OpenOutput (FileName);
      WITH m2tom3_with_15=BufferPool [f] DO
	 m2tom3_with_15.Buffer		:= Alloc (BufferSize + 1);
	 m2tom3_with_15.BufferIndex	:= 0;
	 m2tom3_with_15.OpenForOutput	:= TRUE;
      END;
      CheckFlushLine (f);
      RETURN f;
   END WriteOpen;

PROCEDURE WriteClose	(f: tFile) =		(* close output file	*)
   BEGIN
      WriteFlush (f);
      System.Close (f);
      WITH m2tom3_with_16=BufferPool [f] DO
	 Free (BufferSize + 1, m2tom3_with_16.Buffer);
	 m2tom3_with_16.Buffer := NIL;
      END;
   END WriteClose;

PROCEDURE WriteFlush	(f: tFile) =		(* flush output buffer	*)
   BEGIN
      WITH m2tom3_with_17=BufferPool [f] DO
	 m2tom3_with_17.BytesRead 
           := VAL ( 
                   System.Write 
                      (f, ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 396
 $$ *) (m2tom3_with_17.Buffer^ [1]), VAL (   m2tom3_with_17.BufferIndex,INTEGER ) ),SHORTINT
                  );
	 m2tom3_with_17.BufferIndex := 0;
      END;
   END WriteFlush;

PROCEDURE Write		(f: tFile; Buffer: ADDRESS; Size: INTEGER): INTEGER =
   VAR						(* binary		*)
      BufferPtr : UNTRACED BRANDED REF  ARRAY [0 .. 100000000] OF CHAR;
   BEGIN
      BufferPtr := Buffer;
      WITH m2tom3_with_18=BufferPool [f] DO
	 FOR i := 0 TO Size - 1 DO
	    INC (m2tom3_with_18.BufferIndex);			(* WriteC inline	*)
	    m2tom3_with_18.Buffer^ [m2tom3_with_18.BufferIndex] := BufferPtr^ [i];
	    IF (m2tom3_with_18.BufferIndex = BufferSize) THEN WriteFlush (f); END;
	 END;
      END;
      RETURN Size;
   END Write;

PROCEDURE WriteC	(f: tFile; c: CHAR) =	(* character		*)
   BEGIN
      WITH m2tom3_with_19=BufferPool [f] DO
	 INC (m2tom3_with_19.BufferIndex);
	 m2tom3_with_19.Buffer^ [m2tom3_with_19.BufferIndex] := c;
	 IF (m2tom3_with_19.BufferIndex = BufferSize) OR (m2tom3_with_19.FlushLine AND (c = EolCh)) THEN
	    WriteFlush (f);
	 END;
      END;
   END WriteC;

PROCEDURE WriteI	(f: tFile; n: INTEGER ; FieldWidth: Word.T) =
   VAR						(* integer  number	*)
      length	: Word.T;
      negative	: Word.T;
      digits	: ARRAY [0 .. 10] OF CHAR;
   BEGIN
      IF n < 0 THEN
	 negative := 1;
	 n := - n;
      ELSE
	 negative := 0;
      END;
      length := 0;
      REPEAT
	 INC (length);
	 digits [length] := MyCHR [n MOD 10];
	 n := n DIV 10;
      UNTIL n = 0;
      FOR i := 1 TO LOOPHOLE (FieldWidth - length - negative,INTEGER) DO
	 WriteC (f, ' ');
      END;
      IF negative = 1 THEN WriteC (f, '-'); END;
      FOR i := LOOPHOLE (length,INTEGER) TO 1 BY -1 DO
	 WriteC (f, digits [i]);
      END;
   END WriteI;

PROCEDURE WriteR	(f: tFile; n: REAL; Before, After, Exp: Word.T) =
   CONST					(* real   number	*)
      StartIndex	= 100;
   VAR
      i			: Word.T;
      FirstDigit	: Word.T;
      IntegerDigits	: Word.T;
      TotalDigits	: Word.T;
      IsNegative	: Word.T;
      Digits		: ARRAY [0 .. 200] OF Word.T;
      MaxCard		: REAL;
      MaxCardDiv10	: REAL;
      Mantissa		: M2LONGCARD;
      Exponent		: INTEGER;
   BEGIN
      MaxCard		:= FLOAT (MaxInt);
      MaxCardDiv10	:= FLOAT (MaxIntDiv10);

      IF n < 0.0 THEN				(* determine sign	*)
	 IsNegative := 1;
	 n := - n;
      ELSE
	 IsNegative := 0;
      END;

      IF n = 0.0 THEN		(* determine mantissa and exponent	*)
	 Mantissa := 0;
	 Exponent := 1;
      ELSE
	 Exponent := 10;			(* normalize mantissa	*)
	 WHILE n > MaxCard DO
	    n := n / 10.0;
	    INC (Exponent);
	 END;
	 WHILE n <= MaxCardDiv10 DO
	    n := n * 10.0;
	    DEC (Exponent);
	 END;
	 Mantissa := VAL (   TRUNC (n),M2LONGCARD );
	 IF Mantissa < MaxPow10 THEN
	    DEC (Exponent);
	 END;
      END;
      						(* determine size of:	*)
      IF (Exp > 0) OR (Exponent <= 0) THEN	(* integer part		*)
	 IntegerDigits := 1;
      ELSE
	 IntegerDigits := Exponent;
      END;
      IF After = 0 THEN After := 1; END;	(* fractional part	*)
      TotalDigits := IntegerDigits + After;	(* total # of digits	*)

      FirstDigit := StartIndex;			(* convert mantissa	*)
      REPEAT
	 DEC (FirstDigit);
	 Digits [FirstDigit] := Mantissa MOD 10;
	 Mantissa := Mantissa DIV 10;
      UNTIL Mantissa = 0;
      IF Exp = 0 THEN				(* add leading zeroes	*)
	 FOR j := 1 TO 1 - Exponent DO
	    DEC (FirstDigit);
	    Digits [FirstDigit] := 0;
	 END;
      END;
      FOR i := StartIndex TO FirstDigit + TotalDigits DO
	 Digits [i] := 0;			(* add trailing zeroes	*)
      END;

      Digits [FirstDigit - 1] := 0;		(* round mantissa	*)
      IF Digits [FirstDigit + TotalDigits] >= 5 THEN
	 i := FirstDigit + TotalDigits - 1;
	 WHILE Digits [i] = 9 DO		(* carry		*)
	    Digits [i] := 0;
	    DEC (i);
	 END;
	 INC (Digits [i]);
	 IF i = (FirstDigit - 1) THEN (* carry at most significant pos.	*)
	    FirstDigit := i;
	    IF Exp > 0 THEN
	       INC (Exponent);
	    ELSIF Exponent > 0 THEN
	       INC (IntegerDigits);
	    END;
	 END;
      END;
						(* print mantissa	*)
      FOR j := 1 TO LOOPHOLE (Before - IsNegative - IntegerDigits,INTEGER) DO
	 WriteC (f, ' ');			(* leading spaces	*)
      END;
      IF IsNegative = 1 THEN WriteC (f, '-'); END;	(* sign		*)
      FOR i :=  1 TO IntegerDigits DO		(* integer part		*)
	 WriteC (f, MyCHR [Digits [FirstDigit]]);
	 INC (FirstDigit);
      END;
      WriteC (f, '.');				(* decimal point	*)
      FOR i :=  1 TO After DO			(* fractional part	*)
	 WriteC (f, MyCHR [Digits [FirstDigit]]);
	 INC (FirstDigit);
      END;

      IF Exp > 0 THEN				(* print exponent	*)
	 DEC (Exponent);
	 WriteC (f, 'E');
	 IF Exponent < 0 THEN
	    WriteC (f, '-');
	    Exponent := - Exponent;
	 ELSE
	    WriteC (f, '+');
	 END;
	 WriteN (f, VAL (   Exponent,M2LONGCARD ) , Exp - 1, 10);
      END;
   END WriteR;

PROCEDURE WriteB	(f: tFile; b: BOOLEAN) =	(* boolean		*)
   BEGIN
      IF b
      THEN WriteC (f, 'T');
      ELSE WriteC (f, 'F');
      END;
   END WriteB;

PROCEDURE WriteN	(f: tFile; n: M2LONGCARD; FieldWidth, Base: Word.T) =
   VAR						(* number of base 'Base'*)
      length	: Word.T;
      digits	: ARRAY [0 .. 32] OF CHAR;
   BEGIN
      length := 0;
      REPEAT
	 INC (length);
	 digits [length] 
           := MyCHR [ VAL (   n MOD VAL (   Base,M2LONGCARD ),INTEGER ) ];
	 n := n DIV VAL (   Base,M2LONGCARD );
      UNTIL n = 0;
      FOR i := 1 TO LOOPHOLE (FieldWidth - length,INTEGER) DO
	 WriteC (f, '0');
      END;
      FOR i := LOOPHOLE (length,INTEGER) TO 1 BY -1 DO
	 WriteC (f, digits [i]);
      END;
   END WriteN;

PROCEDURE WriteS	(f: tFile;READONLY  (*VAR*)s: ARRAY OF CHAR) = 
   VAR c	: CHAR;
   BEGIN
      WITH m2tom3_with_20=BufferPool [f] DO
	 FOR i := 0 TO LAST (s) DO
	    c := s [i];
	    IF c = '\000' THEN RETURN; END;
	    INC (m2tom3_with_20.BufferIndex);			(* WriteC inline	*)
	    m2tom3_with_20.Buffer^ [m2tom3_with_20.BufferIndex] := c;
	    IF (m2tom3_with_20.BufferIndex = BufferSize) OR (m2tom3_with_20.FlushLine AND (c = EolCh)) THEN
	       WriteFlush (f);
	    END;
	 END;
      END;
   END WriteS;

PROCEDURE WriteShort	(f: tFile; n: SHORTINT; FieldWidth: Word.T) =
   BEGIN					(* shortint number	*)
      WriteI (f, VAL (   n,INTEGER ) , FieldWidth);
   END WriteShort;

PROCEDURE WriteLong	(f: tFile; n: M2LONGINT ; FieldWidth: Word.T) =
   BEGIN					(* longint  number	*)
      WriteI (f, VAL (   n,INTEGER ) , FieldWidth);
   END WriteLong;

PROCEDURE WriteCard	(f: tFile; n: Word.T; FieldWidth: Word.T) =
   VAR						(* cardinal number	*)
      length	: Word.T;
      digits	: ARRAY [0 .. 10] OF CHAR;
   BEGIN
      length := 0;
      REPEAT
	 INC (length);
	 digits [length] := MyCHR [n MOD 10];
	 n := n DIV 10;
      UNTIL n = 0;
      FOR i := 1 TO LOOPHOLE (FieldWidth - length,INTEGER) DO
	 WriteC (f, ' ');
      END;
      FOR i := length TO 1 BY -1 DO
	 WriteC (f, digits [i]);
      END;
   END WriteCard;

PROCEDURE WriteNl	(f: tFile) =		(* new line		*)
   BEGIN
      WriteC (f, EolCh);
   END WriteNl;


PROCEDURE CloseIO() =				(* close all files	*)
   BEGIN
      FOR i := 0 TO System.cMaxFile DO
	 WITH m2tom3_with_21=BufferPool [i] DO
	    IF m2tom3_with_21.Buffer # NIL THEN
	       IF m2tom3_with_21.OpenForOutput THEN
		  WriteClose (i);
	       ELSE
		  ReadClose (i);
	       END;
	    END;
	 END;
      END;
   END CloseIO;

BEGIN
   MyCHR [ 0] := '0';
   MyCHR [ 1] := '1';
   MyCHR [ 2] := '2';
   MyCHR [ 3] := '3';
   MyCHR [ 4] := '4';
   MyCHR [ 5] := '5';
   MyCHR [ 6] := '6';
   MyCHR [ 7] := '7';
   MyCHR [ 8] := '8';
   MyCHR [ 9] := '9';
   MyCHR [10] := 'A';
   MyCHR [11] := 'B';
   MyCHR [12] := 'C';
   MyCHR [13] := 'D';
   MyCHR [14] := 'E';
   MyCHR [15] := 'F';

   FOR i := 0 TO System.cMaxFile DO
      WITH m2tom3_with_22=BufferPool [i] DO
	 m2tom3_with_22.Buffer		:= NIL;
	 m2tom3_with_22.BufferIndex	:= 0;
	 m2tom3_with_22.BytesRead	:= 0;
	 m2tom3_with_22.OpenForOutput	:= FALSE;
	 m2tom3_with_22.EndOfFile	:= FALSE;
	 m2tom3_with_22.FlushLine	:= FALSE;
      END;
   END;

   BufferPool [StdInput ].Buffer := Alloc (BufferSize + 1);
   BufferPool [StdOutput].Buffer := Alloc (BufferSize + 1);
   BufferPool [StdError ].Buffer := Alloc (BufferSize + 1);

   BufferPool [StdInput ].OpenForOutput := FALSE;
   BufferPool [StdOutput].OpenForOutput := TRUE;
   BufferPool [StdError ].OpenForOutput := TRUE;

   CheckFlushLine (StdInput );
   CheckFlushLine (StdOutput);
   CheckFlushLine (StdError );
END ReuseIO.

