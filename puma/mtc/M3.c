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

#ifndef DEFINITION_Errors
#include "Errors.h"
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

#ifndef DEFINITION_Assertions
#include "Assertions.h"
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

#ifndef DEFINITION_IOUtils
#include "IOUtils.h"
#endif

#ifndef DEFINITION_M3
#include "M3.h"
#endif

IO_tFile M3_yyf;
PROC M3_Exit;

#define kProcedure        0
#define kFunction        1
#define kPredicate        2
static unsigned char RoutineKind;
static CARDINAL i, j;
static INTEGER ListCount;
static Tree_tTree rule, TheClass, InFormals, OutFormals, ReturnFormals, Decls;
static Idents_tIdent TheName;
static BOOLEAN TemposDone;
static CARDINAL TypeCaseDepth;
static void WriteLine ARGS((Positions_tPosition Line));
static void WriteString ARGS((IO_tFile f, StringMem_tStringRef r));
static void CloseTypeCases ARGS((CARDINAL ToDepth));
static void Match ARGS((Tree_tTree t, Tree_tTree Formals));
static void MatchExprs ARGS((Tree_tTree t));
static void MatchExpr ARGS((Tree_tTree t));
static void AssignTempos ARGS((Tree_tTree t));
static void AssignTempo ARGS((Tree_tTree t));
static Idents_tIdent MakeWith ARGS((Idents_tIdent Id));
static void WritePrefixIdent ARGS((Idents_tIdent Id));
static void AssignFormals ARGS((Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrefixIdent));
static void AssignFormal ARGS((Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrefixIdent));
static void BeginFormals ARGS((Tree_tTree Formals, Idents_tIdent PrefixIdent));
static INTEGER ConsPatterns ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER ConsTempos ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER Expressions ARGS((Tree_tTree t, INTEGER ListCount));
static void Expression ARGS((Tree_tTree t));
static void OpenWITHRenames ARGS((Tree_tTree t, Tree_tTree Formals));
static void OpenWITHRenamesAttrs ARGS((Tree_tTree AttrFormals));
static void CloseWITHRenames ARGS((Tree_tTree t, Tree_tTree Formals));
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
        struct {
            struct S_7 {
                CARDINAL LTypeCaseDepth;
            } yyR5;
        } V_1;
    } U_1;
};
static void PathPrefix ARGS((Tree_tTree FPath, BOOLEAN IsNarrowed));
struct S_8 {
    union {
        struct {
            struct S_9 {
                BOOLEAN LIsNarrowed;
            } yyR2;
        } V_1;
    } U_1;
};
static void WritePathWide ARGS((Tree_tTree FPath));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void WritePathNarrow ARGS((Tree_tTree FPath));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void Declare ARGS((Tree_tTree t));
struct S_12 {
    union {
        struct {
            struct S_13 {
                Tree_tTree LVar;
            } yyR2;
        } V_1;
    } U_1;
};
static void NilCheck ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim2 ARGS((Tree_tTree OneTest, Tree_tTree yyP1));
struct S_15 {
    union {
        struct {
            struct S_16 {
                CARDINAL LTypeCaseDepth;
            } yyR1;
        } V_1;
    } U_1;
};
static void CommonTestElim ARGS((Tree_tTree t));
struct S_17 {
    union {
        struct {
            struct S_18 {
                CARDINAL LTypeCaseDepth;
                BOOLEAN LGenerateBlock;
            } yyR8;
        } V_1;
    } U_1;
};
static void Case ARGS((Tree_tTree t));
struct S_19 {
    union {
        struct {
            struct S_20 {
                CARDINAL n;
            } yyR1;
        } V_1;
    } U_1;
};
static void yyExit ARGS(());

static Tree_tTree *G_1_LPath;
static CARDINAL *G_2_Count;
static Tree_tTree *G_3_t;

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

static void WriteString
# ifdef __STDC__
(IO_tFile f, StringMem_tStringRef r)
# else
(f, r)
IO_tFile f;
StringMem_tStringRef r;
# endif
{
  Strings_tString LIn;
  CARDINAL LLength, I;
  CHAR LCh;

  StringMem_GetString(r, &LIn);
  LLength = Strings_Length(&LIn);
  if (LLength < 2) {
    Strings_WriteS(f, &LIn);
  } else if (Strings_Char(&LIn, 1) == '"') {
    Strings_WriteS(f, &LIn);
  } else if (Strings_Char(&LIn, 1) == '\'') {
    IO_WriteC(f, '"');
    {
      LONGCARD B_1 = 2, B_2 = LLength - 1;

      if (B_1 <= B_2)
        for (I = B_1;; I += 1) {
          LCh = Strings_Char(&LIn, (Strings_tStringIndex)I);
          if (LCh == '"') {
            IOUtils_WriteBackslash(f);
          }
          IO_WriteC(f, LCh);
          if (I >= B_2) break;
        }
    }
    IO_WriteC(f, '"');
  } else {
    Strings_WriteS(f, &LIn);
  }
}

static void CloseTypeCases
# ifdef __STDC__
(CARDINAL ToDepth)
# else
(ToDepth)
CARDINAL ToDepth;
# endif
{
  while (TypeCaseDepth > ToDepth) {
    IO_WriteS(Tree_f, (STRING)"      ELSE EXIT", 15L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"      END (* TYPECASE Depth ", 28L);
    Tree_WN((LONGINT)TypeCaseDepth);
    IO_WriteS(Tree_f, (STRING)" , CloseTypeCases *)", 20L);
    IO_WriteNl(Tree_f);
    DEC(TypeCaseDepth);
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
      if (Formals->U_1.V_93.Formal.TypeDesc->U_1.V_1.Kind == Tree_UserType || W_1->IsProperlyNarrowed) {
        INC(TypeCaseDepth);
        IO_WriteS(Tree_f, (STRING)"      TYPECASE (* Depth ", 24L);
        Tree_WN((LONGINT)TypeCaseDepth);
        IO_WriteS(Tree_f, (STRING)" , Decompose *) ", 16L);
        WritePathNarrow(W_1->Path);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      OF ", 9L);
        Tree_WI(TreeName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_1->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" ( ", 3L);
        PathPrefix(W_1->Path, TRUE);
        IO_WriteS(Tree_f, (STRING)"_yy_", 4L);
        Tree_WI(W_1->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" ) ", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      => ", 9L);
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
          M3_Module(W_3->TypeDesc);
          IO_WriteS(Tree_f, (STRING)" ( ", 3L);
          WritePathNarrow(W_3->Path);
          IO_WriteS(Tree_f, (STRING)" , ", 3L);
          WritePathNarrow(Pattern->U_1.V_52.VarDef.Path);
          IO_WriteS(Tree_f, (STRING)" ) ) THEN EXIT END (* IF *) ;", 29L);
          IO_WriteNl(Tree_f);
        }
      }
    }
    break;
  case Tree_NilTest:;
    IO_WriteS(Tree_f, (STRING)"      IF ", 9L);
    WritePathWide(Pattern->U_1.V_53.NilTest.Path);
    IO_WriteS(Tree_f, (STRING)" # NIL THEN EXIT END (* IF *) ;", 31L);
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
      M3_Module(Formals->U_1.V_93.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      WritePathNarrow(W_4->Path);
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
      Expression(W_4->Expr);
      IO_WriteS(Tree_f, (STRING)" ) ) THEN EXIT END (* IF *) ;", 29L);
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
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Tree_WI(W_7->Tempo);
      IO_WriteS(Tree_f, (STRING)" := NEW ( ", 10L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_7->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
      IO_WriteNl(Tree_f);
      if (W_7->Exprs->U_1.V_1.Kind == Tree_OneExpr && !Tree_IsType(W_7->Exprs->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
        AssignFormals(W_7->Exprs, W_7->Object->U_1.V_5.Class.Formals, W_7->Tempo);
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

static Idents_tIdent MakeWith
# ifdef __STDC__
(Idents_tIdent Id)
# else
(Id)
Idents_tIdent Id;
# endif
{
  Strings_tString String1, String2;

  Strings_ArrayToString((STRING)"yyWITH_", 7L, &String1);
  Idents_GetString(Id, &String2);
  Strings_Concatenate(&String1, &String2);
  return Idents_MakeIdent(&String1);
}

static void WritePrefixIdent
# ifdef __STDC__
(Idents_tIdent Id)
# else
(Id)
Idents_tIdent Id;
# endif
{
  if (Id != Idents_NoIdent) {
    Tree_WI(Id);
    IO_WriteS(Tree_f, (STRING)" . ", 3L);
  }
}

static void AssignFormals
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrefixIdent)
# else
(t, Formals, PrefixIdent)
Tree_tTree t, Formals;
Idents_tIdent PrefixIdent;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr || !Tree_IsType(Formals, Tree_Formal)) {
    return;
  }
  if (Tree_IsType(t->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
    BeginFormals(Formals, PrefixIdent);
    return;
  }
  AssignFormal(t->U_1.V_63.OneExpr.Expr, Formals, PrefixIdent);
  AssignFormals(t->U_1.V_63.OneExpr.Next, Formals->U_1.V_93.Formal.Next, PrefixIdent);
}

static void AssignFormal
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrefixIdent)
# else
(t, Formals, PrefixIdent)
Tree_tTree t, Formals;
Idents_tIdent PrefixIdent;
# endif
{
  Idents_tIdent TreeName;
  Idents_tIdent LWithTemp;

  if (t->U_1.V_1.Kind == Tree_Compose) {
    {
      register Tree_yCompose *W_10 = &t->U_1.V_66.Compose;

      TreeName = W_10->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      if (W_10->Exprs->U_1.V_1.Kind == Tree_OneExpr && !Tree_IsType(W_10->Exprs->U_1.V_63.OneExpr.Expr, Tree_DontCare)) {
        LWithTemp = MakeWith(Formals->U_1.V_93.Formal.Name);
        IO_WriteS(Tree_f, (STRING)"      WITH ", 11L);
        Tree_WI(LWithTemp);
        IO_WriteS(Tree_f, (STRING)" := NEW ( ", 10L);
        Tree_WI(TreeName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_10->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" ) DO", 5L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Tree_WI(Formals->U_1.V_93.Formal.Name);
        IO_WriteS(Tree_f, (STRING)" := ", 4L);
        Tree_WI(LWithTemp);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        AssignFormals(W_10->Exprs, W_10->Object->U_1.V_5.Class.Formals, LWithTemp);
        IO_WriteS(Tree_f, (STRING)"      END (* WITH *) ;", 22L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Tree_WI(Formals->U_1.V_93.Formal.Name);
        IO_WriteS(Tree_f, (STRING)" := NEW ( ", 10L);
        Tree_WI(TreeName);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_10->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
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
    WritePrefixIdent(PrefixIdent);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" := ", 4L);
    Expression(t);
    IO_WriteS(Tree_f, (STRING)" ;", 2L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    IO_WriteS(Tree_f, (STRING)"      begin", 11L);
    M3_Module(Formals->U_1.V_93.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" ( ", 3L);
    WritePrefixIdent(PrefixIdent);
    Tree_WI(Formals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" ) ", 3L);
    IO_WriteNl(Tree_f);
    break;
  default :
    break;
  }
}

static void BeginFormals
# ifdef __STDC__
(Tree_tTree Formals, Idents_tIdent PrefixIdent)
# else
(Formals, PrefixIdent)
Tree_tTree Formals;
Idents_tIdent PrefixIdent;
# endif
{
  if (Tree_IsType(Formals, Tree_Formal)) {
    {
      register Tree_yFormal *W_11 = &Formals->U_1.V_93.Formal;

      IO_WriteS(Tree_f, (STRING)"      begin", 11L);
      M3_Module(W_11->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      WritePrefixIdent(PrefixIdent);
      Tree_WI(W_11->Name);
      IO_WriteS(Tree_f, (STRING)" )", 2L);
      IO_WriteNl(Tree_f);
      BeginFormals(W_11->Next, PrefixIdent);
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
        IO_WriteS(Tree_f, (STRING)" , ", 3L);
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
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
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
        IO_WriteS(Tree_f, (STRING)" , ", 3L);
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
        WritePathNarrow(W_14->Object->U_1.V_93.Formal.Path);
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
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      ListCount = Expressions(W_15->Exprs, 0L);
      if (W_15->Object != Tree_NoTree) {
        ListCount = ConsPatterns(W_15->Patterns, ListCount);
      } else {
        ListCount = Expressions(W_15->Patterns, ListCount);
      }
      IO_WriteS(Tree_f, (STRING)" )", 2L);
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
    IO_WriteS(Tree_f, (STRING)" [ ", 3L);
    ListCount = Expressions(t->U_1.V_76.Index.Exprs, 0L);
    IO_WriteS(Tree_f, (STRING)" ]", 2L);
    break;
  case Tree_Parents:;
    IO_WriteS(Tree_f, (STRING)"( ", 2L);
    Expression(t->U_1.V_77.Parents.Expr);
    IO_WriteS(Tree_f, (STRING)" )", 2L);
    break;
  case Tree_TargetExpr:;
    M3_Module(t->U_1.V_78.TargetExpr.Expr);
    break;
  case Tree_StringExpr:;
    WriteString(Tree_f, t->U_1.V_79.StringExpr.String);
    break;
  case Tree_AttrDesc:;
    {
      register Tree_yAttrDesc *W_17 = &t->U_1.V_68.AttrDesc;

      PathPrefix(W_17->Object->U_1.V_93.Formal.Path, FALSE);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_17->Attribute);
    }
    break;
  }
}

static void OpenWITHRenamesAttrs
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
    if (*G_2_Count == 0) {
      IO_WriteS(Tree_f, (STRING)"        ", 8L);
    } else {
      IO_WriteS(Tree_f, (STRING)"      , ", 8L);
    }
    INC(*G_2_Count);
    Tree_WI(AttrFormals->U_1.V_93.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" = ", 3L);
    PathPrefix(*G_1_LPath, FALSE);
    IO_WriteS(Tree_f, (STRING)"_yy_", 4L);
    Tree_WI((*G_3_t)->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Object->U_1.V_5.Class.Name);
    IO_WriteS(Tree_f, (STRING)" . ", 3L);
    Tree_WI(AttrFormals->U_1.V_93.Formal.Name);
    IO_WriteNl(Tree_f);
    OpenWITHRenamesAttrs(AttrFormals->U_1.V_93.Formal.Next);
  }
}

static void OpenWITHRenames
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Tree_tTree Object, LSubFormals, LPath;
  CARDINAL Count;
  Idents_tIdent FormalName;
  Tree_tTree *L_1;
  CARDINAL *L_2;
  Tree_tTree *L_3;

  L_1 = G_1_LPath;
  G_1_LPath = &LPath;
  L_2 = G_2_Count;
  G_2_Count = &Count;
  L_3 = G_3_t;
  G_3_t = &t;
  if (t->U_1.V_1.Kind == Tree_NoPattern || Formals->U_1.V_1.Kind == Tree_NoFormal) {
    G_1_LPath = L_1;
    G_2_Count = L_2;
    G_3_t = L_3;
    return;
  }
  switch (t->U_1.V_45.OnePattern.Pattern->U_1.V_1.Kind) {
  case Tree_Decompose:;
    Object = t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Object;
    if (Object != Tree_NoTree) {
      LSubFormals = Object->U_1.V_5.Class.Formals;
      if (Tree_IsType(LSubFormals, Tree_Formal)) {
        IO_WriteS(Tree_f, (STRING)"    WITH (* Renames *) ", 23L);
        IO_WriteNl(Tree_f);
        LPath = t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Path;
        Count = 0;
        OpenWITHRenamesAttrs(LSubFormals);
        IO_WriteS(Tree_f, (STRING)"    DO (* Renames *) ", 21L);
        IO_WriteNl(Tree_f);
        OpenWITHRenames(t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Patterns, LSubFormals);
      }
    }
    break;
  case Tree_VarDef:;
  case Tree_NilTest:;
  case Tree_Value:;
  case Tree_DontCare1Explicit:;
  case Tree_DontCare1Internal:;
    break;
  default :
    G_1_LPath = L_1;
    G_2_Count = L_2;
    G_3_t = L_3;
    return;
    break;
  }
  OpenWITHRenames(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_93.Formal.Next);
  G_1_LPath = L_1;
  G_2_Count = L_2;
  G_3_t = L_3;
}

static void CloseWITHRenames
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Tree_tTree Object, LSubFormals;

  if (t->U_1.V_1.Kind == Tree_NoPattern || Formals->U_1.V_1.Kind == Tree_NoFormal) {
    return;
  }
  switch (t->U_1.V_45.OnePattern.Pattern->U_1.V_1.Kind) {
  case Tree_Decompose:;
    Object = t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Object;
    if (Object != Tree_NoTree) {
      LSubFormals = Object->U_1.V_5.Class.Formals;
      if (Tree_IsType(LSubFormals, Tree_Formal)) {
        CloseWITHRenames(t->U_1.V_45.OnePattern.Pattern->U_1.V_51.Decompose.Patterns, LSubFormals);
        IO_WriteS(Tree_f, (STRING)"    END (* WITH Renames *) ", 27L);
        IO_WriteNl(Tree_f);
      }
    }
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
  CloseWITHRenames(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_93.Formal.Next);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module M3, routine ", 26L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*M3_Exit)();
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

void M3_MacroM3
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

      M3_MacroM3(W_18->TreeNames);
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
      M3_MacroM3(W_19->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void M3_Interface
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
      IO_WriteS(Tree_f, (STRING)"(* This interface file was mechanically generated by puma. *)", 61L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"INTERFACE ", 10L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT Wr ", 10L);
      M3_Interface(W_20->TreeNames);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_20->Codes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_20->Codes->U_1.V_12.Codes.Import);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_20->Codes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_20->Codes->U_1.V_12.Codes.Export);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyf        : Wr . T ;", 25L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR Exit       : PROCEDURE ( ) ;", 32L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M3_Interface(W_20->Public);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)" .", 2L);
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
      M3_Interface(W_21->Next);
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
        M3_Interface(W_22->Object->U_1.V_32.Routine.InForm);
        M3_Interface(W_22->Object->U_1.V_32.Routine.OutForm);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        if (W_22->Object->U_1.V_1.Kind == Tree_Predicate) {
          IO_WriteS(Tree_f, (STRING)": BOOLEAN", 9L);
        } else if (W_22->Object->U_1.V_1.Kind == Tree_Function) {
          IO_WriteS(Tree_f, (STRING)": ", 2L);
          M3_Interface(W_22->Object->U_1.V_34.Function.ReturnForm->U_1.V_93.Formal.TypeDesc);
        }
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      M3_Interface(W_22->Next);
      return;
    }
    break;
  case Tree_RoutineFormal:;
    if (t->U_1.V_95.RoutineFormal.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
      if (t->U_1.V_95.RoutineFormal.TargetClass->U_1.V_1.Kind == Tree_Class) {
        if (t->U_1.V_95.RoutineFormal.TargetClass->U_1.V_5.Class.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
          {
            register Tree_yRoutineFormal *W_23 = &t->U_1.V_95.RoutineFormal;

            {
              register Tree_yNodeTypes *W_24 = &W_23->TypeDesc->U_1.V_98.NodeTypes;

              {
                register Tree_yTreeName *W_25 = &W_24->TreeName->U_1.V_29.TreeName;

                {
                  register Tree_yClass *W_26 = &W_23->TargetClass->U_1.V_5.Class;

                  {
                    register Tree_yNodeTypes *W_27 = &W_26->TypeDesc->U_1.V_98.NodeTypes;

                    if (ListCount > 0) {
                      IO_WriteS(Tree_f, (STRING)"; ", 2L);
                    }
                    if (W_23->Path->U_1.V_101.Var.IsOutput) {
                      IO_WriteS(Tree_f, (STRING)"VAR ", 4L);
                    }
                    Tree_WI(t->U_1.V_95.RoutineFormal.Name);
                    IO_WriteS(Tree_f, (STRING)" : ", 3L);
                    Tree_WI(t->U_1.V_95.RoutineFormal.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
                    IO_WriteS(Tree_f, (STRING)" . ", 3L);
                    IO_WriteNl(Tree_f);
                    Tree_WI(W_23->TargetClass->U_1.V_5.Class.Name);
                    INC(ListCount);
                    M3_Interface(t->U_1.V_95.RoutineFormal.Next);
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
    break;
  default :
    break;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_28 = &t->U_1.V_93.Formal;

      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
      }
      if (W_28->Path->U_1.V_101.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)"VAR ", 4L);
      }
      Tree_WI(W_28->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      M3_Interface(W_28->TypeDesc);
      INC(ListCount);
      M3_Interface(W_28->Next);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_29 = &t->U_1.V_98.NodeTypes;

      Tree_WI(W_29->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" .t", 3L);
      Tree_WI(W_29->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_30 = &t->U_1.V_99.UserType;

      Tree_WI(W_30->Type);
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
      register Tree_yRule *W_31 = &t->U_1.V_42.Rule;

      if (!Sets_IsElement(ORD('w'), &Tree_Options)) {
        goto EXIT_1;
      }
      if (!(W_31->Statements->U_1.V_1.Kind != Tree_NoStatement || W_31->Exprs->U_1.V_1.Kind != Tree_NoExpr || W_31->Expr->U_1.V_1.Kind != Tree_NoExpr)) {
        goto EXIT_1;
      }
      return TRUE;
    }
  } EXIT_1:;
  return FALSE;
}

void M3_Module
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
      register Tree_ySpec *W_32 = &t->U_1.V_26.Spec;

      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"(* This module file was mechanically generated by puma. *)", 58L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"MODULE ", 7L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT Wr , Stdio , Process ", 28L);
      M3_Interface(W_32->TreeNames);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWrite(s) Wr.PutText (yyf, s)", 39L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWriteNl Wr.PutText(yyf,Wr.EOL)", 41L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_32->Codes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_32->Codes->U_1.V_12.Codes.Global);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyAbort ( yyFunction : TEXT )", 39L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"= BEGIN", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Wr . PutText ", 17L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      (Stdio . stderr, \"Error: module ", 38L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)", routine \" ) ;", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Wr . PutText (Stdio . stderr, yyFunction);", 46L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Wr . PutText (Stdio . stderr, \" failed\" ) ;", 47L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Wr . PutText (Stdio . stderr , Wr . EOL ) ;", 47L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    Exit ( ) ", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"   END yyAbort ;", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M3_Module(W_32->Routines);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ( )", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_32->Codes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_32->Codes->U_1.V_12.Codes.Begin);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END Begin", 10L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)"( )", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_32->Codes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_32->Codes->U_1.V_12.Codes.Close);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END Close", 10L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyExit ( )", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"   Process . Exit ( 1 ) ;", 25L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyExit ;", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" yyf   := Stdio . stdout ;", 26L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" Exit  := yyExit;", 17L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" Begin", 6L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ( ) ;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_32->TrafoName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      TypeCaseDepth = 0;
      return;
    }
    break;
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_33 = &t->U_1.V_33.Procedure;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_33->Name);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      M3_Interface(W_33->InForm);
      M3_Interface(W_33->OutForm);
      IO_WriteS(Tree_f, (STRING)" ) =", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_33->LocalLine);
      Texts_WriteText(Tree_f, W_33->Local);
      IO_WriteNl(Tree_f);
      RoutineKind = kProcedure;
      InFormals = W_33->InForm;
      OutFormals = W_33->OutForm;
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        NilCheck(W_33->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        M3_Module(W_33->Rules);
        if (Sets_IsElement(ORD('f'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ( \"", 13L);
          Tree_WI(W_33->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
          IO_WriteNl(Tree_f);
        }
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_33->Decisions);
        if (Sets_IsElement(ORD('f'), &Tree_Options) && !Optimize_NeedsNoFinale(W_33->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ( \"", 13L);
          Tree_WI(W_33->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_33->Name);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M3_Module(W_33->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_34 = &t->U_1.V_34.Function;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_34->Name);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      M3_Interface(W_34->InForm);
      M3_Interface(W_34->OutForm);
      IO_WriteS(Tree_f, (STRING)" ) : ", 5L);
      M3_Interface(W_34->ReturnForm->U_1.V_93.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)"=", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_34->LocalLine);
      Texts_WriteText(Tree_f, W_34->Local);
      IO_WriteNl(Tree_f);
      RoutineKind = kFunction;
      InFormals = W_34->InForm;
      OutFormals = W_34->OutForm;
      ReturnFormals = W_34->ReturnForm;
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        M3_Module(W_34->Rules);
        IO_WriteS(Tree_f, (STRING)"  yyAbort ( \"", 13L);
        Tree_WI(W_34->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_34->Decisions);
        if (!Optimize_NeedsNoFinale(W_34->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort (\" ", 13L);
          Tree_WI(W_34->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ;", 5L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_34->Name);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M3_Module(W_34->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_35 = &t->U_1.V_35.Predicate;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_35->Name);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      M3_Interface(W_35->InForm);
      M3_Interface(W_35->OutForm);
      IO_WriteS(Tree_f, (STRING)" ) : BOOLEAN = ", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      WriteLine(W_35->LocalLine);
      Texts_WriteText(Tree_f, W_35->Local);
      IO_WriteNl(Tree_f);
      RoutineKind = kPredicate;
      InFormals = W_35->InForm;
      OutFormals = W_35->OutForm;
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        NilCheck(W_35->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        M3_Module(W_35->Rules);
        IO_WriteS(Tree_f, (STRING)"  RETURN FALSE;", 15L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_35->Decisions);
        if (!Optimize_NeedsNoFinale(W_35->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  RETURN FALSE;", 15L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_35->Name);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      M3_Module(W_35->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register struct S_7 *W_36 = &yyTempo.U_1.V_1.yyR5;

      {
        register Tree_yRule *W_37 = &t->U_1.V_42.Rule;

        IO_WriteS(Tree_f, (STRING)"    ", 4L);
        WriteLine(W_37->Line);
        if (W_37->HasTempos) {
          IO_WriteS(Tree_f, (STRING)"    (* Tempo declarations, Module: *)", 37L);
          IO_WriteNl(Tree_f);
          Declare(t);
          IO_WriteS(Tree_f, (STRING)"    BEGIN (* Block of Tempo declarations, Module *)", 51L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
        IO_WriteNl(Tree_f);
        Decls = W_37->VarDecls;
        W_36->LTypeCaseDepth = TypeCaseDepth;
        Match(W_37->Patterns, InFormals);
        if (NeedsWITHStmt(t)) {
          OpenWITHRenames(W_37->Patterns, InFormals);
        }
        M3_Module(W_37->Statements);
        if (!W_37->HasRejectOrFail) {
          AssignFormals(W_37->Exprs, OutFormals, Idents_NoIdent);
          MatchExprs(W_37->Exprs);
          switch (RoutineKind) {
          case kProcedure:;
            IO_WriteS(Tree_f, (STRING)"      RETURN;", 13L);
            IO_WriteNl(Tree_f);
            break;
          case kFunction:;
            AssignTempo(W_37->Expr);
            if (W_37->HasPatterns && W_37->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
              IO_WriteS(Tree_f, (STRING)"      ", 6L);
              Tree_WI(W_37->Tempo);
              IO_WriteS(Tree_f, (STRING)" := ", 4L);
              Expression(W_37->Expr);
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
              MatchExpr(W_37->Expr);
              IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
              Tree_WI(W_37->Tempo);
              IO_WriteS(Tree_f, (STRING)";", 1L);
              IO_WriteNl(Tree_f);
            } else {
              MatchExpr(W_37->Expr);
              IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
              Expression(W_37->Expr);
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
        CloseTypeCases(W_36->LTypeCaseDepth);
        if (NeedsWITHStmt(t)) {
          CloseWITHRenames(W_37->Patterns, InFormals);
        }
        IO_WriteS(Tree_f, (STRING)"   END (* LOOP *) ;", 19L);
        IO_WriteNl(Tree_f);
        if (W_37->HasTempos) {
          IO_WriteS(Tree_f, (STRING)"    END (* Block of Tempo declarations, Module *) ;", 51L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteNl(Tree_f);
        M3_Module(W_37->Next);
        return;
      }
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_38 = &t->U_1.V_83.ProcCall;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_38->Pos);
      AssignTempo(W_38->Call);
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Expression(W_38->Call);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_38->Call);
      M3_Module(W_38->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_39 = &t->U_1.V_84.Condition;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_39->Pos);
      AssignTempo(W_39->Expr);
      IO_WriteS(Tree_f, (STRING)"      IF NOT ( ", 15L);
      Expression(W_39->Expr);
      IO_WriteS(Tree_f, (STRING)" ) THEN EXIT END (* IF *) ;", 27L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_39->Expr);
      M3_Module(W_39->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_40 = &t->U_1.V_85.Assignment;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_40->Pos);
      AssignTempo(W_40->Adr);
      AssignTempo(W_40->Expr);
      if (W_40->Object != Tree_NoTree) {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        WritePathWide(W_40->Object->U_1.V_93.Formal.Path);
      } else {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Expression(W_40->Adr);
      }
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Expression(W_40->Expr);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_40->Adr);
      MatchExpr(W_40->Expr);
      M3_Module(W_40->Next);
      return;
    }
    break;
  case Tree_Reject:;
    {
      register Tree_yReject *W_41 = &t->U_1.V_86.Reject;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_41->Pos);
      IO_WriteS(Tree_f, (STRING)"      EXIT;", 11L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Fail:;
    {
      register Tree_yFail *W_42 = &t->U_1.V_87.Fail;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_42->Pos);
      IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)"FALSE ", 6L);
      }
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_43 = &t->U_1.V_88.TargetStmt;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_43->Pos);
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      M3_Module(W_43->Stmt);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      M3_Module(W_43->Next);
      return;
    }
    break;
  case Tree_Nl:;
    {
      register Tree_yNl *W_44 = &t->U_1.V_89.Nl;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_44->Pos);
      IO_WriteS(Tree_f, (STRING)"      yyWriteNl;", 16L);
      IO_WriteNl(Tree_f);
      M3_Module(W_44->Next);
      return;
    }
    break;
  case Tree_WriteStr:;
    {
      register Tree_yWriteStr *W_45 = &t->U_1.V_90.WriteStr;

      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      WriteLine(W_45->Pos);
      IO_WriteS(Tree_f, (STRING)"      yyWrite ( ", 16L);
      WriteString(Tree_f, W_45->String);
      IO_WriteS(Tree_f, (STRING)" ) ;", 4L);
      IO_WriteNl(Tree_f);
      M3_Module(W_45->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_46 = &t->U_1.V_16.Ident;

      if (W_46->Object != Tree_NoTree) {
        WritePathNarrow(W_46->Object->U_1.V_93.Formal.Path);
      } else {
        Tree_WI(W_46->Attribute);
      }
      M3_Module(W_46->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_47 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_47->Code);
      M3_Module(W_47->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_48 = &t->U_1.V_19.Anys;

      M3_Module(W_48->Layouts);
      M3_Module(W_48->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_49 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_49->Code);
      M3_Module(W_49->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_50 = &t->U_1.V_15.Designator;

      PathPrefix(W_50->Object->U_1.V_93.Formal.Path, FALSE);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_50->Attribute);
      M3_Module(W_50->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_51 = &t->U_1.V_103.Field;

      Assertions_CantHappen((STRING)"Module called on Field", 22L);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_52 = &t->U_1.V_102.ConsType;

      Assertions_CantHappen((STRING)"Module called on ConsType", 25L);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_53 = &t->U_1.V_101.Var;

      Assertions_CantHappen((STRING)"Module called on Var", 20L);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_54 = &t->U_1.V_98.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"t", 1L);
      Tree_WI(W_54->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_55 = &t->U_1.V_99.UserType;

      Tree_WI(W_55->Type);
      return;
    }
    break;
  default :
    break;
  }
}

static void PathPrefix
# ifdef __STDC__
(Tree_tTree FPath, BOOLEAN IsNarrowed)
# else
(FPath, IsNarrowed)
Tree_tTree FPath;
BOOLEAN IsNarrowed;
# endif
{
  struct S_8 yyTempo;

  if (FPath == Tree_NoTree) {
    return;
  }
  switch (FPath->U_1.V_1.Kind) {
  case Tree_Field:;
    {
      register Tree_yField *W_56 = &FPath->U_1.V_103.Field;

      PathPrefix(W_56->Next, IsNarrowed);
      if (IsNarrowed) {
        IO_WriteS(Tree_f, (STRING)"_y_", 3L);
      } else {
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
      }
      Tree_WI(W_56->Name);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register struct S_9 *W_57 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yConsType *W_58 = &FPath->U_1.V_102.ConsType;

        W_57->LIsNarrowed = IsNarrowed || W_58->IsProperlyNarrowed;
        PathPrefix(W_58->Next, W_57->LIsNarrowed);
        if (W_57->LIsNarrowed) {
          IO_WriteS(Tree_f, (STRING)"_yy_", 4L);
          Tree_WI(W_58->Name);
        }
        return;
      }
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_59 = &FPath->U_1.V_101.Var;

      Tree_WI(W_59->Name);
      return;
    }
    break;
  default :
    break;
  }
  Assertions_CantHappen((STRING)"PathPrefix, bad node kind", 25L);
  return;
}

static void WritePathWide
# ifdef __STDC__
(Tree_tTree FPath)
# else
(FPath)
Tree_tTree FPath;
# endif
{
  struct S_10 yyTempo;

  if (FPath == Tree_NoTree) {
    return;
  }
  switch (FPath->U_1.V_1.Kind) {
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_60 = &FPath->U_1.V_102.ConsType;

      WritePathWide(W_60->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_61 = &FPath->U_1.V_103.Field;

      PathPrefix(W_61->Next, FALSE);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_61->Name);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_62 = &FPath->U_1.V_101.Var;

      Tree_WI(W_62->Name);
      return;
    }
    break;
  default :
    break;
  }
}

static void WritePathNarrow
# ifdef __STDC__
(Tree_tTree FPath)
# else
(FPath)
Tree_tTree FPath;
# endif
{
  struct S_11 yyTempo;

  if (FPath == Tree_NoTree) {
    return;
  }
  PathPrefix(FPath, FALSE);
  return;
}

static void Declare
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
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_63 = &t->U_1.V_93.Formal;

      IO_WriteS(Tree_f, (STRING)"       VAR ", 11L);
      Tree_WI(W_63->Name);
      IO_WriteS(Tree_f, (STRING)" : ", 3L);
      M3_Interface(W_63->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ;", 2L);
      IO_WriteNl(Tree_f);
      Declare(W_63->Next);
      return;
    }
    break;
  case Tree_Param:;
    {
      register struct S_13 *W_64 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yParam *W_65 = &t->U_1.V_38.Param;

        W_64->LVar = Semantics_IdentifyVar(Decls, W_65->Name);
        IO_WriteS(Tree_f, (STRING)"       VAR ", 11L);
        Tree_WI(W_65->Name);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        M3_Interface(W_64->LVar->U_1.V_93.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
            IO_WriteS(Tree_f, (STRING)"       VAR ", 11L);
            Tree_WI(W_66->Tempo);
            IO_WriteS(Tree_f, (STRING)" : ", 3L);
            M3_Interface(ReturnFormals->U_1.V_93.Formal.TypeDesc);
            IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
        IO_WriteS(Tree_f, (STRING)"       VAR ", 11L);
        Tree_WI(W_72->Pattern->U_1.V_50.Pattern.Tempo);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        M3_Interface(W_72->Pattern->U_1.V_50.Pattern.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
        IO_WriteS(Tree_f, (STRING)"       VAR ", 11L);
        Tree_WI(W_76->Tempo);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        M3_Interface(W_76->TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
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
        IO_WriteS(Tree_f, (STRING)"       VAR ", 11L);
        Tree_WI(W_78->Tempo);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Tree_WI(W_78->Object->U_1.V_5.Class.TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        IO_WriteNl(Tree_f);
        Tree_WI(W_78->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
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

static void NilCheck
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
  case Tree_Formal:;
  case Tree_PlainFormal:;
  case Tree_RoutineFormal:;
    {
      register Tree_yFormal *W_85 = &t->U_1.V_93.Formal;

      TheName = W_85->Name;
      NilCheck(W_85->TypeDesc);
      NilCheck(W_85->Next);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_86 = &t->U_1.V_98.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      Tree_WI(TheName);
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Tree_WI(W_86->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . No", 5L);
      Tree_WI(W_86->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" THEN RETURN ", 13L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)"FALSE ", 6L);
      }
      IO_WriteS(Tree_f, (STRING)" ; END (* IF *) ;", 17L);
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
    {
      register struct S_16 *W_87 = &yyTempo.U_1.V_1.yyR1;

      for (;;) {
        {
          register Tree_yTestValue *W_88 = &OneTest->U_1.V_111.TestValue;

          if (!Optimize_NeedsMatch(W_88->Expr)) {
            goto EXIT_2;
          }
          CommonTestElim(OneTest);
          IO_WriteS(Tree_f, (STRING)"    LOOP", 8L);
          IO_WriteNl(Tree_f);
          W_87->LTypeCaseDepth = TypeCaseDepth;
          MatchExpr(OneTest->U_1.V_111.TestValue.Expr);
          CommonTestElim(yyP1);
          CloseTypeCases(W_87->LTypeCaseDepth);
          IO_WriteS(Tree_f, (STRING)"    EXIT; END (* LOOP *) ; ", 27L);
          IO_WriteNl(Tree_f);
          return;
        }
      } EXIT_2:;
    }
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
  struct S_17 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Decision:;
    {
      register Tree_yDecision *W_89 = &t->U_1.V_114.Decision;

      if (W_89->Cases == 0) {
        if (!TemposDone && W_89->OneTest->U_1.V_1.Kind == Tree_TestValue && Optimize_NeedsTempo(W_89->ThenPart, &rule)) {
          IO_WriteS(Tree_f, (STRING)"    (* Tempo declarations, Decision: *)", 39L);
          IO_WriteNl(Tree_f);
          Declare(rule);
          IO_WriteS(Tree_f, (STRING)"    BEGIN (* Block of Tempo declarations, Decision *)", 53L);
          IO_WriteNl(Tree_f);
          TemposDone = TRUE;
          CommonTestElim2(W_89->OneTest, W_89->ThenPart);
          IO_WriteS(Tree_f, (STRING)"      ELSE", 10L);
          IO_WriteS(Tree_f, (STRING)"      END (* Test... *) ;", 25L);
          IO_WriteNl(Tree_f);
          DEC(TypeCaseDepth);
          IO_WriteS(Tree_f, (STRING)"    END (* Block of Tempo declarations, Decision *) ; ", 54L);
          IO_WriteNl(Tree_f);
        } else {
          Optimize_GetRule(W_89->ThenPart, &rule);
          Decls = rule->U_1.V_42.Rule.VarDecls;
          CommonTestElim2(W_89->OneTest, W_89->ThenPart);
          IO_WriteS(Tree_f, (STRING)"      ELSE", 10L);
          IO_WriteS(Tree_f, (STRING)"      END (* Test... *) ;", 25L);
          IO_WriteNl(Tree_f);
          DEC(TypeCaseDepth);
        }
        TemposDone = FALSE;
        CommonTestElim(W_89->ElsePart);
      } else {
        i = W_89->Cases;
        Case(t);
      }
      return;
    }
    break;
  case Tree_Decided:;
    {
      register Tree_yDecided *W_90 = &t->U_1.V_115.Decided;

      CommonTestElim(W_90->Rule);
      if (W_90->Rule->U_1.V_42.Rule.HasExit) {
        TemposDone = FALSE;
        CommonTestElim(W_90->ElsePart);
      }
      return;
    }
    break;
  case Tree_TestKind:;
    {
      register Tree_yTestKind *W_91 = &t->U_1.V_107.TestKind;

      IO_WriteS(Tree_f, (STRING)"      TYPECASE (* TestKind *) ", 30L);
      WritePathNarrow(W_91->Path);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      OF ", 9L);
      Tree_WI(W_91->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_91->Name);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      PathPrefix(W_91->Path, TRUE);
      IO_WriteS(Tree_f, (STRING)"_yy_", 4L);
      Tree_WI(W_91->Name);
      IO_WriteS(Tree_f, (STRING)" ) ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      => ", 9L);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_92 = &t->U_1.V_108.TestIsType;

      IO_WriteS(Tree_f, (STRING)"      TYPECASE (* TestIsType *) ", 32L);
      WritePathNarrow(W_92->Path);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      OF ", 9L);
      Tree_WI(W_92->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_92->Name);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      PathPrefix(W_92->Path, TRUE);
      IO_WriteS(Tree_f, (STRING)"_yy_", 4L);
      Tree_WI(W_92->Name);
      IO_WriteS(Tree_f, (STRING)" ) ", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"      => ", 9L);
      return;
    }
    break;
  case Tree_TestNil:;
    {
      register Tree_yTestNil *W_93 = &t->U_1.V_109.TestNil;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      WritePathWide(W_93->Path);
      IO_WriteS(Tree_f, (STRING)" = NIL (* TestNil *) THEN", 25L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNonlin:;
    {
      register Tree_yTestNonlin *W_94 = &t->U_1.V_110.TestNonlin;

      IO_WriteS(Tree_f, (STRING)"  IF (equal", 11L);
      M3_Module(W_94->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      WritePathNarrow(W_94->Path);
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
      WritePathNarrow(W_94->Path2);
      IO_WriteS(Tree_f, (STRING)" ) ) (* TestNonlin *) THEN", 26L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestValue:;
    {
      register Tree_yTestValue *W_95 = &t->U_1.V_111.TestValue;

      AssignTempo(W_95->Expr);
      IO_WriteS(Tree_f, (STRING)"  IF (equal", 11L);
      M3_Module(W_95->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      WritePathNarrow(W_95->Path);
      IO_WriteS(Tree_f, (STRING)" , ", 3L);
      Expression(W_95->Expr);
      IO_WriteS(Tree_f, (STRING)" ) ) (* TestValue *) THEN", 25L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register struct S_18 *W_96 = &yyTempo.U_1.V_1.yyR8;

      {
        register Tree_yRule *W_97 = &t->U_1.V_42.Rule;

        IO_WriteS(Tree_f, (STRING)"    ", 4L);
        WriteLine(W_97->Line);
        W_96->LGenerateBlock = W_97->HasTempos && !TemposDone;
        if (W_96->LGenerateBlock) {
          IO_WriteS(Tree_f, (STRING)"    (* Tempo declarations, CommonTestElim: *)", 45L);
          IO_WriteNl(Tree_f);
          Declare(t);
          IO_WriteS(Tree_f, (STRING)"    BEGIN (* Block of Tempo declarations, CommonTestElim *)", 59L);
          IO_WriteNl(Tree_f);
        }
        if (W_97->HasExit) {
          IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
          IO_WriteNl(Tree_f);
        }
        Decls = W_97->VarDecls;
        if (NeedsWITHStmt(t)) {
          OpenWITHRenames(W_97->Patterns, InFormals);
        }
        W_96->LTypeCaseDepth = TypeCaseDepth;
        M3_Module(W_97->Statements);
        if (!W_97->HasRejectOrFail) {
          AssignFormals(W_97->Exprs, OutFormals, Idents_NoIdent);
          MatchExprs(W_97->Exprs);
          switch (RoutineKind) {
          case kProcedure:;
            IO_WriteS(Tree_f, (STRING)"      RETURN ;", 14L);
            IO_WriteNl(Tree_f);
            break;
          case kFunction:;
            AssignTempo(W_97->Expr);
            if (W_97->HasPatterns && W_97->Expr->U_1.V_1.Kind != Tree_Compose && !Tree_IsType(t, Tree_DontCare1)) {
              IO_WriteS(Tree_f, (STRING)"      ", 6L);
              Tree_WI(W_97->Tempo);
              IO_WriteS(Tree_f, (STRING)" := ", 4L);
              Expression(W_97->Expr);
              IO_WriteS(Tree_f, (STRING)" ;", 2L);
              IO_WriteNl(Tree_f);
              MatchExpr(W_97->Expr);
              IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
              Tree_WI(W_97->Tempo);
              IO_WriteS(Tree_f, (STRING)" ;", 2L);
              IO_WriteNl(Tree_f);
            } else {
              MatchExpr(W_97->Expr);
              IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
              Expression(W_97->Expr);
              IO_WriteS(Tree_f, (STRING)" ;", 2L);
              IO_WriteNl(Tree_f);
            }
            break;
          case kPredicate:;
            IO_WriteS(Tree_f, (STRING)"      RETURN TRUE ;", 19L);
            IO_WriteNl(Tree_f);
            break;
          }
        }
        CloseTypeCases(W_96->LTypeCaseDepth);
        if (NeedsWITHStmt(t)) {
          CloseWITHRenames(W_97->Patterns, InFormals);
        }
        if (W_97->HasExit) {
          IO_WriteS(Tree_f, (STRING)"   END (* LOOP *) ;", 19L);
          IO_WriteNl(Tree_f);
        }
        if (W_96->LGenerateBlock) {
          IO_WriteS(Tree_f, (STRING)"    END (* Block of Tempo declarations, CommonTestElim *) ;  ", 61L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteNl(Tree_f);
        return;
      }
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
  struct S_19 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Decision:;
    {
      register struct S_20 *W_98 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yDecision *W_99 = &t->U_1.V_114.Decision;

        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  TYPECASE (* Decision *) ", 26L);
        WritePathNarrow(W_99->OneTest->U_1.V_106.OneTest.Path);
        IO_WriteS(Tree_f, (STRING)" OF", 3L);
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
        IO_WriteS(Tree_f, (STRING)"  ELSE", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END (* TYPECASE Decision *) ;", 31L);
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

      IO_WriteS(Tree_f, (STRING)"  | ", 4L);
      Tree_WI(W_100->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_100->Name);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      PathPrefix(W_100->Path, TRUE);
      IO_WriteS(Tree_f, (STRING)"_yy_", 4L);
      Tree_WI(W_100->Name);
      IO_WriteS(Tree_f, (STRING)" ) => ", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_101 = &t->U_1.V_108.TestIsType;

      IO_WriteS(Tree_f, (STRING)"  | ", 4L);
      Tree_WI(W_101->TypeDesc->U_1.V_98.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" . ", 3L);
      Tree_WI(W_101->Name);
      IO_WriteS(Tree_f, (STRING)" ( ", 3L);
      PathPrefix(W_101->Path, TRUE);
      IO_WriteS(Tree_f, (STRING)"_yy_", 4L);
      Tree_WI(W_101->Name);
      IO_WriteS(Tree_f, (STRING)" ) => ", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  default :
    break;
  }
}

void M3_BeginM3
# ifdef __STDC__
()
# else
()
# endif
{
}

void M3_CloseM3
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

void M3__init()
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
    Errors__init();
    Positions__init();
    IO__init();
    StringMem__init();
    Strings__init();
    Assertions__init();
    Strings__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Semantics__init();
    Optimize__init();
    Tree__init();
    IOUtils__init();

    M3_yyf = IO_StdOutput;
    M3_Exit = yyExit;
    M3_BeginM3();
  }
}
