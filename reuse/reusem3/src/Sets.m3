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
      WITH With_26 = Set 
      DO With_26 . MaxElmt := 0 
      ; With_26 . LastBitset := 0 
      ; With_26 . Card := 0 
      ; With_26 . FirstElmt := 0 
      ; With_26 . LastElmt := 0 
      ; With_26 . BitsetPtr := NIL 
      END (* WITH Set *) 
    END InitNullSet 

; PROCEDURE MakeSet ( VAR Set : tSet ; MaxElement : tElement ) 

  = VAR BitsetCount : M2LONGINT 

  ; BEGIN (* MakeSet *) 
      WITH With_27 = Set 
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
          ( LOOPHOLE ( With_27 . BitsetPtr , ADDRESS ) 
          , BitsetCount 
          , BytesPerBitset 
          ) 
      ; With_27 . MaxElmt := VAL ( MaxElement , tInternalElmt ) 
      ; With_27 . LastBitset := VAL ( BitsetCount - 1 , SHORTCARD ) 
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
      WITH With_28 = Set1 
      DO i := 0 
      ; WHILE i <= With_28 . LastBitset 
        DO With_28 . BitsetPtr ^ [ i ] 
             := With_28 . BitsetPtr ^ [ i ] + Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; With_28 . Card := VAL ( NoCard , tInternalElmt ) 
      ; With_28 . FirstElmt 
          := MinSHORTCARD ( With_28 . FirstElmt , Set2 . FirstElmt ) 
      ; With_28 . LastElmt 
          := MaxSHORTCARD ( With_28 . LastElmt , Set2 . LastElmt ) 
      END (* WITH *) 
    END Union 

; PROCEDURE Difference ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Difference *) 
      WITH With_29 = Set1 
      DO i := 0 
      ; WHILE i <= With_29 . LastBitset 
        DO With_29 . BitsetPtr ^ [ i ] 
             := With_29 . BitsetPtr ^ [ i ] - Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; With_29 . Card := VAL ( NoCard , tInternalElmt ) 
      END (* WITH *) 
    END Difference 

; PROCEDURE Intersection ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Intersection *) 
      WITH With_30 = Set1 
      DO i := 0 
      ; WHILE i <= With_30 . LastBitset 
        DO With_30 . BitsetPtr ^ [ i ] 
             := With_30 . BitsetPtr ^ [ i ] * Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; With_30 . Card := VAL ( NoCard , tInternalElmt ) 
      ; With_30 . FirstElmt 
          := MaxSHORTCARD ( With_30 . FirstElmt , Set2 . FirstElmt ) 
      ; With_30 . LastElmt 
          := MinSHORTCARD ( With_30 . LastElmt , Set2 . LastElmt ) 
      END (* WITH *) 
    END Intersection 

; PROCEDURE SymDiff ( VAR Set1 : tSet ; Set2 : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* SymDiff *) 
      WITH With_31 = Set1 
      DO i := 0 
      ; WHILE i <= With_31 . LastBitset 
        DO With_31 . BitsetPtr ^ [ i ] 
             := With_31 . BitsetPtr ^ [ i ] / Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; With_31 . Card := VAL ( NoCard , tInternalElmt ) 
      ; With_31 . FirstElmt 
          := MinSHORTCARD ( With_31 . FirstElmt , Set2 . FirstElmt ) 
      ; With_31 . LastElmt 
          := MaxSHORTCARD ( With_31 . LastElmt , Set2 . LastElmt ) 
      END (* WITH *) 
    END SymDiff 

; PROCEDURE Complement ( VAR Set : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* Complement *) 
      WITH With_32 = Set 
      DO i := 0 
      ; WHILE i < With_32 . LastBitset 
        DO With_32 . BitsetPtr ^ [ i ] 
             := AllBits - With_32 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 

      (* if MOCKA or WRL *) 

      ; With_32 . BitsetPtr ^ [ With_32 . LastBitset ] 
          := BITSET { 0 .. With_32 . MaxElmt MOD BitsPerBitset } 
             - With_32 . BitsetPtr ^ [ With_32 . LastBitset ] 

      (* else 
         s := {}; 
         FOR i := 0 TO VAL ( SHORTCARD , MaxElmt MOD BitsPerBitset ) DO 
            INCL (s, SHORTCARD (i)); 
         END; 
         BitsetPtr^[LastBitset] := s - BitsetPtr^[LastBitset]; 
         endif *) 

      ; IF With_32 . Card # VAL ( NoCard , tInternalElmt ) 
        THEN 
          With_32 . Card := With_32 . MaxElmt + 1 - With_32 . Card 
        END (* IF *) 
      ; With_32 . FirstElmt := 0 
      ; With_32 . LastElmt := With_32 . MaxElmt 
      END (* WITH *) 
    END Complement 

; PROCEDURE Include ( VAR Set : tSet ; Elmt : tElement ) 

  = BEGIN (* Include *) 
      WITH With_33 = Set 
      DO WITH 
           WBitset 
           = With_33 . BitsetPtr ^ 
               [ VAL ( Elmt DIV BitsPerBitset , SHORTCARD ) ] 
         DO WBitset := WBitset + BITSET { Elmt MOD BitsPerBitset } 
         END (* WITH *) 

      (* FirstElmt := Min (FirstElmt, Elmt); 
         LastElmt  := Max (LastElmt, Elmt); *) 

      ; IF With_33 . FirstElmt > VAL ( Elmt , tInternalElmt ) 
        THEN 
          With_33 . FirstElmt := VAL ( Elmt , tInternalElmt ) 
        END (* IF *) 
      ; IF With_33 . LastElmt < VAL ( Elmt , tInternalElmt ) 
        THEN 
          With_33 . LastElmt := VAL ( Elmt , tInternalElmt ) 
        END (* IF *) 
      END (* WITH *) 
    END Include 

; PROCEDURE Exclude ( VAR Set : tSet ; Elmt : tElement ) 

  = BEGIN (* Exclude *) 
      WITH With_34 = Set 
      DO WITH 
           WBitset 
           = With_34 . BitsetPtr ^ 
               [ VAL ( Elmt DIV BitsPerBitset , SHORTCARD ) ] 
         DO WBitset := WBitset - BITSET { Elmt MOD BitsPerBitset } 
         END (* WITH *) 
      ; With_34 . Card := VAL ( NoCard , tInternalElmt ) 
      ; IF ( VAL ( Elmt , tInternalElmt ) = With_34 . FirstElmt ) 
           AND ( VAL ( Elmt , tInternalElmt ) < With_34 . MaxElmt ) 
        THEN 
          INC ( With_34 . FirstElmt ) 
        END (* IF *) 
      ; IF ( VAL ( Elmt , tInternalElmt ) = With_34 . LastElmt ) 
           AND ( Elmt > 0 ) 
        THEN 
          DEC ( With_34 . LastElmt ) 
        END (* IF *) 
      END (* WITH *) 
    END Exclude 

; PROCEDURE Card ( VAR Set : tSet ) : tElement 

  = BEGIN (* Card *) 
      WITH With_35 = Set 
      DO IF With_35 . Card = VAL ( NoCard , tInternalElmt ) 
         THEN 
           With_35 . Card := 0 
         ; FOR i := With_35 . FirstElmt TO With_35 . LastElmt 
           DO IF IsElement ( VAL ( i , tElement ) , Set ) 
              THEN 
                INC ( With_35 . Card ) 
              END (* IF *) 
           END (* FOR *) 
         END (* IF *) 
      ; RETURN VAL ( With_35 . Card , tElement ) 
      END (* WITH *) 
    END Card 

; PROCEDURE Size ( VAR Set : tSet ) : tElement 

  = BEGIN (* Size *) 
      RETURN VAL ( Set . MaxElmt , tElement ) 
    END Size 

; PROCEDURE Minimum ( VAR Set : tSet ) : tElement 

  = VAR i : tInternalElmt 

  ; BEGIN (* Minimum *) 
      WITH With_36 = Set 
      DO i := With_36 . FirstElmt 
      ; WHILE i <= With_36 . LastElmt 
        DO IF IsElement ( VAL ( i , tElement ) , Set ) 
           THEN 
             With_36 . FirstElmt := i 
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
      WITH With_37 = Set 
      DO i := With_37 . LastElmt 
      ; WHILE i >= With_37 . FirstElmt 
        DO IF IsElement ( VAL ( i , tElement ) , Set ) 
           THEN 
             With_37 . LastElmt := i 
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
      WITH With_38 = Set1 
      DO i := 0 
      ; WHILE i <= With_38 . LastBitset 
        DO IF NOT ( With_38 . BitsetPtr ^ [ i ] <= Set2 . BitsetPtr ^ [ i ] ) 
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
      WITH With_39 = Set1 
      DO i := 0 
      ; WHILE i <= With_39 . LastBitset 
        DO IF With_39 . BitsetPtr ^ [ i ] # Set2 . BitsetPtr ^ [ i ] 
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
      WITH With_40 = Set 
      DO IF With_40 . FirstElmt <= With_40 . LastElmt 
         THEN 
           i := 0 
         ; WHILE i <= With_40 . LastBitset 
           DO b := With_40 . BitsetPtr ^ [ i ] 
           ; IF With_40 . BitsetPtr ^ [ i ] # BITSET { } 
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
      WITH With_41 = Set 
      DO FOR i := With_41 . FirstElmt TO With_41 . LastElmt 
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
      WITH With_42 = Set 
      DO FOR i := With_42 . FirstElmt TO With_42 . LastElmt 
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
      WITH With_43 = Set 
      DO n := 0 
      ; FOR i := With_43 . FirstElmt TO With_43 . LastElmt 
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
      WITH With_44 = Set1 
      DO i := 0 
      ; WHILE i <= With_44 . LastBitset 
        DO With_44 . BitsetPtr ^ [ i ] := Set2 . BitsetPtr ^ [ i ] 
        ; INC ( i ) 
        END (* WHILE *) 
      ; With_44 . Card := Set2 . Card 
      ; With_44 . FirstElmt := Set2 . FirstElmt 
      ; With_44 . LastElmt := Set2 . LastElmt 
      END (* WITH *) 
    END Assign 

; PROCEDURE AssignElmt ( VAR Set : tSet ; Elmt : tElement ) 

  = BEGIN (* AssignElmt *) 
      WITH With_45 = Set 
      DO AssignEmpty ( Set ) 
      ; Include ( Set , Elmt ) 
      ; With_45 . Card := 1 
      ; With_45 . FirstElmt := VAL ( Elmt , tInternalElmt ) 
      ; With_45 . LastElmt := VAL ( Elmt , tInternalElmt ) 
      END (* WITH *) 
    END AssignElmt 

; PROCEDURE AssignEmpty ( VAR Set : tSet ) 

  = VAR i : SHORTCARD 

  ; BEGIN (* AssignEmpty *) 
      WITH With_46 = Set 
      DO i := 0 
      ; WHILE i <= With_46 . LastBitset 
        DO With_46 . BitsetPtr ^ [ i ] := BITSET { } 
        ; INC ( i ) 
        END (* WHILE *) 
      ; With_46 . Card := 0 
      ; With_46 . FirstElmt := With_46 . MaxElmt 
      ; With_46 . LastElmt := 0 
      END (* WITH *) 
    END AssignEmpty 

; PROCEDURE ForallDo ( Set : tSet ; Proc : ProcOftElement ) 

  = BEGIN (* ForallDo *) 
      WITH With_47 = Set 
      DO IF With_47 . BitsetPtr # NIL 
         THEN 
           FOR i := With_47 . FirstElmt TO With_47 . LastElmt 
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
      WITH <*UNUSED*> With_48 = Set 
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


