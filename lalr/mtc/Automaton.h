#define DEFINITION_Automaton

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#define Automaton_Infinite   65535
#define Automaton_Infinite2   1000000
typedef SHORTCARD Automaton_tStateIndex;
typedef LONGCARD Automaton_tItemIndex;
typedef SHORTCARD Automaton_tProdIndex;
typedef LONGCARD Automaton_tIndex;
typedef struct Automaton_1 {
    LONGINT Used;
    struct Automaton_2 {
        Automaton_tIndex A[Automaton_Infinite - 1 + 1];
    } *Array;
    LONGINT Count;
} Automaton_tIndexList;
typedef struct Automaton_3 {
    LONGINT Used;
    struct Automaton_4 {
        Automaton_tItemIndex A[Automaton_Infinite - 1 + 1];
    } *Array;
    LONGINT Count;
} Automaton_tItemIndexList;
typedef struct Automaton_5 {
    Automaton_tProdIndex Index;
    SHORTCARD Value;
} Automaton_tProdListElmt;
typedef struct Automaton_6 {
    LONGINT Used;
    struct Automaton_7 {
        Automaton_tProdListElmt A[Automaton_Infinite - 1 + 1];
    } *Array;
    LONGINT Count;
} Automaton_tProdIndexList;
#define Automaton_right        0
#define Automaton_left        1
#define Automaton_none        2
#define Automaton_nonassoc        3
typedef unsigned char Automaton_tAss;
typedef struct Automaton_8 {
    TokenTab_Prio Pri;
    Automaton_tAss Ass;
} Automaton_tOper;
typedef struct Automaton_9 {
    Automaton_tIndex ProdNo;
    Automaton_tIndexList Reduce;
    Lists_tList Act;
    TokenTab_PosType ActPos;
    Automaton_tAss Ass;
    TokenTab_Prio Pri;
    Automaton_tIndex Len;
    TokenTab_NonTerminal Left;
    struct Automaton_10 {
        SHORTCARD A[Automaton_Infinite - 1 + 1];
    } Right;
} *Automaton_tProduction;
#define Automaton_NoRep        0
#define Automaton_TermRep        1
#define Automaton_NonTermRep        2
#define Automaton_RedRep        3
typedef unsigned char Automaton_tRep;
#define Automaton_sNone        0
#define Automaton_sRead        1
#define Automaton_sTerm        2
#define Automaton_sNonterm        3
typedef unsigned char Automaton_tStateKind;
typedef struct Automaton_11 {
    Automaton_tStateIndex Next;
    Automaton_tProdIndex Prod;
    Automaton_tIndex Pos;
    Automaton_tItemIndex RepNo;
    Automaton_tRep Rep;
    BOOLEAN EmptyReadSet;
    Sets_tSet Set;
    Sets_tSet ReadSet;
    Automaton_tItemIndexList Relation;
    TokenTab_Vocabulary Read;
    SHORTCARD Number;
} Automaton_tItem;
typedef struct Automaton_12 {
    Automaton_tIndex Size;
    Automaton_tItemIndex Items;
    Automaton_tIndex NewNumber;
    Automaton_tStateKind Kind;
} Automaton_tState;
extern BOOLEAN Automaton_IsBnf;
extern struct Automaton_13 {
    WORD A[Automaton_Infinite + 1];
} *Automaton_ProdArrayPtr;
extern LONGINT Automaton_ProdIndex;
extern CARDINAL Automaton_ProdCount;
extern struct Automaton_14 {
    Automaton_tItem A[Automaton_Infinite2 - 1 + 1];
} *Automaton_ItemArrayPtr;
extern LONGINT Automaton_ItemIndex;
extern struct Automaton_15 {
    Automaton_tState A[Automaton_Infinite - 1 + 1];
} *Automaton_StateArrayPtr;
extern LONGINT Automaton_StateIndex;
extern struct Automaton_16 {
    Automaton_tProdIndexList A[TokenTab_cMAXNonTerm - TokenTab_MINNonTerm + 1];
} Automaton_ProdList;
extern struct Automaton_17 {
    Automaton_tOper A[TokenTab_cMAXTerm + 1];
} Automaton_OperArray;
extern TokenTab_NonTerminal Automaton_StartSymbol;
extern void Automaton_InitAutomaton ARGS(());
extern Automaton_tStateIndex Automaton_MakeFirstState ARGS(());
extern void Automaton_GotoSet ARGS((Automaton_tStateIndex i, Sets_tSet *s));
extern Automaton_tStateIndex Automaton_Goto ARGS((Automaton_tStateIndex i, TokenTab_Vocabulary s, BOOLEAN *new));
extern Automaton_tProdIndex Automaton_NextProdIndex ARGS((Automaton_tProdIndex Index));
extern void Automaton__init();
