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

; IMPORT ObjList 

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
      ;  IF IsInIntSetMem ( SetIntSet ) = 0 
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
         ; ObjList . Add ( SetIntSet ) 
         ; SetMemPtr ^ [ SetCount ] . Set := SetIntSet 
         ; Unused := IntSets . Union ( Unused , SetIntSet)
(*       ; MakeSet ( SetMemPtr ^ [ SetCount ] . Set , ORD ( LastCh ) ) 
         ; Assign ( SetMemPtr ^ [ SetCount ] . Set , Set ) 
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

  = VAR LSet , LSet2 , LSet3 : Sets . tSet  
  ; VAR LIntSet , LIntSet1 , LIntSet2 , LAddIntSet : IntSets . T
  ; VAR LEq , LEq2 : BOOLEAN

; VAR Break := 0 

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
      ; CharSet := IntSets . Complement ( CharSet , 0 , ORD ( LastCh ) ) 
      END (* IF *) 

    ; ClassCount := '\000'

    ; LIntSet := IntSets . Union ( CharSet , Unused )
    ; LIntSet1 := IntSets . Complement ( LIntSet , 0 , ORD ( LastCh ) )

    ; LAddIntSet
        := IntSets . Complement
             ( IntSets . Union ( CharSet , Unused ) , 0 , ORD ( LastCh ) )
    ; ObjList . Add ( LAddIntSet ) 
    ; ClassMemPtr ^ [ '\000' ] := LAddIntSet 
    ; LEq := IntSets . Equal ( LIntSet1 , ClassMemPtr ^ [ '\000' ] )  
    ; Sets . MakeSet ( LSet , ORD ( LastCh ) ) 
    ; Sets . MakeSet ( LSet2 , ORD ( LastCh ) )  
(*
    ; Sets . Assign ( LSet , CharSet ) 
    ; Sets . Union ( LSet, Unused ) 
    ; Sets . Complement ( LSet )

    ; LSet2 := Sets . FromIntSet ( LSet2 , LIntSet1 ) 
    ; LEq2 := IntSets . Equal ( LSet2 , LSet ) 
*)
(*  ; MakeSet ( ClassMemPtr ^ [ '\000' ] , ORD ( LastCh ) ) 
    ; Assign ( ClassMemPtr ^ [ '\000' ] , CharSet ) 
    ; Union ( ClassMemPtr ^ [ '\000' ] , Unused ) 
    ; Complement ( ClassMemPtr ^ [ '\000' ] )
*)

    ; Sets . MakeSet ( LSet3 , ORD ( LastCh ) )
    
    ; FOR i := 1 TO SetCount 
      DO FOR j := '\000' TO ClassCount 
         DO
           LIntSet
             := IntSets . Intersection
                 ( IntSets . Difference ( SetMemPtr ^ [ i ] . Set , CharSet )
                 , ClassMemPtr ^ [ j ]
                 )

         ; Sets . FromIntSet ( LSet , SetMemPtr ^ [ i ] . Set )
         ; Sets . FromIntSet ( LSet2 , CharSet )
         ; Sets . Difference ( LSet , LSet2 ) 
         ; Sets . FromIntSet ( LSet3 , ClassMemPtr ^ [ j ] )
         ; Sets . Intersection ( LSet , LSet3 ) 

         ; IF NOT Sets . IsEqualIntSet ( LSet , LIntSet )
           THEN
             LEq := TRUE 
           END (* IF *)

         ; IF NOT IntSets . IsEmpty ( LIntSet )  
              AND NOT IntSets . Equal ( LIntSet , ClassMemPtr ^ [ j ] )  
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
           ; ObjList . Add ( LIntSet ) 
           ; ClassMemPtr ^ [ ClassCount ] := LIntSet 
           ; WITH WClassJ = ClassMemPtr ^ [ j ]
             DO
               LIntSet := IntSets . Difference ( WClassJ , LIntSet ) 
             ; WClassJ := LIntSet 
             END (* WITH *)
(*         ; MakeSet ( ClassMemPtr ^ [ ClassCount ] , ORD ( LastCh ) ) 
           ; Assign ( ClassMemPtr ^ [ ClassCount ] , Set ) 
           ; Difference ( ClassMemPtr ^ [ j ] , Set )
*)
           END (* IF *)
; Break := 5 
         END (* FOR *) 
      END (* FOR *)
    ; Sets . ReleaseSet ( LSet ) 
    ; Sets . ReleaseSet ( LSet2 ) 
    ; Sets . ReleaseSet ( LSet3 ) 
    ; LIntSet := NIL  

    ; FOR i := 1 TO SetCount 
      DO
        SetMemPtr ^ [ i ] . Classes := IntSets . Empty ( ) 
      ; FOR j := '\000' TO ClassCount 
        DO IF IntSets . IsSubset
                ( ClassMemPtr ^ [ j ] , SetMemPtr ^ [ i ] . Set ) 
           THEN
             WITH WClasses = SetMemPtr ^ [ i ] . Classes
             DO
               LIntSet := IntSets . Include ( WClasses , ORD ( j ) )
             ; ObjList . Add ( LIntSet ) 
             ; WClasses := LIntSet 
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
        EVAL ObjList .Remove ( SetMemPtr ^ [ i ] . Set )
      ; SetMemPtr ^ [ i ] . Set := NIL
      ; EVAL ObjList .Remove ( SetMemPtr ^ [ i ] . Classes )
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

