#include "SYSTEM_.h"

#ifndef DEFINITION_Convert
#include "Convert.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Grammar
#include "Grammar.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Environs
#include "Environs.h"
#endif


static CHAR cTREE [] = "yyt";
static CHAR cKIND [] = "Kind";
static CHAR cCLASS [] = "yyClass";
static CHAR cCOST [] = "Cost";
#define BitsPerBitset   32
#define InitTableSize   100
typedef struct S_1 *tAccessList;
typedef struct S_1 {
    Queues_tQueue Path;
    Idents_tIdent Sel;
    Idents_tIdent Ident;
    BOOLEAN Sure;
    Queues_tQueue Functions;
    tAccessList Next;
    INTEGER CallCount;
    Patterns_tPattern Pat;
} tAccess;
typedef struct S_2 {
    Patterns_tPattern Pat;
    BOOLEAN Cond;
    Sets_tSet Selectors;
    tAccessList Accesses;
    tAccessList Last;
} tTableEntry;
typedef struct S_3 *tFunctions;
typedef struct S_3 {
    Environs_tFunction Funct;
    tFunctions Next;
} tFunctionL;
static struct S_4 {
    tTableEntry A[1000 + 1];
} *Table;
static LONGINT TableSize, TableCount;
static INTEGER vMaxCalls;
static tFunctions Functions;
static Environs_tFunction Function ARGS((Idents_tIdent name));
static tAccessList Definition ARGS((Environs_tDirNo no, Idents_tIdent sel));
static void WriteQueue ARGS((IO_tFile f, Queues_tQueue Path));


Environs_tFunction Environs_MakeFunctEnv
# ifdef __STDC__
(Idents_tIdent name, Sets_tSet domain)
# else
(name, domain)
Idents_tIdent name;
Sets_tSet domain;
# endif
{
  Environs_tFunction f;
  tFunctions l;

  f = (Environs_tFunction)Memory_Alloc((LONGINT)sizeof(Environs_tFunctionR));
  l = (tFunctions)Memory_Alloc((LONGINT)sizeof(tFunctionL));
  l->Funct = f;
  l->Next = Functions;
  Functions = l;
  f->Name = name;
  Queues_MakeQueue(&f->Pats);
  Sets_MakeSet(&f->Domain, (Sets_tElement)Scanner_MaxIdent);
  Sets_Assign(&f->Domain, domain);
  return f;
}

BOOLEAN Environs_InDomain
# ifdef __STDC__
(Idents_tIdent name, Patterns_tPattern pat)
# else
(name, pat)
Idents_tIdent name;
Patterns_tPattern pat;
# endif
{
  Environs_tFunction f;
  BOOLEAN in;
  Sets_tSet classes;

  f = Function(name);
  Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
  Patterns_PatternClasses(pat, &classes);
  Sets_Intersection(&classes, f->Domain);
  in = !Sets_IsEmpty(classes);
  Sets_ReleaseSet(&classes);
  return in;
}

static Environs_tFunction Function
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  tFunctions l;

  l = Functions;
  for (;;) {
    if (l == NIL) {
      Errors_ERROR((STRING)"Environs.Function: not found", 28L);
    }
    if (l->Funct->Name == name) {
      return l->Funct;
    }
    l = l->Next;
  } EXIT_1:;
}

Environs_tDirNo Environs_MakeDirective
# ifdef __STDC__
(Environs_tFunction funct)
# else
(funct)
Environs_tFunction funct;
# endif
{
  INTEGER no;

  INC(TableCount);
  if (TableCount >= TableSize) {
    if (TableSize == 0) {
      TableSize = InitTableSize;
      DynArray_MakeArray((ADDRESS *)&Table, &TableSize, (LONGINT)sizeof(tTableEntry));
    } else {
      DynArray_ExtendArray((ADDRESS *)&Table, &TableSize, (LONGINT)sizeof(tTableEntry));
    }
  }
  no = TableCount;
  Queues_Append(&funct->Pats, (ADDRESS)no);
  {
    register tTableEntry *W_1 = &Table->A[no];

    W_1->Pat = NIL;
    Sets_MakeSet(&W_1->Selectors, (Sets_tElement)Scanner_MaxIdent);
    W_1->Accesses = NIL;
    W_1->Last = NIL;
  }
  return TableCount;
}

void Environs_GetPatterns
# ifdef __STDC__
(Environs_tFunction funct, Queues_tQueue *pats)
# else
(funct, pats)
Environs_tFunction funct;
Queues_tQueue *pats;
# endif
{
  INTEGER no, pos;

  Queues_AssignEmpty(pats);
  {
    LONGINT B_1 = 1, B_2 = Queues_Length(funct->Pats);

    if (B_1 <= B_2)
      for (pos = B_1;; pos += 1) {
        no = (INTEGER)Queues_GetElement(funct->Pats, pos);
        if (!Table->A[no].Cond) {
          Queues_Append(pats, (ADDRESS)Table->A[no].Pat);
        }
        if (pos >= B_2) break;
      }
  }
}

void Environs_GetCondPatterns
# ifdef __STDC__
(Environs_tFunction funct, Queues_tQueue *pats)
# else
(funct, pats)
Environs_tFunction funct;
Queues_tQueue *pats;
# endif
{
  INTEGER no, pos;

  Queues_AssignEmpty(pats);
  {
    LONGINT B_3 = 1, B_4 = Queues_Length(funct->Pats);

    if (B_3 <= B_4)
      for (pos = B_3;; pos += 1) {
        no = (INTEGER)Queues_GetElement(funct->Pats, pos);
        if (Table->A[no].Cond) {
          Queues_Append(pats, (ADDRESS)Table->A[no].Pat);
        }
        if (pos >= B_4) break;
      }
  }
}

Environs_tDirNo Environs_MaxDirective
# ifdef __STDC__
()
# else
()
# endif
{
  return TableCount;
}

void Environs_SetPattern
# ifdef __STDC__
(Environs_tDirNo no, Patterns_tPattern pat)
# else
(no, pat)
Environs_tDirNo no;
Patterns_tPattern pat;
# endif
{
  {
    register tTableEntry *W_2 = &Table->A[no];

    W_2->Pat = pat;
    W_2->Cond = FALSE;
  }
}

void Environs_SetCondPattern
# ifdef __STDC__
(Environs_tDirNo no, Patterns_tPattern pat)
# else
(no, pat)
Environs_tDirNo no;
Patterns_tPattern pat;
# endif
{
  {
    register tTableEntry *W_3 = &Table->A[no];

    W_3->Pat = pat;
    W_3->Cond = TRUE;
  }
}

Patterns_tPattern Environs_GetPattern
# ifdef __STDC__
(Environs_tDirNo no)
# else
(no)
Environs_tDirNo no;
# endif
{
  return Table->A[no].Pat;
}

void Environs_DefineAccess
# ifdef __STDC__
(Environs_tDirNo no, Queues_tQueue path, Idents_tIdent sel, Idents_tIdent ident, BOOLEAN sure)
# else
(no, path, sel, ident, sure)
Environs_tDirNo no;
Queues_tQueue path;
Idents_tIdent sel, ident;
BOOLEAN sure;
# endif
{
  tAccessList access;

  if (sel != Scanner_NoIdent) {
    Sets_Include(&Table->A[no].Selectors, (Sets_tElement)sel);
  }
  access = (tAccessList)Memory_Alloc((LONGINT)sizeof(tAccess));
  {
    register tAccess *W_4 = access;

    Queues_MakeQueue(&W_4->Path);
    Queues_Assign(&W_4->Path, path);
    Queues_MakeQueue(&W_4->Functions);
    W_4->Sel = sel;
    W_4->Ident = ident;
    W_4->Sure = sure || ident == Scanner_NoIdent;
    W_4->Next = NIL;
    W_4->CallCount = 0;
  }
  if (Table->A[no].Last == NIL) {
    if (Types_Type(ident) == Types_cNode) {
      access->Sure = TRUE;
    }
    Table->A[no].Accesses = access;
  } else {
    Table->A[no].Last->Next = access;
  }
  Table->A[no].Last = access;
}

BOOLEAN Environs_Defined
# ifdef __STDC__
(Environs_tDirNo no, Idents_tIdent sel)
# else
(no, sel)
Environs_tDirNo no;
Idents_tIdent sel;
# endif
{
  return Sets_IsElement((Sets_tElement)sel, &Table->A[no].Selectors);
}

void Environs_DefineSelPat
# ifdef __STDC__
(Environs_tDirNo no, Idents_tIdent sel, Patterns_tPattern pat)
# else
(no, sel, pat)
Environs_tDirNo no;
Idents_tIdent sel;
Patterns_tPattern pat;
# endif
{
  tAccessList access;

  access = Definition(no, sel);
  access->Pat = pat;
}

Patterns_tPattern Environs_SelPattern
# ifdef __STDC__
(Environs_tDirNo no, Idents_tIdent sel)
# else
(no, sel)
Environs_tDirNo no;
Idents_tIdent sel;
# endif
{
  tAccessList access;

  access = Definition(no, sel);
  return access->Pat;
}

static tAccessList Definition
# ifdef __STDC__
(Environs_tDirNo no, Idents_tIdent sel)
# else
(no, sel)
Environs_tDirNo no;
Idents_tIdent sel;
# endif
{
  tAccessList access;

  access = Table->A[no].Accesses;
  for (;;) {
    if (access->Sel == sel) {
      return access;
    }
    access = access->Next;
  } EXIT_2:;
}

void Environs_CallFunction
# ifdef __STDC__
(Environs_tDirNo no, Idents_tIdent sel, Idents_tIdent name)
# else
(no, sel, name)
Environs_tDirNo no;
Idents_tIdent sel, name;
# endif
{
  tAccessList access;

  access = Definition(no, sel);
  INC(access->CallCount);
  if (access->CallCount > vMaxCalls) {
    vMaxCalls = access->CallCount;
  }
  Queues_Append(&access->Functions, Convert_IdToAdr(name));
}

BOOLEAN Environs_HeadCalled
# ifdef __STDC__
(Environs_tDirNo no)
# else
(no)
Environs_tDirNo no;
# endif
{
  return !Queues_IsEmpty(Table->A[no].Accesses->Functions);
}

BOOLEAN Environs_IsHead
# ifdef __STDC__
(Environs_tDirNo no, Idents_tIdent sel)
# else
(no, sel)
Environs_tDirNo no;
Idents_tIdent sel;
# endif
{
  return Table->A[no].Accesses->Sel == sel;
}

INTEGER Environs_MaxCalls
# ifdef __STDC__
()
# else
()
# endif
{
  return vMaxCalls;
}

static void WriteQueue
# ifdef __STDC__
(IO_tFile f, Queues_tQueue Path)
# else
(f, Path)
IO_tFile f;
Queues_tQueue Path;
# endif
{
  INTEGER pos;

  IO_WriteS(f, cTREE, 3L);
  {
    LONGINT B_5 = 1, B_6 = Queues_Length(Path) - 1;

    if (B_5 <= B_6)
      for (pos = B_5;; pos += 1) {
        if (ODD(pos)) {
          IO_WriteS(f, (STRING)"^.", 2L);
        } else {
          IO_WriteS(f, (STRING)".", 1L);
        }
        Idents_WriteIdent(f, Convert_AdrToId(Queues_GetElement(Path, pos)));
        if (pos >= B_6) break;
      }
  }
}

void Environs_WritePath
# ifdef __STDC__
(IO_tFile f, Environs_tDirNo no, Idents_tIdent sel)
# else
(f, no, sel)
IO_tFile f;
Environs_tDirNo no;
Idents_tIdent sel;
# endif
{
  tAccessList access;

  access = Definition(no, sel);
  WriteQueue(f, access->Path);
}

void Environs_WriteAccess
# ifdef __STDC__
(IO_tFile f, Environs_tDirNo no, Idents_tIdent sel)
# else
(f, no, sel)
IO_tFile f;
Environs_tDirNo no;
Idents_tIdent sel;
# endif
{
  tAccessList access;

  access = Definition(no, sel);
  WriteQueue(f, access->Path);
  IO_WriteS(f, (STRING)"^.", 2L);
  Idents_WriteIdent(f, access->Ident);
}

BOOLEAN Environs_AlwaysMatch
# ifdef __STDC__
(Environs_tDirNo no, Idents_tIdent node)
# else
(no, node)
Environs_tDirNo no;
Idents_tIdent node;
# endif
{
  Patterns_tPattern pat;
  Patterns_tRelation relation;

  pat = Patterns_NormPattern(Patterns_MakePattern(node));
  relation = Patterns_Relation(Table->A[no].Pat, pat);
  Patterns_ReleasePattern(&pat);
  return relation == Patterns_cEqual || relation == Patterns_cSupersumes;
}

BOOLEAN Environs_HasCondition
# ifdef __STDC__
(Environs_tDirNo no)
# else
(no)
Environs_tDirNo no;
# endif
{
  return Table->A[no].Cond;
}

void Environs_WriteMatch
# ifdef __STDC__
(IO_tFile f, Environs_tDirNo no, INTEGER margin, Idents_tIdent GrammarName)
# else
(f, no, margin, GrammarName)
IO_tFile f;
Environs_tDirNo no;
INTEGER margin;
Idents_tIdent GrammarName;
# endif
{
  tAccessList access;
  BOOLEAN started;

  started = FALSE;
  access = Table->A[no].Accesses;
  while (access != NIL) {
    if (!access->Sure) {
      if (started) {
        IO_WriteNl(f);
        Layout_WriteSpaces(f, 2 * margin);
        IO_WriteS(f, (STRING)" & ", 3L);
      }
      started = TRUE;
      if (Types_Type(access->Ident) == Types_cNode) {
        IO_WriteS(f, (STRING)"(", 1L);
        WriteQueue(f, access->Path);
        IO_WriteS(f, (STRING)"^.", 2L);
        IO_WriteS(f, cKIND, 4L);
        IO_WriteS(f, (STRING)" = ", 3L);
        Idents_WriteIdent(f, GrammarName);
        IO_WriteS(f, (STRING)".", 1L);
        Idents_WriteIdent(f, Grammar_NodeIdent(access->Ident));
        IO_WriteS(f, (STRING)")", 1L);
      } else {
        IO_WriteS(f, cCLASS, 7L);
        IO_WriteS(f, (STRING)" (", 2L);
        WriteQueue(f, access->Path);
        IO_WriteS(f, (STRING)", yyC", 5L);
        Idents_WriteIdent(f, access->Ident);
        IO_WriteS(f, (STRING)" MOD yyBitsPerBitset", 20L);
        IO_WriteS(f, (STRING)", yyC", 5L);
        Idents_WriteIdent(f, access->Ident);
        IO_WriteS(f, (STRING)" DIV yyBitsPerBitset", 20L);
        IO_WriteS(f, (STRING)")", 1L);
      }
    }
    access = access->Next;
  }
  if (!started) {
    IO_WriteS(f, (STRING)"TRUE", 4L);
  }
}

void Environs_WriteCost
# ifdef __STDC__
(IO_tFile f, Environs_tDirNo no, INTEGER margin)
# else
(f, no, margin)
IO_tFile f;
Environs_tDirNo no;
INTEGER margin;
# endif
{
  tAccessList access;
  INTEGER pos;

  access = Table->A[no].Accesses;
  while (access != NIL) {
    {
      LONGINT B_7 = 1, B_8 = Queues_Length(access->Functions);

      if (B_7 <= B_8)
        for (pos = B_7;; pos += 1) {
          IO_WriteNl(f);
          Layout_WriteSpaces(f, 2 * margin);
          IO_WriteS(f, (STRING)"+ ", 2L);
          IO_WriteS(f, cCOST, 4L);
          Idents_WriteIdent(f, Convert_AdrToId(Queues_GetElement(access->Functions, pos)));
          IO_WriteS(f, (STRING)" (", 2L);
          WriteQueue(f, access->Path);
          IO_WriteS(f, (STRING)")", 1L);
          if (pos >= B_8) break;
        }
    }
    access = access->Next;
  }
}

void Environs__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    IO__init();
    Patterns__init();
    Queues__init();
    Sets__init();
    Convert__init();
    DynArray__init();
    Grammar__init();
    Idents__init();
    IO__init();
    Layout__init();
    Memory__init();
    Patterns__init();
    Queues__init();
    Scanner__init();
    Sets__init();
    Types__init();
    Sets__init();
    Errors__init();

    TableCount = 0;
    TableSize = 0;
    vMaxCalls = 1;
    Functions = NIL;
  }
}
