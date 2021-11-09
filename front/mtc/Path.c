#include "SYSTEM_.h"

#ifndef DEFINITION_Strings
#include "Strings.h"
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
  Strings_tString s1, s2;
  Strings_tString l;
  struct S_2 Arg;
  Strings_tStringIndex pos;

  GetArgument(0L, Arg.A, 256L);
  Strings_ArrayToString(Arg.A, 256L, &s1);
  pos = Strings_Length(&s1);
  while (pos > 0 && Strings_Char(&s1, pos) != '/' && Strings_Char(&s1, pos) != '\\') {
    DEC(pos);
  }
  if (pos > 0) {
    Strings_SubString(&s1, 1, pos, &s2);
    Strings_ArrayToString(a, O_1, &s1);
    Strings_Concatenate(&s2, &s1);
    Strings_Append(&s2, '\0');
    Strings_StringToArray(&s2, a, O_1);
  }
}

void Path__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Strings__init();
    System__init();

  }
}
