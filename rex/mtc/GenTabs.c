#include "SYSTEM_.h"

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
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

#ifndef DEFINITION_Times
#include "Times.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_DefTable
#include "DefTable.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Nfa
#include "Nfa.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_Traces
#include "Traces.h"
#endif

#ifndef DEFINITION_ScanTabs
#include "ScanTabs.h"
#endif

#ifndef DEFINITION_ScanGen
#include "ScanGen.h"
#endif

#ifndef DEFINITION_Classes
#include "Classes.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

Tree_tTree GenTabs_Root;
SHORTINT GenTabs_NodeCount, GenTabs_StartStateCount;
SHORTCARD GenTabs_RuleCount, GenTabs_PatternCount, GenTabs_LeafCount;
BOOLEAN GenTabs_LeftJustUsed;
SHORTCARD GenTabs_EobAction, GenTabs_DefaultAction;
GenTabs_PatternTable *GenTabs_PatternTablePtr;
LONGINT GenTabs_PatternTableSize;
GenTabs_RuleToCode *GenTabs_RuleToCodePtr;
LONGINT GenTabs_RuleToCodeSize;

typedef struct S_1 *SetOfNInfoPtr;
typedef struct S_1 {
    SetOfNInfoPtr Next;
    Sets_tSet Set;
    Dfa_DStateRange DState;
} SetOfNInfo;
typedef struct S_2 {
    SetOfNInfoPtr A[100000 + 1];
} MapDToSetOfN;
typedef struct S_3 {
    SetOfNInfoPtr A[100000 + 1];
} HashDToSetOfN;
typedef struct S_4 {
    Dfa_DStateRange A[100000 + 1];
} Stack;
static MapDToSetOfN *MapDToSetOfNPtr;
static LONGINT MapDToSetOfNSize;
static HashDToSetOfN *HashDToSetOfNPtr;
static LONGINT HashDToSetOfNSize;
static Stack *StackPtr;
static LONGINT StackSize;
static Dfa_DStateRange StackTop;
static Sets_tSet StartSet, dSemantics;
static INTEGER SentinelSavings;
static BOOLEAN IsComputedNContext;
static BOOLEAN IsComputedDContext;
static BOOLEAN IsComputedFinals;
static void ComputeNfa ARGS(());
static SHORTINT ComputeLength ARGS((Tree_tTree t));
static void AttributeEvaluator ARGS((Tree_tTree t, Nfa_TransitionRange *Transitions, Sets_tSet *FinalStates, BOOLEAN *IsOptional));
static Nfa_TransitionRange tt;
static SHORTCARD PatternNr;
static void ExtendTransitions ARGS((Sets_tElement NState));
static void EnterNSemantics ARGS((Sets_tElement NState));
static Dfa_DStateRange MapSetOfNToD ARGS((Sets_tSet t));
static void ComputeDfa ARGS(());
#define InitialStackSize   64
struct S_5 {
    Sets_tSet A[256];
};
static Dfa_DStateRange dState;
static void EnterDSemantics ARGS((Sets_tElement NState));
static void SaveSentinels ARGS(());
static void AddConstantREs ARGS(());
static void ComputeConstantRE ARGS((Tree_tTree t, Strings_tString *String));
static void AddConstantRE ARGS((Dfa_DStateRange StartState, Strings_tString String, SHORTCARD PatternNr, Sets_tSet StartStates));
static CHAR GetCh ARGS(());
static void UpdateContext ARGS(());
static void InvertMapping ARGS(());
static void CheckTables ARGS(());
static void CheckStartState ARGS((SHORTCARD StartState, Idents_tIdent Ident, BOOLEAN LeftJust));
static void WritePattern ARGS(());
static void WriteStatistics ARGS(());

static SHORTCARD *G_1_ChIndex;
static SHORTCARD *G_2_StringLength;
static BOOLEAN *G_3_EndOfInput;
static Strings_tString *G_4_String;

static void ComputeNfa
# ifdef __STDC__
()
# else
()
# endif
{
  Nfa_TransitionRange t1, t2;
  Sets_tSet f1, f2;
  BOOLEAN o1, o2;
  Tree_tTree ruleList;
  Tree_tTree rule;
  Tree_tTree patternList;
  Tree_tTree pattern;
  SHORTCARD RuleNr;
  Nfa_NStateRange NState;
  SHORTINT length;

  Nfa_BeginNfa();
  {
    LONGINT B_1 = 1, B_2 = GenTabs_StartStateCount;

    if (B_1 <= B_2)
      for (NState = B_1;; NState += 1) {
        if (Nfa_MakeNState((LONGINT)Nfa_NoTransition) != NState) {
          exit(1);
        }
        if (NState >= B_2) break;
      }
  }
  Sets_MakeSet(&f1, (Sets_tElement)GenTabs_LeafCount);
  Sets_MakeSet(&f2, (Sets_tElement)GenTabs_LeafCount);
  ruleList = GenTabs_Root;
  while (ruleList != Tree_NoTree) {
    rule = ruleList->U_1.V_3.vNode2.Son2;
    RuleNr = rule->U_1.V_7.vNodeRule.RuleNr;
    GenTabs_RuleToCodePtr->A[RuleNr].Text = rule->U_1.V_7.vNodeRule.TargetCode;
    GenTabs_RuleToCodePtr->A[RuleNr].TextLine = rule->U_1.V_7.vNodeRule.Line;
    GenTabs_RuleToCodePtr->A[RuleNr].CodeMode = rule->U_1.V_7.vNodeRule.CodeMode;
    patternList = rule->U_1.V_7.vNodeRule.Patterns;
    while (patternList != Tree_NoTree) {
      pattern = patternList->U_1.V_3.vNode2.Son2;
      PatternNr = pattern->U_1.V_8.vNodePattern.PatternNr;
      {
        register GenTabs_PatternInfo *W_1 = &GenTabs_PatternTablePtr->A[PatternNr];

        W_1->Rule = RuleNr;
        W_1->ContextLng = GenTabs_NoContext;
        W_1->Position = pattern->U_1.V_8.vNodePattern.Position;
      }
      if (!pattern->U_1.V_8.vNodePattern.IsConstantRE) {
        AttributeEvaluator(pattern->U_1.V_8.vNodePattern.RegExpr, &t1, &f1, &o1);
        AttributeEvaluator(pattern->U_1.V_8.vNodePattern.RightContext, &t2, &f2, &o2);
        tt = t1;
        Sets_ForallDo(pattern->U_1.V_8.vNodePattern.StartStates, (Sets_ProcOftElement)ExtendTransitions);
        if (o2) {
          Sets_ForallDo(f1, (Sets_ProcOftElement)EnterNSemantics);
        }
        tt = t2;
        Sets_ForallDo(f1, (Sets_ProcOftElement)ExtendTransitions);
        Sets_ForallDo(f2, (Sets_ProcOftElement)EnterNSemantics);
        length = ComputeLength(pattern->U_1.V_8.vNodePattern.RightContext);
        if (length != GenTabs_VariableContext) {
          GenTabs_PatternTablePtr->A[PatternNr].ContextLng = length;
        } else {
          length = ComputeLength(pattern->U_1.V_8.vNodePattern.RegExpr);
          if (length != GenTabs_VariableContext) {
            GenTabs_PatternTablePtr->A[PatternNr].ContextLng = -length;
          } else {
            GenTabs_PatternTablePtr->A[PatternNr].ContextLng = GenTabs_VariableContext;
            Sets_MakeSet(&GenTabs_PatternTablePtr->A[PatternNr].NContext, (Sets_tElement)GenTabs_LeafCount);
            Sets_Assign(&GenTabs_PatternTablePtr->A[PatternNr].NContext, f1);
          }
        }
      }
      patternList = patternList->U_1.V_3.vNode2.Son1;
    }
    ruleList = ruleList->U_1.V_3.vNode2.Son1;
  }
  IsComputedNContext = TRUE;
  Sets_ReleaseSet(&f1);
  Sets_ReleaseSet(&f2);
}

static SHORTINT ComputeLength
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  SHORTINT l1, l2;
  Strings_tString string;

  if (t == Tree_NoTree) {
    return GenTabs_NoContext;
  }
  switch (t->U_1.V_1.vNode0.Rule) {
  case Tree_nAlternative:;
    l1 = ComputeLength(t->U_1.V_3.vNode2.Son1);
    l2 = ComputeLength(t->U_1.V_3.vNode2.Son2);
    if (l1 == l2) {
      return l1;
    } else {
      return GenTabs_VariableContext;
    }
    break;
  case Tree_nSequence:;
    l1 = ComputeLength(t->U_1.V_3.vNode2.Son1);
    l2 = ComputeLength(t->U_1.V_3.vNode2.Son2);
    if (l1 != GenTabs_VariableContext && l2 != GenTabs_VariableContext) {
      return l1 + l2;
    } else {
      return GenTabs_VariableContext;
    }
    break;
  case Tree_nRepetition:;
  case Tree_nOption:;
    return GenTabs_VariableContext;
    break;
  case Tree_nChar:;
  case Tree_nSet:;
    return 1;
    break;
  case Tree_nString:;
    StringMem_GetString(t->U_1.V_6.vNodeString.String, &string);
    return Strings_Length(&string);
    break;
  }
}

static void AttributeEvaluator
# ifdef __STDC__
(Tree_tTree t, Nfa_TransitionRange *Transitions, Sets_tSet *FinalStates, BOOLEAN *IsOptional)
# else
(t, Transitions, FinalStates, IsOptional)
Tree_tTree t;
Nfa_TransitionRange *Transitions;
Sets_tSet *FinalStates;
BOOLEAN *IsOptional;
# endif
{
  Nfa_TransitionRange t1, t2;
  Sets_tSet f1, f2;
  BOOLEAN o1, o2;
  Nfa_NStateRange NState;
  Strings_tString string;
  CARDINAL i;

  if (t == Tree_NoTree) {
    *Transitions = Nfa_NoTransition;
    Sets_AssignEmpty(FinalStates);
    *IsOptional = TRUE;
    return;
  }
  switch (t->U_1.V_1.vNode0.Rule) {
  case Tree_nAlternative:;
    Sets_MakeSet(&f1, (Sets_tElement)GenTabs_LeafCount);
    Sets_MakeSet(&f2, (Sets_tElement)GenTabs_LeafCount);
    AttributeEvaluator(t->U_1.V_3.vNode2.Son1, &t1, &f1, &o1);
    AttributeEvaluator(t->U_1.V_3.vNode2.Son2, &t2, &f2, &o2);
    *Transitions = Nfa_UniteTransitions(t1, t2);
    Sets_Assign(FinalStates, f1);
    Sets_Union(FinalStates, f2);
    *IsOptional = o1 || o2;
    Sets_ReleaseSet(&f1);
    Sets_ReleaseSet(&f2);
    break;
  case Tree_nSequence:;
    Sets_MakeSet(&f1, (Sets_tElement)GenTabs_LeafCount);
    Sets_MakeSet(&f2, (Sets_tElement)GenTabs_LeafCount);
    AttributeEvaluator(t->U_1.V_3.vNode2.Son1, &t1, &f1, &o1);
    AttributeEvaluator(t->U_1.V_3.vNode2.Son2, &t2, &f2, &o2);
    tt = t2;
    Sets_ForallDo(f1, (Sets_ProcOftElement)ExtendTransitions);
    if (o1) {
      *Transitions = Nfa_UniteTransitions(t1, t2);
    } else {
      *Transitions = t1;
    }
    if (o2) {
      Sets_Assign(FinalStates, f1);
      Sets_Union(FinalStates, f2);
    } else {
      Sets_Assign(FinalStates, f2);
    }
    *IsOptional = o1 && o2;
    Sets_ReleaseSet(&f1);
    Sets_ReleaseSet(&f2);
    break;
  case Tree_nRepetition:;
    Sets_MakeSet(&f1, (Sets_tElement)GenTabs_LeafCount);
    AttributeEvaluator(t->U_1.V_2.vNode1.Son1, &t1, &f1, &o1);
    tt = t1;
    Sets_ForallDo(f1, (Sets_ProcOftElement)ExtendTransitions);
    *Transitions = t1;
    Sets_Assign(FinalStates, f1);
    *IsOptional = o1;
    Sets_ReleaseSet(&f1);
    break;
  case Tree_nOption:;
    Sets_MakeSet(&f1, (Sets_tElement)GenTabs_LeafCount);
    AttributeEvaluator(t->U_1.V_2.vNode1.Son1, &t1, &f1, &o1);
    *Transitions = t1;
    Sets_Assign(FinalStates, f1);
    *IsOptional = TRUE;
    Sets_ReleaseSet(&f1);
    break;
  case Tree_nChar:;
    NState = Nfa_MakeNState((LONGINT)Nfa_NoTransition);
    *Transitions = Nfa_MakeTransition(t->U_1.V_4.vNodeCh.Ch, NState);
    Sets_AssignElmt(FinalStates, (Sets_tElement)NState);
    *IsOptional = FALSE;
    break;
  case Tree_nSet:;
    Sets_MakeSet(&f1, ORD(Dfa_LastCh));
    Sets_Assign(&f1, t->U_1.V_5.vNodeSet.Set);
    NState = Nfa_MakeNState((LONGINT)Nfa_NoTransition);
    *Transitions = Nfa_NoTransition;
    while (!Sets_IsEmpty(f1)) {
      *Transitions = Nfa_AddTransition(Nfa_MakeTransition(CHR(Sets_Extract(&f1)), NState), *Transitions);
    }
    Sets_AssignElmt(FinalStates, (Sets_tElement)NState);
    *IsOptional = FALSE;
    Sets_ReleaseSet(&f1);
    break;
  case Tree_nString:;
    StringMem_GetString(t->U_1.V_6.vNodeString.String, &string);
    NState = Nfa_MakeNState((LONGINT)Nfa_NoTransition);
    *Transitions = Nfa_MakeTransition(Strings_Char(&string, (Strings_tStringIndex)Strings_Length(&string)), NState);
    Sets_AssignElmt(FinalStates, (Sets_tElement)NState);
    for (i = Strings_Length(&string) - 1; i >= 1; i += -1) {
      NState = Nfa_MakeNState(*Transitions);
      *Transitions = Nfa_MakeTransition(Strings_Char(&string, (Strings_tStringIndex)i), NState);
    }
    *IsOptional = FALSE;
    break;
  }
}

static void ExtendTransitions
# ifdef __STDC__
(Sets_tElement NState)
# else
(NState)
Sets_tElement NState;
# endif
{
  Nfa_PutTransitions((LONGINT)NState, Nfa_UniteTransitions(Nfa_GetTransitions((LONGINT)NState), Nfa_CopyTransitions(tt)));
}

static void EnterNSemantics
# ifdef __STDC__
(Sets_tElement NState)
# else
(NState)
Sets_tElement NState;
# endif
{
  Nfa_PutNSemantics((LONGINT)NState, PatternNr);
}

static Dfa_DStateRange MapSetOfNToD
# ifdef __STDC__
(Sets_tSet t)
# else
(t)
Sets_tSet t;
# endif
{
  Dfa_DStateRange DState;
  CARDINAL Hash;
  SetOfNInfoPtr Current;

  Hash = Sets_Maximum(&t) % (CARDINAL)Nfa_NStateCount;
  Current = HashDToSetOfNPtr->A[Hash];
  while (Current != NIL) {
    if (Sets_IsEqual(&Current->Set, &t)) {
      return Current->DState;
    }
    Current = Current->Next;
  }
  DState = Dfa_MakeDState();
  if (DState == MapDToSetOfNSize) {
    DynArray_ExtendArray((ADDRESS *)&MapDToSetOfNPtr, &MapDToSetOfNSize, (LONGINT)sizeof(SetOfNInfoPtr));
  }
  MapDToSetOfNPtr->A[DState] = (SetOfNInfoPtr)Memory_Alloc((LONGINT)sizeof(SetOfNInfo));
  Sets_MakeSet(&MapDToSetOfNPtr->A[DState]->Set, (Sets_tElement)Nfa_NStateCount);
  Sets_Assign(&MapDToSetOfNPtr->A[DState]->Set, t);
  MapDToSetOfNPtr->A[DState]->DState = DState;
  MapDToSetOfNPtr->A[DState]->Next = HashDToSetOfNPtr->A[Hash];
  HashDToSetOfNPtr->A[Hash] = MapDToSetOfNPtr->A[DState];
  INC(StackTop);
  if (StackTop == StackSize) {
    DynArray_ExtendArray((ADDRESS *)&StackPtr, &StackSize, (LONGINT)sizeof(Dfa_DStateRange));
  }
  StackPtr->A[StackTop] = DState;
  return DState;
}

static void ComputeDfa
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange DState;
  Nfa_NStateRange NState;
  Sets_tSet x;
  struct S_5 y;
  Nfa_TransitionRange Transition;
  CHAR Ch;
  Sets_tSet CharSet;
  SHORTCARD Pattern;
  Sets_tSet nStates;

  StackSize = InitialStackSize;
  DynArray_MakeArray((ADDRESS *)&StackPtr, &StackSize, (LONGINT)sizeof(Dfa_DStateRange));
  StackTop = 0;
  MapDToSetOfNSize = GenTabs_LeafCount;
  DynArray_MakeArray((ADDRESS *)&MapDToSetOfNPtr, &MapDToSetOfNSize, (LONGINT)sizeof(SetOfNInfoPtr));
  HashDToSetOfNSize = Nfa_NStateCount;
  DynArray_MakeArray((ADDRESS *)&HashDToSetOfNPtr, &HashDToSetOfNSize, (LONGINT)sizeof(SetOfNInfoPtr));
  {
    LONGINT B_3 = 0, B_4 = Nfa_NStateCount - 1;

    if (B_3 <= B_4)
      for (NState = B_3;; NState += 1) {
        HashDToSetOfNPtr->A[NState] = NIL;
        if (NState >= B_4) break;
      }
  }
  Sets_MakeSet(&x, (Sets_tElement)Nfa_NStateCount);
  {
    CHAR B_5 = Dfa_FirstCh, B_6 = Dfa_LastCh;

    if (B_5 <= B_6)
      for (Ch = B_5;; Ch += 1) {
        Sets_MakeSet(&y.A[Ch], (Sets_tElement)Nfa_NStateCount);
        if (Ch >= B_6) break;
      }
  }
  Sets_MakeSet(&CharSet, ORD(Dfa_LastCh));
  Sets_MakeSet(&nStates, (Sets_tElement)GenTabs_LeafCount);
  {
    LONGINT B_7 = 1, B_8 = GenTabs_StartStateCount;

    if (B_7 <= B_8)
      for (NState = B_7;; NState += 1) {
        Sets_AssignElmt(&x, (Sets_tElement)NState);
        DState = MapSetOfNToD(x);
        if (DState != NState) {
          exit(1);
        }
        if (NState >= B_8) break;
      }
  }
  while (StackTop > 0) {
    DState = StackPtr->A[StackTop];
    DEC(StackTop);
    Sets_Assign(&x, MapDToSetOfNPtr->A[DState]->Set);
    Sets_AssignEmpty(&CharSet);
    {
      LONGINT B_9 = 1, B_10 = Nfa_NStateCount;

      if (B_9 <= B_10)
        for (NState = B_9;; NState += 1) {
          if (Sets_IsElement((Sets_tElement)NState, &x)) {
            Transition = Nfa_GetTransitions(NState);
            while (!Nfa_IsLastTransition(Transition)) {
              Ch = Nfa_GetCh(Transition);
              Sets_Include(&y.A[Ch], (Sets_tElement)Nfa_GetNextState(Transition));
              Sets_Include(&CharSet, ORD(Ch));
              Transition = Nfa_NextTransition(Transition);
            }
          }
          if (NState >= B_10) break;
        }
    }
    while (!Sets_IsEmpty(CharSet)) {
      Ch = CHR(Sets_Extract(&CharSet));
      Dfa_PutTable(DState, Ch, MapSetOfNToD(y.A[Ch]));
      Sets_AssignEmpty(&y.A[Ch]);
    }
  }
  INC1(GenTabs_NodeCount, Dfa_DStateCount + 3);
  {
    SHORTCARD B_11 = 1, B_12 = GenTabs_PatternCount - 2;

    if (B_11 <= B_12)
      for (Pattern = B_11;; Pattern += 1) {
        if (GenTabs_PatternTablePtr->A[Pattern].ContextLng == GenTabs_VariableContext) {
          Sets_MakeSet(&GenTabs_PatternTablePtr->A[Pattern].DContext, (Sets_tElement)GenTabs_NodeCount);
          {
            SHORTINT B_13 = 1, B_14 = Dfa_DStateCount;

            if (B_13 <= B_14)
              for (DState = B_13;; DState += 1) {
                Sets_Assign(&nStates, GenTabs_PatternTablePtr->A[Pattern].NContext);
                Sets_Intersection(&nStates, MapDToSetOfNPtr->A[DState]->Set);
                if (!Sets_IsEmpty(nStates)) {
                  Sets_Include(&GenTabs_PatternTablePtr->A[Pattern].DContext, (Sets_tElement)DState);
                }
                if (DState >= B_14) break;
              }
          }
          Sets_ReleaseSet(&GenTabs_PatternTablePtr->A[Pattern].NContext);
        }
        if (Pattern >= B_12) break;
      }
  }
  IsComputedNContext = FALSE;
  IsComputedDContext = TRUE;
  {
    SHORTINT B_15 = 1, B_16 = Dfa_DStateCount;

    if (B_15 <= B_16)
      for (DState = B_15;; DState += 1) {
        dState = DState;
        Sets_AssignEmpty(&dSemantics);
        Sets_ForallDo(MapDToSetOfNPtr->A[DState]->Set, (Sets_ProcOftElement)EnterDSemantics);
        Sets_Exclude(&dSemantics, (Sets_tElement)ScanTabs_NoRule);
        Dfa_PutDSemantics(DState, dSemantics);
        if (DState >= B_16) break;
      }
  }
  {
    SHORTINT B_17 = 1, B_18 = Dfa_DStateCount;

    if (B_17 <= B_18)
      for (DState = B_17;; DState += 1) {
        Sets_ReleaseSet(&MapDToSetOfNPtr->A[DState]->Set);
        Memory_Free((LONGINT)sizeof(SetOfNInfo), (ADDRESS)MapDToSetOfNPtr->A[DState]);
        if (DState >= B_18) break;
      }
  }
  Sets_ReleaseSet(&x);
  {
    CHAR B_19 = Dfa_FirstCh, B_20 = Dfa_LastCh;

    if (B_19 <= B_20)
      for (Ch = B_19;; Ch += 1) {
        Sets_ReleaseSet(&y.A[Ch]);
        if (Ch >= B_20) break;
      }
  }
  Sets_ReleaseSet(&CharSet);
  Sets_ReleaseSet(&nStates);
  DynArray_ReleaseArray((ADDRESS *)&StackPtr, &StackSize, (LONGINT)sizeof(Dfa_DStateRange));
  DynArray_ReleaseArray((ADDRESS *)&MapDToSetOfNPtr, &MapDToSetOfNSize, (LONGINT)sizeof(SetOfNInfoPtr));
  DynArray_ReleaseArray((ADDRESS *)&HashDToSetOfNPtr, &HashDToSetOfNSize, (LONGINT)sizeof(SetOfNInfoPtr));
  Nfa_FinalizeNfa();
}

static void EnterDSemantics
# ifdef __STDC__
(Sets_tElement NState)
# else
(NState)
Sets_tElement NState;
# endif
{
  Sets_Include(&dSemantics, (Sets_tElement)Nfa_GetNSemantics((LONGINT)NState));
}

static void SaveSentinels
# ifdef __STDC__
()
# else
()
# endif
{
  Dfa_DStateRange DState, Default;
  BOOLEAN Success;
  CHAR Ch, LastCh;
  Sets_tSet Defaults;

  SentinelSavings = 0;
  Sets_MakeSet(&Defaults, (Sets_tElement)Dfa_DStateCount);
  {
    SHORTINT B_21 = 1, B_22 = Dfa_DStateCount;

    if (B_21 <= B_22)
      for (DState = B_21;; DState += 1) {
        Sets_Include(&Defaults, (Sets_tElement)Dfa_GetDefault(DState));
        if (DState >= B_22) break;
      }
  }
  {
    SHORTINT B_23 = 1, B_24 = Dfa_DStateCount;

    if (B_23 <= B_24)
      for (DState = B_23;; DState += 1) {
        Dfa_GetDSemantics(DState, &dSemantics);
        Default = Dfa_GetDefault(DState);
        if (!Sets_IsEmpty(dSemantics) && (Default == Dfa_DNoState || Default == Dfa_EobDefaultState) && !Sets_IsElement((Sets_tElement)DState, &Defaults)) {
          Success = TRUE;
          Ch = Dfa_GetFirst(DState);
          LastCh = Dfa_GetLast(DState);
          if (Ch <= LastCh) {
            for (;;) {
              if (Ch != Classes_ToClass.A[Dfa_EobCh] && Dfa_GetTable(DState, Ch) != Dfa_DNoState) {
                Success = FALSE;
                goto EXIT_1;
              }
              if (Ch == LastCh) {
                goto EXIT_1;
              }
              INC(Ch);
            } EXIT_1:;
          }
          if (Success) {
            Dfa_PutTable(DState, Classes_ToClass.A[Dfa_EobCh], Dfa_DNoState);
            Dfa_PutDefault(DState, Dfa_DNoState);
            INC(SentinelSavings);
          }
        }
        if (DState >= B_24) break;
      }
  }
  Sets_ReleaseSet(&Defaults);
}

static void AddConstantREs
# ifdef __STDC__
()
# else
()
# endif
{
  Tree_tTree ruleList;
  Tree_tTree rule;
  Tree_tTree patternList;
  Tree_tTree pattern;
  Strings_tString string1, string2;
  Dfa_DStateRange StartState;
  SHORTCARD PatternNr;

  Traces_InitTraces();
  Sets_MakeSet(&StartSet, (Sets_tElement)GenTabs_StartStateCount);
  ruleList = GenTabs_Root;
  while (ruleList != Tree_NoTree) {
    rule = ruleList->U_1.V_3.vNode2.Son2;
    patternList = rule->U_1.V_7.vNodeRule.Patterns;
    while (patternList != Tree_NoTree) {
      pattern = patternList->U_1.V_3.vNode2.Son2;
      if (pattern->U_1.V_8.vNodePattern.IsConstantRE) {
        PatternNr = pattern->U_1.V_8.vNodePattern.PatternNr;
        GenTabs_PatternTablePtr->A[PatternNr].ContextLng = ComputeLength(pattern->U_1.V_8.vNodePattern.RightContext);
        ComputeConstantRE(pattern->U_1.V_8.vNodePattern.RegExpr, &string1);
        ComputeConstantRE(pattern->U_1.V_8.vNodePattern.RightContext, &string2);
        Strings_Concatenate(&string1, &string2);
        Traces_ResetTraces((LONGINT)Strings_Length(&string1));
        {
          SHORTINT B_25 = 1, B_26 = GenTabs_StartStateCount;

          if (B_25 <= B_26)
            for (StartState = B_25;; StartState += 1) {
              if (Sets_IsElement((Sets_tElement)StartState, &pattern->U_1.V_8.vNodePattern.StartStates)) {
                AddConstantRE(StartState, string1, PatternNr, pattern->U_1.V_8.vNodePattern.StartStates);
              }
              if (StartState >= B_26) break;
            }
        }
      }
      patternList = patternList->U_1.V_3.vNode2.Son1;
    }
    ruleList = ruleList->U_1.V_3.vNode2.Son1;
  }
  Sets_ReleaseSet(&StartSet);
  Traces_FinalizeTraces();
}

static void ComputeConstantRE
# ifdef __STDC__
(Tree_tTree t, Strings_tString *String)
# else
(t, String)
Tree_tTree t;
Strings_tString *String;
# endif
{
  Strings_tString string2;

  if (t == Tree_NoTree) {
    Strings_AssignEmpty(String);
  } else {
    switch (t->U_1.V_1.vNode0.Rule) {
    case Tree_nSequence:;
      ComputeConstantRE(t->U_1.V_3.vNode2.Son1, String);
      ComputeConstantRE(t->U_1.V_3.vNode2.Son2, &string2);
      Strings_Concatenate(String, &string2);
      break;
    case Tree_nChar:;
      Strings_AssignEmpty(String);
      Strings_Append(String, t->U_1.V_4.vNodeCh.Ch);
      break;
    case Tree_nString:;
      StringMem_GetString(t->U_1.V_6.vNodeString.String, String);
      break;
    }
  }
}

static CHAR GetCh
# ifdef __STDC__
()
# else
()
# endif
{
  if (*G_1_ChIndex == *G_2_StringLength) {
    *G_3_EndOfInput = TRUE;
    return Dfa_FirstCh;
  } else {
    INC(*G_1_ChIndex);
    return Strings_Char(G_4_String, *G_1_ChIndex);
  }
}

static void AddConstantRE
# ifdef __STDC__
(Dfa_DStateRange StartState, Strings_tString String, SHORTCARD PatternNr, Sets_tSet StartStates)
# else
(StartState, String, PatternNr, StartStates)
Dfa_DStateRange StartState;
Strings_tString String;
SHORTCARD PatternNr;
Sets_tSet StartStates;
# endif
{
  CHAR Ch;
  Dfa_DStateRange State, Successor, NewState, PrevState;
  SHORTCARD ChIndex;
  SHORTCARD StringLength;
  BOOLEAN EndOfInput;
  SHORTCARD *L_1;
  SHORTCARD *L_2;
  BOOLEAN *L_3;
  Strings_tString *L_4;

  L_1 = G_1_ChIndex;
  G_1_ChIndex = &ChIndex;
  L_2 = G_2_StringLength;
  G_2_StringLength = &StringLength;
  L_3 = G_3_EndOfInput;
  G_3_EndOfInput = &EndOfInput;
  L_4 = G_4_String;
  G_4_String = &String;
  StringLength = Strings_Length(&String);
  ChIndex = 0;
  EndOfInput = FALSE;
  State = StartState;
  Ch = GetCh();
  PrevState = State;
  for (;;) {
    if (EndOfInput) {
      goto EXIT_2;
    }
    Successor = Dfa_GetTable(State, Ch);
    if (Successor == Dfa_DNoState) {
      goto EXIT_2;
    }
    if (Successor <= Dfa_MaxAmbiguousState && Sets_IsElement((Sets_tElement)Successor, &Dfa_AmbiguousStates)) {
      goto EXIT_2;
    }
    Dfa_GetStartSet(Successor, &StartSet);
    if (!Sets_IsSubset(StartSet, StartStates)) {
      goto EXIT_2;
    }
    State = Successor;
    NewState = Traces_RecordedTrace(ChIndex, State);
    if (NewState != Dfa_DNoState) {
      Dfa_PutTable(PrevState, Ch, NewState);
    } else {
      Traces_RecordTrace(ChIndex, State, State);
      NewState = State;
    }
    Dfa_GetStartSet(NewState, &StartSet);
    Sets_Include(&StartSet, (Sets_tElement)StartState);
    Dfa_PutStartSet(NewState, StartSet);
    PrevState = NewState;
    Ch = GetCh();
  } EXIT_2:;
  for (;;) {
    if (EndOfInput) {
      goto EXIT_3;
    }
    Successor = Dfa_GetTable(State, Ch);
    if (Successor != Dfa_DNoState) {
      State = Successor;
      NewState = Traces_RecordedTrace(ChIndex, State);
      if (NewState == Dfa_DNoState) {
        NewState = Dfa_MakeDState();
        Dfa_GetDSemantics(State, &dSemantics);
        Dfa_PutDSemantics(NewState, dSemantics);
        Dfa_PutDefault(NewState, State);
        Traces_RecordTrace(ChIndex, State, NewState);
      }
      Dfa_PutTable(PrevState, Ch, NewState);
      Dfa_GetStartSet(NewState, &StartSet);
      Sets_Include(&StartSet, (Sets_tElement)StartState);
      Dfa_PutStartSet(NewState, StartSet);
      PrevState = NewState;
      Ch = GetCh();
    } else {
      if (Dfa_GetDefault(State) == Dfa_DNoState) {
        goto EXIT_3;
      }
      State = Dfa_GetDefault(State);
    }
  } EXIT_3:;
  for (;;) {
    if (EndOfInput) {
      goto EXIT_4;
    }
    NewState = Traces_RecordedTrace(ChIndex, Dfa_DNoState);
    if (NewState == Dfa_DNoState) {
      NewState = Dfa_MakeDState();
      Dfa_PutDefault(NewState, Dfa_EobDefaultState);
      Traces_RecordTrace(ChIndex, Dfa_DNoState, NewState);
    }
    Dfa_PutTable(PrevState, Ch, NewState);
    Dfa_GetStartSet(NewState, &StartSet);
    Sets_Include(&StartSet, (Sets_tElement)StartState);
    Dfa_PutStartSet(NewState, StartSet);
    PrevState = NewState;
    Ch = GetCh();
  } EXIT_4:;
  Dfa_GetDSemantics(PrevState, &dSemantics);
  Sets_Include(&dSemantics, (Sets_tElement)PatternNr);
  Dfa_PutDSemantics(PrevState, dSemantics);
  G_1_ChIndex = L_1;
  G_2_StringLength = L_2;
  G_3_EndOfInput = L_3;
  G_4_String = L_4;
}

static void UpdateContext
# ifdef __STDC__
()
# else
()
# endif
{
  SHORTCARD Pattern;
  Dfa_DStateRange State1;
  Dfa_DStateRange State2;
  Dfa_DStateRange Max;

  if (Dfa_DStateCount > GenTabs_NodeCount) {
    IO_WriteS((System_tFile)IO_StdError, (STRING)"internal Error: StateCount > NodeCount", 38L);
    IO_WriteNl((System_tFile)IO_StdError);
  }
  {
    SHORTCARD B_27 = 0, B_28 = GenTabs_PatternCount - 2;

    if (B_27 <= B_28)
      for (Pattern = B_27;; Pattern += 1) {
        if (GenTabs_PatternTablePtr->A[Pattern].ContextLng == GenTabs_VariableContext) {
          Max = Sets_Maximum(&GenTabs_PatternTablePtr->A[Pattern].DContext);
          {
            SHORTINT B_29 = 1, B_30 = Max;

            if (B_29 <= B_30)
              for (State1 = B_29;; State1 += 1) {
                if (Sets_IsElement((Sets_tElement)State1, &GenTabs_PatternTablePtr->A[Pattern].DContext)) {
                  {
                    SHORTINT B_31 = 1, B_32 = Dfa_DStateCount;

                    if (B_31 <= B_32)
                      for (State2 = B_31;; State2 += 1) {
                        if (State1 == Dfa_GetDefault(State2)) {
                          Sets_Include(&GenTabs_PatternTablePtr->A[Pattern].DContext, (Sets_tElement)State2);
                        }
                        if (State2 >= B_32) break;
                      }
                  }
                }
                if (State1 >= B_30) break;
              }
          }
        }
        if (Pattern >= B_28) break;
      }
  }
}

static void InvertMapping
# ifdef __STDC__
()
# else
()
# endif
{
  SHORTCARD Pattern;
  Dfa_DStateRange State;

  {
    SHORTCARD B_33 = 0, B_34 = GenTabs_PatternCount;

    if (B_33 <= B_34)
      for (Pattern = B_33;; Pattern += 1) {
        Sets_MakeSet(&GenTabs_PatternTablePtr->A[Pattern].Finals, (Sets_tElement)Dfa_DStateCount);
        if (Pattern >= B_34) break;
      }
  }
  {
    SHORTINT B_35 = 1, B_36 = Dfa_DStateCount;

    if (B_35 <= B_36)
      for (State = B_35;; State += 1) {
        Dfa_GetDSemantics(State, &dSemantics);
        if (Sets_IsEmpty(dSemantics)) {
          Sets_Include(&GenTabs_PatternTablePtr->A[0].Finals, (Sets_tElement)State);
        } else {
          Pattern = Sets_Minimum(&dSemantics);
          Sets_Include(&GenTabs_PatternTablePtr->A[Pattern].Finals, (Sets_tElement)State);
        }
        if (State >= B_36) break;
      }
  }
  IsComputedFinals = TRUE;
}

static void CheckTables
# ifdef __STDC__
()
# else
()
# endif
{
  DefTable_DefRange Definition;
  Idents_tIdent Ident;
  SHORTCARD StartState;

  {
    LONGINT B_37 = 1, B_38 = DefTable_DefCount;

    if (B_37 <= B_38)
      for (Definition = B_37;; Definition += 1) {
        if (DefTable_GetKind(Definition) == DefTable_Start) {
          DefTable_GetStartDef(Definition, &Ident, &StartState);
          CheckStartState(StartState, Ident, FALSE);
          if (GenTabs_LeftJustUsed) {
            CheckStartState(StartState + 1, Ident, TRUE);
          }
        }
        if (Definition >= B_38) break;
      }
  }
}

static void CheckStartState
# ifdef __STDC__
(SHORTCARD StartState, Idents_tIdent Ident, BOOLEAN LeftJust)
# else
(StartState, Ident, LeftJust)
SHORTCARD StartState;
Idents_tIdent Ident;
BOOLEAN LeftJust;
# endif
{
  CHAR Ch;
  Dfa_DStateRange DState;
  Sets_tSet Undefined, Semantics;
  Strings_tString String;
  INTEGER Count;

  Sets_MakeSet(&Undefined, ORD(Dfa_OldLastCh));
  Sets_MakeSet(&Semantics, (Sets_tElement)GenTabs_PatternCount);
  Sets_Union(&Undefined, Classes_Unused);
  {
    CHAR B_39 = Dfa_FirstCh, B_40 = Dfa_LastCh;

    if (B_39 <= B_40)
      for (Ch = B_39;; Ch += 1) {
        DState = Dfa_GetTable((SHORTINT)StartState, Ch);
        if (DState == Dfa_DNoState) {
          if (Ch <= Classes_ClassCount) {
            Sets_Union(&Undefined, Classes_ClassMemPtr->A[Ch]);
          } else {
            Sets_Include(&Undefined, ORD(Classes_ToChar.A[Ch]));
          }
        } else {
          Dfa_GetDSemantics(DState, &Semantics);
          if (Sets_IsEmpty(Semantics)) {
            if (Ch <= Classes_ClassCount) {
              Sets_Union(&Undefined, Classes_ClassMemPtr->A[Ch]);
            } else {
              Sets_Include(&Undefined, ORD(Classes_ToChar.A[Ch]));
            }
          }
        }
        if (Ch >= B_40) break;
      }
  }
  if (!Sets_IsEmpty(Undefined)) {
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Warning: in start state ", 24L);
    Idents_GetString(Ident, &String);
    Strings_WriteS((System_tFile)IO_StdError, &String);
    if (LeftJust) {
      IO_WriteS((System_tFile)IO_StdError, (STRING)" the default action may be triggered by (left justified):", 57L);
    } else {
      IO_WriteS((System_tFile)IO_StdError, (STRING)" the default action may be triggered by:", 40L);
    }
    IO_WriteNl((System_tFile)IO_StdError);
    Count = 0;
    while (!Sets_IsEmpty(Undefined)) {
      Ch = CHR(Sets_Extract(&Undefined));
      IO_WriteC((System_tFile)IO_StdError, ' ');
      if ('!' <= Ch && Ch <= '~') {
        IO_WriteC((System_tFile)IO_StdError, '\'');
        IO_WriteC((System_tFile)IO_StdError, Ch);
        IO_WriteC((System_tFile)IO_StdError, '\'');
      } else {
        IO_WriteC((System_tFile)IO_StdError, '\\');
        IO_WriteI((System_tFile)IO_StdError, (LONGINT)ORD(Ch), 0L);
      }
      INC(Count);
      if (Count == 16) {
        IO_WriteNl((System_tFile)IO_StdError);
        Count = 0;
      }
    }
    IO_WriteNl((System_tFile)IO_StdError);
  }
  Sets_ReleaseSet(&Semantics);
  Sets_ReleaseSet(&Undefined);
}

static void WritePattern
# ifdef __STDC__
()
# else
()
# endif
{
  SHORTCARD Pattern;

  {
    SHORTCARD B_41 = 0, B_42 = GenTabs_PatternCount - 2;

    if (B_41 <= B_42)
      for (Pattern = B_41;; Pattern += 1) {
        if (GenTabs_PatternTablePtr->A[Pattern].ContextLng != GenTabs_NoContext) {
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Pattern, ContextLng", 19L);
          IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Pattern, 5L);
          IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)GenTabs_PatternTablePtr->A[Pattern].ContextLng, 5L);
          if (GenTabs_PatternTablePtr->A[Pattern].ContextLng == GenTabs_VariableContext) {
            if (IsComputedNContext) {
              IO_WriteS((System_tFile)IO_StdOutput, (STRING)" NContext ", 10L);
              Sets_WriteSet((System_tFile)IO_StdOutput, GenTabs_PatternTablePtr->A[Pattern].NContext);
            }
            if (IsComputedDContext) {
              IO_WriteS((System_tFile)IO_StdOutput, (STRING)" DContext ", 10L);
              Sets_WriteSet((System_tFile)IO_StdOutput, GenTabs_PatternTablePtr->A[Pattern].DContext);
            }
          }
          if (IsComputedFinals) {
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)" Finals ", 8L);
            Sets_WriteSet((System_tFile)IO_StdOutput, GenTabs_PatternTablePtr->A[Pattern].Finals);
          }
          IO_WriteNl((System_tFile)IO_StdOutput);
        }
        if (Pattern >= B_42) break;
      }
  }
}

static void WriteStatistics
# ifdef __STDC__
()
# else
()
# endif
{
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Start States	", 13L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)GenTabs_StartStateCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Definitions	", 12L);
  IO_WriteI((System_tFile)IO_StdOutput, DefTable_DefCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Rules		", 7L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)GenTabs_RuleCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Patterns	", 9L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)GenTabs_PatternCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Classes		", 9L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)ORD(Classes_ClassCount), 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"LastCh		", 8L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)ORD(Dfa_LastCh), 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Transitions	", 12L);
  IO_WriteI((System_tFile)IO_StdOutput, Nfa_TransitionCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Leafs		", 7L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)GenTabs_LeafCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"NFA States	", 11L);
  IO_WriteI((System_tFile)IO_StdOutput, Nfa_NStateCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Minimize Savings", 16L);
  IO_WriteI((System_tFile)IO_StdOutput, Dfa_MinimizeSavings, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Ambiguous States", 16L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Dfa_MaxAmbiguousState, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Nodes		", 7L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)GenTabs_NodeCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"DFA States	", 11L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Dfa_DStateCount, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Sentinel Savings", 16L);
  IO_WriteI((System_tFile)IO_StdOutput, SentinelSavings, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Default Savings	", 16L);
  IO_WriteI((System_tFile)IO_StdOutput, Dfa_DefaultSavings, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Table Entries	", 14L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)ScanTabs_TableEntries, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Table Size	", 11L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)ScanTabs_TableSize, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
  IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Memory used	", 12L);
  IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Memory_MemoryUsed, 6L);
  IO_WriteNl((System_tFile)IO_StdOutput);
}

void GenTabs_GenerateTables
# ifdef __STDC__
(SHORTCARD DebugLevel, BOOLEAN ReduceCaseSize, BOOLEAN Warnings, SHORTINT Optimize)
# else
(DebugLevel, ReduceCaseSize, Warnings, Optimize)
SHORTCARD DebugLevel;
BOOLEAN ReduceCaseSize, Warnings;
SHORTINT Optimize;
# endif
{
  SHORTINT i;

  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"Start		", 7L);
  }
  IsComputedNContext = FALSE;
  IsComputedDContext = FALSE;
  IsComputedFinals = FALSE;
  INC(GenTabs_RuleCount);
  INC(GenTabs_PatternCount);
  GenTabs_EobAction = GenTabs_PatternCount;
  INC(GenTabs_RuleCount);
  INC(GenTabs_PatternCount);
  GenTabs_DefaultAction = GenTabs_PatternCount;
  GenTabs_RuleToCodeSize = GenTabs_RuleCount + 1;
  DynArray_MakeArray((ADDRESS *)&GenTabs_RuleToCodePtr, &GenTabs_RuleToCodeSize, (LONGINT)sizeof(GenTabs_CodeInfo));
  GenTabs_PatternTableSize = GenTabs_PatternCount + 1;
  DynArray_MakeArray((ADDRESS *)&GenTabs_PatternTablePtr, &GenTabs_PatternTableSize, (LONGINT)sizeof(GenTabs_PatternInfo));
  GenTabs_PatternTablePtr->A[0].ContextLng = GenTabs_NoContext;
  Sets_MakeSet(&dSemantics, (Sets_tElement)GenTabs_PatternCount);
  ComputeNfa();
  if (DebugLevel >= 15) {
    Nfa_WriteNfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"ComputeNfa	", 11L);
  }
  ComputeDfa();
  if (DebugLevel >= 14) {
    Dfa_WriteDfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"ComputeDfa	", 11L);
  }
  Dfa_MinimizeDfa();
  if (DebugLevel >= 13) {
    Dfa_WriteDfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"MinimizeDfa	", 12L);
  }
  Dfa_EobDefaultState = Dfa_MakeDState();
  Dfa_ComputeSuccGraph();
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"ComputeSuccGraph", 16L);
  }
  Dfa_ComputeAmbiguousStates();
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"ComputeAmbiguous", 16L);
  }
  Dfa_ComputeCyclicStates();
  if (DebugLevel >= 12) {
    Sets_WriteSet((System_tFile)IO_StdOutput, Dfa_AmbiguousStates);
    IO_WriteNl((System_tFile)IO_StdOutput);
    Sets_WriteSet((System_tFile)IO_StdOutput, Dfa_CyclicStates);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"ComputeCyclicSta", 16L);
  }
  Dfa_ComputeStartSets();
  if (DebugLevel >= 11) {
    Dfa_WriteDfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"ComputeStartSets", 16L);
  }
  Dfa_EobState = Dfa_MakeDState();
  Sets_AssignElmt(&dSemantics, (Sets_tElement)GenTabs_EobAction);
  Dfa_PutDSemantics(Dfa_EobState, dSemantics);
  Sets_AssignElmt(&dSemantics, (Sets_tElement)GenTabs_DefaultAction);
  Dfa_PutDSemantics(Dfa_MakeDState(), dSemantics);
  AddConstantREs();
  if (DebugLevel >= 10) {
    Dfa_WriteDfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"AddConstantREs	", 15L);
  }
  UpdateContext();
  if (DebugLevel >= 9) {
    Dfa_WriteDfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"UpdateContext	", 14L);
  }
  Dfa_SaveEobTransitions();
  if (DebugLevel >= 8) {
    Dfa_WriteDfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"SaveEobTransitio", 16L);
  }
  SaveSentinels();
  if (DebugLevel >= 7) {
    Dfa_WriteDfa();
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"SaveSentinels	", 14L);
  }
  if (Optimize > 0) {
    i = 1;
    while (i <= Dfa_MaxAmbiguousState) {
      Dfa_ComputeDefaults(i, (SHORTINT)General_Min((LONGINT)Dfa_MaxAmbiguousState, (LONGINT)(i + Optimize - 1)));
      if (DebugLevel >= 2) {
        Times_WriteStepTime((STRING)"ComputeDefaults	", 16L);
      }
      INC1(i, Optimize);
    }
  }
  if (DebugLevel >= 6) {
    Dfa_WriteDfa();
    WritePattern();
  }
  InvertMapping();
  if (DebugLevel >= 5) {
    WritePattern();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"InvertMapping	", 14L);
  }
  ScanTabs_MakeTables(ReduceCaseSize);
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"MakeTables	", 11L);
  }
  ScanTabs_CompressTables(Optimize);
  if (DebugLevel >= 4) {
    ScanTabs_WriteTables();
  }
  if (DebugLevel >= 2) {
    Times_WriteStepTime((STRING)"CompressTables	", 15L);
  }
  if (ScanGen_Language == ScanGen_Modula) {
    ScanTabs_PutTables(ReduceCaseSize);
    if (DebugLevel >= 2) {
      Times_WriteStepTime((STRING)"PutTables	", 10L);
    }
  }
  if (DebugLevel >= 3) {
    ScanTabs_QueryTables();
  }
  if (Warnings) {
    CheckTables();
    if (DebugLevel >= 2) {
      Times_WriteStepTime((STRING)"CheckTables	", 12L);
    }
  }
  if (DebugLevel >= 1) {
    WriteStatistics();
  }
}

void GenTabs__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Tree__init();
    Texts__init();
    Sets__init();
    Positions__init();
    General__init();
    Memory__init();
    DynArray__init();
    Strings__init();
    StringMem__init();
    Times__init();
    Sets__init();
    IO__init();
    Layout__init();
    DefTable__init();
    Tree__init();
    Nfa__init();
    Dfa__init();
    Traces__init();
    ScanTabs__init();
    ScanGen__init();
    Classes__init();
    Strings__init();
    Idents__init();

  }
}
