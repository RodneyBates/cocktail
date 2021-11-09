#define DEFINITION_Scanner

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

typedef struct Scanner_1 {
    Positions_tPosition Position;
    union {
        struct {
            INTEGER value;
        } V_1;
        struct {
            Idents_tIdent ident;
        } V_2;
        struct {
            StringMem_tStringRef ref;
        } V_3;
    } U_1;
} Scanner_tScanAttribute;
#define Scanner_NoValue   -1
extern Idents_tIdent Scanner_Epsilon;
extern Idents_tIdent Scanner_EndOfToken;
extern Idents_tIdent Scanner_NoIdent;
extern StringMem_tStringRef Scanner_NoString;
extern void Scanner_ErrorAttribute ARGS((INTEGER Token, Scanner_tScanAttribute *Attribute));
#define Scanner_EofToken   0
extern INTEGER Scanner_TokenLength;
extern Scanner_tScanAttribute Scanner_Attribute;
extern struct Scanner_2 {
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
