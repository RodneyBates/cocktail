#define DEFINITION_EvalC2

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile EvalC2_yyf;
extern PROC EvalC2_Exit;
extern void EvalC2_EvalImplC ARGS((Tree_tTree t));
extern void EvalC2_BeginEvalC2 ARGS(());
extern void EvalC2_CloseEvalC2 ARGS(());
extern void EvalC2__init();
