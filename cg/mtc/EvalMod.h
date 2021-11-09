#define DEFINITION_EvalMod

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern Tree_tTree EvalMod_Class;
extern IO_tFile EvalMod_yyf;
extern PROC EvalMod_Exit;
extern void EvalMod_EvalDefMod ARGS((Tree_tTree t));
extern void EvalMod_EvalImplMod ARGS((Tree_tTree t));
extern void EvalMod_EvalImplHead ARGS((Tree_tTree t));
extern void EvalMod_GenEvaluator ARGS((Tree_tTree t));
extern void EvalMod_BeginEvalMod ARGS(());
extern void EvalMod_CloseEvalMod ARGS(());
extern void EvalMod__init();
