#include "SYSTEM_.h"

#ifndef DEFINITION_Actions
#include "Actions.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Oper
#include "Oper.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Tokens
#include "Tokens.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_Rules
#include "Rules.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_MakeBNF
#include "MakeBNF.h"
#endif


#define InitStackSize   10
#define Infinite   65535
typedef struct S_1 {
    TokenTab_NonTerminal Left;
    Rules_Expression Right;
} tStackElmt;
typedef LONGCARD tStackIndex;
static struct S_2 {
    tStackElmt A[Infinite + 1];
} *RuleStack;
static tStackIndex RuleStackPtr;
static LONGINT RuleStackSize;
static SHORTCARD NontermNumber;
static Strings_tString NontermString;
static SHORTCARD SymbolLength;
static TokenTab_PosType DmPo;
static Idents_tIdent Sym01, Sym02, Sym03, Sym04, Sym05, Sym06, Sym07, Sym08, Sym09, Sym10, Sym11, Sym12;
static void WriteHeader ARGS((IO_tFile out));
static void WritePart ARGS((IO_tFile out, Actions_tActionMode part));
static void WriteOper ARGS((IO_tFile out));
static void WriteTokens ARGS((IO_tFile out));
static void WriteRules ARGS((IO_tFile out));
static void WriteRule ARGS((IO_tFile out, TokenTab_NonTerminal Left, Rules_Expression Right, BOOLEAN HasPrio, Idents_tIdent PrioSym));
static void WriteExpression ARGS((IO_tFile out, Rules_Expression Right, BOOLEAN Last));
static void CreateStack ARGS(());
static BOOLEAN Empty ARGS(());
static void Push ARGS((TokenTab_NonTerminal Left, Rules_Expression Right));
static void Pop ARGS((TokenTab_NonTerminal *Left, Rules_Expression *Right));
static void MakeNonterm ARGS((TokenTab_NonTerminal *Nonterm, Idents_tIdent *Symbol));
static void WriteTokenFix ARGS((IO_tFile out, TokenTab_Vocabulary Token));
static void WriteToken ARGS((IO_tFile out, TokenTab_Vocabulary Token));
static void WriteTab ARGS((IO_tFile out));
static void WriteSymbolFix ARGS((IO_tFile out, Idents_tIdent Symbol));
static void WriteSymbol ARGS((IO_tFile out, Idents_tIdent Symbol));
static void WriteComment ARGS((IO_tFile out, Lists_tList Comment, TokenTab_PosType pos1, TokenTab_PosType pos2));
static void WriteStringList ARGS((IO_tFile out, Lists_tList slist, INTEGER C_1_line));
static void Space ARGS((IO_tFile out));
static void FindSymbolLength ARGS(());
static void ReserveSymbols ARGS(());
static BOOLEAN IsReserved ARGS((Idents_tIdent Symbol));


void MakeBNF_MakeBnf
# ifdef __STDC__
(IO_tFile out)
# else
(out)
IO_tFile out;
# endif
{
  ReserveSymbols();
  WriteHeader(out);
  if (Actions_ScannerName != Idents_NoIdent) {
    IO_WriteS(out, (STRING)"SCANNER ", 8L);
    Idents_WriteIdent(out, Actions_ScannerName);
    IO_WriteNl(out);
  }
  if (Actions_ParserName != Idents_NoIdent) {
    IO_WriteS(out, (STRING)"PARSER ", 7L);
    Idents_WriteIdent(out, Actions_ParserName);
    IO_WriteNl(out);
  }
  WritePart(out, Actions_Export);
  WritePart(out, Actions_Global);
  WritePart(out, Actions_Local);
  WritePart(out, Actions_Begin);
  WritePart(out, Actions_Close);
  FindSymbolLength();
  WriteTokens(out);
  WriteOper(out);
  WriteRules(out);
}

static void WriteHeader
# ifdef __STDC__
(IO_tFile out)
# else
(out)
IO_tFile out;
# endif
{
  Lists_tList Comment;
  TokenTab_PosType Position;

  Tokens_GetGlobalHeader(&Comment, &Position);
  if (!Lists_IsEmpty(Comment)) {
    WriteStringList(out, Comment, 0L);
    IO_WriteNl(out);
    IO_WriteNl(out);
  }
}

static void WritePart
# ifdef __STDC__
(IO_tFile out, Actions_tActionMode part)
# else
(out, part)
IO_tFile out;
Actions_tActionMode part;
# endif
{
  Lists_tList Comment;
  Lists_tList Action;
  TokenTab_PosType pos1, pos2;

  Actions_GetComment(part, &pos1, &Comment, &pos2);
  if (pos1.Line == 0 && pos1.Column == 0) {
    return;
  }
  switch (part) {
  case Actions_Export:;
    IO_WriteS(out, (STRING)"EXPORT", 6L);
    break;
  case Actions_Global:;
    IO_WriteS(out, (STRING)"GLOBAL", 6L);
    break;
  case Actions_Local:;
    IO_WriteS(out, (STRING)"LOCAL", 5L);
    break;
  case Actions_Begin:;
    IO_WriteS(out, (STRING)"BEGIN", 5L);
    break;
  case Actions_Close:;
    IO_WriteS(out, (STRING)"CLOSE", 5L);
    break;
  }
  WriteComment(out, Comment, pos1, pos2);
  IO_WriteNl(out);
  if (ArgCheck_NoActionFlag) {
    return;
  }
  Actions_GetAction(part, &Action, &pos1, &Comment, &pos2);
  if (!Lists_IsEmpty(Action)) {
    WriteStringList(out, Action, (LONGINT)pos1.Line);
    WriteComment(out, Comment, pos1, pos2);
    IO_WriteNl(out);
  }
  IO_WriteNl(out);
}

static void WriteOper
# ifdef __STDC__
(IO_tFile out)
# else
(out)
IO_tFile out;
# endif
{
  TokenTab_PosType pos1, pos2, pos3, pos4;
  Lists_tList Comment;
  Oper_OperKind Kind;
  TokenTab_Vocabulary Token;

  if (Oper_GetOperHeader(&pos1, &Comment, &pos2)) {
    IO_WriteS(out, (STRING)"OPER", 4L);
    WriteComment(out, Comment, pos1, pos2);
    IO_WriteNl(out);
    Oper_InitPrioReading();
    while (Oper_GetPriority(&Kind, &pos1, &Comment, &pos2)) {
      if (Kind == Oper_Right) {
        IO_WriteS(out, (STRING)"  RIGHT", 7L);
      } else if (Kind == Oper_Left) {
        IO_WriteS(out, (STRING)"  LEFT", 6L);
      } else {
        IO_WriteS(out, (STRING)"  NONE", 6L);
      }
      pos4 = pos1;
      while (Oper_GetOperator(&Token, &pos3)) {
        if (pos4.Line != pos3.Line) {
          IO_WriteNl(out);
          IO_WriteS(out, (STRING)"    ", 4L);
        } else {
          Space(out);
        }
        WriteToken(out, Token);
        pos4 = pos3;
      }
      WriteComment(out, Comment, pos2, pos4);
      IO_WriteNl(out);
    }
    IO_WriteNl(out);
  }
}

static void WriteTokens
# ifdef __STDC__
(IO_tFile out)
# else
(out)
IO_tFile out;
# endif
{
  Idents_tIdent Symbol;
  Lists_tList Comment;
  TokenTab_PosType pos1, pos2, pos3, pos4;
  TokenTab_TokenError Error;
  BOOLEAN HasCoding;
  TokenTab_Vocabulary Code;

  IO_WriteS(out, (STRING)"TOKEN", 5L);
  Tokens_GetTokensHeader(&pos1, &Comment, &pos2);
  WriteComment(out, Comment, pos1, pos2);
  IO_WriteNl(out);
  while (Tokens_GetDeclaration(&Symbol, &pos1, &HasCoding, &pos2, &pos3, &Comment, &pos4)) {
    if (HasCoding) {
      Code = TokenTab_SymbolToToken(Symbol, &Error);
      WriteSymbolFix(out, Symbol);
      IO_WriteS(out, (STRING)"= ", 2L);
      IO_WriteI(out, (LONGINT)Code, 3L);
    } else {
      WriteSymbol(out, Symbol);
    }
    WriteComment(out, Comment, pos1, pos4);
    IO_WriteNl(out);
  }
  IO_WriteNl(out);
}

static void WriteRules
# ifdef __STDC__
(IO_tFile out)
# else
(out)
IO_tFile out;
# endif
{
  TokenTab_PosType pos1, pos2, pos3, pos4, pos5, pos6;
  Lists_tList Comment;
  BOOLEAN HasPrio;
  TokenTab_Terminal PrioTerm;
  Idents_tIdent PrioSym;
  TokenTab_NonTerminal Left;
  Rules_Expression Right;
  TokenTab_TokenError Error;

  Rules_GetRulesHeader(&pos1, &Comment, &pos2);
  IO_WriteS(out, (STRING)"RULE", 4L);
  WriteComment(out, Comment, pos1, pos2);
  IO_WriteNl(out);
  Rules_InitRulesReading();
  CreateStack();
  while (Rules_GetRule(&Left, &pos1, &pos2, &Right, &Comment, &pos3, &pos4, &HasPrio, &pos5, &PrioTerm, &pos6)) {
    NontermNumber = 0;
    Idents_GetString(TokenTab_TokenToSymbol(Left, &Error), &NontermString);
    if (HasPrio) {
      PrioSym = TokenTab_TokenToSymbol(PrioTerm, &Error);
    } else {
      PrioSym = 0;
    }
    IO_WriteNl(out);
    WriteRule(out, Left, Right, HasPrio, PrioSym);
    while (!Empty()) {
      Pop(&Left, &Right);
      IO_WriteNl(out);
      WriteRule(out, Left, Right, FALSE, 0);
    }
    WriteComment(out, Comment, pos1, pos6);
    IO_WriteNl(out);
  }
}

static void WriteRule
# ifdef __STDC__
(IO_tFile out, TokenTab_NonTerminal Left, Rules_Expression Right, BOOLEAN HasPrio, Idents_tIdent PrioSym)
# else
(out, Left, Right, HasPrio, PrioSym)
IO_tFile out;
TokenTab_NonTerminal Left;
Rules_Expression Right;
BOOLEAN HasPrio;
Idents_tIdent PrioSym;
# endif
{
  Rules_Expression LSon, RSon;
  BOOLEAN LHasPrio;
  Idents_tIdent LPrioSym;
  TokenTab_PosType pos1, pos2, pos3;

  while (Rules_GetNodeOperation(Right) == Rules_Alternative) {
    Rules_GetPrioAlternativeNode(Right, &pos1, &LSon, &RSon, &LHasPrio, &pos2, &LPrioSym, &pos3);
    WriteRule(out, Left, LSon, LHasPrio, LPrioSym);
    IO_WriteNl(out);
    Right = RSon;
  }
  WriteTokenFix(out, Left);
  IO_WriteS(out, (STRING)": ", 2L);
  WriteExpression(out, Right, TRUE);
  if (HasPrio) {
    IO_WriteS(out, (STRING)"  PREC ", 7L);
    WriteSymbol(out, PrioSym);
  }
  IO_WriteS(out, (STRING)".", 1L);
}

static void WriteExpression
# ifdef __STDC__
(IO_tFile out, Rules_Expression Right, BOOLEAN Last)
# else
(out, Right, Last)
IO_tFile out;
Rules_Expression Right;
BOOLEAN Last;
# endif
{
  TokenTab_PosType pos1, pos2;
  TokenTab_Vocabulary Token;
  Lists_tList Act;
  TokenTab_NonTerminal N1, N2;
  Idents_tIdent S1, S2;
  Rules_Expression Son, LSon, RSon;
  Lists_tList list;

  switch (Rules_GetNodeOperation(Right)) {
  case Rules_Plus:;
    Rules_GetUnaryNode(Right, &pos1, &Son);
    MakeNonterm(&N1, &S1);
    MakeNonterm(&N2, &S2);
    WriteSymbol(out, S1);
    Space(out);
    Push(N2, Son);
    Push(N1, Rules_MakeBinaryNode(Rules_Sequence, DmPo, Rules_MakeLeafNode(S1, DmPo), Rules_MakeLeafNode(S2, DmPo)));
    Push(N1, Rules_MakeLeafNode(S2, DmPo));
    break;
  case Rules_Star:;
    Rules_GetUnaryNode(Right, &pos1, &Son);
    MakeNonterm(&N1, &S1);
    WriteSymbol(out, S1);
    Space(out);
    Push(N1, Rules_MakeBinaryNode(Rules_Sequence, DmPo, Rules_MakeLeafNode(S1, DmPo), Son));
    Push(N1, Rules_NoExpression);
    break;
  case Rules_Optional:;
    Rules_GetBracketNode(Right, &pos1, &pos2, &Son);
    MakeNonterm(&N1, &S1);
    WriteSymbol(out, S1);
    Space(out);
    Push(N1, Son);
    Push(N1, Rules_NoExpression);
    break;
  case Rules_Bracket:;
    Rules_GetBracketNode(Right, &pos1, &pos2, &Son);
    MakeNonterm(&N1, &S1);
    WriteSymbol(out, S1);
    Space(out);
    Push(N1, Son);
    break;
  case Rules_Sequence:;
    Rules_GetBinaryNode(Right, &pos1, &LSon, &RSon);
    WriteExpression(out, LSon, FALSE);
    WriteExpression(out, RSon, Last);
    break;
  case Rules_Separator:;
    Rules_GetBinaryNode(Right, &pos1, &LSon, &RSon);
    MakeNonterm(&N1, &S1);
    MakeNonterm(&N2, &S2);
    WriteSymbol(out, S1);
    Space(out);
    WriteSymbol(out, S2);
    Space(out);
    Push(N2, Rules_MakeBinaryNode(Rules_Sequence, DmPo, Rules_MakeLeafNode(S2, DmPo), Rules_MakeBinaryNode(Rules_Sequence, DmPo, RSon, Rules_MakeLeafNode(S1, DmPo))));
    Push(N1, LSon);
    Push(N2, Rules_NoExpression);
    break;
  case Rules_Alternative:;
  case Rules_ArtAlternative:;
    break;
  case Rules_Action:;
    if (Last) {
      Rules_GetActionNode(Right, &Act, &pos1);
      if (!Lists_IsEmpty(Act) && !ArgCheck_NoActionFlag) {
        list = Act;
        Lists_Tail(&list);
        if (!Lists_IsEmpty(list)) {
          IO_WriteNl(out);
          WriteStringList(out, Act, (LONGINT)pos1.Line);
          IO_WriteNl(out);
          WriteTab(out);
        } else {
          WriteStringList(out, Act, (LONGINT)pos1.Line);
          Space(out);
        }
      }
    } else {
      MakeNonterm(&N1, &S1);
      WriteSymbol(out, S1);
      Space(out);
      Push(N1, Right);
    }
    break;
  case Rules_TermLeaf:;
  case Rules_NonTermLeaf:;
    Rules_GetLeafNode(Right, &Token, &pos1);
    WriteToken(out, Token);
    Space(out);
    break;
  case Rules_NoOperation:;
    break;
  }
}

static void CreateStack
# ifdef __STDC__
()
# else
()
# endif
{
  RuleStackSize = InitStackSize;
  DynArray_MakeArray((ADDRESS *)&RuleStack, &RuleStackSize, (LONGINT)sizeof(tStackElmt));
  RuleStackPtr = 0;
}

static BOOLEAN Empty
# ifdef __STDC__
()
# else
()
# endif
{
  return RuleStackPtr == 0;
}

static void Push
# ifdef __STDC__
(TokenTab_NonTerminal Left, Rules_Expression Right)
# else
(Left, Right)
TokenTab_NonTerminal Left;
Rules_Expression Right;
# endif
{
  tStackIndex size;

  INC(RuleStackPtr);
  size = RuleStackSize;
  if (RuleStackPtr >= size) {
    DynArray_ExtendArray((ADDRESS *)&RuleStack, &RuleStackSize, (LONGINT)sizeof(tStackElmt));
  }
  RuleStack->A[RuleStackPtr].Left = Left;
  RuleStack->A[RuleStackPtr].Right = Right;
}

static void Pop
# ifdef __STDC__
(TokenTab_NonTerminal *Left, Rules_Expression *Right)
# else
(Left, Right)
TokenTab_NonTerminal *Left;
Rules_Expression *Right;
# endif
{
  *Left = RuleStack->A[RuleStackPtr].Left;
  *Right = RuleStack->A[RuleStackPtr].Right;
  DEC(RuleStackPtr);
}

static void MakeNonterm
# ifdef __STDC__
(TokenTab_NonTerminal *Nonterm, Idents_tIdent *Symbol)
# else
(Nonterm, Symbol)
TokenTab_NonTerminal *Nonterm;
Idents_tIdent *Symbol;
# endif
{
  Strings_tString String;
  CARDINAL max, i, j;
  TokenTab_Vocabulary voc;
  CHAR c;

  max = TokenTab_MAXNonTerm;
  do {
    INC(NontermNumber);
    Strings_Assign(&String, &NontermString);
    Strings_Append(&String, '_');
    j = 1;
    while (j <= NontermNumber) {
      j = j * 10;
    }
    i = NontermNumber;
    while (j > 1) {
      j = j / 10;
      c = CHR(ORD('0') + i / j);
      i = i % j;
      Strings_Append(&String, c);
    }
    *Symbol = Idents_MakeIdent(&String);
    voc = TokenTab_MakeVoc(*Symbol, DmPo);
  } while (!(max < TokenTab_MAXNonTerm));
  *Nonterm = voc;
}

static void WriteTokenFix
# ifdef __STDC__
(IO_tFile out, TokenTab_Vocabulary Token)
# else
(out, Token)
IO_tFile out;
TokenTab_Vocabulary Token;
# endif
{
  Idents_tIdent Symbol;
  TokenTab_TokenError Error;

  Symbol = TokenTab_TokenToSymbol(Token, &Error);
  WriteSymbolFix(out, Symbol);
}

static void WriteToken
# ifdef __STDC__
(IO_tFile out, TokenTab_Vocabulary Token)
# else
(out, Token)
IO_tFile out;
TokenTab_Vocabulary Token;
# endif
{
  Idents_tIdent Symbol;
  TokenTab_TokenError Error;

  Symbol = TokenTab_TokenToSymbol(Token, &Error);
  WriteSymbol(out, Symbol);
}

static void WriteTab
# ifdef __STDC__
(IO_tFile out)
# else
(out)
IO_tFile out;
# endif
{
  SHORTCARD i;

  {
    SHORTCARD B_1 = 1, B_2 = SymbolLength;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        Space(out);
        if (i >= B_2) break;
      }
  }
}

static void WriteSymbolFix
# ifdef __STDC__
(IO_tFile out, Idents_tIdent Symbol)
# else
(out, Symbol)
IO_tFile out;
Idents_tIdent Symbol;
# endif
{
  Strings_tString String;
  SHORTCARD i, j;

  Idents_GetString(Symbol, &String);
  j = Strings_Length(&String);
  if (IsReserved(Symbol)) {
    IO_WriteS(out, (STRING)"\\", 1L);
    j = j + 1;
  }
  Strings_WriteS(out, &String);
  {
    SHORTCARD B_3 = j, B_4 = SymbolLength;

    if (B_3 <= B_4)
      for (i = B_3;; i += 1) {
        Space(out);
        if (i >= B_4) break;
      }
  }
}

static void WriteSymbol
# ifdef __STDC__
(IO_tFile out, Idents_tIdent Symbol)
# else
(out, Symbol)
IO_tFile out;
Idents_tIdent Symbol;
# endif
{
  Strings_tString String;

  if (IsReserved(Symbol)) {
    IO_WriteS(out, (STRING)"\\", 1L);
  }
  Idents_GetString(Symbol, &String);
  Strings_WriteS(out, &String);
}

static void WriteComment
# ifdef __STDC__
(IO_tFile out, Lists_tList Comment, TokenTab_PosType pos1, TokenTab_PosType pos2)
# else
(out, Comment, pos1, pos2)
IO_tFile out;
Lists_tList Comment;
TokenTab_PosType pos1, pos2;
# endif
{
  if (!Lists_IsEmpty(Comment)) {
    if (pos2.Line != pos1.Line) {
      IO_WriteNl(out);
    } else {
      Space(out);
      Space(out);
    }
    WriteStringList(out, Comment, 0L);
  }
}

static void WriteStringList
# ifdef __STDC__
(IO_tFile out, Lists_tList slist, INTEGER C_1_line)
# else
(out, slist, C_1_line)
IO_tFile out;
Lists_tList slist;
INTEGER C_1_line;
# endif
{
  Strings_tString s;
  CARDINAL pos;
  CHAR c;

  if (!Lists_IsEmpty(slist)) {
    StringMem_GetString((StringMem_tStringRef)Lists_Head(slist), &s);
    Lists_Tail(&slist);
    c = Strings_Char(&s, 1);
    IO_WriteC(out, c);
    if (C_1_line != 0 && c == '{') {
      if (WriteTok_Language == WriteTok_Modula2) {
        IO_WriteS(out, (STRING)"(* line ", 8L);
        IO_WriteI(out, C_1_line, 1L);
        IO_WriteS(out, (STRING)" ", 1L);
        IO_WriteS(out, ArgCheck_SourceFileName.A, 128L);
        IO_WriteS(out, (STRING)" *)", 3L);
        IO_WriteNl(out);
      } else {
        if (ArgCheck_Line) {
          IO_WriteS(out, (STRING)"# line ", 7L);
          IO_WriteI(out, C_1_line, 1L);
          IO_WriteS(out, (STRING)" \"", 2L);
          IO_WriteS(out, ArgCheck_SourceFileName.A, 128L);
          IO_WriteS(out, (STRING)"\"", 1L);
          IO_WriteNl(out);
        } else {
          IO_WriteS(out, (STRING)"/* line ", 8L);
          IO_WriteI(out, C_1_line, 1L);
          IO_WriteS(out, (STRING)" \"", 2L);
          IO_WriteS(out, ArgCheck_SourceFileName.A, 128L);
          IO_WriteS(out, (STRING)"\" */", 4L);
          IO_WriteNl(out);
        }
      }
    }
    {
      LONGCARD B_5 = 2, B_6 = Strings_Length(&s);

      if (B_5 <= B_6)
        for (pos = B_5;; pos += 1) {
          IO_WriteC(out, Strings_Char(&s, (Strings_tStringIndex)pos));
          if (pos >= B_6) break;
        }
    }
    while (!Lists_IsEmpty(slist)) {
      StringMem_WriteString(out, (StringMem_tStringRef)Lists_Head(slist));
      Lists_Tail(&slist);
    }
  }
}

static void Space
# ifdef __STDC__
(IO_tFile out)
# else
(out)
IO_tFile out;
# endif
{
  IO_WriteC(out, ' ');
}

static void FindSymbolLength
# ifdef __STDC__
()
# else
()
# endif
{
  Idents_tIdent Symbol;
  Strings_tString String;
  TokenTab_Vocabulary Token;
  TokenTab_TokenError Error;

  SymbolLength = 0;
  {
    TokenTab_Vocabulary B_7 = 1, B_8 = TokenTab_MAXTerm;

    if (B_7 <= B_8)
      for (Token = B_7;; Token += 1) {
        if (TokenTab_GetTokenType(Token) == TokenTab_Term) {
          Symbol = TokenTab_TokenToSymbol(Token, &Error);
          Idents_GetString(Symbol, &String);
          if (Strings_Length(&String) > SymbolLength) {
            SymbolLength = Strings_Length(&String);
          }
        }
        if (Token >= B_8) break;
      }
  }
  {
    TokenTab_Vocabulary B_9 = TokenTab_MINNonTerm, B_10 = TokenTab_MAXNonTerm;

    if (B_9 <= B_10)
      for (Token = B_9;; Token += 1) {
        if (TokenTab_GetTokenType(Token) == TokenTab_NonTerm) {
          Symbol = TokenTab_TokenToSymbol(Token, &Error);
          Idents_GetString(Symbol, &String);
          if (Strings_Length(&String) > SymbolLength) {
            SymbolLength = Strings_Length(&String);
          }
        }
        if (Token >= B_10) break;
      }
  }
  INC1(SymbolLength, 3);
}

static void ReserveSymbols
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString s;

  Strings_ArrayToString((STRING)"EXPORT", 6L, &s);
  Sym01 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"GLOBAL", 6L, &s);
  Sym02 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"LOCAL", 5L, &s);
  Sym03 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"BEGIN", 5L, &s);
  Sym04 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"CLOSE", 5L, &s);
  Sym05 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"TOKEN", 5L, &s);
  Sym06 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"OPER", 4L, &s);
  Sym07 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"NONE", 4L, &s);
  Sym08 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"LEFT", 4L, &s);
  Sym09 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"RIGHT", 5L, &s);
  Sym10 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"RULE", 4L, &s);
  Sym11 = Idents_MakeIdent(&s);
  Strings_ArrayToString((STRING)"PREC", 4L, &s);
  Sym12 = Idents_MakeIdent(&s);
}

static BOOLEAN IsReserved
# ifdef __STDC__
(Idents_tIdent Symbol)
# else
(Symbol)
Idents_tIdent Symbol;
# endif
{
  return Symbol == Sym01 || Symbol == Sym02 || Symbol == Sym03 || Symbol == Sym04 || Symbol == Sym05 || Symbol == Sym06 || Symbol == Sym07 || Symbol == Sym08 || Symbol == Sym09 || Symbol == Sym10 || Symbol == Sym11 || Symbol == Sym12;
}

void MakeBNF__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Actions__init();
    ArgCheck__init();
    DynArray__init();
    IO__init();
    Oper__init();
    StringMem__init();
    Strings__init();
    Lists__init();
    Idents__init();
    Tokens__init();
    WriteTok__init();
    Rules__init();
    TokenTab__init();
    Strings__init();
    StringMem__init();

    DmPo.Line = 0;
    DmPo.Column = 0;
    NontermNumber = 0;
    WriteTok_Language = WriteTok_Modula2;
  }
}
