
(* $Id: Lists.mi,v 1.2 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: Lists.mi,v $ 
 * Revision 1.2  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.1  88/10/20  17:20:44  grosch 
 * fixed bug: initialization in Length added 
 * 
 * Revision 1.0  88/10/04  11:47:05  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE Lists 


; IMPORT Word 

; FROM Memory IMPORT Alloc 

; FROM ReuseIO IMPORT tFile 

; PROCEDURE MakeList ( VAR List : tList ) 

  = BEGIN (* MakeList *) 
      List . FirstElmt := NIL 
    ; List . LastElmt := NIL 
    END MakeList 

; PROCEDURE Insert ( VAR List : tList ; Elmt : tElmt ) 

  = VAR ActElmt : tListElmtPtr 

  ; BEGIN (* Insert *) 
      ActElmt := Alloc ( BYTESIZE ( tListElmt ) ) 
    ; ActElmt ^ . Succ := NIL 
    ; ActElmt ^ . Elmt := Elmt 
    ; IF List . FirstElmt = NIL 
      THEN 
        List . LastElmt := ActElmt 
      ELSE 
        ActElmt ^ . Succ := List . FirstElmt 
      END (* IF *) 
    ; List . FirstElmt := ActElmt 
    END Insert 

; PROCEDURE Append ( VAR List : tList ; Elmt : tElmt ) 

  = VAR ActElmt : tListElmtPtr 

  ; BEGIN (* Append *) 
      ActElmt := Alloc ( BYTESIZE ( tListElmt ) ) 
    ; ActElmt ^ . Succ := NIL 
    ; ActElmt ^ . Elmt := Elmt 
    ; IF List . FirstElmt = NIL 
      THEN 
        List . FirstElmt := ActElmt 
      ELSE 
        List . LastElmt ^ . Succ := ActElmt 
      END (* IF *) 
    ; List . LastElmt := ActElmt 
    END Append 

; PROCEDURE Head ( List : tList ) : tElmt 

  = BEGIN (* Head *) 
      RETURN List . FirstElmt ^ . Elmt 
    END Head 

; PROCEDURE Tail ( VAR List : tList ) 

  = BEGIN (* Tail *) 
      List . FirstElmt := List . FirstElmt ^ . Succ 
    END Tail 

; PROCEDURE Last ( List : tList ) : tElmt 

  = BEGIN (* Last *) 
      RETURN List . LastElmt ^ . Elmt 
    END Last 

; PROCEDURE Front ( VAR List : tList ) 

(* Not implemented. *) 

  = BEGIN (* Front *) 

     <* ASSERT FALSE *> 

      EVAL List 
    END Front 

; PROCEDURE IsEmpty ( List : tList ) : BOOLEAN 

  = BEGIN (* IsEmpty *) 
      RETURN List . FirstElmt = NIL 
    END IsEmpty 

; PROCEDURE Length ( List : tList ) : Word . T 

  = VAR n : Word . T 

  ; BEGIN (* Length *) 
      n := 0 
    ; WHILE List . FirstElmt # NIL 
      DO INC ( n ) 
      ; List . FirstElmt := List . FirstElmt ^ . Succ 
      END (* WHILE *) 
    ; RETURN n 
    END Length 

; PROCEDURE WriteList 
    ( f : tFile ; List : tList ; Proc : tProcOfFileAddress ) 

  = BEGIN (* WriteList *) 
      WHILE NOT IsEmpty ( List ) 
      DO Proc ( f , Head ( List ) ) 
      ; Tail ( List ) 
      END (* WHILE *) 
    END WriteList 

; BEGIN (* Lists *) 
  END Lists 
. 

