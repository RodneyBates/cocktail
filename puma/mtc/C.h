#define DEFINITION_C

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile C_yyf;
extern PROC C_Exit;
extern void C_DefC ARGS((Tree_tTree t));
extern void C_ImplC ARGS((Tree_tTree t));
extern void C_MacroC ARGS((Tree_tTree t));
extern void C_BeginC ARGS(());
extern void C_CloseC ARGS(());
extern void C__init();
