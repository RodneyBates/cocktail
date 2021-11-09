#include "SYSTEM_.h"

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Continue
#include "Continue.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Debug
#include "Debug.h"
#endif

BOOLEAN Debug_NoTrace, Debug_Fast, Debug_ItemSets;
IO_tFile Debug_dFile;

#define InitTab   0
#define MaxTabA   40
#define MaxTabB   30
#define MaxTabC   50
#define MaxTabD   40
#define InitChainLength   50
typedef struct S_1 {
    SHORTCARD count;
    LONGINT max;
    struct S_6 {
        Automaton_tItemIndex A[Automaton_Infinite - 1 + 1];
    } *path;
} tItemPath;
typedef struct S_2 {
    Automaton_tProdIndex Prod;
    Automaton_tIndex Pos;
} tProdPathElmt;
typedef struct S_3 {
    SHORTCARD count;
    LONGINT max;
    struct S_7 {
        tProdPathElmt A[Automaton_Infinite - 1 + 1];
    } *path;
} tProdPath;
typedef struct S_4 {
    Automaton_tItemIndex Item;
    Automaton_tIndex Last;
} tItemChainElmt;
typedef struct S_5 {
    Sets_tSet reached;
    LONGINT level;
    LONGINT count;
    LONGINT max;
    struct S_8 {
        tItemChainElmt A[Automaton_Infinite - 1 + 1];
    } *chain;
} tItemChain;
static tProdPath PathA;
static tItemPath PathC;
static tItemPath PathB;
static tItemChain ChainD;
static tProdPath PathD;
static void WriteItem ARGS((Automaton_tItemIndex Item, TokenTab_Terminal t));
static void DebugRedItem ARGS((Automaton_tStateIndex State, Sets_tSet *CS, Automaton_tItemIndex Item, Sets_tSet *EI));
static BOOLEAN Possible ARGS((Automaton_tItemIndex Item, TokenTab_Terminal t));
#define yes        0
#define no        1
#define maybe        2
typedef unsigned char triaer;
static triaer Poss ARGS((Automaton_tStateIndex state, Automaton_tProdIndex prod, Automaton_tIndex pos, CARDINAL depth));
static Automaton_tRep GetRep ARGS((Automaton_tItemIndex Item));
static void FindPathC ARGS((Sets_tSet *cs, Automaton_tItemIndex Item));
static void SearchPathC ARGS((Sets_tSet *cs, CARDINAL maxdepth, CARDINAL depth, Automaton_tItemIndex Item, BOOLEAN *found));
static void UnRepPathC ARGS(());
static void WritePartA ARGS((CARDINAL *d, TokenTab_NonTerminal N));
static void FindPathA ARGS((TokenTab_NonTerminal N));
static void SearchPathA ARGS((TokenTab_NonTerminal From, TokenTab_NonTerminal To, CARDINAL maxdepth, CARDINAL depth, BOOLEAN *found, Sets_tSet *rNTs));
static void WritePartB ARGS((CARDINAL *d, Automaton_tItemIndex I));
static void WritePartC ARGS((CARDINAL *d, Automaton_tItemIndex I, TokenTab_Terminal t));
static void WritePartD ARGS((CARDINAL dist, Automaton_tStateIndex State, TokenTab_Terminal t, Automaton_tItemIndex RedItem, Sets_tSet EI));
static void MakeChainD ARGS(());
static void PutInChain ARGS((Automaton_tItemIndex Item, Automaton_tIndex Last));
static void FindPathD ARGS((TokenTab_NonTerminal NT, Automaton_tStateIndex EndState));
static void WriteProd ARGS((Automaton_tProdIndex p, Automaton_tIndex l, CARDINAL *d));
static void WriteVoc ARGS((TokenTab_Vocabulary voc, CARDINAL *length));
static CARDINAL VocLength ARGS((TokenTab_Vocabulary voc));
static void WriteTab ARGS((CARDINAL d));

static Sets_tSet *G_1_reached;
static TokenTab_Terminal *G_2_t;

void Debug_InformIgnored
# ifdef __STDC__
(Automaton_tItemIndex Item, TokenTab_Terminal t)
# else
(Item, t)
Automaton_tItemIndex Item;
TokenTab_Terminal t;
# endif
{
  IO_WriteS(Debug_dFile, (STRING)"ignored                 ", 24L);
  WriteItem(Item, t);
}

void Debug_InformLowPri
# ifdef __STDC__
(Automaton_tItemIndex Item, TokenTab_Terminal t)
# else
(Item, t)
Automaton_tItemIndex Item;
TokenTab_Terminal t;
# endif
{
  IO_WriteS(Debug_dFile, (STRING)"ignored (precedence)    ", 24L);
  WriteItem(Item, t);
}

void Debug_InformRightAss
# ifdef __STDC__
(Automaton_tItemIndex Item, TokenTab_Terminal t)
# else
(Item, t)
Automaton_tItemIndex Item;
TokenTab_Terminal t;
# endif
{
  IO_WriteS(Debug_dFile, (STRING)"ignored (associativity) ", 24L);
  WriteItem(Item, t);
}

void Debug_InformLeftAss
# ifdef __STDC__
(Automaton_tItemIndex Item, TokenTab_Terminal t)
# else
(Item, t)
Automaton_tItemIndex Item;
TokenTab_Terminal t;
# endif
{
  IO_WriteS(Debug_dFile, (STRING)"ignored (associativity) ", 24L);
  WriteItem(Item, t);
}

void Debug_InformKept
# ifdef __STDC__
(Automaton_tItemIndex Item, TokenTab_Terminal t)
# else
(Item, t)
Automaton_tItemIndex Item;
TokenTab_Terminal t;
# endif
{
  IO_WriteS(Debug_dFile, (STRING)"retained                ", 24L);
  WriteItem(Item, t);
}

void Debug_InformConflict
# ifdef __STDC__
(Debug_tConflict kind)
# else
(kind)
Debug_tConflict kind;
# endif
{
  switch (kind) {
  case Debug_ShRed:;
    IO_WriteS(Debug_dFile, (STRING)"there is a read reduce conflict", 31L);
    break;
  case Debug_RedRed:;
    IO_WriteS(Debug_dFile, (STRING)"there is a reduce reduce conflict", 33L);
    break;
  case Debug_ShRedRed:;
    IO_WriteS(Debug_dFile, (STRING)"there is a read-reduce-reduce conflict", 38L);
    break;
  default :
    break;
  }
  IO_WriteNl(Debug_dFile);
}

void Debug_NewLine
# ifdef __STDC__
()
# else
()
# endif
{
  IO_WriteNl(Debug_dFile);
}

static void WriteItem
# ifdef __STDC__
(Automaton_tItemIndex Item, TokenTab_Terminal t)
# else
(Item, t)
Automaton_tItemIndex Item;
TokenTab_Terminal t;
# endif
{
  CARDINAL length;
  Automaton_tIndex i;
  Automaton_tProduction p;

  {
    register Automaton_tItem *W_1 = &Automaton_ItemArrayPtr->A[Item - 1];

    p = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_1->Prod]);
    WriteVoc(p->Left, &length);
    IO_WriteS(Debug_dFile, (STRING)" -> ", 4L);
    length = 0;
    {
      register struct Automaton_9 *W_2 = p;

      if (W_2->Len == 0) {
        IO_WriteS(Debug_dFile, (STRING)"-Epsilon-.", 10L);
      } else {
        if (W_1->Pos == 0) {
          IO_WriteS(Debug_dFile, (STRING)".", 1L);
        }
        {
          LONGCARD B_1 = 1, B_2 = W_2->Len;

          if (B_1 <= B_2)
            for (i = B_1;; i += 1) {
              WriteVoc(W_2->Right.A[i - 1], &length);
              if (W_1->Pos == i) {
                IO_WriteS(Debug_dFile, (STRING)".", 1L);
              } else {
                IO_WriteS(Debug_dFile, (STRING)" ", 1L);
              }
              if (i >= B_2) break;
            }
        }
      }
    }
    if (W_1->Pos == p->Len && t != TokenTab_MINTerm) {
      IO_WriteS(Debug_dFile, (STRING)" {", 2L);
      WriteVoc(t, &length);
      IO_WriteS(Debug_dFile, (STRING)"}", 1L);
    }
    IO_WriteNl(Debug_dFile);
  }
}

void Debug_PrintItemSets
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT state;
  Automaton_tItemIndex item;

  {
    LONGINT B_3 = 1, B_4 = Automaton_StateIndex;

    if (B_3 <= B_4)
      for (state = B_3;; state += 1) {
        IO_WriteS(Debug_dFile, (STRING)"State ", 6L);
        IO_WriteI(Debug_dFile, state, 1L);
        IO_WriteS(Debug_dFile, (STRING)" = { ", 5L);
        IO_WriteNl(Debug_dFile);
        {
          LONGCARD B_5 = Automaton_StateArrayPtr->A[state - 1].Items, B_6 = Automaton_StateArrayPtr->A[state - 1].Items + Automaton_StateArrayPtr->A[state - 1].Size - 1;

          if (B_5 <= B_6)
            for (item = B_5;; item += 1) {
              WriteItem(item, TokenTab_MINTerm);
              if (item >= B_6) break;
            }
        }
        IO_WriteS(Debug_dFile, (STRING)" } ", 3L);
        IO_WriteNl(Debug_dFile);
        IO_WriteNl(Debug_dFile);
        if (state >= B_4) break;
      }
  }
}

void Debug_DebugHead
# ifdef __STDC__
(Automaton_tStateIndex State)
# else
(State)
Automaton_tStateIndex State;
# endif
{
  if (Debug_NoTrace) {
    return;
  }
  IO_WriteS(Debug_dFile, (STRING)"State ", 6L);
  IO_WriteI(Debug_dFile, (LONGINT)State, 1L);
  IO_WriteNl(Debug_dFile);
  IO_WriteNl(Debug_dFile);
}

void Debug_DebugEnd
# ifdef __STDC__
()
# else
()
# endif
{
  if (Debug_NoTrace) {
    return;
  }
  IO_WriteNl(Debug_dFile);
}

void Debug_DebugState
# ifdef __STDC__
(Automaton_tStateIndex State, Sets_tSet *CS)
# else
(State, CS)
Automaton_tStateIndex State;
Sets_tSet *CS;
# endif
{
  Automaton_tItemIndex Item;
  Sets_tSet s;
  Sets_tSet EI;

  if (Debug_NoTrace) {
    return;
  }
  IO_WriteNl(Debug_dFile);
  Sets_MakeSet(&s, (Sets_tElement)TokenTab_MAXTerm);
  {
    register Automaton_tState *W_3 = &Automaton_StateArrayPtr->A[State - 1];

    Sets_MakeSet(&EI, W_3->Size - 1);
    {
      LONGCARD B_7 = W_3->Items, B_8 = W_3->Items + W_3->Size - 1;

      if (B_7 <= B_8)
        for (Item = B_7;; Item += 1) {
          {
            register Automaton_tItem *W_4 = &Automaton_ItemArrayPtr->A[Item - 1];

            if (W_4->Rep == Automaton_RedRep) {
              Sets_Assign(&s, *CS);
              Sets_Intersection(&s, W_4->Set);
              if (!Sets_IsEmpty(s)) {
                DebugRedItem(State, CS, Item, &EI);
              }
            }
          }
          if (Item >= B_8) break;
        }
    }
    Sets_ReleaseSet(&EI);
  }
  Sets_ReleaseSet(&s);
}

static void DebugRedItem
# ifdef __STDC__
(Automaton_tStateIndex State, Sets_tSet *CS, Automaton_tItemIndex Item, Sets_tSet *EI)
# else
(State, CS, Item, EI)
Automaton_tStateIndex State;
Sets_tSet *CS;
Automaton_tItemIndex Item;
Sets_tSet *EI;
# endif
{
  Sets_tSet T;
  Sets_tSet cs;
  Automaton_tItemIndex i;
  Automaton_tItemIndex I;
  CARDINAL d;
  TokenTab_Terminal t;
  Automaton_tProduction prod;

  Sets_MakeSet(&cs, (Sets_tElement)TokenTab_MAXTerm);
  Sets_Assign(&cs, *CS);
  FindPathC(&cs, Item);
  UnRepPathC();
  Sets_MakeSet(&T, (Sets_tElement)TokenTab_MAXTerm);
  i = PathC.path->A[PathC.count - 1];
  while (!Sets_IsEmpty(cs)) {
    t = Sets_Extract(&cs);
    {
      register Automaton_tItem *W_5 = &Automaton_ItemArrayPtr->A[i - 1];

      {
        register Automaton_tState *W_6 = &Automaton_StateArrayPtr->A[W_5->Next - 1];

        I = W_6->Items;
        for (;;) {
          if (I >= W_6->Items + W_6->Size) {
            goto EXIT_1;
          }
          if (Possible(I, t)) {
            d = InitTab;
            if (!Debug_Fast) {
              prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[I - 1].Prod]);
              WritePartA(&d, prod->Left);
            }
            WritePartB(&d, I);
            WritePartC(&d, Item, t);
            WritePartD(d, State, t, Item, *EI);
            IO_WriteNl(Debug_dFile);
            IO_WriteNl(Debug_dFile);
            DynArray_ReleaseArray((ADDRESS *)&PathB.path, &PathB.max, (LONGINT)sizeof(Automaton_tItemIndex));
            goto EXIT_1;
          }
          INC(I);
        } EXIT_1:;
      }
    }
  }
  Sets_ReleaseSet(&T);
  Sets_ReleaseSet(&cs);
  DynArray_ReleaseArray((ADDRESS *)&PathC.path, &PathC.max, (LONGINT)sizeof(Automaton_tItemIndex));
}

static triaer Poss
# ifdef __STDC__
(Automaton_tStateIndex state, Automaton_tProdIndex prod, Automaton_tIndex pos, CARDINAL depth)
# else
(state, prod, pos, depth)
Automaton_tStateIndex state;
Automaton_tProdIndex prod;
Automaton_tIndex pos;
CARDINAL depth;
# endif
{
  triaer res;
  TokenTab_NonTerminal nt;
  Automaton_tItemIndex item;
  Automaton_tItemIndex Item;
  Automaton_tProduction production;

  {
    register Automaton_tState *W_7 = &Automaton_StateArrayPtr->A[state - 1];

    Item = W_7->Items;
    for (;;) {
      {
        register Automaton_tItem *W_8 = &Automaton_ItemArrayPtr->A[Item - 1];

        if (W_8->Prod == prod && W_8->Pos == pos) {
          goto EXIT_2;
        }
        INC(Item);
      }
    } EXIT_2:;
  }
  if (Sets_IsElement(Item, G_1_reached)) {
    return no;
  }
  Sets_Include(G_1_reached, Item);
  {
    register Automaton_tItem *W_9 = &Automaton_ItemArrayPtr->A[Item - 1];

    switch (GetRep(Item)) {
    case Automaton_TermRep:;
      if (*G_2_t == W_9->Read) {
        PathB.count = depth;
        PathB.max = depth;
        DynArray_MakeArray((ADDRESS *)&PathB.path, &PathB.max, (LONGINT)sizeof(Automaton_tItemIndex));
        PathB.path->A[depth - 1] = Item;
        Sets_Exclude(G_1_reached, Item);
        return yes;
      } else {
        Sets_Exclude(G_1_reached, Item);
        return no;
      }
      break;
    case Automaton_RedRep:;
      Sets_Exclude(G_1_reached, Item);
      return maybe;
      break;
    case Automaton_NonTermRep:;
      res = no;
      nt = W_9->Read;
      {
        register Automaton_tState *W_10 = &Automaton_StateArrayPtr->A[state - 1];

        {
          LONGCARD B_9 = W_10->Items, B_10 = W_10->Items + W_10->Size - 1;

          if (B_9 <= B_10)
            for (item = B_9;; item += 1) {
              {
                register Automaton_tItem *W_11 = &Automaton_ItemArrayPtr->A[item - 1];

                production = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_11->Prod]);
                if (production->Left == nt) {
                  switch (Poss(state, W_11->Prod, W_11->Pos, depth + 1)) {
                  case yes:;
                    PathB.path->A[depth - 1] = Item;
                    Sets_Exclude(G_1_reached, Item);
                    return yes;
                    break;
                  case no:;
                    break;
                  case maybe:;
                    switch (Poss(Automaton_ItemArrayPtr->A[Item - 1].Next, prod, pos + 1, depth)) {
                    case yes:;
                      Sets_Exclude(G_1_reached, Item);
                      return yes;
                      break;
                    case no:;
                      break;
                    case maybe:;
                      res = maybe;
                      break;
                    }
                    break;
                  }
                }
              }
              if (item >= B_10) break;
            }
        }
      }
      Sets_Exclude(G_1_reached, Item);
      return res;
      break;
    }
  }
}

static Automaton_tRep GetRep
# ifdef __STDC__
(Automaton_tItemIndex Item)
# else
(Item)
Automaton_tItemIndex Item;
# endif
{
  Automaton_tProduction prod;

  {
    register Automaton_tItem *W_12 = &Automaton_ItemArrayPtr->A[Item - 1];

    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_12->Prod]);
    {
      register struct Automaton_9 *W_13 = prod;

      if (W_12->Pos == W_13->Len) {
        return Automaton_RedRep;
      } else if (W_13->Right.A[W_12->Pos + 1 - 1] >= TokenTab_MINTerm && W_13->Right.A[W_12->Pos + 1 - 1] <= TokenTab_MAXTerm) {
        return Automaton_TermRep;
      } else {
        return Automaton_NonTermRep;
      }
    }
  }
}

static BOOLEAN Possible
# ifdef __STDC__
(Automaton_tItemIndex Item, TokenTab_Terminal t)
# else
(Item, t)
Automaton_tItemIndex Item;
TokenTab_Terminal t;
# endif
{
  Automaton_tStateIndex state;
  Automaton_tProdIndex prod;
  Automaton_tIndex pos;
  Sets_tSet reached;
  Sets_tSet *L_1;
  TokenTab_Terminal *L_2;

  L_1 = G_1_reached;
  G_1_reached = &reached;
  L_2 = G_2_t;
  G_2_t = &t;
  {
    register Automaton_tItem *W_14 = &Automaton_ItemArrayPtr->A[Item - 1];

    state = W_14->Number;
    prod = W_14->Prod;
    pos = W_14->Pos;
  }
  Sets_MakeSet(&reached, (Sets_tElement)Automaton_ItemIndex);
  if (Poss(state, prod, pos, 1L) == yes) {
    Sets_ReleaseSet(&reached);
    G_1_reached = L_1;
    G_2_t = L_2;
    return TRUE;
  } else {
    Sets_ReleaseSet(&reached);
    G_1_reached = L_1;
    G_2_t = L_2;
    return FALSE;
  }
}

static void FindPathC
# ifdef __STDC__
(Sets_tSet *cs, Automaton_tItemIndex Item)
# else
(cs, Item)
Sets_tSet *cs;
Automaton_tItemIndex Item;
# endif
{
  CARDINAL maxdepth;
  BOOLEAN found;
  Automaton_tIndex i, u;

  maxdepth = 0;
  found = FALSE;
  do {
    INC(maxdepth);
    {
      register Automaton_tItemIndexList *W_15 = &Automaton_ItemArrayPtr->A[Item - 1].Relation;

      i = 1;
      u = W_15->Used;
      while (i <= u && !found) {
        SearchPathC(cs, maxdepth, 0L, W_15->Array->A[i - 1], &found);
        INC(i);
      }
    }
  } while (!found);
}

static void SearchPathC
# ifdef __STDC__
(Sets_tSet *cs, CARDINAL maxdepth, CARDINAL depth, Automaton_tItemIndex Item, BOOLEAN *found)
# else
(cs, maxdepth, depth, Item, found)
Sets_tSet *cs;
CARDINAL maxdepth;
CARDINAL depth;
Automaton_tItemIndex Item;
BOOLEAN *found;
# endif
{
  Sets_tSet s;
  Automaton_tIndex i, u;

  {
    register Automaton_tItem *W_16 = &Automaton_ItemArrayPtr->A[Item - 1];

    INC(depth);
    Sets_MakeSet(&s, (Sets_tElement)TokenTab_MAXTerm);
    if (!W_16->EmptyReadSet) {
      Sets_Assign(&s, W_16->ReadSet);
    }
    Sets_Intersection(&s, *cs);
    *found = !Sets_IsEmpty(s);
    if (*found) {
      Sets_Assign(cs, s);
    }
    Sets_ReleaseSet(&s);
    if (*found) {
      PathC.count = depth;
      PathC.max = depth;
      DynArray_MakeArray((ADDRESS *)&PathC.path, &PathC.max, (LONGINT)sizeof(Automaton_tItemIndex));
      PathC.path->A[depth - 1] = Item;
    } else if (depth < maxdepth) {
      {
        register Automaton_tItemIndexList *W_17 = &Automaton_ItemArrayPtr->A[Item - 1].Relation;

        i = 1;
        u = W_17->Used;
        while (i <= u && !*found) {
          SearchPathC(cs, maxdepth, depth, W_17->Array->A[i - 1], found);
          INC(i);
        }
        if (*found) {
          PathC.path->A[depth - 1] = Item;
        }
      }
    }
  }
}

static void UnRepPathC
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex State;
  Automaton_tItemIndex PathItem, Item;
  CARDINAL i, j;
  Automaton_tProduction prod;
  Automaton_tIndex PathVal, val;

  {
    register tItemPath *W_18 = &PathC;

    {
      LONGCARD B_11 = 1, B_12 = W_18->count - 1;

      if (B_11 <= B_12)
        for (i = B_11;; i += 1) {
          PathItem = W_18->path->A[i - 1];
          prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[PathItem - 1].Prod]);
          PathVal = 0;
          {
            LONGCARD B_13 = Automaton_ItemArrayPtr->A[PathItem - 1].Pos + 1, B_14 = prod->Len;

            if (B_13 <= B_14)
              for (j = B_13;; j += 1) {
                INC1(PathVal, Continue_Value.A[prod->Right.A[j - 1]]);
                if (j >= B_14) break;
              }
          }
          State = Automaton_ItemArrayPtr->A[PathItem - 1].Number;
          {
            register Automaton_tState *W_19 = &Automaton_StateArrayPtr->A[State - 1];

            {
              LONGCARD B_15 = W_19->Items, B_16 = W_19->Items + W_19->Size - 1;

              if (B_15 <= B_16)
                for (Item = B_15;; Item += 1) {
                  if (Automaton_ItemArrayPtr->A[Item - 1].RepNo == Automaton_ItemArrayPtr->A[PathItem - 1].RepNo) {
                    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[Item - 1].Prod]);
                    val = 0;
                    {
                      LONGCARD B_17 = Automaton_ItemArrayPtr->A[Item - 1].Pos + 1, B_18 = prod->Len;

                      if (B_17 <= B_18)
                        for (j = B_17;; j += 1) {
                          INC1(val, Continue_Value.A[prod->Right.A[j - 1]]);
                          if (j >= B_18) break;
                        }
                    }
                    if (val < PathVal) {
                      PathItem = Item;
                      PathVal = val;
                    }
                  }
                  if (Item >= B_16) break;
                }
            }
          }
          W_18->path->A[i - 1] = PathItem;
          if (i >= B_12) break;
        }
    }
  }
}

static void WritePartA
# ifdef __STDC__
(CARDINAL *d, TokenTab_NonTerminal N)
# else
(d, N)
CARDINAL *d;
TokenTab_NonTerminal N;
# endif
{
  CARDINAL i, j;

  FindPathA(N);
  {
    register tProdPath *W_20 = &PathA;

    {
      LONGCARD B_19 = 1, B_20 = W_20->count;

      if (B_19 <= B_20)
        for (i = B_19;; i += 1) {
          WriteTab(*d);
          WriteProd(W_20->path->A[i - 1].Prod, W_20->path->A[i - 1].Pos, d);
          IO_WriteNl(Debug_dFile);
          if (*d > MaxTabA || i == W_20->count && *d > InitTab) {
            WriteTab((LONGCARD)InitTab);
            {
              LONGCARD B_21 = InitTab + 1, B_22 = *d;

              if (B_21 <= B_22)
                for (j = B_21;; j += 1) {
                  IO_WriteC(Debug_dFile, '.');
                  if (j >= B_22) break;
                }
            }
            IO_WriteC(Debug_dFile, ':');
            IO_WriteNl(Debug_dFile);
            *d = InitTab;
            WriteTab(*d);
            IO_WriteC(Debug_dFile, ':');
            IO_WriteNl(Debug_dFile);
          }
          if (i >= B_20) break;
        }
    }
  }
  DynArray_ReleaseArray((ADDRESS *)&PathA.path, &PathA.max, (LONGINT)sizeof(tProdPathElmt));
}

static void FindPathA
# ifdef __STDC__
(TokenTab_NonTerminal N)
# else
(N)
TokenTab_NonTerminal N;
# endif
{
  CARDINAL maxdepth;
  BOOLEAN found;
  Sets_tSet rNTs;

  maxdepth = 0;
  found = FALSE;
  Sets_MakeSet(&rNTs, (Sets_tElement)TokenTab_MAXNonTerm);
  do {
    INC(maxdepth);
    SearchPathA(Automaton_StartSymbol, N, maxdepth, 0L, &found, &rNTs);
  } while (!found);
  Sets_ReleaseSet(&rNTs);
}

static void SearchPathA
# ifdef __STDC__
(TokenTab_NonTerminal From, TokenTab_NonTerminal To, CARDINAL maxdepth, CARDINAL depth, BOOLEAN *found, Sets_tSet *rNTs)
# else
(From, To, maxdepth, depth, found, rNTs)
TokenTab_NonTerminal From;
TokenTab_NonTerminal To;
CARDINAL maxdepth;
CARDINAL depth;
BOOLEAN *found;
Sets_tSet *rNTs;
# endif
{
  Automaton_tProduction prod;
  Automaton_tProdIndex prodindex;
  Automaton_tIndex pos;
  Automaton_tIndex i, u;

  if (From == To) {
    {
      register tProdPath *W_21 = &PathA;

      W_21->count = depth;
      W_21->max = depth;
      DynArray_MakeArray((ADDRESS *)&W_21->path, &W_21->max, (LONGINT)sizeof(tProdPathElmt));
      *found = TRUE;
    }
  } else if (depth < maxdepth) {
    {
      register Automaton_tProdIndexList *W_22 = &Automaton_ProdList.A[From - 1001];

      u = W_22->Used;
      {
        LONGCARD B_23 = 1, B_24 = u;

        if (B_23 <= B_24)
          for (i = B_23;; i += 1) {
            prodindex = W_22->Array->A[i - 1].Index;
            prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[prodindex]);
            {
              register struct Automaton_9 *W_23 = prod;

              {
                LONGCARD B_25 = 1, B_26 = W_23->Len;

                if (B_25 <= B_26)
                  for (pos = B_25;; pos += 1) {
                    if (W_23->Right.A[pos - 1] >= TokenTab_MINNonTerm && W_23->Right.A[pos - 1] <= TokenTab_MAXNonTerm) {
                      if (!Sets_IsElement((Sets_tElement)W_23->Right.A[pos - 1], rNTs)) {
                        Sets_Include(rNTs, (Sets_tElement)W_23->Right.A[pos - 1]);
                        SearchPathA(W_23->Right.A[pos - 1], To, maxdepth, depth + 1, found, rNTs);
                        Sets_Exclude(rNTs, (Sets_tElement)W_23->Right.A[pos - 1]);
                      }
                      if (*found) {
                        PathA.path->A[depth + 1 - 1].Prod = prodindex;
                        PathA.path->A[depth + 1 - 1].Pos = pos - 1;
                        return;
                      }
                    }
                    if (pos >= B_26) break;
                  }
              }
            }
            if (i >= B_24) break;
          }
      }
    }
  }
}

static void WritePartB
# ifdef __STDC__
(CARDINAL *d, Automaton_tItemIndex I)
# else
(d, I)
CARDINAL *d;
Automaton_tItemIndex I;
# endif
{
  Automaton_tProdIndex p;
  Automaton_tIndex l;
  Automaton_tIndex l1;
  CARDINAL length;
  CARDINAL i, j;
  CARDINAL d1;
  Automaton_tProduction prod;

  p = Automaton_ItemArrayPtr->A[I - 1].Prod;
  l = Automaton_ItemArrayPtr->A[I - 1].Pos - 1;
  l1 = Automaton_ItemArrayPtr->A[PathB.path->A[1 - 1] - 1].Pos;
  d1 = 0;
  WriteTab(*d);
  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[p]);
  {
    register struct Automaton_9 *W_24 = prod;

    {
      LONGCARD B_27 = 1, B_28 = W_24->Len;

      if (B_27 <= B_28)
        for (i = B_27;; i += 1) {
          WriteVoc(W_24->Right.A[i - 1], &length);
          IO_WriteS(Debug_dFile, (STRING)" ", 1L);
          if (i <= l) {
            INC1(*d, length + 1);
          } else if (i <= l1) {
            INC1(d1, length + 1);
          }
          if (i >= B_28) break;
        }
    }
  }
  DEC(d1);
  IO_WriteNl(Debug_dFile);
  {
    register tItemPath *W_25 = &PathB;

    {
      LONGCARD B_29 = 2, B_30 = W_25->count;

      if (B_29 <= B_30)
        for (i = B_29;; i += 1) {
          if (*d + d1 + 1 > MaxTabB && d1 > 1) {
            WriteTab(*d);
            IO_WriteS(Debug_dFile, (STRING)": ", 2L);
            {
              LONGCARD B_31 = 2, B_32 = d1;

              if (B_31 <= B_32)
                for (j = B_31;; j += 1) {
                  IO_WriteC(Debug_dFile, '.');
                  if (j >= B_32) break;
                }
            }
            IO_WriteC(Debug_dFile, ':');
            IO_WriteNl(Debug_dFile);
            WriteTab(*d);
            IO_WriteS(Debug_dFile, (STRING)": :", 3L);
            IO_WriteNl(Debug_dFile);
            d1 = 1;
          }
          p = Automaton_ItemArrayPtr->A[W_25->path->A[i - 1] - 1].Prod;
          l = Automaton_ItemArrayPtr->A[W_25->path->A[i - 1] - 1].Pos;
          WriteTab(*d);
          IO_WriteC(Debug_dFile, ':');
          WriteTab(d1);
          WriteProd(p, l, &d1);
          IO_WriteNl(Debug_dFile);
          if (i >= B_30) break;
        }
    }
  }
  WriteTab(*d);
  IO_WriteC(Debug_dFile, ':');
  IO_WriteNl(Debug_dFile);
}

static void WritePartC
# ifdef __STDC__
(CARDINAL *d, Automaton_tItemIndex I, TokenTab_Terminal t)
# else
(d, I, t)
CARDINAL *d;
Automaton_tItemIndex I;
TokenTab_Terminal t;
# endif
{
  CARDINAL i, j;
  Automaton_tProdIndex p;
  CARDINAL l;
  Automaton_tProduction prod;
  CARDINAL d1;

  {
    register tItemPath *W_26 = &PathC;

    for (i = W_26->count - 1; i >= 1; i += -1) {
      if (*d > MaxTabC) {
        WriteTab((LONGCARD)InitTab);
        {
          LONGCARD B_33 = InitTab + 1, B_34 = *d;

          if (B_33 <= B_34)
            for (j = B_33;; j += 1) {
              IO_WriteC(Debug_dFile, '.');
              if (j >= B_34) break;
            }
        }
        IO_WriteC(Debug_dFile, ':');
        IO_WriteNl(Debug_dFile);
        *d = InitTab;
        WriteTab(*d);
        IO_WriteC(Debug_dFile, ':');
        IO_WriteNl(Debug_dFile);
      }
      p = Automaton_ItemArrayPtr->A[W_26->path->A[i - 1] - 1].Prod;
      l = Automaton_ItemArrayPtr->A[W_26->path->A[i - 1] - 1].Pos;
      WriteTab(*d);
      WriteProd(p, l, d);
      IO_WriteNl(Debug_dFile);
    }
  }
  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[I - 1].Prod]);
  d1 = *d;
  p = Automaton_ItemArrayPtr->A[I - 1].Prod;
  l = Automaton_ItemArrayPtr->A[I - 1].Pos;
  WriteTab(d1);
  WriteProd(p, l, &d1);
  IO_WriteNl(Debug_dFile);
  l = VocLength(prod->Left);
  if (*d >= 4 + 7 + l) {
    DEC1(*d, 4 + 7 + l);
  } else {
    WriteTab(*d);
    IO_WriteC(Debug_dFile, ':');
    {
      LONGCARD B_35 = *d + 1, B_36 = 4 + 7 + l;

      if (B_35 <= B_36)
        for (j = B_35;; j += 1) {
          IO_WriteC(Debug_dFile, '.');
          if (j >= B_36) break;
        }
    }
    IO_WriteNl(Debug_dFile);
    WriteTab(4 + 7 + l);
    IO_WriteC(Debug_dFile, ':');
    IO_WriteNl(Debug_dFile);
    *d = 0;
  }
  {
    register struct Automaton_9 *W_27 = prod;

    WriteTab(*d);
    IO_WriteS(Debug_dFile, (STRING)"reduce ", 7L);
    WriteVoc(W_27->Left, &l);
    IO_WriteS(Debug_dFile, (STRING)" -> ", 4L);
    if (W_27->Len == 0) {
      IO_WriteS(Debug_dFile, (STRING)"-Epsilon-", 9L);
    } else {
      {
        LONGCARD B_37 = 1, B_38 = W_27->Len;

        if (B_37 <= B_38)
          for (i = B_37;; i += 1) {
            WriteVoc(W_27->Right.A[i - 1], &l);
            if (i < W_27->Len) {
              IO_WriteC(Debug_dFile, ' ');
            }
            if (i >= B_38) break;
          }
      }
    }
    IO_WriteS(Debug_dFile, (STRING)". {", 3L);
    WriteVoc(t, &l);
    IO_WriteS(Debug_dFile, (STRING)"} ?", 3L);
    IO_WriteNl(Debug_dFile);
  }
}

static void WritePartD
# ifdef __STDC__
(CARDINAL dist, Automaton_tStateIndex State, TokenTab_Terminal t, Automaton_tItemIndex RedItem, Sets_tSet EI)
# else
(dist, State, t, RedItem, EI)
CARDINAL dist;
Automaton_tStateIndex State;
TokenTab_Terminal t;
Automaton_tItemIndex RedItem;
Sets_tSet EI;
# endif
{
  Automaton_tItemIndex Item;
  Automaton_tProduction prod;
  CARDINAL i, j, l;
  CARDINAL d;
  Automaton_tProduction RedProd;

  RedProd = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[RedItem - 1].Prod]);
  {
    register Automaton_tState *W_28 = &Automaton_StateArrayPtr->A[State - 1];

    {
      LONGCARD B_39 = W_28->Items, B_40 = W_28->Items + W_28->Size - 1;

      if (B_39 <= B_40)
        for (Item = B_39;; Item += 1) {
          {
            register Automaton_tItem *W_29 = &Automaton_ItemArrayPtr->A[Item - 1];

            if (W_29->Read == t && !Sets_IsElement(Item - W_28->Items, &EI)) {
              Sets_Include(&EI, Item - W_28->Items);
              d = InitTab;
              prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_29->Prod]);
              {
                register struct Automaton_9 *W_30 = prod;

                if (W_29->Pos != Automaton_ItemArrayPtr->A[RedItem - 1].Pos || W_30->Left != RedProd->Left) {
                  IO_WriteNl(Debug_dFile);
                  FindPathD(W_30->Left, State);
                  {
                    register tProdPath *W_31 = &PathD;

                    {
                      LONGCARD B_41 = 1, B_42 = W_31->count - 1;

                      if (B_41 <= B_42)
                        for (i = B_41;; i += 1) {
                          WriteTab(d);
                          WriteProd(W_31->path->A[i - 1].Prod, W_31->path->A[i - 1].Pos, &d);
                          IO_WriteNl(Debug_dFile);
                          if (d > MaxTabD) {
                            WriteTab((LONGCARD)InitTab);
                            {
                              LONGCARD B_43 = InitTab + 1, B_44 = d;

                              if (B_43 <= B_44)
                                for (j = B_43;; j += 1) {
                                  IO_WriteC(Debug_dFile, '.');
                                  if (j >= B_44) break;
                                }
                            }
                            IO_WriteC(Debug_dFile, ':');
                            IO_WriteNl(Debug_dFile);
                            d = InitTab;
                            WriteTab(d);
                            IO_WriteC(Debug_dFile, ':');
                            IO_WriteNl(Debug_dFile);
                          }
                          if (i >= B_42) break;
                        }
                    }
                  }
                  DynArray_ReleaseArray((ADDRESS *)&PathD.path, &PathD.max, (LONGINT)sizeof(tProdPathElmt));
                  WriteTab(d);
                  WriteProd(W_29->Prod, 0L, &d);
                  IO_WriteNl(Debug_dFile);
                  l = VocLength(W_30->Left);
                  if (d >= 4 + 7 + l) {
                    DEC1(d, 4 + 7 + l);
                  } else {
                    WriteTab(d);
                    IO_WriteC(Debug_dFile, ':');
                    {
                      LONGCARD B_45 = d + 1, B_46 = 4 + 7 + l;

                      if (B_45 <= B_46)
                        for (j = B_45;; j += 1) {
                          IO_WriteC(Debug_dFile, '.');
                          if (j >= B_46) break;
                        }
                    }
                    IO_WriteNl(Debug_dFile);
                    WriteTab(4 + 7 + l);
                    IO_WriteC(Debug_dFile, ':');
                    IO_WriteNl(Debug_dFile);
                    d = 0;
                  }
                } else {
                  d = dist;
                }
                WriteTab(d);
                IO_WriteS(Debug_dFile, (STRING)"read   ", 7L);
                WriteVoc(W_30->Left, &l);
                IO_WriteS(Debug_dFile, (STRING)" -> ", 4L);
                if (W_29->Pos == 0) {
                  IO_WriteC(Debug_dFile, '.');
                }
                {
                  LONGCARD B_47 = 1, B_48 = W_30->Len;

                  if (B_47 <= B_48)
                    for (i = B_47;; i += 1) {
                      WriteVoc(W_30->Right.A[i - 1], &l);
                      if (i == W_29->Pos) {
                        IO_WriteC(Debug_dFile, '.');
                      } else if (i < W_30->Len) {
                        IO_WriteC(Debug_dFile, ' ');
                      }
                      if (i >= B_48) break;
                    }
                }
                IO_WriteS(Debug_dFile, (STRING)" ?", 2L);
              }
              IO_WriteNl(Debug_dFile);
            }
          }
          if (Item >= B_40) break;
        }
    }
  }
}

static void PutInChain
# ifdef __STDC__
(Automaton_tItemIndex Item, Automaton_tIndex Last)
# else
(Item, Last)
Automaton_tItemIndex Item;
Automaton_tIndex Last;
# endif
{
  Automaton_tProduction prod;
  Automaton_tStateIndex State;
  Automaton_tItemIndex I;

  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[Item - 1].Prod]);
  while (Automaton_ItemArrayPtr->A[Item - 1].Pos < prod->Len && !Sets_IsElement(Item, &ChainD.reached)) {
    {
      register tItemChain *W_32 = &ChainD;

      INC(W_32->count);
      if (W_32->count > W_32->max) {
        DynArray_ExtendArray((ADDRESS *)&W_32->chain, &W_32->max, (LONGINT)sizeof(tItemChainElmt));
      }
      W_32->chain->A[W_32->count - 1].Last = Last;
      W_32->chain->A[W_32->count - 1].Item = Item;
      Sets_Include(&W_32->reached, Item);
    }
    State = Automaton_ItemArrayPtr->A[Item - 1].Next;
    I = Automaton_StateArrayPtr->A[State - 1].Items;
    while (Automaton_ItemArrayPtr->A[I - 1].Prod != Automaton_ItemArrayPtr->A[Item - 1].Prod || Automaton_ItemArrayPtr->A[I - 1].Pos != Automaton_ItemArrayPtr->A[Item - 1].Pos + 1) {
      INC(I);
    }
    Item = I;
  }
}

static void MakeChainD
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT LastCount;
  Automaton_tItemIndex Item, I;
  Automaton_tStateIndex State;
  TokenTab_Vocabulary read;
  Automaton_tProduction prod;

  {
    register tItemChain *W_33 = &ChainD;

    W_33->max = InitChainLength;
    W_33->count = 0;
    W_33->level = 0;
    DynArray_MakeArray((ADDRESS *)&W_33->chain, &W_33->max, (LONGINT)sizeof(tItemChainElmt));
    Sets_MakeSet(&W_33->reached, (Sets_tElement)Automaton_ItemIndex);
    PutInChain(1L, 0L);
    for (;;) {
      {
        register tItemChain *W_34 = &ChainD;

        LastCount = W_34->count;
        if (W_34->level == LastCount) {
          goto EXIT_3;
        }
        while (W_34->level < LastCount) {
          INC(W_34->level);
          Item = W_34->chain->A[W_34->level - 1].Item;
          read = Automaton_ItemArrayPtr->A[Item - 1].Read;
          if (read >= TokenTab_MINNonTerm && read <= TokenTab_MAXNonTerm) {
            State = Automaton_ItemArrayPtr->A[Item - 1].Number;
            {
              LONGCARD B_49 = Automaton_StateArrayPtr->A[State - 1].Items, B_50 = Automaton_StateArrayPtr->A[State - 1].Items + Automaton_StateArrayPtr->A[State - 1].Size - 1;

              if (B_49 <= B_50)
                for (I = B_49;; I += 1) {
                  {
                    register Automaton_tItem *W_35 = &Automaton_ItemArrayPtr->A[I - 1];

                    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_35->Prod]);
                    if (prod->Left == read && Automaton_ItemArrayPtr->A[I - 1].Pos == 0) {
                      PutInChain(I, (LONGCARD)W_34->level);
                    }
                  }
                  if (I >= B_50) break;
                }
            }
          }
        }
      }
    } EXIT_3:;
  }
}

static void FindPathD
# ifdef __STDC__
(TokenTab_NonTerminal NT, Automaton_tStateIndex EndState)
# else
(NT, EndState)
TokenTab_NonTerminal NT;
Automaton_tStateIndex EndState;
# endif
{
  LONGINT last, level;
  Automaton_tProduction prod;
  Automaton_tItemIndex I;
  Automaton_tIndex Depth;

  if (ChainD.max == 0) {
    MakeChainD();
  }
  {
    register tItemChain *W_36 = &ChainD;

    last = 0;
    for (;;) {
      INC(last);
      I = W_36->chain->A[last - 1].Item;
      if (Automaton_ItemArrayPtr->A[I - 1].Number == EndState) {
        prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[I - 1].Prod]);
        if (NT == prod->Left) {
          goto EXIT_4;
        }
      }
    } EXIT_4:;
    Depth = 0;
    W_36->level = last;
    while (W_36->level != 0) {
      INC(Depth);
      W_36->level = W_36->chain->A[W_36->level - 1].Last;
    }
    {
      register tProdPath *W_37 = &PathD;

      W_37->count = Depth;
      W_37->max = Depth;
      DynArray_MakeArray((ADDRESS *)&W_37->path, &W_37->max, (LONGINT)sizeof(tProdPathElmt));
    }
    W_36->level = last;
    while (Depth > 0) {
      I = W_36->chain->A[W_36->level - 1].Item;
      PathD.path->A[Depth - 1].Prod = Automaton_ItemArrayPtr->A[I - 1].Prod;
      PathD.path->A[Depth - 1].Pos = Automaton_ItemArrayPtr->A[I - 1].Pos;
      DEC(Depth);
      W_36->level = W_36->chain->A[W_36->level - 1].Last;
    }
  }
}

static void WriteProd
# ifdef __STDC__
(Automaton_tProdIndex p, Automaton_tIndex l, CARDINAL *d)
# else
(p, l, d)
Automaton_tProdIndex p;
Automaton_tIndex l;
CARDINAL *d;
# endif
{
  Automaton_tProduction prod;
  Automaton_tIndex i;
  CARDINAL length;

  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[p]);
  {
    register struct Automaton_9 *W_38 = prod;

    if (W_38->Len == 0) {
      IO_WriteS(Debug_dFile, (STRING)"-Epsilon-", 9L);
    } else {
      {
        LONGCARD B_51 = 1, B_52 = W_38->Len;

        if (B_51 <= B_52)
          for (i = B_51;; i += 1) {
            WriteVoc(W_38->Right.A[i - 1], &length);
            IO_WriteS(Debug_dFile, (STRING)" ", 1L);
            if (i <= l) {
              INC1(*d, length + 1);
            }
            if (i >= B_52) break;
          }
      }
    }
  }
}

static void WriteVoc
# ifdef __STDC__
(TokenTab_Vocabulary voc, CARDINAL *length)
# else
(voc, length)
TokenTab_Vocabulary voc;
CARDINAL *length;
# endif
{
  Idents_tIdent sym;
  Strings_tString str;
  TokenTab_TokenError err;
  CARDINAL i;

  sym = TokenTab_TokenToSymbol(voc, &err);
  Idents_GetString(sym, &str);
  *length = Strings_Length(&str);
  {
    LONGCARD B_53 = 1, B_54 = *length;

    if (B_53 <= B_54)
      for (i = B_53;; i += 1) {
        IO_WriteC(Debug_dFile, Strings_Char(&str, (Strings_tStringIndex)i));
        if (i >= B_54) break;
      }
  }
}

static CARDINAL VocLength
# ifdef __STDC__
(TokenTab_Vocabulary voc)
# else
(voc)
TokenTab_Vocabulary voc;
# endif
{
  Idents_tIdent sym;
  Strings_tString str;
  TokenTab_TokenError err;

  sym = TokenTab_TokenToSymbol(voc, &err);
  Idents_GetString(sym, &str);
  return Strings_Length(&str);
}

static void WriteTab
# ifdef __STDC__
(CARDINAL d)
# else
(d)
CARDINAL d;
# endif
{
  CARDINAL i;

  {
    LONGCARD B_55 = 1, B_56 = d;

    if (B_55 <= B_56)
      for (i = B_55;; i += 1) {
        IO_WriteC(Debug_dFile, ' ');
        if (i >= B_56) break;
      }
  }
}

void Debug__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Sets__init();
    Automaton__init();
    TokenTab__init();
    Automaton__init();
    Continue__init();
    DynArray__init();
    IO__init();
    Sets__init();
    Strings__init();
    Idents__init();
    TokenTab__init();

    Debug_NoTrace = FALSE;
    Debug_Fast = FALSE;
    ChainD.max = 0;
  }
}
