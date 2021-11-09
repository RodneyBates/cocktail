#include "SYSTEM_.h"

#ifndef DEFINITION_Convert
#include "Convert.h"
#endif

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Listing
#include "Listing.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Stack
#include "Stack.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif



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
  Convert__init();
  Character__init();
  Checks__init();
  Errors__init();
  Listing__init();
  Path__init();
  Queues__init();
  Stack__init();
  SysError__init();

exit(0);
}
