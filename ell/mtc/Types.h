#define DEFINITION_Types

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

extern void Types_BeginTypes ARGS(());
extern void Types_MakeTerm ARGS((Idents_tIdent id));
extern void Types_MakeNonterm ARGS((Idents_tIdent id));
extern BOOLEAN Types_IsDeclared ARGS((Idents_tIdent id));
extern BOOLEAN Types_IsTerm ARGS((Idents_tIdent id));
extern BOOLEAN Types_IsNonterm ARGS((Idents_tIdent id));
extern void Types_Terminals ARGS((Sets_tSet *set));
extern void Types_Nonterminals ARGS((Sets_tSet *set));
extern void Types__init();
