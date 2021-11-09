#include "SYSTEM_.h"

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Listing
#include "Listing.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

BOOLEAN ArgCheck_Line;
BOOLEAN ArgCheck_Generate;
BOOLEAN ArgCheck_NoActionFlag;
struct ArgCheck_1 ArgCheck_SourceFileName;

#define eToManyArgs   21
#define eNoOption   20
static CHAR HelpFile [] = "bnf.cat";
static CHAR ShortHelpFile [] = "bnf.syn";
static CHAR cLong [] = "-l";
static CHAR cHelp [] = "-h";
static CHAR cC [] = "-c";
static CHAR cModula2 [] = "-m";
static CHAR cNoAction [] = "-NoAction";
static CHAR cLine [] = "-g";
struct S_1 {
    CHAR A[255 + 1];
};
struct S_2 {
    CHAR A[255 + 1];
};
static void CopyFile ARGS((IO_tFile in, IO_tFile out));


void ArgCheck_ArgCheck
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL ArgNo;
  struct S_1 Argument;
  Strings_tString ArgString;
  INTEGER err;
  IO_tFile file;
  struct S_2 array;
  BOOLEAN SourceFileIsOpen;

  SourceFileIsOpen = FALSE;
  Path_InsertPath(Scanner_ScanTabName.A, 128L);
  Path_InsertPath(Parser_ParsTabName.A, 129L);
  {
    LONGCARD B_1 = 1, B_2 = GetArgCount() - 1;

    if (B_1 <= B_2)
      for (ArgNo = B_1;; ArgNo += 1) {
        GetArgument((LONGINT)ArgNo, Argument.A, 256L);
        if (Argument.A[0] != '-') {
          if (SourceFileIsOpen) {
            Strings_ArrayToString(Argument.A, 256L, &ArgString);
            Errors_ErrorMessageI((LONGCARD)eToManyArgs, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(ArgString));
          } else {
            Listing_SourceFile = IO_ReadOpen(Argument.A, 256L);
            if (SysError_StatIsBad(Listing_SourceFile)) {
              Strings_ArrayToString(Argument.A, 256L, &ArgString);
              SysError_SysErrorMessageI(Listing_SourceFile, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(ArgString));
              Listing_SourceFile = IO_StdInput;
            } else {
              SourceFileIsOpen = TRUE;
              Scanner_BeginFile(Argument.A, 256L);
              Character_Assign(ArgCheck_SourceFileName.A, 128L, Argument.A, 256L);
            }
          }
        } else if (Character_IsEqual(Argument.A, 256L, cNoAction, 9L)) {
          ArgCheck_NoActionFlag = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cLong, 2L)) {
          Errors_SetReportMode(Errors_eListing);
        } else if (Character_IsEqual(Argument.A, 256L, cModula2, 2L)) {
          WriteTok_Language = WriteTok_Modula2;
        } else if (Character_IsEqual(Argument.A, 256L, cC, 2L)) {
          WriteTok_Language = WriteTok_C;
        } else if (Character_IsEqual(Argument.A, 256L, cLine, 2L)) {
          ArgCheck_Line = TRUE;
        } else if (Character_IsEqual(Argument.A, 256L, cHelp, 2L)) {
          (void)strncpy((char *)array.A, (char *)HelpFile, sizeof(array.A));
          Path_InsertPath(array.A, 256L);
          file = IO_ReadOpen(array.A, 256L);
          if (SysError_StatIsBad(file)) {
            Strings_ArrayToString(array.A, 256L, &ArgString);
            SysError_SysErrorMessageI(file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(ArgString));
          } else {
            CopyFile(file, (System_tFile)IO_StdOutput);
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
    (void)strncpy((char *)array.A, (char *)ShortHelpFile, sizeof(array.A));
    Path_InsertPath(array.A, 256L);
    file = IO_ReadOpen(array.A, 256L);
    if (SysError_StatIsBad(file)) {
      Strings_ArrayToString(array.A, 256L, &ArgString);
      SysError_SysErrorMessageI(file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(ArgString));
    } else {
      CopyFile(file, (System_tFile)IO_StdOutput);
    }
    ArgCheck_Generate = FALSE;
    return;
  }
}

static void CopyFile
# ifdef __STDC__
(IO_tFile in, IO_tFile out)
# else
(in, out)
IO_tFile in, out;
# endif
{
  Strings_tString C_1_line;

  while (!IO_EndOfFile(in)) {
    Strings_ReadL(in, &C_1_line);
    Strings_WriteL(out, &C_1_line);
  }
}

void ArgCheck__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Character__init();
    Errors__init();
    IO__init();
    Listing__init();
    WriteTok__init();
    Parser__init();
    Path__init();
    Scanner__init();
    Strings__init();
    SysError__init();
    Positions__init();
    System__init();

    ArgCheck_Line = FALSE;
    ArgCheck_Generate = TRUE;
    ArgCheck_NoActionFlag = FALSE;
    (void)strncpy((char *)ArgCheck_SourceFileName.A, " ", sizeof(ArgCheck_SourceFileName.A));
  }
}
