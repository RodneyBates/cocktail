(* $Id: ParserDrv.mi,v 1.2 1992/08/07 15:28:42 grosch rel $ *)

MODULE ParserDrv;

FROM Parser	IMPORT Parser, CloseParser;
FROM IO		IMPORT CloseIO;

BEGIN
   IF Parser () = 0 THEN END;
   CloseParser;
   CloseIO;
END ParserDrv.
