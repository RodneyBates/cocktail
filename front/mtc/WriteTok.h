#define DEFINITION_WriteTok

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#define WriteTok_Modula2        0
#define WriteTok_C        1
typedef unsigned char WriteTok_tLanguage;
extern WriteTok_tLanguage WriteTok_Language;
extern struct WriteTok_1 {
    CHAR A[255 + 1];
} WriteTok_SourceFileName;
extern void WriteTok_GenWrTo ARGS((IO_tFile f));
extern void WriteTok__init();
