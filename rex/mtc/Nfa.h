#define DEFINITION_Nfa

#ifndef DEFINITION_ScanTabs
#include "ScanTabs.h"
#endif

#define Nfa_NoTransition   0
typedef LONGINT Nfa_NStateRange;
typedef LONGINT Nfa_TransitionRange;
extern Nfa_NStateRange Nfa_NStateCount;
extern Nfa_TransitionRange Nfa_TransitionCount;
extern void Nfa_BeginNfa ARGS(());
extern Nfa_NStateRange Nfa_MakeNState ARGS((Nfa_TransitionRange pTransitions));
extern void Nfa_PutNSemantics ARGS((Nfa_NStateRange State, ScanTabs_RuleType pSemantics));
extern ScanTabs_RuleType Nfa_GetNSemantics ARGS((Nfa_NStateRange State));
extern void Nfa_PutTransitions ARGS((Nfa_NStateRange State, Nfa_TransitionRange pTransition));
extern Nfa_TransitionRange Nfa_GetTransitions ARGS((Nfa_NStateRange State));
extern BOOLEAN Nfa_IsLastTransition ARGS((Nfa_TransitionRange Transition));
extern Nfa_TransitionRange Nfa_NextTransition ARGS((Nfa_TransitionRange Transition));
extern Nfa_TransitionRange Nfa_MakeTransition ARGS((CHAR pCh, Nfa_NStateRange State));
extern Nfa_TransitionRange Nfa_AddTransition ARGS((Nfa_TransitionRange Transition, Nfa_TransitionRange Transitions));
extern CHAR Nfa_GetCh ARGS((Nfa_TransitionRange Transition));
extern Nfa_NStateRange Nfa_GetNextState ARGS((Nfa_TransitionRange Transition));
extern Nfa_TransitionRange Nfa_UniteTransitions ARGS((Nfa_TransitionRange t1, Nfa_TransitionRange t2));
extern Nfa_TransitionRange Nfa_CopyTransitions ARGS((Nfa_TransitionRange t1));
extern void Nfa_WriteNfa ARGS(());
extern void Nfa_FinalizeNfa ARGS(());
extern void Nfa__init();
