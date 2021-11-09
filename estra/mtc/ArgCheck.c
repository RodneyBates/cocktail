#include "SYSTEM_.h"

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
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

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
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

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

CHAR ArgCheck_cVersion [] = "8906";
BOOLEAN ArgCheck_TEST;
BOOLEAN ArgCheck_DEF;
BOOLEAN ArgCheck_IMP;
BOOLEAN ArgCheck_BU;
struct ArgCheck_1 ArgCheck_SourceFileName;
BOOLEAN ArgCheck_TREE;
BOOLEAN ArgCheck_GRAM;
BOOLEAN ArgCheck_MATCH;
BOOLEAN ArgCheck_AUTO;
BOOLEAN ArgCheck_DEBUG;

static CHAR NULL [] = "/dev/null";
struct S_1 {
    CHAR A[255 + 1];
};


void ArgCheck_CheckArgs
# ifdef __STDC__
()
# else
()
# endif
{
  struct S_1 Arg;
  Strings_tString ArgString;
  CARDINAL ArgNo;
  BOOLEAN SourceFileIsOpen;
  INTEGER pos;
  BOOLEAN Help, HelpHelp;
  BOOLEAN Error;
  BOOLEAN Default;

  SourceFileIsOpen = FALSE;
  Help = FALSE;
  HelpHelp = FALSE;
  Error = FALSE;
  Default = TRUE;
  {
    LONGCARD B_1 = 1, B_2 = GetArgCount() - 1;

    if (B_1 <= B_2)
      for (ArgNo = B_1;; ArgNo += 1) {
        GetArgument((LONGINT)ArgNo, Arg.A, 256L);
        if (Arg.A[0] == '-') {
          Default = FALSE;
          {
            LONGINT B_3 = 1, B_4 = Character_Length(Arg.A, 256L) - 1;

            if (B_3 <= B_4)
              for (pos = B_3;; pos += 1) {
                switch (Arg.A[pos]) {
                case 'W':;
                  EXCL(Errors_ReportClass, Errors_eWarning);
                  break;
                case 'R':;
                  EXCL(Errors_ReportClass, Errors_eRepair);
                  break;
                case 'N':;
                  EXCL(Errors_ReportClass, Errors_eNote);
                  break;
                case 'I':;
                  EXCL(Errors_ReportClass, Errors_eInformation);
                  break;
                case 'M':;
                  Errors_SetReportMode(Errors_eLongListing);
                  break;
                case 'D':;
                  Errors_SetReportMode(Errors_eDirectly);
                  break;
                case 't':;
                  ArgCheck_TEST = TRUE;
                  break;
                case 'b':;
                  ArgCheck_BU = TRUE;
                  break;
                case 'd':;
                  ArgCheck_DEF = TRUE;
                  break;
                case 'i':;
                  ArgCheck_IMP = TRUE;
                  break;
                case 'h':;
                  Help = TRUE;
                  break;
                case '?':;
                  Help = TRUE;
                  HelpHelp = TRUE;
                  break;
                case 'A':;
                  ArgCheck_AUTO = TRUE;
                  break;
                case 'C':;
                  ArgCheck_DEBUG = TRUE;
                  break;
                case 'G':;
                  ArgCheck_GRAM = TRUE;
                  break;
                case 'T':;
                  ArgCheck_TREE = TRUE;
                  break;
                case 'B':;
                  ArgCheck_MATCH = TRUE;
                  break;
                default :
                  Errors_ErrorMessageI((LONGCARD)Errors_eNoOption, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eCharacter, ADR(Arg.A[pos]));
                  Error = TRUE;
                  break;
                }
                if (pos >= B_4) break;
              }
          }
        } else {
          if (SourceFileIsOpen) {
            Strings_ArrayToString(Arg.A, 256L, &ArgString);
            Errors_ErrorMessageI((LONGCARD)Errors_eTooManyArgs, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(ArgString));
            Error = TRUE;
          } else {
            Listing_SourceFile = IO_ReadOpen(Arg.A, 256L);
            if (SysError_StatIsBad(Listing_SourceFile)) {
              Checks_CheckReadOpen(&Listing_SourceFile, Arg.A, 256L);
            } else {
              Scanner_BeginFile(Arg.A, 256L);
              SourceFileIsOpen = TRUE;
              Character_Assign(ArgCheck_SourceFileName.A, 256L, Arg.A, 256L);
            }
          }
        }
        if (ArgNo >= B_2) break;
      }
  }
  if (Default) {
    ArgCheck_DEF = TRUE;
    ArgCheck_IMP = TRUE;
  }
  if (!SourceFileIsOpen) {
    Listing_SourceFile = IO_ReadOpen(NULL, 9L);
    Checks_CheckReadOpen(&Listing_SourceFile, NULL, 9L);
  }
  if (Error) {
    Errors_CloseErrors();
    Exit(1L);
  }
  if (Help) {
    StdIO_WriteS((STRING)"estra/", 6L);
    StdIO_WriteS((STRING)"cVersion", 8L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)"usage:  estra [-options] [file]", 31L);
    StdIO_WriteNl();
    StdIO_WriteNl();
    StdIO_WriteS((STRING)"file  specification to be compiled", 34L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)"      if no file is specified stdin is used instead", 51L);
    StdIO_WriteNl();
    StdIO_WriteNl();
    StdIO_WriteS((STRING)"options:", 8L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" d    generate definition module", 32L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" i    generate implementation module", 36L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" b    generate bottom-up pattern matcher", 40L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" h    print help information (this text)", 40L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" t    print test information", 28L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" D    report errors directly", 28L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" M    report errors as a mixed listing", 38L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" W    do not report warnings", 28L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" R    do not report repairs", 27L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" N    do not report notes", 25L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" I    do not report informations", 32L);
    StdIO_WriteNl();
    StdIO_WriteNl();
    if (HelpHelp) {
      StdIO_WriteS((STRING)" private options for testing", 28L);
      StdIO_WriteNl();
      StdIO_WriteS((STRING)" A    test output of bottom up automaton", 40L);
      StdIO_WriteNl();
      StdIO_WriteS((STRING)" B    test output of bottom up automaton", 40L);
      StdIO_WriteNl();
      StdIO_WriteS((STRING)" C    generate code for debugging", 33L);
      StdIO_WriteNl();
      StdIO_WriteS((STRING)" G    test output of grammar", 28L);
      StdIO_WriteNl();
      StdIO_WriteS((STRING)" T    test output of tree", 25L);
      StdIO_WriteNl();
      StdIO_WriteNl();
    }
    StdIO_WriteS((STRING)"the default options are -di", 27L);
    StdIO_WriteNl();
    StdIO_WriteNl();
    Exit(0L);
  }
}

void ArgCheck__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Character__init();
    Checks__init();
    Errors__init();
    IO__init();
    Listing__init();
    Path__init();
    Scanner__init();
    Positions__init();
    StdIO__init();
    Strings__init();
    SysError__init();
    System__init();

    ArgCheck_TEST = FALSE;
    ArgCheck_DEF = FALSE;
    ArgCheck_IMP = FALSE;
    (void)strncpy((char *)ArgCheck_SourceFileName.A, " ", sizeof(ArgCheck_SourceFileName.A));
    ArgCheck_GRAM = FALSE;
    ArgCheck_TREE = FALSE;
    ArgCheck_MATCH = FALSE;
    ArgCheck_AUTO = FALSE;
    ArgCheck_DEBUG = FALSE;
  }
}
