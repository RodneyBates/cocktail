#define DEFINITION_Scanner

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

typedef struct Scanner_1 {
    Positions_tPosition Position;
} Scanner_tScanAttribute;
extern struct Scanner_2 {
    CHAR A[255 + 1];
} Scanner_InfoFileName;
#define Scanner_EofToken   0
extern INTEGER Scanner_TokenLength;
extern Scanner_tScanAttribute Scanner_Attribute;
extern struct Scanner_3 {
    CHAR A[127 + 1];
} Scanner_ScanTabName;
extern PROC Scanner_Exit;
extern void Scanner_BeginScanner ARGS(());
extern void Scanner_BeginFile ARGS((CHAR FileName[], LONGCARD ));
extern INTEGER Scanner_GetToken ARGS(());
extern void Scanner_GetWord ARGS((Strings_tString *Word));
extern void Scanner_GetLower ARGS((Strings_tString *Word));
extern void Scanner_GetUpper ARGS((Strings_tString *Word));
extern void Scanner_CloseFile ARGS(());
extern void Scanner_CloseScanner ARGS(());
extern CHAR Scanner_UpperCase ARGS((CHAR Ch));
extern CHAR Scanner_LowerCase ARGS((CHAR Ch));
extern CARDINAL Scanner_TotalLineCount ARGS(());
extern void Scanner__init();
