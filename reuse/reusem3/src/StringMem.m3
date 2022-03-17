
(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE StringMem 


; FROM SYSTEM IMPORT M2LONGINT 
; IMPORT Word 

; FROM DynArray IMPORT MakeArray , ExtendArray 

; FROM Strings IMPORT tStringIndex , tString 

; FROM ReuseIO IMPORT tFile , StdOutput , WriteC , WriteI , WriteNl , WriteS 

; CONST InitialMemorySize = 1024 * 16 

; TYPE Memory = ARRAY [ 0 .. 100000000 ] OF CHAR 

; VAR MemoryPtr : UNTRACED BRANDED REF Memory 
  ; MemorySize : M2LONGINT 
  ; MemorySpaceLeft : M2LONGINT 
  ; MemoryFreePtr : M2LONGINT 

; PROCEDURE PutString ( READONLY s : tString ) : tStringRef 

  = VAR NeededSpace : M2LONGINT 
    ; OldMemorySize : M2LONGINT 
    ; StartPtr : M2LONGINT 

  ; BEGIN (* PutString *) 
      NeededSpace := VAL ( s . Length , M2LONGINT ) + 2 
    ; WHILE MemorySpaceLeft < NeededSpace 
      DO OldMemorySize := MemorySize 
      ; ExtendArray 
          ( LOOPHOLE ( MemoryPtr , ADDRESS ) , MemorySize , BYTESIZE ( CHAR ) ) 
      ; INC ( MemorySpaceLeft , MemorySize - OldMemorySize ) 
      END (* WHILE *) 
    ; StartPtr := MemoryFreePtr 
    ; MemoryPtr ^ [ MemoryFreePtr ] := VAL ( s . Length DIV 256 , CHAR ) 
    ; INC ( MemoryFreePtr ) 
    ; MemoryPtr ^ [ MemoryFreePtr ] := VAL ( s . Length MOD 256 , CHAR ) 
    ; INC ( MemoryFreePtr ) 
    ; FOR i := 1 TO s . Length 
      DO MemoryPtr ^ [ MemoryFreePtr ] := s . Chars [ i ] 
      ; INC ( MemoryFreePtr ) 
      END (* FOR *) 
    ; DEC ( MemorySpaceLeft , NeededSpace ) 
    ; RETURN StartPtr 
    END PutString 

; PROCEDURE GetString ( r : tStringRef ; VAR s : tString ) 

  = BEGIN (* GetString *) 
      s . Length := VAL ( Length ( r ) , tStringIndex ) 
    ; INC ( r , 2 ) 
    ; FOR i := 1 TO s . Length 
      DO s . Chars [ i ] := MemoryPtr ^ [ r ] 
      ; INC ( r ) 
      END (* FOR *) 
    END GetString 

; PROCEDURE Length ( r : tStringRef ) : Word . T 

  = BEGIN (* Length *) 
      RETURN 
        ( ORD ( MemoryPtr ^ [ r ] ) * 256 ) + ORD ( MemoryPtr ^ [ r + 1 ] ) 
    END Length 

; PROCEDURE IsEqual ( r : tStringRef ; READONLY s : tString ) : BOOLEAN 

  = BEGIN (* IsEqual *) 
      INC ( r , 2 ) 
    ; FOR i := 1 TO s . Length 
      DO IF MemoryPtr ^ [ r ] # s . Chars [ i ] 
         THEN 
           RETURN FALSE 
         END (* IF *) 
      ; INC ( r ) 
      END (* FOR *) 
    ; RETURN TRUE 
    END IsEqual 

; PROCEDURE WriteString ( f : tFile ; r : tStringRef ) 

  = BEGIN (* WriteString *) 
      FOR i := r + 2 TO r + 1 + Length ( r ) 
      DO WriteC ( f , MemoryPtr ^ [ i ] ) 
      END (* FOR *) 
    END WriteString 

; PROCEDURE WriteStringMemory ( ) 

  = VAR StringPtr : M2LONGINT 
    ; sLength : M2LONGINT 

  ; BEGIN (* WriteStringMemory *) 
      StringPtr := 0 
    ; WHILE StringPtr < MemoryFreePtr 
      DO WriteI ( StdOutput , VAL ( StringPtr , INTEGER ) , 5 ) 
      ; WriteC ( StdOutput , ' ' ) 
      ; WriteString ( StdOutput , StringPtr ) 
      ; WriteNl ( StdOutput ) 
      ; sLength := VAL ( Length ( StringPtr ) + 2 , M2LONGINT ) (* damned MODULA *) 
      ; INC ( StringPtr , sLength ) 
      END (* WHILE *) 
    ; WriteNl ( StdOutput ) 
    ; WriteI ( StdOutput , VAL ( StringPtr , INTEGER ) , 5 ) 
    ; WriteS 
        ( StdOutput 
        , ARRAY [ 0 .. 6 ] OF CHAR 
            { ' ' , 'B' , 'y' , 't' , 'e' , 's' , '\000' } 
        ) 
    ; WriteNl ( StdOutput ) 
    END WriteStringMemory 

; PROCEDURE InitStringMemory ( ) 

  = BEGIN (* InitStringMemory *) 
      MemorySpaceLeft := MemorySize 
    ; MemoryFreePtr := 0 
    END InitStringMemory 

; BEGIN (* StringMem *) 
    MemorySize := InitialMemorySize 
  ; MakeArray 
      ( LOOPHOLE ( MemoryPtr , ADDRESS ) , MemorySize , BYTESIZE ( CHAR ) ) 
  ; InitStringMemory ( ) 
  END StringMem 
. 

