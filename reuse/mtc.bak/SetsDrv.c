#include "SYSTEM_.h"

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#define max   1000
static Sets_tSet s, t, u;
static CARDINAL i;
static IO_tFile f;


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
  Sets__init();
  IO__init();

  Sets_MakeSet(&s, max);
  Sets_MakeSet(&t, max);
  Sets_MakeSet(&u, max);
  for (i = 2; i <= max; i += 1) {
    Sets_Include(&t, i);
  }
  Sets_AssignEmpty(&s);
  Sets_AssignElmt(&s, 1);
  Sets_Assign(&u, t);
  Sets_Union(&s, t);
  Sets_AssignEmpty(&t);
  for (i = 0; i <= max; i += 2) {
    Sets_Include(&t, i);
  }
  Sets_Difference(&s, t);
  for (i = 0; i <= max; i += 3) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 5) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 7) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 11) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 13) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 17) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 19) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 23) {
    Sets_Exclude(&s, i);
  }
  for (i = 0; i <= max; i += 29) {
    Sets_Exclude(&s, i);
  }
  f = IO_WriteOpen("t", 1L);
  Sets_WriteSet(f, s);
  IO_WriteNl(f);
  IO_WriteClose(f);
  f = IO_ReadOpen("t", 1L);
  Sets_ReadSet(f, &t);
  IO_ReadClose(f);
  Sets_WriteSet(IO_StdOutput, t);
  IO_WriteNl(IO_StdOutput);
  IO_WriteI(IO_StdOutput, Sets_Size(&t), 5);
  IO_WriteI(IO_StdOutput, Sets_Card(&t), 5);
  IO_WriteI(IO_StdOutput, Sets_Minimum(&t), 5);
  IO_WriteI(IO_StdOutput, Sets_Maximum(&t), 5);
  IO_WriteNl(IO_StdOutput);
  Sets_AssignEmpty(&u);
  for (i = 7; i <= max; i += 10) {
    Sets_Include(&u, i);
  }
  Sets_WriteSet(IO_StdOutput, u);
  IO_WriteNl(IO_StdOutput);
  IO_WriteI(IO_StdOutput, Sets_Size(&u), 5);
  IO_WriteI(IO_StdOutput, Sets_Card(&u), 5);
  IO_WriteI(IO_StdOutput, Sets_Minimum(&u), 5);
  IO_WriteI(IO_StdOutput, Sets_Maximum(&u), 5);
  IO_WriteNl(IO_StdOutput);
  Sets_Intersection(&u, t);
  Sets_WriteSet(IO_StdOutput, u);
  IO_WriteNl(IO_StdOutput);
  IO_WriteI(IO_StdOutput, Sets_Size(&u), 5);
  IO_WriteI(IO_StdOutput, Sets_Card(&u), 5);
  IO_WriteI(IO_StdOutput, Sets_Minimum(&u), 5);
  IO_WriteI(IO_StdOutput, Sets_Maximum(&u), 5);
  IO_WriteNl(IO_StdOutput);
  Sets_ReleaseSet(&s);
  Sets_ReleaseSet(&t);
  Sets_ReleaseSet(&u);
  Sets_MakeSet(&s, 10);
  Sets_Include(&s, 3);
  Sets_Include(&s, 7);
  IO_WriteNl(IO_StdOutput);
  IO_WriteS(IO_StdOutput, "enter Size and Set like below! (Size=0 terminates)", 50L);
  IO_WriteNl(IO_StdOutput);
  IO_WriteS(IO_StdOutput, "10 ", 3L);
  Sets_WriteSet(IO_StdOutput, s);
  IO_WriteNl(IO_StdOutput);
  Sets_ReleaseSet(&s);
  for (;;) {
    IO_WriteNl(IO_StdOutput);
    IO_WriteFlush(IO_StdOutput);
    i = IO_ReadI(IO_StdInput);
    if (i == 0) {
      goto EXIT_1;
    }
    Sets_MakeSet(&s, i);
    Sets_ReadSet(IO_StdInput, &s);
    Sets_WriteSet(IO_StdOutput, s);
    IO_WriteS(IO_StdOutput, " Card = ", 8L);
    IO_WriteI(IO_StdOutput, Sets_Card(&s), 0);
    IO_WriteNl(IO_StdOutput);
    Sets_Complement(&s);
    Sets_WriteSet(IO_StdOutput, s);
    IO_WriteS(IO_StdOutput, " Card = ", 8L);
    IO_WriteI(IO_StdOutput, Sets_Card(&s), 0);
    IO_WriteNl(IO_StdOutput);
    Sets_ReleaseSet(&s);
  } EXIT_1:;
  IO_CloseIO();
exit(0);
}
