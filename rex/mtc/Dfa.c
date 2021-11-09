#include "SYSTEM_.h"

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

#ifndef DEFINITION_Classes
#include "Classes.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

CHAR Dfa_LastCh;
CHAR Dfa_OldLastCh;
Dfa_DStateRange Dfa_DStateCount;
Dfa_DStateRange Dfa_EobState;
Dfa_DStateRange Dfa_EobDefaultState;
Sets_tSet Dfa_AmbiguousStates;
Sets_tSet Dfa_CyclicStates;
Dfa_DStateRange Dfa_MaxAmbiguousState;
INTEGER Dfa_MinimizeSavings;
INTEGER Dfa_DefaultSavings;

#define InitialTableSize   256
typedef struct S_10 {
    Dfa_DStateRange A[256];
} *RowType;
typedef struct S_1 {
    RowType Row;
    Sets_tSet Semantics;
    Dfa_DStateRange Default;
    Sets_tSet StartSet;
    Dfa_DStateRange EobTrans;
    CHAR FirstElmt;
    CHAR LastElmt;
} DStateInfo;
typedef struct S_2 {
    DStateInfo A[100000 + 1];
} DStateTable;
typedef struct S_3 {
    Sets_tSet A[100000 + 1];
} SuccSet;
static DStateTable *TablePtr;
static LONGINT TableSize;
static SuccSet *SuccSetPtr;
static LONGINT SuccSetSize;
static void ReleaseDState ARGS((Dfa_DStateRange State));
typedef Dfa_DStateRange BlockRange;
typedef struct S_4 {
    Dfa_DStateRange Partition;
    SHORTCARD Card;
    Sets_tSet Semantics;
    BOOLEAN Used;
    BlockRange MapBlockToBlock;
    BlockRange MapStateToBlock;
    BlockRange NewMapStateToBlock;
    Dfa_DStateRange NextMember;
    Dfa_DStateRange Location;
} C_2_DBElmt;
typedef struct S_5 {
    C_2_DBElmt A[100000 + 1];
} C_3_DB;
static void WritePartition ARGS(());
typedef struct S_6 {
    SHORTCARD A[100000 + 1];
} PredCount;
typedef struct S_7 {
    Sets_tSet A[100000 + 1];
} C_1_Succ;
typedef struct S_8 {
    Sets_tSet Domain;
    Sets_tSet Defaults;
    Sets_tSet Users;
    SHORTCARD Savings;
    SHORTCARD DFN;
    SHORTCARD DFNToState;
} DBElmt;
typedef struct S_9 {
    DBElmt A[100000 + 1];
} DB;
static void DepthFirstTraversal ARGS((Dfa_DStateRange State));

static C_3_DB* *G_1_DBPtr;
static BlockRange *G_2_BlockCount;
static BlockRange *G_3_Block;
static Dfa_DStateRange *G_4_State;
static DB* *G_5_DBPtr;
static Sets_tSet *G_6_WorkingSet;
static Sets_tSet *G_7_Marked;
static SHORTCARD *G_8_DFN;
static Dfa_DStateRange *G_9_To;
static Dfa_DStateRange *G_10_From;

Dfa_DStateRange Dfa_MakeDState
# ifdef __STDC__
()
# else
()
# endif
{
  CHAR Ch;
  LONGINT RowSize;

  INC(Dfa_DStateCount);
  if ((SHORTINT)Dfa_DStateCount == TableSize) {
    DynArray_ExtendArray((ADDRESS *)&TablePtr, &TableSize, (LONGINT)sizeof(DStateInfo));
  }
  {
    register DStateInfo *W_1 = &TablePtr->A[Dfa_DStateCount];

    RowSize = ORD(Dfa_LastCh) + 1;
    DynArray_MakeArray((ADDRESS *)&W_1->Row, &RowSize, (LONGINT)sizeof(Dfa_DStateRange));
    {
      CHAR B_1 = '\0', B_2 = Dfa_LastCh;

      if (B_1 <= B_2)
        for (Ch = B_1;; Ch += 1) {
          W_1->Row->A[Ch] = Dfa_DNoState;
          if (Ch >= B_2) break;
        }
    }
    Sets_MakeSet(&W_1->Semantics, (Sets_tElement)GenTabs_PatternCount);
    W_1->Default = Dfa_DNoState;
    Sets_MakeSet(&W_1->StartSet, (Sets_tElement)GenTabs_StartStateCount);
    W_1->EobTrans = Dfa_DNoState;
    W_1->FirstElmt = Dfa_LastCh;
    W_1->LastElmt = Dfa_FirstCh;
  }
  return Dfa_DStateCount;
}

static void ReleaseDState
# ifdef __STDC__
(Dfa_DStateRange State)
# else
(State)
Dfa_DStateRange State;
# endif
{
  LONGINT RowSize;

  DEC(Dfa_DStateCount);
  RowSize = ORD(Dfa_LastCh) + 1;
  DynArray_ReleaseArray((ADDRESS *)&TablePtr->A[State].Row, &RowSize, (LONGINT)sizeof(Dfa_DStateRange));
  Sets_ReleaseSet(&TablePtr->A[State].Semantics);
  Sets_ReleaseSet(&TablePtr->A[State].StartSet);
}

Dfa_DStateRange Dfa_GetEobTrans
# ifdef __STDC__
(Dfa_DStateRange State)
# else
(State)
Dfa_DStateRange State;
# endif
{
  return TablePtr->A[State].EobTrans;
}

Dfa_DStateRange Dfa_GetDefault
# ifdef __STDC__
(Dfa_DStateRange State)
# else
(State)
Dfa_DStateRange State;
# endif
{
  return TablePtr->A[State].Default;
}

void Dfa_PutDefault
# ifdef __STDC__
(Dfa_DStateRange State, Dfa_DStateRange DefaultState)
# else
(State, DefaultState)
Dfa_DStateRange State, DefaultState;
# endif
{
  TablePtr->A[State].Default = DefaultState;
}

void Dfa_GetDSemantics
# ifdef __STDC__
(Dfa_DStateRange State, Sets_tSet *Semantics)
# else
(State, Semantics)
Dfa_DStateRange State;
Sets_tSet *Semantics;
# endif
{
  Sets_Assign(Semantics, TablePtr->A[State].Semantics);
}

void Dfa_PutDSemantics
# ifdef __STDC__
(Dfa_DStateRange State, Sets_tSet Semantics)
# else
(State, Semantics)
Dfa_DStateRange State;
Sets_tSet Semantics;
# endif
{
  Sets_Assign(&TablePtr->A[State].Semantics, Semantics);
}

void Dfa_GetStartSet
# ifdef __STDC__
(Dfa_DStateRange State, Sets_tSet *StartSet)
# else
(State, StartSet)
Dfa_DStateRange State;
Sets_tSet *StartSet;
# endif
{
  Sets_Assign(StartSet, TablePtr->A[State].StartSet);
}

void Dfa_PutStartSet
# ifdef __STDC__
(Dfa_DStateRange State, Sets_tSet StartSet)
# else
(State, StartSet)
Dfa_DStateRange State;
Sets_tSet StartSet;
# endif
{
  Sets_Assign(&TablePtr->A[State].StartSet, StartSet);
}

Dfa_DStateRange Dfa_GetTable
# ifdef __STDC__
(Dfa_DStateRange State, CHAR Ch)
# else
(State, Ch)
Dfa_DStateRange State;
CHAR Ch;
# endif
{
  Dfa_DStateRange NextState;

  do {
    NextState = TablePtr->A[State].Row->A[Ch];
    if (NextState != Dfa_DNoState) {
      return NextState;
    }
    State = TablePtr->A[State].Default;
  } while (!(State == Dfa_DNoState));
  return Dfa_DNoState;
}

void Dfa_PutTable
# ifdef __STDC__
(Dfa_DStateRange State, CHAR Ch, Dfa_DStateRange NextState)
# else
(State, Ch, NextState)
Dfa_DStateRange State;
CHAR Ch;
Dfa_DStateRange NextState;
# endif
{
  {
    register DStateInfo *W_2 = &TablePtr->A[State];

    W_2->Row->A[Ch] = NextState;
    if (NextState != Dfa_DNoState) {
      if (Ch < W_2->FirstElmt) {
        W_2->FirstElmt = Ch;
      }
      if (Ch > W_2->LastElmt) {
        W_2->LastElmt = Ch;
      }
    } else {
      if (Ch == W_2->FirstElmt && Ch < Dfa_LastCh) {
        INC(W_2->FirstElmt);
      }
      if (Ch == W_2->LastElmt && Ch > Dfa_FirstCh) {
        DEC(W_2->LastElmt);
      }
    }
  }
}

Dfa_DStateRange Dfa_GetTableNoDef
# ifdef __STDC__
(Dfa_DStateRange State, CHAR Ch)
# else
(State, Ch)
Dfa_DStateRange State;
CHAR Ch;
# endif
{
  return TablePtr->A[State].Row->A[Ch];
}

CHAR Dfa_GetFirst
# ifdef __STDC__
(Dfa_DStateRange State)
# else
(State)
Dfa_DStateRange State;
# endif
{
  return TablePtr->A[State].FirstElmt;
}

CHAR Dfa_GetLast
# ifdef __STDC__
(Dfa_DStateRange State)
# else
(State)
Dfa_DStateRange State;
# endif
{
  return TablePtr->A[State].LastElmt;
}

void Dfa_WriteDfa
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange State;
  CHAR Ch;
  INTEGER Count;

  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"DFA :", 5L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteNl((System_tFile)IO_StdOutput);
  {
    SHORTINT B_3 = 1, B_4 = Dfa_DStateCount;

    if (B_3 <= B_4)
      for (State = B_3;; State += 1) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"State, Default, EobTrans, Semantics, StartSet =", 47L);
        IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)State, 5L);
        IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)TablePtr->A[State].Default, 5L);
        IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)TablePtr->A[State].EobTrans, 5L);
        Layout_WriteSpace((System_tFile)IO_StdOutput);
        Sets_WriteSet((System_tFile)IO_StdOutput, TablePtr->A[State].Semantics);
        Layout_WriteSpace((System_tFile)IO_StdOutput);
        Sets_WriteSet((System_tFile)IO_StdOutput, TablePtr->A[State].StartSet);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Count = 0;
        {
          CHAR B_5 = Dfa_GetFirst(State), B_6 = Dfa_GetLast(State);

          if (B_5 <= B_6)
            for (Ch = B_5;; Ch += 1) {
              if (Dfa_GetTableNoDef(State, Ch) != Dfa_DNoState) {
                if (Count == 10) {
                  IO_WriteNl((System_tFile)IO_StdOutput);
                  Count = 0;
                }
                INC(Count);
                Layout_WriteChar((System_tFile)IO_StdOutput, Ch);
                Layout_WriteSpace((System_tFile)IO_StdOutput);
                IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Dfa_GetTable(State, Ch), 1L);
                IO_WriteC((System_tFile)IO_StdOutput, ',');
                Layout_WriteSpace((System_tFile)IO_StdOutput);
              }
              if (Ch >= B_6) break;
            }
        }
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        if (State >= B_4) break;
      }
  }
}

static void WritePartition
# ifdef __STDC__
()
# else
()
# endif
{
  {
    SHORTINT B_7 = 1, B_8 = *G_2_BlockCount;

    if (B_7 <= B_8)
      for (*G_3_Block = B_7;; *G_3_Block += 1) {
        IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)(*G_3_Block), 3L);
        IO_WriteC((System_tFile)IO_StdOutput, ':');
        *G_4_State = (*G_1_DBPtr)->A[*G_3_Block].Partition;
        while (*G_4_State != Dfa_DNoState) {
          IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)(*G_4_State), 3L);
          *G_4_State = (*G_1_DBPtr)->A[*G_4_State].NextMember;
        }
        IO_WriteNl((System_tFile)IO_StdOutput);
        if (*G_3_Block >= B_8) break;
      }
  }
}

void Dfa_MinimizeDfa
# ifdef __STDC__
()
# else
()
# endif
{
  C_3_DB *DBPtr;
  LONGINT DBSize;
  BlockRange BlockCount;
  BlockRange OldBlockCount;
  BlockRange Block;
  BlockRange TargetBlock;
  BlockRange TargetBlockCount;
  BlockRange i;
  BlockRange Gap;
  BlockRange InitGap;
  BlockRange NextGap;
  Sets_tSet BlockSet;
  Sets_tSet dSemantics;
  Dfa_DStateRange State;
  Dfa_DStateRange NextState;
  CHAR Ch;
  SHORTCARD Pattern;
  Sets_tSet dStates;
  RowType InitGapRow;
  C_3_DB* *L_1;
  BlockRange *L_2;
  BlockRange *L_3;
  Dfa_DStateRange *L_4;

  L_1 = G_1_DBPtr;
  G_1_DBPtr = &DBPtr;
  L_2 = G_2_BlockCount;
  G_2_BlockCount = &BlockCount;
  L_3 = G_3_Block;
  G_3_Block = &Block;
  L_4 = G_4_State;
  G_4_State = &State;
  DBSize = Dfa_DStateCount + 2;
  DynArray_MakeArray((ADDRESS *)&DBPtr, &DBSize, (LONGINT)sizeof(C_2_DBElmt));
  Sets_MakeSet(&dSemantics, (Sets_tElement)GenTabs_PatternCount);
  Sets_MakeSet(&dStates, (Sets_tElement)Dfa_DStateCount);
  DBPtr->A[Dfa_DNoState].MapStateToBlock = 0;
  {
    SHORTINT B_9 = 1, B_10 = GenTabs_StartStateCount;

    if (B_9 <= B_10)
      for (State = B_9;; State += 1) {
        Block = State;
        DBPtr->A[Block].Partition = State;
        DBPtr->A[Block].Card = 1;
        DBPtr->A[State].NextMember = Dfa_DNoState;
        DBPtr->A[State].MapStateToBlock = Block;
        if (State >= B_10) break;
      }
  }
  BlockCount = GenTabs_StartStateCount;
  {
    SHORTINT B_11 = GenTabs_StartStateCount + 1, B_12 = Dfa_DStateCount;

    if (B_11 <= B_12)
      for (State = B_11;; State += 1) {
        Block = GenTabs_StartStateCount + 1;
        for (;;) {
          if (Block > BlockCount) {
            INC(BlockCount);
            Block = BlockCount;
            DBPtr->A[Block].Partition = Dfa_DNoState;
            DBPtr->A[Block].Card = 0;
            Sets_MakeSet(&DBPtr->A[Block].Semantics, (Sets_tElement)GenTabs_PatternCount);
            Dfa_GetDSemantics(State, &DBPtr->A[Block].Semantics);
            goto EXIT_1;
          }
          Dfa_GetDSemantics(State, &dSemantics);
          if (Sets_IsEmpty(dSemantics) && Sets_IsEmpty(DBPtr->A[Block].Semantics) || !Sets_IsEmpty(dSemantics) && !Sets_IsEmpty(DBPtr->A[Block].Semantics) && Sets_Minimum(&dSemantics) == Sets_Minimum(&DBPtr->A[Block].Semantics)) {
            goto EXIT_1;
          }
          INC(Block);
        } EXIT_1:;
        DBPtr->A[State].NextMember = DBPtr->A[Block].Partition;
        DBPtr->A[Block].Partition = State;
        INC(DBPtr->A[Block].Card);
        DBPtr->A[State].MapStateToBlock = Block;
        if (State >= B_12) break;
      }
  }
  {
    SHORTINT B_13 = GenTabs_StartStateCount + 1, B_14 = BlockCount;

    if (B_13 <= B_14)
      for (Block = B_13;; Block += 1) {
        Sets_ReleaseSet(&DBPtr->A[Block].Semantics);
        if (Block >= B_14) break;
      }
  }
  do {
    OldBlockCount = BlockCount;
    Block = GenTabs_StartStateCount + 1;
    while (Block <= BlockCount) {
      if (DBPtr->A[Block].Card > 1) {
        {
          CHAR B_15 = Dfa_FirstCh, B_16 = Dfa_LastCh;

          if (B_15 <= B_16)
            for (Ch = B_15;; Ch += 1) {
              TargetBlockCount = 0;
              {
                SHORTINT B_17 = 0, B_18 = BlockCount;

                if (B_17 <= B_18)
                  for (i = B_17;; i += 1) {
                    DBPtr->A[i].Used = FALSE;
                    if (i >= B_18) break;
                  }
              }
              State = DBPtr->A[Block].Partition;
              while (State != Dfa_DNoState) {
                TargetBlock = DBPtr->A[Dfa_GetTableNoDef(State, Ch)].MapStateToBlock;
                if (!DBPtr->A[TargetBlock].Used) {
                  if (TargetBlockCount == 0) {
                    DBPtr->A[TargetBlock].MapBlockToBlock = Block;
                  } else {
                    INC(BlockCount);
                    DBPtr->A[BlockCount].Partition = Dfa_DNoState;
                    DBPtr->A[BlockCount].Card = 0;
                    DBPtr->A[TargetBlock].MapBlockToBlock = BlockCount;
                  }
                  DBPtr->A[TargetBlock].Used = TRUE;
                  INC(TargetBlockCount);
                }
                DBPtr->A[State].NewMapStateToBlock = DBPtr->A[TargetBlock].MapBlockToBlock;
                State = DBPtr->A[State].NextMember;
              }
              if (TargetBlockCount > 1) {
                State = DBPtr->A[Block].Partition;
                DBPtr->A[Block].Partition = Dfa_DNoState;
                DBPtr->A[Block].Card = 0;
                while (State != Dfa_DNoState) {
                  NextState = DBPtr->A[State].NextMember;
                  TargetBlock = DBPtr->A[State].NewMapStateToBlock;
                  DBPtr->A[State].NextMember = DBPtr->A[TargetBlock].Partition;
                  DBPtr->A[TargetBlock].Partition = State;
                  INC(DBPtr->A[TargetBlock].Card);
                  DBPtr->A[State].MapStateToBlock = TargetBlock;
                  State = NextState;
                }
              }
              if (Ch >= B_16) break;
            }
        }
      }
      INC(Block);
    }
  } while (!(OldBlockCount == BlockCount));
  {
    SHORTINT B_19 = 1, B_20 = BlockCount;

    if (B_19 <= B_20)
      for (Block = B_19;; Block += 1) {
        State = DBPtr->A[Block].Partition;
        {
          CHAR B_21 = Dfa_GetFirst(State), B_22 = Dfa_GetLast(State);

          if (B_21 <= B_22)
            for (Ch = B_21;; Ch += 1) {
              NextState = Dfa_GetTableNoDef(State, Ch);
              if (NextState != Dfa_DNoState) {
                Dfa_PutTable(State, Ch, DBPtr->A[NextState].MapStateToBlock);
              }
              if (Ch >= B_22) break;
            }
        }
        if (Block >= B_20) break;
      }
  }
  Sets_MakeSet(&BlockSet, (Sets_tElement)BlockCount);
  Sets_Complement(&BlockSet);
  Sets_Exclude(&BlockSet, (Sets_tElement)Dfa_DNoState);
  {
    SHORTINT B_23 = 1, B_24 = Dfa_DStateCount;

    if (B_23 <= B_24)
      for (State = B_23;; State += 1) {
        DBPtr->A[State].Location = State;
        if (State >= B_24) break;
      }
  }
  InitGap = Dfa_MakeDState();
  InitGapRow = TablePtr->A[InitGap].Row;
  while (!Sets_IsEmpty(BlockSet)) {
    Block = Sets_Extract(&BlockSet);
    if (Block != DBPtr->A[Block].Partition) {
      TablePtr->A[InitGap].Row = TablePtr->A[Block].Row;
      TablePtr->A[InitGap].FirstElmt = TablePtr->A[Block].FirstElmt;
      TablePtr->A[InitGap].LastElmt = TablePtr->A[Block].LastElmt;
      Dfa_GetDSemantics(Block, &dSemantics);
      Dfa_PutDSemantics(InitGap, dSemantics);
      DBPtr->A[Block].Location = InitGap;
      Gap = Block;
      do {
        NextGap = DBPtr->A[DBPtr->A[Gap].Partition].Location;
        TablePtr->A[Gap].Row = TablePtr->A[NextGap].Row;
        TablePtr->A[Gap].FirstElmt = TablePtr->A[NextGap].FirstElmt;
        TablePtr->A[Gap].LastElmt = TablePtr->A[NextGap].LastElmt;
        Dfa_GetDSemantics(NextGap, &dSemantics);
        Dfa_PutDSemantics(Gap, dSemantics);
        Sets_Exclude(&BlockSet, (Sets_tElement)Gap);
        Gap = NextGap;
      } while (!(Gap > BlockCount));
      InitGap = Gap;
    }
  }
  TablePtr->A[InitGap].Row = InitGapRow;
  {
    SHORTCARD B_25 = 1, B_26 = GenTabs_PatternCount - 2;

    if (B_25 <= B_26)
      for (Pattern = B_25;; Pattern += 1) {
        if (GenTabs_PatternTablePtr->A[Pattern].ContextLng == GenTabs_VariableContext) {
          Sets_Assign(&dStates, GenTabs_PatternTablePtr->A[Pattern].DContext);
          Sets_AssignEmpty(&GenTabs_PatternTablePtr->A[Pattern].DContext);
          while (!Sets_IsEmpty(dStates)) {
            State = DBPtr->A[Sets_Extract(&dStates)].MapStateToBlock;
            Sets_Include(&GenTabs_PatternTablePtr->A[Pattern].DContext, (Sets_tElement)State);
          }
        }
        if (Pattern >= B_26) break;
      }
  }
  Dfa_MinimizeSavings = Dfa_DStateCount - BlockCount;
  Sets_ReleaseSet(&BlockSet);
  Sets_ReleaseSet(&dSemantics);
  Sets_ReleaseSet(&dStates);
  {
    SHORTINT B_27 = Dfa_DStateCount, B_28 = BlockCount + 1;

    if (B_27 >= B_28)
      for (State = B_27;; State += -1) {
        ReleaseDState(State);
        if (State <= B_28) break;
      }
  }
  DynArray_ReleaseArray((ADDRESS *)&DBPtr, &DBSize, (LONGINT)sizeof(C_2_DBElmt));
  G_1_DBPtr = L_1;
  G_2_BlockCount = L_2;
  G_3_Block = L_3;
  G_4_State = L_4;
}

void Dfa_ComputeSuccGraph
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange State;
  Dfa_DStateRange NextState;
  CHAR Ch;

  SuccSetSize = Dfa_DStateCount + 1;
  DynArray_MakeArray((ADDRESS *)&SuccSetPtr, &SuccSetSize, (LONGINT)sizeof(Sets_tSet));
  {
    SHORTINT B_29 = 1, B_30 = Dfa_DStateCount;

    if (B_29 <= B_30)
      for (State = B_29;; State += 1) {
        Sets_MakeSet(&SuccSetPtr->A[State], (Sets_tElement)Dfa_DStateCount);
        {
          CHAR B_31 = Dfa_GetFirst(State), B_32 = Dfa_GetLast(State);

          if (B_31 <= B_32)
            for (Ch = B_31;; Ch += 1) {
              NextState = Dfa_GetTableNoDef(State, Ch);
              if (NextState != Dfa_DNoState) {
                Sets_Include(&SuccSetPtr->A[State], (Sets_tElement)NextState);
              }
              if (Ch >= B_32) break;
            }
        }
        if (State >= B_30) break;
      }
  }
}

void Dfa_ComputeAmbiguousStates
# ifdef __STDC__
()
# else
()
# endif
{
  PredCount *PredCountPtr;
  LONGINT PredCountSize;
  PredCount *PredCount2Ptr;
  LONGINT PredCount2Size;
  Dfa_DStateRange State, State2;
  Dfa_DStateRange Successor;
  Sets_tSet UnambiguousStates;
  CHAR Ch;

  PredCountSize = Dfa_DStateCount + 1;
  DynArray_MakeArray((ADDRESS *)&PredCountPtr, &PredCountSize, (LONGINT)sizeof(SHORTCARD));
  PredCount2Size = Dfa_DStateCount + 1;
  DynArray_MakeArray((ADDRESS *)&PredCount2Ptr, &PredCount2Size, (LONGINT)sizeof(SHORTCARD));
  Dfa_MaxAmbiguousState = Dfa_DStateCount;
  Sets_MakeSet(&UnambiguousStates, (Sets_tElement)Dfa_MaxAmbiguousState);
  Sets_MakeSet(&Dfa_AmbiguousStates, (Sets_tElement)Dfa_MaxAmbiguousState);
  {
    SHORTINT B_33 = 0, B_34 = Dfa_DStateCount;

    if (B_33 <= B_34)
      for (State = B_33;; State += 1) {
        PredCountPtr->A[State] = 0;
        if (State >= B_34) break;
      }
  }
  {
    SHORTINT B_35 = 1, B_36 = GenTabs_StartStateCount;

    if (B_35 <= B_36)
      for (State = B_35;; State += 1) {
        {
          SHORTINT B_37 = 0, B_38 = Dfa_DStateCount;

          if (B_37 <= B_38)
            for (State2 = B_37;; State2 += 1) {
              PredCount2Ptr->A[State2] = 0;
              if (State2 >= B_38) break;
            }
        }
        {
          CHAR B_39 = Dfa_GetFirst(State), B_40 = Dfa_GetLast(State);

          if (B_39 <= B_40)
            for (Ch = B_39;; Ch += 1) {
              Successor = Dfa_GetTableNoDef(State, Ch);
              if (Successor != Dfa_DNoState) {
                INC(PredCount2Ptr->A[Successor]);
              }
              if (Ch >= B_40) break;
            }
        }
        {
          SHORTINT B_41 = 0, B_42 = Dfa_DStateCount;

          if (B_41 <= B_42)
            for (State2 = B_41;; State2 += 1) {
              PredCountPtr->A[State2] = General_Max((LONGINT)PredCountPtr->A[State2], (LONGINT)PredCount2Ptr->A[State2]);
              if (State2 >= B_42) break;
            }
        }
        if (State >= B_36) break;
      }
  }
  {
    SHORTINT B_43 = GenTabs_StartStateCount + 1, B_44 = Dfa_DStateCount;

    if (B_43 <= B_44)
      for (State = B_43;; State += 1) {
        {
          CHAR B_45 = Dfa_GetFirst(State), B_46 = Dfa_GetLast(State);

          if (B_45 <= B_46)
            for (Ch = B_45;; Ch += 1) {
              Successor = Dfa_GetTableNoDef(State, Ch);
              if (Successor != Dfa_DNoState) {
                INC(PredCountPtr->A[Successor]);
              }
              if (Ch >= B_46) break;
            }
        }
        if (State >= B_44) break;
      }
  }
  {
    SHORTINT B_47 = 1, B_48 = GenTabs_StartStateCount;

    if (B_47 <= B_48)
      for (State = B_47;; State += 1) {
        Sets_Include(&UnambiguousStates, (Sets_tElement)State);
        if (State >= B_48) break;
      }
  }
  Sets_Complement(&Dfa_AmbiguousStates);
  Sets_Exclude(&Dfa_AmbiguousStates, (Sets_tElement)Dfa_DNoState);
  while (!Sets_IsEmpty(UnambiguousStates)) {
    State = Sets_Extract(&UnambiguousStates);
    Sets_Exclude(&Dfa_AmbiguousStates, (Sets_tElement)State);
    {
      SHORTINT B_49 = 1, B_50 = Dfa_DStateCount;

      if (B_49 <= B_50)
        for (Successor = B_49;; Successor += 1) {
          if (Sets_IsElement((Sets_tElement)Successor, &SuccSetPtr->A[State])) {
            if (PredCountPtr->A[Successor] == 1) {
              Sets_Include(&UnambiguousStates, (Sets_tElement)Successor);
            }
          }
          if (Successor >= B_50) break;
        }
    }
  }
  Sets_ReleaseSet(&UnambiguousStates);
  DynArray_ReleaseArray((ADDRESS *)&PredCountPtr, &PredCountSize, (LONGINT)sizeof(SHORTCARD));
  DynArray_ReleaseArray((ADDRESS *)&PredCount2Ptr, &PredCount2Size, (LONGINT)sizeof(SHORTCARD));
}

void Dfa_ComputeCyclicStates
# ifdef __STDC__
()
# else
()
# endif
{
  C_1_Succ *SuccPtr;
  LONGINT SuccSize;
  Dfa_DStateRange State;
  Dfa_DStateRange i, j;

  SuccSize = Dfa_DStateCount + 1;
  DynArray_MakeArray((ADDRESS *)&SuccPtr, &SuccSize, (LONGINT)sizeof(Sets_tSet));
  {
    SHORTINT B_51 = 1, B_52 = Dfa_DStateCount;

    if (B_51 <= B_52)
      for (State = B_51;; State += 1) {
        Sets_MakeSet(&SuccPtr->A[State], (Sets_tElement)Dfa_DStateCount);
        Sets_Assign(&SuccPtr->A[State], SuccSetPtr->A[State]);
        if (State >= B_52) break;
      }
  }
  {
    SHORTINT B_53 = 1, B_54 = Dfa_DStateCount;

    if (B_53 <= B_54)
      for (j = B_53;; j += 1) {
        {
          SHORTINT B_55 = 1, B_56 = Dfa_DStateCount;

          if (B_55 <= B_56)
            for (i = B_55;; i += 1) {
              if (Sets_IsElement((Sets_tElement)j, &SuccPtr->A[i])) {
                Sets_Union(&SuccPtr->A[i], SuccPtr->A[j]);
              }
              if (i >= B_56) break;
            }
        }
        if (j >= B_54) break;
      }
  }
  Sets_MakeSet(&Dfa_CyclicStates, (Sets_tElement)Dfa_DStateCount);
  {
    SHORTINT B_57 = 1, B_58 = Dfa_DStateCount;

    if (B_57 <= B_58)
      for (State = B_57;; State += 1) {
        if (Sets_IsElement((Sets_tElement)State, &SuccPtr->A[State])) {
          Sets_Include(&Dfa_CyclicStates, (Sets_tElement)State);
        }
        Sets_ReleaseSet(&SuccPtr->A[State]);
        if (State >= B_58) break;
      }
  }
  DynArray_ReleaseArray((ADDRESS *)&SuccPtr, &SuccSize, (LONGINT)sizeof(Sets_tSet));
}

void Dfa_ComputeStartSets
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange State1, State2;
  Sets_tSet StartSet1, StartSet2, WorkingSet;

  Sets_MakeSet(&StartSet1, (Sets_tElement)GenTabs_StartStateCount);
  Sets_MakeSet(&StartSet2, (Sets_tElement)GenTabs_StartStateCount);
  Sets_MakeSet(&WorkingSet, (Sets_tElement)Dfa_DStateCount);
  {
    SHORTINT B_59 = 1, B_60 = GenTabs_StartStateCount;

    if (B_59 <= B_60)
      for (State1 = B_59;; State1 += 1) {
        {
          SHORTINT B_61 = 1, B_62 = Dfa_DStateCount;

          if (B_61 <= B_62)
            for (State2 = B_61;; State2 += 1) {
              if (Sets_IsElement((Sets_tElement)State2, &SuccSetPtr->A[State1])) {
                Dfa_GetStartSet(State2, &StartSet2);
                Sets_Include(&StartSet2, (Sets_tElement)State1);
                Dfa_PutStartSet(State2, StartSet2);
              }
              if (State2 >= B_62) break;
            }
        }
        Sets_Union(&WorkingSet, SuccSetPtr->A[State1]);
        if (State1 >= B_60) break;
      }
  }
  while (!Sets_IsEmpty(WorkingSet)) {
    State1 = Sets_Extract(&WorkingSet);
    Dfa_GetStartSet(State1, &StartSet1);
    {
      SHORTINT B_63 = 1, B_64 = Dfa_DStateCount;

      if (B_63 <= B_64)
        for (State2 = B_63;; State2 += 1) {
          if (Sets_IsElement((Sets_tElement)State2, &SuccSetPtr->A[State1])) {
            Dfa_GetStartSet(State2, &StartSet2);
            if (!Sets_IsSubset(StartSet1, StartSet2)) {
              Sets_Union(&StartSet2, StartSet1);
              Dfa_PutStartSet(State2, StartSet2);
              Sets_Include(&WorkingSet, (Sets_tElement)State2);
            }
          }
          if (State2 >= B_64) break;
        }
    }
  }
  Sets_ReleaseSet(&StartSet1);
  Sets_ReleaseSet(&StartSet2);
  Sets_ReleaseSet(&WorkingSet);
}

void Dfa_SaveEobTransitions
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange State;

  {
    SHORTINT B_65 = 1, B_66 = Dfa_DStateCount;

    if (B_65 <= B_66)
      for (State = B_65;; State += 1) {
        TablePtr->A[State].EobTrans = Dfa_GetTable(State, Classes_ToClass.A[Dfa_EobCh]);
        if (State >= B_66) break;
      }
  }
  {
    SHORTINT B_67 = 1, B_68 = Dfa_MaxAmbiguousState;

    if (B_67 <= B_68)
      for (State = B_67;; State += 1) {
        Dfa_PutTable(State, Classes_ToClass.A[Dfa_EobCh], Dfa_EobState);
        if (State >= B_68) break;
      }
  }
  {
    SHORTINT B_69 = Dfa_MaxAmbiguousState + 1, B_70 = Dfa_DStateCount;

    if (B_69 <= B_70)
      for (State = B_69;; State += 1) {
        Dfa_PutTable(State, Classes_ToClass.A[Dfa_EobCh], Dfa_DNoState);
        if (State >= B_70) break;
      }
  }
}

static void DepthFirstTraversal
# ifdef __STDC__
(Dfa_DStateRange State)
# else
(State)
Dfa_DStateRange State;
# endif
{
  Dfa_DStateRange State2;

  Sets_Exclude(G_6_WorkingSet, (Sets_tElement)State);
  Sets_Include(G_7_Marked, (Sets_tElement)State);
  {
    SHORTINT B_71 = *G_10_From, B_72 = *G_9_To;

    if (B_71 <= B_72)
      for (State2 = B_71;; State2 += 1) {
        if (Sets_IsElement((Sets_tElement)State2, &(*G_5_DBPtr)->A[State].Defaults) && !Sets_IsElement((Sets_tElement)State2, G_7_Marked)) {
          DepthFirstTraversal(State2);
        }
        if (State2 >= B_72) break;
      }
  }
  INC(*G_8_DFN);
  (*G_5_DBPtr)->A[State].DFN = *G_8_DFN;
  (*G_5_DBPtr)->A[*G_8_DFN].DFNToState = State;
}

void Dfa_ComputeDefaults
# ifdef __STDC__
(Dfa_DStateRange From, Dfa_DStateRange To)
# else
(From, To)
Dfa_DStateRange From, To;
# endif
{
  DB *DBPtr;
  LONGINT DBSize;
  Dfa_DStateRange State, State1, State2, DefaultState;
  SHORTCARD DefaultCard;
  CHAR Ch;
  Sets_tSet Domain1, Domain2;
  Sets_tSet Marked, WorkingSet;
  Sets_tSet Cyclics, Current;
  Sets_tSet Next, Successors;
  SHORTCARD DFN;
  CARDINAL i;
  DB* *L_5;
  Sets_tSet *L_6;
  Sets_tSet *L_7;
  SHORTCARD *L_8;
  Dfa_DStateRange *L_9;
  Dfa_DStateRange *L_10;

  L_5 = G_5_DBPtr;
  G_5_DBPtr = &DBPtr;
  L_6 = G_6_WorkingSet;
  G_6_WorkingSet = &WorkingSet;
  L_7 = G_7_Marked;
  G_7_Marked = &Marked;
  L_8 = G_8_DFN;
  G_8_DFN = &DFN;
  L_9 = G_9_To;
  G_9_To = &To;
  L_10 = G_10_From;
  G_10_From = &From;
  DBSize = To + 1;
  DynArray_MakeArray((ADDRESS *)&DBPtr, &DBSize, (LONGINT)sizeof(DBElmt));
  Sets_MakeSet(&Domain1, ORD(Dfa_LastCh));
  Sets_MakeSet(&Domain2, ORD(Dfa_LastCh));
  Sets_MakeSet(&Marked, (Sets_tElement)To);
  Sets_MakeSet(&WorkingSet, (Sets_tElement)To);
  Sets_MakeSet(&Cyclics, (Sets_tElement)To);
  Sets_MakeSet(&Current, (Sets_tElement)To);
  Sets_MakeSet(&Next, (Sets_tElement)To);
  Sets_MakeSet(&Successors, (Sets_tElement)To);
  Dfa_DefaultSavings = 0;
  {
    SHORTINT B_73 = From, B_74 = To;

    if (B_73 <= B_74)
      for (State = B_73;; State += 1) {
        Sets_MakeSet(&DBPtr->A[State].Domain, ORD(Dfa_LastCh));
        {
          CHAR B_75 = Dfa_GetFirst(State), B_76 = Dfa_GetLast(State);

          if (B_75 <= B_76)
            for (Ch = B_75;; Ch += 1) {
              if (Dfa_GetTable(State, Ch) != Dfa_DNoState) {
                Sets_Include(&DBPtr->A[State].Domain, ORD(Ch));
              }
              if (Ch >= B_76) break;
            }
        }
        if (State >= B_74) break;
      }
  }
  {
    SHORTINT B_77 = From, B_78 = To;

    if (B_77 <= B_78)
      for (State1 = B_77;; State1 += 1) {
        Sets_MakeSet(&DBPtr->A[State1].Defaults, (Sets_tElement)To);
        Sets_MakeSet(&DBPtr->A[State1].Users, (Sets_tElement)To);
        DBPtr->A[State1].Savings = 0;
        if (!Sets_IsEmpty(DBPtr->A[State1].Domain)) {
          Sets_Assign(&Domain1, DBPtr->A[State1].Domain);
          {
            SHORTINT B_79 = From, B_80 = To;

            if (B_79 <= B_80)
              for (State2 = B_79;; State2 += 1) {
                if (State1 != State2) {
                  Sets_Assign(&Domain2, DBPtr->A[State2].Domain);
                  if (Sets_IsSubset(Domain2, Domain1)) {
                    if (Sets_Card(&DBPtr->A[State2].Domain) >= DBPtr->A[State1].Savings) {
                      {
                        CHAR B_81 = Dfa_GetFirst(State2), B_82 = Dfa_GetLast(State2);

                        if (B_81 <= B_82)
                          for (Ch = B_81;; Ch += 1) {
                            State = Dfa_GetTable(State2, Ch);
                            if (State != Dfa_DNoState && State != Dfa_GetTable(State1, Ch)) {
                              Sets_Exclude(&Domain2, ORD(Ch));
                            }
                            if (Ch >= B_82) break;
                          }
                      }
                      DefaultCard = Sets_Card(&Domain2);
                      if (DefaultCard > 0) {
                        if (DefaultCard == DBPtr->A[State1].Savings) {
                          Sets_Include(&DBPtr->A[State1].Defaults, (Sets_tElement)State2);
                        } else if (DefaultCard > DBPtr->A[State1].Savings) {
                          Sets_AssignElmt(&DBPtr->A[State1].Defaults, (Sets_tElement)State2);
                          DBPtr->A[State1].Savings = DefaultCard;
                        }
                      }
                    }
                  }
                }
                if (State2 >= B_80) break;
              }
          }
        }
        if (State1 >= B_78) break;
      }
  }
  {
    SHORTINT B_83 = From, B_84 = To;

    if (B_83 <= B_84)
      for (State1 = B_83;; State1 += 1) {
        {
          SHORTINT B_85 = From, B_86 = To;

          if (B_85 <= B_86)
            for (State2 = B_85;; State2 += 1) {
              if (Sets_IsElement((Sets_tElement)State2, &DBPtr->A[State1].Defaults)) {
                Sets_Include(&DBPtr->A[State2].Users, (Sets_tElement)State1);
              }
              if (State2 >= B_86) break;
            }
        }
        if (State1 >= B_84) break;
      }
  }
  DFN = From - 1;
  Sets_Complement(&WorkingSet);
  {
    SHORTINT B_87 = 0, B_88 = From - 1;

    if (B_87 <= B_88)
      for (State = B_87;; State += 1) {
        Sets_Exclude(&WorkingSet, (Sets_tElement)State);
        if (State >= B_88) break;
      }
  }
  if (From <= Dfa_EobDefaultState && Dfa_EobDefaultState <= To) {
    DepthFirstTraversal(Dfa_EobDefaultState);
  }
  while (!Sets_IsEmpty(WorkingSet)) {
    DepthFirstTraversal((SHORTINT)Sets_Select(&WorkingSet));
  }
  {
    SHORTINT B_89 = From, B_90 = To;

    if (B_89 <= B_90)
      for (State1 = B_89;; State1 += 1) {
        State2 = State1 + 1;
        for (;;) {
          if (State2 > To) {
            goto EXIT_2;
          }
          if (Sets_IsElement((Sets_tElement)State2, &DBPtr->A[State1].Defaults) && Sets_IsElement((Sets_tElement)State1, &DBPtr->A[State2].Defaults)) {
            Sets_Include(&Cyclics, (Sets_tElement)State1);
            Sets_Include(&Cyclics, (Sets_tElement)State2);
            goto EXIT_2;
          }
          INC(State2);
        } EXIT_2:;
        if (State1 >= B_90) break;
      }
  }
  Sets_AssignEmpty(&Marked);
  Sets_AssignEmpty(&WorkingSet);
  Sets_Complement(&WorkingSet);
  {
    SHORTINT B_91 = 0, B_92 = From - 1;

    if (B_91 <= B_92)
      for (State = B_91;; State += 1) {
        Sets_Exclude(&WorkingSet, (Sets_tElement)State);
        if (State >= B_92) break;
      }
  }
  while (!Sets_IsEmpty(WorkingSet)) {
    State = DBPtr->A[Sets_Select(&WorkingSet)].DFNToState;
    Sets_Assign(&Current, DBPtr->A[State].Defaults);
    Sets_Intersection(&Current, Cyclics);
    Sets_Include(&Current, (Sets_tElement)State);
    Sets_Assign(&Next, Current);
    {
      LONGCARD B_93 = Sets_Minimum(&Next), B_94 = Sets_Maximum(&Next);

      if (B_93 <= B_94)
        for (i = B_93;; i += 1) {
          if (!Sets_IsElement(i, &Dfa_CyclicStates)) {
            Sets_Exclude(&Next, i);
          }
          if (i >= B_94) break;
        }
    }
    if (From <= Dfa_EobDefaultState && Dfa_EobDefaultState <= To && Sets_IsElement((Sets_tElement)Dfa_EobDefaultState, &Current)) {
      State = Dfa_EobDefaultState;
    } else if (!Sets_IsEmpty(Next)) {
      State = Sets_Select(&Next);
    } else {
      State = Sets_Select(&Current);
    }
    Sets_AssignElmt(&Current, (Sets_tElement)State);
    Sets_Include(&Marked, (Sets_tElement)State);
    while (!Sets_IsEmpty(Current)) {
      Sets_AssignEmpty(&Next);
      while (!Sets_IsEmpty(Current)) {
        State1 = Sets_Extract(&Current);
        Sets_Exclude(&WorkingSet, (Sets_tElement)DBPtr->A[State1].DFN);
        Sets_Assign(&Successors, DBPtr->A[State1].Users);
        while (!Sets_IsEmpty(Successors)) {
          State2 = Sets_Extract(&Successors);
          if (!Sets_IsElement((Sets_tElement)State2, &Marked)) {
            Dfa_PutDefault(State2, State1);
            Sets_Include(&Next, (Sets_tElement)State2);
            Sets_Include(&Marked, (Sets_tElement)State2);
          }
        }
      }
      Sets_Assign(&Current, Next);
    }
  }
  {
    SHORTINT B_95 = From, B_96 = To;

    if (B_95 <= B_96)
      for (State1 = B_95;; State1 += 1) {
        if (Dfa_GetDefault(State1) == Dfa_DNoState) {
          DBPtr->A[State1].Savings = 0;
          if (!Sets_IsEmpty(DBPtr->A[State1].Domain)) {
            Sets_Assign(&Domain1, DBPtr->A[State1].Domain);
            {
              SHORTINT B_97 = From, B_98 = To;

              if (B_97 <= B_98)
                for (State2 = B_97;; State2 += 1) {
                  if (State1 != State2) {
                    Sets_Assign(&Domain2, DBPtr->A[State2].Domain);
                    if (Sets_IsStrictSubset(Domain2, Domain1)) {
                      if (Sets_Card(&DBPtr->A[State2].Domain) >= DBPtr->A[State1].Savings) {
                        {
                          CHAR B_99 = Dfa_GetFirst(State2), B_100 = Dfa_GetLast(State2);

                          if (B_99 <= B_100)
                            for (Ch = B_99;; Ch += 1) {
                              State = Dfa_GetTable(State2, Ch);
                              if (State != Dfa_DNoState && State != Dfa_GetTable(State1, Ch)) {
                                Sets_Exclude(&Domain2, ORD(Ch));
                              }
                              if (Ch >= B_100) break;
                            }
                        }
                        DefaultCard = Sets_Card(&Domain2);
                        if (DefaultCard > 0) {
                          if (DefaultCard == DBPtr->A[State1].Savings) {
                            Sets_Include(&Current, (Sets_tElement)State2);
                          } else if (DefaultCard > DBPtr->A[State1].Savings) {
                            Sets_AssignElmt(&Current, (Sets_tElement)State2);
                            DBPtr->A[State1].Savings = DefaultCard;
                          }
                        }
                      }
                    }
                  }
                  if (State2 >= B_98) break;
                }
            }
            if (DBPtr->A[State1].Savings > 0) {
              Sets_Assign(&Next, Current);
              {
                LONGCARD B_101 = Sets_Minimum(&Next), B_102 = Sets_Maximum(&Next);

                if (B_101 <= B_102)
                  for (i = B_101;; i += 1) {
                    if (!Sets_IsElement(i, &Dfa_CyclicStates)) {
                      Sets_Exclude(&Next, i);
                    }
                    if (i >= B_102) break;
                  }
              }
              if (From <= Dfa_EobDefaultState && Dfa_EobDefaultState <= To && Sets_IsElement((Sets_tElement)Dfa_EobDefaultState, &Current)) {
                State = Dfa_EobDefaultState;
              } else if (!Sets_IsEmpty(Next)) {
                State = Sets_Select(&Next);
              } else {
                State = Sets_Select(&Current);
              }
              Dfa_PutDefault(State1, State);
            }
          }
        }
        if (State1 >= B_96) break;
      }
  }
  {
    SHORTINT B_103 = From, B_104 = To;

    if (B_103 <= B_104)
      for (State1 = B_103;; State1 += 1) {
        DefaultState = Dfa_GetDefault(State1);
        if (DefaultState != Dfa_DNoState) {
          {
            CHAR B_105 = Dfa_GetFirst(State1), B_106 = Dfa_GetLast(State1);

            if (B_105 <= B_106)
              for (Ch = B_105;; Ch += 1) {
                State = Dfa_GetTable(DefaultState, Ch);
                if (State != Dfa_DNoState && State == Dfa_GetTable(State1, Ch)) {
                  Dfa_PutTable(State1, Ch, Dfa_DNoState);
                }
                if (Ch >= B_106) break;
              }
          }
          INC1(Dfa_DefaultSavings, DBPtr->A[State1].Savings);
        }
        if (State1 >= B_104) break;
      }
  }
  {
    SHORTINT B_107 = From, B_108 = To;

    if (B_107 <= B_108)
      for (State = B_107;; State += 1) {
        Sets_ReleaseSet(&DBPtr->A[State].Domain);
        Sets_ReleaseSet(&DBPtr->A[State].Defaults);
        Sets_ReleaseSet(&DBPtr->A[State].Users);
        if (State >= B_108) break;
      }
  }
  Sets_ReleaseSet(&Domain1);
  Sets_ReleaseSet(&Domain2);
  Sets_ReleaseSet(&Marked);
  Sets_ReleaseSet(&WorkingSet);
  Sets_ReleaseSet(&Cyclics);
  Sets_ReleaseSet(&Current);
  Sets_ReleaseSet(&Next);
  Sets_ReleaseSet(&Successors);
  DynArray_ReleaseArray((ADDRESS *)&DBPtr, &DBSize, (LONGINT)sizeof(DBElmt));
  G_5_DBPtr = L_5;
  G_6_WorkingSet = L_6;
  G_7_Marked = L_7;
  G_8_DFN = L_8;
  G_9_To = L_9;
  G_10_From = L_10;
}

void Dfa__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Sets__init();
    General__init();
    DynArray__init();
    Sets__init();
    IO__init();
    Layout__init();
    GenTabs__init();
    Classes__init();

    Dfa_LastCh = ((CHAR)'\177');
    Dfa_DStateCount = 0;
    TableSize = InitialTableSize;
    DynArray_MakeArray((ADDRESS *)&TablePtr, &TableSize, (LONGINT)sizeof(DStateInfo));
  }
}
