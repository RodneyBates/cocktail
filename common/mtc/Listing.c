#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Listing
#include "Listing.h"
#endif

IO_tFile Listing_SourceFile;
IO_tFile Listing_ListFile;
BOOLEAN Listing_LongListing;

#define ColFlag   '^'
#define LineFlag   '@'
typedef struct S_1 *tErrPtr;
typedef struct S_1 {
    SHORTINT code, class;
    SHORTINT C_0_line, column;
    SHORTINT infcl;
    ADDRESS info;
    tErrPtr next;
} tErrElmt;
static tErrPtr start, stop, last, read;
static INTEGER SourceLine;


void Listing_PutError
# ifdef __STDC__
(INTEGER Code, INTEGER Class, INTEGER Line, INTEGER Column, INTEGER InfoClass, ADDRESS Info)
# else
(Code, Class, Line, Column, InfoClass, Info)
INTEGER Code, Class, Line, Column, InfoClass;
ADDRESS Info;
# endif
{
  tErrPtr err;

  err = (tErrPtr)Memory_Alloc((LONGINT)sizeof(tErrElmt));
  {
    register tErrElmt *W_1 = err;

    W_1->code = Code;
    W_1->class = Class;
    W_1->C_0_line = Line;
    W_1->column = Column;
    W_1->infcl = InfoClass;
    W_1->info = Info;
  }
  if (start == NIL) {
    start = err;
    read = err;
    stop = err;
    err->next = NIL;
    last = err;
  } else if (Line < start->C_0_line || Line == start->C_0_line && Column < start->column) {
    err->next = start;
    start = err;
    read = err;
  } else {
    if (Line > stop->C_0_line || Line == stop->C_0_line && Column >= stop->column) {
      last = stop;
      stop = err;
    } else if (Line > last->C_0_line || Line == last->C_0_line && Column >= last->column) {
    } else {
      last = start;
    }
    while (last->next != NIL && (Line > last->next->C_0_line || Line == last->next->C_0_line && Column >= last->next->column)) {
      last = last->next;
    }
    err->next = last->next;
    last->next = err;
    last = err;
  }
}

BOOLEAN Listing_HasError
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString Buf;

  if (start == NIL) {
    if (Listing_LongListing) {
      while (!IO_EndOfFile(Listing_SourceFile)) {
        Strings_ReadL(Listing_SourceFile, &Buf);
        Strings_WriteL(Listing_ListFile, &Buf);
      }
    }
    IO_WriteC(Listing_ListFile, LineFlag);
  }
  return start != NIL;
}

void Listing_GetError
# ifdef __STDC__
(INTEGER *Code, INTEGER *Class, INTEGER *Line, INTEGER *Column, INTEGER *InfoClass, ADDRESS *Info)
# else
(Code, Class, Line, Column, InfoClass, Info)
INTEGER *Code, *Class, *Line, *Column, *InfoClass;
ADDRESS *Info;
# endif
{
  tErrPtr Next;
  INTEGER col;
  Strings_tString Buf;

  {
    register tErrElmt *W_2 = start;

    *Code = W_2->code;
    *Class = W_2->class;
    *Line = W_2->C_0_line;
    *Column = W_2->column;
    *InfoClass = W_2->infcl;
    *Info = W_2->info;
    Next = W_2->next;
  }
  if (Listing_LongListing) {
    if (read == start) {
      for (;;) {
        if (IO_EndOfFile(Listing_SourceFile)) {
          goto EXIT_1;
        }
        if (SourceLine >= *Line) {
          goto EXIT_1;
        }
        Strings_ReadL(Listing_SourceFile, &Buf);
        Strings_WriteL(Listing_ListFile, &Buf);
        INC(SourceLine);
      } EXIT_1:;
      IO_WriteC(Listing_ListFile, LineFlag);
      col = 2;
      while (read != NIL && read->C_0_line == *Line) {
        while (col < read->column) {
          IO_WriteC(Listing_ListFile, ' ');
          INC(col);
        }
        if (col == read->column) {
          IO_WriteC(Listing_ListFile, ColFlag);
          INC(col);
        }
        read = read->next;
      }
      IO_WriteNl(Listing_ListFile);
    }
    IO_WriteC(Listing_ListFile, LineFlag);
  }
  if (last == start) {
    last = Next;
  }
  if (stop == start) {
    stop = Next;
  }
  Memory_Free((LONGINT)sizeof(tErrElmt), (ADDRESS)start);
  start = Next;
}

void Listing__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    IO__init();
    Memory__init();
    Strings__init();

    start = NIL;
    read = NIL;
    stop = NIL;
    last = NIL;
    Listing_SourceFile = IO_StdInput;
    Listing_ListFile = IO_StdError;
    Listing_LongListing = FALSE;
    SourceLine = 0;
  }
}
