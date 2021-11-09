DEFINITION MODULE Tree;

IMPORT SYSTEM, IO;
(* line 12 "../src/ell.ast" *)

FROM Idents	IMPORT	tIdent;
FROM Sets	IMPORT	tSet;
FROM StringMem	IMPORT	tStringRef;
FROM Positions	IMPORT	tPosition;
FROM SYSTEM	IMPORT	ADDRESS;

TYPE yyEstra = ADDRESS;



VAR ScannerName, ParserName: tIdent;


CONST
NoTree = NIL;

Grammar = 1;
sections = 2;
Sections0 = 3;
Sections = 4;
section = 5;
Export = 6;
Global = 7;
Local = 8;
Begin = 9;
Close = 10;
codes = 11;
Codes0 = 12;
Codes = 13;
Code = 14;
code = 15;
tokens = 16;
Tokens0 = 17;
Tokens = 18;
Token = 19;
token = 20;
Id = 21;
id = 22;
Number = 23;
number = 24;
rules = 25;
Rules0 = 26;
Rules = 27;
Rule = 28;
rule = 29;
expr = 30;
Option = 31;
Times = 32;
Plus = 33;
List = 34;
Action = 35;
Leaf = 36;
alternative = 37;
Alternative0 = 38;
Alternative = 39;
sequence = 40;
Sequence0 = 41;
Sequence = 42;

TYPE tTree = POINTER TO yyNode;
tProcTree = PROCEDURE (tTree);


TYPE
yytNodeHead = RECORD yyKind, yyMark: SHORTCARD; yyEstraInfo: yyEstra;  END;
yGrammar = RECORD yyHead: yytNodeHead; sections: tTree; tokens: tTree; rules: tTree; END;
ysections = RECORD yyHead: yytNodeHead; END;
ySections0 = RECORD yyHead: yytNodeHead; END;
ySections = RECORD yyHead: yytNodeHead; sections: tTree; section: tTree; END;
ysection = RECORD yyHead: yytNodeHead; END;
yExport = RECORD yyHead: yytNodeHead; codes: tTree; END;
yGlobal = RECORD yyHead: yytNodeHead; codes: tTree; END;
yLocal = RECORD yyHead: yytNodeHead; codes: tTree; END;
yBegin = RECORD yyHead: yytNodeHead; codes: tTree; END;
yClose = RECORD yyHead: yytNodeHead; codes: tTree; END;
ycodes = RECORD yyHead: yytNodeHead; END;
yCodes0 = RECORD yyHead: yytNodeHead; END;
yCodes = RECORD yyHead: yytNodeHead; codes: tTree; code: tTree; END;
yCode = RECORD yyHead: yytNodeHead; pos: tPosition; ref: tStringRef; END;
ycode = RECORD yyHead: yytNodeHead; pos: tPosition; ref: tStringRef; END;
ytokens = RECORD yyHead: yytNodeHead; END;
yTokens0 = RECORD yyHead: yytNodeHead; END;
yTokens = RECORD yyHead: yytNodeHead; tokens: tTree; token: tTree; END;
yToken = RECORD yyHead: yytNodeHead; id: tTree; number: tTree; END;
ytoken = RECORD yyHead: yytNodeHead; id: tTree; number: tTree; END;
yId = RECORD yyHead: yytNodeHead; pos: tPosition; ident: tIdent; isstring: BOOLEAN; END;
yid = RECORD yyHead: yytNodeHead; pos: tPosition; ident: tIdent; isstring: BOOLEAN; END;
yNumber = RECORD yyHead: yytNodeHead; pos: tPosition; value: INTEGER; END;
ynumber = RECORD yyHead: yytNodeHead; pos: tPosition; value: INTEGER; END;
yrules = RECORD yyHead: yytNodeHead; END;
yRules0 = RECORD yyHead: yytNodeHead; END;
yRules = RECORD yyHead: yytNodeHead; rules: tTree; rule: tTree; END;
yRule = RECORD yyHead: yytNodeHead; pos: tPosition; id: tTree; codes: tTree; expr: tTree; iscalling: BOOLEAN; END;
yrule = RECORD yyHead: yytNodeHead; pos: tPosition; id: tTree; codes: tTree; expr: tTree; iscalling: BOOLEAN; END;
yexpr = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; END;
yOption = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; expr: tTree; END;
yTimes = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; expr: tTree; END;
yPlus = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; expr: tTree; END;
yList = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; body: tTree; sep: tTree; END;
yAction = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; codes: tTree; END;
yLeaf = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; id: tTree; sure: BOOLEAN; number: INTEGER; END;
yalternative = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; depth: INTEGER; case: BOOLEAN; END;
yAlternative0 = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; depth: INTEGER; case: BOOLEAN; recover: BOOLEAN; default: tTree; END;
yAlternative = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; depth: INTEGER; case: BOOLEAN; alternative: tTree; expr: tTree; END;
ysequence = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; END;
ySequence0 = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; END;
ySequence = RECORD yyHead: yytNodeHead; pos: tPosition; first: tSet; follow: tSet; fifo: tSet; recovery: tSet; length: INTEGER; index: INTEGER; followindex: INTEGER; recindex: INTEGER; expindex: INTEGER; sequence: tTree; expr: tTree; END;

yyNode = RECORD
CASE : SHORTCARD OF
| 0: Kind: SHORTCARD;
| 43: yyHead: yytNodeHead;
| Grammar: Grammar: yGrammar;
| sections: sections: ysections;
| Sections0: Sections0: ySections0;
| Sections: Sections: ySections;
| section: section: ysection;
| Export: Export: yExport;
| Global: Global: yGlobal;
| Local: Local: yLocal;
| Begin: Begin: yBegin;
| Close: Close: yClose;
| codes: codes: ycodes;
| Codes0: Codes0: yCodes0;
| Codes: Codes: yCodes;
| Code: Code: yCode;
| code: code: ycode;
| tokens: tokens: ytokens;
| Tokens0: Tokens0: yTokens0;
| Tokens: Tokens: yTokens;
| Token: Token: yToken;
| token: token: ytoken;
| Id: Id: yId;
| id: id: yid;
| Number: Number: yNumber;
| number: number: ynumber;
| rules: rules: yrules;
| Rules0: Rules0: yRules0;
| Rules: Rules: yRules;
| Rule: Rule: yRule;
| rule: rule: yrule;
| expr: expr: yexpr;
| Option: Option: yOption;
| Times: Times: yTimes;
| Plus: Plus: yPlus;
| List: List: yList;
| Action: Action: yAction;
| Leaf: Leaf: yLeaf;
| alternative: alternative: yalternative;
| Alternative0: Alternative0: yAlternative0;
| Alternative: Alternative: yAlternative;
| sequence: sequence: ysequence;
| Sequence0: Sequence0: ySequence0;
| Sequence: Sequence: ySequence;
END;
END;

VAR TreeRoot        : tTree;
VAR HeapUsed   : LONGCARD;
VAR yyPoolFreePtr, yyPoolMaxPtr        : SYSTEM.ADDRESS;
VAR yyNodeSize : ARRAY [0..42] OF SHORTCARD;
VAR yyExit     : PROC;

PROCEDURE yyAlloc      (): tTree;
PROCEDURE MakeTree  (Kind: SHORTCARD): tTree;
PROCEDURE IsType       (Tree: tTree; Kind: SHORTCARD): BOOLEAN;

PROCEDURE mGrammar (psections: tTree; ptokens: tTree; prules: tTree): tTree;
PROCEDURE msections (): tTree;
PROCEDURE mSections0 (): tTree;
PROCEDURE mSections (psections: tTree; psection: tTree): tTree;
PROCEDURE msection (): tTree;
PROCEDURE mExport (pcodes: tTree): tTree;
PROCEDURE mGlobal (pcodes: tTree): tTree;
PROCEDURE mLocal (pcodes: tTree): tTree;
PROCEDURE mBegin (pcodes: tTree): tTree;
PROCEDURE mClose (pcodes: tTree): tTree;
PROCEDURE mcodes (): tTree;
PROCEDURE mCodes0 (): tTree;
PROCEDURE mCodes (pcodes: tTree; pcode: tTree): tTree;
PROCEDURE mCode (ppos: tPosition; pref: tStringRef): tTree;
PROCEDURE mcode (ppos: tPosition; pref: tStringRef): tTree;
PROCEDURE mtokens (): tTree;
PROCEDURE mTokens0 (): tTree;
PROCEDURE mTokens (ptokens: tTree; ptoken: tTree): tTree;
PROCEDURE mToken (pid: tTree; pnumber: tTree): tTree;
PROCEDURE mtoken (pid: tTree; pnumber: tTree): tTree;
PROCEDURE mId (ppos: tPosition; pident: tIdent; pisstring: BOOLEAN): tTree;
PROCEDURE mid (ppos: tPosition; pident: tIdent; pisstring: BOOLEAN): tTree;
PROCEDURE mNumber (ppos: tPosition; pvalue: INTEGER): tTree;
PROCEDURE mnumber (ppos: tPosition; pvalue: INTEGER): tTree;
PROCEDURE mrules (): tTree;
PROCEDURE mRules0 (): tTree;
PROCEDURE mRules (prules: tTree; prule: tTree): tTree;
PROCEDURE mRule (ppos: tPosition; pid: tTree; pcodes: tTree; pexpr: tTree): tTree;
PROCEDURE mrule (ppos: tPosition; pid: tTree; pcodes: tTree; pexpr: tTree): tTree;
PROCEDURE mexpr (ppos: tPosition): tTree;
PROCEDURE mOption (ppos: tPosition; pexpr: tTree): tTree;
PROCEDURE mTimes (ppos: tPosition; pexpr: tTree): tTree;
PROCEDURE mPlus (ppos: tPosition; pexpr: tTree): tTree;
PROCEDURE mList (ppos: tPosition; pbody: tTree; psep: tTree): tTree;
PROCEDURE mAction (ppos: tPosition; pcodes: tTree): tTree;
PROCEDURE mLeaf (ppos: tPosition; pid: tTree): tTree;
PROCEDURE malternative (ppos: tPosition): tTree;
PROCEDURE mAlternative0 (ppos: tPosition): tTree;
PROCEDURE mAlternative (ppos: tPosition; palternative: tTree; pexpr: tTree): tTree;
PROCEDURE msequence (ppos: tPosition): tTree;
PROCEDURE mSequence0 (ppos: tPosition): tTree;
PROCEDURE mSequence (ppos: tPosition; psequence: tTree; pexpr: tTree): tTree;

PROCEDURE ReverseTree     (Tree: tTree): tTree;
PROCEDURE BeginTree;
PROCEDURE CloseTree;

END Tree.
