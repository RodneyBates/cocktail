#include "SYSTEM_.h"

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

SHORTCARD TokenTab_MAXTerm;
SHORTCARD TokenTab_MAXNonTerm;

#define eNoIntCode   25
#define eTokenOverflow   26
#define MaxTokens   TokenTab_cMAXNonTerm
#define NoValue   MaxTokens
#define DefValue   (MaxTokens + 1)
typedef LONGCARD Symbols;
static struct S_1 {
    TokenTab_Vocabulary A[MaxTokens + 1];
} ExToInt;
static struct S_2 {
    TokenTab_PosType A[MaxTokens + 1];
} ExToPos;
static struct S_3 {
    BOOLEAN A[MaxTokens + 1];
} ExPosSet;
static struct S_4 {
    Symbols A[TokenTab_cMAXNonTerm + 2 + 1];
} IntToEx;
static struct S_5 {
    TokenTab_Prio A[TokenTab_cMAXNonTerm + 2 + 1];
} PrioField;
static LONGCARD DefaultVoc;
static CARDINAL i;
static BOOLEAN GetNextNonTerminalAllowed;
static LONGCARD Actualnt;
static TokenTab_Terminal ter;
static TokenTab_TokenError err;
static Strings_tString s;
static TokenTab_PosType pos;
static void NextDefault ARGS(());
static void ERROR ARGS((CHAR a[], LONGCARD ));


void TokenTab_MakeTerm
# ifdef __STDC__
(Idents_tIdent sym, TokenTab_Terminal *ter, TokenTab_TokenError *Error, TokenTab_PosType pos)
# else
(sym, ter, Error, pos)
Idents_tIdent sym;
TokenTab_Terminal *ter;
TokenTab_TokenError *Error;
TokenTab_PosType pos;
# endif
{
  if (sym > TokenTab_cMAXNonTerm) {
    *Error = TokenTab_OutOfRange;
  } else if (ExToInt.A[sym] != NoValue) {
    *Error = TokenTab_SymbolExists;
    *ter = ExToInt.A[sym];
  } else if (IntToEx.A[*ter] != NoValue) {
    *Error = TokenTab_CodeExists;
  } else {
    ExToInt.A[sym] = *ter;
    IntToEx.A[*ter] = sym;
    *Error = TokenTab_NoError;
    ExToPos.A[sym] = pos;
    if (*ter > TokenTab_MAXTerm) {
      TokenTab_MAXTerm = *ter;
    }
  }
}

void TokenTab_MakeDefTerm
# ifdef __STDC__
(Idents_tIdent *sym, TokenTab_TokenError *Error, TokenTab_PosType pos)
# else
(sym, Error, pos)
Idents_tIdent *sym;
TokenTab_TokenError *Error;
TokenTab_PosType pos;
# endif
{
  if (ExToInt.A[*sym] != NoValue) {
    *Error = TokenTab_SymbolExists;
  } else {
    ExToInt.A[*sym] = DefValue;
    *Error = TokenTab_NoError;
    ExToPos.A[*sym] = pos;
  }
}

void TokenTab_CompleteDefTerm
# ifdef __STDC__
(Idents_tIdent sym, TokenTab_TokenError *Error)
# else
(sym, Error)
Idents_tIdent sym;
TokenTab_TokenError *Error;
# endif
{
  if (ExToInt.A[sym] == NoValue) {
    *Error = TokenTab_NotExists;
  } else if (ExToInt.A[sym] != DefValue) {
    if (TokenTab_GetTokenType(ExToInt.A[sym]) == TokenTab_NonTerm) {
      *Error = TokenTab_NotTerm;
    } else {
      *Error = TokenTab_CodeExists;
    }
  } else {
    NextDefault();
    if (DefaultVoc <= TokenTab_cMAXTerm) {
      ExToInt.A[sym] = DefaultVoc;
      IntToEx.A[DefaultVoc] = sym;
      if (DefaultVoc > TokenTab_MAXTerm) {
        TokenTab_MAXTerm = DefaultVoc;
      }
      *Error = TokenTab_NoError;
    } else {
      Errors_ErrorMessageI((LONGCARD)eTokenOverflow, (LONGCARD)Errors_eRestriction, Positions_NoPosition, (LONGCARD)Errors_eIdent, ADR(sym));
    }
  }
}

TokenTab_Vocabulary TokenTab_MakeVoc
# ifdef __STDC__
(Idents_tIdent sym, TokenTab_PosType symPos)
# else
(sym, symPos)
Idents_tIdent sym;
TokenTab_PosType symPos;
# endif
{
  if (ExToInt.A[sym] == DefValue) {
    Errors_ErrorMessageI((LONGCARD)eNoIntCode, (LONGCARD)Errors_eFatal, symPos, (LONGCARD)Errors_eIdent, ADR(sym));
  } else if (ExToInt.A[sym] != NoValue) {
    if (ExToPos.A[sym].Line > symPos.Line || ExToPos.A[sym].Line == symPos.Line && ExToPos.A[sym].Column > symPos.Column) {
      if (symPos.Line != 0 && symPos.Column != 0) {
        ExToPos.A[sym] = symPos;
      }
    }
    return ExToInt.A[sym];
  } else {
    INC(TokenTab_MAXNonTerm);
    if (TokenTab_MAXNonTerm >= MaxTokens) {
      Errors_ErrorMessageI((LONGCARD)eTokenOverflow, (LONGCARD)Errors_eRestriction, symPos, (LONGCARD)Errors_eIdent, ADR(sym));
    } else {
      ExToPos.A[sym] = symPos;
      ExToInt.A[sym] = TokenTab_MAXNonTerm;
      IntToEx.A[TokenTab_MAXNonTerm] = sym;
      return TokenTab_MAXNonTerm;
    }
  }
}

void TokenTab_SetNontermPos
# ifdef __STDC__
(Idents_tIdent sym, TokenTab_PosType pos)
# else
(sym, pos)
Idents_tIdent sym;
TokenTab_PosType pos;
# endif
{
  if (!ExPosSet.A[sym]) {
    ExToPos.A[sym] = pos;
    ExPosSet.A[sym] = TRUE;
  }
}

TokenTab_TokenType TokenTab_GetTokenType
# ifdef __STDC__
(TokenTab_Vocabulary voc)
# else
(voc)
TokenTab_Vocabulary voc;
# endif
{
  if (IntToEx.A[voc] == NoValue || voc >= MaxTokens) {
    return TokenTab_None;
  } else if (voc <= TokenTab_cMAXTerm) {
    return TokenTab_Term;
  } else {
    return TokenTab_NonTerm;
  }
}

TokenTab_Vocabulary TokenTab_SymbolToToken
# ifdef __STDC__
(Idents_tIdent sym, TokenTab_TokenError *Error)
# else
(sym, Error)
Idents_tIdent sym;
TokenTab_TokenError *Error;
# endif
{
  if (ExToInt.A[sym] == NoValue) {
    *Error = TokenTab_NotExists;
  } else if (ExToInt.A[sym] == DefValue) {
    *Error = TokenTab_NoIntCode;
  } else {
    *Error = TokenTab_NoError;
  }
  return ExToInt.A[sym];
}

Idents_tIdent TokenTab_TokenToSymbol
# ifdef __STDC__
(TokenTab_Vocabulary voc, TokenTab_TokenError *Error)
# else
(voc, Error)
TokenTab_Vocabulary voc;
TokenTab_TokenError *Error;
# endif
{
  if (IntToEx.A[voc] == NoValue) {
    *Error = TokenTab_NotExists;
  } else {
    *Error = TokenTab_NoError;
  }
  return IntToEx.A[voc];
}

void TokenTab_GetTokenPos
# ifdef __STDC__
(TokenTab_Vocabulary voc, TokenTab_PosType *pos)
# else
(voc, pos)
TokenTab_Vocabulary voc;
TokenTab_PosType *pos;
# endif
{
  Idents_tIdent sym;

  sym = IntToEx.A[voc];
  if (sym == NoValue) {
    pos->Line = 0;
    pos->Column = 0;
  } else {
    *pos = ExToPos.A[sym];
  }
}

void TokenTab_PutPrio
# ifdef __STDC__
(TokenTab_Vocabulary voc, TokenTab_Prio p)
# else
(voc, p)
TokenTab_Vocabulary voc;
TokenTab_Prio p;
# endif
{
  PrioField.A[voc] = p;
}

TokenTab_Prio TokenTab_GetPrio
# ifdef __STDC__
(TokenTab_Vocabulary voc)
# else
(voc)
TokenTab_Vocabulary voc;
# endif
{
  return PrioField.A[voc];
}

static void NextDefault
# ifdef __STDC__
()
# else
()
# endif
{
  while (IntToEx.A[DefaultVoc] != NoValue && DefaultVoc < TokenTab_cMAXTerm + 1) {
    INC(DefaultVoc);
  }
}

void TokenTab_InitTokenTable
# ifdef __STDC__
()
# else
()
# endif
{
  GetNextNonTerminalAllowed = FALSE;
  for (i = 0; i <= MaxTokens; i += 1) {
    IntToEx.A[i] = NoValue;
    ExToInt.A[i] = NoValue;
    ExPosSet.A[i] = FALSE;
    PrioField.A[i] = 0;
  }
  DefaultVoc = 1;
  TokenTab_MAXNonTerm = TokenTab_cMAXTerm;
  Strings_ArrayToString((STRING)"_EndOfFile", 10L, &s);
  ter = TokenTab_EndOfToken;
  pos.Line = 0;
  pos.Column = 0;
  TokenTab_MakeTerm(Idents_MakeIdent(&s), &ter, &err, pos);
  if (err != TokenTab_NoError) {
    ERROR((STRING)"TokenTab.InitTokenTable", 23L);
  }
  TokenTab_MAXTerm = 0;
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

void TokenTab__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Strings__init();
    Idents__init();
    Positions__init();
    Strings__init();
    Idents__init();
    Errors__init();
    Positions__init();

  }
}
