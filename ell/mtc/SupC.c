#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_SupC
#include "SupC.h"
#endif


static CHAR cErrDef [] = "Errors.h";
static CHAR cErrImp [] = "Errors.c";
static CHAR cDrvImp [] = "Drv.c";
static CHAR cScaDef [] = ".h";
static CHAR cScaImp [] = ".c";
static Strings_tString PathS, String;
static struct S_1 {
    CHAR A[128 + 1];
} PathA;
static void Prefix ARGS(());

static IO_tFile *G_1_file;

void SupC_ErrC
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile file;

  file = IO_WriteOpen(cErrDef, 8L);
  Checks_CheckWriteOpen(&file, cErrDef, 8L);
  IO_WriteS(file, (STRING)"# ifndef yyErrors", 17L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define yyErrors", 17L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# include \"Positions.h\"", 23L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxNoText		0", 20L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxSyntaxError		1	/* error codes		*/", 44L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxExpectedTokens	2", 27L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxRestartPoint		3", 26L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxTokenInserted	4", 26L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxFatal		1	/* error classes	*/", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxRestriction		2", 25L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxError		3", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxWarning		4", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxRepair		5", 20L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxNote			6", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxInformation		7", 25L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxNone			0", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxInteger		1	/* info classes		*/", 41L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxShort		2", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxLong			3", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxReal			4", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxBoolean		5", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxCharacter		6", 23L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxString		7", 20L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxSet			8", 18L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define xxIdent		9", 19L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define ARGS(parameters)	parameters", 36L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define ARGS(parameters)	()", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern void (* Errors_Exit) ();", 31L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern void ErrorMessage  ARGS((short yyErrorCode, short yyErrorClass, tPosition yyPosition));", 94L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern void ErrorMessageI ARGS((short yyErrorCode, short yyErrorClass, tPosition yyPosition, short yyInfoClass, char * yyInfo));", 128L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern void Message  ARGS((char * yyErrorText, short yyErrorClass, tPosition yyPosition));", 90L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern void MessageI ARGS((char * yyErrorText, short yyErrorClass, tPosition yyPosition, short yyInfoClass, char * yyInfo));", 124L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteClose(file);
  file = IO_WriteOpen(cErrImp, 8L);
  Checks_CheckWriteOpen(&file, cErrImp, 8L);
  IO_WriteS(file, (STRING)"# include \"Errors.h\"", 20L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# include <stdio.h>", 19L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# ifdef __cplusplus", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern \"C\" {", 12L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"#  include \"System.h\"", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"#  include \"Sets.h\"", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"#  include \"Idents.h\"", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"#  include \"System.h\"", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"#  include \"Sets.h\"", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"#  include \"Idents.h\"", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"static void yyExit () { Exit (1); }", 35L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"void (* Errors_Exit) () = yyExit;", 33L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"static void WriteHead", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (short yyErrorClass, tPosition yyPosition)", 45L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyErrorClass, yyPosition) short yyErrorClass; tPosition yyPosition;", 71L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WritePosition (stderr, yyPosition);", 38L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (void) fputs (\": \", stderr);", 31L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   switch (yyErrorClass) {", 26L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxFatal		: (void) fputs (\"Fatal       \", stderr); break;", 64L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxRestriction	: (void) fputs (\"Restriction \", stderr); break;", 69L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxError		: (void) fputs (\"Error       \", stderr); break;", 64L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxWarning	: (void) fputs (\"Warning     \", stderr); break;", 65L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxRepair	: (void) fputs (\"Repair      \", stderr); break;", 64L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxNote		: (void) fputs (\"Note        \", stderr); break;", 63L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxInformation	: (void) fputs (\"Information \", stderr); break;", 69L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   default		: (void) fprintf (stderr, \"Error class: %d \", yyErrorClass);", 72L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   }", 4L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"static void WriteTail", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (short yyErrorClass)", 23L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyErrorClass) short yyErrorClass;", 37L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (void) fputc ('\\n', stderr);", 31L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   if (yyErrorClass == xxFatal) Errors_Exit ();", 47L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"static void WriteCode", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (short yyErrorCode)", 22L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyErrorCode) short yyErrorCode;", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   switch (yyErrorCode) {", 25L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxNoText	: break;", 25L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxSyntaxError	: (void) fputs (\"syntax error\"		, stderr); break;", 71L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxExpectedTokens: (void) fputs (\"expected tokens\"	, stderr); break;", 75L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxRestartPoint	: (void) fputs (\"restart point\"		, stderr); break;", 73L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxTokenInserted	: (void) fputs (\"token inserted \"	, stderr); break;", 75L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   default		: (void) fprintf (stderr, \" error code: %d\", yyErrorCode);", 70L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   }", 4L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"static void WriteInfo", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (short yyInfoClass, char * yyInfo)", 37L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyInfoClass, yyInfo) short yyInfoClass; char * yyInfo;", 58L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (void) fputs (\": \", stderr);", 31L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   switch (yyInfoClass) {", 25L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxInteger	: (void) fprintf (stderr, \"%d\", * (int *)	yyInfo); break;", 75L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxShort		: (void) fprintf (stderr, \"%d\", * (short *)	yyInfo); break;", 76L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxCharacter	: (void) fprintf (stderr, \"%c\", *		yyInfo); break;", 70L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxString	: (void) fputs	 (yyInfo, stderr);			 break;", 60L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxSet		: WriteSet	 (stderr, (tSet *)		yyInfo); break;", 61L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   case xxIdent		: WriteIdent	 (stderr, * (tIdent *)		yyInfo); break;", 69L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   default		: (void) fprintf (stderr, \"info class: %d\", yyInfoClass);", 69L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   }", 4L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"void ErrorMessage", 17L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (short yyErrorCode, short yyErrorClass, tPosition yyPosition)", 64L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyErrorCode, yyErrorClass, yyPosition)", 42L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   short yyErrorCode, yyErrorClass; tPosition yyPosition;", 57L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteHead (yyErrorClass, yyPosition);", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteCode (yyErrorCode);", 27L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteTail (yyErrorClass);", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"void ErrorMessageI", 18L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (short yyErrorCode, short yyErrorClass, tPosition yyPosition, short yyInfoClass, char * yyInfo)", 98L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyErrorCode, yyErrorClass, yyPosition, yyInfoClass, yyInfo)", 63L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   short yyErrorCode, yyErrorClass; tPosition yyPosition; short yyInfoClass; char * yyInfo;", 91L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteHead (yyErrorClass, yyPosition);", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteCode (yyErrorCode);", 27L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteInfo (yyInfoClass, yyInfo);", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteTail (yyErrorClass);", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"void Message", 12L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (char * yyErrorText, short yyErrorClass, tPosition yyPosition)", 65L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyErrorText, yyErrorClass, yyPosition)", 42L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   char * yyErrorText; short yyErrorClass; tPosition yyPosition;", 64L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteHead (yyErrorClass, yyPosition);", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (void) fputs (yyErrorText, stderr);", 38L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteTail (yyErrorClass);", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"void MessageI", 13L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (char * yyErrorText, short yyErrorClass, tPosition yyPosition, short yyInfoClass, char * yyInfo)", 99L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (yyErrorText, yyErrorClass, yyPosition, yyInfoClass, yyInfo)", 63L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   char * yyErrorText; short yyErrorClass; tPosition yyPosition; short yyInfoClass; char * yyInfo;", 98L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteHead (yyErrorClass, yyPosition);", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (void) fputs (yyErrorText, stderr);", 38L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteInfo (yyInfoClass, yyInfo);", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WriteTail (yyErrorClass);", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteClose(file);
}

void SupC_ParC
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile file;

  Idents_GetString(Tree_ParserName, &PathS);
  Strings_ArrayToString(cDrvImp, 5L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  IO_WriteS(file, (STRING)"# include \"", 11L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)".h\"", 3L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"main ()", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   (void) ", 10L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" ();", 4L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Close", 8L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"  ();", 5L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   return 0;", 12L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteClose(file);
}

static void Prefix
# ifdef __STDC__
()
# else
()
# endif
{
  if (Tree_ScannerName != Idents_NoIdent) {
    Idents_WriteIdent(*G_1_file, Tree_ScannerName);
    IO_WriteS(*G_1_file, (STRING)"_", 1L);
  }
}

void SupC_ScaC
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile file;
  Idents_tIdent ScanName;
  Strings_tString String;
  IO_tFile *L_1;

  L_1 = G_1_file;
  G_1_file = &file;
  if (Tree_ScannerName == Idents_NoIdent) {
    Strings_ArrayToString((STRING)"Scanner", 7L, &String);
    ScanName = Idents_MakeIdent(&String);
  } else {
    ScanName = Tree_ScannerName;
  }
  Idents_GetString(ScanName, &PathS);
  Strings_ArrayToString(cScaDef, 2L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  IO_WriteS(file, (STRING)"# ifndef	yy", 11L);
  Idents_WriteIdent(file, ScanName);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define	yy", 11L);
  Idents_WriteIdent(file, ScanName);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define ARGS(parameters)	parameters", 36L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# define ARGS(parameters)	()", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# include \"Positions.h\"", 23L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"typedef	struct { tPosition Position; } ", 39L);
  Prefix();
  IO_WriteS(file, (STRING)"tScanAttribute;", 15L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern	", 7L);
  Prefix();
  IO_WriteS(file, (STRING)"tScanAttribute	", 15L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute	;", 11L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern	int		", 12L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken	();", 12L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"extern	void		", 13L);
  Prefix();
  IO_WriteS(file, (STRING)"ErrorAttribute	ARGS((int Token, ", 32L);
  Prefix();
  IO_WriteS(file, (STRING)"tScanAttribute * RepairAttribute));", 35L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  IO_WriteClose(file);
  Idents_GetString(ScanName, &PathS);
  Strings_ArrayToString(cScaImp, 2L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  IO_WriteS(file, (STRING)"# include <stdio.h>", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"# include \"", 11L);
  Idents_WriteIdent(file, ScanName);
  IO_WriteS(file, (STRING)".h\"", 3L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  Prefix();
  IO_WriteS(file, (STRING)"tScanAttribute	", 15L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute	= {{ 1, 0 }};", 23L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"int ", 4L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken ()", 11L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   char ch;", 11L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   do {", 7L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      ch = getchar ();", 22L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      if (ch == '\\n') {", 23L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"        ", 8L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position.Column = 0;", 30L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"        ", 8L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position.Line ++;", 27L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      } else ", 13L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position.Column ++;", 29L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   } while (ch == ' ' || ch == '\\t' || ch == '\\n');", 51L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   return ch == -1 ? 0 : ch;", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"void ", 5L);
  Prefix();
  IO_WriteS(file, (STRING)"ErrorAttribute (Token, RepairAttribute)", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   int Token;", 13L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   ", 3L);
  Prefix();
  IO_WriteS(file, (STRING)"tScanAttribute * RepairAttribute;", 33L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"{ }", 3L);
  IO_WriteNl(file);
  IO_WriteClose(file);
  G_1_file = L_1;
}

void SupC__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    ArgCheck__init();
    Checks__init();
    IO__init();
    Strings__init();
    Idents__init();
    Tree__init();

  }
}
