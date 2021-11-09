#define DEFINITION_Default

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

extern BOOLEAN Default_NoDefault;
extern void Default_CreateDefaultList ARGS(());
extern void Default_PutInDefaultList ARGS((Automaton_tStateIndex ReadState, Gen_tTableLine *TableLine));
extern void Default_ComputeDefaults ARGS(());
extern Automaton_tStateIndex Default_GetNextState ARGS((Automaton_tStateIndex State));
extern Automaton_tStateIndex Default_GetTSortState ARGS((Automaton_tStateIndex State));
extern Automaton_tStateIndex Default_GetNSortState ARGS((Automaton_tStateIndex State));
extern void Default_GetDefaultTableLine ARGS((Automaton_tStateIndex ReadState, Gen_tTableLine *TableLine, Automaton_tStateIndex *Default));
extern void Default__init();
