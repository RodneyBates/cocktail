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

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif


static struct S_1 {
    CHAR A[15 + 1];
} DevNull;


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
    *file = IO_ReadOpen(DevNull.A, 16L);
    if (SysError_StatIsBad(*file)) {
      Strings_ArrayToString(DevNull.A, 16L, &s);
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
    *file = IO_WriteOpen(DevNull.A, 16L);
    if (SysError_StatIsBad(*file)) {
      Strings_ArrayToString(DevNull.A, 16L, &s);
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
    Errors__init();

    (void)strncpy((char *)DevNull.A, "/dev/null", sizeof(DevNull.A));
  }
}
