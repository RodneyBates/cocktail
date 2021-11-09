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

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Continue
#include "Continue.h"
#endif

struct Continue_1 Continue_Value;



void Continue_MakeContinuation
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex state, maxState;
  Automaton_tIndex MinProdNo;
  Automaton_tIndex i;
  Automaton_tItemIndex item, BestItem;
  Automaton_tProduction prod;

  Gen_ContinuationCount = Gen_LastReadState + 1;
  DynArray_MakeArray((ADDRESS *)&Gen_Continuation, &Gen_ContinuationCount, (LONGINT)Gen_ElmtSize);
  Gen_Continuation->A[0] = 0;
  maxState = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_1 = 1, B_2 = maxState;

    if (B_1 <= B_2)
      for (state = B_1;; state += 1) {
        {
          register Automaton_tState *W_1 = &Automaton_StateArrayPtr->A[state - 1];

          if (W_1->Kind == Automaton_sRead) {
            MinProdNo = Automaton_Infinite;
            item = W_1->Items;
            for (;;) {
              if (item >= W_1->Items + W_1->Size) {
                goto EXIT_1;
              }
              {
                register Automaton_tItem *W_2 = &Automaton_ItemArrayPtr->A[item - 1];

                if (Automaton_ItemArrayPtr->A[W_2->RepNo - 1].Rep == Automaton_TermRep || Automaton_ItemArrayPtr->A[W_2->RepNo - 1].Rep == Automaton_RedRep) {
                  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_2->Prod]);
                  {
                    register struct Automaton_9 *W_3 = prod;

                    if (W_3->ProdNo < MinProdNo) {
                      MinProdNo = W_3->ProdNo;
                      BestItem = W_2->RepNo;
                      goto EXIT_1;
                    }
                  }
                }
              }
              INC(item);
            } EXIT_1:;
            {
              register Automaton_tItem *W_4 = &Automaton_ItemArrayPtr->A[BestItem - 1];

              if (W_4->Rep == Automaton_TermRep) {
                Gen_Continuation->A[W_1->NewNumber] = W_4->Read;
              } else {
                Gen_Continuation->A[W_1->NewNumber] = Sets_Select(&W_4->Set);
              }
            }
          }
        }
        if (state >= B_2) break;
      }
  }
}

void Continue_ValueNonterms
# ifdef __STDC__
()
# else
()
# endif
{
  TokenTab_Vocabulary voc;
  Automaton_tProduction prod;
  Automaton_tProdIndex index, maxIndex;
  BOOLEAN success;
  Automaton_tIndex value;
  Automaton_tIndex i;

  {
    TokenTab_Vocabulary B_3 = TokenTab_MINNonTerm, B_4 = TokenTab_MAXNonTerm;

    if (B_3 <= B_4)
      for (voc = B_3;; voc += 1) {
        Continue_Value.A[voc] = Automaton_Infinite;
        if (voc >= B_4) break;
      }
  }
  {
    TokenTab_Vocabulary B_5 = TokenTab_MINTerm, B_6 = TokenTab_MAXTerm;

    if (B_5 <= B_6)
      for (voc = B_5;; voc += 1) {
        Continue_Value.A[voc] = 1;
        if (voc >= B_6) break;
      }
  }
  maxIndex = Automaton_ProdIndex;
  do {
    success = FALSE;
    index = 0;
    while (index < maxIndex) {
      prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
      value = 0;
      {
        register struct Automaton_9 *W_5 = prod;

        {
          LONGCARD B_7 = 1, B_8 = W_5->Len;

          if (B_7 <= B_8)
            for (i = B_7;; i += 1) {
              voc = W_5->Right.A[i - 1];
              if (value == Automaton_Infinite || Continue_Value.A[voc] == Automaton_Infinite) {
                value = Automaton_Infinite;
              } else {
                INC1(value, Continue_Value.A[voc]);
              }
              if (i >= B_8) break;
            }
        }
        if (Continue_Value.A[W_5->Left] > value) {
          Continue_Value.A[W_5->Left] = value;
          success = TRUE;
        }
      }
      index = Automaton_NextProdIndex(index);
    }
  } while (!!success);
}

void Continue__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Automaton__init();
    TokenTab__init();
    Automaton__init();
    DynArray__init();
    Gen__init();
    Sets__init();
    TokenTab__init();

  }
}
