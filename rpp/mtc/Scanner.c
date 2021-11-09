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

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

struct Scanner_2 Scanner_InfoFileName;
INTEGER Scanner_TokenLength;
Scanner_tScanAttribute Scanner_Attribute;
struct Scanner_3 Scanner_ScanTabName;
PROC Scanner_Exit;

static CHAR MissingInfo [] = "rpp: cannot access file <Scanner>.rpp";
static CARDINAL Level, l;
static Strings_tString StartString;
static Strings_tString TheWord;
static BOOLEAN IsCollecting;
static BOOLEAN BothFlag;
static BOOLEAN Returning;
static Strings_tString InsText;
static IO_tFile InfoFile;
static Idents_tIdent LastIdent;
static struct S_2 {
    SHORTCARD A[1023 + 1];
} TokenCode;
static struct S_3 {
    StringMem_tStringRef A[1023 + 1];
} TokenSelector;
static Strings_tString Not1, Not2, Not3;
static Strings_tString Any1, Any2, Any3;
static struct S_4 {
    CHAR A[127 + 1];
} Argument;
static SHORTCARD i;
#define Modula        0
#define C        1
static unsigned char Language;
static void Skip ARGS(());
static void DoText ARGS(());
static void DoIdent ARGS(());
static void CopyText ARGS(());
static void GenPosition ARGS(());
static void GenScanAttr ARGS(());
static void GenErrorAttr ARGS(());
static void ReadIdents ARGS(());
struct S_15 {
    CHAR A[255 + 1];
};
static void InsertRules ARGS(());
struct S_16 {
    CHAR A[255 + 1];
};
static void WriteIdent ARGS((Strings_tString *TheWord));
struct S_17 {
    CHAR A[255 + 1];
};
#define yyTabSpace   8
#define yyDNoState   0
#define yyFileStackSize   16
#define yyInitBufferSize   (1024 * 8 + 256)
#define yyFirstCh   '\0'
#define yyLastCh   ((CHAR)'\177')
#define yyEolCh   '\n'
#define yyEobCh   ((CHAR)'\177')
#define yyDStateCount   154
#define yyTableSize   1254
#define yyEobState   132
#define yyDefaultState   133
#define STD   1
#define Return   3
#define Start   5
#define Action   7
#define Rules   9
#define Set   11
typedef SHORTCARD yyTableElmt;
typedef yyTableElmt yyStateRange;
typedef yyTableElmt yyTableRange;
typedef struct S_1 {
    yyStateRange Check, Next;
} yyCombType;
typedef yyCombType *yyCombTypePtr;
typedef struct S_5 {
    CHAR A[1000000 + 1];
} *yytChBufferPtr;
typedef CHAR yyChRange;
typedef SHORTCARD yyFileStackPtrTyp;
typedef yyFileStackPtrTyp yyFileStackSubscript;
static struct S_6 {
    LONGCARD A[yyDStateCount + 1];
} yyBasePtr;
static struct S_7 {
    yyStateRange A[yyDStateCount + 1];
} yyDefault;
static struct S_8 {
    yyCombType A[yyTableSize + 1];
} yyComb;
static struct S_9 {
    yyStateRange A[yyDStateCount + 1];
} yyEobTrans;
static struct S_10 {
    CHAR A[yyLastCh + 1];
} yyToLower, yyToUpper;
static struct S_11 {
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
static struct S_12 {
    struct S_13 {
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
struct S_18 {
    yyTableRange A[yyDStateCount + 1];
};
static CARDINAL yyGetTable ARGS((System_tFile TableFile, ADDRESS Address));
static void yyErrorMessage ARGS((SHORTCARD ErrorCode));
static void yyExit ARGS(());


static void Skip
# ifdef __STDC__
()
# else
()
# endif
{
  do {
    Strings_ReadL(InfoFile, &TheWord);
    l = Strings_Length(&TheWord);
  } while (!((l == 2 || l == 3) && Strings_Char(&TheWord, 1) == '%' && Strings_Char(&TheWord, 2) == '%'));
}

static void DoText
# ifdef __STDC__
()
# else
()
# endif
{
  if (!IsCollecting) {
    yyEcho();
  } else if (Level > 0) {
    Scanner_GetWord(&TheWord);
    Strings_Concatenate(&InsText, &TheWord);
  }
}

static void DoIdent
# ifdef __STDC__
()
# else
()
# endif
{
  Idents_tIdent i;

  Scanner_GetWord(&TheWord);
  i = Idents_MakeIdent(&TheWord);
  if (i <= LastIdent) {
    if (Returning) {
      Strings_IntToString((LONGINT)TokenCode.A[i], &TheWord);
    } else {
      StringMem_GetString(TokenSelector.A[i], &TheWord);
    }
    if (IsCollecting) {
      Strings_Concatenate(&InsText, &TheWord);
    } else {
      Strings_WriteS((System_tFile)IO_StdOutput, &TheWord);
    }
  } else {
    if (IsCollecting) {
      Strings_Concatenate(&InsText, &TheWord);
    } else {
      yyEcho();
    }
  }
}

static void CopyText
# ifdef __STDC__
()
# else
()
# endif
{
  for (;;) {
    Strings_ReadL(InfoFile, &TheWord);
    l = Strings_Length(&TheWord);
    if ((l == 2 || l == 3) && Strings_Char(&TheWord, 1) == '%' && Strings_Char(&TheWord, 2) == '%') {
      goto EXIT_1;
    }
    Strings_WriteL((System_tFile)IO_StdOutput, &TheWord);
  } EXIT_1:;
}

static void GenPosition
# ifdef __STDC__
()
# else
()
# endif
{
  switch (Language) {
  case Modula:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"FROM Positions IMPORT tPosition;", 32L);
    break;
  case C:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"# include \"Positions.h\"", 23L);
    break;
  default :
    break;
  }
  IO_WriteNl((System_tFile)IO_StdOutput);
}

static void GenScanAttr
# ifdef __STDC__
()
# else
()
# endif
{
  InfoFile = IO_ReadOpen(Scanner_InfoFileName.A, 256L);
  Strings_ReadL(InfoFile, &TheWord);
  CopyText();
  IO_ReadClose(InfoFile);
}

static void GenErrorAttr
# ifdef __STDC__
()
# else
()
# endif
{
  InfoFile = IO_ReadOpen(Scanner_InfoFileName.A, 256L);
  Skip();
  CopyText();
  IO_ReadClose(InfoFile);
}

static void ReadIdents
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER t, i;
  CHAR c;
  Idents_tIdent Ident;
  struct S_15 Selector;
  Strings_tString String;

  InfoFile = IO_ReadOpen(Scanner_InfoFileName.A, 256L);
  if (InfoFile < 0) {
    IO_WriteS((System_tFile)IO_StdError, MissingInfo, 37L);
    IO_WriteNl((System_tFile)IO_StdError);
    IO_CloseIO();
    exit(1);
  }
  Strings_ReadL(InfoFile, &TheWord);
  switch (Strings_Char(&TheWord, 1)) {
  case 'm':;
    Language = Modula;
    break;
  case 'c':;
    Language = C;
    break;
  default :
    break;
  }
  Skip();
  Skip();
  while (!IO_EndOfFile(InfoFile)) {
    t = IO_ReadI(InfoFile);
    c = IO_ReadC(InfoFile);
    c = IO_ReadC(InfoFile);
    c = IO_ReadC(InfoFile);
    i = 0;
    do {
      Selector.A[i] = IO_ReadC(InfoFile);
      INC(i);
    } while (!(Selector.A[i - 1] == ' '));
    Selector.A[i - 1] = '\0';
    Strings_ArrayToString(Selector.A, 256L, &String);
    Strings_ReadL(InfoFile, &TheWord);
    Ident = Idents_MakeIdent(&TheWord);
    TokenCode.A[Ident] = t;
    TokenSelector.A[Ident] = StringMem_PutString(&String);
  }
  IO_ReadClose(InfoFile);
  LastIdent = Idents_MaxIdent();
}

static void WriteIdent
# ifdef __STDC__
(Strings_tString *TheWord)
# else
(TheWord)
Strings_tString *TheWord;
# endif
{
  struct S_17 s;
  CARDINAL j;

  Strings_StringToArray(TheWord, s.A, 256L);
  s.A[Strings_Length(TheWord)] = '\'';
  if (!BothFlag && (Strings_IsEqual(TheWord, &Not1) || Strings_IsEqual(TheWord, &Not2) || Strings_IsEqual(TheWord, &Not3) || Strings_IsEqual(TheWord, &Any1) || Strings_IsEqual(TheWord, &Any2) || Strings_IsEqual(TheWord, &Any3))) {
    IO_WriteC((System_tFile)IO_StdOutput, '\\');
  }
  if (s.A[0] == '\'' || s.A[0] == '"') {
    j = 1;
  } else {
    j = 0;
  }
  do {
    if (BothFlag) {
      switch (s.A[j]) {
      case 'a':;
      case 'b':;
      case 'c':;
      case 'd':;
      case 'e':;
      case 'f':;
      case 'g':;
      case 'h':;
      case 'i':;
      case 'j':;
      case 'k':;
      case 'l':;
      case 'm':;
      case 'n':;
      case 'o':;
      case 'p':;
      case 'q':;
      case 'r':;
      case 's':;
      case 't':;
      case 'u':;
      case 'v':;
      case 'w':;
      case 'x':;
      case 'y':;
      case 'z':;
        IO_WriteC((System_tFile)IO_StdOutput, '{');
        IO_WriteC((System_tFile)IO_StdOutput, s.A[j]);
        IO_WriteC((System_tFile)IO_StdOutput, CAP(s.A[j]));
        IO_WriteC((System_tFile)IO_StdOutput, '}');
        break;
      case 'A':;
      case 'B':;
      case 'C':;
      case 'D':;
      case 'E':;
      case 'F':;
      case 'G':;
      case 'H':;
      case 'I':;
      case 'J':;
      case 'K':;
      case 'L':;
      case 'M':;
      case 'N':;
      case 'O':;
      case 'P':;
      case 'Q':;
      case 'R':;
      case 'S':;
      case 'T':;
      case 'U':;
      case 'V':;
      case 'W':;
      case 'X':;
      case 'Y':;
      case 'Z':;
        IO_WriteC((System_tFile)IO_StdOutput, '{');
        IO_WriteC((System_tFile)IO_StdOutput, CHR(ORD(s.A[j]) - ORD('A') + ORD('a')));
        IO_WriteC((System_tFile)IO_StdOutput, s.A[j]);
        IO_WriteC((System_tFile)IO_StdOutput, '}');
        break;
      case '0':;
      case '1':;
      case '2':;
      case '3':;
      case '4':;
      case '5':;
      case '6':;
      case '7':;
      case '8':;
      case '9':;
      case '_':;
        IO_WriteC((System_tFile)IO_StdOutput, s.A[j]);
        break;
      default :
        IO_WriteC((System_tFile)IO_StdOutput, '\\');
        IO_WriteC((System_tFile)IO_StdOutput, s.A[j]);
        break;
      }
    } else {
      switch (s.A[j]) {
      case '0':;
      case '1':;
      case '2':;
      case '3':;
      case '4':;
      case '5':;
      case '6':;
      case '7':;
      case '8':;
      case '9':;
      case 'A':;
      case 'B':;
      case 'C':;
      case 'D':;
      case 'E':;
      case 'F':;
      case 'G':;
      case 'H':;
      case 'I':;
      case 'J':;
      case 'K':;
      case 'L':;
      case 'M':;
      case 'N':;
      case 'O':;
      case 'P':;
      case 'Q':;
      case 'R':;
      case 'S':;
      case 'T':;
      case 'U':;
      case 'V':;
      case 'W':;
      case 'X':;
      case 'Y':;
      case 'Z':;
      case 'a':;
      case 'b':;
      case 'c':;
      case 'd':;
      case 'e':;
      case 'f':;
      case 'g':;
      case 'h':;
      case 'i':;
      case 'j':;
      case 'k':;
      case 'l':;
      case 'm':;
      case 'n':;
      case 'o':;
      case 'p':;
      case 'q':;
      case 'r':;
      case 's':;
      case 't':;
      case 'u':;
      case 'v':;
      case 'w':;
      case 'x':;
      case 'y':;
      case 'z':;
      case '_':;
        IO_WriteC((System_tFile)IO_StdOutput, s.A[j]);
        break;
      default :
        IO_WriteC((System_tFile)IO_StdOutput, '\\');
        IO_WriteC((System_tFile)IO_StdOutput, s.A[j]);
        break;
      }
    }
    INC(j);
  } while (!(s.A[j] == '"' || s.A[j] == '\''));
}

static void InsertRules
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL Code;
  CHAR c, Ch;
  struct S_16 Selector;
  CARDINAL i;

  InfoFile = IO_ReadOpen(Scanner_InfoFileName.A, 256L);
  Skip();
  Skip();
  while (!IO_EndOfFile(InfoFile)) {
    Code = IO_ReadI(InfoFile);
    c = IO_ReadC(InfoFile);
    Ch = IO_ReadC(InfoFile);
    c = IO_ReadC(InfoFile);
    i = 0;
    do {
      Selector.A[i] = IO_ReadC(InfoFile);
      INC(i);
    } while (!(Selector.A[i - 1] == ' '));
    Selector.A[i - 1] = '\0';
    Strings_ReadL(InfoFile, &TheWord);
    if (Ch != 'S') {
      Strings_WriteS((System_tFile)IO_StdOutput, &StartString);
      WriteIdent(&TheWord);
      IO_WriteC((System_tFile)IO_StdOutput, '\t');
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)": { ", 4L);
      Strings_WriteS((System_tFile)IO_StdOutput, &InsText);
      switch (Language) {
      case Modula:;
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"RETURN ", 7L);
        break;
      case C:;
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"return ", 7L);
        break;
      }
      IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)Code, 0L);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"; }", 3L);
      IO_WriteNl((System_tFile)IO_StdOutput);
    }
  }
  IO_ReadClose(InfoFile);
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

  for (;;) {
    yyState = yyStartState;
    Scanner_TokenLength = 0;
    for (;;) {
      for (;;) {
        yyTablePtr = (yyCombTypePtr)(yyBasePtr.A[yyState] + VAL(LONGCARD, ORD(yyChBufferPtr->A[yyChBufferIndex])) * VAL(LONGCARD, sizeof(yyCombType)));
        if (yyTablePtr->Check != yyState) {
          yyState = yyDefault.A[yyState];
          if (yyState == yyDNoState) {
            goto EXIT_4;
          }
        } else {
          yyState = yyTablePtr->Next;
          INC(Scanner_TokenLength);
          yyStateStack->A[Scanner_TokenLength] = yyState;
          INC(yyChBufferIndex);
        }
      } EXIT_4:;
      for (;;) {
        switch (yyStateStack->A[Scanner_TokenLength]) {
        case 154:;
          yyStart(Action);
          yyEcho();
          Level = 1;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 29:;
          yyStart(Rules);
          yyEcho();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 19:;
          DoText();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 17:;
          yyStart(Start);
          BothFlag = FALSE;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 18:;
          yyStart(Start);
          BothFlag = TRUE;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 15:;
        case 39:;
          yyStart(Action);
          yyEcho();
          Level = 0;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 153:;
          yyStart(Set);
          yyEcho();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 152:;
          yyPrevious();
          yyEcho();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 151:;
          yyPrevious();
          InsertRules();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 24:;
          yyPrevious();
          Scanner_GetWord(&StartString);
          InsertRules();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 25:;
          while (yyStateStack->A[Scanner_TokenLength] != 24) {
            DEC(yyChBufferIndex);
            DEC(Scanner_TokenLength);
          }
          Scanner_GetWord(&StartString);
          yyStartState = Action;
          Level = 0;
          IsCollecting = TRUE;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 26:;
          DEC1(yyChBufferIndex, 1);
          DEC1(Scanner_TokenLength, 1);
          yyStartState = Action;
          Level = 0;
          IsCollecting = TRUE;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 22:;
          GenPosition();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 21:;
          GenScanAttr();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 23:;
          GenErrorAttr();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 150:;
          DoText();
          INC(Level);
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 149:;
          DEC(Level);
          if (Level > 0) {
            DoText();
          } else {
            yyPrevious();
            if (IsCollecting) {
              InsertRules();
              IsCollecting = FALSE;
            } else {
              yyEcho();
            }
          }
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 148:;
          yyStartState = Return;
          DoText();
          Returning = FALSE;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 20:;
          yyStartState = Return;
          DoText();
          Returning = TRUE;
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 27:;
          yyStartState = Action;
          DoIdent();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 28:;
          yyStartState = Action;
          DoIdent();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 13:;
        case 30:;
        case 31:;
        case 32:;
        case 33:;
        case 34:;
        case 35:;
        case 36:;
        case 37:;
        case 48:;
        case 49:;
        case 65:;
        case 116:;
        case 117:;
        case 130:;
        case 135:;
        case 136:;
        case 137:;
        case 138:;
        case 139:;
          DoText();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 14:;
        case 38:;
          DoText();
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 134:;
          DoText();
          yyRestartFlag = FALSE;
          goto EXIT_5;
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
        case 16:;
        case 40:;
        case 41:;
        case 42:;
        case 43:;
        case 44:;
        case 45:;
        case 46:;
        case 47:;
        case 50:;
        case 51:;
        case 52:;
        case 53:;
        case 54:;
        case 55:;
        case 56:;
        case 57:;
        case 58:;
        case 59:;
        case 60:;
        case 61:;
        case 62:;
        case 63:;
        case 64:;
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
        case 76:;
        case 77:;
        case 78:;
        case 79:;
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
        case 92:;
        case 93:;
        case 94:;
        case 95:;
        case 96:;
        case 97:;
        case 98:;
        case 99:;
        case 100:;
        case 101:;
        case 102:;
        case 103:;
        case 104:;
        case 105:;
        case 106:;
        case 107:;
        case 108:;
        case 109:;
        case 110:;
        case 111:;
        case 112:;
        case 113:;
        case 114:;
        case 115:;
        case 118:;
        case 119:;
        case 120:;
        case 121:;
        case 122:;
        case 123:;
        case 124:;
        case 125:;
        case 126:;
        case 127:;
        case 128:;
        case 129:;
        case 131:;
        case 140:;
        case 141:;
        case 142:;
        case 143:;
        case 144:;
        case 145:;
        case 146:;
        case 147:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 133:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart);
          INC(yyChBufferIndex);
          Scanner_TokenLength = 1;
          IO_WriteC((System_tFile)IO_StdOutput, yyChBufferPtr->A[yyChBufferIndex - 1]);
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case yyDNoState:;
          yyGetTables();
          yyStateStack->A[0] = yyDefaultState;
          if (yyFileStackPtr == 0) {
            yyInitialize();
            yySourceFile = System_StdInput;
          }
          yyRestartFlag = FALSE;
          goto EXIT_5;
          break;
        case 132:;
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
              goto EXIT_5;
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
              goto EXIT_5;
            }
            if (Scanner_TokenLength == 0) {
              Scanner_Attribute.Position.Line = yyLineCount;
              Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart);
              Scanner_CloseFile();
              if (yyFileStackPtr == 0) {
              }
              if (yyFileStackPtr == 0) {
                return Scanner_EofToken;
              }
              yyRestartFlag = FALSE;
              goto EXIT_5;
            }
          }
          break;
        default :
          yyErrorMessage(0);
          break;
        }
      } EXIT_5:;
      if (yyRestartFlag) {
      } else {
        goto EXIT_3;
      }
    } EXIT_3:;
  } EXIT_2:;
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
    register struct S_13 *W_1 = &yyFileStack.A[yyFileStackPtr - 1];

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
    register struct S_13 *W_2 = &yyFileStack.A[yyFileStackPtr - 1];

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
  (void)strncpy((char *)Scanner_InfoFileName.A, "Scanner.rpp", sizeof(Scanner_InfoFileName.A));
  Language = Modula;
  if (GetArgCount() > 1) {
    GetArgument(1L, Scanner_ScanTabName.A, 128L);
  }
  if (GetArgCount() > 2) {
    GetArgument(2L, Scanner_InfoFileName.A, 256L);
  }
  IsCollecting = FALSE;
  Idents_InitIdents();
  ReadIdents();
  Strings_AssignEmpty(&InsText);
  Strings_AssignEmpty(&StartString);
  Strings_ArrayToString((STRING)"NOT", 3L, &Not1);
  Strings_ArrayToString((STRING)"'NOT'", 5L, &Not2);
  Strings_ArrayToString((STRING)"\"NOT\"", 5L, &Not3);
  Strings_ArrayToString((STRING)"ANY", 3L, &Any1);
  Strings_ArrayToString((STRING)"'ANY'", 5L, &Any2);
  Strings_ArrayToString((STRING)"\"ANY\"", 5L, &Any3);
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
  struct S_18 Base;

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
    Strings__init();
    StringMem__init();
    Idents__init();
    IO__init();

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
