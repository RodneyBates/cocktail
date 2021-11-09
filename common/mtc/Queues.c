#include "SYSTEM_.h"

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif


#define InitSize   2
static Queues_tIndex ElmtSize;
static void PackQueue ARGS((Queues_tQueue *Queue));
static void ExtendQueue ARGS((Queues_tQueue *Queue));
static void WriteQueue ARGS((IO_tFile file, Queues_tQueue Queue));


void Queues_MakeQueue
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  {
    register Queues_tQueue *W_1 = Queue;

    W_1->Size = InitSize;
    W_1->First = 0;
    W_1->Last = W_1->Size - 1;
    W_1->Array = (Queues_tArrayPtr)Memory_Alloc(W_1->Size * ElmtSize);
  }
}

void Queues_ReleaseQueue
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  {
    register Queues_tQueue *W_2 = Queue;

    Memory_Free(W_2->Size * ElmtSize, (ADDRESS)W_2->Array);
    W_2->Array = NIL;
    W_2->Size = 0;
  }
}

void Queues_AssignEmpty
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  {
    register Queues_tQueue *W_3 = Queue;

    W_3->First = 0;
    W_3->Last = W_3->Size - 1;
  }
}

void Queues_Append
# ifdef __STDC__
(Queues_tQueue *Queue, Queues_tElmt Elmt)
# else
(Queue, Elmt)
Queues_tQueue *Queue;
Queues_tElmt Elmt;
# endif
{
  {
    register Queues_tQueue *W_4 = Queue;

    INC(W_4->Last);
    if (W_4->Last == W_4->Size) {
      W_4->Last = 0;
    }
    W_4->Array->A[W_4->Last] = Elmt;
    if (Queues_IsEmpty(*Queue)) {
      ExtendQueue(Queue);
    }
  }
}

Queues_tElmt Queues_Head
# ifdef __STDC__
(Queues_tQueue Queue)
# else
(Queue)
Queues_tQueue Queue;
# endif
{
  {
    register Queues_tQueue *W_5 = &Queue;

    if (Queues_IsEmpty(Queue)) {
      Errors_ERROR((STRING)"Queues: \"Head\" of empty queue is not defined", 44L);
    }
    return W_5->Array->A[W_5->First];
  }
}

Queues_tElmt Queues_Last
# ifdef __STDC__
(Queues_tQueue Queue)
# else
(Queue)
Queues_tQueue Queue;
# endif
{
  {
    register Queues_tQueue *W_6 = &Queue;

    if (Queues_IsEmpty(Queue)) {
      Errors_ERROR((STRING)"Queues: \"Last\" of empty queue is not defined", 44L);
    }
    return W_6->Array->A[W_6->Last];
  }
}

void Queues_Tail
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  Queues_ClearHead(Queue);
}

void Queues_ClearHead
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  {
    register Queues_tQueue *W_7 = Queue;

    if (Queues_IsEmpty(*Queue)) {
      Errors_ERROR((STRING)"Queues: \"ClearHead\" of empty queue is not defined", 49L);
    }
    INC(W_7->First);
    if (W_7->First == W_7->Size) {
      W_7->First = 0;
    }
  }
}

void Queues_ClearLast
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  {
    register Queues_tQueue *W_8 = Queue;

    if (Queues_IsEmpty(*Queue)) {
      Errors_ERROR((STRING)"Queues: \"ClearLast\" of empty queue is not defined", 49L);
    }
    if (W_8->Last == 0) {
      W_8->Last = W_8->Size;
    }
    DEC(W_8->Last);
  }
}

void Queues_Insert
# ifdef __STDC__
(Queues_tQueue *Queue, Queues_tElmt Elmt)
# else
(Queue, Elmt)
Queues_tQueue *Queue;
Queues_tElmt Elmt;
# endif
{
  {
    register Queues_tQueue *W_9 = Queue;

    if (W_9->First == 0) {
      W_9->First = W_9->Size;
    }
    DEC(W_9->First);
    W_9->Array->A[W_9->First] = Elmt;
    if (Queues_IsEmpty(*Queue)) {
      ExtendQueue(Queue);
    }
  }
}

BOOLEAN Queues_IsEmpty
# ifdef __STDC__
(Queues_tQueue Queue)
# else
(Queue)
Queues_tQueue Queue;
# endif
{
  {
    register Queues_tQueue *W_10 = &Queue;

    return (W_10->Last + 1) % W_10->Size == W_10->First;
  }
}

Queues_tIndex Queues_Length
# ifdef __STDC__
(Queues_tQueue Queue)
# else
(Queue)
Queues_tQueue Queue;
# endif
{
  Queues_tIndex Len;

  {
    register Queues_tQueue *W_11 = &Queue;

    Len = W_11->Last + 1 - W_11->First;
    if (Len < 0) {
      INC1(Len, W_11->Size);
    } else if (Len >= W_11->Size) {
      DEC1(Len, W_11->Size);
    }
    return Len;
  }
}

Queues_tElmt Queues_GetElement
# ifdef __STDC__
(Queues_tQueue Queue, Queues_tIndex Pos)
# else
(Queue, Pos)
Queues_tQueue Queue;
Queues_tIndex Pos;
# endif
{
  Queues_tIndex Index;

  {
    register Queues_tQueue *W_12 = &Queue;

    if (Pos < 1 || Pos > Queues_Length(Queue)) {
      Errors_ERROR((STRING)"Queues: \"pos\" in \"GetElement\" is out of range", 45L);
    }
    Index = W_12->First + Pos - 1;
    if (Index >= W_12->Size) {
      DEC1(Index, W_12->Size);
    }
    return W_12->Array->A[Index];
  }
}

void Queues_Assign
# ifdef __STDC__
(Queues_tQueue *Queue1, Queues_tQueue Queue2)
# else
(Queue1, Queue2)
Queues_tQueue *Queue1;
Queues_tQueue Queue2;
# endif
{
  Queues_tIndex len, i;

  len = Queues_Length(Queue2);
  if (len == 0) {
    Queues_AssignEmpty(Queue1);
  } else {
    {
      register Queues_tQueue *W_13 = Queue1;

      if (len >= W_13->Size) {
        Memory_Free(W_13->Size * ElmtSize, (ADDRESS)W_13->Array);
        W_13->Size = len + 1;
        W_13->Array = (Queues_tArrayPtr)Memory_Alloc(W_13->Size * ElmtSize);
      }
      W_13->First = 0;
      W_13->Last = -1;
      i = Queue2.First;
      if (i > Queue2.Last) {
        do {
          INC(W_13->Last);
          W_13->Array->A[W_13->Last] = Queue2.Array->A[i];
          INC(i);
        } while (!(i == Queue2.Size));
        i = 0;
      }
      do {
        INC(W_13->Last);
        W_13->Array->A[W_13->Last] = Queue2.Array->A[i];
        INC(i);
      } while (!(i > Queue2.Last));
    }
  }
}

Queues_tElmt Queues_TakeHead
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  Queues_tElmt Elmt;

  Elmt = Queues_Head(*Queue);
  Queues_ClearHead(Queue);
  return Elmt;
}

Queues_tElmt Queues_TakeLast
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  Queues_tElmt Elmt;

  Elmt = Queues_Last(*Queue);
  Queues_ClearLast(Queue);
  return Elmt;
}

static void PackQueue
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  Queues_tQueue hQueue;

  {
    register Queues_tQueue *W_14 = &hQueue;

    W_14->Size = Queues_Length(*Queue) + 1;
    W_14->Array = (Queues_tArrayPtr)Memory_Alloc(W_14->Size * ElmtSize);
    Queues_Assign(&hQueue, *Queue);
  }
  Memory_Free(Queue->Size * ElmtSize, (ADDRESS)Queue->Array);
  *Queue = hQueue;
}

static void ExtendQueue
# ifdef __STDC__
(Queues_tQueue *Queue)
# else
(Queue)
Queues_tQueue *Queue;
# endif
{
  Queues_tIndex i;
  Queues_tArrayPtr hArray;

  {
    register Queues_tQueue *W_15 = Queue;

    hArray = (Queues_tArrayPtr)Memory_Alloc(2 * W_15->Size * ElmtSize);
    if (W_15->First <= W_15->Last) {
      {
        LONGINT B_1 = W_15->First, B_2 = W_15->Last;

        if (B_1 <= B_2)
          for (i = B_1;; i += 1) {
            hArray->A[i] = W_15->Array->A[i];
            if (i >= B_2) break;
          }
      }
    } else {
      {
        LONGINT B_3 = 0, B_4 = W_15->Last;

        if (B_3 <= B_4)
          for (i = B_3;; i += 1) {
            hArray->A[i] = W_15->Array->A[i];
            if (i >= B_4) break;
          }
      }
      {
        LONGINT B_5 = W_15->First, B_6 = W_15->Size - 1;

        if (B_5 <= B_6)
          for (i = B_5;; i += 1) {
            hArray->A[i + W_15->Size] = W_15->Array->A[i];
            if (i >= B_6) break;
          }
      }
      INC1(W_15->First, W_15->Size);
    }
    Memory_Free(W_15->Size * ElmtSize, (ADDRESS)W_15->Array);
    W_15->Size = 2 * W_15->Size;
    W_15->Array = hArray;
  }
}

static void WriteQueue
# ifdef __STDC__
(IO_tFile file, Queues_tQueue Queue)
# else
(file, Queue)
IO_tFile file;
Queues_tQueue Queue;
# endif
{
  {
    register Queues_tQueue *W_16 = &Queue;

    IO_WriteS(file, (STRING)"Size:  ", 7L);
    IO_WriteI(file, W_16->Size, 1L);
    IO_WriteNl(file);
    IO_WriteS(file, (STRING)"First: ", 7L);
    IO_WriteI(file, W_16->First, 1L);
    IO_WriteNl(file);
    IO_WriteS(file, (STRING)"Last:  ", 7L);
    IO_WriteI(file, W_16->Last, 1L);
    IO_WriteNl(file);
  }
}

void Queues__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Errors__init();
    IO__init();
    Memory__init();

    ElmtSize = sizeof(Queues_tElmt);
    if (ODD(ElmtSize) && ElmtSize > 1) {
      INC(ElmtSize);
    }
  }
}
