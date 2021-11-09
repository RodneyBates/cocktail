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

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_TreeMod1
#include "TreeMod1.h"
#endif

#ifndef DEFINITION_TreeMod2
#include "TreeMod2.h"
#endif

#ifndef DEFINITION_EvalMod3
#include "EvalMod3.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_EvalMod
#include "EvalMod.h"
#endif

Tree_tTree EvalMod_Class;
IO_tFile EvalMod_yyf;
PROC EvalMod_Exit;

static SHORTCARD n;
static Tree_tTree Node, Attr, ChildsClass;
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
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void WriteType ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
struct S_7 {
    union {
        struct {
            struct S_8 {
                Tree_tTree TheClass;
                INTEGER k;
            } yyR8;
        } V_1;
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module EvalMod, routine ", 31L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*EvalMod_Exit)();
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

void EvalMod_EvalDefMod
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
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT ", 7L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      TreeMod2_WriteLine(W_1->EvalCodes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_1->EvalCodes->U_1.V_12.Codes.Import);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.ImportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Import);
        Node = Node->U_1.V_43.Module.Next;
      }
      TreeMod2_WriteLine(W_1->EvalCodes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_1->EvalCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.ExportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Export);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval (yyt: ", 21L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

void EvalMod_EvalImplHead
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
  if (t->U_1.V_1.Kind == Tree_Ag) {
    {
      register Tree_yAg *W_2 = &t->U_1.V_26.Ag;

      IO_WriteS(Tree_f, (STRING)"# define DEP(a, b) a", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define SELF yyt", 17L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPLEMENTATION MODULE ", 22L);
      Tree_WI(W_2->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT SYSTEM, ", 15L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Layout, Strings, Idents, Texts, Sets;", 44L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options) || Sets_IsElement(ORD('L'), &Tree_Options) || Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT IO;", 10L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT General;", 15L);
        IO_WriteNl(Tree_f);
      }
      TreeMod2_WriteLine(W_2->EvalCodes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_2->EvalCodes->U_1.V_12.Codes.Global);
      Node = W_2->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.GlobalLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Global);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyb	: BOOLEAN;", 18L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('X'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)".w\"", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# define yyWrite", 16L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"(a) ", 4L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".Write", 6L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyf, a)", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyf	: IO.tFile;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteHex (VAR yyx: ARRAY OF SYSTEM.BYTE);", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi	: INTEGER;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   FOR yyi := 0 TO INTEGER (HIGH (yyx)) DO", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteN (yyf, ORD (CHAR (yyx [yyi])), 2, 16);", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, ' ');", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteHex;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteNl;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN IF yyTrace THEN", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IO.WriteNl (IO.StdOutput); IO.WriteFlush (IO.StdOutput);", 58L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END; END yyWriteNl;", 20L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"CONST yyTrace = TRUE;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteS (yys: ARRAY OF CHAR);", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdOutput, yys); Layout.WriteSpaces (IO.StdOutput, 15 - INTEGER (HIGH (yys)));", 94L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteS;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteType (yyt: ", 28L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE yyt^.Kind OF", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_2->Classes, (Tree_ProcOfT)WriteType);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteType;", 17L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('X'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteEval (yyt: ", 28L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yys: ARRAY OF CHAR);", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteType (yyt);", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (IO.StdOutput, ' e ');", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (IO.StdOutput, yys);", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Layout.WriteSpaces (IO.StdOutput, 23 - INTEGER (HIGH (yys)));", 64L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (IO.StdOutput, ' = ');", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteFlush (IO.StdOutput);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteEval;", 17L);
        IO_WriteNl(Tree_f);
      } else if (Sets_IsElement(ORD('Y'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteEval (yyt: ", 28L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yys: ARRAY OF CHAR);", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteType (yyt);", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (IO.StdOutput, ' e ');", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (IO.StdOutput, yys);", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteNl (IO.StdOutput);", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteFlush (IO.StdOutput);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteEval;", 17L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('Z'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteVisit (yyt: ", 29L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"; yys: ARRAY OF CHAR);", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteType (yyt);", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (IO.StdOutput, ' v ');", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (IO.StdOutput, yys);", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteNl (IO.StdOutput);", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteFlush (IO.StdOutput);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteVisit;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyVisitParent (yyt: ", 30L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN yyWriteVisit (yyt, 'parent'); END yyVisitParent;", 55L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

void EvalMod_EvalImplMod
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
  if (t->U_1.V_1.Kind == Tree_Ag) {
    {
      register Tree_yAg *W_3 = &t->U_1.V_26.Ag;

      EvalMod_EvalImplHead(t);
      if (!Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval (yyt: ", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN ", 7L);
        if (Tree_MaxVisit > 0) {
          IO_WriteS(Tree_f, (STRING)"yyVisit1 (yyt); ", 16L);
        }
        IO_WriteS(Tree_f, (STRING)"END Eval;", 9L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR xxStack: CARDINAL;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval (yyt: ", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR xxHigh: BOOLEAN;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  xxStack := MAX (INTEGER);", 27L);
        IO_WriteNl(Tree_f);
        if (Tree_MaxVisit > 0) {
          IO_WriteS(Tree_f, (STRING)"  yyVisit1 (yyt);", 17L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdOutput, 'Stacksize ');", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IO.WriteI (IO.StdOutput, CARDINAL (SYSTEM.ADR (xxHigh)) - xxStack, 0);", 72L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IO.WriteNl (IO.StdOutput);", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Eval;", 10L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      {
        SHORTCARD B_3 = 1, B_4 = Tree_MaxVisit;

        if (B_3 <= B_4)
          for (n = B_3;; n += 1) {
            IO_WriteS(Tree_f, (STRING)"PROCEDURE yyVisit", 17L);
            Tree_WN((LONGINT)n);
            IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
            Tree_WI(Tree_iMain);
            IO_WriteS(Tree_f, (STRING)".", 1L);
            Tree_WI(Tree_itTree);
            IO_WriteS(Tree_f, (STRING)");", 2L);
            IO_WriteNl(Tree_f);
            TreeMod2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.LocalLine);
            Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Local);
            Node = W_3->Modules;
            while (Node->U_1.V_1.Kind == Tree_Module) {
              TreeMod2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
              Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
              Node = Node->U_1.V_43.Module.Next;
            }
            if (Sets_IsElement(ORD('9'), &Tree_Options)) {
              IO_WriteS(Tree_f, (STRING)" VAR xxLow: BOOLEAN;", 20L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"  xxStack := General.Min (xxStack, CARDINAL (SYSTEM.ADR (xxLow)));", 66L);
              IO_WriteNl(Tree_f);
            } else {
              IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
              IO_WriteNl(Tree_f);
            }
            IO_WriteS(Tree_f, (STRING)"  CASE yyt^.Kind OF", 19L);
            IO_WriteNl(Tree_f);
            if (IN(Tree_cOAG, Tree_GrammarClass)) {
              Tree_ForallClasses(W_3->Classes, (Tree_ProcOfT)EvalMod_GenEvaluator);
            }
            IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
            IO_WriteNl(Tree_f);
            if (Sets_IsElement(ORD('Z'), &Tree_Options)) {
              IO_WriteS(Tree_f, (STRING)"   yyVisitParent (yyt);", 23L);
              IO_WriteNl(Tree_f);
            }
            IO_WriteS(Tree_f, (STRING)"  END;", 6L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)" END yyVisit", 12L);
            Tree_WN((LONGINT)n);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            IO_WriteNl(Tree_f);
            if (n >= B_4) break;
          }
      }
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMod2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Begin);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)" END Begin", 10L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMod2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Close);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMod2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)" END Close", 10L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('X'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" yyf := IO.StdOutput;", 21L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void WriteType
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
    for (;;) {
      {
        register Tree_yClass *W_4 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_4->Properties) == 0X0L)) {
          goto EXIT_1;
        }
        if (!IN(Tree_Trace, W_4->Properties)) {
          goto EXIT_1;
        }
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(Tree_TreeRoot->U_1.V_26.Ag.TreeName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)": yyWriteS ('", 13L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)"');", 3L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_1:;
  }
}

void EvalMod_GenEvaluator
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
    for (;;) {
      {
        register Tree_yClass *W_5 = &t->U_1.V_5.Class;

        if (!((Tree_NoCodeClass & W_5->Properties) == 0X0L)) {
          goto EXIT_2;
        }
        if (W_5->Generated == W_5->InstCount || W_5->Visits < n) {
          return;
        }
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(Tree_TreeRoot->U_1.V_26.Ag.TreeName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_5->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        EvalMod_Class = t;
        for (;;) {
          if (W_5->Generated == W_5->InstCount) {
            goto EXIT_3;
          }
          INC(W_5->Generated);
          {
            register Tree_tInstance *W_6 = &W_5->Instance->A[W_5->Instance->A[W_5->Generated - 1].Order - 1];

            if (IN(Tree_Left, W_6->Properties) && W_6->Attribute->U_1.V_9.Child.Partition > n) {
              DEC(W_5->Generated);
              goto EXIT_3;
            }
            if (SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_First), W_6->Properties) && !IN(Tree_Virtual, W_6->Properties)) {
              if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, '", 19L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"');", 3L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMod_GenEvaluator(W_6->Action);
                }
                IO_WriteNl(Tree_f);
                if (W_6->Attribute->U_1.V_1.Kind == Tree_Child || W_6->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                  IO_WriteS(Tree_f, (STRING)"write", 5L);
                  Tree_WI(Tree_itTree);
                  IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
                  Tree_WI(W_5->Name);
                  IO_WriteS(Tree_f, (STRING)".", 1L);
                  Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"^.", 2L);
                  Tree_WI(W_6->Selector->U_1.V_9.Child.Type);
                  IO_WriteS(Tree_f, (STRING)".", 1L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)")", 1L);
                  IO_WriteNl(Tree_f);
                } else {
                  IO_WriteS(Tree_f, (STRING)"write", 5L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Type);
                  IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
                  Tree_WI(W_5->Name);
                  IO_WriteS(Tree_f, (STRING)".", 1L);
                  Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)"^.", 2L);
                  Tree_WI(W_6->Selector->U_1.V_9.Child.Type);
                  IO_WriteS(Tree_f, (STRING)".", 1L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)") yyWriteNl;", 12L);
                  IO_WriteNl(Tree_f);
                }
              } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, '", 19L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"');", 3L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMod_GenEvaluator(W_6->Action);
                }
              } else {
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMod_GenEvaluator(W_6->Action);
                }
              }
            }
            if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left) | SET_ELEM(Tree_First), W_6->Properties) && ((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Virtual)) & W_6->Properties) == 0X0L) {
              if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, '", 19L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"');", 3L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMod_GenEvaluator(W_6->Action);
                }
                IO_WriteNl(Tree_f);
                if (IN(Tree_Test, W_6->Properties)) {
                  IO_WriteS(Tree_f, (STRING)"writeBOOLEAN (yyb) yyWriteNl;", 29L);
                  IO_WriteNl(Tree_f);
                } else if (W_6->Attribute->U_1.V_1.Kind == Tree_Child || W_6->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                  IO_WriteS(Tree_f, (STRING)"write", 5L);
                  Tree_WI(Tree_itTree);
                  IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
                  Tree_WI(W_5->Name);
                  IO_WriteS(Tree_f, (STRING)".", 1L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)")", 1L);
                } else {
                  IO_WriteS(Tree_f, (STRING)"write", 5L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Type);
                  IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
                  Tree_WI(W_5->Name);
                  IO_WriteS(Tree_f, (STRING)".", 1L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)") yyWriteNl;", 12L);
                  IO_WriteNl(Tree_f);
                }
              } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"yyWriteEval (yyt, '", 19L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"');", 3L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMod_GenEvaluator(W_6->Action);
                }
              } else {
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMod_GenEvaluator(W_6->Action);
                }
              }
            }
            if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_First), W_6->Properties) && W_6->Attribute->U_1.V_9.Child.Partition <= W_6->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Visits) {
              if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"yyWriteVisit (yyt, '", 20L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" ", 1L);
                Tree_WN((LONGINT)W_6->Attribute->U_1.V_9.Child.Partition);
                IO_WriteS(Tree_f, (STRING)"');", 3L);
                IO_WriteNl(Tree_f);
              }
              IO_WriteS(Tree_f, (STRING)"yyVisit", 7L);
              Tree_WN((LONGINT)W_6->Attribute->U_1.V_9.Child.Partition);
              IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
              Tree_WI(W_5->Name);
              IO_WriteS(Tree_f, (STRING)".", 1L);
              Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
              IO_WriteS(Tree_f, (STRING)");", 2L);
              IO_WriteNl(Tree_f);
            }
          }
        } EXIT_3:;
        if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)"yyVisitParent (yyt);", 20L);
          IO_WriteNl(Tree_f);
        }
        return;
      }
    } EXIT_2:;
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_7 = &t->U_1.V_36.Assign;

      TreeMod2_WriteLine(W_7->Pos);
      EvalMod_GenEvaluator(W_7->Results);
      IO_WriteS(Tree_f, (STRING)":=", 2L);
      EvalMod_GenEvaluator(W_7->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_8 = &t->U_1.V_37.Copy;

      TreeMod2_WriteLine(W_8->Pos);
      EvalMod_GenEvaluator(W_8->Results);
      IO_WriteS(Tree_f, (STRING)":=", 2L);
      EvalMod_GenEvaluator(W_8->Arguments);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_9 = &t->U_1.V_38.TargetCode;

      TreeMod2_WriteLine(W_9->Pos);
      EvalMod_GenEvaluator(W_9->Code);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_10 = &t->U_1.V_40.Check;

      TreeMod2_WriteLine(W_10->Pos);
      if (W_10->Condition != Tree_NoTree) {
        if (Sets_IsElement(ORD('X'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"yyb := ", 7L);
          EvalMod_GenEvaluator(W_10->Condition);
          IO_WriteS(Tree_f, (STRING)"; IF NOT yyb THEN ", 18L);
        } else {
          IO_WriteS(Tree_f, (STRING)"IF NOT (", 8L);
          EvalMod_GenEvaluator(W_10->Condition);
          IO_WriteS(Tree_f, (STRING)") THEN ", 7L);
        }
        EvalMod_GenEvaluator(W_10->Statement);
        IO_WriteNl(Tree_f);
        if (W_10->Actions->U_1.V_1.Kind == Tree_Check) {
          IO_WriteS(Tree_f, (STRING)"ELSE", 4L);
          IO_WriteNl(Tree_f);
          EvalMod_GenEvaluator(W_10->Actions);
        }
        IO_WriteS(Tree_f, (STRING)" END;", 5L);
        IO_WriteNl(Tree_f);
      } else {
        if (Sets_IsElement(ORD('X'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"yyb := FALSE; ", 14L);
        }
        EvalMod_GenEvaluator(W_10->Statement);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        EvalMod_GenEvaluator(W_10->Actions);
      }
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_11 = &t->U_1.V_15.Designator;

      Attr = Tree_IdentifyAttribute(EvalMod_Class, W_11->Selector);
      if (Attr != Tree_NoTree) {
        ChildsClass = Attr->U_1.V_9.Child.Class;
        Attr = Tree_IdentifyAttribute(ChildsClass, W_11->Attribute);
        if (!IN(Tree_Virtual, Attr->U_1.V_10.Attribute.Properties)) {
          IO_WriteS(Tree_f, (STRING)"yyt^.", 5L);
          Tree_WI(EvalMod_Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_11->Selector);
          IO_WriteS(Tree_f, (STRING)"^.", 2L);
          Tree_WI(ChildsClass->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_11->Attribute);
        }
      } else {
        Tree_WI(W_11->Selector);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_11->Attribute);
      }
      EvalMod_GenEvaluator(W_11->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_12 = &t->U_1.V_16.Ident;

      Attr = Tree_IdentifyAttribute(EvalMod_Class, W_12->Attribute);
      if (Attr != Tree_NoTree) {
        if (!IN(Tree_Virtual, Attr->U_1.V_10.Attribute.Properties)) {
          IO_WriteS(Tree_f, (STRING)"yyt^.", 5L);
          Tree_WI(EvalMod_Class->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_12->Attribute);
        }
      } else {
        Tree_WI(W_12->Attribute);
      }
      EvalMod_GenEvaluator(W_12->Next);
      return;
    }
    break;
  case Tree_Remote:;
    {
      register struct S_8 *W_13 = &yyTempo.U_1.V_1.yyR8;

      {
        register Tree_yRemote *W_14 = &t->U_1.V_17.Remote;

        W_13->TheClass = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_14->Type);
        if (W_13->TheClass != Tree_NoTree) {
          Attr = Tree_IdentifyAttribute(W_13->TheClass, W_14->Attribute);
          if (Attr != Tree_NoTree) {
            {
              register Tree_yAttribute *W_15 = &Attr->U_1.V_10.Attribute;

              W_13->k = EvalMod3_ToBit0(W_13->TheClass, (LONGINT)W_15->AttrIndex);
              if (IN(Tree_Synthesized, W_15->Properties)) {
                IO_WriteS(Tree_f, (STRING)"REMOTE_SYN (yyIsComp", 20L);
                Tree_WN(W_13->k / TreeMod1_BSS);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WN(W_13->k % TreeMod1_BSS);
                IO_WriteS(Tree_f, (STRING)", yyS", 5L);
                Tree_WN(W_13->k);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                EvalMod_GenEvaluator(W_14->Designators);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WI(t->U_1.V_17.Remote.Type);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WI(W_14->Attribute);
                IO_WriteS(Tree_f, (STRING)")", 1L);
              } else if (IN(Tree_Inherited, W_15->Properties)) {
                IO_WriteS(Tree_f, (STRING)"REMOTE_INH (yyIsComp", 20L);
                Tree_WN(W_13->k / TreeMod1_BSS);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WN(W_13->k % TreeMod1_BSS);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WN(W_13->k);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                EvalMod_GenEvaluator(W_14->Designators);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WI(t->U_1.V_17.Remote.Type);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WI(W_14->Attribute);
                IO_WriteS(Tree_f, (STRING)")", 1L);
              } else {
                EvalMod_GenEvaluator(W_14->Designators);
                IO_WriteS(Tree_f, (STRING)"^.", 2L);
                Tree_WI(t->U_1.V_17.Remote.Type);
                IO_WriteS(Tree_f, (STRING)".", 1L);
                Tree_WI(W_14->Attribute);
              }
            }
          }
        }
        EvalMod_GenEvaluator(W_14->Next);
        return;
      }
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_16 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_16->Code);
      EvalMod_GenEvaluator(W_16->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_17 = &t->U_1.V_19.Anys;

      EvalMod_GenEvaluator(W_17->Layouts);
      EvalMod_GenEvaluator(W_17->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_18 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_18->Code);
      EvalMod_GenEvaluator(W_18->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void EvalMod_BeginEvalMod
# ifdef __STDC__
()
# else
()
# endif
{
}

void EvalMod_CloseEvalMod
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

void EvalMod__init()
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
    Texts__init();
    Sets__init();
    TreeMod1__init();
    TreeMod2__init();
    EvalMod3__init();
    Tree__init();

    EvalMod_yyf = IO_StdOutput;
    EvalMod_Exit = yyExit;
    EvalMod_BeginEvalMod();
  }
}
