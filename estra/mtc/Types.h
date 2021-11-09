#define DEFINITION_Types

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#define Types_cNoType        0
#define Types_cTransformation        1
#define Types_cFunction        2
#define Types_cClass        3
#define Types_cNode        4
#define Types_cNodeId        5
typedef unsigned char Types_tType;
extern void Types_BeginTypes ARGS(());
extern Types_tType Types_Type ARGS((Idents_tIdent id));
extern void Types_MakeTransformation ARGS((Idents_tIdent name));
extern void Types_MakeFunction ARGS((Idents_tIdent name));
extern void Types_MakeClass ARGS((Idents_tIdent name));
extern void Types_MakeNode ARGS((Idents_tIdent name));
extern void Types_MakeNodeId ARGS((Idents_tIdent ident));
extern INTEGER Types_ClassCode ARGS((Idents_tIdent class));
extern INTEGER Types_MaxClassCode ARGS(());
extern void Types_AllNodes ARGS((Sets_tSet *nodes));
extern void Types_AllClasses ARGS((Sets_tSet *classes));
extern void Types_SetEssential ARGS((Idents_tIdent name));
extern void Types_UnionEssential ARGS((Sets_tSet set));
extern BOOLEAN Types_Essential ARGS((Idents_tIdent name));
extern void Types__init();
