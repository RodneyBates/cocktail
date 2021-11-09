#include "SYSTEM_.h"

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Traces
#include "Traces.h"
#endif


#define InitialRELength   16
typedef struct S_1 *TraceStepPtr;
typedef struct S_1 {
    Dfa_DStateRange TraceState;
    Dfa_DStateRange NewState;
    TraceStepPtr Next;
} TraceStep;
typedef struct S_2 {
    TraceStep A[100000 + 1];
} Trace;
typedef struct S_3 {
    TraceStepPtr A[100000 + 1];
} PosToTrace;
static Trace *TracePtr;
static LONGINT TraceSize;
static PosToTrace *PosToTracePtr;
static LONGINT PosToTraceSize;
static INTEGER TraceCount;


void Traces_InitTraces
# ifdef __STDC__
()
# else
()
# endif
{
  PosToTraceSize = InitialRELength;
  DynArray_MakeArray((ADDRESS *)&PosToTracePtr, &PosToTraceSize, (LONGINT)sizeof(TraceStepPtr));
  TraceSize = GenTabs_StartStateCount * PosToTraceSize;
  DynArray_MakeArray((ADDRESS *)&TracePtr, &TraceSize, (LONGINT)sizeof(TraceStep));
}

void Traces_ResetTraces
# ifdef __STDC__
(INTEGER StringLength)
# else
(StringLength)
INTEGER StringLength;
# endif
{
  INTEGER i;

  while (PosToTraceSize <= StringLength) {
    DynArray_ExtendArray((ADDRESS *)&PosToTracePtr, &PosToTraceSize, (LONGINT)sizeof(TraceStepPtr));
  }
  while (TraceSize <= GenTabs_StartStateCount * StringLength) {
    DynArray_ExtendArray((ADDRESS *)&TracePtr, &TraceSize, (LONGINT)sizeof(TraceStep));
  }
  TraceCount = 0;
  {
    LONGINT B_1 = 1, B_2 = StringLength;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        PosToTracePtr->A[i] = NIL;
        if (i >= B_2) break;
      }
  }
}

void Traces_RecordTrace
# ifdef __STDC__
(SHORTCARD Position, Dfa_DStateRange pTraceState, Dfa_DStateRange pNewState)
# else
(Position, pTraceState, pNewState)
SHORTCARD Position;
Dfa_DStateRange pTraceState, pNewState;
# endif
{
  INC(TraceCount);
  {
    register TraceStep *W_1 = &TracePtr->A[TraceCount];

    W_1->TraceState = pTraceState;
    W_1->NewState = pNewState;
    W_1->Next = PosToTracePtr->A[Position];
  }
  PosToTracePtr->A[Position] = (TraceStepPtr)ADR(TracePtr->A[TraceCount]);
}

Dfa_DStateRange Traces_RecordedTrace
# ifdef __STDC__
(SHORTCARD Position, Dfa_DStateRange pTraceState)
# else
(Position, pTraceState)
SHORTCARD Position;
Dfa_DStateRange pTraceState;
# endif
{
  TraceStepPtr ActTraceStep;

  ActTraceStep = PosToTracePtr->A[Position];
  while (ActTraceStep != NIL) {
    if (ActTraceStep->TraceState == pTraceState) {
      return ActTraceStep->NewState;
    }
    ActTraceStep = ActTraceStep->Next;
  }
  return Dfa_DNoState;
}

void Traces_FinalizeTraces
# ifdef __STDC__
()
# else
()
# endif
{
  DynArray_ReleaseArray((ADDRESS *)&TracePtr, &TraceSize, (LONGINT)sizeof(TraceStep));
  DynArray_ReleaseArray((ADDRESS *)&PosToTracePtr, &PosToTraceSize, (LONGINT)sizeof(TraceStepPtr));
}

void Traces__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Dfa__init();
    Dfa__init();
    GenTabs__init();
    DynArray__init();

  }
}
