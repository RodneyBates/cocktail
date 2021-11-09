#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

static LONGINT i;
static CARDINAL j;
typedef struct S_1 {
    LONGINT A[100000 - 1 + 1];
} t;
static t *p;
static LONGINT s;


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
  DynArray__init();
  IO__init();

  s = 10;
  DynArray_MakeArray(&p, &s, sizeof(LONGINT));
  {
    LONGINT B_1 = 1, B_2 = s;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        p->A[i - 1] = i;
        if (i >= B_2) break;
      }
  }
  for (j = 1; j <= 13; j += 1) {
    DynArray_ExtendArray(&p, &s, sizeof(LONGINT));
    if (p == NIL) {
      IO_WriteS(IO_StdOutput, "Extend Error", 12L);
      IO_WriteNl(IO_StdOutput);
    }
    {
      LONGINT B_3 = s / 2 + 1, B_4 = s;

      if (B_3 <= B_4)
        for (i = B_3;; i += 1) {
          p->A[i - 1] = i;
          if (i >= B_4) break;
        }
    }
    {
      LONGINT B_5 = 1, B_6 = s;

      if (B_5 <= B_6)
        for (i = B_5;; i += 1) {
          if (p->A[i - 1] != i) {
            IO_WriteS(IO_StdOutput, "Error j, i, p^[i] =", 19L);
            IO_WriteI(IO_StdOutput, j, 5);
            IO_WriteLong(IO_StdOutput, i, 5);
            IO_WriteLong(IO_StdOutput, p->A[i - 1], 10);
            IO_WriteNl(IO_StdOutput);
          }
          if (i >= B_6) break;
        }
    }
    IO_WriteS(IO_StdOutput, "j, size = ", 10L);
    IO_WriteI(IO_StdOutput, j, 5);
    IO_WriteLong(IO_StdOutput, s, 10);
    IO_WriteS(IO_StdOutput, " ok", 3L);
    IO_WriteNl(IO_StdOutput);
  }
  IO_CloseIO();
exit(0);
}
