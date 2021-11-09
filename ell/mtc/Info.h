#define DEFINITION_Info

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

extern ADDRESS Info_SaveInfo ARGS((INTEGER InfoClass, ADDRESS Info));
extern void Info_WriteInfo ARGS((INTEGER InfoClass, ADDRESS Info));
extern void Info_WriteIdentSet ARGS((IO_tFile f, Sets_tSet s));
extern void Info__init();
