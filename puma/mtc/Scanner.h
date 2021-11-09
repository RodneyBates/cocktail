#define DEFINITION_Scanner

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

typedef struct Scanner_1 {
    Idents_tIdent Ident;
} Scanner_yyIdent;
typedef struct Scanner_2 {
    Idents_tIdent Ident;
} Scanner_yyOperator;
typedef struct Scanner_3 {
    Idents_tIdent Ident;
} Scanner_yyIncOperator;
typedef struct Scanner_4 {
    Idents_tIdent Ident;
} Scanner_yyCompoundOperator;
typedef struct Scanner_5 {
    Texts_tText Text;
} Scanner_yyTargetBlock;
typedef struct Scanner_6 {
    StringMem_tStringRef StringRef;
} Scanner_yyString;
typedef struct Scanner_7 {
    StringMem_tStringRef StringRef;
} Scanner_yyNumber;
typedef struct Scanner_8 {
    StringMem_tStringRef StringRef;
} Scanner_yyTargetCode;
typedef struct Scanner_9 {
    StringMem_tStringRef StringRef;
} Scanner_yyWhiteSpace;
typedef struct Scanner_10 {
    StringMem_tStringRef StringRef;
} Scanner_yy10;
typedef struct Scanner_11 {
    StringMem_tStringRef StringRef;
} Scanner_yy11;
typedef struct Scanner_12 {
    StringMem_tStringRef StringRef;
} Scanner_yy12;
typedef struct Scanner_13 {
    Positions_tPosition Position;
    union {
        struct {
            Scanner_yyIdent Ident;
        } V_1;
        struct {
            Scanner_yyOperator Operator;
        } V_2;
        struct {
            Scanner_yyIncOperator IncOperator;
        } V_3;
        struct {
            Scanner_yyCompoundOperator CompoundOperator;
        } V_4;
        struct {
            Scanner_yyTargetBlock TargetBlock;
        } V_5;
        struct {
            Scanner_yyString String;
        } V_6;
        struct {
            Scanner_yyNumber Number;
        } V_7;
        struct {
            Scanner_yyTargetCode TargetCode;
        } V_8;
        struct {
            Scanner_yyWhiteSpace WhiteSpace;
        } V_9;
        struct {
            Scanner_yy10 yy10;
        } V_10;
        struct {
            Scanner_yy11 yy11;
        } V_11;
        struct {
            Scanner_yy12 yy12;
        } V_12;
    } U_1;
} Scanner_tScanAttribute;
extern void Scanner_ErrorAttribute ARGS((INTEGER Token, Scanner_tScanAttribute *pAttribute));
extern void Scanner_Error ARGS((CHAR Text[], LONGCARD , Positions_tPosition Position));
extern void Scanner_StringError ARGS((Strings_tString Text, Positions_tPosition Position));
extern void Scanner_ErrorI ARGS((CHAR Text[], LONGCARD , Positions_tPosition Position, Idents_tIdent Ident));
extern void Scanner_Warning ARGS((CHAR Text[], LONGCARD , Positions_tPosition Position));
extern void Scanner_StringWarning ARGS((Strings_tString Text, Positions_tPosition Position));
extern void Scanner_WarningI ARGS((CHAR Text[], LONGCARD , Positions_tPosition Position, Idents_tIdent Ident));
#define Scanner_EofToken   0
extern INTEGER Scanner_TokenLength;
extern Scanner_tScanAttribute Scanner_Attribute;
extern struct Scanner_14 {
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
