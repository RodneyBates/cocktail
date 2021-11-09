#define DEFINITION_Optimize

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile Optimize_yyf;
extern PROC Optimize_Exit;
extern void Optimize_Optimize ARGS((Tree_tTree t));
extern void Optimize_RuleProperties ARGS((Tree_tTree yyP1));
extern BOOLEAN Optimize_NeedsTempo ARGS((Tree_tTree yyP5, Tree_tTree *yyP6));
extern BOOLEAN Optimize_NeedsMatch ARGS((Tree_tTree yyP2));
extern BOOLEAN Optimize_NeedsNoFinale ARGS((Tree_tTree yyP7));
extern void Optimize_GetRule ARGS((Tree_tTree yyP8, Tree_tTree *yyP9));
extern void Optimize_BeginOptimize ARGS(());
extern void Optimize_CloseOptimize ARGS(());
extern void Optimize__init();
