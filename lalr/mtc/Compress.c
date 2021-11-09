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

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Compress
#include "Compress.h"
#endif

struct Compress_2 *Compress_Control;
struct Compress_3 *Compress_Base;
struct Compress_4 *Compress_Default;
LONGINT Compress_ControlCount, Compress_BaseCount, Compress_DefaultCount;
Automaton_tIndex Compress_TableMax;
Automaton_tIndex Compress_TableSize;
struct Compress_5 *Compress_NNext;
struct Compress_6 *Compress_NBase;
LONGINT Compress_NNextCount;
LONGINT Compress_NBaseCount;
Automaton_tIndex Compress_NTableMax;
Automaton_tIndex Compress_NTableSize;
Compress_TableElmt Compress_ElmtSize;
CARDINAL Compress_Filling;
CARDINAL Compress_NFilling;

#define InitTableMax   1500
#define InitNTableMax   500
struct S_1 {
    TokenTab_Vocabulary A[TokenTab_cMAXNonTerm + 2 + 1];
};
struct S_2 {
    TokenTab_Vocabulary A[TokenTab_cMAXNonTerm + 2 + 1];
};


void Compress_InitCompressTable
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tIndex b;
  Automaton_tStateIndex State;

  Compress_BaseCount = Gen_LastReadState + 1;
  DynArray_MakeArray((ADDRESS *)&Compress_Base, &Compress_BaseCount, (LONGINT)Compress_ElmtSize);
  Compress_DefaultCount = Gen_LastReadState + 1;
  DynArray_MakeArray((ADDRESS *)&Compress_Default, &Compress_DefaultCount, (LONGINT)Compress_ElmtSize);
  Compress_ControlCount = Gen_LastSymbol + InitTableMax;
  DynArray_MakeArray((ADDRESS *)&Compress_Control, &Compress_ControlCount, (LONGINT)sizeof(Compress_ControlType));
  Compress_TableMax = Compress_ControlCount - 1;
  {
    Automaton_tStateIndex B_1 = 0, B_2 = Gen_LastReadState;

    if (B_1 <= B_2)
      for (State = B_1;; State += 1) {
        Compress_Base->A[State] = 0;
        Compress_Default->A[State] = Gen_NoState;
        if (State >= B_2) break;
      }
  }
  {
    LONGCARD B_3 = 0, B_4 = Compress_TableMax;

    if (B_3 <= B_4)
      for (b = B_3;; b += 1) {
        Compress_Control->A[b].Next = Gen_NoState;
        Compress_Control->A[b].Check = Gen_NoState;
        if (b >= B_4) break;
      }
  }
  Compress_TableSize = 0;
}

void Compress_CompressTableLine
# ifdef __STDC__
(Automaton_tStateIndex State, Automaton_tStateIndex DefaultState, Gen_tTableLine *TableLine)
# else
(State, DefaultState, TableLine)
Automaton_tStateIndex State;
Automaton_tStateIndex DefaultState;
Gen_tTableLine *TableLine;
# endif
{
  Automaton_tIndex b;
  BOOLEAN Success;
  TokenTab_Vocabulary Symbol;
  Automaton_tIndex index;
  Automaton_tIndex OldTableMax;
  struct S_1 NextSym;
  TokenTab_Vocabulary StartSym, StopSym, PrevSym;

  Compress_Default->A[State] = DefaultState;
  Symbol = Gen_FirstTerminal;
  Success = FALSE;
  for (;;) {
    if (Symbol > Gen_LastTerminal) {
      goto EXIT_1;
    }
    if (TableLine->A[Symbol] != Gen_NoState) {
      StartSym = Symbol;
      PrevSym = Symbol;
      Success = TRUE;
      goto EXIT_1;
    }
    INC(Symbol);
  } EXIT_1:;
  INC(Symbol);
  for (;;) {
    if (Symbol > Gen_LastTerminal) {
      goto EXIT_2;
    }
    if (TableLine->A[Symbol] != Gen_NoState) {
      NextSym.A[PrevSym] = Symbol;
      PrevSym = Symbol;
    }
    INC(Symbol);
  } EXIT_2:;
  StopSym = PrevSym;
  b = 0;
  if (Success) {
    for (;;) {
      Success = TRUE;
      Symbol = StartSym;
      for (;;) {
        if (Compress_Control->A[b + Symbol].Check != Gen_NoState) {
          Success = FALSE;
          goto EXIT_4;
        }
        if (Symbol == StopSym) {
          goto EXIT_4;
        }
        Symbol = NextSym.A[Symbol];
      } EXIT_4:;
      if (Success) {
        goto EXIT_3;
      }
      INC(b);
      if (b + Gen_LastTerminal > Compress_TableMax) {
        OldTableMax = Compress_TableMax;
        DynArray_ExtendArray((ADDRESS *)&Compress_Control, &Compress_ControlCount, (LONGINT)sizeof(Compress_ControlType));
        Compress_TableMax = Compress_ControlCount - 1;
        {
          LONGCARD B_5 = OldTableMax + 1, B_6 = Compress_TableMax;

          if (B_5 <= B_6)
            for (index = B_5;; index += 1) {
              Compress_Control->A[index].Next = Gen_NoState;
              Compress_Control->A[index].Check = Gen_NoState;
              if (index >= B_6) break;
            }
        }
      }
    } EXIT_3:;
  } else {
    Success = TRUE;
  }
  Compress_Base->A[State] = b;
  Compress_TableSize = General_Max((LONGINT)Compress_TableSize, (LONGINT)b);
  {
    TokenTab_Vocabulary B_7 = Gen_FirstTerminal, B_8 = Gen_LastTerminal;

    if (B_7 <= B_8)
      for (Symbol = B_7;; Symbol += 1) {
        if (TableLine->A[Symbol] != Gen_NoState) {
          Compress_Control->A[b + Symbol].Check = State;
          Compress_Control->A[b + Symbol].Next = TableLine->A[Symbol];
          INC(Compress_Filling);
        }
        if (Symbol >= B_8) break;
      }
  }
}

void Compress_InitCompressNTable
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tIndex b;
  Automaton_tStateIndex State;

  Compress_NBaseCount = Gen_LastReadState + 1;
  DynArray_MakeArray((ADDRESS *)&Compress_NBase, &Compress_NBaseCount, (LONGINT)Compress_ElmtSize);
  Compress_NNextCount = Gen_LastSymbol + InitNTableMax;
  DynArray_MakeArray((ADDRESS *)&Compress_NNext, &Compress_NNextCount, (LONGINT)sizeof(Compress_TableElmt));
  Compress_NTableMax = Compress_NNextCount - 1;
  {
    Automaton_tStateIndex B_9 = 0, B_10 = Gen_LastReadState;

    if (B_9 <= B_10)
      for (State = B_9;; State += 1) {
        Compress_NBase->A[State] = 0;
        if (State >= B_10) break;
      }
  }
  {
    LONGCARD B_11 = 0, B_12 = Compress_NTableMax;

    if (B_11 <= B_12)
      for (b = B_11;; b += 1) {
        Compress_NNext->A[b] = Gen_NoState;
        if (b >= B_12) break;
      }
  }
  Compress_NTableSize = 0;
}

void Compress_CompressNTableLine
# ifdef __STDC__
(Automaton_tStateIndex State, Gen_tTableLine *TableLine)
# else
(State, TableLine)
Automaton_tStateIndex State;
Gen_tTableLine *TableLine;
# endif
{
  Automaton_tIndex b;
  BOOLEAN Success;
  TokenTab_Vocabulary Symbol;
  Automaton_tIndex index;
  Automaton_tIndex OldTableMax;
  struct S_2 NextSym;
  TokenTab_Vocabulary StartSym, StopSym, PrevSym;

  Symbol = Gen_LastTerminal + 1;
  Success = FALSE;
  for (;;) {
    if (Symbol > Gen_LastSymbol) {
      goto EXIT_5;
    }
    if (TableLine->A[Symbol] != Gen_NoState) {
      StartSym = Symbol;
      PrevSym = Symbol;
      Success = TRUE;
      goto EXIT_5;
    }
    INC(Symbol);
  } EXIT_5:;
  INC(Symbol);
  for (;;) {
    if (Symbol > Gen_LastSymbol) {
      goto EXIT_6;
    }
    if (TableLine->A[Symbol] != Gen_NoState) {
      NextSym.A[PrevSym] = Symbol;
      PrevSym = Symbol;
    }
    INC(Symbol);
  } EXIT_6:;
  StopSym = PrevSym;
  b = 0;
  if (Success) {
    for (;;) {
      Success = TRUE;
      Symbol = StartSym;
      for (;;) {
        if (Compress_NNext->A[b + Symbol] != Gen_NoState && Compress_NNext->A[b + Symbol] != TableLine->A[Symbol]) {
          Success = FALSE;
          goto EXIT_8;
        }
        if (Symbol == StopSym) {
          goto EXIT_8;
        }
        Symbol = NextSym.A[Symbol];
      } EXIT_8:;
      if (Success) {
        goto EXIT_7;
      }
      INC(b);
      if (b + Gen_LastSymbol > Compress_NTableMax) {
        OldTableMax = Compress_NTableMax;
        DynArray_ExtendArray((ADDRESS *)&Compress_NNext, &Compress_NNextCount, (LONGINT)sizeof(Compress_TableElmt));
        Compress_NTableMax = Compress_NNextCount - 1;
        {
          LONGCARD B_13 = OldTableMax + 1, B_14 = Compress_NTableMax;

          if (B_13 <= B_14)
            for (index = B_13;; index += 1) {
              Compress_NNext->A[index] = Gen_NoState;
              if (index >= B_14) break;
            }
        }
      }
    } EXIT_7:;
  } else {
    Success = TRUE;
  }
  Compress_NBase->A[State] = b;
  Compress_NTableSize = General_Max((LONGINT)Compress_NTableSize, (LONGINT)b);
  {
    TokenTab_Vocabulary B_15 = Gen_LastTerminal + 1, B_16 = Gen_LastSymbol;

    if (B_15 <= B_16)
      for (Symbol = B_15;; Symbol += 1) {
        if (TableLine->A[Symbol] != Gen_NoState) {
          Compress_NNext->A[b + Symbol] = TableLine->A[Symbol];
          INC(Compress_NFilling);
        }
        if (Symbol >= B_16) break;
      }
  }
}

void Compress__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Automaton__init();
    Gen__init();
    Automaton__init();
    DynArray__init();
    Gen__init();
    General__init();
    TokenTab__init();

    Compress_ElmtSize = sizeof(Compress_TableElmt);
    Compress_Filling = 0;
    Compress_NFilling = 0;
  }
}
