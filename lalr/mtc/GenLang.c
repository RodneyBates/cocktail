#include "SYSTEM_.h"

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Compress
#include "Compress.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_GenLang
#include "GenLang.h"
#endif


static void OpenCase ARGS((IO_tFile f, Automaton_tStateIndex label));
static void NextCase ARGS((IO_tFile f, Automaton_tStateIndex label));
static void CloseCase ARGS((IO_tFile f, INTEGER cases));
static void WriteSemanticAction ARGS((IO_tFile f, Lists_tList a, CARDINAL len, TokenTab_PosType pos));
static void WriteProdComment ARGS((IO_tFile f, Automaton_tProduction prod));
static void WriteToken ARGS((IO_tFile f, TokenTab_Vocabulary t));
static void WriteLong ARGS((IO_tFile f, LONGINT Check));


void GenLang_WriteConstants
# ifdef __STDC__
(IO_tFile f)
# else
(f)
IO_tFile f;
# endif
{
  if (WriteTok_Language == WriteTok_Modula2) {
    IO_WriteS(f, (STRING)"   yyFirstTerminal          = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_FirstTerminal, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyLastTerminal           = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_LastTerminal, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyFirstSymbol            = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_FirstSymbol, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyLastSymbol             = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_LastSymbol, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyTableMax               = ", 30L);
    IO_WriteI(f, (LONGINT)Compress_TableSize, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyNTableMax              = ", 30L);
    IO_WriteI(f, (LONGINT)Compress_NTableSize, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyFirstReadState         = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_FirstReadState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyLastReadState          = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_LastReadState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyFirstReadTermState             = ", 38L);
    IO_WriteI(f, (LONGINT)Gen_FirstReadTermState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyLastReadTermState              = ", 38L);
    IO_WriteI(f, (LONGINT)Gen_LastReadTermState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyLastReadNontermState           = ", 38L);
    IO_WriteI(f, (LONGINT)Gen_LastReadNonTermState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyFirstReduceState               = ", 38L);
    IO_WriteI(f, (LONGINT)Gen_FirstReduceState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyLastReduceState                = ", 38L);
    IO_WriteI(f, (LONGINT)Gen_LastReduceState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyStartState             = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_StartState(), 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"   yyStopState              = ", 30L);
    IO_WriteI(f, (LONGINT)Gen_StopState, 0L);
    IO_WriteC(f, ';');
    IO_WriteNl(f);
  } else {
    IO_WriteS(f, (STRING)"# define yyFirstTerminal    ", 28L);
    IO_WriteI(f, (LONGINT)Gen_FirstTerminal, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyLastTerminal             ", 36L);
    IO_WriteI(f, (LONGINT)Gen_LastTerminal, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyTableMax         ", 28L);
    IO_WriteI(f, (LONGINT)Compress_TableSize, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyNTableMax                ", 36L);
    IO_WriteI(f, (LONGINT)Compress_NTableSize, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyFirstReadState   ", 28L);
    IO_WriteI(f, (LONGINT)Gen_FirstReadState, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyLastReadState    ", 28L);
    IO_WriteI(f, (LONGINT)Gen_LastReadState, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyFirstReadTermState       ", 36L);
    IO_WriteI(f, (LONGINT)Gen_FirstReadTermState, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyLastReadTermState        ", 36L);
    IO_WriteI(f, (LONGINT)Gen_LastReadTermState, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyLastReadNontermState     ", 36L);
    IO_WriteI(f, (LONGINT)Gen_LastReadNonTermState, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyFirstReduceState ", 28L);
    IO_WriteI(f, (LONGINT)Gen_FirstReduceState, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyLastReduceState  ", 28L);
    IO_WriteI(f, (LONGINT)Gen_LastReduceState, 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyStartState               ", 36L);
    IO_WriteI(f, (LONGINT)Gen_StartState(), 0L);
    IO_WriteNl(f);
    IO_WriteS(f, (STRING)"# define yyStopState                ", 36L);
    IO_WriteI(f, (LONGINT)Gen_StopState, 0L);
    IO_WriteNl(f);
  }
}

void GenLang_WriteReduceCode
# ifdef __STDC__
(IO_tFile f)
# else
(f)
IO_tFile f;
# endif
{
  Automaton_tStateIndex label;
  INTEGER labels;
  INTEGER cases;
  Automaton_tProdIndex index;
  Automaton_tProduction prod;
  Automaton_tProdIndex maxProdIndex;
  LONGINT u;

  label = Gen_FirstReduceState;
  labels = 0;
  cases = 1;
  index = 0;
  if (Gen_CaseLabels > 0) {
    INC1(label, Gen_CaseLabels);
    OpenCase(f, label);
  } else if (WriteTok_Language == WriteTok_Modula2) {
    IO_WriteS(f, (STRING)"CASE yyState OF", 15L);
    IO_WriteNl(f);
  } else {
    IO_WriteS(f, (STRING)"switch (yyState) {", 18L);
    IO_WriteNl(f);
  }
  maxProdIndex = Automaton_ProdIndex;
  while (index < maxProdIndex) {
    if (Gen_CaseLabels > 0) {
      if (labels >= Gen_CaseLabels) {
        INC1(label, Gen_CaseLabels);
        NextCase(f, label);
        INC(cases);
        labels = 0;
      }
      INC(labels);
    }
    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
    {
      register Automaton_tIndexList *W_1 = &prod->Reduce;

      if (WriteTok_Language == WriteTok_Modula2) {
        IO_WriteS(f, (STRING)"  | ", 4L);
        IO_WriteI(f, (LONGINT)W_1->Array->A[1 - 1], 0L);
      } else {
        IO_WriteS(f, (STRING)"case ", 5L);
        IO_WriteI(f, (LONGINT)W_1->Array->A[1 - 1], 0L);
        IO_WriteC(f, ':');
      }
      if (!Gen_CaseFlag) {
        {
          LONGINT B_1 = 2, B_2 = W_1->Used;

          if (B_1 <= B_2)
            for (u = B_1;; u += 1) {
              if (WriteTok_Language == WriteTok_Modula2) {
                IO_WriteC(f, ',');
                IO_WriteI(f, (LONGINT)W_1->Array->A[u - 1], 0L);
              } else {
                IO_WriteNl(f);
                IO_WriteS(f, (STRING)"case ", 5L);
                IO_WriteI(f, (LONGINT)W_1->Array->A[u - 1], 0L);
                IO_WriteC(f, ':');
              }
              if (u >= B_2) break;
            }
        }
      }
      if (WriteTok_Language == WriteTok_Modula2) {
        IO_WriteC(f, ':');
      }
      WriteProdComment(f, prod);
      if (index == 0) {
        if (WriteTok_Language == WriteTok_Modula2) {
          IO_WriteS(f, (STRING)"  DynArray.ReleaseArray (yyStateStack, yyStateStackSize, SYSTEM.TSIZE (yyTableElmt));", 85L);
          IO_WriteNl(f);
          IO_WriteS(f, (STRING)"  DynArray.ReleaseArray (yyAttributeStack, yyAttrStackSize, SYSTEM.TSIZE (tParsAttribute));", 91L);
          IO_WriteNl(f);
          IO_WriteS(f, (STRING)"  RETURN yyErrorCount;", 22L);
          IO_WriteNl(f);
        } else {
          IO_WriteS(f, (STRING)"  ReleaseArray ((char * *) & yyStateStack, & yyStateStackSize, sizeof (yyStateRange));", 86L);
          IO_WriteNl(f);
          IO_WriteS(f, (STRING)"  ReleaseArray ((char * *) & yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute));", 91L);
          IO_WriteNl(f);
          IO_WriteS(f, (STRING)"  return yyErrorCount;", 22L);
          IO_WriteNl(f);
        }
      } else {
        if (WriteTok_Language == WriteTok_Modula2) {
          if (prod->Len != 0) {
            IO_WriteS(f, (STRING)"  DEC (yyStackPtr, ", 19L);
            IO_WriteI(f, (LONGINT)prod->Len, 0L);
            IO_WriteS(f, (STRING)"); ", 3L);
          }
          IO_WriteS(f, (STRING)"yyNonterminal := ", 17L);
          IO_WriteI(f, (LONGINT)(prod->Left - Gen_NonTermOffset), 0L);
          IO_WriteS(f, (STRING)";", 1L);
          IO_WriteNl(f);
        } else {
          if (prod->Len != 0) {
            IO_WriteS(f, (STRING)"  yyStateStackPtr -=", 20L);
            IO_WriteI(f, (LONGINT)prod->Len, 0L);
            IO_WriteS(f, (STRING)"; yyAttrStackPtr -=", 19L);
            IO_WriteI(f, (LONGINT)prod->Len, 0L);
            IO_WriteS(f, (STRING)";", 1L);
          }
          IO_WriteS(f, (STRING)"  yyNonterminal = ", 18L);
          IO_WriteI(f, (LONGINT)(prod->Left - Gen_NonTermOffset), 0L);
          IO_WriteS(f, (STRING)"; {", 3L);
          IO_WriteNl(f);
        }
      }
      DynArray_ReleaseArray((ADDRESS *)&W_1->Array, &W_1->Count, (LONGINT)sizeof(Automaton_tIndex));
    }
    WriteSemanticAction(f, prod->Act, prod->Len, prod->ActPos);
    if (index != 0 && WriteTok_Language == WriteTok_C) {
      IO_WriteS(f, (STRING)"} break;", 8L);
      IO_WriteNl(f);
    }
    index = Automaton_NextProdIndex(index);
  }
  if (Gen_CaseLabels > 0) {
    CloseCase(f, cases);
  } else if (WriteTok_Language == WriteTok_Modula2) {
    IO_WriteS(f, (STRING)"END;", 4L);
    IO_WriteNl(f);
  } else {
    IO_WriteS(f, (STRING)"}", 1L);
    IO_WriteNl(f);
  }
}

static void OpenCase
# ifdef __STDC__
(IO_tFile f, Automaton_tStateIndex label)
# else
(f, label)
IO_tFile f;
Automaton_tStateIndex label;
# endif
{
  if (WriteTok_Language == WriteTok_Modula2) {
    IO_WriteS(f, (STRING)"CASE yyState OF", 15L);
    IO_WriteNl(f);
  } else {
    if (label <= Gen_LastReduceState) {
      IO_WriteS(f, (STRING)"if (yyState < ", 14L);
      IO_WriteI(f, (LONGINT)label, 0L);
      IO_WriteS(f, (STRING)") ", 2L);
    }
    IO_WriteS(f, (STRING)"switch (yyState) {", 18L);
    IO_WriteNl(f);
  }
}

static void NextCase
# ifdef __STDC__
(IO_tFile f, Automaton_tStateIndex label)
# else
(f, label)
IO_tFile f;
Automaton_tStateIndex label;
# endif
{
  if (WriteTok_Language == WriteTok_Modula2) {
    IO_WriteS(f, (STRING)"ELSE CASE yyState OF", 20L);
    IO_WriteNl(f);
  } else {
    IO_WriteS(f, (STRING)"} else ", 7L);
    if (label <= Gen_LastReduceState) {
      IO_WriteS(f, (STRING)"if (yyState < ", 14L);
      IO_WriteI(f, (LONGINT)label, 0L);
      IO_WriteS(f, (STRING)") ", 2L);
    }
    IO_WriteS(f, (STRING)"switch (yyState) {", 18L);
    IO_WriteNl(f);
  }
}

static void CloseCase
# ifdef __STDC__
(IO_tFile f, INTEGER cases)
# else
(f, cases)
IO_tFile f;
INTEGER cases;
# endif
{
  if (WriteTok_Language == WriteTok_Modula2) {
    while (cases > 0) {
      IO_WriteS(f, (STRING)"END; (* additional CASE *)", 26L);
      IO_WriteNl(f);
      DEC(cases);
    }
  } else {
    IO_WriteS(f, (STRING)"}", 1L);
    IO_WriteNl(f);
  }
}

static void WriteSemanticAction
# ifdef __STDC__
(IO_tFile f, Lists_tList a, CARDINAL len, TokenTab_PosType pos)
# else
(f, a, len, pos)
IO_tFile f;
Lists_tList a;
CARDINAL len;
TokenTab_PosType pos;
# endif
{
  CHAR c;
  Strings_tString s;
  Strings_tStringIndex i;
  Strings_tStringIndex i1, i2;
  CARDINAL AttrIndex;
  BOOLEAN negative;
  CHAR Delimiter;

  if (pos.Line != 0) {
    if (WriteTok_Language == WriteTok_Modula2) {
      IO_WriteS(f, (STRING)"(* line ", 8L);
      IO_WriteI(f, (LONGINT)pos.Line, 0L);
      IO_WriteS(f, (STRING)" \"", 2L);
      IO_WriteS(f, WriteTok_SourceFileName.A, 256L);
      IO_WriteS(f, (STRING)"\" *)", 4L);
      IO_WriteNl(f);
    } else {
      if (ArgCheck_LineFlag) {
        IO_WriteS(f, (STRING)"# line ", 7L);
        IO_WriteI(f, (LONGINT)pos.Line, 0L);
        IO_WriteS(f, (STRING)" \"", 2L);
        IO_WriteS(f, WriteTok_SourceFileName.A, 256L);
        IO_WriteC(f, '"');
        IO_WriteNl(f);
      } else {
        IO_WriteS(f, (STRING)"/* line ", 8L);
        IO_WriteI(f, (LONGINT)pos.Line, 0L);
        IO_WriteS(f, (STRING)" \"", 2L);
        IO_WriteS(f, WriteTok_SourceFileName.A, 256L);
        IO_WriteS(f, (STRING)"\" */", 4L);
        IO_WriteNl(f);
      }
    }
  }
  i1 = 2;
  while (!Lists_IsEmpty(a)) {
    StringMem_GetString((StringMem_tStringRef)Lists_Head(a), &s);
    i2 = Strings_Length(&s);
    Lists_Tail(&a);
    if (Lists_IsEmpty(a)) {
      DEC(i2);
    }
    if (WriteTok_Language == WriteTok_Modula2) {
      IO_WriteS(f, (STRING)"  ", 2L);
    }
    i = i1;
    while (i <= i2) {
      c = Strings_Char(&s, i);
      INC(i);
      if (c == '\\') {
        IO_WriteC(f, Strings_Char(&s, i));
        INC(i);
      } else if (c == '"' || c == '\'') {
        Delimiter = c;
        IO_WriteC(f, c);
        do {
          c = Strings_Char(&s, i);
          INC(i);
          IO_WriteC(f, c);
          if (WriteTok_Language == WriteTok_C && c == '\\') {
            IO_WriteC(f, Strings_Char(&s, i));
            INC(i);
          }
        } while (!(c == Delimiter));
      } else if (c == '$') {
        if (i <= i2 && Strings_Char(&s, i) == '$') {
          IO_WriteS(f, (STRING)"yySynAttribute", 14L);
          INC(i);
        } else {
          AttrIndex = 0;
          if (i <= i2 && Strings_Char(&s, i) == '-') {
            negative = TRUE;
            INC(i);
          } else {
            negative = FALSE;
          }
          while (i <= i2 && Strings_Char(&s, i) >= '0' && Strings_Char(&s, i) <= '9') {
            AttrIndex = AttrIndex * 10 + (ORD(Strings_Char(&s, i)) - ORD('0'));
            INC(i);
          }
          if (negative || AttrIndex <= len) {
            if (WriteTok_Language == WriteTok_Modula2) {
              IO_WriteS(f, (STRING)"yyAttributeStack^[yyStackPtr", 28L);
              if (negative) {
                IO_WriteS(f, (STRING)"-", 1L);
              } else {
                IO_WriteS(f, (STRING)"+", 1L);
              }
              IO_WriteI(f, (LONGINT)AttrIndex, 0L);
              IO_WriteS(f, (STRING)"]", 1L);
            } else {
              IO_WriteS(f, (STRING)"yyAttrStackPtr [", 16L);
              if (negative) {
                IO_WriteS(f, (STRING)"-", 1L);
              }
              IO_WriteI(f, (LONGINT)AttrIndex, 0L);
              IO_WriteS(f, (STRING)"-1]", 3L);
            }
          } else {
            IO_WriteC(f, c);
          }
        }
      } else {
        IO_WriteC(f, c);
      }
    }
    i1 = 1;
  }
  IO_WriteNl(f);
}

static void WriteProdComment
# ifdef __STDC__
(IO_tFile f, Automaton_tProduction prod)
# else
(f, prod)
IO_tFile f;
Automaton_tProduction prod;
# endif
{
  Automaton_tIndex i;

  if (WriteTok_Language == WriteTok_Modula2) {
    IO_WriteS(f, (STRING)" (* ", 4L);
  } else {
    IO_WriteS(f, (STRING)" /* ", 4L);
  }
  {
    register struct Automaton_9 *W_2 = prod;

    WriteToken(f, W_2->Left);
    IO_WriteS(f, (STRING)": ", 2L);
    {
      LONGCARD B_3 = 1, B_4 = W_2->Len;

      if (B_3 <= B_4)
        for (i = B_3;; i += 1) {
          WriteToken(f, W_2->Right.A[i - 1]);
          if (i >= B_4) break;
        }
    }
    IO_WriteC(f, '.');
  }
  if (WriteTok_Language == WriteTok_Modula2) {
    IO_WriteS(f, (STRING)"*)", 2L);
    IO_WriteNl(f);
  } else {
    IO_WriteS(f, (STRING)"*/", 2L);
    IO_WriteNl(f);
  }
}

static void WriteToken
# ifdef __STDC__
(IO_tFile f, TokenTab_Vocabulary t)
# else
(f, t)
IO_tFile f;
TokenTab_Vocabulary t;
# endif
{
  Strings_tString s;
  Idents_tIdent sym;
  TokenTab_TokenError error;
  CARDINAL i;

  sym = TokenTab_TokenToSymbol(t, &error);
  Idents_GetString(sym, &s);
  IO_WriteC(f, Strings_Char(&s, 1));
  if (WriteTok_Language == WriteTok_Modula2) {
    {
      LONGCARD B_5 = 2, B_6 = Strings_Length(&s);

      if (B_5 <= B_6)
        for (i = B_5;; i += 1) {
          if (Strings_Char(&s, (Strings_tStringIndex)i) == ')') {
            if (Strings_Char(&s, (Strings_tStringIndex)(i - 1)) == '*') {
              IO_WriteC(f, ' ');
            }
          } else if (Strings_Char(&s, (Strings_tStringIndex)i) == '*') {
            if (Strings_Char(&s, (Strings_tStringIndex)(i - 1)) == '(') {
              IO_WriteC(f, ' ');
            }
          }
          IO_WriteC(f, Strings_Char(&s, (Strings_tStringIndex)i));
          if (i >= B_6) break;
        }
    }
  } else {
    {
      LONGCARD B_7 = 2, B_8 = Strings_Length(&s);

      if (B_7 <= B_8)
        for (i = B_7;; i += 1) {
          if (Strings_Char(&s, (Strings_tStringIndex)i) == '/') {
            if (Strings_Char(&s, (Strings_tStringIndex)(i - 1)) == '*') {
              IO_WriteC(f, ' ');
            }
          } else if (Strings_Char(&s, (Strings_tStringIndex)i) == '*') {
            if (Strings_Char(&s, (Strings_tStringIndex)(i - 1)) == '/') {
              IO_WriteC(f, ' ');
            }
          }
          IO_WriteC(f, Strings_Char(&s, (Strings_tStringIndex)i));
          if (i >= B_8) break;
        }
    }
  }
  IO_WriteC(f, ' ');
}

static void WriteLong
# ifdef __STDC__
(IO_tFile f, LONGINT Check)
# else
(f, Check)
IO_tFile f;
LONGINT Check;
# endif
{
  LONGINT i, j;
  CARDINAL d;

  if (Check < 0) {
    IO_WriteC(f, '-');
    Check = -Check;
  }
  i = 1;
  while (i <= Check / 10) {
    i = i * 10;
  }
  while (i > 0) {
    d = Check / i;
    IO_WriteC(f, CHR(ORD('0') + d));
    j = d;
    DEC1(Check, j * i);
    i = i / 10;
  }
}

void GenLang__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Automaton__init();
    Compress__init();
    DynArray__init();
    ArgCheck__init();
    Gen__init();
    IO__init();
    Lists__init();
    Strings__init();
    StringMem__init();
    StringMem__init();
    Idents__init();
    TokenTab__init();
    WriteTok__init();

  }
}
