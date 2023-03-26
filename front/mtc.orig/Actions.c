#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_Actions
#include "Actions.h"
#endif

Idents_tIdent Actions_ScannerName;
Idents_tIdent Actions_ParserName;

typedef struct S_1 {
    Lists_tList Act;
    TokenTab_PosType ActPos;
    Lists_tList Comm;
    TokenTab_PosType CommPos;
} ElmtType;
static Actions_tActionMode ActionMode;
static struct S_2 {
    TokenTab_PosType A[Actions_Close + 1];
} KeyPos;
static struct S_3 {
    ElmtType A[Actions_Close + 1];
} Action;
static struct S_4 {
    Lists_tList A[Actions_Close + 1];
} ActionComm;
static struct S_5 {
    TokenTab_PosType A[Actions_Close + 1];
} ActionCommPos;
static TokenTab_PosType dummyPos;
static void Tab ARGS(());

static Strings_tStringIndex *G_1_i;
static CARDINAL *G_2_t;
static IO_tFile *G_3_f;

void Actions_PutComment
# ifdef __STDC__
(Actions_tActionMode kind, TokenTab_PosType kp, Lists_tList c, TokenTab_PosType cp)
# else
(kind, kp, c, cp)
Actions_tActionMode kind;
TokenTab_PosType kp;
Lists_tList c;
TokenTab_PosType cp;
# endif
{
  KeyPos.A[kind] = kp;
  ActionComm.A[kind] = c;
  ActionCommPos.A[kind] = cp;
}

void Actions_GetComment
# ifdef __STDC__
(Actions_tActionMode kind, TokenTab_PosType *kp, Lists_tList *c, TokenTab_PosType *cp)
# else
(kind, kp, c, cp)
Actions_tActionMode kind;
TokenTab_PosType *kp;
Lists_tList *c;
TokenTab_PosType *cp;
# endif
{
  *kp = KeyPos.A[kind];
  *c = ActionComm.A[kind];
  *cp = ActionCommPos.A[kind];
}

void Actions_PutAction
# ifdef __STDC__
(Actions_tActionMode kind, Lists_tList a, TokenTab_PosType ap, Lists_tList c, TokenTab_PosType cp)
# else
(kind, a, ap, c, cp)
Actions_tActionMode kind;
Lists_tList a;
TokenTab_PosType ap;
Lists_tList c;
TokenTab_PosType cp;
# endif
{
  {
    register ElmtType *W_1 = &Action.A[kind];

    W_1->Act = a;
    W_1->ActPos = ap;
    W_1->Comm = c;
    W_1->CommPos = cp;
  }
}

void Actions_GetAction
# ifdef __STDC__
(Actions_tActionMode kind, Lists_tList *a, TokenTab_PosType *ap, Lists_tList *c, TokenTab_PosType *cp)
# else
(kind, a, ap, c, cp)
Actions_tActionMode kind;
Lists_tList *a;
TokenTab_PosType *ap;
Lists_tList *c;
TokenTab_PosType *cp;
# endif
{
  {
    register ElmtType *W_2 = &Action.A[kind];

    *a = W_2->Act;
    *ap = W_2->ActPos;
    *c = W_2->Comm;
    *cp = W_2->CommPos;
  }
}

void Actions_WriteActions
# ifdef __STDC__
(Actions_tActionMode kind, IO_tFile f, BOOLEAN Line)
# else
(kind, f, Line)
Actions_tActionMode kind;
IO_tFile f;
BOOLEAN Line;
# endif
{
  if (Action.A[kind].ActPos.Line != 0) {
    if (WriteTok_Language == WriteTok_Modula2) {
      IO_WriteS(f, (STRING)"(* line ", 8L);
      IO_WriteI(f, (LONGINT)Action.A[kind].ActPos.Line, 0L);
      IO_WriteS(f, (STRING)" \"", 2L);
      IO_WriteS(f, WriteTok_SourceFileName.A, 256L);
      IO_WriteS(f, (STRING)"\" *)", 4L);
      IO_WriteNl(f);
    } else {
      if (Line) {
        IO_WriteS(f, (STRING)"# line ", 7L);
        IO_WriteI(f, (LONGINT)Action.A[kind].ActPos.Line, 1L);
        IO_WriteS(f, (STRING)" \"", 2L);
        IO_WriteS(f, WriteTok_SourceFileName.A, 256L);
        IO_WriteC(f, '"');
        IO_WriteNl(f);
      } else {
        IO_WriteS(f, (STRING)"/* line ", 8L);
        IO_WriteI(f, (LONGINT)Action.A[kind].ActPos.Line, 1L);
        IO_WriteS(f, (STRING)" \"", 2L);
        IO_WriteS(f, WriteTok_SourceFileName.A, 256L);
        IO_WriteS(f, (STRING)"\" */", 4L);
        IO_WriteNl(f);
      }
    }
  }
  Actions_WriteSemanticAction(f, Action.A[kind].Act, 0L);
}

static void Tab
# ifdef __STDC__
()
# else
()
# endif
{
  {
    Strings_tStringIndex B_1 = 1, B_2 = *G_2_t;

    if (B_1 <= B_2)
      for (*G_1_i = B_1;; *G_1_i += 1) {
        IO_WriteC(*G_3_f, ' ');
        IO_WriteC(*G_3_f, ' ');
        if (*G_1_i >= B_2) break;
      }
  }
}

void Actions_WriteSemanticAction
# ifdef __STDC__
(IO_tFile f, Lists_tList a, CARDINAL t)
# else
(f, a, t)
IO_tFile f;
Lists_tList a;
CARDINAL t;
# endif
{
  CHAR c;
  Strings_tString s;
  Strings_tStringIndex i;
  Strings_tStringIndex i1, i2;
  CHAR Delimiter;
  Strings_tStringIndex *L_1;
  CARDINAL *L_2;
  IO_tFile *L_3;

  L_1 = G_1_i;
  G_1_i = &i;
  L_2 = G_2_t;
  G_2_t = &t;
  L_3 = G_3_f;
  G_3_f = &f;
  i1 = 2;
  while (!Lists_IsEmpty(a)) {
    StringMem_GetString((StringMem_tStringRef)Lists_Head(a), &s);
    Lists_Tail(&a);
    i2 = Strings_Length(&s);
    if (Lists_IsEmpty(a)) {
      DEC(i2);
    }
    Tab();
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
      } else {
        IO_WriteC(f, c);
      }
    }
    i1 = 1;
  }
  IO_WriteNl(f);
  G_1_i = L_1;
  G_2_t = L_2;
  G_3_f = L_3;
}

void Actions_WriteStringList
# ifdef __STDC__
(IO_tFile file, Lists_tList slist)
# else
(file, slist)
IO_tFile file;
Lists_tList slist;
# endif
{
  while (!Lists_IsEmpty(slist)) {
    StringMem_WriteString(file, (StringMem_tStringRef)Lists_Head(slist));
    Lists_Tail(&slist);
  }
}

void Actions__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    TokenTab__init();
    StringMem__init();
    Strings__init();
    Idents__init();
    IO__init();
    Lists__init();
    IO__init();
    Lists__init();
    Memory__init();
    Strings__init();
    StringMem__init();
    TokenTab__init();
    WriteTok__init();

    dummyPos.Line = 0;
    dummyPos.Column = 0;
    for (ActionMode = Actions_Export; ActionMode <= Actions_Close; ActionMode += 1) {
      KeyPos.A[ActionMode] = dummyPos;
      Lists_MakeList(&ActionComm.A[ActionMode]);
      ActionCommPos.A[ActionMode] = dummyPos;
      Lists_MakeList(&Action.A[ActionMode].Act);
      Action.A[ActionMode].ActPos = dummyPos;
      Lists_MakeList(&Action.A[ActionMode].Comm);
      Action.A[ActionMode].CommPos = dummyPos;
    }
  }
}
