#include "SYSTEM_.h"

#ifndef DEFINITION_Limits
#include "Limits.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Check
#include "Check.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Lookahead
#include "Lookahead.h"
#endif

BOOLEAN Lookahead_NoConflict;

#define eConflict   64
#define eNotLRk   62
static Sets_tSet Nullables;
static BOOLEAN reportedError;
static void ComputeNullables ARGS(());
static void IsYetNullable ARGS((CARDINAL nt));
static void MarkRep ARGS(());
struct S_2 {
    Automaton_tItemIndex A[TokenTab_cMAXNonTerm + 2 + 1];
};
static void ComputeDR ARGS(());
static void ComputeReads ARGS(());
static void CheckReadSets ARGS(());
static void Digraph ARGS((Lookahead_ConflictProc TreatConflict));
static void Traverse ARGS((Automaton_tItemIndex x, Lookahead_ConflictProc TreatConflict));
static void ComputeIncludesAndLookback ARGS(());
static void WindThrough ARGS((Automaton_tStateIndex MyState, Automaton_tProdIndex MyProd, Automaton_tIndex MyPos, Automaton_tItemIndex Trans, BOOLEAN *nullable));
static void ComputeLA ARGS(());
static void TreatReadConflict ARGS((BOOLEAN empty));
static void TreatFollowConflict ARGS((BOOLEAN empty));
static void ClearRelation ARGS(());
static void PutInRelation ARGS((Automaton_tItemIndex Rel, Automaton_tItemIndex NT));
#define InitItemStackCount   10
static Automaton_tItemIndexList Stack;
static void ClearItemStack ARGS(());
static void PushItem ARGS((Automaton_tItemIndex Item));
static Automaton_tItemIndex PopItem ARGS(());
static Automaton_tItemIndex TopItem ARGS(());
static CARDINAL ItemDepth ARGS(());
static void ClearNumbers ARGS(());
static void ERROR ARGS((CHAR a[], LONGCARD ));

static Sets_tSet *G_1_todo;
static BOOLEAN *G_2_success;

void Lookahead_ComputeLALR
# ifdef __STDC__
()
# else
()
# endif
{
  ComputeNullables();
  MarkRep();
  ComputeDR();
  ComputeReads();
  Digraph((Lookahead_ConflictProc)TreatReadConflict);
  CheckReadSets();
  ComputeIncludesAndLookback();
  Digraph((Lookahead_ConflictProc)TreatFollowConflict);
  ComputeLA();
  Check_CheckForConflicts(&Lookahead_NoConflict);
}

static void IsYetNullable
# ifdef __STDC__
(CARDINAL nt)
# else
(nt)
CARDINAL nt;
# endif
{
  Automaton_tIndex u, i;
  Automaton_tProdIndex pn;
  Automaton_tProduction prod;
  TokenTab_Vocabulary ri;
  TokenTab_Terminal t;
  BOOLEAN localsuccess;

  {
    register Automaton_tProdIndexList *W_1 = &Automaton_ProdList.A[nt - 1001];

    u = W_1->Used;
    localsuccess = FALSE;
    pn = 1;
    while (pn <= u && !localsuccess) {
      prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_1->Array->A[pn - 1].Index]);
      {
        register struct Automaton_9 *W_2 = prod;

        localsuccess = TRUE;
        i = 1;
        while (i <= W_2->Len && localsuccess) {
          ri = W_2->Right.A[i - 1];
          localsuccess = Sets_IsElement((Sets_tElement)ri, &Nullables);
          INC(i);
        }
      }
      INC(pn);
    }
  }
  if (localsuccess) {
    Sets_Include(&Nullables, nt);
    Sets_Exclude(G_1_todo, nt);
    *G_2_success = TRUE;
  }
}

static void ComputeNullables
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet todo;
  BOOLEAN success;
  TokenTab_Terminal t;
  TokenTab_NonTerminal nt;
  Sets_tSet *L_1;
  BOOLEAN *L_2;

  L_1 = G_1_todo;
  G_1_todo = &todo;
  L_2 = G_2_success;
  G_2_success = &success;
  Sets_MakeSet(&todo, (Sets_tElement)TokenTab_MAXNonTerm);
  Sets_MakeSet(&Nullables, (Sets_tElement)TokenTab_MAXNonTerm);
  {
    TokenTab_NonTerminal B_1 = TokenTab_MINNonTerm, B_2 = TokenTab_MAXNonTerm;

    if (B_1 <= B_2)
      for (nt = B_1;; nt += 1) {
        if (TokenTab_GetTokenType(nt) == TokenTab_NonTerm) {
          Sets_Include(&todo, (Sets_tElement)nt);
        }
        if (nt >= B_2) break;
      }
  }
  do {
    success = FALSE;
    {
      TokenTab_NonTerminal B_3 = TokenTab_MINNonTerm, B_4 = TokenTab_MAXNonTerm;

      if (B_3 <= B_4)
        for (nt = B_3;; nt += 1) {
          if (Sets_IsElement((Sets_tElement)nt, &todo)) {
            IsYetNullable((LONGCARD)nt);
          }
          if (nt >= B_4) break;
        }
    }
  } while (!!success);
  Sets_ReleaseSet(&todo);
  G_1_todo = L_1;
  G_2_success = L_2;
}

static void MarkRep
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex si, s;
  Automaton_tProduction p;
  Sets_tSet reps;
  Automaton_tItemIndex i;
  struct S_2 RepArray;
  TokenTab_Vocabulary voc;

  Sets_MakeSet(&reps, (Sets_tElement)TokenTab_MAXNonTerm);
  si = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_5 = 1, B_6 = si;

    if (B_5 <= B_6)
      for (s = B_5;; s += 1) {
        Sets_AssignEmpty(&reps);
        {
          register Automaton_tState *W_3 = &Automaton_StateArrayPtr->A[s - 1];

          {
            LONGCARD B_7 = W_3->Items, B_8 = W_3->Items + W_3->Size - 1;

            if (B_7 <= B_8)
              for (i = B_7;; i += 1) {
                {
                  register Automaton_tItem *W_4 = &Automaton_ItemArrayPtr->A[i - 1];

                  p = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_4->Prod]);
                  if (W_4->Pos >= p->Len) {
                    W_4->RepNo = i;
                    W_4->Rep = Automaton_RedRep;
                  } else {
                    voc = W_4->Read;
                    if (Sets_IsElement((Sets_tElement)voc, &reps)) {
                      W_4->Rep = Automaton_NoRep;
                      W_4->RepNo = RepArray.A[voc];
                    } else if (voc >= TokenTab_MINTerm && voc <= TokenTab_MAXTerm) {
                      RepArray.A[voc] = i;
                      W_4->RepNo = i;
                      W_4->Rep = Automaton_TermRep;
                      Sets_Include(&reps, (Sets_tElement)voc);
                    } else {
                      RepArray.A[voc] = i;
                      W_4->RepNo = i;
                      W_4->Rep = Automaton_NonTermRep;
                      Sets_Include(&reps, (Sets_tElement)voc);
                    }
                  }
                  if (W_4->Rep == Automaton_RedRep || W_4->Rep == Automaton_NonTermRep) {
                    Sets_MakeSet(&W_4->Set, (Sets_tElement)TokenTab_MAXTerm);
                  }
                }
                if (i >= B_8) break;
              }
          }
        }
        if (s >= B_6) break;
      }
  }
  Sets_ReleaseSet(&reps);
}

static void ComputeDR
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tItemIndex maxItem;
  Automaton_tItemIndex pAIndex;
  Automaton_tItem pA;
  Automaton_tProduction pAProd;
  Automaton_tStateIndex r;
  Automaton_tItemIndex ir;

  maxItem = Automaton_ItemIndex;
  {
    LONGCARD B_9 = 1, B_10 = maxItem;

    if (B_9 <= B_10)
      for (pAIndex = B_9;; pAIndex += 1) {
        pA = Automaton_ItemArrayPtr->A[pAIndex - 1];
        pAProd = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[pA.Prod]);
        if (pA.Rep == Automaton_NonTermRep) {
          r = pA.Next;
          {
            register Automaton_tState *W_5 = &Automaton_StateArrayPtr->A[r - 1];

            {
              LONGCARD B_11 = W_5->Items, B_12 = W_5->Items + W_5->Size - 1;

              if (B_11 <= B_12)
                for (ir = B_11;; ir += 1) {
                  {
                    register Automaton_tItem *W_6 = &Automaton_ItemArrayPtr->A[ir - 1];

                    if (W_6->Rep == Automaton_TermRep) {
                      Sets_Include(&Automaton_ItemArrayPtr->A[pAIndex - 1].Set, (Sets_tElement)W_6->Read);
                    }
                  }
                  if (ir >= B_12) break;
                }
            }
          }
        }
        if (pAIndex >= B_10) break;
      }
  }
}

static void ComputeReads
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tItemIndex pA, rC;
  Automaton_tStateIndex r;
  Automaton_tItemIndex maxItem;

  maxItem = Automaton_ItemIndex;
  {
    LONGCARD B_13 = 1, B_14 = maxItem;

    if (B_13 <= B_14)
      for (pA = B_13;; pA += 1) {
        if (Automaton_ItemArrayPtr->A[pA - 1].Rep == Automaton_NonTermRep) {
          r = Automaton_ItemArrayPtr->A[pA - 1].Next;
          {
            LONGCARD B_15 = Automaton_StateArrayPtr->A[r - 1].Items, B_16 = Automaton_StateArrayPtr->A[r - 1].Items + Automaton_StateArrayPtr->A[r - 1].Size - 1;

            if (B_15 <= B_16)
              for (rC = B_15;; rC += 1) {
                if (Automaton_ItemArrayPtr->A[rC - 1].Rep == Automaton_NonTermRep) {
                  if (Sets_IsElement((Sets_tElement)Automaton_ItemArrayPtr->A[rC - 1].Read, &Nullables)) {
                    PutInRelation(pA, rC);
                  }
                }
                if (rC >= B_16) break;
              }
          }
        }
        if (pA >= B_14) break;
      }
  }
}

static void CheckReadSets
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tItemIndex Item, MaxItem;

  MaxItem = Automaton_ItemIndex;
  {
    LONGCARD B_17 = 1, B_18 = MaxItem;

    if (B_17 <= B_18)
      for (Item = B_17;; Item += 1) {
        {
          register Automaton_tItem *W_7 = &Automaton_ItemArrayPtr->A[Item - 1];

          if (W_7->Rep == Automaton_NonTermRep) {
            if (Sets_IsEmpty(W_7->Set)) {
              W_7->EmptyReadSet = TRUE;
            } else {
              W_7->EmptyReadSet = FALSE;
              Sets_MakeSet(&W_7->ReadSet, (Sets_tElement)TokenTab_MAXTerm);
              Sets_Assign(&W_7->ReadSet, W_7->Set);
            }
          }
        }
        if (Item >= B_18) break;
      }
  }
}

static void Digraph
# ifdef __STDC__
(Lookahead_ConflictProc TreatConflict)
# else
(TreatConflict)
Lookahead_ConflictProc TreatConflict;
# endif
{
  Automaton_tItemIndex x, maxItem;

  ClearItemStack();
  ClearNumbers();
  maxItem = Automaton_ItemIndex;
  {
    LONGCARD B_19 = 1, B_20 = maxItem;

    if (B_19 <= B_20)
      for (x = B_19;; x += 1) {
        {
          register Automaton_tItem *W_8 = &Automaton_ItemArrayPtr->A[x - 1];

          if (W_8->Number == 0) {
            Traverse(x, TreatConflict);
          }
        }
        if (x >= B_20) break;
      }
  }
}

static void Traverse
# ifdef __STDC__
(Automaton_tItemIndex x, Lookahead_ConflictProc TreatConflict)
# else
(x, TreatConflict)
Automaton_tItemIndex x;
Lookahead_ConflictProc TreatConflict;
# endif
{
  CARDINAL d;
  Automaton_tIndex ArrayIndex;
  Automaton_tItemIndex yIndex;
  Automaton_tIndex u;
  Automaton_tItemIndex Top;
  BOOLEAN EmptyCycle, cyclic;

  {
    register Automaton_tItem *W_9 = &Automaton_ItemArrayPtr->A[x - 1];

    PushItem(x);
    d = ItemDepth();
    W_9->Number = d;
    {
      register Automaton_tItemIndexList *W_10 = &W_9->Relation;

      u = W_10->Used;
      {
        LONGCARD B_21 = 1, B_22 = u;

        if (B_21 <= B_22)
          for (ArrayIndex = B_21;; ArrayIndex += 1) {
            yIndex = W_10->Array->A[ArrayIndex - 1];
            if (Automaton_ItemArrayPtr->A[yIndex - 1].Number == 0) {
              Traverse(yIndex, TreatConflict);
            }
            if (Automaton_ItemArrayPtr->A[yIndex - 1].Number < W_9->Number) {
              W_9->Number = Automaton_ItemArrayPtr->A[yIndex - 1].Number;
            }
            Sets_Union(&W_9->Set, Automaton_ItemArrayPtr->A[yIndex - 1].Set);
            if (ArrayIndex >= B_22) break;
          }
      }
    }
    if (W_9->Number == d) {
      cyclic = FALSE;
      EmptyCycle = TRUE;
      do {
        Top = TopItem();
        Automaton_ItemArrayPtr->A[Top - 1].Number = Limits_MaxShortCard;
        if (Top != x) {
          Sets_Assign(&Automaton_ItemArrayPtr->A[Top - 1].Set, W_9->Set);
          cyclic = TRUE;
          EmptyCycle = EmptyCycle && Automaton_ItemArrayPtr->A[Top - 1].EmptyReadSet;
        }
      } while (!(PopItem() == x));
      if (cyclic) {
        EmptyCycle = EmptyCycle && W_9->EmptyReadSet;
        (*TreatConflict)(EmptyCycle);
      }
    }
  }
}

static void ComputeIncludesAndLookback
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex State, maxState;
  Automaton_tItemIndex Transition, Item, RepItem;
  Automaton_tItem TransItem;
  Automaton_tProduction Production;
  BOOLEAN nullable;

  ClearRelation();
  maxState = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_23 = 1, B_24 = maxState;

    if (B_23 <= B_24)
      for (State = B_23;; State += 1) {
        {
          register Automaton_tState *W_11 = &Automaton_StateArrayPtr->A[State - 1];

          {
            LONGCARD B_25 = W_11->Items, B_26 = W_11->Items + W_11->Size - 1;

            if (B_25 <= B_26)
              for (Transition = B_25;; Transition += 1) {
                TransItem = Automaton_ItemArrayPtr->A[Transition - 1];
                if (TransItem.Rep == Automaton_NonTermRep) {
                  {
                    LONGCARD B_27 = W_11->Items, B_28 = W_11->Items + W_11->Size - 1;

                    if (B_27 <= B_28)
                      for (Item = B_27;; Item += 1) {
                        {
                          register Automaton_tItem *W_12 = &Automaton_ItemArrayPtr->A[Item - 1];

                          Production = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_12->Prod]);
                          if (W_12->Pos == 0 && Production->Left == TransItem.Read) {
                            if (W_12->Pos < Production->Len) {
                              WindThrough(W_12->Next, W_12->Prod, W_12->Pos + 1, Transition, &nullable);
                              if (nullable) {
                                RepItem = W_12->RepNo;
                                if (Automaton_ItemArrayPtr->A[RepItem - 1].Rep == Automaton_NonTermRep) {
                                  if (RepItem != Transition) {
                                    PutInRelation(RepItem, Transition);
                                  }
                                }
                              }
                            } else {
                              PutInRelation(Item, Transition);
                            }
                          }
                        }
                        if (Item >= B_28) break;
                      }
                  }
                }
                if (Transition >= B_26) break;
              }
          }
        }
        if (State >= B_24) break;
      }
  }
}

static void WindThrough
# ifdef __STDC__
(Automaton_tStateIndex MyState, Automaton_tProdIndex MyProd, Automaton_tIndex MyPos, Automaton_tItemIndex Trans, BOOLEAN *nullable)
# else
(MyState, MyProd, MyPos, Trans, nullable)
Automaton_tStateIndex MyState;
Automaton_tProdIndex MyProd;
Automaton_tIndex MyPos;
Automaton_tItemIndex Trans;
BOOLEAN *nullable;
# endif
{
  Automaton_tItemIndex Item;
  Automaton_tProduction Production;

  {
    register Automaton_tState *W_13 = &Automaton_StateArrayPtr->A[MyState - 1];

    Item = W_13->Items;
    for (;;) {
      {
        register Automaton_tItem *W_14 = &Automaton_ItemArrayPtr->A[Item - 1];

        if (W_14->Prod == MyProd && W_14->Pos == MyPos) {
          goto EXIT_1;
        }
        INC(Item);
      }
    } EXIT_1:;
    {
      register Automaton_tItem *W_15 = &Automaton_ItemArrayPtr->A[Item - 1];

      Item = Automaton_ItemArrayPtr->A[Item - 1].RepNo;
      Production = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_15->Prod]);
      if (W_15->Pos < Production->Len) {
        WindThrough(W_15->Next, W_15->Prod, W_15->Pos + 1, Trans, nullable);
        if (*nullable) {
          if (Automaton_ItemArrayPtr->A[Item - 1].Rep == Automaton_NonTermRep) {
            if (Item != Trans) {
              PutInRelation(Item, Trans);
            }
          }
          *nullable = Sets_IsElement((Sets_tElement)W_15->Read, &Nullables);
        }
      } else {
        *nullable = TRUE;
        PutInRelation(Item, Trans);
      }
    }
  }
}

static void ComputeLA
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tIndex Index;
  Automaton_tItemIndex Item;
  Automaton_tItemIndex maxItem;
  Automaton_tItemIndex lookbackindex;
  Automaton_tIndex u;

  maxItem = Automaton_ItemIndex;
  {
    LONGCARD B_29 = 1, B_30 = maxItem;

    if (B_29 <= B_30)
      for (Item = B_29;; Item += 1) {
        {
          register Automaton_tItem *W_16 = &Automaton_ItemArrayPtr->A[Item - 1];

          if (W_16->Rep == Automaton_RedRep) {
            {
              register Automaton_tItemIndexList *W_17 = &W_16->Relation;

              u = W_17->Used;
              {
                LONGCARD B_31 = 1, B_32 = u;

                if (B_31 <= B_32)
                  for (Index = B_31;; Index += 1) {
                    lookbackindex = W_17->Array->A[Index - 1];
                    Sets_Union(&W_16->Set, Automaton_ItemArrayPtr->A[lookbackindex - 1].Set);
                    if (Index >= B_32) break;
                  }
              }
            }
          }
        }
        if (Item >= B_30) break;
      }
  }
}

static void TreatReadConflict
# ifdef __STDC__
(BOOLEAN empty)
# else
(empty)
BOOLEAN empty;
# endif
{
  if (!reportedError) {
    reportedError = TRUE;
  }
}

static void TreatFollowConflict
# ifdef __STDC__
(BOOLEAN empty)
# else
(empty)
BOOLEAN empty;
# endif
{
  if (!empty) {
    if (!reportedError) {
      reportedError = TRUE;
    }
  }
}

static void ClearRelation
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tItemIndex Item, maxItem;

  maxItem = Automaton_ItemIndex;
  {
    LONGCARD B_33 = 1, B_34 = maxItem;

    if (B_33 <= B_34)
      for (Item = B_33;; Item += 1) {
        Automaton_ItemArrayPtr->A[Item - 1].Relation.Used = 0;
        if (Item >= B_34) break;
      }
  }
}

static void PutInRelation
# ifdef __STDC__
(Automaton_tItemIndex Rel, Automaton_tItemIndex NT)
# else
(Rel, NT)
Automaton_tItemIndex Rel;
Automaton_tItemIndex NT;
# endif
{
  Automaton_tIndex i, u;

  {
    register Automaton_tItemIndexList *W_18 = &Automaton_ItemArrayPtr->A[Rel - 1].Relation;

    u = W_18->Used;
    {
      LONGCARD B_35 = 1, B_36 = u;

      if (B_35 <= B_36)
        for (i = B_35;; i += 1) {
          if (W_18->Array->A[i - 1] == NT) {
            return;
          }
          if (i >= B_36) break;
        }
    }
    if (W_18->Used == 0) {
      DynArray_MakeArray((ADDRESS *)&W_18->Array, &W_18->Count, (LONGINT)sizeof(Automaton_tIndex));
    } else if (W_18->Used >= W_18->Count) {
      DynArray_ExtendArray((ADDRESS *)&W_18->Array, &W_18->Count, (LONGINT)sizeof(Automaton_tIndex));
    }
    INC(W_18->Used);
    W_18->Array->A[W_18->Used - 1] = NT;
  }
}

static void ClearItemStack
# ifdef __STDC__
()
# else
()
# endif
{
  Stack.Used = 0;
}

static void PushItem
# ifdef __STDC__
(Automaton_tItemIndex Item)
# else
(Item)
Automaton_tItemIndex Item;
# endif
{
  {
    register Automaton_tItemIndexList *W_19 = &Stack;

    INC(W_19->Used);
    if (W_19->Used > W_19->Count) {
      if (W_19->Count == 0) {
        W_19->Count = InitItemStackCount;
        DynArray_MakeArray((ADDRESS *)&W_19->Array, &W_19->Count, (LONGINT)sizeof(Automaton_tItemIndex));
      } else {
        DynArray_ExtendArray((ADDRESS *)&W_19->Array, &W_19->Count, (LONGINT)sizeof(Automaton_tItemIndex));
      }
    }
    W_19->Array->A[W_19->Used - 1] = Item;
  }
}

static Automaton_tItemIndex PopItem
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tItemIndex Item;

  {
    register Automaton_tItemIndexList *W_20 = &Stack;

    if (W_20->Used < 1) {
      ERROR((STRING)"PopItem on empty Stack", 22L);
    }
    Item = W_20->Array->A[W_20->Used - 1];
    DEC(W_20->Used);
    return Item;
  }
}

static Automaton_tItemIndex TopItem
# ifdef __STDC__
()
# else
()
# endif
{
  {
    register Automaton_tItemIndexList *W_21 = &Stack;

    return W_21->Array->A[W_21->Used - 1];
  }
}

static CARDINAL ItemDepth
# ifdef __STDC__
()
# else
()
# endif
{
  return Stack.Used;
}

static void ItemStack()
{
  Stack.Used = 0;
  Stack.Count = 0;
}

static void ClearNumbers
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tItemIndex i, maxi;

  maxi = Automaton_ItemIndex;
  {
    LONGCARD B_37 = 1, B_38 = maxi;

    if (B_37 <= B_38)
      for (i = B_37;; i += 1) {
        {
          register Automaton_tItem *W_22 = &Automaton_ItemArrayPtr->A[i - 1];

          if (W_22->Rep == Automaton_NonTermRep) {
            W_22->Number = 0;
          } else {
            W_22->Number = Limits_MaxShortCard;
          }
        }
        if (i >= B_38) break;
      }
  }
}

static void ERROR
# ifdef __STDC__
(CHAR a[], LONGCARD O_1)
# else
(a, O_1)
CHAR a[];
LONGCARD O_1;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_1, CHAR)
  Strings_ArrayToString(a, O_1, &s);
  Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(s));
  FREE_OPEN_ARRAYS
}

void Lookahead__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Limits__init();
    Errors__init();
    DynArray__init();
    Sets__init();
    Strings__init();
    Automaton__init();
    Check__init();
    Positions__init();
    TokenTab__init();
    ItemStack();

    reportedError = FALSE;
  }
}
