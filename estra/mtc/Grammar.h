#define DEFINITION_Grammar

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

typedef struct Grammar_2 *Grammar_tLayout;
typedef Idents_tIdent Grammar_tSon;
typedef struct Grammar_1 {
    Grammar_tSon A[100 + 1];
} *Grammar_tSons;
typedef struct Grammar_2 {
    Idents_tIdent node;
    Idents_tIdent class;
    Grammar_tSons sons;
} Grammar_tLayoutRec;
extern void Grammar_BeginGrammar ARGS(());
extern void Grammar_SetSuperClass ARGS((Idents_tIdent class, Idents_tIdent super));
extern void Grammar_Connect ARGS((Idents_tIdent node, Idents_tIdent class));
extern void Grammar_CompleteSubclasses ARGS(());
extern void Grammar_FixMainClasses ARGS(());
extern void Grammar_NodesOfClass ARGS((Idents_tIdent class, Sets_tSet *nodes));
extern void Grammar_ClassesOfNode ARGS((Idents_tIdent node, Sets_tSet *classes));
extern Idents_tIdent Grammar_SuperClass ARGS((Idents_tIdent class));
extern BOOLEAN Grammar_IsSubclass ARGS((Idents_tIdent class, Idents_tIdent super));
extern void Grammar_DirectSubclasses ARGS((Idents_tIdent class, Sets_tSet *sub));
extern void Grammar_Subclasses ARGS((Idents_tIdent class, Sets_tSet *sub));
extern Idents_tIdent Grammar_MainClass ARGS((Idents_tIdent node));
extern void Grammar_SetNodeIdent ARGS((Idents_tIdent node, Idents_tIdent id));
extern void Grammar_SetArity ARGS((Idents_tIdent node, INTEGER arity));
extern void Grammar_SetSonName ARGS((Idents_tIdent node, INTEGER pos, Idents_tIdent name));
extern Grammar_tLayout Grammar_CreateLayout ARGS((Idents_tIdent node, Idents_tIdent class));
extern void Grammar_SetSonClass ARGS((Grammar_tLayout layout, INTEGER pos, Idents_tIdent class));
extern Idents_tIdent Grammar_NodeIdent ARGS((Idents_tIdent node));
extern INTEGER Grammar_Arity ARGS((Idents_tIdent node));
extern Idents_tIdent Grammar_SonName ARGS((Idents_tIdent node, INTEGER pos));
extern Grammar_tLayout Grammar_Layout ARGS((Idents_tIdent node, Idents_tIdent class));
extern Idents_tIdent Grammar_SonClass ARGS((Grammar_tLayout layout, INTEGER pos));
extern void Grammar_MakePatNumbers ARGS((INTEGER size));
extern void Grammar_AddPatNumber ARGS((Idents_tIdent node, INTEGER number));
extern void Grammar_PatsOfNode ARGS((Idents_tIdent node, Sets_tSet *numbers));
extern INTEGER Grammar_MaxArity ARGS(());
extern void Grammar_WriteGrammar ARGS((IO_tFile f));
extern void Grammar__init();
