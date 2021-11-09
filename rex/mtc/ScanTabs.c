#include "SYSTEM_.h"

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

#ifndef DEFINITION_Classes
#include "Classes.h"
#endif

#ifndef DEFINITION_ScanGen
#include "ScanGen.h"
#endif

#ifndef DEFINITION_ScanTabs
#include "ScanTabs.h"
#endif

ScanTabs_RuleBase *ScanTabs_RuleBasePtr;
LONGINT ScanTabs_RuleBaseSize;
ScanTabs_Rule *ScanTabs_RulePtr;
LONGINT ScanTabs_RuleSize;
ScanTabs_Base *ScanTabs_BasePtr;
LONGINT ScanTabs_BaseSize;
ScanTabs_Default *ScanTabs_DefaultPtr;
LONGINT ScanTabs_DefaultSize;
ScanTabs_Control *ScanTabs_ControlPtr;
LONGINT ScanTabs_ControlSize;
ScanTabs_EobTrans *ScanTabs_EobTransPtr;
LONGINT ScanTabs_EobTransSize;
ScanTabs_Context *ScanTabs_ContextPtr;
LONGINT ScanTabs_ContextSize;
ScanTabs_Action *ScanTabs_ActionPtr;
LONGINT ScanTabs_ActionSize;
ScanTabs_ActionType ScanTabs_ActionNr;
ScanTabs_TableRange ScanTabs_TableSize;
ScanTabs_TableRange ScanTabs_TableEntries;

static System_tFile Tables;
static ScanTabs_TableElmt ElmtSize;
struct S_2 {
    CHAR A[127 + 1];
};
static void PutTable ARGS((ScanTabs_TableElmt Length, ADDRESS Address));
typedef struct S_1 *DiffsInfoPtr;
typedef struct S_1 {
    struct S_3 {
        CHAR A[256 - 1 + 1];
    } *DiffsPtr;
    DiffsInfoPtr Next;
    ScanTabs_TableRange Base;
    SHORTCARD Count;
} DiffsInfo;
struct S_4 {
    struct S_5 {
        CHAR First, Last;
    } A[128 + 1];
};
struct S_6 {
    CHAR A[256 + 1];
};
struct S_7 {
    DiffsInfoPtr A[100000 + 1];
};
static void WriteState ARGS((Dfa_DStateRange State));


void ScanTabs_PutTables
# ifdef __STDC__
(BOOLEAN ReduceCaseSize)
# else
(ReduceCaseSize)
BOOLEAN ReduceCaseSize;
# endif
{
  CARDINAL BlockSize, i;
  ScanTabs_StateRange StateCount;
  Strings_tString FileNameS, PathS;
  struct S_2 PathA;

  BlockSize = 64000 / sizeof(ScanTabs_ControlType);
  StateCount = Dfa_DStateCount;
  if (ScanGen_ScannerName == Idents_NoIdent) {
    Strings_ArrayToString((STRING)"Scanner", 7L, &PathS);
  } else {
    Idents_GetString(ScanGen_ScannerName, &PathS);
  }
  Strings_ArrayToString((STRING)".Tab", 4L, &FileNameS);
  Strings_Concatenate(&PathS, &FileNameS);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 128L);
  Tables = OpenOutput(PathA.A, 128L);
  Checks_ErrorCheck((STRING)"PutTables.OpenOutput", 20L, Tables);
  PutTable((StateCount + 1) * ElmtSize, (ADDRESS)ScanTabs_BasePtr);
  PutTable((StateCount + 1) * ElmtSize, (ADDRESS)ScanTabs_DefaultPtr);
  PutTable((StateCount + 1) * ElmtSize, (ADDRESS)ScanTabs_EobTransPtr);
  if (ReduceCaseSize) {
    PutTable((StateCount + 1) * ElmtSize, (ADDRESS)ScanTabs_ActionPtr);
  }
  i = 0;
  while (i <= ScanTabs_TableSize) {
    PutTable((SHORTCARD)(General_Min((LONGINT)BlockSize, (LONGINT)(ScanTabs_TableSize + 1 - i)) * sizeof(ScanTabs_ControlType)), ADR(ScanTabs_ControlPtr->A[i]));
    INC1(i, BlockSize);
  }
}

static void PutTable
# ifdef __STDC__
(ScanTabs_TableElmt Length, ADDRESS Address)
# else
(Length, Address)
ScanTabs_TableElmt Length;
ADDRESS Address;
# endif
{
  INTEGER N;

  N = Write(Tables, ADR(Length), (LONGINT)ElmtSize);
  Checks_ErrorCheck((STRING)"PutTable.Write1", 15L, N);
  N = Write(Tables, Address, (LONGINT)Length);
  Checks_ErrorCheck((STRING)"PutTable.Write2", 15L, N);
}

void ScanTabs_PutComb
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  ScanTabs_TableRange i;

  {
    LONGCARD B_1 = 1, B_2 = ScanTabs_TableSize;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        IO_WriteC(File, '{');
        IO_WriteI(File, (LONGINT)ScanTabs_ControlPtr->A[i].Check, 0L);
        IO_WriteS(File, (STRING)", ", 2L);
        IO_WriteI(File, (LONGINT)ScanTabs_ControlPtr->A[i].Next, 0L);
        IO_WriteS(File, (STRING)"},", 2L);
        IO_WriteNl(File);
        if (i >= B_2) break;
      }
  }
}

void ScanTabs_PutBase
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  INTEGER i;

  {
    LONGINT B_3 = 1, B_4 = Dfa_DStateCount;

    if (B_3 <= B_4)
      for (i = B_3;; i += 1) {
        IO_WriteS(File, (STRING)"& yyComb [", 10L);
        IO_WriteI(File, (LONGINT)ScanTabs_BasePtr->A[i], 0L);
        IO_WriteS(File, (STRING)"],", 2L);
        IO_WriteNl(File);
        if (i >= B_4) break;
      }
  }
}

void ScanTabs_PutDefault
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  INTEGER i;

  {
    LONGINT B_5 = 1, B_6 = Dfa_DStateCount;

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        IO_WriteI(File, (LONGINT)ScanTabs_DefaultPtr->A[i], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_6) break;
      }
  }
}

void ScanTabs_PutEobTrans
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  INTEGER i;

  {
    LONGINT B_7 = 1, B_8 = Dfa_DStateCount;

    if (B_7 <= B_8)
      for (i = B_7;; i += 1) {
        IO_WriteI(File, (LONGINT)ScanTabs_EobTransPtr->A[i], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_8) break;
      }
  }
}

void ScanTabs_PutAction
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  INTEGER i;

  {
    LONGINT B_9 = 1, B_10 = Dfa_DStateCount;

    if (B_9 <= B_10)
      for (i = B_9;; i += 1) {
        IO_WriteI(File, (LONGINT)ScanTabs_ActionPtr->A[i], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_10) break;
      }
  }
}

void ScanTabs_MakeTables
# ifdef __STDC__
(BOOLEAN ReduceCaseSize)
# else
(ReduceCaseSize)
BOOLEAN ReduceCaseSize;
# endif
{
  Dfa_DStateRange State;
  CARDINAL cState;
  SHORTCARD Pattern;

  ScanTabs_DefaultSize = Dfa_DStateCount + 1;
  DynArray_MakeArray((ADDRESS *)&ScanTabs_DefaultPtr, &ScanTabs_DefaultSize, (LONGINT)sizeof(ScanTabs_StateRange));
  DynArray_MakeArray((ADDRESS *)&ScanTabs_EobTransPtr, &ScanTabs_DefaultSize, (LONGINT)sizeof(ScanTabs_StateRange));
  ScanTabs_DefaultPtr->A[Dfa_DNoState] = Dfa_DNoState;
  ScanTabs_EobTransPtr->A[Dfa_DNoState] = Dfa_DNoState;
  {
    SHORTINT B_11 = 1, B_12 = Dfa_DStateCount;

    if (B_11 <= B_12)
      for (State = B_11;; State += 1) {
        ScanTabs_DefaultPtr->A[State] = Dfa_GetDefault(State);
        ScanTabs_EobTransPtr->A[State] = Dfa_GetEobTrans(State);
        if (State >= B_12) break;
      }
  }
  if (ReduceCaseSize) {
    DynArray_MakeArray((ADDRESS *)&ScanTabs_ActionPtr, &ScanTabs_DefaultSize, (LONGINT)sizeof(ScanTabs_TableElmt));
    ScanTabs_ActionPtr->A[Dfa_DNoState] = Dfa_DNoState;
    {
      SHORTINT B_13 = 1, B_14 = Dfa_DStateCount;

      if (B_13 <= B_14)
        for (State = B_13;; State += 1) {
          ScanTabs_ActionPtr->A[State] = GenTabs_PatternCount + 1;
          if (State >= B_14) break;
        }
    }
    {
      SHORTCARD B_15 = 1, B_16 = GenTabs_PatternCount;

      if (B_15 <= B_16)
        for (Pattern = B_15;; Pattern += 1) {
          {
            LONGCARD B_17 = Sets_Minimum(&GenTabs_PatternTablePtr->A[Pattern].Finals), B_18 = Sets_Maximum(&GenTabs_PatternTablePtr->A[Pattern].Finals);

            if (B_17 <= B_18)
              for (cState = B_17;; cState += 1) {
                if (Sets_IsElement(cState, &GenTabs_PatternTablePtr->A[Pattern].Finals)) {
                  ScanTabs_ActionPtr->A[cState] = Pattern;
                }
                if (cState >= B_18) break;
              }
          }
          if (Pattern >= B_16) break;
        }
    }
  }
}

void ScanTabs_CompressTables
# ifdef __STDC__
(SHORTINT Optimize)
# else
(Optimize)
SHORTINT Optimize;
# endif
{
  ScanTabs_TableRange base;
  LONGINT lbase;
  Dfa_DStateRange State;
  BOOLEAN Success;
  CHAR Ch, LastElmt;
  LONGINT OldControlSize;
  INTEGER i;
  CARDINAL j;
  SHORTINT Hash;
  struct S_4 Group;
  CARDINAL GroupCount;
  struct S_6 Diffs;
  CHAR StartCh, StopCh;
  struct S_7 *HashTablePtr;
  LONGINT HashTableSize;
  DiffsInfoPtr Current;
  Sets_tSet Domain;

  ScanTabs_BaseSize = Dfa_DStateCount + 1;
  DynArray_MakeArray((ADDRESS *)&ScanTabs_BasePtr, &ScanTabs_BaseSize, (LONGINT)sizeof(ScanTabs_TableRange));
  {
    SHORTINT B_19 = 0, B_20 = Dfa_DStateCount;

    if (B_19 <= B_20)
      for (State = B_19;; State += 1) {
        ScanTabs_BasePtr->A[State] = 0;
        if (State >= B_20) break;
      }
  }
  if (Optimize == 0) {
    ScanTabs_ControlSize = GenTabs_LeafCount * 60;
  } else if (Optimize >= 10000) {
    ScanTabs_ControlSize = Dfa_DStateCount * 5;
  } else {
    ScanTabs_ControlSize = GenTabs_LeafCount * 12;
  }
  ScanTabs_ControlSize = General_Max(ScanTabs_ControlSize, (LONGINT)ORD(Dfa_OldLastCh) + 1);
  DynArray_MakeArray((ADDRESS *)&ScanTabs_ControlPtr, &ScanTabs_ControlSize, (LONGINT)sizeof(ScanTabs_ControlType));
  {
    LONGINT B_21 = 0, B_22 = ScanTabs_ControlSize - 1;

    if (B_21 <= B_22)
      for (i = B_21;; i += 1) {
        ScanTabs_ControlPtr->A[i].Check = Dfa_DNoState;
        ScanTabs_ControlPtr->A[i].Next = Dfa_DNoState;
        if (i >= B_22) break;
      }
  }
  HashTableSize = Dfa_DStateCount;
  DynArray_MakeArray((ADDRESS *)&HashTablePtr, &HashTableSize, (LONGINT)sizeof(DiffsInfoPtr));
  {
    LONGINT B_23 = 0, B_24 = HashTableSize - 1;

    if (B_23 <= B_24)
      for (i = B_23;; i += 1) {
        HashTablePtr->A[i] = NIL;
        if (i >= B_24) break;
      }
  }
  Sets_MakeSet(&Domain, ORD(Dfa_OldLastCh));
  ScanTabs_TableSize = 0;
  ScanTabs_TableEntries = 0;
  Group.A[0].Last = '\0';
  {
    SHORTINT B_25 = 1, B_26 = Dfa_DStateCount;

    if (B_25 <= B_26)
      for (State = B_25;; State += 1) {
        Sets_AssignEmpty(&Domain);
        Ch = Dfa_GetFirst(State);
        LastElmt = Dfa_GetLast(State);
        if (Ch <= LastElmt) {
          for (;;) {
            if (Dfa_GetTableNoDef(State, Ch) != Dfa_DNoState) {
              if (Ch <= Classes_ClassCount) {
                Sets_Union(&Domain, Classes_ClassMemPtr->A[Ch]);
              } else {
                Sets_Include(&Domain, ORD(Classes_ToChar.A[Ch]));
              }
            }
            if (Ch == LastElmt) {
              goto EXIT_1;
            }
            INC(Ch);
          } EXIT_1:;
        }
        GroupCount = 0;
        if (!Sets_IsEmpty(Domain)) {
          Ch = CHR(Sets_Minimum(&Domain));
          LastElmt = CHR(Sets_Maximum(&Domain));
          if (Ch <= LastElmt) {
            for (;;) {
              for (;;) {
                if (Ch == LastElmt) {
                  goto EXIT_3;
                }
                if (!Sets_IsElement(ORD(Ch), &Domain)) {
                  INC(Ch);
                } else {
                  goto EXIT_3;
                }
              } EXIT_3:;
              if (Sets_IsElement(ORD(Ch), &Domain)) {
                INC(GroupCount);
                Group.A[GroupCount].First = Ch;
                for (;;) {
                  if (Ch == LastElmt) {
                    goto EXIT_4;
                  }
                  if (Sets_IsElement(ORD(Ch), &Domain)) {
                    INC(Ch);
                  } else {
                    goto EXIT_4;
                  }
                } EXIT_4:;
                if (Sets_IsElement(ORD(Ch), &Domain)) {
                  Group.A[GroupCount].Last = Ch;
                } else {
                  Group.A[GroupCount].Last = CHR(ORD(Ch) - 1);
                }
              }
              if (Ch == LastElmt) {
                goto EXIT_2;
              }
            } EXIT_2:;
          }
        }
        base = 0;
        if (GroupCount > 0) {
          Hash = 0;
          {
            LONGCARD B_27 = 1, B_28 = GroupCount;

            if (B_27 <= B_28)
              for (j = B_27;; j += 1) {
                Diffs.A[j + j - 1] = CHR(ORD(Group.A[j].First) - ORD(Group.A[j - 1].Last));
                Diffs.A[j + j] = CHR(ORD(Group.A[j].Last) - ORD(Group.A[j].First));
                INC1(Hash, (ORD(Diffs.A[j + j - 1]) + ORD(Diffs.A[j + j])) * j);
                if (j >= B_28) break;
              }
          }
          Hash = Hash % Dfa_DStateCount;
          Success = FALSE;
          Current = HashTablePtr->A[Hash];
          for (;;) {
            if (Current == NIL) {
              goto EXIT_5;
            }
            if (Current->Count == GroupCount * 2) {
              Success = TRUE;
              j = 0;
              for (;;) {
                INC(j);
                if (Current->DiffsPtr->A[j - 1] != Diffs.A[j]) {
                  Success = FALSE;
                  goto EXIT_6;
                }
                if (j == Current->Count) {
                  goto EXIT_6;
                }
              } EXIT_6:;
              if (Success) {
                goto EXIT_5;
              }
            }
            Current = Current->Next;
          } EXIT_5:;
          if (Success) {
            base = Current->Base + ORD(Current->DiffsPtr->A[2 - 1]) + 1;
          } else {
            Current = (DiffsInfoPtr)Memory_Alloc((LONGINT)sizeof(DiffsInfo));
            {
              register DiffsInfo *W_1 = Current;

              W_1->Base = 0;
              W_1->Next = HashTablePtr->A[Hash];
              W_1->Count = GroupCount * 2;
              W_1->DiffsPtr = (struct S_3 *)Memory_Alloc((LONGINT)W_1->Count);
              {
                LONGCARD B_29 = 1, B_30 = W_1->Count;

                if (B_29 <= B_30)
                  for (j = B_29;; j += 1) {
                    W_1->DiffsPtr->A[j - 1] = Diffs.A[j];
                    if (j >= B_30) break;
                  }
              }
            }
            HashTablePtr->A[Hash] = Current;
          }
          for (;;) {
            lbase = base;
            if (lbase >= ScanTabs_ControlSize - (LONGINT)ORD(Dfa_OldLastCh)) {
              OldControlSize = ScanTabs_ControlSize;
              DynArray_ExtendArray((ADDRESS *)&ScanTabs_ControlPtr, &ScanTabs_ControlSize, (LONGINT)sizeof(ScanTabs_ControlType));
              {
                LONGINT B_31 = OldControlSize, B_32 = ScanTabs_ControlSize - 1;

                if (B_31 <= B_32)
                  for (i = B_31;; i += 1) {
                    ScanTabs_ControlPtr->A[i].Check = Dfa_DNoState;
                    ScanTabs_ControlPtr->A[i].Next = Dfa_DNoState;
                    if (i >= B_32) break;
                  }
              }
            }
            Success = TRUE;
            j = 0;
            for (;;) {
              INC(j);
              StartCh = Group.A[j].First;
              StopCh = Group.A[j].Last;
              Ch = StartCh;
              for (;;) {
                if (ScanTabs_ControlPtr->A[base + ORD(Ch)].Check != Dfa_DNoState) {
                  Success = FALSE;
                  goto EXIT_9;
                }
                if (Ch == StopCh) {
                  goto EXIT_9;
                }
                INC(Ch);
              } EXIT_9:;
              if (!Success || j == GroupCount) {
                goto EXIT_8;
              }
            } EXIT_8:;
            if (Success) {
              goto EXIT_7;
            }
            INC(base);
          } EXIT_7:;
          j = 0;
          for (;;) {
            INC(j);
            Ch = Group.A[j].First;
            StopCh = Group.A[j].Last;
            for (;;) {
              {
                register ScanTabs_ControlType *W_2 = &ScanTabs_ControlPtr->A[base + ORD(Ch)];

                W_2->Check = State;
                W_2->Next = Dfa_GetTableNoDef(State, Classes_ToClass.A[Ch]);
              }
              INC(ScanTabs_TableEntries);
              if (Ch == StopCh) {
                goto EXIT_11;
              }
              INC(Ch);
            } EXIT_11:;
            if (j == GroupCount) {
              goto EXIT_10;
            }
          } EXIT_10:;
          Current->Base = base;
        }
        ScanTabs_BasePtr->A[State] = base;
        ScanTabs_TableSize = General_Max((LONGINT)ScanTabs_TableSize, (LONGINT)base);
        if (State >= B_26) break;
      }
  }
  INC1(ScanTabs_TableSize, ORD(Dfa_OldLastCh));
  DynArray_ReleaseArray((ADDRESS *)&HashTablePtr, &HashTableSize, (LONGINT)sizeof(DiffsInfoPtr));
}

void ScanTabs_WriteTables
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange State;

  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Tables :", 8L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteNl((System_tFile)IO_StdOutput);
  {
    SHORTINT B_33 = 1, B_34 = Dfa_DStateCount;

    if (B_33 <= B_34)
      for (State = B_33;; State += 1) {
        WriteState(State);
        IO_WriteNl((System_tFile)IO_StdOutput);
        if (State >= B_34) break;
      }
  }
}

void ScanTabs_QueryTables
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange State;

  for (;;) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"State ? ", 8L);
    if (IO_EndOfLine((System_tFile)IO_StdInput)) {
      IO_ReadNl((System_tFile)IO_StdInput);
    }
    State = IO_ReadI((System_tFile)IO_StdInput);
    if (State == 0) {
      goto EXIT_12;
    }
    WriteState(State);
  } EXIT_12:;
}

static void WriteState
# ifdef __STDC__
(Dfa_DStateRange State)
# else
(State)
Dfa_DStateRange State;
# endif
{
  ScanTabs_TableElmt NextState;
  CHAR Ch;
  ScanTabs_ControlType ControlRecord;
  INTEGER Count;

  Count = 0;
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"State, Default =", 16L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)State, 5L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)ScanTabs_DefaultPtr->A[State], 5L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  {
    CHAR B_35 = Dfa_FirstCh, B_36 = Dfa_OldLastCh;

    if (B_35 <= B_36)
      for (Ch = B_35;; Ch += 1) {
        NextState = State;
        for (;;) {
          ControlRecord = ScanTabs_ControlPtr->A[ScanTabs_BasePtr->A[NextState] + ORD(Ch)];
          if (ControlRecord.Check == NextState) {
            NextState = ControlRecord.Next;
            goto EXIT_13;
          }
          NextState = ScanTabs_DefaultPtr->A[NextState];
          NextState = Dfa_DNoState;
          if (NextState == Dfa_DNoState) {
            goto EXIT_13;
          }
        } EXIT_13:;
        if (NextState != Dfa_DNoState) {
          if (Count == 10) {
            IO_WriteNl((System_tFile)IO_StdOutput);
            Count = 0;
          }
          INC(Count);
          Layout_WriteChar((System_tFile)IO_StdOutput, Ch);
          Layout_WriteSpace((System_tFile)IO_StdOutput);
          IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)NextState, 1L);
          IO_WriteC((System_tFile)IO_StdOutput, ',');
          Layout_WriteSpace((System_tFile)IO_StdOutput);
        }
        if (Ch >= B_36) break;
      }
  }
  IO_WriteNl((System_tFile)IO_StdOutput);
}

void ScanTabs__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Checks__init();
    General__init();
    Memory__init();
    DynArray__init();
    Strings__init();
    Idents__init();
    Sets__init();
    System__init();
    IO__init();
    Layout__init();
    Dfa__init();
    GenTabs__init();
    Classes__init();
    ScanGen__init();

    ElmtSize = sizeof(ScanTabs_TableElmt);
  }
}
