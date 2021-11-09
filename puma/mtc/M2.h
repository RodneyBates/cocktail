#define DEFINITION_M2

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile M2_yyf;
extern PROC M2_Exit;
extern void M2_DefMod ARGS((Tree_tTree t));
extern void M2_ImplMod ARGS((Tree_tTree t));
extern void M2_MacroMod ARGS((Tree_tTree t));
extern void M2_BeginM2 ARGS(());
extern void M2_CloseM2 ARGS(());
extern void M2__init();
