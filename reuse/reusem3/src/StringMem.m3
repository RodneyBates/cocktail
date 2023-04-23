(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

 UNSAFE MODULE StringMem;


IMPORT Word;
FROM Strings    IMPORT tStringIndex, tString;
FROM ReuseIO            IMPORT tFile, StdOutput, WriteC, WriteI, WriteNl, WriteS;

VAR InitialMemorySize := 1024 * 16;
VAR MaxMemorySize : INTEGER := 0;

TYPE Memory             = ARRAY OF CHAR;

VAR
   MemoryPtr            : REF Memory;
   MemorySpaceLeft      : INTEGER;
   MemoryFreePtr        : INTEGER;

PROCEDURE PutString (READONLY s: tString): tStringRef =
   VAR
      NeededSpace       : INTEGER;
      OldMemorySize     : INTEGER;
      NewMemorySize     : INTEGER;
      OldMemoryPtr      : REF Memory; 
      StartPtr          : INTEGER;
   BEGIN
      NeededSpace := VAL (   s.Length,INTEGER ) + 2;
      WHILE MemorySpaceLeft < NeededSpace DO
         OldMemorySize := NUMBER ( MemoryPtr ^ ); 
         OldMemoryPtr := MemoryPtr;
         MemoryPtr := NEW ( REF Memory , OldMemorySize * 2 );
         SUBARRAY ( MemoryPtr ^ , 0 , OldMemorySize ) := OldMemoryPtr ^;
         NewMemorySize := NUMBER ( MemoryPtr ^ );
         MemorySpaceLeft := NewMemorySize - MemoryFreePtr;
         MaxMemorySize := MAX ( MaxMemorySize, NewMemorySize );
      END;
      StartPtr := MemoryFreePtr;
      MemoryPtr^[MemoryFreePtr] := VAL (s.Length DIV 256,CHAR);
      INC (MemoryFreePtr);
      MemoryPtr^[MemoryFreePtr] := VAL (s.Length MOD 256,CHAR);
      INC (MemoryFreePtr);
      FOR i := 1 TO s.Length DO
         MemoryPtr^[MemoryFreePtr] := s.Chars [i];
         INC (MemoryFreePtr);
      END;
      DEC (MemorySpaceLeft, NeededSpace);
      RETURN StartPtr;
   END PutString;

PROCEDURE GetString (r: tStringRef; VAR s: tString) =
   BEGIN
      s.Length := VAL (   Length (r),tStringIndex );
      INC (r, 2);
      FOR i := 1 TO s.Length DO
         s.Chars [i] := MemoryPtr^[r];
         INC (r);
      END;
   END GetString;

PROCEDURE Length (r: tStringRef): Word.T =
   BEGIN
      RETURN (ORD (MemoryPtr^[r]) * 256) + ORD (MemoryPtr^[r+1]);
   END Length;

PROCEDURE IsEqual (r: tStringRef; READONLY s: tString): BOOLEAN =
   BEGIN
      INC (r, 2);
      FOR i := 1 TO s.Length DO
         IF MemoryPtr^[r] # s.Chars [i] THEN RETURN FALSE; END;
         INC (r);
      END;
      RETURN TRUE;
   END IsEqual;

PROCEDURE WriteString (f: tFile; r: tStringRef) =
   BEGIN
      FOR i := r + 2 TO r + 1 + Length (r) DO
         WriteC (f, MemoryPtr^[i]);
      END;
   END WriteString;

PROCEDURE WriteStringMemory() =
   VAR
      StringPtr : INTEGER;
      sLength   : INTEGER;
   BEGIN
      StringPtr := 0;
      WHILE StringPtr < MemoryFreePtr DO
         WriteI (StdOutput, VAL (   StringPtr,INTEGER ) , 5);
         WriteC (StdOutput, ' ');
         WriteString (StdOutput, StringPtr);
         WriteNl (StdOutput);
         sLength 
           := VAL (   Length (StringPtr) + 2,INTEGER ); (* damned MODULA-2 *)
         INC (StringPtr, sLength);
      END;
      WriteNl (StdOutput);
      WriteI (StdOutput, VAL (   StringPtr,INTEGER ) , 5);
      WriteS (StdOutput, ARRAY [0..6] OF CHAR{' ','B','y','t','e','s','\000'});
      WriteNl (StdOutput);
   END WriteStringMemory;

PROCEDURE InitStringMemory() =
   BEGIN
      MemorySpaceLeft := NUMBER ( MemoryPtr ^ );
      MaxMemorySize := MemorySpaceLeft;
      MemoryFreePtr     := 0;
   END InitStringMemory;

BEGIN
   MemoryPtr := NEW ( REF Memory , InitialMemorySize );
   MaxMemorySize := NUMBER ( MemoryPtr ^ );
   InitStringMemory();
END StringMem.

