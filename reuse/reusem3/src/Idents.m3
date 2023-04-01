(* $Id: Idents.mi,v 1.8 1992/06/22 14:23:18 grosch rel $ *)

(* $Log: Idents.mi,v $

 * RMB 93/10/12 Various type changes and conversions. 
 * RMB 94/02/04 Added LookupIdent.

 * Revision 1.8  1992/06/22  14:23:18  grosch
 * cosmetic changes
 *
 * Revision 1.7  1992/03/24  13:50:12  grosch
 * decreased array type size from 100000000 to 1000000 because of C compiler restrictions
 *
 * Revision 1.6  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.5  91/06/07  12:19:54  grosch
 * decreased bounds of flexible arrays
 * 
 * Revision 1.4  91/06/07  11:37:45  grosch
 * increased bounds of flexible arrays
 * 
 * Revision 1.3  89/06/01  18:21:16  grosch
 * added predefined identifier NoIdent
 * 
 * Revision 1.2  89/01/25  12:05:42  grosch
 * added function MaxIdent
 * 
 * Revision 1.1  89/01/21  23:03:34  grosch
 * added file parameter to procedure WriteIdent
 * 
 * Revision 1.0  88/10/04  11:47:01  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

 UNSAFE MODULE Idents;


FROM SYSTEM IMPORT M2LONGINT;
FROM DynArray	IMPORT MakeArray, ExtendArray;
FROM Strings	IMPORT tString, tStringIndex, AssignEmpty;
FROM StringMem	IMPORT tStringRef, PutString, IsEqual;
FROM ReuseIO		IMPORT tFile, StdOutput, WriteC, WriteI, WriteNl, WriteT;

IMPORT Word, Strings, StringMem;

CONST
   InitialTableSize	= 512;
   HashTableSize	= 256;

TYPE
   IdentTableEntry	=
      RECORD 
	 String		: tStringRef;
	 Length		: tStringIndex;
	 Collision	: tIdent;
      END;

   HashIndex		= [0 .. HashTableSize];

VAR
   TablePtr		: UNTRACED BRANDED REF  
                          ARRAY tIdent OF IdentTableEntry;
   IdentTableSize	: M2LONGINT;
   IdentCount		: tIdent;

   HashTable		: ARRAY HashIndex OF tIdent; 

PROCEDURE MakeOrLookup (READONLY s: tString; DoInsertIfAbsent : BOOLEAN ): tIdent =
   VAR
      HashTableIndex	: HashIndex;
      CurIdent		: tIdent;
      lIdentCount	: tIdent;
   BEGIN
      WITH m2tom3_with_4=s DO					(* hash *)
  	 IF m2tom3_with_4.Length = 0 THEN
	    HashTableIndex := 0;
	 ELSE 
	    HashTableIndex := ( ORD (m2tom3_with_4.Chars [1]) 
                                + (ORD (m2tom3_with_4.Chars [m2tom3_with_4.Length]) * 11)
			        + m2tom3_with_4.Length * 26
                              ) 
                              MOD HashTableSize;
	 END;
      END;

      CurIdent := HashTable [HashTableIndex];	(* search *)
      LOOP
	 IF CurIdent = cNoIdent THEN EXIT; END;
	 WITH m2tom3_with_5=TablePtr^[CurIdent] DO
	    IF (m2tom3_with_5.Length = s.Length) AND IsEqual (m2tom3_with_5.String, s) THEN
	       RETURN CurIdent;			(* found *)
	    END;  
	    CurIdent := m2tom3_with_5.Collision;
	 END;
      END;

      IF DoInsertIfAbsent
      THEN
          INC (IdentCount);				(* not found: enter *)
          lIdentCount := IdentCount;		(* damned MODULA *)
          IF lIdentCount = VAL (   IdentTableSize,tIdent ) THEN
             ExtendArray (LOOPHOLE(TablePtr, ADDRESS), IdentTableSize, BYTESIZE (IdentTableEntry));
          END;
          WITH m2tom3_with_6=TablePtr^[IdentCount] DO
             m2tom3_with_6.String		:= PutString (s);
             m2tom3_with_6.Length		:= s.Length;
             m2tom3_with_6.Collision	:= HashTable [HashTableIndex];
          END;
          HashTable [HashTableIndex] := IdentCount;
          RETURN IdentCount
      ELSE
          RETURN cNoIdent
      END (* IF *)
   END MakeOrLookup;

PROCEDURE MakeIdent (READONLY s: tString): tIdent =

   BEGIN
     RETURN MakeOrLookup ( s , TRUE )
   END MakeIdent;

PROCEDURE LookupIdent (READONLY s: tString): tIdent =

   BEGIN
     RETURN MakeOrLookup ( s , FALSE )
   END LookupIdent;

PROCEDURE GetString (i: tIdent; VAR s: tString) =
   BEGIN
      WITH m2tom3_with_7=TablePtr^[i] DO 
	 StringMem.GetString (m2tom3_with_7.String, s);
      END;
   END GetString;

PROCEDURE GetText (i: tIdent): TEXT =
   VAR s: tString;
   BEGIN
      WITH m2tom3_with_7=TablePtr^[i] DO 
	 StringMem.GetString (m2tom3_with_7.String, s);
      END;
      RETURN Strings.StringToText (s);
   END GetText;

PROCEDURE GetStringRef (i: tIdent): tStringRef =
   BEGIN
      RETURN TablePtr^[i].String;
   END GetStringRef;

PROCEDURE MaxIdent (): tIdent =
   BEGIN
      RETURN IdentCount;
   END MaxIdent;

PROCEDURE WriteIdent (f: tFile; i: tIdent) =
   VAR s	: tString;
   BEGIN
      GetString (i, s);
      Strings.WriteS (f, s);
   END WriteIdent;

PROCEDURE WriteIdents() =
   BEGIN
      FOR i := 1 TO IdentCount DO
	 WriteI (StdOutput, VAL (   i,INTEGER ) , 5);
	 WriteC (StdOutput, ' ');
	 WriteIdent (StdOutput, i );
	 WriteNl (StdOutput);
      END;
   END WriteIdents;

PROCEDURE WriteHashTable() =
   VAR
      CurIdent	: tIdent;
      Count	: Word.T;
   BEGIN
      FOR i := 0 TO HashTableSize DO
	 WriteI (StdOutput, i, 5);

	 Count := 0;
	 CurIdent := HashTable [i];
	 WHILE CurIdent # cNoIdent DO
	    INC (Count);
	    CurIdent := TablePtr^[CurIdent].Collision;
	 END;
	 WriteI (StdOutput, Count, 5);

	 CurIdent := HashTable [i];
	 WHILE CurIdent # cNoIdent DO
	    WriteC (StdOutput, ' ');
	    WriteIdent (StdOutput, CurIdent);
	    CurIdent := TablePtr^[CurIdent].Collision;
	 END;
	 WriteNl (StdOutput);
      END;

      WriteNl (StdOutput);
      WriteT (StdOutput, "Idents =");
      WriteI (StdOutput, VAL (   IdentCount,INTEGER ) , 5);
      WriteNl (StdOutput);
   END WriteHashTable;
    
PROCEDURE InitIdents() =
   VAR String	: tString;
   BEGIN
      FOR i := 0 TO HashTableSize DO
	 HashTable [i] := cNoIdent;
      END;
      IdentCount := 0;
      AssignEmpty (String);
      NoIdent := MakeIdent (String);
   END InitIdents;

BEGIN
   IdentTableSize := InitialTableSize;
   MakeArray (LOOPHOLE(TablePtr,ADDRESS), IdentTableSize, BYTESIZE (IdentTableEntry));
   InitIdents();
END Idents.

