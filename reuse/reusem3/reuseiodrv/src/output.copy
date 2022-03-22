
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

UNSAFE MODULE ReuseIODrv EXPORTS Main                   (* buffered IO       *) 



; FROM ReuseIO 
  IMPORT tFile , StdInput , StdOutput , StdError , ReadOpenT , ReadClose 
  , Read 
  , ReadC , ReadI , ReadR , ReadB , ReadShort , ReadLong , ReadCard , ReadNl 
  , EndOfLine 
  , EndOfFile , WriteOpenT , WriteClose , WriteFlush , WriteT , WriteC , WriteI 
  , WriteR , Write 
  , WriteB , WriteShort , WriteLong , WriteCard , WriteNl , ReadS

; VAR f , g : tFile 
  ; i , j : INTEGER 
  ; c : CHAR 
  ; b : ARRAY [ 1 .. 200 ] OF CHAR 
  ; r : REAL 

; BEGIN (* ReuseIODrv *) 
    f := ReadOpenT ( "../src/ReuseIODrv.m3" ) 
  ; g := WriteOpenT ( "output.copy" ) 

  ; FOR i := 1 TO 200 
    DO c := ReadC ( f ) 
    ; WriteC ( StdOutput , c ) 
    ; WriteC ( g , c )
    ; WriteFlush ( StdOutput ) 
    END (* FOR *) 

  ; WHILE NOT EndOfFile ( f ) 
    DO i := Read ( f , ADR ( b [ FIRST ( b ) ] ) , 200 ) 
    ; j := Write ( StdOutput , ADR ( b [ FIRST ( b ) ] ) , i ) 
    ; j := Write ( g , ADR ( b [ FIRST ( b ) ] ) , i ) 
    END (* WHILE *) 

  ; ReadClose ( f ) 
  ; WriteClose ( g ) 
  ; WriteNl ( StdOutput ) 

  ; WriteT ( StdOutput , "Enter integers, 99 will stop" ) 
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

  ; WriteT ( StdOutput , "Enter reals,  99 will stop" ) 
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
  END ReuseIODrv 
. 

