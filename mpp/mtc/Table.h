#define DEFINITION_Table

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

extern void Table_Define ARGS((CHAR letter, Strings_tString *definition));
extern void Table_Translate ARGS((CHAR letter, Strings_tString *text));
extern void Table_BeginLine ARGS(());
extern void Table_CloseLine ARGS(());
extern void Table_WriteLine ARGS((Strings_tString *text));
extern void Table_NewLine ARGS(());
extern void Table__init();
