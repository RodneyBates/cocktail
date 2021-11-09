#define DEFINITION_GramC

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile GramC_yyf;
extern PROC GramC_Exit;
extern void GramC_ParsSpec ARGS((Tree_tTree t));
extern void GramC_ScanSpec ARGS((Tree_tTree t));
extern void GramC_BeginGramC ARGS(());
extern void GramC_CloseGramC ARGS(());
extern void GramC__init();
