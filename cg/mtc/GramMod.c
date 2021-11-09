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

#ifndef DEFINITION_Strings
#include "Strings.h"
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

#ifndef DEFINITION_IOUtils
#include "IOUtils.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_GramMod
#include "GramMod.h"
#endif

IO_tFile GramMod_yyf;
PROC GramMod_Exit;

static Tree_tTree Node, ActClass, TheClass, TheAttr;
static Idents_tIdent iOper, iLeft, iRight, iNone, iPrec, iRule;
static SHORTCARD ActActionIndex, PrevActionIndex, i;
static BOOLEAN IsImplicit;
static Strings_tString s;
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
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void ErrorActions ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void ScanVariant ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void ScanAttr ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void ParsVariant ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void GenExt ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void Token ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void RecordField ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void PrecDefs ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void Grammar ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void Rule ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void Implicit ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void ClassListDep ARGS((Tree_tTree t));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static void GrammarDep ARGS((Tree_tTree t));
struct S_17 {
    union {
        char dummy;
    } U_1;
};
static void ChildDep ARGS((Tree_tTree t));
struct S_18 {
    union {
        char dummy;
    } U_1;
};
static void ActionsDep ARGS((Tree_tTree t));
struct S_19 {
    union {
        char dummy;
    } U_1;
};
static void WriteName ARGS((Idents_tIdent Name));
struct S_20 {
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module GramMod, routine ", 31L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*GramMod_Exit)();
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

void GramMod_ParsSpec
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

      if (W_1->ScannerName != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"SCANNER ", 8L);
        Tree_WI(W_1->ScannerName);
      }
      IO_WriteS(Tree_f, (STRING)" PARSER ", 8L);
      Tree_WI(W_1->ParserName);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"GLOBAL {", 8L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Global);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Global);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"TYPE", 4L);
      IO_WriteNl(Tree_f);
      ParsVariant(W_1->Classes);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('K'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"tParsAttribute = RECORD", 23L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"tParsAttribute = RECORD CASE : SHORTCARD OF", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  0: Scan: ", 11L);
      }
      if (W_1->ScannerName != Idents_NoIdent) {
        Tree_WI(W_1->ScannerName);
      } else {
        IO_WriteS(Tree_f, (STRING)"Scanner", 7L);
      }
      IO_WriteS(Tree_f, (STRING)".tScanAttribute;", 16L);
      IO_WriteNl(Tree_f);
      i = 0;
      Node = W_1->Classes;
      while (Node->U_1.V_1.Kind == Tree_Class) {
        {
          register Tree_yClass *W_2 = &Node->U_1.V_5.Class;

          if (SET_IS_SUBSET1(SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Referenced) | SET_ELEM(Tree_HasAttributes), W_2->Properties)) {
            INC(i);
            if (!Sets_IsElement(ORD('K'), &Tree_Options)) {
              IO_WriteS(Tree_f, (STRING)"| ", 2L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)": ", 2L);
            }
            if (IN(Tree_String, W_2->Properties) && !IN(Tree_HasSelector, W_2->Properties)) {
              IO_WriteS(Tree_f, (STRING)"(* ", 3L);
              Tree_WE(W_2->Name);
              IO_WriteS(Tree_f, (STRING)" *) yy", 6L);
              Tree_WN((LONGINT)W_2->Name);
              IO_WriteS(Tree_f, (STRING)": yy", 4L);
              Tree_WN((LONGINT)W_2->Name);
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            } else {
              Tree_WI(W_2->Selector);
              IO_WriteS(Tree_f, (STRING)": yy", 4L);
              Tree_WI(W_2->Selector);
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            }
          }
          Node = W_2->Next;
        }
      }
      if (!Sets_IsElement(ORD('K'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" END ;", 6L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"END ;", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"EXPORT {", 8L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Export);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"LOCAL {", 7L);
      IO_WriteNl(Tree_f);
      Texts_WriteText(Tree_f, W_1->ParserCodes->U_1.V_12.Codes.Local);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.ParserCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN {", 7L);
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
      IO_WriteS(Tree_f, (STRING)"CLOSE {", 7L);
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
      IO_WriteS(Tree_f, (STRING)"TOKEN", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)Token);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"OPER", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      PrecDefs(W_1->Precs);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"RULE", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)GramMod_ParsSpec);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_3 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Referenced), W_3->Properties)) {
        TheClass = t;
        if (Sets_IsElement(ORD('e'), &Tree_Options)) {
          GrammarDep(t);
        } else {
          Grammar(t);
        }
      }
      return;
    }
    break;
  default :
    break;
  }
}

void GramMod_ScanSpec
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
      register Tree_yAg *W_4 = &t->U_1.V_26.Ag;

      IO_WriteS(Tree_f, (STRING)"m", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"TYPE", 4L);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_4->Classes, (Tree_ProcOfT)ScanVariant);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"tScanAttribute = RECORD", 23L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"Position: tPosition;", 20L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('K'), &Tree_Options)) {
        Tree_ForallClasses(W_4->Classes, (Tree_ProcOfT)ScanAttr);
      } else {
        IO_WriteS(Tree_f, (STRING)"CASE : SHORTCARD OF", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_4->Classes, (Tree_ProcOfT)ScanAttr);
        IO_WriteS(Tree_f, (STRING)" END ;", 6L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"END ;", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ErrorAttribute (Token: INTEGER; VAR pAttribute: tScanAttribute);", 74L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"%%", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ErrorAttribute (Token: INTEGER; VAR pAttribute: tScanAttribute);", 74L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" pAttribute.Position := Attribute.Position;", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" CASE Token OF", 14L);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_4->Classes, (Tree_ProcOfT)ErrorActions);
      IO_WriteS(Tree_f, (STRING)" ELSE", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END;", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ErrorAttribute;", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"%%", 2L);
      IO_WriteNl(Tree_f);
      Tree_ForallClasses(W_4->Classes, (Tree_ProcOfT)GramMod_ScanSpec);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Referenced), W_5->Properties)) {
        Tree_WN((LONGINT)W_5->Code);
        if (IN(Tree_HasAttributes, W_5->Properties)) {
          IO_WriteS(Tree_f, (STRING)" S ", 3L);
        } else {
          IO_WriteS(Tree_f, (STRING)" N ", 3L);
        }
        if (IN(Tree_String, W_5->Properties) && !IN(Tree_HasSelector, W_5->Properties)) {
          IO_WriteS(Tree_f, (STRING)"yy", 2L);
          Tree_WN((LONGINT)W_5->Code);
        } else {
          Tree_WI(W_5->Selector);
        }
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_5->Name);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void ErrorActions
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
      register Tree_yClass *W_6 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Referenced) | SET_ELEM(Tree_HasAttributes), W_6->Properties)) {
        IO_WriteS(Tree_f, (STRING)" | (* ", 6L);
        Tree_WE(W_6->Name);
        IO_WriteS(Tree_f, (STRING)" *) ", 4L);
        Tree_WN((LONGINT)W_6->Code);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        IO_WriteNl(Tree_f);
        TheClass = t;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ErrorActions);
      }
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_7 = &t->U_1.V_11.ActionPart;

      ErrorActions(W_7->Actions);
      return;
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_8 = &t->U_1.V_36.Assign;

      ErrorActions(W_8->Results);
      IO_WriteS(Tree_f, (STRING)":=", 2L);
      ErrorActions(W_8->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      ErrorActions(W_8->Next);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_9 = &t->U_1.V_37.Copy;

      ErrorActions(W_9->Results);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      ErrorActions(W_9->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      ErrorActions(W_9->Next);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_10 = &t->U_1.V_38.TargetCode;

      ErrorActions(W_10->Code);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      ErrorActions(W_10->Next);
      return;
    }
    break;
  case Tree_Order:;
    {
      register Tree_yOrder *W_11 = &t->U_1.V_39.Order;

      ErrorActions(W_11->Next);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_12 = &t->U_1.V_40.Check;

      if (W_12->Statement != Tree_NoTree) {
        if (W_12->Condition != Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"IF NOT (", 8L);
          ErrorActions(W_12->Condition);
          IO_WriteS(Tree_f, (STRING)") THEN ", 7L);
          ErrorActions(W_12->Statement);
          IO_WriteS(Tree_f, (STRING)"; END;", 6L);
          IO_WriteNl(Tree_f);
        } else {
          ErrorActions(W_12->Statement);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      } else {
        IO_WriteS(Tree_f, (STRING)"IF ", 3L);
        ErrorActions(W_12->Condition);
        IO_WriteS(Tree_f, (STRING)" THEN END;", 10L);
        IO_WriteNl(Tree_f);
      }
      ErrorActions(W_12->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_13 = &t->U_1.V_15.Designator;

      Tree_WI(W_13->Selector);
      IO_WriteS(Tree_f, (STRING)":", 1L);
      Tree_WI(W_13->Attribute);
      ErrorActions(W_13->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_14 = &t->U_1.V_16.Ident;

      TheAttr = Tree_IdentifyAttribute(TheClass, W_14->Attribute);
      if (TheAttr != Tree_NoTree) {
        IO_WriteS(Tree_f, (STRING)"pAttribute", 10L);
        if (W_14->Attribute == Tree_iPosition) {
        } else if (IN(Tree_String, TheClass->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, TheClass->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)".yy", 3L);
          Tree_WN((LONGINT)TheClass->U_1.V_5.Class.Code);
        } else {
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TheClass->U_1.V_5.Class.Selector);
        }
        IO_WriteS(Tree_f, (STRING)".", 1L);
      }
      Tree_WI(W_14->Attribute);
      ErrorActions(W_14->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_15 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_15->Code);
      ErrorActions(W_15->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_16 = &t->U_1.V_19.Anys;

      ErrorActions(W_16->Layouts);
      ErrorActions(W_16->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_17 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_17->Code);
      ErrorActions(W_17->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void ScanVariant
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
      register Tree_yClass *W_18 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Referenced) | SET_ELEM(Tree_HasAttributes), W_18->Properties)) {
        if (IN(Tree_String, W_18->Properties) && !IN(Tree_HasSelector, W_18->Properties)) {
          IO_WriteS(Tree_f, (STRING)"(* ", 3L);
          Tree_WE(W_18->Name);
          IO_WriteS(Tree_f, (STRING)" *) yy", 6L);
          Tree_WN((LONGINT)W_18->Code);
          IO_WriteS(Tree_f, (STRING)" = RECORD ", 10L);
        } else {
          IO_WriteS(Tree_f, (STRING)"yy", 2L);
          Tree_WI(W_18->Selector);
          IO_WriteS(Tree_f, (STRING)" = RECORD ", 10L);
        }
        TheClass = t;
        Tree_ForallAttributes(t, (Tree_ProcOfT)RecordField);
        IO_WriteS(Tree_f, (STRING)"END;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ScanAttr
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
      register Tree_yClass *W_19 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Referenced) | SET_ELEM(Tree_HasAttributes), W_19->Properties)) {
        if (!Sets_IsElement(ORD('K'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"| ", 2L);
          Tree_WN((LONGINT)W_19->Code);
          IO_WriteS(Tree_f, (STRING)": ", 2L);
        }
        if (IN(Tree_String, W_19->Properties) && !IN(Tree_HasSelector, W_19->Properties)) {
          IO_WriteS(Tree_f, (STRING)"(* ", 3L);
          Tree_WE(W_19->Name);
          IO_WriteS(Tree_f, (STRING)" *) yy", 6L);
          Tree_WN((LONGINT)W_19->Code);
          IO_WriteS(Tree_f, (STRING)": yy", 4L);
          Tree_WN((LONGINT)W_19->Code);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        } else {
          Tree_WI(W_19->Selector);
          IO_WriteS(Tree_f, (STRING)": yy", 4L);
          Tree_WI(W_19->Selector);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
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
  struct S_8 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_20 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Referenced) | SET_ELEM(Tree_HasAttributes), W_20->Properties)) {
        if (IN(Tree_String, W_20->Properties) && !IN(Tree_HasSelector, W_20->Properties)) {
          IO_WriteS(Tree_f, (STRING)"(* ", 3L);
          Tree_WE(W_20->Name);
          IO_WriteS(Tree_f, (STRING)" *) yy", 6L);
          Tree_WN((LONGINT)W_20->Name);
          IO_WriteS(Tree_f, (STRING)" = RECORD ", 10L);
        } else {
          IO_WriteS(Tree_f, (STRING)"yy", 2L);
          Tree_WI(W_20->Selector);
          IO_WriteS(Tree_f, (STRING)" = RECORD ", 10L);
        }
        TheClass = t;
        GenExt(W_20->Extensions);
        Tree_ForallAttributes(W_20->Attributes, (Tree_ProcOfT)RecordField);
        IO_WriteS(Tree_f, (STRING)"END;", 4L);
        IO_WriteNl(Tree_f);
      }
      ParsVariant(W_20->Next);
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
  struct S_9 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_21 = &t->U_1.V_5.Class;

      Tree_ForallAttributes(W_21->Attributes, (Tree_ProcOfT)RecordField);
      GenExt(W_21->Extensions);
      GenExt(W_21->Next);
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
  struct S_10 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_22 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Referenced), W_22->Properties)) {
        WriteName(W_22->Name);
        IO_WriteS(Tree_f, (STRING)" = ", 3L);
        Tree_WN((LONGINT)W_22->Code);
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
  struct S_11 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_23 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_23->Properties) == 0X0L) {
        if (IN(Tree_Nonterminal, TheClass->U_1.V_5.Class.Properties) || W_23->Name != Tree_iPosition) {
          Tree_WI(W_23->Name);
          IO_WriteS(Tree_f, (STRING)": ", 2L);
          Tree_WI(W_23->Type);
          IO_WriteS(Tree_f, (STRING)"; ", 2L);
          IO_WriteNl(Tree_f);
        }
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
  struct S_12 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_LeftAssoc:;
    {
      register Tree_yLeftAssoc *W_24 = &t->U_1.V_30.LeftAssoc;

      IO_WriteS(Tree_f, (STRING)"LEFT ", 5L);
      PrecDefs(W_24->Names);
      IO_WriteNl(Tree_f);
      PrecDefs(W_24->Next);
      return;
    }
    break;
  case Tree_RightAssoc:;
    {
      register Tree_yRightAssoc *W_25 = &t->U_1.V_31.RightAssoc;

      IO_WriteS(Tree_f, (STRING)"RIGHT", 5L);
      PrecDefs(W_25->Names);
      IO_WriteNl(Tree_f);
      PrecDefs(W_25->Next);
      return;
    }
    break;
  case Tree_NonAssoc:;
    {
      register Tree_yNonAssoc *W_26 = &t->U_1.V_32.NonAssoc;

      IO_WriteS(Tree_f, (STRING)"NONE ", 5L);
      PrecDefs(W_26->Names);
      IO_WriteNl(Tree_f);
      PrecDefs(W_26->Next);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_27 = &t->U_1.V_25.Name;

      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_27->Name);
      PrecDefs(W_27->Next);
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
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_28 = &t->U_1.V_5.Class;

      if (W_28->Extensions->U_1.V_1.Kind == Tree_NoClass) {
        {
          register Tree_yClass *W_29 = &TheClass->U_1.V_5.Class;

          if (IN(Tree_String, W_29->Properties)) {
            IO_WriteS(Tree_f, (STRING)"yy", 2L);
            Tree_WN((LONGINT)W_29->Name);
          } else {
            WriteName(W_29->Name);
          }
        }
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        ActClass = t;
        PrevActionIndex = 0;
        IsImplicit = FALSE;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Rule);
        if (W_28->Prec != Idents_NoIdent) {
          IO_WriteS(Tree_f, (STRING)"PREC ", 5L);
          Tree_WI(W_28->Prec);
          IO_WriteS(Tree_f, (STRING)" ", 1L);
        }
        IO_WriteS(Tree_f, (STRING)".", 1L);
        IO_WriteNl(Tree_f);
        PrevActionIndex = 0;
        IsImplicit = TRUE;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Implicit);
      } else {
        Rule(W_28->Extensions);
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
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_30 = &t->U_1.V_5.Class;

      Grammar(t);
      Rule(W_30->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_31 = &t->U_1.V_9.Child;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_String) | SET_ELEM(Tree_Nonterminal), W_31->Class->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"yy", 2L);
        Tree_WN((LONGINT)W_31->Type);
      } else {
        WriteName(W_31->Type);
      }
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_32 = &t->U_1.V_11.ActionPart;

      if (IsLast(ActClass, t)) {
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        if (PrevActionIndex != 0) {
          Node = GetBaseClass(TheClass);
          {
            register Tree_yClass *W_33 = &Node->U_1.V_5.Class;

            if (IN(Tree_HasAttributes, W_33->Properties)) {
              IO_WriteS(Tree_f, (STRING)" $$.", 4L);
              if (IN(Tree_String, W_33->Properties)) {
                IO_WriteS(Tree_f, (STRING)"yy", 2L);
                Tree_WN((LONGINT)W_33->Name);
              } else {
                Tree_WI(W_33->Name);
              }
              IO_WriteS(Tree_f, (STRING)" := $", 5L);
              Tree_WN((LONGINT)PrevActionIndex);
              IO_WriteS(Tree_f, (STRING)".", 1L);
              if (IN(Tree_String, W_33->Properties)) {
                IO_WriteS(Tree_f, (STRING)"yy", 2L);
                Tree_WN((LONGINT)W_33->Name);
              } else {
                Tree_WI(W_33->Name);
              }
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            }
          }
        }
        Rule(W_32->Actions);
        IO_WriteS(Tree_f, (STRING)"} ", 2L);
      } else {
        IO_WriteS(Tree_f, (STRING)"xx", 2L);
        Tree_WN((LONGINT)W_32->Name);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
      }
      PrevActionIndex = W_32->ParsIndex;
      return;
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_34 = &t->U_1.V_36.Assign;

      Rule(W_34->Results);
      IO_WriteS(Tree_f, (STRING)":=", 2L);
      Rule(W_34->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Rule(W_34->Next);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_35 = &t->U_1.V_37.Copy;

      Rule(W_35->Results);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Rule(W_35->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Rule(W_35->Next);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_36 = &t->U_1.V_38.TargetCode;

      Rule(W_36->Code);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Rule(W_36->Next);
      return;
    }
    break;
  case Tree_Order:;
    {
      register Tree_yOrder *W_37 = &t->U_1.V_39.Order;

      Rule(W_37->Next);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_38 = &t->U_1.V_40.Check;

      if (W_38->Statement != Tree_NoTree) {
        if (W_38->Condition != Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"IF NOT (", 8L);
          Rule(W_38->Condition);
          IO_WriteS(Tree_f, (STRING)") THEN ", 7L);
          Rule(W_38->Statement);
          IO_WriteS(Tree_f, (STRING)"; END;", 6L);
          IO_WriteNl(Tree_f);
        } else {
          Rule(W_38->Statement);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      } else {
        IO_WriteS(Tree_f, (STRING)"IF ", 3L);
        Rule(W_38->Condition);
        IO_WriteS(Tree_f, (STRING)" THEN END;", 10L);
        IO_WriteNl(Tree_f);
      }
      Rule(W_38->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_39 = &t->U_1.V_15.Designator;

      TheAttr = Tree_IdentifyAttribute(ActClass, W_39->Selector);
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
            IO_WriteS(Tree_f, (STRING)".Scan", 5L);
            if (W_39->Attribute == Tree_iPosition) {
            } else if (IN(Tree_String, Node->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, Node->U_1.V_5.Class.Properties)) {
              IO_WriteS(Tree_f, (STRING)".yy", 3L);
              Tree_WN((LONGINT)Node->U_1.V_5.Class.Code);
            } else {
              IO_WriteS(Tree_f, (STRING)".", 1L);
              Tree_WI(Node->U_1.V_5.Class.Selector);
            }
          }
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_39->Attribute);
        } else {
          Tree_WI(W_39->Selector);
          IO_WriteS(Tree_f, (STRING)":", 1L);
          Tree_WI(W_39->Attribute);
        }
      } else {
        Tree_WI(W_39->Selector);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_39->Attribute);
      }
      Rule(W_39->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_40 = &t->U_1.V_16.Ident;

      TheAttr = Tree_IdentifyAttribute(ActClass, W_40->Attribute);
      Node = GetBaseClass(TheClass);
      if (TheAttr != Tree_NoTree) {
        if (IN(Tree_String, Node->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, Node->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)"$$.yy", 5L);
          Tree_WN((LONGINT)Node->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_40->Attribute);
        } else {
          IO_WriteS(Tree_f, (STRING)"$$.", 3L);
          Tree_WI(Node->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_40->Attribute);
        }
      } else {
        Tree_WI(W_40->Attribute);
      }
      Rule(W_40->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_41 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_41->Code);
      Rule(W_41->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_42 = &t->U_1.V_19.Anys;

      Rule(W_42->Layouts);
      Rule(W_42->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_43 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_43->Code);
      Rule(W_43->Next);
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
  struct S_15 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_ActionPart) {
    {
      register Tree_yActionPart *W_44 = &t->U_1.V_11.ActionPart;

      if (!IN(Tree_Generated, W_44->Properties) && !IsLast(ActClass, t)) {
        INCL(W_44->Properties, Tree_Generated);
        ActActionIndex = W_44->ParsIndex;
        IO_WriteS(Tree_f, (STRING)"xx", 2L);
        Tree_WN((LONGINT)W_44->Name);
        IO_WriteS(Tree_f, (STRING)" : {", 4L);
        if (PrevActionIndex != 0) {
          Node = GetBaseClass(TheClass);
          {
            register Tree_yClass *W_45 = &Node->U_1.V_5.Class;

            if (IN(Tree_HasAttributes, W_45->Properties)) {
              IO_WriteS(Tree_f, (STRING)" $$.", 4L);
              if (IN(Tree_String, W_45->Properties)) {
                IO_WriteS(Tree_f, (STRING)"yy", 2L);
                Tree_WN((LONGINT)W_45->Name);
              } else {
                Tree_WI(W_45->Name);
              }
              IO_WriteS(Tree_f, (STRING)" := $", 5L);
              Tree_WN((LONGINT)(SHORTINT)(PrevActionIndex + 1 - ActActionIndex));
              IO_WriteS(Tree_f, (STRING)".", 1L);
              if (IN(Tree_String, W_45->Properties)) {
                IO_WriteS(Tree_f, (STRING)"yy", 2L);
                Tree_WN((LONGINT)W_45->Name);
              } else {
                Tree_WI(W_45->Name);
              }
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            }
          }
        }
        Rule(W_44->Actions);
        IO_WriteS(Tree_f, (STRING)"} .", 3L);
        IO_WriteNl(Tree_f);
      }
      PrevActionIndex = W_44->ParsIndex;
      return;
    }
  }
}

static void ClassListDep
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
      register Tree_yClass *W_46 = &t->U_1.V_5.Class;

      GrammarDep(t);
      ClassListDep(W_46->Next);
      return;
    }
  }
}

static void GrammarDep
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  SHORTCARD i;
  BOOLEAN BracesGenerated;
  struct S_17 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_47 = &t->U_1.V_5.Class;

      if (W_47->Extensions->U_1.V_1.Kind == Tree_NoClass) {
        {
          register Tree_yClass *W_48 = &TheClass->U_1.V_5.Class;

          if (IN(Tree_String, W_48->Properties)) {
            IO_WriteS(Tree_f, (STRING)"yy", 2L);
            Tree_WN((LONGINT)W_48->Name);
          } else {
            WriteName(W_48->Name);
          }
        }
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ChildDep);
        IO_WriteNl(Tree_f);
        BracesGenerated = FALSE;
        {
          SHORTCARD B_3 = 1, B_4 = W_47->InstCount;

          if (B_3 <= B_4)
            for (i = B_3;; i += 1) {
              {
                register Tree_tInstance *W_49 = &W_47->Instance->A[W_47->Instance->A[i - 1].Order - 1];

                if (SET_IS_SUBSET1(SET_ELEM(Tree_Left) | SET_ELEM(Tree_First), W_49->Properties) && !IN(Tree_Dummy, W_49->Properties) && W_49->Action != ADR(W_49->Action)) {
                  ActClass = t;
                  if (BracesGenerated) {
                    IO_WriteS(Tree_f, (STRING)"   ", 3L);
                  } else {
                    IO_WriteS(Tree_f, (STRING)" { ", 3L);
                    BracesGenerated = TRUE;
                  }
                  ActionsDep(W_49->Action);
                  IO_WriteNl(Tree_f);
                }
              }
              if (i >= B_4) break;
            }
        }
        if (BracesGenerated) {
          IO_WriteS(Tree_f, (STRING)" } ", 3L);
          IO_WriteNl(Tree_f);
        }
        if (W_47->Prec != Idents_NoIdent) {
          IO_WriteS(Tree_f, (STRING)"PREC ", 5L);
          Tree_WI(W_47->Prec);
          IO_WriteS(Tree_f, (STRING)" ", 1L);
        }
        IO_WriteS(Tree_f, (STRING)".", 1L);
        IO_WriteNl(Tree_f);
      } else {
        ClassListDep(W_47->Extensions);
      }
      return;
    }
  }
}

static void ChildDep
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
  if (t->U_1.V_1.Kind == Tree_Child) {
    {
      register Tree_yChild *W_50 = &t->U_1.V_9.Child;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_String) | SET_ELEM(Tree_Nonterminal), W_50->Class->U_1.V_5.Class.Properties)) {
        IO_WriteS(Tree_f, (STRING)"yy", 2L);
        Tree_WN((LONGINT)W_50->Type);
      } else {
        WriteName(W_50->Type);
      }
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      return;
    }
  }
}

static void ActionsDep
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Assign:;
    {
      register Tree_yAssign *W_51 = &t->U_1.V_36.Assign;

      ActionsDep(W_51->Results);
      IO_WriteS(Tree_f, (STRING)":=", 2L);
      ActionsDep(W_51->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      ActionsDep(W_51->Next);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_52 = &t->U_1.V_37.Copy;

      ActionsDep(W_52->Results);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      ActionsDep(W_52->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      ActionsDep(W_52->Next);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_53 = &t->U_1.V_38.TargetCode;

      ActionsDep(W_53->Code);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      ActionsDep(W_53->Next);
      return;
    }
    break;
  case Tree_Order:;
    {
      register Tree_yOrder *W_54 = &t->U_1.V_39.Order;

      ActionsDep(W_54->Next);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_55 = &t->U_1.V_40.Check;

      if (W_55->Statement != Tree_NoTree) {
        if (W_55->Condition != Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"IF NOT (", 8L);
          ActionsDep(W_55->Condition);
          IO_WriteS(Tree_f, (STRING)") THEN ", 7L);
          ActionsDep(W_55->Statement);
          IO_WriteS(Tree_f, (STRING)"; END;", 6L);
          IO_WriteNl(Tree_f);
        } else {
          ActionsDep(W_55->Statement);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      } else {
        IO_WriteS(Tree_f, (STRING)"IF ", 3L);
        ActionsDep(W_55->Condition);
        IO_WriteS(Tree_f, (STRING)" THEN END;", 10L);
        IO_WriteNl(Tree_f);
      }
      ActionsDep(W_55->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_56 = &t->U_1.V_15.Designator;

      TheAttr = Tree_IdentifyAttribute(ActClass, W_56->Selector);
      if (TheAttr != Tree_NoTree) {
        Node = TheAttr->U_1.V_9.Child.Class;
        if (Node != Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"$", 1L);
          Tree_WN((LONGINT)TheAttr->U_1.V_9.Child.ChildIndex);
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
            IO_WriteS(Tree_f, (STRING)".Scan", 5L);
            if (W_56->Attribute == Tree_iPosition) {
            } else if (IN(Tree_String, Node->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, Node->U_1.V_5.Class.Properties)) {
              IO_WriteS(Tree_f, (STRING)".yy", 3L);
              Tree_WN((LONGINT)Node->U_1.V_5.Class.Code);
            } else {
              IO_WriteS(Tree_f, (STRING)".", 1L);
              Tree_WI(Node->U_1.V_5.Class.Selector);
            }
          }
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_56->Attribute);
        } else {
          Tree_WI(W_56->Selector);
          IO_WriteS(Tree_f, (STRING)":", 1L);
          Tree_WI(W_56->Attribute);
        }
      } else {
        Tree_WI(W_56->Selector);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_56->Attribute);
      }
      ActionsDep(W_56->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_57 = &t->U_1.V_16.Ident;

      TheAttr = Tree_IdentifyAttribute(ActClass, W_57->Attribute);
      if (TheAttr != Tree_NoTree) {
        Node = GetBaseClass(TheClass);
        if (IN(Tree_String, Node->U_1.V_5.Class.Properties) && !IN(Tree_HasSelector, Node->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)"$$.yy", 5L);
          Tree_WN((LONGINT)Node->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_57->Attribute);
        } else {
          IO_WriteS(Tree_f, (STRING)"$$.", 3L);
          Tree_WI(Node->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_57->Attribute);
        }
      } else {
        Tree_WI(W_57->Attribute);
      }
      ActionsDep(W_57->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_58 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_58->Code);
      ActionsDep(W_58->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_59 = &t->U_1.V_19.Anys;

      ActionsDep(W_59->Layouts);
      ActionsDep(W_59->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_60 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_60->Code);
      ActionsDep(W_60->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void WriteName
# ifdef __STDC__
(Idents_tIdent Name)
# else
(Name)
Idents_tIdent Name;
# endif
{
  struct S_20 yyTempo;

  if (Name == iOper) {
    IOUtils_WriteBackslash(Tree_f);
    Tree_WI(Name);
    return;
  }
  if (Name == iLeft) {
    IOUtils_WriteBackslash(Tree_f);
    Tree_WI(Name);
    return;
  }
  if (Name == iRight) {
    IOUtils_WriteBackslash(Tree_f);
    Tree_WI(Name);
    return;
  }
  if (Name == iNone) {
    IOUtils_WriteBackslash(Tree_f);
    Tree_WI(Name);
    return;
  }
  if (Name == iPrec) {
    IOUtils_WriteBackslash(Tree_f);
    Tree_WI(Name);
    return;
  }
  if (Name == iRule) {
    IOUtils_WriteBackslash(Tree_f);
    Tree_WI(Name);
    return;
  }
  Tree_WI(Name);
  return;
}

void GramMod_BeginGramMod
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_ArrayToString((STRING)"OPER", 4L, &s);
  iOper = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"RIGHT", 5L, &s);
  iRight = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"LEFT", 4L, &s);
  iLeft = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"NONE", 4L, &s);
  iNone = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"PREC", 4L, &s);
  iPrec = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"RULE", 4L, &s);
  iRule = Idents_MakeIdent(&s);
}

void GramMod_CloseGramMod
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

void GramMod__init()
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
    Strings__init();
    StringMem__init();
    Idents__init();
    Texts__init();
    Sets__init();
    IOUtils__init();
    Tree__init();
    Strings__init();

    GramMod_yyf = IO_StdOutput;
    GramMod_Exit = yyExit;
    GramMod_BeginGramMod();
  }
}
