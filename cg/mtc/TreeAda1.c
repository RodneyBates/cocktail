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

#ifndef DEFINITION_Positions
#include "Positions.h"
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

#ifndef DEFINITION_TreeAda2
#include "TreeAda2.h"
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

#ifndef DEFINITION_TreeAda1
#include "TreeAda1.h"
#endif

IO_tFile TreeAda1_yyf;
PROC TreeAda1_Exit;

static INTEGER ConstCount, ListCount;
static Idents_tIdent iRange, iClassName;
static Tree_tTree Node;
static SHORTCARD gBitCount;
static SHORTCARD i, MaxBit;
static void WriteLine ARGS((Positions_tPosition Line));
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
static void ProcedureDecln ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureDeclm ARGS((Tree_tTree t));
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
static void ProcedureBodyn ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureBodym ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void ReleaseAttributes1 ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void ReleaseAttributes2 ARGS((Tree_tTree t));
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
static void Copy ARGS((Tree_tTree t));
struct S_21 {
    union {
        char dummy;
    } U_1;
};
static void CheckAttributes ARGS((Tree_tTree t));
struct S_22 {
    union {
        char dummy;
    } U_1;
};
static void InitTypeRange ARGS((Tree_tTree t));
struct S_23 {
    union {
        char dummy;
    } U_1;
};
static void InitTypeRange2 ARGS((Tree_tTree t));
struct S_24 {
    union {
        char dummy;
    } U_1;
};
static void QueryAttributes ARGS((Tree_tTree t));
struct S_25 {
    union {
        char dummy;
    } U_1;
};
static void IsEqualAttributes ARGS((Tree_tTree t));
struct S_26 {
    union {
        char dummy;
    } U_1;
};
static void InitAttributes ARGS((Tree_tTree t));
struct S_27 {
    union {
        char dummy;
    } U_1;
};
static void InitNodeSize ARGS((Tree_tTree t));
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


static void WriteLine
# ifdef __STDC__
(Positions_tPosition Line)
# else
(Line)
Positions_tPosition Line;
# endif
{
  if (Line.Line != 0) {
    IO_WriteS(Tree_f, (STRING)"-- Copied from line ", 20L);
    Tree_WN((LONGINT)Line.Line);
    IO_WriteS(Tree_f, (STRING)" of file \"", 10L);
    Tree_WI(Line.File);
    IO_WriteS(Tree_f, (STRING)"\" ", 2L);
    IO_WriteNl(Tree_f);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeAda1, routine ", 32L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeAda1_Exit)();
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

void TreeAda1_TreePackSpec
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

      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"-- This Ada PACKAGE spec file was mechanically generated by cg. ", 64L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"WITH ", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ; USE ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"WITH Text_IO ; ", 15L);
      }
      WriteLine(W_1->TreeCodes->U_1.V_12.Codes.SpecWithLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.SpecWith);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.SpecWithLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.SpecWith);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"PACKAGE ", 8L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" IS ", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Import);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ImportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Import);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"KindNull : CONSTANT := ", 23L);
        Tree_WN(ConstCount);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesPreAndPost(W_1->Classes, (Tree_ProcOfT)ConstDeclsPre, (Tree_ProcOfT)ConstDeclsPost);
        IO_WriteNl(Tree_f);
        if (FALSE || Sets_IsElement(ORD('^'), &Tree_Options)) {
          Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)PointerTypes);
        }
        IO_WriteS(Tree_f, (STRING)"KindLast : CONSTANT := ", 23L);
        Tree_WN(ConstCount + 1);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
      }
      WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ExportLine);
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
        IO_WriteS(Tree_f, (STRING)"SUBTYPE KindTyp IS INTEGER RANGE KindNull .. KindLast ; ", 56L);
        IO_WriteS(Tree_f, (STRING)"TYPE yyNode ( Kind : KindTyp := KindNull ) ; ", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE ", 5L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" IS ACCESS yyNode ; ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"SUBTYPE SHORTCARD IS INTEGER RANGE 0 .. 32767 ; ", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE BITSET IS ARRAY ( 0 .. 31 ) OF BOOLEAN ; ", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"BitSetEmpty : CONSTANT BITSET := ( OTHERS => FALSE ) ; ", 55L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('L'), &Tree_Options)) {
          MaxBit = 0;
          Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)CompMaxBit);
          IO_WriteS(Tree_f, (STRING)"TYPE yytNodeHead IS RECORD ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyMark , yyOffset : SHORTCARD ; ", 34L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyParent : ", 13L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ; ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyIsComp0", 11L);
          if (Sets_IsElement(ORD('5'), &Tree_Options)) {
            IO_WriteS(Tree_f, (STRING)" , yyIsDone0", 12L);
          }
          {
            SHORTCARD B_3 = 1, B_4 = (MaxBit - 1) / TreeAda1_BSS;

            if (B_3 <= B_4)
              for (i = B_3;; i += 1) {
                IO_WriteS(Tree_f, (STRING)" , yyIsComp", 11L);
                Tree_WN((LONGINT)i);
                if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                  IO_WriteS(Tree_f, (STRING)" , yyIsDone", 11L);
                  Tree_WN((LONGINT)i);
                }
                if (i >= B_4) break;
              }
          }
          IO_WriteS(Tree_f, (STRING)" : BITSET ; yyNodeHead ", 23L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"END RECORD ; ", 13L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"TYPE yytNodeHead IS RECORD ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyMark : SHORTCARD ; yyNodeHead ", 34L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"END RECORD ; ", 13L);
          IO_WriteNl(Tree_f);
        }
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)TypeDeclNode);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE yyNode ( Kind : KindTyp := KindNull ) IS RECORD ", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyHead : yytNodeHead ; ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE Kind IS ", 15L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)TypeDeclRecord);
        IO_WriteS(Tree_f, (STRING)"  WHEN OTHERS => NULL ; ", 24L);
        IO_WriteS(Tree_f, (STRING)"  END CASE ; ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"END RECORD ; ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" : CONSTANT ", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" := NULL ; ", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"Root : ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"FUNCTION Make", 13L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ( Kind : KindTyp ) RETURN ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"FUNCTION IsType ( Tree : ", 25L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; Kind : KindTyp ) RETURN BOOLEAN ; ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ProcedureDecln);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ProcedureDeclm);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('f'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-f option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('F'), &Tree_Options) && !Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-F option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ( Tree : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-w option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('^'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"-- Html graph writer:", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Html ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( f : Text_Io . File_Type ; Tree : ", 37L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; Title : STRING := \"\" ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; SuppressNullFields : BOOLEAN := FALSE ) ; ", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-r option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-p option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-g option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-t option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-b option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-R option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-y option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('k'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"FUNCTION Check", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( Tree : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) RETURN BOOLEAN ; ", 20L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-q option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('='), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"-= option not implemented for Ada", 33L);
        IO_WriteNl((System_tFile)IO_StdError);
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Init", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( Tree : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
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
          IO_WriteS(Tree_f, (STRING)" : CONSTANT := ", 15L);
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
            IO_WriteS(Tree_f, (STRING)"Max : CONSTANT := ", 18L);
            Tree_WN(ConstCount);
            IO_WriteS(Tree_f, (STRING)" ; ", 3L);
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
          IO_WriteS(Tree_f, (STRING)"SUBTYPE p", 9L);
          Tree_WI(W_4->Name);
          IO_WriteS(Tree_f, (STRING)" IS ", 4L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ; ", 3L);
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
        IO_WriteS(Tree_f, (STRING)"TYPE y", 6L);
        Tree_WI(W_5->Name);
        IO_WriteS(Tree_f, (STRING)" IS RECORD ", 11L);
        IO_WriteNl(Tree_f);
        Tree_ForallAttributes(t, (Tree_ProcOfT)TypeDeclNode);
        IO_WriteS(Tree_f, (STRING)"  END RECORD ; ", 15L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_6 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      Tree_WI(W_6->Name);
      IO_WriteS(Tree_f, (STRING)" : ", 3L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_7 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_7->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_7->Name);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Tree_WI(W_7->Type);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
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
        IO_WriteS(Tree_f, (STRING)"  WHEN ", 7L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)" : y", 4L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ProcedureDecln
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
        IO_WriteS(Tree_f, (STRING)"FUNCTION n", 10L);
        Tree_WI(W_9->Name);
        IO_WriteS(Tree_f, (STRING)" RETURN ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ProcedureDeclm
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

      ProcedureHeadingm(t);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
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
        IO_WriteS(Tree_f, (STRING)"FUNCTION m", 10L);
        Tree_WI(W_11->Name);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( ", 4L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureHeadingm);
        IO_WriteS(Tree_f, (STRING)") RETURN ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"", 1L);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_12 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_12->Properties)) {
        if (ListCount > 0) {
          IO_WriteS(Tree_f, (STRING)"; ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"  p", 3L);
        Tree_WI(W_12->Name);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" := NULL ", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
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
          IO_WriteS(Tree_f, (STRING)"; ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"  p", 3L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Tree_WI(W_13->Type);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
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

void TreeAda1_TreePackBody
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

      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"-- This Ada PACKAGE BODY file was mechanically generated by cg. ", 64L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('k'), &Tree_Options) || Sets_IsElement(ORD('q'), &Tree_Options) || Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"WITH Text_Io ; ", 15L);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"WITH Unchecked_Conversion ; ", 28L);
      }
      if (Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"WITH ", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ; USE ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      WriteLine(W_14->TreeCodes->U_1.V_12.Codes.BodyWithLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.BodyWith);
      IO_WriteS(Tree_f, (STRING)"PACKAGE BODY ", 13L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" IS ", 4L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('<'), &Tree_Options)) {
      }
      WriteLine(W_14->TreeCodes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Global);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.GlobalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Global);
        Node = Node->U_1.V_43.Module.Next;
      }
      WriteLine(W_14->TreeCodes->U_1.V_12.Codes.LocalLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Local);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.LocalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"yyTypeRange : ARRAY ( 0..", 25L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)") OF SHORTCARD;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"FUNCTION  Make", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ( Kind : KindTyp ) RETURN ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt := NEW yyNode ( Kind ) ; ", 33L);
        IO_WriteS(Tree_f, (STRING)"    yyt . ALL . yyHead . yyMark := 0 ; ", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN yyt; ", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Make", 9L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"FUNCTION IsType ( Tree : ", 25L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; Kind : KindTyp ) RETURN  BOOLEAN ", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN Tree /= ", 19L);
        Tree_WI(Tree_iNoTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      AND Kind <= Tree . ALL . Kind ", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      AND Tree . ALL . Kind <= yyTypeRange ( Kind ) ; ", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END IsType ; ", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tree_ForallClasses(W_14->Classes, (Tree_ProcOfT)ProcedureBodyn);
      }
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        Tree_ForallClasses(W_14->Classes, (Tree_ProcOfT)ProcedureBodym);
      }
      TreeAda2_TreeIO(t);
      if (Sets_IsElement(ORD('f'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('F'), &Tree_Options) && !Sets_IsElement(ORD('<'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options) || Sets_IsElement(ORD('b'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('k'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"FUNCTION yyCheckChild ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( yyParent , yyChild : ", 25L);
        Tree_WI(Tree_itTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; yyType : KindTyp ; yySelector: STRING ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ) ", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"RETURN BOOLEAN ; ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"FUNCTION yyCheck", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) RETURN BOOLEAN ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
        IO_WriteS(Tree_f, (STRING)"    yyResult : BOOLEAN ; ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF yyt = ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN RETURN FALSE ; ", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSIF yyt . ALL . yyHead . yyMark = 0 THEN RETURN TRUE ; ", 61L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END IF ; ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt . ALL . yyHead . yyMark := 0;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyResult := TRUE;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    CASE yyt . ALL . Kind IS ", 29L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_14->Classes, (Tree_ProcOfT)CheckAttributes);
        IO_WriteS(Tree_f, (STRING)"    WHEN OTHERS => NULL ; ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END CASE ; ", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN yyResult ; ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END yyCheck", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"FUNCTION yyCheckChild ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( yyParent , yyChild : ", 25L);
        Tree_WI(Tree_itTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; yyType : KindTyp ; yySelector: STRING ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ) ", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"RETURN BOOLEAN ", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
        IO_WriteS(Tree_f, (STRING)"    yySuccess : BOOLEAN ; ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yySuccess := IsType ( yyChild , yyType ) ; ", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF NOT yySuccess THEN", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Text_Io . Put ( \"CheckTree: parent = \" ) ; ", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Write", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node ( yyParent ) ; ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Text_Io . Put_Line ( \"\" ) ; ", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Text_Io . Put ( \"selector: \" ) ; ", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Text_Io . Put ( yySelector ) ; ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Text_Io . Put ( \", child = \" ) ; ", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Write", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node ( yyChild ) ; ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Text_Io . Put_Line ( \"\" ) ; ", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END IF ; ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyCheck", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( yyChild ) AND yySuccess ; ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyCheckChild ; ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"FUNCTION Check", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( Tree : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) RETURN BOOLEAN ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyMark ( Tree ) ; ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN yyCheck", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( Tree ) ; ", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Check", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('='), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        MaxBit = 0;
        Tree_ForallClasses(W_14->Classes, (Tree_ProcOfT)CompMaxBit);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Init", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS BEGIN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        {
          SHORTCARD B_5 = 0, B_6 = (MaxBit - 1) / TreeAda1_BSS;

          if (B_5 <= B_6)
            for (i = B_5;; i += 1) {
              IO_WriteS(Tree_f, (STRING)"     yyt . ALL . yyIsComp", 25L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)" := BitsetEmpty ; ", 18L);
              IO_WriteNl(Tree_f);
              if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"     yyt . ALL . yyIsDone", 25L);
                Tree_WN((LONGINT)i);
                IO_WriteS(Tree_f, (STRING)" := BitsetEmpty ;", 17L);
                IO_WriteNl(Tree_f);
              }
              if (i >= B_6) break;
            }
        }
        IO_WriteS(Tree_f, (STRING)"    CASE yyt . ALL . Kind OF", 28L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_14->Classes, (Tree_ProcOfT)InitAttributes);
        IO_WriteS(Tree_f, (STRING)"    ELSE RETURN;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END CASE ; ", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END LOOP ;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Init", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
      IO_WriteNl(Tree_f);
      WriteLine(W_14->TreeCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Begin);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"    NULL ; ", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END Begin", 11L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(Tree_iModule);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
      IO_WriteNl(Tree_f);
      WriteLine(W_14->TreeCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_14->TreeCodes->U_1.V_12.Codes.Close);
      Node = W_14->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"    NULL ; ", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END Close", 11L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
      }
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
      }
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        Tree_ForallClasses(W_14->Classes, (Tree_ProcOfT)InitTypeRange);
      }
      if (Sets_IsElement(ORD(';'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
      }
      IO_WriteS(Tree_f, (STRING)"  Begin", 7L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
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
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_15 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_15->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"FUNCTION n", 10L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)" RETURN ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt := NEW yyNode ( ", 24L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt . ALL . yyHead . yyMark := 0 ; ", 39L);
        IO_WriteNl(Tree_f);
        iClassName = W_15->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodyn);
        IO_WriteS(Tree_f, (STRING)"    RETURN yyt ; ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END n", 6L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_16 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"    begin", 9L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" ( yyt . ALL . ", 15L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_16->Name);
      IO_WriteS(Tree_f, (STRING)" ) ", 3L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_17 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_17->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"    begin", 9L);
        Tree_WI(W_17->Type);
        IO_WriteS(Tree_f, (STRING)" ( yyt . ALL . ", 15L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
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
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_18 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_18->Properties) == 0X0L) {
        ProcedureHeadingm(t);
        IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
        IO_WriteS(Tree_f, (STRING)"    yyt : ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt := NEW yyNode ( ", 24L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt . ALL . yyHead . yyMark := 0 ; ", 39L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_18->Properties) != 0X0L) {
          iClassName = W_18->Name;
          Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodym);
        }
        IO_WriteS(Tree_f, (STRING)"    RETURN yyt ; ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END m", 7L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_19 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_19->Properties)) {
        IO_WriteS(Tree_f, (STRING)"    yyt . ALL . ", 16L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_19->Name);
        IO_WriteS(Tree_f, (STRING)" := p", 5L);
        Tree_WI(W_19->Name);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"    begin", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ( yyt . ALL . ", 15L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_19->Name);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_20 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_20->Properties) == 0X0L) {
        if (IN(Tree_Input, W_20->Properties)) {
          IO_WriteS(Tree_f, (STRING)"    yyt . ALL . ", 16L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(W_20->Name);
          IO_WriteS(Tree_f, (STRING)" := p", 5L);
          Tree_WI(W_20->Name);
          IO_WriteS(Tree_f, (STRING)" ; ", 3L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"    begin", 9L);
          Tree_WI(W_20->Type);
          IO_WriteS(Tree_f, (STRING)" ( yyt . ALL . ", 15L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(W_20->Name);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
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
  struct S_15 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_21 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_21->Properties) == 0X0L && IN(Tree_HasChildren, W_21->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_21->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReleaseAttributes1);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_22 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"close", 5L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" (yyt . ALL . ", 14L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)" ) ", 3L);
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
  struct S_16 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_23 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_23->Properties) == 0X0L && IN(Tree_HasAttributes, W_23->Properties)) {
        IO_WriteS(Tree_f, (STRING)"WHEN ", 5L);
        Tree_WI(W_23->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteNl(Tree_f);
        iClassName = W_23->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReleaseAttributes2);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_24 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_24->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"close", 5L);
        Tree_WI(W_24->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt . ALL . ", 14L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_24->Name);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
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
  struct S_17 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_25 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_25->Properties) == 0X0L && IN(Tree_HasChildren, W_25->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_25->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeAda2_GetIterator(t);
        iClassName = W_25->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseTD);
        if (TreeAda2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt := yyt . ALL . ", 19L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ; ", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_26 = &t->U_1.V_9.Child;

      if (t != TreeAda2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD (yyt . ALL . ", 16L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_26->Name);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
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
      register Tree_yClass *W_27 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_27->Properties) == 0X0L && IN(Tree_HasChildren, W_27->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_27->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeAda2_GetIterator(t);
        iClassName = W_27->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseBU);
        if (TreeAda2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"BU (yyt . ALL . ", 16L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_28 = &t->U_1.V_9.Child;

      if (t != TreeAda2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU (yyt . ALL . ", 16L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_28->Name);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
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
      register Tree_yClass *W_29 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_29->Properties) == 0X0L) {
        iClassName = W_29->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse1);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_30 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_30->Properties)) {
        IO_WriteS(Tree_f, (STRING)"WHEN ", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" => yyNext := yyOld . ALL . ", 28L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_30->Name);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteS(Tree_f, (STRING)" yyOld . ALL . ", 15L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_30->Name);
        IO_WriteS(Tree_f, (STRING)" := yyNew ; ", 12L);
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
      register Tree_yClass *W_31 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_31->Properties) == 0X0L) {
        iClassName = W_31->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse2);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_32 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_32->Properties)) {
        IO_WriteS(Tree_f, (STRING)"WHEN ", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" => yyTail . ALL . ", 19L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_32->Name);
        IO_WriteS(Tree_f, (STRING)" := yyOld ; ", 12L);
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
  struct S_21 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_33 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_33->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"WHEN ", 5L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)" => yyNew^^.", 12L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)" := yyt^.", 9L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        TreeAda2_GetIterator(t);
        iClassName = W_33->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Copy);
        if (TreeAda2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt := yyt^.", 12L);
          Tree_WI(W_33->Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"yyNew := SYSTEM.ADR (yyNew^^.", 29L);
          Tree_WI(W_33->Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_34 = &t->U_1.V_9.Child;

      if (t != TreeAda2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"copy", 4L);
        Tree_WI(Tree_itTree);
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
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_35 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_35->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"copy", 4L);
        Tree_WI(W_35->Type);
        IO_WriteS(Tree_f, (STRING)" (yyNew^^.", 10L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_35->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        IO_WriteS(Tree_f, (STRING)"yyt^.", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_35->Name);
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
  struct S_22 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_36 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_36->Properties) == 0X0L && IN(Tree_HasChildren, W_36->Properties)) {
        IO_WriteS(Tree_f, (STRING)"    WHEN ", 9L);
        Tree_WI(W_36->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteNl(Tree_f);
        iClassName = W_36->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)CheckAttributes);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_37 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"       yyResult := yyResult AND THEN ", 37L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"         yyCheckChild ( yyt , yyt . ALL . ", 42L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_37->Name);
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
      Tree_WI(W_37->Type);
      IO_WriteS(Tree_f, (STRING)" , \"", 4L);
      Tree_WI(W_37->Name);
      IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_38 = &t->U_1.V_10.Attribute;

        if (!IN(Tree_Link, W_38->Properties)) {
          goto EXIT_1;
        }
        IO_WriteS(Tree_f, (STRING)"       yyResult := yyResult AND THEN ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"         yyCheckChild  ( yyt , yyt . ALL . ", 43L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_38->Name);
        IO_WriteS(Tree_f, (STRING)" , ", 3L);
        Tree_WI(W_38->Type);
        IO_WriteS(Tree_f, (STRING)" , \"", 4L);
        Tree_WI(W_38->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
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
  struct S_23 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_39 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_39->Properties) == 0X0L) {
        iRange = W_39->Name;
        Tree_ForallClasses(W_39->Extensions, (Tree_ProcOfT)InitTypeRange2);
        IO_WriteS(Tree_f, (STRING)"  yyTypeRange (", 15L);
        Tree_WI(W_39->Name);
        IO_WriteS(Tree_f, (STRING)") := ", 5L);
        Tree_WI(iRange);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
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
  struct S_24 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_40 = &t->U_1.V_5.Class;

      iRange = W_40->Name;
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
  struct S_25 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_41 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_41->Properties) == 0X0L && IN(Tree_HasChildren, W_41->Properties)) {
        IO_WriteS(Tree_f, (STRING)"WHEN ", 5L);
        Tree_WI(W_41->Name);
        IO_WriteS(Tree_f, (STRING)" => IF FALSE THEN", 17L);
        IO_WriteNl(Tree_f);
        iClassName = W_41->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)QueryAttributes);
        IO_WriteS(Tree_f, (STRING)"END;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_42 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"ELSIF yyyIsEqual ('", 19L);
      Tree_WI(W_42->Name);
      IO_WriteS(Tree_f, (STRING)"') THEN Query", 13L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" (yyt . ALL . ", 14L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_42->Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_43 = &t->U_1.V_10.Attribute;

        if (!IN(Tree_Link, W_43->Properties)) {
          goto EXIT_2;
        }
        IO_WriteS(Tree_f, (STRING)"ELSIF yyyIsEqual ('", 19L);
        Tree_WI(W_43->Name);
        IO_WriteS(Tree_f, (STRING)"') THEN Query", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt . ALL . ", 14L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_43->Name);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
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
  struct S_26 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_44 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_44->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_44->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"WHEN ", 5L);
        Tree_WI(W_44->Name);
        IO_WriteS(Tree_f, (STRING)" => RETURN TRUE ", 16L);
        IO_WriteNl(Tree_f);
        iClassName = W_44->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)IsEqualAttributes);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_45 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"AND equal", 9L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" (yyt1 . ALL . ", 15L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_45->Name);
      IO_WriteS(Tree_f, (STRING)", yyt2 . ALL . ", 15L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_45->Name);
      IO_WriteS(Tree_f, (STRING)" ) ", 3L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_46 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_46->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"AND (equal", 10L);
        Tree_WI(W_46->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt1 . ALL . ", 15L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_46->Name);
        IO_WriteS(Tree_f, (STRING)", yyt2 . ALL . ", 15L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_46->Name);
        IO_WriteS(Tree_f, (STRING)" ) ) ", 5L);
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
  struct S_27 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    for (;;) {
      {
        register Tree_yClass *W_47 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_47->Properties) == 0X0L && IN(Tree_HasChildren, W_47->Properties))) {
          goto EXIT_3;
        }
        IO_WriteS(Tree_f, (STRING)"    WHEN ", 9L);
        Tree_WI(W_47->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteNl(Tree_f);
        TreeAda2_GetIterator(t);
        iClassName = W_47->Name;
        gBitCount = W_47->BitCount;
        Tree_ForallAttributes(t, (Tree_ProcOfT)InitAttributes);
        if (TreeAda2_Iterator == Tree_NoTree || !IN(Tree_Input, TreeAda2_Iterator->U_1.V_9.Child.Properties)) {
          IO_WriteS(Tree_f, (STRING)"       RETURN ; ", 16L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"       yyt := yyt . ALL . ", 26L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ; ", 3L);
          IO_WriteNl(Tree_f);
        }
        return;
      }
    } EXIT_3:;
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_48 = &t->U_1.V_9.Child;

        if (!IN(Tree_Input, W_48->Properties)) {
          goto EXIT_4;
        }
        IO_WriteS(Tree_f, (STRING)"       yyt . ALL . yyHead . yyOffset := ", 40L);
        Tree_WN((LONGINT)(gBitCount + W_48->BitOffset));
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteS(Tree_f, (STRING)"       yyt . ALL . yyHead . yyParent := yyt ; ", 46L);
        if (!(t != TreeAda2_Iterator)) {
          goto EXIT_4;
        }
        IO_WriteS(Tree_f, (STRING)"       Init", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt . ALL . ", 14L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_48->Name);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
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
  struct S_28 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    for (;;) {
      {
        register Tree_yClass *W_49 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_49->Properties) == 0X0L)) {
          goto EXIT_5;
        }
        IO_WriteS(Tree_f, (STRING)" yyNodeSize [", 13L);
        Tree_WI(W_49->Name);
        IO_WriteS(Tree_f, (STRING)"] := SYSTEM.TSIZE (y", 20L);
        Tree_WI(W_49->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_5:;
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
      register Tree_yClass *W_50 = &t->U_1.V_5.Class;

      i = 1;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CompMaxBit);
      MaxBit = General_Max((LONGINT)i, (LONGINT)MaxBit);
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_51 = &t->U_1.V_9.Child;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_51->Properties) == 0X0L)) {
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
        register Tree_yAttribute *W_52 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_52->Properties) == 0X0L)) {
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

void TreeAda1_BeginTreeAda1
# ifdef __STDC__
()
# else
()
# endif
{
  ConstCount = 0;
}

void TreeAda1_CloseTreeAda1
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

void TreeAda1__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Tree__init();
    Positions__init();
    System__init();
    IO__init();
    Tree__init();
    Positions__init();
    General__init();
    IO__init();
    Idents__init();
    Texts__init();
    Sets__init();
    TreeAda2__init();
    IOUtils__init();
    Tree__init();
    Strings__init();

    TreeAda1_yyf = IO_StdOutput;
    TreeAda1_Exit = yyExit;
    TreeAda1_BeginTreeAda1();
  }
}
