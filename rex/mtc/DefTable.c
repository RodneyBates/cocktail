#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_DefTable
#include "DefTable.h"
#endif

DefTable_DefRange DefTable_DefCount;

#define InitialDefTableSize   32
typedef struct S_1 {
    Idents_tIdent Symbol;
    DefTable_tKind Kind;
    union {
        struct {
            Tree_tTree Tree;
            SHORTCARD LeafCount;
            BOOLEAN IsConstantRE;
        } V_1;
        struct {
            SHORTCARD Number;
        } V_2;
    } U_1;
} DefType;
typedef struct S_2 {
    DefType A[100000 + 1];
} DefTable;
static DefTable *DefTablePtr;
static LONGINT DefTableSize;


void DefTable_MakeIdentDef
# ifdef __STDC__
(Idents_tIdent pSymbol, Tree_tTree pTree, SHORTCARD pLeafCount, BOOLEAN pIsConstantRE)
# else
(pSymbol, pTree, pLeafCount, pIsConstantRE)
Idents_tIdent pSymbol;
Tree_tTree pTree;
SHORTCARD pLeafCount;
BOOLEAN pIsConstantRE;
# endif
{
  INC(DefTable_DefCount);
  if (DefTable_DefCount == DefTableSize) {
    DynArray_ExtendArray((ADDRESS *)&DefTablePtr, &DefTableSize, (LONGINT)sizeof(DefType));
  }
  {
    register DefType *W_1 = &DefTablePtr->A[DefTable_DefCount];

    W_1->Symbol = pSymbol;
    W_1->Kind = DefTable_Ident;
    W_1->U_1.V_1.Tree = pTree;
    W_1->U_1.V_1.LeafCount = pLeafCount;
    W_1->U_1.V_1.IsConstantRE = pIsConstantRE;
  }
}

void DefTable_MakeStartDef
# ifdef __STDC__
(Idents_tIdent pSymbol, SHORTCARD pNumber)
# else
(pSymbol, pNumber)
Idents_tIdent pSymbol;
SHORTCARD pNumber;
# endif
{
  INC(DefTable_DefCount);
  if (DefTable_DefCount == DefTableSize) {
    DynArray_ExtendArray((ADDRESS *)&DefTablePtr, &DefTableSize, (LONGINT)sizeof(DefType));
  }
  {
    register DefType *W_2 = &DefTablePtr->A[DefTable_DefCount];

    W_2->Symbol = pSymbol;
    W_2->Kind = DefTable_Start;
    W_2->U_1.V_2.Number = pNumber;
  }
}

DefTable_DefRange DefTable_GetDef
# ifdef __STDC__
(Idents_tIdent pSymbol)
# else
(pSymbol)
Idents_tIdent pSymbol;
# endif
{
  DefTable_DefRange Def;

  {
    LONGINT B_1 = 1, B_2 = DefTable_DefCount;

    if (B_1 <= B_2)
      for (Def = B_1;; Def += 1) {
        if (DefTablePtr->A[Def].Symbol == pSymbol) {
          return Def;
        }
        if (Def >= B_2) break;
      }
  }
  return DefTable_NoDef;
}

DefTable_tKind DefTable_GetKind
# ifdef __STDC__
(DefTable_DefRange pDef)
# else
(pDef)
DefTable_DefRange pDef;
# endif
{
  return DefTablePtr->A[pDef].Kind;
}

void DefTable_GetIdentDef
# ifdef __STDC__
(DefTable_DefRange pDef, Idents_tIdent *pSymbol, Tree_tTree *pTree, SHORTCARD *pLeafCount, BOOLEAN *pIsConstantRE)
# else
(pDef, pSymbol, pTree, pLeafCount, pIsConstantRE)
DefTable_DefRange pDef;
Idents_tIdent *pSymbol;
Tree_tTree *pTree;
SHORTCARD *pLeafCount;
BOOLEAN *pIsConstantRE;
# endif
{
  {
    register DefType *W_3 = &DefTablePtr->A[pDef];

    *pSymbol = W_3->Symbol;
    *pTree = W_3->U_1.V_1.Tree;
    *pLeafCount = W_3->U_1.V_1.LeafCount;
    *pIsConstantRE = W_3->U_1.V_1.IsConstantRE;
  }
}

void DefTable_GetStartDef
# ifdef __STDC__
(DefTable_DefRange pDef, Idents_tIdent *pSymbol, SHORTCARD *pNumber)
# else
(pDef, pSymbol, pNumber)
DefTable_DefRange pDef;
Idents_tIdent *pSymbol;
SHORTCARD *pNumber;
# endif
{
  {
    register DefType *W_4 = &DefTablePtr->A[pDef];

    *pSymbol = W_4->Symbol;
    *pNumber = W_4->U_1.V_2.Number;
  }
}

void DefTable__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Tree__init();
    DynArray__init();
    Idents__init();
    Tree__init();

    DefTableSize = InitialDefTableSize;
    DynArray_MakeArray((ADDRESS *)&DefTablePtr, &DefTableSize, (LONGINT)sizeof(DefType));
    DefTable_DefCount = 0;
  }
}
