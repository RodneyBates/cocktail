#include "SYSTEM_.h"

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Listing
#include "Listing.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

BOOLEAN ArgCheck_DEF, ArgCheck_IMP, ArgCheck_ERR, ArgCheck_SCA, ArgCheck_PAR, ArgCheck_LINE;
ArgCheck_tLanguage ArgCheck_LANGUAGE;
struct ArgCheck_1 ArgCheck_SourceFileName;
BOOLEAN ArgCheck_TREE, ArgCheck_TABLE, ArgCheck_CODES, ArgCheck_QUERY;

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
  CARDINAL ArgNo;
  struct S_1 Argument;
  Strings_tString ArgString;
  BOOLEAN Default, Help, SourceFileIsOpen;
  INTEGER pos;

  Help = FALSE;
  Default = TRUE;
  SourceFileIsOpen = FALSE;
  {
    LONGCARD B_1 = 1, B_2 = GetArgCount() - 1;

    if (B_1 <= B_2)
      for (ArgNo = B_1;; ArgNo += 1) {
        GetArgument((LONGINT)ArgNo, Argument.A, 256L);
        if (Argument.A[0] == '-') {
          Default = FALSE;
          {
            LONGINT B_3 = 1, B_4 = Character_Length(Argument.A, 256L) - 1;

            if (B_3 <= B_4)
              for (pos = B_3;; pos += 1) {
                switch (Argument.A[pos]) {
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
                case 'c':;
                  ArgCheck_LANGUAGE = ArgCheck_C;
                  break;
                case 'd':;
                  ArgCheck_DEF = TRUE;
                  break;
                case 'e':;
                  ArgCheck_ERR = TRUE;
                  break;
                case 'g':;
                  ArgCheck_LINE = TRUE;
                  break;
                case 'i':;
                  ArgCheck_IMP = TRUE;
                  break;
                case 'h':;
                  Help = TRUE;
                  break;
                case 'm':;
                  ArgCheck_LANGUAGE = ArgCheck_MODULA2;
                  break;
                case 'p':;
                  ArgCheck_PAR = TRUE;
                  break;
                case 's':;
                  ArgCheck_SCA = TRUE;
                  break;
                default :
                  Errors_ErrorMessageI((LONGCARD)Errors_eNoOption, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eCharacter, ADR(Argument.A[pos]));
                  break;
                }
                if (pos >= B_4) break;
              }
          }
        } else {
          if (SourceFileIsOpen) {
            Strings_ArrayToString(Argument.A, 256L, &ArgString);
            Errors_ErrorMessageI((LONGCARD)Errors_eTooManyArgs, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(ArgString));
          } else {
            Listing_SourceFile = IO_ReadOpen(Argument.A, 256L);
            Checks_CheckReadOpen(&Listing_SourceFile, Argument.A, 256L);
            Scanner_BeginFile(Argument.A, 256L);
            Character_Assign(ArgCheck_SourceFileName.A, 128L, Argument.A, 256L);
            SourceFileIsOpen = TRUE;
          }
        }
        if (ArgNo >= B_2) break;
      }
  }
  if (Default) {
    ArgCheck_DEF = TRUE;
    ArgCheck_IMP = TRUE;
  }
  if (Help) {
    StdIO_WriteNl();
    StdIO_WriteS((STRING)"usage: ell [-options] [file]", 28L);
    StdIO_WriteNl();
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" c  generate C code", 19L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" d  generate definition part", 28L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" e  generate (simple) error handler", 35L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" g  generate # line directives", 30L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" i  generate implementation part", 32L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" h  help (this output)", 22L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" p  generate parser driver", 26L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" s  generate (simple) scanner", 29L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" m  generate Modula-2 code (default)", 36L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" W  no warnings", 15L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" R  no repairs", 14L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" N  no notes", 12L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" I  no informations", 19L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" M  mixed error listing", 23L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" D  report errors directly", 26L);
    StdIO_WriteNl();
    IO_CloseIO();
    Exit(0L);
  }
  if (Errors_InError) {
    Errors_CloseErrors();
    IO_CloseIO();
    Exit(-1L);
  }
}

void ArgCheck__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Checks__init();
    Character__init();
    Errors__init();
    Positions__init();
    Listing__init();
    IO__init();
    Scanner__init();
    StdIO__init();
    Strings__init();
    System__init();

    ArgCheck_DEF = FALSE;
    ArgCheck_ERR = FALSE;
    ArgCheck_PAR = FALSE;
    ArgCheck_SCA = FALSE;
    ArgCheck_IMP = FALSE;
    ArgCheck_LINE = FALSE;
    ArgCheck_LANGUAGE = ArgCheck_MODULA2;
  }
}
