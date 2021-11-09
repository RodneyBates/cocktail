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

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

Tree_tTree Tree_TreeRoot;
LONGCARD Tree_HeapUsed;
ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
struct Tree_55 Tree_yyNodeSize;
PROC Tree_yyExit;

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
    SHORTCARD A[52 + 1];
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
static struct S_4 {
    Tree_tTree A[50000 + 1];
} *yyTreeStorePtr;
static INTEGER yyLabelCount;
static SHORTINT yyRecursionLevel;
static SHORTCARD yyMapToLabel ARGS((Tree_tTree yyTree));
static Tree_tTree yyMapToTree ARGS((SHORTCARD yyLabel));
static void yyWriteNl ARGS(());
static void yyWriteSelector ARGS((CHAR yys[], LONGCARD ));
static void yyWriteHex ARGS((BYTE yyx[], LONGCARD ));
static SHORTINT yyIndentLevel;
static SHORTINT yyActualIndent, yyIndentQuotient, yyIndentRemainder;
#define yyIndentFactor   20
static void yySetIndentInfo ARGS(());
static void yyIndentSelector ARGS((CHAR yys[], LONGCARD ));
static void yyIndentSelectorTree ARGS((CHAR yys[], LONGCARD , Tree_tTree yyt));
static void yWriteSpec ARGS((Tree_tTree yyt));
static void yWriteClass ARGS((Tree_tTree yyt));
static void yWriteNode ARGS((Tree_tTree yyt));
static void yWriteSon ARGS((Tree_tTree yyt));
static void yWriteAttribute ARGS((Tree_tTree yyt));
static void yWriteFunction ARGS((Tree_tTree yyt));
static void yWriteType ARGS((Tree_tTree yyt));
static void yWriteIdent ARGS((Tree_tTree yyt));
static void yWriteDirective ARGS((Tree_tTree yyt));
static void yWritepattern ARGS((Tree_tTree yyt));
static void yWritePattern1 ARGS((Tree_tTree yyt));
static void yWritePattern ARGS((Tree_tTree yyt));
static void yWritePatterns ARGS((Tree_tTree yyt));
static void yWriteCondF ARGS((Tree_tTree yyt));
static void yWriteCostN ARGS((Tree_tTree yyt));
static void yWriteCostF ARGS((Tree_tTree yyt));
static void yWritecode ARGS((Tree_tTree yyt));
static void yWriteCdStr ARGS((Tree_tTree yyt));
static void yWriteCdId ARGS((Tree_tTree yyt));
static void yWriteCdDot ARGS((Tree_tTree yyt));
static void yWriteCdComma ARGS((Tree_tTree yyt));
static void yWriteCdLPar ARGS((Tree_tTree yyt));
static void yWriteCdRPar ARGS((Tree_tTree yyt));
static void yWriteCdLBra ARGS((Tree_tTree yyt));
static void yWriteCdRBra ARGS((Tree_tTree yyt));
static void yWriteCdSpa ARGS((Tree_tTree yyt));
static void yWriteCdCom ARGS((Tree_tTree yyt));
static void yWriteCdRst ARGS((Tree_tTree yyt));
static void yWriteCdEnd ARGS((Tree_tTree yyt));
static void yyWriteTree ARGS((Tree_tTree yyt));
#define yyNil   ((CHAR)'\374')
#define yyNoLabel   ((CHAR)'\375')
#define yyLabelDef   ((CHAR)'\376')
#define yyLabelUse   ((CHAR)'\377')
static void xxExit ARGS(());


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

Tree_tTree Tree_mspec
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_spec]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_spec;
  return yyt;
}

Tree_tTree Tree_mSpec
# ifdef __STDC__
(Idents_tIdent pname, Positions_tPosition ppos, Idents_tIdent pgrna, Positions_tPosition pgrpos, Tree_tTree pexport, Tree_tTree pglobal, Tree_tTree pbegin, Tree_tTree pclose, Tree_tTree pclasses, Tree_tTree pfunctions)
# else
(pname, ppos, pgrna, pgrpos, pexport, pglobal, pbegin, pclose, pclasses, pfunctions)
Idents_tIdent pname;
Positions_tPosition ppos;
Idents_tIdent pgrna;
Positions_tPosition pgrpos;
Tree_tTree pexport;
Tree_tTree pglobal;
Tree_tTree pbegin;
Tree_tTree pclose;
Tree_tTree pclasses;
Tree_tTree pfunctions;
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
    register Tree_ySpec *W_1 = &yyt->U_1.V_4.Spec;

    W_1->name = pname;
    W_1->pos = ppos;
    W_1->grna = pgrna;
    W_1->grpos = pgrpos;
    W_1->export = pexport;
    W_1->global = pglobal;
    W_1->begin = pbegin;
    W_1->close = pclose;
    W_1->classes = pclasses;
    W_1->functions = pfunctions;
  }
  return yyt;
}

Tree_tTree Tree_mclasses
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_classes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_classes;
  return yyt;
}

Tree_tTree Tree_mClass0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Class0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Class0;
  return yyt;
}

Tree_tTree Tree_mClass
# ifdef __STDC__
(Idents_tIdent psuid, Positions_tPosition psupos, Idents_tIdent pclid, Positions_tPosition pclpos, Tree_tTree pnodes, Tree_tTree pclasses, BOOLEAN pcorrect)
# else
(psuid, psupos, pclid, pclpos, pnodes, pclasses, pcorrect)
Idents_tIdent psuid;
Positions_tPosition psupos;
Idents_tIdent pclid;
Positions_tPosition pclpos;
Tree_tTree pnodes;
Tree_tTree pclasses;
BOOLEAN pcorrect;
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
    register Tree_yClass *W_2 = &yyt->U_1.V_7.Class;

    W_2->suid = psuid;
    W_2->supos = psupos;
    W_2->clid = pclid;
    W_2->clpos = pclpos;
    W_2->nodes = pnodes;
    W_2->classes = pclasses;
    W_2->correct = pcorrect;
  }
  return yyt;
}

Tree_tTree Tree_mnodes
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_nodes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_nodes;
  return yyt;
}

Tree_tTree Tree_mNode0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Node0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Node0;
  return yyt;
}

Tree_tTree Tree_mNode
# ifdef __STDC__
(Idents_tIdent pname, Positions_tPosition pnapos, Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree psons, Tree_tTree pnodes, BOOLEAN pcorrect)
# else
(pname, pnapos, pident, pidpos, psons, pnodes, pcorrect)
Idents_tIdent pname;
Positions_tPosition pnapos;
Idents_tIdent pident;
Positions_tPosition pidpos;
Tree_tTree psons;
Tree_tTree pnodes;
BOOLEAN pcorrect;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Node]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Node;
  {
    register Tree_yNode *W_3 = &yyt->U_1.V_10.Node;

    W_3->name = pname;
    W_3->napos = pnapos;
    W_3->ident = pident;
    W_3->idpos = pidpos;
    W_3->sons = psons;
    W_3->nodes = pnodes;
    W_3->correct = pcorrect;
  }
  return yyt;
}

Tree_tTree Tree_msons
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_sons]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_sons;
  return yyt;
}

Tree_tTree Tree_mSon0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Son0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Son0;
  return yyt;
}

Tree_tTree Tree_mSon
# ifdef __STDC__
(Idents_tIdent pname, Positions_tPosition pnapos, Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree psons, BOOLEAN pcorrect)
# else
(pname, pnapos, pident, pidpos, psons, pcorrect)
Idents_tIdent pname;
Positions_tPosition pnapos;
Idents_tIdent pident;
Positions_tPosition pidpos;
Tree_tTree psons;
BOOLEAN pcorrect;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Son]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Son;
  {
    register Tree_ySon *W_4 = &yyt->U_1.V_13.Son;

    W_4->name = pname;
    W_4->napos = pnapos;
    W_4->ident = pident;
    W_4->idpos = pidpos;
    W_4->sons = psons;
    W_4->correct = pcorrect;
  }
  return yyt;
}

Tree_tTree Tree_mattributes
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_attributes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_attributes;
  return yyt;
}

Tree_tTree Tree_mAttribute0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Attribute0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Attribute0;
  return yyt;
}

Tree_tTree Tree_mAttribute
# ifdef __STDC__
(Idents_tIdent pident, Positions_tPosition pidpos, Idents_tIdent pmod, Positions_tPosition pmopos, Idents_tIdent ptype, Positions_tPosition ptypos, Tree_tTree pattributes)
# else
(pident, pidpos, pmod, pmopos, ptype, ptypos, pattributes)
Idents_tIdent pident;
Positions_tPosition pidpos;
Idents_tIdent pmod;
Positions_tPosition pmopos;
Idents_tIdent ptype;
Positions_tPosition ptypos;
Tree_tTree pattributes;
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
    register Tree_yAttribute *W_5 = &yyt->U_1.V_16.Attribute;

    W_5->ident = pident;
    W_5->idpos = pidpos;
    W_5->mod = pmod;
    W_5->mopos = pmopos;
    W_5->type = ptype;
    W_5->typos = ptypos;
    W_5->attributes = pattributes;
  }
  return yyt;
}

Tree_tTree Tree_mfunctions
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_functions]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_functions;
  return yyt;
}

Tree_tTree Tree_mFunction0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Function0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Function0;
  return yyt;
}

Tree_tTree Tree_mFunction
# ifdef __STDC__
(Idents_tIdent pname, Positions_tPosition pnapos, Tree_tTree pin, Tree_tTree pout, Tree_tTree presult, Tree_tTree pdomain, Tree_tTree pdirectives, Tree_tTree pfunctions)
# else
(pname, pnapos, pin, pout, presult, pdomain, pdirectives, pfunctions)
Idents_tIdent pname;
Positions_tPosition pnapos;
Tree_tTree pin;
Tree_tTree pout;
Tree_tTree presult;
Tree_tTree pdomain;
Tree_tTree pdirectives;
Tree_tTree pfunctions;
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
    register Tree_yFunction *W_6 = &yyt->U_1.V_19.Function;

    W_6->name = pname;
    W_6->napos = pnapos;
    W_6->in = pin;
    W_6->out = pout;
    W_6->result = presult;
    W_6->domain = pdomain;
    W_6->directives = pdirectives;
    W_6->functions = pfunctions;
  }
  return yyt;
}

Tree_tTree Tree_mresult
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_result]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_result;
  return yyt;
}

Tree_tTree Tree_mNoResult
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoResult]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoResult;
  return yyt;
}

Tree_tTree Tree_mType
# ifdef __STDC__
(Idents_tIdent pmod, Positions_tPosition pmopos, Idents_tIdent ptype, Positions_tPosition ptypos)
# else
(pmod, pmopos, ptype, ptypos)
Idents_tIdent pmod;
Positions_tPosition pmopos;
Idents_tIdent ptype;
Positions_tPosition ptypos;
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
    register Tree_yType *W_7 = &yyt->U_1.V_22.Type;

    W_7->mod = pmod;
    W_7->mopos = pmopos;
    W_7->type = ptype;
    W_7->typos = ptypos;
  }
  return yyt;
}

Tree_tTree Tree_mdomain
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_domain]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_domain;
  return yyt;
}

Tree_tTree Tree_mIdent0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Ident0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Ident0;
  return yyt;
}

Tree_tTree Tree_mIdent
# ifdef __STDC__
(Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree pdomain)
# else
(pident, pidpos, pdomain)
Idents_tIdent pident;
Positions_tPosition pidpos;
Tree_tTree pdomain;
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
    register Tree_yIdent *W_8 = &yyt->U_1.V_25.Ident;

    W_8->ident = pident;
    W_8->idpos = pidpos;
    W_8->domain = pdomain;
  }
  return yyt;
}

Tree_tTree Tree_mdirectives
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_directives]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_directives;
  return yyt;
}

Tree_tTree Tree_mDirective0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Directive0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Directive0;
  return yyt;
}

Tree_tTree Tree_mDirective
# ifdef __STDC__
(Tree_tTree ppattern, Tree_tTree pcondition, Tree_tTree pcosts, Tree_tTree pdecl, Tree_tTree pinstr, Tree_tTree pdirectives, BOOLEAN pcorrect)
# else
(ppattern, pcondition, pcosts, pdecl, pinstr, pdirectives, pcorrect)
Tree_tTree ppattern;
Tree_tTree pcondition;
Tree_tTree pcosts;
Tree_tTree pdecl;
Tree_tTree pinstr;
Tree_tTree pdirectives;
BOOLEAN pcorrect;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Directive]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Directive;
  {
    register Tree_yDirective *W_9 = &yyt->U_1.V_28.Directive;

    W_9->pattern = ppattern;
    W_9->condition = pcondition;
    W_9->costs = pcosts;
    W_9->decl = pdecl;
    W_9->instr = pinstr;
    W_9->directives = pdirectives;
    W_9->correct = pcorrect;
  }
  return yyt;
}

Tree_tTree Tree_mpattern
# ifdef __STDC__
(Positions_tPosition ppos)
# else
(ppos)
Positions_tPosition ppos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_pattern]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_pattern;
  {
    register Tree_ypattern *W_10 = &yyt->U_1.V_29.pattern;

    W_10->pos = ppos;
  }
  return yyt;
}

Tree_tTree Tree_mPattern1
# ifdef __STDC__
(Positions_tPosition ppos, Idents_tIdent psel, Positions_tPosition psepos, Idents_tIdent pident, Positions_tPosition pidpos, BOOLEAN pcorrect)
# else
(ppos, psel, psepos, pident, pidpos, pcorrect)
Positions_tPosition ppos;
Idents_tIdent psel;
Positions_tPosition psepos;
Idents_tIdent pident;
Positions_tPosition pidpos;
BOOLEAN pcorrect;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Pattern1]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Pattern1;
  {
    register Tree_yPattern1 *W_11 = &yyt->U_1.V_30.Pattern1;

    W_11->pos = ppos;
    W_11->sel = psel;
    W_11->sepos = psepos;
    W_11->ident = pident;
    W_11->idpos = pidpos;
    W_11->correct = pcorrect;
  }
  return yyt;
}

Tree_tTree Tree_mPattern
# ifdef __STDC__
(Positions_tPosition ppos, Idents_tIdent psel, Positions_tPosition psepos, Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree ppatterns, BOOLEAN pcorrect)
# else
(ppos, psel, psepos, pident, pidpos, ppatterns, pcorrect)
Positions_tPosition ppos;
Idents_tIdent psel;
Positions_tPosition psepos;
Idents_tIdent pident;
Positions_tPosition pidpos;
Tree_tTree ppatterns;
BOOLEAN pcorrect;
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
    register Tree_yPattern *W_12 = &yyt->U_1.V_31.Pattern;

    W_12->pos = ppos;
    W_12->sel = psel;
    W_12->sepos = psepos;
    W_12->ident = pident;
    W_12->idpos = pidpos;
    W_12->patterns = ppatterns;
    W_12->correct = pcorrect;
  }
  return yyt;
}

Tree_tTree Tree_mpatterns
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_patterns]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_patterns;
  return yyt;
}

Tree_tTree Tree_mPatterns0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Patterns0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Patterns0;
  return yyt;
}

Tree_tTree Tree_mPatterns
# ifdef __STDC__
(Tree_tTree ppattern, Tree_tTree ppatterns)
# else
(ppattern, ppatterns)
Tree_tTree ppattern;
Tree_tTree ppatterns;
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
  {
    register Tree_yPatterns *W_13 = &yyt->U_1.V_34.Patterns;

    W_13->pattern = ppattern;
    W_13->patterns = ppatterns;
  }
  return yyt;
}

Tree_tTree Tree_mcondition
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_condition]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_condition;
  return yyt;
}

Tree_tTree Tree_mCondD
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CondD]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CondD;
  return yyt;
}

Tree_tTree Tree_mCondF
# ifdef __STDC__
(Tree_tTree pcode)
# else
(pcode)
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CondF]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CondF;
  {
    register Tree_yCondF *W_14 = &yyt->U_1.V_37.CondF;

    W_14->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mcosts
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_costs]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_costs;
  return yyt;
}

Tree_tTree Tree_mCostD
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CostD]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CostD;
  return yyt;
}

Tree_tTree Tree_mCostN
# ifdef __STDC__
(INTEGER pvalue, Positions_tPosition pvapos)
# else
(pvalue, pvapos)
INTEGER pvalue;
Positions_tPosition pvapos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CostN]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CostN;
  {
    register Tree_yCostN *W_15 = &yyt->U_1.V_40.CostN;

    W_15->value = pvalue;
    W_15->vapos = pvapos;
  }
  return yyt;
}

Tree_tTree Tree_mCostF
# ifdef __STDC__
(Tree_tTree pcode)
# else
(pcode)
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CostF]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CostF;
  {
    register Tree_yCostF *W_16 = &yyt->U_1.V_41.CostF;

    W_16->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mcode
# ifdef __STDC__
(Positions_tPosition ppos)
# else
(ppos)
Positions_tPosition ppos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_code]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_code;
  {
    register Tree_ycode *W_17 = &yyt->U_1.V_42.code;

    W_17->pos = ppos;
  }
  return yyt;
}

Tree_tTree Tree_mCdStr
# ifdef __STDC__
(Positions_tPosition ppos, Idents_tIdent pident, Tree_tTree pcode)
# else
(ppos, pident, pcode)
Positions_tPosition ppos;
Idents_tIdent pident;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdStr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdStr;
  {
    register Tree_yCdStr *W_18 = &yyt->U_1.V_43.CdStr;

    W_18->pos = ppos;
    W_18->ident = pident;
    W_18->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdId
# ifdef __STDC__
(Positions_tPosition ppos, Idents_tIdent pident, Tree_tTree pcode)
# else
(ppos, pident, pcode)
Positions_tPosition ppos;
Idents_tIdent pident;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdId]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdId;
  {
    register Tree_yCdId *W_19 = &yyt->U_1.V_44.CdId;

    W_19->pos = ppos;
    W_19->ident = pident;
    W_19->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdDot
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pcode)
# else
(ppos, pcode)
Positions_tPosition ppos;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdDot]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdDot;
  {
    register Tree_yCdDot *W_20 = &yyt->U_1.V_45.CdDot;

    W_20->pos = ppos;
    W_20->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdComma
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pcode)
# else
(ppos, pcode)
Positions_tPosition ppos;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdComma]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdComma;
  {
    register Tree_yCdComma *W_21 = &yyt->U_1.V_46.CdComma;

    W_21->pos = ppos;
    W_21->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdLPar
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pcode)
# else
(ppos, pcode)
Positions_tPosition ppos;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdLPar]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdLPar;
  {
    register Tree_yCdLPar *W_22 = &yyt->U_1.V_47.CdLPar;

    W_22->pos = ppos;
    W_22->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdRPar
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pcode)
# else
(ppos, pcode)
Positions_tPosition ppos;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdRPar]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdRPar;
  {
    register Tree_yCdRPar *W_23 = &yyt->U_1.V_48.CdRPar;

    W_23->pos = ppos;
    W_23->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdLBra
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pcode)
# else
(ppos, pcode)
Positions_tPosition ppos;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdLBra]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdLBra;
  {
    register Tree_yCdLBra *W_24 = &yyt->U_1.V_49.CdLBra;

    W_24->pos = ppos;
    W_24->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdRBra
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pcode)
# else
(ppos, pcode)
Positions_tPosition ppos;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdRBra]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdRBra;
  {
    register Tree_yCdRBra *W_25 = &yyt->U_1.V_50.CdRBra;

    W_25->pos = ppos;
    W_25->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdSpa
# ifdef __STDC__
(Positions_tPosition ppos, StringMem_tStringRef pref, Tree_tTree pcode)
# else
(ppos, pref, pcode)
Positions_tPosition ppos;
StringMem_tStringRef pref;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdSpa]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdSpa;
  {
    register Tree_yCdSpa *W_26 = &yyt->U_1.V_51.CdSpa;

    W_26->pos = ppos;
    W_26->ref = pref;
    W_26->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdCom
# ifdef __STDC__
(Positions_tPosition ppos, StringMem_tStringRef pref, Tree_tTree pcode)
# else
(ppos, pref, pcode)
Positions_tPosition ppos;
StringMem_tStringRef pref;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdCom]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdCom;
  {
    register Tree_yCdCom *W_27 = &yyt->U_1.V_52.CdCom;

    W_27->pos = ppos;
    W_27->ref = pref;
    W_27->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdRst
# ifdef __STDC__
(Positions_tPosition ppos, StringMem_tStringRef pref, Tree_tTree pcode)
# else
(ppos, pref, pcode)
Positions_tPosition ppos;
StringMem_tStringRef pref;
Tree_tTree pcode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdRst]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdRst;
  {
    register Tree_yCdRst *W_28 = &yyt->U_1.V_53.CdRst;

    W_28->pos = ppos;
    W_28->ref = pref;
    W_28->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCdEnd
# ifdef __STDC__
(Positions_tPosition ppos)
# else
(ppos)
Positions_tPosition ppos;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_CdEnd]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_CdEnd;
  {
    register Tree_yCdEnd *W_29 = &yyt->U_1.V_54.CdEnd;

    W_29->pos = ppos;
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
    case Tree_Spec:;
      yyMark(yyt->U_1.V_4.Spec.export);
      yyMark(yyt->U_1.V_4.Spec.global);
      yyMark(yyt->U_1.V_4.Spec.begin);
      yyMark(yyt->U_1.V_4.Spec.close);
      yyMark(yyt->U_1.V_4.Spec.classes);
      yyt = yyt->U_1.V_4.Spec.functions;
      break;
    case Tree_Class:;
      yyMark(yyt->U_1.V_7.Class.nodes);
      yyt = yyt->U_1.V_7.Class.classes;
      break;
    case Tree_Node:;
      yyMark(yyt->U_1.V_10.Node.sons);
      yyt = yyt->U_1.V_10.Node.nodes;
      break;
    case Tree_Son:;
      yyt = yyt->U_1.V_13.Son.sons;
      break;
    case Tree_Attribute:;
      yyt = yyt->U_1.V_16.Attribute.attributes;
      break;
    case Tree_Function:;
      yyMark(yyt->U_1.V_19.Function.in);
      yyMark(yyt->U_1.V_19.Function.out);
      yyMark(yyt->U_1.V_19.Function.result);
      yyMark(yyt->U_1.V_19.Function.domain);
      yyMark(yyt->U_1.V_19.Function.directives);
      yyt = yyt->U_1.V_19.Function.functions;
      break;
    case Tree_Ident:;
      yyt = yyt->U_1.V_25.Ident.domain;
      break;
    case Tree_Directive:;
      yyMark(yyt->U_1.V_28.Directive.pattern);
      yyMark(yyt->U_1.V_28.Directive.condition);
      yyMark(yyt->U_1.V_28.Directive.costs);
      yyMark(yyt->U_1.V_28.Directive.decl);
      yyMark(yyt->U_1.V_28.Directive.instr);
      yyt = yyt->U_1.V_28.Directive.directives;
      break;
    case Tree_Pattern:;
      yyt = yyt->U_1.V_31.Pattern.patterns;
      break;
    case Tree_Patterns:;
      yyMark(yyt->U_1.V_34.Patterns.pattern);
      yyt = yyt->U_1.V_34.Patterns.patterns;
      break;
    case Tree_CondF:;
      yyt = yyt->U_1.V_37.CondF.code;
      break;
    case Tree_CostF:;
      yyt = yyt->U_1.V_41.CostF.code;
      break;
    case Tree_CdStr:;
      yyt = yyt->U_1.V_43.CdStr.code;
      break;
    case Tree_CdId:;
      yyt = yyt->U_1.V_44.CdId.code;
      break;
    case Tree_CdDot:;
      yyt = yyt->U_1.V_45.CdDot.code;
      break;
    case Tree_CdComma:;
      yyt = yyt->U_1.V_46.CdComma.code;
      break;
    case Tree_CdLPar:;
      yyt = yyt->U_1.V_47.CdLPar.code;
      break;
    case Tree_CdRPar:;
      yyt = yyt->U_1.V_48.CdRPar.code;
      break;
    case Tree_CdLBra:;
      yyt = yyt->U_1.V_49.CdLBra.code;
      break;
    case Tree_CdRBra:;
      yyt = yyt->U_1.V_50.CdRBra.code;
      break;
    case Tree_CdSpa:;
      yyt = yyt->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      yyt = yyt->U_1.V_52.CdCom.code;
      break;
    case Tree_CdRst:;
      yyt = yyt->U_1.V_53.CdRst.code;
      break;
    default :
      return;
      break;
    }
  } EXIT_1:;
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
  yyIndentSelector((STRING)"name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_4.Spec.name);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_4.Spec.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"grna", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_4.Spec.grna);
  yyWriteNl();
  yyIndentSelector((STRING)"grpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_4.Spec.grpos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"export", 6L, yyt->U_1.V_4.Spec.export);
  yyIndentSelectorTree((STRING)"global", 6L, yyt->U_1.V_4.Spec.global);
  yyIndentSelectorTree((STRING)"begin", 5L, yyt->U_1.V_4.Spec.begin);
  yyIndentSelectorTree((STRING)"close", 5L, yyt->U_1.V_4.Spec.close);
  yyIndentSelectorTree((STRING)"classes", 7L, yyt->U_1.V_4.Spec.classes);
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
  yyIndentSelector((STRING)"suid", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_7.Class.suid);
  yyWriteNl();
  yyIndentSelector((STRING)"supos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_7.Class.supos);
  yyWriteNl();
  yyIndentSelector((STRING)"clid", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_7.Class.clid);
  yyWriteNl();
  yyIndentSelector((STRING)"clpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_7.Class.clpos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"nodes", 5L, yyt->U_1.V_7.Class.nodes);
  yyIndentSelector((STRING)"correct", 7L);
  IO_WriteB(yyf, yyt->U_1.V_7.Class.correct);
  yyWriteNl();
}

static void yWriteNode
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Node", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_10.Node.name);
  yyWriteNl();
  yyIndentSelector((STRING)"napos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_10.Node.napos);
  yyWriteNl();
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_10.Node.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"idpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_10.Node.idpos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"sons", 4L, yyt->U_1.V_10.Node.sons);
  yyIndentSelector((STRING)"correct", 7L);
  IO_WriteB(yyf, yyt->U_1.V_10.Node.correct);
  yyWriteNl();
}

static void yWriteSon
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Son", 3L);
  yyWriteNl();
  yyIndentSelector((STRING)"name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_13.Son.name);
  yyWriteNl();
  yyIndentSelector((STRING)"napos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_13.Son.napos);
  yyWriteNl();
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_13.Son.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"idpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_13.Son.idpos);
  yyWriteNl();
  yyIndentSelector((STRING)"correct", 7L);
  IO_WriteB(yyf, yyt->U_1.V_13.Son.correct);
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
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_16.Attribute.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"idpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_16.Attribute.idpos);
  yyWriteNl();
  yyIndentSelector((STRING)"mod", 3L);
  Idents_WriteIdent(yyf, yyt->U_1.V_16.Attribute.mod);
  yyWriteNl();
  yyIndentSelector((STRING)"mopos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_16.Attribute.mopos);
  yyWriteNl();
  yyIndentSelector((STRING)"type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_16.Attribute.type);
  yyWriteNl();
  yyIndentSelector((STRING)"typos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_16.Attribute.typos);
  yyWriteNl();
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
  yyIndentSelector((STRING)"name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_19.Function.name);
  yyWriteNl();
  yyIndentSelector((STRING)"napos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_19.Function.napos);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"in", 2L, yyt->U_1.V_19.Function.in);
  yyIndentSelectorTree((STRING)"out", 3L, yyt->U_1.V_19.Function.out);
  yyIndentSelectorTree((STRING)"result", 6L, yyt->U_1.V_19.Function.result);
  yyIndentSelectorTree((STRING)"domain", 6L, yyt->U_1.V_19.Function.domain);
  yyIndentSelectorTree((STRING)"directives", 10L, yyt->U_1.V_19.Function.directives);
  yyIndentSelector((STRING)"funct", 5L);
  yyWriteHex((WORD *)&yyt->U_1.V_19.Function.funct, (LONGCARD)sizeof(yyt->U_1.V_19.Function.funct));
  yyWriteNl();
  yyIndentSelector((STRING)"domainset", 9L);
  Sets_WriteSet(yyf, yyt->U_1.V_19.Function.domainset);
  yyWriteNl();
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
  yyIndentSelector((STRING)"mod", 3L);
  Idents_WriteIdent(yyf, yyt->U_1.V_22.Type.mod);
  yyWriteNl();
  yyIndentSelector((STRING)"mopos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_22.Type.mopos);
  yyWriteNl();
  yyIndentSelector((STRING)"type", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_22.Type.type);
  yyWriteNl();
  yyIndentSelector((STRING)"typos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_22.Type.typos);
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
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_25.Ident.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"idpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_25.Ident.idpos);
  yyWriteNl();
}

static void yWriteDirective
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Directive", 9L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"pattern", 7L, yyt->U_1.V_28.Directive.pattern);
  yyIndentSelectorTree((STRING)"condition", 9L, yyt->U_1.V_28.Directive.condition);
  yyIndentSelectorTree((STRING)"costs", 5L, yyt->U_1.V_28.Directive.costs);
  yyIndentSelectorTree((STRING)"decl", 4L, yyt->U_1.V_28.Directive.decl);
  yyIndentSelectorTree((STRING)"instr", 5L, yyt->U_1.V_28.Directive.instr);
  yyIndentSelector((STRING)"correct", 7L);
  IO_WriteB(yyf, yyt->U_1.V_28.Directive.correct);
  yyWriteNl();
  yyIndentSelector((STRING)"number", 6L);
  IO_WriteI(yyf, yyt->U_1.V_28.Directive.number, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"pat", 3L);
  yyWriteHex((WORD *)&yyt->U_1.V_28.Directive.pat, (LONGCARD)sizeof(yyt->U_1.V_28.Directive.pat));
  yyWriteNl();
  yyIndentSelector((STRING)"iter", 4L);
  IO_WriteB(yyf, yyt->U_1.V_28.Directive.iter);
  yyWriteNl();
}

static void yWritepattern
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"pattern", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_29.pattern.pos);
  yyWriteNl();
}

static void yWritePattern1
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Pattern1", 8L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_30.Pattern1.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"sel", 3L);
  Idents_WriteIdent(yyf, yyt->U_1.V_30.Pattern1.sel);
  yyWriteNl();
  yyIndentSelector((STRING)"sepos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_30.Pattern1.sepos);
  yyWriteNl();
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_30.Pattern1.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"idpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_30.Pattern1.idpos);
  yyWriteNl();
  yyIndentSelector((STRING)"correct", 7L);
  IO_WriteB(yyf, yyt->U_1.V_30.Pattern1.correct);
  yyWriteNl();
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
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_31.Pattern.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"sel", 3L);
  Idents_WriteIdent(yyf, yyt->U_1.V_31.Pattern.sel);
  yyWriteNl();
  yyIndentSelector((STRING)"sepos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_31.Pattern.sepos);
  yyWriteNl();
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_31.Pattern.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"idpos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_31.Pattern.idpos);
  yyWriteNl();
  yyIndentSelector((STRING)"correct", 7L);
  IO_WriteB(yyf, yyt->U_1.V_31.Pattern.correct);
  yyWriteNl();
}

static void yWritePatterns
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"Patterns", 8L);
  yyWriteNl();
  yyIndentSelectorTree((STRING)"pattern", 7L, yyt->U_1.V_34.Patterns.pattern);
}

static void yWriteCondF
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CondF", 5L);
  yyWriteNl();
}

static void yWriteCostN
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CostN", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"value", 5L);
  IO_WriteI(yyf, yyt->U_1.V_40.CostN.value, 0L);
  yyWriteNl();
  yyIndentSelector((STRING)"vapos", 5L);
  Positions_WritePosition(yyf, yyt->U_1.V_40.CostN.vapos);
  yyWriteNl();
}

static void yWriteCostF
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CostF", 5L);
  yyWriteNl();
}

static void yWritecode
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"code", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_42.code.pos);
  yyWriteNl();
}

static void yWriteCdStr
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdStr", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_43.CdStr.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_43.CdStr.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"mode", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_43.CdStr.mode, (LONGCARD)sizeof(yyt->U_1.V_43.CdStr.mode));
  yyWriteNl();
}

static void yWriteCdId
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdId", 4L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_44.CdId.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"ident", 5L);
  Idents_WriteIdent(yyf, yyt->U_1.V_44.CdId.ident);
  yyWriteNl();
  yyIndentSelector((STRING)"mode", 4L);
  yyWriteHex((WORD *)&yyt->U_1.V_44.CdId.mode, (LONGCARD)sizeof(yyt->U_1.V_44.CdId.mode));
  yyWriteNl();
}

static void yWriteCdDot
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdDot", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_45.CdDot.pos);
  yyWriteNl();
}

static void yWriteCdComma
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdComma", 7L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_46.CdComma.pos);
  yyWriteNl();
}

static void yWriteCdLPar
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdLPar", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_47.CdLPar.pos);
  yyWriteNl();
}

static void yWriteCdRPar
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdRPar", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_48.CdRPar.pos);
  yyWriteNl();
}

static void yWriteCdLBra
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdLBra", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_49.CdLBra.pos);
  yyWriteNl();
}

static void yWriteCdRBra
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdRBra", 6L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_50.CdRBra.pos);
  yyWriteNl();
}

static void yWriteCdSpa
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdSpa", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_51.CdSpa.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"ref", 3L);
  StringMem_WriteString(yyf, yyt->U_1.V_51.CdSpa.ref);
  yyWriteNl();
}

static void yWriteCdCom
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdCom", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_52.CdCom.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"ref", 3L);
  StringMem_WriteString(yyf, yyt->U_1.V_52.CdCom.ref);
  yyWriteNl();
}

static void yWriteCdRst
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdRst", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_53.CdRst.pos);
  yyWriteNl();
  yyIndentSelector((STRING)"ref", 3L);
  StringMem_WriteString(yyf, yyt->U_1.V_53.CdRst.ref);
  yyWriteNl();
}

static void yWriteCdEnd
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(yyf, (STRING)"CdEnd", 5L);
  yyWriteNl();
  yyIndentSelector((STRING)"pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_54.CdEnd.pos);
  yyWriteNl();
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
    case Tree_spec:;
      IO_WriteS(yyf, (STRING)"spec", 4L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Spec:;
      yWriteSpec(yyt);
      yyIndentSelector((STRING)"functions", 9L);
      yyt = yyt->U_1.V_4.Spec.functions;
      break;
    case Tree_classes:;
      IO_WriteS(yyf, (STRING)"classes", 7L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Class0:;
      IO_WriteS(yyf, (STRING)"Class0", 6L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Class:;
      yWriteClass(yyt);
      yyIndentSelector((STRING)"classes", 7L);
      yyt = yyt->U_1.V_7.Class.classes;
      break;
    case Tree_nodes:;
      IO_WriteS(yyf, (STRING)"nodes", 5L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Node0:;
      IO_WriteS(yyf, (STRING)"Node0", 5L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Node:;
      yWriteNode(yyt);
      yyIndentSelector((STRING)"nodes", 5L);
      yyt = yyt->U_1.V_10.Node.nodes;
      break;
    case Tree_sons:;
      IO_WriteS(yyf, (STRING)"sons", 4L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Son0:;
      IO_WriteS(yyf, (STRING)"Son0", 4L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Son:;
      yWriteSon(yyt);
      yyIndentSelector((STRING)"sons", 4L);
      yyt = yyt->U_1.V_13.Son.sons;
      break;
    case Tree_attributes:;
      IO_WriteS(yyf, (STRING)"attributes", 10L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Attribute0:;
      IO_WriteS(yyf, (STRING)"Attribute0", 10L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Attribute:;
      yWriteAttribute(yyt);
      yyIndentSelector((STRING)"attributes", 10L);
      yyt = yyt->U_1.V_16.Attribute.attributes;
      break;
    case Tree_functions:;
      IO_WriteS(yyf, (STRING)"functions", 9L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Function0:;
      IO_WriteS(yyf, (STRING)"Function0", 9L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Function:;
      yWriteFunction(yyt);
      yyIndentSelector((STRING)"functions", 9L);
      yyt = yyt->U_1.V_19.Function.functions;
      break;
    case Tree_result:;
      IO_WriteS(yyf, (STRING)"result", 6L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_NoResult:;
      IO_WriteS(yyf, (STRING)"NoResult", 8L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Type:;
      yWriteType(yyt);
      goto EXIT_2;
      break;
    case Tree_domain:;
      IO_WriteS(yyf, (STRING)"domain", 6L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Ident0:;
      IO_WriteS(yyf, (STRING)"Ident0", 6L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Ident:;
      yWriteIdent(yyt);
      yyIndentSelector((STRING)"domain", 6L);
      yyt = yyt->U_1.V_25.Ident.domain;
      break;
    case Tree_directives:;
      IO_WriteS(yyf, (STRING)"directives", 10L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Directive0:;
      IO_WriteS(yyf, (STRING)"Directive0", 10L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Directive:;
      yWriteDirective(yyt);
      yyIndentSelector((STRING)"directives", 10L);
      yyt = yyt->U_1.V_28.Directive.directives;
      break;
    case Tree_pattern:;
      yWritepattern(yyt);
      goto EXIT_2;
      break;
    case Tree_Pattern1:;
      yWritePattern1(yyt);
      goto EXIT_2;
      break;
    case Tree_Pattern:;
      yWritePattern(yyt);
      yyIndentSelector((STRING)"patterns", 8L);
      yyt = yyt->U_1.V_31.Pattern.patterns;
      break;
    case Tree_patterns:;
      IO_WriteS(yyf, (STRING)"patterns", 8L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Patterns0:;
      IO_WriteS(yyf, (STRING)"Patterns0", 9L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_Patterns:;
      yWritePatterns(yyt);
      yyIndentSelector((STRING)"patterns", 8L);
      yyt = yyt->U_1.V_34.Patterns.patterns;
      break;
    case Tree_condition:;
      IO_WriteS(yyf, (STRING)"condition", 9L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_CondD:;
      IO_WriteS(yyf, (STRING)"CondD", 5L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_CondF:;
      yWriteCondF(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_37.CondF.code;
      break;
    case Tree_costs:;
      IO_WriteS(yyf, (STRING)"costs", 5L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_CostD:;
      IO_WriteS(yyf, (STRING)"CostD", 5L);
      yyWriteNl();
      goto EXIT_2;
      break;
    case Tree_CostN:;
      yWriteCostN(yyt);
      goto EXIT_2;
      break;
    case Tree_CostF:;
      yWriteCostF(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_41.CostF.code;
      break;
    case Tree_code:;
      yWritecode(yyt);
      goto EXIT_2;
      break;
    case Tree_CdStr:;
      yWriteCdStr(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_43.CdStr.code;
      break;
    case Tree_CdId:;
      yWriteCdId(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_44.CdId.code;
      break;
    case Tree_CdDot:;
      yWriteCdDot(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_45.CdDot.code;
      break;
    case Tree_CdComma:;
      yWriteCdComma(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_46.CdComma.code;
      break;
    case Tree_CdLPar:;
      yWriteCdLPar(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_47.CdLPar.code;
      break;
    case Tree_CdRPar:;
      yWriteCdRPar(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_48.CdRPar.code;
      break;
    case Tree_CdLBra:;
      yWriteCdLBra(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_49.CdLBra.code;
      break;
    case Tree_CdRBra:;
      yWriteCdRBra(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_50.CdRBra.code;
      break;
    case Tree_CdSpa:;
      yWriteCdSpa(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      yWriteCdCom(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_52.CdCom.code;
      break;
    case Tree_CdRst:;
      yWriteCdRst(yyt);
      yyIndentSelector((STRING)"code", 4L);
      yyt = yyt->U_1.V_53.CdRst.code;
      break;
    case Tree_CdEnd:;
      yWriteCdEnd(yyt);
      goto EXIT_2;
      break;
    default :
      goto EXIT_2;
      break;
    }
  } EXIT_2:;
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
      yyNext = yyOld->U_1.V_7.Class.classes;
      yyOld->U_1.V_7.Class.classes = yyNew;
      break;
    case Tree_Node:;
      yyNext = yyOld->U_1.V_10.Node.nodes;
      yyOld->U_1.V_10.Node.nodes = yyNew;
      break;
    case Tree_Son:;
      yyNext = yyOld->U_1.V_13.Son.sons;
      yyOld->U_1.V_13.Son.sons = yyNew;
      break;
    case Tree_Attribute:;
      yyNext = yyOld->U_1.V_16.Attribute.attributes;
      yyOld->U_1.V_16.Attribute.attributes = yyNew;
      break;
    case Tree_Function:;
      yyNext = yyOld->U_1.V_19.Function.functions;
      yyOld->U_1.V_19.Function.functions = yyNew;
      break;
    case Tree_Ident:;
      yyNext = yyOld->U_1.V_25.Ident.domain;
      yyOld->U_1.V_25.Ident.domain = yyNew;
      break;
    case Tree_Directive:;
      yyNext = yyOld->U_1.V_28.Directive.directives;
      yyOld->U_1.V_28.Directive.directives = yyNew;
      break;
    case Tree_Patterns:;
      yyNext = yyOld->U_1.V_34.Patterns.patterns;
      yyOld->U_1.V_34.Patterns.patterns = yyNew;
      break;
    case Tree_CdStr:;
      yyNext = yyOld->U_1.V_43.CdStr.code;
      yyOld->U_1.V_43.CdStr.code = yyNew;
      break;
    case Tree_CdId:;
      yyNext = yyOld->U_1.V_44.CdId.code;
      yyOld->U_1.V_44.CdId.code = yyNew;
      break;
    case Tree_CdDot:;
      yyNext = yyOld->U_1.V_45.CdDot.code;
      yyOld->U_1.V_45.CdDot.code = yyNew;
      break;
    case Tree_CdComma:;
      yyNext = yyOld->U_1.V_46.CdComma.code;
      yyOld->U_1.V_46.CdComma.code = yyNew;
      break;
    case Tree_CdLPar:;
      yyNext = yyOld->U_1.V_47.CdLPar.code;
      yyOld->U_1.V_47.CdLPar.code = yyNew;
      break;
    case Tree_CdRPar:;
      yyNext = yyOld->U_1.V_48.CdRPar.code;
      yyOld->U_1.V_48.CdRPar.code = yyNew;
      break;
    case Tree_CdLBra:;
      yyNext = yyOld->U_1.V_49.CdLBra.code;
      yyOld->U_1.V_49.CdLBra.code = yyNew;
      break;
    case Tree_CdRBra:;
      yyNext = yyOld->U_1.V_50.CdRBra.code;
      yyOld->U_1.V_50.CdRBra.code = yyNew;
      break;
    case Tree_CdSpa:;
      yyNext = yyOld->U_1.V_51.CdSpa.code;
      yyOld->U_1.V_51.CdSpa.code = yyNew;
      break;
    case Tree_CdCom:;
      yyNext = yyOld->U_1.V_52.CdCom.code;
      yyOld->U_1.V_52.CdCom.code = yyNew;
      break;
    case Tree_CdRst:;
      yyNext = yyOld->U_1.V_53.CdRst.code;
      yyOld->U_1.V_53.CdRst.code = yyNew;
      break;
    default :
      goto EXIT_3;
      break;
    }
    yyNew = yyOld;
    yyOld = yyNext;
  } EXIT_3:;
  switch (yyTail->U_1.V_1.Kind) {
  case Tree_Class:;
    yyTail->U_1.V_7.Class.classes = yyOld;
    break;
  case Tree_Node:;
    yyTail->U_1.V_10.Node.nodes = yyOld;
    break;
  case Tree_Son:;
    yyTail->U_1.V_13.Son.sons = yyOld;
    break;
  case Tree_Attribute:;
    yyTail->U_1.V_16.Attribute.attributes = yyOld;
    break;
  case Tree_Function:;
    yyTail->U_1.V_19.Function.functions = yyOld;
    break;
  case Tree_Ident:;
    yyTail->U_1.V_25.Ident.domain = yyOld;
    break;
  case Tree_Directive:;
    yyTail->U_1.V_28.Directive.directives = yyOld;
    break;
  case Tree_Patterns:;
    yyTail->U_1.V_34.Patterns.patterns = yyOld;
    break;
  case Tree_CdStr:;
    yyTail->U_1.V_43.CdStr.code = yyOld;
    break;
  case Tree_CdId:;
    yyTail->U_1.V_44.CdId.code = yyOld;
    break;
  case Tree_CdDot:;
    yyTail->U_1.V_45.CdDot.code = yyOld;
    break;
  case Tree_CdComma:;
    yyTail->U_1.V_46.CdComma.code = yyOld;
    break;
  case Tree_CdLPar:;
    yyTail->U_1.V_47.CdLPar.code = yyOld;
    break;
  case Tree_CdRPar:;
    yyTail->U_1.V_48.CdRPar.code = yyOld;
    break;
  case Tree_CdLBra:;
    yyTail->U_1.V_49.CdLBra.code = yyOld;
    break;
  case Tree_CdRBra:;
    yyTail->U_1.V_50.CdRBra.code = yyOld;
    break;
  case Tree_CdSpa:;
    yyTail->U_1.V_51.CdSpa.code = yyOld;
    break;
  case Tree_CdCom:;
    yyTail->U_1.V_52.CdCom.code = yyOld;
    break;
  case Tree_CdRst:;
    yyTail->U_1.V_53.CdRst.code = yyOld;
    break;
  default :
    break;
  }
  return yyNew;
}

void Tree_BeginTree
# ifdef __STDC__
()
# else
()
# endif
{
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
    Idents__init();
    IO__init();
    Environs__init();
    Patterns__init();
    Positions__init();
    Sets__init();
    StringMem__init();
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
    Idents__init();
    Positions__init();
    IO__init();
    StringMem__init();

    yyBlockList = NIL;
    Tree_yyPoolFreePtr = (ADDRESS)NIL;
    Tree_yyPoolMaxPtr = (ADDRESS)NIL;
    Tree_HeapUsed = 0;
    Tree_yyExit = xxExit;
    Tree_yyNodeSize.A[Tree_spec] = sizeof(Tree_yspec);
    Tree_yyNodeSize.A[Tree_Spec] = sizeof(Tree_ySpec);
    Tree_yyNodeSize.A[Tree_classes] = sizeof(Tree_yclasses);
    Tree_yyNodeSize.A[Tree_Class0] = sizeof(Tree_yClass0);
    Tree_yyNodeSize.A[Tree_Class] = sizeof(Tree_yClass);
    Tree_yyNodeSize.A[Tree_nodes] = sizeof(Tree_ynodes);
    Tree_yyNodeSize.A[Tree_Node0] = sizeof(Tree_yNode0);
    Tree_yyNodeSize.A[Tree_Node] = sizeof(Tree_yNode);
    Tree_yyNodeSize.A[Tree_sons] = sizeof(Tree_ysons);
    Tree_yyNodeSize.A[Tree_Son0] = sizeof(Tree_ySon0);
    Tree_yyNodeSize.A[Tree_Son] = sizeof(Tree_ySon);
    Tree_yyNodeSize.A[Tree_attributes] = sizeof(Tree_yattributes);
    Tree_yyNodeSize.A[Tree_Attribute0] = sizeof(Tree_yAttribute0);
    Tree_yyNodeSize.A[Tree_Attribute] = sizeof(Tree_yAttribute);
    Tree_yyNodeSize.A[Tree_functions] = sizeof(Tree_yfunctions);
    Tree_yyNodeSize.A[Tree_Function0] = sizeof(Tree_yFunction0);
    Tree_yyNodeSize.A[Tree_Function] = sizeof(Tree_yFunction);
    Tree_yyNodeSize.A[Tree_result] = sizeof(Tree_yresult);
    Tree_yyNodeSize.A[Tree_NoResult] = sizeof(Tree_yNoResult);
    Tree_yyNodeSize.A[Tree_Type] = sizeof(Tree_yType);
    Tree_yyNodeSize.A[Tree_domain] = sizeof(Tree_ydomain);
    Tree_yyNodeSize.A[Tree_Ident0] = sizeof(Tree_yIdent0);
    Tree_yyNodeSize.A[Tree_Ident] = sizeof(Tree_yIdent);
    Tree_yyNodeSize.A[Tree_directives] = sizeof(Tree_ydirectives);
    Tree_yyNodeSize.A[Tree_Directive0] = sizeof(Tree_yDirective0);
    Tree_yyNodeSize.A[Tree_Directive] = sizeof(Tree_yDirective);
    Tree_yyNodeSize.A[Tree_pattern] = sizeof(Tree_ypattern);
    Tree_yyNodeSize.A[Tree_Pattern1] = sizeof(Tree_yPattern1);
    Tree_yyNodeSize.A[Tree_Pattern] = sizeof(Tree_yPattern);
    Tree_yyNodeSize.A[Tree_patterns] = sizeof(Tree_ypatterns);
    Tree_yyNodeSize.A[Tree_Patterns0] = sizeof(Tree_yPatterns0);
    Tree_yyNodeSize.A[Tree_Patterns] = sizeof(Tree_yPatterns);
    Tree_yyNodeSize.A[Tree_condition] = sizeof(Tree_ycondition);
    Tree_yyNodeSize.A[Tree_CondD] = sizeof(Tree_yCondD);
    Tree_yyNodeSize.A[Tree_CondF] = sizeof(Tree_yCondF);
    Tree_yyNodeSize.A[Tree_costs] = sizeof(Tree_ycosts);
    Tree_yyNodeSize.A[Tree_CostD] = sizeof(Tree_yCostD);
    Tree_yyNodeSize.A[Tree_CostN] = sizeof(Tree_yCostN);
    Tree_yyNodeSize.A[Tree_CostF] = sizeof(Tree_yCostF);
    Tree_yyNodeSize.A[Tree_code] = sizeof(Tree_ycode);
    Tree_yyNodeSize.A[Tree_CdStr] = sizeof(Tree_yCdStr);
    Tree_yyNodeSize.A[Tree_CdId] = sizeof(Tree_yCdId);
    Tree_yyNodeSize.A[Tree_CdDot] = sizeof(Tree_yCdDot);
    Tree_yyNodeSize.A[Tree_CdComma] = sizeof(Tree_yCdComma);
    Tree_yyNodeSize.A[Tree_CdLPar] = sizeof(Tree_yCdLPar);
    Tree_yyNodeSize.A[Tree_CdRPar] = sizeof(Tree_yCdRPar);
    Tree_yyNodeSize.A[Tree_CdLBra] = sizeof(Tree_yCdLBra);
    Tree_yyNodeSize.A[Tree_CdRBra] = sizeof(Tree_yCdRBra);
    Tree_yyNodeSize.A[Tree_CdSpa] = sizeof(Tree_yCdSpa);
    Tree_yyNodeSize.A[Tree_CdCom] = sizeof(Tree_yCdCom);
    Tree_yyNodeSize.A[Tree_CdRst] = sizeof(Tree_yCdRst);
    Tree_yyNodeSize.A[Tree_CdEnd] = sizeof(Tree_yCdEnd);
    yyMaxSize = 0;
    for (yyi = 1; yyi <= 52; yyi += 1) {
      Tree_yyNodeSize.A[yyi] = (LONGINT)((BITSET)(Tree_yyNodeSize.A[yyi] + (CARDINAL)General_MaxAlign - 1) & General_AlignMasks.A[General_MaxAlign]);
      yyMaxSize = General_Max((LONGINT)Tree_yyNodeSize.A[yyi], (LONGINT)yyMaxSize);
    }
    yyTypeRange.A[Tree_spec] = Tree_Spec;
    yyTypeRange.A[Tree_Spec] = Tree_Spec;
    yyTypeRange.A[Tree_classes] = Tree_Class;
    yyTypeRange.A[Tree_Class0] = Tree_Class0;
    yyTypeRange.A[Tree_Class] = Tree_Class;
    yyTypeRange.A[Tree_nodes] = Tree_Node;
    yyTypeRange.A[Tree_Node0] = Tree_Node0;
    yyTypeRange.A[Tree_Node] = Tree_Node;
    yyTypeRange.A[Tree_sons] = Tree_Son;
    yyTypeRange.A[Tree_Son0] = Tree_Son0;
    yyTypeRange.A[Tree_Son] = Tree_Son;
    yyTypeRange.A[Tree_attributes] = Tree_Attribute;
    yyTypeRange.A[Tree_Attribute0] = Tree_Attribute0;
    yyTypeRange.A[Tree_Attribute] = Tree_Attribute;
    yyTypeRange.A[Tree_functions] = Tree_Function;
    yyTypeRange.A[Tree_Function0] = Tree_Function0;
    yyTypeRange.A[Tree_Function] = Tree_Function;
    yyTypeRange.A[Tree_result] = Tree_Type;
    yyTypeRange.A[Tree_NoResult] = Tree_NoResult;
    yyTypeRange.A[Tree_Type] = Tree_Type;
    yyTypeRange.A[Tree_domain] = Tree_Ident;
    yyTypeRange.A[Tree_Ident0] = Tree_Ident0;
    yyTypeRange.A[Tree_Ident] = Tree_Ident;
    yyTypeRange.A[Tree_directives] = Tree_Directive;
    yyTypeRange.A[Tree_Directive0] = Tree_Directive0;
    yyTypeRange.A[Tree_Directive] = Tree_Directive;
    yyTypeRange.A[Tree_pattern] = Tree_Pattern;
    yyTypeRange.A[Tree_Pattern1] = Tree_Pattern1;
    yyTypeRange.A[Tree_Pattern] = Tree_Pattern;
    yyTypeRange.A[Tree_patterns] = Tree_Patterns;
    yyTypeRange.A[Tree_Patterns0] = Tree_Patterns0;
    yyTypeRange.A[Tree_Patterns] = Tree_Patterns;
    yyTypeRange.A[Tree_condition] = Tree_CondF;
    yyTypeRange.A[Tree_CondD] = Tree_CondD;
    yyTypeRange.A[Tree_CondF] = Tree_CondF;
    yyTypeRange.A[Tree_costs] = Tree_CostF;
    yyTypeRange.A[Tree_CostD] = Tree_CostD;
    yyTypeRange.A[Tree_CostN] = Tree_CostN;
    yyTypeRange.A[Tree_CostF] = Tree_CostF;
    yyTypeRange.A[Tree_code] = Tree_CdEnd;
    yyTypeRange.A[Tree_CdStr] = Tree_CdStr;
    yyTypeRange.A[Tree_CdId] = Tree_CdId;
    yyTypeRange.A[Tree_CdDot] = Tree_CdDot;
    yyTypeRange.A[Tree_CdComma] = Tree_CdComma;
    yyTypeRange.A[Tree_CdLPar] = Tree_CdLPar;
    yyTypeRange.A[Tree_CdRPar] = Tree_CdRPar;
    yyTypeRange.A[Tree_CdLBra] = Tree_CdLBra;
    yyTypeRange.A[Tree_CdRBra] = Tree_CdRBra;
    yyTypeRange.A[Tree_CdSpa] = Tree_CdSpa;
    yyTypeRange.A[Tree_CdCom] = Tree_CdCom;
    yyTypeRange.A[Tree_CdRst] = Tree_CdRst;
    yyTypeRange.A[Tree_CdEnd] = Tree_CdEnd;
    yyRecursionLevel = 0;
    yyTreeStoreSize = yyInitTreeStoreSize;
    DynArray_MakeArray((ADDRESS *)&yyTreeStorePtr, &yyTreeStoreSize, (LONGINT)sizeof(Tree_tTree));
    Tree_BeginTree();
  }
}
