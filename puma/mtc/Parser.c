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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Assertions
#include "Assertions.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

struct Parser_1 Parser_ParsTabName;

static Strings_tString String1, String2;
static INTEGER NameCount;
static Positions_tPosition Line;
static Tree_tTree nNoParameter, nNoName, nNoRule, nNoDesignator, nNoStatement, nNoLayout, nNoPatternsList;
static Tree_tTree mTargetExpr ARGS((Positions_tPosition pPos, Tree_tTree pExpr));
static Tree_tTree mTargetStmt ARGS((Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pParameters, Tree_tTree pStmt));
static Tree_tTree mCodes ARGS(());
static Tree_tTree mRules ARGS((Positions_tPosition Line, Tree_tTree Patterns, Tree_tTree Exprs, Tree_tTree Expr, Tree_tTree Statements, Tree_tTree Next));
typedef struct S_1 {
    Idents_tIdent Id;
} yyTrafoName;
typedef struct S_2 {
    Tree_tTree Tree;
} yyTreePart;
typedef struct S_3 {
    Tree_tTree Tree;
} yyTreeNames;
typedef struct S_4 {
    Tree_tTree Tree;
} yyPublicPart;
typedef struct S_5 {
    Tree_tTree Tree;
} yyExternPart0;
typedef struct S_6 {
    Tree_tTree Tree;
} yyExternPart;
typedef struct S_7 {
    Tree_tTree Tree;
} yyNames;
typedef struct S_8 {
    Tree_tTree Tree;
} yyCodes;
typedef struct S_9 {
    Tree_tTree Tree;
} yyRoutines;
typedef struct S_10 {
    Tree_tTree Tree;
} yyOutParameters;
typedef struct S_11 {
    Tree_tTree Tree;
} yyParameters;
typedef struct S_12 {
    BOOLEAN IsRef;
} yyMode;
typedef struct S_13 {
    Tree_tTree Tree;
} yyDeclarations;
typedef struct S_14 {
    Tree_tTree Tree;
} yyType;
typedef struct S_15 {
    Texts_tText Text;
    Positions_tPosition Position;
} yyLocalCode;
typedef struct S_16 {
    Tree_tTree Tree;
} yyRules;
typedef struct S_17 {
    Tree_tTree Tree;
} yyPatterns;
typedef struct S_18 {
    Tree_tTree Tree;
} yyPatterns2;
typedef struct S_19 {
    Tree_tTree Tree;
} yyExprs;
typedef struct S_20 {
    Tree_tTree Tree;
} yyNamedExprs;
typedef struct S_21 {
    Tree_tTree Tree;
} yyExprs2;
typedef struct S_22 {
    Tree_tTree Tree;
} yyNamedExprs2;
typedef struct S_23 {
    Tree_tTree Tree;
} yyExpr;
typedef struct S_24 {
    Tree_tTree Tree;
} yyPrefixExpr;
typedef struct S_25 {
    Tree_tTree Tree;
} yyPostfixExpr;
typedef struct S_26 {
    Tree_tTree Tree;
} yyPrimaryExpr;
typedef struct S_27 {
    Tree_tTree Tree;
} yyStatements;
typedef struct S_28 {
    Tree_tTree Tree;
} yyTargetCodes;
typedef struct S_29 {
    Idents_tIdent Id;
    Positions_tPosition Position;
} yyName0;
typedef struct S_30 {
    Idents_tIdent Id;
    Positions_tPosition Position;
} yyName1;
typedef struct S_31 {
    Tree_tTree Tree;
} yySpace;
typedef struct S_32 {
    union {
        struct {
            Scanner_tScanAttribute Scan;
        } V_1;
        struct {
            yyTrafoName TrafoName;
        } V_2;
        struct {
            yyTreePart TreePart;
        } V_3;
        struct {
            yyTreeNames TreeNames;
        } V_4;
        struct {
            yyPublicPart PublicPart;
        } V_5;
        struct {
            yyExternPart0 ExternPart0;
        } V_6;
        struct {
            yyExternPart ExternPart;
        } V_7;
        struct {
            yyNames Names;
        } V_8;
        struct {
            yyCodes Codes;
        } V_9;
        struct {
            yyRoutines Routines;
        } V_10;
        struct {
            yyOutParameters OutParameters;
        } V_11;
        struct {
            yyParameters Parameters;
        } V_12;
        struct {
            yyMode Mode;
        } V_13;
        struct {
            yyDeclarations Declarations;
        } V_14;
        struct {
            yyType Type;
        } V_15;
        struct {
            yyLocalCode LocalCode;
        } V_16;
        struct {
            yyRules Rules;
        } V_17;
        struct {
            yyPatterns Patterns;
        } V_18;
        struct {
            yyPatterns2 Patterns2;
        } V_19;
        struct {
            yyExprs Exprs;
        } V_20;
        struct {
            yyNamedExprs NamedExprs;
        } V_21;
        struct {
            yyExprs2 Exprs2;
        } V_22;
        struct {
            yyNamedExprs2 NamedExprs2;
        } V_23;
        struct {
            yyExpr Expr;
        } V_24;
        struct {
            yyPrefixExpr PrefixExpr;
        } V_25;
        struct {
            yyPostfixExpr PostfixExpr;
        } V_26;
        struct {
            yyPrimaryExpr PrimaryExpr;
        } V_27;
        struct {
            yyStatements Statements;
        } V_28;
        struct {
            yyTargetCodes TargetCodes;
        } V_29;
        struct {
            yyName0 Name0;
        } V_30;
        struct {
            yyName1 Name1;
        } V_31;
        struct {
            yySpace Space;
        } V_32;
    } U_1;
} tParsAttribute;
#define yyInitStackSize   100
#define yyNoState   0
#define yyFirstTerminal   0
#define yyLastTerminal   51
#define yyFirstSymbol   0
#define yyLastSymbol   87
#define yyTableMax   873
#define yyNTableMax   294
#define yyFirstReadState   1
#define yyLastReadState   187
#define yyFirstReadTermState   188
#define yyLastReadTermState   255
#define yyLastReadNontermState   282
#define yyFirstReduceState   283
#define yyLastReduceState   428
#define yyStartState   1
#define yyStopState   283
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
typedef struct S_33 {
    yyStateRange Check, Next;
} yyTCombType;
typedef yyStateRange yyNCombType;
typedef yyTCombType *yyTCombTypePtr;
typedef yyNCombType *yyNCombTypePtr;
typedef yyTableElmt yyStackPtrType;
typedef struct S_34 {
    yyStateRange A[MAX_SHORTCARD + 1];
} *yyStackType;
typedef struct S_35 {
    tParsAttribute A[MAX_SHORTCARD + 1];
} *yyAttributeStackType;
static struct S_36 {
    yyTCombTypePtr A[yyLastReadState + 1];
} yyTBasePtr;
static struct S_37 {
    yyNCombTypePtr A[yyLastReadState + 1];
} yyNBasePtr;
static struct S_38 {
    yyReadRange A[yyLastReadState + 1];
} yyDefault;
static struct S_39 {
    yyTCombType A[yyTableMax + 1];
} yyTComb;
static struct S_40 {
    yyNCombType A[yyNTableMax - (yyLastTerminal + 1) + 1];
} yyNComb;
static struct S_41 {
    yyTableElmt A[yyLastReduceState - yyFirstReduceState + 1];
} yyLength;
static struct S_42 {
    yySymbolRange A[yyLastReduceState - yyFirstReduceState + 1];
} yyLeftHandSide;
static struct S_43 {
    yySymbolRange A[yyLastReadState + 1];
} yyContinuation;
static struct S_44 {
    yyReduceRange A[yyLastReadNontermState - yyFirstReadTermState + 1];
} yyFinalToProd;
static BOOLEAN yyIsInitialized;
static System_tFile yyTableFile;
static void Copy ARGS((CHAR Source[], LONGCARD , CHAR Target[], LONGCARD ));
struct S_48 {
    CHAR A[127 + 1];
};
static void ErrorRecovery ARGS((yySymbolRange *Terminal, yyStackType StateStack, LONGINT StackSize, yyStackPtrType StackPtr));
struct S_49 {
    CHAR A[127 + 1];
};
static void ComputeContinuation ARGS((yyStackType Stack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *ContinueSet));
static BOOLEAN IsContinuation ARGS((yySymbolRange Terminal, yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr));
static void ComputeRestartPoints ARGS((yyStackType ParseStack, LONGINT StackSize, yyStackPtrType StackPtr, Sets_tSet *RestartSet));
static yyStateRange Next ARGS((yyStateRange State, yySymbolRange Symbol));
static void yyGetTables ARGS(());
struct S_50 {
    yyTCombRange A[yyLastReadState + 1];
};
struct S_51 {
    yyNCombRange A[yyLastReadState + 1];
};
static CARDINAL yyGetTable ARGS((ADDRESS Address));
static void yyErrorCheck ARGS((INTEGER ErrorCode, INTEGER Info));
static void BeginParser ARGS(());


static Tree_tTree mTargetExpr
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pExpr)
# else
(pPos, pExpr)
Positions_tPosition pPos;
Tree_tTree pExpr;
# endif
{
  Tree_tTree LResult;

  LResult = Tree_mTargetExpr(pPos, Idents_NoIdent, pExpr);
  Sets_InitNullSet(&LResult->U_1.V_78.TargetExpr.UsedNames);
  return LResult;
}

static Tree_tTree mTargetStmt
# ifdef __STDC__
(Positions_tPosition pPos, Tree_tTree pNext, Tree_tTree pParameters, Tree_tTree pStmt)
# else
(pPos, pNext, pParameters, pStmt)
Positions_tPosition pPos;
Tree_tTree pNext;
Tree_tTree pParameters;
Tree_tTree pStmt;
# endif
{
  Tree_tTree LResult;

  LResult = Tree_mTargetStmt(pPos, pNext, pParameters, pStmt);
  Sets_InitNullSet(&LResult->U_1.V_88.TargetStmt.UsedNames);
  return LResult;
}

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

static Tree_tTree mRules
# ifdef __STDC__
(Positions_tPosition Line, Tree_tTree Patterns, Tree_tTree Exprs, Tree_tTree Expr, Tree_tTree Statements, Tree_tTree Next)
# else
(Line, Patterns, Exprs, Expr, Statements, Next)
Positions_tPosition Line;
Tree_tTree Patterns;
Tree_tTree Exprs, Expr, Statements, Next;
# endif
{
  Tree_tTree Tree;

  Tree = Tree_mRule(Line, Patterns->U_1.V_49.OnePatternsList.Patterns, Exprs, Expr, Statements, Next);
  Patterns = Patterns->U_1.V_49.OnePatternsList.Next;
  while (Patterns->U_1.V_1.Kind == Tree_OnePatternsList) {
    Tree = Tree_mRule(Line, Patterns->U_1.V_49.OnePatternsList.Patterns, Tree_CopyTree(Exprs), Tree_CopyTree(Expr), Tree_CopyTree(Statements), Tree);
    Patterns = Patterns->U_1.V_49.OnePatternsList.Next;
  }
  return Tree;
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
    Copy((STRING)"Operator", 8L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)"IncOperator", 11L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)"CompoundOperator", 16L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)"TargetBlock", 11L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)"String", 6L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)"Number", 6L, Name, O_3);
    break;
  case 8:;
    Copy((STRING)"TargetCode", 10L, Name, O_3);
    break;
  case 9:;
    Copy((STRING)"WhiteSpace", 10L, Name, O_3);
    break;
  case 10:;
    Copy((STRING)"::", 2L, Name, O_3);
    break;
  case 11:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 12:;
    Copy((STRING)"->", 2L, Name, O_3);
    break;
  case 13:;
    Copy((STRING)"TRAFO", 5L, Name, O_3);
    break;
  case 14:;
    Copy((STRING)"TREE", 4L, Name, O_3);
    break;
  case 15:;
    Copy((STRING)",", 1L, Name, O_3);
    break;
  case 16:;
    Copy((STRING)"PUBLIC", 6L, Name, O_3);
    break;
  case 17:;
    Copy((STRING)"EXTERN", 6L, Name, O_3);
    break;
  case 18:;
    Copy((STRING)";", 1L, Name, O_3);
    break;
  case 19:;
    Copy((STRING)"SPECWITH", 8L, Name, O_3);
    break;
  case 20:;
    Copy((STRING)"BODYWITH", 8L, Name, O_3);
    break;
  case 21:;
    Copy((STRING)"EXPORT", 6L, Name, O_3);
    break;
  case 22:;
    Copy((STRING)"IMPORT", 6L, Name, O_3);
    break;
  case 23:;
    Copy((STRING)"GLOBAL", 6L, Name, O_3);
    break;
  case 24:;
    Copy((STRING)"BEGIN", 5L, Name, O_3);
    break;
  case 25:;
    Copy((STRING)"CLOSE", 5L, Name, O_3);
    break;
  case 26:;
    Copy((STRING)"PROCEDURE", 9L, Name, O_3);
    break;
  case 27:;
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 28:;
    Copy((STRING)"REF", 3L, Name, O_3);
    break;
  case 29:;
    Copy((STRING)":", 1L, Name, O_3);
    break;
  case 30:;
    Copy((STRING)"[", 1L, Name, O_3);
    break;
  case 31:;
    Copy((STRING)"]", 1L, Name, O_3);
    break;
  case 32:;
    Copy((STRING)"=>", 2L, Name, O_3);
    break;
  case 33:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 34:;
    Copy((STRING)"LOCAL", 5L, Name, O_3);
    break;
  case 35:;
    Copy((STRING)"..", 2L, Name, O_3);
    break;
  case 36:;
    Copy((STRING)":>", 2L, Name, O_3);
    break;
  case 37:;
    Copy((STRING)"NIL", 3L, Name, O_3);
    break;
  case 38:;
    Copy((STRING)"_", 1L, Name, O_3);
    break;
  case 39:;
    Copy((STRING)"{", 1L, Name, O_3);
    break;
  case 40:;
    Copy((STRING)"}", 1L, Name, O_3);
    break;
  case 41:;
    Copy((STRING)"^", 1L, Name, O_3);
    break;
  case 42:;
    Copy((STRING)":=", 2L, Name, O_3);
    break;
  case 43:;
    Copy((STRING)"?", 1L, Name, O_3);
    break;
  case 44:;
    Copy((STRING)"REJECT", 6L, Name, O_3);
    break;
  case 45:;
    Copy((STRING)"FAIL", 4L, Name, O_3);
    break;
  case 46:;
    Copy((STRING)"VAR", 3L, Name, O_3);
    break;
  case 47:;
    Copy((STRING)"NL", 2L, Name, O_3);
    break;
  case 48:;
    Copy((STRING)"RETURN", 6L, Name, O_3);
    break;
  case 49:;
    Copy((STRING)"FUNCTION", 8L, Name, O_3);
    break;
  case 50:;
    Copy((STRING)"PREDICATE", 9L, Name, O_3);
    break;
  case 51:;
    Copy((STRING)"HIGH", 4L, Name, O_3);
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
  struct S_48 yyTokenString;

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
              yyState = yyFinalToProd.A[yyState - 188];
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
        case 283:;
          DynArray_ReleaseArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyTableElmt));
          DynArray_ReleaseArray((ADDRESS *)&yyAttributeStack, &yyAttrStackSize, (LONGINT)sizeof(tParsAttribute));
          return yyErrorCount;
          break;
        case 284:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 58;
          Tree_TreeRoot = Tree_mSpec(yyAttributeStack->A[yyStackPtr + 1].U_1.V_2.TrafoName.Id, yyAttributeStack->A[yyStackPtr + 2].U_1.V_3.TreePart.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_5.PublicPart.Tree, yyAttributeStack->A[yyStackPtr + 4].U_1.V_6.ExternPart0.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_9.Codes.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 6].U_1.V_10.Routines.Tree));
          break;
        case 285:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 52;
          Strings_ArrayToString((STRING)"Trafo", 5L, &String1);
          yySynAttribute.U_1.V_2.TrafoName.Id = Idents_MakeIdent(&String1);
          break;
        case 286:;
        case 256:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 52;
          yySynAttribute.U_1.V_2.TrafoName.Id = yyAttributeStack->A[yyStackPtr + 2].U_1.V_30.Name0.Id;
          break;
        case 287:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 53;
          Strings_ArrayToString((STRING)"Tree", 4L, &String1);
          yySynAttribute.U_1.V_3.TreePart.Tree = Tree_mTreeName(Idents_MakeIdent(&String1), Scanner_Attribute.Position, Tree_mNoTreeName());
          break;
        case 288:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 53;
          yySynAttribute.U_1.V_3.TreePart.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_4.TreeNames.Tree);
          break;
        case 289:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 60;
          yySynAttribute.U_1.V_4.TreeNames.Tree = Tree_mNoTreeName();
          break;
        case 290:;
        case 190:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 60;
          yySynAttribute.U_1.V_4.TreeNames.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.TreeNames.Tree;
          break;
        case 291:;
        case 257:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 60;
          yySynAttribute.U_1.V_4.TreeNames.Tree = Tree_mTreeName(yyAttributeStack->A[yyStackPtr + 2].U_1.V_30.Name0.Id, yyAttributeStack->A[yyStackPtr + 2].U_1.V_30.Name0.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_4.TreeNames.Tree);
          break;
        case 292:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_5.PublicPart.Tree = nNoName;
          break;
        case 293:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 54;
          yySynAttribute.U_1.V_5.PublicPart.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_8.Names.Tree);
          break;
        case 294:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 55;
          yySynAttribute.U_1.V_6.ExternPart0.Tree = nNoName;
          break;
        case 295:;
        case 259:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 55;
          yySynAttribute.U_1.V_6.ExternPart0.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_8.Names.Tree);
          break;
        case 296:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 63;
          yySynAttribute.U_1.V_7.ExternPart.Tree = nNoName;
          break;
        case 297:;
        case 203:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 63;
          yySynAttribute.U_1.V_7.ExternPart.Tree = Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_8.Names.Tree);
          break;
        case 298:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 61;
          yySynAttribute.U_1.V_8.Names.Tree = nNoName;
          break;
        case 299:;
        case 191:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 61;
          yySynAttribute.U_1.V_8.Names.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_8.Names.Tree;
          break;
        case 300:;
        case 258:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 61;
          yySynAttribute.U_1.V_8.Names.Tree = Tree_mName(yyAttributeStack->A[yyStackPtr + 2].U_1.V_30.Name0.Id, yyAttributeStack->A[yyStackPtr + 2].U_1.V_30.Name0.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_8.Names.Tree);
          break;
        case 301:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = mCodes();
          break;
        case 302:;
        case 193:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_9.Codes.Tree;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.SpecWith = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.SpecWithLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 303:;
        case 194:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_9.Codes.Tree;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.BodyWith = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.BodyWithLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 304:;
        case 195:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_9.Codes.Tree;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.Export = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.ExportLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 305:;
        case 196:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_9.Codes.Tree;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.Import = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.ImportLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 306:;
        case 197:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_9.Codes.Tree;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.Global = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.GlobalLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 307:;
        case 198:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_9.Codes.Tree;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.Begin = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.BeginLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 308:;
        case 199:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 56;
          yySynAttribute.U_1.V_9.Codes.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_9.Codes.Tree;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.Close = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          yySynAttribute.U_1.V_9.Codes.Tree->U_1.V_12.Codes.CloseLine = yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position;
          break;
        case 309:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 57;
          yySynAttribute.U_1.V_10.Routines.Tree = Tree_mNoRoutine();
          break;
        case 310:;
          DEC1(yyStackPtr, 10);
          yyNonterminal = 57;
          yySynAttribute.U_1.V_10.Routines.Tree = Tree_mProcedure(yyAttributeStack->A[yyStackPtr + 1].U_1.V_10.Routines.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Id, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Position, yyAttributeStack->A[yyStackPtr + 5].U_1.V_12.Parameters.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_11.OutParameters.Tree, yyAttributeStack->A[yyStackPtr + 8].U_1.V_7.ExternPart.Tree, yyAttributeStack->A[yyStackPtr + 9].U_1.V_16.LocalCode.Text, yyAttributeStack->A[yyStackPtr + 9].U_1.V_16.LocalCode.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 10].U_1.V_17.Rules.Tree));
          break;
        case 311:;
          DEC1(yyStackPtr, 11);
          yyNonterminal = 57;
          yySynAttribute.U_1.V_10.Routines.Tree = Tree_mFunction(yyAttributeStack->A[yyStackPtr + 1].U_1.V_10.Routines.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Id, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Position, yyAttributeStack->A[yyStackPtr + 5].U_1.V_12.Parameters.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_11.OutParameters.Tree, yyAttributeStack->A[yyStackPtr + 9].U_1.V_7.ExternPart.Tree, yyAttributeStack->A[yyStackPtr + 10].U_1.V_16.LocalCode.Text, yyAttributeStack->A[yyStackPtr + 10].U_1.V_16.LocalCode.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 11].U_1.V_17.Rules.Tree), Tree_mParam(FALSE, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 8].U_1.V_15.Type.Tree->U_1.V_39.Type.Pos, yyAttributeStack->A[yyStackPtr + 8].U_1.V_15.Type.Tree, nNoParameter));
          break;
        case 312:;
          DEC1(yyStackPtr, 12);
          yyNonterminal = 57;
          yySynAttribute.U_1.V_10.Routines.Tree = Tree_mFunction(yyAttributeStack->A[yyStackPtr + 1].U_1.V_10.Routines.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Id, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Position, yyAttributeStack->A[yyStackPtr + 5].U_1.V_12.Parameters.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_11.OutParameters.Tree, yyAttributeStack->A[yyStackPtr + 10].U_1.V_7.ExternPart.Tree, yyAttributeStack->A[yyStackPtr + 11].U_1.V_16.LocalCode.Text, yyAttributeStack->A[yyStackPtr + 11].U_1.V_16.LocalCode.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 12].U_1.V_17.Rules.Tree), Tree_mParam(FALSE, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 8].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 9].U_1.V_15.Type.Tree, nNoParameter));
          break;
        case 313:;
          DEC1(yyStackPtr, 10);
          yyNonterminal = 57;
          yySynAttribute.U_1.V_10.Routines.Tree = Tree_mPredicate(yyAttributeStack->A[yyStackPtr + 1].U_1.V_10.Routines.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Id, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Position, yyAttributeStack->A[yyStackPtr + 5].U_1.V_12.Parameters.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_11.OutParameters.Tree, yyAttributeStack->A[yyStackPtr + 8].U_1.V_7.ExternPart.Tree, yyAttributeStack->A[yyStackPtr + 9].U_1.V_16.LocalCode.Text, yyAttributeStack->A[yyStackPtr + 9].U_1.V_16.LocalCode.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 10].U_1.V_17.Rules.Tree));
          break;
        case 314:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 65;
          yySynAttribute.U_1.V_11.OutParameters.Tree = nNoParameter;
          break;
        case 315:;
        case 260:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 65;
          yySynAttribute.U_1.V_11.OutParameters.Tree = yyAttributeStack->A[yyStackPtr + 2].U_1.V_12.Parameters.Tree;
          break;
        case 316:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 64;
          yySynAttribute.U_1.V_12.Parameters.Tree = nNoParameter;
          break;
        case 317:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 64;
          yySynAttribute.U_1.V_12.Parameters.Tree = Tree_mParam(yyAttributeStack->A[yyStackPtr + 1].U_1.V_13.Mode.IsRef, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_15.Type.Tree, nNoParameter);
          break;
        case 318:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 64;
          Strings_ArrayToString((STRING)"yyP", 3L, &String1);
          INC(NameCount);
          Strings_IntToString(NameCount, &String2);
          Strings_Concatenate(&String1, &String2);
          yySynAttribute.U_1.V_12.Parameters.Tree = Tree_mParam(yyAttributeStack->A[yyStackPtr + 1].U_1.V_13.Mode.IsRef, Idents_MakeIdent(&String1), Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 2].U_1.V_15.Type.Tree, nNoParameter);
          break;
        case 319:;
        case 262:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 64;
          yySynAttribute.U_1.V_12.Parameters.Tree = Tree_mParam(yyAttributeStack->A[yyStackPtr + 1].U_1.V_13.Mode.IsRef, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_15.Type.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_12.Parameters.Tree);
          break;
        case 320:;
        case 264:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 64;
          Strings_ArrayToString((STRING)"yyP", 3L, &String1);
          INC(NameCount);
          Strings_IntToString(NameCount, &String2);
          Strings_Concatenate(&String1, &String2);
          yySynAttribute.U_1.V_12.Parameters.Tree = Tree_mParam(yyAttributeStack->A[yyStackPtr + 1].U_1.V_13.Mode.IsRef, Idents_MakeIdent(&String1), Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 2].U_1.V_15.Type.Tree, yyAttributeStack->A[yyStackPtr + 4].U_1.V_12.Parameters.Tree);
          break;
        case 321:;
        case 263:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 64;
          yySynAttribute.U_1.V_12.Parameters.Tree = Tree_mParam(yyAttributeStack->A[yyStackPtr + 1].U_1.V_13.Mode.IsRef, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_15.Type.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_12.Parameters.Tree);
          break;
        case 322:;
        case 265:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 64;
          Strings_ArrayToString((STRING)"yyP", 3L, &String1);
          INC(NameCount);
          Strings_IntToString(NameCount, &String2);
          Strings_Concatenate(&String1, &String2);
          yySynAttribute.U_1.V_12.Parameters.Tree = Tree_mParam(yyAttributeStack->A[yyStackPtr + 1].U_1.V_13.Mode.IsRef, Idents_MakeIdent(&String1), Positions_NoPosition, yyAttributeStack->A[yyStackPtr + 2].U_1.V_15.Type.Tree, yyAttributeStack->A[yyStackPtr + 4].U_1.V_12.Parameters.Tree);
          break;
        case 323:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 69;
          yySynAttribute.U_1.V_13.Mode.IsRef = FALSE;
          break;
        case 324:;
        case 200:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 69;
          yySynAttribute.U_1.V_13.Mode.IsRef = TRUE;
          break;
        case 325:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 70;
          Scanner_Warning((STRING)"VAR needed", 10L, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position);
          yySynAttribute.U_1.V_14.Declarations.Tree = Tree_mParam(FALSE, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_15.Type.Tree, nNoParameter);
          break;
        case 326:;
        case 280:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 70;
          Scanner_Warning((STRING)"VAR needed", 10L, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position);
          yySynAttribute.U_1.V_14.Declarations.Tree = Tree_mParam(FALSE, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 3].U_1.V_15.Type.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_14.Declarations.Tree);
          break;
        case 327:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 70;
          yySynAttribute.U_1.V_14.Declarations.Tree = Tree_mParam(FALSE, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_15.Type.Tree, nNoParameter);
          break;
        case 328:;
        case 279:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 70;
          yySynAttribute.U_1.V_14.Declarations.Tree = Tree_mParam(FALSE, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 4].U_1.V_15.Type.Tree, yyAttributeStack->A[yyStackPtr + 6].U_1.V_14.Declarations.Tree);
          break;
        case 329:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 68;
          yySynAttribute.U_1.V_15.Type.Tree = Tree_mType(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, nNoName);
          break;
        case 330:;
        case 261:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 68;
          yySynAttribute.U_1.V_15.Type.Tree = Tree_mType(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_mName(yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Id, yyAttributeStack->A[yyStackPtr + 3].U_1.V_30.Name0.Position, nNoName));
          break;
        case 331:;
        case 202:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 68;
          yySynAttribute.U_1.V_15.Type.Tree = Tree_mType(Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_8.Names.Tree));
          break;
        case 332:;
        case 201:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 68;
          yySynAttribute.U_1.V_15.Type.Tree = Tree_mType(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 4].U_1.V_8.Names.Tree));
          break;
        case 333:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 66;
          Texts_MakeText(&yySynAttribute.U_1.V_16.LocalCode.Text);
          yySynAttribute.U_1.V_16.LocalCode.Position = Positions_NoPosition;
          break;
        case 334:;
        case 266:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 66;
          yySynAttribute.U_1.V_16.LocalCode = yyAttributeStack->A[yyStackPtr + 3].U_1.V_16.LocalCode;
          yySynAttribute.U_1.V_16.LocalCode.Position = yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position;
          break;
        case 335:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 71;
          yySynAttribute.U_1.V_16.LocalCode.Text = yyAttributeStack->A[yyStackPtr + 0].U_1.V_1.Scan.U_1.V_5.TargetBlock.Text;
          break;
        case 336:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = nNoRule;
          break;
        case 337:;
        case 236:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_19.Patterns2.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.Position), Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.Position), nNoStatement, yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 338:;
        case 250:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.Position), Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.Position), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 339:;
        case 237:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_22.Exprs2.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.Position), nNoStatement, yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 340:;
        case 254:;
          DEC1(yyStackPtr, 7);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 7].U_1.V_1.Scan.Position), yyAttributeStack->A[yyStackPtr + 5].U_1.V_24.Expr.Tree, nNoStatement, yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 341:;
        case 238:;
          DEC1(yyStackPtr, 8);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_20.Exprs.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 8].U_1.V_1.Scan.Position), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 7].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 342:;
        case 251:;
          DEC1(yyStackPtr, 8);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, yyAttributeStack->A[yyStackPtr + 7].U_1.V_22.Exprs2.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 8].U_1.V_1.Scan.Position), Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 343:;
        case 248:;
          DEC1(yyStackPtr, 9);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_20.Exprs.Tree, yyAttributeStack->A[yyStackPtr + 7].U_1.V_24.Expr.Tree, nNoStatement, yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 344:;
        case 255:;
          DEC1(yyStackPtr, 9);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 9].U_1.V_1.Scan.Position), yyAttributeStack->A[yyStackPtr + 5].U_1.V_24.Expr.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 8].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 345:;
        case 253:;
          DEC1(yyStackPtr, 9);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 9].U_1.V_1.Scan.Position), yyAttributeStack->A[yyStackPtr + 7].U_1.V_24.Expr.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 346:;
        case 249:;
          DEC1(yyStackPtr, 11);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_20.Exprs.Tree, yyAttributeStack->A[yyStackPtr + 7].U_1.V_24.Expr.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 10].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 347:;
        case 244:;
          DEC1(yyStackPtr, 11);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_20.Exprs.Tree, yyAttributeStack->A[yyStackPtr + 9].U_1.V_24.Expr.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 7].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 348:;
        case 252:;
          DEC1(yyStackPtr, 11);
          yyNonterminal = 67;
          yySynAttribute.U_1.V_17.Rules.Tree = mRules(Line, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree, yyAttributeStack->A[yyStackPtr + 7].U_1.V_20.Exprs.Tree, yyAttributeStack->A[yyStackPtr + 9].U_1.V_24.Expr.Tree, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_28.Statements.Tree), yyAttributeStack->A[yyStackPtr + 1].U_1.V_17.Rules.Tree);
          break;
        case 349:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 72;
          Line = Scanner_Attribute.Position;
          break;
        case 350:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 62;
          break;
        case 351:;
        case 192:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 62;
          break;
        case 352:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 74;
          yySynAttribute.U_1.V_18.Patterns.Tree = Tree_mOnePatternsList(yyAttributeStack->A[yyStackPtr + 1].U_1.V_20.Exprs.Tree, nNoPatternsList);
          break;
        case 353:;
        case 282:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 74;
          yySynAttribute.U_1.V_18.Patterns.Tree = Tree_mOnePatternsList(yyAttributeStack->A[yyStackPtr + 1].U_1.V_20.Exprs.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_18.Patterns.Tree);
          break;
        case 354:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 73;
          yySynAttribute.U_1.V_19.Patterns2.Tree = Tree_mOnePatternsList(yyAttributeStack->A[yyStackPtr + 1].U_1.V_20.Exprs.Tree, nNoPatternsList);
          break;
        case 355:;
        case 281:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 73;
          yySynAttribute.U_1.V_19.Patterns2.Tree = Tree_mOnePatternsList(yyAttributeStack->A[yyStackPtr + 1].U_1.V_20.Exprs.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_19.Patterns2.Tree);
          break;
        case 356:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_20.Exprs.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 357:;
        case 225:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_20.Exprs.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 358:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_20.Exprs.Tree = Tree_mOneExpr(yyAttributeStack->A[yyStackPtr + 1].U_1.V_24.Expr.Tree, Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 359:;
        case 271:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_20.Exprs.Tree = Tree_mOneExpr(yyAttributeStack->A[yyStackPtr + 1].U_1.V_24.Expr.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_20.Exprs.Tree);
          break;
        case 360:;
        case 272:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 78;
          yySynAttribute.U_1.V_20.Exprs.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_21.NamedExprs.Tree;
          break;
        case 361:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 79;
          yySynAttribute.U_1.V_21.NamedExprs.Tree = Tree_mNoExpr(Scanner_Attribute.Position);
          break;
        case 362:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 79;
          yySynAttribute.U_1.V_21.NamedExprs.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 363:;
        case 235:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 79;
          yySynAttribute.U_1.V_21.NamedExprs.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 364:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 79;
          yySynAttribute.U_1.V_21.NamedExprs.Tree = Tree_mNamedExpr(yyAttributeStack->A[yyStackPtr + 3].U_1.V_24.Expr.Tree, Tree_mNoExpr(Scanner_Attribute.Position), yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position);
          break;
        case 365:;
        case 275:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 79;
          yySynAttribute.U_1.V_21.NamedExprs.Tree = Tree_mNamedExpr(yyAttributeStack->A[yyStackPtr + 3].U_1.V_24.Expr.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_21.NamedExprs.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position);
          break;
        case 366:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 76;
          yySynAttribute.U_1.V_22.Exprs2.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 367:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 76;
          yySynAttribute.U_1.V_22.Exprs2.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 368:;
        case 277:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 76;
          yySynAttribute.U_1.V_22.Exprs2.Tree = Tree_mOneExpr(yyAttributeStack->A[yyStackPtr + 1].U_1.V_24.Expr.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_22.Exprs2.Tree);
          break;
        case 369:;
        case 278:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 76;
          yySynAttribute.U_1.V_22.Exprs2.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_23.NamedExprs2.Tree;
          break;
        case 370:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 80;
          yySynAttribute.U_1.V_23.NamedExprs2.Tree = Tree_mNoExpr(Scanner_Attribute.Position);
          break;
        case 371:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 80;
          yySynAttribute.U_1.V_23.NamedExprs2.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 372:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 80;
          yySynAttribute.U_1.V_23.NamedExprs2.Tree = Tree_mOneExpr(Tree_mDontCareExplicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position), Tree_mNoExpr(Scanner_Attribute.Position));
          break;
        case 373:;
        case 276:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 80;
          yySynAttribute.U_1.V_23.NamedExprs2.Tree = Tree_mNamedExpr(yyAttributeStack->A[yyStackPtr + 3].U_1.V_24.Expr.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_23.NamedExprs2.Tree, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position);
          break;
        case 374:;
        case 273:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 77;
          yySynAttribute.U_1.V_24.Expr.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_25.PrefixExpr.Tree;
          break;
        case 375:;
        case 270:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 77;
          yySynAttribute.U_1.V_24.Expr.Tree = Tree_mBinary(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_24.Expr.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Operator.Ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_25.PrefixExpr.Tree, FALSE);
          break;
        case 376:;
        case 268:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 77;
          yySynAttribute.U_1.V_24.Expr.Tree = Tree_mBinaryCompound(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_24.Expr.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_2.Operator.Ident, yyAttributeStack->A[yyStackPtr + 4].U_1.V_25.PrefixExpr.Tree, FALSE, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_4.CompoundOperator.Ident);
          break;
        case 377:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 81;
          yySynAttribute.U_1.V_25.PrefixExpr.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree;
          break;
        case 378:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 81;
          yySynAttribute.U_1.V_25.PrefixExpr.Tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_26.PostfixExpr.Tree;
          if (Tree_IsType(yySynAttribute.U_1.V_25.PrefixExpr.Tree, Tree_DontCare1)) {
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_54.DontCare1.Selector = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident;
          } else if (Tree_IsType(yySynAttribute.U_1.V_25.PrefixExpr.Tree, Tree_Expr)) {
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_65.Expr.Selector = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident;
          } else {
            Assertions_CantHappenPos((STRING)"Parser, Label on bad subtree.", 29L, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position);
          }
          break;
        case 379:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 81;
          yySynAttribute.U_1.V_25.PrefixExpr.Tree = yyAttributeStack->A[yyStackPtr + 3].U_1.V_26.PostfixExpr.Tree;
          if (Tree_IsType(yySynAttribute.U_1.V_25.PrefixExpr.Tree, Tree_DontCare1)) {
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_54.DontCare1.Selector = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident;
          } else if (Tree_IsType(yySynAttribute.U_1.V_25.PrefixExpr.Tree, Tree_Expr)) {
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_65.Expr.Selector = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident;
          } else {
            Assertions_CantHappenPos((STRING)"Parser, Label on bad subtree.", 29L, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position);
          }
          switch (yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_1.Kind) {
          case Tree_Compose:;
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_66.Compose.Widen = TRUE;
            break;
          case Tree_Nil:;
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_69.Nil.Widen = TRUE;
            break;
          case Tree_VarUse:;
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_67.VarUse.Widen = TRUE;
            break;
          case Tree_Binary:;
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_71.Binary.Widen = TRUE;
            break;
          case Tree_BinaryCompound:;
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_71.Binary.Widen = TRUE;
            break;
          case Tree_Index:;
            yySynAttribute.U_1.V_25.PrefixExpr.Tree->U_1.V_76.Index.Widen = TRUE;
            break;
          default :
            break;
          }
          break;
        case 380:;
        case 274:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 81;
          yySynAttribute.U_1.V_25.PrefixExpr.Tree = Tree_mPreOperator(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_2.Operator.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_25.PrefixExpr.Tree);
          break;
        case 381:;
        case 267:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 81;
          yySynAttribute.U_1.V_25.PrefixExpr.Tree = Tree_mPreOperator(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_3.IncOperator.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_25.PrefixExpr.Tree);
          break;
        case 382:;
        case 269:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_27.PrimaryExpr.Tree;
          break;
        case 383:;
        case 233:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mIndex(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, Tree_mVarUse(Positions_NoPosition, Idents_NoIdent, Idents_NoIdent, FALSE), yyAttributeStack->A[yyStackPtr + 2].U_1.V_20.Exprs.Tree, FALSE);
          break;
        case 384:;
        case 231:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mIndex(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_20.Exprs.Tree, FALSE);
          break;
        case 385:;
        case 226:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mIndex(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree, yyAttributeStack->A[yyStackPtr + 4].U_1.V_20.Exprs.Tree, FALSE);
          break;
        case 386:;
        case 228:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mCompose(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree, Tree_mNoExpr(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position), FALSE);
          break;
        case 387:;
        case 230:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mCompose(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_20.Exprs.Tree, FALSE);
          break;
        case 388:;
        case 229:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mCall(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree, yyAttributeStack->A[yyStackPtr + 3].U_1.V_20.Exprs.Tree, yyAttributeStack->A[yyStackPtr + 5].U_1.V_20.Exprs.Tree);
          break;
        case 389:;
        case 224:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 82;
          Strings_ArrayToString((STRING)".", 1L, &String1);
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mBinary(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree, Idents_MakeIdent(&String1), Tree_mVarUse(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.Ident.Ident, FALSE), FALSE);
          break;
        case 390:;
        case 227:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 82;
          Strings_ArrayToString((STRING)"->", 2L, &String1);
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mBinary(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree, Idents_MakeIdent(&String1), Tree_mVarUse(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.Ident.Ident, FALSE), FALSE);
          break;
        case 391:;
        case 232:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 82;
          Strings_ArrayToString((STRING)"^", 1L, &String1);
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mPostOperator(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, Idents_MakeIdent(&String1), yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree);
          break;
        case 392:;
        case 223:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 82;
          yySynAttribute.U_1.V_26.PostfixExpr.Tree = Tree_mPostOperator(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_3.IncOperator.Ident, yyAttributeStack->A[yyStackPtr + 1].U_1.V_26.PostfixExpr.Tree);
          break;
        case 393:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mVarUse(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, FALSE);
          break;
        case 394:;
        case 205:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mVarUse(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, Idents_NoIdent, FALSE);
          break;
        case 395:;
        case 206:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mVarUse(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, Idents_NoIdent, TRUE);
          break;
        case 396:;
        case 209:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mNil(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, FALSE);
          break;
        case 397:;
        case 210:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mDontCare1Explicit(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent);
          break;
        case 398:;
        case 208:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = mTargetExpr(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_mAny(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_7.Number.StringRef, nNoDesignator));
          break;
        case 399:;
        case 207:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mStringExpr(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_6.String.StringRef);
          break;
        case 400:;
        case 204:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mAttrDesc(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident, FALSE, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position);
          break;
        case 401:;
        case 221:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = mTargetExpr(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 2].U_1.V_29.TargetCodes.Tree));
          break;
        case 402:;
        case 234:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 83;
          yySynAttribute.U_1.V_27.PrimaryExpr.Tree = Tree_mParents(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position, Idents_NoIdent, yyAttributeStack->A[yyStackPtr + 2].U_1.V_24.Expr.Tree);
          break;
        case 403:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = nNoStatement;
          break;
        case 404:;
        case 246:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = Tree_mProcCall(yyAttributeStack->A[yyStackPtr + 2].U_1.V_24.Expr.Tree->U_1.V_65.Expr.Pos, yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_24.Expr.Tree);
          break;
        case 405:;
        case 247:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = Tree_mAssignment(yyAttributeStack->A[yyStackPtr + 3].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_24.Expr.Tree, yyAttributeStack->A[yyStackPtr + 4].U_1.V_24.Expr.Tree);
          break;
        case 406:;
        case 241:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = Tree_mReject(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree);
          break;
        case 407:;
        case 242:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = Tree_mFail(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree);
          break;
        case 408:;
        case 245:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = mTargetStmt(yyAttributeStack->A[yyStackPtr + 2].U_1.V_14.Declarations.Tree->U_1.V_38.Param.Pos, yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree, yyAttributeStack->A[yyStackPtr + 2].U_1.V_14.Declarations.Tree, nNoDesignator);
          break;
        case 409:;
        case 240:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = mTargetStmt(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree, nNoParameter, Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_29.TargetCodes.Tree));
          break;
        case 410:;
        case 243:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = Tree_mNl(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree);
          break;
        case 411:;
        case 239:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 75;
          yySynAttribute.U_1.V_28.Statements.Tree = yyAttributeStack->A[yyStackPtr + 1].U_1.V_28.Statements.Tree;
          break;
        case 412:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = nNoDesignator;
          break;
        case 413:;
        case 222:;
          DEC1(yyStackPtr, 6);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mDesignator(yyAttributeStack->A[yyStackPtr + 2].U_1.V_31.Name1.Id, yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.U_1.V_1.Ident.Ident, yyAttributeStack->A[yyStackPtr + 2].U_1.V_31.Name1.Position, yyAttributeStack->A[yyStackPtr + 6].U_1.V_1.Scan.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          break;
        case 414:;
          DEC1(yyStackPtr, 5);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mIdent(yyAttributeStack->A[yyStackPtr + 2].U_1.V_31.Name1.Id, yyAttributeStack->A[yyStackPtr + 2].U_1.V_31.Name1.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_32.Space.Tree), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_10.yy10.StringRef, yySynAttribute.U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 5].U_1.V_32.Space.Tree), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          break;
        case 415:;
        case 216:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_11.yy11.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_32.Space.Tree), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(Idents_GetStringRef(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_1.Ident.Ident), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          break;
        case 416:;
        case 217:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_11.yy11.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_32.Space.Tree), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_8.TargetCode.StringRef, yySynAttribute.U_1.V_29.TargetCodes.Tree);
          break;
        case 417:;
        case 219:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_12.yy12.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_32.Space.Tree), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(Idents_GetStringRef(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_1.Ident.Ident), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          break;
        case 418:;
        case 220:;
          DEC1(yyStackPtr, 4);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_12.yy12.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_32.Space.Tree), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 4].U_1.V_1.Scan.U_1.V_8.TargetCode.StringRef, yySynAttribute.U_1.V_29.TargetCodes.Tree);
          break;
        case 419:;
          DEC1(yyStackPtr, 3);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mIdent(yyAttributeStack->A[yyStackPtr + 2].U_1.V_31.Name1.Id, yyAttributeStack->A[yyStackPtr + 2].U_1.V_31.Name1.Position, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAnys(Tree_ReverseTree(yyAttributeStack->A[yyStackPtr + 3].U_1.V_32.Space.Tree), yySynAttribute.U_1.V_29.TargetCodes.Tree);
          break;
        case 420:;
        case 215:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_10.yy10.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          break;
        case 421:;
        case 213:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_8.TargetCode.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          break;
        case 422:;
        case 214:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 84;
          yySynAttribute.U_1.V_29.TargetCodes.Tree = Tree_mAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_9.WhiteSpace.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_29.TargetCodes.Tree);
          break;
        case 423:;
        case 188:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 59;
          yySynAttribute.U_1.V_30.Name0.Id = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident;
          yySynAttribute.U_1.V_30.Name0.Position = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position;
          break;
        case 424:;
        case 189:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 59;
          StringMem_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_6.String.StringRef, &String1);
          Strings_SubString(&String1, 2, (Strings_tStringIndex)(Strings_Length(&String1) - 1), &String2);
          yySynAttribute.U_1.V_30.Name0.Id = Idents_MakeIdent(&String2);
          yySynAttribute.U_1.V_30.Name0.Position = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position;
          break;
        case 425:;
        case 211:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 85;
          yySynAttribute.U_1.V_31.Name1.Id = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_1.Ident.Ident;
          yySynAttribute.U_1.V_31.Name1.Position = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position;
          break;
        case 426:;
        case 212:;
          DEC1(yyStackPtr, 1);
          yyNonterminal = 85;
          StringMem_GetString(yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.U_1.V_6.String.StringRef, &String1);
          yySynAttribute.U_1.V_31.Name1.Id = Idents_MakeIdent(&String1);
          yySynAttribute.U_1.V_31.Name1.Position = yyAttributeStack->A[yyStackPtr + 1].U_1.V_1.Scan.Position;
          break;
        case 427:;
          DEC1(yyStackPtr, 0);
          yyNonterminal = 86;
          yySynAttribute.U_1.V_32.Space.Tree = nNoLayout;
          break;
        case 428:;
        case 218:;
          DEC1(yyStackPtr, 2);
          yyNonterminal = 86;
          yySynAttribute.U_1.V_32.Space.Tree = Tree_mLayoutAny(yyAttributeStack->A[yyStackPtr + 2].U_1.V_1.Scan.U_1.V_9.WhiteSpace.StringRef, yyAttributeStack->A[yyStackPtr + 1].U_1.V_32.Space.Tree);
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
  struct S_49 TokenArray;
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
        DEC1(StackPtr, yyLength.A[State - 283]);
        Nonterminal = yyLeftHandSide.A[State - 283];
      }
      State = Next(Stack->A[StackPtr], Nonterminal);
      if (StackPtr >= VAL(yyStackPtrType, StackSize)) {
        DynArray_ExtendArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
      }
      INC(StackPtr);
      if (State < yyFirstFinalState) {
        goto EXIT_5;
      }
      State = yyFinalToProd.A[State - 188];
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
        State = yyFinalToProd.A[State - 188];
      }
      for (;;) {
        if (State == yyStopState) {
          DynArray_ReleaseArray((ADDRESS *)&Stack, &StackSize, (LONGINT)sizeof(yyStateRange));
          Sets_ReleaseSet(&ContinueSet);
          return;
        } else {
          DEC1(StackPtr, yyLength.A[State - 283]);
          Nonterminal = yyLeftHandSide.A[State - 283];
        }
        State = Next(Stack->A[StackPtr], Nonterminal);
        INC(StackPtr);
        if (State < yyFirstFinalState) {
          goto EXIT_7;
        }
        State = yyFinalToProd.A[State - 188];
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
  struct S_50 TBase;
  struct S_51 NBase;

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
    yyNBasePtr.A[State] = (yyNCombTypePtr)ADR(yyNComb.A[NBase.A[State] - 52]);
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
  NameCount = 0;
  nNoParameter = Tree_mNoParameter();
  nNoName = Tree_mNoName();
  nNoRule = Tree_mNoRule();
  nNoDesignator = Tree_mNoDesignator();
  nNoStatement = Tree_mNoStatement();
  nNoLayout = Tree_mNoLayout();
  nNoPatternsList = Tree_mNoPatternsList();
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
    Tree__init();
    Tree__init();
    Assertions__init();

    yyIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
