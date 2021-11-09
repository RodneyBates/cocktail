#include "SYSTEM_.h"

#ifndef DEFINITION_Convert
#include "Convert.h"
#endif

#ifndef DEFINITION_Heap
#include "Heap.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Stack
#include "Stack.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Info
#include "Info.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Grammar
#include "Grammar.h"
#endif


#define NoArity   -1
#define infinite   100000
typedef struct S_3 {
    INTEGER A[1000 + 1];
} *tIndexes;
typedef struct S_1 {
    Idents_tIdent superclass;
    Sets_tSet nodes;
    Sets_tSet directsubclasses;
    Sets_tSet subclasses;
    Lists_tList layouts;
} tClass;
typedef struct S_2 {
    Idents_tIdent mainclass;
    Idents_tIdent nodeident;
    INTEGER arity;
    Grammar_tSons sonnames;
    Sets_tSet classes;
    Lists_tList layouts;
    Sets_tSet numbers;
} tNode;
typedef struct S_4 {
    union {
        struct {
            tClass Class;
        } V_1;
        struct {
            tNode Node;
        } V_2;
    } U_1;
} *tClassOrNode;
static struct S_5 {
    tClassOrNode A[1000 + 1];
} *TG;
static INTEGER vMaxArity;
static void Digraph ARGS(());
static void Traverse ARGS((Idents_tIdent x, tIndexes N, Stack_tStack *S));
static void FixMainClass ARGS((Idents_tIdent node));


void Grammar_BeginGrammar
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT size;
  Idents_tIdent id;

  size = Scanner_MaxIdent + 1;
  DynArray_MakeArray((ADDRESS *)&TG, &size, (LONGINT)sizeof(tClassOrNode));
  {
    SHORTCARD B_1 = 0, B_2 = Scanner_MaxIdent;

    if (B_1 <= B_2)
      for (id = B_1;; id += 1) {
        switch (Types_Type(id)) {
        case Types_cClass:;
          TG->A[id] = (tClassOrNode)Heap_Alloc((LONGINT)sizeof(tClass));
          {
            register tClass *W_1 = &TG->A[id]->U_1.V_1.Class;

            W_1->superclass = Scanner_NoIdent;
            Sets_MakeSet(&W_1->nodes, (Sets_tElement)Scanner_MaxIdent);
            Sets_MakeSet(&W_1->directsubclasses, (Sets_tElement)Scanner_MaxIdent);
            Sets_MakeSet(&W_1->subclasses, (Sets_tElement)Scanner_MaxIdent);
            Lists_MakeList(&W_1->layouts);
          }
          break;
        case Types_cNode:;
          TG->A[id] = (tClassOrNode)Heap_Alloc((LONGINT)sizeof(tNode));
          {
            register tNode *W_2 = &TG->A[id]->U_1.V_2.Node;

            W_2->mainclass = Scanner_NoIdent;
            W_2->nodeident = id;
            W_2->arity = NoArity;
            W_2->sonnames = NIL;
            Sets_MakeSet(&W_2->classes, (Sets_tElement)Scanner_MaxIdent);
            Lists_MakeList(&W_2->layouts);
          }
          break;
        default :
          TG->A[id] = NIL;
          break;
        }
        if (id >= B_2) break;
      }
  }
}

void Grammar_SetSuperClass
# ifdef __STDC__
(Idents_tIdent class, Idents_tIdent super)
# else
(class, super)
Idents_tIdent class, super;
# endif
{
  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"SetSuperClass: class is no class", 32L);
  }
  if (Types_Type(super) != Types_cClass) {
    Errors_ERROR((STRING)"SetSuperClass: super is no class", 32L);
  }
  TG->A[class]->U_1.V_1.Class.superclass = super;
  Sets_Include(&TG->A[super]->U_1.V_1.Class.directsubclasses, (Sets_tElement)class);
}

void Grammar_Connect
# ifdef __STDC__
(Idents_tIdent node, Idents_tIdent class)
# else
(node, class)
Idents_tIdent node, class;
# endif
{
  Sets_Include(&TG->A[class]->U_1.V_1.Class.nodes, (Sets_tElement)node);
  Sets_Include(&TG->A[node]->U_1.V_2.Node.classes, (Sets_tElement)class);
}

void Grammar_CompleteSubclasses
# ifdef __STDC__
()
# else
()
# endif
{
  Digraph();
}

static void Digraph
# ifdef __STDC__
()
# else
()
# endif
{
  Stack_tStack S;
  tIndexes N;
  Idents_tIdent x;
  LONGINT size;

  Stack_MakeStack(&S);
  size = Scanner_MaxIdent + 1;
  DynArray_MakeArray((ADDRESS *)&N, &size, (LONGINT)sizeof(INTEGER));
  {
    SHORTCARD B_3 = 0, B_4 = Scanner_MaxIdent;

    if (B_3 <= B_4)
      for (x = B_3;; x += 1) {
        N->A[x] = 0;
        if (x >= B_4) break;
      }
  }
  {
    SHORTCARD B_5 = 0, B_6 = Scanner_MaxIdent;

    if (B_5 <= B_6)
      for (x = B_5;; x += 1) {
        if (N->A[x] == 0 && Types_Type(x) == Types_cClass) {
          Traverse(x, N, &S);
        }
        if (x >= B_6) break;
      }
  }
  DynArray_ReleaseArray((ADDRESS *)&N, &size, (LONGINT)sizeof(INTEGER));
  Stack_ReleaseStack(&S);
}

static void Traverse
# ifdef __STDC__
(Idents_tIdent x, tIndexes N, Stack_tStack *S)
# else
(x, N, S)
Idents_tIdent x;
tIndexes N;
Stack_tStack *S;
# endif
{
  INTEGER d;
  Sets_tSet X;
  Idents_tIdent y;

  Sets_MakeSet(&X, (Sets_tElement)Scanner_MaxIdent);
  Stack_Push(S, Convert_IdToAdr(x));
  d = Stack_Depth(*S);
  N->A[x] = d;
  Sets_Assign(&TG->A[x]->U_1.V_1.Class.subclasses, TG->A[x]->U_1.V_1.Class.directsubclasses);
  Grammar_DirectSubclasses(x, &X);
  while (!Sets_IsEmpty(X)) {
    y = Sets_Extract(&X);
    if (N->A[y] == 0) {
      Traverse(y, N, S);
    }
    if (N->A[x] > N->A[y]) {
      N->A[x] = N->A[y];
    }
    Sets_Union(&TG->A[x]->U_1.V_1.Class.subclasses, TG->A[y]->U_1.V_1.Class.subclasses);
  }
  if (N->A[x] == d) {
    do {
      y = Convert_AdrToId(Stack_Pop(S));
      N->A[y] = infinite;
      if (x != y) {
        Sets_Assign(&TG->A[y]->U_1.V_1.Class.subclasses, TG->A[x]->U_1.V_1.Class.subclasses);
      }
    } while (!(y == x));
  }
  Sets_ReleaseSet(&X);
}

void Grammar_FixMainClasses
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet nodes;

  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Types_AllNodes(&nodes);
  while (!Sets_IsEmpty(nodes)) {
    FixMainClass((SHORTCARD)Sets_Extract(&nodes));
  }
  Sets_ReleaseSet(&nodes);
}

static void FixMainClass
# ifdef __STDC__
(Idents_tIdent node)
# else
(node)
Idents_tIdent node;
# endif
{
  INTEGER card;
  Idents_tIdent cl;
  Sets_tSet mcl;

  if (Types_Type(node) != Types_cNode) {
    Errors_ERROR((STRING)"FixMainClass: no node", 21L);
  }
  {
    register tNode *W_3 = &TG->A[node]->U_1.V_2.Node;

    card = Sets_Card(&W_3->classes);
    if (card == 0) {
    } else if (card == 1) {
      W_3->mainclass = Sets_Minimum(&W_3->classes);
    } else {
      Sets_MakeSet(&mcl, (Sets_tElement)Scanner_MaxIdent);
      {
        SHORTCARD B_7 = Sets_Minimum(&W_3->classes), B_8 = Sets_Maximum(&W_3->classes);

        if (B_7 <= B_8)
          for (cl = B_7;; cl += 1) {
            if (Sets_IsElement((Sets_tElement)cl, &W_3->classes)) {
              Sets_Exclude(&W_3->classes, (Sets_tElement)cl);
              if (Sets_IsSubset(W_3->classes, TG->A[cl]->U_1.V_1.Class.subclasses)) {
                Sets_Include(&mcl, (Sets_tElement)cl);
              }
              Sets_Include(&W_3->classes, (Sets_tElement)cl);
            }
            if (cl >= B_8) break;
          }
      }
      if (Sets_Card(&mcl) == 1) {
        W_3->mainclass = Sets_Minimum(&mcl);
      }
      Sets_ReleaseSet(&mcl);
    }
  }
}

void Grammar_NodesOfClass
# ifdef __STDC__
(Idents_tIdent class, Sets_tSet *nodes)
# else
(class, nodes)
Idents_tIdent class;
Sets_tSet *nodes;
# endif
{
  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"NodesOfClass: no class", 22L);
  }
  Sets_Assign(nodes, TG->A[class]->U_1.V_1.Class.nodes);
}

void Grammar_ClassesOfNode
# ifdef __STDC__
(Idents_tIdent node, Sets_tSet *classes)
# else
(node, classes)
Idents_tIdent node;
Sets_tSet *classes;
# endif
{
  if (Types_Type(node) != Types_cNode) {
    Errors_ERROR((STRING)"ClassesOfNode: no node", 22L);
  }
  Sets_Assign(classes, TG->A[node]->U_1.V_2.Node.classes);
}

Idents_tIdent Grammar_SuperClass
# ifdef __STDC__
(Idents_tIdent class)
# else
(class)
Idents_tIdent class;
# endif
{
  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"SuperClass: no class", 20L);
  }
  return TG->A[class]->U_1.V_1.Class.superclass;
}

BOOLEAN Grammar_IsSubclass
# ifdef __STDC__
(Idents_tIdent class, Idents_tIdent super)
# else
(class, super)
Idents_tIdent class, super;
# endif
{
  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"IsSubClass: class is no class", 29L);
  }
  if (Types_Type(super) != Types_cClass) {
    Errors_ERROR((STRING)"IsSubClass: super is no class", 29L);
  }
  return Sets_IsElement((Sets_tElement)class, &TG->A[super]->U_1.V_1.Class.subclasses);
}

void Grammar_DirectSubclasses
# ifdef __STDC__
(Idents_tIdent class, Sets_tSet *sub)
# else
(class, sub)
Idents_tIdent class;
Sets_tSet *sub;
# endif
{
  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"DirectSubClass: no class", 24L);
  }
  Sets_Assign(sub, TG->A[class]->U_1.V_1.Class.directsubclasses);
}

void Grammar_Subclasses
# ifdef __STDC__
(Idents_tIdent class, Sets_tSet *sub)
# else
(class, sub)
Idents_tIdent class;
Sets_tSet *sub;
# endif
{
  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"DirectSubClass: no class", 24L);
  }
  Sets_Assign(sub, TG->A[class]->U_1.V_1.Class.subclasses);
}

Idents_tIdent Grammar_MainClass
# ifdef __STDC__
(Idents_tIdent node)
# else
(node)
Idents_tIdent node;
# endif
{
  return TG->A[node]->U_1.V_2.Node.mainclass;
}

void Grammar_SetNodeIdent
# ifdef __STDC__
(Idents_tIdent node, Idents_tIdent id)
# else
(node, id)
Idents_tIdent node, id;
# endif
{
  TG->A[node]->U_1.V_2.Node.nodeident = id;
}

void Grammar_SetArity
# ifdef __STDC__
(Idents_tIdent node, INTEGER ari)
# else
(node, ari)
Idents_tIdent node;
INTEGER ari;
# endif
{
  INTEGER pos;
  LONGINT size;

  {
    register tNode *W_4 = &TG->A[node]->U_1.V_2.Node;

    W_4->arity = ari;
    size = ari + 1;
    DynArray_MakeArray((ADDRESS *)&W_4->sonnames, &size, (LONGINT)sizeof(Grammar_tSon));
    {
      LONGINT B_9 = 0, B_10 = W_4->arity;

      if (B_9 <= B_10)
        for (pos = B_9;; pos += 1) {
          W_4->sonnames->A[pos] = Scanner_NoIdent;
          if (pos >= B_10) break;
        }
    }
  }
  if (ari > vMaxArity) {
    vMaxArity = ari;
  }
}

void Grammar_SetSonName
# ifdef __STDC__
(Idents_tIdent node, INTEGER pos, Idents_tIdent name)
# else
(node, pos, name)
Idents_tIdent node;
INTEGER pos;
Idents_tIdent name;
# endif
{
  TG->A[node]->U_1.V_2.Node.sonnames->A[pos] = name;
}

Grammar_tLayout Grammar_CreateLayout
# ifdef __STDC__
(Idents_tIdent no, Idents_tIdent cl)
# else
(no, cl)
Idents_tIdent no, cl;
# endif
{
  Grammar_tLayout layout;
  LONGINT size;
  INTEGER arity, pos;

  if (Types_Type(no) != Types_cNode) {
    Errors_ERROR((STRING)"CreateLayout: no node", 21L);
  }
  if (Types_Type(cl) != Types_cClass) {
    Errors_ERROR((STRING)"CreateLayout: no class", 22L);
  }
  arity = Grammar_Arity(no);
  layout = (Grammar_tLayout)Heap_Alloc((LONGINT)sizeof(Grammar_tLayoutRec));
  {
    register Grammar_tLayoutRec *W_5 = layout;

    W_5->node = no;
    W_5->class = cl;
    size = arity + 1;
    DynArray_MakeArray((ADDRESS *)&W_5->sons, &size, (LONGINT)sizeof(Grammar_tSon));
    {
      LONGINT B_11 = 0, B_12 = arity;

      if (B_11 <= B_12)
        for (pos = B_11;; pos += 1) {
          W_5->sons->A[pos] = Scanner_NoIdent;
          if (pos >= B_12) break;
        }
    }
  }
  Lists_Append(&TG->A[no]->U_1.V_2.Node.layouts, (ADDRESS)layout);
  Lists_Append(&TG->A[cl]->U_1.V_1.Class.layouts, (ADDRESS)layout);
  return layout;
}

void Grammar_SetSonClass
# ifdef __STDC__
(Grammar_tLayout layout, INTEGER pos, Idents_tIdent class)
# else
(layout, pos, class)
Grammar_tLayout layout;
INTEGER pos;
Idents_tIdent class;
# endif
{
  layout->sons->A[pos] = class;
}

Idents_tIdent Grammar_NodeIdent
# ifdef __STDC__
(Idents_tIdent node)
# else
(node)
Idents_tIdent node;
# endif
{
  return TG->A[node]->U_1.V_2.Node.nodeident;
}

INTEGER Grammar_Arity
# ifdef __STDC__
(Idents_tIdent node)
# else
(node)
Idents_tIdent node;
# endif
{
  return TG->A[node]->U_1.V_2.Node.arity;
}

Idents_tIdent Grammar_SonName
# ifdef __STDC__
(Idents_tIdent node, INTEGER pos)
# else
(node, pos)
Idents_tIdent node;
INTEGER pos;
# endif
{
  return TG->A[node]->U_1.V_2.Node.sonnames->A[pos];
}

Grammar_tLayout Grammar_Layout
# ifdef __STDC__
(Idents_tIdent node, Idents_tIdent class)
# else
(node, class)
Idents_tIdent node, class;
# endif
{
  Lists_tList layouts;
  Grammar_tLayout layout;

  if (Types_Type(node) != Types_cNode) {
    Errors_ERROR((STRING)"Layout: no node", 15L);
  }
  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"Layout: no class", 16L);
  }
  layouts = TG->A[node]->U_1.V_2.Node.layouts;
  for (;;) {
    layout = (Grammar_tLayout)Lists_Head(layouts);
    if (layout->class == class) {
      return layout;
    }
    Lists_Tail(&layouts);
  } EXIT_1:;
}

Idents_tIdent Grammar_SonClass
# ifdef __STDC__
(Grammar_tLayout layout, INTEGER pos)
# else
(layout, pos)
Grammar_tLayout layout;
INTEGER pos;
# endif
{
  return layout->sons->A[pos];
}

void Grammar_MakePatNumbers
# ifdef __STDC__
(INTEGER size)
# else
(size)
INTEGER size;
# endif
{
  Sets_tSet nodes;

  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Types_AllNodes(&nodes);
  while (!Sets_IsEmpty(nodes)) {
    Sets_MakeSet(&TG->A[Sets_Extract(&nodes)]->U_1.V_2.Node.numbers, (Sets_tElement)size);
  }
  Sets_ReleaseSet(&nodes);
}

void Grammar_AddPatNumber
# ifdef __STDC__
(Idents_tIdent node, INTEGER number)
# else
(node, number)
Idents_tIdent node;
INTEGER number;
# endif
{
  Sets_Include(&TG->A[node]->U_1.V_2.Node.numbers, (Sets_tElement)number);
}

void Grammar_PatsOfNode
# ifdef __STDC__
(Idents_tIdent node, Sets_tSet *numbers)
# else
(node, numbers)
Idents_tIdent node;
Sets_tSet *numbers;
# endif
{
  Sets_Assign(numbers, TG->A[node]->U_1.V_2.Node.numbers);
}

INTEGER Grammar_MaxArity
# ifdef __STDC__
()
# else
()
# endif
{
  return vMaxArity;
}

void Grammar_WriteGrammar
# ifdef __STDC__
(IO_tFile f)
# else
(f)
IO_tFile f;
# endif
{
  Idents_tIdent id;

  {
    SHORTCARD B_13 = 1, B_14 = Scanner_MaxIdent;

    if (B_13 <= B_14)
      for (id = B_13;; id += 1) {
        switch (Types_Type(id)) {
        case Types_cClass:;
          {
            register tClass *W_6 = &TG->A[id]->U_1.V_1.Class;

            IO_WriteS(f, (STRING)"class:                ", 22L);
            Idents_WriteIdent(f, id);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  super class:        ", 22L);
            Idents_WriteIdent(f, W_6->superclass);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  nodes:              ", 22L);
            Info_WriteIdentSet(f, W_6->nodes);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  direct sub classes: ", 22L);
            Info_WriteIdentSet(f, W_6->directsubclasses);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  sub classes:        ", 22L);
            Info_WriteIdentSet(f, W_6->subclasses);
            IO_WriteNl(f);
          }
          break;
        case Types_cNode:;
          {
            register tNode *W_7 = &TG->A[id]->U_1.V_2.Node;

            IO_WriteS(f, (STRING)"node:                 ", 22L);
            Idents_WriteIdent(f, id);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  main class:         ", 22L);
            Idents_WriteIdent(f, W_7->mainclass);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  node ident:         ", 22L);
            Idents_WriteIdent(f, W_7->nodeident);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  arity:              ", 22L);
            IO_WriteI(f, W_7->arity, 1L);
            IO_WriteNl(f);
            IO_WriteS(f, (STRING)"  classes:            ", 22L);
            Info_WriteIdentSet(f, W_7->classes);
            IO_WriteNl(f);
          }
          break;
        default :
          break;
        }
        if (id >= B_14) break;
      }
  }
}

void Grammar__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Sets__init();
    IO__init();
    Convert__init();
    Heap__init();
    DynArray__init();
    Idents__init();
    Lists__init();
    Scanner__init();
    Stack__init();
    Sets__init();
    Types__init();
    Errors__init();
    Info__init();
    Idents__init();
    IO__init();
    StdIO__init();
    IO__init();

    vMaxArity = 0;
  }
}
