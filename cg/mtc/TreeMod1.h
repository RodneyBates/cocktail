#define DEFINITION_TreeMod1

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#define TreeMod1_BSS   32
extern IO_tFile TreeMod1_yyf;
extern PROC TreeMod1_Exit;
extern void TreeMod1_TreeDefMod ARGS((Tree_tTree t));
extern void TreeMod1_TreeImplMod ARGS((Tree_tTree t));
extern void TreeMod1_ImportList ARGS((Tree_tTree t));
extern void TreeMod1_BeginTreeMod1 ARGS(());
extern void TreeMod1_CloseTreeMod1 ARGS(());
extern void TreeMod1__init();
