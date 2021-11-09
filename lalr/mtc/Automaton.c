#include "SYSTEM_.h"

#ifndef DEFINITION_Continue
#include "Continue.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Oper
#include "Oper.h"
#endif

#ifndef DEFINITION_Rules
#include "Rules.h"
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

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

BOOLEAN Automaton_IsBnf;
struct Automaton_13 *Automaton_ProdArrayPtr;
LONGINT Automaton_ProdIndex;
CARDINAL Automaton_ProdCount;
struct Automaton_14 *Automaton_ItemArrayPtr;
LONGINT Automaton_ItemIndex;
struct Automaton_15 *Automaton_StateArrayPtr;
LONGINT Automaton_StateIndex;
struct Automaton_16 Automaton_ProdList;
struct Automaton_17 Automaton_OperArray;
TokenTab_NonTerminal Automaton_StartSymbol;

#define eNoBNF   60
#define eActInside   61
#define InitProdCount   1000
#define InitItemCount   200
#define InitStateCount   50
#define InitListCount   4
#define InitHashListCount   4
#define InitStackCount   10
#define InitRelationListCount   10
typedef LONGCARD HashIndex;
typedef struct S_1 {
    Automaton_tIndex ProdNo;
    Automaton_tIndexList Reduce;
    Lists_tList Act;
    TokenTab_PosType ActPos;
    Automaton_tAss Ass;
    TokenTab_Prio Pri;
    Automaton_tIndex Len;
    TokenTab_NonTerminal Left;
} tDummyProduction;
typedef struct S_2 {
    SHORTCARD A[4 - 1 + 1];
} tDummyRight4;
typedef struct S_3 {
    Lists_tList Act;
    TokenTab_PosType ActPos;
    TokenTab_Vocabulary Voc;
} tStackElmt;
static LONGINT ProdElmtCount;
static Automaton_tProduction Production;
static LONGINT ItemElmtCount;
static LONGINT StateElmtCount;
static struct S_4 {
    Automaton_tIndexList A[99 + 1];
} StateHashList;
static struct S_5 {
    tStackElmt A[Automaton_Infinite - 1 + 1];
} *StackArrayPtr;
static LONGINT StackElmtCount;
static LONGINT StackIndex;
static CARDINAL i;
static CARDINAL prio;
static CARDINAL NonTermNo;
static Sets_tSet ProdSet;
static void Closure ARGS((TokenTab_NonTerminal Symbol));
static Automaton_tStateIndex UniqueState ARGS((BOOLEAN *new));
static void InsertOperators ARGS(());
static void InsertProductions ARGS(());
static void InsertRight ARGS((Rules_Expression Expr, BOOLEAN Last));
static void PutInProdList ARGS((Automaton_tProdIndex index, SHORTCARD value));
static void NextProduction ARGS(());
static void EnsureProdArray ARGS(());
static void NextItem ARGS((TokenTab_Vocabulary ReadSym));
static void NextState ARGS(());
static TokenTab_NonTerminal MakeNonTerm ARGS(());
static BOOLEAN AreEqualStates ARGS((Automaton_tStateIndex Index1, Automaton_tStateIndex Index2));
static HashIndex HashCode ARGS((Automaton_tStateIndex Index));
static void PushAction ARGS((Lists_tList act, TokenTab_Vocabulary voc, TokenTab_PosType actpos));
static BOOLEAN PopAction ARGS((Lists_tList *act, TokenTab_Vocabulary *voc, TokenTab_PosType *actpos));
static void ERROR ARGS((CHAR a[], LONGCARD ));


void Automaton_InitAutomaton
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_IsBnf = TRUE;
  InsertOperators();
  InsertProductions();
}

Automaton_tStateIndex Automaton_MakeFirstState
# ifdef __STDC__
()
# else
()
# endif
{
  BOOLEAN new;
  Automaton_tProdIndex pi;
  Automaton_tProduction prod;
  TokenTab_Vocabulary read;

  NextState();
  INC(Automaton_StateArrayPtr->A[Automaton_StateIndex - 1].Size);
  pi = Automaton_ProdList.A[Automaton_StartSymbol - 1001].Array->A[1 - 1].Index;
  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[pi]);
  read = prod->Right.A[1 - 1];
  NextItem(read);
  Automaton_ItemArrayPtr->A[Automaton_ItemIndex - 1].Prod = pi;
  Automaton_ItemArrayPtr->A[Automaton_ItemIndex - 1].Pos = 0;
  Sets_MakeSet(&ProdSet, Automaton_ProdCount);
  Closure(read);
  return UniqueState(&new);
}

void Automaton_GotoSet
# ifdef __STDC__
(Automaton_tStateIndex Index, Sets_tSet *Set)
# else
(Index, Set)
Automaton_tStateIndex Index;
Sets_tSet *Set;
# endif
{
  TokenTab_Vocabulary v;
  Automaton_tItemIndex i;
  Automaton_tProdIndex pr;
  Automaton_tIndex po;
  Automaton_tProduction p;

  Sets_AssignEmpty(Set);
  {
    register Automaton_tState *W_1 = &Automaton_StateArrayPtr->A[Index - 1];

    {
      LONGCARD B_1 = W_1->Items, B_2 = W_1->Items + W_1->Size - 1;

      if (B_1 <= B_2)
        for (i = B_1;; i += 1) {
          v = Automaton_ItemArrayPtr->A[i - 1].Read;
          if (v <= TokenTab_MAXNonTerm) {
            Sets_Include(Set, (Sets_tElement)v);
          }
          if (i >= B_2) break;
        }
    }
  }
}

Automaton_tStateIndex Automaton_Goto
# ifdef __STDC__
(Automaton_tStateIndex Index, TokenTab_Vocabulary Symbol, BOOLEAN *new)
# else
(Index, Symbol, new)
Automaton_tStateIndex Index;
TokenTab_Vocabulary Symbol;
BOOLEAN *new;
# endif
{
  Automaton_tProduction p;
  Automaton_tItemIndex i;
  Automaton_tProdIndex pr;
  Automaton_tIndex po;
  Automaton_tStateIndex s;
  Automaton_tProduction prod;
  TokenTab_Vocabulary read;

  NextState();
  Sets_AssignEmpty(&ProdSet);
  {
    register Automaton_tState *W_2 = &Automaton_StateArrayPtr->A[Index - 1];

    {
      LONGCARD B_3 = W_2->Items, B_4 = W_2->Items + W_2->Size - 1;

      if (B_3 <= B_4)
        for (i = B_3;; i += 1) {
          if (Automaton_ItemArrayPtr->A[i - 1].Read == Symbol) {
            pr = Automaton_ItemArrayPtr->A[i - 1].Prod;
            po = Automaton_ItemArrayPtr->A[i - 1].Pos;
            p = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[pr]);
            if (po + 1 < p->Len) {
              read = p->Right.A[po + 2 - 1];
            } else {
              read = TokenTab_MAXNonTerm + 1;
            }
            INC(Automaton_StateArrayPtr->A[Automaton_StateIndex - 1].Size);
            NextItem(read);
            Automaton_ItemArrayPtr->A[Automaton_ItemIndex - 1].Prod = pr;
            Automaton_ItemArrayPtr->A[Automaton_ItemIndex - 1].Pos = po + 1;
            if (read >= TokenTab_MINNonTerm && read <= TokenTab_MAXNonTerm) {
              Closure(p->Right.A[po + 2 - 1]);
            }
          }
          if (i >= B_4) break;
        }
    }
  }
  s = UniqueState(new);
  {
    register Automaton_tState *W_3 = &Automaton_StateArrayPtr->A[Index - 1];

    {
      LONGCARD B_5 = W_3->Items, B_6 = W_3->Items + W_3->Size - 1;

      if (B_5 <= B_6)
        for (i = B_5;; i += 1) {
          if (Automaton_ItemArrayPtr->A[i - 1].Read == Symbol) {
            Automaton_ItemArrayPtr->A[i - 1].Next = s;
          }
          if (i >= B_6) break;
        }
    }
  }
  return s;
}

static void Closure
# ifdef __STDC__
(TokenTab_NonTerminal Symbol)
# else
(Symbol)
TokenTab_NonTerminal Symbol;
# endif
{
  Automaton_tIndex i, u;
  TokenTab_Vocabulary read;
  Automaton_tProdIndex pr;
  Automaton_tIndex po;
  BOOLEAN exists;
  Automaton_tProduction p;

  {
    register Automaton_tState *W_4 = &Automaton_StateArrayPtr->A[Automaton_StateIndex - 1];

    {
      register Automaton_tProdIndexList *W_5 = &Automaton_ProdList.A[Symbol - 1001];

      u = W_5->Used;
      {
        LONGCARD B_7 = 1, B_8 = u;

        if (B_7 <= B_8)
          for (i = B_7;; i += 1) {
            pr = W_5->Array->A[i - 1].Index;
            p = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[pr]);
            if (!Sets_IsElement(p->ProdNo, &ProdSet)) {
              Sets_Include(&ProdSet, p->ProdNo);
              INC(W_4->Size);
              {
                register struct Automaton_9 *W_6 = p;

                if (W_6->Len > 0) {
                  read = W_6->Right.A[1 - 1];
                } else {
                  read = TokenTab_MAXNonTerm + 1;
                }
              }
              NextItem(read);
              {
                register Automaton_tItem *W_7 = &Automaton_ItemArrayPtr->A[Automaton_ItemIndex - 1];

                W_7->Prod = pr;
                W_7->Pos = 0;
              }
              if (read >= TokenTab_MINNonTerm && read <= TokenTab_MAXNonTerm) {
                Closure(read);
              }
            }
            if (i >= B_8) break;
          }
      }
    }
  }
}

static Automaton_tStateIndex UniqueState
# ifdef __STDC__
(BOOLEAN *new)
# else
(new)
BOOLEAN *new;
# endif
{
  HashIndex h;
  LONGINT i;

  h = HashCode((Automaton_tStateIndex)Automaton_StateIndex);
  {
    register Automaton_tIndexList *W_8 = &StateHashList.A[h];

    {
      LONGINT B_9 = 1, B_10 = W_8->Used;

      if (B_9 <= B_10)
        for (i = B_9;; i += 1) {
          if (AreEqualStates((Automaton_tStateIndex)Automaton_StateIndex, (Automaton_tStateIndex)W_8->Array->A[i - 1])) {
            DEC1(Automaton_ItemIndex, Automaton_StateArrayPtr->A[Automaton_StateIndex - 1].Size);
            DEC(Automaton_StateIndex);
            *new = FALSE;
            return W_8->Array->A[i - 1];
          }
          if (i >= B_10) break;
        }
    }
    if (W_8->Used == 0) {
      W_8->Count = InitHashListCount;
      DynArray_MakeArray((ADDRESS *)&W_8->Array, &W_8->Count, (LONGINT)sizeof(Automaton_tIndex));
    } else if (W_8->Used >= W_8->Count) {
      DynArray_ExtendArray((ADDRESS *)&W_8->Array, &W_8->Count, (LONGINT)sizeof(Automaton_tIndex));
    }
    INC(W_8->Used);
    W_8->Array->A[W_8->Used - 1] = Automaton_StateIndex;
    *new = TRUE;
    return Automaton_StateIndex;
  }
}

static void InsertOperators
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tOper o;
  TokenTab_Vocabulary t;
  Oper_OperKind kn;
  TokenTab_PosType ps, cmp;
  Lists_tList cm;

  o.Pri = 0;
  Oper_InitPrioReading();
  while (Oper_GetPriority(&kn, &ps, &cm, &cmp)) {
    if (kn == Oper_Left) {
      o.Ass = Automaton_left;
    } else if (kn == Oper_Right) {
      o.Ass = Automaton_right;
    } else {
      o.Ass = Automaton_nonassoc;
    }
    INC(o.Pri);
    while (Oper_GetOperator(&t, &ps)) {
      Automaton_OperArray.A[t] = o;
    }
  }
}

static void InsertProductions
# ifdef __STDC__
()
# else
()
# endif
{
  TokenTab_NonTerminal left;
  TokenTab_PosType lfp, clp, cmp, pnp, prp, prsp;
  Rules_Expression right;
  Lists_tList cm;
  BOOLEAN hpr;
  TokenTab_Terminal prs;
  Lists_tList act;
  TokenTab_PosType actpos;
  TokenTab_Vocabulary voc;
  Automaton_tProdIndex index;
  Automaton_tProdIndex maxIndex;
  SHORTCARD value;
  Automaton_tProduction prod;
  SHORTCARD i;

  Rules_InitRulesReading();
  if (!Rules_GetRule(&left, &lfp, &clp, &right, &cm, &cmp, &pnp, &hpr, &prp, &prs, &prsp)) {
    ERROR((STRING)"Automaton.InsertProduction", 26L);
  }
  {
    register struct Automaton_9 *W_9 = Production;

    Lists_MakeList(&W_9->Act);
    W_9->ActPos = Positions_NoPosition;
    W_9->Ass = Automaton_none;
    W_9->Pri = 0;
    W_9->Len = 0;
  }
  EnsureProdArray();
  {
    register struct Automaton_9 *W_10 = Production;

    INC(W_10->Len);
    W_10->Right.A[W_10->Len - 1] = left;
  }
  EnsureProdArray();
  {
    register struct Automaton_9 *W_11 = Production;

    INC(W_11->Len);
    W_11->Right.A[W_11->Len - 1] = TokenTab_EndOfToken;
  }
  Automaton_StartSymbol = MakeNonTerm();
  Production->Left = Automaton_StartSymbol;
  NextProduction();
  Rules_InitRulesReading();
  while (Rules_GetRule(&left, &lfp, &clp, &right, &cm, &cmp, &pnp, &hpr, &prp, &prs, &prsp)) {
    {
      register struct Automaton_9 *W_12 = Production;

      Lists_MakeList(&W_12->Act);
      W_12->ActPos = Positions_NoPosition;
      W_12->Ass = Automaton_none;
      W_12->Pri = 0;
      W_12->Len = 0;
    }
    InsertRight(right, TRUE);
    {
      register struct Automaton_9 *W_13 = Production;

      W_13->Left = left;
      prio = Automaton_OperArray.A[prs].Pri;
      if (hpr) {
        W_13->Pri = Automaton_OperArray.A[prs].Pri;
        W_13->Ass = Automaton_OperArray.A[prs].Ass;
      }
    }
    NextProduction();
  }
  while (PopAction(&act, &voc, &actpos)) {
    {
      register struct Automaton_9 *W_14 = Production;

      W_14->Act = act;
      W_14->ActPos = actpos;
      W_14->Pri = 0;
      W_14->Ass = Automaton_none;
      W_14->Len = 0;
      W_14->Left = voc;
    }
    NextProduction();
  }
  Continue_ValueNonterms();
  maxIndex = Automaton_ProdIndex;
  index = 0;
  while (index < maxIndex) {
    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
    value = 0;
    {
      register struct Automaton_9 *W_15 = prod;

      {
        SHORTCARD B_11 = 1, B_12 = W_15->Len;

        if (B_11 <= B_12)
          for (i = B_11;; i += 1) {
            INC1(value, Continue_Value.A[W_15->Right.A[i - 1]]);
            if (i >= B_12) break;
          }
      }
    }
    PutInProdList(index, value);
    index = Automaton_NextProdIndex(index);
  }
}

static void InsertRight
# ifdef __STDC__
(Rules_Expression Expr, BOOLEAN Last)
# else
(Expr, Last)
Rules_Expression Expr;
BOOLEAN Last;
# endif
{
  TokenTab_PosType pos, secpos;
  Rules_Expression son, rson, lson;
  Rules_Operation art;
  TokenTab_Vocabulary voc;
  Lists_tList act;
  Idents_tIdent sym;
  TokenTab_TokenError err;

  switch (Rules_GetNodeOperation(Expr)) {
  case Rules_Plus:;
  case Rules_Star:;
    Automaton_IsBnf = FALSE;
    Rules_GetUnaryNode(Expr, &pos, &son);
    InsertRight(son, Last);
    Errors_ErrorMessage((LONGCARD)eNoBNF, (LONGCARD)Errors_eError, pos);
    break;
  case Rules_Bracket:;
    Rules_GetBracketNode(Expr, &pos, &secpos, &son);
    Errors_ErrorMessage((LONGCARD)eNoBNF, (LONGCARD)Errors_eWarning, pos);
    InsertRight(son, Last);
    break;
  case Rules_Optional:;
    Automaton_IsBnf = FALSE;
    Rules_GetBracketNode(Expr, &pos, &secpos, &son);
    Errors_ErrorMessage((LONGCARD)eNoBNF, (LONGCARD)Errors_eError, pos);
    break;
  case Rules_Sequence:;
    Rules_GetBinaryNode(Expr, &pos, &lson, &rson);
    if (rson == Rules_NoExpression) {
      InsertRight(lson, Last);
    } else {
      InsertRight(lson, FALSE);
    }
    InsertRight(rson, Last);
    break;
  case Rules_Separator:;
  case Rules_Alternative:;
    Automaton_IsBnf = FALSE;
    Rules_GetBinaryNode(Expr, &pos, &lson, &rson);
    InsertRight(lson, FALSE);
    Errors_ErrorMessage((LONGCARD)eNoBNF, (LONGCARD)Errors_eError, pos);
    InsertRight(rson, FALSE);
    break;
  case Rules_TermLeaf:;
    if (Automaton_IsBnf) {
      EnsureProdArray();
      Rules_GetLeafNode(Expr, &voc, &pos);
      {
        register struct Automaton_9 *W_16 = Production;

        INC(W_16->Len);
        W_16->Right.A[W_16->Len - 1] = voc;
        if (Automaton_OperArray.A[voc].Ass != Automaton_none) {
          W_16->Ass = Automaton_OperArray.A[voc].Ass;
          W_16->Pri = Automaton_OperArray.A[voc].Pri;
        }
      }
    }
    break;
  case Rules_NonTermLeaf:;
    if (Automaton_IsBnf) {
      EnsureProdArray();
      Rules_GetLeafNode(Expr, &voc, &pos);
      {
        register struct Automaton_9 *W_17 = Production;

        INC(W_17->Len);
        W_17->Right.A[W_17->Len - 1] = voc;
      }
    }
    break;
  case Rules_Action:;
    if (Automaton_IsBnf) {
      Rules_GetActionNode(Expr, &act, &pos);
      if (Last) {
        Production->Act = act;
        Production->ActPos = pos;
      } else {
        EnsureProdArray();
        voc = MakeNonTerm();
        sym = TokenTab_TokenToSymbol(voc, &err);
        Errors_ErrorMessageI((LONGCARD)eActInside, (LONGCARD)Errors_eInformation, pos, (LONGCARD)Errors_eIdent, ADR(sym));
        {
          register struct Automaton_9 *W_18 = Production;

          INC(W_18->Len);
          W_18->Right.A[W_18->Len - 1] = voc;
        }
        PushAction(act, voc, pos);
      }
    }
    break;
  case Rules_NoOperation:;
    break;
  }
}

static void PutInProdList
# ifdef __STDC__
(Automaton_tProdIndex index, SHORTCARD value)
# else
(index, value)
Automaton_tProdIndex index;
SHORTCARD value;
# endif
{
  Automaton_tProduction prod;
  Automaton_tIndex i;

  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
  {
    register Automaton_tProdIndexList *W_19 = &Automaton_ProdList.A[prod->Left - 1001];

    if (W_19->Used == 0) {
      W_19->Count = InitListCount;
      DynArray_MakeArray((ADDRESS *)&W_19->Array, &W_19->Count, (LONGINT)sizeof(Automaton_tProdListElmt));
      INC(W_19->Used);
      W_19->Array->A[W_19->Used - 1].Index = index;
      W_19->Array->A[W_19->Used - 1].Value = value;
    } else {
      if (W_19->Used >= W_19->Count) {
        DynArray_ExtendArray((ADDRESS *)&W_19->Array, &W_19->Count, (LONGINT)sizeof(Automaton_tProdListElmt));
      }
      i = W_19->Used;
      while (i > 0 && W_19->Array->A[i - 1].Value > value) {
        W_19->Array->A[i + 1 - 1].Index = W_19->Array->A[i - 1].Index;
        W_19->Array->A[i + 1 - 1].Value = W_19->Array->A[i - 1].Value;
        DEC(i);
      }
      INC(i);
      W_19->Array->A[i - 1].Index = index;
      W_19->Array->A[i - 1].Value = value;
      INC(W_19->Used);
    }
  }
}

static void NextProduction
# ifdef __STDC__
()
# else
()
# endif
{
  INC(Automaton_ProdCount);
  {
    register struct Automaton_9 *W_20 = Production;

    W_20->ProdNo = Automaton_ProdCount;
    W_20->Reduce.Used = 0;
  }
  Automaton_ProdIndex = Automaton_NextProdIndex((Automaton_tProdIndex)Automaton_ProdIndex);
  if (Automaton_ProdIndex + (sizeof(tDummyProduction) + General_MaxAlign - 1) / General_MaxAlign * General_MaxAlign >= ProdElmtCount) {
    DynArray_ExtendArray((ADDRESS *)&Automaton_ProdArrayPtr, &ProdElmtCount, (LONGINT)sizeof(WORD));
  }
  Production = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ProdIndex]);
}

Automaton_tProdIndex Automaton_NextProdIndex
# ifdef __STDC__
(Automaton_tProdIndex Index)
# else
(Index)
Automaton_tProdIndex Index;
# endif
{
  CARDINAL diff;
  Automaton_tProduction prod;

  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Index]);
  diff = (CARDINAL)((sizeof(tDummyProduction) + General_MaxAlign - 1) / General_MaxAlign * General_MaxAlign) + (prod->Len + 3) / 4 * sizeof(tDummyRight4);
  return Index + (diff - 1) / sizeof(WORD) + 1;
}

static void EnsureProdArray
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT diff;

  diff = (CARDINAL)((sizeof(tDummyProduction) + General_MaxAlign - 1) / General_MaxAlign * General_MaxAlign) + (Production->Len + 1 + 3) / 4 * sizeof(tDummyRight4);
  if (Automaton_ProdIndex + (diff - 1) / sizeof(WORD) + 1 >= ProdElmtCount) {
    DynArray_ExtendArray((ADDRESS *)&Automaton_ProdArrayPtr, &ProdElmtCount, (LONGINT)sizeof(WORD));
    Production = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ProdIndex]);
  }
}

static void NextItem
# ifdef __STDC__
(TokenTab_Vocabulary ReadSym)
# else
(ReadSym)
TokenTab_Vocabulary ReadSym;
# endif
{
  INC(Automaton_ItemIndex);
  if (Automaton_ItemIndex > ItemElmtCount) {
    DynArray_ExtendArray((ADDRESS *)&Automaton_ItemArrayPtr, &ItemElmtCount, (LONGINT)sizeof(Automaton_tItem));
    if (Automaton_ItemArrayPtr == NIL) {
      exit(1);
    }
  }
  {
    register Automaton_tItem *W_21 = &Automaton_ItemArrayPtr->A[Automaton_ItemIndex - 1];

    W_21->EmptyReadSet = TRUE;
    W_21->Relation.Used = 0;
    W_21->Relation.Count = InitRelationListCount;
    W_21->Read = ReadSym;
    W_21->Rep = Automaton_NoRep;
    W_21->RepNo = Automaton_Infinite;
    W_21->Next = Automaton_Infinite;
    W_21->Number = 0;
  }
}

static void NextState
# ifdef __STDC__
()
# else
()
# endif
{
  INC(Automaton_StateIndex);
  if (Automaton_StateIndex > StateElmtCount) {
    DynArray_ExtendArray((ADDRESS *)&Automaton_StateArrayPtr, &StateElmtCount, (LONGINT)sizeof(Automaton_tState));
  }
  {
    register Automaton_tState *W_22 = &Automaton_StateArrayPtr->A[Automaton_StateIndex - 1];

    W_22->Size = 0;
    W_22->Items = Automaton_ItemIndex + 1;
    W_22->NewNumber = Automaton_Infinite;
    W_22->Kind = Automaton_sNone;
  }
}

static TokenTab_NonTerminal MakeNonTerm
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString s;
  CARDINAL max, i, j;
  TokenTab_PosType pos;
  TokenTab_Vocabulary voc;

  s.Chars.A[1] = '_';
  s.Length = 6;
  max = TokenTab_MAXNonTerm;
  do {
    i = NonTermNo;
    for (j = 5; j >= 2; j += -1) {
      s.Chars.A[j] = CHR(ORD('0') + i % 10);
      i = i / 10;
    }
    s.Chars.A[6] = '_';
    pos = Positions_NoPosition;
    INC(NonTermNo);
    voc = TokenTab_MakeVoc(Idents_MakeIdent(&s), pos);
  } while (!(max < TokenTab_MAXNonTerm));
  return voc;
}

static BOOLEAN AreEqualStates
# ifdef __STDC__
(Automaton_tStateIndex Index1, Automaton_tStateIndex Index2)
# else
(Index1, Index2)
Automaton_tStateIndex Index1, Index2;
# endif
{
  Automaton_tItemIndex i1, i2;
  Automaton_tItemIndex l1, l2;

  i1 = Automaton_StateArrayPtr->A[Index1 - 1].Items;
  i2 = Automaton_StateArrayPtr->A[Index2 - 1].Items;
  l1 = Automaton_StateArrayPtr->A[Index1 - 1].Size;
  l2 = Automaton_StateArrayPtr->A[Index2 - 1].Size;
  if (l1 != l2) {
    return FALSE;
  }
  INC1(l1, i1);
  INC1(l2, i2);
  while (i1 < l1 && i2 < l2) {
    if (Automaton_ItemArrayPtr->A[i1 - 1].Prod != Automaton_ItemArrayPtr->A[i2 - 1].Prod) {
      return FALSE;
    }
    if (Automaton_ItemArrayPtr->A[i1 - 1].Pos != Automaton_ItemArrayPtr->A[i2 - 1].Pos) {
      return FALSE;
    }
    INC(i1);
    INC(i2);
  }
  if (i1 < l1) {
    return Automaton_ItemArrayPtr->A[i1 - 1].Pos == 0;
  } else if (i2 < l2) {
    return Automaton_ItemArrayPtr->A[i2 - 1].Pos == 0;
  } else {
    return TRUE;
  }
}

static HashIndex HashCode
# ifdef __STDC__
(Automaton_tStateIndex Index)
# else
(Index)
Automaton_tStateIndex Index;
# endif
{
  {
    register Automaton_tItem *W_23 = &Automaton_ItemArrayPtr->A[Automaton_StateArrayPtr->A[Index - 1].Items - 1];

    return (W_23->Prod + W_23->Pos) % (99L - 0L + 1) + 0L;
  }
}

static void PushAction
# ifdef __STDC__
(Lists_tList act, TokenTab_Vocabulary voc, TokenTab_PosType actpos)
# else
(act, voc, actpos)
Lists_tList act;
TokenTab_Vocabulary voc;
TokenTab_PosType actpos;
# endif
{
  INC(StackIndex);
  if (StackElmtCount == 0) {
    StackElmtCount = InitStackCount;
    DynArray_MakeArray((ADDRESS *)&StackArrayPtr, &StackElmtCount, (LONGINT)sizeof(tStackElmt));
  } else if (StackIndex > StackElmtCount) {
    DynArray_ExtendArray((ADDRESS *)&StackArrayPtr, &StackElmtCount, (LONGINT)sizeof(tStackElmt));
  }
  StackArrayPtr->A[StackIndex - 1].Act = act;
  StackArrayPtr->A[StackIndex - 1].ActPos = actpos;
  StackArrayPtr->A[StackIndex - 1].Voc = voc;
}

static BOOLEAN PopAction
# ifdef __STDC__
(Lists_tList *act, TokenTab_Vocabulary *voc, TokenTab_PosType *actpos)
# else
(act, voc, actpos)
Lists_tList *act;
TokenTab_Vocabulary *voc;
TokenTab_PosType *actpos;
# endif
{
  if (StackIndex < 1) {
    return FALSE;
  }
  *act = StackArrayPtr->A[StackIndex - 1].Act;
  *actpos = StackArrayPtr->A[StackIndex - 1].ActPos;
  *voc = StackArrayPtr->A[StackIndex - 1].Voc;
  DEC(StackIndex);
  return TRUE;
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

void Automaton__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Lists__init();
    Sets__init();
    TokenTab__init();
    Continue__init();
    DynArray__init();
    Errors__init();
    Lists__init();
    Oper__init();
    Rules__init();
    Sets__init();
    Strings__init();
    Idents__init();
    General__init();
    Positions__init();
    TokenTab__init();

    ProdElmtCount = InitProdCount;
    DynArray_MakeArray((ADDRESS *)&Automaton_ProdArrayPtr, &ProdElmtCount, (LONGINT)sizeof(WORD));
    ItemElmtCount = InitItemCount;
    DynArray_MakeArray((ADDRESS *)&Automaton_ItemArrayPtr, &ItemElmtCount, (LONGINT)sizeof(Automaton_tItem));
    StateElmtCount = InitStateCount;
    DynArray_MakeArray((ADDRESS *)&Automaton_StateArrayPtr, &StateElmtCount, (LONGINT)sizeof(Automaton_tState));
    for (i = 1001; i <= 2500; i += 1) {
      Automaton_ProdList.A[i - 1001].Used = 0;
    }
    for (i = 0L; i <= 99L; i += 1) {
      StateHashList.A[i].Used = 0;
    }
    for (i = 0; i <= 1000; i += 1) {
      {
        register Automaton_tOper *W_24 = &Automaton_OperArray.A[i];

        W_24->Ass = Automaton_none;
        W_24->Pri = 0;
      }
    }
    Automaton_ProdCount = 0;
    Automaton_ProdIndex = 0;
    Production = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ProdIndex]);
    Automaton_ItemIndex = 0;
    Automaton_StateIndex = 0;
    StackElmtCount = 0;
    StackIndex = 0;
  }
}
