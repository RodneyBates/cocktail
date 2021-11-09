#define DEFINITION_Complete

#ifndef DEFINITION_Environs
#include "Environs.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

extern BOOLEAN Complete_IsComplete;
extern void Complete_FunctionComplete ARGS((Environs_tFunction function, Idents_tIdent ident, Positions_tPosition pos));
extern void Complete__init();
