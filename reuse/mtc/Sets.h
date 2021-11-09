#define DEFINITION_Sets

#ifndef DEFINITION_IO
#include "IO.h"
#endif

typedef SHORTCARD Sets_tInternalElmt;
typedef CARDINAL Sets_tElement;
typedef struct Sets_1 {
    BITSET A[MAX_SHORTCARD + 1];
} Sets_ArrayOfBitset;
typedef void (*Sets_ProcOftElement) ARGS((Sets_tElement));
typedef BOOLEAN (*Sets_ProcOftElementToBool) ARGS((Sets_tElement));
typedef struct Sets_2 {
    Sets_ArrayOfBitset *BitsetPtr;
    SHORTCARD LastBitset;
    Sets_tInternalElmt MaxElmt;
    Sets_tInternalElmt Card;
    Sets_tInternalElmt FirstElmt;
    Sets_tInternalElmt LastElmt;
} Sets_tSet;
extern void Sets_InitNullSet ARGS((Sets_tSet *Set));
extern void Sets_MakeSet ARGS((Sets_tSet *Set, Sets_tElement MaxElement));
extern void Sets_ReleaseSet ARGS((Sets_tSet *Set));
extern void Sets_Union ARGS((Sets_tSet *Set1, Sets_tSet Set2));
extern void Sets_Difference ARGS((Sets_tSet *Set1, Sets_tSet Set2));
extern void Sets_Intersection ARGS((Sets_tSet *Set1, Sets_tSet Set2));
extern void Sets_SymDiff ARGS((Sets_tSet *Set1, Sets_tSet Set2));
extern void Sets_Complement ARGS((Sets_tSet *Set));
extern void Sets_Include ARGS((Sets_tSet *Set, Sets_tElement Elmt));
extern void Sets_Exclude ARGS((Sets_tSet *Set, Sets_tElement Elmt));
extern Sets_tElement Sets_Card ARGS((Sets_tSet *Set));
extern Sets_tElement Sets_Size ARGS((Sets_tSet *Set));
extern Sets_tElement Sets_Minimum ARGS((Sets_tSet *Set));
extern Sets_tElement Sets_Maximum ARGS((Sets_tSet *Set));
extern Sets_tElement Sets_Select ARGS((Sets_tSet *Set));
extern Sets_tElement Sets_Extract ARGS((Sets_tSet *Set));
extern BOOLEAN Sets_IsSubset ARGS((Sets_tSet Set1, Sets_tSet Set2));
extern BOOLEAN Sets_IsStrictSubset ARGS((Sets_tSet Set1, Sets_tSet Set2));
extern BOOLEAN Sets_IsEqual ARGS((Sets_tSet *Set1, Sets_tSet *Set2));
extern BOOLEAN Sets_IsNotEqual ARGS((Sets_tSet Set1, Sets_tSet Set2));
extern BOOLEAN Sets_IsElement ARGS((Sets_tElement Elmt, Sets_tSet *Set));
extern BOOLEAN Sets_IsEmpty ARGS((Sets_tSet Set));
extern BOOLEAN Sets_Forall ARGS((Sets_tSet Set, Sets_ProcOftElementToBool Proc));
extern BOOLEAN Sets_Exists ARGS((Sets_tSet Set, Sets_ProcOftElementToBool Proc));
extern BOOLEAN Sets_Exists1 ARGS((Sets_tSet Set, Sets_ProcOftElementToBool Proc));
extern void Sets_Assign ARGS((Sets_tSet *Set1, Sets_tSet Set2));
extern void Sets_AssignElmt ARGS((Sets_tSet *Set, Sets_tElement Elmt));
extern void Sets_AssignEmpty ARGS((Sets_tSet *Set));
extern void Sets_ForallDo ARGS((Sets_tSet Set, Sets_ProcOftElement Proc));
extern void Sets_ReadSet ARGS((IO_tFile f, Sets_tSet *Set));
extern void Sets_WriteSet ARGS((IO_tFile f, Sets_tSet Set));
extern void Sets__init();
