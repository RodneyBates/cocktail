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

#ifndef DEFINITION_Rules
#include "Rules.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#define Scanner_Keys        0
#define Scanner_Comment        1
#define Scanner_Number        2
#define Scanner_Action        3
#define Scanner_Symbol        4
#define Scanner_Coding        5
#define Scanner_PrioPart        6
#define Scanner_RightSide        7
#define Scanner_Empty        8
typedef unsigned char Scanner_AttributeMode;
typedef struct Scanner_1 {
    Positions_tPosition Position;
    Scanner_AttributeMode Mode;
    union {
        struct {
            Lists_tList Comm;
        } V_1;
        struct {
            CARDINAL Value;
        } V_2;
        struct {
            Lists_tList Act;
        } V_3;
        struct {
            Idents_tIdent Sym;
        } V_4;
        struct {
            BOOLEAN HasCoding;
            Positions_tPosition CodNumbPos;
            CARDINAL CodValue;
        } V_5;
        struct {
            Rules_Expression Expr;
            BOOLEAN HasPrio;
            union {
                struct {
                    Idents_tIdent PriSym;
                    Positions_tPosition PriSymPos;
                } V_1;
            } U_1;
        } V_6;
    } U_1;
} Scanner_tScanAttribute;
extern void Scanner_ErrorAttribute ARGS((INTEGER Token, Scanner_tScanAttribute *Attr));
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
