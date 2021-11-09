#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Info
#include "Info.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif


#define NoState   -1
#define StartState   0
#define InitCombSize   100
typedef INTEGER tState;
typedef struct S_4 {
    tState A[1000 + 1];
} *tStateTable;
typedef struct S_5 {
    INTEGER A[1000 + 1];
} *tComb;
typedef struct S_1 *tTransition;
typedef struct S_1 {
    INTEGER Input;
    tState Target;
    tTransition Next;
} tTransitionR;
typedef struct S_2 {
    tTransition Trans;
    tState MainState;
} tStateR;
typedef struct S_3 {
    tState StopStates;
    tState LastState;
    INTEGER MaxInput;
    struct S_6 {
        tStateR A[1000 + 1];
    } *TransitionTable;
    INTEGER TableSize;
    LONGINT TableSizeL;
    struct S_7 {
        INTEGER A[1000 + 1];
    } *IndexArray;
    LONGINT IndexArraySize;
} tAutomaton;
static tAutomaton Automaton;
static tComb Comb;
static LONGINT CombSizeL;
static INTEGER CombSize;
static INTEGER CombCount;
static tState NewState ARGS(());
static tState MakeTarget ARGS((tState state, INTEGER input));
static void SetTarget ARGS((tState state, INTEGER input, tState stop));
static void ReduceAutomaton ARGS(());
static void DefineTable ARGS((tStateTable T, tState state));
static BOOLEAN Compatible ARGS((tStateTable T, tState state));
static void Melt ARGS((tState actual, tState state, tStateTable T));
static void MakeComb ARGS(());
static BOOLEAN Fits ARGS((INTEGER index, tState state));
static void Embed ARGS((INTEGER index, tState state));
static void OutputComb ARGS((IO_tFile f));
static void ReleaseAutomaton ARGS(());
static tState MainState ARGS((tState state));
static void WriteTrans ARGS((tState state, Queues_tQueue *q));
static void WriteState ARGS((tState state));


void Automaton_BeginAutomaton
# ifdef __STDC__
(INTEGER stopstates, INTEGER maxinput)
# else
(stopstates, maxinput)
INTEGER stopstates;
INTEGER maxinput;
# endif
{
  tState state;

  {
    register tAutomaton *W_1 = &Automaton;

    W_1->StopStates = stopstates;
    W_1->LastState = stopstates;
    W_1->MaxInput = maxinput;
    W_1->TableSizeL = 4 * stopstates + 4;
    DynArray_MakeArray((ADDRESS *)&W_1->TransitionTable, &W_1->TableSizeL, (LONGINT)sizeof(tStateR));
    W_1->TableSize = W_1->TableSizeL;
    {
      LONGINT B_1 = 0, B_2 = W_1->TableSize - 1;

      if (B_1 <= B_2)
        for (state = B_1;; state += 1) {
          W_1->TransitionTable->A[state].Trans = NIL;
          W_1->TransitionTable->A[state].MainState = NoState;
          if (state >= B_2) break;
        }
    }
  }
}

void Automaton_DefineTransition
# ifdef __STDC__
(Queues_tQueue path, INTEGER stop)
# else
(path, stop)
Queues_tQueue path;
INTEGER stop;
# endif
{
  tState state;
  INTEGER input, length, pos;

  state = StartState;
  pos = 0;
  length = Queues_Length(path);
  for (;;) {
    INC(pos);
    input = (INTEGER)Queues_GetElement(path, pos);
    if (pos == length) {
      goto EXIT_1;
    }
    state = MakeTarget(state, input);
  } EXIT_1:;
  SetTarget(state, input, stop);
}

static tState NewState
# ifdef __STDC__
()
# else
()
# endif
{
  tState state, size;

  {
    register tAutomaton *W_2 = &Automaton;

    INC(W_2->LastState);
    if (W_2->LastState >= W_2->TableSize) {
      DynArray_ExtendArray((ADDRESS *)&W_2->TransitionTable, &W_2->TableSizeL, (LONGINT)sizeof(tStateR));
    }
    size = W_2->TableSizeL;
    {
      LONGINT B_3 = W_2->TableSize, B_4 = size - 1;

      if (B_3 <= B_4)
        for (state = B_3;; state += 1) {
          W_2->TransitionTable->A[state].Trans = NIL;
          W_2->TransitionTable->A[state].MainState = NoState;
          if (state >= B_4) break;
        }
    }
    W_2->TableSize = W_2->TableSizeL;
    return W_2->LastState;
  }
}

static tState MakeTarget
# ifdef __STDC__
(tState state, INTEGER input)
# else
(state, input)
tState state;
INTEGER input;
# endif
{
  tTransition *t;

  t = (tTransition *)ADR(Automaton.TransitionTable->A[state].Trans);
  for (;;) {
    if (*t == NIL) {
      goto EXIT_2;
    }
    if ((*t)->Input == input) {
      return (*t)->Target;
    }
    t = (tTransition *)ADR((*t)->Next);
  } EXIT_2:;
  *t = (tTransition)Memory_Alloc((LONGINT)sizeof(tTransitionR));
  (*t)->Input = input;
  (*t)->Target = NewState();
  (*t)->Next = NIL;
  return (*t)->Target;
}

static void SetTarget
# ifdef __STDC__
(tState state, INTEGER input, tState stop)
# else
(state, input, stop)
tState state;
INTEGER input;
tState stop;
# endif
{
  tTransition *t;

  t = (tTransition *)ADR(Automaton.TransitionTable->A[state].Trans);
  for (;;) {
    if (*t == NIL) {
      goto EXIT_3;
    }
    if ((*t)->Input == input) {
      Errors_ERROR((STRING)"Automaton.SetTarget: already defined", 36L);
    }
    t = (tTransition *)ADR((*t)->Next);
  } EXIT_3:;
  *t = (tTransition)Memory_Alloc((LONGINT)sizeof(tTransitionR));
  (*t)->Input = input;
  (*t)->Target = stop;
  (*t)->Next = NIL;
}

static void ReduceAutomaton
# ifdef __STDC__
()
# else
()
# endif
{
  tState actual, state;
  INTEGER input;
  tStateTable T;
  LONGINT s;

  {
    register tAutomaton *W_3 = &Automaton;

    s = W_3->MaxInput + 1;
    DynArray_MakeArray((ADDRESS *)&T, &s, (LONGINT)sizeof(tState));
    {
      LONGINT B_5 = W_3->LastState - 1, B_6 = W_3->StopStates + 1;

      if (B_5 >= B_6)
        for (actual = B_5;; actual += -1) {
          DefineTable(T, actual);
          {
            LONGINT B_7 = actual + 1, B_8 = W_3->LastState;

            if (B_7 <= B_8)
              for (state = B_7;; state += 1) {
                if (Compatible(T, state)) {
                  Melt(actual, state, T);
                }
                if (state >= B_8) break;
              }
          }
          if (actual <= B_6) break;
        }
    }
    DynArray_ReleaseArray((ADDRESS *)&T, &s, (LONGINT)sizeof(tState));
  }
}

static void DefineTable
# ifdef __STDC__
(tStateTable T, tState state)
# else
(T, state)
tStateTable T;
tState state;
# endif
{
  tState input;
  tTransition t;

  {
    register tAutomaton *W_4 = &Automaton;

    {
      LONGINT B_9 = 0, B_10 = W_4->MaxInput;

      if (B_9 <= B_10)
        for (input = B_9;; input += 1) {
          T->A[input] = NoState;
          if (input >= B_10) break;
        }
    }
    t = W_4->TransitionTable->A[state].Trans;
    while (t != NIL) {
      T->A[t->Input] = MainState(t->Target);
      t = t->Next;
    }
  }
}

static BOOLEAN Compatible
# ifdef __STDC__
(tStateTable T, tState state)
# else
(T, state)
tStateTable T;
tState state;
# endif
{
  tTransition t;

  {
    register tAutomaton *W_5 = &Automaton;

    if (W_5->TransitionTable->A[state].MainState != NoState) {
      return FALSE;
    }
    t = W_5->TransitionTable->A[state].Trans;
    while (t != NIL) {
      if (T->A[t->Input] != NoState && MainState(T->A[t->Input]) != MainState(t->Target)) {
        return FALSE;
      }
      t = t->Next;
    }
    return TRUE;
  }
}

static void Melt
# ifdef __STDC__
(tState actual, tState state, tStateTable T)
# else
(actual, state, T)
tState actual, state;
tStateTable T;
# endif
{
  tTransition t;
  INTEGER input;
  tState target;

  {
    register tAutomaton *W_6 = &Automaton;

    t = W_6->TransitionTable->A[state].Trans;
    while (t != NIL) {
      input = t->Input;
      if (T->A[input] == NoState) {
        target = MainState(t->Target);
        T->A[input] = target;
        SetTarget(actual, input, target);
      }
      t = t->Next;
    }
    W_6->TransitionTable->A[state].MainState = actual;
  }
}

static void MakeComb
# ifdef __STDC__
()
# else
()
# endif
{
  tState state, main;
  INTEGER index;

  CombCount = -1;
  CombSize = 0;
  {
    register tAutomaton *W_7 = &Automaton;

    {
      LONGINT B_11 = StartState, B_12 = W_7->StopStates;

      if (B_11 <= B_12)
        for (state = B_11;; state += 1) {
          W_7->IndexArray->A[state] = state;
          if (state >= B_12) break;
        }
    }
    {
      LONGINT B_13 = W_7->StopStates + 1, B_14 = W_7->LastState;

      if (B_13 <= B_14)
        for (state = B_13;; state += 1) {
          main = W_7->TransitionTable->A[state].MainState;
          if (main == NoState) {
            index = 0;
            while (!Fits(index, state)) {
              INC(index);
            }
            Embed(index, state);
          } else {
            index = W_7->IndexArray->A[main];
          }
          W_7->IndexArray->A[state] = index;
          if (state >= B_14) break;
        }
    }
    {
      LONGINT B_15 = 0, B_16 = CombCount;

      if (B_15 <= B_16)
        for (index = B_15;; index += 1) {
          state = Comb->A[index];
          if (state > W_7->StopStates) {
            Comb->A[index] = W_7->IndexArray->A[state];
          }
          if (index >= B_16) break;
        }
    }
  }
}

static BOOLEAN Fits
# ifdef __STDC__
(INTEGER index, tState state)
# else
(index, state)
INTEGER index;
tState state;
# endif
{
  tTransition t;
  INTEGER i;
  INTEGER old, j;

  t = Automaton.TransitionTable->A[state].Trans;
  while (t != NIL) {
    i = index + t->Input;
    if (i > CombCount) {
      while (i >= CombSize) {
        old = CombSize;
        if (CombSize == 0) {
          CombSizeL = InitCombSize;
          DynArray_MakeArray((ADDRESS *)&Comb, &CombSizeL, (LONGINT)sizeof(INTEGER));
        } else {
          DynArray_ExtendArray((ADDRESS *)&Comb, &CombSizeL, (LONGINT)sizeof(INTEGER));
        }
        CombSize = CombSizeL;
        {
          LONGINT B_17 = old, B_18 = CombSize - 1;

          if (B_17 <= B_18)
            for (j = B_17;; j += 1) {
              Comb->A[j] = NoState;
              if (j >= B_18) break;
            }
        }
      }
      CombCount = i;
    }
    if (Comb->A[i] != NoState && Comb->A[i] != t->Target) {
      return FALSE;
    }
    t = t->Next;
  }
  return TRUE;
}

static void Embed
# ifdef __STDC__
(INTEGER index, tState state)
# else
(index, state)
INTEGER index;
tState state;
# endif
{
  tTransition t;

  t = Automaton.TransitionTable->A[state].Trans;
  while (t != NIL) {
    Comb->A[index + t->Input] = t->Target;
    t = t->Next;
  }
}

void Automaton_CloseAutomaton
# ifdef __STDC__
(IO_tFile f, INTEGER *CombSize)
# else
(f, CombSize)
IO_tFile f;
INTEGER *CombSize;
# endif
{
  ReduceAutomaton();
  {
    register tAutomaton *W_8 = &Automaton;

    W_8->IndexArraySize = W_8->LastState + 1;
    DynArray_MakeArray((ADDRESS *)&W_8->IndexArray, &W_8->IndexArraySize, (LONGINT)sizeof(INTEGER));
  }
  MakeComb();
  OutputComb(f);
  *CombSize = CombCount;
}

static void OutputComb
# ifdef __STDC__
(IO_tFile f)
# else
(f)
IO_tFile f;
# endif
{
  INTEGER i;

  i = Write(f, (ADDRESS)Comb, (1 + CombCount) * sizeof(INTEGER));
}

static void ReleaseAutomaton
# ifdef __STDC__
()
# else
()
# endif
{
  {
    register tAutomaton *W_9 = &Automaton;

    DynArray_ReleaseArray((ADDRESS *)&W_9->IndexArray, &W_9->IndexArraySize, (LONGINT)sizeof(INTEGER));
  }
}

INTEGER Automaton_StartIndex
# ifdef __STDC__
(INTEGER input)
# else
(input)
INTEGER input;
# endif
{
  tTransition trans;

  {
    register tAutomaton *W_10 = &Automaton;

    trans = W_10->TransitionTable->A[StartState].Trans;
    for (;;) {
      if (trans == NIL) {
        goto EXIT_4;
      }
      if (trans->Input == input) {
        return W_10->IndexArray->A[trans->Target];
      }
      trans = trans->Next;
    } EXIT_4:;
    Errors_ERROR((STRING)"Automaton.StartIndex: not defined", 33L);
  }
}

static tState MainState
# ifdef __STDC__
(tState state)
# else
(state)
tState state;
# endif
{
  {
    register tAutomaton *W_11 = &Automaton;

    while (state > W_11->StopStates && W_11->TransitionTable->A[state].MainState != NoState) {
      state = W_11->TransitionTable->A[state].MainState;
    }
    return state;
  }
}

void Automaton_WriteFunction
# ifdef __STDC__
()
# else
()
# endif
{
  Queues_tQueue q;

  Queues_MakeQueue(&q);
  WriteTrans((LONGINT)StartState, &q);
  Queues_ReleaseQueue(&q);
}

static void WriteTrans
# ifdef __STDC__
(tState state, Queues_tQueue *q)
# else
(state, q)
tState state;
Queues_tQueue *q;
# endif
{
  Sets_tSet done;
  tTransition trans, t;
  Sets_tSet inputs;
  Sets_tSet *in;
  INTEGER pos;
  tState target;

  {
    register tAutomaton *W_12 = &Automaton;

    Sets_MakeSet(&done, (Sets_tElement)W_12->LastState);
    Sets_MakeSet(&inputs, (Sets_tElement)W_12->MaxInput);
    Queues_Append(q, ADR(inputs));
    trans = W_12->TransitionTable->A[state].Trans;
    for (;;) {
      if (trans == NIL) {
        goto EXIT_5;
      }
      target = MainState(trans->Target);
      if (!Sets_IsElement((Sets_tElement)target, &done)) {
        Sets_AssignEmpty(&inputs);
        Sets_Include(&inputs, (Sets_tElement)trans->Input);
        t = trans->Next;
        while (t != NIL) {
          if (MainState(t->Target) == target) {
            Sets_Include(&inputs, (Sets_tElement)t->Input);
          }
          t = t->Next;
        }
        if (target > W_12->StopStates) {
          WriteTrans(target, q);
        } else {
          in = (Sets_tSet *)Queues_GetElement(*q, 1L);
          Info_WriteIdentSet((System_tFile)IO_StdOutput, *in);
          StdIO_WriteS((STRING)" ", 1L);
          {
            LONGINT B_19 = 2, B_20 = Queues_Length(*q);

            if (B_19 <= B_20)
              for (pos = B_19;; pos += 1) {
                in = (Sets_tSet *)Queues_GetElement(*q, pos);
                Sets_WriteSet((System_tFile)IO_StdOutput, *in);
                StdIO_WriteS((STRING)" ", 1L);
                if (pos >= B_20) break;
              }
          }
          StdIO_WriteS((STRING)" = ", 3L);
          StdIO_WriteI(target, 1L);
          StdIO_WriteNl();
        }
        Sets_Include(&done, (Sets_tElement)target);
      }
      trans = trans->Next;
    } EXIT_5:;
    Queues_ClearLast(q);
    Sets_ReleaseSet(&inputs);
    Sets_ReleaseSet(&done);
  }
}

void Automaton_WriteAutomaton
# ifdef __STDC__
()
# else
()
# endif
{
  tState state;

  StdIO_WriteS((STRING)"Automaton", 9L);
  StdIO_WriteNl();
  {
    LONGINT B_21 = 0, B_22 = Automaton.LastState;

    if (B_21 <= B_22)
      for (state = B_21;; state += 1) {
        WriteState(state);
        if (state >= B_22) break;
      }
  }
  StdIO_WriteNl();
}

static void WriteState
# ifdef __STDC__
(tState state)
# else
(state)
tState state;
# endif
{
  tTransition t;
  tState m;

  m = Automaton.TransitionTable->A[state].MainState;
  if (m != NoState) {
    StdIO_WriteI(state, 3L);
    StdIO_WriteS((STRING)" -> ", 4L);
    StdIO_WriteI(m, 3L);
    StdIO_WriteNl();
  } else {
    t = Automaton.TransitionTable->A[state].Trans;
    if (t != NIL) {
      StdIO_WriteI(state, 3L);
      while (t != NIL) {
        StdIO_WriteS((STRING)"  (", 3L);
        StdIO_WriteI(t->Input, 1L);
        StdIO_WriteS((STRING)", ", 2L);
        StdIO_WriteI(t->Target, 1L);
        StdIO_WriteS((STRING)")", 1L);
        t = t->Next;
      }
      StdIO_WriteNl();
    }
  }
}

void Automaton_WriteComb
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER index;

  StdIO_WriteS((STRING)"Comb", 4L);
  StdIO_WriteNl();
  StdIO_WriteS((STRING)"       ", 7L);
  for (index = 0; index <= 9; index += 1) {
    StdIO_WriteI(index, 5L);
  }
  {
    LONGINT B_23 = 0, B_24 = CombCount;

    if (B_23 <= B_24)
      for (index = B_23;; index += 1) {
        if (index % 10 == 0) {
          StdIO_WriteNl();
          StdIO_WriteI(index, 5L);
          StdIO_WriteS((STRING)"  ", 2L);
        }
        StdIO_WriteI(Comb->A[index], 5L);
        if (index >= B_24) break;
      }
  }
  StdIO_WriteNl();
  StdIO_WriteNl();
}

void Automaton__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Queues__init();
    DynArray__init();
    Errors__init();
    IO__init();
    Memory__init();
    Queues__init();
    System__init();
    Info__init();
    IO__init();
    Queues__init();
    StdIO__init();
    Sets__init();

  }
}
