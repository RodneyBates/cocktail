#define DEFINITION_EvalMod3

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile EvalMod3_yyf;
extern PROC EvalMod3_Exit;
extern void EvalMod3_EvalImplMod ARGS((Tree_tTree t));
extern INTEGER EvalMod3_ToBit0 ARGS((Tree_tTree yyP2, INTEGER yyP1));
extern void EvalMod3_BeginEvalMod3 ARGS(());
extern void EvalMod3_CloseEvalMod3 ARGS(());
extern void EvalMod3__init();
