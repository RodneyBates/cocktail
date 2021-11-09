#include "SYSTEM_.h"

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif




BOOLEAN SysError_StatIsBad
# ifdef __STDC__
(INTEGER N)
# else
(N)
INTEGER N;
# endif
{
  return N < 0;
}

void SysError_SysErrorMessageI
# ifdef __STDC__
(INTEGER N, CARDINAL ErrCl, CARDINAL InfCl, ADDRESS Info)
# else
(N, ErrCl, InfCl, Info)
INTEGER N;
CARDINAL ErrCl, InfCl;
ADDRESS Info;
# endif
{
  if (SysError_StatIsBad(N)) {
    Errors_ErrorMessageI((LONGCARD)(ErrNum() + Errors_SysOffset), ErrCl, Positions_NoPosition, InfCl, Info);
  }
}

void SysError_SysErrorMessage
# ifdef __STDC__
(INTEGER N, CARDINAL ErrCl)
# else
(N, ErrCl)
INTEGER N;
CARDINAL ErrCl;
# endif
{
  if (SysError_StatIsBad(N)) {
    Errors_ErrorMessage((LONGCARD)(ErrNum() + Errors_SysOffset), ErrCl, Positions_NoPosition);
  }
}

void SysError__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Errors__init();
    Positions__init();
    System__init();

  }
}
