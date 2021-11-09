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

#ifndef DEFINITION_General
#include "General.h"
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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Order
#include "Order.h"
#endif

#ifndef DEFINITION_Optimize
#include "Optimize.h"
#endif

SHORTCARD Optimize_ChildrenDyn, Optimize_ChildrenIn, Optimize_AttributeIn, Optimize_AttributeOut, Optimize_AttributeTree, Optimize_AttributeParam, Optimize_AttributeVar, Optimize_AttributeDemand, Optimize_AttributeStack;
IO_tFile Optimize_yyf;
PROC Optimize_Exit;

typedef struct S_1 {
    SHORTCARD Birth, Death;
} tLife;
static Sets_tSet Children, Parents, Relevant;
static SHORTCARD ClassIndex, MaxChildUse, MaxParentUse, Attr, Comp, Last, ChildsVisit, i, i2, j, j2, k, Visit, v;
static Tree_tTree ActChild, ActClass, ChildsClass;
static LONGINT LifeSize;
static struct S_2 {
    tLife A[10000 + 1];
} *LifePtr;
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void LifeTime2 ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Optimize, routine ", 32L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Optimize_Exit)();
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
    LONGINT B_1 = 0, B_2 = (INTEGER)(O_3 - 1);

    if (B_1 <= B_2)
      for (yyi = B_1;; yyi += 1) {
        if (yya[yyi] != yyb[yyi]) {
          FREE_OPEN_ARRAYS
          return FALSE;
        }
        if (yyi >= B_2) break;
      }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

void Optimize_LifeTime1
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
      register Tree_yClass *W_1 = &t->U_1.V_5.Class;

      LifeSize = W_1->InstCount + 1;
      DynArray_MakeArray((ADDRESS *)&LifePtr, &LifeSize, (LONGINT)sizeof(tLife));
      {
        SHORTCARD B_3 = 1, B_4 = W_1->InstCount;

        if (B_3 <= B_4)
          for (i = B_3;; i += 1) {
            LifePtr->A[i].Birth = 0;
            LifePtr->A[i].Death = 0;
            if (i >= B_4) break;
          }
      }
      Visit = 1;
      {
        SHORTCARD B_5 = 1, B_6 = W_1->InstCount;

        if (B_5 <= B_6)
          for (i = B_5;; i += 1) {
            i2 = W_1->Instance->A[i - 1].Order;
            {
              register Tree_tInstance *W_2 = &W_1->Instance->A[i2 - 1];

              if (SET_IS_SUBSET1(SET_ELEM(Tree_Left) | SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_First), W_2->Properties)) {
                Visit = W_2->Attribute->U_1.V_9.Child.Partition;
              }
              if (SET_IS_SUBSET1(SET_ELEM(Tree_Left) | SET_ELEM(Tree_Synthesized), W_2->Properties)) {
                LifePtr->A[i2].Birth = Visit;
                INCL(W_2->Attribute->U_1.V_9.Child.Usage, Visit);
              }
              if (IN(Tree_Right, W_2->Properties)) {
                LifePtr->A[i2].Birth = Visit;
              }
              if (SET_IS_SUBSET1(SET_ELEM(Tree_Left) | SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_First), W_2->Properties) && !IN(Tree_Dummy, W_2->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Right) | SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_First), W_2->Properties)) {
                {
                  SHORTCARD B_7 = 1, B_8 = W_1->AttrCount;

                  if (B_7 <= B_8)
                    for (j = B_7;; j += 1) {
                      if (Relations_IsRelated((LONGINT)i2, (LONGINT)j, W_1->DP)) {
                        LifePtr->A[j].Death = Visit;
                        INCL(W_1->Instance->A[j - 1].Attribute->U_1.V_9.Child.Usage, Visit);
                      }
                      if (j >= B_8) break;
                    }
                }
                {
                  SHORTCARD B_9 = W_1->AttrCount + 1, B_10 = W_1->InstCount;

                  if (B_9 <= B_10)
                    for (j = B_9;; j += 1) {
                      if (Relations_IsRelated((LONGINT)i2, (LONGINT)j, W_1->DP)) {
                        LifePtr->A[j].Death = Visit;
                      }
                      if (j >= B_10) break;
                    }
                }
              }
              if (SET_IS_SUBSET1(SET_ELEM(Tree_Right) | SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_First), W_2->Properties)) {
                ActClass = t;
                ActChild = W_2->Selector;
                ChildsClass = W_2->Selector->U_1.V_9.Child.Class;
                ChildsVisit = W_2->Attribute->U_1.V_9.Child.Partition;
                LifeTime2(ChildsClass);
                Tree_ForallClasses(ChildsClass->U_1.V_5.Class.Extensions, (Tree_ProcOfT)LifeTime2);
              }
            }
            if (i >= B_6) break;
          }
      }
      {
        SHORTCARD B_11 = 1, B_12 = W_1->AttrCount;

        if (B_11 <= B_12)
          for (i = B_11;; i += 1) {
            {
              register Tree_tInstance *W_3 = &W_1->Instance->A[i - 1];

              if (IN(Tree_Synthesized, W_3->Properties) && LifePtr->A[i].Birth < LifePtr->A[i].Death) {
                INCL(W_3->Attribute->U_1.V_9.Child.Properties, Tree_Tree);
              }
            }
            if (i >= B_12) break;
          }
      }
      {
        SHORTCARD B_13 = W_1->AttrCount + 1, B_14 = W_1->InstCount;

        if (B_13 <= B_14)
          for (i = B_13;; i += 1) {
            if (LifePtr->A[i].Birth < LifePtr->A[i].Death) {
              {
                register Tree_tInstance *W_4 = &W_1->Instance->A[i - 1];

                INCL(W_4->Attribute->U_1.V_9.Child.Properties, Tree_Tree);
              }
            }
            if (i >= B_14) break;
          }
      }
      DynArray_ReleaseArray((ADDRESS *)&LifePtr, &LifeSize, (LONGINT)sizeof(tLife));
      return;
    }
  }
}

static void LifeTime2
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      v = 1;
      {
        SHORTCARD B_15 = 1, B_16 = W_5->InstCount;

        if (B_15 <= B_16)
          for (j = B_15;; j += 1) {
            j2 = W_5->Instance->A[j - 1].Order;
            {
              register Tree_tInstance *W_6 = &W_5->Instance->A[j2 - 1];

              if (SET_IS_SUBSET1(SET_ELEM(Tree_Left) | SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_First), W_6->Properties)) {
                v = W_6->Attribute->U_1.V_9.Child.Partition;
                if (v > ChildsVisit) {
                  return;
                }
              }
              if (!IN(Tree_Dummy, W_6->Properties) && ChildsVisit == v) {
                {
                  SHORTCARD B_17 = 1, B_18 = ChildsClass->U_1.V_5.Class.AttrCount;

                  if (B_17 <= B_18)
                    for (k = B_17;; k += 1) {
                      if (Relations_IsRelated((LONGINT)j2, (LONGINT)k, W_5->DP)) {
                        LifePtr->A[ActClass->U_1.V_5.Class.AttrCount + ActChild->U_1.V_9.Child.InstOffset + k].Death = Visit;
                      }
                      if (k >= B_18) break;
                    }
                }
              }
            }
            if (j >= B_16) break;
          }
      }
      return;
    }
  }
}

void Optimize_LifeTime3
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
      register Tree_yClass *W_7 = &t->U_1.V_5.Class;

      ActClass = t;
      Tree_ForallAttributes(W_7->Attributes, (Tree_ProcOfT)Optimize_LifeTime3);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_8 = &t->U_1.V_9.Child;

      INCL(W_8->Properties, Tree_Tree);
      if (IN(Tree_Input, W_8->Properties)) {
        INC(Optimize_ChildrenIn);
      } else {
        INC(Optimize_ChildrenDyn);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_9 = &t->U_1.V_10.Attribute;

      if (Sets_IsElement(ORD('0'), &Tree_Options)) {
        if (IN(Tree_Input, W_9->Properties) || IN(Tree_Output, W_9->Properties)) {
          INCL(W_9->Properties, Tree_Tree);
          if (IN(Tree_Input, W_9->Properties)) {
            INC(Optimize_AttributeIn);
          } else {
            INC(Optimize_AttributeOut);
          }
        }
        if (!IN(Tree_Tree, W_9->Properties)) {
          INCL(W_9->Properties, Tree_Parameter);
        }
      } else {
        INCL(W_9->Properties, Tree_Tree);
      }
      if (((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Virtual) | SET_ELEM(Tree_Demand)) & W_9->Properties) != 0X0L) {
        EXCL(W_9->Properties, Tree_Tree);
        EXCL(W_9->Properties, Tree_Parameter);
      }
      if (Sets_IsElement(ORD('3'), &Tree_Options)) {
        if (((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Virtual) | SET_ELEM(Tree_Input) | SET_ELEM(Tree_Output)) & W_9->Properties) == 0X0L) {
          Idents_WriteIdent((System_tFile)IO_StdOutput, ActClass->U_1.V_5.Class.Name);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"	= ", 3L);
          Idents_WriteIdent((System_tFile)IO_StdOutput, W_9->Name);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"	", 1L);
          if (IN(Tree_Tree, W_9->Properties)) {
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Tree", 4L);
            INC(Optimize_AttributeTree);
          } else if (IN(Tree_Parameter, W_9->Properties)) {
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Parameter", 9L);
            INC(Optimize_AttributeParam);
          } else if (IN(Tree_Stack, W_9->Properties)) {
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Stack", 5L);
            INC(Optimize_AttributeStack);
          } else if (IN(Tree_Variable, W_9->Properties)) {
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Variable", 8L);
            INC(Optimize_AttributeVar);
          } else if (IN(Tree_Demand, W_9->Properties)) {
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Demand", 6L);
            INC(Optimize_AttributeDemand);
          }
          IO_WriteNl((System_tFile)IO_StdOutput);
        }
      }
      return;
    }
    break;
  default :
    break;
  }
}

void Optimize_BeginOptimize
# ifdef __STDC__
()
# else
()
# endif
{
}

void Optimize_CloseOptimize
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

void Optimize__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Tree__init();
    System__init();
    IO__init();
    Tree__init();
    General__init();
    DynArray__init();
    IO__init();
    Idents__init();
    Sets__init();
    Relations__init();
    Tree__init();
    Order__init();

    Optimize_yyf = IO_StdOutput;
    Optimize_Exit = yyExit;
    Optimize_BeginOptimize();
  }
}
