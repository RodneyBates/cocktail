#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
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

    if (W_1->File < Position2.File) {
      return -1;
    }
    if (W_1->File > Position2.File) {
      return 1;
    }
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
  IO_WriteC(File, '"');
  Idents_WriteIdent(File, Position.File);
  IO_WriteS(File, (STRING)"\", ", 3L);
  IO_WriteI(File, (LONGINT)Position.Line, 3L);
  IO_WriteS(File, (STRING)", ", 2L);
  IO_WriteI(File, (LONGINT)Position.Column, 2L);
}

void Positions__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Idents__init();
    IO__init();
    Idents__init();

    Positions_NoPosition.File = Idents_NoIdent;
    Positions_NoPosition.Line = 0;
    Positions_NoPosition.Column = 0;
  }
}
