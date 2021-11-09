#define DEFINITION_Reachable

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

extern void Reachable_WindThrough ARGS((Idents_tIdent start));
extern BOOLEAN Reachable_IsReachable ARGS((Idents_tIdent nonterm));
extern void Reachable__init();
