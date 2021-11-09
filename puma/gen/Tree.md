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
Spec = 49;
TreeNames = 50;
NoTreeName = 51;
TreeName = 52;
Routines = 53;
NoRoutine = 54;
Routine = 55;
Procedure = 56;
Function = 57;
Predicate = 58;
Parameters = 59;
NoParameter = 60;
Param = 61;
Type = 62;
Rules = 63;
NoRule = 64;
Rule = 65;
Patterns = 66;
NoPattern = 67;
OnePattern = 68;
OnePatternAlts = 69;
PatternsList = 70;
NoPatternsList = 71;
OnePatternsList = 72;
Pattern = 73;
Decompose = 74;
VarDef = 75;
NilTest = 76;
DontCare1 = 77;
DontCare1Explicit = 78;
DontCare1Internal = 79;
DontCare = 80;
DontCareExplicit = 81;
DontCareInternal = 82;
Value = 83;
Exprs = 84;
NoExpr = 85;
OneExpr = 86;
NamedExpr = 87;
Expr = 88;
Compose = 89;
VarUse = 90;
AttrDesc = 91;
Nil = 92;
Call = 93;
Binary = 94;
yy1 = 95;
BinaryCompound = 96;
PreOperator = 97;
PostOperator = 98;
Index = 99;
Parents = 100;
TargetExpr = 101;
StringExpr = 102;
Statements = 103;
NoStatement = 104;
Statement = 105;
ProcCall = 106;
Condition = 107;
Assignment = 108;
Reject = 109;
Fail = 110;
TargetStmt = 111;
Nl = 112;
WriteStr = 113;
Formals = 114;
NoFormal = 115;
Formal = 116;
PlainFormal = 117;
RoutineFormal = 118;
DummyFormal = 119;
TypeDesc = 120;
NodeTypes = 121;
UserType = 122;
Path = 123;
Var = 124;
ConsType = 125;
Field = 126;
Tests = 127;
NoTest = 128;
OneTest = 129;
TestKind = 130;
TestIsType = 131;
TestNil = 132;
TestNonlin = 133;
TestValue = 134;
Decisions = 135;
NoDecision = 136;
Decision = 137;
Decided = 138;

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
(* line 908 "" *)




TYPE
yytNodeHead = RECORD yyKind, yyMark: SHORTCARD;   END;
yClasses = RECORD yyHead: yytNodeHead; END;
yNoClass = RECORD yyHead: yytNodeHead; END;
yClass = RECORD yyHead: yytNodeHead; Name: tIdent; Properties: tClassProperties; Attributes: tTree; Extensions: tTree; Next: tTree; BaseClass: tTree; Formals: tTree; TypeDesc: tTree; Index: SHORTCARD; Depth: INTEGER; END;
yAttributes = RECORD yyHead: yytNodeHead; END;
yNoAttribute = RECORD yyHead: yytNodeHead; END;
yAttrOrAction = RECORD yyHead: yytNodeHead; Next: tTree; END;
yChild = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Type: tIdent; Properties: tAttrProperties; END;
yAttribute = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Type: tIdent; Properties: tAttrProperties; END;
yActionPart = RECORD yyHead: yytNodeHead; Next: tTree; END;
yCodes = RECORD yyHead: yytNodeHead; Export: tText; Import: tText; Global: tText; SpecWith: tText; BodyWith: tText; Local: tText; Begin: tText; Close: tText; ExportLine: tPosition; ImportLine: tPosition; GlobalLine: tPosition; SpecWithLine: tPosition; BodyWithLine: tPosition; LocalLine: tPosition; BeginLine: tPosition; CloseLine: tPosition; END;
yDesignators = RECORD yyHead: yytNodeHead; END;
yNoDesignator = RECORD yyHead: yytNodeHead; END;
yDesignator = RECORD yyHead: yytNodeHead; Selector: tIdent; Attribute: tIdent; Pos: tPosition; AttributePos: tPosition; Next: tTree; Object: tClass; Type: tIdent; END;
yIdent = RECORD yyHead: yytNodeHead; Attribute: tIdent; Pos: tPosition; Next: tTree; Object: tClass; END;
yRemote = RECORD yyHead: yytNodeHead; Designators: tTree; Type: tIdent; Attribute: tIdent; Pos: tPosition; Next: tTree; END;
yAny = RECORD yyHead: yytNodeHead; Code: tStringRef; Next: tTree; END;
yAnys = RECORD yyHead: yytNodeHead; Layouts: tTree; Next: tTree; END;
yLayouts = RECORD yyHead: yytNodeHead; END;
yNoLayout = RECORD yyHead: yytNodeHead; END;
yLayoutAny = RECORD yyHead: yytNodeHead; Code: tStringRef; Next: tTree; END;
yNames = RECORD yyHead: yytNodeHead; END;
yNoName = RECORD yyHead: yytNodeHead; END;
yName = RECORD yyHead: yytNodeHead; Name: tIdent; Pos: tPosition; Next: tTree; Object: tClass; END;
ySpec = RECORD yyHead: yytNodeHead; TrafoName: tIdent; TreeNames: tTree; Public: tTree; Extern: tTree; Codes: tTree; Routines: tTree; END;
yTreeNames = RECORD yyHead: yytNodeHead; END;
yNoTreeName = RECORD yyHead: yytNodeHead; END;
yTreeName = RECORD yyHead: yytNodeHead; Name: tIdent; Pos: tPosition; Next: tTree; Classes: tTree; ClassCount: SHORTCARD; EmptyType: tTree; UniversalClass: tTree; END;
yRoutines = RECORD yyHead: yytNodeHead; END;
yNoRoutine = RECORD yyHead: yytNodeHead; END;
yRoutine = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; END;
yProcedure = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; END;
yFunction = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; ReturnParams: tTree; ReturnForm: tTree; END;
yPredicate = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; Pos: tPosition; InParams: tTree; OutParams: tTree; Extern: tTree; Local: tText; LocalLine: tPosition; Rules: tTree; InForm: tTree; OutForm: tTree; ParamDecls: tTree; IsExtern: BOOLEAN; Decisions: tTree; END;
yParameters = RECORD yyHead: yytNodeHead; END;
yNoParameter = RECORD yyHead: yytNodeHead; END;
yParam = RECORD yyHead: yytNodeHead; IsRef: BOOLEAN; Name: tIdent; Pos: tPosition; Type: tTree; Next: tTree; END;
yType = RECORD yyHead: yytNodeHead; Name: tIdent; Pos: tPosition; Names: tTree; END;
yRules = RECORD yyHead: yytNodeHead; END;
yNoRule = RECORD yyHead: yytNodeHead; END;
yRule = RECORD yyHead: yytNodeHead; Line: tPosition; Patterns: tTree; Exprs: tTree; Expr: tTree; Statements: tTree; Next: tTree; VarDecls: tTree; HasTempos: BOOLEAN; HasPatterns: BOOLEAN; Tempo: tIdent; Index: SHORTCARD; Tests: tTree; HasExit: BOOLEAN; HasAssign: BOOLEAN; HasTargetCode: BOOLEAN; HasRejectOrFail: BOOLEAN; END;
yPatterns = RECORD yyHead: yytNodeHead; END;
yNoPattern = RECORD yyHead: yytNodeHead; Pos: tPosition; END;
yOnePattern = RECORD yyHead: yytNodeHead; Pattern: tTree; Next: tTree; END;
yOnePatternAlts = RECORD yyHead: yytNodeHead; PatternsList: tTree; Next: tTree; Current: tTree; END;
yPatternsList = RECORD yyHead: yytNodeHead; END;
yNoPatternsList = RECORD yyHead: yytNodeHead; END;
yOnePatternsList = RECORD yyHead: yytNodeHead; Patterns: tTree; Next: tTree; END;
yPattern = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; END;
yDecompose = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; Expr: tTree; Patterns: tTree; Widen: BOOLEAN; Object: tClass; IsProperlyNarrowed: BOOLEAN; END;
yVarDef = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; HasDelimiter: BOOLEAN; Object: tClass; END;
yNilTest = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; Widen: BOOLEAN; IsProperlyNarrowed: BOOLEAN; END;
yDontCare1 = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; END;
yDontCare1Explicit = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; END;
yDontCare1Internal = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; END;
yDontCare = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Tempos: tTree; END;
yDontCareExplicit = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Tempos: tTree; END;
yDontCareInternal = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Tempos: tTree; END;
yValue = RECORD yyHead: yytNodeHead; Pos: tPosition; Tempo: tIdent; TypeDesc: tTree; Path: tTree; Selector: tIdent; Expr: tTree; END;
yExprs = RECORD yyHead: yytNodeHead; END;
yNoExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; END;
yOneExpr = RECORD yyHead: yytNodeHead; Expr: tTree; Next: tTree; END;
yNamedExpr = RECORD yyHead: yytNodeHead; Expr: tTree; Next: tTree; Name: tIdent; NamePos: tPosition; END;
yExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; END;
yCompose = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Expr: tTree; Exprs: tTree; Widen: BOOLEAN; Object: tClass; Tempo: tIdent; TypeDesc: tTree; END;
yVarUse = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Name: tIdent; Widen: BOOLEAN; Object: tClass; END;
yAttrDesc = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Name: tIdent; Widen: BOOLEAN; Object: tClass; Attribute: tIdent; AttributePos: tPosition; Type: tIdent; END;
yNil = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Widen: BOOLEAN; END;
yCall = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Expr: tTree; Exprs: tTree; Patterns: tTree; Object: tClass; END;
yBinary = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Lop: tTree; Operator: tIdent; Rop: tTree; Widen: BOOLEAN; END;
yyy1 = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Lop: tTree; Operator: tIdent; Rop: tTree; Widen: BOOLEAN; END;
yBinaryCompound = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Lop: tTree; Operator: tIdent; Rop: tTree; Widen: BOOLEAN; CompoundOperator: tIdent; END;
yPreOperator = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Operator: tIdent; Expr: tTree; END;
yPostOperator = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Operator: tIdent; Expr: tTree; END;
yIndex = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Expr: tTree; Exprs: tTree; Widen: BOOLEAN; END;
yParents = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Expr: tTree; END;
yTargetExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; Expr: tTree; UsedNames: tSet; END;
yStringExpr = RECORD yyHead: yytNodeHead; Pos: tPosition; Selector: tIdent; String: tStringRef; END;
yStatements = RECORD yyHead: yytNodeHead; END;
yNoStatement = RECORD yyHead: yytNodeHead; END;
yStatement = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yProcCall = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Call: tTree; END;
yCondition = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Expr: tTree; END;
yAssignment = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Adr: tTree; Expr: tTree; Object: tClass; END;
yReject = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yFail = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yTargetStmt = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; Parameters: tTree; Stmt: tTree; UsedNames: tSet; END;
yNl = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; END;
yWriteStr = RECORD yyHead: yytNodeHead; Pos: tPosition; Next: tTree; String: tStringRef; END;
yFormals = RECORD yyHead: yytNodeHead; END;
yNoFormal = RECORD yyHead: yytNodeHead; END;
yFormal = RECORD yyHead: yytNodeHead; Next: tTree; Hides: tTree; Name: tIdent; DeclPos: tPosition; TypeDesc: tTree; Path: tTree; END;
yPlainFormal = RECORD yyHead: yytNodeHead; Next: tTree; Hides: tTree; Name: tIdent; DeclPos: tPosition; TypeDesc: tTree; Path: tTree; END;
yRoutineFormal = RECORD yyHead: yytNodeHead; Next: tTree; Hides: tTree; Name: tIdent; DeclPos: tPosition; TypeDesc: tTree; Path: tTree; TargetClass: tTree; DeclaredTypeIsGuaranteed: BOOLEAN; END;
yDummyFormal = RECORD yyHead: yytNodeHead; Next: tTree; END;
yTypeDesc = RECORD yyHead: yytNodeHead; END;
yNodeTypes = RECORD yyHead: yytNodeHead; TreeName: tTree; Types: tSet; END;
yUserType = RECORD yyHead: yytNodeHead; Type: tIdent; END;
yPath = RECORD yyHead: yytNodeHead; END;
yVar = RECORD yyHead: yytNodeHead; Name: tIdent; IsOutput: BOOLEAN; IsRegister: BOOLEAN; END;
yConsType = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; IsProperlyNarrowed: BOOLEAN; END;
yField = RECORD yyHead: yytNodeHead; Next: tTree; Name: tIdent; END;
yTests = RECORD yyHead: yytNodeHead; END;
yNoTest = RECORD yyHead: yytNodeHead; END;
yOneTest = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; END;
yTestKind = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; TypeDesc: tTree; Name: tIdent; END;
yTestIsType = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; TypeDesc: tTree; Name: tIdent; END;
yTestNil = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; END;
yTestNonlin = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; Path2: tTree; TypeDesc: tTree; END;
yTestValue = RECORD yyHead: yytNodeHead; Next: tTree; Path: tTree; Expr: tTree; TypeDesc: tTree; END;
yDecisions = RECORD yyHead: yytNodeHead; END;
yNoDecision = RECORD yyHead: yytNodeHead; END;
yDecision = RECORD yyHead: yytNodeHead; ThenPart: tTree; ElsePart: tTree; OneTest: tTree; Cases: SHORTCARD; IsUnchanged: BOOLEAN; END;
yDecided = RECORD yyHead: yytNodeHead; ElsePart: tTree; Rule: tTree; END;

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
| Spec: Spec: ySpec;
| TreeNames: TreeNames: yTreeNames;
| NoTreeName: NoTreeName: yNoTreeName;
| TreeName: TreeName: yTreeName;
| Routines: Routines: yRoutines;
| NoRoutine: NoRoutine: yNoRoutine;
| Routine: Routine: yRoutine;
| Procedure: Procedure: yProcedure;
| Function: Function: yFunction;
| Predicate: Predicate: yPredicate;
| Parameters: Parameters: yParameters;
| NoParameter: NoParameter: yNoParameter;
| Param: Param: yParam;
| Type: Type: yType;
| Rules: Rules: yRules;
| NoRule: NoRule: yNoRule;
| Rule: Rule: yRule;
| Patterns: Patterns: yPatterns;
| NoPattern: NoPattern: yNoPattern;
| OnePattern: OnePattern: yOnePattern;
| OnePatternAlts: OnePatternAlts: yOnePatternAlts;
| PatternsList: PatternsList: yPatternsList;
| NoPatternsList: NoPatternsList: yNoPatternsList;
| OnePatternsList: OnePatternsList: yOnePatternsList;
| Pattern: Pattern: yPattern;
| Decompose: Decompose: yDecompose;
| VarDef: VarDef: yVarDef;
| NilTest: NilTest: yNilTest;
| DontCare1: DontCare1: yDontCare1;
| DontCare1Explicit: DontCare1Explicit: yDontCare1Explicit;
| DontCare1Internal: DontCare1Internal: yDontCare1Internal;
| DontCare: DontCare: yDontCare;
| DontCareExplicit: DontCareExplicit: yDontCareExplicit;
| DontCareInternal: DontCareInternal: yDontCareInternal;
| Value: Value: yValue;
| Exprs: Exprs: yExprs;
| NoExpr: NoExpr: yNoExpr;
| OneExpr: OneExpr: yOneExpr;
| NamedExpr: NamedExpr: yNamedExpr;
| Expr: Expr: yExpr;
| Compose: Compose: yCompose;
| VarUse: VarUse: yVarUse;
| AttrDesc: AttrDesc: yAttrDesc;
| Nil: Nil: yNil;
| Call: Call: yCall;
| Binary: Binary: yBinary;
| yy1: yy1: yyy1;
| BinaryCompound: BinaryCompound: yBinaryCompound;
| PreOperator: PreOperator: yPreOperator;
| PostOperator: PostOperator: yPostOperator;
| Index: Index: yIndex;
| Parents: Parents: yParents;
| TargetExpr: TargetExpr: yTargetExpr;
| StringExpr: StringExpr: yStringExpr;
| Statements: Statements: yStatements;
| NoStatement: NoStatement: yNoStatement;
| Statement: Statement: yStatement;
| ProcCall: ProcCall: yProcCall;
| Condition: Condition: yCondition;
| Assignment: Assignment: yAssignment;
| Reject: Reject: yReject;
| Fail: Fail: yFail;
| TargetStmt: TargetStmt: yTargetStmt;
| Nl: Nl: yNl;
| WriteStr: WriteStr: yWriteStr;
| Formals: Formals: yFormals;
| NoFormal: NoFormal: yNoFormal;
| Formal: Formal: yFormal;
| PlainFormal: PlainFormal: yPlainFormal;
| RoutineFormal: RoutineFormal: yRoutineFormal;
| DummyFormal: DummyFormal: yDummyFormal;
| TypeDesc: TypeDesc: yTypeDesc;
| NodeTypes: NodeTypes: yNodeTypes;
| UserType: UserType: yUserType;
| Path: Path: yPath;
| Var: Var: yVar;
| ConsType: ConsType: yConsType;
| Field: Field: yField;
| Tests: Tests: yTests;
| NoTest: NoTest: yNoTest;
| OneTest: OneTest: yOneTest;
| TestKind: TestKind: yTestKind;
| TestIsType: TestIsType: yTestIsType;
| TestNil: TestNil: yTestNil;
| TestNonlin: TestNonlin: yTestNonlin;
| TestValue: TestValue: yTestValue;
| Decisions: Decisions: yDecisions;
| NoDecision: NoDecision: yNoDecision;
| Decision: Decision: yDecision;
| Decided: Decided: yDecided;
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
PROCEDURE mClass (pName: tIdent; pProperties: tClassProperties; pAttributes: tTree; pExtensions: tTree; pNext: tTree): tTree;
PROCEDURE mAttributes (): tTree;
PROCEDURE mNoAttribute (): tTree;
PROCEDURE mAttrOrAction (pNext: tTree): tTree;
PROCEDURE mChild (pNext: tTree; pName: tIdent; pType: tIdent; pProperties: tAttrProperties): tTree;
PROCEDURE mAttribute (pNext: tTree; pName: tIdent; pType: tIdent; pProperties: tAttrProperties): tTree;
PROCEDURE mActionPart (pNext: tTree): tTree;
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
PROCEDURE mSpec (pTrafoName: tIdent; pTreeNames: tTree; pPublic: tTree; pExtern: tTree; pCodes: tTree; pRoutines: tTree): tTree;
PROCEDURE mTreeNames (): tTree;
PROCEDURE mNoTreeName (): tTree;
PROCEDURE mTreeName (pName: tIdent; pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mRoutines (): tTree;
PROCEDURE mNoRoutine (): tTree;
PROCEDURE mRoutine (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree): tTree;
PROCEDURE mProcedure (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree): tTree;
PROCEDURE mFunction (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree; pReturnParams: tTree): tTree;
PROCEDURE mPredicate (pNext: tTree; pName: tIdent; pPos: tPosition; pInParams: tTree; pOutParams: tTree; pExtern: tTree; pLocal: tText; pLocalLine: tPosition; pRules: tTree): tTree;
PROCEDURE mParameters (): tTree;
PROCEDURE mNoParameter (): tTree;
PROCEDURE mParam (pIsRef: BOOLEAN; pName: tIdent; pPos: tPosition; pType: tTree; pNext: tTree): tTree;
PROCEDURE mType (pName: tIdent; pPos: tPosition; pNames: tTree): tTree;
PROCEDURE mRules (): tTree;
PROCEDURE mNoRule (): tTree;
PROCEDURE mRule (pLine: tPosition; pPatterns: tTree; pExprs: tTree; pExpr: tTree; pStatements: tTree; pNext: tTree): tTree;
PROCEDURE mPatterns (): tTree;
PROCEDURE mNoPattern (pPos: tPosition): tTree;
PROCEDURE mOnePattern (pPattern: tTree; pNext: tTree): tTree;
PROCEDURE mOnePatternAlts (pPatternsList: tTree; pNext: tTree; pCurrent: tTree): tTree;
PROCEDURE mPatternsList (): tTree;
PROCEDURE mNoPatternsList (): tTree;
PROCEDURE mOnePatternsList (pPatterns: tTree; pNext: tTree): tTree;
PROCEDURE mPattern (pPos: tPosition): tTree;
PROCEDURE mDecompose (pPos: tPosition; pSelector: tIdent; pExpr: tTree; pPatterns: tTree; pWiden: BOOLEAN): tTree;
PROCEDURE mVarDef (pPos: tPosition; pSelector: tIdent; pHasDelimiter: BOOLEAN): tTree;
PROCEDURE mNilTest (pPos: tPosition; pSelector: tIdent; pWiden: BOOLEAN): tTree;
PROCEDURE mDontCare1 (pPos: tPosition; pSelector: tIdent): tTree;
PROCEDURE mDontCare1Explicit (pPos: tPosition; pSelector: tIdent): tTree;
PROCEDURE mDontCare1Internal (pPos: tPosition; pSelector: tIdent): tTree;
PROCEDURE mDontCare (pPos: tPosition): tTree;
PROCEDURE mDontCareExplicit (pPos: tPosition): tTree;
PROCEDURE mDontCareInternal (pPos: tPosition): tTree;
PROCEDURE mValue (pPos: tPosition; pSelector: tIdent; pExpr: tTree): tTree;
PROCEDURE mExprs (): tTree;
PROCEDURE mNoExpr (pPos: tPosition): tTree;
PROCEDURE mOneExpr (pExpr: tTree; pNext: tTree): tTree;
PROCEDURE mNamedExpr (pExpr: tTree; pNext: tTree; pName: tIdent; pNamePos: tPosition): tTree;
PROCEDURE mExpr (pPos: tPosition; pSelector: tIdent): tTree;
PROCEDURE mCompose (pPos: tPosition; pSelector: tIdent; pExpr: tTree; pExprs: tTree; pWiden: BOOLEAN): tTree;
PROCEDURE mVarUse (pPos: tPosition; pSelector: tIdent; pName: tIdent; pWiden: BOOLEAN): tTree;
PROCEDURE mAttrDesc (pPos: tPosition; pSelector: tIdent; pName: tIdent; pWiden: BOOLEAN; pAttribute: tIdent; pAttributePos: tPosition): tTree;
PROCEDURE mNil (pPos: tPosition; pSelector: tIdent; pWiden: BOOLEAN): tTree;
PROCEDURE mCall (pPos: tPosition; pSelector: tIdent; pExpr: tTree; pExprs: tTree; pPatterns: tTree): tTree;
PROCEDURE mBinary (pPos: tPosition; pSelector: tIdent; pLop: tTree; pOperator: tIdent; pRop: tTree; pWiden: BOOLEAN): tTree;
PROCEDURE myy1 (pPos: tPosition; pSelector: tIdent; pLop: tTree; pOperator: tIdent; pRop: tTree; pWiden: BOOLEAN): tTree;
PROCEDURE mBinaryCompound (pPos: tPosition; pSelector: tIdent; pLop: tTree; pOperator: tIdent; pRop: tTree; pWiden: BOOLEAN; pCompoundOperator: tIdent): tTree;
PROCEDURE mPreOperator (pPos: tPosition; pSelector: tIdent; pOperator: tIdent; pExpr: tTree): tTree;
PROCEDURE mPostOperator (pPos: tPosition; pSelector: tIdent; pOperator: tIdent; pExpr: tTree): tTree;
PROCEDURE mIndex (pPos: tPosition; pSelector: tIdent; pExpr: tTree; pExprs: tTree; pWiden: BOOLEAN): tTree;
PROCEDURE mParents (pPos: tPosition; pSelector: tIdent; pExpr: tTree): tTree;
PROCEDURE mTargetExpr (pPos: tPosition; pSelector: tIdent; pExpr: tTree): tTree;
PROCEDURE mStringExpr (pPos: tPosition; pSelector: tIdent; pString: tStringRef): tTree;
PROCEDURE mStatements (): tTree;
PROCEDURE mNoStatement (): tTree;
PROCEDURE mStatement (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mProcCall (pPos: tPosition; pNext: tTree; pCall: tTree): tTree;
PROCEDURE mCondition (pPos: tPosition; pNext: tTree; pExpr: tTree): tTree;
PROCEDURE mAssignment (pPos: tPosition; pNext: tTree; pAdr: tTree; pExpr: tTree): tTree;
PROCEDURE mReject (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mFail (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mTargetStmt (pPos: tPosition; pNext: tTree; pParameters: tTree; pStmt: tTree): tTree;
PROCEDURE mNl (pPos: tPosition; pNext: tTree): tTree;
PROCEDURE mWriteStr (pPos: tPosition; pNext: tTree; pString: tStringRef): tTree;
PROCEDURE mFormals (): tTree;
PROCEDURE mNoFormal (): tTree;
PROCEDURE mFormal (pNext: tTree; pHides: tTree; pName: tIdent; pDeclPos: tPosition; pTypeDesc: tTree; pPath: tTree): tTree;
PROCEDURE mPlainFormal (pNext: tTree; pHides: tTree; pName: tIdent; pDeclPos: tPosition; pTypeDesc: tTree; pPath: tTree): tTree;
PROCEDURE mRoutineFormal (pNext: tTree; pHides: tTree; pName: tIdent; pDeclPos: tPosition; pTypeDesc: tTree; pPath: tTree; pTargetClass: tTree; pDeclaredTypeIsGuaranteed: BOOLEAN): tTree;
PROCEDURE mDummyFormal (pNext: tTree): tTree;
PROCEDURE mTypeDesc (): tTree;
PROCEDURE mNodeTypes (pTreeName: tTree; pTypes: tSet): tTree;
PROCEDURE mUserType (pType: tIdent): tTree;
PROCEDURE mPath (): tTree;
PROCEDURE mVar (pName: tIdent; pIsOutput: BOOLEAN; pIsRegister: BOOLEAN): tTree;
PROCEDURE mConsType (pNext: tTree; pName: tIdent; pIsProperlyNarrowed: BOOLEAN): tTree;
PROCEDURE mField (pNext: tTree; pName: tIdent): tTree;
PROCEDURE mTests (): tTree;
PROCEDURE mNoTest (): tTree;
PROCEDURE mOneTest (pNext: tTree; pPath: tTree): tTree;
PROCEDURE mTestKind (pNext: tTree; pPath: tTree; pTypeDesc: tTree; pName: tIdent): tTree;
PROCEDURE mTestIsType (pNext: tTree; pPath: tTree; pTypeDesc: tTree; pName: tIdent): tTree;
PROCEDURE mTestNil (pNext: tTree; pPath: tTree): tTree;
PROCEDURE mTestNonlin (pNext: tTree; pPath: tTree; pPath2: tTree; pTypeDesc: tTree): tTree;
PROCEDURE mTestValue (pNext: tTree; pPath: tTree; pExpr: tTree; pTypeDesc: tTree): tTree;
PROCEDURE mDecisions (): tTree;
PROCEDURE mNoDecision (): tTree;
PROCEDURE mDecision (pThenPart: tTree; pElsePart: tTree; pOneTest: tTree; pCases: SHORTCARD; pIsUnchanged: BOOLEAN): tTree;
PROCEDURE mDecided (pElsePart: tTree; pRule: tTree): tTree;

PROCEDURE WriteTreeNode   (f: IO.tFile; Tree: tTree);
PROCEDURE WriteTree       (f: IO.tFile; Tree: tTree);
PROCEDURE ReverseTree     (Tree: tTree): tTree;
PROCEDURE CopyTree        (Tree: tTree): tTree;
PROCEDURE QueryTree       (Tree: tTree);
PROCEDURE BeginTree;
PROCEDURE CloseTree;

END Tree.
