#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

Scanner_tScanAttribute Scanner_Attribute;

#define cEof   '\0'
#define cTab   '\t'
#define cEol   '\n'
static CHAR next, ch;


void Scanner_BeginScanner
# ifdef __STDC__
()
# else
()
# endif
{
  next = IO_ReadC((System_tFile)IO_StdInput);
  ch = cEol;
}

void Scanner_CloseScanner
# ifdef __STDC__
()
# else
()
# endif
{
}

CARDINAL Scanner_GetToken
# ifdef __STDC__
()
# else
()
# endif
{
  for (;;) {
    if (ch == cEof) {
      return 0;
    } else if (ch == cEol) {
      INC(Scanner_Attribute.Position.Line);
      Scanner_Attribute.Position.Column = 0;
    } else if (ch == cTab) {
      Scanner_Attribute.Position.Column = (Scanner_Attribute.Position.Column / 8 + 1) * 8;
    }
    INC(Scanner_Attribute.Position.Column);
    ch = next;
    next = IO_ReadC((System_tFile)IO_StdInput);
    switch (ch) {
    case cEof:;
      return 0;
      break;
    case ' ':;
      return 1;
      break;
    case '^':;
      return 2;
      break;
    case '%':;
      return 3;
      break;
    case '$':;
      return 4;
      break;
    case '.':;
      return 5;
      break;
    case '\\':;
      if (next == cEol) {
        ch = next;
        next = IO_ReadC((System_tFile)IO_StdInput);
        return 10;
      } else {
        return 6;
      }
      break;
    case '{':;
      return 7;
      break;
    case '}':;
      return 8;
      break;
    case cEol:;
      return 9;
      break;
    case cTab:;
      return 12;
      break;
    default :
      Scanner_Attribute.Ch = ch;
      return 11;
      break;
    }
  } EXIT_1:;
}

void Scanner_ErrorAttribute
# ifdef __STDC__
(CARDINAL Symbol, Scanner_tScanAttribute *Attribute)
# else
(Symbol, Attribute)
CARDINAL Symbol;
Scanner_tScanAttribute *Attribute;
# endif
{
  Attribute->Ch = ' ';
}

void Scanner__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Positions__init();
    IO__init();

    Scanner_Attribute.Position.Line = 0;
    Scanner_Attribute.Position.Column = 0;
  }
}
