
(* $Id: SetsC.md,v 1.2 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: SetsC.md,v $ 
 
 * RMB 97/06/05 Added InitNullSet, since some tree dumps call 
                WriteSet for sets which are not in use and need 
                no allocated array. 
 
Revision 1.2  1991/11/21  14:33:17  grosch 
new version of RCS on SPARC 
 
Revision 1.1  89/02/23  16:02:11  grosch 
Initial revision 
 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Feb. 1989 *) 

UNSAFE INTERFACE SetsC 

; FROM ReuseIO IMPORT tFile 

; IMPORT Word , Sets 

; TYPE ProcOftElement = Sets . ProcOftElement 
  ; ProcOftElementToBool = Sets . ProcOftElementToBool 
  ; tSet = Sets . tSet 

; PROCEDURE InitNullSet ( VAR Set : tSet ) 

; PROCEDURE MakeSet ( VAR Set : tSet ; MaxSize : Word . T ) 

; PROCEDURE ReleaseSet ( VAR Set : tSet ) 

; PROCEDURE Union ( VAR Set1 : tSet ; Set2 : tSet ) 

; PROCEDURE Difference ( VAR Set1 : tSet ; Set2 : tSet ) 

; PROCEDURE Intersection ( VAR Set1 : tSet ; Set2 : tSet ) 

; PROCEDURE SymDiff ( VAR Set1 : tSet ; Set2 : tSet ) 

; PROCEDURE Complement ( VAR Set : tSet ) 

; PROCEDURE Include ( VAR Set : tSet ; Elmt : Word . T ) 

; PROCEDURE Exclude ( VAR Set : tSet ; Elmt : Word . T ) 

; PROCEDURE Card ( VAR Set : tSet ) : Word . T 

; PROCEDURE Size ( VAR Set : tSet ) : Word . T 

; PROCEDURE Minimum ( VAR Set : tSet ) : Word . T 

; PROCEDURE Maximum ( VAR Set : tSet ) : Word . T 

; PROCEDURE Select ( VAR Set : tSet ) : Word . T 

; PROCEDURE Extract ( VAR Set : tSet ) : Word . T 

; PROCEDURE IsSubset ( Set1 , Set2 : tSet ) : BOOLEAN 

; PROCEDURE IsStrictSubset ( Set1 , Set2 : tSet ) : BOOLEAN 

; PROCEDURE IsEqual ( VAR Set1 , Set2 : tSet ) : BOOLEAN 

; PROCEDURE IsNotEqual ( Set1 , Set2 : tSet ) : BOOLEAN 

; PROCEDURE IsElement ( Elmt : Word . T ; VAR Set : tSet ) : BOOLEAN 

; PROCEDURE IsEmpty ( Set : tSet ) : BOOLEAN 

; PROCEDURE Forall ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

; PROCEDURE Exists ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

; PROCEDURE Exists1 ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

; PROCEDURE Assign ( VAR Set1 : tSet ; Set2 : tSet ) 

; PROCEDURE AssignElmt ( VAR Set : tSet ; Elmt : Word . T ) 

; PROCEDURE AssignEmpty ( VAR Set : tSet ) 

; PROCEDURE ForallDo ( Set : tSet ; Proc : ProcOftElement ) 

; PROCEDURE ReadSet ( f : tFile ; VAR Set : tSet ) 

; PROCEDURE WriteSet ( f : tFile ; Set : tSet ) 

; 
END SetsC 
. 

