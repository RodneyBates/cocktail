#define DEFINITION_GramYacc

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile GramYacc_yyf;
extern PROC GramYacc_Exit;
extern void GramYacc_ParsSpec ARGS((Tree_tTree t));
extern void GramYacc_BeginGramYacc ARGS(());
extern void GramYacc_CloseGramYacc ARGS(());
extern void GramYacc__init();
