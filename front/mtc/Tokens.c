#include "SYSTEM_.h"

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
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

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Tokens
#include "Tokens.h"
#endif


#define eTokenDeclTwice   30
#define eCodeExists   31
typedef struct S_1 *Declarations;
typedef struct S_1 {
    Idents_tIdent Token;
    TokenTab_PosType TokenPos;
    BOOLEAN HasCoding;
    union {
        struct {
            TokenTab_PosType EQUALPos;
            TokenTab_PosType NumberPos;
        } V_1;
    } U_1;
    Lists_tList Comment;
    TokenTab_PosType CommPos;
    Declarations Next;
} Declaration;
static struct S_2 {
    Lists_tList GlobalComment;
    TokenTab_PosType GlobalCommPos;
    TokenTab_PosType TOKENPos;
    Lists_tList TOKENComment;
    TokenTab_PosType TOKENCommPos;
} TokensVars;
static Declarations StartDecl;
static Declarations RDecl;
static Declarations WDecl;
static BOOLEAN ReadyForReading;
static void ERROR ARGS((CHAR a[], LONGCARD ));


void Tokens_MakeGlobalHeader
# ifdef __STDC__
(Lists_tList GlobalComment, TokenTab_PosType GlobalCommPos)
# else
(GlobalComment, GlobalCommPos)
Lists_tList GlobalComment;
TokenTab_PosType GlobalCommPos;
# endif
{
  TokensVars.GlobalComment = GlobalComment;
  TokensVars.GlobalCommPos = GlobalCommPos;
}

void Tokens_MakeTokensHeader
# ifdef __STDC__
(TokenTab_PosType TOKENPos, Lists_tList TOKENComment, TokenTab_PosType TOKENCommPos)
# else
(TOKENPos, TOKENComment, TOKENCommPos)
TokenTab_PosType TOKENPos;
Lists_tList TOKENComment;
TokenTab_PosType TOKENCommPos;
# endif
{
  TokensVars.TOKENPos = TOKENPos;
  TokensVars.TOKENComment = TOKENComment;
  TokensVars.TOKENCommPos = TOKENCommPos;
}

void Tokens_MakeDeclaration
# ifdef __STDC__
(Idents_tIdent Token, TokenTab_PosType TokenPos, BOOLEAN HasCoding, TokenTab_PosType EQUALPos, TokenTab_Terminal Number, TokenTab_PosType NumberPos, Lists_tList Comment, TokenTab_PosType CommPos)
# else
(Token, TokenPos, HasCoding, EQUALPos, Number, NumberPos, Comment, CommPos)
Idents_tIdent Token;
TokenTab_PosType TokenPos;
BOOLEAN HasCoding;
TokenTab_PosType EQUALPos;
TokenTab_Terminal Number;
TokenTab_PosType NumberPos;
Lists_tList Comment;
TokenTab_PosType CommPos;
# endif
{
  Declarations HDecl;
  TokenTab_TokenError Error;

  if (ReadyForReading) {
    ERROR((STRING)"MakeDeclaration: do not write", 29L);
  }
  HDecl = (Declarations)Memory_Alloc((LONGINT)sizeof(Declaration));
  if (HDecl == NIL) {
    ERROR((STRING)"MakeDeclaration: Heap overflow", 30L);
  }
  HDecl->Token = Token;
  HDecl->TokenPos = TokenPos;
  HDecl->HasCoding = HasCoding;
  HDecl->Next = NIL;
  if (HasCoding) {
    TokenTab_MakeTerm(Token, &Number, &Error, TokenPos);
    if (Error == TokenTab_SymbolExists) {
      Errors_ErrorMessageI((LONGCARD)eTokenDeclTwice, (LONGCARD)Errors_eError, TokenPos, (LONGCARD)Errors_eIdent, ADR(Token));
      return;
    } else if (Error == TokenTab_CodeExists) {
      Errors_ErrorMessageI((LONGCARD)eCodeExists, (LONGCARD)Errors_eError, TokenPos, (LONGCARD)Errors_eIdent, ADR(Token));
      return;
    }
    HDecl->U_1.V_1.EQUALPos = EQUALPos;
    HDecl->U_1.V_1.NumberPos = NumberPos;
  } else {
    TokenTab_MakeDefTerm(&Token, &Error, TokenPos);
    if (Error == TokenTab_SymbolExists) {
      Errors_ErrorMessageI((LONGCARD)eTokenDeclTwice, (LONGCARD)Errors_eError, TokenPos, (LONGCARD)Errors_eIdent, ADR(Token));
      return;
    }
  }
  HDecl->Comment = Comment;
  HDecl->CommPos = CommPos;
  if (WDecl == NIL) {
    StartDecl = HDecl;
  } else {
    WDecl->Next = HDecl;
  }
  WDecl = HDecl;
}

void Tokens_CompleteDeclarations
# ifdef __STDC__
()
# else
()
# endif
{
  TokenTab_TokenError Error;

  RDecl = StartDecl;
  while (RDecl != NIL) {
    if (!RDecl->HasCoding) {
      TokenTab_CompleteDefTerm(RDecl->Token, &Error);
      if (Error == TokenTab_NotExists) {
        ERROR((STRING)"CompleteDeclarations: token does not exists", 43L);
      } else if (Error == TokenTab_CodeExists) {
        ERROR((STRING)"CompleteDeclarations: token already complete", 44L);
      } else if (Error == TokenTab_NotTerm) {
        ERROR((STRING)"CompleteDeclarations: token is nonterminal", 42L);
      }
    }
    RDecl = RDecl->Next;
  }
  RDecl = StartDecl;
  ReadyForReading = TRUE;
}

void Tokens_GetGlobalHeader
# ifdef __STDC__
(Lists_tList *GlobalComment, TokenTab_PosType *GlobalCommPos)
# else
(GlobalComment, GlobalCommPos)
Lists_tList *GlobalComment;
TokenTab_PosType *GlobalCommPos;
# endif
{
  *GlobalComment = TokensVars.GlobalComment;
  *GlobalCommPos = TokensVars.GlobalCommPos;
}

void Tokens_GetTokensHeader
# ifdef __STDC__
(TokenTab_PosType *TOKENPos, Lists_tList *TOKENComment, TokenTab_PosType *TOKENCommPos)
# else
(TOKENPos, TOKENComment, TOKENCommPos)
TokenTab_PosType *TOKENPos;
Lists_tList *TOKENComment;
TokenTab_PosType *TOKENCommPos;
# endif
{
  *TOKENPos = TokensVars.TOKENPos;
  *TOKENComment = TokensVars.TOKENComment;
  *TOKENCommPos = TokensVars.TOKENCommPos;
}

BOOLEAN Tokens_GetDeclaration
# ifdef __STDC__
(Idents_tIdent *Token, TokenTab_PosType *TokenPos, BOOLEAN *HasCoding, TokenTab_PosType *EQUALPos, TokenTab_PosType *NumberPos, Lists_tList *Comment, TokenTab_PosType *CommPos)
# else
(Token, TokenPos, HasCoding, EQUALPos, NumberPos, Comment, CommPos)
Idents_tIdent *Token;
TokenTab_PosType *TokenPos;
BOOLEAN *HasCoding;
TokenTab_PosType *EQUALPos;
TokenTab_PosType *NumberPos;
Lists_tList *Comment;
TokenTab_PosType *CommPos;
# endif
{
  if (!ReadyForReading) {
    ERROR((STRING)"GetDeclaration: do not read", 27L);
  }
  if (RDecl == NIL) {
    return FALSE;
  } else {
    *Token = RDecl->Token;
    *TokenPos = RDecl->TokenPos;
    *HasCoding = RDecl->HasCoding;
    if (*HasCoding) {
      *EQUALPos = RDecl->U_1.V_1.EQUALPos;
      *NumberPos = RDecl->U_1.V_1.NumberPos;
    } else {
      EQUALPos->Line = 0;
      EQUALPos->Column = 0;
      NumberPos->Line = 0;
      NumberPos->Column = 0;
    }
    *Comment = RDecl->Comment;
    *CommPos = RDecl->CommPos;
    RDecl = RDecl->Next;
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

void Tokens__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Lists__init();
    TokenTab__init();
    Idents__init();
    Lists__init();
    Strings__init();
    StringMem__init();
    TokenTab__init();
    Memory__init();
    Idents__init();
    TokenTab__init();
    Errors__init();
    Positions__init();

    StartDecl = NIL;
    WDecl = NIL;
    RDecl = NIL;
    ReadyForReading = FALSE;
    {
      register struct S_2 *W_1 = &TokensVars;

      Lists_MakeList(&W_1->GlobalComment);
      W_1->GlobalCommPos.Line = 0;
      W_1->GlobalCommPos.Column = 0;
      Lists_MakeList(&W_1->TOKENComment);
      W_1->TOKENCommPos.Line = 0;
      W_1->TOKENCommPos.Column = 0;
    }
  }
}
