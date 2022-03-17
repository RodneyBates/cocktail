
(* $Id: Strings.md,v 1.3 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: Strings.md,v $ 
 * Revision 1.3  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.2  89/06/06  10:06:58  grosch 
 * changed tStringIndex to SHORTCARD 
 * 
 * Revision 1.1  89/05/22  10:45:34  grosch 
 * added procedure IntToString 
 * 
 * Revision 1.0  88/10/04  11:47:20  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE INTERFACE Strings 

; IMPORT Word 

; FROM ReuseIO IMPORT tFile 

; CONST cMaxStrLength = 255 

; TYPE tStringIndex = [ 0 .. cMaxStrLength ] 

; TYPE tString 
    = RECORD 
        Chars : ARRAY tStringIndex OF CHAR 
      ; Length : tStringIndex 
      END (* RECORD *) 

; PROCEDURE Assign ( VAR s1 : tString ; READONLY s2 : tString ) 

   (* Zuweisung von Zeichenketten                       *) 

                        (* Assigns the string 's2' to the string 's1', 
                           i.e. s1 := s2 *) 

; PROCEDURE AssignEmpty ( VAR s : tString ) 

                        (* Returns an empty string 's'.                 *) 

; PROCEDURE Concatenate ( VAR s1 : tString ; READONLY s2 : tString ) 

                        (* Returns in parameter 's1' the concatenation  *) 
                        (* of the strings 's1' and 's2'.                *) 

; PROCEDURE Append ( VAR s : tString ; c : CHAR ) 

                        (* The character 'c' is concatenated at the end *) 
                        (* of the string 's'.                           *) 

; PROCEDURE Length ( READONLY s : tString ) : Word . T 

                        (* Returns the length of the string 's'.        *) 

; PROCEDURE IsEqual ( READONLY s1 , s2 : tString ) : BOOLEAN 

                        (* Returns TRUE if the strings 's1' and 's2'    *) 
                        (* are equal.                                   *) 

; PROCEDURE IsInOrder ( READONLY s1 , s2 : tString ) : BOOLEAN 

   (* Pruefung von 2 Zeichenketten auf lexikographische Ordnung *) 
                        (* Returns TRUE if the string 's1' is lexico-   *) 
                        (* graphically less or equal to the string 's2'.*) 

; PROCEDURE Exchange ( VAR s1 , s2 : tString ) 

                        (* Exchanges the strings 's1' and 's2'.         *) 

; PROCEDURE SubString 
    ( READONLY s1 : tString ; from , to : tStringIndex ; VAR s2 : tString ) 

                        (* Returns in 's2' the substring from 's1' com- *) 
                        (* prising the characters between 'from' and 'to'. *) 
                        (* PRE  1 <= from <= Length (s1)                *) 
                        (* PRE  1 <=  to  <= Length (s1)                *) 

; PROCEDURE Char ( READONLY s : tString ; i : tStringIndex ) : CHAR 

                        (* Returns the 'i'-th character of the string 's'. *) 
                        (* The characters are counted from 1 to Length (s). *) 
                        (* PRE  1 <= index <= Length (s)                *) 

; PROCEDURE ArrayToString ( READONLY a : ARRAY OF CHAR ; VAR s : tString ) 

                        (* An array 'a' of characters representing a    *) 
                        (* MODULA string is converted to a string 's'   *) 
                        (* of type tString.                             *) 

; PROCEDURE TextToString ( t : TEXT ; VAR s : tString ) 

                        (* TEXT 't' is converted to a string 's'        *) 
                        (* of type tString.                             *) 

; PROCEDURE StringToText ( READONLY s : tString ) : TEXT 

; PROCEDURE StringToArray ( READONLY s : tString ; VAR a : ARRAY OF CHAR ) 

                        (* A string 's' of type tString is converted to *) 
                        (* an array 'a' of characters representing a    *) 
                        (* MODULA string.                               *) 

; PROCEDURE StringToInt ( READONLY s : tString ) : INTEGER 

                        (* Returns the integer value represented by 's'. *) 

; PROCEDURE StringToNumber 
    ( READONLY s : tString ; Base : Word . T ) : Word . T 

                        (* Returns the integer value represented by 's' *) 
                        (* to the base 'Base'.                          *) 

; PROCEDURE StringToReal ( READONLY s : tString ) : REAL 

                        (* Returns the real value represented by 's'.   *) 

; PROCEDURE IntToString ( n : INTEGER ; VAR s : tString ) 

                        (* Returns in 's' the string representation of 'n'. *) 

; PROCEDURE ReadS ( f : tFile ; VAR s : tString ; FieldWidth : tStringIndex ) 

                        (* Read 'FieldWidth' characters as string 's'   *) 
                        (* from file 'f'.                               *) 

; PROCEDURE ReadL ( f : tFile ; VAR s : tString ) 

                        (* Read rest of line as string 's' from file    *) 
                        (* 'f'. Skip to next line.                      *) 

; PROCEDURE WriteS ( f : tFile ; READONLY s : tString ) 

                        (* Write string 's' to file 'f'.                *) 

; PROCEDURE WriteL ( f : tFile ; READONLY s : tString ) 

                        (* Write string 's' as complete line.           *) 

; 
END Strings 
. 

