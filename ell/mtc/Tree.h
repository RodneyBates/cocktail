#define DEFINITION_Tree

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

typedef ADDRESS Tree_yyEstra;
extern Idents_tIdent Tree_ScannerName, Tree_ParserName;
#define Tree_NoTree   NIL
#define Tree_Grammar   1
#define Tree_sections   2
#define Tree_Sections0   3
#define Tree_Sections   4
#define Tree_section   5
#define Tree_Export   6
#define Tree_Global   7
#define Tree_Local   8
#define Tree_Begin   9
#define Tree_Close   10
#define Tree_codes   11
#define Tree_Codes0   12
#define Tree_Codes   13
#define Tree_Code   14
#define Tree_code   15
#define Tree_tokens   16
#define Tree_Tokens0   17
#define Tree_Tokens   18
#define Tree_Token   19
#define Tree_token   20
#define Tree_Id   21
#define Tree_id   22
#define Tree_Number   23
#define Tree_number   24
#define Tree_rules   25
#define Tree_Rules0   26
#define Tree_Rules   27
#define Tree_Rule   28
#define Tree_rule   29
#define Tree_expr   30
#define Tree_Option   31
#define Tree_Times   32
#define Tree_Plus   33
#define Tree_List   34
#define Tree_Action   35
#define Tree_Leaf   36
#define Tree_alternative   37
#define Tree_Alternative0   38
#define Tree_Alternative   39
#define Tree_sequence   40
#define Tree_Sequence0   41
#define Tree_Sequence   42
typedef struct Tree_44 *Tree_tTree;
typedef void (*Tree_tProcTree) ARGS((Tree_tTree));
typedef struct Tree_1 {
    SHORTCARD yyKind, yyMark;
    Tree_yyEstra yyEstraInfo;
} Tree_yytNodeHead;
typedef struct Tree_2 {
    Tree_yytNodeHead yyHead;
    Tree_tTree sections;
    Tree_tTree tokens;
    Tree_tTree rules;
} Tree_yGrammar;
typedef struct Tree_3 {
    Tree_yytNodeHead yyHead;
} Tree_ysections;
typedef struct Tree_4 {
    Tree_yytNodeHead yyHead;
} Tree_ySections0;
typedef struct Tree_5 {
    Tree_yytNodeHead yyHead;
    Tree_tTree sections;
    Tree_tTree section;
} Tree_ySections;
typedef struct Tree_6 {
    Tree_yytNodeHead yyHead;
} Tree_ysection;
typedef struct Tree_7 {
    Tree_yytNodeHead yyHead;
    Tree_tTree codes;
} Tree_yExport;
typedef struct Tree_8 {
    Tree_yytNodeHead yyHead;
    Tree_tTree codes;
} Tree_yGlobal;
typedef struct Tree_9 {
    Tree_yytNodeHead yyHead;
    Tree_tTree codes;
} Tree_yLocal;
typedef struct Tree_10 {
    Tree_yytNodeHead yyHead;
    Tree_tTree codes;
} Tree_yBegin;
typedef struct Tree_11 {
    Tree_yytNodeHead yyHead;
    Tree_tTree codes;
} Tree_yClose;
typedef struct Tree_12 {
    Tree_yytNodeHead yyHead;
} Tree_ycodes;
typedef struct Tree_13 {
    Tree_yytNodeHead yyHead;
} Tree_yCodes0;
typedef struct Tree_14 {
    Tree_yytNodeHead yyHead;
    Tree_tTree codes;
    Tree_tTree code;
} Tree_yCodes;
typedef struct Tree_15 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    StringMem_tStringRef ref;
} Tree_yCode;
typedef struct Tree_16 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    StringMem_tStringRef ref;
} Tree_ycode;
typedef struct Tree_17 {
    Tree_yytNodeHead yyHead;
} Tree_ytokens;
typedef struct Tree_18 {
    Tree_yytNodeHead yyHead;
} Tree_yTokens0;
typedef struct Tree_19 {
    Tree_yytNodeHead yyHead;
    Tree_tTree tokens;
    Tree_tTree token;
} Tree_yTokens;
typedef struct Tree_20 {
    Tree_yytNodeHead yyHead;
    Tree_tTree id;
    Tree_tTree number;
} Tree_yToken;
typedef struct Tree_21 {
    Tree_yytNodeHead yyHead;
    Tree_tTree id;
    Tree_tTree number;
} Tree_ytoken;
typedef struct Tree_22 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Idents_tIdent ident;
    BOOLEAN isstring;
} Tree_yId;
typedef struct Tree_23 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Idents_tIdent ident;
    BOOLEAN isstring;
} Tree_yid;
typedef struct Tree_24 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    INTEGER value;
} Tree_yNumber;
typedef struct Tree_25 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    INTEGER value;
} Tree_ynumber;
typedef struct Tree_26 {
    Tree_yytNodeHead yyHead;
} Tree_yrules;
typedef struct Tree_27 {
    Tree_yytNodeHead yyHead;
} Tree_yRules0;
typedef struct Tree_28 {
    Tree_yytNodeHead yyHead;
    Tree_tTree rules;
    Tree_tTree rule;
} Tree_yRules;
typedef struct Tree_29 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree id;
    Tree_tTree codes;
    Tree_tTree expr;
    BOOLEAN iscalling;
} Tree_yRule;
typedef struct Tree_30 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Tree_tTree id;
    Tree_tTree codes;
    Tree_tTree expr;
    BOOLEAN iscalling;
} Tree_yrule;
typedef struct Tree_31 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
} Tree_yexpr;
typedef struct Tree_32 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    Tree_tTree expr;
} Tree_yOption;
typedef struct Tree_33 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    Tree_tTree expr;
} Tree_yTimes;
typedef struct Tree_34 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    Tree_tTree expr;
} Tree_yPlus;
typedef struct Tree_35 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    Tree_tTree body;
    Tree_tTree sep;
} Tree_yList;
typedef struct Tree_36 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    Tree_tTree codes;
} Tree_yAction;
typedef struct Tree_37 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    Tree_tTree id;
    BOOLEAN sure;
    INTEGER number;
} Tree_yLeaf;
typedef struct Tree_38 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    INTEGER depth;
    BOOLEAN C_0_case;
} Tree_yalternative;
typedef struct Tree_39 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    INTEGER depth;
    BOOLEAN C_0_case;
    BOOLEAN recover;
    Tree_tTree C_0_default;
} Tree_yAlternative0;
typedef struct Tree_40 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    INTEGER depth;
    BOOLEAN C_0_case;
    Tree_tTree alternative;
    Tree_tTree expr;
} Tree_yAlternative;
typedef struct Tree_41 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
} Tree_ysequence;
typedef struct Tree_42 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
} Tree_ySequence0;
typedef struct Tree_43 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition pos;
    Sets_tSet first;
    Sets_tSet follow;
    Sets_tSet fifo;
    Sets_tSet recovery;
    INTEGER length;
    INTEGER index;
    INTEGER followindex;
    INTEGER recindex;
    INTEGER expindex;
    Tree_tTree sequence;
    Tree_tTree expr;
} Tree_ySequence;
typedef struct Tree_44 {
    union {
        struct {
            SHORTCARD Kind;
        } V_1;
        struct {
            Tree_yytNodeHead yyHead;
        } V_2;
        struct {
            Tree_yGrammar Grammar;
        } V_3;
        struct {
            Tree_ysections sections;
        } V_4;
        struct {
            Tree_ySections0 Sections0;
        } V_5;
        struct {
            Tree_ySections Sections;
        } V_6;
        struct {
            Tree_ysection section;
        } V_7;
        struct {
            Tree_yExport Export;
        } V_8;
        struct {
            Tree_yGlobal Global;
        } V_9;
        struct {
            Tree_yLocal Local;
        } V_10;
        struct {
            Tree_yBegin Begin;
        } V_11;
        struct {
            Tree_yClose Close;
        } V_12;
        struct {
            Tree_ycodes codes;
        } V_13;
        struct {
            Tree_yCodes0 Codes0;
        } V_14;
        struct {
            Tree_yCodes Codes;
        } V_15;
        struct {
            Tree_yCode Code;
        } V_16;
        struct {
            Tree_ycode code;
        } V_17;
        struct {
            Tree_ytokens tokens;
        } V_18;
        struct {
            Tree_yTokens0 Tokens0;
        } V_19;
        struct {
            Tree_yTokens Tokens;
        } V_20;
        struct {
            Tree_yToken Token;
        } V_21;
        struct {
            Tree_ytoken token;
        } V_22;
        struct {
            Tree_yId Id;
        } V_23;
        struct {
            Tree_yid id;
        } V_24;
        struct {
            Tree_yNumber Number;
        } V_25;
        struct {
            Tree_ynumber number;
        } V_26;
        struct {
            Tree_yrules rules;
        } V_27;
        struct {
            Tree_yRules0 Rules0;
        } V_28;
        struct {
            Tree_yRules Rules;
        } V_29;
        struct {
            Tree_yRule Rule;
        } V_30;
        struct {
            Tree_yrule rule;
        } V_31;
        struct {
            Tree_yexpr expr;
        } V_32;
        struct {
            Tree_yOption Option;
        } V_33;
        struct {
            Tree_yTimes Times;
        } V_34;
        struct {
            Tree_yPlus Plus;
        } V_35;
        struct {
            Tree_yList List;
        } V_36;
        struct {
            Tree_yAction Action;
        } V_37;
        struct {
            Tree_yLeaf Leaf;
        } V_38;
        struct {
            Tree_yalternative alternative;
        } V_39;
        struct {
            Tree_yAlternative0 Alternative0;
        } V_40;
        struct {
            Tree_yAlternative Alternative;
        } V_41;
        struct {
            Tree_ysequence sequence;
        } V_42;
        struct {
            Tree_ySequence0 Sequence0;
        } V_43;
        struct {
            Tree_ySequence Sequence;
        } V_44;
    } U_1;
} Tree_yyNode;
extern Tree_tTree Tree_TreeRoot;
extern LONGCARD Tree_HeapUsed;
extern ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
extern struct Tree_45 {
    SHORTCARD A[42 + 1];
} Tree_yyNodeSize;
extern PROC Tree_yyExit;
extern Tree_tTree Tree_yyAlloc ARGS(());
extern Tree_tTree Tree_MakeTree ARGS((SHORTCARD Kind));
extern BOOLEAN Tree_IsType ARGS((Tree_tTree Tree, SHORTCARD Kind));
extern Tree_tTree Tree_mGrammar ARGS((Tree_tTree psections, Tree_tTree ptokens, Tree_tTree prules));
extern Tree_tTree Tree_msections ARGS(());
extern Tree_tTree Tree_mSections0 ARGS(());
extern Tree_tTree Tree_mSections ARGS((Tree_tTree psections, Tree_tTree psection));
extern Tree_tTree Tree_msection ARGS(());
extern Tree_tTree Tree_mExport ARGS((Tree_tTree pcodes));
extern Tree_tTree Tree_mGlobal ARGS((Tree_tTree pcodes));
extern Tree_tTree Tree_mLocal ARGS((Tree_tTree pcodes));
extern Tree_tTree Tree_mBegin ARGS((Tree_tTree pcodes));
extern Tree_tTree Tree_mClose ARGS((Tree_tTree pcodes));
extern Tree_tTree Tree_mcodes ARGS(());
extern Tree_tTree Tree_mCodes0 ARGS(());
extern Tree_tTree Tree_mCodes ARGS((Tree_tTree pcodes, Tree_tTree pcode));
extern Tree_tTree Tree_mCode ARGS((Positions_tPosition ppos, StringMem_tStringRef pref));
extern Tree_tTree Tree_mcode ARGS((Positions_tPosition ppos, StringMem_tStringRef pref));
extern Tree_tTree Tree_mtokens ARGS(());
extern Tree_tTree Tree_mTokens0 ARGS(());
extern Tree_tTree Tree_mTokens ARGS((Tree_tTree ptokens, Tree_tTree ptoken));
extern Tree_tTree Tree_mToken ARGS((Tree_tTree pid, Tree_tTree pnumber));
extern Tree_tTree Tree_mtoken ARGS((Tree_tTree pid, Tree_tTree pnumber));
extern Tree_tTree Tree_mId ARGS((Positions_tPosition ppos, Idents_tIdent pident, BOOLEAN pisstring));
extern Tree_tTree Tree_mid ARGS((Positions_tPosition ppos, Idents_tIdent pident, BOOLEAN pisstring));
extern Tree_tTree Tree_mNumber ARGS((Positions_tPosition ppos, INTEGER pvalue));
extern Tree_tTree Tree_mnumber ARGS((Positions_tPosition ppos, INTEGER pvalue));
extern Tree_tTree Tree_mrules ARGS(());
extern Tree_tTree Tree_mRules0 ARGS(());
extern Tree_tTree Tree_mRules ARGS((Tree_tTree prules, Tree_tTree prule));
extern Tree_tTree Tree_mRule ARGS((Positions_tPosition ppos, Tree_tTree pid, Tree_tTree pcodes, Tree_tTree pexpr));
extern Tree_tTree Tree_mrule ARGS((Positions_tPosition ppos, Tree_tTree pid, Tree_tTree pcodes, Tree_tTree pexpr));
extern Tree_tTree Tree_mexpr ARGS((Positions_tPosition ppos));
extern Tree_tTree Tree_mOption ARGS((Positions_tPosition ppos, Tree_tTree pexpr));
extern Tree_tTree Tree_mTimes ARGS((Positions_tPosition ppos, Tree_tTree pexpr));
extern Tree_tTree Tree_mPlus ARGS((Positions_tPosition ppos, Tree_tTree pexpr));
extern Tree_tTree Tree_mList ARGS((Positions_tPosition ppos, Tree_tTree pbody, Tree_tTree psep));
extern Tree_tTree Tree_mAction ARGS((Positions_tPosition ppos, Tree_tTree pcodes));
extern Tree_tTree Tree_mLeaf ARGS((Positions_tPosition ppos, Tree_tTree pid));
extern Tree_tTree Tree_malternative ARGS((Positions_tPosition ppos));
extern Tree_tTree Tree_mAlternative0 ARGS((Positions_tPosition ppos));
extern Tree_tTree Tree_mAlternative ARGS((Positions_tPosition ppos, Tree_tTree palternative, Tree_tTree pexpr));
extern Tree_tTree Tree_msequence ARGS((Positions_tPosition ppos));
extern Tree_tTree Tree_mSequence0 ARGS((Positions_tPosition ppos));
extern Tree_tTree Tree_mSequence ARGS((Positions_tPosition ppos, Tree_tTree psequence, Tree_tTree pexpr));
extern Tree_tTree Tree_ReverseTree ARGS((Tree_tTree Tree));
extern void Tree_BeginTree ARGS(());
extern void Tree_CloseTree ARGS(());
extern void Tree__init();
