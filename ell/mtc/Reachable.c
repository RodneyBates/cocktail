#include "SYSTEM_.h"

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Reachable
#include "Reachable.h"
#endif


static Sets_tSet vReachable;


void Reachable_WindThrough
# ifdef __STDC__
(Idents_tIdent start)
# else
(start)
Idents_tIdent start;
# endif
{
  Sets_tSet todo, leafs, done;
  Idents_tIdent id;

  Sets_MakeSet(&vReachable, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&todo, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&leafs, (Sets_tElement)Idents_MaxIdent());
  Sets_Include(&todo, (Sets_tElement)start);
  do {
    start = Sets_Extract(&todo);
    Sets_Include(&vReachable, (Sets_tElement)start);
    if (Types_IsNonterm(start)) {
      Table_Leafs(start, &leafs);
      Sets_Difference(&leafs, vReachable);
      Sets_Union(&todo, leafs);
    }
  } while (!Sets_IsEmpty(todo));
  Sets_ReleaseSet(&todo);
  Sets_ReleaseSet(&leafs);
}

BOOLEAN Reachable_IsReachable
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((Sets_tElement)id, &vReachable);
}

void Reachable__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Idents__init();
    Sets__init();
    Table__init();
    Types__init();

  }
}
