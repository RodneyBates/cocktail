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

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

struct Parser_1 Parser_ParsTabName;

typedef struct S_1 {
    union {
        struct {
            Scanner_tScanAttribute Scan;
            BITSET Properties;
        } V_1;
        struct {
            Tree_tTree Tree;
            Idents_tIdent Ident;
        } V_2;
    } U_1;
} tParsAttribute;
static BITSET Properties, InitProperties;
static Strings_tString String1, String2;
static INTEGER ClassCount;
static CARDINAL i;
static Idents_tIdent ClassIdent, ModuleIdent;
static Idents_tIdent ParserName, TreeName, EvalName;
static Tree_tTree mCodes ARGS(());
static void UpdateName ARGS((Idents_tIdent *Name, Idents_tIdent Ident));
#define yyInitStackSize   100
#define yyNoState   0
#define yyFirstTerminal   0
#define yyLastTerminal   81
#define yyFirstSymbol   0
#define yyLastSymbol   122
#define yyTableMax   1249
#define yyNTableMax   247
#define yyFirstReadState   1
#define yyLastReadState   186
#define yyFirstReadTermState   187
#define yyLastReadTermState   240
#define yyLastReadNontermState   246
#define yyFirstReduceState   247
#define yyLastReduceState   372
#define yyStartState   1
#define yyStopState   247
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


static Tree_tTree mCodes
# ifdef __STDC__
()
# else
()
# endif
{
  Tree_tTree t;

  t = Tree_MakeTree(Tree_Codes);
  {
    register Tree_yCodes *W_1 = &t->U_1.V_12.Codes;

    Texts_MakeText(&W_1->Export);
    Texts_MakeText(&W_1->Import);
    Texts_MakeText(&W_1->Global);
    Texts_MakeText(&W_1->SpecWith);
    Texts_MakeText(&W_1->BodyWith);
    Texts_MakeText(&W_1->Local);
    Texts_MakeText(&W_1->Begin);
    Texts_MakeText(&W_1->Close);
    W_1->ExportLine = Positions_NoPosition;
    W_1->ImportLine = Positions_NoPosition;
    W_1->GlobalLine = Positions_NoPosition;
    W_1->SpecWithLine = Positions_NoPosition;
    W_1->BodyWithLine = Positions_NoPosition;
    W_1->LocalLine = Positions_NoPosition;
    W_1->BeginLine = Positions_NoPosition;
    W_1->CloseLine = Positions_NoPosition;
  }
  return t;
}

static void UpdateName
# ifdef __STDC__
(Idents_tIdent *Name, Idents_tIdent Ident)
# else
(Name, Ident)
Idents_tIdent *Name;
Idents_tIdent Ident;
# endif
{
  if (*Name == Idents_NoIdent) {
    *Name = Ident;
  }
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
    Copy((STRING)"Integer", 7L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)"String", 6L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)"TargetCode", 10L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)"Code", 4L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)"FUNCTION", 8L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)"WhiteSpace", 10L, Name, O_3);
    break;
  case 10:;
    Copy((STRING)"BEGIN", 5L, Name, O_3);
    break;
  case 11:;
    Copy((STRING)"CLOSE", 5L, Name, O_3);
    break;
  case 12:;
    Copy((STRING)"DECLARE", 7L, Name, O_3);
    break;
  case 13:;
    Copy((STRING)"END", 3L, Name, O_3);
    break;
  case 14:;
    Copy((STRING)"EVAL", 4L, Name, O_3);
    break;
  case 15:;
    Copy((STRING)"EXPORT", 6L, Name, O_3);
    break;
  case 16:;
    Copy((STRING)"GLOBAL", 6L, Name, O_3);
    break;
  case 17:;
    Copy((STRING)"VIRTUAL", 7L, Name, O_3);
    break;
  case 18:;
    Copy((STRING)"LOCAL", 5L, Name, O_3);
    break;
  case 19:;
    Copy((STRING)"MODULE", 6L, Name, O_3);
    break;
  case 20:;
    Copy((STRING)"STACK", 5L, Name, O_3);
    break;
  case 21:;
    Copy((STRING)"REVERSE", 7L, Name, O_3);
    break;
  case 22:;
    Copy((STRING)"RULE", 4L, Name, O_3);
    break;
  case 23:;
    Copy((STRING)"TREE", 4L, Name, O_3);
    break;
  case 24:;
    Copy((STRING)"AFTER", 5L, Name, O_3);
    break;
  case 25:;
    Copy((STRING)"BEFORE", 6L, Name, O_3);
    break;
  case 26:;
    Copy((STRING)"CHECK", 5L, Name, O_3);
    break;
  case 27:;
    Copy((STRING)"THREAD", 6L, Name, O_3);
    break;
  case 28:;
    Copy((STRING)"DEMAND", 6L, Name, O_3);
    break;
  case 30:;
    Copy((STRING)"IMPORT", 6L, Name, O_3);
    break;
  case 31:;
    Copy((STRING)"INPUT", 5L, Name, O_3);
    break;
  case 32:;
    Copy((STRING)"OUTPUT", 6L, Name, O_3);
    break;
  case 33:;
    Copy((STRING)"SYNTHESIZED", 11L, Name, O_3);
    break;
  case 34:;
    Copy((STRING)"INHERITED", 9L, Name, O_3);
    break;
  case 35:;
    Copy((STRING)"PARSER", 6L, Name, O_3);
    break;
  case 36:;
    Copy((STRING)"PREC", 4L, Name, O_3);
    break;
  case 37:;
    Copy((STRING)"LEFT", 4L, Name, O_3);
    break;
  case 38:;
    Copy((STRING)"RIGHT", 5L, Name, O_3);
    break;
  case 39:;
    Copy((STRING)"NONE", 4L, Name, O_3);
    break;
  case 40:;
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 41:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 42:;
    Copy((STRING)"[", 1L, Name, O_3);
    break;
  case 43:;
    Copy((STRING)"]", 1L, Name, O_3);
    break;
  case 44:;
    Copy((STRING)"{", 1L, Name, O_3);
    break;
  case 45:;
    Copy((STRING)"}", 1L, Name, O_3);
    break;
  case 46:;
    Copy((STRING)",", 1L, Name, O_3);
    break;
  case 47:;
    Copy((STRING)";", 1L, Name, O_3);
    break;
  case 48:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 49:;
    Copy((STRING)":", 1L, Name, O_3);
    break;
  case 50:;
    Copy((STRING)"=", 1L, Name, O_3);
    break;
  case 52:;
    Copy((STRING)":=", 2L, Name, O_3);
    break;
  case 57:;
    Copy((STRING)"<", 1L, Name, O_3);
    break;
  case 58:;
    Copy((STRING)">", 1L, Name, O_3);
    break;
  case 59:;
    Copy((STRING)"->", 2L, Name, O_3);
    break;
  case 60:;
    Copy((STRING)":-", 2L, Name, O_3);
    break;
  case 61:;
    Copy((STRING)"=>", 2L, Name, O_3);
    break;
  case 62:;
    Copy((STRING)"<-", 2L, Name, O_3);
    break;
  case 70:;
    Copy((STRING)"PROPERTY", 8L, Name, O_3);
    break;
  case 71:;
    Copy((STRING)"FOR", 3L, Name, O_3);
    break;
  case 72:;
    Copy((STRING)"IGNORE", 6L, Name, O_3);
    break;
  case 74:;
    Copy((STRING)"SELECT", 6L, Name, O_3);
    break;
  case 75:;
    Copy((STRING)"SUBUNIT", 7L, Name, O_3);
    break;
  case 76:;
    Copy((STRING)"REMOTE", 6L, Name, O_3);
    break;
  case 77:;
    Copy((STRING)"SCANNER", 7L, Name, O_3);
    break;
  case 78:;
    Copy((STRING)"VIEW", 4L, Name, O_3);
    break;
  case 79:;
    Copy((STRING)"SPECWITH", 8L, Name, O_3);
    break;
  case 80:;
    Copy((STRING)"BODYWITH", 8L, Name, O_3);
    break;
  case 81:;
    Copy((STRING)"LINK", 4L, Name, O_3);
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
              yyState = yyFinalToProd.A[yyState - 187];
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
        case 247:;
          DynArray_ReleaseArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyTableElmt));
          DynArray_ReleaseArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
          return yyErrorCount;
          break;
        case 248:;
          DEC1(yyStackPtr, 9);
          yyNonterminal = 91;
          Tree_TreeRoot = Tree_mAg(Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Ident, ParserName, yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree, TreeName, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree, EvalName, yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 7].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 8].U_1.V_2.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 9].U_1.V_2.Tree));
          break;
        case 249:;
          DEC1(yyStackPtr, 14);
          yyNonterminal = 91;
          Tree_TreeRoot = Tree_mAg(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Ident, ParserName, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree, TreeName, yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree, EvalName, yyAttributeStack->A[yyStackPtr + 7].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 8].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 9].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 10].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 11].U_1.V_2.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 14].U_1.V_2.Tree));
          break;
        case 250:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 92;
          ModuleIdent = yyAttributeStack->A[yyStackPtr + 0].U_1.V_1.Scan.U_1.V_2.Ident;
          break;
        case 251:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Ident = Idents_NoIdent;
          break;
        case 252:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 82;
          Strings_ArrayToString((STRING)"Scanner", 7L, &String1);
          yySynAttribute.U_1.V_2.Ident = Idents_MakeIdent(&String1);
          break;
        case 253:;
        case 241:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_2.Ident = yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident;
          break;
        case 254:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_2.Tree = mCodes();
          break;
        case 255:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 256:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree;
          UpdateName(&ParserName, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident);
          break;
        case 257:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_2.Tree = mCodes();
          break;
        case 258:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree;
          break;
        case 259:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree;
          UpdateName(&TreeName, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident);
          break;
        case 260:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 85;
          yySynAttribute.U_1.V_2.Tree = mCodes();
          break;
        case 261:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 85;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 262:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 85;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree;
          UpdateName(&EvalName, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident);
          break;
        case 263:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = mCodes();
          break;
        case 264:;
        case 195:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.SpecWith = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.SpecWithLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 265:;
        case 196:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.BodyWith = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.BodyWithLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 266:;
        case 191:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.Export = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.ExportLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 267:;
        case 194:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.Import = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.ImportLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 268:;
        case 192:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.Global = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.GlobalLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 269:;
        case 193:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.Local = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.LocalLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 270:;
        case 189:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.Begin = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.BeginLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 271:;
        case 190:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 94;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.Close = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.Text;
          yySynAttribute.U_1.V_2.Tree->U_1.V_12.Codes.CloseLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 272:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 95;
          break;
        case 273:;
        case 242:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 95;
          UpdateName(&Tree_SubUnit, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident);
          break;
        case 274:;
        case 243:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 95;
          UpdateName(&Tree_ViewName, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident);
          break;
        case 275:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 86;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoPrec;
          break;
        case 276:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 86;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 277:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 96;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoPrec;
          break;
        case 278:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 96;
          yySynAttribute.U_1.V_2.Tree = Tree_mLeftAssoc(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 279:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 96;
          yySynAttribute.U_1.V_2.Tree = Tree_mRightAssoc(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 280:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 96;
          yySynAttribute.U_1.V_2.Tree = Tree_mNonAssoc(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 281:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 87;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 282:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 98;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoProp;
          break;
        case 283:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 98;
          yySynAttribute.U_1.V_2.Tree = Tree_mProp(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Properties, Tree_mName(ModuleIdent, Positions_NoPosition, Tree_nNoName), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          InitProperties = 0X0L;
          break;
        case 284:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 98;
          yySynAttribute.U_1.V_2.Tree = Tree_mProp(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Properties, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          InitProperties = 0X0L;
          break;
        case 285:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 98;
          yySynAttribute.U_1.V_2.Tree = Tree_mSelect(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          InitProperties = 0X0L;
          break;
        case 286:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 88;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoDecl;
          break;
        case 287:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 88;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 288:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 100;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoDecl;
          break;
        case 289:;
        case 232:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 100;
          yySynAttribute.U_1.V_2.Tree = Tree_mDecl(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree), SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Explicit), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 290:;
        case 230:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 100;
          yySynAttribute.U_1.V_2.Tree = Tree_mDecl(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree), SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Explicit), yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 291:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 103;
          Properties = InitProperties;
          break;
        case 292:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 101;
          Properties = InitProperties;
          break;
        case 293:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 97;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoName;
          break;
        case 294:;
        case 244:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 97;
          yySynAttribute.U_1.V_2.Tree = Tree_mName(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 295:;
        case 199:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 97;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          break;
        case 296:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoClass;
          break;
        case 297:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 89;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 298:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 105;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoClass;
          break;
        case 299:;
        case 235:;
          DEC1(yyStackPtr, 8);
          yyNonterminal = 105;
          INC(ClassCount);
          Strings_IntToString(ClassCount, &String2);
          Strings_ArrayToString((STRING)"yy", 2L, &String1);
          Strings_Concatenate(&String1, &String2);
          ClassIdent = Idents_MakeIdent(&String1);
          yySynAttribute.U_1.V_2.Tree = Tree_mClass(ClassIdent, SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Explicit), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 7].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, ClassIdent, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, 0, yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 300:;
        case 238:;
          DEC1(yyStackPtr, 9);
          yyNonterminal = 105;
          yySynAttribute.U_1.V_2.Tree = Tree_mClass(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, SET_ELEM(Tree_Nonterminal) | SET_ELEM(Tree_Explicit) | yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Properties, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 8].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, 0, yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree);
          break;
        case 301:;
        case 237:;
          DEC1(yyStackPtr, 11);
          yyNonterminal = 105;
          yySynAttribute.U_1.V_2.Tree = Tree_mClass(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Explicit) | yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Properties | yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Properties, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 8].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 10].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, (SHORTCARD)yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.U_1.V_3.Integer, yyAttributeStack->A[yyStackPtr + 9].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree);
          break;
        case 302:;
        case 236:;
          DEC1(yyStackPtr, 12);
          yyNonterminal = 105;
          yySynAttribute.U_1.V_2.Tree = Tree_mClass(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, SET_ELEM(Tree_Terminal) | SET_ELEM(Tree_Explicit) | SET_ELEM(Tree_HasSelector) | yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Properties | yyAttributeStack->A[yyStackPtr + 8].U_1.V_1.Properties, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 9].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 11].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, (SHORTCARD)yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.U_1.V_3.Integer, yyAttributeStack->A[yyStackPtr + 10].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree);
          break;
        case 303:;
        case 239:;
          DEC1(yyStackPtr, 9);
          yyNonterminal = 105;
          yySynAttribute.U_1.V_2.Tree = Tree_mClass(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, SET_ELEM(Tree_Abstract) | SET_ELEM(Tree_Explicit) | yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Properties, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 8].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, 0, yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree);
          break;
        case 304:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 115;
          Properties = InitProperties;
          break;
        case 305:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 114;
          Properties = InitProperties;
          break;
        case 306:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 111;
          Properties = InitProperties;
          break;
        case 307:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 110;
          Properties = InitProperties;
          break;
        case 308:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 107;
          Properties = InitProperties;
          break;
        case 309:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 106;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoName;
          break;
        case 310:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 106;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 311:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 112;
          yySynAttribute.U_1.V_1.Scan.U_1.V_3.Integer = 0;
          break;
        case 312:;
        case 233:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 112;
          yySynAttribute.U_1.V_1.Scan.U_1.V_3.Integer = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_3.Integer;
          break;
        case 313:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 108;
          yySynAttribute.U_1.V_1.Scan.U_1.V_2.Ident = Idents_NoIdent;
          break;
        case 314:;
        case 246:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 108;
          yySynAttribute.U_1.V_1.Scan.U_1.V_2.Ident = yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident;
          break;
        case 315:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 109;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoClass;
          break;
        case 316:;
        case 234:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 109;
          yySynAttribute.U_1.V_2.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree);
          break;
        case 317:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 102;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoAttribute;
          break;
        case 318:;
        case 231:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 102;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          Properties = 0X0L;
          break;
        case 319:;
        case 215:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 102;
          if (IN(Tree_Thread, yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Properties)) {
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, &String1);
            Strings_ArrayToString((STRING)"In", 2L, &String2);
            Strings_Concatenate(&String1, &String2);
            yySynAttribute.U_1.V_2.Tree = Tree_mAttribute(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Idents_MakeIdent(&String1), Tree_iInteger, Properties | yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Properties | (SET_ELEM(Tree_Inherited)), yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, &String1);
            Strings_ArrayToString((STRING)"Out", 3L, &String2);
            Strings_Concatenate(&String1, &String2);
            yySynAttribute.U_1.V_2.Tree = Tree_mAttribute(yySynAttribute.U_1.V_2.Tree, Idents_MakeIdent(&String1), Tree_iInteger, Properties | yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Properties | (SET_ELEM(Tree_Synthesized)), yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
          } else {
            yySynAttribute.U_1.V_2.Tree = Tree_mAttribute(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, Tree_iInteger, Properties | yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Properties, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
          }
          break;
        case 320:;
        case 214:;
          DEC1(yyStackPtr, 7);
          yyNonterminal = 102;
          if (IN(Tree_Thread, yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Properties)) {
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, &String1);
            Strings_ArrayToString((STRING)"In", 2L, &String2);
            Strings_Concatenate(&String1, &String2);
            yySynAttribute.U_1.V_2.Tree = Tree_mAttribute(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Idents_MakeIdent(&String1), yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_2.Ident, Properties | yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Properties | (SET_ELEM(Tree_Inherited)), yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
            Idents_GetString(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, &String1);
            Strings_ArrayToString((STRING)"Out", 3L, &String2);
            Strings_Concatenate(&String1, &String2);
            yySynAttribute.U_1.V_2.Tree = Tree_mAttribute(yySynAttribute.U_1.V_2.Tree, Idents_MakeIdent(&String1), yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_2.Ident, Properties | yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Properties | (SET_ELEM(Tree_Synthesized)), yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
          } else {
            yySynAttribute.U_1.V_2.Tree = Tree_mAttribute(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_2.Ident, Properties | yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Properties, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
          }
          break;
        case 321:;
        case 213:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 102;
          yySynAttribute.U_1.V_2.Tree = Tree_mChild(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, Properties | yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Properties, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
          break;
        case 322:;
        case 210:;
          DEC1(yyStackPtr, 7);
          yyNonterminal = 102;
          yySynAttribute.U_1.V_2.Tree = Tree_mChild(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Scan.U_1.V_2.Ident, Properties | yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Properties, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
          break;
        case 323:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 102;
          yySynAttribute.U_1.V_2.Tree = Tree_mChild(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, Properties | yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Properties, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position);
          break;
        case 324:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 102;
          yySynAttribute.U_1.V_2.Tree = Tree_mChild(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_2.Ident, Properties | yyAttributeStack->A[yyStackPtr + 5].U_1.V_1.Properties, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position);
          break;
        case 325:;
        case 222:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 102;
          yySynAttribute.U_1.V_2.Tree = Tree_mActionPart(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree));
          break;
        case 326:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 113;
          yySynAttribute.U_1.V_1.Properties = 0X0L;
          break;
        case 327:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = 0X0L;
          break;
        case 328:;
        case 203:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Reverse));
          break;
        case 329:;
        case 212:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Link));
          break;
        case 330:;
        case 206:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Input));
          break;
        case 331:;
        case 207:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Output));
          break;
        case 332:;
        case 208:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Synthesized));
          break;
        case 333:;
        case 209:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Inherited));
          break;
        case 334:;
        case 204:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Thread));
          break;
        case 335:;
        case 201:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Virtual));
          break;
        case 336:;
        case 202:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Stack));
          break;
        case 337:;
        case 205:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Demand));
          break;
        case 338:;
        case 200:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Funct));
          break;
        case 339:;
        case 211:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 99;
          yySynAttribute.U_1.V_1.Properties = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Properties | (SET_ELEM(Tree_Ignore));
          break;
        case 340:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoAction;
          break;
        case 341:;
        case 227:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_mAssign(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree));
          break;
        case 342:;
        case 228:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_mCopy(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree));
          break;
        case 343:;
        case 226:;
          DEC1(yyStackPtr, 9);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_mTargetCode(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree));
          break;
        case 344:;
        case 223:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_mOrder(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Positions_NoPosition, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree));
          break;
        case 345:;
        case 224:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_mOrder(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Positions_NoPosition, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree));
          break;
        case 346:;
        case 229:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_40.Check.Next = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          break;
        case 347:;
        case 225:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_mTargetCode(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Scanner_Attribute.Position, Tree_nNoDesignator, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree));
          break;
        case 348:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 116;
          yySynAttribute.U_1.V_2.Tree = Tree_mTargetCode(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree, Scanner_Attribute.Position, Tree_nNoDesignator, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree));
          break;
        case 349:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 118;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          break;
        case 350:;
        case 245:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 118;
          yySynAttribute.U_1.V_2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree;
          yySynAttribute.U_1.V_2.Tree->U_1.V_40.Check.Actions = yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree;
          break;
        case 351:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 119;
          yySynAttribute.U_1.V_2.Tree = Tree_mCheck(Tree_nNoAction, Positions_NoPosition, (Tree_tTree)Tree_NoTree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_nNoAction);
          break;
        case 352:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 119;
          yySynAttribute.U_1.V_2.Tree = Tree_mCheck(Tree_nNoAction, Positions_NoPosition, (Tree_tTree)Tree_NoTree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree), Tree_nNoAction);
          break;
        case 353:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 119;
          yySynAttribute.U_1.V_2.Tree = Tree_mCheck(Tree_nNoAction, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), (Tree_tTree)Tree_NoTree, Tree_nNoAction);
          break;
        case 354:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 119;
          yySynAttribute.U_1.V_2.Tree = Tree_mCheck(Tree_nNoAction, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_2.Tree), Tree_nNoAction);
          break;
        case 355:;
          DEC1(yyStackPtr, 8);
          yyNonterminal = 119;
          yySynAttribute.U_1.V_2.Tree = Tree_mCheck(Tree_nNoAction, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_2.Tree), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree), Tree_nNoAction);
          break;
        case 356:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoDesignator;
          break;
        case 357:;
        case 221:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_mDesignator(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 358:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_mIdent(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          yySynAttribute.U_1.V_2.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree), yySynAttribute.U_1.V_2.Tree);
          yySynAttribute.U_1.V_2.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_1.StringRef, yySynAttribute.U_1.V_2.Tree);
          yySynAttribute.U_1.V_2.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree), yySynAttribute.U_1.V_2.Tree);
          break;
        case 359:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_mIdent(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          yySynAttribute.U_1.V_2.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree), yySynAttribute.U_1.V_2.Tree);
          break;
        case 360:;
        case 218:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 361:;
        case 220:;
          DEC1(yyStackPtr, 10);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_mRemote(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_2.Tree), yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 10].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 10].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 362:;
        case 216:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 363:;
        case 217:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 117;
          yySynAttribute.U_1.V_2.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 364:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 90;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoModule;
          break;
        case 365:;
        case 240:;
          DEC1(yyStackPtr, 12);
          yyNonterminal = 90;
          yySynAttribute.U_1.V_2.Tree = Tree_mModule(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_2.Ident, yyAttributeStack->A[yyStackPtr + 5].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 7].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 8].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 9].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 10].U_1.V_2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
          break;
        case 366:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 121;
          ModuleIdent = yyAttributeStack->A[yyStackPtr + 0].U_1.V_1.Scan.U_1.V_2.Ident;
          break;
        case 367:;
        case 187:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 93;
          yySynAttribute.U_1.V_1.Scan = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan;
          break;
        case 368:;
        case 188:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 93;
          yySynAttribute.U_1.V_1.Scan = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan;
          StringMem_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.StringRef, &String1);
          Strings_SubString(&String1, 2, (Strings_tStringIndex)(Strings_Length(&String1) - 1), &String2);
          yySynAttribute.U_1.V_1.Scan.U_1.V_2.Ident = Idents_MakeIdent(&String2);
          break;
        case 369:;
        case 197:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 104;
          yySynAttribute.U_1.V_1.Scan = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan;
          yySynAttribute.U_1.V_1.Properties = 0X0L;
          break;
        case 370:;
        case 198:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 104;
          yySynAttribute.U_1.V_1.Scan = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan;
          StringMem_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.StringRef, &String1);
          yySynAttribute.U_1.V_1.Scan.U_1.V_2.Ident = Idents_MakeIdent(&String1);
          yySynAttribute.U_1.V_1.Properties = SET_ELEM(Tree_String);
          break;
        case 371:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 120;
          yySynAttribute.U_1.V_2.Tree = Tree_nNoLayout;
          break;
        case 372:;
        case 219:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 120;
          yySynAttribute.U_1.V_2.Tree = Tree_mLayoutAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.Tree);
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
        DEC1(StackPtr, yyLength.A[State - 247]);
        Nonterminal = yyLeftHandSide.A[State - 247];
      }
      State = Next(Stack->A[StackPtr], Nonterminal);
      if (StackPtr >= VAL(yyStackPtrType, StackSize)) {
        DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      }
      INC(StackPtr);
      if (State < yyFirstFinalState) {
        goto EXIT_5;
      }
      State = yyFinalToProd.A[State - 187];
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
        State = yyFinalToProd.A[State - 187];
      }
      for (;;) {
        if (State == yyStopState) {
          DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
          Sets_ReleaseSet(&ContinueSet);
          return;
        } else {
          DEC1(StackPtr, yyLength.A[State - 247]);
          Nonterminal = yyLeftHandSide.A[State - 247];
        }
        State = Next(Stack->A[StackPtr], Nonterminal);
        INC(StackPtr);
        if (State < yyFirstFinalState) {
          goto EXIT_7;
        }
        State = yyFinalToProd.A[State - 187];
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
    yyNBasePtr.A[State] = (yyNCombTypePtr)ADR(yyNComb.A[NBase.A[State] - 82]);
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
  ClassCount = 0;
  InitProperties = SET_ELEM(Tree_Input);
  ModuleIdent = Idents_NoIdent;
  Tree_SubUnit = Idents_NoIdent;
  Tree_ViewName = Idents_NoIdent;
  ParserName = Idents_NoIdent;
  TreeName = Idents_NoIdent;
  EvalName = Idents_NoIdent;
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
    StringMem__init();
    Strings__init();
    Idents__init();
    Texts__init();
    Scanner__init();
    Positions__init();
    Idents__init();
    Tree__init();

    yyIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
