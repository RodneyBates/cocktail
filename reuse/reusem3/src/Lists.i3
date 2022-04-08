
(* $Id: Lists.md,v 1.1 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: Lists.md,v $ 
 * Revision 1.1  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.0  88/10/04  11:47:03  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

INTERFACE Lists 


; IMPORT Word 

; FROM ReuseIO IMPORT tFile 

; TYPE tElmt = ADDRESS 
  ; tListElmtPtr = UNTRACED BRANDED REF tListElmt 

  ; tListElmt = RECORD Succ : tListElmtPtr ; Elmt : tElmt END (* RECORD *) 

  ; tList = RECORD FirstElmt , LastElmt : tListElmtPtr END (* RECORD *) 

  ; tProcOfFileAddress = PROCEDURE ( p0 : tFile ; p1 : tElmt ) 

; PROCEDURE MakeList ( VAR List : tList ) 

; PROCEDURE Insert ( VAR List : tList ; Elmt : tElmt ) 

; PROCEDURE Append ( VAR List : tList ; Elmt : tElmt ) 

; PROCEDURE Head ( List : tList ) : tElmt 

; PROCEDURE Tail ( VAR List : tList ) 

; PROCEDURE Last ( List : tList ) : tElmt 

; PROCEDURE Front ( VAR List : tList )                  (* not implemented *) 

; PROCEDURE IsEmpty ( List : tList ) : BOOLEAN 

; PROCEDURE Length ( List : tList ) : Word . T 

; PROCEDURE WriteList 
    ( f : tFile ; List : tList ; Proc : tProcOfFileAddress ) 

; 
END Lists 
. 

