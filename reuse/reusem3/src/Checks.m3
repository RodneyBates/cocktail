
(* $Id: Checks.mi,v 1.2 1992/01/30 13:23:29 grosch rel $ *) 

(* $Log: Checks.mi,v $ 
 * Revision 1.2  1992/01/30  13:23:29  grosch 
 * redesign of interface to operating system 
 * 
 * Revision 1.1  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.0  88/10/04  11:46:50  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE Checks 

; FROM ReuseIO IMPORT StdError , WriteS , WriteT , WriteI , WriteNl 

; FROM System IMPORT ErrNum , Exit , Flush

; VAR ExitStatus := 9999 

; PROCEDURE ErrorCheckS ( READONLY s : ARRAY OF CHAR ; n : INTEGER ) 

  = BEGIN (* ErrorCheckS *) 
      IF n < 0 
      THEN 
        WriteS ( StdError , s ) 
      ; WriteT ( StdError , " : \000" ) 
      ; WriteI ( StdError , n , 2 ) 
      ; WriteT ( StdError , ", errno     = \000" ) 
      ; WriteI ( StdError , ErrNum ( ) , 2 ) 
      ; WriteNl ( StdError )
      ; Flush ( StdError )
      ; Exit ( ExitStatus ) 
      END (* IF *) 
    END ErrorCheckS 

; PROCEDURE ErrorCheckT ( s : TEXT ; n : INTEGER ) 

  = BEGIN (* ErrorCheckT *) 
      IF n < 0 
      THEN 
        WriteT ( StdError , s ) 
      ; WriteT ( StdError , " : \000" ) 
      ; WriteI ( StdError , n , 2 ) 
      ; WriteT ( StdError , ", errno     = \000" ) 
      ; WriteI ( StdError , ErrNum ( ) , 2 ) 
      ; WriteNl ( StdError ) 
      ; Flush ( StdError )
      ; Exit ( ExitStatus ) 
      END (* IF *) 
    END ErrorCheckT 

; BEGIN (* Checks *) 
  END Checks 
. 

