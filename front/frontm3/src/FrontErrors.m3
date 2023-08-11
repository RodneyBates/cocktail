
(* $Id: Errors.mi,v 2.4 1992/08/07 15:13:51 grosch rel $ *)

(* $Log: Errors.mi,v $
 * Revision 2.4  1992/08/07  15:13:51  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.3  1992/01/30  13:34:33  grosch
 * redesign of interface to operating system
 *
 * Revision 2.2  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.1  91/03/19  14:47:01  grosch
 * print error message if ErrorTab can not be opened
 * 
 * Revision 2.0  91/03/08  18:26:17  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/11  18:44:45  grosch
 * layout improvements
 * 
 * Revision 1.0  88/10/04  14:26:44  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE FrontErrors;

IMPORT Fmt;
IMPORT IntSets;
IMPORT Thread;
IMPORT Word;
IMPORT Wr;

FROM SYSTEM IMPORT SHORTCARD, M2LONGINT;
FROM    ReuseIO         IMPORT  tFile,          StdError,       WriteC, 
                                WriteNl,        WriteS,         WriteI,
                                WriteT,         WriteFlush,
                                WriteLong,      WriteB,         WriteR,
                                ReadOpenT,      ReadClose,      EndOfFile,
                                CloseIO;
FROM    Listing         IMPORT  tListMode,      ListMode,       PutError,
                                HasError,       GetError;
FROM    Memory          IMPORT  Alloc;
FROM    Sets            IMPORT  tSet,           MakeSet,        IsElement,
                                Assign;
FROM    Strings         IMPORT  tString,        AssignEmpty,    SubString,
                                Char,           ReadL,          Length,
                                StringToInt,    TextToString;
FROM    StringMem       IMPORT  tStringRef,     PutString,
                                WriteString;
FROM    Idents          IMPORT  tIdent,         WriteIdent,     GetText;
FROM    SysError        IMPORT  StatIsBad;
FROM    System          IMPORT  Exit;

FROM    TokenTab        IMPORT  TokenError,     TokenToSymbol,  MAXTerm;
FROM    Positions       IMPORT  tPosition,      NoPosition;

IMPORT Strings;

CONST
  eNone         = 0     ;       (* for internal use     *)
  cTab          = '\011'        ;       (* tab character        *)
  NoStringRef   = -1    ;

  MaxCode       = 160   ;
  eWrongClass   = 16    ;
  eWrongCode    = 17    ;

VAR 
  NoReports     : BOOLEAN;
  ReportMode    : tReportMode;
  ErrorClassRef : ARRAY [0..MaxErrorClass] OF tStringRef;
  ErrorCodeRef  : ARRAY [0..MaxCode]  OF tStringRef;
  ErrorCountRef : ARRAY [0..MaxErrorClass] OF tStringRef;

PROCEDURE ClassImage ( ErrorClass : Word . T ) : TEXT =
  BEGIN
    CASE ErrorClass OF 
    | Fatal => RETURN "Fatal";
    | Restriction => RETURN "Restriction";
    | Error => RETURN "Error";
    | Warning => RETURN "Warning";
    | Repair => RETURN "Repair";
    | Note => RETURN "Note";
    | Information => RETURN "Information";
    ELSE RETURN "UnknownErrorClass: "& Fmt.Int (ErrorClass);
    END (*CASE*)
  END ClassImage;

PROCEDURE CodeImage ( ErrorCode : Word . T ) : TEXT =
  BEGIN
    CASE ErrorCode OF
    | NoText => RETURN "NoText";
    | SyntaxError => RETURN "Syntax error";
    | ExpectedTokens => RETURN "Expected tokens:";
    | RestartPoint => RETURN "Restart point:";
    | TokenInserted => RETURN "Token inserted:";
    | WrongParseTable => RETURN "Wrong parse table";
    | OpenParseTable => RETURN "While opening parse table";
    | ReadParseTable => RETURN "While reading parse table";
    | NotReach  => RETURN "Token is not reachable:";
    | NoProd    => RETURN "Has no production:";
    | NotTerm   => RETURN "Token is nonterminating:";

    (* Errors from Front Scanner, (generated from input.rex). *) 
    | eEolString    => RETURN "End of line in string.";
    | eUnClAction   => RETURN "Unclosed action.";
    | eUnClComment  => RETURN "Unclosed comment.";
    | eUnClString   => RETURN "Unclosed string.";
    | eCharIgnored  => RETURN "Invalid character, ignored: ";

    | eState          => RETURN "in state ";
    | eReadRed        => RETURN "Shift-reduce conflict on ";
    | eRedRed         => RETURN "Reduce conflict on "; 
    | eReadRedRed     => RETURN "Shift-reduce-reduce conflict on ";
    | eRepReadRed     => RETURN "Repaired shift-reduce conflict on ";
    | eRepRedRed      => RETURN "Repaired reduce conflict on ";
    | eRepReadRedRed  => RETURN "Repaired shift-reduce-reduce conflict on ";
    | eARepReadRed    => RETURN "Assoc. repaired shift-reduce conflict on ";
    | eARepRedRed     => RETURN "Assoc. repaired reduce conflict on ";
    | eARepReadRedRed => RETURN "Assoc. repaired shift-reduce-reduce conflict on ";

    ELSE RETURN "UnknownErrorCode: " & Fmt.Int (ErrorCode);
    END (*CASE*)
  END CodeImage;


(*EXPORTED:*)
PROCEDURE ErrorMessage  (ErrorCode, ErrorClass: Word.T; Position: tPosition) =
   BEGIN
      ErrorMessageI (ErrorCode, ErrorClass, Position, eNone, NIL);
   END ErrorMessage;

(*EXPORTED:*)
PROCEDURE ErrorMessageI (ErrorCode, ErrorClass: Word.T; Position: tPosition;
                         InfoClass: Word.T; Info: ADDRESS) =
(* ^Useful for InfoClass values that do not correspond to <: REFANY. *)

   BEGIN
      INC (ErrorCount [ErrorClass]);
      IF ErrorClass IN ReportClass THEN
        NoReports := FALSE;
        IF ReportMode = tReportMode.eImmediate THEN
          WriteErrorMessage (ErrorCode, ErrorClass, Position.Line, Position.Column);
          WriteInfo (InfoClass, Info);
          WriteNl (StdError);
          WriteFlush (StdError);
        ELSE
          KeepInfo (InfoClass, Info);
          PutError (ErrorCode, ErrorClass, Position.Line, Position.Column, InfoClass, Info);
        END;
      END;
      IF ErrorClass < 3 THEN Finish() END;
   END ErrorMessageI;

(*EXPORTED:*)
PROCEDURE ErrorMessageTraced
  (ErrorCode, ErrorClass: Word.T; Position: tPosition;
                         InfoClass: Word.T; InfoTraced: REFANY) =
(* ^Useful for InfoClass values that do not correspond to <: REFANY. *)

   BEGIN
      INC (ErrorCount [ErrorClass]);
      IF ErrorClass IN ReportClass THEN
        NoReports := FALSE;
        IF ReportMode = tReportMode.eImmediate THEN
          WriteErrorMessage
            (ErrorCode, ErrorClass, Position.Line, Position.Column);
          WriteInfoTraced (InfoClass, InfoTraced := InfoTraced);
          WriteNl (StdError);
          WriteFlush (StdError);
        ELSE
          PutError
            (ErrorCode, ErrorClass, Position.Line, Position.Column,
             InfoClass, Info := NIL, InfoTraced := InfoTraced
            );
        END;
      END;
      IF ErrorClass < 3 THEN Finish() END;
   END ErrorMessageTraced;

(*EXPORTED:*)
PROCEDURE SetReportMode (mode: tReportMode) =
  BEGIN
    ReportMode := mode;
    CASE ReportMode OF
      tReportMode.eListing =>
        ListMode := tListMode.Listing;
    ELSE
        ListMode := tListMode.NoListing;
    END;
  END SetReportMode;

(*EXPORTED:*)
PROCEDURE BeginErrors() =
  VAR
    i : Word.T;
    f : tFile;
    s : tString;
    line : tString;
  BEGIN
    TRY 
      f := ReadOpenT (ErrorTableT);
    EXCEPT (* Expected: OSError . E
             , FileNoError (*No available tFile value.*) *)
    ELSE
     f := -1;
    END; 
    IF StatIsBad (f) THEN
      WriteT (StdError, "Fatal error: cannot open ");
      WriteT (StdError, ErrorTableT);
      WriteNl (StdError);
      WriteFlush (StdError);
      RETURN;
    END;

    LOOP
      IF EndOfFile (f) THEN EXIT; END;
      ReadL (f, line);
      IF Char (line, 1) = '$' THEN EXIT; END;
      IF Char (line, 1) # '%' THEN
        SplitLine (line, i, s);
        IF (i<0) OR (i>MaxErrorClass) THEN
          ErrorMessageI (eWrongClass, eError, NoPosition, eString, ADR(line));
        ELSE
          ErrorClassRef [i] := PutString (s);
        END;
      END;
    END;

    LOOP
      IF EndOfFile (f) THEN EXIT; END;
      ReadL (f, line);
      IF Char (line, 1) = '$' THEN EXIT; END;
      IF Char (line, 1) # '%' THEN
        SplitLine (line, i, s);
        IF (i<0) OR (i>MaxCode) THEN
          ErrorMessageI (eWrongCode, eError, NoPosition, eString, ADR(line));
        ELSE
          ErrorCodeRef [i] := PutString (s);
        END;
      END;
    END;

    LOOP
      IF EndOfFile (f) THEN EXIT; END;
      ReadL (f, line);
      IF Char (line, 1) = '$' THEN EXIT; END;
      IF Char (line, 1) # '%' THEN
        SplitLine (line, i, s);
        IF (i<0) OR (i>MaxErrorClass) THEN
          ErrorMessageI (eWrongClass, eError, NoPosition, eString, ADR(line));
        ELSE
          ErrorCountRef [i] := PutString (s);
        END;
      END;
    END;
    ReadClose (f);
  END BeginErrors;

(*EXPORTED:*)
PROCEDURE CloseErrors () =
   VAR 
     r : tStringRef;
     ErrorCode, ErrorClass, Line, Column, InfoClass: Word.T;
     Info : ADDRESS;
     InfoTraced : REFANY;
   BEGIN
     IF NoReports THEN RETURN END;

     WHILE HasError() DO
        GetError (ErrorCode, ErrorClass, Line, Column, InfoClass, Info, InfoTraced);
        WriteErrorMessage (ErrorCode, ErrorClass, Line, Column);
        IF InfoClass = eTokSet 
        THEN WriteInfoTraced (InfoClass, InfoTraced);
        ELSE WriteInfo (InfoClass, Info);
        END;
        WriteNl (StdError);
        WriteFlush (StdError);

     END;

     FOR i := 0 TO MaxErrorClass DO
       IF ErrorCount [i] > 0 THEN
         WriteT (StdError, "  ");
         WriteI (StdError, ErrorCount [i], 1);
         WriteC (StdError, ' ');

         r := ErrorCountRef [i];
         IF r = NoStringRef THEN
           WriteT (StdError, "in error class ");
           WriteI (StdError, i, 1);
         ELSE
           WriteString (StdError, r);
         END;
       END;
     END; 
     WriteNl (StdError);
     WriteFlush (StdError);
   END CloseErrors;

PROCEDURE WriteErrorMessage (ErrorCode, ErrorClass, Line, Column: Word.T) =
   VAR r : tStringRef;
   BEGIN
      IF (ReportMode # tReportMode.eListing) AND (Line # 0) THEN
        WriteI (StdError, Line, 3);
        WriteT (StdError, ", ");
      END;
      IF Column # 0 THEN
        WriteI (StdError, Column, 2);
        WriteT (StdError, ": ");
      END;
      
      WriteT ( StdError, ClassImage ( ErrorClass ) );
      WriteT ( StdError, " " );
(*
      IF (ErrorClass > MaxErrorClass) OR (ErrorClass < 0) THEN
        WriteT (StdError, "Error class: ");
        WriteI (StdError, ErrorClass, 1);
      ELSE
        r := ErrorClassRef [ErrorClass];
        IF r = NoStringRef THEN
          WriteT (StdError, "Error class: ");
          WriteI (StdError, ErrorClass, 1);
        ELSE
          WriteString (StdError, r);
        END;
      END;
*)
      WriteT ( StdError, CodeImage ( ErrorCode ) );
      WriteT ( StdError, " " );
(*
      IF (ErrorCode > MaxCode) OR (ErrorCode < 0) THEN
        IF ErrorCode >= SysOffset THEN
          WriteT (StdError, " system error code: ");
          WriteI (StdError, ErrorCode - SysOffset, 1);
        ELSE
          WriteT (StdError, " error code: ");
          WriteI (StdError, ErrorCode, 1);
        END;
      ELSE
        r := ErrorCodeRef [ErrorCode];
        IF r = NoStringRef THEN
          IF ErrorCode >= SysOffset THEN
            WriteT (StdError, " system error code: ");
            WriteI (StdError, ErrorCode - SysOffset, 1);
          ELSE
            WriteT (StdError, " error code: ");
            WriteI (StdError, ErrorCode, 1);
          END;
        ELSE
          WriteString (StdError, r);
        END;
      END;
*) 
   END WriteErrorMessage;

PROCEDURE KeepInfo  (InfoClass: Word.T; VAR Info: ADDRESS) =
   VAR
      InfPtrToInteger,  PtrToInteger    : UNTRACED BRANDED REF  INTEGER;
      InfPtrToShort,    PtrToShort      : UNTRACED BRANDED REF  SHORTCARD;
      InfPtrToLong,     PtrToLong       : UNTRACED BRANDED REF  LONGINT;
      InfPtrToReal,     PtrToReal       : UNTRACED BRANDED REF  REAL;
      InfPtrToBoolean,  PtrToBoolean    : UNTRACED BRANDED REF  BOOLEAN;
      InfPtrToCharacter,PtrToCharacter  : UNTRACED BRANDED REF  CHAR;
      InfPtrToString,   PtrToString     : UNTRACED BRANDED REF  tString;
      InfPtrToArray,    PtrToArray      : UNTRACED BRANDED REF  ARRAY [0..255] OF CHAR;
      InfPtrToSet,      PtrToSet        : UNTRACED BRANDED REF  tSet;
      InfPtrToIdent,    PtrToIdent      : UNTRACED BRANDED REF  tIdent;
   BEGIN
      IF InfoClass = eNone THEN RETURN END;
      CASE InfoClass OF

      |  eInteger=> 
            InfPtrToInteger := Alloc (BYTESIZE (INTEGER));
            PtrToInteger := Info;
            InfPtrToInteger^ := PtrToInteger^;
            Info := InfPtrToInteger;
      |  eShort=>
            InfPtrToShort := Alloc (BYTESIZE (SHORTCARD));
            PtrToShort := Info;
            InfPtrToShort^ := PtrToShort^;
            Info := InfPtrToShort;
      |  eLong=>
            InfPtrToLong := Alloc (BYTESIZE (LONGINT));
            PtrToLong := Info;
            InfPtrToLong^ := PtrToLong^;
            Info := InfPtrToLong;
      |  eReal=>
            InfPtrToReal := Alloc (BYTESIZE (REAL));
            PtrToReal := Info;
            InfPtrToReal^ := PtrToReal^;
            Info := InfPtrToReal;
      |  eBoolean=>
            InfPtrToBoolean := Alloc (BYTESIZE (BOOLEAN));
            PtrToBoolean := Info;
            InfPtrToBoolean^ := PtrToBoolean^;
            Info := InfPtrToBoolean;
      |  eCharacter=>
            InfPtrToCharacter := Alloc (BYTESIZE (CHAR));
            PtrToCharacter := Info;
            InfPtrToCharacter^ := PtrToCharacter^;
            Info := InfPtrToCharacter;
      |  eString=>
            InfPtrToString := Alloc (BYTESIZE (tString));
            PtrToString := Info;
            Strings.Assign (InfPtrToString^, PtrToString^);
            Info := InfPtrToString;
      |  eArray=>
            InfPtrToArray := Alloc (256);
            PtrToArray := Info;
            InfPtrToArray^ := PtrToArray^;
            Info := InfPtrToArray;
      |  eIdent=>
            InfPtrToIdent := Alloc (BYTESIZE (tIdent));
            PtrToIdent := Info;
            InfPtrToIdent^ := PtrToIdent^;
            Info := InfPtrToIdent;
      |  eTermSet=>
            InfPtrToSet := Alloc (BYTESIZE (tSet));
            PtrToSet := Info;
            MakeSet (InfPtrToSet^, PtrToSet^.MaxElmt);
            Assign (InfPtrToSet^, PtrToSet^); 
            Info := InfPtrToSet;
      |  eTokSet=> (* No need to copy, GC will protect it. *) 
      ELSE
      END;
   END KeepInfo;

PROCEDURE WriteInfo (InfoClass: Word.T; Info: ADDRESS) =
   VAR
      PtrToInteger      : UNTRACED BRANDED REF  INTEGER;
      PtrToShort        : UNTRACED BRANDED REF  SHORTCARD;
      PtrToLong         : UNTRACED BRANDED REF  M2LONGINT;
      PtrToReal         : UNTRACED BRANDED REF  REAL;
      PtrToBoolean      : UNTRACED BRANDED REF  BOOLEAN;
      PtrToCharacter    : UNTRACED BRANDED REF  CHAR;
      PtrToString       : UNTRACED BRANDED REF  tString;
      PtrToArray        : UNTRACED BRANDED REF  ARRAY [0..255] OF CHAR;
      PtrToSet          : UNTRACED BRANDED REF  tSet;
      PtrToIdent        : UNTRACED BRANDED REF  tIdent;
   BEGIN
      IF InfoClass = eNone THEN RETURN END;

      WriteC (StdError, ' ');
      CASE InfoClass OF
      |  eInteger=> 
            PtrToInteger := Info;
            WriteI (StdError, PtrToInteger^, 1);
      |  eShort=> 
            PtrToShort := Info;
            WriteI (StdError, PtrToShort^, 1);
      |  eLong=>
            PtrToLong := Info;
            WriteLong (StdError, PtrToLong^, 1);
      |  eReal=>
            PtrToReal := Info;
            WriteR (StdError, PtrToReal^, 1, 10, 1);
      |  eBoolean=>
            PtrToBoolean := Info;
            WriteB (StdError, PtrToBoolean^);
      |  eCharacter=>
            PtrToCharacter := Info;
            WriteC (StdError, PtrToCharacter^);
      |  eString=>
            PtrToString := Info;
            Strings.WriteS (StdError, PtrToString^);
      |  eArray=>
            PtrToArray := Info;
            WriteS (StdError, PtrToArray^);
      |  eIdent=>
            PtrToIdent := Info;
            WriteIdent (StdError, PtrToIdent^);
      |  eTermSet=>
            PtrToSet := Info;
            WriteTermSet (StdError, PtrToSet^);

      ELSE        WriteT (StdError, "Info Class: ");
                  WriteI (StdError, InfoClass, 1);
      END;
   END WriteInfo;

PROCEDURE WriteInfoTraced (InfoClass: Word.T; InfoTraced: REFANY) =
(* Only InfoClass IN {eTokSet, eText} does anything much. *) 
   VAR
      IntSetsT         : IntSets.T;
      TextT            : TEXT; 
   BEGIN
      IF InfoClass = eNone THEN RETURN END;

      CASE InfoClass OF 
      | eTokSet=>
          IntSetsT := InfoTraced; 
          WriteTokSet (StdError, IntSetsT);
      | eText =>
        TextT := InfoTraced;
        WriteT (StdError, TextT);
      ELSE
        WriteC (StdError, ' ');
        WriteT (StdError, "Info Class: ");
        WriteI (StdError, InfoClass, 1);
      END;
   END WriteInfoTraced;

PROCEDURE WriteTermSet (f: tFile; s:tSet) =
  VAR Error: TokenError;
  BEGIN
    FOR i := 0 TO MAXTerm DO
      IF IsElement (i, s) THEN
        WriteC (f, ' ');
        WriteIdent (f, TokenToSymbol (i, Error));
      END;
    END;
  END WriteTermSet;

PROCEDURE TokenImage (tok: IntSets.ElemT):TEXT =
  VAR LError: TokenError;
  VAR LIdent: tIdent;
  VAR LResult: TEXT;
  BEGIN
    LIdent := TokenToSymbol (tok, (*VAR*)LError);
    LResult := GetText (LIdent);
    RETURN LResult; 
  END TokenImage; 

PROCEDURE WriteTokSet (f: tFile; s:IntSets.T) =
  VAR LImage: TEXT;
  BEGIN
    WriteT (f, Wr . EOL);
    WriteT (f, "  ");

    <*FATAL Thread.Alerted, Wr.Failure *>
    BEGIN
      LImage := IntSets . Image (s, TokenImage, "  ");
    END;
    WriteT (f, LImage);
  END WriteTokSet;

PROCEDURE SplitLine (READONLY line: tString; VAR i: Word.T; VAR s1: tString) =
  VAR
    m, p1, p2 : Word.T;
    s : tString;
  BEGIN
    p1 := 1;
    p2 := 1;
    m := Length (line);
    LOOP
      IF p2 > m THEN EXIT; END;
      IF Char (line, p2) = cTab THEN EXIT; END;
      INC (p2);
    END;
    DEC (p2);
    IF p1 > p2 THEN 
      i := 0;
    ELSE
      SubString (line, p1, p2, s);
      i := StringToInt (s);
    END;

    p1 := p2+1;
    LOOP
      IF p1 > m THEN EXIT; END;
      IF Char (line, p1) # cTab THEN EXIT; END;
      INC (p1);
    END;
    p2 := p1;
    LOOP
      IF p2 > m THEN EXIT; END;
      IF Char (line, p2) = cTab THEN EXIT; END;
      INC (p2);
    END;
    DEC (p2);
    IF p1 > p2 THEN
      AssignEmpty (s1);
    ELSE
      SubString (line, p1, p2, s1);
    END;

  END SplitLine;

(*EXPORTED:*)
PROCEDURE CrashT (a: TEXT) =
  VAR s: tString;
  BEGIN
    TextToString (a, s);
    ErrorMessageI (eInternal, eFatal, NoPosition, eString, ADR (s));
  END CrashT;

PROCEDURE Finish() =
  BEGIN
    CloseErrors();
    CloseIO();
    Exit (1);
  END Finish;

BEGIN
  NoReports := TRUE;
  ReportMode := tReportMode.eNoListing;
  ReportClass := ErrorClassSet {0..MaxErrorClass};

  FOR i := 0 TO MaxErrorClass DO
    ErrorCount [i] := 0;
  END;

  FOR i := 0 TO MaxErrorClass DO
    ErrorClassRef [i] := NoStringRef;
  END;

  FOR i := 0 TO MaxCode DO
    ErrorCodeRef [i] := NoStringRef;
  END;

  FOR i := 0 TO MaxErrorClass DO
    ErrorCountRef [i] := NoStringRef;
  END;
END FrontErrors.

