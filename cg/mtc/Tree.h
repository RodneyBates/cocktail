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
#define Tree_cLNC   0
#define Tree_cWAG   1
#define Tree_cSNC   2
#define Tree_cDNC   3
#define Tree_cLordered   4
#define Tree_cOAG   5
#define Tree_cSweep   6
#define Tree_cALT   7
#define Tree_cLAG   8
#define Tree_cRAG   9
#define Tree_cSAG   10
typedef struct Tree_1 {
    SHORTCARD ToBit, ToAttr;
} Tree_tBitInfo;
typedef struct Tree_2 {
    Tree_tBitInfo A[1000000 - 1 + 1];
} *Tree_tBitIndex;
typedef struct Tree_6 *Tree_tInstancePtr;
typedef struct Tree_3 *Tree_tSetOfRelPtr;
typedef struct Tree_3 {
    Relations_tRelation Relation;
    Tree_tSetOfRelPtr Next;
} Tree_tSetOfRel;
typedef SHORTCARD Tree_INTEGER9999;
extern INTEGER Tree_ClassCount;
extern BITSET Tree_GrammarClass;
extern SHORTCARD Tree_MaxVisit;
extern Idents_tIdent Tree_SubUnit, Tree_ViewName, Tree_iPosition, Tree_itPosition, Tree_iInteger, Tree_iMain, Tree_iModule, Tree_itTree, Tree_iNoTree;
extern Strings_tString Tree_ModuleName;
extern Sets_tSet Tree_TypeNames, Tree_MaxSet;
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
#define Tree_Ag   24
#define Tree_Precs   25
#define Tree_NoPrec   26
#define Tree_Prec   27
#define Tree_LeftAssoc   28
#define Tree_RightAssoc   29
#define Tree_NonAssoc   30
#define Tree_Actions   31
#define Tree_NoAction   32
#define Tree_Action   33
#define Tree_Assign   34
#define Tree_Copy   35
#define Tree_TargetCode   36
#define Tree_Order   37
#define Tree_Check   38
#define Tree_Modules   39
#define Tree_NoModule   40
#define Tree_Module   41
#define Tree_Props   42
#define Tree_NoProp   43
#define Tree_Prop   44
#define Tree_Select   45
#define Tree_Decls   46
#define Tree_NoDecl   47
#define Tree_Decl   48
typedef struct Tree_56 *Tree_tTree;
typedef void (*Tree_tProcTree) ARGS((Tree_tTree));
typedef SHORTCARD Tree_INTEGER0;
typedef BITSET Tree_tAttrProperties;
typedef BITSET Tree_tClassProperties;
typedef Tree_tTree Tree_tClass;
typedef void (*Tree_ProcOfT) ARGS((Tree_tTree));
extern Sets_tSet Tree_Options;
extern IO_tFile Tree_f;
extern struct Tree_4 {
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
typedef struct Tree_5 {
    Tree_tTree Selector;
    Tree_tTree Attribute;
    Tree_tTree Action;
    Tree_tAttrProperties Properties;
    SHORTINT Order;
    SHORTCARD CopyArg;
} Tree_tInstance;
typedef struct Tree_6 {
    Tree_tInstance A[100000 - 1 + 1];
} Tree_tInstances;
extern Tree_tTree Tree_nNoAction, Tree_nNoAttribute, Tree_nNoClass, Tree_nNoDecl, Tree_nNoDesignator, Tree_nNoLayout, Tree_nNoModule, Tree_nNoName, Tree_nNoPrec, Tree_nNoProp;
extern void Tree_BeginTree2 ARGS(());
extern Tree_tTree Tree_IdentifyModule ARGS((Tree_tTree t, Idents_tIdent Ident));
extern void Tree_WriteName ARGS((Tree_tInstance i));
extern void Tree_WriteInstance ARGS((Tree_tInstance i));
extern void Tree_WriteDependencies ARGS((Tree_tTree t, Relations_tRelation r, Sets_tSet s));
extern void Tree_WriteCyclics ARGS((Tree_tTree t, Sets_tSet s));
extern void Tree_WriteAttrProperties ARGS((IO_tFile f, Tree_tAttrProperties Properties));
extern void Tree_WriteClassProperties ARGS((IO_tFile f, Tree_tClassProperties Properties));
extern void Tree_WriteClass ARGS((Tree_tTree t));
extern BOOLEAN Tree_HasItem ARGS((Tree_tTree t, SHORTCARD Item));
typedef struct Tree_7 {
    SHORTCARD yyKind, yyMark;
} Tree_yytNodeHead;
typedef struct Tree_8 {
    Tree_yytNodeHead yyHead;
} Tree_yClasses;
typedef struct Tree_9 {
    Tree_yytNodeHead yyHead;
} Tree_yNoClass;
typedef struct Tree_10 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Tree_tClassProperties Properties;
    Tree_tTree Attributes;
    Tree_tTree Extensions;
    Tree_tTree Next;
    Tree_tTree BaseClass;
    Idents_tIdent Selector;
    Positions_tPosition Pos;
    SHORTCARD Code;
    Idents_tIdent Prec;
    Tree_tTree Names;
    SHORTCARD AttrCount;
    SHORTCARD InstCount;
    Tree_tInstancePtr Instance;
    Relations_tRelation DP;
    Relations_tRelation SNC;
    Relations_tRelation DNC;
    Relations_tRelation OAG;
    Relations_tRelation Part;
    SHORTCARD Index;
    SHORTCARD Visits;
    Sets_tSet Users;
    Tree_INTEGER0 Generated;
    SHORTCARD BitCount;
    Tree_tBitIndex BitIndex;
    Tree_tSetOfRelPtr D;
    SHORTCARD ClassChildCount;
} Tree_yClass;
typedef struct Tree_11 {
    Tree_yytNodeHead yyHead;
} Tree_yAttributes;
typedef struct Tree_12 {
    Tree_yytNodeHead yyHead;
} Tree_yNoAttribute;
typedef struct Tree_13 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    SHORTCARD Item;
} Tree_yAttrOrAction;
typedef struct Tree_14 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    SHORTCARD Item;
    Idents_tIdent Name;
    Idents_tIdent Type;
    Tree_tAttrProperties Properties;
    Positions_tPosition Pos;
    SHORTCARD AttrIndex;
    Tree_INTEGER9999 Partition;
    BITSET Usage;
    SHORTCARD InstOffset;
    Tree_tClass Class;
    SHORTCARD ParsIndex;
    SHORTCARD BitOffset;
    SHORTCARD ChildIndex;
} Tree_yChild;
typedef struct Tree_15 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    SHORTCARD Item;
    Idents_tIdent Name;
    Idents_tIdent Type;
    Tree_tAttrProperties Properties;
    Positions_tPosition Pos;
    SHORTCARD AttrIndex;
    Tree_INTEGER9999 Partition;
    BITSET Usage;
} Tree_yAttribute;
typedef struct Tree_16 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    SHORTCARD Item;
    Tree_tTree Actions;
    SHORTCARD Name;
    SHORTCARD ParsIndex;
    BITSET Properties;
} Tree_yActionPart;
typedef struct Tree_17 {
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
typedef struct Tree_18 {
    Tree_yytNodeHead yyHead;
} Tree_yDesignators;
typedef struct Tree_19 {
    Tree_yytNodeHead yyHead;
} Tree_yNoDesignator;
typedef struct Tree_20 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Selector;
    Idents_tIdent Attribute;
    Positions_tPosition Pos;
    Positions_tPosition AttributePos;
    Tree_tTree Next;
} Tree_yDesignator;
typedef struct Tree_21 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Attribute;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yIdent;
typedef struct Tree_22 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Designators;
    Idents_tIdent Type;
    Idents_tIdent Attribute;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yRemote;
typedef struct Tree_23 {
    Tree_yytNodeHead yyHead;
    StringMem_tStringRef Code;
    Tree_tTree Next;
} Tree_yAny;
typedef struct Tree_24 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Layouts;
    Tree_tTree Next;
} Tree_yAnys;
typedef struct Tree_25 {
    Tree_yytNodeHead yyHead;
} Tree_yLayouts;
typedef struct Tree_26 {
    Tree_yytNodeHead yyHead;
} Tree_yNoLayout;
typedef struct Tree_27 {
    Tree_yytNodeHead yyHead;
    StringMem_tStringRef Code;
    Tree_tTree Next;
} Tree_yLayoutAny;
typedef struct Tree_28 {
    Tree_yytNodeHead yyHead;
} Tree_yNames;
typedef struct Tree_29 {
    Tree_yytNodeHead yyHead;
} Tree_yNoName;
typedef struct Tree_30 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Positions_tPosition Pos;
    Tree_tTree Next;
} Tree_yName;
typedef struct Tree_31 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Idents_tIdent ScannerName;
    Idents_tIdent ParserName;
    Tree_tTree ParserCodes;
    Idents_tIdent TreeName;
    Tree_tTree TreeCodes;
    Idents_tIdent EvalName;
    Tree_tTree EvalCodes;
    Tree_tTree Precs;
    Tree_tTree Props;
    Tree_tTree Decls;
    Tree_tTree Classes;
    Tree_tTree Modules;
    BITSET Properties;
} Tree_yAg;
typedef struct Tree_32 {
    Tree_yytNodeHead yyHead;
} Tree_yPrecs;
typedef struct Tree_33 {
    Tree_yytNodeHead yyHead;
} Tree_yNoPrec;
typedef struct Tree_34 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Names;
    Tree_tTree Next;
} Tree_yPrec;
typedef struct Tree_35 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Names;
    Tree_tTree Next;
} Tree_yLeftAssoc;
typedef struct Tree_36 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Names;
    Tree_tTree Next;
} Tree_yRightAssoc;
typedef struct Tree_37 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Names;
    Tree_tTree Next;
} Tree_yNonAssoc;
typedef struct Tree_38 {
    Tree_yytNodeHead yyHead;
} Tree_yActions;
typedef struct Tree_39 {
    Tree_yytNodeHead yyHead;
} Tree_yNoAction;
typedef struct Tree_40 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Positions_tPosition Pos;
} Tree_yAction;
typedef struct Tree_41 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Positions_tPosition Pos;
    Tree_tTree Results;
    Tree_tTree Arguments;
} Tree_yAssign;
typedef struct Tree_42 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Positions_tPosition Pos;
    Tree_tTree Results;
    Tree_tTree Arguments;
} Tree_yCopy;
typedef struct Tree_43 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Positions_tPosition Pos;
    Tree_tTree Results;
    Tree_tTree Code;
} Tree_yTargetCode;
typedef struct Tree_44 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Positions_tPosition Pos;
    Tree_tTree Results;
    Tree_tTree Arguments;
} Tree_yOrder;
typedef struct Tree_45 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Next;
    Positions_tPosition Pos;
    Tree_tTree Condition;
    Tree_tTree Statement;
    Tree_tTree Actions;
    Tree_tTree Results;
} Tree_yCheck;
typedef struct Tree_46 {
    Tree_yytNodeHead yyHead;
} Tree_yModules;
typedef struct Tree_47 {
    Tree_yytNodeHead yyHead;
} Tree_yNoModule;
typedef struct Tree_48 {
    Tree_yytNodeHead yyHead;
    Idents_tIdent Name;
    Tree_tTree ParserCodes;
    Tree_tTree TreeCodes;
    Tree_tTree EvalCodes;
    Tree_tTree Props;
    Tree_tTree Decls;
    Tree_tTree Classes;
    Tree_tTree Next;
    BITSET Properties;
} Tree_yModule;
typedef struct Tree_49 {
    Tree_yytNodeHead yyHead;
} Tree_yProps;
typedef struct Tree_50 {
    Tree_yytNodeHead yyHead;
} Tree_yNoProp;
typedef struct Tree_51 {
    Tree_yytNodeHead yyHead;
    BITSET Properties;
    Tree_tTree Names;
    Tree_tTree Next;
} Tree_yProp;
typedef struct Tree_52 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Names;
    Tree_tTree Next;
} Tree_ySelect;
typedef struct Tree_53 {
    Tree_yytNodeHead yyHead;
} Tree_yDecls;
typedef struct Tree_54 {
    Tree_yytNodeHead yyHead;
} Tree_yNoDecl;
typedef struct Tree_55 {
    Tree_yytNodeHead yyHead;
    Tree_tTree Names;
    Tree_tTree Attributes;
    Tree_tClassProperties Properties;
    Tree_tTree Next;
} Tree_yDecl;
typedef struct Tree_56 {
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
            Tree_yAg Ag;
        } V_26;
        struct {
            Tree_yPrecs Precs;
        } V_27;
        struct {
            Tree_yNoPrec NoPrec;
        } V_28;
        struct {
            Tree_yPrec Prec;
        } V_29;
        struct {
            Tree_yLeftAssoc LeftAssoc;
        } V_30;
        struct {
            Tree_yRightAssoc RightAssoc;
        } V_31;
        struct {
            Tree_yNonAssoc NonAssoc;
        } V_32;
        struct {
            Tree_yActions Actions;
        } V_33;
        struct {
            Tree_yNoAction NoAction;
        } V_34;
        struct {
            Tree_yAction Action;
        } V_35;
        struct {
            Tree_yAssign Assign;
        } V_36;
        struct {
            Tree_yCopy Copy;
        } V_37;
        struct {
            Tree_yTargetCode TargetCode;
        } V_38;
        struct {
            Tree_yOrder Order;
        } V_39;
        struct {
            Tree_yCheck Check;
        } V_40;
        struct {
            Tree_yModules Modules;
        } V_41;
        struct {
            Tree_yNoModule NoModule;
        } V_42;
        struct {
            Tree_yModule Module;
        } V_43;
        struct {
            Tree_yProps Props;
        } V_44;
        struct {
            Tree_yNoProp NoProp;
        } V_45;
        struct {
            Tree_yProp Prop;
        } V_46;
        struct {
            Tree_ySelect Select;
        } V_47;
        struct {
            Tree_yDecls Decls;
        } V_48;
        struct {
            Tree_yNoDecl NoDecl;
        } V_49;
        struct {
            Tree_yDecl Decl;
        } V_50;
    } U_1;
} Tree_yyNode;
extern Tree_tTree Tree_TreeRoot;
extern LONGCARD Tree_HeapUsed;
extern ADDRESS Tree_yyPoolFreePtr, Tree_yyPoolMaxPtr;
extern struct Tree_57 {
    SHORTCARD A[138 + 1];
} Tree_yyNodeSize;
extern PROC Tree_yyExit;
extern Tree_tTree Tree_yyAlloc ARGS(());
extern Tree_tTree Tree_MakeTree ARGS((SHORTCARD Kind));
extern BOOLEAN Tree_IsType ARGS((Tree_tTree Tree, SHORTCARD Kind));
extern Tree_tTree Tree_mClasses ARGS(());
extern Tree_tTree Tree_mNoClass ARGS(());
extern Tree_tTree Tree_mClass ARGS((Idents_tIdent pName, Tree_tClassProperties pProperties, Tree_tTree pAttributes, Tree_tTree pExtensions, Tree_tTree pNext, Idents_tIdent pSelector, Positions_tPosition pPos, SHORTCARD pCode, Idents_tIdent pPrec, Tree_tTree pNames));
extern Tree_tTree Tree_mAttributes ARGS(());
extern Tree_tTree Tree_mNoAttribute ARGS(());
extern Tree_tTree Tree_mAttrOrAction ARGS((Tree_tTree pNext));
extern Tree_tTree Tree_mChild ARGS((Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties, Positions_tPosition pPos));
extern Tree_tTree Tree_mAttribute ARGS((Tree_tTree pNext, Idents_tIdent pName, Idents_tIdent pType, Tree_tAttrProperties pProperties, Positions_tPosition pPos));
extern Tree_tTree Tree_mActionPart ARGS((Tree_tTree pNext, Tree_tTree pActions));
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
extern Tree_tTree Tree_mAg ARGS((Idents_tIdent pName, Idents_tIdent pScannerName, Idents_tIdent pParserName, Tree_tTree pParserCodes, Idents_tIdent pTreeName, Tree_tTree pTreeCodes, Idents_tIdent pEvalName, Tree_tTree pEvalCodes, Tree_tTree pPrecs, Tree_tTree pProps, Tree_tTree pDecls, Tree_tTree pClasses, Tree_tTree pModules));
extern Tree_tTree Tree_mPrecs ARGS(());
extern Tree_tTree Tree_mNoPrec ARGS(());
extern Tree_tTree Tree_mPrec ARGS((Tree_tTree pNames, Tree_tTree pNext));
extern Tree_tTree Tree_mLeftAssoc ARGS((Tree_tTree pNames, Tree_tTree pNext));
extern Tree_tTree Tree_mRightAssoc ARGS((Tree_tTree pNames, Tree_tTree pNext));
extern Tree_tTree Tree_mNonAssoc ARGS((Tree_tTree pNames, Tree_tTree pNext));
extern Tree_tTree Tree_mActions ARGS(());
extern Tree_tTree Tree_mNoAction ARGS(());
extern Tree_tTree Tree_mAction ARGS((Tree_tTree pNext, Positions_tPosition pPos));
extern Tree_tTree Tree_mAssign ARGS((Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pArguments));
extern Tree_tTree Tree_mCopy ARGS((Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pArguments));
extern Tree_tTree Tree_mTargetCode ARGS((Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pCode));
extern Tree_tTree Tree_mOrder ARGS((Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pResults, Tree_tTree pArguments));
extern Tree_tTree Tree_mCheck ARGS((Tree_tTree pNext, Positions_tPosition pPos, Tree_tTree pCondition, Tree_tTree pStatement, Tree_tTree pActions));
extern Tree_tTree Tree_mModules ARGS(());
extern Tree_tTree Tree_mNoModule ARGS(());
extern Tree_tTree Tree_mModule ARGS((Idents_tIdent pName, Tree_tTree pParserCodes, Tree_tTree pTreeCodes, Tree_tTree pEvalCodes, Tree_tTree pProps, Tree_tTree pDecls, Tree_tTree pClasses, Tree_tTree pNext));
extern Tree_tTree Tree_mProps ARGS(());
extern Tree_tTree Tree_mNoProp ARGS(());
extern Tree_tTree Tree_mProp ARGS((BITSET pProperties, Tree_tTree pNames, Tree_tTree pNext));
extern Tree_tTree Tree_mSelect ARGS((Tree_tTree pNames, Tree_tTree pNext));
extern Tree_tTree Tree_mDecls ARGS(());
extern Tree_tTree Tree_mNoDecl ARGS(());
extern Tree_tTree Tree_mDecl ARGS((Tree_tTree pNames, Tree_tTree pAttributes, Tree_tClassProperties pProperties, Tree_tTree pNext));
extern void Tree_WriteTreeNode ARGS((IO_tFile f, Tree_tTree Tree));
extern Tree_tTree Tree_ReverseTree ARGS((Tree_tTree Tree));
extern void Tree_QueryTree ARGS((Tree_tTree Tree));
extern void Tree_BeginTree ARGS(());
extern void Tree_CloseTree ARGS(());
extern void Tree__init();
