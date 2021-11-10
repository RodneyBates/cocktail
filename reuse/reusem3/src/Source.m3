
(* Ich, Doktor Josef Grosch, Informatiker, Juli 1992 *)

 UNSAFE MODULE Source;


IMPORT Word;
FROM System	IMPORT tFile, OpenInput, Read, Close;

PROCEDURE BeginSource (READONLY FileName: ARRAY OF CHAR): tFile =
   BEGIN
      RETURN OpenInput (FileName);
   END BeginSource;

PROCEDURE GetLine (File: tFile; Buffer: ADDRESS; Size: Word.T): INTEGER =
   <*UNUSED*> CONST IgnoreChar = ' ';
   <*UNUSED*> VAR n : INTEGER;
   <*UNUSED*> VAR BufferPtr : UNTRACED BRANDED REF  ARRAY [0..30000] OF CHAR;
   BEGIN
   (* # ifdef Dialog
      n := Read (File, Buffer, Size);
      (* Add dummy after newline character in order to supply a lookahead for rex. *)
      (* This way newline tokens are recognized without typing an extra line.      *)
      BufferPtr := Buffer;
      IF (n > 0) AND (BufferPtr^[n - 1] = 012C) THEN BufferPtr^[n] := IgnoreChar; INC (n); END;
      RETURN n;
      # else *)
      RETURN Read (File, Buffer, Size);
   (* # endif *)
   END GetLine;

PROCEDURE CloseSource (File: tFile) =
   BEGIN
      Close (File);
   END CloseSource;

BEGIN
END Source.

