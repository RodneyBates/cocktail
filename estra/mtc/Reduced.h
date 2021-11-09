#define DEFINITION_Reduced

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

extern BOOLEAN Reduced_IsReduced;
extern Sets_tSet Reduced_UnReachable;
extern Sets_tSet Reduced_UnDerivable;
extern void Reduced_TestReduced ARGS((Sets_tSet StartClasses));
extern void Reduced__init();
