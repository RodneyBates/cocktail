#define DEFINITION_Semantics

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern SHORTCARD Semantics_TypeCount;
extern Sets_tSet Semantics_TypeNames, Semantics_UserTypes;
extern Tree_tTree Semantics_IdentifyVar ARGS((Tree_tTree node, Idents_tIdent i));
extern Tree_tTree Semantics_LookupClass ARGS((Tree_tTree Classes, CARDINAL i));
extern IO_tFile Semantics_yyf;
extern PROC Semantics_Exit;
extern void Semantics_Semantics ARGS((Tree_tTree t));
extern void Semantics_RemoveTreeTypes ARGS((Tree_tTree t));
extern void Semantics_BeginSemantics ARGS(());
extern void Semantics_CloseSemantics ARGS(());
extern void Semantics__init();
