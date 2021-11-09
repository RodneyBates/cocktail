#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

static IO_tFile f, g;
static INTEGER i, j;
static CHAR c;
static struct S_1 {
    CHAR A[200 - 1 + 1];
} b;
static REAL r;


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

  f = IO_ReadOpen("Makefile", 8L);
  g = IO_WriteOpen("t", 1L);
  for (i = 1; i <= 200; i += 1) {
    c = IO_ReadC(f);
    IO_WriteC(IO_StdOutput, c);
    IO_WriteC(g, c);
  }
  while (!IO_EndOfFile(f)) {
    i = IO_Read(f, ADR(b), 200);
    j = IO_Write(IO_StdOutput, ADR(b), i);
    j = IO_Write(g, ADR(b), i);
  }
  IO_ReadClose(f);
  IO_WriteClose(g);
  IO_WriteNl(IO_StdOutput);
  IO_WriteS(IO_StdOutput, "enter integers, 99 will stop", 28L);
  IO_WriteNl(IO_StdOutput);
  do {
    IO_WriteFlush(IO_StdOutput);
    i = IO_ReadI(IO_StdInput);
    IO_WriteI(IO_StdOutput, i, 10);
    IO_WriteShort(IO_StdOutput, i, 10);
    IO_WriteLong(IO_StdOutput, i, 10);
    IO_WriteCard(IO_StdOutput, i, 10);
    c = IO_ReadC(IO_StdInput);
    IO_WriteC(IO_StdOutput, ' ');
    IO_WriteC(IO_StdOutput, c);
    IO_WriteNl(IO_StdOutput);
  } while (!(i == 99));
  IO_WriteS(IO_StdOutput, "enter reals, 99 will stop", 25L);
  IO_WriteNl(IO_StdOutput);
  do {
    IO_WriteFlush(IO_StdOutput);
    r = IO_ReadR(IO_StdInput);
    IO_WriteR(IO_StdOutput, r, 2, 12, 3);
    IO_WriteC(IO_StdOutput, ',');
    IO_WriteR(IO_StdOutput, r, 2, 3, 2);
    IO_WriteC(IO_StdOutput, ',');
    IO_WriteR(IO_StdOutput, r, 4, 3, 1);
    IO_WriteC(IO_StdOutput, ',');
    IO_WriteR(IO_StdOutput, r, 8, 3, 0);
    IO_WriteC(IO_StdOutput, ',');
    IO_WriteR(IO_StdOutput, r, 8, 1, 0);
    IO_WriteC(IO_StdOutput, ',');
    IO_WriteR(IO_StdOutput, r, 8, 0, 0);
    IO_WriteC(IO_StdOutput, ',');
    IO_WriteNl(IO_StdOutput);
  } while (!(98.9 <= r && r <= 99.1));
  IO_WriteClose(IO_StdOutput);
exit(0);
}
