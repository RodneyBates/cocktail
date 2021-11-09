#define DEFINITION_TreeC1

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#define TreeC1_BSS   8
extern IO_tFile TreeC1_yyf;
extern PROC TreeC1_Exit;
extern void TreeC1_TreeDefC ARGS((Tree_tTree t));
extern void TreeC1_TreeImplC ARGS((Tree_tTree t));
extern void TreeC1_BeginTreeC1 ARGS(());
extern void TreeC1_CloseTreeC1 ARGS(());
extern void TreeC1__init();
