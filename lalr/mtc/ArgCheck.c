#include "SYSTEM_.h"

#ifndef DEFINITION_Actions
#include "Actions.h"
#endif

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Check
#include "Check.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Debug
#include "Debug.h"
#endif

#ifndef DEFINITION_Default
#include "Default.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Listing
#include "Listing.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

CHAR ArgCheck_Scanner [] = "Scanner";
CHAR ArgCheck_Parser [] = "Parser";
BOOLEAN ArgCheck_LineFlag, ArgCheck_Generate;
IO_tFile ArgCheck_Pars, ArgCheck_Def;
BOOLEAN ArgCheck_TEST;
struct ArgCheck_1 ArgCheck_ExtDef, ArgCheck_ExtImp;
BOOLEAN ArgCheck_MakeDef;

#define eToManyArgs   21
#define eNoOption   20
static CHAR Drv [] = "Drv";
static CHAR ExtDefM [] = ".md";
static CHAR ExtImpM [] = ".mi";
static CHAR ExtDefC [] = ".h";
static CHAR ExtImpC [] = ".c";
static CHAR ScanDefM [] = "Scanner.md";
static CHAR ScanImpM [] = "Scanner.mi";
static CHAR ErrDefM [] = "Errors.md";
static CHAR ErrImpM [] = "Errors.mi";
static CHAR ParsDefM [] = "Parser.md";
static CHAR ParsImpM [] = "Parser.mi";
static CHAR ParsDrvM [] = "ParserDrv.mi";
static CHAR ScanDefC [] = "Scanner.h";
static CHAR ScanImpC [] = "Scanner.c";
static CHAR ErrDefC [] = "Errors.h";
static CHAR ErrImpC [] = "Errors.c";
static CHAR ParsDefC [] = "Parser.h";
static CHAR ParsImpC [] = "Parser.c";
static CHAR ParsDrvC [] = "ParserDrv.c";
static CHAR HelpFile [] = "lalr.cat";
static CHAR ShortHelpFile [] = "lalr.syn";
static CHAR cHelp [] = "-h";
static CHAR cC [] = "-c";
static CHAR cModula [] = "-m";
static CHAR cDefinition [] = "-d";
static CHAR cErrors [] = "-e";
static CHAR cLong [] = "-l";
static CHAR cImmediate [] = "-i";
static CHAR cScan [] = "-s";
static CHAR cParsDrv [] = "-p";
static CHAR cAll [] = "-a";
static CHAR cCase [] = "-cs";
static CHAR cVerbose [] = "-v";
static CHAR cFast [] = "-f";
static CHAR cLine [] = "-g";
static CHAR cNoTrace [] = "-NoTrace";
static CHAR cNoDefault [] = "-NoDefault";
static CHAR cTest [] = "-t";
static CHAR cItemSets [] = "-k";
static BOOLEAN MakeErr, MakeScan, MakeParsDrv;
static struct S_1 {
    CHAR A[15 + 1];
} DevNull;
struct S_4 {
    CHAR A[255 + 1];
};
struct S_5 {
    CHAR A[255 + 1];
};
struct S_6 {
    CHAR A[255 + 1];
};
struct S_7 {
    CHAR A[255 + 1];
};


void ArgCheck_ArgCheck
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL ArgNo;
  struct S_4 Argument;
  Strings_tString ArgString;
  IO_tFile file;
  struct S_5 FileName;
  BOOLEAN SourceFileIsOpen;

  SourceFileIsOpen = FALSE;
  Path_InsertPath(Scanner_ScanTabName.A, 128L);
  Path_InsertPath(Parser_ParsTabName.A, 129L);
  ArgCheck_MakeDef = FALSE;
  MakeErr = FALSE;
  MakeScan = FALSE;
  MakeParsDrv = FALSE;
  Debug_ItemSets = FALSE;
  {
    LONGCARD B_1 = 1, B_2 = GetArgCount() - 1;

    if (B_1 <= B_2)
      for (ArgNo = B_1;; ArgNo += 1) {
        GetArgument((LONGINT)ArgNo, Argument.A, 256L);
        if (Argument.A[0] >= '0' && Argument.A[0] <= '9') {
          Strings_ArrayToString(Argument.A, 256L, &ArgString);
          Gen_CaseLabels = Strings_StringToInt(&ArgString);
          Gen_CaseFlag = TRUE;
        } else if (Argument.A[0] != '-') {
          if (SourceFileIsOpen) {
            Strings_ArrayToString(Argument.A, 256L, &ArgString);
            Errors_ErrorMessageI((LONGCARD)eToManyArgs, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(ArgString));
          } else {
            Character_Assign(WriteTok_SourceFileName.A, 256L, Argument.A, 256L);
            Listing_SourceFile = IO_ReadOpen(Argument.A, 256L);
            if (SysError_StatIsBad(Listing_SourceFile)) {
              Strings_ArrayToString(Argument.A, 256L, &ArgString);
              SysError_SysErrorMessageI(Listing_SourceFile, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(ArgString));
              Listing_SourceFile = IO_StdInput;
            } else {
              SourceFileIsOpen = TRUE;
              Scanner_BeginFile(Argument.A, 256L);
            }
          }
        } else if (Character_IsEqual(Argument.A, 256L, cC, 2L)) {
          WriteTok_Language = WriteTok_C;
        } else if (Character_IsEqual(Argument.A, 256L, cModula, 2L)) {
          WriteTok_Language = WriteTok_Modula2;
        } else if (Character_IsEqual(Argument.A, 256L, cDefinition, 2L)) {
          ArgCheck_MakeDef = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cErrors, 2L)) {
          MakeErr = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cLong, 2L)) {
          Errors_SetReportMode(Errors_eListing);
        } else if (Character_IsEqual(Argument.A, 256L, cImmediate, 2L)) {
          Errors_SetReportMode(Errors_eImmediate);
        } else if (Character_IsEqual(Argument.A, 256L, cScan, 2L)) {
          MakeScan = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cParsDrv, 2L)) {
          MakeParsDrv = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cAll, 2L)) {
          MakeErr = TRUE;
          ArgCheck_MakeDef = TRUE;
          MakeParsDrv = TRUE;
          MakeScan = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cCase, 3L)) {
          Gen_CaseFlag = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cTest, 2L)) {
          ArgCheck_TEST = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cVerbose, 2L)) {
          Check_Verbose = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cFast, 2L)) {
          Check_Verbose = TRUE;
          Debug_Fast = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cItemSets, 2L)) {
          Check_Verbose = TRUE;
          Debug_ItemSets = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cLine, 2L)) {
          ArgCheck_LineFlag = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cNoTrace, 8L)) {
          Debug_NoTrace = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cNoDefault, 10L)) {
          Default_NoDefault = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cHelp, 2L)) {
          (void)strncpy((char *)FileName.A, (char *)HelpFile, sizeof(FileName.A));
          Path_InsertPath(FileName.A, 256L);
          file = IO_ReadOpen(FileName.A, 256L);
          if (SysError_StatIsBad(file)) {
            Strings_ArrayToString(FileName.A, 256L, &ArgString);
            SysError_SysErrorMessageI(file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(ArgString));
          } else {
            ArgCheck_CopyFile(file, (System_tFile)IO_StdOutput);
          }
          ArgCheck_Generate = FALSE;
          return;
        } else {
          Strings_ArrayToString(Argument.A, 256L, &ArgString);
          Errors_ErrorMessageI((LONGCARD)eNoOption, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(ArgString));
        }
        if (ArgNo >= B_2) break;
      }
  }
  if (Listing_SourceFile == IO_StdInput) {
    (void)strncpy((char *)FileName.A, (char *)ShortHelpFile, sizeof(FileName.A));
    Path_InsertPath(FileName.A, 256L);
    file = IO_ReadOpen(FileName.A, 256L);
    if (SysError_StatIsBad(file)) {
      Strings_ArrayToString(FileName.A, 256L, &ArgString);
      SysError_SysErrorMessageI(file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(ArgString));
    } else {
      ArgCheck_CopyFile(file, (System_tFile)IO_StdOutput);
    }
    ArgCheck_Generate = FALSE;
    return;
  }
}

void ArgCheck_GenerateSupport
# ifdef __STDC__
()
# else
()
# endif
{
  struct S_6 FileName;
  struct S_7 ParsDrv, ParsDef, ParsImp, ScanDef, ScanImp, ErrDef, ErrImp;
  IO_tFile in, out;
  Strings_tString String1, String2;

  if (WriteTok_Language == WriteTok_Modula2) {
    (void)strncpy((char *)ParsDrv.A, (char *)ParsDrvM, sizeof(ParsDrv.A));
    (void)strncpy((char *)ParsDef.A, (char *)ParsDefM, sizeof(ParsDef.A));
    (void)strncpy((char *)ParsImp.A, (char *)ParsImpM, sizeof(ParsImp.A));
    (void)strncpy((char *)ScanDef.A, (char *)ScanDefM, sizeof(ScanDef.A));
    (void)strncpy((char *)ScanImp.A, (char *)ScanImpM, sizeof(ScanImp.A));
    (void)strncpy((char *)ErrDef.A, (char *)ErrDefM, sizeof(ErrDef.A));
    (void)strncpy((char *)ErrImp.A, (char *)ErrImpM, sizeof(ErrImp.A));
    (void)strncpy((char *)ArgCheck_ExtDef.A, (char *)ExtDefM, sizeof(ArgCheck_ExtDef.A));
    (void)strncpy((char *)ArgCheck_ExtImp.A, (char *)ExtImpM, sizeof(ArgCheck_ExtImp.A));
  } else {
    (void)strncpy((char *)ParsDrv.A, (char *)ParsDrvC, sizeof(ParsDrv.A));
    (void)strncpy((char *)ParsDef.A, (char *)ParsDefC, sizeof(ParsDef.A));
    (void)strncpy((char *)ParsImp.A, (char *)ParsImpC, sizeof(ParsImp.A));
    (void)strncpy((char *)ScanDef.A, (char *)ScanDefC, sizeof(ScanDef.A));
    (void)strncpy((char *)ScanImp.A, (char *)ScanImpC, sizeof(ScanImp.A));
    (void)strncpy((char *)ErrDef.A, (char *)ErrDefC, sizeof(ErrDef.A));
    (void)strncpy((char *)ErrImp.A, (char *)ErrImpC, sizeof(ErrImp.A));
    (void)strncpy((char *)ArgCheck_ExtDef.A, (char *)ExtDefC, sizeof(ArgCheck_ExtDef.A));
    (void)strncpy((char *)ArgCheck_ExtImp.A, (char *)ExtImpC, sizeof(ArgCheck_ExtImp.A));
  }
  if (MakeScan) {
    ArgCheck_MakeFileName(Actions_ScannerName, ArgCheck_Scanner, 7L, ArgCheck_ExtDef.A, 6L, FileName.A, 256L);
    out = IO_WriteOpen(FileName.A, 256L);
    Checks_CheckWriteOpen(&out, FileName.A, 256L);
    Path_InsertPath(ScanDef.A, 256L);
    in = IO_ReadOpen(ScanDef.A, 256L);
    Checks_CheckReadOpen(&in, ScanDef.A, 256L);
    ArgCheck_CopyFile(in, out);
    IO_WriteClose(out);
    IO_ReadClose(in);
    ArgCheck_MakeFileName(Actions_ScannerName, ArgCheck_Scanner, 7L, ArgCheck_ExtImp.A, 6L, FileName.A, 256L);
    out = IO_WriteOpen(FileName.A, 256L);
    Checks_CheckWriteOpen(&out, FileName.A, 256L);
    Path_InsertPath(ScanImp.A, 256L);
    in = IO_ReadOpen(ScanImp.A, 256L);
    Checks_CheckReadOpen(&in, ScanImp.A, 256L);
    ArgCheck_CopyFile(in, out);
    IO_WriteClose(out);
    IO_ReadClose(in);
  }
  if (MakeErr) {
    out = IO_WriteOpen(ErrDef.A, 256L);
    Checks_CheckWriteOpen(&out, ErrDef.A, 256L);
    Path_InsertPath(ErrDef.A, 256L);
    in = IO_ReadOpen(ErrDef.A, 256L);
    Checks_CheckReadOpen(&in, ErrDef.A, 256L);
    ArgCheck_CopyFile(in, out);
    IO_WriteClose(out);
    IO_ReadClose(in);
    out = IO_WriteOpen(ErrImp.A, 256L);
    Checks_CheckWriteOpen(&out, ErrImp.A, 256L);
    Path_InsertPath(ErrImp.A, 256L);
    in = IO_ReadOpen(ErrImp.A, 256L);
    Checks_CheckReadOpen(&in, ErrImp.A, 256L);
    ArgCheck_CopyFile(in, out);
    IO_WriteClose(out);
    IO_ReadClose(in);
  }
  if (MakeParsDrv) {
    if (Actions_ParserName == Idents_NoIdent) {
      Strings_ArrayToString(ArgCheck_Parser, 6L, &String1);
    } else {
      Idents_GetString(Actions_ParserName, &String1);
    }
    Strings_ArrayToString(Drv, 3L, &String2);
    Strings_Concatenate(&String1, &String2);
    Strings_ArrayToString(ArgCheck_ExtImp.A, 6L, &String2);
    Strings_Concatenate(&String1, &String2);
    Strings_Append(&String1, '\0');
    Strings_StringToArray(&String1, FileName.A, 256L);
    out = IO_WriteOpen(FileName.A, 256L);
    Checks_CheckWriteOpen(&out, FileName.A, 256L);
    Path_InsertPath(ParsDrv.A, 256L);
    in = IO_ReadOpen(ParsDrv.A, 256L);
    Checks_CheckReadOpen(&in, ParsDrv.A, 256L);
    ArgCheck_CopyFile(in, out);
    IO_WriteClose(out);
    IO_ReadClose(in);
  }
  Path_InsertPath(ParsImp.A, 256L);
  ArgCheck_Pars = IO_ReadOpen(ParsImp.A, 256L);
  Checks_CheckReadOpen(&ArgCheck_Pars, ParsImp.A, 256L);
  if (ArgCheck_MakeDef) {
    Path_InsertPath(ParsDef.A, 256L);
    ArgCheck_Def = IO_ReadOpen(ParsDef.A, 256L);
    Checks_CheckReadOpen(&ArgCheck_Def, ParsDef.A, 256L);
  }
}

void ArgCheck_MakeFileName
# ifdef __STDC__
(Idents_tIdent Name, CHAR Default[], LONGCARD O_3, CHAR Ext[], LONGCARD O_2, CHAR FileName[], LONGCARD O_1)
# else
(Name, Default, O_3, Ext, O_2, FileName, O_1)
Idents_tIdent Name;
CHAR Default[];
LONGCARD O_3;
CHAR Ext[];
LONGCARD O_2;
CHAR FileName[];
LONGCARD O_1;
# endif
{
  Strings_tString String1, String2;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR) + O_3 * sizeof(CHAR), 2)
  COPY_OPEN_ARRAY(Ext, O_2, CHAR)
  COPY_OPEN_ARRAY(Default, O_3, CHAR)
  if (Name == Idents_NoIdent) {
    Strings_ArrayToString(Default, O_3, &String1);
  } else {
    Idents_GetString(Name, &String1);
  }
  Strings_ArrayToString(Ext, O_2, &String2);
  Strings_Concatenate(&String1, &String2);
  Strings_Append(&String1, '\0');
  Strings_StringToArray(&String1, FileName, O_1);
  FREE_OPEN_ARRAYS
}

void ArgCheck_ExpandLine
# ifdef __STDC__
(IO_tFile Out, Strings_tString Line)
# else
(Out, Line)
IO_tFile Out;
Strings_tString Line;
# endif
{
  CHAR Ch;
  CARDINAL i;

  i = 3;
  for (;;) {
    INC(i);
    if (i > Strings_Length(&Line)) {
      IO_WriteNl(Out);
      goto EXIT_1;
    }
    Ch = Strings_Char(&Line, (Strings_tStringIndex)i);
    switch (Ch) {
    case '@':;
      if (Actions_ParserName == Idents_NoIdent) {
        IO_WriteS(Out, ArgCheck_Parser, 6L);
      } else {
        Idents_WriteIdent(Out, Actions_ParserName);
      }
      break;
    case '$':;
      if (Actions_ScannerName == Idents_NoIdent) {
        if (Strings_Char(&Line, (Strings_tStringIndex)(i + 1)) == '_') {
          INC(i);
        } else {
          IO_WriteS(Out, ArgCheck_Scanner, 7L);
        }
      } else {
        Idents_WriteIdent(Out, Actions_ScannerName);
      }
      break;
    default :
      IO_WriteC(Out, Ch);
      break;
    }
  } EXIT_1:;
}

void ArgCheck_CopyFile
# ifdef __STDC__
(IO_tFile In, IO_tFile Out)
# else
(In, Out)
IO_tFile In, Out;
# endif
{
  Strings_tString Line;

  while (!IO_EndOfFile(In)) {
    Strings_ReadL(In, &Line);
    if (Strings_Length(&Line) >= 2 && Strings_Char(&Line, 1) == '$' && Strings_Char(&Line, 2) == '@') {
      ArgCheck_ExpandLine(Out, Line);
    } else {
      Strings_WriteL(Out, &Line);
    }
  }
}

void ArgCheck__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Strings__init();
    Idents__init();
    Actions__init();
    Character__init();
    Check__init();
    Checks__init();
    Debug__init();
    Default__init();
    Errors__init();
    Gen__init();
    Idents__init();
    IO__init();
    Listing__init();
    Path__init();
    Parser__init();
    Scanner__init();
    Positions__init();
    Strings__init();
    SysError__init();
    System__init();
    WriteTok__init();

    ArgCheck_LineFlag = FALSE;
    ArgCheck_TEST = FALSE;
    ArgCheck_Generate = TRUE;
    (void)strncpy((char *)DevNull.A, "/dev/null", sizeof(DevNull.A));
  }
}
