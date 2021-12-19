(* $Id: ScanTabs.mi,v 3.5 1992/08/07 15:10:26 grosch rel $ *)

(* $Log: ScanTabs.mi,v $
 * Revision 3.5  1992/08/07  15:10:26  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 3.4  1992/01/30  13:29:56  grosch
 * redesign of interface to operating system
 *
 * Revision 3.3  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.2  91/04/26  18:19:12  grosch
 * fixed bug in computing ControlSize
 * 
 * Revision 3.1  91/04/08  15:51:13  grosch
 * corrected LastCh to OldLastCh
 * 
 * Revision 3.0  91/04/04  18:07:46  grosch
 * introduced partitioning of character set
 * 
 * Revision 1.6  91/03/26  18:27:14  grosch
 * improved generation time
 * introduced options n and o to control table size and generation time
 * increased limitation for table size from 64K to 256K
 * 
 * Revision 1.5  91/02/13  11:34:51  grosch
 * moved tables from file to initialization in C; reduced case size
 * 
 * Revision 1.4  90/06/11  11:28:00  grosch
 * extended character range to 8 bits, ChRange -> CHAR
 * 
 * Revision 1.3  90/05/17  11:20:36  grosch
 * extend character range to 8 bits
 * 
 * Revision 1.2  89/12/05  18:02:05  grosch
 * cosmetic changes
 * 
 * Revision 1.1  89/10/18  17:49:51  grosch
 * renamed ScanTab and ParsTab to Scan.Tab and Pars.Tab because of PCTE
 * 
 * Revision 1.0  88/10/04  11:59:47  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

 UNSAFE MODULE ScanTabs;


FROM SYSTEM IMPORT SHORTINT, SHORTCARD;
IMPORT Word;
FROM Checks	IMPORT ErrorCheck;
FROM General	IMPORT Min, Max;
FROM Memory	IMPORT Alloc;
FROM DynArray	IMPORT MakeArray, ExtendArray, ReleaseArray;
FROM Strings	IMPORT tString, ArrayToString, Append, Concatenate, StringToArray;
FROM Idents	IMPORT tIdent, NoIdent, GetString;
FROM Sets	IMPORT tSet, MakeSet, IsElement, Minimum, Maximum, IsEmpty,
			AssignEmpty, Union, Include;
FROM System	IMPORT tFile, OpenOutput, OpenInput, Read, Write;
FROM IO		IMPORT StdInput, StdOutput, WriteS, WriteNl, WriteC, WriteI,
			ReadI, ReadNl, EndOfLine;
FROM Layout	IMPORT WriteSpace, WriteChar;
FROM Dfa	IMPORT DStateCount, DStateRange, GetFirst, GetLast, FirstCh,
			OldLastCh, DNoState, GetDefault, GetTableNoDef, GetEobTrans;
FROM GenTabs	IMPORT PatternTablePtr, PatternCount, LeafCount;
FROM Classes	IMPORT ClassCount, ClassMemPtr, ToClass, ToChar;
FROM ScanGen	IMPORT ScannerName;

VAR Tables	: tFile;
VAR ElmtSize	: TableElmt;

(*
PROCEDURE GetTables;
   BEGIN
      Tables    	:= OpenInput ("Scan.Tab");
      ErrorCheck	("GetTables.OpenInput", Tables);
      DStateCount	:= GetTable (BasePtr	) DIV ElmtSize - 1;
      DStateCount	:= GetTable (DefaultPtr	) DIV ElmtSize - 1;
      DStateCount	:= GetTable (EobTransPtr) DIV ElmtSize - 1;
      IF ReduceCaseSize THEN
	 DStateCount	:= GetTable (ActionPtr	) DIV ElmtSize - 1;
      END;
      TableSize		:= GetTable (ControlPtr	) DIV TSIZE (ControlType) - 1;
   END GetTables;

PROCEDURE GetTable (Address: ADDRESS): CARDINAL;
   VAR
      N		: INTEGER;
      Length	: TableElmt;
   BEGIN
      N := Read (Tables, ADR (Length), ElmtSize);
      ErrorCheck ("GetTable.Read1", N);
      N := Read (Tables, Address, Length);
      ErrorCheck ("GetTable.Read2", N);
      RETURN Length;
   END GetTable;
*)

PROCEDURE PutTables	(ReduceCaseSize: BOOLEAN) =
   VAR
      BlockSize	,
      i		: Word.T;
      StateCount: StateRange;
      FileNameS	,
      PathS	: tString;
      PathA	: ARRAY [0..127] OF CHAR;
   BEGIN
      BlockSize	:= 64000 DIV BYTESIZE (ControlType);
      StateCount := DStateCount;
      IF ScannerName = NoIdent THEN
	 ArrayToString ("Scanner", PathS);
      ELSE
	 GetString (ScannerName, PathS);
      END;
      ArrayToString	(".Tab", FileNameS);
      Concatenate	(PathS, FileNameS);
      Append		(PathS, '\000');
      StringToArray	(PathS, PathA);
      Tables := OpenOutput (PathA);
      ErrorCheck ("PutTables.OpenOutput", Tables);
      PutTable ((StateCount + 1) * ElmtSize, BasePtr	);
      PutTable ((StateCount + 1) * ElmtSize, DefaultPtr	);
      PutTable ((StateCount + 1) * ElmtSize, EobTransPtr);
      IF ReduceCaseSize THEN
	 PutTable ((StateCount + 1) * ElmtSize, ActionPtr);
      END;
      i := 0;
      WHILE i <= TableSize DO
	 PutTable (Min (BlockSize, TableSize + 1 - i) * BYTESIZE (ControlType), ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 131
 $$ *) (ControlPtr^[i]));
         INC (i, BlockSize);
      END;
   END PutTables;

PROCEDURE PutTable (Length: TableElmt; Address: ADDRESS) =
   VAR N	: INTEGER;
   BEGIN
      N := Write (Tables, ADR (Length), ElmtSize);
      ErrorCheck ("PutTable.Write1", N);
      N := Write (Tables, Address, Length);
      ErrorCheck ("PutTable.Write2", N);
   END PutTable;

PROCEDURE PutComb	(File: tFile) =
   VAR i	: TableRange;
   BEGIN
      FOR i := 1 TO TableSize DO
	 WriteC (File, '{');
	 WriteI (File, ControlPtr^[i].Check, 0); WriteS (File, ", ");
	 WriteI (File, ControlPtr^[i].Next , 0); WriteS (File, "},"); WriteNl (File);
      END;
   END PutComb;

PROCEDURE PutBase	(File: tFile) =
   VAR i	: INTEGER;
   BEGIN
      FOR i := 1 TO DStateCount DO
	 WriteS (File, "& yyComb [");
	 WriteI (File, BasePtr^[i], 0); WriteS (File, "],"); WriteNl (File);
      END;
   END PutBase;

PROCEDURE PutDefault	(File: tFile) =
   VAR i	: INTEGER;
   BEGIN
      FOR i := 1 TO DStateCount DO
	 WriteI (File, DefaultPtr^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutDefault;

PROCEDURE PutEobTrans	(File: tFile) =
   VAR i	: INTEGER;
   BEGIN
      FOR i := 1 TO DStateCount DO
	 WriteI (File, EobTransPtr^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutEobTrans;

PROCEDURE PutAction	(File: tFile) =
   VAR i	: INTEGER;
   BEGIN
      FOR i := 1 TO DStateCount DO
	 WriteI (File, ActionPtr^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutAction;

PROCEDURE MakeTables	(ReduceCaseSize: BOOLEAN) =
   VAR
      State	: DStateRange;
      cState	: Word.T;
      Pattern	: SHORTCARD;
   BEGIN
      DefaultSize := DStateCount + 1;
      MakeArray (DefaultPtr , DefaultSize, BYTESIZE (StateRange));
      MakeArray (EobTransPtr, DefaultSize, BYTESIZE (StateRange));
      DefaultPtr ^[DNoState] := DNoState;
      EobTransPtr^[DNoState] := DNoState;
      FOR State := 1 TO DStateCount DO
	 DefaultPtr ^[State] := GetDefault  (State);
	 EobTransPtr^[State] := GetEobTrans (State);
      END;
      IF ReduceCaseSize THEN
	 MakeArray (ActionPtr, DefaultSize, BYTESIZE (TableElmt));
	 ActionPtr^[DNoState] := DNoState;
	 FOR State := 1 TO DStateCount DO
	    ActionPtr^[State] := PatternCount + 1;
	 END;
	 FOR Pattern := 1 TO PatternCount DO
	    FOR cState := Minimum (PatternTablePtr^[Pattern].Finals) TO
			  Maximum (PatternTablePtr^[Pattern].Finals) DO
	       IF IsElement (cState, PatternTablePtr^[Pattern].Finals) THEN
		  ActionPtr^[cState] := Pattern;
	       END;
	    END;
	 END;
      END;
   END MakeTables;

PROCEDURE CompressTables (Optimize: SHORTINT) =
   TYPE
      DiffsInfoPtr	= UNTRACED BRANDED REF  DiffsInfo;
      DiffsInfo		= RECORD
			     DiffsPtr	: UNTRACED BRANDED REF  ARRAY [1 .. 256] OF CHAR;
			     Next	: DiffsInfoPtr	;
			     Base	: TableRange	;
			     Count	: SHORTCARD	;
			  END;
   VAR
      base		: TableRange;
      lbase		: LONGINT;
      State		: DStateRange;
      Success		: BOOLEAN;
      Ch, LastElmt	: CHAR;
      OldControlSize	: LONGINT;
      i			: INTEGER;
      j			: Word.T;
      Hash		: SHORTINT;
      Group		: ARRAY [0 .. 128] OF RECORD First, Last: CHAR; END;
      GroupCount	: Word.T;
      Diffs		: ARRAY [0 .. 256] OF CHAR;
      StartCh, StopCh	: CHAR;
      HashTablePtr	: UNTRACED BRANDED REF  ARRAY [0 .. 100000] OF DiffsInfoPtr;
      HashTableSize	: LONGINT;
      Current		: DiffsInfoPtr;
      Domain		: tSet;
   BEGIN
      BaseSize := DStateCount + 1;
      MakeArray (BasePtr, BaseSize, BYTESIZE (TableRange));
      FOR State := 0 TO DStateCount DO
	 BasePtr^[State] := 0;
      END;

      IF Optimize = 0 THEN
	 ControlSize := LeafCount * 60;
      ELSIF Optimize >= 10000 THEN
	 ControlSize := DStateCount * 5;
      ELSE
	 ControlSize := LeafCount * 12;
      END;
      ControlSize := Max (ControlSize, LOOPHOLE (ORD (OldLastCh),LONGINT) + 1);
      MakeArray (ControlPtr, ControlSize, BYTESIZE (ControlType));
      FOR i := 0 TO ControlSize - 1 DO
	 ControlPtr^[i].Check := DNoState;
	 ControlPtr^[i].Next  := DNoState;
      END;

      HashTableSize := DStateCount;
      MakeArray (HashTablePtr, HashTableSize, BYTESIZE (DiffsInfoPtr));
      FOR i := 0 TO HashTableSize - 1 DO
	 HashTablePtr^[i] := NIL;
      END;

      MakeSet (Domain, ORD (OldLastCh));
      TableSize    := 0;
      TableEntries := 0;
      Group [0].Last := '\000';

      FOR State := 1 TO DStateCount DO

	 (* SPEC Success := EXISTS base : FORALL Ch IN CHAR :
			      (Table [State, Ch]       # DNoState) AND
			      (Check [base + ORD (Ch)] # DNoState)     *)

	 (* turn the row Table [State, ...] into a list of ranges (groups) *)

	 AssignEmpty (Domain);
	 Ch	    := GetFirst (State);
	 LastElmt   := GetLast  (State);

	 IF Ch <= LastElmt THEN			(* map classes to characters *)
	    LOOP
	       IF GetTableNoDef (State, Ch) # DNoState THEN
		  IF Ch <= ClassCount THEN
		     Union (Domain, ClassMemPtr^[Ch]);
		  ELSE
		     Include (Domain, ORD (ToChar [Ch]));
		  END;
	       END;
	       IF Ch = LastElmt THEN EXIT; END;
	       INC (Ch);
	    END;
	 END;

	 GroupCount := 0;
	 IF NOT IsEmpty (Domain) THEN
	    Ch	     := VAL (Minimum (Domain),CHAR);
	    LastElmt := VAL (Maximum (Domain),CHAR);

	    IF Ch <= LastElmt THEN		(* arrange into groups *)
	       LOOP
		  LOOP
		     IF Ch = LastElmt THEN EXIT; END;
		     IF NOT IsElement (ORD (Ch), Domain) THEN INC (Ch); ELSE EXIT; END;
		  END;

		  IF IsElement (ORD (Ch), Domain) THEN
		     INC (GroupCount);
		     Group [GroupCount].First := Ch;
		     LOOP
			IF Ch = LastElmt THEN EXIT; END;
			IF IsElement (ORD (Ch), Domain) THEN INC (Ch); ELSE EXIT; END;
		     END;
		     IF IsElement (ORD (Ch), Domain) THEN
			Group [GroupCount].Last := Ch;
		     ELSE
			Group [GroupCount].Last := VAL (ORD (Ch) - 1,CHAR);
		     END;
		  END;
		  IF Ch = LastElmt THEN EXIT; END;
	       END;
	    END;
	 END;

	 base := 0;
	 IF GroupCount > 0 THEN			(* search for a usable base *)

	    Hash := 0;
	    FOR j := 1 TO GroupCount DO		(* compute distances of ranges *)
	       Diffs [j + j - 1] := VAL (ORD (Group [j].First) - ORD (Group [j-1].Last),CHAR);
	       Diffs [j + j    ] := VAL (ORD (Group [j].Last) - ORD (Group [j].First),CHAR);
	       INC (Hash, (ORD (Diffs [j + j - 1]) + ORD (Diffs [j + j])) * j);
	    END;
	    Hash := Hash MOD DStateCount;	(* hash distances *)

	    Success := FALSE;			(* lookup format of row *)
	    Current := HashTablePtr^[Hash];
	    LOOP
	       IF Current = NIL THEN EXIT; END;
	       IF Current^.Count = (GroupCount * 2) THEN
		  Success := TRUE;
		  j := 0;
		  LOOP
		     INC (j);
		     IF Current^.DiffsPtr^[j] # Diffs [j] THEN
		        Success := FALSE;
		        EXIT;
		     END;
		     IF j = Current^.Count THEN EXIT; END;
		  END;
		  IF Success THEN EXIT; END;
	       END;
	       Current := Current^.Next;
	    END;

	    IF Success THEN			(* if found: start searching from previous base *)
	       base := Current^.Base + ORD (Current^.DiffsPtr^[2]) + 1;
	    ELSE				(* if not: enter and start from zero *)
	       Current := Alloc (BYTESIZE (DiffsInfo));
	       WITH m2tom3_with_13=Current^ DO
		  m2tom3_with_13.Base := 0;
		  m2tom3_with_13.Next := HashTablePtr^[Hash];
		  m2tom3_with_13.Count := GroupCount * 2;
		  m2tom3_with_13.DiffsPtr := Alloc (m2tom3_with_13.Count);
		  FOR j := 1 TO m2tom3_with_13.Count DO m2tom3_with_13.DiffsPtr^[j] := Diffs [j]; END;
	       END;
	       HashTablePtr^[Hash] := Current;
	    END;

	    LOOP				(* search for a usable base *)
	       lbase := base;
	       IF lbase >= (ControlSize - LOOPHOLE (ORD (OldLastCh),LONGINT)) THEN
		  OldControlSize := ControlSize;
		  ExtendArray (ControlPtr, ControlSize, BYTESIZE (ControlType));
		  FOR i := OldControlSize TO ControlSize - 1 DO
		     ControlPtr^[i].Check := DNoState;
		     ControlPtr^[i].Next  := DNoState;
		  END;
	       END;

	       Success := TRUE;
	       j := 0;
	       LOOP
		  INC (j);
		  StartCh := Group [j].First;
		  StopCh := Group [j].Last;
		  Ch := StartCh;
		  LOOP
		     IF (ControlPtr^[base + ORD (Ch)].Check # DNoState) THEN
			Success := FALSE;
			(* INC (base, ORD (Ch) - ORD (StartCh)); *)
			EXIT;
		     END;
		     IF Ch = StopCh THEN EXIT; END;
		     INC (Ch);
		  END;
		  IF (NOT Success) OR (j = GroupCount) THEN EXIT; END;
	       END;
	       IF Success THEN EXIT; END;
	       INC (base);
	    END;

	    j := 0;				(* enter row into comb *)
	    LOOP
	       INC (j);
	       Ch := Group [j].First;
	       StopCh := Group [j].Last;
	       LOOP
		  WITH m2tom3_with_14=ControlPtr^[base + ORD (Ch)] DO
		     m2tom3_with_14.Check := State;
		     m2tom3_with_14.Next  := GetTableNoDef (State, ToClass [Ch]);
		  END;
		  INC (TableEntries);
		  IF Ch = StopCh THEN EXIT; END;
		  INC (Ch);
	       END;
	       IF j = GroupCount THEN EXIT; END;
	    END;
	    Current^.Base := base;		(* record base of this row *)
	 END;
	 BasePtr^[State] := base;
	 TableSize := Max (TableSize, base);
      END;
      INC (TableSize, ORD (OldLastCh));
      ReleaseArray (HashTablePtr, HashTableSize, BYTESIZE (DiffsInfoPtr));
   END CompressTables;

PROCEDURE WriteTables() =
   VAR State	: DStateRange;
   BEGIN
      WriteS (StdOutput, "Tables :");
      WriteNl (StdOutput);
      WriteNl (StdOutput);
      FOR State := 1 TO DStateCount DO
	 WriteState (State);
	 WriteNl (StdOutput);
      END;
   END WriteTables;

PROCEDURE QueryTables() =
   VAR State	: DStateRange;
   BEGIN
      LOOP
	 WriteS (StdOutput, "State ? ");
	 IF EndOfLine (StdInput) THEN ReadNl (StdInput); END;
	 State := ReadI (StdInput);
         IF State = 0 THEN EXIT; END;
	 WriteState (State);
      END;
   END QueryTables;

PROCEDURE WriteState (State: DStateRange) =
   VAR
      NextState		: TableElmt;
      Ch		: CHAR;
      ControlRecord	: ControlType;
      Count		: INTEGER;
   BEGIN
      Count := 0;
      WriteS (StdOutput, "State, Default =");
      WriteI (StdOutput, State, 5);
      WriteI (StdOutput, DefaultPtr^[State], 5);
      WriteNl (StdOutput);
      FOR Ch := FirstCh TO OldLastCh DO

	 NextState := State;
	 LOOP
	    ControlRecord := ControlPtr^[BasePtr^[NextState] + ORD (Ch)];
	    IF ControlRecord.Check = NextState THEN
	       NextState := ControlRecord.Next;
	       EXIT;
	    END;
	    NextState := DefaultPtr^[NextState];
	    NextState := DNoState;
	    IF NextState = DNoState THEN EXIT; END;
	 END;

	 IF NextState # DNoState THEN
	    IF Count = 10 THEN
	       WriteNl (StdOutput);
	       Count := 0;
	    END;
	    INC (Count);
	    WriteChar (StdOutput, Ch);
	    WriteSpace (StdOutput);
	    WriteI (StdOutput, NextState, 1);
	    WriteC (StdOutput, ',');
	    WriteSpace (StdOutput);
	 END;
      END;
      WriteNl (StdOutput);
   END WriteState;

BEGIN
   ElmtSize := BYTESIZE (TableElmt);
END ScanTabs.

