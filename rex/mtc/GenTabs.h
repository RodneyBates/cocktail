#define DEFINITION_GenTabs

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#define GenTabs_NoContext   0
#define GenTabs_VariableContext   9999
typedef struct GenTabs_1 {
    Positions_tPosition Position;
    SHORTCARD Rule;
    SHORTINT ContextLng;
    Sets_tSet NContext;
    Sets_tSet DContext;
    Sets_tSet Finals;
} GenTabs_PatternInfo;
typedef struct GenTabs_2 {
    Texts_tText Text;
    SHORTCARD TextLine;
    SHORTCARD CodeMode;
} GenTabs_CodeInfo;
typedef struct GenTabs_3 {
    GenTabs_PatternInfo A[100000 + 1];
} GenTabs_PatternTable;
typedef struct GenTabs_4 {
    GenTabs_CodeInfo A[100000 + 1];
} GenTabs_RuleToCode;
extern Tree_tTree GenTabs_Root;
extern SHORTINT GenTabs_NodeCount, GenTabs_StartStateCount;
extern SHORTCARD GenTabs_RuleCount, GenTabs_PatternCount, GenTabs_LeafCount;
extern BOOLEAN GenTabs_LeftJustUsed;
extern SHORTCARD GenTabs_EobAction, GenTabs_DefaultAction;
extern GenTabs_PatternTable *GenTabs_PatternTablePtr;
extern LONGINT GenTabs_PatternTableSize;
extern GenTabs_RuleToCode *GenTabs_RuleToCodePtr;
extern LONGINT GenTabs_RuleToCodeSize;
extern void GenTabs_GenerateTables ARGS((SHORTCARD DebugLevel, BOOLEAN ReduceCaseSize, BOOLEAN Warnings, SHORTINT Optimize));
extern void GenTabs__init();
