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

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_ScanGen
#include "ScanGen.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

INTEGER Scanner_TokenLength;
Scanner_tScanAttribute Scanner_Attribute;
struct Scanner_2 Scanner_ScanTabName;
PROC Scanner_Exit;

#define SymIdent   1
#define SymNumber   2
#define SymString   3
#define SymChar   4
#define SymTargetcode   5
#define SymScanner   37
#define SymExport   32
#define SymGlobal   6
#define SymLocal   31
#define SymBegin   7
#define SymClose   8
#define SymEof   34
#define SymDefault   36
#define SymDefine   9
#define SymStart   10
#define SymRules   11
#define SymNot   30
#define SymDot   12
#define SymComma   13
#define SymEqual   14
#define SymColon   15
#define SymColonMinus   35
#define SymNrSign   33
#define SymSlash   16
#define SymBar   17
#define SymPlus   18
#define SymMinus   19
#define SymAsterisk   20
#define SymQuestion   21
#define SymLParen   22
#define SymRParen   23
#define SymLBracket   24
#define SymRBracket   25
#define SymLBrace   26
#define SymRBrace   27
#define SymLess   28
#define SymGreater   29
#define BraceMissing   13
#define UnclosedComment   14
#define UnclosedString   16
static INTEGER BraceNestingLevel, CommentNestingLevel;
static Strings_tString string;
static StringMem_tStringRef NoString;
static Positions_tPosition TargetPos;
static Positions_tPosition CommentPos;
static Positions_tPosition StringPos;
static SHORTCARD PrevState;
static BOOLEAN InsideTarget;
#define yyTabSpace   8
#define yyDNoState   0
#define yyFileStackSize   16
#define yyInitBufferSize   (1024 * 8 + 256)
#define yyFirstCh   '\0'
#define yyLastCh   ((CHAR)'\377')
#define yyEolCh   '\n'
#define yyEobCh   ((CHAR)'\177')
#define yyDStateCount   182
#define yyTableSize   4468
#define yyEobState   52
#define yyDefaultState   53
#define STD   1
#define targetcode   3
#define set   5
#define rules   7
#define CComment   9
#define M2Comment   11
#define Str1   13
#define Str2   15
#define CStr1   17
#define CStr2   19
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
struct S_12 {
    yyTableRange A[yyDStateCount + 1];
};
static CARDINAL yyGetTable ARGS((System_tFile TableFile, ADDRESS Address));
static void yyErrorMessage ARGS((SHORTCARD ErrorCode));
static void yyExit ARGS(());

static Strings_tString *G_1_Word;
static Strings_tString *G_2_TargetCode;

void Scanner_ErrorAttribute
# ifdef __STDC__
(CARDINAL Token, Scanner_tScanAttribute *Attribute)
# else
(Token, Attribute)
CARDINAL Token;
Scanner_tScanAttribute *Attribute;
# endif
{
  switch (Token) {
  case SymIdent:;
    Attribute->U_1.V_1.Ident = Idents_NoIdent;
    break;
  case SymNumber:;
    Attribute->U_1.V_2.Number = 0;
    break;
  case SymString:;
    Attribute->U_1.V_3.String = NoString;
    break;
  case SymChar:;
    Attribute->U_1.V_4.Ch = '?';
    break;
  case SymTargetcode:;
    Texts_MakeText(&Attribute->U_1.V_5.Text);
    break;
  default :
    break;
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
    Scanner_GetWord(G_1_Word);
    Strings_Concatenate(G_2_TargetCode, G_1_Word);
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
  Strings_tString TargetCode, String, Word;
  Strings_tString *L_1;
  Strings_tString *L_2;

  L_1 = G_1_Word;
  G_1_Word = &Word;
  L_2 = G_2_TargetCode;
  G_2_TargetCode = &TargetCode;
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
        case 182:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          if (BraceNestingLevel == 0) {
            Texts_MakeText(&Scanner_Attribute.U_1.V_5.Text);
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
        case 181:;
          DEC(BraceNestingLevel);
          if (BraceNestingLevel == 0) {
            yyStart(PrevState);
            InsideTarget = FALSE;
            Texts_Append(&Scanner_Attribute.U_1.V_5.Text, &TargetCode);
            Scanner_Attribute.Position = TargetPos;
            G_1_Word = L_1;
            G_2_TargetCode = L_2;
            return SymTargetcode;
          } else {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 34:;
        case 45:;
        case 57:;
        case 65:;
        case 73:;
        case 164:;
        case 170:;
          if (BraceNestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&TargetCode, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 180:;
          if (BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 179:;
          if (BraceNestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_5.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 35:;
          if (BraceNestingLevel > 0) {
            Scanner_GetWord(&Word);
            Strings_Append(&TargetCode, Strings_Char(&Word, 2));
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 32:;
          if (BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\\');
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 178:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (ScanGen_Language == ScanGen_C) {
            yyStart(CStr1);
          } else {
            yyStart(Str1);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 177:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (ScanGen_Language == ScanGen_C) {
            yyStart(CStr2);
          } else {
            yyStart(Str2);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 24:;
        case 60:;
        case 68:;
        case 76:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 23:;
        case 61:;
        case 69:;
        case 77:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 22:;
        case 38:;
        case 48:;
        case 62:;
        case 70:;
        case 78:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 21:;
        case 37:;
        case 47:;
        case 63:;
        case 71:;
        case 79:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 176:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 175:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 174:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          Strings_Concatenate(&TargetCode, &String);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 173:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          Strings_Concatenate(&TargetCode, &String);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 172:;
          Strings_Append(&String, '\t');
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 171:;
          Errors_ErrorMessage((LONGCARD)UnclosedString, (LONGCARD)Errors_Error, StringPos);
          Strings_Append(&String, Strings_Char(&String, 1));
          yyEol(0L);
          yyPrevious();
          Strings_Concatenate(&TargetCode, &String);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 169:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(M2Comment);
          AccumComment();
          CommentNestingLevel = 1;
          CommentPos = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 168:;
          INC(CommentNestingLevel);
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 166:;
          AccumComment();
          DEC(CommentNestingLevel);
          if (CommentNestingLevel == 0) {
            yyPrevious();
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 25:;
        case 39:;
        case 59:;
        case 67:;
        case 75:;
        case 165:;
        case 167:;
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 163:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(CComment);
          AccumComment();
          CommentPos = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 161:;
          AccumComment();
          yyPrevious();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 26:;
        case 40:;
        case 58:;
        case 66:;
        case 74:;
          AccumComment();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 160:;
          if (InsideTarget && BraceNestingLevel > 0) {
            Strings_Append(&TargetCode, '\t');
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 159:;
          if (InsideTarget && BraceNestingLevel > 0) {
            Texts_Append(&Scanner_Attribute.U_1.V_5.Text, &TargetCode);
            Strings_AssignEmpty(&TargetCode);
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 158:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = STD;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymExport;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 153:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = STD;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymGlobal;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 147:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = STD;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymLocal;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 142:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = STD;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymBegin;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 137:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = STD;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymClose;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 132:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = STD;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymDefault;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 128:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = STD;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymEof;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 125:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymScanner;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 119:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymDefine;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 113:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymStart;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 36:;
        case 46:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(rules);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymRules;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 108:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymNot;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 28:;
        case 43:;
        case 49:;
        case 50:;
        case 106:;
        case 107:;
        case 109:;
        case 110:;
        case 111:;
        case 112:;
        case 114:;
        case 115:;
        case 116:;
        case 117:;
        case 118:;
        case 120:;
        case 121:;
        case 122:;
        case 123:;
        case 124:;
        case 126:;
        case 127:;
        case 129:;
        case 130:;
        case 131:;
        case 133:;
        case 134:;
        case 135:;
        case 136:;
        case 138:;
        case 139:;
        case 140:;
        case 141:;
        case 143:;
        case 144:;
        case 145:;
        case 146:;
        case 148:;
        case 149:;
        case 150:;
        case 151:;
        case 152:;
        case 154:;
        case 155:;
        case 156:;
        case 157:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_1.Ident = Idents_MakeIdent(&Word);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymIdent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 29:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_2.Number = Strings_StringToInt(&Word);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymNumber;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 33:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)(Strings_Length(&Word) - 1), &TargetCode);
          Scanner_Attribute.U_1.V_3.String = StringMem_PutString(&TargetCode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 105:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymDot;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 104:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymEqual;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 103:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyPrevious();
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymRBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 102:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymMinus;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 101:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymComma;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 100:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymBar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 99:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymPlus;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 98:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymAsterisk;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 97:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymQuestion;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 96:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymLParen;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 95:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymRParen;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 94:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymLBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 93:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymRBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 92:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(set);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymLBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 91:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymNrSign;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 90:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymSlash;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 89:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymLess;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 88:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymGreater;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 86:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = rules;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 87:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = rules;
          yyStart(targetcode);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymColonMinus;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 85:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.U_1.V_4.Ch = '\n';
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 84:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.U_1.V_4.Ch = '\t';
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 83:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.U_1.V_4.Ch = ((CHAR)'\13');
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 82:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.U_1.V_4.Ch = '\b';
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 81:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.U_1.V_4.Ch = '\r';
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 80:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.U_1.V_4.Ch = '\f';
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 31:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &TargetCode);
          Scanner_Attribute.U_1.V_4.Ch = CHR((CARDINAL)Strings_StringToInt(&TargetCode));
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 30:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_4.Ch = Strings_Char(&Word, 2);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 27:;
        case 41:;
        case 42:;
        case 162:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_4.Ch = Strings_Char(&Word, 1);
          G_1_Word = L_1;
          G_2_TargetCode = L_2;
          return SymChar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 72:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 64:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 56:;
          while (yyChBufferPtr->A[yyChBufferIndex] == ' ') {
            INC(yyChBufferIndex);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 55:;
          DEC1(yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) % 8);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 54:;
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
        case 19:;
        case 20:;
        case 44:;
        case 51:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 53:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart);
          INC(yyChBufferIndex);
          Scanner_TokenLength = 1;
          IO_WriteC((System_tFile)IO_StdOutput, yyChBufferPtr->A[yyChBufferIndex - 1]);
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
        case 52:;
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
                case set:;
                  Errors_ErrorMessage((LONGCARD)BraceMissing, (LONGCARD)Errors_Error, TargetPos);
                  break;
                case CComment:;
                case M2Comment:;
                  Errors_ErrorMessage((LONGCARD)UnclosedComment, (LONGCARD)Errors_Error, CommentPos);
                  if (InsideTarget) {
                    Errors_ErrorMessage((LONGCARD)BraceMissing, (LONGCARD)Errors_Error, TargetPos);
                  }
                  break;
                case CStr1:;
                case CStr2:;
                case Str1:;
                case Str2:;
                  Errors_ErrorMessage((LONGCARD)UnclosedString, (LONGCARD)Errors_Error, StringPos);
                  if (InsideTarget) {
                    Errors_ErrorMessage((LONGCARD)BraceMissing, (LONGCARD)Errors_Error, TargetPos);
                  }
                  break;
                default :
                  break;
                }
                yyStart(STD);
              }
              if (yyFileStackPtr == 0) {
                G_1_Word = L_1;
                G_2_TargetCode = L_2;
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
    register struct S_10 *W_1 = &yyFileStack.A[yyFileStackPtr - 1];

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
    register struct S_10 *W_2 = &yyFileStack.A[yyFileStackPtr - 1];

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
  Strings_AssignEmpty(&string);
  NoString = StringMem_PutString(&string);
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
  struct S_12 Base;

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
    Idents__init();
    StringMem__init();
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
    Strings__init();
    Texts__init();
    StringMem__init();
    Idents__init();
    Errors__init();
    ScanGen__init();
    Positions__init();

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
    {
      CHAR B_11 = yyFirstCh, B_12 = yyLastCh;

      if (B_11 <= B_12)
        for (yyCh = B_11;; yyCh += 1) {
          yyToLower.A[yyCh] = yyCh;
          if (yyCh >= B_12) break;
        }
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
