#define DEFINITION_Automaton

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

extern void Automaton_BeginAutomaton ARGS((INTEGER stopstates, INTEGER MaxInput));
extern void Automaton_DefineTransition ARGS((Queues_tQueue path, INTEGER stop));
extern void Automaton_CloseAutomaton ARGS((IO_tFile f, INTEGER *CombSize));
extern INTEGER Automaton_StartIndex ARGS((INTEGER input));
extern void Automaton_WriteAutomaton ARGS(());
extern void Automaton_WriteFunction ARGS(());
extern void Automaton_WriteComb ARGS(());
extern void Automaton__init();
