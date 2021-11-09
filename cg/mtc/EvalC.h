#define DEFINITION_EvalC

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern Tree_tTree EvalC_Class;
extern IO_tFile EvalC_yyf;
extern PROC EvalC_Exit;
extern void EvalC_EvalDefC ARGS((Tree_tTree t));
extern void EvalC_EvalImplC ARGS((Tree_tTree t));
extern void EvalC_EvalImplHead ARGS((Tree_tTree t));
extern void EvalC_GenEvaluator ARGS((Tree_tTree t));
extern void EvalC_BeginEvalC ARGS(());
extern void EvalC_CloseEvalC ARGS(());
extern void EvalC__init();
