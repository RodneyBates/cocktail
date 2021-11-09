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

UNSAFE MODULE rex EXPORTS Main;


FROM SYSTEM IMPORT SHORTCARD, SHORTINT;
FROM System	IMPORT GetArgCount, GetArgument, Exit;
FROM Strings	IMPORT tString, AssignEmpty, Assign, Append, Concatenate,
			ArrayToString, StringToArray;
FROM IO		IMPORT StdOutput, CloseIO;
FROM StdIO	IMPORT WriteI, WriteS, WriteNl;
FROM Scanner(* $$ m2tom3 warning: unable to find interface for import 'Scanner' in line 72
 $$ *)	IMPORT BeginScanner, BeginFile, ScanTabName;
FROM Parser(* $$ m2tom3 warning: unable to find interface for import 'Parser' in line 73
 $$ *)	IMPORT ParsTabName, Parser;
FROM Errors	IMPORT ErrorCount;
FROM Classes	IMPORT ComputeClasses, ReleaseSetMem;
FROM Eval(* $$ m2tom3 warning: unable to find interface for import 'Eval' in line 76
 $$ *)	IMPORT BeginEval, Eval;
FROM Tree	IMPORT WriteTree;
FROM Tree0(* $$ m2tom3 warning: unable to find interface for import 'Tree0' in line 78
 $$ *)	IMPORT Tree0Root, WriteTree0, ReleaseTree0Module;
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
   Language := tLanguage.Modula;
   AssignEmpty (RexLib);
   SourceFile [0] := '\000';

   FOR i := 1 TO GetArgCount () - 1 DO
      GetArgument (i, Argument);
      IF Argument [0] = '-' THEN 
	 IF Argument [1] = 'l' THEN 
	    AssignEmpty (RexLib);
	    j := 2;
	    LOOP
	       ch := Argument [j];
	       IF ch = '\000' THEN EXIT; END;
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
	       | '\000' => EXIT;
	       | '?'=> h := TRUE;
	       | 'h'=> h := TRUE;
	       | 'c'=> Language := tLanguage.C;
	       | 'm'=> Language := tLanguage.Modula;
	       | 'd'=> d := TRUE;
	       | 's'=> s := TRUE;
	       | 'r'=> r := TRUE;
	       | 'a'=> d := TRUE; s := TRUE;
	       | 'i'=> LastCh := '\377';
	       | 'o'=> optimize := 16000;
	       | 'n'=> optimize := 0;
	       | 'w'=> w := FALSE;
	       | 'g'=> g := TRUE;
	       | 'b'=> b := FALSE;
	       | '0' .. '9'=> n := (n * 10) + ORD (ch) - ORD ('0');
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
	 UNTIL ch = '\000';
      END;
   END;

   IF h THEN
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 159
 $$ *) (tFile{'u','s','a','g','e',':',' ','r','e','x',' ','[','-','o','p','t','i','o','n','s',']',' ','[','f','i','l','e',']','\000',..}				); WriteNl(); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 160
 $$ *) (tFile{' ','a',' ','g','e','n','e','r','a','t','e',' ','a','l','l',' ','(','=',' ','-','d','s','m',')','\000',..}					); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 161
 $$ *) (tFile{' ','m',' ','g','e','n','e','r','a','t','e',' ','a',' ','l','e','x','i','c','a','l',' ','a','n','a','l','y','z','e','r',' ','i','n',' ','M','o','d','u','l','a',' ','(','d','e','f','a','u','l','t',')','\000',..}		); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 162
 $$ *) (tFile{' ','c',' ','g','e','n','e','r','a','t','e',' ','a',' ','l','e','x','i','c','a','l',' ','a','n','a','l','y','z','e','r',' ','i','n',' ','C','\000',..}				); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 163
 $$ *) (tFile{' ','d',' ','g','e','n','e','r','a','t','e',' ','a',' ','d','e','f','i','n','i','t','i','o','n',' ','m','o','d','u','l','e',' ','f','o','r',' ','t','h','e',' ','l','e','x','i','c','a','l',' ','a','n','a','l','y','z','e','r','\000',..}	); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 164
 $$ *) (tFile{' ','s',' ','g','e','n','e','r','a','t','e',' ','s','u','p','p','o','r','t',' ','m','o','d','u','l','e','s',':','\000',..}					); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 165
 $$ *) (tFile{' ',' ',' ','.',' ','a',' ','s','o','u','r','c','e',' ','m','o','d','u','l','e',' ','f','o','r',' ','i','n','p','u','t','\000',..}				); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 166
 $$ *) (tFile{' ',' ',' ','.',' ','a',' ','m','a','i','n',' ','p','r','o','g','r','a','m',' ','t','o',' ','b','e',' ','u','s','e','d',' ','a','s',' ','t','e','s','t',' ','d','r','i','v','e','r','\000',..}			); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 167
 $$ *) (tFile{' ','r',' ','r','e','d','u','c','e',' ','n','u','m','b','e','r',' ','o','f',' ','g','e','n','e','r','a','t','e','d',' ','c','a','s','e','/','s','w','i','t','c','h',' ','l','a','b','e','l','s','\000',..}		); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 168
 $$ *) (tFile{' ','i',' ','u','s','e',' ','I','S','O',' ','8',' ','b','i','t',' ','c','o','d','e',' ','(','d','e','f','a','u','l','t',':',' ','A','S','C','I','I',' ','7',' ','b','i','t',' ','c','o','d','e',')','\000',..}		); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 169
 $$ *) (tFile{' ','o',' ','o','p','t','i','m','i','z','e',' ','t','a','b','l','e',' ','s','i','z','e','\000',..}					); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 170
 $$ *) (tFile{' ','n',' ','d','o',' ','n','o','t',' ','o','p','t','i','m','i','z','e',' ','t','a','b','l','e',' ','s','i','z','e','\000',..}					); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 171
 $$ *) (tFile{' ','w',' ','s','u','p','p','r','e','s','s',' ','w','a','r','n','i','n','g','s','\000',..}						); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 172
 $$ *) (tFile{' ','g',' ','g','e','n','e','r','a','t','e',' ','#',' ','l','i','n','e',' ','d','i','r','e','c','t','i','v','e','s','\000',..}					); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 173
 $$ *) (tFile{' ','b',' ','d','o',' ','n','o','t',' ','p','a','r','t','i','t','i','o','n',' ','c','h','a','r','a','c','t','e','r',' ','s','e','t',' ','i','n','t','o',' ','b','l','o','c','k','s','\000',..}			); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 174
 $$ *) (tFile{' ','1',' ','p','r','i','n','t',' ','s','t','a','t','i','s','t','i','c','s',' ','a','b','o','u','t',' ','t','h','e',' ','g','e','n','e','r','a','t','e','d',' ','l','e','x','i','c','a','l',' ','a','n','a','l','y','z','e','r','\000',..}	); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 175
 $$ *) (tFile{' ','h',' ','p','r','i','n','t',' ','h','e','l','p',' ','i','n','f','o','r','m','a','t','i','o','n','\000',..}					); WriteNl();
WriteS(* $$ m2tom3 warning: actual parameter list is too short for procedure 'WriteS' in line 176
 $$ *) (tFile{' ','l','d','i','r',' ','s','p','e','c','i','f','y',' ','t','h','e',' ','d','i','r','e','c','t','o','r','y',' ','d','i','r',' ','w','h','e','r','e',' ','r','e','x',' ','f','i','n','d','s',' ','i','t','s',' ','d','a','t','a',' ','f','i','l','e','s','\000',..}); WriteNl();
   ELSE
      ArrayToString	(ScanTabName, FileNameS); (* name of scanner table *)
      Assign		(Path, RexLib);
      Concatenate 	(Path, FileNameS);
      Append		(Path, '\000');
      StringToArray	(Path, ScanTabName);

      ArrayToString	(ParsTabName, FileNameS); (* name of parser table *)
      Assign		(Path, RexLib);
      Concatenate 	(Path, FileNameS);
      Append		(Path, '\000');
      StringToArray	(Path, ParsTabName);

      BeginScanner();
      IF SourceFile [0] # '\000' THEN BeginFile (SourceFile); END;
      IF (Parser () = 0) AND (ErrorCount = 0) THEN
	 IF n >= 17 THEN WriteTree0 (StdOutput, Tree0Root); END;
	 BeginEval();
	 ComputeClasses (b);
	 Eval (Tree0Root);
	 IF n >= 16 THEN WriteTree0 (StdOutput, Tree0Root); END;
	 LeafCount := StartStateCount + Tree0Root(* $$ m2tom3 warning: unable to resolve qualification in designator 'Tree0Root' in line 198
 $$ *)^.List(* $$ m2tom3 warning: unable to resolve qualification in designator 'List' in line 198
 $$ *).LeafCount;
	 NodeCount := Tree0Root(* $$ m2tom3 warning: unable to resolve qualification in designator 'Tree0Root' in line 199
 $$ *)^.List(* $$ m2tom3 warning: unable to resolve qualification in designator 'List' in line 199
 $$ *).NodeCount;
	 Root := Tree0Root(* $$ m2tom3 warning: unable to resolve qualification in designator 'Tree0Root' in line 200
 $$ *)^.List(* $$ m2tom3 warning: unable to resolve qualification in designator 'List' in line 200
 $$ *).Tree;
	 ReleaseSetMem();
	 ReleaseTree0Module();
	 IF n >= 15 THEN WriteTree (Root); END;
	 GenerateTables (n, r, w, optimize);
	 GenerateScanner (r, w, g);
      ELSE
	 CloseIO();
	 Exit (1);
      END;
   END;

   IF d THEN GenerateInterface(); END;
   IF s THEN GenerateSupport()  ; END;
   CloseIO();
   Exit (0);
END rex.

