#include "SYSTEM_.h"

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

static INTEGER Token;


extern int  parameters_argc;
extern char **parameters_argv;
extern char **parameters_envp;
# ifdef __STDC__
void main(int argc, char *argv[], char *envp[])
# else
void main(argc, argv, envp)
  int argc;
  char *argv[], *envp[];
# endif
{
parameters_argc = argc;
parameters_argv = argv;
parameters_envp = envp;
  Scanner__init();
  IO__init();
  System__init();

  Scanner_BeginScanner();
  do {
    Token = Scanner_GetToken();
  } while (!(Token == Scanner_EofToken));
  Scanner_CloseScanner();
  IO_CloseIO();
  Exit(0L);
exit(0);
}
