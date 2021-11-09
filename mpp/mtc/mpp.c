#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

static CARDINAL ErrorCount;


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
  IO__init();
  Parser__init();
  Path__init();
  System__init();

  Path_InsertPath(Parser_ParsTabName.A, 129L);
  ErrorCount = Parser_Parser();
  Parser_CloseParser();
  IO_CloseIO();
  if (ErrorCount > 0) {
    Exit(1L);
  } else {
    Exit(0L);
  }
exit(0);
}
