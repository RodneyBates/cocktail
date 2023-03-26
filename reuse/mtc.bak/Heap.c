#include "SYSTEM_.h"

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Heap
#include "Heap.h"
#endif

LONGCARD Heap_HeapUsed;

#define PoolSize   10240
typedef struct S_1 *tBlockPtr;
typedef struct S_1 {
    tBlockPtr Successor;
    struct S_2 {
        CHAR A[PoolSize - 1 + 1];
    } Block;
} tBlock;
static tBlockPtr BlockList;
static ADDRESS PoolFreePtr;
static ADDRESS PoolEndPtr;


ADDRESS Heap_Alloc
# ifdef __STDC__
(LONGINT ByteCount)
# else
(ByteCount)
LONGINT ByteCount;
# endif
{
  tBlockPtr BlockPtr;

  ByteCount = (LONGINT)((BITSET)(ByteCount + VAL(LONGINT, General_MaxAlign) - 1) & General_AlignMasks.A[General_MaxAlign]);
  if ((LONGINT)(PoolEndPtr - (LONGCARD)PoolFreePtr) < ByteCount) {
    BlockPtr = BlockList;
    BlockList = (tBlockPtr)Memory_Alloc(sizeof(tBlock));
    BlockList->Successor = BlockPtr;
    PoolFreePtr = ADR(BlockList->Block);
    PoolEndPtr = (ADDRESS)(PoolFreePtr + PoolSize);
    INC1(Heap_HeapUsed, PoolSize);
  }
  INC1(PoolFreePtr, (LONGCARD)(ADDRESS)ByteCount);
  return PoolFreePtr - (LONGCARD)(ADDRESS)ByteCount;
}

void Heap_Free
# ifdef __STDC__
()
# else
()
# endif
{
  tBlockPtr BlockPtr;

  while (BlockList != NIL) {
    BlockPtr = BlockList;
    BlockList = BlockList->Successor;
    Memory_Free(sizeof(tBlock), BlockPtr);
  }
  PoolFreePtr = (ADDRESS)NIL;
  PoolEndPtr = (ADDRESS)NIL;
  Heap_HeapUsed = 0;
}

void Heap__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    General__init();
    Memory__init();

    BlockList = NIL;
    Heap_Free();
  }
}
