#define DEFINITION_Checks

#ifndef DEFINITION_IO
#include "IO.h"
#endif

extern void Checks_ErrorCheck ARGS((CHAR s[], LONGCARD , INTEGER n));
extern void Checks_CheckReadOpen ARGS((IO_tFile *f, CHAR s[], LONGCARD ));
extern void Checks_CheckWriteOpen ARGS((IO_tFile *f, CHAR s[], LONGCARD ));
extern void Checks_CheckOpenInput ARGS((IO_tFile *f, CHAR s[], LONGCARD ));
extern void Checks_CheckOpenOutput ARGS((IO_tFile *f, CHAR s[], LONGCARD ));
extern void Checks__init();
