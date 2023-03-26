#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

static Relations_tRelation r1, r2;
static INTEGER s;
static CHAR c;
static Sets_tSet s2;


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
  Sets__init();
  Relations__init();

  Relations_MakeRelation(&r2, 10, 20);
  Relations_Include(&r2, 0, 9);
  Relations_Include(&r2, 9, 1);
  Relations_Include(&r2, 1, 8);
  Relations_Include(&r2, 8, 0);
  Relations_WriteRelation(IO_StdOutput, r2);
  IO_WriteNl(IO_StdOutput);
  Relations_Closure(&r2);
  Relations_WriteRelation(IO_StdOutput, r2);
  IO_WriteNl(IO_StdOutput);
  Relations_ReleaseRelation(&r2);
  Relations_MakeRelation(&r1, 10, 20);
  Relations_Include(&r1, 2, 3);
  Relations_Include(&r1, 3, 4);
  IO_WriteNl(IO_StdOutput);
  IO_WriteS(IO_StdOutput, "enter Size and Relation like below! (Size=0 terminates)", 55L);
  IO_WriteNl(IO_StdOutput);
  IO_WriteI(IO_StdOutput, 4, 3);
  IO_WriteS(IO_StdOutput, " ", 1L);
  Relations_WriteRelation(IO_StdOutput, r1);
  IO_WriteNl(IO_StdOutput);
  Relations_ReleaseRelation(&r1);
  for (;;) {
    IO_WriteNl(IO_StdOutput);
    IO_WriteFlush(IO_StdOutput);
    s = IO_ReadI(IO_StdInput);
    if (s == 0) {
      goto EXIT_1;
    }
    Sets_MakeSet(&s2, s);
    Relations_MakeRelation(&r2, s, s);
    Relations_ReadRelation(IO_StdInput, &r2);
    Relations_WriteRelation(IO_StdOutput, r2);
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Reflexive	= ", 12L);
    IO_WriteB(IO_StdOutput, Relations_IsReflexive(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Symmetric	= ", 12L);
    IO_WriteB(IO_StdOutput, Relations_IsSymmetric(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Transitive	= ", 13L);
    IO_WriteB(IO_StdOutput, Relations_IsTransitive(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Equivalence	= ", 14L);
    IO_WriteB(IO_StdOutput, Relations_IsEquivalence(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "HasReflexive	= ", 15L);
    IO_WriteB(IO_StdOutput, Relations_HasReflexive(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Cyclic		= ", 10L);
    IO_WriteB(IO_StdOutput, Relations_IsCyclic(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Card		= ", 8L);
    IO_WriteI(IO_StdOutput, Relations_Card(&r2), 1);
    IO_WriteNl(IO_StdOutput);
    Relations_GetCyclics(r2, &s2);
    IO_WriteS(IO_StdOutput, "Cyclics		= ", 11L);
    Sets_WriteSet(IO_StdOutput, s2);
    IO_WriteNl(IO_StdOutput);
    Relations_Closure(&r2);
    Relations_WriteRelation(IO_StdOutput, r2);
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Reflexive	= ", 12L);
    IO_WriteB(IO_StdOutput, Relations_IsReflexive(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Symmetric	= ", 12L);
    IO_WriteB(IO_StdOutput, Relations_IsSymmetric(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Transitive	= ", 13L);
    IO_WriteB(IO_StdOutput, Relations_IsTransitive(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Equivalence	= ", 14L);
    IO_WriteB(IO_StdOutput, Relations_IsEquivalence(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "HasReflexive	= ", 15L);
    IO_WriteB(IO_StdOutput, Relations_HasReflexive(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Cyclic		= ", 10L);
    IO_WriteB(IO_StdOutput, Relations_IsCyclic(r2));
    IO_WriteNl(IO_StdOutput);
    IO_WriteS(IO_StdOutput, "Card		= ", 8L);
    IO_WriteI(IO_StdOutput, Relations_Card(&r2), 1);
    IO_WriteNl(IO_StdOutput);
    Relations_GetCyclics(r2, &s2);
    IO_WriteS(IO_StdOutput, "Cyclics		= ", 11L);
    Sets_WriteSet(IO_StdOutput, s2);
    IO_WriteNl(IO_StdOutput);
    Relations_ReleaseRelation(&r2);
    Sets_ReleaseSet(&s2);
  } EXIT_1:;
  IO_CloseIO();
exit(0);
}
