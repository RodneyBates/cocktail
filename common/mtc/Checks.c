#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
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

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif


static CHAR DevNull [] = "/dev/null";


void Checks_ErrorCheck
# ifdef __STDC__
(CHAR a[], LONGCARD O_1, INTEGER n)
# else
(a, O_1, n)
CHAR a[];
LONGCARD O_1;
INTEGER n;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_1, CHAR)
  if (SysError_StatIsBad(n)) {
    Strings_ArrayToString(a, O_1, &s);
    SysError_SysErrorMessageI(n, (LONGCARD)Errors_eFatal, (LONGCARD)Errors_eString, ADR(s));
  }
  FREE_OPEN_ARRAYS
}

void Checks_CheckReadOpen
# ifdef __STDC__
(IO_tFile *file, CHAR a[], LONGCARD O_2)
# else
(file, a, O_2)
IO_tFile *file;
CHAR a[];
LONGCARD O_2;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_2, CHAR)
  if (SysError_StatIsBad(*file)) {
    Strings_ArrayToString(a, O_2, &s);
    SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(s));
    *file = IO_ReadOpen(DevNull, 9L);
    if (SysError_StatIsBad(*file)) {
      Strings_ArrayToString(DevNull, 9L, &s);
      SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eFatal, (LONGCARD)Errors_eString, ADR(s));
    }
  }
  FREE_OPEN_ARRAYS
}

void Checks_CheckWriteOpen
# ifdef __STDC__
(IO_tFile *file, CHAR a[], LONGCARD O_3)
# else
(file, a, O_3)
IO_tFile *file;
CHAR a[];
LONGCARD O_3;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_3, CHAR)
  if (SysError_StatIsBad(*file)) {
    Strings_ArrayToString(a, O_3, &s);
    SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(s));
    *file = IO_WriteOpen(DevNull, 9L);
    if (SysError_StatIsBad(*file)) {
      Strings_ArrayToString(DevNull, 9L, &s);
      SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eFatal, (LONGCARD)Errors_eString, ADR(s));
    }
  }
  FREE_OPEN_ARRAYS
}

void Checks_CheckOpenInput
# ifdef __STDC__
(IO_tFile *file, CHAR a[], LONGCARD O_4)
# else
(file, a, O_4)
IO_tFile *file;
CHAR a[];
LONGCARD O_4;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_4, CHAR)
  if (SysError_StatIsBad(*file)) {
    Strings_ArrayToString(a, O_4, &s);
    SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(s));
    *file = OpenInput(DevNull, 9L);
    if (SysError_StatIsBad(*file)) {
      Strings_ArrayToString(DevNull, 9L, &s);
      SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eFatal, (LONGCARD)Errors_eString, ADR(s));
    }
  }
  FREE_OPEN_ARRAYS
}

void Checks_CheckOpenOutput
# ifdef __STDC__
(IO_tFile *file, CHAR a[], LONGCARD O_5)
# else
(file, a, O_5)
IO_tFile *file;
CHAR a[];
LONGCARD O_5;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_5 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_5, CHAR)
  if (SysError_StatIsBad(*file)) {
    Strings_ArrayToString(a, O_5, &s);
    SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(s));
    *file = OpenOutput(DevNull, 9L);
    if (SysError_StatIsBad(*file)) {
      Strings_ArrayToString(DevNull, 9L, &s);
      SysError_SysErrorMessageI(*file, (LONGCARD)Errors_eFatal, (LONGCARD)Errors_eString, ADR(s));
    }
  }
  FREE_OPEN_ARRAYS
}

void Checks__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    IO__init();
    Strings__init();
    SysError__init();
    System__init();
    Errors__init();

  }
}
