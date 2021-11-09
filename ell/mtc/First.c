#include "SYSTEM_.h"

#ifndef DEFINITION_Derivable
#include "Derivable.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Stack
#include "Stack.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_First
#include "First.h"
#endif


static Sets_tSet vLeftRec;
static void LocalFirst ARGS((Tree_tTree t, Sets_tSet *first));
static void LocalFirsts ARGS(());
static void GlobalFirsts ARGS(());
struct S_1 {
    INTEGER A[1000 + 1];
};
static void Traverse ARGS((Idents_tIdent x));
static void TreeFirst ARGS((Tree_tTree t));
static void TreeFirsts ARGS(());

static Stack_tStack *G_1_S;
static struct S_1* *G_2_N;
static Sets_tSet *G_3_X;
static Sets_tSet *G_4_Terms;
static Sets_tSet *G_5_Nonterms;
static INTEGER *G_6_infinite;

static void LocalFirst
# ifdef __STDC__
(Tree_tTree t, Sets_tSet *first)
# else
(t, first)
Tree_tTree t;
Sets_tSet *first;
# endif
{
  Sets_tSet set;

  switch (t->U_1.V_1.Kind) {
  case Tree_Option:;
    LocalFirst(t->U_1.V_33.Option.expr, first);
    Sets_Include(first, (Sets_tElement)Scanner_Epsilon);
    break;
  case Tree_Times:;
    LocalFirst(t->U_1.V_34.Times.expr, first);
    Sets_Include(first, (Sets_tElement)Scanner_Epsilon);
    break;
  case Tree_Plus:;
    LocalFirst(t->U_1.V_35.Plus.expr, first);
    break;
  case Tree_List:;
    LocalFirst(t->U_1.V_36.List.body, first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, first)) {
      Sets_Exclude(first, (Sets_tElement)Scanner_Epsilon);
      Sets_MakeSet(&set, (Sets_tElement)Idents_MaxIdent());
      LocalFirst(t->U_1.V_36.List.sep, &set);
      Sets_Union(first, set);
      Sets_ReleaseSet(&set);
    }
    break;
  case Tree_Action:;
    Sets_AssignElmt(first, (Sets_tElement)Scanner_Epsilon);
    break;
  case Tree_Leaf:;
    Sets_AssignElmt(first, (Sets_tElement)t->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    if (Derivable_IsNullable(t->U_1.V_38.Leaf.id->U_1.V_23.Id.ident)) {
      Sets_Include(first, (Sets_tElement)Scanner_Epsilon);
    }
    break;
  case Tree_Alternative0:;
    Sets_AssignEmpty(first);
    break;
  case Tree_Alternative:;
    LocalFirst(t->U_1.V_41.Alternative.expr, first);
    Sets_MakeSet(&set, (Sets_tElement)Idents_MaxIdent());
    LocalFirst(t->U_1.V_41.Alternative.alternative, &set);
    Sets_Union(first, set);
    Sets_ReleaseSet(&set);
    break;
  case Tree_Sequence0:;
    Sets_AssignElmt(first, (Sets_tElement)Scanner_Epsilon);
    break;
  case Tree_Sequence:;
    LocalFirst(t->U_1.V_44.Sequence.expr, first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, first)) {
      Sets_Exclude(first, (Sets_tElement)Scanner_Epsilon);
      Sets_MakeSet(&set, (Sets_tElement)Idents_MaxIdent());
      LocalFirst(t->U_1.V_44.Sequence.sequence, &set);
      Sets_Union(first, set);
      Sets_ReleaseSet(&set);
    }
    break;
  }
}

static void LocalFirsts
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet N, F;
  Idents_tIdent n;

  Sets_MakeSet(&N, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&F, (Sets_tElement)Idents_MaxIdent());
  Types_Nonterminals(&N);
  while (!Sets_IsEmpty(N)) {
    n = Sets_Extract(&N);
    LocalFirst(Table_Expr(n), &F);
    Table_SetFirst(n, F);
  }
  Sets_ReleaseSet(&F);
  Sets_ReleaseSet(&N);
}

static void Traverse
# ifdef __STDC__
(Idents_tIdent x)
# else
(x)
Idents_tIdent x;
# endif
{
  INTEGER d;
  Sets_tSet Y;
  Idents_tIdent y;
  Sets_tSet Fx, Fy;

  Sets_MakeSet(&Fx, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Fy, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Y, (Sets_tElement)Idents_MaxIdent());
  Stack_Push(G_1_S, (ADDRESS)x);
  d = Stack_Depth(*G_1_S);
  (*G_2_N)->A[x] = d;
  Table_First(x, &Fx);
  Sets_Intersection(&Fx, *G_4_Terms);
  Table_First(x, &Y);
  Sets_Intersection(&Y, *G_5_Nonterms);
  while (!Sets_IsEmpty(Y)) {
    y = Sets_Extract(&Y);
    if (y == x) {
      Sets_Include(&vLeftRec, (Sets_tElement)y);
    } else if (Sets_IsElement((Sets_tElement)y, G_3_X)) {
      Sets_Exclude(G_3_X, (Sets_tElement)y);
      Traverse(y);
    }
    if ((*G_2_N)->A[y] < (*G_2_N)->A[x]) {
      (*G_2_N)->A[x] = (*G_2_N)->A[y];
    }
    Table_First(y, &Fy);
    Sets_Intersection(&Fy, *G_4_Terms);
    Sets_Exclude(&Fy, (Sets_tElement)Scanner_Epsilon);
    Sets_Union(&Fx, Fy);
  }
  Table_SetFirst(x, Fx);
  if ((*G_2_N)->A[x] == d) {
    if (Stack_Top(G_1_S) == x) {
      y = (SHORTCARD)Stack_Pop(G_1_S);
      (*G_2_N)->A[y] = *G_6_infinite;
    } else {
      do {
        y = (SHORTCARD)Stack_Pop(G_1_S);
        (*G_2_N)->A[y] = *G_6_infinite;
        Table_SetFirst(y, Fx);
        Sets_Include(&vLeftRec, (Sets_tElement)y);
      } while (!(y == x));
    }
  }
  Sets_ReleaseSet(&Y);
  Sets_ReleaseSet(&Fx);
  Sets_ReleaseSet(&Fy);
}

static void GlobalFirsts
# ifdef __STDC__
()
# else
()
# endif
{
  Stack_tStack S;
  struct S_1 *N;
  Sets_tSet X;
  Sets_tSet Terms;
  Sets_tSet Nonterms;
  INTEGER infinite;
  LONGINT s;
  Idents_tIdent x;
  Stack_tStack *L_1;
  struct S_1* *L_2;
  Sets_tSet *L_3;
  Sets_tSet *L_4;
  Sets_tSet *L_5;
  INTEGER *L_6;

  L_1 = G_1_S;
  G_1_S = &S;
  L_2 = G_2_N;
  G_2_N = &N;
  L_3 = G_3_X;
  G_3_X = &X;
  L_4 = G_4_Terms;
  G_4_Terms = &Terms;
  L_5 = G_5_Nonterms;
  G_5_Nonterms = &Nonterms;
  L_6 = G_6_infinite;
  G_6_infinite = &infinite;
  Sets_MakeSet(&vLeftRec, (Sets_tElement)Idents_MaxIdent());
  infinite = Idents_MaxIdent() + 1;
  Stack_MakeStack(&S);
  s = Idents_MaxIdent() + 1;
  DynArray_MakeArray((ADDRESS *)&N, &s, (LONGINT)sizeof(INTEGER));
  {
    SHORTCARD B_1 = 0, B_2 = Idents_MaxIdent();

    if (B_1 <= B_2)
      for (x = B_1;; x += 1) {
        N->A[x] = 0;
        if (x >= B_2) break;
      }
  }
  Sets_MakeSet(&Terms, (Sets_tElement)Idents_MaxIdent());
  Types_Terminals(&Terms);
  Sets_MakeSet(&Nonterms, (Sets_tElement)Idents_MaxIdent());
  Types_Nonterminals(&Nonterms);
  Sets_MakeSet(&X, (Sets_tElement)Idents_MaxIdent());
  Types_Nonterminals(&X);
  while (!Sets_IsEmpty(X)) {
    x = Sets_Extract(&X);
    Traverse(x);
  }
  Sets_ReleaseSet(&Terms);
  Sets_ReleaseSet(&Nonterms);
  Sets_ReleaseSet(&X);
  DynArray_ReleaseArray((ADDRESS *)&N, &s, (LONGINT)sizeof(INTEGER));
  Stack_ReleaseStack(&S);
  G_1_S = L_1;
  G_2_N = L_2;
  G_3_X = L_3;
  G_4_Terms = L_4;
  G_5_Nonterms = L_5;
  G_6_infinite = L_6;
}

BOOLEAN First_IsLeftRec
# ifdef __STDC__
(Idents_tIdent nt)
# else
(nt)
Idents_tIdent nt;
# endif
{
  return Sets_IsElement((Sets_tElement)nt, &vLeftRec);
}

static void TreeFirst
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Sets_tSet set;

  Sets_MakeSet(&t->U_1.V_32.expr.first, (Sets_tElement)Idents_MaxIdent());
  switch (t->U_1.V_1.Kind) {
  case Tree_Option:;
    {
      register Tree_yOption *W_1 = &t->U_1.V_33.Option;

      TreeFirst(W_1->expr);
      Sets_Assign(&W_1->first, W_1->expr->U_1.V_32.expr.first);
      Sets_Include(&W_1->first, (Sets_tElement)Scanner_Epsilon);
    }
    break;
  case Tree_Times:;
    {
      register Tree_yTimes *W_2 = &t->U_1.V_34.Times;

      TreeFirst(W_2->expr);
      Sets_Assign(&W_2->first, W_2->expr->U_1.V_32.expr.first);
      Sets_Include(&W_2->first, (Sets_tElement)Scanner_Epsilon);
    }
    break;
  case Tree_Plus:;
    {
      register Tree_yPlus *W_3 = &t->U_1.V_35.Plus;

      TreeFirst(W_3->expr);
      Sets_Assign(&W_3->first, W_3->expr->U_1.V_32.expr.first);
    }
    break;
  case Tree_List:;
    {
      register Tree_yList *W_4 = &t->U_1.V_36.List;

      TreeFirst(W_4->body);
      Sets_Assign(&W_4->first, W_4->body->U_1.V_32.expr.first);
      TreeFirst(W_4->sep);
      if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &W_4->first)) {
        Sets_Exclude(&W_4->first, (Sets_tElement)Scanner_Epsilon);
        Sets_Union(&W_4->first, W_4->sep->U_1.V_32.expr.first);
      }
    }
    break;
  case Tree_Action:;
    {
      register Tree_yAction *W_5 = &t->U_1.V_37.Action;

      Sets_AssignElmt(&W_5->first, (Sets_tElement)Scanner_Epsilon);
    }
    break;
  case Tree_Leaf:;
    {
      register Tree_yLeaf *W_6 = &t->U_1.V_38.Leaf;

      Table_First(W_6->id->U_1.V_23.Id.ident, &W_6->first);
    }
    break;
  case Tree_Alternative0:;
    {
      register Tree_yAlternative0 *W_7 = &t->U_1.V_40.Alternative0;

      Sets_AssignEmpty(&W_7->first);
    }
    break;
  case Tree_Alternative:;
    {
      register Tree_yAlternative *W_8 = &t->U_1.V_41.Alternative;

      TreeFirst(W_8->expr);
      Sets_Assign(&W_8->first, W_8->expr->U_1.V_32.expr.first);
      TreeFirst(W_8->alternative);
      Sets_Union(&W_8->first, W_8->alternative->U_1.V_32.expr.first);
    }
    break;
  case Tree_Sequence0:;
    {
      register Tree_ySequence0 *W_9 = &t->U_1.V_43.Sequence0;

      Sets_AssignElmt(&W_9->first, (Sets_tElement)Scanner_Epsilon);
    }
    break;
  case Tree_Sequence:;
    {
      register Tree_ySequence *W_10 = &t->U_1.V_44.Sequence;

      TreeFirst(W_10->expr);
      Sets_Assign(&W_10->first, W_10->expr->U_1.V_32.expr.first);
      TreeFirst(W_10->sequence);
      if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &W_10->first)) {
        Sets_Exclude(&W_10->first, (Sets_tElement)Scanner_Epsilon);
        Sets_Union(&W_10->first, W_10->sequence->U_1.V_32.expr.first);
      }
    }
    break;
  }
}

static void TreeFirsts
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet N;
  Idents_tIdent n;

  Sets_MakeSet(&N, (Sets_tElement)Idents_MaxIdent());
  Types_Nonterminals(&N);
  while (!Sets_IsEmpty(N)) {
    n = Sets_Extract(&N);
    TreeFirst(Table_Expr(n));
  }
  Sets_ReleaseSet(&N);
}

void First_Firsts
# ifdef __STDC__
()
# else
()
# endif
{
  LocalFirsts();
  GlobalFirsts();
  TreeFirsts();
}

void First__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Derivable__init();
    DynArray__init();
    Idents__init();
    Scanner__init();
    Sets__init();
    Stack__init();
    Table__init();
    Types__init();
    Tree__init();

  }
}
