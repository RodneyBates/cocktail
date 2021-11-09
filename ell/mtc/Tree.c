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

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Info
#include "Info.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

Idents_tIdent Tree_ScannerName, Tree_ParserName;
Tree_tTree Tree_TreeRoot;
LONGCARD Tree_HeapUsed;
ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
struct Tree_45 Tree_yyNodeSize;
PROC Tree_yyExit;

static Strings_tString String;
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
    SHORTCARD A[42 + 1];
} yyTypeRange;
typedef Tree_tTree *yyPtrtTree;
static IO_tFile yyf;
static SHORTCARD yyLabel;
static SHORTCARD yyKind;
static CHAR yyc;
static Strings_tString yys;
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

Tree_tTree Tree_mGrammar
# ifdef __STDC__
(Tree_tTree psections, Tree_tTree ptokens, Tree_tTree prules)
# else
(psections, ptokens, prules)
Tree_tTree psections;
Tree_tTree ptokens;
Tree_tTree prules;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Grammar]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Grammar;
  {
    register Tree_yGrammar *W_1 = &yyt->U_1.V_3.Grammar;

    W_1->sections = psections;
    W_1->tokens = ptokens;
    W_1->rules = prules;
  }
  return yyt;
}

Tree_tTree Tree_msections
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_sections]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_sections;
  return yyt;
}

Tree_tTree Tree_mSections0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Sections0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Sections0;
  return yyt;
}

Tree_tTree Tree_mSections
# ifdef __STDC__
(Tree_tTree psections, Tree_tTree psection)
# else
(psections, psection)
Tree_tTree psections;
Tree_tTree psection;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Sections]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Sections;
  {
    register Tree_ySections *W_2 = &yyt->U_1.V_6.Sections;

    W_2->sections = psections;
    W_2->section = psection;
  }
  return yyt;
}

Tree_tTree Tree_msection
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_section]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_section;
  return yyt;
}

Tree_tTree Tree_mExport
# ifdef __STDC__
(Tree_tTree pcodes)
# else
(pcodes)
Tree_tTree pcodes;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Export]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Export;
  {
    register Tree_yExport *W_3 = &yyt->U_1.V_8.Export;

    W_3->codes = pcodes;
  }
  return yyt;
}

Tree_tTree Tree_mGlobal
# ifdef __STDC__
(Tree_tTree pcodes)
# else
(pcodes)
Tree_tTree pcodes;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Global]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Global;
  {
    register Tree_yGlobal *W_4 = &yyt->U_1.V_9.Global;

    W_4->codes = pcodes;
  }
  return yyt;
}

Tree_tTree Tree_mLocal
# ifdef __STDC__
(Tree_tTree pcodes)
# else
(pcodes)
Tree_tTree pcodes;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Local]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Local;
  {
    register Tree_yLocal *W_5 = &yyt->U_1.V_10.Local;

    W_5->codes = pcodes;
  }
  return yyt;
}

Tree_tTree Tree_mBegin
# ifdef __STDC__
(Tree_tTree pcodes)
# else
(pcodes)
Tree_tTree pcodes;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Begin]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Begin;
  {
    register Tree_yBegin *W_6 = &yyt->U_1.V_11.Begin;

    W_6->codes = pcodes;
  }
  return yyt;
}

Tree_tTree Tree_mClose
# ifdef __STDC__
(Tree_tTree pcodes)
# else
(pcodes)
Tree_tTree pcodes;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Close]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Close;
  {
    register Tree_yClose *W_7 = &yyt->U_1.V_12.Close;

    W_7->codes = pcodes;
  }
  return yyt;
}

Tree_tTree Tree_mcodes
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_codes]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_codes;
  return yyt;
}

Tree_tTree Tree_mCodes0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Codes0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Codes0;
  return yyt;
}

Tree_tTree Tree_mCodes
# ifdef __STDC__
(Tree_tTree pcodes, Tree_tTree pcode)
# else
(pcodes, pcode)
Tree_tTree pcodes;
Tree_tTree pcode;
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
    register Tree_yCodes *W_8 = &yyt->U_1.V_15.Codes;

    W_8->codes = pcodes;
    W_8->code = pcode;
  }
  return yyt;
}

Tree_tTree Tree_mCode
# ifdef __STDC__
(Positions_tPosition ppos, StringMem_tStringRef pref)
# else
(ppos, pref)
Positions_tPosition ppos;
StringMem_tStringRef pref;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Code]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Code;
  {
    register Tree_yCode *W_9 = &yyt->U_1.V_16.Code;

    W_9->pos = ppos;
    W_9->ref = pref;
  }
  return yyt;
}

Tree_tTree Tree_mcode
# ifdef __STDC__
(Positions_tPosition ppos, StringMem_tStringRef pref)
# else
(ppos, pref)
Positions_tPosition ppos;
StringMem_tStringRef pref;
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
    register Tree_ycode *W_10 = &yyt->U_1.V_17.code;

    W_10->pos = ppos;
    W_10->ref = pref;
  }
  return yyt;
}

Tree_tTree Tree_mtokens
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_tokens]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_tokens;
  return yyt;
}

Tree_tTree Tree_mTokens0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Tokens0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Tokens0;
  return yyt;
}

Tree_tTree Tree_mTokens
# ifdef __STDC__
(Tree_tTree ptokens, Tree_tTree ptoken)
# else
(ptokens, ptoken)
Tree_tTree ptokens;
Tree_tTree ptoken;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Tokens]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Tokens;
  {
    register Tree_yTokens *W_11 = &yyt->U_1.V_20.Tokens;

    W_11->tokens = ptokens;
    W_11->token = ptoken;
  }
  return yyt;
}

Tree_tTree Tree_mToken
# ifdef __STDC__
(Tree_tTree pid, Tree_tTree pnumber)
# else
(pid, pnumber)
Tree_tTree pid;
Tree_tTree pnumber;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Token]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Token;
  {
    register Tree_yToken *W_12 = &yyt->U_1.V_21.Token;

    W_12->id = pid;
    W_12->number = pnumber;
  }
  return yyt;
}

Tree_tTree Tree_mtoken
# ifdef __STDC__
(Tree_tTree pid, Tree_tTree pnumber)
# else
(pid, pnumber)
Tree_tTree pid;
Tree_tTree pnumber;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_token]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_token;
  {
    register Tree_ytoken *W_13 = &yyt->U_1.V_22.token;

    W_13->id = pid;
    W_13->number = pnumber;
  }
  return yyt;
}

Tree_tTree Tree_mId
# ifdef __STDC__
(Positions_tPosition ppos, Idents_tIdent pident, BOOLEAN pisstring)
# else
(ppos, pident, pisstring)
Positions_tPosition ppos;
Idents_tIdent pident;
BOOLEAN pisstring;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Id]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Id;
  {
    register Tree_yId *W_14 = &yyt->U_1.V_23.Id;

    W_14->pos = ppos;
    W_14->ident = pident;
    W_14->isstring = pisstring;
  }
  return yyt;
}

Tree_tTree Tree_mid
# ifdef __STDC__
(Positions_tPosition ppos, Idents_tIdent pident, BOOLEAN pisstring)
# else
(ppos, pident, pisstring)
Positions_tPosition ppos;
Idents_tIdent pident;
BOOLEAN pisstring;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_id]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_id;
  {
    register Tree_yid *W_15 = &yyt->U_1.V_24.id;

    W_15->pos = ppos;
    W_15->ident = pident;
    W_15->isstring = pisstring;
  }
  return yyt;
}

Tree_tTree Tree_mNumber
# ifdef __STDC__
(Positions_tPosition ppos, INTEGER pvalue)
# else
(ppos, pvalue)
Positions_tPosition ppos;
INTEGER pvalue;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Number]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Number;
  {
    register Tree_yNumber *W_16 = &yyt->U_1.V_25.Number;

    W_16->pos = ppos;
    W_16->value = pvalue;
  }
  return yyt;
}

Tree_tTree Tree_mnumber
# ifdef __STDC__
(Positions_tPosition ppos, INTEGER pvalue)
# else
(ppos, pvalue)
Positions_tPosition ppos;
INTEGER pvalue;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_number]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_number;
  {
    register Tree_ynumber *W_17 = &yyt->U_1.V_26.number;

    W_17->pos = ppos;
    W_17->value = pvalue;
  }
  return yyt;
}

Tree_tTree Tree_mrules
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_rules]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_rules;
  return yyt;
}

Tree_tTree Tree_mRules0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Rules0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Rules0;
  return yyt;
}

Tree_tTree Tree_mRules
# ifdef __STDC__
(Tree_tTree prules, Tree_tTree prule)
# else
(prules, prule)
Tree_tTree prules;
Tree_tTree prule;
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
  {
    register Tree_yRules *W_18 = &yyt->U_1.V_29.Rules;

    W_18->rules = prules;
    W_18->rule = prule;
  }
  return yyt;
}

Tree_tTree Tree_mRule
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pid, Tree_tTree pcodes, Tree_tTree pexpr)
# else
(ppos, pid, pcodes, pexpr)
Positions_tPosition ppos;
Tree_tTree pid;
Tree_tTree pcodes;
Tree_tTree pexpr;
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
    register Tree_yRule *W_19 = &yyt->U_1.V_30.Rule;

    W_19->pos = ppos;
    W_19->id = pid;
    W_19->codes = pcodes;
    W_19->expr = pexpr;
  }
  return yyt;
}

Tree_tTree Tree_mrule
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pid, Tree_tTree pcodes, Tree_tTree pexpr)
# else
(ppos, pid, pcodes, pexpr)
Positions_tPosition ppos;
Tree_tTree pid;
Tree_tTree pcodes;
Tree_tTree pexpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_rule]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_rule;
  {
    register Tree_yrule *W_20 = &yyt->U_1.V_31.rule;

    W_20->pos = ppos;
    W_20->id = pid;
    W_20->codes = pcodes;
    W_20->expr = pexpr;
  }
  return yyt;
}

Tree_tTree Tree_mexpr
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_expr]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_expr;
  {
    register Tree_yexpr *W_21 = &yyt->U_1.V_32.expr;

    W_21->pos = ppos;
  }
  return yyt;
}

Tree_tTree Tree_mOption
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pexpr)
# else
(ppos, pexpr)
Positions_tPosition ppos;
Tree_tTree pexpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Option]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Option;
  {
    register Tree_yOption *W_22 = &yyt->U_1.V_33.Option;

    W_22->pos = ppos;
    W_22->expr = pexpr;
  }
  return yyt;
}

Tree_tTree Tree_mTimes
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pexpr)
# else
(ppos, pexpr)
Positions_tPosition ppos;
Tree_tTree pexpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Times]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Times;
  {
    register Tree_yTimes *W_23 = &yyt->U_1.V_34.Times;

    W_23->pos = ppos;
    W_23->expr = pexpr;
  }
  return yyt;
}

Tree_tTree Tree_mPlus
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pexpr)
# else
(ppos, pexpr)
Positions_tPosition ppos;
Tree_tTree pexpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Plus]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Plus;
  {
    register Tree_yPlus *W_24 = &yyt->U_1.V_35.Plus;

    W_24->pos = ppos;
    W_24->expr = pexpr;
  }
  return yyt;
}

Tree_tTree Tree_mList
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pbody, Tree_tTree psep)
# else
(ppos, pbody, psep)
Positions_tPosition ppos;
Tree_tTree pbody;
Tree_tTree psep;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_List]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_List;
  {
    register Tree_yList *W_25 = &yyt->U_1.V_36.List;

    W_25->pos = ppos;
    W_25->body = pbody;
    W_25->sep = psep;
  }
  return yyt;
}

Tree_tTree Tree_mAction
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pcodes)
# else
(ppos, pcodes)
Positions_tPosition ppos;
Tree_tTree pcodes;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Action]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Action;
  {
    register Tree_yAction *W_26 = &yyt->U_1.V_37.Action;

    W_26->pos = ppos;
    W_26->codes = pcodes;
  }
  return yyt;
}

Tree_tTree Tree_mLeaf
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree pid)
# else
(ppos, pid)
Positions_tPosition ppos;
Tree_tTree pid;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Leaf]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Leaf;
  {
    register Tree_yLeaf *W_27 = &yyt->U_1.V_38.Leaf;

    W_27->pos = ppos;
    W_27->id = pid;
  }
  return yyt;
}

Tree_tTree Tree_malternative
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_alternative]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_alternative;
  {
    register Tree_yalternative *W_28 = &yyt->U_1.V_39.alternative;

    W_28->pos = ppos;
  }
  return yyt;
}

Tree_tTree Tree_mAlternative0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Alternative0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Alternative0;
  {
    register Tree_yAlternative0 *W_29 = &yyt->U_1.V_40.Alternative0;

    W_29->pos = ppos;
    W_29->C_0_default = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mAlternative
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree palternative, Tree_tTree pexpr)
# else
(ppos, palternative, pexpr)
Positions_tPosition ppos;
Tree_tTree palternative;
Tree_tTree pexpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Alternative]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Alternative;
  {
    register Tree_yAlternative *W_30 = &yyt->U_1.V_41.Alternative;

    W_30->pos = ppos;
    W_30->alternative = palternative;
    W_30->expr = pexpr;
  }
  return yyt;
}

Tree_tTree Tree_msequence
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_sequence]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_sequence;
  {
    register Tree_ysequence *W_31 = &yyt->U_1.V_42.sequence;

    W_31->pos = ppos;
  }
  return yyt;
}

Tree_tTree Tree_mSequence0
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Sequence0]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Sequence0;
  {
    register Tree_ySequence0 *W_32 = &yyt->U_1.V_43.Sequence0;

    W_32->pos = ppos;
  }
  return yyt;
}

Tree_tTree Tree_mSequence
# ifdef __STDC__
(Positions_tPosition ppos, Tree_tTree psequence, Tree_tTree pexpr)
# else
(ppos, psequence, pexpr)
Positions_tPosition ppos;
Tree_tTree psequence;
Tree_tTree pexpr;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Sequence]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Sequence;
  {
    register Tree_ySequence *W_33 = &yyt->U_1.V_44.Sequence;

    W_33->pos = ppos;
    W_33->sequence = psequence;
    W_33->expr = pexpr;
  }
  return yyt;
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
    case Tree_Sections:;
      yyNext = yyOld->U_1.V_6.Sections.sections;
      yyOld->U_1.V_6.Sections.sections = yyNew;
      break;
    case Tree_Codes:;
      yyNext = yyOld->U_1.V_15.Codes.codes;
      yyOld->U_1.V_15.Codes.codes = yyNew;
      break;
    case Tree_Tokens:;
      yyNext = yyOld->U_1.V_20.Tokens.tokens;
      yyOld->U_1.V_20.Tokens.tokens = yyNew;
      break;
    case Tree_Rules:;
      yyNext = yyOld->U_1.V_29.Rules.rules;
      yyOld->U_1.V_29.Rules.rules = yyNew;
      break;
    case Tree_Alternative:;
      yyNext = yyOld->U_1.V_41.Alternative.alternative;
      yyOld->U_1.V_41.Alternative.alternative = yyNew;
      break;
    case Tree_Sequence:;
      yyNext = yyOld->U_1.V_44.Sequence.sequence;
      yyOld->U_1.V_44.Sequence.sequence = yyNew;
      break;
    default :
      goto EXIT_1;
      break;
    }
    yyNew = yyOld;
    yyOld = yyNext;
  } EXIT_1:;
  switch (yyTail->U_1.V_1.Kind) {
  case Tree_Sections:;
    yyTail->U_1.V_6.Sections.sections = yyOld;
    break;
  case Tree_Codes:;
    yyTail->U_1.V_15.Codes.codes = yyOld;
    break;
  case Tree_Tokens:;
    yyTail->U_1.V_20.Tokens.tokens = yyOld;
    break;
  case Tree_Rules:;
    yyTail->U_1.V_29.Rules.rules = yyOld;
    break;
  case Tree_Alternative:;
    yyTail->U_1.V_41.Alternative.alternative = yyOld;
    break;
  case Tree_Sequence:;
    yyTail->U_1.V_44.Sequence.sequence = yyOld;
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
  Tree_ScannerName = Idents_NoIdent;
  Strings_ArrayToString((STRING)"Parser", 6L, &String);
  Tree_ParserName = Idents_MakeIdent(&String);
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
    Sets__init();
    StringMem__init();
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
    Idents__init();
    Strings__init();
    StringMem__init();
    Positions__init();
    Info__init();
    IO__init();

    yyBlockList = NIL;
    Tree_yyPoolFreePtr = (ADDRESS)NIL;
    Tree_yyPoolMaxPtr = (ADDRESS)NIL;
    Tree_HeapUsed = 0;
    Tree_yyExit = xxExit;
    Tree_yyNodeSize.A[Tree_Grammar] = sizeof(Tree_yGrammar);
    Tree_yyNodeSize.A[Tree_sections] = sizeof(Tree_ysections);
    Tree_yyNodeSize.A[Tree_Sections0] = sizeof(Tree_ySections0);
    Tree_yyNodeSize.A[Tree_Sections] = sizeof(Tree_ySections);
    Tree_yyNodeSize.A[Tree_section] = sizeof(Tree_ysection);
    Tree_yyNodeSize.A[Tree_Export] = sizeof(Tree_yExport);
    Tree_yyNodeSize.A[Tree_Global] = sizeof(Tree_yGlobal);
    Tree_yyNodeSize.A[Tree_Local] = sizeof(Tree_yLocal);
    Tree_yyNodeSize.A[Tree_Begin] = sizeof(Tree_yBegin);
    Tree_yyNodeSize.A[Tree_Close] = sizeof(Tree_yClose);
    Tree_yyNodeSize.A[Tree_codes] = sizeof(Tree_ycodes);
    Tree_yyNodeSize.A[Tree_Codes0] = sizeof(Tree_yCodes0);
    Tree_yyNodeSize.A[Tree_Codes] = sizeof(Tree_yCodes);
    Tree_yyNodeSize.A[Tree_Code] = sizeof(Tree_yCode);
    Tree_yyNodeSize.A[Tree_code] = sizeof(Tree_ycode);
    Tree_yyNodeSize.A[Tree_tokens] = sizeof(Tree_ytokens);
    Tree_yyNodeSize.A[Tree_Tokens0] = sizeof(Tree_yTokens0);
    Tree_yyNodeSize.A[Tree_Tokens] = sizeof(Tree_yTokens);
    Tree_yyNodeSize.A[Tree_Token] = sizeof(Tree_yToken);
    Tree_yyNodeSize.A[Tree_token] = sizeof(Tree_ytoken);
    Tree_yyNodeSize.A[Tree_Id] = sizeof(Tree_yId);
    Tree_yyNodeSize.A[Tree_id] = sizeof(Tree_yid);
    Tree_yyNodeSize.A[Tree_Number] = sizeof(Tree_yNumber);
    Tree_yyNodeSize.A[Tree_number] = sizeof(Tree_ynumber);
    Tree_yyNodeSize.A[Tree_rules] = sizeof(Tree_yrules);
    Tree_yyNodeSize.A[Tree_Rules0] = sizeof(Tree_yRules0);
    Tree_yyNodeSize.A[Tree_Rules] = sizeof(Tree_yRules);
    Tree_yyNodeSize.A[Tree_Rule] = sizeof(Tree_yRule);
    Tree_yyNodeSize.A[Tree_rule] = sizeof(Tree_yrule);
    Tree_yyNodeSize.A[Tree_expr] = sizeof(Tree_yexpr);
    Tree_yyNodeSize.A[Tree_Option] = sizeof(Tree_yOption);
    Tree_yyNodeSize.A[Tree_Times] = sizeof(Tree_yTimes);
    Tree_yyNodeSize.A[Tree_Plus] = sizeof(Tree_yPlus);
    Tree_yyNodeSize.A[Tree_List] = sizeof(Tree_yList);
    Tree_yyNodeSize.A[Tree_Action] = sizeof(Tree_yAction);
    Tree_yyNodeSize.A[Tree_Leaf] = sizeof(Tree_yLeaf);
    Tree_yyNodeSize.A[Tree_alternative] = sizeof(Tree_yalternative);
    Tree_yyNodeSize.A[Tree_Alternative0] = sizeof(Tree_yAlternative0);
    Tree_yyNodeSize.A[Tree_Alternative] = sizeof(Tree_yAlternative);
    Tree_yyNodeSize.A[Tree_sequence] = sizeof(Tree_ysequence);
    Tree_yyNodeSize.A[Tree_Sequence0] = sizeof(Tree_ySequence0);
    Tree_yyNodeSize.A[Tree_Sequence] = sizeof(Tree_ySequence);
    yyMaxSize = 0;
    for (yyi = 1; yyi <= 42; yyi += 1) {
      Tree_yyNodeSize.A[yyi] = (LONGINT)((BITSET)(Tree_yyNodeSize.A[yyi] + (CARDINAL)General_MaxAlign - 1) & General_AlignMasks.A[General_MaxAlign]);
      yyMaxSize = General_Max((LONGINT)Tree_yyNodeSize.A[yyi], (LONGINT)yyMaxSize);
    }
    yyTypeRange.A[Tree_Grammar] = Tree_Grammar;
    yyTypeRange.A[Tree_sections] = Tree_Sections;
    yyTypeRange.A[Tree_Sections0] = Tree_Sections0;
    yyTypeRange.A[Tree_Sections] = Tree_Sections;
    yyTypeRange.A[Tree_section] = Tree_Close;
    yyTypeRange.A[Tree_Export] = Tree_Export;
    yyTypeRange.A[Tree_Global] = Tree_Global;
    yyTypeRange.A[Tree_Local] = Tree_Local;
    yyTypeRange.A[Tree_Begin] = Tree_Begin;
    yyTypeRange.A[Tree_Close] = Tree_Close;
    yyTypeRange.A[Tree_codes] = Tree_Codes;
    yyTypeRange.A[Tree_Codes0] = Tree_Codes0;
    yyTypeRange.A[Tree_Codes] = Tree_Codes;
    yyTypeRange.A[Tree_Code] = Tree_code;
    yyTypeRange.A[Tree_code] = Tree_code;
    yyTypeRange.A[Tree_tokens] = Tree_Tokens;
    yyTypeRange.A[Tree_Tokens0] = Tree_Tokens0;
    yyTypeRange.A[Tree_Tokens] = Tree_Tokens;
    yyTypeRange.A[Tree_Token] = Tree_token;
    yyTypeRange.A[Tree_token] = Tree_token;
    yyTypeRange.A[Tree_Id] = Tree_id;
    yyTypeRange.A[Tree_id] = Tree_id;
    yyTypeRange.A[Tree_Number] = Tree_number;
    yyTypeRange.A[Tree_number] = Tree_number;
    yyTypeRange.A[Tree_rules] = Tree_Rules;
    yyTypeRange.A[Tree_Rules0] = Tree_Rules0;
    yyTypeRange.A[Tree_Rules] = Tree_Rules;
    yyTypeRange.A[Tree_Rule] = Tree_rule;
    yyTypeRange.A[Tree_rule] = Tree_rule;
    yyTypeRange.A[Tree_expr] = Tree_Sequence;
    yyTypeRange.A[Tree_Option] = Tree_Option;
    yyTypeRange.A[Tree_Times] = Tree_Times;
    yyTypeRange.A[Tree_Plus] = Tree_Plus;
    yyTypeRange.A[Tree_List] = Tree_List;
    yyTypeRange.A[Tree_Action] = Tree_Action;
    yyTypeRange.A[Tree_Leaf] = Tree_Leaf;
    yyTypeRange.A[Tree_alternative] = Tree_Alternative;
    yyTypeRange.A[Tree_Alternative0] = Tree_Alternative0;
    yyTypeRange.A[Tree_Alternative] = Tree_Alternative;
    yyTypeRange.A[Tree_sequence] = Tree_Sequence;
    yyTypeRange.A[Tree_Sequence0] = Tree_Sequence0;
    yyTypeRange.A[Tree_Sequence] = Tree_Sequence;
    Tree_BeginTree();
  }
}
