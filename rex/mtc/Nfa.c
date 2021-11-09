#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_ScanTabs
#include "ScanTabs.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

#ifndef DEFINITION_Nfa
#include "Nfa.h"
#endif

Nfa_NStateRange Nfa_NStateCount;
Nfa_TransitionRange Nfa_TransitionCount;

#define InitialTransitionTableSize   4096
typedef struct S_1 {
    CHAR Ch;
    Nfa_NStateRange NextState;
    Nfa_TransitionRange NextTrans;
} C_1_Transition;
typedef struct S_2 {
    Nfa_TransitionRange Transitions;
    ScanTabs_RuleType Semantics;
} NStateInfo;
typedef struct S_3 {
    NStateInfo A[100000 + 1];
} NStateTable;
typedef struct S_4 {
    C_1_Transition A[100000 + 1];
} TransitionTable;
static NStateTable *NStateTablePtr;
static LONGINT NStateTableSize;
static TransitionTable *TransitionTablePtr;
static LONGINT TransitionTableSize;
static void WriteTransitions ARGS((Nfa_TransitionRange Transition));


Nfa_NStateRange Nfa_MakeNState
# ifdef __STDC__
(Nfa_TransitionRange pTransitions)
# else
(pTransitions)
Nfa_TransitionRange pTransitions;
# endif
{
  INC(Nfa_NStateCount);
  if (Nfa_NStateCount == NStateTableSize) {
    DynArray_ExtendArray((ADDRESS *)&NStateTablePtr, &NStateTableSize, (LONGINT)sizeof(NStateInfo));
  }
  {
    register NStateInfo *W_1 = &NStateTablePtr->A[Nfa_NStateCount];

    W_1->Transitions = pTransitions;
    W_1->Semantics = ScanTabs_NoRule;
  }
  return Nfa_NStateCount;
}

void Nfa_PutNSemantics
# ifdef __STDC__
(Nfa_NStateRange State, ScanTabs_RuleType pSemantics)
# else
(State, pSemantics)
Nfa_NStateRange State;
ScanTabs_RuleType pSemantics;
# endif
{
  NStateTablePtr->A[State].Semantics = pSemantics;
}

ScanTabs_RuleType Nfa_GetNSemantics
# ifdef __STDC__
(Nfa_NStateRange State)
# else
(State)
Nfa_NStateRange State;
# endif
{
  return NStateTablePtr->A[State].Semantics;
}

void Nfa_PutTransitions
# ifdef __STDC__
(Nfa_NStateRange State, Nfa_TransitionRange Transitions)
# else
(State, Transitions)
Nfa_NStateRange State;
Nfa_TransitionRange Transitions;
# endif
{
  NStateTablePtr->A[State].Transitions = Transitions;
}

Nfa_TransitionRange Nfa_GetTransitions
# ifdef __STDC__
(Nfa_NStateRange State)
# else
(State)
Nfa_NStateRange State;
# endif
{
  return NStateTablePtr->A[State].Transitions;
}

BOOLEAN Nfa_IsLastTransition
# ifdef __STDC__
(Nfa_TransitionRange Transition)
# else
(Transition)
Nfa_TransitionRange Transition;
# endif
{
  return Transition == Nfa_NoTransition;
}

Nfa_TransitionRange Nfa_NextTransition
# ifdef __STDC__
(Nfa_TransitionRange Transition)
# else
(Transition)
Nfa_TransitionRange Transition;
# endif
{
  return TransitionTablePtr->A[Transition].NextTrans;
}

Nfa_TransitionRange Nfa_MakeTransition
# ifdef __STDC__
(CHAR pCh, Nfa_NStateRange State)
# else
(pCh, State)
CHAR pCh;
Nfa_NStateRange State;
# endif
{
  INC(Nfa_TransitionCount);
  if (Nfa_TransitionCount == TransitionTableSize) {
    DynArray_ExtendArray((ADDRESS *)&TransitionTablePtr, &TransitionTableSize, (LONGINT)sizeof(C_1_Transition));
  }
  {
    register C_1_Transition *W_2 = &TransitionTablePtr->A[Nfa_TransitionCount];

    W_2->Ch = pCh;
    W_2->NextState = State;
    W_2->NextTrans = Nfa_NoTransition;
  }
  return Nfa_TransitionCount;
}

Nfa_TransitionRange Nfa_AddTransition
# ifdef __STDC__
(Nfa_TransitionRange Transition, Nfa_TransitionRange Transitions)
# else
(Transition, Transitions)
Nfa_TransitionRange Transition, Transitions;
# endif
{
  TransitionTablePtr->A[Transition].NextTrans = Transitions;
  return Transition;
}

CHAR Nfa_GetCh
# ifdef __STDC__
(Nfa_TransitionRange Transition)
# else
(Transition)
Nfa_TransitionRange Transition;
# endif
{
  return TransitionTablePtr->A[Transition].Ch;
}

Nfa_NStateRange Nfa_GetNextState
# ifdef __STDC__
(Nfa_TransitionRange Transition)
# else
(Transition)
Nfa_TransitionRange Transition;
# endif
{
  return TransitionTablePtr->A[Transition].NextState;
}

Nfa_TransitionRange Nfa_UniteTransitions
# ifdef __STDC__
(Nfa_TransitionRange t1, Nfa_TransitionRange t2)
# else
(t1, t2)
Nfa_TransitionRange t1, t2;
# endif
{
  Nfa_TransitionRange t;

  if (t1 == Nfa_NoTransition) {
    return t2;
  }
  while (t2 != Nfa_NoTransition) {
    t = TransitionTablePtr->A[t2].NextTrans;
    t1 = Nfa_AddTransition(t2, t1);
    t2 = t;
  }
  return t1;
}

Nfa_TransitionRange Nfa_CopyTransitions
# ifdef __STDC__
(Nfa_TransitionRange t1)
# else
(t1)
Nfa_TransitionRange t1;
# endif
{
  Nfa_TransitionRange t2;

  t2 = Nfa_NoTransition;
  while (t1 != Nfa_NoTransition) {
    {
      register C_1_Transition *W_3 = &TransitionTablePtr->A[t1];

      t2 = Nfa_AddTransition(Nfa_MakeTransition(W_3->Ch, W_3->NextState), t2);
      t1 = W_3->NextTrans;
    }
  }
  return t2;
}

void Nfa_WriteNfa
# ifdef __STDC__
()
# else
()
# endif
{
  Nfa_NStateRange State;

  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"NFA :", 5L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteNl((System_tFile)IO_StdOutput);
  {
    LONGINT B_1 = 1, B_2 = Nfa_NStateCount;

    if (B_1 <= B_2)
      for (State = B_1;; State += 1) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"State, Semantics =", 18L);
        IO_WriteI((System_tFile)IO_StdOutput, State, 5L);
        IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Nfa_GetNSemantics(State), 5L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        WriteTransitions(Nfa_GetTransitions(State));
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        if (State >= B_2) break;
      }
  }
  IO_WriteNl((System_tFile)IO_StdOutput);
}

static void WriteTransitions
# ifdef __STDC__
(Nfa_TransitionRange Transition)
# else
(Transition)
Nfa_TransitionRange Transition;
# endif
{
  INTEGER Count;

  Count = 0;
  while (!Nfa_IsLastTransition(Transition)) {
    if (Count == 10) {
      IO_WriteNl((System_tFile)IO_StdOutput);
      Count = 0;
    }
    INC(Count);
    Layout_WriteChar((System_tFile)IO_StdOutput, Nfa_GetCh(Transition));
    Layout_WriteSpace((System_tFile)IO_StdOutput);
    IO_WriteI((System_tFile)IO_StdOutput, Nfa_GetNextState(Transition), 1L);
    IO_WriteC((System_tFile)IO_StdOutput, ',');
    Layout_WriteSpace((System_tFile)IO_StdOutput);
    Transition = Nfa_NextTransition(Transition);
  }
}

void Nfa_FinalizeNfa
# ifdef __STDC__
()
# else
()
# endif
{
  DynArray_ReleaseArray((ADDRESS *)&NStateTablePtr, &NStateTableSize, (LONGINT)sizeof(NStateInfo));
  DynArray_ReleaseArray((ADDRESS *)&TransitionTablePtr, &TransitionTableSize, (LONGINT)sizeof(C_1_Transition));
}

void Nfa_BeginNfa
# ifdef __STDC__
()
# else
()
# endif
{
  NStateTableSize = GenTabs_LeafCount + 1;
  DynArray_MakeArray((ADDRESS *)&NStateTablePtr, &NStateTableSize, (LONGINT)sizeof(NStateInfo));
  Nfa_NStateCount = 0;
  TransitionTableSize = InitialTransitionTableSize;
  DynArray_MakeArray((ADDRESS *)&TransitionTablePtr, &TransitionTableSize, (LONGINT)sizeof(C_1_Transition));
  Nfa_TransitionCount = 0;
}

void Nfa__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    ScanTabs__init();
    DynArray__init();
    IO__init();
    Layout__init();
    ScanTabs__init();
    GenTabs__init();

  }
}
