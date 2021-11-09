(* $Id: Classes.md,v 3.2 1991/11/21 14:41:19 grosch rel $ *)

(* $Log: Classes.md,v $
Revision 3.2  1991/11/21  14:41:19  grosch
fixed bug: interference of right context between constant and non-constant RE
new version of RCS on SPARC

Revision 3.1  91/04/08  15:50:11  grosch
release memory after use in Classes and Tree0

Revision 3.0  91/04/04  18:26:37  grosch
Initial revision

 *)

(* Ich, Doktor Josef Grosch, Informatiker, March 1991 *)

UNSAFE INTERFACE  Classes;

FROM Sets(* $$ m2tom3 warning: unable to find interface for import 'Sets' in line 20
 $$ *)	IMPORT tSet;

TYPE ClassInfo	= RECORD Set, Classes: tSet; END;

VAR
   CharSet, Unused	: tSet;
   ToClass, ToChar	: ARRAY CHAR OF CHAR;

   SetMemPtr	: UNTRACED BRANDED REF  ARRAY [0 .. 100000] OF ClassInfo;
   SetMemSize	: LONGINT;
   SetCount	: INTEGER;

   ClassMemPtr	: UNTRACED BRANDED REF  ARRAY CHAR OF tSet;
   ClassMemSize	: LONGINT;
   ClassCount	: CHAR;

PROCEDURE IsInSetMem (Set: tSet): INTEGER;
PROCEDURE ComputeClasses (Blocking: BOOLEAN);
PROCEDURE ReleaseSetMem();

END Classes.

