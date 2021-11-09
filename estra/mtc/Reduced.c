#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Grammar
#include "Grammar.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
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

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Stack
#include "Stack.h"
#endif

#ifndef DEFINITION_Reduced
#include "Reduced.h"
#endif

BOOLEAN Reduced_IsReduced;
Sets_tSet Reduced_UnReachable;
Sets_tSet Reduced_UnDerivable;

#define infinite   10000
static void Reachable ARGS((Sets_tSet StartClasses));
typedef struct S_1 {
    BOOLEAN Done;
    Stack_tStack Pred;
} tClassTask;
typedef struct S_2 {
    INTEGER Count;
    Idents_tIdent Class;
    Idents_tIdent Node;
} tNodeTask;
typedef tClassTask *tClassTaskPtr;
typedef tNodeTask *tNodeTaskPtr;
static struct S_3 {
    tClassTaskPtr A[infinite + 1];
} *ClassArray;
static LONGINT Size;
static Stack_tStack NodeStack;
static Stack_tStack ReadyTasks;
static void Derivable ARGS(());
static void DoTasks ARGS(());
static void MakeClassTasks ARGS(());
static void ReleaseClassTasks ARGS(());
static void MakeNodeTasks ARGS(());
static void CheckClasses ARGS(());
static void CheckNodes ARGS(());


void Reduced_TestReduced
# ifdef __STDC__
(Sets_tSet StartClasses)
# else
(StartClasses)
Sets_tSet StartClasses;
# endif
{
  Reduced_IsReduced = TRUE;
  Sets_MakeSet(&Reduced_UnReachable, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&Reduced_UnDerivable, (Sets_tElement)Scanner_MaxIdent);
  Reachable(StartClasses);
  Derivable();
}

static void Reachable
# ifdef __STDC__
(Sets_tSet StartClasses)
# else
(StartClasses)
Sets_tSet StartClasses;
# endif
{
  Sets_tSet UnReached, Pending, Classes, Nodes;
  Idents_tIdent node, class, sonclass;
  Grammar_tLayout layout;
  INTEGER pos;

  Sets_MakeSet(&UnReached, (Sets_tElement)Scanner_MaxIdent);
  Types_AllClasses(&UnReached);
  Sets_MakeSet(&Pending, (Sets_tElement)Scanner_MaxIdent);
  Sets_Union(&Pending, StartClasses);
  Sets_MakeSet(&Classes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&Nodes, (Sets_tElement)Scanner_MaxIdent);
  Sets_Difference(&UnReached, Pending);
  while (!Sets_IsEmpty(Pending)) {
    class = Sets_Extract(&Pending);
    Grammar_NodesOfClass(class, &Nodes);
    while (!Sets_IsEmpty(Nodes)) {
      node = Sets_Extract(&Nodes);
      if (Grammar_Arity(node) != Scanner_NoValue) {
        layout = Grammar_Layout(node, class);
        {
          LONGINT B_1 = 1, B_2 = Grammar_Arity(node);

          if (B_1 <= B_2)
            for (pos = B_1;; pos += 1) {
              sonclass = Grammar_SonClass(layout, pos);
              if (Sets_IsElement((Sets_tElement)sonclass, &UnReached)) {
                Sets_Exclude(&UnReached, (Sets_tElement)sonclass);
                Sets_Include(&Pending, (Sets_tElement)sonclass);
              }
              if (pos >= B_2) break;
            }
        }
      }
    }
    Grammar_Subclasses(class, &Classes);
    Sets_Intersection(&Classes, UnReached);
    Sets_Difference(&UnReached, Classes);
    Sets_Union(&Pending, Classes);
  }
  if (!Sets_IsEmpty(UnReached)) {
    Reduced_IsReduced = FALSE;
    Sets_Assign(&Reduced_UnReachable, UnReached);
  }
  Sets_ReleaseSet(&Classes);
  Sets_ReleaseSet(&Nodes);
  Sets_ReleaseSet(&UnReached);
  Sets_ReleaseSet(&Pending);
}

static void Derivable
# ifdef __STDC__
()
# else
()
# endif
{
  Stack_MakeStack(&ReadyTasks);
  MakeClassTasks();
  MakeNodeTasks();
  DoTasks();
  CheckClasses();
  CheckNodes();
  ReleaseClassTasks();
  Stack_ReleaseStack(&ReadyTasks);
}

static void DoTasks
# ifdef __STDC__
()
# else
()
# endif
{
  tNodeTaskPtr NodeTask;
  Idents_tIdent class;
  Idents_tIdent start;

  while (!Stack_IsEmptyStack(ReadyTasks)) {
    NodeTask = (tNodeTaskPtr)Stack_Pop(&ReadyTasks);
    class = NodeTask->Class;
    start = class;
    for (;;) {
      {
        register tClassTask *W_1 = ClassArray->A[class];

        if (!W_1->Done) {
          while (!Stack_IsEmptyStack(W_1->Pred)) {
            NodeTask = (tNodeTaskPtr)Stack_Pop(&W_1->Pred);
            {
              register tNodeTask *W_2 = NodeTask;

              DEC(W_2->Count);
              if (W_2->Count == 0) {
                Stack_Push(&ReadyTasks, (ADDRESS)NodeTask);
              }
            }
          }
          W_1->Done = TRUE;
        }
        class = Grammar_SuperClass(class);
        if (class == Scanner_NoIdent || class == start) {
          goto EXIT_1;
        }
      }
    } EXIT_1:;
  }
}

static void MakeClassTasks
# ifdef __STDC__
()
# else
()
# endif
{
  Idents_tIdent class;
  Sets_tSet Classes;

  Sets_MakeSet(&Classes, (Sets_tElement)Scanner_MaxIdent);
  Types_AllClasses(&Classes);
  Size = Scanner_MaxIdent + 1;
  DynArray_MakeArray((ADDRESS *)&ClassArray, &Size, (LONGINT)sizeof(tClassTaskPtr));
  while (!Sets_IsEmpty(Classes)) {
    class = Sets_Extract(&Classes);
    ClassArray->A[class] = (tClassTaskPtr)Memory_Alloc((LONGINT)sizeof(tClassTask));
    {
      register tClassTask *W_3 = ClassArray->A[class];

      W_3->Done = FALSE;
      Stack_MakeStack(&W_3->Pred);
    }
  }
  Sets_ReleaseSet(&Classes);
}

static void ReleaseClassTasks
# ifdef __STDC__
()
# else
()
# endif
{
  Idents_tIdent class;
  Sets_tSet Classes;

  Sets_MakeSet(&Classes, (Sets_tElement)Scanner_MaxIdent);
  Types_AllClasses(&Classes);
  while (!Sets_IsEmpty(Classes)) {
    class = Sets_Extract(&Classes);
    Stack_ReleaseStack(&ClassArray->A[class]->Pred);
    Memory_Free((LONGINT)sizeof(tClassTask), (ADDRESS)ClassArray->A[class]);
  }
  DynArray_ReleaseArray((ADDRESS *)&ClassArray, &Size, (LONGINT)sizeof(tClassTaskPtr));
  Sets_ReleaseSet(&Classes);
}

static void MakeNodeTasks
# ifdef __STDC__
()
# else
()
# endif
{
  tNodeTaskPtr NodeTask;
  Sets_tSet Nodes, Classes;
  Grammar_tLayout layout;
  Idents_tIdent sonclass, class, node;
  INTEGER pos;

  Stack_MakeStack(&NodeStack);
  Sets_MakeSet(&Nodes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&Classes, (Sets_tElement)Scanner_MaxIdent);
  Types_AllClasses(&Classes);
  while (!Sets_IsEmpty(Classes)) {
    class = Sets_Extract(&Classes);
    Grammar_NodesOfClass(class, &Nodes);
    while (!Sets_IsEmpty(Nodes)) {
      node = Sets_Extract(&Nodes);
      if (Grammar_Arity(node) != Scanner_NoValue) {
        layout = Grammar_Layout(node, class);
        NodeTask = (tNodeTaskPtr)Memory_Alloc((LONGINT)sizeof(tNodeTask));
        {
          register tNodeTask *W_4 = NodeTask;

          W_4->Count = Grammar_Arity(node);
          W_4->Class = class;
          W_4->Node = node;
        }
        if (Grammar_Arity(node) == 0) {
          Stack_Push(&ReadyTasks, (ADDRESS)NodeTask);
        }
        {
          LONGINT B_3 = 1, B_4 = Grammar_Arity(node);

          if (B_3 <= B_4)
            for (pos = B_3;; pos += 1) {
              sonclass = Grammar_SonClass(layout, pos);
              if (sonclass != Scanner_NoIdent) {
                Stack_Push(&ClassArray->A[sonclass]->Pred, (ADDRESS)NodeTask);
              }
              if (pos >= B_4) break;
            }
        }
        Stack_Push(&NodeStack, (ADDRESS)NodeTask);
      }
    }
  }
  Sets_ReleaseSet(&Classes);
  Sets_ReleaseSet(&Nodes);
}

static void CheckClasses
# ifdef __STDC__
()
# else
()
# endif
{
  Idents_tIdent class;
  Sets_tSet Classes;

  Sets_MakeSet(&Classes, (Sets_tElement)Scanner_MaxIdent);
  while (!Sets_IsEmpty(Classes)) {
    class = Sets_Extract(&Classes);
    {
      register tClassTask *W_5 = ClassArray->A[class];

      if (!W_5->Done) {
        Sets_Include(&Reduced_UnDerivable, (Sets_tElement)class);
      }
    }
  }
  Sets_ReleaseSet(&Classes);
}

static void CheckNodes
# ifdef __STDC__
()
# else
()
# endif
{
  Stack_tStack Nodes;
  tNodeTaskPtr NodeTask;

  Stack_MakeStack(&Nodes);
  Stack_Assign(&Nodes, NodeStack);
  while (!Stack_IsEmptyStack(Nodes)) {
    NodeTask = (tNodeTaskPtr)Stack_Pop(&Nodes);
    {
      register tNodeTask *W_6 = NodeTask;

      if (W_6->Count > 0) {
      }
    }
  }
  Stack_ReleaseStack(&Nodes);
}

void Reduced__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Sets__init();
    DynArray__init();
    Grammar__init();
    Errors__init();
    Idents__init();
    Memory__init();
    Scanner__init();
    Sets__init();
    Stack__init();
    Types__init();
    Lists__init();
    Stack__init();

    Reduced_IsReduced = FALSE;
  }
}
