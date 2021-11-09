#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

Positions_tPosition Positions_NoPosition;



INTEGER Positions_Compare
# ifdef __STDC__
(Positions_tPosition Position1, Positions_tPosition Position2)
# else
(Position1, Position2)
Positions_tPosition Position1, Position2;
# endif
{
  {
    register Positions_tPosition *W_1 = &Position1;

    if (W_1->Line < Position2.Line) {
      return -1;
    }
    if (W_1->Line > Position2.Line) {
      return 1;
    }
    if (W_1->Column < Position2.Column) {
      return -1;
    }
    if (W_1->Column > Position2.Column) {
      return 1;
    }
    return 0;
  }
}

void Positions_WritePosition
# ifdef __STDC__
(IO_tFile File, Positions_tPosition Position)
# else
(File, Position)
IO_tFile File;
Positions_tPosition Position;
# endif
{
  IO_WriteI(File, VAL(INTEGER, Position.Line), 4);
  IO_WriteC(File, ',');
  IO_WriteI(File, VAL(INTEGER, Position.Column), 3);
}

void Positions__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    IO__init();

    Positions_NoPosition.Line = 0;
    Positions_NoPosition.Column = 0;
  }
}
