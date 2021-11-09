#define DEFINITION_TreeAda1

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#define TreeAda1_BSS   32
extern IO_tFile TreeAda1_yyf;
extern PROC TreeAda1_Exit;
extern void TreeAda1_TreePackSpec ARGS((Tree_tTree t));
extern void TreeAda1_TreePackBody ARGS((Tree_tTree t));
extern void TreeAda1_BeginTreeAda1 ARGS(());
extern void TreeAda1_CloseTreeAda1 ARGS(());
extern void TreeAda1__init();
