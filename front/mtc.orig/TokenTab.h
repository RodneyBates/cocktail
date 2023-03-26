#define DEFINITION_TokenTab

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#define TokenTab_MINTerm   0
#define TokenTab_cMAXTerm   1000
#define TokenTab_MINNonTerm   (TokenTab_cMAXTerm + 1)
#define TokenTab_cMAXNonTerm   2500
#define TokenTab_EndOfToken   0
extern SHORTCARD TokenTab_MAXTerm;
extern SHORTCARD TokenTab_MAXNonTerm;
typedef Positions_tPosition TokenTab_PosType;
#define TokenTab_Term        0
#define TokenTab_NonTerm        1
#define TokenTab_None        2
typedef unsigned char TokenTab_TokenType;
typedef SHORTCARD TokenTab_NonTerminal;
typedef SHORTCARD TokenTab_Vocabulary;
typedef SHORTCARD TokenTab_Terminal;
typedef SHORTCARD TokenTab_Prio;
#define TokenTab_NoError        0
#define TokenTab_SymbolExists        1
#define TokenTab_CodeExists        2
#define TokenTab_OutOfRange        3
#define TokenTab_NotExists        4
#define TokenTab_NoIntCode        5
#define TokenTab_NotTerm        6
typedef unsigned char TokenTab_TokenError;
extern void TokenTab_MakeTerm ARGS((Idents_tIdent sym, TokenTab_Terminal *ter, TokenTab_TokenError *Error, TokenTab_PosType pos));
extern void TokenTab_MakeDefTerm ARGS((Idents_tIdent *sym, TokenTab_TokenError *Error, TokenTab_PosType pos));
extern void TokenTab_CompleteDefTerm ARGS((Idents_tIdent sym, TokenTab_TokenError *Error));
extern TokenTab_Vocabulary TokenTab_MakeVoc ARGS((Idents_tIdent sym, TokenTab_PosType symPos));
extern void TokenTab_SetNontermPos ARGS((Idents_tIdent sym, TokenTab_PosType pos));
extern TokenTab_TokenType TokenTab_GetTokenType ARGS((TokenTab_Vocabulary voc));
extern TokenTab_Vocabulary TokenTab_SymbolToToken ARGS((Idents_tIdent sym, TokenTab_TokenError *Error));
extern Idents_tIdent TokenTab_TokenToSymbol ARGS((TokenTab_Vocabulary voc, TokenTab_TokenError *Error));
extern void TokenTab_GetTokenPos ARGS((TokenTab_Vocabulary voc, TokenTab_PosType *pos));
extern void TokenTab_PutPrio ARGS((TokenTab_Vocabulary voc, TokenTab_Prio p));
extern TokenTab_Prio TokenTab_GetPrio ARGS((TokenTab_Vocabulary voc));
extern void TokenTab_InitTokenTable ARGS(());
extern void TokenTab__init();
