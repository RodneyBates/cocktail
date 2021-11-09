#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif




void StdIO_ReadClose
# ifdef __STDC__
()
# else
()
# endif
{
  IO_ReadClose(IO_StdInput);
}

INTEGER StdIO_Read
# ifdef __STDC__
(ADDRESS Buffer, CARDINAL Size)
# else
(Buffer, Size)
ADDRESS Buffer;
CARDINAL Size;
# endif
{
  return IO_Read(IO_StdInput, Buffer, Size);
}

CHAR StdIO_ReadC
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_ReadC(IO_StdInput);
}

INTEGER StdIO_ReadI
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_ReadI(IO_StdInput);
}

REAL StdIO_ReadR
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_ReadR(IO_StdInput);
}

BOOLEAN StdIO_ReadB
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_ReadB(IO_StdInput);
}

INTEGER StdIO_ReadN
# ifdef __STDC__
(INTEGER Base)
# else
(Base)
INTEGER Base;
# endif
{
  return IO_ReadN(IO_StdInput, Base);
}

void StdIO_ReadS
# ifdef __STDC__
(CHAR s[], LONGCARD O_1)
# else
(s, O_1)
CHAR s[];
LONGCARD O_1;
# endif
{
  IO_ReadS(IO_StdInput, s, O_1);
}

SHORTINT StdIO_ReadShort
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_ReadShort(IO_StdInput);
}

LONGINT StdIO_ReadLong
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_ReadLong(IO_StdInput);
}

CARDINAL StdIO_ReadCard
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_ReadCard(IO_StdInput);
}

void StdIO_ReadNl
# ifdef __STDC__
()
# else
()
# endif
{
  IO_ReadNl(IO_StdInput);
}

void StdIO_UnRead
# ifdef __STDC__
()
# else
()
# endif
{
  IO_UnRead(IO_StdInput);
}

BOOLEAN StdIO_EndOfLine
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_EndOfLine(IO_StdInput);
}

BOOLEAN StdIO_EndOfFile
# ifdef __STDC__
()
# else
()
# endif
{
  return IO_EndOfFile(IO_StdInput);
}

void StdIO_WriteClose
# ifdef __STDC__
()
# else
()
# endif
{
  IO_WriteClose(IO_StdOutput);
}

void StdIO_WriteFlush
# ifdef __STDC__
()
# else
()
# endif
{
  IO_WriteFlush(IO_StdOutput);
}

INTEGER StdIO_Write
# ifdef __STDC__
(ADDRESS Buffer, CARDINAL Size)
# else
(Buffer, Size)
ADDRESS Buffer;
CARDINAL Size;
# endif
{
  return IO_Write(IO_StdOutput, Buffer, Size);
}

void StdIO_WriteC
# ifdef __STDC__
(CHAR c)
# else
(c)
CHAR c;
# endif
{
  IO_WriteC(IO_StdOutput, c);
}

void StdIO_WriteI
# ifdef __STDC__
(INTEGER n, CARDINAL FieldWidth)
# else
(n, FieldWidth)
INTEGER n;
CARDINAL FieldWidth;
# endif
{
  IO_WriteI(IO_StdOutput, n, FieldWidth);
}

void StdIO_WriteR
# ifdef __STDC__
(REAL n, CARDINAL Before, CARDINAL After, CARDINAL Exp)
# else
(n, Before, After, Exp)
REAL n;
CARDINAL Before, After, Exp;
# endif
{
  IO_WriteR(IO_StdOutput, n, Before, After, Exp);
}

void StdIO_WriteB
# ifdef __STDC__
(BOOLEAN b)
# else
(b)
BOOLEAN b;
# endif
{
  IO_WriteB(IO_StdOutput, b);
}

void StdIO_WriteN
# ifdef __STDC__
(LONGCARD n, CARDINAL FieldWidth, CARDINAL Base)
# else
(n, FieldWidth, Base)
LONGCARD n;
CARDINAL FieldWidth, Base;
# endif
{
  IO_WriteN(IO_StdOutput, n, FieldWidth, Base);
}

void StdIO_WriteS
# ifdef __STDC__
(CHAR s[], LONGCARD O_2)
# else
(s, O_2)
CHAR s[];
LONGCARD O_2;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s, O_2, CHAR)
  IO_WriteS(IO_StdOutput, s, O_2);
  FREE_OPEN_ARRAYS
}

void StdIO_WriteShort
# ifdef __STDC__
(SHORTINT n, CARDINAL FieldWidth)
# else
(n, FieldWidth)
SHORTINT n;
CARDINAL FieldWidth;
# endif
{
  IO_WriteShort(IO_StdOutput, n, FieldWidth);
}

void StdIO_WriteLong
# ifdef __STDC__
(LONGINT n, CARDINAL FieldWidth)
# else
(n, FieldWidth)
LONGINT n;
CARDINAL FieldWidth;
# endif
{
  IO_WriteLong(IO_StdOutput, n, FieldWidth);
}

void StdIO_WriteCard
# ifdef __STDC__
(CARDINAL n, CARDINAL FieldWidth)
# else
(n, FieldWidth)
CARDINAL n;
CARDINAL FieldWidth;
# endif
{
  IO_WriteCard(IO_StdOutput, n, FieldWidth);
}

void StdIO_WriteNl
# ifdef __STDC__
()
# else
()
# endif
{
  IO_WriteNl(IO_StdOutput);
}

void StdIO_CloseIO
# ifdef __STDC__
()
# else
()
# endif
{
  IO_WriteFlush(IO_StdOutput);
}

void StdIO__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    IO__init();

  }
}
