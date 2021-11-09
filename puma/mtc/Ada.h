#define DEFINITION_Ada

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile Ada_yyf;
extern PROC Ada_Exit;
extern void Ada_PackSpec ARGS((Tree_tTree t));
extern void Ada_PackBody ARGS((Tree_tTree t));
extern void Ada_MacroAda ARGS((Tree_tTree t));
extern void Ada_BeginAda ARGS(());
extern void Ada_CloseAda ARGS(());
extern void Ada__init();
