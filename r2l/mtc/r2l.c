#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

static struct S_1 {
    CHAR A[127 + 1];
} SourceFile, Argument;
static Strings_tString RexLib, FileNameS, Path;
static SHORTCARD i, j, n;
static BOOLEAN h;
static CHAR ch;


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
  IO__init();
  StdIO__init();
  Scanner__init();
  Parser__init();

  h = FALSE;
  n = 0;
  Strings_AssignEmpty(&RexLib);
  SourceFile.A[0] = '\0';
  {
    SHORTCARD B_1 = 1, B_2 = GetArgCount() - 1;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        GetArgument((LONGINT)i, Argument.A, 128L);
        if (Argument.A[0] == '-') {
          if (Argument.A[1] == 'l') {
            Strings_AssignEmpty(&RexLib);
            j = 2;
            for (;;) {
              ch = Argument.A[j];
              if (ch == '\0') {
                goto EXIT_1;
              }
              Strings_Append(&RexLib, ch);
              INC(j);
            } EXIT_1:;
            Strings_Append(&RexLib, '/');
          } else {
            j = 0;
            for (;;) {
              INC(j);
              ch = Argument.A[j];
              switch (ch) {
              case '\0':;
                goto EXIT_2;
                break;
              case '?':;
                h = TRUE;
                break;
              case 'h':;
                h = TRUE;
                break;
              default :
                break;
              }
            } EXIT_2:;
          }
        } else if (Argument.A[0] == '?') {
          h = TRUE;
        } else {
          j = 0;
          do {
            ch = Argument.A[j];
            SourceFile.A[j] = ch;
            INC(j);
          } while (!(ch == '\0'));
        }
        if (i >= B_2) break;
      }
  }
  if (h) {
    StdIO_WriteS((STRING)"usage: r2l [-options] [file]", 28L);
    StdIO_WriteNl();
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" -h print help information", 26L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" -ldir specify the directory dir where r2l finds its table and data files", 73L);
    StdIO_WriteNl();
  } else {
    Strings_ArrayToString(Scanner_ScanTabName.A, 128L, &FileNameS);
    Strings_Assign(&Path, &RexLib);
    Strings_Concatenate(&Path, &FileNameS);
    Strings_Append(&Path, '\0');
    Strings_StringToArray(&Path, Scanner_ScanTabName.A, 128L);
    Strings_ArrayToString(Parser_ParsTabName.A, 129L, &FileNameS);
    Strings_Assign(&Path, &RexLib);
    Strings_Concatenate(&Path, &FileNameS);
    Strings_Append(&Path, '\0');
    Strings_StringToArray(&Path, Parser_ParsTabName.A, 129L);
    if (SourceFile.A[0] != '\0') {
      Scanner_BeginFile(SourceFile.A, 128L);
    }
    Scanner_BeginScanner();
    n = Parser_Parser();
  }
  IO_CloseIO();
  Exit(0L);
exit(0);
}
