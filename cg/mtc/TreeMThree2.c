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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_TreeMThree2
#include "TreeMThree2.h"
#endif

Tree_tTree TreeMThree2_Iterator;
IO_tFile TreeMThree2_yyf;
PROC TreeMThree2_Exit;

static Idents_tIdent iClassName;
static Strings_tString sBOOLEAN;
static Idents_tIdent iBOOLEAN;
static Tree_tTree RevChild;
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
static void WriteNodeName ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void WriteNode ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void Mark ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void WriteClassName ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void WriteAttributes ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void NodeKinds ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void WriteHtmlNodes ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void WriteHtmlCases ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


void TreeMThree2_WriteLine
# ifdef __STDC__
(Positions_tPosition Line)
# else
(Line)
Positions_tPosition Line;
# endif
{
  if (Line.Line != 0) {
    IO_WriteS(Tree_f, (STRING)"(* line ", 8L);
    Tree_WN((LONGINT)Line.Line);
    IO_WriteS(Tree_f, (STRING)" \"", 2L);
    Tree_WI(Line.File);
    IO_WriteS(Tree_f, (STRING)"\" *)", 4L);
    IO_WriteNl(Tree_f);
    if (Sets_IsElement(ORD('#'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"<*LINE ", 7L);
      Tree_WN((LONGINT)Line.Line);
      IO_WriteS(Tree_f, (STRING)" \"", 2L);
      Tree_WI(Line.File);
      IO_WriteS(Tree_f, (STRING)"\" *>", 4L);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeMThree2, routine ", 35L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeMThree2_Exit)();
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

void TreeMThree2_TreeIO
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
      if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"VAR yyf        : Wr . T ;", 25L);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
      }
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD(','), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMark  (yyt : ", 25L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN RETURN; END;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   INC ( yyt . yyHead . yyMark ) ;", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt . yyHead . yyMark > 1 THEN RETURN; END;", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   TYPECASE yyt OF", 18L);
        IO_WriteNl(Tree_f);
        Mark(W_1->Classes);
        IO_WriteS(Tree_f, (STRING)"   ELSE RETURN ;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyMark ;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD(';'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"CONST yyInitTreeStoreSize      = 32 ;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE yytTreeStore = ARRAY OF ", 29L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyTreeStorePtr     : REF yytTreeStore ;", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyLabelCount       : CARDINAL ;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyRecursionLevel   : CARDINAL ;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMapToLabel ( yyTree : ", 34L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) : CARDINAL", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yyi       : CARDINAL ;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR LNewTreeStorePtr : REF yytTreeStore ;", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO yyLabelCount - 1 DO", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyTreeStorePtr ^ [ yyi ] = yyTree THEN RETURN yyi ; END ;", 63L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyLabelCount = NUMBER ( yyTreeStorePtr ^ ) THEN", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     LNewTreeStorePtr := NEW ( REF yytTreeStore , NUMBER ( yyTreeStorePtr ^ ) * 2 ) ;", 85L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     SUBARRAY ( LNewTreeStorePtr ^ , 0 , NUMBER ( yyTreeStorePtr ^ ) ) := yyTreeStorePtr ^ ; ", 93L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     yyTreeStorePtr := LNewTreeStorePtr ; ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyi := yyLabelCount ;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyTreeStorePtr ^ [ yyi ] := yyTree ;", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC ( yyLabelCount ) ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyi ;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyMapToLabel;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        }
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('^'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteNl ( ) = BEGIN Wr . PutText ( yyf , Wr . EOL ) ; END yyWriteNl ;", 81L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteSelector ( yys : TEXT ) ", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN Wr . PutText  ( yyf , yys ) ; ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( yyf , Fmt . Pad ( \"\" , MAX ( 0 , 16 - Text . Length ( yys ) ) ) ) ;", 85L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText (yyf, \" = \" ) ;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteSelector ;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR LittleEndian := TRUE ; ", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteHex ( VAR yyx : ARRAY OF CHAR ) ", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF LittleEndian", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  THEN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   FOR yyi := NUMBER ( yyx ) - 1 TO 0 BY - 1 DO", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Fmt . Pad ( Fmt . Int ( ORD ( yyx [ yyi ] ) , 16 ) , 2 , '0' ) ) ;", 91L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   FOR yyi := 0 TO NUMBER ( yyx ) - 1 DO", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Fmt . Pad ( Fmt . Int ( ORD ( yyx [ yyi ] ) , 16 ) , 2 , '0' ) ) ;", 91L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteHex ;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteAdr ( yyt : ", 29L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( yyf , \"", 25L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteHex ( LOOPHOLE ( yyt , ARRAY [ 0 .. 3 ] OF CHAR ) ) ;", 63L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyWriteNl ( ) ;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteAdr;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_1->Classes, (Tree_ProcOfT)WriteNode);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node ( f : Wr . T ; Tree : ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := f ;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF Tree = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( yyf , \"", 25L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl ( ) ; RETURN ;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  TYPECASE Tree OF", 18L);
        IO_WriteNl(Tree_f);
        WriteNodeName(W_1->Classes);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Write", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node ;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"VAR yyIndentLevel      : INTEGER ;", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyActualIndent , yyIndentQuotient , yyIndentRemainder : INTEGER ;", 69L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"CONST yyIndentFactor = 20 ; ", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yySetIndentInfo ( ) ", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyIndentQuotient := yyIndentLevel DIV yyIndentFactor ; ", 58L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyIndentRemainder := yyIndentLevel MOD yyIndentFactor ; ", 59L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyActualIndent ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     := 10 * ORD ( yyIndentQuotient > 0 ) ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        + yyIndentRemainder ", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END yySetIndentInfo ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( f : Wr . T ; Tree : ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yySaveLevel : INTEGER ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := f ;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyRecursionLevel = 0 THEN yyLabelCount := 0 END ;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC ( yyRecursionLevel ) ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark ( Tree ) ;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySaveLevel := yyIndentLevel ;", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIndentLevel := 0 ;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySetIndentInfo ( ) ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyWrite", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( Tree );", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIndentLevel := yySaveLevel ;", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySetIndentInfo ( ) ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  DEC ( yyRecursionLevel ) ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Write", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIndentSelector ( yys : TEXT )", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN ", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyIndentQuotient > 0 ", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   THEN Wr . PutChar ( yyf , '(' ) ; Wr . PutChar ( yyf , '*' ) ;", 65L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     Wr . PutText ( yyf , Fmt . Pad ( Fmt . Int ( yyIndentQuotient * yyIndentFactor ) , 6 ) ) ; ", 96L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     Wr . PutChar ( yyf , '*' ) ; Wr . PutChar ( yyf , ')' ) ;", 62L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ; ", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( yyf , Fmt . Pad ( \"\" , yyIndentRemainder ) ) ;", 64L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteSelector ( yys ) ; ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyIndentSelector ;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIndentSelectorTree ( yys : TEXT ; yyt : ", 52L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN yyIndentSelector  ( yys ) ; write", 40L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (yyt) END yyIndentSelectorTree ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_1->Classes, (Tree_ProcOfT)WriteAttributes);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWrite", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR yyLevel : CARDINAL ;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyLevel := yyIndentLevel ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \" ", 27L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl ( ) ; EXIT ; ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSIF yyt . yyHead . yyMark = 0 THEN", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutChar ( yyf, '^') ;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText  ( yyf , Fmt . Int ( yyMapToLabel ( yyt ) ) ) ; yyWriteNl ( ) ; EXIT ;", 87L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSIF yyt . yyHead . yyMark > 1 THEN", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl ( ) ;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Fmt . Pad ( Fmt . Int ( yyMapToLabel ( yyt ) ) , 6 ) ) ;", 81L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutChar ( yyf , ':') ;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Fmt . Pad ( \"\" , MAX ( 0 , yyActualIndent - 7 ) ) ) ;", 78L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSE", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutChar ( yyf , ' ' ) ;", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyt . yyHead . yyMark := 0 ;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   INC ( yyIndentLevel , 2 ) ;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yySetIndentInfo ( ) ; ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   TYPECASE yyt OF", 18L);
        IO_WriteNl(Tree_f);
        WriteClassName(W_1->Classes);
        IO_WriteS(Tree_f, (STRING)"   ELSE EXIT ;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ;", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIndentLevel := yyLevel ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySetIndentInfo ( ) ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWrite", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('^'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyNodeTag ( yyt : ", 28L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) : TEXT ", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   RETURN \"Node\" & Fmt . Int ( yyMapToLabel ( yyt ) ) ", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyNodeTag ; ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" PROCEDURE yyNodeKind ( yyt : ", 30L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ) : TEXT ", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   THEN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN \"NIL\" ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSE", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    TYPECASE yyt OF", 19L);
        IO_WriteNl(Tree_f);
        NodeKinds(W_1->Classes);
        IO_WriteS(Tree_f, (STRING)"    ELSE ", 9L);
        IO_WriteS(Tree_f, (STRING)"     RETURN \"<Unknown>\" ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END (* TYPECASE *) ", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END (* IF *) ", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END yyNodeKind ; ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Html ", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( f : Wr . T ; Tree : ", 24L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; Title : TEXT := \"\" ", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; SuppressNullFields : BOOLEAN := FALSE ) ", 44L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=CONST IndentString = \"  \" ; ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" PROCEDURE WriteChildOrLink ", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ( Name , Type : TEXT ; Value : ", 34L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ; IsLink : BOOLEAN := FALSE ) ", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =VAR LNodeTag : TEXT ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF Value # NIL OR NOT SuppressNullFields ", 44L);
        IO_WriteS(Tree_f, (STRING)"   THEN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , IndentString ) ; ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Name ) ; ", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \" : \" ) ; ", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Type ) ; ", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF IsLink  ", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    THEN ", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Wr . PutText ( yyf , \" LINK\" ) ; ", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END (* IF *) ; ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \" = \" ) ; ", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    LNodeTag := yyNodeTag ( Value ) ; ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"<a href=\\\"#\" ) ; ", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , LNodeTag ) ; ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"\\\">REF \" ) ; ", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , LNodeTag ) ; ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"(\" ) ; ", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteHex ( LOOPHOLE ( Value , ARRAY [ 0 .. 3 ] OF CHAR ) ) ; ", 67L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \")\" ) ; ", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , yyNodeKind ( Value ) ) ; ", 50L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"</a>\" ) ; ", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl ( ) ; ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END (* IF *) ", 16L);
        IO_WriteS(Tree_f, (STRING)"  END WriteChildOrLink ; ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" PROCEDURE WriteBOOLEANAttribute ", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ( Name : TEXT ; Value : BOOLEAN ) ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF Value OR NOT SuppressNullFields ", 38L);
        IO_WriteS(Tree_f, (STRING)"   THEN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , IndentString ) ; ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , Name ) ; ", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \" : \" ) ; ", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"BOOLEAN = \" ) ; ", 42L);
        IO_WriteS(Tree_f, (STRING)"    writeBOOLEAN ( Value ) ", 27L);
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl ( ) ; ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END (* IF *) ", 16L);
        IO_WriteS(Tree_f, (STRING)"  END WriteBOOLEANAttribute ; ", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClassesExtensionsFirst(W_1->Classes, (Tree_ProcOfT)WriteHtmlNodes);
        IO_WriteS(Tree_f, (STRING)" PROCEDURE WriteHtmlRecurse ( yyt : ", 36L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" =BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF yyt = ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" OR yyt . yyHead . yyMark = 0", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    THEN", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     EXIT", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSE", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     yyt . yyHead . yyMark := 0 ;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     TYPECASE yyt OF", 20L);
        IO_WriteNl(Tree_f);
        WriteHtmlCases(W_1->Classes);
        IO_WriteS(Tree_f, (STRING)"     ELSE EXIT", 14L);
        IO_WriteS(Tree_f, (STRING)"     END (* TYPECASE *)", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END (* IF *)", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END (* LOOP *)", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END WriteHtmlRecurse ;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN (* Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Html *)", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := f ;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyRecursionLevel = 0 THEN yyLabelCount := 0 END ;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC ( yyRecursionLevel ) ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark ( Tree ) ;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"<html> \" ) ; yyWriteNl ( ) ; ", 53L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"<head>\" ) ; yyWriteNl ( ) ; ", 52L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"<title>\" ) ; ", 37L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"Tree \\\"\" ) ; ", 37L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , Title ) ; ", 33L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"\\\"</title>\" ) ; yyWriteNl ( ) ; ", 56L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"</head>\" ) ; yyWriteNl ( ) ; ", 53L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"<body>\" ) ; yyWriteNl ( ) ; ", 52L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"<pre>\" ) ; yyWriteNl ( ) ; ", 51L);
        IO_WriteS(Tree_f, (STRING)"  yyWriteNl ( ) ; ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  WriteHtmlRecurse ( Tree );", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"</pre>\" ) ; yyWriteNl ( ) ; ", 52L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"</body>\" ) ; yyWriteNl ( ) ; ", 53L);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"</html>\" ) ; yyWriteNl ( ) ; ", 53L);
        IO_WriteS(Tree_f, (STRING)"  DEC ( yyRecursionLevel ) ;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Write", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Html ;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"TYPE AtomSpecialTyp = Pickle . Special OBJECT", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  OVERRIDES", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    write := WriteAtom", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; read := ReadAtom", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE WriteAtom ( Self : AtomSpecialTyp ; r : REFANY ; wr : Pickle . Writer )", 81L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RAISES { Pickle . Error , Wr . Failure , Thread . Alerted }", 61L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"= VAR LText : TEXT := Atom . ToText ( NARROW ( r , Atom . T ) )", 63L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      (* Why does M3 accept this without the NARROW? *) ", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"; VAR LLength : INTEGER := Text . Length ( LText )", 50L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"; BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    wr . writeInt ( LLength ) ", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; FOR i := 0 TO LLength ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    DO", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Wr . PutChar ( wr . wr , Text . GetChar ( LText , i ) )", 61L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END (* FOR *) ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END WriteAtom ;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE ReadAtom ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ( Self : AtomSpecialTyp ; rd : Pickle . Reader ; id : Pickle . RefID ) ", 73L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  : REFANY", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RAISES { Pickle . Error , Rd . EndOfFile , Rd . Failure , Thread . Alerted }", 78L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"= VAR LLength : INTEGER := rd . readInt ( ) ", 44L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"; VAR LChars : REF ARRAY OF CHAR := NEW ( REF ARRAY OF CHAR , LLength ) ", 72L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"; BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    FOR i := 0 TO LLength ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    DO ", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      LChars ^ [ i ] := Rd . GetChar ( rd . rd )", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END (* FOR *) ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ; RETURN Atom . FromText ( Text . FromChars ( LChars ^ ) )", 60L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END ReadAtom ;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Put", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( f : Wr . T ; Tree : ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   Pickle . Write ( f , Tree )", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Put", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Get", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ( f : Rd . T ) : ", 18L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"= BEGIN", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN NARROW ( Pickle . Read ( f ) , ", 42L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Get", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

void TreeMThree2_TreeIOInit
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

      if (Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"Pickle . RegisterSpecial ( NEW ( AtomSpecialTyp , sc := TYPECODE ( Atom . T ) ) ) ;", 83L);
        IO_WriteNl(Tree_f);
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
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_3 = &t->U_1.V_5.Class;

      WriteNodeName(W_3->Extensions);
      if ((Tree_NoCodeClass & W_3->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"   | ", 5L);
        Tree_WI(W_3->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) =>", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        Wr . PutText ( yyf , \"", 30L);
        Tree_WI(W_3->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl ( ) ;", 21L);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_3->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"        yyyWriteNode", 20L);
          Tree_WI(W_3->Name);
          IO_WriteS(Tree_f, (STRING)" ( TNode ) ;", 12L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteNl(Tree_f);
      }
      WriteNodeName(W_3->Next);
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
  struct S_6 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_4 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_4->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_4->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyyWriteNode", 22L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        if (W_4->BaseClass->U_1.V_1.Kind == Tree_Class && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_4->BaseClass->U_1.V_5.Class.Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"  yyyWriteNode", 14L);
          Tree_WI(W_4->BaseClass->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)" (yyt); ", 8L);
          IO_WriteNl(Tree_f);
        }
        iClassName = W_4->Name;
        Tree_ForallAttributes(W_4->Attributes, (Tree_ProcOfT)WriteNode);
        IO_WriteS(Tree_f, (STRING)" END yyyWriteNode", 17L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_5 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"  yyWriteSelector ( \"", 21L);
      Tree_WI(W_5->Name);
      IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
      IO_WriteS(Tree_f, (STRING)" yyWriteAdr ( yyt . ", 20L);
      Tree_WI(W_5->Name);
      IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_6 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_6->Properties) == 0X0L) {
        if (IN(Tree_Link, W_6->Properties)) {
          IO_WriteS(Tree_f, (STRING)"  yyWriteSelector ( \"", 21L);
          Tree_WI(W_6->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
          IO_WriteS(Tree_f, (STRING)" yyWriteAdr ( yyt . ", 20L);
          Tree_WI(W_6->Name);
          IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"  yyWriteSelector ( \"", 21L);
          Tree_WI(W_6->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ; write", 11L);
          Tree_WI(W_6->Type);
          IO_WriteS(Tree_f, (STRING)" ( yyt . ", 9L);
          Tree_WI(W_6->Name);
          IO_WriteS(Tree_f, (STRING)" ) yyWriteNl ( ) ;", 18L);
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
  struct S_7 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_7 = &t->U_1.V_5.Class;

      Mark(W_7->Extensions);
      if ((Tree_NoCodeClass & W_7->Properties) == 0X0L && IN(Tree_HasChildren, W_7->Properties)) {
        IO_WriteS(Tree_f, (STRING)"    | ", 6L);
        Tree_WI(W_7->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) => ", 14L);
        IO_WriteNl(Tree_f);
        TreeMThree2_GetIterator(t);
        iClassName = W_7->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Mark);
        if (TreeMThree2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN ;", 8L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt := TNode . ", 15L);
          Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
          IO_WriteS(Tree_f, (STRING)" ;", 2L);
          IO_WriteNl(Tree_f);
        }
      }
      Mark(W_7->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_8 = &t->U_1.V_9.Child;

      if (t != TreeMThree2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyMark ( TNode . ", 17L);
        Tree_WI(W_8->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_9 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Link, W_9->Properties)) {
        IO_WriteS(Tree_f, (STRING)"yyMark ( TNode . ", 17L);
        Tree_WI(W_9->Name);
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

static void WriteClassName
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
      register Tree_yClass *W_10 = &t->U_1.V_5.Class;

      WriteClassName(W_10->Extensions);
      if ((Tree_NoCodeClass & W_10->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"   | ", 5L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) => ", 14L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_10->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"       yWrite", 13L);
          Tree_WI(W_10->Name);
          IO_WriteS(Tree_f, (STRING)" ( TNode ) ; ", 13L);
          IO_WriteNl(Tree_f);
          TreeMThree2_GetIterator(t);
          if (TreeMThree2_Iterator == Tree_NoTree) {
            IO_WriteS(Tree_f, (STRING)"       EXIT ;", 13L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"       yyIndentSelector ( \"", 27L);
            Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
            IO_WriteS(Tree_f, (STRING)"       yyt := TNode . ", 22L);
            Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)" ;", 2L);
            IO_WriteNl(Tree_f);
          }
        } else {
          IO_WriteS(Tree_f, (STRING)"       Wr . PutText ( yyf , \"", 29L);
          Tree_WI(W_10->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl ( ) ; EXIT ;", 28L);
          IO_WriteNl(Tree_f);
        }
      }
      WriteClassName(W_10->Next);
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
  struct S_9 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_11 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_11->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_11->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yWrite", 16L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)" ( yyt : ", 9L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( yyf , \"", 24L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ; yyWriteNl ( ) ;", 21L);
        IO_WriteNl(Tree_f);
        TreeMThree2_GetIterator(t);
        iClassName = W_11->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)WriteAttributes);
        IO_WriteS(Tree_f, (STRING)" END yWrite", 11L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_12 = &t->U_1.V_9.Child;

      if (t != TreeMThree2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"  yyIndentSelectorTree ( \"", 26L);
        Tree_WI(W_12->Name);
        IO_WriteS(Tree_f, (STRING)"\" , yyt . ", 10L);
        Tree_WI(W_12->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_13 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_13->Properties) == 0X0L) {
        if (IN(Tree_Link, W_13->Properties)) {
          IO_WriteS(Tree_f, (STRING)"  yyIndentSelectorTree ( \"", 26L);
          Tree_WI(W_13->Name);
          IO_WriteS(Tree_f, (STRING)"\" , yyt . ", 10L);
          Tree_WI(W_13->Name);
          IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"  yyIndentSelector ( \"", 22L);
          Tree_WI(W_13->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ; ", 6L);
          IO_WriteS(Tree_f, (STRING)"write", 5L);
          Tree_WI(W_13->Type);
          IO_WriteS(Tree_f, (STRING)" ( yyt . ", 9L);
          Tree_WI(W_13->Name);
          IO_WriteS(Tree_f, (STRING)" ) yyWriteNl ( ) ;", 18L);
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
  struct S_10 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_14 = &t->U_1.V_5.Class;

      NodeKinds(W_14->Extensions);
      if ((Tree_NoCodeClass & W_14->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"     | ", 7L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteS(Tree_f, (STRING)"         RETURN \"", 17L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)"\" ; ", 4L);
        IO_WriteNl(Tree_f);
      }
      NodeKinds(W_14->Next);
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
  struct S_11 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_15 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_15->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)" PROCEDURE Write", 16L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)"Html ( TNode : ", 15L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
        IO_WriteS(Tree_f, (STRING)" =VAR LNodeTag : TEXT ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    LNodeTag := yyNodeTag ( TNode ) ; ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"<a name=\\\"\" ) ; ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , LNodeTag ) ; ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"\\\">DEF \" ) ; ", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , LNodeTag ) ; ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \"(\" ) ; ", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteHex ( LOOPHOLE ( TNode , ARRAY [ 0 .. 3 ] OF CHAR ) ) ; ", 67L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , \")", 27L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)"</a>\" ) ; ", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl ( ) ; ", 20L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_15->Properties) != 0X0L) {
          Tree_ForallAttributes(t, (Tree_ProcOfT)WriteHtmlNodes);
        }
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl ( ) ; ", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END Write", 11L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)"Html ; ", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_16 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"    WriteChildOrLink ( \"", 24L);
      Tree_WI(W_16->Name);
      IO_WriteS(Tree_f, (STRING)"\" , \"", 5L);
      Tree_WI(W_16->Type);
      IO_WriteS(Tree_f, (STRING)"\" , TNode . ", 12L);
      Tree_WI(W_16->Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_17 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_17->Properties) == 0X0L) {
        if (IN(Tree_Link, W_17->Properties)) {
          IO_WriteS(Tree_f, (STRING)"    WriteChildOrLink ( \"", 24L);
          Tree_WI(W_17->Name);
          IO_WriteS(Tree_f, (STRING)"\" , \"", 5L);
          Tree_WI(W_17->Type);
          IO_WriteS(Tree_f, (STRING)"\" , TNode . ", 12L);
          Tree_WI(W_17->Name);
          IO_WriteS(Tree_f, (STRING)" , TRUE ) ; ", 12L);
          IO_WriteNl(Tree_f);
        } else if (W_17->Type == iBOOLEAN) {
          IO_WriteS(Tree_f, (STRING)"    WriteBOOLEANAttribute ( \"", 29L);
          Tree_WI(W_17->Name);
          IO_WriteS(Tree_f, (STRING)"\" , TNode . ", 12L);
          Tree_WI(W_17->Name);
          IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"    Wr . PutText ( yyf , IndentString & \"", 41L);
          Tree_WI(W_17->Name);
          IO_WriteS(Tree_f, (STRING)" : ", 3L);
          Tree_WI(W_17->Type);
          IO_WriteS(Tree_f, (STRING)" = \" ) ; ", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    write", 9L);
          Tree_WI(W_17->Type);
          IO_WriteS(Tree_f, (STRING)" ( TNode . ", 11L);
          Tree_WI(W_17->Name);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    yyWriteNl ( ) ; ", 20L);
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
  struct S_12 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_18 = &t->U_1.V_5.Class;

      WriteHtmlCases(W_18->Extensions);
      if ((Tree_NoCodeClass & W_18->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"     | ", 7L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)" ( TNode ) => ", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"         Write", 14L);
        Tree_WI(W_18->Name);
        IO_WriteS(Tree_f, (STRING)"Html ( TNode ) ; ", 17L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_18->Properties) != 0X0L) {
          TreeMThree2_GetIterator(t);
          Tree_ForallAttributes(t, (Tree_ProcOfT)WriteHtmlCases);
          if (TreeMThree2_Iterator == Tree_NoTree) {
            IO_WriteS(Tree_f, (STRING)"         EXIT ;", 15L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"         yyt := TNode . ", 24L);
            Tree_WI(TreeMThree2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)" ; ", 3L);
            IO_WriteNl(Tree_f);
          }
        }
      }
      WriteHtmlCases(W_18->Next);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_19 = &t->U_1.V_9.Child;

      if (t != TreeMThree2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"         WriteHtmlRecurse ( TNode . ", 36L);
        Tree_WI(W_19->Name);
        IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_20 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Link, W_20->Properties)) {
        IO_WriteS(Tree_f, (STRING)"         WriteHtmlRecurse ( TNode . ", 36L);
        Tree_WI(W_20->Name);
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

void TreeMThree2_GetIterator
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
      register Tree_yClass *W_21 = &t->U_1.V_5.Class;

      TreeMThree2_Iterator = Tree_NoTree;
      RevChild = Tree_NoTree;
      Tree_ForallAttributes(t, (Tree_ProcOfT)TreeMThree2_GetIterator);
      if (RevChild != Tree_NoTree) {
        TreeMThree2_Iterator = RevChild;
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_22 = &t->U_1.V_9.Child;

      TreeMThree2_Iterator = t;
      if (IN(Tree_Reverse, W_22->Properties)) {
        RevChild = t;
      }
      return;
    }
    break;
  default :
    break;
  }
}

void TreeMThree2_BeginTreeMThree2
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_ArrayToString((STRING)"BOOLEAN", 7L, &sBOOLEAN);
  iBOOLEAN = Idents_MakeIdent(&sBOOLEAN);
}

void TreeMThree2_CloseTreeMThree2
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

void TreeMThree2__init()
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
    Tree__init();

    TreeMThree2_yyf = IO_StdOutput;
    TreeMThree2_Exit = yyExit;
    TreeMThree2_BeginTreeMThree2();
  }
}
