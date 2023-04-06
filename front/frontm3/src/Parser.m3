(* $Id: Parser.mi,v 2.8 1992/08/12 06:54:05 grosch rel $ *)
(* Skeleton parser for Cocktail lalr. *)
(* Modified Rodney M. Bates. Various times. *)

 UNSAFE MODULE Parser;

IMPORT Fmt, OSError, Rd, Thread, Text, Word, Wr;

IMPORT Scanner, Positions, FrontErrors, Strings, Sets, System;

IMPORT Errors (* From Reusem3. *);

(* line 2 "/tmp/lalr1305" *)
(* line 26 ../src/input.lalr *)

FROM Actions    IMPORT PutAction, PutComment, tActionMode, ScannerName,
                       ParserName;
FROM FrontErrors IMPORT eError, eInteger, ErrorMessageI;
FROM Lists      IMPORT Append, IsEmpty, Head, Tail, MakeList, tList;
FROM Oper       IMPORT OperKind, MakePriority, CompletePriority,
                       MakeOperator, MakeOperHeader;
FROM Scanner    IMPORT GetToken, tScanAttribute, Attribute, ErrorAttribute;
FROM Positions  IMPORT NoPosition;
FROM Strings    IMPORT AssignEmpty, tString, TextToString;
FROM StringMem  IMPORT PutString;
FROM Idents     IMPORT NoIdent, MakeIdent;
FROM TokenTab   IMPORT Terminal;
FROM Tokens     IMPORT MakeGlobalHeader, MakeTokensHeader, MakeDeclaration,
                       CompleteDeclarations;
FROM Rules      IMPORT MakeRulesHeader, MakeLeafNode, MakeActionNode,
                       MakeUnaryNode, MakeBracketNode, MakeBinaryNode,
                       MakePrioAlternativeNode,
                       MakeRule, Operation, NoExpression;

CONST
  cEol = '\012';        (* eol character *)
  eNumToBig = 9;

TYPE SHORTCARD = [ 0 .. 65535];
TYPE tParsAttribute = RECORD Scan: tScanAttribute; END;

VAR
  String                ,
  EndOfLineString       : tString;
  EndOfLine             : ADDRESS;


CONST
   yyInitStackSize      = 100;
   yyNoState            = 0;

   yyFirstTerminal      = 0;
   yyLastTerminal       = 30;
   yyFirstSymbol        = 0;
   yyLastSymbol         = 62;
   yyTableMax           = 222;
   yyNTableMax          = 131;
   yyFirstReadState     = 1;
   yyLastReadState      = 62;
   yyFirstReadTermState = 63;
   yyLastReadTermState  = 78;
   yyLastReadNontermState = 96;
   yyFirstReduceState   = 97;
   yyLastReduceState    = 159;
   yyStartState         = 1;
   yyStopState          = 97;

   yyFirstFinalState    = yyFirstReadTermState;
   yyLastState          = yyLastReduceState;

   yyTableElmtBits = BITSIZE (yyTableElmt);

TYPE
   yyTableElmt          = SHORTCARD;

   (* The conversion to Modula-3 is very fragile, in part due to the
      use of unsafe address arithmetic.
      On the one hand, some types, in some contexts, need to be
      subranges (particularly, as fixed array subscript types),
      and other times, need to have the same size as in Modula-2, to avoid
      undermining various unsafe address arithmetic.  Modula-3 infers
      its own sizes from subranges, except for fields and elements when
      BITS FOR is used.  But assignments involving scalars with BIT FOR
      types present problems and even CM3 code generator failures.

      So if it is a BITS FOR type, its name ends in "Packed", otherwise
      not, the relevant ones ending in "Range".

      Additionally, CM3 has code generator failures assigning between two
      BIT FOR types, at times.  Actual cases where this has happened are
      replaced by two-step copies with an intermediate, unpacked temporary.
  
      These BITS FOR types must occupy exactly a SHORTCARD, when used
      as elements or fields, but must their have subrange bounds when
      used as array subscript types. There a few places where a scalar
      of one of these also must occupy exactly a SHORTCARD. 
   *)
   
   yyTCombRangePacked      = BITS yyTableElmtBits FOR [0 .. yyTableMax];
   yyNCombRangePacked      = BITS yyTableElmtBits
                             FOR [yyLastTerminal + 1 .. yyNTableMax];
   yyStateRange            = [0 .. yyLastState];
   yyStateRangePacked      = BITS yyTableElmtBits FOR yyStateRange;
   yyReadRangePacked       = BITS yyTableElmtBits
                             FOR [yyFirstReadState .. yyLastReadState];
   yyReadReduceRangePacked = BITS yyTableElmtBits
                             FOR [yyFirstReadTermState ..yyLastReadNontermState];
   yyReduceRangePacked     = BITS yyTableElmtBits
                             FOR [yyFirstReduceState .. yyLastReduceState];
   yySymbolRange           = [yyFirstSymbol .. yyLastSymbol];
   yySymbolRangePacked     = BITS yyTableElmtBits FOR yySymbolRange;
   yyTCombType          = RECORD Check, Next: yyStateRangePacked; END;
   yyNCombType          = yyStateRangePacked;
   yyTCombTypePtr       = UNTRACED BRANDED REF  yyTCombType;
   yyNCombTypePtr       = UNTRACED BRANDED REF  yyNCombType;
   yyStackPtrType       = BITS yyTableElmtBits FOR yyTableElmt;
   yyStackType          = REF  ARRAY OF yyStateRangePacked;
   yyAttributeStackType = REF  ARRAY OF tParsAttribute;

VAR
   yyTBasePtr           : ARRAY [0 .. yyLastReadState] OF yyTCombTypePtr;
   yyNBasePtr           : ARRAY [0 .. yyLastReadState] OF yyNCombTypePtr;
   yyDefault            : ARRAY [0 .. yyLastReadState] OF yyReadRangePacked;
   yyTComb              : ARRAY yyTCombRangePacked OF yyTCombType;
   yyNComb              : ARRAY yyNCombRangePacked OF yyNCombType;
   yyLength             : ARRAY yyReduceRangePacked OF yyTableElmt;
   yyLeftHandSide       : ARRAY yyReduceRangePacked OF yySymbolRangePacked;
   yyContinuation       : ARRAY [0 .. yyLastReadState] OF yySymbolRangePacked;
   yyFinalToProd        : ARRAY yyReadReduceRangePacked OF yyReduceRangePacked;
   yyIsInitialized      : BOOLEAN;
   yyTableFile          : System.tFile;

PROCEDURE ExtendStateArray ( VAR ArrRef: REF ARRAY OF yyStateRangePacked ) =
  VAR LOldArrRef : REF ARRAY OF yyStateRangePacked;
  VAR LNumber: INTEGER; 
BEGIN
  LOldArrRef := ArrRef;
  LNumber := NUMBER (ArrRef ^); 
  ArrRef := NEW ( REF ARRAY OF yyStateRangePacked , LNumber * 2 );
  SUBARRAY ( ArrRef ^, 0 , LNumber) := LOldArrRef ^;
END ExtendStateArray; 

PROCEDURE ExtendAttrArray ( VAR ArrRef: REF ARRAY OF tParsAttribute ) =
  VAR LOldArrRef : REF ARRAY OF tParsAttribute;
  VAR LNumber: INTEGER; 
BEGIN
  LOldArrRef := ArrRef;
  LNumber := NUMBER (ArrRef ^); 
  ArrRef := NEW ( REF ARRAY OF tParsAttribute, LNumber * 2 );
  SUBARRAY ( ArrRef ^, 0 , LNumber) := LOldArrRef ^;
END ExtendAttrArray; 

PROCEDURE TokenName (Token: SHORTCARD; VAR Name: ARRAY OF CHAR) =
   PROCEDURE Copy (Source: TEXT; VAR Target: ARRAY OF CHAR) =
      VAR LLastSource, LLastTarget: INTEGER; 
      VAR j: Word.T;
      BEGIN
         LLastSource := Text.Length(Source)-1; 
         LLastTarget := LAST (Target); 
         IF LLastSource < LLastTarget
         THEN j := LLastSource;
         ELSE j := LLastTarget; END;
         FOR i := 0 TO j DO Target [i] := Text.GetChar(Source,i); END;
         IF LLastTarget > j THEN Target [j + 1] := VAL (0,CHAR); END;
      END Copy;
   BEGIN
      CASE Token OF
      | 0=> Copy ("_EndOfFile", Name);
      | 1=> Copy ("=", Name);
      | 2=> Copy (":", Name);
      | 3=> Copy (".", Name);
      | 4=> Copy ("|", Name);
      | 5=> Copy ("*", Name);
      | 6=> Copy ("+", Name);
      | 7=> Copy ("||", Name);
      | 8=> Copy ("(", Name);
      | 9=> Copy (")", Name);
      | 10=> Copy ("[", Name);
      | 11=> Copy ("]", Name);
      | 12=> Copy ("EXPORT", Name);
      | 13=> Copy ("GLOBAL", Name);
      | 14=> Copy ("LOCAL", Name);
      | 15=> Copy ("BEGIN", Name);
      | 16=> Copy ("CLOSE", Name);
      | 17=> Copy ("TOKEN", Name);
      | 18=> Copy ("OPER", Name);
      | 19=> Copy ("NONE", Name);
      | 20=> Copy ("LEFT", Name);
      | 21=> Copy ("RIGHT", Name);
      | 22=> Copy ("RULE", Name);
      | 23=> Copy ("PREC", Name);
      | 24=> Copy ("Comment", Name);
      | 25=> Copy ("Number", Name);
      | 26=> Copy ("Action", Name);
      | 27=> Copy ("Identifier", Name);
      | 28=> Copy ("String", Name);
      | 29=> Copy ("SCANNER", Name);
      | 30=> Copy ("PARSER", Name);
      END;
   END TokenName;

PROCEDURE Parser (): Word.T =
(* line 33 "/tmp/lalr1305" *)
(* line 61 ../src/input.lalr *)
 VAR ActionMode : tActionMode; 
   VAR
      yyState           : yyStateRange;
      yyTerminal        : yySymbolRange;
      yyNonterminal     : yySymbolRange; (* left-hand side symbol *)
      yyStackPtr        : yyStackPtrType;
      yyStateStackSize  : INTEGER;
      yyAttrStackSize   : INTEGER;
      yyShortStackSize  : yyStackPtrType;
      yyStateStack      : yyStackType;
      yyAttributeStack  : yyAttributeStackType;
      yySynAttribute    : tParsAttribute; (* synthesized attribute *)
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
      yyStateStack := NEW ( yyStackType, yyStateStackSize);
      yyAttributeStack := NEW ( yyAttributeStackType, yyAttrStackSize);
      yyShortStackSize  := VAL (   yyStateStackSize,yyStackPtrType ) - 1;
      yyStackPtr        := 0;
      yyErrorCount      := 0;
      yyIsRepairing     := FALSE;

      LOOP
         IF yyStackPtr >= yyShortStackSize THEN
            ExtendStateArray (yyStateStack); 
            ExtendAttrArray (yyAttributeStack); 
            yyShortStackSize := VAL (   yyStateStackSize,yyStackPtrType ) - 1;
         END (* IF *) ;
         yyStateStack^ [yyStackPtr] := yyState;

         LOOP   (* SPEC State := Next (State, Terminal); terminal transition *)
            yyTCombPtr := LOOPHOLE 
                            ( LOOPHOLE ( yyTBasePtr [yyState] ,INTEGER) 
                              + yyTerminal * BYTESIZE (yyTCombType)
                            , yyTCombTypePtr
                            );
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
                     FrontErrors.ErrorMessageI 
                       (FrontErrors.TokenInserted, FrontErrors.Repair,
                     Scanner.Attribute.Position, FrontErrors.Array, 
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
            yyTerminal := VAL(   Scanner.GetToken (),yySymbolRange );
               yyIsRepairing := FALSE;
            END (* IF *) ;

            LOOP (* reduce *)
CASE yyState OF
  | 97=> (* _0000_ : Grammar _EndOfFile .*)
  yyStateStack := NIL;
  yyAttributeStack := NIL;

  RETURN yyErrorCount;

  | 98,96=> (* Grammar : CommentPart ScannerName ParserName Decl Tokens Oper Rules .*)
  DEC (yyStackPtr, 7); yyNonterminal := 38;
(* line 79 "/tmp/lalr1305" *)
  (* line 98 ../src/input.lalr *)
  
  MakeGlobalHeader (yyAttributeStack^[yyStackPtr+1].Scan.Comm, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  
  | 99=> (* ScannerName : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 32;
(* line 86 "/tmp/lalr1305" *)
  (* line 103 ../src/input.lalr *)
  
  ScannerName := NoIdent;
  
  | 100=> (* ScannerName : "SCANNER" .*)
  DEC (yyStackPtr, 1); yyNonterminal := 32;
(* line 92 "/tmp/lalr1305" *)
  (* line 107 ../src/input.lalr *)
  
  TextToString ("Scanner", String); ScannerName := MakeIdent (String);
  
  | 101,64=> (* ScannerName : "SCANNER" Identifier .*)
  DEC (yyStackPtr, 2); yyNonterminal := 32;
(* line 98 "/tmp/lalr1305" *)
  (* line 111 ../src/input.lalr *)
  
  ScannerName := yyAttributeStack^[yyStackPtr+2].Scan.Sym;
  
  | 102=> (* ParserName : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 33;
(* line 105 "/tmp/lalr1305" *)
  (* line 116 ../src/input.lalr *)
  
  ParserName := NoIdent;
  
  | 103=> (* ParserName : "PARSER" .*)
  DEC (yyStackPtr, 1); yyNonterminal := 33;
(* line 111 "/tmp/lalr1305" *)
  (* line 120 ../src/input.lalr *)
  
  TextToString ("Parser", String); ParserName  := MakeIdent (String);
  
  | 104,65=> (* ParserName : "PARSER" Identifier .*)
  DEC (yyStackPtr, 2); yyNonterminal := 33;
(* line 117 "/tmp/lalr1305" *)
  (* line 124 ../src/input.lalr *)
  
  ParserName := yyAttributeStack^[yyStackPtr+2].Scan.Sym;
  
  | 105,79=> (* Decl : Decl "EXPORT" Decl_1 CommentPart Actions .*)
  DEC (yyStackPtr, 5); yyNonterminal := 34;
(* line 124 "/tmp/lalr1305" *)
  (* line 129 ../src/input.lalr *)
  
  PutComment(tActionMode.Export, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Scan.Comm, yyAttributeStack^[yyStackPtr+4].Scan.Position);
  
  | 106,80=> (* Decl : Decl "GLOBAL" Decl_2 CommentPart Actions .*)
  DEC (yyStackPtr, 5); yyNonterminal := 34;
(* line 130 "/tmp/lalr1305" *)
  (* line 133 ../src/input.lalr *)
  
  PutComment(tActionMode.Global, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Scan.Comm, yyAttributeStack^[yyStackPtr+4].Scan.Position);
  
  | 107,81=> (* Decl : Decl "LOCAL" Decl_3 CommentPart Actions .*)
  DEC (yyStackPtr, 5); yyNonterminal := 34;
(* line 136 "/tmp/lalr1305" *)
  (* line 137 ../src/input.lalr *)
  
  PutComment(tActionMode.Local, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Scan.Comm, yyAttributeStack^[yyStackPtr+4].Scan.Position);
  
  | 108,82=> (* Decl : Decl "BEGIN" Decl_4 CommentPart Actions .*)
  DEC (yyStackPtr, 5); yyNonterminal := 34;
(* line 142 "/tmp/lalr1305" *)
  (* line 141 ../src/input.lalr *)
  
  PutComment(tActionMode.Begin, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Scan.Comm, yyAttributeStack^[yyStackPtr+4].Scan.Position);
  
  | 109,83=> (* Decl : Decl "CLOSE" Decl_5 CommentPart Actions .*)
  DEC (yyStackPtr, 5); yyNonterminal := 34;
(* line 148 "/tmp/lalr1305" *)
  (* line 145 ../src/input.lalr *)
  
  PutComment(tActionMode.Close, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Scan.Comm, yyAttributeStack^[yyStackPtr+4].Scan.Position);
  
  | 110=> (* Decl : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 34;

  | 111=> (* Decl_5 : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 44;
(* line 154 "/tmp/lalr1305" *)
  (* line 144 ../src/input.lalr *)
  ActionMode := tActionMode.Close;
  | 112=> (* Decl_4 : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 43;
(* line 156 "/tmp/lalr1305" *)
  (* line 140 ../src/input.lalr *)
  ActionMode := tActionMode.Begin;
  | 113=> (* Decl_3 : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 42;
(* line 158 "/tmp/lalr1305" *)
  (* line 136 ../src/input.lalr *)
  ActionMode := tActionMode.Local;
  | 114=> (* Decl_2 : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 41;
(* line 160 "/tmp/lalr1305" *)
  (* line 132 ../src/input.lalr *)
  ActionMode := tActionMode.Global;
  | 115=> (* Decl_1 : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 39;
(* line 162 "/tmp/lalr1305" *)
  (* line 128 ../src/input.lalr *)
  ActionMode := tActionMode.Export;
  | 116=> (* Actions : Action CommentPart .*)
  DEC (yyStackPtr, 2); yyNonterminal := 40;
(* line 166 "/tmp/lalr1305" *)
  (* line 151 ../src/input.lalr *)
  
  PutAction (ActionMode, yyAttributeStack^[yyStackPtr+1].Scan.Act, yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+2].Scan.Comm, yyAttributeStack^[yyStackPtr+2].Scan.Position);
  
  | 117=> (* Actions : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 40;

  | 118=> (* Tokens : "TOKEN" CommentPart Declarations .*)
  DEC (yyStackPtr, 3); yyNonterminal := 35;
(* line 174 "/tmp/lalr1305" *)
  (* line 157 ../src/input.lalr *)
  
  CompleteDeclarations();
  MakeTokensHeader( yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+2].Scan.Comm, yyAttributeStack^[yyStackPtr+2].Scan.Position);
  
  | 119,84=> (* Declarations : Declarations Declaration .*)
  DEC (yyStackPtr, 2); yyNonterminal := 45;

  | 120,85=> (* Declarations : Declaration .*)
  DEC (yyStackPtr, 1); yyNonterminal := 45;

  | 121=> (* Declaration : Terminal Coding CommentPart .*)
  DEC (yyStackPtr, 3); yyNonterminal := 46;
(* line 185 "/tmp/lalr1305" *)
  (* line 166 ../src/input.lalr *)
  
  MakeDeclaration( yyAttributeStack^[yyStackPtr+1].Scan.Sym, yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+2].Scan.HasCoding, yyAttributeStack^[yyStackPtr+2].Scan.Position,
                   yyAttributeStack^[yyStackPtr+2].Scan.CodValue, yyAttributeStack^[yyStackPtr+2].Scan.CodNumbPos, yyAttributeStack^[yyStackPtr+3].Scan.Comm, yyAttributeStack^[yyStackPtr+3].Scan.Position);
  
  | 122,68=> (* Coding : "=" Number .*)
  DEC (yyStackPtr, 2); yyNonterminal := 48;
(* line 193 "/tmp/lalr1305" *)
  (* line 172 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode := Scanner.AttributeMode.Coding;
  IF (yyAttributeStack^[yyStackPtr+2].Scan.Value > LAST(Terminal)) THEN
    ErrorMessageI (eNumToBig, eError, yyAttributeStack^[yyStackPtr+2].Scan.Position, eInteger, ADR (yyAttributeStack^[yyStackPtr+2].Scan.Value));
    yySynAttribute.Scan.HasCoding       := FALSE;
    yySynAttribute.Scan.CodValue        := 0; (* Dummywert *)
    yySynAttribute.Scan.CodNumbPos      := NoPosition;
  ELSE
    yySynAttribute.Scan.HasCoding       := TRUE;
    yySynAttribute.Scan.CodValue        := yyAttributeStack^[yyStackPtr+2].Scan.Value;
    yySynAttribute.Scan.CodNumbPos      := yyAttributeStack^[yyStackPtr+2].Scan.Position;
  END;
  
  | 123=> (* Coding : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 48;
(* line 209 "/tmp/lalr1305" *)
  (* line 186 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode              := Scanner.AttributeMode.Coding;
  yySynAttribute.Scan.HasCoding := FALSE;
  yySynAttribute.Scan.CodValue  := 0; (* Dummywert *)
  yySynAttribute.Scan.CodNumbPos        := NoPosition;
  
  | 124,86=> (* Oper : "OPER" CommentPart Priorities .*)
  DEC (yyStackPtr, 3); yyNonterminal := 36;
(* line 219 "/tmp/lalr1305" *)
  (* line 194 ../src/input.lalr *)
  
  MakeOperHeader(yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+2].Scan.Comm, yyAttributeStack^[yyStackPtr+2].Scan.Position);
  
  | 125=> (* Oper : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 36;

  | 126,87=> (* Priorities : Priority Priorities .*)
  DEC (yyStackPtr, 2); yyNonterminal := 49;

  | 127=> (* Priorities : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 49;

  | 128=> (* Priority : Associativity Operators CommentPart .*)
  DEC (yyStackPtr, 3); yyNonterminal := 50;
(* line 230 "/tmp/lalr1305" *)
  (* line 203 ../src/input.lalr *)
  
  CompletePriority(yyAttributeStack^[yyStackPtr+3].Scan.Comm, yyAttributeStack^[yyStackPtr+3].Scan.Position);
  
  | 129,70=> (* Associativity : "LEFT" .*)
  DEC (yyStackPtr, 1); yyNonterminal := 51;
(* line 236 "/tmp/lalr1305" *)
  (* line 207 ../src/input.lalr *)
  MakePriority(OperKind.Left, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  | 130,71=> (* Associativity : "RIGHT" .*)
  DEC (yyStackPtr, 1); yyNonterminal := 51;
(* line 238 "/tmp/lalr1305" *)
  (* line 208 ../src/input.lalr *)
  MakePriority(OperKind.Right, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  | 131,69=> (* Associativity : "NONE" .*)
  DEC (yyStackPtr, 1); yyNonterminal := 51;
(* line 240 "/tmp/lalr1305" *)
  (* line 209 ../src/input.lalr *)
  MakePriority(OperKind.None, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  | 132,89=> (* Operators : Operator Operators .*)
  DEC (yyStackPtr, 2); yyNonterminal := 52;

  | 133=> (* Operators : Operator .*)
  DEC (yyStackPtr, 1); yyNonterminal := 52;

  | 134,88=> (* Operator : Terminal .*)
  DEC (yyStackPtr, 1); yyNonterminal := 53;
(* line 247 "/tmp/lalr1305" *)
  (* line 215 ../src/input.lalr *)
  
  MakeOperator(yyAttributeStack^[yyStackPtr+1].Scan.Sym, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  
  | 135,66=> (* Terminal : Identifier .*)
  DEC (yyStackPtr, 1); yyNonterminal := 47;
(* line 254 "/tmp/lalr1305" *)
  (* line 220 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode              := Scanner.AttributeMode.Symbol;
  yySynAttribute.Scan.Sym               := yyAttributeStack^[yyStackPtr+1].Scan.Sym;
  yySynAttribute.Scan.Position  := yyAttributeStack^[yyStackPtr+1].Scan.Position;
  
  | 136,67=> (* Terminal : String .*)
  DEC (yyStackPtr, 1); yyNonterminal := 47;
(* line 262 "/tmp/lalr1305" *)
  (* line 226 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode              := Scanner.AttributeMode.Symbol;
  yySynAttribute.Scan.Sym               := yyAttributeStack^[yyStackPtr+1].Scan.Sym;
  yySynAttribute.Scan.Position  := yyAttributeStack^[yyStackPtr+1].Scan.Position;
  
  | 137=> (* Rules : "RULE" CommentPart Rules_1 .*)
  DEC (yyStackPtr, 3); yyNonterminal := 37;
(* line 271 "/tmp/lalr1305" *)
  (* line 233 ../src/input.lalr *)
  
  MakeRulesHeader(yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+2].Scan.Comm, yyAttributeStack^[yyStackPtr+2].Scan.Position);
  
  | 138=> (* Rules_1 : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 54;

  | 139,95=> (* Rules_1 : Rules_1 Rule .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;

  | 140=> (* Rule : Identifier ":" RightSide "." CommentPart .*)
  DEC (yyStackPtr, 5); yyNonterminal := 55;
(* line 280 "/tmp/lalr1305" *)
  (* line 238 ../src/input.lalr *)
  
  MakeRule(yyAttributeStack^[yyStackPtr+1].Scan.Sym,
           yyAttributeStack^[yyStackPtr+1].Scan.Position,
           yyAttributeStack^[yyStackPtr+2].Scan.Position,
           yyAttributeStack^[yyStackPtr+3].Scan.Expr,
           yyAttributeStack^[yyStackPtr+5].Scan.Comm,
           yyAttributeStack^[yyStackPtr+5].Scan.Position,
           yyAttributeStack^[yyStackPtr+4].Scan.Position,
           yyAttributeStack^[yyStackPtr+3].Scan.HasPrio,   (* Prioritaet der letzten Alternative *)
           yyAttributeStack^[yyStackPtr+3].Scan.Position,
           yyAttributeStack^[yyStackPtr+3].Scan.PriSym,
           yyAttributeStack^[yyStackPtr+3].Scan.PriSymPos);
  
  | 141,93=> (* PrioPart : "PREC" Terminal .*)
  DEC (yyStackPtr, 2); yyNonterminal := 57;
(* line 297 "/tmp/lalr1305" *)
  (* line 253 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode              := Scanner.AttributeMode.PrioPart;
  yySynAttribute.Scan.HasPrio           := TRUE;
  yySynAttribute.Scan.Position  := yyAttributeStack^[yyStackPtr+1].Scan.Position;
  yySynAttribute.Scan.PriSym            := yyAttributeStack^[yyStackPtr+2].Scan.Sym;
  yySynAttribute.Scan.PriSymPos := yyAttributeStack^[yyStackPtr+2].Scan.Position;
  
  | 142=> (* PrioPart : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 57;
(* line 307 "/tmp/lalr1305" *)
  (* line 261 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode              := Scanner.AttributeMode.PrioPart;
  yySynAttribute.Scan.HasPrio           := FALSE;
  yySynAttribute.Scan.PriSymPos := NoPosition;
  yySynAttribute.Scan.PriSym            := 0;
  
  | 143,94=> (* RightSide : Expressions PrioPart "|" RightSide .*)
  DEC (yyStackPtr, 4); yyNonterminal := 56;
(* line 317 "/tmp/lalr1305" *)
  (* line 269 ../src/input.lalr *)
  
  yySynAttribute.Scan           := yyAttributeStack^[yyStackPtr+4].Scan;  (* PrioPart an Rule zurueckgeben *)
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      :=
  MakePrioAlternativeNode (yyAttributeStack^[yyStackPtr+3].Scan.Position,
                           yyAttributeStack^[yyStackPtr+1].Scan.Expr,
                           yyAttributeStack^[yyStackPtr+4].Scan.Expr,
                           yyAttributeStack^[yyStackPtr+2].Scan.HasPrio,
                           yyAttributeStack^[yyStackPtr+2].Scan.Position,
                           yyAttributeStack^[yyStackPtr+2].Scan.PriSym,
                           yyAttributeStack^[yyStackPtr+2].Scan.PriSymPos);
  
  | 144=> (* RightSide : Expressions PrioPart .*)
  DEC (yyStackPtr, 2); yyNonterminal := 56;
(* line 332 "/tmp/lalr1305" *)
  (* line 282 ../src/input.lalr *)
  
  yySynAttribute.Scan           := yyAttributeStack^[yyStackPtr+2].Scan;  (* Priopart an Rule zurueckgeben *)
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  IF yyAttributeStack^[yyStackPtr+1].Scan.Mode = Scanner.AttributeMode.Empty THEN
    yySynAttribute.Scan.Expr    := NoExpression;
  ELSE
    yySynAttribute.Scan.Expr    := yyAttributeStack^[yyStackPtr+1].Scan.Expr;
  END;
  
  | 145,90=> (* Expressions : Expression Expressions .*)
  DEC (yyStackPtr, 2); yyNonterminal := 58;
(* line 345 "/tmp/lalr1305" *)
  (* line 293 ../src/input.lalr *)
  
  IF yyAttributeStack^[yyStackPtr+2].Scan.Mode # Scanner.AttributeMode.Empty
  THEN (* Binary *)
    yySynAttribute.Scan.Mode    := Scanner.AttributeMode.RightSide;
    yySynAttribute.Scan.Expr    := MakeBinaryNode(Operation.Sequence, NoPosition, yyAttributeStack^[yyStackPtr+1].Scan.Expr, yyAttributeStack^[yyStackPtr+2].Scan.Expr);
  ELSE (* Expressions ist leer - Expression ist weiterzureichen *)
    yySynAttribute.Scan := yyAttributeStack^[yyStackPtr+1].Scan;
  END; 
  
  | 146=> (* Expressions : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 58;
(* line 357 "/tmp/lalr1305" *)
  (* line 303 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.Empty;  (* noetig damit kein "leeres Bein" entsteht *)
  yySynAttribute.Scan.Expr      := NoExpression;   (* noetig falls Expr weiterverwendet wird *)
  
  | 147=> (* Expression : Unit .*)
  DEC (yyStackPtr, 1); yyNonterminal := 59;
(* line 365 "/tmp/lalr1305" *)
  (* line 309 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := yyAttributeStack^[yyStackPtr+1].Scan.Expr;
  
  | 148,75=> (* Expression : Unit "*" .*)
  DEC (yyStackPtr, 2); yyNonterminal := 59;
(* line 372 "/tmp/lalr1305" *)
  (* line 314 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeUnaryNode(Operation.Star, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+1].Scan.Expr);
  
  | 149,76=> (* Expression : Unit "+" .*)
  DEC (yyStackPtr, 2); yyNonterminal := 59;
(* line 379 "/tmp/lalr1305" *)
  (* line 319 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeUnaryNode(Operation.Plus, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+1].Scan.Expr);
  
  | 150,91=> (* Expression : Unit "||" Unit .*)
  DEC (yyStackPtr, 3); yyNonterminal := 59;
(* line 386 "/tmp/lalr1305" *)
  (* line 324 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeBinaryNode(Operation.Separator, yyAttributeStack^[yyStackPtr+2].Scan.Position , yyAttributeStack^[yyStackPtr+1].Scan.Expr, yyAttributeStack^[yyStackPtr+3].Scan.Expr);
  
  | 151,77=> (* Unit : "[" Alternative "]" .*)
  DEC (yyStackPtr, 3); yyNonterminal := 60;
(* line 394 "/tmp/lalr1305" *)
  (* line 330 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeBracketNode(Operation.Optional, yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+3].Scan.Position, yyAttributeStack^[yyStackPtr+2].Scan.Expr);
  
  | 152,78=> (* Unit : "(" Alternative ")" .*)
  DEC (yyStackPtr, 3); yyNonterminal := 60;
(* line 401 "/tmp/lalr1305" *)
  (* line 335 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeBracketNode(Operation.Bracket, yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+3].Scan.Position, yyAttributeStack^[yyStackPtr+2].Scan.Expr);
  
  | 153,73=> (* Unit : Identifier .*)
  DEC (yyStackPtr, 1); yyNonterminal := 60;
(* line 408 "/tmp/lalr1305" *)
  (* line 340 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeLeafNode(yyAttributeStack^[yyStackPtr+1].Scan.Sym, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  
  | 154,74=> (* Unit : String .*)
  DEC (yyStackPtr, 1); yyNonterminal := 60;
(* line 415 "/tmp/lalr1305" *)
  (* line 345 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeLeafNode(yyAttributeStack^[yyStackPtr+1].Scan.Sym, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  
  | 155,72=> (* Unit : Action .*)
  DEC (yyStackPtr, 1); yyNonterminal := 60;
(* line 422 "/tmp/lalr1305" *)
  (* line 350 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeActionNode (yyAttributeStack^[yyStackPtr+1].Scan.Act, yyAttributeStack^[yyStackPtr+1].Scan.Position);
  
  | 156,92=> (* Alternative : Expressions "|" Alternative .*)
  DEC (yyStackPtr, 3); yyNonterminal := 61;
(* line 430 "/tmp/lalr1305" *)
  (* line 356 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  yySynAttribute.Scan.Expr      := MakeBinaryNode (Operation.Alternative, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+1].Scan.Expr, yyAttributeStack^[yyStackPtr+3].Scan.Expr);
  
  | 157=> (* Alternative : Expressions .*)
  DEC (yyStackPtr, 1); yyNonterminal := 61;
(* line 437 "/tmp/lalr1305" *)
  (* line 361 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.RightSide;
  IF yyAttributeStack^[yyStackPtr+1].Scan.Mode = Scanner.AttributeMode.Empty THEN
    yySynAttribute.Scan.Expr    := NoExpression;
  ELSE
    yySynAttribute.Scan.Expr    := yyAttributeStack^[yyStackPtr+1].Scan.Expr;
  END;
  
  | 158,63=> (* CommentPart : CommentPart Comment .*)
  DEC (yyStackPtr, 2); yyNonterminal := 31;
(* line 449 "/tmp/lalr1305" *)
  (* line 371 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode      := Scanner.AttributeMode.Comment;
  IF IsEmpty (yyAttributeStack^[yyStackPtr+1].Scan.Comm) THEN
    yySynAttribute.Scan.Position        := yyAttributeStack^[yyStackPtr+2].Scan.Position;
    yySynAttribute.Scan.Comm            := yyAttributeStack^[yyStackPtr+2].Scan.Comm;
  ELSE
    Append (yyAttributeStack^[yyStackPtr+1].Scan.Comm, EndOfLine);
    WHILE NOT IsEmpty (yyAttributeStack^[yyStackPtr+2].Scan.Comm) DO
      Append (yyAttributeStack^[yyStackPtr+1].Scan.Comm, Head(yyAttributeStack^[yyStackPtr+2].Scan.Comm));
      Tail (yyAttributeStack^[yyStackPtr+2].Scan.Comm);
    END;
    yySynAttribute.Scan.Position        := yyAttributeStack^[yyStackPtr+1].Scan.Position;
    yySynAttribute.Scan.Comm            := yyAttributeStack^[yyStackPtr+1].Scan.Comm;
  END;
  
  | 159=> (* CommentPart : .*)
  DEC (yyStackPtr, 0); yyNonterminal := 31;
(* line 467 "/tmp/lalr1305" *)
  (* line 387 ../src/input.lalr *)
  
  yySynAttribute.Scan.Mode              := Scanner.AttributeMode.Comment;
  yySynAttribute.Scan.Position  := NoPosition;
  MakeList (yySynAttribute.Scan.Comm);
  
END;
              (* SPEC State 
                   := Next (Top (), Nonterminal); nonterminal transition *)
               yyNCombPtr 
                 := LOOPHOLE 
                      ( LOOPHOLE ( yyNBasePtr [yyStateStack^ [yyStackPtr]]
                                 , INTEGER
                                 )
                        + yyNonterminal * BYTESIZE (yyNCombType)
                      , yyNCombTypePtr
                      );
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
         yyTerminal := VAL(Scanner.GetToken (),yySymbolRange);
            yyIsRepairing := FALSE;
         END (* IF *);
      END (* LOOP *) ;
   END Parser;

PROCEDURE ErrorRecovery (
      VAR Terminal      : yySymbolRange ;
          StateStack    : yyStackType   ;
          StackSize     : INTEGER       ;
          StackPtr      : yyStackPtrType) =
   VAR
      TokensSkipped     : BOOLEAN;
      ContinueSet       : Sets.tSet;
      RestartSet        : Sets.tSet;
      (*Token           : yySymbolRange;*)
      TokenArray        : ARRAY [0..127] OF CHAR;
      TokenString       : Strings.tString;
      ContinueString    : Strings.tString;
   BEGIN
   (* 1. report the error *)
         TokenName ( Terminal , TokenArray );
         Strings.ArrayToString (TokenArray, TokenString);
         FrontErrors.ErrorMessageI (FrontErrors.SyntaxError, FrontErrors.Error, 
         Scanner.Attribute.Position, FrontErrors.String, ADR(TokenString) );

   (* 2. report the set of expected terminal symbols *)
      Sets.MakeSet (ContinueSet, yyLastTerminal);
      ComputeContinuation (StateStack, StackSize, StackPtr, ContinueSet);
      Strings.AssignEmpty (ContinueString);
      FOR Token := VAL(Sets.Minimum (ContinueSet),yySymbolRange)
          TO VAL(Sets.Maximum (ContinueSet),yySymbolRange) DO
         IF Sets.IsElement (VAL(Token,Sets.tElement), ContinueSet) THEN
            TokenName (Token, TokenArray);
            Strings.ArrayToString (TokenArray, TokenString);
            IF ( ( Strings.Length (ContinueString)
                   + Strings.Length (TokenString) + 1
                 )
                 <= Strings.cMaxStrLength
               ) THEN
               Strings.Concatenate (ContinueString, TokenString);
               Strings.Append (ContinueString, ' ');
            END;
         END;
      END;
      FrontErrors.ErrorMessageI
        (FrontErrors.ExpectedTokens, FrontErrors.Information,
      Scanner.Attribute.Position, FrontErrors.String, ADR (ContinueString));
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
      FrontErrors.ErrorMessage (FrontErrors.RestartPoint, FrontErrors.Information, Scanner.Attribute.Position);
      END;
   END ErrorRecovery;

(*
   compute the set of terminal symbols that can be accepted (read)
   in a given stack configuration (eventually after reduce actions)
*)

PROCEDURE ComputeContinuation (
          Stack         : yyStackType   ;
          StackSize     : INTEGER       ;
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
      StackSize         : INTEGER       ;
      StackPtr          : yyStackPtrType): BOOLEAN =
   VAR
      State             : yyStackPtrType;
      Nonterminal       : yySymbolRange;
      Stack             : yyStackType;
   BEGIN
      Stack := NEW (yyStackType, StackSize);
      FOR RStackPtr := 0 TO StackPtr DO
         (* Making this assignment directly crashes CM3: *)
         State := ParseStack^ [RStackPtr];
         Stack^ [RStackPtr] := State
      END;
      State := StackPtr; 
      State := Stack^ [StackPtr];
      LOOP
         Stack^ [StackPtr] := State;
         State := Next (State, Terminal);
         IF State = yyNoState THEN
            Stack := NIL;
            RETURN FALSE;
         END;
         IF State <= yyLastReadTermState (* read or read terminal reduce ? *)
         THEN
            Stack := NIL;
            RETURN TRUE;
         END;

         LOOP (* reduce *)
            IF State =  yyStopState THEN
               Stack := NIL;
               RETURN TRUE;
            ELSE 
               DEC (StackPtr, yyLength [State]);
               Nonterminal := yyLeftHandSide [State];
            END;

            State := Next (Stack^ [StackPtr], Nonterminal);
            IF StackPtr >= VAL (   StackSize,yyStackPtrType ) THEN
              ExtendStateArray(Stack); 
            END;
            INC (StackPtr);
            IF State < yyFirstFinalState
            THEN EXIT;
            END; (* read nonterminal ? *)
            State := yyFinalToProd [State]; (* read nonterminal reduce *)
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
          StackSize     : INTEGER       ;
          StackPtr      : yyStackPtrType;
      VAR RestartSet    : Sets.tSet     ) =
   VAR
      Stack             : yyStackType;
      State             : yyStackPtrType;
      Nonterminal       : yySymbolRange;
      ContinueSet       : Sets.tSet;
   BEGIN
      Stack := NEW (yyStackType, StackSize);
      FOR RStackPtr := 0 TO StackPtr DO
         (* Making this assignment directly crashes CM3: *)
         State:= ParseStack^ [RStackPtr];
         Stack^ [RStackPtr] := State;
      END;
      Sets.MakeSet (ContinueSet, yyLastTerminal);
      Sets.AssignEmpty (RestartSet);
      State := Stack^ [StackPtr];

      LOOP
         IF StackPtr >= VAL (   StackSize,yyStackPtrType ) THEN
            ExtendStateArray(Stack); 
         END;
         Stack^ [StackPtr] := State;
         ComputeContinuation (Stack, StackSize, StackPtr, ContinueSet);
         Sets.Union (RestartSet, ContinueSet);
         State := Next (State, yyContinuation [State]);

         IF State >= yyFirstFinalState THEN (* final state ? *)
            IF State <= yyLastReadTermState THEN (* read terminal reduce ? *)
               INC (StackPtr);
               State := yyFinalToProd [State];
            END;

            LOOP (* reduce *)
               IF State = yyStopState THEN
                  Stack := NIL;
                  Sets.ReleaseSet (ContinueSet);
                  RETURN;
               ELSE 
                  DEC (StackPtr, yyLength [State]);
                  Nonterminal := yyLeftHandSide [State];
               END;

               State := Next (Stack^ [StackPtr], Nonterminal);
               INC (StackPtr);
               IF State < yyFirstFinalState
               THEN EXIT;
               END; (* read nonterminal ? *)
               State := yyFinalToProd [State]; (* read nonterminal reduce *)
            END;
         ELSE (* read *)
            INC (StackPtr);
         END;
      END;
   END ComputeRestartPoints;

(* access the parse table:   Next : State x Symbol -> State *)

PROCEDURE Next
   (State: yyStateRange; Symbol: yySymbolRange)
   : yyStateRange =
   VAR
      TCombPtr          : yyTCombTypePtr;
      NCombPtr          : yyNCombTypePtr;
   BEGIN
      IF Symbol <= yyLastTerminal THEN
         LOOP
            TCombPtr 
              := LOOPHOLE 
                   ( LOOPHOLE (yyTBasePtr [State],INTEGER) 
                     + Symbol * BYTESIZE (yyTCombType)
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
               ( LOOPHOLE (yyNBasePtr [State],INTEGER) 
                 + Symbol * BYTESIZE (yyNCombType)
               ,yyNCombTypePtr);
(*AS in Rex:yyTCombPtr := LOOPHOLE 
                            ( LOOPHOLE ( yyTBasePtr [yyState] ,M2LONGCARD) 
                              + (VAL (   yyTerminal,M2LONGCARD ) 
                                * BYTESIZE (yyTCombType))
                            ,yyTCombTypePtr);
*)
        RETURN NCombPtr^;
      END;
   END Next;

(* -------------- From rexm3's Parser.m3: -------------------------------*)
(* But further modifiedl *) 

PROCEDURE yyGetTables() 
  = <* FATAL Rd . Failure *> 
    <* FATAL Wr . Failure *> 
    <* FATAL System . FileNoError *> 
    <* FATAL Thread . Alerted *> 
   VAR
      BlockSize, j, n   : Word.T;
      ReadVal: INTEGER;
      OK: BOOLEAN;
      (* These arrays are read-into by binary IO, thus they have to have
         the right bounds on the one hand and the right representation
         element size on the other.  Otherwise, chaos will ensue. *) 
      TBase     : ARRAY [0 .. yyLastReadState] OF yyTCombRangePacked;
      NBase     : ARRAY [0 .. yyLastReadState] OF yyNCombRangePacked;
   BEGIN
      BlockSize := 64000 DIV BYTESIZE (yyTCombType);
      OK := TRUE;
      TRY
        yyTableFile := System.OpenInputT (ParsTabName);
      EXCEPT
        OSError.E 
        => Errors.ErrLine
             ("Error: Can't open parse table file " & ParsTabName); 
        OK := FALSE;
      END;
      IF OK THEN
        ReadVal := yyGetTable
          (ADR (TBase[FIRST(TBase)])) DIV BYTESIZE (yyTCombRangePacked ) - 1;
        IF ReadVal # yyLastReadState THEN
           Errors.ErrLine
             ( "Error reading " & ParsTabName  
               & ", TBase size = " & Fmt.Int (ReadVal) & ", expected "
               & Fmt.Int (yyLastReadState)
             );
           OK := FALSE;
        ELSE
          ReadVal := yyGetTable
            (ADR (NBase[FIRST(NBase)])) DIV BYTESIZE (yyNCombRangePacked ) - 1;
          IF ReadVal # yyLastReadState THEN
             Errors.ErrLine
               ( "Error reading " & ParsTabName
                 & ", NBase size = " & Fmt.Int (ReadVal) & ", expected "
                 & Fmt.Int (yyLastReadState)
               );
             OK := FALSE;
          ELSE
            ReadVal := yyGetTable
              (ADR (yyDefault[FIRST(yyDefault)]))
               DIV BYTESIZE (yyReadRangePacked) - 1;
            IF ReadVal # yyLastReadState THEN
               Errors.ErrLine
                 ( "Error reading " & ParsTabName
                   & ", yyDefault size = " & Fmt.Int (ReadVal) & ", expected "
                   & Fmt.Int (yyLastReadState)
                 );
               OK := FALSE;
            ELSE
              ReadVal := yyGetTable
                (ADR (yyNComb[FIRST(yyNComb)])) DIV BYTESIZE (yyNCombType);
              IF ReadVal # (yyNTableMax - yyLastTerminal) THEN
                 Errors.ErrLine
                   ( "Error reading " & ParsTabName
                     & ", yyNComb size = " & Fmt.Int (ReadVal) & ", expected "
                     & Fmt.Int (yyNTableMax - yyLastTerminal)
                   );
                 OK := FALSE;
              ELSE
                ReadVal := yyGetTable
                  (ADR (yyLength[FIRST(yyLength)]))
                   DIV BYTESIZE (yyTableElmt  ) - 1;
                IF ReadVal # (yyLastReduceState - yyFirstReduceState) THEN
                   Errors.ErrLine
                     ( "Error reading " & ParsTabName
                       & ", yylength size = " & Fmt.Int (ReadVal)
                       & ", expected "
                       & Fmt.Int (yyLastReduceState - yyFirstReduceState)
                     );
                   OK := FALSE;
                ELSE
                  ReadVal := yyGetTable
                    (ADR (yyLeftHandSide[FIRST(yyLeftHandSide)]))
                     DIV BYTESIZE (yySymbolRangePacked) - 1;
                  IF ReadVal # (yyLastReduceState - yyFirstReduceState) THEN
                     Errors.ErrLine
                       ( "Error reading " & ParsTabName
                         & ", yy LeftHandSide size= " & Fmt.Int (ReadVal)
                         & ", expected "
                         & Fmt.Int (yyLastReduceState - yyFirstReduceState)
                       );
                     OK := FALSE;
                  ELSE
                    ReadVal := yyGetTable
                      (ADR (yyContinuation[FIRST(yyContinuation)]))
                       DIV BYTESIZE (yySymbolRangePacked) - 1;
                    IF ReadVal # yyLastReadState THEN
                       Errors.ErrLine
                         ( " Error reading " & ParsTabName
                           & ", yyContinuation size= " & Fmt.Int (ReadVal)
                           & ", expected " & Fmt.Int (yyLastReadState)
                         );
                       OK := FALSE;
                    ELSE
                      ReadVal := yyGetTable
                        (ADR (yyFinalToProd[FIRST(yyFinalToProd)] ))
                         DIV BYTESIZE (yyReduceRangePacked) - 1;
                      IF ReadVal
                         # (yyLastReadNontermState - yyFirstReadTermState)
                      THEN
                         Errors.ErrLine
                           ( "Error reading " & ParsTabName
                             & ", yyFinalToProd size = " & Fmt.Int (ReadVal)
                             & ", expected "
                             & Fmt.Int
                                 (yyLastReadNontermState - yyFirstReadTermState)
                             );
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
          (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition)
      END;
      n := 0;
      j := 0;
      WHILE j <= yyTableMax DO
         INC (n
         , yyGetTable
             (ADR (yyTComb [VAL(j,yyStateRangePacked)]))
              DIV BYTESIZE (yyTCombType)
             );
         INC (j, BlockSize);
      END;
      IF n # (yyTableMax + 1) THEN 
         Errors.ErrorMessage
           (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition);
      END;
      System.Close (yyTableFile);

      FOR StateF := 1 TO yyLastReadState DO
         yyTBasePtr [StateF] := ADR (yyTComb [TBase [StateF]]);
      END;
      FOR StateF := 1 TO yyLastReadState DO
         yyNBasePtr [StateF] := ADR (yyNComb [NBase [StateF]]);
      END;
   END yyGetTables;
(* End from rexm3's Parser.m30 ------------------------------------------*)


PROCEDURE yyGetTable (Address: ADDRESS): Word.T

  = <* FATAL Rd . Failure *> 
    <* FATAL System . FileNoError *> 
    <* FATAL Thread . Alerted *> 
    
   VAR
      N         : INTEGER;
      Length    : RECORD Field : BITS yyTableElmtBits FOR yyTableElmt END;
      LongLength : Word.T;
   BEGIN
      N := System.Read
             (yyTableFile, ADR (Length.Field), BYTESIZE (yyTableElmt));
      yyErrorCheck (FrontErrors.ReadParseTable, N);
      LongLength := Length.Field;
      N := System.Read (yyTableFile, Address, LongLength);
      yyErrorCheck (FrontErrors.ReadParseTable, N);
      RETURN LongLength;
   END yyGetTable;

PROCEDURE yyErrorCheck (ErrorCode: INTEGER; Info: INTEGER) =
   VAR ErrNo: INTEGER;
   BEGIN
     IF Info < 0 THEN
        ErrNo := System.ErrNum ();
        FrontErrors.ErrorMessageI
          (ErrorCode, FrontErrors.Fatal, Positions.NoPosition,
           FrontErrors.Integer, ADR (ErrNo));
     END;
   END yyErrorCheck;

PROCEDURE BeginParser() =
   BEGIN
(* line 37 "/tmp/lalr1305" *)
(* line 55 ../src/input.lalr *)

  AssignEmpty (EndOfLineString);
  Strings.Append (EndOfLineString, cEol);
  EndOfLine := LOOPHOLE (PutString (EndOfLineString),ADDRESS);

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
    ParsTabName := "Parser.Tab";
END Parser.

