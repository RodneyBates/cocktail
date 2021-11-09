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

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Limits
#include "Limits.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
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

#define eCharIgnored   10
#define eEolString   11
#define eUnClAction   12
#define eUnClComment   13
#define eUnClString   14
#define SymNull   0
#define SymEqual   1
#define SymColon   2
#define SymPoint   3
#define SymOr   4
#define SymStar   5
#define SymPlus   6
#define SymList   7
#define SymLBrace   8
#define SymRBrace   9
#define SymLBracket   10
#define SymRBracket   11
#define SymEXPORT   12
#define SymGLOBAL   13
#define SymLOCAL   14
#define SymBEGIN   15
#define SymCLOSE   16
#define SymTOKEN   17
#define SymOPER   18
#define SymNONE   19
#define SymLEFT   20
#define SymRIGHT   21
#define SymRULE   22
#define SymPREC   23
#define SymComment   24
#define SymNumber   25
#define SymAction   26
#define SymIdentifier   27
#define SymString   28
#define SymScanner   29
#define SymParser   30
static INTEGER BraceNestingLevel, CommentNestingLevel;
static Positions_tPosition CommentPos, StringPos, CodePos;
static BOOLEAN InsideCode;
static CARDINAL GetNumber ARGS((Strings_tString *Word));
#define yyTabSpace   8
#define yyDNoState   0
#define yyFileStackSize   16
#define yyInitBufferSize   (1024 * 8 + 256)
#define yyFirstCh   '\0'
#define yyLastCh   ((CHAR)'\177')
#define yyEolCh   '\n'
#define yyEobCh   ((CHAR)'\177')
#define yyDStateCount   164
#define yyTableSize   1743
#define yyEobState   47
#define yyDefaultState   48
#define STD   1
#define token   3
#define rule   5
#define code   7
#define Str1   9
#define Str2   11
#define CStr1   13
#define CStr2   15
#define comment   17
#define comment2   19
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


void Scanner_ErrorAttribute
# ifdef __STDC__
(INTEGER Token, Scanner_tScanAttribute *Attr)
# else
(Token, Attr)
INTEGER Token;
Scanner_tScanAttribute *Attr;
# endif
{
  Strings_tString s;

  switch (Token) {
  case SymNull:;
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
  case 21:;
  case 22:;
  case 23:;
    Attr->Mode = Scanner_Keys;
    break;
  case SymComment:;
    Attr->Mode = Scanner_Comment;
    Lists_MakeList(&Attr->U_1.V_1.Comm);
    break;
  case SymNumber:;
    Attr->Mode = Scanner_Number;
    Attr->U_1.V_2.Value = Limits_MaxShortCard;
    break;
  case SymAction:;
    Attr->Mode = Scanner_Action;
    Lists_MakeList(&Attr->U_1.V_3.Act);
    break;
  case SymIdentifier:;
  case SymString:;
    Attr->Mode = Scanner_Symbol;
    Strings_ArrayToString((STRING)"-error-", 7L, &s);
    Attr->U_1.V_4.Sym = Idents_MakeIdent(&s);
    break;
  }
}

static CARDINAL GetNumber
# ifdef __STDC__
(Strings_tString *Word)
# else
(Word)
Strings_tString *Word;
# endif
{
  CARDINAL i, n, d;

  i = 0;
  n = 0;
  while (i < Strings_Length(Word)) {
    i = i + 1;
    d = ORD(Strings_Char(Word, (Strings_tStringIndex)i)) - ORD('0');
    if (n > Limits_MaxShortCard / 10 || n * 10 > Limits_MaxShortCard - d) {
      return Limits_MaxShortCard;
    }
    n = n * 10 + d;
  }
  return n;
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
  Strings_tString Word, String, LastWord;
  CHAR c;
  SHORTCARD PrevState;

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
        case 164:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymEqual;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 163:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymOPER;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 159:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymNONE;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 155:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymLEFT;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 152:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymRIGHT;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 148:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          yyStart(rule);
          return SymRULE;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 30:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Number;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_4.Sym = Idents_MakeIdent(&Word);
          Scanner_Attribute.U_1.V_2.Value = GetNumber(&Word);
          return SymNumber;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 144:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 143:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymPoint;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 139:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymOr;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 142:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymStar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 141:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymPlus;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 140:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymList;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 74:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymLBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 138:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymRBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 137:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymLBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 136:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymRBracket;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 135:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymPREC;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 132:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymScanner;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 125:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymParser;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 119:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymEXPORT;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 113:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymGLOBAL;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 107:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymLOCAL;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 102:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymBEGIN;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 97:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          return SymCLOSE;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 92:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          yyStart(token);
          return SymTOKEN;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 33:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          Scanner_GetWord(&Word);
          Strings_SubString(&Word, 2, (Strings_tStringIndex)Strings_Length(&Word), &String);
          Scanner_Attribute.U_1.V_4.Sym = Idents_MakeIdent(&String);
          return SymIdentifier;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 31:;
        case 88:;
        case 89:;
        case 90:;
        case 91:;
        case 93:;
        case 94:;
        case 95:;
        case 96:;
        case 98:;
        case 99:;
        case 100:;
        case 101:;
        case 103:;
        case 104:;
        case 105:;
        case 106:;
        case 108:;
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
        case 128:;
        case 129:;
        case 130:;
        case 131:;
        case 133:;
        case 134:;
        case 145:;
        case 146:;
        case 147:;
        case 149:;
        case 150:;
        case 151:;
        case 153:;
        case 154:;
        case 156:;
        case 157:;
        case 158:;
        case 160:;
        case 161:;
        case 162:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_Attribute.Mode = Scanner_Keys;
          Scanner_GetWord(&Word);
          Scanner_Attribute.U_1.V_4.Sym = Idents_MakeIdent(&Word);
          return SymIdentifier;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 32:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 29:;
        case 42:;
        case 64:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&Word);
          c = Strings_Char(&Word, 1);
          Errors_ErrorMessageI((LONGCARD)eCharIgnored, (LONGCARD)Errors_eWarning, Scanner_Attribute.Position, (LONGCARD)Errors_eCharacter, ADR(c));
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 87:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          PrevState = yyStartState;
          CodePos = Scanner_Attribute.Position;
          yyStart(code);
          InsideCode = TRUE;
          Scanner_GetWord(&LastWord);
          Scanner_Attribute.Mode = Scanner_Action;
          Lists_MakeList(&Scanner_Attribute.U_1.V_3.Act);
          BraceNestingLevel = 1;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 28:;
        case 41:;
        case 52:;
        case 62:;
        case 72:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 26:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          c = '\\';
          Errors_ErrorMessageI((LONGCARD)eCharIgnored, (LONGCARD)Errors_eWarning, Scanner_Attribute.Position, (LONGCARD)Errors_eCharacter, ADR(c));
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 86:;
          yyTab();
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 85:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          Lists_Append(&Scanner_Attribute.U_1.V_3.Act, (ADDRESS)StringMem_PutString(&LastWord));
          Strings_AssignEmpty(&LastWord);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 84:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          INC(BraceNestingLevel);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 83:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          DEC(BraceNestingLevel);
          if (BraceNestingLevel == 0) {
            yyStart(PrevState);
            Scanner_Attribute.Position = CodePos;
            Lists_Append(&Scanner_Attribute.U_1.V_3.Act, (ADDRESS)StringMem_PutString(&LastWord));
            InsideCode = FALSE;
            return SymAction;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 82:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (WriteTok_Language == WriteTok_C) {
            yyStart(CStr1);
          } else {
            yyStart(Str1);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 81:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&String);
          StringPos = Scanner_Attribute.Position;
          if (WriteTok_Language == WriteTok_C) {
            yyStart(CStr2);
          } else {
            yyStart(Str2);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 27:;
        case 40:;
        case 53:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 25:;
        case 38:;
        case 54:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 24:;
        case 37:;
        case 44:;
        case 55:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 23:;
        case 36:;
        case 43:;
        case 56:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 80:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&String, &Word);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 45:;
        case 79:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (InsideCode) {
            Strings_Concatenate(&LastWord, &String);
          } else {
            Scanner_Attribute.Mode = Scanner_Symbol;
            Scanner_Attribute.U_1.V_4.Sym = Idents_MakeIdent(&String);
            return SymString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 39:;
        case 78:;
          Strings_Append(&String, Strings_Char(&String, 1));
          yyPrevious();
          if (InsideCode) {
            Strings_Concatenate(&LastWord, &String);
          } else {
            Scanner_Attribute.Mode = Scanner_Symbol;
            Scanner_Attribute.U_1.V_4.Sym = Idents_MakeIdent(&String);
            return SymString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 77:;
          Strings_Append(&String, '\t');
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 76:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Errors_ErrorMessage((LONGCARD)eEolString, (LONGCARD)Errors_eError, StringPos);
          Strings_Append(&String, Strings_Char(&String, 1));
          yyEol(0L);
          yyPrevious();
          if (InsideCode) {
            Strings_Concatenate(&LastWord, &String);
          } else {
            Scanner_Attribute.Mode = Scanner_Symbol;
            Scanner_Attribute.U_1.V_4.Sym = Idents_MakeIdent(&String);
            return SymString;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 75:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(comment);
          Scanner_GetWord(&LastWord);
          Scanner_Attribute.Mode = Scanner_Comment;
          CommentPos = Scanner_Attribute.Position;
          Lists_MakeList(&Scanner_Attribute.U_1.V_1.Comm);
          CommentNestingLevel = 1;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 73:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(comment);
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          CommentPos = Scanner_Attribute.Position;
          CommentNestingLevel = 1;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 71:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          INC(CommentNestingLevel);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 69:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          DEC(CommentNestingLevel);
          if (CommentNestingLevel == 0) {
            yyPrevious();
            if (!InsideCode) {
              Lists_Append(&Scanner_Attribute.U_1.V_1.Comm, (ADDRESS)StringMem_PutString(&LastWord));
              return SymComment;
            }
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 22:;
        case 35:;
        case 57:;
        case 68:;
        case 70:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 67:;
          yyTab();
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 66:;
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          if (InsideCode) {
            Lists_Append(&Scanner_Attribute.U_1.V_3.Act, (ADDRESS)StringMem_PutString(&LastWord));
          } else {
            Lists_Append(&Scanner_Attribute.U_1.V_1.Comm, (ADDRESS)StringMem_PutString(&LastWord));
          }
          Strings_AssignEmpty(&LastWord);
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 65:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(comment2);
          CommentPos = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 63:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(comment2);
          Scanner_GetWord(&Word);
          Strings_Concatenate(&LastWord, &Word);
          CommentPos = Scanner_Attribute.Position;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 61:;
          yyPrevious();
          if (InsideCode) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&LastWord, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 21:;
        case 34:;
        case 58:;
          if (InsideCode) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&LastWord, &Word);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 60:;
          if (InsideCode) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&LastWord, &Word);
          }
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 59:;
          if (InsideCode) {
            Scanner_GetWord(&Word);
            Strings_Concatenate(&LastWord, &Word);
            Lists_Append(&Scanner_Attribute.U_1.V_3.Act, (ADDRESS)StringMem_PutString(&LastWord));
          }
          yyEol(0L);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 51:;
          while (yyChBufferPtr->A[yyChBufferIndex] == ' ') {
            INC(yyChBufferIndex);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 50:;
          DEC1(yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) % 8);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 49:;
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
        case 46:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 48:;
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
        case 47:;
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
                case code:;
                  Errors_ErrorMessage((LONGCARD)eUnClAction, (LONGCARD)Errors_eError, CodePos);
                  break;
                case comment:;
                case comment2:;
                  Errors_ErrorMessage((LONGCARD)eUnClComment, (LONGCARD)Errors_eError, CommentPos);
                  if (InsideCode) {
                    Errors_ErrorMessage((LONGCARD)eUnClAction, (LONGCARD)Errors_eError, CodePos);
                  }
                  break;
                case Str1:;
                case Str2:;
                case CStr1:;
                case CStr2:;
                  Errors_ErrorMessage((LONGCARD)eUnClString, (LONGCARD)Errors_eError, StringPos);
                  if (InsideCode) {
                    Errors_ErrorMessage((LONGCARD)eUnClAction, (LONGCARD)Errors_eError, CodePos);
                  }
                  break;
                default :
                  break;
                }
              }
              if (yyFileStackPtr == 0) {
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
  InsideCode = FALSE;
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
    StringMem__init();
    Idents__init();
    Rules__init();
    Lists__init();
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
    StringMem__init();
    Idents__init();
    Lists__init();
    Limits__init();
    WriteTok__init();
    Errors__init();
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
