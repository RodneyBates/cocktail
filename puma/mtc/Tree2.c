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
static void yyGetTree2 ARGS((yyPtrtTree yyt));
static void yyGet ARGS((BYTE yyx[], LONGCARD ));
static void yyGetIdent ARGS((Idents_tIdent *yyi));


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

Tree_tTree Tree2_GetTree2
# ifdef __STDC__
(IO_tFile yyyf)
# else
(yyyf)
IO_tFile yyyf;
# endif
{
  Tree_tTree yyt;

  yyf = yyyf;
  if (yyRecursionLevel == 0) {
    yyLabelCount = 0;
  }
  INC(yyRecursionLevel);
  yyGetTree2((yyPtrtTree)ADR(yyt));
  DEC(yyRecursionLevel);
  return yyt;
}

static void yyGetTree2
# ifdef __STDC__
(yyPtrtTree yyt)
# else
(yyt)
yyPtrtTree yyt;
# endif
{
  for (;;) {
    yyc = IO_ReadC(yyf);
    switch (yyc) {
    case yyNil:;
      *yyt = Tree_NoTree;
      return;
      break;
    case yyLabelUse:;
      yyGet((WORD *)&yyLabel, (LONGCARD)sizeof(yyLabel));
      *yyt = yyMapToTree(yyLabel);
      return;
      break;
    case yyLabelDef:;
      yyGet((WORD *)&yyLabel, (LONGCARD)sizeof(yyLabel));
      yyKind = ORD(IO_ReadC(yyf));
      *yyt = Tree_MakeTree(yyKind);
      if (yyLabel != yyMapToLabel(*yyt)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"Tree2: error in GetTree2", 24L);
        IO_WriteNl((System_tFile)IO_StdError);
        (*Tree_yyExit)();
      }
      break;
    default :
      yyKind = ORD(yyc);
      *yyt = Tree_MakeTree(yyKind);
      break;
    }
    switch (yyKind) {
    case Tree_Class:;
      yyGetIdent(&(*yyt)->U_1.V_5.Class.Name);
      yyGet((WORD *)&(*yyt)->U_1.V_5.Class.Properties, (LONGCARD)sizeof((*yyt)->U_1.V_5.Class.Properties));
      yyGetTree2((yyPtrtTree)ADR((*yyt)->U_1.V_5.Class.Attributes));
      yyGetTree2((yyPtrtTree)ADR((*yyt)->U_1.V_5.Class.Extensions));
      yyGetTree2((yyPtrtTree)ADR((*yyt)->U_1.V_5.Class.BaseClass));
      yyt = (yyPtrtTree)ADR((*yyt)->U_1.V_5.Class.Next);
      break;
    case Tree_AttrOrAction:;
      yyt = (yyPtrtTree)ADR((*yyt)->U_1.V_8.AttrOrAction.Next);
      break;
    case Tree_Child:;
      yyGetIdent(&(*yyt)->U_1.V_9.Child.Name);
      yyGetIdent(&(*yyt)->U_1.V_9.Child.Type);
      yyGet((WORD *)&(*yyt)->U_1.V_9.Child.Properties, (LONGCARD)sizeof((*yyt)->U_1.V_9.Child.Properties));
      yyt = (yyPtrtTree)ADR((*yyt)->U_1.V_9.Child.Next);
      break;
    case Tree_Attribute:;
      yyGetIdent(&(*yyt)->U_1.V_10.Attribute.Name);
      yyGetIdent(&(*yyt)->U_1.V_10.Attribute.Type);
      yyGet((WORD *)&(*yyt)->U_1.V_10.Attribute.Properties, (LONGCARD)sizeof((*yyt)->U_1.V_10.Attribute.Properties));
      yyt = (yyPtrtTree)ADR((*yyt)->U_1.V_10.Attribute.Next);
      break;
    case Tree_ActionPart:;
      yyt = (yyPtrtTree)ADR((*yyt)->U_1.V_11.ActionPart.Next);
      break;
    default :
      return;
      break;
    }
  } EXIT_1:;
}

static void yyGet
# ifdef __STDC__
(BYTE yyx[], LONGCARD O_1)
# else
(yyx, O_1)
BYTE yyx[];
LONGCARD O_1;
# endif
{
  INTEGER yyi;

  yyi = IO_Read(yyf, ADR1(yyx), (LONGCARD)((INTEGER)(O_1 - 1) + 1));
}

static void yyGetIdent
# ifdef __STDC__
(Idents_tIdent *yyi)
# else
(yyi)
Idents_tIdent *yyi;
# endif
{
  Strings_tString yys;

  Strings_ReadL(yyf, &yys);
  *yyi = Idents_MakeIdent(&yys);
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
