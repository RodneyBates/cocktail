#include "SYSTEM_.h"

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Convert
#include "Convert.h"
#endif




ADDRESS Convert_IdToAdr
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  CARDINAL c;

  c = id;
  return (ADDRESS)c;
}

Idents_tIdent Convert_AdrToId
# ifdef __STDC__
(ADDRESS adr)
# else
(adr)
ADDRESS adr;
# endif
{
  CARDINAL c;

  c = (CARDINAL)adr;
  return c;
}

void Convert__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    Idents__init();

  }
}
