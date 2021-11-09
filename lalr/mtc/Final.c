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

#ifndef DEFINITION_Final
#include "Final.h"
#endif




void Final_MakeFinalToProd
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex state, maxState;
  Automaton_tProduction prod;

  Gen_FinalToProdCount = Gen_LastReadNonTermState - Gen_FirstReadTermState + 1;
  DynArray_MakeArray((ADDRESS *)&Gen_FinalToProd, &Gen_FinalToProdCount, (LONGINT)Gen_ElmtSize);
  {
    Automaton_tStateIndex B_1 = Gen_FirstReadTermState, B_2 = Gen_LastReadNonTermState;

    if (B_1 <= B_2)
      for (state = B_1;; state += 1) {
        Gen_FinalToProd->A[state - Gen_FirstReadTermState] = Gen_NoState;
        if (state >= B_2) break;
      }
  }
  maxState = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_3 = 1, B_4 = maxState;

    if (B_3 <= B_4)
      for (state = B_3;; state += 1) {
        {
          register Automaton_tState *W_1 = &Automaton_StateArrayPtr->A[state - 1];

          if (Gen_FirstReadTermState <= W_1->NewNumber && W_1->NewNumber <= Gen_LastReadNonTermState) {
            prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[W_1->Items - 1].Prod]);
            Gen_FinalToProd->A[W_1->NewNumber - Gen_FirstReadTermState] = prod->ProdNo + Gen_ReduceOffset;
          }
        }
        if (state >= B_4) break;
      }
  }
}

void Final__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Automaton__init();
    DynArray__init();
    Gen__init();

  }
}
