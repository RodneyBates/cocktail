#define DEFINITION_Table

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern void Table_InitTable ARGS(());
extern void Table_SetExpr ARGS((Idents_tIdent nonterm, Tree_tTree expr));
extern Tree_tTree Table_Expr ARGS((Idents_tIdent nonterm));
extern void Table_SetLeaf ARGS((Idents_tIdent nonterm, Idents_tIdent leaf));
extern void Table_Leafs ARGS((Idents_tIdent nonterm, Sets_tSet *leafs));
extern void Table_SetFirst ARGS((Idents_tIdent nonterm, Sets_tSet first));
extern void Table_First ARGS((Idents_tIdent nonterm, Sets_tSet *first));
extern void Table_SetFollow ARGS((Idents_tIdent nonterm, Sets_tSet follow));
extern void Table_ExtendFollow ARGS((Idents_tIdent nonterm, Sets_tSet follow));
extern void Table_Follow ARGS((Idents_tIdent nonterm, Sets_tSet *follow));
extern void Table_SetLength ARGS((Idents_tIdent id, INTEGER len));
extern INTEGER Table_Length ARGS((Idents_tIdent id));
extern void Table__init();
