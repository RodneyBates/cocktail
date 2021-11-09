#define DEFINITION_Scanner

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

typedef struct Scanner_1 {
    Positions_tPosition Position;
    CHAR Ch;
} Scanner_tScanAttribute;
extern Scanner_tScanAttribute Scanner_Attribute;
extern void Scanner_BeginScanner ARGS(());
extern void Scanner_CloseScanner ARGS(());
extern CARDINAL Scanner_GetToken ARGS(());
extern void Scanner_ErrorAttribute ARGS((CARDINAL Symbol, Scanner_tScanAttribute *Attribute));
extern void Scanner__init();
