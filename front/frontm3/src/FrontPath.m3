(* add path to file name *)

(* $Id: Path.mi,v 1.4 1992/09/07 14:45:01 grosch rel $ *)

(* $Log: Path.mi,v $
 * Revision 1.4  1992/09/07  14:45:01  grosch
 * adaption to MS-DOS
 *
 * Revision 1.3  1992/01/30  13:34:33  grosch
 * redesign of interface to operating system
 *
 * Revision 1.2  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/11  18:45:22  grosch
 * layout improvements
 * 
 * Revision 1.0	 88/10/04  14:27:06  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE FrontPath;

IMPORT Text;

FROM	Strings		IMPORT	tString,	tStringIndex,	SubString,
				Char,		Append,		Length,
				Concatenate,	ArrayToString,	StringToArray,
                                StringToText;

FROM	System		IMPORT	GetArgument;

PROCEDURE InsertPathT (VAR T:TEXT) =
  VAR
    ArgT, path: TEXT; 
    pos : INTEGER;
    ArgA : ARRAY [0..255] OF CHAR;
    ArgS : tString;
  BEGIN
    
    (* get program name *)
    GetArgument (0, ArgA);
    ArrayToString (ArgA, ArgS);
    ArgT := StringToText (ArgS);

    (* Find rightmost '/' or '\\' in program name *)
    pos := Text.Length (ArgT)-1;
    WHILE pos >= 0
          AND NOT Text.GetChar (ArgT, pos) IN SET OF CHAR { '/' , '\\' }
    DO DEC (pos);
    END;

    (* If the path is not empty insert it left of T. *)
    IF pos >= 0 THEN
      path := Text.Sub (ArgT, 0 , pos+1);
      T := path & T;
    END;
  END InsertPathT;

PROCEDURE InsertPath (VAR a: ARRAY OF CHAR) =
  VAR
    s1,s2 : tString;
    Arg : ARRAY [0..255] OF CHAR;
    pos : tStringIndex;
  BEGIN
    
    (* get program name *)

    GetArgument (0, Arg);
    ArrayToString (Arg, s1);

    (* find last '/' in program name *)

    pos := Length (s1);
    WHILE (pos > 0) AND (Char (s1, pos) # '/') AND (Char (s1, pos) # '\\') DO
      DEC (pos);
    END;

    (* if the path is not empty insert it *)

    IF pos > 0 THEN
      SubString (s1, 1, pos, s2);
      ArrayToString (a, s1);
      Concatenate (s2, s1);
      Append (s2, '\000');
      StringToArray (s2, a);
    END;
  END InsertPath;

BEGIN
END FrontPath.

