(* $Id: System.md,v 1.8 1992/09/24 13:06:53 grosch rel $ *)

(* $Log: System.md,v $
 * Revision 1.8  1992/09/24  13:06:53  grosch
 * adaption to MS-DOS
 *
 * Revision 1.7  1992/02/04  08:38:39  grosch
 * correction of new system interface
 *
 * Revision 1.6  1992/01/30  13:23:29  grosch
 * redesign of interface to operating system
 *
 * Revision 1.5  1992/01/28  16:59:23  grosch
 * revision of the Makefile
 *
 * Revision 1.4  1991/11/21  14:35:51  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.3  91/03/20  09:29:48  grosch
 * added malloc as alternative to sbrk
 * 
 * Revision 1.2  89/08/09  12:00:48  grosch
 * added return value to svc-call system
 * 
 * Revision 1.1  89/03/02  17:32:24  grosch
 * added system call named 'system'
 * 
 * Revision 1.0  88/10/04  11:47:33  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Jan. 1992 *)

UNSAFE INTERFACE  System; (* interface for machine dependencies   *)



FROM SYSTEM IMPORT M2LONGINT;
IMPORT OSError; 
IMPORT Word;

EXCEPTION TooManyFiles; 
CONST
   cMaxFile     = 32;
   StdInput     = 0;
   StdOutput    = 1;
   StdError     = 2;

TYPE tFile      = [-1 .. cMaxFile];

                        (* binary IO            *)

PROCEDURE OpenInput (READONLY FileName: ARRAY OF CHAR): tFile
    RAISES {OSError.T, TooManyFiles}; 
PROCEDURE OpenOutput    (READONLY FileName: ARRAY OF CHAR): tFile
    RAISES {OSError.T, TooManyFiles};
PROCEDURE Read          (File: tFile; Buffer: ADDRESS; Size: INTEGER): INTEGER;
PROCEDURE Write         (File: tFile; Buffer: ADDRESS; Size: INTEGER): INTEGER;
PROCEDURE Close         (File: tFile);
PROCEDURE IsCharacterSpecial (File: tFile): BOOLEAN;

                        (* calls other than IO  *)

PROCEDURE SysAlloc      (ByteCount: M2LONGINT): ADDRESS;
PROCEDURE Time          (): M2LONGINT;
PROCEDURE GetArgCount   (): Word.T;
PROCEDURE GetArgument   (ArgNum: INTEGER; VAR Argument: ARRAY OF CHAR);
PROCEDURE PutArgs       (Argc: INTEGER; Argv: ADDRESS);
PROCEDURE ErrNum        (): INTEGER;
PROCEDURE System        (VAR String: ARRAY OF CHAR): INTEGER;
PROCEDURE Exit          (Status: INTEGER);

END System.

