#define DEFINITION_Semantics

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern SHORTCARD Semantics_TypeCount;
extern IO_tFile Semantics_yyf;
extern PROC Semantics_Exit;
extern void Semantics_Semantics ARGS((Tree_tTree t));
extern void Semantics_BeginSemantics ARGS(());
extern void Semantics_CloseSemantics ARGS(());
extern void Semantics__init();
