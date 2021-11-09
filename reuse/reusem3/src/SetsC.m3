(* $Id: SetsC.mi,v 1.3 1991/11/21 14:33:17 grosch rel $ *)

(* $Log: SetsC.mi,v $

 * RMB 97/06/05 Added InitNullSet, since some tree dumps call
                WriteSet for sets which are not in use and need
                no allocated array. 

Revision 1.3  1991/11/21  14:33:17  grosch
new version of RCS on SPARC

Revision 1.2  90/05/31  09:45:30  grosch
turned Name parameter of Check procedures into value parameter for SUN m2c

Revision 1.1  89/02/23  16:02:37  grosch
Initial revision

 *)

(* Ich, Doktor Josef Grosch, Informatiker, Feb. 1989 *)

 UNSAFE MODULE SetsC;

IMPORT Word, Sets;

FROM ReuseIO		IMPORT tFile, StdError, WriteI, WriteN, WriteS, WriteNl;

PROCEDURE CheckSetSet (VAR Set1, Set2: tSet;READONLY  Name: ARRAY OF CHAR) =
   BEGIN
      CheckSet (Set1, Name);
      CheckSet (Set2, Name);
      IF Set1.MaxElmt # Set2.MaxElmt THEN
	 WriteS (StdError, ARRAY [0..5] OF CHAR{'S','e','t','s','.','\000'}); WriteS (StdError, Name); 
	 WriteS (StdError, ARRAY [0..19] OF CHAR{':',' ','i','n','c','o','m','p','a','t','i','b','l','e',' ','s','e','t','s','\000'}); WriteNl (StdError);
	 PrintSet (Set1);
	 PrintSet (Set2);
      END;
   END CheckSetSet;

PROCEDURE CheckSetElmt (VAR Set: tSet; Elmt: INTEGER;READONLY  Name: ARRAY OF CHAR) =
   BEGIN
      CheckSet (Set, Name);
      IF Elmt < 0 THEN
	 WriteS (StdError, ARRAY [0..5] OF CHAR{'S','e','t','s','.','\000'}); WriteS (StdError, Name); 
	 WriteS (StdError, ARRAY [0..20] OF CHAR{':',' ','n','e','g','a','t','i','v','e',' ','e','l','e','m','e','n','t',':',' ','\000'});
	 WriteI (StdError, Elmt, 0); WriteNl (StdError);
	 PrintSet (Set);
      END;
      IF Elmt > VAL (   Set.MaxElmt,INTEGER ) THEN
	 WriteS (StdError, ARRAY [0..5] OF CHAR{'S','e','t','s','.','\000'}); WriteS (StdError, Name); 
	 WriteS (StdError, ARRAY [0..24] OF CHAR{':',' ','e','l','e','m','e','n','t',' ','o','u','t',' ','o','f',' ','r','a','n','g','e',':',' ','\000'});
	 WriteI (StdError, Elmt, 0); WriteNl (StdError);
	 PrintSet (Set);
      END;
   END CheckSetElmt;

PROCEDURE CheckSet (VAR Set: tSet;READONLY  Name: ARRAY OF CHAR) =
   BEGIN
      IF Set.BitsetPtr = NIL THEN
	 WriteS (StdError, ARRAY [0..5] OF CHAR{'S','e','t','s','.','\000'}); WriteS (StdError, Name); 
	 WriteS (StdError, ARRAY [0..30] OF CHAR{':',' ','s','e','t',' ','p','r','o','b','a','b','l','y',' ','n','o','t',' ','i','n','i','t','i','a','l','i','z','e','d','\000'}); WriteNl (StdError);
	 PrintSet (Set);
      END;
   END CheckSet;

PROCEDURE CheckNotEmpty (VAR Set: tSet;READONLY  Name: ARRAY OF CHAR) =
   BEGIN
      CheckSet (Set, Name);
      IF Sets.IsEmpty (Set) THEN
	 WriteS (StdError, ARRAY [0..5] OF CHAR{'S','e','t','s','.','\000'}); WriteS (StdError, Name); 
	 WriteS (StdError, ARRAY [0..22] OF CHAR{':',' ','a','p','p','l','i','e','d',' ','t','o',' ','e','m','p','t','y',' ','s','e','t','\000'}); WriteNl (StdError);
	 PrintSet (Set);
      END;
   END CheckNotEmpty;

PROCEDURE PrintSet (Set: tSet) =
   BEGIN
      WITH m2tom3_with_25=Set DO
        WriteS (StdError, ARRAY [0..12] OF CHAR{'B','i','t','s','e','t','P','t','r',' ','=',' ','\000'}); 
        WriteN (StdError, LOOPHOLE(m2tom3_with_25.BitsetPtr,LONGCARD), 0, 16); WriteNl (StdError);
        WriteS (StdError, ARRAY [0..12] OF CHAR{'M','a','x','E','l','m','t',' ',' ',' ','=',' ','\000'}); 
        WriteI (StdError, VAL (   m2tom3_with_25.MaxElmt,INTEGER ) , 0); WriteNl (StdError);
        WriteS (StdError, ARRAY [0..12] OF CHAR{'L','a','s','t','B','i','t','s','e','t','=',' ','\000'}); 
        WriteI (StdError, VAL (   m2tom3_with_25.LastBitset,INTEGER ) , 0); WriteNl (StdError);
        WriteS (StdError, ARRAY [0..12] OF CHAR{'C','a','r','d',' ',' ',' ',' ',' ',' ','=',' ','\000'}); 
        WriteI (StdError, VAL (   m2tom3_with_25.Card,INTEGER ) , 0); WriteNl (StdError);
        WriteS (StdError, ARRAY [0..12] OF CHAR{'F','i','r','s','t','E','l','m','t',' ','=',' ','\000'}); 
        WriteI (StdError, VAL (   m2tom3_with_25.FirstElmt,INTEGER ) , 0); WriteNl (StdError);
        WriteS (StdError, ARRAY [0..12] OF CHAR{'L','a','s','t','E','l','m','t',' ',' ','=',' ','\000'}); 
        WriteI (StdError, VAL (   m2tom3_with_25.LastElmt,INTEGER ) , 0); WriteNl (StdError);
      END;
   END PrintSet;

PROCEDURE InitNullSet ( VAR Set : tSet ) 
 = BEGIN
    Sets . InitNullSet ( Set )
  END InitNullSet ;
      
PROCEDURE MakeSet (VAR Set: tSet; MaxSize: Word.T) =
   BEGIN
      Sets.MakeSet (Set, MaxSize);
      CheckSet (Set, ARRAY [0..7] OF CHAR{'M','a','k','e','S','e','t','\000'});
   END MakeSet;
      
PROCEDURE ReleaseSet (VAR Set: tSet) =
   BEGIN
      CheckSet (Set, ARRAY [0..10] OF CHAR{'R','e','l','e','a','s','e','S','e','t','\000'});
      Sets.ReleaseSet (Set);
   END ReleaseSet;

PROCEDURE Union (VAR Set1: tSet; Set2: tSet) =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..5] OF CHAR{'U','n','i','o','n','\000'});
      Sets.Union (Set1, Set2);
   END Union;

PROCEDURE Difference (VAR Set1: tSet; Set2: tSet) =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..10] OF CHAR{'D','i','f','f','e','r','e','n','c','e','\000'});
      Sets.Difference (Set1, Set2);
   END Difference;

PROCEDURE Intersection (VAR Set1: tSet; Set2: tSet) =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..12] OF CHAR{'I','n','t','e','r','s','e','c','t','i','o','n','\000'});
      Sets.Intersection (Set1, Set2);
   END Intersection;

PROCEDURE SymDiff (VAR Set1: tSet; Set2: tSet) =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..7] OF CHAR{'S','y','m','D','i','f','f','\000'});
      Sets.SymDiff (Set1, Set2);
   END SymDiff;

PROCEDURE Complement (VAR Set: tSet) =
   BEGIN
      CheckSet (Set, ARRAY [0..10] OF CHAR{'C','o','m','p','l','e','m','e','n','t','\000'});
      Sets.Complement (Set);
   END Complement;

PROCEDURE Include (VAR Set: tSet; Elmt: Word.T) =
   BEGIN
      CheckSetElmt (Set, Elmt, ARRAY [0..7] OF CHAR{'I','n','c','l','u','d','e','\000'});
      Sets.Include (Set, Elmt);
   END Include;

PROCEDURE Exclude (VAR Set: tSet; Elmt: Word.T) =
   BEGIN
      CheckSetElmt (Set, Elmt, ARRAY [0..7] OF CHAR{'E','x','c','l','u','d','e','\000'});
      Sets.Exclude (Set, Elmt);
   END Exclude;

PROCEDURE Card (VAR Set: tSet): Word.T =
   BEGIN
      CheckSet (Set, ARRAY [0..4] OF CHAR{'C','a','r','d','\000'});
      RETURN Sets.Card (Set);
   END Card;
    
PROCEDURE Size (VAR Set: tSet): Word.T =
   BEGIN
      CheckSet (Set, ARRAY [0..4] OF CHAR{'S','i','z','e','\000'});
      RETURN Sets.Size (Set);
   END Size;

PROCEDURE Minimum (VAR Set: tSet): Word.T =
   BEGIN
      CheckNotEmpty (Set, ARRAY [0..7] OF CHAR{'M','i','n','i','m','u','m','\000'});
      RETURN Sets.Minimum (Set);
   END Minimum;

PROCEDURE Maximum (VAR Set: tSet): Word.T =
   BEGIN
      CheckNotEmpty (Set, ARRAY [0..7] OF CHAR{'M','a','x','i','m','u','m','\000'});
      RETURN Sets.Maximum (Set);
   END Maximum;

PROCEDURE Select (VAR Set: tSet): Word.T =
   BEGIN
      CheckNotEmpty (Set, ARRAY [0..6] OF CHAR{'S','e','l','e','c','t','\000'});
      RETURN Sets.Select (Set);
   END Select;
    
PROCEDURE Extract (VAR Set: tSet): Word.T =
   BEGIN
      CheckNotEmpty (Set, ARRAY [0..7] OF CHAR{'E','x','t','r','a','c','t','\000'});
      RETURN Sets.Extract (Set);
   END Extract;

PROCEDURE IsSubset (Set1, Set2: tSet): BOOLEAN =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..8] OF CHAR{'I','s','S','u','b','s','e','t','\000'});
      RETURN Sets.IsSubset (Set1, Set2);
   END IsSubset;

PROCEDURE IsStrictSubset (Set1, Set2: tSet): BOOLEAN =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..14] OF CHAR{'I','s','S','t','r','i','c','t','S','u','b','s','e','t','\000'});
      RETURN Sets.IsStrictSubset (Set1, Set2);
   END IsStrictSubset;
    
PROCEDURE IsEqual (VAR Set1, Set2: tSet): BOOLEAN =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..7] OF CHAR{'I','s','E','q','u','a','l','\000'});
      RETURN Sets.IsEqual (Set1, Set2);
   END IsEqual;
    
PROCEDURE IsNotEqual (Set1, Set2: tSet): BOOLEAN =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..10] OF CHAR{'I','s','N','o','t','E','q','u','a','l','\000'});
      RETURN Sets.IsNotEqual (Set1, Set2);
   END IsNotEqual;

PROCEDURE IsElement (Elmt: Word.T; VAR Set: tSet): BOOLEAN =
   BEGIN
      CheckSetElmt (Set, Elmt, ARRAY [0..9] OF CHAR{'I','s','E','l','e','m','e','n','t','\000'});
      RETURN Sets.IsElement (Elmt, Set);
   END IsElement;

PROCEDURE IsEmpty (Set: tSet): BOOLEAN =
   BEGIN
      CheckSet (Set, ARRAY [0..7] OF CHAR{'I','s','E','m','p','t','y','\000'});
      RETURN Sets.IsEmpty (Set);
   END IsEmpty;
    
PROCEDURE Forall (Set: tSet; Proc: ProcOftElementToBool): BOOLEAN =
   BEGIN
      CheckSet (Set, ARRAY [0..6] OF CHAR{'F','o','r','a','l','l','\000'});
      RETURN Sets.Forall (Set, Proc);
   END Forall;
    
PROCEDURE Exists (Set: tSet; Proc: ProcOftElementToBool): BOOLEAN =
   BEGIN
      CheckSet (Set, ARRAY [0..6] OF CHAR{'E','x','i','s','t','s','\000'});
      RETURN Sets.Exists (Set, Proc);
   END Exists;
    
PROCEDURE Exists1 (Set: tSet; Proc: ProcOftElementToBool): BOOLEAN =
   BEGIN
      CheckSet (Set, ARRAY [0..7] OF CHAR{'E','x','i','s','t','s','1','\000'});
      RETURN Sets.Exists1 (Set, Proc);
   END Exists1;

PROCEDURE Assign (VAR Set1: tSet; Set2: tSet) =
   BEGIN
      CheckSetSet (Set1, Set2, ARRAY [0..6] OF CHAR{'A','s','s','i','g','n','\000'});
      Sets.Assign (Set1, Set2);
   END Assign;

PROCEDURE AssignElmt (VAR Set: tSet; Elmt: Word.T) =
   BEGIN
      CheckSetElmt (Set, Elmt, ARRAY [0..10] OF CHAR{'A','s','s','i','g','n','E','l','m','t','\000'});
      Sets.AssignElmt (Set, Elmt);
   END AssignElmt;

PROCEDURE AssignEmpty (VAR Set: tSet) =
   BEGIN
      CheckSet (Set, ARRAY [0..11] OF CHAR{'A','s','s','i','g','n','E','m','p','t','y','\000'});
      Sets.AssignEmpty (Set);
   END AssignEmpty;

PROCEDURE ForallDo (Set: tSet; Proc: ProcOftElement) =
   BEGIN
      CheckSet (Set, ARRAY [0..8] OF CHAR{'F','o','r','a','l','l','D','o','\000'});
      Sets.ForallDo (Set, Proc);
   END ForallDo;

PROCEDURE ReadSet (f: tFile; VAR Set: tSet) =
   BEGIN
      CheckSet (Set, ARRAY [0..7] OF CHAR{'R','e','a','d','S','e','t','\000'});
      Sets.ReadSet (f, Set);
   END ReadSet;

PROCEDURE WriteSet (f: tFile; Set: tSet) =
   BEGIN
      CheckSet (Set, ARRAY [0..8] OF CHAR{'W','r','i','t','e','S','e','t','\000'});
      Sets.WriteSet (f, Set);
   END WriteSet;

BEGIN
END SetsC.

