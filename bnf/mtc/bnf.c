#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_MakeBNF
#include "MakeBNF.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

static CHAR ErrorTab [] = "ErrorTab";
static CARDINAL errors;
static BOOLEAN GoOn;
static INTEGER Status;


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
  ArgCheck__init();
  Errors__init();
  IO__init();
  MakeBNF__init();
  Parser__init();
  Path__init();
  Scanner__init();
  StringMem__init();
  Idents__init();
  System__init();
  TokenTab__init();

  StringMem_InitStringMemory();
  Idents_InitIdents();
  (void)strncpy((char *)Errors_ErrorTable.A, (char *)ErrorTab, sizeof(Errors_ErrorTable.A));
  Path_InsertPath(Errors_ErrorTable.A, 256L);
  Errors_BeginErrors();
  ArgCheck_ArgCheck();
  GoOn = ArgCheck_Generate;
  if (GoOn) {
    TokenTab_InitTokenTable();
    Scanner_BeginScanner();
    errors = Parser_Parser();
    GoOn = Errors_ErrorCount.A[Errors_eError] == 0;
  }
  if (GoOn) {
    MakeBNF_MakeBnf((System_tFile)IO_StdOutput);
    Status = 0;
  } else {
    Status = 1;
  }
  Errors_CloseErrors();
  IO_CloseIO();
  Exit(Status);
exit(0);
}
