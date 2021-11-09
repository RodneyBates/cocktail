#include "SYSTEM_.h"

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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Follow
#include "Follow.h"
#endif


static void Start ARGS((Idents_tIdent start));
static void LocalFollow ARGS((Tree_tTree t, Sets_tSet follow));
static void LocalFollows ARGS(());
static void GlobalFollows ARGS(());
struct S_1 {
    INTEGER A[1000 + 1];
};
static void Traverse ARGS((Idents_tIdent x));
static void TreeFollow ARGS((Tree_tTree t, Sets_tSet follow));
static void TreeFollows ARGS(());

static Stack_tStack *G_1_S;
static struct S_1* *G_2_N;
static Sets_tSet *G_3_X;
static Sets_tSet *G_4_Nonterms;
static Sets_tSet *G_5_Terms;
static INTEGER *G_6_infinite;

static void Start
# ifdef __STDC__
(Idents_tIdent start)
# else
(start)
Idents_tIdent start;
# endif
{
  Sets_tSet F;

  Sets_MakeSet(&F, (Sets_tElement)Idents_MaxIdent());
  Sets_AssignElmt(&F, (Sets_tElement)Scanner_EndOfToken);
  Table_ExtendFollow(start, F);
  Sets_ReleaseSet(&F);
}

static void LocalFollow
# ifdef __STDC__
(Tree_tTree t, Sets_tSet follow)
# else
(t, follow)
Tree_tTree t;
Sets_tSet follow;
# endif
{
  Sets_tSet s;

  switch (t->U_1.V_1.Kind) {
  case Tree_Option:;
    LocalFollow(t->U_1.V_33.Option.expr, follow);
    break;
  case Tree_Times:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, follow);
    Sets_Union(&s, t->U_1.V_34.Times.first);
    Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
    LocalFollow(t->U_1.V_34.Times.expr, s);
    Sets_ReleaseSet(&s);
    break;
  case Tree_Plus:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, follow);
    Sets_Union(&s, t->U_1.V_35.Plus.first);
    Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
    LocalFollow(t->U_1.V_35.Plus.expr, s);
    Sets_ReleaseSet(&s);
    break;
  case Tree_List:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, t->U_1.V_36.List.sep->U_1.V_32.expr.first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
      Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
      Sets_Union(&s, t->U_1.V_36.List.body->U_1.V_32.expr.first);
      if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
        Sets_Union(&s, t->U_1.V_36.List.sep->U_1.V_32.expr.first);
        Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
      }
    }
    Sets_Union(&s, follow);
    LocalFollow(t->U_1.V_36.List.body, s);
    Sets_Assign(&s, t->U_1.V_36.List.body->U_1.V_32.expr.first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
      Sets_Union(&s, t->U_1.V_36.List.sep->U_1.V_32.expr.first);
      Sets_Union(&s, follow);
      Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
    }
    LocalFollow(t->U_1.V_36.List.sep, s);
    Sets_ReleaseSet(&s);
    break;
  case Tree_Action:;
    break;
  case Tree_Leaf:;
    {
      register Tree_yId *W_1 = &t->U_1.V_38.Leaf.id->U_1.V_23.Id;

      if (Types_IsNonterm(W_1->ident)) {
        Table_ExtendFollow(W_1->ident, follow);
      }
    }
    break;
  case Tree_Alternative0:;
    break;
  case Tree_Alternative:;
    LocalFollow(t->U_1.V_41.Alternative.expr, follow);
    LocalFollow(t->U_1.V_41.Alternative.alternative, follow);
    break;
  case Tree_Sequence0:;
    break;
  case Tree_Sequence:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, t->U_1.V_44.Sequence.sequence->U_1.V_32.expr.first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
      Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
      Sets_Union(&s, follow);
    }
    LocalFollow(t->U_1.V_44.Sequence.expr, s);
    Sets_ReleaseSet(&s);
    LocalFollow(t->U_1.V_44.Sequence.sequence, follow);
    break;
  }
}

static void LocalFollows
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet N;
  Sets_tSet F;
  Idents_tIdent n;

  Sets_MakeSet(&N, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&F, (Sets_tElement)Idents_MaxIdent());
  Types_Nonterminals(&N);
  while (!Sets_IsEmpty(N)) {
    n = Sets_Extract(&N);
    Sets_AssignElmt(&F, (Sets_tElement)n);
    LocalFollow(Table_Expr(n), F);
  }
  Sets_ReleaseSet(&N);
  Sets_ReleaseSet(&F);
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
  Table_Follow(x, &Fx);
  Sets_Intersection(&Fx, *G_5_Terms);
  Table_Follow(x, &Y);
  Sets_Intersection(&Y, *G_4_Nonterms);
  while (!Sets_IsEmpty(Y)) {
    y = Sets_Extract(&Y);
    if (Sets_IsElement((Sets_tElement)y, G_3_X)) {
      Sets_Exclude(G_3_X, (Sets_tElement)y);
      Traverse(y);
    }
    if ((*G_2_N)->A[y] < (*G_2_N)->A[x]) {
      (*G_2_N)->A[x] = (*G_2_N)->A[y];
    }
    Table_Follow(y, &Fy);
    Sets_Intersection(&Fy, *G_5_Terms);
    Sets_Union(&Fx, Fy);
  }
  Table_SetFollow(x, Fx);
  if ((*G_2_N)->A[x] == d) {
    do {
      y = (SHORTCARD)Stack_Pop(G_1_S);
      (*G_2_N)->A[y] = *G_6_infinite;
      Table_SetFollow(y, Fx);
    } while (!(y == x));
  }
  Sets_ReleaseSet(&Fx);
  Sets_ReleaseSet(&Fy);
  Sets_ReleaseSet(&Y);
}

static void GlobalFollows
# ifdef __STDC__
()
# else
()
# endif
{
  Stack_tStack S;
  struct S_1 *N;
  Sets_tSet X;
  Sets_tSet Terms, Nonterms;
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
  L_4 = G_4_Nonterms;
  G_4_Nonterms = &Nonterms;
  L_5 = G_5_Terms;
  G_5_Terms = &Terms;
  L_6 = G_6_infinite;
  G_6_infinite = &infinite;
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
  G_4_Nonterms = L_4;
  G_5_Terms = L_5;
  G_6_infinite = L_6;
}

static void TreeFollow
# ifdef __STDC__
(Tree_tTree t, Sets_tSet follow)
# else
(t, follow)
Tree_tTree t;
Sets_tSet follow;
# endif
{
  Sets_tSet s;

  Sets_MakeSet(&t->U_1.V_32.expr.follow, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&t->U_1.V_32.expr.follow, follow);
  Sets_MakeSet(&t->U_1.V_32.expr.fifo, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&t->U_1.V_32.expr.fifo, t->U_1.V_32.expr.first);
  if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &t->U_1.V_32.expr.fifo)) {
    Sets_Exclude(&t->U_1.V_32.expr.fifo, (Sets_tElement)Scanner_Epsilon);
    Sets_Union(&t->U_1.V_32.expr.fifo, t->U_1.V_32.expr.follow);
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Option:;
    TreeFollow(t->U_1.V_33.Option.expr, follow);
    break;
  case Tree_Times:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, follow);
    Sets_Union(&s, t->U_1.V_34.Times.first);
    Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
    TreeFollow(t->U_1.V_34.Times.expr, s);
    Sets_ReleaseSet(&s);
    break;
  case Tree_Plus:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, follow);
    Sets_Union(&s, t->U_1.V_34.Times.first);
    Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
    TreeFollow(t->U_1.V_35.Plus.expr, s);
    Sets_ReleaseSet(&s);
    break;
  case Tree_List:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, t->U_1.V_36.List.sep->U_1.V_32.expr.first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
      Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
      Sets_Union(&s, t->U_1.V_36.List.body->U_1.V_32.expr.first);
      if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
        Sets_Union(&s, t->U_1.V_36.List.sep->U_1.V_32.expr.first);
        Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
      }
    }
    Sets_Union(&s, follow);
    TreeFollow(t->U_1.V_36.List.body, s);
    Sets_Assign(&s, t->U_1.V_36.List.body->U_1.V_32.expr.first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
      Sets_Union(&s, t->U_1.V_36.List.sep->U_1.V_32.expr.first);
      Sets_Union(&s, follow);
      Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
    }
    TreeFollow(t->U_1.V_36.List.sep, s);
    Sets_ReleaseSet(&s);
    break;
  case Tree_Action:;
    break;
  case Tree_Leaf:;
    break;
  case Tree_Alternative0:;
    break;
  case Tree_Alternative:;
    TreeFollow(t->U_1.V_41.Alternative.expr, follow);
    TreeFollow(t->U_1.V_41.Alternative.alternative, follow);
    break;
  case Tree_Sequence0:;
    break;
  case Tree_Sequence:;
    Sets_MakeSet(&s, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&s, t->U_1.V_44.Sequence.sequence->U_1.V_32.expr.first);
    if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &s)) {
      Sets_Exclude(&s, (Sets_tElement)Scanner_Epsilon);
      Sets_Union(&s, follow);
    }
    TreeFollow(t->U_1.V_44.Sequence.expr, s);
    Sets_ReleaseSet(&s);
    TreeFollow(t->U_1.V_44.Sequence.sequence, follow);
    break;
  }
}

static void TreeFollows
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet N;
  Sets_tSet F;
  Idents_tIdent n;

  Sets_MakeSet(&N, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&F, (Sets_tElement)Idents_MaxIdent());
  Types_Nonterminals(&N);
  while (!Sets_IsEmpty(N)) {
    n = Sets_Extract(&N);
    Table_Follow(n, &F);
    TreeFollow(Table_Expr(n), F);
  }
  Sets_ReleaseSet(&N);
  Sets_ReleaseSet(&F);
}

void Follow_Follows
# ifdef __STDC__
(Idents_tIdent start)
# else
(start)
Idents_tIdent start;
# endif
{
  Start(start);
  LocalFollows();
  GlobalFollows();
  TreeFollows();
}

void Follow__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    DynArray__init();
    Idents__init();
    Scanner__init();
    Sets__init();
    Stack__init();
    Table__init();
    Tree__init();
    Types__init();

  }
}
