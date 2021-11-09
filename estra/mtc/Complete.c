#include "SYSTEM_.h"

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Environs
#include "Environs.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Complete
#include "Complete.h"
#endif

BOOLEAN Complete_IsComplete;

#define eNoPattern   61
#define eNoPatAtAll   62
static void Filter ARGS((Queues_tQueue *real, Queues_tQueue *syn, Queues_tQueue *rest, Queues_tQueue *match));


void Complete_FunctionComplete
# ifdef __STDC__
(Environs_tFunction function, Idents_tIdent ident, Positions_tPosition pos)
# else
(function, ident, pos)
Environs_tFunction function;
Idents_tIdent ident;
Positions_tPosition pos;
# endif
{
  Queues_tQueue syn;
  Queues_tQueue rest;
  Queues_tQueue match;
  Queues_tQueue real;
  Patterns_tPattern pat;
  INTEGER i;

  Queues_MakeQueue(&rest);
  Queues_MakeQueue(&match);
  Queues_MakeQueue(&syn);
  Queues_Append(&syn, (ADDRESS)Patterns_NormPattern(Patterns_MakePattern(ident)));
  Queues_MakeQueue(&real);
  Environs_GetPatterns(function, &real);
  Filter(&real, &syn, &rest, &match);
  while (!Queues_IsEmpty(match)) {
    pat = (Patterns_tPattern)Queues_TakeHead(&match);
    Patterns_ReleasePattern(&pat);
  }
  Environs_GetCondPatterns(function, &real);
  Filter(&real, &syn, &rest, &match);
  while (!Queues_IsEmpty(match)) {
    pat = (Patterns_tPattern)Queues_TakeHead(&match);
    Errors_ErrorMessageI((LONGCARD)eNoPattern, (LONGCARD)Errors_eWarning, pos, (LONGCARD)Patterns_ePattern, ADR(pat));
    Patterns_ReleasePattern(&pat);
  }
  while (!Queues_IsEmpty(rest)) {
    pat = (Patterns_tPattern)Queues_TakeHead(&rest);
    Errors_ErrorMessageI((LONGCARD)eNoPatAtAll, (LONGCARD)Errors_eError, pos, (LONGCARD)Patterns_ePattern, ADR(pat));
    Patterns_ReleasePattern(&pat);
  }
  Queues_ReleaseQueue(&rest);
  Queues_ReleaseQueue(&syn);
  Queues_ReleaseQueue(&real);
}

static void Filter
# ifdef __STDC__
(Queues_tQueue *real, Queues_tQueue *syn, Queues_tQueue *rest, Queues_tQueue *match)
# else
(real, syn, rest, match)
Queues_tQueue *real, *syn, *rest, *match;
# endif
{
  Patterns_tPattern pos;
  Patterns_tPattern synpat;
  Patterns_tPattern realpat;
  Patterns_tRelation relation;

  while (!Queues_IsEmpty(*real) && !Queues_IsEmpty(*syn)) {
    realpat = (Patterns_tPattern)Queues_TakeHead(real);
    Queues_AssignEmpty(rest);
    while (!Queues_IsEmpty(*syn)) {
      synpat = (Patterns_tPattern)Queues_TakeHead(syn);
      Patterns_ResetExtendPos();
      relation = Patterns_Relation(synpat, realpat);
      switch (relation) {
      case Patterns_cEqual:;
      case Patterns_cSubsumes:;
        Queues_Append(match, (ADDRESS)synpat);
        break;
      case Patterns_cIndependent:;
      case Patterns_cSupersumes:;
        pos = Patterns_ExtendPos();
        if (pos != NIL) {
          Patterns_Extend(synpat, pos, syn);
        }
        Patterns_ReleasePattern(&synpat);
        break;
      case Patterns_cInconsistent:;
        Queues_Append(rest, (ADDRESS)synpat);
        break;
      }
    }
    Queues_Assign(syn, *rest);
  }
  Queues_Assign(rest, *syn);
}

void Complete__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Environs__init();
    Idents__init();
    Positions__init();
    Errors__init();
    Positions__init();
    Environs__init();
    Idents__init();
    Patterns__init();
    Queues__init();

    Complete_IsComplete = TRUE;
  }
}
