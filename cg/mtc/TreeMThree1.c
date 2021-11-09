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

#ifndef DEFINITION_TreeMThree2
#include "TreeMThree2.h"
#endif

#ifndef DEFINITION_TreeMThree2
#include "TreeMThree2.h"
#endif

#ifndef DEFINITION_GenGnat
#include "GenGnat.h"
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

#ifndef DEFINITION_TreeMThree1
#include "TreeMThree1.h"
#endif

IO_tFile TreeMThree1_yyf;
PROC TreeMThree1_Exit;

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
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void TypeDeclNode ARGS((Tree_tTree t, Tree_tTree Parent));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void TypeDeclNodeAttributes ARGS((Tree_tTree t));
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
static void ProcedureHeadingmInterface ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureHeadingm ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void MakeNode ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void IsTypeCases ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureBodyn ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureBodym ARGS((Tree_tTree t));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static void TraverseTD ARGS((Tree_tTree t));
struct S_17 {
    union {
        char dummy;
    } U_1;
};
static void TraverseBU ARGS((Tree_tTree t));
struct S_18 {
    union {
        char dummy;
    } U_1;
};
static void Reverse1 ARGS((Tree_tTree t));
struct S_19 {
    union {
        char dummy;
    } U_1;
};
static void Reverse2 ARGS((Tree_tTree t));
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
struct S_27 {
    union {
        char dummy;
    } U_1;
};
static void ImportConst ARGS((Tree_tTree t));
struct S_28 {
    union {
        char dummy;
    } U_1;
};
static void CompMaxBit ARGS((Tree_tTree t));
struct S_29 {
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeMThree1, routine ", 35L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeMThree1_Exit)();
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

void TreeMThree1_TreeInterface
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

      IO_WriteS(Tree_f, (STRING)"INTERFACE ", 10L);
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
      if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options) || Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Wr ;", 11L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Rd ;", 11L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('~'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT GnatTypes ;", 18L);
        IO_WriteNl(Tree_f);
      }
      TreeMThree2_WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Import);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ImportLine);
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
        IO_WriteS(Tree_f, (STRING)"TYPE SHORTCARD = BITS 16 FOR [ 0 .. 32767 ];", 44L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"tProcTree = PROCEDURE (Tree:", 28L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)") RAISES ANY;", 13L);
        IO_WriteNl(Tree_f);
      }
      TreeMThree2_WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ExportLine);
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
          IO_WriteS(Tree_f, (STRING)"BitSet = SET OF 0 .. ", 21L);
          Tree_WN((LONGINT)MaxBit);
          IO_WriteS(Tree_f, (STRING)" ;", 2L);
          IO_WriteNl(Tree_f);
          MaxBit = 0;
          Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)CompMaxBit);
          IO_WriteS(Tree_f, (STRING)"yytNodeHead = RECORD yyMark, yyOffset: SHORTCARD; yyParent: ", 60L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)"; yyIsComp", 10L);
          if (Sets_IsElement(ORD('5'), &Tree_Options)) {
            IO_WriteS(Tree_f, (STRING)", yyIsDone", 10L);
          }
          IO_WriteS(Tree_f, (STRING)": BitSet ; yyNodeHead END;", 26L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yytNodeHead = RECORD yyMark: SHORTCARD; yyNodeHead END;", 55L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"TYPE ", 5L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" = OBJECT Kind : SHORTCARD ; yyHead : yytNodeHead ; END;", 56L);
        IO_WriteNl(Tree_f);
        TypeDeclNode(W_1->Classes, t);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR ", 4L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"Root        : ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyExit     : PROCEDURE ( ) ;", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"EXCEPTION BadNodeKind ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* Make", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" is deprecated for Modula-3. *)", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"<*OBSOLETE*>PROCEDURE Make", 26L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"  (Kind : SHORTCARD): ", 22L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" RAISES { BadNodeKind } ; ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* IsType is deprecated for Modula-3. *)", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"<*OBSOLETE*>PROCEDURE IsType       (Tree: ", 42L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; Kind : SHORTCARD): BOOLEAN RAISES { BadNodeKind } ;", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Uninitialized node construtors: *)", 37L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_1->Classes, (Tree_ProcOfT)ProcedureDeclsn);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Node constructors with initialization of input children and attributes: *)", 77L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_1->Classes, (Tree_ProcOfT)ProcedureHeadingmInterface);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Ascii node writer: *)", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node   (f: Wr.T; Tree: ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Ascii graph writer: *)", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"       (f: Wr.T; Tree: ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('^'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Html graph writer: *)", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Html ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( f : Wr . T ; Tree : ", 24L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; Title : TEXT := \"\" ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; SuppressNullFields : BOOLEAN := FALSE ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ) ; ", 6L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Ascii graph reader: *)", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Read", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"        (f: Rd.T): ", 19L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Binary graph writer: *) ", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Put", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (f: Wr.T; Tree: ", 17L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Binary graph reader: *)", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Get", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (f: Rd.T): ", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Top down traverser: *)", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Traverse", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD  (Tree: ", 11L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; Proc: tProcTree);", 19L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Bottom up traverser: *)", 26L);
        IO_WriteNl(Tree_f);
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
        IO_WriteS(Tree_f, (STRING)"(* Graph validity checker.  Unless PSG-style classes get added to cg/puma,", 74L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   this is redundant in Modula-3, since the type system ensures validity. *)", 76L);
        IO_WriteNl(Tree_f);
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
      if (Sets_IsElement(ORD('~'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE GnatConvert", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ( GnatTree : GnatTypes . Node_Id ) : ", 38L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" .", 2L);
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
          IO_WriteS(Tree_f, (STRING)"Nk", 2L);
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
            IO_WriteS(Tree_f, (STRING)"Nk", 2L);
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

void TreeMThree1_NodeType
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
  case Tree_Ag:;
    {
      register Tree_yAg *W_4 = &t->U_1.V_26.Ag;

      Tree_WI(Tree_itTree);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      Tree_WI(W_5->Name);
      return;
    }
    break;
  default :
    break;
  }
}

static void TypeDeclNode
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Parent)
# else
(t, Parent)
Tree_tTree t;
Tree_tTree Parent;
# endif
{
  struct S_7 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (Parent == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_6 = &t->U_1.V_5.Class;

      TypeDeclNode(W_6->Extensions, t);
      if ((Tree_NoCodeClass & W_6->Properties) == 0X0L) {
        Tree_WI(W_6->Name);
        IO_WriteS(Tree_f, (STRING)" = ", 3L);
        TreeMThree1_NodeType(Parent);
        IO_WriteS(Tree_f, (STRING)" BRANDED \"", 10L);
        Tree_WI(W_6->Name);
        IO_WriteS(Tree_f, (STRING)"\" OBJECT ", 9L);
        IO_WriteNl(Tree_f);
        Tree_ForallAttributes(W_6->Attributes, (Tree_ProcOfT)TypeDeclNodeAttributes);
        IO_WriteS(Tree_f, (STRING)"  END (* ", 9L);
        Tree_WI(W_6->Name);
        IO_WriteS(Tree_f, (STRING)" *) ;", 5L);
        IO_WriteNl(Tree_f);
      }
      TypeDeclNode(W_6->Next, Parent);
      return;
    }
  }
}

static void TypeDeclNodeAttributes
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
  case Tree_Child:;
    {
      register Tree_yChild *W_7 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      Tree_WI(W_7->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      Tree_WI(W_7->Class->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Tree_WI(Tree_iNoTree);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_8 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_8->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"    ", 4L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Tree_WI(W_8->Type);
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
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
        IO_WriteS(Tree_f, (STRING)" ( ) : ", 7L);
        Tree_WI(W_9->Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ProcedureHeadingmInterface
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
      register Tree_yClass *W_10 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_10->Properties) == 0X0L) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"PROCEDURE m", 11L);
        Tree_WI(W_10->Name);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( ", 4L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureHeadingm);
        IO_WriteS(Tree_f, (STRING)"  ) : ", 6L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
  struct S_11 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_11 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_11->Properties) == 0X0L) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"PROCEDURE m", 11L);
        Tree_WI(W_11->Name);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( ", 4L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureHeadingm);
        IO_WriteS(Tree_f, (STRING)"  ) : ", 6L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)" =", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_12 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_12->Properties)) {
        if (ListCount > 0) {
          IO_WriteS(Tree_f, (STRING)"  ; ", 4L);
        }
        IO_WriteS(Tree_f, (STRING)"p", 1L);
        Tree_WI(W_12->Name);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Tree_WI(W_12->Name);
        IO_WriteS(Tree_f, (STRING)" := NIL ", 8L);
        IO_WriteNl(Tree_f);
        INC(ListCount);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_13 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Input, W_13->Properties)) {
        if (ListCount > 0) {
          IO_WriteS(Tree_f, (STRING)"  ; ", 4L);
        }
        IO_WriteS(Tree_f, (STRING)"p", 1L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Tree_WI(W_13->Type);
        IO_WriteNl(Tree_f);
        INC(ListCount);
      }
      return;
    }
    break;
  default :
    break;
  }
}

void TreeMThree1_TreeModule
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
  if (t->U_1.V_1.Kind == Tree_Ag) {
    {
      register Tree_yAg *W_14 = &t->U_1.V_26.Ag;

      if (Sets_IsElement(ORD('~'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"UNSAFE ", 7L);
      }
      IO_WriteS(Tree_f, (STRING)"MODULE ", 7L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options) || Sets_IsElement(ORD('k'), &Tree_Options) || Sets_IsElement(ORD('q'), &Tree_Options) || Sets_IsElement(ORD('~'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Fmt , Stdio ;", 20L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options) || Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options) || Sets_IsElement(ORD('k'), &Tree_Options) || Sets_IsElement(ORD('q'), &Tree_Options) || Sets_IsElement(ORD('~'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Wr , Text ;", 18L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Lex ;", 12L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Rd ;", 11L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options) || Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Pickle , Atom , Thread ; ", 32L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT FileWr , FileRd , Pipe ; ", 32L);
        IO_WriteNl(Tree_f);
      }
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Process ;", 16L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('~'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"  IMPORT Sinfo , Einfo , Elists , Nlists , Atree , GnatTypes , GnatUtils ;", 74L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IMPORT ", 9L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('^'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"  IMPORT Display ;", 18L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"FROM ", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" IMPORT ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)", tProcTree, yyExit", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_14->Classes, (Tree_ProcOfT)ImportConst);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      TreeMThree2_WriteLine(W_14->TreeCodes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Global);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.GlobalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Global);
        Node = Node->U_1.V_43.Module.Next;
      }
      TreeMThree2_WriteLine(W_14->TreeCodes->U_1.V_12.Codes.LocalLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Local);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.LocalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"VAR yyTypeRange : ARRAY [ 0 .. ", 31L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)"] OF SHORTCARD ;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* Make", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" is deprecated (<*OBSOLETE*>) for Modula-3. *)", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* VISIBLE: *)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Make", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (Kind : SHORTCARD): ", 21L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" RAISES { BadNodeKind }", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE Kind OF ", 15L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_14->Classes, (Tree_ProcOfT)MakeNode);
        IO_WriteS(Tree_f, (STRING)"  ELSE RAISE BadNodeKind ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END (* CASE *) ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Make", 9L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* IsType is deprecated (<*OBSOLETE*>) for Modula-3. *)", 55L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* VISIBLE: *)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE IsType (Tree: ", 24L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; Kind : SHORTCARD): BOOLEAN RAISES { BadNodeKind }", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF Tree = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  THEN RETURN FALSE ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ELSE ", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE Kind OF ", 16L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_14->Classes, (Tree_ProcOfT)IsTypeCases);
        IO_WriteS(Tree_f, (STRING)"   ELSE RAISE BadNodeKind ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END (* CASE *) ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END (* IF *) ", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END IsType;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Uninitialized node construtors: *)", 37L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_14->Classes, (Tree_ProcOfT)ProcedureBodyn);
      }
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Node constructors with initialization of input children and attributes: *)", 77L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_14->Classes, (Tree_ProcOfT)ProcedureBodym);
      }
      TreeMThree2_TreeIO(t);
      GenGnat_GnatModule(t);
      if (Sets_IsElement(ORD('t'), &Tree_Options) || Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"VAR yyProc     : tProcTree;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Top down traverser: *)", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* VISIBLE: *)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Traverse", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD ( Tree : ", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; Proc : tProcTree )", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =PROCEDURE Recurse (yyt: ", 26L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  = VAR LTree := yyt ; ", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; BEGIN", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     LOOP", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      IF (LTree = ", 18L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") OR (LTree.yyHead.yyMark = 0) THEN RETURN; END;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      LTree . yyHead . yyMark := 0;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Proc ( LTree ) ;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      TYPECASE LTree OF", 23L);
        IO_WriteNl(Tree_f);
        TraverseTD(W_14->Classes);
        IO_WriteS(Tree_f, (STRING)"      ELSE RETURN;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END;", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     END;", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END Recurse ; ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN (* Traverse", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD *) ", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyMark (Tree);", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Recurse (Tree);", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Traverse", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD;", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* Bottom up traverser: *)", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"(* VISIBLE: *)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Traverse", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU ( Tree : ", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; Proc : tProcTree )", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =PROCEDURE Recurse ( yyt : ", 28L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  = VAR LTree := yyt ; ", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; BEGIN", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      IF ( LTree = ", 19L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" ) OR ( LTree . yyHead . yyMark = 0) THEN RETURN; END;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      LTree . yyHead . yyMark := 0;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      TYPECASE LTree OF", 23L);
        IO_WriteNl(Tree_f);
        TraverseBU(W_14->Classes);
        IO_WriteS(Tree_f, (STRING)"      ELSE", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END;", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Proc ( LTree ) ;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Recurse ;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN (* Traverse", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU *) ", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyMark ( Tree );", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Recurse ( Tree );", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Traverse", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU;", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"(* VISIBLE: *)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Reverse", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( Tree : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) : ", 5L);
        Tree_WI(Tree_itTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yyOld, yyNew, yyNext, yyTail     : ", 40L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyOld        := Tree ; ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyNew        := yyOld;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyTail       := yyOld;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   TYPECASE yyOld OF", 20L);
        IO_WriteNl(Tree_f);
        Reverse1(W_14->Classes);
        IO_WriteS(Tree_f, (STRING)"   ELSE EXIT;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyNew       := yyOld;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyOld       := yyNext;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END (* LOOP *) ;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  TYPECASE yyTail OF", 20L);
        IO_WriteNl(Tree_f);
        Reverse2(W_14->Classes);
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
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Copy", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (Tree: ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yyWr : FileWr . T ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyWrPipe , yyRdPipe : Pipe . T ;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" TYPE yytClosure  = Thread . Closure ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"         OBJECT", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"           yyRd : FileRd.T ", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"           yyNew : ", 19L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"         OVERRIDES apply := yyCopyRead ", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"         END ;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyClosure : yytClosure ; ", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyThread : Thread . T ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" PROCEDURE yyCopyRead ( Self : yytClosure ) = ", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   BEGIN ", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     Self . yyNew := NARROW ( Pickle . Read ( Self . yyRd ) , ", 62L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END yyCopyRead ; ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Pipe . Open ( yyRdPipe , yyWrPipe ) ; ", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyWr . init ( yyWrPipe ) ; ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyClosure := NEW ( yytClosure ) ; ", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyClosure . yyRd . init ( yyRdPipe ) ; ", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyThread := Thread . Fork ( yyClosure ) ; ", 44L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Pickle . Write ( Tree , yyWr ) ; ", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Thread . Join ( yyThread ) ; ", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyClosure . yyNew ; ", 29L);
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
        IO_WriteS(Tree_f, (STRING)" (Tree: ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (Tree);", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyCheck", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (Tree);", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Check", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyCheckMessage (yyParent, yyChild: ", 45L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yySelector: TEXT) ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yyf     := Stdio . stderr ;", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( yyf , \"CheckTree: parent = \" ) ;", 50L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Write", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (yyf, yyParent);", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText  ( yyf , Wr . EOL ) ;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText  ( yyf , \"selector: \" ) ;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText  ( yyf , yySelector ) ;", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText  ( yyf , \", child = \");", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Write", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (yyf, yyChild);", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText  (yyf, Wr . EOL ) ;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyCheckMessage;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyCheck", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yyResult  : BOOLEAN;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN RETURN FALSE;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ELSIF yyt.yyHead.yyMark = 0 THEN RETURN TRUE;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt.yyHead.yyMark := 0;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyResult := TRUE;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  TYPECASE yyt OF", 17L);
        IO_WriteNl(Tree_f);
        CheckAttributes(W_14->Classes);
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
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"CONST yyQueryStateWrite = 1 ; yyQueryStateRead = 2 ; yyQueryStateQuit = 3 ;", 75L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyQueryState    : INTEGER;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Query", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (Tree: ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR LCommand : TEXT ;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyQueryState := yyQueryStateWrite;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyQueryState OF", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyQueryStateQuit => RETURN ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyQueryStateWrite => Write", 31L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node ( Stdio . stdout , Tree); yyQueryState := yyQueryStateRead;", 64L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyQueryStateRead   => Wr . PutText ( Stdio . stdout , \"? \" ) ;", 67L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      LCommand := Lex . Scan ( Stdio . Stdin , Lex . NonBlanks ) ;", 66L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      IF    Text . Equal ( LCommand , \"parent\" ) THEN yyQueryState := yyQueryStateWrite; RETURN;", 96L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ELSIF Text . Equal ( LCommand , \"quit\" ) THEN yyQueryState := yyQueryStateQuit ; RETURN;", 94L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ELSIF Tree # ", 19L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"       TYPECASE Tree OF", 23L);
        IO_WriteNl(Tree_f);
        QueryAttributes(W_14->Classes);
        IO_WriteS(Tree_f, (STRING)"       ELSE", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"       END;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END;", 10L);
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
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIsEqual (yya, yyb: ARRAY OF CHAR ): BOOLEAN", 55L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO NUMBER ( yya ) DO", 35L);
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
        IO_WriteS(Tree_f, (STRING)" (Tree1, Tree2: ", 16L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): BOOLEAN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF Tree1 = Tree2 THEN RETURN TRUE; END;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF (Tree1 = ", 14L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") OR (Tree2 = ", 14L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") ", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     OR ( TYPECODE ( Tree1 ) # TYPECODE ( Tree2 ) THEN RETURN FALSE; END;", 73L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  TYPECASE Tree1 OF", 19L);
        IO_WriteNl(Tree_f);
        IsEqualAttributes(W_14->Classes);
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
        Tree_ForallClasses(W_14->Classes, (Tree_ProcOfT)CompMaxBit);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Init", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (Tree: ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Tree . yyHead . yyIsComp := {} ; ", 36L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('5'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"   Tree . yyHead . yyIsDone := {} ; ", 36L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"   TYPECASE Tree OF", 19L);
        IO_WriteNl(Tree_f);
        InitAttributes(W_14->Classes);
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
      IO_WriteS(Tree_f, (STRING)" ( )", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(W_14->TreeCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Begin);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.BeginLine);
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
      IO_WriteS(Tree_f, (STRING)" ( ) ", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(W_14->TreeCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Close);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)" END Close", 10L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE xxExit ( ) ", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Process.Exit (1);", 19L);
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
        IO_WriteS(Tree_f, (STRING)" yyExit        := xxExit;", 25L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_14->Classes, (Tree_ProcOfT)InitTypeRange);
      }
      if (Sets_IsElement(ORD(';'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" yyRecursionLevel := 0;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyTreeStorePtr := NEW ( REF yytTreeStore , yyInitTreeStoreSize ) ;", 67L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)" Begin", 6L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      TreeMThree2_TreeIOInit(t);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" .", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void MakeNode
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
      register Tree_yClass *W_15 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_15->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"  | Nk", 6L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)" => RETURN n", 12L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)" ( ) ; ", 7L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void IsTypeCases
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
    {
      register Tree_yClass *W_16 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_16->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"   | Nk", 7L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)" => RETURN ISTYPE ( Tree , ", 27L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
        IO_WriteNl(Tree_f);
      }
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
  struct S_15 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_17 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_17->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"(* VISIBLE: *)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE n", 11L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)" ( ) : ", 7L);
        Tree_WI(W_17->Name);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yyt : ", 11L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt := NEW ( ", 15L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt . Kind := Nk", 18L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        iClassName = W_17->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodyn);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyt;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END n", 6L);
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

      IO_WriteS(Tree_f, (STRING)"  begin", 7L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" ( yyt . ", 9L);
      Tree_WI(W_18->Name);
      IO_WriteS(Tree_f, (STRING)" )", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_19 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_19->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"  begin", 7L);
        Tree_WI(W_19->Type);
        IO_WriteS(Tree_f, (STRING)" ( yyt . ", 9L);
        Tree_WI(W_19->Name);
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
  struct S_16 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_20 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_20->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"(* VISIBLE: *)", 14L);
        IO_WriteNl(Tree_f);
        ProcedureHeadingm(t);
        IO_WriteS(Tree_f, (STRING)" VAR yyt    : ", 14L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt := NEW ( ", 15L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt . Kind := Nk", 18L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_20->Properties) != 0X0L) {
          iClassName = W_20->Name;
          Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodym);
        }
        IO_WriteS(Tree_f, (STRING)"  RETURN yyt;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END m", 6L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_21 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_21->Properties)) {
        IO_WriteS(Tree_f, (STRING)"  yyt . ", 8L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)" := p", 5L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"  begin", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ( yyt . ", 9L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_22 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_22->Properties) == 0X0L) {
        if (IN(Tree_Input, W_22->Properties)) {
          IO_WriteS(Tree_f, (STRING)"  yyt . ", 8L);
          Tree_WI(W_22->Name);
          IO_WriteS(Tree_f, (STRING)" := p", 5L);
          Tree_WI(W_22->Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"  begin", 7L);
          Tree_WI(W_22->Type);
          IO_WriteS(Tree_f, (STRING)" ( yyt . ", 9L);
          Tree_WI(W_22->Name);
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

static void TraverseTD
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
      register Tree_yClass *W_23 = &t->U_1.V_5.Class;

      TraverseTD(W_23->Extensions);
      if ((Tree_NoCodeClass & W_23->Properties) == 0X0L && IN(Tree_HasChildren, W_23->Properties)) {
        IO_WriteS(Tree_f, (STRING)"      | ", 8L);
        Tree_WI(W_23->Name);
        IO_WriteS(Tree_f, (STRING)" ( Node ) => ", 13L);
        IO_WriteNl(Tree_f);
        TreeMThree2_GetIterator(t);
        iClassName = W_23->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseTD);
        if (TreeMThree2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"      RETURN;", 13L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"      LTree := Node . ", 22L);
          Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ;", 2L);
          IO_WriteNl(Tree_f);
        }
      }
      TraverseTD(W_23->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_24 = &t->U_1.V_9.Child;

      if (t != TreeMThree2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"      Recurse ( Node . ", 23L);
        Tree_WI(W_24->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
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
  struct S_18 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_25 = &t->U_1.V_5.Class;

      TraverseBU(W_25->Extensions);
      if ((Tree_NoCodeClass & W_25->Properties) == 0X0L && IN(Tree_HasChildren, W_25->Properties)) {
        IO_WriteS(Tree_f, (STRING)"      | ", 8L);
        Tree_WI(W_25->Name);
        IO_WriteS(Tree_f, (STRING)" ( Node ) => ", 13L);
        IO_WriteNl(Tree_f);
        TreeMThree2_GetIterator(t);
        iClassName = W_25->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseBU);
        if (TreeMThree2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"      RETURN;", 13L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"      Recurse  ( Node . ", 24L);
          Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
          IO_WriteNl(Tree_f);
        }
      }
      TraverseBU(W_25->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_26 = &t->U_1.V_9.Child;

      if (t != TreeMThree2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"      Recurse ( Node . ", 23L);
        Tree_WI(W_26->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
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
  struct S_19 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_27 = &t->U_1.V_5.Class;

      Reverse1(W_27->Extensions);
      if ((Tree_NoCodeClass & W_27->Properties) == 0X0L) {
        iClassName = W_27->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse1);
      }
      Reverse1(W_27->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_28 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_28->Properties)) {
        IO_WriteS(Tree_f, (STRING)"   | ", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" ( yyNode ) => yyNext := yyNode . ", 34L);
        Tree_WI(W_28->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyNode  ", 9L);
        Tree_WI(W_28->Name);
        IO_WriteS(Tree_f, (STRING)" := NARROW ( yyNew , ", 21L);
        Tree_WI(W_28->Class->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
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
  struct S_20 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_29 = &t->U_1.V_5.Class;

      Reverse2(W_29->Extensions);
      if ((Tree_NoCodeClass & W_29->Properties) == 0X0L) {
        iClassName = W_29->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse2);
      }
      Reverse2(W_29->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_30 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_30->Properties)) {
        IO_WriteS(Tree_f, (STRING)"   | ", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" ( yyNode ) => yyNode . ", 24L);
        Tree_WI(W_30->Name);
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
      register Tree_yClass *W_31 = &t->U_1.V_5.Class;

      CheckAttributes(W_31->Extensions);
      if ((Tree_NoCodeClass & W_31->Properties) == 0X0L && IN(Tree_HasChildren, W_31->Properties)) {
        IO_WriteS(Tree_f, (STRING)"   | ", 5L);
        Tree_WI(W_31->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) => ", 14L);
        IO_WriteNl(Tree_f);
        iClassName = W_31->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)CheckAttributes);
      }
      CheckAttributes(W_31->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_32 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"       IF TNode . ", 18L);
      Tree_WI(W_32->Name);
      IO_WriteS(Tree_f, (STRING)" = NIL", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"       OR NOT ISTYPE ( TNode . ", 31L);
      Tree_WI(W_32->Name);
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
      TreeMThree1_NodeType(W_32->Class);
      IO_WriteS(Tree_f, (STRING)" )", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"       THEN yyCheckMessage ( yyt , TNode . ", 43L);
      Tree_WI(W_32->Name);
      IO_WriteS(Tree_f, (STRING)" , \"", 4L);
      Tree_WI(W_32->Name);
      IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"            yyResult := FALSE ; ", 32L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"       END (* IF *) ; ", 22L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"       yyResult := yyCheck", 26L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
      Tree_WI(W_32->Name);
      IO_WriteS(Tree_f, (STRING)" ) AND yyResult ;", 17L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_33 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Link, W_33->Properties)) {
        IO_WriteS(Tree_f, (STRING)"       IF TNode . ", 18L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)" = NIL", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"       OR NOT ISTYPE ( TNode . ", 31L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)" , ", 3L);
        Tree_WI(W_33->Type);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"       THEN yyCheckMessage ( yyt , TNode . ", 43L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)" , \"", 4L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"            yyResult := FALSE ; ", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"       END (* IF *) ; ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"       yyResult := yyCheck", 26L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)" ) AND yyResult ;", 17L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
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
      register Tree_yClass *W_34 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_34->Properties) == 0X0L) {
        iRange = W_34->Name;
        Tree_ForallClasses(W_34->Extensions, (Tree_ProcOfT)InitTypeRange2);
        IO_WriteS(Tree_f, (STRING)" yyTypeRange [ Nk", 17L);
        Tree_WI(W_34->Name);
        IO_WriteS(Tree_f, (STRING)" ] := Nk", 8L);
        Tree_WI(iRange);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
      register Tree_yClass *W_35 = &t->U_1.V_5.Class;

      iRange = W_35->Name;
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
      register Tree_yClass *W_36 = &t->U_1.V_5.Class;

      QueryAttributes(W_36->Extensions);
      if ((Tree_NoCodeClass & W_36->Properties) == 0X0L && IN(Tree_HasChildren, W_36->Properties)) {
        IO_WriteS(Tree_f, (STRING)"       | ", 9L);
        Tree_WI(W_36->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) =>  IF FALSE THEN", 28L);
        IO_WriteNl(Tree_f);
        iClassName = W_36->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)QueryAttributes);
        IO_WriteS(Tree_f, (STRING)"           END;", 15L);
        IO_WriteNl(Tree_f);
      }
      QueryAttributes(W_36->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_37 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"           ELSIF Text . Equal ( LCommand , \"", 44L);
      Tree_WI(W_37->Name);
      IO_WriteS(Tree_f, (STRING)"\" ) THEN Query", 14L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
      Tree_WI(W_37->Name);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_38 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Link, W_38->Properties)) {
        IO_WriteS(Tree_f, (STRING)"           ELSIF Text . Equal ( LCommand , \"", 44L);
        Tree_WI(W_38->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) THEN Query", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
        Tree_WI(W_38->Name);
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
      register Tree_yClass *W_39 = &t->U_1.V_5.Class;

      IsEqualAttributes(W_39->Extensions);
      if ((Tree_NoCodeClass & W_39->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_39->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"   | ", 5L);
        Tree_WI(W_39->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) => RETURN TRUE", 25L);
        IO_WriteNl(Tree_f);
        iClassName = W_39->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)IsEqualAttributes);
      }
      IsEqualAttributes(W_39->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_40 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"AND equal", 9L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
      Tree_WI(W_40->Name);
      IO_WriteS(Tree_f, (STRING)"    , NARROW ( Tree2 , ", 23L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" ) . ", 5L);
      Tree_WI(W_40->Name);
      IO_WriteS(Tree_f, (STRING)" )", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_41 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_41->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"AND ( equal", 11L);
        Tree_WI(W_41->Type);
        IO_WriteS(Tree_f, (STRING)" (TNode . ", 10L);
        Tree_WI(W_41->Name);
        IO_WriteS(Tree_f, (STRING)"      , NARROW ( Tree2 , ", 25L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" ) . ", 5L);
        Tree_WI(W_41->Name);
        IO_WriteS(Tree_f, (STRING)" ) )", 4L);
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
        register Tree_yClass *W_42 = &t->U_1.V_5.Class;

        InitAttributes(W_42->Extensions);
        if (!((Tree_NoCodeClass & W_42->Properties) == 0X0L && IN(Tree_HasChildren, W_42->Properties))) {
          goto EXIT_1;
        }
        IO_WriteS(Tree_f, (STRING)"  | ", 4L);
        Tree_WI(W_42->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) => ", 14L);
        IO_WriteNl(Tree_f);
        TreeMThree2_GetIterator(t);
        iClassName = W_42->Name;
        gBitCount = W_42->BitCount;
        Tree_ForallAttributes(t, (Tree_ProcOfT)InitAttributes);
        if (TreeMThree2_Iterator == Tree_NoTree || !IN(Tree_Input, TreeMThree2_Iterator->U_1.V_9.Child.Properties)) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"Tree := TNode . ", 16L);
          Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ;", 2L);
          IO_WriteNl(Tree_f);
        }
        InitAttributes(W_42->Extensions);
        return;
      }
    } EXIT_1:;
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_43 = &t->U_1.V_9.Child;

        if (!IN(Tree_Input, W_43->Properties)) {
          goto EXIT_2;
        }
        IO_WriteS(Tree_f, (STRING)"WITH WChildHead = TNode . ", 26L);
        Tree_WI(W_43->Name);
        IO_WriteS(Tree_f, (STRING)" . yyHead DO ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     WChildHead . yyOffset := ", 30L);
        Tree_WN((LONGINT)(gBitCount + W_43->BitOffset));
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     WChildHead . yyParent := Tree ; END;", 41L);
        IO_WriteNl(Tree_f);
        if (!(t != TreeMThree2_Iterator)) {
          goto EXIT_2;
        }
        IO_WriteS(Tree_f, (STRING)"Init", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
        Tree_WI(W_43->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_2:;
    break;
  default :
    break;
  }
}

void TreeMThree1_ImportList
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
  case Tree_Ag:;
    {
      register Tree_yAg *W_44 = &t->U_1.V_26.Ag;

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
      Tree_ForallClassesExtensionsFirst(W_44->Classes, (Tree_ProcOfT)TreeMThree1_ImportList);
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
      if (Sets_IsElement(ORD('^'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Write", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Html,", 5L);
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
      register Tree_yClass *W_45 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_45->Properties) == 0X0L) {
        Tree_WI(W_45->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        IO_WriteS(Tree_f, (STRING)"Nk", 2L);
        Tree_WI(W_45->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        if (Sets_IsElement(ORD('n'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"n", 1L);
          Tree_WI(W_45->Name);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        if (Sets_IsElement(ORD('m'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"m", 1L);
          Tree_WI(W_45->Name);
          IO_WriteS(Tree_f, (STRING)",", 1L);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD('+'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"Nk", 2L);
          Tree_WI(W_45->Name);
          IO_WriteS(Tree_f, (STRING)"Max,", 4L);
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
  struct S_28 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_46 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_46->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)",", 1L);
        IO_WriteNl(Tree_f);
        Tree_WI(W_46->Name);
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
  struct S_29 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_47 = &t->U_1.V_5.Class;

      i = 1;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CompMaxBit);
      MaxBit = General_Max((LONGINT)i, (LONGINT)MaxBit);
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_48 = &t->U_1.V_9.Child;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_48->Properties) == 0X0L)) {
          goto EXIT_3;
        }
        INC(i);
        return;
      }
    } EXIT_3:;
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_49 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_49->Properties) == 0X0L)) {
          goto EXIT_4;
        }
        INC(i);
        return;
      }
    } EXIT_4:;
    break;
  default :
    break;
  }
}

void TreeMThree1_BeginTreeMThree1
# ifdef __STDC__
()
# else
()
# endif
{
  ConstCount = 0;
}

void TreeMThree1_CloseTreeMThree1
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

void TreeMThree1__init()
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
    TreeMThree2__init();
    TreeMThree2__init();
    GenGnat__init();
    IOUtils__init();
    Tree__init();
    Strings__init();

    TreeMThree1_yyf = IO_StdOutput;
    TreeMThree1_Exit = yyExit;
    TreeMThree1_BeginTreeMThree1();
  }
}
