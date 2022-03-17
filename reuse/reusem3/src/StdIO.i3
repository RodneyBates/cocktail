
(* $Id: StdIO.md,v 1.3 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: StdIO.md,v $ 
 * Revision 1.3  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.2  89/07/14  16:27:20  grosch 
 * made WriteN work for numbers with MSBit set 
 * 
 * Revision 1.1  89/01/24  19:04:40  grosch 
 * added procedure UnRead 
 * 
 * Revision 1.0  88/10/04  11:47:15  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE INTERFACE StdIO                          (* buffered standard IO *) 

; FROM SYSTEM IMPORT M2LONGINT , M2LONGCARD 


; FROM SYSTEM IMPORT SHORTINT 
; IMPORT Word 

; PROCEDURE ReadClose ( )                       (* close input file     *) 

; PROCEDURE Read ( Buffer : ADDRESS ; Size : Word . T ) : INTEGER 

                                                (* binary               *) 

; PROCEDURE ReadC ( ) : CHAR                    (* character            *) 

; PROCEDURE ReadI ( ) : INTEGER                 (* integer  number      *) 

; PROCEDURE ReadR ( ) : REAL                    (* real     number      *) 

; PROCEDURE ReadB ( ) : BOOLEAN                 (* boolean              *) 

; PROCEDURE ReadN ( Base : INTEGER ) : INTEGER 

                                                (* number of base 'Base'*) 

; PROCEDURE ReadS ( VAR s : ARRAY OF CHAR ) (* string               *) 

; PROCEDURE ReadShort ( ) : SHORTINT            (* shortint number ?    *) 

; PROCEDURE ReadLong ( ) : M2LONGINT            (* longint  number ?    *) 

; PROCEDURE ReadCard ( ) : Word . T             (* cardinal number ?    *) 

; PROCEDURE ReadNl ( )                          (* new line             *) 

; PROCEDURE UnRead ( )                          (* backspace 1 char.    *) 

; PROCEDURE EndOfLine ( ) : BOOLEAN             (* end of line ?        *) 

; PROCEDURE EndOfFile ( ) : BOOLEAN             (* end of file ?        *) 


; PROCEDURE WriteClose ( )                      (* close output file    *) 

; PROCEDURE WriteFlush ( )                      (* flush output buffer  *) 

; PROCEDURE Write ( Buffer : ADDRESS ; Size : Word . T ) : INTEGER 

                                                (* binary               *) 

; PROCEDURE WriteC ( c : CHAR )                 (* character            *) 

; PROCEDURE WriteI ( n : INTEGER ; FieldWidth : Word . T ) 

                                                (* integer  number      *) 

; PROCEDURE WriteR ( n : REAL ; Before , After , Exp : Word . T ) 

                                                (* real     number      *) 

; PROCEDURE WriteB ( b : BOOLEAN )              (* boolean              *) 

; PROCEDURE WriteN ( n : M2LONGCARD ; FieldWidth , Base : Word . T ) 

                                                (* number of base 'Base'*) 

; PROCEDURE WriteS ( READONLY s : ARRAY OF CHAR )       (* string               *) 

; PROCEDURE WriteT ( s : TEXT )                 (* M3 TEXT              *) 

; PROCEDURE WriteShort ( n : SHORTINT ; FieldWidth : Word . T ) 

                                                (* shortint number ?    *) 

; PROCEDURE WriteLong ( n : M2LONGINT ; FieldWidth : Word . T ) 

                                                (* longint  number ?    *) 

; PROCEDURE WriteCard ( n : Word . T ; FieldWidth : Word . T ) 

                                                (* cardinal number ?    *) 

; PROCEDURE WriteNl ( )                         (* new line             *) 


; PROCEDURE CloseIO ( )                         (* close all files      *) 

; 
END StdIO 
. 

