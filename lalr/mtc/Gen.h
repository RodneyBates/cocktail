#define DEFINITION_Gen

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#define Gen_NoState   0
typedef SHORTCARD Gen_TableElmt;
typedef struct Gen_1 {
    Automaton_tStateIndex A[TokenTab_cMAXNonTerm + 2 + 1];
} Gen_tTableLine;
extern BOOLEAN Gen_Trace;
extern BOOLEAN Gen_CaseFlag;
extern INTEGER Gen_CaseLabels;
extern TokenTab_Vocabulary Gen_FirstSymbol, Gen_LastSymbol, Gen_FirstTerminal, Gen_LastTerminal;
extern CARDINAL Gen_NonTermOffset;
extern Automaton_tStateIndex Gen_FirstState, Gen_LastState, Gen_FirstReadState, Gen_LastReadState, Gen_FirstReadTermState, Gen_LastReadTermState, Gen_FirstReadNonTermState, Gen_LastReadNonTermState, Gen_FirstReduceState, Gen_LastReduceState, Gen_StopState;
extern Automaton_tStateIndex Gen_ReduceOffset;
extern Gen_TableElmt Gen_ElmtSize;
extern struct Gen_2 {
    Gen_TableElmt A[Automaton_Infinite - 1 + 1];
} *Gen_Length;
extern LONGINT Gen_LengthCount;
extern struct Gen_3 {
    Gen_TableElmt A[Automaton_Infinite - 1 + 1];
} *Gen_LeftHandSide;
extern LONGINT Gen_LeftHandSideCount;
extern struct Gen_4 {
    Gen_TableElmt A[Automaton_Infinite + 1];
} *Gen_Continuation;
extern LONGINT Gen_ContinuationCount;
extern struct Gen_5 {
    Gen_TableElmt A[Automaton_Infinite + 1];
} *Gen_FinalToProd;
extern LONGINT Gen_FinalToProdCount;
extern void Gen_GenDefaultActions ARGS(());
extern void Gen_GenCode ARGS((IO_tFile Pars, IO_tFile Def));
extern CARDINAL Gen_StartState ARGS(());
extern void Gen__init();
