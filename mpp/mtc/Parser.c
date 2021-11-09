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

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

Parser_tParsAttribute Parser_ParsAttribute;
struct Parser_1 Parser_ParsTabName;

#define cTab   '\t'
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
    xxtSet A[25 + 1];
} xxHorizontalSet;
static struct S_4 {
    BITSET A[12 + 1];
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
static void yyinput ARGS((Parser_tParsAttribute *input0, xxtUnionPtr xxGlobalRecoverySet));
static void yyline ARGS((Parser_tParsAttribute *line0, xxtUnionPtr xxGlobalRecoverySet));
static void yydefinition ARGS((Parser_tParsAttribute *definition0, xxtUnionPtr xxGlobalRecoverySet));
static void yyusage ARGS((Parser_tParsAttribute *usage0, xxtUnionPtr xxGlobalRecoverySet));
static void yynormal ARGS((Parser_tParsAttribute *normal0, xxtUnionPtr xxGlobalRecoverySet));
static void yybl ARGS((Parser_tParsAttribute *bl0, xxtUnionPtr xxGlobalRecoverySet));
static void yyuse ARGS((Parser_tParsAttribute *use0, xxtUnionPtr xxGlobalRecoverySet));
static void yytext ARGS((Parser_tParsAttribute *text0, xxtUnionPtr xxGlobalRecoverySet));
static void yyany ARGS((Parser_tParsAttribute *any0, xxtUnionPtr xxGlobalRecoverySet));


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
    Copy((STRING)" ", 1L, Name, O_3);
    break;
  case 2:;
    Copy((STRING)"^", 1L, Name, O_3);
    break;
  case 3:;
    Copy((STRING)"%", 1L, Name, O_3);
    break;
  case 4:;
    Copy((STRING)"$", 1L, Name, O_3);
    break;
  case 5:;
    Copy((STRING)".", 1L, Name, O_3);
    break;
  case 6:;
    Copy((STRING)"\\", 1L, Name, O_3);
    break;
  case 7:;
    Copy((STRING)"{", 1L, Name, O_3);
    break;
  case 8:;
    Copy((STRING)"}", 1L, Name, O_3);
    break;
  case 9:;
    Copy((STRING)"nl", 2L, Name, O_3);
    break;
  case 10:;
    Copy((STRING)"bnl", 3L, Name, O_3);
    break;
  case 11:;
    Copy((STRING)"char", 4L, Name, O_3);
    break;
  case 12:;
    Copy((STRING)"tab", 3L, Name, O_3);
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
  yyinput(&Parser_ParsAttribute, (xxtUnionPtr)NIL);
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
    for (Token = 0; Token <= 12; Token += 1) {
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
    Scanner_ErrorAttribute((LONGCARD)Expected, RepairAttribute);
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

static void yyinput
# ifdef __STDC__
(Parser_tParsAttribute *input0, xxtUnionPtr xxGlobalRecoverySet)
# else
(input0, xxGlobalRecoverySet)
Parser_tParsAttribute *input0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute line1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    if (IN(0, xxVerticalSet0.A[xxToken])) {
      xxUnion.LocalRecoverySet = 0;
      yyline(&line1, (xxtUnionPtr)ADR(xxUnion));
    } else if (xxToken == 0 || xxIsRepairMode) {
      goto EXIT_1;
    } else {
      xxExpected(1, 1, xxGlobalRecoverySet);
    }
  } EXIT_1:;
}

static void yyline
# ifdef __STDC__
(Parser_tParsAttribute *line0, xxtUnionPtr xxGlobalRecoverySet)
# else
(line0, xxGlobalRecoverySet)
Parser_tParsAttribute *line0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Parser_tParsAttribute definition1;
  Parser_tParsAttribute usage1;
  Parser_tParsAttribute normal1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 5:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      for (;;) {
        switch (xxToken) {
        case 5:;
          xxUnion.LocalRecoverySet = 0;
          yydefinition(&definition1, (xxtUnionPtr)ADR(xxUnion));
          goto EXIT_3;
          break;
        case 1:;
        case 2:;
        case 3:;
        case 4:;
        case 6:;
        case 7:;
        case 8:;
        case 9:;
        case 10:;
        case 11:;
        case 12:;
          xxUnion.LocalRecoverySet = 0;
          yyusage(&usage1, (xxtUnionPtr)ADR(xxUnion));
          goto EXIT_3;
          break;
        default :
          if (xxIsRepairMode) {
            xxUnion.LocalRecoverySet = 0;
            yyusage(&usage1, (xxtUnionPtr)ADR(xxUnion));
            goto EXIT_3;
          }
          xxExpected(1, 1, xxGlobalRecoverySet);
          break;
        }
      } EXIT_3:;
      goto EXIT_2;
      break;
    case 1:;
    case 2:;
    case 3:;
    case 4:;
    case 6:;
    case 7:;
    case 8:;
    case 9:;
    case 10:;
    case 11:;
    case 12:;
      xxUnion.LocalRecoverySet = 0;
      yynormal(&normal1, (xxtUnionPtr)ADR(xxUnion));
      goto EXIT_2;
      break;
    default :
      if (xxIsRepairMode) {
        xxUnion.LocalRecoverySet = 0;
        yynormal(&normal1, (xxtUnionPtr)ADR(xxUnion));
        goto EXIT_2;
      }
      xxExpected(1, 1, xxGlobalRecoverySet);
      break;
    }
  } EXIT_2:;
}

static void yydefinition
# ifdef __STDC__
(Parser_tParsAttribute *definition0, xxtUnionPtr xxGlobalRecoverySet)
# else
(definition0, xxGlobalRecoverySet)
Parser_tParsAttribute *definition0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute nl1;
  Scanner_tScanAttribute char1;
  Parser_tParsAttribute bl1, bl2;
  Parser_tParsAttribute text1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  if (xxToken != 5) {
    xxRecoveryLiteral(5, 2, xxGlobalRecoverySet);
  } else {
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  xxUnion.LocalRecoverySet = 2;
  yybl(&bl1, (xxtUnionPtr)ADR(xxUnion));
  for (;;) {
    switch (xxToken) {
    case 11:;
      char1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      goto EXIT_4;
      break;
    case 2:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      char1.Ch = '^';
      goto EXIT_4;
      break;
    case 3:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      char1.Ch = '%';
      goto EXIT_4;
      break;
    case 4:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      char1.Ch = '$';
      goto EXIT_4;
      break;
    case 7:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      char1.Ch = '{';
      goto EXIT_4;
      break;
    case 8:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      char1.Ch = '}';
      goto EXIT_4;
      break;
    case 6:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      char1.Ch = '\\';
      goto EXIT_4;
      break;
    default :
      if (xxIsRepairMode) {
        if (xxToken != 11) {
          xxRecoveryTerminal(11, 3, xxGlobalRecoverySet, &char1);
        } else {
          char1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
        }
        goto EXIT_4;
      }
      xxExpected(2, 2, xxGlobalRecoverySet);
      break;
    }
  } EXIT_4:;
  xxUnion.LocalRecoverySet = 3;
  yybl(&bl2, (xxtUnionPtr)ADR(xxUnion));
  Strings_AssignEmpty(&text1);
  for (;;) {
    if (IN(1, xxVerticalSet0.A[xxToken])) {
      xxUnion.LocalRecoverySet = 6;
      yytext(&text1, (xxtUnionPtr)ADR(xxUnion));
      goto EXIT_5;
    } else if (xxToken == 9 || xxIsRepairMode) {
      goto EXIT_5;
    }
    xxExpected(3, 3, xxGlobalRecoverySet);
  } EXIT_5:;
  if (xxToken != 9) {
    xxRecoveryTerminal(9, 6, xxGlobalRecoverySet, &nl1);
  } else {
    nl1 = Scanner_Attribute;
    xxToken = Scanner_GetToken();
    xxIsRepairMode = FALSE;
  }
  Table_Define(char1.Ch, &text1);
  Table_NewLine();
}

static void yyusage
# ifdef __STDC__
(Parser_tParsAttribute *usage0, xxtUnionPtr xxGlobalRecoverySet)
# else
(usage0, xxGlobalRecoverySet)
Parser_tParsAttribute *usage0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute nl1, nl2;
  Scanner_tScanAttribute bnl1;
  Scanner_tScanAttribute char1;
  Parser_tParsAttribute bl1;
  Parser_tParsAttribute text1;
  Parser_tParsAttribute use1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 2:;
    case 3:;
    case 4:;
    case 7:;
    case 8:;
    case 11:;
      Strings_AssignEmpty(&text1);
      for (;;) {
        switch (xxToken) {
        case 11:;
          char1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          goto EXIT_7;
          break;
        case 2:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '^';
          goto EXIT_7;
          break;
        case 3:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '%';
          goto EXIT_7;
          break;
        case 4:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '$';
          goto EXIT_7;
          break;
        case 7:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '{';
          goto EXIT_7;
          break;
        case 8:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '}';
          goto EXIT_7;
          break;
        default :
          if (xxIsRepairMode) {
            if (xxToken != 11) {
              xxRecoveryTerminal(11, 3, xxGlobalRecoverySet, &char1);
            } else {
              char1 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
            }
            goto EXIT_7;
          }
          xxExpected(2, 2, xxGlobalRecoverySet);
          break;
        }
      } EXIT_7:;
      for (;;) {
        if (IN(1, xxVerticalSet0.A[xxToken])) {
          xxUnion.LocalRecoverySet = 6;
          yytext(&text1, (xxtUnionPtr)ADR(xxUnion));
          goto EXIT_8;
        } else if (xxToken == 9 || xxIsRepairMode) {
          goto EXIT_8;
        }
        xxExpected(3, 3, xxGlobalRecoverySet);
      } EXIT_8:;
      if (xxToken != 9) {
        xxRecoveryTerminal(9, 6, xxGlobalRecoverySet, &nl1);
      } else {
        nl1 = Scanner_Attribute;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
      }
      Table_Translate(char1.Ch, &text1);
      goto EXIT_6;
      break;
    case 1:;
    case 5:;
    case 6:;
    case 9:;
    case 10:;
    case 12:;
      Table_BeginLine();
      xxUnion.LocalRecoverySet = 7;
      yybl(&bl1, (xxtUnionPtr)ADR(xxUnion));
      for (;;) {
        if (IN(2, xxVerticalSet0.A[xxToken])) {
          xxUnion.LocalRecoverySet = 8;
          yyuse(&use1, (xxtUnionPtr)ADR(xxUnion));
        } else if (IN(3, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
          goto EXIT_9;
        } else {
          xxExpected(7, 7, xxGlobalRecoverySet);
        }
      } EXIT_9:;
      for (;;) {
        switch (xxToken) {
        case 9:;
          nl2 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          Table_CloseLine();
          goto EXIT_10;
          break;
        case 10:;
          bnl1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          goto EXIT_10;
          break;
        default :
          if (xxIsRepairMode) {
            if (xxToken != 9) {
              xxRecoveryTerminal(9, 6, xxGlobalRecoverySet, &nl2);
            } else {
              nl2 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
            }
            Table_CloseLine();
            goto EXIT_10;
          }
          xxExpected(8, 8, xxGlobalRecoverySet);
          break;
        }
      } EXIT_10:;
      goto EXIT_6;
      break;
    default :
      if (xxIsRepairMode) {
        Table_BeginLine();
        xxUnion.LocalRecoverySet = 7;
        yybl(&bl1, (xxtUnionPtr)ADR(xxUnion));
        for (;;) {
          if (IN(2, xxVerticalSet0.A[xxToken])) {
            xxUnion.LocalRecoverySet = 8;
            yyuse(&use1, (xxtUnionPtr)ADR(xxUnion));
          } else if (IN(3, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
            goto EXIT_11;
          } else {
            xxExpected(7, 7, xxGlobalRecoverySet);
          }
        } EXIT_11:;
        for (;;) {
          switch (xxToken) {
          case 9:;
            nl2 = Scanner_Attribute;
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
            Table_CloseLine();
            goto EXIT_12;
            break;
          case 10:;
            bnl1 = Scanner_Attribute;
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
            goto EXIT_12;
            break;
          default :
            if (xxIsRepairMode) {
              if (xxToken != 9) {
                xxRecoveryTerminal(9, 6, xxGlobalRecoverySet, &nl2);
              } else {
                nl2 = Scanner_Attribute;
                xxToken = Scanner_GetToken();
                xxIsRepairMode = FALSE;
              }
              Table_CloseLine();
              goto EXIT_12;
            }
            xxExpected(8, 8, xxGlobalRecoverySet);
            break;
          }
        } EXIT_12:;
        goto EXIT_6;
      }
      xxExpected(1, 1, xxGlobalRecoverySet);
      break;
    }
  } EXIT_6:;
  Table_NewLine();
}

static void yynormal
# ifdef __STDC__
(Parser_tParsAttribute *normal0, xxtUnionPtr xxGlobalRecoverySet)
# else
(normal0, xxGlobalRecoverySet)
Parser_tParsAttribute *normal0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute nl1;
  Scanner_tScanAttribute bnl1;
  Parser_tParsAttribute any1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    if (IN(4, xxVerticalSet0.A[xxToken])) {
      xxUnion.LocalRecoverySet = 8;
      yyany(&any1, (xxtUnionPtr)ADR(xxUnion));
      Table_WriteLine(&any1);
      goto EXIT_13;
    } else if (IN(3, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
      goto EXIT_13;
    }
    xxExpected(1, 1, xxGlobalRecoverySet);
  } EXIT_13:;
  for (;;) {
    switch (xxToken) {
    case 9:;
      nl1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      goto EXIT_14;
      break;
    case 10:;
      bnl1 = Scanner_Attribute;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      StdIO_WriteC('\\');
      goto EXIT_14;
      break;
    default :
      if (xxIsRepairMode) {
        if (xxToken != 9) {
          xxRecoveryTerminal(9, 6, xxGlobalRecoverySet, &nl1);
        } else {
          nl1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
        }
        goto EXIT_14;
      }
      xxExpected(8, 8, xxGlobalRecoverySet);
      break;
    }
  } EXIT_14:;
  Table_NewLine();
}

static void yybl
# ifdef __STDC__
(Parser_tParsAttribute *bl0, xxtUnionPtr xxGlobalRecoverySet)
# else
(bl0, xxGlobalRecoverySet)
Parser_tParsAttribute *bl0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute tab1;

  for (;;) {
    if (IN(5, xxVerticalSet0.A[xxToken])) {
      if (xxToken == 1) {
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
      } else {
        tab1 = Scanner_Attribute;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
      }
    } else if (IN(0, xxVerticalSet0.A[xxToken]) || xxIsRepairMode) {
      goto EXIT_15;
    } else {
      xxExpected(10, 10, xxGlobalRecoverySet);
    }
  } EXIT_15:;
}

static void yyuse
# ifdef __STDC__
(Parser_tParsAttribute *use0, xxtUnionPtr xxGlobalRecoverySet)
# else
(use0, xxGlobalRecoverySet)
Parser_tParsAttribute *use0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute char1;
  Parser_tParsAttribute bl1;
  Parser_tParsAttribute text1;
  xxtUnion xxUnion;

  xxUnion.GlobalRecoverySet = xxGlobalRecoverySet;
  for (;;) {
    switch (xxToken) {
    case 7:;
      xxToken = Scanner_GetToken();
      xxIsRepairMode = FALSE;
      for (;;) {
        switch (xxToken) {
        case 11:;
          char1 = Scanner_Attribute;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          goto EXIT_17;
          break;
        case 2:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '^';
          goto EXIT_17;
          break;
        case 3:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '%';
          goto EXIT_17;
          break;
        case 4:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '$';
          goto EXIT_17;
          break;
        case 7:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '{';
          goto EXIT_17;
          break;
        case 8:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '}';
          goto EXIT_17;
          break;
        case 6:;
          xxToken = Scanner_GetToken();
          xxIsRepairMode = FALSE;
          char1.Ch = '\\';
          goto EXIT_17;
          break;
        default :
          if (xxIsRepairMode) {
            if (xxToken != 11) {
              xxRecoveryTerminal(11, 14, xxGlobalRecoverySet, &char1);
            } else {
              char1 = Scanner_Attribute;
              xxToken = Scanner_GetToken();
              xxIsRepairMode = FALSE;
            }
            goto EXIT_17;
          }
          xxExpected(13, 13, xxGlobalRecoverySet);
          break;
        }
      } EXIT_17:;
      Strings_AssignEmpty(&text1);
      xxUnion.LocalRecoverySet = 14;
      yybl(&bl1, (xxtUnionPtr)ADR(xxUnion));
      for (;;) {
        if (IN(1, xxVerticalSet0.A[xxToken])) {
          xxUnion.LocalRecoverySet = 15;
          yytext(&text1, (xxtUnionPtr)ADR(xxUnion));
          goto EXIT_18;
        } else if (xxToken == 8 || xxIsRepairMode) {
          goto EXIT_18;
        }
        xxExpected(14, 14, xxGlobalRecoverySet);
      } EXIT_18:;
      if (xxToken != 8) {
        xxRecoveryLiteral(8, 15, xxGlobalRecoverySet);
      } else {
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
      }
      Table_Translate(char1.Ch, &text1);
      goto EXIT_16;
      break;
    case 1:;
    case 2:;
    case 3:;
    case 4:;
    case 5:;
    case 6:;
    case 11:;
    case 12:;
      xxUnion.LocalRecoverySet = 0;
      yytext(&text1, (xxtUnionPtr)ADR(xxUnion));
      Table_Translate('%', &text1);
      goto EXIT_16;
      break;
    default :
      if (xxIsRepairMode) {
        xxUnion.LocalRecoverySet = 0;
        yytext(&text1, (xxtUnionPtr)ADR(xxUnion));
        Table_Translate('%', &text1);
        goto EXIT_16;
      }
      xxExpected(16, 16, xxGlobalRecoverySet);
      break;
    }
  } EXIT_16:;
}

static void yytext
# ifdef __STDC__
(Parser_tParsAttribute *text0, xxtUnionPtr xxGlobalRecoverySet)
# else
(text0, xxGlobalRecoverySet)
Parser_tParsAttribute *text0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute char1;
  Scanner_tScanAttribute tab1, tab2;

  Strings_AssignEmpty(text0);
  for (;;) {
    for (;;) {
      switch (xxToken) {
      case 1:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, ' ');
        goto EXIT_20;
        break;
      case 2:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, '^');
        goto EXIT_20;
        break;
      case 3:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, '%');
        goto EXIT_20;
        break;
      case 4:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, '$');
        goto EXIT_20;
        break;
      case 5:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, '.');
        goto EXIT_20;
        break;
      case 11:;
        char1 = Scanner_Attribute;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, char1.Ch);
        goto EXIT_20;
        break;
      case 12:;
        tab1 = Scanner_Attribute;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, cTab);
        goto EXIT_20;
        break;
      case 6:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(text0, '\\');
        for (;;) {
          switch (xxToken) {
          case 6:;
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
            Strings_Append(text0, '\\');
            goto EXIT_21;
            break;
          case 7:;
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
            Strings_Append(text0, '{');
            goto EXIT_21;
            break;
          case 8:;
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
            Strings_Append(text0, '}');
            goto EXIT_21;
            break;
          case 1:;
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
            Strings_Append(text0, ' ');
            goto EXIT_21;
            break;
          case 12:;
            tab2 = Scanner_Attribute;
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
            Strings_Append(text0, cTab);
            goto EXIT_21;
            break;
          default :
            if (xxIsRepairMode) {
              if (xxToken != 6) {
                xxRecoveryLiteral(6, 24, xxGlobalRecoverySet);
              } else {
                xxToken = Scanner_GetToken();
                xxIsRepairMode = FALSE;
              }
              Strings_Append(text0, '\\');
              goto EXIT_21;
            }
            xxExpected(23, 23, xxGlobalRecoverySet);
            break;
          }
        } EXIT_21:;
        goto EXIT_20;
        break;
      default :
        if (xxIsRepairMode) {
          if (xxToken != 1) {
            xxRecoveryLiteral(1, 11, xxGlobalRecoverySet);
          } else {
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
          }
          Strings_Append(text0, ' ');
          goto EXIT_20;
        }
        xxExpected(17, 17, xxGlobalRecoverySet);
        break;
      }
    } EXIT_20:;
    if (!IN(1, xxVerticalSet0.A[xxToken])) {
      if (IN(0, xxVerticalSet0.A[xxToken])) {
        goto EXIT_19;
      }
      xxExpected(17, 17, xxGlobalRecoverySet);
      if (!IN(1, xxVerticalSet0.A[xxToken])) {
        goto EXIT_19;
      }
    }
  } EXIT_19:;
}

static void yyany
# ifdef __STDC__
(Parser_tParsAttribute *any0, xxtUnionPtr xxGlobalRecoverySet)
# else
(any0, xxGlobalRecoverySet)
Parser_tParsAttribute *any0;
xxtUnionPtr xxGlobalRecoverySet;
# endif
{
  Scanner_tScanAttribute char1;
  Scanner_tScanAttribute tab1;

  Strings_AssignEmpty(any0);
  for (;;) {
    for (;;) {
      switch (xxToken) {
      case 1:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, ' ');
        goto EXIT_23;
        break;
      case 2:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, '^');
        goto EXIT_23;
        break;
      case 3:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, '%');
        goto EXIT_23;
        break;
      case 4:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, '$');
        goto EXIT_23;
        break;
      case 5:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, '.');
        goto EXIT_23;
        break;
      case 6:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, '\\');
        goto EXIT_23;
        break;
      case 7:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, '{');
        goto EXIT_23;
        break;
      case 8:;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, '}');
        goto EXIT_23;
        break;
      case 11:;
        char1 = Scanner_Attribute;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, char1.Ch);
        goto EXIT_23;
        break;
      case 12:;
        tab1 = Scanner_Attribute;
        xxToken = Scanner_GetToken();
        xxIsRepairMode = FALSE;
        Strings_Append(any0, cTab);
        goto EXIT_23;
        break;
      default :
        if (xxIsRepairMode) {
          if (xxToken != 1) {
            xxRecoveryLiteral(1, 11, xxGlobalRecoverySet);
          } else {
            xxToken = Scanner_GetToken();
            xxIsRepairMode = FALSE;
          }
          Strings_Append(any0, ' ');
          goto EXIT_23;
        }
        xxExpected(13, 13, xxGlobalRecoverySet);
        break;
      }
    } EXIT_23:;
    if (!IN(4, xxVerticalSet0.A[xxToken])) {
      if (IN(3, xxVerticalSet0.A[xxToken])) {
        goto EXIT_22;
      }
      xxExpected(13, 13, xxGlobalRecoverySet);
      if (!IN(4, xxVerticalSet0.A[xxToken])) {
        goto EXIT_22;
      }
    }
  } EXIT_22:;
}

void Parser__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Strings__init();
    Positions__init();
    Errors__init();
    Scanner__init();
    Strings__init();
    System__init();
    StdIO__init();
    Scanner__init();
    Strings__init();
    Table__init();

    xxIsInitialized = FALSE;
    (void)strncpy((char *)Parser_ParsTabName.A, "Parser.Tab", sizeof(Parser_ParsTabName.A));
  }
}
