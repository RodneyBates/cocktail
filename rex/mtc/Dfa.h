#define DEFINITION_Dfa

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#define Dfa_DNoState   0
#define Dfa_FirstCh   '\0'
#define Dfa_BlankCh   ' '
#define Dfa_TabCh   '\t'
#define Dfa_EolCh   '\n'
#define Dfa_EobCh   ((CHAR)'\177')
typedef SHORTINT Dfa_DStateRange;
extern CHAR Dfa_LastCh;
extern CHAR Dfa_OldLastCh;
extern Dfa_DStateRange Dfa_DStateCount;
extern Dfa_DStateRange Dfa_EobState;
extern Dfa_DStateRange Dfa_EobDefaultState;
extern Sets_tSet Dfa_AmbiguousStates;
extern Sets_tSet Dfa_CyclicStates;
extern Dfa_DStateRange Dfa_MaxAmbiguousState;
extern INTEGER Dfa_MinimizeSavings;
extern INTEGER Dfa_DefaultSavings;
extern Dfa_DStateRange Dfa_MakeDState ARGS(());
extern Dfa_DStateRange Dfa_GetDefault ARGS((Dfa_DStateRange State));
extern void Dfa_PutDefault ARGS((Dfa_DStateRange State, Dfa_DStateRange DefaultState));
extern void Dfa_GetDSemantics ARGS((Dfa_DStateRange State, Sets_tSet *Semantics));
extern void Dfa_PutDSemantics ARGS((Dfa_DStateRange State, Sets_tSet Semantics));
extern void Dfa_GetStartSet ARGS((Dfa_DStateRange State, Sets_tSet *StartSet));
extern void Dfa_PutStartSet ARGS((Dfa_DStateRange State, Sets_tSet StartSet));
extern Dfa_DStateRange Dfa_GetTable ARGS((Dfa_DStateRange State, CHAR Ch));
extern void Dfa_PutTable ARGS((Dfa_DStateRange State, CHAR Ch, Dfa_DStateRange NextState));
extern Dfa_DStateRange Dfa_GetTableNoDef ARGS((Dfa_DStateRange State, CHAR Ch));
extern CHAR Dfa_GetFirst ARGS((Dfa_DStateRange State));
extern CHAR Dfa_GetLast ARGS((Dfa_DStateRange State));
extern Dfa_DStateRange Dfa_GetEobTrans ARGS((Dfa_DStateRange State));
extern void Dfa_MinimizeDfa ARGS(());
extern void Dfa_ComputeSuccGraph ARGS(());
extern void Dfa_ComputeAmbiguousStates ARGS(());
extern void Dfa_ComputeCyclicStates ARGS(());
extern void Dfa_ComputeStartSets ARGS(());
extern void Dfa_SaveEobTransitions ARGS(());
extern void Dfa_ComputeDefaults ARGS((Dfa_DStateRange From, Dfa_DStateRange To));
extern void Dfa_WriteDfa ARGS(());
extern void Dfa__init();
