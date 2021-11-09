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

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_TreeAda2
#include "TreeAda2.h"
#endif

Tree_tTree TreeAda2_Iterator;
IO_tFile TreeAda2_yyf;
PROC TreeAda2_Exit;

static Idents_tIdent iClassName;
static Strings_tString sBOOLEAN;
static Idents_tIdent iBOOLEAN;
static Tree_tTree RevChild;
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        struct {
            struct S_4 {
                Idents_tIdent LTypeId;
            } yyR1;
        } V_1;
    } U_1;
};
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void WriteNodeName ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void WriteNode ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void WriteNodeAttributes ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void Mark ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void WriteClassName ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void WriteAttributes ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void NodeKinds ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void WriteHtmlNodes ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void WriteHtmlCases ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


void TreeAda2_WriteLine
# ifdef __STDC__
(Positions_tPosition Line)
# else
(Line)
Positions_tPosition Line;
# endif
{
  if (Line.Line != 0) {
    IO_WriteS(Tree_f, (STRING)"-- From line ", 13L);
    Tree_WN((LONGINT)Line.Line);
    IO_WriteS(Tree_f, (STRING)" of file \"", 10L);
    Tree_WI(Line.File);
    IO_WriteS(Tree_f, (STRING)"\"", 1L);
    IO_WriteNl(Tree_f);
    if (Sets_IsElement(ORD('#'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"PRAGMA LINE ( ", 14L);
      Tree_WN((LONGINT)Line.Line);
      IO_WriteS(Tree_f, (STRING)" , \"", 4L);
      Tree_WI(Line.File);
      IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
      IO_WriteNl(Tree_f);
    }
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeAda2, routine ", 32L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeAda2_Exit)();
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

void TreeAda2_TreeIO
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
      register struct S_4 *W_1 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yAg *W_2 = &t->U_1.V_26.Ag;

        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('w'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"yyf : Text_Io . File_Type ; ", 28L);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        }
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD(','), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMark  ( Tree : ", 27L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyt : ", 8L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" := Tree ; ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"BEGIN ", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    IF yyt = ", 13L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)" THEN RETURN ; END IF ;", 23L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    yyt . ALL . yyHead . yyMark := yyt . ALL . yyHead . yyMark + 1 ; ", 69L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    IF yyt . ALL . yyHead . yyMark > 1 THEN RETURN ; END IF ; ", 62L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    CASE yyt . ALL . Kind IS", 28L);
          IO_WriteNl(Tree_f);
          Mark(W_2->Classes);
          IO_WriteS(Tree_f, (STRING)"    WHEN OTHERS => RETURN ; ", 28L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END CASE ; ", 15L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END LOOP ;", 12L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"END yyMark ;", 12L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD(';'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"yyInitTreeStoreSize : CONSTANT := 32 ; ", 39L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"TYPE yytTreeStore IS ARRAY ( INTEGER RANGE <> ) OF ", 51L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ; ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"TYPE yytTreeStorePtr IS ACCESS yytTreeStore ; ", 46L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"yyTreeStorePtr : yytTreeStorePtr := NULL ; ", 43L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"yyLabelCount : NATURAL := 0 ; ", 30L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"yyInitialTreeStoreCount : CONSTANT NATURAL := 2000 ; ", 53L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"yyRecursionLevel : NATURAL ; ", 29L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"FUNCTION yyMapToLabel ( yyTree : ", 33L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ) RETURN NATURAL ", 18L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyi : NATURAL ; ", 18L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  LNewTreeStorePtr : yytTreeStorePtr ; ", 39L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  FOR yyi IN 0 .. yyLabelCount - 1 ", 35L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  LOOP ", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    IF yyTreeStorePtr . ALL ( yyi ) = yyTree THEN RETURN yyi ; END IF ; ", 72L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END LOOP ; ", 13L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF yyTreeStorePtr = NULL ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  THEN ", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    yyTreeStorePtr := NEW yytTreeStore ( 0 .. yyInitialTreeStoreCount - 1 ) ; ", 78L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END IF ; ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF yyLabelCount = yyTreeStorePtr . ALL __ADA_TICK__ LENGTH ", 61L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  THEN ", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"     LNewTreeStorePtr ", 22L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"       := NEW yytTreeStore ( 0 .. yyTreeStorePtr . ALL __ADA_TICK__ LENGTH * 2 - 1 ) ;", 86L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"     LNewTreeStorePtr . ALL ( yyTreeStorePtr . ALL __ADA_TICK__ RANGE ) ", 72L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"       := yyTreeStorePtr . ALL ; ", 33L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"     yyTreeStorePtr := LNewTreeStorePtr ; ", 42L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END IF ; ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyi := yyLabelCount ; ", 24L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyTreeStorePtr . ALL ( yyi ) := yyTree ; ", 43L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyLabelCount := yyLabelCount + 1 ; ", 37L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  RETURN yyi ;", 14L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" END yyMapToLabel ; ", 20L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          if (Sets_IsElement(ORD('r'), &Tree_Options)) {
          }
        }
        if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteNl IS BEGIN Text_Io . Put_Line ( \"\" ) ; END yyWriteNl ; ", 73L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteSelector ( yys : STRING ) ", 43L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  SUBTYPE LPadSt IS STRING ( 1 .. 16 - yys __ADA_TICK__ LENGTH ) ; ", 67L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"BEGIN ", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( yys ) ; ", 26L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( LPadSt __ADA_TICK__ ( OTHERS => ' ' ) ) ; ", 60L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \" = \" ) ; ", 28L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"END yyWriteSelector ; ", 22L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"LittleEndian : BOOLEAN := TRUE ; ", 33L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"TYPE Byte IS RANGE 0 .. 255 ; ", 30L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"TYPE Bytes IS ARRAY ( INTEGER RANGE <> ) OF BYTE ; ", 51L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"PACKAGE BYTE_Text_Io IS NEW Text_Io . Integer_Io ( BYTE ) ; ", 60L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"", 1L);
          IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteHex ( yyx : Bytes ) ", 37L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS BEGIN", 8L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF LittleEndian", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  THEN", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    FOR yyi IN REVERSE yyx __ADA_TICK__ RANGE LOOP ", 51L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"      Byte_Text_Io . Put ( yyx ( yyi ) , 2 , 16 ) ; ", 52L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END LOOP ; ", 15L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    FOR yyi IN yyx __ADA_TICK__ RANGE LOOP ", 43L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"      Byte_Text_Io . Put ( yyx ( yyi ) , 2 , 16 ) ; ", 52L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END LOOP ; ", 15L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END IF ; ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"END yyWriteHex ;", 16L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD('o'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"SUBTYPE ", 8L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)"Bytes IS Bytes ( 1 .. ", 22L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" __ADA_TICK__ Size / 8 ) ; ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"FUNCTION ", 9L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)"ToBytes IS NEW Unchecked_Conversion ", 36L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  ( ", 4L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" , ", 3L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)"Bytes ) ; ", 10L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteAdr ( yyt : ", 29L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS BEGIN ", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)" THEN ", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   Text_Io . Put (\"", 19L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  ELSE ", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   yyWriteHex ( ", 16L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)"ToBytes ( yyt ) ) ;", 19L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END IF ; ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyWriteNl ;", 13L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"END yyWriteAdr ; ", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          if (Tree_itTree <= Semantics_TypeCount) {
            Sets_Exclude(&Tree_TypeNames, (Sets_tElement)Tree_itTree);
          }
          while (!Sets_IsEmpty(Tree_TypeNames)) {
            W_1->LTypeId = Sets_Extract(&Tree_TypeNames);
            IO_WriteS(Tree_f, (STRING)"SUBTYPE ", 8L);
            Tree_WI(W_1->LTypeId);
            IO_WriteS(Tree_f, (STRING)"Bytes IS Bytes ( 1 .. ", 22L);
            Tree_WI(W_1->LTypeId);
            IO_WriteS(Tree_f, (STRING)" __ADA_TICK__ Size / 8 ) ; ", 27L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)"FUNCTION ", 9L);
            Tree_WI(W_1->LTypeId);
            IO_WriteS(Tree_f, (STRING)"ToBytes IS NEW Unchecked_Conversion ", 36L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)"  ( ", 4L);
            Tree_WI(W_1->LTypeId);
            IO_WriteS(Tree_f, (STRING)" , ", 3L);
            Tree_WI(W_1->LTypeId);
            IO_WriteS(Tree_f, (STRING)"Bytes ) ; ", 10L);
            IO_WriteNl(Tree_f);
            IO_WriteNl(Tree_f);
          }
        }
        if (Sets_IsElement(ORD('o'), &Tree_Options)) {
          Tree_ForallClassesExtensionsFirst(W_2->Classes, (Tree_ProcOfT)WriteNode);
          IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"Node ", 5L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" ( Tree : ", 10L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS BEGIN", 8L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF Tree = ", 12L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)" THEN ", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"", 21L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl ; RETURN ; ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END IF ; ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  CASE Tree . ALL . Kind IS ", 28L);
          IO_WriteNl(Tree_f);
          WriteNodeName(W_2->Classes);
          IO_WriteS(Tree_f, (STRING)"  WHEN OTHERS => NULL ; ", 24L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END CASE ;", 12L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"END Write", 9L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"Node ;", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        }
        if (Sets_IsElement(ORD('^'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"FUNCTION yyNodeTag ( yyt : ", 27L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ) RETURN STRING ", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS BEGIN ", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF yyt = NULL ", 16L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  THEN RETURN \"NIL\" ; ", 22L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  ELSE ", 7L);
          IO_WriteS(Tree_f, (STRING)"    RETURN \"Node\" ", 18L);
          IO_WriteS(Tree_f, (STRING)"& INTEGER __ADA_TICK__ IMAGE ( yyMapToLabel ( yyt ) ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END IF ; ", 11L);
          IO_WriteS(Tree_f, (STRING)" END yyNodeTag ; ", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"FUNCTION yyNodeKind ( yyt : ", 28L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ) RETURN STRING ", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS BEGIN", 8L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
          Tree_WI(Tree_iNoTree);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  THEN ", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    RETURN \"NIL\"  ; ", 20L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    CASE yyt . ALL . Kind IS ", 29L);
          IO_WriteNl(Tree_f);
          NodeKinds(W_2->Classes);
          IO_WriteS(Tree_f, (STRING)"    WHEN OTHERS => ", 19L);
          IO_WriteS(Tree_f, (STRING)"      RETURN \"<Unknown>\" ; ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END CASE ; ", 15L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   END IF ; ", 12L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END yyNodeKind ; ", 19L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"Html ", 5L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  ( f : Text_Io . File_Type ; Tree : ", 37L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ; Title : STRING := \"\" ", 24L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  ; SuppressNullFields : BOOLEAN := FALSE ) ", 44L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"IS ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IndentString : CONSTANT STRING := \"  \" ; ", 43L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  PROCEDURE WriteChildOrLink ", 29L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    ( Name , TypeName : STRING ; Value : ", 41L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ; IsLink : BOOLEAN := FALSE ) ", 31L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   LNodeTag : STRING := yyNodeTag ( Value ) ; ", 46L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   IF Value /= NULL OR NOT SuppressNullFields ", 46L);
          IO_WriteS(Tree_f, (STRING)"   THEN ", 8L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( IndentString ) ; ", 37L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( Name ) ; ", 29L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \" : \" ) ; ", 30L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( TypeName ) ; ", 33L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    IF IsLink ", 14L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    THEN ", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"      Text_Io . Put ( \" LINK\" ) ; ", 34L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END IF ; ", 13L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \" = \" ) ; ", 30L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"<a href=__ADA_DQUOTE_IN_STRING__#\" ) ; ", 60L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( LNodeTag ) ; ", 33L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"__ADA_DQUOTE_IN_STRING__>REF \" ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( LNodeTag ) ; ", 33L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"(\" ) ; ", 28L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    yyWriteAdr ( Value ) ; ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \")\" ) ; ", 28L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( yyNodeKind ( Value ) ) ; ", 45L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"</a>\" ) ; ", 31L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    yyWriteNl ; ", 16L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   END IF ; ", 12L);
          IO_WriteS(Tree_f, (STRING)"  END WriteChildOrLink ; ", 25L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  PROCEDURE WriteBOOLEANAttribute ", 34L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    ( Name : STRING ; Value : BOOLEAN ) ", 40L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   IF Value OR NOT SuppressNullFields ", 38L);
          IO_WriteS(Tree_f, (STRING)"   THEN ", 8L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( IndentString ) ; ", 37L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( Name ) ; ", 29L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \" : \" ) ; ", 30L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"BOOLEAN = \" ) ; ", 37L);
          IO_WriteS(Tree_f, (STRING)"    writeBOOLEAN ( Value ) ", 27L);
          IO_WriteS(Tree_f, (STRING)"    yyWriteNl  ; ", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   END IF ; ", 12L);
          IO_WriteS(Tree_f, (STRING)"  END WriteBOOLEANAttribute ; ", 30L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          Tree_ForallClassesExtensionsFirst(W_2->Classes, (Tree_ProcOfT)WriteHtmlNodes);
          IO_WriteS(Tree_f, (STRING)" PROCEDURE WriteHtmlRecurse ( Tree : ", 37L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" IS ", 4L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   yyt : ", 9L);
          Tree_WI(Tree_itTree);
          IO_WriteS(Tree_f, (STRING)" := Tree ; ", 11L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" BEGIN ", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   LOOP ", 8L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    IF yyt = ", 13L);
          Tree_WI(Tree_iNoTree);
          IO_WriteS(Tree_f, (STRING)" OR ELSE yyt . ALL . yyHead . yyMark = 0", 40L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    THEN ", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"     EXIT ; ", 12L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    ELSE ", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"     yyt . ALL . yyHead . yyMark := 0 ; ", 40L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"     CASE yyt . ALL . Kind IS ", 30L);
          IO_WriteNl(Tree_f);
          WriteHtmlCases(W_2->Classes);
          IO_WriteS(Tree_f, (STRING)"     WHEN OTHERS => EXIT ; ", 27L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"     END CASE ; ", 16L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END IF ; ", 13L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   END LOOP ; ", 14L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" END WriteHtmlRecurse ; ", 24L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" BEGIN -- Write", 15L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"Html ", 5L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Set_Output ( f ) ; ", 31L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  IF yyRecursionLevel = 0 THEN yyLabelCount := 0 ; END IF ; ", 60L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyRecursionLevel := yyRecursionLevel + 1 ; ", 45L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyMark ( Tree ) ; ", 20L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"<html> \" ) ; yyWriteNl  ; ", 45L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"<head>\" ) ; yyWriteNl  ; ", 44L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"<title>\" ) ; ", 32L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"Tree \"\"\" ) ; ", 32L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( Title ) ; ", 28L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"\"\"</title>\" ) ; yyWriteNl  ; ", 48L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"</head>\" ) ; yyWriteNl  ; ", 45L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"<body>\" ) ; yyWriteNl  ; ", 44L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"<pre>\" ) ; yyWriteNl  ; ", 43L);
          IO_WriteS(Tree_f, (STRING)"  yyWriteNl  ; ", 15L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  WriteHtmlRecurse ( Tree ) ; ", 30L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"</pre>\" ) ; yyWriteNl  ; ", 44L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"</body>\" ) ; yyWriteNl  ; ", 45L);
          IO_WriteS(Tree_f, (STRING)"  Text_Io . Put ( \"</html>\" ) ; yyWriteNl  ; ", 45L);
          IO_WriteS(Tree_f, (STRING)"  yyRecursionLevel := yyRecursionLevel - 1;", 43L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" END Write", 10L);
          Tree_WI(Tree_iModule);
          IO_WriteS(Tree_f, (STRING)"Html ; ", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
        }
        if (Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options)) {
        }
        if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        }
        if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        }
        return;
      }
    }
  }
}

void TreeAda2_TreeIOInit
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

      if (Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options)) {
      }
      return;
    }
  }
}

static void WriteNodeName
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

      WriteNodeName(W_4->Extensions);
      if ((Tree_NoCodeClass & W_4->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"  WHEN ", 7L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"Node of Kind ", 34L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)":\" ) ; yyWriteNl ; ", 19L);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_4->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"    yyyWriteNode", 16L);
          Tree_WI(W_4->Name);
          IO_WriteS(Tree_f, (STRING)" ( Tree ) ;", 11L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteNl(Tree_f);
      }
      WriteNodeName(W_4->Next);
      return;
    }
  }
}

static void WriteNode
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
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_5->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_5->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyyWriteNode", 22L);
        Tree_WI(W_5->Name);
        IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS BEGIN", 10L);
        IO_WriteNl(Tree_f);
        WriteNodeAttributes(t);
        IO_WriteS(Tree_f, (STRING)"    NULL ; ", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END yyyWriteNode", 18L);
        Tree_WI(W_5->Name);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void WriteNodeAttributes
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
  case Tree_NoClass:;
    return;
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_6 = &t->U_1.V_5.Class;

      WriteNodeAttributes(W_6->BaseClass);
      if ((Tree_NoCodeClass & W_6->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_6->Properties) != 0X0L) {
        iClassName = W_6->Name;
        Tree_ForallAttributes(W_6->Attributes, (Tree_ProcOfT)WriteNodeAttributes);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_7 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"    yyWriteSelector ( \"", 23L);
      Tree_WI(W_7->Name);
      IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    yyWriteAdr ( yyt . ALL . ", 29L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_7->Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_8 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_8->Properties) == 0X0L) {
        if (IN(Tree_Link, W_8->Properties)) {
          IO_WriteS(Tree_f, (STRING)"    yyWriteSelector ( \"", 23L);
          Tree_WI(W_8->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    yyWriteAdr ( yyt . ALL . ", 29L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(W_8->Name);
          IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"    yyWriteSelector ( \"", 23L);
          Tree_WI(W_8->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ; write", 11L);
          Tree_WI(W_8->Type);
          IO_WriteS(Tree_f, (STRING)"      ( yyt . ALL . ", 20L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(W_8->Name);
          IO_WriteS(Tree_f, (STRING)" ) yyWriteNl  ; ", 16L);
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

static void Mark
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
      register Tree_yClass *W_9 = &t->U_1.V_5.Class;

      Mark(W_9->Extensions);
      if ((Tree_NoCodeClass & W_9->Properties) == 0X0L && IN(Tree_HasChildren, W_9->Properties)) {
        IO_WriteS(Tree_f, (STRING)"    WHEN ", 9L);
        Tree_WI(W_9->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteNl(Tree_f);
        TreeAda2_GetIterator(t);
        iClassName = W_9->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Mark);
        if (TreeAda2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"      RETURN ; ", 15L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"      yyt := yyt . ALL . ", 25L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ; ", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      Mark(W_9->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_10 = &t->U_1.V_9.Child;

      if (t != TreeAda2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"      yyMark ( yyt . ALL . ", 27L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_11 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Link, W_11->Properties)) {
        IO_WriteS(Tree_f, (STRING)"      yyMark ( yyt . ALL . ", 27L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_11->Name);
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

static void WriteClassName
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
      register Tree_yClass *W_12 = &t->U_1.V_5.Class;

      WriteClassName(W_12->Extensions);
      if ((Tree_NoCodeClass & W_12->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"   | ", 5L);
        Tree_WI(W_12->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) => ", 14L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_12->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"       yWrite", 13L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)" ( TNode ) ; ", 13L);
          IO_WriteNl(Tree_f);
          TreeAda2_GetIterator(t);
          if (TreeAda2_Iterator == Tree_NoTree) {
            IO_WriteS(Tree_f, (STRING)"       EXIT ;", 13L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"       yyIndentSelector ( \"", 27L);
            Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
            IO_WriteS(Tree_f, (STRING)"       yyt := TNode . ", 22L);
            Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)" ;", 2L);
            IO_WriteNl(Tree_f);
          }
        } else {
          IO_WriteS(Tree_f, (STRING)"       Text_Io . Put (\"", 23L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl  ; EXIT ;", 25L);
          IO_WriteNl(Tree_f);
        }
      }
      WriteClassName(W_12->Next);
      return;
    }
  }
}

static void WriteAttributes
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
      register Tree_yClass *W_13 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_13->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_13->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yWrite", 16L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Text_Io . Put (\"", 18L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl  ;", 18L);
        IO_WriteNl(Tree_f);
        TreeAda2_GetIterator(t);
        iClassName = W_13->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)WriteAttributes);
        IO_WriteS(Tree_f, (STRING)" END yWrite", 11L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_14 = &t->U_1.V_9.Child;

      if (t != TreeAda2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"  yyIndentSelectorTree ( \"", 26L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)"\" , yyt . ", 10L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_15 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_15->Properties) == 0X0L) {
        if (IN(Tree_Link, W_15->Properties)) {
          IO_WriteS(Tree_f, (STRING)"  yyIndentSelectorTree ( \"", 26L);
          Tree_WI(W_15->Name);
          IO_WriteS(Tree_f, (STRING)"\" , yyt . ", 10L);
          Tree_WI(W_15->Name);
          IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"  yyIndentSelector ( \"", 22L);
          Tree_WI(W_15->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
          IO_WriteS(Tree_f, (STRING)"write", 5L);
          Tree_WI(W_15->Type);
          IO_WriteS(Tree_f, (STRING)" ( yyt . ", 9L);
          Tree_WI(W_15->Name);
          IO_WriteS(Tree_f, (STRING)" ) yyWriteNl  ;", 15L);
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

static void NodeKinds
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_16 = &t->U_1.V_5.Class;

      NodeKinds(W_16->Extensions);
      if ((Tree_NoCodeClass & W_16->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"    WHEN ", 9L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)" => RETURN \"", 12L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)"\" ; ", 4L);
        IO_WriteNl(Tree_f);
      }
      NodeKinds(W_16->Next);
      return;
    }
  }
}

static void WriteHtmlNodes
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
        IO_WriteS(Tree_f, (STRING)"  PROCEDURE Write", 17L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)"Html ( TNode : tAst ) ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    LNodeTag : STRING := yyNodeTag ( TNode ) ; ", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"<a name=__ADA_DQUOTE_IN_STRING__\" ) ; ", 59L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( LNodeTag ) ; ", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"__ADA_DQUOTE_IN_STRING__>DEF \" ) ; ", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( LNodeTag ) ; ", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \"(\" ) ; ", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteAdr ( TNode ) ; ", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( \")", 22L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)"</a>\" ) ; ", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl ; ", 16L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_17->Properties) != 0X0L) {
          iClassName = W_17->Name;
          Tree_ForallAttributes(t, (Tree_ProcOfT)WriteHtmlNodes);
        }
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl ; ", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Write", 11L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)"Html ; ", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_18 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"    WriteChildOrLink ( \"", 24L);
      Tree_WI(W_18->Name);
      IO_WriteS(Tree_f, (STRING)"\" , \"", 5L);
      Tree_WI(W_18->Type);
      IO_WriteS(Tree_f, (STRING)"\" , TNode . ALL . ", 18L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_18->Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_19 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_19->Properties) == 0X0L) {
        if (IN(Tree_Link, W_19->Properties)) {
          IO_WriteS(Tree_f, (STRING)"    WriteChildOrLink ( \"", 24L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)"\" , \"", 5L);
          Tree_WI(W_19->Type);
          IO_WriteS(Tree_f, (STRING)"\" , TNode . ALL . ", 18L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)" , TRUE ) ; ", 12L);
          IO_WriteNl(Tree_f);
        } else if (W_19->Type == iBOOLEAN) {
          IO_WriteS(Tree_f, (STRING)"    WriteBOOLEANAttribute ( \"", 29L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)"\" , TNode . ALL . ", 18L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( IndentString & \"", 36L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)" : ", 3L);
          Tree_WI(W_19->Type);
          IO_WriteS(Tree_f, (STRING)" = \" ) ; ", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    write", 9L);
          Tree_WI(W_19->Type);
          IO_WriteS(Tree_f, (STRING)" ( TNode . ALL . ", 17L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)" . ", 3L);
          Tree_WI(W_19->Name);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    yyWriteNl ; ", 16L);
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

static void WriteHtmlCases
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

      WriteHtmlCases(W_20->Extensions);
      if ((Tree_NoCodeClass & W_20->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"     WHEN ", 10L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"         Write", 14L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)"Html ( yyt ) ; ", 15L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_20->Properties) != 0X0L) {
          TreeAda2_GetIterator(t);
          iClassName = W_20->Name;
          Tree_ForallAttributes(t, (Tree_ProcOfT)WriteHtmlCases);
          if (TreeAda2_Iterator == Tree_NoTree) {
            IO_WriteS(Tree_f, (STRING)"         EXIT ; ", 16L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"         yyt := yyt . ALL . ", 28L);
            Tree_WI(iClassName);
            IO_WriteS(Tree_f, (STRING)" . ", 3L);
            Tree_WI(TreeAda2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)" ; ", 3L);
            IO_WriteNl(Tree_f);
          }
        }
      }
      WriteHtmlCases(W_20->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_21 = &t->U_1.V_9.Child;

      if (t != TreeAda2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"         WriteHtmlRecurse ( yyt . ALL . ", 40L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_21->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_22 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Link, W_22->Properties)) {
        IO_WriteS(Tree_f, (STRING)"         WriteHtmlRecurse ( yyt . ALL . ", 40L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_22->Name);
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

void TreeAda2_GetIterator
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
      register Tree_yClass *W_23 = &t->U_1.V_5.Class;

      TreeAda2_Iterator = Tree_NoTree;
      RevChild = Tree_NoTree;
      Tree_ForallAttributes(t, (Tree_ProcOfT)TreeAda2_GetIterator);
      if (RevChild != Tree_NoTree) {
        TreeAda2_Iterator = RevChild;
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_24 = &t->U_1.V_9.Child;

      TreeAda2_Iterator = t;
      if (IN(Tree_Reverse, W_24->Properties)) {
        RevChild = t;
      }
      return;
    }
    break;
  default :
    break;
  }
}

void TreeAda2_BeginTreeAda2
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_ArrayToString((STRING)"BOOLEAN", 7L, &sBOOLEAN);
  iBOOLEAN = Idents_MakeIdent(&sBOOLEAN);
}

void TreeAda2_CloseTreeAda2
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

void TreeAda2__init()
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
    Idents__init();
    Strings__init();
    IO__init();
    Sets__init();
    Idents__init();
    Positions__init();
    Semantics__init();
    Tree__init();

    TreeAda2_yyf = IO_StdOutput;
    TreeAda2_Exit = yyExit;
    TreeAda2_BeginTreeAda2();
  }
}
