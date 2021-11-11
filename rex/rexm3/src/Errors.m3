(* $Id: Errors.mi,v 3.4 1992/09/29 19:02:45 grosch rel $ *)

(* $Log: Errors.mi,v $
 * Revision 3.4  1992/09/29  19:02:45  grosch
 * abort execution upon errors during scanning
 *
 * Revision 3.3  1992/08/07  15:10:26  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 3.2  1991/12/04  16:16:58  grosch
 * unified escape conventions for all tools
 *
 * Revision 3.1  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.0  91/04/04  18:06:55  grosch
 * introduced partitioning of character set
 * 
 * Revision 2.0  91/03/08  18:17:43  grosch
 * turned tables into initialized arrays (in C)
 * reduced case size
 * changed interface for source position
 * 
 * Revision 1.3  91/02/13  11:34:31  grosch
 * moved tables from file to initialization in C; reduced case size
 * 
 * Revision 1.2  89/02/23  15:55:14  grosch
 * added completeness check for the automaton
 * 
 * Revision 1.1  89/01/17  15:00:23  grosch
 * correction and redesign of source position handling
 * 
 * Revision 1.0  88/10/04  11:59:34  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

 UNSAFE MODULE Errors;


FROM SYSTEM IMPORT SHORTCARD, HALT;
FROM IO		IMPORT tFile, StdError, WriteC, WriteNl, WriteS, WriteI,
		       WriteLong, WriteB, WriteR, CloseIO;
FROM Strings	IMPORT tString;
FROM Idents	IMPORT tIdent, WriteIdent;
FROM Positions	IMPORT tPosition, WritePosition;

IMPORT Word, Strings;

CONST
   IdentUndefined	= 10	;
   ImproperUse		= 11	;
   IdentDefBefore	= 12	;
   BraceMissing		= 13	;
   UnclosedComment	= 14	;
   PatternNoMatch	= 15	;
   UnclosedString	= 16	;

PROCEDURE ErrorMessage	(ErrorCode, ErrorClass: Word.T; Position: tPosition) =
   BEGIN
      ErrorMessageI (ErrorCode, ErrorClass, Position, None, NIL);
   END ErrorMessage;

PROCEDURE ErrorMessageI (ErrorCode, ErrorClass: Word.T; Position: tPosition;
			 InfoClass: Word.T; Info: ADDRESS) =
   BEGIN
      WriteErrorMessage (ErrorCode, ErrorClass, Position);
      WriteInfo (InfoClass, Info);
      WriteNl (StdError);
      IF ErrorClass <= Error THEN INC (ErrorCount); END;
      IF ErrorClass = Fatal THEN CloseIO(); HALT(); END;
   END ErrorMessageI;

PROCEDURE WriteErrorMessage (ErrorCode, ErrorClass: Word.T; Position: tPosition) =
   BEGIN
      WritePosition (StdError, Position); WriteS (StdError, ARRAY [0..2] OF CHAR{':',' ','\000'});

      CASE ErrorClass OF
      | Fatal		=> WriteS (StdError, ARRAY [0..12] OF CHAR{'F','a','t','a','l',' ',' ',' ',' ',' ',' ',' ','\000'});
      | Restriction	=> WriteS (StdError, ARRAY [0..12] OF CHAR{'R','e','s','t','r','i','c','t','i','o','n',' ','\000'});
      | Error		=> WriteS (StdError, ARRAY [0..12] OF CHAR{'E','r','r','o','r',' ',' ',' ',' ',' ',' ',' ','\000'});
      | Warning		=> WriteS (StdError, ARRAY [0..12] OF CHAR{'W','a','r','n','i','n','g',' ',' ',' ',' ',' ','\000'});
      | Repair		=> WriteS (StdError, ARRAY [0..12] OF CHAR{'R','e','p','a','i','r',' ',' ',' ',' ',' ',' ','\000'});
      | Note		=> WriteS (StdError, ARRAY [0..12] OF CHAR{'N','o','t','e',' ',' ',' ',' ',' ',' ',' ',' ','\000'});
      | Information	=> WriteS (StdError, ARRAY [0..12] OF CHAR{'I','n','f','o','r','m','a','t','i','o','n',' ','\000'});
      ELSE		  WriteS (StdError, ARRAY [0..13] OF CHAR{'E','r','r','o','r',' ','c','l','a','s','s',':',' ','\000'});
			  WriteI (StdError, ErrorClass, 0);
      END;

      CASE ErrorCode OF
      | NoText		=>
      | SyntaxError	=> WriteS (StdError, ARRAY [0..12] OF CHAR{'s','y','n','t','a','x',' ','e','r','r','o','r','\000'}	);
      | ExpectedTokens	=> WriteS (StdError, ARRAY [0..15] OF CHAR{'e','x','p','e','c','t','e','d',' ','t','o','k','e','n','s','\000'}	);
      | RestartPoint	=> WriteS (StdError, ARRAY [0..13] OF CHAR{'r','e','s','t','a','r','t',' ','p','o','i','n','t','\000'}	);
      | TokenInserted	=> WriteS (StdError, ARRAY [0..15] OF CHAR{'t','o','k','e','n',' ','i','n','s','e','r','t','e','d',' ','\000'}	);
      | WrongParseTable	=> WriteS (StdError, ARRAY [0..20] OF CHAR{'p','a','r','s','e',' ','t','a','b','l','e',' ','m','i','s','m','a','t','c','h','\000'}	);
      | OpenParseTable	=> WriteS (StdError, ARRAY [0..23] OF CHAR{'c','a','n','n','o','t',' ','o','p','e','n',' ','p','a','r','s','e',' ','t','a','b','l','e','\000'}	);
      | ReadParseTable	=> WriteS (StdError, ARRAY [0..23] OF CHAR{'c','a','n','n','o','t',' ','r','e','a','d',' ','p','a','r','s','e',' ','t','a','b','l','e','\000'}	);
      | IdentUndefined	=> WriteS (StdError, ARRAY [0..20] OF CHAR{'i','d','e','n','t','i','f','i','e','r',' ','u','n','d','e','f','i','n','e','d','\000'}	);
      | ImproperUse	=> WriteS (StdError, ARRAY [0..26] OF CHAR{'i','m','p','r','o','p','e','r',' ','u','s','e',' ','o','f',' ','i','d','e','n','t','i','f','i','e','r','\000'});
      | IdentDefBefore	=> WriteS (StdError, ARRAY [0..26] OF CHAR{'i','d','e','n','t','i','f','i','e','r',' ','a','l','r','e','a','d','y',' ','d','e','f','i','n','e','d','\000'});
      | BraceMissing	=> WriteS (StdError, ARRAY [0..19] OF CHAR{'c','l','o','s','i','n','g',' ','\'','}','\'',' ','m','i','s','s','i','n','g','\000'}	);
      | UnclosedComment	=> WriteS (StdError, ARRAY [0..16] OF CHAR{'u','n','c','l','o','s','e','d',' ','c','o','m','m','e','n','t','\000'}		);
      | PatternNoMatch	=> WriteS (StdError, ARRAY [0..24] OF CHAR{'p','a','t','t','e','r','n',' ','w','i','l','l',' ','n','e','v','e','r',' ','m','a','t','c','h','\000'}	);
      | UnclosedString	=> WriteS (StdError, ARRAY [0..15] OF CHAR{'u','n','c','l','o','s','e','d',' ','s','t','r','i','n','g','\000'}		);
      ELSE		  WriteS (StdError, ARRAY [0..13] OF CHAR{' ','e','r','r','o','r',' ','c','o','d','e',':',' ','\000'});
			  WriteI (StdError, ErrorCode, 0);
      END;
   END WriteErrorMessage;

PROCEDURE WriteInfo (InfoClass: Word.T; Info: ADDRESS) =
   VAR
      PtrToInteger	: UNTRACED BRANDED REF  INTEGER;
      PtrToShort	: UNTRACED BRANDED REF  SHORTCARD;
      PtrToLong		: UNTRACED BRANDED REF  M2LONGINT;
      PtrToReal		: UNTRACED BRANDED REF  REAL;
      PtrToBoolean	: UNTRACED BRANDED REF  BOOLEAN;
      PtrToCharacter	: UNTRACED BRANDED REF  CHAR;
      PtrToString	: UNTRACED BRANDED REF  tString;
      PtrToArray	: UNTRACED BRANDED REF  ARRAY [0..1023] OF CHAR;
      PtrToIdent	: UNTRACED BRANDED REF  tIdent;
   BEGIN
      IF InfoClass = None THEN RETURN END;
      WriteS (StdError, ARRAY [0..2] OF CHAR{':',' ','\000'});
      CASE InfoClass OF
      | Integer		=> PtrToInteger	:= Info; WriteI (StdError, PtrToInteger^, 0);
      | Short		=> PtrToShort	:= Info; WriteI (StdError, PtrToShort^, 0);
      | Long		=> PtrToLong	:= Info; WriteLong (StdError, PtrToLong^, 0);
      | Real		=> PtrToReal	:= Info; WriteR (StdError, PtrToReal^, 1, 10, 1);
      | Boolean		=> PtrToBoolean	:= Info; WriteB (StdError, PtrToBoolean^);
      | Character	=> PtrToCharacter:= Info; WriteC (StdError, PtrToCharacter^);
      | String		=> PtrToString	:= Info; Strings.WriteS (StdError, PtrToString^);
      | Array		=> PtrToArray	:= Info; WriteS (StdError, PtrToArray^);
      | Ident		=> PtrToIdent	:= Info; WriteIdent (StdError, PtrToIdent^);
      ELSE WriteS (StdError, ARRAY [0..12] OF CHAR{'i','n','f','o',' ','c','l','a','s','s',':',' ','\000'}); WriteI (StdError, InfoClass, 0);
      END;
   END WriteInfo;

BEGIN
   ErrorCount := 0;
END Errors.

