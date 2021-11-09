#include "SYSTEM_.h"

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Assertions
#include "Assertions.h"
#endif




void Assertions_Assert
# ifdef __STDC__
(BOOLEAN Condition, CHAR Msg[], LONGCARD O_1)
# else
(Condition, Msg, O_1)
BOOLEAN Condition;
CHAR Msg[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Msg, O_1, CHAR)
  Assertions_AssertPos(Condition, Msg, O_1, Positions_NoPosition);
  FREE_OPEN_ARRAYS
}

void Assertions_CantHappen
# ifdef __STDC__
(CHAR Msg[], LONGCARD O_2)
# else
(Msg, O_2)
CHAR Msg[];
LONGCARD O_2;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Msg, O_2, CHAR)
  Assertions_CantHappenPos(Msg, O_2, Positions_NoPosition);
  FREE_OPEN_ARRAYS
}

void Assertions_AssertPos
# ifdef __STDC__
(BOOLEAN Condition, CHAR Msg[], LONGCARD O_3, Positions_tPosition Position)
# else
(Condition, Msg, O_3, Position)
BOOLEAN Condition;
CHAR Msg[];
LONGCARD O_3;
Positions_tPosition Position;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Msg, O_3, CHAR)
  if (!Condition) {
    Assertions_CantHappenPos(Msg, O_3, Position);
  }
  FREE_OPEN_ARRAYS
}

void Assertions_CantHappenPos
# ifdef __STDC__
(CHAR Msg[], LONGCARD O_4, Positions_tPosition Position)
# else
(Msg, O_4, Position)
CHAR Msg[];
LONGCARD O_4;
Positions_tPosition Position;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(Msg, O_4, CHAR)
  Errors_Message(Msg, O_4, (LONGCARD)Errors_Fatal, Position);
  FREE_OPEN_ARRAYS
}

void Assertions__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Positions__init();
    Positions__init();
    Errors__init();

  }
}
