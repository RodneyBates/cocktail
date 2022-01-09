(* $Id: StdIO.mi,v 1.3 1991/11/21 14:33:17 grosch rel $ *)

(* $Log: StdIO.mi,v $
 * Revision 1.3  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  89/07/14  16:27:23  grosch
 * made WriteN work for numbers with MSBit set
 * 
 * Revision 1.1  89/01/24  19:04:43  grosch
 * added procedure UnRead
 * 
 * Revision 1.0  88/10/04  11:47:16  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

 UNSAFE MODULE StdIO;			(* buffered standard IO	*)


FROM SYSTEM IMPORT M2LONGINT, M2LONGCARD;
FROM SYSTEM IMPORT SHORTINT;
FROM ReuseIO	    IMPORT StdInput, StdOutput;

IMPORT Word, ReuseIO;

PROCEDURE ReadClose()	 =			(* close input file	*)
   BEGIN
      ReuseIO.ReadClose (StdInput);
   END ReadClose;

PROCEDURE Read		(Buffer: ADDRESS; Size: Word.T): INTEGER =
   BEGIN					(* binary		*)
      RETURN ReuseIO.Read (StdInput, Buffer, Size);
   END Read;

PROCEDURE ReadC		(): CHAR     =		(* character		*)
   BEGIN
      RETURN ReuseIO.ReadC (StdInput);
   END ReadC;

PROCEDURE ReadI		(): INTEGER  =		(* integer  number	*)
   BEGIN
      RETURN ReuseIO.ReadI (StdInput);
   END ReadI;

PROCEDURE ReadR		(): REAL     =		(* real     number	*)
   BEGIN
      RETURN ReuseIO.ReadR (StdInput);
   END ReadR;

PROCEDURE ReadB		(): BOOLEAN  =		(* boolean		*)
   BEGIN
      RETURN ReuseIO.ReadB (StdInput);
   END ReadB;

PROCEDURE ReadN		(Base: INTEGER): INTEGER =
   BEGIN					(* number of base 'Base'*)
      RETURN ReuseIO.ReadN (StdInput, Base);
   END ReadN;

PROCEDURE ReadS		(VAR s: ARRAY OF CHAR) =	(* string		*)
   BEGIN
      ReuseIO.ReadS (StdInput, s);
   END ReadS;

PROCEDURE ReadShort	(): SHORTINT =		(* shortint number ?	*)
   BEGIN
      RETURN ReuseIO.ReadShort (StdInput);
   END ReadShort;

PROCEDURE ReadLong	(): M2LONGINT  =		(* longint  number ?	*)
   BEGIN
      RETURN ReuseIO.ReadLong (StdInput);
   END ReadLong;

PROCEDURE ReadCard	(): Word.T =		(* cardinal number ?	*)
   BEGIN
      RETURN ReuseIO.ReadCard (StdInput);
   END ReadCard;

PROCEDURE ReadNl()	 =			(* new line		*)
   BEGIN
      ReuseIO.ReadNl (StdInput);
   END ReadNl;

PROCEDURE UnRead()	 =			(* backspace 1 char.	*)
   BEGIN
      ReuseIO.UnRead (StdInput);
   END UnRead;


PROCEDURE EndOfLine	(): BOOLEAN  =		(* end of line ?	*)
   BEGIN
      RETURN ReuseIO.EndOfLine (StdInput);
   END EndOfLine;

PROCEDURE EndOfFile	(): BOOLEAN  =		(* end of file ?	*)
   BEGIN
      RETURN ReuseIO.EndOfFile (StdInput);
   END EndOfFile;



PROCEDURE WriteClose()	 =			(* close output file	*)
   BEGIN
      ReuseIO.WriteClose (StdOutput);
   END WriteClose;

PROCEDURE WriteFlush()	 =			(* flush output buffer	*)
   BEGIN
      ReuseIO.WriteFlush (StdOutput);
   END WriteFlush;

PROCEDURE Write		(Buffer: ADDRESS; Size: Word.T): INTEGER =
   BEGIN					(* binary		*)
      RETURN ReuseIO.Write (StdOutput, Buffer, Size);
   END Write;

PROCEDURE WriteC	(c: CHAR) =		(* character		*)
   BEGIN
      ReuseIO.WriteC (StdOutput, c);
   END WriteC;

PROCEDURE WriteI	(n: INTEGER ; FieldWidth: Word.T) =
   BEGIN					(* integer  number	*)
      ReuseIO.WriteI (StdOutput, n, FieldWidth);
   END WriteI;

PROCEDURE WriteR	(n: REAL; Before, After, Exp: Word.T) =
   BEGIN					(* real     number	*)
      ReuseIO.WriteR (StdOutput, n, Before, After, Exp);
   END WriteR;

PROCEDURE WriteB	(b: BOOLEAN) =		(* boolean		*)
   BEGIN
      ReuseIO.WriteB (StdOutput, b);
   END WriteB;

PROCEDURE WriteN	(n: M2LONGCARD; FieldWidth, Base: Word.T) =
   BEGIN					(* number of base 'Base'*)
      ReuseIO.WriteN (StdOutput, n, FieldWidth, Base);
   END WriteN;

PROCEDURE WriteS	(READONLY s: ARRAY OF CHAR) =	(* string		*)
   BEGIN
      ReuseIO.WriteS (StdOutput, s);
   END WriteS;

PROCEDURE WriteT        (t: TEXT) =             (* M3 TEXT              *)
   BEGIN
      ReuseIO.WriteT (StdOutput, t);
   END WriteT;

PROCEDURE WriteShort	(n: SHORTINT; FieldWidth: Word.T) =
   BEGIN					(* shortint number ?	*)
      ReuseIO.WriteShort (StdOutput, n, FieldWidth);
   END WriteShort;

PROCEDURE WriteLong	(n: M2LONGINT ; FieldWidth: Word.T) =
   BEGIN					(* longint  number ?	*)
      ReuseIO.WriteLong (StdOutput, n, FieldWidth);
   END WriteLong;

PROCEDURE WriteCard	(n: Word.T; FieldWidth: Word.T) =
   BEGIN					(* cardinal number ?	*)
      ReuseIO.WriteCard (StdOutput, n, FieldWidth);
   END WriteCard;

PROCEDURE WriteNl()	 =			(* new line		*)
   BEGIN
      ReuseIO.WriteNl (StdOutput);
   END WriteNl;


PROCEDURE CloseIO() =				(* close all files	*)
   BEGIN
      ReuseIO.WriteFlush (StdOutput);
   END CloseIO;

BEGIN
END StdIO.

