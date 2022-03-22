
(* $Id: SysIODrv.mi,v 1.2 1992/01/30 13:23:29 grosch rel $ *) 

(* $Log: SysIODrv.mi,v $ 
 * Revision 1.2  1992/01/30  13:23:29  grosch 
 * redesign of interface to operating system 
 * 
 * Revision 1.1  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.0  88/10/04  11:47:28  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE SysIODrv EXPORTS Main 

; FROM System IMPORT tFile , OpenInputT , OpenOutputT , Read , Write , Close 

; FROM Checks IMPORT ErrorCheckT 

; CONST BuffSize = 2000 

; VAR b : ARRAY [ 0 .. BuffSize - 1 ] OF CHAR 
  ; f : tFile 
  ; n , m : INTEGER 

; BEGIN (* SysIODrv *) 
    TRY 
      f := OpenInputT ( "../src/SysIODrv.m3" ) 
    EXCEPT 
    ELSE 
    END (* EXCEPT *) 
  ; ErrorCheckT ( "OpenInput" , f ) 
  ; n := Read ( f , ADR ( b [ FIRST ( b ) ] ) , BuffSize ) 
  ; ErrorCheckT ( "Read" , n ) 
  ; Close ( f ) 

  ; TRY 
      f := OpenOutputT ( "SysIODrv.m3.copy" ) 
    EXCEPT 
    ELSE 
    END (* EXCEPT *) 
  ; ErrorCheckT ( "OpenOutput" , f ) 
  ; m := Write ( f , ADR ( b [ FIRST ( b ) ] ) , MIN ( n , BuffSize ) ) 
  ; ErrorCheckT ( "Write" , m ) 
  ; Close ( f ) 
  END SysIODrv 
. 

