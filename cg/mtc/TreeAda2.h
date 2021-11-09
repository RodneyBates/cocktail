#define DEFINITION_TreeAda2

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

extern Tree_tTree TreeAda2_Iterator;
extern void TreeAda2_WriteLine ARGS((Positions_tPosition Line));
extern IO_tFile TreeAda2_yyf;
extern PROC TreeAda2_Exit;
extern void TreeAda2_TreeIO ARGS((Tree_tTree t));
extern void TreeAda2_TreeIOInit ARGS((Tree_tTree t));
extern void TreeAda2_GetIterator ARGS((Tree_tTree t));
extern void TreeAda2_BeginTreeAda2 ARGS(());
extern void TreeAda2_CloseTreeAda2 ARGS(());
extern void TreeAda2__init();
