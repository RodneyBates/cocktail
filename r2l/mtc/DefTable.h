#define DEFINITION_DefTable

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#define DefTable_NoDef   0
typedef LONGINT DefTable_DefRange;
#define DefTable_NoKind        0
#define DefTable_Ident        1
#define DefTable_Start        2
typedef unsigned char DefTable_tKind;
extern DefTable_DefRange DefTable_DefCount;
extern void DefTable_MakeIdentDef ARGS((Idents_tIdent pIdent));
extern void DefTable_MakeStartDef ARGS((Idents_tIdent pIdent));
extern DefTable_DefRange DefTable_GetDef ARGS((Idents_tIdent pIdent));
extern DefTable_tKind DefTable_GetKind ARGS((DefTable_DefRange pDef));
extern void DefTable__init();
