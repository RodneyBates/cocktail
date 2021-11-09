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

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Assertions
#include "Assertions.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

SHORTCARD Semantics_TypeCount;
Sets_tSet Semantics_TypeNames, Semantics_UserTypes;
IO_tFile Semantics_yyf;
PROC Semantics_Exit;

static Sets_tSet ExternNames, LocExternNames, ActTypes, ActNames, UserNames, LabelNames, ParamNames, RoutineNames;
static Tree_tTree dFormals, Parameters, Decls, Args, InFormals, OutFormals, ReturnFormal, Node, Var, TreeName, ActTree, ActClass;
static INTEGER RuleCount, TempoCount;
static Idents_tIdent ProcName, ParamName, IdentDot, IdentEmptyType, IdentFalse, IdentTrue, IdentNil;
static BOOLEAN HasLocals, IsFunction, IsOutput, Mode, Success;
static Strings_tString String, String1;
static CARDINAL i;
static Tree_tTree nNoFormal;
static Tree_tTree GlobalLUBClass;
static Positions_tPosition ParamPos;
static StringMem_tStringRef StringRefNil;
static Tree_tTree nNoDesignator;
static void PositionToString ARGS((Positions_tPosition Pos, Strings_tString *Result));
static void WarningIPP ARGS((CHAR Text1[], LONGCARD , Idents_tIdent Id, CHAR Text2[], LONGCARD , Positions_tPosition Pos2, CHAR Text3[], LONGCARD , Positions_tPosition Pos3, Positions_tPosition Pos));
static INTEGER LookupFormal ARGS((Idents_tIdent Ident, Tree_tTree Formals));
static Tree_tTree IdentifyTree ARGS((Idents_tIdent i));
static Tree_tTree IdentifyProc ARGS((Idents_tIdent i));
static Tree_tTree IdentifyClass2 ARGS((Idents_tIdent i, Tree_tTree *TreeName));
static Tree_tTree IdentifyClass ARGS((Tree_tTree t, Idents_tIdent Ident));
static Tree_tTree ClassOfNodeTypes ARGS((Tree_tTree NodeTypes));
static Idents_tIdent TypeIdentOfFormal ARGS((Tree_tTree Formal));
static void MakeTypes ARGS((INTEGER Index, Tree_tTree Classes, Sets_tSet *Types));
static void CheckSubtype ARGS((Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos, CHAR Reason[], LONGCARD ));
static void CheckType ARGS((Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos));
static void ComputeDepthsClasses ARGS((Tree_tTree t, INTEGER FDepth));
static Tree_tTree ClassLUB ARGS((Tree_tTree Left, Tree_tTree Right));
static void NextPatterns ARGS((Tree_tTree Patterns, Tree_tTree *Result, BOOLEAN *CarryOut));
static void ExpandDecompose ARGS((Positions_tPosition Pos, Idents_tIdent Selector, Tree_tTree Expr, Tree_tTree Exprs, BOOLEAN Widen, Tree_tTree *Result, CARDINAL *PatternCount));
static BOOLEAN IsAllDontCares ARGS((Tree_tTree t));
static Tree_tTree MakeValue ARGS((Tree_tTree t));
static void TransformPattern ARGS((Tree_tTree t, Tree_tTree *Result, CARDINAL *PatternCount));
static void TransformPatternRecurse ARGS((Tree_tTree t, Tree_tTree *Result, CARDINAL *PatternCount));
static Tree_tTree TransformExpr ARGS((Tree_tTree t));
static Tree_tTree TransformStmt ARGS((Tree_tTree t));
static Tree_tTree TransformKeyword ARGS((Tree_tTree t, Tree_tTree Formals));
struct S_7 {
    Tree_tTree A[50000 + 1];
};
static void CheckExprList ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckInParams ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckCallExprs ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckExprVar ARGS((Tree_tTree *t, Tree_tTree Formals));
static void CheckExpr ARGS((Tree_tTree *t, Tree_tTree Formals));
static void CheckExpr2 ARGS((Tree_tTree *t));
#define C_1_RoutineFormal        0
#define ChildFormal        1
#define CallFormal        2
typedef unsigned char FormalKindTyp;
static void CheckRulePatterns ARGS((Tree_tTree t, Tree_tTree Formals, Tree_tTree Predecessor));
static void CheckSubPatterns ARGS((Tree_tTree t, Tree_tTree Formals, Tree_tTree FPath));
static void CheckCallPatterns ARGS((Tree_tTree t, Tree_tTree Formals));
static void AddHidingDecl ARGS((Tree_tTree FDecl));
static void DeclarePattern ARGS((FormalKindTyp FormalKind, Idents_tIdent Name, Tree_tTree TypeDesc, Tree_tTree FPath, Positions_tPosition Pos));
static void DeclareLabel ARGS((Idents_tIdent Selector, Positions_tPosition Pos, BOOLEAN Widen, Tree_tTree Formal, Tree_tTree NarrowTypeDesc, Tree_tTree WidePath, Tree_tTree NarrowPath));
static void CheckPattern ARGS((Tree_tTree *t, Tree_tTree Formals, Tree_tTree FPath, FormalKindTyp FormalKind));
static Idents_tIdent MakeTempoIdent ARGS(());
static Tree_tTree MakeTempos ARGS((Tree_tTree Formals));
static void InitPredefinedExtern ARGS(());
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
static void CollectRoutineNames ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void CollectExtern ARGS((Tree_tTree t, Sets_tSet *Names));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void ProcFormals ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void CollectUniversalTypeDesc ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void ClassFormals ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void CountClasses ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void ClassTypes ARGS((Tree_tTree t));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void Check ARGS((Tree_tTree t));
struct S_16 {
    union {
        struct {
            struct S_18 {
                CARDINAL LPatternCount;
                BOOLEAN LIsLast;
                Tree_tTree LPatterns;
                Tree_tTree LSinglePatterns;
                Tree_tTree LNewRule;
            } yyR4;
        } V_1;
        struct {
            struct S_17 {
                Tree_tTree LAttrFormal;
            } yyR28;
        } V_2;
    } U_1;
};
static void CheckTargetCode ARGS((Tree_tTree t));
struct S_19 {
    union {
        char dummy;
    } U_1;
};
struct S_20 {
    union {
        struct {
            struct S_21 {
                Strings_tString String1;
                Strings_tString String2;
                Idents_tIdent i;
            } yyR2;
        } V_1;
    } U_1;
};
static BOOLEAN HasReject ARGS((Tree_tTree yyP1));
struct S_22 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


static void PositionToString
# ifdef __STDC__
(Positions_tPosition Pos, Strings_tString *Result)
# else
(Pos, Result)
Positions_tPosition Pos;
Strings_tString *Result;
# endif
{
  Strings_tString LString;

  Strings_IntToString(VAL(INTEGER, Pos.Line), Result);
  Strings_Append(Result, ',');
  Strings_IntToString(VAL(INTEGER, Pos.Column), &LString);
  Strings_Concatenate(Result, &LString);
}

static void WarningIPP
# ifdef __STDC__
(CHAR Text1[], LONGCARD O_3, Idents_tIdent Id, CHAR Text2[], LONGCARD O_2, Positions_tPosition Pos2, CHAR Text3[], LONGCARD O_1, Positions_tPosition Pos3, Positions_tPosition Pos)
# else
(Text1, O_3, Id, Text2, O_2, Pos2, Text3, O_1, Pos3, Pos)
CHAR Text1[];
LONGCARD O_3;
Idents_tIdent Id;
CHAR Text2[];
LONGCARD O_2;
Positions_tPosition Pos2;
CHAR Text3[];
LONGCARD O_1;
Positions_tPosition Pos3;
Positions_tPosition Pos;
# endif
{
  Strings_tString LMessage, LString;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR) + O_2 * sizeof(CHAR) + O_3 * sizeof(CHAR), 3)
  COPY_OPEN_ARRAY(Text3, O_1, CHAR)
  COPY_OPEN_ARRAY(Text2, O_2, CHAR)
  COPY_OPEN_ARRAY(Text1, O_3, CHAR)
  Strings_ArrayToString(Text1, O_3, &LMessage);
  Idents_GetString(Id, &LString);
  Strings_Concatenate(&LMessage, &LString);
  Strings_ArrayToString(Text2, O_2, &LString);
  Strings_Concatenate(&LMessage, &LString);
  PositionToString(Pos2, &LString);
  Strings_Concatenate(&LMessage, &LString);
  Strings_ArrayToString(Text3, O_1, &LString);
  Strings_Concatenate(&LMessage, &LString);
  PositionToString(Pos3, &LString);
  Strings_Concatenate(&LMessage, &LString);
  Scanner_StringWarning(LMessage, Pos);
  FREE_OPEN_ARRAYS
}

static INTEGER LookupFormal
# ifdef __STDC__
(Idents_tIdent Ident, Tree_tTree Formals)
# else
(Ident, Formals)
Idents_tIdent Ident;
Tree_tTree Formals;
# endif
{
  INTEGER i;

  i = 0;
  while (Tree_IsType(Formals, Tree_Formal)) {
    INC(i);
    if (Formals->U_1.V_93.Formal.Name == Ident) {
      return i;
    }
    Formals = Formals->U_1.V_93.Formal.Next;
  }
  return 0;
}

static Tree_tTree IdentifyTree
# ifdef __STDC__
(Idents_tIdent i)
# else
(i)
Idents_tIdent i;
# endif
{
  Tree_tTree Node;

  Node = Tree_TreeRoot->U_1.V_26.Spec.TreeNames;
  while (Node->U_1.V_1.Kind == Tree_TreeName) {
    if (Node->U_1.V_29.TreeName.Name == i) {
      return Node;
    }
    Node = Node->U_1.V_29.TreeName.Next;
  }
  return Tree_NoTree;
}

static Tree_tTree IdentifyProc
# ifdef __STDC__
(Idents_tIdent i)
# else
(i)
Idents_tIdent i;
# endif
{
  Tree_tTree Node;

  Node = Tree_TreeRoot->U_1.V_26.Spec.Routines;
  while (Node->U_1.V_1.Kind != Tree_NoRoutine) {
    if (Node->U_1.V_32.Routine.Name == i) {
      return Node;
    }
    Node = Node->U_1.V_32.Routine.Next;
  }
  return Tree_NoTree;
}

Tree_tTree Semantics_IdentifyVar
# ifdef __STDC__
(Tree_tTree Node, Idents_tIdent i)
# else
(Node, i)
Tree_tTree Node;
Idents_tIdent i;
# endif
{
  while (Node->U_1.V_1.Kind != Tree_NoFormal) {
    if (Node->U_1.V_93.Formal.Name == i) {
      return Node;
    }
    Node = Node->U_1.V_93.Formal.Next;
  }
  return Tree_NoTree;
}

static Tree_tTree IdentifyClass2
# ifdef __STDC__
(Idents_tIdent i, Tree_tTree *TreeName)
# else
(i, TreeName)
Idents_tIdent i;
Tree_tTree *TreeName;
# endif
{
  Tree_tTree Class;

  *TreeName = Tree_TreeRoot->U_1.V_26.Spec.TreeNames;
  while ((*TreeName)->U_1.V_1.Kind == Tree_TreeName) {
    Class = IdentifyClass((*TreeName)->U_1.V_29.TreeName.Classes, i);
    if (Class != Tree_NoTree) {
      return Class;
    }
    *TreeName = (*TreeName)->U_1.V_29.TreeName.Next;
  }
  *TreeName = Tree_NoTree;
  return Tree_NoTree;
}

static Tree_tTree IdentifyClass
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent Ident)
# else
(t, Ident)
Tree_tTree t;
Idents_tIdent Ident;
# endif
{
  Tree_tTree class;

  while (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_1 = &t->U_1.V_5.Class;

      if (W_1->Name == Ident) {
        return t;
      }
      class = IdentifyClass(W_1->Extensions, Ident);
      if (class != Tree_NoTree) {
        return class;
      }
      t = W_1->Next;
    }
  }
  return Tree_NoTree;
}

Tree_tTree Semantics_LookupClass
# ifdef __STDC__
(Tree_tTree Classes, CARDINAL i)
# else
(Classes, i)
Tree_tTree Classes;
CARDINAL i;
# endif
{
  Tree_tTree Class;

  if (Classes->U_1.V_1.Kind == Tree_NoClass) {
    return Tree_NoTree;
  }
  {
    register Tree_yClass *W_2 = &Classes->U_1.V_5.Class;

    if (W_2->Index == i) {
      return Classes;
    }
    Class = Semantics_LookupClass(W_2->Extensions, i);
    if (Class != Tree_NoTree) {
      return Class;
    }
    return Semantics_LookupClass(W_2->Next, i);
  }
}

static Tree_tTree ClassOfNodeTypes
# ifdef __STDC__
(Tree_tTree NodeTypes)
# else
(NodeTypes)
Tree_tTree NodeTypes;
# endif
{
  return Semantics_LookupClass(NodeTypes->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Classes, Sets_Minimum(&NodeTypes->U_1.V_98.NodeTypes.Types));
}

static Idents_tIdent TypeIdentOfFormal
# ifdef __STDC__
(Tree_tTree Formal)
# else
(Formal)
Tree_tTree Formal;
# endif
{
  Tree_tTree LClass;

  if (Formal == Tree_NoTree) {
    return Idents_NoIdent;
  } else if (Tree_IsType(Formal, Tree_Formal)) {
    if (Formal->U_1.V_93.Formal.TypeDesc == Tree_NoTree) {
      return Idents_NoIdent;
    } else if (Tree_IsType(Formal->U_1.V_93.Formal.TypeDesc, Tree_UserType)) {
      return Formal->U_1.V_93.Formal.TypeDesc->U_1.V_99.UserType.Type;
    } else if (Tree_IsType(Formal->U_1.V_93.Formal.TypeDesc, Tree_NodeTypes)) {
      if (Tree_IsType(Formal, Tree_RoutineFormal) && Formal->U_1.V_95.RoutineFormal.TargetClass != Tree_NoTree) {
        return Formal->U_1.V_95.RoutineFormal.TargetClass->U_1.V_5.Class.Name;
      } else {
        LClass = ClassOfNodeTypes(Formal->U_1.V_93.Formal.TypeDesc);
        return LClass->U_1.V_5.Class.Name;
      }
    } else {
      return Idents_NoIdent;
    }
  } else {
    return Idents_NoIdent;
  }
}

static void MakeTypes
# ifdef __STDC__
(INTEGER Index, Tree_tTree Classes, Sets_tSet *Types)
# else
(Index, Classes, Types)
INTEGER Index;
Tree_tTree Classes;
Sets_tSet *Types;
# endif
{
  ActTypes = *Types;
  Tree_ForallClasses(Classes, (Tree_ProcOfT)ProcFormals);
  Sets_Include(&ActTypes, (Sets_tElement)Index);
  *Types = ActTypes;
}

static void CheckSubtype
# ifdef __STDC__
(Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos, CHAR Reason[], LONGCARD O_4)
# else
(t1, t2, Pos, Reason, O_4)
Tree_tTree t1, t2;
Positions_tPosition Pos;
CHAR Reason[];
LONGCARD O_4;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Reason, O_4, CHAR)
  if (t1->U_1.V_1.Kind == Tree_NodeTypes) {
    if (t2->U_1.V_1.Kind == Tree_UserType) {
      Scanner_Warning(Reason, O_4, Pos);
      Scanner_Warning((STRING)"  user type is incompatible with formal's tree type", 51L, Pos);
    } else if (t2->U_1.V_98.NodeTypes.TreeName != t1->U_1.V_98.NodeTypes.TreeName) {
      Scanner_Error(Reason, O_4, Pos);
      Scanner_Error((STRING)"  incompatible tree types from different trees", 46L, Pos);
    } else if (!Sets_IsSubset(t2->U_1.V_98.NodeTypes.Types, t1->U_1.V_98.NodeTypes.Types)) {
      Scanner_Error(Reason, O_4, Pos);
      Scanner_Error((STRING)"  not a subset of formal node kinds", 35L, Pos);
    }
  } else if (t1->U_1.V_1.Kind == Tree_UserType) {
    if (t2->U_1.V_1.Kind == Tree_NodeTypes) {
      Scanner_Warning(Reason, O_4, Pos);
      Scanner_Warning((STRING)"  tree type is incompatible with formal's user type", 51L, Pos);
    } else if (t2->U_1.V_99.UserType.Type != t1->U_1.V_99.UserType.Type) {
      Scanner_Warning(Reason, O_4, Pos);
      Scanner_Warning((STRING)"  incompatible user types", 25L, Pos);
    }
  }
  FREE_OPEN_ARRAYS
}

static void CheckType
# ifdef __STDC__
(Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos)
# else
(t1, t2, Pos)
Tree_tTree t1, t2;
Positions_tPosition Pos;
# endif
{
  Sets_tSet t;

  if (t1->U_1.V_1.Kind == Tree_NodeTypes) {
    if (t2->U_1.V_1.Kind == Tree_UserType) {
      Scanner_Warning((STRING)"tree-type required", 18L, Pos);
    } else if (t2->U_1.V_98.NodeTypes.TreeName != t1->U_1.V_98.NodeTypes.TreeName) {
      Scanner_Error((STRING)"incompatible types from different trees", 39L, Pos);
    } else {
      Sets_MakeSet(&t, (Sets_tElement)t1->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
      Sets_Assign(&t, t1->U_1.V_98.NodeTypes.Types);
      Sets_Intersection(&t, t2->U_1.V_98.NodeTypes.Types);
      if (Sets_IsEmpty(t)) {
        Scanner_Warning((STRING)"disjoint node types", 19L, Pos);
      }
      Sets_ReleaseSet(&t);
    }
  } else if (t1->U_1.V_1.Kind == Tree_UserType) {
    if (t2->U_1.V_1.Kind == Tree_NodeTypes) {
      Scanner_Warning((STRING)"user-type required", 18L, Pos);
    } else if (t2->U_1.V_99.UserType.Type != t1->U_1.V_99.UserType.Type) {
      Scanner_Warning((STRING)"incompatible user types", 23L, Pos);
    }
  }
}

static void ComputeDepthsClasses
# ifdef __STDC__
(Tree_tTree t, INTEGER FDepth)
# else
(t, FDepth)
Tree_tTree t;
INTEGER FDepth;
# endif
{
  Tree_tTree LC;

  LC = t;
  while (LC != NIL && LC->U_1.V_1.Kind == Tree_Class) {
    LC->U_1.V_5.Class.Depth = FDepth;
    ComputeDepthsClasses(LC->U_1.V_5.Class.Extensions, FDepth + 1);
    LC = LC->U_1.V_5.Class.Next;
  }
}

static Tree_tTree ClassLUB
# ifdef __STDC__
(Tree_tTree Left, Tree_tTree Right)
# else
(Left, Right)
Tree_tTree Left, Right;
# endif
{
  INTEGER LDepth;

  if (Left == Tree_NoTree) {
    return Right;
  } else if (Right == Tree_NoTree) {
    return Left;
  } else if (Left->U_1.V_1.Kind == Tree_NoClass) {
    return Right;
  } else if (Right->U_1.V_1.Kind == Tree_NoClass) {
    return Left;
  } else if (Left->U_1.V_5.Class.Depth == 0) {
    return Right;
  } else if (Right->U_1.V_5.Class.Depth == 0) {
    return Left;
  } else {
    LDepth = Right->U_1.V_5.Class.Depth;
    while (Left->U_1.V_5.Class.Depth > LDepth) {
      Left = Left->U_1.V_5.Class.BaseClass;
    }
    LDepth = Left->U_1.V_5.Class.Depth;
    while (Right->U_1.V_5.Class.Depth > LDepth) {
      Right = Right->U_1.V_5.Class.BaseClass;
    }
    while (Left != Right) {
      if (Left->U_1.V_5.Class.Depth == 1) {
        Left = Left->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.UniversalClass;
        Right = Left;
      } else {
        Left = Left->U_1.V_5.Class.BaseClass;
        Right = Right->U_1.V_5.Class.BaseClass;
      }
    }
    return Left;
  }
}

static void NextPatterns
# ifdef __STDC__
(Tree_tTree Patterns, Tree_tTree *Result, BOOLEAN *CarryOut)
# else
(Patterns, Result, CarryOut)
Tree_tTree Patterns;
Tree_tTree *Result;
BOOLEAN *CarryOut;
# endif
{
  Tree_tTree LSuffix, LCurrent;

  switch (Patterns->U_1.V_1.Kind) {
  case Tree_NoPattern:;
    *CarryOut = TRUE;
    *Result = Tree_mNoPattern(Patterns->U_1.V_44.NoPattern.Pos);
    break;
  case Tree_OnePattern:;
    NextPatterns(Patterns->U_1.V_45.OnePattern.Next, &LSuffix, CarryOut);
    *Result = Tree_mOnePattern(Tree_CopyTree(Patterns->U_1.V_45.OnePattern.Pattern), LSuffix);
    break;
  case Tree_OnePatternAlts:;
    NextPatterns(Patterns->U_1.V_46.OnePatternAlts.Next, &LSuffix, CarryOut);
    LCurrent = Patterns->U_1.V_46.OnePatternAlts.Current;
    Assertions_Assert(Tree_IsType(LCurrent->U_1.V_49.OnePatternsList.Patterns, Tree_Decompose), (STRING)"NextPatterns, Alt not Decompose.", 32L);
    *Result = Tree_mOnePattern(Tree_CopyTree(LCurrent->U_1.V_49.OnePatternsList.Patterns), LSuffix);
    if (*CarryOut) {
      LCurrent = LCurrent->U_1.V_49.OnePatternsList.Next;
      if (LCurrent->U_1.V_1.Kind == Tree_NoPatternsList) {
        Patterns->U_1.V_46.OnePatternAlts.Current = Patterns->U_1.V_46.OnePatternAlts.PatternsList;
      } else {
        *CarryOut = FALSE;
        Patterns->U_1.V_46.OnePatternAlts.Current = LCurrent;
      }
    }
    break;
  }
}

static void ExpandDecompose
# ifdef __STDC__
(Positions_tPosition Pos, Idents_tIdent Selector, Tree_tTree Expr, Tree_tTree Exprs, BOOLEAN Widen, Tree_tTree *Result, CARDINAL *PatternCount)
# else
(Pos, Selector, Expr, Exprs, Widen, Result, PatternCount)
Positions_tPosition Pos;
Idents_tIdent Selector;
Tree_tTree Expr;
Tree_tTree Exprs;
BOOLEAN Widen;
Tree_tTree *Result;
CARDINAL *PatternCount;
# endif
{
  Tree_tTree LTreeName, LClasses, LClassVarUse, LClass, LOperands;
  Tree_tTree LDecomposeExpr, LResult, LPatterns, LSingleOperands;
  CARDINAL LClassCount, LOperandsCount;
  BOOLEAN LCarryOut, LHasExactlyOneClass;

  LClassCount = 1;
  *PatternCount = 0;
  LResult = Tree_mNoPatternsList();
  switch (Expr->U_1.V_1.Kind) {
  case Tree_Index:;
    Assertions_AssertPos((BOOLEAN)(Expr->U_1.V_76.Index.Expr->U_1.V_1.Kind == Tree_VarUse), (STRING)"ExpandDecompose, Index w/o 1st VarUse.", 38L, Expr->U_1.V_76.Index.Pos);
    LTreeName = Expr->U_1.V_76.Index.Expr->U_1.V_67.VarUse.Object;
    LClasses = Expr->U_1.V_76.Index.Exprs;
    Assertions_AssertPos((BOOLEAN)(LClasses->U_1.V_1.Kind == Tree_OneExpr), (STRING)"ExpandDecompose, Index w/o Expr.", 32L, Expr->U_1.V_76.Index.Pos);
    LClassVarUse = LClasses->U_1.V_63.OneExpr.Expr;
    Assertions_AssertPos((BOOLEAN)(LClassVarUse->U_1.V_1.Kind == Tree_VarUse), (STRING)"ExpandDecompose, Index w/o 2nd VarUse.", 38L, Expr->U_1.V_76.Index.Pos);
    LClass = IdentifyClass(LTreeName->U_1.V_29.TreeName.Classes, LClassVarUse->U_1.V_67.VarUse.Name);
    LClassVarUse->U_1.V_67.VarUse.Object = LClass;
    LDecomposeExpr = Tree_mBinary(Expr->U_1.V_76.Index.Pos, Expr->U_1.V_76.Index.Selector, Expr->U_1.V_76.Index.Expr, IdentDot, LClassVarUse, Widen);
    LHasExactlyOneClass = LClasses->U_1.V_63.OneExpr.Next->U_1.V_1.Kind == Tree_NoExpr;
    break;
  case Tree_VarUse:;
    LClassVarUse = Expr;
    LClass = LClassVarUse->U_1.V_67.VarUse.Object;
    LDecomposeExpr = Expr;
    LHasExactlyOneClass = TRUE;
    break;
  case Tree_Binary:;
    Assertions_AssertPos((BOOLEAN)(Expr->U_1.V_71.Binary.Operator == IdentDot), (STRING)"ExpandDecompose, Binary w/o dot.", 32L, Expr->U_1.V_71.Binary.Pos);
    Assertions_AssertPos((BOOLEAN)(Expr->U_1.V_71.Binary.Lop->U_1.V_1.Kind == Tree_VarUse), (STRING)"ExpandDecompose, Binary w/o 1st VarUse.", 39L, Expr->U_1.V_71.Binary.Pos);
    LTreeName = Expr->U_1.V_71.Binary.Lop->U_1.V_67.VarUse.Object;
    Assertions_AssertPos((BOOLEAN)(Expr->U_1.V_71.Binary.Rop->U_1.V_1.Kind == Tree_VarUse), (STRING)"ExpandDecompose, Binary w/o 2nd VarUse.", 39L, Expr->U_1.V_71.Binary.Pos);
    LClassVarUse = Expr->U_1.V_71.Binary.Rop;
    LClass = IdentifyClass(LTreeName->U_1.V_29.TreeName.Classes, LClassVarUse->U_1.V_67.VarUse.Name);
    LClassVarUse->U_1.V_67.VarUse.Object = LClass;
    LDecomposeExpr = Expr;
    LHasExactlyOneClass = TRUE;
    break;
  default :
    Assertions_CantHappen((STRING)"ExpandDecompose, Bad Kind.", 26L);
    break;
  }
  for (;;) {
    if (LClass == Tree_NoTree) {
      Scanner_Error((STRING)"not a class or node of the required tree", 40L, LClassVarUse->U_1.V_67.VarUse.Pos);
    } else {
      Assertions_AssertPos((BOOLEAN)(LClass->U_1.V_1.Kind == Tree_Class), (STRING)"ExpandDecompose, not a class. ", 30L, Expr->U_1.V_65.Expr.Pos);
      LOperands = TransformKeyword(Exprs, LClass->U_1.V_5.Class.Formals);
      TransformPattern(LOperands, &LOperands, &LOperandsCount);
      INC1(*PatternCount, LOperandsCount);
      for (;;) {
        if (LHasExactlyOneClass && LOperandsCount == 1) {
          LSingleOperands = LOperands;
          LCarryOut = TRUE;
        } else {
          NextPatterns(LOperands, &LSingleOperands, &LCarryOut);
        }
        LPatterns = Tree_mDecompose(Pos, Selector, LDecomposeExpr, LSingleOperands, Widen);
        LPatterns->U_1.V_51.Decompose.Object = LClass;
        LResult = Tree_mOnePatternsList(LPatterns, LResult);
        if (LCarryOut) {
          goto EXIT_2;
        }
      } EXIT_2:;
    }
    if (Expr->U_1.V_1.Kind == Tree_Index) {
      for (;;) {
        LClasses = LClasses->U_1.V_63.OneExpr.Next;
        switch (LClasses->U_1.V_1.Kind) {
        case Tree_NoExpr:;
          LClassVarUse = Tree_NoTree;
          goto EXIT_3;
          break;
        case Tree_NamedExpr:;
          LClassVarUse = LClasses->U_1.V_64.NamedExpr.Expr;
          Scanner_Error((STRING)"named expression not allowed in a type", 38L, LClassVarUse->U_1.V_65.Expr.Pos);
          if (LClassVarUse->U_1.V_1.Kind != Tree_VarUse) {
            Scanner_Error((STRING)"single identifier required in a type", 36L, LClassVarUse->U_1.V_65.Expr.Pos);
          }
          break;
        case Tree_OneExpr:;
          LClassVarUse = LClasses->U_1.V_63.OneExpr.Expr;
          if (LClassVarUse->U_1.V_1.Kind != Tree_VarUse) {
            Scanner_Error((STRING)"single identifier required in a type", 36L, LClassVarUse->U_1.V_65.Expr.Pos);
          } else {
            INC(LClassCount);
            LClass = IdentifyClass(LTreeName->U_1.V_29.TreeName.Classes, LClassVarUse->U_1.V_67.VarUse.Name);
            LClassVarUse->U_1.V_67.VarUse.Object = LClass;
            LDecomposeExpr = Tree_mBinary(Expr->U_1.V_76.Index.Pos, Expr->U_1.V_76.Index.Selector, Expr->U_1.V_76.Index.Expr, IdentDot, LClassVarUse, Widen);
            goto EXIT_3;
          }
          break;
        default :
          Assertions_CantHappenPos((STRING)"ExpandDecompose, not an expr.", 29L, LClassVarUse->U_1.V_67.VarUse.Pos);
          break;
        }
      } EXIT_3:;
      if (LClassVarUse == Tree_NoTree) {
        goto EXIT_1;
      }
    } else {
      goto EXIT_1;
    }
  } EXIT_1:;
  if (*PatternCount == 1) {
    *Result = LResult->U_1.V_49.OnePatternsList.Patterns;
  } else {
    *Result = Tree_ReverseTree(LResult);
  }
}

static BOOLEAN IsAllDontCares
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Tree_tTree LExprs, LExpr;

  LExprs = t;
  for (;;) {
    if (LExprs->U_1.V_1.Kind == Tree_NoExpr) {
      return TRUE;
    } else if (LExprs->U_1.V_1.Kind == Tree_OneExpr) {
      LExpr = LExprs->U_1.V_63.OneExpr.Expr;
      if (Tree_IsType(LExpr, Tree_DontCare)) {
        return TRUE;
      } else if (Tree_IsType(LExpr, Tree_DontCare1)) {
        LExprs = LExprs->U_1.V_63.OneExpr.Next;
      } else {
        return FALSE;
      }
    } else {
      return FALSE;
    }
  } EXIT_4:;
}

static Tree_tTree MakeValue
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Idents_tIdent LSelector;

  LSelector = t->U_1.V_65.Expr.Selector;
  t->U_1.V_65.Expr.Selector = Idents_NoIdent;
  return Tree_mValue(t->U_1.V_65.Expr.Pos, LSelector, TransformExpr(t));
}

static void TransformPattern
# ifdef __STDC__
(Tree_tTree t, Tree_tTree *Result, CARDINAL *PatternCount)
# else
(t, Result, PatternCount)
Tree_tTree t;
Tree_tTree *Result;
CARDINAL *PatternCount;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    *Result = Tree_mOnePattern(Tree_mDontCareInternal(t->U_1.V_62.NoExpr.Pos), Tree_mNoPattern(t->U_1.V_62.NoExpr.Pos));
    *PatternCount = 1;
  } else {
    TransformPatternRecurse(t, Result, PatternCount);
  }
}

static void TransformPatternRecurse
# ifdef __STDC__
(Tree_tTree t, Tree_tTree *Result, CARDINAL *PatternCount)
# else
(t, Result, PatternCount)
Tree_tTree t;
Tree_tTree *Result;
CARDINAL *PatternCount;
# endif
{
  Tree_tTree TreeName, s, LTreeName, LClass, LPrefixVarUse, L1stVarUse;
  Tree_tTree LTree1, LTree2;
  CARDINAL LThisCount, LNextCount;

  *PatternCount = 1;
  switch (t->U_1.V_1.Kind) {
  case Tree_NoExpr:;
    *Result = Tree_mNoPattern(t->U_1.V_62.NoExpr.Pos);
    break;
  case Tree_OneExpr:;
    {
      register Tree_yOneExpr *W_3 = &t->U_1.V_63.OneExpr;

      TransformPatternRecurse(W_3->Expr, &LTree1, &LThisCount);
      TransformPatternRecurse(W_3->Next, &LTree2, &LNextCount);
      if (LThisCount == 1) {
        *Result = Tree_mOnePattern(LTree1, LTree2);
      } else {
        *Result = Tree_mOnePatternAlts(LTree1, LTree2, LTree1);
      }
      *PatternCount = LThisCount * LNextCount;
    }
    break;
  case Tree_NamedExpr:;
    {
      register Tree_yNamedExpr *W_4 = &t->U_1.V_64.NamedExpr;

      Scanner_Error((STRING)"illegal context for named association", 37L, W_4->Expr->U_1.V_65.Expr.Pos);
      TransformPatternRecurse(W_4->Expr, &LTree1, &LThisCount);
      TransformPatternRecurse(W_4->Next, &LTree2, &LNextCount);
      if (LThisCount == 1) {
        *Result = Tree_mOnePattern(LTree1, LTree2);
      } else {
        *Result = Tree_mOnePatternAlts(LTree1, LTree2, LTree1);
      }
      *PatternCount = LThisCount * LNextCount;
    }
    break;
  case Tree_Parents:;
    if (Tree_IsType(t->U_1.V_77.Parents.Expr, Tree_DontCare1)) {
      *Result = t->U_1.V_77.Parents.Expr;
      if (t->U_1.V_77.Parents.Selector != Idents_NoIdent) {
        if ((*Result)->U_1.V_54.DontCare1.Selector != Idents_NoIdent && (*Result)->U_1.V_54.DontCare1.Selector != t->U_1.V_77.Parents.Selector) {
          Scanner_WarningI((STRING)"Label ignored:", 14L, t->U_1.V_77.Parents.Pos, t->U_1.V_77.Parents.Selector);
        } else {
          (*Result)->U_1.V_54.DontCare1.Selector = t->U_1.V_77.Parents.Selector;
        }
      }
    } else {
      *Result = MakeValue(t);
    }
    break;
  case Tree_Nil:;
    {
      register Tree_yNil *W_5 = &t->U_1.V_69.Nil;

      *Result = Tree_mNilTest(W_5->Pos, W_5->Selector, W_5->Widen);
    }
    break;
  case Tree_DontCareExplicit:;
  case Tree_DontCareInternal:;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    *Result = t;
    break;
  case Tree_DontCare1:;
  case Tree_DontCare:;
    Assertions_CantHappen((STRING)"TransformPatternRecurse, undistinguished DontCare", 49L);
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_6 = &t->U_1.V_66.Compose;

      if (W_6->Expr->U_1.V_1.Kind == Tree_Index) {
        if (W_6->Expr->U_1.V_76.Index.Expr->U_1.V_1.Kind == Tree_VarUse && Tree_IsType(W_6->Expr->U_1.V_76.Index.Exprs, Tree_OneExpr) && W_6->Expr->U_1.V_76.Index.Exprs->U_1.V_63.OneExpr.Expr->U_1.V_1.Kind == Tree_VarUse) {
          LPrefixVarUse = W_6->Expr->U_1.V_76.Index.Expr;
          L1stVarUse = W_6->Expr->U_1.V_76.Index.Exprs->U_1.V_63.OneExpr.Expr;
          if (LPrefixVarUse->U_1.V_67.VarUse.Name == Idents_NoIdent) {
            W_6->Object = IdentifyClass2(L1stVarUse->U_1.V_67.VarUse.Name, &LTreeName);
            LPrefixVarUse->U_1.V_67.VarUse.Object = LTreeName;
            L1stVarUse->U_1.V_67.VarUse.Object = W_6->Object;
            if (W_6->Object == Tree_NoTree) {
              Scanner_Error((STRING)"node type not declared", 22L, L1stVarUse->U_1.V_67.VarUse.Pos);
              *Result = Tree_mDontCareInternal(W_6->Pos);
            } else {
              ExpandDecompose(W_6->Pos, W_6->Selector, W_6->Expr, W_6->Exprs, W_6->Widen, Result, PatternCount);
            }
          } else {
            LTreeName = IdentifyTree(LPrefixVarUse->U_1.V_67.VarUse.Name);
            LPrefixVarUse->U_1.V_67.VarUse.Object = LTreeName;
            if (LTreeName == Tree_NoTree) {
              *Result = MakeValue(t);
            } else {
              W_6->Object = IdentifyClass(LTreeName->U_1.V_29.TreeName.Classes, L1stVarUse->U_1.V_67.VarUse.Name);
              L1stVarUse->U_1.V_67.VarUse.Object = W_6->Object;
              if (W_6->Object == Tree_NoTree) {
                *Result = MakeValue(t);
              } else {
                ExpandDecompose(W_6->Pos, W_6->Selector, W_6->Expr, W_6->Exprs, W_6->Widen, Result, PatternCount);
              }
            }
          }
        } else {
          *Result = MakeValue(t);
        }
      } else if (IsAllDontCares(W_6->Exprs) && (Tree_IsType(W_6->Expr, Tree_DontCare1) || Tree_IsType(W_6->Expr, Tree_VarUse) && W_6->Expr->U_1.V_67.VarUse.Name == Idents_NoIdent)) {
        *Result = W_6->Expr;
      } else {
        if (W_6->Expr->U_1.V_1.Kind == Tree_VarUse) {
          W_6->Object = IdentifyClass2(W_6->Expr->U_1.V_67.VarUse.Name, &TreeName);
          if (W_6->Object == Tree_NoTree) {
            W_6->Object = IdentifyProc(W_6->Expr->U_1.V_67.VarUse.Name);
          }
          W_6->Expr->U_1.V_67.VarUse.Object = W_6->Object;
        } else if (W_6->Expr->U_1.V_1.Kind == Tree_Binary && W_6->Expr->U_1.V_71.Binary.Operator == IdentDot && W_6->Expr->U_1.V_71.Binary.Lop->U_1.V_1.Kind == Tree_VarUse && W_6->Expr->U_1.V_71.Binary.Rop->U_1.V_1.Kind == Tree_VarUse) {
          W_6->Object = IdentifyTree(W_6->Expr->U_1.V_71.Binary.Lop->U_1.V_67.VarUse.Name);
          W_6->Expr->U_1.V_71.Binary.Lop->U_1.V_67.VarUse.Object = W_6->Object;
          if (W_6->Object != Tree_NoTree) {
            W_6->Object = IdentifyClass(W_6->Object->U_1.V_29.TreeName.Classes, W_6->Expr->U_1.V_71.Binary.Rop->U_1.V_67.VarUse.Name);
          }
          W_6->Expr->U_1.V_71.Binary.Rop->U_1.V_67.VarUse.Object = W_6->Object;
        } else {
          *Result = MakeValue(W_6->Expr);
          W_6->Object = Tree_NoTree;
        }
        if (W_6->Object != Tree_NoTree) {
          if (W_6->Object->U_1.V_1.Kind == Tree_Class) {
            ExpandDecompose(W_6->Pos, W_6->Selector, W_6->Expr, W_6->Exprs, W_6->Widen, Result, PatternCount);
          } else {
            s = Tree_mCall(W_6->Pos, Idents_NoIdent, W_6->Expr, TransformExpr(W_6->Exprs), Tree_mNoPattern(W_6->Pos));
            s->U_1.V_70.Call.Object = W_6->Object;
            *Result = Tree_mValue(W_6->Pos, W_6->Selector, s);
          }
        } else {
          s = Tree_mCall(W_6->Pos, Idents_NoIdent, W_6->Expr, TransformExpr(W_6->Exprs), Tree_mNoExpr(W_6->Pos));
          s->U_1.V_70.Call.Object = W_6->Object;
          *Result = Tree_mValue(W_6->Pos, W_6->Selector, s);
        }
      }
    }
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_7 = &t->U_1.V_67.VarUse;

      if (W_7->Name == Idents_NoIdent) {
        *Result = Tree_mVarDef(W_7->Pos, W_7->Selector, TRUE);
      } else {
        W_7->Object = IdentifyClass2(W_7->Name, &TreeName);
        if (W_7->Object != Tree_NoTree && Sets_IsElement(ORD('p'), &Tree_Options)) {
          *Result = Tree_mDecompose(W_7->Pos, W_7->Selector, t, Tree_mOnePattern(Tree_mDontCareInternal(W_7->Pos), Tree_mNoPattern(W_7->Pos)), W_7->Widen);
          t->U_1.V_67.VarUse.Selector = Idents_NoIdent;
          (*Result)->U_1.V_51.Decompose.Object = W_7->Object;
        } else if (Sets_IsElement((Sets_tElement)W_7->Name, &ExternNames) || Sets_IsElement((Sets_tElement)W_7->Name, &LocExternNames) || Sets_IsElement((Sets_tElement)W_7->Name, &UserNames) || Sets_IsElement((Sets_tElement)W_7->Name, &RoutineNames)) {
          *Result = MakeValue(t);
        } else if (W_7->Selector != Idents_NoIdent) {
          *Result = MakeValue(t);
        } else {
          *Result = Tree_mVarDef(W_7->Pos, W_7->Name, FALSE);
        }
      }
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_8 = &t->U_1.V_71.Binary;

      if (Sets_IsElement(ORD('p'), &Tree_Options) && W_8->Operator == IdentDot && W_8->Lop->U_1.V_1.Kind == Tree_VarUse && W_8->Rop->U_1.V_1.Kind == Tree_VarUse) {
        LTreeName = IdentifyTree(W_8->Lop->U_1.V_67.VarUse.Name);
        if (LTreeName != Tree_NoTree) {
          LClass = IdentifyClass(LTreeName->U_1.V_29.TreeName.Classes, W_8->Rop->U_1.V_67.VarUse.Name);
          if (LClass != Tree_NoTree) {
            W_8->Lop->U_1.V_67.VarUse.Object = LTreeName;
            W_8->Rop->U_1.V_67.VarUse.Object = LClass;
            *Result = Tree_mDecompose(W_8->Pos, W_8->Selector, t, Tree_mOnePattern(Tree_mDontCareInternal(W_8->Pos), Tree_mNoPattern(W_8->Pos)), W_8->Widen);
            (*Result)->U_1.V_51.Decompose.Object = LClass;
          } else {
            *Result = MakeValue(t);
          }
        } else {
          *Result = MakeValue(t);
        }
      } else {
        *Result = MakeValue(t);
      }
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_9 = &t->U_1.V_76.Index;

      if (Sets_IsElement(ORD('p'), &Tree_Options) && W_9->Expr->U_1.V_1.Kind == Tree_VarUse && Tree_IsType(W_9->Exprs, Tree_OneExpr) && W_9->Exprs->U_1.V_63.OneExpr.Expr->U_1.V_1.Kind == Tree_VarUse) {
        L1stVarUse = W_9->Exprs->U_1.V_63.OneExpr.Expr;
        if (W_9->Expr->U_1.V_67.VarUse.Name == Idents_NoIdent) {
          LClass = IdentifyClass2(L1stVarUse->U_1.V_67.VarUse.Name, &LTreeName);
          W_9->Expr->U_1.V_67.VarUse.Object = LTreeName;
          L1stVarUse->U_1.V_67.VarUse.Object = LClass;
          if (LClass == Tree_NoTree) {
            Scanner_Error((STRING)"node type not declared", 22L, L1stVarUse->U_1.V_67.VarUse.Pos);
            *Result = Tree_mDontCare1Internal(L1stVarUse->U_1.V_67.VarUse.Pos, W_9->Selector);
          } else {
            ExpandDecompose(W_9->Pos, W_9->Selector, t, Tree_mOnePattern(Tree_mDontCareInternal(W_9->Pos), Tree_mNoPattern(W_9->Pos)), W_9->Widen, Result, PatternCount);
          }
        } else {
          LTreeName = IdentifyTree(W_9->Expr->U_1.V_67.VarUse.Name);
          W_9->Expr->U_1.V_67.VarUse.Object = LTreeName;
          if (LTreeName == Tree_NoTree) {
            *Result = MakeValue(t);
          } else {
            LClass = IdentifyClass(LTreeName->U_1.V_29.TreeName.Classes, L1stVarUse->U_1.V_67.VarUse.Name);
            L1stVarUse->U_1.V_67.VarUse.Object = LClass;
            if (LClass == Tree_NoTree) {
              *Result = MakeValue(t);
            } else {
              ExpandDecompose(W_9->Pos, W_9->Selector, t, Tree_mOnePattern(Tree_mDontCareInternal(W_9->Pos), Tree_mNoPattern(W_9->Pos)), W_9->Widen, Result, PatternCount);
            }
          }
        }
      } else {
        *Result = MakeValue(t);
      }
    }
    break;
  case Tree_Call:;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
  case Tree_TargetExpr:;
  case Tree_StringExpr:;
  case Tree_AttrDesc:;
    *Result = MakeValue(t);
    break;
  case Tree_NoPattern:;
  case Tree_OnePattern:;
  case Tree_OnePatternAlts:;
    Assertions_CantHappen((STRING)"TransformPatternRecurse, already transformed.", 45L);
    *Result = t;
    break;
  }
}

static Tree_tTree TransformExpr
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Tree_tTree TreeName, s, LObject1, LObject2;
  CARDINAL LPatternCount;

  switch (t->U_1.V_1.Kind) {
  case Tree_NoExpr:;
    break;
  case Tree_OneExpr:;
    {
      register Tree_yOneExpr *W_10 = &t->U_1.V_63.OneExpr;

      W_10->Expr = TransformExpr(W_10->Expr);
      W_10->Next = TransformExpr(W_10->Next);
    }
    break;
  case Tree_NamedExpr:;
    {
      register Tree_yNamedExpr *W_11 = &t->U_1.V_64.NamedExpr;

      Scanner_Error((STRING)"Keyword notation illegal in an expression", 41L, t->U_1.V_64.NamedExpr.Expr->U_1.V_65.Expr.Pos);
      return Tree_mOneExpr(TransformExpr(W_11->Expr), TransformExpr(W_11->Next));
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_12 = &t->U_1.V_66.Compose;

      if (W_12->Expr->U_1.V_1.Kind == Tree_VarUse) {
        W_12->Object = IdentifyClass2(W_12->Expr->U_1.V_67.VarUse.Name, &TreeName);
        if (W_12->Object == Tree_NoTree) {
          W_12->Object = IdentifyProc(W_12->Expr->U_1.V_67.VarUse.Name);
        }
        W_12->Expr->U_1.V_67.VarUse.Object = W_12->Object;
      } else if (W_12->Expr->U_1.V_1.Kind == Tree_Binary && W_12->Expr->U_1.V_71.Binary.Lop->U_1.V_1.Kind == Tree_VarUse && W_12->Expr->U_1.V_71.Binary.Rop->U_1.V_1.Kind == Tree_VarUse) {
        W_12->Object = IdentifyTree(W_12->Expr->U_1.V_71.Binary.Lop->U_1.V_67.VarUse.Name);
        if (W_12->Object != Tree_NoTree) {
          W_12->Object = IdentifyClass(W_12->Object->U_1.V_29.TreeName.Classes, W_12->Expr->U_1.V_71.Binary.Rop->U_1.V_67.VarUse.Name);
        }
        if (W_12->Object == Tree_NoTree) {
          W_12->Expr->U_1.V_71.Binary.Lop->U_1.V_67.VarUse.Object = Tree_NoTree;
          W_12->Expr->U_1.V_71.Binary.Rop->U_1.V_67.VarUse.Object = Tree_NoTree;
        }
      } else {
        W_12->Object = Tree_NoTree;
        W_12->Expr = TransformExpr(W_12->Expr);
      }
      if (W_12->Object != Tree_NoTree) {
        if (W_12->Object->U_1.V_1.Kind == Tree_Class) {
          W_12->Exprs = TransformKeyword(W_12->Exprs, W_12->Object->U_1.V_5.Class.Formals);
          W_12->Exprs = TransformExpr(W_12->Exprs);
          return t;
        } else {
          s = Tree_mCall(W_12->Pos, W_12->Selector, W_12->Expr, TransformExpr(W_12->Exprs), Tree_mNoPattern(W_12->Pos));
          s->U_1.V_70.Call.Object = W_12->Object;
          return s;
        }
      } else {
        s = Tree_mCall(W_12->Pos, W_12->Selector, W_12->Expr, TransformExpr(W_12->Exprs), Tree_mNoExpr(W_12->Pos));
        s->U_1.V_70.Call.Object = W_12->Object;
        return s;
      }
    }
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_13 = &t->U_1.V_67.VarUse;

      W_13->Object = IdentifyClass2(W_13->Name, &TreeName);
      if (Sets_IsElement(ORD('p'), &Tree_Options) && W_13->Object != Tree_NoTree) {
        s = Tree_mCompose(W_13->Pos, Idents_NoIdent, t, Tree_mOneExpr(Tree_mDontCareInternal(W_13->Pos), Tree_mNoExpr(W_13->Pos)), FALSE);
        s->U_1.V_66.Compose.Object = W_13->Object;
        return s;
      } else {
        W_13->Object = Tree_NoTree;
        return t;
      }
    }
    break;
  case Tree_Nil:;
    break;
  case Tree_DontCare1Explicit:;
    break;
  case Tree_DontCare1Internal:;
    break;
  case Tree_DontCareExplicit:;
    break;
  case Tree_DontCareInternal:;
    break;
  case Tree_DontCare1:;
  case Tree_DontCare:;
    Assertions_CantHappen((STRING)"TransformExpr, undistinguished DontCare", 39L);
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_14 = &t->U_1.V_70.Call;

      if (W_14->Expr->U_1.V_1.Kind == Tree_VarUse) {
        W_14->Object = IdentifyProc(W_14->Expr->U_1.V_67.VarUse.Name);
      } else {
        W_14->Object = Tree_NoTree;
      }
      W_14->Expr = TransformExpr(W_14->Expr);
      W_14->Exprs = TransformExpr(W_14->Exprs);
      if (W_14->Object != Tree_NoTree) {
        TransformPattern(W_14->Patterns, &W_14->Patterns, &LPatternCount);
        if (LPatternCount > 1) {
          Scanner_Error((STRING)"pattern containing multi-valued types not allowed as actual to out formal", 73L, W_14->Pos);
        }
      } else if (W_14->Patterns->U_1.V_1.Kind == Tree_OneExpr) {
        Scanner_Error((STRING)"Call on user procedure cannot have result patterns", 50L, W_14->Pos);
        W_14->Patterns = TransformExpr(W_14->Patterns);
      }
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_15 = &t->U_1.V_71.Binary;

      if (W_15->Operator == IdentDot && W_15->Lop->U_1.V_1.Kind == Tree_VarUse && W_15->Rop->U_1.V_1.Kind == Tree_VarUse) {
        if (Sets_IsElement(ORD('p'), &Tree_Options)) {
          LObject1 = IdentifyTree(W_15->Lop->U_1.V_67.VarUse.Name);
          if (LObject1 != Tree_NoTree) {
            LObject2 = IdentifyClass(LObject1->U_1.V_29.TreeName.Classes, W_15->Rop->U_1.V_67.VarUse.Name);
            if (LObject2 != Tree_NoTree) {
              s = Tree_mCompose(W_15->Pos, Idents_NoIdent, t, Tree_mOneExpr(Tree_mDontCareInternal(W_15->Pos), Tree_mNoExpr(W_15->Pos)), FALSE);
              s->U_1.V_66.Compose.Object = LObject2;
              W_15->Lop->U_1.V_67.VarUse.Object = LObject1;
              W_15->Rop->U_1.V_67.VarUse.Object = LObject2;
              return s;
            }
          }
        }
      } else {
        W_15->Lop = TransformExpr(W_15->Lop);
        W_15->Rop = TransformExpr(W_15->Rop);
      }
    }
    break;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinaryCompound *W_16 = &t->U_1.V_73.BinaryCompound;

      W_16->Lop = TransformExpr(W_16->Lop);
      W_16->Rop = TransformExpr(W_16->Rop);
    }
    break;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
    {
      register Tree_yPreOperator *W_17 = &t->U_1.V_74.PreOperator;

      W_17->Expr = TransformExpr(W_17->Expr);
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_18 = &t->U_1.V_76.Index;

      W_18->Expr = TransformExpr(W_18->Expr);
      W_18->Exprs = TransformExpr(W_18->Exprs);
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_19 = &t->U_1.V_77.Parents;

      W_19->Expr = TransformExpr(W_19->Expr);
    }
    break;
  case Tree_TargetExpr:;
    break;
  case Tree_StringExpr:;
    break;
  case Tree_AttrDesc:;
    break;
  }
  return t;
}

static Tree_tTree TransformStmt
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_NoStatement:;
    return t;
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_20 = &t->U_1.V_83.ProcCall;

      W_20->Call = TransformExpr(W_20->Call);
      if (W_20->Call->U_1.V_1.Kind == Tree_Call) {
        {
          register Tree_yCall *W_21 = &W_20->Call->U_1.V_70.Call;

          if (W_21->Object != Tree_NoTree && (W_21->Object->U_1.V_1.Kind == Tree_Predicate || W_21->Object->U_1.V_1.Kind == Tree_Function)) {
            t->U_1.V_1.Kind = Tree_Condition;
          }
        }
      } else if (W_20->Call->U_1.V_1.Kind == Tree_Compose) {
        Scanner_Error((STRING)"Node constructor as a statement", 31L, W_20->Pos);
      } else if (W_20->Call->U_1.V_1.Kind == Tree_StringExpr) {
        t = Tree_mWriteStr(W_20->Pos, W_20->Next, W_20->Call->U_1.V_79.StringExpr.String);
      } else {
        t->U_1.V_1.Kind = Tree_Condition;
      }
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_22 = &t->U_1.V_85.Assignment;

      W_22->Adr = TransformExpr(W_22->Adr);
      W_22->Expr = TransformExpr(W_22->Expr);
    }
    break;
  case Tree_Reject:;
    break;
  case Tree_Fail:;
    break;
  case Tree_TargetStmt:;
    break;
  case Tree_Nl:;
    break;
  case Tree_WriteStr:;
    break;
  }
  t->U_1.V_82.Statement.Next = TransformStmt(t->U_1.V_82.Statement.Next);
  return t;
}

static Tree_tTree TransformKeyword
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Tree_tTree Exprs;
  Tree_tTree *Last;
  INTEGER n, i, Minimum, Maximum;
  LONGINT PatternsSize;
  struct S_7 *PatternsPtr;
  BOOLEAN LHasDontCare;

  Exprs = t;
  while (Exprs->U_1.V_1.Kind == Tree_OneExpr) {
    Exprs = Exprs->U_1.V_63.OneExpr.Next;
  }
  if (Exprs->U_1.V_1.Kind == Tree_NoExpr) {
    return t;
  } else {
    while (Exprs->U_1.V_1.Kind == Tree_NamedExpr) {
      Exprs = Exprs->U_1.V_64.NamedExpr.Next;
    }
    if (Exprs->U_1.V_1.Kind == Tree_OneExpr) {
      Assertions_Assert((BOOLEAN)(Exprs->U_1.V_63.OneExpr.Expr->U_1.V_1.Kind == Tree_DontCareExplicit && Exprs->U_1.V_63.OneExpr.Next->U_1.V_1.Kind == Tree_NoExpr), (STRING)"Semantics.TransformKeyword, bad form following NamedExpr", 56L);
      LHasDontCare = TRUE;
    } else {
      LHasDontCare = FALSE;
    }
  }
  n = 0;
  Exprs = Formals;
  while (Tree_IsType(Exprs, Tree_Formal)) {
    INC(n);
    Exprs = Exprs->U_1.V_93.Formal.Next;
  }
  PatternsSize = n + 1;
  DynArray_MakeArray((ADDRESS *)&PatternsPtr, &PatternsSize, (LONGINT)sizeof(Tree_tTree));
  {
    LONGINT B_1 = 1, B_2 = n;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        PatternsPtr->A[i] = Tree_NoTree;
        if (i >= B_2) break;
      }
  }
  Last = (Tree_tTree *)ADR(t);
  Exprs = t;
  i = 0;
  while (Exprs->U_1.V_1.Kind == Tree_OneExpr) {
    INC(i);
    PatternsPtr->A[i] = Exprs->U_1.V_63.OneExpr.Expr;
    Last = (Tree_tTree *)ADR(Exprs->U_1.V_63.OneExpr.Next);
    Exprs = Exprs->U_1.V_63.OneExpr.Next;
  }
  Minimum = i + 1;
  Maximum = i;
  while (Exprs->U_1.V_1.Kind == Tree_NamedExpr) {
    i = LookupFormal(Exprs->U_1.V_64.NamedExpr.Name, Formals);
    if (i == 0) {
      Scanner_ErrorI((STRING)"No such formal/child name", 25L, Exprs->U_1.V_64.NamedExpr.NamePos, Exprs->U_1.V_64.NamedExpr.Name);
    } else if (PatternsPtr->A[i] != Tree_NoTree) {
      Scanner_ErrorI((STRING)"this formal/child was previously supplied", 41L, Exprs->U_1.V_64.NamedExpr.NamePos, Exprs->U_1.V_64.NamedExpr.Name);
    } else {
      PatternsPtr->A[i] = Exprs->U_1.V_64.NamedExpr.Expr;
    }
    Maximum = General_Max(Maximum, i);
    Exprs = Exprs->U_1.V_64.NamedExpr.Next;
  }
  if (!LHasDontCare) {
    Exprs = Tree_mOneExpr(Tree_mDontCareInternal(Positions_NoPosition), Tree_mNoExpr(Positions_NoPosition));
  }
  {
    LONGINT B_3 = Maximum, B_4 = Minimum;

    if (B_3 >= B_4)
      for (i = B_3;; i += -1) {
        if (PatternsPtr->A[i] == Tree_NoTree) {
          if (LHasDontCare) {
            Exprs = Tree_mOneExpr(Tree_mDontCare1Explicit(Positions_NoPosition, Idents_NoIdent), Exprs);
          } else {
            Exprs = Tree_mOneExpr(Tree_mDontCare1Internal(Positions_NoPosition, Idents_NoIdent), Exprs);
          }
        } else {
          Exprs = Tree_mOneExpr(PatternsPtr->A[i], Exprs);
        }
        if (i <= B_4) break;
      }
  }
  *Last = Exprs;
  DynArray_ReleaseArray((ADDRESS *)&PatternsPtr, &PatternsSize, (LONGINT)sizeof(Tree_tTree));
  return t;
}

static void CheckExprList
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr && !Tree_IsType(Formals, Tree_Formal)) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    Scanner_Error((STRING)"too few expressions or arguments", 32L, t->U_1.V_62.NoExpr.Pos);
    return;
  }
  {
    register Tree_yOneExpr *W_23 = &t->U_1.V_63.OneExpr;

    if (Tree_IsType(W_23->Expr, Tree_DontCare)) {
      return;
    }
    if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
      Scanner_Error((STRING)"too many expressions or arguments", 33L, W_23->Expr->U_1.V_65.Expr.Pos);
      return;
    }
    CheckExpr(&W_23->Expr, Formals);
    CheckExprList(W_23->Next, Formals->U_1.V_93.Formal.Next);
  }
}

static void CheckInParams
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr || !Tree_IsType(Formals, Tree_Formal)) {
    return;
  }
  {
    register Tree_yOneExpr *W_24 = &t->U_1.V_63.OneExpr;

    if (Tree_IsType(W_24->Expr, Tree_DontCare)) {
      return;
    }
    if (Formals->U_1.V_93.Formal.Path->U_1.V_101.Var.IsOutput && W_24->Expr->U_1.V_1.Kind == Tree_VarUse && W_24->Expr->U_1.V_67.VarUse.Object != Tree_NoTree && W_24->Expr->U_1.V_67.VarUse.Object->U_1.V_93.Formal.Path->U_1.V_1.Kind == Tree_Var && !W_24->Expr->U_1.V_67.VarUse.Object->U_1.V_93.Formal.Path->U_1.V_101.Var.IsOutput) {
      W_24->Expr->U_1.V_67.VarUse.Object->U_1.V_93.Formal.Path->U_1.V_101.Var.IsRegister = FALSE;
    }
    CheckInParams(W_24->Next, Formals->U_1.V_93.Formal.Next);
  }
}

static void CheckCallExprs
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr && !Tree_IsType(Formals, Tree_Formal)) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    Scanner_Error((STRING)"too few actual parameters", 25L, t->U_1.V_62.NoExpr.Pos);
    return;
  }
  {
    register Tree_yOneExpr *W_25 = &t->U_1.V_63.OneExpr;

    if (Tree_IsType(W_25->Expr, Tree_DontCare)) {
      W_25->Expr->U_1.V_57.DontCare.Tempos = MakeTempos(Formals);
      return;
    }
    if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
      Scanner_Error((STRING)"too many actual parameters", 26L, W_25->Expr->U_1.V_65.Expr.Pos);
      return;
    }
    CheckExprVar(&W_25->Expr, Formals);
    CheckCallExprs(W_25->Next, Formals->U_1.V_93.Formal.Next);
  }
}

static void CheckExprVar
# ifdef __STDC__
(Tree_tTree *t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree *t;
Tree_tTree Formals;
# endif
{
  if ((*t)->U_1.V_1.Kind == Tree_Compose) {
    (*t)->U_1.V_66.Compose.Tempo = MakeTempoIdent();
    if (Tree_IsType(Formals, Tree_Formal)) {
      (*t)->U_1.V_66.Compose.TypeDesc = Formals->U_1.V_93.Formal.TypeDesc;
    } else {
      (*t)->U_1.V_66.Compose.TypeDesc = (*t)->U_1.V_66.Compose.Object->U_1.V_5.Class.TypeDesc;
    }
  } else if (Tree_IsType(*t, Tree_DontCare1)) {
    (*t)->U_1.V_54.DontCare1.Tempo = MakeTempoIdent();
    if (Tree_IsType(Formals, Tree_Formal)) {
      (*t)->U_1.V_54.DontCare1.TypeDesc = Formals->U_1.V_93.Formal.TypeDesc;
    } else {
      Scanner_Error((STRING)"Dont care in illegal context", 28L, (*t)->U_1.V_54.DontCare1.Pos);
    }
  }
  CheckExpr(t, Formals);
}

static void CheckExpr
# ifdef __STDC__
(Tree_tTree *t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree *t;
Tree_tTree Formals;
# endif
{
  Tree_tTree LAttrFormal;
  Tree_tTree LObject;
  Tree_tTree LResult;
  Tree_tTree LHides;

  if (Tree_IsType(*t, Tree_Expr) && (*t)->U_1.V_65.Expr.Selector != Idents_NoIdent) {
    Scanner_WarningI((STRING)"Label on expression ignored", 27L, (*t)->U_1.V_65.Expr.Pos, (*t)->U_1.V_65.Expr.Selector);
  }
  switch ((*t)->U_1.V_1.Kind) {
  case Tree_Compose:;
    {
      register Tree_yCompose *W_26 = &(*t)->U_1.V_66.Compose;

      if (Tree_IsType(Formals, Tree_Formal)) {
        CheckSubtype(Formals->U_1.V_93.Formal.TypeDesc, W_26->Object->U_1.V_5.Class.TypeDesc, W_26->Pos, (STRING)"Composed node not in formal/child type, specifically:", 53L);
      }
      if (W_26->Object == Tree_NoTree) {
        CheckExpr(&W_26->Expr, dFormals);
      } else {
        CheckExpr2(&W_26->Expr);
      }
      CheckExprList(W_26->Exprs, W_26->Object->U_1.V_5.Class.Formals);
    }
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_27 = &(*t)->U_1.V_67.VarUse;

      if (W_27->Name == Idents_NoIdent) {
        Scanner_Error((STRING)"Empty Expression", 16L, (*t)->U_1.V_67.VarUse.Pos);
      } else if (Sets_IsElement((Sets_tElement)W_27->Name, &LabelNames)) {
        W_27->Object = Semantics_IdentifyVar(Decls, W_27->Name);
        if (W_27->Object != Tree_NoTree && Tree_IsType(W_27->Object, Tree_Formal)) {
          LHides = W_27->Object->U_1.V_93.Formal.Hides;
          if (LHides != Tree_NoTree && Tree_IsType(LHides, Tree_Formal)) {
            WarningIPP((STRING)"Use of \"", 8L, W_27->Name, (STRING)"\", declared at ", 15L, W_27->Object->U_1.V_93.Formal.DeclPos, (STRING)", which hides a declaration at ", 31L, LHides->U_1.V_93.Formal.DeclPos, W_27->Pos);
          }
        }
        if (W_27->Object != Tree_NoTree && Tree_IsType(Formals, Tree_Formal)) {
          CheckSubtype(Formals->U_1.V_93.Formal.TypeDesc, W_27->Object->U_1.V_93.Formal.TypeDesc, W_27->Pos, (STRING)"Type of label reference not in formal/child type, specifically:", 63L);
        }
      } else if (!Sets_IsElement((Sets_tElement)W_27->Name, &ExternNames) && !Sets_IsElement((Sets_tElement)W_27->Name, &LocExternNames) && !Sets_IsElement((Sets_tElement)W_27->Name, &UserNames) && !Sets_IsElement((Sets_tElement)W_27->Name, &RoutineNames)) {
        if (Sets_IsElement(ORD('e'), &Tree_Options)) {
          Scanner_ErrorI((STRING)"identifier in expression not declared", 37L, W_27->Pos, W_27->Name);
        } else if (Sets_IsElement(ORD('v'), &Tree_Options) && !Sets_IsElement(ORD('s'), &Tree_Options)) {
          Scanner_WarningI((STRING)"identifier in expression not declared", 37L, W_27->Pos, W_27->Name);
        }
        Sets_Include(&LabelNames, (Sets_tElement)W_27->Name);
      }
    }
    break;
  case Tree_Nil:;
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_28 = &(*t)->U_1.V_70.Call;

      if (W_28->Object == Tree_NoTree) {
        CheckExpr(&W_28->Expr, dFormals);
        if (W_28->Expr->U_1.V_1.Kind == Tree_VarUse) {
          ProcName = W_28->Expr->U_1.V_67.VarUse.Name;
        } else if (W_28->Expr->U_1.V_1.Kind == Tree_Binary && W_28->Expr->U_1.V_71.Binary.Lop->U_1.V_1.Kind == Tree_VarUse) {
          ProcName = W_28->Expr->U_1.V_71.Binary.Lop->U_1.V_67.VarUse.Name;
        } else {
          ProcName = Idents_NoIdent;
        }
        if (!Sets_IsElement((Sets_tElement)ProcName, &ExternNames) && !Sets_IsElement((Sets_tElement)ProcName, &LocExternNames) && !Sets_IsElement((Sets_tElement)ProcName, &UserNames)) {
          if (Sets_IsElement(ORD('e'), &Tree_Options)) {
            Scanner_ErrorI((STRING)"subroutine identifier not declared", 34L, W_28->Pos, ProcName);
          } else if (Sets_IsElement(ORD('v'), &Tree_Options) && !Sets_IsElement(ORD('s'), &Tree_Options)) {
            Scanner_WarningI((STRING)"subroutine identifier not declared", 34L, W_28->Pos, ProcName);
          }
          Sets_Include(&UserNames, (Sets_tElement)ProcName);
        }
        CheckCallExprs(W_28->Exprs, dFormals);
        CheckCallExprs(W_28->Patterns, dFormals);
      } else if (Tree_IsType(W_28->Object, Tree_Routine)) {
        CheckExpr2(&W_28->Expr);
        if (W_28->Object->U_1.V_1.Kind == Tree_Function && Tree_IsType(Formals, Tree_Formal)) {
          CheckSubtype(Formals->U_1.V_93.Formal.TypeDesc, W_28->Object->U_1.V_34.Function.ReturnForm->U_1.V_93.Formal.TypeDesc, W_28->Pos, (STRING)"Result type of puma function not in formal/child type, specifically:", 68L);
        }
        CheckCallExprs(W_28->Exprs, W_28->Object->U_1.V_32.Routine.InForm);
        CheckCallPatterns(W_28->Patterns, W_28->Object->U_1.V_32.Routine.OutForm);
        CheckInParams(W_28->Exprs, W_28->Object->U_1.V_32.Routine.InForm);
      } else {
        Scanner_Error((STRING)"subroutine identifier required", 30L, W_28->Pos);
      }
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_29 = &(*t)->U_1.V_71.Binary;

      if (W_29->Operator == IdentDot && W_29->Lop->U_1.V_1.Kind == Tree_VarUse && W_29->Rop->U_1.V_1.Kind == Tree_VarUse && Sets_IsElement((Sets_tElement)W_29->Lop->U_1.V_67.VarUse.Name, &LabelNames)) {
        LObject = Semantics_IdentifyVar(Decls, W_29->Lop->U_1.V_67.VarUse.Name);
        if (LObject != NIL && LObject->U_1.V_93.Formal.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
          ActClass = ClassOfNodeTypes(LObject->U_1.V_93.Formal.TypeDesc);
          LAttrFormal = Semantics_IdentifyVar(ActClass->U_1.V_5.Class.Formals, W_29->Rop->U_1.V_67.VarUse.Name);
          if (LAttrFormal != Tree_NoTree) {
            LResult = Tree_mAttrDesc(W_29->Pos, W_29->Lop->U_1.V_67.VarUse.Selector, W_29->Lop->U_1.V_67.VarUse.Name, FALSE, W_29->Rop->U_1.V_67.VarUse.Name, W_29->Rop->U_1.V_67.VarUse.Pos);
            LResult->U_1.V_68.AttrDesc.Object = LObject;
            LResult->U_1.V_68.AttrDesc.Type = ActClass->U_1.V_5.Class.Name;
            *t = LResult;
          } else {
            CheckExprVar(&W_29->Lop, dFormals);
            CheckExprVar(&W_29->Rop, dFormals);
          }
        } else {
          CheckExprVar(&W_29->Lop, dFormals);
          CheckExprVar(&W_29->Rop, dFormals);
        }
      } else {
        CheckExprVar(&W_29->Lop, dFormals);
        CheckExprVar(&W_29->Rop, dFormals);
      }
    }
    break;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinaryCompound *W_30 = &(*t)->U_1.V_73.BinaryCompound;

      CheckExprVar(&W_30->Lop, dFormals);
      CheckExprVar(&W_30->Rop, dFormals);
    }
    break;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
    {
      register Tree_yPreOperator *W_31 = &(*t)->U_1.V_74.PreOperator;

      CheckExprVar(&W_31->Expr, dFormals);
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_32 = &(*t)->U_1.V_76.Index;

      CheckExprVar(&W_32->Expr, dFormals);
      CheckExprList(W_32->Exprs, dFormals);
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_33 = &(*t)->U_1.V_77.Parents;

      CheckExprVar(&W_33->Expr, Formals);
    }
    break;
  case Tree_AttrDesc:;
    {
      register Tree_yAttrDesc *W_34 = &(*t)->U_1.V_68.AttrDesc;

      if (Sets_IsElement((Sets_tElement)W_34->Name, &LabelNames)) {
        W_34->Object = Semantics_IdentifyVar(Decls, W_34->Name);
        if (W_34->Object != NIL && W_34->Object->U_1.V_93.Formal.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
          ActClass = ClassOfNodeTypes(W_34->Object->U_1.V_93.Formal.TypeDesc);
          W_34->Type = ActClass->U_1.V_5.Class.Name;
          LAttrFormal = Semantics_IdentifyVar(ActClass->U_1.V_5.Class.Formals, W_34->Attribute);
          if (LAttrFormal == Tree_NoTree) {
            Scanner_ErrorI((STRING)"No such child/attribute", 23L, W_34->AttributePos, W_34->Attribute);
          } else if (Tree_IsType(Formals, Tree_Formal)) {
            CheckSubtype(Formals->U_1.V_93.Formal.TypeDesc, LAttrFormal->U_1.V_93.Formal.TypeDesc, W_34->AttributePos, (STRING)"Type of node field not in formal/child type, specifically:", 58L);
          }
        } else {
          Scanner_ErrorI((STRING)"tree-type required", 18L, W_34->Pos, W_34->Name);
        }
      } else {
        Scanner_ErrorI((STRING)"Identifier not declared", 23L, W_34->Pos, W_34->Name);
      }
    }
    break;
  default :
    break;
  }
}

static void CheckExpr2
# ifdef __STDC__
(Tree_tTree *t)
# else
(t)
Tree_tTree *t;
# endif
{
  switch ((*t)->U_1.V_1.Kind) {
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_35 = &(*t)->U_1.V_67.VarUse;

      W_35->Object = Semantics_IdentifyVar(Decls, W_35->Name);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_36 = &(*t)->U_1.V_71.Binary;

      CheckExpr2(&W_36->Lop);
      CheckExpr2(&W_36->Rop);
    }
    break;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinaryCompound *W_37 = &(*t)->U_1.V_73.BinaryCompound;

      CheckExpr2(&W_37->Lop);
      CheckExpr2(&W_37->Rop);
    }
    break;
  case Tree_Compose:;
    CheckExpr(t, dFormals);
    break;
  }
}

static void CheckRulePatterns
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Tree_tTree Predecessor)
# else
(t, Formals, Predecessor)
Tree_tTree t, Formals, Predecessor;
# endif
{
  Tree_tTree Pattern;

  if (t->U_1.V_1.Kind == Tree_NoPattern && !Tree_IsType(Formals, Tree_Formal)) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoPattern) {
    if (Sets_IsElement(ORD('g'), &Tree_Options)) {
    } else {
      Scanner_Error((STRING)"too few patterns for rule", 25L, t->U_1.V_44.NoPattern.Pos);
      return;
    }
    return;
  }
  Pattern = t->U_1.V_45.OnePattern.Pattern;
  if (Tree_IsType(Pattern, Tree_DontCare)) {
    return;
  }
  if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
    Scanner_Error((STRING)"too many patterns for rule", 26L, Pattern->U_1.V_50.Pattern.Pos);
    return;
  }
  CheckPattern(&t->U_1.V_45.OnePattern.Pattern, Formals, Formals->U_1.V_93.Formal.Path, C_1_RoutineFormal);
  CheckRulePatterns(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_93.Formal.Next, t);
}

static void CheckSubPatterns
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Tree_tTree FPath)
# else
(t, Formals, FPath)
Tree_tTree t, Formals, FPath;
# endif
{
  Tree_tTree Lt, LFormals, LPattern;

  Lt = t;
  LFormals = Formals;
  for (;;) {
    if (Lt->U_1.V_1.Kind == Tree_NoPattern) {
      if (Tree_IsType(LFormals, Tree_Formal) && !Sets_IsElement(ORD('g'), &Tree_Options)) {
        Scanner_Error((STRING)"too few child patterns", 22L, Lt->U_1.V_44.NoPattern.Pos);
      }
      goto EXIT_5;
    }
    LPattern = Lt->U_1.V_45.OnePattern.Pattern;
    if (LFormals->U_1.V_1.Kind == Tree_NoFormal) {
      if (!Tree_IsType(LPattern, Tree_DontCare)) {
        Scanner_Error((STRING)"too many child patterns", 23L, LPattern->U_1.V_50.Pattern.Pos);
      }
      goto EXIT_5;
    }
    CheckPattern(&Lt->U_1.V_45.OnePattern.Pattern, LFormals, Tree_mField(FPath, LFormals->U_1.V_93.Formal.Name), ChildFormal);
    if (!Tree_IsType(LPattern, Tree_DontCare)) {
      Lt = Lt->U_1.V_45.OnePattern.Next;
    }
    LFormals = LFormals->U_1.V_93.Formal.Next;
  } EXIT_5:;
}

static void CheckCallPatterns
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Tree_tTree Lt, LFormals;

  Lt = t;
  LFormals = Formals;
  for (;;) {
    if (Lt->U_1.V_1.Kind == Tree_NoPattern) {
      if (Tree_IsType(LFormals, Tree_Formal) && !Sets_IsElement(ORD('g'), &Tree_Options)) {
        Scanner_Error((STRING)"too few result patterns", 23L, Lt->U_1.V_44.NoPattern.Pos);
      }
      goto EXIT_6;
    }
    {
      register Tree_yOnePattern *W_38 = &Lt->U_1.V_45.OnePattern;

      if (Tree_IsType(W_38->Pattern, Tree_DontCare)) {
        W_38->Pattern->U_1.V_57.DontCare.Tempos = MakeTempos(LFormals);
        goto EXIT_6;
      } else {
        if (LFormals->U_1.V_1.Kind == Tree_NoFormal) {
          Scanner_Error((STRING)"too many result patterns", 24L, W_38->Pattern->U_1.V_50.Pattern.Pos);
          goto EXIT_6;
        }
      }
      W_38->Pattern->U_1.V_50.Pattern.Tempo = MakeTempoIdent();
      W_38->Pattern->U_1.V_50.Pattern.TypeDesc = LFormals->U_1.V_93.Formal.TypeDesc;
      CheckPattern(&W_38->Pattern, LFormals, Tree_mVar(W_38->Pattern->U_1.V_50.Pattern.Tempo, FALSE, TRUE), CallFormal);
      if (!Tree_IsType(W_38->Pattern, Tree_DontCare)) {
        Lt = W_38->Next;
      }
      LFormals = LFormals->U_1.V_93.Formal.Next;
    }
  } EXIT_6:;
}

static void AddHidingDecl
# ifdef __STDC__
(Tree_tTree FDecl)
# else
(FDecl)
Tree_tTree FDecl;
# endif
{
  if (Sets_IsElement((Sets_tElement)FDecl->U_1.V_93.Formal.Name, &LabelNames)) {
    FDecl->U_1.V_93.Formal.Hides = Semantics_IdentifyVar(Decls, FDecl->U_1.V_93.Formal.Name);
  } else {
    Sets_Include(&LabelNames, (Sets_tElement)FDecl->U_1.V_93.Formal.Name);
  }
  FDecl->U_1.V_93.Formal.Next = Decls;
  Decls = FDecl;
}

static void DeclarePattern
# ifdef __STDC__
(FormalKindTyp FormalKind, Idents_tIdent Name, Tree_tTree TypeDesc, Tree_tTree FPath, Positions_tPosition Pos)
# else
(FormalKind, Name, TypeDesc, FPath, Pos)
FormalKindTyp FormalKind;
Idents_tIdent Name;
Tree_tTree TypeDesc, FPath;
Positions_tPosition Pos;
# endif
{
  switch (FormalKind) {
  case C_1_RoutineFormal:;
    Decls = Tree_mPlainFormal(Decls, (Tree_tTree)Tree_NoTree, Name, Pos, TypeDesc, FPath);
    break;
  case ChildFormal:;
    if (Sets_IsElement(ORD('j'), &Tree_Options)) {
      if (Sets_IsElement((Sets_tElement)Name, &LabelNames) && Sets_IsElement(ORD('J'), &Tree_Options)) {
        Scanner_WarningI((STRING)"Child name hides another declaration", 36L, Pos, Name);
      }
      AddHidingDecl(Tree_mPlainFormal((Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, Name, Pos, TypeDesc, FPath));
    }
    break;
  case CallFormal:;
    break;
  }
}

static void DeclareLabel
# ifdef __STDC__
(Idents_tIdent Selector, Positions_tPosition Pos, BOOLEAN Widen, Tree_tTree Formal, Tree_tTree NarrowTypeDesc, Tree_tTree WidePath, Tree_tTree NarrowPath)
# else
(Selector, Pos, Widen, Formal, NarrowTypeDesc, WidePath, NarrowPath)
Idents_tIdent Selector;
Positions_tPosition Pos;
BOOLEAN Widen;
Tree_tTree Formal;
Tree_tTree NarrowTypeDesc;
Tree_tTree WidePath;
Tree_tTree NarrowPath;
# endif
{
  Tree_tTree LTypeDesc;
  Tree_tTree LPath;

  if (Selector != Idents_NoIdent) {
    if (Sets_IsElement((Sets_tElement)Selector, &LabelNames)) {
      Scanner_Error((STRING)"label previously declared", 25L, Pos);
    } else {
      Sets_Include(&LabelNames, (Sets_tElement)Selector);
    }
    if (Widen && Tree_IsType(Formal, Tree_Formal)) {
      LTypeDesc = Formal->U_1.V_93.Formal.TypeDesc;
      LPath = WidePath;
    } else {
      LTypeDesc = NarrowTypeDesc;
      LPath = NarrowPath;
    }
    if (Formal->U_1.V_1.Kind == Tree_RoutineFormal) {
      {
        register Tree_yRoutineFormal *W_39 = &Formal->U_1.V_95.RoutineFormal;

        Decls = Tree_mRoutineFormal(Decls, (Tree_tTree)Tree_NoTree, Selector, Pos, LTypeDesc, LPath, W_39->TargetClass, W_39->DeclaredTypeIsGuaranteed);
      }
    } else {
      Decls = Tree_mPlainFormal(Decls, (Tree_tTree)Tree_NoTree, Selector, Pos, LTypeDesc, LPath);
    }
  }
}

static void CheckPattern
# ifdef __STDC__
(Tree_tTree *t, Tree_tTree Formals, Tree_tTree FPath, FormalKindTyp FormalKind)
# else
(t, Formals, FPath, FormalKind)
Tree_tTree *t;
Tree_tTree Formals, FPath;
FormalKindTyp FormalKind;
# endif
{
  Tree_tTree LParam, LTypeDesc;
  Tree_tTree LPath;
  Tree_tTree LFormalTypeDesc;
  BOOLEAN LWasDeclared;

  switch ((*t)->U_1.V_1.Kind) {
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_40 = &(*t)->U_1.V_51.Decompose;

      W_40->IsProperlyNarrowed = FALSE;
      if (Tree_IsType(Formals, Tree_Formal)) {
        CheckSubtype(Formals->U_1.V_93.Formal.TypeDesc, W_40->Object->U_1.V_5.Class.TypeDesc, W_40->Pos, (STRING)"Decompose node not in formal/child type, specifically:", 54L);
        if (Formals->U_1.V_93.Formal.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes && W_40->Object->U_1.V_5.Class.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
          if (Tree_IsType(Formals, Tree_RoutineFormal) && Formals->U_1.V_95.RoutineFormal.TargetClass != Tree_NoTree) {
            LFormalTypeDesc = Formals->U_1.V_95.RoutineFormal.TargetClass->U_1.V_5.Class.TypeDesc;
          } else {
            LFormalTypeDesc = Formals->U_1.V_93.Formal.TypeDesc;
          }
          if (Sets_IsNotEqual(LFormalTypeDesc->U_1.V_98.NodeTypes.Types, W_40->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.Types)) {
            W_40->IsProperlyNarrowed = TRUE;
          }
        }
        LPath = Tree_mConsType(FPath, W_40->Object->U_1.V_5.Class.Name, W_40->IsProperlyNarrowed);
        DeclarePattern(FormalKind, Formals->U_1.V_93.Formal.Name, W_40->Object->U_1.V_5.Class.TypeDesc, LPath, W_40->Pos);
      } else {
        LPath = Tree_mConsType(FPath, W_40->Object->U_1.V_5.Class.Name, FALSE);
      }
      if (W_40->Object == Tree_NoTree) {
        CheckExpr(&W_40->Expr, dFormals);
      } else {
        CheckExpr2(&W_40->Expr);
      }
      DeclareLabel(W_40->Selector, W_40->Pos, W_40->Widen, Formals, W_40->Object->U_1.V_5.Class.TypeDesc, FPath, LPath);
      (*t)->U_1.V_51.Decompose.Path = FPath;
      CheckSubPatterns(W_40->Patterns, W_40->Object->U_1.V_5.Class.Formals, LPath);
    }
    break;
  case Tree_NilTest:;
    {
      register Tree_yNilTest *W_41 = &(*t)->U_1.V_53.NilTest;

      W_41->Path = FPath;
      if (Tree_IsType(Formals, Tree_Formal)) {
        LTypeDesc = Formals->U_1.V_93.Formal.TypeDesc;
        if (LTypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
          W_41->IsProperlyNarrowed = Sets_IsNotEqual(LTypeDesc->U_1.V_98.NodeTypes.Types, LTypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.EmptyType->U_1.V_98.NodeTypes.Types);
          LPath = Tree_mConsType(FPath, IdentEmptyType, W_41->IsProperlyNarrowed);
          LTypeDesc = LTypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.EmptyType;
        } else {
          LPath = Tree_mConsType(FPath, LTypeDesc->U_1.V_99.UserType.Type, FALSE);
          *t = Tree_mValue(W_41->Pos, W_41->Selector, Tree_mTargetExpr(W_41->Pos, Idents_NoIdent, Tree_mAny(StringRefNil, nNoDesignator)));
          (*t)->U_1.V_60.Value.Path = FPath;
        }
        DeclarePattern(FormalKind, Formals->U_1.V_93.Formal.Name, LTypeDesc, LPath, W_41->Pos);
      } else {
        LPath = Tree_mVar(Idents_NoIdent, FALSE, FALSE);
        LTypeDesc = Tree_NoTree;
      }
      DeclareLabel(W_41->Selector, W_41->Pos, W_41->Widen, Formals, LTypeDesc, FPath, LPath);
    }
    break;
  case Tree_VarDef:;
    {
      register Tree_yVarDef *W_42 = &(*t)->U_1.V_52.VarDef;

      LWasDeclared = Sets_IsElement((Sets_tElement)W_42->Selector, &LabelNames);
      if (W_42->HasDelimiter && LWasDeclared) {
        Scanner_ErrorI((STRING)"Label previously declared", 25L, W_42->Pos, W_42->Selector);
      } else if (!W_42->HasDelimiter && !LWasDeclared && Sets_IsElement(ORD('u'), &Tree_Options)) {
        Scanner_ErrorI((STRING)"Colon required on label", 23L, W_42->Pos, W_42->Selector);
      }
      if (W_42->HasDelimiter || !LWasDeclared) {
        if (Formals->U_1.V_1.Kind == Tree_RoutineFormal) {
          AddHidingDecl(Tree_mRoutineFormal((Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, W_42->Selector, W_42->Pos, Formals->U_1.V_95.RoutineFormal.TypeDesc, FPath, Formals->U_1.V_95.RoutineFormal.TargetClass, Formals->U_1.V_95.RoutineFormal.DeclaredTypeIsGuaranteed));
        } else {
          AddHidingDecl(Tree_mPlainFormal((Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, W_42->Selector, W_42->Pos, Formals->U_1.V_93.Formal.TypeDesc, FPath));
        }
        W_42->Object = Tree_NoTree;
      }
      if (!W_42->HasDelimiter && LWasDeclared) {
        if (!Sets_IsElement(ORD('k'), &Tree_Options)) {
          Scanner_Error((STRING)"nonlinear label reference requires -k option", 44L, W_42->Pos);
        }
        W_42->Object = Semantics_IdentifyVar(Decls, W_42->Selector);
        if (Tree_IsType(Formals, Tree_Formal) && W_42->Object != NIL) {
          CheckType(Formals->U_1.V_93.Formal.TypeDesc, W_42->Object->U_1.V_93.Formal.TypeDesc, W_42->Pos);
        }
      }
      (*t)->U_1.V_52.VarDef.Path = FPath;
    }
    break;
  case Tree_DontCare1Explicit:;
    if (Tree_IsType(Formals, Tree_Formal)) {
      DeclarePattern(FormalKind, Formals->U_1.V_93.Formal.Name, Formals->U_1.V_93.Formal.TypeDesc, Tree_mConsType(FPath, TypeIdentOfFormal(Formals), FALSE), (*t)->U_1.V_57.DontCare.Pos);
      DeclareLabel((*t)->U_1.V_55.DontCare1Explicit.Selector, (*t)->U_1.V_55.DontCare1Explicit.Pos, TRUE, Formals, (Tree_tTree)Tree_NoTree, FPath, FPath);
      (*t)->U_1.V_57.DontCare.Path = FPath;
    }
    break;
  case Tree_DontCare1Internal:;
    if (Tree_IsType(Formals, Tree_Formal)) {
      (*t)->U_1.V_57.DontCare.Path = FPath;
    }
    break;
  case Tree_DontCareExplicit:;
    if (Tree_IsType(Formals, Tree_Formal)) {
      DeclarePattern(FormalKind, Formals->U_1.V_93.Formal.Name, Formals->U_1.V_93.Formal.TypeDesc, Tree_mConsType(FPath, TypeIdentOfFormal(Formals), FALSE), (*t)->U_1.V_57.DontCare.Pos);
    }
    break;
  case Tree_DontCareInternal:;
    break;
  case Tree_Value:;
    CheckExprVar(&(*t)->U_1.V_60.Value.Expr, Formals);
    DeclareLabel((*t)->U_1.V_60.Value.Selector, (*t)->U_1.V_60.Value.Pos, TRUE, Formals, (Tree_tTree)Tree_NoTree, FPath, FPath);
    (*t)->U_1.V_60.Value.Path = FPath;
    break;
  default :
    (*t)->U_1.V_50.Pattern.Path = FPath;
    break;
  }
}

static Idents_tIdent MakeTempoIdent
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString String1, String2;

  INC(TempoCount);
  Strings_ArrayToString((STRING)"yyV", 3L, &String1);
  Strings_IntToString(TempoCount, &String2);
  Strings_Concatenate(&String1, &String2);
  return Idents_MakeIdent(&String1);
}

static Tree_tTree MakeTempos
# ifdef __STDC__
(Tree_tTree Formals)
# else
(Formals)
Tree_tTree Formals;
# endif
{
  if (Tree_IsType(Formals, Tree_Formal)) {
    {
      register Tree_yFormal *W_43 = &Formals->U_1.V_93.Formal;

      return Tree_mPlainFormal(MakeTempos(W_43->Next), (Tree_tTree)Tree_NoTree, MakeTempoIdent(), W_43->DeclPos, W_43->TypeDesc, W_43->Path);
    }
  } else {
    return nNoFormal;
  }
}

static void InitPredefinedExtern
# ifdef __STDC__
()
# else
()
# endif
{
  if (Sets_IsElement(ORD('c'), &Tree_Options) || Sets_IsElement(ORD('A'), &Tree_Options)) {
  } else {
    Sets_Include(&ExternNames, (Sets_tElement)IdentFalse);
    Sets_Include(&ExternNames, (Sets_tElement)IdentTrue);
  }
}

static void yyAbort
# ifdef __STDC__
(CHAR yyFunction[], LONGCARD O_5)
# else
(yyFunction, O_5)
CHAR yyFunction[];
LONGCARD O_5;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_5 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yyFunction, O_5, CHAR)
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Semantics, routine ", 33L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_5);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Semantics_Exit)();
  FREE_OPEN_ARRAYS
}

static BOOLEAN yyIsEqual
# ifdef __STDC__
(BYTE yya[], LONGCARD O_7, BYTE yyb[], LONGCARD O_6)
# else
(yya, O_7, yyb, O_6)
BYTE yya[];
LONGCARD O_7;
BYTE yyb[];
LONGCARD O_6;
# endif
{
  INTEGER yyi;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_6 * sizeof(WORD) + O_7 * sizeof(WORD), 2)
  COPY_OPEN_ARRAY(yyb, O_6, WORD)
  COPY_OPEN_ARRAY(yya, O_7, WORD)
  {
    LONGINT B_5 = 0, B_6 = (INTEGER)(O_7 - 1);

    if (B_5 <= B_6)
      for (yyi = B_5;; yyi += 1) {
        if (yya[yyi] != yyb[yyi]) {
          FREE_OPEN_ARRAYS
          return FALSE;
        }
        if (yyi >= B_6) break;
      }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

static void CollectRoutineNames
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
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_44 = &t->U_1.V_33.Procedure;

      if (Sets_IsElement((Sets_tElement)W_44->Name, &RoutineNames)) {
        Scanner_Error((STRING)"routine identifier previously declared", 38L, W_44->Pos);
      } else {
        Sets_Include(&RoutineNames, (Sets_tElement)W_44->Name);
      }
      CollectRoutineNames(W_44->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_45 = &t->U_1.V_35.Predicate;

      if (Sets_IsElement((Sets_tElement)W_45->Name, &RoutineNames)) {
        Scanner_Error((STRING)"routine identifier previously declared", 38L, W_45->Pos);
      } else {
        Sets_Include(&RoutineNames, (Sets_tElement)W_45->Name);
      }
      CollectRoutineNames(W_45->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_46 = &t->U_1.V_34.Function;

      if (Sets_IsElement((Sets_tElement)W_46->Name, &RoutineNames)) {
        Scanner_Error((STRING)"routine identifier previously declared", 38L, W_46->Pos);
      } else {
        Sets_Include(&RoutineNames, (Sets_tElement)W_46->Name);
      }
      CollectRoutineNames(W_46->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void Semantics_Semantics
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
  case Tree_Spec:;
    {
      register Tree_ySpec *W_47 = &t->U_1.V_26.Spec;

      Semantics_TypeCount = Idents_MaxIdent();
      Sets_MakeSet(&RoutineNames, (Sets_tElement)Semantics_TypeCount);
      Sets_MakeSet(&LabelNames, (Sets_tElement)Semantics_TypeCount);
      Sets_MakeSet(&ParamNames, (Sets_tElement)Semantics_TypeCount);
      Sets_MakeSet(&Semantics_TypeNames, (Sets_tElement)Semantics_TypeCount);
      Sets_MakeSet(&ExternNames, (Sets_tElement)Semantics_TypeCount);
      InitPredefinedExtern();
      Sets_MakeSet(&LocExternNames, (Sets_tElement)Semantics_TypeCount);
      Sets_MakeSet(&Semantics_UserTypes, (Sets_tElement)Semantics_TypeCount);
      Sets_MakeSet(&UserNames, (Sets_tElement)Semantics_TypeCount);
      ClassFormals(W_47->TreeNames);
      Semantics_Semantics(W_47->Public);
      CollectExtern(W_47->Extern, &ExternNames);
      ProcFormals(W_47->Routines);
      CollectRoutineNames(W_47->Routines);
      Semantics_Semantics(W_47->Routines);
      if (Sets_IsElement(ORD('o'), &Tree_Options) && !Sets_IsEmpty(UserNames)) {
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Undefined External Names", 24L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"------------------------", 24L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        {
          LONGCARD B_7 = 1, B_8 = Semantics_TypeCount;

          if (B_7 <= B_8)
            for (i = B_7;; i += 1) {
              if (Sets_IsElement(i, &UserNames)) {
                Idents_WriteIdent((System_tFile)IO_StdOutput, (SHORTCARD)i);
                IO_WriteNl((System_tFile)IO_StdOutput);
              }
              if (i >= B_8) break;
            }
        }
      }
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_48 = &t->U_1.V_25.Name;

      W_48->Object = IdentifyProc(W_48->Name);
      if (W_48->Object == Tree_NoTree) {
        Scanner_ErrorI((STRING)"subroutine identifier not declared", 34L, W_48->Pos, W_48->Name);
      } else {
        W_48->Object->U_1.V_32.Routine.IsExtern = TRUE;
      }
      Semantics_Semantics(W_48->Next);
      return;
    }
    break;
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_49 = &t->U_1.V_33.Procedure;

      Sets_AssignEmpty(&LocExternNames);
      CollectExtern(W_49->Extern, &LocExternNames);
      Sets_AssignEmpty(&ParamNames);
      Check(W_49->InParams);
      Check(W_49->OutParams);
      InFormals = W_49->InForm;
      OutFormals = W_49->OutForm;
      Parameters = W_49->ParamDecls;
      IsFunction = FALSE;
      RuleCount = 0;
      Check(W_49->Rules);
      Semantics_Semantics(W_49->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_50 = &t->U_1.V_35.Predicate;

      Sets_AssignEmpty(&LocExternNames);
      CollectExtern(W_50->Extern, &LocExternNames);
      Sets_AssignEmpty(&ParamNames);
      Check(W_50->InParams);
      Check(W_50->OutParams);
      InFormals = W_50->InForm;
      OutFormals = W_50->OutForm;
      Parameters = W_50->ParamDecls;
      IsFunction = FALSE;
      RuleCount = 0;
      Check(W_50->Rules);
      Semantics_Semantics(W_50->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_51 = &t->U_1.V_34.Function;

      Sets_AssignEmpty(&LocExternNames);
      CollectExtern(W_51->Extern, &LocExternNames);
      Sets_AssignEmpty(&ParamNames);
      Check(W_51->InParams);
      Check(W_51->OutParams);
      Check(W_51->ReturnParams);
      InFormals = W_51->InForm;
      OutFormals = W_51->OutForm;
      ReturnFormal = W_51->ReturnForm;
      Parameters = W_51->ParamDecls;
      IsFunction = TRUE;
      RuleCount = 0;
      Check(W_51->Rules);
      Semantics_Semantics(W_51->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void CollectExtern
# ifdef __STDC__
(Tree_tTree t, Sets_tSet *Names)
# else
(t, Names)
Tree_tTree t;
Sets_tSet *Names;
# endif
{
  struct S_10 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Name) {
    {
      register Tree_yName *W_52 = &t->U_1.V_25.Name;

      Sets_Include(Names, (Sets_tElement)W_52->Name);
      CollectExtern(W_52->Next, Names);
      return;
    }
  }
}

static void ProcFormals
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
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_53 = &t->U_1.V_33.Procedure;

      Args = nNoFormal;
      Decls = nNoFormal;
      Sets_AssignEmpty(&ParamNames);
      IsOutput = FALSE;
      ProcFormals(W_53->InParams);
      W_53->InForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_53->OutParams);
      W_53->OutForm = Tree_ReverseTree(Args);
      W_53->ParamDecls = Decls;
      ProcFormals(W_53->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_54 = &t->U_1.V_35.Predicate;

      Args = nNoFormal;
      Decls = nNoFormal;
      Sets_AssignEmpty(&ParamNames);
      IsOutput = FALSE;
      ProcFormals(W_54->InParams);
      W_54->InForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_54->OutParams);
      W_54->OutForm = Tree_ReverseTree(Args);
      W_54->ParamDecls = Decls;
      ProcFormals(W_54->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_55 = &t->U_1.V_34.Function;

      Args = nNoFormal;
      Decls = nNoFormal;
      Sets_AssignEmpty(&ParamNames);
      IsOutput = FALSE;
      ProcFormals(W_55->InParams);
      W_55->InForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_55->OutParams);
      W_55->OutForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_55->ReturnParams);
      W_55->ReturnForm = Tree_ReverseTree(Args);
      W_55->ParamDecls = Decls;
      ProcFormals(W_55->Next);
      return;
    }
    break;
  case Tree_Param:;
    {
      register Tree_yParam *W_56 = &t->U_1.V_38.Param;

      if (Sets_IsElement((Sets_tElement)W_56->Name, &ParamNames)) {
        Scanner_Error((STRING)"parameter identifier previously declared", 40L, W_56->Pos);
      } else {
        Sets_Include(&ParamNames, (Sets_tElement)W_56->Name);
      }
      ParamName = W_56->Name;
      ParamPos = W_56->Pos;
      Mode = W_56->IsRef;
      ProcFormals(W_56->Type);
      ProcFormals(W_56->Next);
      return;
    }
    break;
  case Tree_Type:;
    {
      register Tree_yType *W_57 = &t->U_1.V_39.Type;

      GlobalLUBClass = Tree_NoTree;
      if (W_57->Name != Idents_NoIdent && W_57->Names->U_1.V_1.Kind != Tree_NoName) {
        TreeName = IdentifyTree(W_57->Name);
        if (TreeName != Tree_NoTree) {
          Sets_MakeSet(&ActTypes, (Sets_tElement)TreeName->U_1.V_29.TreeName.ClassCount);
        } else {
          Scanner_Error((STRING)"tree type not declared", 22L, W_57->Pos);
        }
      } else if (W_57->Name != Idents_NoIdent && W_57->Names->U_1.V_1.Kind == Tree_NoName) {
        TreeName = IdentifyTree(W_57->Name);
        if (TreeName != Tree_NoTree) {
          Sets_MakeSet(&ActTypes, (Sets_tElement)TreeName->U_1.V_29.TreeName.ClassCount);
          MakeTypes((LONGINT)TreeName->U_1.V_29.TreeName.Classes->U_1.V_5.Class.Index, TreeName->U_1.V_29.TreeName.Classes, &ActTypes);
          GlobalLUBClass = TreeName->U_1.V_29.TreeName.UniversalClass;
        } else {
          ActClass = IdentifyClass2(W_57->Name, &TreeName);
          if (ActClass != Tree_NoTree) {
            Sets_MakeSet(&ActTypes, (Sets_tElement)TreeName->U_1.V_29.TreeName.ClassCount);
            MakeTypes((LONGINT)ActClass->U_1.V_5.Class.Index, ActClass->U_1.V_5.Class.Extensions, &ActTypes);
            GlobalLUBClass = ActClass;
          }
        }
      } else if (W_57->Name == Idents_NoIdent && W_57->Names->U_1.V_1.Kind != Tree_NoName) {
        ActClass = IdentifyClass2(W_57->Names->U_1.V_25.Name.Name, &TreeName);
        if (ActClass != Tree_NoTree) {
          Sets_MakeSet(&ActTypes, (Sets_tElement)TreeName->U_1.V_29.TreeName.ClassCount);
        } else {
          Scanner_Error((STRING)"node type not declared", 22L, W_57->Names->U_1.V_25.Name.Pos);
        }
      } else {
        TreeName = Tree_NoTree;
      }
      if (TreeName != Tree_NoTree) {
        ActTree = TreeName->U_1.V_29.TreeName.Classes;
        ProcFormals(W_57->Names);
        Node = Tree_mNodeTypes(TreeName, ActTypes);
      } else {
        if (W_57->Name == Idents_NoIdent) {
          Scanner_Error((STRING)"incorrect type", 14L, W_57->Pos);
        } else {
          Sets_Include(&Semantics_TypeNames, (Sets_tElement)W_57->Name);
        }
        Node = Tree_mUserType(W_57->Name);
      }
      Var = Tree_mVar(ParamName, (BOOLEAN)(IsOutput || Mode), TRUE);
      Args = Tree_mRoutineFormal(Args, (Tree_tTree)Tree_NoTree, ParamName, ParamPos, Node, Var, GlobalLUBClass, FALSE);
      Decls = Tree_mRoutineFormal(Decls, (Tree_tTree)Tree_NoTree, ParamName, ParamPos, Node, Var, GlobalLUBClass, FALSE);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_58 = &t->U_1.V_25.Name;

      ActClass = IdentifyClass(ActTree, W_58->Name);
      if (ActClass != Tree_NoTree) {
        Sets_Include(&ActTypes, (Sets_tElement)ActClass->U_1.V_5.Class.Index);
        Tree_ForallClasses(ActClass->U_1.V_5.Class.Extensions, (Tree_ProcOfT)ProcFormals);
        GlobalLUBClass = ClassLUB(GlobalLUBClass, ActClass);
      } else {
        Scanner_Error((STRING)"Node not member of tree type", 28L, W_58->Pos);
      }
      ProcFormals(W_58->Next);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_59 = &t->U_1.V_5.Class;

      Sets_Include(&ActTypes, (Sets_tElement)W_59->Index);
      return;
    }
    break;
  default :
    break;
  }
}

static void CollectUniversalTypeDesc
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
      register Tree_yClass *W_60 = &t->U_1.V_5.Class;

      Sets_Union(&ActTypes, W_60->TypeDesc->U_1.V_98.NodeTypes.Types);
      CollectUniversalTypeDesc(W_60->Next);
      return;
    }
  }
}

static void ClassFormals
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Strings_tString String1, String2;
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_TreeName:;
    {
      register Tree_yTreeName *W_61 = &t->U_1.V_29.TreeName;

      ActTree = t;
      W_61->ClassCount = 0;
      Tree_ForallClasses(W_61->Classes, (Tree_ProcOfT)CountClasses);
      W_61->EmptyType = Tree_mNodeTypes(t, ActTypes);
      Sets_MakeSet(&W_61->EmptyType->U_1.V_98.NodeTypes.Types, (Sets_tElement)t->U_1.V_29.TreeName.ClassCount);
      Sets_AssignEmpty(&W_61->EmptyType->U_1.V_98.NodeTypes.Types);
      Strings_ArrayToString((STRING)"t", 1L, &String1);
      Idents_GetString(W_61->Name, &String2);
      Strings_Concatenate(&String1, &String2);
      Tree_ForallClasses(W_61->Classes, (Tree_ProcOfT)ClassTypes);
      Tree_ForallClasses(W_61->Classes, (Tree_ProcOfT)ClassFormals);
      W_61->UniversalClass = Tree_mClass(Idents_MakeIdent(&String1), SET_ELEM(Tree_Nonterminal), (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree);
      W_61->UniversalClass->U_1.V_5.Class.BaseClass = Tree_NoTree;
      W_61->UniversalClass->U_1.V_5.Class.Formals = Tree_NoTree;
      W_61->UniversalClass->U_1.V_5.Class.Index = 0;
      Sets_MakeSet(&ActTypes, (Sets_tElement)t->U_1.V_29.TreeName.ClassCount);
      Sets_AssignEmpty(&ActTypes);
      CollectUniversalTypeDesc(W_61->Classes);
      W_61->UniversalClass->U_1.V_5.Class.TypeDesc = Tree_mNodeTypes(t, ActTypes);
      ComputeDepthsClasses(W_61->Classes, 1L);
      ClassFormals(W_61->Next);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_62 = &t->U_1.V_5.Class;

      Args = nNoFormal;
      Tree_ForallAttributes(t, (Tree_ProcOfT)ClassFormals);
      W_62->Formals = Tree_ReverseTree(Args);
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_63 = &t->U_1.V_9.Child;

      ActClass = IdentifyClass(ActTree->U_1.V_29.TreeName.Classes, W_63->Type);
      Args = Tree_mPlainFormal(Args, (Tree_tTree)Tree_NoTree, W_63->Name, Positions_NoPosition, ActClass->U_1.V_5.Class.TypeDesc, (Tree_tTree)Tree_NoTree);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_64 = &t->U_1.V_10.Attribute;

      if (((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_64->Properties) == 0X0L) {
        ActClass = IdentifyClass(ActTree->U_1.V_29.TreeName.Classes, W_64->Type);
        if (ActClass == Tree_NoTree) {
          Args = Tree_mPlainFormal(Args, (Tree_tTree)Tree_NoTree, W_64->Name, Positions_NoPosition, Tree_mUserType(W_64->Type), (Tree_tTree)Tree_NoTree);
          Sets_Include(&Semantics_TypeNames, (Sets_tElement)W_64->Type);
        } else {
          Args = Tree_mPlainFormal(Args, (Tree_tTree)Tree_NoTree, W_64->Name, Positions_NoPosition, ActClass->U_1.V_5.Class.TypeDesc, (Tree_tTree)Tree_NoTree);
        }
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
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_65 = &t->U_1.V_5.Class;

      INC(ActTree->U_1.V_29.TreeName.ClassCount);
      W_65->Index = ActTree->U_1.V_29.TreeName.ClassCount;
      return;
    }
  }
}

static void ClassTypes
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_66 = &t->U_1.V_5.Class;

      W_66->TypeDesc = Tree_mNodeTypes(ActTree, ActTypes);
      Sets_MakeSet(&W_66->TypeDesc->U_1.V_98.NodeTypes.Types, (Sets_tElement)ActTree->U_1.V_29.TreeName.ClassCount);
      MakeTypes((LONGINT)W_66->Index, W_66->Extensions, &W_66->TypeDesc->U_1.V_98.NodeTypes.Types);
      return;
    }
  }
}

static void Check
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Reject:;
    if (Tree_IsType(t->U_1.V_86.Reject.Next, Tree_Statement)) {
      for (;;) {
        {
          register Tree_yReject *W_67 = &t->U_1.V_86.Reject;

          {
            register Tree_yStatement *W_68 = &W_67->Next->U_1.V_82.Statement;

            Scanner_Warning((STRING)"statement not reachable", 23L, t->U_1.V_86.Reject.Next->U_1.V_82.Statement.Pos);
            goto EXIT_7;
          }
        }
      } EXIT_7:;
    }
    break;
  case Tree_Fail:;
    if (Tree_IsType(t->U_1.V_87.Fail.Next, Tree_Statement)) {
      for (;;) {
        {
          register Tree_yFail *W_69 = &t->U_1.V_87.Fail;

          {
            register Tree_yStatement *W_70 = &W_69->Next->U_1.V_82.Statement;

            Scanner_Warning((STRING)"statement not reachable", 23L, t->U_1.V_87.Fail.Next->U_1.V_82.Statement.Pos);
            goto EXIT_8;
          }
        }
      } EXIT_8:;
    }
    {
      register Tree_yFail *W_71 = &t->U_1.V_87.Fail;

      if (IsFunction) {
        Scanner_Error((STRING)"FAIL not allowed in function", 28L, W_71->Pos);
      }
      Check(W_71->Next);
      return;
    }
    break;
  default :
    break;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Param:;
    {
      register Tree_yParam *W_72 = &t->U_1.V_38.Param;

      Sets_Include(&ParamNames, (Sets_tElement)W_72->Name);
      Check(W_72->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register struct S_18 *W_73 = &yyTempo.U_1.V_1.yyR4;

      {
        register Tree_yRule *W_74 = &t->U_1.V_42.Rule;

        W_73->LPatterns = TransformKeyword(W_74->Patterns, InFormals);
        TransformPattern(W_73->LPatterns, &W_73->LPatterns, &W_73->LPatternCount);
        W_74->Exprs = TransformKeyword(W_74->Exprs, OutFormals);
        W_74->Exprs = TransformExpr(W_74->Exprs);
        W_74->Expr = TransformExpr(W_74->Expr);
        W_74->Statements = TransformStmt(W_74->Statements);
        for (;;) {
          {
            register Tree_yRule *W_75 = &t->U_1.V_42.Rule;

            if (W_73->LPatternCount == 1) {
              t->U_1.V_42.Rule.Patterns = W_73->LPatterns;
              W_73->LIsLast = TRUE;
            } else {
              NextPatterns(W_73->LPatterns, &W_73->LSinglePatterns, &W_73->LIsLast);
              if (!W_73->LIsLast) {
                W_73->LNewRule = Tree_mRule(t->U_1.V_42.Rule.Line, (Tree_tTree)Tree_NoTree, Tree_CopyTree(t->U_1.V_42.Rule.Exprs), Tree_CopyTree(t->U_1.V_42.Rule.Expr), Tree_CopyTree(t->U_1.V_42.Rule.Statements), t->U_1.V_42.Rule.Next);
                t->U_1.V_42.Rule.Next = W_73->LNewRule;
              }
              t->U_1.V_42.Rule.Patterns = W_73->LSinglePatterns;
            }
            INC(RuleCount);
            t->U_1.V_42.Rule.Index = RuleCount;
            TempoCount = 0;
            HasLocals = FALSE;
            Decls = Parameters;
            Sets_Assign(&LabelNames, ParamNames);
            CheckRulePatterns(t->U_1.V_42.Rule.Patterns, InFormals, (Tree_tTree)NIL);
            Check(t->U_1.V_42.Rule.Patterns);
            Check(t->U_1.V_42.Rule.Statements);
            CheckExprList(t->U_1.V_42.Rule.Exprs, OutFormals);
            Check(t->U_1.V_42.Rule.Exprs);
            if (IsFunction) {
              if (t->U_1.V_42.Rule.Expr->U_1.V_1.Kind == Tree_NoExpr) {
                if (!HasReject(t->U_1.V_42.Rule.Statements)) {
                  Scanner_Error((STRING)"function requires RETURN expression", 35L, t->U_1.V_42.Rule.Expr->U_1.V_65.Expr.Pos);
                }
              } else {
                CheckExprVar(&t->U_1.V_42.Rule.Expr, ReturnFormal);
                Success = FALSE;
                Check(t->U_1.V_42.Rule.Expr);
                t->U_1.V_42.Rule.HasPatterns = Success;
                if (t->U_1.V_42.Rule.HasPatterns && t->U_1.V_42.Rule.Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
                  t->U_1.V_42.Rule.Tempo = MakeTempoIdent();
                }
              }
            }
            if (!IsFunction && t->U_1.V_42.Rule.Expr->U_1.V_1.Kind != Tree_NoExpr) {
              Scanner_Error((STRING)"RETURN in non-function", 22L, t->U_1.V_42.Rule.Expr->U_1.V_65.Expr.Pos);
            }
            t->U_1.V_42.Rule.VarDecls = Decls;
            if (Sets_IsElement(ORD('c'), &Tree_Options)) {
              t->U_1.V_42.Rule.HasTempos = TempoCount > 0 || HasLocals;
            } else {
              t->U_1.V_42.Rule.HasTempos = TempoCount > 0 || HasLocals || t->U_1.V_42.Rule.HasPatterns;
            }
            CheckTargetCode(t->U_1.V_42.Rule.Patterns);
            CheckTargetCode(t->U_1.V_42.Rule.Exprs);
            if (IsFunction) {
              CheckTargetCode(t->U_1.V_42.Rule.Expr);
            }
            CheckTargetCode(t->U_1.V_42.Rule.Statements);
            if (W_73->LIsLast) {
              goto EXIT_9;
            } else {
              t = t->U_1.V_42.Rule.Next;
            }
          }
        } EXIT_9:;
        Check(t->U_1.V_42.Rule.Next);
        return;
      }
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_76 = &t->U_1.V_83.ProcCall;

      CheckExprVar(&W_76->Call, dFormals);
      Check(W_76->Call);
      Check(W_76->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_77 = &t->U_1.V_84.Condition;

      CheckExprVar(&W_77->Expr, dFormals);
      Check(W_77->Expr);
      Check(W_77->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_78 = &t->U_1.V_85.Assignment;

      if (W_78->Adr->U_1.V_1.Kind == Tree_VarUse) {
        W_78->Object = Semantics_IdentifyVar(Decls, W_78->Adr->U_1.V_67.VarUse.Name);
      } else {
        W_78->Object = Tree_NoTree;
      }
      CheckExprVar(&W_78->Adr, dFormals);
      if (W_78->Object != Tree_NoTree) {
        CheckExprVar(&W_78->Expr, W_78->Object);
      } else {
        CheckExprVar(&W_78->Expr, dFormals);
      }
      Check(W_78->Adr);
      Check(W_78->Expr);
      Check(W_78->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_79 = &t->U_1.V_88.TargetStmt;

      CheckTargetCode(W_79->Parameters);
      Sets_MakeSet(&W_79->UsedNames, (Sets_tElement)Idents_MaxIdent());
      ActNames = W_79->UsedNames;
      Check(W_79->Stmt);
      W_79->UsedNames = ActNames;
      Check(W_79->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_80 = &t->U_1.V_82.Statement;

      Check(W_80->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_81 = &t->U_1.V_45.OnePattern;

      Check(W_81->Pattern);
      Check(W_81->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_82 = &t->U_1.V_63.OneExpr;

      Check(W_82->Expr);
      Check(W_82->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_83 = &t->U_1.V_51.Decompose;

      Check(W_83->Expr);
      Success = TRUE;
      Check(W_83->Patterns);
      return;
    }
    break;
  case Tree_VarDef:;
    {
      register Tree_yVarDef *W_84 = &t->U_1.V_52.VarDef;

      if (W_84->Object != Tree_NoTree) {
        Success = TRUE;
      }
      return;
    }
    break;
  case Tree_NilTest:;
    {
      register Tree_yNilTest *W_85 = &t->U_1.V_53.NilTest;

      Success = TRUE;
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_86 = &t->U_1.V_60.Value;

      Success = TRUE;
      Check(W_86->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_87 = &t->U_1.V_66.Compose;

      Check(W_87->Expr);
      Check(W_87->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_88 = &t->U_1.V_70.Call;

      Check(W_88->Expr);
      Check(W_88->Exprs);
      Check(W_88->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
  case Tree_yy1:;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinary *W_89 = &t->U_1.V_71.Binary;

      Check(W_89->Lop);
      Check(W_89->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_90 = &t->U_1.V_74.PreOperator;

      Check(W_90->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_91 = &t->U_1.V_75.PostOperator;

      Check(W_91->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_92 = &t->U_1.V_77.Parents;

      Check(W_92->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_93 = &t->U_1.V_76.Index;

      Check(W_93->Expr);
      Check(W_93->Exprs);
      return;
    }
    break;
  case Tree_TargetExpr:;
    {
      register Tree_yTargetExpr *W_94 = &t->U_1.V_78.TargetExpr;

      Sets_MakeSet(&W_94->UsedNames, (Sets_tElement)Idents_MaxIdent());
      ActNames = W_94->UsedNames;
      Check(W_94->Expr);
      W_94->UsedNames = ActNames;
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_95 = &t->U_1.V_16.Ident;

      W_95->Object = Semantics_IdentifyVar(Decls, W_95->Attribute);
      if (W_95->Object == Tree_NoTree) {
        Sets_Include(&ActNames, (Sets_tElement)W_95->Attribute);
      }
      Check(W_95->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_96 = &t->U_1.V_18.Any;

      Check(W_96->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_97 = &t->U_1.V_19.Anys;

      Check(W_97->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register struct S_17 *W_98 = &yyTempo.U_1.V_2.yyR28;

      {
        register Tree_yDesignator *W_99 = &t->U_1.V_15.Designator;

        if (Sets_IsElement((Sets_tElement)W_99->Selector, &LabelNames)) {
          W_99->Object = Semantics_IdentifyVar(Decls, W_99->Selector);
          if (W_99->Object != NIL && W_99->Object->U_1.V_93.Formal.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
            ActClass = ClassOfNodeTypes(W_99->Object->U_1.V_93.Formal.TypeDesc);
            W_99->Type = ActClass->U_1.V_5.Class.Name;
            W_98->LAttrFormal = Semantics_IdentifyVar(ActClass->U_1.V_5.Class.Formals, W_99->Attribute);
            if (W_98->LAttrFormal == Tree_NoTree) {
              Scanner_ErrorI((STRING)"D No such child/attribute", 25L, W_99->AttributePos, W_99->Attribute);
            }
          } else {
            Scanner_ErrorI((STRING)"D tree-type required", 20L, W_99->Pos, W_99->Selector);
          }
        } else {
          Scanner_ErrorI((STRING)" D identifier is not declared", 29L, W_99->Pos, W_99->Selector);
        }
        Check(W_99->Next);
        return;
      }
    }
    break;
  default :
    break;
  }
}

static void CheckTargetCode
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Param:;
    {
      register Tree_yParam *W_100 = &t->U_1.V_38.Param;

      HasLocals = TRUE;
      ParamName = W_100->Name;
      IsOutput = FALSE;
      ProcFormals(W_100->Type);
      if (Sets_IsElement((Sets_tElement)W_100->Name, &LabelNames)) {
        Scanner_Error((STRING)"identifier previously declared", 30L, W_100->Pos);
      } else {
        Sets_Include(&LabelNames, (Sets_tElement)W_100->Name);
      }
      CheckTargetCode(W_100->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_101 = &t->U_1.V_83.ProcCall;

      CheckTargetCode(W_101->Call);
      CheckTargetCode(W_101->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_102 = &t->U_1.V_84.Condition;

      CheckTargetCode(W_102->Expr);
      CheckTargetCode(W_102->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_103 = &t->U_1.V_85.Assignment;

      CheckTargetCode(W_103->Expr);
      CheckTargetCode(W_103->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_104 = &t->U_1.V_88.TargetStmt;

      ActNames = W_104->UsedNames;
      CheckTargetCode(W_104->Stmt);
      Sets_ReleaseSet(&W_104->UsedNames);
      CheckTargetCode(W_104->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_105 = &t->U_1.V_82.Statement;

      CheckTargetCode(W_105->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_106 = &t->U_1.V_45.OnePattern;

      CheckTargetCode(W_106->Pattern);
      CheckTargetCode(W_106->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_107 = &t->U_1.V_63.OneExpr;

      CheckTargetCode(W_107->Expr);
      CheckTargetCode(W_107->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_108 = &t->U_1.V_51.Decompose;

      CheckTargetCode(W_108->Expr);
      CheckTargetCode(W_108->Patterns);
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_109 = &t->U_1.V_60.Value;

      CheckTargetCode(W_109->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_110 = &t->U_1.V_66.Compose;

      CheckTargetCode(W_110->Expr);
      CheckTargetCode(W_110->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_111 = &t->U_1.V_70.Call;

      CheckTargetCode(W_111->Expr);
      CheckTargetCode(W_111->Exprs);
      CheckTargetCode(W_111->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
  case Tree_yy1:;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinary *W_112 = &t->U_1.V_71.Binary;

      CheckTargetCode(W_112->Lop);
      CheckTargetCode(W_112->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_113 = &t->U_1.V_74.PreOperator;

      CheckTargetCode(W_113->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_114 = &t->U_1.V_75.PostOperator;

      CheckTargetCode(W_114->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_115 = &t->U_1.V_77.Parents;

      CheckTargetCode(W_115->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_116 = &t->U_1.V_76.Index;

      CheckTargetCode(W_116->Expr);
      CheckTargetCode(W_116->Exprs);
      return;
    }
    break;
  case Tree_TargetExpr:;
    {
      register Tree_yTargetExpr *W_117 = &t->U_1.V_78.TargetExpr;

      ActNames = W_117->UsedNames;
      CheckTargetCode(W_117->Expr);
      Sets_ReleaseSet(&W_117->UsedNames);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_118 = &t->U_1.V_16.Ident;

      if (Sets_IsElement((Sets_tElement)W_118->Attribute, &ActNames) && Semantics_IdentifyVar(Decls, W_118->Attribute) != Tree_NoTree) {
        Scanner_Error((STRING)"label not computed yet", 22L, W_118->Pos);
      }
      CheckTargetCode(W_118->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_119 = &t->U_1.V_18.Any;

      CheckTargetCode(W_119->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_120 = &t->U_1.V_19.Anys;

      CheckTargetCode(W_120->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_121 = &t->U_1.V_15.Designator;

      CheckTargetCode(W_121->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void Semantics_RemoveTreeTypes
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Spec:;
    {
      register Tree_ySpec *W_122 = &t->U_1.V_26.Spec;

      Semantics_RemoveTreeTypes(W_122->TreeNames);
      return;
    }
    break;
  case Tree_TreeName:;
    {
      register struct S_21 *W_123 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yTreeName *W_124 = &t->U_1.V_29.TreeName;

        Strings_ArrayToString((STRING)"t", 1L, &W_123->String1);
        Idents_GetString(W_124->Name, &W_123->String2);
        Strings_Concatenate(&W_123->String1, &W_123->String2);
        W_123->i = Idents_MakeIdent(&W_123->String1);
        if (W_123->i <= Semantics_TypeCount) {
          Sets_Exclude(&Semantics_TypeNames, (Sets_tElement)W_123->i);
        }
        Semantics_RemoveTreeTypes(W_124->Next);
        return;
      }
    }
    break;
  default :
    break;
  }
}

static BOOLEAN HasReject
# ifdef __STDC__
(Tree_tTree yyP1)
# else
(yyP1)
Tree_tTree yyP1;
# endif
{
  struct S_22 yyTempo;

  if (yyP1 == Tree_NoTree) {
    return FALSE;
  }
  switch (yyP1->U_1.V_1.Kind) {
  case Tree_Reject:;
    return TRUE;
    break;
  case Tree_Statement:;
  case Tree_ProcCall:;
  case Tree_Condition:;
  case Tree_Assignment:;
  case Tree_Fail:;
  case Tree_TargetStmt:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    for (;;) {
      {
        register Tree_yStatement *W_125 = &yyP1->U_1.V_82.Statement;

        if (!HasReject(W_125->Next)) {
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

void Semantics_BeginSemantics
# ifdef __STDC__
()
# else
()
# endif
{
  dFormals = Tree_mDummyFormal((Tree_tTree)Tree_NoTree);
  dFormals->U_1.V_96.DummyFormal.Next = dFormals;
  nNoFormal = Tree_mNoFormal();
  Strings_ArrayToString((STRING)".", 1L, &String1);
  IdentDot = Idents_MakeIdent(&String1);
  Strings_ArrayToString((STRING)"EmptyType", 9L, &String1);
  IdentEmptyType = Idents_MakeIdent(&String1);
  Strings_ArrayToString((STRING)"FALSE", 5L, &String1);
  IdentFalse = Idents_MakeIdent(&String1);
  Strings_ArrayToString((STRING)"TRUE", 4L, &String1);
  IdentTrue = Idents_MakeIdent(&String1);
  Strings_ArrayToString((STRING)"NIL", 3L, &String1);
  IdentNil = Idents_MakeIdent(&String1);
  StringRefNil = Idents_GetStringRef(IdentNil);
  nNoDesignator = Tree_mNoDesignator();
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
    Idents__init();
    Sets__init();
    Tree__init();
    System__init();
    IO__init();
    Tree__init();
    General__init();
    IO__init();
    DynArray__init();
    Strings__init();
    StringMem__init();
    Idents__init();
    Texts__init();
    Scanner__init();
    Positions__init();
    Assertions__init();
    Sets__init();
    Tree__init();

    Semantics_yyf = IO_StdOutput;
    Semantics_Exit = yyExit;
    Semantics_BeginSemantics();
  }
}
