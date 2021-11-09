#define DEFINITION_Debug

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#define Debug_ShRed        0
#define Debug_RedRed        1
#define Debug_ShRedRed        2
typedef unsigned char Debug_tConflict;
extern BOOLEAN Debug_NoTrace, Debug_Fast, Debug_ItemSets;
extern IO_tFile Debug_dFile;
extern void Debug_DebugHead ARGS((Automaton_tStateIndex State));
extern void Debug_DebugState ARGS((Automaton_tStateIndex State, Sets_tSet *Set));
extern void Debug_DebugEnd ARGS(());
extern void Debug_PrintItemSets ARGS(());
extern void Debug_InformIgnored ARGS((Automaton_tItemIndex Item, TokenTab_Terminal t));
extern void Debug_InformLowPri ARGS((Automaton_tItemIndex Item, TokenTab_Terminal t));
extern void Debug_InformLeftAss ARGS((Automaton_tItemIndex Item, TokenTab_Terminal t));
extern void Debug_InformRightAss ARGS((Automaton_tItemIndex Item, TokenTab_Terminal t));
extern void Debug_InformKept ARGS((Automaton_tItemIndex Item, TokenTab_Terminal t));
extern void Debug_InformConflict ARGS((Debug_tConflict kind));
extern void Debug_NewLine ARGS(());
extern void Debug__init();
