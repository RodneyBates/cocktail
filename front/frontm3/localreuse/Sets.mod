(* $Id: Sets.mi,v 1.4 1991/11/21 14:33:17 grosch rel $ *)

(* $Log: Sets.mi,v $

 * RMB July 98 Documentation/name changes. 

 * RMB 97/06/05 Changed ForAllDo and IsElement to not choke on NIL
                BitsetPtr, since some tree dumps call 
                WriteSet for sets which are not in use and need
                no allocated array. 

 * RMB 97/06/05 Added InitNullSet, since some tree dumps call
                WriteSet for sets which are not in use and need
                no allocated array. 

 * RMB 93/10/13 Rework types for WRL Modula-2.

 * Revision 1.4  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.3  90/05/30  17:08:45  grosch
 * bug fixes in Complement and ReadSet
 * 
 * Revision 1.2  89/09/20  11:50:33  grosch
 * turned many FOR into WHILE loops to increase efficiency
 * 
 * Revision 1.1  89/01/09  17:13:35  grosch
 * added functions Size, Minimum, and Maximum
 * 
 * Revision 1.0  88/10/04  11:47:13  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

IMPLEMENTATION MODULE Sets;

FROM SYSTEM	IMPORT TSIZE;
FROM General	IMPORT MinSHORTCARD, MaxSHORTCARD;
FROM DynArray	IMPORT MakeArray, ReleaseArray;
FROM IO		IMPORT tFile, StdError, ReadCard, ReadC, WriteCard, WriteC, WriteS, WriteNl;

CONST
   BitsPerBitset	= 32;
   BitsPerByte		= 8;
   BytesPerBitset	= BitsPerBitset DIV BitsPerByte;
   NoCard		= MAX ( tInternalElmt ) ;

VAR
   AllBits		: BITSET;

PROCEDURE InitNullSet ( VAR Set : tSet ) 

; BEGIN 
    WITH Set 
    DO
      MaxElmt := 0 
    ; LastBitset := 0 
    ; Card := 0 
    ; FirstElmt := 0 
    ; LastElmt := 0 
    ; BitsetPtr := NIL 
    END (* WITH Set *) 
  END InitNullSet ; 

PROCEDURE MakeSet (VAR Set: tSet; MaxElement: tElement);
   VAR BitsetCount : LONGINT;
   BEGIN
      WITH Set DO
	 BitsetCount 
           := VAL ( LONGINT
                  , (MaxElement + BitsPerBitset - MaxElement MOD BitsPerBitset)
	            DIV BitsPerBitset
                  );
	 MakeArray (BitsetPtr, BitsetCount, BytesPerBitset);
	 MaxElmt := VAL ( tInternalElmt , MaxElement ) ;
	 LastBitset := VAL ( SHORTCARD , BitsetCount - 1 );
	 AssignEmpty (Set);
      END;
   END MakeSet;
      
PROCEDURE ReleaseSet (VAR Set: tSet);
   VAR BitsetCount : LONGINT;
   BEGIN
      BitsetCount := VAL ( LONGINT , Set.LastBitset + 1 );
      ReleaseArray (Set.BitsetPtr, BitsetCount, BytesPerBitset);
      InitNullSet ( Set ) 
   END ReleaseSet;

PROCEDURE Union (VAR Set1: tSet; Set2: tSet);
   VAR i : SHORTCARD;
   BEGIN
      WITH Set1 DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    BitsetPtr^[i] := BitsetPtr^[i] + Set2.BitsetPtr^[i];
	    INC (i);
	 END;
	 Card      := VAL ( tInternalElmt , NoCard );
	 FirstElmt := MinSHORTCARD (FirstElmt, Set2.FirstElmt);
	 LastElmt  := MaxSHORTCARD (LastElmt, Set2.LastElmt);
      END;
   END Union;

PROCEDURE Difference (VAR Set1: tSet; Set2: tSet);
   VAR i : SHORTCARD;
   BEGIN
      WITH Set1 DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    BitsetPtr^[i] := BitsetPtr^[i] - Set2.BitsetPtr^[i];
	    INC (i);
	 END;
	 Card := VAL ( tInternalElmt , NoCard );
      END;
   END Difference;

PROCEDURE Intersection (VAR Set1: tSet; Set2: tSet);
   VAR i : SHORTCARD;
   BEGIN
      WITH Set1 DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    BitsetPtr^[i] := BitsetPtr^[i] * Set2.BitsetPtr^[i];
	    INC (i);
	 END;
	 Card      := VAL ( tInternalElmt , NoCard );
	 FirstElmt := MaxSHORTCARD (FirstElmt, Set2.FirstElmt);
	 LastElmt  := MinSHORTCARD (LastElmt, Set2.LastElmt);
      END;
   END Intersection;

PROCEDURE SymDiff (VAR Set1: tSet; Set2: tSet);
   VAR i : SHORTCARD;
   BEGIN
      WITH Set1 DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    BitsetPtr^[i] := BitsetPtr^[i] / Set2.BitsetPtr^[i];
	    INC (i);
	 END;
	 Card      := VAL ( tInternalElmt , NoCard );
	 FirstElmt := MinSHORTCARD (FirstElmt, Set2.FirstElmt);
	 LastElmt  := MaxSHORTCARD (LastElmt, Set2.LastElmt);
      END;
   END SymDiff;

PROCEDURE Complement (VAR Set: tSet);
   VAR i : SHORTCARD;
   BEGIN
      WITH Set DO
	 i := 0;
	 WHILE i < LastBitset DO
	    BitsetPtr^[i] := AllBits - BitsetPtr^[i];
	    INC (i);
	 END;
      (* if MOCKA or WRL *)
	 BitsetPtr^[LastBitset] 
           := BITSET {0 .. MaxElmt MOD BitsPerBitset} - BitsetPtr^[LastBitset];
      (* else
	 s := {};
	 FOR i := 0 TO VAL ( SHORTCARD , MaxElmt MOD BitsPerBitset ) DO
	    INCL (s, SHORTCARD (i));
	 END;
	 BitsetPtr^[LastBitset] := s - BitsetPtr^[LastBitset];
         endif *)
	 IF Card # VAL ( tInternalElmt , NoCard ) THEN
	    Card   := MaxElmt + 1 - Card;
	 END;
	 FirstElmt := 0;
	 LastElmt  := MaxElmt;
      END;
   END Complement;

PROCEDURE Include (VAR Set: tSet; Elmt: tElement);
   BEGIN
      WITH Set DO
	 INCL (BitsetPtr^[VAL ( SHORTCARD , Elmt DIV BitsPerBitset ) ]
              , Elmt MOD BitsPerBitset
              );
	 Card      := VAL ( tInternalElmt , NoCard );
      (* FirstElmt := Min (FirstElmt, Elmt);
	 LastElmt  := Max (LastElmt, Elmt); *)
	 IF FirstElmt > VAL ( tInternalElmt , Elmt ) 
         THEN FirstElmt := VAL ( tInternalElmt , Elmt ) ; END;
	 IF LastElmt  < VAL ( tInternalElmt , Elmt ) 
         THEN LastElmt  := VAL ( tInternalElmt , Elmt ) ; END;
      END;
   END Include;

PROCEDURE Exclude (VAR Set: tSet; Elmt: tElement);
   BEGIN
      WITH Set DO
	 EXCL ( BitsetPtr^[ VAL ( SHORTCARD , Elmt DIV BitsPerBitset ) ]
              , Elmt MOD BitsPerBitset
              );
	 Card      := VAL ( tInternalElmt , NoCard );
	 IF ( VAL ( tInternalElmt , Elmt ) = FirstElmt) 
            AND ( VAL ( tInternalElmt , Elmt ) < MaxElmt) THEN
	    INC (FirstElmt);
	 END;
	 IF ( VAL ( tInternalElmt , Elmt ) = LastElmt ) 
            AND (Elmt > 0) THEN
	    DEC (LastElmt);
	 END;
      END;
   END Exclude;

PROCEDURE Card (VAR Set: tSet): tElement;
   VAR i : tInternalElmt;
   BEGIN
      WITH Set DO
	 IF Card = VAL ( tInternalElmt , NoCard ) THEN
	    Card := 0;
	    FOR i := FirstElmt TO LastElmt DO
	       IF IsElement ( VAL ( tElement , i ) , Set) 
               THEN INC (Card); END;
	    END;
	 END;
	 RETURN VAL ( tElement , Card ) ;
      END;
   END Card;
    
PROCEDURE Size (VAR Set: tSet): tElement;
   BEGIN
      RETURN VAL ( tElement , Set.MaxElmt ) ;
   END Size;

PROCEDURE Minimum (VAR Set: tSet): tElement;
   VAR i : tInternalElmt;
   BEGIN
      WITH Set DO
	 i := FirstElmt;
	 WHILE i <= LastElmt DO
	    IF IsElement ( VAL ( tElement , i ) , Set) THEN
	       FirstElmt := i;
	       RETURN VAL ( tElement , i ) ;
	    END;
	    INC (i);
	 END;
	 RETURN 0;
      END;
   END Minimum;

PROCEDURE Maximum (VAR Set: tSet): tElement;
   VAR i : tInternalElmt;
   BEGIN
      WITH Set DO
	 i := LastElmt;
	 WHILE i >= FirstElmt DO
	    IF IsElement ( VAL ( tElement , i ) , Set) THEN
	       LastElmt := i;
	       RETURN VAL ( tElement , i ) ;
	    END;
	    DEC (i);
	 END;
	 RETURN 0;
      END;
   END Maximum;

PROCEDURE Select (VAR Set: tSet): tElement;
   BEGIN
      RETURN Minimum (Set);
   END Select;
    
PROCEDURE Extract (VAR Set: tSet): tElement;
   VAR i : tElement;
   BEGIN
      i := Minimum (Set);
      Exclude (Set, i);
      RETURN i;
   END Extract;

PROCEDURE IsSubset (Set1, Set2: tSet): BOOLEAN;
   VAR i : SHORTCARD;
   BEGIN
      WITH Set1 DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    IF NOT (BitsetPtr^[i] <= Set2.BitsetPtr^[i]) THEN RETURN FALSE; END;
	    INC (i);
	 END;
	 RETURN TRUE;
      END;
   END IsSubset;

PROCEDURE IsStrictSubset (Set1, Set2: tSet): BOOLEAN;
   BEGIN
      RETURN IsSubset (Set1, Set2) AND IsNotEqual (Set1, Set2);
   END IsStrictSubset;
    
PROCEDURE IsEqual (VAR Set1, Set2: tSet): BOOLEAN;
   VAR i : SHORTCARD;
   BEGIN
      WITH Set1 DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    IF BitsetPtr^[i] # Set2.BitsetPtr^[i] THEN RETURN FALSE; END;
	    INC (i);
	 END;
	 RETURN TRUE;
      END;
   END IsEqual;
    
PROCEDURE IsNotEqual (Set1, Set2: tSet): BOOLEAN;
   BEGIN
      RETURN NOT IsEqual (Set1, Set2);
   END IsNotEqual;

PROCEDURE IsElement (Elmt: tElement; VAR Set: tSet): BOOLEAN;
   BEGIN
     IF Set.BitsetPtr = NIL 
     THEN RETURN FALSE 
     ELSE 
       RETURN Elmt MOD BitsPerBitset 
              IN Set.BitsetPtr^[ VAL ( SHORTCARD , Elmt DIV BitsPerBitset ) ]
     END (* IF *) 
   END IsElement;

PROCEDURE IsEmpty (Set: tSet): BOOLEAN;
   VAR i : SHORTCARD;
   VAR b : BITSET;
   BEGIN
      WITH Set DO
	 IF FirstElmt <= LastElmt THEN
	    i := 0;
	    WHILE i <= LastBitset DO
               b := BitsetPtr^[i]; 
	       IF BitsetPtr^[i] # {} 
                  THEN 
                    RETURN FALSE; 
                  END;
	       INC (i);
	    END;
	 END;
	 RETURN TRUE;
      END;
   END IsEmpty;
    
PROCEDURE Forall (Set: tSet; Proc: ProcOftElementToBool): BOOLEAN;
   VAR i : tInternalElmt;
   BEGIN
      WITH Set DO
	 FOR i := FirstElmt TO LastElmt DO
	    IF IsElement ( VAL ( tElement , i ) , Set) 
               AND NOT Proc ( VAL ( tElement , i ) ) 
            THEN RETURN FALSE; END;
	 END;
	 RETURN TRUE;
      END;
   END Forall;
    
PROCEDURE Exists (Set: tSet; Proc: ProcOftElementToBool): BOOLEAN;
   VAR i : tInternalElmt;
   BEGIN
      WITH Set DO
	 FOR i := FirstElmt TO LastElmt DO
	    IF IsElement ( VAL ( tElement , i ) , Set) 
               AND Proc ( VAL ( tElement , i ) ) THEN RETURN TRUE; END;
	 END;
	 RETURN FALSE;
      END;
   END Exists;
    
PROCEDURE Exists1 (Set: tSet; Proc: ProcOftElementToBool): BOOLEAN;
   VAR i, n : tInternalElmt;
   BEGIN
      WITH Set DO
	 n := 0;
	 FOR i := FirstElmt TO LastElmt DO
	    IF IsElement ( VAL ( tElement , i ) , Set) 
               AND Proc ( VAL ( tElement , i ) ) THEN INC (n); END;
	 END;
	 RETURN n = 1;
      END;
   END Exists1;

PROCEDURE Assign (VAR Set1: tSet; Set2: tSet);
   VAR i : SHORTCARD;
   BEGIN
      WITH Set1 DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    BitsetPtr^[i] := Set2.BitsetPtr^[i];
	    INC (i);
	 END;
	 Card      := Set2.Card;
	 FirstElmt := Set2.FirstElmt;
	 LastElmt  := Set2.LastElmt;
      END;
   END Assign;

PROCEDURE AssignElmt (VAR Set: tSet; Elmt: tElement);
   BEGIN
      WITH Set DO
	 AssignEmpty (Set);
	 Include (Set, Elmt);
	 Card      := 1;
	 FirstElmt := VAL ( tInternalElmt , Elmt );
	 LastElmt  := VAL ( tInternalElmt , Elmt );
      END;
   END AssignElmt;

PROCEDURE AssignEmpty (VAR Set: tSet);
   VAR i : SHORTCARD;
   BEGIN
      WITH Set DO
	 i := 0;
	 WHILE i <= LastBitset DO
	    BitsetPtr^[i] := {};
	    INC (i);
	 END;
	 Card      := 0;
	 FirstElmt := MaxElmt;
	 LastElmt  := 0;
      END;
   END AssignEmpty;

PROCEDURE ForallDo (Set: tSet; Proc: ProcOftElement);
   VAR i : tInternalElmt;
   BEGIN
      WITH Set DO
        IF BitsetPtr <> NIL 
        THEN 
 	  FOR i := FirstElmt TO LastElmt DO
	     IF IsElement ( VAL ( tElement , i ) , Set) 
             THEN Proc ( VAL ( tElement , i ) ); END;
	  END;
        END (* IF *) 
      END;
   END ForallDo;

PROCEDURE ReadSet (f: tFile; VAR Set: tSet);
   VAR card	: tInternalElmt;
   BEGIN
      REPEAT UNTIL ReadC (f) = '{';
      AssignEmpty (Set);
      card := 0;
      LOOP
	 IF ReadC (f) = '}' THEN EXIT; END;
	 Include (Set, ReadCard (f));
	 INC (card);
      END;
      Set.Card := card;
   END ReadSet;

VAR g	: tFile;

PROCEDURE WriteSet (f: tFile; Set: tSet);
   BEGIN
      WITH Set DO
      (* WriteS (f, "MaxElmt = "	) ; WriteCard (f, MaxElmt	 , 0);
	 WriteS (f, " LastBitset = "	) ; WriteCard (f, LastBitset, 0);
	 WriteS (f, " Card = "		) ; WriteCard (f, Card	 , 0);
	 WriteS (f, " FirstElmt = "	) ; WriteCard (f, FirstElmt , 0);
	 WriteS (f, " LastElmt = "	) ; WriteCard (f, LastElmt	 , 0);
	 WriteNl (f);
      *)
	 g := f;
	 WriteC (f, '{');
	 ForallDo (Set, WriteElmt);
	 WriteC (f, '}');
      END;
   END WriteSet;

PROCEDURE WriteElmt (Elmt: tElement);
   BEGIN
      WriteC (g, ' ');
      WriteCard (g, Elmt, 0);
   END WriteElmt;

BEGIN
   AllBits := BITSET { 0 .. BitsPerBitset - 1 };
   IF TSIZE (BITSET) # BytesPerBitset THEN
      WriteS (StdError, "TSIZE (BITSET) = ");
      WriteCard (StdError, TSIZE (BITSET), 0);
      WriteNl (StdError);
   END;
END Sets.

