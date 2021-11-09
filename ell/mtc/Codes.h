#define DEFINITION_Codes

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#define Codes_cNoIndex   -1
extern INTEGER Codes_vMaxRecSetIndex, Codes_vMaxSetIndex, Codes_EmptyRecSetIndex;
typedef INTEGER Codes_tCode;
extern void Codes_SetCode ARGS((Idents_tIdent term, Codes_tCode code));
extern Codes_tCode Codes_Code ARGS((Idents_tIdent term));
extern Idents_tIdent Codes_Term ARGS((Codes_tCode code));
extern BOOLEAN Codes_IsCoded ARGS((Idents_tIdent term));
extern BOOLEAN Codes_IsCode ARGS((Codes_tCode code));
extern void Codes_SetDefCode ARGS((Idents_tIdent term));
extern Codes_tCode Codes_MaxCode ARGS(());
extern INTEGER Codes_RecSetIndex ARGS((Sets_tSet set));
extern INTEGER Codes_SetIndex ARGS((Sets_tSet set));
extern void Codes_GetRecSet ARGS((INTEGER index, Sets_tSet *set));
extern void Codes_GetSet ARGS((INTEGER index, Sets_tSet *set));
extern void Codes_WriteIndex ARGS((IO_tFile f, INTEGER index));
extern void Codes_WriteRecIndex ARGS((IO_tFile f, INTEGER index));
extern void Codes__init();
