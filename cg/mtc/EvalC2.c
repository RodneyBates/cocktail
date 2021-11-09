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

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
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

#ifndef DEFINITION_TreeC2
#include "TreeC2.h"
#endif

#ifndef DEFINITION_EvalC
#include "EvalC.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_EvalC2
#include "EvalC2.h"
#endif

IO_tFile EvalC2_yyf;
PROC EvalC2_Exit;

static SHORTCARD Start, Stop, Visit, ChildVisit, i, j, k;
static Tree_tTree Node, Attr, Class, AttrClass, Child, Child2, ChildsClass;
static CARDINAL Representative ARGS((CARDINAL i));
static void GenAttribute ARGS((CARDINAL i, BOOLEAN repr));
static Tree_tTree GetClass ARGS((Tree_tTree Class, Idents_tIdent Attribute));
static BOOLEAN CheckUsage ARGS((BITSET Usage));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
static void TypeName ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void Forward ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void GenEvaluator ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void Generated0 ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void GenFormals1 ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void GenFormals2 ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void GenFormals3 ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void GenActualsRight ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void GenActualsLeft ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void GenTempos ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void GenTemposChildren ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void GenTemposLocal ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void GenDemandProc ARGS((Tree_tTree t));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static void GenDemandProc2 ARGS((Tree_tTree t));
struct S_17 {
    union {
        char dummy;
    } U_1;
};
static void GenDemandEval ARGS((Tree_tTree t));
struct S_18 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


static CARDINAL Representative
# ifdef __STDC__
(CARDINAL i)
# else
(i)
CARDINAL i;
# endif
{
  Sets_tSet s;
  CARDINAL r;
  BOOLEAN Stable;
  CARDINAL j, k;

  {
    register Tree_yClass *W_1 = &Class->U_1.V_5.Class;

    Sets_MakeSet(&s, (Sets_tElement)W_1->InstCount);
    Sets_Include(&s, i);
    do {
      Stable = TRUE;
      {
        LONGCARD B_1 = 1, B_2 = W_1->InstCount;

        if (B_1 <= B_2)
          for (j = B_1;; j += 1) {
            if (Sets_IsElement(j, &s)) {
              if (IN(Tree_CopyDef, W_1->Instance->A[j - 1].Properties)) {
                k = W_1->Instance->A[j - 1].CopyArg;
                if (IN(Tree_Parameter, W_1->Instance->A[k - 1].Attribute->U_1.V_10.Attribute.Properties) && !Sets_IsElement(k, &s)) {
                  Sets_Include(&s, k);
                  Stable = FALSE;
                }
              }
              if (IN(Tree_CopyUse, W_1->Instance->A[j - 1].Properties)) {
                {
                  LONGCARD B_3 = 1, B_4 = W_1->InstCount;

                  if (B_3 <= B_4)
                    for (k = B_3;; k += 1) {
                      if (IN(Tree_CopyDef, W_1->Instance->A[k - 1].Properties) && IN(Tree_Parameter, W_1->Instance->A[k - 1].Attribute->U_1.V_10.Attribute.Properties) && W_1->Instance->A[k - 1].CopyArg == j && !Sets_IsElement(k, &s)) {
                        Sets_Include(&s, k);
                        Stable = FALSE;
                      }
                      if (k >= B_4) break;
                    }
                }
              }
            }
            if (j >= B_2) break;
          }
      }
    } while (!Stable);
    r = Sets_Minimum(&s);
    if (r <= W_1->AttrCount) {
      Stable = TRUE;
      j = r + 1;
      for (;;) {
        if (j > W_1->AttrCount) {
          goto EXIT_1;
        }
        if (Sets_IsElement(j, &s)) {
          Stable = FALSE;
          goto EXIT_1;
        }
        INC(j);
      } EXIT_1:;
      if (!Stable) {
        j = 1;
        for (;;) {
          k = W_1->Instance->A[j - 1].Order;
          if (k <= W_1->AttrCount && Sets_IsElement(k, &s)) {
            r = k;
            goto EXIT_2;
          }
          INC(j);
        } EXIT_2:;
      }
    }
    Sets_ReleaseSet(&s);
    return r;
  }
}

static void GenAttribute
# ifdef __STDC__
(CARDINAL i, BOOLEAN repr)
# else
(i, repr)
CARDINAL i;
BOOLEAN repr;
# endif
{
  if (repr) {
    {
      register Tree_tInstance *W_2 = &Class->U_1.V_5.Class.Instance->A[i - 1];

      if (IN(Tree_Parameter, W_2->Attribute->U_1.V_10.Attribute.Properties) && ((SET_ELEM(Tree_CopyDef) | SET_ELEM(Tree_CopyUse)) & W_2->Properties) != 0X0L) {
        i = Representative(i);
      }
    }
  }
  {
    register Tree_tInstance *W_3 = &Class->U_1.V_5.Class.Instance->A[i - 1];

    if (IN(Tree_Virtual, W_3->Properties)) {
      return;
    }
    if (IN(Tree_Left, W_3->Properties)) {
      {
        register Tree_yAttribute *W_4 = &W_3->Attribute->U_1.V_10.Attribute;

        if (IN(Tree_Parameter, W_4->Properties)) {
          if (Tree_IdentifyAttribute(Node, W_4->Name) == Tree_NoTree) {
            IO_WriteS(Tree_f, (STRING)"yy", 2L);
            Tree_WI(W_4->Name);
          } else {
            IO_WriteS(Tree_f, (STRING)"(* yy", 5L);
            Tree_WI(W_4->Name);
            IO_WriteS(Tree_f, (STRING)")", 1L);
          }
        } else if (IN(Tree_Demand, W_4->Properties)) {
          if (IN(Tree_Funct, W_4->Properties)) {
            AttrClass = GetClass(Class, W_4->Name);
            IO_WriteS(Tree_f, (STRING)"y", 1L);
            Tree_WI(AttrClass->U_1.V_5.Class.Name);
            IO_WriteS(Tree_f, (STRING)"y", 1L);
            Tree_WI(W_4->Name);
            IO_WriteS(Tree_f, (STRING)" (yyt)", 6L);
          } else if (i != k) {
            IO_WriteS(Tree_f, (STRING)"yy", 2L);
            Tree_WI(W_4->Name);
          } else {
            IO_WriteS(Tree_f, (STRING)"(* yy", 5L);
            Tree_WI(W_4->Name);
            IO_WriteS(Tree_f, (STRING)")", 1L);
          }
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt->", 5L);
          Tree_WI(Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_4->Name);
        }
      }
    } else {
      {
        register Tree_yAttribute *W_5 = &W_3->Attribute->U_1.V_10.Attribute;

        if (IN(Tree_Parameter, W_5->Properties)) {
          Tree_WI(W_3->Selector->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)"yy", 2L);
          Tree_WI(W_5->Name);
        } else if (IN(Tree_Demand, W_5->Properties)) {
          if (IN(Tree_Funct, W_5->Properties)) {
            AttrClass = GetClass(W_3->Selector->U_1.V_9.Child.Class, W_5->Name);
            IO_WriteS(Tree_f, (STRING)"y", 1L);
            Tree_WI(AttrClass->U_1.V_5.Class.Name);
            IO_WriteS(Tree_f, (STRING)"y", 1L);
            Tree_WI(W_5->Name);
            IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
            Tree_WI(Class->U_1.V_5.Class.Name);
            IO_WriteS(Tree_f, (STRING)".", 1L);
            Tree_WI(W_3->Selector->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)")", 1L);
          } else {
            Tree_WI(W_3->Selector->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"yy", 2L);
            Tree_WI(W_5->Name);
          }
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt->", 5L);
          Tree_WI(Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_3->Selector->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)"->", 2L);
          Tree_WI(W_3->Selector->U_1.V_9.Child.Type);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_5->Name);
        }
      }
    }
  }
}

static Tree_tTree GetClass
# ifdef __STDC__
(Tree_tTree Class, Idents_tIdent Attribute)
# else
(Class, Attribute)
Tree_tTree Class;
Idents_tIdent Attribute;
# endif
{
  while (Class->U_1.V_1.Kind != Tree_NoClass) {
    if (Tree_IdentifyAttribute(Class->U_1.V_5.Class.Attributes, Attribute) != Tree_NoTree) {
      return Class;
    }
    Class = Class->U_1.V_5.Class.BaseClass;
  }
  return Tree_NoTree;
}

static BOOLEAN CheckUsage
# ifdef __STDC__
(BITSET Usage)
# else
(Usage)
BITSET Usage;
# endif
{
  SHORTCARD i, i2;

  {
    SHORTCARD B_5 = Start, B_6 = Stop;

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        i2 = Class->U_1.V_5.Class.Instance->A[i - 1].Order;
        {
          register Tree_tInstance *W_6 = &Class->U_1.V_5.Class.Instance->A[i2 - 1];

          if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_First), W_6->Properties) && Child == W_6->Selector && W_6->Attribute->U_1.V_9.Child.Partition <= W_6->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Visits && IN(W_6->Attribute->U_1.V_9.Child.Partition, Usage)) {
            return TRUE;
          }
          if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_6->Properties) && i2 == j) {
            return TRUE;
          }
        }
        if (i >= B_6) break;
      }
  }
  return FALSE;
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module EvalC2, routine ", 30L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*EvalC2_Exit)();
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

void EvalC2_EvalImplC
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
      register Tree_yAg *W_7 = &t->U_1.V_26.Ag;

      EvalC_EvalImplHead(t);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_7->Classes, (Tree_ProcOfT)Forward);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void ", 5L);
      Tree_WI(W_7->EvalName);
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
      Node = W_7->Classes;
      Class = W_7->Classes;
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      Tree_ForallAttributes(Class, (Tree_ProcOfT)GenTemposLocal);
      if (!Sets_IsElement(ORD('9'), &Tree_Options)) {
        if (Tree_MaxVisit > 0) {
          Class = W_7->Classes;
          Visit = 1;
          IO_WriteS(Tree_f, (STRING)" yyVisit1", 9L);
          Tree_WI(Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)" (yyt", 5L);
          Tree_ForallAttributes(Class, (Tree_ProcOfT)GenActualsLeft);
          IO_WriteS(Tree_f, (STRING)");", 2L);
        }
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)" char xxHigh;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" xxStack = 1000000000;", 22L);
        IO_WriteNl(Tree_f);
        if (Tree_MaxVisit > 0) {
          Class = W_7->Classes;
          Visit = 1;
          IO_WriteS(Tree_f, (STRING)" yyVisit1", 9L);
          Tree_WI(Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)" (yyt", 5L);
          Tree_ForallAttributes(Class, (Tree_ProcOfT)GenActualsLeft);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)" (void) printf (\"Stacksize %d\\n\", (int) & xxHigh - xxStack);", 60L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_7->Classes, (Tree_ProcOfT)GenDemandProc);
      Tree_ForallClasses(W_7->Classes, (Tree_ProcOfT)EvalC2_EvalImplC);
      IO_WriteS(Tree_f, (STRING)"void Begin", 10L);
      Tree_WI(W_7->EvalName);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(W_7->EvalCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_7->EvalCodes->U_1.V_12.Codes.Begin);
      Node = W_7->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void Close", 10L);
      Tree_WI(W_7->EvalName);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(W_7->EvalCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_7->EvalCodes->U_1.V_12.Codes.Close);
      Node = W_7->Modules;
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
      register Tree_yClass *W_8 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_8->Properties) != 0X0L) {
        return;
      }
      if (IN(Tree_Referenced, W_8->Properties)) {
        W_8->Generated = 0;
        Tree_ForallClasses(W_8->Extensions, (Tree_ProcOfT)Generated0);
        {
          SHORTCARD B_9 = 1, B_10 = W_8->Visits;

          if (B_9 <= B_10)
            for (Visit = B_9;; Visit += 1) {
              Node = t;
              Class = t;
              IO_WriteS(Tree_f, (STRING)"static void yyVisit", 19L);
              Tree_WN((LONGINT)Visit);
              Tree_WI(W_8->Name);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" (register ", 11L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt", 4L);
              Tree_ForallAttributes(t, (Tree_ProcOfT)GenFormals3);
              IO_WriteS(Tree_f, (STRING)")", 1L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"# else", 6L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" (yyt", 5L);
              Tree_ForallAttributes(t, (Tree_ProcOfT)GenFormals1);
              IO_WriteS(Tree_f, (STRING)")", 1L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" register ", 10L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
              IO_WriteNl(Tree_f);
              Tree_ForallAttributes(t, (Tree_ProcOfT)GenFormals2);
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
              IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
              IO_WriteNl(Tree_f);
              if (IN(Tree_cOAG, Tree_GrammarClass)) {
                Node = t;
                GenEvaluator(t);
                Tree_ForallClasses(W_8->Extensions, (Tree_ProcOfT)GenEvaluator);
              }
              IO_WriteS(Tree_f, (STRING)" default: ;", 11L);
              IO_WriteNl(Tree_f);
              if (Sets_IsElement(ORD('Z'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"  yyVisitParent (yyt);", 22L);
                IO_WriteNl(Tree_f);
              }
              IO_WriteS(Tree_f, (STRING)" }", 2L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"}", 1L);
              IO_WriteNl(Tree_f);
              IO_WriteNl(Tree_f);
              if (Visit >= B_10) break;
            }
        }
      }
      return;
    }
    break;
  default :
    break;
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
  struct S_4 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_9 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_9->Properties) != 0X0L) {
        return;
      }
      if (IN(Tree_Trace, W_9->Properties)) {
        IO_WriteS(Tree_f, (STRING)"\"", 1L);
        Tree_WI(W_9->Name);
        IO_WriteS(Tree_f, (STRING)"\",", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void Forward
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_10 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_10->Properties) != 0X0L) {
        return;
      }
      if (IN(Tree_Referenced, W_10->Properties)) {
        {
          SHORTCARD B_11 = 1, B_12 = W_10->Visits;

          if (B_11 <= B_12)
            for (Visit = B_11;; Visit += 1) {
              IO_WriteS(Tree_f, (STRING)"static void yyVisit", 19L);
              Tree_WN((LONGINT)Visit);
              Tree_WI(W_10->Name);
              IO_WriteS(Tree_f, (STRING)" ARGS((register ", 16L);
              Tree_WI(Tree_itTree);
              IO_WriteS(Tree_f, (STRING)" yyt", 4L);
              Node = t;
              Class = t;
              Tree_ForallAttributes(t, (Tree_ProcOfT)Forward);
              IO_WriteS(Tree_f, (STRING)"));", 3L);
              IO_WriteNl(Tree_f);
              if (Visit >= B_12) break;
            }
        }
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_11 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_11->Properties) && IN(Visit, W_11->Usage)) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        Tree_WI(W_11->Type);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        GenAttribute((LONGCARD)W_11->AttrIndex, FALSE);
      }
      return;
    }
    break;
  default :
    break;
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
  struct S_6 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_12 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_12->Properties) != 0X0L) {
        return;
      }
      if (W_12->Generated == W_12->InstCount) {
        return;
      }
      IO_WriteS(Tree_f, (STRING)"case k", 6L);
      Tree_WI(W_12->Name);
      IO_WriteS(Tree_f, (STRING)": {", 3L);
      IO_WriteNl(Tree_f);
      Start = W_12->Generated + 1;
      for (;;) {
        if (W_12->Generated == W_12->InstCount) {
          goto EXIT_3;
        }
        INC(W_12->Generated);
        {
          register Tree_tInstance *W_13 = &W_12->Instance->A[W_12->Instance->A[W_12->Generated - 1].Order - 1];

          if (IN(Tree_Left, W_13->Properties) && W_13->Attribute->U_1.V_9.Child.Partition > Visit) {
            DEC(W_12->Generated);
            goto EXIT_3;
          }
        }
      } EXIT_3:;
      Stop = W_12->Generated;
      Class = t;
      Tree_ForallAttributes(t, (Tree_ProcOfT)GenTempos);
      {
        SHORTCARD B_13 = Start, B_14 = Stop;

        if (B_13 <= B_14)
          for (Start = B_13;; Start += 1) {
            i = W_12->Instance->A[Start - 1].Order;
            {
              register Tree_tInstance *W_14 = &W_12->Instance->A[i - 1];

              if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_First), W_14->Properties) && ((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Virtual) | SET_ELEM(Tree_Demand)) & W_14->Properties) == 0X0L) {
                GenDemandEval(t);
                if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                  IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
                  Tree_WI(W_14->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)":", 1L);
                  Tree_WI(W_14->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"\");", 3L);
                  IO_WriteNl(Tree_f);
                  if (W_14->Action != ADR(W_14->Action)) {
                    GenEvaluator(W_14->Action);
                  }
                  IO_WriteNl(Tree_f);
                  if (W_14->Attribute->U_1.V_1.Kind == Tree_Child || W_14->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                    IO_WriteS(Tree_f, (STRING)"write", 5L);
                    Tree_WI(Tree_itTree);
                    IO_WriteS(Tree_f, (STRING)" (", 2L);
                    GenAttribute((LONGCARD)i, TRUE);
                    IO_WriteS(Tree_f, (STRING)")", 1L);
                    IO_WriteNl(Tree_f);
                  } else {
                    IO_WriteS(Tree_f, (STRING)"write", 5L);
                    Tree_WI(W_14->Attribute->U_1.V_9.Child.Type);
                    IO_WriteS(Tree_f, (STRING)" (", 2L);
                    GenAttribute((LONGCARD)i, TRUE);
                    IO_WriteS(Tree_f, (STRING)") yyWriteNl ();", 15L);
                    IO_WriteNl(Tree_f);
                  }
                } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                  IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
                  Tree_WI(W_14->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)":", 1L);
                  Tree_WI(W_14->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"\");", 3L);
                  IO_WriteNl(Tree_f);
                  if (W_14->Action != ADR(W_14->Action)) {
                    GenEvaluator(W_14->Action);
                  }
                } else {
                  if (W_14->Action != ADR(W_14->Action)) {
                    GenEvaluator(W_14->Action);
                  }
                }
              }
              if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left) | SET_ELEM(Tree_First), W_14->Properties) && ((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Virtual) | SET_ELEM(Tree_Demand)) & W_14->Properties) == 0X0L) {
                GenDemandEval(t);
                if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                  IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
                  Tree_WI(W_14->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"\");", 3L);
                  IO_WriteNl(Tree_f);
                  if (W_14->Action != ADR(W_14->Action)) {
                    GenEvaluator(W_14->Action);
                  }
                  IO_WriteNl(Tree_f);
                  if (IN(Tree_Test, W_14->Properties)) {
                    IO_WriteS(Tree_f, (STRING)"writebool (yyb) yyWriteNl ();", 29L);
                    IO_WriteNl(Tree_f);
                  } else if (W_14->Attribute->U_1.V_1.Kind == Tree_Child || W_14->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                    IO_WriteS(Tree_f, (STRING)"write", 5L);
                    Tree_WI(Tree_itTree);
                    IO_WriteS(Tree_f, (STRING)" (", 2L);
                    GenAttribute((LONGCARD)i, TRUE);
                    IO_WriteS(Tree_f, (STRING)")", 1L);
                    IO_WriteNl(Tree_f);
                  } else {
                    IO_WriteS(Tree_f, (STRING)"write", 5L);
                    Tree_WI(W_14->Attribute->U_1.V_9.Child.Type);
                    IO_WriteS(Tree_f, (STRING)" (", 2L);
                    GenAttribute((LONGCARD)i, TRUE);
                    IO_WriteS(Tree_f, (STRING)") yyWriteNl ();", 15L);
                    IO_WriteNl(Tree_f);
                  }
                } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                  IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, \"", 19L);
                  Tree_WI(W_14->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"\");", 3L);
                  IO_WriteNl(Tree_f);
                  if (W_14->Action != ADR(W_14->Action)) {
                    GenEvaluator(W_14->Action);
                  }
                } else {
                  if (W_14->Action != ADR(W_14->Action)) {
                    GenEvaluator(W_14->Action);
                  }
                }
              }
              if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_First), W_14->Properties) && W_14->Attribute->U_1.V_9.Child.Partition <= W_14->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Visits) {
                if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                  IO_WriteS(Tree_f, (STRING)"yyWriteVisit (yyt, \"", 20L);
                  Tree_WI(W_14->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)" ", 1L);
                  Tree_WN((LONGINT)W_14->Attribute->U_1.V_9.Child.Partition);
                  IO_WriteS(Tree_f, (STRING)"\");", 3L);
                  IO_WriteNl(Tree_f);
                }
                ChildVisit = W_14->Attribute->U_1.V_9.Child.Partition;
                Child = W_14->Selector;
                IO_WriteS(Tree_f, (STRING)"yyVisit", 7L);
                Tree_WN((LONGINT)ChildVisit);
                Tree_WI(Child->U_1.V_9.Child.Type);
                IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
                Tree_WI(W_12->Name);
                IO_WriteS(Tree_f, (STRING)".", 1L);
                Tree_WI(Child->U_1.V_9.Child.Name);
                Tree_ForallAttributes(Child->U_1.V_9.Child.Class, (Tree_ProcOfT)GenActualsRight);
                IO_WriteS(Tree_f, (STRING)");", 2L);
                IO_WriteNl(Tree_f);
              }
            }
            if (Start >= B_14) break;
          }
      }
      if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"yyVisitParent (yyt);", 20L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"} break;", 8L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_15 = &t->U_1.V_36.Assign;

      TreeC2_WriteLine(W_15->Pos);
      GenEvaluator(W_15->Results);
      IO_WriteS(Tree_f, (STRING)"=", 1L);
      GenEvaluator(W_15->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_16 = &t->U_1.V_37.Copy;

      j = Class->U_1.V_5.Class.Instance->A[i - 1].CopyArg;
      if (IN(Tree_Parameter, Class->U_1.V_5.Class.Instance->A[i - 1].Attribute->U_1.V_10.Attribute.Properties) && IN(Tree_Parameter, Class->U_1.V_5.Class.Instance->A[j - 1].Attribute->U_1.V_10.Attribute.Properties)) {
        if (IN(Tree_Left, Class->U_1.V_5.Class.Instance->A[i - 1].Properties) && IN(Tree_Left, Class->U_1.V_5.Class.Instance->A[j - 1].Properties)) {
          TreeC2_WriteLine(W_16->Pos);
          GenAttribute((LONGCARD)i, FALSE);
          IO_WriteS(Tree_f, (STRING)" =", 2L);
          GenEvaluator(W_16->Arguments);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      } else {
        TreeC2_WriteLine(W_16->Pos);
        GenEvaluator(W_16->Results);
        IO_WriteS(Tree_f, (STRING)"=", 1L);
        GenEvaluator(W_16->Arguments);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_17 = &t->U_1.V_38.TargetCode;

      TreeC2_WriteLine(W_17->Pos);
      GenEvaluator(W_17->Code);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_18 = &t->U_1.V_40.Check;

      TreeC2_WriteLine(W_18->Pos);
      if (W_18->Condition != Tree_NoTree) {
        IO_WriteS(Tree_f, (STRING)"if (! (", 7L);
        if (Sets_IsElement(ORD('X'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"yyb = ", 6L);
        }
        GenEvaluator(W_18->Condition);
        IO_WriteS(Tree_f, (STRING)")) {", 4L);
        GenEvaluator(W_18->Statement);
        IO_WriteS(Tree_f, (STRING)"; }", 3L);
        IO_WriteNl(Tree_f);
        if (W_18->Actions->U_1.V_1.Kind == Tree_Check) {
          IO_WriteS(Tree_f, (STRING)"else ", 5L);
          GenEvaluator(W_18->Actions);
        }
      } else {
        if (Sets_IsElement(ORD('X'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"yyb = false; ", 13L);
        }
        GenEvaluator(W_18->Statement);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        GenEvaluator(W_18->Actions);
      }
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_19 = &t->U_1.V_15.Designator;

      Child2 = Tree_IdentifyAttribute(Class, W_19->Selector);
      if (Child2 != Tree_NoTree) {
        ChildsClass = Child2->U_1.V_9.Child.Class;
        Attr = Tree_IdentifyAttribute(ChildsClass, W_19->Attribute);
        if (Attr != Tree_NoTree) {
          GenAttribute((LONGCARD)(Class->U_1.V_5.Class.AttrCount + Child2->U_1.V_9.Child.InstOffset + Attr->U_1.V_10.Attribute.AttrIndex), TRUE);
        } else {
          Tree_WI(W_19->Selector);
          IO_WriteS(Tree_f, (STRING)":", 1L);
          Tree_WI(W_19->Attribute);
        }
      } else {
        Tree_WI(W_19->Selector);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_19->Attribute);
      }
      GenEvaluator(W_19->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_20 = &t->U_1.V_16.Ident;

      Attr = Tree_IdentifyAttribute(Class, W_20->Attribute);
      if (Attr != Tree_NoTree) {
        GenAttribute((LONGCARD)Attr->U_1.V_10.Attribute.AttrIndex, TRUE);
      } else {
        Tree_WI(W_20->Attribute);
      }
      GenEvaluator(W_20->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_21 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_21->Code);
      GenEvaluator(W_21->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_22 = &t->U_1.V_19.Anys;

      GenEvaluator(W_22->Layouts);
      GenEvaluator(W_22->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_23 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_23->Code);
      GenEvaluator(W_23->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void Generated0
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
      register Tree_yClass *W_24 = &t->U_1.V_5.Class;

      W_24->Generated = 0;
      return;
    }
  }
}

static void GenFormals1
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_25 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_25->Properties) && IN(Visit, W_25->Usage)) {
        IO_WriteS(Tree_f, (STRING)", yy", 4L);
        Tree_WI(W_25->Name);
      }
      return;
    }
  }
}

static void GenFormals2
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_26 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_26->Properties) && IN(Visit, W_26->Usage)) {
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_26->Type);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        GenAttribute((LONGCARD)W_26->AttrIndex, FALSE);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void GenFormals3
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_27 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_27->Properties) && IN(Visit, W_27->Usage)) {
        IO_WriteS(Tree_f, (STRING)" ,", 2L);
        Tree_WI(W_27->Type);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        GenAttribute((LONGCARD)W_27->AttrIndex, FALSE);
      }
      return;
    }
  }
}

static void GenActualsRight
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_28 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_28->Properties) && IN(ChildVisit, W_28->Usage)) {
        IO_WriteS(Tree_f, (STRING)", & ", 4L);
        GenAttribute((LONGCARD)(Class->U_1.V_5.Class.AttrCount + Child->U_1.V_9.Child.InstOffset + W_28->AttrIndex), TRUE);
      }
      return;
    }
  }
}

static void GenActualsLeft
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_29 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_29->Properties) && IN(Visit, W_29->Usage)) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        GenAttribute((LONGCARD)W_29->AttrIndex, FALSE);
      }
      return;
    }
  }
}

static void GenTempos
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
  case Tree_Child:;
    {
      register Tree_yChild *W_30 = &t->U_1.V_9.Child;

      Child = t;
      Tree_ForallAttributes(W_30->Class, (Tree_ProcOfT)GenTemposChildren);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_31 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_31->Properties) && Tree_IdentifyAttribute(Node, W_31->Name) == Tree_NoTree && IN(Visit, W_31->Usage) || IN(Tree_Demand, W_31->Properties) && !IN(Tree_Funct, W_31->Properties) && W_31->AttrIndex != k) {
        Tree_WI(W_31->Type);
        IO_WriteS(Tree_f, (STRING)" yy", 3L);
        Tree_WI(W_31->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void GenTemposChildren
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_32 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_32->Properties) || IN(Tree_Demand, W_32->Properties) && !IN(Tree_Funct, W_32->Properties)) {
        j = Class->U_1.V_5.Class.AttrCount + Child->U_1.V_9.Child.InstOffset + W_32->AttrIndex;
        if (IN(Tree_Demand, W_32->Properties) || ((SET_ELEM(Tree_CopyDef) | SET_ELEM(Tree_CopyUse)) & Class->U_1.V_5.Class.Instance->A[j - 1].Properties) == 0X0L || j == Representative((LONGCARD)j)) {
          if (CheckUsage(W_32->Usage)) {
            Tree_WI(W_32->Type);
            IO_WriteS(Tree_f, (STRING)" ", 1L);
            Tree_WI(Child->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"yy", 2L);
            Tree_WI(W_32->Name);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
        }
      }
      return;
    }
  }
}

static void GenTemposLocal
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_33 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Parameter, W_33->Properties)) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_33->Type);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        GenAttribute((LONGCARD)W_33->AttrIndex, FALSE);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void GenDemandProc
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_34 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_34->Properties) != 0X0L) {
        return;
      }
      Node = t;
      Tree_ForallAttributes(W_34->Attributes, (Tree_ProcOfT)GenDemandProc);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_35 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Demand, W_35->Properties)) {
        Class = Node;
        k = W_35->AttrIndex;
        if (IN(Tree_Funct, W_35->Properties)) {
          IO_WriteS(Tree_f, (STRING)"static ", 7L);
          Tree_WI(W_35->Type);
          IO_WriteS(Tree_f, (STRING)" y", 2L);
          Tree_WI(Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)"y", 1L);
          Tree_WI(W_35->Name);
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
        } else {
          IO_WriteS(Tree_f, (STRING)"static void y", 13L);
          Tree_WI(Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)"y", 1L);
          Tree_WI(W_35->Name);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" (register ", 11L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" yyt, ", 6L);
          Tree_WI(W_35->Type);
          IO_WriteS(Tree_f, (STRING)" * ", 3L);
          GenAttribute((LONGCARD)W_35->AttrIndex, FALSE);
          IO_WriteS(Tree_f, (STRING)")", 1L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"# else", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" (yyt, ", 7L);
          GenAttribute((LONGCARD)W_35->AttrIndex, FALSE);
          IO_WriteS(Tree_f, (STRING)")", 1L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" register ", 10L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" ", 1L);
          Tree_WI(W_35->Type);
          IO_WriteS(Tree_f, (STRING)" * ", 3L);
          GenAttribute((LONGCARD)W_35->AttrIndex, FALSE);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"# endif", 7L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
        IO_WriteNl(Tree_f);
        if (IN(Tree_cOAG, Tree_GrammarClass)) {
          i = W_35->AttrIndex;
          Class = Node;
          Visit = W_35->Partition;
          GenDemandProc2(Class);
          Tree_ForallClasses(Class->U_1.V_5.Class.Extensions, (Tree_ProcOfT)GenDemandProc2);
          Class = Node;
        }
        IO_WriteS(Tree_f, (STRING)" default: ;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        k = 0;
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void GenDemandProc2
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
      register Tree_yClass *W_36 = &t->U_1.V_5.Class;

      IO_WriteS(Tree_f, (STRING)"case k", 6L);
      Tree_WI(W_36->Name);
      IO_WriteS(Tree_f, (STRING)": {", 3L);
      IO_WriteNl(Tree_f);
      {
        register Tree_tInstance *W_37 = &W_36->Instance->A[i - 1];

        Class = t;
        Tree_ForallAttributes(t, (Tree_ProcOfT)GenTempos);
        GenDemandEval(t);
        if (IN(Tree_Funct, W_37->Properties)) {
          GenDemandProc2(W_37->Action);
        } else {
          GenEvaluator(W_37->Action);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)"} break;", 8L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_38 = &t->U_1.V_36.Assign;

      IO_WriteS(Tree_f, (STRING)"return ", 7L);
      GenEvaluator(W_38->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_39 = &t->U_1.V_37.Copy;

      IO_WriteS(Tree_f, (STRING)"return ", 7L);
      GenEvaluator(W_39->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_40 = &t->U_1.V_38.TargetCode;

      IO_WriteS(Tree_f, (STRING)"NoBlockStatementForDemandFunctionAttributes;", 44L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  default :
    break;
  }
}

static void GenDemandEval
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
      register Tree_yClass *W_41 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_15 = 1, B_16 = W_41->InstCount;

        if (B_15 <= B_16)
          for (j = B_15;; j += 1) {
            {
              register Tree_tInstance *W_42 = &W_41->Instance->A[j - 1];

              if (Relations_IsRelated((LONGINT)i, (LONGINT)j, W_41->DP) && IN(Tree_Demand, W_42->Properties) && !IN(Tree_Funct, W_42->Properties)) {
                if (IN(Tree_Left, W_42->Properties)) {
                  AttrClass = GetClass(t, W_42->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"    y", 5L);
                  Tree_WI(AttrClass->U_1.V_5.Class.Name);
                  IO_WriteS(Tree_f, (STRING)"y", 1L);
                  Tree_WI(W_42->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)" (yyt, ", 7L);
                  GenAttribute((LONGCARD)j, FALSE);
                  IO_WriteS(Tree_f, (STRING)");", 2L);
                  IO_WriteNl(Tree_f);
                } else {
                  AttrClass = GetClass(W_42->Selector->U_1.V_9.Child.Class, W_42->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"    y", 5L);
                  Tree_WI(AttrClass->U_1.V_5.Class.Name);
                  IO_WriteS(Tree_f, (STRING)"y", 1L);
                  Tree_WI(W_42->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
                  Tree_WI(W_41->Name);
                  IO_WriteS(Tree_f, (STRING)".", 1L);
                  Tree_WI(W_42->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)", ", 2L);
                  GenAttribute((LONGCARD)j, FALSE);
                  IO_WriteS(Tree_f, (STRING)");", 2L);
                  IO_WriteNl(Tree_f);
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

void EvalC2_BeginEvalC2
# ifdef __STDC__
()
# else
()
# endif
{
  k = 0;
}

void EvalC2_CloseEvalC2
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

void EvalC2__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Tree__init();
    System__init();
    IO__init();
    Tree__init();
    IO__init();
    StringMem__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Relations__init();
    TreeC2__init();
    EvalC__init();
    Tree__init();

    EvalC2_yyf = IO_StdOutput;
    EvalC2_Exit = yyExit;
    EvalC2_BeginEvalC2();
  }
}
