INTERFACE SYSTEM;

(***************************************************************************)
(**                  This file is part of m2tom3
       (C) 1991-1994 Lehrstuhl fuer Informatik III, RWTH Aachen
                         All Rights Reserved
*)
(** Created by:  Markus Jansen                                             *)

(** pk
    1.1
    1994/11/30 15:03:04
    SYSTEM.i3,v
# Revision 1.1  1994/11/30  15:03:04  pk
# Release Version 2.00.
#
*)
(***************************************************************************)

(** --- SYSTEM -----------------------------------------------------------------
  * This 'real' module should help to realize some features of the pseudo
  * module SYSTEM from Modula-2.
  *
  * Beware that not all features can be handled nor all handled features are
  * handled like Modula-2 does.
  * ----------------------------------------------------------------------------
  **)

(* Modified for use in gmd. RMB. *)
(* Modula-2 predefined types that are not builtin to Modula3 with
   the same name. *)

  (* Code that is to use this interface is converted from Modula2
     and subsequently further modified.  It was developed and run
     successfully in Modula2, in the days of 32-bit machines, when
     Modula2 LONGINT and LONGCARD were 32-bits.  Client code of this
     interface is/will be modified to replace LONGINT with M2LONGINT
     and LONGCARD with M3LONGCARD.  This will make converted code
     adapt to the native word size. *)

IMPORT Long;
IMPORT Word;

TYPE
  BYTE = (* BITS 8 FOR *) [0 .. 255];
  WORD = Word.T;

  BYTEINT = (* BITS 8 FOR *) [-128 .. 127];
  SHORTINT = (*BITS 16 FOR *) [-32768 .. 32767];
  M2LONGINT = INTEGER;
  (*LONGINT = INTEGER; Builtin to Modula3. *)

BYTECARD = (* BITS 8 FOR *) [0 .. 256];
  SHORTCARD = (* BITS 16 FOR *) [0 .. 65535];
  M2LONGCARD = Long.T;
  (* LONGCARD = Long.T; Builtin to Modula3. *)

  BYTEBITSET = (* BITS 8 FOR *) SET OF [0 .. 7];
  SHORTBITSET = (* BITS 16 FOR *) SET OF [0 .. 15];
  BITSET = SET OF [0 .. BITSIZE(WORD) - 1];

  PROC = PROCEDURE ();
  PROCESS = ADDRESS;

PROCEDURE HALT ();
  (* Modula-2 standard procedure to terminate a program *)

PROCEDURE ODD (i: INTEGER): BOOLEAN;
  (* Modula-2's ODD function *)

END SYSTEM.
