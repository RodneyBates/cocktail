
(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE DynArray 

; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT ODD 

; FROM General IMPORT Log2 , Exp2 , MaxAlign 

; FROM Memory IMPORT Alloc , Free 

; FROM ReuseIO IMPORT StdError , WriteS , WriteNl 

(* INVARIANT ElmtCount * AlignedSize (ElmtSize) MOD TSIZE (M2LONGINT) = 0 *) 

; PROCEDURE MakeArray 
    ( VAR ArrayPtr : ADDRESS 
    ; VAR ElmtCount : M2LONGINT 
    ; ElmtSize : M2LONGINT 
    ) 

  = BEGIN (* MakeArray *) 
      ElmtSize := AlignedSize ( ElmtSize ) 
    ; CASE ElmtSize MOD 4 
      OF 0 
      => 
      | 2 
      => IF ODD ( ElmtCount ) THEN INC ( ElmtCount ) END (* IF *) 
      | 1 , 3 
      => INC 
           ( ElmtCount 
           , BYTESIZE ( M2LONGINT ) 
             - 1 
             - ( ( ElmtCount - 1 ) MOD BYTESIZE ( M2LONGINT ) ) 
           ) 
      END (* CASE *) 
    ; ArrayPtr := Alloc ( ElmtCount * ElmtSize ) 
    ; IF ArrayPtr = NIL 
      THEN 
        WriteS 
          ( StdError 
          , ARRAY [ 0 .. 24 ] OF CHAR 
              { 'M' , 'a' , 'k' , 'e' , 'A' , 'r' , 'r' , 'a' , 'y' , ':' 
              , ' ' 
              , 'o' , 'u' , 't' , ' ' , 'o' , 'f' , ' ' , 'm' , 'e' , 'm' 
              , 'o' , 'r' , 'y' , '\000' 
              } 
          ) 
      ; WriteNl ( StdError ) 
      END (* IF *) 
    END MakeArray 

; PROCEDURE ExtendArray 
    ( VAR ArrayPtr : ADDRESS 
    ; VAR ElmtCount : M2LONGINT 
    ; ElmtSize : M2LONGINT 
    ) 

  = VAR NewPtr : ADDRESS 
    ; Source , Target : UNTRACED BRANDED REF M2LONGINT 

  ; BEGIN (* ExtendArray *) 
      ElmtSize := AlignedSize ( ElmtSize ) 
    ; NewPtr := Alloc ( ElmtCount * ElmtSize * 2 ) 
    ; IF NewPtr = NIL 
      THEN 
        WriteS 
          ( StdError 
          , ARRAY [ 0 .. 26 ] OF CHAR 
              { 'E' , 'x' , 't' , 'e' , 'n' , 'd' , 'A' , 'r' , 'r' , 'a' 
              , 'y' 
              , ':' , ' ' , 'o' , 'u' , 't' , ' ' , 'o' , 'f' , ' ' , 'm' 
              , 'e' , 'm' , 'o' , 'r' , 'y' , '\000' 
              } 
          ) 
      ; WriteNl ( StdError ) 
      ELSE 
        Source := ArrayPtr 
      ; Target := NewPtr 
      ; FOR i := 1 TO ElmtCount * ElmtSize DIV BYTESIZE ( M2LONGINT ) 
        DO Target ^ := Source ^ 
        ; Source 
            := LOOPHOLE 
                 ( LOOPHOLE ( Source , ADDRESS ) + BYTESIZE ( M2LONGINT ) 
                 , ADDRESS 
                 ) 
        ; Target 
            := LOOPHOLE 
                 ( LOOPHOLE ( Target , ADDRESS ) + BYTESIZE ( M2LONGINT ) 
                 , ADDRESS 
                 ) 
        END (* FOR *) 
      ; Free ( ElmtCount * ElmtSize , ArrayPtr ) 
      ; INC ( ElmtCount , ElmtCount ) 
      END (* IF *) 
    ; ArrayPtr := NewPtr 
    END ExtendArray 

; PROCEDURE ReleaseArray 
    ( ArrayPtr : ADDRESS ; ElmtCount : M2LONGINT ; ElmtSize : M2LONGINT ) 

  = BEGIN (* ReleaseArray *) 
      ElmtSize := AlignedSize ( ElmtSize ) 
    ; Free ( ElmtCount * ElmtSize , ArrayPtr ) 
    END ReleaseArray 

; PROCEDURE AlignedSize ( ElmtSize : M2LONGINT ) : M2LONGINT 

  = VAR Align : M2LONGINT 

  ; BEGIN (* AlignedSize *) 
      IF ElmtSize >= VAL ( MaxAlign , M2LONGINT ) 
      THEN 
        Align := VAL ( MaxAlign , M2LONGINT ) 
      ELSE 
        Align := Exp2 ( Log2 ( ElmtSize + ElmtSize - 2 ) ) 
      END (* IF *) 
    ; RETURN ElmtSize + Align - 1 - ( ( ElmtSize - 1 ) MOD Align ) 
    END AlignedSize 

; BEGIN (* DynArray *) 
  END DynArray 
. 

