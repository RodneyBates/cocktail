#include "SYSTEM_.h"

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Rules
#include "Rules.h"
#endif

Rules_Expression Rules_NoExpression;

#define eNoOperator   41
#define eTermLeft   42
#define eTokenNotDecl   32
typedef struct S_1 *Expression;
typedef struct S_1 {
    Rules_Operation Type;
    union {
        struct {
            Rules_Expression Son;
        } V_1;
        struct {
            Rules_Expression LeSon, RiSon;
        } V_2;
        struct {
            Lists_tList Act;
        } V_3;
        struct {
            TokenTab_Vocabulary Token;
        } V_4;
    } U_1;
    TokenTab_PosType Position, SecondPos;
    ADDRESS Special;
    BOOLEAN HasPrio;
    TokenTab_PosType PRIOPos;
    Idents_tIdent PrioSym;
    TokenTab_PosType PrioSymPos;
} Node;
typedef struct S_2 *MRules;
typedef struct S_2 {
    TokenTab_NonTerminal Left;
    TokenTab_PosType LeftPos;
    TokenTab_PosType ColonPos;
    Rules_Expression Right;
    TokenTab_PosType PointPos;
    Lists_tList Comment;
    TokenTab_PosType CommPos;
    BOOLEAN HasPrio;
    union {
        struct {
            TokenTab_PosType PRIOPos;
            SHORTCARD Priority;
            TokenTab_Terminal PrioSym;
            TokenTab_PosType PrioSymPos;
        } V_1;
    } U_1;
    Rules_MRules Next;
} Rule;
static struct S_3 {
    TokenTab_PosType RULESPos;
    Lists_tList Comment;
    TokenTab_PosType CommPos;
} RulesVars;
static Rules_MRules StartMRule, RMRule, WMRule;
static BOOLEAN OpenForReading;
static Rules_Expression MakeArtificialNode ARGS((TokenTab_PosType Pos, TokenTab_PosType SecPos, Rules_Expression LSon, Rules_Expression RSon));
static void ERROR ARGS((CHAR a[], LONGCARD ));


Rules_Expression Rules_MakeLeafNode
# ifdef __STDC__
(Idents_tIdent sym, TokenTab_PosType Pos)
# else
(sym, Pos)
Idents_tIdent sym;
TokenTab_PosType Pos;
# endif
{
  Rules_Expression HNode;
  TokenTab_TokenError Error;
  TokenTab_Vocabulary voc;

  HNode = (Rules_Expression)Memory_Alloc((LONGINT)sizeof(Node));
  if (HNode == NIL) {
    ERROR((STRING)"MakeLeafNode: Heap overflow", 27L);
  }
  ((Expression)HNode)->Position = Pos;
  ((Expression)HNode)->Special = (ADDRESS)NIL;
  voc = TokenTab_MakeVoc(sym, Pos);
  if (TokenTab_GetTokenType(voc) == TokenTab_Term) {
    ((Expression)HNode)->Type = Rules_TermLeaf;
    ((Expression)HNode)->U_1.V_4.Token = voc;
  } else {
    ((Expression)HNode)->Type = Rules_NonTermLeaf;
    ((Expression)HNode)->U_1.V_4.Token = voc;
  }
  return HNode;
}

Rules_Expression Rules_MakeActionNode
# ifdef __STDC__
(Lists_tList Act, TokenTab_PosType Pos)
# else
(Act, Pos)
Lists_tList Act;
TokenTab_PosType Pos;
# endif
{
  Rules_Expression HNode;
  Strings_tString s;

  HNode = (Rules_Expression)Memory_Alloc((LONGINT)sizeof(Node));
  if (HNode == NIL) {
    Strings_ArrayToString((STRING)"MakeActionNode : Heap overflow", 30L, &s);
    Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Pos, (LONGCARD)Errors_eString, ADR(s));
  }
  ((Expression)HNode)->Special = (ADDRESS)NIL;
  ((Expression)HNode)->Type = Rules_Action;
  ((Expression)HNode)->U_1.V_3.Act = Act;
  ((Expression)HNode)->Position = Pos;
  return HNode;
}

Rules_Expression Rules_MakeUnaryNode
# ifdef __STDC__
(Rules_UnaryOperation Type, TokenTab_PosType Pos, Rules_Expression Son)
# else
(Type, Pos, Son)
Rules_UnaryOperation Type;
TokenTab_PosType Pos;
Rules_Expression Son;
# endif
{
  Rules_Expression HNode;
  Strings_tString s;

  HNode = (Rules_Expression)Memory_Alloc((LONGINT)sizeof(Node));
  if (HNode == NIL) {
    Strings_ArrayToString((STRING)" MakeUnaryNode : Heap overflow", 30L, &s);
    Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Pos, (LONGCARD)Errors_eString, ADR(s));
  }
  ((Expression)HNode)->Special = (ADDRESS)NIL;
  ((Expression)HNode)->Type = Type;
  ((Expression)HNode)->Position = Pos;
  ((Expression)HNode)->U_1.V_1.Son = Son;
  return HNode;
}

Rules_Expression Rules_MakeBracketNode
# ifdef __STDC__
(Rules_BracketOperation Type, TokenTab_PosType Pos, TokenTab_PosType SecPos, Rules_Expression Son)
# else
(Type, Pos, SecPos, Son)
Rules_BracketOperation Type;
TokenTab_PosType Pos, SecPos;
Rules_Expression Son;
# endif
{
  Rules_Expression HNode;
  Strings_tString s;

  HNode = (Rules_Expression)Memory_Alloc((LONGINT)sizeof(Node));
  if (HNode == NIL) {
    Strings_ArrayToString((STRING)"MakeBracketNode : Heap overflow", 31L, &s);
    Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Pos, (LONGCARD)Errors_eString, ADR(s));
  }
  ((Expression)HNode)->Special = (ADDRESS)NIL;
  ((Expression)HNode)->Type = Type;
  ((Expression)HNode)->Position = Pos;
  ((Expression)HNode)->SecondPos = SecPos;
  ((Expression)HNode)->U_1.V_1.Son = Son;
  return HNode;
}

Rules_Expression Rules_MakeBinaryNode
# ifdef __STDC__
(Rules_BinaryOperation Type, TokenTab_PosType Pos, Rules_Expression LSon, Rules_Expression RSon)
# else
(Type, Pos, LSon, RSon)
Rules_BinaryOperation Type;
TokenTab_PosType Pos;
Rules_Expression LSon, RSon;
# endif
{
  Rules_Expression HNode;
  Strings_tString s;

  HNode = (Rules_Expression)Memory_Alloc((LONGINT)sizeof(Node));
  if (HNode == NIL) {
    Strings_ArrayToString((STRING)"MakeBinaryNode : Heap overflow", 30L, &s);
    Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Pos, (LONGCARD)Errors_eString, ADR(s));
  }
  ((Expression)HNode)->Special = (ADDRESS)NIL;
  ((Expression)HNode)->Type = Type;
  ((Expression)HNode)->Position = Pos;
  ((Expression)HNode)->U_1.V_2.LeSon = LSon;
  ((Expression)HNode)->U_1.V_2.RiSon = RSon;
  if (Type == Rules_Alternative) {
    ((Expression)HNode)->HasPrio = FALSE;
  }
  return HNode;
}

Rules_Expression Rules_MakePrioAlternativeNode
# ifdef __STDC__
(TokenTab_PosType Pos, Rules_Expression LSon, Rules_Expression RSon, BOOLEAN HasPrio, TokenTab_PosType PRIOPos, Idents_tIdent PrioSym, TokenTab_PosType PrioSymPos)
# else
(Pos, LSon, RSon, HasPrio, PRIOPos, PrioSym, PrioSymPos)
TokenTab_PosType Pos;
Rules_Expression LSon, RSon;
BOOLEAN HasPrio;
TokenTab_PosType PRIOPos;
Idents_tIdent PrioSym;
TokenTab_PosType PrioSymPos;
# endif
{
  Rules_Expression HNode;
  Strings_tString s;

  HNode = (Rules_Expression)Memory_Alloc((LONGINT)sizeof(Node));
  if (HNode == NIL) {
    Strings_ArrayToString((STRING)"MakePrioAlternativeNode : Heap overflow", 39L, &s);
    Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Pos, (LONGCARD)Errors_eString, ADR(s));
  }
  ((Expression)HNode)->HasPrio = HasPrio;
  ((Expression)HNode)->PRIOPos = PRIOPos;
  ((Expression)HNode)->PrioSym = PrioSym;
  ((Expression)HNode)->PrioSymPos = PrioSymPos;
  ((Expression)HNode)->Special = (ADDRESS)NIL;
  ((Expression)HNode)->Type = Rules_Alternative;
  ((Expression)HNode)->Position = Pos;
  ((Expression)HNode)->U_1.V_2.LeSon = LSon;
  ((Expression)HNode)->U_1.V_2.RiSon = RSon;
  return HNode;
}

void Rules_AppendArtificialNode
# ifdef __STDC__
(TokenTab_PosType Pos, TokenTab_PosType Pos2, Rules_Expression *Expr, Rules_Expression New)
# else
(Pos, Pos2, Expr, New)
TokenTab_PosType Pos, Pos2;
Rules_Expression *Expr;
Rules_Expression New;
# endif
{
  Rules_Expression last, expr;

  if (*Expr == Rules_NoExpression || Rules_GetNodeOperation(*Expr) != Rules_ArtAlternative) {
    *Expr = MakeArtificialNode(Pos, Pos2, *Expr, New);
  } else {
    expr = *Expr;
    for (;;) {
      last = ((Expression)expr)->U_1.V_2.RiSon;
      if (Rules_GetNodeOperation(last) != Rules_ArtAlternative) {
        goto EXIT_1;
      }
      expr = last;
    } EXIT_1:;
    ((Expression)expr)->U_1.V_2.RiSon = MakeArtificialNode(((Expression)last)->Position, Pos2, last, New);
  }
}

static Rules_Expression MakeArtificialNode
# ifdef __STDC__
(TokenTab_PosType Pos, TokenTab_PosType SecPos, Rules_Expression LSon, Rules_Expression RSon)
# else
(Pos, SecPos, LSon, RSon)
TokenTab_PosType Pos;
TokenTab_PosType SecPos;
Rules_Expression LSon, RSon;
# endif
{
  Rules_Expression HNode;
  Strings_tString s;

  HNode = (Rules_Expression)Memory_Alloc((LONGINT)sizeof(Node));
  if (HNode == NIL) {
    Strings_ArrayToString((STRING)"MakeArtificialNode : Heap overflow", 34L, &s);
    Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Pos, (LONGCARD)Errors_eString, ADR(s));
  }
  ((Expression)HNode)->Special = (ADDRESS)NIL;
  ((Expression)HNode)->Type = Rules_ArtAlternative;
  ((Expression)HNode)->Position = Pos;
  ((Expression)HNode)->SecondPos = SecPos;
  ((Expression)HNode)->U_1.V_2.LeSon = LSon;
  ((Expression)HNode)->U_1.V_2.RiSon = RSon;
  return HNode;
}

void Rules_PutNodeSpecial
# ifdef __STDC__
(Rules_Expression Expr, ADDRESS Spec)
# else
(Expr, Spec)
Rules_Expression Expr;
ADDRESS Spec;
# endif
{
  if (Expr != NIL) {
    ((Expression)Expr)->Special = Spec;
  } else {
    ERROR((STRING)"PutNodeSpecial : You tried to access an empty node", 50L);
  }
}

void Rules_MakeRule
# ifdef __STDC__
(Idents_tIdent Left, TokenTab_PosType LeftPos, TokenTab_PosType ColonPos, Rules_Expression Right, Lists_tList Comment, TokenTab_PosType CommPos, TokenTab_PosType PointPos, BOOLEAN HasPrio, TokenTab_PosType PRIOPos, Idents_tIdent PrioSym, TokenTab_PosType PrioSymPos)
# else
(Left, LeftPos, ColonPos, Right, Comment, CommPos, PointPos, HasPrio, PRIOPos, PrioSym, PrioSymPos)
Idents_tIdent Left;
TokenTab_PosType LeftPos;
TokenTab_PosType ColonPos;
Rules_Expression Right;
Lists_tList Comment;
TokenTab_PosType CommPos;
TokenTab_PosType PointPos;
BOOLEAN HasPrio;
TokenTab_PosType PRIOPos;
Idents_tIdent PrioSym;
TokenTab_PosType PrioSymPos;
# endif
{
  Rules_MRules HRule;
  TokenTab_TokenError Error;
  TokenTab_Vocabulary Leftvoc;
  TokenTab_Vocabulary voc;
  Strings_tString s;

  OpenForReading = FALSE;
  Leftvoc = TokenTab_MakeVoc(Left, LeftPos);
  if (TokenTab_GetTokenType(Leftvoc) == TokenTab_Term) {
    Errors_ErrorMessageI((LONGCARD)eTermLeft, (LONGCARD)Errors_eError, LeftPos, (LONGCARD)Errors_eIdent, ADR(Left));
  } else {
    TokenTab_SetNontermPos(Left, LeftPos);
    HRule = (Rules_MRules)Memory_Alloc((LONGINT)sizeof(Rule));
    if (HRule == NIL) {
      Strings_ArrayToString((STRING)"MakeRule : Heap overflow", 24L, &s);
      Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, LeftPos, (LONGCARD)Errors_eString, ADR(s));
    }
    ((MRules)HRule)->Left = Leftvoc;
    ((MRules)HRule)->LeftPos = LeftPos;
    ((MRules)HRule)->ColonPos = ColonPos;
    ((MRules)HRule)->PointPos = PointPos;
    ((MRules)HRule)->Right = Right;
    ((MRules)HRule)->Comment = Comment;
    ((MRules)HRule)->CommPos = CommPos;
    ((MRules)HRule)->HasPrio = HasPrio;
    ((MRules)HRule)->U_1.V_1.Priority = 0;
    if (HasPrio) {
      ((MRules)HRule)->U_1.V_1.PRIOPos = PRIOPos;
      ((MRules)HRule)->U_1.V_1.PrioSymPos = PrioSymPos;
      voc = TokenTab_SymbolToToken(PrioSym, &Error);
      if (Error != TokenTab_NoError) {
        Errors_ErrorMessageI((LONGCARD)eTokenNotDecl, (LONGCARD)Errors_eError, PrioSymPos, (LONGCARD)Errors_eIdent, ADR(PrioSym));
      } else {
        ((MRules)HRule)->U_1.V_1.PrioSym = voc;
        ((MRules)HRule)->U_1.V_1.Priority = TokenTab_GetPrio(voc);
        if (((MRules)HRule)->U_1.V_1.Priority == 0) {
          Errors_ErrorMessageI((LONGCARD)eNoOperator, (LONGCARD)Errors_eError, PrioSymPos, (LONGCARD)Errors_eIdent, ADR(PrioSym));
        }
      }
    }
    if (WMRule != NIL) {
      ((MRules)WMRule)->Next = HRule;
    } else {
      StartMRule = HRule;
    }
    ((MRules)HRule)->Next = (Rules_MRules)NIL;
    WMRule = HRule;
  }
}

void Rules_MakeRulesHeader
# ifdef __STDC__
(TokenTab_PosType RULESPos, Lists_tList Comment, TokenTab_PosType CommPos)
# else
(RULESPos, Comment, CommPos)
TokenTab_PosType RULESPos;
Lists_tList Comment;
TokenTab_PosType CommPos;
# endif
{
  RulesVars.RULESPos = RULESPos;
  RulesVars.Comment = Comment;
  RulesVars.CommPos = CommPos;
}

void Rules_InitRulesReading
# ifdef __STDC__
()
# else
()
# endif
{
  OpenForReading = TRUE;
  RMRule = StartMRule;
}

Rules_Operation Rules_GetNodeOperation
# ifdef __STDC__
(Rules_Expression Expr)
# else
(Expr)
Rules_Expression Expr;
# endif
{
  if (Expr == NIL) {
    return Rules_NoOperation;
  } else {
    return ((Expression)Expr)->Type;
  }
}

void Rules_GetLeafNode
# ifdef __STDC__
(Rules_Expression Expr, TokenTab_Vocabulary *Voc, TokenTab_PosType *Pos)
# else
(Expr, Voc, Pos)
Rules_Expression Expr;
TokenTab_Vocabulary *Voc;
TokenTab_PosType *Pos;
# endif
{
  if (Rules_GetNodeOperation(Expr) != Rules_TermLeaf && Rules_GetNodeOperation(Expr) != Rules_NonTermLeaf) {
    ERROR((STRING)"GetLeafNode : Wrong Node Type", 29L);
  }
  if (Expr != NIL) {
    *Voc = ((Expression)Expr)->U_1.V_4.Token;
    *Pos = ((Expression)Expr)->Position;
  } else {
    ERROR((STRING)"GetLeafNode : Node empty", 24L);
  }
}

void Rules_GetActionNode
# ifdef __STDC__
(Rules_Expression Expr, Lists_tList *Act, TokenTab_PosType *Pos)
# else
(Expr, Act, Pos)
Rules_Expression Expr;
Lists_tList *Act;
TokenTab_PosType *Pos;
# endif
{
  if (Rules_GetNodeOperation(Expr) != Rules_Action) {
    ERROR((STRING)"GetActionNode : Wrong Node Type", 31L);
  }
  if (Expr != NIL) {
    *Act = ((Expression)Expr)->U_1.V_3.Act;
    *Pos = ((Expression)Expr)->Position;
  } else {
    ERROR((STRING)"GetActionNode : Node empty", 26L);
  }
}

void Rules_GetUnaryNode
# ifdef __STDC__
(Rules_Expression Expr, TokenTab_PosType *Pos, Rules_Expression *Son)
# else
(Expr, Pos, Son)
Rules_Expression Expr;
TokenTab_PosType *Pos;
Rules_Expression *Son;
# endif
{
  if (Rules_GetNodeOperation(Expr) != Rules_Star && Rules_GetNodeOperation(Expr) != Rules_Plus) {
    ERROR((STRING)"GetUnaryNode : Wrong Node Type", 30L);
  }
  if (Expr != NIL) {
    *Pos = ((Expression)Expr)->Position;
    *Son = ((Expression)Expr)->U_1.V_1.Son;
  } else {
    ERROR((STRING)"GetUnaryNode : Node empty", 25L);
  }
}

void Rules_GetBracketNode
# ifdef __STDC__
(Rules_Expression Expr, TokenTab_PosType *Pos, TokenTab_PosType *SecPos, Rules_Expression *Son)
# else
(Expr, Pos, SecPos, Son)
Rules_Expression Expr;
TokenTab_PosType *Pos, *SecPos;
Rules_Expression *Son;
# endif
{
  if (Rules_GetNodeOperation(Expr) != Rules_Bracket && Rules_GetNodeOperation(Expr) != Rules_Optional) {
    ERROR((STRING)"GetBracketNode : Wrong Node Type", 32L);
  }
  if (Expr != NIL) {
    *Pos = ((Expression)Expr)->Position;
    *SecPos = ((Expression)Expr)->SecondPos;
    *Son = ((Expression)Expr)->U_1.V_1.Son;
  } else {
    ERROR((STRING)"GetBracketNode : Node empty", 27L);
  }
}

void Rules_GetBinaryNode
# ifdef __STDC__
(Rules_Expression Expr, TokenTab_PosType *Pos, Rules_Expression *LSon, Rules_Expression *RSon)
# else
(Expr, Pos, LSon, RSon)
Rules_Expression Expr;
TokenTab_PosType *Pos;
Rules_Expression *LSon, *RSon;
# endif
{
  if (Rules_GetNodeOperation(Expr) != Rules_Sequence && Rules_GetNodeOperation(Expr) != Rules_Separator && Rules_GetNodeOperation(Expr) != Rules_Alternative && Rules_GetNodeOperation(Expr) != Rules_ArtAlternative) {
    ERROR((STRING)"GetBinaryNode : Wrong Node Type", 31L);
  }
  if (Expr != NIL) {
    *Pos = ((Expression)Expr)->Position;
    *LSon = ((Expression)Expr)->U_1.V_2.LeSon;
    *RSon = ((Expression)Expr)->U_1.V_2.RiSon;
  } else {
    ERROR((STRING)"GetBinaryNode : Node empty", 26L);
  }
}

void Rules_GetPrioAlternativeNode
# ifdef __STDC__
(Rules_Expression Expr, TokenTab_PosType *Pos, Rules_Expression *LSon, Rules_Expression *RSon, BOOLEAN *HasPrio, TokenTab_PosType *PRIOPos, Idents_tIdent *PrioSym, TokenTab_PosType *PrioSymPos)
# else
(Expr, Pos, LSon, RSon, HasPrio, PRIOPos, PrioSym, PrioSymPos)
Rules_Expression Expr;
TokenTab_PosType *Pos;
Rules_Expression *LSon;
Rules_Expression *RSon;
BOOLEAN *HasPrio;
TokenTab_PosType *PRIOPos;
Idents_tIdent *PrioSym;
TokenTab_PosType *PrioSymPos;
# endif
{
  if (Rules_GetNodeOperation(Expr) != Rules_Alternative) {
    ERROR((STRING)"GetPrioAlternativeNode : Wrong Node Type", 40L);
  }
  if (Expr != NIL) {
    *Pos = ((Expression)Expr)->Position;
    *LSon = ((Expression)Expr)->U_1.V_2.LeSon;
    *RSon = ((Expression)Expr)->U_1.V_2.RiSon;
    *HasPrio = ((Expression)Expr)->HasPrio;
    *PRIOPos = ((Expression)Expr)->PRIOPos;
    *PrioSym = ((Expression)Expr)->PrioSym;
    *PrioSymPos = ((Expression)Expr)->PrioSymPos;
  } else {
    ERROR((STRING)"GetPrioAlternativeNode : Node empty", 35L);
  }
}

void Rules_GetArtificialNode
# ifdef __STDC__
(Rules_Expression Expr, TokenTab_PosType *Pos, TokenTab_PosType *SecPos, Rules_Expression *LSon, Rules_Expression *RSon)
# else
(Expr, Pos, SecPos, LSon, RSon)
Rules_Expression Expr;
TokenTab_PosType *Pos;
TokenTab_PosType *SecPos;
Rules_Expression *LSon, *RSon;
# endif
{
  if (Rules_GetNodeOperation(Expr) != Rules_ArtAlternative) {
    ERROR((STRING)"GetArtificialNode : Wrong Node Type", 35L);
  }
  if (Expr != NIL) {
    *Pos = ((Expression)Expr)->Position;
    *SecPos = ((Expression)Expr)->SecondPos;
    *LSon = ((Expression)Expr)->U_1.V_2.LeSon;
    *RSon = ((Expression)Expr)->U_1.V_2.RiSon;
  } else {
    ERROR((STRING)"GetArtificialNode : Node empty", 30L);
  }
}

ADDRESS Rules_GetNodeSpecial
# ifdef __STDC__
(Rules_Expression Expr)
# else
(Expr)
Rules_Expression Expr;
# endif
{
  if (Expr != NIL) {
    return ((Expression)Expr)->Special;
  } else {
    ERROR((STRING)"GetNodeSpecial : Node empty", 27L);
    return (ADDRESS)NIL;
  }
}

BOOLEAN Rules_GetRule
# ifdef __STDC__
(TokenTab_NonTerminal *Left, TokenTab_PosType *LeftPos, TokenTab_PosType *ColonPos, Rules_Expression *Right, Lists_tList *Comment, TokenTab_PosType *CommPos, TokenTab_PosType *PointPos, BOOLEAN *HasPrio, TokenTab_PosType *PRIOPos, TokenTab_Terminal *PrioSym, TokenTab_PosType *PrioSymPos)
# else
(Left, LeftPos, ColonPos, Right, Comment, CommPos, PointPos, HasPrio, PRIOPos, PrioSym, PrioSymPos)
TokenTab_NonTerminal *Left;
TokenTab_PosType *LeftPos;
TokenTab_PosType *ColonPos;
Rules_Expression *Right;
Lists_tList *Comment;
TokenTab_PosType *CommPos;
TokenTab_PosType *PointPos;
BOOLEAN *HasPrio;
TokenTab_PosType *PRIOPos;
TokenTab_Terminal *PrioSym;
TokenTab_PosType *PrioSymPos;
# endif
{
  if (!OpenForReading) {
    ERROR((STRING)"GetRule : You must not read here", 32L);
  }
  if (RMRule == NIL) {
    return FALSE;
  } else {
    *Left = ((MRules)RMRule)->Left;
    *LeftPos = ((MRules)RMRule)->LeftPos;
    *ColonPos = ((MRules)RMRule)->ColonPos;
    *PointPos = ((MRules)RMRule)->PointPos;
    *Right = ((MRules)RMRule)->Right;
    *Comment = ((MRules)RMRule)->Comment;
    *CommPos = ((MRules)RMRule)->CommPos;
    if (((MRules)RMRule)->HasPrio) {
      *PRIOPos = ((MRules)RMRule)->U_1.V_1.PRIOPos;
      *PrioSym = ((MRules)RMRule)->U_1.V_1.PrioSym;
      *PrioSymPos = ((MRules)RMRule)->U_1.V_1.PrioSymPos;
    } else {
      PRIOPos->Line = 0;
      PRIOPos->Column = 0;
      *PrioSym = 0;
      PrioSymPos->Line = 0;
      PrioSymPos->Column = 0;
    }
    *HasPrio = ((MRules)RMRule)->HasPrio;
    RMRule = ((MRules)RMRule)->Next;
    return TRUE;
  }
}

BOOLEAN Rules_GetEssentialRule
# ifdef __STDC__
(TokenTab_NonTerminal *Left, Rules_Expression *Right, BOOLEAN *HasPrio)
# else
(Left, Right, HasPrio)
TokenTab_NonTerminal *Left;
Rules_Expression *Right;
BOOLEAN *HasPrio;
# endif
{
  if (!OpenForReading) {
    ERROR((STRING)"GetEssentialRule : You must not read here", 41L);
  }
  if (RMRule == NIL) {
    return FALSE;
  } else {
    *Left = ((MRules)RMRule)->Left;
    *Right = ((MRules)RMRule)->Right;
    *HasPrio = ((MRules)RMRule)->HasPrio;
    RMRule = ((MRules)RMRule)->Next;
    return TRUE;
  }
}

void Rules_GetRulesHeader
# ifdef __STDC__
(TokenTab_PosType *RULESPos, Lists_tList *Comment, TokenTab_PosType *CommPos)
# else
(RULESPos, Comment, CommPos)
TokenTab_PosType *RULESPos;
Lists_tList *Comment;
TokenTab_PosType *CommPos;
# endif
{
  *RULESPos = RulesVars.RULESPos;
  *Comment = RulesVars.Comment;
  *CommPos = RulesVars.CommPos;
}

static void ERROR
# ifdef __STDC__
(CHAR a[], LONGCARD O_1)
# else
(a, O_1)
CHAR a[];
LONGCARD O_1;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_1, CHAR)
  Strings_ArrayToString(a, O_1, &s);
  Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(s));
  FREE_OPEN_ARRAYS
}

void Rules__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Lists__init();
    TokenTab__init();
    Idents__init();
    Lists__init();
    TokenTab__init();
    Memory__init();
    Idents__init();
    Errors__init();
    Strings__init();
    Positions__init();

    RMRule = (Rules_MRules)NIL;
    WMRule = (Rules_MRules)NIL;
    StartMRule = (Rules_MRules)NIL;
    RulesVars.RULESPos.Line = 0;
    RulesVars.RULESPos.Column = 0;
    Lists_MakeList(&RulesVars.Comment);
    RulesVars.CommPos.Line = 0;
    RulesVars.CommPos.Column = 0;
    Rules_NoExpression = (Rules_Expression)NIL;
  }
}
