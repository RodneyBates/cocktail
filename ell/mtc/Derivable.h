#define DEFINITION_Derivable

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

extern void Derivable_TestDerivable ARGS(());
extern BOOLEAN Derivable_IsDerivable ARGS((Idents_tIdent Nonterm));
extern BOOLEAN Derivable_IsNullable ARGS((Idents_tIdent Nonterm));
extern void Derivable__init();
