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

 UNSAFE MODULE RexErrors;


FROM SYSTEM IMPORT SHORTCARD, M2LONGINT, HALT;
FROM ReuseIO	
	IMPORT StdError, WriteC, WriteNl, WriteS, WriteI,
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
      WritePosition (StdError, Position); WriteS (StdError, ": ");

      CASE ErrorClass OF
      | Fatal		=> WriteS (StdError, "Fatal       ");
      | Restriction	=> WriteS (StdError, "Restriction ");
      | Error		=> WriteS (StdError, "Error       ");
      | Warning		=> WriteS (StdError, "Warning     ");
      | Repair		=> WriteS (StdError, "Repair      ");
      | Note		=> WriteS (StdError, "Note        ");
      | Information	=> WriteS (StdError, "Information ");
      ELSE		  WriteS (StdError, "Error class: ");
			  WriteI (StdError, ErrorClass, 0);
      END;

      CASE ErrorCode OF
      | NoText		=>
      | SyntaxError	=> WriteS (StdError, "syntax error"	);
      | ExpectedTokens	=> WriteS (StdError, "expected tokens"	);
      | RestartPoint	=> WriteS (StdError, "restart point"	);
      | TokenInserted	=> WriteS (StdError, "token inserted "	);
      | WrongParseTable	=> WriteS (StdError, "parse table mismatch"	);
      | OpenParseTable	=> WriteS (StdError, "cannot open parse table"	);
      | ReadParseTable	=> WriteS (StdError, "cannot read parse table"	);
      | IdentUndefined	=> WriteS (StdError, "identifier undefined"	);
      | ImproperUse	=> WriteS (StdError, "improper use of identifier");
      | IdentDefBefore	=> WriteS (StdError, "identifier already defined");
      | BraceMissing	=> WriteS (StdError, "closing '}' missing"	);
      | UnclosedComment	=> WriteS (StdError, "unclosed comment"		);
      | PatternNoMatch	=> WriteS (StdError, "pattern will never match"	);
      | UnclosedString	=> WriteS (StdError, "unclosed string"		);
      ELSE		  WriteS (StdError, " error code: ");
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
      WriteS (StdError, ": ");
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
      ELSE WriteS (StdError, "info class: "); WriteI (StdError, InfoClass, 0);
      END;
   END WriteInfo;

BEGIN
   ErrorCount := 0;
END RexErrors.

