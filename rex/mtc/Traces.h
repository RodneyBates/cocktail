#define DEFINITION_Traces

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

extern void Traces_InitTraces ARGS(());
extern void Traces_ResetTraces ARGS((INTEGER StringLength));
extern void Traces_RecordTrace ARGS((SHORTCARD Position, Dfa_DStateRange TraceState, Dfa_DStateRange NewState));
extern Dfa_DStateRange Traces_RecordedTrace ARGS((SHORTCARD Position, Dfa_DStateRange TraceState));
extern void Traces_FinalizeTraces ARGS(());
extern void Traces__init();
