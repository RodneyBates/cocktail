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

#ifndef DEFINITION_TreeC2
#include "TreeC2.h"
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

#ifndef DEFINITION_TreeC1
#include "TreeC1.h"
#endif

IO_tFile TreeC1_yyf;
PROC TreeC1_Exit;

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
static void ConstDecls ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void TypeDeclNode ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void TypeDeclRecord ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureDeclsn ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureDeclsm ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureHeadingm ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void ProcedureHeadingm2 ARGS((Tree_tTree t));
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
static void TreeImplC1 ARGS((Tree_tTree t));
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
static void InitNodeName ARGS((Tree_tTree t));
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeC1, routine ", 30L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeC1_Exit)();
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

void TreeC1_TreeDefC
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

      IO_WriteS(Tree_f, (STRING)"# ifndef yy", 11L);
      Tree_WI(Tree_iModule);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yy", 11L);
      Tree_WI(Tree_iModule);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define ARGS(parameters)      parameters", 41L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define ARGS(parameters)      ()", 33L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# include \"", 11L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".h\"", 3L);
        IO_WriteNl(Tree_f);
      }
      TreeC2_WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Import);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ImportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Import);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef bool", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define bool char", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# define ", 9L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)") 0L", 4L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ConstDecls);
        IO_WriteNl(Tree_f);
        if (Tree_ClassCount > 251) {
          IO_WriteS(Tree_f, (STRING)"typedef unsigned short ", 23L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tKind;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"typedef unsigned char ", 22L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tKind;", 7L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"typedef unsigned short ", 23L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tMark;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"typedef unsigned short ", 23L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tLabel;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"typedef union ", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Node * ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"typedef void (* ", 16L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree) ARGS((", 18L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"));", 3L);
        IO_WriteNl(Tree_f);
      }
      TreeC2_WriteLine(W_1->TreeCodes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_1->TreeCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.ExportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Export);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# ifndef ", 9L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeHead", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# define ", 9L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeHead", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('L'), &Tree_Options)) {
          MaxBit = 0;
          Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)CompMaxBit);
          IO_WriteS(Tree_f, (STRING)"typedef struct { ", 17L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tKind yyKind; unsigned char yyIsComp0", 38L);
          if (Sets_IsElement(ORD('5'), &Tree_Options)) {
            IO_WriteS(Tree_f, (STRING)", yyIsDone0", 11L);
          }
          {
            SHORTCARD B_3 = 1, B_4 = (MaxBit - 1) / TreeC1_BSS;

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
          IO_WriteS(Tree_f, (STRING)"; ", 2L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tMark yyMark, yyOffset; ", 25L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" yyParent; ", 11L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_NodeHead } ", 12L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tNodeHead;", 11L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"typedef struct { ", 17L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tKind yyKind; ", 15L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tMark yyMark; ", 15L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_NodeHead } ", 12L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tNodeHead;", 11L);
          IO_WriteNl(Tree_f);
        }
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)TypeDeclNode);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"union ", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Node {", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind Kind;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tNodeHead yyHead;", 18L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)TypeDeclRecord);
        IO_WriteS(Tree_f, (STRING)"};", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"Root;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern unsigned long ", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_HeapUsed;", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern char * ", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolFreePtr, * ", 16L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern unsigned short ", 22L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [", 11L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" + 1];", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern char * ", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeName [", 11L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" + 1];", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern void (* ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Exit) ();", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Alloc ();", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Make", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind));", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"extern bool ", 12L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_IsType ARGS((register ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt, register ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind));", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ProcedureDeclsn);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ProcedureDeclsm);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('f'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Release", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('F'), &Tree_Options) && !Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Release", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Module ();", 10L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Write", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node ARGS((FILE * yyyf, ", 24L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Write", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((FILE * yyyf, ", 20L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Read", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((FILE * yyyf));", 21L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Put", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((FILE * yyyf, ", 20L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Get", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((FILE * yyyf));", 21L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Traverse", 20L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD ARGS((", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt, ", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree yyyProc));", 21L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Traverse", 20L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU ARGS((", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt, ", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree yyyProc));", 21L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Reverse", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld));", 9L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Copy", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('k'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern bool Check", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Query", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('='), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern bool IsEqual", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt1, ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt2));", 8L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"extern void Init", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((register ", 16L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"extern void Begin", 17L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ();", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"extern void Close", 17L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ();", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void ConstDecls
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
          IO_WriteS(Tree_f, (STRING)"# define k", 10L);
          Tree_WI(W_2->Name);
          IO_WriteS(Tree_f, (STRING)" ", 1L);
          Tree_WN(ConstCount);
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
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_3 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_3->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"typedef struct { ", 17L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tNodeHead yyHead; ", 19L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)TypeDeclNode);
        IO_WriteS(Tree_f, (STRING)"} y", 3L);
        Tree_WI(W_3->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_4 = &t->U_1.V_9.Child;

      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_4->Name);
      IO_WriteS(Tree_f, (STRING)"; ", 2L);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_5 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_5->Properties) == 0X0L) {
        Tree_WI(W_5->Type);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_5->Name);
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
  struct S_6 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_6 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_6->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)" y", 2L);
        Tree_WI(W_6->Name);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_6->Name);
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
  struct S_7 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_7 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_7->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" n", 2L);
        Tree_WI(W_7->Name);
        IO_WriteS(Tree_f, (STRING)" ();", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ProcedureDeclsm
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
  case Tree_Class:;
    {
      register Tree_yClass *W_8 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_8->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" m", 2L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        ListCount = 0;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureDeclsm);
        IO_WriteS(Tree_f, (STRING)"));", 3L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_9 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_9->Properties)) {
        if (ListCount > 0) {
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" p", 2L);
        Tree_WI(W_9->Name);
        INC(ListCount);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_10 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Input, W_10->Properties)) {
        if (ListCount > 0) {
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        Tree_WI(W_10->Type);
        IO_WriteS(Tree_f, (STRING)" p", 2L);
        Tree_WI(W_10->Name);
        INC(ListCount);
      }
      return;
    }
    break;
  default :
    break;
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
  struct S_9 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_11 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_11->Properties) == 0X0L) {
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" m", 2L);
        Tree_WI(W_11->Name);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"(", 1L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureDeclsm);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"(", 1L);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureHeadingm);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureHeadingm2);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
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
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"p", 1L);
        Tree_WI(W_12->Name);
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
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"p", 1L);
        Tree_WI(W_13->Name);
        INC(ListCount);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void ProcedureHeadingm2
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
  case Tree_Child:;
    {
      register Tree_yChild *W_14 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_14->Properties)) {
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" p", 2L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_15 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Input, W_15->Properties)) {
        Tree_WI(W_15->Type);
        IO_WriteS(Tree_f, (STRING)" p", 2L);
        Tree_WI(W_15->Name);
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

void TreeC1_TreeImplC
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
      register Tree_yAg *W_16 = &t->U_1.V_26.Ag;

      IO_WriteS(Tree_f, (STRING)"# include \"", 11L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)".h\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(ptr, size)    if ((ptr = (", 43L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)") ", 2L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)"_PoolFreePtr) >= (", 18L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)") ", 2L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr) ", 13L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr = ", 8L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)"_Alloc (); ", 11L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)"_PoolFreePtr += size;", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyFREE(ptr, size)     ", 31L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include <stdio.h>", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifdef __cplusplus", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"extern \"C\" {", 12L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"System.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"General.h\"", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Memory.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"DynArray.h\"", 22L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"StringMem.h\"", 23L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Idents.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Sets.h\"", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Positions.h\"", 23L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"System.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"General.h\"", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Memory.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"DynArray.h\"", 22L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"StringMem.h\"", 23L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Idents.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Sets.h\"", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"Positions.h\"", 23L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(W_16->TreeCodes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_16->TreeCodes->U_1.V_12.Codes.Global);
      Node = W_16->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.GlobalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Global);
        Node = Node->U_1.V_43.Module.Next;
      }
      TreeC2_WriteLine(W_16->TreeCodes->U_1.V_12.Codes.LocalLine);
      Texts_WriteText(Tree_f, W_16->TreeCodes->U_1.V_12.Codes.Local);
      Node = W_16->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.LocalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Local);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"# ifdef getchar", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# undef getchar", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifdef putchar", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# undef putchar", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyExit () { Exit (1); }", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"void (* ", 8L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Exit) () = yyExit;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# define yyBlockSize 20480", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"typedef struct yysBlock {", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" char yyBlock [yyBlockSize];", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" struct yysBlock * yySuccessor;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"} yytBlock, * yytBlockPtr;", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"Root;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"unsigned long ", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_HeapUsed = 0;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static yytBlockPtr yyBlockList = (yytBlockPtr) ", 47L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"char * ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolFreePtr     = (char *) ", 28L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"char * ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr      = (char *) ", 28L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static unsigned short yyMaxSize        = 0;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"unsigned short ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [", 11L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" + 1] = { 0,", 12L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)InitNodeSize);
        IO_WriteS(Tree_f, (STRING)"};", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"char * ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeName [", 11L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" + 1] = {", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" \"", 2L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"\",", 2L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)InitNodeName);
        IO_WriteS(Tree_f, (STRING)"};", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyTypeRange [", 20L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" + 1] = { 0,", 12L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)InitTypeRange);
        IO_WriteS(Tree_f, (STRING)"};", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Alloc ()", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register yytBlockPtr yyBlockPtr = yyBlockList;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register int i;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyMaxSize == 0)", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  for (i = 1; i <= ", 19L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)"; i ++) {", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ", 3L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [i] = (", 17L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [i] + yyMaxAlign - 1) & yyAlignMasks [yyMaxAlign];", 60L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyMaxSize = Max (", 20L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [i], yyMaxSize);", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyBlockList = (yytBlockPtr) Alloc (sizeof (yytBlock));", 55L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyBlockList->yySuccessor = yyBlockPtr;", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolFreePtr = yyBlockList->yyBlock;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr = ", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolFreePtr + yyBlockSize - yyMaxSize + 1;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_HeapUsed += yyBlockSize;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return (", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)") ", 2L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolFreePtr;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Make", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyKind) ", 10L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyALLOC (yyt, ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [yyKind])", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->Kind = yyKind;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyMark = 0;", 24L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('L'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyParent = ", 24L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)" return yyt;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"bool ", 5L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_IsType", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (register ", 11L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt, register ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyt, yyKind) register ", 24L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt; register ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyt != ", 15L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" && yyKind <= yyt->Kind && yyt->Kind <= yyTypeRange [yyKind];", 61L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)ProcedureBodyn);
      }
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('m'), &Tree_Options)) {
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)ProcedureBodym);
      }
      TreeC2_TreeIO(t);
      if (Sets_IsElement(ORD('f'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyChild;", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyRelease", 21L);
        Tree_WI(Tree_iModule);
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
        IO_WriteS(Tree_f, (STRING)" if (yyt == ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") return;", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)ReleaseAttributes1);
        IO_WriteS(Tree_f, (STRING)" default: ;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (-- yyt->yyHead.yyMark == 0) {", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)ReleaseAttributes2);
        IO_WriteS(Tree_f, (STRING)"  default: ;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyFREE (yyt, ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [yyt->Kind])", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"void Release", 12L);
        Tree_WI(Tree_iModule);
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
        IO_WriteS(Tree_f, (STRING)" yyMark (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyRelease", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('F'), &Tree_Options) && !Sets_IsElement(ORD('<'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"void Release", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Module ()", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yytBlockPtr yyBlockPtr;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" while (yyBlockList != (yytBlockPtr) ", 37L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") {", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyBlockPtr = yyBlockList;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyBlockList = yyBlockList->yySuccessor;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Free (sizeof (yytBlock), (char *) yyBlockPtr);", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolFreePtr = (char *) ", 24L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr = (char *) ", 23L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_HeapUsed = 0;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options) || Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree yyProc;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyTraverse", 22L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD", 2L);
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
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyt == ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" || yyt->yyHead.yyMark == 0) return;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt->yyHead.yyMark = 0;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyProc (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)TraverseTD);
        IO_WriteS(Tree_f, (STRING)"  default: return;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"void Traverse", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt, ", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree yyyProc)", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyt, yyyProc) ", 16L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt; ", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree yyyProc;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyMark (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyProc = yyyProc;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyTraverse", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD (yyt);", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyTraverse", 22L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU", 2L);
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
        IO_WriteS(Tree_f, (STRING)" if (yyt == ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" || yyt->yyHead.yyMark == 0) return;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyMark = 0;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_16->Classes, (Tree_ProcOfT)TraverseBU);
        IO_WriteS(Tree_f, (STRING)" default: ;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyProc (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"void Traverse", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt, ", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree yyyProc)", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyt, yyyProc) ", 16L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt; ", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tProcTree yyyProc;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyMark (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyProc = yyyProc;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyTraverse", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU (yyt);", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      TreeImplC1(t);
      return;
    }
  }
}

static void TreeImplC1
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
      register Tree_yAg *W_17 = &t->U_1.V_26.Ag;

      if (Sets_IsElement(ORD('R'), &Tree_Options)) {
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Reverse", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld)", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyOld) ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyNew, yyNext, yyTail;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyNew = yyOld;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyTail = yyOld;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyOld->Kind) {", 24L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)Reverse1);
        IO_WriteS(Tree_f, (STRING)"  default: goto yyExit;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyNew = yyOld;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyOld = yyNext;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"yyExit:", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" switch (yyTail->Kind) {", 24L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)Reverse2);
        IO_WriteS(Tree_f, (STRING)" default: ;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyNew;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('y'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# define yyInitOldToNewStoreSize 32", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"typedef struct { ", 17L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld, yyNew; } yytOldToNew;", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static unsigned long yyOldToNewStoreSize = yyInitOldToNewStoreSize;", 67L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static yytOldToNew yyOldToNewStore [yyInitOldToNewStoreSize];", 61L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static yytOldToNew * yyOldToNewStorePtr = yyOldToNewStore;", 58L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static int yyOldToNewCount;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyStoreOldToNew", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld, ", 8L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyNew)", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyOld, yyNew) ", 16L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld, yyNew;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (++ yyOldToNewCount == yyOldToNewStoreSize)", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ExtendArray ((char * *) & yyOldToNewStorePtr, & yyOldToNewStoreSize, sizeof (yytOldToNew));", 93L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyOldToNewStorePtr [yyOldToNewCount].yyOld = yyOld;", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyOldToNewStorePtr [yyOldToNewCount].yyNew = yyNew;", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyMapOldToNew", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld)", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyOld) ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyOld;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register int yyi;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (yyi = 1; yyi <= yyOldToNewCount; yyi ++)", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyOldToNewStorePtr [yyi].yyOld == yyOld) return yyOldToNewStorePtr [yyi].yyNew;", 85L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyCopy", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt, yyPtrtTree yyNew)", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyt, yyNew) ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt; yyPtrtTree yyNew;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyt == ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") { * yyNew = ", 14L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"; return; }", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyt->yyHead.yyMark == 0) { * yyNew = yyMapOldToNew (yyt); return; }", 73L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyALLOC (* yyNew, ", 20L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [yyt->Kind])", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyt->yyHead.yyMark > 1) { yyStoreOldToNew (yyt, * yyNew); }", 65L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt->yyHead.yyMark = 0;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)Copy);
        IO_WriteS(Tree_f, (STRING)"  default: ;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Copy", 5L);
        Tree_WI(Tree_iModule);
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
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyNew;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyMark (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyOldToNewCount = 0;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyCopy", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt, & yyNew);", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyNew;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('k'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static bool yyCheck", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt));", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"bool Check", 10L);
        Tree_WI(Tree_iModule);
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
        IO_WriteS(Tree_f, (STRING)" yyMark (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyCheck", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static bool yyCheckChild", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyParent, ", 11L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyyChild, ", 11L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyType, char * yySelector)", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyParent, yyyChild, yyType, yySelector)", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyParent, yyyChild;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyType;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" char * yySelector;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" bool yySuccess = ", 18L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_IsType (yyyChild, yyType);", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (! yySuccess) {", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  (void) fputs (\"CheckTree: parent = \", stderr);", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Write", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (stderr, yyParent);", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  (void) fprintf (stderr, \"\\nselector: %s child = \", yySelector);", 65L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Write", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (stderr, yyyChild);", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  (void) fputc ('\\n', stderr);", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyCheck", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyyChild) && yySuccess;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static bool yyCheck", 19L);
        Tree_WI(Tree_iModule);
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
        IO_WriteS(Tree_f, (STRING)" bool yyResult;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyt == ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") return false;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" else if (yyt->yyHead.yyMark == 0) return true;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyMark = 0;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyResult = true;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)CheckAttributes);
        IO_WriteS(Tree_f, (STRING)" default: ;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyResult;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('q'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# define yyyWrite      1", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# define yyyRead       2", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# define yyyQuit       3", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static char yyyString [32], yyCh;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static int yyLength, yyState;", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static bool yyyIsEqual", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (char * yya)", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yya) char * yya;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register int yyi;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyLength >= 0 && yyyString [yyLength] == ' ') {", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyLength != strlen (yya)) return false;", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  for (yyi = 0; yyi < yyLength; yyi ++)", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if (yyyString [yyi] != yya [yyi]) return false;", 50L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" } else {", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyLength >= strlen (yya)) return false;", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  for (yyi = 0; yyi <= yyLength; yyi ++)", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if (yyyString [yyi] != yya [yyi]) return false;", 50L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return true;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"void Query", 10L);
        Tree_WI(Tree_iModule);
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
        IO_WriteS(Tree_f, (STRING)" yyState = yyyWrite;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyState) {", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case yyyQuit : return;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case yyyWrite: Write", 22L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (stdout, yyt); yyState = yyyRead;", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case yyyRead : (void) printf (\"? \"); yyLength = -1; yyCh = getc (stdin);", 74L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   while (yyCh != ", 18L);
        IO_WriteS(Tree_f, (STRING)"'\\n' && yyCh > 0)", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    { yyyString [++ yyLength] = yyCh; yyCh = getc (stdin); }", 60L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if (yyCh < 0) { (void) fputs (\"QueryTree: eof reached\\n\", stderr);", 69L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyState = yyyQuit; return; }", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if      (yyyIsEqual (\"parent\")) { yyState = yyyWrite; return; }", 66L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   else if (yyyIsEqual (\"quit\"  )) { yyState = yyyQuit ; return; }", 66L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   else if (yyt != ", 19L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") {", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    switch (yyt->Kind) {", 24L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)QueryAttributes);
        IO_WriteS(Tree_f, (STRING)"    default: ;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    }", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   }", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('='), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"bool IsEqual", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt1, ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt2)", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyt1, yyt2) ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt1, yyt2;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyt1 == yyt2) return true;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyt1 == ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" || yyt2 == ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" || yyt1->Kind != yyt2->Kind) return false;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" switch (yyt1->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)IsEqualAttributes);
        IO_WriteS(Tree_f, (STRING)" default: return true;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        MaxBit = 0;
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)CompMaxBit);
        IO_WriteS(Tree_f, (STRING)"void Init", 9L);
        Tree_WI(Tree_iModule);
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
        IO_WriteS(Tree_f, (STRING)" register ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyr;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        {
          SHORTCARD B_5 = 0, B_6 = (MaxBit - 1) / TreeC1_BSS;

          if (B_5 <= B_6)
            for (i = B_5;; i += 1) {
              IO_WriteS(Tree_f, (STRING)"  yyt->yyHead.yyIsComp", 22L);
              Tree_WN((LONGINT)i);
              IO_WriteS(Tree_f, (STRING)" = 0;", 5L);
              IO_WriteNl(Tree_f);
              if (Sets_IsElement(ORD('5'), &Tree_Options)) {
                IO_WriteS(Tree_f, (STRING)"  yyt->yyHead.yyIsDone", 22L);
                Tree_WN((LONGINT)i);
                IO_WriteS(Tree_f, (STRING)" = 0;", 5L);
                IO_WriteNl(Tree_f);
              }
              if (i >= B_6) break;
            }
        }
        IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)InitAttributes);
        IO_WriteS(Tree_f, (STRING)"  default: return;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"void Begin", 10L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(W_17->TreeCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_17->TreeCodes->U_1.V_12.Codes.Begin);
      Node = W_17->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void Close", 10L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      TreeC2_WriteLine(W_17->TreeCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_17->TreeCodes->U_1.V_12.Codes.Close);
      Node = W_17->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeC2_WriteLine(Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.TreeCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
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
      register Tree_yClass *W_18 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_18->Properties) == 0X0L) {
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" n", 2L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)" () {", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyALLOC (yyt, ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [k", 12L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)"])", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->Kind = k", 14L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyMark = 0;", 24L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('L'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyParent = ", 24L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
        iClassName = W_18->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodyn);
        IO_WriteS(Tree_f, (STRING)" return yyt;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_19 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)" begin", 6L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)"(yyt->", 6L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_20 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_20->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)" begin", 6L);
        Tree_WI(W_20->Type);
        IO_WriteS(Tree_f, (STRING)"(yyt->", 6L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_20->Name);
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
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_21 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_21->Properties) == 0X0L) {
        ProcedureHeadingm(t);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register ", 10L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyALLOC (yyt, ", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeSize [k", 12L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)"])", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->Kind = k", 14L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyMark = 0;", 24L);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('L'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)" yyt->yyHead.yyParent = ", 24L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
        iClassName = W_21->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ProcedureBodym);
        IO_WriteS(Tree_f, (STRING)" return yyt;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_22 = &t->U_1.V_9.Child;

      if (IN(Tree_Input, W_22->Properties)) {
        IO_WriteS(Tree_f, (STRING)" yyt->", 6L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)" = p", 4L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)" begin", 6L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"(yyt->", 6L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_23 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_23->Properties) == 0X0L) {
        if (IN(Tree_Input, W_23->Properties)) {
          IO_WriteS(Tree_f, (STRING)" yyt->", 6L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_23->Name);
          IO_WriteS(Tree_f, (STRING)" = p", 4L);
          Tree_WI(W_23->Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)" begin", 6L);
          Tree_WI(W_23->Type);
          IO_WriteS(Tree_f, (STRING)"(yyt->", 6L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_23->Name);
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
  struct S_15 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_24 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_24->Properties) == 0X0L && IN(Tree_HasChildren, W_24->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_24->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_24->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReleaseAttributes1);
        IO_WriteS(Tree_f, (STRING)"break;", 6L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_25 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"close", 5L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_25->Name);
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
  struct S_16 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_26 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_26->Properties) == 0X0L && IN(Tree_HasAttributes, W_26->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_26->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_26->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReleaseAttributes2);
        IO_WriteS(Tree_f, (STRING)"break;", 6L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_27 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_27->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"close", 5L);
        Tree_WI(W_27->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_27->Name);
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
  struct S_17 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_28 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_28->Properties) == 0X0L && IN(Tree_HasChildren, W_28->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_28->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_28->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseTD);
        if (TreeC2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"return;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt = yyt->", 11L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)"; break;", 8L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_29 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"TD (yyt->", 9L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_29->Name);
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
  struct S_18 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_30 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_30->Properties) == 0X0L && IN(Tree_HasChildren, W_30->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_30->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_30->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)TraverseBU);
        if (TreeC2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"return;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"BU (yyt->", 9L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)"); break;", 9L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_31 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyTraverse", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"BU (yyt->", 9L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_31->Name);
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
  struct S_19 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_32 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_32->Properties) == 0X0L) {
        iClassName = W_32->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse1);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_33 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_33->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)": yyNext = yyOld->", 18L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteS(Tree_f, (STRING)" yyOld->", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_33->Name);
        IO_WriteS(Tree_f, (STRING)" = yyNew; break;", 16L);
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
      register Tree_yClass *W_34 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_34->Properties) == 0X0L) {
        iClassName = W_34->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Reverse2);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_35 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_35->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)": yyTail->", 10L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_35->Name);
        IO_WriteS(Tree_f, (STRING)" = yyOld; break;", 16L);
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
      register Tree_yClass *W_36 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_36->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_36->Name);
        IO_WriteS(Tree_f, (STRING)": (* yyNew)->", 13L);
        Tree_WI(W_36->Name);
        IO_WriteS(Tree_f, (STRING)" = yyt->", 8L);
        Tree_WI(W_36->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_36->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Copy);
        if (TreeC2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"return;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt = yyt->", 11L);
          Tree_WI(W_36->Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"yyNew = & (* yyNew)->", 21L);
          Tree_WI(W_36->Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)"; break;", 8L);
          IO_WriteNl(Tree_f);
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_37 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"copy", 4L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ((* yyNew)->", 13L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_37->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        IO_WriteS(Tree_f, (STRING)"yyt->", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_37->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_38 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_38->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"copy", 4L);
        Tree_WI(W_38->Type);
        IO_WriteS(Tree_f, (STRING)" ((* yyNew)->", 13L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_38->Name);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        IO_WriteS(Tree_f, (STRING)"yyt->", 5L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_38->Name);
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
      register Tree_yClass *W_39 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_39->Properties) == 0X0L && IN(Tree_HasChildren, W_39->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_39->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        iClassName = W_39->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)CheckAttributes);
        IO_WriteS(Tree_f, (STRING)"break;", 6L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_40 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"yyResult = yyCheckChild (yyt, yyt->", 35L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_40->Name);
      IO_WriteS(Tree_f, (STRING)", k", 3L);
      Tree_WI(W_40->Type);
      IO_WriteS(Tree_f, (STRING)", \"", 3L);
      Tree_WI(W_40->Name);
      IO_WriteS(Tree_f, (STRING)"\") && yyResult;", 15L);
      IO_WriteNl(Tree_f);
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
  struct S_23 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_41 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_41->Properties) == 0X0L) {
        iRange = W_41->Name;
        Tree_ForallClasses(W_41->Extensions, (Tree_ProcOfT)InitTypeRange2);
        IO_WriteS(Tree_f, (STRING)" k", 2L);
        Tree_WI(iRange);
        IO_WriteS(Tree_f, (STRING)",", 1L);
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
      register Tree_yClass *W_42 = &t->U_1.V_5.Class;

      iRange = W_42->Name;
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
      register Tree_yClass *W_43 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_43->Properties) == 0X0L && IN(Tree_HasChildren, W_43->Properties)) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_43->Name);
        IO_WriteS(Tree_f, (STRING)": if (false) ;", 14L);
        IO_WriteNl(Tree_f);
        iClassName = W_43->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)QueryAttributes);
        IO_WriteS(Tree_f, (STRING)"break;", 6L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_44 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"else if (yyyIsEqual (\"", 22L);
      Tree_WI(W_44->Name);
      IO_WriteS(Tree_f, (STRING)"\")) Query", 9L);
      Tree_WI(Tree_iModule);
      IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_44->Name);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_45 = &t->U_1.V_10.Attribute;

        if (!IN(Tree_Link, W_45->Properties)) {
          goto EXIT_1;
        }
        IO_WriteS(Tree_f, (STRING)"else if (yyyIsEqual (\"", 22L);
        Tree_WI(W_45->Name);
        IO_WriteS(Tree_f, (STRING)"\")) Query", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_45->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_1:;
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
      register Tree_yClass *W_46 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_46->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_46->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_46->Name);
        IO_WriteS(Tree_f, (STRING)": return true", 13L);
        IO_WriteNl(Tree_f);
        iClassName = W_46->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)IsEqualAttributes);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_47 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"&& equal", 8L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" (yyt1->", 8L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_47->Name);
      IO_WriteS(Tree_f, (STRING)", yyt2->", 8L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_47->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_48 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_48->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"&& (equal", 9L);
        Tree_WI(W_48->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt1->", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_48->Name);
        IO_WriteS(Tree_f, (STRING)", yyt2->", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_48->Name);
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
  struct S_27 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    for (;;) {
      {
        register Tree_yClass *W_49 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_49->Properties) == 0X0L && IN(Tree_HasChildren, W_49->Properties))) {
          goto EXIT_2;
        }
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_49->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_49->Name;
        gBitCount = W_49->BitCount;
        Tree_ForallAttributes(t, (Tree_ProcOfT)InitAttributes);
        if (TreeC2_Iterator == Tree_NoTree || !IN(Tree_Input, TreeC2_Iterator->U_1.V_9.Child.Properties)) {
          IO_WriteS(Tree_f, (STRING)"return;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt = yyt->", 11L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)"; break;", 8L);
          IO_WriteNl(Tree_f);
        }
        return;
      }
    } EXIT_2:;
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_50 = &t->U_1.V_9.Child;

        if (!IN(Tree_Input, W_50->Properties)) {
          goto EXIT_3;
        }
        IO_WriteS(Tree_f, (STRING)"yyr = yyt->", 11L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_50->Name);
        IO_WriteS(Tree_f, (STRING)"; yyr->yyHead.yyOffset = ", 25L);
        Tree_WN((LONGINT)(gBitCount + W_50->BitOffset));
        IO_WriteS(Tree_f, (STRING)"; yyr->yyHead.yyParent = yyt;", 29L);
        IO_WriteNl(Tree_f);
        if (!(t != TreeC2_Iterator)) {
          goto EXIT_3;
        }
        IO_WriteS(Tree_f, (STRING)"Init", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyr);", 7L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_3:;
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
    {
      register Tree_yClass *W_51 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_51->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)" sizeof (y", 10L);
        Tree_WI(W_51->Name);
        IO_WriteS(Tree_f, (STRING)"),", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void InitNodeName
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
      register Tree_yClass *W_52 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_52->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)" \"", 2L);
        Tree_WI(W_52->Name);
        IO_WriteS(Tree_f, (STRING)"\",", 2L);
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
      register Tree_yClass *W_53 = &t->U_1.V_5.Class;

      i = 1;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CompMaxBit);
      MaxBit = General_Max((LONGINT)i, (LONGINT)MaxBit);
      return;
    }
    break;
  case Tree_Child:;
    for (;;) {
      {
        register Tree_yChild *W_54 = &t->U_1.V_9.Child;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_54->Properties) == 0X0L)) {
          goto EXIT_4;
        }
        INC(i);
        return;
      }
    } EXIT_4:;
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_55 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_55->Properties) == 0X0L)) {
          goto EXIT_5;
        }
        INC(i);
        return;
      }
    } EXIT_5:;
    break;
  default :
    break;
  }
}

void TreeC1_BeginTreeC1
# ifdef __STDC__
()
# else
()
# endif
{
  ConstCount = 0;
}

void TreeC1_CloseTreeC1
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

void TreeC1__init()
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
    TreeC2__init();
    IOUtils__init();
    Tree__init();
    Strings__init();

    TreeC1_yyf = IO_StdOutput;
    TreeC1_Exit = yyExit;
    TreeC1_BeginTreeC1();
  }
}
