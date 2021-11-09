#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

static CARDINAL ErrorCount;
static CARDINAL i, j;
static struct S_1 {
    CHAR A[127 + 1];
} Argument;
static CHAR ch;
static Strings_tString String, FileNameS, Lib;


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
  System__init();
  Strings__init();
  Scanner__init();
  Parser__init();
  Errors__init();
  IO__init();

  Strings_AssignEmpty(&Lib);
  {
    LONGCARD B_1 = 1, B_2 = GetArgCount() - 1;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        GetArgument(i, Argument.A, 128L);
        if (Argument.A[0] == '-' && Argument.A[1] == 'l') {
          j = 2;
          for (;;) {
            ch = Argument.A[j];
            if (ch == '\0') {
              goto EXIT_1;
            }
            Strings_Append(&Lib, ch);
            INC(j);
          } EXIT_1:;
          Strings_Append(&Lib, '/');
        }
        if (i >= B_2) break;
      }
  }
  Strings_ArrayToString(Scanner_ScanTabName.A, 128L, &FileNameS);
  Strings_Assign(&String, &Lib);
  Strings_Concatenate(&String, &FileNameS);
  Strings_Append(&String, '\0');
  Strings_StringToArray(&String, Scanner_ScanTabName.A, 128L);
  Strings_ArrayToString(Parser_ParsTabName.A, 129L, &FileNameS);
  Strings_Assign(&String, &Lib);
  Strings_Concatenate(&String, &FileNameS);
  Strings_Append(&String, '\0');
  Strings_StringToArray(&String, Parser_ParsTabName.A, 129L);
  ErrorCount = Parser_Parser();
  Parser_CloseParser();
  IO_CloseIO();
  if (Errors_NumberOfErrors() == 0) {
    Exit(0);
  } else {
    Exit(1);
  }
exit(0);
}
