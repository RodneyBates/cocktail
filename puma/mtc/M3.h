#define DEFINITION_M3

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile M3_yyf;
extern PROC M3_Exit;
extern void M3_Interface ARGS((Tree_tTree t));
extern void M3_Module ARGS((Tree_tTree t));
extern void M3_MacroM3 ARGS((Tree_tTree t));
extern void M3_BeginM3 ARGS(());
extern void M3_CloseM3 ARGS(());
extern void M3__init();
