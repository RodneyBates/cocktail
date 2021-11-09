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

#ifndef DEFINITION_TreeMThree2
#include "TreeMThree2.h"
#endif

#ifndef DEFINITION_EvalMThree
#include "EvalMThree.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_EvalMThree
#include "EvalMThree.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_EvalMThree3
#include "EvalMThree3.h"
#endif

IO_tFile EvalMThree3_yyf;
PROC EvalMThree3_Exit;

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
static void GenS ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void GenE ARGS((Tree_tTree t));
struct S_11 {
    union {
        struct {
            struct S_12 {
                Sets_tSet ToCompute;
            } yyR1;
        } V_1;
    } U_1;
};
static void CompOutput ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void CompOutput2 ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static INTEGER ToBit1 ARGS((Tree_tTree yyP4, INTEGER yyP3));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static INTEGER ToBit2 ARGS((Tree_tTree yyP7, Tree_tTree yyP6, SHORTCARD yyP5));
struct S_17 {
    union {
        struct {
            struct S_18 {
                INTEGER yyV1;
            } yyR1;
        } V_1;
    } U_1;
};
static INTEGER ToAttr ARGS((Tree_tTree yyP9, INTEGER yyP8));
struct S_19 {
    union {
        struct {
            struct S_20 {
                INTEGER yyV1;
            } yyR1;
        } V_1;
    } U_1;
};
static void GenEvaluator ARGS((Tree_tTree t));
struct S_21 {
    union {
        struct {
            struct S_22 {
                Tree_tTree TheClass;
                INTEGER k;
            } yyR9;
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
      k = EvalMThree3_ToBit0(t, (LONGINT)j);
      IO_WriteS(Tree_f, (STRING)"      IFNOTIN (", 15L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)", TNode . yyHead . yyIsComp ) ", 30L);
      IO_WriteS(Tree_f, (STRING)"yyS", 3L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)" ( TNode ) ; (* ", 16L);
      Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)" *) END;", 8L);
      IO_WriteNl(Tree_f);
    } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_1->Properties)) {
      k = EvalMThree3_ToBit0(t, (LONGINT)j);
      IO_WriteS(Tree_f, (STRING)"      IFNOTIN (", 15L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)" , TNode . yyHead . yyIsComp ) ", 31L);
      if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"      yyVisitParent ( TNode ) ; ", 32L);
        IO_WriteS(Tree_f, (STRING)"      yyI [ TNode . yyHead . yyOffset + ", 40L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)" ] ( TNode . yyHead . yyParent ) ; (* ", 38L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" *) ", 4L);
        IO_WriteS(Tree_f, (STRING)"      yyWriteVisit ( TNode . yyHead . yyParent , \"?\") ; END ;", 61L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"      yyI [ TNode . yyHead . yyOffset + ", 40L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)" ] ( TNode . yyHead . yyParent ) ; (* ", 38L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" *) END ;", 9L);
        IO_WriteNl(Tree_f);
      }
    } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_1->Properties)) {
      k = ToBit1(W_1->Selector, (LONGINT)(j - t->U_1.V_5.Class.AttrCount - W_1->Selector->U_1.V_9.Child.InstOffset));
      IO_WriteS(Tree_f, (STRING)"      IFNOTIN (", 15L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)" , TNode . ", 11L);
      Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)" . yyHead.yyIsComp ) ", 21L);
      k = ToBit2(t, W_1->Selector, j);
      IO_WriteS(Tree_f, (STRING)"      yyI", 9L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)" ( TNode ) ; (* ", 16L);
      Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)":", 1L);
      Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)" *) END ;", 9L);
      IO_WriteNl(Tree_f);
    } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right), W_1->Properties)) {
      k = ToBit1(W_1->Selector, (LONGINT)(j - t->U_1.V_5.Class.AttrCount - W_1->Selector->U_1.V_9.Child.InstOffset));
      IO_WriteS(Tree_f, (STRING)"      IFNOTIN (", 15L);
      Tree_WN((LONGINT)k);
      IO_WriteS(Tree_f, (STRING)" , TNode . ", 11L);
      Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)" . yyHead . yyIsComp ) ", 23L);
      if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"      yyWriteVisit ( TNode , \"", 30L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      yyS", 9L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" ) ; (* ", 8L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" *) ", 4L);
        IO_WriteS(Tree_f, (STRING)"      yyVisitParent ( TNode . ", 30L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" ) ; END ;", 10L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"      yyS", 9L);
        Tree_WN((LONGINT)k);
        IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" ) ; (* ", 8L);
        Tree_WI(W_1->Selector->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_1->Attribute->U_1.V_9.Child.Name);
        IO_WriteS(Tree_f, (STRING)" *) END ;", 9L);
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
  EvalMThree_Class = t;
  {
    register Tree_tInstance *W_2 = &t->U_1.V_5.Class.Instance->A[i - 1];

    if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
      IO_WriteS(Tree_f, (STRING)"      yyWriteEval ( TNode , \"", 29L);
      Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
      IO_WriteNl(Tree_f);
      if (W_2->Action != ADR(W_2->Action) && !IN(Tree_Virtual, W_2->Properties)) {
        GenEvaluator(W_2->Action);
        EvalMThree_GenEvaluator(W_2->Action);
        IO_WriteNl(Tree_f);
        if (IN(Tree_Test, W_2->Properties)) {
          IO_WriteS(Tree_f, (STRING)"      writeBOOLEAN ( yyb ) yyWriteNl ( ) ;", 42L);
          IO_WriteNl(Tree_f);
        } else if (W_2->Attribute->U_1.V_1.Kind == Tree_Child || W_2->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
          IO_WriteS(Tree_f, (STRING)"      write", 11L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
          Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" )", 2L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"      write", 11L);
          Tree_WI(W_2->Attribute->U_1.V_9.Child.Type);
          IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
          Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ) yyWriteNl ( ) ;", 18L);
          IO_WriteNl(Tree_f);
        }
      } else {
        IO_WriteS(Tree_f, (STRING)"      yyWriteNl ( ) ;", 21L);
        IO_WriteNl(Tree_f);
      }
    } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
      IO_WriteS(Tree_f, (STRING)"      yyWriteEval ( TNode , \"", 29L);
      Tree_WI(W_2->Attribute->U_1.V_9.Child.Name);
      IO_WriteS(Tree_f, (STRING)"\") ;", 4L);
      IO_WriteNl(Tree_f);
      if (W_2->Action != ADR(W_2->Action) && !IN(Tree_Virtual, W_2->Properties)) {
        GenEvaluator(W_2->Action);
        EvalMThree_GenEvaluator(W_2->Action);
      }
    } else {
      if (W_2->Action != ADR(W_2->Action) && !IN(Tree_Virtual, W_2->Properties)) {
        GenEvaluator(W_2->Action);
        EvalMThree_GenEvaluator(W_2->Action);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module EvalMThree3, routine ", 35L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*EvalMThree3_Exit)();
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

void EvalMThree3_EvalModule
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
      IO_WriteS(Tree_f, (STRING)"# define IFNOTIN(b, s) IF NOT ((b) IN (s)) THEN", 47L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define REMOTE_SYN(i, b, c, n, t, a) n.t.a", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define REMOTE_INH(i, b, k, n, t, a) n.t.a", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define INCLUDE(s, b) WITH yyTemp = ( s ) DO yyTemp := yyTemp + ", 65L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" . BitSet { b } END ;", 21L);
      IO_WriteNl(Tree_f);
      EvalMThree_EvalModuleHead(t);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyI: ARRAY [0 .. ", 21L);
      Tree_WN((LONGINT)Sets_Maximum(&InhIndices));
      IO_WriteS(Tree_f, (STRING)"] OF ", 5L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)".tProcTree;", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyAbort (yyt: ", 24L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" )", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . Stderr, \"Error: module ", 48L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)", cyclic dependencies\" ) ;", 26L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . Stderr , Wr . EOL ) ;", 46L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" . yyExit ( ) ;", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyAbort;", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval ( yyt : ", 23L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . Init", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( yyt ) ; yyE ( yyt ) ; END Eval ;", 35L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR xxStack : INTEGER ;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval ( yyt : ", 23L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"= VAR xxHigh : BOOLEAN ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    xxStack := LAST ( INTEGER ) ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ", 4L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . Init", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( yyt ) ; yyE ( yyt ) ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( Stdio . Stdout , \"Stacksize \" ) ;", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( Stdio . Stdout", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               , Fmt . Int ( LOOPHOLE ( ADR ( xxHigh ) , INTEGER ) - xxStack ) ) ;", 82L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( Stdio . Stdout , Wr . EOL );", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Eval ;", 12L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      do {
        IsStable = TRUE;
        Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)CompOutput);
      } while (!IsStable);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyE ( yyt : ", 22L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" ) =", 4L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.LocalLine);
      Texts_WriteText(Tree_f, Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.Local);
      Node = Tree_TreeRoot->U_1.V_26.Ag.Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      if (Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"  VAR xxLow : BOOLEAN ;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    xxStack := MIN ( xxStack , LOOPHOLE ( ADR ( xxLow ) , INTEGER ) ) ;", 71L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    IF ( yyt = ", 15L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(Tree_iNoTree);
      IO_WriteS(Tree_f, (STRING)" ) OR ( 0 IN yyt . yyHead . yyIsComp ) THEN RETURN ; END ;", 58L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    INCLUDE ( yyt . yyHead . yyIsComp , 0 )", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    TYPECASE yyt OF", 19L);
      IO_WriteNl(Tree_f);
      Tree_ForallClassesExtensionsFirst(W_3->Classes, (Tree_ProcOfT)GenE);
      IO_WriteS(Tree_f, (STRING)"    ELSE RETURN ;", 17L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    END ;", 9L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"   END ;", 8L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END yyE ;", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      {
        SHORTCARD B_5 = 2, B_6 = MaxBit;

        if (B_5 <= B_6)
          for (i = B_5;; i += 1) {
            n = 0;
            Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)CountSynAttr);
            if (n > 0) {
              IO_WriteS(Tree_f, (STRING)"PROCEDURE yyS", 13L);
              Tree_WN((LONGINT)(i - 1));
              IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
              Tree_WI(Tree_iMain);
              IO_WriteS(Tree_f, (STRING)" . ", 3L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" )=", 3L);
              IO_WriteNl(Tree_f);
              TreeMThree2_WriteLine(Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.LocalLine);
              Texts_WriteText(Tree_f, Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.Local);
              Node = Tree_TreeRoot->U_1.V_26.Ag.Modules;
              while (Node->U_1.V_1.Kind == Tree_Module) {
                TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
                Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
                Node = Node->U_1.V_43.Module.Next;
              }
              if (Sets_IsElement(ORD('9'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"  VAR xxLow : BOOLEAN ;", 23L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"    xxStack := MIN ( xxStack , LOOPHOLE ( ADR ( xxLow ) , INTEGER ) ) ;", 71L);
                IO_WriteNl(Tree_f);
              } else {
                IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
                IO_WriteNl(Tree_f);
              }
              if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"    IFNOTIN (", 13L);
                Tree_WN((LONGINT)(i - 1));
                IO_WriteS(Tree_f, (STRING)", yyt . yyHead . yyIsDone )", 27L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"    INCLUDE  (yyt . yyHead . yyIsDone, ", 39L);
                Tree_WN((LONGINT)(i - 1));
                IO_WriteS(Tree_f, (STRING)" )", 2L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"    ELSE yyAbort ( yyt ) ; END ;", 32L);
                IO_WriteNl(Tree_f);
              }
              if (n > 1) {
                IO_WriteS(Tree_f, (STRING)"    TYPECASE yyt OF", 19L);
                IO_WriteNl(Tree_f);
                Tree_ForallClassesExtensionsFirst(W_3->Classes, (Tree_ProcOfT)GenS);
                IO_WriteS(Tree_f, (STRING)"    END ;", 9L);
                IO_WriteNl(Tree_f);
              } else {
                Tree_ForallClassesExtensionsFirst(W_3->Classes, (Tree_ProcOfT)GenS);
              }
              IO_WriteS(Tree_f, (STRING)"    INCLUDE ( yyt . yyHead . yyIsComp , ", 40L);
              Tree_WN((LONGINT)(i - 1));
              IO_WriteS(Tree_f, (STRING)" )", 2L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"  END yyS", 9L);
              Tree_WN((LONGINT)(i - 1));
              IO_WriteS(Tree_f, (STRING)" ;", 2L);
              IO_WriteNl(Tree_f);
              IO_WriteNl(Tree_f);
            }
            if (i >= B_6) break;
          }
      }
      {
        SHORTCARD B_7 = Sets_Minimum(&InhIndices), B_8 = Sets_Maximum(&InhIndices);

        if (B_7 <= B_8)
          for (i = B_7;; i += 1) {
            if (Sets_IsElement((Sets_tElement)i, &InhIndices)) {
              IO_WriteS(Tree_f, (STRING)"PROCEDURE yyI", 13L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)"  (yyt : ", 9L);
              Tree_WI(Tree_iMain);
              IO_WriteS(Tree_f, (STRING)" . ", 3L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" )=", 3L);
              IO_WriteNl(Tree_f);
              TreeMThree2_WriteLine(Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.LocalLine);
              Texts_WriteText(Tree_f, Tree_TreeRoot->U_1.V_26.Ag.EvalCodes->U_1.V_12.Codes.Local);
              Node = Tree_TreeRoot->U_1.V_26.Ag.Modules;
              while (Node->U_1.V_1.Kind == Tree_Module) {
                TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
                Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
                Node = Node->U_1.V_43.Module.Next;
              }
              if (Sets_IsElement(ORD('9'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"  VAR xxLow : BOOLEAN ;", 23L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"    xxStack := MIN ( xxStack , LOOPHOLE ( ADR ( xxLow ) , INTEGER ) ) ;", 71L);
                IO_WriteNl(Tree_f);
              } else {
                IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
                IO_WriteNl(Tree_f);
              }
              Check = 0;
              if (InhIndexCount->A[i - 1] > 1) {
                IO_WriteS(Tree_f, (STRING)"    TYPECASE yyt  OF", 20L);
                IO_WriteNl(Tree_f);
                Tree_ForallClassesExtensionsFirst(W_3->Classes, (Tree_ProcOfT)EvalMThree3_EvalModule);
                IO_WriteS(Tree_f, (STRING)"    END ;", 9L);
                IO_WriteNl(Tree_f);
              } else {
                Tree_ForallClassesExtensionsFirst(W_3->Classes, (Tree_ProcOfT)EvalMThree3_EvalModule);
              }
              if (Check != InhIndexCount->A[i - 1]) {
                Errors_MessageI((STRING)"internal error in yyI", 21L, (LONGCARD)Errors_Error, Positions_NoPosition, (LONGCARD)Errors_Short, ADR(i));
              }
              IO_WriteS(Tree_f, (STRING)"  END yyI", 9L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)" ;", 2L);
              IO_WriteNl(Tree_f);
              IO_WriteNl(Tree_f);
            }
            if (i >= B_8) break;
          }
      }
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ( )", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"= BEGIN", 7L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Begin);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"  END Begin", 11L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ( )", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"= BEGIN", 7L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Close);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"  END Close", 11L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('X'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"  yyf := Stdio . Stdout ;", 25L);
        IO_WriteNl(Tree_f);
      }
      {
        SHORTCARD B_9 = Sets_Minimum(&InhIndices), B_10 = Sets_Maximum(&InhIndices);

        if (B_9 <= B_10)
          for (i = B_9;; i += 1) {
            if (Sets_IsElement((Sets_tElement)i, &InhIndices)) {
              IO_WriteS(Tree_f, (STRING)"  yyI [ ", 8L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)" ] := yyI", 9L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)" ;", 2L);
              IO_WriteNl(Tree_f);
            }
            if (i >= B_10) break;
          }
      }
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" .", 2L);
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
              EvalMThree_Class = t;
              if (InhIndexCount->A[i - 1] > 1) {
                IO_WriteS(Tree_f, (STRING)"     | ", 7L);
                Tree_WI(Tree_iMain);
                IO_WriteS(Tree_f, (STRING)" . ", 3L);
                Tree_WI(W_5->Name);
                IO_WriteS(Tree_f, (STRING)" ( TNode ) =>", 13L);
                IO_WriteNl(Tree_f);
              }
              INC(Check);
              k = ToBit1(W_6->Selector, (LONGINT)(W_4->a - W_5->AttrCount - W_6->Selector->U_1.V_9.Child.InstOffset));
              if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"      IFNOTIN (", 15L);
                Tree_WN((LONGINT)k);
                IO_WriteS(Tree_f, (STRING)", TNode . ", 10L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" . yyHead . yyIsDone )", 22L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"      INCLUDE ( TNode . ", 24L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" . yyHead . yyIsDone , ", 23L);
                Tree_WN((LONGINT)k);
                IO_WriteS(Tree_f, (STRING)" )", 2L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"      ELSE yyAbort ( TNode ) ;", 30L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"      END ;", 11L);
                IO_WriteNl(Tree_f);
              }
              {
                SHORTCARD B_11 = 1, B_12 = W_5->InstCount;

                if (B_11 <= B_12)
                  for (j = B_11;; j += 1) {
                    if (Relations_IsRelated((LONGINT)W_4->a, (LONGINT)j, W_5->DP)) {
                      GenCall(t, j);
                    }
                    if (j >= B_12) break;
                  }
              }
              if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"      yyWriteEval ( TNode , \"", 29L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action) && !IN(Tree_Virtual, W_6->Properties)) {
                  GenEvaluator(W_6->Action);
                  EvalMThree_GenEvaluator(W_6->Action);
                  IO_WriteNl(Tree_f);
                  if (W_6->Attribute->U_1.V_1.Kind == Tree_Child || W_6->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                    IO_WriteS(Tree_f, (STRING)"      write", 11L);
                    Tree_WI(Tree_itTree);
                    IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
                    Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)" . ", 3L);
                    Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)" )", 2L);
                    IO_WriteNl(Tree_f);
                  } else {
                    IO_WriteS(Tree_f, (STRING)"     write", 10L);
                    Tree_WI(W_6->Attribute->U_1.V_9.Child.Type);
                    IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
                    Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)" . ", 3L);
                    Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)" )", 2L);
                    IO_WriteNl(Tree_f);
                    IO_WriteS(Tree_f, (STRING)"     yyWriteNl ( ) ;", 20L);
                    IO_WriteNl(Tree_f);
                  }
                } else {
                  IO_WriteS(Tree_f, (STRING)"     yyWriteNl ( ) ;", 20L);
                  IO_WriteNl(Tree_f);
                }
              } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"     yyWriteEval ( TNode , \"", 28L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action) && !IN(Tree_Virtual, W_6->Properties)) {
                  GenEvaluator(W_6->Action);
                  EvalMThree_GenEvaluator(W_6->Action);
                }
              } else {
                if (W_6->Action != ADR(W_6->Action) && !IN(Tree_Virtual, W_6->Properties)) {
                  GenEvaluator(W_6->Action);
                  EvalMThree_GenEvaluator(W_6->Action);
                }
              }
              if (!IN(Tree_Input, W_6->Properties) && W_6->Attribute->U_1.V_1.Kind == Tree_Child) {
                IO_WriteS(Tree_f, (STRING)"      WITH yyTemp = TNode . ", 28L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" . ", 3L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" . yyHead DO", 12L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"         IF yyTemp . yyParent = ", 32L);
                Tree_WI(Tree_iMain);
                IO_WriteS(Tree_f, (STRING)" . ", 3L);
                Tree_WI(Tree_iNoTree);
                IO_WriteS(Tree_f, (STRING)" THEN", 5L);
                IO_WriteS(Tree_f, (STRING)"            yyOffset := ", 24L);
                Tree_WN((LONGINT)(W_6->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.BitCount + W_6->Attribute->U_1.V_9.Child.BitOffset));
                IO_WriteS(Tree_f, (STRING)" ;", 2L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"            yyTemp . yyParent := TNode . ", 41L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" ;", 2L);
                IO_WriteNl(Tree_f);
                Tree_WI(Tree_iMain);
                IO_WriteS(Tree_f, (STRING)" . Init", 7L);
                Tree_WI(Tree_iModule);
                IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" . ", 3L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"         END ;", 14L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"      END ;", 11L);
                IO_WriteNl(Tree_f);
              }
              {
                SHORTCARD B_13 = 1, B_14 = W_5->InstCount;

                if (B_13 <= B_14)
                  for (i2 = B_13;; i2 += 1) {
                    if (W_5->Instance->A[i2 - 1].Action == W_6->Action) {
                      {
                        register Tree_tInstance *W_7 = &W_5->Instance->A[i2 - 1];

                        if (IN(Tree_Synthesized, W_7->Properties)) {
                          k = EvalMThree3_ToBit0(EvalMThree_Class, (LONGINT)i2);
                          IO_WriteS(Tree_f, (STRING)"     INCLUDE ( TNode . yyHead . yyIsComp , ", 43L);
                          Tree_WN((LONGINT)k);
                          IO_WriteS(Tree_f, (STRING)" )", 2L);
                          IO_WriteNl(Tree_f);
                        } else if (IN(Tree_Inherited, W_7->Properties)) {
                          k = ToBit1(W_7->Selector, (LONGINT)(i2 - W_5->AttrCount - W_7->Selector->U_1.V_9.Child.InstOffset));
                          IO_WriteS(Tree_f, (STRING)"     INCLUDE ( TNode . ", 23L);
                          Tree_WI(W_7->Selector->U_1.V_9.Child.Name);
                          IO_WriteS(Tree_f, (STRING)" . yyHead . yyIsComp , ", 23L);
                          Tree_WN((LONGINT)k);
                          IO_WriteS(Tree_f, (STRING)" )", 2L);
                          IO_WriteNl(Tree_f);
                        }
                      }
                    }
                    if (i2 >= B_14) break;
                  }
              }
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
          SHORTCARD B_15 = W_12->AttrCount + 1, B_16 = W_12->InstCount;

          if (B_15 <= B_16)
            for (j = B_15;; j += 1) {
              {
                register Tree_tInstance *W_13 = &W_12->Instance->A[j - 1];

                if (IN(Tree_Inherited, W_13->Properties)) {
                  W_11->b = ToBit2(t, W_13->Selector, j);
                  Sets_Include(&InhIndices, (Sets_tElement)W_11->b);
                  INC(InhIndexCount->A[W_11->b - 1]);
                }
              }
              if (j >= B_16) break;
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

static void GenS
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
        if (!(i <= W_16->BitCount)) {
          goto EXIT_5;
        }
        {
          register Tree_tInstance *W_17 = &W_16->Instance->A[W_16->BitIndex->A[i - 1].ToAttr - 1];

          if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_17->Properties) && !IN(Tree_Test, W_17->Properties)) {
            EvalMThree_Class = t;
            if (n > 1) {
              IO_WriteS(Tree_f, (STRING)"     | ", 7L);
              Tree_WI(Tree_iMain);
              IO_WriteS(Tree_f, (STRING)" . ", 3L);
              Tree_WI(W_16->Name);
              IO_WriteS(Tree_f, (STRING)" ( TNode ) =>", 13L);
              IO_WriteNl(Tree_f);
            } else {
              IO_WriteS(Tree_f, (STRING)"     WITH TNode = NARROW ( yyt , ", 33L);
              Tree_WI(Tree_iMain);
              IO_WriteS(Tree_f, (STRING)" . ", 3L);
              Tree_WI(W_16->Name);
              IO_WriteS(Tree_f, (STRING)" ) DO", 5L);
              IO_WriteNl(Tree_f);
            }
            {
              SHORTCARD B_17 = 1, B_18 = W_16->InstCount;

              if (B_17 <= B_18)
                for (j = B_17;; j += 1) {
                  if (Relations_IsRelated((LONGINT)W_16->BitIndex->A[i - 1].ToAttr, (LONGINT)j, W_16->DP)) {
                    GenCall(t, j);
                  }
                  if (j >= B_18) break;
                }
            }
            GenEvalAttr(t, (LONGINT)W_16->BitIndex->A[i - 1].ToAttr);
            if (!IN(Tree_Input, W_17->Properties) && W_17->Attribute->U_1.V_1.Kind == Tree_Child) {
              IO_WriteS(Tree_f, (STRING)"      WITH yyTemp = TNode . ", 28L);
              Tree_WI(W_17->Attribute->U_1.V_9.Child.Name);
              IO_WriteS(Tree_f, (STRING)" . yyHead DO", 12L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"        IF yyTemp . yyParent = ", 31L);
              Tree_WI(Tree_iMain);
              IO_WriteS(Tree_f, (STRING)" . ", 3L);
              Tree_WI(Tree_iNoTree);
              IO_WriteS(Tree_f, (STRING)" THEN", 5L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"          yyOffset := ", 22L);
              Tree_WN((LONGINT)(W_16->BitCount + W_17->Attribute->U_1.V_9.Child.BitOffset));
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"          yyParent := TNode ;", 29L);
              IO_WriteS(Tree_f, (STRING)"          ", 10L);
              Tree_WI(Tree_iMain);
              IO_WriteS(Tree_f, (STRING)" . Init", 7L);
              Tree_WI(Tree_iModule);
              IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
              Tree_WI(W_17->Attribute->U_1.V_9.Child.Name);
              IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"        END ;", 13L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"      END ;", 11L);
              IO_WriteNl(Tree_f);
            }
            {
              SHORTCARD B_19 = 1, B_20 = W_16->InstCount;

              if (B_19 <= B_20)
                for (i2 = B_19;; i2 += 1) {
                  if (W_16->Instance->A[i2 - 1].Action == W_17->Action) {
                    {
                      register Tree_tInstance *W_18 = &W_16->Instance->A[i2 - 1];

                      if (IN(Tree_Synthesized, W_18->Properties)) {
                        k = EvalMThree3_ToBit0(EvalMThree_Class, (LONGINT)i2);
                        if (k != i - 1) {
                          IO_WriteS(Tree_f, (STRING)"      INCLUDE ( TNode . yyHead . yyIsComp , ", 44L);
                          Tree_WN((LONGINT)k);
                          IO_WriteS(Tree_f, (STRING)" )", 2L);
                          IO_WriteNl(Tree_f);
                        }
                      } else if (IN(Tree_Inherited, W_18->Properties)) {
                        k = ToBit1(W_18->Selector, (LONGINT)(i2 - W_16->AttrCount - W_18->Selector->U_1.V_9.Child.InstOffset));
                        IO_WriteS(Tree_f, (STRING)"         INCLUDE ( TNode . ", 27L);
                        Tree_WI(W_18->Selector->U_1.V_9.Child.Name);
                        IO_WriteS(Tree_f, (STRING)" . yyHead . yyIsComp , ", 23L);
                        Tree_WN((LONGINT)k);
                        IO_WriteS(Tree_f, (STRING)" )", 2L);
                        IO_WriteNl(Tree_f);
                      }
                    }
                  }
                  if (i2 >= B_20) break;
                }
            }
            if (n > 1) {
            } else {
              IO_WriteS(Tree_f, (STRING)"     END (* WITH TNode *)", 25L);
              IO_WriteNl(Tree_f);
            }
          }
        }
        return;
      }
    } EXIT_5:;
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
  struct S_11 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register struct S_12 *W_19 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yClass *W_20 = &t->U_1.V_5.Class;

        TreeMThree2_GetIterator(t);
        n = 0;
        j = 2;
        for (;;) {
          if (j > W_20->InstCount) {
            goto EXIT_6;
          }
          {
            register Tree_tInstance *W_21 = &W_20->Instance->A[j - 1];

            if (((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Output) | SET_ELEM(Tree_Test)) & W_21->Properties) != 0X0L) {
              if (IN(Tree_Test, W_21->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_21->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_21->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_21->Properties) && !IN(Tree_Input, W_21->Properties) && W_21->Attribute->U_1.V_1.Kind == Tree_Child || SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_Dummy), W_21->Properties) && W_21->Selector != TreeMThree2_Iterator && IN(Tree_HasOutput, W_21->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Properties)) {
                INC(n);
                goto EXIT_6;
              }
            }
          }
          INC(j);
        } EXIT_6:;
        if (n == 0 && (TreeMThree2_Iterator == Tree_NoTree || !IN(Tree_HasOutput, TreeMThree2_Iterator->U_1.V_9.Child.Class->U_1.V_5.Class.Properties))) {
          return;
        }
        EvalMThree_Class = t;
        IO_WriteS(Tree_f, (STRING)"      | ", 8L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) =>", 13L);
        IO_WriteNl(Tree_f);
        {
          SHORTCARD B_21 = 2, B_22 = W_20->InstCount;

          if (B_21 <= B_22)
            for (j = B_21;; j += 1) {
              {
                register Tree_tInstance *W_22 = &W_20->Instance->A[j - 1];

                if (((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Output)) & W_22->Properties) != 0X0L) {
                  if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_22->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_22->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Left), W_22->Properties) && !IN(Tree_Input, W_22->Properties) && W_22->Attribute->U_1.V_1.Kind == Tree_Child) {
                    GenCall(t, j);
                  } else if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_Dummy), W_22->Properties) && W_22->Selector != TreeMThree2_Iterator && IN(Tree_HasOutput, W_22->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Properties)) {
                    if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                      IO_WriteS(Tree_f, (STRING)"      yyWriteVisit ( TNode , \"", 30L);
                      Tree_WI(W_22->Selector->U_1.V_9.Child.Name);
                      IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
                      IO_WriteNl(Tree_f);
                    }
                    IO_WriteS(Tree_f, (STRING)"      yyE ( TNode . ", 20L);
                    Tree_WI(W_22->Selector->U_1.V_9.Child.Name);
                    IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
                    IO_WriteNl(Tree_f);
                    if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                      IO_WriteS(Tree_f, (STRING)"      yyVisitParent ( TNode . ", 30L);
                      Tree_WI(W_22->Selector->U_1.V_9.Child.Name);
                      IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
                      IO_WriteNl(Tree_f);
                    }
                  }
                }
              }
              if (j >= B_22) break;
            }
        }
        Sets_MakeSet(&W_19->ToCompute, (Sets_tElement)W_20->InstCount);
        {
          SHORTCARD B_23 = 2, B_24 = W_20->AttrCount;

          if (B_23 <= B_24)
            for (i = B_23;; i += 1) {
              {
                register Tree_tInstance *W_23 = &W_20->Instance->A[i - 1];

                if (IN(Tree_Test, W_23->Properties)) {
                  {
                    SHORTCARD B_25 = 2, B_26 = W_20->InstCount;

                    if (B_25 <= B_26)
                      for (j = B_25;; j += 1) {
                        if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_20->DP)) {
                          if (((SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Inherited)) & W_20->Instance->A[j - 1].Properties) != 0X0L) {
                            Sets_Include(&W_19->ToCompute, (Sets_tElement)j);
                          }
                        }
                        if (j >= B_26) break;
                      }
                  }
                }
              }
              if (i >= B_24) break;
            }
        }
        {
          SHORTCARD B_27 = 2, B_28 = W_20->InstCount;

          if (B_27 <= B_28)
            for (i = B_27;; i += 1) {
              {
                register Tree_tInstance *W_24 = &W_20->Instance->A[i - 1];

                if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left) | SET_ELEM(Tree_Output), W_24->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_Output), W_24->Properties)) {
                  Sets_Exclude(&W_19->ToCompute, (Sets_tElement)i);
                }
              }
              if (i >= B_28) break;
            }
        }
        while (!Sets_IsEmpty(W_19->ToCompute)) {
          GenCall(t, (SHORTCARD)Sets_Extract(&W_19->ToCompute));
        }
        Sets_ReleaseSet(&W_19->ToCompute);
        {
          SHORTCARD B_29 = 2, B_30 = W_20->AttrCount;

          if (B_29 <= B_30)
            for (i = B_29;; i += 1) {
              if (IN(Tree_Test, W_20->Instance->A[i - 1].Properties)) {
                GenEvalAttr(t, (LONGINT)i);
              }
              if (i >= B_30) break;
            }
        }
        if (TreeMThree2_Iterator == Tree_NoTree || !IN(Tree_HasOutput, TreeMThree2_Iterator->U_1.V_9.Child.Class->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)"RETURN ;", 8L);
          IO_WriteNl(Tree_f);
        } else {
          if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
            IO_WriteS(Tree_f, (STRING)"      yyWriteVisit ( TNode , \"", 30L);
            Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
            IO_WriteNl(Tree_f);
          }
          IO_WriteS(Tree_f, (STRING)"      yyt := TNode . ", 21L);
          Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    for (;;) {
      {
        register Tree_yClass *W_25 = &t->U_1.V_5.Class;

        if (!!IN(Tree_HasOutput, W_25->Properties)) {
          goto EXIT_7;
        }
        Success = FALSE;
        Tree_ForallAttributes(t, (Tree_ProcOfT)CompOutput);
        Tree_ForallClasses(W_25->Extensions, (Tree_ProcOfT)CompOutput2);
        if (!Success) {
          goto EXIT_7;
        }
        INCL(W_25->Properties, Tree_HasOutput);
        IsStable = FALSE;
        return;
      }
    } EXIT_7:;
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_26 = &t->U_1.V_9.Child;

        if (!(IN(Tree_Output, W_26->Properties) || IN(Tree_HasOutput, W_26->Class->U_1.V_5.Class.Properties))) {
          goto EXIT_8;
        }
        Success = TRUE;
        return;
      }
    } EXIT_8:;
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_27 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Output)) & W_27->Properties) != 0X0L)) {
          goto EXIT_9;
        }
        Success = TRUE;
        return;
      }
    } EXIT_9:;
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
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    for (;;) {
      {
        register Tree_yClass *W_28 = &t->U_1.V_5.Class;

        if (!IN(Tree_HasOutput, W_28->Properties)) {
          goto EXIT_10;
        }
        Success = TRUE;
        return;
      }
    } EXIT_10:;
  }
}

INTEGER EvalMThree3_ToBit0
# ifdef __STDC__
(Tree_tTree yyP2, INTEGER yyP1)
# else
(yyP2, yyP1)
Tree_tTree yyP2;
INTEGER yyP1;
# endif
{
  struct S_15 yyTempo;

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
  struct S_16 yyTempo;

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
  struct S_17 yyTempo;

  {
    register struct S_18 *W_29 = &yyTempo.U_1.V_1.yyR1;

    {
      register Tree_yChild *W_30 = &yyP6->U_1.V_9.Child;

      return yyP7->U_1.V_5.Class.BitCount + W_30->BitOffset + W_30->Class->U_1.V_5.Class.BitIndex->A[yyP5 - yyP7->U_1.V_5.Class.AttrCount - W_30->InstOffset - 1].ToBit - 1;
    }
    return W_29->yyV1;
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
  struct S_19 yyTempo;

  {
    register struct S_20 *W_31 = &yyTempo.U_1.V_1.yyR1;

    {
      register Tree_yClass *W_32 = &yyP9->U_1.V_5.Class;

      {
        SHORTCARD B_31 = W_32->AttrCount + 1, B_32 = W_32->InstCount;

        if (B_31 <= B_32)
          for (a = B_31;; a += 1) {
            {
              register Tree_tInstance *W_33 = &W_32->Instance->A[a - 1];

              if (((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_33->Properties) == 0X0L && ToBit2(yyP9, W_33->Selector, a) == yyP8) {
                return a;
              }
            }
            if (a >= B_32) break;
          }
      }
    }
    return 0;
    return W_31->yyV1;
  }
}

static void GenEvaluator
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Assign:;
    {
      register Tree_yAssign *W_34 = &t->U_1.V_36.Assign;

      GenEvaluator(W_34->Arguments);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_35 = &t->U_1.V_37.Copy;

      GenEvaluator(W_35->Arguments);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_36 = &t->U_1.V_38.TargetCode;

      GenEvaluator(W_36->Code);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_37 = &t->U_1.V_40.Check;

      GenEvaluator(W_37->Condition);
      GenEvaluator(W_37->Statement);
      GenEvaluator(W_37->Actions);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_38 = &t->U_1.V_15.Designator;

      GenEvaluator(W_38->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_39 = &t->U_1.V_16.Ident;

      GenEvaluator(W_39->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_40 = &t->U_1.V_18.Any;

      GenEvaluator(W_40->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_41 = &t->U_1.V_19.Anys;

      GenEvaluator(W_41->Next);
      return;
    }
    break;
  case Tree_Remote:;
    {
      register struct S_22 *W_42 = &yyTempo.U_1.V_1.yyR9;

      {
        register Tree_yRemote *W_43 = &t->U_1.V_17.Remote;

        W_42->TheClass = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_43->Type);
        if (W_42->TheClass != Tree_NoTree) {
          Attr = Tree_IdentifyAttribute(W_42->TheClass, W_43->Attribute);
          if (Attr != Tree_NoTree) {
            {
              register Tree_yAttribute *W_44 = &Attr->U_1.V_10.Attribute;

              W_42->k = EvalMThree3_ToBit0(W_42->TheClass, (LONGINT)W_44->AttrIndex);
              if (IN(Tree_Synthesized, W_44->Properties)) {
                IO_WriteS(Tree_f, (STRING)"      IFNOTIN ( ", 16L);
                Tree_WN(W_42->k);
                IO_WriteS(Tree_f, (STRING)" , ", 3L);
                EvalMThree_GenEvaluator(W_43->Designators);
                IO_WriteS(Tree_f, (STRING)" . yyHead . yyIsComp )", 22L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"      yyS", 9L);
                Tree_WN(W_42->k);
                IO_WriteS(Tree_f, (STRING)" ( ", 3L);
                EvalMThree_GenEvaluator(W_43->Designators);
                IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"    END ;", 9L);
                IO_WriteNl(Tree_f);
              } else if (IN(Tree_Inherited, W_44->Properties)) {
                IO_WriteS(Tree_f, (STRING)"      IFNOTIN ( ", 16L);
                Tree_WN(W_42->k);
                IO_WriteS(Tree_f, (STRING)" , ", 3L);
                EvalMThree_GenEvaluator(W_43->Designators);
                IO_WriteS(Tree_f, (STRING)" . yyHead . yyIsComp ) yyI [", 28L);
                EvalMThree_GenEvaluator(W_43->Designators);
                IO_WriteS(Tree_f, (STRING)" . yyHead . yyOffset + ", 23L);
                Tree_WN(W_42->k);
                IO_WriteS(Tree_f, (STRING)" ] ( ", 5L);
                EvalMThree_GenEvaluator(W_43->Designators);
                IO_WriteS(Tree_f, (STRING)" . yyHead . yyParent ) ;", 24L);
                IO_WriteNl(Tree_f);
                IO_WriteS(Tree_f, (STRING)"    END ;", 9L);
                IO_WriteNl(Tree_f);
              }
            }
          }
        }
        GenEvaluator(W_43->Next);
        return;
      }
    }
    break;
  default :
    break;
  }
}

void EvalMThree3_BeginEvalMThree3
# ifdef __STDC__
()
# else
()
# endif
{
}

void EvalMThree3_CloseEvalMThree3
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

void EvalMThree3__init()
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
    TreeMThree2__init();
    EvalMThree__init();
    Errors__init();
    Positions__init();
    EvalMThree__init();
    Tree__init();

    EvalMThree3_yyf = IO_StdOutput;
    EvalMThree3_Exit = yyExit;
    EvalMThree3_BeginEvalMThree3();
  }
}
