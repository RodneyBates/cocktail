#define DEFINITION_EvalMod2

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile EvalMod2_yyf;
extern PROC EvalMod2_Exit;
extern void EvalMod2_EvalImplMod ARGS((Tree_tTree t));
extern void EvalMod2_BeginEvalMod2 ARGS(());
extern void EvalMod2_CloseEvalMod2 ARGS(());
extern void EvalMod2__init();
