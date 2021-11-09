#define DEFINITION_ScanGen

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#define ScanGen_Position   0
#define ScanGen_NoPosition   1
#define ScanGen_Modula        0
#define ScanGen_C        1
typedef unsigned char ScanGen_tLanguage;
extern Texts_tText ScanGen_Export, ScanGen_Global, ScanGen_Local, ScanGen_Begin, ScanGen_Close, ScanGen_Default, ScanGen_Eof, ScanGen_BlankText, ScanGen_TabText, ScanGen_EolText;
extern SHORTCARD ScanGen_ExportLine, ScanGen_GlobalLine, ScanGen_LocalLine, ScanGen_BeginLine, ScanGen_CloseLine, ScanGen_DefaultLine, ScanGen_EofLine;
extern Idents_tIdent ScanGen_ScannerName;
extern ScanGen_tLanguage ScanGen_Language;
extern Strings_tString ScanGen_RexLib;
extern struct ScanGen_1 {
    CHAR A[127 + 1];
} ScanGen_SourceFile;
extern void ScanGen_InitScanGen ARGS(());
extern void ScanGen_GenerateScanner ARGS((BOOLEAN ReduceCaseSize, BOOLEAN Warnings, BOOLEAN GenLine));
extern void ScanGen_GenerateInterface ARGS(());
extern void ScanGen_GenerateSupport ARGS(());
extern void ScanGen__init();
