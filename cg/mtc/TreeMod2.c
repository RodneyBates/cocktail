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

#ifndef DEFINITION_TreeMod2
#include "TreeMod2.h"
#endif

Tree_tTree TreeMod2_Iterator;
IO_tFile TreeMod2_yyf;
PROC TreeMod2_Exit;

static Idents_tIdent iClassName;
static Tree_tTree RevChild;
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
static void WriteNodeName ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void WriteNode ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void Mark ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void WriteClassName ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void WriteAttributes ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void ReadAttributes ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void PutAttributes ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void GetAttributes ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void InitKindToIdent ARGS((Tree_tTree t));
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


void TreeMod2_WriteLine
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeMod2, routine ", 32L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeMod2_Exit)();
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

void TreeMod2_TreeIO
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

      IO_WriteS(Tree_f, (STRING)"TYPE yyPtrtTree        = POINTER TO ", 36L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyf        : IO.tFile;", 26L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyLabel    : SHORTCARD;", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyKind     : SHORTCARD;", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyc        : CHAR;", 22L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yys        : Strings.tString;", 33L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD(','), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMark (yyt: ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN RETURN; END;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   INC (yyt^.yyHead.yyMark);", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt^.yyHead.yyMark > 1 THEN RETURN; END;", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyt^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)Mark);
        IO_WriteS(Tree_f, (STRING)"   ELSE RETURN;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyMark;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD(';'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"CONST yyInitTreeStoreSize      = 32;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyTreeStoreSize    : LONGINT;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyTreeStorePtr     : POINTER TO ARRAY [0..50000] OF ", 56L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyLabelCount       : INTEGER;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyRecursionLevel   : SHORTINT;", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMapToLabel (yyTree: ", 32L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"): SHORTCARD;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyi := 1 TO yyLabelCount DO", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyTreeStorePtr^[yyi] = yyTree THEN RETURN yyi; END;", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC (yyLabelCount);", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyLabelCount = yyTreeStoreSize THEN", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   DynArray.ExtendArray (yyTreeStorePtr, yyTreeStoreSize, SYSTEM.TSIZE (", 72L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"));", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyTreeStorePtr^[yyLabelCount] := yyTree;", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyLabelCount;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyMapToLabel;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMapToTree (yyLabel: SHORTCARD): ", 44L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN RETURN yyTreeStorePtr^[yyLabel]; END yyMapToTree;", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteNl; BEGIN IO.WriteNl (yyf); END yyWriteNl;", 59L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteSelector (yys: ARRAY OF CHAR);", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN IO.WriteS (yyf, yys); Layout.WriteSpaces (yyf, 15 - INTEGER (HIGH (yys))); IO.WriteS (yyf, ' = '); END yyWriteSelector;", 126L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteHex (VAR yyx: ARRAY OF SYSTEM.BYTE);", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO INTEGER (HIGH (yyx)) DO", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteN (yyf, ORD (CHAR (yyx [yyi])), 2, 16);", 50L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteC (yyf, ' ');", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteHex;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteAdr (yyt: ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (yyf, '", 20L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"');", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyWriteHex (yyt);", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyWriteNl;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyWriteAdr;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteNode);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node (yyyf: IO.tFile; yyt: ", 27L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := yyyf;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyt = ", 11L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IO.WriteS (yyf, '", 20L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"'); yyWriteNl; RETURN;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE yyt^.Kind OF", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteNodeName);
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Write", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"VAR yyIndentLevel      : SHORTINT;", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyActualIndent , yyIndentQuotient , yyIndentRemainder : SHORTINT;", 69L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"CONST yyIndentFactor = 20; ", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yySetIndentInfo ( ); ", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN ", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyIndentQuotient := yyIndentLevel DIV yyIndentFactor; ", 57L);
        IO_WriteS(Tree_f, (STRING)"   yyIndentRemainder := yyIndentLevel MOD yyIndentFactor; ", 58L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyActualIndent ", 18L);
        IO_WriteS(Tree_f, (STRING)"     := VAL ( SHORTINT , 10 * ORD ( yyIndentQuotient > 0 ) ) ", 61L);
        IO_WriteS(Tree_f, (STRING)"        + yyIndentRemainder ", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END yySetIndentInfo ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Write", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyyf: IO.tFile; yyt: ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yySaveLevel       : SHORTINT;", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := yyyf;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyRecursionLevel = 0 THEN yyLabelCount := 0; END;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySaveLevel := yyIndentLevel;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIndentLevel := 0;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySetIndentInfo ( ) ; ", 24L);
        IO_WriteS(Tree_f, (STRING)"  yyWrite", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIndentLevel := yySaveLevel;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySetIndentInfo ( ) ; ", 24L);
        IO_WriteS(Tree_f, (STRING)"  DEC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Write", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIndentSelector (yys: ARRAY OF CHAR);", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN ", 7L);
        IO_WriteS(Tree_f, (STRING)"   IF yyIndentQuotient > 0 ", 27L);
        IO_WriteS(Tree_f, (STRING)"   THEN IO.WriteC ( yyf , '(' ); IO.WriteC ( yyf , '*' ); ", 58L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     IO.WriteN ( yyf , yyIndentQuotient * yyIndentFactor , 6 , 10 ); ", 69L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     IO.WriteC ( yyf , '*' ); IO.WriteC ( yyf , ')' ); ", 55L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"     Layout.WriteSpaces (yyf, yyIndentRemainder ); ", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSE Layout.WriteSpaces (yyf, yyIndentRemainder); ", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END ; ", 9L);
        IO_WriteS(Tree_f, (STRING)"   yyWriteSelector (yys); ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyIndentSelector;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIndentSelectorTree (yys: ARRAY OF CHAR; yyt: ", 57L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN yyIndentSelector (yys); write", 36L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (yyt) END yyIndentSelectorTree;", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteAttributes);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWrite", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyLevel   : SHORTCARD;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyLevel := yyIndentLevel;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteS (yyf, ' ", 22L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"'); yyWriteNl; EXIT;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSIF yyt^.yyHead.yyMark = 0 THEN", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, '^'); IO.WriteI (yyf, yyMapToLabel (yyt), 0); yyWriteNl; EXIT;", 82L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSIF yyt^.yyHead.yyMark > 1 THEN", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyWriteNl; IO.WriteN (yyf, yyMapToLabel (yyt), 6, 10); IO.WriteC (yyf, ':');", 80L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Layout.WriteSpaces (yyf, yyActualIndent - 7);", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSE", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, ' ');", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyt^.yyHead.yyMark := 0;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   INC (yyIndentLevel, 2);", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yySetIndentInfo ( ) ; ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyt^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteClassName);
        IO_WriteS(Tree_f, (STRING)"   ELSE EXIT;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIndentLevel := yyLevel;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yySetIndentInfo ( ) ; ", 24L);
        IO_WriteS(Tree_f, (STRING)" END yyWrite", 12L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Read", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyyf: IO.tFile): ", 19L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyt       : ", 17L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := yyyf;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyRecursionLevel = 0 THEN yyLabelCount := 0; END;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF NOT yyIsInitialized THEN", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyInitKindToIdent; yyIsInitialized := TRUE;", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyRead", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (SYSTEM.ADR (yyt));", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  DEC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyt;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Read", 9L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyRead", 16L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: yyPtrtTree);", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE IO.ReadC (yyf) OF", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | '^': yyLabel := IO.ReadI (yyf); yyReadNl; yyt^ := yyMapToTree (yyLabel); RETURN;", 85L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | 12C, '0': yyLabel := IO.ReadI (yyf); yyc := IO.ReadC (yyf);", 64L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Layout.SkipSpaces (yyf); Strings.ReadL (yyf, yys);", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyKind := yyMapToKind (yys); yyt^ := Make", 45L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF yyLabel # yyMapToLabel (yyt^) THEN IO.WriteS (IO.StdError, '", 67L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)": error in Read", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"'); IO.WriteNl (IO.StdError); yyExit; END;", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSE", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    Layout.SkipSpaces (yyf); Strings.ReadL (yyf, yys);", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyKind := yyMapToKind (yys);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF yyKind = 0 THEN yyt^ := ", 31L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"; RETURN; END;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    yyt^ := Make", 16L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyKind OF", 17L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ReadAttributes);
        IO_WriteS(Tree_f, (STRING)"   ELSE RETURN;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyRead", 11L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyKindToIdent      : ARRAY [0..", 35L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)"] OF Idents.tIdent;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyIsInitialized    : BOOLEAN;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyMapToKind (VAR yys: Strings.tString): SHORTCARD;", 60L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : Idents.tIdent;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyk       : SHORTCARD;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyi := Idents.MakeIdent (yys);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyk := 0 TO ", 18L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyKindToIdent [yyk] = yyi THEN RETURN yyk; END;", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN 0;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyMapToKind;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyInitKindToIdent2 (yya: ARRAY OF CHAR; yyKind: SHORTCARD);", 69L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yys       : Strings.tString;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Strings.ArrayToString (yya, yys);", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyKindToIdent [yyKind] := Idents.MakeIdent (yys);", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyInitKindToIdent2;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyInitKindToIdent;", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyInitKindToIdent2 ('", 23L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"', 0);", 6L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)InitKindToIdent);
        IO_WriteS(Tree_f, (STRING)" END yyInitKindToIdent;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyReadNl; BEGIN IO.ReadNl (yyf); END yyReadNl;", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyReadIdent (): Idents.tIdent;", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yys       : Strings.tString;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Strings.ReadL (yyf, yys);", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IO.UnRead (yyf);", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN Idents.MakeIdent (yys);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyReadIdent;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyReadHex (VAR yyx: ARRAY OF SYSTEM.BYTE);", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO INTEGER (HIGH (yyx)) DO", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyx [yyi] := SYSTEM.BYTE (CHR (CARDINAL (IO.ReadN (yyf, 16))));", 66L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyReadHex;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yySkip;", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  REPEAT UNTIL IO.ReadC (yyf) = '='; yyc := IO.ReadC (yyf);", 59L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yySkip;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"CONST yyNil    = 374C;", 22L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"CONST yyNoLabel        = 375C;", 30L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"CONST yyLabelDef       = 376C;", 30L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"CONST yyLabelUse       = 377C;", 30L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Put", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyyf: IO.tFile; yyt: ", 23L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := yyyf;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyRecursionLevel = 0 THEN yyLabelCount := 0; END;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyMark (yyt);", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyPut", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  DEC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Put", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyPut", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   IF yyt = ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" THEN", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, yyNil); RETURN;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSIF yyt^.yyHead.yyMark = 0 THEN", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, yyLabelUse); yyLabel := yyMapToLabel (yyt); yyPut (yyLabel);", 80L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    RETURN;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ELSIF yyt^.yyHead.yyMark > 1 THEN", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, yyLabelDef); yyLabel := yyMapToLabel (yyt); yyPut (yyLabel);", 80L);
        IO_WriteNl(Tree_f);
        if (Tree_ClassCount > 251) {
          IO_WriteS(Tree_f, (STRING)"    yyPut (yyt^.Kind);", 22L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   ELSIF yyt^.Kind > 251 THEN", 29L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, yyNoLabel); yyPut (yyt^.Kind);", 50L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, CHR (yyt^.Kind));", 37L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"   ELSE", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IO.WriteC (yyf, CHR (yyt^.Kind));", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyt^.yyHead.yyMark := 0;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyt^.Kind OF", 20L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)PutAttributes);
        IO_WriteS(Tree_f, (STRING)"   ELSE RETURN;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyPut", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyPut (VAR yyx: ARRAY OF SYSTEM.BYTE);", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyi := IO.Write (yyf, SYSTEM.ADR (yyx), INTEGER (HIGH (yyx)) + 1);", 68L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyPut;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyPutIdent (yyi: Idents.tIdent);", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yys       : Strings.tString;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Idents.GetString (yyi, yys);", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Strings.WriteL (yyf, yys);", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyPutIdent;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE Get", 13L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyyf: IO.tFile): ", 19L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyt       : ", 17L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyf := yyyf;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IF yyRecursionLevel = 0 THEN yyLabelCount := 0; END;", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  INC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyGet", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (SYSTEM.ADR (yyt));", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  DEC (yyRecursionLevel);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN yyt;", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END Get", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyGet", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt: yyPtrtTree);", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyc := IO.ReadC (yyf);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyc OF", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyNil     : yyt^ := ", 25L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"; RETURN;", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyLabelUse        : yyGet (yyLabel); yyt^ := yyMapToTree (yyLabel); RETURN;", 80L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   | yyLabelDef        : yyGet (yyLabel);", 41L);
        if (Tree_ClassCount > 251) {
          IO_WriteS(Tree_f, (STRING)" yyGet (yyKind);", 16L);
        } else {
          IO_WriteS(Tree_f, (STRING)" yyKind := ORD (IO.ReadC (yyf));", 32L);
        }
        IO_WriteS(Tree_f, (STRING)" yyt^ := Make", 13L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF yyLabel # yyMapToLabel (yyt^) THEN IO.WriteS (IO.StdError, '", 67L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)": error in Get", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"'); IO.WriteNl (IO.StdError); yyExit; END;", 42L);
        IO_WriteNl(Tree_f);
        if (Tree_ClassCount > 251) {
          IO_WriteS(Tree_f, (STRING)"   | yyNoLabel : yyGet (yyKind); yyt^ := Make", 45L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"   ELSE yyKind := ORD (yyc); yyt^ := Make", 41L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   CASE yyKind OF", 17L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)GetAttributes);
        IO_WriteS(Tree_f, (STRING)"   ELSE RETURN;", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyGet", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyGet (VAR yyx: ARRAY OF SYSTEM.BYTE);", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyi := IO.Read (yyf, SYSTEM.ADR (yyx), INTEGER (HIGH (yyx)) + 1);", 67L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyGet;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyGetIdent (VAR yyi: Idents.tIdent);", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" VAR yys       : Strings.tString;", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  Strings.ReadL (yyf, yys);", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyi := Idents.MakeIdent (yys);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyGetIdent;", 16L);
        IO_WriteNl(Tree_f);
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
  struct S_4 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_2 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_2->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_2->Name);
        IO_WriteS(Tree_f, (STRING)": IO.WriteS (yyf, '", 19L);
        Tree_WI(W_2->Name);
        IO_WriteS(Tree_f, (STRING)"'); yyWriteNl;", 14L);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_2->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)" yyyWriteNode", 13L);
          Tree_WI(W_2->Name);
          IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        }
        IO_WriteNl(Tree_f);
      }
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
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_3 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_3->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_3->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyyWriteNode", 22L);
        Tree_WI(W_3->Name);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        if (W_3->BaseClass->U_1.V_1.Kind == Tree_Class && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_3->BaseClass->U_1.V_5.Class.Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"  yyyWriteNode", 14L);
          Tree_WI(W_3->BaseClass->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)" (yyt); ", 8L);
          IO_WriteNl(Tree_f);
        }
        iClassName = W_3->Name;
        Tree_ForallAttributes(W_3->Attributes, (Tree_ProcOfT)WriteNode);
        IO_WriteS(Tree_f, (STRING)" END yyyWriteNode", 17L);
        Tree_WI(W_3->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_4 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)"  yyWriteSelector ('", 20L);
      Tree_WI(W_4->Name);
      IO_WriteS(Tree_f, (STRING)"');", 3L);
      IO_WriteS(Tree_f, (STRING)" yyWriteAdr (yyt^.", 18L);
      Tree_WI(iClassName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_4->Name);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_5 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_5->Properties) == 0X0L) {
        if (IN(Tree_Link, W_5->Properties)) {
          IO_WriteS(Tree_f, (STRING)"  yyWriteSelector ('", 20L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)"');", 3L);
          IO_WriteS(Tree_f, (STRING)" yyWriteAdr (yyt^.", 18L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"  yyWriteSelector ('", 20L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)"'); write", 9L);
          Tree_WI(W_5->Type);
          IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)") yyWriteNl;", 12L);
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
  struct S_6 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_6 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_6->Properties) == 0X0L && IN(Tree_HasChildren, W_6->Properties)) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_6->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_6->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Mark);
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
      register Tree_yChild *W_7 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyMark (yyt^.", 13L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_7->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_8 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Link, W_8->Properties)) {
        IO_WriteS(Tree_f, (STRING)"yyMark (yyt^.", 13L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_8->Name);
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
  struct S_7 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_9 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_9->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_9->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_9->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"yWrite", 6L);
          Tree_WI(W_9->Name);
          IO_WriteS(Tree_f, (STRING)" (yyt); ", 8L);
          TreeMod2_GetIterator(t);
          if (TreeMod2_Iterator == Tree_NoTree) {
            IO_WriteS(Tree_f, (STRING)"EXIT;", 5L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"yyIndentSelector ('", 19L);
            Tree_WI(TreeMod2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"'); ", 4L);
            IO_WriteS(Tree_f, (STRING)"yyt := yyt^.", 12L);
            Tree_WI(W_9->Name);
            IO_WriteS(Tree_f, (STRING)".", 1L);
            Tree_WI(TreeMod2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
        } else {
          IO_WriteS(Tree_f, (STRING)"IO.WriteS (yyf, '", 17L);
          Tree_WI(W_9->Name);
          IO_WriteS(Tree_f, (STRING)"'); yyWriteNl; EXIT;", 20L);
          IO_WriteNl(Tree_f);
        }
      }
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
  struct S_8 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_10 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_10->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_10->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yWrite", 16L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)" (yyt: ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  IO.WriteS (yyf, '", 19L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)"'); yyWriteNl;", 14L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_10->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)WriteAttributes);
        IO_WriteS(Tree_f, (STRING)" END yWrite", 11L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_11 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"  yyIndentSelectorTree ('", 25L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)"', yyt^.", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_12 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_12->Properties) == 0X0L) {
        if (IN(Tree_Link, W_12->Properties)) {
          IO_WriteS(Tree_f, (STRING)"  yyIndentSelectorTree ('", 25L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)"', yyt^.", 8L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"  yyIndentSelector ('", 21L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)"'); ", 4L);
          IO_WriteS(Tree_f, (STRING)"write", 5L);
          Tree_WI(W_12->Type);
          IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)") yyWriteNl;", 12L);
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

static void ReadAttributes
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
      register Tree_yClass *W_13 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_13->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_13->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_13->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReadAttributes);
        if (TreeMod2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yySkip; yyt := SYSTEM.ADR (yyt^^.", 33L);
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
      register Tree_yChild *W_14 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yySkip; read", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (SYSTEM.ADR (yyt^^.", 20L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_14->Name);
        IO_WriteS(Tree_f, (STRING)"))", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_15 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_15->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"yySkip; read", 12L);
        Tree_WI(W_15->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt^^.", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)") yyReadNl;", 11L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void PutAttributes
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
      register Tree_yClass *W_16 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_16->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_16->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_16->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)PutAttributes);
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
      register Tree_yChild *W_17 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"put", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_17->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_18 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_18->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"put", 3L);
        Tree_WI(W_18->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt^.", 7L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_18->Name);
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

static void GetAttributes
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
      register Tree_yClass *W_19 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_19->Properties) == 0X0L && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_19->Properties) != 0X0L) {
        IO_WriteS(Tree_f, (STRING)"| ", 2L);
        Tree_WI(W_19->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeMod2_GetIterator(t);
        iClassName = W_19->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)GetAttributes);
        if (TreeMod2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"RETURN;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt := SYSTEM.ADR (yyt^^.", 25L);
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
      register Tree_yChild *W_20 = &t->U_1.V_9.Child;

      if (t != TreeMod2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"get", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (SYSTEM.ADR (yyt^^.", 20L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_20->Name);
        IO_WriteS(Tree_f, (STRING)"))", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_21 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_21->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"get", 3L);
        Tree_WI(W_21->Type);
        IO_WriteS(Tree_f, (STRING)" (yyt^^.", 8L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_21->Name);
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

static void InitKindToIdent
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
      register Tree_yClass *W_22 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_22->Properties) == 0X0L) {
        IO_WriteS(Tree_f, (STRING)"  yyInitKindToIdent2 ('", 23L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)"', ", 3L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)");", 2L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

void TreeMod2_GetIterator
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
      register Tree_yClass *W_23 = &t->U_1.V_5.Class;

      TreeMod2_Iterator = Tree_NoTree;
      RevChild = Tree_NoTree;
      Tree_ForallAttributes(t, (Tree_ProcOfT)TreeMod2_GetIterator);
      if (RevChild != Tree_NoTree) {
        TreeMod2_Iterator = RevChild;
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_24 = &t->U_1.V_9.Child;

      TreeMod2_Iterator = t;
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

void TreeMod2_BeginTreeMod2
# ifdef __STDC__
()
# else
()
# endif
{
}

void TreeMod2_CloseTreeMod2
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

void TreeMod2__init()
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
    IO__init();
    Sets__init();
    Idents__init();
    Positions__init();
    Tree__init();

    TreeMod2_yyf = IO_StdOutput;
    TreeMod2_Exit = yyExit;
    TreeMod2_BeginTreeMod2();
  }
}
