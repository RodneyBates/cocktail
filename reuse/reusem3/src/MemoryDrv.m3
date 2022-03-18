
(* $Id: MemoryDrv.mi,v 1.2 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: MemoryDrv.mi,v $ 
 * Revision 1.2  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.1  90/03/02  17:35:01  grosch 
 * improved output behaviour using WriteFlush 
 * 
 * Revision 1.0  88/10/04  11:47:12  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE MemoryDrv EXPORTS Main 

; IMPORT Word 

; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT WORD 

; FROM Memory IMPORT Alloc , Free , MemoryUsed 

; FROM ReuseIO 
  IMPORT StdOutput , WriteS , WriteI , WriteLong , WriteN , WriteNl , CloseIO 

; VAR p1 , p2 , p3 , p4 : ADDRESS 
  ; i : Word . T 
  ; small , best , notbest , large : M2LONGINT 

; PROCEDURE AllocPrint ( n : M2LONGINT ) : ADDRESS 

  = VAR a : ADDRESS 

  ; BEGIN (* AllocPrint *) 
      a := Alloc ( n ) 
    ; WriteT ( StdOutput , "Alloc:  n = " ) 
    ; WriteLong ( StdOutput , n , 10 ) 
    ; WriteT ( StdOutput , ", ADR = " ) 
    ; WriteN ( StdOutput , LOOPHOLE ( a , INTEGER ) , 8 , 16 ) 
    ; WriteNl ( StdOutput ) 
    ; RETURN a 
    END AllocPrint 

; BEGIN (* MemoryDrv *) 
    FOR i := 0 TO 62 
    DO p1 := AllocPrint ( i ) 
    ; p2 := AllocPrint ( i ) 
    ; Free ( i , p1 ) 
    ; Free ( i , p2 ) 
    ; p3 := AllocPrint ( i ) 
    ; p4 := AllocPrint ( i ) 

    ; IF p3 # p2 
      THEN 
        WriteT ( StdOutput , "Alloc/Free small not inverse " ) 
      ; WriteI ( StdOutput , i , 10 ) 
      ; WriteNl ( StdOutput ) 
      END (* IF *) 

    ; IF p4 # p1 
      THEN 
        WriteT ( StdOutput , "Alloc/Free small not inverse " ) 
      ; WriteI ( StdOutput , i , 10 ) 
      ; WriteNl ( StdOutput ) 
      END (* IF *) 
    END (* FOR *) 

  ; small := 80 
  ; best := 96 
  ; notbest := 112 
  ; large := 128 

  ; LOOP 
      FOR i := 7 TO 24 (* 32 *) 
      DO WriteT ( StdOutput , "        i = " ) 
      ; WriteI ( StdOutput , i , 10 ) 
      ; WriteNl ( StdOutput ) 

      ; p1 := AllocPrint ( small ) 
      ; p2 := AllocPrint ( best ) 
      ; p3 := AllocPrint ( notbest ) 
      ; p4 := AllocPrint ( large ) 

      ; IF ( p1 = NIL ) OR ( p2 = NIL ) OR ( p3 = NIL ) OR ( p4 = NIL ) 
        THEN 
          EXIT 
        END (* IF *) 

      ; Free ( large , p4 ) 
      ; Free ( notbest , p3 ) 
      ; Free ( best , p2 ) 
      ; Free ( small , p1 ) 

      ; p1 := AllocPrint ( best ) 
      ; IF p1 # p2 
        THEN 
          WriteT ( StdOutput , "Alloc/Free large not inverse " ) 
        ; WriteI ( StdOutput , i , 10 ) 
        ; WriteNl ( StdOutput ) 
        END (* IF *) 

      ; p1 := AllocPrint ( best ) 
      ; IF p1 # p3 
        THEN 
          WriteT ( StdOutput , "Alloc/Free large not inverse " ) 
        ; WriteI ( StdOutput , i , 10 ) 
        ; WriteNl ( StdOutput ) 
        END (* IF *) 

      ; p1 := AllocPrint ( best ) 
      ; IF p1 # p4 
        THEN 
          WriteT ( StdOutput , "Alloc/Free large not inverse " ) 
        ; WriteI ( StdOutput , i , 10 ) 
        ; WriteNl ( StdOutput ) 
        END (* IF *) 

      ; INC ( small , small ) 
      ; INC ( best , best ) 
      ; INC ( notbest , notbest ) 
      ; INC ( large , large ) 
      END (* FOR *) 
    END (* LOOP *) 
  ; WriteNl ( StdOutput ) 
  ; WriteT ( StdOutput , "Memory used: " ) 
  ; WriteI ( StdOutput , MemoryUsed , 10 ) 
  ; WriteNl ( StdOutput ) 
  ; CloseIO ( ) 
  END MemoryDrv 
. 

