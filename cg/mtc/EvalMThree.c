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

#ifndef DEFINITION_TreeMThree2
#include "TreeMThree2.h"
#endif

#ifndef DEFINITION_EvalMThree3
#include "EvalMThree3.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_EvalMThree
#include "EvalMThree.h"
#endif

Tree_tTree EvalMThree_Class;
IO_tFile EvalMThree_yyf;
PROC EvalMThree_Exit;

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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module EvalMThree, routine ", 34L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*EvalMThree_Exit)();
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

void EvalMThree_EvalInterface
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
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT ", 7L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('X'), &Tree_Options) || Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options) || Sets_IsElement(ORD('L'), &Tree_Options) || Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Wr , Fmt ;", 17L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('X'), &Tree_Options) || Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"IMPORT Text ;", 13L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"IMPORT Stdio , Text ;", 21L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(W_1->EvalCodes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_1->EvalCodes->U_1.V_12.Codes.Import);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.ImportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Import);
        Node = Node->U_1.V_43.Module.Next;
      }
      TreeMThree2_WriteLine(W_1->EvalCodes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_1->EvalCodes->U_1.V_12.Codes.Export);
      Node = W_1->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.ExportLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Export);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval ( t : ", 21L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_1->EvalName);
      IO_WriteS(Tree_f, (STRING)" .", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

void EvalMThree_EvalModuleHead
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
      IO_WriteS(Tree_f, (STRING)"# define SELF TNode", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"MODULE ", 7L);
      Tree_WI(W_2->EvalName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT ", 7L);
      Tree_WI(Tree_iMain);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options)) {
      }
      if (Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options) || Sets_IsElement(ORD('L'), &Tree_Options) || Sets_IsElement(ORD('9'), &Tree_Options)) {
      }
      TreeMThree2_WriteLine(W_2->EvalCodes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_2->EvalCodes->U_1.V_12.Codes.Global);
      Node = W_2->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.GlobalLine);
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
        IO_WriteS(Tree_f, (STRING)"VAR yyf	: Wr . T ;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteHex ( VAR yyx : ARRAY OF CHAR ) ", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   FOR yyi := 0 TO NUMBER ( yyx ) - 1 DO", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Fmt . Pad ( Fmt . Int ( ORD ( yyx [ yyi ] ) , 16 ) , 2 ) ) ;", 85L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutChar ( yyf, ' ' ) ;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteHex ;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteNl ( ) ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN IF yyTrace THEN", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ;", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . Flush ( Stdio . stdout ) ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END; END yyWriteNl;", 20L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"CONST yyTrace = TRUE;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteS (yys: TEXT )", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . Stdout , yys ) ;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . Stdout , Fmt . Pad ( \"\" , MAX ( 0, 15 - Text . Length ( yys ) ) ) ) ;", 94L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteS;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteType ( yyt : ", 30L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  TYPECASE yyt OF", 17L);
        IO_WriteNl(Tree_f);
        WriteType(W_2->Classes);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteType;", 17L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('X'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteEval  (yyt : ", 30L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; yys : TEXT )", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteType ( yyt ) ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout, \" e \" ) ;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout, yys ) ;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout , Fmt . Pad ( \"\" , MAX ( 0 , 23 - Text . Length ( yys ) ) ) ) ;", 96L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout, \" = \" ) ;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . Flush ( Stdio . Stdout) ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteEval ;", 18L);
        IO_WriteNl(Tree_f);
      } else if (Sets_IsElement(ORD('Y'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteEval  (yyt : ", 30L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; yys : TEXT )", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteType ( yyt ) ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout, \" e \" ) ;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout, yys ) ;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout , Wr . EOL ) ;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . Flush ( Stdio . Stdout) ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteEval;", 17L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('Z'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteVisit ( yyt : ", 31L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; yys : TEXT )", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyTrace THEN", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteType ( yyt ) ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout, \" v \" ) ;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout, yys ) ;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . Stdout , Wr . EOL ) ;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . Flush ( Stdio . Stdout) ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteVisit ;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyVisitParent ( yyt : ", 32L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN yyWriteVisit ( yyt , \"parent\" ) ; END yyVisitParent ;", 60L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

void EvalMThree_EvalModule
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

      EvalMThree_EvalModuleHead(t);
      if (!Sets_IsElement(ORD('9'), &Tree_Options)) {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval ( yyt : ", 23L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN ", 7L);
        if (Tree_MaxVisit > 0) {
          IO_WriteS(Tree_f, (STRING)"yyVisit1  (yyt ) ;", 18L);
        }
        IO_WriteS(Tree_f, (STRING)"END Eval ;", 10L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR xxStack : INTEGER ;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Eval ( yyt : ", 23L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR xxHigh : BOOLEAN ;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  xxStack := LAST ( INTEGER ) ;", 31L);
        IO_WriteNl(Tree_f);
        if (Tree_MaxVisit > 0) {
          IO_WriteS(Tree_f, (STRING)"  yyVisit1 ( yyt ) ;", 20L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . Stdout , \"Stacksize \" ) ;", 50L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . Stdout", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               , Fmt . Int ( LOOPHOLE ( ADR ( xxHigh ) , INTEGER ) - xxStack ) ) ;", 82L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . Stdout , Wr . EOL );", 45L);
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
            IO_WriteS(Tree_f, (STRING)"  (yyt : ", 9L);
            Tree_WI(Tree_iMain);
            IO_WriteS(Tree_f, (STRING)" . ", 3L);
            Tree_WI(Tree_itTree);
            IO_WriteS(Tree_f, (STRING)" )", 2L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)"=", 1L);
            IO_WriteNl(Tree_f);
            TreeMThree2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.LocalLine);
            Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Local);
            Node = W_3->Modules;
            while (Node->U_1.V_1.Kind == Tree_Module) {
              TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.LocalLine);
              Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Local);
              Node = Node->U_1.V_43.Module.Next;
            }
            if (Sets_IsElement(ORD('9'), &Tree_Options)) {
              IO_WriteS(Tree_f, (STRING)" VAR xxLow : BOOLEAN ;", 22L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"  xxStack := MIN ( xxStack , LOOPHOLE ( ADR ( xxLow ) , INTEGER ) ) ;", 69L);
              IO_WriteNl(Tree_f);
            } else {
              IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
              IO_WriteNl(Tree_f);
            }
            IO_WriteS(Tree_f, (STRING)"  TYPECASE yyt OF", 17L);
            IO_WriteNl(Tree_f);
            if (IN(Tree_cOAG, Tree_GrammarClass)) {
              EvalMThree_GenEvaluator(W_3->Classes);
            }
            IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
            IO_WriteNl(Tree_f);
            if (Sets_IsElement(ORD('Z'), &Tree_Options)) {
              IO_WriteS(Tree_f, (STRING)"   yyVisitParent ( yyt ) ;", 26L);
              IO_WriteNl(Tree_f);
            }
            IO_WriteS(Tree_f, (STRING)"  END;", 6L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)" END yyVisit", 12L);
            Tree_WN((LONGINT)n);
            IO_WriteS(Tree_f, (STRING)" ;", 2L);
            IO_WriteNl(Tree_f);
            IO_WriteNl(Tree_f);
            if (n >= B_4) break;
          }
      }
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ( )", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Begin);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.BeginLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Begin);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)" END Begin", 10L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ( )", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      TreeMThree2_WriteLine(W_3->EvalCodes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_3->EvalCodes->U_1.V_12.Codes.Close);
      Node = W_3->Modules;
      while (Node->U_1.V_1.Kind == Tree_Module) {
        TreeMThree2_WriteLine(Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.CloseLine);
        Texts_WriteText(Tree_f, Node->U_1.V_43.Module.EvalCodes->U_1.V_12.Codes.Close);
        Node = Node->U_1.V_43.Module.Next;
      }
      IO_WriteS(Tree_f, (STRING)" END Close", 10L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('X'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)" yyf := Stdio . Stdout ;", 24L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_3->EvalName);
      IO_WriteS(Tree_f, (STRING)" .", 2L);
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

        WriteType(W_4->Extensions);
        if (!((Tree_NoCodeClass & W_4->Properties) == 0X0L)) {
          goto EXIT_1;
        }
        if (!IN(Tree_Trace, W_4->Properties)) {
          goto EXIT_1;
        }
        IO_WriteS(Tree_f, (STRING)"  | ", 4L);
        Tree_WI(Tree_TreeRoot->U_1.V_26.Ag.TreeName);
        IO_WriteS(Tree_f, (STRING)" . t", 4L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)" => yyWriteS ( \"", 16L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)"\" );", 4L);
        IO_WriteNl(Tree_f);
        WriteType(W_4->Next);
        return;
      }
    } EXIT_1:;
  }
}

void EvalMThree_GenEvaluator
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

        EvalMThree_GenEvaluator(W_5->Extensions);
        if (!((Tree_NoCodeClass & W_5->Properties) == 0X0L)) {
          goto EXIT_2;
        }
        if (W_5->Generated == W_5->InstCount || W_5->Visits < n) {
          return;
        }
        IO_WriteS(Tree_f, (STRING)"  | ", 4L);
        Tree_WI(Tree_TreeRoot->U_1.V_26.Ag.TreeName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_5->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) =>", 13L);
        IO_WriteNl(Tree_f);
        EvalMThree_Class = t;
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
                IO_WriteS(Tree_f, (STRING)"    yyWriteEval ( TNode , \"", 27L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\" );", 4L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMThree_GenEvaluator(W_6->Action);
                }
                IO_WriteNl(Tree_f);
                if (W_6->Attribute->U_1.V_1.Kind == Tree_Child || W_6->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                  IO_WriteS(Tree_f, (STRING)"    write", 9L);
                  Tree_WI(Tree_itTree);
                  IO_WriteS(Tree_f, (STRING)"( TNode . ", 10L);
                  Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)" . ", 3L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)")", 1L);
                  IO_WriteNl(Tree_f);
                } else {
                  IO_WriteS(Tree_f, (STRING)"    write", 9L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Type);
                  IO_WriteS(Tree_f, (STRING)"( TNode . ", 10L);
                  Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)" . ", 3L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)")", 1L);
                  IO_WriteNl(Tree_f);
                  IO_WriteS(Tree_f, (STRING)"yyWriteNl ;", 11L);
                  IO_WriteNl(Tree_f);
                }
              } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"    yyWriteEval ( TNode , \"", 27L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)":", 1L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMThree_GenEvaluator(W_6->Action);
                }
              } else {
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMThree_GenEvaluator(W_6->Action);
                }
              }
            }
            if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left) | SET_ELEM(Tree_First), W_6->Properties) && ((SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Virtual)) & W_6->Properties) == 0X0L) {
              if (Sets_IsElement(ORD('X'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"    yyWriteEval ( TNode , \"", 27L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMThree_GenEvaluator(W_6->Action);
                }
                IO_WriteNl(Tree_f);
                if (IN(Tree_Test, W_6->Properties)) {
                  IO_WriteS(Tree_f, (STRING)"    writeBOOLEAN(yyb) yyWriteNl;", 32L);
                  IO_WriteNl(Tree_f);
                } else if (W_6->Attribute->U_1.V_1.Kind == Tree_Child || W_6->Attribute->U_1.V_10.Attribute.Type == Tree_itTree) {
                  IO_WriteS(Tree_f, (STRING)"    write", 9L);
                  Tree_WI(Tree_itTree);
                  IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)")", 1L);
                } else {
                  IO_WriteS(Tree_f, (STRING)"    write", 9L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Type);
                  IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
                  Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                  IO_WriteS(Tree_f, (STRING)") yyWriteNl;", 12L);
                  IO_WriteNl(Tree_f);
                }
              } else if (Sets_IsElement(ORD('Y'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"    yyWriteEval ( TNode , \"", 27L);
                Tree_WI(W_6->Attribute->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
                IO_WriteNl(Tree_f);
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMThree_GenEvaluator(W_6->Action);
                }
              } else {
                if (W_6->Action != ADR(W_6->Action)) {
                  EvalMThree_GenEvaluator(W_6->Action);
                }
              }
            }
            if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Right) | SET_ELEM(Tree_First), W_6->Properties) && W_6->Attribute->U_1.V_9.Child.Partition <= W_6->Selector->U_1.V_9.Child.Class->U_1.V_5.Class.Visits) {
              if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
                IO_WriteS(Tree_f, (STRING)"    yyWriteVisit ( TNode , \"", 28L);
                Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
                IO_WriteS(Tree_f, (STRING)" ", 1L);
                Tree_WN((LONGINT)W_6->Attribute->U_1.V_9.Child.Partition);
                IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
                IO_WriteNl(Tree_f);
              }
              IO_WriteS(Tree_f, (STRING)"    yyVisit", 11L);
              Tree_WN((LONGINT)W_6->Attribute->U_1.V_9.Child.Partition);
              IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
              Tree_WI(W_6->Selector->U_1.V_9.Child.Name);
              IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
              IO_WriteNl(Tree_f);
            }
          }
        } EXIT_3:;
        if (Sets_IsElement(ORD('Z'), &Tree_Options) && IN(Tree_Trace, t->U_1.V_5.Class.Properties)) {
          IO_WriteS(Tree_f, (STRING)"    yyVisitParent ( TNode ) ;", 29L);
          IO_WriteNl(Tree_f);
        }
        EvalMThree_GenEvaluator(W_5->Next);
        return;
      }
    } EXIT_2:;
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_7 = &t->U_1.V_36.Assign;

      TreeMThree2_WriteLine(W_7->Pos);
      EvalMThree_GenEvaluator(W_7->Results);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      EvalMThree_GenEvaluator(W_7->Arguments);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_8 = &t->U_1.V_37.Copy;

      TreeMThree2_WriteLine(W_8->Pos);
      EvalMThree_GenEvaluator(W_8->Results);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      EvalMThree_GenEvaluator(W_8->Arguments);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_9 = &t->U_1.V_38.TargetCode;

      TreeMThree2_WriteLine(W_9->Pos);
      EvalMThree_GenEvaluator(W_9->Code);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_10 = &t->U_1.V_40.Check;

      TreeMThree2_WriteLine(W_10->Pos);
      if (W_10->Condition != Tree_NoTree) {
        if (Sets_IsElement(ORD('X'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"    yyb := ", 11L);
          EvalMThree_GenEvaluator(W_10->Condition);
          IO_WriteS(Tree_f, (STRING)" ; IF NOT yyb THEN ", 19L);
        } else {
          IO_WriteS(Tree_f, (STRING)"    IF NOT ( ", 13L);
          EvalMThree_GenEvaluator(W_10->Condition);
          IO_WriteS(Tree_f, (STRING)" ) THEN ", 8L);
        }
        EvalMThree_GenEvaluator(W_10->Statement);
        IO_WriteNl(Tree_f);
        if (W_10->Actions->U_1.V_1.Kind == Tree_Check) {
          IO_WriteS(Tree_f, (STRING)"    ELSE", 8L);
          IO_WriteNl(Tree_f);
          EvalMThree_GenEvaluator(W_10->Actions);
        }
        IO_WriteS(Tree_f, (STRING)"    END ;", 9L);
        IO_WriteNl(Tree_f);
      } else {
        if (Sets_IsElement(ORD('X'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"    yyb := FALSE ; ", 19L);
        }
        EvalMThree_GenEvaluator(W_10->Statement);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        EvalMThree_GenEvaluator(W_10->Actions);
      }
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_11 = &t->U_1.V_15.Designator;

      Attr = Tree_IdentifyAttribute(EvalMThree_Class, W_11->Selector);
      if (Attr != Tree_NoTree) {
        ChildsClass = Attr->U_1.V_9.Child.Class;
        Attr = Tree_IdentifyAttribute(ChildsClass, W_11->Attribute);
        if (!IN(Tree_Virtual, Attr->U_1.V_10.Attribute.Properties)) {
          IO_WriteS(Tree_f, (STRING)" TNode . ", 9L);
          Tree_WI(W_11->Selector);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(W_11->Attribute);
        }
      } else {
        Tree_WI(W_11->Selector);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        Tree_WI(W_11->Attribute);
      }
      EvalMThree_GenEvaluator(W_11->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_12 = &t->U_1.V_16.Ident;

      Attr = Tree_IdentifyAttribute(EvalMThree_Class, W_12->Attribute);
      if (Attr != Tree_NoTree) {
        if (!IN(Tree_Virtual, Attr->U_1.V_10.Attribute.Properties)) {
          IO_WriteS(Tree_f, (STRING)" TNode . ", 9L);
          Tree_WI(W_12->Attribute);
        }
      } else {
        Tree_WI(W_12->Attribute);
      }
      EvalMThree_GenEvaluator(W_12->Next);
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

              W_13->k = EvalMThree3_ToBit0(W_13->TheClass, (LONGINT)W_15->AttrIndex);
              if (IN(Tree_Synthesized, W_15->Properties)) {
                IO_WriteS(Tree_f, (STRING)"REMOTE_SYN (yyIsComp, ", 22L);
                Tree_WN(W_13->k);
                IO_WriteS(Tree_f, (STRING)", yyS", 5L);
                Tree_WN(W_13->k);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                EvalMThree_GenEvaluator(W_14->Designators);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WI(t->U_1.V_17.Remote.Type);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WI(W_14->Attribute);
                IO_WriteS(Tree_f, (STRING)")", 1L);
              } else if (IN(Tree_Inherited, W_15->Properties)) {
                IO_WriteS(Tree_f, (STRING)"REMOTE_INH (yyIsComp, ", 22L);
                Tree_WN(W_13->k);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                Tree_WN(W_13->k);
                IO_WriteS(Tree_f, (STRING)", ", 2L);
                EvalMThree_GenEvaluator(W_14->Designators);
                IO_WriteS(Tree_f, (STRING)" , ", 3L);
                Tree_WI(t->U_1.V_17.Remote.Type);
                IO_WriteS(Tree_f, (STRING)" , ", 3L);
                Tree_WI(W_14->Attribute);
                IO_WriteS(Tree_f, (STRING)" )", 2L);
              } else {
                EvalMThree_GenEvaluator(W_14->Designators);
                IO_WriteS(Tree_f, (STRING)" . ", 3L);
                Tree_WI(W_14->Attribute);
              }
            }
          }
        }
        EvalMThree_GenEvaluator(W_14->Next);
        return;
      }
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_16 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_16->Code);
      EvalMThree_GenEvaluator(W_16->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_17 = &t->U_1.V_19.Anys;

      EvalMThree_GenEvaluator(W_17->Layouts);
      EvalMThree_GenEvaluator(W_17->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_18 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_18->Code);
      EvalMThree_GenEvaluator(W_18->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void EvalMThree_BeginEvalMThree
# ifdef __STDC__
()
# else
()
# endif
{
}

void EvalMThree_CloseEvalMThree
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

void EvalMThree__init()
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
    TreeMThree2__init();
    EvalMThree3__init();
    Tree__init();

    EvalMThree_yyf = IO_StdOutput;
    EvalMThree_Exit = yyExit;
    EvalMThree_BeginEvalMThree();
  }
}
