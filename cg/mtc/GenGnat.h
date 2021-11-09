#define DEFINITION_GenGnat

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile GenGnat_yyf;
extern PROC GenGnat_Exit;
extern void GenGnat_GnatModule ARGS((Tree_tTree t));
extern void GenGnat_BeginGenGnat ARGS(());
extern void GenGnat_CloseGenGnat ARGS(());
extern void GenGnat__init();
