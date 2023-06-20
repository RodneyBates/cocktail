

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

IMPORT Stdio;
IMPORT Wr;

IMPORT Params;
IMPORT Text;
IMPORT Word;
FROM Actions    IMPORT  ScannerName,    ParserName;
FROM Character  IMPORT  IsEqual,        Assign;
FROM Check      IMPORT  Verbose;
FROM FrontChecks     IMPORT  CheckReadOpen,  CheckWriteOpen;
FROM FrontChecks     IMPORT  CheckReadOpenT,  CheckWriteOpenT;
FROM Debug      IMPORT  NoTrace, Fast, ItemSets;
FROM Default    IMPORT  NoDefault;
FROM FrontErrors     IMPORT  eError,         eString,
                        ErrorMessageI,  tReportMode,    SetReportMode,
                        CloseErrors, ErrorTableT;
FROM Gen        IMPORT  CaseFlag,       CaseLabels;
FROM Idents     IMPORT  tIdent, NoIdent, WriteIdent, GetString, GetText;
FROM ReuseIO         IMPORT  tFile,          StdInput,       StdOutput,
                        ReadOpen, ReadOpenT, WriteOpen, WriteOpenT, ReadClose,
                        WriteClose,     EndOfFile,      CloseIO,
                        WriteT,         WriteC,         WriteNl;
FROM Listing    IMPORT  SourceFile;
FROM FrontPath  IMPORT  InsertPathT;
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

IMPORT WriteTok;
FROM WriteTok   IMPORT  tLanguage,      Language;

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

  ErrorTab      = "Error.Tab";
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
  cLib          = "-L";

VAR cLibLen := Text.Length(cLib);

VAR (* MakeDef, *) MakeErr, MakeScan, MakeParsDrv: BOOLEAN;
VAR LibDirPath : TEXT := NIL;
VAR DevNullT : TEXT;

PROCEDURE ArgCheck() =
  VAR
    ArgNo               : Word.T;
    ArgumentT           : TEXT;
    ArgumentA           : ARRAY [0..255] OF CHAR;
    SourceFileNameS     : tString;
    file                : tFile;
    ArgString           : tString;
    FileNameT           : TEXT;
    FileName            : ARRAY [0..255] OF CHAR;
    ArgCt               : INTEGER;
    ArgLen              : INTEGER;
    Ch                  : CHAR;
    SourceFileIsOpen    : BOOLEAN;
  BEGIN
    SourceFileIsOpen := FALSE;

    MakeDef := FALSE;
    MakeErr := FALSE;
    MakeScan := FALSE;
    MakeParsDrv := FALSE;
    ItemSets := FALSE;

    ArgCt := GetArgCount ();
    ArgNo := 1;
    WHILE ArgNo < ArgCt DO 
      ArgumentT := Params.Get(ArgNo);
      IF ArgumentT = NIL THEN ArgumentT := "" END;
      TextToString (ArgumentT, ArgString);
      Ch := Text.GetChar (ArgumentT, 0);
      IF Ch>= '0' AND Ch <= '9' THEN
        CaseLabels := StringToInt (ArgString);
        CaseFlag := TRUE;
      ELSIF Ch # '-' THEN (* Not an option.  Must be input file name. *) 
        IF SourceFileIsOpen THEN
          ErrorMessageI (eToManyArgs, eError, NoPosition, eString, ADR (ArgString));
        ELSE
          WriteTok.SourceFileName := ArgumentT;
          SourceFileNameS := ArgString;
        END;
          
      ELSIF Text.Equal (ArgumentT, cC) THEN
        Language := tLanguage.C;
      ELSIF Text.Equal (ArgumentT, cModula3) THEN
        Language := tLanguage.Modula3;
      ELSIF Text.Equal (ArgumentT, cModula2) THEN
        Language := tLanguage.Modula2;
      ELSIF Text.Equal (ArgumentT, cDefinition) THEN
        MakeDef := TRUE;
      ELSIF Text.Equal (ArgumentT, cErrors) THEN
        MakeErr := TRUE;
      ELSIF Text.Equal (ArgumentT, cLong) THEN
        SetReportMode (tReportMode.eListing);
      ELSIF Text.Equal (ArgumentT, cImmediate) THEN
        SetReportMode (tReportMode.eImmediate);
      ELSIF Text.Equal (ArgumentT, cScan) THEN
        MakeScan := TRUE;
      ELSIF Text.Equal (ArgumentT, cParsDrv) THEN
        MakeParsDrv := TRUE;
      ELSIF Text.Equal (ArgumentT, cAll) THEN
        MakeErr := TRUE;
        MakeDef := TRUE;
        MakeParsDrv := TRUE;
        MakeScan := TRUE;
      ELSIF Text.Equal (ArgumentT, cCase) THEN
        CaseFlag := TRUE;
      ELSIF Text.Equal (ArgumentT, cTest) THEN
        TEST := TRUE;
      ELSIF Text.Equal (ArgumentT, cVerbose) THEN
        Verbose := TRUE;
      ELSIF Text.Equal (ArgumentT, cFast) THEN
        Verbose := TRUE;
        Fast := TRUE;
      ELSIF Text.Equal (ArgumentT, cItemSets) THEN
        Verbose := TRUE;
        ItemSets := TRUE;
      ELSIF Text.Equal (ArgumentT, cLine) THEN
        LineFlag := TRUE;
      ELSIF Text.Equal (ArgumentT, cNoTrace) THEN
        NoTrace := TRUE;
      ELSIF Text.Equal (ArgumentT, cNoDefault) THEN
        NoDefault := TRUE;
      ELSIF Text.Equal (ArgumentT, cHelp) THEN
        FileNameT := HelpFile;
        InsertLibPathT (FileNameT);
        TRY file := ReadOpenT (FileNameT);
        EXCEPT ELSE file := - 1; END; 
        IF StatIsBad (file) THEN
          TextToString (FileNameT, ArgString);
          SysErrorMessageI (file, eError, eString, ADR (ArgString));
        ELSE
          CopyFile (file, StdOutput);
        END;
        Generate := FALSE;
        RETURN;
      ELSIF Text.Equal (Text.Sub (ArgumentT, 0, cLibLen), cLib) THEN
        ArgLen := Text.Length (ArgumentT);
        IF ArgLen > cLibLen THEN (* Path is part of this arg. *) 
          LibDirPath := Text.Sub (ArgumentT, cLibLen, ArgLen-cLibLen);
        ELSE (* Path is the following arg. *) 
          ArgumentT := Params.Get(ArgNo);
          INC (ArgNo);
          LibDirPath := ArgumentT;
        END;
      ELSE
        ErrorMessageI (eNoOption, eError, NoPosition, eString, ADR (ArgString));
      END;
      INC (ArgNo);
    END (*WHILE*);

    InsertLibPathT (ScanTabName);
    InsertLibPathT (ParsTabName);

    (* ErrorTableT := ErrorTab; *)
    InsertLibPathT ((*VAR*) ErrorTableT);

    TRY SourceFile := ReadOpenT (WriteTok.SourceFileName);
    EXCEPT ELSE SourceFile := - 1; END; 
    IF StatIsBad (SourceFile) THEN
      Wr . PutText ( Stdio . stderr , "Unable to open source file " );
      Wr . PutText ( Stdio . stderr , WriteTok.SourceFileName );  
      Wr . PutText
        ( Stdio . stderr , ", reading from standard input instead." );  
      Wr . PutText ( Stdio . stderr , Wr . EOL );
      Wr . Flush ( Stdio . stderr ); 
      SourceFile := StdInput;
    ELSE
      CheckReadOpenT (SourceFile, WriteTok.SourceFileName);
      SourceFileIsOpen := TRUE;
      StringToArray(SourceFileNameS, ArgumentA);
      BeginFile (ArgumentA);
(* YUCK: What a tangled mess of conversions among 3 different
         representations of character strings!  All because I
         am avoiding massive and pervasive rework from Modula-2
         to Modula-3. *) 
    END;

    IF SourceFile = StdInput THEN
      FileNameT := ShortHelpFile;
      InsertLibPathT (FileNameT);
      TRY file := ReadOpenT (FileNameT);
      EXCEPT ELSE file := -1; END;
      IF StatIsBad (file) THEN
        TextToString (FileNameT, ArgString);
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
    FileName             : ARRAY [0..255] OF CHAR;
    BaseNameT, FileNameT : TEXT;
    ParsDrvT,
    ParsDef, ParsImp,
    ScanDef, ScanImp,
    ErrDef,  ErrImp     : TEXT;
    in, out             : tFile;
    String1, String2    : tString;
  BEGIN
    IF Language = tLanguage.Modula3 THEN
      ParsDrvT  := ParsDrvM3;
      ParsDef   := ParsDefM3;
      ParsImp   := ParsImpM3;
      ScanDef   := ScanDefM3;
      ScanImp   := ScanImpM3;
      ErrDef    := ErrDefM3;
      ErrImp    := ErrImpM3;
      ExtDef    := ExtDefM3;
      ExtImp    := ExtImpM3;


ELSIF Language = tLanguage.Modula2 THEN
      ParsDrvT  := ParsDrvM;
      ParsDef   := ParsDefM;
      ParsImp   := ParsImpM;
      ScanDef   := ScanDefM;
      ScanImp   := ScanImpM;
      ErrDef    := ErrDefM;
      ErrImp    := ErrImpM;
      ExtDef    := ExtDefM;
      ExtImp    := ExtImpM;
    ELSE
      ParsDrvT  := ParsDrvC;
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
      FileNameT := MakeFileNameT (ScannerName, ScannerT, ExtDef);
      out := WriteOpenT (FileNameT);      CheckWriteOpenT (out, FileNameT);
      InsertLibPathT (ScanDef);
      in := ReadOpenT (ScanDef);         CheckReadOpenT (in, ScanDef);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);

    END;

    IF MakeErr THEN
      out := WriteOpenT (ErrDef);        CheckWriteOpenT (out, ErrDef);
      InsertLibPathT (ErrDef);
      in := ReadOpenT (ErrDef);          CheckReadOpenT (in, ErrDef);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);

      out := WriteOpenT (ErrImp);        CheckWriteOpenT (out, ErrImp);
      InsertLibPathT (ErrImp);
      in := ReadOpenT (ErrImp);          CheckReadOpenT (in, ErrImp);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);
    END;

    IF MakeParsDrv THEN
      IF ParserName = NoIdent THEN
         BaseNameT := ParserT; 
      ELSE
         BaseNameT := GetText (ParserName);
      END;
      FileNameT := BaseNameT & Drv & ExtImp;
      out := WriteOpenT (FileNameT);      CheckWriteOpenT (out, FileNameT);
      InsertLibPathT (ParsDrvT);
      in := ReadOpenT (ParsDrvT);         CheckReadOpenT (in, ParsDrvT);
      CopyFile (in, out);
      WriteClose (out);
      ReadClose (in);
    END;

    InsertLibPathT (ParsImp);
    Pars := ReadOpenT (ParsImp);         CheckReadOpenT (Pars, ParsImp);

    IF MakeDef THEN
      InsertLibPathT (ParsDef);
      Def := ReadOpenT (ParsDef);        CheckReadOpenT (Def, ParsDef);
 (* ELSE
      Def := ReadOpenT (DevNullT);     CheckReadOpenT (Def, DevNullT); *) 
    END;
  END GenerateSupport;

CONST DirSep = "/"; (* Fix this for windows: "\\".*)
VAR DirSepLen := Text.Length (DirSep);

PROCEDURE InsertLibPathT (VAR FileNameT: TEXT) =
  VAR Suffix: TEXT;
  VAR PathLen: INTEGER; 
  BEGIN
    IF LibDirPath = NIL
    THEN
      InsertPathT ((*VAR*)FileNameT);
      (* Which will prefix FileNameT with the directory where the lalr
         executable was invoked from.*)
    ELSE
      PathLen := Text.Length (LibDirPath);
      IF PathLen >= DirSepLen
         AND Text.Sub (LibDirPath, PathLen-DirSepLen, DirSepLen) = DirSep
        THEN Suffix := "";
        ELSE Suffix := DirSep;
      END; 
      FileNameT := LibDirPath & Suffix & FileNameT;
    END (*IF*) 
  END InsertLibPathT;

PROCEDURE MakeFileNameT (Name: tIdent; DefaultT, ExtT: TEXT): TEXT =
   VAR BaseNameT: TEXT; 
   BEGIN
      IF Name = NoIdent THEN
         BaseNameT := DefaultT; 
      ELSE
         BaseNameT := GetText (Name);
      END;
      RETURN BaseNameT & ExtT;
   END MakeFileNameT;

(* WAS:
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
*)
PROCEDURE ExpandLine (Out: tFile; READONLY Line: tString) =
   VAR
      Ch        : CHAR;
      i         : Word.T;
   BEGIN
      WriteC (Out, ' '); (* Replace the "$@" at beginning of of Line. *) 
      WriteC (Out, ' ');
      i := 3;
      LOOP
         INC (i);
         IF i > Length (Line) THEN WriteNl (Out); EXIT; END;
         Ch := Char (Line, i);
         CASE Ch OF
         | '@' => IF ParserName = NoIdent
                 THEN WriteT (Out, ParserT); 
                 ELSE WriteIdent (Out, ParserName); END;
         | '$' => IF ScannerName = NoIdent THEN
                    IF Char (Line, i + 1) = '_'
                    THEN INC (i);
                    ELSE WriteT (Out, ScannerT);
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
  DevNullT       := "/dev/null"; 
END ArgCheck.

