(* $Id: Classes.mi,v 3.2 1991/11/21 14:41:19 grosch rel $ *) 

(* Rodney M. Bates 
    Apr. 1999 Minor changes to compile, after changes to Sets 
    Nov. 1999 Remove unused import of Layout . WriteChar 
*) 

(* $Log: Classes.mi,v $ 
Revision 3.2  1991/11/21  14:41:19  grosch 
fixed bug: interference of right context between constant and non-constant RE 
new version of RCS on SPARC 
 
Revision 3.1  91/04/08  15:50:12  grosch 
release memory after use in Classes and Tree0 
 
Revision 3.0  91/04/04  18:26:37  grosch 
Initial revision 
 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, March 1991 *) 

UNSAFE MODULE Classes 

; IMPORT Word 

; FROM DynArray IMPORT MakeArray , ExtendArray , ReleaseArray 

; FROM Strings IMPORT tString , Char , Length 

; FROM StringMem IMPORT GetString 

; IMPORT IntSets

; IMPORT Sets 

(*
; FROM Sets 
  IMPORT tSet , tElement , MakeSet , Assign , Include , IsEqual , ForallDo 
  , Intersection 
  , Union , Difference , Complement , ReleaseSet , IsEmpty , IsSubset 
*)
; FROM Tree0 IMPORT tTree0 , Tree0Root , TraverseTree0TD , Ch , Set , String 

; FROM Dfa IMPORT FirstCh , LastCh , OldLastCh , EobCh 

; PROCEDURE IsInSetMem ( Set : Sets . tSet ) : INTEGER 

  = VAR LIntSet : IntSets . T

  ; BEGIN (* IsInSetMem *)
      LIntSet := Sets . IntSet ( Set ) 
    ; FOR i := 1 TO SetCount 
      DO IF IntSets . Equal ( LIntSet , SetMemPtr ^ [ i ] . Set ) 
         THEN 
           RETURN i 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN 0 
    END IsInSetMem 

; PROCEDURE IsInIntSetMem ( Set : IntSets . T ) : INTEGER 

  = BEGIN (* IsInSetMem *) 
      FOR i := 1 TO SetCount 
      DO IF IntSets . Equal ( Set , SetMemPtr ^ [ i ] . Set ) 
         THEN 
           RETURN i 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN 0 
    END IsInIntSetMem 

; PROCEDURE CollectSets ( t : tTree0 ) 

  = VAR string : tString
  ; VAR SetIntSet : IntSets . T 

  ; BEGIN (* CollectSets *) 
      CASE t ^ . Kind 
      OF Ch 
      => CharSet := IntSets . Include ( CharSet , ORD ( t ^ . Ch . Ch ) ) 

      | Set 
      => SetIntSet := Sets . IntSet ( t ^ . Set . Set ) 
      ;  IF IsInIntSetMem ( SetIntSet) = 0 
         THEN 
           INC ( SetCount ) 
         ; IF SetCount = SetMemSize 
           THEN 
             ExtendArray 
               ( LOOPHOLE ( SetMemPtr , ADDRESS ) 
               , SetMemSize 
               , BYTESIZE ( ClassInfo ) 
               ) 
           END (* IF *)
         ; SetMemPtr ^ [ SetCount ] . Set := SetIntSet 
         ; Unused := IntSets . Union ( Unused , SetIntSet)
(*       ; MakeSet ( SetMemPtr ^ [ SetCount ] . Set , ORD ( LastCh ) ) 
         ; Assign ( SetMemPtr ^ [ SetCount ] . Set , SetIntSet) 
         ; Union ( Unused , t ^ . Set . Set )
*)
         END (* IF *) 

      | String 
      => GetString ( t ^ . String . String , string ) 
      ; FOR i := Length ( string ) TO 1 BY - 1 
        DO CharSet
             := IntSets . Include ( CharSet , ORD ( Char ( string , i ) ) ) 
        END (* FOR *) 
      ELSE 
      END (* CASE *) 
    END CollectSets 

; VAR Class : CHAR 

; PROCEDURE CharToClass0 ( Elem : IntSets . ValidElemT ) 

  = BEGIN (* CharToClass0 *) 
      ToClass [ VAL ( Elem , CHAR ) ] := Class 
    END CharToClass0 

; PROCEDURE CharToClass ( Elem : IntSets . ValidElemT ) 

  = VAR Ch : IntSets . ValidElemT 
  ; BEGIN (* CharToClass *)
      Ch := ORD ( Elem ) 
    ; INC ( LastCh ) 
    ; ToClass [ VAL ( Elem , CHAR ) ] := LastCh 
    ; ToChar [ LastCh ] := VAL ( Elem , CHAR ) 
    END CharToClass 

; PROCEDURE ComputeClasses ( Blocking : BOOLEAN ) 

  = VAR Set : IntSets . T 

  ; BEGIN (* ComputeClasses *) 
      OldLastCh := LastCh 
    ; CharSet := IntSets . Empty ( ) 
    ; Unused := IntSets . Empty ( ) 

    ; IF Blocking 
      THEN 
        TraverseTree0TD ( Tree0Root , CollectSets ) 
      ; CharSet := IntSets . Include ( CharSet , ORD ( EobCh ) ) 
      ; Unused := IntSets . Union ( Unused , CharSet ) 
      ; Unused := IntSets . Complement ( Unused , 0 , ORD ( LastCh ) ) 
      ELSE 
        CharSet := IntSets . Include ( CharSet , ORD ( FirstCh ) ) 
      ; CharSet := IntSets . Complement ( CharSet , 0 , ORD ( FirstCh ) ) 
      END (* IF *) 

    ; ClassCount := '\000'
    ; ClassMemPtr ^ [ '\000' ]
        := IntSets . Complement
             ( IntSets . Union ( CharSet , Unused ) , 0 , ORD ( LastCh ) )
(*  ; MakeSet ( ClassMemPtr ^ [ '\000' ] , ORD ( LastCh ) ) 
    ; Assign ( ClassMemPtr ^ [ '\000' ] , CharSet ) 
    ; Union ( ClassMemPtr ^ [ '\000' ] , Unused ) 
    ; Complement ( ClassMemPtr ^ [ '\000' ] )
*)

    ; FOR i := 1 TO SetCount 
      DO FOR j := '\000' TO ClassCount 
         DO
           Set
             := IntSets . Intersection
                 ( IntSets . Difference ( SetMemPtr ^ [ i ] . Set , CharSet )
                 , ClassMemPtr ^ [ j ]
                 ) 
(*         Assign ( Set , SetMemPtr ^ [ i ] . Set ) 
         ; Difference ( Set , CharSet ) 
         ; Intersection ( Set , ClassMemPtr ^ [ j ] )
*)
         ; IF NOT IntSets . IsEmpty ( Set )  
              AND NOT IntSets . Equal ( Set , ClassMemPtr ^ [ j ] )  
           THEN 
             INC ( ClassCount ) 
           ; IF ORD ( ClassCount ) = LOOPHOLE ( ClassMemSize , Word . T ) 
             THEN 
               ExtendArray 
                 ( LOOPHOLE ( ClassMemPtr , ADDRESS ) 
                 , ClassMemSize 
                 , BYTESIZE ( IntSets . T ) 
                 ) 
             END (* IF *)
           ; ClassMemPtr ^ [ ClassCount ] := Set 
           ; WITH WClassJ = ClassMemPtr ^ [ j ]
             DO WClassJ := IntSets . Difference ( WClassJ , Set ) 
             END (* WITH *)
(*         ; MakeSet ( ClassMemPtr ^ [ ClassCount ] , ORD ( LastCh ) ) 
           ; Assign ( ClassMemPtr ^ [ ClassCount ] , Set ) 
           ; Difference ( ClassMemPtr ^ [ j ] , Set )
*)
           END (* IF *) 
         END (* FOR *) 
      END (* FOR *) 
    ; Set := NIL  

    ; FOR i := 1 TO SetCount 
      DO
        SetMemPtr ^ [ i ] . Classes := IntSets . Empty ( ) 
      ; FOR j := '\000' TO ClassCount 
        DO IF IntSets . IsSubset
                ( ClassMemPtr ^ [ j ] , SetMemPtr ^ [ i ] . Set ) 
           THEN
             WITH WClasses = SetMemPtr ^ [ i ] . Classes
             DO WClasses := IntSets . Include ( WClasses , ORD ( j ) )
             END (* WITH *) 
           END (* IF *) 
        END (* FOR *) 
(*      MakeSet ( SetMemPtr ^ [ i ] . Classes , ORD ( ClassCount ) ) 
      ; FOR j := '\000' TO ClassCount 
        DO IF IntSets . IsSubset
                ( ClassMemPtr ^ [ j ] , SetMemPtr ^ [ i ] . Set ) 
           THEN 
             Include ( SetMemPtr ^ [ i ] . Classes , ORD ( j ) ) 
           END (* IF *) 
        END (* FOR *) 
*)
      END (* FOR *) 

    ; FOR j := '\000' TO ClassCount 
      DO Class := j 
      ; IntSets . ForAllDo ( ClassMemPtr ^ [ j ] , CharToClass0 ) 
      END (* FOR *) 

    ; LastCh := ClassCount 
    ; IntSets . ForAllDo ( CharSet , CharToClass ) 
    END ComputeClasses 

; PROCEDURE ReleaseSetMem ( ) 

  = BEGIN (* ReleaseSetMem *) 
      FOR i := 1 TO SetCount 
      DO
        SetMemPtr ^ [ i ] . Set := NIL
      ; SetMemPtr ^ [ i ] . Classes := NIL
(*      ReleaseSet ( SetMemPtr ^ [ i ] . Set ) 
      ; ReleaseSet ( SetMemPtr ^ [ i ] . Classes )
*)
      END (* FOR *) 
    ; ReleaseArray ( SetMemPtr , SetMemSize , BYTESIZE ( ClassInfo ) ) 
    END ReleaseSetMem 

; BEGIN (* Classes *) 
    SetMemSize := 16 
  ; MakeArray 
      ( LOOPHOLE ( SetMemPtr , ADDRESS ) 
      , SetMemSize 
      , BYTESIZE ( ClassInfo ) 
      ) 
  ; SetCount := 0 
  ; ClassMemSize := 16 
  ; MakeArray 
      ( LOOPHOLE ( ClassMemPtr , ADDRESS )
      , ClassMemSize
      , BYTESIZE ( IntSets . T )
      ) 
  END Classes 
. 

