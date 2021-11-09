#define DEFINITION_TreeMod2

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

extern Tree_tTree TreeMod2_Iterator;
extern void TreeMod2_WriteLine ARGS((Positions_tPosition Line));
extern IO_tFile TreeMod2_yyf;
extern PROC TreeMod2_Exit;
extern void TreeMod2_TreeIO ARGS((Tree_tTree t));
extern void TreeMod2_GetIterator ARGS((Tree_tTree t));
extern void TreeMod2_BeginTreeMod2 ARGS(());
extern void TreeMod2_CloseTreeMod2 ARGS(());
extern void TreeMod2__init();
