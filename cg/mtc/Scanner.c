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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
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

INTEGER Scanner_CurArg, Scanner_ArgCount;
INTEGER Scanner_TokenLength;
Scanner_tScanAttribute Scanner_Attribute;
struct Scanner_2 Scanner_ScanTabName;
PROC Scanner_Exit;

#define TokIdentifier   1
#define TokInteger   2
#define TokString   3
#define TokTargetCode   4
#define TokCode   5
#define TokWhiteSpace   7
#define TokAfter   24
#define TokBefore   25
#define TokBegin   10
#define TokBodyWith   80
#define TokCheck   26
#define TokClose   11
#define TokDeclare   12
#define TokDemand   28
#define TokEnd   13
#define TokEval   14
#define TokExport   15
#define TokFor   71
#define TokFunction   6
#define TokGlobal   16
#define TokIgnore   72
#define TokImport   30
#define TokInherited   34
#define TokInput   31
#define TokLeft   37
#define TokLink   81
#define TokLocal   18
#define TokModule   19
#define TokNone   39
#define TokOutput   32
#define TokParser   35
#define TokPrec   36
#define TokProperty   70
#define TokRemote   76
#define TokReverse   21
#define TokRight   38
#define TokRule   22
#define TokScanner   77
#define TokSelect   74
#define TokSpecWith   79
#define TokStack   20
#define TokSubunit   75
#define TokSynthesized   33
#define TokThread   27
#define TokTree   23
#define TokView   78
#define TokVirtual   17
#define TokLParent   40
#define TokRParent   41
#define TokLBracket   42
#define TokRBracket   43
#define TokLBrace   44
#define TokRBrace   45
#define TokComma   46
#define TokSemiColon   47
#define TokDot   48
#define TokColon   49
#define TokEqual   50
#define TokBar   51
#define TokAssign   52
#define TokPlus   53
#define TokMinus   54
#define TokAsterisk   55
#define TokSlash   56
#define TokLAngle   57
#define TokRAngle   58
#define TokRArrow   59
#define TokCopy   60
#define TokArrow   61
#define TokLArrow   62
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
#define yyDStateCount   329
#define yyTableSize   2934
#define yyEobState   98
#define yyDefaultState   99
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
typedef struct S_2 {
    CHAR A[1000000 + 1];
} *yytChBufferPtr;
typedef CHAR yyChRange;
typedef SHORTCARD yyFileStackPtrTyp;
typedef yyFileStackPtrTyp yyFileStackSubscript;
static struct S_3 {
    LONGCARD A[yyDStateCount + 1];
} yyBasePtr;
static struct S_4 {
    yyStateRange A[yyDStateCount + 1];
} yyDefault;
static struct S_5 {
    yyCombType A[yyTableSize + 1];
} yyComb;
static struct S_6 {
    yyStateRange A[yyDStateCount + 1];
} yyEobTrans;
static struct S_7 {
    CHAR A[yyLastCh + 1];
} yyToLower, yyToUpper;
static struct S_8 {
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
static struct S_9 {
    struct S_10 {
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
struct S_12 {
    CHAR A[255 + 1];
};
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
struct S_13 {
    yyTableRange A[yyDStateCount + 1];
};
static CARDINAL yyGetTable ARGS((System_tFile TableFile, ADDRESS Address));
static void yyErrorMessage ARGS((SHORTCARD ErrorCode));
static void yyExit ARGS(());

static Strings_tString *G_1_TargetCode;
static Strings_tString *G_2_Word;

void Scanner_ErrorAttribute
# ifdef __STDC__
(CARDINAL Token, Scanner_tScanAttribute *Attribute)
# else
(Token, Attribute)
CARDINAL Token;
Scanner_tScanAttribute *Attribute;
# endif
{
  {
    register Scanner_tScanAttribute *W_1 = Attribute;

    switch (Token) {
    case TokIdentifier:;
      W_1->U_1.V_2.Ident = Idents_NoIdent;
      break;
    case TokInteger:;
      W_1->U_1.V_3.Integer = 0;
      break;
    case TokTargetCode:;
      Texts_MakeText(&W_1->U_1.V_4.Text);
      break;
    case TokString:;
    case TokCode:;
    case TokWhiteSpace:;
      W_1->U_1.V_1.StringRef = Idents_GetStringRef(Idents_NoIdent);
      break;
    default :
      break;
    }
  }
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
  Strings_tString String, Word, TargetCode;
  struct S_12 Argument;
  SHORTCARD j;
  CHAR ch;
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
        case 329:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel == 0) {
            Texts_MakeText(&Scanner_Attribute.U_1.V_4.Text);
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
        case 328:;
          DEC(BraceNestingLevel);
          if (BraceNestingLevel == 0) {
            yyStart(STD);
            InsideTarget = FALSE;
            Texts_Append(&Scanner_Attribute.U_1.V_4.Text, &TargetCode);
            Scanner_Attribute.Position = TargetPos;
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokTargetCode;
          } else {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 26:;
        case 52:;
        case 109:;
        case 318:;
        case 324:;
          if (BraceNestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 327:;
          if (BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 326:;
          if (BraceNestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_4.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 27:;
          if (BraceNestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Append(&TargetCode, Strings_Char(&Word, 2));
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 49:;
          if (BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\\');
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 323:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          AccumComment();
          CommentNestingLevel = 1;
          CommentPos = Scanner_Attribute.Position;
          yyStart(M2Comment);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 322:;
          INC(CommentNestingLevel);
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 320:;
          AccumComment();
          DEC(CommentNestingLevel);
          if (CommentNestingLevel == 0) {
            yyPrevious();
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 32:;
        case 55:;
        case 104:;
        case 319:;
        case 321:;
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 317:;
          AccumComment();
          yyStart(CComment);
          CommentPos = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 315:;
          AccumComment();
          yyPrevious();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 33:;
        case 56:;
        case 103:;
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 314:;
          if (InsideTarget && BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 313:;
          if (InsideTarget && BraceNestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_4.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 35:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 34:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_3.Integer = Strings_StringToInt(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokInteger;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 312:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (Sets_IsElement(ORD('c'), &Tree_Options)) {
            yyStart(CStr1);
          } else {
            yyStart(Str1);
          }
          StringPos = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 311:;
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
        case 31:;
        case 105:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 30:;
        case 106:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 29:;
        case 54:;
        case 78:;
        case 107:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 28:;
        case 53:;
        case 77:;
        case 108:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 310:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 309:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 308:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 307:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 306:;
          Strings_Append(&String, '\t');
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 305:;
          Errors_Message((STRING)"unclosed string", 15L, (LONGCARD)Errors_Error, Scanner_Attribute.Position);
          INC(Tree_ErrorCount);
          Strings_Append(&String, Strings_Char(&String, 1));
          yyEol(0L);
          yyPrevious();
          if (yyStartState == targetcode) {
            Strings_Concatenate(&TargetCode, &String);
          } else {
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 304:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 303:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokRParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 302:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokComma;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 301:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokRArrow;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 299:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokDot;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 36:;
        case 57:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 297:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLAngle;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 298:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLArrow;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 296:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokEqual;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 295:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokRAngle;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 294:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 293:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokRBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 292:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel == 0) {
            TargetPos = Scanner_Attribute.Position;
          }
          yyStart(expr);
          INC(BraceNestingLevel);
          InsideExpr = TRUE;
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 291:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokAfter;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 286:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokBefore;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 280:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokCheck;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 275:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokRemote;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 20:;
        case 47:;
        case 76:;
        case 262:;
        case 325:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 269:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel <= 1) {
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokAssign;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 268:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel <= 1) {
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokCopy;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 267:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel <= 1) {
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokSemiColon;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 22:;
        case 48:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 266:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokArrow;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 264:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          INC(BraceNestingLevel);
          if (BraceNestingLevel <= 2) {
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokLBrace;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 263:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          DEC(BraceNestingLevel);
          if (BraceNestingLevel == 0) {
            yyStart(STD);
            InsideExpr = FALSE;
          }
          if (BraceNestingLevel <= 1) {
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokRBrace;
          } else {
            Scanner_GetWord(&Word);
            Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
            G_1_TargetCode = L_1;
            G_2_Word = L_2;
            return TokCode;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 261:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 260:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 21:;
        case 110:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokWhiteSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 259:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          yyEol(0L);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokWhiteSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 258:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          yyTab();
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokWhiteSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 24:;
        case 51:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, 2, &String);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 25:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &String);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&String);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 50:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.StringRef = StringMem_PutString(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokCode;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 257:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokBegin;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 253:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokBodyWith;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 245:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokClose;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 240:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokDeclare;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 235:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokDemand;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 229:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokEnd;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 227:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokEval;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 224:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokExport;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 218:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokFor;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 216:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokFunction;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 208:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokGlobal;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 202:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokIgnore;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 197:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokImport;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 42:;
        case 58:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokInput;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 43:;
        case 94:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokInherited;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 192:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLeft;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 189:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLink;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 186:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokLocal;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 181:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokModule;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 175:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokNone;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 41:;
        case 79:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokOutput;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 171:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokParser;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 166:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokPrec;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 164:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokProperty;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 40:;
        case 93:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokReverse;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 156:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokRight;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 152:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokRule;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 149:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokScanner;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 143:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokSelect;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 138:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(targetcode);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokSpecWith;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 131:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokStack;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 127:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokSubunit;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 39:;
        case 92:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokSynthesized;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 121:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokThread;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 116:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokTree;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 112:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokView;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 38:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokVirtual;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 19:;
        case 44:;
        case 45:;
        case 46:;
        case 59:;
        case 60:;
        case 61:;
        case 62:;
        case 63:;
        case 64:;
        case 65:;
        case 66:;
        case 67:;
        case 68:;
        case 69:;
        case 70:;
        case 71:;
        case 72:;
        case 73:;
        case 74:;
        case 75:;
        case 80:;
        case 81:;
        case 82:;
        case 83:;
        case 84:;
        case 85:;
        case 86:;
        case 87:;
        case 88:;
        case 89:;
        case 90:;
        case 91:;
        case 95:;
        case 96:;
        case 111:;
        case 113:;
        case 114:;
        case 115:;
        case 117:;
        case 118:;
        case 119:;
        case 120:;
        case 122:;
        case 123:;
        case 124:;
        case 125:;
        case 126:;
        case 128:;
        case 129:;
        case 130:;
        case 132:;
        case 133:;
        case 134:;
        case 135:;
        case 136:;
        case 137:;
        case 139:;
        case 140:;
        case 141:;
        case 142:;
        case 144:;
        case 145:;
        case 146:;
        case 147:;
        case 148:;
        case 150:;
        case 151:;
        case 153:;
        case 154:;
        case 155:;
        case 157:;
        case 158:;
        case 159:;
        case 160:;
        case 161:;
        case 162:;
        case 163:;
        case 165:;
        case 167:;
        case 168:;
        case 169:;
        case 170:;
        case 172:;
        case 173:;
        case 174:;
        case 176:;
        case 177:;
        case 178:;
        case 179:;
        case 180:;
        case 182:;
        case 183:;
        case 184:;
        case 185:;
        case 187:;
        case 188:;
        case 190:;
        case 191:;
        case 193:;
        case 194:;
        case 195:;
        case 196:;
        case 198:;
        case 199:;
        case 200:;
        case 201:;
        case 203:;
        case 204:;
        case 205:;
        case 206:;
        case 207:;
        case 209:;
        case 210:;
        case 211:;
        case 212:;
        case 213:;
        case 214:;
        case 215:;
        case 217:;
        case 219:;
        case 220:;
        case 221:;
        case 222:;
        case 223:;
        case 225:;
        case 226:;
        case 228:;
        case 230:;
        case 231:;
        case 232:;
        case 233:;
        case 234:;
        case 236:;
        case 237:;
        case 238:;
        case 239:;
        case 241:;
        case 242:;
        case 243:;
        case 244:;
        case 246:;
        case 247:;
        case 248:;
        case 249:;
        case 250:;
        case 251:;
        case 252:;
        case 254:;
        case 255:;
        case 256:;
        case 270:;
        case 271:;
        case 272:;
        case 273:;
        case 274:;
        case 276:;
        case 277:;
        case 278:;
        case 279:;
        case 281:;
        case 282:;
        case 283:;
        case 284:;
        case 285:;
        case 287:;
        case 288:;
        case 289:;
        case 290:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_2.Ident = Idents_MakeIdent(&Word);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokIdentifier;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 37:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &String);
          Scanner_Attribute.U_1.V_2.Ident = Idents_MakeIdent(&String);
          G_1_TargetCode = L_1;
          G_2_Word = L_2;
          return TokIdentifier;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 102:;
          while (yyChBufferPtr->A[yyChBufferIndex] == ' ') {
            INC(yyChBufferIndex);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 101:;
          DEC1(yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) % 8);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 100:;
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
        case 23:;
        case 97:;
        case 265:;
        case 300:;
        case 316:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 99:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart);
          INC(yyChBufferIndex);
          Scanner_TokenLength = 1;
          Scanner_GetWord(&Word);
          Errors_MessageI((STRING)"illegal character", 17L, (LONGCARD)Errors_Error, Scanner_Attribute.Position, (LONGCARD)Errors_String, ADR(Word));
          INC(Tree_ErrorCount);
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
        case 98:;
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
                case targetcode:;
                case expr:;
                  Errors_Message((STRING)"unclosed target code", 20L, (LONGCARD)Errors_Error, TargetPos);
                  INC(Tree_ErrorCount);
                  break;
                case CComment:;
                case M2Comment:;
                  Errors_Message((STRING)"unclosed comment", 16L, (LONGCARD)Errors_Error, CommentPos);
                  INC(Tree_ErrorCount);
                  if (InsideTarget || InsideExpr) {
                    Errors_Message((STRING)"unclosed target code", 20L, (LONGCARD)Errors_Error, TargetPos);
                    INC(Tree_ErrorCount);
                  }
                  break;
                case CStr1:;
                case CStr2:;
                case Str1:;
                case Str2:;
                  Errors_Message((STRING)"unclosed string", 15L, (LONGCARD)Errors_Error, StringPos);
                  INC(Tree_ErrorCount);
                  if (InsideTarget || InsideExpr) {
                    Errors_Message((STRING)"unclosed target code", 20L, (LONGCARD)Errors_Error, TargetPos);
                    INC(Tree_ErrorCount);
                  }
                  break;
                default :
                  break;
                }
                BraceNestingLevel = 0;
                CommentNestingLevel = 0;
                InsideTarget = FALSE;
                InsideExpr = FALSE;
                yyStart(STD);
                INC(Scanner_CurArg);
                if (Scanner_CurArg <= Scanner_ArgCount) {
                  GetArgument(Scanner_CurArg, Argument.A, 256L);
                  j = 0;
                  do {
                    ch = Argument.A[j];
                    Tree_SourceFile.A[j] = ch;
                    INC(j);
                  } while (!(ch == '\0'));
                  Scanner_BeginFile(Tree_SourceFile.A, 256L);
                  Strings_ArrayToString(Tree_SourceFile.A, 256L, &String);
                  Scanner_Attribute.Position.File = Idents_MakeIdent(&String);
                }
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
(CHAR FileName[], LONGCARD O_1)
# else
(FileName, O_1)
CHAR FileName[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(FileName, O_1, CHAR)
  if (yyStateStack->A[0] == yyDNoState) {
    yyGetTables();
    yyStateStack->A[0] = yyDefaultState;
  }
  yyInitialize();
  yySourceFile = Source_BeginSource(FileName, O_1);
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
    register struct S_10 *W_2 = &yyFileStack.A[yyFileStackPtr - 1];

    W_2->SourceFile = yySourceFile;
    W_2->Eof = yyEof;
    W_2->ChBufferPtr = yyChBufferPtr;
    W_2->ChBufferStart = yyChBufferStart;
    W_2->ChBufferSize = yyChBufferSize;
    W_2->ChBufferIndex = yyChBufferIndex;
    W_2->BytesRead = yyBytesRead;
    W_2->LineCount = yyLineCount;
    W_2->LineStart = yyLineStart;
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
    register struct S_10 *W_3 = &yyFileStack.A[yyFileStackPtr - 1];

    yySourceFile = W_3->SourceFile;
    yyEof = W_3->Eof;
    yyChBufferPtr = W_3->ChBufferPtr;
    yyChBufferStart = W_3->ChBufferStart;
    yyChBufferSize = W_3->ChBufferSize;
    yyChBufferIndex = W_3->ChBufferIndex;
    yyBytesRead = W_3->BytesRead;
    yyLineCount = W_3->LineCount;
    yyLineStart = W_3->LineStart;
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
  struct S_13 Base;

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
    Checks__init();
    System__init();
    General__init();
    Positions__init();
    IO__init();
    DynArray__init();
    Strings__init();
    Source__init();
    System__init();
    StringMem__init();
    Strings__init();
    Idents__init();
    Texts__init();
    Tree__init();
    Sets__init();
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
