#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Listing
#include "Listing.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

BOOLEAN Errors_NoReports;
BOOLEAN Errors_InError;
Errors_tSaveProc Errors_SaveProc;
Errors_tWriteProc Errors_WriteProc;
BITSET Errors_ReportClass;
struct Errors_1 Errors_ErrorTable;

#define cTab   '\t'
#define NoStringRef   -1
#define cESC   '\\'
#define cSEP   '$'
static Errors_tReportMode ReportMode;
static struct S_1 {
    SHORTCARD A[Errors_MaxErrorClass + 1];
} ErrorCount;
static struct S_2 {
    StringMem_tStringRef A[Errors_MaxErrorClass + 1];
} ErrorClassRef;
static struct S_3 {
    StringMem_tStringRef A[Errors_MaxCode + 1];
} ErrorCodeRef;
static struct S_4 {
    StringMem_tStringRef A[Errors_MaxErrorClass + 1];
} ErrorCountRef;
static INTEGER i;
static void WriteErrorMessage ARGS((INTEGER ErrorCode, INTEGER ErrorClass, INTEGER Line, INTEGER Column, INTEGER InfoClass, ADDRESS Info));
static void SplitLine ARGS((Strings_tString C_1_line, INTEGER *i, Strings_tString *s1));
static void Finish ARGS(());


void Errors_ErrorMessage
# ifdef __STDC__
(CARDINAL ErrorCode, CARDINAL ErrorClass, Positions_tPosition Position)
# else
(ErrorCode, ErrorClass, Position)
CARDINAL ErrorCode, ErrorClass;
Positions_tPosition Position;
# endif
{
  Errors_ErrorMessageI(ErrorCode, ErrorClass, Position, (LONGCARD)Errors_eNone, (ADDRESS)NIL);
}

void Errors_ErrorMessageI
# ifdef __STDC__
(CARDINAL ErrorCode, CARDINAL ErrorClass, Positions_tPosition Position, CARDINAL InfoClass, ADDRESS Info)
# else
(ErrorCode, ErrorClass, Position, InfoClass, Info)
CARDINAL ErrorCode, ErrorClass;
Positions_tPosition Position;
CARDINAL InfoClass;
ADDRESS Info;
# endif
{
  INC(ErrorCount.A[ErrorClass]);
  if (ErrorClass <= Errors_eError) {
    Errors_InError = TRUE;
  }
  if (IN(ErrorClass, Errors_ReportClass)) {
    Errors_NoReports = FALSE;
    if (ReportMode == Errors_eDirectly) {
      WriteErrorMessage((LONGINT)ErrorCode, (LONGINT)ErrorClass, (LONGINT)Position.Line, (LONGINT)Position.Column, (LONGINT)InfoClass, Info);
      IO_WriteNl((System_tFile)IO_StdError);
    } else {
      Info = (*Errors_SaveProc)((LONGINT)InfoClass, Info);
      Listing_PutError((LONGINT)ErrorCode, (LONGINT)ErrorClass, (LONGINT)Position.Line, (LONGINT)Position.Column, (LONGINT)InfoClass, Info);
    }
  }
  if (ErrorClass < 3) {
    Finish();
  }
}

void Errors_SetReportMode
# ifdef __STDC__
(Errors_tReportMode mode)
# else
(mode)
Errors_tReportMode mode;
# endif
{
  ReportMode = mode;
  Listing_LongListing = mode == Errors_eLongListing;
}

void Errors_BeginErrors
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER i;
  IO_tFile f;
  Strings_tString s;
  Strings_tString C_2_line;

  f = IO_ReadOpen(Errors_ErrorTable.A, 256L);
  if (SysError_StatIsBad(f)) {
    Strings_ArrayToString(Errors_ErrorTable.A, 256L, &s);
    SysError_SysErrorMessageI(f, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(s));
    return;
  }
  for (;;) {
    if (IO_EndOfFile(f)) {
      goto EXIT_1;
    }
    Strings_ReadL(f, &C_2_line);
    if (Strings_Char(&C_2_line, 1) == '$') {
      goto EXIT_1;
    }
    if (Strings_Char(&C_2_line, 1) != '%') {
      SplitLine(C_2_line, &i, &s);
      if (i < 0 || i > Errors_MaxErrorClass) {
        Errors_ErrorMessageI((LONGCARD)Errors_eWrongClass, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(C_2_line));
      } else {
        ErrorClassRef.A[i] = StringMem_PutString(&s);
      }
    }
  } EXIT_1:;
  for (;;) {
    if (IO_EndOfFile(f)) {
      goto EXIT_2;
    }
    Strings_ReadL(f, &C_2_line);
    if (Strings_Char(&C_2_line, 1) == '$') {
      goto EXIT_2;
    }
    if (Strings_Char(&C_2_line, 1) != '%') {
      SplitLine(C_2_line, &i, &s);
      if (i < 0 || i > Errors_MaxCode) {
        Errors_ErrorMessageI((LONGCARD)Errors_eWrongCode, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(C_2_line));
      } else {
        ErrorCodeRef.A[i] = StringMem_PutString(&s);
      }
    }
  } EXIT_2:;
  for (;;) {
    if (IO_EndOfFile(f)) {
      goto EXIT_3;
    }
    Strings_ReadL(f, &C_2_line);
    if (Strings_Char(&C_2_line, 1) == '$') {
      goto EXIT_3;
    }
    if (Strings_Char(&C_2_line, 1) != '%') {
      SplitLine(C_2_line, &i, &s);
      if (i < 0 || i > Errors_MaxErrorClass) {
        Errors_ErrorMessageI((LONGCARD)Errors_eWrongClass, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(C_2_line));
      } else {
        ErrorCountRef.A[i] = StringMem_PutString(&s);
      }
    }
  } EXIT_3:;
  IO_ReadClose(f);
}

void Errors_CloseErrors
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER i;
  StringMem_tStringRef r;
  INTEGER ErrorCode, ErrorClass, Line, Column, InfoClass;
  ADDRESS Info;

  if (Errors_NoReports) {
    return;
  }
  while (Listing_HasError()) {
    Listing_GetError(&ErrorCode, &ErrorClass, &Line, &Column, &InfoClass, &Info);
    WriteErrorMessage(ErrorCode, ErrorClass, Line, Column, InfoClass, Info);
    IO_WriteNl((System_tFile)IO_StdError);
  }
  for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
    if (ErrorCount.A[i] > 0) {
      IO_WriteS((System_tFile)IO_StdError, (STRING)"  ", 2L);
      IO_WriteI((System_tFile)IO_StdError, (LONGINT)ErrorCount.A[i], 1L);
      IO_WriteC((System_tFile)IO_StdError, ' ');
      r = ErrorCountRef.A[i];
      if (r == NoStringRef) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"in error class ", 15L);
        IO_WriteI((System_tFile)IO_StdError, i, 1L);
      } else {
        StringMem_WriteString((System_tFile)IO_StdError, r);
      }
    }
  }
  IO_WriteNl((System_tFile)IO_StdError);
}

void Errors_ERROR
# ifdef __STDC__
(CHAR c[], LONGCARD O_1)
# else
(c, O_1)
CHAR c[];
LONGCARD O_1;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(c, O_1, CHAR)
  Strings_ArrayToString(c, O_1, &s);
  Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(s));
  FREE_OPEN_ARRAYS
}

static void WriteErrorMessage
# ifdef __STDC__
(INTEGER ErrorCode, INTEGER ErrorClass, INTEGER Line, INTEGER Column, INTEGER InfoClass, ADDRESS Info)
# else
(ErrorCode, ErrorClass, Line, Column, InfoClass, Info)
INTEGER ErrorCode;
INTEGER ErrorClass;
INTEGER Line;
INTEGER Column;
INTEGER InfoClass;
ADDRESS Info;
# endif
{
  StringMem_tStringRef r;
  Strings_tString s;
  INTEGER i, l;
  CHAR c;
  BOOLEAN ESC;

  if (ReportMode != Errors_eLongListing && Line != 0) {
    IO_WriteI((System_tFile)IO_StdError, Line, 3L);
    IO_WriteS((System_tFile)IO_StdError, (STRING)", ", 2L);
  }
  if (Column != 0) {
    IO_WriteI((System_tFile)IO_StdError, Column, 2L);
    IO_WriteS((System_tFile)IO_StdError, (STRING)": ", 2L);
  }
  if (ErrorClass > Errors_MaxErrorClass || ErrorClass < 0) {
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Error class: ", 13L);
    IO_WriteI((System_tFile)IO_StdError, ErrorClass, 1L);
  } else {
    r = ErrorClassRef.A[ErrorClass];
    if (r == NoStringRef) {
      IO_WriteS((System_tFile)IO_StdError, (STRING)"Error class: ", 13L);
      IO_WriteI((System_tFile)IO_StdError, ErrorClass, 1L);
    } else {
      StringMem_WriteString((System_tFile)IO_StdError, r);
    }
  }
  if (ErrorCode > Errors_MaxCode || ErrorCode < 0) {
    if (ErrorCode >= Errors_SysOffset) {
      IO_WriteS((System_tFile)IO_StdError, (STRING)" system error code: ", 20L);
      IO_WriteI((System_tFile)IO_StdError, ErrorCode - Errors_SysOffset, 1L);
    } else {
      IO_WriteS((System_tFile)IO_StdError, (STRING)" error code: ", 13L);
      IO_WriteI((System_tFile)IO_StdError, ErrorCode, 1L);
    }
    (*Errors_WriteProc)(InfoClass, Info);
  } else {
    r = ErrorCodeRef.A[ErrorCode];
    if (r == NoStringRef) {
      if (ErrorCode >= Errors_SysOffset) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)" system error code: ", 20L);
        IO_WriteI((System_tFile)IO_StdError, ErrorCode - Errors_SysOffset, 1L);
      } else {
        IO_WriteS((System_tFile)IO_StdError, (STRING)" error code: ", 13L);
        IO_WriteI((System_tFile)IO_StdError, ErrorCode, 1L);
      }
      (*Errors_WriteProc)(InfoClass, Info);
    } else {
      StringMem_GetString(r, &s);
      l = Strings_Length(&s);
      i = 0;
      ESC = FALSE;
      for (;;) {
        INC(i);
        if (i > l) {
          goto EXIT_4;
        }
        c = Strings_Char(&s, (Strings_tStringIndex)i);
        if (ESC) {
          IO_WriteC((System_tFile)IO_StdError, c);
          ESC = FALSE;
        } else if (c == cESC) {
          ESC = TRUE;
        } else if (c == cSEP) {
          goto EXIT_4;
        } else {
          IO_WriteC((System_tFile)IO_StdError, c);
        }
      } EXIT_4:;
      (*Errors_WriteProc)(InfoClass, Info);
      for (;;) {
        INC(i);
        if (i > l) {
          goto EXIT_5;
        }
        c = Strings_Char(&s, (Strings_tStringIndex)i);
        if (ESC) {
          IO_WriteC((System_tFile)IO_StdError, c);
          ESC = FALSE;
        } else if (c == cESC) {
          ESC = TRUE;
        } else {
          IO_WriteC((System_tFile)IO_StdError, c);
        }
      } EXIT_5:;
    }
  }
}

static void SplitLine
# ifdef __STDC__
(Strings_tString C_1_line, INTEGER *i, Strings_tString *s1)
# else
(C_1_line, i, s1)
Strings_tString C_1_line;
INTEGER *i;
Strings_tString *s1;
# endif
{
  INTEGER m, p1, p2;
  Strings_tString s;

  p1 = 1;
  p2 = 1;
  m = Strings_Length(&C_1_line);
  for (;;) {
    if (p2 > m) {
      goto EXIT_6;
    }
    if (Strings_Char(&C_1_line, (Strings_tStringIndex)p2) == cTab) {
      goto EXIT_6;
    }
    INC(p2);
  } EXIT_6:;
  DEC(p2);
  if (p1 > p2) {
    *i = 0;
  } else {
    Strings_SubString(&C_1_line, (Strings_tStringIndex)p1, (Strings_tStringIndex)p2, &s);
    *i = Strings_StringToInt(&s);
  }
  p1 = p2 + 1;
  for (;;) {
    if (p1 > m) {
      goto EXIT_7;
    }
    if (Strings_Char(&C_1_line, (Strings_tStringIndex)p1) != cTab) {
      goto EXIT_7;
    }
    INC(p1);
  } EXIT_7:;
  p2 = p1;
  for (;;) {
    if (p2 > m) {
      goto EXIT_8;
    }
    if (Strings_Char(&C_1_line, (Strings_tStringIndex)p2) == cTab) {
      goto EXIT_8;
    }
    INC(p2);
  } EXIT_8:;
  DEC(p2);
  if (p1 > p2) {
    Strings_AssignEmpty(s1);
  } else {
    Strings_SubString(&C_1_line, (Strings_tStringIndex)p1, (Strings_tStringIndex)p2, s1);
  }
}

static void Finish
# ifdef __STDC__
()
# else
()
# endif
{
  Errors_CloseErrors();
  IO_CloseIO();
  if (ReportMode == Errors_eDirectly) {
    switch (0) {
    }
  }
  Exit(1L);
}

void Errors__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Positions__init();
    IO__init();
    Listing__init();
    Strings__init();
    StringMem__init();
    SysError__init();
    System__init();
    Positions__init();
    Strings__init();

    Errors_NoReports = TRUE;
    Errors_InError = FALSE;
    ReportMode = Errors_eShortListing;
    (void)strncpy((char *)Errors_ErrorTable.A, "ErrorTab", sizeof(Errors_ErrorTable.A));
    Errors_ReportClass = SET_cRNG(0, Errors_MaxErrorClass);
    for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
      ErrorCount.A[i] = 0;
    }
    for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
      ErrorClassRef.A[i] = NoStringRef;
    }
    for (i = 0; i <= Errors_MaxCode; i += 1) {
      ErrorCodeRef.A[i] = NoStringRef;
    }
    for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
      ErrorCountRef.A[i] = NoStringRef;
    }
  }
}
