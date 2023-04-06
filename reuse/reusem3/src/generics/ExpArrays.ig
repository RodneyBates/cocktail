
(* -----------------------------------------------------------------------1- *)
(* This file is part of the FM3 Modula-3 compiler.                           *)
(* Copyright 2023,       Rodney M. Bates.                                    *)
(* rodney.m.bates@acm.org                                                    *)
(* Licensed under the MIT License.                                           *)

GENERIC INTERFACE ExpArrays ( Elem ) 

(* Instantiating interface Elem must provide:
  TYPE T (* Type of array elements, not open. *)
  CONST Brand : TEXT
*)

; CONST Brand = "ExpArrays_" & Elem . Brand 

; TYPE ElemTyp = Elem . T
; TYPE ArrayRefTyp = REF ARRAY OF ElemTyp 

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

; END ExpArrays
.


