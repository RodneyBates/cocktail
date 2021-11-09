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

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
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

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_Optimize
#include "Optimize.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_IOUtils
#include "IOUtils.h"
#endif

#ifndef DEFINITION_Assertions
#include "Assertions.h"
#endif

#ifndef DEFINITION_M2
#include "M2.h"
#endif

IO_tFile M2_yyf;
PROC M2_Exit;

#define kProcedure        0
#define kFunction        1
#define kPredicate        2
static unsigned char RoutineKind;
static CARDINAL i, j;
static INTEGER ListCount;
static Tree_tTree rule, TheClass, InFormals, OutFormals, ReturnFormals, Decls;
static Idents_tIdent TheName;
static BOOLEAN TemposDone;
static void WriteLine ARGS((Positions_tPosition Line));
static void Match ARGS((Tree_tTree t, Tree_tTree Formals));
static void MatchExprs ARGS((Tree_tTree t));
static void MatchExpr ARGS((Tree_tTree t));
static void AssignTempos ARGS((Tree_tTree t));
static void AssignTempo ARGS((Tree_tTree t));
static void AssignFormals ARGS((Tree_tTree t, Tree_tTree Formals));
static void AssignFormal ARGS((Tree_tTree t, Tree_tTree Formals));
static void BeginFormals ARGS((Tree_tTree Formals));
static INTEGER ConsPatterns ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER ConsTempos ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER Expressions ARGS((Tree_tTree t, INTEGER ListCount));
static void Expression ARGS((Tree_tTree t));
static void Tg2 ARGS((Tree_tTree t, Tree_tTree Formals));
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
static BOOLEAN NeedsWITHStmt ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void WritePathRecurse ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void WritePath ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void Declare ARGS((Tree_tTree t));
struct S_9 {
    union {
        struct {
            struct S_10 {
                Tree_tTree Var;
            } yyR2;
        } V_1;
    } U_1;
};
static void Tg1 ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void Tg3 ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim2 ARGS((Tree_tTree OneTest, Tree_tTree yyP1));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void Case ARGS((Tree_tTree t));
struct S_15 {
    union {
        struct {
            struct S_16 {
                CARDINAL n;
            } yyR1;
        } V_1;
    } U_1;
};
static void yyExit ARGS(());


static void WriteLine
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
    IO_WriteS(Tree_f, Tree_SourceFile.A, 256L);
    IO_WriteS(Tree_f, (STRING)"\" *)", 4L);
    IO_WriteNl(Tree_f);
  }
}

static void Match
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Idents_tIdent TreeName;
  Tree_tTree Pattern;

  if (t->U_1.V_1.Kind == Tree_NoPattern || !Tree_IsType(Formals, Tree_Formal)) {
    return;
  }
  Pattern = t->U_1.V_45.OnePattern.Pattern;
  switch (Pattern->U_1.V_1.Kind) {
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_1 = &Pattern->U_1.V_51.Decompose;

      TreeName = W_1->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      if (Formals->U_1.V_93.Formal.TypeDesc->U_1.V_1.Kind == Tree_UserType || Sets_IsNotEqual(W_1->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.Types, Formals->U_1.V_93.Formal.TypeDesc->U_1.V_98.NodeTypes.Types)) {
        if (W_1->Object->U_1.V_5.Class.Extensions->U_1.V_1.Kind == Tree_NoClass) {
          IO_WriteS(Tree_f, (STRING)"      IF (", 10L);
          WritePath(W_1->Path);
          IO_WriteS(Tree_f, (STRING)"^.Kind # ", 9L);
        } else {
          IO_WriteS(Tree_f, (STRING)"      IF NOT ", 13L);
          Tree_WI(TreeName);
          IO_WriteS(Tree_f, (STRING)".IsType (", 9L);
          WritePath(W_1->Path);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        Tree_WI(TreeName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_1->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)") THEN EXIT; END;", 17L);
        IO_WriteNl(Tree_f);
      }
      Match(W_1->Patterns, W_1->Object->U_1.V_5.Class.Formals);
    }
    break;
  case Tree_VarDef:;
    {
      register Tree_yVarDef *W_2 = &Pattern->U_1.V_52.VarDef;

      if (W_2->Object != Tree_NoTree) {
        {
          register Tree_yFormal *W_3 = &W_2->Object->U_1.V_93.Formal;

          IO_WriteS(Tree_f, (STRING)"      IF NOT (equal", 19L);
          M2_ImplMod(W_3->TypeDesc);
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          WritePath(W_3->Path);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
          WritePath(Pattern->U_1.V_52.VarDef.Path);
          IO_WriteS(Tree_f, (STRING)")) THEN EXIT; END;", 18L);
          IO_WriteNl(Tree_f);
        }
      }
    }
    break;
  case Tree_NilTest:;
    IO_WriteS(Tree_f, (STRING)"      IF ", 9L);
    WritePath(Pattern->U_1.V_53.NilTest.Path);
    IO_WriteS(Tree_f, (STRING)" # NIL THEN EXIT; END;", 22L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    break;
  case Tree_DontCareExplicit:;
  case Tree_DontCareInternal:;
    return;
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_4 = &Pattern->U_1.V_60.Value;

      AssignTempo(W_4->Expr);
      IO_WriteS(Tree_f, (STRING)"      IF NOT (equal", 19L);
      M2_ImplMod(Formals->U_1.V_93.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      WritePath(W_4->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Expression(W_4->Expr);
      IO_WriteS(Tree_f, (STRING)")) THEN EXIT; END;", 18L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_4->Expr);
    }
    break;
  }
  Match(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_93.Formal.Next);
}

static void MatchExprs
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    return;
  }
  if (Tree_IsType(t->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
    return;
  }
  MatchExpr(t->U_1.V_63.OneExpr.Expr);
  MatchExprs(t->U_1.V_63.OneExpr.Next);
}

static void MatchExpr
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Compose:;
    MatchExprs(t->U_1.V_66.Compose.Exprs);
    break;
  case Tree_VarUse:;
    break;
  case Tree_Nil:;
    break;
  case Tree_DontCare1Explicit:;
    break;
  case Tree_DontCare1Internal:;
    break;
  case Tree_TargetExpr:;
    break;
  case Tree_StringExpr:;
    break;
  case Tree_AttrDesc:;
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_5 = &t->U_1.V_70.Call;

      MatchExpr(W_5->Expr);
      MatchExprs(W_5->Exprs);
      if (W_5->Object != Tree_NoTree) {
        Match(W_5->Patterns, W_5->Object->U_1.V_32.Routine.OutForm);
      }
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_6 = &t->U_1.V_71.Binary;

      MatchExpr(W_6->Lop);
      MatchExpr(W_6->Rop);
    }
    break;
  case Tree_PreOperator:;
    MatchExpr(t->U_1.V_74.PreOperator.Expr);
    break;
  case Tree_PostOperator:;
    MatchExpr(t->U_1.V_75.PostOperator.Expr);
    break;
  case Tree_Index:;
    MatchExpr(t->U_1.V_76.Index.Expr);
    MatchExprs(t->U_1.V_76.Index.Exprs);
    break;
  case Tree_Parents:;
    MatchExpr(t->U_1.V_77.Parents.Expr);
    break;
  }
}

static void AssignTempos
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    return;
  }
  if (Tree_IsType(t->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
    return;
  }
  AssignTempo(t->U_1.V_63.OneExpr.Expr);
  AssignTempos(t->U_1.V_63.OneExpr.Next);
}

static void AssignTempo
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Idents_tIdent TreeName;

  switch (t->U_1.V_1.Kind) {
  case Tree_Compose:;
    {
      register Tree_yCompose *W_7 = &t->U_1.V_66.Compose;

      TreeName = W_7->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      IO_WriteS(Tree_f, (STRING)"      yyALLOC (", 15L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",Make", 5L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(W_7->Tempo);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(W_7->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      if (W_7->Exprs->U_1.V_1.Kind == Tree_OneExpr && !Tree_IsType(W_7->Exprs->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
        IO_WriteS(Tree_f, (STRING)"      WITH ", 11L);
        Tree_WI(W_7->Tempo);
        IO_WriteS(Tree_f, (STRING)"^.", 2L);
        Tree_WI(W_7->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
        IO_WriteNl(Tree_f);
        AssignFormals(W_7->Exprs, W_7->Object->U_1.V_5.Class.Formals);
        IO_WriteS(Tree_f, (STRING)"      END;", 10L);
        IO_WriteNl(Tree_f);
      }
    }
    break;
  case Tree_VarUse:;
    break;
  case Tree_Nil:;
    break;
  case Tree_DontCare1Explicit:;
    break;
  case Tree_DontCare1Internal:;
    break;
  case Tree_TargetExpr:;
    break;
  case Tree_StringExpr:;
    break;
  case Tree_AttrDesc:;
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_8 = &t->U_1.V_70.Call;

      AssignTempo(W_8->Expr);
      AssignTempos(W_8->Exprs);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_9 = &t->U_1.V_71.Binary;

      AssignTempo(W_9->Lop);
      AssignTempo(W_9->Rop);
    }
    break;
  case Tree_PreOperator:;
    AssignTempo(t->U_1.V_74.PreOperator.Expr);
    break;
  case Tree_PostOperator:;
    AssignTempo(t->U_1.V_75.PostOperator.Expr);
    break;
  case Tree_Index:;
    AssignTempo(t->U_1.V_76.Index.Expr);
    AssignTempos(t->U_1.V_76.Index.Exprs);
    break;
  case Tree_Parents:;
    AssignTempo(t->U_1.V_77.Parents.Expr);
    break;
  }
}

static void AssignFormals
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
  if (Tree_IsType(t->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
    BeginFormals(Formals);
    return;
  }
  AssignFormal(t->U_1.V_63.OneExpr.Expr, Formals);
  AssignFormals(t->U_1.V_63.OneExpr.Next, Formals->U_1.V_93.Formal.Next);
}

static void AssignFormal
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Idents_tIdent TreeName;

  if (t->U_1.V_1.Kind == Tree_Compose) {
    {
      register Tree_yCompose *W_10 = &t->U_1.V_66.Compose;

      TreeName = W_10->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      IO_WriteS(Tree_f, (STRING)"      yyALLOC (", 15L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",Make", 5L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(Formals->U_1.V_93.Formal.Name);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(W_10->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      if (W_10->Exprs->U_1.V_1.Kind == Tree_OneExpr && !Tree_IsType(W_10->Exprs->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
        IO_WriteS(Tree_f, (STRING)"      WITH ", 11L);
        Tree_WI(Formals->U_1.V_93.Formal.Name);
        IO_WriteS(Tree_f, (STRING)"^.", 2L);
        Tree_WI(W_10->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
        IO_WriteNl(Tree_f);
        AssignFormals(W_10->Exprs, W_10->Object->U_1.V_5.Class.Formals);
        IO_WriteS(Tree_f, (STRING)"      END;", 10L);
        IO_WriteNl(Tree_f);
      }
    }
  } else {
    AssignTempo(t);
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_VarUse:;
  case Tree_Nil:;
  case Tree_Call:;
  case Tree_Binary:;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
  case Tree_Index:;
  case Tree_Parents:;
  case Tree_TargetExpr:;
  case Tree_StringExpr:;
  case Tree_AttrDesc:;
    IO_WriteS(Tree_f, (STRING)"      ", 6L);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" := ", 4L);
    Expression(t);
    IO_WriteS(Tree_f, (STRING)";", 1L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    IO_WriteS(Tree_f, (STRING)"      begin", 11L);
    M2_ImplMod(Formals->U_1.V_93.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" (", 2L);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)")", 1L);
    IO_WriteNl(Tree_f);
    break;
  default :
    break;
  }
}

static void BeginFormals
# ifdef __STDC__
(Tree_tTree Formals)
# else
(Formals)
Tree_tTree Formals;
# endif
{
  if (Tree_IsType(Formals, Tree_Formal)) {
    {
      register Tree_yFormal *W_11 = &Formals->U_1.V_93.Formal;

      IO_WriteS(Tree_f, (STRING)"      begin", 11L);
      M2_ImplMod(W_11->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Tree_WI(W_11->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      BeginFormals(W_11->Next);
    }
  }
}

static INTEGER ConsPatterns
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount)
# else
(t, ListCount)
Tree_tTree t;
INTEGER ListCount;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoPattern) {
    return ListCount;
  }
  {
    register Tree_yOnePattern *W_12 = &t->U_1.V_45.OnePattern;

    if (Tree_IsType(W_12->Pattern, Tree_DontCare)) {
      return ConsTempos(W_12->Pattern->U_1.V_57.DontCare.Tempos, ListCount);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Tree_WI(W_12->Pattern->U_1.V_50.Pattern.Tempo);
      return ConsPatterns(W_12->Next, ListCount + 1);
    }
  }
}

static INTEGER ConsTempos
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount)
# else
(t, ListCount)
Tree_tTree t;
INTEGER ListCount;
# endif
{
  if (Tree_IsType(t, Tree_Formal)) {
    if (ListCount > 0) {
      IO_WriteS(Tree_f, (STRING)", ", 2L);
    }
    Tree_WI(t->U_1.V_93.Formal.Name);
    return ConsTempos(t->U_1.V_93.Formal.Next, ListCount + 1);
  } else {
    return ListCount;
  }
}

static INTEGER Expressions
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount)
# else
(t, ListCount)
Tree_tTree t;
INTEGER ListCount;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    return ListCount;
  }
  {
    register Tree_yOneExpr *W_13 = &t->U_1.V_63.OneExpr;

    if (Tree_IsType(W_13->Expr, Tree_DontCare)) {
      return ConsTempos(W_13->Expr->U_1.V_57.DontCare.Tempos, ListCount);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Expression(W_13->Expr);
      return Expressions(W_13->Next, ListCount + 1);
    }
  }
}

static void Expression
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Compose:;
    Tree_WI(t->U_1.V_66.Compose.Tempo);
    break;
  case Tree_Nil:;
    IO_WriteS(Tree_f, (STRING)"NIL", 3L);
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_14 = &t->U_1.V_67.VarUse;

      if (W_14->Object != Tree_NoTree) {
        WritePath(W_14->Object->U_1.V_93.Formal.Path);
      } else {
        Tree_WI(W_14->Name);
      }
    }
    break;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    Tree_WI(t->U_1.V_54.DontCare1.Tempo);
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_15 = &t->U_1.V_70.Call;

      Expression(W_15->Expr);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      ListCount = Expressions(W_15->Exprs, 0L);
      if (W_15->Object != Tree_NoTree) {
        ListCount = ConsPatterns(W_15->Patterns, ListCount);
      } else {
        ListCount = Expressions(W_15->Patterns, ListCount);
      }
      IO_WriteS(Tree_f, (STRING)")", 1L);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_16 = &t->U_1.V_71.Binary;

      Expression(W_16->Lop);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_16->Operator);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Expression(W_16->Rop);
    }
    break;
  case Tree_PreOperator:;
    Tree_WI(t->U_1.V_74.PreOperator.Operator);
    IO_WriteS(Tree_f, (STRING)" ", 1L);
    Expression(t->U_1.V_74.PreOperator.Expr);
    break;
  case Tree_PostOperator:;
    Expression(t->U_1.V_75.PostOperator.Expr);
    IO_WriteS(Tree_f, (STRING)" ", 1L);
    Tree_WI(t->U_1.V_75.PostOperator.Operator);
    break;
  case Tree_Index:;
    Expression(t->U_1.V_76.Index.Expr);
    IO_WriteS(Tree_f, (STRING)" [", 2L);
    ListCount = Expressions(t->U_1.V_76.Index.Exprs, 0L);
    IO_WriteS(Tree_f, (STRING)"]", 1L);
    break;
  case Tree_Parents:;
    IO_WriteS(Tree_f, (STRING)"(", 1L);
    Expression(t->U_1.V_77.Parents.Expr);
    IO_WriteS(Tree_f, (STRING)")", 1L);
    break;
  case Tree_TargetExpr:;
    M2_ImplMod(t->U_1.V_78.TargetExpr.Expr);
    break;
  case Tree_StringExpr:;
    StringMem_WriteString(Tree_f, t->U_1.V_79.StringExpr.String);
    break;
  case Tree_AttrDesc:;
    {
      register Tree_yAttrDesc *W_17 = &t->U_1.V_68.AttrDesc;

      WritePath(W_17->Object->U_1.V_93.Formal.Path);
      IO_WriteS(Tree_f, (STRING)"^.", 2L);
      Tree_WI(W_17->Type);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_17->Attribute);
    }
    break;
  }
}

static void Tg2
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoPattern || Formals->U_1.V_1.Kind == Tree_NoFormal) {
    return;
  }
  switch (t->U_1.V_45.OnePattern.Pattern->U_1.V_1.Kind) {
  case Tree_Decompose:;
    IO_WriteS(Tree_f, (STRING)"     WITH ", 10L);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)"^.", 2L);
    Tree_WI(t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Object->U_1.V_5.Class.Name);
    IO_WriteS(Tree_f, (STRING)" DO", 3L);
    IO_WriteNl(Tree_f);
    Tg2(t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Patterns, t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Object->U_1.V_5.Class.Formals);
    break;
  case Tree_VarDef:;
  case Tree_NilTest:;
  case Tree_Value:;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    break;
  default :
    return;
    break;
  }
  Tg2(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_93.Formal.Next);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module M2, routine ", 26L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*M2_Exit)();
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

void M2_MacroMod
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
  case Tree_Spec:;
    {
      register Tree_ySpec *W_18 = &t->U_1.V_26.Spec;

      M2_MacroMod(W_18->TreeNames);
      return;
    }
    break;
  case Tree_TreeName:;
    {
      register Tree_yTreeName *W_19 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)"# define begint", 15L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)"(a)       a := NIL;", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equalt", 15L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)"(a, b)    ", 10L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)".IsEqual", 8L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)" (a, b)", 7L);
      IO_WriteNl(Tree_f);
      M2_MacroMod(W_19->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void M2_DefMod
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
  case Tree_Spec:;
    {
      register Tree_ySpec *W_20 = &t->U_1.V_26.Spec;

      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"(* This file was mechanically generated by puma. *)", 51L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"DEFINITION MODULE ", 18L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT SYSTEM, IO", 17L);
      M2_DefMod(W_20->TreeNames);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_20->Codes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_20->Codes->U_1.V_12.Codes.Import);
      IO_WriteNl(Tree_f);
      WriteLine(W_20->Codes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_20->Codes->U_1.V_12.Codes.Export);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyf        : IO.tFile;", 26L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR Exit       : PROC;", 22L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M2_DefMod(W_20->Public);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TreeName:;
    {
      register Tree_yTreeName *W_21 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Tree_WI(W_21->Name);
      M2_DefMod(W_21->Next);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_22 = &t->U_1.V_25.Name;

      if (W_22->Object != Tree_NoTree) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        M2_DefMod(W_22->Object->U_1.V_32.Routine.InForm);
        M2_DefMod(W_22->Object->U_1.V_32.Routine.OutForm);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        if (W_22->Object->U_1.V_1.Kind == Tree_Predicate) {
          IO_WriteS(Tree_f, (STRING)": BOOLEAN", 9L);
        } else if (W_22->Object->U_1.V_1.Kind == Tree_Function) {
          IO_WriteS(Tree_f, (STRING)": ", 2L);
          M2_DefMod(W_22->Object->U_1.V_34.Function.ReturnForm->U_1.V_93.Formal.TypeDesc);
        }
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      M2_DefMod(W_22->Next);
      return;
    }
    break;
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_23 = &t->U_1.V_93.Formal;

      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
      }
      if (W_23->Path->U_1.V_101.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)"VAR ", 4L);
      }
      Tree_WI(W_23->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      M2_DefMod(W_23->TypeDesc);
      INC(ListCount);
      M2_DefMod(W_23->Next);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_24 = &t->U_1.V_98.NodeTypes;

      Tree_WI(W_24->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".t", 2L);
      Tree_WI(W_24->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_25 = &t->U_1.V_99.UserType;

      Tree_WI(W_25->Type);
      return;
    }
    break;
  default :
    break;
  }
}

static BOOLEAN NeedsWITHStmt
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return FALSE;
  }
  for (;;) {
    {
      register Tree_yRule *W_26 = &t->U_1.V_42.Rule;

      if (!Sets_IsElement(ORD('w'), &Tree_Options)) {
        goto EXIT_1;
      }
      if (!(W_26->Statements->U_1.V_1.Kind != Tree_NoStatement || W_26->Exprs->U_1.V_1.Kind != Tree_NoExpr || W_26->Expr->U_1.V_1.Kind != Tree_NoExpr)) {
        goto EXIT_1;
      }
      return TRUE;
    }
  } EXIT_1:;
  return FALSE;
}

void M2_ImplMod
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
  case Tree_Spec:;
    {
      register Tree_ySpec *W_27 = &t->U_1.V_26.Spec;

      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"(* This file was mechanically generated by puma. *)", 51L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPLEMENTATION MODULE ", 22L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('m'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# define yyInline", 17L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"# ifdef yyInline", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(tree, make, ptr, kind) ", 40L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr := tree.yyPoolFreePtr; ", 29L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IF SYSTEM.ADDRESS (ptr) >= tree.yyPoolMaxPtr THEN ptr := tree.yyAlloc (); END; ", 81L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  INC (tree.yyPoolFreePtr, tree.yyNodeSize [tree.kind]); ", 57L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr^.yyHead.yyMark := 0; ", 27L);
      IOUtils_WriteBackslash(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr^.Kind := tree.kind;", 25L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(tree, make, ptr, kind) ptr := tree.make (tree.kind);", 69L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWrite(s) IO.WriteS (yyf, s)", 38L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWriteNl IO.WriteNl (yyf)", 35L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT SYSTEM, System, IO", 25L);
      M2_DefMod(W_27->TreeNames);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_27->Codes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_27->Codes->U_1.V_12.Codes.Global);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyAbort (yyFunction: ARRAY OF CHAR);", 46L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdError, 'Error: module ", 41L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)", routine ');", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdError, yyFunction);", 38L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdError, ' failed');", 37L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteNl (IO.StdError);", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  Exit;", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyAbort;", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIsEqual (yya, yyb: ARRAY OF SYSTEM.BYTE): BOOLEAN;", 62L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" VAR yyi       : INTEGER;", 25L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO INTEGER (HIGH (yya)) DO", 41L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"   IF yya [yyi] # yyb [yyi] THEN RETURN FALSE; END;", 51L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  RETURN TRUE;", 14L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyIsEqual;", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_27->Routines);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      WriteLine(W_27->Codes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_27->Codes->U_1.V_12.Codes.Begin);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END Begin", 10L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      WriteLine(W_27->Codes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_27->Codes->U_1.V_12.Codes.Close);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END Close", 10L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyExit;", 17L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.CloseIO; System.Exit (1);", 30L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyExit;", 12L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" yyf   := IO.StdOutput;", 23L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" Exit  := yyExit;", 17L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" Begin", 6L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_27->TrafoName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_28 = &t->U_1.V_33.Procedure;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_28->Name);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      M2_DefMod(W_28->InForm);
      M2_DefMod(W_28->OutForm);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      WriteLine(W_28->LocalLine);
      Texts_WriteText(Tree_f, W_28->Local);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" VAR yyTempo: RECORD CASE : INTEGER OF", 38L);
      IO_WriteNl(Tree_f);
      RoutineKind = kProcedure;
      InFormals = W_28->InForm;
      OutFormals = W_28->OutForm;
      Declare(W_28->Rules);
      IO_WriteS(Tree_f, (STRING)" END; END;", 10L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_28->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        M2_ImplMod(W_28->Rules);
        if (Sets_IsElement(ORD('f'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
          Tree_WI(W_28->Name);
          IO_WriteS(Tree_f, (STRING)"');", 3L);
          IO_WriteNl(Tree_f);
        }
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_28->Decisions);
        if (Sets_IsElement(ORD('f'), &Tree_Options) && !Optimize_NeedsNoFinale(W_28->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
          Tree_WI(W_28->Name);
          IO_WriteS(Tree_f, (STRING)"');", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_28->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_28->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_29 = &t->U_1.V_34.Function;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_29->Name);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      M2_DefMod(W_29->InForm);
      M2_DefMod(W_29->OutForm);
      IO_WriteS(Tree_f, (STRING)"): ", 3L);
      M2_DefMod(W_29->ReturnForm->U_1.V_93.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_29->LocalLine);
      Texts_WriteText(Tree_f, W_29->Local);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" VAR yyTempo: RECORD CASE : INTEGER OF", 38L);
      IO_WriteNl(Tree_f);
      RoutineKind = kFunction;
      InFormals = W_29->InForm;
      OutFormals = W_29->OutForm;
      ReturnFormals = W_29->ReturnForm;
      Declare(W_29->Rules);
      IO_WriteS(Tree_f, (STRING)" END; END;", 10L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        M2_ImplMod(W_29->Rules);
        IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
        Tree_WI(W_29->Name);
        IO_WriteS(Tree_f, (STRING)"');", 3L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_29->Decisions);
        if (!Optimize_NeedsNoFinale(W_29->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
          Tree_WI(W_29->Name);
          IO_WriteS(Tree_f, (STRING)"');", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_29->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_29->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_30 = &t->U_1.V_35.Predicate;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_30->Name);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      M2_DefMod(W_30->InForm);
      M2_DefMod(W_30->OutForm);
      IO_WriteS(Tree_f, (STRING)"): BOOLEAN;", 11L);
      IO_WriteNl(Tree_f);
      WriteLine(W_30->LocalLine);
      Texts_WriteText(Tree_f, W_30->Local);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" VAR yyTempo: RECORD CASE : INTEGER OF", 38L);
      IO_WriteNl(Tree_f);
      RoutineKind = kPredicate;
      InFormals = W_30->InForm;
      OutFormals = W_30->OutForm;
      Declare(W_30->Rules);
      IO_WriteS(Tree_f, (STRING)" END; END;", 10L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_30->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        M2_ImplMod(W_30->Rules);
        IO_WriteS(Tree_f, (STRING)"  RETURN FALSE;", 15L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_30->Decisions);
        if (!Optimize_NeedsNoFinale(W_30->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  RETURN FALSE;", 15L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_30->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_30->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_31 = &t->U_1.V_42.Rule;

      WriteLine(W_31->Line);
      if (W_31->HasTempos) {
        IO_WriteS(Tree_f, (STRING)"    WITH yyTempo.yyR", 20L);
        Tree_WN((LONGINT)W_31->Index);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
      }
      IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
      IO_WriteNl(Tree_f);
      Decls = W_31->VarDecls;
      Match(W_31->Patterns, InFormals);
      if (NeedsWITHStmt(t)) {
        Tg2(W_31->Patterns, InFormals);
      }
      M2_ImplMod(W_31->Statements);
      if (!W_31->HasRejectOrFail) {
        AssignFormals(W_31->Exprs, OutFormals);
        MatchExprs(W_31->Exprs);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"      RETURN;", 13L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          AssignTempo(W_31->Expr);
          if (W_31->HasPatterns && W_31->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
            IO_WriteS(Tree_f, (STRING)"      ", 6L);
            Tree_WI(W_31->Tempo);
            IO_WriteS(Tree_f, (STRING)" := ", 4L);
            Expression(W_31->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_31->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Tree_WI(W_31->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          } else {
            MatchExpr(W_31->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Expression(W_31->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"      RETURN TRUE;", 18L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (NeedsWITHStmt(t)) {
        Tg3(W_31->Patterns);
      }
      IO_WriteS(Tree_f, (STRING)"   END (* LOOP *) ;", 19L);
      IO_WriteNl(Tree_f);
      if (W_31->HasTempos) {
        IO_WriteS(Tree_f, (STRING)"    END (* WITH yyTempo.yyR ... *) ;", 36L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_31->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_32 = &t->U_1.V_83.ProcCall;

      WriteLine(W_32->Pos);
      AssignTempo(W_32->Call);
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Expression(W_32->Call);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_32->Call);
      M2_ImplMod(W_32->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_33 = &t->U_1.V_84.Condition;

      WriteLine(W_33->Pos);
      AssignTempo(W_33->Expr);
      IO_WriteS(Tree_f, (STRING)"      IF NOT (", 14L);
      Expression(W_33->Expr);
      IO_WriteS(Tree_f, (STRING)") THEN EXIT; END;", 17L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_33->Expr);
      M2_ImplMod(W_33->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_34 = &t->U_1.V_85.Assignment;

      WriteLine(W_34->Pos);
      AssignTempo(W_34->Adr);
      AssignTempo(W_34->Expr);
      if (W_34->Object != Tree_NoTree) {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        WritePath(W_34->Object->U_1.V_93.Formal.Path);
      } else {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Expression(W_34->Adr);
      }
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Expression(W_34->Expr);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_34->Adr);
      MatchExpr(W_34->Expr);
      M2_ImplMod(W_34->Next);
      return;
    }
    break;
  case Tree_Reject:;
    {
      register Tree_yReject *W_35 = &t->U_1.V_86.Reject;

      WriteLine(W_35->Pos);
      IO_WriteS(Tree_f, (STRING)"      EXIT;", 11L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Fail:;
    {
      register Tree_yFail *W_36 = &t->U_1.V_87.Fail;

      WriteLine(W_36->Pos);
      IO_WriteS(Tree_f, (STRING)"      RETURN", 12L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" FALSE", 6L);
      }
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_37 = &t->U_1.V_88.TargetStmt;

      WriteLine(W_37->Pos);
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      M2_ImplMod(W_37->Stmt);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_37->Next);
      return;
    }
    break;
  case Tree_Nl:;
    {
      register Tree_yNl *W_38 = &t->U_1.V_89.Nl;

      WriteLine(W_38->Pos);
      IO_WriteS(Tree_f, (STRING)"      yyWriteNl;", 16L);
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_38->Next);
      return;
    }
    break;
  case Tree_WriteStr:;
    {
      register Tree_yWriteStr *W_39 = &t->U_1.V_90.WriteStr;

      WriteLine(W_39->Pos);
      IO_WriteS(Tree_f, (STRING)"      yyWrite (", 15L);
      StringMem_WriteString(Tree_f, W_39->String);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      M2_ImplMod(W_39->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_40 = &t->U_1.V_16.Ident;

      if (W_40->Object != Tree_NoTree) {
        WritePath(W_40->Object->U_1.V_93.Formal.Path);
      } else {
        Tree_WI(W_40->Attribute);
      }
      M2_ImplMod(W_40->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_41 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_41->Code);
      M2_ImplMod(W_41->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_42 = &t->U_1.V_19.Anys;

      M2_ImplMod(W_42->Layouts);
      M2_ImplMod(W_42->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_43 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_43->Code);
      M2_ImplMod(W_43->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_44 = &t->U_1.V_15.Designator;

      WritePath(W_44->Object->U_1.V_93.Formal.Path);
      IO_WriteS(Tree_f, (STRING)"^.", 2L);
      Tree_WI(W_44->Type);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_44->Attribute);
      M2_ImplMod(W_44->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_45 = &t->U_1.V_103.Field;

      Assertions_CantHappen((STRING)"M2, ImplMod, Field", 18L);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_46 = &t->U_1.V_102.ConsType;

      Assertions_CantHappen((STRING)"M2, ImplMod, ConsType", 21L);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_47 = &t->U_1.V_101.Var;

      Assertions_CantHappen((STRING)"M2, ImplMod, Var", 16L);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_48 = &t->U_1.V_98.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"t", 1L);
      Tree_WI(W_48->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_49 = &t->U_1.V_99.UserType;

      Tree_WI(W_49->Type);
      return;
    }
    break;
  default :
    break;
  }
}

static void WritePathRecurse
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
  case Tree_Field:;
    {
      register Tree_yField *W_50 = &t->U_1.V_103.Field;

      WritePathRecurse(W_50->Next);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_50->Name);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_51 = &t->U_1.V_102.ConsType;

      WritePathRecurse(W_51->Next);
      IO_WriteS(Tree_f, (STRING)"^.", 2L);
      Tree_WI(W_51->Name);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_52 = &t->U_1.V_101.Var;

      Tree_WI(W_52->Name);
      return;
    }
    break;
  default :
    break;
  }
}

static void WritePath
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
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_53 = &t->U_1.V_102.ConsType;

      WritePathRecurse(W_53->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_54 = &t->U_1.V_103.Field;

      WritePathRecurse(t);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_55 = &t->U_1.V_101.Var;

      WritePathRecurse(t);
      return;
    }
    break;
  default :
    break;
  }
}

static void Declare
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
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_56 = &t->U_1.V_93.Formal;

      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      Tree_WI(W_56->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      M2_DefMod(W_56->TypeDesc);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Declare(W_56->Next);
      return;
    }
    break;
  case Tree_Param:;
    {
      register struct S_10 *W_57 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yParam *W_58 = &t->U_1.V_38.Param;

        W_57->Var = Semantics_IdentifyVar(Decls, W_58->Name);
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_58->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        M2_DefMod(W_57->Var->U_1.V_93.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        Declare(W_58->Next);
        return;
      }
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_59 = &t->U_1.V_42.Rule;

      if (W_59->HasTempos) {
        IO_WriteS(Tree_f, (STRING)" | ", 3L);
        Tree_WN((LONGINT)W_59->Index);
        IO_WriteS(Tree_f, (STRING)": yyR", 5L);
        Tree_WN((LONGINT)W_59->Index);
        IO_WriteS(Tree_f, (STRING)": RECORD", 8L);
        IO_WriteNl(Tree_f);
        Decls = W_59->VarDecls;
        Declare(W_59->Patterns);
        Declare(W_59->Exprs);
        if (RoutineKind == kFunction) {
          Declare(W_59->Expr);
          if (W_59->HasPatterns && W_59->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
            IO_WriteS(Tree_f, (STRING)"  ", 2L);
            Tree_WI(W_59->Tempo);
            IO_WriteS(Tree_f, (STRING)": ", 2L);
            M2_DefMod(ReturnFormals->U_1.V_93.Formal.TypeDesc);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
        }
        Declare(W_59->Statements);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_59->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_60 = &t->U_1.V_83.ProcCall;

      Declare(W_60->Call);
      Declare(W_60->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_61 = &t->U_1.V_84.Condition;

      Declare(W_61->Expr);
      Declare(W_61->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_62 = &t->U_1.V_85.Assignment;

      Declare(W_62->Adr);
      Declare(W_62->Expr);
      Declare(W_62->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_63 = &t->U_1.V_88.TargetStmt;

      Declare(W_63->Parameters);
      Declare(W_63->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_64 = &t->U_1.V_82.Statement;

      Declare(W_64->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_65 = &t->U_1.V_45.OnePattern;

      if (W_65->Pattern->U_1.V_50.Pattern.Tempo != Idents_NoIdent && !Tree_IsType(W_65->Pattern, Tree_DontCare1)) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_65->Pattern->U_1.V_50.Pattern.Tempo);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        M2_DefMod(W_65->Pattern->U_1.V_50.Pattern.TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_65->Pattern);
      Declare(W_65->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_66 = &t->U_1.V_63.OneExpr;

      Declare(W_66->Expr);
      Declare(W_66->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_67 = &t->U_1.V_51.Decompose;

      Declare(W_67->Patterns);
      return;
    }
    break;
  case Tree_DontCare:;
  case Tree_DontCareExplicit:;
  case Tree_DontCareInternal:;
    {
      register Tree_yDontCare *W_68 = &t->U_1.V_57.DontCare;

      Declare(W_68->Tempos);
      return;
    }
    break;
  case Tree_DontCare1:;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    {
      register Tree_yDontCare1 *W_69 = &t->U_1.V_54.DontCare1;

      if (W_69->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_69->Tempo);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        M2_DefMod(W_69->TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_70 = &t->U_1.V_60.Value;

      Declare(W_70->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_71 = &t->U_1.V_66.Compose;

      if (W_71->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_71->Tempo);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        M2_DefMod(W_71->TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_71->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_72 = &t->U_1.V_70.Call;

      Declare(W_72->Expr);
      Declare(W_72->Exprs);
      Declare(W_72->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
  case Tree_yy1:;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinary *W_73 = &t->U_1.V_71.Binary;

      Declare(W_73->Lop);
      Declare(W_73->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_74 = &t->U_1.V_74.PreOperator;

      Declare(W_74->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_75 = &t->U_1.V_75.PostOperator;

      Declare(W_75->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_76 = &t->U_1.V_77.Parents;

      Declare(W_76->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_77 = &t->U_1.V_76.Index;

      Declare(W_77->Expr);
      Declare(W_77->Exprs);
      return;
    }
    break;
  default :
    break;
  }
}

static void Tg1
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
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_78 = &t->U_1.V_93.Formal;

      TheName = W_78->Name;
      Tg1(W_78->TypeDesc);
      Tg1(W_78->Next);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_79 = &t->U_1.V_98.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      Tree_WI(TheName);
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Tree_WI(W_79->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".No", 3L);
      Tree_WI(W_79->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" THEN RETURN", 12L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" FALSE", 6L);
      }
      IO_WriteS(Tree_f, (STRING)"; END;", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  default :
    break;
  }
}

static void Tg3
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
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_80 = &t->U_1.V_45.OnePattern;

      Tg3(W_80->Pattern);
      Tg3(W_80->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_81 = &t->U_1.V_51.Decompose;

      Tg3(W_81->Patterns);
      IO_WriteS(Tree_f, (STRING)"     END (* WITH *) ;", 21L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  default :
    break;
  }
}

static void CommonTestElim2
# ifdef __STDC__
(Tree_tTree OneTest, Tree_tTree yyP1)
# else
(OneTest, yyP1)
Tree_tTree OneTest;
Tree_tTree yyP1;
# endif
{
  struct S_13 yyTempo;

  if (OneTest == Tree_NoTree) {
    return;
  }
  if (yyP1 == Tree_NoTree) {
    return;
  }
  if (OneTest->U_1.V_1.Kind == Tree_TestValue) {
    for (;;) {
      {
        register Tree_yTestValue *W_82 = &OneTest->U_1.V_111.TestValue;

        if (!Optimize_NeedsMatch(W_82->Expr)) {
          goto EXIT_2;
        }
        CommonTestElim(OneTest);
        IO_WriteS(Tree_f, (STRING)"    LOOP", 8L);
        IO_WriteNl(Tree_f);
        MatchExpr(OneTest->U_1.V_111.TestValue.Expr);
        CommonTestElim(yyP1);
        IO_WriteS(Tree_f, (STRING)"    EXIT; END;", 14L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_2:;
  }
  CommonTestElim(OneTest);
  CommonTestElim(yyP1);
  return;
}

static void CommonTestElim
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
  case Tree_Decision:;
    {
      register Tree_yDecision *W_83 = &t->U_1.V_114.Decision;

      if (W_83->Cases == 0) {
        if (!TemposDone && W_83->OneTest->U_1.V_1.Kind == Tree_TestValue && Optimize_NeedsTempo(W_83->ThenPart, &rule)) {
          IO_WriteS(Tree_f, (STRING)"    WITH yyTempo.yyR", 20L);
          Tree_WN((LONGINT)rule->U_1.V_42.Rule.Index);
          IO_WriteS(Tree_f, (STRING)" DO ", 4L);
          IO_WriteNl(Tree_f);
          TemposDone = TRUE;
          CommonTestElim2(W_83->OneTest, W_83->ThenPart);
          IO_WriteS(Tree_f, (STRING)"  END;", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END (* WITH yyTempo.yyR ... *) ; ", 37L);
          IO_WriteNl(Tree_f);
        } else {
          Optimize_GetRule(W_83->ThenPart, &rule);
          Decls = rule->U_1.V_42.Rule.VarDecls;
          CommonTestElim2(W_83->OneTest, W_83->ThenPart);
          IO_WriteS(Tree_f, (STRING)"  END;", 6L);
          IO_WriteNl(Tree_f);
        }
        TemposDone = FALSE;
        CommonTestElim(W_83->ElsePart);
      } else {
        i = W_83->Cases;
        Case(t);
      }
      return;
    }
    break;
  case Tree_Decided:;
    {
      register Tree_yDecided *W_84 = &t->U_1.V_115.Decided;

      CommonTestElim(W_84->Rule);
      if (W_84->Rule->U_1.V_42.Rule.HasExit) {
        TemposDone = FALSE;
        CommonTestElim(W_84->ElsePart);
      }
      return;
    }
    break;
  case Tree_TestKind:;
    {
      register Tree_yTestKind *W_85 = &t->U_1.V_107.TestKind;

      IO_WriteS(Tree_f, (STRING)"  IF (", 6L);
      WritePath(W_85->Path);
      IO_WriteS(Tree_f, (STRING)"^.Kind = ", 9L);
      Tree_WI(W_85->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_85->Name);
      IO_WriteS(Tree_f, (STRING)") THEN", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_86 = &t->U_1.V_108.TestIsType;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      Tree_WI(W_86->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".IsType (", 9L);
      WritePath(W_86->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Tree_WI(W_86->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_86->Name);
      IO_WriteS(Tree_f, (STRING)") THEN", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNil:;
    {
      register Tree_yTestNil *W_87 = &t->U_1.V_109.TestNil;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      WritePath(W_87->Path);
      IO_WriteS(Tree_f, (STRING)" = NIL THEN", 11L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNonlin:;
    {
      register Tree_yTestNonlin *W_88 = &t->U_1.V_110.TestNonlin;

      IO_WriteS(Tree_f, (STRING)"  IF (equal", 11L);
      M2_ImplMod(W_88->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      WritePath(W_88->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      WritePath(W_88->Path2);
      IO_WriteS(Tree_f, (STRING)")) THEN", 7L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestValue:;
    {
      register Tree_yTestValue *W_89 = &t->U_1.V_111.TestValue;

      AssignTempo(W_89->Expr);
      IO_WriteS(Tree_f, (STRING)"  IF (equal", 11L);
      M2_ImplMod(W_89->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      WritePath(W_89->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Expression(W_89->Expr);
      IO_WriteS(Tree_f, (STRING)")) THEN", 7L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_90 = &t->U_1.V_42.Rule;

      WriteLine(W_90->Line);
      if (W_90->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)"    WITH yyTempo.yyR", 20L);
        Tree_WN((LONGINT)W_90->Index);
        IO_WriteS(Tree_f, (STRING)" DO  ", 5L);
        IO_WriteNl(Tree_f);
      }
      if (W_90->HasExit) {
        IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
        IO_WriteNl(Tree_f);
      }
      Decls = W_90->VarDecls;
      if (NeedsWITHStmt(t)) {
        Tg2(W_90->Patterns, InFormals);
      }
      M2_ImplMod(W_90->Statements);
      if (!W_90->HasRejectOrFail) {
        AssignFormals(W_90->Exprs, OutFormals);
        MatchExprs(W_90->Exprs);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"      RETURN;", 13L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          AssignTempo(W_90->Expr);
          if (W_90->HasPatterns && W_90->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
            IO_WriteS(Tree_f, (STRING)"      ", 6L);
            Tree_WI(W_90->Tempo);
            IO_WriteS(Tree_f, (STRING)" := ", 4L);
            Expression(W_90->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_90->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Tree_WI(W_90->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          } else {
            MatchExpr(W_90->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Expression(W_90->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"      RETURN TRUE;", 18L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (NeedsWITHStmt(t)) {
        Tg3(W_90->Patterns);
      }
      if (W_90->HasExit) {
        IO_WriteS(Tree_f, (STRING)"   END (* LOOP *) ;", 19L);
        IO_WriteNl(Tree_f);
      }
      if (W_90->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)"    END (* WITH yyTempos.yyR ... *) ;  ", 39L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  default :
    break;
  }
}

static void Case
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
  case Tree_Decision:;
    {
      register struct S_16 *W_91 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yDecision *W_92 = &t->U_1.V_114.Decision;

        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE ", 7L);
        WritePath(W_92->OneTest->U_1.V_106.OneTest.Path);
        IO_WriteS(Tree_f, (STRING)"^.Kind OF", 9L);
        IO_WriteNl(Tree_f);
        W_91->n = i;
        while (W_91->n > 0) {
          if (!Sets_IsEmpty(t->U_1.V_114.Decision.OneTest->U_1.V_108.TestIsType.TypeDesc->U_1.V_98.NodeTypes.Types)) {
            Case(t->U_1.V_114.Decision.OneTest);
            CommonTestElim(t->U_1.V_114.Decision.ThenPart);
          }
          t = t->U_1.V_114.Decision.ElsePart;
          DEC(W_91->n);
        }
        IO_WriteS(Tree_f, (STRING)"  ELSE END;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        CommonTestElim(t);
        return;
      }
    }
    break;
  case Tree_TestKind:;
    {
      register Tree_yTestKind *W_93 = &t->U_1.V_107.TestKind;

      IO_WriteS(Tree_f, (STRING)"  | ", 4L);
      Tree_WI(W_93->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_93->Name);
      IO_WriteS(Tree_f, (STRING)":", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_94 = &t->U_1.V_108.TestIsType;

      {
        register Tree_yNodeTypes *W_95 = &W_94->TypeDesc->U_1.V_98.NodeTypes;

        TheClass = Semantics_LookupClass(W_95->TreeName->U_1.V_29.TreeName.Classes, Sets_Minimum(&W_95->Types));
        IO_WriteS(Tree_f, (STRING)"  | ", 4L);
        Tree_WI(W_95->TreeName->U_1.V_29.TreeName.Name);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(TheClass->U_1.V_5.Class.Name);
        Case(W_94->TypeDesc);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_96 = &t->U_1.V_98.NodeTypes;

      {
        LONGCARD B_3 = Sets_Minimum(&W_96->Types) + 1, B_4 = Sets_Maximum(&W_96->Types);

        if (B_3 <= B_4)
          for (j = B_3;; j += 1) {
            if (Sets_IsElement(j, &W_96->Types)) {
              TheClass = Semantics_LookupClass(W_96->TreeName->U_1.V_29.TreeName.Classes, j);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"  , ", 4L);
              Tree_WI(W_96->TreeName->U_1.V_29.TreeName.Name);
              IO_WriteS(Tree_f, (STRING)".", 1L);
              Tree_WI(TheClass->U_1.V_5.Class.Name);
            }
            if (j >= B_4) break;
          }
      }
      return;
    }
    break;
  default :
    break;
  }
}

void M2_BeginM2
# ifdef __STDC__
()
# else
()
# endif
{
}

void M2_CloseM2
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

void M2__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Tree__init();
    System__init();
    IO__init();
    Tree__init();
    Positions__init();
    IO__init();
    StringMem__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Semantics__init();
    Optimize__init();
    Tree__init();
    IOUtils__init();
    Assertions__init();

    M2_yyf = IO_StdOutput;
    M2_Exit = yyExit;
    M2_BeginM2();
  }
}
