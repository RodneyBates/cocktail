(* $Id: rex.mi,v 3.9 1992/09/29 19:02:45 grosch rel $ *)

(* $Log: rex.mi,v $
 * Revision 3.9  1992/09/29  19:02:45  grosch
 * abort execution upon errors during scanning
 *
 * Revision 3.8  1992/09/29  14:38:55  grosch
 * abort execution upon errors during scanning
 *
 * Revision 3.7  1992/08/07  15:10:26  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 3.6  1992/01/30  13:29:56  grosch
 * redesign of interface to operating system
 *
 * Revision 3.5  1992/01/14  10:42:44  grosch
 * fixed bug: multiply NodeCount by Card (StartStates)
 *
 * Revision 3.4  1992/01/07  11:05:57  grosch
 * corrected spelling error
 *
 * Revision 3.3  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.2  91/09/18  15:05:36  grosch
 * added option to control generation of # line directives
 * 
 * Revision 3.1  91/04/08  15:50:20  grosch
 * release memory after use in Classes and Tree0
 * 
 * Revision 3.0  91/04/04  18:08:09  grosch
 * introduced partitioning of character set
 * 
 * Revision 1.6  91/03/26  18:27:22  grosch
 * improved generation time
 * introduced options n and o to control table size and generation time
 * increased limitation for table size from 64K to 256K
 * 
 * Revision 1.5  91/02/13  11:35:15  grosch
 * moved tables from file to initialization in C; reduced case size
 * 
 * Revision 1.4  90/06/11  11:28:09  grosch
 * extended character range to 8 bits, ChRange -> CHAR
 * 
 * Revision 1.3  90/05/17  11:18:51  grosch
 * cosmetic changes
 * 
 * Revision 1.2  89/11/06  12:36:34  grosch
 * renamed module Rex to GenTabs to avoid name clash with rex under VMS
 * 
 * Revision 1.1  89/02/23  15:56:10  grosch
 * added include files
 * added help facility
 * improved handling of command line arguments
 * 
 * Revision 1.0  88/10/04  11:59:56  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

MODULE rex;

FROM SYSTEM	IMPORT ADDRESS;
FROM System	IMPORT GetArgCount, GetArgument, Exit;
FROM Strings	IMPORT tString, AssignEmpty, Assign, Append, Concatenate,
			ArrayToString, StringToArray;
FROM IO		IMPORT StdOutput, CloseIO;
FROM StdIO	IMPORT WriteI, WriteS, WriteNl;
FROM Scanner	IMPORT BeginScanner, BeginFile, ScanTabName;
FROM Parser	IMPORT ParsTabName, Parser;
FROM Errors	IMPORT ErrorCount;
FROM Classes	IMPORT ComputeClasses, ReleaseSetMem;
FROM Eval	IMPORT BeginEval, Eval;
FROM Tree	IMPORT WriteTree;
FROM Tree0	IMPORT Tree0Root, WriteTree0, ReleaseTree0Module;
FROM Dfa	IMPORT LastCh;
FROM GenTabs	IMPORT StartStateCount, LeafCount, NodeCount, Root, GenerateTables;
FROM ScanGen	IMPORT GenerateScanner, GenerateInterface, GenerateSupport,
			Language, tLanguage, RexLib, SourceFile;

VAR
   Argument	: ARRAY [0 .. 127] OF CHAR;
   FileNameS	,
   Path		: tString;
   optimize	: SHORTINT;
   i, j, n	: SHORTCARD;
   d, s, r, h, w, g, b: BOOLEAN;
   ch		: CHAR;

BEGIN
   d := FALSE;
   s := FALSE;
   r := FALSE;
   h := FALSE;
   w := TRUE;
   g := FALSE;
   b := TRUE;
   optimize := 40;
   n := 0;
   Language := Modula;
   AssignEmpty (RexLib);
   SourceFile [0] := 0C;

   FOR i := 1 TO GetArgCount () - 1 DO
      GetArgument (i, Argument);
      IF Argument [0] = '-' THEN 
	 IF Argument [1] = 'l' THEN 
	    AssignEmpty (RexLib);
	    j := 2;
	    LOOP
	       ch := Argument [j];
	       IF ch = 0C THEN EXIT; END;
	       Append (RexLib, ch);
	       INC (j);
	    END;
	    Append (RexLib, '/');
	 ELSE
	    j := 0;
	    LOOP
	       INC (j);
	       ch := Argument [j];
	       CASE ch OF
	       | 0C : EXIT;
	       | '?': h := TRUE;
	       | 'h': h := TRUE;
	       | 'c': Language := C;
	       | 'm': Language := Modula;
	       | 'd': d := TRUE;
	       | 's': s := TRUE;
	       | 'r': r := TRUE;
	       | 'a': d := TRUE; s := TRUE;
	       | 'i': LastCh := 377C;
	       | 'o': optimize := 16000;
	       | 'n': optimize := 0;
	       | 'w': w := FALSE;
	       | 'g': g := TRUE;
	       | 'b': b := FALSE;
	       | '0' .. '9': n := n * 10 + ORD (ch) - ORD ('0');
	       ELSE
	       END;
	    END;
	 END;
      ELSIF Argument [0] = '?' THEN 
	 h := TRUE;
      ELSE
	 j := 0;
	 REPEAT
            ch := Argument [j];
	    SourceFile [j] := ch;
	    INC (j);
	 UNTIL ch = 0C;
      END;
   END;

   IF h THEN
WriteS ("usage: rex [-options] [file]"				); WriteNl; WriteNl;
WriteS (" a generate all (= -dsm)"					); WriteNl;
WriteS (" m generate a lexical analyzer in Modula (default)"		); WriteNl;
WriteS (" c generate a lexical analyzer in C"				); WriteNl;
WriteS (" d generate a definition module for the lexical analyzer"	); WriteNl;
WriteS (" s generate support modules:"					); WriteNl;
WriteS ("   . a source module for input"				); WriteNl;
WriteS ("   . a main program to be used as test driver"			); WriteNl;
WriteS (" r reduce number of generated case/switch labels"		); WriteNl;
WriteS (" i use ISO 8 bit code (default: ASCII 7 bit code)"		); WriteNl;
WriteS (" o optimize table size"					); WriteNl;
WriteS (" n do not optimize table size"					); WriteNl;
WriteS (" w suppress warnings"						); WriteNl;
WriteS (" g generate # line directives"					); WriteNl;
WriteS (" b do not partition character set into blocks"			); WriteNl;
WriteS (" 1 print statistics about the generated lexical analyzer"	); WriteNl;
WriteS (" h print help information"					); WriteNl;
WriteS (" ldir specify the directory dir where rex finds its data files"); WriteNl;
   ELSE
      ArrayToString	(ScanTabName, FileNameS); (* name of scanner table *)
      Assign		(Path, RexLib);
      Concatenate 	(Path, FileNameS);
      Append		(Path, 0C);
      StringToArray	(Path, ScanTabName);

      ArrayToString	(ParsTabName, FileNameS); (* name of parser table *)
      Assign		(Path, RexLib);
      Concatenate 	(Path, FileNameS);
      Append		(Path, 0C);
      StringToArray	(Path, ParsTabName);

      BeginScanner;
      IF SourceFile [0] # 0C THEN BeginFile (SourceFile); END;
      IF (Parser () = 0) AND (ErrorCount = 0) THEN
	 IF n >= 17 THEN WriteTree0 (StdOutput, Tree0Root); END;
	 BeginEval;
	 ComputeClasses (b);
	 Eval (Tree0Root);
	 IF n >= 16 THEN WriteTree0 (StdOutput, Tree0Root); END;
	 LeafCount := StartStateCount + Tree0Root^.List.LeafCount;
	 NodeCount := Tree0Root^.List.NodeCount;
	 Root := Tree0Root^.List.Tree;
	 ReleaseSetMem;
	 ReleaseTree0Module;
	 IF n >= 15 THEN WriteTree (Root); END;
	 GenerateTables (n, r, w, optimize);
	 GenerateScanner (r, w, g);
      ELSE
	 CloseIO;
	 Exit (1);
      END;
   END;

   IF d THEN GenerateInterface; END;
   IF s THEN GenerateSupport  ; END;
   CloseIO;
   Exit (0);
END rex.
