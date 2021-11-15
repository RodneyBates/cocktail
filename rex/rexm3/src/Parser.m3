(* $Id: Parser.mi,v 2.8 1992/08/12 06:54:05 grosch rel $ *)
(* Skeleton parser for Cocktail lalr. *)
(* Modified Rodney M. Bates. Various times. *)

 UNSAFE MODULE Parser;

FROM SYSTEM IMPORT M2LONGINT, M2LONGCARD, SHORTCARD;
IMPORT Word, SYSTEM, Scanner, Positions, Strings, DynArray, Sets, System;

(* line 24 "/tmp/lalr4706" *)
(* line 26 ../src/rex.lalr *)



IMPORT RexErrors AS Errors;

FROM Tree0	IMPORT
   tTree0	, Tree0Root	,
   mNode	, mRule		, mPattern	,
   mCh		, mSet		, mString	, mList		,
   mAlternative	, mSequence	, mRepetition	, mOption	;

FROM Tree	IMPORT
   tTree	;

FROM Sets	IMPORT
   tSet		, MakeSet	, ReleaseSet	,
   Union		, Include	, Exclude	,
   Complement	;

FROM Strings	IMPORT
   tString	, ArrayToString	, IntToString	;

FROM Lists	IMPORT
   tList	;

FROM StringMem	IMPORT
   tStringRef	, PutString	;

FROM Idents	IMPORT
   tIdent	, MakeIdent	, GetString	, GetStringRef	, NoIdent	;

FROM DefTable	IMPORT
   NoDef	, DefRange	, tKind		, GetKind	,
   MakeIdentDef	, MakeStartDef	, GetDef	, GetIdentDef	,
   GetStartDef	;

FROM GenTabs	IMPORT
   StartStateCount, RuleCount	, PatternCount	, LeftJustUsed	;

FROM Dfa	IMPORT
   BlankCh	, TabCh		, EolCh		, LastCh	;

FROM ScanGen	IMPORT
   Export	, Global	, Local		, Begin		,
   Close	, Eof		, Position	, NoPosition	,
   ExportLine	, GlobalLine	, LocalLine	, BeginLine	,
   CloseLine	, EofLine	, DefaultLine	, Default	,
   BlankText	, TabText	, EolText	,
   ScannerName	, InitScanGen	;

CONST
   IdentUndefined	= 10	;
   ImproperUse		= 11	;
   IdentDefBefore	= 12	;
   Error		= 3	;
   String		= 7	;

TYPE
   tParsAttribute = RECORD
       
        Scan		: Scanner.tScanAttribute;
        Tree		: tTree0	;
        IsLeftJust	: BOOLEAN	;
	   Position	: Positions.tPosition;
        Set		: tSet		;
      
   END;

VAR
   Number	: SHORTCARD	;
   bool		: BOOLEAN	;
   string	: tString	;
   stringref	: tStringRef	;
   set		: tSet		;
   tree		: tTree0	;
   tree1	: tTree		;
   Definition	: DefRange	;
   Identifier	: tIdent	;
   nNode	,
   EOLTree	: tTree0	;

PROCEDURE AppendRule (Tree: tTree0; Ch: CHAR; Text: tList): tTree0 =
   VAR
      Set	: tSet	;
      t		: tTree0;
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

   yyFirstTerminal		= 0;
   yyLastTerminal		= 38;
   yyFirstSymbol		= 0;
   yyLastSymbol		= 64;
   yyTableMax		= 221;
   yyNTableMax		= 89;
   yyFirstReadState		= 1;
   yyLastReadState		= 55;
   yyFirstReadTermState		= 56;
   yyLastReadTermState		= 84;
   yyLastReadNontermState		= 99;
   yyFirstReduceState		= 100;
   yyLastReduceState		= 164;
   yyStartState		= 1;
   yyStopState		= 100;

   yyFirstFinalState    = yyFirstReadTermState;
   yyLastState          = yyLastReduceState;

TYPE
   yyTableElmt          = SHORTCARD;
   yyTCombRange         = (*yyTableElmt*) [0 .. yyTableMax];
   yyNCombRange         = (*yyTableElmt*) [yyLastTerminal + 1 .. yyNTableMax];
   yyStateRange         = (*yyTableElmt*) [0 .. yyLastState];
   yyReadRange          = (*yyTableElmt*) [yyFirstReadState .. yyLastReadState];
   yyReadReduceRange    = (*yyTableElmt*) 
                            [yyFirstReadTermState ..yyLastReadNontermState];
   yyReduceRange        = (*yyTableElmt*) [yyFirstReduceState .. yyLastReduceState];
   yySymbolRange        = (*yyTableElmt*) [yyFirstSymbol .. yyLastSymbol];
   yyTCombType          = RECORD Check, Next: yyStateRange; END;
   yyNCombType          = yyStateRange;
   yyTCombTypePtr       = UNTRACED BRANDED REF  yyTCombType;
   yyNCombTypePtr       = UNTRACED BRANDED REF  yyNCombType;
   yyStackPtrType       = (*yyTableElmt*) [ FIRST(yyTableElmt) .. LAST (yyTableElmt) ];
   yyStackType          = UNTRACED BRANDED REF  ARRAY yyStackPtrType OF yyStateRange;
   yyAttributeStackType = UNTRACED BRANDED REF  ARRAY yyStackPtrType OF tParsAttribute;

VAR
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
      | 0=> CopyA (ARRAY [0..10] OF CHAR{'_','E','n','d','O','f','F','i','l','e','\000'}, Name);
      | 1=> CopyA (ARRAY [0..5] OF CHAR{'I','d','e','n','t','\000'}, Name);
      | 2=> CopyA (ARRAY [0..6] OF CHAR{'N','u','m','b','e','r','\000'}, Name);
      | 3=> CopyA (ARRAY [0..6] OF CHAR{'S','t','r','i','n','g','\000'}, Name);
      | 4=> CopyA (ARRAY [0..4] OF CHAR{'C','h','a','r','\000'}, Name);
      | 5=> CopyA (ARRAY [0..10] OF CHAR{'T','a','r','g','e','t','C','o','d','e','\000'}, Name);
      | 6=> CopyA (ARRAY [0..6] OF CHAR{'G','L','O','B','A','L','\000'}, Name);
      | 7=> CopyA (ARRAY [0..5] OF CHAR{'B','E','G','I','N','\000'}, Name);
      | 8=> CopyA (ARRAY [0..5] OF CHAR{'C','L','O','S','E','\000'}, Name);
      | 9=> CopyA (ARRAY [0..6] OF CHAR{'D','E','F','I','N','E','\000'}, Name);
      | 10=> CopyA (ARRAY [0..5] OF CHAR{'S','T','A','R','T','\000'}, Name);
      | 11=> CopyA (ARRAY [0..5] OF CHAR{'R','U','L','E','S','\000'}, Name);
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
      | 30=> CopyA (ARRAY [0..3] OF CHAR{'N','O','T','\000'}, Name);
      | 31=> CopyA (ARRAY [0..5] OF CHAR{'L','O','C','A','L','\000'}, Name);
      | 32=> CopyA (ARRAY [0..6] OF CHAR{'E','X','P','O','R','T','\000'}, Name);
      | 33=> Copy ('#', Name);
      | 34=> CopyA (ARRAY [0..3] OF CHAR{'E','O','F','\000'}, Name);
      | 35=> CopyA (ARRAY [0..2] OF CHAR{':','-','\000'}, Name);
      | 36=> CopyA (ARRAY [0..7] OF CHAR{'D','E','F','A','U','L','T','\000'}, Name);
      | 37=> CopyA (ARRAY [0..7] OF CHAR{'S','C','A','N','N','E','R','\000'}, Name);
      | 38=> CopyA (ARRAY [0..8] OF CHAR{'S','E','Q','U','E','N','C','E','\000'}, Name);
      END;
   END TokenName;

PROCEDURE Parser (): Word.T =

   VAR
      yyState           : yyStateRange;
      yyTerminal        : yySymbolRange;
      yyNonterminal     : yySymbolRange;        (* left-hand side symbol *)
      yyStackPtr        : yyStackPtrType;
      yyStateStackSize  : M2LONGINT;
      yyAttrStackSize   : M2LONGINT;
      yyShortStackSize  : yyStackPtrType;
      yyStateStack      : yyStackType;
      yyAttributeStack  : yyAttributeStackType;
      yySynAttribute    : tParsAttribute;       (* synthesized attribute *)
   yyRepairAttribute : Scanner.tScanAttribute;
      yyRepairToken     : yySymbolRange;
      yyTCombPtr        : yyTCombTypePtr;
      yyNCombPtr        : yyNCombTypePtr;
      yyIsRepairing     : BOOLEAN;
      yyErrorCount      : Word.T;
      yyTokenString     : ARRAY [0..127] OF CHAR;
   BEGIN
   BeginParser();
      yyState           := yyStartState;
   yyTerminal        := VAL ( Scanner.GetToken (),yySymbolRange);
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
                     yyAttributeStack^ [yyStackPtr].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 309
 $$ *) := yyRepairAttribute;
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
            yyAttributeStack^ [yyStackPtr].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 330
 $$ *) := Scanner.Attribute;
            yyTerminal := VAL(   Scanner.GetToken (),yySymbolRange );
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
  		  RuleCount	  := 0;
  		  PatternCount	  := 0;
  		  LeftJustUsed	  := FALSE;
  		  EOLTree	  := mCh (EolCh);
  
  		  ArrayToString (ARRAY [0..3] OF CHAR{'A','N','Y','\000'}, string);
  		  MakeSet (set, ORD (LastCh));
  		  Complement (set);
  		  Exclude (set, ORD (EolCh));
  		  MakeIdentDef (MakeIdent (string), LOOPHOLE (mSet (set),ADDRESS), 1, FALSE);
  
  		  ArrayToString (ARRAY [0..3] OF CHAR{'S','T','D','\000'}, string);
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
   ArrayToString (ARRAY [0..7] OF CHAR{'S','c','a','n','n','e','r','\000'}, string); ScannerName := MakeIdent (string); 
  | 105,56=> (* name : 'SCANNER' Ident .*)
  DEC (yyStackPtr, 2); yyNonterminal := 40;
(* line 207 "/tmp/lalr4706" *)
  (* line 204 ../src/rex.lalr *)
   ScannerName := yyAttributeStack^[yyStackPtr+2].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 378
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 378
 $$ *); 
  | 106=> (* code : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 41;

  | 107,74=> (* code : code 'EXPORT' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 211 "/tmp/lalr4706" *)
  (* line 207 ../src/rex.lalr *)
   Export  := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 386
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 386
 $$ *);	ExportLine	:= yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 386
 $$ *).Position.Line; 
  | 108,57=> (* code : code 'GLOBAL' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 213 "/tmp/lalr4706" *)
  (* line 208 ../src/rex.lalr *)
   Global  := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 391
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 391
 $$ *);	GlobalLine	:= yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 391
 $$ *).Position.Line; 
  | 109,73=> (* code : code 'LOCAL' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 215 "/tmp/lalr4706" *)
  (* line 209 ../src/rex.lalr *)
   Local   := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 396
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 396
 $$ *);	LocalLine	:= yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 396
 $$ *).Position.Line; 
  | 110,58=> (* code : code 'BEGIN' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 217 "/tmp/lalr4706" *)
  (* line 210 ../src/rex.lalr *)
   Begin   := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 401
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 401
 $$ *);	BeginLine	:= yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 401
 $$ *).Position.Line; 
  | 111,59=> (* code : code 'CLOSE' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 219 "/tmp/lalr4706" *)
  (* line 211 ../src/rex.lalr *)
   Close   := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 406
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 406
 $$ *);	CloseLine	:= yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 406
 $$ *).Position.Line; 
  | 112,76=> (* code : code DEFAULT TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 221 "/tmp/lalr4706" *)
  (* line 212 ../src/rex.lalr *)
   Default := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 411
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 411
 $$ *);	DefaultLine	:= yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 411
 $$ *).Position.Line; 
  | 113,75=> (* code : code EOF TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 41;
(* line 223 "/tmp/lalr4706" *)
  (* line 213 ../src/rex.lalr *)
   Eof     := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 416
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 416
 $$ *);	EofLine		:= yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 416
 $$ *).Position.Line; 
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
   Tree0Root := yyAttributeStack^[yyStackPtr+2].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 437
 $$ *);
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
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 451
 $$ *) := nNode;					
  | 122,95=> (* ruleList : ruleList rule .*)
  DEC (yyStackPtr, 2); yyNonterminal := 48;
(* line 247 "/tmp/lalr4706" *)
  (* line 234 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 456
 $$ *) := mList (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 456
 $$ *), yyAttributeStack^[yyStackPtr+2].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 456
 $$ *));			
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
   Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 470
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 470
 $$ *));
  		  IF Definition = NoDef THEN
  		     MakeStartDef (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 472
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 472
 $$ *), StartStateCount + 1);
  		     INC (StartStateCount, 2);
  		  ELSE
  		     GetString (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 475
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 475
 $$ *), string);
  		     Errors.ErrorMessageI (IdentDefBefore, Error, yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 476
 $$ *).Position,
  			String, ADR (string));
  		  END;							
  | 127,92=> (* identListUse : IdentUse .*)
  DEC (yyStackPtr, 1); yyNonterminal := 53;
(* line 268 "/tmp/lalr4706" *)
  (* line 252 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 483
 $$ *), StartStateCount);
  		  Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 484
 $$ *), yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 484
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 484
 $$ *));
  		  Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 485
 $$ *), yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 485
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 485
 $$ *) + 1);			
  | 128,94=> (* identListUse : identListUse IdentUse .*)
  DEC (yyStackPtr, 2); yyNonterminal := 53;
(* line 274 "/tmp/lalr4706" *)
  (* line 257 ../src/rex.lalr *)
   yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 490
 $$ *) := yyAttributeStack^[yyStackPtr+1].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 490
 $$ *);
  		  Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 491
 $$ *), yyAttributeStack^[yyStackPtr+2].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 491
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 491
 $$ *));
  		  Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 492
 $$ *), yyAttributeStack^[yyStackPtr+2].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 492
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 492
 $$ *) + 1);			
  | 129,93=> (* identListUse : identListUse ',' IdentUse .*)
  DEC (yyStackPtr, 3); yyNonterminal := 53;
(* line 280 "/tmp/lalr4706" *)
  (* line 262 ../src/rex.lalr *)
   yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 497
 $$ *) := yyAttributeStack^[yyStackPtr+1].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 497
 $$ *);
  		  Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 498
 $$ *), yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 498
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 498
 $$ *));
  		  Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 499
 $$ *), yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 499
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 499
 $$ *) + 1);			
  | 130,78=> (* IdentUse : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 52;
(* line 287 "/tmp/lalr4706" *)
  (* line 267 ../src/rex.lalr *)
   yySynAttribute.Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 504
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 504
 $$ *) := 0;
  		  Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 505
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 505
 $$ *));
  		  IF Definition = NoDef THEN
  		     GetString (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 507
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 507
 $$ *), string);
  		     Errors.ErrorMessageI (IdentUndefined, Error, yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 508
 $$ *).Position,
  			String, ADR (string));
  		  ELSIF GetKind (Definition) # tKind.Start THEN
  		     GetString (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 511
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 511
 $$ *), string);
  		     Errors.ErrorMessageI (ImproperUse, Error, yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 512
 $$ *).Position,
  			String, ADR (string));
  		  ELSE
  		     GetStartDef (Definition, Identifier, yySynAttribute.Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 515
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 515
 $$ *));
  		  END;							
  | 131,72=> (* definition : Ident '=' regExpr '.' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 49;
(* line 304 "/tmp/lalr4706" *)
  (* line 282 ../src/rex.lalr *)
   Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 521
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 521
 $$ *));
  		  IF Definition = NoDef THEN
  		     MakeIdentDef (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 523
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 523
 $$ *), LOOPHOLE (yyAttributeStack^[yyStackPtr+3].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 523
 $$ *),ADDRESS), 0, FALSE);
  		  ELSE
  		     GetString (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 525
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 525
 $$ *), string);
  		     Errors.ErrorMessageI (IdentDefBefore, Error, yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 526
 $$ *).Position,
  			String, ADR (string));
  		  END;							
  | 132,83=> (* rule : patternList ':' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 50;
(* line 316 "/tmp/lalr4706" *)
  (* line 292 ../src/rex.lalr *)
   INC (RuleCount);
  		  yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 534
 $$ *) := mRule (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 534
 $$ *), yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 534
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 534
 $$ *), yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 534
 $$ *).Position.Line, Position, RuleCount); 
  | 133,84=> (* rule : patternList ':-' TargetCode .*)
  DEC (yyStackPtr, 3); yyNonterminal := 50;
(* line 321 "/tmp/lalr4706" *)
  (* line 295 ../src/rex.lalr *)
   INC (RuleCount);
  		  yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 540
 $$ *) := mRule (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 540
 $$ *), yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 540
 $$ *).Text(* $$ m2tom3 warning: application of variant field, possible cast of 'Text' in line 540
 $$ *), yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 540
 $$ *).Position.Line, NoPosition, RuleCount); 
  | 134,98=> (* patternList : pattern .*)
  DEC (yyStackPtr, 1); yyNonterminal := 55;
(* line 326 "/tmp/lalr4706" *)
  (* line 299 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 545
 $$ *) := mList (nNode, yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 545
 $$ *));			
  | 135,96=> (* patternList : patternList ',' pattern .*)
  DEC (yyStackPtr, 3); yyNonterminal := 55;
(* line 328 "/tmp/lalr4706" *)
  (* line 302 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 550
 $$ *) := mList (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 550
 $$ *), yyAttributeStack^[yyStackPtr+3].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 550
 $$ *));			
  | 136,97=> (* pattern : startStates leftJust regExpr rightContext rightJust .*)
  DEC (yyStackPtr, 5); yyNonterminal := 56;
(* line 332 "/tmp/lalr4706" *)
  (* line 305 ../src/rex.lalr *)
   IF yyAttributeStack^[yyStackPtr+4].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 555
 $$ *) = nNode THEN
  		     tree := yyAttributeStack^[yyStackPtr+5].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 556
 $$ *);
  		  ELSE
  		     IF yyAttributeStack^[yyStackPtr+5].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 558
 $$ *) = nNode THEN
  			tree := yyAttributeStack^[yyStackPtr+4].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 559
 $$ *);
  		     ELSE
  			tree := mSequence (yyAttributeStack^[yyStackPtr+4].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 561
 $$ *), yyAttributeStack^[yyStackPtr+5].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 561
 $$ *));
  		     END;
  		  END;
  
  		  IF yyAttributeStack^[yyStackPtr+2].IsLeftJust(* $$ m2tom3 warning: application of variant field, possible cast of 'IsLeftJust' in line 565
 $$ *) THEN
  		     FOR Number := 1 TO LOOPHOLE (StartStateCount,SHORTCARD) BY 2 DO
  			Exclude (yyAttributeStack^[yyStackPtr+1].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 567
 $$ *), Number);
  		     END;
  		  END;
  
  		  INC (PatternCount);
  		  yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 572
 $$ *) := mPattern (yyAttributeStack^[yyStackPtr+1].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 572
 $$ *), yyAttributeStack^[yyStackPtr+3].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 572
 $$ *), tree,
  		     PatternCount, yyAttributeStack^[yyStackPtr+2].Position(* $$ m2tom3 warning: application of variant field, possible cast of 'Position' in line 573
 $$ *)); 			
  | 137=> (* startStates : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 57;
(* line 355 "/tmp/lalr4706" *)
  (* line 326 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 578
 $$ *), StartStateCount);
  		  Complement (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 579
 $$ *));
  		  Exclude (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 580
 $$ *), 0);					
  | 138,80=> (* startStates : '#' identListUse '#' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 57;
(* line 360 "/tmp/lalr4706" *)
  (* line 331 ../src/rex.lalr *)
   yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 585
 $$ *) := yyAttributeStack^[yyStackPtr+2].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 585
 $$ *);					
  | 139,79=> (* startStates : NOT '#' identListUse '#' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 57;
(* line 363 "/tmp/lalr4706" *)
  (* line 334 ../src/rex.lalr *)
   yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 590
 $$ *) := yyAttributeStack^[yyStackPtr+3].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 590
 $$ *);
  		  Complement (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 591
 $$ *));
  		  Exclude (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 592
 $$ *), 0);					
  | 140=> (* leftJust : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 58;
(* line 370 "/tmp/lalr4706" *)
  (* line 339 ../src/rex.lalr *)
   yySynAttribute.IsLeftJust(* $$ m2tom3 warning: application of variant field, possible cast of 'IsLeftJust' in line 597
 $$ *) := FALSE;
  		  yySynAttribute.Position(* $$ m2tom3 warning: application of variant field, possible cast of 'Position' in line 598
 $$ *)	:= Scanner.Attribute.Position;		
  | 141,81=> (* leftJust : '<' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 58;
(* line 375 "/tmp/lalr4706" *)
  (* line 343 ../src/rex.lalr *)
   yySynAttribute.IsLeftJust(* $$ m2tom3 warning: application of variant field, possible cast of 'IsLeftJust' in line 603
 $$ *) := TRUE;
  		  LeftJustUsed  := TRUE;
  		  yySynAttribute.Position(* $$ m2tom3 warning: application of variant field, possible cast of 'Position' in line 605
 $$ *)	:= Scanner.Attribute.Position;		
  | 142=> (* rightContext : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 59;
(* line 381 "/tmp/lalr4706" *)
  (* line 348 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 610
 $$ *) := nNode;					
  | 143=> (* rightContext : '/' regExpr .*)
  DEC (yyStackPtr, 2); yyNonterminal := 59;
(* line 383 "/tmp/lalr4706" *)
  (* line 351 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 615
 $$ *) := yyAttributeStack^[yyStackPtr+2].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 615
 $$ *);					
  | 144=> (* rightJust : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 60;
(* line 386 "/tmp/lalr4706" *)
  (* line 354 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 620
 $$ *) := nNode;					
  | 145,82=> (* rightJust : '>' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 60;
(* line 388 "/tmp/lalr4706" *)
  (* line 357 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 625
 $$ *) := EOLTree;					
  | 146=> (* regExpr : regExpr '|' regExpr .*)
  DEC (yyStackPtr, 3); yyNonterminal := 54;
(* line 391 "/tmp/lalr4706" *)
  (* line 360 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 630
 $$ *) := mAlternative (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 630
 $$ *), yyAttributeStack^[yyStackPtr+3].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 630
 $$ *));		
  | 147=> (* regExpr : regExpr regExpr .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 393 "/tmp/lalr4706" *)
  (* line 363 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 635
 $$ *) := mSequence (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 635
 $$ *), yyAttributeStack^[yyStackPtr+2].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 635
 $$ *));		
  | 148,66=> (* regExpr : regExpr '+' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 395 "/tmp/lalr4706" *)
  (* line 367 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 640
 $$ *) := mRepetition (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 640
 $$ *));			
  | 149,67=> (* regExpr : regExpr '*' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 397 "/tmp/lalr4706" *)
  (* line 370 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 645
 $$ *) := mOption (mRepetition (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 645
 $$ *)));		
  | 150,68=> (* regExpr : regExpr '?' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 399 "/tmp/lalr4706" *)
  (* line 373 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 650
 $$ *) := mOption (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 650
 $$ *));				
  | 151,70=> (* regExpr : regExpr '[' Number ']' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 54;
(* line 402 "/tmp/lalr4706" *)
  (* line 376 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 655
 $$ *) := nNode;
  		  FOR Number := 1 TO yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 656
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 656
 $$ *) DO
  		     yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 657
 $$ *) := mSequence (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 657
 $$ *), yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 657
 $$ *));
  		  END;							
  | 152,69=> (* regExpr : regExpr '[' Number '-' Number ']' .*)
  DEC (yyStackPtr, 6); yyNonterminal := 54;
(* line 409 "/tmp/lalr4706" *)
  (* line 382 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 663
 $$ *) := nNode;
  		  tree := mOption (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 664
 $$ *));
  		  FOR Number := yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 665
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 665
 $$ *) + 1 TO yyAttributeStack^[yyStackPtr+5].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 665
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 665
 $$ *) DO
  		     yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 666
 $$ *) := mSequence (tree, yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 666
 $$ *));
  		  END;
  		  FOR Number := 1 TO yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 668
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 668
 $$ *) DO
  		     yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 669
 $$ *) := mSequence (yyAttributeStack^[yyStackPtr+1].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 669
 $$ *), yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 669
 $$ *));
  		  END;							
  | 153,71=> (* regExpr : '(' regExpr ')' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 54;
(* line 419 "/tmp/lalr4706" *)
  (* line 392 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 675
 $$ *) := yyAttributeStack^[yyStackPtr+2].Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 675
 $$ *);					
  | 154,87=> (* regExpr : charSet .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 421 "/tmp/lalr4706" *)
  (* line 395 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 680
 $$ *) := mSet (yyAttributeStack^[yyStackPtr+1].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 680
 $$ *));				
  | 155,63=> (* regExpr : Char .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 423 "/tmp/lalr4706" *)
  (* line 398 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 685
 $$ *) := mCh (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 685
 $$ *).Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 685
 $$ *));				
  | 156,60=> (* regExpr : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 426 "/tmp/lalr4706" *)
  (* line 401 ../src/rex.lalr *)
   Definition := GetDef (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 690
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 690
 $$ *));
  		  IF Definition # NoDef THEN
  		     IF GetKind (Definition) = tKind.Ident THEN
  			GetIdentDef (Definition, Identifier, tree1, Number, bool);
  			yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 694
 $$ *) := LOOPHOLE (tree1,ADDRESS);
  		     ELSE
  			GetString (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 696
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 696
 $$ *), string);
  			Errors.ErrorMessageI (ImproperUse, Error, yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 697
 $$ *).Position,
  			   String, ADR (string));
  			yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 699
 $$ *) := nNode;
  		     END;
  		  ELSE
  		     stringref := GetStringRef (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 702
 $$ *).Ident(* $$ m2tom3 warning: application of variant field, possible cast of 'Ident' in line 702
 $$ *));
  		     yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 703
 $$ *) := mString (stringref);
  		  END;							
  | 157,62=> (* regExpr : String .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 443 "/tmp/lalr4706" *)
  (* line 418 ../src/rex.lalr *)
   yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 709
 $$ *) := mString (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 709
 $$ *).String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 709
 $$ *));			
  | 158,61=> (* regExpr : Number .*)
  DEC (yyStackPtr, 1); yyNonterminal := 54;
(* line 446 "/tmp/lalr4706" *)
  (* line 421 ../src/rex.lalr *)
   IntToString (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 714
 $$ *).Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 714
 $$ *), string);
  		  yySynAttribute.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 715
 $$ *) := mString (PutString (string));		
  | 159,86=> (* charSet : '-' charSet .*)
  DEC (yyStackPtr, 2); yyNonterminal := 61;
(* line 452 "/tmp/lalr4706" *)
  (* line 425 ../src/rex.lalr *)
   yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 720
 $$ *) := yyAttributeStack^[yyStackPtr+2].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 720
 $$ *);
  		  Complement (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 721
 $$ *));					
  | 160,65=> (* charSet : '{' rangeList '}' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 61;
(* line 456 "/tmp/lalr4706" *)
  (* line 429 ../src/rex.lalr *)
   yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 726
 $$ *) := yyAttributeStack^[yyStackPtr+2].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 726
 $$ *);					
  | 161=> (* rangeList : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 62;
(* line 459 "/tmp/lalr4706" *)
  (* line 432 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 731
 $$ *), ORD (LastCh));			
  | 162,85=> (* rangeList : rangeList range .*)
  DEC (yyStackPtr, 2); yyNonterminal := 62;
(* line 462 "/tmp/lalr4706" *)
  (* line 435 ../src/rex.lalr *)
   yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 736
 $$ *) := yyAttributeStack^[yyStackPtr+1].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 736
 $$ *);
  		  Union (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 737
 $$ *), yyAttributeStack^[yyStackPtr+2].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 737
 $$ *));
  		  ReleaseSet (yyAttributeStack^[yyStackPtr+2].Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 738
 $$ *));					
  | 163=> (* range : Char .*)
  DEC (yyStackPtr, 1); yyNonterminal := 63;
(* line 469 "/tmp/lalr4706" *)
  (* line 440 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 743
 $$ *), ORD (LastCh));
  		  Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 744
 $$ *), ORD (yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 744
 $$ *).Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 744
 $$ *)));			
  | 164,64=> (* range : Char '-' Char .*)
  DEC (yyStackPtr, 3); yyNonterminal := 63;
(* line 474 "/tmp/lalr4706" *)
  (* line 444 ../src/rex.lalr *)
   MakeSet (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 749
 $$ *), ORD (LastCh));
  		  FOR ch := yyAttributeStack^[yyStackPtr+1].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 750
 $$ *).Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 750
 $$ *) TO yyAttributeStack^[yyStackPtr+3].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 750
 $$ *).Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 750
 $$ *) DO
  		     Include (yySynAttribute.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 751
 $$ *), ORD (ch));
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
         yyAttributeStack^ [yyStackPtr].Scan(* $$ m2tom3 warning: application of variant field, possible cast of 'Scan' in line 773
 $$ *) := Scanner.Attribute;
         yyTerminal := VAL(Scanner.GetToken (),yySymbolRange);
            yyIsRepairing := FALSE;
         END (* IF *);
      END (* LOOP *) ;
   END Parser;

PROCEDURE ErrorRecovery (
      VAR Terminal      : yySymbolRange ;
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
      FOR Token := VAL(Sets.Minimum (ContinueSet),yySymbolRange) TO VAL(Sets.Maximum (ContinueSet),yySymbolRange) DO
         IF Sets.IsElement (VAL(Token,Sets.tElement), ContinueSet) THEN
            TokenName (Token, TokenArray);
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
      Terminal := VAL(Scanner.GetToken (),yySymbolRange);
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
      FOR Terminal := yyFirstTerminal TO yyLastTerminal DO
         IF IsContinuation (Terminal, Stack, StackSize, StackPtr) THEN
            Sets.Include (ContinueSet, VAL(Terminal,Sets.tElement));
         END;
      END;
   END ComputeContinuation;

(*
   check whether a given terminal symbol can be accepted (read)
   in a certain stack configuration (eventually after reduce actions)
*)

PROCEDURE IsContinuation (
      Terminal          : yySymbolRange ;
      ParseStack        : yyStackType   ;
      StackSize         : M2LONGINT       ;
      StackPtr          : yyStackPtrType): BOOLEAN =
   VAR
      State             : yyStackPtrType;
      Nonterminal       : yySymbolRange;
      Stack             : yyStackType;
   BEGIN
      DynArray.MakeArray (LOOPHOLE(Stack,ADDRESS), StackSize, BYTESIZE (yyStateRange));
      FOR State := 0 TO StackPtr DO
         Stack^ [State] := ParseStack^ [State];
      END;
      State := Stack^ [StackPtr];
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
      Nonterminal       : yySymbolRange;
      ContinueSet       : Sets.tSet;
   BEGIN
      DynArray.MakeArray (LOOPHOLE(Stack,ADDRESS), StackSize, BYTESIZE (yyStateRange));
      FOR State := 0 TO StackPtr DO
         Stack^ [State] := ParseStack^ [State];
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

PROCEDURE Next (State: yyStateRange; Symbol: yySymbolRange): yyStateRange =
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
      TBase     : ARRAY (*yyTableElmt*)[0 .. yyLastReadState] OF yyTCombRange;
      NBase     : ARRAY (*yyTableElmt*)[0 .. yyLastReadState] OF yyNCombRange;
   BEGIN
      BlockSize := 64000 DIV BYTESIZE (yyTCombType);
      yyTableFile := System.OpenInput (ParsTabName);
      yyErrorCheck (Errors.OpenParseTable, yyTableFile);
      IF 
         ((yyGetTable (ADR (TBase[FIRST(TBase)]         )) DIV BYTESIZE (yyTCombRange ) - 1)
            # yyLastReadState) OR
         ((yyGetTable (ADR (NBase[FIRST(NBase)]         )) DIV BYTESIZE (yyNCombRange ) - 1)
            # yyLastReadState) OR
         ((yyGetTable (ADR (yyDefault[FIRST(yyDefault)]     )) DIV BYTESIZE (yyReadRange  ) - 1)
            # yyLastReadState) OR
         ((yyGetTable (ADR (yyNComb[FIRST(yyNComb)]       )) DIV BYTESIZE (yyNCombType  ))
            # (yyNTableMax - yyLastTerminal)) OR
         ((yyGetTable (ADR (yyLength[FIRST(yyLength)]      )) DIV BYTESIZE (yyTableElmt  ) - 1)
            # (yyLastReduceState - yyFirstReduceState)) OR
         ((yyGetTable (ADR (yyLeftHandSide[FIRST(yyLeftHandSide)])) DIV BYTESIZE (yySymbolRange) - 1)
            # (yyLastReduceState - yyFirstReduceState)) OR
         ((yyGetTable (ADR (yyContinuation[FIRST(yyContinuation)])) DIV BYTESIZE (yySymbolRange) - 1)
            # yyLastReadState) OR
         ((yyGetTable (ADR (yyFinalToProd[FIRST(yyFinalToProd)] )) DIV BYTESIZE (yyReduceRange) - 1)
            # (yyLastReadNontermState - yyFirstReadTermState))
      THEN
         Errors.ErrorMessage (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition);
      END;
      n := 0;
      j := 0;
      WHILE j <= yyTableMax DO
         INC (n, yyGetTable (ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1037
 $$ *) (yyTComb [VAL(j,yyStateRange)])) DIV BYTESIZE (yyTCombType));
         INC (j, BlockSize);
      END;
      IF n # (yyTableMax + 1) THEN 
         Errors.ErrorMessage (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition);
      END;
      System.Close (yyTableFile);

      FOR State := 1 TO yyLastReadState DO
         yyTBasePtr [State] := ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1046
 $$ *) (yyTComb [TBase [State]]);
      END;
      FOR State := 1 TO yyLastReadState DO
         yyNBasePtr [State] := ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 1049
 $$ *) (yyNComb [NBase [State]]);
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

BEGIN
    yyIsInitialized := FALSE;
    SUBARRAY(ParsTabName , 0, 10) := ARRAY [0..9] OF CHAR{'P','a','r','s','e','r','.','T','a','b'};
IF NUMBER(ParsTabName) > 10 THEN ParsTabName[FIRST(ParsTabName) + 10] := '\000'; END
;
END Parser.

