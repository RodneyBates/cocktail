#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Relations
#include "Relations.h"
#endif


static INTEGER i, j;
static Relations_tRelation gRel;
static BOOLEAN gSymmetric ARGS((Sets_tElement e));
typedef struct S_1 {
    SHORTCARD A[100000000 + 1];
} PredCount;
static PredCount *PredCountPtr;
static Sets_tSet WithoutPred;
static void gPredCount ARGS((Sets_tElement e));
static void gPredCount2 ARGS((Sets_tElement e));
static Relations_ProcOfIntIntToBool gProc2b;
static BOOLEAN gProc1b ARGS((Sets_tElement e));
static Relations_ProcOfIntInt gProc2;
static void gProc1 ARGS((Sets_tElement e));
static IO_tFile g;
static void WritePair ARGS((INTEGER e1, INTEGER e2));


void Relations_MakeRelation
# ifdef __STDC__
(Relations_tRelation *Rel, INTEGER Max1, INTEGER Max2)
# else
(Rel, Max1, Max2)
Relations_tRelation *Rel;
INTEGER Max1, Max2;
# endif
{
  LONGINT ElmtCount;

  Rel->Max1 = Max1;
  Rel->Max2 = Max2;
  ElmtCount = VAL(LONGINT, Max1 + 1);
  DynArray_MakeArray(&Rel->ArrayPtr, &ElmtCount, sizeof(Sets_tSet));
  {
    LONGINT B_1 = 0, B_2 = Rel->Max1;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        Sets_MakeSet(&Rel->ArrayPtr->A[i], Max2);
        if (i >= B_2) break;
      }
  }
}

void Relations_ReleaseRelation
# ifdef __STDC__
(Relations_tRelation *Rel)
# else
(Rel)
Relations_tRelation *Rel;
# endif
{
  LONGINT ElmtCount;

  {
    LONGINT B_3 = 0, B_4 = Rel->Max1;

    if (B_3 <= B_4)
      for (i = B_3;; i += 1) {
        Sets_ReleaseSet(&Rel->ArrayPtr->A[i]);
        if (i >= B_4) break;
      }
  }
  ElmtCount = VAL(LONGINT, Rel->Max1 + 1);
  DynArray_ReleaseArray(&Rel->ArrayPtr, &ElmtCount, sizeof(Sets_tSet));
}

void Relations_Include
# ifdef __STDC__
(Relations_tRelation *Rel, INTEGER e1, INTEGER e2)
# else
(Rel, e1, e2)
Relations_tRelation *Rel;
INTEGER e1, e2;
# endif
{
  Sets_Include(&Rel->ArrayPtr->A[e1], e2);
}

void Relations_Exclude
# ifdef __STDC__
(Relations_tRelation *Rel, INTEGER e1, INTEGER e2)
# else
(Rel, e1, e2)
Relations_tRelation *Rel;
INTEGER e1, e2;
# endif
{
  Sets_Exclude(&Rel->ArrayPtr->A[e1], e2);
}

BOOLEAN Relations_IsElement
# ifdef __STDC__
(INTEGER e1, INTEGER e2, Relations_tRelation Rel)
# else
(e1, e2, Rel)
INTEGER e1, e2;
Relations_tRelation Rel;
# endif
{
  return Sets_IsElement(e2, &Rel.ArrayPtr->A[e1]);
}

BOOLEAN Relations_IsRelated
# ifdef __STDC__
(INTEGER e1, INTEGER e2, Relations_tRelation Rel)
# else
(e1, e2, Rel)
INTEGER e1, e2;
Relations_tRelation Rel;
# endif
{
  return Sets_IsElement(e2, &Rel.ArrayPtr->A[e1]);
}

BOOLEAN Relations_IsReflexive1
# ifdef __STDC__
(INTEGER e1, Relations_tRelation Rel)
# else
(e1, Rel)
INTEGER e1;
Relations_tRelation Rel;
# endif
{
  return Sets_IsElement(e1, &Rel.ArrayPtr->A[e1]);
}

BOOLEAN Relations_IsSymmetric1
# ifdef __STDC__
(INTEGER e1, INTEGER e2, Relations_tRelation Rel)
# else
(e1, e2, Rel)
INTEGER e1, e2;
Relations_tRelation Rel;
# endif
{
  return !Sets_IsElement(e2, &Rel.ArrayPtr->A[e1]) || Sets_IsElement(e1, &Rel.ArrayPtr->A[e2]);
}

BOOLEAN Relations_IsTransitive1
# ifdef __STDC__
(INTEGER e1, INTEGER e2, INTEGER e3, Relations_tRelation Rel)
# else
(e1, e2, e3, Rel)
INTEGER e1, e2, e3;
Relations_tRelation Rel;
# endif
{
  return !(Sets_IsElement(e2, &Rel.ArrayPtr->A[e1]) && Sets_IsElement(e3, &Rel.ArrayPtr->A[e2])) || Sets_IsElement(e3, &Rel.ArrayPtr->A[e1]);
}

BOOLEAN Relations_IsReflexive
# ifdef __STDC__
(Relations_tRelation Rel)
# else
(Rel)
Relations_tRelation Rel;
# endif
{
  {
    LONGINT B_5 = 0, B_6 = Rel.Max1;

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        if (!Sets_IsElement(i, &Rel.ArrayPtr->A[i])) {
          return FALSE;
        }
        if (i >= B_6) break;
      }
  }
  return TRUE;
}

static BOOLEAN gSymmetric
# ifdef __STDC__
(Sets_tElement e)
# else
(e)
Sets_tElement e;
# endif
{
  return Sets_IsElement(i, &gRel.ArrayPtr->A[e]);
}

BOOLEAN Relations_IsSymmetric
# ifdef __STDC__
(Relations_tRelation Rel)
# else
(Rel)
Relations_tRelation Rel;
# endif
{
  gRel = Rel;
  {
    LONGINT B_7 = 0, B_8 = Rel.Max1;

    if (B_7 <= B_8)
      for (i = B_7;; i += 1) {
        if (!Sets_Forall(Rel.ArrayPtr->A[i], gSymmetric)) {
          return FALSE;
        }
        if (i >= B_8) break;
      }
  }
  return TRUE;
}

BOOLEAN Relations_IsTransitive
# ifdef __STDC__
(Relations_tRelation Rel)
# else
(Rel)
Relations_tRelation Rel;
# endif
{
  Relations_tRelation r;
  BOOLEAN Result;

  Relations_MakeRelation(&r, Rel.Max1, Rel.Max2);
  Relations_Assign(&r, Rel);
  Relations_Closure(&r);
  Result = Relations_IsEqual(&r, &Rel);
  Relations_ReleaseRelation(&r);
  return Result;
}

BOOLEAN Relations_IsEquivalence
# ifdef __STDC__
(Relations_tRelation Rel)
# else
(Rel)
Relations_tRelation Rel;
# endif
{
  return Relations_IsReflexive(Rel) && Relations_IsSymmetric(Rel) && Relations_IsTransitive(Rel);
}

BOOLEAN Relations_HasReflexive
# ifdef __STDC__
(Relations_tRelation Rel)
# else
(Rel)
Relations_tRelation Rel;
# endif
{
  {
    LONGINT B_9 = 0, B_10 = Rel.Max1;

    if (B_9 <= B_10)
      for (i = B_9;; i += 1) {
        if (Sets_IsElement(i, &Rel.ArrayPtr->A[i])) {
          return TRUE;
        }
        if (i >= B_10) break;
      }
  }
  return FALSE;
}

BOOLEAN Relations_IsCyclic
# ifdef __STDC__
(Relations_tRelation Rel)
# else
(Rel)
Relations_tRelation Rel;
# endif
{
  LONGINT PredCountSize;
  Sets_tSet WithPred;
  BOOLEAN Result;

  PredCountSize = VAL(LONGINT, Rel.Max1 + 1);
  DynArray_MakeArray(&PredCountPtr, &PredCountSize, sizeof(SHORTCARD));
  Sets_MakeSet(&WithoutPred, Rel.Max1);
  Sets_MakeSet(&WithPred, Rel.Max1);
  {
    LONGINT B_11 = 0, B_12 = Rel.Max1;

    if (B_11 <= B_12)
      for (i = B_11;; i += 1) {
        PredCountPtr->A[i] = 0;
        if (i >= B_12) break;
      }
  }
  {
    LONGINT B_13 = 0, B_14 = Rel.Max1;

    if (B_13 <= B_14)
      for (i = B_13;; i += 1) {
        Sets_ForallDo(Rel.ArrayPtr->A[i], gPredCount);
        if (i >= B_14) break;
      }
  }
  {
    LONGINT B_15 = 0, B_16 = Rel.Max1;

    if (B_15 <= B_16)
      for (i = B_15;; i += 1) {
        if (PredCountPtr->A[i] == 0) {
          Sets_Include(&WithoutPred, i);
        }
        if (i >= B_16) break;
      }
  }
  Sets_Complement(&WithPred);
  while (!Sets_IsEmpty(WithoutPred)) {
    i = Sets_Extract(&WithoutPred);
    Sets_Exclude(&WithPred, i);
    Sets_ForallDo(Rel.ArrayPtr->A[i], gPredCount2);
  }
  Result = !Sets_IsEmpty(WithPred);
  Sets_ReleaseSet(&WithoutPred);
  Sets_ReleaseSet(&WithPred);
  DynArray_ReleaseArray(&PredCountPtr, &PredCountSize, sizeof(SHORTCARD));
  return Result;
}

static void gPredCount
# ifdef __STDC__
(Sets_tElement e)
# else
(e)
Sets_tElement e;
# endif
{
  INC(PredCountPtr->A[e]);
}

static void gPredCount2
# ifdef __STDC__
(Sets_tElement e)
# else
(e)
Sets_tElement e;
# endif
{
  DEC(PredCountPtr->A[e]);
  if (PredCountPtr->A[e] == 0) {
    Sets_Include(&WithoutPred, e);
  }
}

void Relations_GetCyclics
# ifdef __STDC__
(Relations_tRelation Rel, Sets_tSet *Set)
# else
(Rel, Set)
Relations_tRelation Rel;
Sets_tSet *Set;
# endif
{
  Relations_tRelation r;

  Relations_MakeRelation(&r, Rel.Max1, Rel.Max2);
  Relations_Assign(&r, Rel);
  Relations_Closure(&r);
  Sets_AssignEmpty(Set);
  {
    LONGINT B_17 = 0, B_18 = r.Max1;

    if (B_17 <= B_18)
      for (i = B_17;; i += 1) {
        if (Sets_IsElement(VAL(CARDINAL, i), &r.ArrayPtr->A[i])) {
          Sets_Include(Set, VAL(INTEGER, i));
        }
        if (i >= B_18) break;
      }
  }
  Relations_ReleaseRelation(&r);
}

void Relations_AssignEmpty
# ifdef __STDC__
(Relations_tRelation *Rel)
# else
(Rel)
Relations_tRelation *Rel;
# endif
{
  {
    LONGINT B_19 = 0, B_20 = Rel->Max1;

    if (B_19 <= B_20)
      for (i = B_19;; i += 1) {
        Sets_AssignEmpty(&Rel->ArrayPtr->A[i]);
        if (i >= B_20) break;
      }
  }
}

void Relations_AssignElmt
# ifdef __STDC__
(Relations_tRelation *Rel, INTEGER e1, INTEGER e2)
# else
(Rel, e1, e2)
Relations_tRelation *Rel;
INTEGER e1, e2;
# endif
{
  Relations_AssignEmpty(Rel);
  Relations_Include(Rel, e1, e2);
}

void Relations_Assign
# ifdef __STDC__
(Relations_tRelation *Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation *Rel1;
Relations_tRelation Rel2;
# endif
{
  {
    LONGINT B_21 = 0, B_22 = Rel1->Max1;

    if (B_21 <= B_22)
      for (i = B_21;; i += 1) {
        Sets_Assign(&Rel1->ArrayPtr->A[i], Rel2.ArrayPtr->A[i]);
        if (i >= B_22) break;
      }
  }
}

void Relations_Closure
# ifdef __STDC__
(Relations_tRelation *Rel)
# else
(Rel)
Relations_tRelation *Rel;
# endif
{
  Sets_tSet aj;

  {
    register Relations_tRelation *W_1 = Rel;

    {
      LONGINT B_23 = 0, B_24 = W_1->Max1;

      if (B_23 <= B_24)
        for (j = B_23;; j += 1) {
          if (!Sets_IsEmpty(W_1->ArrayPtr->A[j])) {
            aj = W_1->ArrayPtr->A[j];
            {
              LONGINT B_25 = 0, B_26 = W_1->Max1;

              if (B_25 <= B_26)
                for (i = B_25;; i += 1) {
                  if (Sets_IsElement(VAL(CARDINAL, j), &W_1->ArrayPtr->A[i])) {
                    Sets_Union(&W_1->ArrayPtr->A[i], aj);
                  }
                  if (i >= B_26) break;
                }
            }
          }
          if (j >= B_24) break;
        }
    }
  }
}

void Relations_Union
# ifdef __STDC__
(Relations_tRelation *Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation *Rel1;
Relations_tRelation Rel2;
# endif
{
  {
    LONGINT B_27 = 0, B_28 = Rel1->Max1;

    if (B_27 <= B_28)
      for (i = B_27;; i += 1) {
        Sets_Union(&Rel1->ArrayPtr->A[i], Rel2.ArrayPtr->A[i]);
        if (i >= B_28) break;
      }
  }
}

void Relations_Difference
# ifdef __STDC__
(Relations_tRelation *Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation *Rel1;
Relations_tRelation Rel2;
# endif
{
  {
    LONGINT B_29 = 0, B_30 = Rel1->Max1;

    if (B_29 <= B_30)
      for (i = B_29;; i += 1) {
        Sets_Difference(&Rel1->ArrayPtr->A[i], Rel2.ArrayPtr->A[i]);
        if (i >= B_30) break;
      }
  }
}

void Relations_Intersection
# ifdef __STDC__
(Relations_tRelation *Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation *Rel1;
Relations_tRelation Rel2;
# endif
{
  {
    LONGINT B_31 = 0, B_32 = Rel1->Max1;

    if (B_31 <= B_32)
      for (i = B_31;; i += 1) {
        Sets_Intersection(&Rel1->ArrayPtr->A[i], Rel2.ArrayPtr->A[i]);
        if (i >= B_32) break;
      }
  }
}

void Relations_SymDiff
# ifdef __STDC__
(Relations_tRelation *Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation *Rel1;
Relations_tRelation Rel2;
# endif
{
  {
    LONGINT B_33 = 0, B_34 = Rel1->Max1;

    if (B_33 <= B_34)
      for (i = B_33;; i += 1) {
        Sets_SymDiff(&Rel1->ArrayPtr->A[i], Rel2.ArrayPtr->A[i]);
        if (i >= B_34) break;
      }
  }
}

void Relations_Complement
# ifdef __STDC__
(Relations_tRelation *Rel)
# else
(Rel)
Relations_tRelation *Rel;
# endif
{
  {
    LONGINT B_35 = 0, B_36 = Rel->Max1;

    if (B_35 <= B_36)
      for (i = B_35;; i += 1) {
        Sets_Complement(&Rel->ArrayPtr->A[i]);
        if (i >= B_36) break;
      }
  }
}

BOOLEAN Relations_IsSubset
# ifdef __STDC__
(Relations_tRelation Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation Rel1, Rel2;
# endif
{
  {
    LONGINT B_37 = 0, B_38 = Rel1.Max1;

    if (B_37 <= B_38)
      for (i = B_37;; i += 1) {
        if (!Sets_IsSubset(Rel1.ArrayPtr->A[i], Rel2.ArrayPtr->A[i])) {
          return FALSE;
        }
        if (i >= B_38) break;
      }
  }
  return TRUE;
}

BOOLEAN Relations_IsStrictSubset
# ifdef __STDC__
(Relations_tRelation Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation Rel1, Rel2;
# endif
{
  return Relations_IsSubset(Rel1, Rel2) && Relations_IsNotEqual(Rel1, Rel2);
}

BOOLEAN Relations_IsEqual
# ifdef __STDC__
(Relations_tRelation *Rel1, Relations_tRelation *Rel2)
# else
(Rel1, Rel2)
Relations_tRelation *Rel1, *Rel2;
# endif
{
  {
    LONGINT B_39 = 0, B_40 = Rel1->Max1;

    if (B_39 <= B_40)
      for (i = B_39;; i += 1) {
        if (!Sets_IsEqual(&Rel1->ArrayPtr->A[i], &Rel2->ArrayPtr->A[i])) {
          return FALSE;
        }
        if (i >= B_40) break;
      }
  }
  return TRUE;
}

BOOLEAN Relations_IsNotEqual
# ifdef __STDC__
(Relations_tRelation Rel1, Relations_tRelation Rel2)
# else
(Rel1, Rel2)
Relations_tRelation Rel1, Rel2;
# endif
{
  return !Relations_IsEqual(&Rel1, &Rel2);
}

BOOLEAN Relations_IsEmpty
# ifdef __STDC__
(Relations_tRelation Rel)
# else
(Rel)
Relations_tRelation Rel;
# endif
{
  {
    LONGINT B_41 = 0, B_42 = Rel.Max1;

    if (B_41 <= B_42)
      for (i = B_41;; i += 1) {
        if (!Sets_IsEmpty(Rel.ArrayPtr->A[i])) {
          return FALSE;
        }
        if (i >= B_42) break;
      }
  }
  return TRUE;
}

INTEGER Relations_Card
# ifdef __STDC__
(Relations_tRelation *Rel)
# else
(Rel)
Relations_tRelation *Rel;
# endif
{
  INTEGER n;

  n = 0;
  {
    LONGINT B_43 = 0, B_44 = Rel->Max1;

    if (B_43 <= B_44)
      for (i = B_43;; i += 1) {
        INC1(n, Sets_Card(&Rel->ArrayPtr->A[i]));
        if (i >= B_44) break;
      }
  }
  return n;
}

void Relations_Select
# ifdef __STDC__
(Relations_tRelation *Rel, INTEGER *e1, INTEGER *e2)
# else
(Rel, e1, e2)
Relations_tRelation *Rel;
INTEGER *e1, *e2;
# endif
{
  {
    LONGINT B_45 = 0, B_46 = Rel->Max1;

    if (B_45 <= B_46)
      for (i = B_45;; i += 1) {
        if (!Sets_IsEmpty(Rel->ArrayPtr->A[i])) {
          *e1 = VAL(INTEGER, i);
          *e2 = Sets_Select(&Rel->ArrayPtr->A[i]);
          return;
        }
        if (i >= B_46) break;
      }
  }
  *e1 = 0;
  *e2 = 0;
}

void Relations_Extract
# ifdef __STDC__
(Relations_tRelation *Rel, INTEGER *e1, INTEGER *e2)
# else
(Rel, e1, e2)
Relations_tRelation *Rel;
INTEGER *e1, *e2;
# endif
{
  Relations_Select(Rel, e1, e2);
  Relations_Exclude(Rel, *e1, *e2);
}

static BOOLEAN gProc1b
# ifdef __STDC__
(Sets_tElement e)
# else
(e)
Sets_tElement e;
# endif
{
  return (*gProc2b)(VAL(INTEGER, i), e);
}

BOOLEAN Relations_Forall
# ifdef __STDC__
(Relations_tRelation Rel, Relations_ProcOfIntIntToBool Proc)
# else
(Rel, Proc)
Relations_tRelation Rel;
Relations_ProcOfIntIntToBool Proc;
# endif
{
  gProc2b = Proc;
  {
    LONGINT B_47 = 0, B_48 = Rel.Max1;

    if (B_47 <= B_48)
      for (i = B_47;; i += 1) {
        if (!Sets_Forall(Rel.ArrayPtr->A[i], gProc1b)) {
          return FALSE;
        }
        if (i >= B_48) break;
      }
  }
  return TRUE;
}

BOOLEAN Relations_Exists
# ifdef __STDC__
(Relations_tRelation Rel, Relations_ProcOfIntIntToBool Proc)
# else
(Rel, Proc)
Relations_tRelation Rel;
Relations_ProcOfIntIntToBool Proc;
# endif
{
  gProc2b = Proc;
  {
    LONGINT B_49 = 0, B_50 = Rel.Max1;

    if (B_49 <= B_50)
      for (i = B_49;; i += 1) {
        if (Sets_Exists(Rel.ArrayPtr->A[i], gProc1b)) {
          return TRUE;
        }
        if (i >= B_50) break;
      }
  }
  return FALSE;
}

BOOLEAN Relations_Exists1
# ifdef __STDC__
(Relations_tRelation Rel, Relations_ProcOfIntIntToBool Proc)
# else
(Rel, Proc)
Relations_tRelation Rel;
Relations_ProcOfIntIntToBool Proc;
# endif
{
  INTEGER n;

  n = 0;
  gProc2b = Proc;
  {
    LONGINT B_51 = 0, B_52 = Rel.Max1;

    if (B_51 <= B_52)
      for (i = B_51;; i += 1) {
        if (Sets_Exists(Rel.ArrayPtr->A[i], gProc1b)) {
          INC(n);
        }
        if (i >= B_52) break;
      }
  }
  return n == 1;
}

static void gProc1
# ifdef __STDC__
(Sets_tElement e)
# else
(e)
Sets_tElement e;
# endif
{
  (*gProc2)(VAL(INTEGER, i), e);
}

void Relations_ForallDo
# ifdef __STDC__
(Relations_tRelation Rel, Relations_ProcOfIntInt Proc)
# else
(Rel, Proc)
Relations_tRelation Rel;
Relations_ProcOfIntInt Proc;
# endif
{
  gProc2 = Proc;
  {
    LONGINT B_53 = 0, B_54 = Rel.Max1;

    if (B_53 <= B_54)
      for (i = B_53;; i += 1) {
        Sets_ForallDo(Rel.ArrayPtr->A[i], gProc1);
        if (i >= B_54) break;
      }
  }
}

void Relations_ReadRelation
# ifdef __STDC__
(IO_tFile f, Relations_tRelation *Rel)
# else
(f, Rel)
IO_tFile f;
Relations_tRelation *Rel;
# endif
{
  CHAR ch;
  INTEGER i;

  do {
  } while (!(IO_ReadC(f) == '{'));
  Relations_AssignEmpty(Rel);
  for (;;) {
    if (IO_ReadC(f) == '}') {
      goto EXIT_1;
    }
    i = IO_ReadI(f);
    Relations_Include(Rel, i, IO_ReadI(f));
    ch = IO_ReadC(f);
  } EXIT_1:;
}

void Relations_WriteRelation
# ifdef __STDC__
(IO_tFile f, Relations_tRelation Rel)
# else
(f, Rel)
IO_tFile f;
Relations_tRelation Rel;
# endif
{
  g = f;
  IO_WriteC(f, '{');
  Relations_ForallDo(Rel, WritePair);
  IO_WriteC(f, '}');
}

static void WritePair
# ifdef __STDC__
(INTEGER e1, INTEGER e2)
# else
(e1, e2)
INTEGER e1, e2;
# endif
{
  IO_WriteC(g, ' ');
  IO_WriteI(g, e1, 1);
  IO_WriteC(g, ' ');
  IO_WriteI(g, e2, 1);
  IO_WriteC(g, ',');
}

void Relations__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Sets__init();
    IO__init();
    DynArray__init();
    Sets__init();
    Sets__init();

  }
}
