
(* $Id: Layout.mi,v 1.2 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: Layout.mi,v $ 
 * Revision 1.2  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.1  89/01/24  19:04:59  grosch 
 * added procedure SkipSpaces 
 * 
 * Revision 1.0  88/10/04  11:47:03  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE Layout 

; FROM ReuseIO IMPORT tFile , WriteC , WriteS , WriteI , ReadC , UnRead 

; PROCEDURE WriteChar ( f : tFile ; Ch : CHAR ) 

  = BEGIN (* WriteChar *) 
      IF ( '!' <= Ch ) AND ( Ch <= '~' ) 
      THEN 
        WriteC ( f , '\'' ) 
      ; WriteC ( f , Ch ) 
      ; WriteC ( f , '\'' ) 
      ELSIF Ch = '\000' 
      THEN 
        WriteS ( f , ARRAY [ 0 .. 3 ] OF CHAR { 'e' , 'p' , 's' , '\000' } ) 
      ELSE 
        WriteI ( f , ORD ( Ch ) , 2 ) 
      ; WriteC ( f , 'C' ) 
      END (* IF *) 
    END WriteChar 

; PROCEDURE WriteSpace ( f : tFile ) 

  = BEGIN (* WriteSpace *) 
      WriteC ( f , ' ' ) 
    END WriteSpace 

; PROCEDURE WriteSpaces ( f : tFile ; Count : INTEGER ) 

  = BEGIN (* WriteSpaces *) 
      FOR i := 1 TO Count DO WriteC ( f , ' ' ) END (* FOR *) 
    END WriteSpaces 

; PROCEDURE ReadSpace ( f : tFile ) 

  = VAR Ch : CHAR 

  ; BEGIN (* ReadSpace *) 
      Ch := ReadC ( f ) 
    END ReadSpace 

; PROCEDURE ReadSpaces ( f : tFile ; Count : INTEGER ) 

  = VAR Ch : CHAR 

  ; BEGIN (* ReadSpaces *) 
      FOR i := 1 TO Count DO Ch := ReadC ( f ) END (* FOR *) 
    END ReadSpaces 

; PROCEDURE SkipSpaces ( f : tFile ) 

  = BEGIN (* SkipSpaces *) 
      REPEAT UNTIL ReadC ( f ) # ' ' 
    ; UnRead ( f ) 
    END SkipSpaces 

; BEGIN (* Layout *) 
  END Layout 
. 

