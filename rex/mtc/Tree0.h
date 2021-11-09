#define DEFINITION_Tree0

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#define Tree0_NoTree0   NIL
#define Tree0_Node   1
#define Tree0_Node1   2
#define Tree0_Option   3
#define Tree0_Repetition   4
#define Tree0_Node2   5
#define Tree0_List   6
#define Tree0_Sequence   7
#define Tree0_Alternative   8
#define Tree0_Ch   9
#define Tree0_Set   10
#define Tree0_String   11
#define Tree0_Rule   12
#define Tree0_Pattern   13
typedef struct Tree0_15 *Tree0_tTree0;
typedef void (*Tree0_tProcTree) ARGS((Tree0_tTree0));
typedef struct Tree0_1 {
    SHORTCARD yyKind, yyMark;
} Tree0_yytNodeHead;
typedef struct Tree0_2 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
} Tree0_yNode;
typedef struct Tree0_3 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Son1;
} Tree0_yNode1;
typedef struct Tree0_4 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Son1;
} Tree0_yOption;
typedef struct Tree0_5 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Son1;
} Tree0_yRepetition;
typedef struct Tree0_6 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Son1;
    Tree0_tTree0 Son2;
} Tree0_yNode2;
typedef struct Tree0_7 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Son1;
    Tree0_tTree0 Son2;
} Tree0_yList;
typedef struct Tree0_8 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Son1;
    Tree0_tTree0 Son2;
} Tree0_ySequence;
typedef struct Tree0_9 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Son1;
    Tree0_tTree0 Son2;
} Tree0_yAlternative;
typedef struct Tree0_10 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    CHAR Ch;
} Tree0_yCh;
typedef struct Tree0_11 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Sets_tSet Set;
    SHORTCARD card;
} Tree0_ySet;
typedef struct Tree0_12 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    StringMem_tStringRef String;
} Tree0_yString;
typedef struct Tree0_13 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Tree0_tTree0 Patterns;
    Texts_tText TargetCode;
    SHORTCARD Line;
    SHORTCARD CodeMode;
    SHORTCARD RuleNr;
} Tree0_yRule;
typedef struct Tree0_14 {
    Tree0_yytNodeHead yyHead;
    Tree_tTree Tree;
    BOOLEAN IsConstantRE;
    SHORTINT LeafCount;
    SHORTINT NodeCount;
    Sets_tSet StartStates;
    Tree0_tTree0 RegExpr;
    Tree0_tTree0 RightContext;
    SHORTCARD PatternNr;
    Positions_tPosition Position;
    SHORTINT card;
} Tree0_yPattern;
typedef struct Tree0_15 {
    union {
        struct {
            SHORTCARD Kind;
        } V_1;
        struct {
            Tree0_yytNodeHead yyHead;
        } V_2;
        struct {
            Tree0_yNode Node;
        } V_3;
        struct {
            Tree0_yNode1 Node1;
        } V_4;
        struct {
            Tree0_yOption Option;
        } V_5;
        struct {
            Tree0_yRepetition Repetition;
        } V_6;
        struct {
            Tree0_yNode2 Node2;
        } V_7;
        struct {
            Tree0_yList List;
        } V_8;
        struct {
            Tree0_ySequence Sequence;
        } V_9;
        struct {
            Tree0_yAlternative Alternative;
        } V_10;
        struct {
            Tree0_yCh Ch;
        } V_11;
        struct {
            Tree0_ySet Set;
        } V_12;
        struct {
            Tree0_yString String;
        } V_13;
        struct {
            Tree0_yRule Rule;
        } V_14;
        struct {
            Tree0_yPattern Pattern;
        } V_15;
    } U_1;
} Tree0_yyNode;
extern Tree0_tTree0 Tree0_Tree0Root;
extern LONGCARD Tree0_HeapUsed;
extern ADDRESS Tree0_yyPoolFreePtr, Tree0_yyPoolMaxPtr;
extern struct Tree0_16 {
    SHORTCARD A[13 + 1];
} Tree0_yyNodeSize;
extern PROC Tree0_yyExit;
extern Tree0_tTree0 Tree0_yyAlloc ARGS(());
extern Tree0_tTree0 Tree0_MakeTree0 ARGS((SHORTCARD Kind));
extern BOOLEAN Tree0_IsType ARGS((Tree0_tTree0 Tree, SHORTCARD Kind));
extern Tree0_tTree0 Tree0_mNode ARGS(());
extern Tree0_tTree0 Tree0_mNode1 ARGS((Tree0_tTree0 pSon1));
extern Tree0_tTree0 Tree0_mOption ARGS((Tree0_tTree0 pSon1));
extern Tree0_tTree0 Tree0_mRepetition ARGS((Tree0_tTree0 pSon1));
extern Tree0_tTree0 Tree0_mNode2 ARGS((Tree0_tTree0 pSon1, Tree0_tTree0 pSon2));
extern Tree0_tTree0 Tree0_mList ARGS((Tree0_tTree0 pSon1, Tree0_tTree0 pSon2));
extern Tree0_tTree0 Tree0_mSequence ARGS((Tree0_tTree0 pSon1, Tree0_tTree0 pSon2));
extern Tree0_tTree0 Tree0_mAlternative ARGS((Tree0_tTree0 pSon1, Tree0_tTree0 pSon2));
extern Tree0_tTree0 Tree0_mCh ARGS((CHAR pCh));
extern Tree0_tTree0 Tree0_mSet ARGS((Sets_tSet pSet));
extern Tree0_tTree0 Tree0_mString ARGS((StringMem_tStringRef pString));
extern Tree0_tTree0 Tree0_mRule ARGS((Tree0_tTree0 pPatterns, Texts_tText pTargetCode, SHORTCARD pLine, SHORTCARD pCodeMode, SHORTCARD pRuleNr));
extern Tree0_tTree0 Tree0_mPattern ARGS((Sets_tSet pStartStates, Tree0_tTree0 pRegExpr, Tree0_tTree0 pRightContext, SHORTCARD pPatternNr, Positions_tPosition pPosition));
extern void Tree0_ReleaseTree0Module ARGS(());
extern void Tree0_WriteTree0 ARGS((IO_tFile f, Tree0_tTree0 Tree));
extern void Tree0_TraverseTree0TD ARGS((Tree0_tTree0 Tree, Tree0_tProcTree Proc));
extern void Tree0_BeginTree0 ARGS(());
extern void Tree0_CloseTree0 ARGS(());
extern void Tree0__init();
