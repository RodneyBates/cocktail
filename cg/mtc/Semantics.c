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

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
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

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

SHORTCARD Semantics_TypeCount;
IO_tFile Semantics_yyf;
PROC Semantics_Exit;

#define AssignmentLhsNamesNoAttributes   10
#define CopyRuleLhsNamesNoAttributes   11
#define BlockLhsNamesNoAttributes   12
#define CheckWithoutStatement   13
#define InheritedUseOfSynthesizedAttribute   14
#define AttributeMultipleComputed   15
#define ChildsClassHasNoSuchAttribute   16
#define NoSuchChild   17
#define SynthesizedUseOfInheritedAttribute   18
#define NoSuchAttribute   19
#define CopyRuleInsertionsInherited   20
#define CopyRuleInsertionsSynthesized   21
#define CopyRuleInsertionsThreaded   22
#define ModuleNotDeclared   23
#define TerminalCodeMultipleUsed   24
#define NodeTypeNotDeclared   25
#define OnlyOneReverseAllowedInNodeType   26
#define NodeTypeMultipleDeclared   27
#define VariantSelectorMultipleDeclared   28
#define PrecedenceNotDeclared   29
#define SelectorMultipleDeclared   30
#define PrecedenceMultipleDeclared   31
#define AbstractTypeRequired   32
#define ChildRequired   33
#define AttributeNotDeclared   34
#define SelectorNotDeclared   35
#define AttributeNeverSet   36
#define AttributeNeverUsed   37
#define AssignmentToInputAttribute   38
#define AttributeSynthesizedAsWellAsInherited   39
#define NodeTypeNotUsed   40
#define InheritedAttributesAllowedOnlyInBaseClasses   41
#define AttributeComputationMissing   42
#define CycleInLocalDependenciesDP   43
static INTEGER CopyInherited, CopySynthesized, CopyThreaded, ChildCount, AttributeCount, ActionCount, ActionName;
static INTEGER ItemCount, ChecksCount, ReverseCount;
static Idents_tIdent iNull, Ident;
static Sets_tSet ClassNames, SelectorNames, VariantNames, PrecNames, CodesUsed, Results, Arguments, Cyclics;
static SHORTCARD MaxInstCount, TokenCode, DummyIndex, i, j, k;
static LONGINT InstanceSize;
static BOOLEAN IsAbstract, Success;
static Tree_tTree Module, Node, Attribute, Child, TheAction, TheClass, Class;
static Strings_tString String, String2;
static BITSET ActProperties;
static BOOLEAN LookUp ARGS((Idents_tIdent i, Tree_tTree t));
static Tree_tTree ProcessIgnore2 ARGS((Tree_tTree t));
static void CompBaseClass ARGS((Tree_tTree t, Tree_tTree b));
static void CompParsIndex ARGS((Tree_tTree t, SHORTCARD *Index));
static void CompChildIndex ARGS((Tree_tTree t, SHORTCARD *Index));
static void CompIndex ARGS((Tree_tTree t, SHORTCARD In, SHORTCARD *Out));
static void CompInstance ARGS((Tree_tTree t, SHORTCARD In, SHORTCARD *Out));
static void CompBitCount ARGS((Tree_tTree t, SHORTCARD In, SHORTCARD *Out));
static void CompBitOffset ARGS((Tree_tTree t, SHORTCARD In, SHORTCARD *Out));
static void InitInstance ARGS((Tree_tTree t, SHORTCARD Offset, Tree_tInstancePtr InstancePtr));
static void InitInstance1 ARGS((Tree_tTree t, Tree_tTree selector, SHORTCARD Offset, Tree_tInstancePtr InstancePtr));
static Relations_tRelation relation;
static INTEGER result;
static void EnterDependency ARGS((Sets_tElement argument));
static BOOLEAN MultipleInheritedActions;
static void CompDP1 ARGS((Tree_tTree t, Sets_tSet *Set, INTEGER Usage, BOOLEAN NonBase, BOOLEAN Check));
static BOOLEAN IsCode ARGS((Tree_tTree t));
static Tree_tTree CopyTree ARGS((Tree_tTree t));
static void ExpandMultiple ARGS((Tree_tTree Class));
static void AppendAttr ARGS((Tree_tTree *Attributes, Tree_tTree Attribute));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
static void StampItems ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void ExpandProps ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void CheckSelect ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void ProcessIgnore ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void ExpandModules ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void ExpandChecks ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void ExpandMultiple2 ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void CountClasses ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void CompReachable ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void CodeTerminals ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void CheckReverse ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void CheckNames ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void CheckNames2 ARGS((Tree_tTree t));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static void CheckDesignator ARGS((Tree_tTree t));
struct S_17 {
    union {
        char dummy;
    } U_1;
};
static void Identify ARGS((Tree_tTree t));
struct S_18 {
    union {
        char dummy;
    } U_1;
};
static void InitInstance0 ARGS((Tree_tTree t));
struct S_19 {
    union {
        char dummy;
    } U_1;
};
static void CompDP ARGS((Tree_tTree t));
struct S_20 {
    union {
        char dummy;
    } U_1;
};
static void CopyProperties ARGS((Tree_tTree t));
struct S_21 {
    union {
        char dummy;
    } U_1;
};
static void CheckUsage ARGS((Tree_tTree t));
struct S_22 {
    union {
        char dummy;
    } U_1;
};
static void CheckUsage2 ARGS((Tree_tTree t));
struct S_23 {
    union {
        struct {
            struct S_24 {
                Strings_tString String;
            } yyR1;
        } V_1;
    } U_1;
};
static void CheckInherited ARGS((Tree_tTree t));
struct S_25 {
    union {
        char dummy;
    } U_1;
};
static void CheckComplete ARGS((Tree_tTree t));
struct S_26 {
    union {
        char dummy;
    } U_1;
};
static void CopyRule ARGS((Tree_tTree t));
struct S_27 {
    union {
        char dummy;
    } U_1;
};
static void CopyRule2 ARGS((Tree_tTree t));
struct S_28 {
    union {
        char dummy;
    } U_1;
};
static BOOLEAN IsCopy ARGS((Tree_tTree yyP1));
struct S_29 {
    union {
        struct {
            struct S_30 {
                Tree_tTree Attr;
                Tree_tTree ChildsClass;
            } yyR1;
        } V_1;
    } U_1;
};
static BOOLEAN IsWhiteSpace ARGS((Tree_tTree yyP2));
struct S_31 {
    union {
        char dummy;
    } U_1;
};
static BOOLEAN IsWhiteSpace2 ARGS((StringMem_tStringRef yyP3));
struct S_32 {
    union {
        struct {
            struct S_33 {
                Strings_tString String;
                CHAR ch;
            } yyR1;
        } V_1;
    } U_1;
};
static void yyExit ARGS(());


static BOOLEAN LookUp
# ifdef __STDC__
(Idents_tIdent i, Tree_tTree t)
# else
(i, t)
Idents_tIdent i;
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Name) {
    if (t->U_1.V_25.Name.Name == i) {
      return TRUE;
    }
    t = t->U_1.V_25.Name.Next;
  }
  return FALSE;
}

static Tree_tTree ProcessIgnore2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Tree_tTree r;

  if (t->U_1.V_1.Kind != Tree_NoAttribute) {
    t->U_1.V_8.AttrOrAction.Next = ProcessIgnore2(t->U_1.V_8.AttrOrAction.Next);
  }
  if (t->U_1.V_1.Kind == Tree_Child && IN(Tree_Ignore, t->U_1.V_9.Child.Properties) || t->U_1.V_1.Kind == Tree_Attribute && IN(Tree_Ignore, t->U_1.V_10.Attribute.Properties) || t->U_1.V_1.Kind == Tree_ActionPart && IN(Tree_Ignore, t->U_1.V_11.ActionPart.Properties)) {
    return t->U_1.V_8.AttrOrAction.Next;
  }
  return t;
}

static void CompBaseClass
# ifdef __STDC__
(Tree_tTree t, Tree_tTree b)
# else
(t, b)
Tree_tTree t, b;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Class) {
    t->U_1.V_5.Class.BaseClass = b;
    CompBaseClass(t->U_1.V_5.Class.Next, b);
    CompBaseClass(t->U_1.V_5.Class.Extensions, t);
  }
}

static void CompParsIndex
# ifdef __STDC__
(Tree_tTree t, SHORTCARD *Index)
# else
(t, Index)
Tree_tTree t;
SHORTCARD *Index;
# endif
{
  SHORTCARD OldIndex;

  OldIndex = *Index;
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    CompParsIndex(t->U_1.V_5.Class.Attributes, Index);
    CompParsIndex(t->U_1.V_5.Class.Extensions, Index);
    CompParsIndex(t->U_1.V_5.Class.Next, &OldIndex);
    break;
  case Tree_Child:;
    INC(*Index);
    t->U_1.V_9.Child.ParsIndex = *Index;
    CompParsIndex(t->U_1.V_9.Child.Next, Index);
    break;
  case Tree_Attribute:;
    CompParsIndex(t->U_1.V_10.Attribute.Next, Index);
    break;
  case Tree_ActionPart:;
    INC(*Index);
    t->U_1.V_11.ActionPart.ParsIndex = *Index;
    INC(ActionName);
    t->U_1.V_11.ActionPart.Name = ActionName;
    CompParsIndex(t->U_1.V_11.ActionPart.Next, Index);
    break;
  default :
    break;
  }
}

static void CompChildIndex
# ifdef __STDC__
(Tree_tTree t, SHORTCARD *Index)
# else
(t, Index)
Tree_tTree t;
SHORTCARD *Index;
# endif
{
  SHORTCARD OldIndex;

  OldIndex = *Index;
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    CompChildIndex(t->U_1.V_5.Class.Attributes, Index);
    t->U_1.V_5.Class.ClassChildCount = *Index;
    CompChildIndex(t->U_1.V_5.Class.Extensions, Index);
    CompChildIndex(t->U_1.V_5.Class.Next, &OldIndex);
    break;
  case Tree_Child:;
    INC(*Index);
    t->U_1.V_9.Child.ChildIndex = *Index;
    CompChildIndex(t->U_1.V_9.Child.Next, Index);
    break;
  case Tree_Attribute:;
    CompChildIndex(t->U_1.V_10.Attribute.Next, Index);
    break;
  case Tree_ActionPart:;
    CompChildIndex(t->U_1.V_11.ActionPart.Next, Index);
    break;
  default :
    break;
  }
}

static void CompIndex
# ifdef __STDC__
(Tree_tTree t, SHORTCARD In, SHORTCARD *Out)
# else
(t, In, Out)
Tree_tTree t;
SHORTCARD In;
SHORTCARD *Out;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    CompIndex(t->U_1.V_5.Class.Attributes, In, Out);
    t->U_1.V_5.Class.AttrCount = *Out;
    CompIndex(t->U_1.V_5.Class.Extensions, *Out, Out);
    CompIndex(t->U_1.V_5.Class.Next, In, Out);
    break;
  case Tree_NoClass:;
    break;
  case Tree_Child:;
    INC(In);
    t->U_1.V_9.Child.AttrIndex = In;
    CompIndex(t->U_1.V_9.Child.Next, In, Out);
    break;
  case Tree_Attribute:;
    INC(In);
    t->U_1.V_10.Attribute.AttrIndex = In;
    CompIndex(t->U_1.V_10.Attribute.Next, In, Out);
    break;
  case Tree_ActionPart:;
    CompIndex(t->U_1.V_11.ActionPart.Next, In, Out);
    break;
  case Tree_NoAttribute:;
    *Out = In;
    break;
  }
}

static void CompInstance
# ifdef __STDC__
(Tree_tTree t, SHORTCARD In, SHORTCARD *Out)
# else
(t, In, Out)
Tree_tTree t;
SHORTCARD In;
SHORTCARD *Out;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    CompInstance(t->U_1.V_5.Class.Attributes, In, Out);
    t->U_1.V_5.Class.InstCount = t->U_1.V_5.Class.AttrCount + *Out;
    MaxInstCount = General_Max((LONGINT)MaxInstCount, (LONGINT)t->U_1.V_5.Class.InstCount);
    CompInstance(t->U_1.V_5.Class.Extensions, *Out, Out);
    CompInstance(t->U_1.V_5.Class.Next, In, Out);
    break;
  case Tree_NoClass:;
    break;
  case Tree_Child:;
    t->U_1.V_9.Child.InstOffset = In;
    if (t->U_1.V_9.Child.Class != Tree_NoTree) {
      CompInstance(t->U_1.V_9.Child.Next, In + t->U_1.V_9.Child.Class->U_1.V_5.Class.AttrCount, Out);
    } else {
      CompInstance(t->U_1.V_9.Child.Next, In, Out);
    }
    break;
  case Tree_Attribute:;
    CompInstance(t->U_1.V_10.Attribute.Next, In, Out);
    break;
  case Tree_ActionPart:;
    CompInstance(t->U_1.V_11.ActionPart.Next, In, Out);
    break;
  case Tree_NoAttribute:;
    *Out = In;
    break;
  }
}

static void CompBitCount
# ifdef __STDC__
(Tree_tTree t, SHORTCARD In, SHORTCARD *Out)
# else
(t, In, Out)
Tree_tTree t;
SHORTCARD In;
SHORTCARD *Out;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    CompBitCount(t->U_1.V_5.Class.Attributes, In, Out);
    t->U_1.V_5.Class.BitCount = *Out;
    CompBitCount(t->U_1.V_5.Class.Extensions, *Out, Out);
    CompBitCount(t->U_1.V_5.Class.Next, In, Out);
    break;
  case Tree_NoClass:;
    break;
  case Tree_Child:;
    if (((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & t->U_1.V_9.Child.Properties) == 0X0L) {
      INC(In);
    }
    CompBitCount(t->U_1.V_9.Child.Next, In, Out);
    break;
  case Tree_Attribute:;
    if (((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & t->U_1.V_10.Attribute.Properties) == 0X0L) {
      INC(In);
    }
    CompBitCount(t->U_1.V_10.Attribute.Next, In, Out);
    break;
  case Tree_ActionPart:;
    CompBitCount(t->U_1.V_11.ActionPart.Next, In, Out);
    break;
  case Tree_NoAttribute:;
    *Out = In;
    break;
  }
}

static void CompBitOffset
# ifdef __STDC__
(Tree_tTree t, SHORTCARD In, SHORTCARD *Out)
# else
(t, In, Out)
Tree_tTree t;
SHORTCARD In;
SHORTCARD *Out;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    CompBitOffset(t->U_1.V_5.Class.Attributes, In, Out);
    CompBitOffset(t->U_1.V_5.Class.Extensions, *Out, Out);
    CompBitOffset(t->U_1.V_5.Class.Next, In, Out);
    break;
  case Tree_NoClass:;
    break;
  case Tree_Child:;
    t->U_1.V_9.Child.BitOffset = In;
    if (t->U_1.V_9.Child.Class != Tree_NoTree) {
      CompBitOffset(t->U_1.V_9.Child.Next, In + t->U_1.V_9.Child.Class->U_1.V_5.Class.BitCount, Out);
    } else {
      CompBitOffset(t->U_1.V_9.Child.Next, In, Out);
    }
    break;
  case Tree_Attribute:;
    CompBitOffset(t->U_1.V_10.Attribute.Next, In, Out);
    break;
  case Tree_ActionPart:;
    CompBitOffset(t->U_1.V_11.ActionPart.Next, In, Out);
    break;
  case Tree_NoAttribute:;
    *Out = In;
    break;
  }
}

static void InitInstance
# ifdef __STDC__
(Tree_tTree t, SHORTCARD Offset, Tree_tInstancePtr InstancePtr)
# else
(t, Offset, InstancePtr)
Tree_tTree t;
SHORTCARD Offset;
Tree_tInstancePtr InstancePtr;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    InitInstance(t->U_1.V_5.Class.BaseClass, Offset, InstancePtr);
    InitInstance(t->U_1.V_5.Class.Attributes, Offset, InstancePtr);
    break;
  case Tree_NoClass:;
    break;
  case Tree_Child:;
    {
      register Tree_tInstance *W_1 = &InstancePtr->A[t->U_1.V_9.Child.AttrIndex - 1];

      W_1->Attribute = t;
      W_1->Properties = t->U_1.V_9.Child.Properties | (SET_ELEM(Tree_Left));
      W_1->Action = (Tree_tTree)ADR(W_1->Action);
    }
    if (t->U_1.V_9.Child.Class != Tree_NoTree) {
      InitInstance1(t->U_1.V_9.Child.Class, t, Offset + t->U_1.V_9.Child.InstOffset, InstancePtr);
    }
    InitInstance(t->U_1.V_9.Child.Next, Offset, InstancePtr);
    break;
  case Tree_Attribute:;
    {
      register Tree_tInstance *W_2 = &InstancePtr->A[t->U_1.V_10.Attribute.AttrIndex - 1];

      W_2->Attribute = t;
      W_2->Properties = t->U_1.V_10.Attribute.Properties | (SET_ELEM(Tree_Left));
      W_2->Action = (Tree_tTree)ADR(W_2->Action);
    }
    InitInstance(t->U_1.V_10.Attribute.Next, Offset, InstancePtr);
    break;
  case Tree_ActionPart:;
    InitInstance(t->U_1.V_11.ActionPart.Next, Offset, InstancePtr);
    break;
  case Tree_NoAttribute:;
    break;
  }
}

static void InitInstance1
# ifdef __STDC__
(Tree_tTree t, Tree_tTree selector, SHORTCARD Offset, Tree_tInstancePtr InstancePtr)
# else
(t, selector, Offset, InstancePtr)
Tree_tTree t, selector;
SHORTCARD Offset;
Tree_tInstancePtr InstancePtr;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    InitInstance1(t->U_1.V_5.Class.BaseClass, selector, Offset, InstancePtr);
    InitInstance1(t->U_1.V_5.Class.Attributes, selector, Offset, InstancePtr);
    break;
  case Tree_NoClass:;
    break;
  case Tree_Child:;
    {
      register Tree_tInstance *W_3 = &InstancePtr->A[Offset + t->U_1.V_9.Child.AttrIndex - 1];

      W_3->Selector = selector;
      W_3->Attribute = t;
      W_3->Properties = t->U_1.V_9.Child.Properties | (SET_ELEM(Tree_Right));
      W_3->Action = (Tree_tTree)ADR(W_3->Action);
    }
    InitInstance1(t->U_1.V_9.Child.Next, selector, Offset, InstancePtr);
    break;
  case Tree_Attribute:;
    {
      register Tree_tInstance *W_4 = &InstancePtr->A[Offset + t->U_1.V_10.Attribute.AttrIndex - 1];

      W_4->Selector = selector;
      W_4->Attribute = t;
      W_4->Properties = t->U_1.V_10.Attribute.Properties | (SET_ELEM(Tree_Right));
      W_4->Action = (Tree_tTree)ADR(W_4->Action);
    }
    InitInstance1(t->U_1.V_10.Attribute.Next, selector, Offset, InstancePtr);
    break;
  case Tree_ActionPart:;
    InitInstance1(t->U_1.V_11.ActionPart.Next, selector, Offset, InstancePtr);
    break;
  case Tree_NoAttribute:;
    break;
  }
}

static void EnterDependency
# ifdef __STDC__
(Sets_tElement argument)
# else
(argument)
Sets_tElement argument;
# endif
{
  Relations_Include(&relation, result, (LONGINT)argument);
}

static void CompDP1
# ifdef __STDC__
(Tree_tTree t, Sets_tSet *Set, INTEGER Usage, BOOLEAN NonBase, BOOLEAN Check)
# else
(t, Set, Usage, NonBase, Check)
Tree_tTree t;
Sets_tSet *Set;
INTEGER Usage;
BOOLEAN NonBase, Check;
# endif
{
  Tree_tTree Attribute, ChildsClass;
  SHORTCARD Offset;

  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    CompDP1(t->U_1.V_5.Class.BaseClass, Set, Usage, FALSE, Check);
    MultipleInheritedActions = FALSE;
    CompDP1(t->U_1.V_5.Class.Attributes, Set, Usage, NonBase, Check);
    break;
  case Tree_NoClass:;
    break;
  case Tree_Attribute:;
    if (t->U_1.V_10.Attribute.AttrIndex != DummyIndex) {
      Relations_Include(&relation, (LONGINT)DummyIndex, (LONGINT)t->U_1.V_10.Attribute.AttrIndex);
    }
    CompDP1(t->U_1.V_10.Attribute.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Child:;
    ChildsClass = t->U_1.V_9.Child.Class;
    if (ChildsClass != Tree_NoTree) {
      if (!IN(Tree_Input, t->U_1.V_9.Child.Properties)) {
        Relations_Include(&relation, (LONGINT)DummyIndex, (LONGINT)t->U_1.V_9.Child.AttrIndex);
        {
          SHORTCARD B_1 = 1, B_2 = ChildsClass->U_1.V_5.Class.AttrCount;

          if (B_1 <= B_2)
            for (i = B_1;; i += 1) {
              Relations_Include(&relation, (LONGINT)(Class->U_1.V_5.Class.AttrCount + t->U_1.V_9.Child.InstOffset + i), (LONGINT)t->U_1.V_9.Child.AttrIndex);
              if (i >= B_2) break;
            }
        }
      }
      Attribute = Tree_IdentifyAttribute(ChildsClass, iNull);
      Offset = Class->U_1.V_5.Class.AttrCount + t->U_1.V_9.Child.InstOffset + Attribute->U_1.V_9.Child.AttrIndex;
      Relations_Include(&relation, (LONGINT)DummyIndex, (LONGINT)Offset);
      INCL(Class->U_1.V_5.Class.Instance->A[Offset - 1].Properties, Tree_Right);
    }
    CompDP1(t->U_1.V_9.Child.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_ActionPart:;
    if (IN(Tree_MultInhComp, t->U_1.V_11.ActionPart.Properties)) {
      MultipleInheritedActions = TRUE;
    }
    CompDP1(t->U_1.V_11.ActionPart.Actions, Set, Usage, NonBase, Check);
    CompDP1(t->U_1.V_11.ActionPart.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_NoAttribute:;
    break;
  case Tree_Assign:;
    if (IsCopy(t->U_1.V_36.Assign.Arguments)) {
      t->U_1.V_1.Kind = Tree_Copy;
    }
    Sets_AssignEmpty(&Results);
    Sets_AssignEmpty(&Arguments);
    CompDP1(t->U_1.V_36.Assign.Results, &Results, (LONGINT)Tree_Write, NonBase, TRUE);
    CompDP1(t->U_1.V_36.Assign.Arguments, &Arguments, (LONGINT)Tree_Read, NonBase, FALSE);
    if (Sets_IsEmpty(Results)) {
      Tree_Error((LONGINT)AssignmentLhsNamesNoAttributes, t->U_1.V_36.Assign.Pos);
    }
    while (!Sets_IsEmpty(Results)) {
      result = Sets_Extract(&Results);
      {
        register Tree_tInstance *W_5 = &Class->U_1.V_5.Class.Instance->A[result - 1];

        if (W_5->Action == ADR(W_5->Action) || IN(Tree_MultInhComp, W_5->Properties) || !MultipleInheritedActions) {
          W_5->Action = t;
          if (t->U_1.V_1.Kind == Tree_Copy) {
            W_5->CopyArg = Sets_Select(&Arguments);
          }
        }
      }
      Sets_ForallDo(Arguments, (Sets_ProcOftElement)EnterDependency);
    }
    CompDP1(t->U_1.V_36.Assign.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Copy:;
    Sets_AssignEmpty(&Results);
    Sets_AssignEmpty(&Arguments);
    CompDP1(t->U_1.V_37.Copy.Results, &Results, (LONGINT)Tree_Write, NonBase, TRUE);
    CompDP1(t->U_1.V_37.Copy.Arguments, &Arguments, (LONGINT)Tree_Read, NonBase, TRUE);
    if (Sets_IsEmpty(Results)) {
      Tree_Error((LONGINT)CopyRuleLhsNamesNoAttributes, t->U_1.V_37.Copy.Pos);
    }
    while (!Sets_IsEmpty(Results)) {
      result = Sets_Extract(&Results);
      {
        register Tree_tInstance *W_6 = &Class->U_1.V_5.Class.Instance->A[result - 1];

        if (W_6->Action == ADR(W_6->Action) || IN(Tree_MultInhComp, W_6->Properties) || !MultipleInheritedActions) {
          W_6->Action = t;
          W_6->CopyArg = Sets_Select(&Arguments);
        }
      }
      Sets_ForallDo(Arguments, (Sets_ProcOftElement)EnterDependency);
    }
    CompDP1(t->U_1.V_37.Copy.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_TargetCode:;
    Sets_AssignEmpty(&Results);
    Sets_AssignEmpty(&Arguments);
    CompDP1(t->U_1.V_38.TargetCode.Results, &Results, (LONGINT)Tree_Write, NonBase, TRUE);
    CompDP1(t->U_1.V_38.TargetCode.Code, &Arguments, (LONGINT)Tree_Read, NonBase, FALSE);
    Sets_Difference(&Arguments, Results);
    if (Sets_IsEmpty(Results) && IsCode(t->U_1.V_38.TargetCode.Code)) {
      Tree_Error((LONGINT)BlockLhsNamesNoAttributes, t->U_1.V_38.TargetCode.Pos);
    }
    while (!Sets_IsEmpty(Results)) {
      result = Sets_Extract(&Results);
      {
        register Tree_tInstance *W_7 = &Class->U_1.V_5.Class.Instance->A[result - 1];

        if (W_7->Action == ADR(W_7->Action) || IN(Tree_MultInhComp, W_7->Properties) || !MultipleInheritedActions) {
          W_7->Action = t;
        }
      }
      Sets_ForallDo(Arguments, (Sets_ProcOftElement)EnterDependency);
    }
    CompDP1(t->U_1.V_38.TargetCode.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Order:;
    Sets_AssignEmpty(&Results);
    Sets_AssignEmpty(&Arguments);
    CompDP1(t->U_1.V_39.Order.Results, &Results, (LONGINT)Tree_Read, NonBase, TRUE);
    CompDP1(t->U_1.V_39.Order.Arguments, &Arguments, (LONGINT)Tree_Read, NonBase, TRUE);
    while (!Sets_IsEmpty(Results)) {
      result = Sets_Extract(&Results);
      Sets_ForallDo(Arguments, (Sets_ProcOftElement)EnterDependency);
    }
    CompDP1(t->U_1.V_39.Order.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Check:;
    if (t->U_1.V_40.Check.Results != Tree_NoTree) {
      Sets_AssignEmpty(&Results);
      Sets_AssignEmpty(&Arguments);
      CompDP1(t->U_1.V_40.Check.Results, &Results, (LONGINT)Tree_Write, NonBase, FALSE);
    }
    if (t->U_1.V_40.Check.Condition != Tree_NoTree) {
      CompDP1(t->U_1.V_40.Check.Condition, &Arguments, (LONGINT)Tree_Read, NonBase, FALSE);
    }
    if (t->U_1.V_40.Check.Statement != Tree_NoTree) {
      CompDP1(t->U_1.V_40.Check.Statement, &Arguments, (LONGINT)Tree_Read, NonBase, FALSE);
    } else {
      Tree_Warning((LONGINT)CheckWithoutStatement, t->U_1.V_40.Check.Pos);
    }
    CompDP1(t->U_1.V_40.Check.Actions, &Arguments, (LONGINT)Tree_Read, NonBase, FALSE);
    if (t->U_1.V_40.Check.Results != Tree_NoTree) {
      result = Sets_Extract(&Results);
      Class->U_1.V_5.Class.Instance->A[result - 1].Action = t;
      Sets_ForallDo(Arguments, (Sets_ProcOftElement)EnterDependency);
      CompDP1(t->U_1.V_40.Check.Next, Set, Usage, NonBase, Check);
    }
    break;
  case Tree_NoAction:;
    break;
  case Tree_Designator:;
    Attribute = Tree_IdentifyAttribute(Class, t->U_1.V_15.Designator.Selector);
    if (Attribute != Tree_NoTree && Attribute->U_1.V_1.Kind == Tree_Child) {
      ChildsClass = Attribute->U_1.V_9.Child.Class;
      Offset = Class->U_1.V_5.Class.AttrCount + Attribute->U_1.V_9.Child.InstOffset;
      INCL(Attribute->U_1.V_9.Child.Properties, Tree_Read);
      if (ChildsClass != Tree_NoTree) {
        Attribute = Tree_IdentifyAttribute(ChildsClass, t->U_1.V_15.Designator.Attribute);
        if (Attribute != Tree_NoTree) {
          Sets_Include(Set, (Sets_tElement)(Offset + Attribute->U_1.V_9.Child.AttrIndex));
          INCL(Attribute->U_1.V_9.Child.Properties, Usage);
          if (Usage == Tree_Write) {
            INCL(Attribute->U_1.V_9.Child.Properties, Tree_Inherited);
            INCL(Class->U_1.V_5.Class.Instance->A[Offset + Attribute->U_1.V_9.Child.AttrIndex - 1].Properties, Tree_Computed);
            if (IN(Tree_Synthesized, Attribute->U_1.V_9.Child.Properties)) {
              Tree_ErrorI((LONGINT)InheritedUseOfSynthesizedAttribute, t->U_1.V_15.Designator.Pos, (LONGINT)Errors_Ident, ADR(t->U_1.V_15.Designator.Attribute));
            }
            {
              register Tree_tInstance *W_8 = &Class->U_1.V_5.Class.Instance->A[Offset + Attribute->U_1.V_9.Child.AttrIndex - 1];

              if (NonBase && !MultipleInheritedActions && IN(Tree_NonBaseComp, W_8->Properties) && !IN(Tree_MultInhComp, W_8->Properties)) {
                Tree_ErrorI((LONGINT)AttributeMultipleComputed, t->U_1.V_15.Designator.Pos, (LONGINT)Errors_Ident, ADR(t->U_1.V_15.Designator.Attribute));
              }
              if (!MultipleInheritedActions || IN(Tree_MultInhComp, W_8->Properties)) {
                EXCL(W_8->Properties, Tree_MultInhComp);
                if (NonBase) {
                  INCL(W_8->Properties, Tree_NonBaseComp);
                }
                if (MultipleInheritedActions) {
                  INCL(W_8->Properties, Tree_MultInhComp);
                }
              }
            }
          }
        } else if (Check) {
          Tree_ErrorI((LONGINT)ChildsClassHasNoSuchAttribute, t->U_1.V_15.Designator.Pos, (LONGINT)Errors_Ident, ADR(t->U_1.V_15.Designator.Attribute));
        }
      }
    } else if (Check) {
      Tree_ErrorI((LONGINT)NoSuchChild, t->U_1.V_15.Designator.Pos, (LONGINT)Errors_Ident, ADR(t->U_1.V_15.Designator.Selector));
    }
    CompDP1(t->U_1.V_15.Designator.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Ident:;
    Attribute = Tree_IdentifyAttribute(Class, t->U_1.V_16.Ident.Attribute);
    if (Attribute != Tree_NoTree) {
      Sets_Include(Set, (Sets_tElement)Attribute->U_1.V_9.Child.AttrIndex);
      INCL(Attribute->U_1.V_9.Child.Properties, Usage);
      if (Usage == Tree_Write) {
        INCL(Attribute->U_1.V_9.Child.Properties, Tree_Synthesized);
        INCL(Class->U_1.V_5.Class.Instance->A[Attribute->U_1.V_9.Child.AttrIndex - 1].Properties, Tree_Computed);
        if (IN(Tree_Inherited, Attribute->U_1.V_9.Child.Properties)) {
          Tree_ErrorI((LONGINT)SynthesizedUseOfInheritedAttribute, t->U_1.V_16.Ident.Pos, (LONGINT)Errors_Ident, ADR(t->U_1.V_16.Ident.Attribute));
        }
        {
          register Tree_tInstance *W_9 = &Class->U_1.V_5.Class.Instance->A[Attribute->U_1.V_9.Child.AttrIndex - 1];

          if (NonBase && !MultipleInheritedActions && IN(Tree_NonBaseComp, W_9->Properties) && !IN(Tree_MultInhComp, W_9->Properties)) {
            Tree_ErrorI((LONGINT)AttributeMultipleComputed, t->U_1.V_16.Ident.Pos, (LONGINT)Errors_Ident, ADR(t->U_1.V_16.Ident.Attribute));
          }
          if (!MultipleInheritedActions || IN(Tree_MultInhComp, W_9->Properties)) {
            EXCL(W_9->Properties, Tree_MultInhComp);
            if (NonBase) {
              INCL(W_9->Properties, Tree_NonBaseComp);
            }
            if (MultipleInheritedActions) {
              INCL(W_9->Properties, Tree_MultInhComp);
            }
          }
        }
      }
    } else if (Check) {
      Tree_ErrorI((LONGINT)NoSuchAttribute, t->U_1.V_16.Ident.Pos, (LONGINT)Errors_Ident, ADR(t->U_1.V_16.Ident.Attribute));
    }
    CompDP1(t->U_1.V_16.Ident.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Remote:;
    CompDP1(t->U_1.V_17.Remote.Designators, Set, Usage, NonBase, Check);
    CompDP1(t->U_1.V_17.Remote.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Any:;
    CompDP1(t->U_1.V_18.Any.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_Anys:;
    CompDP1(t->U_1.V_19.Anys.Next, Set, Usage, NonBase, Check);
    break;
  case Tree_NoDesignator:;
    break;
  }
}

static BOOLEAN IsCode
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Designator:;
  case Tree_Ident:;
  case Tree_Remote:;
    return TRUE;
    break;
  case Tree_Any:;
    return IsCode(t->U_1.V_18.Any.Next);
    break;
  case Tree_Anys:;
    return IsCode(t->U_1.V_19.Anys.Next);
    break;
  case Tree_NoDesignator:;
    return FALSE;
    break;
  }
}

static Tree_tTree CopyTree
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_10 = &t->U_1.V_10.Attribute;

      return Tree_mAttribute(CopyTree(W_10->Next), W_10->Name, W_10->Type, W_10->Properties, W_10->Pos);
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_11 = &t->U_1.V_9.Child;

      return Tree_mChild(CopyTree(W_11->Next), W_11->Name, W_11->Type, W_11->Properties, W_11->Pos);
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_12 = &t->U_1.V_11.ActionPart;

      return Tree_mActionPart(CopyTree(W_12->Next), W_12->Actions);
    }
    break;
  case Tree_NoAttribute:;
    return Tree_nNoAttribute;
    break;
  }
}

static void ExpandMultiple
# ifdef __STDC__
(Tree_tTree Class)
# else
(Class)
Tree_tTree Class;
# endif
{
  Tree_tTree Node, class;

  {
    register Tree_yClass *W_13 = &Class->U_1.V_5.Class;

    if (!IN(Tree_Mark, W_13->Properties)) {
      INCL(W_13->Properties, Tree_Mark);
      if (W_13->BaseClass->U_1.V_1.Kind == Tree_Class) {
        ExpandMultiple(W_13->BaseClass);
      }
      Node = W_13->Names;
      while (Node->U_1.V_1.Kind == Tree_Name) {
        {
          register Tree_yName *W_14 = &Node->U_1.V_25.Name;

          class = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_14->Name);
          if (class != Tree_NoTree) {
            ExpandMultiple(class);
            TheClass = Class;
            Tree_ForallAttributes(class, (Tree_ProcOfT)ExpandMultiple2);
          }
          Node = W_14->Next;
        }
      }
      EXCL(W_13->Properties, Tree_Mark);
    }
  }
}

static void AppendAttr
# ifdef __STDC__
(Tree_tTree *Attributes, Tree_tTree Attribute)
# else
(Attributes, Attribute)
Tree_tTree *Attributes;
Tree_tTree Attribute;
# endif
{
  if ((*Attributes)->U_1.V_1.Kind == Tree_NoAttribute) {
    Attribute->U_1.V_8.AttrOrAction.Next = *Attributes;
    *Attributes = Attribute;
  } else {
    AppendAttr(&(*Attributes)->U_1.V_8.AttrOrAction.Next, Attribute);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Semantics, routine ", 33L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Semantics_Exit)();
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
    LONGINT B_3 = 0, B_4 = (INTEGER)(O_3 - 1);

    if (B_3 <= B_4)
      for (yyi = B_3;; yyi += 1) {
        if (yya[yyi] != yyb[yyi]) {
          FREE_OPEN_ARRAYS
          return FALSE;
        }
        if (yyi >= B_4) break;
      }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

void Semantics_Semantics
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Ag:;
    {
      register Tree_yAg *W_15 = &t->U_1.V_26.Ag;

      Tree_InitIdentifyClass(W_15->Classes);
      Tree_ForallClasses(W_15->Classes, (Tree_ProcOfT)StampItems);
      StampItems(W_15->Modules);
      ExpandProps(W_15->Props);
      ExpandProps(W_15->Modules);
      if (IN(Tree_Ignore, W_15->Properties)) {
        ProcessIgnore(W_15->ParserCodes);
        ProcessIgnore(W_15->TreeCodes);
        ProcessIgnore(W_15->EvalCodes);
      }
      ProcessIgnore(W_15->Decls);
      Tree_ForallClasses(W_15->Classes, (Tree_ProcOfT)ProcessIgnore);
      ProcessIgnore(W_15->Modules);
      ExpandModules(W_15->Decls);
      ExpandModules(W_15->Modules);
      if (Sets_IsElement(ORD('c'), &Tree_Options)) {
        Strings_ArrayToString((STRING)"bool", 4L, &String);
      } else {
        Strings_ArrayToString((STRING)"BOOLEAN", 7L, &String);
      }
      Ident = Idents_MakeIdent(&String);
      Semantics_TypeCount = Idents_MaxIdent();
      Sets_MakeSet(&Tree_TypeNames, (Sets_tElement)Semantics_TypeCount);
      Sets_Include(&Tree_TypeNames, (Sets_tElement)Ident);
      Semantics_Semantics(W_15->Classes);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_16 = &t->U_1.V_5.Class;

      CompBaseClass(t, Tree_nNoClass);
      Tree_ForallClasses(t, (Tree_ProcOfT)ExpandMultiple);
      Tree_ClassCount = 0;
      Sets_MakeSet(&CodesUsed, (Sets_tElement)Idents_MaxIdent());
      Tree_ForallClasses(t, (Tree_ProcOfT)CountClasses);
      Tree_ForallClasses(t, (Tree_ProcOfT)CheckReverse);
      INCL(t->U_1.V_5.Class.Properties, Tree_Referenced);
      CompReachable(t);
      if (Sets_IsElement(ORD('x'), &Tree_Options) || Sets_IsElement(ORD('z'), &Tree_Options) || Sets_IsElement(ORD('u'), &Tree_Options)) {
        TokenCode = 0;
        Tree_ForallClasses(t, (Tree_ProcOfT)CodeTerminals);
        ActionName = 0;
        i = 0;
        CompChildIndex(t, &i);
        i = 0;
        CompParsIndex(t, &i);
        Tree_ForallClasses(t, (Tree_ProcOfT)CheckUsage2);
      }
      Tree_ForallClasses(t, (Tree_ProcOfT)ExpandChecks);
      Tree_ForallClasses(t, (Tree_ProcOfT)Identify);
      Sets_MakeSet(&ClassNames, (Sets_tElement)Idents_MaxIdent());
      Sets_MakeSet(&SelectorNames, (Sets_tElement)Idents_MaxIdent());
      Sets_MakeSet(&VariantNames, (Sets_tElement)Idents_MaxIdent());
      Sets_MakeSet(&PrecNames, (Sets_tElement)Idents_MaxIdent());
      CheckNames(Tree_TreeRoot->U_1.V_26.Ag.Precs);
      Tree_ForallClasses(t, (Tree_ProcOfT)CheckNames);
      Sets_ReleaseSet(&ClassNames);
      Sets_ReleaseSet(&SelectorNames);
      Sets_ReleaseSet(&VariantNames);
      Sets_ReleaseSet(&PrecNames);
      Sets_ReleaseSet(&CodesUsed);
      Tree_ForallClasses(t, (Tree_ProcOfT)CheckDesignator);
      CompBitCount(t, 1, &i);
      CompBitOffset(t, 0, &i);
      if (Sets_IsElement(ORD('.'), &Tree_Options)) {
        CompIndex(t, 0, &i);
        CompInstance(t, 0, &i);
        Sets_MakeSet(&Tree_MaxSet, (Sets_tElement)MaxInstCount);
        Sets_Complement(&Tree_MaxSet);
        Tree_ForallClasses(t, (Tree_ProcOfT)InitInstance0);
        Tree_ForallClasses(t, (Tree_ProcOfT)CompDP);
        if (Sets_IsElement(ORD('2'), &Tree_Options)) {
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Inherited Attribute Computation Rules", 37L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"-------------------------------------", 37L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteNl((System_tFile)IO_StdOutput);
        }
        Tree_ForallClasses(t, (Tree_ProcOfT)CopyProperties);
        Tree_ForallClasses(t, (Tree_ProcOfT)CheckInherited);
        if (Sets_IsElement(ORD('1'), &Tree_Options)) {
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Inserted Copy Rules", 19L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"-------------------", 19L);
          IO_WriteNl((System_tFile)IO_StdOutput);
          IO_WriteNl((System_tFile)IO_StdOutput);
        }
        Success = TRUE;
        Tree_ForallClasses(t, (Tree_ProcOfT)CheckComplete);
        if (Success) {
          INCL(Tree_GrammarClass, Tree_cLNC);
        }
        if (CopyInherited > 0) {
          Tree_InformationI((LONGINT)CopyRuleInsertionsInherited, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Integer, ADR(CopyInherited));
        }
        if (CopySynthesized > 0) {
          Tree_InformationI((LONGINT)CopyRuleInsertionsSynthesized, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Integer, ADR(CopySynthesized));
        }
        if (CopyThreaded > 0) {
          Tree_InformationI((LONGINT)CopyRuleInsertionsThreaded, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Integer, ADR(CopyThreaded));
        }
        Tree_ForallClasses(t, (Tree_ProcOfT)CheckUsage);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void StampItems
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Module:;
    {
      register Tree_yModule *W_17 = &t->U_1.V_43.Module;

      Tree_ForallClasses(W_17->Classes, (Tree_ProcOfT)StampItems);
      StampItems(W_17->Next);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_18 = &t->U_1.V_5.Class;

      if (IN(Tree_Abstract, W_18->Properties)) {
        Tree_ForallAttributes(W_18->Attributes, (Tree_ProcOfT)StampItems);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_19 = &t->U_1.V_9.Child;

      INC(ItemCount);
      W_19->Item = ItemCount;
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_20 = &t->U_1.V_10.Attribute;

      INC(ItemCount);
      W_20->Item = ItemCount;
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_21 = &t->U_1.V_11.ActionPart;

      INC(ItemCount);
      W_21->Item = ItemCount;
      return;
    }
    break;
  default :
    break;
  }
}

static void ExpandProps
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
  case Tree_Module:;
    {
      register Tree_yModule *W_22 = &t->U_1.V_43.Module;

      ExpandProps(W_22->Props);
      ExpandProps(W_22->Next);
      return;
    }
    break;
  case Tree_Prop:;
    {
      register Tree_yProp *W_23 = &t->U_1.V_46.Prop;

      ActProperties = W_23->Properties;
      ExpandProps(W_23->Names);
      ExpandProps(W_23->Next);
      return;
    }
    break;
  case Tree_Select:;
    {
      register Tree_ySelect *W_24 = &t->U_1.V_47.Select;

      CheckSelect(W_24->Names);
      ActProperties = SET_ELEM(Tree_Ignore);
      if (!LookUp(Tree_TreeRoot->U_1.V_26.Ag.Name, W_24->Names)) {
        Tree_TreeRoot->U_1.V_26.Ag.Properties = Tree_TreeRoot->U_1.V_26.Ag.Properties | ActProperties;
        ExpandProps(Tree_TreeRoot->U_1.V_26.Ag.Decls);
        Tree_ForallClasses(Tree_TreeRoot->U_1.V_26.Ag.Classes, (Tree_ProcOfT)ExpandProps);
      }
      Module = Tree_TreeRoot->U_1.V_26.Ag.Modules;
      while (Module->U_1.V_1.Kind == Tree_Module) {
        if (!LookUp(Module->U_1.V_43.Module.Name, W_24->Names)) {
          Module->U_1.V_43.Module.Properties = Module->U_1.V_43.Module.Properties | ActProperties;
          ExpandProps(Module->U_1.V_43.Module.Decls);
          Tree_ForallClasses(Module->U_1.V_43.Module.Classes, (Tree_ProcOfT)ExpandProps);
        }
        Module = Module->U_1.V_43.Module.Next;
      }
      ExpandProps(W_24->Next);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_25 = &t->U_1.V_25.Name;

      if (W_25->Name == Tree_TreeRoot->U_1.V_26.Ag.Name) {
        Tree_TreeRoot->U_1.V_26.Ag.Properties = Tree_TreeRoot->U_1.V_26.Ag.Properties | ActProperties;
        ExpandProps(Tree_TreeRoot->U_1.V_26.Ag.Decls);
        Tree_ForallClasses(Tree_TreeRoot->U_1.V_26.Ag.Classes, (Tree_ProcOfT)ExpandProps);
      } else {
        Module = Tree_IdentifyModule(Tree_TreeRoot->U_1.V_26.Ag.Modules, W_25->Name);
        if (Module == Tree_NoTree) {
          Tree_WarningI((LONGINT)ModuleNotDeclared, t->U_1.V_25.Name.Pos, (LONGINT)Errors_Ident, ADR(W_25->Name));
        } else {
          Module->U_1.V_43.Module.Properties = Module->U_1.V_43.Module.Properties | ActProperties;
          ExpandProps(Module->U_1.V_43.Module.Decls);
          Tree_ForallClasses(Module->U_1.V_43.Module.Classes, (Tree_ProcOfT)ExpandProps);
        }
      }
      ExpandProps(W_25->Next);
      return;
    }
    break;
  case Tree_Decl:;
    {
      register Tree_yDecl *W_26 = &t->U_1.V_50.Decl;

      Tree_ForallAttributes(W_26->Attributes, (Tree_ProcOfT)ExpandProps);
      ExpandProps(W_26->Next);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_27 = &t->U_1.V_5.Class;

      W_27->Properties = W_27->Properties | ActProperties;
      Tree_ForallAttributes(W_27->Attributes, (Tree_ProcOfT)ExpandProps);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_28 = &t->U_1.V_9.Child;

      W_28->Properties = W_28->Properties | ActProperties;
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_29 = &t->U_1.V_10.Attribute;

      W_29->Properties = W_29->Properties | ActProperties;
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_30 = &t->U_1.V_11.ActionPart;

      W_30->Properties = W_30->Properties | ActProperties;
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckSelect
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
  if (t->U_1.V_1.Kind == Tree_Name) {
    {
      register Tree_yName *W_31 = &t->U_1.V_25.Name;

      if (!(W_31->Name == Tree_TreeRoot->U_1.V_26.Ag.Name || Tree_IdentifyModule(Tree_TreeRoot->U_1.V_26.Ag.Modules, W_31->Name) != Tree_NoTree)) {
        Tree_WarningI((LONGINT)ModuleNotDeclared, t->U_1.V_25.Name.Pos, (LONGINT)Errors_Ident, ADR(W_31->Name));
      }
      CheckSelect(W_31->Next);
      return;
    }
  }
}

static void ProcessIgnore
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
  case Tree_Module:;
    {
      register Tree_yModule *W_32 = &t->U_1.V_43.Module;

      if (IN(Tree_Ignore, W_32->Properties)) {
        ProcessIgnore(W_32->ParserCodes);
        ProcessIgnore(W_32->TreeCodes);
        ProcessIgnore(W_32->EvalCodes);
      }
      ProcessIgnore(W_32->Decls);
      Tree_ForallClasses(W_32->Classes, (Tree_ProcOfT)ProcessIgnore);
      ProcessIgnore(W_32->Next);
      return;
    }
    break;
  case Tree_Codes:;
    {
      register Tree_yCodes *W_33 = &t->U_1.V_12.Codes;

      Texts_MakeText(&W_33->Export);
      Texts_MakeText(&W_33->Import);
      Texts_MakeText(&W_33->Global);
      Texts_MakeText(&W_33->Local);
      Texts_MakeText(&W_33->Begin);
      Texts_MakeText(&W_33->Close);
      return;
    }
    break;
  case Tree_Decl:;
    {
      register Tree_yDecl *W_34 = &t->U_1.V_50.Decl;

      W_34->Attributes = ProcessIgnore2(W_34->Attributes);
      ProcessIgnore(W_34->Next);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_35 = &t->U_1.V_5.Class;

      W_35->Attributes = ProcessIgnore2(W_35->Attributes);
      if (IN(Tree_Ignore, W_35->Properties)) {
        W_35->Names = Tree_nNoName;
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void ExpandModules
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
  case Tree_Module:;
    {
      register Tree_yModule *W_36 = &t->U_1.V_43.Module;

      ExpandModules(W_36->Decls);
      ExpandModules(W_36->Classes);
      ExpandModules(W_36->Next);
      return;
    }
    break;
  case Tree_Decl:;
    {
      register Tree_yDecl *W_37 = &t->U_1.V_50.Decl;

      Attribute = W_37->Attributes;
      ActProperties = W_37->Properties;
      ExpandModules(W_37->Names);
      ExpandModules(W_37->Next);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_38 = &t->U_1.V_25.Name;

      Class = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_38->Name);
      if (Class == Tree_NoTree) {
        if (Tree_TreeRoot->U_1.V_26.Ag.Classes->U_1.V_1.Kind == Tree_NoClass) {
          Tree_TreeRoot->U_1.V_26.Ag.Classes = Tree_mClass(W_38->Name, ActProperties, CopyTree(Attribute), Tree_nNoClass, Tree_TreeRoot->U_1.V_26.Ag.Classes, W_38->Name, W_38->Pos, 0, Idents_NoIdent, Tree_nNoName);
          Tree_InitIdentifyClass2(Tree_TreeRoot->U_1.V_26.Ag.Classes);
        } else {
          Node = Tree_TreeRoot->U_1.V_26.Ag.Classes;
          while (Node->U_1.V_5.Class.Next->U_1.V_1.Kind != Tree_NoClass) {
            Node = Node->U_1.V_5.Class.Next;
          }
          Node->U_1.V_5.Class.Next = Tree_mClass(W_38->Name, ActProperties, CopyTree(Attribute), Tree_nNoClass, Node->U_1.V_5.Class.Next, W_38->Name, W_38->Pos, 0, Idents_NoIdent, Tree_nNoName);
          Tree_InitIdentifyClass2(Node->U_1.V_5.Class.Next);
        }
      } else {
        if (Class->U_1.V_5.Class.Attributes->U_1.V_1.Kind == Tree_NoAttribute) {
          Class->U_1.V_5.Class.Attributes = CopyTree(Attribute);
        } else {
          Node = Class->U_1.V_5.Class.Attributes;
          while (Node->U_1.V_10.Attribute.Next->U_1.V_1.Kind != Tree_NoAttribute) {
            Node = Node->U_1.V_10.Attribute.Next;
          }
          Node->U_1.V_10.Attribute.Next = CopyTree(Attribute);
        }
      }
      ExpandModules(W_38->Next);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_39 = &t->U_1.V_5.Class;

      Class = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_39->Name);
      Tree_ForallClasses(W_39->Extensions, (Tree_ProcOfT)Tree_InitIdentifyClass2);
      if (Class == Tree_NoTree) {
        if (Tree_TreeRoot->U_1.V_26.Ag.Classes->U_1.V_1.Kind == Tree_NoClass) {
          Tree_TreeRoot->U_1.V_26.Ag.Classes = Tree_mClass(W_39->Name, W_39->Properties, W_39->Attributes, W_39->Extensions, Tree_TreeRoot->U_1.V_26.Ag.Classes, W_39->Selector, W_39->Pos, W_39->Code, W_39->Prec, W_39->Names);
          Tree_InitIdentifyClass2(Tree_TreeRoot->U_1.V_26.Ag.Classes);
        } else {
          Node = Tree_TreeRoot->U_1.V_26.Ag.Classes;
          while (Node->U_1.V_5.Class.Next->U_1.V_1.Kind != Tree_NoClass) {
            Node = Node->U_1.V_5.Class.Next;
          }
          Node->U_1.V_5.Class.Next = Tree_mClass(W_39->Name, W_39->Properties, W_39->Attributes, W_39->Extensions, Node->U_1.V_5.Class.Next, W_39->Selector, W_39->Pos, W_39->Code, W_39->Prec, W_39->Names);
          Tree_InitIdentifyClass2(Node->U_1.V_5.Class.Next);
        }
      } else {
        if (Class->U_1.V_5.Class.Attributes->U_1.V_1.Kind == Tree_NoAttribute) {
          Class->U_1.V_5.Class.Attributes = W_39->Attributes;
        } else {
          Node = Class->U_1.V_5.Class.Attributes;
          while (Node->U_1.V_10.Attribute.Next->U_1.V_1.Kind != Tree_NoAttribute) {
            Node = Node->U_1.V_10.Attribute.Next;
          }
          Node->U_1.V_10.Attribute.Next = W_39->Attributes;
        }
        if (Class->U_1.V_5.Class.Extensions->U_1.V_1.Kind == Tree_NoClass) {
          Class->U_1.V_5.Class.Extensions = W_39->Extensions;
        } else {
          Node = Class->U_1.V_5.Class.Extensions;
          while (Node->U_1.V_5.Class.Next->U_1.V_1.Kind != Tree_NoClass) {
            Node = Node->U_1.V_5.Class.Next;
          }
          Node->U_1.V_5.Class.Next = W_39->Extensions;
        }
        if (Class->U_1.V_5.Class.Names->U_1.V_1.Kind == Tree_NoName) {
          Class->U_1.V_5.Class.Names = W_39->Names;
        } else {
          Node = Class->U_1.V_5.Class.Names;
          while (Node->U_1.V_25.Name.Next->U_1.V_1.Kind != Tree_NoName) {
            Node = Node->U_1.V_25.Name.Next;
          }
          Node->U_1.V_25.Name.Next = W_39->Names;
        }
      }
      ExpandModules(W_39->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void ExpandChecks
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
      register Tree_yClass *W_40 = &t->U_1.V_5.Class;

      Class = t;
      ExpandChecks(W_40->Attributes);
      if (W_40->BaseClass->U_1.V_1.Kind == Tree_NoClass) {
        W_40->Attributes = Tree_mAttribute(W_40->Attributes, iNull, iNull, SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Computed) | SET_ELEM(Tree_Dummy), Positions_NoPosition);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_41 = &t->U_1.V_9.Child;

      ExpandChecks(W_41->Next);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_42 = &t->U_1.V_10.Attribute;

      ExpandChecks(W_42->Next);
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_43 = &t->U_1.V_11.ActionPart;

      ExpandChecks(W_43->Actions);
      ExpandChecks(W_43->Next);
      return;
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_44 = &t->U_1.V_36.Assign;

      ExpandChecks(W_44->Next);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_45 = &t->U_1.V_37.Copy;

      ExpandChecks(W_45->Next);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_46 = &t->U_1.V_38.TargetCode;

      ExpandChecks(W_46->Next);
      return;
    }
    break;
  case Tree_Order:;
    {
      register Tree_yOrder *W_47 = &t->U_1.V_39.Order;

      ExpandChecks(W_47->Next);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_48 = &t->U_1.V_40.Check;

      if (W_48->Results == Tree_NoTree) {
        INC(ChecksCount);
        Strings_IntToString(ChecksCount, &String);
        Ident = Idents_MakeIdent(&String);
        Class->U_1.V_5.Class.Attributes = Tree_mAttribute(Class->U_1.V_5.Class.Attributes, Ident, Ident, SET_ELEM(Tree_Test), Positions_NoPosition);
        W_48->Results = Tree_mIdent(Ident, Positions_NoPosition, Tree_nNoDesignator);
      } else {
        Class->U_1.V_5.Class.Attributes = Tree_mAttribute(Class->U_1.V_5.Class.Attributes, W_48->Results->U_1.V_16.Ident.Attribute, W_48->Results->U_1.V_16.Ident.Attribute, SET_ELEM(Tree_Test), Positions_NoPosition);
      }
      ExpandChecks(W_48->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void ExpandMultiple2
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
  case Tree_Child:;
    {
      register Tree_yChild *W_49 = &t->U_1.V_9.Child;

      if (!Tree_HasItem(TheClass, W_49->Item)) {
        Node = Tree_mChild((Tree_tTree)Tree_NoTree, W_49->Name, W_49->Type, W_49->Properties, W_49->Pos);
        Node->U_1.V_8.AttrOrAction.Item = W_49->Item;
        AppendAttr(&TheClass->U_1.V_5.Class.Attributes, Node);
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_50 = &t->U_1.V_10.Attribute;

      if (!Tree_HasItem(TheClass, W_50->Item)) {
        Node = Tree_mAttribute((Tree_tTree)Tree_NoTree, W_50->Name, W_50->Type, W_50->Properties, W_50->Pos);
        Node->U_1.V_8.AttrOrAction.Item = W_50->Item;
        AppendAttr(&TheClass->U_1.V_5.Class.Attributes, Node);
      }
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_51 = &t->U_1.V_11.ActionPart;

      if (!Tree_HasItem(TheClass, W_51->Item)) {
        Node = Tree_mActionPart((Tree_tTree)Tree_NoTree, W_51->Actions);
        Node->U_1.V_8.AttrOrAction.Item = W_51->Item;
        INCL(Node->U_1.V_11.ActionPart.Properties, Tree_MultInhComp);
        AppendAttr(&TheClass->U_1.V_5.Class.Attributes, Node);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CountClasses
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
      register Tree_yClass *W_52 = &t->U_1.V_5.Class;

      if (!IN(Tree_Abstract, W_52->Properties)) {
        INC(Tree_ClassCount);
      }
      ChildCount = 0;
      AttributeCount = 0;
      ActionCount = 0;
      Class = t;
      Tree_ForallAttributes(t, (Tree_ProcOfT)CountClasses);
      if (ChildCount > 0) {
        INCL(t->U_1.V_5.Class.Properties, Tree_HasChildren);
      }
      if (AttributeCount > 0) {
        INCL(t->U_1.V_5.Class.Properties, Tree_HasAttributes);
      }
      if (ActionCount > 0) {
        INCL(t->U_1.V_5.Class.Properties, Tree_HasActions);
      }
      if (IN(Tree_Terminal, W_52->Properties) && W_52->Code != 0) {
        if (Sets_IsElement((Sets_tElement)W_52->Code, &CodesUsed)) {
          Tree_ErrorI((LONGINT)TerminalCodeMultipleUsed, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Integer, ADR(W_52->Code));
        }
        Sets_Include(&CodesUsed, (Sets_tElement)W_52->Code);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_53 = &t->U_1.V_9.Child;

      INC(ChildCount);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_54 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_54->Properties) == 0X0L) {
        Sets_Include(&Tree_TypeNames, (Sets_tElement)W_54->Type);
        if (IN(Tree_Nonterminal, Class->U_1.V_5.Class.Properties) || W_54->Name != Tree_iPosition) {
          INC(AttributeCount);
        }
      }
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_55 = &t->U_1.V_11.ActionPart;

      INC(ActionCount);
      return;
    }
    break;
  default :
    break;
  }
}

static void CompReachable
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
    for (;;) {
      {
        register Tree_yClass *W_56 = &t->U_1.V_5.Class;

        if (!!IN(Tree_Reachable, W_56->Properties)) {
          goto EXIT_1;
        }
        INCL(W_56->Properties, Tree_Reachable);
        Tree_ForallAttributes(W_56->Attributes, (Tree_ProcOfT)CompReachable);
        Tree_ForallClasses(W_56->Extensions, (Tree_ProcOfT)CompReachable);
        return;
      }
    } EXIT_1:;
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_57 = &t->U_1.V_9.Child;

      W_57->Class = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_57->Type);
      if (W_57->Class != Tree_NoTree) {
        INCL(W_57->Class->U_1.V_5.Class.Properties, Tree_Referenced);
        CompReachable(W_57->Class);
      } else {
        if (!Sets_IsElement(ORD('j'), &Tree_Options)) {
          Tree_WarningI((LONGINT)NodeTypeNotDeclared, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_57->Type));
        }
        if (Tree_TreeRoot->U_1.V_26.Ag.Classes->U_1.V_1.Kind == Tree_NoClass) {
          Tree_TreeRoot->U_1.V_26.Ag.Classes = Tree_mClass(W_57->Type, SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Implicit) | SET_ELEM(Tree_Reachable) | SET_ELEM(Tree_Referenced), Tree_nNoAttribute, Tree_nNoClass, Tree_TreeRoot->U_1.V_26.Ag.Classes, W_57->Type, W_57->Pos, 0, Idents_NoIdent, Tree_nNoName);
          Tree_InitIdentifyClass2(Tree_TreeRoot->U_1.V_26.Ag.Classes);
          Tree_TreeRoot->U_1.V_26.Ag.Classes->U_1.V_5.Class.BaseClass = Tree_nNoClass;
          W_57->Class = Tree_TreeRoot->U_1.V_26.Ag.Classes;
        } else {
          Node = Tree_TreeRoot->U_1.V_26.Ag.Classes;
          while (Node->U_1.V_5.Class.Next->U_1.V_1.Kind != Tree_NoClass) {
            Node = Node->U_1.V_5.Class.Next;
          }
          Node->U_1.V_5.Class.Next = Tree_mClass(W_57->Type, SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Implicit) | SET_ELEM(Tree_Reachable) | SET_ELEM(Tree_Referenced), Tree_nNoAttribute, Tree_nNoClass, Node->U_1.V_5.Class.Next, W_57->Type, W_57->Pos, 0, Idents_NoIdent, Tree_nNoName);
          Tree_InitIdentifyClass2(Node->U_1.V_5.Class.Next);
          Node->U_1.V_5.Class.Next->U_1.V_5.Class.BaseClass = Tree_nNoClass;
          W_57->Class = Node->U_1.V_5.Class.Next;
        }
        INC(Tree_ClassCount);
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CodeTerminals
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_58 = &t->U_1.V_5.Class;

      if (SET_IS_SUBSET1(SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Referenced), W_58->Properties) && W_58->Code == 0) {
        do {
          INC(TokenCode);
        } while (!!Sets_IsElement((Sets_tElement)TokenCode, &CodesUsed));
        W_58->Code = TokenCode;
      }
      if (IN(Tree_Terminal, W_58->Properties) && W_58->BaseClass->U_1.V_1.Kind == Tree_NoClass) {
        W_58->Attributes = Tree_mAttribute(W_58->Attributes, Tree_iPosition, Tree_itPosition, SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Computed) | SET_ELEM(Tree_Input) | SET_ELEM(Tree_Read), Positions_NoPosition);
      }
      return;
    }
  }
}

static void CheckReverse
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
      register Tree_yClass *W_59 = &t->U_1.V_5.Class;

      if (W_59->Extensions->U_1.V_1.Kind == Tree_NoClass) {
        ReverseCount = 0;
        Tree_ForallAttributes(t, (Tree_ProcOfT)CheckReverse);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_60 = &t->U_1.V_9.Child;

      if (IN(Tree_Reverse, W_60->Properties)) {
        INC(ReverseCount);
        if (ReverseCount > 1) {
          Tree_Error((LONGINT)OnlyOneReverseAllowedInNodeType, t->U_1.V_9.Child.Pos);
        }
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckNames
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
      register Tree_yClass *W_61 = &t->U_1.V_5.Class;

      if (Sets_IsElement((Sets_tElement)W_61->Name, &ClassNames)) {
        Tree_ErrorI((LONGINT)NodeTypeMultipleDeclared, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_61->Name));
      }
      Sets_Include(&ClassNames, (Sets_tElement)W_61->Name);
      if (IN(Tree_Terminal, W_61->Properties)) {
        if (Sets_IsElement((Sets_tElement)W_61->Selector, &VariantNames)) {
          Tree_ErrorI((LONGINT)VariantSelectorMultipleDeclared, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_61->Selector));
        }
        Sets_Include(&VariantNames, (Sets_tElement)W_61->Selector);
      }
      if (W_61->Prec != Idents_NoIdent && !Sets_IsElement((Sets_tElement)W_61->Prec, &PrecNames)) {
        Tree_ErrorI((LONGINT)PrecedenceNotDeclared, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_61->Prec));
      }
      if (W_61->Extensions->U_1.V_1.Kind == Tree_NoClass) {
        Sets_AssignEmpty(&SelectorNames);
        Tree_ForallAttributes(t, (Tree_ProcOfT)CheckNames);
      }
      CheckNames2(W_61->Names);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_62 = &t->U_1.V_9.Child;

      if (Sets_IsElement((Sets_tElement)W_62->Name, &SelectorNames)) {
        if (!(Sets_IsElement(ORD('x'), &Tree_Options) || Sets_IsElement(ORD('z'), &Tree_Options) || Sets_IsElement(ORD('u'), &Tree_Options))) {
          Tree_ErrorI((LONGINT)SelectorMultipleDeclared, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_62->Name));
        }
      }
      Sets_Include(&SelectorNames, (Sets_tElement)W_62->Name);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_63 = &t->U_1.V_10.Attribute;

      if (Sets_IsElement((Sets_tElement)W_63->Name, &SelectorNames)) {
        Tree_ErrorI((LONGINT)SelectorMultipleDeclared, t->U_1.V_10.Attribute.Pos, (LONGINT)Errors_Ident, ADR(W_63->Name));
      }
      Sets_Include(&SelectorNames, (Sets_tElement)W_63->Name);
      return;
    }
    break;
  case Tree_LeftAssoc:;
    {
      register Tree_yLeftAssoc *W_64 = &t->U_1.V_30.LeftAssoc;

      CheckNames(W_64->Names);
      CheckNames(W_64->Next);
      return;
    }
    break;
  case Tree_RightAssoc:;
    {
      register Tree_yRightAssoc *W_65 = &t->U_1.V_31.RightAssoc;

      CheckNames(W_65->Names);
      CheckNames(W_65->Next);
      return;
    }
    break;
  case Tree_NonAssoc:;
    {
      register Tree_yNonAssoc *W_66 = &t->U_1.V_32.NonAssoc;

      CheckNames(W_66->Names);
      CheckNames(W_66->Next);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_67 = &t->U_1.V_25.Name;

      if (Sets_IsElement((Sets_tElement)W_67->Name, &PrecNames)) {
        Tree_ErrorI((LONGINT)PrecedenceMultipleDeclared, t->U_1.V_25.Name.Pos, (LONGINT)Errors_Ident, ADR(W_67->Name));
      }
      Sets_Include(&PrecNames, (Sets_tElement)W_67->Name);
      CheckNames(W_67->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckNames2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_16 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Name) {
    {
      register Tree_yName *W_68 = &t->U_1.V_25.Name;

      Class = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_68->Name);
      if (Class == Tree_NoTree) {
        Tree_ErrorI((LONGINT)NodeTypeNotDeclared, t->U_1.V_25.Name.Pos, (LONGINT)Errors_Ident, ADR(W_68->Name));
      } else {
        if (!IN(Tree_Abstract, Class->U_1.V_5.Class.Properties)) {
          Tree_Error((LONGINT)AbstractTypeRequired, t->U_1.V_25.Name.Pos);
        }
      }
      CheckNames2(W_68->Next);
      return;
    }
  }
}

static void CheckDesignator
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_17 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_69 = &t->U_1.V_5.Class;

      Class = t;
      Tree_ForallAttributes(W_69->Attributes, (Tree_ProcOfT)CheckDesignator);
      return;
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_70 = &t->U_1.V_11.ActionPart;

      CheckDesignator(W_70->Actions);
      return;
    }
    break;
  case Tree_Assign:;
    {
      register Tree_yAssign *W_71 = &t->U_1.V_36.Assign;

      CheckDesignator(W_71->Results);
      CheckDesignator(W_71->Arguments);
      CheckDesignator(W_71->Next);
      return;
    }
    break;
  case Tree_Copy:;
    {
      register Tree_yCopy *W_72 = &t->U_1.V_37.Copy;

      CheckDesignator(W_72->Results);
      CheckDesignator(W_72->Arguments);
      CheckDesignator(W_72->Next);
      return;
    }
    break;
  case Tree_TargetCode:;
    {
      register Tree_yTargetCode *W_73 = &t->U_1.V_38.TargetCode;

      CheckDesignator(W_73->Code);
      CheckDesignator(W_73->Next);
      return;
    }
    break;
  case Tree_Check:;
    {
      register Tree_yCheck *W_74 = &t->U_1.V_40.Check;

      CheckDesignator(W_74->Statement);
      CheckDesignator(W_74->Condition);
      CheckDesignator(W_74->Actions);
      CheckDesignator(W_74->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_75 = &t->U_1.V_15.Designator;

      Node = Tree_IdentifyAttribute(Class, W_75->Selector);
      if (Node != Tree_NoTree) {
        if (Node->U_1.V_1.Kind != Tree_Child) {
          Tree_Error((LONGINT)ChildRequired, t->U_1.V_15.Designator.Pos);
        } else {
          if (Node->U_1.V_9.Child.Class != Tree_NoTree) {
            Node = Tree_IdentifyAttribute(Node->U_1.V_9.Child.Class, W_75->Attribute);
            if (Node == Tree_NoTree) {
              Tree_ErrorI((LONGINT)AttributeNotDeclared, t->U_1.V_15.Designator.Pos, (LONGINT)Errors_Ident, ADR(W_75->Attribute));
            }
          }
        }
      } else {
        Tree_ErrorI((LONGINT)SelectorNotDeclared, t->U_1.V_15.Designator.Pos, (LONGINT)Errors_Ident, ADR(W_75->Selector));
      }
      CheckDesignator(W_75->Next);
      return;
    }
    break;
  case Tree_Remote:;
    {
      register Tree_yRemote *W_76 = &t->U_1.V_17.Remote;

      Node = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_76->Type);
      if (Node == Tree_NoTree) {
        Tree_ErrorI((LONGINT)NodeTypeNotDeclared, t->U_1.V_17.Remote.Pos, (LONGINT)Errors_Ident, ADR(W_76->Type));
      } else {
        Node = Tree_IdentifyAttribute(Node, W_76->Attribute);
        if (Node == Tree_NoTree) {
          Tree_ErrorI((LONGINT)AttributeNotDeclared, t->U_1.V_17.Remote.Pos, (LONGINT)Errors_Ident, ADR(W_76->Attribute));
        }
      }
      CheckDesignator(W_76->Designators);
      CheckDesignator(W_76->Next);
      return;
    }
    break;
  case Tree_Order:;
    {
      register Tree_yOrder *W_77 = &t->U_1.V_39.Order;

      CheckDesignator(W_77->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_78 = &t->U_1.V_16.Ident;

      CheckDesignator(W_78->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_79 = &t->U_1.V_18.Any;

      CheckDesignator(W_79->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_80 = &t->U_1.V_19.Anys;

      CheckDesignator(W_80->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_81 = &t->U_1.V_22.LayoutAny;

      CheckDesignator(W_81->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void Identify
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_18 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_82 = &t->U_1.V_5.Class;

      Tree_ForallAttributes(t, (Tree_ProcOfT)Identify);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_83 = &t->U_1.V_9.Child;

      W_83->Class = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, W_83->Type);
      if (W_83->Class == Tree_NoTree && !Sets_IsElement(ORD('x'), &Tree_Options) && !Sets_IsElement(ORD('z'), &Tree_Options) && !Sets_IsElement(ORD('u'), &Tree_Options)) {
        Tree_ErrorI((LONGINT)NodeTypeNotDeclared, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_83->Type));
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void InitInstance0
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_19 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_84 = &t->U_1.V_5.Class;

      InstanceSize = W_84->InstCount;
      DynArray_MakeArray((ADDRESS *)&W_84->Instance, &InstanceSize, (LONGINT)sizeof(Tree_tInstance));
      InitInstance(t, W_84->AttrCount, W_84->Instance);
      return;
    }
  }
}

static void CompDP
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_20 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_85 = &t->U_1.V_5.Class;

      Relations_MakeRelation(&W_85->DP, (LONGINT)W_85->InstCount, (LONGINT)W_85->InstCount);
      relation = W_85->DP;
      Sets_MakeSet(&Results, (Sets_tElement)W_85->InstCount);
      Sets_MakeSet(&Arguments, (Sets_tElement)W_85->InstCount);
      Class = t;
      Attribute = Tree_IdentifyAttribute(t, iNull);
      DummyIndex = Attribute->U_1.V_10.Attribute.AttrIndex;
      INCL(W_85->Instance->A[DummyIndex - 1].Properties, Tree_Left);
      CompDP1(t, &Results, (LONGINT)Tree_Write, TRUE, TRUE);
      Sets_ReleaseSet(&Results);
      Sets_ReleaseSet(&Arguments);
      return;
    }
  }
}

static void CopyProperties
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_21 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_86 = &t->U_1.V_5.Class;

      {
        SHORTCARD B_5 = 1, B_6 = W_86->InstCount;

        if (B_5 <= B_6)
          for (i = B_5;; i += 1) {
            {
              register Tree_tInstance *W_87 = &W_86->Instance->A[i - 1];

              W_87->Properties = W_87->Properties | W_87->Attribute->U_1.V_9.Child.Properties;
              if (W_87->Action != ADR(W_87->Action) && W_87->Action->U_1.V_1.Kind == Tree_Copy) {
                INCL(W_87->Properties, Tree_CopyDef);
                INCL(W_86->Instance->A[W_87->CopyArg - 1].Properties, Tree_CopyUse);
              }
              if (Sets_IsElement(ORD('2'), &Tree_Options)) {
                if (!IN(Tree_NonBaseComp, W_87->Properties) && W_87->Action != ADR(W_87->Action) && (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_87->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_87->Properties))) {
                  Idents_WriteIdent((System_tFile)IO_StdOutput, W_86->Name);
                  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   = { ", 7L);
                  Tree_WriteClass(W_87->Action);
                  IO_WriteS((System_tFile)IO_StdOutput, (STRING)" } .", 4L);
                  IO_WriteNl((System_tFile)IO_StdOutput);
                }
              }
            }
            if (i >= B_6) break;
          }
      }
      return;
    }
  }
}

static void CheckUsage
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_22 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_88 = &t->U_1.V_5.Class;

      if (W_88->Extensions->U_1.V_1.Kind == Tree_NoClass) {
        Class = t;
        IsAbstract = IN(Tree_Abstract, W_88->Properties);
        Tree_ForallAttributes(t, (Tree_ProcOfT)CheckUsage);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_89 = &t->U_1.V_9.Child;

      if (!Sets_IsElement(ORD('W'), &Tree_Options) && !IsAbstract) {
        if (!IN(Tree_Input, W_89->Properties) && !IN(Tree_Write, W_89->Properties)) {
          Tree_WarningI((LONGINT)AttributeNeverSet, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_89->Name));
        }
        if (!IN(Tree_Output, W_89->Properties) && !IN(Tree_Read, W_89->Properties) && !Sets_IsElement(ORD('x'), &Tree_Options) && !Sets_IsElement(ORD('z'), &Tree_Options) && !Sets_IsElement(ORD('u'), &Tree_Options)) {
          Tree_WarningI((LONGINT)AttributeNeverUsed, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_89->Name));
        }
      }
      if (SET_IS_SUBSET1(SET_ELEM(Tree_Input) | SET_ELEM(Tree_Write), W_89->Properties) && (W_89->Class == Tree_NoTree || W_89->Class != Tree_NoTree && !IN(Tree_Terminal, W_89->Class->U_1.V_5.Class.Properties))) {
        Tree_ErrorI((LONGINT)AssignmentToInputAttribute, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_89->Name));
      }
      if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Inherited), W_89->Properties)) {
        Tree_ErrorI((LONGINT)AttributeSynthesizedAsWellAsInherited, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_89->Name));
      }
      return;
    }
    break;
  case Tree_Attribute:;
    for (;;) {
      {
        register Tree_yAttribute *W_90 = &t->U_1.V_10.Attribute;

        if (!(((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_90->Properties) == 0X0L)) {
          goto EXIT_2;
        }
        if (!Sets_IsElement(ORD('W'), &Tree_Options) && !IsAbstract) {
          if (!IN(Tree_Input, W_90->Properties) && !IN(Tree_Write, W_90->Properties)) {
            Tree_WarningI((LONGINT)AttributeNeverSet, t->U_1.V_10.Attribute.Pos, (LONGINT)Errors_Ident, ADR(W_90->Name));
          }
          if (!IN(Tree_Output, W_90->Properties) && !IN(Tree_Read, W_90->Properties)) {
            Tree_WarningI((LONGINT)AttributeNeverUsed, t->U_1.V_10.Attribute.Pos, (LONGINT)Errors_Ident, ADR(W_90->Name));
          }
        }
        if (SET_IS_SUBSET1(SET_ELEM(Tree_Input) | SET_ELEM(Tree_Write), W_90->Properties) && (Class == Tree_NoTree || Class != Tree_NoTree && !IN(Tree_Terminal, Class->U_1.V_5.Class.Properties))) {
          Tree_ErrorI((LONGINT)AssignmentToInputAttribute, t->U_1.V_10.Attribute.Pos, (LONGINT)Errors_Ident, ADR(W_90->Name));
        }
        if (SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Inherited), W_90->Properties)) {
          Tree_ErrorI((LONGINT)AttributeSynthesizedAsWellAsInherited, t->U_1.V_10.Attribute.Pos, (LONGINT)Errors_Ident, ADR(W_90->Name));
        }
        return;
      }
    } EXIT_2:;
    break;
  default :
    break;
  }
}

static void CheckUsage2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_23 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register struct S_24 *W_91 = &yyTempo.U_1.V_1.yyR1;

      for (;;) {
        {
          register Tree_yClass *W_92 = &t->U_1.V_5.Class;

          if (!!Sets_IsElement(ORD('W'), &Tree_Options)) {
            goto EXIT_3;
          }
          if (!!IN(Tree_Reachable, W_92->Properties)) {
            goto EXIT_3;
          }
          Idents_GetString(W_92->Name, &W_91->String);
          if (!(Strings_Char(&W_91->String, 1) != 'y' && Strings_Char(&W_91->String, 2) != 'y')) {
            goto EXIT_3;
          }
          Tree_WarningI((LONGINT)NodeTypeNotUsed, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_92->Name));
          return;
        }
      } EXIT_3:;
    }
  }
}

static void CheckInherited
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_25 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_93 = &t->U_1.V_5.Class;

      if (W_93->BaseClass->U_1.V_1.Kind == Tree_Class) {
        CheckInherited(W_93->Attributes);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_94 = &t->U_1.V_9.Child;

      if (IN(Tree_Inherited, W_94->Properties)) {
        Tree_ErrorI((LONGINT)InheritedAttributesAllowedOnlyInBaseClasses, t->U_1.V_9.Child.Pos, (LONGINT)Errors_Ident, ADR(W_94->Name));
      }
      CheckInherited(W_94->Next);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_95 = &t->U_1.V_10.Attribute;

      if (IN(Tree_Inherited, W_95->Properties)) {
        Tree_ErrorI((LONGINT)InheritedAttributesAllowedOnlyInBaseClasses, t->U_1.V_10.Attribute.Pos, (LONGINT)Errors_Ident, ADR(W_95->Name));
      }
      CheckInherited(W_95->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckComplete
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_26 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_96 = &t->U_1.V_5.Class;

      if (W_96->Extensions->U_1.V_1.Kind == Tree_NoClass || !Sets_IsElement(ORD('B'), &Tree_Options)) {
        {
          SHORTCARD B_7 = 1, B_8 = W_96->InstCount;

          if (B_7 <= B_8)
            for (i = B_7;; i += 1) {
              {
                register Tree_tInstance *W_97 = &W_96->Instance->A[i - 1];

                if (((SET_ELEM(Tree_Input) | SET_ELEM(Tree_Computed)) & W_97->Properties) == 0X0L && (IN(Tree_Terminal, t->U_1.V_5.Class.Properties) && W_97->Attribute->U_1.V_1.Kind == Tree_Attribute || SET_IS_SUBSET1(SET_ELEM(Tree_Synthesized) | SET_ELEM(Tree_Left), W_97->Properties) || SET_IS_SUBSET1(SET_ELEM(Tree_Inherited) | SET_ELEM(Tree_Right), W_97->Properties))) {
                  CopyRule(t);
                  if (j == 0) {
                    Idents_GetString(W_96->Name, &String);
                    Strings_ArrayToString((STRING)" = ", 3L, &String2);
                    Strings_Concatenate(&String, &String2);
                    if (IN(Tree_Right, W_97->Properties)) {
                      Idents_GetString(W_97->Selector->U_1.V_9.Child.Name, &String2);
                      Strings_Concatenate(&String, &String2);
                      Strings_Append(&String, ':');
                      Idents_GetString(W_97->Attribute->U_1.V_9.Child.Name, &String2);
                      Strings_Concatenate(&String, &String2);
                    } else {
                      Idents_GetString(W_97->Attribute->U_1.V_9.Child.Name, &String2);
                      Strings_Concatenate(&String, &String2);
                    }
                    Tree_ErrorI((LONGINT)AttributeComputationMissing, t->U_1.V_5.Class.Pos, (LONGINT)Errors_String, ADR(String));
                  }
                }
              }
              if (i >= B_8) break;
            }
        }
      }
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        {
          SHORTCARD B_9 = 1, B_10 = W_96->AttrCount;

          if (B_9 <= B_10)
            for (i = B_9;; i += 1) {
              {
                register Tree_tInstance *W_98 = &W_96->Instance->A[i - 1];

                if (!IN(Tree_Input, W_98->Properties) && W_98->Attribute->U_1.V_1.Kind == Tree_Child) {
                  {
                    SHORTCARD B_11 = 1, B_12 = W_96->InstCount;

                    if (B_11 <= B_12)
                      for (j = B_11;; j += 1) {
                        if (Relations_IsRelated((LONGINT)j, (LONGINT)i, W_96->DP)) {
                          {
                            SHORTCARD B_13 = 1, B_14 = W_96->AttrCount;

                            if (B_13 <= B_14)
                              for (k = B_13;; k += 1) {
                                if (Relations_IsRelated((LONGINT)k, (LONGINT)j, W_96->DP)) {
                                  Relations_Include(&W_96->DP, (LONGINT)k, (LONGINT)i);
                                }
                                if (k >= B_14) break;
                              }
                          }
                        }
                        if (j >= B_12) break;
                      }
                  }
                }
              }
              if (i >= B_10) break;
            }
        }
      }
      if (Relations_IsCyclic(W_96->DP)) {
        Tree_ErrorI((LONGINT)CycleInLocalDependenciesDP, t->U_1.V_5.Class.Pos, (LONGINT)Errors_Ident, ADR(W_96->Name));
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Attribute Dependencies DP", 25L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Tree_WriteDependencies(t, W_96->DP, Tree_MaxSet);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Cyclic Attributes", 17L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Sets_MakeSet(&Cyclics, (Sets_tElement)W_96->InstCount);
        Relations_GetCyclics(W_96->DP, &Cyclics);
        Tree_WriteCyclics(t, Cyclics);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Sets_ReleaseSet(&Cyclics);
        Success = FALSE;
      }
      if (Sets_IsElement(ORD('M'), &Tree_Options)) {
        Tree_WriteClass(t);
        IO_WriteNl((System_tFile)IO_StdOutput);
      }
      if (Sets_IsElement(ORD('P'), &Tree_Options)) {
        Tree_WriteDependencies(t, W_96->DP, Tree_MaxSet);
      }
      return;
    }
  }
}

static void CopyRule
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  SHORTCARD LLastParsIndex;
  Tree_tTree LNewNode;
  struct S_27 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_99 = &t->U_1.V_5.Class;

      {
        register Tree_tInstance *W_100 = &W_99->Instance->A[i - 1];

        j = 0;
        if (i <= W_99->AttrCount) {
          Ident = W_100->Attribute->U_1.V_10.Attribute.Name;
          Tree_ForallAttributes(t, (Tree_ProcOfT)CopyRule2);
          if (j != 0) {
            INC1(j, W_99->AttrCount + Child->U_1.V_9.Child.InstOffset);
            W_100->Action = Tree_mCopy(Tree_nNoAction, Positions_NoPosition, Tree_mIdent(Ident, Positions_NoPosition, Tree_nNoDesignator), Tree_mDesignator(W_99->Instance->A[j - 1].Selector->U_1.V_9.Child.Name, Ident, Positions_NoPosition, Positions_NoPosition, Tree_nNoDesignator));
            INC(CopySynthesized);
          }
          if (j == 0 && IN(Tree_Thread, W_100->Properties)) {
            j = i - 1;
            W_100->Action = Tree_mCopy(Tree_nNoAction, Positions_NoPosition, Tree_mIdent(Ident, Positions_NoPosition, Tree_nNoDesignator), Tree_mIdent(W_99->Instance->A[j - 1].Attribute->U_1.V_10.Attribute.Name, Positions_NoPosition, Tree_nNoDesignator));
            INC(CopyThreaded);
          }
        } else {
          if (IN(Tree_Thread, W_100->Properties) && W_100->Selector->U_1.V_9.Child.InstOffset > 0) {
            Ident = W_99->Instance->A[i + 1 - 1].Attribute->U_1.V_10.Attribute.Name;
            j = i - 1;
            for (;;) {
              if (j <= W_99->AttrCount) {
                j = 0;
                goto EXIT_4;
              }
              if (!IN(Tree_Link, W_99->Instance->A[j - 1].Selector->U_1.V_9.Child.Properties) && W_99->Instance->A[j - 1].Attribute->U_1.V_10.Attribute.Name == Ident) {
                W_100->Action = Tree_mCopy(Tree_nNoAction, Positions_NoPosition, Tree_mDesignator(W_100->Selector->U_1.V_9.Child.Name, W_100->Attribute->U_1.V_10.Attribute.Name, Positions_NoPosition, Positions_NoPosition, Tree_nNoDesignator), Tree_mDesignator(W_99->Instance->A[j - 1].Selector->U_1.V_9.Child.Name, Ident, Positions_NoPosition, Positions_NoPosition, Tree_nNoDesignator));
                INC(CopyThreaded);
                goto EXIT_4;
              }
              DEC(j);
            } EXIT_4:;
          }
          if (j == 0) {
            Ident = W_100->Attribute->U_1.V_10.Attribute.Name;
            Tree_ForallAttributes(t, (Tree_ProcOfT)CopyRule);
            if (j != 0) {
              W_100->Action = Tree_mCopy(Tree_nNoAction, Positions_NoPosition, Tree_mDesignator(W_100->Selector->U_1.V_9.Child.Name, Ident, Positions_NoPosition, Positions_NoPosition, Tree_nNoDesignator), Tree_mIdent(Ident, Positions_NoPosition, Tree_nNoDesignator));
              INC(CopyInherited);
            }
          }
        }
        if (j != 0) {
          if (Sets_IsElement(ORD('1'), &Tree_Options)) {
            Idents_WriteIdent((System_tFile)IO_StdOutput, W_99->Name);
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"  = { ", 6L);
            Tree_WriteClass(W_100->Action);
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)" } .", 4L);
            IO_WriteNl((System_tFile)IO_StdOutput);
          }
          W_100->CopyArg = j;
          TheAction = W_100->Action;
          Relations_Include(&W_99->DP, (LONGINT)i, (LONGINT)j);
          INCL(W_100->Properties, Tree_CopyDef);
          INCL(W_99->Instance->A[W_100->CopyArg - 1].Properties, Tree_CopyUse);
          INCL(W_100->Properties, Tree_Write);
          INCL(W_100->Properties, Tree_Computed);
          INCL(W_99->Instance->A[W_100->CopyArg - 1].Properties, Tree_Read);
          INCL(W_100->Attribute->U_1.V_10.Attribute.Properties, Tree_Write);
          INCL(W_100->Attribute->U_1.V_10.Attribute.Properties, Tree_Computed);
          INCL(W_99->Instance->A[W_100->CopyArg - 1].Attribute->U_1.V_10.Attribute.Properties, Tree_Read);
          if (IN(Tree_Right, W_100->Properties)) {
            INCL(W_100->Selector->U_1.V_9.Child.Properties, Tree_Read);
          }
          if (IN(Tree_Right, W_99->Instance->A[W_100->CopyArg - 1].Properties)) {
            INCL(W_99->Instance->A[W_100->CopyArg - 1].Selector->U_1.V_9.Child.Properties, Tree_Read);
          }
        }
      }
      if (j != 0) {
        INCL(W_99->Properties, Tree_HasActions);
        if (W_99->Attributes->U_1.V_1.Kind == Tree_NoAttribute) {
          W_99->Attributes = Tree_mActionPart(W_99->Attributes, TheAction);
          W_99->Attributes->U_1.V_11.ActionPart.ParsIndex = 1;
          INC(ActionName);
          W_99->Attributes->U_1.V_11.ActionPart.Name = ActionName;
        } else {
          Node = W_99->Attributes;
          LLastParsIndex = 0;
          for (;;) {
            switch (Node->U_1.V_1.Kind) {
            case Tree_Child:;
              LLastParsIndex = Node->U_1.V_9.Child.ParsIndex;
              break;
            case Tree_ActionPart:;
              LLastParsIndex = Node->U_1.V_11.ActionPart.ParsIndex;
              break;
            default :
              break;
            }
            if (Node->U_1.V_8.AttrOrAction.Next->U_1.V_1.Kind == Tree_NoAttribute) {
              goto EXIT_5;
            } else {
              Node = Node->U_1.V_8.AttrOrAction.Next;
            }
          } EXIT_5:;
          LNewNode = Tree_mActionPart(Tree_nNoAttribute, TheAction);
          Node->U_1.V_8.AttrOrAction.Next = LNewNode;
          LNewNode->U_1.V_11.ActionPart.ParsIndex = LLastParsIndex + 1;
          INC(ActionName);
          LNewNode->U_1.V_11.ActionPart.Name = ActionName;
        }
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_101 = &t->U_1.V_9.Child;

      if (W_101->Name == Ident) {
        Child = Attribute;
        j = W_101->AttrIndex;
      }
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_102 = &t->U_1.V_10.Attribute;

      if (W_102->Name == Ident) {
        Child = Attribute;
        j = W_102->AttrIndex;
      }
      return;
    }
    break;
  default :
    break;
  }
}

static void CopyRule2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_28 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Child) {
    for (;;) {
      {
        register Tree_yChild *W_103 = &t->U_1.V_9.Child;

        if (!(W_103->Class != Tree_NoTree)) {
          goto EXIT_6;
        }
        if (!!IN(Tree_Link, W_103->Properties)) {
          goto EXIT_6;
        }
        Attribute = t;
        Tree_ForallAttributes(W_103->Class, (Tree_ProcOfT)CopyRule);
        return;
      }
    } EXIT_6:;
  }
}

static BOOLEAN IsCopy
# ifdef __STDC__
(Tree_tTree yyP1)
# else
(yyP1)
Tree_tTree yyP1;
# endif
{
  struct S_29 yyTempo;

  if (yyP1 == Tree_NoTree) {
    return FALSE;
  }
  switch (yyP1->U_1.V_1.Kind) {
  case Tree_Designator:;
    {
      register struct S_30 *W_104 = &yyTempo.U_1.V_1.yyR1;

      for (;;) {
        {
          register Tree_yDesignator *W_105 = &yyP1->U_1.V_15.Designator;

          W_104->Attr = Tree_IdentifyAttribute(Class, W_105->Selector);
          if (!(W_104->Attr != Tree_NoTree)) {
            goto EXIT_7;
          }
          if (!(W_104->Attr->U_1.V_1.Kind == Tree_Child)) {
            goto EXIT_7;
          }
          W_104->ChildsClass = W_104->Attr->U_1.V_9.Child.Class;
          if (!(W_104->ChildsClass != Tree_NoTree)) {
            goto EXIT_7;
          }
          if (!(Tree_IdentifyAttribute(W_104->ChildsClass, W_105->Attribute) != Tree_NoTree)) {
            goto EXIT_7;
          }
          if (!IsWhiteSpace(W_105->Next)) {
            goto EXIT_7;
          }
          return TRUE;
        }
      } EXIT_7:;
    }
    break;
  case Tree_Ident:;
    for (;;) {
      {
        register Tree_yIdent *W_106 = &yyP1->U_1.V_16.Ident;

        if (!(Tree_IdentifyAttribute(Class, W_106->Attribute) != Tree_NoTree)) {
          goto EXIT_8;
        }
        if (!IsWhiteSpace(W_106->Next)) {
          goto EXIT_8;
        }
        return TRUE;
      }
    } EXIT_8:;
    break;
  case Tree_Any:;
    for (;;) {
      {
        register Tree_yAny *W_107 = &yyP1->U_1.V_18.Any;

        if (!IsWhiteSpace2(W_107->Code)) {
          goto EXIT_9;
        }
        if (!IsCopy(W_107->Next)) {
          goto EXIT_9;
        }
        return TRUE;
      }
    } EXIT_9:;
    break;
  case Tree_Anys:;
    for (;;) {
      {
        register Tree_yAnys *W_108 = &yyP1->U_1.V_19.Anys;

        if (!IsCopy(W_108->Next)) {
          goto EXIT_10;
        }
        return TRUE;
      }
    } EXIT_10:;
    break;
  default :
    break;
  }
  return FALSE;
}

static BOOLEAN IsWhiteSpace
# ifdef __STDC__
(Tree_tTree yyP2)
# else
(yyP2)
Tree_tTree yyP2;
# endif
{
  struct S_31 yyTempo;

  if (yyP2 == Tree_NoTree) {
    return FALSE;
  }
  switch (yyP2->U_1.V_1.Kind) {
  case Tree_Any:;
    for (;;) {
      {
        register Tree_yAny *W_109 = &yyP2->U_1.V_18.Any;

        if (!IsWhiteSpace2(W_109->Code)) {
          goto EXIT_11;
        }
        if (!IsWhiteSpace(W_109->Next)) {
          goto EXIT_11;
        }
        return TRUE;
      }
    } EXIT_11:;
    break;
  case Tree_Anys:;
    for (;;) {
      {
        register Tree_yAnys *W_110 = &yyP2->U_1.V_19.Anys;

        if (!IsWhiteSpace(W_110->Next)) {
          goto EXIT_12;
        }
        return TRUE;
      }
    } EXIT_12:;
    break;
  case Tree_NoDesignator:;
    return TRUE;
    break;
  default :
    break;
  }
  return FALSE;
}

static BOOLEAN IsWhiteSpace2
# ifdef __STDC__
(StringMem_tStringRef yyP3)
# else
(yyP3)
StringMem_tStringRef yyP3;
# endif
{
  CARDINAL i;
  struct S_32 yyTempo;

  {
    register struct S_33 *W_111 = &yyTempo.U_1.V_1.yyR1;

    StringMem_GetString(yyP3, &W_111->String);
    {
      LONGCARD B_15 = 1, B_16 = Strings_Length(&W_111->String);

      if (B_15 <= B_16)
        for (i = B_15;; i += 1) {
          W_111->ch = Strings_Char(&W_111->String, (Strings_tStringIndex)i);
          if (W_111->ch != ' ' && W_111->ch != '\n' && W_111->ch != '\t') {
            return FALSE;
          }
          if (i >= B_16) break;
        }
    }
    return TRUE;
  }
}

void Semantics_BeginSemantics
# ifdef __STDC__
()
# else
()
# endif
{
  ItemCount = 0;
  ChecksCount = 0;
  MaxInstCount = 0;
  CopyInherited = 0;
  CopySynthesized = 0;
  CopyThreaded = 0;
  Strings_IntToString(0L, &String);
  iNull = Idents_MakeIdent(&String);
}

void Semantics_CloseSemantics
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

void Semantics__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Tree__init();
    System__init();
    IO__init();
    Tree__init();
    General__init();
    IO__init();
    DynArray__init();
    StringMem__init();
    Strings__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Sets__init();
    Relations__init();
    Positions__init();
    Tree__init();
    Relations__init();
    StringMem__init();
    Errors__init();

    Semantics_yyf = IO_StdOutput;
    Semantics_Exit = yyExit;
    Semantics_BeginSemantics();
  }
}
