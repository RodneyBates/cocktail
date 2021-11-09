#define DEFINITION_ArgCheck

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

extern CHAR ArgCheck_Scanner[];
extern CHAR ArgCheck_Parser[];
extern BOOLEAN ArgCheck_LineFlag, ArgCheck_Generate;
extern IO_tFile ArgCheck_Pars, ArgCheck_Def;
extern BOOLEAN ArgCheck_TEST;
extern struct ArgCheck_1 {
    CHAR A[5 + 1];
} ArgCheck_ExtDef, ArgCheck_ExtImp;
extern BOOLEAN ArgCheck_MakeDef;
extern void ArgCheck_ArgCheck ARGS(());
extern void ArgCheck_GenerateSupport ARGS(());
extern void ArgCheck_MakeFileName ARGS((Idents_tIdent Name, CHAR Default[], LONGCARD , CHAR Ext[], LONGCARD , CHAR array[], LONGCARD ));
extern void ArgCheck_ExpandLine ARGS((IO_tFile Out, Strings_tString Line));
extern void ArgCheck_CopyFile ARGS((IO_tFile In, IO_tFile Out));
extern void ArgCheck__init();
