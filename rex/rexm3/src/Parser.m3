(* $Id: Parser.mi,v 2.8 1992/08/12 06:54:05 grosch rel $ *)
(* Skeleton parser for Cocktail lalr. *)
(* Modified Rodney M. Bates. Various times. *)

 UNSAFE MODULE Parser;

IMPORT Fmt;
IMPORT OSError;
IMPORT Process;
IMPORT Text;


FROM SYSTEM IMPORT M2LONGINT, M2LONGCARD, SHORTCARD;

IMPORT Word, SYSTEM, Scanner, Positions, Strings, DynArray, Sets, System;

(* line 24 "/tmp/lalr4706" *)
(* line 26 ../src/rex.lalr *)

IMPORT RexErrors AS Errors;

FROM Tree0      IMPORT
   tTree0       , Tree0Root     ,
   mNode        , mRule         , mPattern      ,
   mCh          , mSet          , mString       , mList         ,
   mAlternative , mSequence     , mRepetition   , mOption       ;

FROM Tree       IMPORT
   tTree        ;

FROM Sets       IMPORT
   tSet         , MakeSet       , ReleaseSet    ,
   Union                , Include       , Exclude       ,
   Complement   ;

FROM Strings    IMPORT
   tString      , ArrayToString , IntToString   ;

FROM Lists      IMPORT
   tList        ;

FROM StringMem  IMPORT
   tStringRef   , PutString     ;

FROM Idents     IMPORT
   tIdent       , MakeIdent     , GetString     , GetStringRef  , NoIdent       ;

FROM DefTable   IMPORT
   NoDef        , DefRange      , tKind         , GetKind       ,
   MakeIdentDef , MakeStartDef  , GetDef        , GetIdentDef   ,
   GetStartDef  ;

FROM GenTabs    IMPORT
   StartStateCount, RuleCount   , PatternCount  , LeftJustUsed  ;

FROM Dfa        IMPORT
   BlankCh      , TabCh         , EolCh         , LastCh        ;

FROM ScanGen    IMPORT
   Export       , Global        , Local         , Begin         ,
   Close        , Eof           , Position      , NoPosition    ,
   ExportLine   , GlobalLine    , LocalLine     , BeginLine     ,
   CloseLine    , EofLine       , DefaultLine   , Default       ,
   BlankText    , TabText       , EolText       ,
   ScannerName  , InitScanGen   ;

CONST
   IdentUndefined       = 10    ;
   ImproperUse          = 11    ;
   IdentDefBefore       = 12    ;
   Error                = 3     ;
   String               = 7     ;

TYPE
   tParsAttribute = RECORD
       
        Scan            : Scanner.tScanAttribute;
        Tree            : tTree0        ;
        IsLeftJust      : BOOLEAN       ;
           Position     : Positions.tPosition;
        Set             : tSet          ;
      
   END;

VAR
   Number       : SHORTCARD     ;
   bool         : BOOLEAN       ;
   string       : tString       ;
   stringref    : tStringRef    ;
   set          : tSet          ;
   tree         : tTree0        ;
   tree1        : tTree         ;
   Definition   : DefRange      ;
   Identifier   : tIdent        ;
   nNode        ,
   EOLTree      : tTree0        ;
   ch           : CHAR          ;

PROCEDURE AppendRule (Tree: tTree0; Ch: CHAR; Text: tList): tTree0 =
   VAR
      Set       : tSet  ;
      t         : tTree0;
   BEGIN
      MakeSet (Set, StartStateCount);
      Complement (Set);
      Exclude (Set, 0);
      t := mCh (Ch);
      INC (PatternCount);
      t := mPattern (Set, t, nNode, PatternCount, Positions.NoPosition);
      t := mList (nNode, t);
      INC (RuleCount);
      t := mRule (t, Text, 0, NoPosition, RuleCount);
      RETURN mList (Tree, t);
   END AppendRule;


CONST
   yyInitStackSize      = 100;
   yyNoState            = 0;

   yyFirstTerminal              = 0;
   yyLastTerminal               = 38;
   yyFirstSymbol                = 0;
   yyLastSymbol         = 64;
   yyTableMax           = 221;
   yyNTableMax          = 89;
   yyFirstReadState             = 1;
   yyLastReadState              = 55;
   yyFirstReadTermState         = 56;
   yyLastReadTermState          = 84;
   yyLastReadNontermState               = 99;
   yyFirstReduceState           = 100;
   yyLastReduceState            = 164;
   yyStartState         = 1;
   yyStopState          = 100;

   yyFirstFinalState    = yyFirstReadTermState;
   yyLastState          = yyLastReduceState;

   yyTableElmtBits = BITSIZE (yyTableElmt); 

TYPE
   (* The following ranges all need to occupy 16 bits when in an array, in order to
      match the to-be-read-in table files.  Using BITS FOR doesn't work because of
      cm3 CG errors compiling BITS FOR BITS FOR. *)
   yyTableElmt       = SHORTCARD;
   yyTCombRange      = BITS yyTableElmtBits FOR [0 .. yyTableMax];
   yyNCombRange      = BITS yyTableElmtBits FOR [yyLastTerminal + 1 .. yyNTableMax];
   yyStateType       = [0 .. yyLastState];
   yyStateRange      = BITS yyTableElmtBits FOR yyStateType;
   yyReadRange       = BITS yyTableElmtBits FOR [yyFirstReadState .. yyLastReadState];
   yyReadReduceRange = BITS yyTableElmtBits FOR [yyFirstReadTermState ..yyLastReadNontermState];
   yyReduceRange     = BITS yyTableElmtBits FOR [yyFirstReduceState .. yyLastReduceState];
   yySymbolType      = [yyFirstSymbol .. yyLastSymbol];
   yySymbolRange     = BITS yyTableElmtBits FOR yySymbolType;

   yyTCombType          = RECORD Check, Next: yyStateRange; END;
   yyNCombType          = yyStateRange;
   yyTCombTypePtr       = UNTRACED BRANDED REF  yyTCombType;
   yyNCombTypePtr       = UNTRACED BRANDED REF  yyNCombType;
   yyStackPtrType       = yyTableElmt;
   yyStackType          = UNTRACED BRANDED REF  ARRAY yyStackPtrType OF yyStateRange;
   yyAttributeStackType = UNTRACED BRANDED REF  ARRAY yyStackPtrType OF tParsAttribute;

VAR

yyByteSizeType := BYTESIZE (yySymbolType);
yyByteSizeRange := BYTESIZE (yySymbolRange);

   yyTBasePtr           : ARRAY (*yyTableElmt*) [0 .. yyLastReadState] 
                          OF yyTCombTypePtr;
   yyNBasePtr           : ARRAY (*yyTableElmt*) [0 .. yyLastReadState]      
                          OF yyNCombTypePtr;
   yyDefault            : ARRAY (*yyTableElmt*) [0 .. yyLastReadState]      
                          OF yyReadRange  ;
   yyTComb              : ARRAY yyTCombRange            OF yyTCombType  ;
   yyNComb              : ARRAY yyNCombRange            OF yyNCombType  ;
   yyLength             : ARRAY yyReduceRange           OF yyTableElmt  ;
   yyLeftHandSide       : ARRAY yyReduceRange           OF yySymbolRange;
   yyContinuation       : ARRAY (*yyTableElmt*) [0 .. yyLastReadState]      
                          OF yySymbolRange;
   yyFinalToProd        : ARRAY yyReadReduceRange       OF yyReduceRange;
   yyIsInitialized      : BOOLEAN;
   yyTableFile          : System.tFile;

PROCEDURE TokenName (Token: SHORTCARD; VAR Name: ARRAY OF CHAR) =

   PROCEDURE CopyT (Source: TEXT; VAR Target: ARRAY OF CHAR) =
      VAR lastSource: INTEGER;
      VAR j: INTEGER;
      BEGIN
        IF Source # NIL
        THEN
         lastSource := Text.Length (Source)-1;
         IF lastSource  < LAST (Target)
         THEN j := lastSource; ELSE j := LAST (Target); END;
         FOR i := 0 TO j DO Target [i] := Text.GetChar (Source,i); END;
         IF LAST (Target) > j THEN Target [j + 1] := VAL (0,CHAR); END;
        END;
      END CopyT;
      
   PROCEDURE CopyA (READONLY Source: ARRAY OF CHAR; VAR Target: ARRAY OF CHAR) =
      VAR j: Word.T;
      BEGIN
         IF LAST (Source) < LAST (Target)
         THEN j := LAST (Source); ELSE j := LAST (Target); END;
         FOR i := 0 TO j DO Target [i] := Source [i]; END;
         IF LAST (Target) > j THEN Target [j + 1] := VAL (0,CHAR); END;
      END CopyA;
      
   PROCEDURE Copy (Ch: CHAR; VAR Target: ARRAY OF CHAR) =
      BEGIN
         Target [0] := Ch;
         IF LAST (Target) > 0 THEN Target [1] := VAL (0,CHAR); END;
      END Copy;
      
   BEGIN
      CASE Token OF
      | 0=> CopyT ("_EndOfFile", Name);
      | 1=> CopyT ("Ident", Name);
      | 2=> CopyT ("Number", Name);
      | 3=> CopyT ("String", Name);
      | 4=> CopyT ("Char", Name);
      | 5=> CopyT ("TargetCode", Name);
      | 6=> CopyT ("GLOBAL", Name);
      | 7=> CopyT ("BEGIN", Name);
      | 8=> CopyT ("CLOSE", Name);
      | 9=> CopyT ("DEFINE", Name);
      | 10=> CopyT ("START", Name);
      | 11=> CopyT ("RULES", Name);
      | 12=> Copy ('.', Name);
      | 13=> Copy (',', Name);
      | 14=> Copy ('=', Name);
      | 15=> Copy (':', Name);
      | 16=> Copy ('/', Name);
      | 17=> Copy ('|', Name);
      | 18=> Copy ('+', Name);
      | 19=> Copy ('-', Name);
      | 20=> Copy ('*', Name);
      | 21=> Copy ('?', Name);
      | 22=> Copy ('(', Name);
      | 23=> Copy (')', Name);
      | 24=> Copy ('[', Name);
      | 25=> Copy (']', Name);
      | 26=> Copy ('{', Name);
      | 27=> Copy ('}', Name);
      | 28=> Copy ('<', Name);
      | 29=> Copy ('>', Name);
      | 30=> CopyT ("NOT", Name);
      | 31=> CopyT ("LOCAL", Name);
      | 32=> CopyT ("EXPORT", Name);
      | 33=> Copy ('#', Name);
      | 34=> CopyT ("EOF", Name);
      | 35=> CopyT (":-", Name);
      | 36=> CopyT ("DEFAULT", Name);
      | 37=> CopyT ("SCANNER", Name);
      | 38=> CopyT ("SEQUENCE", Name);
      END;
   END TokenName;

PROCEDURE Parser (): Word.T =

   VAR
      yyState           : yyStateType;
      yyTerminal        : yySymbolType;
      yyNonterminal     : yySymbolType;        (* left-hand side symbol *)
      yyStackPtr        : yyStackPtrType;
      yyStateStackSize  : M2LONGINT;
      yyAttrStackSize   : M2LONGINT;
      yyShortStackSize  : yyStackPtrType;
      yyStateStack      : yyStackType;
      yyAttributeStack  : yyAttributeStackType;
      yySynAttribute    : tParsAttribute;       (* synthesized attribute *)
   yyRepairAttribute : Scanner.tScanAttribute;
      yyRepairToken     : yySymbolType;
      yyTCombPtr        : yyTCombTypePtr;
      yyNCombPtr        : yyNCombTypePtr;
      yyIsRepairing     : BOOLEAN;
      yyErrorCount      : Word.T;
      yyTokenString     : ARRAY [0..127] OF CHAR;
   BEGIN
   BeginParser();
      yyState           := yyStartState;
   yyTerminal        := VAL ( Scanner.GetToken (),yySymbolType);
      yyStateStackSize  := yyInitStackSize;
      yyAttrStackSize   := yyInitStackSize;
      DynArray.MakeArray 
        (LOOPHOLE(yyStateStack,ADDRESS), yyStateStackSize, BYTESIZE (yyStateRange));
      DynArray.MakeArray 
        (LOOPHOLE(yyAttributeStack,ADDRESS), yyAttrStackSize, BYTESIZE (tParsAttribute));
      yyShortStackSize  := VAL (   yyStateStackSize,yyStackPtrType ) - 1;
      yyStackPtr        := 0;
      yyErrorCount      := 0;
      yyIsRepairing     := FALSE;

      LOOP
         IF yyStackPtr >= yyShortStackSize THEN
            DynArray.ExtendArray 
              (LOOPHOLE(yyStateStack,ADDRESS), yyStateStackSize, BYTESIZE (yyStateRange));
            DynArray.ExtendArray 
              (LOOPHOLE(yyAttributeStack,ADDRESS), yyAttrStackSize, 
               BYTESIZE (tParsAttribute)
              );
            yyShortStackSize := VAL (   yyStateStackSize,yyStackPtrType ) - 1;
         END (* IF *) ;
         yyStateStack^ [yyStackPtr] := yyState;

         LOOP   (* SPEC State := Next (State, Terminal); terminal transition *)
            yyTCombPtr := LOOPHOLE 
                            ( LOOPHOLE ( yyTBasePtr [yyState] ,M2LONGCARD) 
                              + (VAL (   yyTerminal,M2LONGCARD ) 
                                * BYTESIZE (yyTCombType))
                            ,yyTCombTypePtr);
            IF yyTCombPtr^.Check = yyState 
            THEN
               yyState := yyTCombPtr^.Next;
               EXIT;
            END (* IF *) ;
            yyState := yyDefault [yyState];

            IF yyState = yyNoState 
            THEN (* syntax error *)
               yyState := yyStateStack^ [yyStackPtr];
               IF yyIsRepairing 
               THEN (* repair *)
                  yyRepairToken := yyContinuation [yyState];
                  yyState := Next (yyState, yyRepairToken);
                  IF yyState <= yyLastReadTermState 
                  THEN (* read or read terminal reduce ? *)
                  Scanner.ErrorAttribute 
                       (VAL(yyRepairToken,INTEGER), yyRepairAttribute);
                     TokenName (yyRepairToken, yyTokenString);
                     Errors.ErrorMessageI 
                       (Errors.TokenInserted, Errors.Repair,
                     Scanner.Attribute.Position, Errors.Array, 
                        ADR (yyTokenString[FIRST(yyTokenString)])
                       );
                     IF yyState >= yyFirstFinalState 
                     THEN (* avoid second push *)
                        yyState := yyFinalToProd [yyState];
                     END (* IF *) ;
                     INC (yyStackPtr);
                     yyAttributeStack^ [yyStackPtr].Scan := yyRepairAttribute;
                     yyStateStack^     [yyStackPtr] := yyState;
                  END (* IF *) ;
                  IF yyState >= yyFirstFinalState 
                  THEN (* final state ? *)
                    EXIT;
                  END (* IF *) ;
               ELSE (* report and recover *)
                  INC (yyErrorCount);
                  ErrorRecovery 
                    (yyTerminal, yyStateStack, yyStateStackSize, yyStackPtr);
                  yyIsRepairing := TRUE;
               END (* IF *) ;
            END (* IF *) ;
         END (* LOOP *) ;

         IF yyState >= yyFirstFinalState 
         THEN (* final state ? *)
            IF yyState <= yyLastReadTermState 
            THEN (* read terminal reduce ? *)
               INC (yyStackPtr);
            yyAttributeStack^ [yyStackPtr].Scan := Scanner.Attribute;
            yyTerminal := VAL(   Scanner.GetToken (),yySymbolType );
               yyIsRepairing := FALSE;
            END (* IF *) ;

            LOOP (* reduce *)
CASE yyState OF
  | 100=> (* _0000_ : input _EndOfFile .*)
  DynArray.ReleaseArray (yyStateStack, yyStateStackSize, BYTESIZE (yyTableElmt));
  DynArray.ReleaseArray (yyAttributeStack, yyAttrStackSize, BYTESIZE (tParsAttribute));
  RETURN yyErrorCount;

  | 101,99=> (* input : init name code define start rules .*)
  DEC (yyStackPtr, 6); yyNonterminal := 45;

  | 102=> (* init : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 39;
(* line 185 "/tmp/lalr4706" *)
  (* line 186 ../src/rex.lalr *)
   StartStateCount := 0;
                  RuleCount       := 0;
                  PatternCount    := 0;
                  LeftJustUsed    := FALSE;
                  EOLTree         := mCh (EolCh);
  
                  Strings.TextToString ("ANY", string);
                  MakeSet (set, ORD (LastCh));
                  Complement (set);
                  Exclude (set, ORD (EolCh));
                  MakeIdentDef (MakeIdent (string), LOOPHOLE (mSet (set),ADDRESS), 1, FALSE);
  
                  Strings.TextToString ("STD", string);
                  MakeStartDef (MakeIdent (string), StartStateCount + 1);
                  INC (StartStateCount, 2);                             
  | 103=> (* name : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 40;
(* line 203 "/tmp/lalr4706" *)
  (* line 202 ../src/rex.lalr *)
   ScannerName := NoIdent; 
  | 104=> (* name : 'SCANNER' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 40;
(* line 205 "/tmp/lalr4706" *)
  (* line 203 ../src/rex.lalr *)
   Strings.TextToString ("Scanner", string); ScannerName := MakeIdent (string); 
  | 105,56=> (* name : 'SCANNER' Ident .*)
  DEC (yyStackPtr, 2); yyNonterminal := 40;
(* line 207 "/tmp/lalr4706" *)
  (* line 204 ../src/rex.lalr *)
   ScannerName := yyAttributeStack^[yyStackPtr+2].Scan.Ident; 
  | 106=> (* code : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 41;

  | 107,74=> (* code : code 'EXPORT' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 211 "/tmp/lalr4706" *)
  (* line 207 ../src/rex.lalr *)
   Export  := yyAttributeStack^[yyStackPtr+3].Scan.Text; ExportLine      := yyAttributeStack^[yyStackPtr+3].Scan.Position.Line; 
  | 108,57=> (* code : code 'GLOBAL' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 213 "/tmp/lalr4706" *)
  (* line 208 ../src/rex.lalr *)
   Global  := yyAttributeStack^[yyStackPtr+3].Scan.Text; GlobalLine      := yyAttributeStack^[yyStackPtr+3].Scan.Position.Line; 
  | 109,73=> (* code : code 'LOCAL' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 215 "/tmp/lalr4706" *)
  (* line 209 ../src/rex.lalr *)
   Local   := yyAttributeStack^[yyStackPtr+3].Scan.Text; LocalLine       := yyAttributeStack^[yyStackPtr+3].Scan.Position.Line; 
  | 110,58=> (* code : code 'BEGIN' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 217 "/tmp/lalr4706" *)
  (* line 210 ../src/rex.lalr *)
   Begin   := yyAttributeStack^[yyStackPtr+3].Scan.Text; BeginLine       := yyAttributeStack^[yyStackPtr+3].Scan.Position.Line; 
  | 111,59=> (* code : code 'CLOSE' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 219 "/tmp/lalr4706" *)
  (* line 211 ../src/rex.lalr *)
   Close   := yyAttributeStack^[yyStackPtr+3].Scan.Text; CloseLine       := yyAttributeStack^[yyStackPtr+3].Scan.Position.Line; 
  | 112,76=> (* code : code DEFAULT TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 221 "/tmp/lalr4706" *)
  (* line 212 ../src/rex.lalr *)
   Default := yyAttributeStack^[yyStackPtr+3].Scan.Text; DefaultLine     := yyAttributeStack^[yyStackPtr+3].Scan.Position.Line; 
  | 113,75=> (* code : code EOF TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 223 "/tmp/lalr4706" *)
  (* line 213 ../src/rex.lalr *)
   Eof     := yyAttributeStack^[yyStackPtr+3].Scan.Text; EofLine         := yyAttributeStack^[yyStackPtr+3].Scan.Position.Line; 
  | 114=> (* define : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 42;
(* line 226 "/tmp/lalr4706" *)
  (* line 215 ../src/rex.lalr *)
   InitScanGen(); 
  | 115=> (* define : DEFINE definitionList .*)
  DEC (yyStackPtr, 2); yyNonterminal := 42;
(* line 228 "/tmp/lalr4706" *)
  (* line 216 ../src/rex.lalr *)
   InitScanGen(); 
  | 116=> (* start : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 43;

  | 117=> (* start : START identListDef .*)
  DEC (yyStackPtr, 2); yyNonterminal := 43;

  | 118=> (* rules : RULES ruleList .*)
  DEC (yyStackPtr, 2); yyNonterminal := 44;
(* line 235 "/tmp/lalr4706" *)
  (* line 222 ../src/rex.lalr *)
   Tree0Root := yyAttributeStack^[yyStackPtr+2].Tree;
                  Tree0Root := AppendRule (Tree0Root, BlankCh, BlankText);
                  Tree0Root := AppendRule (Tree0Root, TabCh  , TabText  );
                  Tree0Root := AppendRule (Tree0Root, EolCh  , EolText  );      
  | 119=> (* definitionList : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 46;

  | 120,88=> (* definitionList : definitionList definition .*)
  DEC (yyStackPtr, 2); yyNonterminal := 46;

  | 121=> (* ruleList : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 48;
(* line 245 "/tmp/lalr4706" *)
  (* line 231 ../src/rex.lalr *)
   yySynAttribute.Tree := nNode;                                        
  | 122,95=> (* ruleList : ruleList rule .*)
  DEC (yyStackPtr, 2); yyNonterminal := 48;
(* line 247 "/tmp/lalr4706" *)
  (* line 234 ../src/rex.lalr *)
   yySynAttribute.Tree := mList (yyAttributeStack^[yyStackPtr+1].Tree, yyAttributeStack^[yyStackPtr+2].Tree);                        
  | 123,91=> (* identListDef : IdentDef .*)
  DEC (yyStackPtr, 1); yyNonterminal := 47;

  | 124,90=> (* identListDef : identListDef IdentDef .*)
  DEC (yyStackPtr, 2); yyNonterminal := 47;

  | 125,89=> (* identListDef : identListDef ',' IdentDef .*)
  DEC (yyStackPtr, 3); yyNonterminal := 47;

  | 126,77=> (* IdentDef : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 51;
(* line 255 "/tmp/lalr4706" *)
  (* line 241 ../src/rex.lalr *)
   Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan.Ident);
                  IF Definition = NoDef THEN
                     MakeStartDef (yyAttributeStack^[yyStackPtr+1].Scan.Ident, StartStateCount + 1);
                     INC (StartStateCount, 2);
                  ELSE
                     GetString (yyAttributeStack^[yyStackPtr+1].Scan.Ident, string);
                     Errors.ErrorMessageI (IdentDefBefore, Error, yyAttributeStack^[yyStackPtr+1].Scan.Position,
                        String, ADR (string));
                  END;                                                  
  | 127,92=> (* identListUse : IdentUse .*)
  DEC (yyStackPtr, 1); yyNonterminal := 53;
(* line 268 "/tmp/lalr4706" *)
  (* line 252 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set, StartStateCount);
                  Include (yySynAttribute.Set, yyAttributeStack^[yyStackPtr+1].Scan.Number);
                  Include (yySynAttribute.Set, yyAttributeStack^[yyStackPtr+1].Scan.Number + 1);                    
  | 128,94=> (* identListUse : identListUse IdentUse .*)
  DEC (yyStackPtr, 2); yyNonterminal := 53;
(* line 274 "/tmp/lalr4706" *)
  (* line 257 ../src/rex.lalr *)
   yySynAttribute.Set := yyAttributeStack^[yyStackPtr+1].Set;
                  Include (yySynAttribute.Set, yyAttributeStack^[yyStackPtr+2].Scan.Number);
                  Include (yySynAttribute.Set, yyAttributeStack^[yyStackPtr+2].Scan.Number + 1);                    
  | 129,93=> (* identListUse : identListUse ',' IdentUse .*)
  DEC (yyStackPtr, 3); yyNonterminal := 53;
(* line 280 "/tmp/lalr4706" *)
  (* line 262 ../src/rex.lalr *)
   yySynAttribute.Set := yyAttributeStack^[yyStackPtr+1].Set;
                  Include (yySynAttribute.Set, yyAttributeStack^[yyStackPtr+3].Scan.Number);
                  Include (yySynAttribute.Set, yyAttributeStack^[yyStackPtr+3].Scan.Number + 1);                    
  | 130,78=> (* IdentUse : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 52;
(* line 287 "/tmp/lalr4706" *)
  (* line 267 ../src/rex.lalr *)
   yySynAttribute.Scan.Number := 0;
                  Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan.Ident);
                  IF Definition = NoDef THEN
                     GetString (yyAttributeStack^[yyStackPtr+1].Scan.Ident, string);
                     Errors.ErrorMessageI (IdentUndefined, Error, yyAttributeStack^[yyStackPtr+1].Scan.Position,
                        String, ADR (string));
                  ELSIF GetKind (Definition) # tKind.Start THEN
                     GetString (yyAttributeStack^[yyStackPtr+1].Scan.Ident, string);
                     Errors.ErrorMessageI (ImproperUse, Error, yyAttributeStack^[yyStackPtr+1].Scan.Position,
                        String, ADR (string));
                  ELSE
                     GetStartDef (Definition, Identifier, yySynAttribute.Scan.Number);
                  END;                                                  
  | 131,72=> (* definition : Ident '=' regExpr '.' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 49;
(* line 304 "/tmp/lalr4706" *)
  (* line 282 ../src/rex.lalr *)
   Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan.Ident);
                  IF Definition = NoDef THEN
                     MakeIdentDef (yyAttributeStack^[yyStackPtr+1].Scan.Ident, LOOPHOLE (yyAttributeStack^[yyStackPtr+3].Tree,ADDRESS), 0, FALSE);
                  ELSE
                     GetString (yyAttributeStack^[yyStackPtr+1].Scan.Ident, string);
                     Errors.ErrorMessageI (IdentDefBefore, Error, yyAttributeStack^[yyStackPtr+1].Scan.Position,
                        String, ADR (string));
                  END;                                                  
  | 132,83=> (* rule : patternList ':' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 50;
(* line 316 "/tmp/lalr4706" *)
  (* line 292 ../src/rex.lalr *)
   INC (RuleCount);
                  yySynAttribute.Tree := mRule (yyAttributeStack^[yyStackPtr+1].Tree, yyAttributeStack^[yyStackPtr+3].Scan.Text, yyAttributeStack^[yyStackPtr+3].Scan.Position.Line, Position, RuleCount); 
  | 133,84=> (* rule : patternList ':-' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 50;
(* line 321 "/tmp/lalr4706" *)
  (* line 295 ../src/rex.lalr *)
   INC (RuleCount);
                  yySynAttribute.Tree := mRule (yyAttributeStack^[yyStackPtr+1].Tree, yyAttributeStack^[yyStackPtr+3].Scan.Text, yyAttributeStack^[yyStackPtr+3].Scan.Position.Line, NoPosition, RuleCount); 
  | 134,98=> (* patternList : pattern .*)
  DEC (yyStackPtr, 1); yyNonterminal := 55;
(* line 326 "/tmp/lalr4706" *)
  (* line 299 ../src/rex.lalr *)
   yySynAttribute.Tree := mList (nNode, yyAttributeStack^[yyStackPtr+1].Tree);                        
  | 135,96=> (* patternList : patternList ',' pattern .*)
  DEC (yyStackPtr, 3); yyNonterminal := 55;
(* line 328 "/tmp/lalr4706" *)
  (* line 302 ../src/rex.lalr *)
   yySynAttribute.Tree := mList (yyAttributeStack^[yyStackPtr+1].Tree, yyAttributeStack^[yyStackPtr+3].Tree);                        
  | 136,97=> (* pattern : startStates leftJust regExpr rightContext rightJust .*)
  DEC (yyStackPtr, 5); yyNonterminal := 56;
(* line 332 "/tmp/lalr4706" *)
  (* line 305 ../src/rex.lalr *)
   IF yyAttributeStack^[yyStackPtr+4].Tree = nNode THEN
                     tree := yyAttributeStack^[yyStackPtr+5].Tree;
                  ELSE
                     IF yyAttributeStack^[yyStackPtr+5].Tree = nNode THEN
                        tree := yyAttributeStack^[yyStackPtr+4].Tree;
                     ELSE
                        tree := mSequence (yyAttributeStack^[yyStackPtr+4].Tree, yyAttributeStack^[yyStackPtr+5].Tree);
                     END;
                  END;
  
                  IF yyAttributeStack^[yyStackPtr+2].IsLeftJust THEN
                     Number := LOOPHOLE (StartStateCount,SHORTCARD);
                     FOR NumberF := 1 TO Number BY 2 DO
                        Exclude (yyAttributeStack^[yyStackPtr+1].Set, NumberF);
                     END;
                  END;
  
                  INC (PatternCount);
                  yySynAttribute.Tree := mPattern (yyAttributeStack^[yyStackPtr+1].Set, yyAttributeStack^[yyStackPtr+3].Tree, tree,
                     PatternCount, yyAttributeStack^[yyStackPtr+2].Position);                        
  | 137=> (* startStates : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 57;
(* line 355 "/tmp/lalr4706" *)
  (* line 326 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set, StartStateCount);
                  Complement (yySynAttribute.Set);
                  Exclude (yySynAttribute.Set, 0);                                     
  | 138,80=> (* startStates : '#' identListUse '#' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 57;
(* line 360 "/tmp/lalr4706" *)
  (* line 331 ../src/rex.lalr *)
   yySynAttribute.Set := yyAttributeStack^[yyStackPtr+2].Set;                                 
  | 139,79=> (* startStates : NOT '#' identListUse '#' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 57;
(* line 363 "/tmp/lalr4706" *)
  (* line 334 ../src/rex.lalr *)
   yySynAttribute.Set := yyAttributeStack^[yyStackPtr+3].Set;
                  Complement (yySynAttribute.Set);
                  Exclude (yySynAttribute.Set, 0);                                     
  | 140=> (* leftJust : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 58;
(* line 370 "/tmp/lalr4706" *)
  (* line 339 ../src/rex.lalr *)
   yySynAttribute.IsLeftJust := FALSE;
                  yySynAttribute.Position  := Scanner.Attribute.Position;          
  | 141,81=> (* leftJust : '<' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 58;
(* line 375 "/tmp/lalr4706" *)
  (* line 343 ../src/rex.lalr *)
   yySynAttribute.IsLeftJust := TRUE;
                  LeftJustUsed  := TRUE;
                  yySynAttribute.Position  := Scanner.Attribute.Position;          
  | 142=> (* rightContext : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 59;
(* line 381 "/tmp/lalr4706" *)
  (* line 348 ../src/rex.lalr *)
   yySynAttribute.Tree := nNode;                                        
  | 143=> (* rightContext : '/' regExpr .*)
  DEC (yyStackPtr, 2); yyNonterminal := 59;
(* line 383 "/tmp/lalr4706" *)
  (* line 351 ../src/rex.lalr *)
   yySynAttribute.Tree := yyAttributeStack^[yyStackPtr+2].Tree;                                 
  | 144=> (* rightJust : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 60;
(* line 386 "/tmp/lalr4706" *)
  (* line 354 ../src/rex.lalr *)
   yySynAttribute.Tree := nNode;                                        
  | 145,82=> (* rightJust : '>' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 60;
(* line 388 "/tmp/lalr4706" *)
  (* line 357 ../src/rex.lalr *)
   yySynAttribute.Tree := EOLTree;                                      
  | 146=> (* regExpr : regExpr '|' regExpr .*)
  DEC (yyStackPtr, 3); yyNonterminal := 54;
(* line 391 "/tmp/lalr4706" *)
  (* line 360 ../src/rex.lalr *)
   yySynAttribute.Tree := mAlternative (yyAttributeStack^[yyStackPtr+1].Tree, yyAttributeStack^[yyStackPtr+3].Tree);                
  | 147=> (* regExpr : regExpr regExpr .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 393 "/tmp/lalr4706" *)
  (* line 363 ../src/rex.lalr *)
   yySynAttribute.Tree := mSequence (yyAttributeStack^[yyStackPtr+1].Tree, yyAttributeStack^[yyStackPtr+2].Tree);                
  | 148,66=> (* regExpr : regExpr '+' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 395 "/tmp/lalr4706" *)
  (* line 367 ../src/rex.lalr *)
   yySynAttribute.Tree := mRepetition (yyAttributeStack^[yyStackPtr+1].Tree);                        
  | 149,67=> (* regExpr : regExpr '*' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 397 "/tmp/lalr4706" *)
  (* line 370 ../src/rex.lalr *)
   yySynAttribute.Tree := mOption (mRepetition (yyAttributeStack^[yyStackPtr+1].Tree));               
  | 150,68=> (* regExpr : regExpr '?' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 399 "/tmp/lalr4706" *)
  (* line 373 ../src/rex.lalr *)
   yySynAttribute.Tree := mOption (yyAttributeStack^[yyStackPtr+1].Tree);                                
  | 151,70=> (* regExpr : regExpr '[' Number ']' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 54;
(* line 402 "/tmp/lalr4706" *)
  (* line 376 ../src/rex.lalr *)
   yySynAttribute.Tree := nNode;
                  Number := yyAttributeStack^[yyStackPtr+3].Scan.Number ;
                  FOR NumberF := 1 TO Number DO
                     yySynAttribute.Tree := mSequence (yyAttributeStack^[yyStackPtr+1].Tree, yySynAttribute.Tree);
                  END;                                                  
  | 152,69=> (* regExpr : regExpr '[' Number '-' Number ']' .*)
  DEC (yyStackPtr, 6); yyNonterminal := 54;
(* line 409 "/tmp/lalr4706" *)
  (* line 382 ../src/rex.lalr *)
   yySynAttribute.Tree := nNode;
                  tree := mOption (yyAttributeStack^[yyStackPtr+1].Tree);

                  Number := yyAttributeStack^[yyStackPtr+5].Scan.Number;
                  FOR NumberF := yyAttributeStack^[yyStackPtr+3].Scan.Number + 1 TO Number DO
                     yySynAttribute.Tree := mSequence (tree, yySynAttribute.Tree);
                  END;


                  Number := yyAttributeStack^[yyStackPtr+3].Scan.Number ;
                  FOR NumberF := 1 TO Number DO
                     yySynAttribute.Tree := mSequence (yyAttributeStack^[yyStackPtr+1].Tree, yySynAttribute.Tree);
                  END;                                                  
  | 153,71=> (* regExpr : '(' regExpr ')' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 54;
(* line 419 "/tmp/lalr4706" *)
  (* line 392 ../src/rex.lalr *)
   yySynAttribute.Tree := yyAttributeStack^[yyStackPtr+2].Tree;                                 
  | 154,87=> (* regExpr : charSet .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 421 "/tmp/lalr4706" *)
  (* line 395 ../src/rex.lalr *)
   yySynAttribute.Tree := mSet (yyAttributeStack^[yyStackPtr+1].Set);                                
  | 155,63=> (* regExpr : Char .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 423 "/tmp/lalr4706" *)
  (* line 398 ../src/rex.lalr *)
   yySynAttribute.Tree := mCh (yyAttributeStack^[yyStackPtr+1].Scan.Ch);                                
  | 156,60=> (* regExpr : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 426 "/tmp/lalr4706" *)
  (* line 401 ../src/rex.lalr *)
   Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan.Ident);
                  IF Definition # NoDef THEN
                     IF GetKind (Definition) = tKind.Ident THEN
                        GetIdentDef (Definition, Identifier, tree1, Number, bool);
                        yySynAttribute.Tree := LOOPHOLE (tree1,ADDRESS);
                     ELSE
                        GetString (yyAttributeStack^[yyStackPtr+1].Scan.Ident, string);
                        Errors.ErrorMessageI (ImproperUse, Error, yyAttributeStack^[yyStackPtr+1].Scan.Position,
                           String, ADR (string));
                        yySynAttribute.Tree := nNode;
                     END;
                  ELSE
                     stringref := GetStringRef (yyAttributeStack^[yyStackPtr+1].Scan.Ident);
                     yySynAttribute.Tree := mString (stringref);
                  END;                                                  
  | 157,62=> (* regExpr : String .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 443 "/tmp/lalr4706" *)
  (* line 418 ../src/rex.lalr *)
   yySynAttribute.Tree := mString (yyAttributeStack^[yyStackPtr+1].Scan.String);                        
  | 158,61=> (* regExpr : Number .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 446 "/tmp/lalr4706" *)
  (* line 421 ../src/rex.lalr *)
   IntToString (yyAttributeStack^[yyStackPtr+1].Scan.Number, string);
                  yySynAttribute.Tree := mString (PutString (string));         
  | 159,86=> (* charSet : '-' charSet .*)
  DEC (yyStackPtr, 2); yyNonterminal := 61;
(* line 452 "/tmp/lalr4706" *)
  (* line 425 ../src/rex.lalr *)
   yySynAttribute.Set := yyAttributeStack^[yyStackPtr+2].Set;
                  Complement (yySynAttribute.Set);                                        
  | 160,65=> (* charSet : '{' rangeList '}' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 61;
(* line 456 "/tmp/lalr4706" *)
  (* line 429 ../src/rex.lalr *)
   yySynAttribute.Set := yyAttributeStack^[yyStackPtr+2].Set;                                 
  | 161=> (* rangeList : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 62;
(* line 459 "/tmp/lalr4706" *)
  (* line 432 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set, ORD (LastCh));                  
  | 162,85=> (* rangeList : rangeList range .*)
  DEC (yyStackPtr, 2); yyNonterminal := 62;
(* line 462 "/tmp/lalr4706" *)
  (* line 435 ../src/rex.lalr *)
   yySynAttribute.Set := yyAttributeStack^[yyStackPtr+1].Set;
                  Union (yySynAttribute.Set, yyAttributeStack^[yyStackPtr+2].Set);
                  ReleaseSet (yyAttributeStack^[yyStackPtr+2].Set);                                        
  | 163=> (* range : Char .*)
  DEC (yyStackPtr, 1); yyNonterminal := 63;
(* line 469 "/tmp/lalr4706" *)
  (* line 440 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set, ORD (LastCh));
                  Include (yySynAttribute.Set, ORD (yyAttributeStack^[yyStackPtr+1].Scan.Ch));                       
  | 164,64=> (* range : Char '-' Char .*)
  DEC (yyStackPtr, 3); yyNonterminal := 63;
(* line 474 "/tmp/lalr4706" *)
  (* line 444 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set, ORD (LastCh));
 
                  ch := yyAttributeStack^[yyStackPtr+3].Scan.Ch;
                  FOR chF := yyAttributeStack^[yyStackPtr+1].Scan.Ch            TO ch DO
                     Include (yySynAttribute.Set, ORD (chF));
                  END;                                                  
END;
              (* SPEC State 
                   := Next (Top (), Nonterminal); nonterminal transition *)
               yyNCombPtr 
                 := LOOPHOLE 
                      ( LOOPHOLE (yyNBasePtr [yyStateStack^ [yyStackPtr]],M2LONGCARD)
                        + (VAL (  yyNonterminal,M2LONGCARD )
                          * BYTESIZE (yyNCombType))
                      ,yyNCombTypePtr);
               yyState := yyNCombPtr^;
               INC (yyStackPtr);
               yyAttributeStack^ [yyStackPtr] := yySynAttribute;
               IF yyState < yyFirstFinalState 
               THEN (* read nonterminal ? *)
                 EXIT 
               END (* IF *) ; 
            END (* LOOP *) ;

         ELSE (* read *)
            INC (yyStackPtr);
         yyAttributeStack^ [yyStackPtr].Scan := Scanner.Attribute;
         yyTerminal := VAL(Scanner.GetToken (),yySymbolType);
            yyIsRepairing := FALSE;
         END (* IF *);
      END (* LOOP *) ;
   END Parser;

PROCEDURE ErrorRecovery (
      VAR Terminal      : yySymbolType ;
          StateStack    : yyStackType   ;
          StackSize     : M2LONGINT       ;
          StackPtr      : yyStackPtrType) =
   VAR
      TokensSkipped     : BOOLEAN;
      ContinueSet       : Sets.tSet;
      RestartSet        : Sets.tSet;
      TokenArray        : ARRAY [0..127] OF CHAR;
      TokenString       : Strings.tString;
      ContinueString    : Strings.tString;
   BEGIN
   (* 1. report the error *)
         TokenName ( Terminal , TokenArray );
         Strings.ArrayToString (TokenArray, TokenString);
         Errors.ErrorMessageI (Errors.SyntaxError, Errors.Error, 
         Scanner.Attribute.Position, Errors.String, ADR(TokenString) );

   (* 2. report the set of expected terminal symbols *)
      Sets.MakeSet (ContinueSet, yyLastTerminal);
      ComputeContinuation (StateStack, StackSize, StackPtr, ContinueSet);
      Strings.AssignEmpty (ContinueString);
      FOR TokenF := VAL(Sets.Minimum (ContinueSet),yySymbolType) TO VAL(Sets.Maximum (ContinueSet),yySymbolType) DO
         IF Sets.IsElement (VAL(TokenF,Sets.tElement), ContinueSet) THEN
            TokenName (TokenF, TokenArray);
            Strings.ArrayToString (TokenArray, TokenString);
            IF ((Strings.Length (ContinueString) + Strings.Length (TokenString) + 1) <= Strings.cMaxStrLength) THEN
               Strings.Concatenate (ContinueString, TokenString);
               Strings.Append (ContinueString, ' ');
            END;
         END;
      END;
      Errors.ErrorMessageI (Errors.ExpectedTokens, Errors.Information,
      Scanner.Attribute.Position, Errors.String, ADR (ContinueString));
      Sets.ReleaseSet (ContinueSet);

   (* 3. compute the set of terminal symbols for restart of the parse *)
      Sets.MakeSet (RestartSet, yyLastTerminal);
      ComputeRestartPoints (StateStack, StackSize, StackPtr, RestartSet);

   (* 4. skip terminal symbols until a restart point is reached *)
      TokensSkipped := FALSE;
      WHILE NOT Sets.IsElement (VAL(Terminal,Sets.tElement), RestartSet) DO
      Terminal := VAL(Scanner.GetToken (),yySymbolType);
         TokensSkipped := TRUE;
      END;
      Sets.ReleaseSet (RestartSet);

   (* 5. report the restart point *)
      IF TokensSkipped THEN
      Errors.ErrorMessage (Errors.RestartPoint, Errors.Information, Scanner.Attribute.Position);
      END;
   END ErrorRecovery;

(*
   compute the set of terminal symbols that can be accepted (read)
   in a given stack configuration (eventually after reduce actions)
*)

PROCEDURE ComputeContinuation (
          Stack         : yyStackType   ;
          StackSize     : M2LONGINT       ;
          StackPtr      : yyStackPtrType;
      VAR ContinueSet   : Sets.tSet     ) =
   BEGIN
      Sets.AssignEmpty (ContinueSet);
      FOR TerminalF := yyFirstTerminal TO yyLastTerminal DO
         IF IsContinuation (TerminalF, Stack, StackSize, StackPtr) THEN
            Sets.Include (ContinueSet, VAL(TerminalF,Sets.tElement));
         END;
      END;
   END ComputeContinuation;

(*
   check whether a given terminal symbol can be accepted (read)
   in a certain stack configuration (eventually after reduce actions)
*)

PROCEDURE IsContinuation (
      Terminal          : yySymbolType ;
      ParseStack        : yyStackType   ;
      StackSize         : M2LONGINT       ;
      StackPtr          : yyStackPtrType): BOOLEAN =
   VAR
      State             : yyStackPtrType;
      Nonterminal       : yySymbolType;
      Stack             : yyStackType;
   BEGIN
      DynArray.MakeArray (LOOPHOLE(Stack,ADDRESS), StackSize, BYTESIZE (yyStateRange));
      FOR StateF := 0 TO StackPtr DO
         Stack^ [StateF] := ParseStack^ [StateF];
      END;
      State := Stack^ [StackPtr];

IF Terminal = 12 AND State = 26 THEN
  State := 26
END;

      LOOP
         Stack^ [StackPtr] := State;
         State := Next (State, Terminal);
         IF State = yyNoState THEN
            DynArray.ReleaseArray (Stack, StackSize, BYTESIZE (yyStateRange));
            RETURN FALSE;
         END;
         IF State <= yyLastReadTermState THEN           (* read or read terminal reduce ? *)
            DynArray.ReleaseArray (Stack, StackSize, BYTESIZE (yyStateRange));
            RETURN TRUE;
         END;

         LOOP                                           (* reduce *)
            IF State =  yyStopState THEN
               DynArray.ReleaseArray (Stack, StackSize, BYTESIZE (yyStateRange));
               RETURN TRUE;
            ELSE 
               DEC (StackPtr, yyLength [State]);
               Nonterminal := yyLeftHandSide [State];
            END;

            State := Next (Stack^ [StackPtr], Nonterminal);
            IF StackPtr >= VAL (   StackSize,yyStackPtrType ) THEN
               DynArray.ExtendArray (LOOPHOLE(Stack,ADDRESS), StackSize, BYTESIZE (yyStateRange));
            END;
            INC (StackPtr);
            IF State < yyFirstFinalState THEN EXIT; END; (* read nonterminal ? *)
            State := yyFinalToProd [State];             (* read nonterminal reduce *)
         END;
      END;
   END IsContinuation;

(*
   compute a set of terminal symbols that can be used to restart
   parsing in a given stack configuration. we simulate parsing until
   end of file using a suffix program synthesized by the function
   Continuation. All symbols acceptable in the states reached during
   the simulation can be used to restart parsing.
*)

PROCEDURE ComputeRestartPoints (
          ParseStack    : yyStackType   ;
          StackSize     : M2LONGINT       ;
          StackPtr      : yyStackPtrType;
      VAR RestartSet    : Sets.tSet     ) =
   VAR
      Stack             : yyStackType;
      State             : yyStackPtrType;
      Nonterminal       : yySymbolType;
      ContinueSet       : Sets.tSet;
   BEGIN
      DynArray.MakeArray (LOOPHOLE(Stack,ADDRESS), StackSize, BYTESIZE (yyStateRange));
      FOR StateF := 0 TO StackPtr DO
         Stack^ [StateF] := ParseStack^ [StateF];
      END;
      Sets.MakeSet (ContinueSet, yyLastTerminal);
      Sets.AssignEmpty (RestartSet);
      State := Stack^ [StackPtr];

      LOOP
         IF StackPtr >= VAL (   StackSize,yyStackPtrType ) THEN
            DynArray.ExtendArray (LOOPHOLE(Stack,ADDRESS), StackSize, BYTESIZE (yyStateRange));
         END;
         Stack^ [StackPtr] := State;
         ComputeContinuation (Stack, StackSize, StackPtr, ContinueSet);
         Sets.Union (RestartSet, ContinueSet);
         State := Next (State, yyContinuation [State]);

         IF State >= yyFirstFinalState THEN             (* final state ? *)
            IF State <= yyLastReadTermState THEN        (* read terminal reduce ? *)
               INC (StackPtr);
               State := yyFinalToProd [State];
            END;

            LOOP                                        (* reduce *)
               IF State = yyStopState THEN
                  DynArray.ReleaseArray (Stack, StackSize, BYTESIZE (yyStateRange));
                  Sets.ReleaseSet (ContinueSet);
                  RETURN;
               ELSE 
                  DEC (StackPtr, yyLength [State]);
                  Nonterminal := yyLeftHandSide [State];
               END;

               State := Next (Stack^ [StackPtr], Nonterminal);
               INC (StackPtr);
               IF State < yyFirstFinalState THEN EXIT; END; (* read nonterminal ? *)
               State := yyFinalToProd [State];          (* read nonterminal reduce *)
            END;
         ELSE                                           (* read *)
            INC (StackPtr);
         END;
      END;
   END ComputeRestartPoints;

(* access the parse table:   Next : State x Symbol -> State *)

PROCEDURE Next (State: yyStateType; Symbol: yySymbolType): yyStateRange =
   VAR
      TCombPtr          : yyTCombTypePtr;
      NCombPtr          : yyNCombTypePtr;
   BEGIN
      IF Symbol <= yyLastTerminal THEN
         LOOP
            TCombPtr 
              := LOOPHOLE 
                   ( LOOPHOLE (yyTBasePtr [State],M2LONGCARD) 
                     + (VAL (   Symbol,M2LONGCARD )
                       * BYTESIZE (yyTCombType))
                   ,yyTCombTypePtr);
(* FIXME: Once got here with State = 0, yyNBasePtr[0]=NIL, tCombPtr
          =16_30, segfaulting its deref below. *)
            IF TCombPtr^.Check # State THEN
               State := yyDefault [State];
               IF State = yyNoState THEN RETURN yyNoState; END;
            ELSE
               RETURN TCombPtr^.Next;
            END;
         END;
      ELSE
        NCombPtr 
          := LOOPHOLE 
               ( LOOPHOLE (yyNBasePtr [State],M2LONGCARD)
                 + (VAL (   Symbol,M2LONGCARD )
                   * BYTESIZE (yyNCombType))
               ,yyNCombTypePtr);
        RETURN NCombPtr^;
      END;
   END Next;

PROCEDURE yyGetTables() =
   VAR
      BlockSize, j, n   : Word.T;
      ReadVal: INTEGER;
      OK: BOOLEAN;
      TBase     : ARRAY (*yyTableElmt*)[0 .. yyLastReadState] OF yyTCombRange;
      NBase     : ARRAY (*yyTableElmt*)[0 .. yyLastReadState] OF yyNCombRange;
   BEGIN
      BlockSize := 64000 DIV BYTESIZE (yyTCombType);
      OK := TRUE;
      TRY
        yyTableFile := System.OpenInputT (ParsTabName);
      EXCEPT
        OSError.E (code)
        => Errors.ErrLine
             ("Error: Can't open parse table file " & ParsTabName); 
        OK := FALSE;
      END;
      IF OK THEN
        ReadVal := yyGetTable (ADR (TBase[FIRST(TBase)])) DIV BYTESIZE (yyTCombRange ) - 1;
        IF ReadVal # yyLastReadState THEN
           Errors.ErrLine
             ("Error reading " & ParsTabName & ", TBase size = " & Fmt.Int (ReadVal) & ", expected "
              & Fmt.Int (yyLastReadState) );
           OK := FALSE;
        ELSE
          ReadVal := yyGetTable (ADR (NBase[FIRST(NBase)])) DIV BYTESIZE (yyNCombRange ) - 1;
          IF ReadVal # yyLastReadState THEN
             Errors.ErrLine
               ("Error reading " & ParsTabName & ", NBase size = " & Fmt.Int (ReadVal) & ", expected "
                & Fmt.Int (yyLastReadState) );
             OK := FALSE;
          ELSE
            ReadVal := yyGetTable (ADR (yyDefault[FIRST(yyDefault)])) DIV BYTESIZE (yyReadRange) - 1;
            IF ReadVal # yyLastReadState THEN
               Errors.ErrLine
                 ("Error reading " & ParsTabName & ", yyDefault size = " & Fmt.Int (ReadVal) & ", expected "
                  & Fmt.Int (yyLastReadState) );
               OK := FALSE;
            ELSE
              ReadVal := yyGetTable (ADR (yyNComb[FIRST(yyNComb)])) DIV BYTESIZE (yyNCombType);
              IF ReadVal # (yyNTableMax - yyLastTerminal) THEN
                 Errors.ErrLine
                   ("Error reading " & ParsTabName & ", yyNComb size = " & Fmt.Int (ReadVal) & ", expected "
                    & Fmt.Int (yyNTableMax - yyLastTerminal) );
                 OK := FALSE;
              ELSE
                ReadVal := yyGetTable (ADR (yyLength[FIRST(yyLength)])) DIV BYTESIZE (yyTableElmt  ) - 1;
                IF ReadVal # (yyLastReduceState - yyFirstReduceState) THEN
                   Errors.ErrLine
                     ("Error reading " & ParsTabName & ", yylength size = " & Fmt.Int (ReadVal) & ", expected "
                      & Fmt.Int (yyLastReduceState - yyFirstReduceState) );
                   OK := FALSE;
                ELSE
                  ReadVal := yyGetTable (ADR (yyLeftHandSide[FIRST(yyLeftHandSide)])) DIV BYTESIZE (yySymbolRange) - 1;
                  IF ReadVal # (yyLastReduceState - yyFirstReduceState) THEN
                     Errors.ErrLine
                       ("Error reading " & ParsTabName & ", yy LeftHandSide size= " & Fmt.Int (ReadVal) & ", expected "
                        & Fmt.Int (yyLastReduceState - yyFirstReduceState) );
                     OK := FALSE;
                  ELSE
                    ReadVal := yyGetTable (ADR (yyContinuation[FIRST(yyContinuation)])) DIV BYTESIZE (yySymbolRange) - 1;
                    IF ReadVal # yyLastReadState THEN
                       Errors.ErrLine
                         ("Error reading " & ParsTabName & ", yyContinuation size= " & Fmt.Int (ReadVal) & ", expected "
                          & Fmt.Int (yyLastReadState) );
                       OK := FALSE;
                    ELSE
                      ReadVal := yyGetTable (ADR (yyFinalToProd[FIRST(yyFinalToProd)] )) DIV BYTESIZE (yyReduceRange) - 1;
                      IF ReadVal # (yyLastReadNontermState - yyFirstReadTermState)
                      THEN
                         Errors.ErrLine
                           ("Error reading " & ParsTabName & ", yyFinalToProd size = " & Fmt.Int (ReadVal) & ", expected "
                            & Fmt.Int (yyLastReadNontermState - yyFirstReadTermState) );
                         OK := FALSE;
                      END;
                    END;
                  END;
                END;
              END;
            END;
          END;
        END;
      END;
      IF NOT OK THEN
        Errors.ErrorMessage 
        (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition);
        Process.Exit (Errors.AbnormalTermination);
      END;
      n := 0;
      j := 0;
      WHILE j <= yyTableMax DO
         INC (n, yyGetTable (ADR (yyTComb [VAL(j,yyStateRange)])) DIV BYTESIZE (yyTCombType));
         INC (j, BlockSize);
      END;
      IF n # (yyTableMax + 1) THEN 
         Errors.ErrorMessage (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition);
      END;
      System.Close (yyTableFile);

      FOR StateF := 1 TO yyLastReadState DO
         yyTBasePtr [StateF] := ADR (yyTComb [TBase [StateF]]);
      END;
      FOR StateF := 1 TO yyLastReadState DO
         yyNBasePtr [StateF] := ADR (yyNComb [NBase [StateF]]);
      END;
   END yyGetTables;

PROCEDURE yyGetTable (Address: ADDRESS): Word.T =
   VAR
      N         : INTEGER;
      Length    : yyTableElmt;
      LongLength : Word.T;
   BEGIN
      N := System.Read (yyTableFile, ADR (Length), BYTESIZE (yyTableElmt));
      yyErrorCheck (Errors.ReadParseTable, N);
      LongLength := Length;
      N := System.Read (yyTableFile, Address, LongLength);
      yyErrorCheck (Errors.ReadParseTable, N);
      RETURN LongLength;
   END yyGetTable;

PROCEDURE yyErrorCheck (ErrorCode: INTEGER; Info: INTEGER) =
   VAR ErrNo: INTEGER;
   BEGIN
     IF Info < 0 THEN
        ErrNo := System.ErrNum ();
        Errors.ErrorMessageI (ErrorCode, Errors.Fatal, Positions.NoPosition,
           Errors.Integer, ADR (ErrNo));
     END;
   END yyErrorCheck;

PROCEDURE BeginParser() =
   BEGIN
(* line 131 "/tmp/lalr4706" *)
(* line 131 ../src/rex.lalr *)
 nNode := mNode (); 
      IF NOT yyIsInitialized THEN
         yyIsInitialized := TRUE;
         yyGetTables();
      END;
   END BeginParser;

PROCEDURE CloseParser() =
   BEGIN

   END CloseParser;

PROCEDURE TextToRefArray ( textVal: TEXT): REF ARRAY OF CHAR =
  VAR length: INTEGER;
  VAR lRef: REF ARRAY OF CHAR;
  BEGIN
    IF textVal = NIL THEN textVal := "" END;
    length := Text.Length (textVal); 
    lRef := NEW (REF ARRAY OF CHAR, length + 1);
    Text.SetChars (lRef^, textVal);
    lRef^[length] := '\000';
    RETURN lRef;
  END  TextToRefArray;

BEGIN
    yyIsInitialized := FALSE;
    ParsTabName := "Parser.Tab";
END Parser.

