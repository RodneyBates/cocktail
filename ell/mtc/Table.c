#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif


typedef struct S_3 *tTableEntryP;
typedef struct S_1 {
    char dummy;
} tTermEntry;
typedef struct S_2 {
    Tree_tTree Expr;
    Sets_tSet Leafs;
    Sets_tSet First;
    Sets_tSet Follow;
    INTEGER Length;
} tNontermEntry;
typedef struct S_3 {
    union {
        struct {
            tTermEntry Term;
        } V_1;
        struct {
            tNontermEntry Nonterm;
        } V_2;
    } U_1;
} tTableEntry;
static struct S_4 {
    tTableEntryP A[1000 + 1];
} *TableArray;
static LONGINT TableSizeL;
static INTEGER infinite;


void Table_InitTable
# ifdef __STDC__
()
# else
()
# endif
{
  Idents_tIdent id;
  Idents_tIdent MaxId;

  MaxId = Idents_MaxIdent();
  TableSizeL = MaxId + 1;
  DynArray_MakeArray((ADDRESS *)&TableArray, &TableSizeL, (LONGINT)sizeof(tTableEntryP));
  {
    SHORTCARD B_1 = 1, B_2 = Idents_MaxIdent();

    if (B_1 <= B_2)
      for (id = B_1;; id += 1) {
        if (Types_IsNonterm(id)) {
          TableArray->A[id] = (tTableEntryP)Memory_Alloc((LONGINT)sizeof(tNontermEntry));
          {
            register tNontermEntry *W_1 = &TableArray->A[id]->U_1.V_2.Nonterm;

            W_1->Expr = NIL;
            Sets_MakeSet(&W_1->Leafs, (Sets_tElement)MaxId);
            Sets_MakeSet(&W_1->First, (Sets_tElement)MaxId);
            Sets_MakeSet(&W_1->Follow, (Sets_tElement)MaxId);
            W_1->Length = infinite;
          }
        } else if (Types_IsTerm(id)) {
        } else {
          TableArray->A[id] = NIL;
        }
        if (id >= B_2) break;
      }
  }
}

void Table_SetExpr
# ifdef __STDC__
(Idents_tIdent nonterm, Tree_tTree expr)
# else
(nonterm, expr)
Idents_tIdent nonterm;
Tree_tTree expr;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    TableArray->A[nonterm]->U_1.V_2.Nonterm.Expr = expr;
  }
}

Tree_tTree Table_Expr
# ifdef __STDC__
(Idents_tIdent nonterm)
# else
(nonterm)
Idents_tIdent nonterm;
# endif
{
  return TableArray->A[nonterm]->U_1.V_2.Nonterm.Expr;
}

void Table_SetLeaf
# ifdef __STDC__
(Idents_tIdent nonterm, Idents_tIdent leaf)
# else
(nonterm, leaf)
Idents_tIdent nonterm;
Idents_tIdent leaf;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    Sets_Include(&TableArray->A[nonterm]->U_1.V_2.Nonterm.Leafs, (Sets_tElement)leaf);
  }
}

void Table_Leafs
# ifdef __STDC__
(Idents_tIdent nonterm, Sets_tSet *leafs)
# else
(nonterm, leafs)
Idents_tIdent nonterm;
Sets_tSet *leafs;
# endif
{
  Sets_Assign(leafs, TableArray->A[nonterm]->U_1.V_2.Nonterm.Leafs);
}

void Table_SetFirst
# ifdef __STDC__
(Idents_tIdent nonterm, Sets_tSet first)
# else
(nonterm, first)
Idents_tIdent nonterm;
Sets_tSet first;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    Sets_Assign(&TableArray->A[nonterm]->U_1.V_2.Nonterm.First, first);
  }
}

void Table_First
# ifdef __STDC__
(Idents_tIdent id, Sets_tSet *first)
# else
(id, first)
Idents_tIdent id;
Sets_tSet *first;
# endif
{
  if (Types_IsNonterm(id)) {
    Sets_Assign(first, TableArray->A[id]->U_1.V_2.Nonterm.First);
  } else if (Types_IsTerm(id)) {
    Sets_AssignElmt(first, (Sets_tElement)id);
  } else {
    Sets_AssignEmpty(first);
  }
}

void Table_SetFollow
# ifdef __STDC__
(Idents_tIdent nonterm, Sets_tSet follow)
# else
(nonterm, follow)
Idents_tIdent nonterm;
Sets_tSet follow;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    Sets_Assign(&TableArray->A[nonterm]->U_1.V_2.Nonterm.Follow, follow);
  }
}

void Table_ExtendFollow
# ifdef __STDC__
(Idents_tIdent nonterm, Sets_tSet follow)
# else
(nonterm, follow)
Idents_tIdent nonterm;
Sets_tSet follow;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    Sets_Union(&TableArray->A[nonterm]->U_1.V_2.Nonterm.Follow, follow);
  }
}

void Table_Follow
# ifdef __STDC__
(Idents_tIdent nonterm, Sets_tSet *follow)
# else
(nonterm, follow)
Idents_tIdent nonterm;
Sets_tSet *follow;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    Sets_Assign(follow, TableArray->A[nonterm]->U_1.V_2.Nonterm.Follow);
  } else {
    Sets_AssignEmpty(follow);
  }
}

void Table_SetLength
# ifdef __STDC__
(Idents_tIdent nonterm, INTEGER len)
# else
(nonterm, len)
Idents_tIdent nonterm;
INTEGER len;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    TableArray->A[nonterm]->U_1.V_2.Nonterm.Length = len;
  }
}

INTEGER Table_Length
# ifdef __STDC__
(Idents_tIdent nonterm)
# else
(nonterm)
Idents_tIdent nonterm;
# endif
{
  if (Types_IsNonterm(nonterm)) {
    return TableArray->A[nonterm]->U_1.V_2.Nonterm.Length;
  } else {
    return 1;
  }
}

void Table__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Sets__init();
    Tree__init();
    DynArray__init();
    Idents__init();
    Memory__init();
    Sets__init();
    Tree__init();
    Types__init();

    infinite = MAX_LONGINT / 2;
  }
}
