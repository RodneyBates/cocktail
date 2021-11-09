#include "SYSTEM_.h"

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Oper
#include "Oper.h"
#endif


#define eNoIntCode   25
#define eTokenOverflow   26
#define eNoTerm   40
#define eTokenInPrio   35
typedef struct S_1 *Priorities;
typedef struct S_2 *Operators;
typedef struct S_1 {
    Oper_OperKind Kind;
    TokenTab_PosType KindPos;
    Operators List;
    Lists_tList Comment;
    TokenTab_PosType CommPos;
    Priorities Next;
} Priority;
typedef struct S_2 {
    TokenTab_Vocabulary Token;
    TokenTab_PosType TokenPos;
    Operators List;
} Operator;
static struct S_3 {
    TokenTab_PosType OPERPos;
    Lists_tList Comment;
    TokenTab_PosType CommPos;
} OperVars;
static BOOLEAN ReadyForOperator;
static Priorities WPrio;
static Priorities StartPrio;
static Priorities RPrio;
static BOOLEAN INTOPERExists;
static TokenTab_Prio CurrentPrio;
static Operators WOp, ROp;
static BOOLEAN GetOperatorAllowed;
static BOOLEAN OpenForReading;
static void ERROR ARGS((CHAR a[], LONGCARD ));


void Oper_MakePriority
# ifdef __STDC__
(Oper_OperKind Kind, TokenTab_PosType Pos)
# else
(Kind, Pos)
Oper_OperKind Kind;
TokenTab_PosType Pos;
# endif
{
  Priorities HPrio;

  if (OpenForReading) {
    ERROR((STRING)"MakePriority : Do not write now ", 32L);
  }
  ReadyForOperator = TRUE;
  HPrio = (Priorities)Memory_Alloc((LONGINT)sizeof(Priority));
  if (HPrio == NIL) {
    ERROR((STRING)"MakePriority : Heap overflow", 28L);
  }
  HPrio->Kind = Kind;
  HPrio->KindPos = Pos;
  HPrio->List = NIL;
  WOp = NIL;
  HPrio->Next = NIL;
  Lists_MakeList(&HPrio->Comment);
  HPrio->CommPos.Line = 0;
  HPrio->CommPos.Column = 0;
  if (WPrio != NIL) {
    WPrio->Next = HPrio;
  } else {
    StartPrio = HPrio;
  }
  WPrio = HPrio;
  INC(CurrentPrio);
}

void Oper_CompletePriority
# ifdef __STDC__
(Lists_tList Comment, TokenTab_PosType CommPos)
# else
(Comment, CommPos)
Lists_tList Comment;
TokenTab_PosType CommPos;
# endif
{
  if (!ReadyForOperator) {
    ERROR((STRING)"CompletePriority : Wrong use of procedure", 41L);
  }
  if (OpenForReading) {
    ERROR((STRING)"CompletePriority : Do not write now", 35L);
  }
  WPrio->Comment = Comment;
  WPrio->CommPos = CommPos;
  ReadyForOperator = FALSE;
}

void Oper_MakeOperator
# ifdef __STDC__
(Idents_tIdent Token, TokenTab_PosType TokenPos)
# else
(Token, TokenPos)
Idents_tIdent Token;
TokenTab_PosType TokenPos;
# endif
{
  Operators HOper;
  TokenTab_Vocabulary HToken;
  TokenTab_TokenError Error;
  TokenTab_Terminal ter;

  if (!ReadyForOperator) {
    ERROR((STRING)"makeOperator : Wrong use of procedure", 37L);
  }
  HToken = TokenTab_SymbolToToken(Token, &Error);
  if (Error == TokenTab_NotExists) {
    HToken = TokenTab_MAXTerm + 1;
    if (HToken > TokenTab_cMAXTerm) {
      Errors_ErrorMessage((LONGCARD)eTokenOverflow, (LONGCARD)Errors_eRestriction, TokenPos);
    }
    ter = HToken;
    TokenTab_MakeTerm(Token, &ter, &Error, TokenPos);
    if (Error == TokenTab_OutOfRange) {
      Errors_ErrorMessage((LONGCARD)eTokenOverflow, (LONGCARD)Errors_eRestriction, TokenPos);
    }
  } else if (Error == TokenTab_NoIntCode) {
    Errors_ErrorMessageI((LONGCARD)eNoIntCode, (LONGCARD)Errors_eFatal, Positions_NoPosition, (LONGCARD)Errors_eIdent, ADR(Token));
  }
  if (TokenTab_GetTokenType(HToken) != TokenTab_Term) {
    Errors_ErrorMessageI((LONGCARD)eNoTerm, (LONGCARD)Errors_eError, TokenPos, (LONGCARD)Errors_eIdent, ADR(Token));
  } else if (TokenTab_GetPrio(HToken) != 0) {
    Errors_ErrorMessageI((LONGCARD)eTokenInPrio, (LONGCARD)Errors_eError, TokenPos, (LONGCARD)Errors_eIdent, ADR(Token));
  } else {
    TokenTab_PutPrio(TokenTab_SymbolToToken(Token, &Error), CurrentPrio);
    HOper = (Operators)Memory_Alloc((LONGINT)sizeof(Operator));
    if (HOper == NIL) {
      ERROR((STRING)"MakeOperator : Heap Overflow", 28L);
    }
    HOper->Token = TokenTab_SymbolToToken(Token, &Error);
    HOper->TokenPos = TokenPos;
    HOper->List = NIL;
    if (WOp != NIL) {
      WOp->List = HOper;
    } else {
      WPrio->List = HOper;
    }
    WOp = HOper;
  }
}

void Oper_MakeOperHeader
# ifdef __STDC__
(TokenTab_PosType OPERPos, Lists_tList Comment, TokenTab_PosType CommPos)
# else
(OPERPos, Comment, CommPos)
TokenTab_PosType OPERPos;
Lists_tList Comment;
TokenTab_PosType CommPos;
# endif
{
  OperVars.OPERPos = OPERPos;
  OperVars.Comment = Comment;
  OperVars.CommPos = CommPos;
  INTOPERExists = TRUE;
}

void Oper_InitPrioReading
# ifdef __STDC__
()
# else
()
# endif
{
  OpenForReading = TRUE;
  RPrio = StartPrio;
}

BOOLEAN Oper_GetOperHeader
# ifdef __STDC__
(TokenTab_PosType *OPERPos, Lists_tList *Comment, TokenTab_PosType *CommPos)
# else
(OPERPos, Comment, CommPos)
TokenTab_PosType *OPERPos;
Lists_tList *Comment;
TokenTab_PosType *CommPos;
# endif
{
  if (INTOPERExists) {
    *OPERPos = OperVars.OPERPos;
    *Comment = OperVars.Comment;
    *CommPos = OperVars.CommPos;
  } else {
    OPERPos->Line = 0;
    OPERPos->Column = 0;
    Lists_MakeList(Comment);
    CommPos->Line = 0;
    CommPos->Column = 0;
  }
  return INTOPERExists;
}

BOOLEAN Oper_GetPriority
# ifdef __STDC__
(Oper_OperKind *Kind, TokenTab_PosType *Pos, Lists_tList *Comment, TokenTab_PosType *CommPos)
# else
(Kind, Pos, Comment, CommPos)
Oper_OperKind *Kind;
TokenTab_PosType *Pos;
Lists_tList *Comment;
TokenTab_PosType *CommPos;
# endif
{
  if (!OpenForReading) {
    ERROR((STRING)"GetPriority : You must not read now", 35L);
  }
  if (RPrio == NIL) {
    GetOperatorAllowed = FALSE;
    return FALSE;
  } else {
    *Kind = RPrio->Kind;
    *Pos = RPrio->KindPos;
    *Comment = RPrio->Comment;
    *CommPos = RPrio->CommPos;
    ROp = RPrio->List;
    RPrio = RPrio->Next;
    GetOperatorAllowed = TRUE;
    return TRUE;
  }
}

BOOLEAN Oper_GetOperator
# ifdef __STDC__
(TokenTab_Vocabulary *Token, TokenTab_PosType *TokenPos)
# else
(Token, TokenPos)
TokenTab_Vocabulary *Token;
TokenTab_PosType *TokenPos;
# endif
{
  if (!GetOperatorAllowed) {
    ERROR((STRING)"GetOperator : Wrong use of procedure", 36L);
  }
  if (ROp == NIL) {
    return FALSE;
  } else {
    *Token = ROp->Token;
    *TokenPos = ROp->TokenPos;
    ROp = ROp->List;
    return TRUE;
  }
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

void Oper__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Lists__init();
    TokenTab__init();
    Idents__init();
    Lists__init();
    Strings__init();
    Idents__init();
    Memory__init();
    Positions__init();
    TokenTab__init();
    Errors__init();

    StartPrio = NIL;
    WPrio = NIL;
    RPrio = NIL;
    INTOPERExists = FALSE;
    ReadyForOperator = FALSE;
    WOp = NIL;
    ROp = NIL;
    OpenForReading = FALSE;
    GetOperatorAllowed = FALSE;
    CurrentPrio = 0;
  }
}
