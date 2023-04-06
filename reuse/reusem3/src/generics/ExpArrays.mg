
(* -----------------------------------------------------------------------1- *)
(* This file is part of the FM3 Modula-3 compiler.                           *)
(* Copyright 2023,       Rodney M. Bates.                                    *)
(* rodney.m.bates@acm.org                                                    *)
(* Licensed under the MIT License.                                           *)

GENERIC MODULE ExpArrays ( Elem ) 

(* Instantiating interface Elem must provide:
  TYPE T (* Type of array elements, not open. *)
  CONST Brand : TEXT
*)

(*EXPORTED*) 
; PROCEDURE Expand
    ( VAR ArrayRef : ArrayRefTyp
    ; RequiredNum : INTEGER )
    ; ExpandTo := -1
    )

  (* IF NUMBER(ArrayRef^) < RequiredNum, replace ArrayRef by one
     whose NUMBER is MAX (RequiredNum, ExpandTo), copying elements
     of the old array to the new.
     If ExpandTo = -1, instead use 2*RequiredNum. 
  )*

  = VAR LOldArrayRef : ArrayRefTyp
  ; VAR LArrayNumber : INTEGER
  ; BEGIN
      LArrayNumber := NUMBER ( ArrayRef ^ )
    ; IF LArrayNumber < RequiredNum 
      THEN
        LOldArrayRef := ArrayRef
      ; IF ExpandTo = - 1
        THEN LNewNumber := RequiredNum * 2 
        ELSE LNewNumber := MAX ( RequiredNum , ExpandTo )
        END (*IF*)
      ; ArrayRef := NEW ( ArrayRefTyp , LNewNumber )
      ; SUBARRAY ( ArrayRef ^ , 0 , LArrayNumber ) := LOldArrayRef ^
      ; LOldArrayRef := NIL (* GC bait *)
      END 
    END Expand

; BEGIN
  END ExpArrays
.



