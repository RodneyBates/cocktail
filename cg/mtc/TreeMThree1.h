#define DEFINITION_TreeMThree1

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile TreeMThree1_yyf;
extern PROC TreeMThree1_Exit;
extern void TreeMThree1_TreeInterface ARGS((Tree_tTree t));
extern void TreeMThree1_TreeModule ARGS((Tree_tTree t));
extern void TreeMThree1_ImportList ARGS((Tree_tTree t));
extern void TreeMThree1_NodeType ARGS((Tree_tTree t));
extern void TreeMThree1_BeginTreeMThree1 ARGS(());
extern void TreeMThree1_CloseTreeMThree1 ARGS(());
extern void TreeMThree1__init();
