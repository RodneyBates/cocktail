(* $Id: Parser.md,v 2.1 1992/08/07 15:28:42 grosch rel $ *) 

UNSAFE INTERFACE Parser 



; IMPORT Word 

; FROM SYSTEM IMPORT SHORTCARD 

; VAR ParsTabName : TEXT 

; PROCEDURE TokenName ( Token : SHORTCARD ; VAR Name : ARRAY OF CHAR ) 

; PROCEDURE Parser ( ) : Word . T 

; PROCEDURE CloseParser ( ) 

; 
END Parser 
. 

