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

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_Optimize
#include "Optimize.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Assertions
#include "Assertions.h"
#endif

#ifndef DEFINITION_Ada
#include "Ada.h"
#endif

IO_tFile Ada_yyf;
PROC Ada_Exit;

#define kProcedure        0
#define kFunction        1
#define kPredicate        2
static unsigned char RoutineKind;
static CARDINAL i, j;
static INTEGER ListCount, WithCount;
static Tree_tTree rule, TheClass, InFormals, OutFormals, ReturnFormals, Decls;
static Idents_tIdent TheName;
static BOOLEAN TemposDone;
static void WriteLine ARGS((Positions_tPosition Line));
static void Match ARGS((Tree_tTree t, Tree_tTree Formals));
static void MatchExprs ARGS((Tree_tTree t));
static void MatchExpr ARGS((Tree_tTree t));
static void AssignTempos ARGS((Tree_tTree t));
static void AssignTempo ARGS((Tree_tTree t));
static Idents_tIdent MakeWith ARGS(());
static void AssignFormals ARGS((Tree_tTree t, Tree_tTree Formals));
static void AssignFormal ARGS((Tree_tTree t, Tree_tTree Formals));
static void BeginFormals ARGS((Tree_tTree Formals));
static void AssignSubFormals ARGS((Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer));
static void AssignSubFormal ARGS((Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer));
static void BeginSubFormals ARGS((Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer));
static INTEGER ConsPatterns ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER ConsTempos ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER Expressions ARGS((Tree_tTree t, INTEGER ListCount));
static void Expression ARGS((Tree_tTree t));
static void Tg2 ARGS((Tree_tTree t, Tree_tTree Formals));
static void Tg2Attrs ARGS((Tree_tTree AttrFormals));
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
static void TreeOperators ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void ForwardDecls ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static BOOLEAN NeedsDeclareRenames ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void WritePathRecurse ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void WritePath ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void Declare ARGS((Tree_tTree t));
struct S_11 {
    union {
        struct {
            struct S_12 {
                Tree_tTree Var;
            } yyR2;
        } V_1;
    } U_1;
};
static void Tg1 ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void Tg3 ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim2 ARGS((Tree_tTree OneTest, Tree_tTree yyP1));
struct S_15 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim ARGS((Tree_tTree t));
struct S_16 {
    union {
        char dummy;
    } U_1;
};
static void Case ARGS((Tree_tTree t));
struct S_17 {
    union {
        struct {
            struct S_18 {
                CARDINAL n;
            } yyR1;
        } V_1;
    } U_1;
};
static void yyExit ARGS(());

static Tree_tTree *G_1_Object;
static Idents_tIdent *G_2_FormalName;
static Tree_tTree *G_3_Formals;

static void WriteLine
# ifdef __STDC__
(Positions_tPosition Line)
# else
(Line)
Positions_tPosition Line;
# endif
{
  if (Line.Line != 0) {
    IO_WriteS(Tree_f, (STRING)"-- line ", 8L);
    Tree_WN((LONGINT)Line.Line);
    IO_WriteS(Tree_f, (STRING)", file \"", 8L);
    IO_WriteS(Tree_f, Tree_SourceFile.A, 256L);
    IO_WriteS(Tree_f, (STRING)"\" ", 2L);
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
          IO_WriteS(Tree_f, (STRING)"        IF (", 12L);
          WritePath(W_1->Path);
          IO_WriteS(Tree_f, (STRING)".ALL.Kind /= ", 13L);
        } else {
          IO_WriteS(Tree_f, (STRING)"        IF NOT ", 15L);
          Tree_WI(TreeName);
          IO_WriteS(Tree_f, (STRING)".IsType (", 9L);
          WritePath(W_1->Path);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        Tree_WI(TreeName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_1->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)") THEN EXIT ; END IF ;", 22L);
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

          IO_WriteS(Tree_f, (STRING)"        IF NOT (equal", 21L);
          Ada_PackBody(W_3->TypeDesc);
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          WritePath(W_3->Path);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
          WritePath(Pattern->U_1.V_52.VarDef.Path);
          IO_WriteS(Tree_f, (STRING)")) THEN EXIT ; END IF ;", 23L);
          IO_WriteNl(Tree_f);
        }
      }
    }
    break;
  case Tree_NilTest:;
    IO_WriteS(Tree_f, (STRING)"        IF ", 11L);
    WritePath(Pattern->U_1.V_53.NilTest.Path);
    IO_WriteS(Tree_f, (STRING)" /= NULL THEN EXIT ; END IF ;", 29L);
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
      IO_WriteS(Tree_f, (STRING)"        IF NOT (equal", 21L);
      Ada_PackBody(Formals->U_1.V_93.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      WritePath(W_4->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Expression(W_4->Expr);
      IO_WriteS(Tree_f, (STRING)")) THEN EXIT ; END IF ;", 23L);
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
  case Tree_PostOperator:;
    MatchExpr(t->U_1.V_74.PreOperator.Expr);
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
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Tree_WI(W_7->Tempo);
      IO_WriteS(Tree_f, (STRING)" := NEW ", 8L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" . yyNode ( ", 12L);
      Tree_WI(W_7->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      AssignSubFormals(W_7->Exprs, W_7->Object->U_1.V_5.Class.Formals, W_7->Tempo, W_7->Object->U_1.V_5.Class.Name);
    }
    break;
  case Tree_VarUse:;
    break;
  case Tree_Nil:;
    break;
  case Tree_DontCare1Explicit:;
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
  case Tree_PostOperator:;
    AssignTempo(t->U_1.V_74.PreOperator.Expr);
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

static Idents_tIdent MakeWith
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString String1, String2;

  INC(WithCount);
  Strings_ArrayToString((STRING)"yyW", 3L, &String1);
  Strings_IntToString(WithCount, &String2);
  Strings_Concatenate(&String1, &String2);
  return Idents_MakeIdent(&String1);
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
  Idents_tIdent TreeName, With;

  if (t->U_1.V_1.Kind == Tree_Compose) {
    {
      register Tree_yCompose *W_10 = &t->U_1.V_66.Compose;

      TreeName = W_10->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      With = MakeWith();
      IO_WriteS(Tree_f, (STRING)"      DECLARE -- Compose ", 25L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)" : ", 3L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" . t", 4L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"            := NEW ", 19L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" . yyNode ( ", 12L);
      Tree_WI(W_10->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      BEGIN -- DECLARE Compose ", 31L);
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      Tree_WI(Formals->U_1.V_93.Formal.Name);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      AssignSubFormals(W_10->Exprs, W_10->Object->U_1.V_5.Class.Formals, With, W_10->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)"      END ; -- DECLARE Compose ", 31L);
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
    IO_WriteS(Tree_f, (STRING)"begin", 5L);
    Ada_PackBody(Formals->U_1.V_93.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" ( ", 3L);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
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
      Ada_PackBody(W_11->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      Tree_WI(W_11->Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      BeginFormals(W_11->Next);
    }
  }
}

static void AssignSubFormals
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer)
# else
(t, Formals, PrevWith, Composer)
Tree_tTree t, Formals;
Idents_tIdent PrevWith, Composer;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr || !Tree_IsType(Formals, Tree_Formal)) {
    return;
  }
  if (Tree_IsType(t->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
    BeginSubFormals(Formals, PrevWith, Composer);
    return;
  }
  AssignSubFormal(t->U_1.V_63.OneExpr.Expr, Formals, PrevWith, Composer);
  AssignSubFormals(t->U_1.V_63.OneExpr.Next, Formals->U_1.V_93.Formal.Next, PrevWith, Composer);
}

static void AssignSubFormal
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer)
# else
(t, Formals, PrevWith, Composer)
Tree_tTree t, Formals;
Idents_tIdent PrevWith, Composer;
# endif
{
  Idents_tIdent TreeName, With;

  if (t->U_1.V_1.Kind == Tree_Compose) {
    {
      register Tree_yCompose *W_12 = &t->U_1.V_66.Compose;

      TreeName = W_12->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      With = MakeWith();
      IO_WriteS(Tree_f, (STRING)"      DECLARE -- Subcompose ", 28L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)" : ", 3L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" . t", 4L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"            := NEW ", 19L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" . yyNode ( ", 12L);
      Tree_WI(W_12->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      BEGIN -- DECLARE Subcompose ", 34L);
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      Tree_WI(PrevWith);
      IO_WriteS(Tree_f, (STRING)" . ALL . ", 9L);
      Tree_WI(Composer);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(Formals->U_1.V_93.Formal.Name);
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      AssignSubFormals(W_12->Exprs, W_12->Object->U_1.V_5.Class.Formals, With, W_12->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)"      END ; -- DECLARE Subcompose ", 34L);
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
    IO_WriteS(Tree_f, (STRING)"        ", 8L);
    Tree_WI(PrevWith);
    IO_WriteS(Tree_f, (STRING)" . ALL . ", 9L);
    Tree_WI(Composer);
    IO_WriteS(Tree_f, (STRING)" . ", 3L);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" := ", 4L);
    Expression(t);
    IO_WriteS(Tree_f, (STRING)" ; ", 3L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    IO_WriteS(Tree_f, (STRING)"begin", 5L);
    Ada_PackBody(Formals->U_1.V_93.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" ( ", 3L);
    Tree_WI(PrevWith);
    IO_WriteS(Tree_f, (STRING)" . ALL . ", 9L);
    Tree_WI(Composer);
    IO_WriteS(Tree_f, (STRING)" . ", 3L);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
    IO_WriteNl(Tree_f);
    break;
  default :
    break;
  }
}

static void BeginSubFormals
# ifdef __STDC__
(Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer)
# else
(Formals, PrevWith, Composer)
Tree_tTree Formals;
Idents_tIdent PrevWith, Composer;
# endif
{
  if (Tree_IsType(Formals, Tree_Formal)) {
    {
      register Tree_yFormal *W_13 = &Formals->U_1.V_93.Formal;

      IO_WriteS(Tree_f, (STRING)"      begin", 11L);
      Ada_PackBody(W_13->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      Tree_WI(PrevWith);
      IO_WriteS(Tree_f, (STRING)" . ALL . ", 9L);
      Tree_WI(Composer);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_13->Name);
      IO_WriteS(Tree_f, (STRING)" ) ; ", 5L);
      IO_WriteNl(Tree_f);
      BeginSubFormals(W_13->Next, PrevWith, Composer);
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
    register Tree_yOnePattern *W_14 = &t->U_1.V_45.OnePattern;

    if (Tree_IsType(W_14->Pattern, Tree_DontCare)) {
      return ConsTempos(W_14->Pattern->U_1.V_57.DontCare.Tempos, ListCount);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Tree_WI(W_14->Pattern->U_1.V_50.Pattern.Tempo);
      return ConsPatterns(W_14->Next, ListCount + 1);
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
    register Tree_yOneExpr *W_15 = &t->U_1.V_63.OneExpr;

    if (Tree_IsType(W_15->Expr, Tree_DontCare)) {
      return ConsTempos(W_15->Expr->U_1.V_57.DontCare.Tempos, ListCount);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Expression(W_15->Expr);
      return Expressions(W_15->Next, ListCount + 1);
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
    IO_WriteS(Tree_f, (STRING)"NULL ", 5L);
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_16 = &t->U_1.V_67.VarUse;

      if (W_16->Object != Tree_NoTree) {
        WritePath(W_16->Object->U_1.V_93.Formal.Path);
      } else {
        Tree_WI(W_16->Name);
      }
    }
    break;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    Tree_WI(t->U_1.V_54.DontCare1.Tempo);
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_17 = &t->U_1.V_70.Call;

      Expression(W_17->Expr);
      if (W_17->Exprs->U_1.V_1.Kind == Tree_NoExpr && (W_17->Patterns->U_1.V_1.Kind == Tree_NoPattern || W_17->Patterns->U_1.V_1.Kind == Tree_NoExpr)) {
      } else {
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        ListCount = Expressions(W_17->Exprs, 0L);
        if (W_17->Object != Tree_NoTree) {
          ListCount = ConsPatterns(W_17->Patterns, ListCount);
        } else {
          ListCount = Expressions(W_17->Patterns, ListCount);
        }
        IO_WriteS(Tree_f, (STRING)") ", 2L);
        IO_WriteNl(Tree_f);
      }
    }
    break;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinaryCompound *W_18 = &t->U_1.V_73.BinaryCompound;

      Expression(W_18->Lop);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_18->Operator);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_18->CompoundOperator);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Expression(W_18->Rop);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_19 = &t->U_1.V_71.Binary;

      Expression(W_19->Lop);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_19->Operator);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Expression(W_19->Rop);
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
    IO_WriteS(Tree_f, (STRING)" (", 2L);
    ListCount = Expressions(t->U_1.V_76.Index.Exprs, 0L);
    IO_WriteS(Tree_f, (STRING)")", 1L);
    break;
  case Tree_Parents:;
    IO_WriteS(Tree_f, (STRING)"(", 1L);
    Expression(t->U_1.V_77.Parents.Expr);
    IO_WriteS(Tree_f, (STRING)")", 1L);
    break;
  case Tree_TargetExpr:;
    Ada_PackBody(t->U_1.V_78.TargetExpr.Expr);
    break;
  case Tree_StringExpr:;
    StringMem_WriteString(Tree_f, t->U_1.V_79.StringExpr.String);
    break;
  case Tree_AttrDesc:;
    {
      register Tree_yAttrDesc *W_20 = &t->U_1.V_68.AttrDesc;

      WritePath(W_20->Object->U_1.V_93.Formal.Path);
      IO_WriteS(Tree_f, (STRING)" . ALL . ", 9L);
      Tree_WI(W_20->Type);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_20->Attribute);
    }
    break;
  }
}

static void Tg2Attrs
# ifdef __STDC__
(Tree_tTree AttrFormals)
# else
(AttrFormals)
Tree_tTree AttrFormals;
# endif
{
  Idents_tIdent LNewFormalName;
  Strings_tString LString1, LString2;

  if (Tree_IsType(AttrFormals, Tree_Formal)) {
    if (AttrFormals->U_1.V_93.Formal.Name == *G_2_FormalName) {
      Strings_ArrayToString((STRING)"Puma_Rename_Of_", 15L, &LString1);
      Idents_GetString(*G_2_FormalName, &LString2);
      Strings_Concatenate(&LString1, &LString2);
      LNewFormalName = Idents_MakeIdent(&LString1);
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Tree_WI(LNewFormalName);
      IO_WriteS(Tree_f, (STRING)" : ", 3L);
      Ada_PackSpec((*G_3_Formals)->U_1.V_93.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)" RENAMES ", 9L);
      Tree_WI(*G_2_FormalName);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      *G_2_FormalName = LNewFormalName;
    }
    IO_WriteS(Tree_f, (STRING)"      ", 6L);
    Tree_WI(AttrFormals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" : ", 3L);
    Ada_PackSpec(AttrFormals->U_1.V_93.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" RENAMES ", 9L);
    Tree_WI(*G_2_FormalName);
    IO_WriteS(Tree_f, (STRING)" . ALL . ", 9L);
    Tree_WI((*G_1_Object)->U_1.V_5.Class.Name);
    IO_WriteS(Tree_f, (STRING)" . ", 3L);
    Tree_WI(AttrFormals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" ; ", 3L);
    IO_WriteNl(Tree_f);
    Tg2Attrs(AttrFormals->U_1.V_93.Formal.Next);
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
  Tree_tTree Object;
  Idents_tIdent FormalName;
  Tree_tTree *L_1;
  Idents_tIdent *L_2;
  Tree_tTree *L_3;

  L_1 = G_1_Object;
  G_1_Object = &Object;
  L_2 = G_2_FormalName;
  G_2_FormalName = &FormalName;
  L_3 = G_3_Formals;
  G_3_Formals = &Formals;
  if (t->U_1.V_1.Kind == Tree_NoPattern || Formals->U_1.V_1.Kind == Tree_NoFormal) {
    G_1_Object = L_1;
    G_2_FormalName = L_2;
    G_3_Formals = L_3;
    return;
  }
  switch (t->U_1.V_45.OnePattern.Pattern->U_1.V_1.Kind) {
  case Tree_Decompose:;
    IO_WriteS(Tree_f, (STRING)"    DECLARE -- Renames ", 23L);
    IO_WriteNl(Tree_f);
    Object = t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Object;
    FormalName = Formals->U_1.V_93.Formal.Name;
    Tg2Attrs(Object->U_1.V_5.Class.Formals);
    IO_WriteS(Tree_f, (STRING)"    BEGIN -- DECLARE renames ", 29L);
    IO_WriteNl(Tree_f);
    Tg2(t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Patterns, Object->U_1.V_5.Class.Formals);
    break;
  case Tree_VarDef:;
  case Tree_NilTest:;
  case Tree_Value:;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    break;
  default :
    G_1_Object = L_1;
    G_2_FormalName = L_2;
    G_3_Formals = L_3;
    return;
    break;
  }
  Tg2(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_93.Formal.Next);
  G_1_Object = L_1;
  G_2_FormalName = L_2;
  G_3_Formals = L_3;
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Ada, routine ", 27L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Ada_Exit)();
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

void Ada_MacroAda
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
      register Tree_ySpec *W_21 = &t->U_1.V_26.Spec;

      Ada_MacroAda(W_21->TreeNames);
      return;
    }
    break;
  case Tree_TreeName:;
    {
      register Tree_yTreeName *W_22 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)"# define begint", 15L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)"(a) ( a ) := NULL ; ", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equalt", 15L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)"(a, b)    ", 10L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)".IsEqual", 8L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)" (a, b)", 7L);
      IO_WriteNl(Tree_f);
      Ada_MacroAda(W_22->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void Ada_PackSpec
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
      register Tree_ySpec *W_23 = &t->U_1.V_26.Spec;

      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"-- This file was mechanically generated by puma. ", 49L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"WITH Text_Io ", 13L);
      IO_WriteNl(Tree_f);
      Ada_PackSpec(W_23->TreeNames);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_23->Codes->U_1.V_12.Codes.SpecWithLine);
      Texts_WriteText(Tree_f, W_23->Codes->U_1.V_12.Codes.SpecWith);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PACKAGE ", 8L);
      Tree_WI(W_23->TrafoName);
      IO_WriteS(Tree_f, (STRING)"", 1L);
      IO_WriteS(Tree_f, (STRING)" IS ", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      WriteLine(W_23->Codes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_23->Codes->U_1.V_12.Codes.Import);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      WriteLine(W_23->Codes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_23->Codes->U_1.V_12.Codes.Export);
      IO_WriteNl(Tree_f);
      Ada_PackSpec(W_23->Public);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  PROCEDURE Begin", 17L);
      Tree_WI(W_23->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  PROCEDURE Close", 17L);
      Tree_WI(W_23->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_23->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TreeName:;
    {
      register Tree_yTreeName *W_24 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Tree_WI(W_24->Name);
      Ada_PackSpec(W_24->Next);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_25 = &t->U_1.V_25.Name;

      if (W_25->Object != Tree_NoTree) {
        if (W_25->Object->U_1.V_1.Kind == Tree_Predicate || W_25->Object->U_1.V_1.Kind == Tree_Function) {
          IO_WriteS(Tree_f, (STRING)"FUNCTION ", 9L);
        } else {
          IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
        }
        Tree_WI(W_25->Name);
        if (W_25->Object->U_1.V_32.Routine.InForm->U_1.V_1.Kind == Tree_NoFormal && W_25->Object->U_1.V_32.Routine.OutForm->U_1.V_1.Kind == Tree_NoFormal) {
        } else {
          IO_WriteS(Tree_f, (STRING)" ( ", 3L);
          ListCount = 0;
          Ada_PackSpec(W_25->Object->U_1.V_32.Routine.InForm);
          Ada_PackSpec(W_25->Object->U_1.V_32.Routine.OutForm);
          IO_WriteS(Tree_f, (STRING)" ) ", 3L);
          IO_WriteNl(Tree_f);
        }
        if (W_25->Object->U_1.V_1.Kind == Tree_Predicate) {
          IO_WriteS(Tree_f, (STRING)"RETURN BOOLEAN ", 15L);
        } else if (W_25->Object->U_1.V_1.Kind == Tree_Function) {
          IO_WriteS(Tree_f, (STRING)"RETURN ", 7L);
          Ada_PackSpec(W_25->Object->U_1.V_34.Function.ReturnForm->U_1.V_93.Formal.TypeDesc);
        }
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
      }
      Ada_PackSpec(W_25->Next);
      return;
    }
    break;
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_26 = &t->U_1.V_93.Formal;

      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
      }
      Tree_WI(W_26->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      if (W_26->Path->U_1.V_101.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)"IN OUT ", 7L);
      }
      Ada_PackSpec(W_26->TypeDesc);
      INC(ListCount);
      Ada_PackSpec(W_26->Next);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_27 = &t->U_1.V_98.NodeTypes;

      Tree_WI(W_27->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".t", 2L);
      Tree_WI(W_27->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_28 = &t->U_1.V_99.UserType;

      Tree_WI(W_28->Type);
      return;
    }
    break;
  default :
    break;
  }
}

static void TreeOperators
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
  if (t->U_1.V_1.Kind == Tree_TreeName) {
    {
      register Tree_yTreeName *W_29 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)"  USE ", 6L);
      Tree_WI(W_29->Name);
      IO_WriteS(Tree_f, (STRING)" . Operators ; ", 15L);
      TreeOperators(W_29->Next);
      return;
    }
  }
}

static void ForwardDecls
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
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_30 = &t->U_1.V_33.Procedure;

      if (!W_30->IsExtern) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"  PROCEDURE ", 12L);
        Tree_WI(W_30->Name);
        if (W_30->InForm->U_1.V_1.Kind == Tree_NoFormal && W_30->OutForm->U_1.V_1.Kind == Tree_NoFormal) {
        } else {
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          Ada_PackSpec(W_30->InForm);
          Ada_PackSpec(W_30->OutForm);
          IO_WriteS(Tree_f, (STRING)") ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
        IO_WriteNl(Tree_f);
      }
      ForwardDecls(W_30->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_31 = &t->U_1.V_34.Function;

      if (!W_31->IsExtern) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"  FUNCTION ", 11L);
        Tree_WI(W_31->Name);
        if (W_31->InForm->U_1.V_1.Kind == Tree_NoFormal && W_31->OutForm->U_1.V_1.Kind == Tree_NoFormal) {
        } else {
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          Ada_PackSpec(W_31->InForm);
          Ada_PackSpec(W_31->OutForm);
          IO_WriteS(Tree_f, (STRING)") ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)" RETURN ", 8L);
        Ada_PackSpec(W_31->ReturnForm->U_1.V_93.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ; ", 3L);
        IO_WriteNl(Tree_f);
      }
      ForwardDecls(W_31->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_32 = &t->U_1.V_35.Predicate;

      if (!W_32->IsExtern) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"  FUNCTION ", 11L);
        Tree_WI(W_32->Name);
        if (W_32->InForm->U_1.V_1.Kind == Tree_NoFormal && W_32->OutForm->U_1.V_1.Kind == Tree_NoFormal) {
        } else {
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          Ada_PackSpec(W_32->InForm);
          Ada_PackSpec(W_32->OutForm);
          IO_WriteS(Tree_f, (STRING)") ", 2L);
        }
        IO_WriteS(Tree_f, (STRING)"RETURN BOOLEAN ; ", 17L);
        IO_WriteNl(Tree_f);
      }
      ForwardDecls(W_32->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static BOOLEAN NeedsDeclareRenames
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_7 yyTempo;

  if (t == Tree_NoTree) {
    return FALSE;
  }
  for (;;) {
    {
      register Tree_yRule *W_33 = &t->U_1.V_42.Rule;

      if (!Sets_IsElement(ORD('w'), &Tree_Options)) {
        goto EXIT_1;
      }
      if (!(W_33->Statements->U_1.V_1.Kind != Tree_NoStatement || W_33->Exprs->U_1.V_1.Kind != Tree_NoExpr || W_33->Expr->U_1.V_1.Kind != Tree_NoExpr)) {
        goto EXIT_1;
      }
      return TRUE;
    }
  } EXIT_1:;
  return FALSE;
}

void Ada_PackBody
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
  case Tree_Spec:;
    {
      register Tree_ySpec *W_34 = &t->U_1.V_26.Spec;

      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"-- This file was mechanically generated by puma. ", 49L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"WITH PumaSys , Text_Io ", 23L);
      IO_WriteNl(Tree_f);
      Ada_PackSpec(W_34->TreeNames);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      WriteLine(W_34->Codes->U_1.V_12.Codes.BodyWithLine);
      Texts_WriteText(Tree_f, W_34->Codes->U_1.V_12.Codes.BodyWith);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PACKAGE BODY ", 13L);
      Tree_WI(W_34->TrafoName);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWrite(s) Text_Io . Put ( s ) ", 40L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWriteNl Text_Io . New_Line ", 38L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      WriteLine(W_34->Codes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_34->Codes->U_1.V_12.Codes.Global);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(W_34->TrafoName);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  -- Operator Visibility. ", 26L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      TreeOperators(W_34->TreeNames);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  -- Forward declarations of routines. ", 39L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      ForwardDecls(W_34->Routines);
      IO_WriteS(Tree_f, (STRING)"", 1L);
      IO_WriteS(Tree_f, (STRING)"  -- Utility routines used by Puma routine bodies. ", 51L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"", 1L);
      IO_WriteS(Tree_f, (STRING)"  PROCEDURE yyAbort (yyFunction: STRING ) ", 42L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      (Text_Io . Standard_Output , \"Error: module ", 50L);
      Tree_WI(W_34->TrafoName);
      IO_WriteS(Tree_f, (STRING)", routine \" ); ", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( Text_Io . Standard_Output, yyFunction); ", 60L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Text_Io . Put ( Text_Io . Standard_Output, \" failed\"); ", 59L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Text_Io . New_Line ( Text_Io . Standard_Output ) ; ", 55L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    RAISE PumaSys . AbortPuma ; ", 32L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END yyAbort ; ", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  -- Routine bodies. ", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"", 1L);
      Ada_PackBody(W_34->Routines);
      IO_WriteS(Tree_f, (STRING)"", 1L);
      IO_WriteS(Tree_f, (STRING)"  -- Standard routines. ", 24L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"", 1L);
      IO_WriteS(Tree_f, (STRING)"  PROCEDURE Begin", 17L);
      Tree_WI(W_34->TrafoName);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_34->Codes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_34->Codes->U_1.V_12.Codes.Begin);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END Begin", 11L);
      Tree_WI(W_34->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  PROCEDURE Close", 17L);
      Tree_WI(W_34->TrafoName);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS BEGIN ", 11L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_34->Codes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_34->Codes->U_1.V_12.Codes.Close);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END Close", 11L);
      Tree_WI(W_34->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN -- ", 9L);
      Tree_WI(W_34->TrafoName);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  Text_Io . Set_Output ( Text_Io . Standard_Output ) ; ", 55L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  Begin", 7L);
      Tree_WI(W_34->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_34->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_35 = &t->U_1.V_33.Procedure;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"  PROCEDURE ", 12L);
      Tree_WI(W_35->Name);
      if (W_35->InForm->U_1.V_1.Kind == Tree_NoFormal && W_35->OutForm->U_1.V_1.Kind == Tree_NoFormal) {
      } else {
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Ada_PackSpec(W_35->InForm);
        Ada_PackSpec(W_35->OutForm);
        IO_WriteS(Tree_f, (STRING)") ", 2L);
      }
      IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
      IO_WriteNl(Tree_f);
      if (W_35->LocalLine.Line != 0) {
        IO_WriteS(Tree_f, (STRING)"    ", 4L);
        WriteLine(W_35->LocalLine);
        Texts_WriteText(Tree_f, W_35->Local);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN -- ", 11L);
        Tree_WI(W_35->Name);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"BEGIN -- ", 9L);
        Tree_WI(W_35->Name);
        IO_WriteNl(Tree_f);
      }
      RoutineKind = kProcedure;
      InFormals = W_35->InForm;
      OutFormals = W_35->OutForm;
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_35->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        Ada_PackBody(W_35->Rules);
        if (Sets_IsElement(ORD('f'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"    yyAbort (\"", 14L);
          Tree_WI(W_35->Name);
          IO_WriteS(Tree_f, (STRING)"\");", 3L);
          IO_WriteNl(Tree_f);
        }
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_35->Decisions);
        if (Sets_IsElement(ORD('f'), &Tree_Options) && !Optimize_NeedsNoFinale(W_35->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"    yyAbort (\"", 14L);
          Tree_WI(W_35->Name);
          IO_WriteS(Tree_f, (STRING)"\");", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)"  END ", 6L);
      Tree_WI(W_35->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Ada_PackBody(W_35->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_36 = &t->U_1.V_34.Function;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"  FUNCTION ", 11L);
      Tree_WI(W_36->Name);
      if (W_36->InForm->U_1.V_1.Kind == Tree_NoFormal && W_36->OutForm->U_1.V_1.Kind == Tree_NoFormal) {
      } else {
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Ada_PackSpec(W_36->InForm);
        Ada_PackSpec(W_36->OutForm);
        IO_WriteS(Tree_f, (STRING)") ", 2L);
      }
      IO_WriteS(Tree_f, (STRING)" RETURN ", 8L);
      Ada_PackSpec(W_36->ReturnForm->U_1.V_93.Formal.TypeDesc);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
      if (W_36->LocalLine.Line != 0) {
        IO_WriteS(Tree_f, (STRING)"    ", 4L);
        WriteLine(W_36->LocalLine);
        Texts_WriteText(Tree_f, W_36->Local);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN -- ", 11L);
        Tree_WI(W_36->Name);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"BEGIN -- ", 9L);
        Tree_WI(W_36->Name);
        IO_WriteNl(Tree_f);
      }
      RoutineKind = kFunction;
      InFormals = W_36->InForm;
      OutFormals = W_36->OutForm;
      ReturnFormals = W_36->ReturnForm;
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        Ada_PackBody(W_36->Rules);
        IO_WriteS(Tree_f, (STRING)"    yyAbort (\"", 14L);
        Tree_WI(W_36->Name);
        IO_WriteS(Tree_f, (STRING)"\");", 3L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_36->Decisions);
        if (!Optimize_NeedsNoFinale(W_36->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"    yyAbort (\"", 14L);
          Tree_WI(W_36->Name);
          IO_WriteS(Tree_f, (STRING)"\");", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)"  END ", 6L);
      Tree_WI(W_36->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Ada_PackBody(W_36->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_37 = &t->U_1.V_35.Predicate;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"  FUNCTION ", 11L);
      Tree_WI(W_37->Name);
      if (W_37->InForm->U_1.V_1.Kind == Tree_NoFormal && W_37->OutForm->U_1.V_1.Kind == Tree_NoFormal) {
      } else {
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Ada_PackSpec(W_37->InForm);
        Ada_PackSpec(W_37->OutForm);
        IO_WriteS(Tree_f, (STRING)") ", 2L);
      }
      IO_WriteS(Tree_f, (STRING)"RETURN BOOLEAN ", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IS ", 5L);
      if (W_37->LocalLine.Line != 0) {
        IO_WriteS(Tree_f, (STRING)"    ", 4L);
        WriteLine(W_37->LocalLine);
        Texts_WriteText(Tree_f, W_37->Local);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  BEGIN -- ", 11L);
        Tree_WI(W_37->Name);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"BEGIN -- ", 9L);
        Tree_WI(W_37->Name);
        IO_WriteNl(Tree_f);
      }
      RoutineKind = kPredicate;
      InFormals = W_37->InForm;
      OutFormals = W_37->OutForm;
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_37->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        Ada_PackBody(W_37->Rules);
        IO_WriteS(Tree_f, (STRING)"    RETURN FALSE;", 17L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_37->Decisions);
        if (!Optimize_NeedsNoFinale(W_37->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"    RETURN FALSE;", 17L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)"  END ", 6L);
      Tree_WI(W_37->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Ada_PackBody(W_37->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_38 = &t->U_1.V_42.Rule;

      WithCount = 0;
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_38->Line);
      if (W_38->HasTempos) {
        IO_WriteS(Tree_f, (STRING)"    DECLARE -- Tempos", 21L);
        IO_WriteNl(Tree_f);
        Declare(t);
        IO_WriteS(Tree_f, (STRING)"    BEGIN -- DECLARE Tempos", 27L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"      LOOP", 10L);
      IO_WriteNl(Tree_f);
      Decls = W_38->VarDecls;
      Match(W_38->Patterns, InFormals);
      if (NeedsDeclareRenames(t)) {
        Tg2(W_38->Patterns, InFormals);
      }
      Ada_PackBody(W_38->Statements);
      if (!W_38->HasRejectOrFail) {
        AssignFormals(W_38->Exprs, OutFormals);
        MatchExprs(W_38->Exprs);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"        RETURN;", 15L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          AssignTempo(W_38->Expr);
          if (W_38->HasPatterns && W_38->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
            IO_WriteS(Tree_f, (STRING)"        ", 8L);
            Tree_WI(W_38->Tempo);
            IO_WriteS(Tree_f, (STRING)" := ", 4L);
            Expression(W_38->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_38->Expr);
            IO_WriteS(Tree_f, (STRING)"        RETURN ", 15L);
            Tree_WI(W_38->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          } else {
            MatchExpr(W_38->Expr);
            IO_WriteS(Tree_f, (STRING)"        RETURN ", 15L);
            Expression(W_38->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"        RETURN TRUE;", 20L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (NeedsDeclareRenames(t)) {
        Tg3(W_38->Patterns);
      }
      IO_WriteS(Tree_f, (STRING)"      END LOOP ; ", 17L);
      IO_WriteNl(Tree_f);
      if (W_38->HasTempos) {
        IO_WriteS(Tree_f, (STRING)"    END ; -- DECLARE Tempos", 27L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      Ada_PackBody(W_38->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_39 = &t->U_1.V_83.ProcCall;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_39->Pos);
      AssignTempo(W_39->Call);
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      Expression(W_39->Call);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_39->Call);
      Ada_PackBody(W_39->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_40 = &t->U_1.V_84.Condition;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_40->Pos);
      AssignTempo(W_40->Expr);
      IO_WriteS(Tree_f, (STRING)"        IF NOT ( ", 17L);
      Expression(W_40->Expr);
      IO_WriteS(Tree_f, (STRING)" ) THEN EXIT ; END IF ;", 23L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_40->Expr);
      Ada_PackBody(W_40->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_41 = &t->U_1.V_85.Assignment;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_41->Pos);
      AssignTempo(W_41->Adr);
      AssignTempo(W_41->Expr);
      if (W_41->Object != Tree_NoTree) {
        IO_WriteS(Tree_f, (STRING)"        ", 8L);
        WritePath(W_41->Object->U_1.V_93.Formal.Path);
      } else {
        IO_WriteS(Tree_f, (STRING)"        ", 8L);
        Expression(W_41->Adr);
      }
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Expression(W_41->Expr);
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_41->Adr);
      MatchExpr(W_41->Expr);
      Ada_PackBody(W_41->Next);
      return;
    }
    break;
  case Tree_Reject:;
    {
      register Tree_yReject *W_42 = &t->U_1.V_86.Reject;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_42->Pos);
      IO_WriteS(Tree_f, (STRING)"        EXIT ; ", 15L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Fail:;
    {
      register Tree_yFail *W_43 = &t->U_1.V_87.Fail;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_43->Pos);
      IO_WriteS(Tree_f, (STRING)"        RETURN ", 15L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" FALSE ", 7L);
      }
      IO_WriteS(Tree_f, (STRING)" ; ", 3L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_44 = &t->U_1.V_88.TargetStmt;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_44->Pos);
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      Ada_PackBody(W_44->Stmt);
      IO_WriteNl(Tree_f);
      Ada_PackBody(W_44->Next);
      return;
    }
    break;
  case Tree_Nl:;
    {
      register Tree_yNl *W_45 = &t->U_1.V_89.Nl;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_45->Pos);
      IO_WriteS(Tree_f, (STRING)"        yyWriteNl;", 18L);
      IO_WriteNl(Tree_f);
      Ada_PackBody(W_45->Next);
      return;
    }
    break;
  case Tree_WriteStr:;
    {
      register Tree_yWriteStr *W_46 = &t->U_1.V_90.WriteStr;

      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_46->Pos);
      IO_WriteS(Tree_f, (STRING)"        yyWrite (", 17L);
      StringMem_WriteString(Tree_f, W_46->String);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      Ada_PackBody(W_46->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_47 = &t->U_1.V_16.Ident;

      if (W_47->Object != Tree_NoTree) {
        WritePath(W_47->Object->U_1.V_93.Formal.Path);
      } else {
        Tree_WI(W_47->Attribute);
      }
      Ada_PackBody(W_47->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_48 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_48->Code);
      Ada_PackBody(W_48->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_49 = &t->U_1.V_19.Anys;

      Ada_PackBody(W_49->Layouts);
      Ada_PackBody(W_49->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_50 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_50->Code);
      Ada_PackBody(W_50->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_51 = &t->U_1.V_15.Designator;

      WritePath(W_51->Object->U_1.V_93.Formal.Path);
      IO_WriteS(Tree_f, (STRING)". ALL . ", 8L);
      Tree_WI(W_51->Type);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_51->Attribute);
      Ada_PackBody(W_51->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_52 = &t->U_1.V_103.Field;

      Assertions_CantHappen((STRING)"Ada, PackBody, Field", 20L);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_53 = &t->U_1.V_102.ConsType;

      Assertions_CantHappen((STRING)"Ada, PackBody, ConsType", 23L);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_54 = &t->U_1.V_101.Var;

      Assertions_CantHappen((STRING)"Ada, PackBody, Var", 18L);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_55 = &t->U_1.V_98.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"t", 1L);
      Tree_WI(W_55->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_56 = &t->U_1.V_99.UserType;

      Tree_WI(W_56->Type);
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
  struct S_9 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Field:;
    {
      register Tree_yField *W_57 = &t->U_1.V_103.Field;

      WritePathRecurse(W_57->Next);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_57->Name);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_58 = &t->U_1.V_102.ConsType;

      WritePathRecurse(W_58->Next);
      IO_WriteS(Tree_f, (STRING)" . ALL . ", 9L);
      Tree_WI(W_58->Name);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_59 = &t->U_1.V_101.Var;

      Tree_WI(W_59->Name);
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
  struct S_10 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_60 = &t->U_1.V_102.ConsType;

      WritePathRecurse(W_60->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_61 = &t->U_1.V_103.Field;

      WritePathRecurse(t);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_62 = &t->U_1.V_101.Var;

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
  struct S_11 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_63 = &t->U_1.V_93.Formal;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Tree_WI(W_63->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      Ada_PackSpec(W_63->TypeDesc);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Declare(W_63->Next);
      return;
    }
    break;
  case Tree_Param:;
    {
      register struct S_12 *W_64 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yParam *W_65 = &t->U_1.V_38.Param;

        W_64->Var = Semantics_IdentifyVar(Decls, W_65->Name);
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Tree_WI(W_65->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Ada_PackSpec(W_64->Var->U_1.V_93.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        Declare(W_65->Next);
        return;
      }
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_66 = &t->U_1.V_42.Rule;

      if (W_66->HasTempos) {
        Decls = W_66->VarDecls;
        Declare(W_66->Patterns);
        Declare(W_66->Exprs);
        if (RoutineKind == kFunction) {
          Declare(W_66->Expr);
          if (W_66->HasPatterns && W_66->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
            IO_WriteS(Tree_f, (STRING)"      ", 6L);
            Tree_WI(W_66->Tempo);
            IO_WriteS(Tree_f, (STRING)" : ", 3L);
            Ada_PackSpec(ReturnFormals->U_1.V_93.Formal.TypeDesc);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
        }
        Declare(W_66->Statements);
      }
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_67 = &t->U_1.V_83.ProcCall;

      Declare(W_67->Call);
      Declare(W_67->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_68 = &t->U_1.V_84.Condition;

      Declare(W_68->Expr);
      Declare(W_68->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_69 = &t->U_1.V_85.Assignment;

      Declare(W_69->Adr);
      Declare(W_69->Expr);
      Declare(W_69->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_70 = &t->U_1.V_88.TargetStmt;

      Declare(W_70->Parameters);
      Declare(W_70->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_71 = &t->U_1.V_82.Statement;

      Declare(W_71->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_72 = &t->U_1.V_45.OnePattern;

      if (W_72->Pattern->U_1.V_50.Pattern.Tempo != Idents_NoIdent && !Tree_IsType(W_72->Pattern, Tree_DontCare1)) {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Tree_WI(W_72->Pattern->U_1.V_50.Pattern.Tempo);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Ada_PackSpec(W_72->Pattern->U_1.V_50.Pattern.TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_72->Pattern);
      Declare(W_72->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_73 = &t->U_1.V_63.OneExpr;

      Declare(W_73->Expr);
      Declare(W_73->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_74 = &t->U_1.V_51.Decompose;

      Declare(W_74->Patterns);
      return;
    }
    break;
  case Tree_DontCare:;
  case Tree_DontCareExplicit:;
  case Tree_DontCareInternal:;
    {
      register Tree_yDontCare *W_75 = &t->U_1.V_57.DontCare;

      Declare(W_75->Tempos);
      return;
    }
    break;
  case Tree_DontCare1:;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    {
      register Tree_yDontCare1 *W_76 = &t->U_1.V_54.DontCare1;

      if (W_76->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Tree_WI(W_76->Tempo);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Ada_PackSpec(W_76->TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_77 = &t->U_1.V_60.Value;

      Declare(W_77->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_78 = &t->U_1.V_66.Compose;

      if (W_78->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Tree_WI(W_78->Tempo);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Ada_PackSpec(W_78->TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_78->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_79 = &t->U_1.V_70.Call;

      Declare(W_79->Expr);
      Declare(W_79->Exprs);
      Declare(W_79->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
  case Tree_yy1:;
  case Tree_BinaryCompound:;
    {
      register Tree_yBinary *W_80 = &t->U_1.V_71.Binary;

      Declare(W_80->Lop);
      Declare(W_80->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_81 = &t->U_1.V_74.PreOperator;

      Declare(W_81->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_82 = &t->U_1.V_75.PostOperator;

      Declare(W_82->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_83 = &t->U_1.V_77.Parents;

      Declare(W_83->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_84 = &t->U_1.V_76.Index;

      Declare(W_84->Expr);
      Declare(W_84->Exprs);
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
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_85 = &t->U_1.V_93.Formal;

      TheName = W_85->Name;
      Tg1(W_85->TypeDesc);
      Tg1(W_85->Next);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_86 = &t->U_1.V_98.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"    IF ", 7L);
      Tree_WI(TheName);
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Tree_WI(W_86->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . No", 5L);
      Tree_WI(W_86->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" THEN RETURN ", 13L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" FALSE ", 7L);
      }
      IO_WriteS(Tree_f, (STRING)"; END IF ; ", 11L);
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
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_87 = &t->U_1.V_45.OnePattern;

      Tg3(W_87->Pattern);
      Tg3(W_87->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_88 = &t->U_1.V_51.Decompose;

      Tg3(W_88->Patterns);
      IO_WriteS(Tree_f, (STRING)"    END ; -- DECLARE renames ", 29L);
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
  struct S_15 yyTempo;

  if (OneTest == Tree_NoTree) {
    return;
  }
  if (yyP1 == Tree_NoTree) {
    return;
  }
  if (OneTest->U_1.V_1.Kind == Tree_TestValue) {
    for (;;) {
      {
        register Tree_yTestValue *W_89 = &OneTest->U_1.V_111.TestValue;

        if (!Optimize_NeedsMatch(W_89->Expr)) {
          goto EXIT_2;
        }
        CommonTestElim(OneTest);
        IO_WriteS(Tree_f, (STRING)"      LOOP ", 11L);
        IO_WriteNl(Tree_f);
        MatchExpr(OneTest->U_1.V_111.TestValue.Expr);
        CommonTestElim(yyP1);
        IO_WriteS(Tree_f, (STRING)"      EXIT ; ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END LOOP ;", 16L);
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
  struct S_16 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Decision:;
    {
      register Tree_yDecision *W_90 = &t->U_1.V_114.Decision;

      if (W_90->Cases == 0) {
        if (!TemposDone && W_90->OneTest->U_1.V_1.Kind == Tree_TestValue && Optimize_NeedsTempo(W_90->ThenPart, &rule)) {
          IO_WriteS(Tree_f, (STRING)"    DECLARE -- Tempos ", 22L);
          IO_WriteNl(Tree_f);
          Declare(rule);
          IO_WriteS(Tree_f, (STRING)"    BEGIN -- DECLARE Tempos ", 28L);
          IO_WriteNl(Tree_f);
          TemposDone = TRUE;
          CommonTestElim2(W_90->OneTest, W_90->ThenPart);
          IO_WriteS(Tree_f, (STRING)"        END IF ; ", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END ; -- DECLARE Tempos ", 28L);
          IO_WriteNl(Tree_f);
        } else {
          Optimize_GetRule(W_90->ThenPart, &rule);
          Decls = rule->U_1.V_42.Rule.VarDecls;
          CommonTestElim2(W_90->OneTest, W_90->ThenPart);
          IO_WriteS(Tree_f, (STRING)"        END IF ; ", 17L);
          IO_WriteNl(Tree_f);
        }
        TemposDone = FALSE;
        CommonTestElim(W_90->ElsePart);
      } else {
        i = W_90->Cases;
        Case(t);
      }
      return;
    }
    break;
  case Tree_Decided:;
    {
      register Tree_yDecided *W_91 = &t->U_1.V_115.Decided;

      CommonTestElim(W_91->Rule);
      if (W_91->Rule->U_1.V_42.Rule.HasExit) {
        TemposDone = FALSE;
        CommonTestElim(W_91->ElsePart);
      }
      return;
    }
    break;
  case Tree_TestKind:;
    {
      register Tree_yTestKind *W_92 = &t->U_1.V_107.TestKind;

      IO_WriteS(Tree_f, (STRING)"        IF (", 12L);
      WritePath(W_92->Path);
      IO_WriteS(Tree_f, (STRING)". ALL . Kind = ", 15L);
      Tree_WI(W_92->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_92->Name);
      IO_WriteS(Tree_f, (STRING)") THEN", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_93 = &t->U_1.V_108.TestIsType;

      IO_WriteS(Tree_f, (STRING)"        IF ", 11L);
      Tree_WI(W_93->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . IsType ( ", 12L);
      WritePath(W_93->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Tree_WI(W_93->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_93->Name);
      IO_WriteS(Tree_f, (STRING)" ) THEN", 7L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNil:;
    {
      register Tree_yTestNil *W_94 = &t->U_1.V_109.TestNil;

      IO_WriteS(Tree_f, (STRING)"        IF ", 11L);
      WritePath(W_94->Path);
      IO_WriteS(Tree_f, (STRING)" = NULL THEN ", 13L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNonlin:;
    {
      register Tree_yTestNonlin *W_95 = &t->U_1.V_110.TestNonlin;

      IO_WriteS(Tree_f, (STRING)"        IF ( equal", 18L);
      Ada_PackBody(W_95->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      WritePath(W_95->Path);
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
      WritePath(W_95->Path2);
      IO_WriteS(Tree_f, (STRING)" ) ) THEN ", 10L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestValue:;
    {
      register Tree_yTestValue *W_96 = &t->U_1.V_111.TestValue;

      AssignTempo(W_96->Expr);
      IO_WriteS(Tree_f, (STRING)"        IF ( equal", 18L);
      Ada_PackBody(W_96->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      WritePath(W_96->Path);
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
      Expression(W_96->Expr);
      IO_WriteS(Tree_f, (STRING)" ) ) THEN ", 10L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_97 = &t->U_1.V_42.Rule;

      WithCount = 0;
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
      WriteLine(W_97->Line);
      if (W_97->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)"    DECLARE -- Tempos  ", 23L);
        IO_WriteNl(Tree_f);
        Declare(t);
        IO_WriteS(Tree_f, (STRING)"    BEGIN -- DECLARE Tempos  ", 29L);
        IO_WriteNl(Tree_f);
      }
      if (W_97->HasExit) {
        IO_WriteS(Tree_f, (STRING)"       LOOP", 11L);
        IO_WriteNl(Tree_f);
      }
      Decls = W_97->VarDecls;
      if (NeedsDeclareRenames(t)) {
        Tg2(W_97->Patterns, InFormals);
      }
      Ada_PackBody(W_97->Statements);
      if (!W_97->HasRejectOrFail) {
        AssignFormals(W_97->Exprs, OutFormals);
        MatchExprs(W_97->Exprs);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"        RETURN ; ", 17L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          AssignTempo(W_97->Expr);
          if (W_97->HasPatterns && W_97->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
            IO_WriteS(Tree_f, (STRING)"        ", 8L);
            Tree_WI(W_97->Tempo);
            IO_WriteS(Tree_f, (STRING)" := ", 4L);
            Expression(W_97->Expr);
            IO_WriteS(Tree_f, (STRING)" ; ", 3L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_97->Expr);
            IO_WriteS(Tree_f, (STRING)"        RETURN ", 15L);
            Tree_WI(W_97->Tempo);
            IO_WriteS(Tree_f, (STRING)" ; ", 3L);
            IO_WriteNl(Tree_f);
          } else {
            MatchExpr(W_97->Expr);
            IO_WriteS(Tree_f, (STRING)"        RETURN ", 15L);
            Expression(W_97->Expr);
            IO_WriteS(Tree_f, (STRING)" ; ", 3L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"        RETURN TRUE ; ", 22L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (NeedsDeclareRenames(t)) {
        Tg3(W_97->Patterns);
      }
      if (W_97->HasExit) {
        IO_WriteS(Tree_f, (STRING)"     END LOOP ; ", 16L);
        IO_WriteNl(Tree_f);
      }
      if (W_97->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)"    END ; -- DECLARE Tempos  ", 29L);
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
  struct S_17 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Decision:;
    {
      register struct S_18 *W_98 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yDecision *W_99 = &t->U_1.V_114.Decision;

        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        CASE ", 13L);
        WritePath(W_99->OneTest->U_1.V_106.OneTest.Path);
        IO_WriteS(Tree_f, (STRING)" . ALL . Kind IS ", 17L);
        IO_WriteNl(Tree_f);
        W_98->n = i;
        while (W_98->n > 0) {
          if (!Sets_IsEmpty(t->U_1.V_114.Decision.OneTest->U_1.V_108.TestIsType.TypeDesc->U_1.V_98.NodeTypes.Types)) {
            Case(t->U_1.V_114.Decision.OneTest);
            CommonTestElim(t->U_1.V_114.Decision.ThenPart);
          }
          t = t->U_1.V_114.Decision.ElsePart;
          DEC(W_98->n);
        }
        IO_WriteS(Tree_f, (STRING)"        WHEN OTHERS => NULL ; ", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        END CASE ; ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        CommonTestElim(t);
        return;
      }
    }
    break;
  case Tree_TestKind:;
    {
      register Tree_yTestKind *W_100 = &t->U_1.V_107.TestKind;

      IO_WriteS(Tree_f, (STRING)"        WHEN ", 13L);
      Tree_WI(W_100->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_100->Name);
      IO_WriteS(Tree_f, (STRING)" => ", 4L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_101 = &t->U_1.V_108.TestIsType;

      {
        register Tree_yNodeTypes *W_102 = &W_101->TypeDesc->U_1.V_98.NodeTypes;

        TheClass = Semantics_LookupClass(W_102->TreeName->U_1.V_29.TreeName.Classes, Sets_Minimum(&W_102->Types));
        IO_WriteS(Tree_f, (STRING)"        WHEN ", 13L);
        Tree_WI(W_102->TreeName->U_1.V_29.TreeName.Name);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(TheClass->U_1.V_5.Class.Name);
        Case(W_101->TypeDesc);
        IO_WriteS(Tree_f, (STRING)" => ", 4L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_103 = &t->U_1.V_98.NodeTypes;

      {
        LONGCARD B_3 = Sets_Minimum(&W_103->Types) + 1, B_4 = Sets_Maximum(&W_103->Types);

        if (B_3 <= B_4)
          for (j = B_3;; j += 1) {
            if (Sets_IsElement(j, &W_103->Types)) {
              TheClass = Semantics_LookupClass(W_103->TreeName->U_1.V_29.TreeName.Classes, j);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"        | ", 10L);
              Tree_WI(W_103->TreeName->U_1.V_29.TreeName.Name);
              IO_WriteS(Tree_f, (STRING)" . ", 3L);
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

void Ada_BeginAda
# ifdef __STDC__
()
# else
()
# endif
{
}

void Ada_CloseAda
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

void Ada__init()
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
    Strings__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Semantics__init();
    Optimize__init();
    Tree__init();
    Assertions__init();

    Ada_yyf = IO_StdOutput;
    Ada_Exit = yyExit;
    Ada_BeginAda();
  }
}
