#define DEFINITION_Patterns

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Stack
#include "Stack.h"
#endif

#define Patterns_infinite   10000
#define Patterns_ePattern   13
#define Patterns_cIndependent        0
#define Patterns_cInconsistent        1
#define Patterns_cSubsumes        2
#define Patterns_cSupersumes        3
#define Patterns_cEqual        4
typedef unsigned char Patterns_tRelation;
typedef struct Patterns_2 *Patterns_tPattern;
typedef struct Patterns_1 {
    Patterns_tPattern A[Patterns_infinite + 1];
} *Patterns_tSons;
typedef struct Patterns_2 {
    Idents_tIdent Ident;
    Sets_tSet Classes;
    Patterns_tSons Sons;
} Patterns_tPatternR;
extern Patterns_tPattern Patterns_MakePattern ARGS((Idents_tIdent id));
extern void Patterns_SetPatternSon ARGS((Patterns_tPattern pat, INTEGER pos, Patterns_tPattern son));
extern void Patterns_ReleasePattern ARGS((Patterns_tPattern *pat));
extern Patterns_tPattern Patterns_GetPatternSon ARGS((Patterns_tPattern pat, INTEGER pos));
extern Idents_tIdent Patterns_GetPatternId ARGS((Patterns_tPattern pat));
extern void Patterns_PatternClasses ARGS((Patterns_tPattern pat, Sets_tSet *classes));
extern Patterns_tPattern Patterns_NormPattern ARGS((Patterns_tPattern pat));
extern Patterns_tRelation Patterns_Relation ARGS((Patterns_tPattern pat1, Patterns_tPattern pat2));
extern BOOLEAN Patterns_IsEqual ARGS((Patterns_tPattern pat1, Patterns_tPattern pat2));
extern void Patterns_ResetExtendPos ARGS(());
extern Patterns_tPattern Patterns_ExtendPos ARGS(());
extern void Patterns_Extend ARGS((Patterns_tPattern pat1, Patterns_tPattern pos, Queues_tQueue *pats));
extern void Patterns_SynthesizePatterns ARGS((Idents_tIdent class, Stack_tStack *pats));
extern Patterns_tPattern Patterns_CopyPattern ARGS((Patterns_tPattern pat));
extern void Patterns_WritePattern ARGS((IO_tFile f, Patterns_tPattern p));
extern void Patterns__init();
