(* $Id: Errors.mi,v 1.0 1992/08/07 14:41:59 grosch rel $ *) 

(* $Log: Errors.mi,v $ 
 
# RMB 93/10/11 Various type conversions on integerish types. 
 
# Revision 1.0  1992/08/07  14:41:59  grosch 
# Initial revision 
# 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Juli 1992 *) 

(* Modified Rodney M. Bates: 
   Jul 1999: Increase MaxError . 
   Aug 1999: Add StringMessage . 
*) 

UNSAFE MODULE Errors 

; IMPORT Stdio 
; IMPORT Wr 

; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT SHORTCARD 

; FROM Memory IMPORT Alloc 

; FROM ReuseIO 
  IMPORT tFile , StdError , WriteC , WriteNl , WriteS , WriteT , WriteI 
  , WriteB 
  , WriteR , CloseIO 

; FROM Positions IMPORT tPosition , Compare , WritePosition 

; FROM StringMem IMPORT tStringRef , PutString , GetString 

; FROM Strings IMPORT tString , ArrayToString 

; FROM Idents IMPORT tIdent , WriteIdent , MakeIdent 

; FROM Sets IMPORT tSet , Assign , MakeSet , Size 

; FROM Sort IMPORT Sort 

; IMPORT Word , System , Strings 

; CONST MaxError = 2000 

; TYPE tArray = ARRAY [ 0 .. 255 ] OF CHAR 

; TYPE tError 
    = RECORD 
        Position : tPosition 
      ; IsErrorCode : BOOLEAN 
      ; ErrorNumber : SHORTCARD 
      ; ErrorCode : SHORTCARD 
      ; ErrorClass : SHORTCARD 
      ; InfoClass : SHORTCARD 

      ; vInteger : INTEGER 
      ; vShort : INTEGER 
      ; vLong : INTEGER 
      ; vReal : REAL 
      ; vBoolean : BOOLEAN 
      ; vCharacter : CHAR 
      ; vString : tStringRef 
      ; vArray : tStringRef 
      ; vSet : UNTRACED BRANDED REF tSet 
      ; vIdent : tIdent 

      END (* RECORD *) 

; VAR ErrorTable : ARRAY [ 0 .. MaxError ] OF tError 
  ; MessageCount : INTEGER 
  ; IsStore : BOOLEAN 
  ; HandleMessage 
    : PROCEDURE 
        ( p0 : BOOLEAN 
        ; p1 : Word . T 
        ; p2 : Word . T 
        ; p3 : tPosition 
        ; p4 : Word . T 
        ; p5 : ADDRESS 
        ) 
  ; Out : tFile 

; PROCEDURE ErrorMessage 
    ( ErrorCode , ErrorClass : Word . T ; Position : tPosition ) 

  = BEGIN (* ErrorMessage *) 
      HandleMessage ( TRUE , ErrorCode , ErrorClass , Position , None , NIL ) 
    END ErrorMessage 

; PROCEDURE ErrorMessageI 
    ( ErrorCode , ErrorClass : Word . T 
    ; Position : tPosition 
    ; InfoClass : Word . T 
    ; Info : ADDRESS 
    ) 

  = BEGIN (* ErrorMessageI *) 
      HandleMessage 
        ( TRUE , ErrorCode , ErrorClass , Position , InfoClass , Info ) 
    END ErrorMessageI 

; PROCEDURE Message 
    ( READONLY ErrorText : ARRAY OF CHAR 
    ; ErrorClass : Word . T 
    ; Position : tPosition 
    ) 

  = VAR String : tString 

  ; BEGIN (* Message *) 
      ArrayToString ( ErrorText , String ) 
    ; HandleMessage 
        ( FALSE , MakeIdent ( String ) , ErrorClass , Position , None , NIL ) 
    END Message 

; PROCEDURE MessageI 
    ( READONLY ErrorText : ARRAY OF CHAR 
    ; ErrorClass : Word . T 
    ; Position : tPosition 
    ; InfoClass : Word . T 
    ; Info : ADDRESS 
    ) 

  = VAR String : tString 

  ; BEGIN (* MessageI *) 
      ArrayToString ( ErrorText , String ) 
    ; HandleMessage 
        ( FALSE 
        , MakeIdent ( String ) 
        , ErrorClass 
        , Position 
        , InfoClass 
        , Info 
        ) 
    END MessageI 

; PROCEDURE StringMessage 
    ( READONLY ErrorText : tString 
    ; ErrorClass : Word . T 
    ; Position : tPosition 
    ) 

                        (* Report a message represented by a tString     *) 
                        (* 'ErrorText' and classified by 'ErrorClass'.  *) 

  = BEGIN (* StringMessage *) 
      HandleMessage 
        ( FALSE 
        , MakeIdent ( ErrorText ) 
        , ErrorClass 
        , Position 
        , None 
        , NIL 
        ) 
    END StringMessage 


; PROCEDURE WriteHead ( Position : tPosition ; ErrorClass : Word . T ) 

  = BEGIN (* WriteHead *) 
      WritePosition ( Out , Position ) 
    ; WriteT ( Out , ": " ) 
    ; CASE ErrorClass 
      OF Fatal 
      => WriteT ( Out , "Fatal       " ) 
      | Restriction 
      => WriteT ( Out , "Restriction " ) 
      | Error 
      => WriteT ( Out , "Error       " ) 
      | Warning 
      => WriteT ( Out , "Warning     " ) 
      | Repair 
      => WriteT ( Out , "Repair      " ) 
      | Note 
      => WriteT ( Out , "Note        " ) 
      | Information 
      => WriteT ( Out , "Information " ) 
      ELSE 
        WriteT ( Out , "Error class: " ) 
      ; WriteI ( Out , ErrorClass , 0 ) 
      END (* CASE *) 
    END WriteHead 

; PROCEDURE WriteCode ( ErrorCode : Word . T ) 

  = BEGIN (* WriteCode *) 
      CASE ErrorCode 
      OF NoText 
      => 
      | SyntaxError 
      => WriteT ( Out , "syntax error" ) 
      | ExpectedTokens 
      => WriteT ( Out , "expected tokens" ) 
      | RestartPoint 
      => WriteT ( Out , "restart point" ) 
      | TokenInserted 
      => WriteT ( Out , "token inserted " ) 
      | WrongParseTable 
      => WriteT ( Out , "parse table mismatch" ) 
      | OpenParseTable 
      => WriteT ( Out , "cannot open parse table" ) 
      | ReadParseTable 
      => WriteT ( Out , "cannot read parse table" ) 
      | TooManyErrors 
      => WriteT ( Out , "too many errors" ) 
      ELSE 
        WriteT ( Out , " error code: " ) 
      ; WriteI ( Out , ErrorCode , 0 ) 
      END (* CASE *) 
    END WriteCode 

; PROCEDURE WriteInfo ( InfoClass : Word . T ; Info : ADDRESS ) 

  = VAR PtrToInteger : UNTRACED BRANDED REF INTEGER 
    ; PtrToShort : UNTRACED BRANDED REF SHORTCARD 
    ; PtrToLong : UNTRACED BRANDED REF M2LONGINT 
    ; PtrToReal : UNTRACED BRANDED REF REAL 
    ; PtrToBoolean : UNTRACED BRANDED REF BOOLEAN 
    ; PtrToCharacter : UNTRACED BRANDED REF CHAR 
    ; PtrToString : UNTRACED BRANDED REF tString 
    ; PtrToArray : UNTRACED BRANDED REF tArray 
    ; PtrToIdent : UNTRACED BRANDED REF tIdent 

  ; BEGIN (* WriteInfo *) 
      IF InfoClass = None THEN RETURN END (* IF *) 
    ; WriteT ( Out , ": " ) 
    ; CASE InfoClass 
      OF Integer 
      => PtrToInteger := Info 
      ; WriteI ( Out , PtrToInteger ^ , 0 ) 
      | Short 
      => PtrToShort := Info 
      ; WriteI ( Out , VAL ( PtrToShort ^ , INTEGER ) , 0 ) 
      | Long 
      => PtrToLong := Info 
      ; WriteI ( Out , VAL ( PtrToLong ^ , INTEGER ) , 0 ) 
      | Real 
      => PtrToReal := Info 
      ; WriteR ( Out , PtrToReal ^ , 1 , 10 , 1 ) 
      | Boolean 
      => PtrToBoolean := Info 
      ; WriteB ( Out , PtrToBoolean ^ ) 
      | Character 
      => PtrToCharacter := Info 
      ; WriteC ( Out , PtrToCharacter ^ ) 
      | String 
      => PtrToString := Info 
      ; Strings . WriteS ( Out , PtrToString ^ ) 
      | Array 
      => PtrToArray := Info 
      ; WriteS ( Out , PtrToArray ^ ) 
      | Ident 
      => PtrToIdent := Info 
      ; WriteIdent ( Out , PtrToIdent ^ ) 
      ELSE 
      END (* CASE *) 
    END WriteInfo 

; PROCEDURE WriteMessage 
    ( IsErrorCode : BOOLEAN 
    ; ErrorCode , ErrorClass : Word . T 
    ; Position : tPosition 
    ; InfoClass : Word . T 
    ; Info : ADDRESS 
    ) 

  = BEGIN (* WriteMessage *) 
      WriteHead ( Position , ErrorClass ) 
    ; IF IsErrorCode 
      THEN 
        WriteCode ( ErrorCode ) 
      ELSE 
        WriteIdent ( Out , VAL ( ErrorCode , tIdent ) ) 
      END (* IF *) 
    ; WriteInfo ( InfoClass , Info ) 
    ; WriteNl ( Out ) 
    ; IF ( ErrorClass = Fatal ) AND ( NOT IsStore ) 
      THEN 
        Exit ( ) 
      END (* IF *) 
    END WriteMessage 

; PROCEDURE WriteMessages ( File : tFile ) 

  = VAR Info : ADDRESS 
  ; VAR s : tString 

  ; BEGIN (* WriteMessages *) 
      Sort ( 1 , MessageCount , IsLess , Swap ) 
    ; Out := File 
    ; FOR i := 1 TO MessageCount 
      DO WITH With_1 = ErrorTable [ i ] 
         DO CASE With_1 . InfoClass 
            OF Integer 
            => Info := ADR ( With_1 . vInteger ) 
            | Short 
            => Info := ADR ( With_1 . vShort ) 
            | Long 
            => Info := ADR ( With_1 . vLong ) 
            | Real 
            => Info := ADR ( With_1 . vReal ) 
            | Boolean 
            => Info := ADR ( With_1 . vBoolean ) 
            | Character 
            => Info := ADR ( With_1 . vCharacter ) 
            | String 
            => GetString ( With_1 . vString , s ) 
            ; Info := ADR ( s ) 
            | Set 
            => Info := With_1 . vSet 
            | Ident 
            => Info := ADR ( With_1 . vIdent ) 
            ELSE 
            END (* CASE *) 
         ; WriteMessage 
             ( With_1 . IsErrorCode 
             , With_1 . ErrorCode 
             , With_1 . ErrorClass 
             , With_1 . Position 
             , With_1 . InfoClass 
             , Info 
             ) 
         END (* WITH *) 
      END (* FOR *) 
    ; Out := StdError 
    END WriteMessages 

; PROCEDURE StoreMessage 
    ( pIsErrorCode : BOOLEAN 
    ; pErrorCode , pErrorClass : Word . T 
    ; pPosition : tPosition 
    ; pInfoClass : Word . T 
    ; pInfo : ADDRESS 
    ) 

  = VAR PtrToInteger : UNTRACED BRANDED REF INTEGER 
    ; PtrToShort : UNTRACED BRANDED REF SHORTCARD 
    ; PtrToLong : UNTRACED BRANDED REF M2LONGINT 
    ; PtrToReal : UNTRACED BRANDED REF REAL 
    ; PtrToBoolean : UNTRACED BRANDED REF BOOLEAN 
    ; PtrToCharacter : UNTRACED BRANDED REF CHAR 
    ; PtrToString : UNTRACED BRANDED REF tString 
    ; PtrToArray : UNTRACED BRANDED REF tArray 
    ; PtrToSet : UNTRACED BRANDED REF tSet 
    ; PtrToIdent : UNTRACED BRANDED REF tIdent 
    ; s : tString 

  ; BEGIN (* StoreMessage *) 
      IF MessageCount < MaxError 
      THEN 
        INC ( MessageCount ) 
      ; WITH With_2 = ErrorTable [ MessageCount ] 
        DO With_2 . Position := pPosition 
        ; With_2 . IsErrorCode := pIsErrorCode 
        ; With_2 . ErrorNumber := VAL ( MessageCount , SHORTCARD ) 
        ; With_2 . ErrorCode := VAL ( pErrorCode , SHORTCARD ) 
        ; With_2 . ErrorClass := VAL ( pErrorClass , SHORTCARD ) 
        ; With_2 . InfoClass := VAL ( pInfoClass , SHORTCARD ) 
        ; CASE With_2 . InfoClass 
          OF Integer 
          => PtrToInteger := pInfo 
          ; With_2 . vInteger := PtrToInteger ^ 
          | Short 
          => PtrToShort := pInfo 
          ; With_2 . vShort := VAL ( PtrToShort ^ , INTEGER ) 
          | Long 
          => PtrToLong := pInfo 
          ; With_2 . vLong := VAL ( PtrToLong ^ , INTEGER ) 
          | Real 
          => PtrToReal := pInfo 
          ; With_2 . vReal := PtrToReal ^ 
          | Boolean 
          => PtrToBoolean := pInfo 
          ; With_2 . vBoolean := PtrToBoolean ^ 
          | Character 
          => PtrToCharacter := pInfo 
          ; With_2 . vCharacter := PtrToCharacter ^ 
          | String 
          => PtrToString := pInfo 
          ; With_2 . vString := PutString ( PtrToString ^ ) 
          | Array 
          => PtrToArray := pInfo 
          ; ArrayToString ( PtrToArray ^ , s ) 
          ; With_2 . InfoClass := String 
          ; With_2 . vArray := PutString ( s ) 
          | Set 
          => PtrToSet := pInfo 
          ; With_2 . vSet := Alloc ( BYTESIZE ( tSet ) ) 
          ; MakeSet ( With_2 . vSet ^ , Size ( PtrToSet ^ ) ) 
          ; Assign ( With_2 . vSet ^ , PtrToSet ^ ) 
          | Ident 
          => PtrToIdent := pInfo 
          ; With_2 . vIdent := PtrToIdent ^ 
          ELSE 
          END (* CASE *) 
        END (* WITH *) 
      ELSE 
        WITH With_3 = ErrorTable [ MessageCount ] 
        DO With_3 . IsErrorCode := TRUE 
        ; With_3 . ErrorCode := TooManyErrors 
        ; With_3 . ErrorClass := Restriction 
        ; With_3 . InfoClass := None 
        END (* WITH *) 
      END (* IF *) 
    ; IF pErrorClass = Fatal 
      THEN 
        WriteMessages ( StdError ) 
      ; Exit ( ) 
      END (* IF *) 
    END StoreMessage 

; PROCEDURE IsLess ( i , j : INTEGER ) : BOOLEAN 

  = VAR r : INTEGER 

  ; BEGIN (* IsLess *) 
      r := Compare 
             ( ErrorTable [ i ] . Position , ErrorTable [ j ] . Position ) 
    ; IF r = - 1 THEN RETURN TRUE END (* IF *) 
    ; IF r = + 1 THEN RETURN FALSE END (* IF *) 
    ; RETURN ErrorTable [ i ] . ErrorNumber < ErrorTable [ j ] . ErrorNumber 
    END IsLess 

; PROCEDURE Swap ( i , j : INTEGER ) 

  = VAR t : tError 

  ; BEGIN (* Swap *) 
      t := ErrorTable [ i ] 
    ; ErrorTable [ i ] := ErrorTable [ j ] 
    ; ErrorTable [ j ] := t 
    END Swap 

; PROCEDURE StoreMessages ( Store : BOOLEAN ) 

  = BEGIN (* StoreMessages *) 
      IF Store 
      THEN 
        HandleMessage := StoreMessage 
      ; MessageCount := 0 
      ELSE 
        HandleMessage := WriteMessage 
      END (* IF *) 
    ; IsStore := Store 
    END StoreMessages 

; PROCEDURE yyExit ( ) 

  = BEGIN (* yyExit *) 
      CloseIO ( ) 
    ; System . Exit ( 1 ) 
    END yyExit 

; PROCEDURE ErrLine ( msg : TEXT ) 

  = BEGIN (* ErrLine *) 
      Wr . PutText ( Stdio . stderr , msg ) 
    ; Wr . PutText ( Stdio . stderr , Wr . EOL ) 
    ; Wr . Flush ( Stdio . stderr ) 
    END ErrLine 

; BEGIN (* Errors *) 
    Exit := yyExit 
  ; IsStore := FALSE 
  ; Out := StdError 
  ; HandleMessage := WriteMessage 
  END Errors 
. 








