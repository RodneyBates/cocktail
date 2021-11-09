#define DEFINITION_Classes

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

typedef struct Classes_1 {
    Sets_tSet Set, Classes;
} Classes_ClassInfo;
extern Sets_tSet Classes_CharSet, Classes_Unused;
extern struct Classes_2 {
    CHAR A[256];
} Classes_ToClass, Classes_ToChar;
extern struct Classes_3 {
    Classes_ClassInfo A[100000 + 1];
} *Classes_SetMemPtr;
extern LONGINT Classes_SetMemSize;
extern INTEGER Classes_SetCount;
extern struct Classes_4 {
    Sets_tSet A[256];
} *Classes_ClassMemPtr;
extern LONGINT Classes_ClassMemSize;
extern CHAR Classes_ClassCount;
extern INTEGER Classes_IsInSetMem ARGS((Sets_tSet Set));
extern void Classes_ComputeClasses ARGS((BOOLEAN Blocking));
extern void Classes_ReleaseSetMem ARGS(());
extern void Classes__init();
