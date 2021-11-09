#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_IOUtils
#include "IOUtils.h"
#endif




void IOUtils_WriteBackslash
# ifdef __STDC__
(IO_tFile f)
# else
(f)
IO_tFile f;
# endif
{
  IO_WriteC(f, '\\');
}

void IOUtils__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    IO__init();

  }
}
