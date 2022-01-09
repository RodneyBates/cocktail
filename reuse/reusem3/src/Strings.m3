
(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

 UNSAFE MODULE Strings;

IMPORT Text;

FROM General    IMPORT Exp10;
FROM ReuseIO            IMPORT tFile, StdError, ReadC, WriteC, WriteNl;

IMPORT  Word, ReuseIO;

CONST   EolCh   = '\012';

VAR     reported: BOOLEAN;
VAR     MyCHR   : ARRAY [0 .. 15] OF CHAR;

PROCEDURE Error() =
   BEGIN
      ReuseIO.WriteS (StdError, ARRAY [0..25] OF CHAR{'s','t','r','i','n','g',' ','t','o','o',' ','l','o','n','g',',',' ','m','a','x','.',' ','2','5','5','\000'});
      ReuseIO.WriteNl (StdError);
   END Error;

PROCEDURE Assign        (VAR s1: tString; READONLY s2: tString) =
   (* Zuweisung von Zeichenketten                       *)
   BEGIN
   (* s1 := s2; *)
      WITH m2tom3_with_49=s2 DO
         FOR i := 1 TO m2tom3_with_49.Length DO
            s1.Chars [i] := m2tom3_with_49.Chars [i];
         END;
         s1.Length := m2tom3_with_49.Length;
      END;
   END Assign;

PROCEDURE AssignEmpty   (VAR s: tString) =
   (* leere Zeichenkette erzeugen                       *)
   BEGIN
      s.Length := 0;
      reported := FALSE;
   END AssignEmpty;

PROCEDURE Concatenate   (VAR s1: tString; READONLY s2: tString) =
   (* Returns in parameter 's1' the concatenation       *)
   (* of the strings 's1' and 's2'.                     *)
   BEGIN
      IF (s1.Length + s2.Length) > cMaxStrLength THEN
         Error();
      ELSE
         WITH m2tom3_with_50=s1 DO
            FOR i := 1 TO s2.Length DO
               m2tom3_with_50.Chars [m2tom3_with_50.Length+i] := s2.Chars [i];
            END;
            INC (m2tom3_with_50.Length, s2.Length);
         END;
      END;
   END Concatenate;

PROCEDURE Append        (VAR s: tString; c: CHAR) =
   (* 1 Zeichen an eine Zeichenkette anhaengen          *)
   BEGIN
      IF s.Length = cMaxStrLength THEN
         IF NOT reported THEN
            Error();
            reported := TRUE;
         END;
      ELSE
         INC (s.Length);
         s.Chars [s.Length] := c;
      END;
   END Append;

PROCEDURE Length        (READONLY s: tString)                        : Word.T =
   (* Laenge einer Zeichenkette                         *)
   BEGIN
      RETURN s.Length;
   END Length;

PROCEDURE IsEqual       (READONLY s1, s2: tString)                   : BOOLEAN =
   (* Pruefung von 2 Zeichenketten auf Gleichheit       *)
   BEGIN
      IF s1.Length # s2.Length THEN
         RETURN FALSE;
      ELSE
         FOR i := 1 TO s1.Length DO
            IF s1.Chars [i] # s2.Chars [i] THEN
               RETURN FALSE;
            END;
         END;
      END;
      RETURN TRUE;
   END IsEqual;

PROCEDURE IsInOrder     (READONLY s1, s2: tString): BOOLEAN =
   (* Pruefung von 2 Zeichenketten auf lexikographische Ordnung *)
   VAR
      rank1, rank2: Word.T;
   BEGIN
      FOR i := 1 TO MIN (s1.Length, s2.Length) DO
         rank1 := Rank (s1.Chars [i]);
         rank2 := Rank (s2.Chars [i]);
         IF rank1 < rank2 THEN
            RETURN TRUE;
         ELSIF rank1 > rank2 THEN
            RETURN FALSE;
         END;
      END;
      RETURN s1.Length <= s2.Length;
   END IsInOrder;

PROCEDURE Rank (ch: CHAR): Word.T =
   (* Abbildung aller Zeichen auf einen Rang
      gemaess ihrer lexikographischen Ordnung           *)
   BEGIN
      RETURN ORD (ch);   (* maschinenabhaengig *)
   END Rank;

PROCEDURE Exchange      (VAR s1, s2: tString) =
   (* Vertauschen von 2 Zeichenketten                   *)
   VAR temp: tString;
   BEGIN
      Assign (temp, s1  );
      Assign (s1  , s2  );
      Assign (s2  , temp);
   END Exchange;

PROCEDURE SubString (READONLY s1: tString; from, to: tStringIndex; VAR s2: tString) =
   (* Returns in 's2' the substring from 's1' com-      *)
   (* prising the characters between 'from' and 'to'.   *)
   (* PRE 1 <= from <= Length (s1)                      *)
   (* PRE 1 <=  to  <= Length (s1)                      *)
   BEGIN
      WITH m2tom3_with_51=s2 DO
         m2tom3_with_51.Length := 0;
         FOR i := from TO to DO
            INC (m2tom3_with_51.Length);
            m2tom3_with_51.Chars [m2tom3_with_51.Length] := s1.Chars [i];
         END;
      END;
   END SubString;

PROCEDURE Char          (READONLY s: tString; i: tStringIndex)       : CHAR =
   (* liefert ein Zeichen einer Zeichenkette: s [index] *)
   (* PRE 1 <= index <= Length (s)                      *)
   BEGIN
      RETURN s.Chars [i];
   END Char;

PROCEDURE ArrayToString (READONLY a: ARRAY OF CHAR; VAR s: tString) =
   VAR i: tStringIndex;
   BEGIN
      i := 0;
      LOOP
         IF a [i] = '\000' THEN EXIT; END;
         s.Chars [i+1] := a [i];
         INC (i);
         IF i > LAST (a) THEN EXIT; END;
      END;
      s.Length := i;
   END ArrayToString;

PROCEDURE TextToString	(t:TEXT; VAR s: tString) =
   VAR length: INTEGER;
   BEGIN
     IF t = NIL THEN t := "" END;
     length := Text.Length (t);
     Text.SetChars (SUBARRAY (s.Chars, 1, length), t);
     s.Length := length;
   END TextToString;

PROCEDURE StringToText (READONLY s: tString): TEXT =
  BEGIN
    IF s.Length <= 0 THEN RETURN "" END;
    RETURN Text.FromChars (SUBARRAY(s.Chars, 1, s.Length));
  END StringToText;

PROCEDURE StringToArray (READONLY s: tString; VAR a: ARRAY OF CHAR) =
   BEGIN
      FOR i := 1 TO s.Length DO
         a [i-1] := s.Chars [i];
      END;
      a [s.Length] := '\000';
   END StringToArray;

PROCEDURE StringToInt   (READONLY s: tString)                        : INTEGER =
   (* Returns the integer value represented by 's'.     *)
   VAR
      start     : tStringIndex;
      n         : INTEGER;
      negative  : BOOLEAN;
   BEGIN
      CASE s.Chars [1] OF
      | '+' => negative := FALSE; start := 2;
      | '-' => negative := TRUE ; start := 2;
      ELSE    negative := FALSE; start := 1;
      END;
      n := 0;
      FOR i := start TO s.Length DO
         n := (n * 10) + LOOPHOLE (ORD (s.Chars [i]) - ORD ('0'),INTEGER);
      END;
      IF negative
      THEN RETURN - n;
      ELSE RETURN   n;
      END;
   END StringToInt;

PROCEDURE StringToNumber (READONLY s: tString; Base: Word.T) : Word.T =
   (* Returns the integer value represented by 's'      *)
   (* to the base 'Base'.                               *)
   VAR
      n : Word.T;
      ch: CHAR;
   BEGIN
      n := 0;
      FOR i := 1 TO s.Length DO
         ch := s.Chars [i];
         IF ('A' <= ch) AND (ch <= 'F') THEN
            n := (n * Base) + ORD (ch) - ORD ('A') + 10;
         ELSIF ('a' <= ch) AND (ch <= 'f') THEN
            n := (n * Base) + ORD (ch) - ORD ('a') + 10;
         ELSE
            n := (n * Base) + ORD (ch) - ORD ('0');
         END;
      END;
      RETURN n;
   END StringToNumber;

PROCEDURE StringToReal  (READONLY Fs: tString)                        : REAL =
   (* Returns the real value represented by 's'.        *)
   CONST
      MaxInt            = 2147483647;   (* 2 ** 31 - 1 *)
      MaxIntDiv10       = MaxInt DIV 10;
   VAR
      n                 : REAL;
      Mantissa          : CARDINAL;
      Exponent          : INTEGER;
      MantissaNeg       : BOOLEAN;
      ExponentNeg       : BOOLEAN;
      FractionDigits    : Word.T;
      TruncatedDigits   : Word.T;
      ch                : CHAR;
      i                 : tStringIndex;
      s                 : tString;
   BEGIN
      MantissaNeg       := FALSE;
      Mantissa          := 0;
      Exponent          := 0;
      FractionDigits    := 0;
      TruncatedDigits   := 0;
      i                 := 0;

      Assign (s, Fs);
      Append (s, ' ');          (* ASSERT Length (s) < cMaxStrLength    *)
      INC (i); ch := s.Chars [i];

      CASE ch OF                                (* handle sign          *)
      | '+' => INC (i); ch := s.Chars [i];
      | '-' => INC (i); ch := s.Chars [i]; MantissaNeg := TRUE;
      | 'E' ,
        'e' => Mantissa := 1;
      ELSE
      END;

      WHILE ('0' <= ch) AND (ch <= '9') DO      (* integer part         *)
         IF Mantissa <= MaxIntDiv10 THEN
            Mantissa := 10 * Mantissa;
            IF Mantissa 
               <= MaxInt - (ORD (ch) - ORD ('0')) THEN
               INC (Mantissa, ORD (ch) - ORD ('0') );
            ELSE
               INC (TruncatedDigits);
            END;
         ELSE
            INC (TruncatedDigits);
         END;
         INC (i); ch := s.Chars [i];
      END;

      IF ch = '.' THEN INC (i); ch := s.Chars [i]; END; (* decimal point        *)

      WHILE ('0' <= ch) AND (ch <= '9') DO      (* fractional part      *)
         IF Mantissa <= MaxIntDiv10 THEN
            Mantissa := 10 * Mantissa;
            IF Mantissa 
               <= MaxInt - (ORD (ch) - ORD ('0')) THEN
               INC (Mantissa, ORD (ch) - ORD ('0') );
            ELSE
               INC (TruncatedDigits);
            END;
         ELSE
            INC (TruncatedDigits);
         END;
         INC (FractionDigits);
         INC (i); ch := s.Chars [i];
      END;

      IF ch = 'E' THEN                          (* exponent             *)
         INC (i); ch := s.Chars [i];

         CASE ch OF
         |  '+' => ExponentNeg := FALSE; INC (i); ch := s.Chars [i];
         |  '-' => ExponentNeg := TRUE ; INC (i); ch := s.Chars [i];
         ELSE     ExponentNeg := FALSE;
         END;

         WHILE ('0' <= ch) AND (ch <= '9') DO
            Exponent := (10 * Exponent) + LOOPHOLE (ORD (ch) - ORD ('0'),INTEGER);
            INC (i); ch := s.Chars [i];
         END;

         IF ExponentNeg THEN
            Exponent := - Exponent;
         END;
      END;

      DEC (Exponent, FractionDigits - TruncatedDigits);
      n := FLOAT (Mantissa) * Exp10 (Exponent);
      IF MantissaNeg
      THEN RETURN - n;
      ELSE RETURN   n;
      END;
   END StringToReal;

PROCEDURE IntToString   (n: INTEGER; VAR s: tString) =
   (* Returns in 's' the string representation of 'n'.  *)
   VAR
      j : tStringIndex;
      length    : tStringIndex;
      digits    : ARRAY [0 .. 10] OF CHAR;
   BEGIN
      IF n < 0 THEN
         s.Chars [1] := '-';
         j := 1;
         n := - n;
      ELSE
         j := 0;
      END;
      length := 0;
      REPEAT
         INC (length);
         digits [length] := MyCHR [n MOD 10];
         n := n DIV 10;
      UNTIL n = 0;
      FOR i := length TO 1 BY -1 DO
         INC (j);
         s.Chars [j] := digits [i];
      END;
      s.Length := j;
   END IntToString;

PROCEDURE ReadS         (f: tFile; VAR s: tString; FieldWidth: tStringIndex) =
   (* Read 'FieldWidth' characters as string 's'        *)
   (* from file 'f'.                                    *)
   BEGIN
      FOR i := 1 TO FieldWidth DO
         s.Chars [i] := ReadC (f);
      END;
      s.Length := FieldWidth;
   END ReadS;

PROCEDURE ReadL         (f: tFile; VAR s: tString) =
   (* Read rest of line as string 's' from file 'f'.    *)
   VAR
      i : tStringIndex;
      ch: CHAR;
   BEGIN
      i := 0;
      LOOP
         ch := ReadC (f);
         IF ch = EolCh THEN EXIT; END;
         IF i = cMaxStrLength THEN
            REPEAT
            UNTIL ReadC (f) = EolCh;
            EXIT;
         END;
         INC (i);
         s.Chars [i] := ch;
      END;
      s.Length := i;
   END ReadL;

PROCEDURE WriteS        (f: tFile; READONLY s: tString) =
   (* Write string 's' to file 'f'.                     *)
   BEGIN
      FOR i := 1 TO s.Length DO
         WriteC (f, s.Chars [i]);
      END;
   END WriteS;

PROCEDURE WriteL        (f: tFile; READONLY s: tString) =
   (* Write string 's' as complete line to file 'f'.    *)
   BEGIN
      WriteS (f, s);
      WriteNl (f);
   END WriteL;

BEGIN
   MyCHR [ 0] := '0';
   MyCHR [ 1] := '1';
   MyCHR [ 2] := '2';
   MyCHR [ 3] := '3';
   MyCHR [ 4] := '4';
   MyCHR [ 5] := '5';
   MyCHR [ 6] := '6';
   MyCHR [ 7] := '7';
   MyCHR [ 8] := '8';
   MyCHR [ 9] := '9';
   MyCHR [10] := 'A';
   MyCHR [11] := 'B';
   MyCHR [12] := 'C';
   MyCHR [13] := 'D';
   MyCHR [14] := 'E';
   MyCHR [15] := 'F';
END Strings.

