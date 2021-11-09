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
INTEGER Tree_ClassCount;
BITSET Tree_GrammarClass;
SHORTCARD Tree_MaxVisit;
Idents_tIdent Tree_SubUnit, Tree_ViewName, Tree_iPosition, Tree_itPosition, Tree_iInteger, Tree_iMain, Tree_iModule, Tree_itTree, Tree_iNoTree;
Strings_tString Tree_ModuleName;
Sets_tSet Tree_TypeNames, Tree_MaxSet;
Sets_tSet Tree_Options;
IO_tFile Tree_f;
struct Tree_4 Tree_SourceFile;
BITSET Tree_NoCodeAttr, Tree_NoCodeClass;
Tree_tTree Tree_nNoAction, Tree_nNoAttribute, Tree_nNoClass, Tree_nNoDecl, Tree_nNoDesignator, Tree_nNoLayout, Tree_nNoModule, Tree_nNoName, Tree_nNoPrec, Tree_nNoProp;
Tree_tTree Tree_TreeRoot;
LONGCARD Tree_HeapUsed;
ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
struct Tree_57 Tree_yyNodeSize;
PROC Tree_yyExit;

#define Backslash   '\\'
static struct S_2 {
    Tree_tTree A[1000000 + 1];
} *IdentToClassPtr;
static LONGINT IdentToClassSize;
static Idents_tIdent sIdentToClassSize;
static Sets_tSet DummySet;
static Relations_tRelation DummyRelation;
#define yyBlockSize   20480
typedef struct S_1 *yytBlockPtr;
typedef struct S_1 {
    struct S_3 {
        CHAR A[yyBlockSize - 1 + 1];
    } yyBlock;
    yytBlockPtr yySuccessor;
} yytBlock;
static yytBlockPtr yyBlockList;
static SHORTCARD yyMaxSize, yyi;
static struct S_4 {
    SHORTCARD A[138 + 1];
} yyTypeRange;
typedef Tree_tTree *yyPtrtTree;
static IO_tFile yyf;
static SHORTCARD yyLabel;
static SHORTCARD yyKind;
static CHAR yyc;
static Strings_tString yys;
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
static void yyyWriteNodeAg ARGS((Tree_tTree yyt));
static void yyyWriteNodePrec ARGS((Tree_tTree yyt));
static void yyyWriteNodeLeftAssoc ARGS((Tree_tTree yyt));
static void yyyWriteNodeRightAssoc ARGS((Tree_tTree yyt));
static void yyyWriteNodeNonAssoc ARGS((Tree_tTree yyt));
static void yyyWriteNodeAction ARGS((Tree_tTree yyt));
static void yyyWriteNodeAssign ARGS((Tree_tTree yyt));
static void yyyWriteNodeCopy ARGS((Tree_tTree yyt));
static void yyyWriteNodeTargetCode ARGS((Tree_tTree yyt));
static void yyyWriteNodeOrder ARGS((Tree_tTree yyt));
static void yyyWriteNodeCheck ARGS((Tree_tTree yyt));
static void yyyWriteNodeModule ARGS((Tree_tTree yyt));
static void yyyWriteNodeProp ARGS((Tree_tTree yyt));
static void yyyWriteNodeSelect ARGS((Tree_tTree yyt));
static void yyyWriteNodeDecl ARGS((Tree_tTree yyt));
#define yyNil   ((CHAR)'\374')
#define yyNoLabel   ((CHAR)'\375')
#define yyLabelDef   ((CHAR)'\376')
#define yyLabelUse   ((CHAR)'\377')
#define yyyWrite   1
#define yyyRead   2
#define yyyQuit   3
static struct S_7 {
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

void Tree_BeginTree2
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString Word;

  {
    register Tree_yAg *W_1 = &Tree_TreeRoot->U_1.V_26.Ag;

    if (W_1->ParserName == Idents_NoIdent) {
      Strings_ArrayToString((STRING)"Parser", 6L, &Word);
      W_1->ParserName = Idents_MakeIdent(&Word);
    }
    if (W_1->TreeName == Idents_NoIdent) {
      Strings_ArrayToString((STRING)"Tree", 4L, &Word);
      W_1->TreeName = Idents_MakeIdent(&Word);
    }
    if (W_1->EvalName == Idents_NoIdent) {
      Strings_ArrayToString((STRING)"Eval", 4L, &Word);
      W_1->EvalName = Idents_MakeIdent(&Word);
    }
    if (Tree_ViewName == Idents_NoIdent) {
      Tree_ViewName = W_1->TreeName;
    }
    Idents_GetString(W_1->TreeName, &Tree_ModuleName);
    Tree_iMain = W_1->TreeName;
  }
  Strings_ArrayToString((STRING)"t", 1L, &Word);
  Strings_Concatenate(&Word, &Tree_ModuleName);
  Tree_itTree = Idents_MakeIdent(&Word);
  Strings_ArrayToString((STRING)"No", 2L, &Word);
  Strings_Concatenate(&Word, &Tree_ModuleName);
  Tree_iNoTree = Idents_MakeIdent(&Word);
  Strings_ArrayToString((STRING)"Position", 8L, &Word);
  Tree_iPosition = Idents_MakeIdent(&Word);
  Strings_ArrayToString((STRING)"tPosition", 9L, &Word);
  Tree_itPosition = Idents_MakeIdent(&Word);
  if (Tree_SubUnit == Idents_NoIdent) {
    Tree_iModule = Tree_iMain;
  } else {
    Tree_iModule = Tree_SubUnit;
    Sets_Include(&Tree_Options, ORD('<'));
  }
}

Tree_tTree Tree_IdentifyModule
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent Ident)
# else
(t, Ident)
Tree_tTree t;
Idents_tIdent Ident;
# endif
{
  Tree_tTree module;

  if (t->U_1.V_1.Kind == Tree_Module) {
    if (t->U_1.V_43.Module.Name == Ident) {
      return t;
    }
    return Tree_IdentifyModule(t->U_1.V_43.Module.Next, Ident);
  } else {
    return Tree_NoTree;
  }
}

void Tree_WriteInstance
# ifdef __STDC__
(Tree_tInstance i)
# else
(i)
Tree_tInstance i;
# endif
{
  {
    register Tree_tInstance *W_2 = &i;

    IO_WriteS((System_tFile)IO_StdOutput, (STRING)" ", 1L);
    Tree_WriteName(i);
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"  ", 2L);
    IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)W_2->Attribute->U_1.V_9.Child.Partition, 0L);
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)" ", 1L);
    Tree_WriteAttrProperties((System_tFile)IO_StdOutput, W_2->Properties | W_2->Attribute->U_1.V_9.Child.Properties);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
}

void Tree_WriteName
# ifdef __STDC__
(Tree_tInstance i)
# else
(i)
Tree_tInstance i;
# endif
{
  {
    register Tree_tInstance *W_3 = &i;

    if (W_3->Selector != Tree_NoTree && IN(Tree_Right, W_3->Properties)) {
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_3->Selector->U_1.V_9.Child.Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)":", 1L);
    }
    if (W_3->Attribute != Tree_NoTree) {
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_3->Attribute->U_1.V_9.Child.Name);
    }
  }
}

void Tree_WriteAttrProperties
# ifdef __STDC__
(IO_tFile f, Tree_tAttrProperties Properties)
# else
(f, Properties)
IO_tFile f;
Tree_tAttrProperties Properties;
# endif
{
  if (IN(Tree_Virtual, Properties)) {
    IO_WriteS(f, (STRING)"Virtual ", 8L);
  }
  if (IN(Tree_Computed, Properties)) {
    IO_WriteS(f, (STRING)"Computed ", 9L);
  }
  if (IN(Tree_Reverse, Properties)) {
    IO_WriteS(f, (STRING)"Reverse ", 8L);
  }
  if (IN(Tree_Write, Properties)) {
    IO_WriteS(f, (STRING)"Write ", 6L);
  }
  if (IN(Tree_Read, Properties)) {
    IO_WriteS(f, (STRING)"Read ", 5L);
  }
  if (IN(Tree_Inherited, Properties)) {
    IO_WriteS(f, (STRING)"Inherited ", 10L);
  }
  if (IN(Tree_Synthesized, Properties)) {
    IO_WriteS(f, (STRING)"Synthesized ", 12L);
  }
  if (IN(Tree_Input, Properties)) {
    IO_WriteS(f, (STRING)"Input ", 6L);
  }
  if (IN(Tree_Output, Properties)) {
    IO_WriteS(f, (STRING)"Output ", 7L);
  }
  if (IN(Tree_Tree, Properties)) {
    IO_WriteS(f, (STRING)"Tree ", 5L);
  }
  if (IN(Tree_Parameter, Properties)) {
    IO_WriteS(f, (STRING)"Parameter ", 10L);
  }
  if (IN(Tree_Stack, Properties)) {
    IO_WriteS(f, (STRING)"Stack ", 6L);
  }
  if (IN(Tree_Variable, Properties)) {
    IO_WriteS(f, (STRING)"Variable ", 9L);
  }
  if (IN(Tree_Demand, Properties)) {
    IO_WriteS(f, (STRING)"Demand ", 7L);
  }
  if (IN(Tree_Funct, Properties)) {
    IO_WriteS(f, (STRING)"Function ", 9L);
  }
  if (IN(Tree_Ignore, Properties)) {
    IO_WriteS(f, (STRING)"Ignore ", 7L);
  }
  if (IN(Tree_Thread, Properties)) {
    IO_WriteS(f, (STRING)"Thread ", 7L);
  }
  if (IN(Tree_Test, Properties)) {
    IO_WriteS(f, (STRING)"Test ", 5L);
  }
  if (IN(Tree_Left, Properties)) {
    IO_WriteS(f, (STRING)"Left ", 5L);
  }
  if (IN(Tree_Right, Properties)) {
    IO_WriteS(f, (STRING)"Right ", 6L);
  }
  if (IN(Tree_CopyDef, Properties)) {
    IO_WriteS(f, (STRING)"CopyDef ", 8L);
  }
  if (IN(Tree_CopyUse, Properties)) {
    IO_WriteS(f, (STRING)"CopyUse ", 8L);
  }
  if (IN(Tree_NonBaseComp, Properties)) {
    IO_WriteS(f, (STRING)"NonBaseComp ", 12L);
  }
  if (IN(Tree_MultInhComp, Properties)) {
    IO_WriteS(f, (STRING)"MultInhComp ", 12L);
  }
  if (IN(Tree_First, Properties)) {
    IO_WriteS(f, (STRING)"First ", 6L);
  }
  if (IN(Tree_Dummy, Properties)) {
    IO_WriteS(f, (STRING)"Dummy ", 6L);
  }
  if (IN(Tree_Def, Properties)) {
    IO_WriteS(f, (STRING)"Def ", 4L);
  }
  if (IN(Tree_Use, Properties)) {
    IO_WriteS(f, (STRING)"Use ", 4L);
  }
  if (IN(Tree_ChildUse, Properties)) {
    IO_WriteS(f, (STRING)"ChildUse ", 9L);
  }
  if (IN(Tree_ParentUse, Properties)) {
    IO_WriteS(f, (STRING)"ParentUse ", 10L);
  }
  if (IN(Tree_Generated, Properties)) {
    IO_WriteS(f, (STRING)"Generated ", 10L);
  }
}

void Tree_WriteClassProperties
# ifdef __STDC__
(IO_tFile f, Tree_tClassProperties Properties)
# else
(f, Properties)
IO_tFile f;
Tree_tClassProperties Properties;
# endif
{
  if (IN(Tree_Top, Properties)) {
    IO_WriteS(f, (STRING)"Top ", 4L);
  }
  if (IN(Tree_Intermediate, Properties)) {
    IO_WriteS(f, (STRING)"Intermediate ", 13L);
  }
  if (IN(Tree_Low, Properties)) {
    IO_WriteS(f, (STRING)"Low ", 4L);
  }
  if (IN(Tree_Referenced, Properties)) {
    IO_WriteS(f, (STRING)"Referenced ", 11L);
  }
  if (IN(Tree_Reachable, Properties)) {
    IO_WriteS(f, (STRING)"Reachable ", 10L);
  }
  if (IN(Tree_Nonterminal, Properties)) {
    IO_WriteS(f, (STRING)"Nonterminal ", 12L);
  }
  if (IN(Tree_Terminal, Properties)) {
    IO_WriteS(f, (STRING)"Terminal ", 9L);
  }
  if (IN(Tree_Explicit, Properties)) {
    IO_WriteS(f, (STRING)"Explicit ", 9L);
  }
  if (IN(Tree_Implicit, Properties)) {
    IO_WriteS(f, (STRING)"Implicit ", 9L);
  }
  if (IN(Tree_Trace, Properties)) {
    IO_WriteS(f, (STRING)"Trace ", 6L);
  }
  if (IN(Tree_String, Properties)) {
    IO_WriteS(f, (STRING)"String ", 7L);
  }
  if (IN(Tree_HasSelector, Properties)) {
    IO_WriteS(f, (STRING)"HasSelector ", 12L);
  }
  if (IN(Tree_HasChildren, Properties)) {
    IO_WriteS(f, (STRING)"HasChildren ", 12L);
  }
  if (IN(Tree_HasAttributes, Properties)) {
    IO_WriteS(f, (STRING)"HasAttributes ", 14L);
  }
  if (IN(Tree_HasActions, Properties)) {
    IO_WriteS(f, (STRING)"HasActions ", 11L);
  }
  if (IN(Tree_Abstract, Properties)) {
    IO_WriteS(f, (STRING)"Abstract ", 9L);
  }
  if (IN(Tree_Mark, Properties)) {
    IO_WriteS(f, (STRING)"Mark ", 5L);
  }
  if (IN(Tree_HasOutput, Properties)) {
    IO_WriteS(f, (STRING)"HasOutput ", 10L);
  }
}

void Tree_WriteDependencies
# ifdef __STDC__
(Tree_tTree t, Relations_tRelation r, Sets_tSet s)
# else
(t, r, s)
Tree_tTree t;
Relations_tRelation r;
Sets_tSet s;
# endif
{
  SHORTCARD i, j, k, count;

  if (t == Tree_NoTree || VAL(SHORTCARD, r.Max1) != t->U_1.V_5.Class.InstCount) {
    return;
  }
  Idents_WriteIdent((System_tFile)IO_StdOutput, t->U_1.V_5.Class.Name);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"      ", 6L);
  Tree_WriteClassProperties((System_tFile)IO_StdOutput, t->U_1.V_5.Class.Properties);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteNl((System_tFile)IO_StdOutput);
  {
    SHORTCARD B_5 = 1, B_6 = t->U_1.V_5.Class.InstCount;

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        if (Sets_IsElement((Sets_tElement)i, &s) && !IN(Tree_Dummy, t->U_1.V_5.Class.Instance->A[i - 1].Properties)) {
          Tree_WriteName(t->U_1.V_5.Class.Instance->A[i - 1]);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"     :", 6L);
          count = 0;
          k = 0;
          {
            SHORTCARD B_7 = 1, B_8 = t->U_1.V_5.Class.InstCount;

            if (B_7 <= B_8)
              for (j = B_7;; j += 1) {
                if (Sets_IsElement((Sets_tElement)j, &s) && Relations_IsRelated((LONGINT)i, (LONGINT)j, r)) {
                  if (count == 5) {
                    IO_WriteNl((System_tFile)IO_StdOutput);
                    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"      ", 6L);
                    count = 0;
                  }
                  IO_WriteS((System_tFile)IO_StdOutput, (STRING)" ", 1L);
                  Tree_WriteName(t->U_1.V_5.Class.Instance->A[j - 1]);
                  INC(count);
                  INC(k);
                }
                if (j >= B_8) break;
              }
          }
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)" (", 2L);
          IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)k, 0L);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)")", 1L);
          IO_WriteNl((System_tFile)IO_StdOutput);
        }
        if (i >= B_6) break;
      }
  }
  IO_WriteNl((System_tFile)IO_StdOutput);
}

void Tree_WriteCyclics
# ifdef __STDC__
(Tree_tTree t, Sets_tSet s)
# else
(t, s)
Tree_tTree t;
Sets_tSet s;
# endif
{
  SHORTCARD i, count;

  count = 0;
  {
    SHORTCARD B_9 = 1, B_10 = t->U_1.V_5.Class.InstCount;

    if (B_9 <= B_10)
      for (i = B_9;; i += 1) {
        if (Sets_IsElement((Sets_tElement)i, &s)) {
          if (count == 5) {
            IO_WriteNl((System_tFile)IO_StdOutput);
            count = 0;
          }
          Tree_WriteName(t->U_1.V_5.Class.Instance->A[i - 1]);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)" ", 1L);
          INC(count);
        }
        if (i >= B_10) break;
      }
  }
  IO_WriteNl((System_tFile)IO_StdOutput);
}

void Tree_WriteClass
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  SHORTCARD i;

  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_4 = &t->U_1.V_5.Class;

      Idents_WriteIdent((System_tFile)IO_StdOutput, W_4->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)" =", 2L);
      IO_WriteNl((System_tFile)IO_StdOutput);
      Tree_ForallAttributes(t, (Tree_ProcOfT)Tree_WriteClass);
      IO_WriteNl((System_tFile)IO_StdOutput);
      {
        SHORTCARD B_11 = 1, B_12 = W_4->InstCount;

        if (B_11 <= B_12)
          for (i = B_11;; i += 1) {
            {
              register Tree_tInstance *W_5 = &W_4->Instance->A[i - 1];

              if (W_5->Action != ADR(W_5->Action)) {
                if (IN(Tree_Test, W_5->Properties)) {
                  Tree_WriteName(W_4->Instance->A[i - 1]);
                  IO_WriteS((System_tFile)IO_StdOutput, (STRING)":", 1L);
                }
                IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   {", 4L);
                Tree_WriteClass(W_5->Action);
                IO_WriteS((System_tFile)IO_StdOutput, (STRING)"}", 1L);
                IO_WriteNl((System_tFile)IO_StdOutput);
              }
            }
            if (i >= B_12) break;
          }
      }
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)".", 1L);
      IO_WriteNl((System_tFile)IO_StdOutput);
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_6 = &t->U_1.V_9.Child;

      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   ", 3L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_6->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)": ", 2L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_6->Type);
      IO_WriteNl((System_tFile)IO_StdOutput);
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_7 = &t->U_1.V_10.Attribute;

      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   [", 4L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_7->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)": ", 2L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_7->Type);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"]", 1L);
      IO_WriteNl((System_tFile)IO_StdOutput);
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_8 = &t->U_1.V_36.Assign;

      Tree_WriteClass(W_8->Results);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)":=", 2L);
      Tree_WriteClass(W_8->Arguments);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)";", 1L);
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_9 = &t->U_1.V_37.Copy;

      Tree_WriteClass(W_9->Results);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)" :- ", 4L);
      Tree_WriteClass(W_9->Arguments);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)";", 1L);
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_10 = &t->U_1.V_38.TargetCode;

      if (W_10->Results->U_1.V_1.Kind != Tree_NoDesignator) {
        Tree_WriteClass(W_10->Results);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)":= {", 4L);
        Tree_WriteClass(W_10->Code);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"};", 2L);
      }
    }
    break;
  case Tree_Order:;
    {
      register Tree_yOrder *W_11 = &t->U_1.V_39.Order;

      Tree_WriteClass(W_11->Results);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)" AFTER ", 7L);
      Tree_WriteClass(W_11->Arguments);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)";", 1L);
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_12 = &t->U_1.V_40.Check;

      if (W_12->Condition != Tree_NoTree) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"CHECK ", 6L);
        Tree_WriteClass(W_12->Condition);
      }
      if (W_12->Statement != Tree_NoTree) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)" ==> { ", 7L);
        Tree_WriteClass(W_12->Statement);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"}", 1L);
      }
      Tree_WriteClass(W_12->Actions);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)";", 1L);
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_13 = &t->U_1.V_15.Designator;

      Idents_WriteIdent((System_tFile)IO_StdOutput, W_13->Selector);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)":", 1L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_13->Attribute);
      Tree_WriteClass(W_13->Next);
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_14 = &t->U_1.V_16.Ident;

      Idents_WriteIdent((System_tFile)IO_StdOutput, W_14->Attribute);
      Tree_WriteClass(W_14->Next);
    }
    break;
  case Tree_Remote:;
    {
      register Tree_yRemote *W_15 = &t->U_1.V_17.Remote;

      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"REMOTE ", 7L);
      Tree_WriteClass(W_15->Designators);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"==>", 3L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_15->Type);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)":", 1L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_15->Attribute);
      Tree_WriteClass(W_15->Next);
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_16 = &t->U_1.V_18.Any;

      StringMem_WriteString((System_tFile)IO_StdOutput, W_16->Code);
      Tree_WriteClass(W_16->Next);
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_17 = &t->U_1.V_19.Anys;

      Tree_WriteClass(W_17->Layouts);
      Tree_WriteClass(W_17->Next);
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_18 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString((System_tFile)IO_StdOutput, W_18->Code);
      Tree_WriteClass(W_18->Next);
    }
    break;
  default :
    break;
  }
}

BOOLEAN Tree_HasItem
# ifdef __STDC__
(Tree_tTree t, SHORTCARD Item)
# else
(t, Item)
Tree_tTree t;
SHORTCARD Item;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    return Tree_HasItem(t->U_1.V_5.Class.BaseClass, Item) || Tree_HasItem(t->U_1.V_5.Class.Attributes, Item);
    break;
  case Tree_NoClass:;
  case Tree_NoAttribute:;
    return FALSE;
    break;
  default :
    return t->U_1.V_8.AttrOrAction.Item == Item || Tree_HasItem(t->U_1.V_8.AttrOrAction.Next, Item);
    break;
  }
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
(Idents_tIdent pName, Tree_tClassProperties pProperties, Tree_tTree pAttributes, Tree_tTree pExtensions, Tree_tTree pNext, Idents_tIdent pSelector, Positions_tPosition pPos, SHORTCARD pCode, Idents_tIdent pPrec, Tree_tTree pNames)
# else
(pName, pProperties, pAttributes, pExtensions, pNext, pSelector, pPos, pCode, pPrec, pNames)
Idents_tIdent pName;
Tree_tClassProperties pProperties;
Tree_tTree pAttributes;
Tree_tTree pExtensions;
Tree_tTree pNext;
Idents_tIdent pSelector;
Positions_tPosition pPos;
SHORTCARD pCode;
Idents_tIdent pPrec;
Tree_tTree pNames;
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
    register Tree_yClass *W_19 = &yyt->U_1.V_5.Class;

    W_19->Name = pName;
    W_19->Properties = pProperties;
    W_19->Attributes = pAttributes;
    W_19->Extensions = pExtensions;
    W_19->Next = pNext;
    W_19->BaseClass = Tree_NoTree;
    W_19->Selector = pSelector;
    W_19->Pos = pPos;
    W_19->Code = pCode;
    W_19->Prec = pPrec;
    W_19->Names = pNames;
    W_19->DP = DummyRelation;
    W_19->SNC = DummyRelation;
    W_19->DNC = DummyRelation;
    W_19->OAG = DummyRelation;
    W_19->Part = DummyRelation;
    W_19->Users = DummySet;
    W_19->Generated = 0;
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
    register Tree_yAttrOrAction *W_20 = &yyt->U_1.V_8.AttrOrAction;

    W_20->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mChild
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties, Positions_tPosition pPos)
# else
(pNext, pName, pType, pProperties, pPos)
Tree_tTree pNext;
Idents_tIdent pName;
Idents_tIdent pType;
Tree_tAttrProperties pProperties;
Positions_tPosition pPos;
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
    register Tree_yChild *W_21 = &yyt->U_1.V_9.Child;

    W_21->Next = pNext;
    W_21->Name = pName;
    W_21->Type = pType;
    W_21->Properties = pProperties;
    W_21->Pos = pPos;
    W_21->Partition = 9999;
    W_21->Usage = 0X0L;
  }
  return yyt;
}

Tree_tTree Tree_mAttribute
# ifdef __STDC__
(Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties, Positions_tPosition pPos)
# else
(pNext, pName, pType, pProperties, pPos)
Tree_tTree pNext;
Idents_tIdent pName;
Idents_tIdent pType;
Tree_tAttrProperties pProperties;
Positions_tPosition pPos;
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
    register Tree_yAttribute *W_22 = &yyt->U_1.V_10.Attribute;

    W_22->Next = pNext;
    W_22->Name = pName;
    W_22->Type = pType;
    W_22->Properties = pProperties;
    W_22->Pos = pPos;
    W_22->Partition = 9999;
    W_22->Usage = 0X0L;
  }
  return yyt;
}

Tree_tTree Tree_mActionPart
# ifdef __STDC__
(Tree_tTree pNext, Tree_tTree pActions)
# else
(pNext, pActions)
Tree_tTree pNext;
Tree_tTree pActions;
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
    register Tree_yActionPart *W_23 = &yyt->U_1.V_11.ActionPart;

    W_23->Next = pNext;
    W_23->Actions = pActions;
    W_23->Properties = 0X0L;
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
    register Tree_yCodes *W_24 = &yyt->U_1.V_12.Codes;

    W_24->Export = pExport;
    W_24->Import = pImport;
    W_24->Global = pGlobal;
    W_24->SpecWith = pSpecWith;
    W_24->BodyWith = pBodyWith;
    W_24->Local = pLocal;
    W_24->Begin = pBegin;
    W_24->Close = pClose;
    W_24->ExportLine = pExportLine;
    W_24->ImportLine = pImportLine;
    W_24->GlobalLine = pGlobalLine;
    W_24->SpecWithLine = pSpecWithLine;
    W_24->BodyWithLine = pBodyWithLine;
    W_24->LocalLine = pLocalLine;
    W_24->BeginLine = pBeginLine;
    W_24->CloseLine = pCloseLine;
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
    register Tree_yDesignator *W_25 = &yyt->U_1.V_15.Designator;

    W_25->Selector = pSelector;
    W_25->Attribute = pAttribute;
    W_25->Pos = pPos;
    W_25->AttributePos = pAttributePos;
    W_25->Next = pNext;
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
    register Tree_yIdent *W_26 = &yyt->U_1.V_16.Ident;

    W_26->Attribute = pAttribute;
    W_26->Pos = pPos;
    W_26->Next = pNext;
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
    register Tree_yRemote *W_27 = &yyt->U_1.V_17.Remote;

    W_27->Designators = pDesignators;
    W_27->Type = pType;
    W_27->Attribute = pAttribute;
    W_27->Pos = pPos;
    W_27->Next = pNext;
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
    register Tree_yAny *W_28 = &yyt->U_1.V_18.Any;

    W_28->Code = pCode;
    W_28->Next = pNext;
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
    register Tree_yAnys *W_29 = &yyt->U_1.V_19.Anys;

    W_29->Layouts = pLayouts;
    W_29->Next = pNext;
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
    register Tree_yLayoutAny *W_30 = &yyt->U_1.V_22.LayoutAny;

    W_30->Code = pCode;
    W_30->Next = pNext;
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
    register Tree_yName *W_31 = &yyt->U_1.V_25.Name;

    W_31->Name = pName;
    W_31->Pos = pPos;
    W_31->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mAg
# ifdef __STDC__
(Idents_tIdent pName, Idents_tIdent pScannerName, Idents_tIdent pParserName, Tree_tTree pParserCodes, Idents_tIdent pTreeName, Tree_tTree pTreeCodes, Idents_tIdent pEvalName, Tree_tTree pEvalCodes, Tree_tTree pPrecs, Tree_tTree pProps, Tree_tTree pDecls, Tree_tTree pClasses, Tree_tTree pModules)
# else
(pName, pScannerName, pParserName, pParserCodes, pTreeName, pTreeCodes, pEvalName, pEvalCodes, pPrecs, pProps, pDecls, pClasses, pModules)
Idents_tIdent pName;
Idents_tIdent pScannerName;
Idents_tIdent pParserName;
Tree_tTree pParserCodes;
Idents_tIdent pTreeName;
Tree_tTree pTreeCodes;
Idents_tIdent pEvalName;
Tree_tTree pEvalCodes;
Tree_tTree pPrecs;
Tree_tTree pProps;
Tree_tTree pDecls;
Tree_tTree pClasses;
Tree_tTree pModules;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Ag]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Ag;
  {
    register Tree_yAg *W_32 = &yyt->U_1.V_26.Ag;

    W_32->Name = pName;
    W_32->ScannerName = pScannerName;
    W_32->ParserName = pParserName;
    W_32->ParserCodes = pParserCodes;
    W_32->TreeName = pTreeName;
    W_32->TreeCodes = pTreeCodes;
    W_32->EvalName = pEvalName;
    W_32->EvalCodes = pEvalCodes;
    W_32->Precs = pPrecs;
    W_32->Props = pProps;
    W_32->Decls = pDecls;
    W_32->Classes = pClasses;
    W_32->Modules = pModules;
    W_32->Properties = 0X0L;
  }
  return yyt;
}

Tree_tTree Tree_mPrecs
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Precs]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Precs;
  return yyt;
}

Tree_tTree Tree_mNoPrec
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoPrec]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoPrec;
  return yyt;
}

Tree_tTree Tree_mPrec
# ifdef __STDC__
(Tree_tTree pNames, Tree_tTree pNext)
# else
(pNames, pNext)
Tree_tTree pNames;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Prec]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Prec;
  {
    register Tree_yPrec *W_33 = &yyt->U_1.V_29.Prec;

    W_33->Names = pNames;
    W_33->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mLeftAssoc
# ifdef __STDC__
(Tree_tTree pNames, Tree_tTree pNext)
# else
(pNames, pNext)
Tree_tTree pNames;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_LeftAssoc]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_LeftAssoc;
  {
    register Tree_yLeftAssoc *W_34 = &yyt->U_1.V_30.LeftAssoc;

    W_34->Names = pNames;
    W_34->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mRightAssoc
# ifdef __STDC__
(Tree_tTree pNames, Tree_tTree pNext)
# else
(pNames, pNext)
Tree_tTree pNames;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_RightAssoc]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_RightAssoc;
  {
    register Tree_yRightAssoc *W_35 = &yyt->U_1.V_31.RightAssoc;

    W_35->Names = pNames;
    W_35->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mNonAssoc
# ifdef __STDC__
(Tree_tTree pNames, Tree_tTree pNext)
# else
(pNames, pNext)
Tree_tTree pNames;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NonAssoc]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NonAssoc;
  {
    register Tree_yNonAssoc *W_36 = &yyt->U_1.V_32.NonAssoc;

    W_36->Names = pNames;
    W_36->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mActions
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Actions]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Actions;
  return yyt;
}

Tree_tTree Tree_mNoAction
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoAction]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoAction;
  return yyt;
}

Tree_tTree Tree_mAction
# ifdef __STDC__
(Tree_tTree pNext, Positions_tPosition pPos)
# else
(pNext, pPos)
Tree_tTree pNext;
Positions_tPosition pPos;
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
    register Tree_yAction *W_37 = &yyt->U_1.V_35.Action;

    W_37->Next = pNext;
    W_37->Pos = pPos;
  }
  return yyt;
}

Tree_tTree Tree_mAssign
# ifdef __STDC__
(Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pArguments)
# else
(pNext, pPos, pResults, pArguments)
Tree_tTree pNext;
Positions_tPosition pPos;
Tree_tTree pResults;
Tree_tTree pArguments;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Assign]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Assign;
  {
    register Tree_yAssign *W_38 = &yyt->U_1.V_36.Assign;

    W_38->Next = pNext;
    W_38->Pos = pPos;
    W_38->Results = pResults;
    W_38->Arguments = pArguments;
  }
  return yyt;
}

Tree_tTree Tree_mCopy
# ifdef __STDC__
(Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pArguments)
# else
(pNext, pPos, pResults, pArguments)
Tree_tTree pNext;
Positions_tPosition pPos;
Tree_tTree pResults;
Tree_tTree pArguments;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Copy]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Copy;
  {
    register Tree_yCopy *W_39 = &yyt->U_1.V_37.Copy;

    W_39->Next = pNext;
    W_39->Pos = pPos;
    W_39->Results = pResults;
    W_39->Arguments = pArguments;
  }
  return yyt;
}

Tree_tTree Tree_mTargetCode
# ifdef __STDC__
(Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pCode)
# else
(pNext, pPos, pResults, pCode)
Tree_tTree pNext;
Positions_tPosition pPos;
Tree_tTree pResults;
Tree_tTree pCode;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TargetCode]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_TargetCode;
  {
    register Tree_yTargetCode *W_40 = &yyt->U_1.V_38.TargetCode;

    W_40->Next = pNext;
    W_40->Pos = pPos;
    W_40->Results = pResults;
    W_40->Code = pCode;
  }
  return yyt;
}

Tree_tTree Tree_mOrder
# ifdef __STDC__
(Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pArguments)
# else
(pNext, pPos, pResults, pArguments)
Tree_tTree pNext;
Positions_tPosition pPos;
Tree_tTree pResults;
Tree_tTree pArguments;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Order]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Order;
  {
    register Tree_yOrder *W_41 = &yyt->U_1.V_39.Order;

    W_41->Next = pNext;
    W_41->Pos = pPos;
    W_41->Results = pResults;
    W_41->Arguments = pArguments;
  }
  return yyt;
}

Tree_tTree Tree_mCheck
# ifdef __STDC__
(Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pCondition, Tree_tTree pStatement, Tree_tTree pActions)
# else
(pNext, pPos, pCondition, pStatement, pActions)
Tree_tTree pNext;
Positions_tPosition pPos;
Tree_tTree pCondition;
Tree_tTree pStatement;
Tree_tTree pActions;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Check]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Check;
  {
    register Tree_yCheck *W_42 = &yyt->U_1.V_40.Check;

    W_42->Next = pNext;
    W_42->Pos = pPos;
    W_42->Condition = pCondition;
    W_42->Statement = pStatement;
    W_42->Actions = pActions;
    W_42->Results = Tree_NoTree;
  }
  return yyt;
}

Tree_tTree Tree_mModules
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Modules]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Modules;
  return yyt;
}

Tree_tTree Tree_mNoModule
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoModule]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoModule;
  return yyt;
}

Tree_tTree Tree_mModule
# ifdef __STDC__
(Idents_tIdent pName, Tree_tTree pParserCodes, Tree_tTree pTreeCodes, Tree_tTree pEvalCodes, Tree_tTree pProps, Tree_tTree pDecls, Tree_tTree pClasses, Tree_tTree pNext)
# else
(pName, pParserCodes, pTreeCodes, pEvalCodes, pProps, pDecls, pClasses, pNext)
Idents_tIdent pName;
Tree_tTree pParserCodes;
Tree_tTree pTreeCodes;
Tree_tTree pEvalCodes;
Tree_tTree pProps;
Tree_tTree pDecls;
Tree_tTree pClasses;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Module]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Module;
  {
    register Tree_yModule *W_43 = &yyt->U_1.V_43.Module;

    W_43->Name = pName;
    W_43->ParserCodes = pParserCodes;
    W_43->TreeCodes = pTreeCodes;
    W_43->EvalCodes = pEvalCodes;
    W_43->Props = pProps;
    W_43->Decls = pDecls;
    W_43->Classes = pClasses;
    W_43->Next = pNext;
    W_43->Properties = 0X0L;
  }
  return yyt;
}

Tree_tTree Tree_mProps
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Props]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Props;
  return yyt;
}

Tree_tTree Tree_mNoProp
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoProp]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoProp;
  return yyt;
}

Tree_tTree Tree_mProp
# ifdef __STDC__
(BITSET pProperties, Tree_tTree pNames, Tree_tTree pNext)
# else
(pProperties, pNames, pNext)
BITSET pProperties;
Tree_tTree pNames;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Prop]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Prop;
  {
    register Tree_yProp *W_44 = &yyt->U_1.V_46.Prop;

    W_44->Properties = pProperties;
    W_44->Names = pNames;
    W_44->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mSelect
# ifdef __STDC__
(Tree_tTree pNames, Tree_tTree pNext)
# else
(pNames, pNext)
Tree_tTree pNames;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Select]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Select;
  {
    register Tree_ySelect *W_45 = &yyt->U_1.V_47.Select;

    W_45->Names = pNames;
    W_45->Next = pNext;
  }
  return yyt;
}

Tree_tTree Tree_mDecls
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decls]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Decls;
  return yyt;
}

Tree_tTree Tree_mNoDecl
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
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoDecl]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_NoDecl;
  return yyt;
}

Tree_tTree Tree_mDecl
# ifdef __STDC__
(Tree_tTree pNames, Tree_tTree pAttributes, Tree_tClassProperties pProperties, Tree_tTree pNext)
# else
(pNames, pAttributes, pProperties, pNext)
Tree_tTree pNames;
Tree_tTree pAttributes;
Tree_tClassProperties pProperties;
Tree_tTree pNext;
# endif
{
  LONGINT yyByteCount;
  Tree_tTree yyt;

  yyt = (Tree_tTree)Tree_yyPoolFreePtr;
  if ((ADDRESS)yyt >= Tree_yyPoolMaxPtr) {
    yyt = Tree_yyAlloc();
  }
  INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decl]);
  yyt->U_1.V_2.yyHead.yyMark = 0;
  yyt->U_1.V_1.Kind = Tree_Decl;
  {
    register Tree_yDecl *W_46 = &yyt->U_1.V_50.Decl;

    W_46->Names = pNames;
    W_46->Attributes = pAttributes;
    W_46->Properties = pProperties;
    W_46->Next = pNext;
  }
  return yyt;
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
    LONGINT B_13 = 0, B_14 = (INTEGER)(O_2 - 1);

    if (B_13 <= B_14)
      for (yyi = B_13;; yyi += 1) {
        IO_WriteN(yyf, ORD((CHAR)yyx[yyi]), 2L, 16L);
        IO_WriteC(yyf, ' ');
        if (yyi >= B_14) break;
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
  Tree_WriteClassProperties(yyf, yyt->U_1.V_5.Class.Properties);
  yyWriteNl();
  yyWriteSelector((STRING)"Attributes", 10L);
  yyWriteAdr(yyt->U_1.V_5.Class.Attributes);
  yyWriteSelector((STRING)"Extensions", 10L);
  yyWriteAdr(yyt->U_1.V_5.Class.Extensions);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_5.Class.Next);
  yyWriteSelector((STRING)"BaseClass", 9L);
  yyWriteAdr(yyt->U_1.V_5.Class.BaseClass);
  yyWriteSelector((STRING)"Selector", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_5.Class.Selector);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_5.Class.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"Code", 4L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.Code, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Prec", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_5.Class.Prec);
  yyWriteNl();
  yyWriteSelector((STRING)"Names", 5L);
  yyWriteAdr(yyt->U_1.V_5.Class.Names);
  yyWriteSelector((STRING)"AttrCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.AttrCount, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"InstCount", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.InstCount, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Instance", 8L);
  yyWriteHex((WORD *)&yyt->U_1.V_5.Class.Instance, (LONGCARD)sizeof(yyt->U_1.V_5.Class.Instance));
  yyWriteNl();
  yyWriteSelector((STRING)"DP", 2L);
  Relations_WriteRelation(yyf, yyt->U_1.V_5.Class.DP);
  yyWriteNl();
  yyWriteSelector((STRING)"SNC", 3L);
  Relations_WriteRelation(yyf, yyt->U_1.V_5.Class.SNC);
  yyWriteNl();
  yyWriteSelector((STRING)"DNC", 3L);
  Relations_WriteRelation(yyf, yyt->U_1.V_5.Class.DNC);
  yyWriteNl();
  yyWriteSelector((STRING)"OAG", 3L);
  Relations_WriteRelation(yyf, yyt->U_1.V_5.Class.OAG);
  yyWriteNl();
  yyWriteSelector((STRING)"Part", 4L);
  Relations_WriteRelation(yyf, yyt->U_1.V_5.Class.Part);
  yyWriteNl();
  yyWriteSelector((STRING)"Index", 5L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.Index, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Visits", 6L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.Visits, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Users", 5L);
  Sets_WriteSet(yyf, yyt->U_1.V_5.Class.Users);
  yyWriteNl();
  yyWriteSelector((STRING)"Generated", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.Generated, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"BitCount", 8L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.BitCount, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"BitIndex", 8L);
  yyWriteHex((WORD *)&yyt->U_1.V_5.Class.BitIndex, (LONGCARD)sizeof(yyt->U_1.V_5.Class.BitIndex));
  yyWriteNl();
  yyWriteSelector((STRING)"D", 1L);
  yyWriteHex((WORD *)&yyt->U_1.V_5.Class.D, (LONGCARD)sizeof(yyt->U_1.V_5.Class.D));
  yyWriteNl();
  yyWriteSelector((STRING)"ClassChildCount", 15L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_5.Class.ClassChildCount, 0L);
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
  yyWriteSelector((STRING)"Item", 4L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_8.AttrOrAction.Item, 0L);
  yyWriteNl();
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
  Tree_WriteAttrProperties(yyf, yyt->U_1.V_9.Child.Properties);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_9.Child.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"AttrIndex", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Child.AttrIndex, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Partition", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Child.Partition, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Usage", 5L);
  yyWriteHex((WORD *)&yyt->U_1.V_9.Child.Usage, (LONGCARD)sizeof(yyt->U_1.V_9.Child.Usage));
  yyWriteNl();
  yyWriteSelector((STRING)"InstOffset", 10L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Child.InstOffset, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Class", 5L);
  yyWriteHex((WORD *)&yyt->U_1.V_9.Child.Class, (LONGCARD)sizeof(yyt->U_1.V_9.Child.Class));
  yyWriteNl();
  yyWriteSelector((STRING)"ParsIndex", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Child.ParsIndex, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"BitOffset", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Child.BitOffset, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"ChildIndex", 10L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_9.Child.ChildIndex, 0L);
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
  Tree_WriteAttrProperties(yyf, yyt->U_1.V_10.Attribute.Properties);
  yyWriteNl();
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_10.Attribute.Pos);
  yyWriteNl();
  yyWriteSelector((STRING)"AttrIndex", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_10.Attribute.AttrIndex, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Partition", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_10.Attribute.Partition, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Usage", 5L);
  yyWriteHex((WORD *)&yyt->U_1.V_10.Attribute.Usage, (LONGCARD)sizeof(yyt->U_1.V_10.Attribute.Usage));
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
  yyWriteSelector((STRING)"Actions", 7L);
  yyWriteAdr(yyt->U_1.V_11.ActionPart.Actions);
  yyWriteSelector((STRING)"Name", 4L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_11.ActionPart.Name, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"ParsIndex", 9L);
  IO_WriteI(yyf, (LONGINT)yyt->U_1.V_11.ActionPart.ParsIndex, 0L);
  yyWriteNl();
  yyWriteSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_11.ActionPart.Properties, (LONGCARD)sizeof(yyt->U_1.V_11.ActionPart.Properties));
  yyWriteNl();
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
}

static void yyyWriteNodeAg
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_26.Ag.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"ScannerName", 11L);
  Idents_WriteIdent(yyf, yyt->U_1.V_26.Ag.ScannerName);
  yyWriteNl();
  yyWriteSelector((STRING)"ParserName", 10L);
  Idents_WriteIdent(yyf, yyt->U_1.V_26.Ag.ParserName);
  yyWriteNl();
  yyWriteSelector((STRING)"ParserCodes", 11L);
  yyWriteAdr(yyt->U_1.V_26.Ag.ParserCodes);
  yyWriteSelector((STRING)"TreeName", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_26.Ag.TreeName);
  yyWriteNl();
  yyWriteSelector((STRING)"TreeCodes", 9L);
  yyWriteAdr(yyt->U_1.V_26.Ag.TreeCodes);
  yyWriteSelector((STRING)"EvalName", 8L);
  Idents_WriteIdent(yyf, yyt->U_1.V_26.Ag.EvalName);
  yyWriteNl();
  yyWriteSelector((STRING)"EvalCodes", 9L);
  yyWriteAdr(yyt->U_1.V_26.Ag.EvalCodes);
  yyWriteSelector((STRING)"Precs", 5L);
  yyWriteAdr(yyt->U_1.V_26.Ag.Precs);
  yyWriteSelector((STRING)"Props", 5L);
  yyWriteAdr(yyt->U_1.V_26.Ag.Props);
  yyWriteSelector((STRING)"Decls", 5L);
  yyWriteAdr(yyt->U_1.V_26.Ag.Decls);
  yyWriteSelector((STRING)"Classes", 7L);
  yyWriteAdr(yyt->U_1.V_26.Ag.Classes);
  yyWriteSelector((STRING)"Modules", 7L);
  yyWriteAdr(yyt->U_1.V_26.Ag.Modules);
  yyWriteSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_26.Ag.Properties, (LONGCARD)sizeof(yyt->U_1.V_26.Ag.Properties));
  yyWriteNl();
}

static void yyyWriteNodePrec
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Names", 5L);
  yyWriteAdr(yyt->U_1.V_29.Prec.Names);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_29.Prec.Next);
}

static void yyyWriteNodeLeftAssoc
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePrec(yyt);
}

static void yyyWriteNodeRightAssoc
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePrec(yyt);
}

static void yyyWriteNodeNonAssoc
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodePrec(yyt);
}

static void yyyWriteNodeAction
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_35.Action.Next);
  yyWriteSelector((STRING)"Pos", 3L);
  Positions_WritePosition(yyf, yyt->U_1.V_35.Action.Pos);
  yyWriteNl();
}

static void yyyWriteNodeAssign
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAction(yyt);
  yyWriteSelector((STRING)"Results", 7L);
  yyWriteAdr(yyt->U_1.V_36.Assign.Results);
  yyWriteSelector((STRING)"Arguments", 9L);
  yyWriteAdr(yyt->U_1.V_36.Assign.Arguments);
}

static void yyyWriteNodeCopy
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAction(yyt);
  yyWriteSelector((STRING)"Results", 7L);
  yyWriteAdr(yyt->U_1.V_37.Copy.Results);
  yyWriteSelector((STRING)"Arguments", 9L);
  yyWriteAdr(yyt->U_1.V_37.Copy.Arguments);
}

static void yyyWriteNodeTargetCode
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAction(yyt);
  yyWriteSelector((STRING)"Results", 7L);
  yyWriteAdr(yyt->U_1.V_38.TargetCode.Results);
  yyWriteSelector((STRING)"Code", 4L);
  yyWriteAdr(yyt->U_1.V_38.TargetCode.Code);
}

static void yyyWriteNodeOrder
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAction(yyt);
  yyWriteSelector((STRING)"Results", 7L);
  yyWriteAdr(yyt->U_1.V_39.Order.Results);
  yyWriteSelector((STRING)"Arguments", 9L);
  yyWriteAdr(yyt->U_1.V_39.Order.Arguments);
}

static void yyyWriteNodeCheck
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyyWriteNodeAction(yyt);
  yyWriteSelector((STRING)"Condition", 9L);
  yyWriteAdr(yyt->U_1.V_40.Check.Condition);
  yyWriteSelector((STRING)"Statement", 9L);
  yyWriteAdr(yyt->U_1.V_40.Check.Statement);
  yyWriteSelector((STRING)"Actions", 7L);
  yyWriteAdr(yyt->U_1.V_40.Check.Actions);
  yyWriteSelector((STRING)"Results", 7L);
  yyWriteAdr(yyt->U_1.V_40.Check.Results);
}

static void yyyWriteNodeModule
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Name", 4L);
  Idents_WriteIdent(yyf, yyt->U_1.V_43.Module.Name);
  yyWriteNl();
  yyWriteSelector((STRING)"ParserCodes", 11L);
  yyWriteAdr(yyt->U_1.V_43.Module.ParserCodes);
  yyWriteSelector((STRING)"TreeCodes", 9L);
  yyWriteAdr(yyt->U_1.V_43.Module.TreeCodes);
  yyWriteSelector((STRING)"EvalCodes", 9L);
  yyWriteAdr(yyt->U_1.V_43.Module.EvalCodes);
  yyWriteSelector((STRING)"Props", 5L);
  yyWriteAdr(yyt->U_1.V_43.Module.Props);
  yyWriteSelector((STRING)"Decls", 5L);
  yyWriteAdr(yyt->U_1.V_43.Module.Decls);
  yyWriteSelector((STRING)"Classes", 7L);
  yyWriteAdr(yyt->U_1.V_43.Module.Classes);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_43.Module.Next);
  yyWriteSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_43.Module.Properties, (LONGCARD)sizeof(yyt->U_1.V_43.Module.Properties));
  yyWriteNl();
}

static void yyyWriteNodeProp
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Properties", 10L);
  yyWriteHex((WORD *)&yyt->U_1.V_46.Prop.Properties, (LONGCARD)sizeof(yyt->U_1.V_46.Prop.Properties));
  yyWriteNl();
  yyWriteSelector((STRING)"Names", 5L);
  yyWriteAdr(yyt->U_1.V_46.Prop.Names);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_46.Prop.Next);
}

static void yyyWriteNodeSelect
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Names", 5L);
  yyWriteAdr(yyt->U_1.V_47.Select.Names);
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_47.Select.Next);
}

static void yyyWriteNodeDecl
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyWriteSelector((STRING)"Names", 5L);
  yyWriteAdr(yyt->U_1.V_50.Decl.Names);
  yyWriteSelector((STRING)"Attributes", 10L);
  yyWriteAdr(yyt->U_1.V_50.Decl.Attributes);
  yyWriteSelector((STRING)"Properties", 10L);
  Tree_WriteClassProperties(yyf, yyt->U_1.V_50.Decl.Properties);
  yyWriteNl();
  yyWriteSelector((STRING)"Next", 4L);
  yyWriteAdr(yyt->U_1.V_50.Decl.Next);
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
  case Tree_Ag:;
    IO_WriteS(yyf, (STRING)"Ag", 2L);
    yyWriteNl();
    yyyWriteNodeAg(yyt);
    break;
  case Tree_Precs:;
    IO_WriteS(yyf, (STRING)"Precs", 5L);
    yyWriteNl();
    break;
  case Tree_NoPrec:;
    IO_WriteS(yyf, (STRING)"NoPrec", 6L);
    yyWriteNl();
    break;
  case Tree_Prec:;
    IO_WriteS(yyf, (STRING)"Prec", 4L);
    yyWriteNl();
    yyyWriteNodePrec(yyt);
    break;
  case Tree_LeftAssoc:;
    IO_WriteS(yyf, (STRING)"LeftAssoc", 9L);
    yyWriteNl();
    yyyWriteNodeLeftAssoc(yyt);
    break;
  case Tree_RightAssoc:;
    IO_WriteS(yyf, (STRING)"RightAssoc", 10L);
    yyWriteNl();
    yyyWriteNodeRightAssoc(yyt);
    break;
  case Tree_NonAssoc:;
    IO_WriteS(yyf, (STRING)"NonAssoc", 8L);
    yyWriteNl();
    yyyWriteNodeNonAssoc(yyt);
    break;
  case Tree_Actions:;
    IO_WriteS(yyf, (STRING)"Actions", 7L);
    yyWriteNl();
    break;
  case Tree_NoAction:;
    IO_WriteS(yyf, (STRING)"NoAction", 8L);
    yyWriteNl();
    break;
  case Tree_Action:;
    IO_WriteS(yyf, (STRING)"Action", 6L);
    yyWriteNl();
    yyyWriteNodeAction(yyt);
    break;
  case Tree_Assign:;
    IO_WriteS(yyf, (STRING)"Assign", 6L);
    yyWriteNl();
    yyyWriteNodeAssign(yyt);
    break;
  case Tree_Copy:;
    IO_WriteS(yyf, (STRING)"Copy", 4L);
    yyWriteNl();
    yyyWriteNodeCopy(yyt);
    break;
  case Tree_TargetCode:;
    IO_WriteS(yyf, (STRING)"TargetCode", 10L);
    yyWriteNl();
    yyyWriteNodeTargetCode(yyt);
    break;
  case Tree_Order:;
    IO_WriteS(yyf, (STRING)"Order", 5L);
    yyWriteNl();
    yyyWriteNodeOrder(yyt);
    break;
  case Tree_Check:;
    IO_WriteS(yyf, (STRING)"Check", 5L);
    yyWriteNl();
    yyyWriteNodeCheck(yyt);
    break;
  case Tree_Modules:;
    IO_WriteS(yyf, (STRING)"Modules", 7L);
    yyWriteNl();
    break;
  case Tree_NoModule:;
    IO_WriteS(yyf, (STRING)"NoModule", 8L);
    yyWriteNl();
    break;
  case Tree_Module:;
    IO_WriteS(yyf, (STRING)"Module", 6L);
    yyWriteNl();
    yyyWriteNodeModule(yyt);
    break;
  case Tree_Props:;
    IO_WriteS(yyf, (STRING)"Props", 5L);
    yyWriteNl();
    break;
  case Tree_NoProp:;
    IO_WriteS(yyf, (STRING)"NoProp", 6L);
    yyWriteNl();
    break;
  case Tree_Prop:;
    IO_WriteS(yyf, (STRING)"Prop", 4L);
    yyWriteNl();
    yyyWriteNodeProp(yyt);
    break;
  case Tree_Select:;
    IO_WriteS(yyf, (STRING)"Select", 6L);
    yyWriteNl();
    yyyWriteNodeSelect(yyt);
    break;
  case Tree_Decls:;
    IO_WriteS(yyf, (STRING)"Decls", 5L);
    yyWriteNl();
    break;
  case Tree_NoDecl:;
    IO_WriteS(yyf, (STRING)"NoDecl", 6L);
    yyWriteNl();
    break;
  case Tree_Decl:;
    IO_WriteS(yyf, (STRING)"Decl", 4L);
    yyWriteNl();
    yyyWriteNodeDecl(yyt);
    break;
  default :
    break;
  }
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
    case Tree_Prec:;
      yyNext = yyOld->U_1.V_29.Prec.Next;
      yyOld->U_1.V_29.Prec.Next = yyNew;
      break;
    case Tree_LeftAssoc:;
      yyNext = yyOld->U_1.V_30.LeftAssoc.Next;
      yyOld->U_1.V_30.LeftAssoc.Next = yyNew;
      break;
    case Tree_RightAssoc:;
      yyNext = yyOld->U_1.V_31.RightAssoc.Next;
      yyOld->U_1.V_31.RightAssoc.Next = yyNew;
      break;
    case Tree_NonAssoc:;
      yyNext = yyOld->U_1.V_32.NonAssoc.Next;
      yyOld->U_1.V_32.NonAssoc.Next = yyNew;
      break;
    case Tree_Action:;
      yyNext = yyOld->U_1.V_35.Action.Next;
      yyOld->U_1.V_35.Action.Next = yyNew;
      break;
    case Tree_Assign:;
      yyNext = yyOld->U_1.V_36.Assign.Next;
      yyOld->U_1.V_36.Assign.Next = yyNew;
      break;
    case Tree_Copy:;
      yyNext = yyOld->U_1.V_37.Copy.Next;
      yyOld->U_1.V_37.Copy.Next = yyNew;
      break;
    case Tree_TargetCode:;
      yyNext = yyOld->U_1.V_38.TargetCode.Next;
      yyOld->U_1.V_38.TargetCode.Next = yyNew;
      break;
    case Tree_Order:;
      yyNext = yyOld->U_1.V_39.Order.Next;
      yyOld->U_1.V_39.Order.Next = yyNew;
      break;
    case Tree_Check:;
      yyNext = yyOld->U_1.V_40.Check.Next;
      yyOld->U_1.V_40.Check.Next = yyNew;
      break;
    case Tree_Module:;
      yyNext = yyOld->U_1.V_43.Module.Next;
      yyOld->U_1.V_43.Module.Next = yyNew;
      break;
    case Tree_Prop:;
      yyNext = yyOld->U_1.V_46.Prop.Next;
      yyOld->U_1.V_46.Prop.Next = yyNew;
      break;
    case Tree_Select:;
      yyNext = yyOld->U_1.V_47.Select.Next;
      yyOld->U_1.V_47.Select.Next = yyNew;
      break;
    case Tree_Decl:;
      yyNext = yyOld->U_1.V_50.Decl.Next;
      yyOld->U_1.V_50.Decl.Next = yyNew;
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
  case Tree_Prec:;
    yyTail->U_1.V_29.Prec.Next = yyOld;
    break;
  case Tree_LeftAssoc:;
    yyTail->U_1.V_30.LeftAssoc.Next = yyOld;
    break;
  case Tree_RightAssoc:;
    yyTail->U_1.V_31.RightAssoc.Next = yyOld;
    break;
  case Tree_NonAssoc:;
    yyTail->U_1.V_32.NonAssoc.Next = yyOld;
    break;
  case Tree_Action:;
    yyTail->U_1.V_35.Action.Next = yyOld;
    break;
  case Tree_Assign:;
    yyTail->U_1.V_36.Assign.Next = yyOld;
    break;
  case Tree_Copy:;
    yyTail->U_1.V_37.Copy.Next = yyOld;
    break;
  case Tree_TargetCode:;
    yyTail->U_1.V_38.TargetCode.Next = yyOld;
    break;
  case Tree_Order:;
    yyTail->U_1.V_39.Order.Next = yyOld;
    break;
  case Tree_Check:;
    yyTail->U_1.V_40.Check.Next = yyOld;
    break;
  case Tree_Module:;
    yyTail->U_1.V_43.Module.Next = yyOld;
    break;
  case Tree_Prop:;
    yyTail->U_1.V_46.Prop.Next = yyOld;
    break;
  case Tree_Select:;
    yyTail->U_1.V_47.Select.Next = yyOld;
    break;
  case Tree_Decl:;
    yyTail->U_1.V_50.Decl.Next = yyOld;
    break;
  default :
    break;
  }
  return yyNew;
}

static BOOLEAN yyyIsEqual
# ifdef __STDC__
(CHAR yya[], LONGCARD O_3)
# else
(yya, O_3)
CHAR yya[];
LONGCARD O_3;
# endif
{
  INTEGER yyi;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yya, O_3, CHAR)
  if (yyLength >= 0 && yyString.A[yyLength] == ' ') {
    if (yyLength - 1 != (INTEGER)(O_3 - 1)) {
      FREE_OPEN_ARRAYS
      return FALSE;
    }
    {
      LONGINT B_15 = 0, B_16 = yyLength - 1;

      if (B_15 <= B_16)
        for (yyi = B_15;; yyi += 1) {
          if (yyString.A[yyi] != yya[yyi]) {
            FREE_OPEN_ARRAYS
            return FALSE;
          }
          if (yyi >= B_16) break;
        }
    }
  } else {
    if (yyLength > (INTEGER)(O_3 - 1)) {
      FREE_OPEN_ARRAYS
      return FALSE;
    }
    {
      LONGINT B_17 = 0, B_18 = yyLength;

      if (B_17 <= B_18)
        for (yyi = B_17;; yyi += 1) {
          if (yyString.A[yyi] != yya[yyi]) {
            FREE_OPEN_ARRAYS
            return FALSE;
          }
          if (yyi >= B_18) break;
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
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_5.Class.Names);
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
          } else if (yyyIsEqual((STRING)"Actions", 7L)) {
            Tree_QueryTree(yyt->U_1.V_11.ActionPart.Actions);
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
        case Tree_Ag:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"ParserCodes", 11L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.ParserCodes);
          } else if (yyyIsEqual((STRING)"TreeCodes", 9L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.TreeCodes);
          } else if (yyyIsEqual((STRING)"EvalCodes", 9L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.EvalCodes);
          } else if (yyyIsEqual((STRING)"Precs", 5L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.Precs);
          } else if (yyyIsEqual((STRING)"Props", 5L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.Props);
          } else if (yyyIsEqual((STRING)"Decls", 5L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.Decls);
          } else if (yyyIsEqual((STRING)"Classes", 7L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.Classes);
          } else if (yyyIsEqual((STRING)"Modules", 7L)) {
            Tree_QueryTree(yyt->U_1.V_26.Ag.Modules);
          }
          break;
        case Tree_Prec:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_29.Prec.Names);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_29.Prec.Next);
          }
          break;
        case Tree_LeftAssoc:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_30.LeftAssoc.Names);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_30.LeftAssoc.Next);
          }
          break;
        case Tree_RightAssoc:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_31.RightAssoc.Names);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_31.RightAssoc.Next);
          }
          break;
        case Tree_NonAssoc:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_32.NonAssoc.Names);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_32.NonAssoc.Next);
          }
          break;
        case Tree_Action:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_35.Action.Next);
          }
          break;
        case Tree_Assign:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_36.Assign.Next);
          } else if (yyyIsEqual((STRING)"Results", 7L)) {
            Tree_QueryTree(yyt->U_1.V_36.Assign.Results);
          } else if (yyyIsEqual((STRING)"Arguments", 9L)) {
            Tree_QueryTree(yyt->U_1.V_36.Assign.Arguments);
          }
          break;
        case Tree_Copy:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_37.Copy.Next);
          } else if (yyyIsEqual((STRING)"Results", 7L)) {
            Tree_QueryTree(yyt->U_1.V_37.Copy.Results);
          } else if (yyyIsEqual((STRING)"Arguments", 9L)) {
            Tree_QueryTree(yyt->U_1.V_37.Copy.Arguments);
          }
          break;
        case Tree_TargetCode:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_38.TargetCode.Next);
          } else if (yyyIsEqual((STRING)"Results", 7L)) {
            Tree_QueryTree(yyt->U_1.V_38.TargetCode.Results);
          } else if (yyyIsEqual((STRING)"Code", 4L)) {
            Tree_QueryTree(yyt->U_1.V_38.TargetCode.Code);
          }
          break;
        case Tree_Order:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_39.Order.Next);
          } else if (yyyIsEqual((STRING)"Results", 7L)) {
            Tree_QueryTree(yyt->U_1.V_39.Order.Results);
          } else if (yyyIsEqual((STRING)"Arguments", 9L)) {
            Tree_QueryTree(yyt->U_1.V_39.Order.Arguments);
          }
          break;
        case Tree_Check:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_40.Check.Next);
          } else if (yyyIsEqual((STRING)"Condition", 9L)) {
            Tree_QueryTree(yyt->U_1.V_40.Check.Condition);
          } else if (yyyIsEqual((STRING)"Statement", 9L)) {
            Tree_QueryTree(yyt->U_1.V_40.Check.Statement);
          } else if (yyyIsEqual((STRING)"Actions", 7L)) {
            Tree_QueryTree(yyt->U_1.V_40.Check.Actions);
          } else if (yyyIsEqual((STRING)"Results", 7L)) {
            Tree_QueryTree(yyt->U_1.V_40.Check.Results);
          }
          break;
        case Tree_Module:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"ParserCodes", 11L)) {
            Tree_QueryTree(yyt->U_1.V_43.Module.ParserCodes);
          } else if (yyyIsEqual((STRING)"TreeCodes", 9L)) {
            Tree_QueryTree(yyt->U_1.V_43.Module.TreeCodes);
          } else if (yyyIsEqual((STRING)"EvalCodes", 9L)) {
            Tree_QueryTree(yyt->U_1.V_43.Module.EvalCodes);
          } else if (yyyIsEqual((STRING)"Props", 5L)) {
            Tree_QueryTree(yyt->U_1.V_43.Module.Props);
          } else if (yyyIsEqual((STRING)"Decls", 5L)) {
            Tree_QueryTree(yyt->U_1.V_43.Module.Decls);
          } else if (yyyIsEqual((STRING)"Classes", 7L)) {
            Tree_QueryTree(yyt->U_1.V_43.Module.Classes);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_43.Module.Next);
          }
          break;
        case Tree_Prop:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_46.Prop.Names);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_46.Prop.Next);
          }
          break;
        case Tree_Select:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_47.Select.Names);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_47.Select.Next);
          }
          break;
        case Tree_Decl:;
          if (FALSE) {
          } else if (yyyIsEqual((STRING)"Names", 5L)) {
            Tree_QueryTree(yyt->U_1.V_50.Decl.Names);
          } else if (yyyIsEqual((STRING)"Attributes", 10L)) {
            Tree_QueryTree(yyt->U_1.V_50.Decl.Attributes);
          } else if (yyyIsEqual((STRING)"Next", 4L)) {
            Tree_QueryTree(yyt->U_1.V_50.Decl.Next);
          }
          break;
        default :
          break;
        }
      }
      break;
    }
  } EXIT_4:;
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
  Sets_MakeSet(&DummySet, 0L);
  Relations_MakeRelation(&DummyRelation, 0L, 0L);
  Tree_nNoAction = Tree_mNoAction();
  Tree_nNoAttribute = Tree_mNoAttribute();
  Tree_nNoClass = Tree_mNoClass();
  Tree_nNoDecl = Tree_mNoDecl();
  Tree_nNoDesignator = Tree_mNoDesignator();
  Tree_nNoLayout = Tree_mNoLayout();
  Tree_nNoModule = Tree_mNoModule();
  Tree_nNoName = Tree_mNoName();
  Tree_nNoPrec = Tree_mNoPrec();
  Tree_nNoProp = Tree_mNoProp();
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
    Tree_yyNodeSize.A[Tree_Ag] = sizeof(Tree_yAg);
    Tree_yyNodeSize.A[Tree_Precs] = sizeof(Tree_yPrecs);
    Tree_yyNodeSize.A[Tree_NoPrec] = sizeof(Tree_yNoPrec);
    Tree_yyNodeSize.A[Tree_Prec] = sizeof(Tree_yPrec);
    Tree_yyNodeSize.A[Tree_LeftAssoc] = sizeof(Tree_yLeftAssoc);
    Tree_yyNodeSize.A[Tree_RightAssoc] = sizeof(Tree_yRightAssoc);
    Tree_yyNodeSize.A[Tree_NonAssoc] = sizeof(Tree_yNonAssoc);
    Tree_yyNodeSize.A[Tree_Actions] = sizeof(Tree_yActions);
    Tree_yyNodeSize.A[Tree_NoAction] = sizeof(Tree_yNoAction);
    Tree_yyNodeSize.A[Tree_Action] = sizeof(Tree_yAction);
    Tree_yyNodeSize.A[Tree_Assign] = sizeof(Tree_yAssign);
    Tree_yyNodeSize.A[Tree_Copy] = sizeof(Tree_yCopy);
    Tree_yyNodeSize.A[Tree_TargetCode] = sizeof(Tree_yTargetCode);
    Tree_yyNodeSize.A[Tree_Order] = sizeof(Tree_yOrder);
    Tree_yyNodeSize.A[Tree_Check] = sizeof(Tree_yCheck);
    Tree_yyNodeSize.A[Tree_Modules] = sizeof(Tree_yModules);
    Tree_yyNodeSize.A[Tree_NoModule] = sizeof(Tree_yNoModule);
    Tree_yyNodeSize.A[Tree_Module] = sizeof(Tree_yModule);
    Tree_yyNodeSize.A[Tree_Props] = sizeof(Tree_yProps);
    Tree_yyNodeSize.A[Tree_NoProp] = sizeof(Tree_yNoProp);
    Tree_yyNodeSize.A[Tree_Prop] = sizeof(Tree_yProp);
    Tree_yyNodeSize.A[Tree_Select] = sizeof(Tree_ySelect);
    Tree_yyNodeSize.A[Tree_Decls] = sizeof(Tree_yDecls);
    Tree_yyNodeSize.A[Tree_NoDecl] = sizeof(Tree_yNoDecl);
    Tree_yyNodeSize.A[Tree_Decl] = sizeof(Tree_yDecl);
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
    yyTypeRange.A[Tree_Ag] = Tree_Ag;
    yyTypeRange.A[Tree_Precs] = Tree_NonAssoc;
    yyTypeRange.A[Tree_NoPrec] = Tree_NoPrec;
    yyTypeRange.A[Tree_Prec] = Tree_NonAssoc;
    yyTypeRange.A[Tree_LeftAssoc] = Tree_LeftAssoc;
    yyTypeRange.A[Tree_RightAssoc] = Tree_RightAssoc;
    yyTypeRange.A[Tree_NonAssoc] = Tree_NonAssoc;
    yyTypeRange.A[Tree_Actions] = Tree_Check;
    yyTypeRange.A[Tree_NoAction] = Tree_NoAction;
    yyTypeRange.A[Tree_Action] = Tree_Check;
    yyTypeRange.A[Tree_Assign] = Tree_Assign;
    yyTypeRange.A[Tree_Copy] = Tree_Copy;
    yyTypeRange.A[Tree_TargetCode] = Tree_TargetCode;
    yyTypeRange.A[Tree_Order] = Tree_Order;
    yyTypeRange.A[Tree_Check] = Tree_Check;
    yyTypeRange.A[Tree_Modules] = Tree_Module;
    yyTypeRange.A[Tree_NoModule] = Tree_NoModule;
    yyTypeRange.A[Tree_Module] = Tree_Module;
    yyTypeRange.A[Tree_Props] = Tree_Select;
    yyTypeRange.A[Tree_NoProp] = Tree_NoProp;
    yyTypeRange.A[Tree_Prop] = Tree_Prop;
    yyTypeRange.A[Tree_Select] = Tree_Select;
    yyTypeRange.A[Tree_Decls] = Tree_Decl;
    yyTypeRange.A[Tree_NoDecl] = Tree_NoDecl;
    yyTypeRange.A[Tree_Decl] = Tree_Decl;
    Tree_BeginTree();
  }
}
