#define DEFINITION_TreeC2

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

extern Tree_tTree TreeC2_Iterator;
extern void TreeC2_WriteLine ARGS((Positions_tPosition Line));
extern IO_tFile TreeC2_yyf;
extern PROC TreeC2_Exit;
extern void TreeC2_TreeIO ARGS((Tree_tTree t));
extern void TreeC2_GetIterator ARGS((Tree_tTree t));
extern void TreeC2_BeginTreeC2 ARGS(());
extern void TreeC2_CloseTreeC2 ARGS(());
extern void TreeC2__init();
