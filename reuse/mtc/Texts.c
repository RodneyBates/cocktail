#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif




void Texts_MakeText
# ifdef __STDC__
(Texts_tText *Text)
# else
(Text)
Texts_tText *Text;
# endif
{
  Lists_MakeList(Text);
}

void Texts_Append
# ifdef __STDC__
(Texts_tText *Text, Strings_tString *String)
# else
(Text, String)
Texts_tText *Text;
Strings_tString *String;
# endif
{
  Lists_Append(Text, (ADDRESS)StringMem_PutString(String));
}

void Texts_Insert
# ifdef __STDC__
(Texts_tText *Text, Strings_tString *String)
# else
(Text, String)
Texts_tText *Text;
Strings_tString *String;
# endif
{
  Lists_Insert(Text, (ADDRESS)StringMem_PutString(String));
}

BOOLEAN Texts_IsEmpty
# ifdef __STDC__
(Texts_tText *Text)
# else
(Text)
Texts_tText *Text;
# endif
{
  return Lists_IsEmpty(*Text);
}

void Texts_WriteText
# ifdef __STDC__
(IO_tFile f, Texts_tText Text)
# else
(f, Text)
IO_tFile f;
Texts_tText Text;
# endif
{
  Strings_tString String;

  while (!Lists_IsEmpty(Text)) {
    StringMem_GetString((StringMem_tStringRef)Lists_Head(Text), &String);
    Strings_WriteL(f, &String);
    Lists_Tail(&Text);
  }
}

void Texts__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Lists__init();
    Strings__init();
    IO__init();
    Lists__init();
    Strings__init();
    StringMem__init();
    Lists__init();

  }
}
