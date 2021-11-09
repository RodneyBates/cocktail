#include "SYSTEM_.h"

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
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

#ifndef DEFINITION_Info
#include "Info.h"
#endif


#define BitsPerBitset   32
struct S_1 {
    CHAR A[255 + 1];
};
struct S_2 {
    CHAR A[255 + 1];
};


ADDRESS Info_SaveInfo
# ifdef __STDC__
(INTEGER InfoClass, ADDRESS Info)
# else
(InfoClass, Info)
INTEGER InfoClass;
ADDRESS Info;
# endif
{
  INTEGER *InfPtrToInteger, *PtrToInteger;
  SHORTCARD *InfPtrToShort, *PtrToShort;
  LONGINT *InfPtrToLong, *PtrToLong;
  REAL *InfPtrToReal, *PtrToReal;
  BOOLEAN *InfPtrToBoolean, *PtrToBoolean;
  CHAR *InfPtrToCharacter, *PtrToCharacter;
  Strings_tString *InfPtrToString, *PtrToString;
  struct S_1 *InfPtrToArray, *PtrToArray;
  Sets_tSet *InfPtrToSet, *PtrToSet;
  Idents_tIdent *InfPtrToIdent, *PtrToIdent;

  switch (InfoClass) {
  case Errors_eInteger:;
    InfPtrToInteger = (LONGINT *)Memory_Alloc((LONGINT)sizeof(INTEGER));
    PtrToInteger = (LONGINT *)Info;
    *InfPtrToInteger = *PtrToInteger;
    return (ADDRESS)InfPtrToInteger;
    break;
  case Errors_eShort:;
    InfPtrToShort = (SHORTCARD *)Memory_Alloc((LONGINT)sizeof(SHORTCARD));
    PtrToShort = (SHORTCARD *)Info;
    *InfPtrToShort = *PtrToShort;
    return (ADDRESS)InfPtrToShort;
    break;
  case Errors_eLong:;
    InfPtrToLong = (LONGINT *)Memory_Alloc((LONGINT)sizeof(LONGINT));
    PtrToLong = (LONGINT *)Info;
    *InfPtrToLong = *PtrToLong;
    return (ADDRESS)InfPtrToLong;
    break;
  case Errors_eReal:;
    InfPtrToReal = (REAL *)Memory_Alloc((LONGINT)sizeof(REAL));
    PtrToReal = (REAL *)Info;
    *InfPtrToReal = *PtrToReal;
    return (ADDRESS)InfPtrToReal;
    break;
  case Errors_eBoolean:;
    InfPtrToBoolean = (BOOLEAN *)Memory_Alloc((LONGINT)sizeof(BOOLEAN));
    PtrToBoolean = (BOOLEAN *)Info;
    *InfPtrToBoolean = *PtrToBoolean;
    return (ADDRESS)InfPtrToBoolean;
    break;
  case Errors_eCharacter:;
    InfPtrToCharacter = (CHAR *)Memory_Alloc((LONGINT)sizeof(CHAR));
    PtrToCharacter = (CHAR *)Info;
    *InfPtrToCharacter = *PtrToCharacter;
    return (ADDRESS)InfPtrToCharacter;
    break;
  case Errors_eString:;
    InfPtrToString = (Strings_tString *)Memory_Alloc((LONGINT)sizeof(Strings_tString));
    PtrToString = (Strings_tString *)Info;
    Strings_Assign(InfPtrToString, PtrToString);
    return (ADDRESS)InfPtrToString;
    break;
  case Errors_eArray:;
    InfPtrToArray = (struct S_1 *)Memory_Alloc(256L);
    PtrToArray = (struct S_1 *)Info;
    *InfPtrToArray = *PtrToArray;
    return (ADDRESS)InfPtrToArray;
    break;
  case Errors_eIdent:;
    InfPtrToIdent = (SHORTCARD *)Memory_Alloc((LONGINT)sizeof(Idents_tIdent));
    PtrToIdent = (SHORTCARD *)Info;
    *InfPtrToIdent = *PtrToIdent;
    return (ADDRESS)InfPtrToIdent;
    break;
  case Errors_eIdentSet:;
    InfPtrToSet = (Sets_tSet *)Memory_Alloc((LONGINT)sizeof(Sets_tSet));
    PtrToSet = (Sets_tSet *)Info;
    Sets_MakeSet(InfPtrToSet, Sets_Size(PtrToSet));
    Sets_Assign(InfPtrToSet, *PtrToSet);
    return (ADDRESS)InfPtrToSet;
    break;
  default :
    return (ADDRESS)NIL;
    break;
  }
}

void Info_WriteInfo
# ifdef __STDC__
(INTEGER InfoClass, ADDRESS Info)
# else
(InfoClass, Info)
INTEGER InfoClass;
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
  struct S_2 *PtrToArray;
  Sets_tSet *PtrToSet;
  Idents_tIdent *PtrToIdent;

  if (InfoClass == Errors_eNone) {
    return;
  }
  switch (InfoClass) {
  case Errors_eInteger:;
    PtrToInteger = (LONGINT *)Info;
    IO_WriteI((System_tFile)IO_StdError, *PtrToInteger, 0L);
    break;
  case Errors_eShort:;
    PtrToShort = (SHORTCARD *)Info;
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)(*PtrToShort), 0L);
    break;
  case Errors_eLong:;
    PtrToLong = (LONGINT *)Info;
    IO_WriteLong((System_tFile)IO_StdError, *PtrToLong, 0L);
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
    PtrToArray = (struct S_2 *)Info;
    IO_WriteS((System_tFile)IO_StdError, (*PtrToArray).A, 256L);
    break;
  case Errors_eIdent:;
    PtrToIdent = (SHORTCARD *)Info;
    Idents_WriteIdent((System_tFile)IO_StdError, *PtrToIdent);
    break;
  case Errors_eIdentSet:;
    PtrToSet = (Sets_tSet *)Info;
    Info_WriteIdentSet((System_tFile)IO_StdError, *PtrToSet);
    break;
  default :
    IO_WriteS((System_tFile)IO_StdError, (STRING)"info class: ", 12L);
    IO_WriteI((System_tFile)IO_StdError, InfoClass, 0L);
    break;
  }
}

void Info_WriteIdentSet
# ifdef __STDC__
(IO_tFile f, Sets_tSet s)
# else
(f, s)
IO_tFile f;
Sets_tSet s;
# endif
{
  Sets_tSet h;

  Sets_MakeSet(&h, Sets_Size(&s));
  Sets_Assign(&h, s);
  while (!Sets_IsEmpty(h)) {
    IO_WriteC(f, ' ');
    Idents_WriteIdent(f, (SHORTCARD)Sets_Extract(&h));
  }
  Sets_ReleaseSet(&h);
}

void Info__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Sets__init();
    Strings__init();
    Errors__init();
    Idents__init();
    IO__init();
    Memory__init();
    Sets__init();
    Strings__init();

  }
}
