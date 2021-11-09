#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
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

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Tree0
#include "Tree0.h"
#endif

Tree0_tTree0 Tree0_Tree0Root;
LONGCARD Tree0_HeapUsed;
ADDRESS Tree0_yyPoolFreePtr, Tree0_yyPoolMaxPtr;
struct Tree0_16 Tree0_yyNodeSize;
PROC Tree0_yyExit;

#define yyBlockSize   20480
typedef struct S_1 *yytBlockPtr;
typedef struct S_1 {
    struct S_2 {
        CHAR A[yyBlockSize - 1 + 1];
    } yyBlock;
    yytBlockPtr yySuccessor;
} yytBlock;
static yytBlockPtr yyBlockList;
static SHORTCARD yyMaxSize, yyi;
static struct S_3 {
    SHORTCARD A[13 + 1];
} yyTypeRange;
typedef Tree0_tTree0 *yyPtrtTree;
static IO_tFile yyf;
static SHORTCARD yyLabel;
static SHORTCARD yyKind;
static CHAR yyc;
static Strings_tString yys;
static void yyMark ARGS((Tree0_tTree0 yyt));
#define yyInitTreeStoreSize   32
static LONGINT yyTreeStoreSize;
static struct S_4 {
    Tree0_tTree0 A[50000 + 1];
} *yyTreeStorePtr;
static INTEGER yyLabelCount;
static SHORTINT yyRecursionLevel;
static SHORTCARD yyMapToLabel ARGS((Tree0_tTree0 yyTree));
static Tree0_tTree0 yyMapToTree ARGS((SHORTCARD yyLabel));
static void yyWriteNl ARGS(());
static void yyWriteSelector ARGS((CHAR yys[], LONGCARD ));
static void yyWriteHex ARGS((BYTE yyx[], LONGCARD ));
static SHORTINT yyIndentLevel;
static SHORTINT yyActualIndent, yyIndentQuotient, yyIndentRemainder;
#define yyIndentFactor   20
static void yySetIndentInfo ARGS(());
static void yyIndentSelector ARGS((CHAR yys[], LONGCARD ));
static void yyIndentSelectorTree ARGS((CHAR yys[], LONGCARD , Tree0_tTree0 yyt));
static void yWriteNode ARGS((Tree0_tTree0 yyt));
static void yWriteNode1 ARGS((Tree0_tTree0 yyt));
static void yWriteOption ARGS((Tree0_tTree0 yyt));
static void yWriteRepetition ARGS((Tree0_tTree0 yyt));
static void yWriteNode2 ARGS((Tree0_tTree0 yyt));
static void yWriteList ARGS((Tree0_tTree0 yyt));
static void yWriteSequence ARGS((Tree0_tTree0 yyt));
static void yWriteAlternative ARGS((Tree0_tTree0 yyt));
static void yWriteCh ARGS((Tree0_tTree0 yyt));
static void yWriteSet ARGS((Tree0_tTree0 yyt));
static void yWriteString ARGS((Tree0_tTree0 yyt));
static void yWriteRule ARGS((Tree0_tTree0 yyt));
static void yWritePattern ARGS((Tree0_tTree0 yyt));
static void yyWriteTree0 ARGS((Tree0_tTree0 yyt));
#define yyNil   ((CHAR)'\374')
#define yyNoLabel   ((CHAR)'\375')
#define yyLabelDef   ((CHAR)'\376')
#define yyLabelUse   ((CHAR)'\377')
static Tree0_tProcTree yyProc;
static void yyTraverseTree0TD ARGS((Tree0_tTree0 yyt));
static void xxExit ARGS(());


Tree0_tTree0 Tree0_yyAlloc
# ifdef __STDC__
()
# else
()
# endif
{
  yytBlockPtr yyBlockPtr;

  yyBlockPtr = yyBlockList;
  yyBlockList = (yytBlockPtr)Memory_Alloc((LONGINT)sizeof(yytBlock));
  yyBlockList->yySuccessor = yyBlockPtr;
  Tree0_yyPoolFreePtr = ADR(yyBlockList->yyBlock);
  Tree0_yyPoolMaxPtr = (ADDRESS)(Tree0_yyPoolFreePtr + yyBlockSize - yyMaxSize + 1);
  INC1(Tree0_HeapUsed, yyBlockSize);
  return (Tree0_tTree0)Tree0_yyPoolFreePtr;
}

Tree0_tTree0 Tree0_MakeTree0
# ifdef __STDC__
(SHORTCARD yyKind)
# else
(yyKind)
SHORTCARD yyKind;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[yyKind]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = yyKind;
  return yyt;
}

BOOLEAN Tree0_IsType
# ifdef __STDC__
(Tree0_tTree0 yyTree, SHORTCARD yyKind)
# else
(yyTree, yyKind)
Tree0_tTree0 yyTree;
SHORTCARD yyKind;
# endif
{
  return yyTree != Tree0_NoTree0 && yyKind <= yyTree->U_1.V_1.Kind && yyTree->U_1.V_1.Kind <= yyTypeRange.A[yyKind];
}

Tree0_tTree0 Tree0_mNode
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Node]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Node;
  {
    register Tree0_yNode *W_1 = &yyt->U_1.V_3.Node;

  }
  return yyt;
}

Tree0_tTree0 Tree0_mNode1
# ifdef __STDC__
(Tree0_tTree0 pSon1)
# else
(pSon1)
Tree0_tTree0 pSon1;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Node1]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Node1;
  {
    register Tree0_yNode1 *W_2 = &yyt->U_1.V_4.Node1;

    W_2->Son1 = pSon1;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mOption
# ifdef __STDC__
(Tree0_tTree0 pSon1)
# else
(pSon1)
Tree0_tTree0 pSon1;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Option]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Option;
  {
    register Tree0_yOption *W_3 = &yyt->U_1.V_5.Option;

    W_3->Son1 = pSon1;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mRepetition
# ifdef __STDC__
(Tree0_tTree0 pSon1)
# else
(pSon1)
Tree0_tTree0 pSon1;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Repetition]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Repetition;
  {
    register Tree0_yRepetition *W_4 = &yyt->U_1.V_6.Repetition;

    W_4->Son1 = pSon1;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mNode2
# ifdef __STDC__
(Tree0_tTree0 pSon1, Tree0_tTree0 pSon2)
# else
(pSon1, pSon2)
Tree0_tTree0 pSon1;
Tree0_tTree0 pSon2;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Node2]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Node2;
  {
    register Tree0_yNode2 *W_5 = &yyt->U_1.V_7.Node2;

    W_5->Son1 = pSon1;
    W_5->Son2 = pSon2;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mList
# ifdef __STDC__
(Tree0_tTree0 pSon1, Tree0_tTree0 pSon2)
# else
(pSon1, pSon2)
Tree0_tTree0 pSon1;
Tree0_tTree0 pSon2;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_List]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_List;
  {
    register Tree0_yList *W_6 = &yyt->U_1.V_8.List;

    W_6->Son1 = pSon1;
    W_6->Son2 = pSon2;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mSequence
# ifdef __STDC__
(Tree0_tTree0 pSon1, Tree0_tTree0 pSon2)
# else
(pSon1, pSon2)
Tree0_tTree0 pSon1;
Tree0_tTree0 pSon2;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Sequence]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Sequence;
  {
    register Tree0_ySequence *W_7 = &yyt->U_1.V_9.Sequence;

    W_7->Son1 = pSon1;
    W_7->Son2 = pSon2;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mAlternative
# ifdef __STDC__
(Tree0_tTree0 pSon1, Tree0_tTree0 pSon2)
# else
(pSon1, pSon2)
Tree0_tTree0 pSon1;
Tree0_tTree0 pSon2;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Alternative]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Alternative;
  {
    register Tree0_yAlternative *W_8 = &yyt->U_1.V_10.Alternative;

    W_8->Son1 = pSon1;
    W_8->Son2 = pSon2;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mCh
# ifdef __STDC__
(CHAR pCh)
# else
(pCh)
CHAR pCh;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Ch]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Ch;
  {
    register Tree0_yCh *W_9 = &yyt->U_1.V_11.Ch;

    W_9->Ch = pCh;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mSet
# ifdef __STDC__
(Sets_tSet pSet)
# else
(pSet)
Sets_tSet pSet;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Set]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Set;
  {
    register Tree0_ySet *W_10 = &yyt->U_1.V_12.Set;

    W_10->Set = pSet;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mString
# ifdef __STDC__
(StringMem_tStringRef pString)
# else
(pString)
StringMem_tStringRef pString;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_String]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_String;
  {
    register Tree0_yString *W_11 = &yyt->U_1.V_13.String;

    W_11->String = pString;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mRule
# ifdef __STDC__
(Tree0_tTree0 pPatterns, Texts_tText pTargetCode, SHORTCARD pLine, SHORTCARD pCodeMode, SHORTCARD pRuleNr)
# else
(pPatterns, pTargetCode, pLine, pCodeMode, pRuleNr)
Tree0_tTree0 pPatterns;
Texts_tText pTargetCode;
SHORTCARD pLine;
SHORTCARD pCodeMode;
SHORTCARD pRuleNr;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Rule]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Rule;
  {
    register Tree0_yRule *W_12 = &yyt->U_1.V_14.Rule;

    W_12->Patterns = pPatterns;
    W_12->TargetCode = pTargetCode;
    W_12->Line = pLine;
    W_12->CodeMode = pCodeMode;
    W_12->RuleNr = pRuleNr;
  }
  return yyt;
}

Tree0_tTree0 Tree0_mPattern
# ifdef __STDC__
(Sets_tSet pStartStates, Tree0_tTree0 pRegExpr, Tree0_tTree0 pRightContext, SHORTCARD pPatternNr, Positions_tPosition pPosition)
# else
(pStartStates, pRegExpr, pRightContext, pPatternNr, pPosition)
Sets_tSet pStartStates;
Tree0_tTree0 pRegExpr;
Tree0_tTree0 pRightContext;
SHORTCARD pPatternNr;
Positions_tPosition pPosition;
# endif
{
  LONGINT yyByteCount;
  Tree0_tTree0 yyt;

  yyt = (Tree0_tTree0)Tree0_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree0_yyPoolMaxPtr) {
    yyt = Tree0_yyAlloc();
  }
  INC1(Tree0_yyPoolFreePtr, Tree0_yyNodeSize.A[Tree0_Pattern]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree0_Pattern;
  {
    register Tree0_yPattern *W_13 = &yyt->U_1.V_15.Pattern;

    W_13->StartStates = pStartStates;
    W_13->RegExpr = pRegExpr;
    W_13->RightContext = pRightContext;
    W_13->PatternNr = pPatternNr;
    W_13->Position = pPosition;
  }
  return yyt;
}

static void yyMark
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  for (;;) {
    if (yyt == Tree0_NoTree0) {
      return;
    }
    INC(yyt->U_1.V_2.yyHead.yyMark);
    if (yyt->U_1.V_2.yyHead.yyMark > 1) {
      return;
    }
    switch (yyt->U_1.V_1.Kind) {
    case Tree0_Node1:;
      yyt = yyt->U_1.V_4.Node1.Son1;
      break;
    case Tree0_Option:;
      yyt = yyt->U_1.V_5.Option.Son1;
      break;
    case Tree0_Repetition:;
      yyt = yyt->U_1.V_6.Repetition.Son1;
      break;
    case Tree0_Node2:;
      yyMark(yyt->U_1.V_7.Node2.Son1);
      yyt = yyt->U_1.V_7.Node2.Son2;
      break;
    case Tree0_List:;
      yyMark(yyt->U_1.V_8.List.Son1);
      yyt = yyt->U_1.V_8.List.Son2;
      break;
    case Tree0_Sequence:;
      yyMark(yyt->U_1.V_9.Sequence.Son1);
      yyt = yyt->U_1.V_9.Sequence.Son2;
      break;
    case Tree0_Alternative:;
      yyMark(yyt->U_1.V_10.Alternative.Son1);
      yyt = yyt->U_1.V_10.Alternative.Son2;
      break;
    case Tree0_Rule:;
      yyt = yyt->U_1.V_14.Rule.Patterns;
      break;
    case Tree0_Pattern:;
      yyMark(yyt->U_1.V_15.Pattern.RegExpr);
      yyt = yyt->U_1.V_15.Pattern.RightContext;
      break;
    default :
      return;
      break;
    }
  } EXIT_1:;
}

static SHORTCARD yyMapToLabel
# ifdef __STDC__
(Tree0_tTree0 yyTree)
# else
(yyTree)
Tree0_tTree0 yyTree;
# endif
{
  INTEGER yyi;

  {
    LONGINT B_1 = 1, B_2 = yyLabelCount;

    if (B_1 <= B_2)
      for (yyi = B_1;; yyi += 1) {
        if (yyTreeStorePtr->A[yyi] == yyTree) {
          return yyi;
        }
        if (yyi >= B_2) break;
      }
  }
  INC(yyLabelCount);
  if (yyLabelCount == yyTreeStoreSize) {
    DynArray_ExtendArray((ADDRESS *)&yyTreeStorePtr, &yyTreeStoreSize, (LONGINT)sizeof(Tree0_tTree0));
  }
  yyTreeStorePtr->A[yyLabelCount] = yyTree;
  return yyLabelCount;
}

static Tree0_tTree0 yyMapToTree
# ifdef __STDC__
(SHORTCARD yyLabel)
# else
(yyLabel)
SHORTCARD yyLabel;
# endif
{
  return yyTreeStorePtr->A[yyLabel];
}

static void yyWriteNl
# ifdef __STDC__
()
# else
()
# endif
{
  IO_WriteNl(yyf);
}

static void yyWriteSelector
# ifdef __STDC__
(CHAR yys[], LONGCARD O_1)
# else
(yys, O_1)
CHAR yys[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yys, O_1, CHAR)
  IO_WriteS(yyf, yys, O_1);
  Layout_WriteSpaces(yyf, 15 - (INTEGER)(O_1 - 1));
  IO_WriteS(yyf, (STRING)" = ", 3L);
  FREE_OPEN_ARRAYS
}

static void yyWriteHex
# ifdef __STDC__
(BYTE yyx[], LONGCARD O_2)
# else
(yyx, O_2)
BYTE yyx[];
LONGCARD O_2;
# endif
{
  INTEGER yyi;

  {
    LONGINT B_3 = 0, B_4 = (INTEGER)(O_2 - 1);

    if (B_3 <= B_4)
      for (yyi = B_3;; yyi += 1) {
        IO_WriteN(yyf, ORD((CHAR)yyx[yyi]), 2L, 16L);
        IO_WriteC(yyf, ' ');
        if (yyi >= B_4) break;
      }
  }
}

static void yySetIndentInfo
# ifdef __STDC__
()
# else
()
# endif
{
  yyIndentQuotient = yyIndentLevel / yyIndentFactor;
  yyIndentRemainder = yyIndentLevel % yyIndentFactor;
  yyActualIndent = VAL(SHORTINT, 10 * ORD(yyIndentQuotient > 0)) + yyIndentRemainder;
}

void Tree0_WriteTree0
# ifdef __STDC__
(IO_tFile yyyf, Tree0_tTree0 yyt)
# else
(yyyf, yyt)
IO_tFile yyyf;
Tree0_tTree0 yyt;
# endif
{
  SHORTINT yySaveLevel;

  yyf = yyyf;
  if (yyRecursionLevel == 0) {
    yyLabelCount = 0;
  }
  INC(yyRecursionLevel);
  yyMark(yyt);
  yySaveLevel = yyIndentLevel;
  yyIndentLevel = 0;
  yySetIndentInfo();
  yyWriteTree0(yyt);
  yyIndentLevel = yySaveLevel;
  yySetIndentInfo();
  DEC(yyRecursionLevel);
}

static void yyIndentSelector
# ifdef __STDC__
(CHAR yys[], LONGCARD O_3)
# else
(yys, O_3)
CHAR yys[];
LONGCARD O_3;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yys, O_3, CHAR)
  if (yyIndentQuotient > 0) {
    IO_WriteC(yyf, '(');
    IO_WriteC(yyf, '*');
    IO_WriteN(yyf, (LONGCARD)(yyIndentQuotient * yyIndentFactor), 6L, 10L);
    IO_WriteC(yyf, '*');
    IO_WriteC(yyf, ')');
    Layout_WriteSpaces(yyf, (LONGINT)yyIndentRemainder);
  } else {
    Layout_WriteSpaces(yyf, (LONGINT)yyIndentRemainder);
  }
  yyWriteSelector(yys, O_3);
  FREE_OPEN_ARRAYS
}

static void yyIndentSelectorTree
# ifdef __STDC__
(CHAR yys[], LONGCARD O_4, Tree0_tTree0 yyt)
# else
(yys, O_4, yyt)
CHAR yys[];
LONGCARD O_4;
Tree0_tTree0 yyt;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yys, O_4, CHAR)
  yyIndentSelector(yys, O_4);
  yyWriteTree0(yyt);
  FREE_OPEN_ARRAYS
}

static void yWriteNode
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Node", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_3.Node.Tree, (LONGCARD)sizeof(yyt->U_1.V_3.Node.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_3.Node.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_3.Node.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_3.Node.NodeCount, 0L);
  yyWriteNl();
}

static void yWriteNode1
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Node1", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_4.Node1.Tree, (LONGCARD)sizeof(yyt->U_1.V_4.Node1.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_4.Node1.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_4.Node1.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_4.Node1.NodeCount, 0L);
  yyWriteNl();
}

static void yWriteOption
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Option", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_5.Option.Tree, (LONGCARD)sizeof(yyt->U_1.V_5.Option.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_5.Option.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Option.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Option.NodeCount, 0L);
  yyWriteNl();
}

static void yWriteRepetition
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Repetition", 10L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_6.Repetition.Tree, (LONGCARD)sizeof(yyt->U_1.V_6.Repetition.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_6.Repetition.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_6.Repetition.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_6.Repetition.NodeCount, 0L);
  yyWriteNl();
}

static void yWriteNode2
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Node2", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_7.Node2.Tree, (LONGCARD)sizeof(yyt->U_1.V_7.Node2.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_7.Node2.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_7.Node2.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_7.Node2.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Son1", 4L, yyt->U_1.V_7.Node2.Son1);
}

static void yWriteList
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"List", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_8.List.Tree, (LONGCARD)sizeof(yyt->U_1.V_8.List.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_8.List.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_8.List.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_8.List.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Son1", 4L, yyt->U_1.V_8.List.Son1);
}

static void yWriteSequence
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Sequence", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_9.Sequence.Tree, (LONGCARD)sizeof(yyt->U_1.V_9.Sequence.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_9.Sequence.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Sequence.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Sequence.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Son1", 4L, yyt->U_1.V_9.Sequence.Son1);
}

static void yWriteAlternative
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Alternative", 11L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_10.Alternative.Tree, (LONGCARD)sizeof(yyt->U_1.V_10.Alternative.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_10.Alternative.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_10.Alternative.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_10.Alternative.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Son1", 4L, yyt->U_1.V_10.Alternative.Son1);
}

static void yWriteCh
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Ch", 2L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_11.Ch.Tree, (LONGCARD)sizeof(yyt->U_1.V_11.Ch.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_11.Ch.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_11.Ch.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_11.Ch.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"Ch", 2L);
  IO_WriteC(yyf, yyt->U_1.V_11.Ch.Ch);
  yyWriteNl();
}

static void yWriteSet
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Set", 3L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_12.Set.Tree, (LONGCARD)sizeof(yyt->U_1.V_12.Set.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_12.Set.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_12.Set.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_12.Set.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"Set", 3L);
  Sets_WriteSet(yyf, yyt->U_1.V_12.Set.Set);
  yyWriteNl();
  yyIndentSelector((STRING)"card", 4L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_12.Set.card, 0L);
  yyWriteNl();
}

static void yWriteString
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"String", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_13.String.Tree, (LONGCARD)sizeof(yyt->U_1.V_13.String.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_13.String.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_13.String.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_13.String.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"String", 6L);
  StringMem_WriteString(yyf, yyt->U_1.V_13.String.String);
  yyWriteNl();
}

static void yWriteRule
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Rule", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_14.Rule.Tree, (LONGCARD)sizeof(yyt->U_1.V_14.Rule.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_14.Rule.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_14.Rule.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_14.Rule.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"TargetCode", 10L);
  Texts_WriteText(yyf, yyt->U_1.V_14.Rule.TargetCode);
  yyWriteNl();
  yyIndentSelector((STRING)"Line", 4L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_14.Rule.Line, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"CodeMode", 8L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_14.Rule.CodeMode, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"RuleNr", 6L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_14.Rule.RuleNr, 0L);
  yyWriteNl();
}

static void yWritePattern
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Pattern", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"Tree", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_15.Pattern.Tree, (LONGCARD)sizeof(yyt->U_1.V_15.Pattern.Tree));
  yyWriteNl();
  yyIndentSelector((STRING)"IsConstantRE", 12L);
  IO_WriteB(yyf, yyt->U_1.V_15.Pattern.IsConstantRE);
  yyWriteNl();
  yyIndentSelector((STRING)"LeafCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_15.Pattern.LeafCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"NodeCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_15.Pattern.NodeCount, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"StartStates", 11L);
  Sets_WriteSet(yyf, yyt->U_1.V_15.Pattern.StartStates);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"RegExpr", 7L, yyt->U_1.V_15.Pattern.RegExpr);
  yyIndentSelector((STRING)"PatternNr", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_15.Pattern.PatternNr, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"Position", 8L);
  Positions_WritePosition(yyf, yyt->U_1.V_15.Pattern.Position);
  yyWriteNl();
  yyIndentSelector((STRING)"card", 4L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_15.Pattern.card, 0L);
  yyWriteNl();
}

static void yyWriteTree0
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  SHORTCARD yyLevel;

  yyLevel = yyIndentLevel;
  for (;;) {
    if (yyt == Tree0_NoTree0) {
      IO_WriteS(yyf, (STRING)" NoTree0", 8L);
      yyWriteNl();
      goto EXIT_2;
    } else if (yyt->U_1.V_2.yyHead.yyMark == 0) {
      IO_WriteC(yyf, '^');
      IO_WriteI(yyf, (LONGINT)yyMapToLabel(yyt), 0L);
      yyWriteNl();
      goto EXIT_2;
    } else if (yyt->U_1.V_2.yyHead.yyMark > 1) {
      yyWriteNl();
      IO_WriteN(yyf, (LONGCARD)yyMapToLabel(yyt), 6L, 10L);
      IO_WriteC(yyf, ':');
      Layout_WriteSpaces(yyf, (LONGINT)(yyActualIndent - 7));
    } else {
      IO_WriteC(yyf, ' ');
    }
    yyt->U_1.V_2.yyHead.yyMark = 0;
    INC1(yyIndentLevel, 2);
    yySetIndentInfo();
    switch (yyt->U_1.V_1.Kind) {
    case Tree0_Node:;
      yWriteNode(yyt);
      goto EXIT_2;
      break;
    case Tree0_Node1:;
      yWriteNode1(yyt);
      yyIndentSelector((STRING)"Son1", 4L);
      yyt = yyt->U_1.V_4.Node1.Son1;
      break;
    case Tree0_Option:;
      yWriteOption(yyt);
      yyIndentSelector((STRING)"Son1", 4L);
      yyt = yyt->U_1.V_5.Option.Son1;
      break;
    case Tree0_Repetition:;
      yWriteRepetition(yyt);
      yyIndentSelector((STRING)"Son1", 4L);
      yyt = yyt->U_1.V_6.Repetition.Son1;
      break;
    case Tree0_Node2:;
      yWriteNode2(yyt);
      yyIndentSelector((STRING)"Son2", 4L);
      yyt = yyt->U_1.V_7.Node2.Son2;
      break;
    case Tree0_List:;
      yWriteList(yyt);
      yyIndentSelector((STRING)"Son2", 4L);
      yyt = yyt->U_1.V_8.List.Son2;
      break;
    case Tree0_Sequence:;
      yWriteSequence(yyt);
      yyIndentSelector((STRING)"Son2", 4L);
      yyt = yyt->U_1.V_9.Sequence.Son2;
      break;
    case Tree0_Alternative:;
      yWriteAlternative(yyt);
      yyIndentSelector((STRING)"Son2", 4L);
      yyt = yyt->U_1.V_10.Alternative.Son2;
      break;
    case Tree0_Ch:;
      yWriteCh(yyt);
      goto EXIT_2;
      break;
    case Tree0_Set:;
      yWriteSet(yyt);
      goto EXIT_2;
      break;
    case Tree0_String:;
      yWriteString(yyt);
      goto EXIT_2;
      break;
    case Tree0_Rule:;
      yWriteRule(yyt);
      yyIndentSelector((STRING)"Patterns", 8L);
      yyt = yyt->U_1.V_14.Rule.Patterns;
      break;
    case Tree0_Pattern:;
      yWritePattern(yyt);
      yyIndentSelector((STRING)"RightContext", 12L);
      yyt = yyt->U_1.V_15.Pattern.RightContext;
      break;
    default :
      goto EXIT_2;
      break;
    }
  } EXIT_2:;
  yyIndentLevel = yyLevel;
  yySetIndentInfo();
}

void Tree0_ReleaseTree0Module
# ifdef __STDC__
()
# else
()
# endif
{
  yytBlockPtr yyBlockPtr;

  while (yyBlockList != NIL) {
    yyBlockPtr = yyBlockList;
    yyBlockList = yyBlockList->yySuccessor;
    Memory_Free((LONGINT)sizeof(yytBlock), (ADDRESS)yyBlockPtr);
  }
  Tree0_yyPoolFreePtr = (ADDRESS)NIL;
  Tree0_yyPoolMaxPtr = (ADDRESS)NIL;
  Tree0_HeapUsed = 0;
}

void Tree0_TraverseTree0TD
# ifdef __STDC__
(Tree0_tTree0 yyt, Tree0_tProcTree yyyProc)
# else
(yyt, yyyProc)
Tree0_tTree0 yyt;
Tree0_tProcTree yyyProc;
# endif
{
  yyMark(yyt);
  yyProc = yyyProc;
  yyTraverseTree0TD(yyt);
}

static void yyTraverseTree0TD
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  for (;;) {
    if (yyt == Tree0_NoTree0 || yyt->U_1.V_2.yyHead.yyMark == 0) {
      return;
    }
    yyt->U_1.V_2.yyHead.yyMark = 0;
    (*yyProc)(yyt);
    switch (yyt->U_1.V_1.Kind) {
    case Tree0_Node1:;
      yyt = yyt->U_1.V_4.Node1.Son1;
      break;
    case Tree0_Option:;
      yyt = yyt->U_1.V_5.Option.Son1;
      break;
    case Tree0_Repetition:;
      yyt = yyt->U_1.V_6.Repetition.Son1;
      break;
    case Tree0_Node2:;
      yyTraverseTree0TD(yyt->U_1.V_7.Node2.Son1);
      yyt = yyt->U_1.V_7.Node2.Son2;
      break;
    case Tree0_List:;
      yyTraverseTree0TD(yyt->U_1.V_8.List.Son1);
      yyt = yyt->U_1.V_8.List.Son2;
      break;
    case Tree0_Sequence:;
      yyTraverseTree0TD(yyt->U_1.V_9.Sequence.Son1);
      yyt = yyt->U_1.V_9.Sequence.Son2;
      break;
    case Tree0_Alternative:;
      yyTraverseTree0TD(yyt->U_1.V_10.Alternative.Son1);
      yyt = yyt->U_1.V_10.Alternative.Son2;
      break;
    case Tree0_Rule:;
      yyt = yyt->U_1.V_14.Rule.Patterns;
      break;
    case Tree0_Pattern:;
      yyTraverseTree0TD(yyt->U_1.V_15.Pattern.RegExpr);
      yyt = yyt->U_1.V_15.Pattern.RightContext;
      break;
    default :
      return;
      break;
    }
  } EXIT_3:;
}

void Tree0_BeginTree0
# ifdef __STDC__
()
# else
()
# endif
{
}

void Tree0_CloseTree0
# ifdef __STDC__
()
# else
()
# endif
{
}

static void xxExit
# ifdef __STDC__
()
# else
()
# endif
{
  IO_CloseIO();
  Exit(1L);
}

void Tree0__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Sets__init();
    Texts__init();
    StringMem__init();
    Positions__init();
    Tree__init();
    System__init();
    General__init();
    Memory__init();
    DynArray__init();
    IO__init();
    Layout__init();
    StringMem__init();
    Strings__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Positions__init();
    Sets__init();
    Texts__init();
    StringMem__init();
    Positions__init();

    yyBlockList = NIL;
    Tree0_yyPoolFreePtr = (ADDRESS)NIL;
    Tree0_yyPoolMaxPtr = (ADDRESS)NIL;
    Tree0_HeapUsed = 0;
    Tree0_yyExit = xxExit;
    Tree0_yyNodeSize.A[Tree0_Node] = sizeof(Tree0_yNode);
    Tree0_yyNodeSize.A[Tree0_Node1] = sizeof(Tree0_yNode1);
    Tree0_yyNodeSize.A[Tree0_Option] = sizeof(Tree0_yOption);
    Tree0_yyNodeSize.A[Tree0_Repetition] = sizeof(Tree0_yRepetition);
    Tree0_yyNodeSize.A[Tree0_Node2] = sizeof(Tree0_yNode2);
    Tree0_yyNodeSize.A[Tree0_List] = sizeof(Tree0_yList);
    Tree0_yyNodeSize.A[Tree0_Sequence] = sizeof(Tree0_ySequence);
    Tree0_yyNodeSize.A[Tree0_Alternative] = sizeof(Tree0_yAlternative);
    Tree0_yyNodeSize.A[Tree0_Ch] = sizeof(Tree0_yCh);
    Tree0_yyNodeSize.A[Tree0_Set] = sizeof(Tree0_ySet);
    Tree0_yyNodeSize.A[Tree0_String] = sizeof(Tree0_yString);
    Tree0_yyNodeSize.A[Tree0_Rule] = sizeof(Tree0_yRule);
    Tree0_yyNodeSize.A[Tree0_Pattern] = sizeof(Tree0_yPattern);
    yyMaxSize = 0;
    for (yyi = 1; yyi <= 13; yyi += 1) {
      Tree0_yyNodeSize.A[yyi] = (LONGINT)((BITSET)(Tree0_yyNodeSize.A[yyi] + (CARDINAL)General_MaxAlign - 1) & General_AlignMasks.A[General_MaxAlign]);
      yyMaxSize = General_Max((LONGINT)Tree0_yyNodeSize.A[yyi], (LONGINT)yyMaxSize);
    }
    yyTypeRange.A[Tree0_Node] = Tree0_Pattern;
    yyTypeRange.A[Tree0_Node1] = Tree0_Repetition;
    yyTypeRange.A[Tree0_Option] = Tree0_Option;
    yyTypeRange.A[Tree0_Repetition] = Tree0_Repetition;
    yyTypeRange.A[Tree0_Node2] = Tree0_Alternative;
    yyTypeRange.A[Tree0_List] = Tree0_List;
    yyTypeRange.A[Tree0_Sequence] = Tree0_Sequence;
    yyTypeRange.A[Tree0_Alternative] = Tree0_Alternative;
    yyTypeRange.A[Tree0_Ch] = Tree0_Ch;
    yyTypeRange.A[Tree0_Set] = Tree0_Set;
    yyTypeRange.A[Tree0_String] = Tree0_String;
    yyTypeRange.A[Tree0_Rule] = Tree0_Rule;
    yyTypeRange.A[Tree0_Pattern] = Tree0_Pattern;
    yyRecursionLevel = 0;
    yyTreeStoreSize = yyInitTreeStoreSize;
    DynArray_MakeArray((ADDRESS *)&yyTreeStorePtr, &yyTreeStoreSize, (LONGINT)sizeof(Tree0_tTree0));
    Tree0_BeginTree0();
  }
}
