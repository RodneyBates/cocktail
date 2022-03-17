
(* $Id: Relations.md,v 1.4 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: Relations.md,v $ 
 
 * RMB July 98 Documentation/name changes. 
 
 * RMB 93/10/12 Type changes. 
 
Revision 1.4  1991/11/21  14:33:17  grosch 
new version of RCS on SPARC 
 
Revision 1.3  91/06/07  12:19:55  grosch 
decreased bounds of flexible arrays 
 
Revision 1.2  91/06/07  11:37:46  grosch 
increased bounds of flexible arrays 
 
Revision 1.1  90/06/11  10:40:58  grosch 
added procedure GetCyclics 
 
Revision 1.0  89/11/02  18:24:47  grosch 
Initial revision 
 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, 8.1.1988 *) 

UNSAFE INTERFACE Relations 

; FROM ReuseIO IMPORT tFile 

; FROM Sets IMPORT tSet 

; CONST Bound = 10000000 

      (* ^mtc and/or cc get crabby if you make this too large. *) 

; TYPE Bounds = [ 0 .. Bound ] 
  ; ArrayOfSet = ARRAY Bounds OF tSet 
  ; ProcOfIntInt = PROCEDURE ( p0 : INTEGER ; p1 : INTEGER ) 
  ; ProcOfIntIntToBool = PROCEDURE ( p0 : INTEGER ; p1 : INTEGER ) : BOOLEAN 

  ; tRelation 
    = RECORD (* Treat as opaque *) 
        ArrayPtr : UNTRACED BRANDED REF ArrayOfSet 
      ; Max1 

(* Change this to Max1 and recompile *) 

        , Max2 
        : INTEGER 
      END (* RECORD *) 

; PROCEDURE MakeRelation ( VAR Rel : tRelation ; Max1 , Max2 : INTEGER ) 

; PROCEDURE ReleaseRelation ( VAR Rel : tRelation ) 

; PROCEDURE Include ( VAR Rel : tRelation ; e1 , e2 : INTEGER ) 

; PROCEDURE Exclude ( VAR Rel : tRelation ; e1 , e2 : INTEGER ) 

; PROCEDURE IsElement ( e1 , e2 : INTEGER ; Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsRelated ( e1 , e2 : INTEGER ; Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsReflexive1 ( e1 : INTEGER ; Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsSymmetric1 ( e1 , e2 : INTEGER ; Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsTransitive1 
    ( e1 , e2 , e3 : INTEGER ; Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsReflexive ( Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsSymmetric ( Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsTransitive ( Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsEquivalence ( Rel : tRelation ) : BOOLEAN 

; PROCEDURE HasReflexive ( Rel : tRelation ) : BOOLEAN 

; PROCEDURE IsCyclic ( Rel : tRelation ) : BOOLEAN 

; PROCEDURE GetCyclics ( Rel : tRelation ; VAR Set : tSet ) 

; PROCEDURE Closure ( VAR Rel : tRelation ) 

; PROCEDURE AssignEmpty ( VAR Rel : tRelation ) 

; PROCEDURE AssignElmt ( VAR Rel : tRelation ; e1 , e2 : INTEGER ) 

; PROCEDURE Assign ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

; PROCEDURE Union ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

; PROCEDURE Difference ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

; PROCEDURE Intersection ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

; PROCEDURE SymDiff ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

; PROCEDURE Complement ( VAR Rel : tRelation ) 

; PROCEDURE IsSubset ( Rel1 , Rel2 : tRelation ) : BOOLEAN 

; PROCEDURE IsStrictSubset ( Rel1 , Rel2 : tRelation ) : BOOLEAN 

; PROCEDURE IsEqual ( VAR Rel1 , Rel2 : tRelation ) : BOOLEAN 

; PROCEDURE IsNotEqual ( Rel1 , Rel2 : tRelation ) : BOOLEAN 

; PROCEDURE IsEmpty ( Rel : tRelation ) : BOOLEAN 

; PROCEDURE Card ( VAR Rel : tRelation ) : INTEGER 

; PROCEDURE Select ( VAR Rel : tRelation ; VAR e1 , e2 : INTEGER ) 

; PROCEDURE Extract ( VAR Rel : tRelation ; VAR e1 , e2 : INTEGER ) 

; PROCEDURE Forall ( Rel : tRelation ; Proc : ProcOfIntIntToBool ) : BOOLEAN 

; PROCEDURE Exists ( Rel : tRelation ; Proc : ProcOfIntIntToBool ) : BOOLEAN 

; PROCEDURE Exists1 ( Rel : tRelation ; Proc : ProcOfIntIntToBool ) : BOOLEAN 

; PROCEDURE ForallDo ( Rel : tRelation ; Proc : ProcOfIntInt ) 

; PROCEDURE ReadRelation ( f : tFile ; VAR Rel : tRelation ) 

; PROCEDURE WriteRelation ( f : tFile ; Rel : tRelation ) 

; 
END Relations 
. 

