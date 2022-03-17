
(* $Id: RelDrv.mi,v 1.3 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: RelDrv.mi,v $ 
Revision 1.3  1991/11/21  14:33:17  grosch 
new version of RCS on SPARC 
 
Revision 1.2  90/06/11  10:40:57  grosch 
added procedure GetCyclics 
 
Revision 1.1  90/03/02  17:35:02  grosch 
improved output behaviour using WriteFlush 
 
Revision 1.0  89/11/02  18:24:02  grosch 
Initial revision 
 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, 8.1.1988 *) 

UNSAFE MODULE RelDrv EXPORTS Main 

; FROM ReuseIO 
  IMPORT StdInput , StdOutput , ReadI , ReadC , WriteI , WriteS , WriteFlush 
  , WriteB 
  , WriteNl , CloseIO 

; FROM Sets IMPORT tSet , MakeSet , ReleaseSet , WriteSet 

; FROM Relations 
  IMPORT tRelation , MakeRelation , ReleaseRelation , Include , Exclude 
  , IsElement 
  , IsRelated , IsReflexive1 , IsSymmetric1 , IsTransitive1 , IsReflexive 
  , IsSymmetric 
  , IsTransitive , IsEquivalence , HasReflexive , IsCyclic , GetCyclics 
  , Closure 
  , AssignEmpty , AssignElmt , Assign , Union , Difference , Intersection 
  , SymDiff 
  , Complement , IsSubset , IsStrictSubset , IsEqual , IsNotEqual , IsEmpty 
  , Card 
  , Select , Extract , Forall , Exists , Exists1 , ForallDo , ReadRelation 
  , WriteRelation 

; VAR r1 , r2 : tRelation 
  ; s : INTEGER 
  ; c : CHAR 
  ; s2 : tSet 

; BEGIN (* RelDrv *) 
    MakeRelation ( r2 , 10 , 20 ) 
  ; Include ( r2 , 0 , 9 ) 
  ; Include ( r2 , 9 , 1 ) 
  ; Include ( r2 , 1 , 8 ) 
  ; Include ( r2 , 8 , 0 ) 
  ; WriteRelation ( StdOutput , r2 ) 
  ; WriteNl ( StdOutput ) 
  ; Closure ( r2 ) 
  ; WriteRelation ( StdOutput , r2 ) 
  ; WriteNl ( StdOutput ) 
  ; ReleaseRelation ( r2 ) 

  ; MakeRelation ( r1 , 10 , 20 ) 
  ; Include ( r1 , 2 , 3 ) 
  ; Include ( r1 , 3 , 4 ) 
  ; WriteNl ( StdOutput ) 
  ; WriteS 
      ( StdOutput 
      , ARRAY [ 0 .. 55 ] OF CHAR 
          { 'e' , 'n' , 't' , 'e' , 'r' , ' ' , 'S' , 'i' , 'z' , 'e' , ' ' 
          , 'a' 
          , 'n' , 'd' , ' ' , 'R' , 'e' , 'l' , 'a' , 't' , 'i' , 'o' , 'n' 
          , ' ' , 'l' , 'i' , 'k' , 'e' , ' ' , 'b' , 'e' , 'l' , 'o' , 'w' 
          , '!' 
          , ' ' , '(' , 'S' , 'i' , 'z' , 'e' , '=' , '0' , ' ' , 't' , 'e' 
          , 'r' , 'm' , 'i' , 'n' , 'a' , 't' , 'e' , 's' , ')' , '\000' 
          } 
      ) 
  ; WriteNl ( StdOutput ) 
  ; WriteI ( StdOutput , 4 , 3 ) 
  ; WriteS ( StdOutput , ' ' ) 
  ; WriteRelation ( StdOutput , r1 ) 
  ; WriteNl ( StdOutput ) 
  ; ReleaseRelation ( r1 ) 

  ; LOOP 
      WriteNl ( StdOutput ) 
    ; WriteFlush ( StdOutput ) 
    ; s := ReadI ( StdInput ) 
    ; IF s = 0 THEN EXIT END (* IF *) 
    ; MakeSet ( s2 , s ) 
    ; MakeRelation ( r2 , s , s ) 
    ; ReadRelation ( StdInput , r2 ) 
    ; WriteRelation ( StdOutput , r2 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'R' , 'e' , 'f' , 'l' , 'e' , 'x' , 'i' , 'v' , 'e' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsReflexive ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'S' , 'y' , 'm' , 'm' , 'e' , 't' , 'r' , 'i' , 'c' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsSymmetric ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'T' , 'r' , 'a' , 'n' , 's' , 'i' , 't' , 'i' , 'v' , 'e' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsTransitive ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'E' , 'q' , 'u' , 'i' , 'v' , 'a' , 'l' , 'e' , 'n' , 'c' , 'e' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsEquivalence ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'H' , 'a' , 's' , 'R' , 'e' , 'f' , 'l' , 'e' , 'x' , 'i' , 'v' 
            , 'e' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , HasReflexive ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 22 ] OF CHAR 
            { 'C' , 'y' , 'c' , 'l' , 'i' , 'c' , ' ' , ' ' , ' ' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , '=' , ' ' 
            , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsCyclic ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'C' , 'a' , 'r' , 'd' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteI ( StdOutput , Card ( r2 ) , 1 ) 
    ; WriteNl ( StdOutput ) 
    ; GetCyclics ( r2 , s2 ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 22 ] OF CHAR 
            { 'C' , 'y' , 'c' , 'l' , 'i' , 'c' , 's' , ' ' , ' ' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , '=' , ' ' 
            , '\000' 
            } 
        ) 
    ; WriteSet ( StdOutput , s2 ) 
    ; WriteNl ( StdOutput ) 
    ; Closure ( r2 ) 
    ; WriteRelation ( StdOutput , r2 ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'R' , 'e' , 'f' , 'l' , 'e' , 'x' , 'i' , 'v' , 'e' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsReflexive ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'S' , 'y' , 'm' , 'm' , 'e' , 't' , 'r' , 'i' , 'c' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsSymmetric ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'T' , 'r' , 'a' , 'n' , 's' , 'i' , 't' , 'i' , 'v' , 'e' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsTransitive ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'E' , 'q' , 'u' , 'i' , 'v' , 'a' , 'l' , 'e' , 'n' , 'c' , 'e' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsEquivalence ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'H' , 'a' , 's' , 'R' , 'e' , 'f' , 'l' , 'e' , 'x' , 'i' , 'v' 
            , 'e' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , HasReflexive ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 22 ] OF CHAR 
            { 'C' , 'y' , 'c' , 'l' , 'i' , 'c' , ' ' , ' ' , ' ' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , '=' , ' ' 
            , '\000' 
            } 
        ) 
    ; WriteB ( StdOutput , IsCyclic ( r2 ) ) 
    ; WriteNl ( StdOutput ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 16 ] OF CHAR 
            { 'C' , 'a' , 'r' , 'd' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , '=' , ' ' , '\000' 
            } 
        ) 
    ; WriteI ( StdOutput , Card ( r2 ) , 1 ) 
    ; WriteNl ( StdOutput ) 
    ; GetCyclics ( r2 , s2 ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 22 ] OF CHAR 
            { 'C' , 'y' , 'c' , 'l' , 'i' , 'c' , 's' , ' ' , ' ' , ' ' , ' ' 
            , ' ' 
            , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , '=' , ' ' 
            , '\000' 
            } 
        ) 
    ; WriteSet ( StdOutput , s2 ) 
    ; WriteNl ( StdOutput ) 
    ; ReleaseRelation ( r2 ) 
    ; ReleaseSet ( s2 ) 
    END (* LOOP *) 

  ; CloseIO ( ) 
  END RelDrv 
. 

