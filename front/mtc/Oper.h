#define DEFINITION_Oper

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#define Oper_Left        0
#define Oper_Right        1
#define Oper_None        2
typedef unsigned char Oper_OperKind;
extern void Oper_MakePriority ARGS((Oper_OperKind Art, TokenTab_PosType Pos));
extern void Oper_CompletePriority ARGS((Lists_tList Comment, TokenTab_PosType CommPos));
extern void Oper_MakeOperator ARGS((Idents_tIdent Token, TokenTab_PosType TokenPos));
extern void Oper_MakeOperHeader ARGS((TokenTab_PosType OPERPos, Lists_tList Comment, TokenTab_PosType CommPos));
extern void Oper_InitPrioReading ARGS(());
extern BOOLEAN Oper_GetOperHeader ARGS((TokenTab_PosType *OPERPos, Lists_tList *Comment, TokenTab_PosType *CommPos));
extern BOOLEAN Oper_GetPriority ARGS((Oper_OperKind *Art, TokenTab_PosType *Pos, Lists_tList *Comment, TokenTab_PosType *CommPos));
extern BOOLEAN Oper_GetOperator ARGS((TokenTab_Vocabulary *Token, TokenTab_PosType *TokenPos));
extern void Oper__init();
