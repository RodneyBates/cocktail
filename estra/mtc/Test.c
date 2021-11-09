#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Times
#include "Times.h"
#endif

#ifndef DEFINITION_Times
#include "Times.h"
#endif

#ifndef DEFINITION_Test
#include "Test.h"
#endif


static LONGINT time;


void Test_WriteTest
# ifdef __STDC__
()
# else
()
# endif
{
  StdIO_WriteS((STRING)"MaxIdent: ", 10L);
  StdIO_WriteI((LONGINT)Idents_MaxIdent(), 1L);
  StdIO_WriteNl();
  StdIO_WriteI((LONGINT)(Memory_MemoryUsed / 1024), 4L);
  StdIO_WriteS((STRING)".", 1L);
  StdIO_WriteI((LONGINT)(Memory_MemoryUsed % 1024 * 10 / 1024), 1L);
  StdIO_WriteS((STRING)"  kBytes   memory used", 22L);
  StdIO_WriteNl();
  time = Times_CpuTime();
  StdIO_WriteI(time / 1000, 4L);
  StdIO_WriteS((STRING)".", 1L);
  StdIO_WriteI(time % 1000 / 10, 2L);
  StdIO_WriteS((STRING)" s        CPU time used", 23L);
  StdIO_WriteNl();
}

void Test_WriteStepTime
# ifdef __STDC__
(CHAR s[], LONGCARD O_1)
# else
(s, O_1)
CHAR s[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s, O_1, CHAR)
  if (ArgCheck_TEST) {
    Times_WriteStepTime(s, O_1);
  }
  FREE_OPEN_ARRAYS
}

void Test__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    ArgCheck__init();
    Idents__init();
    Memory__init();
    StdIO__init();
    Times__init();
    Times__init();

  }
}
