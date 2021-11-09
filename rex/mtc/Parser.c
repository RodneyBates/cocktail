#include "SYSTEM_.h"

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Tree0
#include "Tree0.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_DefTable
#include "DefTable.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_ScanGen
#include "ScanGen.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

struct Parser_1 Parser_ParsTabName;

#define IdentUndefined   10
#define ImproperUse   11
#define IdentDefBefore   12
#define Error   3
#define C_1_String   7
typedef struct S_1 {
    union {
        struct {
            Scanner_tScanAttribute Scan;
        } V_1;
        struct {
            Tree0_tTree0 Tree;
        } V_2;
        struct {
            BOOLEAN IsLeftJust;
            Positions_tPosition Position;
        } V_3;
        struct {
            Sets_tSet Set;
        } V_4;
    } U_1;
} tParsAttribute;
static SHORTCARD Number;
static CHAR ch;
static BOOLEAN bool;
static Strings_tString string;
static StringMem_tStringRef stringref;
static Lists_tList Text;
static Sets_tSet set;
static Tree0_tTree0 tree;
static Tree_tTree tree1;
static DefTable_DefRange Definition;
static DefTable_tKind Kind;
static Idents_tIdent Identifier;
static Tree0_tTree0 nNode, EOLTree;
static Tree0_tTree0 AppendRule ARGS((Tree0_tTree0 Tree, CHAR Ch, Lists_tList Text));
#define yyInitStackSize   100
#define yyNoState   0
#define yyFirstTerminal   0
#define yyLastTerminal   38
#define yyFirstSymbol   0
#define yyLastSymbol   64
#define yyTableMax   221
#define yyNTableMax   89
#define yyFirstReadState   1
#define yyLastReadState   55
#define yyFirstReadTermState   56
#define yyLastReadTermState   84
#define yyLastReadNontermState   99
#define yyFirstReduceState   100
#define yyLastReduceState   164
#define yyStartState   1
#define yyStopState   100
#define yyFirstFinalState   yyFirstReadTermState
#define yyLastState   yyLastReduceState
typedef SHORTCARD yyTableElmt;
typedef yyTableElmt yyTCombRange;
typedef yyTableElmt yyNCombRange;
typedef yyTableElmt yyStateRange;
typedef yyTableElmt yyReadRange;
typedef yyTableElmt yyReadReduceRange;
typedef yyTableElmt yyReduceRange;
typedef yyTableElmt yySymbolRange;
typedef struct S_2 {
    yyStateRange Check, Next;
} yyTCombType;
typedef yyStateRange yyNCombType;
typedef yyTCombType *yyTCombTypePtr;
typedef yyNCombType *yyNCombTypePtr;
typedef yyTableElmt yyStackPtrType;
typedef struct S_3 {
    yyStateRange A[MAX_SHORTCARD + 1];
} *yyStackType;
typedef struct S_4 {
    tParsAttribute A[MAX_SHORTCARD + 1];
} *yyAttributeStackType;
static struct S_5 {
    yyTCombTypePtr A[yyLastReadState + 1];
} yyTBasePtr;
static struct S_6 {
    yyNCombTypePtr A[yyLastReadState + 1];
} yyNBasePtr;
static struct S_7 {
    yyReadRange A[yyLastReadState + 1];
} yyDefault;
static struct S_8 {
    yyTCombType A[yyTableMax + 1];
} yyTComb;
static struct S_9 {
    yyNCombType A[yyNTableMax - (yyLastTerminal + 1) + 1];
} yyNComb;
static struct S_10 {
    yyTableElmt A[yyLastReduceState - yyFirstReduceState + 1];
} yyLength;
static struct S_11 {
    yySymbolRange A[yyLastReduceState - yyFirstReduceState + 1];
} yyLeftHandSide;
static struct S_12 {
    yySymbolRange A[yyLastReadState + 1];
} yyContinuation;
static struct S_13 {
    yyReduceRange A[yyLastReadNontermState - yyFirstReadTermState + 1];
} yyFinalToProd;
static BOOLEAN yyIsInitialized;
static System_tFile yyTableFile;
static void Copy ARGS((CHAR Source[], LONGCARD , CHAR Target[], LONGCARD ));
struct S_17 {
    CHAR A[127 + 1];
};
static void ErrorRecovery ARGS((yySymbolRange *Terminal, yyStackType StateStack, LONGINT StackSize, yyStackPtrType StackPtr));
struct S_18 {
    CHAR A[127 + 1];
};
static void ComputeContinuation ARGS((yyStackType Stack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *ContinueSet));
static BOOLEAN IsContinuation ARGS((yySymbolRange Terminal, yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr));
static void ComputeRestartPoints ARGS((yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *RestartSet));
static yyStateRange Next ARGS((yyStateRange State, yySymbolRange Symbol));
static void yyGetTables ARGS(());
struct S_19 {
    yyTCombRange A[yyLastReadState + 1];
};
struct S_20 {
    yyNCombRange A[yyLastReadState + 1];
};
static CARDINAL yyGetTable ARGS((ADDRESS Address));
static void yyErrorCheck ARGS((INTEGER ErrorCode, INTEGER Info));
static void BeginParser ARGS(());


static Tree0_tTree0 AppendRule
# ifdef __STDC__
(Tree0_tTree0 Tree, CHAR Ch, Lists_tList Text)
# else
(Tree, Ch, Text)
Tree0_tTree0 Tree;
CHAR Ch;
Lists_tList Text;
# endif
{
  Sets_tSet Set;
  Tree0_tTree0 t;

  Sets_MakeSet(&Set, (Sets_tElement)GenTabs_StartStateCount);
  Sets_Complement(&Set);
  Sets_Exclude(&Set, 0L);
  t = Tree0_mCh(Ch);
  INC(GenTabs_PatternCount);
  t = Tree0_mPattern(Set, t, nNode, GenTabs_PatternCount, Positions_NoPosition);
  t = Tree0_mList(nNode, t);
  INC(GenTabs_RuleCount);
  t = Tree0_mRule(t, Text, 0, ScanGen_NoPosition, GenTabs_RuleCount);
  return Tree0_mList(Tree, t);
}

static void Copy
# ifdef __STDC__
(CHAR Source[], LONGCARD O_2, CHAR Target[], LONGCARD O_1)
# else
(Source, O_2, Target, O_1)
CHAR Source[];
LONGCARD O_2;
CHAR Target[];
LONGCARD O_1;
# endif
{
  CARDINAL i, j;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Source, O_2, CHAR)
  if ((O_2 - 1) < (O_1 - 1)) {
    j = (O_2 - 1);
  } else {
    j = (O_1 - 1);
  }
  {
    LONGCARD B_1 = 0, B_2 = j;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        Target[i] = Source[i];
        if (i >= B_2) break;
      }
  }
  if ((O_1 - 1) > j) {
    Target[j + 1] = CHR(0);
  }
  FREE_OPEN_ARRAYS
}

void Parser_TokenName
# ifdef __STDC__
(SHORTCARD Token, CHAR Name[], LONGCARD O_3)
# else
(Token, Name, O_3)
SHORTCARD Token;
CHAR Name[];
LONGCARD O_3;
# endif
{
  switch (Token) {
  case 0:;
    Copy((STRING)"_EndOfFile", 10L, Name, O_3);
    break;
  case 1:;
    Copy((STRING)"Ident", 5L, Name, O_3);
    break;
  case 2:;
    Copy((STRING)"Number", 6L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)"String", 6L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)"Char", 4L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)"TargetCode", 10L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)"GLOBAL", 6L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)"BEGIN", 5L, Name, O_3);
    break;
  case 8:;
    Copy((STRING)"CLOSE", 5L, Name, O_3);
    break;
  case 9:;
    Copy((STRING)"DEFINE", 6L, Name, O_3);
    break;
  case 10:;
    Copy((STRING)"START", 5L, Name, O_3);
    break;
  case 11:;
    Copy((STRING)"RULES", 5L, Name, O_3);
    break;
  case 12:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 13:;
    Copy((STRING)",", 1L, Name, O_3);
    break;
  case 14:;
    Copy((STRING)"=", 1L, Name, O_3);
    break;
  case 15:;
    Copy((STRING)":", 1L, Name, O_3);
    break;
  case 16:;
    Copy((STRING)"/", 1L, Name, O_3);
    break;
  case 17:;
    Copy((STRING)"|", 1L, Name, O_3);
    break;
  case 18:;
    Copy((STRING)"+", 1L, Name, O_3);
    break;
  case 19:;
    Copy((STRING)"-", 1L, Name, O_3);
    break;
  case 20:;
    Copy((STRING)"*", 1L, Name, O_3);
    break;
  case 21:;
    Copy((STRING)"?", 1L, Name, O_3);
    break;
  case 22:;
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 23:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 24:;
    Copy((STRING)"[", 1L, Name, O_3);
    break;
  case 25:;
    Copy((STRING)"]", 1L, Name, O_3);
    break;
  case 26:;
    Copy((STRING)"{", 1L, Name, O_3);
    break;
  case 27:;
    Copy((STRING)"}", 1L, Name, O_3);
    break;
  case 28:;
    Copy((STRING)"<", 1L, Name, O_3);
    break;
  case 29:;
    Copy((STRING)">", 1L, Name, O_3);
    break;
  case 30:;
    Copy((STRING)"NOT", 3L, Name, O_3);
    break;
  case 31:;
    Copy((STRING)"LOCAL", 5L, Name, O_3);
    break;
  case 32:;
    Copy((STRING)"EXPORT", 6L, Name, O_3);
    break;
  case 33:;
    Copy((STRING)"#", 1L, Name, O_3);
    break;
  case 34:;
    Copy((STRING)"EOF", 3L, Name, O_3);
    break;
  case 35:;
    Copy((STRING)":-", 2L, Name, O_3);
    break;
  case 36:;
    Copy((STRING)"DEFAULT", 7L, Name, O_3);
    break;
  case 37:;
    Copy((STRING)"SCANNER", 7L, Name, O_3);
    break;
  case 38:;
    Copy((STRING)"SEQUENCE", 8L, Name, O_3);
    break;
  }
}

CARDINAL Parser_Parser
# ifdef __STDC__
()
# else
()
# endif
{
  yyStateRange yyState;
  yySymbolRange yyTerminal;
  yySymbolRange yyNonterminal;
  yyStackPtrType yyStackPtr;
  LONGINT yyStateStackSize;
  LONGINT yyAttrStackSize;
  yyStackPtrType yyShortStackSize;
  yyStackType yyStateStack;
  yyAttributeStackType yyAttributeStack;
  tParsAttribute yySynAttribute;
  Scanner_tScanAttribute yyRepairAttribute;
  yySymbolRange yyRepairToken;
  yyTCombTypePtr yyTCombPtr;
  yyNCombTypePtr yyNCombPtr;
  BOOLEAN yyIsRepairing;
  CARDINAL yyErrorCount;
  struct S_17 yyTokenString;

  BeginParser();
  yyState = yyStartState;
  yyTerminal = VAL(yySymbolRange, Scanner_GetToken());
  yyStateStackSize = yyInitStackSize;
  yyAttrStackSize = yyInitStackSize;
  DynArray_MakeArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
  DynArray_MakeArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
  yyShortStackSize = VAL(yyStackPtrType, yyStateStackSize) - 1;
  yyStackPtr = 0;
  yyErrorCount = 0;
  yyIsRepairing = FALSE;
  for (;;) {
    if (yyStackPtr >= yyShortStackSize) {
      DynArray_ExtendArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
      DynArray_ExtendArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
      yyShortStackSize = VAL(yyStackPtrType, yyStateStackSize) - 1;
    }
    yyStateStack->A[yyStackPtr] = yyState;
    for (;;) {
      yyTCombPtr = (yyTCombTypePtr)((LONGCARD)yyTBasePtr.A[yyState] + VAL(LONGCARD, yyTerminal) * sizeof(yyTCombType));
      if (yyTCombPtr->Check == yyState) {
        yyState = yyTCombPtr->Next;
        goto EXIT_2;
      }
      yyState = yyDefault.A[yyState];
      if (yyState == yyNoState) {
        yyState = yyStateStack->A[yyStackPtr];
        if (yyIsRepairing) {
          yyRepairToken = yyContinuation.A[yyState];
          yyState = Next(yyState, yyRepairToken);
          if (yyState <= yyLastReadTermState) {
            Scanner_ErrorAttribute((LONGCARD)VAL(INTEGER, yyRepairToken), &yyRepairAttribute);
            Parser_TokenName(yyRepairToken, yyTokenString.A, 128L);
            Errors_ErrorMessageI((LONGCARD)Errors_TokenInserted, (LONGCARD)Errors_Repair, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(yyTokenString));
            if (yyState >= yyFirstFinalState) {
              yyState = yyFinalToProd.A[yyState - 56];
            }
            INC(yyStackPtr);
            yyAttributeStack->A[yyStackPtr].U_1.V_1.Scan = yyRepairAttribute;
            yyStateStack->A[yyStackPtr] = yyState;
          }
          if (yyState >= yyFirstFinalState) {
            goto EXIT_2;
          }
        } else {
          INC(yyErrorCount);
          ErrorRecovery(&yyTerminal, yyStateStack, yyStateStackSize, yyStackPtr);
          yyIsRepairing = TRUE;
        }
      }
    } EXIT_2:;
    if (yyState >= yyFirstFinalState) {
      if (yyState <= yyLastReadTermState) {
        INC(yyStackPtr);
        yyAttributeStack->A[yyStackPtr].U_1.V_1.Scan = Scanner_Attribute;
        yyTerminal = VAL(yySymbolRange, Scanner_GetToken());
        yyIsRepairing = FALSE;
      }
      for (;;) {
        switch (yyState) {
        case 100:;
          DynArray_ReleaseArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyTableElmt));
          DynArray_ReleaseArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
          return yyErrorCount;
          break;
        case 101:;
        case 99:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 45;
          break;
        case 102:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 39;
          GenTabs_StartStateCount = 0;
          GenTabs_RuleCount = 0;
          GenTabs_PatternCount = 0;
          GenTabs_LeftJustUsed = FALSE;
          EOLTree = Tree0_mCh(Dfa_EolCh);
          Strings_ArrayToString((STRING)"ANY", 3L, &string);
          Sets_MakeSet(&set, ORD(Dfa_LastCh));
          Sets_Complement(&set);
          Sets_Exclude(&set, ORD(Dfa_EolCh));
          DefTable_MakeIdentDef(Idents_MakeIdent(&string), (Tree_tTree)(ADDRESS)Tree0_mSet(set), 1, FALSE);
          Strings_ArrayToString((STRING)"STD", 3L, &string);
          DefTable_MakeStartDef(Idents_MakeIdent(&string), (SHORTCARD)(GenTabs_StartStateCount + 1));
          INC1(GenTabs_StartStateCount, 2);
          break;
        case 103:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 40;
          ScanGen_ScannerName = Idents_NoIdent;
          break;
        case 104:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 40;
          Strings_ArrayToString((STRING)"Scanner", 7L, &string);
          ScanGen_ScannerName = Idents_MakeIdent(&string);
          break;
        case 105:;
        case 56:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 40;
          ScanGen_ScannerName = yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.Ident;
          break;
        case 106:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 41;
          break;
        case 107:;
        case 74:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 41;
          ScanGen_Export = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text;
          ScanGen_ExportLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line;
          break;
        case 108:;
        case 57:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 41;
          ScanGen_Global = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text;
          ScanGen_GlobalLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line;
          break;
        case 109:;
        case 73:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 41;
          ScanGen_Local = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text;
          ScanGen_LocalLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line;
          break;
        case 110:;
        case 58:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 41;
          ScanGen_Begin = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text;
          ScanGen_BeginLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line;
          break;
        case 111:;
        case 59:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 41;
          ScanGen_Close = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text;
          ScanGen_CloseLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line;
          break;
        case 112:;
        case 76:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 41;
          ScanGen_Default = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text;
          ScanGen_DefaultLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line;
          break;
        case 113:;
        case 75:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 41;
          ScanGen_Eof = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text;
          ScanGen_EofLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line;
          break;
        case 114:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 42;
          ScanGen_InitScanGen();
          break;
        case 115:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 42;
          ScanGen_InitScanGen();
          break;
        case 116:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 43;
          break;
        case 117:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 43;
          break;
        case 118:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 44;
          Tree0_Tree0Root = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          Tree0_Tree0Root = AppendRule(Tree0_Tree0Root, Dfa_BlankCh, ScanGen_BlankText);
          Tree0_Tree0Root = AppendRule(Tree0_Tree0Root, Dfa_TabCh, ScanGen_TabText);
          Tree0_Tree0Root = AppendRule(Tree0_Tree0Root, Dfa_EolCh, ScanGen_EolText);
          break;
        case 119:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 46;
          break;
        case 120:;
        case 88:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 46;
          break;
        case 121:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 48;
          yySynAttribute.U_1.V_2.Tree = nNode;
          break;
        case 122:;
        case 95:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 48;
          yySynAttribute.U_1.V_2.Tree = Tree0_mList(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 123:;
        case 91:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 47;
          break;
        case 124:;
        case 90:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 47;
          break;
        case 125:;
        case 89:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 47;
          break;
        case 126:;
        case 77:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 51;
          Definition = DefTable_GetDef(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident);
          if (Definition == DefTable_NoDef) {
            DefTable_MakeStartDef(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident, (SHORTCARD)(GenTabs_StartStateCount + 1));
            INC1(GenTabs_StartStateCount, 2);
          } else {
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident, &string);
            Errors_ErrorMessageI((LONGCARD)IdentDefBefore, (LONGCARD)Error, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, (LONGCARD)C_1_String, ADR(string));
          }
          break;
        case 127:;
        case 92:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 53;
          Sets_MakeSet(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)GenTabs_StartStateCount);
          Sets_Include(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_2.Number);
          Sets_Include(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_2.Number + 1));
          break;
        case 128:;
        case 94:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 53;
          yySynAttribute.U_1.V_4.Set = yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.Set;
          Sets_Include(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Number);
          Sets_Include(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Number + 1));
          break;
        case 129:;
        case 93:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 53;
          yySynAttribute.U_1.V_4.Set = yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.Set;
          Sets_Include(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Number);
          Sets_Include(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Number + 1));
          break;
        case 130:;
        case 78:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 52;
          yySynAttribute.U_1.V_1.Scan.U_1.V_2.Number = 0;
          Definition = DefTable_GetDef(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident);
          if (Definition == DefTable_NoDef) {
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident, &string);
            Errors_ErrorMessageI((LONGCARD)IdentUndefined, (LONGCARD)Error, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, (LONGCARD)C_1_String, ADR(string));
          } else if (DefTable_GetKind(Definition) != DefTable_Start) {
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident, &string);
            Errors_ErrorMessageI((LONGCARD)ImproperUse, (LONGCARD)Error, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, (LONGCARD)C_1_String, ADR(string));
          } else {
            DefTable_GetStartDef(Definition, &Identifier, &yySynAttribute.U_1.V_1.Scan.U_1.V_2.Number);
          }
          break;
        case 131:;
        case 72:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 49;
          Definition = DefTable_GetDef(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident);
          if (Definition == DefTable_NoDef) {
            DefTable_MakeIdentDef(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident, (Tree_tTree)(ADDRESS)yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, 0, FALSE);
          } else {
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident, &string);
            Errors_ErrorMessageI((LONGCARD)IdentDefBefore, (LONGCARD)Error, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, (LONGCARD)C_1_String, ADR(string));
          }
          break;
        case 132:;
        case 83:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 50;
          INC(GenTabs_RuleCount);
          yySynAttribute.U_1.V_2.Tree = Tree0_mRule(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line, ScanGen_Position, GenTabs_RuleCount);
          break;
        case 133:;
        case 84:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 50;
          INC(GenTabs_RuleCount);
          yySynAttribute.U_1.V_2.Tree = Tree0_mRule(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.Text, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position.Line, ScanGen_NoPosition, GenTabs_RuleCount);
          break;
        case 134:;
        case 98:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 55;
          yySynAttribute.U_1.V_2.Tree = Tree0_mList(nNode, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 135:;
        case 96:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 55;
          yySynAttribute.U_1.V_2.Tree = Tree0_mList(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree);
          break;
        case 136:;
        case 97:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 56;
          if (yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree == nNode) {
            tree = yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree;
          } else {
            if (yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree == nNode) {
              tree = yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree;
            } else {
              tree = Tree0_mSequence(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree);
            }
          }
          if (yyAttributeStack->A[yyStackPtr + 2].U_1.V_3.IsLeftJust) {
            {
              SHORTCARD B_3 = 1, B_4 = (SHORTCARD)GenTabs_StartStateCount;

              if (B_3 <= B_4)
                for (Number = B_3, B_4 = FOR_LIMIT_UP(B_4, 2, MIN_SHORTCARD);; Number += 2) {
                  Sets_Exclude(&yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.Set, (Sets_tElement)Number);
                  if (Number >= B_4) break;
                }
            }
          }
          INC(GenTabs_PatternCount);
          yySynAttribute.U_1.V_2.Tree = Tree0_mPattern(yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.Set, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, tree, GenTabs_PatternCount, yyAttributeStack->A[yyStackPtr + 2].U_1.V_3.Position);
          break;
        case 137:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 57;
          Sets_MakeSet(&yySynAttribute.U_1.V_4.Set, (Sets_tElement)GenTabs_StartStateCount);
          Sets_Complement(&yySynAttribute.U_1.V_4.Set);
          Sets_Exclude(&yySynAttribute.U_1.V_4.Set, 0L);
          break;
        case 138:;
        case 80:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 57;
          yySynAttribute.U_1.V_4.Set = yyAttributeStack->A[yyStackPtr + 2].U_1.V_4.Set;
          break;
        case 139:;
        case 79:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 57;
          yySynAttribute.U_1.V_4.Set = yyAttributeStack->A[yyStackPtr + 3].U_1.V_4.Set;
          Sets_Complement(&yySynAttribute.U_1.V_4.Set);
          Sets_Exclude(&yySynAttribute.U_1.V_4.Set, 0L);
          break;
        case 140:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 58;
          yySynAttribute.U_1.V_3.IsLeftJust = FALSE;
          yySynAttribute.U_1.V_3.Position = Scanner_Attribute.Position;
          break;
        case 141:;
        case 81:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 58;
          yySynAttribute.U_1.V_3.IsLeftJust = TRUE;
          GenTabs_LeftJustUsed = TRUE;
          yySynAttribute.U_1.V_3.Position = Scanner_Attribute.Position;
          break;
        case 142:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 59;
          yySynAttribute.U_1.V_2.Tree = nNode;
          break;
        case 143:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 59;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 144:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 60;
          yySynAttribute.U_1.V_2.Tree = nNode;
          break;
        case 145:;
        case 82:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 60;
          yySynAttribute.U_1.V_2.Tree = EOLTree;
          break;
        case 146:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mAlternative(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree);
          break;
        case 147:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mSequence(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 148:;
        case 66:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mRepetition(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 149:;
        case 67:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mOption(Tree0_mRepetition(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree));
          break;
        case 150:;
        case 68:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mOption(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 151:;
        case 70:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = nNode;
          {
            SHORTCARD B_5 = 1, B_6 = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Number;

            if (B_5 <= B_6)
              for (Number = B_5;; Number += 1) {
                yySynAttribute.U_1.V_2.Tree = Tree0_mSequence(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yySynAttribute.U_1.V_2.Tree);
                if (Number >= B_6) break;
              }
          }
          break;
        case 152:;
        case 69:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = nNode;
          tree = Tree0_mOption(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          {
            SHORTCARD B_7 = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Number + 1, B_8 = yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_2.Number;

            if (B_7 <= B_8)
              for (Number = B_7;; Number += 1) {
                yySynAttribute.U_1.V_2.Tree = Tree0_mSequence(tree, yySynAttribute.U_1.V_2.Tree);
                if (Number >= B_8) break;
              }
          }
          {
            SHORTCARD B_9 = 1, B_10 = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Number;

            if (B_9 <= B_10)
              for (Number = B_9;; Number += 1) {
                yySynAttribute.U_1.V_2.Tree = Tree0_mSequence(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yySynAttribute.U_1.V_2.Tree);
                if (Number >= B_10) break;
              }
          }
          break;
        case 153:;
        case 71:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 154:;
        case 87:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mSet(yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.Set);
          break;
        case 155:;
        case 63:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mCh(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_4.Ch);
          break;
        case 156:;
        case 60:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 54;
          Definition = DefTable_GetDef(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident);
          if (Definition != DefTable_NoDef) {
            if (DefTable_GetKind(Definition) == DefTable_Ident) {
              DefTable_GetIdentDef(Definition, &Identifier, &tree1, &Number, &bool);
              yySynAttribute.U_1.V_2.Tree = (Tree0_tTree0)(ADDRESS)tree1;
            } else {
              Idents_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident, &string);
              Errors_ErrorMessageI((LONGCARD)ImproperUse, (LONGCARD)Error, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, (LONGCARD)C_1_String, ADR(string));
              yySynAttribute.U_1.V_2.Tree = nNode;
            }
          } else {
            stringref = Idents_GetStringRef(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident);
            yySynAttribute.U_1.V_2.Tree = Tree0_mString(stringref);
          }
          break;
        case 157:;
        case 62:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_2.Tree = Tree0_mString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_3.String);
          break;
        case 158:;
        case 61:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 54;
          Strings_IntToString((LONGINT)yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_2.Number, &string);
          yySynAttribute.U_1.V_2.Tree = Tree0_mString(StringMem_PutString(&string));
          break;
        case 159:;
        case 86:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 61;
          yySynAttribute.U_1.V_4.Set = yyAttributeStack->A[yyStackPtr + 2].U_1.V_4.Set;
          Sets_Complement(&yySynAttribute.U_1.V_4.Set);
          break;
        case 160:;
        case 65:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 61;
          yySynAttribute.U_1.V_4.Set = yyAttributeStack->A[yyStackPtr + 2].U_1.V_4.Set;
          break;
        case 161:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 62;
          Sets_MakeSet(&yySynAttribute.U_1.V_4.Set, ORD(Dfa_LastCh));
          break;
        case 162:;
        case 85:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 62;
          yySynAttribute.U_1.V_4.Set = yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.Set;
          Sets_Union(&yySynAttribute.U_1.V_4.Set, yyAttributeStack->A[yyStackPtr + 2].U_1.V_4.Set);
          Sets_ReleaseSet(&yyAttributeStack->A[yyStackPtr + 2].U_1.V_4.Set);
          break;
        case 163:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 63;
          Sets_MakeSet(&yySynAttribute.U_1.V_4.Set, ORD(Dfa_LastCh));
          Sets_Include(&yySynAttribute.U_1.V_4.Set, ORD(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_4.Ch));
          break;
        case 164:;
        case 64:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 63;
          Sets_MakeSet(&yySynAttribute.U_1.V_4.Set, ORD(Dfa_LastCh));
          {
            CHAR B_11 = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_4.Ch, B_12 = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Ch;

            if (B_11 <= B_12)
              for (ch = B_11;; ch += 1) {
                Sets_Include(&yySynAttribute.U_1.V_4.Set, ORD(ch));
                if (ch >= B_12) break;
              }
          }
          break;
        }
        yyNCombPtr = (yyNCombTypePtr)((LONGCARD)yyNBasePtr.A[yyStateStack->A[yyStackPtr]] + VAL(LONGCARD, yyNonterminal) * sizeof(yyNCombType));
        yyState = *yyNCombPtr;
        INC(yyStackPtr);
        yyAttributeStack->A[yyStackPtr] = yySynAttribute;
        if (yyState < yyFirstFinalState) {
          goto EXIT_3;
        }
      } EXIT_3:;
    } else {
      INC(yyStackPtr);
      yyAttributeStack->A[yyStackPtr].U_1.V_1.Scan = Scanner_Attribute;
      yyTerminal = VAL(yySymbolRange, Scanner_GetToken());
      yyIsRepairing = FALSE;
    }
  } EXIT_1:;
}

static void ErrorRecovery
# ifdef __STDC__
(yySymbolRange *Terminal, yyStackType StateStack, LONGINT StackSize, yyStackPtrType StackPtr)
# else
(Terminal, StateStack, StackSize, StackPtr)
yySymbolRange *Terminal;
yyStackType StateStack;
LONGINT StackSize;
yyStackPtrType StackPtr;
# endif
{
  BOOLEAN TokensSkipped;
  Sets_tSet ContinueSet;
  Sets_tSet RestartSet;
  yySymbolRange Token;
  struct S_18 TokenArray;
  Strings_tString TokenString;
  Strings_tString ContinueString;

  Parser_TokenName(*Terminal, TokenArray.A, 128L);
  Strings_ArrayToString(TokenArray.A, 128L, &TokenString);
  Errors_ErrorMessageI((LONGCARD)Errors_SyntaxError, (LONGCARD)Errors_Error, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(TokenString));
  Sets_MakeSet(&ContinueSet, (Sets_tElement)yyLastTerminal);
  ComputeContinuation(StateStack, StackSize, StackPtr, &ContinueSet);
  Strings_AssignEmpty(&ContinueString);
  {
    yySymbolRange B_13 = VAL(yySymbolRange, Sets_Minimum(&ContinueSet)), B_14 = VAL(yySymbolRange, Sets_Maximum(&ContinueSet));

    if (B_13 <= B_14)
      for (Token = B_13;; Token += 1) {
        if (Sets_IsElement(VAL(Sets_tElement, Token), &ContinueSet)) {
          Parser_TokenName(Token, TokenArray.A, 128L);
          Strings_ArrayToString(TokenArray.A, 128L, &TokenString);
          if (Strings_Length(&ContinueString) + Strings_Length(&TokenString) + 1 <= Strings_cMaxStrLength) {
            Strings_Concatenate(&ContinueString, &TokenString);
            Strings_Append(&ContinueString, ' ');
          }
        }
        if (Token >= B_14) break;
      }
  }
  Errors_ErrorMessageI((LONGCARD)Errors_ExpectedTokens, (LONGCARD)Errors_Information, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(ContinueString));
  Sets_ReleaseSet(&ContinueSet);
  Sets_MakeSet(&RestartSet, (Sets_tElement)yyLastTerminal);
  ComputeRestartPoints(StateStack, StackSize, StackPtr, &RestartSet);
  TokensSkipped = FALSE;
  while (!Sets_IsElement(VAL(Sets_tElement, *Terminal), &RestartSet)) {
    *Terminal = VAL(yySymbolRange, Scanner_GetToken());
    TokensSkipped = TRUE;
  }
  Sets_ReleaseSet(&RestartSet);
  if (TokensSkipped) {
    Errors_ErrorMessage((LONGCARD)Errors_RestartPoint, (LONGCARD)Errors_Information, Scanner_Attribute.Position);
  }
}

static void ComputeContinuation
# ifdef __STDC__
(yyStackType Stack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *ContinueSet)
# else
(Stack, StackSize, StackPtr, ContinueSet)
yyStackType Stack;
LONGINT StackSize;
yyStackPtrType StackPtr;
Sets_tSet *ContinueSet;
# endif
{
  yySymbolRange Terminal;

  Sets_AssignEmpty(ContinueSet);
  for (Terminal = yyFirstTerminal; Terminal <= yyLastTerminal; Terminal += 1) {
    if (IsContinuation(Terminal, Stack, StackSize, StackPtr)) {
      Sets_Include(ContinueSet, VAL(Sets_tElement, Terminal));
    }
  }
}

static BOOLEAN IsContinuation
# ifdef __STDC__
(yySymbolRange Terminal, yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr)
# else
(Terminal, ParseStack, StackSize, StackPtr)
yySymbolRange Terminal;
yyStackType ParseStack;
LONGINT StackSize;
yyStackPtrType StackPtr;
# endif
{
  yyStackPtrType State;
  yySymbolRange Nonterminal;
  yyStackType Stack;

  DynArray_MakeArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
  {
    yyStackPtrType B_15 = 0, B_16 = StackPtr;

    if (B_15 <= B_16)
      for (State = B_15;; State += 1) {
        Stack->A[State] = ParseStack->A[State];
        if (State >= B_16) break;
      }
  }
  State = Stack->A[StackPtr];
  for (;;) {
    Stack->A[StackPtr] = State;
    State = Next(State, Terminal);
    if (State == yyNoState) {
      DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      return FALSE;
    }
    if (State <= yyLastReadTermState) {
      DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      return TRUE;
    }
    for (;;) {
      if (State == yyStopState) {
        DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
        return TRUE;
      } else {
        DEC1(StackPtr, yyLength.A[State - 100]);
        Nonterminal = yyLeftHandSide.A[State - 100];
      }
      State = Next(Stack->A[StackPtr], Nonterminal);
      if (StackPtr >= VAL(yyStackPtrType, StackSize)) {
        DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      }
      INC(StackPtr);
      if (State < yyFirstFinalState) {
        goto EXIT_5;
      }
      State = yyFinalToProd.A[State - 56];
    } EXIT_5:;
  } EXIT_4:;
}

static void ComputeRestartPoints
# ifdef __STDC__
(yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *RestartSet)
# else
(ParseStack, StackSize, StackPtr, RestartSet)
yyStackType ParseStack;
LONGINT StackSize;
yyStackPtrType StackPtr;
Sets_tSet *RestartSet;
# endif
{
  yyStackType Stack;
  yyStackPtrType State;
  yySymbolRange Nonterminal;
  Sets_tSet ContinueSet;

  DynArray_MakeArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
  {
    yyStackPtrType B_17 = 0, B_18 = StackPtr;

    if (B_17 <= B_18)
      for (State = B_17;; State += 1) {
        Stack->A[State] = ParseStack->A[State];
        if (State >= B_18) break;
      }
  }
  Sets_MakeSet(&ContinueSet, (Sets_tElement)yyLastTerminal);
  Sets_AssignEmpty(RestartSet);
  State = Stack->A[StackPtr];
  for (;;) {
    if (StackPtr >= VAL(yyStackPtrType, StackSize)) {
      DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
    }
    Stack->A[StackPtr] = State;
    ComputeContinuation(Stack, StackSize, StackPtr, &ContinueSet);
    Sets_Union(RestartSet, ContinueSet);
    State = Next(State, yyContinuation.A[State]);
    if (State >= yyFirstFinalState) {
      if (State <= yyLastReadTermState) {
        INC(StackPtr);
        State = yyFinalToProd.A[State - 56];
      }
      for (;;) {
        if (State == yyStopState) {
          DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
          Sets_ReleaseSet(&ContinueSet);
          return;
        } else {
          DEC1(StackPtr, yyLength.A[State - 100]);
          Nonterminal = yyLeftHandSide.A[State - 100];
        }
        State = Next(Stack->A[StackPtr], Nonterminal);
        INC(StackPtr);
        if (State < yyFirstFinalState) {
          goto EXIT_7;
        }
        State = yyFinalToProd.A[State - 56];
      } EXIT_7:;
    } else {
      INC(StackPtr);
    }
  } EXIT_6:;
}

static yyStateRange Next
# ifdef __STDC__
(yyStateRange State, yySymbolRange Symbol)
# else
(State, Symbol)
yyStateRange State;
yySymbolRange Symbol;
# endif
{
  yyTCombTypePtr TCombPtr;
  yyNCombTypePtr NCombPtr;

  if (Symbol <= yyLastTerminal) {
    for (;;) {
      TCombPtr = (yyTCombTypePtr)((LONGCARD)yyTBasePtr.A[State] + VAL(LONGCARD, Symbol) * sizeof(yyTCombType));
      if (TCombPtr->Check != State) {
        State = yyDefault.A[State];
        if (State == yyNoState) {
          return yyNoState;
        }
      } else {
        return TCombPtr->Next;
      }
    } EXIT_8:;
  } else {
    NCombPtr = (yyNCombTypePtr)((LONGCARD)yyNBasePtr.A[State] + VAL(LONGCARD, Symbol) * sizeof(yyNCombType));
    return *NCombPtr;
  }
}

static void yyGetTables
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL BlockSize, j, n;
  yyStateRange State;
  struct S_19 TBase;
  struct S_20 NBase;

  BlockSize = 64000 / sizeof(yyTCombType);
  yyTableFile = OpenInput(Parser_ParsTabName.A, 129L);
  yyErrorCheck((LONGINT)Errors_OpenParseTable, yyTableFile);
  if (yyGetTable(ADR(TBase)) / sizeof(yyTCombRange) - 1 != yyLastReadState || yyGetTable(ADR(NBase)) / sizeof(yyNCombRange) - 1 != yyLastReadState || yyGetTable(ADR(yyDefault)) / sizeof(yyReadRange) - 1 != yyLastReadState || yyGetTable(ADR(yyNComb)) / sizeof(yyNCombType) != yyNTableMax - yyLastTerminal || yyGetTable(ADR(yyLength)) / sizeof(yyTableElmt) - 1 != yyLastReduceState - yyFirstReduceState || yyGetTable(ADR(yyLeftHandSide)) / sizeof(yySymbolRange) - 1 != yyLastReduceState - yyFirstReduceState || yyGetTable(ADR(yyContinuation)) / sizeof(yySymbolRange) - 1 != yyLastReadState || yyGetTable(ADR(yyFinalToProd)) / sizeof(yyReduceRange) - 1 != yyLastReadNontermState - yyFirstReadTermState) {
    Errors_ErrorMessage((LONGCARD)Errors_WrongParseTable, (LONGCARD)Errors_Fatal, Positions_NoPosition);
  }
  n = 0;
  j = 0;
  while (j <= yyTableMax) {
    INC1(n, yyGetTable(ADR(yyTComb.A[VAL(yyStateRange, j)])) / sizeof(yyTCombType));
    INC1(j, BlockSize);
  }
  if (n != yyTableMax + 1) {
    Errors_ErrorMessage((LONGCARD)Errors_WrongParseTable, (LONGCARD)Errors_Fatal, Positions_NoPosition);
  }
  Close(yyTableFile);
  for (State = 1; State <= yyLastReadState; State += 1) {
    yyTBasePtr.A[State] = (yyTCombTypePtr)ADR(yyTComb.A[TBase.A[State]]);
  }
  for (State = 1; State <= yyLastReadState; State += 1) {
    yyNBasePtr.A[State] = (yyNCombTypePtr)ADR(yyNComb.A[NBase.A[State] - 39]);
  }
}

static CARDINAL yyGetTable
# ifdef __STDC__
(ADDRESS Address)
# else
(Address)
ADDRESS Address;
# endif
{
  INTEGER N;
  yyTableElmt Length;
  CARDINAL LongLength;

  N = Read(yyTableFile, ADR(Length), (LONGINT)sizeof(yyTableElmt));
  yyErrorCheck((LONGINT)Errors_ReadParseTable, N);
  LongLength = VAL(CARDINAL, Length);
  N = Read(yyTableFile, Address, (LONGINT)LongLength);
  yyErrorCheck((LONGINT)Errors_ReadParseTable, N);
  return LongLength;
}

static void yyErrorCheck
# ifdef __STDC__
(INTEGER ErrorCode, INTEGER Info)
# else
(ErrorCode, Info)
INTEGER ErrorCode;
INTEGER Info;
# endif
{
  INTEGER ErrNo;

  if (Info < 0) {
    ErrNo = ErrNum();
    Errors_ErrorMessageI((LONGCARD)ErrorCode, (LONGCARD)Errors_Fatal, Positions_NoPosition, (LONGCARD)Errors_Integer, ADR(ErrNo));
  }
}

static void BeginParser
# ifdef __STDC__
()
# else
()
# endif
{
  nNode = Tree0_mNode();
  if (!yyIsInitialized) {
    yyIsInitialized = TRUE;
    yyGetTables();
  }
}

void Parser_CloseParser
# ifdef __STDC__
()
# else
()
# endif
{
}

void Parser__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Scanner__init();
    Positions__init();
    Errors__init();
    Strings__init();
    DynArray__init();
    Sets__init();
    System__init();
    Errors__init();
    Tree0__init();
    Tree__init();
    Sets__init();
    Strings__init();
    Lists__init();
    StringMem__init();
    Idents__init();
    DefTable__init();
    GenTabs__init();
    Dfa__init();
    ScanGen__init();

    yyIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
