#define DEFINITION_Rules

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#define Rules_Plus        0
#define Rules_Star        1
#define Rules_Optional        2
#define Rules_Bracket        3
#define Rules_Sequence        4
#define Rules_Separator        5
#define Rules_Alternative        6
#define Rules_ArtAlternative        7
#define Rules_Action        8
#define Rules_TermLeaf        9
#define Rules_NonTermLeaf        10
#define Rules_NoOperation        11
typedef unsigned char Rules_Operation;
typedef Rules_Operation Rules_UnaryOperation;
typedef Rules_Operation Rules_BracketOperation;
typedef Rules_Operation Rules_BinaryOperation;
typedef Rules_Operation Rules_ArtificialOperation;
typedef Rules_Operation Rules_LeafOperation;
typedef OPAQUE Rules_Expression;
typedef OPAQUE Rules_MRules;
extern Rules_Expression Rules_NoExpression;
extern Rules_Expression Rules_MakeLeafNode ARGS((Idents_tIdent Sym, TokenTab_PosType Pos));
extern Rules_Expression Rules_MakeActionNode ARGS((Lists_tList Act, TokenTab_PosType Pos));
extern Rules_Expression Rules_MakeUnaryNode ARGS((Rules_UnaryOperation Art, TokenTab_PosType Pos, Rules_Expression Son));
extern Rules_Expression Rules_MakeBracketNode ARGS((Rules_BracketOperation Art, TokenTab_PosType Pos, TokenTab_PosType SecPos, Rules_Expression Son));
extern Rules_Expression Rules_MakeBinaryNode ARGS((Rules_BinaryOperation Art, TokenTab_PosType Pos, Rules_Expression LSon, Rules_Expression RSon));
extern Rules_Expression Rules_MakePrioAlternativeNode ARGS((TokenTab_PosType Pos, Rules_Expression LSon, Rules_Expression RSon, BOOLEAN HasPrio, TokenTab_PosType PRIOPos, Idents_tIdent PrioSym, TokenTab_PosType PrioSymPos));
extern void Rules_AppendArtificialNode ARGS((TokenTab_PosType Pos, TokenTab_PosType SecPos, Rules_Expression *Expr, Rules_Expression New));
extern void Rules_PutNodeSpecial ARGS((Rules_Expression Exp, ADDRESS Spec));
extern void Rules_MakeRule ARGS((Idents_tIdent Left, TokenTab_PosType LeftPos, TokenTab_PosType ColonPos, Rules_Expression Right, Lists_tList Comment, TokenTab_PosType CommPos, TokenTab_PosType PointPos, BOOLEAN HasPrio, TokenTab_PosType PRIOPos, Idents_tIdent PrioSym, TokenTab_PosType PrioSymPos));
extern void Rules_MakeRulesHeader ARGS((TokenTab_PosType RULESPos, Lists_tList Comment, TokenTab_PosType CommPos));
extern void Rules_InitRulesReading ARGS(());
extern Rules_Operation Rules_GetNodeOperation ARGS((Rules_Expression Exp));
extern void Rules_GetLeafNode ARGS((Rules_Expression Exp, TokenTab_Vocabulary *Voc, TokenTab_PosType *Pos));
extern void Rules_GetActionNode ARGS((Rules_Expression Expr, Lists_tList *Act, TokenTab_PosType *Pos));
extern void Rules_GetUnaryNode ARGS((Rules_Expression Expr, TokenTab_PosType *Pos, Rules_Expression *Son));
extern void Rules_GetBracketNode ARGS((Rules_Expression Expr, TokenTab_PosType *Pos, TokenTab_PosType *SecPos, Rules_Expression *Son));
extern void Rules_GetBinaryNode ARGS((Rules_Expression Expr, TokenTab_PosType *Pos, Rules_Expression *LSon, Rules_Expression *RSon));
extern void Rules_GetPrioAlternativeNode ARGS((Rules_Expression Expr, TokenTab_PosType *Pos, Rules_Expression *LSon, Rules_Expression *RSon, BOOLEAN *HasPrio, TokenTab_PosType *PRIOPos, Idents_tIdent *PrioSym, TokenTab_PosType *PrioSymPos));
extern void Rules_GetArtificialNode ARGS((Rules_Expression Expr, TokenTab_PosType *Pos, TokenTab_PosType *SecPos, Rules_Expression *LSon, Rules_Expression *RSon));
extern ADDRESS Rules_GetNodeSpecial ARGS((Rules_Expression Exp));
extern BOOLEAN Rules_GetRule ARGS((TokenTab_NonTerminal *Left, TokenTab_PosType *LeftPos, TokenTab_PosType *ColonPos, Rules_Expression *Right, Lists_tList *Comment, TokenTab_PosType *CommPos, TokenTab_PosType *PointPos, BOOLEAN *HasPrio, TokenTab_PosType *PRIOPos, TokenTab_Terminal *PrioSym, TokenTab_PosType *PrioSymPos));
extern BOOLEAN Rules_GetEssentialRule ARGS((TokenTab_NonTerminal *Left, Rules_Expression *Right, BOOLEAN *HasPrio));
extern void Rules_GetRulesHeader ARGS((TokenTab_PosType *RULESPos, Lists_tList *Comment, TokenTab_PosType *CommPos));
extern void Rules__init();
