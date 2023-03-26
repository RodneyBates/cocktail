(* $Id: Errors.mi,v 2.1 1992/08/07 15:28:42 grosch rel $ *)

(* R.M.B. WriteI will accept INTEGER, but not SHORTINT or LONGINT.
   Changed WriteInfo to comply. *)

(* Modified from Errors.mi, to be in Modula-3.
   Rodney M. Bates, rodney.m.bates@acm.org.
*) 
MODULE Errors;

FROM IO		IMPORT tFile, StdError, WriteC, WriteNl, WriteS, WriteI,
		       WriteB, WriteR, CloseIO;
FROM Sets	IMPORT tSet, IsElement, Size;
FROM Idents	IMPORT tIdent, WriteIdent;
FROM Positions	IMPORT tPosition, WritePosition;

IMPORT System, Strings;

PROCEDURE ErrorMessage	(ErrorCode, ErrorClass: CARDINAL; Position: tPosition);
   BEGIN
      WriteHead	(Position, ErrorClass);
      WriteCode	(ErrorCode);
      WriteTail	(ErrorClass);
   END ErrorMessage;

PROCEDURE ErrorMessageI	(ErrorCode, ErrorClass: CARDINAL; Position: tPosition;
			 InfoClass: CARDINAL; Info: ADDRESS);
   BEGIN
      WriteHead	(Position, ErrorClass);
      WriteCode	(ErrorCode);
      WriteInfo	(InfoClass, Info);
      WriteTail	(ErrorClass);
   END ErrorMessageI;

PROCEDURE Message  (ErrorText: ARRAY OF CHAR; ErrorClass: CARDINAL; Position: tPosition);
   BEGIN
      WriteHead	(Position, ErrorClass);
      WriteS	(StdError, ErrorText);
      WriteTail	(ErrorClass);
   END Message;

PROCEDURE MessageI (ErrorText: ARRAY OF CHAR; ErrorClass: CARDINAL; Position: tPosition;
			 InfoClass: CARDINAL; Info: ADDRESS);
   BEGIN
      WriteHead	(Position, ErrorClass);
      WriteS	(StdError, ErrorText);
      WriteInfo	(InfoClass, Info);
      WriteTail	(ErrorClass);
   END MessageI;

PROCEDURE WriteHead (Position: tPosition; ErrorClass: CARDINAL);
   BEGIN
      WritePosition (StdError, Position);
      WriteS	(StdError, ": ");
      CASE ErrorClass OF
      |  Fatal		: WriteS (StdError, "Fatal       ");
      |  Restriction	: WriteS (StdError, "Restriction ");
      |  Error		: WriteS (StdError, "Error       ");
      |  Warning	: WriteS (StdError, "Warning     ");
      |  Repair		: WriteS (StdError, "Repair      ");
      |  Note		: WriteS (StdError, "Note        ");
      |  Information	: WriteS (StdError, "Information ");
      ELSE WriteS (StdError, "Error class: "); WriteI (StdError, ErrorClass, 0);
      END;
   END WriteHead;

PROCEDURE WriteTail (ErrorClass: CARDINAL);
   BEGIN
      WriteNl (StdError);
      IF ErrorClass = Fatal THEN Exit; END;
   END WriteTail;

PROCEDURE WriteCode (ErrorCode: CARDINAL);
   BEGIN
      CASE ErrorCode OF
      |  NoText		 :
       |  SyntaxError	 : WriteS (StdError, "syntax error"		);
      |  ExpectedTokens	 : WriteS (StdError, "expected tokens"		);
      |  RestartPoint	 : WriteS (StdError, "restart point"		);
      |  TokenInserted	 : WriteS (StdError, "token inserted "		);
      |  WrongParseTable : WriteS (StdError, "parse table mismatch"	);
      |  OpenParseTable	 : WriteS (StdError, "cannot open parse table"	);
      |  ReadParseTable	 : WriteS (StdError, "cannot read parse table"	);
      ELSE WriteS (StdError, " error code: "); WriteI (StdError, ErrorCode, 0);
      END;
   END WriteCode;

PROCEDURE WriteInfo	(InfoClass: CARDINAL; Info: ADDRESS);
   VAR
      PtrToInteger	: REF INTEGER;
      PtrToShort	: REF [0 .. 65535]
      PtrToLong		: REF INTEGER;
      PtrToReal		: REF REAL;
      PtrToBoolean	: REF BOOLEAN;
      PtrToCharacter	: REF CHAR;
      PtrToString	: REF Strings.tString;
      PtrToArray	: REF ARRAY [0..1023] OF CHAR;
      PtrToIdent	: REF tIdent;
      Int               : INTEGER;
   BEGIN
      WriteS (StdError, ": ");
      CASE InfoClass OF
      | Integer	, Long
                : PtrToInteger	:= Info; WriteI (StdError, PtrToInteger^, 0);
      | Short 
                : PtrToShort	:= Info; Int := PtrToShort ^; 
                  WriteI (StdError, Int, 0);
(*    | Short  	: PtrToShort	:= Info; WriteI (StdError, PtrToShort^, 0);
      | Long   	: PtrToLong	:= Info; WriteI (StdError, PtrToLong^, 0); 
*)
      | Real   	: PtrToReal	:= Info; WriteR (StdError, PtrToReal^, 1, 10, 1);
      | Boolean	: PtrToBoolean	:= Info; WriteB (StdError, PtrToBoolean^);
      | Character:PtrToCharacter:= Info; WriteC (StdError, PtrToCharacter^);
      | String	: PtrToString	:= Info; Strings.WriteS (StdError, PtrToString^);
      | Array	: PtrToArray	:= Info; WriteS (StdError, PtrToArray^);
      | Ident	: PtrToIdent	:= Info; WriteIdent (StdError, PtrToIdent^);
      ELSE
      END;
   END WriteInfo;

PROCEDURE yyExit;
   BEGIN
      CloseIO; System.Exit (1);
   END yyExit;

BEGIN
   Exit := yyExit;
END Errors.
