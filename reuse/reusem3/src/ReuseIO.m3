
(* $Id: IO.mi,v 1.9 1992/01/30 13:23:29 grosch rel $ *) 

(* $Log: IO.mi,v $ 
 
 * RMB 93/10/12 Various type conversions, removed VAR on parameter s 
       of WriteS and FileName of ReadOpen and WriteOpen. 
 
 * Revision 1.9  1992/01/30  13:23:29  grosch 
 * redesign of interface to operating system 
 * 
 * Revision 1.8  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.7  91/06/07  12:19:51  grosch 
 * decreased bounds of flexible arrays 
 * 
 * Revision 1.6  91/06/07  11:37:42  grosch 
 * increased bounds of flexible arrays 
 * 
 * Revision 1.5  91/01/16  17:11:13  grosch 
 * fixed range check problem with BytesRead 
 * 
 * Revision 1.4  89/08/18  11:11:48  grosch 
 * make Write work for Size = 0 
 * 
 * Revision 1.3  89/07/14  16:27:15  grosch 
 * made WriteN work for numbers with MSBit set 
 * 
 * Revision 1.2  89/01/25  19:37:28  grosch 
 * tuning: ReadC inline in Read and ReadS, WriteC inline in Write and WriteS 
 * 
 * Revision 1.1  89/01/24  19:04:35  grosch 
 * added procedure UnRead 
 * 
 * Revision 1.0  88/10/04  11:46:58  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

UNSAFE MODULE ReuseIO                   (* buffered IO          *) 

; IMPORT Text 

; FROM SYSTEM IMPORT M2LONGINT , M2LONGCARD 

; FROM SYSTEM IMPORT SHORTINT 

; FROM General IMPORT Exp10 

; FROM Memory IMPORT Alloc , Free 

; IMPORT Word , System 

; CONST EolCh = '\012' 
  ; TabCh = '\011' 
  ; BufferSize = 1024 
  ; MaxInt = 2147483647                 (* 2 ** 31 - 1 *) 
  ; MaxPow10 = 1000000000 
  ; MaxIntDiv10 = MaxInt DIV 10 

; TYPE BufferDescriptor 
    = RECORD 
        Buffer : UNTRACED BRANDED REF ARRAY [ 0 .. BufferSize ] OF CHAR 
      ; BufferIndex : SHORTINT 
      ; BytesRead : SHORTINT 
      ; OpenForOutput : BOOLEAN 
      ; EndOfFile : BOOLEAN 
      ; FlushLine : BOOLEAN
      ; IsIntermittent : BOOLEAN := FALSE (* IMPLIES input file. *) 
      END (* RECORD *) 

   (* INV BufferIndex points before the character to be read next *) 

; VAR BufferPool : ARRAY tFile OF BufferDescriptor 
; VAR MyCHR : ARRAY [ 0 .. 15 ] OF CHAR 

; PROCEDURE FillBuffer ( f : tFile ; MinSize : INTEGER )
  (* Do not block if MinSize bytes can be gotten. *)

  = VAR Size : INTEGER

  ; BEGIN (* FillBuffer *)
      WITH With_8 = BufferPool [ f ] 
      DO
        IF With_8 . FlushLine 
         THEN 
           WriteFlush ( StdOutput ) 
         ; WriteFlush ( StdError ) 
         END (* IF *)
      ; IF With_8 . IsIntermittent
        THEN Size := MIN ( MinSize , BufferSize )
        ELSE Size := BufferSize
        END (* IF *)
      ; With_8 . BufferIndex := 0 
      ; With_8 . BytesRead 
          := VAL 
               ( System . Read 
                   ( f 
                   , ADR ( With_8 . Buffer ^ [ 1 ] ) 
                   , Size 
                   ) 
               , SHORTINT 
               ) 
      ; IF With_8 . BytesRead <= 0 
        THEN 
          With_8 . BytesRead := 0 
        ; With_8 . EndOfFile := TRUE 
        END (* IF *) 
      END (* WITH *) 
    END FillBuffer 

; PROCEDURE ReadOpen ( READONLY FileName : ARRAY OF CHAR ) : tFile 

  = VAR                                         (* open  input file     *) 
      f : tFile 

  ; BEGIN (* ReadOpen *) 
      f := System . OpenInput ( FileName )
    ; IF f >= 0
      THEN 
        WITH With_9 = BufferPool [ f ] 
        DO With_9 . Buffer := Alloc ( BufferSize + 1 ) 
        ; With_9 . BufferIndex := 0 
        ; With_9 . BytesRead := 0 
        ; With_9 . OpenForOutput := FALSE
        ; With_9 . IsIntermittent := System . IsIntermittent ( f ) 
        ; With_9 . EndOfFile := FALSE 
        END (* WITH *)
      ; CheckFlushLine ( f ) 
      END(* IF *)
    ; RETURN f 
    END ReadOpen 

; PROCEDURE ReadOpenT ( READONLY FileName : TEXT ) : tFile 

  = VAR                                         (* open  input file     *) 
      f : tFile 

  ; BEGIN (* ReadOpenT *) 
      f := System . OpenInputT ( FileName )
    ; IF f >= 0
      THEN 
        WITH With_9 = BufferPool [ f ] 
        DO With_9 . Buffer := Alloc ( BufferSize + 1 ) 
        ; With_9 . BufferIndex := 0 
        ; With_9 . BytesRead := 0 
        ; With_9 . OpenForOutput := FALSE
        ; With_9 . IsIntermittent := System . IsIntermittent ( f ) 
        ; With_9 . EndOfFile := FALSE 
        END (* WITH *) 
      ; CheckFlushLine ( f ) 
      END(* IF *)
    ; RETURN f 
    END ReadOpenT 

; PROCEDURE ReadClose ( f : tFile )             (* close input file     *) 

  = BEGIN (* ReadClose *) 
      System . Close ( f ) 
    ; WITH With_10 = BufferPool [ f ] 
      DO Free ( BufferSize + 1 , With_10 . Buffer ) 
      ; With_10 . Buffer := NIL 
      END (* WITH *) 
    END ReadClose 

; PROCEDURE Read ( f : tFile ; Buffer : ADDRESS ; Size : Word . T ) : INTEGER 

  = VAR                                         (* binary               *) 
      BufferPtr : UNTRACED BRANDED REF ARRAY [ 0 .. 100000000 ] OF CHAR 
    ; i : Word . T 

  ; BEGIN (* Read *) 
      BufferPtr := Buffer 
    ; WITH With_11 = BufferPool [ f ] 
      DO i := 0 
      ; LOOP 
          IF i = Size THEN RETURN i END (* IF *) 
        ; IF With_11 . BufferIndex = With_11 . BytesRead 
          THEN 
            FillBuffer ( f , MinSize := Size ) 
          ; IF With_11 . EndOfFile 
            THEN 
              With_11 . Buffer ^ [ 1 ] := '\000' 
            END (* IF *) 
          END (* IF *) 
        ; INC ( With_11 . BufferIndex ) 
        ; BufferPtr ^ [ i ] 
            := With_11 . Buffer ^ [ With_11 . BufferIndex ] 
        ; IF With_11 . EndOfFile THEN RETURN i END (* IF *) 
        ; INC ( i ) 
        END (* LOOP *) 
      END (* WITH *) 
    END Read 

; PROCEDURE ReadC ( f : tFile ) : CHAR          (* character            *) 

  = BEGIN (* ReadC *) 
      WITH With_12 = BufferPool [ f ] 
      DO IF With_12 . BufferIndex = With_12 . BytesRead 
         THEN 
           FillBuffer ( f , MinSize := 1 ) 
         ; IF With_12 . EndOfFile 
           THEN 
             With_12 . Buffer ^ [ 1 ] := '\000' 
           END (* IF *) 
         END (* IF *) 
      ; INC ( With_12 . BufferIndex ) 
      ; RETURN With_12 . Buffer ^ [ With_12 . BufferIndex ] 
      END (* WITH *) 
    END ReadC 

; PROCEDURE ReadI ( f : tFile ) : INTEGER       (* integer  number      *) 

  = VAR n : INTEGER 
    ; ch : CHAR 
    ; negative : BOOLEAN 

  ; BEGIN (* ReadI *)
    (* Scan out leading whitespace. *) 
      REPEAT
        ch := ReadC ( f ) 
      UNTIL ( ch # ' ' ) AND ( ch # TabCh ) AND ( ch # EolCh ) 
    ; CASE ch 
      OF '+' 
      => negative := FALSE 
      ; ch := ReadC ( f ) 
      | '-' 
      => negative := TRUE 
      ; ch := ReadC ( f ) 
      ELSE 
        negative := FALSE 
      END (* CASE *) 
    ; n := 0 
    ; WHILE ( '0' <= ch ) AND ( ch <= '9' ) 
      DO n := ( 10 * n ) + ORD ( ch ) - ORD ( '0' )  
      ; ch := ReadC ( f ) 
      END (* WHILE *) 
    ; DEC ( BufferPool [ f ] . BufferIndex ) 
    ; IF negative THEN RETURN - n ELSE RETURN n END (* IF *) 
    END ReadI 

; PROCEDURE ReadR ( f : tFile ) : REAL          (* real     number      *) 

  = VAR n : REAL 
    ; Mantissa : M2LONGCARD 
    ; Exponent : INTEGER 
    ; MantissaNeg : BOOLEAN 
    ; ExponentNeg : BOOLEAN 
    ; FractionDigits : Word . T 
    ; TruncatedDigits : Word . T 
    ; ch : CHAR 

  ; BEGIN (* ReadR *) 
      MantissaNeg := FALSE 
    ; Mantissa := 0 
    ; Exponent := 0 
    ; FractionDigits := 0 
    ; TruncatedDigits := 0 

    ; REPEAT                                    (* skip white space     *) 
        ch := ReadC ( f ) 
      UNTIL ( ch # ' ' ) AND ( ch # TabCh ) AND ( ch # EolCh ) 

    ; CASE ch                                   (* handle sign          *) 
      OF '+' 
      => ch := ReadC ( f ) 
      | '-' 
      => ch := ReadC ( f ) 
      ; MantissaNeg := TRUE 
      | 'E' 
      => Mantissa := 1 
      ELSE 
      END (* CASE *) 

    ; WHILE ( '0' <= ch ) AND ( ch <= '9' ) 
      DO                                        (* integer part         *) 
         IF Mantissa <= MaxIntDiv10 
         THEN 
           Mantissa := 10 * Mantissa 
         ; IF Mantissa 
              <= VAL ( MaxInt - ( ORD ( ch ) - ORD ( '0' ) ) , M2LONGCARD ) 
           THEN 
             INC ( Mantissa , ORD ( ch ) - ORD ( '0' ) ) 
           ELSE 
             INC ( TruncatedDigits ) 
           END (* IF *) 
         ELSE 
           INC ( TruncatedDigits ) 
         END (* IF *) 
      ; ch := ReadC ( f ) 
      END (* WHILE *) 

    ; IF ch = '.' THEN ch := ReadC ( f ) END (* IF *) 
                                                (* decimal point        *) 

    ; WHILE ( '0' <= ch ) AND ( ch <= '9' ) 
      DO                                        (* fractional part      *) 
         IF Mantissa <= MaxIntDiv10 
         THEN 
           Mantissa := 10 * Mantissa 
         ; IF Mantissa 
              <= VAL ( MaxInt - ( ORD ( ch ) - ORD ( '0' ) ) , M2LONGCARD ) 
           THEN 
             INC ( Mantissa , ORD ( ch ) - ORD ( '0' ) ) 
           ELSE 
             INC ( TruncatedDigits ) 
           END (* IF *) 
         ELSE 
           INC ( TruncatedDigits ) 
         END (* IF *) 
      ; INC ( FractionDigits ) 
      ; ch := ReadC ( f ) 
      END (* WHILE *) 

    ; IF ch = 'E' 
      THEN                                      (* exponent             *) 
        ch := ReadC ( f ) 

      ; CASE ch 
        OF '+' 
        => ExponentNeg := FALSE 
        ; ch := ReadC ( f ) 
        | '-' 
        => ExponentNeg := TRUE 
        ; ch := ReadC ( f ) 
        ELSE 
          ExponentNeg := FALSE 
        END (* CASE *) 

      ; WHILE ( '0' <= ch ) AND ( ch <= '9' ) 
        DO Exponent 
             := ( 10 * Exponent ) 
                + LOOPHOLE ( ORD ( ch ) - ORD ( '0' ) , INTEGER ) 
        ; ch := ReadC ( f ) 
        END (* WHILE *) 

      ; IF ExponentNeg THEN Exponent := - Exponent END (* IF *) 
      END (* IF *) 

    ; DEC ( BufferPool [ f ] . BufferIndex ) 
    ; DEC ( Exponent , FractionDigits - TruncatedDigits ) 
    ; n := FLOAT ( Mantissa ) * Exp10 ( Exponent ) 
    ; IF MantissaNeg THEN RETURN - n ELSE RETURN n END (* IF *) 
    END ReadR 

; PROCEDURE ReadB ( f : tFile ) : BOOLEAN       (* boolean              *) 

  = BEGIN (* ReadB *) 
      RETURN ReadC ( f ) = 'T' 
    END ReadB 

; PROCEDURE ReadN ( f : tFile ; Base : INTEGER ) : INTEGER 

  = VAR                                         (* number of base 'Base'*) 
      n : INTEGER 
    ; ch : CHAR 
    ; digit : INTEGER 

  ; BEGIN (* ReadN *) 
      REPEAT 
        ch := ReadC ( f ) 
      UNTIL ( ch # ' ' ) AND ( ch # TabCh ) AND ( ch # EolCh ) 
    ; n := 0 
    ; LOOP 
        IF ( '0' <= ch ) AND ( ch <= '9' ) 
        THEN 
          digit := ORD ( ch ) - ORD ( '0' ) 
        ELSIF ( 'A' <= ch ) AND ( ch <= 'F' ) 
        THEN 
          digit := ORD ( ch ) - ORD ( 'A' ) + 10 
        ELSE 
          digit := 99 
        END (* IF *) 
      ; IF digit >= Base THEN EXIT END (* IF *) 
      ; n := ( Base * n ) + digit 
      ; ch := ReadC ( f ) 
      END (* LOOP *) 
    ; DEC ( BufferPool [ f ] . BufferIndex ) 
    ; RETURN n 
    END ReadN 

; PROCEDURE ReadS ( f : tFile ; VAR s : ARRAY OF CHAR ) 

  = BEGIN (* ReadS *) 
      WITH With_13 = BufferPool [ f ] 
      DO FOR i := 0 TO LAST ( s ) 
         DO IF With_13 . BufferIndex = With_13 . BytesRead 
            THEN                                                                (* ReadC inline         *) 
              FillBuffer ( f , MinSize := NUMBER ( s ) ) 
            ; IF With_13 . EndOfFile 
              THEN 
                With_13 . Buffer ^ [ 1 ] := '\000' 
              END (* IF *) 
            END (* IF *) 
         ; INC ( With_13 . BufferIndex ) 
         ; s [ i ] 
             := With_13 . Buffer ^ [ With_13 . BufferIndex ] 
         END (* FOR *) 
      END (* WITH *) 
    END ReadS 

; PROCEDURE ReadShort ( f : tFile ) : SHORTINT  (* shortint number      *) 

  = BEGIN (* ReadShort *) 
      RETURN VAL ( ReadI ( f ) , SHORTINT ) 
    END ReadShort 

; PROCEDURE ReadLong ( f : tFile ) : M2LONGINT (* longint  number      *) 

  = BEGIN (* ReadLong *) 
      RETURN VAL ( ReadI ( f ) , M2LONGINT ) 
    END ReadLong 

; PROCEDURE ReadCard ( f : tFile ) : Word . T   (* cardinal number      *) 

  = BEGIN (* ReadCard *) 
      RETURN ReadI ( f ) 
    END ReadCard 

; PROCEDURE ReadNl ( f : tFile )                (* new line             *) 

  = BEGIN (* ReadNl *) 
      REPEAT UNTIL ReadC ( f ) = EolCh 
    END ReadNl 

; PROCEDURE UnRead ( f : tFile )                (* backspace 1 char.    *) 

  = BEGIN (* UnRead *) 
      DEC ( BufferPool [ f ] . BufferIndex ) 
    END UnRead 


; PROCEDURE EndOfLine ( f : tFile ) : BOOLEAN   (* end of line ?        *) 

  = BEGIN (* EndOfLine *) 
      WITH With_14 = BufferPool [ f ] 
      DO IF With_14 . BufferIndex = With_14 . BytesRead 
         THEN 
           FillBuffer ( f , MinSize := 1 ) 
         ; IF With_14 . EndOfFile 
           THEN 
             With_14 . Buffer ^ [ 1 ] := '\000' 
           END (* IF *) 
         END (* IF *) 
      ; RETURN 
          With_14 . Buffer ^ [ With_14 . BufferIndex + 1 ] 
          = EolCh 
      END (* WITH *) 
    END EndOfLine 

; PROCEDURE EndOfFile ( f : tFile ) : BOOLEAN   (* end of file ?        *) 

  = VAR ch : CHAR 

  ; BEGIN (* EndOfFile *) 
      ch := ReadC ( f ) 
    ; DEC ( BufferPool [ f ] . BufferIndex ) 
    ; RETURN BufferPool [ f ] . EndOfFile 
    END EndOfFile 


; PROCEDURE CheckFlushLine ( f : tFile ) 

  = BEGIN (* CheckFlushLine *) 
      BufferPool [ f ] . FlushLine := System . IsCharacterSpecial ( f ) 
    END CheckFlushLine 

; PROCEDURE WriteOpen ( READONLY FileName : ARRAY OF CHAR ) : tFile 

  = VAR                                         (* open  output file    *) 
      f : tFile 

  ; BEGIN (* WriteOpen *) 
      f := System . OpenOutput ( FileName ) 
    ; IF f >= 0
      THEN 
        WITH With_15 = BufferPool [ f ] 
        DO With_15 . Buffer := Alloc ( BufferSize + 1 ) 
        ; With_15 . BufferIndex := 0 
        ; With_15 . OpenForOutput := TRUE 
        END (* WITH *) 
      ; CheckFlushLine ( f ) 
      END(* IF *)
    ; RETURN f 
    END WriteOpen 

; PROCEDURE WriteOpenT ( READONLY FileName : TEXT ) : tFile 

  = VAR                                         (* open  output file    *) 
      f : tFile 

  ; BEGIN (* WriteOpenT *) 
      f := System . OpenOutputT ( FileName ) 
    ; IF f >= 0
      THEN 
        WITH With_15 = BufferPool [ f ] 
        DO With_15 . Buffer := Alloc ( BufferSize + 1 ) 
        ; With_15 . BufferIndex := 0 
        ; With_15 . OpenForOutput := TRUE 
        END (* WITH *) 
      ; CheckFlushLine ( f ) 
      END(* IF *)
    ; RETURN f 
    END WriteOpenT 

; PROCEDURE WriteClose ( f : tFile )            (* close output file    *) 

  = BEGIN (* WriteClose *) 
      WriteFlush ( f ) 
    ; System . Close ( f ) 
    ; WITH With_16 = BufferPool [ f ] 
      DO Free ( BufferSize + 1 , With_16 . Buffer ) 
      ; With_16 . Buffer := NIL 
      END (* WITH *) 
    END WriteClose 

; PROCEDURE WriteFlush ( f : tFile )            (* flush output buffer  *) 

  = BEGIN (* WriteFlush *) 
      WITH With_17 = BufferPool [ f ] 
      DO With_17 . BytesRead 
           := VAL 
                ( System . Write 
                    ( f 
                    , ADR ( With_17 . Buffer ^ [ 1 ] ) 
                    , VAL ( With_17 . BufferIndex , INTEGER ) 
                    ) 
                , SHORTINT 
                ) 
      ; With_17 . BufferIndex := 0 
      END (* WITH *)
    ; System . Flush ( f ) 
    END WriteFlush 

; PROCEDURE Write ( f : tFile ; Buffer : ADDRESS ; Size : INTEGER ) : INTEGER 

  = VAR                                         (* binary               *) 
      BufferPtr : UNTRACED BRANDED REF ARRAY [ 0 .. 100000000 ] OF CHAR 

  ; BEGIN (* Write *) 
      BufferPtr := Buffer 
    ; WITH With_18 = BufferPool [ f ] 
      DO FOR i := 0 TO Size - 1 
         DO INC ( With_18 . BufferIndex ) 
         ; With_18 . Buffer ^ [ With_18 . BufferIndex ] 
             := BufferPtr ^ [ i ] 
         ; IF ( With_18 . BufferIndex = BufferSize ) 
           THEN 
             WriteFlush ( f ) 
           END (* IF *) 
         END (* FOR *) 
      END (* WITH *) 
    ; RETURN Size 
    END Write 

; PROCEDURE WriteC ( f : tFile ; c : CHAR )     (* character            *) 

  = BEGIN (* WriteC *) 
      WITH With_19 = BufferPool [ f ] 
      DO INC ( With_19 . BufferIndex ) 
      ; With_19 . Buffer ^ [ With_19 . BufferIndex ] := c 
      ; IF ( With_19 . BufferIndex = BufferSize ) 
           OR ( With_19 . FlushLine AND ( c = EolCh ) ) 
        THEN 
          WriteFlush ( f ) 
        END (* IF *) 
      END (* WITH *) 
    END WriteC 

; PROCEDURE WriteI ( f : tFile ; n : INTEGER ; FieldWidth : Word . T ) 

  = VAR                                         (* integer  number      *) 
      length : Word . T 
    ; negative : Word . T 
    ; digits : ARRAY [ 0 .. 20 ] OF CHAR 

  ; BEGIN (* WriteI *) 
      IF n < 0 THEN negative := 1 ; n := - n ELSE negative := 0 END (* IF *) 
    ; length := 0 
    ; REPEAT 
        INC ( length ) 
      ; digits [ length ] := MyCHR [ n MOD 10 ] 
      ; n := n DIV 10 
      UNTIL n = 0 
    ; FOR i := 1 TO LOOPHOLE ( FieldWidth - length - negative , INTEGER ) 
      DO WriteC ( f , ' ' ) 
      END (* FOR *) 
    ; IF negative = 1 THEN WriteC ( f , '-' ) END (* IF *) 
    ; FOR i := LOOPHOLE ( length , INTEGER ) TO 1 BY - 1 
      DO WriteC ( f , digits [ i ] ) 
      END (* FOR *) 
    END WriteI 

; PROCEDURE WriteR ( f : tFile ; n : REAL ; Before , After , Exp : Word . T ) 

  = CONST                                       (* real   number        *) 
      StartIndex = 100 

  ; VAR i : Word . T 
    ; FirstDigit : Word . T 
    ; IntegerDigits : Word . T 
    ; TotalDigits : Word . T 
    ; IsNegative : Word . T 
    ; Digits : ARRAY [ 0 .. 200 ] OF Word . T 
    ; MaxCard : REAL 
    ; MaxCardDiv10 : REAL 
    ; Mantissa : M2LONGCARD 
    ; Exponent : INTEGER 

  ; BEGIN (* WriteR *) 
      MaxCard := FLOAT ( MaxInt ) 
    ; MaxCardDiv10 := FLOAT ( MaxIntDiv10 ) 

    ; IF n < 0.0 
      THEN                                      (* determine sign       *) 
        IsNegative := 1 
      ; n := - n 
      ELSE 
        IsNegative := 0 
      END (* IF *) 

    ; IF n = 0.0 
      THEN                      (* determine mantissa and exponent      *) 
        Mantissa := 0 
      ; Exponent := 1 
      ELSE 
        Exponent := 10                          (* normalize mantissa   *) 
      ; WHILE n > MaxCard DO n := n / 10.0 ; INC ( Exponent ) END (* WHILE *) 
      ; WHILE n <= MaxCardDiv10 
        DO n := n * 10.0 
        ; DEC ( Exponent ) 
        END (* WHILE *) 
      ; Mantissa := VAL ( TRUNC ( n ) , M2LONGCARD ) 
      ; IF Mantissa < MaxPow10 THEN DEC ( Exponent ) END (* IF *) 
      END (* IF *) 

                                                (* determine size of:   *) 

    ; IF ( Exp > 0 ) OR ( Exponent <= 0 ) 
      THEN                                      (* integer part         *) 
        IntegerDigits := 1 
      ELSE 
        IntegerDigits := Exponent 
      END (* IF *) 
    ; IF After = 0 THEN After := 1 END (* IF *)  (* fractional part      *) 
    ; TotalDigits := IntegerDigits + After      (* total # of digits    *) 

    ; FirstDigit := StartIndex                  (* convert mantissa     *) 
    ; REPEAT 
        DEC ( FirstDigit ) 
      ; Digits [ FirstDigit ] := Mantissa MOD 10 
      ; Mantissa := Mantissa DIV 10 
      UNTIL Mantissa = 0 
    ; IF Exp = 0 
      THEN                                      (* add leading zeroes   *) 
        FOR j := 1 TO 1 - Exponent 
        DO DEC ( FirstDigit ) 
        ; Digits [ FirstDigit ] := 0 
        END (* FOR *) 
      END (* IF *) 
    ; FOR i := StartIndex TO FirstDigit + TotalDigits 
      DO Digits [ i ] := 0                      (* add trailing zeroes  *) 
      END (* FOR *) 

    ; Digits [ FirstDigit - 1 ] := 0            (* round mantissa       *) 
    ; IF Digits [ FirstDigit + TotalDigits ] >= 5 
      THEN 
        i := FirstDigit + TotalDigits - 1 
      ; WHILE Digits [ i ] = 9 
        DO                                      (* carry                *) 
           Digits [ i ] := 0 
        ; DEC ( i ) 
        END (* WHILE *) 
      ; INC ( Digits [ i ] ) 
      ; IF i = ( FirstDigit - 1 ) 
        THEN (* carry at most significant pos. *) 
          FirstDigit := i 
        ; IF Exp > 0 
          THEN 
            INC ( Exponent ) 
          ELSIF Exponent > 0 
          THEN 
            INC ( IntegerDigits ) 
          END (* IF *) 
        END (* IF *) 
      END (* IF *) 

                                                (* print mantissa       *) 

    ; FOR j := 1 
            TO LOOPHOLE ( Before - IsNegative - IntegerDigits , INTEGER ) 
      DO WriteC ( f , ' ' )                     (* leading spaces       *) 
      END (* FOR *) 
    ; IF IsNegative = 1 THEN WriteC ( f , '-' ) END (* IF *) 
                                                        (* sign         *) 
    ; FOR i := 1 TO IntegerDigits 
      DO                                        (* integer part         *) 
         WriteC ( f , MyCHR [ Digits [ FirstDigit ] ] ) 
      ; INC ( FirstDigit ) 
      END (* FOR *) 
    ; WriteC ( f , '.' )                        (* decimal point        *) 
    ; FOR i := 1 TO After 
      DO                                        (* fractional part      *) 
         WriteC ( f , MyCHR [ Digits [ FirstDigit ] ] ) 
      ; INC ( FirstDigit ) 
      END (* FOR *) 

    ; IF Exp > 0 
      THEN                                      (* print exponent       *) 
        DEC ( Exponent ) 
      ; WriteC ( f , 'E' ) 
      ; IF Exponent < 0 
        THEN 
          WriteC ( f , '-' ) 
        ; Exponent := - Exponent 
        ELSE 
          WriteC ( f , '+' ) 
        END (* IF *) 
      ; WriteN ( f , VAL ( Exponent , M2LONGCARD ) , Exp - 1 , 10 ) 
      END (* IF *) 
    END WriteR 

; PROCEDURE WriteB ( f : tFile ; b : BOOLEAN )          (* boolean              *) 

  = BEGIN (* WriteB *) 
      IF b THEN WriteC ( f , 'T' ) ELSE WriteC ( f , 'F' ) END (* IF *) 
    END WriteB 

; PROCEDURE WriteN ( f : tFile ; n : INTEGER ; FieldWidth , Base : Word . T ) 

  = VAR                                         (* number of base 'Base'*) 
      length : Word . T 
    ; digits : ARRAY [ 0 .. 32 ] OF CHAR 

  ; BEGIN (* WriteN *) 
      length := 0 
    ; REPEAT 
        INC ( length ) 
      ; digits [ length ] := MyCHR [ n MOD Base ] 
      ; n := n DIV Base 
      UNTIL n = 0 
    ; FOR i := 1 TO FieldWidth - length DO WriteC ( f , '0' ) END (* FOR *) 
    ; FOR i := length TO 1 BY - 1 
      DO WriteC ( f , digits [ i ] ) 
      END (* FOR *) 
    END WriteN 

; PROCEDURE WriteS ( f : tFile ; READONLY s : ARRAY OF CHAR ) 

  = VAR c : CHAR 

  ; BEGIN (* WriteS *) 
      WITH With_20 = BufferPool [ f ] 
      DO FOR i := 0 TO LAST ( s ) 
         DO c := s [ i ] 
         ; IF c = '\000' THEN RETURN END (* IF *) 
         ; INC ( With_20 . BufferIndex )                 (* WriteC inline        *) 
         ; With_20 . Buffer ^ [ With_20 . BufferIndex ] := c 
         ; IF ( With_20 . BufferIndex = BufferSize ) 
              OR ( With_20 . FlushLine AND ( c = EolCh ) ) 
           THEN 
             WriteFlush ( f ) 
           END (* IF *) 
         END (* FOR *) 
      END (* WITH *) 
    END WriteS 

; PROCEDURE WriteT ( f : tFile ; t : TEXT ) 

  = VAR c : CHAR 

  ; BEGIN (* WriteT *) 
      IF t # NIL 
      THEN 
        WITH With_20 = BufferPool [ f ] 
        DO FOR i := 0 TO Text . Length ( t ) - 1 
           DO c := Text . GetChar ( t , i ) 
           ; IF c = '\000' THEN RETURN END (* IF *) 
           ; INC ( With_20 . BufferIndex )               (* WriteC inline        *) 
           ; With_20 . Buffer ^ [ With_20 . BufferIndex ] := c 
           ; IF ( With_20 . BufferIndex = BufferSize ) 
                OR ( With_20 . FlushLine AND ( c = EolCh ) ) 
             THEN 
               WriteFlush ( f ) 
             END (* IF *) 
           END (* FOR *) 
        END (* WITH *) 
      END (* IF *) 
    END WriteT 

; PROCEDURE WriteShort ( f : tFile ; n : SHORTINT ; FieldWidth : Word . T ) 

  = BEGIN (* WriteShort *)                      (* shortint number      *) 
      WriteI ( f , VAL ( n , INTEGER ) , FieldWidth ) 
    END WriteShort 

; PROCEDURE WriteLong ( f : tFile ; n : M2LONGINT ; FieldWidth : Word . T ) 

  = BEGIN (* WriteLong *)                       (* longint  number      *) 
      WriteI ( f , VAL ( n , INTEGER ) , FieldWidth ) 
    END WriteLong 

; PROCEDURE WriteCard ( f : tFile ; n : Word . T ; FieldWidth : Word . T ) 

  = VAR                                         (* cardinal number      *) 
      length : Word . T 
    ; digits : ARRAY [ 0 .. 10 ] OF CHAR 

  ; BEGIN (* WriteCard *) 
      length := 0 
    ; REPEAT 
        INC ( length ) 
      ; digits [ length ] := MyCHR [ n MOD 10 ] 
      ; n := n DIV 10 
      UNTIL n = 0 
    ; FOR i := 1 TO LOOPHOLE ( FieldWidth - length , INTEGER ) 
      DO WriteC ( f , ' ' ) 
      END (* FOR *) 
    ; FOR i := length TO 1 BY - 1 
      DO WriteC ( f , digits [ i ] ) 
      END (* FOR *) 
    END WriteCard 

; PROCEDURE WriteNl ( f : tFile )               (* new line             *) 

  = BEGIN (* WriteNl *) 
      WriteC ( f , EolCh ) 
    END WriteNl 


; PROCEDURE CloseIO ( )                         (* close all files      *) 

  = BEGIN (* CloseIO *) 
      FOR i := 0 TO System . cMaxFile 
      DO WITH With_21 = BufferPool [ i ] 
         DO IF With_21 . Buffer # NIL 
            THEN 
              IF With_21 . OpenForOutput 
              THEN WriteClose ( i )
              ELSE ReadClose ( i ) 
              END (* IF *) 
            END (* IF *) 
         END (* WITH *) 
      END (* FOR *) 
    END CloseIO 

; BEGIN (* ReuseIO *) 
    MyCHR [ 0 ] := '0' 
  ; MyCHR [ 1 ] := '1' 
  ; MyCHR [ 2 ] := '2' 
  ; MyCHR [ 3 ] := '3' 
  ; MyCHR [ 4 ] := '4' 
  ; MyCHR [ 5 ] := '5' 
  ; MyCHR [ 6 ] := '6' 
  ; MyCHR [ 7 ] := '7' 
  ; MyCHR [ 8 ] := '8' 
  ; MyCHR [ 9 ] := '9' 
  ; MyCHR [ 10 ] := 'A' 
  ; MyCHR [ 11 ] := 'B' 
  ; MyCHR [ 12 ] := 'C' 
  ; MyCHR [ 13 ] := 'D' 
  ; MyCHR [ 14 ] := 'E' 
  ; MyCHR [ 15 ] := 'F' 

  ; FOR i := 0 TO System . cMaxFile 
    DO WITH With_22 = BufferPool [ i ] 
       DO With_22 . Buffer := NIL 
       ; With_22 . BufferIndex := 0 
       ; With_22 . BytesRead := 0 
       ; With_22 . OpenForOutput := FALSE 
       ; With_22 . EndOfFile := FALSE 
       ; With_22 . FlushLine := FALSE 
       ; With_22 . IsIntermittent := FALSE 
       END (* WITH *) 
    END (* FOR *) 

  ; BufferPool [ StdInput ] . Buffer := Alloc ( BufferSize + 1 ) 
  ; BufferPool [ StdOutput ] . Buffer := Alloc ( BufferSize + 1 ) 
  ; BufferPool [ StdError ] . Buffer := Alloc ( BufferSize + 1 ) 

  ; BufferPool [ StdInput ] . OpenForOutput := FALSE 
  ; BufferPool [ StdInput ] . IsIntermittent
      := System . IsIntermittent ( StdInput ) 
  ; BufferPool [ StdOutput ] . OpenForOutput := TRUE 
  ; BufferPool [ StdError ] . OpenForOutput := TRUE 

  ; CheckFlushLine ( StdInput ) 
  ; CheckFlushLine ( StdOutput ) 
  ; CheckFlushLine ( StdError ) 
  END ReuseIO 
. 

