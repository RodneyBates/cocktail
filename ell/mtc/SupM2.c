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

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_SupM2
#include "SupM2.h"
#endif


static CHAR cErrDef [] = "Errors.md";
static CHAR cErrImp [] = "Errors.mi";
static CHAR cDrvImp [] = "Drv.mi";
static CHAR cScaDef [] = ".md";
static CHAR cScaImp [] = ".mi";
static Strings_tString PathS, String;
static struct S_1 {
    CHAR A[128 + 1];
} PathA;


void SupM2_ErrM2
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile file;

  file = IO_WriteOpen(cErrDef, 9L);
  Checks_CheckWriteOpen(&file, cErrDef, 9L);
  IO_WriteS(file, (STRING)"DEFINITION MODULE Errors;", 25L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM SYSTEM	IMPORT ADDRESS;", 27L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM Positions	IMPORT tPosition;", 32L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"CONST", 5L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   NoText		= 0	;", 16L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   SyntaxError		= 1	;	(* error codes		*)", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   ExpectedTokens	= 2	;", 23L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   RestartPoint		= 3	;", 22L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   TokenInserted	= 4	;", 22L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   WrongParseTable	= 5	;", 24L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   OpenParseTable	= 6	;", 23L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   ReadParseTable	= 7	;", 23L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Fatal		= 1	;	(* error classes	*)", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Restriction		= 2	;", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Error		= 3	;", 15L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Warning		= 4	;", 17L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Repair		= 5	;", 16L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Note			= 6	;", 15L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Information		= 7	;", 21L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   None			= 0	;", 15L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Integer		= 1	;	(* info classes		*)", 37L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Short		= 2	;", 15L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Long			= 3	;", 15L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Real			= 4	;", 15L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Boolean		= 5	;", 17L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Character		= 6	;", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   String		= 7	;", 16L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Array		= 8	;", 15L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Set			= 9	;", 14L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Ident		= 10	;", 16L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"VAR Exit	: PROC;", 16L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE ErrorMessage	(ErrorCode, ErrorClass: CARDINAL; Position: tPosition);", 78L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE ErrorMessageI	(ErrorCode, ErrorClass: CARDINAL; Position: tPosition;", 78L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"			 InfoClass: CARDINAL; Info: ADDRESS);", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE Message  (ErrorText: ARRAY OF CHAR; ErrorClass: CARDINAL; Position: tPosition);", 89L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE MessageI (ErrorText: ARRAY OF CHAR; ErrorClass: CARDINAL; Position: tPosition;", 88L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"			 InfoClass: CARDINAL; Info: ADDRESS);", 40L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"END Errors.", 11L);
  IO_WriteNl(file);
  IO_WriteClose(file);
  file = IO_WriteOpen(cErrImp, 9L);
  Checks_CheckWriteOpen(&file, cErrImp, 9L);
  IO_WriteS(file, (STRING)"IMPLEMENTATION MODULE Errors;", 29L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM SYSTEM	IMPORT ADDRESS;", 27L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM IO		IMPORT tFile, StdError, WriteC, WriteNl, WriteS, WriteI,", 65L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"		       WriteB, WriteR, CloseIO;", 33L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM Sets	IMPORT tSet, IsElement, Size;", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM Idents	IMPORT tIdent, WriteIdent;", 38L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM Positions	IMPORT tPosition, WritePosition;", 47L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"IMPORT System, Strings;", 23L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE ErrorMessage	(ErrorCode, ErrorClass: CARDINAL; Position: tPosition);", 78L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteHead	(Position, ErrorClass);", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteCode	(ErrorCode);", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteTail	(ErrorClass);", 29L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END ErrorMessage;", 20L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE ErrorMessageI	(ErrorCode, ErrorClass: CARDINAL; Position: tPosition;", 78L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"			 InfoClass: CARDINAL; Info: ADDRESS);", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteHead	(Position, ErrorClass);", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteCode	(ErrorCode);", 28L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteInfo	(InfoClass, Info);", 34L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteTail	(ErrorClass);", 29L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END ErrorMessageI;", 21L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE Message  (ErrorText: ARRAY OF CHAR; ErrorClass: CARDINAL; Position: tPosition);", 89L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteHead	(Position, ErrorClass);", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteS	(StdError, ErrorText);", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteTail	(ErrorClass);", 29L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END Message;", 15L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE MessageI (ErrorText: ARRAY OF CHAR; ErrorClass: CARDINAL; Position: tPosition;", 88L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"			 InfoClass: CARDINAL; Info: ADDRESS);", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteHead	(Position, ErrorClass);", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteS	(StdError, ErrorText);", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteInfo	(InfoClass, Info);", 34L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteTail	(ErrorClass);", 29L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END MessageI;", 16L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE WriteHead (Position: tPosition; ErrorClass: CARDINAL);", 64L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WritePosition (StdError, Position);", 41L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteS	(StdError, ': ');", 30L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      CASE ErrorClass OF", 24L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  Fatal		: WriteS (StdError, 'Fatal       ');", 52L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  Restriction	: WriteS (StdError, 'Restriction ');", 57L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  Error		: WriteS (StdError, 'Error       ');", 52L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  Warning	: WriteS (StdError, 'Warning     ');", 53L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  Repair		: WriteS (StdError, 'Repair      ');", 53L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  Note		: WriteS (StdError, 'Note        ');", 51L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  Information	: WriteS (StdError, 'Information ');", 57L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      ELSE WriteS (StdError, 'Error class: '); WriteI (StdError, ErrorClass, 0);", 80L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      END;", 10L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END WriteHead;", 17L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE WriteTail (ErrorClass: CARDINAL);", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteNl (StdError);", 25L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      IF ErrorClass = Fatal THEN Exit; END;", 43L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END WriteTail;", 17L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE WriteCode (ErrorCode: CARDINAL);", 42L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      CASE ErrorCode OF", 23L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  NoText		 :", 19L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  SyntaxError	 : WriteS (StdError, 'syntax error'		);", 60L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  ExpectedTokens	 : WriteS (StdError, 'expected tokens'		);", 66L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  RestartPoint	 : WriteS (StdError, 'restart point'		);", 62L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  TokenInserted	 : WriteS (StdError, 'token inserted '		);", 65L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  WrongParseTable : WriteS (StdError, 'parse table mismatch'	);", 70L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  OpenParseTable	 : WriteS (StdError, 'cannot open parse table'	);", 73L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      |  ReadParseTable	 : WriteS (StdError, 'cannot read parse table'	);", 73L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      ELSE WriteS (StdError, ' error code: '); WriteI (StdError, ErrorCode, 0);", 79L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      END;", 10L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END WriteCode;", 17L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE WriteInfo	(InfoClass: CARDINAL; Info: ADDRESS);", 57L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   VAR", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToInteger	: POINTER TO INTEGER;", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToShort	: POINTER TO SHORTCARD;", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToLong		: POINTER TO LONGINT;", 38L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToReal		: POINTER TO REAL;", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToBoolean	: POINTER TO BOOLEAN;", 40L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToCharacter	: POINTER TO CHAR;", 39L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToString	: POINTER TO Strings.tString;", 47L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToArray	: POINTER TO ARRAY [0..1023] OF CHAR;", 54L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      PtrToIdent	: POINTER TO tIdent;", 37L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      WriteS (StdError, ': ');", 30L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      CASE InfoClass OF", 23L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Integer	: PtrToInteger	:= Info; WriteI (StdError, PtrToInteger^, 0);", 76L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Short  	: PtrToShort	:= Info; WriteI (StdError, PtrToShort^, 0);", 72L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Long   	: PtrToLong	:= Info; WriteI (StdError, PtrToLong^, 0);", 70L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Real   	: PtrToReal	:= Info; WriteR (StdError, PtrToReal^, 1, 10, 1);", 77L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Boolean	: PtrToBoolean	:= Info; WriteB (StdError, PtrToBoolean^);", 73L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Character:PtrToCharacter:= Info; WriteC (StdError, PtrToCharacter^);", 76L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | String	: PtrToString	:= Info; Strings.WriteS (StdError, PtrToString^);", 78L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Array	: PtrToArray	:= Info; WriteS (StdError, PtrToArray^);", 67L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      | Ident	: PtrToIdent	:= Info; WriteIdent (StdError, PtrToIdent^);", 71L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      ELSE", 10L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      END;", 10L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END WriteInfo;", 17L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE yyExit;", 17L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      CloseIO; System.Exit (1);", 31L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END yyExit;", 14L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"BEGIN", 5L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Exit := yyExit;", 18L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"END Errors.", 11L);
  IO_WriteNl(file);
  IO_WriteClose(file);
}

void SupM2_ParM2
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile file;

  Idents_GetString(Tree_ParserName, &PathS);
  Strings_ArrayToString(cDrvImp, 6L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  IO_WriteS(file, (STRING)"MODULE ", 7L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"Drv;", 4L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM ", 5L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"	IMPORT ", 8L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)", Close", 7L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM IO		IMPORT CloseIO;", 24L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"BEGIN", 5L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   IF ", 6L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" () = 0 THEN END;", 17L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   Close", 8L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   CloseIO;", 11L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"END ", 4L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"Drv.", 4L);
  IO_WriteNl(file);
  IO_WriteClose(file);
}

void SupM2_ScaM2
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile file;
  Idents_tIdent ScanName;
  Strings_tString String;

  if (Tree_ScannerName == Idents_NoIdent) {
    Strings_ArrayToString((STRING)"Scanner", 7L, &String);
    ScanName = Idents_MakeIdent(&String);
  } else {
    ScanName = Tree_ScannerName;
  }
  Idents_GetString(ScanName, &PathS);
  Strings_ArrayToString(cScaDef, 3L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  IO_WriteS(file, (STRING)"DEFINITION MODULE ", 18L);
  Idents_WriteIdent(file, ScanName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM Positions	IMPORT	tPosition;", 32L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"TYPE tScanAttribute	= RECORD Position: tPosition; END;", 54L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"VAR  Attribute		: tScanAttribute;", 33L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE GetToken ()	: INTEGER;", 32L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attribute: tScanAttribute);", 73L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"END ", 4L);
  Idents_WriteIdent(file, ScanName);
  IO_WriteS(file, (STRING)".", 1L);
  IO_WriteNl(file);
  IO_WriteClose(file);
  Idents_GetString(ScanName, &PathS);
  Strings_ArrayToString(cScaImp, 3L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  IO_WriteS(file, (STRING)"IMPLEMENTATION MODULE ", 22L);
  Idents_WriteIdent(file, ScanName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"FROM IO		IMPORT StdInput, ReadC;", 32L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE GetToken (): INTEGER;", 31L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   VAR ch	: CHAR;", 17L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      LOOP", 10L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	 ch := ReadC (StdInput);", 25L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"         IF ch = 12C THEN", 25L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	   INC (Attribute.Position.Line);", 34L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	   Attribute.Position.Column := 0;", 35L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	 ELSIF ch = ' ' THEN", 21L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	   INC (Attribute.Position.Column);", 36L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"         ELSE", 13L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	   INC (Attribute.Position.Column);", 36L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	   EXIT;", 9L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"	 END;", 6L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      END;", 10L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"      RETURN ORD (ch);", 22L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END GetToken;", 16L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attribute: tScanAttribute);", 73L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   BEGIN", 8L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"   END ErrorAttribute;", 22L);
  IO_WriteNl(file);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"BEGIN", 5L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"  Attribute.Position.Line	:= 1;", 31L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"  Attribute.Position.Column	:= 0;", 33L);
  IO_WriteNl(file);
  IO_WriteS(file, (STRING)"END ", 4L);
  Idents_WriteIdent(file, ScanName);
  IO_WriteS(file, (STRING)".", 1L);
  IO_WriteNl(file);
  IO_WriteClose(file);
}

void SupM2__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    ArgCheck__init();
    Checks__init();
    IO__init();
    Idents__init();
    Tree__init();
    Strings__init();

  }
}
