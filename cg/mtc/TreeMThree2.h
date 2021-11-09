#define DEFINITION_TreeMThree2

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

extern Tree_tTree TreeMThree2_Iterator;
extern void TreeMThree2_WriteLine ARGS((Positions_tPosition Line));
extern IO_tFile TreeMThree2_yyf;
extern PROC TreeMThree2_Exit;
extern void TreeMThree2_TreeIO ARGS((Tree_tTree t));
extern void TreeMThree2_TreeIOInit ARGS((Tree_tTree t));
extern void TreeMThree2_GetIterator ARGS((Tree_tTree t));
extern void TreeMThree2_BeginTreeMThree2 ARGS(());
extern void TreeMThree2_CloseTreeMThree2 ARGS(());
extern void TreeMThree2__init();
