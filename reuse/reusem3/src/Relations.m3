 (* Ich, Doktor Josef Grosch, Informatiker, 8.1.1988 *) 

UNSAFE MODULE Relations 


; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT SHORTCARD 

; FROM ReuseIO IMPORT tFile , ReadI , ReadC , WriteI , WriteC 

; FROM DynArray IMPORT MakeArray , ReleaseArray 

; FROM Sets IMPORT tSet 

; IMPORT Sets 

; VAR i : INTEGER 

; PROCEDURE MakeRelation ( VAR Rel : tRelation ; Max1 , Max2 : INTEGER ) 

  = VAR ElmtCount : M2LONGINT 

  ; BEGIN (* MakeRelation *) 
      Rel . Max1 := Max1 
    ; Rel . Max2 := Max2 
    ; ElmtCount := VAL ( Max1 + 1 , M2LONGINT ) 
    ; MakeArray 
        ( LOOPHOLE ( Rel . ArrayPtr , ADDRESS ) 
        , ElmtCount 
        , BYTESIZE ( tSet ) 
        ) 
    ; FOR i := 0 TO Rel . Max1 
      DO Sets . MakeSet ( Rel . ArrayPtr ^ [ i ] , Max2 ) 
      END (* FOR *) 
    END MakeRelation 

; PROCEDURE ReleaseRelation ( VAR Rel : tRelation ) 

  = VAR ElmtCount : M2LONGINT 

  ; BEGIN (* ReleaseRelation *) 
      FOR i := 0 TO Rel . Max1 
      DO Sets . ReleaseSet ( Rel . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    ; ElmtCount := VAL ( Rel . Max1 + 1 , M2LONGINT ) 
    ; ReleaseArray ( Rel . ArrayPtr , ElmtCount , BYTESIZE ( tSet ) ) 
    END ReleaseRelation 

; PROCEDURE Include ( VAR Rel : tRelation ; e1 , e2 : INTEGER ) 

  = BEGIN (* Include *) 
      Sets . Include ( Rel . ArrayPtr ^ [ e1 ] , e2 ) 
    END Include 

; PROCEDURE Exclude ( VAR Rel : tRelation ; e1 , e2 : INTEGER ) 

  = BEGIN (* Exclude *) 
      Sets . Exclude ( Rel . ArrayPtr ^ [ e1 ] , e2 ) 
    END Exclude 

; PROCEDURE IsElement ( e1 , e2 : INTEGER ; Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsElement *) 
      RETURN Sets . IsElement ( e2 , Rel . ArrayPtr ^ [ e1 ] ) 
    END IsElement 

; PROCEDURE IsRelated ( e1 , e2 : INTEGER ; Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsRelated *) 
      RETURN Sets . IsElement ( e2 , Rel . ArrayPtr ^ [ e1 ] ) 
    END IsRelated 

; PROCEDURE IsReflexive1 ( e1 : INTEGER ; Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsReflexive1 *) 
      RETURN Sets . IsElement ( e1 , Rel . ArrayPtr ^ [ e1 ] ) 
    END IsReflexive1 

; PROCEDURE IsSymmetric1 ( e1 , e2 : INTEGER ; Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsSymmetric1 *) 
      RETURN 
        ( NOT Sets . IsElement ( e2 , Rel . ArrayPtr ^ [ e1 ] ) ) 
        OR Sets . IsElement ( e1 , Rel . ArrayPtr ^ [ e2 ] ) 
    END IsSymmetric1 

; PROCEDURE IsTransitive1 
    ( e1 , e2 , e3 : INTEGER ; Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsTransitive1 *) 
      RETURN 
        ( NOT ( Sets . IsElement ( e2 , Rel . ArrayPtr ^ [ e1 ] ) 
                AND Sets . IsElement ( e3 , Rel . ArrayPtr ^ [ e2 ] ) 
              ) 
        ) 
        OR Sets . IsElement ( e3 , Rel . ArrayPtr ^ [ e1 ] ) 
    END IsTransitive1 

; PROCEDURE IsReflexive ( Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsReflexive *) 
      FOR i := 0 TO Rel . Max1 
      DO IF NOT Sets . IsElement ( i , Rel . ArrayPtr ^ [ i ] ) 
         THEN 
           RETURN FALSE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN TRUE 
    END IsReflexive 

; VAR gRel : tRelation 

; PROCEDURE gSymmetric ( e : Sets . tElement ) : BOOLEAN 

  = BEGIN (* gSymmetric *) 
      RETURN Sets . IsElement ( i , gRel . ArrayPtr ^ [ e ] ) 
    END gSymmetric 

; PROCEDURE IsSymmetric ( Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsSymmetric *) 
      gRel := Rel 
    ; FOR i := 0 TO Rel . Max1 
      DO IF NOT Sets . Forall ( Rel . ArrayPtr ^ [ i ] , gSymmetric ) 
         THEN 
           RETURN FALSE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN TRUE 
    END IsSymmetric 

; PROCEDURE IsTransitive ( Rel : tRelation ) : BOOLEAN 

  = VAR r : tRelation 
  ; VAR Result : BOOLEAN 

  ; BEGIN (* IsTransitive *) 
      MakeRelation ( r , Rel . Max1 , Rel . Max2 ) 
    ; Assign ( r , Rel ) 
    ; Closure ( r ) 
    ; Result := IsEqual ( r , Rel ) 
    ; ReleaseRelation ( r ) 
    ; RETURN Result 
    END IsTransitive 

; PROCEDURE IsEquivalence ( Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsEquivalence *) 
      RETURN 
        IsReflexive ( Rel ) AND IsSymmetric ( Rel ) AND IsTransitive ( Rel ) 
    END IsEquivalence 

; PROCEDURE HasReflexive ( Rel : tRelation ) : BOOLEAN 

  = BEGIN (* HasReflexive *) 
      FOR i := 0 TO Rel . Max1 
      DO IF Sets . IsElement ( i , Rel . ArrayPtr ^ [ i ] ) 
         THEN 
           RETURN TRUE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN FALSE 
    END HasReflexive 

(* 
PROCEDURE IsCyclic      (Rel: tRelation): BOOLEAN; 
   VAR r        : tRelation; 
   VAR Result   : BOOLEAN; 
   BEGIN 
      MakeRelation (r, Rel.Max1, Rel.Max2); 
      Assign (r, Rel); 
      Closure (r); 
      Result := HasReflexive (r); 
      ReleaseRelation (r); 
      RETURN Result; 
   END IsCyclic; 
*) 

; TYPE PredCount = ARRAY [ 0 .. 100000000 ] OF SHORTCARD 

; VAR PredCountPtr : UNTRACED BRANDED REF PredCount 
; VAR WithoutPred : tSet 

; PROCEDURE IsCyclic ( Rel : tRelation ) : BOOLEAN 

  = VAR PredCountSize : M2LONGINT 
  ; VAR WithPred : tSet 
  ; VAR Result : BOOLEAN 

  ; BEGIN (* IsCyclic *)                (* cycle test for graphs *) 
      PredCountSize := VAL ( Rel . Max1 + 1 , M2LONGINT ) 
    ; MakeArray 
        ( LOOPHOLE ( PredCountPtr , ADDRESS ) 
        , PredCountSize 
        , BYTESIZE ( SHORTCARD ) 
        ) 
    ; Sets . MakeSet ( WithoutPred , Rel . Max1 ) 
    ; Sets . MakeSet ( WithPred , Rel . Max1 ) 
    ; FOR i := 0 TO Rel . Max1 DO PredCountPtr ^ [ i ] := 0 END (* FOR *) 
    ; FOR i := 0 TO Rel . Max1 
      DO Sets . ForallDo ( Rel . ArrayPtr ^ [ i ] , gPredCount ) 
      END (* FOR *) 
    ; FOR i := 0 TO Rel . Max1 
      DO IF PredCountPtr ^ [ i ] = 0 
         THEN 
           Sets . Include ( WithoutPred , i ) 
         END (* IF *) 
      END (* FOR *) 
    ; Sets . Complement ( WithPred ) 
    ; WHILE NOT Sets . IsEmpty ( WithoutPred ) 
      DO i := Sets . Extract ( WithoutPred ) 
      ; Sets . Exclude ( WithPred , i ) 
      ; Sets . ForallDo ( Rel . ArrayPtr ^ [ i ] , gPredCount2 ) 
      END (* WHILE *) 
    ; Result := NOT Sets . IsEmpty ( WithPred ) 
    ; Sets . ReleaseSet ( WithoutPred ) 
    ; Sets . ReleaseSet ( WithPred ) 
    ; ReleaseArray ( PredCountPtr , PredCountSize , BYTESIZE ( SHORTCARD ) ) 
    ; RETURN Result 
    END IsCyclic 

; PROCEDURE gPredCount ( e : Sets . tElement ) 

  = BEGIN (* gPredCount *) 
      INC ( PredCountPtr ^ [ e ] ) 
    END gPredCount 

; PROCEDURE gPredCount2 ( e : Sets . tElement ) 

  = BEGIN (* gPredCount2 *) 
      DEC ( PredCountPtr ^ [ e ] ) 
    ; IF PredCountPtr ^ [ e ] = 0 
      THEN 
        Sets . Include ( WithoutPred , e ) 
      END (* IF *) 
    END gPredCount2 

; PROCEDURE GetCyclics ( Rel : tRelation ; VAR Set : tSet ) 

  = VAR r : tRelation 

  ; BEGIN (* GetCyclics *) 
      MakeRelation ( r , Rel . Max1 , Rel . Max2 ) 
    ; Assign ( r , Rel ) 
    ; Closure ( r ) 
    ; Sets . AssignEmpty ( Set ) 
    ; FOR i := 0 TO r . Max1 
      DO IF Sets . IsElement ( i , r . ArrayPtr ^ [ i ] ) 
         THEN   (* IsReflexive *) 
           Sets . Include ( Set , VAL ( i , INTEGER ) ) 
         END (* IF *) 
      END (* FOR *) 
    ; ReleaseRelation ( r ) 
    END GetCyclics 

; PROCEDURE AssignEmpty ( VAR Rel : tRelation ) 

  = BEGIN (* AssignEmpty *) 
      FOR i := 0 TO Rel . Max1 
      DO Sets . AssignEmpty ( Rel . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    END AssignEmpty 

; PROCEDURE AssignElmt ( VAR Rel : tRelation ; e1 , e2 : INTEGER ) 

  = BEGIN (* AssignElmt *) 
      AssignEmpty ( Rel ) 
    ; Include ( Rel , e1 , e2 ) 
    END AssignElmt 

; PROCEDURE Assign ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

  = BEGIN (* Assign *) 
      FOR i := 0 TO Rel1 . Max1 
      DO Sets . Assign ( Rel1 . ArrayPtr ^ [ i ] , Rel2 . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    END Assign 

; PROCEDURE Closure ( VAR Rel : tRelation ) 

  = VAR aj : tSet 

  ; BEGIN (* Closure *)                 (* Warshall *) 
      WITH With_24 = Rel 
      DO FOR j := 0 TO With_24 . Max1 
         DO IF NOT Sets . IsEmpty ( With_24 . ArrayPtr ^ [ j ] ) 
            THEN 
              aj := With_24 . ArrayPtr ^ [ j ] 
            ; FOR i := 0 TO With_24 . Max1 
              DO IF Sets . IsElement ( j , With_24 . ArrayPtr ^ [ i ] ) 
                 THEN 
                   Sets . Union ( With_24 . ArrayPtr ^ [ i ] , aj ) 
                 END (* IF *) 
              END (* FOR *) 
            END (* IF *) 
         END (* FOR *) 
      END (* WITH *) 
    END Closure 

; PROCEDURE Union ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

  = BEGIN (* Union *) 
      FOR i := 0 TO Rel1 . Max1 
      DO Sets . Union ( Rel1 . ArrayPtr ^ [ i ] , Rel2 . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    END Union 

; PROCEDURE Difference ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

  = BEGIN (* Difference *) 
      FOR i := 0 TO Rel1 . Max1 
      DO Sets . Difference 
           ( Rel1 . ArrayPtr ^ [ i ] , Rel2 . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    END Difference 

; PROCEDURE Intersection ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

  = BEGIN (* Intersection *) 
      FOR i := 0 TO Rel1 . Max1 
      DO Sets . Intersection 
           ( Rel1 . ArrayPtr ^ [ i ] , Rel2 . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    END Intersection 

; PROCEDURE SymDiff ( VAR Rel1 : tRelation ; Rel2 : tRelation ) 

  = BEGIN (* SymDiff *) 
      FOR i := 0 TO Rel1 . Max1 
      DO Sets . SymDiff ( Rel1 . ArrayPtr ^ [ i ] , Rel2 . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    END SymDiff 

; PROCEDURE Complement ( VAR Rel : tRelation ) 

  = BEGIN (* Complement *) 
      FOR i := 0 TO Rel . Max1 
      DO Sets . Complement ( Rel . ArrayPtr ^ [ i ] ) 
      END (* FOR *) 
    END Complement 

; PROCEDURE IsSubset ( Rel1 , Rel2 : tRelation ) : BOOLEAN 

  = BEGIN (* IsSubset *) 
      FOR i := 0 TO Rel1 . Max1 
      DO IF NOT Sets . IsSubset 
                  ( Rel1 . ArrayPtr ^ [ i ] , Rel2 . ArrayPtr ^ [ i ] ) 
         THEN 
           RETURN FALSE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN TRUE 
    END IsSubset 

; PROCEDURE IsStrictSubset ( Rel1 , Rel2 : tRelation ) : BOOLEAN 

  = BEGIN (* IsStrictSubset *) 
      RETURN IsSubset ( Rel1 , Rel2 ) AND IsNotEqual ( Rel1 , Rel2 ) 
    END IsStrictSubset 

; PROCEDURE IsEqual ( VAR Rel1 , Rel2 : tRelation ) : BOOLEAN 

  = BEGIN (* IsEqual *) 
      FOR i := 0 TO Rel1 . Max1 
      DO IF NOT Sets . IsEqual 
                  ( Rel1 . ArrayPtr ^ [ i ] , Rel2 . ArrayPtr ^ [ i ] ) 
         THEN 
           RETURN FALSE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN TRUE 
    END IsEqual 

; PROCEDURE IsNotEqual ( Rel1 , Rel2 : tRelation ) : BOOLEAN 

  = BEGIN (* IsNotEqual *) 
      RETURN NOT IsEqual ( Rel1 , Rel2 ) 
    END IsNotEqual 

; PROCEDURE IsEmpty ( Rel : tRelation ) : BOOLEAN 

  = BEGIN (* IsEmpty *) 
      FOR i := 0 TO Rel . Max1 
      DO IF NOT Sets . IsEmpty ( Rel . ArrayPtr ^ [ i ] ) 
         THEN 
           RETURN FALSE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN TRUE 
    END IsEmpty 

; PROCEDURE Card ( VAR Rel : tRelation ) : INTEGER 

  = VAR n : INTEGER 

  ; BEGIN (* Card *) 
      n := 0 
    ; FOR i := 0 TO Rel . Max1 
      DO INC ( n , Sets . Card ( Rel . ArrayPtr ^ [ i ] ) ) 
      END (* FOR *) 
    ; RETURN n 
    END Card 

; PROCEDURE Select ( VAR Rel : tRelation ; VAR e1 , e2 : INTEGER ) 

  = BEGIN (* Select *) 
      FOR i := 0 TO Rel . Max1 
      DO IF NOT Sets . IsEmpty ( Rel . ArrayPtr ^ [ i ] ) 
         THEN 
           e1 := VAL ( i , INTEGER ) 
         ; e2 := Sets . Select ( Rel . ArrayPtr ^ [ i ] ) 
         ; RETURN 
         END (* IF *) 
      END (* FOR *) 
    ; e1 := 0 
    ; e2 := 0 
    END Select 

; PROCEDURE Extract ( VAR Rel : tRelation ; VAR e1 , e2 : INTEGER ) 

  = BEGIN (* Extract *) 
      Select ( Rel , e1 , e2 ) 
    ; Exclude ( Rel , e1 , e2 ) 
    END Extract 

; VAR gProc2b : ProcOfIntIntToBool 

; PROCEDURE gProc1b ( e : Sets . tElement ) : BOOLEAN 

  = BEGIN (* gProc1b *) 
      RETURN gProc2b ( VAL ( i , INTEGER ) , e ) 
    END gProc1b 

; PROCEDURE Forall ( Rel : tRelation ; Proc : ProcOfIntIntToBool ) : BOOLEAN 

  = BEGIN (* Forall *) 
      gProc2b := Proc 
    ; FOR i := 0 TO Rel . Max1 
      DO IF NOT Sets . Forall ( Rel . ArrayPtr ^ [ i ] , gProc1b ) 
         THEN 
           RETURN FALSE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN TRUE 
    END Forall 

; PROCEDURE Exists ( Rel : tRelation ; Proc : ProcOfIntIntToBool ) : BOOLEAN 

  = BEGIN (* Exists *) 
      gProc2b := Proc 
    ; FOR i := 0 TO Rel . Max1 
      DO IF Sets . Exists ( Rel . ArrayPtr ^ [ i ] , gProc1b ) 
         THEN 
           RETURN TRUE 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN FALSE 
    END Exists 

; PROCEDURE Exists1 ( Rel : tRelation ; Proc : ProcOfIntIntToBool ) : BOOLEAN 

  = VAR n : INTEGER 

  ; BEGIN (* Exists1 *) 
      n := 0 
    ; gProc2b := Proc 
    ; FOR i := 0 TO Rel . Max1 
      DO IF Sets . Exists ( Rel . ArrayPtr ^ [ i ] , gProc1b ) 
         THEN 
           INC ( n ) 
         END (* IF *) 
      END (* FOR *) 
    ; RETURN n = 1 
    END Exists1 

; VAR gProc2 : ProcOfIntInt 

; PROCEDURE gProc1 ( e : Sets . tElement ) 

  = BEGIN (* gProc1 *) 
      gProc2 ( VAL ( i , INTEGER ) , e ) 
    END gProc1 

; PROCEDURE ForallDo ( Rel : tRelation ; Proc : ProcOfIntInt ) 

  = BEGIN (* ForallDo *) 
      gProc2 := Proc 
    ; FOR i := 0 TO Rel . Max1 
      DO Sets . ForallDo ( Rel . ArrayPtr ^ [ i ] , gProc1 ) 
      END (* FOR *) 
    END ForallDo 

; PROCEDURE ReadRelation ( f : tFile ; VAR Rel : tRelation ) 

  = VAR ch : CHAR 
  ; VAR i : INTEGER 

  ; BEGIN (* ReadRelation *) 
      REPEAT UNTIL ReadC ( f ) = '{' 
    ; AssignEmpty ( Rel ) 
    ; LOOP 
        IF ReadC ( f ) = '}' THEN EXIT END (* IF *) 
      ; i := ReadI ( f ) 
      ; Include ( Rel , i , ReadI ( f ) ) 
      ; ch := ReadC ( f ) 
      END (* LOOP *) 
    END ReadRelation 

; VAR g : tFile 

; PROCEDURE WriteRelation ( f : tFile ; Rel : tRelation ) 

  = BEGIN (* WriteRelation *) 
      g := f 
    ; WriteC ( f , '{' ) 
    ; ForallDo ( Rel , WritePair ) 
    ; WriteC ( f , '}' ) 
    END WriteRelation 

; PROCEDURE WritePair ( e1 , e2 : INTEGER ) 

  = BEGIN (* WritePair *) 
      WriteC ( g , ' ' ) 
    ; WriteI ( g , e1 , 1 ) 
    ; WriteC ( g , ' ' ) 
    ; WriteI ( g , e2 , 1 ) 
    ; WriteC ( g , ',' ) 
    END WritePair 

; BEGIN (* Relations *) 
  END Relations 
. 

