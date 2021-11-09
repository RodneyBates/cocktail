#define DEFINITION_Tree

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

#define Tree_NoTree   NIL
#define Tree_nList   1
#define Tree_nRule   2
#define Tree_nPattern   3
#define Tree_nAlternative   4
#define Tree_nSequence   5
#define Tree_nRepetition   6
#define Tree_nOption   7
#define Tree_nChar   8
#define Tree_nSet   9
#define Tree_nString   10
typedef struct Tree_9 *Tree_tTree;
typedef struct Tree_1 {
    SHORTCARD Rule;
} Tree_Node0;
typedef struct Tree_2 {
    SHORTCARD Rule;
    Tree_tTree Son1;
} Tree_Node1;
typedef struct Tree_3 {
    SHORTCARD Rule;
    Tree_tTree Son1;
    Tree_tTree Son2;
} Tree_Node2;
typedef struct Tree_4 {
    SHORTCARD Rule;
    CHAR Ch;
} Tree_NodeCh;
typedef struct Tree_5 {
    SHORTCARD Rule;
    Sets_tSet Set;
} Tree_NodeSet;
typedef struct Tree_6 {
    SHORTCARD Rule;
    StringMem_tStringRef String;
} Tree_NodeString;
typedef struct Tree_7 {
    SHORTCARD Rule;
    Tree_tTree Patterns;
    Texts_tText TargetCode;
    SHORTCARD Line;
    SHORTCARD CodeMode;
    SHORTCARD RuleNr;
} Tree_NodeRule;
typedef struct Tree_8 {
    SHORTCARD Rule;
    Sets_tSet StartStates;
    Tree_tTree RegExpr;
    Tree_tTree RightContext;
    BOOLEAN IsConstantRE;
    SHORTCARD PatternNr;
    Positions_tPosition Position;
} Tree_NodePattern;
typedef struct Tree_9 {
    union {
        struct {
            Tree_Node0 vNode0;
        } V_1;
        struct {
            Tree_Node1 vNode1;
        } V_2;
        struct {
            Tree_Node2 vNode2;
        } V_3;
        struct {
            Tree_NodeCh vNodeCh;
        } V_4;
        struct {
            Tree_NodeSet vNodeSet;
        } V_5;
        struct {
            Tree_NodeString vNodeString;
        } V_6;
        struct {
            Tree_NodeRule vNodeRule;
        } V_7;
        struct {
            Tree_NodePattern vNodePattern;
        } V_8;
    } U_1;
} Tree_Node;
extern Tree_tTree Tree_MakeTree1 ARGS((SHORTCARD pRule, Tree_tTree pSon1));
extern Tree_tTree Tree_MakeTree2 ARGS((SHORTCARD pRule, Tree_tTree pSon1, Tree_tTree pSon2));
extern Tree_tTree Tree_MakeTreeCh ARGS((SHORTCARD pRule, CHAR pCh));
extern Tree_tTree Tree_MakeTreeSet ARGS((SHORTCARD pRule, Sets_tSet pSet));
extern Tree_tTree Tree_MakeTreeString ARGS((SHORTCARD pRule, StringMem_tStringRef pString));
extern Tree_tTree Tree_MakeTreeRule ARGS((SHORTCARD pRule, Tree_tTree pPatterns, Texts_tText pTargetCode, SHORTCARD pLine, SHORTCARD pCodeMode, SHORTCARD pRuleNr));
extern Tree_tTree Tree_MakeTreePattern ARGS((SHORTCARD pRule, Sets_tSet pStartStates, Tree_tTree pRegExpr, Tree_tTree pRightContext, BOOLEAN pIsConstantRE, SHORTCARD pPatternNr, Positions_tPosition pPosition));
extern void Tree_WriteTree ARGS((Tree_tTree t));
extern void Tree__init();
