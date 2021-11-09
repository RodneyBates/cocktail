#define DEFINITION_Convert

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

extern ADDRESS Convert_IdToAdr ARGS((Idents_tIdent id));
extern Idents_tIdent Convert_AdrToId ARGS((ADDRESS adr));
extern void Convert__init();
