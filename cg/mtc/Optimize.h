#define DEFINITION_Optimize

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern SHORTCARD Optimize_ChildrenDyn, Optimize_ChildrenIn, Optimize_AttributeIn, Optimize_AttributeOut, Optimize_AttributeTree, Optimize_AttributeParam, Optimize_AttributeVar, Optimize_AttributeDemand, Optimize_AttributeStack;
extern IO_tFile Optimize_yyf;
extern PROC Optimize_Exit;
extern void Optimize_LifeTime1 ARGS((Tree_tTree t));
extern void Optimize_LifeTime3 ARGS((Tree_tTree t));
extern void Optimize_BeginOptimize ARGS(());
extern void Optimize_CloseOptimize ARGS(());
extern void Optimize__init();
