#include "SYSTEM_.h"

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Derivable
#include "Derivable.h"
#endif


static Sets_tSet vDerivables;
static INTEGER infinite;
static void YetLength ARGS((Tree_tTree t));


void Derivable_TestDerivable
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet N;
  Idents_tIdent nt;
  Tree_tTree t;
  BOOLEAN success;

  Sets_MakeSet(&N, (Sets_tElement)Idents_MaxIdent());
  do {
    Types_Nonterminals(&N);
    success = FALSE;
    while (!Sets_IsEmpty(N)) {
      nt = Sets_Extract(&N);
      t = Table_Expr(nt);
      YetLength(t);
      if (t->U_1.V_32.expr.length < Table_Length(nt)) {
        success = TRUE;
        Table_SetLength(nt, t->U_1.V_32.expr.length);
      }
    }
  } while (!!success);
  Sets_ReleaseSet(&N);
}

static void YetLength
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Option:;
    YetLength(t->U_1.V_33.Option.expr);
    t->U_1.V_33.Option.length = 0;
    break;
  case Tree_Times:;
    YetLength(t->U_1.V_34.Times.expr);
    t->U_1.V_34.Times.length = 0;
    break;
  case Tree_Plus:;
    YetLength(t->U_1.V_35.Plus.expr);
    t->U_1.V_35.Plus.length = t->U_1.V_35.Plus.expr->U_1.V_32.expr.length;
    break;
  case Tree_List:;
    YetLength(t->U_1.V_36.List.body);
    YetLength(t->U_1.V_36.List.sep);
    t->U_1.V_36.List.length = t->U_1.V_36.List.body->U_1.V_32.expr.length;
    break;
  case Tree_Action:;
    t->U_1.V_37.Action.length = 0;
    break;
  case Tree_Leaf:;
    t->U_1.V_38.Leaf.length = Table_Length(t->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    break;
  case Tree_Alternative0:;
    t->U_1.V_40.Alternative0.length = infinite;
    break;
  case Tree_Alternative:;
    YetLength(t->U_1.V_41.Alternative.expr);
    YetLength(t->U_1.V_41.Alternative.alternative);
    t->U_1.V_41.Alternative.length = General_Min(t->U_1.V_41.Alternative.expr->U_1.V_32.expr.length, t->U_1.V_41.Alternative.alternative->U_1.V_32.expr.length);
    break;
  case Tree_Sequence0:;
    t->U_1.V_43.Sequence0.length = 0;
    break;
  case Tree_Sequence:;
    YetLength(t->U_1.V_44.Sequence.expr);
    YetLength(t->U_1.V_44.Sequence.sequence);
    t->U_1.V_44.Sequence.length = General_Min(t->U_1.V_44.Sequence.sequence->U_1.V_32.expr.length + t->U_1.V_44.Sequence.expr->U_1.V_32.expr.length, infinite);
    break;
  }
}

BOOLEAN Derivable_IsDerivable
# ifdef __STDC__
(Idents_tIdent Nonterm)
# else
(Nonterm)
Idents_tIdent Nonterm;
# endif
{
  return Table_Length(Nonterm) < infinite;
}

BOOLEAN Derivable_IsNullable
# ifdef __STDC__
(Idents_tIdent Nonterm)
# else
(Nonterm)
Idents_tIdent Nonterm;
# endif
{
  return Table_Length(Nonterm) == 0;
}

void Derivable__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    General__init();
    Idents__init();
    Sets__init();
    Table__init();
    Tree__init();
    Types__init();

    infinite = MAX_LONGINT / 2;
  }
}
