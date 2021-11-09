#define DEFINITION_Tree

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

extern CARDINAL Tree_ErrorCount;
#define Tree_Virtual   0
#define Tree_Computed   1
#define Tree_Reverse   2
#define Tree_Write   3
#define Tree_Read   4
#define Tree_Inherited   5
#define Tree_Synthesized   6
#define Tree_Input   7
#define Tree_Output   8
#define Tree_Tree   9
#define Tree_Parameter   10
#define Tree_Stack   11
#define Tree_Variable   12
#define Tree_Demand   13
#define Tree_Funct   14
#define Tree_Ignore   15
#define Tree_Link   16
#define Tree_Thread   17
#define Tree_Test   18
#define Tree_Left   19
#define Tree_Right   20
#define Tree_CopyDef   21
#define Tree_CopyUse   22
#define Tree_NonBaseComp   23
#define Tree_MultInhComp   24
#define Tree_First   25
#define Tree_Dummy   26
#define Tree_Def   27
#define Tree_Use   28
#define Tree_ChildUse   29
#define Tree_ParentUse   30
#define Tree_Generated   31
#define Tree_Top   0
#define Tree_Intermediate   1
#define Tree_Low   2
#define Tree_Referenced   3
#define Tree_Reachable   4
#define Tree_Nonterminal   5
#define Tree_Terminal   6
#define Tree_Explicit   7
#define Tree_Implicit   8
#define Tree_Trace   9
#define Tree_String   10
#define Tree_HasSelector   11
#define Tree_HasChildren   12
#define Tree_HasAttributes   13
#define Tree_HasActions   14
#define Tree_Abstract   16
#define Tree_Mark   17
#define Tree_HasOutput   18
#define Tree_NoTree   NIL
#define Tree_Classes   1
#define Tree_NoClass   2
#define Tree_Class   3
#define Tree_Attributes   4
#define Tree_NoAttribute   5
#define Tree_AttrOrAction   6
#define Tree_Child   7
#define Tree_Attribute   8
#define Tree_ActionPart   9
#define Tree_Codes   10
#define Tree_Designators   11
#define Tree_NoDesignator   12
#define Tree_Designator   13
#define Tree_Ident   14
#define Tree_Remote   15
#define Tree_Any   16
#define Tree_Anys   17
#define Tree_Layouts   18
#define Tree_NoLayout   19
#define Tree_LayoutAny   20
#define Tree_Names   21
#define Tree_NoName   22
#define Tree_Name   23
#define Tree_Spec   49
#define Tree_TreeNames   50
#define Tree_NoTreeName   51
#define Tree_TreeName   52
#define Tree_Routines   53
#define Tree_NoRoutine   54
#define Tree_Routine   55
#define Tree_Procedure   56
#define Tree_Function   57
#define Tree_Predicate   58
#define Tree_Parameters   59
#define Tree_NoParameter   60
#define Tree_Param   61
#define Tree_Type   62
#define Tree_Rules   63
#define Tree_NoRule   64
#define Tree_Rule   65
#define Tree_Patterns   66
#define Tree_NoPattern   67
#define Tree_OnePattern   68
#define Tree_OnePatternAlts   69
#define Tree_PatternsList   70
#define Tree_NoPatternsList   71
#define Tree_OnePatternsList   72
#define Tree_Pattern   73
#define Tree_Decompose   74
#define Tree_VarDef   75
#define Tree_NilTest   76
#define Tree_DontCare1   77
#define Tree_DontCare1Explicit   78
#define Tree_DontCare1Internal   79
#define Tree_DontCare   80
#define Tree_DontCareExplicit   81
#define Tree_DontCareInternal   82
#define Tree_Value   83
#define Tree_Exprs   84
#define Tree_NoExpr   85
#define Tree_OneExpr   86
#define Tree_NamedExpr   87
#define Tree_Expr   88
#define Tree_Compose   89
#define Tree_VarUse   90
#define Tree_AttrDesc   91
#define Tree_Nil   92
#define Tree_Call   93
#define Tree_Binary   94
#define Tree_yy1   95
#define Tree_BinaryCompound   96
#define Tree_PreOperator   97
#define Tree_PostOperator   98
#define Tree_Index   99
#define Tree_Parents   100
#define Tree_TargetExpr   101
#define Tree_StringExpr   102
#define Tree_Statements   103
#define Tree_NoStatement   104
#define Tree_Statement   105
#define Tree_ProcCall   106
#define Tree_Condition   107
#define Tree_Assignment   108
#define Tree_Reject   109
#define Tree_Fail   110
#define Tree_TargetStmt   111
#define Tree_Nl   112
#define Tree_WriteStr   113
#define Tree_Formals   114
#define Tree_NoFormal   115
#define Tree_Formal   116
#define Tree_PlainFormal   117
#define Tree_RoutineFormal   118
#define Tree_DummyFormal   119
#define Tree_TypeDesc   120
#define Tree_NodeTypes   121
#define Tree_UserType   122
#define Tree_Path   123
#define Tree_Var   124
#define Tree_ConsType   125
#define Tree_Field   126
#define Tree_Tests   127
#define Tree_NoTest   128
#define Tree_OneTest   129
#define Tree_TestKind   130
#define Tree_TestIsType   131
#define Tree_TestNil   132
#define Tree_TestNonlin   133
#define Tree_TestValue   134
#define Tree_Decisions   135
#define Tree_NoDecision   136
#define Tree_Decision   137
#define Tree_Decided   138
typedef struct Tree_116 *Tree_tTree;
typedef void (*Tree_tProcTree) ARGS((Tree_tTree));
typedef SHORTCARD Tree_INTEGER0;
typedef BITSET Tree_tAttrProperties;
typedef BITSET Tree_tClassProperties;
typedef Tree_tTree Tree_tClass;
typedef void (*Tree_ProcOfT) ARGS((Tree_tTree));
extern Sets_tSet Tree_Options;
extern IO_tFile Tree_f;
extern struct Tree_1 {
    CHAR A[255 + 1];
} Tree_SourceFile;
extern BITSET Tree_NoCodeAttr, Tree_NoCodeClass;
extern void Tree_InitIdentifyClass ARGS((Tree_tTree t));
extern void Tree_InitIdentifyClass2 ARGS((Tree_tTree t));
extern Tree_tTree Tree_IdentifyClass ARGS((Tree_tTree t, Idents_tIdent Ident));
extern Tree_tTree Tree_IdentifyAttribute ARGS((Tree_tTree t, Idents_tIdent Ident));
extern void Tree_ForallClasses ARGS((Tree_tTree t, Tree_ProcOfT Proc));
extern void Tree_ForallClassesExtensionsFirst ARGS((Tree_tTree t, Tree_ProcOfT Proc));
extern void Tree_ForallClassesPreAndPost ARGS((Tree_tTree t, Tree_ProcOfT PreProc, Tree_ProcOfT PostProc));
extern void Tree_ForallAttributes ARGS((Tree_tTree t, Tree_ProcOfT Proc));
extern void Tree_Error ARGS((INTEGER ErrorCode, Positions_tPosition Pos));
extern void Tree_Warning ARGS((INTEGER ErrorCode, Positions_tPosition Pos));
extern void Tree_Information ARGS((INTEGER ErrorCode, Positions_tPosition Pos));
extern void Tree_ErrorI ARGS((INTEGER ErrorCode, Positions_tPosition Pos, INTEGER iClass, ADDRESS iPtr));
extern void Tree_WarningI ARGS((INTEGER ErrorCode, Positions_tPosition Pos, INTEGER iClass, ADDRESS iPtr));
extern void Tree_InformationI ARGS((INTEGER ErrorCode, Positions_tPosition Pos, INTEGER iClass, ADDRESS iPtr));
extern void Tree_WI ARGS((Idents_tIdent i));
extern void Tree_WE ARGS((Idents_tIdent i));
extern void Tree_WN ARGS((INTEGER n));
typedef struct Tree_2 {
    SHORTCARD yyKind, yyMark;
} Tree_yytNodeHead;
typedef struct Tree_3 {
    Tree_yytNodeHead yyHead;
} Tree_yClasses;
typedef struct Tree_4 {
    Tree_yytNodeHead yyHead;
} Tree_yNoClass;
typedef struct Tree_5 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Tree_tClassProperties Properties;
    Tree_tTree Attributes;
    Tree_tTree Extensions;
    Tree_tTree Next;
    Tree_tTree BaseClass;
    Tree_tTree Formals;
    Tree_tTree TypeDesc;
    SHORTCARD Index;
    INTEGER Depth;
} Tree_yClass;
typedef struct Tree_6 {
    Tree_yytNodeHead yyHead;
} Tree_yAttributes;
typedef struct Tree_7 {
    Tree_yytNodeHead yyHead;
} Tree_yNoAttribute;
typedef struct Tree_8 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
} Tree_yAttrOrAction;
typedef struct Tree_9 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
    Idents_tIdent Type;
    Tree_tAttrProperties Properties;
} Tree_yChild;
typedef struct Tree_10 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
    Idents_tIdent Type;
    Tree_tAttrProperties Properties;
} Tree_yAttribute;
typedef struct Tree_11 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
} Tree_yActionPart;
typedef struct Tree_12 {
    Tree_yytNodeHead yyHead;
    Texts_tText Export;
    Texts_tText Import;
    Texts_tText Global;
    Texts_tText SpecWith;
    Texts_tText BodyWith;
    Texts_tText Local;
    Texts_tText Begin;
    Texts_tText Close;
    Positions_tPosition ExportLine;
    Positions_tPosition ImportLine;
    Positions_tPosition GlobalLine;
    Positions_tPosition SpecWithLine;
    Positions_tPosition BodyWithLine;
    Positions_tPosition LocalLine;
    Positions_tPosition BeginLine;
    Positions_tPosition CloseLine;
} Tree_yCodes;
typedef struct Tree_13 {
    Tree_yytNodeHead yyHead;
} Tree_yDesignators;
typedef struct Tree_14 {
    Tree_yytNodeHead yyHead;
} Tree_yNoDesignator;
typedef struct Tree_15 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Selector;
    Idents_tIdent Attribute;
    Positions_tPosition Pos;
    Positions_tPosition AttributePos;
    Tree_tTree Next;
    Tree_tClass Object;
    Idents_tIdent Type;
} Tree_yDesignator;
typedef struct Tree_16 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Attribute;
    Positions_tPosition Pos;
    Tree_tTree Next;
    Tree_tClass Object;
} Tree_yIdent;
typedef struct Tree_17 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Designators;
    Idents_tIdent Type;
    Idents_tIdent Attribute;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yRemote;
typedef struct Tree_18 {
    Tree_yytNodeHead yyHead;
    StringMem_tStringRef Code;
    Tree_tTree Next;
} Tree_yAny;
typedef struct Tree_19 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Layouts;
    Tree_tTree Next;
} Tree_yAnys;
typedef struct Tree_20 {
    Tree_yytNodeHead yyHead;
} Tree_yLayouts;
typedef struct Tree_21 {
    Tree_yytNodeHead yyHead;
} Tree_yNoLayout;
typedef struct Tree_22 {
    Tree_yytNodeHead yyHead;
    StringMem_tStringRef Code;
    Tree_tTree Next;
} Tree_yLayoutAny;
typedef struct Tree_23 {
    Tree_yytNodeHead yyHead;
} Tree_yNames;
typedef struct Tree_24 {
    Tree_yytNodeHead yyHead;
} Tree_yNoName;
typedef struct Tree_25 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree Next;
    Tree_tClass Object;
} Tree_yName;
typedef struct Tree_26 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent TrafoName;
    Tree_tTree TreeNames;
    Tree_tTree Public;
    Tree_tTree Extern;
    Tree_tTree Codes;
    Tree_tTree Routines;
} Tree_ySpec;
typedef struct Tree_27 {
    Tree_yytNodeHead yyHead;
} Tree_yTreeNames;
typedef struct Tree_28 {
    Tree_yytNodeHead yyHead;
} Tree_yNoTreeName;
typedef struct Tree_29 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree Next;
    Tree_tTree Classes;
    SHORTCARD ClassCount;
    Tree_tTree EmptyType;
    Tree_tTree UniversalClass;
} Tree_yTreeName;
typedef struct Tree_30 {
    Tree_yytNodeHead yyHead;
} Tree_yRoutines;
typedef struct Tree_31 {
    Tree_yytNodeHead yyHead;
} Tree_yNoRoutine;
typedef struct Tree_32 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree InParams;
    Tree_tTree OutParams;
    Tree_tTree Extern;
    Texts_tText Local;
    Positions_tPosition LocalLine;
    Tree_tTree Rules;
    Tree_tTree InForm;
    Tree_tTree OutForm;
    Tree_tTree ParamDecls;
    BOOLEAN IsExtern;
    Tree_tTree Decisions;
} Tree_yRoutine;
typedef struct Tree_33 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree InParams;
    Tree_tTree OutParams;
    Tree_tTree Extern;
    Texts_tText Local;
    Positions_tPosition LocalLine;
    Tree_tTree Rules;
    Tree_tTree InForm;
    Tree_tTree OutForm;
    Tree_tTree ParamDecls;
    BOOLEAN IsExtern;
    Tree_tTree Decisions;
} Tree_yProcedure;
typedef struct Tree_34 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree InParams;
    Tree_tTree OutParams;
    Tree_tTree Extern;
    Texts_tText Local;
    Positions_tPosition LocalLine;
    Tree_tTree Rules;
    Tree_tTree InForm;
    Tree_tTree OutForm;
    Tree_tTree ParamDecls;
    BOOLEAN IsExtern;
    Tree_tTree Decisions;
    Tree_tTree ReturnParams;
    Tree_tTree ReturnForm;
} Tree_yFunction;
typedef struct Tree_35 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree InParams;
    Tree_tTree OutParams;
    Tree_tTree Extern;
    Texts_tText Local;
    Positions_tPosition LocalLine;
    Tree_tTree Rules;
    Tree_tTree InForm;
    Tree_tTree OutForm;
    Tree_tTree ParamDecls;
    BOOLEAN IsExtern;
    Tree_tTree Decisions;
} Tree_yPredicate;
typedef struct Tree_36 {
    Tree_yytNodeHead yyHead;
} Tree_yParameters;
typedef struct Tree_37 {
    Tree_yytNodeHead yyHead;
} Tree_yNoParameter;
typedef struct Tree_38 {
    Tree_yytNodeHead yyHead;
    BOOLEAN IsRef;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree Type;
    Tree_tTree Next;
} Tree_yParam;
typedef struct Tree_39 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree Names;
} Tree_yType;
typedef struct Tree_40 {
    Tree_yytNodeHead yyHead;
} Tree_yRules;
typedef struct Tree_41 {
    Tree_yytNodeHead yyHead;
} Tree_yNoRule;
typedef struct Tree_42 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Line;
    Tree_tTree Patterns;
    Tree_tTree Exprs;
    Tree_tTree Expr;
    Tree_tTree Statements;
    Tree_tTree Next;
    Tree_tTree VarDecls;
    BOOLEAN HasTempos;
    BOOLEAN HasPatterns;
    Idents_tIdent Tempo;
    SHORTCARD Index;
    Tree_tTree Tests;
    BOOLEAN HasExit;
    BOOLEAN HasAssign;
    BOOLEAN HasTargetCode;
    BOOLEAN HasRejectOrFail;
} Tree_yRule;
typedef struct Tree_43 {
    Tree_yytNodeHead yyHead;
} Tree_yPatterns;
typedef struct Tree_44 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
} Tree_yNoPattern;
typedef struct Tree_45 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Pattern;
    Tree_tTree Next;
} Tree_yOnePattern;
typedef struct Tree_46 {
    Tree_yytNodeHead yyHead;
    Tree_tTree PatternsList;
    Tree_tTree Next;
    Tree_tTree Current;
} Tree_yOnePatternAlts;
typedef struct Tree_47 {
    Tree_yytNodeHead yyHead;
} Tree_yPatternsList;
typedef struct Tree_48 {
    Tree_yytNodeHead yyHead;
} Tree_yNoPatternsList;
typedef struct Tree_49 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Patterns;
    Tree_tTree Next;
} Tree_yOnePatternsList;
typedef struct Tree_50 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
} Tree_yPattern;
typedef struct Tree_51 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Idents_tIdent Selector;
    Tree_tTree Expr;
    Tree_tTree Patterns;
    BOOLEAN Widen;
    Tree_tClass Object;
    BOOLEAN IsProperlyNarrowed;
} Tree_yDecompose;
typedef struct Tree_52 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Idents_tIdent Selector;
    BOOLEAN HasDelimiter;
    Tree_tClass Object;
} Tree_yVarDef;
typedef struct Tree_53 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Idents_tIdent Selector;
    BOOLEAN Widen;
    BOOLEAN IsProperlyNarrowed;
} Tree_yNilTest;
typedef struct Tree_54 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Idents_tIdent Selector;
} Tree_yDontCare1;
typedef struct Tree_55 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Idents_tIdent Selector;
} Tree_yDontCare1Explicit;
typedef struct Tree_56 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Idents_tIdent Selector;
} Tree_yDontCare1Internal;
typedef struct Tree_57 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Tree_tTree Tempos;
} Tree_yDontCare;
typedef struct Tree_58 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Tree_tTree Tempos;
} Tree_yDontCareExplicit;
typedef struct Tree_59 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Tree_tTree Tempos;
} Tree_yDontCareInternal;
typedef struct Tree_60 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Idents_tIdent Selector;
    Tree_tTree Expr;
} Tree_yValue;
typedef struct Tree_61 {
    Tree_yytNodeHead yyHead;
} Tree_yExprs;
typedef struct Tree_62 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
} Tree_yNoExpr;
typedef struct Tree_63 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Expr;
    Tree_tTree Next;
} Tree_yOneExpr;
typedef struct Tree_64 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Expr;
    Tree_tTree Next;
    Idents_tIdent Name;
    Positions_tPosition NamePos;
} Tree_yNamedExpr;
typedef struct Tree_65 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
} Tree_yExpr;
typedef struct Tree_66 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Expr;
    Tree_tTree Exprs;
    BOOLEAN Widen;
    Tree_tClass Object;
    Idents_tIdent Tempo;
    Tree_tTree TypeDesc;
} Tree_yCompose;
typedef struct Tree_67 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Idents_tIdent Name;
    BOOLEAN Widen;
    Tree_tClass Object;
} Tree_yVarUse;
typedef struct Tree_68 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Idents_tIdent Name;
    BOOLEAN Widen;
    Tree_tClass Object;
    Idents_tIdent Attribute;
    Positions_tPosition AttributePos;
    Idents_tIdent Type;
} Tree_yAttrDesc;
typedef struct Tree_69 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    BOOLEAN Widen;
} Tree_yNil;
typedef struct Tree_70 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Expr;
    Tree_tTree Exprs;
    Tree_tTree Patterns;
    Tree_tClass Object;
} Tree_yCall;
typedef struct Tree_71 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Lop;
    Idents_tIdent Operator;
    Tree_tTree Rop;
    BOOLEAN Widen;
} Tree_yBinary;
typedef struct Tree_72 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Lop;
    Idents_tIdent Operator;
    Tree_tTree Rop;
    BOOLEAN Widen;
} Tree_yyy1;
typedef struct Tree_73 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Lop;
    Idents_tIdent Operator;
    Tree_tTree Rop;
    BOOLEAN Widen;
    Idents_tIdent CompoundOperator;
} Tree_yBinaryCompound;
typedef struct Tree_74 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Idents_tIdent Operator;
    Tree_tTree Expr;
} Tree_yPreOperator;
typedef struct Tree_75 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Idents_tIdent Operator;
    Tree_tTree Expr;
} Tree_yPostOperator;
typedef struct Tree_76 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Expr;
    Tree_tTree Exprs;
    BOOLEAN Widen;
} Tree_yIndex;
typedef struct Tree_77 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Expr;
} Tree_yParents;
typedef struct Tree_78 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    Tree_tTree Expr;
    Sets_tSet UsedNames;
} Tree_yTargetExpr;
typedef struct Tree_79 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Idents_tIdent Selector;
    StringMem_tStringRef String;
} Tree_yStringExpr;
typedef struct Tree_80 {
    Tree_yytNodeHead yyHead;
} Tree_yStatements;
typedef struct Tree_81 {
    Tree_yytNodeHead yyHead;
} Tree_yNoStatement;
typedef struct Tree_82 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yStatement;
typedef struct Tree_83 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
    Tree_tTree Call;
} Tree_yProcCall;
typedef struct Tree_84 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
    Tree_tTree Expr;
} Tree_yCondition;
typedef struct Tree_85 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
    Tree_tTree Adr;
    Tree_tTree Expr;
    Tree_tClass Object;
} Tree_yAssignment;
typedef struct Tree_86 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yReject;
typedef struct Tree_87 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yFail;
typedef struct Tree_88 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
    Tree_tTree Parameters;
    Tree_tTree Stmt;
    Sets_tSet UsedNames;
} Tree_yTargetStmt;
typedef struct Tree_89 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yNl;
typedef struct Tree_90 {
    Tree_yytNodeHead yyHead;
    Positions_tPosition Pos;
    Tree_tTree Next;
    StringMem_tStringRef String;
} Tree_yWriteStr;
typedef struct Tree_91 {
    Tree_yytNodeHead yyHead;
} Tree_yFormals;
typedef struct Tree_92 {
    Tree_yytNodeHead yyHead;
} Tree_yNoFormal;
typedef struct Tree_93 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Hides;
    Idents_tIdent Name;
    Positions_tPosition DeclPos;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
} Tree_yFormal;
typedef struct Tree_94 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Hides;
    Idents_tIdent Name;
    Positions_tPosition DeclPos;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
} Tree_yPlainFormal;
typedef struct Tree_95 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Hides;
    Idents_tIdent Name;
    Positions_tPosition DeclPos;
    Tree_tTree TypeDesc;
    Tree_tTree Path;
    Tree_tTree TargetClass;
    BOOLEAN DeclaredTypeIsGuaranteed;
} Tree_yRoutineFormal;
typedef struct Tree_96 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
} Tree_yDummyFormal;
typedef struct Tree_97 {
    Tree_yytNodeHead yyHead;
} Tree_yTypeDesc;
typedef struct Tree_98 {
    Tree_yytNodeHead yyHead;
    Tree_tTree TreeName;
    Sets_tSet Types;
} Tree_yNodeTypes;
typedef struct Tree_99 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Type;
} Tree_yUserType;
typedef struct Tree_100 {
    Tree_yytNodeHead yyHead;
} Tree_yPath;
typedef struct Tree_101 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    BOOLEAN IsOutput;
    BOOLEAN IsRegister;
} Tree_yVar;
typedef struct Tree_102 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
    BOOLEAN IsProperlyNarrowed;
} Tree_yConsType;
typedef struct Tree_103 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Idents_tIdent Name;
} Tree_yField;
typedef struct Tree_104 {
    Tree_yytNodeHead yyHead;
} Tree_yTests;
typedef struct Tree_105 {
    Tree_yytNodeHead yyHead;
} Tree_yNoTest;
typedef struct Tree_106 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Path;
} Tree_yOneTest;
typedef struct Tree_107 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Path;
    Tree_tTree TypeDesc;
    Idents_tIdent Name;
} Tree_yTestKind;
typedef struct Tree_108 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Path;
    Tree_tTree TypeDesc;
    Idents_tIdent Name;
} Tree_yTestIsType;
typedef struct Tree_109 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Path;
} Tree_yTestNil;
typedef struct Tree_110 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Path;
    Tree_tTree Path2;
    Tree_tTree TypeDesc;
} Tree_yTestNonlin;
typedef struct Tree_111 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Tree_tTree Path;
    Tree_tTree Expr;
    Tree_tTree TypeDesc;
} Tree_yTestValue;
typedef struct Tree_112 {
    Tree_yytNodeHead yyHead;
} Tree_yDecisions;
typedef struct Tree_113 {
    Tree_yytNodeHead yyHead;
} Tree_yNoDecision;
typedef struct Tree_114 {
    Tree_yytNodeHead yyHead;
    Tree_tTree ThenPart;
    Tree_tTree ElsePart;
    Tree_tTree OneTest;
    SHORTCARD Cases;
    BOOLEAN IsUnchanged;
} Tree_yDecision;
typedef struct Tree_115 {
    Tree_yytNodeHead yyHead;
    Tree_tTree ElsePart;
    Tree_tTree Rule;
} Tree_yDecided;
typedef struct Tree_116 {
    union {
        struct {
            SHORTCARD Kind;
        } V_1;
        struct {
            Tree_yytNodeHead yyHead;
        } V_2;
        struct {
            Tree_yClasses Classes;
        } V_3;
        struct {
            Tree_yNoClass NoClass;
        } V_4;
        struct {
            Tree_yClass Class;
        } V_5;
        struct {
            Tree_yAttributes Attributes;
        } V_6;
        struct {
            Tree_yNoAttribute NoAttribute;
        } V_7;
        struct {
            Tree_yAttrOrAction AttrOrAction;
        } V_8;
        struct {
            Tree_yChild Child;
        } V_9;
        struct {
            Tree_yAttribute Attribute;
        } V_10;
        struct {
            Tree_yActionPart ActionPart;
        } V_11;
        struct {
            Tree_yCodes Codes;
        } V_12;
        struct {
            Tree_yDesignators Designators;
        } V_13;
        struct {
            Tree_yNoDesignator NoDesignator;
        } V_14;
        struct {
            Tree_yDesignator Designator;
        } V_15;
        struct {
            Tree_yIdent Ident;
        } V_16;
        struct {
            Tree_yRemote Remote;
        } V_17;
        struct {
            Tree_yAny Any;
        } V_18;
        struct {
            Tree_yAnys Anys;
        } V_19;
        struct {
            Tree_yLayouts Layouts;
        } V_20;
        struct {
            Tree_yNoLayout NoLayout;
        } V_21;
        struct {
            Tree_yLayoutAny LayoutAny;
        } V_22;
        struct {
            Tree_yNames Names;
        } V_23;
        struct {
            Tree_yNoName NoName;
        } V_24;
        struct {
            Tree_yName Name;
        } V_25;
        struct {
            Tree_ySpec Spec;
        } V_26;
        struct {
            Tree_yTreeNames TreeNames;
        } V_27;
        struct {
            Tree_yNoTreeName NoTreeName;
        } V_28;
        struct {
            Tree_yTreeName TreeName;
        } V_29;
        struct {
            Tree_yRoutines Routines;
        } V_30;
        struct {
            Tree_yNoRoutine NoRoutine;
        } V_31;
        struct {
            Tree_yRoutine Routine;
        } V_32;
        struct {
            Tree_yProcedure Procedure;
        } V_33;
        struct {
            Tree_yFunction Function;
        } V_34;
        struct {
            Tree_yPredicate Predicate;
        } V_35;
        struct {
            Tree_yParameters Parameters;
        } V_36;
        struct {
            Tree_yNoParameter NoParameter;
        } V_37;
        struct {
            Tree_yParam Param;
        } V_38;
        struct {
            Tree_yType Type;
        } V_39;
        struct {
            Tree_yRules Rules;
        } V_40;
        struct {
            Tree_yNoRule NoRule;
        } V_41;
        struct {
            Tree_yRule Rule;
        } V_42;
        struct {
            Tree_yPatterns Patterns;
        } V_43;
        struct {
            Tree_yNoPattern NoPattern;
        } V_44;
        struct {
            Tree_yOnePattern OnePattern;
        } V_45;
        struct {
            Tree_yOnePatternAlts OnePatternAlts;
        } V_46;
        struct {
            Tree_yPatternsList PatternsList;
        } V_47;
        struct {
            Tree_yNoPatternsList NoPatternsList;
        } V_48;
        struct {
            Tree_yOnePatternsList OnePatternsList;
        } V_49;
        struct {
            Tree_yPattern Pattern;
        } V_50;
        struct {
            Tree_yDecompose Decompose;
        } V_51;
        struct {
            Tree_yVarDef VarDef;
        } V_52;
        struct {
            Tree_yNilTest NilTest;
        } V_53;
        struct {
            Tree_yDontCare1 DontCare1;
        } V_54;
        struct {
            Tree_yDontCare1Explicit DontCare1Explicit;
        } V_55;
        struct {
            Tree_yDontCare1Internal DontCare1Internal;
        } V_56;
        struct {
            Tree_yDontCare DontCare;
        } V_57;
        struct {
            Tree_yDontCareExplicit DontCareExplicit;
        } V_58;
        struct {
            Tree_yDontCareInternal DontCareInternal;
        } V_59;
        struct {
            Tree_yValue Value;
        } V_60;
        struct {
            Tree_yExprs Exprs;
        } V_61;
        struct {
            Tree_yNoExpr NoExpr;
        } V_62;
        struct {
            Tree_yOneExpr OneExpr;
        } V_63;
        struct {
            Tree_yNamedExpr NamedExpr;
        } V_64;
        struct {
            Tree_yExpr Expr;
        } V_65;
        struct {
            Tree_yCompose Compose;
        } V_66;
        struct {
            Tree_yVarUse VarUse;
        } V_67;
        struct {
            Tree_yAttrDesc AttrDesc;
        } V_68;
        struct {
            Tree_yNil Nil;
        } V_69;
        struct {
            Tree_yCall Call;
        } V_70;
        struct {
            Tree_yBinary Binary;
        } V_71;
        struct {
            Tree_yyy1 yy1;
        } V_72;
        struct {
            Tree_yBinaryCompound BinaryCompound;
        } V_73;
        struct {
            Tree_yPreOperator PreOperator;
        } V_74;
        struct {
            Tree_yPostOperator PostOperator;
        } V_75;
        struct {
            Tree_yIndex Index;
        } V_76;
        struct {
            Tree_yParents Parents;
        } V_77;
        struct {
            Tree_yTargetExpr TargetExpr;
        } V_78;
        struct {
            Tree_yStringExpr StringExpr;
        } V_79;
        struct {
            Tree_yStatements Statements;
        } V_80;
        struct {
            Tree_yNoStatement NoStatement;
        } V_81;
        struct {
            Tree_yStatement Statement;
        } V_82;
        struct {
            Tree_yProcCall ProcCall;
        } V_83;
        struct {
            Tree_yCondition Condition;
        } V_84;
        struct {
            Tree_yAssignment Assignment;
        } V_85;
        struct {
            Tree_yReject Reject;
        } V_86;
        struct {
            Tree_yFail Fail;
        } V_87;
        struct {
            Tree_yTargetStmt TargetStmt;
        } V_88;
        struct {
            Tree_yNl Nl;
        } V_89;
        struct {
            Tree_yWriteStr WriteStr;
        } V_90;
        struct {
            Tree_yFormals Formals;
        } V_91;
        struct {
            Tree_yNoFormal NoFormal;
        } V_92;
        struct {
            Tree_yFormal Formal;
        } V_93;
        struct {
            Tree_yPlainFormal PlainFormal;
        } V_94;
        struct {
            Tree_yRoutineFormal RoutineFormal;
        } V_95;
        struct {
            Tree_yDummyFormal DummyFormal;
        } V_96;
        struct {
            Tree_yTypeDesc TypeDesc;
        } V_97;
        struct {
            Tree_yNodeTypes NodeTypes;
        } V_98;
        struct {
            Tree_yUserType UserType;
        } V_99;
        struct {
            Tree_yPath Path;
        } V_100;
        struct {
            Tree_yVar Var;
        } V_101;
        struct {
            Tree_yConsType ConsType;
        } V_102;
        struct {
            Tree_yField Field;
        } V_103;
        struct {
            Tree_yTests Tests;
        } V_104;
        struct {
            Tree_yNoTest NoTest;
        } V_105;
        struct {
            Tree_yOneTest OneTest;
        } V_106;
        struct {
            Tree_yTestKind TestKind;
        } V_107;
        struct {
            Tree_yTestIsType TestIsType;
        } V_108;
        struct {
            Tree_yTestNil TestNil;
        } V_109;
        struct {
            Tree_yTestNonlin TestNonlin;
        } V_110;
        struct {
            Tree_yTestValue TestValue;
        } V_111;
        struct {
            Tree_yDecisions Decisions;
        } V_112;
        struct {
            Tree_yNoDecision NoDecision;
        } V_113;
        struct {
            Tree_yDecision Decision;
        } V_114;
        struct {
            Tree_yDecided Decided;
        } V_115;
    } U_1;
} Tree_yyNode;
extern Tree_tTree Tree_TreeRoot;
extern LONGCARD Tree_HeapUsed;
extern ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
extern struct Tree_117 {
    SHORTCARD A[138 + 1];
} Tree_yyNodeSize;
extern PROC Tree_yyExit;
extern Tree_tTree Tree_yyAlloc ARGS(());
extern Tree_tTree Tree_MakeTree ARGS((SHORTCARD Kind));
extern BOOLEAN Tree_IsType ARGS((Tree_tTree Tree, SHORTCARD Kind));
extern Tree_tTree Tree_mClasses ARGS(());
extern Tree_tTree Tree_mNoClass ARGS(());
extern Tree_tTree Tree_mClass ARGS((Idents_tIdent pName, Tree_tClassProperties pProperties, Tree_tTree pAttributes, Tree_tTree pExtensions, Tree_tTree pNext));
extern Tree_tTree Tree_mAttributes ARGS(());
extern Tree_tTree Tree_mNoAttribute ARGS(());
extern Tree_tTree Tree_mAttrOrAction ARGS((Tree_tTree pNext));
extern Tree_tTree Tree_mChild ARGS((Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties));
extern Tree_tTree Tree_mAttribute ARGS((Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties));
extern Tree_tTree Tree_mActionPart ARGS((Tree_tTree pNext));
extern Tree_tTree Tree_mCodes ARGS((Texts_tText pExport, Texts_tText pImport, Texts_tText pGlobal, Texts_tText pSpecWith, Texts_tText pBodyWith, Texts_tText pLocal, Texts_tText pBegin, Texts_tText pClose, Positions_tPosition pExportLine, Positions_tPosition pImportLine, Positions_tPosition pGlobalLine, Positions_tPosition pSpecWithLine, Positions_tPosition pBodyWithLine, Positions_tPosition pLocalLine, Positions_tPosition pBeginLine, Positions_tPosition pCloseLine));
extern Tree_tTree Tree_mDesignators ARGS(());
extern Tree_tTree Tree_mNoDesignator ARGS(());
extern Tree_tTree Tree_mDesignator ARGS((Idents_tIdent pSelector, Idents_tIdent pAttribute, Positions_tPosition pPos, Positions_tPosition pAttributePos, Tree_tTree pNext));
extern Tree_tTree Tree_mIdent ARGS((Idents_tIdent pAttribute, Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mRemote ARGS((Tree_tTree pDesignators, Idents_tIdent pType, Idents_tIdent pAttribute, Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mAny ARGS((StringMem_tStringRef pCode, Tree_tTree pNext));
extern Tree_tTree Tree_mAnys ARGS((Tree_tTree pLayouts, Tree_tTree pNext));
extern Tree_tTree Tree_mLayouts ARGS(());
extern Tree_tTree Tree_mNoLayout ARGS(());
extern Tree_tTree Tree_mLayoutAny ARGS((StringMem_tStringRef pCode, Tree_tTree pNext));
extern Tree_tTree Tree_mNames ARGS(());
extern Tree_tTree Tree_mNoName ARGS(());
extern Tree_tTree Tree_mName ARGS((Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mSpec ARGS((Idents_tIdent pTrafoName, Tree_tTree pTreeNames, Tree_tTree pPublic, Tree_tTree pExtern, Tree_tTree pCodes, Tree_tTree pRoutines));
extern Tree_tTree Tree_mTreeNames ARGS(());
extern Tree_tTree Tree_mNoTreeName ARGS(());
extern Tree_tTree Tree_mTreeName ARGS((Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mRoutines ARGS(());
extern Tree_tTree Tree_mNoRoutine ARGS(());
extern Tree_tTree Tree_mRoutine ARGS((Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules));
extern Tree_tTree Tree_mProcedure ARGS((Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules));
extern Tree_tTree Tree_mFunction ARGS((Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules, Tree_tTree pReturnParams));
extern Tree_tTree Tree_mPredicate ARGS((Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pInParams, Tree_tTree pOutParams, Tree_tTree pExtern, Texts_tText pLocal, Positions_tPosition pLocalLine, Tree_tTree pRules));
extern Tree_tTree Tree_mParameters ARGS(());
extern Tree_tTree Tree_mNoParameter ARGS(());
extern Tree_tTree Tree_mParam ARGS((BOOLEAN pIsRef, Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pType, Tree_tTree pNext));
extern Tree_tTree Tree_mType ARGS((Idents_tIdent pName, Positions_tPosition pPos, Tree_tTree pNames));
extern Tree_tTree Tree_mRules ARGS(());
extern Tree_tTree Tree_mNoRule ARGS(());
extern Tree_tTree Tree_mRule ARGS((Positions_tPosition pLine, Tree_tTree pPatterns, Tree_tTree pExprs, Tree_tTree pExpr, Tree_tTree pStatements, Tree_tTree pNext));
extern Tree_tTree Tree_mPatterns ARGS(());
extern Tree_tTree Tree_mNoPattern ARGS((Positions_tPosition pPos));
extern Tree_tTree Tree_mOnePattern ARGS((Tree_tTree pPattern, Tree_tTree pNext));
extern Tree_tTree Tree_mOnePatternAlts ARGS((Tree_tTree pPatternsList, Tree_tTree pNext, Tree_tTree pCurrent));
extern Tree_tTree Tree_mPatternsList ARGS(());
extern Tree_tTree Tree_mNoPatternsList ARGS(());
extern Tree_tTree Tree_mOnePatternsList ARGS((Tree_tTree pPatterns, Tree_tTree pNext));
extern Tree_tTree Tree_mPattern ARGS((Positions_tPosition pPos));
extern Tree_tTree Tree_mDecompose ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pPatterns, BOOLEAN pWiden));
extern Tree_tTree Tree_mVarDef ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, BOOLEAN pHasDelimiter));
extern Tree_tTree Tree_mNilTest ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, BOOLEAN pWiden));
extern Tree_tTree Tree_mDontCare1 ARGS((Positions_tPosition pPos, Idents_tIdent pSelector));
extern Tree_tTree Tree_mDontCare1Explicit ARGS((Positions_tPosition pPos, Idents_tIdent pSelector));
extern Tree_tTree Tree_mDontCare1Internal ARGS((Positions_tPosition pPos, Idents_tIdent pSelector));
extern Tree_tTree Tree_mDontCare ARGS((Positions_tPosition pPos));
extern Tree_tTree Tree_mDontCareExplicit ARGS((Positions_tPosition pPos));
extern Tree_tTree Tree_mDontCareInternal ARGS((Positions_tPosition pPos));
extern Tree_tTree Tree_mValue ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr));
extern Tree_tTree Tree_mExprs ARGS(());
extern Tree_tTree Tree_mNoExpr ARGS((Positions_tPosition pPos));
extern Tree_tTree Tree_mOneExpr ARGS((Tree_tTree pExpr, Tree_tTree pNext));
extern Tree_tTree Tree_mNamedExpr ARGS((Tree_tTree pExpr, Tree_tTree pNext, Idents_tIdent pName, Positions_tPosition pNamePos));
extern Tree_tTree Tree_mExpr ARGS((Positions_tPosition pPos, Idents_tIdent pSelector));
extern Tree_tTree Tree_mCompose ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pExprs, BOOLEAN pWiden));
extern Tree_tTree Tree_mVarUse ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pName, BOOLEAN pWiden));
extern Tree_tTree Tree_mAttrDesc ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pName, BOOLEAN pWiden, Idents_tIdent pAttribute, Positions_tPosition pAttributePos));
extern Tree_tTree Tree_mNil ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, BOOLEAN pWiden));
extern Tree_tTree Tree_mCall ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pExprs, Tree_tTree pPatterns));
extern Tree_tTree Tree_mBinary ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pLop, Idents_tIdent pOperator, Tree_tTree pRop, BOOLEAN pWiden));
extern Tree_tTree Tree_myy1 ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pLop, Idents_tIdent pOperator, Tree_tTree pRop, BOOLEAN pWiden));
extern Tree_tTree Tree_mBinaryCompound ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pLop, Idents_tIdent pOperator, Tree_tTree pRop, BOOLEAN pWiden, Idents_tIdent pCompoundOperator));
extern Tree_tTree Tree_mPreOperator ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pOperator, Tree_tTree pExpr));
extern Tree_tTree Tree_mPostOperator ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Idents_tIdent pOperator, Tree_tTree pExpr));
extern Tree_tTree Tree_mIndex ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr, Tree_tTree pExprs, BOOLEAN pWiden));
extern Tree_tTree Tree_mParents ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr));
extern Tree_tTree Tree_mTargetExpr ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, Tree_tTree pExpr));
extern Tree_tTree Tree_mStringExpr ARGS((Positions_tPosition pPos, Idents_tIdent pSelector, StringMem_tStringRef pString));
extern Tree_tTree Tree_mStatements ARGS(());
extern Tree_tTree Tree_mNoStatement ARGS(());
extern Tree_tTree Tree_mStatement ARGS((Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mProcCall ARGS((Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pCall));
extern Tree_tTree Tree_mCondition ARGS((Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pExpr));
extern Tree_tTree Tree_mAssignment ARGS((Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pAdr, Tree_tTree pExpr));
extern Tree_tTree Tree_mReject ARGS((Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mFail ARGS((Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mTargetStmt ARGS((Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pParameters, Tree_tTree pStmt));
extern Tree_tTree Tree_mNl ARGS((Positions_tPosition pPos, Tree_tTree pNext));
extern Tree_tTree Tree_mWriteStr ARGS((Positions_tPosition pPos, Tree_tTree pNext, StringMem_tStringRef pString));
extern Tree_tTree Tree_mFormals ARGS(());
extern Tree_tTree Tree_mNoFormal ARGS(());
extern Tree_tTree Tree_mFormal ARGS((Tree_tTree pNext, Tree_tTree pHides, Idents_tIdent pName, Positions_tPosition pDeclPos, Tree_tTree pTypeDesc, Tree_tTree pPath));
extern Tree_tTree Tree_mPlainFormal ARGS((Tree_tTree pNext, Tree_tTree pHides, Idents_tIdent pName, Positions_tPosition pDeclPos, Tree_tTree pTypeDesc, Tree_tTree pPath));
extern Tree_tTree Tree_mRoutineFormal ARGS((Tree_tTree pNext, Tree_tTree pHides, Idents_tIdent pName, Positions_tPosition pDeclPos, Tree_tTree pTypeDesc, Tree_tTree pPath, Tree_tTree pTargetClass, BOOLEAN pDeclaredTypeIsGuaranteed));
extern Tree_tTree Tree_mDummyFormal ARGS((Tree_tTree pNext));
extern Tree_tTree Tree_mTypeDesc ARGS(());
extern Tree_tTree Tree_mNodeTypes ARGS((Tree_tTree pTreeName, Sets_tSet pTypes));
extern Tree_tTree Tree_mUserType ARGS((Idents_tIdent pType));
extern Tree_tTree Tree_mPath ARGS(());
extern Tree_tTree Tree_mVar ARGS((Idents_tIdent pName, BOOLEAN pIsOutput, BOOLEAN pIsRegister));
extern Tree_tTree Tree_mConsType ARGS((Tree_tTree pNext, Idents_tIdent pName, BOOLEAN pIsProperlyNarrowed));
extern Tree_tTree Tree_mField ARGS((Tree_tTree pNext, Idents_tIdent pName));
extern Tree_tTree Tree_mTests ARGS(());
extern Tree_tTree Tree_mNoTest ARGS(());
extern Tree_tTree Tree_mOneTest ARGS((Tree_tTree pNext, Tree_tTree pPath));
extern Tree_tTree Tree_mTestKind ARGS((Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pTypeDesc, Idents_tIdent pName));
extern Tree_tTree Tree_mTestIsType ARGS((Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pTypeDesc, Idents_tIdent pName));
extern Tree_tTree Tree_mTestNil ARGS((Tree_tTree pNext, Tree_tTree pPath));
extern Tree_tTree Tree_mTestNonlin ARGS((Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pPath2, Tree_tTree pTypeDesc));
extern Tree_tTree Tree_mTestValue ARGS((Tree_tTree pNext, Tree_tTree pPath, Tree_tTree pExpr, Tree_tTree pTypeDesc));
extern Tree_tTree Tree_mDecisions ARGS(());
extern Tree_tTree Tree_mNoDecision ARGS(());
extern Tree_tTree Tree_mDecision ARGS((Tree_tTree pThenPart, Tree_tTree pElsePart, Tree_tTree pOneTest, SHORTCARD pCases, BOOLEAN pIsUnchanged));
extern Tree_tTree Tree_mDecided ARGS((Tree_tTree pElsePart, Tree_tTree pRule));
extern void Tree_WriteTreeNode ARGS((IO_tFile f, Tree_tTree Tree));
extern void Tree_WriteTree ARGS((IO_tFile f, Tree_tTree Tree));
extern Tree_tTree Tree_ReverseTree ARGS((Tree_tTree Tree));
extern Tree_tTree Tree_CopyTree ARGS((Tree_tTree Tree));
extern void Tree_QueryTree ARGS((Tree_tTree Tree));
extern void Tree_BeginTree ARGS(());
extern void Tree_CloseTree ARGS(());
extern void Tree__init();
