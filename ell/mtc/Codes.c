#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Codes
#include "Codes.h"
#endif

INTEGER Codes_vMaxRecSetIndex, Codes_vMaxSetIndex, Codes_EmptyRecSetIndex;

#define NoCode   -1
#define InitTermArraySize   200
#define InitCodeArraySize   100
#define InitRecSetArraySize   20
#define InitSetArraySize   20
typedef struct S_1 {
    Codes_tCode Code;
} tTermR;
typedef struct S_2 {
    Idents_tIdent Term;
} tCodeR;
static struct S_3 {
    tTermR A[1000 + 1];
} *TermArray;
static LONGINT TermArraySizeL;
static Idents_tIdent TermArraySize;
static struct S_4 {
    tCodeR A[1000 + 1];
} *CodeArray;
static LONGINT CodeArraySizeL;
static Codes_tCode CodeArraySize;
static Codes_tCode vMaxCode, vDefCode;
static struct S_5 {
    Sets_tSet A[1000 + 1];
} *RecSetArray;
static LONGINT RecSetArraySizeL;
static INTEGER RecSetArraySize;
static struct S_6 {
    Sets_tSet A[1000 + 1];
} *SetArray;
static LONGINT SetArraySizeL;
static INTEGER SetArraySize;
static Codes_tCode DefCode ARGS(());
static void FixTerm ARGS((Idents_tIdent term));
static void FixCode ARGS((Codes_tCode code));
static IO_tFile f;
static void WriteName ARGS((Sets_tElement e));


void Codes_SetCode
# ifdef __STDC__
(Idents_tIdent term, Codes_tCode code)
# else
(term, code)
Idents_tIdent term;
Codes_tCode code;
# endif
{
  FixTerm(term);
  FixCode(code);
  TermArray->A[term].Code = code;
  CodeArray->A[code].Term = term;
  if (code > vMaxCode) {
    vMaxCode = code;
  }
}

Codes_tCode Codes_Code
# ifdef __STDC__
(Idents_tIdent term)
# else
(term)
Idents_tIdent term;
# endif
{
  FixTerm(term);
  return TermArray->A[term].Code;
}

Idents_tIdent Codes_Term
# ifdef __STDC__
(Codes_tCode code)
# else
(code)
Codes_tCode code;
# endif
{
  FixCode(code);
  return CodeArray->A[code].Term;
}

BOOLEAN Codes_IsCode
# ifdef __STDC__
(Codes_tCode code)
# else
(code)
Codes_tCode code;
# endif
{
  return Codes_Term(code) != Scanner_NoIdent;
}

BOOLEAN Codes_IsCoded
# ifdef __STDC__
(Idents_tIdent term)
# else
(term)
Idents_tIdent term;
# endif
{
  return Codes_Code(term) != NoCode;
}

void Codes_SetDefCode
# ifdef __STDC__
(Idents_tIdent term)
# else
(term)
Idents_tIdent term;
# endif
{
  Codes_tCode code;

  code = DefCode();
  Codes_SetCode(term, code);
}

static Codes_tCode DefCode
# ifdef __STDC__
()
# else
()
# endif
{
  Codes_tCode code;

  for (;;) {
    FixCode(vDefCode);
    if (!Codes_IsCode(vDefCode)) {
      return vDefCode;
    }
    INC(vDefCode);
  } EXIT_1:;
}

Codes_tCode Codes_MaxCode
# ifdef __STDC__
()
# else
()
# endif
{
  return vMaxCode;
}

static void FixTerm
# ifdef __STDC__
(Idents_tIdent term)
# else
(term)
Idents_tIdent term;
# endif
{
  Idents_tIdent OldSize;

  if (term >= TermArraySize) {
    OldSize = TermArraySize;
    if (TermArraySize == 0) {
      DynArray_MakeArray((ADDRESS *)&TermArray, &TermArraySizeL, (LONGINT)sizeof(tTermR));
      TermArraySize = TermArraySizeL;
    }
    while (term >= TermArraySize) {
      DynArray_ExtendArray((ADDRESS *)&TermArray, &TermArraySizeL, (LONGINT)sizeof(tTermR));
      TermArraySize = TermArraySizeL;
    }
    while (OldSize < TermArraySize) {
      {
        register tTermR *W_1 = &TermArray->A[OldSize];

        W_1->Code = NoCode;
      }
      INC(OldSize);
    }
  }
}

static void FixCode
# ifdef __STDC__
(Codes_tCode code)
# else
(code)
Codes_tCode code;
# endif
{
  Codes_tCode OldSize;

  if (code >= CodeArraySize) {
    OldSize = CodeArraySize;
    if (CodeArraySize == 0) {
      DynArray_MakeArray((ADDRESS *)&CodeArray, &CodeArraySizeL, (LONGINT)sizeof(tCodeR));
      CodeArraySize = CodeArraySizeL;
    }
    while (code >= CodeArraySize) {
      DynArray_ExtendArray((ADDRESS *)&CodeArray, &CodeArraySizeL, (LONGINT)sizeof(tCodeR));
      CodeArraySize = CodeArraySizeL;
    }
    while (OldSize < CodeArraySize) {
      {
        register tCodeR *W_2 = &CodeArray->A[OldSize];

        W_2->Term = Scanner_NoIdent;
      }
      INC(OldSize);
    }
  }
}

INTEGER Codes_RecSetIndex
# ifdef __STDC__
(Sets_tSet set)
# else
(set)
Sets_tSet set;
# endif
{
  INTEGER Index;
  Sets_tSet Codes;
  Idents_tIdent Ident;

  Sets_MakeSet(&Codes, (Sets_tElement)vMaxCode);
  if (!Sets_IsEmpty(set)) {
    {
      SHORTCARD B_1 = Sets_Minimum(&set), B_2 = Sets_Maximum(&set);

      if (B_1 <= B_2)
        for (Ident = B_1;; Ident += 1) {
          if (Sets_IsElement((Sets_tElement)Ident, &set) && Ident != Scanner_Epsilon) {
            Sets_Include(&Codes, (Sets_tElement)Codes_Code(Ident));
          }
          if (Ident >= B_2) break;
        }
    }
  }
  Index = Codes_vMaxRecSetIndex;
  for (;;) {
    if (Index == Codes_cNoIndex) {
      goto EXIT_2;
    }
    if (Sets_IsEqual(&RecSetArray->A[Index], &Codes)) {
      goto EXIT_2;
    }
    DEC(Index);
  } EXIT_2:;
  if (Index == Codes_cNoIndex) {
    INC(Codes_vMaxRecSetIndex);
    Index = Codes_vMaxRecSetIndex;
    if (Codes_vMaxRecSetIndex >= RecSetArraySize) {
      if (RecSetArraySize == 0) {
        DynArray_MakeArray((ADDRESS *)&RecSetArray, &RecSetArraySizeL, (LONGINT)sizeof(Sets_tSet));
        RecSetArraySize = RecSetArraySizeL;
      } else {
        DynArray_ExtendArray((ADDRESS *)&RecSetArray, &RecSetArraySizeL, (LONGINT)sizeof(Sets_tSet));
        RecSetArraySize = RecSetArraySizeL;
      }
    }
    RecSetArray->A[Index] = Codes;
  } else {
    Sets_ReleaseSet(&Codes);
  }
  return Index;
}

INTEGER Codes_SetIndex
# ifdef __STDC__
(Sets_tSet set)
# else
(set)
Sets_tSet set;
# endif
{
  INTEGER Index;
  Sets_tSet Codes;
  Idents_tIdent Ident;

  Sets_MakeSet(&Codes, (Sets_tElement)vMaxCode);
  {
    SHORTCARD B_3 = Sets_Minimum(&set), B_4 = Sets_Maximum(&set);

    if (B_3 <= B_4)
      for (Ident = B_3;; Ident += 1) {
        if (Sets_IsElement((Sets_tElement)Ident, &set) && Ident != Scanner_Epsilon) {
          Sets_Include(&Codes, (Sets_tElement)Codes_Code(Ident));
        }
        if (Ident >= B_4) break;
      }
  }
  Index = Codes_vMaxSetIndex;
  for (;;) {
    if (Index == Codes_cNoIndex) {
      goto EXIT_3;
    }
    if (Sets_IsEqual(&SetArray->A[Index], &Codes)) {
      goto EXIT_3;
    }
    DEC(Index);
  } EXIT_3:;
  if (Index == Codes_cNoIndex) {
    INC(Codes_vMaxSetIndex);
    Index = Codes_vMaxSetIndex;
    if (Codes_vMaxSetIndex >= SetArraySize) {
      if (SetArraySize == 0) {
        DynArray_MakeArray((ADDRESS *)&SetArray, &SetArraySizeL, (LONGINT)sizeof(Sets_tSet));
        SetArraySize = SetArraySizeL;
      } else {
        DynArray_ExtendArray((ADDRESS *)&SetArray, &SetArraySizeL, (LONGINT)sizeof(Sets_tSet));
        SetArraySize = SetArraySizeL;
      }
    }
    SetArray->A[Index] = Codes;
  } else {
    Sets_ReleaseSet(&Codes);
  }
  return Index;
}

void Codes_GetRecSet
# ifdef __STDC__
(INTEGER index, Sets_tSet *set)
# else
(index, set)
INTEGER index;
Sets_tSet *set;
# endif
{
  Sets_Assign(set, RecSetArray->A[index]);
}

void Codes_GetSet
# ifdef __STDC__
(INTEGER index, Sets_tSet *set)
# else
(index, set)
INTEGER index;
Sets_tSet *set;
# endif
{
  if (index > Codes_vMaxSetIndex) {
    Sets_AssignEmpty(set);
  } else {
    Sets_Assign(set, SetArray->A[index]);
  }
}

void Codes_WriteIndex
# ifdef __STDC__
(IO_tFile file, INTEGER index)
# else
(file, index)
IO_tFile file;
INTEGER index;
# endif
{
  Sets_tSet set;

  if (index == Codes_cNoIndex) {
    return;
  }
  Sets_MakeSet(&set, (Sets_tElement)Codes_MaxCode());
  Codes_GetSet(index, &set);
  f = file;
  Sets_ForallDo(set, (Sets_ProcOftElement)WriteName);
  Sets_ReleaseSet(&set);
}

void Codes_WriteRecIndex
# ifdef __STDC__
(IO_tFile file, INTEGER index)
# else
(file, index)
IO_tFile file;
INTEGER index;
# endif
{
  Sets_tSet set;

  if (index == Codes_cNoIndex) {
    return;
  }
  Sets_MakeSet(&set, (Sets_tElement)Codes_MaxCode());
  Codes_GetRecSet(index, &set);
  f = file;
  Sets_ForallDo(set, (Sets_ProcOftElement)WriteName);
  Sets_ReleaseSet(&set);
}

static void WriteName
# ifdef __STDC__
(Sets_tElement e)
# else
(e)
Sets_tElement e;
# endif
{
  IO_WriteS(f, (STRING)" ", 1L);
  Idents_WriteIdent(f, Codes_Term((LONGINT)e));
}

void Codes__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Sets__init();
    IO__init();
    DynArray__init();
    Idents__init();
    Scanner__init();
    Sets__init();
    IO__init();

    TermArraySizeL = InitTermArraySize;
    TermArraySize = 0;
    CodeArraySizeL = InitCodeArraySize;
    CodeArraySize = 0;
    RecSetArraySizeL = InitRecSetArraySize;
    RecSetArraySize = 0;
    SetArraySizeL = InitSetArraySize;
    SetArraySize = 0;
    vDefCode = 1;
    vMaxCode = 0;
    Codes_vMaxSetIndex = -1;
    Codes_vMaxRecSetIndex = -1;
  }
}
