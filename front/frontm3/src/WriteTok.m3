(* generate output procedure for tokens *)

(* Rodney M. Bates, modifications: 
    3-2023 Add generation of Module-3 code. 
    Further changes in https://github.com/RodneyBates/cocktail
*) 

(* $Id: WriteTok.mi,v 2.1 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: WriteTok.mi,v $
 * Revision 2.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:26:45  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.3  91/01/18  17:46:25  grosch
 * calmed down lint
 * 
 * Revision 1.2  90/06/11  18:45:52  grosch
 * layout improvements
 * 
 * Revision 1.1  89/01/12  17:45:56  vielsack
 * supply source file name
 * 
 * Revision 1.0  88/10/04  14:27:30  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE WriteTok;

FROM ReuseIO         IMPORT WriteC, WriteI, WriteNl, WriteS, WriteT, tFile;
IMPORT Word, Strings;
FROM Strings    IMPORT Length, Char, SubString, tString;
FROM Idents     IMPORT GetString, tIdent, WriteIdent;
FROM TokenTab   IMPORT MAXTerm, MINTerm, Terminal, TokenError, GetTokenType,
                        TokenType, TokenToSymbol;

  PROCEDURE GenWrTo (f : tFile) =
    VAR
      t         : Terminal;
      sym       : tIdent;
      s,s2      : tString;
      error     : TokenError;
      l         : Word.T;
      del       : CHAR;
    BEGIN
      FOR t := MINTerm TO MAXTerm DO
        IF GetTokenType (t) = TokenType.Term THEN
          sym := TokenToSymbol (t, error);
          GetString (sym, s);
          IF Language = tLanguage.Modula3 THEN
            WriteT (f, "      | ");
            WriteI (f, t, 0);
            WriteT (f, " => Name := ");
            del := Char (s, 1);
            IF del = '\'' THEN
              WriteC (f, '"');
              SubString (s, 2 , Length(s)-1, s2);
              Strings.WriteS (f, s2);
              WriteC (f, '"');
            ELSIF del = '"' THEN
              WriteIdent (f, sym);
            ELSE
              WriteC (f, '"');
              WriteIdent (f, sym);
              WriteC (f, '"');
            END;
            WriteC (f, ';');
            WriteNl (f);
          ELSIF Language = tLanguage.Modula2 THEN
            WriteT (f, "      | ");
            WriteI (f, t, 0);
            WriteT (f, ": Copy (");
            del := Char (s, 1);
            IF (del = '"') OR (del = '\'') THEN
              WriteIdent (f, sym);
            ELSE
              WriteC (f, '"');
              WriteIdent (f, sym);
              WriteC (f, '"');
            END;
            WriteT (f, ", Name);");
            WriteNl (f);
          ELSE (* Language = C *)
            WriteC (f, '"');
            IF (Char (s, 1) = '"') OR (Char (s, 1) = '\'') THEN
              FOR l := 2 TO Length (s) - 1 DO
                IF (Char (s, l) = '\\') OR (Char (s, l) = '"') THEN WriteC (f, '\\'); END;
                WriteC (f, Char (s, l));
              END;
            ELSE
              FOR l := 1 TO Length (s) DO
                IF (Char (s, l) = '\\') OR (Char (s, l) = '"') THEN WriteC (f, '\\'); END;
                WriteC (f, Char (s, l));
              END;
            END;
            WriteT (f, "\",");
            WriteNl (f);
          END;
        ELSIF Language = tLanguage.C THEN
          WriteT (f, "0,");
          WriteNl (f);
        END;
      END;
    END GenWrTo;

BEGIN
  Language := tLanguage.Modula2;
END WriteTok.

