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

 UNSAFE MODULE Errors;


FROM SYSTEM IMPORT M2LONGINT;
FROM SYSTEM IMPORT SHORTCARD;
FROM Memory     IMPORT Alloc;
FROM ReuseIO         IMPORT tFile, StdError, WriteC, WriteNl, WriteS, WriteI,
                       WriteB, WriteR, CloseIO;
FROM Positions  IMPORT tPosition, Compare, WritePosition;
FROM StringMem  IMPORT tStringRef, PutString, GetString;
FROM Strings    IMPORT tString, ArrayToString, StringToArray;
FROM Idents     IMPORT tIdent, WriteIdent, MakeIdent;
FROM Sets       IMPORT tSet, WriteSet, Assign, MakeSet, Size;
FROM Sort       IMPORT Sort;

IMPORT Word, System, Strings;

CONST MaxError  = 2000;

TYPE tArray     = ARRAY [0..255] OF CHAR;

TYPE tError     = RECORD
                                  Position      : tPosition     ;
                                  IsErrorCode   : BOOLEAN       ;
                                  ErrorNumber   : SHORTCARD     ;
                                  ErrorCode     : SHORTCARD     ;
                                  ErrorClass    : SHORTCARD     ;
                              InfoClass     : SHORTCARD;     
                           
                         vInteger      : INTEGER       ;
                           vShort        : INTEGER       ;
                            vLong         : INTEGER       ;
                            vReal         : REAL          ;
                         vBoolean      : BOOLEAN       ;
                       vCharacter    : CHAR          ;
                          vString       : tStringRef    ;
                           vArray        : tStringRef    ;
                             vSet          : UNTRACED BRANDED REF  tSet;
                           vIdent        : tIdent        ;
                     
                  END;

VAR
   ErrorTable   : ARRAY [0..MaxError] OF tError;
   MessageCount : INTEGER;
   IsStore      : BOOLEAN;
   HandleMessage: PROCEDURE (p0: BOOLEAN; p1: Word.T; p2: Word.T; p3: tPosition; p4: Word.T; p5: ADDRESS);
   Out          : tFile;

PROCEDURE ErrorMessage  (ErrorCode, ErrorClass: Word.T; Position: tPosition) =
   BEGIN
      HandleMessage (TRUE, ErrorCode, ErrorClass, Position, None, NIL);
   END ErrorMessage;

PROCEDURE ErrorMessageI (ErrorCode, ErrorClass: Word.T; Position: tPosition;
                         InfoClass: Word.T; Info: ADDRESS) =
   BEGIN
      HandleMessage (TRUE, ErrorCode, ErrorClass, Position, InfoClass, Info);
   END ErrorMessageI;

PROCEDURE Message  (READONLY ErrorText: ARRAY OF CHAR; ErrorClass: Word.T; Position: tPosition) =
   VAR String   : tString;
   BEGIN
      ArrayToString (ErrorText, String);
      HandleMessage 
        (FALSE
        , MakeIdent (String)
        , ErrorClass, Position, None, NIL
        );
   END Message;

PROCEDURE MessageI (READONLY ErrorText: ARRAY OF CHAR; ErrorClass: Word.T; Position: tPosition;
                         InfoClass: Word.T; Info: ADDRESS) =
   VAR String   : tString;
   BEGIN
      ArrayToString (ErrorText, String);
      HandleMessage 
        (FALSE
        , MakeIdent (String)
        , ErrorClass, Position, InfoClass, Info
        );
   END MessageI;

PROCEDURE StringMessage  
  (ErrorText: tString; ErrorClass: Word.T; Position: tPosition) =
                        (* Report a message represented by a tString     *)
                        (* 'ErrorText' and classified by 'ErrorClass'.  *)
   BEGIN
      HandleMessage 
        (FALSE
        , MakeIdent ( ErrorText )  
        , ErrorClass, Position, None, NIL
        );
   END StringMessage ;


PROCEDURE WriteHead (Position: tPosition; ErrorClass: Word.T) =
   BEGIN
      WritePosition (Out, Position);
      WriteS    (Out, ARRAY [0..2] OF CHAR{':',' ','\000'});
      CASE ErrorClass OF
      |  Fatal          => WriteS (Out, ARRAY [0..12] OF CHAR{'F','a','t','a','l',' ',' ',' ',' ',' ',' ',' ','\000'});
      |  Restriction    => WriteS (Out, ARRAY [0..12] OF CHAR{'R','e','s','t','r','i','c','t','i','o','n',' ','\000'});
      |  Error          => WriteS (Out, ARRAY [0..12] OF CHAR{'E','r','r','o','r',' ',' ',' ',' ',' ',' ',' ','\000'});
      |  Warning        => WriteS (Out, ARRAY [0..12] OF CHAR{'W','a','r','n','i','n','g',' ',' ',' ',' ',' ','\000'});
      |  Repair         => WriteS (Out, ARRAY [0..12] OF CHAR{'R','e','p','a','i','r',' ',' ',' ',' ',' ',' ','\000'});
      |  Note           => WriteS (Out, ARRAY [0..12] OF CHAR{'N','o','t','e',' ',' ',' ',' ',' ',' ',' ',' ','\000'});
      |  Information    => WriteS (Out, ARRAY [0..12] OF CHAR{'I','n','f','o','r','m','a','t','i','o','n',' ','\000'});
      ELSE WriteS (Out, ARRAY [0..13] OF CHAR{'E','r','r','o','r',' ','c','l','a','s','s',':',' ','\000'}); WriteI (Out, ErrorClass, 0);
      END;
   END WriteHead;

PROCEDURE WriteCode (ErrorCode: Word.T) =
   BEGIN
      CASE ErrorCode OF
      |  NoText         =>
      |  SyntaxError    => WriteS (Out, ARRAY [0..12] OF CHAR{'s','y','n','t','a','x',' ','e','r','r','o','r','\000'}           );
      |  ExpectedTokens => WriteS (Out, ARRAY [0..15] OF CHAR{'e','x','p','e','c','t','e','d',' ','t','o','k','e','n','s','\000'}        );
      |  RestartPoint   => WriteS (Out, ARRAY [0..13] OF CHAR{'r','e','s','t','a','r','t',' ','p','o','i','n','t','\000'}          );
      |  TokenInserted  => WriteS (Out, ARRAY [0..15] OF CHAR{'t','o','k','e','n',' ','i','n','s','e','r','t','e','d',' ','\000'}        );
      |  WrongParseTable=> WriteS (Out, ARRAY [0..20] OF CHAR{'p','a','r','s','e',' ','t','a','b','l','e',' ','m','i','s','m','a','t','c','h','\000'}   );
      |  OpenParseTable => WriteS (Out, ARRAY [0..23] OF CHAR{'c','a','n','n','o','t',' ','o','p','e','n',' ','p','a','r','s','e',' ','t','a','b','l','e','\000'});
      |  ReadParseTable => WriteS (Out, ARRAY [0..23] OF CHAR{'c','a','n','n','o','t',' ','r','e','a','d',' ','p','a','r','s','e',' ','t','a','b','l','e','\000'});
      |  TooManyErrors  => WriteS (Out, ARRAY [0..15] OF CHAR{'t','o','o',' ','m','a','n','y',' ','e','r','r','o','r','s','\000'}        );
      ELSE WriteS (Out, ARRAY [0..13] OF CHAR{' ','e','r','r','o','r',' ','c','o','d','e',':',' ','\000'}); WriteI (Out, ErrorCode, 0);
      END;
   END WriteCode;

PROCEDURE WriteInfo (InfoClass: Word.T; Info: ADDRESS) =
   VAR
      PtrToInteger      : UNTRACED BRANDED REF  INTEGER;
      PtrToShort        : UNTRACED BRANDED REF  SHORTCARD;
      PtrToLong         : UNTRACED BRANDED REF  M2LONGINT;
      PtrToReal         : UNTRACED BRANDED REF  REAL;
      PtrToBoolean      : UNTRACED BRANDED REF  BOOLEAN;
      PtrToCharacter    : UNTRACED BRANDED REF  CHAR;
      PtrToString       : UNTRACED BRANDED REF  tString;
      PtrToArray        : UNTRACED BRANDED REF  tArray;
      PtrToIdent        : UNTRACED BRANDED REF  tIdent;
   BEGIN
      IF InfoClass = None THEN RETURN; END;
      WriteS (Out, ARRAY [0..2] OF CHAR{':',' ','\000'});
      CASE InfoClass OF
      | Integer => PtrToInteger  := Info; WriteI (Out, PtrToInteger^, 0);
      | Short   => PtrToShort    := Info; WriteI (Out, VAL (   PtrToShort^,INTEGER), 0);
      | Long    => PtrToLong     := Info; WriteI (Out, VAL (   PtrToLong^,INTEGER), 0);
      | Real    => PtrToReal     := Info; WriteR (Out, PtrToReal^, 1, 10, 1);
      | Boolean => PtrToBoolean  := Info; WriteB (Out, PtrToBoolean^);
      | Character=>PtrToCharacter:= Info; WriteC (Out, PtrToCharacter^);
      | String  => PtrToString   := Info; Strings.WriteS (Out, PtrToString^);
      | Array   => PtrToArray    := Info; WriteS (Out, PtrToArray^);
      | Ident   => PtrToIdent    := Info; WriteIdent (Out, PtrToIdent^);
      ELSE
      END;
   END WriteInfo;

PROCEDURE WriteMessage  (IsErrorCode: BOOLEAN; ErrorCode, ErrorClass: Word.T;
                         Position: tPosition; InfoClass: Word.T; Info: ADDRESS) =
   BEGIN
      WriteHead (Position, ErrorClass);
      IF IsErrorCode THEN
         WriteCode (ErrorCode);
      ELSE
         WriteIdent (Out, VAL (   ErrorCode,tIdent ) );
      END;
      WriteInfo (InfoClass, Info);
      WriteNl (Out);
      IF (ErrorClass = Fatal) AND (NOT IsStore) THEN Exit(); END;
   END WriteMessage;

PROCEDURE WriteMessages (File: tFile) =
   VAR i        : INTEGER;
   VAR Info     : ADDRESS;
   VAR s        : tString;
   BEGIN
      Sort (1, MessageCount, IsLess, Swap);
      Out := File;
      FOR i := 1 TO MessageCount DO
         WITH m2tom3_with_1=ErrorTable [i] DO
            CASE m2tom3_with_1.InfoClass(* $$ m2tom3 warning: application of variant field, possible cast of 'InfoClass' in line 193
 $$ *) OF
            | Integer   => Info := ADR (m2tom3_with_1.vInteger(* $$ m2tom3 warning: application of variant field, possible cast of 'vInteger' in line 194
 $$ *) );
            | Short     => Info := ADR (m2tom3_with_1.vShort(* $$ m2tom3 warning: application of variant field, possible cast of 'vShort' in line 195
 $$ *)   );
            | Long      => Info := ADR (m2tom3_with_1.vLong(* $$ m2tom3 warning: application of variant field, possible cast of 'vLong' in line 196
 $$ *)    );
            | Real      => Info := ADR (m2tom3_with_1.vReal(* $$ m2tom3 warning: application of variant field, possible cast of 'vReal' in line 197
 $$ *)    );
            | Boolean   => Info := ADR (m2tom3_with_1.vBoolean(* $$ m2tom3 warning: application of variant field, possible cast of 'vBoolean' in line 198
 $$ *) );
            | Character => Info := ADR (m2tom3_with_1.vCharacter(* $$ m2tom3 warning: application of variant field, possible cast of 'vCharacter' in line 199
 $$ *));
            | String    => GetString (m2tom3_with_1.vString(* $$ m2tom3 warning: application of variant field, possible cast of 'vString' in line 200
 $$ *), s); Info := ADR (s);
            | Set       => Info :=      m2tom3_with_1.vSet(* $$ m2tom3 warning: application of variant field, possible cast of 'vSet' in line 201
 $$ *)      ;
            | Ident     => Info := ADR (m2tom3_with_1.vIdent(* $$ m2tom3 warning: application of variant field, possible cast of 'vIdent' in line 202
 $$ *)   );
            ELSE
            END;
            WriteMessage 
              ( m2tom3_with_1.IsErrorCode
              , m2tom3_with_1.ErrorCode
              , m2tom3_with_1.ErrorClass
              , m2tom3_with_1.Position
              , m2tom3_with_1.InfoClass
              (* $$ m2tom3 warning: application of variant field, possible cast of 'InfoClass' in line 208*)
              , Info
              );
         END;
      END;
      Out := StdError;
   END WriteMessages;

PROCEDURE StoreMessage  (pIsErrorCode: BOOLEAN; pErrorCode, pErrorClass: Word.T;
                         pPosition: tPosition; pInfoClass: Word.T; pInfo: ADDRESS) =
   VAR
      PtrToInteger      : UNTRACED BRANDED REF  INTEGER    ;
      PtrToShort        : UNTRACED BRANDED REF  SHORTCARD  ;
      PtrToLong         : UNTRACED BRANDED REF  M2LONGINT    ;
      PtrToReal         : UNTRACED BRANDED REF  REAL       ;
      PtrToBoolean      : UNTRACED BRANDED REF  BOOLEAN    ;
      PtrToCharacter    : UNTRACED BRANDED REF  CHAR       ;
      PtrToString       : UNTRACED BRANDED REF  tString    ;
      PtrToArray        : UNTRACED BRANDED REF  tArray     ;
      PtrToSet          : UNTRACED BRANDED REF  tSet       ;
      PtrToIdent        : UNTRACED BRANDED REF  tIdent     ;
      s                 : tString               ;
   BEGIN
      IF MessageCount < MaxError THEN
         INC (MessageCount);
         WITH m2tom3_with_2=ErrorTable [MessageCount] DO
            m2tom3_with_2.Position    := pPosition    ;
            m2tom3_with_2.IsErrorCode := pIsErrorCode ;
            m2tom3_with_2.ErrorNumber := VAL (   MessageCount,SHORTCARD )     ;
            m2tom3_with_2.ErrorCode   := VAL (   pErrorCode,SHORTCARD )       ;
            m2tom3_with_2.ErrorClass  := VAL (   pErrorClass,SHORTCARD )      ;
            m2tom3_with_2.InfoClass(* $$ m2tom3 warning: application of variant field, possible cast of 'InfoClass' in line 238
 $$ *)   := VAL (   pInfoClass,SHORTCARD )       ;
            CASE m2tom3_with_2.InfoClass(* $$ m2tom3 warning: application of variant field, possible cast of 'InfoClass' in line 239
 $$ *) OF
            | Integer   => PtrToInteger  := pInfo; m2tom3_with_2.vInteger(* $$ m2tom3 warning: application of variant field, possible cast of 'vInteger' in line 240
 $$ *)      := PtrToInteger ^;
            | Short     => PtrToShort    := pInfo; m2tom3_with_2.vShort(* $$ m2tom3 warning: application of variant field, possible cast of 'vShort' in line 241
 $$ *)        := VAL (   PtrToShort   ^,INTEGER);
            | Long      => PtrToLong     := pInfo; m2tom3_with_2.vLong(* $$ m2tom3 warning: application of variant field, possible cast of 'vLong' in line 242
 $$ *)         := VAL (   PtrToLong    ^,INTEGER);
            | Real      => PtrToReal     := pInfo; m2tom3_with_2.vReal(* $$ m2tom3 warning: application of variant field, possible cast of 'vReal' in line 243
 $$ *)         := PtrToReal    ^;
            | Boolean   => PtrToBoolean  := pInfo; m2tom3_with_2.vBoolean(* $$ m2tom3 warning: application of variant field, possible cast of 'vBoolean' in line 244
 $$ *)      := PtrToBoolean ^;
            | Character => PtrToCharacter:= pInfo; m2tom3_with_2.vCharacter(* $$ m2tom3 warning: application of variant field, possible cast of 'vCharacter' in line 245
 $$ *)    := PtrToCharacter^;
            | String    => PtrToString   := pInfo; m2tom3_with_2.vString(* $$ m2tom3 warning: application of variant field, possible cast of 'vString' in line 246
 $$ *)       := PutString (PtrToString^);
            | Array     => PtrToArray    := pInfo; ArrayToString (PtrToArray^, s);
                          m2tom3_with_2.InfoClass(* $$ m2tom3 warning: application of variant field, possible cast of 'InfoClass' in line 248
 $$ *)     := String;m2tom3_with_2.vArray(* $$ m2tom3 warning: application of variant field, possible cast of 'vArray' in line 248
 $$ *)        := PutString (s);
            | Set       => PtrToSet      := pInfo; m2tom3_with_2.vSet(* $$ m2tom3 warning: application of variant field, possible cast of 'vSet' in line 249
 $$ *)          := Alloc (BYTESIZE (tSet));
                                                  MakeSet (m2tom3_with_2.vSet(* $$ m2tom3 warning: application of variant field, possible cast of 'vSet' in line 250
 $$ *)^, Size (PtrToSet^));
                                                  Assign  (m2tom3_with_2.vSet(* $$ m2tom3 warning: application of variant field, possible cast of 'vSet' in line 251
 $$ *)^, PtrToSet^);
            | Ident     => PtrToIdent    := pInfo; m2tom3_with_2.vIdent(* $$ m2tom3 warning: application of variant field, possible cast of 'vIdent' in line 252
 $$ *)        := PtrToIdent   ^;
            ELSE
            END;
         END;
      ELSE
         WITH m2tom3_with_3=ErrorTable [MessageCount] DO
            m2tom3_with_3.IsErrorCode := TRUE         ;
            m2tom3_with_3.ErrorCode   := TooManyErrors;
            m2tom3_with_3.ErrorClass  := Restriction  ;
            m2tom3_with_3.InfoClass(* $$ m2tom3 warning: application of variant field, possible cast of 'InfoClass' in line 261
 $$ *)   := None         ;
         END;
      END;
      IF pErrorClass = Fatal THEN WriteMessages (StdError); Exit(); END;
   END StoreMessage;

PROCEDURE IsLess (i, j: INTEGER): BOOLEAN =
   VAR r: INTEGER;
   BEGIN
      r := Compare (ErrorTable [i].Position, ErrorTable [j].Position);
      IF r = -1 THEN RETURN TRUE ; END;
      IF r = +1 THEN RETURN FALSE; END;
      RETURN ErrorTable [i].ErrorNumber < ErrorTable [j].ErrorNumber;
   END IsLess;

PROCEDURE Swap (i, j: INTEGER) =
   VAR t: tError;
   BEGIN
      t := ErrorTable [i]; ErrorTable [i] := ErrorTable [j]; ErrorTable [j] := t;
   END Swap;

PROCEDURE StoreMessages (Store: BOOLEAN) =
   BEGIN
      IF Store THEN
         HandleMessage := StoreMessage;
         MessageCount  := 0;
      ELSE
         HandleMessage := WriteMessage;
      END;
      IsStore := Store;
   END StoreMessages;

PROCEDURE yyExit() =
   BEGIN
      CloseIO(); System.Exit (1);
   END yyExit;

BEGIN
   Exit         := yyExit;
   IsStore      := FALSE;
   Out          := StdError;
   HandleMessage:= WriteMessage;
END Errors.








