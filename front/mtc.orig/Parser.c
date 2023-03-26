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

#ifndef DEFINITION_Actions
#include "Actions.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Oper
#include "Oper.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
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

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Tokens
#include "Tokens.h"
#endif

#ifndef DEFINITION_Rules
#include "Rules.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

struct Parser_1 Parser_ParsTabName;

#define cEol   '\n'
#define eNumToBig   9
typedef struct S_1 {
    Scanner_tScanAttribute Scan;
} tParsAttribute;
static Strings_tString String, EndOfLineString;
static ADDRESS EndOfLine;
#define yyInitStackSize   100
#define yyNoState   0
#define yyFirstTerminal   0
#define yyLastTerminal   30
#define yyFirstSymbol   0
#define yyLastSymbol   62
#define yyTableMax   222
#define yyNTableMax   131
#define yyFirstReadState   1
#define yyLastReadState   62
#define yyFirstReadTermState   63
#define yyLastReadTermState   78
#define yyLastReadNontermState   96
#define yyFirstReduceState   97
#define yyLastReduceState   159
#define yyStartState   1
#define yyStopState   97
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
    Copy((STRING)"=", 1L, Name, O_3);
    break;
  case 2:;
    Copy((STRING)":", 1L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)"|", 1L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)"*", 1L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)"+", 1L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)"||", 2L, Name, O_3);
    break;
  case 8:;
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 9:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 10:;
    Copy((STRING)"[", 1L, Name, O_3);
    break;
  case 11:;
    Copy((STRING)"]", 1L, Name, O_3);
    break;
  case 12:;
    Copy((STRING)"EXPORT", 6L, Name, O_3);
    break;
  case 13:;
    Copy((STRING)"GLOBAL", 6L, Name, O_3);
    break;
  case 14:;
    Copy((STRING)"LOCAL", 5L, Name, O_3);
    break;
  case 15:;
    Copy((STRING)"BEGIN", 5L, Name, O_3);
    break;
  case 16:;
    Copy((STRING)"CLOSE", 5L, Name, O_3);
    break;
  case 17:;
    Copy((STRING)"TOKEN", 5L, Name, O_3);
    break;
  case 18:;
    Copy((STRING)"OPER", 4L, Name, O_3);
    break;
  case 19:;
    Copy((STRING)"NONE", 4L, Name, O_3);
    break;
  case 20:;
    Copy((STRING)"LEFT", 4L, Name, O_3);
    break;
  case 21:;
    Copy((STRING)"RIGHT", 5L, Name, O_3);
    break;
  case 22:;
    Copy((STRING)"RULE", 4L, Name, O_3);
    break;
  case 23:;
    Copy((STRING)"PREC", 4L, Name, O_3);
    break;
  case 24:;
    Copy((STRING)"Comment", 7L, Name, O_3);
    break;
  case 25:;
    Copy((STRING)"Number", 6L, Name, O_3);
    break;
  case 26:;
    Copy((STRING)"Action", 6L, Name, O_3);
    break;
  case 27:;
    Copy((STRING)"Identifier", 10L, Name, O_3);
    break;
  case 28:;
    Copy((STRING)"String", 6L, Name, O_3);
    break;
  case 29:;
    Copy((STRING)"SCANNER", 7L, Name, O_3);
    break;
  case 30:;
    Copy((STRING)"PARSER", 6L, Name, O_3);
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
  Actions_tActionMode ActionMode;
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
            Scanner_ErrorAttribute(VAL(INTEGER, yyRepairToken), &yyRepairAttribute);
            Parser_TokenName(yyRepairToken, yyTokenString.A, 128L);
            Errors_ErrorMessageI((LONGCARD)Errors_TokenInserted, (LONGCARD)Errors_Repair, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(yyTokenString));
            if (yyState >= yyFirstFinalState) {
              yyState = yyFinalToProd.A[yyState - 63];
            }
            INC(yyStackPtr);
            yyAttributeStack->A[yyStackPtr].Scan = yyRepairAttribute;
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
        yyAttributeStack->A[yyStackPtr].Scan = Scanner_Attribute;
        yyTerminal = VAL(yySymbolRange, Scanner_GetToken());
        yyIsRepairing = FALSE;
      }
      for (;;) {
        switch (yyState) {
        case 97:;
          DynArray_ReleaseArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyTableElmt));
          DynArray_ReleaseArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
          return yyErrorCount;
          break;
        case 98:;
        case 96:;
          DEC1(yyStackPtr, 7);
          yyNonterminal = 38;
          Tokens_MakeGlobalHeader(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 99:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 32;
          Actions_ScannerName = Idents_NoIdent;
          break;
        case 100:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 32;
          Strings_ArrayToString((STRING)"Scanner", 7L, &String);
          Actions_ScannerName = Idents_MakeIdent(&String);
          break;
        case 101:;
        case 64:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 32;
          Actions_ScannerName = yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_4.Sym;
          break;
        case 102:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 33;
          Actions_ParserName = Idents_NoIdent;
          break;
        case 103:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 33;
          Strings_ArrayToString((STRING)"Parser", 6L, &String);
          Actions_ParserName = Idents_MakeIdent(&String);
          break;
        case 104:;
        case 65:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 33;
          Actions_ParserName = yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_4.Sym;
          break;
        case 105:;
        case 79:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 34;
          Actions_PutComment(Actions_Export, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 4].Scan.Position);
          break;
        case 106:;
        case 80:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 34;
          Actions_PutComment(Actions_Global, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 4].Scan.Position);
          break;
        case 107:;
        case 81:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 34;
          Actions_PutComment(Actions_Local, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 4].Scan.Position);
          break;
        case 108:;
        case 82:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 34;
          Actions_PutComment(Actions_Begin, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 4].Scan.Position);
          break;
        case 109:;
        case 83:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 34;
          Actions_PutComment(Actions_Close, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 4].Scan.Position);
          break;
        case 110:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 34;
          break;
        case 111:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 44;
          ActionMode = Actions_Close;
          break;
        case 112:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 43;
          ActionMode = Actions_Begin;
          break;
        case 113:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 42;
          ActionMode = Actions_Local;
          break;
        case 114:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 41;
          ActionMode = Actions_Global;
          break;
        case 115:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 39;
          ActionMode = Actions_Export;
          break;
        case 116:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 40;
          Actions_PutAction(ActionMode, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_3.Act, yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 2].Scan.Position);
          break;
        case 117:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 40;
          break;
        case 118:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 35;
          Tokens_CompleteDeclarations();
          Tokens_MakeTokensHeader(yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 2].Scan.Position);
          break;
        case 119:;
        case 84:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 45;
          break;
        case 120:;
        case 85:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 45;
          break;
        case 121:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 46;
          Tokens_MakeDeclaration(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Sym, yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_5.HasCoding, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, (TokenTab_Terminal)yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_5.CodValue, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_5.CodNumbPos, yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 3].Scan.Position);
          break;
        case 122:;
        case 68:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 48;
          yySynAttribute.Scan.Mode = Scanner_Coding;
          if (yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_2.Value > 1000) {
            Errors_ErrorMessageI((LONGCARD)eNumToBig, (LONGCARD)Errors_eError, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, (LONGCARD)Errors_eInteger, ADR(yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_2.Value));
            yySynAttribute.Scan.U_1.V_5.HasCoding = FALSE;
            yySynAttribute.Scan.U_1.V_5.CodValue = 0;
            yySynAttribute.Scan.U_1.V_5.CodNumbPos = Positions_NoPosition;
          } else {
            yySynAttribute.Scan.U_1.V_5.HasCoding = TRUE;
            yySynAttribute.Scan.U_1.V_5.CodValue = yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_2.Value;
            yySynAttribute.Scan.U_1.V_5.CodNumbPos = yyAttributeStack->A[yyStackPtr + 2].Scan.Position;
          }
          break;
        case 123:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 48;
          yySynAttribute.Scan.Mode = Scanner_Coding;
          yySynAttribute.Scan.U_1.V_5.HasCoding = FALSE;
          yySynAttribute.Scan.U_1.V_5.CodValue = 0;
          yySynAttribute.Scan.U_1.V_5.CodNumbPos = Positions_NoPosition;
          break;
        case 124:;
        case 86:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 36;
          Oper_MakeOperHeader(yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 2].Scan.Position);
          break;
        case 125:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 36;
          break;
        case 126:;
        case 87:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 49;
          break;
        case 127:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 49;
          break;
        case 128:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 50;
          Oper_CompletePriority(yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 3].Scan.Position);
          break;
        case 129:;
        case 70:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 51;
          Oper_MakePriority(Oper_Left, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 130:;
        case 71:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 51;
          Oper_MakePriority(Oper_Right, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 131:;
        case 69:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 51;
          Oper_MakePriority(Oper_None, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 132:;
        case 89:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 52;
          break;
        case 133:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 52;
          break;
        case 134:;
        case 88:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 53;
          Oper_MakeOperator(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Sym, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 135:;
        case 66:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 47;
          yySynAttribute.Scan.Mode = Scanner_Symbol;
          yySynAttribute.Scan.U_1.V_4.Sym = yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Sym;
          yySynAttribute.Scan.Position = yyAttributeStack->A[yyStackPtr + 1].Scan.Position;
          break;
        case 136:;
        case 67:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 47;
          yySynAttribute.Scan.Mode = Scanner_Symbol;
          yySynAttribute.Scan.U_1.V_4.Sym = yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Sym;
          yySynAttribute.Scan.Position = yyAttributeStack->A[yyStackPtr + 1].Scan.Position;
          break;
        case 137:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 37;
          Rules_MakeRulesHeader(yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 2].Scan.Position);
          break;
        case 138:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 54;
          break;
        case 139:;
        case 95:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 54;
          break;
        case 140:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 55;
          Rules_MakeRule(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Sym, yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_6.Expr, yyAttributeStack->A[yyStackPtr + 5].Scan.U_1.V_1.Comm, yyAttributeStack->A[yyStackPtr + 5].Scan.Position, yyAttributeStack->A[yyStackPtr + 4].Scan.Position, yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_6.HasPrio, yyAttributeStack->A[yyStackPtr + 3].Scan.Position, yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_6.U_1.V_1.PriSym, yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_6.U_1.V_1.PriSymPos);
          break;
        case 141:;
        case 93:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 57;
          yySynAttribute.Scan.Mode = Scanner_PrioPart;
          yySynAttribute.Scan.U_1.V_6.HasPrio = TRUE;
          yySynAttribute.Scan.Position = yyAttributeStack->A[yyStackPtr + 1].Scan.Position;
          yySynAttribute.Scan.U_1.V_6.U_1.V_1.PriSym = yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_4.Sym;
          yySynAttribute.Scan.U_1.V_6.U_1.V_1.PriSymPos = yyAttributeStack->A[yyStackPtr + 2].Scan.Position;
          break;
        case 142:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 57;
          yySynAttribute.Scan.Mode = Scanner_PrioPart;
          yySynAttribute.Scan.U_1.V_6.HasPrio = FALSE;
          yySynAttribute.Scan.U_1.V_6.U_1.V_1.PriSymPos = Positions_NoPosition;
          yySynAttribute.Scan.U_1.V_6.U_1.V_1.PriSym = 0;
          break;
        case 143:;
        case 94:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 56;
          yySynAttribute.Scan = yyAttributeStack->A[yyStackPtr + 4].Scan;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakePrioAlternativeNode(yyAttributeStack->A[yyStackPtr + 3].Scan.Position, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr, yyAttributeStack->A[yyStackPtr + 4].Scan.U_1.V_6.Expr, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_6.HasPrio, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_6.U_1.V_1.PriSym, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_6.U_1.V_1.PriSymPos);
          break;
        case 144:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 56;
          yySynAttribute.Scan = yyAttributeStack->A[yyStackPtr + 2].Scan;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          if (yyAttributeStack->A[yyStackPtr + 1].Scan.Mode == Scanner_Empty) {
            yySynAttribute.Scan.U_1.V_6.Expr = Rules_NoExpression;
          } else {
            yySynAttribute.Scan.U_1.V_6.Expr = yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr;
          }
          break;
        case 145:;
        case 90:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 58;
          if (yyAttributeStack->A[yyStackPtr + 2].Scan.Mode != Scanner_Empty) {
            yySynAttribute.Scan.Mode = Scanner_RightSide;
            yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeBinaryNode(Rules_Sequence, Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_6.Expr);
          } else {
            yySynAttribute.Scan = yyAttributeStack->A[yyStackPtr + 1].Scan;
          }
          break;
        case 146:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 58;
          yySynAttribute.Scan.Mode = Scanner_Empty;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_NoExpression;
          break;
        case 147:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 59;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr;
          break;
        case 148:;
        case 75:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 59;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeUnaryNode(Rules_Star, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr);
          break;
        case 149:;
        case 76:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 59;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeUnaryNode(Rules_Plus, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr);
          break;
        case 150:;
        case 91:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 59;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeBinaryNode(Rules_Separator, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr, yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_6.Expr);
          break;
        case 151:;
        case 77:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 60;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeBracketNode(Rules_Optional, yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 3].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_6.Expr);
          break;
        case 152:;
        case 78:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 60;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeBracketNode(Rules_Bracket, yyAttributeStack->A[yyStackPtr + 1].Scan.Position, yyAttributeStack->A[yyStackPtr + 3].Scan.Position, yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_6.Expr);
          break;
        case 153:;
        case 73:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 60;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeLeafNode(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Sym, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 154:;
        case 74:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 60;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeLeafNode(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_4.Sym, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 155:;
        case 72:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 60;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeActionNode(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_3.Act, yyAttributeStack->A[yyStackPtr + 1].Scan.Position);
          break;
        case 156:;
        case 92:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 61;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          yySynAttribute.Scan.U_1.V_6.Expr = Rules_MakeBinaryNode(Rules_Alternative, yyAttributeStack->A[yyStackPtr + 2].Scan.Position, yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr, yyAttributeStack->A[yyStackPtr + 3].Scan.U_1.V_6.Expr);
          break;
        case 157:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 61;
          yySynAttribute.Scan.Mode = Scanner_RightSide;
          if (yyAttributeStack->A[yyStackPtr + 1].Scan.Mode == Scanner_Empty) {
            yySynAttribute.Scan.U_1.V_6.Expr = Rules_NoExpression;
          } else {
            yySynAttribute.Scan.U_1.V_6.Expr = yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_6.Expr;
          }
          break;
        case 158:;
        case 63:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 31;
          yySynAttribute.Scan.Mode = Scanner_Comment;
          if (Lists_IsEmpty(yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Comm)) {
            yySynAttribute.Scan.Position = yyAttributeStack->A[yyStackPtr + 2].Scan.Position;
            yySynAttribute.Scan.U_1.V_1.Comm = yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm;
          } else {
            Lists_Append(&yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Comm, EndOfLine);
            while (!Lists_IsEmpty(yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm)) {
              Lists_Append(&yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Comm, Lists_Head(yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm));
              Lists_Tail(&yyAttributeStack->A[yyStackPtr + 2].Scan.U_1.V_1.Comm);
            }
            yySynAttribute.Scan.Position = yyAttributeStack->A[yyStackPtr + 1].Scan.Position;
            yySynAttribute.Scan.U_1.V_1.Comm = yyAttributeStack->A[yyStackPtr + 1].Scan.U_1.V_1.Comm;
          }
          break;
        case 159:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 31;
          yySynAttribute.Scan.Mode = Scanner_Comment;
          yySynAttribute.Scan.Position = Positions_NoPosition;
          Lists_MakeList(&yySynAttribute.Scan.U_1.V_1.Comm);
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
      yyAttributeStack->A[yyStackPtr].Scan = Scanner_Attribute;
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
        DEC1(StackPtr, yyLength.A[State - 97]);
        Nonterminal = yyLeftHandSide.A[State - 97];
      }
      State = Next(Stack->A[StackPtr], Nonterminal);
      if (StackPtr >= VAL(yyStackPtrType, StackSize)) {
        DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      }
      INC(StackPtr);
      if (State < yyFirstFinalState) {
        goto EXIT_5;
      }
      State = yyFinalToProd.A[State - 63];
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
        State = yyFinalToProd.A[State - 63];
      }
      for (;;) {
        if (State == yyStopState) {
          DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
          Sets_ReleaseSet(&ContinueSet);
          return;
        } else {
          DEC1(StackPtr, yyLength.A[State - 97]);
          Nonterminal = yyLeftHandSide.A[State - 97];
        }
        State = Next(Stack->A[StackPtr], Nonterminal);
        INC(StackPtr);
        if (State < yyFirstFinalState) {
          goto EXIT_7;
        }
        State = yyFinalToProd.A[State - 63];
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
    yyNBasePtr.A[State] = (yyNCombTypePtr)ADR(yyNComb.A[NBase.A[State] - 31]);
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
  Strings_AssignEmpty(&EndOfLineString);
  Strings_Append(&EndOfLineString, cEol);
  EndOfLine = (ADDRESS)StringMem_PutString(&EndOfLineString);
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
    Actions__init();
    Errors__init();
    Lists__init();
    Oper__init();
    Scanner__init();
    Positions__init();
    Strings__init();
    StringMem__init();
    Idents__init();
    TokenTab__init();
    Tokens__init();
    Rules__init();

    yyIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
