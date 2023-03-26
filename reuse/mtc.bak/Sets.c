#include "SYSTEM_.h"

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif


#define BitsPerBitset   32
#define BitsPerByte   8
#define BytesPerBitset   (BitsPerBitset / BitsPerByte)
#define NoCard   MAX_SHORTCARD
static BITSET AllBits;
static IO_tFile g;
static void WriteElmt ARGS((Sets_tElement Elmt));


void Sets_InitNullSet
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  {
    register Sets_tSet *W_1 = Set;

    W_1->MaxElmt = 0;
    W_1->LastBitset = 0;
    W_1->Card = 0;
    W_1->FirstElmt = 0;
    W_1->LastElmt = 0;
    W_1->BitsetPtr = NIL;
  }
}

void Sets_MakeSet
# ifdef __STDC__
(Sets_tSet *Set, Sets_tElement MaxElement)
# else
(Set, MaxElement)
Sets_tSet *Set;
Sets_tElement MaxElement;
# endif
{
  LONGINT BitsetCount;

  {
    register Sets_tSet *W_2 = Set;

    BitsetCount = VAL(LONGINT, (MaxElement + BitsPerBitset - MaxElement % BitsPerBitset) / BitsPerBitset);
    DynArray_MakeArray(&W_2->BitsetPtr, &BitsetCount, BytesPerBitset);
    W_2->MaxElmt = VAL(Sets_tInternalElmt, MaxElement);
    W_2->LastBitset = VAL(SHORTCARD, BitsetCount - 1);
    Sets_AssignEmpty(Set);
  }
}

void Sets_ReleaseSet
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  LONGINT BitsetCount;

  BitsetCount = VAL(LONGINT, Set->LastBitset + 1);
  DynArray_ReleaseArray(&Set->BitsetPtr, &BitsetCount, BytesPerBitset);
  Sets_InitNullSet(Set);
}

void Sets_Union
# ifdef __STDC__
(Sets_tSet *Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet *Set1;
Sets_tSet Set2;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_3 = Set1;

    i = 0;
    while (i <= W_3->LastBitset) {
      W_3->BitsetPtr->A[i] = W_3->BitsetPtr->A[i] | Set2.BitsetPtr->A[i];
      INC(i);
    }
    W_3->Card = VAL(Sets_tInternalElmt, NoCard);
    W_3->FirstElmt = General_MinSHORTCARD(W_3->FirstElmt, Set2.FirstElmt);
    W_3->LastElmt = General_MaxSHORTCARD(W_3->LastElmt, Set2.LastElmt);
  }
}

void Sets_Difference
# ifdef __STDC__
(Sets_tSet *Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet *Set1;
Sets_tSet Set2;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_4 = Set1;

    i = 0;
    while (i <= W_4->LastBitset) {
      W_4->BitsetPtr->A[i] = SET_DIFF(W_4->BitsetPtr->A[i], Set2.BitsetPtr->A[i]);
      INC(i);
    }
    W_4->Card = VAL(Sets_tInternalElmt, NoCard);
  }
}

void Sets_Intersection
# ifdef __STDC__
(Sets_tSet *Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet *Set1;
Sets_tSet Set2;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_5 = Set1;

    i = 0;
    while (i <= W_5->LastBitset) {
      W_5->BitsetPtr->A[i] = W_5->BitsetPtr->A[i] & Set2.BitsetPtr->A[i];
      INC(i);
    }
    W_5->Card = VAL(Sets_tInternalElmt, NoCard);
    W_5->FirstElmt = General_MaxSHORTCARD(W_5->FirstElmt, Set2.FirstElmt);
    W_5->LastElmt = General_MinSHORTCARD(W_5->LastElmt, Set2.LastElmt);
  }
}

void Sets_SymDiff
# ifdef __STDC__
(Sets_tSet *Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet *Set1;
Sets_tSet Set2;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_6 = Set1;

    i = 0;
    while (i <= W_6->LastBitset) {
      W_6->BitsetPtr->A[i] = W_6->BitsetPtr->A[i] ^ Set2.BitsetPtr->A[i];
      INC(i);
    }
    W_6->Card = VAL(Sets_tInternalElmt, NoCard);
    W_6->FirstElmt = General_MinSHORTCARD(W_6->FirstElmt, Set2.FirstElmt);
    W_6->LastElmt = General_MaxSHORTCARD(W_6->LastElmt, Set2.LastElmt);
  }
}

void Sets_Complement
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_7 = Set;

    i = 0;
    while (i < W_7->LastBitset) {
      W_7->BitsetPtr->A[i] = SET_DIFF(AllBits, W_7->BitsetPtr->A[i]);
      INC(i);
    }
    W_7->BitsetPtr->A[W_7->LastBitset] = SET_DIFF(SET_RANGE(0, W_7->MaxElmt % BitsPerBitset), W_7->BitsetPtr->A[W_7->LastBitset]);
    if (W_7->Card != VAL(Sets_tInternalElmt, NoCard)) {
      W_7->Card = W_7->MaxElmt + 1 - W_7->Card;
    }
    W_7->FirstElmt = 0;
    W_7->LastElmt = W_7->MaxElmt;
  }
}

void Sets_Include
# ifdef __STDC__
(Sets_tSet *Set, Sets_tElement Elmt)
# else
(Set, Elmt)
Sets_tSet *Set;
Sets_tElement Elmt;
# endif
{
  {
    register Sets_tSet *W_8 = Set;

    INCL(W_8->BitsetPtr->A[VAL(SHORTCARD, Elmt / BitsPerBitset)], Elmt % BitsPerBitset);
    W_8->Card = VAL(Sets_tInternalElmt, NoCard);
    if (W_8->FirstElmt > VAL(Sets_tInternalElmt, Elmt)) {
      W_8->FirstElmt = VAL(Sets_tInternalElmt, Elmt);
    }
    if (W_8->LastElmt < VAL(Sets_tInternalElmt, Elmt)) {
      W_8->LastElmt = VAL(Sets_tInternalElmt, Elmt);
    }
  }
}

void Sets_Exclude
# ifdef __STDC__
(Sets_tSet *Set, Sets_tElement Elmt)
# else
(Set, Elmt)
Sets_tSet *Set;
Sets_tElement Elmt;
# endif
{
  {
    register Sets_tSet *W_9 = Set;

    EXCL(W_9->BitsetPtr->A[VAL(SHORTCARD, Elmt / BitsPerBitset)], Elmt % BitsPerBitset);
    W_9->Card = VAL(Sets_tInternalElmt, NoCard);
    if (VAL(Sets_tInternalElmt, Elmt) == W_9->FirstElmt && VAL(Sets_tInternalElmt, Elmt) < W_9->MaxElmt) {
      INC(W_9->FirstElmt);
    }
    if (VAL(Sets_tInternalElmt, Elmt) == W_9->LastElmt && Elmt > 0) {
      DEC(W_9->LastElmt);
    }
  }
}

Sets_tElement Sets_Card
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  Sets_tInternalElmt i;

  {
    register Sets_tSet *W_10 = Set;

    if (W_10->Card == VAL(Sets_tInternalElmt, NoCard)) {
      W_10->Card = 0;
      {
        SHORTCARD B_1 = W_10->FirstElmt, B_2 = W_10->LastElmt;

        if (B_1 <= B_2)
          for (i = B_1;; i += 1) {
            if (Sets_IsElement(VAL(Sets_tElement, i), Set)) {
              INC(W_10->Card);
            }
            if (i >= B_2) break;
          }
      }
    }
    return VAL(Sets_tElement, W_10->Card);
  }
}

Sets_tElement Sets_Size
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  return VAL(Sets_tElement, Set->MaxElmt);
}

Sets_tElement Sets_Minimum
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  Sets_tInternalElmt i;

  {
    register Sets_tSet *W_11 = Set;

    i = W_11->FirstElmt;
    while (i <= W_11->LastElmt) {
      if (Sets_IsElement(VAL(Sets_tElement, i), Set)) {
        W_11->FirstElmt = i;
        return VAL(Sets_tElement, i);
      }
      INC(i);
    }
    return 0;
  }
}

Sets_tElement Sets_Maximum
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  Sets_tInternalElmt i;

  {
    register Sets_tSet *W_12 = Set;

    i = W_12->LastElmt;
    while (i >= W_12->FirstElmt) {
      if (Sets_IsElement(VAL(Sets_tElement, i), Set)) {
        W_12->LastElmt = i;
        return VAL(Sets_tElement, i);
      }
      DEC(i);
    }
    return 0;
  }
}

Sets_tElement Sets_Select
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  return Sets_Minimum(Set);
}

Sets_tElement Sets_Extract
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  Sets_tElement i;

  i = Sets_Minimum(Set);
  Sets_Exclude(Set, i);
  return i;
}

BOOLEAN Sets_IsSubset
# ifdef __STDC__
(Sets_tSet Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet Set1, Set2;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_13 = &Set1;

    i = 0;
    while (i <= W_13->LastBitset) {
      if (!SET_IS_SUBSET1(W_13->BitsetPtr->A[i], Set2.BitsetPtr->A[i])) {
        return FALSE;
      }
      INC(i);
    }
    return TRUE;
  }
}

BOOLEAN Sets_IsStrictSubset
# ifdef __STDC__
(Sets_tSet Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet Set1, Set2;
# endif
{
  return Sets_IsSubset(Set1, Set2) && Sets_IsNotEqual(Set1, Set2);
}

BOOLEAN Sets_IsEqual
# ifdef __STDC__
(Sets_tSet *Set1, Sets_tSet *Set2)
# else
(Set1, Set2)
Sets_tSet *Set1, *Set2;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_14 = Set1;

    i = 0;
    while (i <= W_14->LastBitset) {
      if (W_14->BitsetPtr->A[i] != Set2->BitsetPtr->A[i]) {
        return FALSE;
      }
      INC(i);
    }
    return TRUE;
  }
}

BOOLEAN Sets_IsNotEqual
# ifdef __STDC__
(Sets_tSet Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet Set1, Set2;
# endif
{
  return !Sets_IsEqual(&Set1, &Set2);
}

BOOLEAN Sets_IsElement
# ifdef __STDC__
(Sets_tElement Elmt, Sets_tSet *Set)
# else
(Elmt, Set)
Sets_tElement Elmt;
Sets_tSet *Set;
# endif
{
  if (Set->BitsetPtr == NIL) {
    return FALSE;
  } else {
    return IN(Elmt % BitsPerBitset, Set->BitsetPtr->A[VAL(SHORTCARD, Elmt / BitsPerBitset)]);
  }
}

BOOLEAN Sets_IsEmpty
# ifdef __STDC__
(Sets_tSet Set)
# else
(Set)
Sets_tSet Set;
# endif
{
  SHORTCARD i;
  BITSET b;

  {
    register Sets_tSet *W_15 = &Set;

    if (W_15->FirstElmt <= W_15->LastElmt) {
      i = 0;
      while (i <= W_15->LastBitset) {
        b = W_15->BitsetPtr->A[i];
        if (W_15->BitsetPtr->A[i] != 0X0L) {
          return FALSE;
        }
        INC(i);
      }
    }
    return TRUE;
  }
}

BOOLEAN Sets_Forall
# ifdef __STDC__
(Sets_tSet Set, Sets_ProcOftElementToBool Proc)
# else
(Set, Proc)
Sets_tSet Set;
Sets_ProcOftElementToBool Proc;
# endif
{
  Sets_tInternalElmt i;

  {
    register Sets_tSet *W_16 = &Set;

    {
      SHORTCARD B_3 = W_16->FirstElmt, B_4 = W_16->LastElmt;

      if (B_3 <= B_4)
        for (i = B_3;; i += 1) {
          if (Sets_IsElement(VAL(Sets_tElement, i), &Set) && !(*Proc)(VAL(Sets_tElement, i))) {
            return FALSE;
          }
          if (i >= B_4) break;
        }
    }
    return TRUE;
  }
}

BOOLEAN Sets_Exists
# ifdef __STDC__
(Sets_tSet Set, Sets_ProcOftElementToBool Proc)
# else
(Set, Proc)
Sets_tSet Set;
Sets_ProcOftElementToBool Proc;
# endif
{
  Sets_tInternalElmt i;

  {
    register Sets_tSet *W_17 = &Set;

    {
      SHORTCARD B_5 = W_17->FirstElmt, B_6 = W_17->LastElmt;

      if (B_5 <= B_6)
        for (i = B_5;; i += 1) {
          if (Sets_IsElement(VAL(Sets_tElement, i), &Set) && (*Proc)(VAL(Sets_tElement, i))) {
            return TRUE;
          }
          if (i >= B_6) break;
        }
    }
    return FALSE;
  }
}

BOOLEAN Sets_Exists1
# ifdef __STDC__
(Sets_tSet Set, Sets_ProcOftElementToBool Proc)
# else
(Set, Proc)
Sets_tSet Set;
Sets_ProcOftElementToBool Proc;
# endif
{
  Sets_tInternalElmt i, n;

  {
    register Sets_tSet *W_18 = &Set;

    n = 0;
    {
      SHORTCARD B_7 = W_18->FirstElmt, B_8 = W_18->LastElmt;

      if (B_7 <= B_8)
        for (i = B_7;; i += 1) {
          if (Sets_IsElement(VAL(Sets_tElement, i), &Set) && (*Proc)(VAL(Sets_tElement, i))) {
            INC(n);
          }
          if (i >= B_8) break;
        }
    }
    return n == 1;
  }
}

void Sets_Assign
# ifdef __STDC__
(Sets_tSet *Set1, Sets_tSet Set2)
# else
(Set1, Set2)
Sets_tSet *Set1;
Sets_tSet Set2;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_19 = Set1;

    i = 0;
    while (i <= W_19->LastBitset) {
      W_19->BitsetPtr->A[i] = Set2.BitsetPtr->A[i];
      INC(i);
    }
    W_19->Card = Set2.Card;
    W_19->FirstElmt = Set2.FirstElmt;
    W_19->LastElmt = Set2.LastElmt;
  }
}

void Sets_AssignElmt
# ifdef __STDC__
(Sets_tSet *Set, Sets_tElement Elmt)
# else
(Set, Elmt)
Sets_tSet *Set;
Sets_tElement Elmt;
# endif
{
  {
    register Sets_tSet *W_20 = Set;

    Sets_AssignEmpty(Set);
    Sets_Include(Set, Elmt);
    W_20->Card = 1;
    W_20->FirstElmt = VAL(Sets_tInternalElmt, Elmt);
    W_20->LastElmt = VAL(Sets_tInternalElmt, Elmt);
  }
}

void Sets_AssignEmpty
# ifdef __STDC__
(Sets_tSet *Set)
# else
(Set)
Sets_tSet *Set;
# endif
{
  SHORTCARD i;

  {
    register Sets_tSet *W_21 = Set;

    i = 0;
    while (i <= W_21->LastBitset) {
      W_21->BitsetPtr->A[i] = 0X0L;
      INC(i);
    }
    W_21->Card = 0;
    W_21->FirstElmt = W_21->MaxElmt;
    W_21->LastElmt = 0;
  }
}

void Sets_ForallDo
# ifdef __STDC__
(Sets_tSet Set, Sets_ProcOftElement Proc)
# else
(Set, Proc)
Sets_tSet Set;
Sets_ProcOftElement Proc;
# endif
{
  Sets_tInternalElmt i;

  {
    register Sets_tSet *W_22 = &Set;

    if (W_22->BitsetPtr != NIL) {
      {
        SHORTCARD B_9 = W_22->FirstElmt, B_10 = W_22->LastElmt;

        if (B_9 <= B_10)
          for (i = B_9;; i += 1) {
            if (Sets_IsElement(VAL(Sets_tElement, i), &Set)) {
              (*Proc)(VAL(Sets_tElement, i));
            }
            if (i >= B_10) break;
          }
      }
    }
  }
}

void Sets_ReadSet
# ifdef __STDC__
(IO_tFile f, Sets_tSet *Set)
# else
(f, Set)
IO_tFile f;
Sets_tSet *Set;
# endif
{
  Sets_tInternalElmt card;

  do {
  } while (!(IO_ReadC(f) == '{'));
  Sets_AssignEmpty(Set);
  card = 0;
  for (;;) {
    if (IO_ReadC(f) == '}') {
      goto EXIT_1;
    }
    Sets_Include(Set, IO_ReadCard(f));
    INC(card);
  } EXIT_1:;
  Set->Card = card;
}

void Sets_WriteSet
# ifdef __STDC__
(IO_tFile f, Sets_tSet Set)
# else
(f, Set)
IO_tFile f;
Sets_tSet Set;
# endif
{
  {
    register Sets_tSet *W_23 = &Set;

    g = f;
    IO_WriteC(f, '{');
    Sets_ForallDo(Set, WriteElmt);
    IO_WriteC(f, '}');
  }
}

static void WriteElmt
# ifdef __STDC__
(Sets_tElement Elmt)
# else
(Elmt)
Sets_tElement Elmt;
# endif
{
  IO_WriteC(g, ' ');
  IO_WriteCard(g, Elmt, 0);
}

void Sets__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    General__init();
    DynArray__init();
    IO__init();

    AllBits = SET_cRNG(0, BitsPerBitset - 1);
    if (sizeof(BITSET) != BytesPerBitset) {
      IO_WriteS(IO_StdError, "TSIZE (BITSET) = ", 17L);
      IO_WriteCard(IO_StdError, sizeof(BITSET), 0);
      IO_WriteNl(IO_StdError);
    }
  }
}
