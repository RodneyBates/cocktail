
(* $Id: Texts.mi,v 1.2 1992/08/07 14:43:04 grosch rel $ *) 

(* $Log: Texts.mi,v $ 
 * Revision 1.2  1992/08/07  14:43:04  grosch 
 * added procedure IsEmpty 
 * 
 * Revision 1.1  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.0  88/10/04  11:47:37  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, 31.8.1988 *) 

UNSAFE MODULE Texts 


; FROM ReuseIO IMPORT tFile 

; FROM Lists IMPORT MakeList , Head , Tail 

; FROM Strings IMPORT tString , WriteL 

; FROM StringMem IMPORT tStringRef , PutString , GetString 

; IMPORT Lists 

(*EXPORTED*) 

; PROCEDURE MakeText ( VAR Text : tText ) 

  = BEGIN (* MakeText *) 
      MakeList ( Text ) 
    END MakeText 

(*EXPORTED*) 

; PROCEDURE Append ( VAR Text : tText ; VAR String : tString ) 

  = BEGIN (* Append *) 
      Lists . Append ( Text , LOOPHOLE ( PutString ( String ) , ADDRESS ) ) 
    END Append 

(*EXPORTED*) 

; PROCEDURE Insert ( VAR Text : tText ; VAR String : tString ) 

  = BEGIN (* Insert *) 
      Lists . Insert ( Text , LOOPHOLE ( PutString ( String ) , ADDRESS ) ) 
    END Insert 

(*EXPORTED*) 

; PROCEDURE IsEmpty ( VAR Text : tText ) : BOOLEAN 

  = BEGIN (* IsEmpty *) 
      RETURN Lists . IsEmpty ( Text ) 
    END IsEmpty 

(*EXPORTED*) 

; PROCEDURE WriteText ( f : tFile ; Text : tText ) 

  = VAR String : tString 

  ; BEGIN (* WriteText *) 
      WHILE NOT Lists . IsEmpty ( Text ) 
      DO GetString ( LOOPHOLE ( Head ( Text ) , tStringRef ) , String ) 
      ; WriteL ( f , String ) 
      ; Tail ( Text ) 
      END (* WHILE *) 
    END WriteText 

; BEGIN (* Texts *) 
  END Texts 
. 

