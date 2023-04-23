(* error listing *)

(* $Id: Listing.mi,v 1.3 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: Listing.mi,v $
 * Revision 1.3  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/11  18:45:03  grosch
 * layout improvements
 * 
 * Revision 1.1  89/01/23  15:46:50  vielsack
 * fixed bug in handling no position
 * 
 * Revision 1.0  88/10/04  14:26:50  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE Listing;

IMPORT Word;
FROM SYSTEM IMPORT SHORTCARD;
FROM    ReuseIO              IMPORT  StdInput,       StdError,       tFile,
                                EndOfFile,      WriteNl,        WriteC;
FROM    Memory          IMPORT  Alloc,          Free;
FROM    Strings         IMPORT  tString,        ReadL,          WriteL;



CONST
  ColFlag  = '^';
  LineFlag = '@';

TYPE
  tErrPtr  =  UNTRACED BRANDED REF  tErrElmt;
  tErrElmt =  RECORD
                code, class, line, column, infcl   : INTEGER;
                info       : ADDRESS := NIL;
                infoTraced : REFANY := NIL;
                next       : tErrPtr;
              END;

VAR
  start, stop, last, read: tErrPtr;
  SourceLine : SHORTCARD;

PROCEDURE PutError
  (Code,Class,Line,Column,InfoClass: Word.T;
   Info: ADDRESS := NIL; InfoTraced: REFANY := NIL) =
  VAR err : tErrPtr;
  BEGIN
    err := Alloc (BYTESIZE (tErrElmt));
    IF Line = 0 THEN Line := LAST (SHORTCARD) END;
    WITH m2tom3_with_1=err^ DO
      m2tom3_with_1.code    := Code;
      m2tom3_with_1.class   := Class;
      m2tom3_with_1.line    := Line;
      m2tom3_with_1.column  := Column;
      m2tom3_with_1.infcl   := InfoClass;
      m2tom3_with_1.info    := Info;
      m2tom3_with_1.infoTraced := InfoTraced;
    END;

    IF start = NIL THEN
                                                 (* list is emty *)
      start := err;
      read  := err;
      stop  := err;
      err^.next := NIL;
      last  := err;

    ELSIF (Line < start^.line) OR
    (  (Line = start^.line) AND (Column < start^.column) ) THEN
                                                (* insert before start *)
      err^.next := start;
      start := err;
      read  := err;
    
    ELSE                                
      IF (Line > stop^.line) OR
      (  (Line = stop^.line) AND (Column >= stop^.column)  )  THEN
                                                (* insert after stop    *)
        last := stop;
        stop := err;
      ELSIF (Line > last^.line) OR
      (  (Line = last^.line) AND (Column >= last^.column)  )  THEN
                                                (* insert after last    *)
        
      ELSE
                                                (* insert after start   *)
        last := start;
      END;


      WHILE (last^.next # NIL) AND 
       (   (Line > last^.next^.line) OR
         ( (Line = last^.next^.line) AND (Column >= last^.next^.column) )  ) DO
                                                (* find exact position *)
        last := last^.next;
      END;

      err^.next := last^.next;
      last^.next := err;
      last := err;
    END;
  END PutError;

PROCEDURE HasError (): BOOLEAN =
  VAR Buf : tString;
  BEGIN
    IF start = NIL THEN
      IF ListMode = tListMode.Listing THEN
        WHILE NOT EndOfFile (SourceFile) DO
          ReadL (SourceFile, Buf);
          WriteL (ListFile, Buf);
        END;
        WriteC (ListFile, LineFlag);
      END;
    END;
    RETURN start # NIL;
  END HasError;

PROCEDURE GetError
  (VAR Code,Class,Line,Column,InfoClass: Word.T;
   VAR Info: ADDRESS; VAR InfoTraced: REFANY) =
  VAR
    Next : tErrPtr;
    col  : SHORTCARD;
    Buf : tString;
  BEGIN
    WITH m2tom3_with_2=start^ DO
      Code       := m2tom3_with_2.code;
      Class      := m2tom3_with_2.class;
      Line       := m2tom3_with_2.line;
      Column     := m2tom3_with_2.column;
      InfoClass  := m2tom3_with_2.infcl;
      Info       := m2tom3_with_2.info;
      InfoTraced := m2tom3_with_2.infoTraced;
      Next       := m2tom3_with_2.next;
    END;

    Free (BYTESIZE (tErrElmt), start);

    IF ListMode = tListMode.Listing THEN
      IF read = start THEN
        LOOP
          IF EndOfFile (SourceFile) THEN EXIT END;
          IF SourceLine >= Line THEN EXIT END;
          ReadL (SourceFile, Buf);
          WriteL (ListFile, Buf);
          INC (SourceLine);
        END;
        WriteC (ListFile, LineFlag);
        col := 2;
        WHILE (read # NIL) AND (read^.line = Line) DO
          WHILE (col < read^.column) DO
            WriteC (ListFile, ' ');
            INC (col);
          END;
          IF col = read^.column THEN
            WriteC (ListFile, ColFlag);
            INC (col);
          END;
          read := read^.next;
        END;
        WriteNl (ListFile);
      END;
      WriteC (ListFile, LineFlag);
    END;

    IF last = start THEN
      last := Next;
    END;

    IF stop = start THEN
      stop := Next;
    END;

    start := Next;
    IF Line = LAST (SHORTCARD) THEN Line := 0; END;
  END GetError;

BEGIN
  start := NIL;
  read  := NIL;
  stop  := NIL;
  last  := NIL;
  SourceFile := StdInput;
  ListFile := StdError;
  ListMode := tListMode.NoListing;
  SourceLine := 0;
END Listing.

