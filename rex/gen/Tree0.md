DEFINITION MODULE Tree0;

IMPORT SYSTEM, IO;
(* line 23 "../src/rex.cg" *)

FROM Sets	IMPORT tSet;
FROM Texts	IMPORT tText;
FROM StringMem	IMPORT tStringRef;
FROM Positions	IMPORT tPosition;
FROM Tree	IMPORT tTree;


CONST
NoTree0 = NIL;

Node = 1;
Node1 = 2;
Option = 3;
Repetition = 4;
Node2 = 5;
List = 6;
Sequence = 7;
Alternative = 8;
Ch = 9;
Set = 10;
String = 11;
Rule = 12;
Pattern = 13;

TYPE tTree0 = POINTER TO yyNode;
tProcTree = PROCEDURE (tTree0);




TYPE
yytNodeHead = RECORD yyKind, yyMark: SHORTCARD;   END;
yNode = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; END;
yNode1 = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Son1: tTree0; END;
yOption = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Son1: tTree0; END;
yRepetition = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Son1: tTree0; END;
yNode2 = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Son1: tTree0; Son2: tTree0; END;
yList = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Son1: tTree0; Son2: tTree0; END;
ySequence = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Son1: tTree0; Son2: tTree0; END;
yAlternative = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Son1: tTree0; Son2: tTree0; END;
yCh = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Ch: CHAR; END;
ySet = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Set: tSet; card: SHORTCARD; END;
yString = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; String: tStringRef; END;
yRule = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; Patterns: tTree0; TargetCode: tText; Line: SHORTCARD; CodeMode: SHORTCARD; RuleNr: SHORTCARD; END;
yPattern = RECORD yyHead: yytNodeHead; Tree: tTree; IsConstantRE: BOOLEAN; LeafCount: SHORTINT; NodeCount: SHORTINT; StartStates: tSet; RegExpr: tTree0; RightContext: tTree0; PatternNr: SHORTCARD; Position: tPosition; card: SHORTINT; END;

yyNode = RECORD
CASE : SHORTCARD OF
| 0: Kind: SHORTCARD;
| 14: yyHead: yytNodeHead;
| Node: Node: yNode;
| Node1: Node1: yNode1;
| Option: Option: yOption;
| Repetition: Repetition: yRepetition;
| Node2: Node2: yNode2;
| List: List: yList;
| Sequence: Sequence: ySequence;
| Alternative: Alternative: yAlternative;
| Ch: Ch: yCh;
| Set: Set: ySet;
| String: String: yString;
| Rule: Rule: yRule;
| Pattern: Pattern: yPattern;
END;
END;

VAR Tree0Root        : tTree0;
VAR HeapUsed   : LONGCARD;
VAR yyPoolFreePtr, yyPoolMaxPtr        : SYSTEM.ADDRESS;
VAR yyNodeSize : ARRAY [0..13] OF SHORTCARD;
VAR yyExit     : PROC;

PROCEDURE yyAlloc      (): tTree0;
PROCEDURE MakeTree0  (Kind: SHORTCARD): tTree0;
PROCEDURE IsType       (Tree: tTree0; Kind: SHORTCARD): BOOLEAN;

PROCEDURE mNode (): tTree0;
PROCEDURE mNode1 (pSon1: tTree0): tTree0;
PROCEDURE mOption (pSon1: tTree0): tTree0;
PROCEDURE mRepetition (pSon1: tTree0): tTree0;
PROCEDURE mNode2 (pSon1: tTree0; pSon2: tTree0): tTree0;
PROCEDURE mList (pSon1: tTree0; pSon2: tTree0): tTree0;
PROCEDURE mSequence (pSon1: tTree0; pSon2: tTree0): tTree0;
PROCEDURE mAlternative (pSon1: tTree0; pSon2: tTree0): tTree0;
PROCEDURE mCh (pCh: CHAR): tTree0;
PROCEDURE mSet (pSet: tSet): tTree0;
PROCEDURE mString (pString: tStringRef): tTree0;
PROCEDURE mRule (pPatterns: tTree0; pTargetCode: tText; pLine: SHORTCARD; pCodeMode: SHORTCARD; pRuleNr: SHORTCARD): tTree0;
PROCEDURE mPattern (pStartStates: tSet; pRegExpr: tTree0; pRightContext: tTree0; pPatternNr: SHORTCARD; pPosition: tPosition): tTree0;

PROCEDURE ReleaseTree0Module;
PROCEDURE WriteTree0       (f: IO.tFile; Tree: tTree0);
PROCEDURE TraverseTree0TD  (Tree: tTree0; Proc: tProcTree);
PROCEDURE BeginTree0;
PROCEDURE CloseTree0;

END Tree0.
