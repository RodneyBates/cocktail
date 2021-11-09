#define DEFINITION_Tree

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Environs
#include "Environs.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#define Tree_cNoSel        0
#define Tree_cSel        1
#define Tree_cTreeSel        2
typedef unsigned char Tree_tSelMode;
typedef ADDRESS Tree_yyEstra;
#define Tree_NoTree   NIL
#define Tree_spec   1
#define Tree_Spec   2
#define Tree_classes   3
#define Tree_Class0   4
#define Tree_Class   5
#define Tree_nodes   6
#define Tree_Node0   7
#define Tree_Node   8
#define Tree_sons   9
#define Tree_Son0   10
#define Tree_Son   11
#define Tree_attributes   12
#define Tree_Attribute0   13
#define Tree_Attribute   14
#define Tree_functions   15
#define Tree_Function0   16
#define Tree_Function   17
#define Tree_result   18
#define Tree_NoResult   19
#define Tree_Type   20
#define Tree_domain   21
#define Tree_Ident0   22
#define Tree_Ident   23
#define Tree_directives   24
#define Tree_Directive0   25
#define Tree_Directive   26
#define Tree_pattern   27
#define Tree_Pattern1   28
#define Tree_Pattern   29
#define Tree_patterns   30
#define Tree_Patterns0   31
#define Tree_Patterns   32
#define Tree_condition   33
#define Tree_CondD   34
#define Tree_CondF   35
#define Tree_costs   36
#define Tree_CostD   37
#define Tree_CostN   38
#define Tree_CostF   39
#define Tree_code   40
#define Tree_CdStr   41
#define Tree_CdId   42
#define Tree_CdDot   43
#define Tree_CdComma   44
#define Tree_CdLPar   45
#define Tree_CdRPar   46
#define Tree_CdLBra   47
#define Tree_CdRBra   48
#define Tree_CdSpa   49
#define Tree_CdCom   50
#define Tree_CdRst   51
#define Tree_CdEnd   52
typedef struct Tree_54 *Tree_tTree;
typedef void (*Tree_tProcTree) ARGS((Tree_tTree));
typedef struct Tree_1 {
    SHORTCARD yyKind, yyMark;
} Tree_yytNodeHead;
typedef struct Tree_2 {
    Tree_yytNodeHead yyHead;
} Tree_yspec;
typedef struct Tree_3 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent name;
    Positions_tPosition pos;
    Idents_tIdent grna;
    Positions_tPosition grpos;
    Tree_tTree export;
    Tree_tTree global;
    Tree_tTree begin;
    Tree_tTree close;
    Tree_tTree classes;
    Tree_tTree functions;
} Tree_ySpec;
typedef struct Tree_4 {
    Tree_yytNodeHead yyHead;
} Tree_yclasses;
typedef struct Tree_5 {
    Tree_yytNodeHead yyHead;
} Tree_yClass0;
typedef struct Tree_6 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent suid;
    Positions_tPosition supos;
    Idents_tIdent clid;
    Positions_tPosition clpos;
    Tree_tTree nodes;
    Tree_tTree classes;
    BOOLEAN correct;
} Tree_yClass;
typedef struct Tree_7 {
    Tree_yytNodeHead yyHead;
} Tree_ynodes;
typedef struct Tree_8 {
    Tree_yytNodeHead yyHead;
} Tree_yNode0;
typedef struct Tree_9 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent name;
    Positions_tPosition napos;
    Idents_tIdent ident;
    Positions_tPosition idpos;
    Tree_tTree sons;
    Tree_tTree nodes;
    BOOLEAN correct;
} Tree_yNode;
typedef struct Tree_10 {
    Tree_yytNodeHead yyHead;
} Tree_ysons;
typedef struct Tree_11 {
    Tree_yytNodeHead yyHead;
} Tree_ySon0;
typedef struct Tree_12 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent name;
    Positions_tPosition napos;
    Idents_tIdent ident;
    Positions_tPosition idpos;
    Tree_tTree sons;
    BOOLEAN correct;
} Tree_ySon;
typedef struct Tree_13 {
    Tree_yytNodeHead yyHead;
} Tree_yattributes;
typedef struct Tree_14 {
    Tree_yytNodeHead yyHead;
} Tree_yAttribute0;
typedef struct Tree_15 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent ident;
    Positions_tPosition idpos;
    Idents_tIdent mod;
    Positions_tPosition mopos;
    Idents_tIdent type;
    Positions_tPosition typos;
    Tree_tTree attributes;
} Tree_yAttribute;
typedef struct Tree_16 {
    Tree_yytNodeHead yyHead;
} Tree_yfunctions;
typedef struct Tree_17 {
    Tree_yytNodeHead yyHead;
} Tree_yFunction0;
typedef struct Tree_18 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent name;
    Positions_tPosition napos;
    Tree_tTree in;
    Tree_tTree out;
    Tree_tTree result;
    Tree_tTree domain;
    Tree_tTree directives;
    Tree_tTree functions;
    Environs_tFunction funct;
    Sets_tSet domainset;
} Tree_yFunction;
typedef struct Tree_19 {
    Tree_yytNodeHead yyHead;
} Tree_yresult;
typedef struct Tree_20 {
    Tree_yytNodeHead yyHead;
} Tree_yNoResult;
typedef struct Tree_21 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent mod;
    Positions_tPosition mopos;
    Idents_tIdent type;
    Positions_tPosition typos;
} Tree_yType;
typedef struct Tree_22 {
    Tree_yytNodeHead yyHead;
} Tree_ydomain;
typedef struct Tree_23 {
    Tree_yytNodeHead yyHead;
} Tree_yIdent0;
typedef struct Tree_24 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent ident;
    Positions_tPosition idpos;
    Tree_tTree domain;
} Tree_yIdent;
typedef struct Tree_25 {
    Tree_yytNodeHead yyHead;
} Tree_ydirectives;
typedef struct Tree_26 {
    Tree_yytNodeHead yyHead;
} Tree_yDirective0;
typedef struct Tree_27 {
    Tree_yytNodeHead yyHead;
    Tree_tTree pattern;
    Tree_tTree condition;
    Tree_tTree costs;
    Tree_tTree decl;
    Tree_tTree instr;
    Tree_tTree directives;
    BOOLEAN correct;
    INTEGER number;
    Patterns_tPattern pat;
    BOOLEAN iter;
} Tree_yDirective;
typedef struct Tree_28 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
} Tree_ypattern;
typedef struct Tree_29 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Idents_tIdent sel;
    Positions_tPosition sepos;
    Idents_tIdent ident;
    Positions_tPosition idpos;
    BOOLEAN correct;
} Tree_yPattern1;
typedef struct Tree_30 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Idents_tIdent sel;
    Positions_tPosition sepos;
    Idents_tIdent ident;
    Positions_tPosition idpos;
    Tree_tTree patterns;
    BOOLEAN correct;
} Tree_yPattern;
typedef struct Tree_31 {
    Tree_yytNodeHead yyHead;
} Tree_ypatterns;
typedef struct Tree_32 {
    Tree_yytNodeHead yyHead;
} Tree_yPatterns0;
typedef struct Tree_33 {
    Tree_yytNodeHead yyHead;
    Tree_tTree pattern;
    Tree_tTree patterns;
} Tree_yPatterns;
typedef struct Tree_34 {
    Tree_yytNodeHead yyHead;
} Tree_ycondition;
typedef struct Tree_35 {
    Tree_yytNodeHead yyHead;
} Tree_yCondD;
typedef struct Tree_36 {
    Tree_yytNodeHead yyHead;
    Tree_tTree code;
} Tree_yCondF;
typedef struct Tree_37 {
    Tree_yytNodeHead yyHead;
} Tree_ycosts;
typedef struct Tree_38 {
    Tree_yytNodeHead yyHead;
} Tree_yCostD;
typedef struct Tree_39 {
    Tree_yytNodeHead yyHead;
    INTEGER value;
    Positions_tPosition vapos;
} Tree_yCostN;
typedef struct Tree_40 {
    Tree_yytNodeHead yyHead;
    Tree_tTree code;
} Tree_yCostF;
typedef struct Tree_41 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
} Tree_ycode;
typedef struct Tree_42 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Idents_tIdent ident;
    Tree_tTree code;
    Tree_tSelMode mode;
} Tree_yCdStr;
typedef struct Tree_43 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Idents_tIdent ident;
    Tree_tTree code;
    Tree_tSelMode mode;
} Tree_yCdId;
typedef struct Tree_44 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree code;
} Tree_yCdDot;
typedef struct Tree_45 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree code;
} Tree_yCdComma;
typedef struct Tree_46 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree code;
} Tree_yCdLPar;
typedef struct Tree_47 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree code;
} Tree_yCdRPar;
typedef struct Tree_48 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree code;
} Tree_yCdLBra;
typedef struct Tree_49 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree code;
} Tree_yCdRBra;
typedef struct Tree_50 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    StringMem_tStringRef ref;
    Tree_tTree code;
} Tree_yCdSpa;
typedef struct Tree_51 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    StringMem_tStringRef ref;
    Tree_tTree code;
} Tree_yCdCom;
typedef struct Tree_52 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    StringMem_tStringRef ref;
    Tree_tTree code;
} Tree_yCdRst;
typedef struct Tree_53 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
} Tree_yCdEnd;
typedef struct Tree_54 {
    union {
        struct {
            SHORTCARD Kind;
        } V_1;
        struct {
            Tree_yytNodeHead yyHead;
        } V_2;
        struct {
            Tree_yspec spec;
        } V_3;
        struct {
            Tree_ySpec Spec;
        } V_4;
        struct {
            Tree_yclasses classes;
        } V_5;
        struct {
            Tree_yClass0 Class0;
        } V_6;
        struct {
            Tree_yClass Class;
        } V_7;
        struct {
            Tree_ynodes nodes;
        } V_8;
        struct {
            Tree_yNode0 Node0;
        } V_9;
        struct {
            Tree_yNode Node;
        } V_10;
        struct {
            Tree_ysons sons;
        } V_11;
        struct {
            Tree_ySon0 Son0;
        } V_12;
        struct {
            Tree_ySon Son;
        } V_13;
        struct {
            Tree_yattributes attributes;
        } V_14;
        struct {
            Tree_yAttribute0 Attribute0;
        } V_15;
        struct {
            Tree_yAttribute Attribute;
        } V_16;
        struct {
            Tree_yfunctions functions;
        } V_17;
        struct {
            Tree_yFunction0 Function0;
        } V_18;
        struct {
            Tree_yFunction Function;
        } V_19;
        struct {
            Tree_yresult result;
        } V_20;
        struct {
            Tree_yNoResult NoResult;
        } V_21;
        struct {
            Tree_yType Type;
        } V_22;
        struct {
            Tree_ydomain domain;
        } V_23;
        struct {
            Tree_yIdent0 Ident0;
        } V_24;
        struct {
            Tree_yIdent Ident;
        } V_25;
        struct {
            Tree_ydirectives directives;
        } V_26;
        struct {
            Tree_yDirective0 Directive0;
        } V_27;
        struct {
            Tree_yDirective Directive;
        } V_28;
        struct {
            Tree_ypattern pattern;
        } V_29;
        struct {
            Tree_yPattern1 Pattern1;
        } V_30;
        struct {
            Tree_yPattern Pattern;
        } V_31;
        struct {
            Tree_ypatterns patterns;
        } V_32;
        struct {
            Tree_yPatterns0 Patterns0;
        } V_33;
        struct {
            Tree_yPatterns Patterns;
        } V_34;
        struct {
            Tree_ycondition condition;
        } V_35;
        struct {
            Tree_yCondD CondD;
        } V_36;
        struct {
            Tree_yCondF CondF;
        } V_37;
        struct {
            Tree_ycosts costs;
        } V_38;
        struct {
            Tree_yCostD CostD;
        } V_39;
        struct {
            Tree_yCostN CostN;
        } V_40;
        struct {
            Tree_yCostF CostF;
        } V_41;
        struct {
            Tree_ycode code;
        } V_42;
        struct {
            Tree_yCdStr CdStr;
        } V_43;
        struct {
            Tree_yCdId CdId;
        } V_44;
        struct {
            Tree_yCdDot CdDot;
        } V_45;
        struct {
            Tree_yCdComma CdComma;
        } V_46;
        struct {
            Tree_yCdLPar CdLPar;
        } V_47;
        struct {
            Tree_yCdRPar CdRPar;
        } V_48;
        struct {
            Tree_yCdLBra CdLBra;
        } V_49;
        struct {
            Tree_yCdRBra CdRBra;
        } V_50;
        struct {
            Tree_yCdSpa CdSpa;
        } V_51;
        struct {
            Tree_yCdCom CdCom;
        } V_52;
        struct {
            Tree_yCdRst CdRst;
        } V_53;
        struct {
            Tree_yCdEnd CdEnd;
        } V_54;
    } U_1;
} Tree_yyNode;
extern Tree_tTree Tree_TreeRoot;
extern LONGCARD Tree_HeapUsed;
extern ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
extern struct Tree_55 {
    SHORTCARD A[52 + 1];
} Tree_yyNodeSize;
extern PROC Tree_yyExit;
extern Tree_tTree Tree_yyAlloc ARGS(());
extern Tree_tTree Tree_MakeTree ARGS((SHORTCARD Kind));
extern BOOLEAN Tree_IsType ARGS((Tree_tTree Tree, SHORTCARD Kind));
extern Tree_tTree Tree_mspec ARGS(());
extern Tree_tTree Tree_mSpec ARGS((Idents_tIdent pname, Positions_tPosition ppos, Idents_tIdent pgrna, Positions_tPosition pgrpos, Tree_tTree pexport, Tree_tTree pglobal, Tree_tTree pbegin, Tree_tTree pclose, Tree_tTree pclasses, Tree_tTree pfunctions));
extern Tree_tTree Tree_mclasses ARGS(());
extern Tree_tTree Tree_mClass0 ARGS(());
extern Tree_tTree Tree_mClass ARGS((Idents_tIdent psuid, Positions_tPosition psupos, Idents_tIdent pclid, Positions_tPosition pclpos, Tree_tTree pnodes, Tree_tTree pclasses, BOOLEAN pcorrect));
extern Tree_tTree Tree_mnodes ARGS(());
extern Tree_tTree Tree_mNode0 ARGS(());
extern Tree_tTree Tree_mNode ARGS((Idents_tIdent pname, Positions_tPosition pnapos, Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree psons, Tree_tTree pnodes, BOOLEAN pcorrect));
extern Tree_tTree Tree_msons ARGS(());
extern Tree_tTree Tree_mSon0 ARGS(());
extern Tree_tTree Tree_mSon ARGS((Idents_tIdent pname, Positions_tPosition pnapos, Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree psons, BOOLEAN pcorrect));
extern Tree_tTree Tree_mattributes ARGS(());
extern Tree_tTree Tree_mAttribute0 ARGS(());
extern Tree_tTree Tree_mAttribute ARGS((Idents_tIdent pident, Positions_tPosition pidpos, Idents_tIdent pmod, Positions_tPosition pmopos, Idents_tIdent ptype, Positions_tPosition ptypos, Tree_tTree pattributes));
extern Tree_tTree Tree_mfunctions ARGS(());
extern Tree_tTree Tree_mFunction0 ARGS(());
extern Tree_tTree Tree_mFunction ARGS((Idents_tIdent pname, Positions_tPosition pnapos, Tree_tTree pin, Tree_tTree pout, Tree_tTree presult, Tree_tTree pdomain, Tree_tTree pdirectives, Tree_tTree pfunctions));
extern Tree_tTree Tree_mresult ARGS(());
extern Tree_tTree Tree_mNoResult ARGS(());
extern Tree_tTree Tree_mType ARGS((Idents_tIdent pmod, Positions_tPosition pmopos, Idents_tIdent ptype, Positions_tPosition ptypos));
extern Tree_tTree Tree_mdomain ARGS(());
extern Tree_tTree Tree_mIdent0 ARGS(());
extern Tree_tTree Tree_mIdent ARGS((Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree pdomain));
extern Tree_tTree Tree_mdirectives ARGS(());
extern Tree_tTree Tree_mDirective0 ARGS(());
extern Tree_tTree Tree_mDirective ARGS((Tree_tTree ppattern, Tree_tTree pcondition, Tree_tTree pcosts, Tree_tTree pdecl, Tree_tTree pinstr, Tree_tTree pdirectives, BOOLEAN pcorrect));
extern Tree_tTree Tree_mpattern ARGS((Positions_tPosition ppos));
extern Tree_tTree Tree_mPattern1 ARGS((Positions_tPosition ppos, Idents_tIdent psel, Positions_tPosition psepos, Idents_tIdent pident, Positions_tPosition pidpos, BOOLEAN pcorrect));
extern Tree_tTree Tree_mPattern ARGS((Positions_tPosition ppos, Idents_tIdent psel, Positions_tPosition psepos, Idents_tIdent pident, Positions_tPosition pidpos, Tree_tTree ppatterns, BOOLEAN pcorrect));
extern Tree_tTree Tree_mpatterns ARGS(());
extern Tree_tTree Tree_mPatterns0 ARGS(());
extern Tree_tTree Tree_mPatterns ARGS((Tree_tTree ppattern, Tree_tTree ppatterns));
extern Tree_tTree Tree_mcondition ARGS(());
extern Tree_tTree Tree_mCondD ARGS(());
extern Tree_tTree Tree_mCondF ARGS((Tree_tTree pcode));
extern Tree_tTree Tree_mcosts ARGS(());
extern Tree_tTree Tree_mCostD ARGS(());
extern Tree_tTree Tree_mCostN ARGS((INTEGER pvalue, Positions_tPosition pvapos));
extern Tree_tTree Tree_mCostF ARGS((Tree_tTree pcode));
extern Tree_tTree Tree_mcode ARGS((Positions_tPosition ppos));
extern Tree_tTree Tree_mCdStr ARGS((Positions_tPosition ppos, Idents_tIdent pident, Tree_tTree pcode));
extern Tree_tTree Tree_mCdId ARGS((Positions_tPosition ppos, Idents_tIdent pident, Tree_tTree pcode));
extern Tree_tTree Tree_mCdDot ARGS((Positions_tPosition ppos, Tree_tTree pcode));
extern Tree_tTree Tree_mCdComma ARGS((Positions_tPosition ppos, Tree_tTree pcode));
extern Tree_tTree Tree_mCdLPar ARGS((Positions_tPosition ppos, Tree_tTree pcode));
extern Tree_tTree Tree_mCdRPar ARGS((Positions_tPosition ppos, Tree_tTree pcode));
extern Tree_tTree Tree_mCdLBra ARGS((Positions_tPosition ppos, Tree_tTree pcode));
extern Tree_tTree Tree_mCdRBra ARGS((Positions_tPosition ppos, Tree_tTree pcode));
extern Tree_tTree Tree_mCdSpa ARGS((Positions_tPosition ppos, StringMem_tStringRef pref, Tree_tTree pcode));
extern Tree_tTree Tree_mCdCom ARGS((Positions_tPosition ppos, StringMem_tStringRef pref, Tree_tTree pcode));
extern Tree_tTree Tree_mCdRst ARGS((Positions_tPosition ppos, StringMem_tStringRef pref, Tree_tTree pcode));
extern Tree_tTree Tree_mCdEnd ARGS((Positions_tPosition ppos));
extern void Tree_WriteTree ARGS((IO_tFile f, Tree_tTree Tree));
extern Tree_tTree Tree_ReverseTree ARGS((Tree_tTree Tree));
extern void Tree_BeginTree ARGS(());
extern void Tree_CloseTree ARGS(());
extern void Tree__init();
