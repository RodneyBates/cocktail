#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_Queue
#include "Queue.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Optimize
#include "Optimize.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_Queue
#include "Queue.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Order
#include "Order.h"
#endif

struct Order_1 *Order_IndexToClass;
IO_tFile Order_yyf;
PROC Order_Exit;

#define GrammarIsInNormalForm   50
#define GrammarIsNotInNormalForm   51
#define SwitchedOnOptionL   52
#define GrammarIsSAG   53
#define GrammarIsLAG   54
#define GrammarIsOAG   55
#define GrammarIsDNC   56
#define GrammarIsSNC   57
#define GrammarIsWAG   58
#define GrammarIsNotWAG   59
#define CycleInSNC   60
#define CycleInDNC   61
#define CycleInOAG   62
#define InternalErrorCompOAG   63
#define CycleInWAG   64
static Sets_tSet HasCycle, Children, Parents, Relevant, Cyclics, IsComputed, IsComputable;
static SHORTCARD Prio, UserIndex, ClassCount, Kind, i, i2, j, k, n, Visit;
static BOOLEAN Reporting, Success, Stable;
static Tree_tTree ActClass, UserClass, ChildsClass;
static Tree_tInstance AttrInstance;
static LONGINT IndexSize;
static BOOLEAN IsComputable3a ARGS((SHORTCARD i, Tree_tTree t));
static BOOLEAN IsComputable3b ARGS((SHORTCARD i, Tree_tTree t));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
static void CompIndex ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void CompIndexToClass ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void CompUsers ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void CompSNC1 ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void CompSNC2 ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void CompDNC1 ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void CompDNC2 ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG0a ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG0b ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG0c ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG0d ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG0e ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG1 ARGS((Tree_tTree t));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG2 ARGS((Tree_tTree t));
struct S_17 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG3a ARGS((Tree_tTree t));
struct S_18 {
    union {
        char dummy;
    } U_1;
};
static void CompOAG3b ARGS((Tree_tTree t));
struct S_19 {
    union {
        char dummy;
    } U_1;
};
struct S_20 {
    union {
        char dummy;
    } U_1;
};
struct S_21 {
    union {
        char dummy;
    } U_1;
};
struct S_22 {
    union {
        char dummy;
    } U_1;
};
static void CheckNormalForm ARGS((Tree_tTree t));
struct S_23 {
    union {
        char dummy;
    } U_1;
};
static void CheckLAG ARGS((Tree_tTree t));
struct S_24 {
    union {
        char dummy;
    } U_1;
};
static void CheckSAG ARGS((Tree_tTree t));
struct S_25 {
    union {
        char dummy;
    } U_1;
};
static void InitWAG ARGS((Tree_tTree t));
struct S_26 {
    union {
        char dummy;
    } U_1;
};
static void CheckWAG0 ARGS((Tree_tTree t));
struct S_27 {
    union {
        char dummy;
    } U_1;
};
static void CheckWAG1 ARGS((Tree_tTree t));
struct S_28 {
    union {
        struct {
            struct S_29 {
                Relations_tRelation C_0_A;
            } yyR1;
        } V_1;
    } U_1;
};
static void CheckWAG2 ARGS((Tree_tTree t));
struct S_30 {
    union {
        struct {
            struct S_31 {
                Relations_tRelation C_0_A;
            } yyR1;
        } V_1;
    } U_1;
};
static void CheckWAG3 ARGS((Tree_tTree yyP2, Relations_tRelation yyP1));
struct S_32 {
    union {
        char dummy;
    } U_1;
};
static void CheckWAG4 ARGS((Tree_tTree yyP6, Relations_tRelation yyP5, Tree_tTree yyP4, Tree_tTree yyP3));
struct S_33 {
    union {
        struct {
            struct S_34 {
                Relations_tRelation B;
                Tree_tSetOfRelPtr ActD;
            } yyR1;
        } V_1;
    } U_1;
};
static void CheckWAG5 ARGS((Tree_tTree t, Relations_tRelation yyP7));
typedef Tree_tSetOfRelPtr *tSetOfRelPtrPtr;
struct S_35 {
    union {
        struct {
            struct S_36 {
                Relations_tRelation B;
                Tree_tSetOfRelPtr ActD;
                tSetOfRelPtrPtr LastNext;
            } yyR1;
        } V_1;
    } U_1;
};
static void yyExit ARGS(());


static BOOLEAN IsComputable3a
# ifdef __STDC__
(SHORTCARD i, Tree_tTree t)
# else
(i, t)
SHORTCARD i;
Tree_tTree t;
# endif
{
  SHORTCARD j;

  {
    register Tree_yClass *W_1 = &t->U_1.V_5.Class;

    {
      SHORTCARD B_1 = 1, B_2 = W_1->InstCount;

      if (B_1 <= B_2)
        for (j = B_1;; j += 1) {
          if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_1->OAG) && !Sets_IsElement((Sets_tElement)j, &IsComputed)) {
            return FALSE;
          }
          if (j >= B_2) break;
        }
    }
    return TRUE;
  }
}

static BOOLEAN IsComputable3b
# ifdef __STDC__
(SHORTCARD i, Tree_tTree t)
# else
(i, t)
SHORTCARD i;
Tree_tTree t;
# endif
{
  SHORTCARD j;

  {
    register Tree_yClass *W_2 = &t->U_1.V_5.Class;

    if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right), W_2->Instance->A[i - 1].Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_2->Instance->A[i - 1].Properties)) {
      {
        SHORTCARD B_3 = 1, B_4 = W_2->InstCount;

        if (B_3 <= B_4)
          for (j = B_3;; j += 1) {
            if (IN(Tree_First, W_2->Instance->A[j - 1].Properties) && Relations_IsRelated((LONGINT)j, (LONGINT)i, W_2->OAG) && !Sets_IsElement((Sets_tElement)j, &IsComputed)) {
              return FALSE;
            }
            if (j >= B_4) break;
          }
      }
    } else {
      {
        SHORTCARD B_5 = 1, B_6 = W_2->InstCount;

        if (B_5 <= B_6)
          for (j = B_5;; j += 1) {
            if (Relations_IsRelated((LONGINT)j, (LONGINT)i, W_2->OAG) && !Sets_IsElement((Sets_tElement)j, &IsComputed)) {
              return FALSE;
            }
            if (j >= B_6) break;
          }
      }
    }
    return TRUE;
  }
}

static void yyAbort
# ifdef __STDC__
(CHAR yyFunction[], LONGCARD O_1)
# else
(yyFunction, O_1)
CHAR yyFunction[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yyFunction, O_1, CHAR)
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Order, routine ", 29L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Order_Exit)();
  FREE_OPEN_ARRAYS
}

static BOOLEAN yyIsEqual
# ifdef __STDC__
(BYTE yya[], LONGCARD O_3, BYTE yyb[], LONGCARD O_2)
# else
(yya, O_3, yyb, O_2)
BYTE yya[];
LONGCARD O_3;
BYTE yyb[];
LONGCARD O_2;
# endif
{
  INTEGER yyi;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(WORD) + O_3 * sizeof(WORD), 2)
  COPY_OPEN_ARRAY(yyb, O_2, WORD)
  COPY_OPEN_ARRAY(yya, O_3, WORD)
  {
    LONGINT B_7 = 0, B_8 = (INTEGER)(O_3 - 1);

    if (B_7 <= B_8)
      for (yyi = B_7;; yyi += 1) {
        if (yya[yyi] != yyb[yyi]) {
          FREE_OPEN_ARRAYS
          return FALSE;
        }
        if (yyi >= B_8) break;
      }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

void Order_Order
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_3 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Ag:;
    {
      register Tree_yAg *W_3 = &t->U_1.V_26.Ag;

      Order_Order(W_3->Classes);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_4 = &t->U_1.V_5.Class;

      Success = TRUE;
      Tree_ForallClasses(t, (Tree_ProcOfT)CheckNormalForm);
      if (Success) {
        Tree_Information((LONGINT)GrammarIsInNormalForm, t->U_1.V_5.Class.Pos);
      } else {
        Tree_Information((LONGINT)GrammarIsNotInNormalForm, t->U_1.V_5.Class.Pos);
      }
      if (IN(Tree_cLNC, Tree_GrammarClass)) {
        Tree_ForallClasses(t, (Tree_ProcOfT)CompIndex);
        IndexSize = ClassCount + 1;
        DynArray_MakeArray((ADDRESS *)&Order_IndexToClass, &IndexSize, (LONGINT)sizeof(Tree_tTree));
        Queue_MakeQueue(ClassCount);
        Sets_MakeSet(&HasCycle, (Sets_tElement)ClassCount);
        Tree_ForallClasses(t, (Tree_ProcOfT)CompIndexToClass);
        Tree_ForallClasses(t, (Tree_ProcOfT)CompUsers);
        while (!Queue_IsEmpty()) {
          ActClass = Order_IndexToClass->A[Queue_Dequeue()];
          Relations_Closure(&ActClass->U_1.V_5.Class.SNC);
          CompSNC1(ActClass->U_1.V_5.Class.BaseClass);
          {
            SHORTCARD B_9 = Sets_Minimum(&ActClass->U_1.V_5.Class.Users), B_10 = Sets_Maximum(&ActClass->U_1.V_5.Class.Users);

            if (B_9 <= B_10)
              for (UserIndex = B_9;; UserIndex += 1) {
                if (Sets_IsElement((Sets_tElement)UserIndex, &ActClass->U_1.V_5.Class.Users)) {
                  UserClass = Order_IndexToClass->A[UserIndex];
                  Tree_ForallAttributes(UserClass, (Tree_ProcOfT)CompSNC1);
                }
                if (UserIndex >= B_10) break;
              }
          }
        }
        Tree_ForallClasses(t, (Tree_ProcOfT)CompSNC2);
        if (Sets_IsEmpty(HasCycle)) {
          INCL(Tree_GrammarClass, Tree_cSNC);
        } else if (!Sets_IsElement(ORD('L'), &Tree_Options)) {
          Tree_Information((LONGINT)SwitchedOnOptionL, t->U_1.V_5.Class.Pos);
          Sets_Include(&Tree_Options, ORD('L'));
        }
        if (IN(Tree_cSNC, Tree_GrammarClass)) {
          while (!Queue_IsEmpty()) {
            ActClass = Order_IndexToClass->A[Queue_Dequeue()];
            Relations_Closure(&ActClass->U_1.V_5.Class.DNC);
            Tree_ForallClasses(ActClass->U_1.V_5.Class.Extensions, (Tree_ProcOfT)CompDNC1);
            Tree_ForallAttributes(ActClass, (Tree_ProcOfT)CompDNC1);
          }
          Queue_ReleaseQueue();
          Success = TRUE;
          Tree_ForallClasses(t, (Tree_ProcOfT)CompDNC2);
          if (Success) {
            INCL(Tree_GrammarClass, Tree_cDNC);
          } else if (!Sets_IsElement(ORD('L'), &Tree_Options)) {
            Tree_Information((LONGINT)SwitchedOnOptionL, t->U_1.V_5.Class.Pos);
            Sets_Include(&Tree_Options, ORD('L'));
          }
          if (IN(Tree_cDNC, Tree_GrammarClass)) {
            if (Sets_IsElement(ORD('/'), &Tree_Options)) {
              Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG0a);
            } else {
              Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG0b);
              Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG0c);
              Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG0d);
            }
            Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG1);
            Success = TRUE;
            Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG2);
            if (Success) {
              INCL(Tree_GrammarClass, Tree_cOAG);
            } else if (!Sets_IsElement(ORD('L'), &Tree_Options)) {
              Tree_Information((LONGINT)SwitchedOnOptionL, t->U_1.V_5.Class.Pos);
              Sets_Include(&Tree_Options, ORD('L'));
            }
            if (IN(Tree_cOAG, Tree_GrammarClass)) {
              if (!Sets_IsElement(ORD('L'), &Tree_Options)) {
                if (Sets_IsElement(ORD('/'), &Tree_Options)) {
                  Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG3a);
                } else {
                  Tree_ForallClasses(t, (Tree_ProcOfT)CompOAG3b);
                }
                if (Sets_IsElement(ORD('0'), &Tree_Options)) {
                  Tree_ForallClasses(t, (Tree_ProcOfT)Optimize_LifeTime1);
                  if (Sets_IsElement(ORD('3'), &Tree_Options)) {
                    IO_WriteNl((System_tFile)IO_StdOutput);
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Storage Assignment", 28L);
                    IO_WriteNl((System_tFile)IO_StdOutput);
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"----------------------------", 28L);
                    IO_WriteNl((System_tFile)IO_StdOutput);
                    IO_WriteNl((System_tFile)IO_StdOutput);
                    Optimize_ChildrenDyn = 0;
                    Optimize_ChildrenIn = 0;
                    Optimize_AttributeIn = 0;
                    Optimize_AttributeOut = 0;
                    Optimize_AttributeTree = 0;
                    Optimize_AttributeParam = 0;
                    Optimize_AttributeVar = 0;
                    Optimize_AttributeDemand = 0;
                    Optimize_AttributeStack = 0;
                  }
                  Tree_ForallClasses(t, (Tree_ProcOfT)Optimize_LifeTime3);
                  if (Sets_IsElement(ORD('3'), &Tree_Options)) {
                    IO_WriteNl((System_tFile)IO_StdOutput);
                    if (Optimize_ChildrenIn > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Children  Input          ", 25L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_ChildrenIn, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_ChildrenDyn > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Children  Dynamic        ", 25L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_ChildrenDyn, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_AttributeIn > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Input          ", 25L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_AttributeIn, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_AttributeOut > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Output ", 17L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_AttributeOut, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_AttributeTree > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Tree           ", 25L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_AttributeTree, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_AttributeParam > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Parameter      ", 25L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_AttributeParam, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_AttributeVar > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Variable       ", 25L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_AttributeVar, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_AttributeDemand > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Demand ", 17L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_AttributeDemand, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    if (Optimize_AttributeStack > 0) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Stack  ", 17L);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Optimize_AttributeStack, 3L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                  }
                }
              }
              Success = TRUE;
              Tree_ForallClasses(t, (Tree_ProcOfT)CheckLAG);
              if (Success) {
                INCL(Tree_GrammarClass, Tree_cLAG);
              }
              if (IN(Tree_cLAG, Tree_GrammarClass)) {
                Success = TRUE;
                Tree_ForallClasses(t, (Tree_ProcOfT)CheckSAG);
                if (Success) {
                  INCL(Tree_GrammarClass, Tree_cSAG);
                }
                if (IN(Tree_cSAG, Tree_GrammarClass)) {
                  Tree_Information((LONGINT)GrammarIsSAG, t->U_1.V_5.Class.Pos);
                } else {
                  Tree_Information((LONGINT)GrammarIsLAG, t->U_1.V_5.Class.Pos);
                }
              } else {
                Tree_Information((LONGINT)GrammarIsOAG, t->U_1.V_5.Class.Pos);
              }
            } else {
              Tree_Information((LONGINT)GrammarIsDNC, t->U_1.V_5.Class.Pos);
            }
          } else {
            Tree_Information((LONGINT)GrammarIsSNC, t->U_1.V_5.Class.Pos);
          }
        } else {
          Queue_ReleaseQueue();
          Queue_MakeQueue(ClassCount);
          Sets_MakeSet(&Relevant, (Sets_tElement)ClassCount);
          Sets_MakeSet(&Cyclics, (Sets_tElement)ClassCount);
          Sets_Assign(&Cyclics, HasCycle);
          while (!Sets_IsEmpty(Cyclics)) {
            InitWAG(Order_IndexToClass->A[Sets_Extract(&Cyclics)]);
          }
          Reporting = FALSE;
          while (!Sets_IsEmpty(HasCycle)) {
            CheckWAG0(Order_IndexToClass->A[Sets_Extract(&HasCycle)]);
          }
          Sets_ReleaseSet(&Cyclics);
          while (!Queue_IsEmpty()) {
            CheckWAG2(Order_IndexToClass->A[Queue_Dequeue()]);
          }
          if (Sets_IsEmpty(HasCycle)) {
            INCL(Tree_GrammarClass, Tree_cWAG);
            Tree_Information((LONGINT)GrammarIsWAG, t->U_1.V_5.Class.Pos);
          } else {
            Reporting = TRUE;
            while (!Sets_IsEmpty(HasCycle)) {
              CheckWAG2(Order_IndexToClass->A[Sets_Extract(&HasCycle)]);
            }
            Tree_Information((LONGINT)GrammarIsNotWAG, t->U_1.V_5.Class.Pos);
          }
          Sets_ReleaseSet(&HasCycle);
          Queue_ReleaseQueue();
        }
      } else {
        Tree_Information((LONGINT)GrammarIsNotWAG, t->U_1.V_5.Class.Pos);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CompIndex
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_4 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      INC(ClassCount);
      W_5->Index = ClassCount;
      Relations_MakeRelation(&W_5->SNC, (LONGINT)W_5->InstCount, (LONGINT)W_5->InstCount);
      Relations_Assign(&W_5->SNC, W_5->DP);
      return;
    }
  }
}

static void CompIndexToClass
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_6 = &t->U_1.V_5.Class;

      Order_IndexToClass->A[W_6->Index] = t;
      Sets_MakeSet(&W_6->Users, (Sets_tElement)ClassCount);
      Queue_Enqueue(W_6->Index);
      return;
    }
  }
}

static void CompUsers
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_6 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_7 = &t->U_1.V_5.Class;

      ActClass = t;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CompUsers);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_8 = &t->U_1.V_9.Child;

      ChildsClass = W_8->Class;
      if (ChildsClass != Tree_NoTree) {
        Sets_Include(&ChildsClass->U_1.V_5.Class.Users, (Sets_tElement)ActClass->U_1.V_5.Class.Index);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CompSNC1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_7 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_9 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_11 = 1, B_12 = W_9->AttrCount;

        if (B_11 <= B_12)
          for (i = B_11;; i += 1) {
            {
              SHORTCARD B_13 = 1, B_14 = W_9->AttrCount;

              if (B_13 <= B_14)
                for (j = B_13;; j += 1) {
                  if (Relations_IsRelated((LONGINT)i, (LONGINT)j, ActClass->U_1.V_5.Class.SNC)) {
                    if (!Relations_IsRelated((LONGINT)i, (LONGINT)j, W_9->SNC)) {
                      Relations_Include(&W_9->SNC, (LONGINT)i, (LONGINT)j);
                      Queue_Enqueue(W_9->Index);
                    }
                  }
                  if (j >= B_14) break;
                }
            }
            if (i >= B_12) break;
          }
      }
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_10 = &t->U_1.V_9.Child;

        if (!(W_10->Class != Tree_NoTree)) {
          goto EXIT_1;
        }
        ChildsClass = W_10->Class;
        if (!(ChildsClass == ActClass || Queue_IsElement(ChildsClass->U_1.V_5.Class.Index))) {
          goto EXIT_1;
        }
        {
          SHORTCARD B_15 = 1, B_16 = ChildsClass->U_1.V_5.Class.AttrCount;

          if (B_15 <= B_16)
            for (i = B_15;; i += 1) {
              {
                SHORTCARD B_17 = 1, B_18 = ChildsClass->U_1.V_5.Class.AttrCount;

                if (B_17 <= B_18)
                  for (j = B_17;; j += 1) {
                    if (Relations_IsRelated((LONGINT)i, (LONGINT)j, ChildsClass->U_1.V_5.Class.SNC)) {
                      if (!Relations_IsRelated((LONGINT)(UserClass->U_1.V_5.Class.AttrCount + W_10->InstOffset + i), (LONGINT)(UserClass->U_1.V_5.Class.AttrCount + W_10->InstOffset + j), UserClass->U_1.V_5.Class.SNC)) {
                        Relations_Include(&UserClass->U_1.V_5.Class.SNC, (LONGINT)(UserClass->U_1.V_5.Class.AttrCount + W_10->InstOffset + i), (LONGINT)(UserClass->U_1.V_5.Class.AttrCount + W_10->InstOffset + j));
                        Queue_Enqueue(UserClass->U_1.V_5.Class.Index);
                      }
                    }
                    if (j >= B_18) break;
                  }
              }
              if (i >= B_16) break;
            }
        }
        return;
      }
    } EXIT_1:;
    break;
  default :
    break;
  }
}

static void CompSNC2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_8 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_11 = &t->U_1.V_5.Class;

      if (Relations_HasReflexive(W_11->SNC)) {
        if (!Sets_IsElement(ORD('L'), &Tree_Options)) {
          Tree_WarningI((LONGINT)CycleInSNC, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_11->Name));
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Dependencies SNC", 26L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteNl((System_tFile)IO_StdOutput);
          Tree_WriteDependencies(t, W_11->SNC, Tree_MaxSet);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Cyclic Attributes", 17L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteNl((System_tFile)IO_StdOutput);
          Sets_MakeSet(&Cyclics, (Sets_tElement)W_11->InstCount);
          Relations_GetCyclics(W_11->SNC, &Cyclics);
          Tree_WriteCyclics(t, Cyclics);
          IO_WriteNl((System_tFile)IO_StdOutput);
          Sets_ReleaseSet(&Cyclics);
        }
        Sets_Include(&HasCycle, (Sets_tElement)W_11->Index);
      }
      if (Sets_IsElement(ORD('S'), &Tree_Options)) {
        Tree_WriteDependencies(t, W_11->SNC, Tree_MaxSet);
      }
      Relations_MakeRelation(&W_11->DNC, (LONGINT)W_11->InstCount, (LONGINT)W_11->InstCount);
      Relations_Assign(&W_11->DNC, W_11->SNC);
      Queue_Enqueue(W_11->Index);
      return;
    }
  }
}

static void CompDNC1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_9 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_12 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_19 = 1, B_20 = ActClass->U_1.V_5.Class.AttrCount;

        if (B_19 <= B_20)
          for (i = B_19;; i += 1) {
            {
              SHORTCARD B_21 = 1, B_22 = ActClass->U_1.V_5.Class.AttrCount;

              if (B_21 <= B_22)
                for (j = B_21;; j += 1) {
                  if (Relations_IsRelated((LONGINT)i, (LONGINT)j, ActClass->U_1.V_5.Class.DNC)) {
                    if (!Relations_IsRelated((LONGINT)i, (LONGINT)j, W_12->DNC)) {
                      Relations_Include(&W_12->DNC, (LONGINT)i, (LONGINT)j);
                      Queue_Enqueue(W_12->Index);
                    }
                  }
                  if (j >= B_22) break;
                }
            }
            if (i >= B_20) break;
          }
      }
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_13 = &t->U_1.V_9.Child;

        if (!(W_13->Class != Tree_NoTree)) {
          goto EXIT_2;
        }
        ChildsClass = W_13->Class;
        {
          SHORTCARD B_23 = 1, B_24 = ChildsClass->U_1.V_5.Class.AttrCount;

          if (B_23 <= B_24)
            for (i = B_23;; i += 1) {
              {
                SHORTCARD B_25 = 1, B_26 = ChildsClass->U_1.V_5.Class.AttrCount;

                if (B_25 <= B_26)
                  for (j = B_25;; j += 1) {
                    if (Relations_IsRelated((LONGINT)(ActClass->U_1.V_5.Class.AttrCount + W_13->InstOffset + i), (LONGINT)(ActClass->U_1.V_5.Class.AttrCount + W_13->InstOffset + j), ActClass->U_1.V_5.Class.DNC)) {
                      if (!Relations_IsRelated((LONGINT)i, (LONGINT)j, ChildsClass->U_1.V_5.Class.DNC)) {
                        Relations_Include(&ChildsClass->U_1.V_5.Class.DNC, (LONGINT)i, (LONGINT)j);
                        Queue_Enqueue(ChildsClass->U_1.V_5.Class.Index);
                      }
                    }
                    if (j >= B_26) break;
                  }
              }
              if (i >= B_24) break;
            }
        }
        return;
      }
    } EXIT_2:;
    break;
  default :
    break;
  }
}

static void CompDNC2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_10 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_14 = &t->U_1.V_5.Class;

      if (Relations_HasReflexive(W_14->DNC)) {
        if (!Sets_IsElement(ORD('L'), &Tree_Options)) {
          Tree_WarningI((LONGINT)CycleInDNC, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_14->Name));
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Dependencies DNC", 26L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteNl((System_tFile)IO_StdOutput);
          Tree_WriteDependencies(t, W_14->DNC, Tree_MaxSet);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Cyclic Attributes", 17L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteNl((System_tFile)IO_StdOutput);
          Sets_MakeSet(&Cyclics, (Sets_tElement)W_14->InstCount);
          Relations_GetCyclics(W_14->DNC, &Cyclics);
          Tree_WriteCyclics(t, Cyclics);
          IO_WriteNl((System_tFile)IO_StdOutput);
          Sets_ReleaseSet(&Cyclics);
        }
        Success = FALSE;
      }
      if (Sets_IsElement(ORD('N'), &Tree_Options)) {
        Tree_WriteDependencies(t, W_14->DNC, Tree_MaxSet);
      }
      Relations_MakeRelation(&W_14->OAG, (LONGINT)W_14->InstCount, (LONGINT)W_14->InstCount);
      Relations_Assign(&W_14->OAG, W_14->DNC);
      return;
    }
  }
}

static void CompOAG0a
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_11 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_15 = &t->U_1.V_5.Class;

      ActClass = t;
      if (W_15->BaseClass->U_1.V_1.Kind == Tree_Class) {
        n = W_15->BaseClass->U_1.V_5.Class.AttrCount;
      } else {
        n = 0;
      }
      k = 0;
      do {
        INC(k);
        do {
          Stable = TRUE;
          Kind = Tree_Inherited;
          Tree_ForallAttributes(W_15->Attributes, (Tree_ProcOfT)CompOAG0a);
        } while (!Stable);
        do {
          Stable = TRUE;
          Kind = Tree_Synthesized;
          Tree_ForallAttributes(W_15->Attributes, (Tree_ProcOfT)CompOAG0a);
        } while (!Stable);
      } while (!(n == W_15->AttrCount));
      if (W_15->BaseClass->U_1.V_1.Kind == Tree_Class && W_15->BaseClass->U_1.V_5.Class.Visits > k) {
        k = W_15->BaseClass->U_1.V_5.Class.Visits;
      }
      W_15->Visits = k;
      if (Tree_MaxVisit < k) {
        Tree_MaxVisit = k;
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_16 = &t->U_1.V_9.Child;

      if (W_16->Partition == 9999) {
        if (IN(Tree_Input, W_16->Properties) || (W_16->Properties & (SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Synthesized))) == 0X0L) {
          W_16->Partition = 0;
          INC(n);
          return;
        }
        if (IN(Kind, W_16->Properties)) {
          {
            SHORTCARD B_27 = 1, B_28 = ActClass->U_1.V_5.Class.AttrCount;

            if (B_27 <= B_28)
              for (i = B_27;; i += 1) {
                if (Relations_IsRelated((LONGINT)W_16->AttrIndex, (LONGINT)i, ActClass->U_1.V_5.Class.OAG) && ActClass->U_1.V_5.Class.Instance->A[i - 1].Attribute->U_1.V_9.Child.Partition > k) {
                  return;
                }
                if (i >= B_28) break;
              }
          }
          W_16->Partition = k;
          INC(n);
          Stable = FALSE;
        }
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_17 = &t->U_1.V_10.Attribute;

      if (W_17->Partition == 9999) {
        if (IN(Tree_Input, W_17->Properties) || (W_17->Properties & (SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Synthesized))) == 0X0L) {
          W_17->Partition = 0;
          INC(n);
          return;
        }
        if (IN(Kind, W_17->Properties)) {
          {
            SHORTCARD B_29 = 1, B_30 = ActClass->U_1.V_5.Class.AttrCount;

            if (B_29 <= B_30)
              for (i = B_29;; i += 1) {
                if (Relations_IsRelated((LONGINT)W_17->AttrIndex, (LONGINT)i, ActClass->U_1.V_5.Class.OAG) && ActClass->U_1.V_5.Class.Instance->A[i - 1].Attribute->U_1.V_10.Attribute.Partition > k) {
                  return;
                }
                if (i >= B_30) break;
              }
          }
          W_17->Partition = k;
          INC(n);
          Stable = FALSE;
        }
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CompOAG0b
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_12 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_18 = &t->U_1.V_5.Class;

      ActClass = t;
      if (W_18->BaseClass->U_1.V_1.Kind == Tree_Class) {
        n = W_18->BaseClass->U_1.V_5.Class.AttrCount;
      } else {
        n = 0;
      }
      k = 0;
      do {
        INC(k);
        do {
          Kind = Tree_Synthesized;
          Stable = TRUE;
          Tree_ForallAttributes(W_18->Attributes, (Tree_ProcOfT)CompOAG0b);
        } while (!Stable);
        do {
          Stable = TRUE;
          Kind = Tree_Inherited;
          Tree_ForallAttributes(W_18->Attributes, (Tree_ProcOfT)CompOAG0b);
        } while (!Stable);
      } while (!(n == W_18->AttrCount));
      if (W_18->BaseClass->U_1.V_1.Kind == Tree_Class && W_18->BaseClass->U_1.V_5.Class.Visits > k) {
        k = W_18->BaseClass->U_1.V_5.Class.Visits;
      }
      W_18->Visits = k;
      if (Tree_MaxVisit < k) {
        Tree_MaxVisit = k;
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_19 = &t->U_1.V_9.Child;

      if (W_19->Partition == 9999) {
        if (IN(Tree_Input, W_19->Properties) || (W_19->Properties & (SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Synthesized))) == 0X0L) {
          W_19->Partition = 0;
          INC(n);
          return;
        }
        if (IN(Kind, W_19->Properties)) {
          {
            SHORTCARD B_31 = 1, B_32 = ActClass->U_1.V_5.Class.AttrCount;

            if (B_31 <= B_32)
              for (i = B_31;; i += 1) {
                if (Relations_IsRelated((LONGINT)i, (LONGINT)W_19->AttrIndex, ActClass->U_1.V_5.Class.OAG) && ActClass->U_1.V_5.Class.Instance->A[i - 1].Attribute->U_1.V_9.Child.Partition > k) {
                  return;
                }
                if (i >= B_32) break;
              }
          }
          W_19->Partition = k;
          INC(n);
          Stable = FALSE;
        }
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_20 = &t->U_1.V_10.Attribute;

      if (W_20->Partition == 9999) {
        if (IN(Tree_Input, W_20->Properties) || (W_20->Properties & (SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Synthesized))) == 0X0L) {
          W_20->Partition = 0;
          INC(n);
          return;
        }
        if (IN(Kind, W_20->Properties)) {
          {
            SHORTCARD B_33 = 1, B_34 = ActClass->U_1.V_5.Class.AttrCount;

            if (B_33 <= B_34)
              for (i = B_33;; i += 1) {
                if (Relations_IsRelated((LONGINT)i, (LONGINT)W_20->AttrIndex, ActClass->U_1.V_5.Class.OAG) && ActClass->U_1.V_5.Class.Instance->A[i - 1].Attribute->U_1.V_10.Attribute.Partition > k) {
                  return;
                }
                if (i >= B_34) break;
              }
          }
          W_20->Partition = k;
          INC(n);
          Stable = FALSE;
        }
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CompOAG0c
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_21 = &t->U_1.V_5.Class;

      k = W_21->Visits + 1;
      Tree_ForallAttributes(W_21->Attributes, (Tree_ProcOfT)CompOAG0c);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_22 = &t->U_1.V_9.Child;

      if (W_22->Partition != 0) {
        W_22->Partition = k - W_22->Partition;
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_23 = &t->U_1.V_10.Attribute;

      if (W_23->Partition != 0) {
        W_23->Partition = k - W_23->Partition;
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CompOAG0d
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_24 = &t->U_1.V_5.Class;

      ActClass = t;
      k = 0;
      do {
        INC(k);
        do {
          Stable = TRUE;
          Tree_ForallAttributes(W_24->Attributes, (Tree_ProcOfT)CompOAG0d);
        } while (!Stable);
        do {
          Stable = TRUE;
          Tree_ForallAttributes(W_24->Attributes, (Tree_ProcOfT)CompOAG0e);
        } while (!Stable);
      } while (!(k == W_24->Visits));
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_25 = &t->U_1.V_9.Child;

      if (W_25->Partition > k && IN(Tree_Synthesized, W_25->Properties) && (((SET_ELEM(Tree_Output) | SET_ELEM(Tree_Test)) & W_25->Properties) != 0X0L || ((SET_ELEM(Tree_Read) | SET_ELEM(Tree_Dummy)) & W_25->Properties) == 0X0L)) {
        {
          SHORTCARD B_35 = 1, B_36 = ActClass->U_1.V_5.Class.AttrCount;

          if (B_35 <= B_36)
            for (i = B_35;; i += 1) {
              if (Relations_IsRelated((LONGINT)W_25->AttrIndex, (LONGINT)i, ActClass->U_1.V_5.Class.OAG) && ActClass->U_1.V_5.Class.Instance->A[i - 1].Attribute->U_1.V_9.Child.Partition > k) {
                return;
              }
              if (i >= B_36) break;
            }
        }
        W_25->Partition = k;
        Stable = FALSE;
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_26 = &t->U_1.V_10.Attribute;

      if (W_26->Partition > k && IN(Tree_Synthesized, W_26->Properties) && (((SET_ELEM(Tree_Output) | SET_ELEM(Tree_Test)) & W_26->Properties) != 0X0L || ((SET_ELEM(Tree_Read) | SET_ELEM(Tree_Dummy)) & W_26->Properties) == 0X0L)) {
        {
          SHORTCARD B_37 = 1, B_38 = ActClass->U_1.V_5.Class.AttrCount;

          if (B_37 <= B_38)
            for (i = B_37;; i += 1) {
              if (Relations_IsRelated((LONGINT)W_26->AttrIndex, (LONGINT)i, ActClass->U_1.V_5.Class.OAG) && ActClass->U_1.V_5.Class.Instance->A[i - 1].Attribute->U_1.V_10.Attribute.Partition > k) {
                return;
              }
              if (i >= B_38) break;
            }
        }
        W_26->Partition = k;
        Stable = FALSE;
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CompOAG0e
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_15 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Child:;
    {
      register Tree_yChild *W_27 = &t->U_1.V_9.Child;

      if (W_27->Partition > k && IN(Tree_Inherited, W_27->Properties) && (((SET_ELEM(Tree_Output) | SET_ELEM(Tree_Test)) & W_27->Properties) != 0X0L || ((SET_ELEM(Tree_Read) | SET_ELEM(Tree_Dummy)) & W_27->Properties) == 0X0L)) {
        {
          SHORTCARD B_39 = 1, B_40 = ActClass->U_1.V_5.Class.AttrCount;

          if (B_39 <= B_40)
            for (i = B_39;; i += 1) {
              {
                register Tree_tInstance *W_28 = &ActClass->U_1.V_5.Class.Instance->A[i - 1];

                if (Relations_IsRelated((LONGINT)W_27->AttrIndex, (LONGINT)i, ActClass->U_1.V_5.Class.OAG) && (IN(Tree_Inherited, W_28->Properties) && W_28->Attribute->U_1.V_9.Child.Partition > k || IN(Tree_Synthesized, W_28->Properties) && W_28->Attribute->U_1.V_9.Child.Partition >= k)) {
                  return;
                }
              }
              if (i >= B_40) break;
            }
        }
        W_27->Partition = k;
        Stable = FALSE;
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_29 = &t->U_1.V_10.Attribute;

      if (W_29->Partition > k && IN(Tree_Inherited, W_29->Properties) && (((SET_ELEM(Tree_Output) | SET_ELEM(Tree_Test)) & W_29->Properties) != 0X0L || ((SET_ELEM(Tree_Read) | SET_ELEM(Tree_Dummy)) & W_29->Properties) == 0X0L)) {
        {
          SHORTCARD B_41 = 1, B_42 = ActClass->U_1.V_5.Class.AttrCount;

          if (B_41 <= B_42)
            for (i = B_41;; i += 1) {
              {
                register Tree_tInstance *W_30 = &ActClass->U_1.V_5.Class.Instance->A[i - 1];

                if (Relations_IsRelated((LONGINT)W_29->AttrIndex, (LONGINT)i, ActClass->U_1.V_5.Class.OAG) && (IN(Tree_Inherited, W_30->Properties) && W_30->Attribute->U_1.V_10.Attribute.Partition > k || IN(Tree_Synthesized, W_30->Properties) && W_30->Attribute->U_1.V_10.Attribute.Partition >= k)) {
                  return;
                }
              }
              if (i >= B_42) break;
            }
        }
        W_29->Partition = k;
        Stable = FALSE;
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CompOAG1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_16 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_31 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_43 = 1, B_44 = W_31->AttrCount;

        if (B_43 <= B_44)
          for (i = B_43;; i += 1) {
            {
              register Tree_tInstance *W_32 = &W_31->Instance->A[i - 1];

              if (IN(Tree_Synthesized, W_32->Properties)) {
                {
                  SHORTCARD B_45 = 1, B_46 = W_31->AttrCount;

                  if (B_45 <= B_46)
                    for (j = B_45;; j += 1) {
                      if (IN(Tree_Inherited, W_31->Instance->A[j - 1].Properties) && W_32->Attribute->U_1.V_9.Child.Partition == W_31->Instance->A[j - 1].Attribute->U_1.V_9.Child.Partition) {
                        Relations_Include(&W_31->OAG, (LONGINT)i, (LONGINT)j);
                      }
                      if (j >= B_46) break;
                    }
                }
              }
            }
            if (i >= B_44) break;
          }
      }
      {
        SHORTCARD B_47 = 1, B_48 = W_31->AttrCount;

        if (B_47 <= B_48)
          for (i = B_47;; i += 1) {
            {
              register Tree_tInstance *W_33 = &W_31->Instance->A[i - 1];

              if (IN(Tree_Inherited, W_33->Properties) && W_33->Attribute->U_1.V_9.Child.Partition >= 2) {
                {
                  SHORTCARD B_49 = 1, B_50 = W_31->AttrCount;

                  if (B_49 <= B_50)
                    for (j = B_49;; j += 1) {
                      if (IN(Tree_Synthesized, W_31->Instance->A[j - 1].Properties) && W_33->Attribute->U_1.V_9.Child.Partition - 1 == W_31->Instance->A[j - 1].Attribute->U_1.V_9.Child.Partition) {
                        Relations_Include(&W_31->OAG, (LONGINT)i, (LONGINT)j);
                      }
                      if (j >= B_50) break;
                    }
                }
              }
            }
            if (i >= B_48) break;
          }
      }
      if (Sets_IsElement(ORD('C'), &Tree_Options)) {
        Relations_MakeRelation(&W_31->Part, (LONGINT)W_31->InstCount, (LONGINT)W_31->InstCount);
        Relations_Assign(&W_31->Part, W_31->OAG);
        Relations_Difference(&W_31->Part, W_31->DNC);
        Tree_WriteDependencies(t, W_31->Part, Tree_MaxSet);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Relations_ReleaseRelation(&W_31->Part);
      }
      return;
    }
  }
}

static void CompOAG2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_17 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_34 = &t->U_1.V_5.Class;

      ActClass = t;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CompOAG2);
      if (Relations_IsCyclic(W_34->OAG)) {
        if (!Sets_IsElement(ORD('L'), &Tree_Options)) {
          Tree_WarningI((LONGINT)CycleInOAG, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_34->Name));
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Cyclic Attributes and Artificially Introduced Dependencies", 58L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteNl((System_tFile)IO_StdOutput);
          Relations_MakeRelation(&W_34->Part, (LONGINT)W_34->InstCount, (LONGINT)W_34->InstCount);
          Sets_MakeSet(&Cyclics, (Sets_tElement)W_34->InstCount);
          Relations_GetCyclics(W_34->OAG, &Cyclics);
          Relations_Assign(&W_34->Part, W_34->OAG);
          Relations_Difference(&W_34->Part, W_34->DNC);
          Tree_WriteDependencies(t, W_34->Part, Cyclics);
          Relations_ReleaseRelation(&W_34->Part);
          Sets_ReleaseSet(&Cyclics);
        }
        Success = FALSE;
      }
      if (Sets_IsElement(ORD('O'), &Tree_Options)) {
        Tree_WriteDependencies(t, W_34->OAG, Tree_MaxSet);
      }
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_35 = &t->U_1.V_9.Child;

        if (!(W_35->Class != Tree_NoTree)) {
          goto EXIT_3;
        }
        ChildsClass = W_35->Class;
        {
          SHORTCARD B_51 = 1, B_52 = ChildsClass->U_1.V_5.Class.AttrCount;

          if (B_51 <= B_52)
            for (i = B_51;; i += 1) {
              {
                SHORTCARD B_53 = 1, B_54 = ChildsClass->U_1.V_5.Class.AttrCount;

                if (B_53 <= B_54)
                  for (j = B_53;; j += 1) {
                    if (Relations_IsRelated((LONGINT)i, (LONGINT)j, ChildsClass->U_1.V_5.Class.OAG)) {
                      Relations_Include(&ActClass->U_1.V_5.Class.OAG, (LONGINT)(ActClass->U_1.V_5.Class.AttrCount + W_35->InstOffset + i), (LONGINT)(ActClass->U_1.V_5.Class.AttrCount + W_35->InstOffset + j));
                    }
                    if (j >= B_54) break;
                  }
              }
              if (i >= B_52) break;
            }
        }
        return;
      }
    } EXIT_3:;
    break;
  default :
    break;
  }
}

static void CompOAG3a
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_18 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_36 = &t->U_1.V_5.Class;

      n = 0;
      Sets_MakeSet(&IsComputed, (Sets_tElement)W_36->InstCount);
      Sets_MakeSet(&IsComputable, (Sets_tElement)W_36->InstCount);
      {
        SHORTCARD B_55 = 1, B_56 = W_36->InstCount;

        if (B_55 <= B_56)
          for (i = B_55;; i += 1) {
            if (IsComputable3a(i, t)) {
              Sets_Include(&IsComputable, (Sets_tElement)i);
            }
            if (i >= B_56) break;
          }
      }
      while (!Sets_IsEmpty(IsComputable)) {
        i2 = Sets_Minimum(&IsComputable);
        j = Sets_Maximum(&IsComputable);
        for (;;) {
          if (Sets_IsElement((Sets_tElement)i2, &IsComputable)) {
            i = i2;
            if (!SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_36->Instance->A[i2 - 1].Properties)) {
              goto EXIT_4;
            }
          }
          INC(i2);
          if (i2 > j) {
            goto EXIT_4;
          }
        } EXIT_4:;
        {
          register Tree_tInstance *W_37 = &W_36->Instance->A[i - 1];

          INC(n);
          W_36->Instance->A[n - 1].Order = i;
          Sets_Include(&IsComputed, (Sets_tElement)i);
          Sets_Exclude(&IsComputable, (Sets_tElement)i);
          INCL(W_37->Properties, Tree_First);
          Visit = W_37->Attribute->U_1.V_9.Child.Partition;
          if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_37->Properties)) {
            {
              SHORTCARD B_57 = 1, B_58 = W_36->AttrCount;

              if (B_57 <= B_58)
                for (i2 = B_57;; i2 += 1) {
                  {
                    register Tree_tInstance *W_38 = &W_36->Instance->A[i2 - 1];

                    if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && IN(Tree_Inherited, W_38->Properties) && W_38->Attribute->U_1.V_9.Child.Partition == Visit) {
                      INC(n);
                      W_36->Instance->A[n - 1].Order = i2;
                      Sets_Include(&IsComputed, (Sets_tElement)i2);
                      Sets_Exclude(&IsComputable, (Sets_tElement)i2);
                    }
                  }
                  if (i2 >= B_58) break;
                }
            }
          } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right), W_37->Properties)) {
            if (W_37->Selector != Tree_NoTree) {
              ChildsClass = W_37->Selector->U_1.V_9.Child.Class;
              {
                SHORTCARD B_59 = W_36->AttrCount + W_37->Selector->U_1.V_9.Child.InstOffset + 1, B_60 = W_36->AttrCount + W_37->Selector->U_1.V_9.Child.InstOffset + ChildsClass->U_1.V_5.Class.AttrCount;

                if (B_59 <= B_60)
                  for (i2 = B_59;; i2 += 1) {
                    {
                      register Tree_tInstance *W_39 = &W_36->Instance->A[i2 - 1];

                      if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && IN(Tree_Synthesized, W_39->Properties) && W_39->Attribute->U_1.V_9.Child.Partition == Visit) {
                        INC(n);
                        W_36->Instance->A[n - 1].Order = i2;
                        Sets_Include(&IsComputed, (Sets_tElement)i2);
                        Sets_Exclude(&IsComputable, (Sets_tElement)i2);
                      }
                    }
                    if (i2 >= B_60) break;
                  }
              }
            }
          } else {
            {
              SHORTCARD B_61 = 1, B_62 = W_36->InstCount;

              if (B_61 <= B_62)
                for (i2 = B_61;; i2 += 1) {
                  if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && W_36->Instance->A[i2 - 1].Action == W_37->Action) {
                    INC(n);
                    W_36->Instance->A[n - 1].Order = i2;
                    Sets_Include(&IsComputed, (Sets_tElement)i2);
                    Sets_Exclude(&IsComputable, (Sets_tElement)i2);
                  }
                  if (i2 >= B_62) break;
                }
            }
          }
          {
            SHORTCARD B_63 = 1, B_64 = W_36->InstCount;

            if (B_63 <= B_64)
              for (i2 = B_63;; i2 += 1) {
                if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && !Sets_IsElement((Sets_tElement)i2, &IsComputable) && IsComputable3a(i2, t)) {
                  Sets_Include(&IsComputable, (Sets_tElement)i2);
                }
                if (i2 >= B_64) break;
              }
          }
        }
      }
      if (n != W_36->InstCount) {
        Tree_ErrorI((LONGINT)InternalErrorCompOAG, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_36->Name));
        Sets_Exclude(&Tree_Options, ORD('o'));
      }
      Sets_ReleaseSet(&IsComputed);
      Sets_ReleaseSet(&IsComputable);
      if (Sets_IsElement(ORD('G'), &Tree_Options)) {
        Order_WriteOrderDecl(t);
      }
      if (Sets_IsElement(ORD('E'), &Tree_Options)) {
        Order_WriteOrderEval(t);
      }
      if (Sets_IsElement(ORD('V'), &Tree_Options)) {
        Order_WriteVisitSequence(t);
      }
      return;
    }
  }
}

static void CompOAG3b
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_19 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_40 = &t->U_1.V_5.Class;

      Sets_MakeSet(&IsComputed, (Sets_tElement)W_40->InstCount);
      n = 0;
      do {
        i = W_40->InstCount;
        for (;;) {
          {
            register Tree_tInstance *W_41 = &W_40->Instance->A[i - 1];

            if (!Sets_IsElement((Sets_tElement)i, &IsComputed) && IsComputable3a(i, t)) {
              INC(n);
              Sets_Include(&IsComputed, (Sets_tElement)i);
              INCL(W_41->Properties, Tree_First);
              Visit = W_41->Attribute->U_1.V_9.Child.Partition;
              if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_41->Properties)) {
                {
                  SHORTCARD B_65 = 1, B_66 = W_40->AttrCount;

                  if (B_65 <= B_66)
                    for (i2 = B_65;; i2 += 1) {
                      {
                        register Tree_tInstance *W_42 = &W_40->Instance->A[i2 - 1];

                        if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && IN(Tree_Inherited, W_42->Properties) && W_42->Attribute->U_1.V_9.Child.Partition == Visit) {
                          INC(n);
                          Sets_Include(&IsComputed, (Sets_tElement)i2);
                          {
                            SHORTCARD B_67 = 1, B_68 = W_40->InstCount;

                            if (B_67 <= B_68)
                              for (j = B_67;; j += 1) {
                                if (Relations_IsRelated((LONGINT)j, (LONGINT)i2, W_40->OAG)) {
                                  Relations_Include(&W_40->OAG, (LONGINT)j, (LONGINT)i);
                                }
                                if (j >= B_68) break;
                              }
                          }
                        }
                      }
                      if (i2 >= B_66) break;
                    }
                }
              } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right), W_41->Properties)) {
                if (W_41->Selector != Tree_NoTree) {
                  ChildsClass = W_41->Selector->U_1.V_9.Child.Class;
                  {
                    SHORTCARD B_69 = W_40->AttrCount + W_41->Selector->U_1.V_9.Child.InstOffset + 1, B_70 = W_40->AttrCount + W_41->Selector->U_1.V_9.Child.InstOffset + ChildsClass->U_1.V_5.Class.AttrCount;

                    if (B_69 <= B_70)
                      for (i2 = B_69;; i2 += 1) {
                        {
                          register Tree_tInstance *W_43 = &W_40->Instance->A[i2 - 1];

                          if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && IN(Tree_Synthesized, W_43->Properties) && W_43->Attribute->U_1.V_9.Child.Partition == Visit) {
                            INC(n);
                            Sets_Include(&IsComputed, (Sets_tElement)i2);
                            {
                              SHORTCARD B_71 = 1, B_72 = W_40->InstCount;

                              if (B_71 <= B_72)
                                for (j = B_71;; j += 1) {
                                  if (Relations_IsRelated((LONGINT)j, (LONGINT)i2, W_40->OAG)) {
                                    Relations_Include(&W_40->OAG, (LONGINT)j, (LONGINT)i);
                                  }
                                  if (j >= B_72) break;
                                }
                            }
                          }
                        }
                        if (i2 >= B_70) break;
                      }
                  }
                }
              } else {
                {
                  SHORTCARD B_73 = 1, B_74 = W_40->InstCount;

                  if (B_73 <= B_74)
                    for (i2 = B_73;; i2 += 1) {
                      if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && W_40->Instance->A[i2 - 1].Action == W_41->Action) {
                        INC(n);
                        Sets_Include(&IsComputed, (Sets_tElement)i2);
                        {
                          SHORTCARD B_75 = 1, B_76 = W_40->InstCount;

                          if (B_75 <= B_76)
                            for (j = B_75;; j += 1) {
                              if (Relations_IsRelated((LONGINT)j, (LONGINT)i2, W_40->OAG)) {
                                Relations_Include(&W_40->OAG, (LONGINT)j, (LONGINT)i);
                              }
                              if (j >= B_76) break;
                            }
                        }
                      }
                      if (i2 >= B_74) break;
                    }
                }
              }
              goto EXIT_5;
            }
          }
          DEC(i);
        } EXIT_5:;
      } while (!(n == W_40->InstCount));
      Sets_AssignEmpty(&IsComputed);
      Sets_MakeSet(&IsComputable, (Sets_tElement)W_40->InstCount);
      {
        SHORTCARD B_77 = 1, B_78 = W_40->InstCount;

        if (B_77 <= B_78)
          for (i = B_77;; i += 1) {
            if (IsComputable3b(i, t)) {
              Sets_Include(&IsComputable, (Sets_tElement)i);
            }
            if (i >= B_78) break;
          }
      }
      while (!Sets_IsEmpty(IsComputable)) {
        Prio = 0;
        i2 = Sets_Minimum(&IsComputable);
        j = Sets_Maximum(&IsComputable);
        for (;;) {
          if (Sets_IsElement((Sets_tElement)i2, &IsComputable)) {
            {
              register Tree_tInstance *W_44 = &W_40->Instance->A[i2 - 1];

              if ((IN(Tree_Test, W_44->Properties) || !IN(Tree_Read, W_44->Properties)) && Prio < 1) {
                i = i2;
                Prio = 1;
              } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_44->Properties) && Prio < 2) {
                i = i2;
                Prio = 2;
              } else if (IN(Tree_Output, W_44->Properties) && Prio < 3) {
                i = i2;
                Prio = 3;
              } else {
                i = i2;
                goto EXIT_6;
              }
            }
          }
          INC(i2);
          if (i2 > j) {
            goto EXIT_6;
          }
        } EXIT_6:;
        {
          register Tree_tInstance *W_45 = &W_40->Instance->A[i - 1];

          Sets_Include(&IsComputed, (Sets_tElement)i);
          Visit = W_45->Attribute->U_1.V_9.Child.Partition;
          if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_45->Properties)) {
            {
              SHORTCARD B_79 = 1, B_80 = W_40->AttrCount;

              if (B_79 <= B_80)
                for (i2 = B_79;; i2 += 1) {
                  {
                    register Tree_tInstance *W_46 = &W_40->Instance->A[i2 - 1];

                    if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && IN(Tree_Inherited, W_46->Properties) && W_46->Attribute->U_1.V_9.Child.Partition == Visit) {
                      W_40->Instance->A[n - 1].Order = i2;
                      DEC(n);
                      Sets_Include(&IsComputed, (Sets_tElement)i2);
                    }
                  }
                  if (i2 >= B_80) break;
                }
            }
          } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right), W_45->Properties)) {
            if (W_45->Selector != Tree_NoTree) {
              ChildsClass = W_45->Selector->U_1.V_9.Child.Class;
              {
                SHORTCARD B_81 = W_40->AttrCount + W_45->Selector->U_1.V_9.Child.InstOffset + 1, B_82 = W_40->AttrCount + W_45->Selector->U_1.V_9.Child.InstOffset + ChildsClass->U_1.V_5.Class.AttrCount;

                if (B_81 <= B_82)
                  for (i2 = B_81;; i2 += 1) {
                    {
                      register Tree_tInstance *W_47 = &W_40->Instance->A[i2 - 1];

                      if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && IN(Tree_Synthesized, W_47->Properties) && W_47->Attribute->U_1.V_9.Child.Partition == Visit) {
                        W_40->Instance->A[n - 1].Order = i2;
                        DEC(n);
                        Sets_Include(&IsComputed, (Sets_tElement)i2);
                      }
                    }
                    if (i2 >= B_82) break;
                  }
              }
            }
          } else {
            {
              SHORTCARD B_83 = 1, B_84 = W_40->InstCount;

              if (B_83 <= B_84)
                for (i2 = B_83;; i2 += 1) {
                  if (!Sets_IsElement((Sets_tElement)i2, &IsComputed) && W_40->Instance->A[i2 - 1].Action == W_45->Action) {
                    W_40->Instance->A[n - 1].Order = i2;
                    DEC(n);
                    Sets_Include(&IsComputed, (Sets_tElement)i2);
                  }
                  if (i2 >= B_84) break;
                }
            }
          }
          W_40->Instance->A[n - 1].Order = i;
          DEC(n);
          Sets_Exclude(&IsComputable, (Sets_tElement)i);
          {
            SHORTCARD B_85 = 1, B_86 = W_40->InstCount;

            if (B_85 <= B_86)
              for (i2 = B_85;; i2 += 1) {
                if (IN(Tree_First, W_40->Instance->A[i2 - 1].Properties) && !Sets_IsElement((Sets_tElement)i2, &IsComputed) && !Sets_IsElement((Sets_tElement)i2, &IsComputable) && IsComputable3b(i2, t)) {
                  Sets_Include(&IsComputable, (Sets_tElement)i2);
                }
                if (i2 >= B_86) break;
              }
          }
        }
      }
      Sets_ReleaseSet(&IsComputed);
      Sets_ReleaseSet(&IsComputable);
      if (n != 0) {
        CompOAG3a(t);
      } else {
        if (Sets_IsElement(ORD('G'), &Tree_Options)) {
          Order_WriteOrderDecl(t);
        }
        if (Sets_IsElement(ORD('E'), &Tree_Options)) {
          Order_WriteOrderEval(t);
        }
        if (Sets_IsElement(ORD('V'), &Tree_Options)) {
          Order_WriteVisitSequence(t);
        }
      }
      return;
    }
  }
}

void Order_WriteOrderDecl
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_20 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_48 = &t->U_1.V_5.Class;

      Idents_WriteIdent((System_tFile)IO_StdOutput, W_48->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   ", 3L);
      Tree_WriteClassProperties((System_tFile)IO_StdOutput, W_48->Properties);
      IO_WriteNl((System_tFile)IO_StdOutput);
      IO_WriteNl((System_tFile)IO_StdOutput);
      {
        SHORTCARD B_87 = 1, B_88 = W_48->InstCount;

        if (B_87 <= B_88)
          for (i = B_87;; i += 1) {
            IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)i, 2L);
            Tree_WriteInstance(W_48->Instance->A[i - 1]);
            if (i >= B_88) break;
          }
      }
      IO_WriteNl((System_tFile)IO_StdOutput);
      return;
    }
  }
}

void Order_WriteOrderEval
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_21 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_49 = &t->U_1.V_5.Class;

      Idents_WriteIdent((System_tFile)IO_StdOutput, W_49->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   ", 3L);
      Tree_WriteClassProperties((System_tFile)IO_StdOutput, W_49->Properties);
      IO_WriteNl((System_tFile)IO_StdOutput);
      IO_WriteNl((System_tFile)IO_StdOutput);
      {
        SHORTCARD B_89 = 1, B_90 = W_49->InstCount;

        if (B_89 <= B_90)
          for (i = B_89;; i += 1) {
            IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)W_49->Instance->A[i - 1].Order, 2L);
            Tree_WriteInstance(W_49->Instance->A[W_49->Instance->A[i - 1].Order - 1]);
            if (i >= B_90) break;
          }
      }
      IO_WriteNl((System_tFile)IO_StdOutput);
      return;
    }
  }
}

void Order_WriteVisitSequence
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_22 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_50 = &t->U_1.V_5.Class;

      Idents_WriteIdent((System_tFile)IO_StdOutput, W_50->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   ", 3L);
      Tree_WriteClassProperties((System_tFile)IO_StdOutput, W_50->Properties);
      IO_WriteNl((System_tFile)IO_StdOutput);
      IO_WriteNl((System_tFile)IO_StdOutput);
      {
        SHORTCARD B_91 = 1, B_92 = W_50->InstCount;

        if (B_91 <= B_92)
          for (i = B_91;; i += 1) {
            AttrInstance = W_50->Instance->A[W_50->Instance->A[i - 1].Order - 1];
            {
              register Tree_tInstance *W_51 = &AttrInstance;

              if (IN(Tree_Inherited, W_51->Properties)) {
                if (IN(Tree_Left, W_51->Properties)) {
                  if (IN(Tree_First, W_51->Properties)) {
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"visit       parent ", 19L);
                    IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)W_51->Attribute->U_1.V_9.Child.Partition, 0L);
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)". time to compute", 17L);
                    IO_WriteNl((System_tFile)IO_StdOutput);
                  }
                  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"    ", 4L);
                  Tree_WriteName(AttrInstance);
                  IO_WriteNl((System_tFile)IO_StdOutput);
                }
                if (IN(Tree_Right, W_51->Properties)) {
                  if (IN(Tree_First, W_51->Properties)) {
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"compute     ", 12L);
                  } else {
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"    ", 4L);
                  }
                  Tree_WriteName(AttrInstance);
                  IO_WriteNl((System_tFile)IO_StdOutput);
                }
              }
              if (IN(Tree_Synthesized, W_51->Properties)) {
                if (IN(Tree_Left, W_51->Properties) && !IN(Tree_Dummy, W_51->Properties)) {
                  if (IN(Tree_Test, W_51->Properties)) {
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"check       condition ", 22L);
                  } else if (IN(Tree_First, W_51->Properties)) {
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"compute     ", 12L);
                  } else {
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"    ", 4L);
                  }
                  Idents_WriteIdent((System_tFile)IO_StdOutput, W_51->Attribute->U_1.V_9.Child.Name);
                  IO_WriteNl((System_tFile)IO_StdOutput);
                }
                if (IN(Tree_Right, W_51->Properties)) {
                  if (SET_IS_SUBSET1(SET_ELEM(Tree_First) | SET_ELEM(Tree_Dummy), W_51->Properties)) {
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"visit    ", 9L);
                    Idents_WriteIdent((System_tFile)IO_StdOutput, W_51->Selector->U_1.V_9.Child.Name);
                    IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)W_51->Attribute->U_1.V_9.Child.Partition, 2L);
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)". time", 6L);
                    IO_WriteNl((System_tFile)IO_StdOutput);
                  }
                  if (!IN(Tree_Dummy, W_51->Properties)) {
                    if (IN(Tree_First, W_51->Properties)) {
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"visit    ", 9L);
                      Idents_WriteIdent((System_tFile)IO_StdOutput, W_51->Selector->U_1.V_9.Child.Name);
                      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)W_51->Attribute->U_1.V_9.Child.Partition, 2L);
                      IO_WriteS((System_tFile)IO_StdOutput, (STRING)". time to compute", 17L);
                      IO_WriteNl((System_tFile)IO_StdOutput);
                    }
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)" ", 1L);
                    Tree_WriteName(AttrInstance);
                    IO_WriteNl((System_tFile)IO_StdOutput);
                  }
                }
              }
            }
            if (i >= B_92) break;
          }
      }
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"visit      parent", 17L);
      IO_WriteNl((System_tFile)IO_StdOutput);
      IO_WriteNl((System_tFile)IO_StdOutput);
      return;
    }
  }
}

static void CheckNormalForm
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_23 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_52 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_93 = 1, B_94 = W_52->InstCount;

        if (B_93 <= B_94)
          for (i = B_93;; i += 1) {
            if (!IN(Tree_Dummy, W_52->Instance->A[i - 1].Properties)) {
              {
                SHORTCARD B_95 = 1, B_96 = W_52->InstCount;

                if (B_95 <= B_96)
                  for (j = B_95;; j += 1) {
                    if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_52->DP)) {
                      {
                        register Tree_tInstance *W_53 = &W_52->Instance->A[j - 1];

                        if (SET_IS_SUBSET1(SET_ELEM(Tree_Left) | SET_ELEM(Tree_Synthesized), W_53->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Right) | SET_ELEM(Tree_Inherited), W_53->Properties)) {
                          Success = FALSE;
                          return;
                        }
                      }
                    }
                    if (j >= B_96) break;
                  }
              }
            }
            if (i >= B_94) break;
          }
      }
      return;
    }
  }
}

static void CheckLAG
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_24 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_54 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_97 = W_54->AttrCount + 1, B_98 = W_54->InstCount;

        if (B_97 <= B_98)
          for (i = B_97;; i += 1) {
            {
              SHORTCARD B_99 = 1, B_100 = W_54->AttrCount;

              if (B_99 <= B_100)
                for (j = B_99;; j += 1) {
                  if (IN(Tree_Synthesized, W_54->Instance->A[j - 1].Properties) && Relations_IsRelated((LONGINT)i, (LONGINT)j, W_54->DP)) {
                    Success = FALSE;
                    return;
                  }
                  if (j >= B_100) break;
                }
            }
            {
              register Tree_tInstance *W_55 = &W_54->Instance->A[i - 1];

              if (W_55->Selector != Tree_NoTree) {
                ChildsClass = W_55->Selector->U_1.V_9.Child.Class;
                {
                  SHORTCARD B_101 = W_54->AttrCount + W_55->Selector->U_1.V_9.Child.InstOffset + 1, B_102 = W_54->AttrCount + W_55->Selector->U_1.V_9.Child.InstOffset + ChildsClass->U_1.V_5.Class.AttrCount;

                  if (B_101 <= B_102)
                    for (j = B_101;; j += 1) {
                      if (IN(Tree_Synthesized, W_54->Instance->A[j - 1].Properties) && Relations_IsRelated((LONGINT)i, (LONGINT)j, W_54->DP)) {
                        Success = FALSE;
                        return;
                      }
                      if (j >= B_102) break;
                    }
                }
                {
                  SHORTCARD B_103 = W_54->AttrCount + W_55->Selector->U_1.V_9.Child.InstOffset + ChildsClass->U_1.V_5.Class.AttrCount + 1, B_104 = W_54->InstCount;

                  if (B_103 <= B_104)
                    for (j = B_103;; j += 1) {
                      if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_54->DP)) {
                        Success = FALSE;
                        return;
                      }
                      if (j >= B_104) break;
                    }
                }
              }
            }
            if (i >= B_98) break;
          }
      }
      return;
    }
  }
}

static void CheckSAG
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_25 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_56 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_105 = W_56->AttrCount + 1, B_106 = W_56->InstCount;

        if (B_105 <= B_106)
          for (i = B_105;; i += 1) {
            {
              SHORTCARD B_107 = 1, B_108 = W_56->InstCount;

              if (B_107 <= B_108)
                for (j = B_107;; j += 1) {
                  if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_56->DP)) {
                    Success = FALSE;
                    return;
                  }
                  if (j >= B_108) break;
                }
            }
            if (i >= B_106) break;
          }
      }
      return;
    }
  }
}

static void InitWAG
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_26 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    for (;;) {
      {
        register Tree_yClass *W_57 = &t->U_1.V_5.Class;

        if (!!Sets_IsElement((Sets_tElement)W_57->Index, &Relevant)) {
          goto EXIT_7;
        }
        Sets_Include(&Relevant, (Sets_tElement)W_57->Index);
        Tree_ForallAttributes(t, (Tree_ProcOfT)InitWAG);
        Tree_ForallClasses(W_57->Extensions, (Tree_ProcOfT)InitWAG);
        return;
      }
    } EXIT_7:;
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_58 = &t->U_1.V_9.Child;

      InitWAG(W_58->Class);
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckWAG0
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_27 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_59 = &t->U_1.V_5.Class;

      Tree_ForallAttributes(t, (Tree_ProcOfT)CheckWAG0);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_60 = &t->U_1.V_9.Child;

      CheckWAG1(W_60->Class);
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckWAG1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_28 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  {
    register struct S_29 *W_61 = &yyTempo.U_1.V_1.yyR1;

    for (;;) {
      {
        register Tree_yClass *W_62 = &t->U_1.V_5.Class;

        if (!!Sets_IsElement((Sets_tElement)W_62->Index, &Cyclics)) {
          goto EXIT_8;
        }
        Sets_Include(&Cyclics, (Sets_tElement)W_62->Index);
        Relations_ReleaseRelation(&W_62->DNC);
        Relations_MakeRelation(&W_61->C_0_A, (LONGINT)W_62->InstCount, (LONGINT)W_62->InstCount);
        Relations_Assign(&W_61->C_0_A, W_62->DP);
        W_62->D = NIL;
        CheckWAG5(t, W_61->C_0_A);
        Relations_ReleaseRelation(&W_61->C_0_A);
        CheckWAG0(t);
        Tree_ForallClasses(W_62->Extensions, (Tree_ProcOfT)CheckWAG1);
        return;
      }
    } EXIT_8:;
  }
}

static void CheckWAG2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_30 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  {
    register struct S_31 *W_63 = &yyTempo.U_1.V_1.yyR1;

    {
      register Tree_yClass *W_64 = &t->U_1.V_5.Class;

      Relations_MakeRelation(&W_63->C_0_A, (LONGINT)W_64->InstCount, (LONGINT)W_64->InstCount);
      Relations_Assign(&W_63->C_0_A, W_64->DP);
      ActClass = t;
      CheckWAG3(W_64->Attributes, W_63->C_0_A);
      Relations_ReleaseRelation(&W_63->C_0_A);
      return;
    }
  }
}

static void CheckWAG3
# ifdef __STDC__
(Tree_tTree yyP2, Relations_tRelation yyP1)
# else
(yyP2, yyP1)
Tree_tTree yyP2;
Relations_tRelation yyP1;
# endif
{
  struct S_32 yyTempo;

  if (yyP2 == Tree_NoTree) {
    return;
  }
  switch (yyP2->U_1.V_1.Kind) {
  case Tree_Child:;
    {
      register Tree_yChild *W_65 = &yyP2->U_1.V_9.Child;

      CheckWAG4(W_65->Class, yyP1, W_65->Next, yyP2);
      return;
    }
    break;
  case Tree_NoAttribute:;
    {
      register Tree_yNoAttribute *W_66 = &yyP2->U_1.V_7.NoAttribute;

      CheckWAG5(ActClass, yyP1);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_67 = &yyP2->U_1.V_10.Attribute;

      CheckWAG3(W_67->Next, yyP1);
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_68 = &yyP2->U_1.V_11.ActionPart;

      CheckWAG3(W_68->Next, yyP1);
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckWAG4
# ifdef __STDC__
(Tree_tTree yyP6, Relations_tRelation yyP5, Tree_tTree yyP4, Tree_tTree yyP3)
# else
(yyP6, yyP5, yyP4, yyP3)
Tree_tTree yyP6;
Relations_tRelation yyP5;
Tree_tTree yyP4;
Tree_tTree yyP3;
# endif
{
  struct S_33 yyTempo;

  if (yyP6 == Tree_NoTree) {
    return;
  }
  if (yyP4 == Tree_NoTree) {
    return;
  }
  if (yyP3 == Tree_NoTree) {
    return;
  }
  {
    register struct S_34 *W_69 = &yyTempo.U_1.V_1.yyR1;

    {
      register Tree_yClass *W_70 = &yyP6->U_1.V_5.Class;

      Relations_MakeRelation(&W_69->B, (LONGINT)ActClass->U_1.V_5.Class.InstCount, (LONGINT)ActClass->U_1.V_5.Class.InstCount);
      W_69->ActD = W_70->D;
      while (W_69->ActD != NIL) {
        Relations_Assign(&W_69->B, yyP5);
        {
          SHORTCARD B_109 = 2, B_110 = yyP3->U_1.V_9.Child.Class->U_1.V_5.Class.AttrCount;

          if (B_109 <= B_110)
            for (i = B_109;; i += 1) {
              {
                SHORTCARD B_111 = 2, B_112 = yyP3->U_1.V_9.Child.Class->U_1.V_5.Class.AttrCount;

                if (B_111 <= B_112)
                  for (j = B_111;; j += 1) {
                    if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_69->ActD->Relation)) {
                      Relations_Include(&W_69->B, (LONGINT)(ActClass->U_1.V_5.Class.AttrCount + yyP3->U_1.V_9.Child.InstOffset + i), (LONGINT)(ActClass->U_1.V_5.Class.AttrCount + yyP3->U_1.V_9.Child.InstOffset + j));
                    }
                    if (j >= B_112) break;
                  }
              }
              if (i >= B_110) break;
            }
        }
        CheckWAG3(yyP4, W_69->B);
        W_69->ActD = W_69->ActD->Next;
      }
      Relations_ReleaseRelation(&W_69->B);
      return;
    }
  }
}

static void CheckWAG5
# ifdef __STDC__
(Tree_tTree t, Relations_tRelation yyP7)
# else
(t, yyP7)
Tree_tTree t;
Relations_tRelation yyP7;
# endif
{
  struct S_35 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  {
    register struct S_36 *W_71 = &yyTempo.U_1.V_1.yyR1;

    {
      register Tree_yClass *W_72 = &t->U_1.V_5.Class;

      if (Reporting) {
        Tree_ErrorI((LONGINT)CycleInWAG, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_72->Name));
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Dependencies WAG", 26L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Tree_WriteDependencies(t, yyP7, Tree_MaxSet);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Cyclic Attributes", 17L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Sets_MakeSet(&Cyclics, (Sets_tElement)W_72->InstCount);
        Relations_GetCyclics(yyP7, &Cyclics);
        Tree_WriteCyclics(ActClass, Cyclics);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Sets_ReleaseSet(&Cyclics);
      } else {
        if (IN(Tree_Referenced, W_72->Properties) || W_72->BaseClass->U_1.V_1.Kind == Tree_NoClass) {
          Relations_Closure(&yyP7);
          if (Relations_HasReflexive(yyP7)) {
            Sets_Include(&HasCycle, (Sets_tElement)W_72->Index);
          }
          Relations_MakeRelation(&W_71->B, (LONGINT)W_72->AttrCount, (LONGINT)W_72->AttrCount);
          {
            SHORTCARD B_113 = 2, B_114 = W_72->AttrCount;

            if (B_113 <= B_114)
              for (i = B_113;; i += 1) {
                {
                  SHORTCARD B_115 = 2, B_116 = W_72->AttrCount;

                  if (B_115 <= B_116)
                    for (j = B_115;; j += 1) {
                      if (Relations_IsRelated((LONGINT)i, (LONGINT)j, yyP7)) {
                        Relations_Include(&W_71->B, (LONGINT)i, (LONGINT)j);
                      }
                      if (j >= B_116) break;
                    }
                }
                if (i >= B_114) break;
              }
          }
          if (Relations_IsEmpty(W_71->B)) {
            Relations_ReleaseRelation(&W_71->B);
            return;
          }
          W_71->ActD = W_72->D;
          while (W_71->ActD != NIL) {
            if (Relations_IsSubset(W_71->B, W_71->ActD->Relation)) {
              Relations_ReleaseRelation(&W_71->B);
              return;
            }
            W_71->ActD = W_71->ActD->Next;
          }
          W_71->ActD = W_72->D;
          W_71->LastNext = (tSetOfRelPtrPtr)ADR(W_72->D);
          while (W_71->ActD != NIL) {
            if (Relations_IsSubset(W_71->ActD->Relation, W_71->B)) {
              W_71->ActD = W_71->ActD->Next;
              Memory_Free((LONGINT)sizeof(Tree_tSetOfRel), (ADDRESS)(*W_71->LastNext));
              *W_71->LastNext = W_71->ActD;
            } else {
              W_71->LastNext = (tSetOfRelPtrPtr)ADR(W_71->ActD->Next);
              W_71->ActD = W_71->ActD->Next;
            }
          }
          W_71->ActD = (Tree_tSetOfRelPtr)Memory_Alloc((LONGINT)sizeof(Tree_tSetOfRel));
          W_71->ActD->Next = W_72->D;
          W_71->ActD->Relation = W_71->B;
          W_72->D = W_71->ActD;
          {
            SHORTCARD B_117 = Sets_Minimum(&W_72->Users), B_118 = Sets_Maximum(&W_72->Users);

            if (B_117 <= B_118)
              for (UserIndex = B_117;; UserIndex += 1) {
                if (Sets_IsElement((Sets_tElement)UserIndex, &W_72->Users) && Sets_IsElement((Sets_tElement)UserIndex, &Relevant)) {
                  Queue_Enqueue(UserIndex);
                }
                if (UserIndex >= B_118) break;
              }
          }
        }
        if (W_72->BaseClass->U_1.V_1.Kind != Tree_NoClass) {
          CheckWAG5(W_72->BaseClass, yyP7);
        }
      }
      return;
    }
  }
}

void Order_BeginOrder
# ifdef __STDC__
()
# else
()
# endif
{
}

void Order_CloseOrder
# ifdef __STDC__
()
# else
()
# endif
{
}

static void yyExit
# ifdef __STDC__
()
# else
()
# endif
{
  IO_CloseIO();
  Exit(1L);
}

void Order__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Tree__init();
    System__init();
    IO__init();
    Tree__init();
    Memory__init();
    DynArray__init();
    IO__init();
    Idents__init();
    Sets__init();
    Relations__init();
    Queue__init();
    Tree__init();
    Optimize__init();
    Sets__init();
    Relations__init();
    Queue__init();
    Errors__init();

    Order_yyf = IO_StdOutput;
    Order_Exit = yyExit;
    Order_BeginOrder();
  }
}
