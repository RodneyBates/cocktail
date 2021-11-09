#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Listing
#include "Listing.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
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

struct Errors_1 Errors_ErrorCount;
BITSET Errors_ReportClass;
struct Errors_2 Errors_ErrorTable;

#define eNone   0
#define cTab   '\t'
#define NoStringRef   -1
#define MaxCode   160
#define eWrongClass   16
#define eWrongCode   17
static BOOLEAN NoReports;
static Errors_tReportMode ReportMode;
static struct S_1 {
    StringMem_tStringRef A[Errors_MaxErrorClass + 1];
} ErrorClassRef;
static struct S_2 {
    StringMem_tStringRef A[MaxCode + 1];
} ErrorCodeRef;
static struct S_3 {
    StringMem_tStringRef A[Errors_MaxErrorClass + 1];
} ErrorCountRef;
static CARDINAL i;
static void WriteErrorMessage ARGS((CARDINAL ErrorCode, CARDINAL ErrorClass, CARDINAL Line, CARDINAL Column));
static void KeepInfo ARGS((CARDINAL InfoClass, ADDRESS *Info));
struct S_4 {
    CHAR A[255 + 1];
};
static void WriteInfo ARGS((CARDINAL InfoClass, ADDRESS Info));
struct S_5 {
    CHAR A[255 + 1];
};
static void WriteTermSet ARGS((IO_tFile f, Sets_tSet s));
static void SplitLine ARGS((Strings_tString C_1_line, CARDINAL *i, Strings_tString *s1));
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
  Errors_ErrorMessageI(ErrorCode, ErrorClass, Position, (LONGCARD)eNone, (ADDRESS)NIL);
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
  INC(Errors_ErrorCount.A[ErrorClass]);
  if (IN(ErrorClass, Errors_ReportClass)) {
    NoReports = FALSE;
    if (ReportMode == Errors_eImmediate) {
      WriteErrorMessage(ErrorCode, ErrorClass, (LONGCARD)Position.Line, (LONGCARD)Position.Column);
      WriteInfo(InfoClass, Info);
      IO_WriteNl((System_tFile)IO_StdError);
    } else {
      KeepInfo(InfoClass, &Info);
      Listing_PutError(ErrorCode, ErrorClass, (LONGCARD)Position.Line, (LONGCARD)Position.Column, InfoClass, Info);
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
  switch (ReportMode) {
  case Errors_eListing:;
    Listing_ListMode = Listing_Listing;
    break;
  default :
    Listing_ListMode = Listing_NoListing;
    break;
  }
}

void Errors_BeginErrors
# ifdef __STDC__
()
# else
()
# endif
{
  CARDINAL i;
  IO_tFile f;
  Strings_tString s;
  Strings_tString C_2_line;

  f = IO_ReadOpen(Errors_ErrorTable.A, 256L);
  if (SysError_StatIsBad(f)) {
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Fatal error: cannot open ", 25L);
    IO_WriteS((System_tFile)IO_StdError, Errors_ErrorTable.A, 256L);
    IO_WriteNl((System_tFile)IO_StdError);
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
        Errors_ErrorMessageI((LONGCARD)eWrongClass, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(C_2_line));
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
      if (i < 0 || i > MaxCode) {
        Errors_ErrorMessageI((LONGCARD)eWrongCode, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(C_2_line));
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
        Errors_ErrorMessageI((LONGCARD)eWrongClass, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(C_2_line));
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
  CARDINAL i;
  StringMem_tStringRef r;
  CARDINAL ErrorCode, ErrorClass, Line, Column, InfoClass;
  ADDRESS Info;

  if (NoReports) {
    return;
  }
  while (Listing_HasError()) {
    Listing_GetError(&ErrorCode, &ErrorClass, &Line, &Column, &InfoClass, &Info);
    WriteErrorMessage(ErrorCode, ErrorClass, Line, Column);
    WriteInfo(InfoClass, Info);
    IO_WriteNl((System_tFile)IO_StdError);
  }
  for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
    if (Errors_ErrorCount.A[i] > 0) {
      IO_WriteS((System_tFile)IO_StdError, (STRING)"  ", 2L);
      IO_WriteI((System_tFile)IO_StdError, (LONGINT)Errors_ErrorCount.A[i], 1L);
      IO_WriteC((System_tFile)IO_StdError, ' ');
      r = ErrorCountRef.A[i];
      if (r == NoStringRef) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)"in error class ", 15L);
        IO_WriteI((System_tFile)IO_StdError, (LONGINT)i, 1L);
      } else {
        StringMem_WriteString((System_tFile)IO_StdError, r);
      }
    }
  }
  IO_WriteNl((System_tFile)IO_StdError);
}

static void WriteErrorMessage
# ifdef __STDC__
(CARDINAL ErrorCode, CARDINAL ErrorClass, CARDINAL Line, CARDINAL Column)
# else
(ErrorCode, ErrorClass, Line, Column)
CARDINAL ErrorCode, ErrorClass, Line, Column;
# endif
{
  StringMem_tStringRef r;

  if (ReportMode != Errors_eListing && Line != 0) {
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)Line, 3L);
    IO_WriteS((System_tFile)IO_StdError, (STRING)", ", 2L);
  }
  if (Column != 0) {
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)Column, 2L);
    IO_WriteS((System_tFile)IO_StdError, (STRING)": ", 2L);
  }
  if (ErrorClass > Errors_MaxErrorClass || ErrorClass < 0) {
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Error class: ", 13L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)ErrorClass, 1L);
  } else {
    r = ErrorClassRef.A[ErrorClass];
    if (r == NoStringRef) {
      IO_WriteS((System_tFile)IO_StdError, (STRING)"Error class: ", 13L);
      IO_WriteI((System_tFile)IO_StdError, (LONGINT)ErrorClass, 1L);
    } else {
      StringMem_WriteString((System_tFile)IO_StdError, r);
    }
  }
  if (ErrorCode > MaxCode || ErrorCode < 0) {
    if (ErrorCode >= Errors_SysOffset) {
      IO_WriteS((System_tFile)IO_StdError, (STRING)" system error code: ", 20L);
      IO_WriteI((System_tFile)IO_StdError, (LONGINT)(ErrorCode - Errors_SysOffset), 1L);
    } else {
      IO_WriteS((System_tFile)IO_StdError, (STRING)" error code: ", 13L);
      IO_WriteI((System_tFile)IO_StdError, (LONGINT)ErrorCode, 1L);
    }
  } else {
    r = ErrorCodeRef.A[ErrorCode];
    if (r == NoStringRef) {
      if (ErrorCode >= Errors_SysOffset) {
        IO_WriteS((System_tFile)IO_StdError, (STRING)" system error code: ", 20L);
        IO_WriteI((System_tFile)IO_StdError, (LONGINT)(ErrorCode - Errors_SysOffset), 1L);
      } else {
        IO_WriteS((System_tFile)IO_StdError, (STRING)" error code: ", 13L);
        IO_WriteI((System_tFile)IO_StdError, (LONGINT)ErrorCode, 1L);
      }
    } else {
      StringMem_WriteString((System_tFile)IO_StdError, r);
    }
  }
}

static void KeepInfo
# ifdef __STDC__
(CARDINAL InfoClass, ADDRESS *Info)
# else
(InfoClass, Info)
CARDINAL InfoClass;
ADDRESS *Info;
# endif
{
  INTEGER *InfPtrToInteger, *PtrToInteger;
  SHORTCARD *InfPtrToShort, *PtrToShort;
  LONGINT *InfPtrToLong, *PtrToLong;
  REAL *InfPtrToReal, *PtrToReal;
  BOOLEAN *InfPtrToBoolean, *PtrToBoolean;
  CHAR *InfPtrToCharacter, *PtrToCharacter;
  Strings_tString *InfPtrToString, *PtrToString;
  struct S_4 *InfPtrToArray, *PtrToArray;
  Sets_tSet *InfPtrToSet, *PtrToSet;
  Idents_tIdent *InfPtrToIdent, *PtrToIdent;

  if (InfoClass == eNone) {
    return;
  }
  switch (InfoClass) {
  case Errors_eInteger:;
    InfPtrToInteger = (LONGINT *)Memory_Alloc((LONGINT)sizeof(INTEGER));
    PtrToInteger = (LONGINT *)(*Info);
    *InfPtrToInteger = *PtrToInteger;
    *Info = (ADDRESS)InfPtrToInteger;
    break;
  case Errors_eShort:;
    InfPtrToShort = (SHORTCARD *)Memory_Alloc((LONGINT)sizeof(SHORTCARD));
    PtrToShort = (SHORTCARD *)(*Info);
    *InfPtrToShort = *PtrToShort;
    *Info = (ADDRESS)InfPtrToShort;
    break;
  case Errors_eLong:;
    InfPtrToLong = (LONGINT *)Memory_Alloc((LONGINT)sizeof(LONGINT));
    PtrToLong = (LONGINT *)(*Info);
    *InfPtrToLong = *PtrToLong;
    *Info = (ADDRESS)InfPtrToLong;
    break;
  case Errors_eReal:;
    InfPtrToReal = (REAL *)Memory_Alloc((LONGINT)sizeof(REAL));
    PtrToReal = (REAL *)(*Info);
    *InfPtrToReal = *PtrToReal;
    *Info = (ADDRESS)InfPtrToReal;
    break;
  case Errors_eBoolean:;
    InfPtrToBoolean = (BOOLEAN *)Memory_Alloc((LONGINT)sizeof(BOOLEAN));
    PtrToBoolean = (BOOLEAN *)(*Info);
    *InfPtrToBoolean = *PtrToBoolean;
    *Info = (ADDRESS)InfPtrToBoolean;
    break;
  case Errors_eCharacter:;
    InfPtrToCharacter = (CHAR *)Memory_Alloc((LONGINT)sizeof(CHAR));
    PtrToCharacter = (CHAR *)(*Info);
    *InfPtrToCharacter = *PtrToCharacter;
    *Info = (ADDRESS)InfPtrToCharacter;
    break;
  case Errors_eString:;
    InfPtrToString = (Strings_tString *)Memory_Alloc((LONGINT)sizeof(Strings_tString));
    PtrToString = (Strings_tString *)(*Info);
    Strings_Assign(InfPtrToString, PtrToString);
    *Info = (ADDRESS)InfPtrToString;
    break;
  case Errors_eArray:;
    InfPtrToArray = (struct S_4 *)Memory_Alloc(256L);
    PtrToArray = (struct S_4 *)(*Info);
    *InfPtrToArray = *PtrToArray;
    *Info = (ADDRESS)InfPtrToArray;
    break;
  case Errors_eIdent:;
    InfPtrToIdent = (SHORTCARD *)Memory_Alloc((LONGINT)sizeof(Idents_tIdent));
    PtrToIdent = (SHORTCARD *)(*Info);
    *InfPtrToIdent = *PtrToIdent;
    *Info = (ADDRESS)InfPtrToIdent;
    break;
  case Errors_eTermSet:;
    InfPtrToSet = (Sets_tSet *)Memory_Alloc((LONGINT)sizeof(Sets_tSet));
    PtrToSet = (Sets_tSet *)(*Info);
    Sets_MakeSet(InfPtrToSet, (Sets_tElement)PtrToSet->MaxElmt);
    Sets_Assign(InfPtrToSet, *PtrToSet);
    *Info = (ADDRESS)InfPtrToSet;
    break;
  default :
    break;
  }
}

static void WriteInfo
# ifdef __STDC__
(CARDINAL InfoClass, ADDRESS Info)
# else
(InfoClass, Info)
CARDINAL InfoClass;
ADDRESS Info;
# endif
{
  INTEGER *PtrToInteger;
  SHORTCARD *PtrToShort;
  LONGINT *PtrToLong;
  REAL *PtrToReal;
  BOOLEAN *PtrToBoolean;
  CHAR *PtrToCharacter;
  Strings_tString *PtrToString;
  struct S_5 *PtrToArray;
  Sets_tSet *PtrToSet;
  Idents_tIdent *PtrToIdent;

  if (InfoClass == eNone) {
    return;
  }
  IO_WriteC((System_tFile)IO_StdError, ' ');
  switch (InfoClass) {
  case Errors_eInteger:;
    PtrToInteger = (LONGINT *)Info;
    IO_WriteI((System_tFile)IO_StdError, *PtrToInteger, 1L);
    break;
  case Errors_eShort:;
    PtrToShort = (SHORTCARD *)Info;
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)(*PtrToShort), 1L);
    break;
  case Errors_eLong:;
    PtrToLong = (LONGINT *)Info;
    IO_WriteLong((System_tFile)IO_StdError, *PtrToLong, 1L);
    break;
  case Errors_eReal:;
    PtrToReal = (REAL *)Info;
    IO_WriteR((System_tFile)IO_StdError, *PtrToReal, 1L, 10L, 1L);
    break;
  case Errors_eBoolean:;
    PtrToBoolean = (BOOLEAN *)Info;
    IO_WriteB((System_tFile)IO_StdError, *PtrToBoolean);
    break;
  case Errors_eCharacter:;
    PtrToCharacter = (CHAR *)Info;
    IO_WriteC((System_tFile)IO_StdError, *PtrToCharacter);
    break;
  case Errors_eString:;
    PtrToString = (Strings_tString *)Info;
    Strings_WriteS((System_tFile)IO_StdError, PtrToString);
    break;
  case Errors_eArray:;
    PtrToArray = (struct S_5 *)Info;
    IO_WriteS((System_tFile)IO_StdError, (*PtrToArray).A, 256L);
    break;
  case Errors_eIdent:;
    PtrToIdent = (SHORTCARD *)Info;
    Idents_WriteIdent((System_tFile)IO_StdError, *PtrToIdent);
    break;
  case Errors_eTermSet:;
    PtrToSet = (Sets_tSet *)Info;
    WriteTermSet((System_tFile)IO_StdError, *PtrToSet);
    break;
  default :
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Info Class: ", 12L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)InfoClass, 1L);
    break;
  }
}

static void WriteTermSet
# ifdef __STDC__
(IO_tFile f, Sets_tSet s)
# else
(f, s)
IO_tFile f;
Sets_tSet s;
# endif
{
  CARDINAL i;
  TokenTab_TokenError Error;

  {
    LONGCARD B_1 = 0, B_2 = TokenTab_MAXTerm;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        if (Sets_IsElement(i, &s)) {
          IO_WriteS(f, (STRING)" ", 1L);
          Idents_WriteIdent(f, TokenTab_TokenToSymbol((TokenTab_Vocabulary)i, &Error));
        }
        if (i >= B_2) break;
      }
  }
}

static void SplitLine
# ifdef __STDC__
(Strings_tString C_1_line, CARDINAL *i, Strings_tString *s1)
# else
(C_1_line, i, s1)
Strings_tString C_1_line;
CARDINAL *i;
Strings_tString *s1;
# endif
{
  CARDINAL m, p1, p2;
  Strings_tString s;

  p1 = 1;
  p2 = 1;
  m = Strings_Length(&C_1_line);
  for (;;) {
    if (p2 > m) {
      goto EXIT_4;
    }
    if (Strings_Char(&C_1_line, (Strings_tStringIndex)p2) == cTab) {
      goto EXIT_4;
    }
    INC(p2);
  } EXIT_4:;
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
      goto EXIT_5;
    }
    if (Strings_Char(&C_1_line, (Strings_tStringIndex)p1) != cTab) {
      goto EXIT_5;
    }
    INC(p1);
  } EXIT_5:;
  p2 = p1;
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
    Memory__init();
    Sets__init();
    Strings__init();
    StringMem__init();
    Idents__init();
    SysError__init();
    System__init();
    TokenTab__init();
    Positions__init();
    Strings__init();

    NoReports = TRUE;
    ReportMode = Errors_eNoListing;
    (void)strncpy((char *)Errors_ErrorTable.A, "ErrorTab", sizeof(Errors_ErrorTable.A));
    Errors_ReportClass = SET_cRNG(0, Errors_MaxErrorClass);
    for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
      Errors_ErrorCount.A[i] = 0;
    }
    for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
      ErrorClassRef.A[i] = NoStringRef;
    }
    for (i = 0; i <= MaxCode; i += 1) {
      ErrorCodeRef.A[i] = NoStringRef;
    }
    for (i = 0; i <= Errors_MaxErrorClass; i += 1) {
      ErrorCountRef.A[i] = NoStringRef;
    }
  }
}
