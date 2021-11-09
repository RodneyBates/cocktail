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

#ifndef DEFINITION_TreeC2
#include "TreeC2.h"
#endif

Tree_tTree TreeC2_Iterator;
IO_tFile TreeC2_yyf;
PROC TreeC2_Exit;

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
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


void TreeC2_WriteLine
# ifdef __STDC__
(Positions_tPosition Line)
# else
(Line)
Positions_tPosition Line;
# endif
{
  if (Line.Line != 0) {
    if (Sets_IsElement(ORD('6'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"# line ", 7L);
      Tree_WN((LONGINT)Line.Line);
      IO_WriteS(Tree_f, (STRING)" \"", 2L);
      Tree_WI(Line.File);
      IO_WriteS(Tree_f, (STRING)"\"", 1L);
      IO_WriteNl(Tree_f);
    } else {
      IO_WriteS(Tree_f, (STRING)"/* line ", 8L);
      Tree_WN((LONGINT)Line.Line);
      IO_WriteS(Tree_f, (STRING)" \"", 2L);
      Tree_WI(Line.File);
      IO_WriteS(Tree_f, (STRING)"\" */", 4L);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module TreeC2, routine ", 30L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*TreeC2_Exit)();
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

void TreeC2_TreeIO
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

      IO_WriteS(Tree_f, (STRING)"typedef ", 8L);
      Tree_WI(Tree_itTree);
      IO_WriteS(Tree_f, (STRING)" * yyPtrtTree;", 14L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"static FILE * yyf;", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD(','), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyMark", 18L);
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
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyt == ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)" || ++ yyt->yyHead.yyMark > 1) return;", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)Mark);
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
      if (Sets_IsElement(ORD(';'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# define yyInitTreeStoreSize 32", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# define yyMapToTree(yyLabel) yyTreeStorePtr [yyLabel]", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static unsigned long yyTreeStoreSize = yyInitTreeStoreSize;", 59L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyTreeStore [yyInitTreeStoreSize];", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" * yyTreeStorePtr = yyTreeStore;", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static int yyLabelCount;", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static short yyRecursionLevel = 0;", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tLabel yyMapToLabel", 20L);
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
        IO_WriteS(Tree_f, (STRING)" register int yyi;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (yyi = 1; yyi <= yyLabelCount; yyi ++) if (yyTreeStorePtr [yyi] == yyt) return yyi;", 88L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (++ yyLabelCount == yyTreeStoreSize)", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ExtendArray ((char * *) & yyTreeStorePtr, & yyTreeStoreSize, sizeof (", 71L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)"));", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyTreeStorePtr [yyLabelCount] = yyt;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyLabelCount;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyWrite", 19L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" ();", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyWriteNl () { (void) putc ('\\n', yyf); }", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyWriteSelector", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (char * yys)", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yys) char * yys;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register int yyi = 16 - strlen (yys);", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (void) fputs (yys, yyf);", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" while (yyi -- > 0) (void) putc (' ', yyf);", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (void) fputs (\" = \", yyf);", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyWriteHex", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (unsigned char * yyx, int yysize)", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyx, yysize) unsigned char * yyx; int yysize;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{ register int yyi; for (yyi = 0; yyi < yysize; yyi ++) (void) fprintf (yyf, \"%02x \", yyx [yyi]); }", 99L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('o'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyWriteAdr", 22L);
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
        IO_WriteS(Tree_f, (STRING)") (void) fputs (\"", 17L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"\", yyf);", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" else yyWriteHex ((unsigned char *) & yyt, sizeof (yyt));", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyWriteNl ();", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteNode);
        IO_WriteS(Tree_f, (STRING)"void Write", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"Node", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (FILE * yyyf, ", 15L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyyf, yyt) FILE * yyyf; ", 26L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyf = yyyf;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyt == ", 12L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") { (void) fputs (\"", 19L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"\\n\", yyf); return; }", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" switch (yyt->Kind) {", 21L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteNodeName);
        IO_WriteS(Tree_f, (STRING)" default: ;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static short yyIndentLevel;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"void Write", 10L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (FILE * yyyf, ", 15L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyyf, yyt) FILE * yyyf; ", 26L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" short yySaveLevel = yyIndentLevel;", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyf = yyyf;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyRecursionLevel ++ == 0) yyLabelCount = 0;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyMark (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyIndentLevel = 0;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyWrite", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyIndentLevel = yySaveLevel;", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyRecursionLevel --;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyIndentSelector", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (char * yys)", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yys) char * yys;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register int yyi;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (yyi = 1; yyi <= yyIndentLevel; yyi ++) (void) putc (' ', yyf);", 68L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyWriteSelector (yys);", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyIndentSelectorTree", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (char * yys, ", 14L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yys, yyt) char * yys; ", 24L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{ yyIndentSelector (yys); write", 31L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (yyt) }", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteAttributes);
        IO_WriteS(Tree_f, (STRING)"static void yyWrite", 19L);
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
        IO_WriteS(Tree_f, (STRING)"{ unsigned short yyLevel = yyIndentLevel;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyt == ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") { (void) fputs (\" ", 20L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"\\n\", yyf); goto yyExit;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  } else if (yyt->yyHead.yyMark == 0) { (void) fprintf (yyf, \"^%d\\n\", yyMapToLabel (yyt)); goto yyExit;", 103L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  } else if (yyt->yyHead.yyMark > 1) {", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   register int yyi;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   (void) fprintf (yyf, \"\\n%06d:\", yyMapToLabel (yyt));", 55L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   for (yyi = 8; yyi <= yyIndentLevel; yyi ++) (void) putc (' ', yyf);", 70L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  } else (void) putc (' ', yyf);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt->yyHead.yyMark = 0;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIndentLevel += 2;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)WriteClassName);
        IO_WriteS(Tree_f, (STRING)"  default: goto yyExit;", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"yyExit:", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyIndentLevel = yyLevel;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static tIdent yyKindToIdent [", 29L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)" + 1];", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static bool yyIsInitialized = false;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static short yyMapToKind", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (char * yys)", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yys) char * yys;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register int yyk;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register tIdent yyi = MakeIdent ((tString) yys, strlen (yys));", 63L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (yyk = 0; yyk <= ", 22L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)"; yyk ++) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyKindToIdent [yyk] == yyi) return yyk;", 45L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return 0;", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyReadNl () { (void) fscanf (yyf, \"\\n\"); }", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static tIdent yyReadIdent ()", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" char yys [256];", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (void) fscanf (yyf, \"%s\", yys);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return MakeIdent ((tString) yys, strlen (yys));", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyReadHex", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (unsigned char * yyx, int yysize)", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyx, yysize) unsigned char * yyx; int yysize;", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" register int yyi; int yyk;", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (yyi = 0; yyi < yysize; yyi ++) { (void) fscanf (yyf, \"%x \", & yyk); yyx [yyi] = yyk; }", 92L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yySkip () { (void) fscanf (yyf, \" %*s =%*c\"); }", 59L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyRead", 18L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyPtrtTree yyt)", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyt) yyPtrtTree yyt;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" static ", 8L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tLabel yyLabel;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" static ", 8L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" static char yys [256];", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (getc (yyf)) {", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case '^':", 11L);
        IO_WriteS(Tree_f, (STRING)" (void) fscanf (yyf, \"%hd\\n\", & yyLabel); * yyt = yyMapToTree (yyLabel); return;", 80L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case '\\n': case '0':", 22L);
        IO_WriteS(Tree_f, (STRING)" (void) fscanf (yyf, \"%hd%*c %s\\n\", & yyLabel, yys);", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyKind = yyMapToKind (yys); * yyt = Make", 43L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if (yyLabel != yyMapToLabel (* yyt)) { (void) fputs (\"", 57L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)": error in Read", 15L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"\\n\", stderr); ", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Exit (); } break;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  default: ;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   (void) fscanf (yyf, \"%s\", yys);", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyKind = yyMapToKind (yys);", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if (yyKind == 0) { * yyt = ", 30L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"; return; }", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   * yyt = Make", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyKind) {", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)ReadAttributes);
        IO_WriteS(Tree_f, (STRING)"  default: return;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Read", 5L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (FILE * yyyf)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyyf) FILE * yyyf;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyf = yyyf;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyRecursionLevel ++ == 0) yyLabelCount = 0;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (! yyIsInitialized) {", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  register int yyi;", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  for (yyi = 0; yyi <= ", 23L);
        Tree_WN(Tree_ClassCount);
        IO_WriteS(Tree_f, (STRING)"; yyi ++)", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   yyKindToIdent [yyi] = MakeIdent ((tString) ", 46L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeName [yyi], strlen (", 25L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeName [yyi]));", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyIsInitialized = true;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyRead", 7L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (& yyt);", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyRecursionLevel --;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyt;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"# define yyNil 0374", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyNoLabel     0375", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyLabelDef    0376", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyLabelUse    0377", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('p'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyPut", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (char * yyx, int yysize)", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyx, yysize) char * yyx; int yysize;", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{ (void) fwrite (yyx, 1, yysize, yyf); }", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyPutIdent", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (tIdent yyi)", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyi) tIdent yyi;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" char yys [256];", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" GetString (yyi, (tString) yys);", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (void) fprintf (yyf, \"%s\\n\", yys);", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyPut", 17L);
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
        IO_WriteS(Tree_f, (STRING)" static ", 8L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tLabel yyLabel;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  if (yyt == ", 13L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)") {", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   (void) putc (yyNil, yyf); return;", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  } else if (yyt->yyHead.yyMark == 0) {", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   (void) putc (yyLabelUse, yyf); yyLabel = yyMapToLabel (yyt); yyPut ((char *) & yyLabel, sizeof (yyLabel)); return;", 117L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  } else if (yyt->yyHead.yyMark > 1) {", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   (void) putc (yyLabelDef, yyf); yyLabel = yyMapToLabel (yyt); yyPut ((char *) & yyLabel, sizeof (yyLabel));", 109L);
        IO_WriteNl(Tree_f);
        if (Tree_ClassCount > 251) {
          IO_WriteS(Tree_f, (STRING)"   yyPut ((char *) & yyt->Kind, sizeof (", 40L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tKind));", 9L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  } else if (yyt->Kind > 251) {", 31L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   (void) putc (yyNoLabel, yyf); yyPut ((char *) & yyt->Kind, sizeof (", 70L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_tKind));", 9L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"   (void) putc ((char) yyt->Kind, yyf);", 39L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  } else {", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   (void) putc ((char) yyt->Kind, yyf);", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyt->yyHead.yyMark = 0;", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyt->Kind) {", 22L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)PutAttributes);
        IO_WriteS(Tree_f, (STRING)"  default: return;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"void Put", 8L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (FILE * yyyf, ", 15L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt)", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyyf, yyt) FILE * yyyf; ", 26L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyf = yyyf;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyRecursionLevel ++ == 0) yyLabelCount = 0;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyMark (yyt);", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyPut", 6L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyRecursionLevel --;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      if (Sets_IsElement(ORD('g'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"static void yyGet", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (char * yyx, int yysize)", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyx, yysize) char * yyx; int yysize;", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{ (void) fread (yyx, 1, yysize, yyf); }", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyGetIdent", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (tIdent * yyi)", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyi) tIdent * yyi;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" char yys [256];", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (void) fscanf (yyf, \"%s%*c\", yys);", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" * yyi = MakeIdent ((tString) yys, strlen (yys));", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"static void yyGet", 17L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyPtrtTree yyt)", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyt) yyPtrtTree yyt;", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" static ", 8L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tLabel yyLabel;", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" static ", 8L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_tKind yyKind;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" for (;;) {", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyKind = getc (yyf)) {", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case yyNil           : * yyt = ", 33L);
        Tree_WI(Tree_iNoTree);
        IO_WriteS(Tree_f, (STRING)"; return;", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case yyLabelUse      : yyGet ((char *) & yyLabel, sizeof (yyLabel));", 70L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   * yyt = yyMapToTree (yyLabel); return;", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  case yyLabelDef      : yyGet ((char *) & yyLabel, sizeof (yyLabel));", 70L);
        IO_WriteNl(Tree_f);
        if (Tree_ClassCount > 251) {
          IO_WriteS(Tree_f, (STRING)"   yyGet ((char *) & yyKind, sizeof (yyKind));", 46L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"   yyKind = getc (yyf);", 23L);
        }
        IO_WriteS(Tree_f, (STRING)"   * yyt = Make", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if (yyLabel != yyMapToLabel (* yyt)) { (void) fputs (\"", 57L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)": error in Get", 14L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)"\\n\", stderr); ", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_Exit (); } break;", 18L);
        IO_WriteNl(Tree_f);
        if (Tree_ClassCount > 251) {
          IO_WriteS(Tree_f, (STRING)"  case yyNoLabel       : yyGet ((char *) & yyKind, sizeof (yyKind));", 68L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   * yyt = Make", 15L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)" (yyKind); break;", 17L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  default      : * yyt = Make", 29L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" (yyKind);", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (yyKind) {", 19L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)GetAttributes);
        IO_WriteS(Tree_f, (STRING)"  default: return;", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" Get", 4L);
        Tree_WI(Tree_iModule);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (FILE * yyyf)", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# else", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" (yyyf) FILE * yyyf;", 20L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"# endif", 7L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"{", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" yyt;", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyf = yyyf;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" if (yyRecursionLevel ++ == 0) yyLabelCount = 0;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyGet", 6L);
        Tree_WI(Tree_iModule);
        IO_WriteS(Tree_f, (STRING)" (& yyt);", 9L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" yyRecursionLevel --;", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" return yyt;", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
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
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_2->Name);
        IO_WriteS(Tree_f, (STRING)": (void) fputs (", 16L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeName [k", 12L);
        Tree_WI(W_2->Name);
        IO_WriteS(Tree_f, (STRING)"], yyf); (void) fputc ('\\n', yyf);", 34L);
        IO_WriteNl(Tree_f);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_2->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)" yyyWriteNode", 13L);
          Tree_WI(W_2->Name);
          IO_WriteS(Tree_f, (STRING)" (yyt);", 7L);
        }
        IO_WriteS(Tree_f, (STRING)" break;", 7L);
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
        IO_WriteS(Tree_f, (STRING)"static void yyyWriteNode", 24L);
        Tree_WI(W_3->Name);
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
        if (W_3->BaseClass->U_1.V_1.Kind == Tree_Class && ((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_3->BaseClass->U_1.V_5.Class.Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)" yyyWriteNode", 13L);
          Tree_WI(W_3->BaseClass->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)" (yyt); ", 8L);
          IO_WriteNl(Tree_f);
        }
        iClassName = W_3->Name;
        Tree_ForallAttributes(W_3->Attributes, (Tree_ProcOfT)WriteNode);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_4 = &t->U_1.V_9.Child;

      IO_WriteS(Tree_f, (STRING)" yyWriteSelector (\"", 19L);
      Tree_WI(W_4->Name);
      IO_WriteS(Tree_f, (STRING)"\");", 3L);
      IO_WriteS(Tree_f, (STRING)" yyWriteAdr (yyt->", 18L);
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
          IO_WriteS(Tree_f, (STRING)" yyWriteSelector (\"", 19L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)"\");", 3L);
          IO_WriteS(Tree_f, (STRING)" yyWriteAdr (yyt->", 18L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)" yyWriteSelector (\"", 19L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)"\"); write", 9L);
          Tree_WI(W_5->Type);
          IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)") yyWriteNl ();", 15L);
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
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_6->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_6->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)Mark);
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
      register Tree_yChild *W_7 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yyMark (yyt->", 13L);
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
        IO_WriteS(Tree_f, (STRING)"yyMark (yyt->", 13L);
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
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_9->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        if (((SET_ELEM(Tree_HasChildren) | SET_ELEM(Tree_HasAttributes)) & W_9->Properties) != 0X0L) {
          IO_WriteS(Tree_f, (STRING)"yWrite", 6L);
          Tree_WI(W_9->Name);
          IO_WriteS(Tree_f, (STRING)" (yyt); ", 8L);
          TreeC2_GetIterator(t);
          if (TreeC2_Iterator == Tree_NoTree) {
            IO_WriteS(Tree_f, (STRING)"goto yyExit;", 12L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"yyIndentSelector (\"", 19L);
            Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"\"); ", 4L);
            IO_WriteS(Tree_f, (STRING)"yyt = yyt->", 11L);
            Tree_WI(W_9->Name);
            IO_WriteS(Tree_f, (STRING)".", 1L);
            Tree_WI(TreeC2_Iterator->U_1.V_9.Child.Name);
            IO_WriteS(Tree_f, (STRING)"; break;", 8L);
            IO_WriteNl(Tree_f);
          }
        } else {
          IO_WriteS(Tree_f, (STRING)"(void) fputs (", 14L);
          Tree_WI(Tree_iMain);
          IO_WriteS(Tree_f, (STRING)"_NodeName [k", 12L);
          Tree_WI(W_9->Name);
          IO_WriteS(Tree_f, (STRING)"], yyf); (void) fputc ('\\n', yyf); goto yyExit;", 47L);
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
        IO_WriteS(Tree_f, (STRING)"static void yWrite", 18L);
        Tree_WI(W_10->Name);
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
        IO_WriteS(Tree_f, (STRING)" (void) fputs (", 15L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)"_NodeName [k", 12L);
        Tree_WI(W_10->Name);
        IO_WriteS(Tree_f, (STRING)"], yyf); (void) fputc ('\\n', yyf);", 34L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_10->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)WriteAttributes);
        IO_WriteS(Tree_f, (STRING)"}", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_11 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)" yyIndentSelectorTree (\"", 24L);
        Tree_WI(W_11->Name);
        IO_WriteS(Tree_f, (STRING)"\", yyt->", 8L);
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
          IO_WriteS(Tree_f, (STRING)" yyIndentSelectorTree (\"", 24L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)"\", yyt->", 8L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)");", 2L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)" yyIndentSelector (\"", 20L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)"\"); ", 4L);
          IO_WriteS(Tree_f, (STRING)"write", 5L);
          Tree_WI(W_12->Type);
          IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
          Tree_WI(iClassName);
          IO_WriteS(Tree_f, (STRING)".", 1L);
          Tree_WI(W_12->Name);
          IO_WriteS(Tree_f, (STRING)") yyWriteNl ();", 15L);
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
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_13->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_13->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)ReadAttributes);
        if (TreeC2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"return;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yySkip (); yyt = & ((* yyt)->", 29L);
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
      register Tree_yChild *W_14 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"yySkip (); read", 15L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (& ((* yyt)->", 14L);
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
        IO_WriteS(Tree_f, (STRING)"yySkip (); read", 15L);
        Tree_WI(W_15->Type);
        IO_WriteS(Tree_f, (STRING)" ((* yyt)->", 11L);
        Tree_WI(iClassName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_15->Name);
        IO_WriteS(Tree_f, (STRING)") yyReadNl ();", 14L);
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
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_16->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_16->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)PutAttributes);
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
      register Tree_yChild *W_17 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"put", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
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
        IO_WriteS(Tree_f, (STRING)" (yyt->", 7L);
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
        IO_WriteS(Tree_f, (STRING)"case k", 6L);
        Tree_WI(W_19->Name);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
        TreeC2_GetIterator(t);
        iClassName = W_19->Name;
        Tree_ForallAttributes(t, (Tree_ProcOfT)GetAttributes);
        if (TreeC2_Iterator == Tree_NoTree) {
          IO_WriteS(Tree_f, (STRING)"return;", 7L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"yyt = & ((* yyt)->", 18L);
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
      register Tree_yChild *W_20 = &t->U_1.V_9.Child;

      if (t != TreeC2_Iterator) {
        IO_WriteS(Tree_f, (STRING)"get", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" (& ((* yyt)->", 14L);
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
        IO_WriteS(Tree_f, (STRING)" ((* yyt)->", 11L);
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

void TreeC2_GetIterator
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
      register Tree_yClass *W_22 = &t->U_1.V_5.Class;

      TreeC2_Iterator = Tree_NoTree;
      RevChild = Tree_NoTree;
      Tree_ForallAttributes(t, (Tree_ProcOfT)TreeC2_GetIterator);
      if (RevChild != Tree_NoTree) {
        TreeC2_Iterator = RevChild;
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_23 = &t->U_1.V_9.Child;

      TreeC2_Iterator = t;
      if (IN(Tree_Reverse, W_23->Properties)) {
        RevChild = t;
      }
      return;
    }
    break;
  default :
    break;
  }
}

void TreeC2_BeginTreeC2
# ifdef __STDC__
()
# else
()
# endif
{
}

void TreeC2_CloseTreeC2
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

void TreeC2__init()
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

    TreeC2_yyf = IO_StdOutput;
    TreeC2_Exit = yyExit;
    TreeC2_BeginTreeC2();
  }
}
