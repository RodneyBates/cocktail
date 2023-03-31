
(* 2001-02-15, Rodney M. Bates. 
   1) changes to open _Debug file properly. Apparently this
      was bitrot for a string literal not getting a null byte
      following, when compiled using m2c. I thought I had fixed 
      something like this earlier. 
   2) changes to support printing item sets.
*) 

(* check and repair inconsitences *)

(* $Id: Check.mi,v 2.4 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Check.mi,v $
 * Revision 2.4  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.3  1992/02/05  08:00:15  grosch
 * renamed NULL to DevNull
 *
 * Revision 2.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.1  91/03/19  14:19:23  grosch
 * fixed: IF Verbose THEN WriteClose (dFile); END;
 * 
 * Revision 2.0  91/03/08  18:31:37  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.5  91/01/18  20:32:43  grosch
 * fixed resolution of reduce-reduce conflicts
 * 
 * Revision 1.4  90/06/12  16:53:43  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.3  89/05/02  14:34:18  vielsack
 * new option: -v (verbose)
 * 
 * Revision 1.2  89/01/02  16:17:34  vielsack
 * fixed bug (instead of a reduce reduce conflict a read reduce conflict
 * was reported)
 * 
 * Revision 1.1  88/11/08  12:09:28  vielsack
 * report all read items in the conclusion (not only the representative)
 * 
 * Revision 1.0  88/10/04  14:35:55  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

 UNSAFE MODULE Check;

IMPORT Word, ArgCheck , Idents ;

FROM Automaton  IMPORT Infinite, tAss, tRep, tIndex, tProduction, ProdArrayPtr,
                        tStateIndex, StateArrayPtr, StateIndex, tItemIndex,
                        ItemArrayPtr, OperArray;
FROM Debug      IMPORT dFile, tConflict, DebugHead, DebugState, DebugEnd, InformIgnored,
                        InformLowPri, InformRightAss, InformLeftAss, InformKept,
                        InformConflict, NewLine;
FROM Debug      IMPORT ItemSets, PrintItemSets;
FROM FrontErrors     IMPORT eInternal, eInformation, eWarning, eError, eFatal, eString,
                        eShort, eTermSet, ErrorMessageI;
FROM Idents     IMPORT tIdent;
FROM ReuseIO         IMPORT WriteOpen, WriteClose;
FROM Sets       IMPORT tSet, IsElement, IsEmpty, Include, Exclude, Extract, Union,
                        Intersection, Assign,  AssignEmpty, MakeSet, ReleaseSet;
IMPORT IntSets;
FROM Strings    IMPORT tString, TextToString;
FROM SysError   IMPORT StatIsBad, SysErrorMessageI;

FROM Positions  IMPORT NoPosition;
FROM TokenTab   IMPORT MAXTerm, Terminal, Prio, TokenToSymbol, TokenError;

  CONST
    eState              = 70;
    eReadRed            = 71;
    eRedRed             = 72;
    eReadRedRed         = 73;
    eRepReadRed         = 74;
    eRepRedRed          = 75;
    eRepReadRedRed      = 76;
    eARepReadRed        = 77;
    eARepRedRed         = 78;
    eARepReadRedRed     = 79;

    DevNull     = "/dev/null";
    DEBUG       = "_Debug";

  VAR FileName : ARRAY [ 0 .. 128 ] OF CHAR ; 

  PROCEDURE CheckForConflicts (VAR ok: BOOLEAN) =

  (* Pruefe ob die Zustaende Konflikte beinhalten,
     so weit moeglich werden Konflikte mit Hilfe von
     Prioritaeten und Assoziativitaeten geloest,
     falls keine Korektur moeglich ist wird das Programm mit 
     einer Fehlermeldung beendet, sonst steht ein konfliktfreier
     Automat zur Auswertung zur Verfuegung *)

    VAR
      SymbolSet,
      ConflictSet,
      TempSet  : IntSets.T;
      state, 
      maxState : tStateIndex;
      item     : tItemIndex;
      Error    : BOOLEAN;
      string   : tString;
    BEGIN
      Error := FALSE;
      MakeSet (SymbolSet,MAXTerm);
      MakeSet (ConflictSet,MAXTerm);
      MakeSet (TempSet,MAXTerm);

      IF Verbose THEN
        ArgCheck . MakeFileName 
          ( Idents . NoIdent , "_Debug" , "" , FileName ) ;
        dFile := WriteOpen (FileName);  
        (* dFile := WriteOpen (DEBUG); *) 
        IF StatIsBad (dFile) THEN
          TextToString (DEBUG, string);
          SysErrorMessageI (dFile, eError, eString, ADR (string));
          ArgCheck . MakeFileName 
            ( Idents . NoIdent , "/dev/null" , "" , FileName ) ;
          dFile := WriteOpen (FileName);
          IF StatIsBad (dFile) THEN
            TextToString (DevNull, string);
            SysErrorMessageI (dFile, eFatal, eString, ADR (string));
          END;
        END;
      END;

      (* fuer Debug wird in Number ein Verweis auf den zugeh. State eingetragen *)

      maxState := StateIndex;
      FOR state := 1 TO maxState DO
        WITH m2tom3_with_1=StateArrayPtr^[state] DO
          FOR item := m2tom3_with_1.Items TO m2tom3_with_1.Items + m2tom3_with_1.Size - 1 DO
            WITH m2tom3_with_2=ItemArrayPtr^[item] DO
              m2tom3_with_2.Number := state;
            END;
          END;
        END;
      END;

      FOR state := 1 TO maxState DO
        WITH m2tom3_with_4=StateArrayPtr^[state] DO

          AssignEmpty (ConflictSet);
          AssignEmpty (SymbolSet);

          FOR item := m2tom3_with_4.Items TO m2tom3_with_4.Items + m2tom3_with_4.Size - 1 DO
            WITH m2tom3_with_5=ItemArrayPtr^[item] DO
              CASE m2tom3_with_5.Rep OF
              | tRep.TermRep =>
                  IF IntSets.IsElement (m2tom3_with_5.Read,SymbolSet) THEN
                    ConflictSet := IntSets.Include (ConflictSet,m2tom3_with_5.Read);
                  ELSE
                    SymbolSet  := IntSets.Include (SymbolSet,m2tom3_with_5.Read);
                  END;
              | tRep.RedRep =>
                  Assign (TempSet,m2tom3_with_5.Set);
                  Intersection (TempSet,SymbolSet);
                  ConflictSet := IntSets.Union (ConflictSet,TempSet);
                  SymbolSet := IntSets.Union (SymbolSet,m2tom3_with_5.Set);
              ELSE
              END;
            END;
          END;

          IF NOT IntSets.IsEmpty (ConflictSet) THEN
            RepairConflict (state, ConflictSet);
            IF NOT IntSets.IsEmpty (ConflictSet) THEN Error := TRUE; END;
          END;
        END;
      END;

      ReleaseSet (TempSet);
      ReleaseSet (ConflictSet);
      ReleaseSet (SymbolSet);
      IF ItemSets THEN PrintItemSets ( ) END ; 
      ok := NOT Error;
      IF Verbose THEN
        WriteClose (dFile);
      END;
    END CheckForConflicts;

PROCEDURE RepairConflict (state: tStateIndex; VAR ConflictSet: IntSets.T) =
    VAR
      todo                                              : IntSets.T;
      LookAhead                                         : Terminal;
      ReadRedSet, RedRedSet, ReadRedRedSet, RepReadRedSet,
      RepRedRedSet, RepReadRedRedSet, ARepReadRedSet,
      ARepRedRedSet, ARepReadRedRedSet                  : IntSets.T;
      Priority, ReducePri, ShiftPri                     : Prio;
      Associativity, ReduceAss, ShiftAss                : tAss;
      MinProdNo                                         : tIndex;
      OnlyOpers                                         : BOOLEAN;
      ReduceCount, ShiftCount, ReduceRest, ShiftRest    : Word.T;
      item                                              : tItemIndex;
      prod                                              : tProduction;
      ConflictFree                                      : BOOLEAN;
    BEGIN
      MakeSet (ReadRedSet, MAXTerm);
      MakeSet (RedRedSet, MAXTerm);
      MakeSet (ReadRedRedSet, MAXTerm);
      MakeSet (RepReadRedSet, MAXTerm);
      MakeSet (RepRedRedSet, MAXTerm);
      MakeSet (RepReadRedRedSet, MAXTerm);
      MakeSet (ARepReadRedSet, MAXTerm);
      MakeSet (ARepRedRedSet, MAXTerm);
      MakeSet (ARepReadRedRedSet, MAXTerm);

      IF Verbose THEN
        DebugHead (state);
        DebugState (state, ConflictSet);
      END;

      MakeSet (todo, MAXTerm);
      Assign (todo, ConflictSet);

      WITH m2tom3_with_7=StateArrayPtr^[state] DO
        WHILE NOT IntSets.IsEmpty (todo) DO
          LookAhead := IntSets.ExtractArbitraryMember ((*VAR*)7odo);

          OnlyOpers := TRUE;
          ReduceCount := 0;
          ShiftCount := 0;
          ReduceRest := 0;
          ShiftRest := 0;
          ReducePri := 0;
          ReduceAss := tAss.none;
          ShiftPri  := 0;
          ShiftAss  := tAss.none;
          MinProdNo := 10000;

          FOR item := m2tom3_with_7.Items TO m2tom3_with_7.Items + m2tom3_with_7.Size - 1 DO
            WITH m2tom3_with_8=ItemArrayPtr^[item] DO
              IF (m2tom3_with_8.Rep = tRep.RedRep) AND IntSets.IsElement (LookAhead, m2tom3_with_8.Set) THEN
                INC (ReduceCount);
                prod := ADR(ProdArrayPtr^[m2tom3_with_8.Prod]);
                IF prod^.Pri = 0 THEN
                  OnlyOpers := FALSE;
                ELSIF prod^.Pri > ReducePri THEN
                  ReducePri := prod^.Pri;
                  ReduceAss := prod^.Ass;
                END;
                IF prod^.ProdNo < MinProdNo THEN
                  MinProdNo := prod^.ProdNo;
                END;
              ELSIF (m2tom3_with_8.Rep = tRep.TermRep) AND (m2tom3_with_8.Read = LookAhead) THEN
                INC (ShiftCount);
                IF OperArray [LookAhead].Pri = 0 THEN
                  OnlyOpers := FALSE;
                ELSE
                  ShiftPri := OperArray [LookAhead].Pri;
                  ShiftAss := OperArray [LookAhead].Ass;
                END;
              END;
            END;
          END;

          IF OnlyOpers THEN

            IF ReducePri > ShiftPri THEN
              Priority          := ReducePri;
              Associativity     := ReduceAss;
            ELSE
              Priority          := ShiftPri;
              Associativity     := ShiftAss;
            END;
            
            FOR item := m2tom3_with_7.Items TO m2tom3_with_7.Items + m2tom3_with_7.Size - 1 DO
              WITH m2tom3_with_9=ItemArrayPtr^[item] DO
                IF (m2tom3_with_9.Rep = tRep.RedRep) AND IntSets.IsElement (LookAhead, m2tom3_with_9.Set) THEN
                  prod := ADR (ProdArrayPtr^[m2tom3_with_9.Prod]);
                  IF (prod^.Pri < Priority) THEN        (* lower priority       *)
                    IF Verbose THEN
                      InformLowPri (item, LookAhead);   (* ignore reduce        *)
                    END;
                    m2tom3_with_9.Set := IntSets.Exclude (m2tom3_with_9.Set, LookAhead);
                    IF IntSets.IsEmpty (m2tom3_with_9.Set) THEN m2tom3_with_9.Rep := tRep.NoRep; END;
                  ELSIF (prod^.Pri = Priority) AND      (* max. priority        *)
                     ((Associativity = tAss.right) OR   (* right associative    *)
                     (Associativity = tAss.nonassoc)) AND       (* not associative      *)
                     (ShiftPri = Priority) THEN         (* same priority        *)
                    IF Verbose THEN
                      InformRightAss (item, LookAhead); (* ignore reduce        *)
                    END;
                    m2tom3_with_9.Set := IntSets.Exclude (m2tom3_with_9.Set, LookAhead);
                    IF IntSets.IsEmpty (m2tom3_with_9.Set) THEN m2tom3_with_9.Rep := tRep.NoRep; END;
                  ELSE
                    IF Verbose THEN
                      InformKept (item, LookAhead);     (* keep reduce          *)
                    END;
                    INC (ReduceRest);
                  END;
                ELSIF (m2tom3_with_9.Read = LookAhead) THEN
                  IF (ShiftPri < Priority) THEN         (* lower priority       *)
                    IF Verbose THEN
                      InformLowPri (item, LookAhead);   (* ignore read          *)
                    END;
                    m2tom3_with_9.Rep := tRep.NoRep;
                  ELSIF (ShiftPri = Priority) AND       (* max. priority        *)
                     ((Associativity = tAss.left) OR            (* left associative     *)
                     (Associativity = tAss.nonassoc)) AND       (* not associative      *)
                     (ReducePri = Priority) THEN        (* same priority        *)
                    IF Verbose THEN
                      InformLeftAss (item, LookAhead);  (* ignore read          *)
                    END;
                    m2tom3_with_9.Rep := tRep.NoRep;
                  ELSE
                    IF Verbose THEN
                      InformKept (item, LookAhead);     (* keep read            *);
                    END;
                    INC (ShiftRest);
                  END;
                END;
              END;
            END;

          ELSE (* NOT OnlyOpers *)

            IF ShiftCount > 0 THEN      (* shift wird reduce vorgezogen *)

              FOR item := m2tom3_with_7.Items TO m2tom3_with_7.Items + m2tom3_with_7.Size - 1 DO
                WITH m2tom3_with_10=ItemArrayPtr^[item] DO
                  IF (m2tom3_with_10.Rep = tRep.RedRep) AND (IntSets.IsElement (LookAhead, m2tom3_with_10.Set)) THEN
                    IF Verbose THEN
                      InformIgnored (item, LookAhead);  (* ignore reduce *)
                    END;
                    m2tom3_with_10.Set := IntSets.Exclude (m2tom3_with_10.Set, LookAhead);
                    IF IntSets.IsEmpty (m2tom3_with_10.Set) THEN m2tom3_with_10.Rep := tRep.NoRep; END;
                  ELSIF (m2tom3_with_10.Read = LookAhead) THEN
                    IF Verbose THEN
                      InformKept (item, LookAhead);
                    END;
                    INC (ShiftRest);
                  END;
                END;
              END;

            ELSE        (* erstes reduce auswaehlen *)

              FOR item := m2tom3_with_7.Items TO m2tom3_with_7.Items + m2tom3_with_7.Size - 1 DO
                WITH m2tom3_with_11=ItemArrayPtr^[item] DO
                  IF (m2tom3_with_11.Rep = tRep.RedRep) AND (IntSets.IsElement (LookAhead, m2tom3_with_11.Set)) THEN
                    prod := ADR (ProdArrayPtr^[m2tom3_with_11.Prod]);
                    IF prod^.ProdNo = MinProdNo THEN
                      IF Verbose THEN
                        InformKept (item, LookAhead);           (* keep reduce *)
                      END;
                      INC (ReduceRest);
                    ELSE
                      IF Verbose THEN
                        InformIgnored (item, LookAhead);        (* ignore reduce *)
                      END;
                      m2tom3_with_11.Set := IntSets.Exclude (m2tom3_with_11.Set, LookAhead);
                      IF IntSets.IsEmpty (m2tom3_with_11.Set) THEN m2tom3_with_11.Rep := tRep.NoRep; END;
                    END;
                  END;
                END;
              END;
            END;
          END;

          ConflictFree := FALSE;

          ReadRedSet := IntSets.Include (ReadRedSet, LookAhead);
            ELSE (* reduce - no conflict *)
              ConflictFree := TRUE;
            END;
          ELSE (* ReduceRest = 0 *)
            ConflictFree := TRUE;
          END;

          IF Verbose THEN NewLine(); END;
          IF ConflictFree THEN
            ConflictSet := IntSets.Exclude (ConflictSet, LookAhead);

            IF ReduceCount > 1 THEN
              IF ShiftCount > 0 THEN
                IF OnlyOpers THEN
                  RepReadRedRedSet := IntSets.Include (RepReadRedRedSet, LookAhead);
                ELSE
                  ARepReadRedRedSet := IntSets.Include (ARepReadRedRedSet, LookAhead);
                END;
              ELSE (* ShiftCount = 0 *)
                IF OnlyOpers THEN
                  RepRedRedSet := IntSets.Include (RepRedRedSet, LookAhead);
                ELSE
                  ARepRedRedSet := IntSets.Include (ARepRedRedSet, LookAhead);
                END;
              END;
            ELSIF ReduceCount = 1 THEN
              IF ShiftCount > 0 THEN
                IF OnlyOpers THEN
                  RepReadRedSet := IntSets.Include (RepReadRedSet, LookAhead);
                ELSE
                  ARepReadRedSet := IntSets.Include (ARepReadRedSet, LookAhead);
                END;
              ELSE (* ShiftCount = 0 *)
                ERROR ("Check.RepairConflict: No Conflict (1)");
              END;
            ELSE (* ReduceCount = 0 *)
              ERROR ("Check.RepairConflict: No Conflict (2)");
            END;
          END;
        END;
      END;

      ErrorMessageI (eState, eInformation, NoPosition, eShort, ADR (state));

      IF NOT IntSets.IsEmpty (ReadRedSet) THEN
        ErrorMessageI (eReadRed, eError, NoPosition, eTermSet, ADR (ReadRedSet));
      END;
      IF NOT IntSets.IsEmpty (RedRedSet) THEN
        ErrorMessageI (eRedRed, eError, NoPosition, eTermSet, ADR (RedRedSet));
      END;
      IF NOT IntSets.IsEmpty (ReadRedRedSet) THEN
        ErrorMessageI (eReadRedRed, eError, NoPosition, eTermSet, ADR (ReadRedRedSet));
      END;
      IF NOT IntSets.IsEmpty (RepReadRedSet) THEN
        ErrorMessageI (eRepReadRed, eInformation, NoPosition, eTermSet, ADR (RepReadRedSet));
      END;
      IF NOT IntSets.IsEmpty (RepRedRedSet) THEN
        ErrorMessageI (eRepRedRed, eInformation, NoPosition, eTermSet, ADR(RepRedRedSet));
      END;
      IF NOT IntSets.IsEmpty (RepReadRedRedSet) THEN
        ErrorMessageI (eRepReadRedRed, eInformation, NoPosition, eTermSet, ADR(RepReadRedRedSet));
      END;
      IF NOT IntSets.IsEmpty (ARepReadRedSet) THEN
        ErrorMessageI (eARepReadRed, eWarning, NoPosition, eTermSet, ADR(ARepReadRedSet));
      END;
      IF NOT IntSets.IsEmpty (ARepRedRedSet) THEN
        ErrorMessageI (eARepRedRed, eWarning, NoPosition, eTermSet, ADR(ARepRedRedSet));
      END;
      IF NOT IntSets.IsEmpty (ARepReadRedRedSet) THEN
        ErrorMessageI (eARepReadRedRed, eWarning, NoPosition, eTermSet, ADR(ARepReadRedRedSet));
      END;

      ReleaseSet (ReadRedSet);
      ReleaseSet (RedRedSet);
      ReleaseSet (ReadRedRedSet);
      ReleaseSet (RepReadRedSet);
      ReleaseSet (RepRedRedSet);
      ReleaseSet (RepReadRedRedSet);
      ReleaseSet (ARepReadRedSet);
      ReleaseSet (ARepRedRedSet);
      ReleaseSet (ARepReadRedRedSet);
      ReleaseSet (todo);
      IF Verbose THEN DebugEnd(); END;
    END RepairConflict;

  PROCEDURE ERROR (READONLY a: ARRAY OF CHAR) =
    VAR s: tString;
    BEGIN
      ArrayToString (a, s);
      ErrorMessageI (eInternal, eFatal, NoPosition, eString, ADR (s));
    END ERROR;

BEGIN
  Verbose := FALSE;
END Check.

