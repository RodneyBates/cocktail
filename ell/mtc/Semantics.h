#define DEFINITION_Semantics

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern struct Semantics_1 {
    CHAR A[127 + 1];
} Semantics_SemanticsTabName;
extern void Semantics_BeginSemantics ARGS(());
extern void Semantics_DoSemantics ARGS((Tree_tTree yyt));
extern void Semantics_CloseSemantics ARGS(());
extern void Semantics__init();
