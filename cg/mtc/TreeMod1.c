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

#ifndef DEFINITION_IO
#include "IO.h"
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

#ifndef DEFINITION_TreeMod2
#include "TreeMod2.h"
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

#ifndef DEFINITION_TreeMod1
#include "TreeMod1.h"
#endif

IO_tFile TreeMod1_yyf;
PROC TreeMod1_Exit;

static INTEGER ConstCount, ListCount;
static Idents_tIdent iRange, iClassName;
static Tree_tTree Node;
static SHORTCARD gBitCount;
static SHORTCARD i, MaxBit;
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
static void ConstDeclsPre ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void ConstDeclsPost ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void PointerTypes ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void TypeDeclNode ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void TypeDeclRecord ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureDeclsn ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureHeadingm ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureBodyn ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureBodym ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void ReleaseAttributes1 ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void ReleaseAttributes2 ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void TraverseTD ARGS((Tree_tTree t));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static void TraverseBU ARGS((Tree_tTree t));
struct S_17 {
    union {
        char dummy;
    } U_1;
};
static void Reverse1 ARGS((Tree_tTree t));
struct S_18 {
    union {
        char dummy;
    } U_1;
};
static void Reverse2 ARGS((Tree_tTree t));
struct S_19 {
    union {
        char dummy;
    } U_1;
};
static void Copy ARGS((Tree_tTree t));
struct S_20 {
    union {
        char dummy;
    } U_1;
};
static void CheckAttributes ARGS((Tree_tTree t));
struct S_21 {
    union {
        char dummy;
    } U_1;
};
static void InitTypeRange ARGS((Tree_tTree t));
struct S_22 {
    union {
        char dummy;
    } U_1;
};
static void InitTypeRange2 ARGS((Tree_tTree t));
struct S_23 {
    union {
        char dummy;
    } U_1;
};
static void QueryAttributes ARGS((Tree_tTree t));
struct S_24 {
    union {
        char dummy;
    } U_1;
};
static void IsEqualAttributes ARGS((Tree_tTree t));
struct S_25 {
    union {
        char dummy;
    } U_1;
};
static void InitAttributes ARGS((Tree_tTree t));
struct S_26 {
    union {
        char dummy;
    } U_1;
};
static void InitNodeSize ARGS((Tree_tTree t));
struct S_27 {
    union {
        char dummy;
    } U_1;
};
struct S_28 {
    union {
        char dummy;
    } U_1;
};
static void ImportConst ARGS((Tree_tTree t));
struct S_29 {
    union {
        char dummy;
    } U_1;
};
static void CompMaxBit ARGS((Tree_tTree t));
struct S_30 {
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeMod1, routine ", 32L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeMod1_Exit)();
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

void TreeMod1_TreeDefMod
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
  if (t->U_1.V_1.Kind == Tree_Ag) {
    {
      register Tree_yAg *W_1 = &t->U_1.V_26.Ag;

      IO_WriteS(Tree_f, (STRING)"DEFINITION MODULE ", 18L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"FROM ", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" IMPORT ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)", tProcTree;", 12L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"IMPORT SYSTEM, IO;", 18L);
      IO_WriteNl(Tree_f);
      TreeMod2_WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Import);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ImportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Import);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"CONST", 5L);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" = NIL;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesPreAndPost(W_1->Classes, (Tree_ProcOfT)ConstDeclsPre, (Tree_ProcOfT)ConstDeclsPost);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE ", 5L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" = POINTER TO yyNode;", 21L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('^'), &Tree_Options)) {
          Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)PointerTypes);
        }
        IO_WriteS(Tree_f, (STRING)"tProcTree = PROCEDURE (", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      TreeMod2_WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ExportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Export);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# ifndef yyNodeHead", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# define yyNodeHead", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE", 4L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('L'), &Tree_Options)) {
          MaxBit = 0;
          Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)CompMaxBit);
          IO_WriteS(Tree_f, (STRING)"yytNodeHead = RECORD yyKind, yyMark, yyOffset: SHORTCARD; yyParent: ", 68L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)"; yyIsComp0", 11L);
          if (Sets_IsElement(ORD('5'), &Tree_Options)) {
            IO_WriteS(Tree_f, (STRING)", yyIsDone0", 11L);
          }
          {
            SHORTCARD B_3 = 1, B_4 = (MaxBit - 1) / TreeMod1_BSS;

            if (B_3 <= B_4)
              for (i = B_3;; i += 1) {
                IO_WriteS(Tree_f, (STRING)", yyIsComp", 10L);
                Tree_WN((LONGINT)i);
                if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                  IO_WriteS(Tree_f, (STRING)", yyIsDone", 10L);
                  Tree_WN((LONGINT)i);
                }
                if (i >= B_4) break;
              }
          }
          IO_WriteS(Tree_f, (STRING)": BITSET; yyNodeHead END;", 25L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yytNodeHead = RECORD yyKind, yyMark: SHORTCARD; yyNodeHead END;", 63L);
          IO_WriteNl(Tree_f);
        }
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)TypeDeclNode);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"yyNode = RECORD", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"CASE : SHORTCARD OF", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"| 0: Kind: SHORTCARD;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WN(Tree_ClassCount + 1);
        IO_WriteS(Tree_f, (STRING)": yyHead: yytNodeHead;", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)TypeDeclRecord);
        IO_WriteS(Tree_f, (STRING)"END;", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"END;", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR ", 4L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"Root        : ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR HeapUsed   : LONGCARD;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyPoolFreePtr, yyPoolMaxPtr        : SYSTEM.ADDRESS;", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyNodeSize : ARRAY [0..", 27L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)"] OF SHORTCARD;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyExit     : PROC;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyAlloc      (): ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Make", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"  (Kind: SHORTCARD): ", 21L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE IsType       (Tree: ", 30L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; Kind: SHORTCARD): BOOLEAN;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ProcedureDeclsn);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ProcedureHeadingm);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('f'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Release", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"     (Tree: ", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('F'), &Tree_Options) && !Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Release", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Module;", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node   (f: IO.tFile; Tree: ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"       (f: IO.tFile; Tree: ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Read", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"        (f: IO.tFile): ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Put", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (f: IO.tFile; Tree: ", 21L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Get", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (f: IO.tFile): ", 16L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Traverse", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD  (Tree: ", 11L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; Proc: tProcTree);", 19L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Traverse", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU  (Tree: ", 11L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; Proc: tProcTree);", 19L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Reverse", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"     (Tree: ", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Copy", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"        (Tree: ", 15L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('k'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Check", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"       (Tree: ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN;", 11L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Query", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"       (Tree: ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('='), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE IsEqual", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"     (Tree1, Tree2: ", 20L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN;", 11L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Init", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"        (Tree: ", 15L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void ConstDeclsPre
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
      register Tree_yClass *W_2 = &t->U_1.V_5.Class;

      if (!IN(Tree_Abstract, W_2->Properties)) {
        INC(ConstCount);
        if (!IN(Tree_Ignore, W_2->Properties)) {
          Tree_WI(W_2->Name);
          IO_WriteS(Tree_f, (STRING)" = ", 3L);
          Tree_WN(ConstCount);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
  }
}

static void ConstDeclsPost
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
      register Tree_yClass *W_3 = &t->U_1.V_5.Class;

      if (Sets_IsElement(ORD('+'), &Tree_Options)) {
        if (!IN(Tree_Abstract, W_3->Properties)) {
          if (!IN(Tree_Ignore, W_3->Properties)) {
            Tree_WI(W_3->Name);
            IO_WriteS(Tree_f, (STRING)"Max = ", 6L);
            Tree_WN(ConstCount);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
        }
      }
      return;
    }
  }
}

static void PointerTypes
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
      register Tree_yClass *W_4 = &t->U_1.V_5.Class;

      if (!IN(Tree_Abstract, W_4->Properties)) {
        if (!IN(Tree_Ignore, W_4->Properties)) {
          IO_WriteS(Tree_f, (STRING)"p", 1L);
          Tree_WI(W_4->Name);
          IO_WriteS(Tree_f, (STRING)" = ", 3L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
  }
}

static void TypeDeclNode
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
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_5->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"y", 1L);
        Tree_WI(W_5->Name);
        IO_WriteS(Tree_f, (STRING)" = RECORD yyHead: yytNodeHead; ", 31L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)TypeDeclNode);
        IO_WriteS(Tree_f, (STRING)"END;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_6 = &t->U_1.V_9.Child;

      Tree_WI(W_6->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)"; ", 2L);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_7 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_7->Properties) == 0X0L) {
        Tree_WI(W_7->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Tree_WI(W_7->Type);
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void TypeDeclRecord
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
      register Tree_yClass *W_8 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_8->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)": y", 3L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ProcedureDeclsn
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
      register Tree_yClass *W_9 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_9->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE n", 11L);
        Tree_WI(W_9->Name);
        IO_WriteS(Tree_f, (STRING)" (): ", 5L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ProcedureHeadingm
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
      register Tree_yClass *W_10 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_10->Properties) == 0X0L) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"PROCEDURE m", 11L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureHeadingm);
        IO_WriteS(Tree_f, (STRING)"): ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_11 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_11->Properties)) {
        if (ListCount > 0) {
          IO_WriteS(Tree_f, (STRING)"; ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"p", 1L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Tree_WI(Tree_itTree);
        INC(ListCount);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_12 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Input, W_12->Properties)) {
        if (ListCount > 0) {
          IO_WriteS(Tree_f, (STRING)"; ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"p", 1L);
        Tree_WI(W_12->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Tree_WI(W_12->Type);
        INC(ListCount);
      }
      return;
    }
    break;
  default :
    break;
  }
}

void TreeMod1_TreeImplMod
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
  if (t->U_1.V_1.Kind == Tree_Ag) {
    {
      register Tree_yAg *W_13 = &t->U_1.V_26.Ag;

      IO_WriteS(Tree_f, (STRING)"IMPLEMENTATION MODULE ", 22L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(ptr, size)    ptr := yyPoolFreePtr; ", 53L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IF SYSTEM.ADDRESS (ptr) >= yyPoolMaxPtr THEN ptr := yyAlloc (); END; ", 71L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  INC (yyPoolFreePtr, size);", 28L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyFREE(ptr, size)     ", 31L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT SYSTEM, System, General, Memory, DynArray, IO, Layout, StringMem, Strings, Idents, Texts, Sets, Positions;", 113L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"FROM ", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" IMPORT ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)", tProcTree, Make", 17L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)", IsType, yyExit,", 17L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)ImportConst);
        IO_WriteS(Tree_f, (STRING)"yyAlloc, yyPoolFreePtr, yyPoolMaxPtr, yyNodeSize;", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      TreeMod2_WriteLine(W_13->TreeCodes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_13->TreeCodes->U_1.V_12.Codes.Global);
      Node = W_13->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.GlobalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Global);
        Node = Node->U_1.V_43.Module.Next;
      }
      TreeMod2_WriteLine(W_13->TreeCodes->U_1.V_12.Codes.LocalLine);
      Texts_WriteText(Tree_f, W_13->TreeCodes->U_1.V_12.Codes.Local);
      Node = W_13->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.LocalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"CONST yyBlockSize = 20480;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yytBlockPtr   = POINTER TO yytBlock;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yytBlock      = RECORD", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                    yyBlock    : ARRAY [1..yyBlockSize] OF CHAR;", 64L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                    yySuccessor: yytBlockPtr;", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                 END;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyBlockList        : yytBlockPtr;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyMaxSize, yyi     : SHORTCARD;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyTypeRange        : ARRAY [0..", 35L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)"] OF SHORTCARD;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyAlloc (): ", 22L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyBlockPtr        : yytBlockPtr;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyBlockPtr   := yyBlockList;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyBlockList  := Memory.Alloc (SYSTEM.TSIZE (yytBlock));", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyBlockList^.yySuccessor := yyBlockPtr;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyPoolFreePtr        := SYSTEM.ADR (yyBlockList^.yyBlock);", 60L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyPoolMaxPtr := yyPoolFreePtr + yyBlockSize - yyMaxSize + 1;", 62L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC (HeapUsed, yyBlockSize);", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyPoolFreePtr;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyAlloc;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Make", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind: SHORTCARD): ", 22L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyByteCount       : LONGINT;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyt       : ", 17L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyALLOC (yyt, yyNodeSize [yyKind])", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.yyHead.yyMark := 0;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.Kind := yyKind;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyt;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Make", 9L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE IsType (yyTree: ", 26L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yyKind: SHORTCARD): BOOLEAN;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN (yyTree # ", 19L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") AND (yyKind <= yyTree^.Kind) AND (yyTree^.Kind <= yyTypeRange [yyKind]);", 74L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END IsType;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)ProcedureBodyn);
      }
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)ProcedureBodym);
      }
      TreeMod2_TreeIO(t);
      if (Sets_IsElement(ORD('f'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Release", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyRelease", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Release", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyChild    : ", 17L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyRelease", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN RETURN; END;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE yyt^.Kind OF", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)ReleaseAttributes1);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  DEC (yyt^.yyHead.yyMark);", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt^.yyHead.yyMark = 0 THEN", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyt^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)ReleaseAttributes2);
        IO_WriteS(Tree_f, (STRING)"   ELSE", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyFREE (yyt, yyNodeSize [yyt^.Kind])", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyRelease", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('F'), &Tree_Options) && !Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Release", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Module;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyBlockPtr        : yytBlockPtr;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  WHILE yyBlockList # NIL DO", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyBlockPtr  := yyBlockList;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyBlockList := yyBlockList^.yySuccessor;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Memory.Free (SYSTEM.TSIZE (yytBlock), yyBlockPtr);", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyPoolFreePtr        := NIL;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyPoolMaxPtr := NIL;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  HeapUsed     := 0;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Release", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Module;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options) || Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"VAR yyProc     : tProcTree;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Traverse", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD (yyt: ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yyyProc: tProcTree);", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyProc := yyyProc;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyTraverse", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD (yyt);", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Traverse", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD;", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyTraverse", 20L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD (yyt: ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF (yyt = ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") OR (yyt^.yyHead.yyMark = 0) THEN RETURN; END;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyt^.yyHead.yyMark := 0;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyProc (yyt);", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyt^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)TraverseTD);
        IO_WriteS(Tree_f, (STRING)"   ELSE RETURN;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyTraverse", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD;", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Traverse", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU (yyt: ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yyyProc: tProcTree);", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyProc := yyyProc;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyTraverse", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU (yyt);", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Traverse", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU;", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyTraverse", 20L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU (yyt: ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF (yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") OR (yyt^.yyHead.yyMark = 0) THEN RETURN; END;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.yyHead.yyMark := 0;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE yyt^.Kind OF", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)TraverseBU);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyProc (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyTraverse", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU;", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Reverse", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyOld: ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyNew, yyNext, yyTail     : ", 33L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyNew        := yyOld;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyTail       := yyOld;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyOld^.Kind OF", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)Reverse1);
        IO_WriteS(Tree_f, (STRING)"   ELSE EXIT;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyNew       := yyOld;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyOld       := yyNext;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE yyTail^.Kind OF", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)Reverse2);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyNew;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Reverse", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"CONST yyInitOldToNewStoreSize  = 32;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE yytOldToNew = RECORD yyOld, yyNew: ", 40L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyOldToNewStoreSize        : LONGINT;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyOldToNewStorePtr : POINTER TO ARRAY [0..50000] OF yytOldToNew;", 68L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyOldToNewCount    : INTEGER;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyStoreOldToNew (yyOld, yyNew: ", 41L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF (yyOldToNewCount = yyOldToNewStoreSize) THEN", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   DynArray.ExtendArray (yyOldToNewStorePtr, yyOldToNewStoreSize, SYSTEM.TSIZE (yytOldToNew));", 94L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyOldToNewStorePtr^[yyOldToNewCount].yyOld := yyOld;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyOldToNewStorePtr^[yyOldToNewCount].yyNew := yyNew;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC (yyOldToNewCount);", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyStoreOldToNew;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMapOldToNew (yyOld: ", 32L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi: INTEGER;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO yyOldToNewCount - 1 DO", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyOldToNewStorePtr^[yyi].yyOld = yyOld THEN", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN yyOldToNewStorePtr^[yyi].yyNew;", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyMapOldToNew;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyCopy", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yyNew: yyPtrtTree);", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN yyNew^ := ", 16L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"; RETURN; END;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt^.yyHead.yyMark = 0 THEN yyNew^ := yyMapOldToNew (yyt); RETURN; END;", 77L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyNew^ := Make", 17L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyt^.Kind);", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt^.yyHead.yyMark > 1 THEN yyStoreOldToNew (yyt, yyNew^); END;", 69L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyt^.yyHead.yyMark := 0;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyt^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)Copy);
        IO_WriteS(Tree_f, (STRING)"   ELSE", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyCopy", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Copy", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyNew     : ", 17L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyOldToNewCount := 0;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyCopy", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt, SYSTEM.ADR (yyNew));", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyNew;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Copy", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('k'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Check", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyCheck", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Check", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyCheckChild (yyParent, yyChild: ", 43L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yyType: SHORTCARD; yySelector: ARRAY OF CHAR): BOOLEAN;", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" CONST yyf     = IO.StdError;", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yySuccess : BOOLEAN;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySuccess := IsType (yyChild, yyType);", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF NOT yySuccess THEN", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (yyf, 'CheckTree: parent = ');", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Write", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (yyf, yyParent);", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteNl (yyf);", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (yyf, 'selector: ');", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (yyf, yySelector);", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (yyf, ', child = ');", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Write", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (yyf, yyChild);", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteNl (yyf);", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyCheck", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyChild) AND yySuccess;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyCheckChild;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyCheck", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyResult  : BOOLEAN;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN RETURN FALSE;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ELSIF yyt^.yyHead.yyMark = 0 THEN RETURN TRUE;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.yyHead.yyMark := 0;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyResult := TRUE;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE yyt^.Kind OF", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)CheckAttributes);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyResult;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyCheck", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"CONST yyyWrite = 1; yyyRead = 2; yyyQuit = 3;", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyString   : ARRAY [0..31] OF CHAR;", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyLength   : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyCh       : CHAR;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyState    : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyyIsEqual (yya: ARRAY OF CHAR): BOOLEAN;", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF (yyLength >= 0) AND (yyString [yyLength] = ' ') THEN", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyLength - 1 # INTEGER (HIGH (yya)) THEN RETURN FALSE; END;", 65L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   FOR yyi := 0 TO yyLength - 1 DO", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF yyString [yyi] # yya [yyi] THEN RETURN FALSE; END;", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyLength > INTEGER (HIGH (yya)) THEN RETURN FALSE; END;", 61L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   FOR yyi := 0 TO yyLength DO", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF yyString [yyi] # yya [yyi] THEN RETURN FALSE; END;", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN TRUE;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyyIsEqual;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Query", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyState := yyyWrite;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyState OF", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyyQuit   : RETURN;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyyWrite  : Write", 22L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (IO.StdOutput, yyt); yyState := yyyRead;", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyyRead   : IO.WriteS (IO.StdOutput, '? '); yyLength := -1; yyCh := IO.ReadC (IO.StdInput);", 96L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    WHILE yyCh # 12C DO INC (yyLength); yyString [yyLength] := yyCh; yyCh := IO.ReadC (IO.StdInput); END;", 105L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF    yyyIsEqual ('parent') THEN yyState := yyyWrite; RETURN;", 65L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSIF yyyIsEqual ('quit'  ) THEN yyState := yyyQuit ; RETURN;", 65L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSIF yyt # ", 16L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     CASE yyt^.Kind OF", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)QueryAttributes);
        IO_WriteS(Tree_f, (STRING)"     ELSE", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     END;", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Query", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('='), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIsEqual (yya, yyb: ARRAY OF SYSTEM.BYTE): BOOLEAN;", 62L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO INTEGER (HIGH (yya)) DO", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yya [yyi] # yyb [yyi] THEN RETURN FALSE; END;", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN TRUE;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyIsEqual;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE IsEqual", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt1, yyt2: ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt1 = yyt2 THEN RETURN TRUE; END;", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF (yyt1 = ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") OR (yyt2 = ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") OR (yyt1^.Kind # yyt2^.Kind) THEN RETURN FALSE; END;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE yyt1^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)IsEqualAttributes);
        IO_WriteS(Tree_f, (STRING)"  ELSE RETURN TRUE;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END IsEqual", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        MaxBit = 0;
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)CompMaxBit);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Init", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        {
          SHORTCARD B_5 = 0, B_6 = (MaxBit - 1) / TreeMod1_BSS;

          if (B_5 <= B_6)
            for (i = B_5;; i += 1) {
              IO_WriteS(Tree_f, (STRING)"   yyt^.yyHead.yyIsComp", 23L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)" := {};", 7L);
              IO_WriteNl(Tree_f);
              if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"   yyt^.yyHead.yyIsDone", 23L);
                Tree_WN((LONGINT)i);
                IO_WriteS(Tree_f, (STRING)" := {};", 7L);
                IO_WriteNl(Tree_f);
              }
              if (i >= B_6) break;
            }
        }
        IO_WriteS(Tree_f, (STRING)"   CASE yyt^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)InitAttributes);
        IO_WriteS(Tree_f, (STRING)"   ELSE RETURN;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Init", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMod2_WriteLine(W_13->TreeCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_13->TreeCodes->U_1.V_12.Codes.Begin);
      Node = W_13->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)" END Begin", 10L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMod2_WriteLine(W_13->TreeCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_13->TreeCodes->U_1.V_12.Codes.Close);
      Node = W_13->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)" END Close", 10L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE xxExit;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IO.CloseIO; System.Exit (1);", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END xxExit;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" yyIsInitialized := FALSE;", 26L);
        IO_WriteNl(Tree_f);
      }
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" yyBlockList   := NIL;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyPoolFreePtr := NIL;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyPoolMaxPtr  := NIL;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" HeapUsed      := 0;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyExit        := xxExit;", 25L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)InitNodeSize);
        IO_WriteS(Tree_f, (STRING)" yyMaxSize     := 0;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" FOR yyi := 1 TO ", 17L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyNodeSize [yyi] := LONGINT (BITSET (yyNodeSize [yyi] + CARDINAL (General.MaxAlign) - 1) * General.AlignMasks [General.MaxAlign]);", 132L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMaxSize := General.Max (yyNodeSize [yyi], yyMaxSize);", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END;", 5L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_13->Classes, (Tree_ProcOfT)InitTypeRange);
      }
      if (Sets_IsElement(ORD(';'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" yyRecursionLevel := 0;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyTreeStoreSize := yyInitTreeStoreSize;", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" DynArray.MakeArray (yyTreeStorePtr, yyTreeStoreSize, SYSTEM.TSIZE (", 68L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"));", 3L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" yyOldToNewStoreSize := yyInitOldToNewStoreSize;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" DynArray.MakeArray (yyOldToNewStorePtr, yyOldToNewStoreSize, SYSTEM.TSIZE (yytOldToNew));", 90L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)" Begin", 6L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void ProcedureBodyn
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
      register Tree_yClass *W_14 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_14->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE n", 11L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)" (): ", 5L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyByteCount    : LONGINT;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyt    : ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyALLOC (yyt, yyNodeSize [", 28L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)"])", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.yyHead.yyMark := 0;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.Kind := ", 15L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_14->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodyn);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyt;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END n", 6L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_15 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"  begin", 7L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)"(yyt^.", 6L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_15->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_16 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_16->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"  begin", 7L);
        Tree_WI(W_16->Type);
        IO_WriteS(Tree_f, (STRING)"(yyt^.", 6L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void ProcedureBodym
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
      register Tree_yClass *W_17 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_17->Properties) == 0X0L) {
        ProcedureHeadingm(t);
        IO_WriteS(Tree_f, (STRING)" VAR yyByteCount    : LONGINT;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyt    : ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyALLOC (yyt, yyNodeSize [", 28L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)"])", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.yyHead.yyMark := 0;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt^.Kind := ", 15L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_17->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"  WITH yyt^.", 12L);
          Tree_WI(W_17->Name);
          IO_WriteS(Tree_f, (STRING)" DO", 3L);
          IO_WriteNl(Tree_f);
          Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodym);
          IO_WriteS(Tree_f, (STRING)"  END;", 6L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  RETURN yyt;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END m", 6L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_18 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_18->Properties)) {
        IO_WriteS(Tree_f, (STRING)"   ", 3L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)" := p", 5L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"   begin", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"(", 1L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_19 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_19->Properties) == 0X0L) {
        if (IN(Tree_Input, W_19->Properties)) {
          IO_WriteS(Tree_f, (STRING)"   ", 3L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)" := p", 5L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"   begin", 8L);
          Tree_WI(W_19->Type);
          IO_WriteS(Tree_f, (STRING)"(", 1L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)")", 1L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void ReleaseAttributes1
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
      register Tree_yClass *W_20 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_20->Properties) == 0X0L && IN(Tree_HasChildren, W_20->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_20->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReleaseAttributes1);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_21 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"close", 5L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_21->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  default :
    break;
  }
}

static void ReleaseAttributes2
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
  case Tree_Class:;
    {
      register Tree_yClass *W_22 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_22->Properties) == 0X0L && IN(Tree_HasAttributes, W_22->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_22->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReleaseAttributes2);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_23 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_23->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"close", 5L);
        Tree_WI(W_23->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_23->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void TraverseTD
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
      register Tree_yClass *W_24 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_24->Properties) == 0X0L && IN(Tree_HasChildren, W_24->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_24->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_24->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseTD);
        if (TreeMod2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt := yyt^.", 12L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeMod2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_25 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD (yyt^.", 9L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_25->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void TraverseBU
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
      register Tree_yClass *W_26 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_26->Properties) == 0X0L && IN(Tree_HasChildren, W_26->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_26->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_26->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseBU);
        if (TreeMod2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"BU (yyt^.", 9L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeMod2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_27 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU (yyt^.", 9L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_27->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void Reverse1
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_28 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_28->Properties) == 0X0L) {
        iClassName = W_28->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse1);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_29 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_29->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)": yyNext := yyOld^.", 19L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_29->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteS(Tree_f, (STRING)" yyOld^.", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_29->Name);
        IO_WriteS(Tree_f, (STRING)" := yyNew;", 10L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void Reverse2
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
  case Tree_Class:;
    {
      register Tree_yClass *W_30 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_30->Properties) == 0X0L) {
        iClassName = W_30->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse2);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_31 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_31->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)": yyTail^.", 10L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_31->Name);
        IO_WriteS(Tree_f, (STRING)" := yyOld;", 10L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void Copy
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_32 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_32->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_32->Name);
        IO_WriteS(Tree_f, (STRING)": yyNew^^.", 10L);
        Tree_WI(W_32->Name);
        IO_WriteS(Tree_f, (STRING)" := yyt^.", 9L);
        Tree_WI(W_32->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_32->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Copy);
        if (TreeMod2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt := yyt^.", 12L);
          Tree_WI(W_32->Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeMod2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"yyNew := SYSTEM.ADR (yyNew^^.", 29L);
          Tree_WI(W_32->Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeMod2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_33 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"copy", 4L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (yyNew^^.", 10L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        IO_WriteS(Tree_f, (STRING)"yyt^.", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_34 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_34->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"copy", 4L);
        Tree_WI(W_34->Type);
        IO_WriteS(Tree_f, (STRING)" (yyNew^^.", 10L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_34->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        IO_WriteS(Tree_f, (STRING)"yyt^.", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_34->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckAttributes
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
  case Tree_Class:;
    {
      register Tree_yClass *W_35 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_35->Properties) == 0X0L && IN(Tree_HasChildren, W_35->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_35->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_35->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)CheckAttributes);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_36 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"yyResult := yyCheckChild (yyt, yyt^.", 36L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_36->Name);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Tree_WI(W_36->Type);
      IO_WriteS(Tree_f, (STRING)", '", 3L);
      Tree_WI(W_36->Name);
      IO_WriteS(Tree_f, (STRING)"') AND yyResult;", 16L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_37 = &t->U_1.V_10.Attribute;

        if (!IN(Tree_Link, W_37->Properties)) {
          goto EXIT_1;
        }
        IO_WriteS(Tree_f, (STRING)"yyResult := yyCheckChild (yyt, yyt^.", 36L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_37->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        Tree_WI(W_37->Type);
        IO_WriteS(Tree_f, (STRING)", '", 3L);
        Tree_WI(W_37->Name);
        IO_WriteS(Tree_f, (STRING)"') AND yyResult;", 16L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_1:;
    break;
  default :
    break;
  }
}

static void InitTypeRange
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
      register Tree_yClass *W_38 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_38->Properties) == 0X0L) {
        iRange = W_38->Name;
        Tree_ForallClasses(W_38->Extensions, (Tree_ProcOfT)InitTypeRange2);
        IO_WriteS(Tree_f, (STRING)" yyTypeRange [", 14L);
        Tree_WI(W_38->Name);
        IO_WriteS(Tree_f, (STRING)"] := ", 5L);
        Tree_WI(iRange);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void InitTypeRange2
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
      register Tree_yClass *W_39 = &t->U_1.V_5.Class;

      iRange = W_39->Name;
      return;
    }
  }
}

static void QueryAttributes
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_40 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_40->Properties) == 0X0L && IN(Tree_HasChildren, W_40->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_40->Name);
        IO_WriteS(Tree_f, (STRING)": IF FALSE THEN", 15L);
        IO_WriteNl(Tree_f);
        iClassName = W_40->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)QueryAttributes);
        IO_WriteS(Tree_f, (STRING)"END;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_41 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"ELSIF yyyIsEqual ('", 19L);
      Tree_WI(W_41->Name);
      IO_WriteS(Tree_f, (STRING)"') THEN Query", 13L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_41->Name);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_42 = &t->U_1.V_10.Attribute;

        if (!IN(Tree_Link, W_42->Properties)) {
          goto EXIT_2;
        }
        IO_WriteS(Tree_f, (STRING)"ELSIF yyyIsEqual ('", 19L);
        Tree_WI(W_42->Name);
        IO_WriteS(Tree_f, (STRING)"') THEN Query", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_42->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_2:;
    break;
  default :
    break;
  }
}

static void IsEqualAttributes
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_43 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_43->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_43->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_43->Name);
        IO_WriteS(Tree_f, (STRING)": RETURN TRUE", 13L);
        IO_WriteNl(Tree_f);
        iClassName = W_43->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)IsEqualAttributes);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_44 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"AND equal", 9L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" (yyt1^.", 8L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_44->Name);
      IO_WriteS(Tree_f, (STRING)", yyt2^.", 8L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_44->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_45 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_45->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"AND (equal", 10L);
        Tree_WI(W_45->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt1^.", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_45->Name);
        IO_WriteS(Tree_f, (STRING)", yyt2^.", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_45->Name);
        IO_WriteS(Tree_f, (STRING)"))", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void InitAttributes
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
        register Tree_yClass *W_46 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_46->Properties) == 0X0L && IN(Tree_HasChildren, W_46->Properties))) {
          goto EXIT_3;
        }
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_46->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_46->Name;
        gBitCount = W_46->BitCount;
        Tree_ForallAttributes(t, (Tree_ProcOfT)InitAttributes);
        if (TreeMod2_Iterator == Tree_NoTree || !IN(Tree_Input, TreeMod2_Iterator->U_1.V_9.Child.Properties)) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt := yyt^.", 12L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeMod2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
        return;
      }
    } EXIT_3:;
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_47 = &t->U_1.V_9.Child;

        if (!IN(Tree_Input, W_47->Properties)) {
          goto EXIT_4;
        }
        IO_WriteS(Tree_f, (STRING)"WITH yyt^.", 10L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_47->Name);
        IO_WriteS(Tree_f, (STRING)"^.yyHead DO yyOffset := ", 24L);
        Tree_WN((LONGINT)(gBitCount + W_47->BitOffset));
        IO_WriteS(Tree_f, (STRING)"; yyParent := yyt; END;", 23L);
        IO_WriteNl(Tree_f);
        if (!(t != TreeMod2_Iterator)) {
          goto EXIT_4;
        }
        IO_WriteS(Tree_f, (STRING)"Init", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_47->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_4:;
    break;
  default :
    break;
  }
}

static void InitNodeSize
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    for (;;) {
      {
        register Tree_yClass *W_48 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_48->Properties) == 0X0L)) {
          goto EXIT_5;
        }
        IO_WriteS(Tree_f, (STRING)" yyNodeSize [", 13L);
        Tree_WI(W_48->Name);
        IO_WriteS(Tree_f, (STRING)"] := SYSTEM.TSIZE (y", 20L);
        Tree_WI(W_48->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_5:;
  }
}

void TreeMod1_ImportList
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Ag:;
    {
      register Tree_yAg *W_49 = &t->U_1.V_26.Ag;

      IO_WriteS(Tree_f, (STRING)"FROM ", 5L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" IMPORT", 7L);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"Root, Make", 10L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)", IsType,", 9L);
        IO_WriteNl(Tree_f);
      }
      Tree_ForallClasses(W_49->Classes, (Tree_ProcOfT)TreeMod1_ImportList);
      if (Sets_IsElement(ORD('f'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Release", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('F'), &Tree_Options) && !Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Release", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Module,", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Write", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node,", 5L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Write", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Read", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Put", 3L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Get", 3L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Traverse", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD,", 3L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Traverse", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU,", 3L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Reverse", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Copy", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('k'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Check", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Query", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('='), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IsEqual", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Init", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"Begin", 5L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"Close", 5L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_50 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_50->Properties) == 0X0L) {
        Tree_WI(W_50->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        if (Sets_IsElement(ORD('n'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"n", 1L);
          Tree_WI(W_50->Name);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        if (Sets_IsElement(ORD('m'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"m", 1L);
          Tree_WI(W_50->Name);
          IO_WriteS(Tree_f, (STRING)",", 1L);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD('+'), &Tree_Options)) {
          Tree_WI(W_50->Name);
          IO_WriteS(Tree_f, (STRING)"Max,", 4L);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD('^'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"p", 1L);
          Tree_WI(W_50->Name);
          IO_WriteS(Tree_f, (STRING)",", 1L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void ImportConst
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_29 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_51 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_51->Properties) == 0X0L) {
        Tree_WI(W_51->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void CompMaxBit
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_52 = &t->U_1.V_5.Class;

      i = 1;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CompMaxBit);
      MaxBit = General_Max((LONGINT)i, (LONGINT)MaxBit);
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_53 = &t->U_1.V_9.Child;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_53->Properties) == 0X0L)) {
          goto EXIT_6;
        }
        INC(i);
        return;
      }
    } EXIT_6:;
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_54 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_54->Properties) == 0X0L)) {
          goto EXIT_7;
        }
        INC(i);
        return;
      }
    } EXIT_7:;
    break;
  default :
    break;
  }
}

void TreeMod1_BeginTreeMod1
# ifdef __STDC__
()
# else
()
# endif
{
  ConstCount = 0;
}

void TreeMod1_CloseTreeMod1
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

void TreeMod1__init()
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
    IO__init();
    Idents__init();
    Texts__init();
    Sets__init();
    TreeMod2__init();
    IOUtils__init();
    Tree__init();
    Strings__init();

    TreeMod1_yyf = IO_StdOutput;
    TreeMod1_Exit = yyExit;
    TreeMod1_BeginTreeMod1();
  }
}
