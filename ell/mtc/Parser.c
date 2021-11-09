#include "SYSTEM_.h"

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

Parser_tParsAttribute Parser_ParsAttribute;
struct Parser_1 Parser_ParsTabName;

#define eOperIgnored   30
#define ePrecIgnored   31
static Strings_tString String;
#define xxEof   0
typedef struct S_1 *xxtUnionPtr;
typedef struct S_1 {
    xxtUnionPtr GlobalRecoverySet;
    SHORTCARD LocalRecoverySet;
} xxtUnion;
typedef struct S_2 {
    BITSET A[0 + 1];
} xxtSet;
static SHORTCARD xxToken;
static INTEGER xxErrorCount;
static BOOLEAN xxIsInitialized;
static BOOLEAN xxIsRepairMode;
static struct S_3 {
    xxtSet A[51 + 1];
} xxHorizontalSet;
static struct S_4 {
    BITSET A[30 + 1];
} xxVerticalSet0;
static void Copy ARGS((CHAR Source[], LONGCARD , CHAR Target[], LONGCARD ));
static BOOLEAN xxIsElement ARGS((xxtSet *Set, SHORTCARD Element));
static void xxUnexpected ARGS((SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet));
static void xxExpected ARGS((SHORTCARD ExpectedSet, SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet));
struct S_8 {
    CHAR A[127 + 1];
};
static void xxRecoveryLiteral ARGS((SHORTCARD Expected, SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet));
struct S_9 {
    CHAR A[127 + 1];
};
static void xxRecoveryTerminal ARGS((SHORTCARD Expected, SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet, Scanner_tScanAttribute *RepairAttribute));
struct S_10 {
    CHAR A[127 + 1];
};
static void xxSkipTokens ARGS((SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet));
static void BeginParser ARGS(());
static void yyGrammar ARGS((Parser_tParsAttribute *Grammar0, xxtUnionPtr xxGlobalRecoverySet));
static void yyNames ARGS((Parser_tParsAttribute *Names0, xxtUnionPtr xxGlobalRecoverySet));
static void yySections ARGS((Parser_tParsAttribute *Sections0, xxtUnionPtr xxGlobalRecoverySet));
static void yyCodeOption ARGS((Parser_tParsAttribute *CodeOption0, xxtUnionPtr xxGlobalRecoverySet));
static void yyCodeLines ARGS((Parser_tParsAttribute *CodeLines0, xxtUnionPtr xxGlobalRecoverySet));
static void yyTokens ARGS((Parser_tParsAttribute *Tokens0, xxtUnionPtr xxGlobalRecoverySet));
static void yyTokenDecl ARGS((Parser_tParsAttribute *TokenDecl0, xxtUnionPtr xxGlobalRecoverySet));
static void yyOper ARGS((Parser_tParsAttribute *Oper0, xxtUnionPtr xxGlobalRecoverySet));
static void yyRules ARGS((Parser_tParsAttribute *Rules0, xxtUnionPtr xxGlobalRecoverySet));
static void yyRule ARGS((Parser_tParsAttribute *Rule0, xxtUnionPtr xxGlobalRecoverySet));
static void yyLocalOption ARGS((Parser_tParsAttribute *LocalOption0, xxtUnionPtr xxGlobalRecoverySet));
static void yyRightSide ARGS((Parser_tParsAttribute *RightSide0, xxtUnionPtr xxGlobalRecoverySet));
static void yyPrecAlternative ARGS((Parser_tParsAttribute *PrecAlternative0, xxtUnionPtr xxGlobalRecoverySet));
static void yyPrecPart ARGS((Parser_tParsAttribute *PrecPart0, xxtUnionPtr xxGlobalRecoverySet));
static void yyExpression ARGS((Parser_tParsAttribute *Expression0, xxtUnionPtr xxGlobalRecoverySet));
static void yyUnit ARGS((Parser_tParsAttribute *Unit0, xxtUnionPtr xxGlobalRecoverySet));
static void yyAlternative ARGS((Parser_tParsAttribute *Alternative0, xxtUnionPtr xxGlobalRecoverySet));
static void yyExpressions ARGS((Parser_tParsAttribute *Expressions0, xxtUnionPtr xxGlobalRecoverySet));
static void yyId ARGS((Parser_tParsAttribute *Id0, xxtUnionPtr xxGlobalRecoverySet));
static void yyStr ARGS((Parser_tParsAttribute *Str0, xxtUnionPtr xxGlobalRecoverySet));


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

void Parser_xxTokenName
# ifdef __STDC__
(CARDINAL Token, CHAR Name[], LONGCARD O_3)
# else
(Token, Name, O_3)
CARDINAL Token;
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
    Copy((STRING)"COLON", 5L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)"|", 1L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)"ASTERISK", 8L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)"PLUS", 4L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)"DOUBLEBAR", 9L, Name, O_3);
    break;
  case 8:;
    Copy((STRING)"(", 1L, Name, O_3);
    break;
  case 9:;
    Copy((STRING)")", 1L, Name, O_3);
    break;
  case 10:;
    Copy((STRING)"LEFTBRACKET", 11L, Name, O_3);
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
    Copy((STRING)"Number", 6L, Name, O_3);
    break;
  case 25:;
    Copy((STRING)"CodeLine", 8L, Name, O_3);
    break;
  case 26:;
    Copy((STRING)"LastCodeLine", 12L, Name, O_3);
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

INTEGER Parser_Parser
# ifdef __STDC__
()
# else
()
# endif
{
  xxErrorCount = 0;
  BeginParser();
  xxToken = Scanner_GetToken();
  xxIsRepairMode = FALSE;
  yyGrammar(&Parser_ParsAttribute, (xxtUnionPtr)NIL);
  if (xxToken != xxEof) {
    xxRecoveryLiteral(xxEof, 0, (xxtUnionPtr)NIL);
  }
  return xxErrorCount;
}

static BOOLEAN xxIsElement
# ifdef __STDC__
(xxtSet *Set, SHORTCARD Element)
# else
(Set, Element)
xxtSet *Set;
SHORTCARD Element;
# endif
{
  return IN(Element % 32, Set->A[Element / 32]);
}

static void xxUnexpected
# ifdef __STDC__
(SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet)
# else
(LocalRecoverySet, GlobalRecoverySet)
SHORTCARD LocalRecoverySet;
xxtUnionPtr GlobalRecoverySet;
# endif
{
  if (!xxIsRepairMode) {
    INC(xxErrorCount);
    Errors_ErrorMessage((LONGCARD)Errors_SyntaxError, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
    xxSkipTokens(LocalRecoverySet, GlobalRecoverySet);
  }
}

static void xxExpected
# ifdef __STDC__
(SHORTCARD ExpectedSet, SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet)
# else
(ExpectedSet, LocalRecoverySet, GlobalRecoverySet)
SHORTCARD ExpectedSet;
SHORTCARD LocalRecoverySet;
xxtUnionPtr GlobalRecoverySet;
# endif
{
  SHORTCARD Token;
  struct S_8 TokenArray;
  Strings_tString TokenString;
  Strings_tString ContinueString;

  if (!xxIsRepairMode) {
    INC(xxErrorCount);
    Errors_ErrorMessage((LONGCARD)Errors_SyntaxError, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
    Strings_AssignEmpty(&ContinueString);
    for (Token = 0; Token <= 30; Token += 1) {
      if (xxIsElement(&xxHorizontalSet.A[ExpectedSet], Token)) {
        Parser_xxTokenName((LONGCARD)Token, TokenArray.A, 128L);
        Strings_ArrayToString(TokenArray.A, 128L, &TokenString);
        if (Strings_Length(&ContinueString) + Strings_Length(&TokenString) + 1 <= Strings_cMaxStrLength) {
          Strings_Concatenate(&ContinueString, &TokenString);
          Strings_Append(&ContinueString, ' ');
        }
      }
    }
    Errors_ErrorMessageI((LONGCARD)Errors_ExpectedTokens, (LONGCARD)Errors_Information, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(ContinueString));
    xxSkipTokens(LocalRecoverySet, GlobalRecoverySet);
  }
}

static void xxRecoveryLiteral
# ifdef __STDC__
(SHORTCARD Expected, SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet)
# else
(Expected, LocalRecoverySet, GlobalRecoverySet)
SHORTCARD Expected;
SHORTCARD LocalRecoverySet;
xxtUnionPtr GlobalRecoverySet;
# endif
{
  struct S_9 TokenString;

  if (!xxIsRepairMode) {
    INC(xxErrorCount);
    Errors_ErrorMessage((LONGCARD)Errors_SyntaxError, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
    Parser_xxTokenName((LONGCARD)Expected, TokenString.A, 128L);
    Errors_ErrorMessageI((LONGCARD)Errors_ExpectedTokens, (LONGCARD)Errors_Information, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(TokenString));
    xxSkipTokens(LocalRecoverySet, GlobalRecoverySet);
  }
  if (xxToken != Expected) {
    Parser_xxTokenName((LONGCARD)Expected, TokenString.A, 128L);
    Errors_ErrorMessageI((LONGCARD)Errors_TokenInserted, (LONGCARD)Errors_Repair, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(TokenString));
  } else {
    if (xxToken != xxEof) {
      xxToken = Scanner_GetToken();
    }
    xxIsRepairMode = FALSE;
  }
}

static void xxRecoveryTerminal
# ifdef __STDC__
(SHORTCARD Expected, SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet, Scanner_tScanAttribute *RepairAttribute)
# else
(Expected, LocalRecoverySet, GlobalRecoverySet, RepairAttribute)
SHORTCARD Expected;
SHORTCARD LocalRecoverySet;
xxtUnionPtr GlobalRecoverySet;
Scanner_tScanAttribute *RepairAttribute;
# endif
{
  struct S_10 TokenString;

  if (!xxIsRepairMode) {
    INC(xxErrorCount);
    Errors_ErrorMessage((LONGCARD)Errors_SyntaxError, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
    Parser_xxTokenName((LONGCARD)Expected, TokenString.A, 128L);
    Errors_ErrorMessageI((LONGCARD)Errors_ExpectedTokens, (LONGCARD)Errors_Information, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(TokenString));
    xxSkipTokens(LocalRecoverySet, GlobalRecoverySet);
  }
  if (xxToken != Expected) {
    Parser_xxTokenName((LONGCARD)Expected, TokenString.A, 128L);
    Errors_ErrorMessageI((LONGCARD)Errors_TokenInserted, (LONGCARD)Errors_Repair, Scanner_Attribute.Position, (LONGCARD)Errors_Array, ADR(TokenString));
    Scanner_ErrorAttribute((LONGINT)Expected, RepairAttribute);
  } else {
    *RepairAttribute = Scanner_Attribute;
    if (xxToken != xxEof) {
      xxToken = Scanner_GetToken();
    }
    xxIsRepairMode = FALSE;
  }
}

static void xxSkipTokens
# ifdef __STDC__
(SHORTCARD LocalRecoverySet, xxtUnionPtr GlobalRecoverySet)
# else
(LocalRecoverySet, GlobalRecoverySet)
SHORTCARD LocalRecoverySet;
xxtUnionPtr GlobalRecoverySet;
# endif
{
  xxtSet RecoverySet;
  BOOLEAN TokensSkipped;

  RecoverySet = xxHorizontalSet.A[LocalRecoverySet];
  INCL(RecoverySet.A[0], xxEof);
  while (GlobalRecoverySet != NIL) {
    RecoverySet.A[0] = RecoverySet.A[0] | xxHorizontalSet.A[GlobalRecoverySet->LocalRecoverySet].A[0];
    GlobalRecoverySet = GlobalRecoverySet->GlobalRecoverySet;
  }
  TokensSkipped = FALSE;
  while (!xxIsElement(&RecoverySet, xxToken)) {
    xxToken = Scanner_GetToken();
    TokensSkipped = TRUE;
  }
  if (TokensSkipped) {
    Errors_ErrorMessage((LONGCARD)Errors_RestartPoint, (LONGCARD)Errors_Information, Scanner_Attribute.Position);
  }
  xxIsRepairMode = TRUE;
}

static void BeginParser
# ifdef __STDC__
()
# else
()
# endif
{
  System_tFile xxTableFile;
  CARDINAL xxSize;

  if (xxIsInitialized) {
    return;
  }
  Scanner_BeginScanner();
  xxTableFile = OpenInput(Parser_ParsTabName.A, 129L);
  if (xxTableFile < 0) {
    Errors_ErrorMessage((LONGCARD)Errors_ReadParseTable, (LONGCARD)Errors_Fatal, Positions_NoPosition);
  }
  xxSize = Read(xxTableFile, ADR(xxHorizontalSet), (LONGINT)sizeof(xxHorizontalSet));
  if (xxSize != sizeof(xxHorizontalSet)) {
    Errors_ErrorMessage((LONGCARD)Errors_ReadParseTable, (LONGCARD)Errors_Fatal, Positions_NoPosition);
  }
  xxSize = Read(xxTableFile, ADR(xxVerticalSet0), (LONGINT)sizeof(xxVerticalSet0));
  if (xxSize != sizeof(xxVerticalSet0)) {
    Errors_ErrorMessage((LONGCARD)Errors_ReadParseTable, (LONGCARD)Errors_Fatal, Positions_NoPosition);
  }
  Close(xxTableFile);
  xxIsInitialized = TRUE;
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

static void yyGrammar
# ifdef __STDC__
(Parser_tParsAttribute *Grammar0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Grammar0, xxGlobalRecoverySet)
Parser_tParsAttribute *Grammar0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute Names1;
  Parser_tParsAttribute Sections1;
  Parser_tParsAttribute Tokens1;
  Parser_tParsAttribute Oper1;
  Parser_tParsAttribute Rules1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  xxUnion.LocalRecoverySet = 1;
  yyNames(&Names1, (xxtUnionPtr)ADR(xxUnion));
  xxUnion.LocalRecoverySet = 2;
  yySections(&Sections1, (xxtUnionPtr)ADR(xxUnion));
  xxUnion.LocalRecoverySet = 3;
  yyTokens(&Tokens1, (xxtUnionPtr)ADR(xxUnion));
  xxUnion.LocalRecoverySet = 4;
  yyOper(&Oper1, (xxtUnionPtr)ADR(xxUnion));
  xxUnion.LocalRecoverySet = 0;
  yyRules(&Rules1, (xxtUnionPtr)ADR(xxUnion));
  Tree_TreeRoot = Tree_mGrammar(Sections1, Tokens1, Rules1);
}

static void yyNames
# ifdef __STDC__
(Parser_tParsAttribute *Names0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Names0, xxGlobalRecoverySet)
Parser_tParsAttribute *Names0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute Identifier1, Identifier2;
  Scanner_tScanAttribute SCANNER1;
  Scanner_tScanAttribute PARSER1;

  for (;;) {
    if (xxToken == 29) {
      SCANNER1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      Strings_ArrayToString((STRING)"Scanner", 7L, &String);
      Tree_ScannerName = Idents_MakeIdent(&String);
      for (;;) {
        if (xxToken == 27) {
          Identifier1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          Tree_ScannerName = Identifier1.U_1.V_2.ident;
          goto EXIT_2;
        } else if (IN(0, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
          goto EXIT_2;
        }
        xxExpected(7, 7, xxGlobalRecoverySet);
      } EXIT_2:;
      goto EXIT_1;
    } else if (IN(0, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
      goto EXIT_1;
    }
    xxExpected(5, 5, xxGlobalRecoverySet);
  } EXIT_1:;
  for (;;) {
    if (xxToken == 30) {
      PARSER1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      for (;;) {
        if (xxToken == 27) {
          Identifier2 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          Tree_ParserName = Identifier2.U_1.V_2.ident;
          goto EXIT_4;
        } else if (IN(1, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
          goto EXIT_4;
        }
        xxExpected(9, 9, xxGlobalRecoverySet);
      } EXIT_4:;
      goto EXIT_3;
    } else if (IN(1, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
      goto EXIT_3;
    }
    xxExpected(8, 8, xxGlobalRecoverySet);
  } EXIT_3:;
}

static void yySections
# ifdef __STDC__
(Parser_tParsAttribute *Sections0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Sections0, xxGlobalRecoverySet)
Parser_tParsAttribute *Sections0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute EXPORT1;
  Scanner_tScanAttribute GLOBAL1;
  Scanner_tScanAttribute LOCAL1;
  Scanner_tScanAttribute BEGIN1;
  Scanner_tScanAttribute CLOSE1;
  Parser_tParsAttribute CodeOption1, CodeOption2, CodeOption3, CodeOption4, CodeOption5;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  *Sections0 = Tree_mSections0();
  for (;;) {
    if (IN(2, xxVerticalSet0.A[xxToken])) {
      for (;;) {
        switch (xxToken) {
        case 12:;
          EXPORT1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          xxUnion.LocalRecoverySet = 0;
          yyCodeOption(&CodeOption1, (xxtUnionPtr)ADR(xxUnion));
          *Sections0 = Tree_mSections(*Sections0, Tree_mExport(CodeOption1));
          goto EXIT_6;
          break;
        case 13:;
          GLOBAL1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          xxUnion.LocalRecoverySet = 0;
          yyCodeOption(&CodeOption2, (xxtUnionPtr)ADR(xxUnion));
          *Sections0 = Tree_mSections(*Sections0, Tree_mGlobal(CodeOption2));
          goto EXIT_6;
          break;
        case 14:;
          LOCAL1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          xxUnion.LocalRecoverySet = 0;
          yyCodeOption(&CodeOption3, (xxtUnionPtr)ADR(xxUnion));
          *Sections0 = Tree_mSections(*Sections0, Tree_mLocal(CodeOption3));
          goto EXIT_6;
          break;
        case 15:;
          BEGIN1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          xxUnion.LocalRecoverySet = 0;
          yyCodeOption(&CodeOption4, (xxtUnionPtr)ADR(xxUnion));
          *Sections0 = Tree_mSections(*Sections0, Tree_mBegin(CodeOption4));
          goto EXIT_6;
          break;
        case 16:;
          CLOSE1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          xxUnion.LocalRecoverySet = 0;
          yyCodeOption(&CodeOption5, (xxtUnionPtr)ADR(xxUnion));
          *Sections0 = Tree_mSections(*Sections0, Tree_mClose(CodeOption5));
          goto EXIT_6;
          break;
        default :
          if (xxIsRepairMode) {
            if (xxToken != 12) {
              xxRecoveryTerminal(12, 11, xxGlobalRecoverySet, &EXPORT1);
            } else {
              EXPORT1 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
            }
            xxUnion.LocalRecoverySet = 0;
            yyCodeOption(&CodeOption1, (xxtUnionPtr)ADR(xxUnion));
            *Sections0 = Tree_mSections(*Sections0, Tree_mExport(CodeOption1));
            goto EXIT_6;
          }
          xxExpected(10, 10, xxGlobalRecoverySet);
          break;
        }
      } EXIT_6:;
    } else if (xxToken == 17 || xxIsRepairMode) {
      goto EXIT_5;
    } else {
      xxExpected(10, 10, xxGlobalRecoverySet);
    }
  } EXIT_5:;
  *Sections0 = Tree_ReverseTree(*Sections0);
}

static void yyCodeOption
# ifdef __STDC__
(Parser_tParsAttribute *CodeOption0, xxtUnionPtr xxGlobalRecoverySet)
# else
(CodeOption0, xxGlobalRecoverySet)
Parser_tParsAttribute *CodeOption0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute CodeLines1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 25:;
    case 26:;
      xxUnion.LocalRecoverySet = 0;
      yyCodeLines(&CodeLines1, (xxtUnionPtr)ADR(xxUnion));
      *CodeOption0 = CodeLines1;
      goto EXIT_7;
      break;
    case 12:;
    case 13:;
    case 14:;
    case 15:;
    case 16:;
    case 17:;
      *CodeOption0 = Tree_mCodes0();
      goto EXIT_7;
      break;
    default :
      if (xxIsRepairMode) {
        *CodeOption0 = Tree_mCodes0();
        goto EXIT_7;
      }
      xxUnexpected(16, xxGlobalRecoverySet);
      break;
    }
  } EXIT_7:;
}

static void yyCodeLines
# ifdef __STDC__
(Parser_tParsAttribute *CodeLines0, xxtUnionPtr xxGlobalRecoverySet)
# else
(CodeLines0, xxGlobalRecoverySet)
Parser_tParsAttribute *CodeLines0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute CodeLine1;
  Scanner_tScanAttribute LastCodeLine1;

  *CodeLines0 = Tree_mCodes0();
  for (;;) {
    if (xxToken == 25) {
      CodeLine1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      *CodeLines0 = Tree_mCodes(*CodeLines0, Tree_mCode(CodeLine1.Position, CodeLine1.U_1.V_3.ref));
    } else if (xxToken == 26 || xxIsRepairMode) {
      goto EXIT_8;
    } else {
      xxExpected(16, 16, xxGlobalRecoverySet);
    }
  } EXIT_8:;
  if (xxToken != 26) {
    xxRecoveryTerminal(26, 17, xxGlobalRecoverySet, &LastCodeLine1);
  } else {
    LastCodeLine1 = Scanner_Attribute;
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  *CodeLines0 = Tree_mCodes(*CodeLines0, Tree_mCode(LastCodeLine1.Position, LastCodeLine1.U_1.V_3.ref));
  *CodeLines0 = Tree_ReverseTree(*CodeLines0);
}

static void yyTokens
# ifdef __STDC__
(Parser_tParsAttribute *Tokens0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Tokens0, xxGlobalRecoverySet)
Parser_tParsAttribute *Tokens0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute TOKEN1;
  Parser_tParsAttribute TokenDecl1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  if (xxToken != 17) {
    xxRecoveryTerminal(17, 18, xxGlobalRecoverySet, &TOKEN1);
  } else {
    TOKEN1 = Scanner_Attribute;
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  *Tokens0 = Tree_mTokens0();
  for (;;) {
    if (IN(3, xxVerticalSet0.A[xxToken])) {
      xxUnion.LocalRecoverySet = 0;
      yyTokenDecl(&TokenDecl1, (xxtUnionPtr)ADR(xxUnion));
      *Tokens0 = Tree_mTokens(*Tokens0, TokenDecl1);
    } else if (IN(4, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
      goto EXIT_9;
    } else {
      xxExpected(19, 19, xxGlobalRecoverySet);
    }
  } EXIT_9:;
  *Tokens0 = Tree_ReverseTree(*Tokens0);
}

static void yyTokenDecl
# ifdef __STDC__
(Parser_tParsAttribute *TokenDecl0, xxtUnionPtr xxGlobalRecoverySet)
# else
(TokenDecl0, xxGlobalRecoverySet)
Parser_tParsAttribute *TokenDecl0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute Number1;
  Parser_tParsAttribute Id1;
  Parser_tParsAttribute Str1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 27:;
      xxUnion.LocalRecoverySet = 20;
      yyId(&Id1, (xxtUnionPtr)ADR(xxUnion));
      *TokenDecl0 = Id1;
      goto EXIT_10;
      break;
    case 28:;
      xxUnion.LocalRecoverySet = 20;
      yyStr(&Str1, (xxtUnionPtr)ADR(xxUnion));
      *TokenDecl0 = Str1;
      goto EXIT_10;
      break;
    default :
      if (xxIsRepairMode) {
        xxUnion.LocalRecoverySet = 20;
        yyId(&Id1, (xxtUnionPtr)ADR(xxUnion));
        *TokenDecl0 = Id1;
        goto EXIT_10;
      }
      xxExpected(21, 21, xxGlobalRecoverySet);
      break;
    }
  } EXIT_10:;
  for (;;) {
    switch (xxToken) {
    case 1:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      if (xxToken != 24) {
        xxRecoveryTerminal(24, 23, xxGlobalRecoverySet, &Number1);
      } else {
        Number1 = Scanner_Attribute;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
      }
      *TokenDecl0 = Tree_mToken(*TokenDecl0, Tree_mNumber(Number1.Position, Number1.U_1.V_1.value));
      goto EXIT_11;
      break;
    case 18:;
    case 22:;
    case 27:;
    case 28:;
      *TokenDecl0 = Tree_mToken(*TokenDecl0, Tree_mNumber(Scanner_Attribute.Position, (LONGINT)Scanner_NoValue));
      goto EXIT_11;
      break;
    default :
      if (xxIsRepairMode) {
        *TokenDecl0 = Tree_mToken(*TokenDecl0, Tree_mNumber(Scanner_Attribute.Position, (LONGINT)Scanner_NoValue));
        goto EXIT_11;
      }
      xxUnexpected(20, xxGlobalRecoverySet);
      break;
    }
  } EXIT_11:;
}

static void yyOper
# ifdef __STDC__
(Parser_tParsAttribute *Oper0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Oper0, xxGlobalRecoverySet)
Parser_tParsAttribute *Oper0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute OPER1;
  Scanner_tScanAttribute NONE1;
  Scanner_tScanAttribute LEFT1;
  Scanner_tScanAttribute RIGHT1;
  Scanner_tScanAttribute Identifier1;
  Scanner_tScanAttribute String1;

  for (;;) {
    if (xxToken == 18) {
      OPER1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      for (;;) {
        if (IN(5, xxVerticalSet0.A[xxToken])) {
          for (;;) {
            switch (xxToken) {
            case 20:;
              LEFT1 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
              goto EXIT_14;
              break;
            case 21:;
              RIGHT1 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
              goto EXIT_14;
              break;
            case 19:;
              NONE1 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
              goto EXIT_14;
              break;
            default :
              if (xxIsRepairMode) {
                if (xxToken != 20) {
                  xxRecoveryTerminal(20, 27, xxGlobalRecoverySet, &LEFT1);
                } else {
                  LEFT1 = Scanner_Attribute;
                  xxToken = Scanner_GetToken();
                  xxIsRepairMode = FALSE;
                }
                goto EXIT_14;
              }
              xxExpected(30, 30, xxGlobalRecoverySet);
              break;
            }
          } EXIT_14:;
          for (;;) {
            for (;;) {
              switch (xxToken) {
              case 27:;
                Identifier1 = Scanner_Attribute;
                xxToken = Scanner_GetToken();
                xxIsRepairMode = FALSE;
                goto EXIT_16;
                break;
              case 28:;
                String1 = Scanner_Attribute;
                xxToken = Scanner_GetToken();
                xxIsRepairMode = FALSE;
                goto EXIT_16;
                break;
              default :
                if (xxIsRepairMode) {
                  if (xxToken != 27) {
                    xxRecoveryTerminal(27, 9, xxGlobalRecoverySet, &Identifier1);
                  } else {
                    Identifier1 = Scanner_Attribute;
                    xxToken = Scanner_GetToken();
                    xxIsRepairMode = FALSE;
                  }
                  goto EXIT_16;
                }
                xxExpected(19, 19, xxGlobalRecoverySet);
                break;
              }
            } EXIT_16:;
            if (!IN(3, xxVerticalSet0.A[xxToken])) {
              if (IN(6, xxVerticalSet0.A[xxToken])) {
                goto EXIT_15;
              }
              xxExpected(19, 19, xxGlobalRecoverySet);
              if (!IN(3, xxVerticalSet0.A[xxToken])) {
                goto EXIT_15;
              }
            }
          } EXIT_15:;
        } else if (xxToken == 22 || xxIsRepairMode) {
          goto EXIT_13;
        } else {
          xxExpected(26, 26, xxGlobalRecoverySet);
        }
      } EXIT_13:;
      Errors_ErrorMessage((LONGCARD)eOperIgnored, (LONGCARD)Errors_eWarning, OPER1.Position);
      goto EXIT_12;
    } else if (xxToken == 22 || xxIsRepairMode) {
      goto EXIT_12;
    }
    xxExpected(24, 24, xxGlobalRecoverySet);
  } EXIT_12:;
}

static void yyRules
# ifdef __STDC__
(Parser_tParsAttribute *Rules0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Rules0, xxGlobalRecoverySet)
Parser_tParsAttribute *Rules0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute RULE1;
  Parser_tParsAttribute Rule1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  if (xxToken != 22) {
    xxRecoveryTerminal(22, 32, xxGlobalRecoverySet, &RULE1);
  } else {
    RULE1 = Scanner_Attribute;
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  *Rules0 = Tree_mRules0();
  for (;;) {
    if (xxToken == 27) {
      xxUnion.LocalRecoverySet = 0;
      yyRule(&Rule1, (xxtUnionPtr)ADR(xxUnion));
      *Rules0 = Tree_mRules(*Rules0, Rule1);
    } else if (xxToken == 0 || xxIsRepairMode) {
      goto EXIT_17;
    } else {
      xxExpected(9, 9, xxGlobalRecoverySet);
    }
  } EXIT_17:;
  *Rules0 = Tree_ReverseTree(*Rules0);
}

static void yyRule
# ifdef __STDC__
(Parser_tParsAttribute *Rule0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Rule0, xxGlobalRecoverySet)
Parser_tParsAttribute *Rule0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute COLON1;
  Parser_tParsAttribute Id1;
  Parser_tParsAttribute LocalOption1;
  Parser_tParsAttribute RightSide1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  xxUnion.LocalRecoverySet = 33;
  yyId(&Id1, (xxtUnionPtr)ADR(xxUnion));
  if (xxToken != 2) {
    xxRecoveryTerminal(2, 33, xxGlobalRecoverySet, &COLON1);
  } else {
    COLON1 = Scanner_Attribute;
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  xxUnion.LocalRecoverySet = 34;
  yyLocalOption(&LocalOption1, (xxtUnionPtr)ADR(xxUnion));
  xxUnion.LocalRecoverySet = 35;
  yyRightSide(&RightSide1, (xxtUnionPtr)ADR(xxUnion));
  if (xxToken != 3) {
    xxRecoveryLiteral(3, 35, xxGlobalRecoverySet);
  } else {
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  *Rule0 = Tree_mRule(COLON1.Position, Id1, LocalOption1, RightSide1);
}

static void yyLocalOption
# ifdef __STDC__
(Parser_tParsAttribute *LocalOption0, xxtUnionPtr xxGlobalRecoverySet)
# else
(LocalOption0, xxGlobalRecoverySet)
Parser_tParsAttribute *LocalOption0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute LOCAL1;
  Parser_tParsAttribute CodeLines1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 14:;
      LOCAL1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      xxUnion.LocalRecoverySet = 0;
      yyCodeLines(&CodeLines1, (xxtUnionPtr)ADR(xxUnion));
      *LocalOption0 = CodeLines1;
      goto EXIT_18;
      break;
    case 3:;
    case 4:;
    case 8:;
    case 10:;
    case 23:;
    case 25:;
    case 26:;
    case 27:;
    case 28:;
      *LocalOption0 = Tree_mCodes0();
      goto EXIT_18;
      break;
    default :
      if (xxIsRepairMode) {
        *LocalOption0 = Tree_mCodes0();
        goto EXIT_18;
      }
      xxUnexpected(36, xxGlobalRecoverySet);
      break;
    }
  } EXIT_18:;
}

static void yyRightSide
# ifdef __STDC__
(Parser_tParsAttribute *RightSide0, xxtUnionPtr xxGlobalRecoverySet)
# else
(RightSide0, xxGlobalRecoverySet)
Parser_tParsAttribute *RightSide0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute PrecAlternative1, PrecAlternative2;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  xxUnion.LocalRecoverySet = 37;
  yyPrecAlternative(&PrecAlternative1, (xxtUnionPtr)ADR(xxUnion));
  *RightSide0 = PrecAlternative1;
  for (;;) {
    if (xxToken == 4) {
      *RightSide0 = Tree_mAlternative(PrecAlternative1->U_1.V_32.expr.pos, Tree_mAlternative0(Scanner_Attribute.Position), PrecAlternative1);
      for (;;) {
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        xxUnion.LocalRecoverySet = 0;
        yyPrecAlternative(&PrecAlternative2, (xxtUnionPtr)ADR(xxUnion));
        *RightSide0 = Tree_mAlternative(PrecAlternative2->U_1.V_32.expr.pos, *RightSide0, PrecAlternative2);
        if (!(xxToken == 4)) {
          if (xxToken == 3) {
            goto EXIT_20;
          }
          xxExpected(37, 37, xxGlobalRecoverySet);
          if (!(xxToken == 4)) {
            goto EXIT_20;
          }
        }
      } EXIT_20:;
      *RightSide0 = Tree_ReverseTree(*RightSide0);
      goto EXIT_19;
    } else if (xxToken == 3 || xxIsRepairMode) {
      goto EXIT_19;
    }
    xxExpected(37, 37, xxGlobalRecoverySet);
  } EXIT_19:;
}

static void yyPrecAlternative
# ifdef __STDC__
(Parser_tParsAttribute *PrecAlternative0, xxtUnionPtr xxGlobalRecoverySet)
# else
(PrecAlternative0, xxGlobalRecoverySet)
Parser_tParsAttribute *PrecAlternative0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute Expression1, Expression2;
  Parser_tParsAttribute PrecPart1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 3:;
    case 4:;
    case 23:;
      *PrecAlternative0 = Tree_mSequence0(Scanner_Attribute.Position);
      goto EXIT_21;
      break;
    case 8:;
    case 10:;
    case 25:;
    case 26:;
    case 27:;
    case 28:;
      xxUnion.LocalRecoverySet = 39;
      yyExpression(&Expression1, (xxtUnionPtr)ADR(xxUnion));
      *PrecAlternative0 = Expression1;
      for (;;) {
        if (IN(7, xxVerticalSet0.A[xxToken])) {
          *PrecAlternative0 = Tree_mSequence(Expression1->U_1.V_32.expr.pos, Tree_mSequence0(Scanner_Attribute.Position), Expression1);
          for (;;) {
            xxUnion.LocalRecoverySet = 40;
            yyExpression(&Expression2, (xxtUnionPtr)ADR(xxUnion));
            *PrecAlternative0 = Tree_mSequence(Expression2->U_1.V_32.expr.pos, *PrecAlternative0, Expression2);
            if (!IN(7, xxVerticalSet0.A[xxToken])) {
              if (IN(8, xxVerticalSet0.A[xxToken])) {
                goto EXIT_23;
              }
              xxExpected(39, 39, xxGlobalRecoverySet);
              if (!IN(7, xxVerticalSet0.A[xxToken])) {
                goto EXIT_23;
              }
            }
          } EXIT_23:;
          *PrecAlternative0 = Tree_ReverseTree(*PrecAlternative0);
          goto EXIT_22;
        } else if (IN(8, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
          goto EXIT_22;
        }
        xxExpected(39, 39, xxGlobalRecoverySet);
      } EXIT_22:;
      goto EXIT_21;
      break;
    default :
      if (xxIsRepairMode) {
        *PrecAlternative0 = Tree_mSequence0(Scanner_Attribute.Position);
        goto EXIT_21;
      }
      xxExpected(39, 39, xxGlobalRecoverySet);
      break;
    }
  } EXIT_21:;
  xxUnion.LocalRecoverySet = 0;
  yyPrecPart(&PrecPart1, (xxtUnionPtr)ADR(xxUnion));
}

static void yyPrecPart
# ifdef __STDC__
(Parser_tParsAttribute *PrecPart0, xxtUnionPtr xxGlobalRecoverySet)
# else
(PrecPart0, xxGlobalRecoverySet)
Parser_tParsAttribute *PrecPart0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute PREC1;
  Scanner_tScanAttribute Identifier1;
  Scanner_tScanAttribute String1;

  for (;;) {
    if (xxToken == 23) {
      PREC1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      for (;;) {
        switch (xxToken) {
        case 27:;
          Identifier1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          goto EXIT_25;
          break;
        case 28:;
          String1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          goto EXIT_25;
          break;
        default :
          if (xxIsRepairMode) {
            if (xxToken != 27) {
              xxRecoveryTerminal(27, 9, xxGlobalRecoverySet, &Identifier1);
            } else {
              Identifier1 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
            }
            goto EXIT_25;
          }
          xxExpected(19, 19, xxGlobalRecoverySet);
          break;
        }
      } EXIT_25:;
      Errors_ErrorMessage((LONGCARD)ePrecIgnored, (LONGCARD)Errors_eWarning, PREC1.Position);
      goto EXIT_24;
    } else if (IN(9, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
      goto EXIT_24;
    }
    xxExpected(40, 40, xxGlobalRecoverySet);
  } EXIT_24:;
}

static void yyExpression
# ifdef __STDC__
(Parser_tParsAttribute *Expression0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Expression0, xxGlobalRecoverySet)
Parser_tParsAttribute *Expression0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute ASTERISK1;
  Scanner_tScanAttribute PLUS1;
  Scanner_tScanAttribute DOUBLEBAR1;
  Parser_tParsAttribute Unit1, Unit2;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  xxUnion.LocalRecoverySet = 42;
  yyUnit(&Unit1, (xxtUnionPtr)ADR(xxUnion));
  for (;;) {
    switch (xxToken) {
    case 5:;
      ASTERISK1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      *Expression0 = Tree_mTimes(ASTERISK1.Position, Unit1);
      goto EXIT_26;
      break;
    case 6:;
      PLUS1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      *Expression0 = Tree_mPlus(PLUS1.Position, Unit1);
      goto EXIT_26;
      break;
    case 7:;
      DOUBLEBAR1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      xxUnion.LocalRecoverySet = 0;
      yyUnit(&Unit2, (xxtUnionPtr)ADR(xxUnion));
      *Expression0 = Tree_mList(DOUBLEBAR1.Position, Unit1, Unit2);
      goto EXIT_26;
      break;
    case 3:;
    case 4:;
    case 8:;
    case 9:;
    case 10:;
    case 11:;
    case 23:;
    case 25:;
    case 26:;
    case 27:;
    case 28:;
      *Expression0 = Unit1;
      goto EXIT_26;
      break;
    default :
      if (xxIsRepairMode) {
        *Expression0 = Unit1;
        goto EXIT_26;
      }
      xxUnexpected(42, xxGlobalRecoverySet);
      break;
    }
  } EXIT_26:;
}

static void yyUnit
# ifdef __STDC__
(Parser_tParsAttribute *Unit0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Unit0, xxGlobalRecoverySet)
Parser_tParsAttribute *Unit0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute LEFTBRACKET1;
  Parser_tParsAttribute CodeLines1;
  Parser_tParsAttribute Id1;
  Parser_tParsAttribute Str1;
  Parser_tParsAttribute Alternative1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 10:;
      LEFTBRACKET1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      xxUnion.LocalRecoverySet = 47;
      yyAlternative(&Alternative1, (xxtUnionPtr)ADR(xxUnion));
      if (xxToken != 11) {
        xxRecoveryLiteral(11, 47, xxGlobalRecoverySet);
      } else {
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
      }
      *Unit0 = Tree_mOption(LEFTBRACKET1.Position, Alternative1);
      goto EXIT_27;
      break;
    case 8:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      xxUnion.LocalRecoverySet = 49;
      yyAlternative(&Alternative1, (xxtUnionPtr)ADR(xxUnion));
      if (xxToken != 9) {
        xxRecoveryLiteral(9, 49, xxGlobalRecoverySet);
      } else {
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
      }
      *Unit0 = Alternative1;
      goto EXIT_27;
      break;
    case 27:;
      xxUnion.LocalRecoverySet = 0;
      yyId(&Id1, (xxtUnionPtr)ADR(xxUnion));
      *Unit0 = Tree_mLeaf(Id1->U_1.V_23.Id.pos, Id1);
      goto EXIT_27;
      break;
    case 28:;
      xxUnion.LocalRecoverySet = 0;
      yyStr(&Str1, (xxtUnionPtr)ADR(xxUnion));
      *Unit0 = Tree_mLeaf(Str1->U_1.V_23.Id.pos, Str1);
      goto EXIT_27;
      break;
    case 25:;
    case 26:;
      xxUnion.LocalRecoverySet = 0;
      yyCodeLines(&CodeLines1, (xxtUnionPtr)ADR(xxUnion));
      *Unit0 = Tree_mAction(CodeLines1->U_1.V_15.Codes.code->U_1.V_16.Code.pos, CodeLines1);
      goto EXIT_27;
      break;
    default :
      if (xxIsRepairMode) {
        xxUnion.LocalRecoverySet = 0;
        yyId(&Id1, (xxtUnionPtr)ADR(xxUnion));
        *Unit0 = Tree_mLeaf(Id1->U_1.V_23.Id.pos, Id1);
        goto EXIT_27;
      }
      xxExpected(50, 50, xxGlobalRecoverySet);
      break;
    }
  } EXIT_27:;
}

static void yyAlternative
# ifdef __STDC__
(Parser_tParsAttribute *Alternative0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Alternative0, xxGlobalRecoverySet)
Parser_tParsAttribute *Alternative0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute Expressions1, Expressions2;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  xxUnion.LocalRecoverySet = 37;
  yyExpressions(&Expressions1, (xxtUnionPtr)ADR(xxUnion));
  *Alternative0 = Expressions1;
  for (;;) {
    if (xxToken == 4) {
      *Alternative0 = Tree_mAlternative(Expressions1->U_1.V_32.expr.pos, Tree_mAlternative0(Scanner_Attribute.Position), Expressions1);
      for (;;) {
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        xxUnion.LocalRecoverySet = 0;
        yyExpressions(&Expressions2, (xxtUnionPtr)ADR(xxUnion));
        *Alternative0 = Tree_mAlternative(Expressions2->U_1.V_32.expr.pos, *Alternative0, Expressions2);
        if (!(xxToken == 4)) {
          if (IN(10, xxVerticalSet0.A[xxToken])) {
            goto EXIT_29;
          }
          xxExpected(37, 37, xxGlobalRecoverySet);
          if (!(xxToken == 4)) {
            goto EXIT_29;
          }
        }
      } EXIT_29:;
      *Alternative0 = Tree_ReverseTree(*Alternative0);
      goto EXIT_28;
    } else if (IN(10, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
      goto EXIT_28;
    }
    xxExpected(37, 37, xxGlobalRecoverySet);
  } EXIT_28:;
}

static void yyExpressions
# ifdef __STDC__
(Parser_tParsAttribute *Expressions0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Expressions0, xxGlobalRecoverySet)
Parser_tParsAttribute *Expressions0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute Expression1, Expression2;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 4:;
    case 9:;
    case 11:;
      *Expressions0 = Tree_mSequence0(Scanner_Attribute.Position);
      goto EXIT_30;
      break;
    case 8:;
    case 10:;
    case 25:;
    case 26:;
    case 27:;
    case 28:;
      xxUnion.LocalRecoverySet = 50;
      yyExpression(&Expression1, (xxtUnionPtr)ADR(xxUnion));
      *Expressions0 = Expression1;
      for (;;) {
        if (IN(7, xxVerticalSet0.A[xxToken])) {
          *Expressions0 = Tree_mSequence(Expression1->U_1.V_32.expr.pos, Tree_mSequence0(Scanner_Attribute.Position), Expression1);
          for (;;) {
            xxUnion.LocalRecoverySet = 0;
            yyExpression(&Expression2, (xxtUnionPtr)ADR(xxUnion));
            *Expressions0 = Tree_mSequence(Expression2->U_1.V_32.expr.pos, *Expressions0, Expression2);
            if (!IN(7, xxVerticalSet0.A[xxToken])) {
              if (IN(11, xxVerticalSet0.A[xxToken])) {
                goto EXIT_32;
              }
              xxExpected(50, 50, xxGlobalRecoverySet);
              if (!IN(7, xxVerticalSet0.A[xxToken])) {
                goto EXIT_32;
              }
            }
          } EXIT_32:;
          *Expressions0 = Tree_ReverseTree(*Expressions0);
          goto EXIT_31;
        } else if (IN(11, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
          goto EXIT_31;
        }
        xxExpected(50, 50, xxGlobalRecoverySet);
      } EXIT_31:;
      goto EXIT_30;
      break;
    default :
      if (xxIsRepairMode) {
        *Expressions0 = Tree_mSequence0(Scanner_Attribute.Position);
        goto EXIT_30;
      }
      xxUnexpected(50, xxGlobalRecoverySet);
      break;
    }
  } EXIT_30:;
}

static void yyId
# ifdef __STDC__
(Parser_tParsAttribute *Id0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Id0, xxGlobalRecoverySet)
Parser_tParsAttribute *Id0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute Identifier1;

  if (xxToken != 27) {
    xxRecoveryTerminal(27, 9, xxGlobalRecoverySet, &Identifier1);
  } else {
    Identifier1 = Scanner_Attribute;
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  *Id0 = Tree_mId(Identifier1.Position, Identifier1.U_1.V_2.ident, FALSE);
}

static void yyStr
# ifdef __STDC__
(Parser_tParsAttribute *Str0, xxtUnionPtr xxGlobalRecoverySet)
# else
(Str0, xxGlobalRecoverySet)
Parser_tParsAttribute *Str0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute String1;

  if (xxToken != 28) {
    xxRecoveryTerminal(28, 31, xxGlobalRecoverySet, &String1);
  } else {
    String1 = Scanner_Attribute;
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  *Str0 = Tree_mId(String1.Position, String1.U_1.V_2.ident, TRUE);
}

void Parser__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Tree__init();
    Positions__init();
    Errors__init();
    Scanner__init();
    Strings__init();
    System__init();
    Idents__init();
    Strings__init();
    Errors__init();
    Scanner__init();
    Tree__init();

    xxIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
