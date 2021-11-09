#include "SYSTEM_.h"

#ifndef DEFINITION_Convert
#include "Convert.h"
#endif

#ifndef DEFINITION_Complete
#include "Complete.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Environs
#include "Environs.h"
#endif

#ifndef DEFINITION_Grammar
#include "Grammar.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Reduced
#include "Reduced.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

BOOLEAN Semantics_Correct;

#define eAlreadyDeclared   31
#define eNotDeclared   32
#define eNoClass   33
#define eNoNode   34
#define eCodingUsed   35
#define eCodeUnexpected   36
#define eNodeNameUnexpected   37
#define eNoMainClass   39
#define eCyclicClass   40
#define eTooFewSons   42
#define eTooManySons   43
#define eNoSubClass   44
#define eLParExpected   45
#define eIdOrStrExpected   46
#define eDoNotCallCond   47
#define eDoNotCallCost   48
#define eNoSelector   49
#define eExtended   50
#define eUnReachable   51
#define eUnDerivable   52
#define eNoFunction   53
#define eNotInDomain   54
#define eIdentExpected   55
#define eIllegalPattern   56
#define eAlreadyInClass   57
#define eNotInFDomain   58
static BOOLEAN IsString ARGS((Idents_tIdent name));
static void Spec1 ARGS((Tree_tTree t));
static void Classes1 ARGS((Tree_tTree t));
static void Nodes1 ARGS((Tree_tTree t));
static void Functions1 ARGS((Tree_tTree t));
static void Spec2 ARGS((Tree_tTree t));
static void Classes2 ARGS((Tree_tTree t));
static void Nodes2 ARGS((Tree_tTree t, Idents_tIdent clid));
static void Functions2 ARGS((Tree_tTree t));
static void Directives2 ARGS((Tree_tTree t));
static void Pattern2 ARGS((Tree_tTree t));
static void Patterns2 ARGS((Tree_tTree t));
static void Domain2 ARGS((Tree_tTree t, Sets_tSet *domainset));
static void Spec3 ARGS((Tree_tTree t));
static void Classes3 ARGS((Tree_tTree t));
static void Nodes3 ARGS((Tree_tTree t, Idents_tIdent clid, Sets_tSet *codes));
static void Sons3 ARGS((Tree_tTree t, Idents_tIdent class, Idents_tIdent node));
static void Functions3 ARGS((Tree_tTree t));
static void Directives3 ARGS((Tree_tTree t));
static void Pattern3 ARGS((Tree_tTree t, BOOLEAN *ok));
static void Patterns3 ARGS((Tree_tTree t, Idents_tIdent node, Positions_tPosition nopos, BOOLEAN *ok));
static void Spec4 ARGS((Tree_tTree t));
static void Classes4 ARGS((Tree_tTree t));
static void Nodes4 ARGS((Tree_tTree t, Idents_tIdent clid));
static void Sons4 ARGS((Tree_tTree t, Idents_tIdent class, Idents_tIdent node, Positions_tPosition nopos));
static void Functions4 ARGS((Tree_tTree t));
static void Directives4 ARGS((Tree_tTree t, Queues_tQueue *path, Environs_tFunction f));
static void Pattern4 ARGS((Tree_tTree t, INTEGER no, Idents_tIdent class, Queues_tQueue *path, Patterns_tPattern *pat));
static void Patterns4 ARGS((Tree_tTree t, INTEGER no, Queues_tQueue *path, Idents_tIdent node, Patterns_tPattern *pat));
static void Condition4 ARGS((Tree_tTree t, INTEGER no));
static void Costs4 ARGS((Tree_tTree t, INTEGER no));
static void Instr4 ARGS((Tree_tTree t, INTEGER no));
static Tree_tSelMode SelMode ARGS((Tree_tTree t));
static Idents_tIdent FunctionSelector ARGS((Tree_tTree t, INTEGER no, INTEGER kind));
static BOOLEAN RParOrComma ARGS((Tree_tTree t));
static void Spec5 ARGS((Tree_tTree t));
static void Classes5 ARGS((Tree_tTree t));
static void Functions5 ARGS((Tree_tTree t));
static void Domain5 ARGS((Tree_tTree t, Environs_tFunction f));
static void Directives5 ARGS((Tree_tTree t, Sets_tSet domain, Idents_tIdent name));
static void Pattern5 ARGS((Tree_tTree t, INTEGER number));


void Semantics_Semantic
# ifdef __STDC__
()
# else
()
# endif
{
  Types_BeginTypes();
  Spec1(Parser_AST);
  if (Semantics_Correct) {
    Grammar_BeginGrammar();
    Spec2(Parser_AST);
  }
  if (Semantics_Correct) {
    Grammar_CompleteSubclasses();
    Grammar_FixMainClasses();
    Types_UnionEssential(Parser_AST->U_1.V_4.Spec.functions->U_1.V_19.Function.domainset);
    Spec3(Parser_AST);
  }
  if (Semantics_Correct) {
    Spec4(Parser_AST);
  }
  if (Semantics_Correct) {
    Grammar_MakePatNumbers(Environs_MaxDirective());
    Reduced_TestReduced(Parser_AST->U_1.V_4.Spec.functions->U_1.V_19.Function.domainset);
    Spec5(Parser_AST);
  }
}

static BOOLEAN IsString
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  Strings_tString s;
  CHAR c;

  Idents_GetString(name, &s);
  c = Strings_Char(&s, 1);
  return c == '"' || c == '\'';
}

static void Spec1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  {
    register Tree_ySpec *W_1 = &t->U_1.V_4.Spec;

    Types_MakeTransformation(W_1->name);
    Classes1(W_1->classes);
    if (W_1->functions->U_1.V_1.Kind == Tree_Function0) {
      Semantics_Correct = FALSE;
      Errors_ErrorMessageI((LONGCARD)eNoFunction, (LONGCARD)Errors_eError, W_1->pos, (LONGCARD)Errors_eIdent, ADR(W_1->name));
    }
    Functions1(W_1->functions);
  }
}

static void Classes1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_2 = &t->U_1.V_7.Class;

      if (Types_Type(W_2->clid) != Types_cNoType) {
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eAlreadyDeclared, (LONGCARD)Errors_eError, W_2->clpos, (LONGCARD)Errors_eIdent, ADR(W_2->clid));
        W_2->correct = FALSE;
      } else {
        Types_MakeClass(W_2->clid);
      }
      Nodes1(W_2->nodes);
      t = W_2->classes;
    }
  }
}

static void Nodes1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Node) {
    {
      register Tree_yNode *W_3 = &t->U_1.V_10.Node;

      switch (Types_Type(W_3->name)) {
      case Types_cNoType:;
        Types_MakeNode(W_3->name);
        break;
      case Types_cNode:;
        break;
      default :
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNoNode, (LONGCARD)Errors_eError, W_3->napos, (LONGCARD)Errors_eIdent, ADR(W_3->name));
        W_3->correct = FALSE;
        break;
      }
      t = W_3->nodes;
    }
  }
}

static void Functions1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_4 = &t->U_1.V_19.Function;

      if (Types_Type(W_4->name) != Types_cNoType) {
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eAlreadyDeclared, (LONGCARD)Errors_eError, W_4->napos, (LONGCARD)Errors_eIdent, ADR(W_4->name));
      } else {
        Types_MakeFunction(W_4->name);
      }
      t = W_4->functions;
    }
  }
}

static void Spec2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  {
    register Tree_ySpec *W_5 = &t->U_1.V_4.Spec;

    Classes2(W_5->classes);
    Functions2(W_5->functions);
  }
}

static void Classes2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_6 = &t->U_1.V_7.Class;

      if (W_6->correct) {
        switch (Types_Type(W_6->suid)) {
        case Types_cClass:;
          Grammar_SetSuperClass(W_6->clid, W_6->suid);
          break;
        case Types_cNoType:;
          if (W_6->suid != Scanner_NoIdent) {
            Semantics_Correct = FALSE;
            Errors_ErrorMessageI((LONGCARD)eNotDeclared, (LONGCARD)Errors_eError, W_6->supos, (LONGCARD)Errors_eIdent, ADR(W_6->suid));
            W_6->correct = FALSE;
          }
          break;
        default :
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eNoClass, (LONGCARD)Errors_eError, W_6->supos, (LONGCARD)Errors_eIdent, ADR(W_6->suid));
          W_6->correct = FALSE;
          break;
        }
        Nodes2(W_6->nodes, W_6->clid);
      }
      t = W_6->classes;
    }
  }
}

static void Nodes2
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent clid)
# else
(t, clid)
Tree_tTree t;
Idents_tIdent clid;
# endif
{
  Sets_tSet Nodes;

  while (t->U_1.V_1.Kind == Tree_Node) {
    {
      register Tree_yNode *W_7 = &t->U_1.V_10.Node;

      if (W_7->correct) {
        Sets_MakeSet(&Nodes, (Sets_tElement)Scanner_MaxIdent);
        Grammar_NodesOfClass(clid, &Nodes);
        if (Sets_IsElement((Sets_tElement)W_7->name, &Nodes)) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eAlreadyInClass, (LONGCARD)Errors_eError, W_7->napos, (LONGCARD)Errors_eIdent, ADR(W_7->name));
          W_7->correct = FALSE;
        } else {
          Grammar_Connect(W_7->name, clid);
        }
        Sets_ReleaseSet(&Nodes);
      }
      t = W_7->nodes;
    }
  }
}

static void Functions2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_8 = &t->U_1.V_19.Function;

      Directives2(W_8->directives);
      Sets_MakeSet(&W_8->domainset, (Sets_tElement)Scanner_MaxIdent);
      Domain2(W_8->domain, &W_8->domainset);
      t = W_8->functions;
    }
  }
}

static void Directives2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Directive) {
    {
      register Tree_yDirective *W_9 = &t->U_1.V_28.Directive;

      Pattern2(W_9->pattern);
      t = W_9->directives;
    }
  }
}

static void Pattern2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Pattern) {
    {
      register Tree_yPattern *W_10 = &t->U_1.V_31.Pattern;

      switch (Types_Type(W_10->ident)) {
      case Types_cNode:;
        break;
      case Types_cNoType:;
        if (W_10->ident != Scanner_NoIdent) {
          Errors_ErrorMessageI((LONGCARD)eNotDeclared, (LONGCARD)Errors_eError, W_10->idpos, (LONGCARD)Errors_eIdent, ADR(W_10->ident));
        }
        Semantics_Correct = FALSE;
        W_10->correct = FALSE;
        break;
      default :
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNoNode, (LONGCARD)Errors_eError, W_10->idpos, (LONGCARD)Errors_eIdent, ADR(W_10->ident));
        W_10->correct = FALSE;
        break;
      }
      Patterns2(W_10->patterns);
    }
  } else {
    {
      register Tree_yPattern1 *W_11 = &t->U_1.V_30.Pattern1;

      switch (Types_Type(W_11->ident)) {
      case Types_cClass:;
        break;
      case Types_cNoType:;
        if (W_11->ident != Scanner_NoIdent) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eNotDeclared, (LONGCARD)Errors_eError, W_11->idpos, (LONGCARD)Errors_eIdent, ADR(W_11->ident));
          W_11->correct = FALSE;
        }
        break;
      default :
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNoClass, (LONGCARD)Errors_eError, W_11->idpos, (LONGCARD)Errors_eIdent, ADR(W_11->ident));
        W_11->correct = FALSE;
        break;
      }
    }
  }
}

static void Patterns2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Patterns) {
    {
      register Tree_yPatterns *W_12 = &t->U_1.V_34.Patterns;

      Pattern2(W_12->pattern);
      t = W_12->patterns;
    }
  }
}

static void Domain2
# ifdef __STDC__
(Tree_tTree t, Sets_tSet *domainset)
# else
(t, domainset)
Tree_tTree t;
Sets_tSet *domainset;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Ident) {
    {
      register Tree_yIdent *W_13 = &t->U_1.V_25.Ident;

      switch (Types_Type(W_13->ident)) {
      case Types_cNoType:;
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNotDeclared, (LONGCARD)Errors_eError, W_13->idpos, (LONGCARD)Errors_eIdent, ADR(W_13->ident));
        break;
      case Types_cClass:;
        Sets_Include(domainset, (Sets_tElement)W_13->ident);
        break;
      case Types_cNode:;
      case Types_cFunction:;
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNoClass, (LONGCARD)Errors_eError, W_13->idpos, (LONGCARD)Errors_eIdent, ADR(W_13->ident));
        break;
      }
      t = W_13->domain;
    }
  }
}

static void Spec3
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  {
    register Tree_ySpec *W_14 = &t->U_1.V_4.Spec;

    Classes3(W_14->classes);
    Functions3(W_14->functions);
  }
}

static void Classes3
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Sets_tSet codes;

  Sets_MakeSet(&codes, (Sets_tElement)Scanner_MaxValue);
  while (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_15 = &t->U_1.V_7.Class;

      if (W_15->correct) {
        Nodes3(W_15->nodes, W_15->clid, &codes);
      }
      t = W_15->classes;
    }
  }
  Sets_ReleaseSet(&codes);
}

static void Nodes3
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent clid, Sets_tSet *codes)
# else
(t, clid, codes)
Tree_tTree t;
Idents_tIdent clid;
Sets_tSet *codes;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Node) {
    {
      register Tree_yNode *W_16 = &t->U_1.V_10.Node;

      if (W_16->correct) {
        if (Grammar_MainClass(W_16->name) == Scanner_NoIdent) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eNoMainClass, (LONGCARD)Errors_eError, W_16->napos, (LONGCARD)Errors_eIdent, ADR(W_16->name));
          W_16->correct = FALSE;
        } else if (Grammar_MainClass(W_16->name) == clid) {
          if (Types_Type(W_16->ident) != Types_cNoType) {
            Semantics_Correct = FALSE;
            Errors_ErrorMessageI((LONGCARD)eAlreadyDeclared, (LONGCARD)Errors_eError, W_16->napos, (LONGCARD)Errors_eIdent, ADR(W_16->name));
            W_16->correct = FALSE;
          } else {
            if (W_16->ident != Scanner_NoIdent) {
              Types_MakeNodeId(W_16->ident);
              Grammar_SetNodeIdent(W_16->name, W_16->ident);
            } else if (IsString(W_16->name)) {
              Semantics_Correct = FALSE;
              Errors_ErrorMessage((LONGCARD)eIdentExpected, (LONGCARD)Errors_eError, W_16->napos);
              W_16->correct = FALSE;
            }
          }
          Sons3(W_16->sons, clid, W_16->name);
        } else {
          if (W_16->ident != Scanner_NoIdent) {
            Semantics_Correct = FALSE;
            Errors_ErrorMessageI((LONGCARD)eNodeNameUnexpected, (LONGCARD)Errors_eError, W_16->idpos, (LONGCARD)Errors_eIdent, ADR(W_16->ident));
          }
        }
      }
      t = W_16->nodes;
    }
  }
}

static void Sons3
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent class, Idents_tIdent node)
# else
(t, class, node)
Tree_tTree t;
Idents_tIdent class, node;
# endif
{
  Tree_tTree tt;
  INTEGER a;
  Grammar_tLayout layout;

  tt = t;
  a = 0;
  while (tt->U_1.V_1.Kind == Tree_Son) {
    INC(a);
    tt = tt->U_1.V_13.Son.sons;
  }
  Grammar_SetArity(node, a);
  layout = Grammar_CreateLayout(node, class);
  a = 0;
  while (t->U_1.V_1.Kind == Tree_Son) {
    {
      register Tree_ySon *W_17 = &t->U_1.V_13.Son;

      INC(a);
      switch (Types_Type(W_17->ident)) {
      case Types_cClass:;
        Grammar_SetSonClass(layout, a, W_17->ident);
        Types_SetEssential(W_17->ident);
        break;
      case Types_cNoType:;
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNotDeclared, (LONGCARD)Errors_eError, W_17->idpos, (LONGCARD)Errors_eIdent, ADR(W_17->ident));
        W_17->correct = FALSE;
        break;
      default :
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNoClass, (LONGCARD)Errors_eError, W_17->idpos, (LONGCARD)Errors_eIdent, ADR(W_17->ident));
        W_17->correct = FALSE;
        break;
      }
      if (W_17->name == Scanner_NoIdent) {
        W_17->correct = FALSE;
      } else {
        Grammar_SetSonName(node, a, W_17->name);
      }
      t = W_17->sons;
    }
  }
}

static void Functions3
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_18 = &t->U_1.V_19.Function;

      W_18->funct = Environs_MakeFunctEnv(W_18->name, W_18->domainset);
      Directives3(W_18->directives);
      t = W_18->functions;
    }
  }
}

static void Directives3
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Directive) {
    {
      register Tree_yDirective *W_19 = &t->U_1.V_28.Directive;

      Pattern3(W_19->pattern, &W_19->correct);
      t = W_19->directives;
    }
  }
}

static void Pattern3
# ifdef __STDC__
(Tree_tTree t, BOOLEAN *ok)
# else
(t, ok)
Tree_tTree t;
BOOLEAN *ok;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Pattern) {
    {
      register Tree_yPattern *W_20 = &t->U_1.V_31.Pattern;

      if (W_20->correct) {
        Patterns3(W_20->patterns, W_20->ident, W_20->idpos, &W_20->correct);
      }
      *ok = W_20->correct;
    }
  } else {
    {
      register Tree_yPattern1 *W_21 = &t->U_1.V_30.Pattern1;

      *ok = W_21->correct;
    }
  }
}

static void Patterns3
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent node, Positions_tPosition nopos, BOOLEAN *ok)
# else
(t, node, nopos, ok)
Tree_tTree t;
Idents_tIdent node;
Positions_tPosition nopos;
BOOLEAN *ok;
# endif
{
  INTEGER p;
  BOOLEAN correct;

  *ok = TRUE;
  p = 0;
  while (t->U_1.V_1.Kind == Tree_Patterns) {
    {
      register Tree_yPatterns *W_22 = &t->U_1.V_34.Patterns;

      INC(p);
      Pattern3(W_22->pattern, &correct);
      *ok = *ok && correct;
      t = W_22->patterns;
    }
  }
  if (p != Grammar_Arity(node)) {
    if (Grammar_Arity(node) == Scanner_NoValue) {
    } else if (p < Grammar_Arity(node)) {
      Semantics_Correct = FALSE;
      Errors_ErrorMessageI((LONGCARD)eTooFewSons, (LONGCARD)Errors_eError, nopos, (LONGCARD)Errors_eIdent, ADR(node));
    } else {
      Semantics_Correct = FALSE;
      Errors_ErrorMessageI((LONGCARD)eTooManySons, (LONGCARD)Errors_eError, nopos, (LONGCARD)Errors_eIdent, ADR(node));
    }
    *ok = FALSE;
  }
}

static void Spec4
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  {
    register Tree_ySpec *W_23 = &t->U_1.V_4.Spec;

    Classes4(W_23->classes);
    Functions4(W_23->functions);
  }
}

static void Classes4
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_24 = &t->U_1.V_7.Class;

      if (W_24->correct) {
        if (Grammar_IsSubclass(W_24->clid, W_24->clid)) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eCyclicClass, (LONGCARD)Errors_eError, W_24->clpos, (LONGCARD)Errors_eIdent, ADR(W_24->clid));
        }
        Nodes4(W_24->nodes, W_24->clid);
      }
      t = W_24->classes;
    }
  }
}

static void Nodes4
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent clid)
# else
(t, clid)
Tree_tTree t;
Idents_tIdent clid;
# endif
{
  Idents_tIdent mainclass;
  Idents_tIdent cl;

  while (t->U_1.V_1.Kind == Tree_Node) {
    {
      register Tree_yNode *W_25 = &t->U_1.V_10.Node;

      if (W_25->correct) {
        mainclass = Grammar_MainClass(W_25->name);
        if (mainclass == Scanner_NoIdent) {
        } else if (clid != mainclass) {
          cl = clid;
          for (;;) {
            if (Types_Essential(cl)) {
              Semantics_Correct = FALSE;
              Errors_ErrorMessageI((LONGCARD)eExtended, (LONGCARD)Errors_eError, W_25->napos, (LONGCARD)Errors_eIdent, ADR(W_25->name));
              goto EXIT_1;
            }
            cl = Grammar_SuperClass(cl);
            if (cl == mainclass) {
              goto EXIT_1;
            }
          } EXIT_1:;
          Sons4(W_25->sons, clid, W_25->name, W_25->napos);
        }
      }
      t = W_25->nodes;
    }
  }
}

static void Sons4
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent class, Idents_tIdent node, Positions_tPosition nopos)
# else
(t, class, node, nopos)
Tree_tTree t;
Idents_tIdent class, node;
Positions_tPosition nopos;
# endif
{
  Tree_tTree tt;
  INTEGER a;
  Idents_tIdent mainclass, sonclass;
  Grammar_tLayout mainlayout, layout;

  tt = t;
  a = 0;
  while (tt->U_1.V_1.Kind == Tree_Son) {
    {
      register Tree_ySon *W_26 = &tt->U_1.V_13.Son;

      INC(a);
      switch (Types_Type(W_26->ident)) {
      case Types_cClass:;
        break;
      case Types_cNoType:;
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNotDeclared, (LONGCARD)Errors_eError, W_26->idpos, (LONGCARD)Errors_eIdent, ADR(W_26->ident));
        W_26->correct = FALSE;
        break;
      default :
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eNoClass, (LONGCARD)Errors_eError, W_26->idpos, (LONGCARD)Errors_eIdent, ADR(W_26->ident));
        W_26->correct = FALSE;
        break;
      }
      tt = W_26->sons;
    }
  }
  if (a != Grammar_Arity(node)) {
    if (a > Grammar_Arity(node)) {
      Semantics_Correct = FALSE;
      Errors_ErrorMessageI((LONGCARD)eTooManySons, (LONGCARD)Errors_eError, nopos, (LONGCARD)Errors_eIdent, ADR(node));
    } else {
      Semantics_Correct = FALSE;
      Errors_ErrorMessageI((LONGCARD)eTooFewSons, (LONGCARD)Errors_eError, nopos, (LONGCARD)Errors_eIdent, ADR(node));
    }
  } else {
    mainclass = Grammar_MainClass(node);
    if (mainclass != Scanner_NoIdent) {
      mainlayout = Grammar_Layout(node, mainclass);
      layout = Grammar_CreateLayout(node, class);
      a = 0;
      while (t->U_1.V_1.Kind == Tree_Son) {
        {
          register Tree_ySon *W_27 = &t->U_1.V_13.Son;

          INC(a);
          sonclass = Grammar_SonClass(mainlayout, a);
          if (W_27->correct && sonclass != Scanner_NoIdent) {
            if (W_27->ident == sonclass || Grammar_IsSubclass(W_27->ident, sonclass)) {
              Grammar_SetSonClass(layout, a, W_27->ident);
            } else {
              Semantics_Correct = FALSE;
              Errors_ErrorMessageI((LONGCARD)eNoSubClass, (LONGCARD)Errors_eError, W_27->idpos, (LONGCARD)Errors_eIdent, ADR(mainclass));
              Grammar_SetSonClass(layout, a, sonclass);
            }
          }
          t = W_27->sons;
        }
      }
    }
  }
}

static void Functions4
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Queues_tQueue path;

  Queues_MakeQueue(&path);
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_28 = &t->U_1.V_19.Function;

      Directives4(W_28->directives, &path, W_28->funct);
      t = W_28->functions;
    }
  }
  Queues_ReleaseQueue(&path);
}

static void Directives4
# ifdef __STDC__
(Tree_tTree t, Queues_tQueue *path, Environs_tFunction f)
# else
(t, path, f)
Tree_tTree t;
Queues_tQueue *path;
Environs_tFunction f;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Directive) {
    {
      register Tree_yDirective *W_29 = &t->U_1.V_28.Directive;

      if (W_29->correct) {
        W_29->number = Environs_MakeDirective(f);
        Pattern4(W_29->pattern, W_29->number, Scanner_NoIdent, path, &W_29->pat);
        W_29->pat = Patterns_NormPattern(W_29->pat);
        Condition4(W_29->condition, W_29->number);
        Costs4(W_29->costs, W_29->number);
        Instr4(W_29->instr, W_29->number);
        W_29->iter = Environs_HeadCalled(W_29->number);
      }
      t = W_29->directives;
    }
  }
}

static void Pattern4
# ifdef __STDC__
(Tree_tTree t, INTEGER no, Idents_tIdent class, Queues_tQueue *path, Patterns_tPattern *pat)
# else
(t, no, class, path, pat)
Tree_tTree t;
INTEGER no;
Idents_tIdent class;
Queues_tQueue *path;
Patterns_tPattern *pat;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Pattern) {
    {
      register Tree_yPattern *W_30 = &t->U_1.V_31.Pattern;

      if (W_30->ident == Scanner_NoIdent) {
        if (class != Scanner_NoIdent) {
          Queues_Append(path, Convert_IdToAdr(class));
        }
      } else {
        Queues_Append(path, Convert_IdToAdr(Grammar_NodeIdent(W_30->ident)));
      }
      *pat = Patterns_MakePattern(W_30->ident);
      if (W_30->sel != Scanner_NoIdent) {
        if (Environs_Defined(no, W_30->sel)) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eAlreadyDeclared, (LONGCARD)Errors_eError, W_30->sepos, (LONGCARD)Errors_eIdent, ADR(W_30->sel));
        }
      }
      Environs_DefineAccess(no, *path, W_30->sel, W_30->ident, FALSE);
      Patterns4(W_30->patterns, no, path, W_30->ident, pat);
      if (W_30->sel != Scanner_NoIdent) {
        Environs_DefineSelPat(no, W_30->sel, Patterns_NormPattern(Patterns_CopyPattern(*pat)));
      }
      Queues_ClearLast(path);
    }
  } else {
    {
      register Tree_yPattern1 *W_31 = &t->U_1.V_30.Pattern1;

      if (W_31->ident == Scanner_NoIdent) {
        Queues_Append(path, Convert_IdToAdr(class));
        *pat = Patterns_MakePattern(class);
      } else {
        Queues_Append(path, Convert_IdToAdr(W_31->ident));
        *pat = Patterns_MakePattern(W_31->ident);
        if (!(class == Scanner_NoIdent || class == W_31->ident || Grammar_IsSubclass(W_31->ident, class))) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eNoSubClass, (LONGCARD)Errors_eError, W_31->idpos, (LONGCARD)Errors_eIdent, ADR(class));
        }
      }
      if (W_31->sel != Scanner_NoIdent) {
        if (Environs_Defined(no, W_31->sel)) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessageI((LONGCARD)eAlreadyDeclared, (LONGCARD)Errors_eError, W_31->sepos, (LONGCARD)Errors_eIdent, ADR(W_31->sel));
        }
      }
      Environs_DefineAccess(no, *path, W_31->sel, W_31->ident, (BOOLEAN)(W_31->ident == class));
      if (W_31->sel != Scanner_NoIdent) {
        Environs_DefineSelPat(no, W_31->sel, Patterns_NormPattern(Patterns_CopyPattern(*pat)));
      }
      Queues_ClearLast(path);
    }
  }
}

static void Patterns4
# ifdef __STDC__
(Tree_tTree t, INTEGER no, Queues_tQueue *path, Idents_tIdent node, Patterns_tPattern *pat)
# else
(t, no, path, node, pat)
Tree_tTree t;
INTEGER no;
Queues_tQueue *path;
Idents_tIdent node;
Patterns_tPattern *pat;
# endif
{
  INTEGER p;
  Grammar_tLayout layout;
  Patterns_tPattern sonpat;

  p = 0;
  layout = Grammar_Layout(node, Grammar_MainClass(node));
  while (t->U_1.V_1.Kind == Tree_Patterns) {
    {
      register Tree_yPatterns *W_32 = &t->U_1.V_34.Patterns;

      INC(p);
      Queues_Append(path, Convert_IdToAdr(Grammar_SonName(node, p)));
      Pattern4(W_32->pattern, no, Grammar_SonClass(layout, p), path, &sonpat);
      Patterns_SetPatternSon(*pat, p, sonpat);
      t = W_32->patterns;
      Queues_ClearLast(path);
    }
  }
}

static void Condition4
# ifdef __STDC__
(Tree_tTree t, INTEGER no)
# else
(t, no)
Tree_tTree t;
INTEGER no;
# endif
{
  Idents_tIdent sel;

  if (t->U_1.V_1.Kind != Tree_CondF) {
    return;
  }
  t = t->U_1.V_37.CondF.code;
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdStr:;
      if (Environs_Defined(no, t->U_1.V_43.CdStr.ident)) {
        t->U_1.V_43.CdStr.mode = SelMode(t->U_1.V_43.CdStr.code);
      } else {
        t->U_1.V_43.CdStr.mode = Tree_cNoSel;
      }
      t = t->U_1.V_43.CdStr.code;
      break;
    case Tree_CdId:;
      if (Environs_Defined(no, t->U_1.V_44.CdId.ident)) {
        t->U_1.V_44.CdId.mode = SelMode(t->U_1.V_44.CdId.code);
      } else {
        t->U_1.V_44.CdId.mode = Tree_cNoSel;
      }
      if (Types_Type(t->U_1.V_44.CdId.ident) == Types_cFunction) {
        sel = FunctionSelector(t->U_1.V_44.CdId.code, no, (LONGINT)Tree_condition);
        if (sel != Scanner_NoIdent) {
          if (Environs_IsHead(no, sel)) {
            Semantics_Correct = FALSE;
            Errors_ErrorMessageI((LONGCARD)eDoNotCallCond, (LONGCARD)Errors_eError, t->U_1.V_44.CdId.pos, (LONGCARD)Errors_eIdent, ADR(t->U_1.V_44.CdId.ident));
          } else {
            Environs_CallFunction(no, sel, t->U_1.V_44.CdId.ident);
          }
        }
      }
      t = t->U_1.V_44.CdId.code;
      break;
    case Tree_CdDot:;
      t = t->U_1.V_45.CdDot.code;
      break;
    case Tree_CdLPar:;
      t = t->U_1.V_47.CdLPar.code;
      break;
    case Tree_CdRPar:;
      t = t->U_1.V_48.CdRPar.code;
      break;
    case Tree_CdLBra:;
      t = t->U_1.V_49.CdLBra.code;
      break;
    case Tree_CdRBra:;
      t = t->U_1.V_50.CdRBra.code;
      break;
    case Tree_CdSpa:;
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdComma:;
      t = t->U_1.V_46.CdComma.code;
      break;
    case Tree_CdRst:;
      t = t->U_1.V_53.CdRst.code;
      break;
    case Tree_CdEnd:;
      goto EXIT_2;
      break;
    }
  } EXIT_2:;
}

static void Costs4
# ifdef __STDC__
(Tree_tTree t, INTEGER no)
# else
(t, no)
Tree_tTree t;
INTEGER no;
# endif
{
  Idents_tIdent sel;

  if (t->U_1.V_1.Kind != Tree_CostF) {
    return;
  }
  t = t->U_1.V_41.CostF.code;
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdStr:;
      if (Environs_Defined(no, t->U_1.V_43.CdStr.ident)) {
        t->U_1.V_43.CdStr.mode = SelMode(t->U_1.V_43.CdStr.code);
      } else {
        t->U_1.V_43.CdStr.mode = Tree_cNoSel;
      }
      t = t->U_1.V_43.CdStr.code;
      break;
    case Tree_CdId:;
      if (Environs_Defined(no, t->U_1.V_44.CdId.ident)) {
        t->U_1.V_44.CdId.mode = SelMode(t->U_1.V_44.CdId.code);
      } else {
        t->U_1.V_44.CdId.mode = Tree_cNoSel;
      }
      if (Types_Type(t->U_1.V_44.CdId.ident) == Types_cFunction) {
        Semantics_Correct = FALSE;
        Errors_ErrorMessageI((LONGCARD)eDoNotCallCost, (LONGCARD)Errors_eError, t->U_1.V_44.CdId.pos, (LONGCARD)Errors_eIdent, ADR(t->U_1.V_44.CdId.ident));
      }
      t = t->U_1.V_44.CdId.code;
      break;
    case Tree_CdDot:;
      t = t->U_1.V_45.CdDot.code;
      break;
    case Tree_CdLPar:;
      t = t->U_1.V_47.CdLPar.code;
      break;
    case Tree_CdRPar:;
      t = t->U_1.V_48.CdRPar.code;
      break;
    case Tree_CdLBra:;
      t = t->U_1.V_49.CdLBra.code;
      break;
    case Tree_CdRBra:;
      t = t->U_1.V_50.CdRBra.code;
      break;
    case Tree_CdSpa:;
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdComma:;
      t = t->U_1.V_46.CdComma.code;
      break;
    case Tree_CdRst:;
      t = t->U_1.V_53.CdRst.code;
      break;
    case Tree_CdEnd:;
      goto EXIT_3;
      break;
    }
  } EXIT_3:;
}

static void Instr4
# ifdef __STDC__
(Tree_tTree t, INTEGER no)
# else
(t, no)
Tree_tTree t;
INTEGER no;
# endif
{
  Idents_tIdent sel;

  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdStr:;
      if (Environs_Defined(no, t->U_1.V_43.CdStr.ident)) {
        t->U_1.V_43.CdStr.mode = SelMode(t->U_1.V_43.CdStr.code);
      } else {
        t->U_1.V_43.CdStr.mode = Tree_cNoSel;
      }
      t = t->U_1.V_43.CdStr.code;
      break;
    case Tree_CdId:;
      if (Environs_Defined(no, t->U_1.V_44.CdId.ident)) {
        t->U_1.V_44.CdId.mode = SelMode(t->U_1.V_44.CdId.code);
      } else {
        t->U_1.V_44.CdId.mode = Tree_cNoSel;
      }
      if (Types_Type(t->U_1.V_44.CdId.ident) == Types_cFunction) {
        sel = FunctionSelector(t->U_1.V_44.CdId.code, no, (LONGINT)Tree_code);
        if (sel != Scanner_NoIdent) {
          if (!Environs_InDomain(t->U_1.V_44.CdId.ident, Environs_SelPattern(no, sel))) {
            Semantics_Correct = FALSE;
            Errors_ErrorMessageI((LONGCARD)eNotInFDomain, (LONGCARD)Errors_eError, t->U_1.V_44.CdId.pos, (LONGCARD)Errors_eIdent, ADR(sel));
          }
          Environs_CallFunction(no, sel, t->U_1.V_44.CdId.ident);
        }
      }
      t = t->U_1.V_44.CdId.code;
      break;
    case Tree_CdDot:;
      t = t->U_1.V_45.CdDot.code;
      break;
    case Tree_CdLPar:;
      t = t->U_1.V_47.CdLPar.code;
      break;
    case Tree_CdRPar:;
      t = t->U_1.V_48.CdRPar.code;
      break;
    case Tree_CdLBra:;
      t = t->U_1.V_49.CdLBra.code;
      break;
    case Tree_CdRBra:;
      t = t->U_1.V_50.CdRBra.code;
      break;
    case Tree_CdSpa:;
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdComma:;
      t = t->U_1.V_46.CdComma.code;
      break;
    case Tree_CdRst:;
      t = t->U_1.V_53.CdRst.code;
      break;
    case Tree_CdEnd:;
      goto EXIT_4;
      break;
    }
  } EXIT_4:;
}

static Tree_tSelMode SelMode
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdStr:;
    case Tree_CdId:;
      return Tree_cTreeSel;
      break;
    case Tree_CdDot:;
      return Tree_cSel;
      break;
    case Tree_CdLPar:;
    case Tree_CdRPar:;
    case Tree_CdLBra:;
    case Tree_CdRBra:;
      return Tree_cTreeSel;
      break;
    case Tree_CdSpa:;
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdComma:;
      return Tree_cTreeSel;
      break;
    case Tree_CdRst:;
      return Tree_cTreeSel;
      break;
    case Tree_CdEnd:;
      return Tree_cTreeSel;
      break;
    }
  } EXIT_5:;
}

static Idents_tIdent FunctionSelector
# ifdef __STDC__
(Tree_tTree t, INTEGER no, INTEGER kind)
# else
(t, no, kind)
Tree_tTree t;
INTEGER no;
INTEGER kind;
# endif
{
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdSpa:;
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdLPar:;
      t = t->U_1.V_47.CdLPar.code;
      goto EXIT_6;
      break;
    case Tree_CdStr:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_43.CdStr.pos);
      goto EXIT_6;
      break;
    case Tree_CdId:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_44.CdId.pos);
      goto EXIT_6;
      break;
    case Tree_CdDot:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_45.CdDot.pos);
      goto EXIT_6;
      break;
    case Tree_CdRPar:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_48.CdRPar.pos);
      goto EXIT_6;
      break;
    case Tree_CdLBra:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_49.CdLBra.pos);
      goto EXIT_6;
      break;
    case Tree_CdRBra:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_50.CdRBra.pos);
      goto EXIT_6;
      break;
    case Tree_CdComma:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_46.CdComma.pos);
      goto EXIT_6;
      break;
    case Tree_CdRst:;
      Errors_ErrorMessage((LONGCARD)eLParExpected, (LONGCARD)Errors_eError, t->U_1.V_53.CdRst.pos);
      goto EXIT_6;
      break;
    case Tree_CdEnd:;
      goto EXIT_6;
      break;
    }
  } EXIT_6:;
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdSpa:;
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdStr:;
      if (!Environs_Defined(no, t->U_1.V_43.CdStr.ident) || !RParOrComma(t->U_1.V_43.CdStr.code)) {
        Semantics_Correct = FALSE;
        Errors_ErrorMessage((LONGCARD)eNoSelector, (LONGCARD)Errors_eError, t->U_1.V_43.CdStr.pos);
        return Scanner_NoIdent;
      } else {
        return t->U_1.V_43.CdStr.ident;
      }
      break;
    case Tree_CdId:;
      if (!Environs_Defined(no, t->U_1.V_44.CdId.ident) || !RParOrComma(t->U_1.V_44.CdId.code)) {
        if (kind == Tree_condition) {
          Semantics_Correct = FALSE;
          Errors_ErrorMessage((LONGCARD)eNoSelector, (LONGCARD)Errors_eError, t->U_1.V_44.CdId.pos);
          return Scanner_NoIdent;
        } else {
          Errors_ErrorMessage((LONGCARD)eNoSelector, (LONGCARD)Errors_eWarning, t->U_1.V_44.CdId.pos);
          return Scanner_NoIdent;
        }
      } else {
        return t->U_1.V_44.CdId.ident;
      }
      break;
    case Tree_CdDot:;
      Semantics_Correct = FALSE;
      Errors_ErrorMessage((LONGCARD)eIdOrStrExpected, (LONGCARD)Errors_eError, t->U_1.V_45.CdDot.pos);
      return Scanner_NoIdent;
      break;
    case Tree_CdLPar:;
      Semantics_Correct = FALSE;
      Errors_ErrorMessage((LONGCARD)eIdOrStrExpected, (LONGCARD)Errors_eError, t->U_1.V_47.CdLPar.pos);
      return Scanner_NoIdent;
      break;
    case Tree_CdRPar:;
      Semantics_Correct = FALSE;
      Errors_ErrorMessage((LONGCARD)eIdOrStrExpected, (LONGCARD)Errors_eError, t->U_1.V_48.CdRPar.pos);
      return Scanner_NoIdent;
      break;
    case Tree_CdLBra:;
      Semantics_Correct = FALSE;
      Errors_ErrorMessage((LONGCARD)eIdOrStrExpected, (LONGCARD)Errors_eError, t->U_1.V_49.CdLBra.pos);
      return Scanner_NoIdent;
      break;
    case Tree_CdRBra:;
      Semantics_Correct = FALSE;
      Errors_ErrorMessage((LONGCARD)eIdOrStrExpected, (LONGCARD)Errors_eError, t->U_1.V_50.CdRBra.pos);
      return Scanner_NoIdent;
      break;
    case Tree_CdComma:;
      Semantics_Correct = FALSE;
      Errors_ErrorMessage((LONGCARD)eIdOrStrExpected, (LONGCARD)Errors_eError, t->U_1.V_46.CdComma.pos);
      return Scanner_NoIdent;
      break;
    case Tree_CdRst:;
      Semantics_Correct = FALSE;
      Errors_ErrorMessage((LONGCARD)eIdOrStrExpected, (LONGCARD)Errors_eError, t->U_1.V_53.CdRst.pos);
      return Scanner_NoIdent;
      break;
    case Tree_CdEnd:;
      return Scanner_NoIdent;
      break;
    }
  } EXIT_7:;
}

static BOOLEAN RParOrComma
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdRPar:;
    case Tree_CdComma:;
      return TRUE;
      break;
    case Tree_CdStr:;
    case Tree_CdId:;
    case Tree_CdLPar:;
    case Tree_CdLBra:;
    case Tree_CdRBra:;
    case Tree_CdRst:;
    case Tree_CdEnd:;
    case Tree_CdDot:;
      return FALSE;
      break;
    case Tree_CdSpa:;
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      t = t->U_1.V_52.CdCom.code;
      break;
    }
  } EXIT_8:;
}

static void Spec5
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  {
    register Tree_ySpec *W_33 = &t->U_1.V_4.Spec;

    Classes5(W_33->classes);
    Functions5(W_33->functions);
  }
}

static void Classes5
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_34 = &t->U_1.V_7.Class;

      if (Sets_IsElement((Sets_tElement)W_34->clid, &Reduced_UnReachable)) {
        Errors_ErrorMessageI((LONGCARD)eUnReachable, (LONGCARD)Errors_eError, W_34->clpos, (LONGCARD)Errors_eIdent, ADR(W_34->clid));
      }
      if (Sets_IsElement((Sets_tElement)W_34->clid, &Reduced_UnDerivable)) {
        Errors_ErrorMessageI((LONGCARD)eUnDerivable, (LONGCARD)Errors_eError, W_34->clpos, (LONGCARD)Errors_eIdent, ADR(W_34->clid));
      }
      t = W_34->classes;
    }
  }
}

static void Functions5
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_35 = &t->U_1.V_19.Function;

      Directives5(W_35->directives, W_35->domainset, W_35->name);
      Domain5(W_35->domain, W_35->funct);
      t = W_35->functions;
    }
  }
}

static void Domain5
# ifdef __STDC__
(Tree_tTree t, Environs_tFunction f)
# else
(t, f)
Tree_tTree t;
Environs_tFunction f;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Ident) {
    {
      register Tree_yIdent *W_36 = &t->U_1.V_25.Ident;

      if (Types_Type(W_36->ident) == Types_cClass) {
        Complete_FunctionComplete(f, W_36->ident, W_36->idpos);
      }
      t = W_36->domain;
    }
  }
}

static void Directives5
# ifdef __STDC__
(Tree_tTree t, Sets_tSet domain, Idents_tIdent name)
# else
(t, domain, name)
Tree_tTree t;
Sets_tSet domain;
Idents_tIdent name;
# endif
{
  Sets_tSet classes;

  Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
  while (t->U_1.V_1.Kind == Tree_Directive) {
    {
      register Tree_yDirective *W_37 = &t->U_1.V_28.Directive;

      if (W_37->correct) {
        Pattern5(W_37->pattern, W_37->number);
        Patterns_PatternClasses(W_37->pat, &classes);
        if (Sets_IsEmpty(classes)) {
          W_37->correct = FALSE;
          Semantics_Correct = FALSE;
          Errors_ErrorMessage((LONGCARD)eIllegalPattern, (LONGCARD)Errors_eError, W_37->pattern->U_1.V_29.pattern.pos);
        } else {
          Sets_Intersection(&classes, domain);
          if (Sets_IsEmpty(classes)) {
            W_37->correct = FALSE;
            Semantics_Correct = FALSE;
            Errors_ErrorMessageI((LONGCARD)eNotInDomain, (LONGCARD)Errors_eError, W_37->pattern->U_1.V_29.pattern.pos, (LONGCARD)Errors_eIdent, ADR(name));
          }
        }
        if (W_37->condition->U_1.V_1.Kind == Tree_CondF) {
          Environs_SetCondPattern(W_37->number, W_37->pat);
        } else {
          Environs_SetPattern(W_37->number, W_37->pat);
        }
      }
      t = W_37->directives;
    }
  }
  Sets_ReleaseSet(&classes);
}

static void Pattern5
# ifdef __STDC__
(Tree_tTree t, INTEGER number)
# else
(t, number)
Tree_tTree t;
INTEGER number;
# endif
{
  Sets_tSet nodes, classes, add;

  if (t->U_1.V_1.Kind == Tree_Pattern1) {
    {
      register Tree_yPattern1 *W_38 = &t->U_1.V_30.Pattern1;

      Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
      Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
      Sets_MakeSet(&add, (Sets_tElement)Scanner_MaxIdent);
      switch (Types_Type(W_38->ident)) {
      case Types_cNoType:;
        Types_AllNodes(&nodes);
        break;
      case Types_cClass:;
        Grammar_Subclasses(W_38->ident, &classes);
        Grammar_NodesOfClass(W_38->ident, &nodes);
        while (!Sets_IsEmpty(classes)) {
          Grammar_NodesOfClass((SHORTCARD)Sets_Extract(&classes), &add);
          Sets_Union(&nodes, add);
        }
        break;
      }
      while (!Sets_IsEmpty(nodes)) {
        Grammar_AddPatNumber((SHORTCARD)Sets_Extract(&nodes), number);
      }
      Sets_ReleaseSet(&nodes);
      Sets_ReleaseSet(&classes);
      Sets_ReleaseSet(&add);
    }
  } else {
    {
      register Tree_yPattern *W_39 = &t->U_1.V_31.Pattern;

      Grammar_AddPatNumber(W_39->ident, number);
    }
  }
}

void Semantics__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Convert__init();
    Complete__init();
    Errors__init();
    Positions__init();
    Environs__init();
    Grammar__init();
    Idents__init();
    Parser__init();
    Patterns__init();
    Queues__init();
    Reduced__init();
    Scanner__init();
    Sets__init();
    Strings__init();
    Tree__init();
    Types__init();

    Semantics_Correct = TRUE;
  }
}
