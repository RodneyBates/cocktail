#define DEFINITION_Order

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern struct Order_1 {
    Tree_tTree A[10000 + 1];
} *Order_IndexToClass;
extern IO_tFile Order_yyf;
extern PROC Order_Exit;
extern void Order_Order ARGS((Tree_tTree t));
extern void Order_WriteOrderDecl ARGS((Tree_tTree t));
extern void Order_WriteOrderEval ARGS((Tree_tTree t));
extern void Order_WriteVisitSequence ARGS((Tree_tTree t));
extern void Order_BeginOrder ARGS(());
extern void Order_CloseOrder ARGS(());
extern void Order__init();
