#include "SYSTEM_.h"

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

static CARDINAL errors;


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
  WriteTok__init();
  Character__init();
  Path__init();
  Checks__init();
  Errors__init();
  Parser__init();
  Idents__init();
  Scanner__init();
  StringMem__init();
  TokenTab__init();

  StringMem_InitStringMemory();
  Idents_InitIdents();
  Errors_BeginErrors();
  Scanner_BeginScanner();
  TokenTab_InitTokenTable();
  errors = Parser_Parser();
  Errors_CloseErrors();
exit(0);
}
