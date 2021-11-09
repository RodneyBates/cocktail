#define DEFINITION_Continue

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

extern struct Continue_1 {
    Automaton_tIndex A[TokenTab_cMAXNonTerm + 2 + 1];
} Continue_Value;
extern void Continue_ValueNonterms ARGS(());
extern void Continue_MakeContinuation ARGS(());
extern void Continue__init();
