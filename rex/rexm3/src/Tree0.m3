 UNSAFE MODULE Tree0;



FROM SYSTEM IMPORT BYTE, BITSET, SHORTINT, SHORTCARD, M2LONGINT;
IMPORT Word, SYSTEM, System, General, Memory, DynArray, ReuseIO, Layout, StringMem, Strings, Idents, Texts, Sets, Positions;
(* line 31 "../src/rex.cg" *)

FROM Sets	IMPORT tSet;
FROM Texts	IMPORT tText;
FROM StringMem	IMPORT tStringRef;
FROM Positions	IMPORT tPosition;

CONST yyBlockSize = 20480;

TYPE
 yytBlockPtr   = UNTRACED BRANDED REF  yytBlock;
 yytBlock      = RECORD
                    yyBlock    : ARRAY [1..yyBlockSize] OF CHAR;
                    yySuccessor: yytBlockPtr;
                 END;

VAR yyBlockList        : yytBlockPtr;
VAR yyMaxSize, yyi     : SHORTCARD;
VAR yyTypeRange        : ARRAY [0..13] OF SHORTCARD;

PROCEDURE yyAlloc (): tTree0 =
 VAR yyBlockPtr        : yytBlockPtr;
 BEGIN
  yyBlockPtr   := yyBlockList;
  yyBlockList  := Memory.Alloc (BYTESIZE (yytBlock));
  yyBlockList^.yySuccessor := yyBlockPtr;
  yyPoolFreePtr        := ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 274
 $$ *) (yyBlockList^.yyBlock);
  yyPoolMaxPtr := yyPoolFreePtr + yyBlockSize - yyMaxSize + 1;
  INC (HeapUsed, yyBlockSize);
  RETURN yyPoolFreePtr;
 END yyAlloc;

PROCEDURE MakeTree0 (yyKind: SHORTCARD): tTree0 =
 VAR yyByteCount       : M2LONGINT;
 VAR yyt       : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [yyKind] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 285
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 286
 $$ *) := yyKind;
  RETURN yyt;
 END MakeTree0;

PROCEDURE IsType (yyTree: tTree0; yyKind: SHORTCARD): BOOLEAN =
 BEGIN
  RETURN (yyTree # NoTree0) AND (yyKind <= yyTree^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 292
 $$ *)) AND (yyTree^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 292
 $$ *) <= yyTypeRange [yyKind]);
 END IsType;


PROCEDURE mNode (): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Node] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 301
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 302
 $$ *) := Node;
  WITH m2tom3_with_16=yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 303
 $$ *) DO
    
    
    
    
  END;
  RETURN yyt;
 END mNode;

PROCEDURE mNode1 (pSon1: tTree0): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Node1] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 317
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 318
 $$ *) := Node1;
  WITH m2tom3_with_17=yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 319
 $$ *) DO
    
    
    
    
   m2tom3_with_17.Son1 := pSon1;
  END;
  RETURN yyt;
 END mNode1;

PROCEDURE mOption (pSon1: tTree0): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Option] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 334
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 335
 $$ *) := Option;
  WITH m2tom3_with_18=yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 336
 $$ *) DO
    
    
    
    
   m2tom3_with_18.Son1 := pSon1;
  END;
  RETURN yyt;
 END mOption;

PROCEDURE mRepetition (pSon1: tTree0): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Repetition] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 351
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 352
 $$ *) := Repetition;
  WITH m2tom3_with_19=yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 353
 $$ *) DO
    
    
    
    
   m2tom3_with_19.Son1 := pSon1;
  END;
  RETURN yyt;
 END mRepetition;

PROCEDURE mNode2 (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Node2] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 368
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 369
 $$ *) := Node2;
  WITH m2tom3_with_20=yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 370
 $$ *) DO
    
    
    
    
   m2tom3_with_20.Son1 := pSon1;
   m2tom3_with_20.Son2 := pSon2;
  END;
  RETURN yyt;
 END mNode2;

PROCEDURE mList (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [List] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 386
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 387
 $$ *) := List;
  WITH m2tom3_with_21=yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 388
 $$ *) DO
    
    
    
    
   m2tom3_with_21.Son1 := pSon1;
   m2tom3_with_21.Son2 := pSon2;
  END;
  RETURN yyt;
 END mList;

PROCEDURE mSequence (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Sequence] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 404
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 405
 $$ *) := Sequence;
  WITH m2tom3_with_22=yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 406
 $$ *) DO
    
    
    
    
   m2tom3_with_22.Son1 := pSon1;
   m2tom3_with_22.Son2 := pSon2;
  END;
  RETURN yyt;
 END mSequence;

PROCEDURE mAlternative (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Alternative] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 422
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 423
 $$ *) := Alternative;
  WITH m2tom3_with_23=yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 424
 $$ *) DO
    
    
    
    
   m2tom3_with_23.Son1 := pSon1;
   m2tom3_with_23.Son2 := pSon2;
  END;
  RETURN yyt;
 END mAlternative;

PROCEDURE mCh (pCh: CHAR): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Ch] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 440
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 441
 $$ *) := Ch;
  WITH m2tom3_with_24=yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 442
 $$ *) DO
    
    
    
    
   m2tom3_with_24.Ch := pCh;
  END;
  RETURN yyt;
 END mCh;

PROCEDURE mSet (pSet: tSet): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Set] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 457
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 458
 $$ *) := Set;
  WITH m2tom3_with_25=yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 459
 $$ *) DO
    
    
    
    
   m2tom3_with_25.Set := pSet;
    
  END;
  RETURN yyt;
 END mSet;

PROCEDURE mString (pString: tStringRef): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [String] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 475
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 476
 $$ *) := String;
  WITH m2tom3_with_26=yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 477
 $$ *) DO
    
    
    
    
   m2tom3_with_26.String := pString;
  END;
  RETURN yyt;
 END mString;

PROCEDURE mRule (pPatterns: tTree0; pTargetCode: tText; pLine: SHORTCARD; pCodeMode: SHORTCARD; pRuleNr: SHORTCARD): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Rule] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 492
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 493
 $$ *) := Rule;
  WITH m2tom3_with_27=yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 494
 $$ *) DO
    
    
    
    
   m2tom3_with_27.Patterns := pPatterns;
   m2tom3_with_27.TargetCode := pTargetCode;
   m2tom3_with_27.Line := pLine;
   m2tom3_with_27.CodeMode := pCodeMode;
   m2tom3_with_27.RuleNr := pRuleNr;
  END;
  RETURN yyt;
 END mRule;

PROCEDURE mPattern (pStartStates: tSet; pRegExpr: tTree0; pRightContext: tTree0; pPatternNr: SHORTCARD; pPosition: tPosition): tTree0 =
 VAR yyByteCount    : M2LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Pattern] ); 
  yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 513
 $$ *).yyMark := 0;
  yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 514
 $$ *) := Pattern;
  WITH m2tom3_with_28=yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 515
 $$ *) DO
    
    
    
    
   m2tom3_with_28.StartStates := pStartStates;
   m2tom3_with_28.RegExpr := pRegExpr;
   m2tom3_with_28.RightContext := pRightContext;
   m2tom3_with_28.PatternNr := pPatternNr;
   m2tom3_with_28.Position := pPosition;
    
  END;
  RETURN yyt;
 END mPattern;

TYPE yyPtrtTree        = UNTRACED BRANDED REF  tTree0;

VAR yyf        : ReuseIO.tFile;
VAR yyLabel    : SHORTCARD;
VAR yyKind     : SHORTCARD;
VAR yyc        : CHAR;
VAR yys        : Strings.tString;

PROCEDURE yyMark (yyt: tTree0) =
 BEGIN
  LOOP
   IF yyt = NoTree0 THEN RETURN; END;
   INC (yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 542
 $$ *).yyMark);
   IF yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 543
 $$ *).yyMark > 1 THEN RETURN; END;

   CASE yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 545
 $$ *) OF
| Node1=>
yyt := yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 547
 $$ *).Son1;
| Option=>
yyt := yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 549
 $$ *).Son1;
| Repetition=>
yyt := yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 551
 $$ *).Son1;
| Node2=>
yyMark (yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 553
 $$ *).Son1);
yyt := yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 554
 $$ *).Son2;
| List=>
yyMark (yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 556
 $$ *).Son1);
yyt := yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 557
 $$ *).Son2;
| Sequence=>
yyMark (yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 559
 $$ *).Son1);
yyt := yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 560
 $$ *).Son2;
| Alternative=>
yyMark (yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 562
 $$ *).Son1);
yyt := yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 563
 $$ *).Son2;
| Rule=>
yyt := yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 565
 $$ *).Patterns;
| Pattern=>
yyMark (yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 567
 $$ *).RegExpr);
yyt := yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 568
 $$ *).RightContext;
   ELSE RETURN;
   END;
  END;
 END yyMark;

CONST yyInitTreeStoreSize      = 32;

VAR yyTreeStoreSize    : M2LONGINT;
VAR yyTreeStorePtr     : UNTRACED BRANDED REF  ARRAY [0..50000] OF tTree0;
VAR yyLabelCount       : INTEGER;
VAR yyRecursionLevel   : SHORTINT;

PROCEDURE yyMapToLabel (yyTree: tTree0): SHORTCARD =
 VAR yyi       : INTEGER;
 BEGIN
  FOR yyi := 1 TO yyLabelCount DO
   IF yyTreeStorePtr^[yyi] = yyTree THEN RETURN yyi; END;
  END;
  INC (yyLabelCount);
  IF yyLabelCount = yyTreeStoreSize THEN
   DynArray.ExtendArray (LOOPHOLE(yyTreeStorePtr,ADDRESS), yyTreeStoreSize, BYTESIZE (tTree0));
  END;
  yyTreeStorePtr^[yyLabelCount] := yyTree;
  RETURN yyLabelCount;
 END yyMapToLabel;

PROCEDURE yyMapToTree (yyLabel: SHORTCARD): tTree0 =
 BEGIN RETURN yyTreeStorePtr^[yyLabel]; END yyMapToTree;

PROCEDURE yyWriteNl() = BEGIN ReuseIO.WriteNl (yyf); END yyWriteNl;

PROCEDURE yyWriteSelector (READONLY yys: ARRAY OF CHAR) =
 BEGIN ReuseIO.WriteS (yyf, yys); Layout.WriteSpaces (yyf, 15 - LOOPHOLE (LAST (yys),INTEGER)); ReuseIO.WriteS (yyf, ARRAY [0..3] OF CHAR{' ','=',' ','\000'}); END yyWriteSelector;

PROCEDURE yyWriteHex (VAR yyx: ARRAY OF SYSTEM.BYTE) =
 VAR yyi       : INTEGER;
 BEGIN
  FOR yyi := 0 TO LOOPHOLE (LAST (yyx),INTEGER) DO
   ReuseIO.WriteN (yyf, ORD (LOOPHOLE (yyx [yyi],CHAR)), 2, 16);
   ReuseIO.WriteC (yyf, ' ');
  END;
 END yyWriteHex;

VAR yyIndentLevel      : SHORTINT;
VAR yyActualIndent , yyIndentQuotient , yyIndentRemainder : SHORTINT;
CONST yyIndentFactor = 20; 
PROCEDURE yySetIndentInfo ( ) = 
  BEGIN 
   yyIndentQuotient := yyIndentLevel DIV yyIndentFactor;    yyIndentRemainder := yyIndentLevel MOD yyIndentFactor; 
   yyActualIndent      := VAL (   10 * ORD ( yyIndentQuotient > 0 ),SHORTINT )         + yyIndentRemainder 
  END yySetIndentInfo ; 

PROCEDURE WriteTree0 (yyyf: ReuseIO.tFile; yyt: tTree0) =
 VAR yySaveLevel       : SHORTINT;
 BEGIN
  yyf := yyyf;
  IF yyRecursionLevel = 0 THEN yyLabelCount := 0; END;
  INC (yyRecursionLevel);
  yyMark (yyt);
  yySaveLevel := yyIndentLevel;
  yyIndentLevel := 0;
  yySetIndentInfo ( ) ;   yyWriteTree0 (yyt);
  yyIndentLevel := yySaveLevel;
  yySetIndentInfo ( ) ;   DEC (yyRecursionLevel);
 END WriteTree0;

PROCEDURE yyIndentSelector (READONLY yys: ARRAY OF CHAR) =
 BEGIN    IF yyIndentQuotient > 0    THEN ReuseIO.WriteC ( yyf , '(' ); ReuseIO.WriteC ( yyf , '*' ); 
     ReuseIO.WriteN ( yyf , yyIndentQuotient * yyIndentFactor , 6 , 10 ); 
     ReuseIO.WriteC ( yyf , '*' ); ReuseIO.WriteC ( yyf , ')' ); 
     Layout.WriteSpaces (yyf, yyIndentRemainder ); 
   ELSE Layout.WriteSpaces (yyf, yyIndentRemainder); 
   END ;    yyWriteSelector (yys); 
 END yyIndentSelector;

PROCEDURE yyIndentSelectorTree (READONLY yys: ARRAY OF CHAR; yyt: tTree0) =
 BEGIN yyIndentSelector (yys); yyWriteTree0 ( yyt );  END yyIndentSelectorTree;

PROCEDURE yWriteNode (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..4] OF CHAR{'N','o','d','e','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_8 =  yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 650
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_8,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 651
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 652
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 653
 $$ *).NodeCount , 0);  yyWriteNl();
 END yWriteNode;

PROCEDURE yWriteNode1 (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..5] OF CHAR{'N','o','d','e','1','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_11 =  yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 659
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_11,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 660
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 661
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 662
 $$ *).NodeCount , 0);  yyWriteNl();
 END yWriteNode1;

PROCEDURE yWriteOption (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..6] OF CHAR{'O','p','t','i','o','n','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_7 =  yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 668
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_7,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 669
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 670
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 671
 $$ *).NodeCount , 0);  yyWriteNl();
 END yWriteOption;

PROCEDURE yWriteRepetition (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..10] OF CHAR{'R','e','p','e','t','i','t','i','o','n','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_12 =  yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 677
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_12,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 678
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 679
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 680
 $$ *).NodeCount , 0);  yyWriteNl();
 END yWriteRepetition;

PROCEDURE yWriteNode2 (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..5] OF CHAR{'N','o','d','e','2','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_0 =  yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 686
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_0,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 687
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 688
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 689
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree (ARRAY [0..4] OF CHAR{'S','o','n','1','\000'}, yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 690
 $$ *).Son1);
 END yWriteNode2;

PROCEDURE yWriteList (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..4] OF CHAR{'L','i','s','t','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_10 =  yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 696
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_10,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 697
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 698
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 699
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree (ARRAY [0..4] OF CHAR{'S','o','n','1','\000'}, yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 700
 $$ *).Son1);
 END yWriteList;

PROCEDURE yWriteSequence (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..8] OF CHAR{'S','e','q','u','e','n','c','e','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_1 =  yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 706
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_1,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 707
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 708
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 709
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree (ARRAY [0..4] OF CHAR{'S','o','n','1','\000'}, yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 710
 $$ *).Son1);
 END yWriteSequence;

PROCEDURE yWriteAlternative (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..11] OF CHAR{'A','l','t','e','r','n','a','t','i','v','e','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_4 =  yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 716
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_4,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 717
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 718
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 719
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree (ARRAY [0..4] OF CHAR{'S','o','n','1','\000'}, yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 720
 $$ *).Son1);
 END yWriteAlternative;

PROCEDURE yWriteCh (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..2] OF CHAR{'C','h','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_5 =  yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 726
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_5,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 727
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 728
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 729
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..2] OF CHAR{'C','h','\000'}); ReuseIO.WriteC (yyf,  yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 730
 $$ *).Ch );  yyWriteNl();
 END yWriteCh;

PROCEDURE yWriteSet (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..3] OF CHAR{'S','e','t','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_6 =  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 736
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_6,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 737
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 738
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 739
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..3] OF CHAR{'S','e','t','\000'}); Sets.WriteSet (yyf,  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 740
 $$ *).Set );  yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'c','a','r','d','\000'}); ReuseIO.WriteI (yyf,  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 741
 $$ *).card , 0);  yyWriteNl();
 END yWriteSet;

PROCEDURE yWriteString (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..6] OF CHAR{'S','t','r','i','n','g','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_9 =  yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 747
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_9,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 748
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 749
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 750
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..6] OF CHAR{'S','t','r','i','n','g','\000'}); StringMem.WriteString (yyf,  yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 751
 $$ *).String );  yyWriteNl();
 END yWriteString;

PROCEDURE yWriteRule (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..4] OF CHAR{'R','u','l','e','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_2 =  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 757
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_2,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 758
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 759
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 760
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..10] OF CHAR{'T','a','r','g','e','t','C','o','d','e','\000'}); Texts.WriteText (yyf,  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 761
 $$ *).TargetCode );  yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'L','i','n','e','\000'}); ReuseIO.WriteI (yyf,  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 762
 $$ *).Line , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..8] OF CHAR{'C','o','d','e','M','o','d','e','\000'}); ReuseIO.WriteI (yyf,  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 763
 $$ *).CodeMode , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..6] OF CHAR{'R','u','l','e','N','r','\000'}); ReuseIO.WriteI (yyf,  yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 764
 $$ *).RuleNr , 0);  yyWriteNl();
 END yWriteRule;

PROCEDURE yWritePattern (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteS (yyf, ARRAY [0..7] OF CHAR{'P','a','t','t','e','r','n','\000'}); yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'T','r','e','e','\000'}); WITH m2tom3_desig_3 =  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 770
 $$ *).Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_3,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector (ARRAY [0..12] OF CHAR{'I','s','C','o','n','s','t','a','n','t','R','E','\000'}); ReuseIO.WriteB (yyf,  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 771
 $$ *).IsConstantRE );  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'L','e','a','f','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 772
 $$ *).LeafCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..9] OF CHAR{'N','o','d','e','C','o','u','n','t','\000'}); ReuseIO.WriteI (yyf,  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 773
 $$ *).NodeCount , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..11] OF CHAR{'S','t','a','r','t','S','t','a','t','e','s','\000'}); Sets.WriteSet (yyf,  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 774
 $$ *).StartStates );  yyWriteNl();
  yyIndentSelectorTree (ARRAY [0..7] OF CHAR{'R','e','g','E','x','p','r','\000'}, yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 775
 $$ *).RegExpr);
  yyIndentSelector (ARRAY [0..9] OF CHAR{'P','a','t','t','e','r','n','N','r','\000'}); ReuseIO.WriteI (yyf,  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 776
 $$ *).PatternNr , 0);  yyWriteNl();
  yyIndentSelector (ARRAY [0..8] OF CHAR{'P','o','s','i','t','i','o','n','\000'}); Positions.WritePosition (yyf,  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 777
 $$ *).Position );  yyWriteNl();
  yyIndentSelector (ARRAY [0..4] OF CHAR{'c','a','r','d','\000'}); ReuseIO.WriteI (yyf,  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 778
 $$ *).card , 0);  yyWriteNl();
 END yWritePattern;

PROCEDURE yyWriteTree0 (yyt: tTree0) =
 VAR yyLevel   : SHORTCARD;
 BEGIN
  yyLevel := yyIndentLevel;
  LOOP
   IF yyt = NoTree0 THEN
    ReuseIO.WriteS (yyf, ARRAY [0..8] OF CHAR{' ','N','o','T','r','e','e','0','\000'}); yyWriteNl(); EXIT;
   ELSIF yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 788
 $$ *).yyMark = 0 THEN
    ReuseIO.WriteC (yyf, '^'); ReuseIO.WriteI (yyf, yyMapToLabel (yyt), 0); yyWriteNl(); EXIT;
   ELSIF yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 790
 $$ *).yyMark > 1 THEN
    yyWriteNl(); ReuseIO.WriteN (yyf, yyMapToLabel (yyt), 6, 10); ReuseIO.WriteC (yyf, ':');
    Layout.WriteSpaces (yyf, yyActualIndent - 7);
   ELSE
    ReuseIO.WriteC (yyf, ' ');
   END;
   yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 796
 $$ *).yyMark := 0;
   INC (yyIndentLevel, 2);
   yySetIndentInfo ( ) ; 
   CASE yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 799
 $$ *) OF
| Node=> yWriteNode (yyt); EXIT;
| Node1=> yWriteNode1 (yyt); yyIndentSelector (ARRAY [0..4] OF CHAR{'S','o','n','1','\000'}); yyt := yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 801
 $$ *).Son1;
| Option=> yWriteOption (yyt); yyIndentSelector (ARRAY [0..4] OF CHAR{'S','o','n','1','\000'}); yyt := yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 802
 $$ *).Son1;
| Repetition=> yWriteRepetition (yyt); yyIndentSelector (ARRAY [0..4] OF CHAR{'S','o','n','1','\000'}); yyt := yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 803
 $$ *).Son1;
| Node2=> yWriteNode2 (yyt); yyIndentSelector (ARRAY [0..4] OF CHAR{'S','o','n','2','\000'}); yyt := yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 804
 $$ *).Son2;
| List=> yWriteList (yyt); yyIndentSelector (ARRAY [0..4] OF CHAR{'S','o','n','2','\000'}); yyt := yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 805
 $$ *).Son2;
| Sequence=> yWriteSequence (yyt); yyIndentSelector (ARRAY [0..4] OF CHAR{'S','o','n','2','\000'}); yyt := yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 806
 $$ *).Son2;
| Alternative=> yWriteAlternative (yyt); yyIndentSelector (ARRAY [0..4] OF CHAR{'S','o','n','2','\000'}); yyt := yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 807
 $$ *).Son2;
| Ch=> yWriteCh (yyt); EXIT;
| Set=> yWriteSet (yyt); EXIT;
| String=> yWriteString (yyt); EXIT;
| Rule=> yWriteRule (yyt); yyIndentSelector (ARRAY [0..8] OF CHAR{'P','a','t','t','e','r','n','s','\000'}); yyt := yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 811
 $$ *).Patterns;
| Pattern=> yWritePattern (yyt); yyIndentSelector (ARRAY [0..12] OF CHAR{'R','i','g','h','t','C','o','n','t','e','x','t','\000'}); yyt := yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 812
 $$ *).RightContext;
   ELSE EXIT;
   END;
  END;
  yyIndentLevel := yyLevel;
  yySetIndentInfo ( ) ;  END yyWriteTree0;

CONST yyNil    = '\374';
CONST yyNoLabel        = '\375';
CONST yyLabelDef       = '\376';
CONST yyLabelUse       = '\377';

PROCEDURE ReleaseTree0Module() =
 VAR yyBlockPtr        : yytBlockPtr;
 BEGIN
  WHILE yyBlockList # NIL DO
   yyBlockPtr  := yyBlockList;
   yyBlockList := yyBlockList^.yySuccessor;
   Memory.Free (BYTESIZE (yytBlock), yyBlockPtr);
  END;
  yyPoolFreePtr        := NIL;
  yyPoolMaxPtr := NIL;
  HeapUsed     := 0;
 END ReleaseTree0Module;

VAR yyProc     : tProcTree;

PROCEDURE TraverseTree0TD (yyt: tTree0; yyyProc: tProcTree) =
 BEGIN
  yyMark (yyt);
  yyProc := yyyProc;
  yyTraverseTree0TD (yyt);
 END TraverseTree0TD;

PROCEDURE yyTraverseTree0TD (yyt: tTree0) =
 BEGIN
  LOOP
   IF (yyt = NoTree0) OR (yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 849
 $$ *).yyMark = 0) THEN RETURN; END;
   yyt^.yyHead(* $$ m2tom3 warning: application of variant field, possible cast of 'yyHead' in line 850
 $$ *).yyMark := 0;
   yyProc (yyt);

   CASE yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 853
 $$ *) OF
| Node1=>
yyt := yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 855
 $$ *).Son1;
| Option=>
yyt := yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 857
 $$ *).Son1;
| Repetition=>
yyt := yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 859
 $$ *).Son1;
| Node2=>
yyTraverseTree0TD (yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 861
 $$ *).Son1);
yyt := yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 862
 $$ *).Son2;
| List=>
yyTraverseTree0TD (yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 864
 $$ *).Son1);
yyt := yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 865
 $$ *).Son2;
| Sequence=>
yyTraverseTree0TD (yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 867
 $$ *).Son1);
yyt := yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 868
 $$ *).Son2;
| Alternative=>
yyTraverseTree0TD (yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 870
 $$ *).Son1);
yyt := yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 871
 $$ *).Son2;
| Rule=>
yyt := yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 873
 $$ *).Patterns;
| Pattern=>
yyTraverseTree0TD (yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 875
 $$ *).RegExpr);
yyt := yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 876
 $$ *).RightContext;
   ELSE RETURN;
   END;
  END;
 END yyTraverseTree0TD;

PROCEDURE BeginTree0() =
 BEGIN
 END BeginTree0;

PROCEDURE CloseTree0() =
 BEGIN
 END CloseTree0;

PROCEDURE xxExit() =
 BEGIN
  ReuseIO.CloseIO(); System.Exit (1);
 END xxExit;

BEGIN
 yyBlockList   := NIL;
 yyPoolFreePtr := NIL;
 yyPoolMaxPtr  := NIL;
 HeapUsed      := 0;
 yyExit        := xxExit;
 yyNodeSize [Node] := BYTESIZE (yNode);
 yyNodeSize [Node1] := BYTESIZE (yNode1);
 yyNodeSize [Option] := BYTESIZE (yOption);
 yyNodeSize [Repetition] := BYTESIZE (yRepetition);
 yyNodeSize [Node2] := BYTESIZE (yNode2);
 yyNodeSize [List] := BYTESIZE (yList);
 yyNodeSize [Sequence] := BYTESIZE (ySequence);
 yyNodeSize [Alternative] := BYTESIZE (yAlternative);
 yyNodeSize [Ch] := BYTESIZE (yCh);
 yyNodeSize [Set] := BYTESIZE (ySet);
 yyNodeSize [String] := BYTESIZE (yString);
 yyNodeSize [Rule] := BYTESIZE (yRule);
 yyNodeSize [Pattern] := BYTESIZE (yPattern);
 yyMaxSize     := 0;
 FOR yyi := 1 TO 13 DO
  yyNodeSize [yyi] := LOOPHOLE (LOOPHOLE (yyNodeSize [yyi] + LOOPHOLE (General.MaxAlign,Word.T) - 1,BITSET) * General.AlignMasks [General.MaxAlign],M2LONGINT);
  yyMaxSize := General.Max (yyNodeSize [yyi], yyMaxSize);
 END;
 yyTypeRange [Node] := Pattern;
 yyTypeRange [Node1] := Repetition;
 yyTypeRange [Option] := Option;
 yyTypeRange [Repetition] := Repetition;
 yyTypeRange [Node2] := Alternative;
 yyTypeRange [List] := List;
 yyTypeRange [Sequence] := Sequence;
 yyTypeRange [Alternative] := Alternative;
 yyTypeRange [Ch] := Ch;
 yyTypeRange [Set] := Set;
 yyTypeRange [String] := String;
 yyTypeRange [Rule] := Rule;
 yyTypeRange [Pattern] := Pattern;
 yyRecursionLevel := 0;
 yyTreeStoreSize := yyInitTreeStoreSize;
 DynArray.MakeArray (LOOPHOLE(yyTreeStorePtr,ADDRESS), yyTreeStoreSize, BYTESIZE (tTree0));
 BeginTree0();
END Tree0.

