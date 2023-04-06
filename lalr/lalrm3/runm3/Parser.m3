(* Derived from: ** $Id: Parser.mi,v 2.8 1992/08/12 06:54:05 grosch rel $ *)
(* Skeleton parser for Cocktail lalr. *)
(* Modified Rodney M. Bates. Various times. rodney.m.bates@acm.org*)
(* Beginning 3-2023: 
    3-2023 Add generation of Module-3 code. 
    Further changes in https://github.com/RodneyBates/cocktail
*) 

(* Parser.m3. *) 

MODULE Parser;

IMPORT SYSTEM, Scanner, Positions, Errors, Strings, IntSets, System;
   IMPORT Fmt, OSError, Text, Word;
(* line 2 "pumagenParser.lalr" *)



FROM StringMem  IMPORT GetString, PutString;
FROM Strings    IMPORT tString, SubString, Length, ArrayToString, IntToString, Concatenate;
FROM Idents     IMPORT tIdent, NoIdent, MakeIdent , GetStringRef ;
FROM Texts      IMPORT tText, MakeText;
FROM Scanner    IMPORT BeginScanner, tScanAttribute, Attribute, Warning;
FROM Positions  IMPORT tPosition, NoPosition;

IMPORT Tree ; 
FROM Tree       IMPORT
(* Note: We have no choice but to import unqualified from Tree,
   since 'Tree' has also been used as the semantic attribute of
   grammar symbols, and has the latter meaning in parse rules. *) 
   mSpec                        , mAttrDesc     , mDesignator   ,
   mLayoutAny   , mNoLayout     , mAnys         ,
   mNoDesignator, mIdent        , mAny          , mNamedExpr    ,
   mNoName      , mName         , mNoTreeName   , mTreeName     ,
   mNoRoutine   , mPredicate    , mProcedure    , mFunction     ,
   mType        , mNoParameter  , mParam        , mNoRule       ,
   mRule        , mNoExpr       , mCompose      , mVarUse       ,
   mOneExpr     ,
   mDontCare1Explicit           , mDontCareExplicit             , 
   mNoStatement , mAssignment   , mCall         , mBinaryCompound , 
   mBinary      , mPreOperator  , mPostOperator , mParents      ,
   mProcCall    , mReject       , mFail         , mNl           ,
   mStringExpr  , mNil          , mIndex        , 
   mOnePatternsList, mNoPatternsList    , OnePatternsList       ,
   tTree        , Compose       , VarUse        , Nil           ,
   Binary       , BinaryCompound, Index         , DontCare1     ,
   Expr         , CopyTree      ,
   TreeRoot     , MakeTree      , Codes         , ReverseTree   ,
   Options      , IsType        ;
FROM Assertions IMPORT Assert, AssertPos, CantHappen, CantHappenPos; 

VAR
   String1, String2     : tString;
   NameCount            : INTEGER;
   Line                 : tPosition;
   nNoParameter, nNoName, nNoRule, nNoDesignator,
   nNoStatement, nNoLayout, nNoPatternsList: tTree;

PROCEDURE mTargetExpr ( pPos : tPosition ; pExpr : tTree ) : tTree

  ; VAR LResult : tTree 

  ; BEGIN 
      LResult 
        := Tree . mTargetExpr ( pPos , (* Selector := *) NoIdent , pExpr ) 
    ; Sets . InitNullSet ( LResult ^ . TargetExpr . UsedNames ) 
    ; RETURN LResult 
    END mTargetExpr ; 

PROCEDURE mTargetStmt 
  ( pPos : tPosition ; pNext : tTree ; pParameters : tTree ; pStmt : tTree ) : tTree

  ; VAR LResult : tTree 

  ; BEGIN 
      LResult := Tree . mTargetStmt ( pPos , pNext , pParameters , pStmt ) 
    ; Sets . InitNullSet ( LResult ^ . TargetStmt . UsedNames ) 
    ; RETURN LResult 
    END mTargetStmt ; 

PROCEDURE mCodes (): tTree;
   VAR t: tTree;
   BEGIN
      t := MakeTree (Codes);
      WITH t^.Codes DO
         MakeText (Export);
         MakeText (Import);
         MakeText (Global);
         MakeText (SpecWith);
         MakeText (BodyWith);
         MakeText (Local);
         MakeText (Begin);
         MakeText (Close);
         ExportLine := NoPosition;
         ImportLine := NoPosition;
         GlobalLine := NoPosition;
         SpecWithLine := NoPosition;
         BodyWithLine := NoPosition;
         LocalLine  := NoPosition;
         BeginLine  := NoPosition;
         CloseLine  := NoPosition;
      END;
      RETURN t;
   END mCodes;

PROCEDURE mRules 
  (Line: tPosition; Patterns: tTree; (* Actually in class PatternsList *) 
   Exprs, Expr, Statements, Next: tTree): tTree;
   VAR Tree     : tTree;
   BEGIN
      Tree := mRule (Line, Patterns^.OnePatternsList.Patterns, Exprs, Expr, Statements, Next);
      Patterns := Patterns^.OnePatternsList.Next;
      WHILE Patterns^.Kind = OnePatternsList DO
         Tree := mRule (Line, Patterns^.OnePatternsList.Patterns, CopyTree (Exprs),
                        CopyTree (Expr), CopyTree (Statements), Tree);
         Patterns := Patterns^.OnePatternsList.Next;
      END;
      RETURN Tree;
   END mRules;

TYPE
yyTrafoName = RECORD Id: tIdent; 
END;
yyTreePart = RECORD Tree: tTree; 
END;
yyTreeNames = RECORD Tree: tTree; 
END;
yyPublicPart = RECORD Tree: tTree; 
END;
yyExternPart0 = RECORD Tree: tTree; 
END;
yyExternPart = RECORD Tree: tTree; 
END;
yyNames = RECORD Tree: tTree; 
END;
yyCodes = RECORD Tree: tTree; 
END;
yyRoutines = RECORD Tree: tTree; 
END;
yyOutParameters = RECORD Tree: tTree; 
END;
yyParameters = RECORD Tree: tTree; 
END;
yyMode = RECORD IsRef: BOOLEAN; 
END;
yyDeclarations = RECORD Tree: tTree; 
END;
yyType = RECORD Tree: tTree; 
END;
yyLocalCode = RECORD Text: tText; 
Position: tPosition; 
END;
yyRules = RECORD Tree: tTree; 
END;
yyPatterns = RECORD Tree: tTree; 
END;
yyPatterns2 = RECORD Tree: tTree; 
END;
yyExprs = RECORD Tree: tTree; 
END;
yyNamedExprs = RECORD Tree: tTree; 
END;
yyExprs2 = RECORD Tree: tTree; 
END;
yyNamedExprs2 = RECORD Tree: tTree; 
END;
yyExpr = RECORD Tree: tTree; 
END;
yyPrefixExpr = RECORD Tree: tTree; 
END;
yyPostfixExpr = RECORD Tree: tTree; 
END;
yyPrimaryExpr = RECORD Tree: tTree; 
END;
yyStatements = RECORD Tree: tTree; 
END;
yyTargetCodes = RECORD Tree: tTree; 
END;
yyName0 = RECORD Id: tIdent; 
Position: tPosition; 
END;
yyName1 = RECORD Id: tIdent; 
Position: tPosition; 
END;
yySpace = RECORD Tree: tTree; 
END;

tParsAttribute = RECORD CASE : SHORTCARD OF
  0: Scan: Scanner.tScanAttribute;
| 1: TrafoName: yyTrafoName;
| 2: TreePart: yyTreePart;
| 3: TreeNames: yyTreeNames;
| 4: PublicPart: yyPublicPart;
| 5: ExternPart0: yyExternPart0;
| 6: ExternPart: yyExternPart;
| 7: Names: yyNames;
| 8: Codes: yyCodes;
| 9: Routines: yyRoutines;
| 10: OutParameters: yyOutParameters;
| 11: Parameters: yyParameters;
| 12: Mode: yyMode;
| 13: Declarations: yyDeclarations;
| 14: Type: yyType;
| 15: LocalCode: yyLocalCode;
| 16: Rules: yyRules;
| 17: Patterns: yyPatterns;
| 18: Patterns2: yyPatterns2;
| 19: Exprs: yyExprs;
| 20: NamedExprs: yyNamedExprs;
| 21: Exprs2: yyExprs2;
| 22: NamedExprs2: yyNamedExprs2;
| 23: Expr: yyExpr;
| 24: PrefixExpr: yyPrefixExpr;
| 25: PostfixExpr: yyPostfixExpr;
| 26: PrimaryExpr: yyPrimaryExpr;
| 27: Statements: yyStatements;
| 28: TargetCodes: yyTargetCodes;
| 29: Name0: yyName0;
| 30: Name1: yyName1;
| 31: Space: yySpace;
 END ;
END ;


CONST
   yyInitStackSize      = 100;
   yyStackExpansionFactor = 2.0 
   yyNoState            = 0;

   yyFirstTerminal          = 0;
   yyLastTerminal           = 51;
   yyFirstSymbol            = 0;
   yyLastSymbol             = 87;
   yyTableMax               = 873;
   yyNTableMax              = 294;
   yyFirstReadState         = 1;
   yyLastReadState          = 187;
   yyFirstReadTermState             = 188;
   yyLastReadTermState              = 255;
   yyLastReadNontermState           = 282;
   yyFirstReduceState               = 283;
   yyLastReduceState                = 428;
   yyStartState             = 1;
   yyStopState              = 283;

   yyFirstFinalState    = yyFirstReadTermState;
   yyLastState          = yyLastReduceState;

TYPE
   yyTableElmt          = SHORTCARD;
   yyTCombRange         = yyTableElmt (*[0 .. yyTableMax]*);
   yyNCombRange         = yyTableElmt (*[yyLastTerminal + 1 .. yyNTableMax]*);
   yyStateRange         = yyTableElmt (*[0 .. yyLastState]*);
   yyReadRange          = yyTableElmt (*[yyFirstReadState .. yyLastReadState]*);
   yyReadReduceRange    = yyTableElmt 
                            (*[yyFirstReadTermState ..yyLastReadNontermState]*);
   yyReduceRange        = yyTableElmt
                            (*[yyFirstReduceState .. yyLastReduceState]*);
   yySymbolRange        = yyTableElmt (*[yyFirstSymbol .. yyLastSymbol]*);
   yyTCombType          = RECORD Check, Next: yyStateRange; END;
   yyNCombType          = yyStateRange;
   yyTCombTypePtr       = REF yyTCombType;
   yyNCombTypePtr       = REF yyNCombType;
   yyStackPtrType       = INTEGER 
   yyStackType          = REF ARRAY OF yyStateRange;
   yyAttributeStackType = REF ARRAY OF tParsAttribute 

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

(*EXPORTED*)
PROCEDURE TokenName (Token: SHORTCARD; VAR Name: TEXT) =
   BEGIN
      CASE Token OF
      | 0 => Name := "_EndOfFile";
      | 1 => Name := "Ident";
      | 2 => Name := "Operator";
      | 3 => Name := "IncOperator";
      | 4 => Name := "CompoundOperator";
      | 5 => Name := "TargetBlock";
      | 6 => Name := "String";
      | 7 => Name := "Number";
      | 8 => Name := "TargetCode";
      | 9 => Name := "WhiteSpace";
      | 10 => Name := "::";
      | 11 => Name := ".";
      | 12 => Name := "->";
      | 13 => Name := "TRAFO";
      | 14 => Name := "TREE";
      | 15 => Name := ",";
      | 16 => Name := "PUBLIC";
      | 17 => Name := "EXTERN";
      | 18 => Name := ";";
      | 19 => Name := "SPECWITH";
      | 20 => Name := "BODYWITH";
      | 21 => Name := "EXPORT";
      | 22 => Name := "IMPORT";
      | 23 => Name := "GLOBAL";
      | 24 => Name := "BEGIN";
      | 25 => Name := "CLOSE";
      | 26 => Name := "PROCEDURE";
      | 27 => Name := "(";
      | 28 => Name := "REF";
      | 29 => Name := ":";
      | 30 => Name := "[";
      | 31 => Name := "]";
      | 32 => Name := "=>";
      | 33 => Name := ")";
      | 34 => Name := "LOCAL";
      | 35 => Name := "..";
      | 36 => Name := ":>";
      | 37 => Name := "NIL";
      | 38 => Name := "_";
      | 39 => Name := "{";
      | 40 => Name := "}";
      | 41 => Name := "^";
      | 42 => Name := ":=";
      | 43 => Name := "?";
      | 44 => Name := "REJECT";
      | 45 => Name := "FAIL";
      | 46 => Name := "VAR";
      | 47 => Name := "NL";
      | 48 => Name := "RETURN";
      | 49 => Name := "FUNCTION";
      | 50 => Name := "PREDICATE";
      | 51 => Name := "HIGH";
      END;
   END TokenName;

(*EXPORTED*)
PROCEDURE Parser (): CARDINAL =
(* line 214 "pumagenParser.lalr" *)


   VAR
      yyState           : yyStateRange;
      yyTerminal        : yySymbolRange;
      yyNonterminal     : yySymbolRange;        (* left-hand side symbol *)
      yyStackPtr        : yyStackPtrType;
      yyStackLAST       : INTEGER;
      yyStateStackSize  : INTEGER;
      (* yyStackPtr, yyStackLAST, and yyStateStackSize always apply equally
         to yyStateStack and yyAttributeStack. *)
      yyStateStack      : yyStackType;
      yyAttributeStack  : yyAttributeStackType;
      yySynAttribute    : tParsAttribute;       (* synthesized attribute *)
   yyRepairAttribute : Scanner.tScanAttribute;
      yyRepairToken     : yySymbolRange;
      yyTCombPtr        : yyTCombTypePtr;
      yyNCombPtr        : yyNCombTypePtr;
      yyIsRepairing     : BOOLEAN;
      yyErrorCount      : CARDINAL;
      yyTokenString     : ARRAY [0..127] OF CHAR;
      
    PROCEDURE ExpandStateStack ( VAR Stack : yyStackTyp , ToSize : INTEGER ) =

      VAR LOldStack : yyStackTyp;
      VAR LStackNumber : INTEGER; 
      BEGIN
        LStackNumber := NUMBER ( Stack ^ );
        IF LStackNumber < ToSize
        THEN
          LOldStack := Stack; 
          Stack := NEW ( yyStackTyp , ToSize );
          SUBARRAY ( Stack ^ , 0 LStackNumber ) := LOldStack ^;
          LOldStack := NIL; 
        END; ll
      END ExpandStateStack; 

    PROCEDURE ExpandAttributeStack
      ( VAR Stack : yyAttributeStackTyp , ToSize : INTEGER ) =

      VAR LOldStack : yyAttributeStackTyp;
      VAR LStackNumber : INTEGER; 
      BEGIN
        LStackNumber := NUMBER ( Stack ^ );
        IF LStackNumber < ToSize
        THEN
          LOldStack := Stack; 
          Stack := NEW ( yyAttributeStackTyp , ToSize );
          SUBARRAY ( Stack ^ , 0 LStackNumber ) := LOldStack ^;
          LOldStack := NIL; 
        END; 
      END ExpandAttributeStack; 

BEGIN (* Parser *) 
   BeginParser;
      yyState           := yyStartState;
   yyTerminal        := Scanner.GetToken ();
      yyStateStackSize  := yyInitStackSize;
      yyAttrStackSize   := yyInitStackSize;
      yyStateStack := NEW ( yStateStackType , yyStateStackSize )
      yyAttributeStack := NEW ( yyAttributeStackType , yyStateStackSize ) 
      yyStackLAST := LAST ( yyStateStack ^ ) (* Of yyAttributeStack too. *);
      yyStackPtr        := 0;
      yyErrorCount      := 0;
      yyIsRepairing     := FALSE;

      LOOP (* Through parsing actions. One iteration does:
              1) Any token deletions called for by an error.
              2) Any continuation token insertions called for 
                 after an error.
              3) Either: 
                 a) Possibly one read-reduce followed by 
                    a sequence of reduces
              or b) One read
           *)  
         (* Push state stack. *) 
         IF yyStackPtr >= yyStackLAST 
         THEN
            yyStateStackSize
              := MAX ( NUMBER ( yyStateStack ^ ) * 2 , yyStackPtr + 2 ) 
            ExpandStateStack ( yyStateStack , yyStateStackSize ); 
            ExpandAttributeStack ( yyAttributeStack , yyStateStackSize );
            yyStackLAST
              := LAST ( yyStateStack ^ ) (* Of yyAttributeStack too. *);
         END (* IF *) ;
         yyStateStack^ [yyStackPtr] := yyState;

         LOOP (* Through all continuation pushes, plus compute the state
                 after that. This loop also goes through the default state
                 computations. *) 
            (* SPEC State := Next (State, Terminal); terminal transition *)

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
                       (yyRepairToken, yyRepairAttribute);
                     TokenName (yyRepairToken, yyTokenString);
                     Errors.ErrorMessageI 
                       (Errors.TokenInserted, Errors.Repair,
                     Scanner.Attribute.Position, Errors.Array, 
                        ADR (yyTokenString)
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
                    (yyTerminal, yyStateStack,
                     NUMBER ( yyStateStack ^ ), yyStackPtr);
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
            yyTerminal := Scanner.GetToken ();
               yyIsRepairing := FALSE;
            END (* IF *) ;

            LOOP (* Through successive reductions *)
CASE yyState OF
  | 283: (* _0000_ : Trafo _EndOfFile .*)
  yyStateStack := NIL;
  yyAttributeStack := NIL;
  RETURN yyErrorCount;

  | 284: (* Trafo : TrafoName TreePart PublicPart ExternPart0 Codes Routines .*)
  DEC (yyStackPtr, 6); yyNonterminal := 58;
(* line 294 of "pumagenParser.lalr" *)
   ;
   TreeRoot := mSpec (yyAttributeStack^[yyStackPtr+1].TrafoName.Id, yyAttributeStack^[yyStackPtr+2].TreePart.Tree, yyAttributeStack^[yyStackPtr+3].PublicPart.Tree,
                   yyAttributeStack^[yyStackPtr+4].ExternPart0.Tree, yyAttributeStack^[yyStackPtr+5].Codes.Tree, ReverseTree (yyAttributeStack^[yyStackPtr+6].Routines.Tree)); ;
   ;
  
  | 285: (* TrafoName : .*)
yyNonterminal := 52;
(* line 299 of "pumagenParser.lalr" *)
   ArrayToString ("Trafo", String1); yySynAttribute.TrafoName.Id := MakeIdent (String1); ;
    ;
  
  | 286,256: (* TrafoName : TRAFO Name0 .*)
  DEC (yyStackPtr, 2); yyNonterminal := 52;
(* line 302 of "pumagenParser.lalr" *)
  yySynAttribute.TrafoName.Id := yyAttributeStack^[yyStackPtr+2].Name0.Id;
  
  | 287: (* TreePart : .*)
yyNonterminal := 53;
(* line 304 of "pumagenParser.lalr" *)
   ArrayToString ("Tree", String1);
              yySynAttribute.TreePart.Tree := mTreeName (MakeIdent (String1), Attribute.Position, mNoTreeName ()); ;
   ;
  
  | 288: (* TreePart : 'TREE' TreeNames .*)
  DEC (yyStackPtr, 2); yyNonterminal := 53;
(* line 308 of "pumagenParser.lalr" *)
   yySynAttribute.TreePart.Tree := ReverseTree (yyAttributeStack^[yyStackPtr+2].TreeNames.Tree);
   ;
  
  | 289: (* TreeNames : .*)
yyNonterminal := 60;
(* line 311 of "pumagenParser.lalr" *)
   yySynAttribute.TreeNames.Tree := mNoTreeName ();
   ;
  
  | 290,190: (* TreeNames : TreeNames ',' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 60;
(* line 314 of "pumagenParser.lalr" *)
  yySynAttribute.TreeNames.Tree := yyAttributeStack^[yyStackPtr+1].TreeNames.Tree;
  
  | 291,257: (* TreeNames : TreeNames Name0 .*)
  DEC (yyStackPtr, 2); yyNonterminal := 60;
(* line 316 of "pumagenParser.lalr" *)
   yySynAttribute.TreeNames.Tree := mTreeName (yyAttributeStack^[yyStackPtr+2].Name0.Id, yyAttributeStack^[yyStackPtr+2].Name0.Position, yyAttributeStack^[yyStackPtr+1].TreeNames.Tree);
   ;
  
  | 292: (* PublicPart : .*)
yyNonterminal := 54;
(* line 319 of "pumagenParser.lalr" *)
   yySynAttribute.PublicPart.Tree := nNoName;
   ;
  
  | 293: (* PublicPart : PUBLIC Names .*)
  DEC (yyStackPtr, 2); yyNonterminal := 54;
(* line 322 of "pumagenParser.lalr" *)
   yySynAttribute.PublicPart.Tree := ReverseTree (yyAttributeStack^[yyStackPtr+2].Names.Tree);
   ;
  
  | 294: (* ExternPart0 : .*)
yyNonterminal := 55;
(* line 325 of "pumagenParser.lalr" *)
   yySynAttribute.ExternPart0.Tree := nNoName;
   ;
  
  | 295,259: (* ExternPart0 : EXTERN Names OptSemiColon .*)
  DEC (yyStackPtr, 3); yyNonterminal := 55;
(* line 328 of "pumagenParser.lalr" *)
   yySynAttribute.ExternPart0.Tree := ReverseTree (yyAttributeStack^[yyStackPtr+2].Names.Tree);
   ;
  
  | 296: (* ExternPart : .*)
yyNonterminal := 63;
(* line 331 of "pumagenParser.lalr" *)
   yySynAttribute.ExternPart.Tree := nNoName;
   ;
  
  | 297,203: (* ExternPart : EXTERN Names ';' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 63;
(* line 334 of "pumagenParser.lalr" *)
   yySynAttribute.ExternPart.Tree := ReverseTree (yyAttributeStack^[yyStackPtr+2].Names.Tree);
   ;
  
  | 298: (* Names : .*)
yyNonterminal := 61;
(* line 337 of "pumagenParser.lalr" *)
   yySynAttribute.Names.Tree := nNoName;
   ;
  
  | 299,191: (* Names : Names ',' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 61;
(* line 340 of "pumagenParser.lalr" *)
  yySynAttribute.Names.Tree := yyAttributeStack^[yyStackPtr+1].Names.Tree;
  
  | 300,258: (* Names : Names Name0 .*)
  DEC (yyStackPtr, 2); yyNonterminal := 61;
(* line 342 of "pumagenParser.lalr" *)
   yySynAttribute.Names.Tree := mName (yyAttributeStack^[yyStackPtr+2].Name0.Id, yyAttributeStack^[yyStackPtr+2].Name0.Position, yyAttributeStack^[yyStackPtr+1].Names.Tree);
   ;
  
  | 301: (* Codes : .*)
yyNonterminal := 56;
(* line 345 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := mCodes();
   ;
  
  | 302,193: (* Codes : Codes 'SPECWITH' TargetBlock .*)
  DEC (yyStackPtr, 3); yyNonterminal := 56;
(* line 348 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := yyAttributeStack^[yyStackPtr+1].Codes.Tree;
              yySynAttribute.Codes.Tree^.Codes.SpecWith     := yyAttributeStack^[yyStackPtr+3].Scan.TargetBlock.Text;
              yySynAttribute.Codes.Tree^.Codes.SpecWithLine := yyAttributeStack^[yyStackPtr+3].Scan.Position; ;
   ;
  
  | 303,194: (* Codes : Codes 'BODYWITH' TargetBlock .*)
  DEC (yyStackPtr, 3); yyNonterminal := 56;
(* line 353 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := yyAttributeStack^[yyStackPtr+1].Codes.Tree;
              yySynAttribute.Codes.Tree^.Codes.BodyWith     := yyAttributeStack^[yyStackPtr+3].Scan.TargetBlock.Text;
              yySynAttribute.Codes.Tree^.Codes.BodyWithLine := yyAttributeStack^[yyStackPtr+3].Scan.Position; ;
   ;
  
  | 304,195: (* Codes : Codes 'EXPORT' TargetBlock .*)
  DEC (yyStackPtr, 3); yyNonterminal := 56;
(* line 358 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := yyAttributeStack^[yyStackPtr+1].Codes.Tree;
              yySynAttribute.Codes.Tree^.Codes.Export     := yyAttributeStack^[yyStackPtr+3].Scan.TargetBlock.Text;
              yySynAttribute.Codes.Tree^.Codes.ExportLine := yyAttributeStack^[yyStackPtr+3].Scan.Position; ;
   ;
  
  | 305,196: (* Codes : Codes 'IMPORT' TargetBlock .*)
  DEC (yyStackPtr, 3); yyNonterminal := 56;
(* line 363 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := yyAttributeStack^[yyStackPtr+1].Codes.Tree;
              yySynAttribute.Codes.Tree^.Codes.Import     := yyAttributeStack^[yyStackPtr+3].Scan.TargetBlock.Text;
              yySynAttribute.Codes.Tree^.Codes.ImportLine := yyAttributeStack^[yyStackPtr+3].Scan.Position; ;
   ;
  
  | 306,197: (* Codes : Codes 'GLOBAL' TargetBlock .*)
  DEC (yyStackPtr, 3); yyNonterminal := 56;
(* line 368 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := yyAttributeStack^[yyStackPtr+1].Codes.Tree;
              yySynAttribute.Codes.Tree^.Codes.Global     := yyAttributeStack^[yyStackPtr+3].Scan.TargetBlock.Text;
              yySynAttribute.Codes.Tree^.Codes.GlobalLine := yyAttributeStack^[yyStackPtr+3].Scan.Position; ;
   ;
  
  | 307,198: (* Codes : Codes 'BEGIN' TargetBlock .*)
  DEC (yyStackPtr, 3); yyNonterminal := 56;
(* line 373 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := yyAttributeStack^[yyStackPtr+1].Codes.Tree;
              yySynAttribute.Codes.Tree^.Codes.Begin      := yyAttributeStack^[yyStackPtr+3].Scan.TargetBlock.Text;
              yySynAttribute.Codes.Tree^.Codes.BeginLine  := yyAttributeStack^[yyStackPtr+3].Scan.Position; ;
   ;
  
  | 308,199: (* Codes : Codes 'CLOSE' TargetBlock .*)
  DEC (yyStackPtr, 3); yyNonterminal := 56;
(* line 378 of "pumagenParser.lalr" *)
   yySynAttribute.Codes.Tree := yyAttributeStack^[yyStackPtr+1].Codes.Tree;
              yySynAttribute.Codes.Tree^.Codes.Close      := yyAttributeStack^[yyStackPtr+3].Scan.TargetBlock.Text;
              yySynAttribute.Codes.Tree^.Codes.CloseLine  := yyAttributeStack^[yyStackPtr+3].Scan.Position; ;
   ;
  
  | 309: (* Routines : .*)
yyNonterminal := 57;
(* line 383 of "pumagenParser.lalr" *)
   yySynAttribute.Routines.Tree := mNoRoutine ();
   ;
  
  | 310: (* Routines : Routines PROCEDURE Name0 '(' Parameters OutParameters ')' ExternPart LocalCode Rules .*)
  DEC (yyStackPtr, 10); yyNonterminal := 57;
(* line 386 of "pumagenParser.lalr" *)
   yySynAttribute.Routines.Tree := mProcedure (yyAttributeStack^[yyStackPtr+1].Routines.Tree, yyAttributeStack^[yyStackPtr+3].Name0.Id, yyAttributeStack^[yyStackPtr+3].Name0.Position,
                 yyAttributeStack^[yyStackPtr+5].Parameters.Tree, yyAttributeStack^[yyStackPtr+6].OutParameters.Tree, yyAttributeStack^[yyStackPtr+8].ExternPart.Tree, yyAttributeStack^[yyStackPtr+9].LocalCode.Text,
                 yyAttributeStack^[yyStackPtr+9].LocalCode.Position, ReverseTree (yyAttributeStack^[yyStackPtr+10].Rules.Tree));
   ;
  
  | 311: (* Routines : Routines 'FUNCTION' Name0 '(' Parameters OutParameters ')' Type ExternPart LocalCode Rules .*)
  DEC (yyStackPtr, 11); yyNonterminal := 57;
(* line 391 of "pumagenParser.lalr" *)
   yySynAttribute.Routines.Tree := mFunction (yyAttributeStack^[yyStackPtr+1].Routines.Tree, yyAttributeStack^[yyStackPtr+3].Name0.Id, yyAttributeStack^[yyStackPtr+3].Name0.Position,
                 yyAttributeStack^[yyStackPtr+5].Parameters.Tree, yyAttributeStack^[yyStackPtr+6].OutParameters.Tree, yyAttributeStack^[yyStackPtr+9].ExternPart.Tree, yyAttributeStack^[yyStackPtr+10].LocalCode.Text,
                 yyAttributeStack^[yyStackPtr+10].LocalCode.Position, ReverseTree (yyAttributeStack^[yyStackPtr+11].Rules.Tree),
                 mParam (FALSE, NoIdent, yyAttributeStack^[yyStackPtr+8].Type.Tree^.Type.Pos, yyAttributeStack^[yyStackPtr+8].Type.Tree, nNoParameter));
   ;
  
  | 312: (* Routines : Routines 'FUNCTION' Name0 '(' Parameters OutParameters ')' ':' Type ExternPart LocalCode Rules .*)
  DEC (yyStackPtr, 12); yyNonterminal := 57;
(* line 397 of "pumagenParser.lalr" *)
   yySynAttribute.Routines.Tree := mFunction (yyAttributeStack^[yyStackPtr+1].Routines.Tree, yyAttributeStack^[yyStackPtr+3].Name0.Id, yyAttributeStack^[yyStackPtr+3].Name0.Position,
                 yyAttributeStack^[yyStackPtr+5].Parameters.Tree, yyAttributeStack^[yyStackPtr+6].OutParameters.Tree, yyAttributeStack^[yyStackPtr+10].ExternPart.Tree, yyAttributeStack^[yyStackPtr+11].LocalCode.Text,
                 yyAttributeStack^[yyStackPtr+11].LocalCode.Position, ReverseTree (yyAttributeStack^[yyStackPtr+12].Rules.Tree),
                 mParam (FALSE, NoIdent, yyAttributeStack^[yyStackPtr+8].Scan.Position, yyAttributeStack^[yyStackPtr+9].Type.Tree, nNoParameter));
   ;
  
  | 313: (* Routines : Routines PREDICATE Name0 '(' Parameters OutParameters ')' ExternPart LocalCode Rules .*)
  DEC (yyStackPtr, 10); yyNonterminal := 57;
(* line 403 of "pumagenParser.lalr" *)
   yySynAttribute.Routines.Tree := mPredicate (yyAttributeStack^[yyStackPtr+1].Routines.Tree, yyAttributeStack^[yyStackPtr+3].Name0.Id, yyAttributeStack^[yyStackPtr+3].Name0.Position,
                 yyAttributeStack^[yyStackPtr+5].Parameters.Tree, yyAttributeStack^[yyStackPtr+6].OutParameters.Tree, yyAttributeStack^[yyStackPtr+8].ExternPart.Tree, yyAttributeStack^[yyStackPtr+9].LocalCode.Text,
                 yyAttributeStack^[yyStackPtr+9].LocalCode.Position, ReverseTree (yyAttributeStack^[yyStackPtr+10].Rules.Tree));
   ;
  
  | 314: (* OutParameters : .*)
yyNonterminal := 65;
(* line 408 of "pumagenParser.lalr" *)
   yySynAttribute.OutParameters.Tree := nNoParameter;
   ;
  
  | 315,260: (* OutParameters : '=>' Parameters .*)
  DEC (yyStackPtr, 2); yyNonterminal := 65;
(* line 411 of "pumagenParser.lalr" *)
  yySynAttribute.OutParameters.Tree := yyAttributeStack^[yyStackPtr+2].Parameters.Tree;
  
  | 316: (* Parameters : .*)
yyNonterminal := 64;
(* line 413 of "pumagenParser.lalr" *)
   yySynAttribute.Parameters.Tree := nNoParameter;
   ;
  
  | 317: (* Parameters : Mode Ident ':' Type .*)
  DEC (yyStackPtr, 4); yyNonterminal := 64;
(* line 416 of "pumagenParser.lalr" *)
   yySynAttribute.Parameters.Tree := mParam (yyAttributeStack^[yyStackPtr+1].Mode.IsRef, yyAttributeStack^[yyStackPtr+2].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Type.Tree, nNoParameter);
   ;
  
  | 318: (* Parameters : Mode Type .*)
  DEC (yyStackPtr, 2); yyNonterminal := 64;
(* line 419 of "pumagenParser.lalr" *)
   ArrayToString ("yyP", String1); INC (NameCount);
                 IntToString (NameCount, String2); Concatenate (String1, String2);
                 yySynAttribute.Parameters.Tree := mParam (yyAttributeStack^[yyStackPtr+1].Mode.IsRef, MakeIdent (String1), NoPosition, yyAttributeStack^[yyStackPtr+2].Type.Tree, nNoParameter); ;
   ;
  
  | 319,262: (* Parameters : Mode Ident ':' Type ',' Parameters .*)
  DEC (yyStackPtr, 6); yyNonterminal := 64;
(* line 424 of "pumagenParser.lalr" *)
   yySynAttribute.Parameters.Tree := mParam (yyAttributeStack^[yyStackPtr+1].Mode.IsRef, yyAttributeStack^[yyStackPtr+2].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Type.Tree, yyAttributeStack^[yyStackPtr+6].Parameters.Tree);
   ;
  
  | 320,264: (* Parameters : Mode Type ',' Parameters .*)
  DEC (yyStackPtr, 4); yyNonterminal := 64;
(* line 427 of "pumagenParser.lalr" *)
   ArrayToString ("yyP", String1); INC (NameCount);
                 IntToString (NameCount, String2); Concatenate (String1, String2);
                 yySynAttribute.Parameters.Tree := mParam (yyAttributeStack^[yyStackPtr+1].Mode.IsRef, MakeIdent (String1), NoPosition, yyAttributeStack^[yyStackPtr+2].Type.Tree, yyAttributeStack^[yyStackPtr+4].Parameters.Tree); ;
   ;
  
  | 321,263: (* Parameters : Mode Ident ':' Type ';' Parameters .*)
  DEC (yyStackPtr, 6); yyNonterminal := 64;
(* line 432 of "pumagenParser.lalr" *)
   yySynAttribute.Parameters.Tree := mParam (yyAttributeStack^[yyStackPtr+1].Mode.IsRef, yyAttributeStack^[yyStackPtr+2].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Type.Tree, yyAttributeStack^[yyStackPtr+6].Parameters.Tree);
   ;
  
  | 322,265: (* Parameters : Mode Type ';' Parameters .*)
  DEC (yyStackPtr, 4); yyNonterminal := 64;
(* line 435 of "pumagenParser.lalr" *)
   ArrayToString ("yyP", String1); INC (NameCount);
                 IntToString (NameCount, String2); Concatenate (String1, String2);
                 yySynAttribute.Parameters.Tree := mParam (yyAttributeStack^[yyStackPtr+1].Mode.IsRef, MakeIdent (String1), NoPosition, yyAttributeStack^[yyStackPtr+2].Type.Tree, yyAttributeStack^[yyStackPtr+4].Parameters.Tree); ;
   ;
  
  | 323: (* Mode : .*)
yyNonterminal := 69;
(* line 440 of "pumagenParser.lalr" *)
   yySynAttribute.Mode.IsRef := FALSE ;
   ;
  
  | 324,200: (* Mode : REF .*)
  DEC (yyStackPtr, 1); yyNonterminal := 69;
(* line 443 of "pumagenParser.lalr" *)
   yySynAttribute.Mode.IsRef := TRUE ;
   ;
  
  | 325: (* Declarations : Ident ':' Type .*)
  DEC (yyStackPtr, 3); yyNonterminal := 70;
(* line 446 of "pumagenParser.lalr" *)
   Warning ( "VAR needed" , yyAttributeStack^[yyStackPtr+1].Scan.Position ) ;  
                     yySynAttribute.Declarations.Tree := mParam 
                       ( FALSE , yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident , yyAttributeStack^[yyStackPtr+1].Scan.Position
                       , yyAttributeStack^[yyStackPtr+3].Type.Tree , nNoParameter
                       ) ; 
                   ;
    
            ;
  
  | 326,280: (* Declarations : Ident ':' Type ',' Declarations .*)
  DEC (yyStackPtr, 5); yyNonterminal := 70;
(* line 455 of "pumagenParser.lalr" *)
   Warning ( "VAR needed" , yyAttributeStack^[yyStackPtr+1].Scan.Position ) ;  
                yySynAttribute.Declarations.Tree := mParam 
                     ( FALSE , yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident , yyAttributeStack^[yyStackPtr+1].Scan.Position , yyAttributeStack^[yyStackPtr+3].Type.Tree
                     , yyAttributeStack^[yyStackPtr+5].Declarations.Tree
                     ) ;
              ;
    
            ;
  
  | 327: (* Declarations : 'VAR' Ident ':' Type .*)
  DEC (yyStackPtr, 4); yyNonterminal := 70;
(* line 464 of "pumagenParser.lalr" *)
   yySynAttribute.Declarations.Tree := mParam (FALSE, yyAttributeStack^[yyStackPtr+2].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Type.Tree, nNoParameter);
   ;
  
  | 328,279: (* Declarations : 'VAR' Ident ':' Type ',' Declarations .*)
  DEC (yyStackPtr, 6); yyNonterminal := 70;
(* line 467 of "pumagenParser.lalr" *)
   yySynAttribute.Declarations.Tree := mParam (FALSE, yyAttributeStack^[yyStackPtr+2].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+4].Type.Tree, yyAttributeStack^[yyStackPtr+6].Declarations.Tree);
   ;
  
  | 329: (* Type : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 68;
(* line 470 of "pumagenParser.lalr" *)
   yySynAttribute.Type.Tree := mType (yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+1].Scan.Position, nNoName);
   ;
  
  | 330,261: (* Type : Ident '.' Name0 .*)
  DEC (yyStackPtr, 3); yyNonterminal := 68;
(* line 473 of "pumagenParser.lalr" *)
   yySynAttribute.Type.Tree := mType (yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+1].Scan.Position, mName (yyAttributeStack^[yyStackPtr+3].Name0.Id, yyAttributeStack^[yyStackPtr+3].Name0.Position, nNoName));
   ;
  
  | 331,202: (* Type : '[' Names ']' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 68;
(* line 476 of "pumagenParser.lalr" *)
   yySynAttribute.Type.Tree := mType (NoIdent, yyAttributeStack^[yyStackPtr+1].Scan.Position, ReverseTree (yyAttributeStack^[yyStackPtr+2].Names.Tree));
   ;
  
  | 332,201: (* Type : Ident '.' '[' Names ']' .*)
  DEC (yyStackPtr, 5); yyNonterminal := 68;
(* line 479 of "pumagenParser.lalr" *)
   yySynAttribute.Type.Tree := mType (yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident, yyAttributeStack^[yyStackPtr+1].Scan.Position, ReverseTree (yyAttributeStack^[yyStackPtr+4].Names.Tree));
   ;
  
  | 333: (* LocalCode : .*)
yyNonterminal := 66;
(* line 482 of "pumagenParser.lalr" *)
   MakeText (yySynAttribute.LocalCode.Text); ;
   yySynAttribute.LocalCode.Position := NoPosition;
   ;
  
  | 334,266: (* LocalCode : 'LOCAL' TargetBlock xx140 .*)
  DEC (yyStackPtr, 3); yyNonterminal := 66;
(* line 486 of "pumagenParser.lalr" *)
   yySynAttribute.LocalCode := yyAttributeStack^[yyStackPtr+3].LocalCode;
  yySynAttribute.LocalCode.Position := yyAttributeStack^[yyStackPtr+2].Scan.Position;
  
  | 335: (* xx140 : .*)
yyNonterminal := 71;
(* line 489 of "pumagenParser.lalr" *)
  yySynAttribute.LocalCode.Text := yyAttributeStack^[yyStackPtr+0].Scan.TargetBlock.Text;
  
  | 336: (* Rules : .*)
yyNonterminal := 67;
(* line 491 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := nNoRule;
   ;
  
  | 337,236: (* Rules : Rules SetLine Patterns2 '.' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 67;
(* line 494 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns2.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+4].Scan.Position),
                     mNoExpr (yyAttributeStack^[yyStackPtr+4].Scan.Position), nNoStatement, yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 338,250: (* Rules : Rules SetLine Patterns '?' Statements '.' .*)
  DEC (yyStackPtr, 6); yyNonterminal := 67;
(* line 498 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+6].Scan.Position),
                     mNoExpr (yyAttributeStack^[yyStackPtr+6].Scan.Position), ReverseTree (yyAttributeStack^[yyStackPtr+5].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 339,237: (* Rules : Rules SetLine Patterns '=>' Exprs2 '.' .*)
  DEC (yyStackPtr, 6); yyNonterminal := 67;
(* line 502 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, yyAttributeStack^[yyStackPtr+5].Exprs2.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+6].Scan.Position),
                     nNoStatement, yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 340,254: (* Rules : Rules SetLine Patterns RETURN Expr ';' '.' .*)
  DEC (yyStackPtr, 7); yyNonterminal := 67;
(* line 506 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+7].Scan.Position), yyAttributeStack^[yyStackPtr+5].Expr.Tree,
                     nNoStatement, yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 341,238: (* Rules : Rules SetLine Patterns '=>' Exprs '?' Statements '.' .*)
  DEC (yyStackPtr, 8); yyNonterminal := 67;
(* line 510 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, yyAttributeStack^[yyStackPtr+5].Exprs.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+8].Scan.Position),
                     ReverseTree (yyAttributeStack^[yyStackPtr+7].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 342,251: (* Rules : Rules SetLine Patterns '?' Statements '=>' Exprs2 '.' .*)
  DEC (yyStackPtr, 8); yyNonterminal := 67;
(* line 514 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, yyAttributeStack^[yyStackPtr+7].Exprs2.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+8].Scan.Position),
                     ReverseTree (yyAttributeStack^[yyStackPtr+5].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 343,248: (* Rules : Rules SetLine Patterns '=>' Exprs RETURN Expr ';' '.' .*)
  DEC (yyStackPtr, 9); yyNonterminal := 67;
(* line 518 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, yyAttributeStack^[yyStackPtr+5].Exprs.Tree, yyAttributeStack^[yyStackPtr+7].Expr.Tree,
                     nNoStatement, yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 344,255: (* Rules : Rules SetLine Patterns RETURN Expr OptSemiColon '?' Statements '.' .*)
  DEC (yyStackPtr, 9); yyNonterminal := 67;
(* line 522 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+9].Scan.Position), yyAttributeStack^[yyStackPtr+5].Expr.Tree,
                     ReverseTree (yyAttributeStack^[yyStackPtr+8].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 345,253: (* Rules : Rules SetLine Patterns '?' Statements RETURN Expr ';' '.' .*)
  DEC (yyStackPtr, 9); yyNonterminal := 67;
(* line 526 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, mNoExpr (yyAttributeStack^[yyStackPtr+9].Scan.Position), yyAttributeStack^[yyStackPtr+7].Expr.Tree,
                     ReverseTree (yyAttributeStack^[yyStackPtr+5].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 346,249: (* Rules : Rules SetLine Patterns '=>' Exprs RETURN Expr OptSemiColon '?' Statements '.' .*)
  DEC (yyStackPtr, 11); yyNonterminal := 67;
(* line 530 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, yyAttributeStack^[yyStackPtr+5].Exprs.Tree, yyAttributeStack^[yyStackPtr+7].Expr.Tree,
                     ReverseTree (yyAttributeStack^[yyStackPtr+10].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 347,244: (* Rules : Rules SetLine Patterns '=>' Exprs '?' Statements RETURN Expr ';' '.' .*)
  DEC (yyStackPtr, 11); yyNonterminal := 67;
(* line 534 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, yyAttributeStack^[yyStackPtr+5].Exprs.Tree, yyAttributeStack^[yyStackPtr+9].Expr.Tree,
                     ReverseTree (yyAttributeStack^[yyStackPtr+7].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 348,252: (* Rules : Rules SetLine Patterns '?' Statements '=>' Exprs RETURN Expr ';' '.' .*)
  DEC (yyStackPtr, 11); yyNonterminal := 67;
(* line 538 of "pumagenParser.lalr" *)
   yySynAttribute.Rules.Tree := mRules (Line, yyAttributeStack^[yyStackPtr+3].Patterns.Tree, yyAttributeStack^[yyStackPtr+7].Exprs.Tree, yyAttributeStack^[yyStackPtr+9].Expr.Tree,
                     ReverseTree (yyAttributeStack^[yyStackPtr+5].Statements.Tree), yyAttributeStack^[yyStackPtr+1].Rules.Tree);
   ;
  
  | 349: (* SetLine : .*)
yyNonterminal := 72;
(* line 542 of "pumagenParser.lalr" *)
   ;
   Line := Attribute.Position; ;
   ;
  
  | 350: (* OptSemiColon : .*)
yyNonterminal := 62;

  | 351,192: (* OptSemiColon : ';' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 62;

  | 352: (* Patterns : Exprs .*)
  DEC (yyStackPtr, 1); yyNonterminal := 74;
(* line 548 of "pumagenParser.lalr" *)
   yySynAttribute.Patterns.Tree := mOnePatternsList (yyAttributeStack^[yyStackPtr+1].Exprs.Tree, nNoPatternsList);
   ;
  
  | 353,282: (* Patterns : Exprs ';' Patterns .*)
  DEC (yyStackPtr, 3); yyNonterminal := 74;
(* line 551 of "pumagenParser.lalr" *)
   yySynAttribute.Patterns.Tree := mOnePatternsList (yyAttributeStack^[yyStackPtr+1].Exprs.Tree, yyAttributeStack^[yyStackPtr+3].Patterns.Tree);
   ;
  
  | 354: (* Patterns2 : Exprs ';' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 73;
(* line 554 of "pumagenParser.lalr" *)
   yySynAttribute.Patterns2.Tree := mOnePatternsList (yyAttributeStack^[yyStackPtr+1].Exprs.Tree, nNoPatternsList);
   ;
  
  | 355,281: (* Patterns2 : Exprs ';' Patterns2 .*)
  DEC (yyStackPtr, 3); yyNonterminal := 73;
(* line 557 of "pumagenParser.lalr" *)
   yySynAttribute.Patterns2.Tree := mOnePatternsList (yyAttributeStack^[yyStackPtr+1].Exprs.Tree, yyAttributeStack^[yyStackPtr+3].Patterns2.Tree);
   ;
  
  | 356: (* Exprs : '..' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 78;
(* line 560 of "pumagenParser.lalr" *)
   yySynAttribute.Exprs.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 357,225: (* Exprs : '..' ',' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 78;
(* line 563 of "pumagenParser.lalr" *)
   yySynAttribute.Exprs.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 358: (* Exprs : Expr .*)
  DEC (yyStackPtr, 1); yyNonterminal := 78;
(* line 566 of "pumagenParser.lalr" *)
   yySynAttribute.Exprs.Tree := mOneExpr (yyAttributeStack^[yyStackPtr+1].Expr.Tree, mNoExpr (Attribute.Position));
   ;
  
  | 359,271: (* Exprs : Expr ',' Exprs .*)
  DEC (yyStackPtr, 3); yyNonterminal := 78;
(* line 569 of "pumagenParser.lalr" *)
   yySynAttribute.Exprs.Tree := mOneExpr (yyAttributeStack^[yyStackPtr+1].Expr.Tree, yyAttributeStack^[yyStackPtr+3].Exprs.Tree);
   ;
  
  | 360,272: (* Exprs : NamedExprs .*)
  DEC (yyStackPtr, 1); yyNonterminal := 78;
(* line 572 of "pumagenParser.lalr" *)
  yySynAttribute.Exprs.Tree := yyAttributeStack^[yyStackPtr+1].NamedExprs.Tree;
  
  | 361: (* NamedExprs : .*)
yyNonterminal := 79;
(* line 574 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs.Tree := mNoExpr (Attribute.Position);
   ;
  
  | 362: (* NamedExprs : '..' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 79;
(* line 577 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 363,235: (* NamedExprs : '..' ',' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 79;
(* line 580 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 364: (* NamedExprs : Ident ':=' Expr .*)
  DEC (yyStackPtr, 3); yyNonterminal := 79;
(* line 583 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs.Tree 
                := mNamedExpr 
                     ( yyAttributeStack^[yyStackPtr+3].Expr.Tree
                     , mNoExpr ( Attribute . Position )
                     , yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident
                     , yyAttributeStack^[yyStackPtr+1].Scan.Position 
                     ) ;
   
            ;
  
  | 365,275: (* NamedExprs : Ident ':=' Expr ',' NamedExprs .*)
  DEC (yyStackPtr, 5); yyNonterminal := 79;
(* line 593 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs.Tree 
                := mNamedExpr 
                     ( yyAttributeStack^[yyStackPtr+3].Expr.Tree
                     , yyAttributeStack^[yyStackPtr+5].NamedExprs.Tree
                     , yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident
                     , yyAttributeStack^[yyStackPtr+1].Scan.Position 
                     ) ;
   
            ;
  
  | 366: (* Exprs2 : '..' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 76;
(* line 603 of "pumagenParser.lalr" *)
   yySynAttribute.Exprs2.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 367: (* Exprs2 : '..' ',' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 76;
(* line 606 of "pumagenParser.lalr" *)
   yySynAttribute.Exprs2.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 368,277: (* Exprs2 : Expr ',' Exprs2 .*)
  DEC (yyStackPtr, 3); yyNonterminal := 76;
(* line 609 of "pumagenParser.lalr" *)
   yySynAttribute.Exprs2.Tree := mOneExpr (yyAttributeStack^[yyStackPtr+1].Expr.Tree, yyAttributeStack^[yyStackPtr+3].Exprs2.Tree);
   ;
  
  | 369,278: (* Exprs2 : NamedExprs2 .*)
  DEC (yyStackPtr, 1); yyNonterminal := 76;
(* line 612 of "pumagenParser.lalr" *)
  yySynAttribute.Exprs2.Tree := yyAttributeStack^[yyStackPtr+1].NamedExprs2.Tree;
  
  | 370: (* NamedExprs2 : .*)
yyNonterminal := 80;
(* line 614 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs2.Tree := mNoExpr (Attribute.Position);
   ;
  
  | 371: (* NamedExprs2 : '..' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 80;
(* line 617 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs2.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 372: (* NamedExprs2 : '..' ',' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 80;
(* line 620 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs2.Tree := mOneExpr (mDontCareExplicit (yyAttributeStack^[yyStackPtr+1].Scan.Position), mNoExpr (Attribute.Position));
   ;
  
  | 373,276: (* NamedExprs2 : Ident ':=' Expr ',' NamedExprs2 .*)
  DEC (yyStackPtr, 5); yyNonterminal := 80;
(* line 623 of "pumagenParser.lalr" *)
   yySynAttribute.NamedExprs2.Tree 
                := mNamedExpr 
                     ( yyAttributeStack^[yyStackPtr+3].Expr.Tree 
                     , yyAttributeStack^[yyStackPtr+5].NamedExprs2.Tree
                     , yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident
                     , yyAttributeStack^[yyStackPtr+1].Scan.Position 
                     ) ;
   
            ;
  
  | 374,273: (* Expr : PrefixExpr .*)
  DEC (yyStackPtr, 1); yyNonterminal := 77;
(* line 633 of "pumagenParser.lalr" *)
  yySynAttribute.Expr.Tree := yyAttributeStack^[yyStackPtr+1].PrefixExpr.Tree;
  
  | 375,270: (* Expr : Expr Operator PrefixExpr .*)
  DEC (yyStackPtr, 3); yyNonterminal := 77;
(* line 635 of "pumagenParser.lalr" *)
   yySynAttribute.Expr.Tree 
                := mBinary 
                     ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+1].Expr.Tree
                     , yyAttributeStack^[yyStackPtr+2].Scan.Operator.Ident
                     , yyAttributeStack^[yyStackPtr+3].PrefixExpr.Tree
                     ,  FALSE 
                     ) ;
   
            ;
  
  | 376,268: (* Expr : Expr Operator CompoundOperator PrefixExpr .*)
  DEC (yyStackPtr, 4); yyNonterminal := 77;
(* line 647 of "pumagenParser.lalr" *)
   yySynAttribute.Expr.Tree 
                := mBinaryCompound 
                     ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+1].Expr.Tree 
                     , yyAttributeStack^[yyStackPtr+2].Scan.Operator.Ident
                     , yyAttributeStack^[yyStackPtr+4].PrefixExpr.Tree 
                     ,  FALSE 
                     , yyAttributeStack^[yyStackPtr+3].Scan.CompoundOperator.Ident 
                     ) ;
   
            ;
  
  | 377: (* PrefixExpr : PostfixExpr .*)
  DEC (yyStackPtr, 1); yyNonterminal := 81;
(* line 660 of "pumagenParser.lalr" *)
  yySynAttribute.PrefixExpr.Tree := yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree;
  
  | 378: (* PrefixExpr : Ident ':' PostfixExpr .*)
  DEC (yyStackPtr, 3); yyNonterminal := 81;
(* line 662 of "pumagenParser.lalr" *)
   yySynAttribute.PrefixExpr.Tree := yyAttributeStack^[yyStackPtr+3].PostfixExpr.Tree ;
                     IF IsType ( yySynAttribute.PrefixExpr.Tree , DontCare1 ) 
                     THEN  
                       yySynAttribute.PrefixExpr.Tree ^ . DontCare1 . Selector := yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident ;
                     ELSIF IsType ( yySynAttribute.PrefixExpr.Tree , Expr ) 
                     THEN 
                       yySynAttribute.PrefixExpr.Tree ^ . Expr . Selector := yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident ;
                     ELSE 
                       CantHappenPos 
                         ( "Parser, Label on bad subtree." 
                         , yyAttributeStack^[yyStackPtr+2].Scan.Position 
                         ) 
                     END  ;   
                   ;
   
            ;
  
  | 379: (* PrefixExpr : Ident ':>' PostfixExpr .*)
  DEC (yyStackPtr, 3); yyNonterminal := 81;
(* line 679 of "pumagenParser.lalr" *)
   yySynAttribute.PrefixExpr.Tree := yyAttributeStack^[yyStackPtr+3].PostfixExpr.Tree ;
                     IF IsType ( yySynAttribute.PrefixExpr.Tree , DontCare1 ) 
                     THEN  
                       yySynAttribute.PrefixExpr.Tree ^ . DontCare1 . Selector := yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident ;
                     ELSIF IsType ( yySynAttribute.PrefixExpr.Tree , Expr ) 
                     THEN 
                       yySynAttribute.PrefixExpr.Tree ^ . Expr . Selector := yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident ;
                     ELSE 
                       CantHappenPos 
                         ( "Parser, Label on bad subtree." 
                         , yyAttributeStack^[yyStackPtr+2].Scan.Position 
                         ) 
                     END  ;   
                     CASE yySynAttribute.PrefixExpr.Tree ^ . Kind 
                     OF Compose : yySynAttribute.PrefixExpr.Tree ^ . Compose . Widen := TRUE
                     | Nil : yySynAttribute.PrefixExpr.Tree ^ . Nil . Widen := TRUE 
                     | VarUse : yySynAttribute.PrefixExpr.Tree ^ . VarUse . Widen := TRUE 
                     | Binary : yySynAttribute.PrefixExpr.Tree ^ . Binary . Widen := TRUE 
                     | BinaryCompound : yySynAttribute.PrefixExpr.Tree ^ . Binary . Widen := TRUE 
                     | Index : yySynAttribute.PrefixExpr.Tree ^ . Index . Widen := TRUE 
                     ELSE 
                     END  
                   ;
   
            ;
  
  | 380,274: (* PrefixExpr : Operator PrefixExpr .*)
  DEC (yyStackPtr, 2); yyNonterminal := 81;
(* line 705 of "pumagenParser.lalr" *)
   yySynAttribute.PrefixExpr.Tree 
                := mPreOperator 
                     ( yyAttributeStack^[yyStackPtr+1].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+1].Scan.Operator.Ident
                     , yyAttributeStack^[yyStackPtr+2].PrefixExpr.Tree
                     ) ;
   
            ;
  
  | 381,267: (* PrefixExpr : IncOperator PrefixExpr .*)
  DEC (yyStackPtr, 2); yyNonterminal := 81;
(* line 715 of "pumagenParser.lalr" *)
   yySynAttribute.PrefixExpr.Tree 
                := mPreOperator 
                     ( yyAttributeStack^[yyStackPtr+1].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+1].Scan.IncOperator.Ident
                     , yyAttributeStack^[yyStackPtr+2].PrefixExpr.Tree
                     ) ;
   
            ;
  
  | 382,269: (* PostfixExpr : PrimaryExpr .*)
  DEC (yyStackPtr, 1); yyNonterminal := 82;
(* line 725 of "pumagenParser.lalr" *)
  yySynAttribute.PostfixExpr.Tree := yyAttributeStack^[yyStackPtr+1].PrimaryExpr.Tree;
  
  | 383,233: (* PostfixExpr : '[' Exprs ']' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 82;
(* line 727 of "pumagenParser.lalr" *)
   yySynAttribute.PostfixExpr.Tree 
                := mIndex 
                     ( yyAttributeStack^[yyStackPtr+1].Scan.Position
                     ,  NoIdent
                     , mVarUse ( NoPosition , NoIdent , NoIdent , FALSE ) 
                     , yyAttributeStack^[yyStackPtr+2].Exprs.Tree
                     ,  FALSE 
                     ) ;
   
            ;
  
  | 384,231: (* PostfixExpr : PostfixExpr '[' Exprs ']' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 82;
(* line 738 of "pumagenParser.lalr" *)
   yySynAttribute.PostfixExpr.Tree 
                := mIndex 
                     ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                     , yyAttributeStack^[yyStackPtr+3].Exprs.Tree
                     ,  FALSE 
                     ) ;
   
            ;
  
  | 385,226: (* PostfixExpr : PostfixExpr '.' '[' Exprs ']' .*)
  DEC (yyStackPtr, 5); yyNonterminal := 82;
(* line 749 of "pumagenParser.lalr" *)
   yySynAttribute.PostfixExpr.Tree 
                := mIndex 
                     ( yyAttributeStack^[yyStackPtr+3].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                     , yyAttributeStack^[yyStackPtr+4].Exprs.Tree
                     ,  FALSE 
                     ) ;
   
            ;
  
  | 386,228: (* PostfixExpr : PostfixExpr '(' ')' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 82;
(* line 760 of "pumagenParser.lalr" *)
   yySynAttribute.PostfixExpr.Tree 
                := mCompose 
                     ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                     ,  NoIdent 
                     , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                     , mNoExpr ( yyAttributeStack^[yyStackPtr+2].Scan.Position ) 
                     ,  FALSE 
                     ) ;
   
            ;
  
  | 387,230: (* PostfixExpr : PostfixExpr '(' Exprs ')' .*)
  DEC (yyStackPtr, 4); yyNonterminal := 82;
(* line 771 of "pumagenParser.lalr" *)
   yySynAttribute.PostfixExpr.Tree 
                := mCompose 
                     ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                     ,  NoIdent 
                     , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                     , yyAttributeStack^[yyStackPtr+3].Exprs.Tree
                     ,  FALSE 
                     ) ;
   
            ;
  
  | 388,229: (* PostfixExpr : PostfixExpr '(' Exprs '=>' Exprs ')' .*)
  DEC (yyStackPtr, 6); yyNonterminal := 82;
(* line 782 of "pumagenParser.lalr" *)
   yySynAttribute.PostfixExpr.Tree 
                := mCall 
                     ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                     , yyAttributeStack^[yyStackPtr+3].Exprs.Tree
                     , yyAttributeStack^[yyStackPtr+5].Exprs.Tree
                     ) ;
   
            ;
  
  | 389,224: (* PostfixExpr : PostfixExpr '.' Ident .*)
  DEC (yyStackPtr, 3); yyNonterminal := 82;
(* line 793 of "pumagenParser.lalr" *)
   ArrayToString ( "." , String1 ) ;
                     yySynAttribute.PostfixExpr.Tree 
                       := mBinary 
                            ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                            ,  NoIdent
                            , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree 
                            , MakeIdent (String1)
                            , mVarUse 
                                ( yyAttributeStack^[yyStackPtr+3].Scan.Position 
                                ,  NoIdent 
                                , yyAttributeStack^[yyStackPtr+3].Scan.Ident.Ident
                                ,  FALSE
                                )
                            ,  FALSE 
                            ) ; 
                   ;
   
            ;
  
  | 390,227: (* PostfixExpr : PostfixExpr '->' Ident .*)
  DEC (yyStackPtr, 3); yyNonterminal := 82;
(* line 812 of "pumagenParser.lalr" *)
   ArrayToString  ( "->" , String1 ) ;
                     yySynAttribute.PostfixExpr.Tree 
                       := mBinary 
                            ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                            ,  NoIdent
                            , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                            , MakeIdent ( String1 )
                            , mVarUse 
                                ( yyAttributeStack^[yyStackPtr+3].Scan.Position
                                ,  NoIdent 
                                , yyAttributeStack^[yyStackPtr+3].Scan.Ident.Ident
                                ,  FALSE
                                )
                            ,  FALSE 
                            ) ; 
                   ;
   
            ;
  
  | 391,232: (* PostfixExpr : PostfixExpr '^' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 82;
(* line 831 of "pumagenParser.lalr" *)
   ArrayToString ( "^" , String1 ) ;
                     yySynAttribute.PostfixExpr.Tree 
                       := mPostOperator 
                            ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                            ,  NoIdent
                            , MakeIdent ( String1 )
                            , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                            ) ; 
                    ;
   
            ;
  
  | 392,223: (* PostfixExpr : PostfixExpr IncOperator .*)
  DEC (yyStackPtr, 2); yyNonterminal := 82;
(* line 843 of "pumagenParser.lalr" *)
   yySynAttribute.PostfixExpr.Tree 
                := mPostOperator 
                     ( yyAttributeStack^[yyStackPtr+2].Scan.Position
                     ,  NoIdent
                     , yyAttributeStack^[yyStackPtr+2].Scan.IncOperator.Ident
                     , yyAttributeStack^[yyStackPtr+1].PostfixExpr.Tree
                     ) ;
   
            ;
  
  | 393: (* PrimaryExpr : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 83;
(* line 853 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree := mVarUse (yyAttributeStack^[yyStackPtr+1].Scan.Position, NoIdent, yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident, FALSE );
   ;
  
  | 394,205: (* PrimaryExpr : Ident ':' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 83;
(* line 856 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree := mVarUse (yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident, NoIdent, FALSE );
   ;
  
  | 395,206: (* PrimaryExpr : Ident ':>' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 83;
(* line 859 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree := mVarUse (yyAttributeStack^[yyStackPtr+1].Scan.Position, yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident, NoIdent, TRUE );
   ;
  
  | 396,209: (* PrimaryExpr : NIL .*)
  DEC (yyStackPtr, 1); yyNonterminal := 83;
(* line 862 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree := mNil ( yyAttributeStack^[yyStackPtr+1].Scan.Position , NoIdent , FALSE ) ;
   ;
  
  | 397,210: (* PrimaryExpr : '_' .*)
  DEC (yyStackPtr, 1); yyNonterminal := 83;
(* line 865 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree := mDontCare1Explicit ( yyAttributeStack^[yyStackPtr+1].Scan.Position , NoIdent ) ;
   ;
  
  | 398,208: (* PrimaryExpr : Number .*)
  DEC (yyStackPtr, 1); yyNonterminal := 83;
(* line 868 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree 
                := mTargetExpr 
                     ( yyAttributeStack^[yyStackPtr+1].Scan.Position
                     , mAny ( yyAttributeStack^[yyStackPtr+1].Scan.Number.StringRef , nNoDesignator )
                     ) 
          ;
   ;
  
  | 399,207: (* PrimaryExpr : String .*)
  DEC (yyStackPtr, 1); yyNonterminal := 83;
(* line 876 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree 
                := mStringExpr 
                     ( yyAttributeStack^[yyStackPtr+1].Scan.Position 
                     ,  NoIdent 
                     , yyAttributeStack^[yyStackPtr+1].Scan.String.StringRef 
                     ) ;
   
            ;
  
  | 400,204: (* PrimaryExpr : Ident '::' Ident .*)
  DEC (yyStackPtr, 3); yyNonterminal := 83;
(* line 885 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree 
                := mAttrDesc 
                     ( yyAttributeStack^[yyStackPtr+1].Scan.Position
                     ,  NoIdent 
                     , yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident
                     ,  FALSE
                     , yyAttributeStack^[yyStackPtr+3].Scan.Ident.Ident
                     , yyAttributeStack^[yyStackPtr+3].Scan.Position
                     ) ;
   
            ;
  
  | 401,221: (* PrimaryExpr : '{' TargetCodes '}' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 83;
(* line 897 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree 
                := mTargetExpr 
                     ( yyAttributeStack^[yyStackPtr+1].Scan.Position
                     , ReverseTree ( yyAttributeStack^[yyStackPtr+2].TargetCodes.Tree )
                     );
   
            ;
  
  | 402,234: (* PrimaryExpr : '(' Expr ')' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 83;
(* line 905 of "pumagenParser.lalr" *)
   yySynAttribute.PrimaryExpr.Tree 
                 := mParents 
                      ( yyAttributeStack^[yyStackPtr+1].Scan.Position ,  NoIdent , yyAttributeStack^[yyStackPtr+2].Expr.Tree ) ;
   
            ;
  
  | 403: (* Statements : .*)
yyNonterminal := 75;
(* line 911 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := nNoStatement;
   ;
  
  | 404,246: (* Statements : Statements Expr ';' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 75;
(* line 914 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := mProcCall (yyAttributeStack^[yyStackPtr+2].Expr.Tree^.Expr.Pos, yyAttributeStack^[yyStackPtr+1].Statements.Tree, yyAttributeStack^[yyStackPtr+2].Expr.Tree);
   ;
  
  | 405,247: (* Statements : Statements Expr ':=' Expr ';' .*)
  DEC (yyStackPtr, 5); yyNonterminal := 75;
(* line 917 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := mAssignment (yyAttributeStack^[yyStackPtr+3].Scan.Position, yyAttributeStack^[yyStackPtr+1].Statements.Tree, yyAttributeStack^[yyStackPtr+2].Expr.Tree, yyAttributeStack^[yyStackPtr+4].Expr.Tree);
   ;
  
  | 406,241: (* Statements : Statements REJECT .*)
  DEC (yyStackPtr, 2); yyNonterminal := 75;
(* line 920 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := mReject (yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+1].Statements.Tree);
   ;
  
  | 407,242: (* Statements : Statements FAIL .*)
  DEC (yyStackPtr, 2); yyNonterminal := 75;
(* line 923 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := mFail (yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+1].Statements.Tree);
   ;
  
  | 408,245: (* Statements : Statements Declarations ';' .*)
  DEC (yyStackPtr, 3); yyNonterminal := 75;
(* line 926 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := mTargetStmt (yyAttributeStack^[yyStackPtr+2].Declarations.Tree^.Param.Pos, yyAttributeStack^[yyStackPtr+1].Statements.Tree, yyAttributeStack^[yyStackPtr+2].Declarations.Tree, nNoDesignator);
   ;
  
  | 409,240: (* Statements : Statements '{' TargetCodes '}' ';' .*)
  DEC (yyStackPtr, 5); yyNonterminal := 75;
(* line 929 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := mTargetStmt (yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+1].Statements.Tree, nNoParameter, ReverseTree (yyAttributeStack^[yyStackPtr+3].TargetCodes.Tree));
   ;
  
  | 410,243: (* Statements : Statements NL .*)
  DEC (yyStackPtr, 2); yyNonterminal := 75;
(* line 932 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree := mNl (yyAttributeStack^[yyStackPtr+2].Scan.Position, yyAttributeStack^[yyStackPtr+1].Statements.Tree);
   ;
  
  | 411,239: (* Statements : Statements ';' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 75;
(* line 935 of "pumagenParser.lalr" *)
   yySynAttribute.Statements.Tree  :=  yyAttributeStack^[yyStackPtr+1].Statements.Tree;
   ;
  
  | 412: (* TargetCodes : .*)
yyNonterminal := 84;
(* line 938 of "pumagenParser.lalr" *)
   yySynAttribute.TargetCodes.Tree := nNoDesignator;
   ;
  
  | 413,222: (* TargetCodes : TargetCodes Name1 Space '::' Space Ident .*)
  DEC (yyStackPtr, 6); yyNonterminal := 84;
(* line 941 of "pumagenParser.lalr" *)
   yySynAttribute.TargetCodes.Tree 
                := mDesignator 
                     ( yyAttributeStack^[yyStackPtr+2].Name1.Id 
                     , yyAttributeStack^[yyStackPtr+6].Scan.Ident.Ident 
                     , yyAttributeStack^[yyStackPtr+2].Name1.Position
                     , yyAttributeStack^[yyStackPtr+6].Scan.Position
                     , yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree
                     ) ;
   
            ;
  
  | 414: (* TargetCodes : TargetCodes Name1 Space '::' Space .*)
  DEC (yyStackPtr, 5); yyNonterminal := 84;
(* line 952 of "pumagenParser.lalr" *)
  
              yySynAttribute.TargetCodes.Tree := mIdent (yyAttributeStack^[yyStackPtr+2].Name1.Id, yyAttributeStack^[yyStackPtr+2].Name1.Position, yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree);
              yySynAttribute.TargetCodes.Tree := mAnys (ReverseTree (yyAttributeStack^[yyStackPtr+3].Space.Tree), yySynAttribute.TargetCodes.Tree);
              yySynAttribute.TargetCodes.Tree := mAny (yyAttributeStack^[yyStackPtr+4].Scan.yy10.StringRef, yySynAttribute.TargetCodes.Tree);
              yySynAttribute.TargetCodes.Tree := mAnys (ReverseTree (yyAttributeStack^[yyStackPtr+5].Space.Tree), yySynAttribute.TargetCodes.Tree); ;
   ;
  
  | 415,216: (* TargetCodes : TargetCodes '.' Space Ident .*)
  DEC (yyStackPtr, 4); yyNonterminal := 84;
(* line 959 of "pumagenParser.lalr" *)
  
              yySynAttribute.TargetCodes.Tree := mAny (yyAttributeStack^[yyStackPtr+2].Scan.yy11.StringRef, yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree); 
              yySynAttribute.TargetCodes.Tree := mAnys (ReverseTree (yyAttributeStack^[yyStackPtr+3].Space.Tree), yySynAttribute.TargetCodes.Tree);
              yySynAttribute.TargetCodes.Tree := mAny ( GetStringRef ( yyAttributeStack^[yyStackPtr+4].Scan.Ident.Ident ) , yySynAttribute.TargetCodes.Tree); 
            ;
   ;
  
  | 416,217: (* TargetCodes : TargetCodes '.' Space TargetCode .*)
  DEC (yyStackPtr, 4); yyNonterminal := 84;
(* line 966 of "pumagenParser.lalr" *)
   
                yySynAttribute.TargetCodes.Tree := mAny ( yyAttributeStack^[yyStackPtr+2].Scan.yy11.StringRef , yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree ) ;  
                yySynAttribute.TargetCodes.Tree := mAnys (ReverseTree (yyAttributeStack^[yyStackPtr+3].Space.Tree), yySynAttribute.TargetCodes.Tree);
                yySynAttribute.TargetCodes.Tree := mAny ( yyAttributeStack^[yyStackPtr+4].Scan.TargetCode.StringRef , yySynAttribute.TargetCodes.Tree ) ; 
              ;
   
            ;
  
  | 417,219: (* TargetCodes : TargetCodes '->' Space Ident .*)
  DEC (yyStackPtr, 4); yyNonterminal := 84;
(* line 974 of "pumagenParser.lalr" *)
  
              yySynAttribute.TargetCodes.Tree := mAny (yyAttributeStack^[yyStackPtr+2].Scan.yy12.StringRef, yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree); 
              yySynAttribute.TargetCodes.Tree := mAnys (ReverseTree (yyAttributeStack^[yyStackPtr+3].Space.Tree), yySynAttribute.TargetCodes.Tree);
              yySynAttribute.TargetCodes.Tree := mAny ( GetStringRef ( yyAttributeStack^[yyStackPtr+4].Scan.Ident.Ident ) , yySynAttribute.TargetCodes.Tree); 
            ;
   ;
  
  | 418,220: (* TargetCodes : TargetCodes '->' Space TargetCode .*)
  DEC (yyStackPtr, 4); yyNonterminal := 84;
(* line 981 of "pumagenParser.lalr" *)
   
                yySynAttribute.TargetCodes.Tree := mAny ( yyAttributeStack^[yyStackPtr+2].Scan.yy12.StringRef , yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree ) ;  
                yySynAttribute.TargetCodes.Tree := mAnys (ReverseTree (yyAttributeStack^[yyStackPtr+3].Space.Tree), yySynAttribute.TargetCodes.Tree);
                yySynAttribute.TargetCodes.Tree := mAny ( yyAttributeStack^[yyStackPtr+4].Scan.TargetCode.StringRef , yySynAttribute.TargetCodes.Tree ) ; 
              ;
   
            ;
  
  | 419: (* TargetCodes : TargetCodes Name1 Space .*)
  DEC (yyStackPtr, 3); yyNonterminal := 84;
(* line 989 of "pumagenParser.lalr" *)
  
              yySynAttribute.TargetCodes.Tree := mIdent (yyAttributeStack^[yyStackPtr+2].Name1.Id, yyAttributeStack^[yyStackPtr+2].Name1.Position, yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree);
              yySynAttribute.TargetCodes.Tree := mAnys (ReverseTree (yyAttributeStack^[yyStackPtr+3].Space.Tree), yySynAttribute.TargetCodes.Tree); ;
   ;
  
  | 420,215: (* TargetCodes : TargetCodes '::' .*)
  DEC (yyStackPtr, 2); yyNonterminal := 84;
(* line 994 of "pumagenParser.lalr" *)
   yySynAttribute.TargetCodes.Tree := mAny (yyAttributeStack^[yyStackPtr+2].Scan.yy10.StringRef, yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree);
   ;
  
  | 421,213: (* TargetCodes : TargetCodes TargetCode .*)
  DEC (yyStackPtr, 2); yyNonterminal := 84;
(* line 997 of "pumagenParser.lalr" *)
   yySynAttribute.TargetCodes.Tree := mAny (yyAttributeStack^[yyStackPtr+2].Scan.TargetCode.StringRef, yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree);
   ;
  
  | 422,214: (* TargetCodes : TargetCodes WhiteSpace .*)
  DEC (yyStackPtr, 2); yyNonterminal := 84;
(* line 1000 of "pumagenParser.lalr" *)
   yySynAttribute.TargetCodes.Tree := mAny (yyAttributeStack^[yyStackPtr+2].Scan.WhiteSpace.StringRef, yyAttributeStack^[yyStackPtr+1].TargetCodes.Tree);
   ;
  
  | 423,188: (* Name0 : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 59;
(* line 1003 of "pumagenParser.lalr" *)
   yySynAttribute.Name0.Id           :=  yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident;
  
              yySynAttribute.Name0.Position     :=  yyAttributeStack^[yyStackPtr+1].Scan.Position;
   ;
  
  | 424,189: (* Name0 : String .*)
  DEC (yyStackPtr, 1); yyNonterminal := 59;
(* line 1008 of "pumagenParser.lalr" *)
   GetString (yyAttributeStack^[yyStackPtr+1].Scan.String.StringRef, String1);
                               SubString (String1, 2, Length (String1) - 1, String2);
                               yySynAttribute.Name0.Id := MakeIdent (String2); ;
  
              yySynAttribute.Name0.Position     :=  yyAttributeStack^[yyStackPtr+1].Scan.Position;
   ;
  
  | 425,211: (* Name1 : Ident .*)
  DEC (yyStackPtr, 1); yyNonterminal := 85;
(* line 1015 of "pumagenParser.lalr" *)
   yySynAttribute.Name1.Id   :=  yyAttributeStack^[yyStackPtr+1].Scan.Ident.Ident;
  
              yySynAttribute.Name1.Position     :=  yyAttributeStack^[yyStackPtr+1].Scan.Position;
   ;
  
  | 426,212: (* Name1 : String .*)
  DEC (yyStackPtr, 1); yyNonterminal := 85;
(* line 1020 of "pumagenParser.lalr" *)
   GetString (yyAttributeStack^[yyStackPtr+1].Scan.String.StringRef, String1); yySynAttribute.Name1.Id := MakeIdent (String1); ;
  
              yySynAttribute.Name1.Position     :=  yyAttributeStack^[yyStackPtr+1].Scan.Position;
   ;
  
  | 427: (* Space : .*)
yyNonterminal := 86;
(* line 1025 of "pumagenParser.lalr" *)
   yySynAttribute.Space.Tree := nNoLayout;
   ;
  
  | 428,218: (* Space : Space WhiteSpace .*)
  DEC (yyStackPtr, 2); yyNonterminal := 86;
(* line 1028 of "pumagenParser.lalr" *)
   yySynAttribute.Space.Tree := mLayoutAny (yyAttributeStack^[yyStackPtr+2].Scan.WhiteSpace.StringRef, yyAttributeStack^[yyStackPtr+1].Space.Tree);
   ;
  
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
         yyTerminal := Scanner.GetToken ();
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
      ContinueSet       : IntSets . T;
      RestartSet        : IntSets . T;
      Token             : yySymbolRange;
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
      ContinueSet:= IntSets . Empty ( ) 
      ComputeContinuation (StateStack, StackSize, StackPtr, ContinueSet);
      Strings.AssignEmpty (ContinueString);
      FOR Token := IntSets.Minimum (ContinueSet) TO IntSets.Maximum (ContinueSet) DO
         IF IntSets.IsElement (Token, ContinueSet) THEN
            TokenName (Token, TokenArray);
            Strings.ArrayToString (TokenArray, TokenString);
            IF (Strings.Length (ContinueString) + Strings.Length (TokenString) + 1 <= Strings.cMaxStrLength) THEN
               Strings.Concatenate (ContinueString, TokenString);
               Strings.Append (ContinueString, ' ');
            END;
         END;
      END;
      Errors.ErrorMessageI (Errors.ExpectedTokens, Errors.Information,
      Scanner.Attribute.Position, Errors.String, ADR (ContinueString));
      ContinueSet := NIL;

   (* 3. compute the set of terminal symbols for restart of the parse *)
      RestartSet := IntSets . Empty ( )
      ComputeRestartPoints (StateStack, StackSize, StackPtr, RestartSet);

   (* 4. skip terminal symbols until a restart point is reached *)
      TokensSkipped := FALSE;
      WHILE NOT IntSets.IsElement (Terminal, RestartSet) DO
      Terminal := Scanner.GetToken ();
         TokensSkipped := TRUE;
      END;
      RestartSet := NIL;

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
          StackSize     : INTEGER       ;
          StackPtr      : yyStackPtrType;
      VAR ContinueSet   : IntSets . T     ) =
   VAR Terminal         : yySymbolRange;
   BEGIN
      ContinueSet:= IntSets . Empty ( );
      FOR Terminal := yyFirstTerminal TO yyLastTerminal DO
         IF IsContinuation (Terminal, Stack, StackSize, StackPtr) THEN
            ContinueSet := IntSets . Include ( ContinueSet , Terminal )
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
      Stack := NEW (yyStackTyp , StackSize);
      FOR State := 0 TO StackPtr DO
         Stack^ [State] := ParseStack^ [State];
      END;
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

         LOOP                                           (* reduce *)
            IF State =  yyStopState THEN
               Stack := NIL; 
               RETURN TRUE;
            ELSE 
               DEC (StackPtr, yyLength [State]);
               Nonterminal := yyLeftHandSide [State];
            END;

            State := Next (Stack^ [StackPtr], Nonterminal);
            IF StackPtr >= StackSize THEN
              ExpandStateStack
                (Stack, MAX (NUMBER ( Stack ^ ) * 2 , StackPtr + 2 ) )
              StackSize := NUMBER (Stack^); 
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
          StackSize     : INTEGER       ;
          StackPtr      : yyStackPtrType;
      VAR RestartSet    : IntSets . T     ) =
   VAR
      Stack             : yyStackType;
      State             : yyStackPtrType;
      Nonterminal       : yySymbolRange;
      ContinueSet       : IntSets . T;
   BEGIN
      Stack := NEW (yyStackTyp, StackSize); 
      FOR State := 0 TO StackPtr DO
         Stack^ [State] := ParseStack^ [State];
      END;
      ContinueSet := IntSets . Empty ( )
      State := Stack^ [StackPtr];

      LOOP
         IF StackPtr >= StackSize THEN
            ExpandStateStack
              (Stack, MAX (NUMBER (Stack ^) * 2 , StackPtr + 2 ) )
            StackSize := NUMBER (Stack^); 
         END;
         Stack^ [StackPtr] := State;
         ComputeContinuation (Stack, StackSize, StackPtr, ContinueSet);
         RestartSet := IntSets.Union (RestartSet, ContinueSet);
         State := Next (State, yyContinuation [State]);

         IF State >= yyFirstFinalState THEN             (* final state ? *)
            IF State <= yyLastReadTermState THEN        (* read terminal reduce ? *)
               INC (StackPtr);
               State := yyFinalToProd [State];
            END;

            LOOP                                        (* reduce *)
               IF State = yyStopState THEN
                  Stack := NIL; 
                  ContinueSet := NIL;
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

(* -------------- From rexm3's Parser.m3: -------------------------------*)

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
        (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition)
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

(* --------------------------------------------------------------------- *) 


(* -------------- from lalr's (nearly) original lib/Parser.mi -----------** 
PROCEDURE yyGetTables ( ) = 
   VAR
      BlockSize, j, n   : CARDINAL;
      State     : yyStateRange;
      TBase     : ARRAY (*yyTableElmt*) [0 .. yyLastReadState] OF yyTCombRange;
      NBase     : ARRAY (*yyTableElmt*) [0 .. yyLastReadState] OF yyNCombRange;
   BEGIN
      BlockSize := 64000 DIV BYTESIZE (yyTCombType);
      yyTableFile := System.OpenInput (ParsTabName);
      yyErrorCheck (Errors.OpenParseTable, yyTableFile);
      IF 
         (yyGetTable (ADR (TBase         )) DIV BYTESIZE (yyTCombRange ) - 1
            # yyLastReadState) OR
         (yyGetTable (ADR (NBase         )) DIV BYTESIZE (yyNCombRange ) - 1
            # yyLastReadState) OR
         (yyGetTable (ADR (yyDefault     )) DIV BYTESIZE (yyReadRange  ) - 1
            # yyLastReadState) OR
         (yyGetTable (ADR (yyNComb       )) DIV BYTESIZE (yyNCombType  )
            # yyNTableMax - yyLastTerminal) OR
         (yyGetTable (ADR (yyLength      )) DIV BYTESIZE (yyTableElmt  ) - 1
            # yyLastReduceState - yyFirstReduceState) OR
         (yyGetTable (ADR (yyLeftHandSide)) DIV BYTESIZE (yySymbolRange) - 1
            # yyLastReduceState - yyFirstReduceState) OR
         (yyGetTable (ADR (yyContinuation)) DIV BYTESIZE (yySymbolRange) - 1
            # yyLastReadState) OR
         (yyGetTable (ADR (yyFinalToProd )) DIV BYTESIZE (yyReduceRange) - 1
            # yyLastReadNontermState - yyFirstReadTermState)
      THEN
         Errors.ErrorMessage (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition);
      END;
      n := 0;
      j := 0;
      WHILE j <= yyTableMax DO
         INC (n, yyGetTable (ADR (yyTComb [yyStateRange,j])) DIV BYTESIZE (yyTCombType));
         INC (j, BlockSize);
      END;
      IF n # yyTableMax + 1 THEN 
         Errors.ErrorMessage (Errors.WrongParseTable, Errors.Fatal, Positions.NoPosition);
      END;
      System.Close (yyTableFile);

      FOR State := 1 TO yyLastReadState DO
         yyTBasePtr [State] := ADR (yyTComb [TBase [State]]);
      END;
      FOR State := 1 TO yyLastReadState DO
         yyNBasePtr [State] := ADR (yyNComb [NBase [State]]);
      END;
   END yyGetTables;
**---------------------------------------------------------------------- *) 

PROCEDURE yyGetTable (Address: ADDRESS): Word . T =
   VAR
      N         : INTEGER;
      Length    : yyTableElmt;
      LongLength : Word . T;
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

PROCEDURE BeginParser =
   BEGIN
(* line 217 "pumagenParser.lalr" *)


   BeginScanner;
   NameCount := 0;
   nNoParameter         := mNoParameter         ();
   nNoName              := mNoName              ();
   nNoRule              := mNoRule              ();
   nNoDesignator        := mNoDesignator        ();
   nNoStatement         := mNoStatement         ();
   nNoLayout            := mNoLayout            ();
   nNoPatternsList      := mNoPatternsList      ();


      IF NOT yyIsInitialized THEN
         yyIsInitialized := TRUE;
         yyGetTables;
      END;
   END BeginParser;

(*EXPORTED*)
PROCEDURE CloseParser =
   BEGIN
(* line 231 "pumagenParser.lalr" *)


   END CloseParser;

BEGIN
    yyIsInitialized := FALSE;
    ParsTabName := 'Parser.Tab';
END Parser.
