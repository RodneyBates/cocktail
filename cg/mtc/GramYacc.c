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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_GramYacc
#include "GramYacc.h"
#endif

IO_tFile GramYacc_yyf;
PROC GramYacc_Exit;

static Tree_tTree Node, ActClass, TheClass, TheAttr;
static SHORTCARD ActActionIndex, PrevActionIndex;
static BOOLEAN IsImplicit;
static Tree_tTree GetBaseClass ARGS((Tree_tTree Class));
static BOOLEAN IsLast ARGS((Tree_tTree Class, Tree_tTree Action));
static void IsLast2 ARGS((Tree_tTree t, Tree_tTree Action, BOOLEAN *pFound, BOOLEAN *pLast));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
static void ParsVariant ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void GenExt ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void Token ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void RecordField ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void PrecDefs ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void Grammar ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void Rule ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void Implicit ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


static Tree_tTree GetBaseClass
# ifdef __STDC__
(Tree_tTree Class)
# else
(Class)
Tree_tTree Class;
# endif
{
  while (Class->U_1.V_5.Class.BaseClass->U_1.V_1.Kind != Tree_NoClass) {
    Class = Class->U_1.V_5.Class.BaseClass;
  }
  return Class;
}

static BOOLEAN IsLast
# ifdef __STDC__
(Tree_tTree Class, Tree_tTree Action)
# else
(Class, Action)
Tree_tTree Class, Action;
# endif
{
  BOOLEAN Found, Last;

  IsLast2(Class, Action, &Found, &Last);
  return Last;
}

static void IsLast2
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Action, BOOLEAN *pFound, BOOLEAN *pLast)
# else
(t, Action, pFound, pLast)
Tree_tTree t, Action;
BOOLEAN *pFound, *pLast;
# endif
{
  BOOLEAN Found, Last;

  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    IsLast2(t->U_1.V_5.Class.Attributes, Action, pFound, pLast);
    if (*pFound || !*pLast) {
      return;
    }
    IsLast2(t->U_1.V_5.Class.BaseClass, Action, pFound, pLast);
    break;
  case Tree_Child:;
    IsLast2(t->U_1.V_9.Child.Next, Action, &Found, &Last);
    *pFound = Found;
    if (Found) {
      *pLast = Last;
    } else {
      *pLast = FALSE;
    }
    break;
  case Tree_Attribute:;
    IsLast2(t->U_1.V_10.Attribute.Next, Action, pFound, pLast);
    break;
  case Tree_ActionPart:;
    IsLast2(t->U_1.V_11.ActionPart.Next, Action, &Found, &Last);
    *pFound = Found || Action == t;
    if (Found) {
      *pLast = Last;
    } else {
      *pLast = Last && Action == t;
    }
    break;
  default :
    *pFound = FALSE;
    *pLast = TRUE;
    break;
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module GramYacc, routine ", 32L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*GramYacc_Exit)();
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

void GramYacc_ParsSpec
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
      register Tree_yAg *W_1 = &t->U_1.V_26.Ag;

      IO_WriteS(Tree_f, (STRING)"%{", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Scanner.h\"", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"/* EXPORT */", 12L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Export);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"/* GLOBAL */", 12L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Global);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Global);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"/* LOCAL */", 11L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Local);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void BeginParser ()", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Begin);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void CloseParser ()", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Close);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      ParsVariant(W_1->Classes);
      IO_WriteS(Tree_f, (STRING)"%}", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"%union {", 8L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" tScanAttribute Scan;", 21L);
      IO_WriteNl(Tree_f);
      Node = W_1->Classes;
      while (Node->U_1.V_1.Kind == Tree_Class) {
        {
          register Tree_yClass *W_2 = &Node->U_1.V_5.Class;

          if (SET_IS_SUBSET1(SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Referenced) | SET_ELEM(Tree_HasAttributes), W_2->Properties)) {
            if (IN(Tree_String, W_2->Properties) && !IN(Tree_HasSelector, W_2->Properties)) {
              IO_WriteS(Tree_f, (STRING)" yy", 3L);
              Tree_WN((LONGINT)W_2->Name);
              IO_WriteS(Tree_f, (STRING)" /* ", 4L);
              Tree_WI(W_2->Name);
              IO_WriteS(Tree_f, (STRING)" */ yy", 6L);
              Tree_WN((LONGINT)W_2->Name);
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            } else {
              IO_WriteS(Tree_f, (STRING)" yy", 3L);
              Tree_WI(W_2->Selector);
              IO_WriteS(Tree_f, (STRING)" ", 1L);
              Tree_WI(W_2->Selector);
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            }
          }
          Node = W_2->Next;
        }
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"%token", 6L);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)Token);
      IO_WriteNl(Tree_f);
      PrecDefs(W_1->Precs);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"%%", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)GramYacc_ParsSpec);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_3 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Referenced), W_3->Properties)) {
        TheClass = t;
        Grammar(t);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void ParsVariant
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
      register Tree_yClass *W_4 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Referenced) | SET_ELEM(Tree_HasAttributes), W_4->Properties)) {
        IO_WriteS(Tree_f, (STRING)"typedef struct { ", 17L);
        Tree_ForallAttributes(W_4->Attributes, (Tree_ProcOfT)RecordField);
        GenExt(W_4->Extensions);
        if (IN(Tree_String, W_4->Properties) && !IN(Tree_HasSelector, W_4->Properties)) {
          IO_WriteS(Tree_f, (STRING)"} /* ", 5L);
          Tree_WI(W_4->Name);
          IO_WriteS(Tree_f, (STRING)" */ yy", 6L);
          Tree_WN((LONGINT)W_4->Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"} yy", 4L);
          Tree_WI(W_4->Selector);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      }
      ParsVariant(W_4->Next);
      return;
    }
  }
}

static void GenExt
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
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      Tree_ForallAttributes(W_5->Attributes, (Tree_ProcOfT)RecordField);
      GenExt(W_5->Extensions);
      GenExt(W_5->Next);
      return;
    }
  }
}

static void Token
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
      register Tree_yClass *W_6 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Referenced), W_6->Properties)) {
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_6->Name);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WN((LONGINT)W_6->Code);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void RecordField
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
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_7 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_7->Properties) == 0X0L) {
        Tree_WI(W_7->Type);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_7->Name);
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
      }
      return;
    }
  }
}

static void PrecDefs
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
  switch (t->U_1.V_1.Kind) {
  case Tree_LeftAssoc:;
    {
      register Tree_yLeftAssoc *W_8 = &t->U_1.V_30.LeftAssoc;

      IO_WriteS(Tree_f, (STRING)"%left ", 6L);
      PrecDefs(W_8->Names);
      IO_WriteNl(Tree_f);
      PrecDefs(W_8->Next);
      return;
    }
    break;
  case Tree_RightAssoc:;
    {
      register Tree_yRightAssoc *W_9 = &t->U_1.V_31.RightAssoc;

      IO_WriteS(Tree_f, (STRING)"%right", 6L);
      PrecDefs(W_9->Names);
      IO_WriteNl(Tree_f);
      PrecDefs(W_9->Next);
      return;
    }
    break;
  case Tree_NonAssoc:;
    {
      register Tree_yNonAssoc *W_10 = &t->U_1.V_32.NonAssoc;

      IO_WriteS(Tree_f, (STRING)"%none ", 6L);
      PrecDefs(W_10->Names);
      IO_WriteNl(Tree_f);
      PrecDefs(W_10->Next);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_11 = &t->U_1.V_25.Name;

      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_11->Name);
      PrecDefs(W_11->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void Grammar
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
    {
      register Tree_yClass *W_12 = &t->U_1.V_5.Class;

      if (W_12->Extensions->U_1.V_1.Kind == Tree_NoClass) {
        {
          register Tree_yClass *W_13 = &TheClass->U_1.V_5.Class;

          if (IN(Tree_String, W_13->Properties)) {
            IO_WriteS(Tree_f, (STRING)"yy", 2L);
            Tree_WN((LONGINT)W_13->Name);
          } else {
            Tree_WI(W_13->Name);
          }
        }
        IO_WriteS(Tree_f, (STRING)"	: ", 3L);
        ActClass = t;
        PrevActionIndex = 0;
        IsImplicit = FALSE;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Rule);
        if (W_12->Prec != Idents_NoIdent) {
          IO_WriteS(Tree_f, (STRING)"%prec ", 6L);
          Tree_WI(W_12->Prec);
          IO_WriteS(Tree_f, (STRING)" ", 1L);
        }
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        PrevActionIndex = 0;
        IsImplicit = TRUE;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Implicit);
      } else {
        Rule(W_12->Extensions);
      }
      return;
    }
  }
}

static void Rule
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_14 = &t->U_1.V_5.Class;

      Grammar(t);
      Rule(W_14->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_15 = &t->U_1.V_9.Child;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_String) | SET_ELEM(Tree_Nonterminal), W_15->Class->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"yy", 2L);
        Tree_WN((LONGINT)W_15->Type);
      } else {
        Tree_WI(W_15->Type);
      }
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_16 = &t->U_1.V_11.ActionPart;

      if (!Sets_IsElement(ORD('v'), &Tree_Options)) {
        if (IsLast(ActClass, t)) {
          IO_WriteS(Tree_f, (STRING)"{", 1L);
          if (PrevActionIndex != 0) {
            Node = GetBaseClass(TheClass);
            {
              register Tree_yClass *W_17 = &Node->U_1.V_5.Class;

              IO_WriteS(Tree_f, (STRING)" $$.", 4L);
              if (IN(Tree_String, W_17->Properties)) {
                IO_WriteS(Tree_f, (STRING)"yy", 2L);
                Tree_WN((LONGINT)W_17->Name);
              } else {
                Tree_WI(W_17->Name);
              }
              IO_WriteS(Tree_f, (STRING)" = $", 4L);
              Tree_WN((LONGINT)PrevActionIndex);
              IO_WriteS(Tree_f, (STRING)".", 1L);
              if (IN(Tree_String, W_17->Properties)) {
                IO_WriteS(Tree_f, (STRING)"yy", 2L);
                Tree_WN((LONGINT)W_17->Name);
              } else {
                Tree_WI(W_17->Name);
              }
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            }
          }
          Rule(W_16->Actions);
          IO_WriteS(Tree_f, (STRING)"} ", 2L);
        } else {
          IO_WriteS(Tree_f, (STRING)"xx", 2L);
          Tree_WN((LONGINT)W_16->Name);
          IO_WriteS(Tree_f, (STRING)" ", 1L);
        }
        PrevActionIndex = W_16->ParsIndex;
      }
      return;
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_18 = &t->U_1.V_36.Assign;

      Rule(W_18->Results);
      IO_WriteS(Tree_f, (STRING)"=", 1L);
      Rule(W_18->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Rule(W_18->Next);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_19 = &t->U_1.V_37.Copy;

      Rule(W_19->Results);
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Rule(W_19->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Rule(W_19->Next);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_20 = &t->U_1.V_38.TargetCode;

      Rule(W_20->Code);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Rule(W_20->Next);
      return;
    }
    break;
  case Tree_Order:;
    {
      register Tree_yOrder *W_21 = &t->U_1.V_39.Order;

      Rule(W_21->Next);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_22 = &t->U_1.V_40.Check;

      if (W_22->Statement != Tree_NoTree) {
        if (W_22->Condition != Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"if (", 4L);
          Rule(W_22->Condition);
          IO_WriteS(Tree_f, (STRING)") ; else { ", 11L);
          Rule(W_22->Statement);
          IO_WriteS(Tree_f, (STRING)" }", 2L);
          IO_WriteNl(Tree_f);
        } else {
          Rule(W_22->Statement);
        }
      }
      Rule(W_22->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_23 = &t->U_1.V_15.Designator;

      TheAttr = Tree_IdentifyAttribute(ActClass, W_23->Selector);
      if (TheAttr != Tree_NoTree) {
        Node = TheAttr->U_1.V_9.Child.Class;
        if (Node != Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"$", 1L);
          if (!IsImplicit) {
            Tree_WN((LONGINT)TheAttr->U_1.V_9.Child.ParsIndex);
          } else {
            Tree_WN((LONGINT)(SHORTINT)(TheAttr->U_1.V_9.Child.ParsIndex + 1 - ActActionIndex));
          }
          if (IN(Tree_Nonterminal, Node->U_1.V_5.Class.Properties)) {
            Node = GetBaseClass(Node);
            if (IN(Tree_String, Node->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, Node->U_1.V_5.Class.Properties)) {
              IO_WriteS(Tree_f, (STRING)".yy", 3L);
              Tree_WN((LONGINT)Node->U_1.V_5.Class.Name);
            } else {
              IO_WriteS(Tree_f, (STRING)".", 1L);
              Tree_WI(Node->U_1.V_5.Class.Name);
            }
          } else {
            if (IN(Tree_String, Node->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, Node->U_1.V_5.Class.Properties)) {
              IO_WriteS(Tree_f, (STRING)".Scan.yy", 8L);
              Tree_WN((LONGINT)Node->U_1.V_5.Class.Code);
            } else {
              IO_WriteS(Tree_f, (STRING)".Scan.", 6L);
              Tree_WI(Node->U_1.V_5.Class.Selector);
            }
          }
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_23->Attribute);
        } else {
          Tree_WI(W_23->Selector);
          IO_WriteS(Tree_f, (STRING)":", 1L);
          Tree_WI(W_23->Attribute);
        }
      } else {
        Tree_WI(W_23->Selector);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_23->Attribute);
      }
      Rule(W_23->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_24 = &t->U_1.V_16.Ident;

      TheAttr = Tree_IdentifyAttribute(ActClass, W_24->Attribute);
      Node = GetBaseClass(TheClass);
      if (TheAttr != Tree_NoTree) {
        if (IN(Tree_String, Node->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, Node->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)"$$.yy", 5L);
          Tree_WN((LONGINT)Node->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_24->Attribute);
        } else {
          IO_WriteS(Tree_f, (STRING)"$$.", 3L);
          Tree_WI(Node->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_24->Attribute);
        }
      } else {
        Tree_WI(W_24->Attribute);
      }
      Rule(W_24->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_25 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_25->Code);
      Rule(W_25->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_26 = &t->U_1.V_19.Anys;

      Rule(W_26->Layouts);
      Rule(W_26->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_27 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_27->Code);
      Rule(W_27->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void Implicit
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
  if (t->U_1.V_1.Kind == Tree_ActionPart) {
    {
      register Tree_yActionPart *W_28 = &t->U_1.V_11.ActionPart;

      if (!IN(Tree_Generated, W_28->Properties) && !IsLast(ActClass, t)) {
        INCL(W_28->Properties, Tree_Generated);
        ActActionIndex = W_28->ParsIndex;
        IO_WriteS(Tree_f, (STRING)"xx", 2L);
        Tree_WN((LONGINT)W_28->Name);
        IO_WriteS(Tree_f, (STRING)"	: {", 4L);
        if (PrevActionIndex != 0) {
          Node = GetBaseClass(TheClass);
          {
            register Tree_yClass *W_29 = &Node->U_1.V_5.Class;

            IO_WriteS(Tree_f, (STRING)" $$.", 4L);
            if (IN(Tree_String, W_29->Properties)) {
              IO_WriteS(Tree_f, (STRING)"yy", 2L);
              Tree_WN((LONGINT)W_29->Name);
            } else {
              Tree_WI(W_29->Name);
            }
            IO_WriteS(Tree_f, (STRING)" = $", 4L);
            Tree_WN((LONGINT)(SHORTINT)(PrevActionIndex + 1 - ActActionIndex));
            IO_WriteS(Tree_f, (STRING)".", 1L);
            if (IN(Tree_String, W_29->Properties)) {
              IO_WriteS(Tree_f, (STRING)"yy", 2L);
              Tree_WN((LONGINT)W_29->Name);
            } else {
              Tree_WI(W_29->Name);
            }
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
        }
        Rule(W_28->Actions);
        IO_WriteS(Tree_f, (STRING)"} .", 3L);
        IO_WriteNl(Tree_f);
      }
      PrevActionIndex = W_28->ParsIndex;
      return;
    }
  }
}

void GramYacc_BeginGramYacc
# ifdef __STDC__
()
# else
()
# endif
{
}

void GramYacc_CloseGramYacc
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

void GramYacc__init()
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
    Tree__init();
    Strings__init();

    GramYacc_yyf = IO_StdOutput;
    GramYacc_Exit = yyExit;
    GramYacc_BeginGramYacc();
  }
}
