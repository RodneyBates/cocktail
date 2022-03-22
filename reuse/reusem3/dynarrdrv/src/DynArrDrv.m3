
(* $Id: DynArrDrv.mi,v 1.1 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: DynArrDrv.mi,v $ 
 * Revision 1.1  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.0  88/10/04  11:46:51  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE DynArrDrv EXPORTS Main 

; FROM SYSTEM IMPORT M2LONGINT 
; IMPORT Word 

; FROM DynArray IMPORT MakeArray , ExtendArray 

; FROM ReuseIO 
  IMPORT StdOutput , WriteC , WriteI , WriteNl , WriteT , WriteLong , CloseIO 


; VAR i : M2LONGINT 
  ; j : Word . T 

; TYPE t = ARRAY [ 1 .. 100000 ] OF M2LONGINT 

(* necessary to force index arithmetic to be done with long integers *) 

; VAR p : UNTRACED BRANDED REF t
; VAR padr : ADDRESS 
; VAR s : M2LONGINT 

; BEGIN (* DynArrDrv *) 
    s := 10 

  ; MakeArray ( LOOPHOLE ( p , ADDRESS ) , s , BYTESIZE ( M2LONGINT ) ) 
  ; FOR i := 1 TO s DO p ^ [ i ] := i END (* FOR *) 

  ; FOR j := 1 TO 13 
    DO ExtendArray ( LOOPHOLE ( p , ADDRESS ) , s , BYTESIZE ( M2LONGINT ) ) 

    ; IF p = NIL 
      THEN 
        WriteT ( StdOutput , "Extend Error" ) 
      ; WriteNl ( StdOutput ) 
      END (* IF *) 

    ; FOR i := ( s DIV 2 ) + 1 TO s DO p ^ [ i ] := i END (* FOR *) 

    ; FOR i := 1 TO s 
      DO IF p ^ [ i ] # i 
         THEN 
           WriteT ( StdOutput , "Error j, i, p^[i] =" ) 
         ; WriteI ( StdOutput , j , 5 ) 
         ; WriteLong ( StdOutput , i , 5 ) 
         ; WriteLong ( StdOutput , p ^ [ i ] , 10 ) 
         ; WriteNl ( StdOutput ) 
         END (* IF *) 
      END (* FOR *) 

    ; WriteT ( StdOutput , "j, size = " ) 
    ; WriteI ( StdOutput , j , 5 ) 
    ; WriteLong ( StdOutput , s , 10 ) 
    ; WriteT ( StdOutput , " ok" ) 
    ; WriteNl ( StdOutput ) 
    END (* FOR *) 
  ; CloseIO ( ) 
  END DynArrDrv 
. 

