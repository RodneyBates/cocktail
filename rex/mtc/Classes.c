#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree0
#include "Tree0.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_Classes
#include "Classes.h"
#endif

Sets_tSet Classes_CharSet, Classes_Unused;
struct Classes_2 Classes_ToClass, Classes_ToChar;
struct Classes_3 *Classes_SetMemPtr;
LONGINT Classes_SetMemSize;
INTEGER Classes_SetCount;
struct Classes_4 *Classes_ClassMemPtr;
LONGINT Classes_ClassMemSize;
CHAR Classes_ClassCount;

static void CollectSets ARGS((Tree0_tTree0 t));
static CHAR Class;
static void CharToClass0 ARGS((Sets_tElement Ch));
static void CharToClass ARGS((Sets_tElement Ch));


INTEGER Classes_IsInSetMem
# ifdef __STDC__
(Sets_tSet Set)
# else
(Set)
Sets_tSet Set;
# endif
{
  INTEGER i;

  {
    LONGINT B_1 = 1, B_2 = Classes_SetCount;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        if (Sets_IsEqual(&Set, &Classes_SetMemPtr->A[i].Set)) {
          return i;
        }
        if (i >= B_2) break;
      }
  }
  return 0;
}

static void CollectSets
# ifdef __STDC__
(Tree0_tTree0 t)
# else
(t)
Tree0_tTree0 t;
# endif
{
  CARDINAL i;
  Strings_tString string;

  switch (t->U_1.V_1.Kind) {
  case Tree0_Ch:;
    Sets_Include(&Classes_CharSet, ORD(t->U_1.V_11.Ch.Ch));
    break;
  case Tree0_Set:;
    if (Classes_IsInSetMem(t->U_1.V_12.Set.Set) == 0) {
      INC(Classes_SetCount);
      if (Classes_SetCount == Classes_SetMemSize) {
        DynArray_ExtendArray((ADDRESS *)&Classes_SetMemPtr, &Classes_SetMemSize, (LONGINT)sizeof(Classes_ClassInfo));
      }
      Sets_MakeSet(&Classes_SetMemPtr->A[Classes_SetCount].Set, ORD(Dfa_LastCh));
      Sets_Assign(&Classes_SetMemPtr->A[Classes_SetCount].Set, t->U_1.V_12.Set.Set);
      Sets_Union(&Classes_Unused, t->U_1.V_12.Set.Set);
    }
    break;
  case Tree0_String:;
    StringMem_GetString(t->U_1.V_13.String.String, &string);
    for (i = Strings_Length(&string); i >= 1; i += -1) {
      Sets_Include(&Classes_CharSet, ORD(Strings_Char(&string, (Strings_tStringIndex)i)));
    }
    break;
  default :
    break;
  }
}

static void CharToClass0
# ifdef __STDC__
(Sets_tElement Ch)
# else
(Ch)
Sets_tElement Ch;
# endif
{
  Classes_ToClass.A[CHR(Ch)] = Class;
}

static void CharToClass
# ifdef __STDC__
(Sets_tElement Ch)
# else
(Ch)
Sets_tElement Ch;
# endif
{
  INC(Dfa_LastCh);
  Classes_ToClass.A[CHR(Ch)] = Dfa_LastCh;
  Classes_ToChar.A[Dfa_LastCh] = CHR(Ch);
}

void Classes_ComputeClasses
# ifdef __STDC__
(BOOLEAN Blocking)
# else
(Blocking)
BOOLEAN Blocking;
# endif
{
  INTEGER i;
  CHAR j;
  Sets_tSet Set;

  Dfa_OldLastCh = Dfa_LastCh;
  Sets_MakeSet(&Classes_CharSet, ORD(Dfa_LastCh));
  Sets_MakeSet(&Classes_Unused, ORD(Dfa_LastCh));
  if (Blocking) {
    Tree0_TraverseTree0TD(Tree0_Tree0Root, (Tree0_tProcTree)CollectSets);
    Sets_Include(&Classes_CharSet, ORD(Dfa_EobCh));
    Sets_Union(&Classes_Unused, Classes_CharSet);
    Sets_Complement(&Classes_Unused);
  } else {
    Sets_Include(&Classes_CharSet, ORD(Dfa_FirstCh));
    Sets_Complement(&Classes_CharSet);
  }
  Classes_ClassCount = '\0';
  Sets_MakeSet(&Classes_ClassMemPtr->A['\0'], ORD(Dfa_LastCh));
  Sets_Assign(&Classes_ClassMemPtr->A['\0'], Classes_CharSet);
  Sets_Union(&Classes_ClassMemPtr->A['\0'], Classes_Unused);
  Sets_Complement(&Classes_ClassMemPtr->A['\0']);
  Sets_MakeSet(&Set, ORD(Dfa_LastCh));
  {
    LONGINT B_3 = 1, B_4 = Classes_SetCount;

    if (B_3 <= B_4)
      for (i = B_3;; i += 1) {
        {
          CHAR B_5 = '\0', B_6 = Classes_ClassCount;

          if (B_5 <= B_6)
            for (j = B_5;; j += 1) {
              Sets_Assign(&Set, Classes_SetMemPtr->A[i].Set);
              Sets_Difference(&Set, Classes_CharSet);
              Sets_Intersection(&Set, Classes_ClassMemPtr->A[j]);
              if (!Sets_IsEmpty(Set) && !Sets_IsEqual(&Set, &Classes_ClassMemPtr->A[j])) {
                INC(Classes_ClassCount);
                if (ORD(Classes_ClassCount) == (CARDINAL)Classes_ClassMemSize) {
                  DynArray_ExtendArray((ADDRESS *)&Classes_ClassMemPtr, &Classes_ClassMemSize, (LONGINT)sizeof(Sets_tSet));
                }
                Sets_MakeSet(&Classes_ClassMemPtr->A[Classes_ClassCount], ORD(Dfa_LastCh));
                Sets_Assign(&Classes_ClassMemPtr->A[Classes_ClassCount], Set);
                Sets_Difference(&Classes_ClassMemPtr->A[j], Set);
              }
              if (j >= B_6) break;
            }
        }
        if (i >= B_4) break;
      }
  }
  Sets_ReleaseSet(&Set);
  {
    LONGINT B_7 = 1, B_8 = Classes_SetCount;

    if (B_7 <= B_8)
      for (i = B_7;; i += 1) {
        Sets_MakeSet(&Classes_SetMemPtr->A[i].Classes, ORD(Classes_ClassCount));
        {
          CHAR B_9 = '\0', B_10 = Classes_ClassCount;

          if (B_9 <= B_10)
            for (j = B_9;; j += 1) {
              if (Sets_IsSubset(Classes_ClassMemPtr->A[j], Classes_SetMemPtr->A[i].Set)) {
                Sets_Include(&Classes_SetMemPtr->A[i].Classes, ORD(j));
              }
              if (j >= B_10) break;
            }
        }
        if (i >= B_8) break;
      }
  }
  {
    CHAR B_11 = '\0', B_12 = Classes_ClassCount;

    if (B_11 <= B_12)
      for (j = B_11;; j += 1) {
        Class = j;
        Sets_ForallDo(Classes_ClassMemPtr->A[j], (Sets_ProcOftElement)CharToClass0);
        if (j >= B_12) break;
      }
  }
  Dfa_LastCh = Classes_ClassCount;
  Sets_ForallDo(Classes_CharSet, (Sets_ProcOftElement)CharToClass);
}

void Classes_ReleaseSetMem
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER i;

  {
    LONGINT B_13 = 1, B_14 = Classes_SetCount;

    if (B_13 <= B_14)
      for (i = B_13;; i += 1) {
        Sets_ReleaseSet(&Classes_SetMemPtr->A[i].Set);
        Sets_ReleaseSet(&Classes_SetMemPtr->A[i].Classes);
        if (i >= B_14) break;
      }
  }
  DynArray_ReleaseArray((ADDRESS *)&Classes_SetMemPtr, &Classes_SetMemSize, (LONGINT)sizeof(Classes_ClassInfo));
}

void Classes__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Sets__init();
    DynArray__init();
    Strings__init();
    StringMem__init();
    IO__init();
    Sets__init();
    Tree0__init();
    Dfa__init();

    Classes_SetMemSize = 16;
    DynArray_MakeArray((ADDRESS *)&Classes_SetMemPtr, &Classes_SetMemSize, (LONGINT)sizeof(Classes_ClassInfo));
    Classes_SetCount = 0;
    Classes_ClassMemSize = 16;
    DynArray_MakeArray((ADDRESS *)&Classes_ClassMemPtr, &Classes_ClassMemSize, (LONGINT)sizeof(Sets_tSet));
  }
}
