#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
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


#define IdentUndefined   10
#define ImproperUse   11
#define IdentDefBefore   12
#define BraceMissing   13
#define UnclosedComment   14
#define PatternNoMatch   15
static void WriteErrorMessage ARGS((CARDINAL ErrorCode, CARDINAL ErrorClass, Positions_tPosition Position));
static void WriteInfo ARGS((CARDINAL InfoClass, ADDRESS Info));
struct S_1 {
    CHAR A[1023 + 1];
};


void Errors_ErrorMessage
# ifdef __STDC__
(CARDINAL ErrorCode, CARDINAL ErrorClass, Positions_tPosition Position)
# else
(ErrorCode, ErrorClass, Position)
CARDINAL ErrorCode, ErrorClass;
Positions_tPosition Position;
# endif
{
  Errors_ErrorMessageI(ErrorCode, ErrorClass, Position, (LONGCARD)Errors_None, (ADDRESS)NIL);
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
  WriteErrorMessage(ErrorCode, ErrorClass, Position);
  WriteInfo(InfoClass, Info);
  IO_WriteNl((System_tFile)IO_StdError);
  if (ErrorClass == Errors_Fatal) {
    IO_CloseIO();
    exit(1);
  }
}

static void WriteErrorMessage
# ifdef __STDC__
(CARDINAL ErrorCode, CARDINAL ErrorClass, Positions_tPosition Position)
# else
(ErrorCode, ErrorClass, Position)
CARDINAL ErrorCode, ErrorClass;
Positions_tPosition Position;
# endif
{
  Positions_WritePosition((System_tFile)IO_StdError, Position);
  IO_WriteS((System_tFile)IO_StdError, (STRING)": ", 2L);
  switch (ErrorClass) {
  case Errors_Fatal:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Fatal       ", 12L);
    break;
  case Errors_Restriction:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Restriction ", 12L);
    break;
  case Errors_Error:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Error       ", 12L);
    break;
  case Errors_Warning:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Warning     ", 12L);
    break;
  case Errors_Repair:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Repair      ", 12L);
    break;
  case Errors_Note:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Note        ", 12L);
    break;
  case Errors_Information:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Information ", 12L);
    break;
  default :
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Error class: ", 13L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)ErrorClass, 0L);
    break;
  }
  switch (ErrorCode) {
  case Errors_NoText:;
    break;
  case Errors_SyntaxError:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"syntax error", 12L);
    break;
  case Errors_ExpectedTokens:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"expected tokens", 15L);
    break;
  case Errors_RestartPoint:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"restart point", 13L);
    break;
  case Errors_TokenInserted:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"token inserted ", 15L);
    break;
  case Errors_WrongParseTable:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"parse table mismatch", 20L);
    break;
  case Errors_OpenParseTable:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"cannot open parse table", 23L);
    break;
  case Errors_ReadParseTable:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"cannot read parse table", 23L);
    break;
  case IdentUndefined:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"identifier undefined", 20L);
    break;
  case ImproperUse:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"improper use of identifier", 26L);
    break;
  case IdentDefBefore:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"identifier already defined", 26L);
    break;
  case BraceMissing:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"closing '}' missing", 19L);
    break;
  case UnclosedComment:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"unclosed comment", 16L);
    break;
  case PatternNoMatch:;
    IO_WriteS((System_tFile)IO_StdError, (STRING)"pattern will never match", 24L);
    break;
  default :
    IO_WriteS((System_tFile)IO_StdError, (STRING)" error code: ", 13L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)ErrorCode, 0L);
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
  struct S_1 *PtrToArray;
  Sets_tSet *PtrToSet;

  if (InfoClass == Errors_None) {
    return;
  }
  IO_WriteS((System_tFile)IO_StdError, (STRING)": ", 2L);
  switch (InfoClass) {
  case Errors_Integer:;
    PtrToInteger = (LONGINT *)Info;
    IO_WriteI((System_tFile)IO_StdError, *PtrToInteger, 0L);
    break;
  case Errors_Short:;
    PtrToShort = (SHORTCARD *)Info;
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)(*PtrToShort), 0L);
    break;
  case Errors_Long:;
    PtrToLong = (LONGINT *)Info;
    IO_WriteLong((System_tFile)IO_StdError, *PtrToLong, 0L);
    break;
  case Errors_Real:;
    PtrToReal = (REAL *)Info;
    IO_WriteR((System_tFile)IO_StdError, *PtrToReal, 1L, 10L, 1L);
    break;
  case Errors_Boolean:;
    PtrToBoolean = (BOOLEAN *)Info;
    IO_WriteB((System_tFile)IO_StdError, *PtrToBoolean);
    break;
  case Errors_Character:;
    PtrToCharacter = (CHAR *)Info;
    IO_WriteC((System_tFile)IO_StdError, *PtrToCharacter);
    break;
  case Errors_String:;
    PtrToString = (Strings_tString *)Info;
    Strings_WriteS((System_tFile)IO_StdError, PtrToString);
    break;
  case Errors_Array:;
    PtrToArray = (struct S_1 *)Info;
    IO_WriteS((System_tFile)IO_StdError, (*PtrToArray).A, 1024L);
    break;
  default :
    IO_WriteS((System_tFile)IO_StdError, (STRING)"info class: ", 12L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)InfoClass, 0L);
    break;
  }
}

void Errors__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Positions__init();
    IO__init();
    Sets__init();
    Strings__init();
    Positions__init();
    Strings__init();

  }
}
