#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

static struct S_1 {
    CHAR A[1023 + 1];
} b;
static System_tFile f;
static INTEGER n;


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
  Checks__init();

  f = OpenInput("Makefile", 8L);
  Checks_ErrorCheck("OpenInput", 9L, f);
  n = Read(f, ADR(b), 1024);
  Checks_ErrorCheck("Read", 4L, n);
  Close(f);
  f = OpenOutput("t", 1L);
  Checks_ErrorCheck("OpenOutput", 10L, f);
  n = Write(f, ADR(b), 1024);
  Checks_ErrorCheck("Write", 5L, n);
  Close(f);
exit(0);
}
