#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Queue
#include "Queue.h"
#endif


static LONGINT QueueSizeL;
static struct S_1 {
    SHORTCARD A[10000 + 1];
} *QueuePtr;
static SHORTCARD QueueSize, QueueCount, QueueIn, QueueOut;
static Sets_tSet QueueSet;


void Queue_MakeQueue
# ifdef __STDC__
(SHORTCARD Size)
# else
(Size)
SHORTCARD Size;
# endif
{
  QueueSizeL = Size;
  DynArray_MakeArray((ADDRESS *)&QueuePtr, &QueueSizeL, (LONGINT)sizeof(SHORTCARD));
  QueueSize = Size;
  QueueCount = 0;
  QueueIn = 0;
  QueueOut = 0;
  Sets_MakeSet(&QueueSet, (Sets_tElement)QueueSize);
}

void Queue_ReleaseQueue
# ifdef __STDC__
()
# else
()
# endif
{
  DynArray_ReleaseArray((ADDRESS *)&QueuePtr, &QueueSizeL, (LONGINT)sizeof(SHORTCARD));
  Sets_ReleaseSet(&QueueSet);
}

BOOLEAN Queue_IsEmpty
# ifdef __STDC__
()
# else
()
# endif
{
  return QueueCount == 0;
}

void Queue_Enqueue
# ifdef __STDC__
(SHORTCARD Elmt)
# else
(Elmt)
SHORTCARD Elmt;
# endif
{
  if (!Sets_IsElement((Sets_tElement)Elmt, &QueueSet)) {
    QueuePtr->A[QueueIn] = Elmt;
    QueueIn = (QueueIn + 1) % QueueSize;
    INC(QueueCount);
    Sets_Include(&QueueSet, (Sets_tElement)Elmt);
  }
}

SHORTCARD Queue_Dequeue
# ifdef __STDC__
()
# else
()
# endif
{
  SHORTCARD Result;

  Result = QueuePtr->A[QueueOut];
  QueueOut = (QueueOut + 1) % QueueSize;
  DEC(QueueCount);
  Sets_Exclude(&QueueSet, (Sets_tElement)Result);
  return Result;
}

BOOLEAN Queue_IsElement
# ifdef __STDC__
(SHORTCARD Elmt)
# else
(Elmt)
SHORTCARD Elmt;
# endif
{
  return Sets_IsElement((Sets_tElement)Elmt, &QueueSet);
}

void Queue__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    DynArray__init();
    Sets__init();
    Sets__init();

  }
}
