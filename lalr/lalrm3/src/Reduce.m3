(* check if the grammar is reduced *)

(* $Id: Reduce.mi,v 2.2 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Reduce.mi,v $
 * Revision 2.2  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:31:50  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/12  16:54:34  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0  88/10/04  14:36:38  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE Reduce;

  IMPORT IntSets;

  IMPORT Word;
  FROM FrontErrors IMPORT
    eWarning, eError, eIdent, ErrorMessage, ErrorMessageI;

  FROM Sets IMPORT
    tSet,
    MakeSet, ReleaseSet,
    Include, Exclude,
    Extract, 
    IsElement, IsEmpty,
    ForallDo;

  FROM Automaton IMPORT
    tIndex,
    tStateIndex,
    tProdIndex,
    tItemIndex,
    StartSymbol,
    tProduction,
    ProdList,
    ProdArrayPtr;

  FROM TokenTab IMPORT 
    MINTerm, MAXTerm,
    MINNonTerm, MAXNonTerm,
    Vocabulary,
    Terminal, NonTerminal,
    PosType, GetTokenPos,
    TokenError, TokenType,
    GetTokenType, TokenToSymbol;
  
  FROM Idents IMPORT
    tIdent;

  CONST
    eNotReach   = 47;
    eNoProd     = 46;
    eNotTerm    = 45;

  PROCEDURE TestReduced() =

  (* prueft ob die im Modul Automaton bekannte Grammatik
     reduziert ist. Falls nein wird das Programm mittels einer
     Fehlermeldung abgebrochen *)
  
    VAR
      ok, okreach, okterm : BOOLEAN;
      reached  : IntSets.T;           (* erreichbare Symbole  *)

    BEGIN
      reached := IntSets.Empty();
      okreach := TestReach (reached);
      okterm := TestTerm (reached);
      ok := (* okreach AND *) okterm;    (* kein genereller Abbruch *)

      Reduced := ok;
      reached := NIL;
    END TestReduced;

  PROCEDURE TestReach (reached: IntSets.T) : BOOLEAN =

  (* Pruefe ob alle Vokabularzeichen erreichbar sind *)
    
    VAR
      reach    : BOOLEAN;        (* Funktionsergebniss *)
      t        : Terminal;
      nt       : NonTerminal;
      todo     : IntSets.T;           (* noch zu bearbeiten *)
      done     : IntSets.T;           (* bereits bearbeitet *)
      u, i     : tIndex;
      pn       : tProdIndex;
      prodADR : (*tProduction*) ADDRESS;
      prod     : tProduction;
      ri,voc   : Vocabulary;
      error    : TokenError;
      sym      : tIdent;        (* zur Fehlerausgabe  *)
      pos      : PosType;


    BEGIN
      todo := IntSets.Empty();
      done := IntSets.Empty();

      (* Startsymbol ist zu bearbeiten *)

      todo := IntSets.Include (todo,StartSymbol);
      reached := IntSets.Include (reached,StartSymbol);

      (* Terminale sind nicht mehr zu bearbeiten *)

      FOR t := MINTerm TO MAXTerm DO
        IF GetTokenType (t) = TokenType.Term THEN
          done := IntSets.Include (done,t);
        END;
      END;

      REPEAT

        (* waehle ein Nichtterminal zur Bearbeitung aus *)

        nt := IntSets.Extract ((*VAR*)todo);
        done := IntSets.Include (done, nt);

        WITH m2tom3_with_1=ProdList[nt] DO
          u := m2tom3_with_1.Used;

          (* fuer alle Produktionen mit linker Seite nt *)

          FOR pn := 1 TO u DO

            (* waehle aktuelle Produktion aus *)

            prodADR := ADR(ProdArrayPtr^[m2tom3_with_1.Array^[pn].Index]);
            prod := LOOPHOLE (prodADR, tProduction);
            WITH m2tom3_with_2=prod^ DO

              (* alle Vocabularzeichen auf der rechten Seite werden *)
              (* hiermit erreichbar *)

              FOR i := 1 TO m2tom3_with_2.Len DO
                ri := m2tom3_with_2.Right [i];
                reached := IntSets.Include (reached, ri);

                (* noch nicht erledigte Vokabularzeichen die rechts *)
                (* auftreten sind zu bearbeiten *)

                IF NOT IntSets.IsElement (ri, done) THEN
                  todo := IntSets.Include (todo, ri);
                END;
              END;
            END;
          END;
        END;
      UNTIL IntSets.IsEmpty (todo);

      reach := TRUE;

      (* pruefe ob alle Vocabularzeichen erreichbar sind *)
      (* gebe ggf. eine Fehlermeldung aus *)

      FOR voc := MINTerm TO MAXTerm DO
        IF (GetTokenType (voc) # TokenType.None) AND
           (NOT IntSets.IsElement (voc, reached)) THEN
          GetTokenPos   (voc,pos);
          sym := TokenToSymbol (voc,error);
          ErrorMessageI (eNotReach, eWarning, pos,eIdent, ADR (sym));
        END;
      END;

      FOR voc := MINNonTerm TO MAXNonTerm DO
        IF (GetTokenType (voc) # TokenType.None) AND
           (NOT IntSets.IsElement (voc, reached)) THEN
          GetTokenPos   (voc,pos);
          sym := TokenToSymbol (voc,error);
          ErrorMessageI (eNotReach, eWarning, pos, eIdent, ADR (sym));

          (* nichtereichbare Nichtterminal sind toetlich *)
          reach := FALSE;

        END;
      END;

      todo := NIL;
      done := NIL;

      RETURN reach;
    END TestReach;


  PROCEDURE TestTerm (reached: IntSets.T) : BOOLEAN =

  (* Pruefe ob alle Nichtterminale terminalisierbar sind *)

    VAR
      todo : IntSets.T;    (* noch zu ueberpruefende Nichterminale *)
      done : IntSets.T;    (* als terminalisierbar erkannte Vokabularzeichen *)
      success : BOOLEAN; (* hatte der letzte Schritt erfolg *)
      t : Terminal;
      nt : NonTerminal;
      term : BOOLEAN;
      error : TokenError;
      sym : tIdent;
      pos : PosType;
      kind : Word.T;

    PROCEDURE IsYetTerm (nt : Word.T) =

      VAR
        u, i : tIndex;
        pn   : tProdIndex;
        prodADR : (*tProduction*) ADDRESS;
        prod : tProduction;
        ri   : Vocabulary;
        t : Terminal;
        localsuccess : BOOLEAN;

      BEGIN 
        WITH m2tom3_with_4=ProdList[nt] DO
          u := m2tom3_with_4.Used;

          (* Betrachte alle Produktionen mit linker Seite nt *)

          localsuccess := FALSE;
          pn := 1;
          WHILE (pn <= u) AND (NOT localsuccess) DO

            (* Auswahl der einzelnen Produktion *)

            prodADR := ADR(ProdArrayPtr^[m2tom3_with_4.Array^[pn].Index]);
            prod := LOOPHOLE (prodADR, tProduction);
            WITH m2tom3_with_5=prod^ DO

              (* Pruefe ob rechte Seite in todo* liegt *)

              localsuccess := TRUE;
              i := 1;
              WHILE (i <= m2tom3_with_5.Len) AND localsuccess DO
                ri := m2tom3_with_5.Right [i];
                localsuccess := IntSets.IsElement (ri,done);
                INC (i);
              END;

            END;

            INC (pn);
          END;
        END;

        IF localsuccess THEN
          done := IntSets.Include (done, nt);
          todo := IntSets.Exclude (todo, nt);
          success := TRUE
        END;

      END IsYetTerm;

    BEGIN
      todo := IntSets.Empty();
      done := IntSets.Empty();

      (* todo = Menge aller Nichtterminale *)

      FOR nt := MINNonTerm TO MAXNonTerm DO
        IF GetTokenType (nt) = TokenType.NonTerm THEN
          todo := IntSets.Include (todo,nt);
        END;
      END;

      (* done := Menge alle Terminale *)

      FOR t := MINTerm TO MAXTerm DO
        IF GetTokenType (t) = TokenType.Term THEN
          done := IntSets.Include (done,t);
        END;
      END;

      REPEAT

        success := FALSE;

        (* Pruefe ob jetzt ein weiteres *)
        (* Nichtterminal terminalisierbar ist *)

        FOR nt := MINNonTerm TO MAXNonTerm DO
          IF IntSets.IsElement (nt, todo) THEN
            IsYetTerm (nt);
          END;
        END;
      UNTIL NOT success;    (* solange bis sich nichts aendert *)

      term := TRUE;
      IF NOT IntSets.IsEmpty (todo) THEN
        REPEAT 
          nt := IntSets.Extract (todo);

          (* Ein ereichbares Nichtterminal, das nicht terminalisiserbar
             ist, fuehrt zum Abbruch *)
          IF IntSets.IsElement (nt, reached) THEN
            term := FALSE;
            kind := eError;
          ELSE
            kind := eWarning;
          END;
          GetTokenPos   (nt,pos);
          sym := TokenToSymbol (nt,error);
          IF ProdList[nt].Used = 0 THEN
            ErrorMessageI (eNoProd, kind, pos, eIdent, ADR (sym));
          ELSE
            ErrorMessageI (eNotTerm, kind, pos, eIdent, ADR (sym));
          END;
        UNTIL IntSets.IsEmpty (todo);
      END;

      todo := NIL;
      done := NIL;

      RETURN term;
    END TestTerm;

BEGIN
END Reduce.

