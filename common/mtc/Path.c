#include "SYSTEM_.h"

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif


struct S_2 {
    CHAR A[255 + 1];
};


void Path_InsertPath
# ifdef __STDC__
(CHAR a[], LONGCARD O_1)
# else
(a, O_1)
CHAR a[];
LONGCARD O_1;
# endif
{
  struct S_2 s, Arg;
  INTEGER pos;

  GetArgument(0L, Arg.A, 256L);
  pos = Character_Length(Arg.A, 256L);
  while (pos > 0 && Character_Char(Arg.A, 256L, pos) != '/' && Character_Char(Arg.A, 256L, pos) != '\\') {
    DEC(pos);
  }
  if (pos > 0) {
    Character_SubString(Arg.A, 256L, 1L, pos, s.A, 256L);
    Character_Concatenate(s.A, 256L, a, O_1);
    Character_Assign(a, O_1, s.A, 256L);
  }
}

void Path__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Character__init();
    System__init();

  }
}
