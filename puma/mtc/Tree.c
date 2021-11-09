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

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
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

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

CARDINAL Tree_ErrorCount;
Sets_tSet Tree_Options;
IO_tFile Tree_f;
struct Tree_1 Tree_SourceFile;
BITSET Tree_NoCodeAttr, Tree_NoCodeClass;
Tree_tTree Tree_TreeRoot;
LONGCARD Tree_HeapUsed;
ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
struct Tree_117 Tree_yyNodeSize;
PROC Tree_yyExit;

#define Backslash   '\\'
static struct S_3 {
    Tree_tTree A[1000000 + 1];
} *IdentToClassPtr;
static LONGINT IdentToClassSize;
static Idents_tIdent sIdentToClassSize;
#define yyBlockSize   20480
typedef struct S_1 *yytBlockPtr;
typedef struct S_1 {
    struct S_4 {
        CHAR A[yyBlockSize - 1 + 1];
    } yyBlock;
    yytBlockPtr yySuccessor;
} yytBlock;
static yytBlockPtr yyBlockList;
static SHORTCARD yyMaxSize, yyi;
static struct S_5 {
    SHORTCARD A[138 + 1];
} yyTypeRange;
typedef Tree_tTree *yyPtrtTree;
static IO_tFile yyf;
static SHORTCARD yyLabel;
static SHORTCARD yyKind;
static CHAR yyc;
static Strings_tString yys;
static void yyMark ARGS((Tree_tTree yyt));
#define yyInitTreeStoreSize   32
static LONGINT yyTreeStoreSize;
static struct S_6 {
    Tree_tTree A[50000 + 1];
} *yyTreeStorePtr;
static INTEGER yyLabelCount;
static SHORTINT yyRecursionLevel;
static SHORTCARD yyMapToLabel ARGS((Tree_tTree yyTree));
static Tree_tTree yyMapToTree ARGS((SHORTCARD yyLabel));
static void yyWriteNl ARGS(());
static void yyWriteSelector ARGS((CHAR yys[], LONGCARD ));
static void yyWriteHex ARGS((BYTE yyx[], LONGCARD ));
static void yyWriteAdr ARGS((Tree_tTree yyt));
static void yyyWriteNodeClass ARGS((Tree_tTree yyt));
static void yyyWriteNodeAttrOrAction ARGS((Tree_tTree yyt));
static void yyyWriteNodeChild ARGS((Tree_tTree yyt));
static void yyyWriteNodeAttribute ARGS((Tree_tTree yyt));
static void yyyWriteNodeActionPart ARGS((Tree_tTree yyt));
static void yyyWriteNodeCodes ARGS((Tree_tTree yyt));
static void yyyWriteNodeDesignator ARGS((Tree_tTree yyt));
static void yyyWriteNodeIdent ARGS((Tree_tTree yyt));
static void yyyWriteNodeRemote ARGS((Tree_tTree yyt));
static void yyyWriteNodeAny ARGS((Tree_tTree yyt));
static void yyyWriteNodeAnys ARGS((Tree_tTree yyt));
static void yyyWriteNodeLayoutAny ARGS((Tree_tTree yyt));
static void yyyWriteNodeName ARGS((Tree_tTree yyt));
static void yyyWriteNodeSpec ARGS((Tree_tTree yyt));
static void yyyWriteNodeTreeName ARGS((Tree_tTree yyt));
static void yyyWriteNodeRoutine ARGS((Tree_tTree yyt));
static void yyyWriteNodeProcedure ARGS((Tree_tTree yyt));
static void yyyWriteNodeFunction ARGS((Tree_tTree yyt));
static void yyyWriteNodePredicate ARGS((Tree_tTree yyt));
static void yyyWriteNodeParam ARGS((Tree_tTree yyt));
static void yyyWriteNodeType ARGS((Tree_tTree yyt));
static void yyyWriteNodeRule ARGS((Tree_tTree yyt));
static void yyyWriteNodeNoPattern ARGS((Tree_tTree yyt));
static void yyyWriteNodeOnePattern ARGS((Tree_tTree yyt));
static void yyyWriteNodeOnePatternAlts ARGS((Tree_tTree yyt));
static void yyyWriteNodeOnePatternsList ARGS((Tree_tTree yyt));
static void yyyWriteNodePattern ARGS((Tree_tTree yyt));
static void yyyWriteNodeDecompose ARGS((Tree_tTree yyt));
static void yyyWriteNodeVarDef ARGS((Tree_tTree yyt));
static void yyyWriteNodeNilTest ARGS((Tree_tTree yyt));
static void yyyWriteNodeDontCare1 ARGS((Tree_tTree yyt));
static void yyyWriteNodeDontCare1Explicit ARGS((Tree_tTree yyt));
static void yyyWriteNodeDontCare1Internal ARGS((Tree_tTree yyt));
static void yyyWriteNodeDontCare ARGS((Tree_tTree yyt));
static void yyyWriteNodeDontCareExplicit ARGS((Tree_tTree yyt));
static void yyyWriteNodeDontCareInternal ARGS((Tree_tTree yyt));
static void yyyWriteNodeValue ARGS((Tree_tTree yyt));
static void yyyWriteNodeNoExpr ARGS((Tree_tTree yyt));
static void yyyWriteNodeOneExpr ARGS((Tree_tTree yyt));
static void yyyWriteNodeNamedExpr ARGS((Tree_tTree yyt));
static void yyyWriteNodeExpr ARGS((Tree_tTree yyt));
static void yyyWriteNodeCompose ARGS((Tree_tTree yyt));
static void yyyWriteNodeVarUse ARGS((Tree_tTree yyt));
static void yyyWriteNodeAttrDesc ARGS((Tree_tTree yyt));
static void yyyWriteNodeNil ARGS((Tree_tTree yyt));
static void yyyWriteNodeCall ARGS((Tree_tTree yyt));
static void yyyWriteNodeBinary ARGS((Tree_tTree yyt));
static void yyyWriteNodeyy1 ARGS((Tree_tTree yyt));
static void yyyWriteNodeBinaryCompound ARGS((Tree_tTree yyt));
static void yyyWriteNodePreOperator ARGS((Tree_tTree yyt));
static void yyyWriteNodePostOperator ARGS((Tree_tTree yyt));
static void yyyWriteNodeIndex ARGS((Tree_tTree yyt));
static void yyyWriteNodeParents ARGS((Tree_tTree yyt));
static void yyyWriteNodeTargetExpr ARGS((Tree_tTree yyt));
static void yyyWriteNodeStringExpr ARGS((Tree_tTree yyt));
static void yyyWriteNodeStatement ARGS((Tree_tTree yyt));
static void yyyWriteNodeProcCall ARGS((Tree_tTree yyt));
static void yyyWriteNodeCondition ARGS((Tree_tTree yyt));
static void yyyWriteNodeAssignment ARGS((Tree_tTree yyt));
static void yyyWriteNodeReject ARGS((Tree_tTree yyt));
static void yyyWriteNodeFail ARGS((Tree_tTree yyt));
static void yyyWriteNodeTargetStmt ARGS((Tree_tTree yyt));
static void yyyWriteNodeNl ARGS((Tree_tTree yyt));
static void yyyWriteNodeWriteStr ARGS((Tree_tTree yyt));
static void yyyWriteNodeFormal ARGS((Tree_tTree yyt));
static void yyyWriteNodePlainFormal ARGS((Tree_tTree yyt));
static void yyyWriteNodeRoutineFormal ARGS((Tree_tTree yyt));
static void yyyWriteNodeDummyFormal ARGS((Tree_tTree yyt));
static void yyyWriteNodeNodeTypes ARGS((Tree_tTree yyt));
static void yyyWriteNodeUserType ARGS((Tree_tTree yyt));
static void yyyWriteNodeVar ARGS((Tree_tTree yyt));
static void yyyWriteNodeConsType ARGS((Tree_tTree yyt));
static void yyyWriteNodeField ARGS((Tree_tTree yyt));
static void yyyWriteNodeOneTest ARGS((Tree_tTree yyt));
static void yyyWriteNodeTestKind ARGS((Tree_tTree yyt));
static void yyyWriteNodeTestIsType ARGS((Tree_tTree yyt));
static void yyyWriteNodeTestNil ARGS((Tree_tTree yyt));
static void yyyWriteNodeTestNonlin ARGS((Tree_tTree yyt));
static void yyyWriteNodeTestValue ARGS((Tree_tTree yyt));
static void yyyWriteNodeDecision ARGS((Tree_tTree yyt));
static void yyyWriteNodeDecided ARGS((Tree_tTree yyt));
static SHORTINT yyIndentLevel;
static SHORTINT yyActualIndent, yyIndentQuotient, yyIndentRemainder;
#define yyIndentFactor   20
static void yySetIndentInfo ARGS(());
static void yyIndentSelector ARGS((CHAR yys[], LONGCARD ));
static void yyIndentSelectorTree ARGS((CHAR yys[], LONGCARD , Tree_tTree yyt));
static void yWriteClass ARGS((Tree_tTree yyt));
static void yWriteAttrOrAction ARGS((Tree_tTree yyt));
static void yWriteChild ARGS((Tree_tTree yyt));
static void yWriteAttribute ARGS((Tree_tTree yyt));
static void yWriteActionPart ARGS((Tree_tTree yyt));
static void yWriteCodes ARGS((Tree_tTree yyt));
static void yWriteDesignator ARGS((Tree_tTree yyt));
static void yWriteIdent ARGS((Tree_tTree yyt));
static void yWriteRemote ARGS((Tree_tTree yyt));
static void yWriteAny ARGS((Tree_tTree yyt));
static void yWriteAnys ARGS((Tree_tTree yyt));
static void yWriteLayoutAny ARGS((Tree_tTree yyt));
static void yWriteName ARGS((Tree_tTree yyt));
static void yWriteSpec ARGS((Tree_tTree yyt));
static void yWriteTreeName ARGS((Tree_tTree yyt));
static void yWriteRoutine ARGS((Tree_tTree yyt));
static void yWriteProcedure ARGS((Tree_tTree yyt));
static void yWriteFunction ARGS((Tree_tTree yyt));
static void yWritePredicate ARGS((Tree_tTree yyt));
static void yWriteParam ARGS((Tree_tTree yyt));
static void yWriteType ARGS((Tree_tTree yyt));
static void yWriteRule ARGS((Tree_tTree yyt));
static void yWriteNoPattern ARGS((Tree_tTree yyt));
static void yWriteOnePattern ARGS((Tree_tTree yyt));
static void yWriteOnePatternAlts ARGS((Tree_tTree yyt));
static void yWriteOnePatternsList ARGS((Tree_tTree yyt));
static void yWritePattern ARGS((Tree_tTree yyt));
static void yWriteDecompose ARGS((Tree_tTree yyt));
static void yWriteVarDef ARGS((Tree_tTree yyt));
static void yWriteNilTest ARGS((Tree_tTree yyt));
static void yWriteDontCare1 ARGS((Tree_tTree yyt));
static void yWriteDontCare1Explicit ARGS((Tree_tTree yyt));
static void yWriteDontCare1Internal ARGS((Tree_tTree yyt));
static void yWriteDontCare ARGS((Tree_tTree yyt));
static void yWriteDontCareExplicit ARGS((Tree_tTree yyt));
static void yWriteDontCareInternal ARGS((Tree_tTree yyt));
static void yWriteValue ARGS((Tree_tTree yyt));
static void yWriteNoExpr ARGS((Tree_tTree yyt));
static void yWriteOneExpr ARGS((Tree_tTree yyt));
static void yWriteNamedExpr ARGS((Tree_tTree yyt));
static void yWriteExpr ARGS((Tree_tTree yyt));
static void yWriteCompose ARGS((Tree_tTree yyt));
static void yWriteVarUse ARGS((Tree_tTree yyt));
static void yWriteAttrDesc ARGS((Tree_tTree yyt));
static void yWriteNil ARGS((Tree_tTree yyt));
static void yWriteCall ARGS((Tree_tTree yyt));
static void yWriteBinary ARGS((Tree_tTree yyt));
static void yWriteyy1 ARGS((Tree_tTree yyt));
static void yWriteBinaryCompound ARGS((Tree_tTree yyt));
static void yWritePreOperator ARGS((Tree_tTree yyt));
static void yWritePostOperator ARGS((Tree_tTree yyt));
static void yWriteIndex ARGS((Tree_tTree yyt));
static void yWriteParents ARGS((Tree_tTree yyt));
static void yWriteTargetExpr ARGS((Tree_tTree yyt));
static void yWriteStringExpr ARGS((Tree_tTree yyt));
static void yWriteStatement ARGS((Tree_tTree yyt));
static void yWriteProcCall ARGS((Tree_tTree yyt));
static void yWriteCondition ARGS((Tree_tTree yyt));
static void yWriteAssignment ARGS((Tree_tTree yyt));
static void yWriteReject ARGS((Tree_tTree yyt));
static void yWriteFail ARGS((Tree_tTree yyt));
static void yWriteTargetStmt ARGS((Tree_tTree yyt));
static void yWriteNl ARGS((Tree_tTree yyt));
static void yWriteWriteStr ARGS((Tree_tTree yyt));
static void yWriteFormal ARGS((Tree_tTree yyt));
static void yWritePlainFormal ARGS((Tree_tTree yyt));
static void yWriteRoutineFormal ARGS((Tree_tTree yyt));
static void yWriteDummyFormal ARGS((Tree_tTree yyt));
static void yWriteNodeTypes ARGS((Tree_tTree yyt));
static void yWriteUserType ARGS((Tree_tTree yyt));
static void yWriteVar ARGS((Tree_tTree yyt));
static void yWriteConsType ARGS((Tree_tTree yyt));
static void yWriteField ARGS((Tree_tTree yyt));
static void yWriteOneTest ARGS((Tree_tTree yyt));
static void yWriteTestKind ARGS((Tree_tTree yyt));
static void yWriteTestIsType ARGS((Tree_tTree yyt));
static void yWriteTestNil ARGS((Tree_tTree yyt));
static void yWriteTestNonlin ARGS((Tree_tTree yyt));
static void yWriteTestValue ARGS((Tree_tTree yyt));
static void yWriteDecision ARGS((Tree_tTree yyt));
static void yWriteDecided ARGS((Tree_tTree yyt));
static void yyWriteTree ARGS((Tree_tTree yyt));
#define yyNil   ((CHAR)'\374')
#define yyNoLabel   ((CHAR)'\375')
#define yyLabelDef   ((CHAR)'\376')
#define yyLabelUse   ((CHAR)'\377')
#define yyInitOldToNewStoreSize   32
typedef struct S_2 {
    Tree_tTree yyOld, yyNew;
} yytOldToNew;
static LONGINT yyOldToNewStoreSize;
static struct S_11 {
    yytOldToNew A[50000 + 1];
} *yyOldToNewStorePtr;
static INTEGER yyOldToNewCount;
static void yyStoreOldToNew ARGS((Tree_tTree yyOld, Tree_tTree yyNew));
static Tree_tTree yyMapOldToNew ARGS((Tree_tTree yyOld));
static void yyCopyTree ARGS((Tree_tTree yyt, yyPtrtTree yyNew));
#define yyyWrite   1
#define yyyRead   2
#define yyyQuit   3
static struct S_12 {
    CHAR A[31 + 1];
} yyString;
static INTEGER yyLength;
static CHAR yyCh;
static INTEGER yyState;
static BOOLEAN yyyIsEqual ARGS((CHAR yya[], LONGCARD ));
static void xxExit ARGS(());


void Tree_InitIdentifyClass
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  INTEGER i;

  IdentToClassSize = Idents_MaxIdent() + 1;
  sIdentToClassSize = IdentToClassSize;
  DynArray_MakeArray((ADDRESS *)&IdentToClassPtr, &IdentToClassSize, (LONGINT)sizeof(Tree_tTree));
  {
    LONGINT B_1 = 0, B_2 = IdentToClassSize - 1;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        IdentToClassPtr->A[i] = Tree_NoTree;
        if (i >= B_2) break;
      }
  }
  Tree_ForallClasses(t, (Tree_ProcOfT)Tree_InitIdentifyClass2);
}

void Tree_InitIdentifyClass2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  IdentToClassPtr->A[t->U_1.V_5.Class.Name] = t;
}

Tree_tTree Tree_IdentifyClass
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent Ident)
# else
(t, Ident)
Tree_tTree t;
Idents_tIdent Ident;
# endif
{
  if (Ident < sIdentToClassSize) {
    return IdentToClassPtr->A[Ident];
  }
  return Tree_NoTree;
}

Tree_tTree Tree_IdentifyAttribute
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent Ident)
# else
(t, Ident)
Tree_tTree t;
Idents_tIdent Ident;
# endif
{
  Tree_tTree attribute;

  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_Class:;
      attribute = Tree_IdentifyAttribute(t->U_1.V_5.Class.BaseClass, Ident);
      if (attribute != Tree_NoTree) {
        return attribute;
      }
      t = t->U_1.V_5.Class.Attributes;
      break;
    case Tree_Child:;
      if (t->U_1.V_9.Child.Name == Ident) {
        return t;
      }
      t = t->U_1.V_9.Child.Next;
      break;
    case Tree_Attribute:;
      if (t->U_1.V_10.Attribute.Name == Ident) {
        return t;
      }
      t = t->U_1.V_10.Attribute.Next;
      break;
    case Tree_ActionPart:;
      t = t->U_1.V_11.ActionPart.Next;
      break;
    default :
      return Tree_NoTree;
      break;
    }
  } EXIT_1:;
}

void Tree_ForallClasses
# ifdef __STDC__
(Tree_tTree t, Tree_ProcOfT Proc)
# else
(t, Proc)
Tree_tTree t;
Tree_ProcOfT Proc;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Class) {
    (*Proc)(t);
    Tree_ForallClasses(t->U_1.V_5.Class.Extensions, Proc);
    t = t->U_1.V_5.Class.Next;
  }
}

void Tree_ForallClassesExtensionsFirst
# ifdef __STDC__
(Tree_tTree t, Tree_ProcOfT Proc)
# else
(t, Proc)
Tree_tTree t;
Tree_ProcOfT Proc;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Class) {
    Tree_ForallClassesExtensionsFirst(t->U_1.V_5.Class.Extensions, Proc);
    (*Proc)(t);
    t = t->U_1.V_5.Class.Next;
  }
}

void Tree_ForallClassesPreAndPost
# ifdef __STDC__
(Tree_tTree t, Tree_ProcOfT PreProc, Tree_ProcOfT PostProc)
# else
(t, PreProc, PostProc)
Tree_tTree t;
Tree_ProcOfT PreProc, PostProc;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Class) {
    (*PreProc)(t);
    Tree_ForallClassesPreAndPost(t->U_1.V_5.Class.Extensions, PreProc, PostProc);
    (*PostProc)(t);
    t = t->U_1.V_5.Class.Next;
  }
}

void Tree_ForallAttributes
# ifdef __STDC__
(Tree_tTree t, Tree_ProcOfT Proc)
# else
(t, Proc)
Tree_tTree t;
Tree_ProcOfT Proc;
# endif
{
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_Class:;
      Tree_ForallAttributes(t->U_1.V_5.Class.BaseClass, Proc);
      t = t->U_1.V_5.Class.Attributes;
      break;
    case Tree_Child:;
      (*Proc)(t);
      t = t->U_1.V_9.Child.Next;
      break;
    case Tree_Attribute:;
      (*Proc)(t);
      t = t->U_1.V_10.Attribute.Next;
      break;
    case Tree_ActionPart:;
      (*Proc)(t);
      t = t->U_1.V_11.ActionPart.Next;
      break;
    default :
      return;
      break;
    }
  } EXIT_2:;
}

void Tree_Error
# ifdef __STDC__
(INTEGER ErrorCode, Positions_tPosition Pos)
# else
(ErrorCode, Pos)
INTEGER ErrorCode;
Positions_tPosition Pos;
# endif
{
  Errors_ErrorMessage((LONGCARD)ErrorCode, (LONGCARD)Errors_Error, Pos);
  INC(Tree_ErrorCount);
}

void Tree_Warning
# ifdef __STDC__
(INTEGER ErrorCode, Positions_tPosition Pos)
# else
(ErrorCode, Pos)
INTEGER ErrorCode;
Positions_tPosition Pos;
# endif
{
  Errors_ErrorMessage((LONGCARD)ErrorCode, (LONGCARD)Errors_Warning, Pos);
}

void Tree_Information
# ifdef __STDC__
(INTEGER ErrorCode, Positions_tPosition Pos)
# else
(ErrorCode, Pos)
INTEGER ErrorCode;
Positions_tPosition Pos;
# endif
{
  Errors_ErrorMessage((LONGCARD)ErrorCode, (LONGCARD)Errors_Information, Pos);
}

void Tree_ErrorI
# ifdef __STDC__
(INTEGER ErrorCode, Positions_tPosition Pos, INTEGER iClass, ADDRESS iPtr)
# else
(ErrorCode, Pos, iClass, iPtr)
INTEGER ErrorCode;
Positions_tPosition Pos;
INTEGER iClass;
ADDRESS iPtr;
# endif
{
  Errors_ErrorMessageI((LONGCARD)ErrorCode, (LONGCARD)Errors_Error, Pos, (LONGCARD)iClass, iPtr);
  INC(Tree_ErrorCount);
}

void Tree_WarningI
# ifdef __STDC__
(INTEGER ErrorCode, Positions_tPosition Pos, INTEGER iClass, ADDRESS iPtr)
# else
(ErrorCode, Pos, iClass, iPtr)
INTEGER ErrorCode;
Positions_tPosition Pos;
INTEGER iClass;
ADDRESS iPtr;
# endif
{
  Errors_ErrorMessageI((LONGCARD)ErrorCode, (LONGCARD)Errors_Warning, Pos, (LONGCARD)iClass, iPtr);
}

void Tree_InformationI
# ifdef __STDC__
(INTEGER ErrorCode, Positions_tPosition Pos, INTEGER iClass, ADDRESS iPtr)
# else
(ErrorCode, Pos, iClass, iPtr)
INTEGER ErrorCode;
Positions_tPosition Pos;
INTEGER iClass;
ADDRESS iPtr;
# endif
{
  Errors_ErrorMessageI((LONGCARD)ErrorCode, (LONGCARD)Errors_Information, Pos, (LONGCARD)iClass, iPtr);
}

void Tree_WI
# ifdef __STDC__
(Idents_tIdent i)
# else
(i)
Idents_tIdent i;
# endif
{
  Idents_WriteIdent(Tree_f, i);
}

void Tree_WE
# ifdef __STDC__
(Idents_tIdent i)
# else
(i)
Idents_tIdent i;
# endif
{
  Strings_tString s;
  CHAR Ch;
  SHORTCARD j;

  Idents_GetString(i, &s);
  {
    SHORTCARD B_3 = 1, B_4 = Strings_Length(&s);

    if (B_3 <= B_4)
      for (j = B_3;; j += 1) {
        Ch = Strings_Char(&s, j);
        if (Ch == '{' || Ch == '}' || Ch == Backslash) {
          IO_WriteC(Tree_f, Backslash);
        }
        IO_WriteC(Tree_f, Ch);
        if (j >= B_4) break;
      }
  }
}

void Tree_WN
# ifdef __STDC__
(INTEGER n)
# else
(n)
INTEGER n;
# endif
{
  IO_WriteI(Tree_f, n, 0L);
}

Tree_tTree Tree_yyAlloc
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
  Tree_yyPoolFreePtr = ADR(yyBlockList->yyBlock);
  Tree_yyPoolMaxPtr = (ADDRESS)(Tree_yyPoolFreePtr + yyBlockSize - yyMaxSize + 1);
  INC1(Tree_HeapUsed, yyBlockSize);
  return (Tree_tTree)Tree_yyPoolFreePtr;
}

Tree_tTree Tree_MakeTree
# ifdef __STDC__
(SHORTCARD yyKind)
# else
(yyKind)
SHORTCARD yyKind;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[yyKind]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = yyKind;
  return yyt;
}

BOOLEAN Tree_IsType
# ifdef __STDC__
(Tree_tTree yyTree, SHORTCARD yyKind)
# else
(yyTree, yyKind)
Tree_tTree yyTree;
SHORTCARD yyKind;
# endif
{
  return yyTree != Tree_NoTree && yyKind <= yyTree->U_1.V_1.Kind && yyTree->U_1.V_1.Kind <= yyTypeRange.A[yyKind];
}

Tree_tTree Tree_mClasses
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Classes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Classes;
  return yyt;
}

Tree_tTree Tree_mNoClass
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoClass]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoClass;
  return yyt;
}

Tree_tTree Tree_mClass
# ifdef __STDC__
(Idents_tIdent pName, Tree_tClassProperties pProperties, Tree_tTree pAttributes, Tree_tTree pExtensions, Tree_tTree pNext)
# else
(pName, pProperties, pAttributes, pExtensions, pNext)
Idents_tIdent pName;
Tree_tClassProperties pProperties;
Tree_tTree pAttributes;
Tree_tTree pExtensions;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Class]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Class;
  {
    register Tree_yClass *W_1 = &yyt->U_1.V_5.Class;

    W_1->Name = pName;
    W_1->Properties = pProperties;
    W_1->Attributes = pAttributes;
    W_1->Extensions = pExtensions;
    W_1->Next = pNext;
    W_1->BaseClass = Tree_NoTree;
    W_1->Formals = Tree_NoTree;
    W_1->TypeDesc = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mAttributes
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Attributes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Attributes;
  return yyt;
}

Tree_tTree Tree_mNoAttribute
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoAttribute]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoAttribute;
  return yyt;
}

Tree_tTree Tree_mAttrOrAction
# ifdef __STDC__
(Tree_tTree pNext)
# else
(pNext)
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_AttrOrAction]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_AttrOrAction;
  {
    register Tree_yAttrOrAction *W_2 = &yyt->U_1.V_8.AttrOrAction;

    W_2->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mChild
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties)
# else
(pNext, pName, pType, pProperties)
Tree_tTree pNext;
Idents_tIdent pName;
Idents_tIdent pType;
Tree_tAttrProperties pProperties;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Child]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Child;
  {
    register Tree_yChild *W_3 = &yyt->U_1.V_9.Child;

    W_3->Next = pNext;
    W_3->Name = pName;
    W_3->Type = pType;
    W_3->Properties = pProperties;
  }
  return yyt;
}

Tree_tTree Tree_mAttribute
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties)
# else
(pNext, pName, pType, pProperties)
Tree_tTree pNext;
Idents_tIdent pName;
Idents_tIdent pType;
Tree_tAttrProperties pProperties;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Attribute]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Attribute;
  {
    register Tree_yAttribute *W_4 = &yyt->U_1.V_10.Attribute;

    W_4->Next = pNext;
    W_4->Name = pName;
    W_4->Type = pType;
    W_4->Properties = pProperties;
  }
  return yyt;
}

Tree_tTree Tree_mActionPart
# ifdef __STDC__
(Tree_tTree pNext)
# else
(pNext)
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_ActionPart]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_ActionPart;
  {
    register Tree_yActionPart *W_5 = &yyt->U_1.V_11.ActionPart;

    W_5->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mCodes
# ifdef __STDC__
(Texts_tText pExport, Texts_tText pImport, Texts_tText pGlobal, Texts_tText pSpecWith, Texts_tText pBodyWith, Texts_tText pLocal, Texts_tText pBegin, Texts_tText pClose, Positions_tPosition pExportLine, Positions_tPosition pImportLine, Positions_tPosition pGlobalLine, Positions_tPosition pSpecWithLine, Positions_tPosition pBodyWithLine, Positions_tPosition pLocalLine, Positions_tPosition pBeginLine, Positions_tPosition pCloseLine)
# else
(pExport, pImport, pGlobal, pSpecWith, pBodyWith, pLocal, pBegin, pClose, pExportLine, pImportLine, pGlobalLine, pSpecWithLine, pBodyWithLine, pLocalLine, pBeginLine, pCloseLine)
Texts_tText pExport;
Texts_tText pImport;
Texts_tText pGlobal;
Texts_tText pSpecWith;
Texts_tText pBodyWith;
Texts_tText pLocal;
Texts_tText pBegin;
Texts_tText pClose;
Positions_tPosition pExportLine;
Positions_tPosition pImportLine;
Positions_tPosition pGlobalLine;
Positions_tPosition pSpecWithLine;
Positions_tPosition pBodyWithLine;
Positions_tPosition pLocalLine;
Positions_tPosition pBeginLine;
Positions_tPosition pCloseLine;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Codes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Codes;
  {
    register Tree_yCodes *W_6 = &yyt->U_1.V_12.Codes;

    W_6->Export = pExport;
    W_6->Import = pImport;
    W_6->Global = pGlobal;
    W_6->SpecWith = pSpecWith;
    W_6->BodyWith = pBodyWith;
    W_6->Local = pLocal;
    W_6->Begin = pBegin;
    W_6->Close = pClose;
    W_6->ExportLine = pExportLine;
    W_6->ImportLine = pImportLine;
    W_6->GlobalLine = pGlobalLine;
    W_6->SpecWithLine = pSpecWithLine;
    W_6->BodyWithLine = pBodyWithLine;
    W_6->LocalLine = pLocalLine;
    W_6->BeginLine = pBeginLine;
    W_6->CloseLine = pCloseLine;
  }
  return yyt;
}

Tree_tTree Tree_mDesignators
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Designators]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Designators;
  return yyt;
}

Tree_tTree Tree_mNoDesignator
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoDesignator]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoDesignator;
  return yyt;
}

Tree_tTree Tree_mDesignator
# ifdef __STDC__
(Idents_tIdent pSelector, Idents_tIdent pAttribute, Positions_tPosition pPos, Positions_tPosition pAttributePos, Tree_tTree pNext)
# else
(pSelector, pAttribute, pPos, pAttributePos, pNext)
Idents_tIdent pSelector;
Idents_tIdent pAttribute;
Positions_tPosition pPos;
Positions_tPosition pAttributePos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Designator]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Designator;
  {
    register Tree_yDesignator *W_7 = &yyt->U_1.V_15.Designator;

    W_7->Selector = pSelector;
    W_7->Attribute = pAttribute;
    W_7->Pos = pPos;
    W_7->AttributePos = pAttributePos;
    W_7->Next = pNext;
    W_7->Type = Idents_NoIdent;
  }
  return yyt;
}

Tree_tTree Tree_mIdent
# ifdef __STDC__
(Idents_tIdent pAttribute, Positions_tPosition pPos, Tree_tTree pNext)
# else
(pAttribute, pPos, pNext)
Idents_tIdent pAttribute;
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Ident]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Ident;
  {
    register Tree_yIdent *W_8 = &yyt->U_1.V_16.Ident;

    W_8->Attribute = pAttribute;
    W_8->Pos = pPos;
    W_8->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mRemote
# ifdef __STDC__
(Tree_tTree pDesignators, Idents_tIdent pType, Idents_tIdent pAttribute, Positions_tPosition pPos, Tree_tTree pNext)
# else
(pDesignators, pType, pAttribute, pPos, pNext)
Tree_tTree pDesignators;
Idents_tIdent pType;
Idents_tIdent pAttribute;
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Remote]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Remote;
  {
    register Tree_yRemote *W_9 = &yyt->U_1.V_17.Remote;

    W_9->Designators = pDesignators;
    W_9->Type = pType;
    W_9->Attribute = pAttribute;
    W_9->Pos = pPos;
    W_9->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mAny
# ifdef __STDC__
(StringMem_tStringRef pCode, Tree_tTree pNext)
# else
(pCode, pNext)
StringMem_tStringRef pCode;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Any]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Any;
  {
    register Tree_yAny *W_10 = &yyt->U_1.V_18.Any;

    W_10->Code = pCode;
    W_10->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mAnys
# ifdef __STDC__
(Tree_tTree pLayouts, Tree_tTree pNext)
# else
(pLayouts, pNext)
Tree_tTree pLayouts;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Anys]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Anys;
  {
    register Tree_yAnys *W_11 = &yyt->U_1.V_19.Anys;

    W_11->Layouts = pLayouts;
    W_11->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mLayouts
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Layouts]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Layouts;
  return yyt;
}

Tree_tTree Tree_mNoLayout
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoLayout]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoLayout;
  return yyt;
}

Tree_tTree Tree_mLayoutAny
# ifdef __STDC__
(StringMem_tStringRef pCode, Tree_tTree pNext)
# else
(pCode, pNext)
StringMem_tStringRef pCode;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_LayoutAny]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_LayoutAny;
  {
    register Tree_yLayoutAny *W_12 = &yyt->U_1.V_22.LayoutAny;

    W_12->Code = pCode;
    W_12->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mNames
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Names]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Names;
  return yyt;
}

Tree_tTree Tree_mNoName
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoName]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoName;
  return yyt;
}

Tree_tTree Tree_mName
# ifdef __STDC__
(Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pNext)
# else
(pName, pPos, pNext)
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Name]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Name;
  {
    register Tree_yName *W_13 = &yyt->U_1.V_25.Name;

    W_13->Name = pName;
    W_13->Pos = pPos;
    W_13->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mSpec
# ifdef __STDC__
(Idents_tIdent pTrafoName, Tree_tTree pTreeNames, Tree_tTree pPublic, Tree_tTree pExtern, Tree_tTree pCodes, Tree_tTree pRoutines)
# else
(pTrafoName, pTreeNames, pPublic, pExtern, pCodes, pRoutines)
Idents_tIdent pTrafoName;
Tree_tTree pTreeNames;
Tree_tTree pPublic;
Tree_tTree pExtern;
Tree_tTree pCodes;
Tree_tTree pRoutines;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Spec]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Spec;
  {
    register Tree_ySpec *W_14 = &yyt->U_1.V_26.Spec;

    W_14->TrafoName = pTrafoName;
    W_14->TreeNames = pTreeNames;
    W_14->Public = pPublic;
    W_14->Extern = pExtern;
    W_14->Codes = pCodes;
    W_14->Routines = pRoutines;
  }
  return yyt;
}

Tree_tTree Tree_mTreeNames
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TreeNames]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TreeNames;
  return yyt;
}

Tree_tTree Tree_mNoTreeName
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoTreeName]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoTreeName;
  return yyt;
}

Tree_tTree Tree_mTreeName
# ifdef __STDC__
(Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pNext)
# else
(pName, pPos, pNext)
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TreeName]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TreeName;
  {
    register Tree_yTreeName *W_15 = &yyt->U_1.V_29.TreeName;

    W_15->Name = pName;
    W_15->Pos = pPos;
    W_15->Next = pNext;
    W_15->Classes = Tree_NoTree;
    W_15->EmptyType = Tree_NoTree;
    W_15->UniversalClass = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mRoutines
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Routines]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Routines;
  return yyt;
}

Tree_tTree Tree_mNoRoutine
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoRoutine]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoRoutine;
  return yyt;
}

Tree_tTree Tree_mRoutine
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules)
# else
(pNext, pName, pPos, pInParams, pOutParams, pExtern, pLocal, pLocalLine, pRules)
Tree_tTree pNext;
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pInParams;
Tree_tTree pOutParams;
Tree_tTree pExtern;
Texts_tText pLocal;
Positions_tPosition pLocalLine;
Tree_tTree pRules;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Routine]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Routine;
  {
    register Tree_yRoutine *W_16 = &yyt->U_1.V_32.Routine;

    W_16->Next = pNext;
    W_16->Name = pName;
    W_16->Pos = pPos;
    W_16->InParams = pInParams;
    W_16->OutParams = pOutParams;
    W_16->Extern = pExtern;
    W_16->Local = pLocal;
    W_16->LocalLine = pLocalLine;
    W_16->Rules = pRules;
    W_16->InForm = Tree_NoTree;
    W_16->OutForm = Tree_NoTree;
    W_16->ParamDecls = Tree_NoTree;
    W_16->IsExtern = FALSE;
    W_16->Decisions = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mProcedure
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules)
# else
(pNext, pName, pPos, pInParams, pOutParams, pExtern, pLocal, pLocalLine, pRules)
Tree_tTree pNext;
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pInParams;
Tree_tTree pOutParams;
Tree_tTree pExtern;
Texts_tText pLocal;
Positions_tPosition pLocalLine;
Tree_tTree pRules;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Procedure]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Procedure;
  {
    register Tree_yProcedure *W_17 = &yyt->U_1.V_33.Procedure;

    W_17->Next = pNext;
    W_17->Name = pName;
    W_17->Pos = pPos;
    W_17->InParams = pInParams;
    W_17->OutParams = pOutParams;
    W_17->Extern = pExtern;
    W_17->Local = pLocal;
    W_17->LocalLine = pLocalLine;
    W_17->Rules = pRules;
    W_17->InForm = Tree_NoTree;
    W_17->OutForm = Tree_NoTree;
    W_17->ParamDecls = Tree_NoTree;
    W_17->IsExtern = FALSE;
    W_17->Decisions = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mFunction
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules, Tree_tTree pReturnParams)
# else
(pNext, pName, pPos, pInParams, pOutParams, pExtern, pLocal, pLocalLine, pRules, pReturnParams)
Tree_tTree pNext;
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pInParams;
Tree_tTree pOutParams;
Tree_tTree pExtern;
Texts_tText pLocal;
Positions_tPosition pLocalLine;
Tree_tTree pRules;
Tree_tTree pReturnParams;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Function]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Function;
  {
    register Tree_yFunction *W_18 = &yyt->U_1.V_34.Function;

    W_18->Next = pNext;
    W_18->Name = pName;
    W_18->Pos = pPos;
    W_18->InParams = pInParams;
    W_18->OutParams = pOutParams;
    W_18->Extern = pExtern;
    W_18->Local = pLocal;
    W_18->LocalLine = pLocalLine;
    W_18->Rules = pRules;
    W_18->InForm = Tree_NoTree;
    W_18->OutForm = Tree_NoTree;
    W_18->ParamDecls = Tree_NoTree;
    W_18->IsExtern = FALSE;
    W_18->Decisions = Tree_NoTree;
    W_18->ReturnParams = pReturnParams;
    W_18->ReturnForm = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mPredicate
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules)
# else
(pNext, pName, pPos, pInParams, pOutParams, pExtern, pLocal, pLocalLine, pRules)
Tree_tTree pNext;
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pInParams;
Tree_tTree pOutParams;
Tree_tTree pExtern;
Texts_tText pLocal;
Positions_tPosition pLocalLine;
Tree_tTree pRules;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Predicate]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Predicate;
  {
    register Tree_yPredicate *W_19 = &yyt->U_1.V_35.Predicate;

    W_19->Next = pNext;
    W_19->Name = pName;
    W_19->Pos = pPos;
    W_19->InParams = pInParams;
    W_19->OutParams = pOutParams;
    W_19->Extern = pExtern;
    W_19->Local = pLocal;
    W_19->LocalLine = pLocalLine;
    W_19->Rules = pRules;
    W_19->InForm = Tree_NoTree;
    W_19->OutForm = Tree_NoTree;
    W_19->ParamDecls = Tree_NoTree;
    W_19->IsExtern = FALSE;
    W_19->Decisions = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mParameters
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Parameters]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Parameters;
  return yyt;
}

Tree_tTree Tree_mNoParameter
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoParameter]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoParameter;
  return yyt;
}

Tree_tTree Tree_mParam
# ifdef __STDC__
(BOOLEAN pIsRef, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pType, Tree_tTree pNext)
# else
(pIsRef, pName, pPos, pType, pNext)
BOOLEAN pIsRef;
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pType;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Param]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Param;
  {
    register Tree_yParam *W_20 = &yyt->U_1.V_38.Param;

    W_20->IsRef = pIsRef;
    W_20->Name = pName;
    W_20->Pos = pPos;
    W_20->Type = pType;
    W_20->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mType
# ifdef __STDC__
(Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pNames)
# else
(pName, pPos, pNames)
Idents_tIdent pName;
Positions_tPosition pPos;
Tree_tTree pNames;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Type]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Type;
  {
    register Tree_yType *W_21 = &yyt->U_1.V_39.Type;

    W_21->Name = pName;
    W_21->Pos = pPos;
    W_21->Names = pNames;
  }
  return yyt;
}

Tree_tTree Tree_mRules
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Rules]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Rules;
  return yyt;
}

Tree_tTree Tree_mNoRule
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoRule]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoRule;
  return yyt;
}

Tree_tTree Tree_mRule
# ifdef __STDC__
(Positions_tPosition pLine, Tree_tTree pPatterns, Tree_tTree pExprs, Tree_tTree pExpr, Tree_tTree pStatements, Tree_tTree pNext)
# else
(pLine, pPatterns, pExprs, pExpr, pStatements, pNext)
Positions_tPosition pLine;
Tree_tTree pPatterns;
Tree_tTree pExprs;
Tree_tTree pExpr;
Tree_tTree pStatements;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Rule]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Rule;
  {
    register Tree_yRule *W_22 = &yyt->U_1.V_42.Rule;

    W_22->Line = pLine;
    W_22->Patterns = pPatterns;
    W_22->Exprs = pExprs;
    W_22->Expr = pExpr;
    W_22->Statements = pStatements;
    W_22->Next = pNext;
    W_22->VarDecls = Tree_NoTree;
    W_22->HasTempos = FALSE;
    W_22->HasPatterns = FALSE;
    W_22->Tempo = Idents_NoIdent;
    W_22->Tests = Tree_NoTree;
    W_22->HasExit = FALSE;
    W_22->HasAssign = FALSE;
    W_22->HasTargetCode = FALSE;
    W_22->HasRejectOrFail = FALSE;
  }
  return yyt;
}

Tree_tTree Tree_mPatterns
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Patterns]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Patterns;
  return yyt;
}

Tree_tTree Tree_mNoPattern
# ifdef __STDC__
(Positions_tPosition pPos)
# else
(pPos)
Positions_tPosition pPos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoPattern]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoPattern;
  {
    register Tree_yNoPattern *W_23 = &yyt->U_1.V_44.NoPattern;

    W_23->Pos = pPos;
  }
  return yyt;
}

Tree_tTree Tree_mOnePattern
# ifdef __STDC__
(Tree_tTree pPattern, Tree_tTree pNext)
# else
(pPattern, pNext)
Tree_tTree pPattern;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_OnePattern]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_OnePattern;
  {
    register Tree_yOnePattern *W_24 = &yyt->U_1.V_45.OnePattern;

    W_24->Pattern = pPattern;
    W_24->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mOnePatternAlts
# ifdef __STDC__
(Tree_tTree pPatternsList, Tree_tTree pNext, Tree_tTree pCurrent)
# else
(pPatternsList, pNext, pCurrent)
Tree_tTree pPatternsList;
Tree_tTree pNext;
Tree_tTree pCurrent;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_OnePatternAlts]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_OnePatternAlts;
  {
    register Tree_yOnePatternAlts *W_25 = &yyt->U_1.V_46.OnePatternAlts;

    W_25->PatternsList = pPatternsList;
    W_25->Next = pNext;
    W_25->Current = pCurrent;
  }
  return yyt;
}

Tree_tTree Tree_mPatternsList
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_PatternsList]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_PatternsList;
  return yyt;
}

Tree_tTree Tree_mNoPatternsList
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoPatternsList]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoPatternsList;
  return yyt;
}

Tree_tTree Tree_mOnePatternsList
# ifdef __STDC__
(Tree_tTree pPatterns, Tree_tTree pNext)
# else
(pPatterns, pNext)
Tree_tTree pPatterns;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_OnePatternsList]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_OnePatternsList;
  {
    register Tree_yOnePatternsList *W_26 = &yyt->U_1.V_49.OnePatternsList;

    W_26->Patterns = pPatterns;
    W_26->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mPattern
# ifdef __STDC__
(Positions_tPosition pPos)
# else
(pPos)
Positions_tPosition pPos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Pattern]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Pattern;
  {
    register Tree_yPattern *W_27 = &yyt->U_1.V_50.Pattern;

    W_27->Pos = pPos;
    W_27->Tempo = Idents_NoIdent;
    W_27->TypeDesc = Tree_NoTree;
    W_27->Path = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mDecompose
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pPatterns, BOOLEAN pWiden)
# else
(pPos, pSelector, pExpr, pPatterns, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pExpr;
Tree_tTree pPatterns;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decompose]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Decompose;
  {
    register Tree_yDecompose *W_28 = &yyt->U_1.V_51.Decompose;

    W_28->Pos = pPos;
    W_28->Tempo = Idents_NoIdent;
    W_28->TypeDesc = Tree_NoTree;
    W_28->Path = Tree_NoTree;
    W_28->Selector = pSelector;
    W_28->Expr = pExpr;
    W_28->Patterns = pPatterns;
    W_28->Widen = pWiden;
    W_28->IsProperlyNarrowed = FALSE;
  }
  return yyt;
}

Tree_tTree Tree_mVarDef
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, BOOLEAN pHasDelimiter)
# else
(pPos, pSelector, pHasDelimiter)
Positions_tPosition pPos;
Idents_tIdent pSelector;
BOOLEAN pHasDelimiter;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_VarDef]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_VarDef;
  {
    register Tree_yVarDef *W_29 = &yyt->U_1.V_52.VarDef;

    W_29->Pos = pPos;
    W_29->Tempo = Idents_NoIdent;
    W_29->TypeDesc = Tree_NoTree;
    W_29->Path = Tree_NoTree;
    W_29->Selector = pSelector;
    W_29->HasDelimiter = pHasDelimiter;
  }
  return yyt;
}

Tree_tTree Tree_mNilTest
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, BOOLEAN pWiden)
# else
(pPos, pSelector, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NilTest]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NilTest;
  {
    register Tree_yNilTest *W_30 = &yyt->U_1.V_53.NilTest;

    W_30->Pos = pPos;
    W_30->Tempo = Idents_NoIdent;
    W_30->TypeDesc = Tree_NoTree;
    W_30->Path = Tree_NoTree;
    W_30->Selector = pSelector;
    W_30->Widen = pWiden;
    W_30->IsProperlyNarrowed = FALSE;
  }
  return yyt;
}

Tree_tTree Tree_mDontCare1
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector)
# else
(pPos, pSelector)
Positions_tPosition pPos;
Idents_tIdent pSelector;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_DontCare1]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_DontCare1;
  {
    register Tree_yDontCare1 *W_31 = &yyt->U_1.V_54.DontCare1;

    W_31->Pos = pPos;
    W_31->Tempo = Idents_NoIdent;
    W_31->TypeDesc = Tree_NoTree;
    W_31->Path = Tree_NoTree;
    W_31->Selector = pSelector;
  }
  return yyt;
}

Tree_tTree Tree_mDontCare1Explicit
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector)
# else
(pPos, pSelector)
Positions_tPosition pPos;
Idents_tIdent pSelector;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_DontCare1Explicit]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_DontCare1Explicit;
  {
    register Tree_yDontCare1Explicit *W_32 = &yyt->U_1.V_55.DontCare1Explicit;

    W_32->Pos = pPos;
    W_32->Tempo = Idents_NoIdent;
    W_32->TypeDesc = Tree_NoTree;
    W_32->Path = Tree_NoTree;
    W_32->Selector = pSelector;
  }
  return yyt;
}

Tree_tTree Tree_mDontCare1Internal
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector)
# else
(pPos, pSelector)
Positions_tPosition pPos;
Idents_tIdent pSelector;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_DontCare1Internal]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_DontCare1Internal;
  {
    register Tree_yDontCare1Internal *W_33 = &yyt->U_1.V_56.DontCare1Internal;

    W_33->Pos = pPos;
    W_33->Tempo = Idents_NoIdent;
    W_33->TypeDesc = Tree_NoTree;
    W_33->Path = Tree_NoTree;
    W_33->Selector = pSelector;
  }
  return yyt;
}

Tree_tTree Tree_mDontCare
# ifdef __STDC__
(Positions_tPosition pPos)
# else
(pPos)
Positions_tPosition pPos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_DontCare]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_DontCare;
  {
    register Tree_yDontCare *W_34 = &yyt->U_1.V_57.DontCare;

    W_34->Pos = pPos;
    W_34->Tempo = Idents_NoIdent;
    W_34->TypeDesc = Tree_NoTree;
    W_34->Path = Tree_NoTree;
    W_34->Tempos = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mDontCareExplicit
# ifdef __STDC__
(Positions_tPosition pPos)
# else
(pPos)
Positions_tPosition pPos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_DontCareExplicit]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_DontCareExplicit;
  {
    register Tree_yDontCareExplicit *W_35 = &yyt->U_1.V_58.DontCareExplicit;

    W_35->Pos = pPos;
    W_35->Tempo = Idents_NoIdent;
    W_35->TypeDesc = Tree_NoTree;
    W_35->Path = Tree_NoTree;
    W_35->Tempos = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mDontCareInternal
# ifdef __STDC__
(Positions_tPosition pPos)
# else
(pPos)
Positions_tPosition pPos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_DontCareInternal]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_DontCareInternal;
  {
    register Tree_yDontCareInternal *W_36 = &yyt->U_1.V_59.DontCareInternal;

    W_36->Pos = pPos;
    W_36->Tempo = Idents_NoIdent;
    W_36->TypeDesc = Tree_NoTree;
    W_36->Path = Tree_NoTree;
    W_36->Tempos = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mValue
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr)
# else
(pPos, pSelector, pExpr)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pExpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Value]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Value;
  {
    register Tree_yValue *W_37 = &yyt->U_1.V_60.Value;

    W_37->Pos = pPos;
    W_37->Tempo = Idents_NoIdent;
    W_37->TypeDesc = Tree_NoTree;
    W_37->Path = Tree_NoTree;
    W_37->Selector = pSelector;
    W_37->Expr = pExpr;
  }
  return yyt;
}

Tree_tTree Tree_mExprs
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Exprs]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Exprs;
  return yyt;
}

Tree_tTree Tree_mNoExpr
# ifdef __STDC__
(Positions_tPosition pPos)
# else
(pPos)
Positions_tPosition pPos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoExpr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoExpr;
  {
    register Tree_yNoExpr *W_38 = &yyt->U_1.V_62.NoExpr;

    W_38->Pos = pPos;
  }
  return yyt;
}

Tree_tTree Tree_mOneExpr
# ifdef __STDC__
(Tree_tTree pExpr, Tree_tTree pNext)
# else
(pExpr, pNext)
Tree_tTree pExpr;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_OneExpr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_OneExpr;
  {
    register Tree_yOneExpr *W_39 = &yyt->U_1.V_63.OneExpr;

    W_39->Expr = pExpr;
    W_39->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mNamedExpr
# ifdef __STDC__
(Tree_tTree pExpr, Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pNamePos)
# else
(pExpr, pNext, pName, pNamePos)
Tree_tTree pExpr;
Tree_tTree pNext;
Idents_tIdent pName;
Positions_tPosition pNamePos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NamedExpr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NamedExpr;
  {
    register Tree_yNamedExpr *W_40 = &yyt->U_1.V_64.NamedExpr;

    W_40->Expr = pExpr;
    W_40->Next = pNext;
    W_40->Name = pName;
    W_40->NamePos = pNamePos;
  }
  return yyt;
}

Tree_tTree Tree_mExpr
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector)
# else
(pPos, pSelector)
Positions_tPosition pPos;
Idents_tIdent pSelector;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Expr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Expr;
  {
    register Tree_yExpr *W_41 = &yyt->U_1.V_65.Expr;

    W_41->Pos = pPos;
    W_41->Selector = pSelector;
  }
  return yyt;
}

Tree_tTree Tree_mCompose
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pExprs, BOOLEAN pWiden)
# else
(pPos, pSelector, pExpr, pExprs, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pExpr;
Tree_tTree pExprs;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Compose]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Compose;
  {
    register Tree_yCompose *W_42 = &yyt->U_1.V_66.Compose;

    W_42->Pos = pPos;
    W_42->Selector = pSelector;
    W_42->Expr = pExpr;
    W_42->Exprs = pExprs;
    W_42->Widen = pWiden;
    W_42->Tempo = Idents_NoIdent;
    W_42->TypeDesc = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mVarUse
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pName, BOOLEAN pWiden)
# else
(pPos, pSelector, pName, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Idents_tIdent pName;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_VarUse]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_VarUse;
  {
    register Tree_yVarUse *W_43 = &yyt->U_1.V_67.VarUse;

    W_43->Pos = pPos;
    W_43->Selector = pSelector;
    W_43->Name = pName;
    W_43->Widen = pWiden;
  }
  return yyt;
}

Tree_tTree Tree_mAttrDesc
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pName, BOOLEAN pWiden, Idents_tIdent pAttribute, Positions_tPosition pAttributePos)
# else
(pPos, pSelector, pName, pWiden, pAttribute, pAttributePos)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Idents_tIdent pName;
BOOLEAN pWiden;
Idents_tIdent pAttribute;
Positions_tPosition pAttributePos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_AttrDesc]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_AttrDesc;
  {
    register Tree_yAttrDesc *W_44 = &yyt->U_1.V_68.AttrDesc;

    W_44->Pos = pPos;
    W_44->Selector = pSelector;
    W_44->Name = pName;
    W_44->Widen = pWiden;
    W_44->Attribute = pAttribute;
    W_44->AttributePos = pAttributePos;
    W_44->Type = Idents_NoIdent;
  }
  return yyt;
}

Tree_tTree Tree_mNil
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, BOOLEAN pWiden)
# else
(pPos, pSelector, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Nil]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Nil;
  {
    register Tree_yNil *W_45 = &yyt->U_1.V_69.Nil;

    W_45->Pos = pPos;
    W_45->Selector = pSelector;
    W_45->Widen = pWiden;
  }
  return yyt;
}

Tree_tTree Tree_mCall
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pExprs, Tree_tTree pPatterns)
# else
(pPos, pSelector, pExpr, pExprs, pPatterns)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pExpr;
Tree_tTree pExprs;
Tree_tTree pPatterns;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Call]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Call;
  {
    register Tree_yCall *W_46 = &yyt->U_1.V_70.Call;

    W_46->Pos = pPos;
    W_46->Selector = pSelector;
    W_46->Expr = pExpr;
    W_46->Exprs = pExprs;
    W_46->Patterns = pPatterns;
  }
  return yyt;
}

Tree_tTree Tree_mBinary
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pLop, Idents_tIdent pOperator, Tree_tTree pRop, BOOLEAN pWiden)
# else
(pPos, pSelector, pLop, pOperator, pRop, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pLop;
Idents_tIdent pOperator;
Tree_tTree pRop;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Binary]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Binary;
  {
    register Tree_yBinary *W_47 = &yyt->U_1.V_71.Binary;

    W_47->Pos = pPos;
    W_47->Selector = pSelector;
    W_47->Lop = pLop;
    W_47->Operator = pOperator;
    W_47->Rop = pRop;
    W_47->Widen = pWiden;
  }
  return yyt;
}

Tree_tTree Tree_myy1
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pLop, Idents_tIdent pOperator, Tree_tTree pRop, BOOLEAN pWiden)
# else
(pPos, pSelector, pLop, pOperator, pRop, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pLop;
Idents_tIdent pOperator;
Tree_tTree pRop;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_yy1]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_yy1;
  {
    register Tree_yyy1 *W_48 = &yyt->U_1.V_72.yy1;

    W_48->Pos = pPos;
    W_48->Selector = pSelector;
    W_48->Lop = pLop;
    W_48->Operator = pOperator;
    W_48->Rop = pRop;
    W_48->Widen = pWiden;
  }
  return yyt;
}

Tree_tTree Tree_mBinaryCompound
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pLop, Idents_tIdent pOperator, Tree_tTree pRop, BOOLEAN pWiden, Idents_tIdent pCompoundOperator)
# else
(pPos, pSelector, pLop, pOperator, pRop, pWiden, pCompoundOperator)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pLop;
Idents_tIdent pOperator;
Tree_tTree pRop;
BOOLEAN pWiden;
Idents_tIdent pCompoundOperator;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_BinaryCompound]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_BinaryCompound;
  {
    register Tree_yBinaryCompound *W_49 = &yyt->U_1.V_73.BinaryCompound;

    W_49->Pos = pPos;
    W_49->Selector = pSelector;
    W_49->Lop = pLop;
    W_49->Operator = pOperator;
    W_49->Rop = pRop;
    W_49->Widen = pWiden;
    W_49->CompoundOperator = pCompoundOperator;
  }
  return yyt;
}

Tree_tTree Tree_mPreOperator
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pOperator, Tree_tTree pExpr)
# else
(pPos, pSelector, pOperator, pExpr)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Idents_tIdent pOperator;
Tree_tTree pExpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_PreOperator]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_PreOperator;
  {
    register Tree_yPreOperator *W_50 = &yyt->U_1.V_74.PreOperator;

    W_50->Pos = pPos;
    W_50->Selector = pSelector;
    W_50->Operator = pOperator;
    W_50->Expr = pExpr;
  }
  return yyt;
}

Tree_tTree Tree_mPostOperator
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pOperator, Tree_tTree pExpr)
# else
(pPos, pSelector, pOperator, pExpr)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Idents_tIdent pOperator;
Tree_tTree pExpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_PostOperator]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_PostOperator;
  {
    register Tree_yPostOperator *W_51 = &yyt->U_1.V_75.PostOperator;

    W_51->Pos = pPos;
    W_51->Selector = pSelector;
    W_51->Operator = pOperator;
    W_51->Expr = pExpr;
  }
  return yyt;
}

Tree_tTree Tree_mIndex
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pExprs, BOOLEAN pWiden)
# else
(pPos, pSelector, pExpr, pExprs, pWiden)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pExpr;
Tree_tTree pExprs;
BOOLEAN pWiden;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Index]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Index;
  {
    register Tree_yIndex *W_52 = &yyt->U_1.V_76.Index;

    W_52->Pos = pPos;
    W_52->Selector = pSelector;
    W_52->Expr = pExpr;
    W_52->Exprs = pExprs;
    W_52->Widen = pWiden;
  }
  return yyt;
}

Tree_tTree Tree_mParents
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr)
# else
(pPos, pSelector, pExpr)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pExpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Parents]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Parents;
  {
    register Tree_yParents *W_53 = &yyt->U_1.V_77.Parents;

    W_53->Pos = pPos;
    W_53->Selector = pSelector;
    W_53->Expr = pExpr;
  }
  return yyt;
}

Tree_tTree Tree_mTargetExpr
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr)
# else
(pPos, pSelector, pExpr)
Positions_tPosition pPos;
Idents_tIdent pSelector;
Tree_tTree pExpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TargetExpr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TargetExpr;
  {
    register Tree_yTargetExpr *W_54 = &yyt->U_1.V_78.TargetExpr;

    W_54->Pos = pPos;
    W_54->Selector = pSelector;
    W_54->Expr = pExpr;
  }
  return yyt;
}

Tree_tTree Tree_mStringExpr
# ifdef __STDC__
(Positions_tPosition pPos, Idents_tIdent pSelector, StringMem_tStringRef pString)
# else
(pPos, pSelector, pString)
Positions_tPosition pPos;
Idents_tIdent pSelector;
StringMem_tStringRef pString;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_StringExpr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_StringExpr;
  {
    register Tree_yStringExpr *W_55 = &yyt->U_1.V_79.StringExpr;

    W_55->Pos = pPos;
    W_55->Selector = pSelector;
    W_55->String = pString;
  }
  return yyt;
}

Tree_tTree Tree_mStatements
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Statements]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Statements;
  return yyt;
}

Tree_tTree Tree_mNoStatement
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoStatement]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoStatement;
  return yyt;
}

Tree_tTree Tree_mStatement
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext)
# else
(pPos, pNext)
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Statement]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Statement;
  {
    register Tree_yStatement *W_56 = &yyt->U_1.V_82.Statement;

    W_56->Pos = pPos;
    W_56->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mProcCall
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pCall)
# else
(pPos, pNext, pCall)
Positions_tPosition pPos;
Tree_tTree pNext;
Tree_tTree pCall;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_ProcCall]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_ProcCall;
  {
    register Tree_yProcCall *W_57 = &yyt->U_1.V_83.ProcCall;

    W_57->Pos = pPos;
    W_57->Next = pNext;
    W_57->Call = pCall;
  }
  return yyt;
}

Tree_tTree Tree_mCondition
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pExpr)
# else
(pPos, pNext, pExpr)
Positions_tPosition pPos;
Tree_tTree pNext;
Tree_tTree pExpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Condition]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Condition;
  {
    register Tree_yCondition *W_58 = &yyt->U_1.V_84.Condition;

    W_58->Pos = pPos;
    W_58->Next = pNext;
    W_58->Expr = pExpr;
  }
  return yyt;
}

Tree_tTree Tree_mAssignment
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pAdr, Tree_tTree pExpr)
# else
(pPos, pNext, pAdr, pExpr)
Positions_tPosition pPos;
Tree_tTree pNext;
Tree_tTree pAdr;
Tree_tTree pExpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Assignment]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Assignment;
  {
    register Tree_yAssignment *W_59 = &yyt->U_1.V_85.Assignment;

    W_59->Pos = pPos;
    W_59->Next = pNext;
    W_59->Adr = pAdr;
    W_59->Expr = pExpr;
  }
  return yyt;
}

Tree_tTree Tree_mReject
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext)
# else
(pPos, pNext)
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Reject]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Reject;
  {
    register Tree_yReject *W_60 = &yyt->U_1.V_86.Reject;

    W_60->Pos = pPos;
    W_60->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mFail
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext)
# else
(pPos, pNext)
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Fail]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Fail;
  {
    register Tree_yFail *W_61 = &yyt->U_1.V_87.Fail;

    W_61->Pos = pPos;
    W_61->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mTargetStmt
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pParameters, Tree_tTree pStmt)
# else
(pPos, pNext, pParameters, pStmt)
Positions_tPosition pPos;
Tree_tTree pNext;
Tree_tTree pParameters;
Tree_tTree pStmt;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TargetStmt]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TargetStmt;
  {
    register Tree_yTargetStmt *W_62 = &yyt->U_1.V_88.TargetStmt;

    W_62->Pos = pPos;
    W_62->Next = pNext;
    W_62->Parameters = pParameters;
    W_62->Stmt = pStmt;
  }
  return yyt;
}

Tree_tTree Tree_mNl
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext)
# else
(pPos, pNext)
Positions_tPosition pPos;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Nl]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Nl;
  {
    register Tree_yNl *W_63 = &yyt->U_1.V_89.Nl;

    W_63->Pos = pPos;
    W_63->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mWriteStr
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext, StringMem_tStringRef pString)
# else
(pPos, pNext, pString)
Positions_tPosition pPos;
Tree_tTree pNext;
StringMem_tStringRef pString;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_WriteStr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_WriteStr;
  {
    register Tree_yWriteStr *W_64 = &yyt->U_1.V_90.WriteStr;

    W_64->Pos = pPos;
    W_64->Next = pNext;
    W_64->String = pString;
  }
  return yyt;
}

Tree_tTree Tree_mFormals
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Formals]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Formals;
  return yyt;
}

Tree_tTree Tree_mNoFormal
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoFormal]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoFormal;
  return yyt;
}

Tree_tTree Tree_mFormal
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pHides, Idents_tIdent pName, Positions_tPosition pDeclPos, Tree_tTree pTypeDesc, Tree_tTree pPath)
# else
(pNext, pHides, pName, pDeclPos, pTypeDesc, pPath)
Tree_tTree pNext;
Tree_tTree pHides;
Idents_tIdent pName;
Positions_tPosition pDeclPos;
Tree_tTree pTypeDesc;
Tree_tTree pPath;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Formal]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Formal;
  {
    register Tree_yFormal *W_65 = &yyt->U_1.V_93.Formal;

    W_65->Next = pNext;
    W_65->Hides = pHides;
    W_65->Name = pName;
    W_65->DeclPos = pDeclPos;
    W_65->TypeDesc = pTypeDesc;
    W_65->Path = pPath;
  }
  return yyt;
}

Tree_tTree Tree_mPlainFormal
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pHides, Idents_tIdent pName, Positions_tPosition pDeclPos, Tree_tTree pTypeDesc, Tree_tTree pPath)
# else
(pNext, pHides, pName, pDeclPos, pTypeDesc, pPath)
Tree_tTree pNext;
Tree_tTree pHides;
Idents_tIdent pName;
Positions_tPosition pDeclPos;
Tree_tTree pTypeDesc;
Tree_tTree pPath;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_PlainFormal]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_PlainFormal;
  {
    register Tree_yPlainFormal *W_66 = &yyt->U_1.V_94.PlainFormal;

    W_66->Next = pNext;
    W_66->Hides = pHides;
    W_66->Name = pName;
    W_66->DeclPos = pDeclPos;
    W_66->TypeDesc = pTypeDesc;
    W_66->Path = pPath;
  }
  return yyt;
}

Tree_tTree Tree_mRoutineFormal
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pHides, Idents_tIdent pName, Positions_tPosition pDeclPos, Tree_tTree pTypeDesc, Tree_tTree pPath, Tree_tTree pTargetClass, BOOLEAN pDeclaredTypeIsGuaranteed)
# else
(pNext, pHides, pName, pDeclPos, pTypeDesc, pPath, pTargetClass, pDeclaredTypeIsGuaranteed)
Tree_tTree pNext;
Tree_tTree pHides;
Idents_tIdent pName;
Positions_tPosition pDeclPos;
Tree_tTree pTypeDesc;
Tree_tTree pPath;
Tree_tTree pTargetClass;
BOOLEAN pDeclaredTypeIsGuaranteed;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_RoutineFormal]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_RoutineFormal;
  {
    register Tree_yRoutineFormal *W_67 = &yyt->U_1.V_95.RoutineFormal;

    W_67->Next = pNext;
    W_67->Hides = pHides;
    W_67->Name = pName;
    W_67->DeclPos = pDeclPos;
    W_67->TypeDesc = pTypeDesc;
    W_67->Path = pPath;
    W_67->TargetClass = pTargetClass;
    W_67->DeclaredTypeIsGuaranteed = pDeclaredTypeIsGuaranteed;
  }
  return yyt;
}

Tree_tTree Tree_mDummyFormal
# ifdef __STDC__
(Tree_tTree pNext)
# else
(pNext)
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_DummyFormal]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_DummyFormal;
  {
    register Tree_yDummyFormal *W_68 = &yyt->U_1.V_96.DummyFormal;

    W_68->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mTypeDesc
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TypeDesc]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TypeDesc;
  return yyt;
}

Tree_tTree Tree_mNodeTypes
# ifdef __STDC__
(Tree_tTree pTreeName, Sets_tSet pTypes)
# else
(pTreeName, pTypes)
Tree_tTree pTreeName;
Sets_tSet pTypes;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NodeTypes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NodeTypes;
  {
    register Tree_yNodeTypes *W_69 = &yyt->U_1.V_98.NodeTypes;

    W_69->TreeName = pTreeName;
    W_69->Types = pTypes;
  }
  return yyt;
}

Tree_tTree Tree_mUserType
# ifdef __STDC__
(Idents_tIdent pType)
# else
(pType)
Idents_tIdent pType;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_UserType]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_UserType;
  {
    register Tree_yUserType *W_70 = &yyt->U_1.V_99.UserType;

    W_70->Type = pType;
  }
  return yyt;
}

Tree_tTree Tree_mPath
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Path]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Path;
  return yyt;
}

Tree_tTree Tree_mVar
# ifdef __STDC__
(Idents_tIdent pName, BOOLEAN pIsOutput, BOOLEAN pIsRegister)
# else
(pName, pIsOutput, pIsRegister)
Idents_tIdent pName;
BOOLEAN pIsOutput;
BOOLEAN pIsRegister;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Var]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Var;
  {
    register Tree_yVar *W_71 = &yyt->U_1.V_101.Var;

    W_71->Name = pName;
    W_71->IsOutput = pIsOutput;
    W_71->IsRegister = pIsRegister;
  }
  return yyt;
}

Tree_tTree Tree_mConsType
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, BOOLEAN pIsProperlyNarrowed)
# else
(pNext, pName, pIsProperlyNarrowed)
Tree_tTree pNext;
Idents_tIdent pName;
BOOLEAN pIsProperlyNarrowed;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_ConsType]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_ConsType;
  {
    register Tree_yConsType *W_72 = &yyt->U_1.V_102.ConsType;

    W_72->Next = pNext;
    W_72->Name = pName;
    W_72->IsProperlyNarrowed = pIsProperlyNarrowed;
  }
  return yyt;
}

Tree_tTree Tree_mField
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName)
# else
(pNext, pName)
Tree_tTree pNext;
Idents_tIdent pName;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Field]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Field;
  {
    register Tree_yField *W_73 = &yyt->U_1.V_103.Field;

    W_73->Next = pNext;
    W_73->Name = pName;
  }
  return yyt;
}

Tree_tTree Tree_mTests
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Tests]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Tests;
  return yyt;
}

Tree_tTree Tree_mNoTest
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoTest]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoTest;
  return yyt;
}

Tree_tTree Tree_mOneTest
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pPath)
# else
(pNext, pPath)
Tree_tTree pNext;
Tree_tTree pPath;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_OneTest]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_OneTest;
  {
    register Tree_yOneTest *W_74 = &yyt->U_1.V_106.OneTest;

    W_74->Next = pNext;
    W_74->Path = pPath;
  }
  return yyt;
}

Tree_tTree Tree_mTestKind
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pTypeDesc, Idents_tIdent pName)
# else
(pNext, pPath, pTypeDesc, pName)
Tree_tTree pNext;
Tree_tTree pPath;
Tree_tTree pTypeDesc;
Idents_tIdent pName;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestKind]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TestKind;
  {
    register Tree_yTestKind *W_75 = &yyt->U_1.V_107.TestKind;

    W_75->Next = pNext;
    W_75->Path = pPath;
    W_75->TypeDesc = pTypeDesc;
    W_75->Name = pName;
  }
  return yyt;
}

Tree_tTree Tree_mTestIsType
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pTypeDesc, Idents_tIdent pName)
# else
(pNext, pPath, pTypeDesc, pName)
Tree_tTree pNext;
Tree_tTree pPath;
Tree_tTree pTypeDesc;
Idents_tIdent pName;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestIsType]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TestIsType;
  {
    register Tree_yTestIsType *W_76 = &yyt->U_1.V_108.TestIsType;

    W_76->Next = pNext;
    W_76->Path = pPath;
    W_76->TypeDesc = pTypeDesc;
    W_76->Name = pName;
  }
  return yyt;
}

Tree_tTree Tree_mTestNil
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pPath)
# else
(pNext, pPath)
Tree_tTree pNext;
Tree_tTree pPath;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestNil]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TestNil;
  {
    register Tree_yTestNil *W_77 = &yyt->U_1.V_109.TestNil;

    W_77->Next = pNext;
    W_77->Path = pPath;
  }
  return yyt;
}

Tree_tTree Tree_mTestNonlin
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pPath2, Tree_tTree pTypeDesc)
# else
(pNext, pPath, pPath2, pTypeDesc)
Tree_tTree pNext;
Tree_tTree pPath;
Tree_tTree pPath2;
Tree_tTree pTypeDesc;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestNonlin]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TestNonlin;
  {
    register Tree_yTestNonlin *W_78 = &yyt->U_1.V_110.TestNonlin;

    W_78->Next = pNext;
    W_78->Path = pPath;
    W_78->Path2 = pPath2;
    W_78->TypeDesc = pTypeDesc;
  }
  return yyt;
}

Tree_tTree Tree_mTestValue
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pExpr, Tree_tTree pTypeDesc)
# else
(pNext, pPath, pExpr, pTypeDesc)
Tree_tTree pNext;
Tree_tTree pPath;
Tree_tTree pExpr;
Tree_tTree pTypeDesc;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestValue]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TestValue;
  {
    register Tree_yTestValue *W_79 = &yyt->U_1.V_111.TestValue;

    W_79->Next = pNext;
    W_79->Path = pPath;
    W_79->Expr = pExpr;
    W_79->TypeDesc = pTypeDesc;
  }
  return yyt;
}

Tree_tTree Tree_mDecisions
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decisions]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Decisions;
  return yyt;
}

Tree_tTree Tree_mNoDecision
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoDecision]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoDecision;
  return yyt;
}

Tree_tTree Tree_mDecision
# ifdef __STDC__
(Tree_tTree pThenPart, Tree_tTree pElsePart, Tree_tTree pOneTest, SHORTCARD pCases, BOOLEAN pIsUnchanged)
# else
(pThenPart, pElsePart, pOneTest, pCases, pIsUnchanged)
Tree_tTree pThenPart;
Tree_tTree pElsePart;
Tree_tTree pOneTest;
SHORTCARD pCases;
BOOLEAN pIsUnchanged;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decision]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Decision;
  {
    register Tree_yDecision *W_80 = &yyt->U_1.V_114.Decision;

    W_80->ThenPart = pThenPart;
    W_80->ElsePart = pElsePart;
    W_80->OneTest = pOneTest;
    W_80->Cases = pCases;
    W_80->IsUnchanged = pIsUnchanged;
  }
  return yyt;
}

Tree_tTree Tree_mDecided
# ifdef __STDC__
(Tree_tTree pElsePart, Tree_tTree pRule)
# else
(pElsePart, pRule)
Tree_tTree pElsePart;
Tree_tTree pRule;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decided]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Decided;
  {
    register Tree_yDecided *W_81 = &yyt->U_1.V_115.Decided;

    W_81->ElsePart = pElsePart;
    W_81->Rule = pRule;
  }
  return yyt;
}

static void yyMark
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  for (;;) {
    if (yyt == Tree_NoTree) {
      return;
    }
    INC(yyt->U_1.V_2.yyHead.yyMark);
    if (yyt->U_1.V_2.yyHead.yyMark > 1) {
      return;
    }
    switch (yyt->U_1.V_1.Kind) {
    case Tree_Class:;
      yyMark(yyt->U_1.V_5.Class.Attributes);
      yyMark(yyt->U_1.V_5.Class.Extensions);
      yyMark(yyt->U_1.V_5.Class.BaseClass);
      yyMark(yyt->U_1.V_5.Class.Formals);
      yyMark(yyt->U_1.V_5.Class.TypeDesc);
      yyt = yyt->U_1.V_5.Class.Next;
      break;
    case Tree_AttrOrAction:;
      yyt = yyt->U_1.V_8.AttrOrAction.Next;
      break;
    case Tree_Child:;
      yyt = yyt->U_1.V_9.Child.Next;
      break;
    case Tree_Attribute:;
      yyt = yyt->U_1.V_10.Attribute.Next;
      break;
    case Tree_ActionPart:;
      yyt = yyt->U_1.V_11.ActionPart.Next;
      break;
    case Tree_Designator:;
      yyt = yyt->U_1.V_15.Designator.Next;
      break;
    case Tree_Ident:;
      yyt = yyt->U_1.V_16.Ident.Next;
      break;
    case Tree_Remote:;
      yyMark(yyt->U_1.V_17.Remote.Designators);
      yyt = yyt->U_1.V_17.Remote.Next;
      break;
    case Tree_Any:;
      yyt = yyt->U_1.V_18.Any.Next;
      break;
    case Tree_Anys:;
      yyMark(yyt->U_1.V_19.Anys.Layouts);
      yyt = yyt->U_1.V_19.Anys.Next;
      break;
    case Tree_LayoutAny:;
      yyt = yyt->U_1.V_22.LayoutAny.Next;
      break;
    case Tree_Name:;
      yyt = yyt->U_1.V_25.Name.Next;
      break;
    case Tree_Spec:;
      yyMark(yyt->U_1.V_26.Spec.TreeNames);
      yyMark(yyt->U_1.V_26.Spec.Public);
      yyMark(yyt->U_1.V_26.Spec.Extern);
      yyMark(yyt->U_1.V_26.Spec.Codes);
      yyt = yyt->U_1.V_26.Spec.Routines;
      break;
    case Tree_TreeName:;
      yyMark(yyt->U_1.V_29.TreeName.Classes);
      yyMark(yyt->U_1.V_29.TreeName.EmptyType);
      yyMark(yyt->U_1.V_29.TreeName.UniversalClass);
      yyt = yyt->U_1.V_29.TreeName.Next;
      break;
    case Tree_Routine:;
      yyMark(yyt->U_1.V_32.Routine.InParams);
      yyMark(yyt->U_1.V_32.Routine.OutParams);
      yyMark(yyt->U_1.V_32.Routine.Extern);
      yyMark(yyt->U_1.V_32.Routine.Rules);
      yyMark(yyt->U_1.V_32.Routine.InForm);
      yyMark(yyt->U_1.V_32.Routine.OutForm);
      yyMark(yyt->U_1.V_32.Routine.ParamDecls);
      yyMark(yyt->U_1.V_32.Routine.Decisions);
      yyt = yyt->U_1.V_32.Routine.Next;
      break;
    case Tree_Procedure:;
      yyMark(yyt->U_1.V_33.Procedure.InParams);
      yyMark(yyt->U_1.V_33.Procedure.OutParams);
      yyMark(yyt->U_1.V_33.Procedure.Extern);
      yyMark(yyt->U_1.V_33.Procedure.Rules);
      yyMark(yyt->U_1.V_33.Procedure.InForm);
      yyMark(yyt->U_1.V_33.Procedure.OutForm);
      yyMark(yyt->U_1.V_33.Procedure.ParamDecls);
      yyMark(yyt->U_1.V_33.Procedure.Decisions);
      yyt = yyt->U_1.V_33.Procedure.Next;
      break;
    case Tree_Function:;
      yyMark(yyt->U_1.V_34.Function.InParams);
      yyMark(yyt->U_1.V_34.Function.OutParams);
      yyMark(yyt->U_1.V_34.Function.Extern);
      yyMark(yyt->U_1.V_34.Function.Rules);
      yyMark(yyt->U_1.V_34.Function.InForm);
      yyMark(yyt->U_1.V_34.Function.OutForm);
      yyMark(yyt->U_1.V_34.Function.ParamDecls);
      yyMark(yyt->U_1.V_34.Function.Decisions);
      yyMark(yyt->U_1.V_34.Function.ReturnParams);
      yyMark(yyt->U_1.V_34.Function.ReturnForm);
      yyt = yyt->U_1.V_34.Function.Next;
      break;
    case Tree_Predicate:;
      yyMark(yyt->U_1.V_35.Predicate.InParams);
      yyMark(yyt->U_1.V_35.Predicate.OutParams);
      yyMark(yyt->U_1.V_35.Predicate.Extern);
      yyMark(yyt->U_1.V_35.Predicate.Rules);
      yyMark(yyt->U_1.V_35.Predicate.InForm);
      yyMark(yyt->U_1.V_35.Predicate.OutForm);
      yyMark(yyt->U_1.V_35.Predicate.ParamDecls);
      yyMark(yyt->U_1.V_35.Predicate.Decisions);
      yyt = yyt->U_1.V_35.Predicate.Next;
      break;
    case Tree_Param:;
      yyMark(yyt->U_1.V_38.Param.Type);
      yyt = yyt->U_1.V_38.Param.Next;
      break;
    case Tree_Type:;
      yyt = yyt->U_1.V_39.Type.Names;
      break;
    case Tree_Rule:;
      yyMark(yyt->U_1.V_42.Rule.Patterns);
      yyMark(yyt->U_1.V_42.Rule.Exprs);
      yyMark(yyt->U_1.V_42.Rule.Expr);
      yyMark(yyt->U_1.V_42.Rule.Statements);
      yyMark(yyt->U_1.V_42.Rule.VarDecls);
      yyMark(yyt->U_1.V_42.Rule.Tests);
      yyt = yyt->U_1.V_42.Rule.Next;
      break;
    case Tree_OnePattern:;
      yyMark(yyt->U_1.V_45.OnePattern.Pattern);
      yyt = yyt->U_1.V_45.OnePattern.Next;
      break;
    case Tree_OnePatternAlts:;
      yyMark(yyt->U_1.V_46.OnePatternAlts.PatternsList);
      yyMark(yyt->U_1.V_46.OnePatternAlts.Current);
      yyt = yyt->U_1.V_46.OnePatternAlts.Next;
      break;
    case Tree_OnePatternsList:;
      yyMark(yyt->U_1.V_49.OnePatternsList.Patterns);
      yyt = yyt->U_1.V_49.OnePatternsList.Next;
      break;
    case Tree_Pattern:;
      yyMark(yyt->U_1.V_50.Pattern.TypeDesc);
      yyt = yyt->U_1.V_50.Pattern.Path;
      break;
    case Tree_Decompose:;
      yyMark(yyt->U_1.V_51.Decompose.TypeDesc);
      yyMark(yyt->U_1.V_51.Decompose.Path);
      yyMark(yyt->U_1.V_51.Decompose.Expr);
      yyt = yyt->U_1.V_51.Decompose.Patterns;
      break;
    case Tree_VarDef:;
      yyMark(yyt->U_1.V_52.VarDef.TypeDesc);
      yyt = yyt->U_1.V_52.VarDef.Path;
      break;
    case Tree_NilTest:;
      yyMark(yyt->U_1.V_53.NilTest.TypeDesc);
      yyt = yyt->U_1.V_53.NilTest.Path;
      break;
    case Tree_DontCare1:;
      yyMark(yyt->U_1.V_54.DontCare1.TypeDesc);
      yyt = yyt->U_1.V_54.DontCare1.Path;
      break;
    case Tree_DontCare1Explicit:;
      yyMark(yyt->U_1.V_55.DontCare1Explicit.TypeDesc);
      yyt = yyt->U_1.V_55.DontCare1Explicit.Path;
      break;
    case Tree_DontCare1Internal:;
      yyMark(yyt->U_1.V_56.DontCare1Internal.TypeDesc);
      yyt = yyt->U_1.V_56.DontCare1Internal.Path;
      break;
    case Tree_DontCare:;
      yyMark(yyt->U_1.V_57.DontCare.TypeDesc);
      yyMark(yyt->U_1.V_57.DontCare.Path);
      yyt = yyt->U_1.V_57.DontCare.Tempos;
      break;
    case Tree_DontCareExplicit:;
      yyMark(yyt->U_1.V_58.DontCareExplicit.TypeDesc);
      yyMark(yyt->U_1.V_58.DontCareExplicit.Path);
      yyt = yyt->U_1.V_58.DontCareExplicit.Tempos;
      break;
    case Tree_DontCareInternal:;
      yyMark(yyt->U_1.V_59.DontCareInternal.TypeDesc);
      yyMark(yyt->U_1.V_59.DontCareInternal.Path);
      yyt = yyt->U_1.V_59.DontCareInternal.Tempos;
      break;
    case Tree_Value:;
      yyMark(yyt->U_1.V_60.Value.TypeDesc);
      yyMark(yyt->U_1.V_60.Value.Path);
      yyt = yyt->U_1.V_60.Value.Expr;
      break;
    case Tree_OneExpr:;
      yyMark(yyt->U_1.V_63.OneExpr.Expr);
      yyt = yyt->U_1.V_63.OneExpr.Next;
      break;
    case Tree_NamedExpr:;
      yyMark(yyt->U_1.V_64.NamedExpr.Expr);
      yyt = yyt->U_1.V_64.NamedExpr.Next;
      break;
    case Tree_Compose:;
      yyMark(yyt->U_1.V_66.Compose.Expr);
      yyMark(yyt->U_1.V_66.Compose.Exprs);
      yyt = yyt->U_1.V_66.Compose.TypeDesc;
      break;
    case Tree_Call:;
      yyMark(yyt->U_1.V_70.Call.Expr);
      yyMark(yyt->U_1.V_70.Call.Exprs);
      yyt = yyt->U_1.V_70.Call.Patterns;
      break;
    case Tree_Binary:;
      yyMark(yyt->U_1.V_71.Binary.Lop);
      yyt = yyt->U_1.V_71.Binary.Rop;
      break;
    case Tree_yy1:;
      yyMark(yyt->U_1.V_72.yy1.Lop);
      yyt = yyt->U_1.V_72.yy1.Rop;
      break;
    case Tree_BinaryCompound:;
      yyMark(yyt->U_1.V_73.BinaryCompound.Lop);
      yyt = yyt->U_1.V_73.BinaryCompound.Rop;
      break;
    case Tree_PreOperator:;
      yyt = yyt->U_1.V_74.PreOperator.Expr;
      break;
    case Tree_PostOperator:;
      yyt = yyt->U_1.V_75.PostOperator.Expr;
      break;
    case Tree_Index:;
      yyMark(yyt->U_1.V_76.Index.Expr);
      yyt = yyt->U_1.V_76.Index.Exprs;
      break;
    case Tree_Parents:;
      yyt = yyt->U_1.V_77.Parents.Expr;
      break;
    case Tree_TargetExpr:;
      yyt = yyt->U_1.V_78.TargetExpr.Expr;
      break;
    case Tree_Statement:;
      yyt = yyt->U_1.V_82.Statement.Next;
      break;
    case Tree_ProcCall:;
      yyMark(yyt->U_1.V_83.ProcCall.Call);
      yyt = yyt->U_1.V_83.ProcCall.Next;
      break;
    case Tree_Condition:;
      yyMark(yyt->U_1.V_84.Condition.Expr);
      yyt = yyt->U_1.V_84.Condition.Next;
      break;
    case Tree_Assignment:;
      yyMark(yyt->U_1.V_85.Assignment.Adr);
      yyMark(yyt->U_1.V_85.Assignment.Expr);
      yyt = yyt->U_1.V_85.Assignment.Next;
      break;
    case Tree_Reject:;
      yyt = yyt->U_1.V_86.Reject.Next;
      break;
    case Tree_Fail:;
      yyt = yyt->U_1.V_87.Fail.Next;
      break;
    case Tree_TargetStmt:;
      yyMark(yyt->U_1.V_88.TargetStmt.Parameters);
      yyMark(yyt->U_1.V_88.TargetStmt.Stmt);
      yyt = yyt->U_1.V_88.TargetStmt.Next;
      break;
    case Tree_Nl:;
      yyt = yyt->U_1.V_89.Nl.Next;
      break;
    case Tree_WriteStr:;
      yyt = yyt->U_1.V_90.WriteStr.Next;
      break;
    case Tree_Formal:;
      yyMark(yyt->U_1.V_93.Formal.Hides);
      yyMark(yyt->U_1.V_93.Formal.TypeDesc);
      yyMark(yyt->U_1.V_93.Formal.Path);
      yyt = yyt->U_1.V_93.Formal.Next;
      break;
    case Tree_PlainFormal:;
      yyMark(yyt->U_1.V_94.PlainFormal.Hides);
      yyMark(yyt->U_1.V_94.PlainFormal.TypeDesc);
      yyMark(yyt->U_1.V_94.PlainFormal.Path);
      yyt = yyt->U_1.V_94.PlainFormal.Next;
      break;
    case Tree_RoutineFormal:;
      yyMark(yyt->U_1.V_95.RoutineFormal.Hides);
      yyMark(yyt->U_1.V_95.RoutineFormal.TypeDesc);
      yyMark(yyt->U_1.V_95.RoutineFormal.Path);
      yyMark(yyt->U_1.V_95.RoutineFormal.TargetClass);
      yyt = yyt->U_1.V_95.RoutineFormal.Next;
      break;
    case Tree_DummyFormal:;
      yyt = yyt->U_1.V_96.DummyFormal.Next;
      break;
    case Tree_NodeTypes:;
      yyt = yyt->U_1.V_98.NodeTypes.TreeName;
      break;
    case Tree_ConsType:;
      yyt = yyt->U_1.V_102.ConsType.Next;
      break;
    case Tree_Field:;
      yyt = yyt->U_1.V_103.Field.Next;
      break;
    case Tree_OneTest:;
      yyMark(yyt->U_1.V_106.OneTest.Next);
      yyt = yyt->U_1.V_106.OneTest.Path;
      break;
    case Tree_TestKind:;
      yyMark(yyt->U_1.V_107.TestKind.Next);
      yyMark(yyt->U_1.V_107.TestKind.Path);
      yyt = yyt->U_1.V_107.TestKind.TypeDesc;
      break;
    case Tree_TestIsType:;
      yyMark(yyt->U_1.V_108.TestIsType.Next);
      yyMark(yyt->U_1.V_108.TestIsType.Path);
      yyt = yyt->U_1.V_108.TestIsType.TypeDesc;
      break;
    case Tree_TestNil:;
      yyMark(yyt->U_1.V_109.TestNil.Next);
      yyt = yyt->U_1.V_109.TestNil.Path;
      break;
    case Tree_TestNonlin:;
      yyMark(yyt->U_1.V_110.TestNonlin.Next);
      yyMark(yyt->U_1.V_110.TestNonlin.Path);
      yyMark(yyt->U_1.V_110.TestNonlin.Path2);
      yyt = yyt->U_1.V_110.TestNonlin.TypeDesc;
      break;
    case Tree_TestValue:;
      yyMark(yyt->U_1.V_111.TestValue.Next);
      yyMark(yyt->U_1.V_111.TestValue.Path);
      yyMark(yyt->U_1.V_111.TestValue.Expr);
      yyt = yyt->U_1.V_111.TestValue.TypeDesc;
      break;
    case Tree_Decision:;
      yyMark(yyt->U_1.V_114.Decision.ThenPart);
      yyMark(yyt->U_1.V_114.Decision.ElsePart);
      yyt = yyt->U_1.V_114.Decision.OneTest;
      break;
    case Tree_Decided:;
      yyMark(yyt->U_1.V_115.Decided.ElsePart);
      yyt = yyt->U_1.V_115.Decided.Rule;
      break;
    default :
      return;
      break;
    }
  } EXIT_3:;
}

static SHORTCARD yyMapToLabel
# ifdef __STDC__
(Tree_tTree yyTree)
# else
(yyTree)
Tree_tTree yyTree;
# endif
{
  INTEGER yyi;

  {
    LONGINT B_5 = 1, B_6 = yyLabelCount;

    if (B_5 <= B_6)
      for (yyi = B_5;; yyi += 1) {
        if (yyTreeStorePtr->A[yyi] == yyTree) {
          return yyi;
        }
        if (yyi >= B_6) break;
      }
  }
  INC(yyLabelCount);
  if (yyLabelCount == yyTreeStoreSize) {
    DynArray_ExtendArray((ADDRESS *)&yyTreeStorePtr, &yyTreeStoreSize, (LONGINT)sizeof(Tree_tTree));
  }
  yyTreeStorePtr->A[yyLabelCount] = yyTree;
  return yyLabelCount;
}

static Tree_tTree yyMapToTree
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
    LONGINT B_7 = 0, B_8 = (INTEGER)(O_2 - 1);

    if (B_7 <= B_8)
      for (yyi = B_7;; yyi += 1) {
        IO_WriteN(yyf, ORD((CHAR)yyx[yyi]), 2L, 16L);
        IO_WriteC(yyf, ' ');
        if (yyi >= B_8) break;
      }
  }
}

static void yyWriteAdr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (yyt == Tree_NoTree) {
    IO_WriteS(yyf, (STRING)"NoTree", 6L);
  } else {
    yyWriteHex((WORD *)&yyt, (LONGCARD)sizeof(yyt));
  }
  yyWriteNl();
}

static void yyyWriteNodeClass
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_5.Class.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_5.Class.Properties, (LONGCARD)sizeof(yyt->U_1.V_5.Class.Properties));
  yyWriteNl();
  yyWriteSelector((STRING)"Attributes", 10L);
  yyWriteAdr(yyt->U_1.V_5.Class.Attributes);
  yyWriteSelector((STRING)"Extensions", 10L);
  yyWriteAdr(yyt->U_1.V_5.Class.Extensions);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_5.Class.Next);
  yyWriteSelector((STRING)"BaseClass", 9L);
  yyWriteAdr(yyt->U_1.V_5.Class.BaseClass);
  yyWriteSelector((STRING)"Formals", 7L);
  yyWriteAdr(yyt->U_1.V_5.Class.Formals);
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_5.Class.TypeDesc);
  yyWriteSelector((STRING)"Index", 5L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.Index, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Depth", 5L);
  IO_WriteI(yyf, yyt->U_1.V_5.Class.Depth, 0L);
  yyWriteNl();
}

static void yyyWriteNodeAttrOrAction
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_8.AttrOrAction.Next);
}

static void yyyWriteNodeChild
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAttrOrAction(yyt);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_9.Child.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_9.Child.Type);
  yyWriteNl();
  yyWriteSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_9.Child.Properties, (LONGCARD)sizeof(yyt->U_1.V_9.Child.Properties));
  yyWriteNl();
}

static void yyyWriteNodeAttribute
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAttrOrAction(yyt);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_10.Attribute.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_10.Attribute.Type);
  yyWriteNl();
  yyWriteSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_10.Attribute.Properties, (LONGCARD)sizeof(yyt->U_1.V_10.Attribute.Properties));
  yyWriteNl();
}

static void yyyWriteNodeActionPart
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAttrOrAction(yyt);
}

static void yyyWriteNodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Export", 6L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Export);
  yyWriteNl();
  yyWriteSelector((STRING)"Import", 6L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Import);
  yyWriteNl();
  yyWriteSelector((STRING)"Global", 6L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Global);
  yyWriteNl();
  yyWriteSelector((STRING)"SpecWith", 8L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.SpecWith);
  yyWriteNl();
  yyWriteSelector((STRING)"BodyWith", 8L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.BodyWith);
  yyWriteNl();
  yyWriteSelector((STRING)"Local", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Local);
  yyWriteNl();
  yyWriteSelector((STRING)"Begin", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Begin);
  yyWriteNl();
  yyWriteSelector((STRING)"Close", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Close);
  yyWriteNl();
  yyWriteSelector((STRING)"ExportLine", 10L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.ExportLine);
  yyWriteNl();
  yyWriteSelector((STRING)"ImportLine", 10L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.ImportLine);
  yyWriteNl();
  yyWriteSelector((STRING)"GlobalLine", 10L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.GlobalLine);
  yyWriteNl();
  yyWriteSelector((STRING)"SpecWithLine", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.SpecWithLine);
  yyWriteNl();
  yyWriteSelector((STRING)"BodyWithLine", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.BodyWithLine);
  yyWriteNl();
  yyWriteSelector((STRING)"LocalLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.LocalLine);
  yyWriteNl();
  yyWriteSelector((STRING)"BeginLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.BeginLine);
  yyWriteNl();
  yyWriteSelector((STRING)"CloseLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.CloseLine);
  yyWriteNl();
}

static void yyyWriteNodeDesignator
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_15.Designator.Selector);
  yyWriteNl();
  yyWriteSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_15.Designator.Attribute);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_15.Designator.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"AttributePos", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_15.Designator.AttributePos);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_15.Designator.Next);
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_15.Designator.Object, (LONGCARD)sizeof(yyt->U_1.V_15.Designator.Object));
  yyWriteNl();
  yyWriteSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_15.Designator.Type);
  yyWriteNl();
}

static void yyyWriteNodeIdent
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_16.Ident.Attribute);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_16.Ident.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_16.Ident.Next);
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_16.Ident.Object, (LONGCARD)sizeof(yyt->U_1.V_16.Ident.Object));
  yyWriteNl();
}

static void yyyWriteNodeRemote
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Designators", 11L);
  yyWriteAdr(yyt->U_1.V_17.Remote.Designators);
  yyWriteSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_17.Remote.Type);
  yyWriteNl();
  yyWriteSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_17.Remote.Attribute);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_17.Remote.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_17.Remote.Next);
}

static void yyyWriteNodeAny
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Code", 4L);
  StringMem_WriteString(yyf, yyt->U_1.V_18.Any.Code);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_18.Any.Next);
}

static void yyyWriteNodeAnys
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Layouts", 7L);
  yyWriteAdr(yyt->U_1.V_19.Anys.Layouts);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_19.Anys.Next);
}

static void yyyWriteNodeLayoutAny
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Code", 4L);
  StringMem_WriteString(yyf, yyt->U_1.V_22.LayoutAny.Code);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_22.LayoutAny.Next);
}

static void yyyWriteNodeName
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_25.Name.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_25.Name.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_25.Name.Next);
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_25.Name.Object, (LONGCARD)sizeof(yyt->U_1.V_25.Name.Object));
  yyWriteNl();
}

static void yyyWriteNodeSpec
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"TrafoName", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_26.Spec.TrafoName);
  yyWriteNl();
  yyWriteSelector((STRING)"TreeNames", 9L);
  yyWriteAdr(yyt->U_1.V_26.Spec.TreeNames);
  yyWriteSelector((STRING)"Public", 6L);
  yyWriteAdr(yyt->U_1.V_26.Spec.Public);
  yyWriteSelector((STRING)"Extern", 6L);
  yyWriteAdr(yyt->U_1.V_26.Spec.Extern);
  yyWriteSelector((STRING)"Codes", 5L);
  yyWriteAdr(yyt->U_1.V_26.Spec.Codes);
  yyWriteSelector((STRING)"Routines", 8L);
  yyWriteAdr(yyt->U_1.V_26.Spec.Routines);
}

static void yyyWriteNodeTreeName
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_29.TreeName.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_29.TreeName.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_29.TreeName.Next);
  yyWriteSelector((STRING)"Classes", 7L);
  yyWriteAdr(yyt->U_1.V_29.TreeName.Classes);
  yyWriteSelector((STRING)"ClassCount", 10L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_29.TreeName.ClassCount, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"EmptyType", 9L);
  yyWriteAdr(yyt->U_1.V_29.TreeName.EmptyType);
  yyWriteSelector((STRING)"UniversalClass", 14L);
  yyWriteAdr(yyt->U_1.V_29.TreeName.UniversalClass);
}

static void yyyWriteNodeRoutine
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_32.Routine.Next);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_32.Routine.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_32.Routine.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"InParams", 8L);
  yyWriteAdr(yyt->U_1.V_32.Routine.InParams);
  yyWriteSelector((STRING)"OutParams", 9L);
  yyWriteAdr(yyt->U_1.V_32.Routine.OutParams);
  yyWriteSelector((STRING)"Extern", 6L);
  yyWriteAdr(yyt->U_1.V_32.Routine.Extern);
  yyWriteSelector((STRING)"Local", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_32.Routine.Local);
  yyWriteNl();
  yyWriteSelector((STRING)"LocalLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_32.Routine.LocalLine);
  yyWriteNl();
  yyWriteSelector((STRING)"Rules", 5L);
  yyWriteAdr(yyt->U_1.V_32.Routine.Rules);
  yyWriteSelector((STRING)"InForm", 6L);
  yyWriteAdr(yyt->U_1.V_32.Routine.InForm);
  yyWriteSelector((STRING)"OutForm", 7L);
  yyWriteAdr(yyt->U_1.V_32.Routine.OutForm);
  yyWriteSelector((STRING)"ParamDecls", 10L);
  yyWriteAdr(yyt->U_1.V_32.Routine.ParamDecls);
  yyWriteSelector((STRING)"IsExtern", 8L);
  IO_WriteB(yyf, yyt->U_1.V_32.Routine.IsExtern);
  yyWriteNl();
  yyWriteSelector((STRING)"Decisions", 9L);
  yyWriteAdr(yyt->U_1.V_32.Routine.Decisions);
}

static void yyyWriteNodeProcedure
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeRoutine(yyt);
}

static void yyyWriteNodeFunction
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeRoutine(yyt);
  yyWriteSelector((STRING)"ReturnParams", 12L);
  yyWriteAdr(yyt->U_1.V_34.Function.ReturnParams);
  yyWriteSelector((STRING)"ReturnForm", 10L);
  yyWriteAdr(yyt->U_1.V_34.Function.ReturnForm);
}

static void yyyWriteNodePredicate
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeRoutine(yyt);
}

static void yyyWriteNodeParam
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"IsRef", 5L);
  IO_WriteB(yyf, yyt->U_1.V_38.Param.IsRef);
  yyWriteNl();
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_38.Param.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_38.Param.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Type", 4L);
  yyWriteAdr(yyt->U_1.V_38.Param.Type);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_38.Param.Next);
}

static void yyyWriteNodeType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_39.Type.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_39.Type.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Names", 5L);
  yyWriteAdr(yyt->U_1.V_39.Type.Names);
}

static void yyyWriteNodeRule
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Line", 4L);
  Positions_WritePosition(yyf, yyt->U_1.V_42.Rule.Line);
  yyWriteNl();
  yyWriteSelector((STRING)"Patterns", 8L);
  yyWriteAdr(yyt->U_1.V_42.Rule.Patterns);
  yyWriteSelector((STRING)"Exprs", 5L);
  yyWriteAdr(yyt->U_1.V_42.Rule.Exprs);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_42.Rule.Expr);
  yyWriteSelector((STRING)"Statements", 10L);
  yyWriteAdr(yyt->U_1.V_42.Rule.Statements);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_42.Rule.Next);
  yyWriteSelector((STRING)"VarDecls", 8L);
  yyWriteAdr(yyt->U_1.V_42.Rule.VarDecls);
  yyWriteSelector((STRING)"HasTempos", 9L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasTempos);
  yyWriteNl();
  yyWriteSelector((STRING)"HasPatterns", 11L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasPatterns);
  yyWriteNl();
  yyWriteSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_42.Rule.Tempo);
  yyWriteNl();
  yyWriteSelector((STRING)"Index", 5L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_42.Rule.Index, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Tests", 5L);
  yyWriteAdr(yyt->U_1.V_42.Rule.Tests);
  yyWriteSelector((STRING)"HasExit", 7L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasExit);
  yyWriteNl();
  yyWriteSelector((STRING)"HasAssign", 9L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasAssign);
  yyWriteNl();
  yyWriteSelector((STRING)"HasTargetCode", 13L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasTargetCode);
  yyWriteNl();
  yyWriteSelector((STRING)"HasRejectOrFail", 15L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasRejectOrFail);
  yyWriteNl();
}

static void yyyWriteNodeNoPattern
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_44.NoPattern.Pos);
  yyWriteNl();
}

static void yyyWriteNodeOnePattern
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Pattern", 7L);
  yyWriteAdr(yyt->U_1.V_45.OnePattern.Pattern);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_45.OnePattern.Next);
}

static void yyyWriteNodeOnePatternAlts
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"PatternsList", 12L);
  yyWriteAdr(yyt->U_1.V_46.OnePatternAlts.PatternsList);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_46.OnePatternAlts.Next);
  yyWriteSelector((STRING)"Current", 7L);
  yyWriteAdr(yyt->U_1.V_46.OnePatternAlts.Current);
}

static void yyyWriteNodeOnePatternsList
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Patterns", 8L);
  yyWriteAdr(yyt->U_1.V_49.OnePatternsList.Patterns);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_49.OnePatternsList.Next);
}

static void yyyWriteNodePattern
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_50.Pattern.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_50.Pattern.Tempo);
  yyWriteNl();
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_50.Pattern.TypeDesc);
  yyWriteSelector((STRING)"Path", 4L);
  yyWriteAdr(yyt->U_1.V_50.Pattern.Path);
}

static void yyyWriteNodeDecompose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePattern(yyt);
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_51.Decompose.Selector);
  yyWriteNl();
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_51.Decompose.Expr);
  yyWriteSelector((STRING)"Patterns", 8L);
  yyWriteAdr(yyt->U_1.V_51.Decompose.Patterns);
  yyWriteSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_51.Decompose.Widen);
  yyWriteNl();
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_51.Decompose.Object, (LONGCARD)sizeof(yyt->U_1.V_51.Decompose.Object));
  yyWriteNl();
  yyWriteSelector((STRING)"IsProperlyNarrowed", 18L);
  IO_WriteB(yyf, yyt->U_1.V_51.Decompose.IsProperlyNarrowed);
  yyWriteNl();
}

static void yyyWriteNodeVarDef
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePattern(yyt);
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_52.VarDef.Selector);
  yyWriteNl();
  yyWriteSelector((STRING)"HasDelimiter", 12L);
  IO_WriteB(yyf, yyt->U_1.V_52.VarDef.HasDelimiter);
  yyWriteNl();
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_52.VarDef.Object, (LONGCARD)sizeof(yyt->U_1.V_52.VarDef.Object));
  yyWriteNl();
}

static void yyyWriteNodeNilTest
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePattern(yyt);
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_53.NilTest.Selector);
  yyWriteNl();
  yyWriteSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_53.NilTest.Widen);
  yyWriteNl();
  yyWriteSelector((STRING)"IsProperlyNarrowed", 18L);
  IO_WriteB(yyf, yyt->U_1.V_53.NilTest.IsProperlyNarrowed);
  yyWriteNl();
}

static void yyyWriteNodeDontCare1
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePattern(yyt);
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_54.DontCare1.Selector);
  yyWriteNl();
}

static void yyyWriteNodeDontCare1Explicit
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeDontCare1(yyt);
}

static void yyyWriteNodeDontCare1Internal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeDontCare1(yyt);
}

static void yyyWriteNodeDontCare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePattern(yyt);
  yyWriteSelector((STRING)"Tempos", 6L);
  yyWriteAdr(yyt->U_1.V_57.DontCare.Tempos);
}

static void yyyWriteNodeDontCareExplicit
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeDontCare(yyt);
}

static void yyyWriteNodeDontCareInternal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeDontCare(yyt);
}

static void yyyWriteNodeValue
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePattern(yyt);
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_60.Value.Selector);
  yyWriteNl();
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_60.Value.Expr);
}

static void yyyWriteNodeNoExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_62.NoExpr.Pos);
  yyWriteNl();
}

static void yyyWriteNodeOneExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_63.OneExpr.Expr);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_63.OneExpr.Next);
}

static void yyyWriteNodeNamedExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeOneExpr(yyt);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_64.NamedExpr.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"NamePos", 7L);
  Positions_WritePosition(yyf, yyt->U_1.V_64.NamedExpr.NamePos);
  yyWriteNl();
}

static void yyyWriteNodeExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_65.Expr.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_65.Expr.Selector);
  yyWriteNl();
}

static void yyyWriteNodeCompose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_66.Compose.Expr);
  yyWriteSelector((STRING)"Exprs", 5L);
  yyWriteAdr(yyt->U_1.V_66.Compose.Exprs);
  yyWriteSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_66.Compose.Widen);
  yyWriteNl();
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_66.Compose.Object, (LONGCARD)sizeof(yyt->U_1.V_66.Compose.Object));
  yyWriteNl();
  yyWriteSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_66.Compose.Tempo);
  yyWriteNl();
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_66.Compose.TypeDesc);
}

static void yyyWriteNodeVarUse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_67.VarUse.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_67.VarUse.Widen);
  yyWriteNl();
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_67.VarUse.Object, (LONGCARD)sizeof(yyt->U_1.V_67.VarUse.Object));
  yyWriteNl();
}

static void yyyWriteNodeAttrDesc
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeVarUse(yyt);
  yyWriteSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_68.AttrDesc.Attribute);
  yyWriteNl();
  yyWriteSelector((STRING)"AttributePos", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_68.AttrDesc.AttributePos);
  yyWriteNl();
  yyWriteSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_68.AttrDesc.Type);
  yyWriteNl();
}

static void yyyWriteNodeNil
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_69.Nil.Widen);
  yyWriteNl();
}

static void yyyWriteNodeCall
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_70.Call.Expr);
  yyWriteSelector((STRING)"Exprs", 5L);
  yyWriteAdr(yyt->U_1.V_70.Call.Exprs);
  yyWriteSelector((STRING)"Patterns", 8L);
  yyWriteAdr(yyt->U_1.V_70.Call.Patterns);
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_70.Call.Object, (LONGCARD)sizeof(yyt->U_1.V_70.Call.Object));
  yyWriteNl();
}

static void yyyWriteNodeBinary
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Lop", 3L);
  yyWriteAdr(yyt->U_1.V_71.Binary.Lop);
  yyWriteSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_71.Binary.Operator);
  yyWriteNl();
  yyWriteSelector((STRING)"Rop", 3L);
  yyWriteAdr(yyt->U_1.V_71.Binary.Rop);
  yyWriteSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_71.Binary.Widen);
  yyWriteNl();
}

static void yyyWriteNodeyy1
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeBinary(yyt);
}

static void yyyWriteNodeBinaryCompound
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeBinary(yyt);
  yyWriteSelector((STRING)"CompoundOperator", 16L);
  Idents_WriteIdent(yyf, yyt->U_1.V_73.BinaryCompound.CompoundOperator);
  yyWriteNl();
}

static void yyyWriteNodePreOperator
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_74.PreOperator.Operator);
  yyWriteNl();
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_74.PreOperator.Expr);
}

static void yyyWriteNodePostOperator
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_75.PostOperator.Operator);
  yyWriteNl();
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_75.PostOperator.Expr);
}

static void yyyWriteNodeIndex
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_76.Index.Expr);
  yyWriteSelector((STRING)"Exprs", 5L);
  yyWriteAdr(yyt->U_1.V_76.Index.Exprs);
  yyWriteSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_76.Index.Widen);
  yyWriteNl();
}

static void yyyWriteNodeParents
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_77.Parents.Expr);
}

static void yyyWriteNodeTargetExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_78.TargetExpr.Expr);
  yyWriteSelector((STRING)"UsedNames", 9L);
  Sets_WriteSet(yyf, yyt->U_1.V_78.TargetExpr.UsedNames);
  yyWriteNl();
}

static void yyyWriteNodeStringExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeExpr(yyt);
  yyWriteSelector((STRING)"String", 6L);
  StringMem_WriteString(yyf, yyt->U_1.V_79.StringExpr.String);
  yyWriteNl();
}

static void yyyWriteNodeStatement
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_82.Statement.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_82.Statement.Next);
}

static void yyyWriteNodeProcCall
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
  yyWriteSelector((STRING)"Call", 4L);
  yyWriteAdr(yyt->U_1.V_83.ProcCall.Call);
}

static void yyyWriteNodeCondition
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_84.Condition.Expr);
}

static void yyyWriteNodeAssignment
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
  yyWriteSelector((STRING)"Adr", 3L);
  yyWriteAdr(yyt->U_1.V_85.Assignment.Adr);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_85.Assignment.Expr);
  yyWriteSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_85.Assignment.Object, (LONGCARD)sizeof(yyt->U_1.V_85.Assignment.Object));
  yyWriteNl();
}

static void yyyWriteNodeReject
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
}

static void yyyWriteNodeFail
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
}

static void yyyWriteNodeTargetStmt
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
  yyWriteSelector((STRING)"Parameters", 10L);
  yyWriteAdr(yyt->U_1.V_88.TargetStmt.Parameters);
  yyWriteSelector((STRING)"Stmt", 4L);
  yyWriteAdr(yyt->U_1.V_88.TargetStmt.Stmt);
  yyWriteSelector((STRING)"UsedNames", 9L);
  Sets_WriteSet(yyf, yyt->U_1.V_88.TargetStmt.UsedNames);
  yyWriteNl();
}

static void yyyWriteNodeNl
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
}

static void yyyWriteNodeWriteStr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeStatement(yyt);
  yyWriteSelector((STRING)"String", 6L);
  StringMem_WriteString(yyf, yyt->U_1.V_90.WriteStr.String);
  yyWriteNl();
}

static void yyyWriteNodeFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_93.Formal.Next);
  yyWriteSelector((STRING)"Hides", 5L);
  yyWriteAdr(yyt->U_1.V_93.Formal.Hides);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_93.Formal.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"DeclPos", 7L);
  Positions_WritePosition(yyf, yyt->U_1.V_93.Formal.DeclPos);
  yyWriteNl();
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_93.Formal.TypeDesc);
  yyWriteSelector((STRING)"Path", 4L);
  yyWriteAdr(yyt->U_1.V_93.Formal.Path);
}

static void yyyWriteNodePlainFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeFormal(yyt);
}

static void yyyWriteNodeRoutineFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeFormal(yyt);
  yyWriteSelector((STRING)"TargetClass", 11L);
  yyWriteAdr(yyt->U_1.V_95.RoutineFormal.TargetClass);
  yyWriteSelector((STRING)"DeclaredTypeIsGuaranteed", 24L);
  IO_WriteB(yyf, yyt->U_1.V_95.RoutineFormal.DeclaredTypeIsGuaranteed);
  yyWriteNl();
}

static void yyyWriteNodeDummyFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_96.DummyFormal.Next);
}

static void yyyWriteNodeNodeTypes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"TreeName", 8L);
  yyWriteAdr(yyt->U_1.V_98.NodeTypes.TreeName);
  yyWriteSelector((STRING)"Types", 5L);
  Sets_WriteSet(yyf, yyt->U_1.V_98.NodeTypes.Types);
  yyWriteNl();
}

static void yyyWriteNodeUserType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_99.UserType.Type);
  yyWriteNl();
}

static void yyyWriteNodeVar
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_101.Var.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"IsOutput", 8L);
  IO_WriteB(yyf, yyt->U_1.V_101.Var.IsOutput);
  yyWriteNl();
  yyWriteSelector((STRING)"IsRegister", 10L);
  IO_WriteB(yyf, yyt->U_1.V_101.Var.IsRegister);
  yyWriteNl();
}

static void yyyWriteNodeConsType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_102.ConsType.Next);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_102.ConsType.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"IsProperlyNarrowed", 18L);
  IO_WriteB(yyf, yyt->U_1.V_102.ConsType.IsProperlyNarrowed);
  yyWriteNl();
}

static void yyyWriteNodeField
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_103.Field.Next);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_103.Field.Name);
  yyWriteNl();
}

static void yyyWriteNodeOneTest
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_106.OneTest.Next);
  yyWriteSelector((STRING)"Path", 4L);
  yyWriteAdr(yyt->U_1.V_106.OneTest.Path);
}

static void yyyWriteNodeTestKind
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeOneTest(yyt);
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_107.TestKind.TypeDesc);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_107.TestKind.Name);
  yyWriteNl();
}

static void yyyWriteNodeTestIsType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeOneTest(yyt);
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_108.TestIsType.TypeDesc);
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_108.TestIsType.Name);
  yyWriteNl();
}

static void yyyWriteNodeTestNil
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeOneTest(yyt);
}

static void yyyWriteNodeTestNonlin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeOneTest(yyt);
  yyWriteSelector((STRING)"Path2", 5L);
  yyWriteAdr(yyt->U_1.V_110.TestNonlin.Path2);
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_110.TestNonlin.TypeDesc);
}

static void yyyWriteNodeTestValue
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeOneTest(yyt);
  yyWriteSelector((STRING)"Expr", 4L);
  yyWriteAdr(yyt->U_1.V_111.TestValue.Expr);
  yyWriteSelector((STRING)"TypeDesc", 8L);
  yyWriteAdr(yyt->U_1.V_111.TestValue.TypeDesc);
}

static void yyyWriteNodeDecision
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"ThenPart", 8L);
  yyWriteAdr(yyt->U_1.V_114.Decision.ThenPart);
  yyWriteSelector((STRING)"ElsePart", 8L);
  yyWriteAdr(yyt->U_1.V_114.Decision.ElsePart);
  yyWriteSelector((STRING)"OneTest", 7L);
  yyWriteAdr(yyt->U_1.V_114.Decision.OneTest);
  yyWriteSelector((STRING)"Cases", 5L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_114.Decision.Cases, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"IsUnchanged", 11L);
  IO_WriteB(yyf, yyt->U_1.V_114.Decision.IsUnchanged);
  yyWriteNl();
}

static void yyyWriteNodeDecided
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"ElsePart", 8L);
  yyWriteAdr(yyt->U_1.V_115.Decided.ElsePart);
  yyWriteSelector((STRING)"Rule", 4L);
  yyWriteAdr(yyt->U_1.V_115.Decided.Rule);
}

void Tree_WriteTreeNode
# ifdef __STDC__
(IO_tFile yyyf, Tree_tTree yyt)
# else
(yyyf, yyt)
IO_tFile yyyf;
Tree_tTree yyt;
# endif
{
  yyf = yyyf;
  if (yyt == Tree_NoTree) {
    IO_WriteS(yyf, (STRING)"NoTree", 6L);
    yyWriteNl();
    return;
  }
  switch (yyt->U_1.V_1.Kind) {
  case Tree_Classes:;
    IO_WriteS(yyf, (STRING)"Classes", 7L);
    yyWriteNl();
    break;
  case Tree_NoClass:;
    IO_WriteS(yyf, (STRING)"NoClass", 7L);
    yyWriteNl();
    break;
  case Tree_Class:;
    IO_WriteS(yyf, (STRING)"Class", 5L);
    yyWriteNl();
    yyyWriteNodeClass(yyt);
    break;
  case Tree_Attributes:;
    IO_WriteS(yyf, (STRING)"Attributes", 10L);
    yyWriteNl();
    break;
  case Tree_NoAttribute:;
    IO_WriteS(yyf, (STRING)"NoAttribute", 11L);
    yyWriteNl();
    break;
  case Tree_AttrOrAction:;
    IO_WriteS(yyf, (STRING)"AttrOrAction", 12L);
    yyWriteNl();
    yyyWriteNodeAttrOrAction(yyt);
    break;
  case Tree_Child:;
    IO_WriteS(yyf, (STRING)"Child", 5L);
    yyWriteNl();
    yyyWriteNodeChild(yyt);
    break;
  case Tree_Attribute:;
    IO_WriteS(yyf, (STRING)"Attribute", 9L);
    yyWriteNl();
    yyyWriteNodeAttribute(yyt);
    break;
  case Tree_ActionPart:;
    IO_WriteS(yyf, (STRING)"ActionPart", 10L);
    yyWriteNl();
    yyyWriteNodeActionPart(yyt);
    break;
  case Tree_Codes:;
    IO_WriteS(yyf, (STRING)"Codes", 5L);
    yyWriteNl();
    yyyWriteNodeCodes(yyt);
    break;
  case Tree_Designators:;
    IO_WriteS(yyf, (STRING)"Designators", 11L);
    yyWriteNl();
    break;
  case Tree_NoDesignator:;
    IO_WriteS(yyf, (STRING)"NoDesignator", 12L);
    yyWriteNl();
    break;
  case Tree_Designator:;
    IO_WriteS(yyf, (STRING)"Designator", 10L);
    yyWriteNl();
    yyyWriteNodeDesignator(yyt);
    break;
  case Tree_Ident:;
    IO_WriteS(yyf, (STRING)"Ident", 5L);
    yyWriteNl();
    yyyWriteNodeIdent(yyt);
    break;
  case Tree_Remote:;
    IO_WriteS(yyf, (STRING)"Remote", 6L);
    yyWriteNl();
    yyyWriteNodeRemote(yyt);
    break;
  case Tree_Any:;
    IO_WriteS(yyf, (STRING)"Any", 3L);
    yyWriteNl();
    yyyWriteNodeAny(yyt);
    break;
  case Tree_Anys:;
    IO_WriteS(yyf, (STRING)"Anys", 4L);
    yyWriteNl();
    yyyWriteNodeAnys(yyt);
    break;
  case Tree_Layouts:;
    IO_WriteS(yyf, (STRING)"Layouts", 7L);
    yyWriteNl();
    break;
  case Tree_NoLayout:;
    IO_WriteS(yyf, (STRING)"NoLayout", 8L);
    yyWriteNl();
    break;
  case Tree_LayoutAny:;
    IO_WriteS(yyf, (STRING)"LayoutAny", 9L);
    yyWriteNl();
    yyyWriteNodeLayoutAny(yyt);
    break;
  case Tree_Names:;
    IO_WriteS(yyf, (STRING)"Names", 5L);
    yyWriteNl();
    break;
  case Tree_NoName:;
    IO_WriteS(yyf, (STRING)"NoName", 6L);
    yyWriteNl();
    break;
  case Tree_Name:;
    IO_WriteS(yyf, (STRING)"Name", 4L);
    yyWriteNl();
    yyyWriteNodeName(yyt);
    break;
  case Tree_Spec:;
    IO_WriteS(yyf, (STRING)"Spec", 4L);
    yyWriteNl();
    yyyWriteNodeSpec(yyt);
    break;
  case Tree_TreeNames:;
    IO_WriteS(yyf, (STRING)"TreeNames", 9L);
    yyWriteNl();
    break;
  case Tree_NoTreeName:;
    IO_WriteS(yyf, (STRING)"NoTreeName", 10L);
    yyWriteNl();
    break;
  case Tree_TreeName:;
    IO_WriteS(yyf, (STRING)"TreeName", 8L);
    yyWriteNl();
    yyyWriteNodeTreeName(yyt);
    break;
  case Tree_Routines:;
    IO_WriteS(yyf, (STRING)"Routines", 8L);
    yyWriteNl();
    break;
  case Tree_NoRoutine:;
    IO_WriteS(yyf, (STRING)"NoRoutine", 9L);
    yyWriteNl();
    break;
  case Tree_Routine:;
    IO_WriteS(yyf, (STRING)"Routine", 7L);
    yyWriteNl();
    yyyWriteNodeRoutine(yyt);
    break;
  case Tree_Procedure:;
    IO_WriteS(yyf, (STRING)"Procedure", 9L);
    yyWriteNl();
    yyyWriteNodeProcedure(yyt);
    break;
  case Tree_Function:;
    IO_WriteS(yyf, (STRING)"Function", 8L);
    yyWriteNl();
    yyyWriteNodeFunction(yyt);
    break;
  case Tree_Predicate:;
    IO_WriteS(yyf, (STRING)"Predicate", 9L);
    yyWriteNl();
    yyyWriteNodePredicate(yyt);
    break;
  case Tree_Parameters:;
    IO_WriteS(yyf, (STRING)"Parameters", 10L);
    yyWriteNl();
    break;
  case Tree_NoParameter:;
    IO_WriteS(yyf, (STRING)"NoParameter", 11L);
    yyWriteNl();
    break;
  case Tree_Param:;
    IO_WriteS(yyf, (STRING)"Param", 5L);
    yyWriteNl();
    yyyWriteNodeParam(yyt);
    break;
  case Tree_Type:;
    IO_WriteS(yyf, (STRING)"Type", 4L);
    yyWriteNl();
    yyyWriteNodeType(yyt);
    break;
  case Tree_Rules:;
    IO_WriteS(yyf, (STRING)"Rules", 5L);
    yyWriteNl();
    break;
  case Tree_NoRule:;
    IO_WriteS(yyf, (STRING)"NoRule", 6L);
    yyWriteNl();
    break;
  case Tree_Rule:;
    IO_WriteS(yyf, (STRING)"Rule", 4L);
    yyWriteNl();
    yyyWriteNodeRule(yyt);
    break;
  case Tree_Patterns:;
    IO_WriteS(yyf, (STRING)"Patterns", 8L);
    yyWriteNl();
    break;
  case Tree_NoPattern:;
    IO_WriteS(yyf, (STRING)"NoPattern", 9L);
    yyWriteNl();
    yyyWriteNodeNoPattern(yyt);
    break;
  case Tree_OnePattern:;
    IO_WriteS(yyf, (STRING)"OnePattern", 10L);
    yyWriteNl();
    yyyWriteNodeOnePattern(yyt);
    break;
  case Tree_OnePatternAlts:;
    IO_WriteS(yyf, (STRING)"OnePatternAlts", 14L);
    yyWriteNl();
    yyyWriteNodeOnePatternAlts(yyt);
    break;
  case Tree_PatternsList:;
    IO_WriteS(yyf, (STRING)"PatternsList", 12L);
    yyWriteNl();
    break;
  case Tree_NoPatternsList:;
    IO_WriteS(yyf, (STRING)"NoPatternsList", 14L);
    yyWriteNl();
    break;
  case Tree_OnePatternsList:;
    IO_WriteS(yyf, (STRING)"OnePatternsList", 15L);
    yyWriteNl();
    yyyWriteNodeOnePatternsList(yyt);
    break;
  case Tree_Pattern:;
    IO_WriteS(yyf, (STRING)"Pattern", 7L);
    yyWriteNl();
    yyyWriteNodePattern(yyt);
    break;
  case Tree_Decompose:;
    IO_WriteS(yyf, (STRING)"Decompose", 9L);
    yyWriteNl();
    yyyWriteNodeDecompose(yyt);
    break;
  case Tree_VarDef:;
    IO_WriteS(yyf, (STRING)"VarDef", 6L);
    yyWriteNl();
    yyyWriteNodeVarDef(yyt);
    break;
  case Tree_NilTest:;
    IO_WriteS(yyf, (STRING)"NilTest", 7L);
    yyWriteNl();
    yyyWriteNodeNilTest(yyt);
    break;
  case Tree_DontCare1:;
    IO_WriteS(yyf, (STRING)"DontCare1", 9L);
    yyWriteNl();
    yyyWriteNodeDontCare1(yyt);
    break;
  case Tree_DontCare1Explicit:;
    IO_WriteS(yyf, (STRING)"DontCare1Explicit", 17L);
    yyWriteNl();
    yyyWriteNodeDontCare1Explicit(yyt);
    break;
  case Tree_DontCare1Internal:;
    IO_WriteS(yyf, (STRING)"DontCare1Internal", 17L);
    yyWriteNl();
    yyyWriteNodeDontCare1Internal(yyt);
    break;
  case Tree_DontCare:;
    IO_WriteS(yyf, (STRING)"DontCare", 8L);
    yyWriteNl();
    yyyWriteNodeDontCare(yyt);
    break;
  case Tree_DontCareExplicit:;
    IO_WriteS(yyf, (STRING)"DontCareExplicit", 16L);
    yyWriteNl();
    yyyWriteNodeDontCareExplicit(yyt);
    break;
  case Tree_DontCareInternal:;
    IO_WriteS(yyf, (STRING)"DontCareInternal", 16L);
    yyWriteNl();
    yyyWriteNodeDontCareInternal(yyt);
    break;
  case Tree_Value:;
    IO_WriteS(yyf, (STRING)"Value", 5L);
    yyWriteNl();
    yyyWriteNodeValue(yyt);
    break;
  case Tree_Exprs:;
    IO_WriteS(yyf, (STRING)"Exprs", 5L);
    yyWriteNl();
    break;
  case Tree_NoExpr:;
    IO_WriteS(yyf, (STRING)"NoExpr", 6L);
    yyWriteNl();
    yyyWriteNodeNoExpr(yyt);
    break;
  case Tree_OneExpr:;
    IO_WriteS(yyf, (STRING)"OneExpr", 7L);
    yyWriteNl();
    yyyWriteNodeOneExpr(yyt);
    break;
  case Tree_NamedExpr:;
    IO_WriteS(yyf, (STRING)"NamedExpr", 9L);
    yyWriteNl();
    yyyWriteNodeNamedExpr(yyt);
    break;
  case Tree_Expr:;
    IO_WriteS(yyf, (STRING)"Expr", 4L);
    yyWriteNl();
    yyyWriteNodeExpr(yyt);
    break;
  case Tree_Compose:;
    IO_WriteS(yyf, (STRING)"Compose", 7L);
    yyWriteNl();
    yyyWriteNodeCompose(yyt);
    break;
  case Tree_VarUse:;
    IO_WriteS(yyf, (STRING)"VarUse", 6L);
    yyWriteNl();
    yyyWriteNodeVarUse(yyt);
    break;
  case Tree_AttrDesc:;
    IO_WriteS(yyf, (STRING)"AttrDesc", 8L);
    yyWriteNl();
    yyyWriteNodeAttrDesc(yyt);
    break;
  case Tree_Nil:;
    IO_WriteS(yyf, (STRING)"Nil", 3L);
    yyWriteNl();
    yyyWriteNodeNil(yyt);
    break;
  case Tree_Call:;
    IO_WriteS(yyf, (STRING)"Call", 4L);
    yyWriteNl();
    yyyWriteNodeCall(yyt);
    break;
  case Tree_Binary:;
    IO_WriteS(yyf, (STRING)"Binary", 6L);
    yyWriteNl();
    yyyWriteNodeBinary(yyt);
    break;
  case Tree_yy1:;
    IO_WriteS(yyf, (STRING)"yy1", 3L);
    yyWriteNl();
    yyyWriteNodeyy1(yyt);
    break;
  case Tree_BinaryCompound:;
    IO_WriteS(yyf, (STRING)"BinaryCompound", 14L);
    yyWriteNl();
    yyyWriteNodeBinaryCompound(yyt);
    break;
  case Tree_PreOperator:;
    IO_WriteS(yyf, (STRING)"PreOperator", 11L);
    yyWriteNl();
    yyyWriteNodePreOperator(yyt);
    break;
  case Tree_PostOperator:;
    IO_WriteS(yyf, (STRING)"PostOperator", 12L);
    yyWriteNl();
    yyyWriteNodePostOperator(yyt);
    break;
  case Tree_Index:;
    IO_WriteS(yyf, (STRING)"Index", 5L);
    yyWriteNl();
    yyyWriteNodeIndex(yyt);
    break;
  case Tree_Parents:;
    IO_WriteS(yyf, (STRING)"Parents", 7L);
    yyWriteNl();
    yyyWriteNodeParents(yyt);
    break;
  case Tree_TargetExpr:;
    IO_WriteS(yyf, (STRING)"TargetExpr", 10L);
    yyWriteNl();
    yyyWriteNodeTargetExpr(yyt);
    break;
  case Tree_StringExpr:;
    IO_WriteS(yyf, (STRING)"StringExpr", 10L);
    yyWriteNl();
    yyyWriteNodeStringExpr(yyt);
    break;
  case Tree_Statements:;
    IO_WriteS(yyf, (STRING)"Statements", 10L);
    yyWriteNl();
    break;
  case Tree_NoStatement:;
    IO_WriteS(yyf, (STRING)"NoStatement", 11L);
    yyWriteNl();
    break;
  case Tree_Statement:;
    IO_WriteS(yyf, (STRING)"Statement", 9L);
    yyWriteNl();
    yyyWriteNodeStatement(yyt);
    break;
  case Tree_ProcCall:;
    IO_WriteS(yyf, (STRING)"ProcCall", 8L);
    yyWriteNl();
    yyyWriteNodeProcCall(yyt);
    break;
  case Tree_Condition:;
    IO_WriteS(yyf, (STRING)"Condition", 9L);
    yyWriteNl();
    yyyWriteNodeCondition(yyt);
    break;
  case Tree_Assignment:;
    IO_WriteS(yyf, (STRING)"Assignment", 10L);
    yyWriteNl();
    yyyWriteNodeAssignment(yyt);
    break;
  case Tree_Reject:;
    IO_WriteS(yyf, (STRING)"Reject", 6L);
    yyWriteNl();
    yyyWriteNodeReject(yyt);
    break;
  case Tree_Fail:;
    IO_WriteS(yyf, (STRING)"Fail", 4L);
    yyWriteNl();
    yyyWriteNodeFail(yyt);
    break;
  case Tree_TargetStmt:;
    IO_WriteS(yyf, (STRING)"TargetStmt", 10L);
    yyWriteNl();
    yyyWriteNodeTargetStmt(yyt);
    break;
  case Tree_Nl:;
    IO_WriteS(yyf, (STRING)"Nl", 2L);
    yyWriteNl();
    yyyWriteNodeNl(yyt);
    break;
  case Tree_WriteStr:;
    IO_WriteS(yyf, (STRING)"WriteStr", 8L);
    yyWriteNl();
    yyyWriteNodeWriteStr(yyt);
    break;
  case Tree_Formals:;
    IO_WriteS(yyf, (STRING)"Formals", 7L);
    yyWriteNl();
    break;
  case Tree_NoFormal:;
    IO_WriteS(yyf, (STRING)"NoFormal", 8L);
    yyWriteNl();
    break;
  case Tree_Formal:;
    IO_WriteS(yyf, (STRING)"Formal", 6L);
    yyWriteNl();
    yyyWriteNodeFormal(yyt);
    break;
  case Tree_PlainFormal:;
    IO_WriteS(yyf, (STRING)"PlainFormal", 11L);
    yyWriteNl();
    yyyWriteNodePlainFormal(yyt);
    break;
  case Tree_RoutineFormal:;
    IO_WriteS(yyf, (STRING)"RoutineFormal", 13L);
    yyWriteNl();
    yyyWriteNodeRoutineFormal(yyt);
    break;
  case Tree_DummyFormal:;
    IO_WriteS(yyf, (STRING)"DummyFormal", 11L);
    yyWriteNl();
    yyyWriteNodeDummyFormal(yyt);
    break;
  case Tree_TypeDesc:;
    IO_WriteS(yyf, (STRING)"TypeDesc", 8L);
    yyWriteNl();
    break;
  case Tree_NodeTypes:;
    IO_WriteS(yyf, (STRING)"NodeTypes", 9L);
    yyWriteNl();
    yyyWriteNodeNodeTypes(yyt);
    break;
  case Tree_UserType:;
    IO_WriteS(yyf, (STRING)"UserType", 8L);
    yyWriteNl();
    yyyWriteNodeUserType(yyt);
    break;
  case Tree_Path:;
    IO_WriteS(yyf, (STRING)"Path", 4L);
    yyWriteNl();
    break;
  case Tree_Var:;
    IO_WriteS(yyf, (STRING)"Var", 3L);
    yyWriteNl();
    yyyWriteNodeVar(yyt);
    break;
  case Tree_ConsType:;
    IO_WriteS(yyf, (STRING)"ConsType", 8L);
    yyWriteNl();
    yyyWriteNodeConsType(yyt);
    break;
  case Tree_Field:;
    IO_WriteS(yyf, (STRING)"Field", 5L);
    yyWriteNl();
    yyyWriteNodeField(yyt);
    break;
  case Tree_Tests:;
    IO_WriteS(yyf, (STRING)"Tests", 5L);
    yyWriteNl();
    break;
  case Tree_NoTest:;
    IO_WriteS(yyf, (STRING)"NoTest", 6L);
    yyWriteNl();
    break;
  case Tree_OneTest:;
    IO_WriteS(yyf, (STRING)"OneTest", 7L);
    yyWriteNl();
    yyyWriteNodeOneTest(yyt);
    break;
  case Tree_TestKind:;
    IO_WriteS(yyf, (STRING)"TestKind", 8L);
    yyWriteNl();
    yyyWriteNodeTestKind(yyt);
    break;
  case Tree_TestIsType:;
    IO_WriteS(yyf, (STRING)"TestIsType", 10L);
    yyWriteNl();
    yyyWriteNodeTestIsType(yyt);
    break;
  case Tree_TestNil:;
    IO_WriteS(yyf, (STRING)"TestNil", 7L);
    yyWriteNl();
    yyyWriteNodeTestNil(yyt);
    break;
  case Tree_TestNonlin:;
    IO_WriteS(yyf, (STRING)"TestNonlin", 10L);
    yyWriteNl();
    yyyWriteNodeTestNonlin(yyt);
    break;
  case Tree_TestValue:;
    IO_WriteS(yyf, (STRING)"TestValue", 9L);
    yyWriteNl();
    yyyWriteNodeTestValue(yyt);
    break;
  case Tree_Decisions:;
    IO_WriteS(yyf, (STRING)"Decisions", 9L);
    yyWriteNl();
    break;
  case Tree_NoDecision:;
    IO_WriteS(yyf, (STRING)"NoDecision", 10L);
    yyWriteNl();
    break;
  case Tree_Decision:;
    IO_WriteS(yyf, (STRING)"Decision", 8L);
    yyWriteNl();
    yyyWriteNodeDecision(yyt);
    break;
  case Tree_Decided:;
    IO_WriteS(yyf, (STRING)"Decided", 7L);
    yyWriteNl();
    yyyWriteNodeDecided(yyt);
    break;
  default :
    break;
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

void Tree_WriteTree
# ifdef __STDC__
(IO_tFile yyyf, Tree_tTree yyt)
# else
(yyyf, yyt)
IO_tFile yyyf;
Tree_tTree yyt;
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
  yyWriteTree(yyt);
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
(CHAR yys[], LONGCARD O_4, Tree_tTree yyt)
# else
(yys, O_4, yyt)
CHAR yys[];
LONGCARD O_4;
Tree_tTree yyt;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yys, O_4, CHAR)
  yyIndentSelector(yys, O_4);
  yyWriteTree(yyt);
  FREE_OPEN_ARRAYS
}

static void yWriteClass
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Class", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_5.Class.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_5.Class.Properties, (LONGCARD)sizeof(yyt->U_1.V_5.Class.Properties));
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Attributes", 10L, yyt->U_1.V_5.Class.Attributes);
  yyIndentSelectorTree((STRING)"Extensions", 10L, yyt->U_1.V_5.Class.Extensions);
  yyIndentSelectorTree((STRING)"BaseClass", 9L, yyt->U_1.V_5.Class.BaseClass);
  yyIndentSelectorTree((STRING)"Formals", 7L, yyt->U_1.V_5.Class.Formals);
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_5.Class.TypeDesc);
  yyIndentSelector((STRING)"Index", 5L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.Index, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"Depth", 5L);
  IO_WriteI(yyf, yyt->U_1.V_5.Class.Depth, 0L);
  yyWriteNl();
}

static void yWriteAttrOrAction
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"AttrOrAction", 12L);
  yyWriteNl();
}

static void yWriteChild
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Child", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_9.Child.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_9.Child.Type);
  yyWriteNl();
  yyIndentSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_9.Child.Properties, (LONGCARD)sizeof(yyt->U_1.V_9.Child.Properties));
  yyWriteNl();
}

static void yWriteAttribute
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Attribute", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_10.Attribute.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_10.Attribute.Type);
  yyWriteNl();
  yyIndentSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_10.Attribute.Properties, (LONGCARD)sizeof(yyt->U_1.V_10.Attribute.Properties));
  yyWriteNl();
}

static void yWriteActionPart
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"ActionPart", 10L);
  yyWriteNl();
}

static void yWriteCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Codes", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Export", 6L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Export);
  yyWriteNl();
  yyIndentSelector((STRING)"Import", 6L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Import);
  yyWriteNl();
  yyIndentSelector((STRING)"Global", 6L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Global);
  yyWriteNl();
  yyIndentSelector((STRING)"SpecWith", 8L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.SpecWith);
  yyWriteNl();
  yyIndentSelector((STRING)"BodyWith", 8L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.BodyWith);
  yyWriteNl();
  yyIndentSelector((STRING)"Local", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Local);
  yyWriteNl();
  yyIndentSelector((STRING)"Begin", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Begin);
  yyWriteNl();
  yyIndentSelector((STRING)"Close", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_12.Codes.Close);
  yyWriteNl();
  yyIndentSelector((STRING)"ExportLine", 10L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.ExportLine);
  yyWriteNl();
  yyIndentSelector((STRING)"ImportLine", 10L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.ImportLine);
  yyWriteNl();
  yyIndentSelector((STRING)"GlobalLine", 10L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.GlobalLine);
  yyWriteNl();
  yyIndentSelector((STRING)"SpecWithLine", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.SpecWithLine);
  yyWriteNl();
  yyIndentSelector((STRING)"BodyWithLine", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.BodyWithLine);
  yyWriteNl();
  yyIndentSelector((STRING)"LocalLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.LocalLine);
  yyWriteNl();
  yyIndentSelector((STRING)"BeginLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.BeginLine);
  yyWriteNl();
  yyIndentSelector((STRING)"CloseLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_12.Codes.CloseLine);
  yyWriteNl();
}

static void yWriteDesignator
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Designator", 10L);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_15.Designator.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_15.Designator.Attribute);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_15.Designator.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"AttributePos", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_15.Designator.AttributePos);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_15.Designator.Object, (LONGCARD)sizeof(yyt->U_1.V_15.Designator.Object));
  yyWriteNl();
  yyIndentSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_15.Designator.Type);
  yyWriteNl();
}

static void yWriteIdent
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Ident", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_16.Ident.Attribute);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_16.Ident.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_16.Ident.Object, (LONGCARD)sizeof(yyt->U_1.V_16.Ident.Object));
  yyWriteNl();
}

static void yWriteRemote
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Remote", 6L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Designators", 11L, yyt->U_1.V_17.Remote.Designators);
  yyIndentSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_17.Remote.Type);
  yyWriteNl();
  yyIndentSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_17.Remote.Attribute);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_17.Remote.Pos);
  yyWriteNl();
}

static void yWriteAny
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Any", 3L);
  yyWriteNl();
  yyIndentSelector((STRING)"Code", 4L);
  StringMem_WriteString(yyf, yyt->U_1.V_18.Any.Code);
  yyWriteNl();
}

static void yWriteAnys
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Anys", 4L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Layouts", 7L, yyt->U_1.V_19.Anys.Layouts);
}

static void yWriteLayoutAny
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"LayoutAny", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Code", 4L);
  StringMem_WriteString(yyf, yyt->U_1.V_22.LayoutAny.Code);
  yyWriteNl();
}

static void yWriteName
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Name", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_25.Name.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_25.Name.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_25.Name.Object, (LONGCARD)sizeof(yyt->U_1.V_25.Name.Object));
  yyWriteNl();
}

static void yWriteSpec
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Spec", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"TrafoName", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_26.Spec.TrafoName);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TreeNames", 9L, yyt->U_1.V_26.Spec.TreeNames);
  yyIndentSelectorTree((STRING)"Public", 6L, yyt->U_1.V_26.Spec.Public);
  yyIndentSelectorTree((STRING)"Extern", 6L, yyt->U_1.V_26.Spec.Extern);
  yyIndentSelectorTree((STRING)"Codes", 5L, yyt->U_1.V_26.Spec.Codes);
}

static void yWriteTreeName
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TreeName", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_29.TreeName.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_29.TreeName.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Classes", 7L, yyt->U_1.V_29.TreeName.Classes);
  yyIndentSelector((STRING)"ClassCount", 10L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_29.TreeName.ClassCount, 0L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"EmptyType", 9L, yyt->U_1.V_29.TreeName.EmptyType);
  yyIndentSelectorTree((STRING)"UniversalClass", 14L, yyt->U_1.V_29.TreeName.UniversalClass);
}

static void yWriteRoutine
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Routine", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_32.Routine.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_32.Routine.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"InParams", 8L, yyt->U_1.V_32.Routine.InParams);
  yyIndentSelectorTree((STRING)"OutParams", 9L, yyt->U_1.V_32.Routine.OutParams);
  yyIndentSelectorTree((STRING)"Extern", 6L, yyt->U_1.V_32.Routine.Extern);
  yyIndentSelector((STRING)"Local", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_32.Routine.Local);
  yyWriteNl();
  yyIndentSelector((STRING)"LocalLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_32.Routine.LocalLine);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Rules", 5L, yyt->U_1.V_32.Routine.Rules);
  yyIndentSelectorTree((STRING)"InForm", 6L, yyt->U_1.V_32.Routine.InForm);
  yyIndentSelectorTree((STRING)"OutForm", 7L, yyt->U_1.V_32.Routine.OutForm);
  yyIndentSelectorTree((STRING)"ParamDecls", 10L, yyt->U_1.V_32.Routine.ParamDecls);
  yyIndentSelector((STRING)"IsExtern", 8L);
  IO_WriteB(yyf, yyt->U_1.V_32.Routine.IsExtern);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Decisions", 9L, yyt->U_1.V_32.Routine.Decisions);
}

static void yWriteProcedure
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Procedure", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_33.Procedure.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_33.Procedure.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"InParams", 8L, yyt->U_1.V_33.Procedure.InParams);
  yyIndentSelectorTree((STRING)"OutParams", 9L, yyt->U_1.V_33.Procedure.OutParams);
  yyIndentSelectorTree((STRING)"Extern", 6L, yyt->U_1.V_33.Procedure.Extern);
  yyIndentSelector((STRING)"Local", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_33.Procedure.Local);
  yyWriteNl();
  yyIndentSelector((STRING)"LocalLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_33.Procedure.LocalLine);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Rules", 5L, yyt->U_1.V_33.Procedure.Rules);
  yyIndentSelectorTree((STRING)"InForm", 6L, yyt->U_1.V_33.Procedure.InForm);
  yyIndentSelectorTree((STRING)"OutForm", 7L, yyt->U_1.V_33.Procedure.OutForm);
  yyIndentSelectorTree((STRING)"ParamDecls", 10L, yyt->U_1.V_33.Procedure.ParamDecls);
  yyIndentSelector((STRING)"IsExtern", 8L);
  IO_WriteB(yyf, yyt->U_1.V_33.Procedure.IsExtern);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Decisions", 9L, yyt->U_1.V_33.Procedure.Decisions);
}

static void yWriteFunction
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Function", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_34.Function.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_34.Function.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"InParams", 8L, yyt->U_1.V_34.Function.InParams);
  yyIndentSelectorTree((STRING)"OutParams", 9L, yyt->U_1.V_34.Function.OutParams);
  yyIndentSelectorTree((STRING)"Extern", 6L, yyt->U_1.V_34.Function.Extern);
  yyIndentSelector((STRING)"Local", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_34.Function.Local);
  yyWriteNl();
  yyIndentSelector((STRING)"LocalLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_34.Function.LocalLine);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Rules", 5L, yyt->U_1.V_34.Function.Rules);
  yyIndentSelectorTree((STRING)"InForm", 6L, yyt->U_1.V_34.Function.InForm);
  yyIndentSelectorTree((STRING)"OutForm", 7L, yyt->U_1.V_34.Function.OutForm);
  yyIndentSelectorTree((STRING)"ParamDecls", 10L, yyt->U_1.V_34.Function.ParamDecls);
  yyIndentSelector((STRING)"IsExtern", 8L);
  IO_WriteB(yyf, yyt->U_1.V_34.Function.IsExtern);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Decisions", 9L, yyt->U_1.V_34.Function.Decisions);
  yyIndentSelectorTree((STRING)"ReturnParams", 12L, yyt->U_1.V_34.Function.ReturnParams);
  yyIndentSelectorTree((STRING)"ReturnForm", 10L, yyt->U_1.V_34.Function.ReturnForm);
}

static void yWritePredicate
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Predicate", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_35.Predicate.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_35.Predicate.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"InParams", 8L, yyt->U_1.V_35.Predicate.InParams);
  yyIndentSelectorTree((STRING)"OutParams", 9L, yyt->U_1.V_35.Predicate.OutParams);
  yyIndentSelectorTree((STRING)"Extern", 6L, yyt->U_1.V_35.Predicate.Extern);
  yyIndentSelector((STRING)"Local", 5L);
  Texts_WriteText(yyf, yyt->U_1.V_35.Predicate.Local);
  yyWriteNl();
  yyIndentSelector((STRING)"LocalLine", 9L);
  Positions_WritePosition(yyf, yyt->U_1.V_35.Predicate.LocalLine);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Rules", 5L, yyt->U_1.V_35.Predicate.Rules);
  yyIndentSelectorTree((STRING)"InForm", 6L, yyt->U_1.V_35.Predicate.InForm);
  yyIndentSelectorTree((STRING)"OutForm", 7L, yyt->U_1.V_35.Predicate.OutForm);
  yyIndentSelectorTree((STRING)"ParamDecls", 10L, yyt->U_1.V_35.Predicate.ParamDecls);
  yyIndentSelector((STRING)"IsExtern", 8L);
  IO_WriteB(yyf, yyt->U_1.V_35.Predicate.IsExtern);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Decisions", 9L, yyt->U_1.V_35.Predicate.Decisions);
}

static void yWriteParam
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Param", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"IsRef", 5L);
  IO_WriteB(yyf, yyt->U_1.V_38.Param.IsRef);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_38.Param.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_38.Param.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Type", 4L, yyt->U_1.V_38.Param.Type);
}

static void yWriteType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Type", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_39.Type.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_39.Type.Pos);
  yyWriteNl();
}

static void yWriteRule
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Rule", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Line", 4L);
  Positions_WritePosition(yyf, yyt->U_1.V_42.Rule.Line);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Patterns", 8L, yyt->U_1.V_42.Rule.Patterns);
  yyIndentSelectorTree((STRING)"Exprs", 5L, yyt->U_1.V_42.Rule.Exprs);
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_42.Rule.Expr);
  yyIndentSelectorTree((STRING)"Statements", 10L, yyt->U_1.V_42.Rule.Statements);
  yyIndentSelectorTree((STRING)"VarDecls", 8L, yyt->U_1.V_42.Rule.VarDecls);
  yyIndentSelector((STRING)"HasTempos", 9L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasTempos);
  yyWriteNl();
  yyIndentSelector((STRING)"HasPatterns", 11L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasPatterns);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_42.Rule.Tempo);
  yyWriteNl();
  yyIndentSelector((STRING)"Index", 5L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_42.Rule.Index, 0L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Tests", 5L, yyt->U_1.V_42.Rule.Tests);
  yyIndentSelector((STRING)"HasExit", 7L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasExit);
  yyWriteNl();
  yyIndentSelector((STRING)"HasAssign", 9L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasAssign);
  yyWriteNl();
  yyIndentSelector((STRING)"HasTargetCode", 13L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasTargetCode);
  yyWriteNl();
  yyIndentSelector((STRING)"HasRejectOrFail", 15L);
  IO_WriteB(yyf, yyt->U_1.V_42.Rule.HasRejectOrFail);
  yyWriteNl();
}

static void yWriteNoPattern
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"NoPattern", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_44.NoPattern.Pos);
  yyWriteNl();
}

static void yWriteOnePattern
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"OnePattern", 10L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Pattern", 7L, yyt->U_1.V_45.OnePattern.Pattern);
}

static void yWriteOnePatternAlts
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"OnePatternAlts", 14L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"PatternsList", 12L, yyt->U_1.V_46.OnePatternAlts.PatternsList);
  yyIndentSelectorTree((STRING)"Current", 7L, yyt->U_1.V_46.OnePatternAlts.Current);
}

static void yWriteOnePatternsList
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"OnePatternsList", 15L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Patterns", 8L, yyt->U_1.V_49.OnePatternsList.Patterns);
}

static void yWritePattern
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Pattern", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_50.Pattern.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_50.Pattern.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_50.Pattern.TypeDesc);
}

static void yWriteDecompose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Decompose", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_51.Decompose.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_51.Decompose.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_51.Decompose.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_51.Decompose.Path);
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_51.Decompose.Selector);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_51.Decompose.Expr);
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_51.Decompose.Widen);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_51.Decompose.Object, (LONGCARD)sizeof(yyt->U_1.V_51.Decompose.Object));
  yyWriteNl();
  yyIndentSelector((STRING)"IsProperlyNarrowed", 18L);
  IO_WriteB(yyf, yyt->U_1.V_51.Decompose.IsProperlyNarrowed);
  yyWriteNl();
}

static void yWriteVarDef
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"VarDef", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_52.VarDef.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_52.VarDef.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_52.VarDef.TypeDesc);
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_52.VarDef.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"HasDelimiter", 12L);
  IO_WriteB(yyf, yyt->U_1.V_52.VarDef.HasDelimiter);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_52.VarDef.Object, (LONGCARD)sizeof(yyt->U_1.V_52.VarDef.Object));
  yyWriteNl();
}

static void yWriteNilTest
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"NilTest", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_53.NilTest.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_53.NilTest.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_53.NilTest.TypeDesc);
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_53.NilTest.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_53.NilTest.Widen);
  yyWriteNl();
  yyIndentSelector((STRING)"IsProperlyNarrowed", 18L);
  IO_WriteB(yyf, yyt->U_1.V_53.NilTest.IsProperlyNarrowed);
  yyWriteNl();
}

static void yWriteDontCare1
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"DontCare1", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_54.DontCare1.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_54.DontCare1.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_54.DontCare1.TypeDesc);
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_54.DontCare1.Selector);
  yyWriteNl();
}

static void yWriteDontCare1Explicit
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"DontCare1Explicit", 17L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_55.DontCare1Explicit.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_55.DontCare1Explicit.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_55.DontCare1Explicit.TypeDesc);
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_55.DontCare1Explicit.Selector);
  yyWriteNl();
}

static void yWriteDontCare1Internal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"DontCare1Internal", 17L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_56.DontCare1Internal.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_56.DontCare1Internal.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_56.DontCare1Internal.TypeDesc);
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_56.DontCare1Internal.Selector);
  yyWriteNl();
}

static void yWriteDontCare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"DontCare", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_57.DontCare.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_57.DontCare.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_57.DontCare.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_57.DontCare.Path);
}

static void yWriteDontCareExplicit
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"DontCareExplicit", 16L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_58.DontCareExplicit.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_58.DontCareExplicit.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_58.DontCareExplicit.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_58.DontCareExplicit.Path);
}

static void yWriteDontCareInternal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"DontCareInternal", 16L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_59.DontCareInternal.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_59.DontCareInternal.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_59.DontCareInternal.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_59.DontCareInternal.Path);
}

static void yWriteValue
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Value", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_60.Value.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_60.Value.Tempo);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_60.Value.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_60.Value.Path);
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_60.Value.Selector);
  yyWriteNl();
}

static void yWriteNoExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"NoExpr", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_62.NoExpr.Pos);
  yyWriteNl();
}

static void yWriteOneExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"OneExpr", 7L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_63.OneExpr.Expr);
}

static void yWriteNamedExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"NamedExpr", 9L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_64.NamedExpr.Expr);
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_64.NamedExpr.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"NamePos", 7L);
  Positions_WritePosition(yyf, yyt->U_1.V_64.NamedExpr.NamePos);
  yyWriteNl();
}

static void yWriteExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Expr", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_65.Expr.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_65.Expr.Selector);
  yyWriteNl();
}

static void yWriteCompose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Compose", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_66.Compose.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_66.Compose.Selector);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_66.Compose.Expr);
  yyIndentSelectorTree((STRING)"Exprs", 5L, yyt->U_1.V_66.Compose.Exprs);
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_66.Compose.Widen);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_66.Compose.Object, (LONGCARD)sizeof(yyt->U_1.V_66.Compose.Object));
  yyWriteNl();
  yyIndentSelector((STRING)"Tempo", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_66.Compose.Tempo);
  yyWriteNl();
}

static void yWriteVarUse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"VarUse", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_67.VarUse.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_67.VarUse.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_67.VarUse.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_67.VarUse.Widen);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_67.VarUse.Object, (LONGCARD)sizeof(yyt->U_1.V_67.VarUse.Object));
  yyWriteNl();
}

static void yWriteAttrDesc
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"AttrDesc", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_68.AttrDesc.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_68.AttrDesc.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_68.AttrDesc.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_68.AttrDesc.Widen);
  yyWriteNl();
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_68.AttrDesc.Object, (LONGCARD)sizeof(yyt->U_1.V_68.AttrDesc.Object));
  yyWriteNl();
  yyIndentSelector((STRING)"Attribute", 9L);
  Idents_WriteIdent(yyf, yyt->U_1.V_68.AttrDesc.Attribute);
  yyWriteNl();
  yyIndentSelector((STRING)"AttributePos", 12L);
  Positions_WritePosition(yyf, yyt->U_1.V_68.AttrDesc.AttributePos);
  yyWriteNl();
  yyIndentSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_68.AttrDesc.Type);
  yyWriteNl();
}

static void yWriteNil
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Nil", 3L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_69.Nil.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_69.Nil.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_69.Nil.Widen);
  yyWriteNl();
}

static void yWriteCall
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Call", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_70.Call.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_70.Call.Selector);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_70.Call.Expr);
  yyIndentSelectorTree((STRING)"Exprs", 5L, yyt->U_1.V_70.Call.Exprs);
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_70.Call.Object, (LONGCARD)sizeof(yyt->U_1.V_70.Call.Object));
  yyWriteNl();
}

static void yWriteBinary
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Binary", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_71.Binary.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_71.Binary.Selector);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Lop", 3L, yyt->U_1.V_71.Binary.Lop);
  yyIndentSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_71.Binary.Operator);
  yyWriteNl();
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_71.Binary.Widen);
  yyWriteNl();
}

static void yWriteyy1
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"yy1", 3L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_72.yy1.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_72.yy1.Selector);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Lop", 3L, yyt->U_1.V_72.yy1.Lop);
  yyIndentSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_72.yy1.Operator);
  yyWriteNl();
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_72.yy1.Widen);
  yyWriteNl();
}

static void yWriteBinaryCompound
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"BinaryCompound", 14L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_73.BinaryCompound.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_73.BinaryCompound.Selector);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Lop", 3L, yyt->U_1.V_73.BinaryCompound.Lop);
  yyIndentSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_73.BinaryCompound.Operator);
  yyWriteNl();
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_73.BinaryCompound.Widen);
  yyWriteNl();
  yyIndentSelector((STRING)"CompoundOperator", 16L);
  Idents_WriteIdent(yyf, yyt->U_1.V_73.BinaryCompound.CompoundOperator);
  yyWriteNl();
}

static void yWritePreOperator
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"PreOperator", 11L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_74.PreOperator.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_74.PreOperator.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_74.PreOperator.Operator);
  yyWriteNl();
}

static void yWritePostOperator
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"PostOperator", 12L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_75.PostOperator.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_75.PostOperator.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"Operator", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_75.PostOperator.Operator);
  yyWriteNl();
}

static void yWriteIndex
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Index", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_76.Index.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_76.Index.Selector);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_76.Index.Expr);
  yyIndentSelector((STRING)"Widen", 5L);
  IO_WriteB(yyf, yyt->U_1.V_76.Index.Widen);
  yyWriteNl();
}

static void yWriteParents
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Parents", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_77.Parents.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_77.Parents.Selector);
  yyWriteNl();
}

static void yWriteTargetExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TargetExpr", 10L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_78.TargetExpr.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_78.TargetExpr.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"UsedNames", 9L);
  Sets_WriteSet(yyf, yyt->U_1.V_78.TargetExpr.UsedNames);
  yyWriteNl();
}

static void yWriteStringExpr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"StringExpr", 10L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_79.StringExpr.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_79.StringExpr.Selector);
  yyWriteNl();
  yyIndentSelector((STRING)"String", 6L);
  StringMem_WriteString(yyf, yyt->U_1.V_79.StringExpr.String);
  yyWriteNl();
}

static void yWriteStatement
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Statement", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_82.Statement.Pos);
  yyWriteNl();
}

static void yWriteProcCall
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"ProcCall", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_83.ProcCall.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Call", 4L, yyt->U_1.V_83.ProcCall.Call);
}

static void yWriteCondition
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Condition", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_84.Condition.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_84.Condition.Expr);
}

static void yWriteAssignment
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Assignment", 10L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_85.Assignment.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Adr", 3L, yyt->U_1.V_85.Assignment.Adr);
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_85.Assignment.Expr);
  yyIndentSelector((STRING)"Object", 6L);
  yyWriteHex((WORD *)&yyt->U_1.V_85.Assignment.Object, (LONGCARD)sizeof(yyt->U_1.V_85.Assignment.Object));
  yyWriteNl();
}

static void yWriteReject
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Reject", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_86.Reject.Pos);
  yyWriteNl();
}

static void yWriteFail
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Fail", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_87.Fail.Pos);
  yyWriteNl();
}

static void yWriteTargetStmt
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TargetStmt", 10L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_88.TargetStmt.Pos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Parameters", 10L, yyt->U_1.V_88.TargetStmt.Parameters);
  yyIndentSelectorTree((STRING)"Stmt", 4L, yyt->U_1.V_88.TargetStmt.Stmt);
  yyIndentSelector((STRING)"UsedNames", 9L);
  Sets_WriteSet(yyf, yyt->U_1.V_88.TargetStmt.UsedNames);
  yyWriteNl();
}

static void yWriteNl
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Nl", 2L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_89.Nl.Pos);
  yyWriteNl();
}

static void yWriteWriteStr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"WriteStr", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_90.WriteStr.Pos);
  yyWriteNl();
  yyIndentSelector((STRING)"String", 6L);
  StringMem_WriteString(yyf, yyt->U_1.V_90.WriteStr.String);
  yyWriteNl();
}

static void yWriteFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Formal", 6L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Hides", 5L, yyt->U_1.V_93.Formal.Hides);
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_93.Formal.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"DeclPos", 7L);
  Positions_WritePosition(yyf, yyt->U_1.V_93.Formal.DeclPos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_93.Formal.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_93.Formal.Path);
}

static void yWritePlainFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"PlainFormal", 11L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Hides", 5L, yyt->U_1.V_94.PlainFormal.Hides);
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_94.PlainFormal.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"DeclPos", 7L);
  Positions_WritePosition(yyf, yyt->U_1.V_94.PlainFormal.DeclPos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_94.PlainFormal.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_94.PlainFormal.Path);
}

static void yWriteRoutineFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"RoutineFormal", 13L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Hides", 5L, yyt->U_1.V_95.RoutineFormal.Hides);
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_95.RoutineFormal.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"DeclPos", 7L);
  Positions_WritePosition(yyf, yyt->U_1.V_95.RoutineFormal.DeclPos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"TypeDesc", 8L, yyt->U_1.V_95.RoutineFormal.TypeDesc);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_95.RoutineFormal.Path);
  yyIndentSelectorTree((STRING)"TargetClass", 11L, yyt->U_1.V_95.RoutineFormal.TargetClass);
  yyIndentSelector((STRING)"DeclaredTypeIsGuaranteed", 24L);
  IO_WriteB(yyf, yyt->U_1.V_95.RoutineFormal.DeclaredTypeIsGuaranteed);
  yyWriteNl();
}

static void yWriteDummyFormal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"DummyFormal", 11L);
  yyWriteNl();
}

static void yWriteNodeTypes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"NodeTypes", 9L);
  yyWriteNl();
  yyIndentSelector((STRING)"Types", 5L);
  Sets_WriteSet(yyf, yyt->U_1.V_98.NodeTypes.Types);
  yyWriteNl();
}

static void yWriteUserType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"UserType", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_99.UserType.Type);
  yyWriteNl();
}

static void yWriteVar
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Var", 3L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_101.Var.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"IsOutput", 8L);
  IO_WriteB(yyf, yyt->U_1.V_101.Var.IsOutput);
  yyWriteNl();
  yyIndentSelector((STRING)"IsRegister", 10L);
  IO_WriteB(yyf, yyt->U_1.V_101.Var.IsRegister);
  yyWriteNl();
}

static void yWriteConsType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"ConsType", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_102.ConsType.Name);
  yyWriteNl();
  yyIndentSelector((STRING)"IsProperlyNarrowed", 18L);
  IO_WriteB(yyf, yyt->U_1.V_102.ConsType.IsProperlyNarrowed);
  yyWriteNl();
}

static void yWriteField
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Field", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_103.Field.Name);
  yyWriteNl();
}

static void yWriteOneTest
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"OneTest", 7L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Next", 4L, yyt->U_1.V_106.OneTest.Next);
}

static void yWriteTestKind
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TestKind", 8L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Next", 4L, yyt->U_1.V_107.TestKind.Next);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_107.TestKind.Path);
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_107.TestKind.Name);
  yyWriteNl();
}

static void yWriteTestIsType
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TestIsType", 10L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Next", 4L, yyt->U_1.V_108.TestIsType.Next);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_108.TestIsType.Path);
  yyIndentSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_108.TestIsType.Name);
  yyWriteNl();
}

static void yWriteTestNil
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TestNil", 7L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Next", 4L, yyt->U_1.V_109.TestNil.Next);
}

static void yWriteTestNonlin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TestNonlin", 10L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Next", 4L, yyt->U_1.V_110.TestNonlin.Next);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_110.TestNonlin.Path);
  yyIndentSelectorTree((STRING)"Path2", 5L, yyt->U_1.V_110.TestNonlin.Path2);
}

static void yWriteTestValue
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"TestValue", 9L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"Next", 4L, yyt->U_1.V_111.TestValue.Next);
  yyIndentSelectorTree((STRING)"Path", 4L, yyt->U_1.V_111.TestValue.Path);
  yyIndentSelectorTree((STRING)"Expr", 4L, yyt->U_1.V_111.TestValue.Expr);
}

static void yWriteDecision
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Decision", 8L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"ThenPart", 8L, yyt->U_1.V_114.Decision.ThenPart);
  yyIndentSelectorTree((STRING)"ElsePart", 8L, yyt->U_1.V_114.Decision.ElsePart);
  yyIndentSelector((STRING)"Cases", 5L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_114.Decision.Cases, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"IsUnchanged", 11L);
  IO_WriteB(yyf, yyt->U_1.V_114.Decision.IsUnchanged);
  yyWriteNl();
}

static void yWriteDecided
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Decided", 7L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"ElsePart", 8L, yyt->U_1.V_115.Decided.ElsePart);
}

static void yyWriteTree
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  SHORTCARD yyLevel;

  yyLevel = yyIndentLevel;
  for (;;) {
    if (yyt == Tree_NoTree) {
      IO_WriteS(yyf, (STRING)" NoTree", 7L);
      yyWriteNl();
      goto EXIT_4;
    } else if (yyt->U_1.V_2.yyHead.yyMark == 0) {
      IO_WriteC(yyf, '^');
      IO_WriteI(yyf, (LONGINT)yyMapToLabel(yyt), 0L);
      yyWriteNl();
      goto EXIT_4;
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
    case Tree_Classes:;
      IO_WriteS(yyf, (STRING)"Classes", 7L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoClass:;
      IO_WriteS(yyf, (STRING)"NoClass", 7L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Class:;
      yWriteClass(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_5.Class.Next;
      break;
    case Tree_Attributes:;
      IO_WriteS(yyf, (STRING)"Attributes", 10L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoAttribute:;
      IO_WriteS(yyf, (STRING)"NoAttribute", 11L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_AttrOrAction:;
      yWriteAttrOrAction(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_8.AttrOrAction.Next;
      break;
    case Tree_Child:;
      yWriteChild(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_9.Child.Next;
      break;
    case Tree_Attribute:;
      yWriteAttribute(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_10.Attribute.Next;
      break;
    case Tree_ActionPart:;
      yWriteActionPart(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_11.ActionPart.Next;
      break;
    case Tree_Codes:;
      yWriteCodes(yyt);
      goto EXIT_4;
      break;
    case Tree_Designators:;
      IO_WriteS(yyf, (STRING)"Designators", 11L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoDesignator:;
      IO_WriteS(yyf, (STRING)"NoDesignator", 12L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Designator:;
      yWriteDesignator(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_15.Designator.Next;
      break;
    case Tree_Ident:;
      yWriteIdent(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_16.Ident.Next;
      break;
    case Tree_Remote:;
      yWriteRemote(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_17.Remote.Next;
      break;
    case Tree_Any:;
      yWriteAny(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_18.Any.Next;
      break;
    case Tree_Anys:;
      yWriteAnys(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_19.Anys.Next;
      break;
    case Tree_Layouts:;
      IO_WriteS(yyf, (STRING)"Layouts", 7L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoLayout:;
      IO_WriteS(yyf, (STRING)"NoLayout", 8L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_LayoutAny:;
      yWriteLayoutAny(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_22.LayoutAny.Next;
      break;
    case Tree_Names:;
      IO_WriteS(yyf, (STRING)"Names", 5L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoName:;
      IO_WriteS(yyf, (STRING)"NoName", 6L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Name:;
      yWriteName(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_25.Name.Next;
      break;
    case Tree_Spec:;
      yWriteSpec(yyt);
      yyIndentSelector((STRING)"Routines", 8L);
      yyt = yyt->U_1.V_26.Spec.Routines;
      break;
    case Tree_TreeNames:;
      IO_WriteS(yyf, (STRING)"TreeNames", 9L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoTreeName:;
      IO_WriteS(yyf, (STRING)"NoTreeName", 10L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_TreeName:;
      yWriteTreeName(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_29.TreeName.Next;
      break;
    case Tree_Routines:;
      IO_WriteS(yyf, (STRING)"Routines", 8L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoRoutine:;
      IO_WriteS(yyf, (STRING)"NoRoutine", 9L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Routine:;
      yWriteRoutine(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_32.Routine.Next;
      break;
    case Tree_Procedure:;
      yWriteProcedure(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_33.Procedure.Next;
      break;
    case Tree_Function:;
      yWriteFunction(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_34.Function.Next;
      break;
    case Tree_Predicate:;
      yWritePredicate(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_35.Predicate.Next;
      break;
    case Tree_Parameters:;
      IO_WriteS(yyf, (STRING)"Parameters", 10L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoParameter:;
      IO_WriteS(yyf, (STRING)"NoParameter", 11L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Param:;
      yWriteParam(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_38.Param.Next;
      break;
    case Tree_Type:;
      yWriteType(yyt);
      yyIndentSelector((STRING)"Names", 5L);
      yyt = yyt->U_1.V_39.Type.Names;
      break;
    case Tree_Rules:;
      IO_WriteS(yyf, (STRING)"Rules", 5L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoRule:;
      IO_WriteS(yyf, (STRING)"NoRule", 6L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Rule:;
      yWriteRule(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_42.Rule.Next;
      break;
    case Tree_Patterns:;
      IO_WriteS(yyf, (STRING)"Patterns", 8L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoPattern:;
      yWriteNoPattern(yyt);
      goto EXIT_4;
      break;
    case Tree_OnePattern:;
      yWriteOnePattern(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_45.OnePattern.Next;
      break;
    case Tree_OnePatternAlts:;
      yWriteOnePatternAlts(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_46.OnePatternAlts.Next;
      break;
    case Tree_PatternsList:;
      IO_WriteS(yyf, (STRING)"PatternsList", 12L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoPatternsList:;
      IO_WriteS(yyf, (STRING)"NoPatternsList", 14L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_OnePatternsList:;
      yWriteOnePatternsList(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_49.OnePatternsList.Next;
      break;
    case Tree_Pattern:;
      yWritePattern(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_50.Pattern.Path;
      break;
    case Tree_Decompose:;
      yWriteDecompose(yyt);
      yyIndentSelector((STRING)"Patterns", 8L);
      yyt = yyt->U_1.V_51.Decompose.Patterns;
      break;
    case Tree_VarDef:;
      yWriteVarDef(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_52.VarDef.Path;
      break;
    case Tree_NilTest:;
      yWriteNilTest(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_53.NilTest.Path;
      break;
    case Tree_DontCare1:;
      yWriteDontCare1(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_54.DontCare1.Path;
      break;
    case Tree_DontCare1Explicit:;
      yWriteDontCare1Explicit(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_55.DontCare1Explicit.Path;
      break;
    case Tree_DontCare1Internal:;
      yWriteDontCare1Internal(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_56.DontCare1Internal.Path;
      break;
    case Tree_DontCare:;
      yWriteDontCare(yyt);
      yyIndentSelector((STRING)"Tempos", 6L);
      yyt = yyt->U_1.V_57.DontCare.Tempos;
      break;
    case Tree_DontCareExplicit:;
      yWriteDontCareExplicit(yyt);
      yyIndentSelector((STRING)"Tempos", 6L);
      yyt = yyt->U_1.V_58.DontCareExplicit.Tempos;
      break;
    case Tree_DontCareInternal:;
      yWriteDontCareInternal(yyt);
      yyIndentSelector((STRING)"Tempos", 6L);
      yyt = yyt->U_1.V_59.DontCareInternal.Tempos;
      break;
    case Tree_Value:;
      yWriteValue(yyt);
      yyIndentSelector((STRING)"Expr", 4L);
      yyt = yyt->U_1.V_60.Value.Expr;
      break;
    case Tree_Exprs:;
      IO_WriteS(yyf, (STRING)"Exprs", 5L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoExpr:;
      yWriteNoExpr(yyt);
      goto EXIT_4;
      break;
    case Tree_OneExpr:;
      yWriteOneExpr(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_63.OneExpr.Next;
      break;
    case Tree_NamedExpr:;
      yWriteNamedExpr(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_64.NamedExpr.Next;
      break;
    case Tree_Expr:;
      yWriteExpr(yyt);
      goto EXIT_4;
      break;
    case Tree_Compose:;
      yWriteCompose(yyt);
      yyIndentSelector((STRING)"TypeDesc", 8L);
      yyt = yyt->U_1.V_66.Compose.TypeDesc;
      break;
    case Tree_VarUse:;
      yWriteVarUse(yyt);
      goto EXIT_4;
      break;
    case Tree_AttrDesc:;
      yWriteAttrDesc(yyt);
      goto EXIT_4;
      break;
    case Tree_Nil:;
      yWriteNil(yyt);
      goto EXIT_4;
      break;
    case Tree_Call:;
      yWriteCall(yyt);
      yyIndentSelector((STRING)"Patterns", 8L);
      yyt = yyt->U_1.V_70.Call.Patterns;
      break;
    case Tree_Binary:;
      yWriteBinary(yyt);
      yyIndentSelector((STRING)"Rop", 3L);
      yyt = yyt->U_1.V_71.Binary.Rop;
      break;
    case Tree_yy1:;
      yWriteyy1(yyt);
      yyIndentSelector((STRING)"Rop", 3L);
      yyt = yyt->U_1.V_72.yy1.Rop;
      break;
    case Tree_BinaryCompound:;
      yWriteBinaryCompound(yyt);
      yyIndentSelector((STRING)"Rop", 3L);
      yyt = yyt->U_1.V_73.BinaryCompound.Rop;
      break;
    case Tree_PreOperator:;
      yWritePreOperator(yyt);
      yyIndentSelector((STRING)"Expr", 4L);
      yyt = yyt->U_1.V_74.PreOperator.Expr;
      break;
    case Tree_PostOperator:;
      yWritePostOperator(yyt);
      yyIndentSelector((STRING)"Expr", 4L);
      yyt = yyt->U_1.V_75.PostOperator.Expr;
      break;
    case Tree_Index:;
      yWriteIndex(yyt);
      yyIndentSelector((STRING)"Exprs", 5L);
      yyt = yyt->U_1.V_76.Index.Exprs;
      break;
    case Tree_Parents:;
      yWriteParents(yyt);
      yyIndentSelector((STRING)"Expr", 4L);
      yyt = yyt->U_1.V_77.Parents.Expr;
      break;
    case Tree_TargetExpr:;
      yWriteTargetExpr(yyt);
      yyIndentSelector((STRING)"Expr", 4L);
      yyt = yyt->U_1.V_78.TargetExpr.Expr;
      break;
    case Tree_StringExpr:;
      yWriteStringExpr(yyt);
      goto EXIT_4;
      break;
    case Tree_Statements:;
      IO_WriteS(yyf, (STRING)"Statements", 10L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoStatement:;
      IO_WriteS(yyf, (STRING)"NoStatement", 11L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Statement:;
      yWriteStatement(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_82.Statement.Next;
      break;
    case Tree_ProcCall:;
      yWriteProcCall(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_83.ProcCall.Next;
      break;
    case Tree_Condition:;
      yWriteCondition(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_84.Condition.Next;
      break;
    case Tree_Assignment:;
      yWriteAssignment(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_85.Assignment.Next;
      break;
    case Tree_Reject:;
      yWriteReject(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_86.Reject.Next;
      break;
    case Tree_Fail:;
      yWriteFail(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_87.Fail.Next;
      break;
    case Tree_TargetStmt:;
      yWriteTargetStmt(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_88.TargetStmt.Next;
      break;
    case Tree_Nl:;
      yWriteNl(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_89.Nl.Next;
      break;
    case Tree_WriteStr:;
      yWriteWriteStr(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_90.WriteStr.Next;
      break;
    case Tree_Formals:;
      IO_WriteS(yyf, (STRING)"Formals", 7L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoFormal:;
      IO_WriteS(yyf, (STRING)"NoFormal", 8L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Formal:;
      yWriteFormal(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_93.Formal.Next;
      break;
    case Tree_PlainFormal:;
      yWritePlainFormal(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_94.PlainFormal.Next;
      break;
    case Tree_RoutineFormal:;
      yWriteRoutineFormal(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_95.RoutineFormal.Next;
      break;
    case Tree_DummyFormal:;
      yWriteDummyFormal(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_96.DummyFormal.Next;
      break;
    case Tree_TypeDesc:;
      IO_WriteS(yyf, (STRING)"TypeDesc", 8L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NodeTypes:;
      yWriteNodeTypes(yyt);
      yyIndentSelector((STRING)"TreeName", 8L);
      yyt = yyt->U_1.V_98.NodeTypes.TreeName;
      break;
    case Tree_UserType:;
      yWriteUserType(yyt);
      goto EXIT_4;
      break;
    case Tree_Path:;
      IO_WriteS(yyf, (STRING)"Path", 4L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Var:;
      yWriteVar(yyt);
      goto EXIT_4;
      break;
    case Tree_ConsType:;
      yWriteConsType(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_102.ConsType.Next;
      break;
    case Tree_Field:;
      yWriteField(yyt);
      yyIndentSelector((STRING)"Next", 4L);
      yyt = yyt->U_1.V_103.Field.Next;
      break;
    case Tree_Tests:;
      IO_WriteS(yyf, (STRING)"Tests", 5L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoTest:;
      IO_WriteS(yyf, (STRING)"NoTest", 6L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_OneTest:;
      yWriteOneTest(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_106.OneTest.Path;
      break;
    case Tree_TestKind:;
      yWriteTestKind(yyt);
      yyIndentSelector((STRING)"TypeDesc", 8L);
      yyt = yyt->U_1.V_107.TestKind.TypeDesc;
      break;
    case Tree_TestIsType:;
      yWriteTestIsType(yyt);
      yyIndentSelector((STRING)"TypeDesc", 8L);
      yyt = yyt->U_1.V_108.TestIsType.TypeDesc;
      break;
    case Tree_TestNil:;
      yWriteTestNil(yyt);
      yyIndentSelector((STRING)"Path", 4L);
      yyt = yyt->U_1.V_109.TestNil.Path;
      break;
    case Tree_TestNonlin:;
      yWriteTestNonlin(yyt);
      yyIndentSelector((STRING)"TypeDesc", 8L);
      yyt = yyt->U_1.V_110.TestNonlin.TypeDesc;
      break;
    case Tree_TestValue:;
      yWriteTestValue(yyt);
      yyIndentSelector((STRING)"TypeDesc", 8L);
      yyt = yyt->U_1.V_111.TestValue.TypeDesc;
      break;
    case Tree_Decisions:;
      IO_WriteS(yyf, (STRING)"Decisions", 9L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_NoDecision:;
      IO_WriteS(yyf, (STRING)"NoDecision", 10L);
      yyWriteNl();
      goto EXIT_4;
      break;
    case Tree_Decision:;
      yWriteDecision(yyt);
      yyIndentSelector((STRING)"OneTest", 7L);
      yyt = yyt->U_1.V_114.Decision.OneTest;
      break;
    case Tree_Decided:;
      yWriteDecided(yyt);
      yyIndentSelector((STRING)"Rule", 4L);
      yyt = yyt->U_1.V_115.Decided.Rule;
      break;
    default :
      goto EXIT_4;
      break;
    }
  } EXIT_4:;
  yyIndentLevel = yyLevel;
  yySetIndentInfo();
}

Tree_tTree Tree_ReverseTree
# ifdef __STDC__
(Tree_tTree yyOld)
# else
(yyOld)
Tree_tTree yyOld;
# endif
{
  Tree_tTree yyNew, yyNext, yyTail;

  yyNew = yyOld;
  yyTail = yyOld;
  for (;;) {
    switch (yyOld->U_1.V_1.Kind) {
    case Tree_Class:;
      yyNext = yyOld->U_1.V_5.Class.Next;
      yyOld->U_1.V_5.Class.Next = yyNew;
      break;
    case Tree_AttrOrAction:;
      yyNext = yyOld->U_1.V_8.AttrOrAction.Next;
      yyOld->U_1.V_8.AttrOrAction.Next = yyNew;
      break;
    case Tree_Child:;
      yyNext = yyOld->U_1.V_9.Child.Next;
      yyOld->U_1.V_9.Child.Next = yyNew;
      break;
    case Tree_Attribute:;
      yyNext = yyOld->U_1.V_10.Attribute.Next;
      yyOld->U_1.V_10.Attribute.Next = yyNew;
      break;
    case Tree_ActionPart:;
      yyNext = yyOld->U_1.V_11.ActionPart.Next;
      yyOld->U_1.V_11.ActionPart.Next = yyNew;
      break;
    case Tree_Designator:;
      yyNext = yyOld->U_1.V_15.Designator.Next;
      yyOld->U_1.V_15.Designator.Next = yyNew;
      break;
    case Tree_Ident:;
      yyNext = yyOld->U_1.V_16.Ident.Next;
      yyOld->U_1.V_16.Ident.Next = yyNew;
      break;
    case Tree_Remote:;
      yyNext = yyOld->U_1.V_17.Remote.Next;
      yyOld->U_1.V_17.Remote.Next = yyNew;
      break;
    case Tree_Any:;
      yyNext = yyOld->U_1.V_18.Any.Next;
      yyOld->U_1.V_18.Any.Next = yyNew;
      break;
    case Tree_Anys:;
      yyNext = yyOld->U_1.V_19.Anys.Next;
      yyOld->U_1.V_19.Anys.Next = yyNew;
      break;
    case Tree_LayoutAny:;
      yyNext = yyOld->U_1.V_22.LayoutAny.Next;
      yyOld->U_1.V_22.LayoutAny.Next = yyNew;
      break;
    case Tree_Name:;
      yyNext = yyOld->U_1.V_25.Name.Next;
      yyOld->U_1.V_25.Name.Next = yyNew;
      break;
    case Tree_TreeName:;
      yyNext = yyOld->U_1.V_29.TreeName.Next;
      yyOld->U_1.V_29.TreeName.Next = yyNew;
      break;
    case Tree_Routine:;
      yyNext = yyOld->U_1.V_32.Routine.Next;
      yyOld->U_1.V_32.Routine.Next = yyNew;
      break;
    case Tree_Procedure:;
      yyNext = yyOld->U_1.V_33.Procedure.Next;
      yyOld->U_1.V_33.Procedure.Next = yyNew;
      break;
    case Tree_Function:;
      yyNext = yyOld->U_1.V_34.Function.Next;
      yyOld->U_1.V_34.Function.Next = yyNew;
      break;
    case Tree_Predicate:;
      yyNext = yyOld->U_1.V_35.Predicate.Next;
      yyOld->U_1.V_35.Predicate.Next = yyNew;
      break;
    case Tree_Param:;
      yyNext = yyOld->U_1.V_38.Param.Next;
      yyOld->U_1.V_38.Param.Next = yyNew;
      break;
    case Tree_Rule:;
      yyNext = yyOld->U_1.V_42.Rule.Next;
      yyOld->U_1.V_42.Rule.Next = yyNew;
      break;
    case Tree_OnePattern:;
      yyNext = yyOld->U_1.V_45.OnePattern.Next;
      yyOld->U_1.V_45.OnePattern.Next = yyNew;
      break;
    case Tree_OnePatternAlts:;
      yyNext = yyOld->U_1.V_46.OnePatternAlts.Next;
      yyOld->U_1.V_46.OnePatternAlts.Next = yyNew;
      break;
    case Tree_OnePatternsList:;
      yyNext = yyOld->U_1.V_49.OnePatternsList.Next;
      yyOld->U_1.V_49.OnePatternsList.Next = yyNew;
      break;
    case Tree_OneExpr:;
      yyNext = yyOld->U_1.V_63.OneExpr.Next;
      yyOld->U_1.V_63.OneExpr.Next = yyNew;
      break;
    case Tree_NamedExpr:;
      yyNext = yyOld->U_1.V_64.NamedExpr.Next;
      yyOld->U_1.V_64.NamedExpr.Next = yyNew;
      break;
    case Tree_Statement:;
      yyNext = yyOld->U_1.V_82.Statement.Next;
      yyOld->U_1.V_82.Statement.Next = yyNew;
      break;
    case Tree_ProcCall:;
      yyNext = yyOld->U_1.V_83.ProcCall.Next;
      yyOld->U_1.V_83.ProcCall.Next = yyNew;
      break;
    case Tree_Condition:;
      yyNext = yyOld->U_1.V_84.Condition.Next;
      yyOld->U_1.V_84.Condition.Next = yyNew;
      break;
    case Tree_Assignment:;
      yyNext = yyOld->U_1.V_85.Assignment.Next;
      yyOld->U_1.V_85.Assignment.Next = yyNew;
      break;
    case Tree_Reject:;
      yyNext = yyOld->U_1.V_86.Reject.Next;
      yyOld->U_1.V_86.Reject.Next = yyNew;
      break;
    case Tree_Fail:;
      yyNext = yyOld->U_1.V_87.Fail.Next;
      yyOld->U_1.V_87.Fail.Next = yyNew;
      break;
    case Tree_TargetStmt:;
      yyNext = yyOld->U_1.V_88.TargetStmt.Next;
      yyOld->U_1.V_88.TargetStmt.Next = yyNew;
      break;
    case Tree_Nl:;
      yyNext = yyOld->U_1.V_89.Nl.Next;
      yyOld->U_1.V_89.Nl.Next = yyNew;
      break;
    case Tree_WriteStr:;
      yyNext = yyOld->U_1.V_90.WriteStr.Next;
      yyOld->U_1.V_90.WriteStr.Next = yyNew;
      break;
    case Tree_Formal:;
      yyNext = yyOld->U_1.V_93.Formal.Next;
      yyOld->U_1.V_93.Formal.Next = yyNew;
      break;
    case Tree_PlainFormal:;
      yyNext = yyOld->U_1.V_94.PlainFormal.Next;
      yyOld->U_1.V_94.PlainFormal.Next = yyNew;
      break;
    case Tree_RoutineFormal:;
      yyNext = yyOld->U_1.V_95.RoutineFormal.Next;
      yyOld->U_1.V_95.RoutineFormal.Next = yyNew;
      break;
    default :
      goto EXIT_5;
      break;
    }
    yyNew = yyOld;
    yyOld = yyNext;
  } EXIT_5:;
  switch (yyTail->U_1.V_1.Kind) {
  case Tree_Class:;
    yyTail->U_1.V_5.Class.Next = yyOld;
    break;
  case Tree_AttrOrAction:;
    yyTail->U_1.V_8.AttrOrAction.Next = yyOld;
    break;
  case Tree_Child:;
    yyTail->U_1.V_9.Child.Next = yyOld;
    break;
  case Tree_Attribute:;
    yyTail->U_1.V_10.Attribute.Next = yyOld;
    break;
  case Tree_ActionPart:;
    yyTail->U_1.V_11.ActionPart.Next = yyOld;
    break;
  case Tree_Designator:;
    yyTail->U_1.V_15.Designator.Next = yyOld;
    break;
  case Tree_Ident:;
    yyTail->U_1.V_16.Ident.Next = yyOld;
    break;
  case Tree_Remote:;
    yyTail->U_1.V_17.Remote.Next = yyOld;
    break;
  case Tree_Any:;
    yyTail->U_1.V_18.Any.Next = yyOld;
    break;
  case Tree_Anys:;
    yyTail->U_1.V_19.Anys.Next = yyOld;
    break;
  case Tree_LayoutAny:;
    yyTail->U_1.V_22.LayoutAny.Next = yyOld;
    break;
  case Tree_Name:;
    yyTail->U_1.V_25.Name.Next = yyOld;
    break;
  case Tree_TreeName:;
    yyTail->U_1.V_29.TreeName.Next = yyOld;
    break;
  case Tree_Routine:;
    yyTail->U_1.V_32.Routine.Next = yyOld;
    break;
  case Tree_Procedure:;
    yyTail->U_1.V_33.Procedure.Next = yyOld;
    break;
  case Tree_Function:;
    yyTail->U_1.V_34.Function.Next = yyOld;
    break;
  case Tree_Predicate:;
    yyTail->U_1.V_35.Predicate.Next = yyOld;
    break;
  case Tree_Param:;
    yyTail->U_1.V_38.Param.Next = yyOld;
    break;
  case Tree_Rule:;
    yyTail->U_1.V_42.Rule.Next = yyOld;
    break;
  case Tree_OnePattern:;
    yyTail->U_1.V_45.OnePattern.Next = yyOld;
    break;
  case Tree_OnePatternAlts:;
    yyTail->U_1.V_46.OnePatternAlts.Next = yyOld;
    break;
  case Tree_OnePatternsList:;
    yyTail->U_1.V_49.OnePatternsList.Next = yyOld;
    break;
  case Tree_OneExpr:;
    yyTail->U_1.V_63.OneExpr.Next = yyOld;
    break;
  case Tree_NamedExpr:;
    yyTail->U_1.V_64.NamedExpr.Next = yyOld;
    break;
  case Tree_Statement:;
    yyTail->U_1.V_82.Statement.Next = yyOld;
    break;
  case Tree_ProcCall:;
    yyTail->U_1.V_83.ProcCall.Next = yyOld;
    break;
  case Tree_Condition:;
    yyTail->U_1.V_84.Condition.Next = yyOld;
    break;
  case Tree_Assignment:;
    yyTail->U_1.V_85.Assignment.Next = yyOld;
    break;
  case Tree_Reject:;
    yyTail->U_1.V_86.Reject.Next = yyOld;
    break;
  case Tree_Fail:;
    yyTail->U_1.V_87.Fail.Next = yyOld;
    break;
  case Tree_TargetStmt:;
    yyTail->U_1.V_88.TargetStmt.Next = yyOld;
    break;
  case Tree_Nl:;
    yyTail->U_1.V_89.Nl.Next = yyOld;
    break;
  case Tree_WriteStr:;
    yyTail->U_1.V_90.WriteStr.Next = yyOld;
    break;
  case Tree_Formal:;
    yyTail->U_1.V_93.Formal.Next = yyOld;
    break;
  case Tree_PlainFormal:;
    yyTail->U_1.V_94.PlainFormal.Next = yyOld;
    break;
  case Tree_RoutineFormal:;
    yyTail->U_1.V_95.RoutineFormal.Next = yyOld;
    break;
  default :
    break;
  }
  return yyNew;
}

static void yyStoreOldToNew
# ifdef __STDC__
(Tree_tTree yyOld, Tree_tTree yyNew)
# else
(yyOld, yyNew)
Tree_tTree yyOld, yyNew;
# endif
{
  if (yyOldToNewCount == yyOldToNewStoreSize) {
    DynArray_ExtendArray((ADDRESS *)&yyOldToNewStorePtr, &yyOldToNewStoreSize, (LONGINT)sizeof(yytOldToNew));
  }
  yyOldToNewStorePtr->A[yyOldToNewCount].yyOld = yyOld;
  yyOldToNewStorePtr->A[yyOldToNewCount].yyNew = yyNew;
  INC(yyOldToNewCount);
}

static Tree_tTree yyMapOldToNew
# ifdef __STDC__
(Tree_tTree yyOld)
# else
(yyOld)
Tree_tTree yyOld;
# endif
{
  INTEGER yyi;

  {
    LONGINT B_9 = 0, B_10 = yyOldToNewCount - 1;

    if (B_9 <= B_10)
      for (yyi = B_9;; yyi += 1) {
        if (yyOldToNewStorePtr->A[yyi].yyOld == yyOld) {
          return yyOldToNewStorePtr->A[yyi].yyNew;
        }
        if (yyi >= B_10) break;
      }
  }
}

static void yyCopyTree
# ifdef __STDC__
(Tree_tTree yyt, yyPtrtTree yyNew)
# else
(yyt, yyNew)
Tree_tTree yyt;
yyPtrtTree yyNew;
# endif
{
  for (;;) {
    if (yyt == Tree_NoTree) {
      *yyNew = Tree_NoTree;
      return;
    }
    if (yyt->U_1.V_2.yyHead.yyMark == 0) {
      *yyNew = yyMapOldToNew(yyt);
      return;
    }
    *yyNew = Tree_MakeTree(yyt->U_1.V_1.Kind);
    if (yyt->U_1.V_2.yyHead.yyMark > 1) {
      yyStoreOldToNew(yyt, *yyNew);
    }
    yyt->U_1.V_2.yyHead.yyMark = 0;
    switch (yyt->U_1.V_1.Kind) {
    case Tree_Classes:;
      (*yyNew)->U_1.V_3.Classes = yyt->U_1.V_3.Classes;
      return;
      break;
    case Tree_NoClass:;
      (*yyNew)->U_1.V_4.NoClass = yyt->U_1.V_4.NoClass;
      return;
      break;
    case Tree_Class:;
      (*yyNew)->U_1.V_5.Class = yyt->U_1.V_5.Class;
      yyCopyTree(yyt->U_1.V_5.Class.Attributes, (yyPtrtTree)ADR((*yyNew)->U_1.V_5.Class.Attributes));
      yyCopyTree(yyt->U_1.V_5.Class.Extensions, (yyPtrtTree)ADR((*yyNew)->U_1.V_5.Class.Extensions));
      yyCopyTree(yyt->U_1.V_5.Class.BaseClass, (yyPtrtTree)ADR((*yyNew)->U_1.V_5.Class.BaseClass));
      yyCopyTree(yyt->U_1.V_5.Class.Formals, (yyPtrtTree)ADR((*yyNew)->U_1.V_5.Class.Formals));
      yyCopyTree(yyt->U_1.V_5.Class.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_5.Class.TypeDesc));
      yyt = yyt->U_1.V_5.Class.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_5.Class.Next);
      break;
    case Tree_Attributes:;
      (*yyNew)->U_1.V_6.Attributes = yyt->U_1.V_6.Attributes;
      return;
      break;
    case Tree_NoAttribute:;
      (*yyNew)->U_1.V_7.NoAttribute = yyt->U_1.V_7.NoAttribute;
      return;
      break;
    case Tree_AttrOrAction:;
      (*yyNew)->U_1.V_8.AttrOrAction = yyt->U_1.V_8.AttrOrAction;
      yyt = yyt->U_1.V_8.AttrOrAction.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_8.AttrOrAction.Next);
      break;
    case Tree_Child:;
      (*yyNew)->U_1.V_9.Child = yyt->U_1.V_9.Child;
      yyt = yyt->U_1.V_9.Child.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_9.Child.Next);
      break;
    case Tree_Attribute:;
      (*yyNew)->U_1.V_10.Attribute = yyt->U_1.V_10.Attribute;
      yyt = yyt->U_1.V_10.Attribute.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_10.Attribute.Next);
      break;
    case Tree_ActionPart:;
      (*yyNew)->U_1.V_11.ActionPart = yyt->U_1.V_11.ActionPart;
      yyt = yyt->U_1.V_11.ActionPart.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_11.ActionPart.Next);
      break;
    case Tree_Codes:;
      (*yyNew)->U_1.V_12.Codes = yyt->U_1.V_12.Codes;
      return;
      break;
    case Tree_Designators:;
      (*yyNew)->U_1.V_13.Designators = yyt->U_1.V_13.Designators;
      return;
      break;
    case Tree_NoDesignator:;
      (*yyNew)->U_1.V_14.NoDesignator = yyt->U_1.V_14.NoDesignator;
      return;
      break;
    case Tree_Designator:;
      (*yyNew)->U_1.V_15.Designator = yyt->U_1.V_15.Designator;
      yyt = yyt->U_1.V_15.Designator.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_15.Designator.Next);
      break;
    case Tree_Ident:;
      (*yyNew)->U_1.V_16.Ident = yyt->U_1.V_16.Ident;
      yyt = yyt->U_1.V_16.Ident.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_16.Ident.Next);
      break;
    case Tree_Remote:;
      (*yyNew)->U_1.V_17.Remote = yyt->U_1.V_17.Remote;
      yyCopyTree(yyt->U_1.V_17.Remote.Designators, (yyPtrtTree)ADR((*yyNew)->U_1.V_17.Remote.Designators));
      yyt = yyt->U_1.V_17.Remote.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_17.Remote.Next);
      break;
    case Tree_Any:;
      (*yyNew)->U_1.V_18.Any = yyt->U_1.V_18.Any;
      yyt = yyt->U_1.V_18.Any.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_18.Any.Next);
      break;
    case Tree_Anys:;
      (*yyNew)->U_1.V_19.Anys = yyt->U_1.V_19.Anys;
      yyCopyTree(yyt->U_1.V_19.Anys.Layouts, (yyPtrtTree)ADR((*yyNew)->U_1.V_19.Anys.Layouts));
      yyt = yyt->U_1.V_19.Anys.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_19.Anys.Next);
      break;
    case Tree_Layouts:;
      (*yyNew)->U_1.V_20.Layouts = yyt->U_1.V_20.Layouts;
      return;
      break;
    case Tree_NoLayout:;
      (*yyNew)->U_1.V_21.NoLayout = yyt->U_1.V_21.NoLayout;
      return;
      break;
    case Tree_LayoutAny:;
      (*yyNew)->U_1.V_22.LayoutAny = yyt->U_1.V_22.LayoutAny;
      yyt = yyt->U_1.V_22.LayoutAny.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_22.LayoutAny.Next);
      break;
    case Tree_Names:;
      (*yyNew)->U_1.V_23.Names = yyt->U_1.V_23.Names;
      return;
      break;
    case Tree_NoName:;
      (*yyNew)->U_1.V_24.NoName = yyt->U_1.V_24.NoName;
      return;
      break;
    case Tree_Name:;
      (*yyNew)->U_1.V_25.Name = yyt->U_1.V_25.Name;
      yyt = yyt->U_1.V_25.Name.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_25.Name.Next);
      break;
    case Tree_Spec:;
      (*yyNew)->U_1.V_26.Spec = yyt->U_1.V_26.Spec;
      yyCopyTree(yyt->U_1.V_26.Spec.TreeNames, (yyPtrtTree)ADR((*yyNew)->U_1.V_26.Spec.TreeNames));
      yyCopyTree(yyt->U_1.V_26.Spec.Public, (yyPtrtTree)ADR((*yyNew)->U_1.V_26.Spec.Public));
      yyCopyTree(yyt->U_1.V_26.Spec.Extern, (yyPtrtTree)ADR((*yyNew)->U_1.V_26.Spec.Extern));
      yyCopyTree(yyt->U_1.V_26.Spec.Codes, (yyPtrtTree)ADR((*yyNew)->U_1.V_26.Spec.Codes));
      yyt = yyt->U_1.V_26.Spec.Routines;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_26.Spec.Routines);
      break;
    case Tree_TreeNames:;
      (*yyNew)->U_1.V_27.TreeNames = yyt->U_1.V_27.TreeNames;
      return;
      break;
    case Tree_NoTreeName:;
      (*yyNew)->U_1.V_28.NoTreeName = yyt->U_1.V_28.NoTreeName;
      return;
      break;
    case Tree_TreeName:;
      (*yyNew)->U_1.V_29.TreeName = yyt->U_1.V_29.TreeName;
      yyCopyTree(yyt->U_1.V_29.TreeName.Classes, (yyPtrtTree)ADR((*yyNew)->U_1.V_29.TreeName.Classes));
      yyCopyTree(yyt->U_1.V_29.TreeName.EmptyType, (yyPtrtTree)ADR((*yyNew)->U_1.V_29.TreeName.EmptyType));
      yyCopyTree(yyt->U_1.V_29.TreeName.UniversalClass, (yyPtrtTree)ADR((*yyNew)->U_1.V_29.TreeName.UniversalClass));
      yyt = yyt->U_1.V_29.TreeName.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_29.TreeName.Next);
      break;
    case Tree_Routines:;
      (*yyNew)->U_1.V_30.Routines = yyt->U_1.V_30.Routines;
      return;
      break;
    case Tree_NoRoutine:;
      (*yyNew)->U_1.V_31.NoRoutine = yyt->U_1.V_31.NoRoutine;
      return;
      break;
    case Tree_Routine:;
      (*yyNew)->U_1.V_32.Routine = yyt->U_1.V_32.Routine;
      yyCopyTree(yyt->U_1.V_32.Routine.InParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.InParams));
      yyCopyTree(yyt->U_1.V_32.Routine.OutParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.OutParams));
      yyCopyTree(yyt->U_1.V_32.Routine.Extern, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.Extern));
      yyCopyTree(yyt->U_1.V_32.Routine.Rules, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.Rules));
      yyCopyTree(yyt->U_1.V_32.Routine.InForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.InForm));
      yyCopyTree(yyt->U_1.V_32.Routine.OutForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.OutForm));
      yyCopyTree(yyt->U_1.V_32.Routine.ParamDecls, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.ParamDecls));
      yyCopyTree(yyt->U_1.V_32.Routine.Decisions, (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.Decisions));
      yyt = yyt->U_1.V_32.Routine.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_32.Routine.Next);
      break;
    case Tree_Procedure:;
      (*yyNew)->U_1.V_33.Procedure = yyt->U_1.V_33.Procedure;
      yyCopyTree(yyt->U_1.V_33.Procedure.InParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.InParams));
      yyCopyTree(yyt->U_1.V_33.Procedure.OutParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.OutParams));
      yyCopyTree(yyt->U_1.V_33.Procedure.Extern, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.Extern));
      yyCopyTree(yyt->U_1.V_33.Procedure.Rules, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.Rules));
      yyCopyTree(yyt->U_1.V_33.Procedure.InForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.InForm));
      yyCopyTree(yyt->U_1.V_33.Procedure.OutForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.OutForm));
      yyCopyTree(yyt->U_1.V_33.Procedure.ParamDecls, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.ParamDecls));
      yyCopyTree(yyt->U_1.V_33.Procedure.Decisions, (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.Decisions));
      yyt = yyt->U_1.V_33.Procedure.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_33.Procedure.Next);
      break;
    case Tree_Function:;
      (*yyNew)->U_1.V_34.Function = yyt->U_1.V_34.Function;
      yyCopyTree(yyt->U_1.V_34.Function.InParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.InParams));
      yyCopyTree(yyt->U_1.V_34.Function.OutParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.OutParams));
      yyCopyTree(yyt->U_1.V_34.Function.Extern, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.Extern));
      yyCopyTree(yyt->U_1.V_34.Function.Rules, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.Rules));
      yyCopyTree(yyt->U_1.V_34.Function.InForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.InForm));
      yyCopyTree(yyt->U_1.V_34.Function.OutForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.OutForm));
      yyCopyTree(yyt->U_1.V_34.Function.ParamDecls, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.ParamDecls));
      yyCopyTree(yyt->U_1.V_34.Function.Decisions, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.Decisions));
      yyCopyTree(yyt->U_1.V_34.Function.ReturnParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.ReturnParams));
      yyCopyTree(yyt->U_1.V_34.Function.ReturnForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.ReturnForm));
      yyt = yyt->U_1.V_34.Function.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_34.Function.Next);
      break;
    case Tree_Predicate:;
      (*yyNew)->U_1.V_35.Predicate = yyt->U_1.V_35.Predicate;
      yyCopyTree(yyt->U_1.V_35.Predicate.InParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.InParams));
      yyCopyTree(yyt->U_1.V_35.Predicate.OutParams, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.OutParams));
      yyCopyTree(yyt->U_1.V_35.Predicate.Extern, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.Extern));
      yyCopyTree(yyt->U_1.V_35.Predicate.Rules, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.Rules));
      yyCopyTree(yyt->U_1.V_35.Predicate.InForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.InForm));
      yyCopyTree(yyt->U_1.V_35.Predicate.OutForm, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.OutForm));
      yyCopyTree(yyt->U_1.V_35.Predicate.ParamDecls, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.ParamDecls));
      yyCopyTree(yyt->U_1.V_35.Predicate.Decisions, (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.Decisions));
      yyt = yyt->U_1.V_35.Predicate.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_35.Predicate.Next);
      break;
    case Tree_Parameters:;
      (*yyNew)->U_1.V_36.Parameters = yyt->U_1.V_36.Parameters;
      return;
      break;
    case Tree_NoParameter:;
      (*yyNew)->U_1.V_37.NoParameter = yyt->U_1.V_37.NoParameter;
      return;
      break;
    case Tree_Param:;
      (*yyNew)->U_1.V_38.Param = yyt->U_1.V_38.Param;
      yyCopyTree(yyt->U_1.V_38.Param.Type, (yyPtrtTree)ADR((*yyNew)->U_1.V_38.Param.Type));
      yyt = yyt->U_1.V_38.Param.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_38.Param.Next);
      break;
    case Tree_Type:;
      (*yyNew)->U_1.V_39.Type = yyt->U_1.V_39.Type;
      yyt = yyt->U_1.V_39.Type.Names;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_39.Type.Names);
      break;
    case Tree_Rules:;
      (*yyNew)->U_1.V_40.Rules = yyt->U_1.V_40.Rules;
      return;
      break;
    case Tree_NoRule:;
      (*yyNew)->U_1.V_41.NoRule = yyt->U_1.V_41.NoRule;
      return;
      break;
    case Tree_Rule:;
      (*yyNew)->U_1.V_42.Rule = yyt->U_1.V_42.Rule;
      yyCopyTree(yyt->U_1.V_42.Rule.Patterns, (yyPtrtTree)ADR((*yyNew)->U_1.V_42.Rule.Patterns));
      yyCopyTree(yyt->U_1.V_42.Rule.Exprs, (yyPtrtTree)ADR((*yyNew)->U_1.V_42.Rule.Exprs));
      yyCopyTree(yyt->U_1.V_42.Rule.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_42.Rule.Expr));
      yyCopyTree(yyt->U_1.V_42.Rule.Statements, (yyPtrtTree)ADR((*yyNew)->U_1.V_42.Rule.Statements));
      yyCopyTree(yyt->U_1.V_42.Rule.VarDecls, (yyPtrtTree)ADR((*yyNew)->U_1.V_42.Rule.VarDecls));
      yyCopyTree(yyt->U_1.V_42.Rule.Tests, (yyPtrtTree)ADR((*yyNew)->U_1.V_42.Rule.Tests));
      yyt = yyt->U_1.V_42.Rule.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_42.Rule.Next);
      break;
    case Tree_Patterns:;
      (*yyNew)->U_1.V_43.Patterns = yyt->U_1.V_43.Patterns;
      return;
      break;
    case Tree_NoPattern:;
      (*yyNew)->U_1.V_44.NoPattern = yyt->U_1.V_44.NoPattern;
      return;
      break;
    case Tree_OnePattern:;
      (*yyNew)->U_1.V_45.OnePattern = yyt->U_1.V_45.OnePattern;
      yyCopyTree(yyt->U_1.V_45.OnePattern.Pattern, (yyPtrtTree)ADR((*yyNew)->U_1.V_45.OnePattern.Pattern));
      yyt = yyt->U_1.V_45.OnePattern.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_45.OnePattern.Next);
      break;
    case Tree_OnePatternAlts:;
      (*yyNew)->U_1.V_46.OnePatternAlts = yyt->U_1.V_46.OnePatternAlts;
      yyCopyTree(yyt->U_1.V_46.OnePatternAlts.PatternsList, (yyPtrtTree)ADR((*yyNew)->U_1.V_46.OnePatternAlts.PatternsList));
      yyCopyTree(yyt->U_1.V_46.OnePatternAlts.Current, (yyPtrtTree)ADR((*yyNew)->U_1.V_46.OnePatternAlts.Current));
      yyt = yyt->U_1.V_46.OnePatternAlts.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_46.OnePatternAlts.Next);
      break;
    case Tree_PatternsList:;
      (*yyNew)->U_1.V_47.PatternsList = yyt->U_1.V_47.PatternsList;
      return;
      break;
    case Tree_NoPatternsList:;
      (*yyNew)->U_1.V_48.NoPatternsList = yyt->U_1.V_48.NoPatternsList;
      return;
      break;
    case Tree_OnePatternsList:;
      (*yyNew)->U_1.V_49.OnePatternsList = yyt->U_1.V_49.OnePatternsList;
      yyCopyTree(yyt->U_1.V_49.OnePatternsList.Patterns, (yyPtrtTree)ADR((*yyNew)->U_1.V_49.OnePatternsList.Patterns));
      yyt = yyt->U_1.V_49.OnePatternsList.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_49.OnePatternsList.Next);
      break;
    case Tree_Pattern:;
      (*yyNew)->U_1.V_50.Pattern = yyt->U_1.V_50.Pattern;
      yyCopyTree(yyt->U_1.V_50.Pattern.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_50.Pattern.TypeDesc));
      yyt = yyt->U_1.V_50.Pattern.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_50.Pattern.Path);
      break;
    case Tree_Decompose:;
      (*yyNew)->U_1.V_51.Decompose = yyt->U_1.V_51.Decompose;
      yyCopyTree(yyt->U_1.V_51.Decompose.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_51.Decompose.TypeDesc));
      yyCopyTree(yyt->U_1.V_51.Decompose.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_51.Decompose.Path));
      yyCopyTree(yyt->U_1.V_51.Decompose.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_51.Decompose.Expr));
      yyt = yyt->U_1.V_51.Decompose.Patterns;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_51.Decompose.Patterns);
      break;
    case Tree_VarDef:;
      (*yyNew)->U_1.V_52.VarDef = yyt->U_1.V_52.VarDef;
      yyCopyTree(yyt->U_1.V_52.VarDef.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_52.VarDef.TypeDesc));
      yyt = yyt->U_1.V_52.VarDef.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_52.VarDef.Path);
      break;
    case Tree_NilTest:;
      (*yyNew)->U_1.V_53.NilTest = yyt->U_1.V_53.NilTest;
      yyCopyTree(yyt->U_1.V_53.NilTest.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_53.NilTest.TypeDesc));
      yyt = yyt->U_1.V_53.NilTest.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_53.NilTest.Path);
      break;
    case Tree_DontCare1:;
      (*yyNew)->U_1.V_54.DontCare1 = yyt->U_1.V_54.DontCare1;
      yyCopyTree(yyt->U_1.V_54.DontCare1.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_54.DontCare1.TypeDesc));
      yyt = yyt->U_1.V_54.DontCare1.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_54.DontCare1.Path);
      break;
    case Tree_DontCare1Explicit:;
      (*yyNew)->U_1.V_55.DontCare1Explicit = yyt->U_1.V_55.DontCare1Explicit;
      yyCopyTree(yyt->U_1.V_55.DontCare1Explicit.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_55.DontCare1Explicit.TypeDesc));
      yyt = yyt->U_1.V_55.DontCare1Explicit.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_55.DontCare1Explicit.Path);
      break;
    case Tree_DontCare1Internal:;
      (*yyNew)->U_1.V_56.DontCare1Internal = yyt->U_1.V_56.DontCare1Internal;
      yyCopyTree(yyt->U_1.V_56.DontCare1Internal.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_56.DontCare1Internal.TypeDesc));
      yyt = yyt->U_1.V_56.DontCare1Internal.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_56.DontCare1Internal.Path);
      break;
    case Tree_DontCare:;
      (*yyNew)->U_1.V_57.DontCare = yyt->U_1.V_57.DontCare;
      yyCopyTree(yyt->U_1.V_57.DontCare.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_57.DontCare.TypeDesc));
      yyCopyTree(yyt->U_1.V_57.DontCare.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_57.DontCare.Path));
      yyt = yyt->U_1.V_57.DontCare.Tempos;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_57.DontCare.Tempos);
      break;
    case Tree_DontCareExplicit:;
      (*yyNew)->U_1.V_58.DontCareExplicit = yyt->U_1.V_58.DontCareExplicit;
      yyCopyTree(yyt->U_1.V_58.DontCareExplicit.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_58.DontCareExplicit.TypeDesc));
      yyCopyTree(yyt->U_1.V_58.DontCareExplicit.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_58.DontCareExplicit.Path));
      yyt = yyt->U_1.V_58.DontCareExplicit.Tempos;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_58.DontCareExplicit.Tempos);
      break;
    case Tree_DontCareInternal:;
      (*yyNew)->U_1.V_59.DontCareInternal = yyt->U_1.V_59.DontCareInternal;
      yyCopyTree(yyt->U_1.V_59.DontCareInternal.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_59.DontCareInternal.TypeDesc));
      yyCopyTree(yyt->U_1.V_59.DontCareInternal.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_59.DontCareInternal.Path));
      yyt = yyt->U_1.V_59.DontCareInternal.Tempos;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_59.DontCareInternal.Tempos);
      break;
    case Tree_Value:;
      (*yyNew)->U_1.V_60.Value = yyt->U_1.V_60.Value;
      yyCopyTree(yyt->U_1.V_60.Value.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_60.Value.TypeDesc));
      yyCopyTree(yyt->U_1.V_60.Value.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_60.Value.Path));
      yyt = yyt->U_1.V_60.Value.Expr;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_60.Value.Expr);
      break;
    case Tree_Exprs:;
      (*yyNew)->U_1.V_61.Exprs = yyt->U_1.V_61.Exprs;
      return;
      break;
    case Tree_NoExpr:;
      (*yyNew)->U_1.V_62.NoExpr = yyt->U_1.V_62.NoExpr;
      return;
      break;
    case Tree_OneExpr:;
      (*yyNew)->U_1.V_63.OneExpr = yyt->U_1.V_63.OneExpr;
      yyCopyTree(yyt->U_1.V_63.OneExpr.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_63.OneExpr.Expr));
      yyt = yyt->U_1.V_63.OneExpr.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_63.OneExpr.Next);
      break;
    case Tree_NamedExpr:;
      (*yyNew)->U_1.V_64.NamedExpr = yyt->U_1.V_64.NamedExpr;
      yyCopyTree(yyt->U_1.V_64.NamedExpr.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_64.NamedExpr.Expr));
      yyt = yyt->U_1.V_64.NamedExpr.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_64.NamedExpr.Next);
      break;
    case Tree_Expr:;
      (*yyNew)->U_1.V_65.Expr = yyt->U_1.V_65.Expr;
      return;
      break;
    case Tree_Compose:;
      (*yyNew)->U_1.V_66.Compose = yyt->U_1.V_66.Compose;
      yyCopyTree(yyt->U_1.V_66.Compose.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_66.Compose.Expr));
      yyCopyTree(yyt->U_1.V_66.Compose.Exprs, (yyPtrtTree)ADR((*yyNew)->U_1.V_66.Compose.Exprs));
      yyt = yyt->U_1.V_66.Compose.TypeDesc;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_66.Compose.TypeDesc);
      break;
    case Tree_VarUse:;
      (*yyNew)->U_1.V_67.VarUse = yyt->U_1.V_67.VarUse;
      return;
      break;
    case Tree_AttrDesc:;
      (*yyNew)->U_1.V_68.AttrDesc = yyt->U_1.V_68.AttrDesc;
      return;
      break;
    case Tree_Nil:;
      (*yyNew)->U_1.V_69.Nil = yyt->U_1.V_69.Nil;
      return;
      break;
    case Tree_Call:;
      (*yyNew)->U_1.V_70.Call = yyt->U_1.V_70.Call;
      yyCopyTree(yyt->U_1.V_70.Call.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_70.Call.Expr));
      yyCopyTree(yyt->U_1.V_70.Call.Exprs, (yyPtrtTree)ADR((*yyNew)->U_1.V_70.Call.Exprs));
      yyt = yyt->U_1.V_70.Call.Patterns;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_70.Call.Patterns);
      break;
    case Tree_Binary:;
      (*yyNew)->U_1.V_71.Binary = yyt->U_1.V_71.Binary;
      yyCopyTree(yyt->U_1.V_71.Binary.Lop, (yyPtrtTree)ADR((*yyNew)->U_1.V_71.Binary.Lop));
      yyt = yyt->U_1.V_71.Binary.Rop;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_71.Binary.Rop);
      break;
    case Tree_yy1:;
      (*yyNew)->U_1.V_72.yy1 = yyt->U_1.V_72.yy1;
      yyCopyTree(yyt->U_1.V_72.yy1.Lop, (yyPtrtTree)ADR((*yyNew)->U_1.V_72.yy1.Lop));
      yyt = yyt->U_1.V_72.yy1.Rop;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_72.yy1.Rop);
      break;
    case Tree_BinaryCompound:;
      (*yyNew)->U_1.V_73.BinaryCompound = yyt->U_1.V_73.BinaryCompound;
      yyCopyTree(yyt->U_1.V_73.BinaryCompound.Lop, (yyPtrtTree)ADR((*yyNew)->U_1.V_73.BinaryCompound.Lop));
      yyt = yyt->U_1.V_73.BinaryCompound.Rop;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_73.BinaryCompound.Rop);
      break;
    case Tree_PreOperator:;
      (*yyNew)->U_1.V_74.PreOperator = yyt->U_1.V_74.PreOperator;
      yyt = yyt->U_1.V_74.PreOperator.Expr;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_74.PreOperator.Expr);
      break;
    case Tree_PostOperator:;
      (*yyNew)->U_1.V_75.PostOperator = yyt->U_1.V_75.PostOperator;
      yyt = yyt->U_1.V_75.PostOperator.Expr;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_75.PostOperator.Expr);
      break;
    case Tree_Index:;
      (*yyNew)->U_1.V_76.Index = yyt->U_1.V_76.Index;
      yyCopyTree(yyt->U_1.V_76.Index.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_76.Index.Expr));
      yyt = yyt->U_1.V_76.Index.Exprs;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_76.Index.Exprs);
      break;
    case Tree_Parents:;
      (*yyNew)->U_1.V_77.Parents = yyt->U_1.V_77.Parents;
      yyt = yyt->U_1.V_77.Parents.Expr;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_77.Parents.Expr);
      break;
    case Tree_TargetExpr:;
      (*yyNew)->U_1.V_78.TargetExpr = yyt->U_1.V_78.TargetExpr;
      yyt = yyt->U_1.V_78.TargetExpr.Expr;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_78.TargetExpr.Expr);
      break;
    case Tree_StringExpr:;
      (*yyNew)->U_1.V_79.StringExpr = yyt->U_1.V_79.StringExpr;
      return;
      break;
    case Tree_Statements:;
      (*yyNew)->U_1.V_80.Statements = yyt->U_1.V_80.Statements;
      return;
      break;
    case Tree_NoStatement:;
      (*yyNew)->U_1.V_81.NoStatement = yyt->U_1.V_81.NoStatement;
      return;
      break;
    case Tree_Statement:;
      (*yyNew)->U_1.V_82.Statement = yyt->U_1.V_82.Statement;
      yyt = yyt->U_1.V_82.Statement.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_82.Statement.Next);
      break;
    case Tree_ProcCall:;
      (*yyNew)->U_1.V_83.ProcCall = yyt->U_1.V_83.ProcCall;
      yyCopyTree(yyt->U_1.V_83.ProcCall.Call, (yyPtrtTree)ADR((*yyNew)->U_1.V_83.ProcCall.Call));
      yyt = yyt->U_1.V_83.ProcCall.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_83.ProcCall.Next);
      break;
    case Tree_Condition:;
      (*yyNew)->U_1.V_84.Condition = yyt->U_1.V_84.Condition;
      yyCopyTree(yyt->U_1.V_84.Condition.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_84.Condition.Expr));
      yyt = yyt->U_1.V_84.Condition.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_84.Condition.Next);
      break;
    case Tree_Assignment:;
      (*yyNew)->U_1.V_85.Assignment = yyt->U_1.V_85.Assignment;
      yyCopyTree(yyt->U_1.V_85.Assignment.Adr, (yyPtrtTree)ADR((*yyNew)->U_1.V_85.Assignment.Adr));
      yyCopyTree(yyt->U_1.V_85.Assignment.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_85.Assignment.Expr));
      yyt = yyt->U_1.V_85.Assignment.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_85.Assignment.Next);
      break;
    case Tree_Reject:;
      (*yyNew)->U_1.V_86.Reject = yyt->U_1.V_86.Reject;
      yyt = yyt->U_1.V_86.Reject.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_86.Reject.Next);
      break;
    case Tree_Fail:;
      (*yyNew)->U_1.V_87.Fail = yyt->U_1.V_87.Fail;
      yyt = yyt->U_1.V_87.Fail.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_87.Fail.Next);
      break;
    case Tree_TargetStmt:;
      (*yyNew)->U_1.V_88.TargetStmt = yyt->U_1.V_88.TargetStmt;
      yyCopyTree(yyt->U_1.V_88.TargetStmt.Parameters, (yyPtrtTree)ADR((*yyNew)->U_1.V_88.TargetStmt.Parameters));
      yyCopyTree(yyt->U_1.V_88.TargetStmt.Stmt, (yyPtrtTree)ADR((*yyNew)->U_1.V_88.TargetStmt.Stmt));
      yyt = yyt->U_1.V_88.TargetStmt.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_88.TargetStmt.Next);
      break;
    case Tree_Nl:;
      (*yyNew)->U_1.V_89.Nl = yyt->U_1.V_89.Nl;
      yyt = yyt->U_1.V_89.Nl.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_89.Nl.Next);
      break;
    case Tree_WriteStr:;
      (*yyNew)->U_1.V_90.WriteStr = yyt->U_1.V_90.WriteStr;
      yyt = yyt->U_1.V_90.WriteStr.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_90.WriteStr.Next);
      break;
    case Tree_Formals:;
      (*yyNew)->U_1.V_91.Formals = yyt->U_1.V_91.Formals;
      return;
      break;
    case Tree_NoFormal:;
      (*yyNew)->U_1.V_92.NoFormal = yyt->U_1.V_92.NoFormal;
      return;
      break;
    case Tree_Formal:;
      (*yyNew)->U_1.V_93.Formal = yyt->U_1.V_93.Formal;
      yyCopyTree(yyt->U_1.V_93.Formal.Hides, (yyPtrtTree)ADR((*yyNew)->U_1.V_93.Formal.Hides));
      yyCopyTree(yyt->U_1.V_93.Formal.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_93.Formal.TypeDesc));
      yyCopyTree(yyt->U_1.V_93.Formal.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_93.Formal.Path));
      yyt = yyt->U_1.V_93.Formal.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_93.Formal.Next);
      break;
    case Tree_PlainFormal:;
      (*yyNew)->U_1.V_94.PlainFormal = yyt->U_1.V_94.PlainFormal;
      yyCopyTree(yyt->U_1.V_94.PlainFormal.Hides, (yyPtrtTree)ADR((*yyNew)->U_1.V_94.PlainFormal.Hides));
      yyCopyTree(yyt->U_1.V_94.PlainFormal.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_94.PlainFormal.TypeDesc));
      yyCopyTree(yyt->U_1.V_94.PlainFormal.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_94.PlainFormal.Path));
      yyt = yyt->U_1.V_94.PlainFormal.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_94.PlainFormal.Next);
      break;
    case Tree_RoutineFormal:;
      (*yyNew)->U_1.V_95.RoutineFormal = yyt->U_1.V_95.RoutineFormal;
      yyCopyTree(yyt->U_1.V_95.RoutineFormal.Hides, (yyPtrtTree)ADR((*yyNew)->U_1.V_95.RoutineFormal.Hides));
      yyCopyTree(yyt->U_1.V_95.RoutineFormal.TypeDesc, (yyPtrtTree)ADR((*yyNew)->U_1.V_95.RoutineFormal.TypeDesc));
      yyCopyTree(yyt->U_1.V_95.RoutineFormal.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_95.RoutineFormal.Path));
      yyCopyTree(yyt->U_1.V_95.RoutineFormal.TargetClass, (yyPtrtTree)ADR((*yyNew)->U_1.V_95.RoutineFormal.TargetClass));
      yyt = yyt->U_1.V_95.RoutineFormal.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_95.RoutineFormal.Next);
      break;
    case Tree_DummyFormal:;
      (*yyNew)->U_1.V_96.DummyFormal = yyt->U_1.V_96.DummyFormal;
      yyt = yyt->U_1.V_96.DummyFormal.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_96.DummyFormal.Next);
      break;
    case Tree_TypeDesc:;
      (*yyNew)->U_1.V_97.TypeDesc = yyt->U_1.V_97.TypeDesc;
      return;
      break;
    case Tree_NodeTypes:;
      (*yyNew)->U_1.V_98.NodeTypes = yyt->U_1.V_98.NodeTypes;
      yyt = yyt->U_1.V_98.NodeTypes.TreeName;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_98.NodeTypes.TreeName);
      break;
    case Tree_UserType:;
      (*yyNew)->U_1.V_99.UserType = yyt->U_1.V_99.UserType;
      return;
      break;
    case Tree_Path:;
      (*yyNew)->U_1.V_100.Path = yyt->U_1.V_100.Path;
      return;
      break;
    case Tree_Var:;
      (*yyNew)->U_1.V_101.Var = yyt->U_1.V_101.Var;
      return;
      break;
    case Tree_ConsType:;
      (*yyNew)->U_1.V_102.ConsType = yyt->U_1.V_102.ConsType;
      yyt = yyt->U_1.V_102.ConsType.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_102.ConsType.Next);
      break;
    case Tree_Field:;
      (*yyNew)->U_1.V_103.Field = yyt->U_1.V_103.Field;
      yyt = yyt->U_1.V_103.Field.Next;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_103.Field.Next);
      break;
    case Tree_Tests:;
      (*yyNew)->U_1.V_104.Tests = yyt->U_1.V_104.Tests;
      return;
      break;
    case Tree_NoTest:;
      (*yyNew)->U_1.V_105.NoTest = yyt->U_1.V_105.NoTest;
      return;
      break;
    case Tree_OneTest:;
      (*yyNew)->U_1.V_106.OneTest = yyt->U_1.V_106.OneTest;
      yyCopyTree(yyt->U_1.V_106.OneTest.Next, (yyPtrtTree)ADR((*yyNew)->U_1.V_106.OneTest.Next));
      yyt = yyt->U_1.V_106.OneTest.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_106.OneTest.Path);
      break;
    case Tree_TestKind:;
      (*yyNew)->U_1.V_107.TestKind = yyt->U_1.V_107.TestKind;
      yyCopyTree(yyt->U_1.V_107.TestKind.Next, (yyPtrtTree)ADR((*yyNew)->U_1.V_107.TestKind.Next));
      yyCopyTree(yyt->U_1.V_107.TestKind.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_107.TestKind.Path));
      yyt = yyt->U_1.V_107.TestKind.TypeDesc;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_107.TestKind.TypeDesc);
      break;
    case Tree_TestIsType:;
      (*yyNew)->U_1.V_108.TestIsType = yyt->U_1.V_108.TestIsType;
      yyCopyTree(yyt->U_1.V_108.TestIsType.Next, (yyPtrtTree)ADR((*yyNew)->U_1.V_108.TestIsType.Next));
      yyCopyTree(yyt->U_1.V_108.TestIsType.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_108.TestIsType.Path));
      yyt = yyt->U_1.V_108.TestIsType.TypeDesc;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_108.TestIsType.TypeDesc);
      break;
    case Tree_TestNil:;
      (*yyNew)->U_1.V_109.TestNil = yyt->U_1.V_109.TestNil;
      yyCopyTree(yyt->U_1.V_109.TestNil.Next, (yyPtrtTree)ADR((*yyNew)->U_1.V_109.TestNil.Next));
      yyt = yyt->U_1.V_109.TestNil.Path;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_109.TestNil.Path);
      break;
    case Tree_TestNonlin:;
      (*yyNew)->U_1.V_110.TestNonlin = yyt->U_1.V_110.TestNonlin;
      yyCopyTree(yyt->U_1.V_110.TestNonlin.Next, (yyPtrtTree)ADR((*yyNew)->U_1.V_110.TestNonlin.Next));
      yyCopyTree(yyt->U_1.V_110.TestNonlin.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_110.TestNonlin.Path));
      yyCopyTree(yyt->U_1.V_110.TestNonlin.Path2, (yyPtrtTree)ADR((*yyNew)->U_1.V_110.TestNonlin.Path2));
      yyt = yyt->U_1.V_110.TestNonlin.TypeDesc;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_110.TestNonlin.TypeDesc);
      break;
    case Tree_TestValue:;
      (*yyNew)->U_1.V_111.TestValue = yyt->U_1.V_111.TestValue;
      yyCopyTree(yyt->U_1.V_111.TestValue.Next, (yyPtrtTree)ADR((*yyNew)->U_1.V_111.TestValue.Next));
      yyCopyTree(yyt->U_1.V_111.TestValue.Path, (yyPtrtTree)ADR((*yyNew)->U_1.V_111.TestValue.Path));
      yyCopyTree(yyt->U_1.V_111.TestValue.Expr, (yyPtrtTree)ADR((*yyNew)->U_1.V_111.TestValue.Expr));
      yyt = yyt->U_1.V_111.TestValue.TypeDesc;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_111.TestValue.TypeDesc);
      break;
    case Tree_Decisions:;
      (*yyNew)->U_1.V_112.Decisions = yyt->U_1.V_112.Decisions;
      return;
      break;
    case Tree_NoDecision:;
      (*yyNew)->U_1.V_113.NoDecision = yyt->U_1.V_113.NoDecision;
      return;
      break;
    case Tree_Decision:;
      (*yyNew)->U_1.V_114.Decision = yyt->U_1.V_114.Decision;
      yyCopyTree(yyt->U_1.V_114.Decision.ThenPart, (yyPtrtTree)ADR((*yyNew)->U_1.V_114.Decision.ThenPart));
      yyCopyTree(yyt->U_1.V_114.Decision.ElsePart, (yyPtrtTree)ADR((*yyNew)->U_1.V_114.Decision.ElsePart));
      yyt = yyt->U_1.V_114.Decision.OneTest;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_114.Decision.OneTest);
      break;
    case Tree_Decided:;
      (*yyNew)->U_1.V_115.Decided = yyt->U_1.V_115.Decided;
      yyCopyTree(yyt->U_1.V_115.Decided.ElsePart, (yyPtrtTree)ADR((*yyNew)->U_1.V_115.Decided.ElsePart));
      yyt = yyt->U_1.V_115.Decided.Rule;
      yyNew = (yyPtrtTree)ADR((*yyNew)->U_1.V_115.Decided.Rule);
      break;
    default :
      break;
    }
  } EXIT_6:;
}

Tree_tTree Tree_CopyTree
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Tree_tTree yyNew;

  yyMark(yyt);
  yyOldToNewCount = 0;
  yyCopyTree(yyt, (yyPtrtTree)ADR(yyNew));
  return yyNew;
}

static BOOLEAN yyyIsEqual
# ifdef __STDC__
(CHAR yya[], LONGCARD O_5)
# else
(yya, O_5)
CHAR yya[];
LONGCARD O_5;
# endif
{
  INTEGER yyi;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_5 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yya, O_5, CHAR)
  if (yyLength >= 0 && yyString.A[yyLength] == ' ') {
    if (yyLength - 1 != (INTEGER)(O_5 - 1)) {
      FREE_OPEN_ARRAYS
      return FALSE;
    }
    {
      LONGINT B_11 = 0, B_12 = yyLength - 1;

      if (B_11 <= B_12)
        for (yyi = B_11;; yyi += 1) {
          if (yyString.A[yyi] != yya[yyi]) {
            FREE_OPEN_ARRAYS
            return FALSE;
          }
          if (yyi >= B_12) break;
        }
    }
  } else {
    if (yyLength > (INTEGER)(O_5 - 1)) {
      FREE_OPEN_ARRAYS
      return FALSE;
    }
    {
      LONGINT B_13 = 0, B_14 = yyLength;

      if (B_13 <= B_14)
        for (yyi = B_13;; yyi += 1) {
          if (yyString.A[yyi] != yya[yyi]) {
            FREE_OPEN_ARRAYS
            return FALSE;
          }
          if (yyi >= B_14) break;
        }
    }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

void Tree_QueryTree
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyState = yyyWrite;
  for (;;) {
    switch (yyState) {
    case yyyQuit:;
      return;
      break;
    case yyyWrite:;
      Tree_WriteTreeNode((System_tFile)IO_StdOutput, yyt);
      yyState = yyyRead;
      break;
    case yyyRead:;
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"? ", 2L);
      yyLength = -1;
      yyCh = IO_ReadC((System_tFile)IO_StdInput);
      while (yyCh != '\n') {
        INC(yyLength);
        yyString.A[yyLength] = yyCh;
        yyCh = IO_ReadC((System_tFile)IO_StdInput);
      }
      if (yyyIsEqual((STRING)"parent", 6L)) {
        yyState = yyyWrite;
        return;
      } else if (yyyIsEqual((STRING)"quit", 4L)) {
        yyState = yyyQuit;
        return;
      } else if (yyt != Tree_NoTree) {
        switch (yyt->U_1.V_1.Kind) {
        case Tree_Class:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Attributes", 10L)) {
            Tree_QueryTree(yyt->U_1.V_5.Class.Attributes);
          } else if (yyyIsEqual((STRING)"Extensions", 10L)) {
            Tree_QueryTree(yyt->U_1.V_5.Class.Extensions);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_5.Class.Next);
          } else if (yyyIsEqual((STRING)"BaseClass", 9L)) {
            Tree_QueryTree(yyt->U_1.V_5.Class.BaseClass);
          } else if (yyyIsEqual((STRING)"Formals", 7L)) {
            Tree_QueryTree(yyt->U_1.V_5.Class.Formals);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_5.Class.TypeDesc);
          }
          break;
        case Tree_AttrOrAction:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_8.AttrOrAction.Next);
          }
          break;
        case Tree_Child:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_9.Child.Next);
          }
          break;
        case Tree_Attribute:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_10.Attribute.Next);
          }
          break;
        case Tree_ActionPart:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_11.ActionPart.Next);
          }
          break;
        case Tree_Designator:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_15.Designator.Next);
          }
          break;
        case Tree_Ident:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_16.Ident.Next);
          }
          break;
        case Tree_Remote:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Designators", 11L)) {
            Tree_QueryTree(yyt->U_1.V_17.Remote.Designators);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_17.Remote.Next);
          }
          break;
        case Tree_Any:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_18.Any.Next);
          }
          break;
        case Tree_Anys:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Layouts", 7L)) {
            Tree_QueryTree(yyt->U_1.V_19.Anys.Layouts);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_19.Anys.Next);
          }
          break;
        case Tree_LayoutAny:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_22.LayoutAny.Next);
          }
          break;
        case Tree_Name:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_25.Name.Next);
          }
          break;
        case Tree_Spec:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TreeNames", 9L)) {
            Tree_QueryTree(yyt->U_1.V_26.Spec.TreeNames);
          } else if (yyyIsEqual((STRING)"Public", 6L)) {
            Tree_QueryTree(yyt->U_1.V_26.Spec.Public);
          } else if (yyyIsEqual((STRING)"Extern", 6L)) {
            Tree_QueryTree(yyt->U_1.V_26.Spec.Extern);
          } else if (yyyIsEqual((STRING)"Codes", 5L)) {
            Tree_QueryTree(yyt->U_1.V_26.Spec.Codes);
          } else if (yyyIsEqual((STRING)"Routines", 8L)) {
            Tree_QueryTree(yyt->U_1.V_26.Spec.Routines);
          }
          break;
        case Tree_TreeName:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_29.TreeName.Next);
          } else if (yyyIsEqual((STRING)"Classes", 7L)) {
            Tree_QueryTree(yyt->U_1.V_29.TreeName.Classes);
          } else if (yyyIsEqual((STRING)"EmptyType", 9L)) {
            Tree_QueryTree(yyt->U_1.V_29.TreeName.EmptyType);
          } else if (yyyIsEqual((STRING)"UniversalClass", 14L)) {
            Tree_QueryTree(yyt->U_1.V_29.TreeName.UniversalClass);
          }
          break;
        case Tree_Routine:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.Next);
          } else if (yyyIsEqual((STRING)"InParams", 8L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.InParams);
          } else if (yyyIsEqual((STRING)"OutParams", 9L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.OutParams);
          } else if (yyyIsEqual((STRING)"Extern", 6L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.Extern);
          } else if (yyyIsEqual((STRING)"Rules", 5L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.Rules);
          } else if (yyyIsEqual((STRING)"InForm", 6L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.InForm);
          } else if (yyyIsEqual((STRING)"OutForm", 7L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.OutForm);
          } else if (yyyIsEqual((STRING)"ParamDecls", 10L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.ParamDecls);
          } else if (yyyIsEqual((STRING)"Decisions", 9L)) {
            Tree_QueryTree(yyt->U_1.V_32.Routine.Decisions);
          }
          break;
        case Tree_Procedure:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.Next);
          } else if (yyyIsEqual((STRING)"InParams", 8L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.InParams);
          } else if (yyyIsEqual((STRING)"OutParams", 9L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.OutParams);
          } else if (yyyIsEqual((STRING)"Extern", 6L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.Extern);
          } else if (yyyIsEqual((STRING)"Rules", 5L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.Rules);
          } else if (yyyIsEqual((STRING)"InForm", 6L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.InForm);
          } else if (yyyIsEqual((STRING)"OutForm", 7L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.OutForm);
          } else if (yyyIsEqual((STRING)"ParamDecls", 10L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.ParamDecls);
          } else if (yyyIsEqual((STRING)"Decisions", 9L)) {
            Tree_QueryTree(yyt->U_1.V_33.Procedure.Decisions);
          }
          break;
        case Tree_Function:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.Next);
          } else if (yyyIsEqual((STRING)"InParams", 8L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.InParams);
          } else if (yyyIsEqual((STRING)"OutParams", 9L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.OutParams);
          } else if (yyyIsEqual((STRING)"Extern", 6L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.Extern);
          } else if (yyyIsEqual((STRING)"Rules", 5L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.Rules);
          } else if (yyyIsEqual((STRING)"InForm", 6L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.InForm);
          } else if (yyyIsEqual((STRING)"OutForm", 7L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.OutForm);
          } else if (yyyIsEqual((STRING)"ParamDecls", 10L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.ParamDecls);
          } else if (yyyIsEqual((STRING)"Decisions", 9L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.Decisions);
          } else if (yyyIsEqual((STRING)"ReturnParams", 12L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.ReturnParams);
          } else if (yyyIsEqual((STRING)"ReturnForm", 10L)) {
            Tree_QueryTree(yyt->U_1.V_34.Function.ReturnForm);
          }
          break;
        case Tree_Predicate:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.Next);
          } else if (yyyIsEqual((STRING)"InParams", 8L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.InParams);
          } else if (yyyIsEqual((STRING)"OutParams", 9L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.OutParams);
          } else if (yyyIsEqual((STRING)"Extern", 6L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.Extern);
          } else if (yyyIsEqual((STRING)"Rules", 5L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.Rules);
          } else if (yyyIsEqual((STRING)"InForm", 6L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.InForm);
          } else if (yyyIsEqual((STRING)"OutForm", 7L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.OutForm);
          } else if (yyyIsEqual((STRING)"ParamDecls", 10L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.ParamDecls);
          } else if (yyyIsEqual((STRING)"Decisions", 9L)) {
            Tree_QueryTree(yyt->U_1.V_35.Predicate.Decisions);
          }
          break;
        case Tree_Param:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Type", 4L)) {
            Tree_QueryTree(yyt->U_1.V_38.Param.Type);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_38.Param.Next);
          }
          break;
        case Tree_Type:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_39.Type.Names);
          }
          break;
        case Tree_Rule:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Patterns", 8L)) {
            Tree_QueryTree(yyt->U_1.V_42.Rule.Patterns);
          } else if (yyyIsEqual((STRING)"Exprs", 5L)) {
            Tree_QueryTree(yyt->U_1.V_42.Rule.Exprs);
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_42.Rule.Expr);
          } else if (yyyIsEqual((STRING)"Statements", 10L)) {
            Tree_QueryTree(yyt->U_1.V_42.Rule.Statements);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_42.Rule.Next);
          } else if (yyyIsEqual((STRING)"VarDecls", 8L)) {
            Tree_QueryTree(yyt->U_1.V_42.Rule.VarDecls);
          } else if (yyyIsEqual((STRING)"Tests", 5L)) {
            Tree_QueryTree(yyt->U_1.V_42.Rule.Tests);
          }
          break;
        case Tree_OnePattern:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Pattern", 7L)) {
            Tree_QueryTree(yyt->U_1.V_45.OnePattern.Pattern);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_45.OnePattern.Next);
          }
          break;
        case Tree_OnePatternAlts:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"PatternsList", 12L)) {
            Tree_QueryTree(yyt->U_1.V_46.OnePatternAlts.PatternsList);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_46.OnePatternAlts.Next);
          } else if (yyyIsEqual((STRING)"Current", 7L)) {
            Tree_QueryTree(yyt->U_1.V_46.OnePatternAlts.Current);
          }
          break;
        case Tree_OnePatternsList:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Patterns", 8L)) {
            Tree_QueryTree(yyt->U_1.V_49.OnePatternsList.Patterns);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_49.OnePatternsList.Next);
          }
          break;
        case Tree_Pattern:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_50.Pattern.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_50.Pattern.Path);
          }
          break;
        case Tree_Decompose:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_51.Decompose.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_51.Decompose.Path);
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_51.Decompose.Expr);
          } else if (yyyIsEqual((STRING)"Patterns", 8L)) {
            Tree_QueryTree(yyt->U_1.V_51.Decompose.Patterns);
          }
          break;
        case Tree_VarDef:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_52.VarDef.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_52.VarDef.Path);
          }
          break;
        case Tree_NilTest:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_53.NilTest.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_53.NilTest.Path);
          }
          break;
        case Tree_DontCare1:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_54.DontCare1.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_54.DontCare1.Path);
          }
          break;
        case Tree_DontCare1Explicit:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_55.DontCare1Explicit.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_55.DontCare1Explicit.Path);
          }
          break;
        case Tree_DontCare1Internal:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_56.DontCare1Internal.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_56.DontCare1Internal.Path);
          }
          break;
        case Tree_DontCare:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_57.DontCare.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_57.DontCare.Path);
          } else if (yyyIsEqual((STRING)"Tempos", 6L)) {
            Tree_QueryTree(yyt->U_1.V_57.DontCare.Tempos);
          }
          break;
        case Tree_DontCareExplicit:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_58.DontCareExplicit.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_58.DontCareExplicit.Path);
          } else if (yyyIsEqual((STRING)"Tempos", 6L)) {
            Tree_QueryTree(yyt->U_1.V_58.DontCareExplicit.Tempos);
          }
          break;
        case Tree_DontCareInternal:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_59.DontCareInternal.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_59.DontCareInternal.Path);
          } else if (yyyIsEqual((STRING)"Tempos", 6L)) {
            Tree_QueryTree(yyt->U_1.V_59.DontCareInternal.Tempos);
          }
          break;
        case Tree_Value:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_60.Value.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_60.Value.Path);
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_60.Value.Expr);
          }
          break;
        case Tree_OneExpr:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_63.OneExpr.Expr);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_63.OneExpr.Next);
          }
          break;
        case Tree_NamedExpr:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_64.NamedExpr.Expr);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_64.NamedExpr.Next);
          }
          break;
        case Tree_Compose:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_66.Compose.Expr);
          } else if (yyyIsEqual((STRING)"Exprs", 5L)) {
            Tree_QueryTree(yyt->U_1.V_66.Compose.Exprs);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_66.Compose.TypeDesc);
          }
          break;
        case Tree_Call:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_70.Call.Expr);
          } else if (yyyIsEqual((STRING)"Exprs", 5L)) {
            Tree_QueryTree(yyt->U_1.V_70.Call.Exprs);
          } else if (yyyIsEqual((STRING)"Patterns", 8L)) {
            Tree_QueryTree(yyt->U_1.V_70.Call.Patterns);
          }
          break;
        case Tree_Binary:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Lop", 3L)) {
            Tree_QueryTree(yyt->U_1.V_71.Binary.Lop);
          } else if (yyyIsEqual((STRING)"Rop", 3L)) {
            Tree_QueryTree(yyt->U_1.V_71.Binary.Rop);
          }
          break;
        case Tree_yy1:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Lop", 3L)) {
            Tree_QueryTree(yyt->U_1.V_72.yy1.Lop);
          } else if (yyyIsEqual((STRING)"Rop", 3L)) {
            Tree_QueryTree(yyt->U_1.V_72.yy1.Rop);
          }
          break;
        case Tree_BinaryCompound:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Lop", 3L)) {
            Tree_QueryTree(yyt->U_1.V_73.BinaryCompound.Lop);
          } else if (yyyIsEqual((STRING)"Rop", 3L)) {
            Tree_QueryTree(yyt->U_1.V_73.BinaryCompound.Rop);
          }
          break;
        case Tree_PreOperator:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_74.PreOperator.Expr);
          }
          break;
        case Tree_PostOperator:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_75.PostOperator.Expr);
          }
          break;
        case Tree_Index:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_76.Index.Expr);
          } else if (yyyIsEqual((STRING)"Exprs", 5L)) {
            Tree_QueryTree(yyt->U_1.V_76.Index.Exprs);
          }
          break;
        case Tree_Parents:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_77.Parents.Expr);
          }
          break;
        case Tree_TargetExpr:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_78.TargetExpr.Expr);
          }
          break;
        case Tree_Statement:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_82.Statement.Next);
          }
          break;
        case Tree_ProcCall:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_83.ProcCall.Next);
          } else if (yyyIsEqual((STRING)"Call", 4L)) {
            Tree_QueryTree(yyt->U_1.V_83.ProcCall.Call);
          }
          break;
        case Tree_Condition:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_84.Condition.Next);
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_84.Condition.Expr);
          }
          break;
        case Tree_Assignment:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_85.Assignment.Next);
          } else if (yyyIsEqual((STRING)"Adr", 3L)) {
            Tree_QueryTree(yyt->U_1.V_85.Assignment.Adr);
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_85.Assignment.Expr);
          }
          break;
        case Tree_Reject:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_86.Reject.Next);
          }
          break;
        case Tree_Fail:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_87.Fail.Next);
          }
          break;
        case Tree_TargetStmt:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_88.TargetStmt.Next);
          } else if (yyyIsEqual((STRING)"Parameters", 10L)) {
            Tree_QueryTree(yyt->U_1.V_88.TargetStmt.Parameters);
          } else if (yyyIsEqual((STRING)"Stmt", 4L)) {
            Tree_QueryTree(yyt->U_1.V_88.TargetStmt.Stmt);
          }
          break;
        case Tree_Nl:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_89.Nl.Next);
          }
          break;
        case Tree_WriteStr:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_90.WriteStr.Next);
          }
          break;
        case Tree_Formal:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_93.Formal.Next);
          } else if (yyyIsEqual((STRING)"Hides", 5L)) {
            Tree_QueryTree(yyt->U_1.V_93.Formal.Hides);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_93.Formal.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_93.Formal.Path);
          }
          break;
        case Tree_PlainFormal:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_94.PlainFormal.Next);
          } else if (yyyIsEqual((STRING)"Hides", 5L)) {
            Tree_QueryTree(yyt->U_1.V_94.PlainFormal.Hides);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_94.PlainFormal.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_94.PlainFormal.Path);
          }
          break;
        case Tree_RoutineFormal:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_95.RoutineFormal.Next);
          } else if (yyyIsEqual((STRING)"Hides", 5L)) {
            Tree_QueryTree(yyt->U_1.V_95.RoutineFormal.Hides);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_95.RoutineFormal.TypeDesc);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_95.RoutineFormal.Path);
          } else if (yyyIsEqual((STRING)"TargetClass", 11L)) {
            Tree_QueryTree(yyt->U_1.V_95.RoutineFormal.TargetClass);
          }
          break;
        case Tree_DummyFormal:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_96.DummyFormal.Next);
          }
          break;
        case Tree_NodeTypes:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"TreeName", 8L)) {
            Tree_QueryTree(yyt->U_1.V_98.NodeTypes.TreeName);
          }
          break;
        case Tree_ConsType:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_102.ConsType.Next);
          }
          break;
        case Tree_Field:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_103.Field.Next);
          }
          break;
        case Tree_OneTest:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_106.OneTest.Next);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_106.OneTest.Path);
          }
          break;
        case Tree_TestKind:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_107.TestKind.Next);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_107.TestKind.Path);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_107.TestKind.TypeDesc);
          }
          break;
        case Tree_TestIsType:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_108.TestIsType.Next);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_108.TestIsType.Path);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_108.TestIsType.TypeDesc);
          }
          break;
        case Tree_TestNil:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_109.TestNil.Next);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_109.TestNil.Path);
          }
          break;
        case Tree_TestNonlin:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_110.TestNonlin.Next);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_110.TestNonlin.Path);
          } else if (yyyIsEqual((STRING)"Path2", 5L)) {
            Tree_QueryTree(yyt->U_1.V_110.TestNonlin.Path2);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_110.TestNonlin.TypeDesc);
          }
          break;
        case Tree_TestValue:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_111.TestValue.Next);
          } else if (yyyIsEqual((STRING)"Path", 4L)) {
            Tree_QueryTree(yyt->U_1.V_111.TestValue.Path);
          } else if (yyyIsEqual((STRING)"Expr", 4L)) {
            Tree_QueryTree(yyt->U_1.V_111.TestValue.Expr);
          } else if (yyyIsEqual((STRING)"TypeDesc", 8L)) {
            Tree_QueryTree(yyt->U_1.V_111.TestValue.TypeDesc);
          }
          break;
        case Tree_Decision:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"ThenPart", 8L)) {
            Tree_QueryTree(yyt->U_1.V_114.Decision.ThenPart);
          } else if (yyyIsEqual((STRING)"ElsePart", 8L)) {
            Tree_QueryTree(yyt->U_1.V_114.Decision.ElsePart);
          } else if (yyyIsEqual((STRING)"OneTest", 7L)) {
            Tree_QueryTree(yyt->U_1.V_114.Decision.OneTest);
          }
          break;
        case Tree_Decided:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"ElsePart", 8L)) {
            Tree_QueryTree(yyt->U_1.V_115.Decided.ElsePart);
          } else if (yyyIsEqual((STRING)"Rule", 4L)) {
            Tree_QueryTree(yyt->U_1.V_115.Decided.Rule);
          }
          break;
        default :
          break;
        }
      }
      break;
    }
  } EXIT_7:;
}

void Tree_BeginTree
# ifdef __STDC__
()
# else
()
# endif
{
  Tree_ErrorCount = 0;
  Sets_MakeSet(&Tree_Options, 127L);
  Tree_NoCodeAttr = SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy) | SET_ELEM(Tree_Virtual) | SET_ELEM(Tree_Parameter);
  Tree_NoCodeClass = SET_ELEM(Tree_Ignore) | SET_ELEM(Tree_Abstract);
}

void Tree_CloseTree
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

void Tree__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    IO__init();
    Strings__init();
    StringMem__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Relations__init();
    Positions__init();
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
    DynArray__init();
    IO__init();
    Strings__init();
    StringMem__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Relations__init();
    Positions__init();
    Relations__init();
    Errors__init();

    yyBlockList = NIL;
    Tree_yyPoolFreePtr = (ADDRESS)NIL;
    Tree_yyPoolMaxPtr = (ADDRESS)NIL;
    Tree_HeapUsed = 0;
    Tree_yyExit = xxExit;
    Tree_yyNodeSize.A[Tree_Classes] = sizeof(Tree_yClasses);
    Tree_yyNodeSize.A[Tree_NoClass] = sizeof(Tree_yNoClass);
    Tree_yyNodeSize.A[Tree_Class] = sizeof(Tree_yClass);
    Tree_yyNodeSize.A[Tree_Attributes] = sizeof(Tree_yAttributes);
    Tree_yyNodeSize.A[Tree_NoAttribute] = sizeof(Tree_yNoAttribute);
    Tree_yyNodeSize.A[Tree_AttrOrAction] = sizeof(Tree_yAttrOrAction);
    Tree_yyNodeSize.A[Tree_Child] = sizeof(Tree_yChild);
    Tree_yyNodeSize.A[Tree_Attribute] = sizeof(Tree_yAttribute);
    Tree_yyNodeSize.A[Tree_ActionPart] = sizeof(Tree_yActionPart);
    Tree_yyNodeSize.A[Tree_Codes] = sizeof(Tree_yCodes);
    Tree_yyNodeSize.A[Tree_Designators] = sizeof(Tree_yDesignators);
    Tree_yyNodeSize.A[Tree_NoDesignator] = sizeof(Tree_yNoDesignator);
    Tree_yyNodeSize.A[Tree_Designator] = sizeof(Tree_yDesignator);
    Tree_yyNodeSize.A[Tree_Ident] = sizeof(Tree_yIdent);
    Tree_yyNodeSize.A[Tree_Remote] = sizeof(Tree_yRemote);
    Tree_yyNodeSize.A[Tree_Any] = sizeof(Tree_yAny);
    Tree_yyNodeSize.A[Tree_Anys] = sizeof(Tree_yAnys);
    Tree_yyNodeSize.A[Tree_Layouts] = sizeof(Tree_yLayouts);
    Tree_yyNodeSize.A[Tree_NoLayout] = sizeof(Tree_yNoLayout);
    Tree_yyNodeSize.A[Tree_LayoutAny] = sizeof(Tree_yLayoutAny);
    Tree_yyNodeSize.A[Tree_Names] = sizeof(Tree_yNames);
    Tree_yyNodeSize.A[Tree_NoName] = sizeof(Tree_yNoName);
    Tree_yyNodeSize.A[Tree_Name] = sizeof(Tree_yName);
    Tree_yyNodeSize.A[Tree_Spec] = sizeof(Tree_ySpec);
    Tree_yyNodeSize.A[Tree_TreeNames] = sizeof(Tree_yTreeNames);
    Tree_yyNodeSize.A[Tree_NoTreeName] = sizeof(Tree_yNoTreeName);
    Tree_yyNodeSize.A[Tree_TreeName] = sizeof(Tree_yTreeName);
    Tree_yyNodeSize.A[Tree_Routines] = sizeof(Tree_yRoutines);
    Tree_yyNodeSize.A[Tree_NoRoutine] = sizeof(Tree_yNoRoutine);
    Tree_yyNodeSize.A[Tree_Routine] = sizeof(Tree_yRoutine);
    Tree_yyNodeSize.A[Tree_Procedure] = sizeof(Tree_yProcedure);
    Tree_yyNodeSize.A[Tree_Function] = sizeof(Tree_yFunction);
    Tree_yyNodeSize.A[Tree_Predicate] = sizeof(Tree_yPredicate);
    Tree_yyNodeSize.A[Tree_Parameters] = sizeof(Tree_yParameters);
    Tree_yyNodeSize.A[Tree_NoParameter] = sizeof(Tree_yNoParameter);
    Tree_yyNodeSize.A[Tree_Param] = sizeof(Tree_yParam);
    Tree_yyNodeSize.A[Tree_Type] = sizeof(Tree_yType);
    Tree_yyNodeSize.A[Tree_Rules] = sizeof(Tree_yRules);
    Tree_yyNodeSize.A[Tree_NoRule] = sizeof(Tree_yNoRule);
    Tree_yyNodeSize.A[Tree_Rule] = sizeof(Tree_yRule);
    Tree_yyNodeSize.A[Tree_Patterns] = sizeof(Tree_yPatterns);
    Tree_yyNodeSize.A[Tree_NoPattern] = sizeof(Tree_yNoPattern);
    Tree_yyNodeSize.A[Tree_OnePattern] = sizeof(Tree_yOnePattern);
    Tree_yyNodeSize.A[Tree_OnePatternAlts] = sizeof(Tree_yOnePatternAlts);
    Tree_yyNodeSize.A[Tree_PatternsList] = sizeof(Tree_yPatternsList);
    Tree_yyNodeSize.A[Tree_NoPatternsList] = sizeof(Tree_yNoPatternsList);
    Tree_yyNodeSize.A[Tree_OnePatternsList] = sizeof(Tree_yOnePatternsList);
    Tree_yyNodeSize.A[Tree_Pattern] = sizeof(Tree_yPattern);
    Tree_yyNodeSize.A[Tree_Decompose] = sizeof(Tree_yDecompose);
    Tree_yyNodeSize.A[Tree_VarDef] = sizeof(Tree_yVarDef);
    Tree_yyNodeSize.A[Tree_NilTest] = sizeof(Tree_yNilTest);
    Tree_yyNodeSize.A[Tree_DontCare1] = sizeof(Tree_yDontCare1);
    Tree_yyNodeSize.A[Tree_DontCare1Explicit] = sizeof(Tree_yDontCare1Explicit);
    Tree_yyNodeSize.A[Tree_DontCare1Internal] = sizeof(Tree_yDontCare1Internal);
    Tree_yyNodeSize.A[Tree_DontCare] = sizeof(Tree_yDontCare);
    Tree_yyNodeSize.A[Tree_DontCareExplicit] = sizeof(Tree_yDontCareExplicit);
    Tree_yyNodeSize.A[Tree_DontCareInternal] = sizeof(Tree_yDontCareInternal);
    Tree_yyNodeSize.A[Tree_Value] = sizeof(Tree_yValue);
    Tree_yyNodeSize.A[Tree_Exprs] = sizeof(Tree_yExprs);
    Tree_yyNodeSize.A[Tree_NoExpr] = sizeof(Tree_yNoExpr);
    Tree_yyNodeSize.A[Tree_OneExpr] = sizeof(Tree_yOneExpr);
    Tree_yyNodeSize.A[Tree_NamedExpr] = sizeof(Tree_yNamedExpr);
    Tree_yyNodeSize.A[Tree_Expr] = sizeof(Tree_yExpr);
    Tree_yyNodeSize.A[Tree_Compose] = sizeof(Tree_yCompose);
    Tree_yyNodeSize.A[Tree_VarUse] = sizeof(Tree_yVarUse);
    Tree_yyNodeSize.A[Tree_AttrDesc] = sizeof(Tree_yAttrDesc);
    Tree_yyNodeSize.A[Tree_Nil] = sizeof(Tree_yNil);
    Tree_yyNodeSize.A[Tree_Call] = sizeof(Tree_yCall);
    Tree_yyNodeSize.A[Tree_Binary] = sizeof(Tree_yBinary);
    Tree_yyNodeSize.A[Tree_yy1] = sizeof(Tree_yyy1);
    Tree_yyNodeSize.A[Tree_BinaryCompound] = sizeof(Tree_yBinaryCompound);
    Tree_yyNodeSize.A[Tree_PreOperator] = sizeof(Tree_yPreOperator);
    Tree_yyNodeSize.A[Tree_PostOperator] = sizeof(Tree_yPostOperator);
    Tree_yyNodeSize.A[Tree_Index] = sizeof(Tree_yIndex);
    Tree_yyNodeSize.A[Tree_Parents] = sizeof(Tree_yParents);
    Tree_yyNodeSize.A[Tree_TargetExpr] = sizeof(Tree_yTargetExpr);
    Tree_yyNodeSize.A[Tree_StringExpr] = sizeof(Tree_yStringExpr);
    Tree_yyNodeSize.A[Tree_Statements] = sizeof(Tree_yStatements);
    Tree_yyNodeSize.A[Tree_NoStatement] = sizeof(Tree_yNoStatement);
    Tree_yyNodeSize.A[Tree_Statement] = sizeof(Tree_yStatement);
    Tree_yyNodeSize.A[Tree_ProcCall] = sizeof(Tree_yProcCall);
    Tree_yyNodeSize.A[Tree_Condition] = sizeof(Tree_yCondition);
    Tree_yyNodeSize.A[Tree_Assignment] = sizeof(Tree_yAssignment);
    Tree_yyNodeSize.A[Tree_Reject] = sizeof(Tree_yReject);
    Tree_yyNodeSize.A[Tree_Fail] = sizeof(Tree_yFail);
    Tree_yyNodeSize.A[Tree_TargetStmt] = sizeof(Tree_yTargetStmt);
    Tree_yyNodeSize.A[Tree_Nl] = sizeof(Tree_yNl);
    Tree_yyNodeSize.A[Tree_WriteStr] = sizeof(Tree_yWriteStr);
    Tree_yyNodeSize.A[Tree_Formals] = sizeof(Tree_yFormals);
    Tree_yyNodeSize.A[Tree_NoFormal] = sizeof(Tree_yNoFormal);
    Tree_yyNodeSize.A[Tree_Formal] = sizeof(Tree_yFormal);
    Tree_yyNodeSize.A[Tree_PlainFormal] = sizeof(Tree_yPlainFormal);
    Tree_yyNodeSize.A[Tree_RoutineFormal] = sizeof(Tree_yRoutineFormal);
    Tree_yyNodeSize.A[Tree_DummyFormal] = sizeof(Tree_yDummyFormal);
    Tree_yyNodeSize.A[Tree_TypeDesc] = sizeof(Tree_yTypeDesc);
    Tree_yyNodeSize.A[Tree_NodeTypes] = sizeof(Tree_yNodeTypes);
    Tree_yyNodeSize.A[Tree_UserType] = sizeof(Tree_yUserType);
    Tree_yyNodeSize.A[Tree_Path] = sizeof(Tree_yPath);
    Tree_yyNodeSize.A[Tree_Var] = sizeof(Tree_yVar);
    Tree_yyNodeSize.A[Tree_ConsType] = sizeof(Tree_yConsType);
    Tree_yyNodeSize.A[Tree_Field] = sizeof(Tree_yField);
    Tree_yyNodeSize.A[Tree_Tests] = sizeof(Tree_yTests);
    Tree_yyNodeSize.A[Tree_NoTest] = sizeof(Tree_yNoTest);
    Tree_yyNodeSize.A[Tree_OneTest] = sizeof(Tree_yOneTest);
    Tree_yyNodeSize.A[Tree_TestKind] = sizeof(Tree_yTestKind);
    Tree_yyNodeSize.A[Tree_TestIsType] = sizeof(Tree_yTestIsType);
    Tree_yyNodeSize.A[Tree_TestNil] = sizeof(Tree_yTestNil);
    Tree_yyNodeSize.A[Tree_TestNonlin] = sizeof(Tree_yTestNonlin);
    Tree_yyNodeSize.A[Tree_TestValue] = sizeof(Tree_yTestValue);
    Tree_yyNodeSize.A[Tree_Decisions] = sizeof(Tree_yDecisions);
    Tree_yyNodeSize.A[Tree_NoDecision] = sizeof(Tree_yNoDecision);
    Tree_yyNodeSize.A[Tree_Decision] = sizeof(Tree_yDecision);
    Tree_yyNodeSize.A[Tree_Decided] = sizeof(Tree_yDecided);
    yyMaxSize = 0;
    for (yyi = 1; yyi <= 138; yyi += 1) {
      Tree_yyNodeSize.A[yyi] = (LONGINT)((BITSET)(Tree_yyNodeSize.A[yyi] + (CARDINAL)General_MaxAlign - 1) & General_AlignMasks.A[General_MaxAlign]);
      yyMaxSize = General_Max((LONGINT)Tree_yyNodeSize.A[yyi], (LONGINT)yyMaxSize);
    }
    yyTypeRange.A[Tree_Classes] = Tree_Class;
    yyTypeRange.A[Tree_NoClass] = Tree_NoClass;
    yyTypeRange.A[Tree_Class] = Tree_Class;
    yyTypeRange.A[Tree_Attributes] = Tree_ActionPart;
    yyTypeRange.A[Tree_NoAttribute] = Tree_NoAttribute;
    yyTypeRange.A[Tree_AttrOrAction] = Tree_ActionPart;
    yyTypeRange.A[Tree_Child] = Tree_Child;
    yyTypeRange.A[Tree_Attribute] = Tree_Attribute;
    yyTypeRange.A[Tree_ActionPart] = Tree_ActionPart;
    yyTypeRange.A[Tree_Codes] = Tree_Codes;
    yyTypeRange.A[Tree_Designators] = Tree_Anys;
    yyTypeRange.A[Tree_NoDesignator] = Tree_NoDesignator;
    yyTypeRange.A[Tree_Designator] = Tree_Designator;
    yyTypeRange.A[Tree_Ident] = Tree_Ident;
    yyTypeRange.A[Tree_Remote] = Tree_Remote;
    yyTypeRange.A[Tree_Any] = Tree_Any;
    yyTypeRange.A[Tree_Anys] = Tree_Anys;
    yyTypeRange.A[Tree_Layouts] = Tree_LayoutAny;
    yyTypeRange.A[Tree_NoLayout] = Tree_NoLayout;
    yyTypeRange.A[Tree_LayoutAny] = Tree_LayoutAny;
    yyTypeRange.A[Tree_Names] = Tree_Name;
    yyTypeRange.A[Tree_NoName] = Tree_NoName;
    yyTypeRange.A[Tree_Name] = Tree_Name;
    yyTypeRange.A[Tree_Spec] = Tree_Spec;
    yyTypeRange.A[Tree_TreeNames] = Tree_TreeName;
    yyTypeRange.A[Tree_NoTreeName] = Tree_NoTreeName;
    yyTypeRange.A[Tree_TreeName] = Tree_TreeName;
    yyTypeRange.A[Tree_Routines] = Tree_Predicate;
    yyTypeRange.A[Tree_NoRoutine] = Tree_NoRoutine;
    yyTypeRange.A[Tree_Routine] = Tree_Predicate;
    yyTypeRange.A[Tree_Procedure] = Tree_Procedure;
    yyTypeRange.A[Tree_Function] = Tree_Function;
    yyTypeRange.A[Tree_Predicate] = Tree_Predicate;
    yyTypeRange.A[Tree_Parameters] = Tree_Param;
    yyTypeRange.A[Tree_NoParameter] = Tree_NoParameter;
    yyTypeRange.A[Tree_Param] = Tree_Param;
    yyTypeRange.A[Tree_Type] = Tree_Type;
    yyTypeRange.A[Tree_Rules] = Tree_Rule;
    yyTypeRange.A[Tree_NoRule] = Tree_NoRule;
    yyTypeRange.A[Tree_Rule] = Tree_Rule;
    yyTypeRange.A[Tree_Patterns] = Tree_OnePatternAlts;
    yyTypeRange.A[Tree_NoPattern] = Tree_NoPattern;
    yyTypeRange.A[Tree_OnePattern] = Tree_OnePattern;
    yyTypeRange.A[Tree_OnePatternAlts] = Tree_OnePatternAlts;
    yyTypeRange.A[Tree_PatternsList] = Tree_OnePatternsList;
    yyTypeRange.A[Tree_NoPatternsList] = Tree_NoPatternsList;
    yyTypeRange.A[Tree_OnePatternsList] = Tree_OnePatternsList;
    yyTypeRange.A[Tree_Pattern] = Tree_Value;
    yyTypeRange.A[Tree_Decompose] = Tree_Decompose;
    yyTypeRange.A[Tree_VarDef] = Tree_VarDef;
    yyTypeRange.A[Tree_NilTest] = Tree_NilTest;
    yyTypeRange.A[Tree_DontCare1] = Tree_DontCare1Internal;
    yyTypeRange.A[Tree_DontCare1Explicit] = Tree_DontCare1Explicit;
    yyTypeRange.A[Tree_DontCare1Internal] = Tree_DontCare1Internal;
    yyTypeRange.A[Tree_DontCare] = Tree_DontCareInternal;
    yyTypeRange.A[Tree_DontCareExplicit] = Tree_DontCareExplicit;
    yyTypeRange.A[Tree_DontCareInternal] = Tree_DontCareInternal;
    yyTypeRange.A[Tree_Value] = Tree_Value;
    yyTypeRange.A[Tree_Exprs] = Tree_NamedExpr;
    yyTypeRange.A[Tree_NoExpr] = Tree_NoExpr;
    yyTypeRange.A[Tree_OneExpr] = Tree_NamedExpr;
    yyTypeRange.A[Tree_NamedExpr] = Tree_NamedExpr;
    yyTypeRange.A[Tree_Expr] = Tree_StringExpr;
    yyTypeRange.A[Tree_Compose] = Tree_Compose;
    yyTypeRange.A[Tree_VarUse] = Tree_AttrDesc;
    yyTypeRange.A[Tree_AttrDesc] = Tree_AttrDesc;
    yyTypeRange.A[Tree_Nil] = Tree_Nil;
    yyTypeRange.A[Tree_Call] = Tree_Call;
    yyTypeRange.A[Tree_Binary] = Tree_BinaryCompound;
    yyTypeRange.A[Tree_yy1] = Tree_yy1;
    yyTypeRange.A[Tree_BinaryCompound] = Tree_BinaryCompound;
    yyTypeRange.A[Tree_PreOperator] = Tree_PreOperator;
    yyTypeRange.A[Tree_PostOperator] = Tree_PostOperator;
    yyTypeRange.A[Tree_Index] = Tree_Index;
    yyTypeRange.A[Tree_Parents] = Tree_Parents;
    yyTypeRange.A[Tree_TargetExpr] = Tree_TargetExpr;
    yyTypeRange.A[Tree_StringExpr] = Tree_StringExpr;
    yyTypeRange.A[Tree_Statements] = Tree_WriteStr;
    yyTypeRange.A[Tree_NoStatement] = Tree_NoStatement;
    yyTypeRange.A[Tree_Statement] = Tree_WriteStr;
    yyTypeRange.A[Tree_ProcCall] = Tree_ProcCall;
    yyTypeRange.A[Tree_Condition] = Tree_Condition;
    yyTypeRange.A[Tree_Assignment] = Tree_Assignment;
    yyTypeRange.A[Tree_Reject] = Tree_Reject;
    yyTypeRange.A[Tree_Fail] = Tree_Fail;
    yyTypeRange.A[Tree_TargetStmt] = Tree_TargetStmt;
    yyTypeRange.A[Tree_Nl] = Tree_Nl;
    yyTypeRange.A[Tree_WriteStr] = Tree_WriteStr;
    yyTypeRange.A[Tree_Formals] = Tree_DummyFormal;
    yyTypeRange.A[Tree_NoFormal] = Tree_NoFormal;
    yyTypeRange.A[Tree_Formal] = Tree_RoutineFormal;
    yyTypeRange.A[Tree_PlainFormal] = Tree_PlainFormal;
    yyTypeRange.A[Tree_RoutineFormal] = Tree_RoutineFormal;
    yyTypeRange.A[Tree_DummyFormal] = Tree_DummyFormal;
    yyTypeRange.A[Tree_TypeDesc] = Tree_UserType;
    yyTypeRange.A[Tree_NodeTypes] = Tree_NodeTypes;
    yyTypeRange.A[Tree_UserType] = Tree_UserType;
    yyTypeRange.A[Tree_Path] = Tree_Field;
    yyTypeRange.A[Tree_Var] = Tree_Var;
    yyTypeRange.A[Tree_ConsType] = Tree_ConsType;
    yyTypeRange.A[Tree_Field] = Tree_Field;
    yyTypeRange.A[Tree_Tests] = Tree_TestValue;
    yyTypeRange.A[Tree_NoTest] = Tree_NoTest;
    yyTypeRange.A[Tree_OneTest] = Tree_TestValue;
    yyTypeRange.A[Tree_TestKind] = Tree_TestKind;
    yyTypeRange.A[Tree_TestIsType] = Tree_TestIsType;
    yyTypeRange.A[Tree_TestNil] = Tree_TestNil;
    yyTypeRange.A[Tree_TestNonlin] = Tree_TestNonlin;
    yyTypeRange.A[Tree_TestValue] = Tree_TestValue;
    yyTypeRange.A[Tree_Decisions] = Tree_Decided;
    yyTypeRange.A[Tree_NoDecision] = Tree_NoDecision;
    yyTypeRange.A[Tree_Decision] = Tree_Decision;
    yyTypeRange.A[Tree_Decided] = Tree_Decided;
    yyRecursionLevel = 0;
    yyTreeStoreSize = yyInitTreeStoreSize;
    DynArray_MakeArray((ADDRESS *)&yyTreeStorePtr, &yyTreeStoreSize, (LONGINT)sizeof(Tree_tTree));
    yyOldToNewStoreSize = yyInitOldToNewStoreSize;
    DynArray_MakeArray((ADDRESS *)&yyOldToNewStorePtr, &yyOldToNewStoreSize, (LONGINT)sizeof(yytOldToNew));
    Tree_BeginTree();
  }
}
