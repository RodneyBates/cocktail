(* generate the parser *)

(* $Id: Gen.mi,v 2.6 1992/08/12 07:04:48 grosch rel $ *)

(* Rodney M. Bates, modifications: 
    1-98 Change to not open /dev/null when -d (or -a) flag is not given. 
    3-2023 Add generation of Module-3 code. 
    Further changes in https://github.com/RodneyBates/cocktail
*) 

(* $Log: Gen.mi,v $
 * Revision 2.6  1992/08/12  07:04:48  grosch
 * extend parse table TComb over 65535 bytes
 *
 * Revision 2.5  1992/08/12  06:53:34  grosch
 * extend parse table TComb over 65535 bytes
 *
 * Revision 2.4  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.3  1992/01/30  14:08:30  grosch
 * redesign of interface to operating system
 *
 * Revision 2.2  1991/12/04  16:23:39  grosch
 * unified escape conventions for all tools
 *
 * Revision 2.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:31:42  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.4  90/12/20  19:26:39  grosch
 * removed time stamp from tables
 * 
 * Revision 1.3  90/06/12  17:17:20  grosch
 * layout improvements
 * 
 * Revision 1.2  90/06/12  16:54:10  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.1  89/10/18  19:41:35  grosch
 * renamed ScanTab and ParsTab to Scan.Tab and Pars.Tab because of PCTE
 * 
 * Revision 1.0  88/10/04  14:36:17  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE Gen;

  FROM SYSTEM IMPORT M2LONGINT, SHORTINT;
  FROM Actions IMPORT tActionMode, PutAction, WriteActions, ScannerName, ParserName;
  FROM ArgCheck IMPORT ExpandLine, MakeFileName, ScannerT, ParserT, ExtDef, ExtImp, LineFlag;
  FROM ArgCheck IMPORT MakeDef; 

  FROM Automaton IMPORT
    Infinite,
    tStateKind,
    tRep,
    tIndex,
    tProdIndex,
    tProduction,
    ProdArrayPtr, ProdIndex,
    NextProdIndex,
    ProdCount,
    ProdList,
    tStateIndex,
    StateArrayPtr, StateIndex,
    tItemIndex,
    ItemArrayPtr,
    StartSymbol;
  
  FROM Compress IMPORT
    InitCompressTable,
    CompressTableLine,
    InitCompressNTable,
    CompressNTableLine,
    TableSize,
    NTableSize,
    Base,
    NBase,
    Control,
    NNext,
    Default;

  FROM Continue IMPORT MakeContinuation;
  FROM FrontChecks   IMPORT CheckWriteOpen;

  FROM Default  IMPORT
    CreateDefaultList,
    PutInDefaultList,
    ComputeDefaults,
    GetNextState,
    GetTSortState,
    GetNSortState,
    GetDefaultTableLine;

  FROM DynArray IMPORT MakeArray, ExtendArray, ReleaseArray;
  FROM FrontErrors   IMPORT eString, eError;
  FROM Final    IMPORT MakeFinalToProd;
  FROM General  IMPORT Min;
  FROM GenLang  IMPORT WriteConstants, WriteReduceCode;
  FROM ReuseIO       IMPORT StdOutput, EndOfFile, WriteOpen, WriteClose, WriteC, WriteT,
    WriteI, WriteCard, WriteNl;
  
  FROM Lists    IMPORT MakeList, tList;
  IMPORT Word, Lists;
  FROM Sets     IMPORT tSet, MakeSet, ReleaseSet, Extract, Assign, IsEmpty;
  IMPORT Strings; (* Length *)
  FROM StringMem        IMPORT PutString;
  FROM Strings  IMPORT Char, tString, TextToString, Append, ReadL, WriteL, SubString;
  FROM Idents   IMPORT tIdent, GetString;
  FROM SysError IMPORT StatIsBad, SysErrorMessageI;
  
  IMPORT System; (* Close *)
  FROM System   IMPORT tFile, OpenOutput, Write;
  FROM Times    IMPORT StepTime;

  FROM TokenTab IMPORT
    MINNonTerm,
    MAXNonTerm,
    MAXTerm,
    PosType,
    TokenType,
    TokenError,
    Vocabulary,
    Terminal,
    GetTokenType,
    TokenToSymbol;
  
  FROM WriteTok IMPORT tLanguage, Language, GenWrTo;

  CONST EOL             = '\012';
  CONST InitReduceCount = 4;

  TYPE ControlType      = RECORD Check, Next : TableElmt; END;

  VAR TableLine : tTableLine;
  VAR StateCnt  : tStateIndex;
  VAR FileName  : ARRAY [0..128] OF CHAR;

  PROCEDURE GenDefaultActions() =
  VAR
    act: tList;
    pos: PosType;
    com: tList;
    cpos: PosType;
    s: tString;
  BEGIN
    MakeList (act); pos.Line := 0;      pos.Column := 0;
    MakeList (com); cpos.Line := 0;     cpos.Column := 0;

    IF ((Language = tLanguage.Modula3) OR (Language)) = tLanguage.Modula2 THEN
      TextToString ("{", s);
        Append (s,EOL); Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
      TextToString ("TYPE", s);
        Append (s,EOL); Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
      TextToString ("   tParsAttribute = RECORD", s);
        Append (s,EOL); Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
      TextToString ("                       Scan: Scanner.tScanAttribute", s);
        Append (s,EOL); Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
      TextToString ("                    END;", s);
        Append (s,EOL); Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
      TextToString ("}", s);
        Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
    ELSE (* Language = C *)
      TextToString ("{", s);
        Append (s,EOL); Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
      TextToString ("typedef struct    { tScanAttribute Scan; } tParsAttribute;", s);
        Append (s,EOL); Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
      TextToString ("}", s);
        Lists.Append (act, LOOPHOLE (PutString (s),ADDRESS));
    END;
    PutAction (tActionMode.Global, act, pos, com, cpos);
  END GenDefaultActions;

  PROCEDURE GenCode (Pars: tFile; Def: tFile) =
    VAR
      out  : tFile;
      line, rest, String1, String2: tString;
      N    : INTEGER;
    BEGIN
      FindKind();
      MakeNumbers();
      MakeLength();
      MakeLeftHandSide();
      MakeContinuation();
      MakeFinalToProd();

      IF Trace THEN
        WriteT (StdOutput," Time :");
        WriteI (StdOutput,StepTime(),5);
        WriteNl (StdOutput);
      END;

      MakeTable();

      IF Trace THEN
        WriteT (StdOutput," Time :");
        WriteI (StdOutput,StepTime(),5);
        WriteNl (StdOutput);
      END;

      (* Erzeuge Zerteilertabelle *)

      INC (TableSize, LastTerminal);
      INC (NTableSize, LastSymbol);
      IF (Language = tLanguage.Modula3) OR (Language = tLanguage.Modula2) THEN
         MakeFileName (ParserName, Parser, ".Tab", FileName);
         out := OpenOutput (FileName);
         IF StatIsBad (out) THEN
           TextToString (FileName, String1);
           SysErrorMessageI (out, eError, eString, ADR (String1));
         ELSE
           PutTables (out);
           System.Close (out);
         END;
      END;

      (* Mische den generierten Text in den Rahmen *)

      MakeFileName (ParserName, Parser, ExtImp, FileName);
      out := WriteOpen (FileName);
      CheckWriteOpen (out, FileName);
        
      WHILE NOT EndOfFile (Pars) DO
        ReadL (Pars, line);
        IF (Strings.Length (line) >= 2) AND (Char (line, 1) = '$') THEN
          CASE Char (line, 2) OF
          | 'G' => WriteActions  (tActionMode.Global,out, LineFlag);
          | 'T' => WriteConstants(out);
          | 'L' => WriteActions  (tActionMode.Local,out, LineFlag);
          | 'R' => PrepareReduceCode();
                  WriteReduceCode (out);
          | 'B' => WriteActions  (tActionMode.Begin,out, LineFlag);
          | 'C' => WriteActions  (tActionMode.Close,out, LineFlag);
          | 'X' => IF CaseFlag THEN
                    SubString   (line,3,Strings.Length(line),rest);
                    WriteL      (out,rest);
                  END;
          | 'W' => GenWrTo      (out);
          | 'P' => PutBase      (out);
          | 'Q' => PutNBase     (out);
          | 'D' => PutDefault   (out);
          | 'M' => PutControl   (out);
          | 'N' => PutNNext     (out);
          | 'K' => PutLength    (out);
          | 'H' => PutLeftHandSide      (out);
          | 'O' => PutContinuation      (out);
          | 'F' => PutFinalToProd       (out);
          | '@' => ExpandLine (out, line);
          END;
        ELSE
          WriteL (out,line);
        END;
      END;
      WriteClose (out);

      (* Mische Abschnitt EXPORT in Rahmen *)

      IF MakeDef AND (NOT EndOfFile (Def)) THEN
         MakeFileName (ParserName, Parser, ExtDef, FileName);
         out := WriteOpen (FileName);
         CheckWriteOpen (out, FileName);
         WHILE NOT EndOfFile (Def) DO
            ReadL (Def, line);
            IF (Strings.Length (line) >= 2) AND (Char (line, 1) = '$') THEN
               CASE Char (line, 2) OF
               | 'E' => WriteActions  (tActionMode.Export, out, LineFlag);
               | '@' => ExpandLine (out, line);
               END;
            ELSE
               WriteL (out, line);
            END;
         END;
         WriteClose (out);
      END;
    END GenCode;

  PROCEDURE FindKind() = (* Zustaende klassifizieren und mit einer neuen Nummer versehen *)
    VAR
      maxState,
      state : tStateIndex;
      prod : tProduction;
      item : tItemIndex;
      RepCount : Word.T;
      LastItem : tItemIndex;
    BEGIN
      maxState := StateIndex;
      FOR state := 1 TO maxState DO     (* Betrachte alle Zustaende *)
        WITH m2tom3_with_1=StateArrayPtr^[state] DO
          IF m2tom3_with_1.Size = 1 THEN
            RepCount := 1;
            item := m2tom3_with_1.Items;
          ELSE
            RepCount := 0;
            FOR item := m2tom3_with_1.Items TO m2tom3_with_1.Items + m2tom3_with_1.Size - 1 DO
            WITH m2tom3_with_2=ItemArrayPtr^[item] DO
              IF m2tom3_with_2.Rep # tRep.NoRep THEN
                INC (RepCount);
                LastItem := item;
              END;
            END;
            END;
            item := LastItem;
          END;

          IF RepCount = 1 THEN          (* Zustand enthaelt nur ein Item *)
            WITH m2tom3_with_3=ItemArrayPtr^[item] DO
              IF m2tom3_with_3.Rep = tRep.RedRep THEN   (* es handelt sich um eine Reduktion *)
                prod := ADR (ProdArrayPtr^[m2tom3_with_3.Prod]); (* beschaffe zugh. Produktion *)
                WITH m2tom3_with_4=prod^ DO
                  IF m2tom3_with_4.Right[m2tom3_with_4.Len] > MAXTerm THEN (* letztes Symbol war ein Nichtterminal *)
                    m2tom3_with_1.Kind := tStateKind.sNonterm;
                  ELSE                  (* letztes Symbol war ein Terminal *)
                    m2tom3_with_1.Kind := tStateKind.sTerm;
                  END;
                END;
              ELSE                      (* es handelt sich um einen Read-Zustand *)
                m2tom3_with_1.Kind := tStateKind.sRead;
              END;
            END;
          ELSE                          (* Zustand mit mehreren Items, die Repraesanten sind,
                                           muss ein Read-Zustand sein *)
            m2tom3_with_1.Kind := tStateKind.sRead;
          END;
        END;
      END;
    END FindKind;

  PROCEDURE MakeNumbers() =
  VAR
    maxState, state : tStateIndex;
    prodADR : (*tProduction*) ADDRESS;
    prod : tProduction;
    remember : tStateIndex;
  BEGIN
      FirstTerminal := FindFirstTerminal();
      LastTerminal  := FindLastTerminal();
      NonTermOffset := MINNonTerm - LastTerminal - 1;
      FirstSymbol   := FirstTerminal;
      LastSymbol    := FindLastSymbol()-NonTermOffset;
      StateCnt      := 0;
      maxState      := StateIndex;
      FirstState    := 1;

      (* Trage neue Nummern fuer ReadStates ein *)

      FirstReadState := StateCnt+1;
      FOR state := 1 TO maxState DO
        WITH m2tom3_with_9=StateArrayPtr^[state] DO
          IF m2tom3_with_9.Kind = tStateKind.sRead THEN
            INC(StateCnt);
            m2tom3_with_9.NewNumber := StateCnt;
          END;
        END;
      END;
      LastReadState := StateCnt;

      (* Trage neue Nummern fuer ReadTermStates ein *)

      FirstReadTermState := StateCnt+1;
      FOR state := 1 TO maxState DO
        WITH m2tom3_with_10=StateArrayPtr^[state] DO
          IF m2tom3_with_10.Kind = tStateKind.sTerm THEN
            prod := ADR (ProdArrayPtr^[ItemArrayPtr^[m2tom3_with_10.Items].Prod]);
            IF prod^.Left = StartSymbol THEN
              remember := state;   (* Stopzustand kommt in andere Gruppe *)
            ELSE
              INC(StateCnt);
              m2tom3_with_10.NewNumber := StateCnt;
            END;
          END;
        END;
      END;
      LastReadTermState := StateCnt;

      (* Trage neue Nummern fuer ReadNonTermStates ein *)

      FirstReadNonTermState := StateCnt+1;
      FOR state := 1 TO maxState DO
        WITH m2tom3_with_11=StateArrayPtr^[state] DO
          IF m2tom3_with_11.Kind = tStateKind.sNonterm THEN
            INC(StateCnt);
            m2tom3_with_11.NewNumber := StateCnt;
          END;
        END;
      END;
      LastReadNonTermState := StateCnt;

      (* Nummern fuer ReduceStates *)

      ReduceOffset := StateCnt;
      WITH m2tom3_with_12=StateArrayPtr^[remember] DO
        prodADR := ADR(ProdArrayPtr^[ItemArrayPtr^[m2tom3_with_12.Items].Prod]);
        prod := LOOPHOLE (prodADR, tProduction);
        m2tom3_with_12.NewNumber := prod^.ProdNo + ReduceOffset;
      END;

      FirstReduceState  := StateCnt+1;
      LastReduceState   := ReduceOffset+ProdCount;
      StopState         := FirstReduceState;
      LastState         := LastReduceState;
    END MakeNumbers;

  PROCEDURE MakeTable() =
    VAR
      maxState : tStateIndex;
      state    : tStateIndex;
      index    : tStateIndex;
      NewNum   : tStateIndex;
      DefaultState  : tStateIndex;
    BEGIN

      (* Erstellen der Listen fuer Defaultberechnung *)

      CreateDefaultList();
      maxState := StateIndex;
      FOR state := 1 TO maxState DO
        InitTableLine();
        NewNum := MakeTableLine (state);
        IF NewNum <= LastReadState THEN
          PutInDefaultList (NewNum, TableLine);
        END;
      END;

      (* Berechnung der Defaults *)

      ComputeDefaults();

      (* Comprimieren der Tabelle *)

(* - - - alternative 1a 
      InitCompressTable;
      NewNum := GetNextState (NoState);
      WHILE NewNum # NoState DO
        GetDefaultTableLine (NewNum, TableLine, DefaultState);
        CompressTableLine (NewNum, DefaultState, TableLine);
        NewNum := GetNextState (NewNum);
      END;
 - - - *)

(* - - - alternative 1b *)
      InitCompressTable();
      FOR index := 1 TO LastReadState DO
        NewNum := GetTSortState (index);
        GetDefaultTableLine (NewNum, TableLine, DefaultState);
        CompressTableLine (NewNum, DefaultState, TableLine);
      END;
(*- - - *)

(* - - -  alternative  2a 
      InitCompressNTable;
      NewNum := GetNextState (NoState);
      WHILE NewNum # NoState DO
        GetDefaultTableLine (NewNum, TableLine, DefaultState);
        CompressNTableLine (NewNum, TableLine);
        NewNum := GetNextState (NewNum);
      END;
 - - - *)

(* - - -  alternative  2b *)
      InitCompressNTable();
      FOR index := 1 TO LastReadState DO
        NewNum := GetNSortState (index);
        GetDefaultTableLine (NewNum, TableLine, DefaultState);
        CompressNTableLine (NewNum, TableLine);
      END;
(* - - - *)
    END MakeTable;

  PROCEDURE InitTableLine() =
    VAR
      state : tStateIndex;
      symbol : Vocabulary;
    BEGIN
      FOR symbol := FirstSymbol TO LastSymbol DO
        TableLine[symbol] := NoState;
      END;
    END InitTableLine;
  
  PROCEDURE MakeTableLine (state : tStateIndex) : tStateIndex =
    VAR
      RedState : tStateIndex;
      maxState : tStateIndex;
      item : tItemIndex;
      prodADR : (*tProduction*) ADDRESS;
      prod : tProduction;
      Look : IntSets.T;
      t : Terminal;
    BEGIN
      Look := IntSets.Emptyu();

      (* alle States *)

      WITH m2tom3_with_13=StateArrayPtr^[state] DO

        (* nur ReadStates *)

        IF m2tom3_with_13.Kind = tStateKind.sRead THEN

          (* alle Items *)

          FOR item := m2tom3_with_13.Items TO m2tom3_with_13.Items + m2tom3_with_13.Size - 1 DO
          WITH m2tom3_with_14=ItemArrayPtr^[item] DO
            CASE m2tom3_with_14.Rep OF
            | tRep.TermRep=>
                TableLine[m2tom3_with_14.Read] := StateArrayPtr^[m2tom3_with_14.Next].NewNumber;
            | tRep.NonTermRep=>
                TableLine[m2tom3_with_14.Read-NonTermOffset] := StateArrayPtr^[m2tom3_with_14.Next].NewNumber;
            | tRep.RedRep=>
                prodADR := ADR(ProdArrayPtr^[m2tom3_with_14.Prod]);
                prod := LOOPHOLE (prodADR, tProduction);
                RedState := ReduceOffset + prod^.ProdNo;
                Look := m2tom3_with_14.Set;
                Assign (Look,m2tom3_with_14.Set);
                WHILE NOT IntSets.IsEmpty (Look) DO
                  t := IntSets.Extract((*VAR*)Look);
                  TableLine[t] := RedState;
                END;
              ELSE
            END;
          END;
          END;
        END;

        Look := NIL;
        RETURN (m2tom3_with_13.NewNumber);
      END;
    END MakeTableLine;

  PROCEDURE MakeLength() =
    VAR
      prodADR : (*tProduction*) ADDRESS;
      prod : tProduction;
      index,prodno: tProdIndex;
    BEGIN
      LengthCount := ProdCount;
      Length := NEW (REF ARRAY OF TableElmt, LengthCount);
(*WAS:MakeArray (Length,LengthCount,ElmtSize);*)
      index := 0;
      FOR prodno := 1 TO ProdCount DO
        prodADR := ADR(ProdArrayPtr^[index]);
        prod := LOOPHOLE (prodADR, tProduction);
        Length^[prodno] := prod^.Len;
        index := NextProdIndex(index);
      END;
    END MakeLength;  

  PROCEDURE MakeLeftHandSide() =
    VAR
      prodADR : (*tProduction*) ADDRESS;
      prod : tProduction;
      index,prodno: tProdIndex;
    BEGIN
      LeftHandSideCount := ProdCount;
      LeftHandSide := NEW (REF ARRAY OF TableElmt, LeftHandSideCount);
(*WAS:MakeArray (LeftHandSide,LeftHandSideCount,TableElmt);*)
      index := 0;
      FOR prodno := 1 TO ProdCount DO
        prodADR := ADR(ProdArrayPtr^[index]);
        prod := LOOPHOLE (prodADR, tProduction);
        LeftHandSide^[prodno] := prod^.Left - NonTermOffset;
        index := NextProdIndex(index);
      END;
    END MakeLeftHandSide;  

  PROCEDURE FindFirstTerminal ():Vocabulary =
    BEGIN
      RETURN 0;                 (* EndOfToken wird immer mit 0 codiert *)
    END FindFirstTerminal;

  PROCEDURE FindLastTerminal ():Vocabulary =
    VAR sym : Vocabulary;
    BEGIN
      sym := MAXTerm;
      LOOP
        IF GetTokenType (sym) = TokenType.Term THEN RETURN sym END;
        DEC (sym);
      END;
    END FindLastTerminal;

  PROCEDURE FindLastSymbol ():Vocabulary =
    VAR sym : Vocabulary;
    BEGIN
      sym := MAXNonTerm;
      LOOP
        IF GetTokenType (sym) # TokenType.None THEN RETURN sym END;
        DEC (sym);
      END;
    END FindLastSymbol;

  PROCEDURE StartState ():Word.T =
    BEGIN
      RETURN StateArrayPtr^[1].NewNumber;
    END StartState;

  PROCEDURE PrepareReduceCode() =
    VAR
      index : tProdIndex;
      prod  : tProduction;
      maxState,state : tStateIndex;
      maxProdIndex : tProdIndex;
      u : M2LONGINT;
      item : tItemIndex;
    BEGIN
      (* Felder fuer Statelisten initialisieren *)

      index := 0;
      state := ReduceOffset;
      maxProdIndex := ProdIndex;
      WHILE index < maxProdIndex DO
        INC (state);
        prod := ADR (ProdArrayPtr^[index]);
        WITH m2tom3_with_16=prod^.Reduce DO
          m2tom3_with_16.Count := InitReduceCount;
          m2tom3_with_16.Array := NEW (REF ARRAY OF tIndex, m2tom3_with_16.Count);
(*WAS:    MakeArray (m2tom3_with_16.Array, m2tom3_with_16.Count, BYTESIZE(tIndex));*)
          m2tom3_with_16.Used := 1;
          m2tom3_with_16.Array^[1] := state; (* Reduce State *)
        END;
        index := NextProdIndex(index);
      END;

      (* Felder ausfuellen *)

      maxState := StateIndex;
      FOR state := 1 TO maxState DO
        WITH m2tom3_with_17=StateArrayPtr^[state] DO
          IF (m2tom3_with_17.Kind = tStateKind.sTerm) OR (m2tom3_with_17.Kind = tStateKind.sNonterm) THEN

            (* Read-Terminal- bzw. Read-Nonterminal-Reducee *)
            (* Finde erste Item, das Repraesentant ist *)

            item := m2tom3_with_17.Items;
            LOOP
              IF ItemArrayPtr^[item].Rep # tRep.NoRep THEN
                EXIT;
              END;
              INC (item);
            END;

            (* bestimme zugh. Produktion *)

            IF m2tom3_with_17.NewNumber <= ReduceOffset THEN
            (* StopState ausfiltern *)

              index := ItemArrayPtr^[item].Prod;
              prod := ADR (ProdArrayPtr^[index]);
              WITH m2tom3_with_18=prod^.Reduce DO
                INC (m2tom3_with_18.Used);
                IF m2tom3_with_18.Used > m2tom3_with_18.Count THEN
                  (*ExtendArray (m2tom3_with_18.Array,m2tom3_with_18.Count,BYTESIZE(tIndex));*)
                END;
                m2tom3_with_18.Array^[m2tom3_with_18.Used] := m2tom3_with_17.NewNumber;
              END;
            END;
          END;
        END;
      END;
    END PrepareReduceCode;

PROCEDURE PutTables (TableFile: tFile) =
  VAR InError           : BOOLEAN;
      BlockSize , i     : Word.T;

    PROCEDURE PutTable (Length: TableElmt; Address: ADDRESS) =
       VAR
          N     : INTEGER;
          string: tString;
       BEGIN
          N := Write (TableFile, ADR (Length), ElmtSize);
          IF StatIsBad (N) THEN
            TextToString (FileName, string);
            SysErrorMessageI (N, eError, eString, ADR (string));
            InError := TRUE;
            RETURN;
          END;
          N := Write (TableFile, Address, Length);
          IF StatIsBad (N) THEN
            TextToString (FileName, string);
            SysErrorMessageI (N, eError, eString, ADR (string));
            InError := TRUE;
            RETURN;
          END;
       END PutTable;

   BEGIN
      BlockSize := 64000 DIV BYTESIZE (ControlType);
      InError := FALSE;
      PutTable ((LastReadState + 1) * ElmtSize, Base);
      IF InError THEN RETURN END;
      PutTable ((LastReadState + 1) * ElmtSize, NBase);
      IF InError THEN RETURN END;
      PutTable ((LastReadState + 1) * ElmtSize, Default);
      IF InError THEN RETURN END;
      PutTable ((NTableSize - LastTerminal) * BYTESIZE (TableElmt), ADR (NNext^[LastTerminal + 1]));
      IF InError THEN RETURN END;
      PutTable ((LastReduceState - FirstReduceState + 1) * ElmtSize, Length);
      IF InError THEN RETURN END;
      PutTable ((LastReduceState - FirstReduceState + 1) * ElmtSize, LeftHandSide);
      IF InError THEN RETURN END;
      PutTable ((LastReadState + 1) * ElmtSize, Continuation);
      IF InError THEN RETURN END;
      PutTable ((LastReadNonTermState - FirstReadTermState + 1) * ElmtSize, FinalToProd);
      IF InError THEN RETURN END;

      i := 0;
      WHILE i <= TableSize DO
         PutTable (Min (BlockSize, TableSize + 1 - i) * BYTESIZE (ControlType), ADR (Control^[i]));
         IF InError THEN RETURN END;
         INC (i, BlockSize);
      END;
   END PutTables;

PROCEDURE PutBase       (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := 0 TO LastReadState DO
         WriteT (File, "& yyTComb [");
         WriteI (File, Base^[i], 0); WriteT (File, "],"); WriteNl (File);
      END;
   END PutBase;

PROCEDURE PutNBase      (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := 0 TO LastReadState DO
         WriteT (File, "& yyNComb [");
         WriteI (File, LOOPHOLE (NBase^[i],SHORTINT) - LOOPHOLE (LastTerminal,SHORTINT) - 1, 0);
         WriteT (File, "],"); WriteNl (File);
      END;
   END PutNBase;

PROCEDURE PutDefault    (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := 0 TO LastReadState DO
         WriteI (File, Default^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutDefault;

PROCEDURE PutControl    (File: tFile) =
   VAR i: Word.T;
   BEGIN
      FOR i := 0 TO TableSize DO
         WriteC (File, '{');
         WriteI (File, Control^[i].Check, 0); WriteT (File, ", ");
         WriteI (File, Control^[i].Next , 0); WriteT (File, "},"); WriteNl (File);
      END;
   END PutControl;

PROCEDURE PutNNext      (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := LastTerminal + 1 TO NTableSize DO
         WriteI (File, NNext^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutNNext;

PROCEDURE PutLength     (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := 1 TO ProdCount DO
         WriteI (File, Length^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutLength;

PROCEDURE PutLeftHandSide       (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := 1 TO ProdCount DO
         WriteI (File, LeftHandSide^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutLeftHandSide;

PROCEDURE PutContinuation       (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := 0 TO LastReadState DO
         WriteI (File, Continuation^[i], 0); WriteC (File, ','); WriteNl (File);
      END;
   END PutContinuation;

PROCEDURE PutFinalToProd        (File: tFile) =
   VAR i: tStateIndex;
   BEGIN
      FOR i := FirstReadTermState TO LastReadNonTermState DO
        
         WriteI (File, FinalToProd^[i - FirstReadTermState], 0);
         WriteC (File, ','); WriteNl (File);
      END;
   END PutFinalToProd;

(* +++ 

  PROCEDURE PrintTable;
    VAR maxState, state, NewNum : tStateIndex;
    BEGIN
      WriteT (StdOutput,"***** Table ***** ");
      WriteNl (StdOutput);
      maxState := StateIndex;
      FOR state := 1 TO maxState DO
        InitTableLine;
        NewNum := MakeTableLine (state);
        IF NewNum <= LastReadState THEN
          PrintTableLine (NewNum);
        END;
      END;
    END PrintTable;

  PROCEDURE PrintTableLine (state:tStateIndex);
    VAR
      nextstate : tStateIndex;
      symbol : Vocabulary;
    BEGIN
      WriteT (StdOutput,"State ");
      WriteCard (StdOutput,state,1);
      WriteC (StdOutput,':');
      FOR symbol := FirstSymbol TO LastSymbol DO
        nextstate := TableLine [symbol];
        IF nextstate # NoState THEN
          WriteT (StdOutput," (");
          IF symbol > LastTerminal THEN
            PrintToken (symbol+NonTermOffset);
          ELSE
            PrintToken (symbol);
          END;
          WriteC (StdOutput,',');
          WriteCard (StdOutput,nextstate,1);
          WriteC (StdOutput,')');
        END;
      END;
      WriteNl (StdOutput);
    END PrintTableLine;

  PROCEDURE PrintLength;
    VAR prodno : tProdIndex;
    BEGIN
      WriteT (StdOutput,"***** Length ***** ");
      WriteNl (StdOutput);
      FOR prodno := 1 TO ProdCount DO
        WriteT (StdOutput,"Length (");
        WriteCard (StdOutput,prodno,1);
        WriteT (StdOutput,") = ");
        WriteCard (StdOutput,Length^[prodno],1);
        WriteNl (StdOutput);
      END;
      WriteNl (StdOutput);
    END PrintLength;

  PROCEDURE PrintLeftHandSide;
    VAR prodno : tProdIndex;
    BEGIN
      WriteT (StdOutput,"***** LeftHandSide ***** ");
      WriteNl (StdOutput);
      FOR prodno := 1 TO ProdCount DO
        WriteT (StdOutput,"LeftHandSide (");
        WriteCard (StdOutput,prodno,1);
        WriteT (StdOutput,") = ");
        PrintToken (LeftHandSide^[prodno]);
        WriteNl (StdOutput);
      END;
      WriteNl (StdOutput);
    END PrintLeftHandSide;
 --- *)

BEGIN
  ElmtSize      := BYTESIZE (TableElmt);
  Trace         := FALSE;
  CaseFlag      := FALSE;
END Gen.

