#define DEFINITION_Tokens

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

extern void Tokens_MakeGlobalHeader ARGS((Lists_tList GlobalComment, TokenTab_PosType GlobalCommPos));
extern void Tokens_MakeTokensHeader ARGS((TokenTab_PosType TOKENPos, Lists_tList TOKENComment, TokenTab_PosType TOKENCommPos));
extern void Tokens_MakeDeclaration ARGS((Idents_tIdent Token, TokenTab_PosType TokenPos, BOOLEAN HasCoding, TokenTab_PosType EQUALPos, TokenTab_Terminal Number, TokenTab_PosType NumberPos, Lists_tList Comment, TokenTab_PosType CommPos));
extern void Tokens_CompleteDeclarations ARGS(());
extern void Tokens_GetGlobalHeader ARGS((Lists_tList *GlobalComment, TokenTab_PosType *GlobalCommPos));
extern void Tokens_GetTokensHeader ARGS((TokenTab_PosType *TOKENPos, Lists_tList *TOKENComment, TokenTab_PosType *TOKENCommPos));
extern BOOLEAN Tokens_GetDeclaration ARGS((Idents_tIdent *Token, TokenTab_PosType *TokenPos, BOOLEAN *HasCoding, TokenTab_PosType *EQUALPos, TokenTab_PosType *NumberPos, Lists_tList *Comment, TokenTab_PosType *CommPos));
extern void Tokens__init();
