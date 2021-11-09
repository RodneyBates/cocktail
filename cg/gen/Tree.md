DEFINITION MODULE Tree;

IMPORT SYSTEM, IO;
(* line 83 "" *)


FROM SYSTEM     IMPORT ADDRESS;
FROM IO         IMPORT tFile;
FROM Strings    IMPORT tString;
FROM StringMem  IMPORT tStringRef;
FROM Idents     IMPORT tIdent;
FROM Texts      IMPORT tText;
FROM Sets       IMPORT tSet;
FROM Relations  IMPORT tRelation;
FROM Positions  IMPORT tPosition;

VAR ErrorCount  : CARDINAL;

CONST

   (* properties of attributes and attribute instances          *)

   Virtual      = 0;
   Computed     = 1;
   Reverse      = 2;    (* list attribute to be used for reversion *)
   Write        = 3;    (* Usage:                               *)
   Read         = 4;    (*                                      *)
   Inherited    = 5;    (* Kind:                                *)
   Synthesized  = 6;
   Input        = 7;    (* Mode:                                *)
   Output       = 8;
   Tree         = 9;    (* Store:                               *)
   Parameter    = 10;
   Stack        = 11;
   Variable     = 12;   (*      global variable                 *)
   Demand       = 13;
   Funct        = 14;
   Ignore       = 15;
(* Abstract     = 16;                                           *)
   Link         = 16;   (* a link child, not a tree child       *)
   Thread       = 17;   (* specified thread                     *)
   Test         = 18;   (* generated for check                  *)
   Left         = 19;   (* lhs/rhs of rule (for instances)      *)
   Right        = 20;   (*                                      *)
   CopyDef      = 21;   (* defined by copy rule                 *)
   CopyUse      = 22;   (* used by copy rule                    *)
   NonBaseComp  = 23;   (* non inherited computation            *)
   MultInhComp  = 24;   (* multiple inherited computation       *)
   First        = 25;   (* first attribute of group             *)
   Dummy        = 26;   (* dummy attribute for complete evaluation *)
   Def          = 27;   (* marks definition of attribute        *)
   Use          = 28;   (* marks last use of attribute          *)
   ChildUse     = 29;   (* marks last use of rhs attribute      *)
   ParentUse    = 30;   (* marks last use of lhs attribute      *)
   Generated    = 31;   (* action part has been generated       *)

   (* properties of classes                                     *)

   Top          = 0;    (* declaration level:                   *)
   Intermediate = 1;    (*                                      *)
   Low          = 2;    (*      (has no extensions)             *)
   Referenced   = 3;    (* explicitly used                      *)
   Reachable    = 4;    (* reachable maybe via extensions       *)
   Nonterminal  = 5;
   Terminal     = 6;
   Explicit     = 7;    (* class explicitely declared           *)
   Implicit     = 8;    (* class implicitely declared           *)
   Trace        = 9;    (*                                      *)
   String       = 10;   (* named by string, otherwise ident     *)
   HasSelector  = 11;   (* selector explicitly specified        *)
   HasChildren  = 12;   (*                                      *)
   HasAttributes= 13;   (*                                      *)
   HasActions   = 14;   (*                                      *)
(* Ignore       = 15;                                           *)
   Abstract     = 16;
   Mark         = 17;
   HasOutput    = 18;   (* has output attributes or tests       *)

(* line 423 "" *)


CONST                   (* grammar classes      *)

   cLNC         = 0;    (* locally non circular *)
   cWAG         = 1;    (* well defined *)
   cSNC         = 2;    (* ANC, ANCAG *)
   cDNC         = 3;
   cLordered    = 4;
   cOAG         = 5;
   cSweep       = 6;
   cALT         = 7;    (* APAG *)
   cLAG         = 8;
   cRAG         = 9;
   cSAG         = 10;

TYPE
   tBitInfo     = RECORD ToBit, ToAttr: SHORTCARD; END;
   tBitIndex    = POINTER TO ARRAY [1 .. 1000000] OF tBitInfo;
   tInstancePtr = POINTER TO tInstances;
   tSetOfRelPtr = POINTER TO tSetOfRel;
   tSetOfRel    = RECORD Relation: tRelation; Next: tSetOfRelPtr; END;
   INTEGER9999  = SHORTCARD;

VAR
   ClassCount   : INTEGER;
   GrammarClass : BITSET;
   MaxVisit     : SHORTCARD;
   SubUnit      ,
   ViewName     ,
   iPosition    ,
   itPosition   ,
   iInteger     ,
   iMain        , (* TREE name *) 
   iModule      , (* SUBUNIT module name, possibly different from iMain *) 
   itTree       ,
   iNoTree      : tIdent;
   ModuleName   : tString;
   TypeNames    ,
   MaxSet       : tSet;


CONST
NoTree = NIL;

Classes = 1;
NoClass = 2;
Class = 3;
Attributes = 4;
NoAttribute = 5;
AttrOrAction = 6;
Child = 7;
Attribute = 8;
ActionPart = 9;
Codes = 10;
Designators = 11;
NoDesignator = 12;
Designator = 13;
Ident = 14;
Remote = 15;
Any = 16;
Anys = 17;
Layouts = 18;
NoLayout = 19;
LayoutAny = 20;
Names = 21;
NoName = 22;
Name = 23;
Ag = 24;
Precs = 25;
NoPrec = 26;
Prec = 27;
LeftAssoc = 28;
RightAssoc = 29;
NonAssoc = 30;
Actions = 31;
NoAction = 32;
Action = 33;
Assign = 34;
Copy = 35;
TargetCode = 36;
Order = 37;
Check = 38;
Modules = 39;
NoModule = 40;
Module = 41;
Props = 42;
NoProp = 43;
Prop = 44;
Select = 45;
Decls = 46;
NoDecl = 47;
Decl = 48;

TYPE tTree = POINTER TO yyNode;
tProcTree = PROCEDURE (tTree);
(* line 158 "" *)


TYPE
   INTEGER0             = SHORTCARD;
   tAttrProperties      = BITSET;
   tClassProperties     = BITSET;
   tClass               = tTree;
   ProcOfT              = PROCEDURE (tTree);

VAR
   Options      : tSet;
   f            : tFile;
   SourceFile   : ARRAY [0..255] OF CHAR;
   NoCodeAttr   ,
   NoCodeClass  : BITSET;

PROCEDURE InitIdentifyClass     (t: tTree);
PROCEDURE InitIdentifyClass2    (t: tTree);
PROCEDURE IdentifyClass         (t: tTree; Ident: tIdent): tTree;
(* Return Attribute node for attribute "Ident" of class "t" *) 
PROCEDURE IdentifyAttribute     (t: tTree; Ident: tIdent): tTree;
PROCEDURE ForallClasses         (t: tTree; Proc: ProcOfT);
PROCEDURE ForallClassesExtensionsFirst (t: tTree; Proc: ProcOfT);
PROCEDURE ForallClassesPreAndPost (t: tTree; PreProc, PostProc : ProcOfT);
PROCEDURE ForallAttributes      (t: tTree; Proc: ProcOfT);
PROCEDURE Error         (ErrorCode: INTEGER; Pos: tPosition);
PROCEDURE Warning       (ErrorCode: INTEGER; Pos: tPosition);
PROCEDURE Information   (ErrorCode: INTEGER; Pos: tPosition);
PROCEDURE ErrorI        (ErrorCode: INTEGER; Pos: tPosition; iClass: INTEGER; iPtr: ADDRESS);
PROCEDURE WarningI      (ErrorCode: INTEGER; Pos: tPosition; iClass: INTEGER; iPtr: ADDRESS);
PROCEDURE InformationI  (ErrorCode: INTEGER; Pos: tPosition; iClass: INTEGER; iPtr: ADDRESS);
PROCEDURE WI            (i: tIdent);
PROCEDURE WE            (i: tIdent);
PROCEDURE WN            (n: INTEGER);

(* line 465 "" *)

TYPE
   tInstance    = RECORD
                     Selector   : tTree; (* For rhs attributes only, the rhs
                                            child to which it belongs *) 
                     Attribute  : tTree;
                     Action     : tTree;
                     Properties : tAttrProperties;
                     Order      : SHORTINT;
                     CopyArg    : SHORTCARD;
                  END;
   tInstances   = ARRAY [1 .. 100000] OF tInstance;

VAR
   nNoAction    ,
   nNoAttribute ,
   nNoClass     ,
   nNoDecl      ,
   nNoDesignator,
   nNoLayout    ,
   nNoModule    ,
   nNoName      ,
   nNoPrec      ,
   nNoProp      : tTree;

PROCEDURE BeginTree2;
PROCEDURE IdentifyModule        (t: tTree; Ident: tIdent): tTree;
PROCEDURE WriteName             (i: tInstance);
PROCEDURE WriteInstance         (i: tInstance);
PROCEDURE WriteDependencies     (t: tTree; r: tRelation; s: tSet);
PROCEDURE WriteCyclics          (t: tTree; s: tSet);
PROCEDURE WriteAttrProperties   (f: tFile; Properties: tAttrProperties);
PROCEDURE WriteClassProperties  (f: tFile; Properties: tClassProperties);
PROCEDURE WriteClass            (t: tTree);

(* line 908 "" *)

PROCEDURE HasItem (t: tTree; Item: SHORTCARD): BOOLEAN;





TYPE
yytNodeHead = RECORD yyKind, yyMark: SHORTCARD;   END;
yClasses = RECORD yyHead: yytNodeHead; END;
yNoClass = RECORD yyHead: yytNodeHead; END;
yClass = RECORD yyHead: yytNodeHead; Name: tIdent; Properties: tClassProperties; Attributes: tTree; Extensions: tTree; Next: tTree; BaseClass: tTree; Selector: tIdent; Pos: tPosition; Code: SHORTCARD; Prec: tIdent; Names: tTree; AttrCount: SHORTCARD; InstCount: SHORTCARD; Instance: tInstancePtr; DP: tRelation; SNC: tRelation; DNC: tRelation; OAG: tRelation; Part: tRelation; Index: SHORTCARD; Visits: SHORTCARD; Users: tSet; Generated: INTEGER0; BitCount: SHORTCARD; BitIndex: tBitIndex; D: tSetOfRelPtr; ClassChildCount: SHORTCARD; END;
yAttributes = RECORD yyHead: yytNodeHead; END;
yNoAttribute = RECORD yyHead: yytNodeHead; END;
yAttrOrAction = RECORD yyHead: yytNodeHead; Next: tTree; Item: SHORTCARD; END;
yChild = RECORD yyHead: yytNodeHead; Next: tTree; Item: SHORTCARD; Name: tIdent; Type: tIdent; Properties: tAttrProperties; Pos: tPosition; AttrIndex: SHORTCARD; Partition: INTEGER9999; Usage: BITSET; InstOffset: SHORTCARD; Class: tClass; ParsIndex: SHORTCARD; BitOffset: SHORTCARD; ChildIndex: SHORTCARD; END;
yAttribute = RECORD yyHead: yytNodeHead; Next: tTree; Item: SHORTCARD; Name: tIdent; Type: tIdent; Properties: tAttrProperties; Pos: tPosition; AttrIndex: SHORTCARD; Partition: INTEGER9999; Usage: BITSET; END;
yActionPart = RECORD yyHead: yytNodeHead; Next: tTree; Item: SHORTCARD; Actions: tTree; Name: SHORTCARD; ParsIndex: SHORTCARD; Properties: BITSET; END;
yCodes = RECORD yyHead: yytNodeHead; Export: tText; Import: tText; Global: tText; SpecWith: tText; BodyWith: tText; Local: tText; Begin: tText; Close: tText; ExportLine: tPosition; ImportLine: tPosition; GlobalLine: tPosition; SpecWithLine: tPosition; BodyWithLine: tPosition; LocalLine: tPosition; BeginLine: tPosition; CloseLine: tPosition; END;
yDesignators = RECORD yyHead: yytNodeHead; END;
yNoDesignator = RECORD yyHead: yytNodeHead; END;
yDesignator = RECORD yyHead: yytNodeHead; Selector: tIdent; Attribute: tIdent; Pos: tPosition; AttributePos: tPosition; Next: tTree; END;
yIdent = RECORD yyHead: yytNodeHead; Attribute: tIdent; Pos: tPosition; Next: tTree; END;
yRemote = RECORD yyHead: yytNodeHead; Designators: tTree; Type: tIdent; Attribute: tIdent; Pos: tPosition; Next: tTree; END;
yAny = RECORD yyHead: yytNodeHead; Code: tStringRef; Next: tTree; END;
yAnys = RECORD yyHead: yytNodeHead; Layouts: tTree; Next: tTree; END;
yLayouts = RECORD yyHead: yytNodeHead; END;
yNoLayout = RECORD yyHead: yytNodeHead; END;
yLayoutAny = RECORD yyHead: yytNodeHead; Code: tStringRef; Next: tTree; END;
yNames = RECORD yyHead: yytNodeHead; END;
yNoName = RECORD yyHead: yytNodeHead; END;
yName = RECORD yyHead: yytNodeHead; Name: tIdent; Pos: tPosition; Next: tTree; END;
yAg = RECORD yyHead: yytNodeHead; Name: tIdent; ScannerName: tIdent; ParserName: tIdent; ParserCodes: tTree; TreeName: tIdent; TreeCodes: tTree; EvalName: tIdent; EvalCodes: tTree; Precs: tTree; Props: tTree; Decls: tTree; Classes: tTree; Modules: tTree; Properties: BITSET; END;
yPrecs = RECORD yyHead: yytNodeHead; END;
yNoPrec = RECORD yyHead: yytNodeHead; END;
yPrec = RECORD yyHead: yytNodeHead; Names: tTree; Next: tTree; END;
yLeftAssoc = RECORD yyHead: yytNodeHead; Names: tTree; Next: tTree; END;
yRightAssoc = RECORD yyHead: yytNodeHead; Names: tTree; Next: tTree; END;
yNonAssoc = RECORD yyHead: yytNodeHead; Names: tTree; Next: tTree; END;
yActions = RECORD yyHead: yytNodeHead; END;
yNoAction = RECORD yyHead: yytNodeHead; END;
yAction = RECORD yyHead: yytNodeHead; Next: tTree; Pos: tPosition; END;
yAssign = RECORD yyHead: yytNodeHead; Next: tTree; Pos: tPosition; Results: tTree; Arguments: tTree; END;
yCopy = RECORD yyHead: yytNodeHead; Next: tTree; Pos: tPosition; Results: tTree; Arguments: tTree; END;
yTargetCode = RECORD yyHead: yytNodeHead; Next: tTree; Pos: tPosition; Results: tTree; Code: tTree; END;
yOrder = RECORD yyHead: yytNodeHead; Next: tTree; Pos: tPosition; Results: tTree; Arguments: tTree; END;
yCheck = RECORD yyHead: yytNodeHead; Next: tTree; Pos: tPosition; Condition: tTree; Statement: tTree; Actions: tTree; Results: tTree; END;
yModules = RECORD yyHead: yytNodeHead; END;
yNoModule = RECORD yyHead: yytNodeHead; END;
yModule = RECORD yyHead: yytNodeHead; Name: tIdent; ParserCodes: tTree; TreeCodes: tTree; EvalCodes: tTree; Props: tTree; Decls: tTree; Classes: tTree; Next: tTree; Properties: BITSET; END;
yProps = RECORD yyHead: yytNodeHead; END;
yNoProp = RECORD yyHead: yytNodeHead; END;
yProp = RECORD yyHead: yytNodeHead; Properties: BITSET; Names: tTree; Next: tTree; END;
ySelect = RECORD yyHead: yytNodeHead; Names: tTree; Next: tTree; END;
yDecls = RECORD yyHead: yytNodeHead; END;
yNoDecl = RECORD yyHead: yytNodeHead; END;
yDecl = RECORD yyHead: yytNodeHead; Names: tTree; Attributes: tTree; Properties: tClassProperties; Next: tTree; END;

yyNode = RECORD
CASE : SHORTCARD OF
| 0: Kind: SHORTCARD;
| 139: yyHead: yytNodeHead;
| Classes: Classes: yClasses;
| NoClass: NoClass: yNoClass;
| Class: Class: yClass;
| Attributes: Attributes: yAttributes;
| NoAttribute: NoAttribute: yNoAttribute;
| AttrOrAction: AttrOrAction: yAttrOrAction;
| Child: Child: yChild;
| Attribute: Attribute: yAttribute;
| ActionPart: ActionPart: yActionPart;
| Codes: Codes: yCodes;
| Designators: Designators: yDesignators;
| NoDesignator: NoDesignator: yNoDesignator;
| Designator: Designator: yDesignator;
| Ident: Ident: yIdent;
| Remote: Remote: yRemote;
| Any: Any: yAny;
| Anys: Anys: yAnys;
| Layouts: Layouts: yLayouts;
| NoLayout: NoLayout: yNoLayout;
| LayoutAny: LayoutAny: yLayoutAny;
| Names: Names: yNames;
| NoName: NoName: yNoName;
| Name: Name: yName;
| Ag: Ag: yAg;
| Precs: Precs: yPrecs;
| NoPrec: NoPrec: yNoPrec;
| Prec: Prec: yPrec;
| LeftAssoc: LeftAssoc: yLeftAssoc;
| RightAssoc: RightAssoc: yRightAssoc;
| NonAssoc: NonAssoc: yNonAssoc;
| Actions: Actions: yActions;
| NoAction: NoAction: yNoAction;
| Action: Action: yAction;
| Assign: Assign: yAssign;
| Copy: Copy: yCopy;
| TargetCode: TargetCode: yTargetCode;
| Order: Order: yOrder;
| Check: Check: yCheck;
| Modules: Modules: yModules;
| NoModule: NoModule: yNoModule;
| Module: Module: yModule;
| Props: Props: yProps;
| NoProp: NoProp: yNoProp;
| Prop: Prop: yProp;
| Select: Select: ySelect;
| Decls: Decls: yDecls;
| NoDecl: NoDecl: yNoDecl;
| Decl: Decl: yDecl;
END;
END;

VAR TreeRoot        : tTree;
VAR HeapUsed   : LONGCARD;
VAR yyPoolFreePtr, yyPoolMaxPtr        : SYSTEM.ADDRESS;
VAR yyNodeSize : ARRAY [0..138] OF SHORTCARD;
VAR yyExit     : PROC;

PROCEDURE yyAlloc      (): tTree;
PROCEDURE MakeTree  (Kind: SHORTCARD): tTree;
PROCEDURE IsType       (Tree: tTree; Kind: SHORTCARD): BOOLEAN;

PROCEDURE mClasses (): tTree;
PROCEDURE mNoClass (): tTree;
PROCEDURE mClass (pName: tIdent; pProperties: tClassProperties; pAttributes: tTree; pExtensions: tTree; pNext: tTree; pSelector: tIdent; pPos: tPosition; pCode: SHORTCARD; pPrec: tIdent; pNames: tTree): tTree;
PROCEDURE mAttributes (): tTree;
PROCEDURE mNoAttribute (): tTree;
PROCEDURE mAttrOrAction (pNext: tTree): tTree;
PROCEDURE mChild (pNext: tTree; pName: tIdent; pType: tIdent; pProperties: tAttrProperties; pPos: tPosition): tTree;
PROCEDURE mAttribute (pNext: tTree; pName: tIdent; pType: tIdent; pProperties: tAttrProperties; pPos: tPosition): tTree;
PROCEDURE mActionPart (pNext: tTree; pActions: tTree): tTree;
PROCEDURE mCodes (pExport: tText; pImport: tText; pGlobal: tText; pSpecWith: tText; pBodyWith: tText; pLocal: tText; pBegin: tText; pClose: tText; pExportLine: tPosition; pImportLine: tPosition; pGlobalLine: tPosition; pSpecWithLine: tPosition; pBodyWithLine: tPosition; pLocalLine: tPosition; pBeginLine: tPosition; pCloseLine: tPosition): tTree;
PROCEDURE mDesignators (): tTree;
PROCEDURE mNoDesignator (): tTree;
PROCEDURE mDesignator (pSelector: tIdent; pAttribute: tIdent; pPos: tPosition; pAttributePos: tPosition; pNext: tTree): tTree;
PROCEDURE mIdent (pAttribute: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mRemote (pDesignators: tTree; pType: tIdent; pAttribute: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mAny (pCode: tStringRef; pNext: tTree): tTree;
PROCEDURE mAnys (pLayouts: tTree; pNext: tTree): tTree;
PROCEDURE mLayouts (): tTree;
PROCEDURE mNoLayout (): tTree;
PROCEDURE mLayoutAny (pCode: tStringRef; pNext: tTree): tTree;
PROCEDURE mNames (): tTree;
PROCEDURE mNoName (): tTree;
PROCEDURE mName (pName: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mAg (pName: tIdent; pScannerName: tIdent; pParserName: tIdent; pParserCodes: tTree; pTreeName: tIdent; pTreeCodes: tTree; pEvalName: tIdent; pEvalCodes: tTree; pPrecs: tTree; pProps: tTree; pDecls: tTree; pClasses: tTree; pModules: tTree): tTree;
PROCEDURE mPrecs (): tTree;
PROCEDURE mNoPrec (): tTree;
PROCEDURE mPrec (pNames: tTree; pNext: tTree): tTree;
PROCEDURE mLeftAssoc (pNames: tTree; pNext: tTree): tTree;
PROCEDURE mRightAssoc (pNames: tTree; pNext: tTree): tTree;
PROCEDURE mNonAssoc (pNames: tTree; pNext: tTree): tTree;
PROCEDURE mActions (): tTree;
PROCEDURE mNoAction (): tTree;
PROCEDURE mAction (pNext: tTree; pPos: tPosition): tTree;
PROCEDURE mAssign (pNext: tTree; pPos: tPosition; pResults: tTree; pArguments: tTree): tTree;
PROCEDURE mCopy (pNext: tTree; pPos: tPosition; pResults: tTree; pArguments: tTree): tTree;
PROCEDURE mTargetCode (pNext: tTree; pPos: tPosition; pResults: tTree; pCode: tTree): tTree;
PROCEDURE mOrder (pNext: tTree; pPos: tPosition; pResults: tTree; pArguments: tTree): tTree;
PROCEDURE mCheck (pNext: tTree; pPos: tPosition; pCondition: tTree; pStatement: tTree; pActions: tTree): tTree;
PROCEDURE mModules (): tTree;
PROCEDURE mNoModule (): tTree;
PROCEDURE mModule (pName: tIdent; pParserCodes: tTree; pTreeCodes: tTree; pEvalCodes: tTree; pProps: tTree; pDecls: tTree; pClasses: tTree; pNext: tTree): tTree;
PROCEDURE mProps (): tTree;
PROCEDURE mNoProp (): tTree;
PROCEDURE mProp (pProperties: BITSET; pNames: tTree; pNext: tTree): tTree;
PROCEDURE mSelect (pNames: tTree; pNext: tTree): tTree;
PROCEDURE mDecls (): tTree;
PROCEDURE mNoDecl (): tTree;
PROCEDURE mDecl (pNames: tTree; pAttributes: tTree; pProperties: tClassProperties; pNext: tTree): tTree;

PROCEDURE WriteTreeNode   (f: IO.tFile; Tree: tTree);
PROCEDURE ReverseTree     (Tree: tTree): tTree;
PROCEDURE QueryTree       (Tree: tTree);
PROCEDURE BeginTree;
PROCEDURE CloseTree;

END Tree.
