
(* RMB July 98 Documentation/name changes. *) 

(* RMB 97/06/05 Changed ForAllDo and IsElement to not choke on NIL 
                BitsetPtr, since some tree dumps call 
                WriteSet for sets which are not in use and need 
                no allocated array. *) 

(* RMB 97/06/05 Added InitNullSet, since some tree dumps call 
                WriteSet for sets which are not in use and need 
                no allocated array. *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE Sets 

; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT SHORTCARD , BITSET 

; FROM General IMPORT MinSHORTCARD , MaxSHORTCARD 

; FROM DynArray IMPORT MakeArray , ReleaseArray 

; FROM ReuseIO 
  IMPORT tFile , StdError , ReadCard , ReadC , WriteCard , WriteC , WriteT  
  , WriteNl 

; CONST BitsPerBitset = BITSIZE ( BITSET ) 
  ; BitsPerByte = 8 
  ; BytesPerBitset = BitsPerBitset DIV BitsPerByte 
  ; NoCard = LAST ( tInternalElmt ) 

; VAR AllBits : BITSET 

; PROCEDURE InitNullSet ( VAR Set : tSet ) 

  = BEGIN (* InitNullSet *) 
      WITH m2tom3_with_26 = Set 
      DO m2tom3_with_26 . MaxElmt := 0 
      ; m2tom3_with_26 . LastBitset := 0 
      ; m2tom3_with_26 . Card := 0 
      ; m2tom3_with_26 . FirstElmt := 0 
      ; m2tom3_with_26 . LastElmt := 0 
      ; m2tom3_with_26 . BitsetPtr := NIL 
      END (* WITH Set *) 
    END InitNullSet 

; PROCEDURE MakeSet ( VAR Set : tSet ; MaxElement : tElement ) 

  = VAR BitsetCount : M2LONGINT 

  ; BEGIN (* MakeSet *) 
      WITH m2tom3_with_27 = Set 
      DO BitsetCount 
           := VAL 
                ( ( MaxElement 
                    + BitsPerBitset 
                    - ( MaxElement MOD BitsPerBitset ) 
                  ) 
                  DIV BitsPerBitset 
                , M2LONGINT 
                ) 
      ; MakeArray 
          ( LOOPHOLE ( m2tom3_with_27 . BitsetPtr , ADDRESS ) 
          , BitsetCount 
          , BytesPerBitset 
          ) 
      ; m2tom3_with_27 . MaxElmt := VAL ( MaxElement , tInternalElmt ) 
      ; m2tom3_with_27 . LastBitset := VAL ( BitsetCount - 1 , SHORTCARD ) 
      ; AssignEmpty ( Set ) 
      END (* WITH *) 
    END MakeSet 

; PROCEDURE ReleaseSet ( VAR Set : tSet ) 

  = VAR BitsetCount : M2LONGINT 

  ; BEGIN (* ReleaseSet *) 
      BitsetCount := VAL ( Set . LastBitset + 1 , M2LONGINT ) 
    ; ReleaseArray ( Set . BitsetPtr , BitsetCount , BytesPerBitset ) 
    ; InitNullSet ( Set ) 
    END ReleaseSet 

; PROCEDURE Union ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Union *) 
      WITH m2tom3_with_28 = Set1 
      DO i := 0 
      ; WHILE i <= m2tom3_with_28 . LastBitset 
        DO m2tom3_with_28 . BitsetPtr ^ [ i ] 
             := m2tom3_with_28 . BitsetPtr ^ [ i ] + Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; m2tom3_with_28 . Card := VAL ( NoCard , tInternalElmt ) 
      ; m2tom3_with_28 . FirstElmt 
          := MinSHORTCARD ( m2tom3_with_28 . FirstElmt , Set2 . FirstElmt ) 
      ; m2tom3_with_28 . LastElmt 
          := MaxSHORTCARD ( m2tom3_with_28 . LastElmt , Set2 . LastElmt ) 
      END (* WITH *) 
    END Union 

; PROCEDURE Difference ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Difference *) 
      WITH m2tom3_with_29 = Set1 
      DO i := 0 
      ; WHILE i <= m2tom3_with_29 . LastBitset 
        DO m2tom3_with_29 . BitsetPtr ^ [ i ] 
             := m2tom3_with_29 . BitsetPtr ^ [ i ] - Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; m2tom3_with_29 . Card := VAL ( NoCard , tInternalElmt ) 
      END (* WITH *) 
    END Difference 

; PROCEDURE Intersection ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Intersection *) 
      WITH m2tom3_with_30 = Set1 
      DO i := 0 
      ; WHILE i <= m2tom3_with_30 . LastBitset 
        DO m2tom3_with_30 . BitsetPtr ^ [ i ] 
             := m2tom3_with_30 . BitsetPtr ^ [ i ] * Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; m2tom3_with_30 . Card := VAL ( NoCard , tInternalElmt ) 
      ; m2tom3_with_30 . FirstElmt 
          := MaxSHORTCARD ( m2tom3_with_30 . FirstElmt , Set2 . FirstElmt ) 
      ; m2tom3_with_30 . LastElmt 
          := MinSHORTCARD ( m2tom3_with_30 . LastElmt , Set2 . LastElmt ) 
      END (* WITH *) 
    END Intersection 

; PROCEDURE SymDiff ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* SymDiff *) 
      WITH m2tom3_with_31 = Set1 
      DO i := 0 
      ; WHILE i <= m2tom3_with_31 . LastBitset 
        DO m2tom3_with_31 . BitsetPtr ^ [ i ] 
             := m2tom3_with_31 . BitsetPtr ^ [ i ] / Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; m2tom3_with_31 . Card := VAL ( NoCard , tInternalElmt ) 
      ; m2tom3_with_31 . FirstElmt 
          := MinSHORTCARD ( m2tom3_with_31 . FirstElmt , Set2 . FirstElmt ) 
      ; m2tom3_with_31 . LastElmt 
          := MaxSHORTCARD ( m2tom3_with_31 . LastElmt , Set2 . LastElmt ) 
      END (* WITH *) 
    END SymDiff 

; PROCEDURE Complement ( VAR Set : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Complement *) 
      WITH m2tom3_with_32 = Set 
      DO i := 0 
      ; WHILE i < m2tom3_with_32 . LastBitset 
        DO m2tom3_with_32 . BitsetPtr ^ [ i ] 
             := AllBits - m2tom3_with_32 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 

      (* if MOCKA or WRL *) 

      ; m2tom3_with_32 . BitsetPtr ^ [ m2tom3_with_32 . LastBitset ] 
          := BITSET { 0 .. m2tom3_with_32 . MaxElmt MOD BitsPerBitset } 
             - m2tom3_with_32 . BitsetPtr ^ [ m2tom3_with_32 . LastBitset ] 

      (* else 
         s := {}; 
         FOR i := 0 TO VAL ( SHORTCARD , MaxElmt MOD BitsPerBitset ) DO 
            INCL (s, SHORTCARD (i)); 
         END; 
         BitsetPtr^[LastBitset] := s - BitsetPtr^[LastBitset]; 
         endif *) 

      ; IF m2tom3_with_32 . Card # VAL ( NoCard , tInternalElmt ) 
        THEN 
          m2tom3_with_32 . Card 
            := m2tom3_with_32 . MaxElmt + 1 - m2tom3_with_32 . Card 
        END (* IF *) 
      ; m2tom3_with_32 . FirstElmt := 0 
      ; m2tom3_with_32 . LastElmt := m2tom3_with_32 . MaxElmt 
      END (* WITH *) 
    END Complement 

; PROCEDURE Include ( VAR Set : tSet ; Elmt : tElement ) 

  = BEGIN (* Include *) 
      WITH m2tom3_with_33 = Set 
      DO WITH 
           WBitset 
           = m2tom3_with_33 . BitsetPtr ^ 
               [ VAL ( Elmt DIV BitsPerBitset , SHORTCARD ) ] 
         DO WBitset := WBitset + BITSET { Elmt MOD BitsPerBitset } 
         END (* WITH *) 

      (* FirstElmt := Min (FirstElmt, Elmt); 
         LastElmt  := Max (LastElmt, Elmt); *) 

      ; IF m2tom3_with_33 . FirstElmt > VAL ( Elmt , tInternalElmt ) 
        THEN 
          m2tom3_with_33 . FirstElmt := VAL ( Elmt , tInternalElmt ) 
        END (* IF *) 
      ; IF m2tom3_with_33 . LastElmt < VAL ( Elmt , tInternalElmt ) 
        THEN 
          m2tom3_with_33 . LastElmt := VAL ( Elmt , tInternalElmt ) 
        END (* IF *) 
      END (* WITH *) 
    END Include 

; PROCEDURE Exclude ( VAR Set : tSet ; Elmt : tElement ) 

  = BEGIN (* Exclude *) 
      WITH m2tom3_with_34 = Set 
      DO WITH 
           WBitset 
           = m2tom3_with_34 . BitsetPtr ^ 
               [ VAL ( Elmt DIV BitsPerBitset , SHORTCARD ) ] 
         DO WBitset := WBitset - BITSET { Elmt MOD BitsPerBitset } 
         END (* WITH *) 
      ; m2tom3_with_34 . Card := VAL ( NoCard , tInternalElmt ) 
      ; IF ( VAL ( Elmt , tInternalElmt ) = m2tom3_with_34 . FirstElmt ) 
           AND ( VAL ( Elmt , tInternalElmt ) < m2tom3_with_34 . MaxElmt ) 
        THEN 
          INC ( m2tom3_with_34 . FirstElmt ) 
        END (* IF *) 
      ; IF ( VAL ( Elmt , tInternalElmt ) = m2tom3_with_34 . LastElmt ) 
           AND ( Elmt > 0 ) 
        THEN 
          DEC ( m2tom3_with_34 . LastElmt ) 
        END (* IF *) 
      END (* WITH *) 
    END Exclude 

; PROCEDURE Card ( VAR Set : tSet ) : tElement 

  = BEGIN (* Card *) 
      WITH m2tom3_with_35 = Set 
      DO IF m2tom3_with_35 . Card = VAL ( NoCard , tInternalElmt ) 
         THEN 
           m2tom3_with_35 . Card := 0 
         ; FOR i := m2tom3_with_35 . FirstElmt TO m2tom3_with_35 . LastElmt 
           DO IF IsElement ( VAL ( i , tElement ) , Set ) 
              THEN 
                INC ( m2tom3_with_35 . Card ) 
              END (* IF *) 
           END (* FOR *) 
         END (* IF *) 
      ; RETURN VAL ( m2tom3_with_35 . Card , tElement ) 
      END (* WITH *) 
    END Card 

; PROCEDURE Size ( VAR Set : tSet ) : tElement 

  = BEGIN (* Size *) 
      RETURN VAL ( Set . MaxElmt , tElement ) 
    END Size 

; PROCEDURE Minimum ( VAR Set : tSet ) : tElement 

  = VAR i : tInternalElmt 

  ; BEGIN (* Minimum *) 
      WITH m2tom3_with_36 = Set 
      DO i := m2tom3_with_36 . FirstElmt 
      ; WHILE i <= m2tom3_with_36 . LastElmt 
        DO IF IsElement ( VAL ( i , tElement ) , Set ) 
           THEN 
             m2tom3_with_36 . FirstElmt := i 
           ; RETURN VAL ( i , tElement ) 
           END (* IF *) 
        ; INC ( i ) 
        END (* WHILE *) 
      ; RETURN 0 
      END (* WITH *) 
    END Minimum 

; PROCEDURE Maximum ( VAR Set : tSet ) : tElement 

  = VAR i : tInternalElmt 

  ; BEGIN (* Maximum *) 
      WITH m2tom3_with_37 = Set 
      DO i := m2tom3_with_37 . LastElmt 
      ; WHILE i >= m2tom3_with_37 . FirstElmt 
        DO IF IsElement ( VAL ( i , tElement ) , Set ) 
           THEN 
             m2tom3_with_37 . LastElmt := i 
           ; RETURN VAL ( i , tElement ) 
           END (* IF *) 
        ; DEC ( i ) 
        END (* WHILE *) 
      ; RETURN 0 
      END (* WITH *) 
    END Maximum 

; PROCEDURE Select ( VAR Set : tSet ) : tElement 

  = BEGIN (* Select *) 
      RETURN Minimum ( Set ) 
    END Select 

; PROCEDURE Extract ( VAR Set : tSet ) : tElement 

  = VAR i : tElement 

  ; BEGIN (* Extract *) 
      i := Minimum ( Set ) 
    ; Exclude ( Set , i ) 
    ; RETURN i 
    END Extract 

; PROCEDURE IsSubset ( Set1 , Set2 : tSet ) : BOOLEAN 

  = VAR i : SHORTCARD 

  ; BEGIN (* IsSubset *) 
      WITH m2tom3_with_38 = Set1 
      DO i := 0 
      ; WHILE i <= m2tom3_with_38 . LastBitset 
        DO IF NOT ( m2tom3_with_38 . BitsetPtr ^ [ i ] 
                    <= Set2 . BitsetPtr ^ [ i ] 
                  ) 
           THEN 
             RETURN FALSE 
           END (* IF *) 
        ; INC ( i ) 
        END (* WHILE *) 
      ; RETURN TRUE 
      END (* WITH *) 
    END IsSubset 

; PROCEDURE IsStrictSubset ( Set1 , Set2 : tSet ) : BOOLEAN 

  = BEGIN (* IsStrictSubset *) 
      RETURN IsSubset ( Set1 , Set2 ) AND IsNotEqual ( Set1 , Set2 ) 
    END IsStrictSubset 

; PROCEDURE IsEqual ( VAR Set1 , Set2 : tSet ) : BOOLEAN 

  = VAR i : SHORTCARD 

  ; BEGIN (* IsEqual *) 
      WITH m2tom3_with_39 = Set1 
      DO i := 0 
      ; WHILE i <= m2tom3_with_39 . LastBitset 
        DO IF m2tom3_with_39 . BitsetPtr ^ [ i ] # Set2 . BitsetPtr ^ [ i ] 
           THEN 
             RETURN FALSE 
           END (* IF *) 
        ; INC ( i ) 
        END (* WHILE *) 
      ; RETURN TRUE 
      END (* WITH *) 
    END IsEqual 

; PROCEDURE IsNotEqual ( Set1 , Set2 : tSet ) : BOOLEAN 

  = BEGIN (* IsNotEqual *) 
      RETURN NOT IsEqual ( Set1 , Set2 ) 
    END IsNotEqual 

; PROCEDURE IsElement ( Elmt : tElement ; VAR Set : tSet ) : BOOLEAN 

  = BEGIN (* IsElement *) 
      IF Set . BitsetPtr = NIL 
      THEN 
        RETURN FALSE 
      ELSE 
        RETURN 
          ( Elmt MOD BitsPerBitset ) 
          IN Set . BitsetPtr ^ [ VAL ( Elmt DIV BitsPerBitset , SHORTCARD ) ] 
      END (* IF *) 
    END IsElement 

; PROCEDURE IsEmpty ( Set : tSet ) : BOOLEAN 

  = VAR i : SHORTCARD 
  ; VAR b : BITSET 

  ; BEGIN (* IsEmpty *) 
      WITH m2tom3_with_40 = Set 
      DO IF m2tom3_with_40 . FirstElmt <= m2tom3_with_40 . LastElmt 
         THEN 
           i := 0 
         ; WHILE i <= m2tom3_with_40 . LastBitset 
           DO b := m2tom3_with_40 . BitsetPtr ^ [ i ] 
           ; IF m2tom3_with_40 . BitsetPtr ^ [ i ] # BITSET { } 
             THEN 
               RETURN FALSE 
             END (* IF *) 
           ; INC ( i ) 
           END (* WHILE *) 
         END (* IF *) 
      ; RETURN TRUE 
      END (* WITH *) 
    END IsEmpty 

; PROCEDURE Forall ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

  = BEGIN (* Forall *) 
      WITH m2tom3_with_41 = Set 
      DO FOR i := m2tom3_with_41 . FirstElmt TO m2tom3_with_41 . LastElmt 
         DO IF IsElement ( VAL ( i , tElement ) , Set ) 
               AND ( NOT Proc ( VAL ( i , tElement ) ) ) 
            THEN 
              RETURN FALSE 
            END (* IF *) 
         END (* FOR *) 
      ; RETURN TRUE 
      END (* WITH *) 
    END Forall 

; PROCEDURE Exists ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

  = BEGIN (* Exists *) 
      WITH m2tom3_with_42 = Set 
      DO FOR i := m2tom3_with_42 . FirstElmt TO m2tom3_with_42 . LastElmt 
         DO IF IsElement ( VAL ( i , tElement ) , Set ) 
               AND Proc ( VAL ( i , tElement ) ) 
            THEN 
              RETURN TRUE 
            END (* IF *) 
         END (* FOR *) 
      ; RETURN FALSE 
      END (* WITH *) 
    END Exists 

; PROCEDURE Exists1 ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

  = VAR n : tInternalElmt 

  ; BEGIN (* Exists1 *) 
      WITH m2tom3_with_43 = Set 
      DO n := 0 
      ; FOR i := m2tom3_with_43 . FirstElmt TO m2tom3_with_43 . LastElmt 
        DO IF IsElement ( VAL ( i , tElement ) , Set ) 
              AND Proc ( VAL ( i , tElement ) ) 
           THEN 
             INC ( n ) 
           END (* IF *) 
        END (* FOR *) 
      ; RETURN n = 1 
      END (* WITH *) 
    END Exists1 

; PROCEDURE Assign ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Assign *) 
      WITH m2tom3_with_44 = Set1 
      DO i := 0 
      ; WHILE i <= m2tom3_with_44 . LastBitset 
        DO m2tom3_with_44 . BitsetPtr ^ [ i ] := Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; m2tom3_with_44 . Card := Set2 . Card 
      ; m2tom3_with_44 . FirstElmt := Set2 . FirstElmt 
      ; m2tom3_with_44 . LastElmt := Set2 . LastElmt 
      END (* WITH *) 
    END Assign 

; PROCEDURE AssignElmt ( VAR Set : tSet ; Elmt : tElement ) 

  = BEGIN (* AssignElmt *) 
      WITH m2tom3_with_45 = Set 
      DO AssignEmpty ( Set ) 
      ; Include ( Set , Elmt ) 
      ; m2tom3_with_45 . Card := 1 
      ; m2tom3_with_45 . FirstElmt := VAL ( Elmt , tInternalElmt ) 
      ; m2tom3_with_45 . LastElmt := VAL ( Elmt , tInternalElmt ) 
      END (* WITH *) 
    END AssignElmt 

; PROCEDURE AssignEmpty ( VAR Set : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* AssignEmpty *) 
      WITH m2tom3_with_46 = Set 
      DO i := 0 
      ; WHILE i <= m2tom3_with_46 . LastBitset 
        DO m2tom3_with_46 . BitsetPtr ^ [ i ] := BITSET { } 
        ; INC ( i ) 
        END (* WHILE *) 
      ; m2tom3_with_46 . Card := 0 
      ; m2tom3_with_46 . FirstElmt := m2tom3_with_46 . MaxElmt 
      ; m2tom3_with_46 . LastElmt := 0 
      END (* WITH *) 
    END AssignEmpty 

; PROCEDURE ForallDo ( Set : tSet ; Proc : ProcOftElement ) 

  = BEGIN (* ForallDo *) 
      WITH m2tom3_with_47 = Set 
      DO IF m2tom3_with_47 . BitsetPtr # NIL 
         THEN 
           FOR i := m2tom3_with_47 . FirstElmt TO m2tom3_with_47 . LastElmt 
           DO IF IsElement ( VAL ( i , tElement ) , Set ) 
              THEN 
                Proc ( VAL ( i , tElement ) ) 
              END (* IF *) 
           END (* FOR *) 
         END (* IF *) 
      END (* WITH *) 
    END ForallDo 

; PROCEDURE ReadSet ( f : tFile ; VAR Set : tSet ) 

  = VAR card : tInternalElmt 

  ; BEGIN (* ReadSet *) 
      REPEAT UNTIL ReadC ( f ) = '{' 
    ; AssignEmpty ( Set ) 
    ; card := 0 
    ; LOOP 
        IF ReadC ( f ) = '}' THEN EXIT END (* IF *) 
      ; Include ( Set , ReadCard ( f ) ) 
      ; INC ( card ) 
      END (* LOOP *) 
    ; Set . Card := card 
    END ReadSet 

; VAR g : tFile 

; PROCEDURE WriteSet ( f : tFile ; Set : tSet ) 

  = BEGIN (* WriteSet *) 
      WITH <*UNUSED*> m2tom3_with_48 = Set 
      DO 

      (* WriteT (f, "MaxElmt = "        ) ; WriteCard (f, MaxElmt        , 0); 
         WriteT (f, " LastBitset = "    ) ; WriteCard (f, LastBitset, 0); 
         WriteT (f, " Card = "          ) ; WriteCard (f, Card   , 0); 
         WriteT (f, " FirstElmt = "     ) ; WriteCard (f, FirstElmt , 0); 
         WriteT (f, " LastElmt = "      ) ; WriteCard (f, LastElmt       , 0); 
         WriteNl (f); 
      *) 

        g := f 
      ; WriteC ( f , '{' ) 
      ; ForallDo ( Set , WriteElmt ) 
      ; WriteC ( f , '}' ) 
      END (* WITH *) 
    END WriteSet 

; PROCEDURE WriteElmt ( Elmt : tElement ) 

  = BEGIN (* WriteElmt *) 
      WriteC ( g , ' ' ) 
    ; WriteCard ( g , Elmt , 0 ) 
    END WriteElmt 

; BEGIN (* Sets *) 
    AllBits := BITSET { 0 .. BitsPerBitset - 1 } 
  ; IF BYTESIZE ( BITSET ) # BytesPerBitset 
    THEN 
      WriteT ( StdError , "TSIZE (BITSET) = " ) 
    ; WriteCard ( StdError , BYTESIZE ( BITSET ) , 0 ) 
    ; WriteNl ( StdError ) 
    END (* IF *) 
  END Sets 
. 


