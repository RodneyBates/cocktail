#define DEFINITION_Assertions

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

extern void Assertions_Assert ARGS((BOOLEAN Condition, CHAR Msg[], LONGCARD ));
extern void Assertions_CantHappen ARGS((CHAR Msg[], LONGCARD ));
extern void Assertions_AssertPos ARGS((BOOLEAN Condition, CHAR Msg[], LONGCARD , Positions_tPosition Position));
extern void Assertions_CantHappenPos ARGS((CHAR Msg[], LONGCARD , Positions_tPosition Position));
extern void Assertions__init();
