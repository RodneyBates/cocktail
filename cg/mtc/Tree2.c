#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_General
#include "General.h"
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

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
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

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Tree2
#include "Tree2.h"
#endif


typedef Tree_tTree *yyPtrtTree;
static IO_tFile yyf;
static SHORTCARD yyLabel;
static SHORTCARD yyKind;
static CHAR yyc;
static Strings_tString yys;
static void yyMark ARGS((Tree_tTree yyt));
#define yyInitTreeStoreSize   32
static LONGINT yyTreeStoreSize;
static struct S_1 {
    Tree_tTree A[50000 + 1];
} *yyTreeStorePtr;
static INTEGER yyLabelCount;
static SHORTINT yyRecursionLevel;
static SHORTCARD yyMapToLabel ARGS((Tree_tTree yyTree));
static Tree_tTree yyMapToTree ARGS((SHORTCARD yyLabel));
#define yyNil   ((CHAR)'\374')
#define yyNoLabel   ((CHAR)'\375')
#define yyLabelDef   ((CHAR)'\376')
#define yyLabelUse   ((CHAR)'\377')
static void yyPutTree2 ARGS((Tree_tTree yyt));
static void yyPut ARGS((BYTE yyx[], LONGCARD ));
static void yyPutIdent ARGS((Idents_tIdent yyi));


static void yyMark
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  for (;;) {
    if (yyt == Tree_NoTree) {
      return;
    }
    INC(yyt->U_1.V_2.yyHead.yyMark);
    if (yyt->U_1.V_2.yyHead.yyMark > 1) {
      return;
    }
    switch (yyt->U_1.V_1.Kind) {
    case Tree_Class:;
      yyMark(yyt->U_1.V_5.Class.Attributes);
      yyMark(yyt->U_1.V_5.Class.Extensions);
      yyMark(yyt->U_1.V_5.Class.BaseClass);
      yyt = yyt->U_1.V_5.Class.Next;
      break;
    case Tree_AttrOrAction:;
      yyt = yyt->U_1.V_8.AttrOrAction.Next;
      break;
    case Tree_Child:;
      yyt = yyt->U_1.V_9.Child.Next;
      break;
    case Tree_Attribute:;
      yyt = yyt->U_1.V_10.Attribute.Next;
      break;
    case Tree_ActionPart:;
      yyt = yyt->U_1.V_11.ActionPart.Next;
      break;
    default :
      return;
      break;
    }
  } EXIT_1:;
}

static SHORTCARD yyMapToLabel
# ifdef __STDC__
(Tree_tTree yyTree)
# else
(yyTree)
Tree_tTree yyTree;
# endif
{
  INTEGER yyi;

  {
    LONGINT B_1 = 1, B_2 = yyLabelCount;

    if (B_1 <= B_2)
      for (yyi = B_1;; yyi += 1) {
        if (yyTreeStorePtr->A[yyi] == yyTree) {
          return yyi;
        }
        if (yyi >= B_2) break;
      }
  }
  INC(yyLabelCount);
  if (yyLabelCount == yyTreeStoreSize) {
    DynArray_ExtendArray((ADDRESS *)&yyTreeStorePtr, &yyTreeStoreSize, (LONGINT)sizeof(Tree_tTree));
  }
  yyTreeStorePtr->A[yyLabelCount] = yyTree;
  return yyLabelCount;
}

static Tree_tTree yyMapToTree
# ifdef __STDC__
(SHORTCARD yyLabel)
# else
(yyLabel)
SHORTCARD yyLabel;
# endif
{
  return yyTreeStorePtr->A[yyLabel];
}

void Tree2_PutTree2
# ifdef __STDC__
(IO_tFile yyyf, Tree_tTree yyt)
# else
(yyyf, yyt)
IO_tFile yyyf;
Tree_tTree yyt;
# endif
{
  yyf = yyyf;
  if (yyRecursionLevel == 0) {
    yyLabelCount = 0;
  }
  INC(yyRecursionLevel);
  yyMark(yyt);
  yyPutTree2(yyt);
  DEC(yyRecursionLevel);
}

static void yyPutTree2
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  for (;;) {
    if (yyt == Tree_NoTree) {
      IO_WriteC(yyf, yyNil);
      return;
    } else if (yyt->U_1.V_2.yyHead.yyMark == 0) {
      IO_WriteC(yyf, yyLabelUse);
      yyLabel = yyMapToLabel(yyt);
      yyPut((WORD *)&yyLabel, (LONGCARD)sizeof(yyLabel));
      return;
    } else if (yyt->U_1.V_2.yyHead.yyMark > 1) {
      IO_WriteC(yyf, yyLabelDef);
      yyLabel = yyMapToLabel(yyt);
      yyPut((WORD *)&yyLabel, (LONGCARD)sizeof(yyLabel));
      IO_WriteC(yyf, CHR(yyt->U_1.V_1.Kind));
    } else {
      IO_WriteC(yyf, CHR(yyt->U_1.V_1.Kind));
    }
    yyt->U_1.V_2.yyHead.yyMark = 0;
    switch (yyt->U_1.V_1.Kind) {
    case Tree_Class:;
      yyPutIdent(yyt->U_1.V_5.Class.Name);
      yyPut((WORD *)&yyt->U_1.V_5.Class.Properties, (LONGCARD)sizeof(yyt->U_1.V_5.Class.Properties));
      yyPutTree2(yyt->U_1.V_5.Class.Attributes);
      yyPutTree2(yyt->U_1.V_5.Class.Extensions);
      yyPutTree2(yyt->U_1.V_5.Class.BaseClass);
      yyt = yyt->U_1.V_5.Class.Next;
      break;
    case Tree_AttrOrAction:;
      yyt = yyt->U_1.V_8.AttrOrAction.Next;
      break;
    case Tree_Child:;
      yyPutIdent(yyt->U_1.V_9.Child.Name);
      yyPutIdent(yyt->U_1.V_9.Child.Type);
      yyPut((WORD *)&yyt->U_1.V_9.Child.Properties, (LONGCARD)sizeof(yyt->U_1.V_9.Child.Properties));
      yyt = yyt->U_1.V_9.Child.Next;
      break;
    case Tree_Attribute:;
      yyPutIdent(yyt->U_1.V_10.Attribute.Name);
      yyPutIdent(yyt->U_1.V_10.Attribute.Type);
      yyPut((WORD *)&yyt->U_1.V_10.Attribute.Properties, (LONGCARD)sizeof(yyt->U_1.V_10.Attribute.Properties));
      yyt = yyt->U_1.V_10.Attribute.Next;
      break;
    case Tree_ActionPart:;
      yyt = yyt->U_1.V_11.ActionPart.Next;
      break;
    default :
      return;
      break;
    }
  } EXIT_2:;
}

static void yyPut
# ifdef __STDC__
(BYTE yyx[], LONGCARD O_1)
# else
(yyx, O_1)
BYTE yyx[];
LONGCARD O_1;
# endif
{
  INTEGER yyi;

  yyi = IO_Write(yyf, ADR1(yyx), (INTEGER)(O_1 - 1) + 1);
}

static void yyPutIdent
# ifdef __STDC__
(Idents_tIdent yyi)
# else
(yyi)
Idents_tIdent yyi;
# endif
{
  Strings_tString yys;

  Idents_GetString(yyi, &yys);
  Strings_WriteL(yyf, &yys);
}

void Tree2_BeginTree2
# ifdef __STDC__
()
# else
()
# endif
{
}

void Tree2_CloseTree2
# ifdef __STDC__
()
# else
()
# endif
{
}

void Tree2__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Tree__init();
    IO__init();
    System__init();
    General__init();
    Memory__init();
    DynArray__init();
    IO__init();
    Layout__init();
    StringMem__init();
    Strings__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Positions__init();
    Tree__init();

    yyRecursionLevel = 0;
    yyTreeStoreSize = yyInitTreeStoreSize;
    DynArray_MakeArray((ADDRESS *)&yyTreeStorePtr, &yyTreeStoreSize, (LONGINT)sizeof(Tree_tTree));
    Tree2_BeginTree2();
  }
}
