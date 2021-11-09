#include "SYSTEM_.h"

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Default
#include "Default.h"
#endif

BOOLEAN Default_NoDefault;

#define NoState   0
typedef struct S_1 *tTrans;
typedef struct S_1 {
    TokenTab_Vocabulary Voc;
    Automaton_tStateIndex State;
    tTrans Next;
} tTran;
typedef struct S_2 {
    tTrans Transitions;
    Sets_tSet Terms;
    Automaton_tStateIndex Succ;
    Automaton_tStateIndex DefaultState;
    SHORTCARD Saving;
    SHORTCARD NontermCount;
    BOOLEAN ToTest;
    BOOLEAN InTest;
} tLine;
static struct S_3 {
    tLine A[Automaton_Infinite + 1];
} *TablePtr;
static LONGINT TableSize;
static struct S_4 {
    Automaton_tStateIndex A[Automaton_Infinite + 1];
} *TSorting;
static LONGINT TSortingSize;
static struct S_5 {
    Automaton_tStateIndex A[Automaton_Infinite + 1];
} *NSorting;
static LONGINT NSortingSize;
static void ComputeBestDefaults ARGS(());
static SHORTCARD ComputeSaving ARGS((Automaton_tStateIndex State, Automaton_tStateIndex DefState));
static void EliminateCycles ARGS(());
static void SortTStates ARGS(());
static void SortNStates ARGS(());


void Default_CreateDefaultList
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex State;

  TableSize = Gen_LastReadState + 1;
  DynArray_MakeArray((ADDRESS *)&TablePtr, &TableSize, (LONGINT)sizeof(tLine));
  TSortingSize = Gen_LastReadState + 1;
  DynArray_MakeArray((ADDRESS *)&TSorting, &TSortingSize, (LONGINT)sizeof(Automaton_tStateIndex));
  NSortingSize = Gen_LastReadState + 1;
  DynArray_MakeArray((ADDRESS *)&NSorting, &NSortingSize, (LONGINT)sizeof(Automaton_tStateIndex));
  {
    Automaton_tStateIndex B_1 = 0, B_2 = Gen_LastReadState;

    if (B_1 <= B_2)
      for (State = B_1;; State += 1) {
        {
          register tLine *W_1 = &TablePtr->A[State];

          W_1->Transitions = NIL;
          Sets_MakeSet(&W_1->Terms, (Sets_tElement)Gen_LastTerminal);
          W_1->Succ = NoState;
          W_1->DefaultState = NoState;
          W_1->Saving = 0;
          W_1->NontermCount = 0;
          W_1->ToTest = TRUE;
          W_1->InTest = FALSE;
        }
        TSorting->A[State] = State;
        NSorting->A[State] = State;
        if (State >= B_2) break;
      }
  }
}

void Default_PutInDefaultList
# ifdef __STDC__
(Automaton_tStateIndex ReadState, Gen_tTableLine *TableLine)
# else
(ReadState, TableLine)
Automaton_tStateIndex ReadState;
Gen_tTableLine *TableLine;
# endif
{
  tTrans Trans;
  tTrans TransSucc;
  TokenTab_Vocabulary Voc;
  Automaton_tStateIndex State;
  SHORTCARD Elements;
  BOOLEAN Continue;

  {
    register tLine *W_2 = &TablePtr->A[ReadState];

    W_2->Transitions = NIL;
    {
      TokenTab_Vocabulary B_3 = Gen_LastSymbol, B_4 = Gen_FirstSymbol;

      if (B_3 >= B_4)
        for (Voc = B_3;; Voc += -1) {
          if (TableLine->A[Voc] != NoState) {
            Trans = (tTrans)Memory_Alloc((LONGINT)sizeof(tTran));
            Trans->Voc = Voc;
            Trans->State = TableLine->A[Voc];
            Trans->Next = W_2->Transitions;
            W_2->Transitions = Trans;
            if (Voc >= Gen_FirstTerminal && Voc <= Gen_LastTerminal) {
              Sets_Include(&W_2->Terms, (Sets_tElement)Voc);
            } else {
              INC(W_2->NontermCount);
            }
          }
          if (Voc <= B_4) break;
        }
    }
    State = NoState;
    Elements = Sets_Card(&W_2->Terms);
    for (;;) {
      W_2->Succ = TablePtr->A[State].Succ;
      if (W_2->Succ == NoState) {
        goto EXIT_1;
      }
      if (Elements > Sets_Card(&TablePtr->A[W_2->Succ].Terms)) {
        goto EXIT_1;
      } else if (Elements == Sets_Card(&TablePtr->A[W_2->Succ].Terms)) {
        Trans = W_2->Transitions;
        TransSucc = TablePtr->A[W_2->Succ].Transitions;
        Continue = TRUE;
        while (Trans != NIL && TransSucc != NIL && Continue) {
          if (Trans->Voc > TransSucc->Voc) {
            goto EXIT_1;
          } else if (Trans->Voc < TransSucc->Voc) {
            Continue = FALSE;
          }
          Trans = Trans->Next;
          TransSucc = TransSucc->Next;
        }
      }
      State = W_2->Succ;
    } EXIT_1:;
    TablePtr->A[State].Succ = ReadState;
  }
}

void Default_ComputeDefaults
# ifdef __STDC__
()
# else
()
# endif
{
  if (Default_NoDefault) {
    return;
  }
  ComputeBestDefaults();
  EliminateCycles();
}

static void ComputeBestDefaults
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex LastState;
  Automaton_tStateIndex State;
  Automaton_tStateIndex DefState;
  SHORTCARD DefSaving;
  BOOLEAN backwards;

  LastState = NoState;
  State = TablePtr->A[LastState].Succ;
  while (State != NoState) {
    if (!Sets_IsEqual(&TablePtr->A[LastState].Terms, &TablePtr->A[State].Terms)) {
      LastState = State;
    }
    DefState = LastState;
    backwards = TRUE;
    for (;;) {
      if (DefState == State) {
        DefState = TablePtr->A[DefState].Succ;
        backwards = FALSE;
      }
      if (DefState == NoState) {
        goto EXIT_2;
      }
      if (Sets_Card(&TablePtr->A[DefState].Terms) < TablePtr->A[State].Saving) {
        goto EXIT_2;
      }
      DefSaving = ComputeSaving(State, DefState);
      if (DefSaving > 0 && DefSaving >= TablePtr->A[State].Saving) {
        TablePtr->A[State].DefaultState = DefState;
        TablePtr->A[State].Saving = DefSaving;
        TablePtr->A[State].ToTest = backwards;
      }
      DefState = TablePtr->A[DefState].Succ;
    } EXIT_2:;
    State = TablePtr->A[State].Succ;
  }
}

static SHORTCARD ComputeSaving
# ifdef __STDC__
(Automaton_tStateIndex State, Automaton_tStateIndex DefState)
# else
(State, DefState)
Automaton_tStateIndex State;
Automaton_tStateIndex DefState;
# endif
{
  SHORTCARD DefSaving;
  tTrans Trans, DefTrans;

  DefSaving = 0;
  if (Sets_IsSubset(TablePtr->A[DefState].Terms, TablePtr->A[State].Terms)) {
    Trans = TablePtr->A[State].Transitions;
    DefTrans = TablePtr->A[DefState].Transitions;
    while (DefTrans != NIL && DefTrans->Voc < Gen_LastTerminal) {
      while (Trans->Voc != DefTrans->Voc) {
        Trans = Trans->Next;
      }
      if (Trans->State == DefTrans->State) {
        INC(DefSaving);
      }
      DefTrans = DefTrans->Next;
      Trans = Trans->Next;
    }
  }
  return DefSaving;
}

static void EliminateCycles
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex State;
  Automaton_tStateIndex WorstState;
  SHORTCARD WorstSaving;
  Automaton_tStateIndex ActState;
  Automaton_tStateIndex FirstState;
  Automaton_tStateIndex DefState;
  SHORTCARD DefSaving;

  State = Default_GetNextState(NoState);
  while (State != NoState) {
    if (TablePtr->A[State].ToTest) {
      TablePtr->A[State].ToTest = FALSE;
      WorstSaving = TablePtr->A[State].Saving;
      WorstState = State;
      TablePtr->A[State].InTest = TRUE;
      ActState = TablePtr->A[State].DefaultState;
      while (ActState != NoState && !TablePtr->A[ActState].InTest) {
        TablePtr->A[ActState].InTest = TRUE;
        ActState = TablePtr->A[ActState].DefaultState;
      }
      FirstState = ActState;
      TablePtr->A[State].InTest = FALSE;
      ActState = TablePtr->A[State].DefaultState;
      while (ActState != NoState && TablePtr->A[ActState].InTest) {
        TablePtr->A[ActState].InTest = FALSE;
        ActState = TablePtr->A[ActState].DefaultState;
      }
      if (FirstState == NoState) {
        State = Default_GetNextState(State);
      } else {
        WorstState = FirstState;
        WorstSaving = TablePtr->A[WorstState].Saving;
        ActState = TablePtr->A[FirstState].DefaultState;
        while (ActState != FirstState) {
          if (TablePtr->A[ActState].Saving < WorstSaving) {
            WorstState = ActState;
            WorstSaving = TablePtr->A[WorstState].Saving;
          }
          ActState = TablePtr->A[ActState].DefaultState;
        }
        DefState = TablePtr->A[WorstState].DefaultState;
        DefState = TablePtr->A[DefState].Succ;
        TablePtr->A[WorstState].DefaultState = NoState;
        TablePtr->A[WorstState].Saving = 0;
        for (;;) {
          if (DefState == WorstState) {
            DefState = TablePtr->A[DefState].Succ;
          }
          if (DefState == NoState) {
            goto EXIT_3;
          }
          if (Sets_Card(&TablePtr->A[DefState].Terms) < TablePtr->A[WorstState].Saving) {
            goto EXIT_3;
          }
          DefSaving = ComputeSaving(WorstState, DefState);
          if (DefSaving > 0 && DefSaving >= TablePtr->A[WorstState].Saving) {
            TablePtr->A[WorstState].DefaultState = DefState;
            TablePtr->A[WorstState].Saving = DefSaving;
          }
          DefState = TablePtr->A[DefState].Succ;
        } EXIT_3:;
        if (TablePtr->A[WorstState].DefaultState != NoState) {
          TablePtr->A[State].ToTest = TRUE;
        }
      }
    } else {
      State = Default_GetNextState(State);
    }
  }
}

Automaton_tStateIndex Default_GetNextState
# ifdef __STDC__
(Automaton_tStateIndex State)
# else
(State)
Automaton_tStateIndex State;
# endif
{
  return TablePtr->A[State].Succ;
}

Automaton_tStateIndex Default_GetTSortState
# ifdef __STDC__
(Automaton_tStateIndex State)
# else
(State)
Automaton_tStateIndex State;
# endif
{
  return TSorting->A[State];
}

Automaton_tStateIndex Default_GetNSortState
# ifdef __STDC__
(Automaton_tStateIndex State)
# else
(State)
Automaton_tStateIndex State;
# endif
{
  return NSorting->A[State];
}

void Default_GetDefaultTableLine
# ifdef __STDC__
(Automaton_tStateIndex ReadState, Gen_tTableLine *TableLine, Automaton_tStateIndex *Default)
# else
(ReadState, TableLine, Default)
Automaton_tStateIndex ReadState;
Gen_tTableLine *TableLine;
Automaton_tStateIndex *Default;
# endif
{
  TokenTab_Vocabulary Voc;
  tTrans Trans;

  {
    TokenTab_Vocabulary B_5 = Gen_FirstSymbol, B_6 = Gen_LastSymbol;

    if (B_5 <= B_6)
      for (Voc = B_5;; Voc += 1) {
        TableLine->A[Voc] = NoState;
        if (Voc >= B_6) break;
      }
  }
  {
    register tLine *W_3 = &TablePtr->A[ReadState];

    *Default = W_3->DefaultState;
    Trans = W_3->Transitions;
    while (Trans != NIL) {
      TableLine->A[Trans->Voc] = Trans->State;
      Trans = Trans->Next;
    }
  }
  {
    register tLine *W_4 = &TablePtr->A[*Default];

    Trans = W_4->Transitions;
    while (Trans != NIL && Trans->Voc <= Gen_LastTerminal) {
      if (TableLine->A[Trans->Voc] == Trans->State) {
        TableLine->A[Trans->Voc] = NoState;
      }
      Trans = Trans->Next;
    }
  }
}

static void SortTStates
# ifdef __STDC__
()
# else
()
# endif
{
  BOOLEAN sorted;
  Automaton_tStateIndex I;
  Automaton_tStateIndex State;
  SHORTCARD Key, LastKey;

  for (;;) {
    sorted = TRUE;
    State = TSorting->A[1];
    LastKey = Sets_Card(&TablePtr->A[State].Terms) - TablePtr->A[State].Saving;
    {
      Automaton_tStateIndex B_7 = 2, B_8 = Gen_LastReadState;

      if (B_7 <= B_8)
        for (I = B_7;; I += 1) {
          State = TSorting->A[I];
          Key = Sets_Card(&TablePtr->A[State].Terms) - TablePtr->A[State].Saving;
          if (LastKey < Key) {
            sorted = FALSE;
            TSorting->A[I] = TSorting->A[I - 1];
            TSorting->A[I - 1] = State;
          } else {
            LastKey = Key;
          }
          if (I >= B_8) break;
        }
    }
    if (sorted) {
      goto EXIT_4;
    }
    sorted = TRUE;
    State = TSorting->A[Gen_LastReadState];
    LastKey = Sets_Card(&TablePtr->A[State].Terms) - TablePtr->A[State].Saving;
    for (I = Gen_LastReadState - 1; I >= 1; I += -1) {
      State = TSorting->A[I];
      Key = Sets_Card(&TablePtr->A[State].Terms) - TablePtr->A[State].Saving;
      if (LastKey > Key) {
        sorted = FALSE;
        TSorting->A[I] = TSorting->A[I + 1];
        TSorting->A[I + 1] = State;
      } else {
        LastKey = Key;
      }
    }
    if (sorted) {
      goto EXIT_4;
    }
  } EXIT_4:;
}

static void SortNStates
# ifdef __STDC__
()
# else
()
# endif
{
  BOOLEAN sorted;
  Automaton_tStateIndex I;
  Automaton_tStateIndex State;
  SHORTCARD Key, LastKey;

  for (;;) {
    sorted = TRUE;
    State = NSorting->A[1];
    LastKey = TablePtr->A[State].NontermCount;
    {
      Automaton_tStateIndex B_9 = 2, B_10 = Gen_LastReadState;

      if (B_9 <= B_10)
        for (I = B_9;; I += 1) {
          State = NSorting->A[I];
          Key = TablePtr->A[State].NontermCount;
          if (LastKey < Key) {
            sorted = FALSE;
            NSorting->A[I] = NSorting->A[I - 1];
            NSorting->A[I - 1] = State;
          } else {
            LastKey = Key;
          }
          if (I >= B_10) break;
        }
    }
    if (sorted) {
      goto EXIT_5;
    }
    sorted = TRUE;
    State = NSorting->A[Gen_LastReadState];
    LastKey = TablePtr->A[State].NontermCount;
    for (I = Gen_LastReadState - 1; I >= 1; I += -1) {
      State = NSorting->A[I];
      Key = TablePtr->A[State].NontermCount;
      if (LastKey > Key) {
        sorted = FALSE;
        NSorting->A[I] = NSorting->A[I + 1];
        NSorting->A[I + 1] = State;
      } else {
        LastKey = Key;
      }
    }
    if (sorted) {
      goto EXIT_5;
    }
  } EXIT_5:;
}

void Default__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Automaton__init();
    TokenTab__init();
    Gen__init();
    Automaton__init();
    DynArray__init();
    Gen__init();
    Memory__init();
    Sets__init();
    TokenTab__init();

    Default_NoDefault = FALSE;
  }
}
