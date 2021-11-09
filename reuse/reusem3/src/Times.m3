(* $Id: Times.mi,v 1.3 1992/02/04 08:38:39 grosch rel $ *)

(* $Log: Times.mi,v $

 * RMB 93/10/13 Type conversions for WRL.

 * Revision 1.3  1992/02/04  08:38:39  grosch
 * correction of new system interface
 *
 * Revision 1.2  1992/01/30  13:23:29  grosch
 * redesign of interface to operating system
 *
 * Revision 1.1  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  11:47:39  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

 UNSAFE MODULE Times;

FROM SYSTEM IMPORT M3LONGINT;
FROM System	IMPORT Time;
FROM IO		IMPORT StdOutput, WriteS, WriteI, WriteNl;

VAR PrevTime	: M3LONGINT;

PROCEDURE CpuTime (): M3LONGINT =
   BEGIN
      RETURN Time ();
   END CpuTime;

PROCEDURE StepTime (): M3LONGINT =
   VAR
      ActTime	: M3LONGINT;
      DeltaTime	: M3LONGINT;
   BEGIN
      ActTime	:= CpuTime ();
      DeltaTime	:= ActTime - PrevTime;
      PrevTime	:= ActTime;
      RETURN DeltaTime;
   END StepTime;

PROCEDURE WriteStepTime (READONLY Text: ARRAY OF CHAR) =
   BEGIN
      WriteS (StdOutput, Text);
      WriteI (StdOutput, VAL (   StepTime (),INTEGER ), 5);
      WriteNl (StdOutput);
   END WriteStepTime;

BEGIN
   PrevTime := 0;
END Times.

