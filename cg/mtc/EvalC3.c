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

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_TreeC1
#include "TreeC1.h"
#endif

#ifndef DEFINITION_TreeC2
#include "TreeC2.h"
#endif

#ifndef DEFINITION_EvalC
#include "EvalC.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_EvalC
#include "EvalC.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_EvalC3
#include "EvalC3.h"
#endif

IO_tFile EvalC3_yyf;
PROC EvalC3_Exit;

static SHORTCARD i, i2, j, k, n, MaxBit, MaxInstCount, Check;
static Tree_tTree Node, Attr, ChildsClass;
static BOOLEAN Success, IsStable;
static LONGINT BitIndexSize;
static Tree_tBitIndex gBitIndex;
static Sets_tSet InhIndices;
static LONGINT InhIndexSize;
static struct S_1 {
    SHORTCARD A[1000000 - 1 + 1];
} *InhIndexCount;
static void GenCall ARGS((Tree_tTree t, SHORTCARD j));
static void GenEvalAttr ARGS((Tree_tTree t, INTEGER i));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_4 {
    union {
        struct {
            struct S_5 {
                SHORTCARD a;
            } yyR2;
        } V_1;
    } U_1;
};
static void CompBitInfo ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void CompInhIndices ARGS((Tree_tTree t));
struct S_7 {
    union {
        struct {
            struct S_8 {
                INTEGER b;
            } yyR1;
        } V_1;
    } U_1;
};
static void CountSynAttr ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void TypeName ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void GenS ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void GenE ARGS((Tree_tTree t));
struct S_12 {
    union {
        struct {
            struct S_13 {
                Sets_tSet ToCompute;
            } yyR1;
        } V_1;
    } U_1;
};
static void CompOutput ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void CompOutput2 ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static INTEGER ToBit1 ARGS((Tree_tTree yyP4, INTEGER yyP3));
struct S_17 {
    union {
        char dummy;
    } U_1;
};
static INTEGER ToBit2 ARGS((Tree_tTree yyP7, Tree_tTree yyP6, SHORTCARD yyP5));
struct S_18 {
    union {
        struct {
            struct S_19 {
                INTEGER yyV1;
            } yyR1;
        } V_1;
    } U_1;
};
static INTEGER ToAttr ARGS((Tree_tTree yyP9, INTEGER yyP8));
struct S_20 {
    union {
        struct {
            struct S_21 {
                INTEGER yyV1;
            } yyR1;
        } V_1;
    } U_1;
};
static void yyExit ARGS(());


static void GenCall
# ifdef __STDC__
(Tree_tTree t, SHORTCARD j)
# else
(t, j)
Tree_tTree t;
SHORTCARD j;
# endif
{
  {
    register Tree_tInstance *W_1 = &t->U_1.V_5.Class.Instance->A[j - 1];

    if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_1->Properties)) {
      k = EvalC3_ToBit0(t, (LONGINT)j);
      IO_WriteS(Tree_f, (STRING)"IFNOTIN (", 9L);
      Tree_WN((LONGINT)(k % TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)", yyt->yyHead.yyIsComp", 22L);
      Tree_WN((LONGINT)(k / TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)") ", 2L);
      IO_WriteS(Tree_f, (STRING)"yyS", 3L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)" (yyt); /* ", 11L);
      Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)" */ }", 5L);
      IO_WriteNl(Tree_f);
    } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_1->Properties)) {
      k = EvalC3_ToBit0(t, (LONGINT)j);
      IO_WriteS(Tree_f, (STRING)"IFNOTIN (", 9L);
      Tree_WN((LONGINT)(k % TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)", yyt->yyHead.yyIsComp", 22L);
      Tree_WN((LONGINT)(k / TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)") ", 2L);
      if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"yyVisitParent (yyt); ", 21L);
        IO_WriteS(Tree_f, (STRING)"yyI [yyt->yyHead.yyOffset + ", 28L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)"](yyt->yyHead.yyParent); /* ", 28L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" */ ", 4L);
        IO_WriteS(Tree_f, (STRING)"yyWriteVisit (yyt->yyHead.yyParent, \"?\"); }", 43L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"yyI [yyt->yyHead.yyOffset + ", 28L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)"](yyt->yyHead.yyParent); /* ", 28L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" */ }", 5L);
        IO_WriteNl(Tree_f);
      }
    } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_1->Properties)) {
      k = ToBit1(W_1->Selector, (LONGINT)(j - t->U_1.V_5.Class.AttrCount - W_1->Selector->U_1.V_9.Child.InstOffset));
      IO_WriteS(Tree_f, (STRING)"IFNOTIN (", 9L);
      Tree_WN((LONGINT)(k % TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)", yyt->", 7L);
      Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)"->yyHead.yyIsComp", 17L);
      Tree_WN((LONGINT)(k / TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)") ", 2L);
      k = ToBit2(t, W_1->Selector, j);
      IO_WriteS(Tree_f, (STRING)"yyI", 3L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)" (yyt); /* ", 11L);
      Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)":", 1L);
      Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)" */ }", 5L);
      IO_WriteNl(Tree_f);
    } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right), W_1->Properties)) {
      k = ToBit1(W_1->Selector, (LONGINT)(j - t->U_1.V_5.Class.AttrCount - W_1->Selector->U_1.V_9.Child.InstOffset));
      IO_WriteS(Tree_f, (STRING)"IFNOTIN (", 9L);
      Tree_WN((LONGINT)(k % TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)", yyt->", 7L);
      Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)"->yyHead.yyIsComp", 17L);
      Tree_WN((LONGINT)(k / TreeC1_BSS));
      IO_WriteS(Tree_f, (STRING)") ", 2L);
      if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"yyWriteVisit (yyt, \"", 20L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)"\"); ", 4L);
        IO_WriteS(Tree_f, (STRING)"yyS", 3L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
        Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)"); /* ", 6L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" */ ", 4L);
        IO_WriteS(Tree_f, (STRING)"yyVisitParent (yyt->", 20L);
        Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)"); }", 4L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"yyS", 3L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
        Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)"); /* ", 6L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" */ }", 5L);
        IO_WriteNl(Tree_f);
      }
    }
  }
}

static void GenEvalAttr
# ifdef __STDC__
(Tree_tTree t, INTEGER i)
# else
(t, i)
Tree_tTree t;
INTEGER i;
# endif
{
  EvalC_Class = t;
  {
    register Tree_tInstance *W_2 = &t->U_1.V_5.Class.Instance->A[i - 1];

    if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
      IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
      Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)"\");", 3L);
      IO_WriteNl(Tree_f);
      if (W_2->Action != ADR(W_2->Action) && !IN(Tree_Virtual, W_2->Properties)) {
        EvalC_GenEvaluator(W_2->Action);
        IO_WriteNl(Tree_f);
        if (IN(Tree_Test, W_2->Properties)) {
          IO_WriteS(Tree_f, (STRING)"writebool (yyb) yyWriteNl ();", 29L);
          IO_WriteNl(Tree_f);
        } else if (W_2->Attribute->U_1.V_1.Kind == Tree_Child || W_2->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
          IO_WriteS(Tree_f, (STRING)"write", 5L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
          Tree_WI(t->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)")", 1L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"write", 5L);
          Tree_WI(W_2->Attribute->U_1.V_9.Child.Type);
          IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
          Tree_WI(t->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)") yyWriteNl ();", 15L);
          IO_WriteNl(Tree_f);
        }
      } else {
        IO_WriteS(Tree_f, (STRING)"yyWriteNl ();", 13L);
        IO_WriteNl(Tree_f);
      }
    } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
      IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
      Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)"\");", 3L);
      IO_WriteNl(Tree_f);
      if (W_2->Action != ADR(W_2->Action) && !IN(Tree_Virtual, W_2->Properties)) {
        EvalC_GenEvaluator(W_2->Action);
      }
    } else {
      if (W_2->Action != ADR(W_2->Action) && !IN(Tree_Virtual, W_2->Properties)) {
        EvalC_GenEvaluator(W_2->Action);
      }
    }
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module EvalC3, routine ", 30L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*EvalC3_Exit)();
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

void EvalC3_EvalImplC
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Ag:;
    {
      register Tree_yAg *W_3 = &t->U_1.V_26.Ag;

      MaxBit = 0;
      MaxInstCount = 0;
      Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)CompBitInfo);
      Sets_MakeSet(&InhIndices, (Sets_tElement)MaxInstCount);
      InhIndexSize = MaxInstCount;
      DynArray_MakeArray((ADDRESS *)&InhIndexCount, &InhIndexSize, (LONGINT)sizeof(SHORTCARD));
      {
        SHORTCARD B_3 = 1, B_4 = MaxInstCount;

        if (B_3 <= B_4)
          for (i = B_3;; i += 1) {
            InhIndexCount->A[i - 1] = 0;
            if (i >= B_4) break;
          }
      }
      Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)CompInhIndices);
      IO_WriteS(Tree_f, (STRING)"# define IFNOTIN(b, s) if (! (s & 1 << b)) {", 44L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define INCL(s, b) s |= 1 << b", 31L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define REMOTE_SYN(i, b, c, n, t, a) (n->yyHead.i & 1 << b ? (void) 0 : c (n), n->t.a)", 87L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define REMOTE_INH(i, b, k, n, t, a) (n->yyHead.i & 1 << b ? (void) 0 : yyI [n->yyHead.yyOffset + k](n->yyHead.yyParent), n->t.a)", 130L);
      IO_WriteNl(Tree_f);
      EvalC_EvalImplHead(t);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"static void yyE ARGS((register ", 31L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
      IO_WriteNl(Tree_f);
      {
        SHORTCARD B_5 = 1, B_6 = MaxBit - 1;

        if (B_5 <= B_6)
          for (i = B_5;; i += 1) {
            IO_WriteS(Tree_f, (STRING)"static void yyS", 15L);
            Tree_WN((LONGINT)i);
            IO_WriteS(Tree_f, (STRING)" ARGS((register ", 16L);
            Tree_WI(Tree_itTree);
            IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
            IO_WriteNl(Tree_f);
            if (i >= B_6) break;
          }
      }
      {
        SHORTCARD B_7 = Sets_Minimum(&InhIndices), B_8 = Sets_Maximum(&InhIndices);

        if (B_7 <= B_8)
          for (i = B_7;; i += 1) {
            if (Sets_IsElement((Sets_tElement)i, &InhIndices)) {
              IO_WriteS(Tree_f, (STRING)"static void yyI", 15L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)" ARGS((register ", 16L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
              IO_WriteNl(Tree_f);
            }
            if (i >= B_8) break;
          }
      }
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"static ", 7L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)"_tProcTree yyI [", 16L);
      Tree_WN((LONGINT)(Sets_Maximum(&InhIndices) + 1));
      IO_WriteS(Tree_f, (STRING)"] = { 0,", 8L);
      IO_WriteNl(Tree_f);
      {
        SHORTCARD B_9 = 1, B_10 = Sets_Maximum(&InhIndices);

        if (B_9 <= B_10)
          for (i = B_9;; i += 1) {
            if (Sets_IsElement((Sets_tElement)i, &InhIndices)) {
              IO_WriteS(Tree_f, (STRING)" yyI", 4L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)",", 1L);
              IO_WriteNl(Tree_f);
            } else {
              IO_WriteS(Tree_f, (STRING)" 0,", 3L);
              IO_WriteNl(Tree_f);
            }
            if (i >= B_10) break;
          }
      }
      IO_WriteS(Tree_f, (STRING)"};", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"static void yyAbort", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (yyt) ", 7L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (void) fprintf (stderr, \"Error: module ", 40L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)", cyclic dependencies\\n\");", 26L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)"_Exit ();", 9L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void ", 5L);
      Tree_WI(W_3->EvalName);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (yyt) ", 7L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"{ Init", 6L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt); yyE (yyt); }", 20L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" char xxHigh;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" xxStack = 1000000000;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" Init", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt); yyE (yyt);", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (void) printf (\"Stacksize %d\\n\", (int) & xxHigh - xxStack);", 60L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      do {
        IsStable = TRUE;
        Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)CompOutput);
      } while (!IsStable);
      IO_WriteS(Tree_f, (STRING)"static void yyE", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (register ", 11L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (yyt) register ", 16L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.LocalLine);
      Texts_WriteText(Tree_f, Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.Local);
      Node = Tree_TreeRoot->U_1.V_26.Ag.Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      if (Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" char xxLow;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" xxStack = Min (xxStack, (int) & xxLow);", 40L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  if (yyt == ", 13L);
      Tree_WI(Tree_iNoTree);
      IO_WriteS(Tree_f, (STRING)" || yyt->yyHead.yyIsComp0 & 1) return;", 38L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  yyt->yyHead.yyIsComp0 |= 1;", 29L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)GenE);
      IO_WriteS(Tree_f, (STRING)"  default: return;", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  }", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" }", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      {
        SHORTCARD B_11 = 2, B_12 = MaxBit;

        if (B_11 <= B_12)
          for (i = B_11;; i += 1) {
            n = 0;
            Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)CountSynAttr);
            if (n > 0) {
              IO_WriteS(Tree_f, (STRING)"static void yyS", 15L);
              Tree_WN((LONGINT)(i - 1));
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" (register ", 11L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# else", 6L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" (yyt) register ", 16L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# endif", 7L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"{", 1L);
              IO_WriteNl(Tree_f);
              TreeC2_WriteLine(Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.LocalLine);
              Texts_WriteText(Tree_f, Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.Local);
              Node = Tree_TreeRoot->U_1.V_26.Ag.Modules;
              while (Node->U_1.V_1.Kind == Tree_Module) {
                TreeC2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
                Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
                Node = Node->U_1.V_43.Module.Next;
              }
              if (Sets_IsElement(ORD('9'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)" char xxLow;", 12L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)" xxStack = Min (xxStack, (int) & xxLow);", 40L);
                IO_WriteNl(Tree_f);
              }
              if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)" IFNOTIN (", 10L);
                Tree_WN((LONGINT)((i - 1) % TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)", yyt->yyHead.yyIsDone", 22L);
                Tree_WN((LONGINT)((i - 1) / TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)") INCL (yyt->yyHead.yyIsDone", 28L);
                Tree_WN((LONGINT)((i - 1) / TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WN((LONGINT)((i - 1) % TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)"); } else yyAbort (yyt);", 24L);
                IO_WriteNl(Tree_f);
              }
              if (n > 1) {
                IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
                IO_WriteNl(Tree_f);
                Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)GenS);
                IO_WriteS(Tree_f, (STRING)" }", 2L);
                IO_WriteNl(Tree_f);
              } else {
                Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)GenS);
              }
              IO_WriteS(Tree_f, (STRING)" INCL (yyt->yyHead.yyIsComp", 27L);
              Tree_WN((LONGINT)((i - 1) / TreeC1_BSS));
              IO_WriteS(Tree_f, (STRING)", ", 2L);
              Tree_WN((LONGINT)((i - 1) % TreeC1_BSS));
              IO_WriteS(Tree_f, (STRING)");", 2L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"}", 1L);
              IO_WriteNl(Tree_f);
              IO_WriteNl(Tree_f);
            }
            if (i >= B_12) break;
          }
      }
      {
        SHORTCARD B_13 = Sets_Minimum(&InhIndices), B_14 = Sets_Maximum(&InhIndices);

        if (B_13 <= B_14)
          for (i = B_13;; i += 1) {
            if (Sets_IsElement((Sets_tElement)i, &InhIndices)) {
              IO_WriteS(Tree_f, (STRING)"static void yyI", 15L);
              Tree_WN((LONGINT)i);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" (register ", 11L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# else", 6L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" (yyt) register ", 16L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# endif", 7L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"{", 1L);
              IO_WriteNl(Tree_f);
              TreeC2_WriteLine(Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.LocalLine);
              Texts_WriteText(Tree_f, Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.Local);
              Node = Tree_TreeRoot->U_1.V_26.Ag.Modules;
              while (Node->U_1.V_1.Kind == Tree_Module) {
                TreeC2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
                Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
                Node = Node->U_1.V_43.Module.Next;
              }
              if (Sets_IsElement(ORD('9'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)" char xxLow;", 12L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)" xxStack = Min (xxStack, (int) & xxLow);", 40L);
                IO_WriteNl(Tree_f);
              }
              Check = 0;
              if (InhIndexCount->A[i - 1] > 1) {
                IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
                IO_WriteNl(Tree_f);
                Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)EvalC3_EvalImplC);
                IO_WriteS(Tree_f, (STRING)" }", 2L);
                IO_WriteNl(Tree_f);
              } else {
                Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)EvalC3_EvalImplC);
              }
              if (Check != InhIndexCount->A[i - 1]) {
                Errors_MessageI((STRING)"internal error in yyI", 21L, (LONGCARD)Errors_Error, Positions_NoPosition, (LONGCARD)Errors_Short, ADR(i));
              }
              IO_WriteS(Tree_f, (STRING)"}", 1L);
              IO_WriteNl(Tree_f);
              IO_WriteNl(Tree_f);
            }
            if (i >= B_14) break;
          }
      }
      IO_WriteS(Tree_f, (STRING)"void Begin", 10L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Begin);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void Close", 10L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Close);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Class:;
    {
      register struct S_5 *W_4 = &yyTempo.U_1.V_1.yyR2;

      for (;;) {
        {
          register Tree_yClass *W_5 = &t->U_1.V_5.Class;

          if (!((Tree_NoCodeClass & W_5->Properties) == 0X0L)) {
            goto EXIT_1;
          }
          if (!(i <= W_5->InstCount)) {
            goto EXIT_1;
          }
          W_4->a = ToAttr(t, (LONGINT)i);
          if (W_4->a == 0) {
            return;
          }
          {
            register Tree_tInstance *W_6 = &W_5->Instance->A[W_4->a - 1];

            if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_6->Properties)) {
              EvalC_Class = t;
              if (InhIndexCount->A[i - 1] > 1) {
                IO_WriteS(Tree_f, (STRING)"  case k", 8L);
                Tree_WI(W_5->Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                IO_WriteNl(Tree_f);
              }
              INC(Check);
              k = ToBit1(W_6->Selector, (LONGINT)(W_4->a - W_5->AttrCount - W_6->Selector->U_1.V_9.Child.InstOffset));
              if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)" IFNOTIN (", 10L);
                Tree_WN((LONGINT)(k % TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)", yyt->", 7L);
                Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
                IO_WriteS(Tree_f, (STRING)".", 1L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"->yyHead.yyIsDone", 17L);
                Tree_WN((LONGINT)(k / TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)") INCL (yyt->", 13L);
                Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
                IO_WriteS(Tree_f, (STRING)".", 1L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"->yyHead.yyIsDone", 17L);
                Tree_WN((LONGINT)(k / TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WN((LONGINT)(k % TreeC1_BSS));
                IO_WriteS(Tree_f, (STRING)"); } else yyAbort (yyt);", 24L);
                IO_WriteNl(Tree_f);
              }
              {
                SHORTCARD B_15 = 1, B_16 = W_5->InstCount;

                if (B_15 <= B_16)
                  for (j = B_15;; j += 1) {
                    if (Relations_IsRelated((LONGINT)W_4->a, (LONGINT)j, W_5->DP)) {
                      GenCall(t, j);
                    }
                    if (j >= B_16) break;
                  }
              }
              if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\");", 3L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action) && !IN(Tree_Virtual, W_6->Properties)) {
                  EvalC_GenEvaluator(W_6->Action);
                  IO_WriteNl(Tree_f);
                  if (W_6->Attribute->U_1.V_1.Kind == Tree_Child || W_6->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                    IO_WriteS(Tree_f, (STRING)"write", 5L);
                    Tree_WI(Tree_itTree);
                    IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
                    Tree_WI(W_5->Name);
                    IO_WriteS(Tree_f, (STRING)".", 1L);
                    Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)"->", 2L);
                    Tree_WI(W_6->Selector->U_1.V_9.Child.Type);
                    IO_WriteS(Tree_f, (STRING)".", 1L);
                    Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)")", 1L);
                    IO_WriteNl(Tree_f);
                  } else {
                    IO_WriteS(Tree_f, (STRING)"write", 5L);
                    Tree_WI(W_6->Attribute->U_1.V_9.Child.Type);
                    IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
                    Tree_WI(W_5->Name);
                    IO_WriteS(Tree_f, (STRING)".", 1L);
                    Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)"->", 2L);
                    Tree_WI(W_6->Selector->U_1.V_9.Child.Type);
                    IO_WriteS(Tree_f, (STRING)".", 1L);
                    Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)") yyWriteNl ();", 15L);
                    IO_WriteNl(Tree_f);
                  }
                } else {
                  IO_WriteS(Tree_f, (STRING)"yyWriteNl ();", 13L);
                  IO_WriteNl(Tree_f);
                }
              } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\");", 3L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action) && !IN(Tree_Virtual, W_6->Properties)) {
                  EvalC_GenEvaluator(W_6->Action);
                }
              } else {
                if (W_6->Action != ADR(W_6->Action) && !IN(Tree_Virtual, W_6->Properties)) {
                  EvalC_GenEvaluator(W_6->Action);
                }
              }
              if (!IN(Tree_Input, W_6->Properties) && W_6->Attribute->U_1.V_1.Kind == Tree_Child) {
                IO_WriteS(Tree_f, (STRING)"{ register ", 11L);
                Tree_WI(Tree_itTree);
                IO_WriteS(Tree_f, (STRING)" yyr = yyt->", 12L);
                Tree_WI(W_5->Name);
                IO_WriteS(Tree_f, (STRING)".", 1L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"->", 2L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Type);
                IO_WriteS(Tree_f, (STRING)".", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"; if (yyr->yyHead.yyParent == ", 30L);
                Tree_WI(Tree_iNoTree);
                IO_WriteS(Tree_f, (STRING)") { yyr->yyHead.yyOffset = ", 27L);
                Tree_WN((LONGINT)(W_6->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.BitCount + W_6->Attribute->U_1.V_9.Child.BitOffset));
                IO_WriteS(Tree_f, (STRING)"; yyr->yyHead.yyParent = yyt->", 30L);
                Tree_WI(W_5->Name);
                IO_WriteS(Tree_f, (STRING)".", 1L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"; Init", 6L);
                Tree_WI(Tree_iModule);
                IO_WriteS(Tree_f, (STRING)" (yyr); } }", 11L);
                IO_WriteNl(Tree_f);
              }
              {
                SHORTCARD B_17 = 1, B_18 = W_5->InstCount;

                if (B_17 <= B_18)
                  for (i2 = B_17;; i2 += 1) {
                    if (W_5->Instance->A[i2 - 1].Action == W_6->Action) {
                      {
                        register Tree_tInstance *W_7 = &W_5->Instance->A[i2 - 1];

                        if (IN(Tree_Synthesized, W_7->Properties)) {
                          k = EvalC3_ToBit0(EvalC_Class, (LONGINT)i2);
                          IO_WriteS(Tree_f, (STRING)"  INCL (yyt->yyHead.yyIsComp", 28L);
                          Tree_WN((LONGINT)(k / TreeC1_BSS));
                          IO_WriteS(Tree_f, (STRING)", ", 2L);
                          Tree_WN((LONGINT)(k % TreeC1_BSS));
                          IO_WriteS(Tree_f, (STRING)");", 2L);
                          IO_WriteNl(Tree_f);
                        } else if (IN(Tree_Inherited, W_7->Properties)) {
                          k = ToBit1(W_7->Selector, (LONGINT)(i2 - W_5->AttrCount - W_7->Selector->U_1.V_9.Child.InstOffset));
                          IO_WriteS(Tree_f, (STRING)"  INCL (yyt->", 13L);
                          Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
                          IO_WriteS(Tree_f, (STRING)".", 1L);
                          Tree_WI(W_7->Selector->U_1.V_9.Child.Name);
                          IO_WriteS(Tree_f, (STRING)"->yyHead.yyIsComp", 17L);
                          Tree_WN((LONGINT)(k / TreeC1_BSS));
                          IO_WriteS(Tree_f, (STRING)", ", 2L);
                          Tree_WN((LONGINT)(k % TreeC1_BSS));
                          IO_WriteS(Tree_f, (STRING)");", 2L);
                          IO_WriteNl(Tree_f);
                        }
                      }
                    }
                    if (i2 >= B_18) break;
                  }
              }
              IO_WriteS(Tree_f, (STRING)" return;", 8L);
              IO_WriteNl(Tree_f);
            }
          }
          return;
        }
      } EXIT_1:;
    }
    break;
  default :
    break;
  }
}

static void CompBitInfo
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
      register Tree_yClass *W_8 = &t->U_1.V_5.Class;

      BitIndexSize = W_8->AttrCount;
      DynArray_MakeArray((ADDRESS *)&W_8->BitIndex, &BitIndexSize, (LONGINT)sizeof(Tree_tBitInfo));
      i = 1;
      gBitIndex = W_8->BitIndex;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CompBitInfo);
      MaxBit = General_Max((LONGINT)i, (LONGINT)MaxBit);
      MaxInstCount = General_Max((LONGINT)W_8->InstCount, (LONGINT)MaxInstCount);
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_9 = &t->U_1.V_9.Child;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_9->Properties) == 0X0L)) {
          goto EXIT_2;
        }
        INC(i);
        gBitIndex->A[W_9->AttrIndex - 1].ToBit = i;
        gBitIndex->A[i - 1].ToAttr = W_9->AttrIndex;
        return;
      }
    } EXIT_2:;
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_10 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_10->Properties) == 0X0L)) {
          goto EXIT_3;
        }
        INC(i);
        gBitIndex->A[W_10->AttrIndex - 1].ToBit = i;
        gBitIndex->A[i - 1].ToAttr = W_10->AttrIndex;
        return;
      }
    } EXIT_3:;
    break;
  default :
    break;
  }
}

static void CompInhIndices
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register struct S_8 *W_11 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yClass *W_12 = &t->U_1.V_5.Class;

        {
          SHORTCARD B_19 = W_12->AttrCount + 1, B_20 = W_12->InstCount;

          if (B_19 <= B_20)
            for (j = B_19;; j += 1) {
              {
                register Tree_tInstance *W_13 = &W_12->Instance->A[j - 1];

                if (IN(Tree_Inherited, W_13->Properties)) {
                  W_11->b = ToBit2(t, W_13->Selector, j);
                  Sets_Include(&InhIndices, (Sets_tElement)W_11->b);
                  INC(InhIndexCount->A[W_11->b - 1]);
                }
              }
              if (j >= B_20) break;
            }
        }
        return;
      }
    }
  }
}

static void CountSynAttr
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    for (;;) {
      {
        register Tree_yClass *W_14 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_14->Properties) == 0X0L)) {
          goto EXIT_4;
        }
        if (!(i <= W_14->BitCount)) {
          goto EXIT_4;
        }
        {
          register Tree_tInstance *W_15 = &W_14->Instance->A[W_14->BitIndex->A[i - 1].ToAttr - 1];

          if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_15->Properties) && !IN(Tree_Test, W_15->Properties)) {
            INC(n);
          }
        }
        return;
      }
    } EXIT_4:;
  }
}

static void TypeName
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
    for (;;) {
      {
        register Tree_yClass *W_16 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_16->Properties) == 0X0L)) {
          goto EXIT_5;
        }
        if (!IN(Tree_Trace, W_16->Properties)) {
          goto EXIT_5;
        }
        IO_WriteS(Tree_f, (STRING)"\"", 1L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)"\",", 2L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_5:;
  }
}

static void GenS
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    for (;;) {
      {
        register Tree_yClass *W_17 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_17->Properties) == 0X0L)) {
          goto EXIT_6;
        }
        if (!(i <= W_17->BitCount)) {
          goto EXIT_6;
        }
        {
          register Tree_tInstance *W_18 = &W_17->Instance->A[W_17->BitIndex->A[i - 1].ToAttr - 1];

          if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_18->Properties) && !IN(Tree_Test, W_18->Properties)) {
            EvalC_Class = t;
            if (n > 1) {
              IO_WriteS(Tree_f, (STRING)" case k", 7L);
              Tree_WI(W_17->Name);
              IO_WriteS(Tree_f, (STRING)":", 1L);
              IO_WriteNl(Tree_f);
            }
            {
              SHORTCARD B_21 = 1, B_22 = W_17->InstCount;

              if (B_21 <= B_22)
                for (j = B_21;; j += 1) {
                  if (Relations_IsRelated((LONGINT)W_17->BitIndex->A[i - 1].ToAttr, (LONGINT)j, W_17->DP)) {
                    GenCall(t, j);
                  }
                  if (j >= B_22) break;
                }
            }
            GenEvalAttr(t, (LONGINT)W_17->BitIndex->A[i - 1].ToAttr);
            if (!IN(Tree_Input, W_18->Properties) && W_18->Attribute->U_1.V_1.Kind == Tree_Child) {
              IO_WriteS(Tree_f, (STRING)"{ register ", 11L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyr = yyt->", 12L);
              Tree_WI(W_17->Name);
              IO_WriteS(Tree_f, (STRING)".", 1L);
              Tree_WI(W_18->Attribute->U_1.V_9.Child.Name);
              IO_WriteS(Tree_f, (STRING)"; if (yyr->yyHead.yyParent == ", 30L);
              Tree_WI(Tree_iNoTree);
              IO_WriteS(Tree_f, (STRING)") { yyr->yyHead.yyOffset = ", 27L);
              Tree_WN((LONGINT)(W_17->BitCount + W_18->Attribute->U_1.V_9.Child.BitOffset));
              IO_WriteS(Tree_f, (STRING)"; yyr->yyHead.yyParent = yyt; Init", 34L);
              Tree_WI(Tree_iModule);
              IO_WriteS(Tree_f, (STRING)" (yyr); } }", 11L);
              IO_WriteNl(Tree_f);
            }
            {
              SHORTCARD B_23 = 1, B_24 = W_17->InstCount;

              if (B_23 <= B_24)
                for (i2 = B_23;; i2 += 1) {
                  if (W_17->Instance->A[i2 - 1].Action == W_18->Action) {
                    {
                      register Tree_tInstance *W_19 = &W_17->Instance->A[i2 - 1];

                      if (IN(Tree_Synthesized, W_19->Properties)) {
                        k = EvalC3_ToBit0(EvalC_Class, (LONGINT)i2);
                        if (k != i - 1) {
                          IO_WriteS(Tree_f, (STRING)"  INCL (yyt->yyHead.yyIsComp", 28L);
                          Tree_WN((LONGINT)(k / TreeC1_BSS));
                          IO_WriteS(Tree_f, (STRING)", ", 2L);
                          Tree_WN((LONGINT)(k % TreeC1_BSS));
                          IO_WriteS(Tree_f, (STRING)");", 2L);
                          IO_WriteNl(Tree_f);
                        }
                      } else if (IN(Tree_Inherited, W_19->Properties)) {
                        k = ToBit1(W_19->Selector, (LONGINT)(i2 - W_17->AttrCount - W_19->Selector->U_1.V_9.Child.InstOffset));
                        IO_WriteS(Tree_f, (STRING)"  INCL (yyt->", 13L);
                        Tree_WI(EvalC_Class->U_1.V_5.Class.Name);
                        IO_WriteS(Tree_f, (STRING)".", 1L);
                        Tree_WI(W_19->Selector->U_1.V_9.Child.Name);
                        IO_WriteS(Tree_f, (STRING)"->yyHead.yyIsComp", 17L);
                        Tree_WN((LONGINT)(k / TreeC1_BSS));
                        IO_WriteS(Tree_f, (STRING)", ", 2L);
                        Tree_WN((LONGINT)(k % TreeC1_BSS));
                        IO_WriteS(Tree_f, (STRING)");", 2L);
                        IO_WriteNl(Tree_f);
                      }
                    }
                  }
                  if (i2 >= B_24) break;
                }
            }
            if (n > 1) {
              IO_WriteS(Tree_f, (STRING)"  break;", 8L);
              IO_WriteNl(Tree_f);
            }
          }
        }
        return;
      }
    } EXIT_6:;
  }
}

static void GenE
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register struct S_13 *W_20 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yClass *W_21 = &t->U_1.V_5.Class;

        TreeC2_GetIterator(t);
        n = 0;
        j = 2;
        for (;;) {
          if (j > W_21->InstCount) {
            goto EXIT_7;
          }
          {
            register Tree_tInstance *W_22 = &W_21->Instance->A[j - 1];

            if (((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Output) | SET_ELEM(Tree_Test)) & W_22->Properties) != 0X0L) {
              if (IN(Tree_Test, W_22->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_22->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_22->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_22->Properties) && !IN(Tree_Input, W_22->Properties) && W_22->Attribute->U_1.V_1.Kind == Tree_Child || SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_Dummy), W_22->Properties) && W_22->Selector != TreeC2_Iterator && IN(Tree_HasOutput, W_22->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Properties)) {
                INC(n);
                goto EXIT_7;
              }
            }
          }
          INC(j);
        } EXIT_7:;
        if (n == 0 && (TreeC2_Iterator == Tree_NoTree || !IN(Tree_HasOutput, TreeC2_Iterator->U_1.V_9.Child.Class->U_1.V_5.Class.Properties))) {
          return;
        }
        EvalC_Class = t;
        IO_WriteS(Tree_f, (STRING)"  case k", 8L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        {
          SHORTCARD B_25 = 2, B_26 = W_21->InstCount;

          if (B_25 <= B_26)
            for (j = B_25;; j += 1) {
              {
                register Tree_tInstance *W_23 = &W_21->Instance->A[j - 1];

                if (((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Output)) & W_23->Properties) != 0X0L) {
                  if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_23->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_23->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_23->Properties) && !IN(Tree_Input, W_23->Properties) && W_23->Attribute->U_1.V_1.Kind == Tree_Child) {
                    GenCall(t, j);
                  } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_Dummy), W_23->Properties) && W_23->Selector != TreeC2_Iterator && IN(Tree_HasOutput, W_23->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Properties)) {
                    if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                      IO_WriteS(Tree_f, (STRING)"yyWriteVisit (yyt, \"", 20L);
                      Tree_WI(W_23->Selector->U_1.V_9.Child.Name);
                      IO_WriteS(Tree_f, (STRING)"\"); ", 4L);
                    }
                    IO_WriteS(Tree_f, (STRING)"yyE (yyt->", 10L);
                    Tree_WI(W_21->Name);
                    IO_WriteS(Tree_f, (STRING)".", 1L);
                    Tree_WI(W_23->Selector->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)");", 2L);
                    IO_WriteNl(Tree_f);
                    if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                      IO_WriteS(Tree_f, (STRING)"yyVisitParent (yyt->", 20L);
                      Tree_WI(W_21->Name);
                      IO_WriteS(Tree_f, (STRING)".", 1L);
                      Tree_WI(W_23->Selector->U_1.V_9.Child.Name);
                      IO_WriteS(Tree_f, (STRING)");", 2L);
                      IO_WriteNl(Tree_f);
                    }
                  }
                }
              }
              if (j >= B_26) break;
            }
        }
        Sets_MakeSet(&W_20->ToCompute, (Sets_tElement)W_21->InstCount);
        {
          SHORTCARD B_27 = 2, B_28 = W_21->AttrCount;

          if (B_27 <= B_28)
            for (i = B_27;; i += 1) {
              {
                register Tree_tInstance *W_24 = &W_21->Instance->A[i - 1];

                if (IN(Tree_Test, W_24->Properties)) {
                  {
                    SHORTCARD B_29 = 2, B_30 = W_21->InstCount;

                    if (B_29 <= B_30)
                      for (j = B_29;; j += 1) {
                        if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_21->DP)) {
                          if (((SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Inherited)) & W_21->Instance->A[j - 1].Properties) != 0X0L) {
                            Sets_Include(&W_20->ToCompute, (Sets_tElement)j);
                          }
                        }
                        if (j >= B_30) break;
                      }
                  }
                }
              }
              if (i >= B_28) break;
            }
        }
        {
          SHORTCARD B_31 = 2, B_32 = W_21->InstCount;

          if (B_31 <= B_32)
            for (i = B_31;; i += 1) {
              {
                register Tree_tInstance *W_25 = &W_21->Instance->A[i - 1];

                if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left) | SET_ELEM(Tree_Output), W_25->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_Output), W_25->Properties)) {
                  Sets_Exclude(&W_20->ToCompute, (Sets_tElement)i);
                }
              }
              if (i >= B_32) break;
            }
        }
        while (!Sets_IsEmpty(W_20->ToCompute)) {
          GenCall(t, (SHORTCARD)Sets_Extract(&W_20->ToCompute));
        }
        Sets_ReleaseSet(&W_20->ToCompute);
        {
          SHORTCARD B_33 = 2, B_34 = W_21->AttrCount;

          if (B_33 <= B_34)
            for (i = B_33;; i += 1) {
              if (IN(Tree_Test, W_21->Instance->A[i - 1].Properties)) {
                GenEvalAttr(t, (LONGINT)i);
              }
              if (i >= B_34) break;
            }
        }
        if (TreeC2_Iterator == Tree_NoTree || !IN(Tree_HasOutput, TreeC2_Iterator->U_1.V_9.Child.Class->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)"return;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
            IO_WriteS(Tree_f, (STRING)"yyWriteVisit (yyt, \"", 20L);
            Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"\"); ", 4L);
          }
          IO_WriteS(Tree_f, (STRING)"yyt = yyt->", 11L);
          Tree_WI(W_21->Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)"; break;", 8L);
          IO_WriteNl(Tree_f);
        }
        return;
      }
    }
  }
}

static void CompOutput
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
    for (;;) {
      {
        register Tree_yClass *W_26 = &t->U_1.V_5.Class;

        if (!!IN(Tree_HasOutput, W_26->Properties)) {
          goto EXIT_8;
        }
        Success = FALSE;
        Tree_ForallAttributes(t, (Tree_ProcOfT)CompOutput);
        Tree_ForallClasses(W_26->Extensions, (Tree_ProcOfT)CompOutput2);
        if (!Success) {
          goto EXIT_8;
        }
        INCL(W_26->Properties, Tree_HasOutput);
        IsStable = FALSE;
        return;
      }
    } EXIT_8:;
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_27 = &t->U_1.V_9.Child;

        if (!(IN(Tree_Output, W_27->Properties) || IN(Tree_HasOutput, W_27->Class->U_1.V_5.Class.Properties))) {
          goto EXIT_9;
        }
        Success = TRUE;
        return;
      }
    } EXIT_9:;
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_28 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Output)) & W_28->Properties) != 0X0L)) {
          goto EXIT_10;
        }
        Success = TRUE;
        return;
      }
    } EXIT_10:;
    break;
  default :
    break;
  }
}

static void CompOutput2
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    for (;;) {
      {
        register Tree_yClass *W_29 = &t->U_1.V_5.Class;

        if (!IN(Tree_HasOutput, W_29->Properties)) {
          goto EXIT_11;
        }
        Success = TRUE;
        return;
      }
    } EXIT_11:;
  }
}

INTEGER EvalC3_ToBit0
# ifdef __STDC__
(Tree_tTree yyP2, INTEGER yyP1)
# else
(yyP2, yyP1)
Tree_tTree yyP2;
INTEGER yyP1;
# endif
{
  struct S_16 yyTempo;

  return yyP2->U_1.V_5.Class.BitIndex->A[yyP1 - 1].ToBit - 1;
}

static INTEGER ToBit1
# ifdef __STDC__
(Tree_tTree yyP4, INTEGER yyP3)
# else
(yyP4, yyP3)
Tree_tTree yyP4;
INTEGER yyP3;
# endif
{
  struct S_17 yyTempo;

  return yyP4->U_1.V_9.Child.Class->U_1.V_5.Class.BitIndex->A[yyP3 - 1].ToBit - 1;
}

static INTEGER ToBit2
# ifdef __STDC__
(Tree_tTree yyP7, Tree_tTree yyP6, SHORTCARD yyP5)
# else
(yyP7, yyP6, yyP5)
Tree_tTree yyP7;
Tree_tTree yyP6;
SHORTCARD yyP5;
# endif
{
  struct S_18 yyTempo;

  {
    register struct S_19 *W_30 = &yyTempo.U_1.V_1.yyR1;

    {
      register Tree_yChild *W_31 = &yyP6->U_1.V_9.Child;

      return yyP7->U_1.V_5.Class.BitCount + W_31->BitOffset + W_31->Class->U_1.V_5.Class.BitIndex->A[yyP5 - yyP7->U_1.V_5.Class.AttrCount - W_31->InstOffset - 1].ToBit - 1;
    }
    return W_30->yyV1;
  }
}

static INTEGER ToAttr
# ifdef __STDC__
(Tree_tTree yyP9, INTEGER yyP8)
# else
(yyP9, yyP8)
Tree_tTree yyP9;
INTEGER yyP8;
# endif
{
  SHORTCARD a;
  struct S_20 yyTempo;

  {
    register struct S_21 *W_32 = &yyTempo.U_1.V_1.yyR1;

    {
      register Tree_yClass *W_33 = &yyP9->U_1.V_5.Class;

      {
        SHORTCARD B_35 = W_33->AttrCount + 1, B_36 = W_33->InstCount;

        if (B_35 <= B_36)
          for (a = B_35;; a += 1) {
            {
              register Tree_tInstance *W_34 = &W_33->Instance->A[a - 1];

              if (((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_34->Properties) == 0X0L && ToBit2(yyP9, W_34->Selector, a) == yyP8) {
                return a;
              }
            }
            if (a >= B_36) break;
          }
      }
    }
    return 0;
    return W_32->yyV1;
  }
}

void EvalC3_BeginEvalC3
# ifdef __STDC__
()
# else
()
# endif
{
}

void EvalC3_CloseEvalC3
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

void EvalC3__init()
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
    Texts__init();
    Sets__init();
    Relations__init();
    TreeC1__init();
    TreeC2__init();
    EvalC__init();
    Errors__init();
    Positions__init();
    EvalC__init();
    Tree__init();

    EvalC3_yyf = IO_StdOutput;
    EvalC3_Exit = yyExit;
    EvalC3_BeginEvalC3();
  }
}
