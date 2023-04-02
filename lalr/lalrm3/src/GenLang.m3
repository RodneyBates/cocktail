(* generate source parts of the parser *)

(* $Id: GenLang.mi,v 1.10 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: GenLang.mi,v $
 * Revision 1.10  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.9  1992/01/30  14:08:30  grosch
 * redesign of interface to operating system
 *
 * Revision 1.8  1991/12/04  16:23:39  grosch
 * unified escape conventions for all tools
 *
 * Revision 1.7  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.6  90/12/20  19:26:42  grosch
 * removed time stamp from tables
 * 
 * Revision 1.5  90/09/20  17:52:31  grosch
 * calmed down lint
 * 
 * Revision 1.4  90/06/12  17:17:23  grosch
 * layout improvements
 * 
 * Revision 1.3  90/06/12  16:54:16  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 *  
* Revision 1.2  89/05/02  14:36:38  vielsack
 * $$ is used instead of $0
 * $0, $-1, $-2, .. are legal now
 * attribute access is changed for the stacks are now dynamic arrays
 * 
 * Revision 1.1  89/01/12  18:09:43  vielsack
 * line number is printed before an action is output
 * 
 * Revision 1.0  88/10/04  14:36:23  vielsack
 * Initial revision
 * 
 *)

(* Revised Rodney M. Bates: 

   Nov 1999 Optimize out decrements by zero of stack pointers 

*) 

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE GenLang; (* Erzeugung von Modula2- oder C-Quelltexten *)

FROM SYSTEM IMPORT M2LONGINT;
FROM Automaton  IMPORT tIndex, tStateIndex, tProdIndex, tProduction, ProdIndex, ProdArrayPtr, NextProdIndex;
FROM Compress   IMPORT NTableSize, TableSize;
FROM DynArray   IMPORT ReleaseArray;
FROM ArgCheck   IMPORT LineFlag;
FROM Gen        IMPORT NonTermOffset, FirstTerminal, LastTerminal, FirstSymbol,
                        LastSymbol, FirstReadState, LastReadState, FirstReadTermState,
                        LastReadTermState, FirstReadNonTermState, LastReadNonTermState,
                        FirstReduceState, LastReduceState, StartState, StopState,
                        CaseLabels, CaseFlag;
FROM ReuseIO         IMPORT tFile, WriteNl, WriteI, WriteT, WriteC;
FROM Lists      IMPORT tList, IsEmpty, Tail, Head;
FROM Strings    IMPORT tStringIndex, tString, Char, Length;
FROM StringMem  IMPORT tStringRef;
IMPORT Word, StringMem;   (* GetString *)
FROM Idents     IMPORT tIdent, GetString;

FROM TokenTab   IMPORT PosType, TokenError, Vocabulary, TokenToSymbol;
FROM WriteTok   IMPORT tLanguage, Language, SourceFileName;

  PROCEDURE WriteConstants (f: tFile) = (* Ausgabe der Konstanten *)
    BEGIN
      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WriteT (f, "   yyFirstTerminal          = ");
        WriteI (f, FirstTerminal, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyLastTerminal           = ");
        WriteI (f, LastTerminal, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyFirstSymbol            = ");
        WriteI (f, FirstSymbol, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyLastSymbol             = ");
        WriteI (f, LastSymbol, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyTableMax               = ");
        WriteI (f, TableSize, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyNTableMax              = ");
        WriteI (f, NTableSize, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyFirstReadState         = ");
        WriteI (f, FirstReadState, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyLastReadState          = ");
        WriteI (f, LastReadState, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyFirstReadTermState             = ");
        WriteI (f, FirstReadTermState, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyLastReadTermState              = ");
        WriteI (f, LastReadTermState, 0); WriteC (f, ';'); WriteNl(f);
(*      WriteT (f, "   yyFirstReadNontermState          = ");
        WriteI (f, FirstReadNonTermState, 0); WriteC (f, ';'); WriteNl(f);      *)
        WriteT (f, "   yyLastReadNontermState           = ");
        WriteI (f, LastReadNonTermState, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyFirstReduceState               = ");
        WriteI (f, FirstReduceState, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyLastReduceState                = ");
        WriteI (f, LastReduceState, 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyStartState             = ");
        WriteI (f, StartState(), 0); WriteC (f, ';'); WriteNl(f);
        WriteT (f, "   yyStopState              = ");
        WriteI (f, StopState, 0); WriteC (f, ';'); WriteNl(f);
      ELSE (* Language = C *)
        WriteT (f, "# define yyFirstTerminal    ");
        WriteI (f, FirstTerminal, 0); WriteNl(f);
        WriteT (f, "# define yyLastTerminal             ");
        WriteI (f, LastTerminal, 0); WriteNl(f);
(*      WriteT (f, '# define yyFirstSymbol      ');
        WriteI (f, FirstSymbol, 0); WriteNl(f);
        WriteT (f, '# define yyLastSymbol       ');
        WriteI (f, LastSymbol, 0); WriteNl(f);          *)
        WriteT (f, "# define yyTableMax         ");
        WriteI (f, TableSize, 0); WriteNl(f);
        WriteT (f, "# define yyNTableMax                ");
        WriteI (f, NTableSize, 0); WriteNl(f);
        WriteT (f, "# define yyFirstReadState   ");
        WriteI (f, FirstReadState, 0); WriteNl(f);
        WriteT (f, "# define yyLastReadState    ");
        WriteI (f, LastReadState, 0); WriteNl(f);
        WriteT (f, "# define yyFirstReadTermState       ");
        WriteI (f, FirstReadTermState, 0); WriteNl(f);
        WriteT (f, "# define yyLastReadTermState        ");
        WriteI (f, LastReadTermState, 0); WriteNl(f);
(*      WriteT (f, '# define yyFirstReadNontermState    ');
        WriteI (f, FirstReadNonTermState, 0); WriteNl(f);       *)
        WriteT (f, "# define yyLastReadNontermState     ");
        WriteI (f, LastReadNonTermState, 0); WriteNl(f);
        WriteT (f, "# define yyFirstReduceState ");
        WriteI (f, FirstReduceState, 0); WriteNl(f);
        WriteT (f, "# define yyLastReduceState  ");
        WriteI (f, LastReduceState, 0); WriteNl(f);
        WriteT (f, "# define yyStartState               ");
        WriteI (f, StartState(), 0); WriteNl(f);
        WriteT (f, "# define yyStopState                ");
        WriteI (f, StopState, 0); WriteNl(f);
      END;
    END WriteConstants;

  PROCEDURE WriteReduceCode (f:tFile) = (* Ausgabe des Codes fuer die Reduktionen *)
    VAR
      label: tStateIndex;
      labels: INTEGER;
      cases: INTEGER;
      index: tProdIndex;
      prod: tProduction;
      maxProdIndex: tProdIndex;
      u: M2LONGINT;
    BEGIN
      label := FirstReduceState;
      labels := 0;
      cases := 1;
      index := 0;

      IF CaseLabels > 0 THEN
        INC (label, CaseLabels);
        OpenCase (f, label);
      ELSIF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WriteT  (f, "CASE yyState OF");
        WriteNl (f);
      ELSE (* Language = C *)
        WriteT  (f, "switch (yyState) {");
        WriteNl (f);
      END;

      maxProdIndex := ProdIndex;
      WHILE index < maxProdIndex DO

        IF CaseLabels > 0 THEN
          IF labels >= CaseLabels THEN
            INC (label, CaseLabels);
            NextCase (f, label);
            INC (cases);
            labels := 0;
          END;
          INC (labels);
        END;

        prod := ADR (ProdArrayPtr^[index]);

        (* States ausgeben *)

        WITH m2tom3_with_1=prod^.Reduce DO
          IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
            WriteT (f, "  | ");
            WriteI (f, m2tom3_with_1.Array^[1], 0);
          ELSE (* Language = C *)
            WriteT (f, "case ");
            WriteI (f, m2tom3_with_1.Array^[1], 0);
            WriteC (f, ':');
          END;
          IF NOT CaseFlag THEN
            FOR u := 2 TO m2tom3_with_1.Used DO
              IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
                WriteC (f, ',');
                WriteI (f, m2tom3_with_1.Array^[u], 0);
              ELSE (* Language = C *)
                WriteNl (f);
                WriteT (f, "case ");
                WriteI (f, m2tom3_with_1.Array^[u], 0);
                WriteC (f, ':');
              END;
            END;
          END;
          IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN WriteC (f, ':'); END;
          
          WriteProdComment (f, prod);

          IF index = 0 THEN   (* Endzustand *)
            IF Language = tLanguage.Modula3 THEN
              WriteT (f, "  yyStateStack := NIL;");
              WriteNl (f);
              WriteT (f, "  yyAttributeStack := NIL;");
              WriteNl (f);
              WriteT (f, "  RETURN yyErrorCount;");
              WriteNl (f);
            ELSIF Language = tLanguage.Modula2 THEN
              WriteT (f, "  DynArray.ReleaseArray (yyStateStack, yyStateStackSize, BYTESIZE (yyTableElmt));");
              WriteNl (f);
              WriteT (f, "  DynArray.ReleaseArray (yyAttributeStack, yyAttrStackSize, BYTESIZE (tParsAttribute));");
              WriteNl (f);
              WriteT (f, "  RETURN yyErrorCount;");
              WriteNl (f);
            ELSE (* Language = C *)
              WriteT (f, "  ReleaseArray ((char * *) & yyStateStack, & yyStateStackSize, sizeof (yyStateRange));");
              WriteNl (f);
              WriteT (f, "  ReleaseArray ((char * *) & yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute));");
              WriteNl (f);
              WriteT (f, "  return yyErrorCount;");
              WriteNl (f);
            END;
          ELSE
            IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
              IF prod^.Len # 0 
              THEN 
                WriteT (f, "  DEC (yyStackPtr, ");
                WriteI (f, prod^.Len, 0);
                WriteT (f, "); ");
              END (* IF *) ;  
              WriteT (f, "yyNonterminal := ");
              WriteI (f, prod^.Left-NonTermOffset, 0);
              WriteC (f, ';');
              WriteNl (f);
            ELSE (* Language = C *)
              IF prod^.Len # 0
              THEN  
                WriteT (f, "  yyStateStackPtr -=");
                WriteI (f, prod^.Len, 0);
                WriteT (f, "; yyAttrStackPtr -=");
                WriteI (f, prod^.Len, 0);
                WriteC (f, ';');
              END (* IF *) ; 
              WriteT (f, "  yyNonterminal = ");
              WriteI (f, prod^.Left-NonTermOffset, 0);
              WriteT (f, "; {");
              WriteNl (f);
            END;
          END;

          m2tom3_with_1.Array := NIL;
(*WAS     ReleaseArray (m2tom3_with_1.Array, m2tom3_with_1.Count, BYTESIZE (tIndex));*)
        END;

        (* semantische Aktion ausgeben *)

        WriteSemanticAction (f, prod^.Act, prod^.Len, prod^.ActPos);
        IF (index # 0) AND (Language = tLanguage.C) THEN
          WriteT (f, "} break;"); WriteNl (f);
        END;
        index := NextProdIndex(index);
      END;

      IF CaseLabels > 0 THEN
        CloseCase (f, cases);
      ELSIF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WriteT  (f, "END;");
        WriteNl (f);
      ELSE (* Language = C *)
        WriteC  (f, '}');
        WriteNl (f);
      END;
    END WriteReduceCode;
  
  PROCEDURE OpenCase (f: tFile; label: tStateIndex) =
    BEGIN
      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WriteT  (f, "CASE yyState OF");
        WriteNl (f);
      ELSE (* Language = C *)
        IF label <= LastReduceState THEN
          WriteT  (f, "if (yyState < ");
          WriteI  (f, label, 0);
          WriteT  (f, ") ");
        END;
        WriteT  (f, "switch (yyState) {");
        WriteNl (f);
      END;
    END OpenCase;

  PROCEDURE NextCase (f: tFile; label: tStateIndex) =
    BEGIN
      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WriteT  (f, "ELSE CASE yyState OF");
        WriteNl (f);
      ELSE (* Language = C *)
        WriteT  (f, "} else ");
        IF label <= LastReduceState THEN
          WriteT  (f, "if (yyState < ");
          WriteI  (f, label, 0);
          WriteT  (f, ") ");
        END;
        WriteT  (f, "switch (yyState) {");
        WriteNl (f);
      END;
    END NextCase;

  PROCEDURE CloseCase (f: tFile; cases: INTEGER) =
    BEGIN
      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WHILE cases > 0 DO
          WriteT  (f, "END; (* additional CASE *)");
          WriteNl (f);
          DEC (cases);
        END;
      ELSE (* Language = C *)
          WriteC  (f, '}');
          WriteNl (f);
      END;
    END CloseCase;

  PROCEDURE WriteSemanticAction (f: tFile; a: tList; len: Word.T; pos: PosType) =
    VAR
      c: CHAR;
      s: tString;
      i: tStringIndex;
      i1, i2: tStringIndex;
      AttrIndex: Word.T;
      negative: BOOLEAN;
      Delimiter : CHAR;
    BEGIN
      IF pos.Line # 0 THEN
        IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
          WriteT (f, "(* line ");
          WriteI (f, pos.Line, 0);
          WriteT (f, " of \"");
          WriteT (f, SourceFileName);
          WriteT (f, "\" *)");
          WriteNl (f);
        ELSE (* Language = C *)
          IF LineFlag THEN
             WriteT (f, "# line ");
             WriteI (f, pos.Line, 0);
             WriteT (f, " of \"");
             WriteT (f, SourceFileName);
             WriteC (f, '"');
             WriteNl (f);
          ELSE
             WriteT (f, "/* line ");
             WriteI (f, pos.Line, 0);
             WriteT (f, " of \"");
             WriteT (f, SourceFileName);
             WriteT (f, "\" */");
             WriteNl (f);
          END;
        END;
      END;
      (* gib die semantische Aktion zeilenweise aus *)
      i1 := 2;
      WHILE NOT IsEmpty (a) DO
        StringMem.GetString (tStringRef (Head (a)), s);
        i2 := Length (s);
        Tail (a);
        IF IsEmpty (a) THEN DEC (i2); END;
        IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN WriteT (f, "  "); END;
        i := i1;
        WHILE i <= i2 DO
          c := Char (s, i); INC (i);
          IF c = '\\' THEN
            WriteC (f, Char (s, i)); INC (i);
          ELSIF (c = '\"') OR (c = '\'') THEN
            Delimiter := c;
            WriteC (f, c);
            REPEAT
              c := Char (s, i); INC (i);
              WriteC (f, c);
              IF (Language = tLanguage.C) AND (c = '\\') THEN
                WriteC (f, Char (s, i)); INC (i);
              END;
            UNTIL c = Delimiter;
          ELSIF c = '$' THEN                            (* evtl. Attribute *)
            IF (i <= i2) AND (Char (s, i) = '$') THEN
              WriteT (f, "yySynAttribute");
              INC (i);
            ELSE
              AttrIndex := 0;
              IF (i <= i2) AND (Char (s, i) = '-') THEN
                negative := TRUE;
                INC (i);
              ELSE
                negative := FALSE;
              END;
              WHILE (i <= i2) AND (Char (s, i) >= '0') AND (Char (s, i) <= '9') DO
                AttrIndex := (AttrIndex * 10) + (ORD (Char (s, i)) - ORD('0'));
                INC (i);
              END;
              IF negative OR (AttrIndex <= len) THEN
                IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
                  WriteT (f, "yyAttributeStack^[yyStackPtr");
                  IF negative THEN WriteC (f, '-'); ELSE WriteC (f, '+'); END;
                  WriteI (f, AttrIndex, 0);
                  WriteC (f, ']');
                ELSE (* Language = C *)
                  WriteT (f, "yyAttrStackPtr [");
                  IF negative THEN WriteC (f, '-'); END;
                  WriteI (f, AttrIndex, 0);
                  WriteT (f, "-1]");
                END;
              ELSE    (* Index unbrauchbar -> Kopie in Ausgabe *)
                WriteC (f, c);
              END;
            END;
          ELSE
            WriteC (f, c);
          END;
        END;
        i1 := 1;
      END;
      WriteNl (f);
    END WriteSemanticAction;

  PROCEDURE WriteProdComment (f: tFile; prod: tProduction) =
    VAR i: tIndex;
    BEGIN
      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WriteT (f, " (* ");
      ELSE (* Language = C *)
        WriteT (f, " /* ");
      END;

      WITH m2tom3_with_2=prod^ DO
        WriteToken (f, m2tom3_with_2.Left);
        WriteT (f, ": ");
        FOR i := 1 TO m2tom3_with_2.Len DO
          WriteToken (f, m2tom3_with_2.Right[i]);
        END;
        WriteC (f, '.');
      END;

      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        WriteT (f, "*)");
        WriteNl (f);
      ELSE (* Language = C *)
        WriteT (f, "*/");
        WriteNl (f);
      END;
    END WriteProdComment;

  PROCEDURE WriteToken (f: tFile; t: Vocabulary) =
    VAR
     s: tString;
     sym: tIdent;
     error: TokenError;
     i: Word.T;
    BEGIN
      sym := TokenToSymbol (t, error);
      GetString (sym, s);
      WriteC (f, Char (s, 1));
      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
        FOR i := 2 TO Length (s) DO
          IF Char (s, i) = ')' THEN
            IF Char (s, i-1) = '*' THEN
              WriteC (f, ' ');
            END;
          ELSIF Char (s, i) = '*' THEN
            IF Char (s, i-1) = '(' THEN
              WriteC (f, ' ');
            END;
          END;
          WriteC (f, Char (s, i));
        END;
      ELSE (* Language = C *)
        FOR i := 2 TO Length (s) DO
          IF Char (s, i) = '/' THEN
            IF Char (s, i-1) = '*' THEN
              WriteC (f, ' ');
            END;
          ELSIF Char (s, i) = '*' THEN
            IF Char (s, i-1) = '/' THEN
              WriteC (f, ' ');
            END;
          END;
          WriteC (f, Char (s, i));
        END;
      END;
      WriteC (f, ' ');
    END WriteToken;

  PROCEDURE WriteLong (f:tFile; Check:M2LONGINT) =
    VAR
      i, j: M2LONGINT;
      d: Word.T;
    BEGIN
      IF Check < 0 THEN
        WriteC (f, '-');
        Check := - Check;
      END;
      i := 1;
      WHILE i <= (Check DIV 10) DO
        i := i * 10;
      END;
      WHILE i > 0 DO
        d := Check DIV i;
        WriteC (f, VAL(ORD('0')+d,CHAR));
        j := d;
        DEC (Check, j * i);
        i := i DIV 10;
      END;
    END WriteLong;
  BEGIN
END GenLang.

