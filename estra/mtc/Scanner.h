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

#define Scanner_SymLParent   1
#define Scanner_SymRParent   2
#define Scanner_SymComma   3
#define Scanner_SymDot   4
#define Scanner_SymSlash   5
#define Scanner_SymColon   6
#define Scanner_SymSemiColon   7
#define Scanner_SymEqual   8
#define Scanner_SymBar   11
#define Scanner_SymLBrace   12
#define Scanner_SymRBrace   13
#define Scanner_SymRArrow   15
#define Scanner_SymBEGIN   21
#define Scanner_SymCLOSE   22
#define Scanner_SymCONDITION   23
#define Scanner_SymCOSTS   24
#define Scanner_SymDECLARE   25
#define Scanner_SymEXPORT   26
#define Scanner_SymGLOBAL   27
#define Scanner_SymGRAMMAR   28
#define Scanner_SymLOCAL   29
#define Scanner_SymFUNCTION   30
#define Scanner_SymTRANSFORMATION   31
#define Scanner_SymIdent   41
#define Scanner_SymNumber   42
#define Scanner_SymString   43
#define Scanner_SymCodeLBrace   51
#define Scanner_SymCodeRBrace   52
#define Scanner_SymCodeDot   53
#define Scanner_SymCodeLParent   54
#define Scanner_SymCodeRParent   55
#define Scanner_SymCodeIdent   56
#define Scanner_SymCodeString   57
#define Scanner_SymCodeSpace   58
#define Scanner_SymCodeComment   59
#define Scanner_SymCodeRest   60
#define Scanner_SymCodeComma   61
typedef struct Scanner_1 {
    Positions_tPosition Position;
    union {
        struct {
            Idents_tIdent ident;
        } V_1;
        struct {
            StringMem_tStringRef ref;
        } V_2;
        struct {
            INTEGER val;
        } V_3;
    } U_1;
} Scanner_tScanAttribute;
#define Scanner_NoValue   -1
extern Idents_tIdent Scanner_NoIdent;
extern Idents_tIdent Scanner_MaxIdent;
extern StringMem_tStringRef Scanner_NoStringRef;
extern INTEGER Scanner_MaxValue;
extern void Scanner_ErrorAttribute ARGS((INTEGER Symbol, Scanner_tScanAttribute *Attribute));
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
