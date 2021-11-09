#define DEFINITION_GenLang

#ifndef DEFINITION_IO
#include "IO.h"
#endif

extern void GenLang_WriteConstants ARGS((IO_tFile f));
extern void GenLang_WriteReduceCode ARGS((IO_tFile f));
extern void GenLang__init();
