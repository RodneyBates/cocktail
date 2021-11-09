#define DEFINITION_EvalMThree

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern Tree_tTree EvalMThree_Class;
extern IO_tFile EvalMThree_yyf;
extern PROC EvalMThree_Exit;
extern void EvalMThree_EvalInterface ARGS((Tree_tTree t));
extern void EvalMThree_EvalModule ARGS((Tree_tTree t));
extern void EvalMThree_EvalModuleHead ARGS((Tree_tTree t));
extern void EvalMThree_GenEvaluator ARGS((Tree_tTree t));
extern void EvalMThree_BeginEvalMThree ARGS(());
extern void EvalMThree_CloseEvalMThree ARGS(());
extern void EvalMThree__init();
