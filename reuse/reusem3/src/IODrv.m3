
(* $Id: IODrv.mi,v 1.2 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: IODrv.mi,v $ 
 * Revision 1.2  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.1  90/03/02  17:35:00  grosch 
 * improved output behaviour using WriteFlush 
 * 
 * Revision 1.0  88/10/04  11:46:59  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE IODrv EXPORTS Main                                (* buffered IO          *) 



; FROM ReuseIO 
  IMPORT tFile , StdInput , StdOutput , StdError , ReadOpen , ReadClose 
  , Read 
  , ReadC , ReadI , ReadR , ReadB , ReadShort , ReadLong , ReadCard , ReadNl 
  , EndOfLine 
  , EndOfFile , WriteOpen , WriteClose , WriteFlush , Write , WriteC , WriteI 
  , WriteR 
  , WriteB , WriteShort , WriteLong , WriteCard , WriteNl , ReadS , WriteS 

; VAR f , g : tFile 
  ; i , j : INTEGER 
  ; c : CHAR 
  ; b : ARRAY [ 1 .. 200 ] OF CHAR 
  ; r : REAL 

; BEGIN (* IODrv *) 
    f := ReadOpen 
           ( ARRAY [ 0 .. 8 ] OF CHAR 
               { 'M' , 'a' , 'k' , 'e' , 'f' , 'i' , 'l' , 'e' , '\000' } 
           ) 
  ; g := WriteOpen ( 't' ) 

  ; FOR i := 1 TO 200 
    DO c := ReadC ( f ) 
    ; WriteC ( StdOutput , c ) 
    ; WriteC ( g , c ) 
    END (* FOR *) 

  ; WHILE NOT EndOfFile ( f ) 
    DO i := Read ( f , ADR ( b [ FIRST ( b ) ] ) , 200 ) 
    ; j := Write ( StdOutput , ADR ( b [ FIRST ( b ) ] ) , i ) 
    ; j := Write ( g , ADR ( b [ FIRST ( b ) ] ) , i ) 
    END (* WHILE *) 

  ; ReadClose ( f ) 
  ; WriteClose ( g ) 
  ; WriteNl ( StdOutput ) 

  ; WriteS 
      ( StdOutput 
      , ARRAY [ 0 .. 28 ] OF CHAR 
          { 'e' , 'n' , 't' , 'e' , 'r' , ' ' , 'i' , 'n' , 't' , 'e' , 'g' 
          , 'e' 
          , 'r' , 's' , ',' , ' ' , '9' , '9' , ' ' , 'w' , 'i' , 'l' , 'l' 
          , ' ' , 's' , 't' , 'o' , 'p' , '\000' 
          } 
      ) 
  ; WriteNl ( StdOutput ) 
  ; REPEAT 
      WriteFlush ( StdOutput ) 
    ; i := ReadI ( StdInput ) 
    ; WriteI ( StdOutput , i , 10 ) 
    ; WriteShort ( StdOutput , i , 10 ) 
    ; WriteLong ( StdOutput , i , 10 ) 
    ; WriteCard ( StdOutput , i , 10 ) 
    ; c := ReadC ( StdInput ) 
    ; WriteC ( StdOutput , ' ' ) 
    ; WriteC ( StdOutput , c ) 
    ; WriteNl ( StdOutput ) 
    UNTIL i = 99 

  ; WriteS 
      ( StdOutput 
      , ARRAY [ 0 .. 25 ] OF CHAR 
          { 'e' , 'n' , 't' , 'e' , 'r' , ' ' , 'r' , 'e' , 'a' , 'l' , 's' 
          , ',' 
          , ' ' , '9' , '9' , ' ' , 'w' , 'i' , 'l' , 'l' , ' ' , 's' , 't' 
          , 'o' , 'p' , '\000' 
          } 
      ) 
  ; WriteNl ( StdOutput ) 
  ; REPEAT 
      WriteFlush ( StdOutput ) 
    ; r := ReadR ( StdInput ) 
    ; WriteR ( StdOutput , r , 2 , 12 , 3 ) 
    ; WriteC ( StdOutput , ',' ) 
    ; WriteR ( StdOutput , r , 2 , 3 , 2 ) 
    ; WriteC ( StdOutput , ',' ) 
    ; WriteR ( StdOutput , r , 4 , 3 , 1 ) 
    ; WriteC ( StdOutput , ',' ) 
    ; WriteR ( StdOutput , r , 8 , 3 , 0 ) 
    ; WriteC ( StdOutput , ',' ) 
    ; WriteR ( StdOutput , r , 8 , 1 , 0 ) 
    ; WriteC ( StdOutput , ',' ) 
    ; WriteR ( StdOutput , r , 8 , 0 , 0 ) 
    ; WriteC ( StdOutput , ',' ) 
    ; WriteNl ( StdOutput ) 
    UNTIL ( 98.9 <= r ) AND ( r <= 99.1 ) 

  ; WriteClose ( StdOutput ) 
  END IODrv 
. 

