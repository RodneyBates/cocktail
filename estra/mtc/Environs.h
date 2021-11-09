#define DEFINITION_Environs

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

typedef INTEGER Environs_tDirNo;
typedef struct Environs_1 *Environs_tFunction;
typedef struct Environs_1 {
    Idents_tIdent Name;
    Queues_tQueue Pats;
    Sets_tSet Domain;
} Environs_tFunctionR;
extern Environs_tFunction Environs_MakeFunctEnv ARGS((Idents_tIdent name, Sets_tSet doamin));
extern BOOLEAN Environs_InDomain ARGS((Idents_tIdent name, Patterns_tPattern pat));
extern Environs_tDirNo Environs_MakeDirective ARGS((Environs_tFunction funct));
extern void Environs_GetPatterns ARGS((Environs_tFunction funct, Queues_tQueue *pats));
extern void Environs_GetCondPatterns ARGS((Environs_tFunction funct, Queues_tQueue *pats));
extern Environs_tDirNo Environs_MaxDirective ARGS(());
extern void Environs_SetPattern ARGS((Environs_tDirNo no, Patterns_tPattern pat));
extern void Environs_SetCondPattern ARGS((Environs_tDirNo no, Patterns_tPattern pat));
extern Patterns_tPattern Environs_GetPattern ARGS((Environs_tDirNo no));
extern void Environs_DefineAccess ARGS((Environs_tDirNo no, Queues_tQueue path, Idents_tIdent sel, Idents_tIdent ident, BOOLEAN sure));
extern void Environs_DefineSelPat ARGS((Environs_tDirNo no, Idents_tIdent sel, Patterns_tPattern pat));
extern BOOLEAN Environs_Defined ARGS((Environs_tDirNo no, Idents_tIdent sel));
extern Patterns_tPattern Environs_SelPattern ARGS((Environs_tDirNo no, Idents_tIdent sel));
extern void Environs_CallFunction ARGS((Environs_tDirNo no, Idents_tIdent sel, Idents_tIdent name));
extern BOOLEAN Environs_HeadCalled ARGS((Environs_tDirNo no));
extern BOOLEAN Environs_IsHead ARGS((Environs_tDirNo no, Idents_tIdent sel));
extern INTEGER Environs_MaxCalls ARGS(());
extern void Environs_WritePath ARGS((IO_tFile f, Environs_tDirNo no, Idents_tIdent sel));
extern void Environs_WriteAccess ARGS((IO_tFile f, Environs_tDirNo no, Idents_tIdent sel));
extern BOOLEAN Environs_AlwaysMatch ARGS((Environs_tDirNo no, Idents_tIdent node));
extern BOOLEAN Environs_HasCondition ARGS((Environs_tDirNo no));
extern void Environs_WriteMatch ARGS((IO_tFile f, Environs_tDirNo no, INTEGER margin, Idents_tIdent GrammarName));
extern void Environs_WriteCost ARGS((IO_tFile f, Environs_tDirNo no, INTEGER margin));
extern void Environs__init();
