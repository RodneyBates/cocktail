#include "SYSTEM_.h"

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Reduce
#include "Reduce.h"
#endif

BOOLEAN Reduce_Reduced;

#define eNotReach   47
#define eNoProd   46
#define eNotTerm   45
static BOOLEAN TestReach ARGS((Sets_tSet reached));
static BOOLEAN TestTerm ARGS((Sets_tSet reached));
static void IsYetTerm ARGS((CARDINAL nt));

static Sets_tSet *G_1_todo;
static Sets_tSet *G_2_done;
static BOOLEAN *G_3_success;

void Reduce_TestReduced
# ifdef __STDC__
()
# else
()
# endif
{
  BOOLEAN ok, okreach, okterm;
  Sets_tSet reached;

  Sets_MakeSet(&reached, (Sets_tElement)TokenTab_MAXNonTerm);
  okreach = TestReach(reached);
  okterm = TestTerm(reached);
  ok = okterm;
  Reduce_Reduced = ok;
  Sets_ReleaseSet(&reached);
}

static BOOLEAN TestReach
# ifdef __STDC__
(Sets_tSet reached)
# else
(reached)
Sets_tSet reached;
# endif
{
  BOOLEAN reach;
  TokenTab_Terminal t;
  TokenTab_NonTerminal nt;
  Sets_tSet todo;
  Sets_tSet done;
  Automaton_tIndex u, i;
  Automaton_tProdIndex pn;
  Automaton_tProduction prod;
  TokenTab_Vocabulary ri, voc;
  TokenTab_TokenError error;
  Idents_tIdent sym;
  TokenTab_PosType pos;

  Sets_MakeSet(&todo, (Sets_tElement)TokenTab_MAXNonTerm);
  Sets_MakeSet(&done, (Sets_tElement)TokenTab_MAXNonTerm);
  Sets_Include(&todo, (Sets_tElement)Automaton_StartSymbol);
  Sets_Include(&reached, (Sets_tElement)Automaton_StartSymbol);
  {
    TokenTab_Terminal B_1 = TokenTab_MINTerm, B_2 = TokenTab_MAXTerm;

    if (B_1 <= B_2)
      for (t = B_1;; t += 1) {
        if (TokenTab_GetTokenType(t) == TokenTab_Term) {
          Sets_Include(&done, (Sets_tElement)t);
        }
        if (t >= B_2) break;
      }
  }
  do {
    nt = Sets_Extract(&todo);
    Sets_Include(&done, (Sets_tElement)nt);
    {
      register Automaton_tProdIndexList *W_1 = &Automaton_ProdList.A[nt - 1001];

      u = W_1->Used;
      {
        Automaton_tProdIndex B_3 = 1, B_4 = u;

        if (B_3 <= B_4)
          for (pn = B_3;; pn += 1) {
            prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_1->Array->A[pn - 1].Index]);
            {
              register struct Automaton_9 *W_2 = prod;

              {
                LONGCARD B_5 = 1, B_6 = W_2->Len;

                if (B_5 <= B_6)
                  for (i = B_5;; i += 1) {
                    ri = W_2->Right.A[i - 1];
                    Sets_Include(&reached, (Sets_tElement)ri);
                    if (!Sets_IsElement((Sets_tElement)ri, &done)) {
                      Sets_Include(&todo, (Sets_tElement)ri);
                    }
                    if (i >= B_6) break;
                  }
              }
            }
            if (pn >= B_4) break;
          }
      }
    }
  } while (!Sets_IsEmpty(todo));
  reach = TRUE;
  {
    TokenTab_Vocabulary B_7 = TokenTab_MINTerm, B_8 = TokenTab_MAXTerm;

    if (B_7 <= B_8)
      for (voc = B_7;; voc += 1) {
        if (TokenTab_GetTokenType(voc) != TokenTab_None && !Sets_IsElement((Sets_tElement)voc, &reached)) {
          TokenTab_GetTokenPos(voc, &pos);
          sym = TokenTab_TokenToSymbol(voc, &error);
          Errors_ErrorMessageI((LONGCARD)eNotReach, (LONGCARD)Errors_eWarning, pos, (LONGCARD)Errors_eIdent, ADR(sym));
        }
        if (voc >= B_8) break;
      }
  }
  {
    TokenTab_Vocabulary B_9 = TokenTab_MINNonTerm, B_10 = TokenTab_MAXNonTerm;

    if (B_9 <= B_10)
      for (voc = B_9;; voc += 1) {
        if (TokenTab_GetTokenType(voc) != TokenTab_None && !Sets_IsElement((Sets_tElement)voc, &reached)) {
          TokenTab_GetTokenPos(voc, &pos);
          sym = TokenTab_TokenToSymbol(voc, &error);
          Errors_ErrorMessageI((LONGCARD)eNotReach, (LONGCARD)Errors_eWarning, pos, (LONGCARD)Errors_eIdent, ADR(sym));
          reach = FALSE;
        }
        if (voc >= B_10) break;
      }
  }
  Sets_ReleaseSet(&todo);
  Sets_ReleaseSet(&done);
  return reach;
}

static void IsYetTerm
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
    register Automaton_tProdIndexList *W_3 = &Automaton_ProdList.A[nt - 1001];

    u = W_3->Used;
    localsuccess = FALSE;
    pn = 1;
    while (pn <= u && !localsuccess) {
      prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_3->Array->A[pn - 1].Index]);
      {
        register struct Automaton_9 *W_4 = prod;

        localsuccess = TRUE;
        i = 1;
        while (i <= W_4->Len && localsuccess) {
          ri = W_4->Right.A[i - 1];
          localsuccess = Sets_IsElement((Sets_tElement)ri, G_2_done);
          INC(i);
        }
      }
      INC(pn);
    }
  }
  if (localsuccess) {
    Sets_Include(G_2_done, nt);
    Sets_Exclude(G_1_todo, nt);
    *G_3_success = TRUE;
  }
}

static BOOLEAN TestTerm
# ifdef __STDC__
(Sets_tSet reached)
# else
(reached)
Sets_tSet reached;
# endif
{
  Sets_tSet todo;
  Sets_tSet done;
  BOOLEAN success;
  TokenTab_Terminal t;
  TokenTab_NonTerminal nt;
  BOOLEAN term;
  TokenTab_TokenError error;
  Idents_tIdent sym;
  TokenTab_PosType pos;
  CARDINAL kind;
  Sets_tSet *L_1;
  Sets_tSet *L_2;
  BOOLEAN *L_3;

  L_1 = G_1_todo;
  G_1_todo = &todo;
  L_2 = G_2_done;
  G_2_done = &done;
  L_3 = G_3_success;
  G_3_success = &success;
  Sets_MakeSet(&todo, (Sets_tElement)TokenTab_MAXNonTerm);
  Sets_MakeSet(&done, (Sets_tElement)TokenTab_MAXNonTerm);
  {
    TokenTab_NonTerminal B_11 = TokenTab_MINNonTerm, B_12 = TokenTab_MAXNonTerm;

    if (B_11 <= B_12)
      for (nt = B_11;; nt += 1) {
        if (TokenTab_GetTokenType(nt) == TokenTab_NonTerm) {
          Sets_Include(&todo, (Sets_tElement)nt);
        }
        if (nt >= B_12) break;
      }
  }
  {
    TokenTab_Terminal B_13 = TokenTab_MINTerm, B_14 = TokenTab_MAXTerm;

    if (B_13 <= B_14)
      for (t = B_13;; t += 1) {
        if (TokenTab_GetTokenType(t) == TokenTab_Term) {
          Sets_Include(&done, (Sets_tElement)t);
        }
        if (t >= B_14) break;
      }
  }
  do {
    success = FALSE;
    {
      TokenTab_NonTerminal B_15 = TokenTab_MINNonTerm, B_16 = TokenTab_MAXNonTerm;

      if (B_15 <= B_16)
        for (nt = B_15;; nt += 1) {
          if (Sets_IsElement((Sets_tElement)nt, &todo)) {
            IsYetTerm((LONGCARD)nt);
          }
          if (nt >= B_16) break;
        }
    }
  } while (!!success);
  term = TRUE;
  if (!Sets_IsEmpty(todo)) {
    do {
      nt = Sets_Extract(&todo);
      if (Sets_IsElement((Sets_tElement)nt, &reached)) {
        term = FALSE;
        kind = Errors_eError;
      } else {
        kind = Errors_eWarning;
      }
      TokenTab_GetTokenPos(nt, &pos);
      sym = TokenTab_TokenToSymbol(nt, &error);
      if (Automaton_ProdList.A[nt - 1001].Used == 0) {
        Errors_ErrorMessageI((LONGCARD)eNoProd, kind, pos, (LONGCARD)Errors_eIdent, ADR(sym));
      } else {
        Errors_ErrorMessageI((LONGCARD)eNotTerm, kind, pos, (LONGCARD)Errors_eIdent, ADR(sym));
      }
    } while (!Sets_IsEmpty(todo));
  }
  Sets_ReleaseSet(&todo);
  Sets_ReleaseSet(&done);
  G_1_todo = L_1;
  G_2_done = L_2;
  G_3_success = L_3;
  return term;
}

void Reduce__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Errors__init();
    Sets__init();
    Automaton__init();
    TokenTab__init();
    Idents__init();

  }
}
