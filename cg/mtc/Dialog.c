#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Order
#include "Order.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Dialog
#include "Dialog.h"
#endif


typedef struct S_1 {
    SHORTCARD C_0_A, B;
    Tree_tTree Rule;
} tDepend;
static Sets_tSet Cyclics;
static SHORTCARD ClassCount;
static Strings_tString String;
static LONGINT MarkSize;
static struct S_2 {
    tDepend A[10000 + 1];
} *MarkPtr;
static INTEGER MarkCount;
static LONGINT TraceSize;
static struct S_3 {
    tDepend A[10000 + 1];
} *TracePtr;
static INTEGER TraceCount;
static BOOLEAN Find ARGS((SHORTCARD a, SHORTCARD b, Tree_tTree rule));
static BOOLEAN ForallClasses ARGS((Tree_tTree t));
static BOOLEAN ForallAttributes ARGS((Tree_tTree t));
static void FindPath ARGS((SHORTCARD a, SHORTCARD b, Tree_tTree rule));
static void Menue ARGS(());
struct S_4 {
    CHAR A[64 + 1];
};

static Tree_tTree *G_1_UserClass;
static Tree_tTree *G_2_rule;
static SHORTCARD *G_3_b;
static SHORTCARD *G_4_a;

static BOOLEAN ForallClasses
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_1 = &(*G_2_rule)->U_1.V_5.Class;

      {
        register Tree_yChild *W_2 = &W_1->Instance->A[*G_4_a - 1].Selector->U_1.V_9.Child;

        if (Find(*G_4_a - W_1->AttrCount - W_2->InstOffset, *G_3_b - W_1->AttrCount - W_2->InstOffset, t)) {
          return TRUE;
        }
      }
    }
    if (ForallClasses(t->U_1.V_5.Class.Extensions)) {
      return TRUE;
    }
    return ForallClasses(t->U_1.V_5.Class.Next);
  } else {
    return FALSE;
  }
}

static BOOLEAN ForallAttributes
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    if (ForallAttributes(t->U_1.V_5.Class.BaseClass)) {
      return TRUE;
    } else {
      return ForallAttributes(t->U_1.V_5.Class.Attributes);
    }
    break;
  case Tree_Child:;
    {
      register Tree_yClass *W_3 = &(*G_1_UserClass)->U_1.V_5.Class;

      {
        register Tree_yChild *W_4 = &t->U_1.V_9.Child;

        if (W_4->Class == *G_2_rule && Find(W_3->AttrCount + W_4->InstOffset + *G_4_a, W_3->AttrCount + W_4->InstOffset + *G_3_b, *G_1_UserClass)) {
          return TRUE;
        }
      }
    }
    return ForallAttributes(t->U_1.V_9.Child.Next);
    break;
  case Tree_Attribute:;
    return ForallAttributes(t->U_1.V_10.Attribute.Next);
    break;
  case Tree_ActionPart:;
    return ForallAttributes(t->U_1.V_11.ActionPart.Next);
    break;
  default :
    return FALSE;
    break;
  }
}

static BOOLEAN Find
# ifdef __STDC__
(SHORTCARD a, SHORTCARD b, Tree_tTree rule)
# else
(a, b, rule)
SHORTCARD a, b;
Tree_tTree rule;
# endif
{
  SHORTCARD c, UserIndex;
  INTEGER i, markCount, traceCount;
  Relations_tRelation DPClosure;
  Tree_tTree UserClass;
  Tree_tTree *L_1;
  Tree_tTree *L_2;
  SHORTCARD *L_3;
  SHORTCARD *L_4;

  L_1 = G_1_UserClass;
  G_1_UserClass = &UserClass;
  L_2 = G_2_rule;
  G_2_rule = &rule;
  L_3 = G_3_b;
  G_3_b = &b;
  L_4 = G_4_a;
  G_4_a = &a;
  {
    register Tree_yClass *W_5 = &rule->U_1.V_5.Class;

    if (!(IN(Tree_cSNC, Tree_GrammarClass) && Relations_IsRelated((LONGINT)a, (LONGINT)b, W_5->DNC) || IN(Tree_cLNC, Tree_GrammarClass) && Relations_IsRelated((LONGINT)a, (LONGINT)b, W_5->SNC))) {
      G_1_UserClass = L_1;
      G_2_rule = L_2;
      G_3_b = L_3;
      G_4_a = L_4;
      return FALSE;
    }
    {
      LONGINT B_1 = 1, B_2 = MarkCount;

      if (B_1 <= B_2)
        for (i = B_1;; i += 1) {
          {
            register tDepend *W_6 = &MarkPtr->A[i];

            if (a == W_6->C_0_A && b == W_6->B && rule == W_6->Rule) {
              G_1_UserClass = L_1;
              G_2_rule = L_2;
              G_3_b = L_3;
              G_4_a = L_4;
              return FALSE;
            }
          }
          if (i >= B_2) break;
        }
    }
    INC(MarkCount);
    if (MarkCount == MarkSize) {
      DynArray_ExtendArray((ADDRESS *)&MarkPtr, &MarkSize, (LONGINT)sizeof(tDepend));
    }
    {
      register tDepend *W_7 = &MarkPtr->A[MarkCount];

      W_7->C_0_A = a;
      W_7->B = b;
      W_7->Rule = rule;
    }
    markCount = MarkCount;
    traceCount = TraceCount;
    Relations_MakeRelation(&DPClosure, (LONGINT)W_5->InstCount, (LONGINT)W_5->InstCount);
    Relations_Assign(&DPClosure, W_5->DP);
    Relations_Closure(&DPClosure);
    if (Relations_IsRelated((LONGINT)a, (LONGINT)b, DPClosure)) {
      {
        SHORTCARD B_3 = 1, B_4 = W_5->InstCount;

        if (B_3 <= B_4)
          for (c = B_3;; c += 1) {
            if (Relations_IsRelated((LONGINT)a, (LONGINT)c, W_5->DP) && (Relations_IsRelated((LONGINT)c, (LONGINT)b, DPClosure) || c == b)) {
              INC(TraceCount);
              if (TraceCount == TraceSize) {
                DynArray_ExtendArray((ADDRESS *)&TracePtr, &TraceSize, (LONGINT)sizeof(tDepend));
              }
              {
                register tDepend *W_8 = &TracePtr->A[TraceCount];

                W_8->C_0_A = a;
                W_8->B = c;
                W_8->Rule = rule;
              }
              Relations_ReleaseRelation(&DPClosure);
              {
                BOOLEAN R_1 = c == b || Find(c, b, rule);

                G_1_UserClass = L_1;
                G_2_rule = L_2;
                G_3_b = L_3;
                G_4_a = L_4;
                return R_1;
              }
            }
            if (c >= B_4) break;
          }
      }
    }
    Relations_ReleaseRelation(&DPClosure);
    if (IN(Tree_Right, W_5->Instance->A[a - 1].Properties) && IN(Tree_Right, W_5->Instance->A[b - 1].Properties) && W_5->Instance->A[a - 1].Selector == W_5->Instance->A[b - 1].Selector && W_5->Instance->A[a - 1].Selector != Tree_NoTree) {
      {
        register Tree_yChild *W_9 = &W_5->Instance->A[a - 1].Selector->U_1.V_9.Child;

        if (Find(a - W_5->AttrCount - W_9->InstOffset, b - W_5->AttrCount - W_9->InstOffset, W_9->Class)) {
          G_1_UserClass = L_1;
          G_2_rule = L_2;
          G_3_b = L_3;
          G_4_a = L_4;
          return TRUE;
        }
        if (ForallClasses(W_9->Class->U_1.V_5.Class.Extensions)) {
          G_1_UserClass = L_1;
          G_2_rule = L_2;
          G_3_b = L_3;
          G_4_a = L_4;
          return TRUE;
        }
      }
    }
    if (IN(Tree_Left, W_5->Instance->A[a - 1].Properties) && IN(Tree_Left, W_5->Instance->A[b - 1].Properties)) {
      {
        SHORTCARD B_5 = 1, B_6 = ClassCount;

        if (B_5 <= B_6)
          for (UserIndex = B_5;; UserIndex += 1) {
            if (Sets_IsElement((Sets_tElement)UserIndex, &W_5->Users)) {
              UserClass = Order_IndexToClass->A[UserIndex];
              if (ForallAttributes(UserClass)) {
                G_1_UserClass = L_1;
                G_2_rule = L_2;
                G_3_b = L_3;
                G_4_a = L_4;
                return TRUE;
              }
            }
            if (UserIndex >= B_6) break;
          }
      }
    }
    if (IN(Tree_cLNC, Tree_GrammarClass)) {
      {
        SHORTCARD B_7 = 1, B_8 = W_5->InstCount;

        if (B_7 <= B_8)
          for (c = B_7;; c += 1) {
            if (Relations_IsRelated((LONGINT)a, (LONGINT)c, W_5->SNC) && Relations_IsRelated((LONGINT)c, (LONGINT)b, W_5->SNC) && Find(a, c, rule) && Find(c, b, rule)) {
              G_1_UserClass = L_1;
              G_2_rule = L_2;
              G_3_b = L_3;
              G_4_a = L_4;
              return TRUE;
            }
            if (c >= B_8) break;
          }
      }
    }
    if (IN(Tree_cSNC, Tree_GrammarClass)) {
      {
        SHORTCARD B_9 = 1, B_10 = W_5->InstCount;

        if (B_9 <= B_10)
          for (c = B_9;; c += 1) {
            if (Relations_IsRelated((LONGINT)a, (LONGINT)c, W_5->DNC) && Relations_IsRelated((LONGINT)c, (LONGINT)b, W_5->DNC) && Find(a, c, rule) && Find(c, b, rule)) {
              G_1_UserClass = L_1;
              G_2_rule = L_2;
              G_3_b = L_3;
              G_4_a = L_4;
              return TRUE;
            }
            if (c >= B_10) break;
          }
      }
    }
    MarkCount = markCount;
    TraceCount = traceCount;
    G_1_UserClass = L_1;
    G_2_rule = L_2;
    G_3_b = L_3;
    G_4_a = L_4;
    return FALSE;
  }
}

static void FindPath
# ifdef __STDC__
(SHORTCARD a, SHORTCARD b, Tree_tTree rule)
# else
(a, b, rule)
SHORTCARD a, b;
Tree_tTree rule;
# endif
{
  INTEGER i;

  {
    register Tree_yClass *W_10 = &rule->U_1.V_5.Class;

    Idents_WriteIdent((System_tFile)IO_StdOutput, W_10->Name);
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"	", 1L);
    Tree_WriteName(W_10->Instance->A[a - 1]);
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"	", 1L);
    Tree_WriteName(W_10->Instance->A[b - 1]);
    IO_WriteNl((System_tFile)IO_StdOutput);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
  MarkSize = 32;
  DynArray_MakeArray((ADDRESS *)&MarkPtr, &MarkSize, (LONGINT)sizeof(tDepend));
  MarkCount = 0;
  TraceSize = 32;
  DynArray_MakeArray((ADDRESS *)&TracePtr, &TraceSize, (LONGINT)sizeof(tDepend));
  TraceCount = 0;
  if (Find(a, b, rule)) {
    {
      LONGINT B_11 = 1, B_12 = TraceCount;

      if (B_11 <= B_12)
        for (i = B_11;; i += 1) {
          {
            register tDepend *W_11 = &TracePtr->A[i];

            Idents_WriteIdent((System_tFile)IO_StdOutput, W_11->Rule->U_1.V_5.Class.Name);
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"	", 1L);
            Tree_WriteName(W_11->Rule->U_1.V_5.Class.Instance->A[W_11->C_0_A - 1]);
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"	", 1L);
            Tree_WriteName(W_11->Rule->U_1.V_5.Class.Instance->A[W_11->B - 1]);
            IO_WriteNl((System_tFile)IO_StdOutput);
          }
          if (i >= B_12) break;
        }
    }
  }
  DynArray_ReleaseArray((ADDRESS *)&MarkPtr, &MarkSize, (LONGINT)sizeof(tDepend));
  DynArray_ReleaseArray((ADDRESS *)&TracePtr, &TraceSize, (LONGINT)sizeof(tDepend));
}

static void Menue
# ifdef __STDC__
()
# else
()
# endif
{
  Tree_f = IO_StdOutput;
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" Dialog System", 14L);
  IO_WriteNl(Tree_f);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)"   <name>          select current node type (rule)", 50L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" t <name>          select current node type (rule)", 50L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" a <name>[:<name>] select current attribute instance a", 54L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" b <name>[:<name>] select current attribute instance b", 54L);
  IO_WriteNl(Tree_f);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" P print dependency relation DP  for complete node type", 55L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" p print dependency relation DP  for current attribute instance", 63L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" S print dependency relation SNC for complete node type", 55L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" s print dependency relation SNC for current attribute instance", 63L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" N print dependency relation DNC for complete node type", 55L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" n print dependency relation DNC for current attribute instance", 63L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" O print dependency relation OAG for complete node type", 55L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" o print dependency relation OAG for current attribute instance", 63L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" C print dependencies introduced for total order for complete node type", 71L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" c print dependencies introduced for total order for cyclic attributes", 70L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" G print attribute instances sorted by declaration order", 56L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" E print attribute instances sorted by evaluation order", 55L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" V print visit sequence", 23L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" F search for and print dependency path between attributes a and b", 66L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" M print summary of node type (rule) from source", 48L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" Q browse internal data structure of complete attribute grammar", 63L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" q browse internal data structure of current node type", 54L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" h print menue for dialog system", 32L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" ? print current state", 22L);
  IO_WriteNl(Tree_f);
  IO_WriteS(Tree_f, (STRING)" x exit dialog system", 21L);
  IO_WriteNl(Tree_f);
  IO_WriteNl(Tree_f);
}

void Dialog_Dialog
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  CHAR Com, Ch;
  Tree_tTree Class, ChildsClass;
  Tree_tTree Attribute;
  struct S_4 Name0, Name1, Name2;
  INTEGER Length0, Length1, Length2;
  Idents_tIdent Ident;
  SHORTCARD a, b, Offset;

  Menue();
  Class = Tree_NoTree;
  a = 0;
  b = 0;
  for (;;) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"? ", 2L);
    Ch = IO_ReadC((System_tFile)IO_StdInput);
    Length0 = -1;
    while (Ch > ' ' && Ch != ':') {
      INC(Length0);
      Name0.A[Length0] = Ch;
      Ch = IO_ReadC((System_tFile)IO_StdInput);
    }
    Name0.A[Length0 + 1] = '\0';
    while (Ch <= ' ' && Ch != '\n' || Ch == ':') {
      Ch = IO_ReadC((System_tFile)IO_StdInput);
    }
    Length1 = -1;
    while (Ch > ' ' && Ch != ':') {
      INC(Length1);
      Name1.A[Length1] = Ch;
      Ch = IO_ReadC((System_tFile)IO_StdInput);
    }
    Name1.A[Length1 + 1] = '\0';
    while (Ch <= ' ' && Ch != '\n' || Ch == ':') {
      Ch = IO_ReadC((System_tFile)IO_StdInput);
    }
    Length2 = -1;
    while (Ch > ' ' && Ch != ':') {
      INC(Length2);
      Name2.A[Length2] = Ch;
      Ch = IO_ReadC((System_tFile)IO_StdInput);
    }
    Name2.A[Length2 + 1] = '\0';
    while (Ch != '\n') {
      Ch = IO_ReadC((System_tFile)IO_StdInput);
    }
    if (Length0 == 0) {
      Com = Name0.A[0];
      switch (Com) {
      case 't':;
      case 'T':;
        Strings_ArrayToString(Name1.A, 65L, &String);
        Ident = Idents_MakeIdent(&String);
        Class = Tree_IdentifyClass(t->U_1.V_26.Ag.Classes, Ident);
        if (Class == Tree_NoTree) {
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"unknown node type: ", 19L);
          Strings_WriteL((System_tFile)IO_StdOutput, &String);
        }
        break;
      case 'a':;
      case 'A':;
      case 'b':;
      case 'B':;
        Strings_ArrayToString(Name1.A, 65L, &String);
        Ident = Idents_MakeIdent(&String);
        Attribute = Tree_IdentifyAttribute(Class, Ident);
        if (Attribute == Tree_NoTree) {
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"unknown attribute: ", 19L);
          Strings_WriteL((System_tFile)IO_StdOutput, &String);
        } else {
          if (Com == 'a' || Com == 'A') {
            a = Attribute->U_1.V_9.Child.AttrIndex;
          } else {
            b = Attribute->U_1.V_9.Child.AttrIndex;
          }
          if (Length2 >= 0) {
            ChildsClass = Attribute->U_1.V_9.Child.Class;
            if (ChildsClass != Tree_NoTree) {
              Strings_ArrayToString(Name2.A, 65L, &String);
              Ident = Idents_MakeIdent(&String);
              Offset = Class->U_1.V_5.Class.AttrCount + Attribute->U_1.V_9.Child.InstOffset;
              Attribute = Tree_IdentifyAttribute(ChildsClass, Ident);
              if (Attribute == Tree_NoTree) {
                IO_WriteS((System_tFile)IO_StdOutput, (STRING)"unknown attribute: ", 19L);
                Strings_WriteL((System_tFile)IO_StdOutput, &String);
              } else {
                if (Com == 'a' || Com == 'A') {
                  a = Offset + Attribute->U_1.V_9.Child.AttrIndex;
                } else {
                  b = Offset + Attribute->U_1.V_9.Child.AttrIndex;
                }
              }
            }
          }
        }
        break;
      case 'P':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.DP, Tree_MaxSet);
        break;
      case 'p':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.DP, Tree_MaxSet);
        break;
      case 'S':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.SNC, Tree_MaxSet);
        break;
      case 's':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.SNC, Tree_MaxSet);
        break;
      case 'N':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.DNC, Tree_MaxSet);
        break;
      case 'n':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.DNC, Tree_MaxSet);
        break;
      case 'O':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.OAG, Tree_MaxSet);
        break;
      case 'o':;
        Tree_WriteDependencies(Class, Class->U_1.V_5.Class.OAG, Tree_MaxSet);
        break;
      case 'C':;
        if (Class != Tree_NoTree && IN(Tree_cDNC, Tree_GrammarClass)) {
          {
            register Tree_yClass *W_12 = &Class->U_1.V_5.Class;

            Relations_MakeRelation(&W_12->Part, (LONGINT)W_12->InstCount, (LONGINT)W_12->InstCount);
            Relations_Assign(&W_12->Part, W_12->OAG);
            Relations_Difference(&W_12->Part, W_12->DNC);
            Tree_WriteDependencies(Class, W_12->Part, Tree_MaxSet);
            IO_WriteNl((System_tFile)IO_StdOutput);
            Relations_ReleaseRelation(&W_12->Part);
          }
        }
        break;
      case 'c':;
        if (Class != Tree_NoTree && IN(Tree_cDNC, Tree_GrammarClass)) {
          {
            register Tree_yClass *W_13 = &Class->U_1.V_5.Class;

            Relations_MakeRelation(&W_13->Part, (LONGINT)W_13->InstCount, (LONGINT)W_13->InstCount);
            Sets_MakeSet(&Cyclics, (Sets_tElement)W_13->InstCount);
            Relations_GetCyclics(W_13->OAG, &Cyclics);
            Relations_Assign(&W_13->Part, W_13->OAG);
            Relations_Difference(&W_13->Part, W_13->DNC);
            Tree_WriteDependencies(Class, W_13->Part, Cyclics);
            Relations_ReleaseRelation(&W_13->Part);
            Sets_ReleaseSet(&Cyclics);
          }
        }
        break;
      case 'D':;
      case 'd':;
      case 'G':;
      case 'g':;
        Order_WriteOrderDecl(Class);
        break;
      case 'E':;
      case 'e':;
        if (IN(Tree_cOAG, Tree_GrammarClass)) {
          Order_WriteOrderEval(Class);
        }
        break;
      case 'V':;
      case 'v':;
        if (IN(Tree_cOAG, Tree_GrammarClass)) {
          Order_WriteVisitSequence(Class);
        }
        break;
      case 'F':;
      case 'f':;
        if (Class != Tree_NoTree && 1 <= a && a <= Class->U_1.V_5.Class.InstCount && 1 <= b && b <= Class->U_1.V_5.Class.InstCount) {
          FindPath(a, b, Class);
        }
        break;
      case 'M':;
      case 'm':;
        Tree_WriteClass(Class);
        break;
      case 'Q':;
        Tree_QueryTree(t);
        break;
      case 'q':;
        Tree_QueryTree(Class);
        break;
      case 'h':;
      case 'H':;
        Menue();
        break;
      case 'x':;
      case 'X':;
        goto EXIT_1;
        break;
      case '?':;
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"node type: ", 11L);
        if (Class != Tree_NoTree) {
          {
            register Tree_yClass *W_14 = &Class->U_1.V_5.Class;

            Idents_WriteIdent((System_tFile)IO_StdOutput, W_14->Name);
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)", a: ", 5L);
            if (1 <= a && a <= Class->U_1.V_5.Class.InstCount) {
              Tree_WriteName(W_14->Instance->A[a - 1]);
              IO_WriteS((System_tFile)IO_StdOutput, (STRING)" = ", 3L);
              IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)a, 0L);
            } else {
              IO_WriteS((System_tFile)IO_StdOutput, (STRING)"?", 1L);
            }
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)", b: ", 5L);
            if (1 <= b && b <= Class->U_1.V_5.Class.InstCount) {
              Tree_WriteName(W_14->Instance->A[b - 1]);
              IO_WriteS((System_tFile)IO_StdOutput, (STRING)" = ", 3L);
              IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)b, 0L);
            } else {
              IO_WriteS((System_tFile)IO_StdOutput, (STRING)"?", 1L);
            }
          }
        } else {
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"?, a: ?, b: ?", 13L);
        }
        IO_WriteNl((System_tFile)IO_StdOutput);
        break;
      default :
        Strings_ArrayToString(Name0.A, 65L, &String);
        Ident = Idents_MakeIdent(&String);
        Class = Tree_IdentifyClass(t->U_1.V_26.Ag.Classes, Ident);
        if (Class == Tree_NoTree) {
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)"unknown node type: ", 19L);
          Strings_WriteL((System_tFile)IO_StdOutput, &String);
        }
        break;
      }
    } else {
      Strings_ArrayToString(Name0.A, 65L, &String);
      Ident = Idents_MakeIdent(&String);
      Class = Tree_IdentifyClass(t->U_1.V_26.Ag.Classes, Ident);
      if (Class == Tree_NoTree) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"unknown node type: ", 19L);
        Strings_WriteL((System_tFile)IO_StdOutput, &String);
      }
    }
  } EXIT_1:;
}

void Dialog__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Tree__init();
    DynArray__init();
    IO__init();
    Strings__init();
    Idents__init();
    Sets__init();
    Relations__init();
    Tree__init();
    Order__init();
    Tree__init();

  }
}
