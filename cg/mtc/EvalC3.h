#define DEFINITION_EvalC3

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile EvalC3_yyf;
extern PROC EvalC3_Exit;
extern void EvalC3_EvalImplC ARGS((Tree_tTree t));
extern INTEGER EvalC3_ToBit0 ARGS((Tree_tTree yyP2, INTEGER yyP1));
extern void EvalC3_BeginEvalC3 ARGS(());
extern void EvalC3_CloseEvalC3 ARGS(());
extern void EvalC3__init();
