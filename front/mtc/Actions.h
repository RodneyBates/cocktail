#define DEFINITION_Actions

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#define Actions_Export        0
#define Actions_Global        1
#define Actions_Local        2
#define Actions_Begin        3
#define Actions_Close        4
typedef unsigned char Actions_tActionMode;
extern Idents_tIdent Actions_ScannerName;
extern Idents_tIdent Actions_ParserName;
extern void Actions_PutComment ARGS((Actions_tActionMode kind, TokenTab_PosType kp, Lists_tList c, TokenTab_PosType cp));
extern void Actions_GetComment ARGS((Actions_tActionMode kind, TokenTab_PosType *kp, Lists_tList *c, TokenTab_PosType *cp));
extern void Actions_PutAction ARGS((Actions_tActionMode kind, Lists_tList a, TokenTab_PosType ap, Lists_tList c, TokenTab_PosType cp));
extern void Actions_GetAction ARGS((Actions_tActionMode kind, Lists_tList *a, TokenTab_PosType *ap, Lists_tList *c, TokenTab_PosType *cp));
extern void Actions_WriteActions ARGS((Actions_tActionMode kind, IO_tFile f, BOOLEAN Line));
extern void Actions_WriteSemanticAction ARGS((IO_tFile f, Lists_tList a, CARDINAL t));
extern void Actions_WriteStringList ARGS((IO_tFile file, Lists_tList slist));
extern void Actions__init();
