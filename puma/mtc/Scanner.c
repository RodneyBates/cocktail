#include "SYSTEM_.h"

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Source
#include "Source.h"
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

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

INTEGER Scanner_TokenLength;
Scanner_tScanAttribute Scanner_Attribute;
struct Scanner_14 Scanner_ScanTabName;
PROC Scanner_Exit;

static INTEGER BraceNestingLevel, CommentNestingLevel;
static Positions_tPosition CommentPos, StringPos, TargetPos;
static BOOLEAN InsideTarget, InsideExpr;
#define yyTabSpace   8
#define yyDNoState   0
#define yyFileStackSize   16
#define yyInitBufferSize   (1024 * 8 + 256)
#define yyFirstCh   '\0'
#define yyLastCh   ((CHAR)'\177')
#define yyEolCh   '\n'
#define yyEobCh   ((CHAR)'\177')
#define yyDStateCount   260
#define yyTableSize   2837
#define yyEobState   83
#define yyDefaultState   84
#define STD   1
#define CComment   3
#define M2Comment   5
#define Str1   7
#define Str2   9
#define CStr1   11
#define CStr2   13
#define targetcode   15
#define expr   17
typedef SHORTCARD yyTableElmt;
typedef yyTableElmt yyStateRange;
typedef yyTableElmt yyTableRange;
typedef struct S_1 {
    yyStateRange Check, Next;
} yyCombType;
typedef yyCombType *yyCombTypePtr;
typedef struct S_6 {
    CHAR A[1000000 + 1];
} *yytChBufferPtr;
typedef CHAR yyChRange;
typedef SHORTCARD yyFileStackPtrTyp;
typedef yyFileStackPtrTyp yyFileStackSubscript;
static struct S_7 {
    LONGCARD A[yyDStateCount + 1];
} yyBasePtr;
static struct S_8 {
    yyStateRange A[yyDStateCount + 1];
} yyDefault;
static struct S_9 {
    yyCombType A[yyTableSize + 1];
} yyComb;
static struct S_10 {
    yyStateRange A[yyDStateCount + 1];
} yyEobTrans;
static struct S_11 {
    CHAR A[yyLastCh + 1];
} yyToLower, yyToUpper;
static struct S_12 {
    yyStateRange A[1000000 + 1];
} *yyStateStack;
static LONGINT yyStateStackSize;
static yyStateRange yyStartState;
static yyStateRange yyPreviousStart;
static CHAR yyCh;
static System_tFile yySourceFile;
static BOOLEAN yyEof;
static yytChBufferPtr yyChBufferPtr;
static INTEGER yyChBufferStart;
static LONGINT yyChBufferSize;
static INTEGER yyChBufferIndex;
static INTEGER yyBytesRead;
static SHORTCARD yyLineCount;
static CARDINAL yyTotalLineCount;
static INTEGER yyLineStart;
static yyFileStackPtrTyp yyFileStackPtr;
static struct S_13 {
    struct S_14 {
        System_tFile SourceFile;
        BOOLEAN Eof;
        yytChBufferPtr ChBufferPtr;
        INTEGER ChBufferStart;
        LONGINT ChBufferSize;
        INTEGER ChBufferIndex;
        INTEGER BytesRead;
        SHORTCARD LineCount;
        INTEGER LineStart;
    } A[yyFileStackSize - 1 + 1];
} yyFileStack;
static void AccumComment ARGS(());
static void yyInitialize ARGS(());
static void yyStart ARGS((yyStateRange State));
static void yyPrevious ARGS(());
static void yyEcho ARGS(());
static void yyLess ARGS((INTEGER n));
static void yyTab ARGS(());
static void yyTab1 ARGS((INTEGER a));
static void yyTab2 ARGS((INTEGER a, INTEGER b));
static void yyEol ARGS((INTEGER Column));
static void output ARGS((CHAR c));
static void unput ARGS((CHAR c));
static CHAR input ARGS(());
static void yyGetTables ARGS(());
struct S_16 {
    yyTableRange A[yyDStateCount + 1];
};
static CARDINAL yyGetTable ARGS((System_tFile TableFile, ADDRESS Address));
static void yyErrorMessage ARGS((SHORTCARD ErrorCode));
static void yyExit ARGS(());

static Strings_tString *G_1_TargetCode;
static Strings_tString *G_2_Word;

void Scanner_ErrorAttribute
# ifdef __STDC__
(INTEGER Token, Scanner_tScanAttribute *pAttribute)
# else
(Token, pAttribute)
INTEGER Token;
Scanner_tScanAttribute *pAttribute;
# endif
{
  pAttribute->Position = Scanner_Attribute.Position;
  switch (Token) {
  case 1:;
    pAttribute->U_1.V_1.Ident.Ident = Idents_NoIdent;
    break;
  case 2:;
    pAttribute->U_1.V_2.Operator.Ident = Idents_NoIdent;
    break;
  case 3:;
    pAttribute->U_1.V_3.IncOperator.Ident = Idents_NoIdent;
    break;
  case 4:;
    pAttribute->U_1.V_4.CompoundOperator.Ident = Idents_NoIdent;
    break;
  case 5:;
    Texts_MakeText(&pAttribute->U_1.V_5.TargetBlock.Text);
    break;
  case 6:;
    pAttribute->U_1.V_6.String.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 7:;
    pAttribute->U_1.V_7.Number.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 8:;
    pAttribute->U_1.V_8.TargetCode.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 9:;
    pAttribute->U_1.V_9.WhiteSpace.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 10:;
    pAttribute->U_1.V_10.yy10.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 11:;
    pAttribute->U_1.V_11.yy11.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  case 12:;
    pAttribute->U_1.V_12.yy12.StringRef = Idents_GetStringRef(Idents_NoIdent);
    break;
  default :
    break;
  }
}

void Scanner_Error
# ifdef __STDC__
(CHAR Text[], LONGCARD O_1, Positions_tPosition Position)
# else
(Text, O_1, Position)
CHAR Text[];
LONGCARD O_1;
Positions_tPosition Position;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_1, CHAR)
  Errors_Message(Text, O_1, (LONGCARD)Errors_Error, Position);
  INC(Tree_ErrorCount);
  FREE_OPEN_ARRAYS
}

void Scanner_StringError
# ifdef __STDC__
(Strings_tString Text, Positions_tPosition Position)
# else
(Text, Position)
Strings_tString Text;
Positions_tPosition Position;
# endif
{
  Errors_StringMessage(Text, (LONGCARD)Errors_Error, Position);
  INC(Tree_ErrorCount);
}

void Scanner_ErrorI
# ifdef __STDC__
(CHAR Text[], LONGCARD O_2, Positions_tPosition Position, Idents_tIdent Ident)
# else
(Text, O_2, Position, Ident)
CHAR Text[];
LONGCARD O_2;
Positions_tPosition Position;
Idents_tIdent Ident;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_2, CHAR)
  Errors_MessageI(Text, O_2, (LONGCARD)Errors_Error, Position, (LONGCARD)Errors_Ident, ADR(Ident));
  INC(Tree_ErrorCount);
  FREE_OPEN_ARRAYS
}

void Scanner_Warning
# ifdef __STDC__
(CHAR Text[], LONGCARD O_3, Positions_tPosition Position)
# else
(Text, O_3, Position)
CHAR Text[];
LONGCARD O_3;
Positions_tPosition Position;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_3, CHAR)
  if (!Sets_IsElement(ORD('s'), &Tree_Options)) {
    Errors_Message(Text, O_3, (LONGCARD)Errors_Warning, Position);
  }
  FREE_OPEN_ARRAYS
}

void Scanner_StringWarning
# ifdef __STDC__
(Strings_tString Text, Positions_tPosition Position)
# else
(Text, Position)
Strings_tString Text;
Positions_tPosition Position;
# endif
{
  if (!Sets_IsElement(ORD('s'), &Tree_Options)) {
    Errors_StringMessage(Text, (LONGCARD)Errors_Warning, Position);
  }
}

void Scanner_WarningI
# ifdef __STDC__
(CHAR Text[], LONGCARD O_4, Positions_tPosition Position, Idents_tIdent Ident)
# else
(Text, O_4, Position, Ident)
CHAR Text[];
LONGCARD O_4;
Positions_tPosition Position;
Idents_tIdent Ident;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Text, O_4, CHAR)
  if (!Sets_IsElement(ORD('s'), &Tree_Options)) {
    Errors_MessageI(Text, O_4, (LONGCARD)Errors_Warning, Position, (LONGCARD)Errors_Ident, ADR(Ident));
  }
  FREE_OPEN_ARRAYS
}

static void AccumComment
# ifdef __STDC__
()
# else
()
# endif
{
  if (InsideTarget && BraceNestingLevel > 0) {
    Scanner_GetWord(G_2_Word);
    Strings_Concatenate(G_1_TargetCode, G_2_Word);
  }
}

INTEGER Scanner_GetToken
# ifdef __STDC__
()
# else
()
# endif
{
  yyStateRange yyState;
  yyCombTypePtr yyTablePtr;
  BOOLEAN yyRestartFlag;
  INTEGER yyi, yySource, yyTarget;
  LONGINT yyChBufferFree;
  Strings_tString Word, String, TargetCode;
  Strings_tString *L_1;
  Strings_tString *L_2;

  L_1 = G_1_TargetCode;
  G_1_TargetCode = &TargetCode;
  L_2 = G_2_Word;
  G_2_Word = &Word;
  for (;;) {
    yyState = yyStartState;
    Scanner_TokenLength = 0;
    for (;;) {
      for (;;) {
        yyTablePtr = (yyCombTypePtr)(yyBasePtr.A[yyState] + VAL(LONGCARD, ORD(yyChBufferPtr->A[yyChBufferIndex])) * VAL(LONGCARD, sizeof(yyCombType)));
        if (yyTablePtr->Check != yyState) {
          yyState = yyDefault.A[yyState];
          if (yyState == yyDNoState) {
            goto EXIT_3;
          }
        } else {
          yyState = yyTablePtr->Next;
          INC(Scanner_TokenLength);
          yyStateStack->A[Scanner_TokenLength] = yyState;
          INC(yyChBufferIndex);
        }
      } EXIT_3:;
      for (;;) {
        switch (yyStateStack->A[Scanner_TokenLength]) {
        case 260:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel == 0) {
            Texts_MakeText(&Scanner_Attribute.U_1.V_5.TargetBlock.Text);
            Strings_AssignEmpty(&TargetCode);
            TargetPos = Scanner_Attribute.Position;
            InsideTarget = TRUE;
          } else {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          INC(BraceNestingLevel);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 259:;
          DEC(BraceNestingLevel);
          if (BraceNestingLevel == 0) {
            yyStart(STD);
            InsideTarget = FALSE;
            Texts_Append(&Scanner_Attribute.U_1.V_5.TargetBlock.Text, &TargetCode);
            Scanner_Attribute.Position = TargetPos;
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return 5;
          } else {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 24:;
        case 44:;
        case 94:;
        case 248:;
        case 255:;
          if (BraceNestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 258:;
          if (BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 257:;
          if (BraceNestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_5.TargetBlock.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 25:;
          if (BraceNestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Append(&TargetCode, Strings_Char(&Word, 2));
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 41:;
          if (BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\\');
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 254:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          AccumComment();
          CommentNestingLevel = 1;
          CommentPos = Scanner_Attribute.Position;
          yyStart(M2Comment);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 253:;
          INC(CommentNestingLevel);
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 251:;
          AccumComment();
          DEC(CommentNestingLevel);
          if (CommentNestingLevel == 0) {
            yyPrevious();
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 30:;
        case 47:;
        case 89:;
        case 250:;
        case 252:;
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 247:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          AccumComment();
          yyStart(CComment);
          CommentPos = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 245:;
          AccumComment();
          yyPrevious();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 31:;
        case 48:;
        case 88:;
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 244:;
          if (InsideTarget && BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 243:;
          if (InsideTarget && BraceNestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_5.TargetBlock.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 33:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 32:;
        case 49:;
        case 50:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_7.Number.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 7;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 242:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (Sets_IsElement(ORD('c'), &Tree_Options)) {
            yyStart(CStr1);
          } else {
            yyStart(Str1);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 241:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (Sets_IsElement(ORD('c'), &Tree_Options)) {
            yyStart(CStr2);
          } else {
            yyStart(Str2);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 29:;
        case 90:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 28:;
        case 91:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 27:;
        case 46:;
        case 70:;
        case 92:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 26:;
        case 45:;
        case 69:;
        case 93:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 240:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 239:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 238:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_6.String.StringRef = StringMem_PutString(&String);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return 6;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 237:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_6.String.StringRef = StringMem_PutString(&String);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return 6;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 236:;
          Strings_Append(&String, '\t');
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 235:;
          Scanner_Error((STRING)"unclosed string", 15L, Scanner_Attribute.Position);
          Strings_Append(&String, Strings_Char(&String, 1));
          yyEol(0L);
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_6.String.StringRef = StringMem_PutString(&String);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return 6;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 234:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 10;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 81:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 11;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 233:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 12;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 139:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel == 0) {
            TargetPos = Scanner_Attribute.Position;
          }
          yyStart(expr);
          InsideExpr = TRUE;
          INC(BraceNestingLevel);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 39;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 20:;
        case 39:;
        case 68:;
        case 249:;
        case 256:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.TargetCode.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 232:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          INC(BraceNestingLevel);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.TargetCode.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 231:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          DEC(BraceNestingLevel);
          if (BraceNestingLevel == 0) {
            yyStart(STD);
            InsideExpr = FALSE;
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return 40;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_8.TargetCode.StringRef = StringMem_PutString(&Word);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return 8;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 229:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.TargetCode.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 230:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_10.yy10.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 10;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 228:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_11.yy11.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 11;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 227:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_12.yy12.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 12;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 226:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.TargetCode.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 21:;
        case 95:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_9.WhiteSpace.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 9;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 225:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_9.WhiteSpace.StringRef = StringMem_PutString(&Word);
          yyEol(0L);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 9;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 224:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_9.WhiteSpace.StringRef = StringMem_PutString(&Word);
          yyTab();
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 9;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 23:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, 2, &String);
          Scanner_Attribute.U_1.V_8.TargetCode.StringRef = StringMem_PutString(&String);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 42:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_8.TargetCode.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 8;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 205:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 19;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 197:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 20;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 172:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 24;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 167:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 25;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 190:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 21;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 178:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 23;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 184:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 22;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 148:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 34;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 34:;
        case 51:;
        case 52:;
        case 53:;
        case 54:;
        case 55:;
        case 56:;
        case 57:;
        case 58:;
        case 71:;
        case 150:;
        case 246:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_2.Operator.Ident = Idents_MakeIdent(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 2;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 35:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_2.Operator.Ident = Idents_MakeIdent(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 4;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 37:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_3.IncOperator.Ident = Idents_MakeIdent(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 3;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 36:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &String);
          Scanner_Attribute.U_1.V_2.Operator.Ident = Idents_MakeIdent(&String);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 2;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 223:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 13;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 220:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 14;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 216:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 15;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 215:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 16;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 210:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 17;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 206:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 18;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 162:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 26;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 155:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 27;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 154:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 28;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 96:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 29;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 153:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 30;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 152:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 31;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 151:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 32;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 149:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 33;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 98:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 35;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 143:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 36;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 142:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 37;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 140:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 38;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 138:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 40;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 137:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 41;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 136:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 42;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 135:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 43;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 134:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 44;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 130:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 45;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 127:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 46;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 124:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 47;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 122:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 48;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 116:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 49;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 108:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 50;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 99:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 35;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 97:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 43;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 19:;
        case 38:;
        case 59:;
        case 60:;
        case 61:;
        case 62:;
        case 63:;
        case 64:;
        case 65:;
        case 66:;
        case 67:;
        case 72:;
        case 73:;
        case 74:;
        case 75:;
        case 76:;
        case 77:;
        case 78:;
        case 79:;
        case 80:;
        case 100:;
        case 101:;
        case 102:;
        case 103:;
        case 104:;
        case 105:;
        case 106:;
        case 107:;
        case 109:;
        case 110:;
        case 111:;
        case 112:;
        case 113:;
        case 114:;
        case 115:;
        case 117:;
        case 118:;
        case 119:;
        case 120:;
        case 121:;
        case 123:;
        case 125:;
        case 126:;
        case 128:;
        case 129:;
        case 131:;
        case 132:;
        case 133:;
        case 141:;
        case 144:;
        case 145:;
        case 146:;
        case 147:;
        case 156:;
        case 157:;
        case 158:;
        case 159:;
        case 160:;
        case 161:;
        case 163:;
        case 164:;
        case 165:;
        case 166:;
        case 168:;
        case 169:;
        case 170:;
        case 171:;
        case 173:;
        case 174:;
        case 175:;
        case 176:;
        case 177:;
        case 179:;
        case 180:;
        case 181:;
        case 182:;
        case 183:;
        case 185:;
        case 186:;
        case 187:;
        case 188:;
        case 189:;
        case 191:;
        case 192:;
        case 193:;
        case 194:;
        case 195:;
        case 196:;
        case 198:;
        case 199:;
        case 200:;
        case 201:;
        case 202:;
        case 203:;
        case 204:;
        case 207:;
        case 208:;
        case 209:;
        case 211:;
        case 212:;
        case 213:;
        case 214:;
        case 217:;
        case 218:;
        case 219:;
        case 221:;
        case 222:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.Ident.Ident = Idents_MakeIdent(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return 1;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 87:;
          while (yyChBufferPtr->A[yyChBufferIndex] == ' ') {
            INC(yyChBufferIndex);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 86:;
          DEC1(yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) % 8);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 85:;
          INC(yyLineCount);
          yyLineStart = yyChBufferIndex - 1;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 1:;
        case 2:;
        case 3:;
        case 4:;
        case 5:;
        case 6:;
        case 7:;
        case 8:;
        case 9:;
        case 10:;
        case 11:;
        case 12:;
        case 13:;
        case 14:;
        case 15:;
        case 16:;
        case 17:;
        case 18:;
        case 22:;
        case 40:;
        case 43:;
        case 82:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 84:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart);
          INC(yyChBufferIndex);
          Scanner_TokenLength = 1;
          Scanner_GetWord(&Word);
          Errors_MessageI((STRING)"illegal character", 17L, (LONGCARD)Errors_Error, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(Word));
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case yyDNoState:;
          yyGetTables();
          yyStateStack->A[0] = yyDefaultState;
          if (yyFileStackPtr == 0) {
            yyInitialize();
            yySourceFile = System_StdInput;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 83:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          if (Scanner_TokenLength == 0) {
            yyState = yyStartState;
          } else {
            yyState = yyStateStack->A[Scanner_TokenLength];
          }
          if (yyChBufferIndex != yyChBufferStart + yyBytesRead) {
            yyState = yyEobTrans.A[yyState];
            if (yyState != yyDNoState) {
              INC(yyChBufferIndex);
              INC(Scanner_TokenLength);
              yyStateStack->A[Scanner_TokenLength] = yyState;
              yyRestartFlag = TRUE;
              goto EXIT_4;
            }
          } else {
            yySource = yyChBufferIndex - Scanner_TokenLength - 1;
            yyTarget = General_MaxAlign - Scanner_TokenLength % General_MaxAlign - 1;
            if (yySource != yyTarget) {
              {
                LONGINT B_1 = 1, B_2 = Scanner_TokenLength;

                if (B_1 <= B_2)
                  for (yyi = B_1;; yyi += 1) {
                    yyChBufferPtr->A[yyTarget + yyi] = yyChBufferPtr->A[yySource + yyi];
                    if (yyi >= B_2) break;
                  }
              }
              DEC1(yyLineStart, yySource - yyTarget);
              yyChBufferStart = yyTarget + Scanner_TokenLength + 1;
            } else {
              yyChBufferStart = yyChBufferIndex;
            }
            if (!yyEof) {
              yyChBufferFree = VAL(LONGINT, General_Exp2(General_Log2(yyChBufferSize - 4 - VAL(LONGINT, General_MaxAlign) - VAL(LONGINT, Scanner_TokenLength))));
              if (yyChBufferFree < yyChBufferSize / 8) {
                DynArray_ExtendArray((ADDRESS *)&yyChBufferPtr, &yyChBufferSize, (LONGINT)sizeof(CHAR));
                if (yyChBufferPtr == NIL) {
                  yyErrorMessage(1);
                }
                yyChBufferFree = VAL(LONGINT, General_Exp2(General_Log2(yyChBufferSize - 4 - VAL(LONGINT, General_MaxAlign) - VAL(LONGINT, Scanner_TokenLength))));
                if (yyStateStackSize < yyChBufferSize) {
                  DynArray_ExtendArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
                  if (yyStateStack == NIL) {
                    yyErrorMessage(1);
                  }
                }
              }
              yyChBufferIndex = yyChBufferStart;
              yyBytesRead = Source_GetLine(yySourceFile, ADR(yyChBufferPtr->A[yyChBufferIndex]), VAL(CARDINAL, yyChBufferFree));
              if (yyBytesRead <= 0) {
                yyBytesRead = 0;
                yyEof = TRUE;
              }
              yyChBufferPtr->A[yyChBufferStart + yyBytesRead] = yyEobCh;
              yyChBufferPtr->A[yyChBufferStart + yyBytesRead + 1] = '\0';
              yyRestartFlag = TRUE;
              goto EXIT_4;
            }
            if (Scanner_TokenLength == 0) {
              Scanner_Attribute.Position.Line = yyLineCount;
              Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart);
              Scanner_CloseFile();
              if (yyFileStackPtr == 0) {
                switch (yyStartState) {
                case CComment:;
                case M2Comment:;
                  Scanner_Error((STRING)"unclosed comment", 16L, CommentPos);
                  if (InsideTarget || InsideExpr) {
                    Scanner_Error((STRING)"unclosed target code", 20L, TargetPos);
                  }
                  break;
                case expr:;
                case targetcode:;
                  Scanner_Error((STRING)"unclosed target code", 20L, TargetPos);
                  break;
                case CStr1:;
                case CStr2:;
                case Str1:;
                case Str2:;
                  Scanner_Error((STRING)"unclosed string", 15L, StringPos);
                  if (InsideTarget || InsideExpr) {
                    Scanner_Error((STRING)"unclosed target code", 20L, TargetPos);
                  }
                  break;
                default :
                  break;
                }
                BraceNestingLevel = 0;
                CommentNestingLevel = 0;
              }
              if (yyFileStackPtr == 0) {
                G_1_TargetCode = L_1;
                G_2_Word = L_2;
                return Scanner_EofToken;
              }
              yyRestartFlag = FALSE;
              goto EXIT_4;
            }
          }
          break;
        default :
          yyErrorMessage(0);
          break;
        }
      } EXIT_4:;
      if (yyRestartFlag) {
      } else {
        goto EXIT_2;
      }
    } EXIT_2:;
  } EXIT_1:;
}

void Scanner_BeginFile
# ifdef __STDC__
(CHAR FileName[], LONGCARD O_5)
# else
(FileName, O_5)
CHAR FileName[];
LONGCARD O_5;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_5 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(FileName, O_5, CHAR)
  if (yyStateStack->A[0] == yyDNoState) {
    yyGetTables();
    yyStateStack->A[0] = yyDefaultState;
  }
  yyInitialize();
  yySourceFile = Source_BeginSource(FileName, O_5);
  if (yySourceFile < 0) {
    yyErrorMessage(5);
  }
  FREE_OPEN_ARRAYS
}

static void yyInitialize
# ifdef __STDC__
()
# else
()
# endif
{
  if (yyFileStackPtr >= yyFileStackSize) {
    yyErrorMessage(3);
  }
  INC(yyFileStackPtr);
  {
    register struct S_14 *W_1 = &yyFileStack.A[yyFileStackPtr - 1];

    W_1->SourceFile = yySourceFile;
    W_1->Eof = yyEof;
    W_1->ChBufferPtr = yyChBufferPtr;
    W_1->ChBufferStart = yyChBufferStart;
    W_1->ChBufferSize = yyChBufferSize;
    W_1->ChBufferIndex = yyChBufferIndex;
    W_1->BytesRead = yyBytesRead;
    W_1->LineCount = yyLineCount;
    W_1->LineStart = yyLineStart;
  }
  yyChBufferSize = yyInitBufferSize;
  DynArray_MakeArray((ADDRESS *)&yyChBufferPtr, &yyChBufferSize, (LONGINT)sizeof(CHAR));
  if (yyChBufferPtr == NIL) {
    yyErrorMessage(1);
  }
  yyChBufferStart = General_MaxAlign;
  yyChBufferPtr->A[yyChBufferStart - 1] = yyEolCh;
  yyChBufferPtr->A[yyChBufferStart] = yyEobCh;
  yyChBufferPtr->A[yyChBufferStart + 1] = '\0';
  yyChBufferIndex = yyChBufferStart;
  yyEof = FALSE;
  yyBytesRead = 0;
  yyLineCount = 1;
  yyTotalLineCount = 0;
  yyLineStart = yyChBufferStart - 1;
}

void Scanner_CloseFile
# ifdef __STDC__
()
# else
()
# endif
{
  if (yyFileStackPtr == 0) {
    yyErrorMessage(4);
  }
  Source_CloseSource(yySourceFile);
  DynArray_ReleaseArray((ADDRESS *)&yyChBufferPtr, &yyChBufferSize, (LONGINT)sizeof(CHAR));
  {
    register struct S_14 *W_2 = &yyFileStack.A[yyFileStackPtr - 1];

    yySourceFile = W_2->SourceFile;
    yyEof = W_2->Eof;
    yyChBufferPtr = W_2->ChBufferPtr;
    yyChBufferStart = W_2->ChBufferStart;
    yyChBufferSize = W_2->ChBufferSize;
    yyChBufferIndex = W_2->ChBufferIndex;
    yyBytesRead = W_2->BytesRead;
    yyLineCount = W_2->LineCount;
    yyLineStart = W_2->LineStart;
  }
  DEC(yyFileStackPtr);
}

void Scanner_GetWord
# ifdef __STDC__
(Strings_tString *Word)
# else
(Word)
Strings_tString *Word;
# endif
{
  INTEGER i, WordStart;

  WordStart = yyChBufferIndex - Scanner_TokenLength - 1;
  {
    LONGINT B_3 = 1, B_4 = Scanner_TokenLength;

    if (B_3 <= B_4)
      for (i = B_3;; i += 1) {
        Word->Chars.A[VAL(Strings_tStringIndex, i)] = yyChBufferPtr->A[WordStart + i];
        if (i >= B_4) break;
      }
  }
  Word->Length = VAL(SHORTCARD, Scanner_TokenLength);
}

void Scanner_GetLower
# ifdef __STDC__
(Strings_tString *Word)
# else
(Word)
Strings_tString *Word;
# endif
{
  INTEGER i, WordStart;

  WordStart = yyChBufferIndex - Scanner_TokenLength - 1;
  {
    LONGINT B_5 = 1, B_6 = Scanner_TokenLength;

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        Word->Chars.A[VAL(Strings_tStringIndex, i)] = yyToLower.A[yyChBufferPtr->A[WordStart + i]];
        if (i >= B_6) break;
      }
  }
  Word->Length = VAL(SHORTCARD, Scanner_TokenLength);
}

void Scanner_GetUpper
# ifdef __STDC__
(Strings_tString *Word)
# else
(Word)
Strings_tString *Word;
# endif
{
  INTEGER i, WordStart;

  WordStart = yyChBufferIndex - Scanner_TokenLength - 1;
  {
    LONGINT B_7 = 1, B_8 = Scanner_TokenLength;

    if (B_7 <= B_8)
      for (i = B_7;; i += 1) {
        Word->Chars.A[VAL(Strings_tStringIndex, i)] = yyToUpper.A[yyChBufferPtr->A[WordStart + i]];
        if (i >= B_8) break;
      }
  }
  Word->Length = VAL(SHORTCARD, Scanner_TokenLength);
}

static void yyStart
# ifdef __STDC__
(yyStateRange State)
# else
(State)
yyStateRange State;
# endif
{
  yyPreviousStart = yyStartState;
  yyStartState = State;
}

static void yyPrevious
# ifdef __STDC__
()
# else
()
# endif
{
  yyStateRange s;

  s = yyStartState;
  yyStartState = yyPreviousStart;
  yyPreviousStart = s;
}

static void yyEcho
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER i;

  {
    LONGINT B_9 = yyChBufferIndex - Scanner_TokenLength, B_10 = yyChBufferIndex - 1;

    if (B_9 <= B_10)
      for (i = B_9;; i += 1) {
        IO_WriteC((System_tFile)IO_StdOutput, yyChBufferPtr->A[i]);
        if (i >= B_10) break;
      }
  }
}

static void yyLess
# ifdef __STDC__
(INTEGER n)
# else
(n)
INTEGER n;
# endif
{
  DEC1(yyChBufferIndex, Scanner_TokenLength - n);
  Scanner_TokenLength = n;
}

static void yyTab
# ifdef __STDC__
()
# else
()
# endif
{
  DEC1(yyLineStart, yyTabSpace - 1 - (yyChBufferIndex - yyLineStart - 2) % yyTabSpace);
}

static void yyTab1
# ifdef __STDC__
(INTEGER a)
# else
(a)
INTEGER a;
# endif
{
  DEC1(yyLineStart, yyTabSpace - 1 - (yyChBufferIndex - yyLineStart - Scanner_TokenLength + a - 1) % yyTabSpace);
}

static void yyTab2
# ifdef __STDC__
(INTEGER a, INTEGER b)
# else
(a, b)
INTEGER a, b;
# endif
{
  DEC1(yyLineStart, yyTabSpace - 1 - (yyChBufferIndex - yyLineStart - Scanner_TokenLength + a - 1) % yyTabSpace);
}

static void yyEol
# ifdef __STDC__
(INTEGER Column)
# else
(Column)
INTEGER Column;
# endif
{
  INC(yyLineCount);
  INC(yyTotalLineCount);
  yyLineStart = yyChBufferIndex - 1 - Column;
}

static void output
# ifdef __STDC__
(CHAR c)
# else
(c)
CHAR c;
# endif
{
  IO_WriteC((System_tFile)IO_StdOutput, c);
}

static void unput
# ifdef __STDC__
(CHAR c)
# else
(c)
CHAR c;
# endif
{
  DEC(yyChBufferIndex);
  yyChBufferPtr->A[yyChBufferIndex] = c;
}

static CHAR input
# ifdef __STDC__
()
# else
()
# endif
{
  if (yyChBufferIndex == yyChBufferStart + yyBytesRead) {
    if (!yyEof) {
      DEC1(yyLineStart, yyBytesRead);
      DEC1(yyLineStart, yyChBufferStart);
      yyChBufferIndex = 0;
      yyChBufferStart = 0;
      yyBytesRead = Source_GetLine(yySourceFile, (ADDRESS)yyChBufferPtr, VAL(CARDINAL, General_Exp2(General_Log2(yyChBufferSize))));
      if (yyBytesRead <= 0) {
        yyBytesRead = 0;
        yyEof = TRUE;
      }
      yyChBufferPtr->A[yyBytesRead] = yyEobCh;
      yyChBufferPtr->A[yyBytesRead + 1] = '\0';
    }
  }
  if (yyChBufferIndex == yyChBufferStart + yyBytesRead) {
    return '\0';
  } else {
    INC(yyChBufferIndex);
    return yyChBufferPtr->A[yyChBufferIndex - 1];
  }
}

CHAR Scanner_UpperCase
# ifdef __STDC__
(CHAR Ch)
# else
(Ch)
CHAR Ch;
# endif
{
  return yyToUpper.A[Ch];
}

CHAR Scanner_LowerCase
# ifdef __STDC__
(CHAR Ch)
# else
(Ch)
CHAR Ch;
# endif
{
  return yyToLower.A[Ch];
}

CARDINAL Scanner_TotalLineCount
# ifdef __STDC__
()
# else
()
# endif
{
  return yyTotalLineCount;
}

void Scanner_BeginScanner
# ifdef __STDC__
()
# else
()
# endif
{
  BraceNestingLevel = 0;
  CommentNestingLevel = 0;
  InsideTarget = FALSE;
  InsideExpr = FALSE;
}

void Scanner_CloseScanner
# ifdef __STDC__
()
# else
()
# endif
{
}

static void yyGetTables
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL BlockSize, j, n;
  System_tFile TableFile;
  yyStateRange i;
  struct S_16 Base;

  BlockSize = 64000 / sizeof(yyCombType);
  TableFile = OpenInput(Scanner_ScanTabName.A, 128L);
  Checks_ErrorCheck((STRING)"yyGetTables.OpenInput", 21L, TableFile);
  if (yyGetTable(TableFile, ADR(Base)) / sizeof(yyTableElmt) - 1 != yyDStateCount || yyGetTable(TableFile, ADR(yyDefault)) / sizeof(yyTableElmt) - 1 != yyDStateCount || yyGetTable(TableFile, ADR(yyEobTrans)) / sizeof(yyTableElmt) - 1 != yyDStateCount) {
    yyErrorMessage(2);
  }
  n = 0;
  j = 0;
  while (j <= yyTableSize) {
    INC1(n, yyGetTable(TableFile, ADR(yyComb.A[VAL(SHORTCARD, j)])) / sizeof(yyCombType));
    INC1(j, BlockSize);
  }
  if (n != yyTableSize + 1) {
    yyErrorMessage(2);
  }
  Close(TableFile);
  for (i = 0; i <= yyDStateCount; i += 1) {
    yyBasePtr.A[i] = (LONGCARD)ADR(yyComb.A[Base.A[i]]);
  }
}

static CARDINAL yyGetTable
# ifdef __STDC__
(System_tFile TableFile, ADDRESS Address)
# else
(TableFile, Address)
System_tFile TableFile;
ADDRESS Address;
# endif
{
  INTEGER N;
  yyTableElmt Length;

  N = Read(TableFile, ADR(Length), (LONGINT)sizeof(yyTableElmt));
  Checks_ErrorCheck((STRING)"yyGetTable.Read1", 16L, N);
  N = Read(TableFile, Address, VAL(INTEGER, Length));
  Checks_ErrorCheck((STRING)"yyGetTable.Read2", 16L, N);
  return VAL(CARDINAL, Length);
}

static void yyErrorMessage
# ifdef __STDC__
(SHORTCARD ErrorCode)
# else
(ErrorCode)
SHORTCARD ErrorCode;
# endif
{
  Positions_WritePosition((System_tFile)IO_StdError, Scanner_Attribute.Position);
  switch (ErrorCode) {
  case 0:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: internal error", 25L);
    break;
  case 1:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: out of memory", 24L);
    break;
  case 2:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: table mismatch", 25L);
    break;
  case 3:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: too many nested include files", 40L);
    break;
  case 4:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: file stack underflow (too many calls of CloseFile)", 61L);
    break;
  case 5:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)": Scanner: cannot open input file", 33L);
    break;
  }
  IO_WriteNl((System_tFile)IO_StdError);
  (*Scanner_Exit)();
}

static void yyExit
# ifdef __STDC__
()
# else
()
# endif
{
  IO_CloseIO();
  Exit(1L);
}

void Scanner__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Strings__init();
    StringMem__init();
    Idents__init();
    Texts__init();
    Positions__init();
    Strings__init();
    Checks__init();
    System__init();
    General__init();
    Positions__init();
    IO__init();
    DynArray__init();
    Strings__init();
    Source__init();
    StringMem__init();
    Strings__init();
    Idents__init();
    Texts__init();
    Sets__init();
    Tree__init();
    Positions__init();
    Errors__init();

    (void)strncpy((char *)Scanner_ScanTabName.A, "Scanner.Tab", sizeof(Scanner_ScanTabName.A));
    Scanner_Exit = yyExit;
    yyFileStackPtr = 0;
    yyStartState = 1;
    yyPreviousStart = 1;
    yyBasePtr.A[yyStartState] = (LONGCARD)ADR(yyComb.A[0]);
    yyDefault.A[yyStartState] = yyDNoState;
    yyComb.A[0].Check = yyDNoState;
    yyChBufferPtr = (yytChBufferPtr)ADR(yyComb.A[0]);
    yyChBufferIndex = 1;
    yyStateStackSize = yyInitBufferSize;
    DynArray_MakeArray((ADDRESS *)&yyStateStack, &yyStateStackSize, (LONGINT)sizeof(yyStateRange));
    yyStateStack->A[0] = yyDNoState;
    for (yyCh = yyFirstCh; yyCh <= yyLastCh; yyCh += 1) {
      yyToLower.A[yyCh] = yyCh;
    }
    yyToUpper = yyToLower;
    for (yyCh = 'A'; yyCh <= 'Z'; yyCh += 1) {
      yyToLower.A[yyCh] = CHR(ORD(yyCh) - ORD('A') + ORD('a'));
    }
    for (yyCh = 'a'; yyCh <= 'z'; yyCh += 1) {
      yyToUpper.A[yyCh] = CHR(ORD(yyCh) - ORD('a') + ORD('A'));
    }
  }
}
