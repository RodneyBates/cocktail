
(* $Id: Sort.md,v 1.0 1992/08/07 14:42:01 grosch rel $ *) 

(* $Log: Sort.md,v $ 
# Revision 1.0  1992/08/07  14:42:01  grosch 
# Initial revision 
# 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Juli 1992 *) 

UNSAFE INTERFACE Sort 

; TYPE tProcIntIntBool = PROCEDURE ( p0 : INTEGER ; p1 : INTEGER ) : BOOLEAN 
; TYPE tProcIntInt = PROCEDURE ( p0 : INTEGER ; p1 : INTEGER ) 

; PROCEDURE Sort 
    ( Lwb , Upb : INTEGER ; IsLess : tProcIntIntBool ; Swap : tProcIntInt ) 

        (* Sort data from the indices 'Lwb' to 'Upb' using quicksort.   *) 
        (* The procedures 'IsLess' and 'Swap' are used to compare and   *) 
        (* exchange two data elements.                                  *) 

; 
END Sort 
. 

