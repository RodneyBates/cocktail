#include "SYSTEM_.h"

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

static ADDRESS p1, p2, p3, p4;
static CARDINAL i;
static LONGINT small, best, notbest, large;
static ADDRESS AllocPrint ARGS((LONGINT n));


static ADDRESS AllocPrint
# ifdef __STDC__
(LONGINT n)
# else
(n)
LONGINT n;
# endif
{
  ADDRESS a;

  a = Memory_Alloc(n);
  IO_WriteS(IO_StdOutput, "Alloc:  n = ", 12L);
  IO_WriteLong(IO_StdOutput, n, 10);
  IO_WriteS(IO_StdOutput, ", ADR = ", 8L);
  IO_WriteN(IO_StdOutput, (INTEGER)a, 8, 16);
  IO_WriteNl(IO_StdOutput);
  return a;
}

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
  Memory__init();
  IO__init();

  for (i = 0; i <= 62; i += 1) {
    p1 = AllocPrint(i);
    p2 = AllocPrint(i);
    Memory_Free(i, p1);
    Memory_Free(i, p2);
    p3 = AllocPrint(i);
    p4 = AllocPrint(i);
    if (p3 != p2) {
      IO_WriteS(IO_StdOutput, "Alloc/Free small not inverse ", 29L);
      IO_WriteI(IO_StdOutput, i, 10);
      IO_WriteNl(IO_StdOutput);
    }
    if (p4 != p1) {
      IO_WriteS(IO_StdOutput, "Alloc/Free small not inverse ", 29L);
      IO_WriteI(IO_StdOutput, i, 10);
      IO_WriteNl(IO_StdOutput);
    }
  }
  small = 80;
  best = 96;
  notbest = 112;
  large = 128;
  for (;;) {
    for (i = 7; i <= 24; i += 1) {
      IO_WriteS(IO_StdOutput, "        i = ", 12L);
      IO_WriteI(IO_StdOutput, i, 10);
      IO_WriteNl(IO_StdOutput);
      p1 = AllocPrint(small);
      p2 = AllocPrint(best);
      p3 = AllocPrint(notbest);
      p4 = AllocPrint(large);
      if (p1 == NIL || p2 == NIL || p3 == NIL || p4 == NIL) {
        goto EXIT_1;
      }
      Memory_Free(large, p4);
      Memory_Free(notbest, p3);
      Memory_Free(best, p2);
      Memory_Free(small, p1);
      p1 = AllocPrint(best);
      if (p1 != p2) {
        IO_WriteS(IO_StdOutput, "Alloc/Free large not inverse ", 29L);
        IO_WriteI(IO_StdOutput, i, 10);
        IO_WriteNl(IO_StdOutput);
      }
      p1 = AllocPrint(best);
      if (p1 != p3) {
        IO_WriteS(IO_StdOutput, "Alloc/Free large not inverse ", 29L);
        IO_WriteI(IO_StdOutput, i, 10);
        IO_WriteNl(IO_StdOutput);
      }
      p1 = AllocPrint(best);
      if (p1 != p4) {
        IO_WriteS(IO_StdOutput, "Alloc/Free large not inverse ", 29L);
        IO_WriteI(IO_StdOutput, i, 10);
        IO_WriteNl(IO_StdOutput);
      }
      INC1(small, small);
      INC1(best, best);
      INC1(notbest, notbest);
      INC1(large, large);
    }
  } EXIT_1:;
  IO_WriteNl(IO_StdOutput);
  IO_WriteS(IO_StdOutput, "Memory used: ", 13L);
  IO_WriteI(IO_StdOutput, Memory_MemoryUsed, 10);
  IO_WriteNl(IO_StdOutput);
  IO_CloseIO();
exit(0);
}
