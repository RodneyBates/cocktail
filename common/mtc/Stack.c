#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Stack
#include "Stack.h"
#endif


#define InitStackSize   50


void Stack_MakeStack
# ifdef __STDC__
(Stack_tStack *s)
# else
(s)
Stack_tStack *s;
# endif
{
  s->StackPtr = 0;
  s->StackSize = InitStackSize;
  DynArray_MakeArray((ADDRESS *)&s->Array, &s->StackSize, (LONGINT)sizeof(Stack_tElmt));
}

void Stack_ReleaseStack
# ifdef __STDC__
(Stack_tStack *s)
# else
(s)
Stack_tStack *s;
# endif
{
  if (s->Array == NIL || s->StackSize < InitStackSize) {
    Errors_ERROR((STRING)"Stack.Release", 13L);
  }
  DynArray_ReleaseArray((ADDRESS *)&s->Array, &s->StackSize, (LONGINT)sizeof(Stack_tElmt));
  s->Array = NIL;
  s->StackSize = -1;
}

void Stack_ClearStack
# ifdef __STDC__
(Stack_tStack *s)
# else
(s)
Stack_tStack *s;
# endif
{
  if (s->Array == NIL || s->StackSize < InitStackSize) {
    Errors_ERROR((STRING)"Stack.ClearStack", 16L);
  }
  s->StackPtr = 0;
}

BOOLEAN Stack_IsEmptyStack
# ifdef __STDC__
(Stack_tStack s)
# else
(s)
Stack_tStack s;
# endif
{
  if (s.Array == NIL || s.StackSize < InitStackSize) {
    Errors_ERROR((STRING)"Stack.IsEmptyStack", 18L);
  }
  return s.StackPtr == 0;
}

void Stack_Push
# ifdef __STDC__
(Stack_tStack *s, Stack_tElmt e)
# else
(s, e)
Stack_tStack *s;
Stack_tElmt e;
# endif
{
  if (s->Array == NIL || s->StackSize < InitStackSize) {
    Errors_ERROR((STRING)"Stack.Push", 10L);
  }
  INC(s->StackPtr);
  if (s->StackPtr >= s->StackSize) {
    DynArray_ExtendArray((ADDRESS *)&s->Array, &s->StackSize, (LONGINT)sizeof(Stack_tElmt));
  }
  s->Array->A[s->StackPtr] = e;
}

Stack_tElmt Stack_Pop
# ifdef __STDC__
(Stack_tStack *s)
# else
(s)
Stack_tStack *s;
# endif
{
  Stack_tElmt e;

  if (s->Array == NIL || s->StackSize < InitStackSize || s->StackPtr < 1) {
    Errors_ERROR((STRING)"Stack.Pop", 9L);
  }
  e = Stack_Top(s);
  DEC(s->StackPtr);
  return e;
}

Stack_tElmt Stack_Top
# ifdef __STDC__
(Stack_tStack *s)
# else
(s)
Stack_tStack *s;
# endif
{
  if (s->Array == NIL || s->StackSize < InitStackSize || s->StackPtr < 1) {
    Errors_ERROR((STRING)"Stack.Top", 9L);
  }
  return s->Array->A[s->StackPtr];
}

INTEGER Stack_Depth
# ifdef __STDC__
(Stack_tStack s)
# else
(s)
Stack_tStack s;
# endif
{
  if (s.Array == NIL || s.StackSize < InitStackSize || s.StackPtr < 0) {
    Errors_ERROR((STRING)"Stack.Depth", 11L);
  }
  return s.StackPtr;
}

void Stack_Assign
# ifdef __STDC__
(Stack_tStack *s1, Stack_tStack s2)
# else
(s1, s2)
Stack_tStack *s1;
Stack_tStack s2;
# endif
{
  INTEGER i;

  Stack_ClearStack(s1);
  {
    LONGINT B_1 = 1, B_2 = Stack_Depth(s2);

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        Stack_Push(s1, s2.Array->A[i]);
        if (i >= B_2) break;
      }
  }
}

void Stack__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    DynArray__init();
    Errors__init();
    Strings__init();

  }
}
