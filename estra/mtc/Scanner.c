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

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
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

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

Idents_tIdent Scanner_NoIdent;
Idents_tIdent Scanner_MaxIdent;
StringMem_tStringRef Scanner_NoStringRef;
INTEGER Scanner_MaxValue;
INTEGER Scanner_TokenLength;
Scanner_tScanAttribute Scanner_Attribute;
struct Scanner_2 Scanner_ScanTabName;
PROC Scanner_Exit;

#define eEolString   21
#define eEofCode   22
#define eEofString   23
#define eEofComment   24
#define eIllegalChar   25
#define eDoNotUseYY   26
static Strings_tString word, string;
static CHAR C_1_char;
static INTEGER level, clevel;
static Positions_tPosition CodePos, CommentPos;
#define yyTabSpace   8
#define yyDNoState   0
#define yyFileStackSize   16
#define yyInitBufferSize   (1024 * 8 + 256)
#define yyFirstCh   '\0'
#define yyLastCh   ((CHAR)'\177')
#define yyEolCh   '\n'
#define yyEobCh   ((CHAR)'\177')
#define yyDStateCount   188
#define yyTableSize   1881
#define yyEobState   46
#define yyDefaultState   47
#define STD   1
#define code   3
#define str1   5
#define str2   7
#define comment1   9
#define comment2   11
#define codestr1   13
#define codestr2   15
#define codecom1   17
#define codecom2   19
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
(INTEGER Symbol, Scanner_tScanAttribute *Attribute)
# else
(Symbol, Attribute)
INTEGER Symbol;
Scanner_tScanAttribute *Attribute;
# endif
{
  switch (Symbol) {
  case Scanner_SymIdent:;
  case Scanner_SymString:;
  case Scanner_SymCodeIdent:;
  case Scanner_SymCodeString:;
    Attribute->U_1.V_1.ident = Scanner_NoIdent;
    break;
  case 58:;
  case 59:;
  case 60:;
    Attribute->U_1.V_2.ref = Scanner_NoStringRef;
    break;
  case Scanner_SymNumber:;
    Attribute->U_1.V_3.val = Scanner_NoValue;
    break;
  default :
    break;
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
        case 188:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          yyStart(comment1);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 187:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          level = 1;
          yyStart(comment2);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 186:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymLParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 185:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymRParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 184:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymComma;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 183:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymDot;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 182:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymSlash;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 181:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 180:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymSemiColon;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 179:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymEqual;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 178:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymBar;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 177:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymRArrow;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 175:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymBEGIN;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 170:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymCLOSE;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 166:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymCONDITION;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 159:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymCOSTS;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 154:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymDECLARE;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 147:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymEXPORT;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 141:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymGLOBAL;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 136:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymGRAMMAR;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 129:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymLOCAL;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 124:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymFUNCTION;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 116:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymTRANSFORMATION;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 39:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Errors_ErrorMessage((LONGCARD)eDoNotUseYY, (LONGCARD)Errors_eWarning, Scanner_Attribute.Position);
          Scanner_GetWord(&word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&word);
          return Scanner_SymIdent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 37:;
        case 43:;
        case 44:;
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
        case 117:;
        case 118:;
        case 119:;
        case 120:;
        case 121:;
        case 122:;
        case 123:;
        case 125:;
        case 126:;
        case 127:;
        case 128:;
        case 130:;
        case 131:;
        case 132:;
        case 133:;
        case 134:;
        case 135:;
        case 137:;
        case 138:;
        case 139:;
        case 140:;
        case 142:;
        case 143:;
        case 144:;
        case 145:;
        case 146:;
        case 148:;
        case 149:;
        case 150:;
        case 151:;
        case 152:;
        case 153:;
        case 155:;
        case 156:;
        case 157:;
        case 158:;
        case 160:;
        case 161:;
        case 162:;
        case 163:;
        case 164:;
        case 165:;
        case 167:;
        case 168:;
        case 169:;
        case 171:;
        case 172:;
        case 173:;
        case 174:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&word);
          return Scanner_SymIdent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 38:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&word);
          Scanner_Attribute.U_1.V_3.val = Strings_StringToInt(&word);
          if (Scanner_Attribute.U_1.V_3.val > Scanner_MaxValue) {
            Scanner_MaxValue = Scanner_Attribute.U_1.V_3.val;
          }
          return Scanner_SymNumber;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 102:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          yyStart(str1);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 101:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          yyStart(str2);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 100:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          CodePos = Scanner_Attribute.Position;
          yyStart(code);
          clevel = 1;
          return Scanner_SymLBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 36:;
        case 176:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&word);
          C_1_char = Strings_Char(&word, 1);
          Errors_ErrorMessageI((LONGCARD)eIllegalChar, (LONGCARD)Errors_eError, Scanner_Attribute.Position, (LONGCARD)Errors_eCharacter, ADR(C_1_char));
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 29:;
        case 52:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 99:;
          Scanner_GetWord(&word);
          yyTab();
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 98:;
          Strings_Append(&string, '\'');
          yyEol(0L);
          Errors_ErrorMessage((LONGCARD)eEolString, (LONGCARD)Errors_eError, Scanner_Attribute.Position);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(STD);
          return Scanner_SymString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 97:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(STD);
          return Scanner_SymString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 28:;
        case 53:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 96:;
          Scanner_GetWord(&word);
          yyTab();
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 95:;
          Strings_Append(&string, '"');
          yyEol(0L);
          Errors_ErrorMessage((LONGCARD)eEolString, (LONGCARD)Errors_eError, Scanner_Attribute.Position);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(STD);
          return Scanner_SymString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 94:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(STD);
          return Scanner_SymString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 93:;
          yyStart(STD);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 27:;
        case 54:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 92:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 91:;
          INC(level);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 90:;
          DEC(level);
          if (level == 0) {
            yyStart(STD);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 26:;
        case 55:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 89:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 88:;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 87:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          CommentPos = Scanner_Attribute.Position;
          Scanner_GetWord(&string);
          yyStart(codecom1);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 85:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          CommentPos = Scanner_Attribute.Position;
          Scanner_GetWord(&string);
          level = 1;
          yyStart(codecom2);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 84:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymCodeDot;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 83:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymCodeComma;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 82:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymCodeLParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 81:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          return Scanner_SymCodeRParent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 80:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          INC(clevel);
          return Scanner_SymCodeLBrace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 79:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          DEC(clevel);
          if (clevel == 0) {
            yyStart(STD);
            return Scanner_SymRBrace;
          } else {
            return Scanner_SymCodeRBrace;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 33:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Errors_ErrorMessage((LONGCARD)eDoNotUseYY, (LONGCARD)Errors_eWarning, Scanner_Attribute.Position);
          Scanner_GetWord(&word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&word);
          return Scanner_SymCodeIdent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 31:;
        case 42:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&word);
          return Scanner_SymCodeIdent;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 40:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          yyStart(codestr1);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 35:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&word);
          return Scanner_SymCodeString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 78:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          yyStart(codestr2);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 32:;
        case 51:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
          return Scanner_SymCodeSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 77:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
          yyTab();
          return Scanner_SymCodeSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 76:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
          yyEol(0L);
          return Scanner_SymCodeSpace;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 30:;
        case 41:;
        case 86:;
          Scanner_Attribute.Position.Line = yyLineCount;
          Scanner_Attribute.Position.Column = VAL(SHORTCARD, yyChBufferIndex - yyLineStart - Scanner_TokenLength);
          Scanner_GetWord(&string);
          Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
          return Scanner_SymCodeRest;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 25:;
        case 56:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 75:;
          Scanner_GetWord(&word);
          yyTab();
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 74:;
          Strings_Append(&string, '\'');
          yyEol(0L);
          Errors_ErrorMessage((LONGCARD)eEolString, (LONGCARD)Errors_eError, Scanner_Attribute.Position);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(code);
          return Scanner_SymCodeString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 73:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(code);
          return Scanner_SymCodeString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 24:;
        case 57:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 72:;
          Scanner_GetWord(&word);
          yyTab();
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 71:;
          Strings_Append(&string, '"');
          yyEol(0L);
          Errors_ErrorMessage((LONGCARD)eEolString, (LONGCARD)Errors_eError, Scanner_Attribute.Position);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(code);
          return Scanner_SymCodeString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 70:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          Scanner_Attribute.U_1.V_1.ident = Idents_MakeIdent(&string);
          yyStart(code);
          return Scanner_SymCodeString;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 69:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
          yyStart(code);
          return Scanner_SymCodeComment;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 23:;
        case 58:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 68:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 67:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
          Strings_AssignEmpty(&string);
          yyEol(0L);
          return Scanner_SymCodeRest;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 66:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 65:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          INC(level);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 63:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          DEC(level);
          if (level == 0) {
            yyStart(code);
            Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
            return Scanner_SymCodeComment;
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 21:;
        case 59:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 61:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyTab();
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 60:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          Scanner_Attribute.U_1.V_2.ref = StringMem_PutString(&string);
          Strings_AssignEmpty(&string);
          yyEol(0L);
          return Scanner_SymCodeRest;
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 22:;
        case 62:;
        case 64:;
          Scanner_GetWord(&word);
          Strings_Concatenate(&string, &word);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 50:;
          while (yyChBufferPtr->A[yyChBufferIndex] == ' ') {
            INC(yyChBufferIndex);
          }
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 49:;
          DEC1(yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) % 8);
          yyRestartFlag = FALSE;
          goto EXIT_4;
          break;
        case 48:;
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
        case 34:;
        case 45:;
          DEC(yyChBufferIndex);
          DEC(Scanner_TokenLength);
          break;
        case 47:;
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
        case 46:;
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
                case STD:;
                  break;
                case code:;
                  Errors_ErrorMessage((LONGCARD)eEofCode, (LONGCARD)Errors_eError, CodePos);
                  break;
                case str1:;
                case str2:;
                case codestr1:;
                case codestr2:;
                  Errors_ErrorMessage((LONGCARD)eEofString, (LONGCARD)Errors_eError, Scanner_Attribute.Position);
                  break;
                case codecom1:;
                case codecom2:;
                  Errors_ErrorMessage((LONGCARD)eEofComment, (LONGCARD)Errors_eError, CommentPos);
                  break;
                case comment1:;
                case comment2:;
                  Errors_ErrorMessage((LONGCARD)eEofComment, (LONGCARD)Errors_eError, Scanner_Attribute.Position);
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
  Strings_ArrayToString((STRING)"_no_string_ref_", 15L, &word);
  Scanner_NoStringRef = StringMem_PutString(&word);
  Strings_ArrayToString((STRING)"_no_identifier_", 15L, &word);
  Scanner_NoIdent = Idents_MakeIdent(&word);
  Scanner_MaxValue = 0;
}

void Scanner_CloseScanner
# ifdef __STDC__
()
# else
()
# endif
{
  Scanner_MaxIdent = Idents_MaxIdent();
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
    Positions__init();
    Checks__init();
    System__init();
    General__init();
    Positions__init();
    IO__init();
    DynArray__init();
    Strings__init();
    Source__init();
    Errors__init();
    Positions__init();
    Idents__init();
    Strings__init();
    StringMem__init();
    Idents__init();

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
