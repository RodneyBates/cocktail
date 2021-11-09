#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif


static Strings_tString empty;
static BOOLEAN outside;
static struct S_1 {
    Strings_tString A[256];
} table;
static CHAR c;
static void WriteText ARGS((Strings_tString *text));


void Table_Define
# ifdef __STDC__
(CHAR letter, Strings_tString *definition)
# else
(letter, definition)
CHAR letter;
Strings_tString *definition;
# endif
{
  Strings_Assign(&table.A[letter], definition);
}

void Table_Translate
# ifdef __STDC__
(CHAR letter, Strings_tString *text)
# else
(letter, text)
CHAR letter;
Strings_tString *text;
# endif
{
  Strings_tString def;
  INTEGER l, i;

  Strings_Assign(&def, &table.A[letter]);
  i = 0;
  l = Strings_Length(&def);
  for (;;) {
    if (i == l) {
      goto EXIT_1;
    }
    INC(i);
    c = Strings_Char(&def, (Strings_tStringIndex)i);
    if (c == '%') {
      WriteText(text);
    } else if (c == '\\') {
      if (i < l) {
        INC(i);
        c = Strings_Char(&def, (Strings_tStringIndex)i);
        StdIO_WriteC(c);
      }
    } else {
      StdIO_WriteC(c);
    }
  } EXIT_1:;
}

static void WriteText
# ifdef __STDC__
(Strings_tString *text)
# else
(text)
Strings_tString *text;
# endif
{
  INTEGER i, l;
  CHAR c;

  i = 0;
  l = Strings_Length(text);
  for (;;) {
    if (i == l) {
      goto EXIT_2;
    }
    INC(i);
    c = Strings_Char(text, (Strings_tStringIndex)i);
    if (c == '\\') {
      if (i < l) {
        INC(i);
        c = Strings_Char(text, (Strings_tStringIndex)i);
        StdIO_WriteC(c);
      }
    } else {
      StdIO_WriteC(c);
    }
  } EXIT_2:;
}

void Table_BeginLine
# ifdef __STDC__
()
# else
()
# endif
{
  if (outside) {
    Table_Translate('^', &empty);
    outside = FALSE;
  }
}

void Table_CloseLine
# ifdef __STDC__
()
# else
()
# endif
{
  Table_Translate('$', &empty);
  outside = TRUE;
}

void Table_WriteLine
# ifdef __STDC__
(Strings_tString *text)
# else
(text)
Strings_tString *text;
# endif
{
  Strings_WriteS((System_tFile)IO_StdOutput, text);
}

void Table_NewLine
# ifdef __STDC__
()
# else
()
# endif
{
  StdIO_WriteNl();
}

void Table__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Strings__init();
    IO__init();
    StdIO__init();
    Strings__init();

    outside = TRUE;
    Strings_AssignEmpty(&empty);
    {
      CHAR B_1 = MIN_CHAR, B_2 = MAX_CHAR;

      if (B_1 <= B_2)
        for (c = B_1;; c += 1) {
          Strings_AssignEmpty(&table.A[c]);
          if (c >= B_2) break;
        }
    }
  }
}
