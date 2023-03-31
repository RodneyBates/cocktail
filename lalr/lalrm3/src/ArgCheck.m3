(* check arguments *)

(* $Id: ArgCheck.mi,v 2.5 1992/09/24 13:12:31 grosch rel $ *)

(* Rodney M. Bates, modifications: 
    2-02 Changes to support printing item sets.
    1-98 Change to not open /dev/null (which was failing anyway)
         when -d (or -a) flag is not given. 
    1-98 Change (Now unused) DevNull so it has a trailing null when passed
    3-2023 Add generation of Module-3 code. 
    Further changes in https://github.com/RodneyBates/cocktail
*) 

(* $Log: ArgCheck.mi,v $
 * Revision 2.5  1992/09/24  13:12:31  grosch
 * added option -f
 *
 * Revision 2.4  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.3  1992/01/30  14:08:30  grosch
 * redesign of interface to operating system
 *
 * Revision 2.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.1  91/10/09  09:05:14  grosch
 * renamed NULL in DevNull for C compatibility
 * 
 * Revision 2.0  91/03/08  18:31:31  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.5  90/06/12  16:53:33  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.4  89/10/18  19:41:33  grosch
 * renamed ScanTab and ParsTab to Scan.Tab and Pars.Tab because of PCTE
 * 
 * Revision 1.3  89/05/02  14:33:06  vielsack
 * new option: -v
 * 
 * Revision 1.2  89/02/24  14:06:52  vielsack
 * call BeginFile
 * 
 * Revision 1.1  89/01/12  18:10:34  vielsack
 * supply source file name
 * 
 * Revision 1.0  88/10/04  14:35:47  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE ArgCheck;

IMPORT Word;
FROM Actions    IMPORT  ScannerName,    ParserName;
FROM Character  IMPORT  IsEqual,        Assign;
FROM Check      IMPORT  Verbose;
FROM Checks     IMPORT  CheckReadOpen,  CheckWriteOpen;
FROM Debug      IMPORT  NoTrace, Fast, ItemSets;
FROM Default    IMPORT  NoDefault;
FROM FrontErrors     IMPORT  eError,         eString,
                        ErrorMessageI,  tReportMode,    SetReportMode,
                        CloseErrors;
FROM Gen        IMPORT  CaseFlag,       CaseLabels;
FROM Idents     IMPORT  tIdent, NoIdent, WriteIdent, GetString;
FROM ReuseIO         IMPORT  tFile,          StdInput,       StdOutput,
                        ReadOpen,       WriteOpen,      ReadClose,
                        WriteClose,     EndOfFile,      CloseIO,
                        WriteT,         WriteC,         WriteNl;
FROM Listing    IMPORT  SourceFile;
FROM FrontPath       IMPORT  InsertPath;
FROM Parser     IMPORT  ParsTabName;
FROM Scanner    IMPORT  ScanTabName,    BeginFile;
FROM Positions  IMPORT  NoPosition;
FROM Strings    IMPORT  tString,        tStringIndex,   ArrayToString,
                        TextToString,
                        StringToArray,  SubString,      Char,
                        Concatenate,    Length,         ReadL,
                        WriteL,         StringToInt,    Append;
FROM SysError   IMPORT  StatIsBad,      SysErrorMessageI;
FROM System     IMPORT  GetArgument,    GetArgCount;

FROM WriteTok   IMPORT  tLanguage,      Language,       SourceFileName;

CONST
  eToManyArgs   = 21;
  eNoOption     = 20;

  Drv           = "Drv";
  ExtDefM3      = ".i3";
  ExtImpM3      = ".m3";
  ExtDefM       = ".md";
  ExtImpM       = ".mi";
  ExtDefC       = ".h";
  ExtImpC       = ".c";

  ScanDefM3     = "Scanner.i3";
  ScanImpM3     = "Scanner.m3";
  ScanDefM      = "Scanner.md";
  ScanImpM      = "Scanner.mi";
  ErrDefM3      = "Errors.i3";
  ErrImpM3      = "Errors.m3";
  ErrDefM       = "Errors.md";
  ErrImpM       = "Errors.mi";
  ParsDefM3     = "Parser.i3";
  ParsImpM3     = "Parser.m3";
  ParsDrvM3     = "ParserDrv.m3";
  ParsDefM      = "Parser.md";
  ParsImpM      = "Parser.mi";
  ParsDrvM      = "ParserDrv.mi";

  ScanDefC      = "Scanner.h";
  ScanImpC      = "Scanner.c";
  ErrDefC       = "Errors.h";
  ErrImpC       = "Errors.c";
  ParsDefC      = "Parser.h";
  ParsImpC      = "Parser.c";
  ParsDrvC      = "ParserDrv.c";

  HelpFile      = "lalr.cat";
  ShortHelpFile = "lalr.syn";

  cHelp         = "-h";
  cC            = "-c";
  cModula3      = "-M";
  cModula2      = "-m";
  cDefinition   = "-d";
  cErrors       = "-e";
  cLong         = "-l";
  cImmediate    = "-i";
  cScan         = "-s";
  cParsDrv      = "-p";
  cAll          = "-a";
  cCase         = "-cs";
  cVerbose      = "-v";
  cFast         = "-f";
  cLine         = "-g";
  cNoTrace      = "-NoTrace";
  cNoDefault    = "-NoDefault";
  cTest         = "-t";
  cItemSets     = "-k";

VAR (* MakeDef, *) MakeErr, MakeScan, MakeParsDrv: BOOLEAN;
VAR DevNull : ARRAY [ 0 .. 15 ] OF CHAR; 

PROCEDURE ArgCheck() =
  VAR
    ArgNo               : Word.T;
    Argument            : ARRAY [0..255] OF CHAR;
    ArgString           : tString;
    file                : tFile;
    FileName            : ARRAY [0..255] OF CHAR;
    SourceFileIsOpen    : BOOLEAN;
  BEGIN
    SourceFileIsOpen := FALSE;
    InsertPath (ScanTabName);
    InsertPath (ParsTabName);

    MakeDef := FALSE;
    MakeErr := FALSE;
    MakeScan := FALSE;
    MakeParsDrv := FALSE;
    ItemSets := FALSE;

    FOR ArgNo := 1 TO GetArgCount () - 1 DO
      GetArgument (ArgNo, Argument);
      IF (Argument [0] >= '0') AND (Argument [0] <= '9') THEN
        ArrayToString (Argument, ArgString);
        CaseLabels := StringToInt (ArgString);
        CaseFlag := TRUE;
      ELSIF Argument [0] # '-' THEN
        IF SourceFileIsOpen THEN
          ArrayToString (Argument, ArgString);
          ErrorMessageI (eToManyArgs, eError, NoPosition, eString, ADR (ArgString));
        ELSE
          Assign (SourceFileName, Argument);
          SourceFile := ReadOpen (Argument);
          IF StatIsBad (SourceFile) THEN
            ArrayToString (Argument, ArgString);
            SysErrorMessageI (SourceFile, eError, eString, ADR(ArgString));
            SourceFile := StdInput;
          ELSE
            SourceFileIsOpen := TRUE;
            BeginFile (Argument);
          END;
        END;
          
      ELSIF IsEqual (Argument, cC) THEN
        Language := tLanguage.C;
      ELSIF IsEqual (Argument, cModula3) THEN
        Language := tLanguage.Modula3;
      ELSIF IsEqual (Argument, cModula2) THEN
        Language := tLanguage.Modula2;
      ELSIF IsEqual (Argument, cDefinition) THEN
        MakeDef := TRUE;
      ELSIF IsEqual (Argument, cErrors) THEN
        MakeErr := TRUE;
      ELSIF IsEqual (Argument, cLong) THEN
        SetReportMode (tReportMode.eListing);
      ELSIF IsEqual (Argument, cImmediate) THEN
        SetReportMode (tReportMode.eImmediate);
      ELSIF IsEqual (Argument, cScan) THEN
        MakeScan := TRUE;
      ELSIF IsEqual (Argument, cParsDrv) THEN
        MakeParsDrv := TRUE;
      ELSIF IsEqual (Argument, cAll) THEN
        MakeErr := TRUE;
        MakeDef := TRUE;
        MakeParsDrv := TRUE;
        MakeScan := TRUE;
      ELSIF IsEqual (Argument, cCase) THEN
        CaseFlag := TRUE;
      ELSIF IsEqual (Argument, cTest) THEN
        TEST := TRUE;
      ELSIF IsEqual (Argument, cVerbose) THEN
        Verbose := TRUE;
      ELSIF IsEqual (Argument, cFast) THEN
        Verbose := TRUE;
        Fast := TRUE;
      ELSIF IsEqual (Argument, cItemSets) THEN
        Verbose := TRUE;
        ItemSets := TRUE;
      ELSIF IsEqual (Argument, cLine) THEN
        LineFlag := TRUE;
      ELSIF IsEqual (Argument, cNoTrace) THEN
        NoTrace := TRUE;
      ELSIF IsEqual (Argument, cNoDefault) THEN
        NoDefault := TRUE;
      ELSIF IsEqual (Argument, cHelp) THEN
        FileName := HelpFile;
        InsertPath (FileName);
        file := ReadOpen (FileName);
        IF StatIsBad (file) THEN
          ArrayToString (FileName, ArgString);
          SysErrorMessageI (file, eError, eString, ADR (ArgString));
        ELSE
          CopyFile (file, StdOutput);
        END;
        Generate := FALSE;
        RETURN;
      ELSE
        ArrayToString (Argument, ArgString);
        ErrorMessageI (eNoOption, eError, NoPosition, eString, ADR (ArgString));
      END;
    END;

    IF SourceFile = StdInput THEN
      FileName := ShortHelpFile;
      InsertPath (FileName);
      file := ReadOpen (FileName);
      IF StatIsBad (file) THEN
        ArrayToString (FileName, ArgString);
        SysErrorMessageI (file, eError, eString, ADR (ArgString));
      ELSE
        CopyFile (file, StdOutput);
      END;
      Generate := FALSE;
      RETURN;
    END;
  END ArgCheck;

PROCEDURE GenerateSupport() =
  VAR
    FileName            : ARRAY [0..255] OF CHAR;
    ParsDrv,
    ParsDef, ParsImp,
    ScanDef, ScanImp,
    ErrDef,  ErrImp     : ARRAY [0..255] OF CHAR;
    in, out             : tFile;
    String1, String2    : tString;
  BEGIN
    IF Language = tLanguage.Modula3 THEN
      ParsDrv   := ParsDrvM3;
      ParsDef   := ParsDefM3;
      ParsImp   := ParsImpM3;
      ScanDef   := ScanDefM3;
      ScanImp   := ScanImpM3;
      ErrDef    := ErrDefM3;
      ErrImp    := ErrImpM3;
      ExtDef    := ExtDefM3;
      ExtImp    := ExtImpM3;


ELSIF Language = tLanguage.Modula2 THEN
      ParsDrv   := ParsDrvM;
      ParsDef   := ParsDefM;
      ParsImp   := ParsImpM;
      ScanDef   := ScanDefM;
      ScanImp   := ScanImpM;
      ErrDef    := ErrDefM;
      ErrImp    := ErrImpM;
      ExtDef    := ExtDefM;
      ExtImp    := ExtImpM;
    ELSE
      ParsDrv   := ParsDrvC;
      ParsDef   := ParsDefC;
      ParsImp   := ParsImpC;
      ScanDef   := ScanDefC;
      ScanImp   := ScanImpC;
      ErrDef    := ErrDefC;
      ErrImp    := ErrImpC;
      ExtDef    := ExtDefC;
      ExtImp    := ExtImpC;
    END;

    IF MakeScan THEN
      MakeFileName (ScannerName, Scanner, ExtDef, FileName);
      out := WriteOpen (FileName);      CheckWriteOpen (out, FileName);
      InsertPath (ScanDef);
      in := ReadOpen (ScanDef);         CheckReadOpen (in, ScanDef);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);

      MakeFileName (ScannerName, Scanner, ExtImp, FileName);
      out := WriteOpen (FileName);      CheckWriteOpen (out, FileName);
      InsertPath (ScanImp);
      in := ReadOpen (ScanImp);         CheckReadOpen (in, ScanImp);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);
    END;

    IF MakeErr THEN
      out := WriteOpen (ErrDef);        CheckWriteOpen (out, ErrDef);
      InsertPath (ErrDef);
      in := ReadOpen (ErrDef);          CheckReadOpen (in, ErrDef);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);

      out := WriteOpen (ErrImp);        CheckWriteOpen (out, ErrImp);
      InsertPath (ErrImp);
      in := ReadOpen (ErrImp);          CheckReadOpen (in, ErrImp);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);
    END;

    IF MakeParsDrv THEN
      IF ParserName = NoIdent THEN
         TextToString  (Parser, String1);
      ELSE
         GetString      (ParserName, String1);
      END;
      TextToString     (Drv, String2);
      Concatenate       (String1, String2);
      TextToString     (ExtImp, String2);
      Concatenate       (String1, String2);
      Append            (String1, '\000');
      StringToArray     (String1, FileName);
      out := WriteOpen (FileName);      CheckWriteOpen (out, FileName);
      InsertPath (ParsDrv);
      in := ReadOpen (ParsDrv);         CheckReadOpen (in, ParsDrv);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);
    END;

    InsertPath (ParsImp);
    Pars := ReadOpen (ParsImp);         CheckReadOpen (Pars, ParsImp);

    IF MakeDef THEN
      InsertPath (ParsDef);
      Def := ReadOpen (ParsDef);        CheckReadOpen (Def, ParsDef);
 (* ELSE
      Def := ReadOpen (DevNull);     CheckReadOpen (Def, DevNull); *) 
    END;
  END GenerateSupport;

PROCEDURE MakeFileName (Name: tIdent;READONLY  Default, Ext: ARRAY OF CHAR; VAR FileName: ARRAY OF CHAR) =
   VAR String1, String2 : tString;
   BEGIN
      IF Name = NoIdent THEN
         TextToString  (Default, String1);
      ELSE
         GetString      (Name, String1);
      END;
      TextToString     (Ext, String2);
      Concatenate       (String1, String2);
      Append            (String1, '\000');
      StringToArray     (String1, FileName);
   END MakeFileName;

PROCEDURE ExpandLine (Out: tFile; Line: tString) =
   VAR
      Ch        : CHAR;
      i         : Word.T;
   BEGIN
      i := 3;
      LOOP
         INC (i);
         IF i > Length (Line) THEN WriteNl (Out); EXIT; END;
         Ch := Char (Line, i);
         CASE Ch OF
         | '@' => IF ParserName = NoIdent
                 THEN WriteT (Out, Parser); 
                 ELSE WriteIdent (Out, ParserName); END;
         | '$' => IF ScannerName = NoIdent THEN
                    IF Char (Line, i + 1) = '_'
                    THEN INC (i);
                    ELSE WriteT (Out, Scanner);
                    END;
                 ELSE WriteIdent (Out, ScannerName); END;
         ELSE    WriteC (Out, Ch);
         END;
      END;
   END ExpandLine;

PROCEDURE CopyFile (In, Out: tFile) =
  VAR Line      : tString;
  BEGIN
    WHILE NOT EndOfFile (In) DO
      ReadL (In, Line);
      IF (Length (Line) >= 2) AND (Char (Line, 1) = '$') AND (Char (Line, 2) = '@') THEN
         ExpandLine (Out, Line);
      ELSE
         WriteL (Out, Line);
      END;
    END;
  END CopyFile;

BEGIN
  LineFlag      := FALSE;
  TEST          := FALSE;
  Generate      := TRUE;
  DevNull       := "/dev/null"; 
END ArgCheck.

