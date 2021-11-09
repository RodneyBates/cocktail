#include "SYSTEM_.h"

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif


static Sets_tSet vDefined, vTerms, vNonterms;


void Types_BeginTypes
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_MakeSet(&vDefined, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&vTerms, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&vNonterms, (Sets_tElement)Idents_MaxIdent());
}

void Types_MakeTerm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  Sets_Include(&vDefined, (Sets_tElement)id);
  Sets_Include(&vTerms, (Sets_tElement)id);
}

void Types_MakeNonterm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  Sets_Include(&vDefined, (Sets_tElement)id);
  Sets_Include(&vNonterms, (Sets_tElement)id);
}

BOOLEAN Types_IsDeclared
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((Sets_tElement)id, &vDefined);
}

BOOLEAN Types_IsTerm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((Sets_tElement)id, &vTerms);
}

BOOLEAN Types_IsNonterm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((Sets_tElement)id, &vNonterms);
}

void Types_Terminals
# ifdef __STDC__
(Sets_tSet *set)
# else
(set)
Sets_tSet *set;
# endif
{
  Sets_Assign(set, vTerms);
}

void Types_Nonterminals
# ifdef __STDC__
(Sets_tSet *set)
# else
(set)
Sets_tSet *set;
# endif
{
  Sets_Assign(set, vNonterms);
}

void Types__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Sets__init();
    Idents__init();
    Sets__init();

  }
}
