(* $Id: IO.md,v 1.5 1992/01/30 13:23:29 grosch rel $ *)

(* $Log: IO.md,v $

 * RMB: 93/10/11
        Changed param s of WriteS and Filename of ReadOpen and WriteOpen
        not to be VAR, so many calls thereon, in this package and 
        elsewhere, which pass a string literal, are legal in
        WRL Modula-2. 

 * Revision 1.5  1992/01/30  13:23:29  grosch
 * redesign of interface to operating system
 *
 * Revision 1.4  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.3  89/08/18  11:11:28  grosch
 * make Write work for Size = 0
 * 
 * Revision 1.2  89/07/14  16:26:27  grosch
 * made WriteN work for numbers with MSBit set
 * 
 * Revision 1.1  89/01/24  19:04:20  grosch
 * added procedure UnRead
 * 
 * Revision 1.0  88/10/04  11:46:57  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

UNSAFE INTERFACE  ReuseIO;				(* buffered IO		*)



FROM SYSTEM IMPORT M2LONGINT, M2LONGCARD;
FROM SYSTEM IMPORT SHORTINT;
IMPORT Word, System;

CONST
   StdInput	= System.StdInput;
   StdOutput	= System.StdOutput;
   StdError	= System.StdError;

TYPE
   tFile	= System.tFile;

PROCEDURE ReadOpen	(READONLY (*VAR*) FileName: ARRAY OF CHAR): tFile;
						(* open  input file	*)
PROCEDURE ReadClose	(f: tFile);		(* close input file	*)
PROCEDURE Read		(f: tFile; Buffer: ADDRESS; Size: Word.T): INTEGER;
						(* binary		*)
PROCEDURE ReadC		(f: tFile): CHAR    ;	(* character		*)
PROCEDURE ReadI		(f: tFile): INTEGER ;	(* integer  number	*)
PROCEDURE ReadR		(f: tFile): REAL    ;	(* real     number	*)
PROCEDURE ReadB		(f: tFile): BOOLEAN ;	(* boolean		*)
PROCEDURE ReadN		(f: tFile; Base: INTEGER): INTEGER;
						(* number of base 'Base'*)
PROCEDURE ReadS		(f: tFile; VAR s: ARRAY OF CHAR);
						(* string		*)
PROCEDURE ReadShort	(f: tFile): SHORTINT;	(* shortint number ?	*)
PROCEDURE ReadLong	(f: tFile): M2LONGINT ;	(* longint  number ?	*)
PROCEDURE ReadCard	(f: tFile): Word.T;	(* cardinal number ?	*)
PROCEDURE ReadNl	(f: tFile);		(* new line		*)
PROCEDURE UnRead	(f: tFile);		(* backspace 1 char.	*)

PROCEDURE EndOfLine	(f: tFile): BOOLEAN ;	(* end of line ?	*)
(* NOTE!!! TRUE if we are _about to_ read the new line, _not_ have read it. *) 
PROCEDURE EndOfFile	(f: tFile): BOOLEAN ;	(* end of file ?	*)

PROCEDURE WriteOpen	(READONLY FileName: ARRAY OF CHAR): tFile;
						(* open  output file	*)
PROCEDURE WriteClose	(f: tFile);		(* close output file	*)
PROCEDURE WriteFlush	(f: tFile);		(* flush output buffer	*)
PROCEDURE Write		(f: tFile; Buffer: ADDRESS; Size: INTEGER): INTEGER;
						(* binary		*)
PROCEDURE WriteC	(f: tFile; c: CHAR);	(* character		*)
PROCEDURE WriteI	(f: tFile; n: INTEGER ; FieldWidth: Word.T);
						(* integer  number	*)
PROCEDURE WriteR	(f: tFile; n: REAL; Before, After, Exp: Word.T);
						(* real     number	*)
PROCEDURE WriteB	(f: tFile; b: BOOLEAN);	(* boolean		*)
PROCEDURE WriteN	(f: tFile; n: INTEGER; FieldWidth, Base: Word.T);
						(* number of base 'Base'*)
PROCEDURE WriteS	(f: tFile;READONLY  (*VAR*) s: ARRAY OF CHAR); 
						(* string		*)
PROCEDURE WriteShort	(f: tFile; n: SHORTINT; FieldWidth: Word.T);
						(* shortint number ?	*)
PROCEDURE WriteLong	(f: tFile; n: M2LONGINT ; FieldWidth: Word.T);
						(* longint  number ?	*)
PROCEDURE WriteCard	(f: tFile; n: Word.T; FieldWidth: Word.T);
						(* cardinal number ?	*)
PROCEDURE WriteNl	(f: tFile);		(* new line		*)


PROCEDURE CloseIO();				(* close all files	*)

END ReuseIO.

