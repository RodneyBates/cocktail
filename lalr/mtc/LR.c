#include "SYSTEM_.h"

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_LR
#include "LR.h"
#endif


static void ComputeNext ARGS((Automaton_tStateIndex s));


void LR_ComputeLR
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex s;

  s = Automaton_MakeFirstState();
  ComputeNext(s);
}

static void ComputeNext
# ifdef __STDC__
(Automaton_tStateIndex s)
# else
(s)
Automaton_tStateIndex s;
# endif
{
  Automaton_tStateIndex t;
  Sets_tSet g;
  TokenTab_Vocabulary v;
  BOOLEAN n;

  Sets_MakeSet(&g, (Sets_tElement)TokenTab_MAXNonTerm);
  Automaton_GotoSet(s, &g);
  while (!Sets_IsEmpty(g)) {
    v = Sets_Extract(&g);
    t = Automaton_Goto(s, v, &n);
    if (n) {
      ComputeNext(t);
    }
  }
  Sets_ReleaseSet(&g);
}

void LR__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Automaton__init();
    Sets__init();
    TokenTab__init();

  }
}
