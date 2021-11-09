#define DEFINITION_GramMod

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile GramMod_yyf;
extern PROC GramMod_Exit;
extern void GramMod_ParsSpec ARGS((Tree_tTree t));
extern void GramMod_ScanSpec ARGS((Tree_tTree t));
extern void GramMod_BeginGramMod ARGS(());
extern void GramMod_CloseGramMod ARGS(());
extern void GramMod__init();
