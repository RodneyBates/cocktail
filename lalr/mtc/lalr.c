#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Check
#include "Check.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

#ifndef DEFINITION_Infos
#include "Infos.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Lookahead
#include "Lookahead.h"
#endif

#ifndef DEFINITION_LR
#include "LR.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Reduce
#include "Reduce.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
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

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

static CHAR ErrorTab [] = "ErrorTab";
static INTEGER errors;
static INTEGER Status;
static BOOLEAN GoOn;


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
  Automaton__init();
  Check__init();
  Errors__init();
  Gen__init();
  Infos__init();
  IO__init();
  Lookahead__init();
  LR__init();
  Parser__init();
  Path__init();
  Reduce__init();
  Scanner__init();
  Strings__init();
  StringMem__init();
  Idents__init();
  System__init();
  TokenTab__init();
  WriteTok__init();

  (void)strncpy((char *)Errors_ErrorTable.A, (char *)ErrorTab, sizeof(Errors_ErrorTable.A));
  Path_InsertPath(Errors_ErrorTable.A, 256L);
  StringMem_InitStringMemory();
  Idents_InitIdents();
  Errors_BeginErrors();
  ArgCheck_ArgCheck();
  GoOn = ArgCheck_Generate;
  if (GoOn) {
    Gen_GenDefaultActions();
    TokenTab_InitTokenTable();
    Scanner_BeginScanner();
    errors = Parser_Parser();
    ArgCheck_GenerateSupport();
    GoOn = Errors_ErrorCount.A[Errors_eError] == 0;
  }
  if (GoOn) {
    Automaton_InitAutomaton();
    GoOn = Automaton_IsBnf;
  }
  if (GoOn) {
    Reduce_TestReduced();
    GoOn = Reduce_Reduced;
  }
  if (GoOn) {
    LR_ComputeLR();
  }
  if (GoOn) {
    Lookahead_ComputeLALR();
    GoOn = Lookahead_NoConflict;
  }
  if (GoOn) {
    Gen_GenCode(ArgCheck_Pars, ArgCheck_Def);
    Status = 0;
  } else {
    Status = 1;
  }
  Errors_CloseErrors();
  if (ArgCheck_TEST && GoOn) {
    Infos_WriteInfo((System_tFile)IO_StdOutput);
  }
  IO_CloseIO();
  Exit(Status);
exit(0);
}
