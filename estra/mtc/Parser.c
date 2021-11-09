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

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

Tree_tTree Parser_AST;
struct Parser_1 Parser_ParsTabName;

typedef struct S_1 {
    union {
        struct {
            Scanner_tScanAttribute Scan;
        } V_1;
        struct {
            Tree_tTree Tree;
        } V_2;
        struct {
            struct S_4 {
                Tree_tTree first, last;
            } List;
        } V_3;
        struct {
            struct S_3 {
                Tree_tTree tree;
                Scanner_tScanAttribute scan;
            } Pair;
        } V_4;
    } U_1;
} tParsAttribute;
static Tree_tTree tree;
#define yyInitStackSize   100
#define yyNoState   0
#define yyFirstTerminal   0
#define yyLastTerminal   61
#define yyFirstSymbol   0
#define yyLastSymbol   90
#define yyTableMax   255
#define yyNTableMax   138
#define yyFirstReadState   1
#define yyLastReadState   91
#define yyFirstReadTermState   92
#define yyLastReadTermState   123
#define yyLastReadNontermState   134
#define yyFirstReduceState   135
#define yyLastReduceState   214
#define yyStartState   1
#define yyStopState   135
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
typedef struct S_5 {
    yyStateRange A[MAX_SHORTCARD + 1];
} *yyStackType;
typedef struct S_6 {
    tParsAttribute A[MAX_SHORTCARD + 1];
} *yyAttributeStackType;
static struct S_7 {
    yyTCombTypePtr A[yyLastReadState + 1];
} yyTBasePtr;
static struct S_8 {
    yyNCombTypePtr A[yyLastReadState + 1];
} yyNBasePtr;
static struct S_9 {
    yyReadRange A[yyLastReadState + 1];
} yyDefault;
static struct S_10 {
    yyTCombType A[yyTableMax + 1];
} yyTComb;
static struct S_11 {
    yyNCombType A[yyNTableMax - (yyLastTerminal + 1) + 1];
} yyNComb;
static struct S_12 {
    yyTableElmt A[yyLastReduceState - yyFirstReduceState + 1];
} yyLength;
static struct S_13 {
    yySymbolRange A[yyLastReduceState - yyFirstReduceState + 1];
} yyLeftHandSide;
static struct S_14 {
    yySymbolRange A[yyLastReadState + 1];
} yyContinuation;
static struct S_15 {
    yyReduceRange A[yyLastReadNontermState - yyFirstReadTermState + 1];
} yyFinalToProd;
static BOOLEAN yyIsInitialized;
static System_tFile yyTableFile;
static void Copy ARGS((CHAR Source[], LONGCARD , CHAR Target[], LONGCARD ));
struct S_19 {
    CHAR A[127 + 1];
};
static void ErrorRecovery ARGS((yySymbolRange *Terminal, yyStackType StateStack, LONGINT StackSize, yyStackPtrType StackPtr));
struct S_20 {
    CHAR A[127 + 1];
};
static void ComputeContinuation ARGS((yyStackType Stack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *ContinueSet));
static BOOLEAN IsContinuation ARGS((yySymbolRange Terminal, yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr));
static void ComputeRestartPoints ARGS((yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *RestartSet));
static yyStateRange Next ARGS((yyStateRange State, yySymbolRange Symbol));
static void yyGetTables ARGS(());
struct S_21 {
    yyTCombRange A[yyLastReadState + 1];
};
struct S_22 {
    yyNCombRange A[yyLastReadState + 1];
};
static CARDINAL yyGetTable ARGS((ADDRESS Address));
static void yyErrorCheck ARGS((INTEGER ErrorCode, INTEGER Info));
static void BeginParser ARGS(());


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
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 2:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)",", 1L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)"/", 1L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)":", 1L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)";", 1L, Name, O_3);
    break;
  case 8:;
    Copy((STRING)"=", 1L, Name, O_3);
    break;
  case 11:;
    Copy((STRING)"|", 1L, Name, O_3);
    break;
  case 12:;
    Copy((STRING)"{", 1L, Name, O_3);
    break;
  case 13:;
    Copy((STRING)"}", 1L, Name, O_3);
    break;
  case 15:;
    Copy((STRING)"->", 2L, Name, O_3);
    break;
  case 21:;
    Copy((STRING)"BEGIN", 5L, Name, O_3);
    break;
  case 22:;
    Copy((STRING)"CLOSE", 5L, Name, O_3);
    break;
  case 23:;
    Copy((STRING)"CONDITION", 9L, Name, O_3);
    break;
  case 24:;
    Copy((STRING)"COSTS", 5L, Name, O_3);
    break;
  case 25:;
    Copy((STRING)"DECLARE", 7L, Name, O_3);
    break;
  case 26:;
    Copy((STRING)"EXPORT", 6L, Name, O_3);
    break;
  case 27:;
    Copy((STRING)"GLOBAL", 6L, Name, O_3);
    break;
  case 28:;
    Copy((STRING)"GRAMMAR", 7L, Name, O_3);
    break;
  case 30:;
    Copy((STRING)"FUNCTION", 8L, Name, O_3);
    break;
  case 31:;
    Copy((STRING)"TRANSFORMATION", 14L, Name, O_3);
    break;
  case 41:;
    Copy((STRING)"Ident", 5L, Name, O_3);
    break;
  case 42:;
    Copy((STRING)"Number", 6L, Name, O_3);
    break;
  case 43:;
    Copy((STRING)"String", 6L, Name, O_3);
    break;
  case 51:;
    Copy((STRING)"{", 1L, Name, O_3);
    break;
  case 52:;
    Copy((STRING)"}", 1L, Name, O_3);
    break;
  case 53:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 54:;
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 55:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 56:;
    Copy((STRING)"ident", 5L, Name, O_3);
    break;
  case 57:;
    Copy((STRING)"string", 6L, Name, O_3);
    break;
  case 58:;
    Copy((STRING)"space", 5L, Name, O_3);
    break;
  case 59:;
    Copy((STRING)"comment", 7L, Name, O_3);
    break;
  case 60:;
    Copy((STRING)"rest", 4L, Name, O_3);
    break;
  case 61:;
    Copy((STRING)",", 1L, Name, O_3);
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
  struct S_19 yyTokenString;

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
            Scanner_ErrorAttribute(VAL(INTEGER, yyRepairToken), &yyRepairAttribute);
            Parser_TokenName(yyRepairToken, yyTokenString.A, 128L);
            Errors_ErrorMessageI((LONGCARD)Errors_TokenInserted, (LONGCARD)Errors_Repair, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(yyTokenString));
            if (yyState >= yyFirstFinalState) {
              yyState = yyFinalToProd.A[yyState - 92];
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
        case 135:;
          DynArray_ReleaseArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyTableElmt));
          DynArray_ReleaseArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
          return yyErrorCount;
          break;
        case 136:;
          DEC1(yyStackPtr, 8);
          yyNonterminal = 68;
          Parser_AST = Tree_mSpec(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 8].U_1.V_4.Pair.scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 8].U_1.V_4.Pair.scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 7].U_1.V_2.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 8].U_1.V_4.Pair.tree));
          break;
        case 137:;
        case 124:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 62;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 138:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 62;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdEnd(Positions_NoPosition);
          break;
        case 139:;
        case 125:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 63;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 140:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 63;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdEnd(Positions_NoPosition);
          break;
        case 141:;
        case 126:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 64;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 142:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 64;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdEnd(Positions_NoPosition);
          break;
        case 143:;
        case 127:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 65;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 144:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 65;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdEnd(Positions_NoPosition);
          break;
        case 145:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 66;
          yySynAttribute.U_1.V_4.Pair.scan.U_1.V_1.ident = yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident;
          yySynAttribute.U_1.V_4.Pair.scan.Position = yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position;
          yySynAttribute.U_1.V_4.Pair.tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree);
          break;
        case 146:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 70;
          yySynAttribute.U_1.V_2.Tree = Tree_mClass0();
          break;
        case 147:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 70;
          yySynAttribute.U_1.V_2.Tree = Tree_mClass(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, TRUE);
          break;
        case 148:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 70;
          yySynAttribute.U_1.V_2.Tree = Tree_mClass(Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, TRUE);
          break;
        case 149:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 71;
          yySynAttribute.U_1.V_2.Tree = Tree_mNode0();
          break;
        case 150:;
        case 109:;
          DEC1(yyStackPtr, 8);
          yyNonterminal = 71;
          yySynAttribute.U_1.V_2.Tree = Tree_mNode(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 7].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, TRUE);
          break;
        case 151:;
        case 107:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 71;
          yySynAttribute.U_1.V_2.Tree = Tree_mNode(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, TRUE);
          break;
        case 152:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 73;
          yySynAttribute.U_1.V_2.Tree = Tree_mSon0();
          break;
        case 153:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 73;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 154:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 74;
          yySynAttribute.U_1.V_2.Tree = Tree_mSon(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_mSon0(), TRUE);
          break;
        case 155:;
        case 106:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 74;
          yySynAttribute.U_1.V_2.Tree = Tree_mSon(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Tree_mSon0(), TRUE);
          break;
        case 156:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 74;
          yySynAttribute.U_1.V_2.Tree = Tree_mSon(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, TRUE);
          break;
        case 157:;
        case 108:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 74;
          yySynAttribute.U_1.V_2.Tree = Tree_mSon(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, TRUE);
          break;
        case 158:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_2.Tree = Tree_mAttribute0();
          break;
        case 159:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 160:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 76;
          tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.first;
          for (;;) {
            tree->U_1.V_16.Attribute.type = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident;
            tree->U_1.V_16.Attribute.typos = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
            if (tree == yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.last) {
              goto EXIT_4;
            }
            tree = tree->U_1.V_16.Attribute.attributes;
          } EXIT_4:;
          yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.last->U_1.V_16.Attribute.attributes = Tree_mAttribute0();
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.first;
          break;
        case 161:;
        case 115:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 76;
          tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.first;
          for (;;) {
            tree->U_1.V_16.Attribute.mod = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident;
            tree->U_1.V_16.Attribute.mopos = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
            tree->U_1.V_16.Attribute.type = yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_1.ident;
            tree->U_1.V_16.Attribute.typos = yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.Position;
            if (tree == yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.last) {
              goto EXIT_5;
            }
            tree = tree->U_1.V_16.Attribute.attributes;
          } EXIT_5:;
          yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.last->U_1.V_16.Attribute.attributes = Tree_mAttribute0();
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.first;
          break;
        case 162:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 76;
          tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.first;
          for (;;) {
            tree->U_1.V_16.Attribute.type = yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_1.ident;
            tree->U_1.V_16.Attribute.typos = yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.Position;
            if (tree == yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.last) {
              goto EXIT_6;
            }
            tree = tree->U_1.V_16.Attribute.attributes;
          } EXIT_6:;
          yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.last->U_1.V_16.Attribute.attributes = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.first;
          break;
        case 163:;
        case 114:;
          DEC1(yyStackPtr, 7);
          yyNonterminal = 76;
          tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.first;
          for (;;) {
            tree->U_1.V_16.Attribute.mod = yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_1.ident;
            tree->U_1.V_16.Attribute.mopos = yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.Position;
            tree->U_1.V_16.Attribute.type = yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.U_1.V_1.ident;
            tree->U_1.V_16.Attribute.typos = yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.Position;
            if (tree == yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.last) {
              goto EXIT_7;
            }
            tree = tree->U_1.V_16.Attribute.attributes;
          } EXIT_7:;
          yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.last->U_1.V_16.Attribute.attributes = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_3.List.first;
          break;
        case 164:;
        case 111:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 77;
          tree = Tree_mAttribute(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Scanner_NoIdent, Positions_NoPosition, Scanner_NoIdent, Positions_NoPosition, (Tree_tTree)Tree_NoTree);
          yySynAttribute.U_1.V_3.List.first = tree;
          yySynAttribute.U_1.V_3.List.last = tree;
          break;
        case 165:;
        case 113:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 77;
          yySynAttribute.U_1.V_3.List.first = Tree_mAttribute(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Scanner_NoIdent, Positions_NoPosition, Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.first);
          yySynAttribute.U_1.V_3.List.last = yyAttributeStack->A[yyStackPtr + 1].U_1.V_3.List.last;
          break;
        case 166:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_2.Tree = Tree_mFunction0();
          break;
        case 167:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 67;
          yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree->U_1.V_19.Function.name = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident;
          yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree->U_1.V_19.Function.napos = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree->U_1.V_19.Function.domain = yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree;
          yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree->U_1.V_19.Function.directives = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree);
          yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree->U_1.V_19.Function.functions = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree;
          break;
        case 168:;
        case 112:;
          DEC1(yyStackPtr, 7);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_2.Tree = Tree_mFunction(Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, Tree_mType(yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.Position), (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree);
          break;
        case 169:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_2.Tree = Tree_mFunction(Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, Tree_mType(Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.Position), (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree);
          break;
        case 170:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_2.Tree = Tree_mFunction(Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, Tree_mNoResult(), (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree);
          break;
        case 171:;
        case 110:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_2.Tree = Tree_mFunction(Scanner_NoIdent, Positions_NoPosition, Tree_mAttribute0(), Tree_mAttribute0(), Tree_mType(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.Position), (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree);
          break;
        case 172:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_2.Tree = Tree_mFunction(Scanner_NoIdent, Positions_NoPosition, Tree_mAttribute0(), Tree_mAttribute0(), Tree_mType(Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position), (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree);
          break;
        case 173:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_2.Tree = Tree_mFunction(Scanner_NoIdent, Positions_NoPosition, Tree_mAttribute0(), Tree_mAttribute0(), Tree_mNoResult(), (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree, (Tree_tTree)Tree_NoTree);
          break;
        case 174:;
        case 116:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 79;
          yySynAttribute.U_1.V_2.Tree = Tree_mIdent0();
          break;
        case 175:;
        case 119:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 79;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 176:;
        case 117:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 81;
          yySynAttribute.U_1.V_2.Tree = Tree_mIdent(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_mIdent0());
          break;
        case 177:;
        case 118:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 81;
          yySynAttribute.U_1.V_2.Tree = Tree_mIdent(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 178:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 80;
          yySynAttribute.U_1.V_2.Tree = Tree_mDirective0();
          break;
        case 179:;
        case 134:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 80;
          yySynAttribute.U_1.V_2.Tree = Tree_mDirective(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, TRUE);
          break;
        case 180:;
        case 121:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree, TRUE);
          break;
        case 181:;
        case 120:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, TRUE);
          break;
        case 182:;
        case 122:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree, TRUE);
          break;
        case 183:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern1(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, TRUE);
          break;
        case 184:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern1(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, TRUE);
          break;
        case 185:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern1(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Scanner_NoIdent, Positions_NoPosition, TRUE);
          break;
        case 186:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern1(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Scanner_NoIdent, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, TRUE);
          break;
        case 187:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Tree = Tree_mPattern1(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Scanner_NoIdent, Positions_NoPosition, Scanner_NoIdent, Positions_NoPosition, TRUE);
          break;
        case 188:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 87;
          yySynAttribute.U_1.V_2.Tree = Tree_mPatterns0();
          break;
        case 189:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 87;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 190:;
        case 128:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 88;
          yySynAttribute.U_1.V_2.Tree = Tree_mPatterns(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Tree_mPatterns0());
          break;
        case 191:;
        case 129:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 88;
          yySynAttribute.U_1.V_2.Tree = Tree_mPatterns(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 192:;
        case 104:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 72;
          yySynAttribute.U_1.V_1.Scan = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan;
          break;
        case 193:;
        case 105:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 72;
          yySynAttribute.U_1.V_1.Scan = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan;
          break;
        case 194:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_2.Tree = Tree_mCondD();
          break;
        case 195:;
        case 130:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_2.Tree = Tree_mCondF(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 196:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_2.Tree = Tree_mCostD();
          break;
        case 197:;
        case 123:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_2.Tree = Tree_mCostN(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_3.val, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position);
          break;
        case 198:;
        case 131:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_2.Tree = Tree_mCostF(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 199:;
        case 132:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 85;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 200:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 85;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdEnd(Positions_NoPosition);
          break;
        case 201:;
        case 133:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 86;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          break;
        case 202:;
        case 92:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 69;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 203:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdEnd(Positions_NoPosition);
          break;
        case 204:;
        case 99:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdStr(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 205:;
        case 98:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdId(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 206:;
        case 95:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdDot(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 207:;
        case 96:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdLPar(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 208:;
        case 97:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdRPar(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 209:;
        case 93:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdLBra(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 210:;
        case 94:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdRBra(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 211:;
        case 100:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdSpa(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.ref, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 212:;
        case 101:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdCom(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.ref, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 213:;
        case 102:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdRst(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.ref, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 214:;
        case 103:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_mCdComma(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
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
  struct S_20 TokenArray;
  Strings_tString TokenString;
  Strings_tString ContinueString;

  Parser_TokenName(*Terminal, TokenArray.A, 128L);
  Strings_ArrayToString(TokenArray.A, 128L, &TokenString);
  Errors_ErrorMessageI((LONGCARD)Errors_SyntaxError, (LONGCARD)Errors_Error, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(TokenString));
  Sets_MakeSet(&ContinueSet, (Sets_tElement)yyLastTerminal);
  ComputeContinuation(StateStack, StackSize, StackPtr, &ContinueSet);
  Strings_AssignEmpty(&ContinueString);
  {
    yySymbolRange B_3 = VAL(yySymbolRange, Sets_Minimum(&ContinueSet)), B_4 = VAL(yySymbolRange, Sets_Maximum(&ContinueSet));

    if (B_3 <= B_4)
      for (Token = B_3;; Token += 1) {
        if (Sets_IsElement(VAL(Sets_tElement, Token), &ContinueSet)) {
          Parser_TokenName(Token, TokenArray.A, 128L);
          Strings_ArrayToString(TokenArray.A, 128L, &TokenString);
          if (Strings_Length(&ContinueString) + Strings_Length(&TokenString) + 1 <= Strings_cMaxStrLength) {
            Strings_Concatenate(&ContinueString, &TokenString);
            Strings_Append(&ContinueString, ' ');
          }
        }
        if (Token >= B_4) break;
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
    yyStackPtrType B_5 = 0, B_6 = StackPtr;

    if (B_5 <= B_6)
      for (State = B_5;; State += 1) {
        Stack->A[State] = ParseStack->A[State];
        if (State >= B_6) break;
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
        DEC1(StackPtr, yyLength.A[State - 135]);
        Nonterminal = yyLeftHandSide.A[State - 135];
      }
      State = Next(Stack->A[StackPtr], Nonterminal);
      if (StackPtr >= VAL(yyStackPtrType, StackSize)) {
        DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      }
      INC(StackPtr);
      if (State < yyFirstFinalState) {
        goto EXIT_9;
      }
      State = yyFinalToProd.A[State - 92];
    } EXIT_9:;
  } EXIT_8:;
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
    yyStackPtrType B_7 = 0, B_8 = StackPtr;

    if (B_7 <= B_8)
      for (State = B_7;; State += 1) {
        Stack->A[State] = ParseStack->A[State];
        if (State >= B_8) break;
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
        State = yyFinalToProd.A[State - 92];
      }
      for (;;) {
        if (State == yyStopState) {
          DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
          Sets_ReleaseSet(&ContinueSet);
          return;
        } else {
          DEC1(StackPtr, yyLength.A[State - 135]);
          Nonterminal = yyLeftHandSide.A[State - 135];
        }
        State = Next(Stack->A[StackPtr], Nonterminal);
        INC(StackPtr);
        if (State < yyFirstFinalState) {
          goto EXIT_11;
        }
        State = yyFinalToProd.A[State - 92];
      } EXIT_11:;
    } else {
      INC(StackPtr);
    }
  } EXIT_10:;
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
    } EXIT_12:;
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
  struct S_21 TBase;
  struct S_22 NBase;

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
    yyNBasePtr.A[State] = (yyNCombTypePtr)ADR(yyNComb.A[NBase.A[State] - 62]);
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
  Scanner_BeginScanner();
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
  Scanner_CloseScanner();
}

void Parser__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Tree__init();
    Scanner__init();
    Positions__init();
    Errors__init();
    Strings__init();
    DynArray__init();
    Sets__init();
    System__init();
    Scanner__init();
    Tree__init();
    Positions__init();
    Tree__init();

    yyIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
