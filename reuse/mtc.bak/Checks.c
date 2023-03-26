#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif




void Checks_ErrorCheck
# ifdef __STDC__
(CHAR s[], LONGCARD O_1, INTEGER n)
# else
(s, O_1, n)
CHAR s[];
LONGCARD O_1;
INTEGER n;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s, O_1, CHAR)
  if (n < 0) {
    IO_WriteS(IO_StdError, s, O_1);
    IO_WriteS(IO_StdError, " : ", 3L);
    IO_WriteI(IO_StdError, n, 2);
    IO_WriteS(IO_StdError, ", errno	= ", 10L);
    IO_WriteI(IO_StdError, ErrNum(), 2);
    IO_WriteNl(IO_StdError);
  }
  FREE_OPEN_ARRAYS
}

void Checks__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    System__init();

  }
}
