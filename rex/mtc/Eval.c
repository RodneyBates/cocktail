#include "SYSTEM_.h"

#ifndef DEFINITION_Tree0
#include "Tree0.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Classes
#include "Classes.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Eval
#include "Eval.h"
#endif


static Strings_tString String1, String2;
static Sets_tSet Set1, Set2;
static CARDINAL i, j;
static BOOLEAN yyb;
static void yyVisit1 ARGS((Tree0_tTree0 yyt));


void Eval_Eval
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  yyVisit1(yyt);
}

static void yyVisit1
# ifdef __STDC__
(Tree0_tTree0 yyt)
# else
(yyt)
Tree0_tTree0 yyt;
# endif
{
  switch (yyt->U_1.V_1.Kind) {
  case Tree0_Node:;
    yyt->U_1.V_3.Node.NodeCount = 0;
    yyt->U_1.V_3.Node.LeafCount = 0;
    yyt->U_1.V_3.Node.IsConstantRE = TRUE;
    yyt->U_1.V_3.Node.Tree = Tree_NoTree;
    break;
  case Tree0_Node1:;
    yyVisit1(yyt->U_1.V_4.Node1.Son1);
    yyt->U_1.V_4.Node1.NodeCount = yyt->U_1.V_4.Node1.Son1->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_4.Node1.LeafCount = yyt->U_1.V_4.Node1.Son1->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_4.Node1.IsConstantRE = TRUE;
    yyt->U_1.V_4.Node1.Tree = Tree_NoTree;
    break;
  case Tree0_Option:;
    yyVisit1(yyt->U_1.V_5.Option.Son1);
    yyt->U_1.V_5.Option.NodeCount = yyt->U_1.V_5.Option.Son1->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_5.Option.LeafCount = yyt->U_1.V_5.Option.Son1->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_5.Option.IsConstantRE = FALSE;
    yyt->U_1.V_5.Option.Tree = Tree_MakeTree1(Tree_nOption, yyt->U_1.V_5.Option.Son1->U_1.V_3.Node.Tree);
    break;
  case Tree0_Repetition:;
    yyVisit1(yyt->U_1.V_6.Repetition.Son1);
    yyt->U_1.V_6.Repetition.NodeCount = yyt->U_1.V_6.Repetition.Son1->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_6.Repetition.LeafCount = yyt->U_1.V_6.Repetition.Son1->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_6.Repetition.IsConstantRE = FALSE;
    yyt->U_1.V_6.Repetition.Tree = Tree_MakeTree1(Tree_nRepetition, yyt->U_1.V_6.Repetition.Son1->U_1.V_3.Node.Tree);
    break;
  case Tree0_Node2:;
    yyVisit1(yyt->U_1.V_7.Node2.Son2);
    yyVisit1(yyt->U_1.V_7.Node2.Son1);
    yyt->U_1.V_7.Node2.NodeCount = yyt->U_1.V_7.Node2.Son1->U_1.V_3.Node.NodeCount + yyt->U_1.V_7.Node2.Son2->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_7.Node2.LeafCount = yyt->U_1.V_7.Node2.Son1->U_1.V_3.Node.LeafCount + yyt->U_1.V_7.Node2.Son2->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_7.Node2.IsConstantRE = TRUE;
    yyt->U_1.V_7.Node2.Tree = Tree_NoTree;
    break;
  case Tree0_List:;
    yyVisit1(yyt->U_1.V_8.List.Son2);
    yyVisit1(yyt->U_1.V_8.List.Son1);
    yyt->U_1.V_8.List.NodeCount = yyt->U_1.V_8.List.Son1->U_1.V_3.Node.NodeCount + yyt->U_1.V_8.List.Son2->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_8.List.LeafCount = yyt->U_1.V_8.List.Son1->U_1.V_3.Node.LeafCount + yyt->U_1.V_8.List.Son2->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_8.List.IsConstantRE = TRUE;
    yyt->U_1.V_8.List.Tree = Tree_MakeTree2(Tree_nList, yyt->U_1.V_8.List.Son1->U_1.V_3.Node.Tree, yyt->U_1.V_8.List.Son2->U_1.V_3.Node.Tree);
    break;
  case Tree0_Sequence:;
    yyVisit1(yyt->U_1.V_9.Sequence.Son2);
    yyVisit1(yyt->U_1.V_9.Sequence.Son1);
    yyt->U_1.V_9.Sequence.NodeCount = yyt->U_1.V_9.Sequence.Son1->U_1.V_3.Node.NodeCount + yyt->U_1.V_9.Sequence.Son2->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_9.Sequence.LeafCount = yyt->U_1.V_9.Sequence.Son1->U_1.V_3.Node.LeafCount + yyt->U_1.V_9.Sequence.Son2->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_9.Sequence.IsConstantRE = yyt->U_1.V_9.Sequence.Son1->U_1.V_3.Node.IsConstantRE && yyt->U_1.V_9.Sequence.Son2->U_1.V_3.Node.IsConstantRE;
    yyt->U_1.V_9.Sequence.Tree = Tree_MakeTree2(Tree_nSequence, yyt->U_1.V_9.Sequence.Son1->U_1.V_3.Node.Tree, yyt->U_1.V_9.Sequence.Son2->U_1.V_3.Node.Tree);
    break;
  case Tree0_Alternative:;
    yyVisit1(yyt->U_1.V_10.Alternative.Son2);
    yyVisit1(yyt->U_1.V_10.Alternative.Son1);
    yyt->U_1.V_10.Alternative.NodeCount = yyt->U_1.V_10.Alternative.Son1->U_1.V_3.Node.NodeCount + yyt->U_1.V_10.Alternative.Son2->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_10.Alternative.LeafCount = yyt->U_1.V_10.Alternative.Son1->U_1.V_3.Node.LeafCount + yyt->U_1.V_10.Alternative.Son2->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_10.Alternative.IsConstantRE = FALSE;
    yyt->U_1.V_10.Alternative.Tree = Tree_MakeTree2(Tree_nAlternative, yyt->U_1.V_10.Alternative.Son1->U_1.V_3.Node.Tree, yyt->U_1.V_10.Alternative.Son2->U_1.V_3.Node.Tree);
    break;
  case Tree0_Ch:;
    yyt->U_1.V_11.Ch.NodeCount = 1;
    yyt->U_1.V_11.Ch.LeafCount = 1;
    yyt->U_1.V_11.Ch.IsConstantRE = TRUE;
    yyt->U_1.V_11.Ch.Tree = Tree_MakeTreeCh(Tree_nChar, Classes_ToClass.A[yyt->U_1.V_11.Ch.Ch]);
    break;
  case Tree0_Set:;
    j = Classes_IsInSetMem(yyt->U_1.V_12.Set.Set);
    if (j != 0) {
      yyt->U_1.V_12.Set.card = Sets_Card(&Classes_SetMemPtr->A[j].Classes);
      Sets_Assign(&Set1, yyt->U_1.V_12.Set.Set);
      Sets_Intersection(&Set1, Classes_CharSet);
      INC1(yyt->U_1.V_12.Set.card, Sets_Card(&Set1));
      if (yyt->U_1.V_12.Set.card == 1) {
        if (Sets_Card(&Classes_SetMemPtr->A[j].Classes) == 1) {
          yyt->U_1.V_12.Set.Tree = Tree_MakeTreeCh(Tree_nChar, CHR(Sets_Select(&Classes_SetMemPtr->A[j].Classes)));
        } else {
          yyt->U_1.V_12.Set.Tree = Tree_MakeTreeCh(Tree_nChar, Classes_ToClass.A[CHR(Sets_Select(&Set1))]);
        }
      } else {
        Sets_MakeSet(&Set2, ORD(Dfa_LastCh));
        if (!Sets_IsEmpty(Set1)) {
          {
            LONGCARD B_1 = Sets_Minimum(&Set1), B_2 = Sets_Maximum(&Set1);

            if (B_1 <= B_2)
              for (i = B_1;; i += 1) {
                if (Sets_IsElement(i, &Set1)) {
                  Sets_Include(&Set2, ORD(Classes_ToClass.A[CHR(i)]));
                }
                if (i >= B_2) break;
              }
          }
        }
        if (!Sets_IsEmpty(Classes_SetMemPtr->A[j].Classes)) {
          {
            LONGCARD B_3 = Sets_Minimum(&Classes_SetMemPtr->A[j].Classes), B_4 = Sets_Maximum(&Classes_SetMemPtr->A[j].Classes);

            if (B_3 <= B_4)
              for (i = B_3;; i += 1) {
                if (Sets_IsElement(i, &Classes_SetMemPtr->A[j].Classes)) {
                  Sets_Include(&Set2, i);
                }
                if (i >= B_4) break;
              }
          }
        }
        yyt->U_1.V_12.Set.Tree = Tree_MakeTreeSet(Tree_nSet, Set2);
      }
    } else {
      yyt->U_1.V_12.Set.card = Sets_Card(&yyt->U_1.V_12.Set.Set);
      if (yyt->U_1.V_12.Set.card == 1) {
        yyt->U_1.V_12.Set.Tree = Tree_MakeTreeCh(Tree_nChar, CHR(Sets_Select(&yyt->U_1.V_12.Set.Set)));
      } else {
        yyt->U_1.V_12.Set.Tree = Tree_MakeTreeSet(Tree_nSet, yyt->U_1.V_12.Set.Set);
      }
    }
    yyt->U_1.V_12.Set.NodeCount = 1;
    yyt->U_1.V_12.Set.LeafCount = 1;
    yyt->U_1.V_12.Set.IsConstantRE = yyt->U_1.V_12.Set.card == 1;
    break;
  case Tree0_String:;
    yyt->U_1.V_13.String.NodeCount = StringMem_Length(yyt->U_1.V_13.String.String);
    yyt->U_1.V_13.String.LeafCount = StringMem_Length(yyt->U_1.V_13.String.String);
    yyt->U_1.V_13.String.IsConstantRE = TRUE;
    StringMem_GetString(yyt->U_1.V_13.String.String, &String1);
    Strings_AssignEmpty(&String2);
    {
      LONGCARD B_5 = 1, B_6 = Strings_Length(&String1);

      if (B_5 <= B_6)
        for (i = B_5;; i += 1) {
          Strings_Append(&String2, Classes_ToClass.A[Strings_Char(&String1, (Strings_tStringIndex)i)]);
          if (i >= B_6) break;
        }
    }
    yyt->U_1.V_13.String.Tree = Tree_MakeTreeString(Tree_nString, StringMem_PutString(&String2));
    break;
  case Tree0_Rule:;
    yyVisit1(yyt->U_1.V_14.Rule.Patterns);
    yyt->U_1.V_14.Rule.NodeCount = yyt->U_1.V_14.Rule.Patterns->U_1.V_3.Node.NodeCount;
    yyt->U_1.V_14.Rule.LeafCount = yyt->U_1.V_14.Rule.Patterns->U_1.V_3.Node.LeafCount;
    yyt->U_1.V_14.Rule.IsConstantRE = TRUE;
    yyt->U_1.V_14.Rule.Tree = Tree_MakeTreeRule(Tree_nRule, yyt->U_1.V_14.Rule.Patterns->U_1.V_3.Node.Tree, yyt->U_1.V_14.Rule.TargetCode, yyt->U_1.V_14.Rule.Line, yyt->U_1.V_14.Rule.CodeMode, yyt->U_1.V_14.Rule.RuleNr);
    break;
  case Tree0_Pattern:;
    yyVisit1(yyt->U_1.V_15.Pattern.RightContext);
    yyVisit1(yyt->U_1.V_15.Pattern.RegExpr);
    if (yyt->U_1.V_15.Pattern.RegExpr->U_1.V_3.Node.IsConstantRE && yyt->U_1.V_15.Pattern.RightContext->U_1.V_3.Node.IsConstantRE) {
      yyt->U_1.V_15.Pattern.card = Sets_Card(&yyt->U_1.V_15.Pattern.StartStates);
      yyt->U_1.V_15.Pattern.NodeCount = (yyt->U_1.V_15.Pattern.RegExpr->U_1.V_3.Node.NodeCount + yyt->U_1.V_15.Pattern.RightContext->U_1.V_3.Node.NodeCount) * yyt->U_1.V_15.Pattern.card;
    } else {
      yyt->U_1.V_15.Pattern.NodeCount = 0;
    }
    if (!(yyt->U_1.V_15.Pattern.RegExpr->U_1.V_3.Node.IsConstantRE && yyt->U_1.V_15.Pattern.RightContext->U_1.V_3.Node.IsConstantRE)) {
      yyt->U_1.V_15.Pattern.LeafCount = yyt->U_1.V_15.Pattern.RegExpr->U_1.V_3.Node.LeafCount + yyt->U_1.V_15.Pattern.RightContext->U_1.V_3.Node.LeafCount;
    } else {
      yyt->U_1.V_15.Pattern.LeafCount = 0;
    }
    yyt->U_1.V_15.Pattern.IsConstantRE = TRUE;
    yyt->U_1.V_15.Pattern.Tree = Tree_MakeTreePattern(Tree_nPattern, yyt->U_1.V_15.Pattern.StartStates, yyt->U_1.V_15.Pattern.RegExpr->U_1.V_3.Node.Tree, yyt->U_1.V_15.Pattern.RightContext->U_1.V_3.Node.Tree, (BOOLEAN)(yyt->U_1.V_15.Pattern.RegExpr->U_1.V_3.Node.IsConstantRE && yyt->U_1.V_15.Pattern.RightContext->U_1.V_3.Node.IsConstantRE), yyt->U_1.V_15.Pattern.PatternNr, yyt->U_1.V_15.Pattern.Position);
    break;
  default :
    break;
  }
}

void Eval_BeginEval
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_MakeSet(&Set1, ORD(Dfa_LastCh));
}

void Eval_CloseEval
# ifdef __STDC__
()
# else
()
# endif
{
}

void Eval__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Tree0__init();
    Tree0__init();
    Strings__init();
    StringMem__init();
    Sets__init();
    Classes__init();
    Dfa__init();
    StringMem__init();
    Tree__init();

  }
}
