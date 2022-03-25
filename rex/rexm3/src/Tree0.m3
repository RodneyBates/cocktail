 UNSAFE MODULE Tree0;

IMPORT Text;

FROM SYSTEM IMPORT BYTE, BITSET, SHORTINT, SHORTCARD, M2LONGINT;
IMPORT Word, SYSTEM, System, General, Memory, DynArray, ReuseIO;
IMPORT IO, Layout, StringMem, Strings, Idents, Texts, Sets, Positions;
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
 VAR yyByteCount       : LONGINT;
 VAR yyt       : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [yyKind] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := yyKind;
  RETURN yyt;
 END MakeTree0;

PROCEDURE IsType (yyTree: tTree0; yyKind: SHORTCARD): BOOLEAN =
 BEGIN
  RETURN (yyTree # NoTree0) AND (yyKind <= yyTree^.Kind) AND (yyTree^.Kind <= yyTypeRange [yyKind]);
 END IsType;


PROCEDURE mNode (): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Node] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Node;
  WITH With_16=yyt^.Node DO
    
    
    
    
  END;
  RETURN yyt;
 END mNode;

PROCEDURE mNode1 (pSon1: tTree0): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Node1] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Node1;
  WITH With_17=yyt^.Node1 DO
    
    
    
    
   With_17.Son1 := pSon1;
  END;
  RETURN yyt;
 END mNode1;

PROCEDURE mOption (pSon1: tTree0): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Option] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Option;
  WITH With_18=yyt^.Option DO
    
    
    
    
   With_18.Son1 := pSon1;
  END;
  RETURN yyt;
 END mOption;

PROCEDURE mRepetition (pSon1: tTree0): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Repetition] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Repetition;
  WITH With_19=yyt^.Repetition DO
    
    
    
    
   With_19.Son1 := pSon1;
  END;
  RETURN yyt;
 END mRepetition;

PROCEDURE mNode2 (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Node2] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Node2;
  WITH With_20=yyt^.Node2 DO
    
    
    
    
   With_20.Son1 := pSon1;
   With_20.Son2 := pSon2;
  END;
  RETURN yyt;
 END mNode2;

PROCEDURE mList (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [List] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := List;
  WITH With_21=yyt^.List DO
    
    
    
    
   With_21.Son1 := pSon1;
   With_21.Son2 := pSon2;
  END;
  RETURN yyt;
 END mList;

PROCEDURE mSequence (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Sequence] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Sequence;
  WITH With_22=yyt^.Sequence DO
    
    
    
    
   With_22.Son1 := pSon1;
   With_22.Son2 := pSon2;
  END;
  RETURN yyt;
 END mSequence;

PROCEDURE mAlternative (pSon1: tTree0; pSon2: tTree0): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Alternative] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Alternative;
  WITH With_23=yyt^.Alternative DO
    
    
    
    
   With_23.Son1 := pSon1;
   With_23.Son2 := pSon2;
  END;
  RETURN yyt;
 END mAlternative;

PROCEDURE mCh (pCh: CHAR): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Ch] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Ch;
  WITH With_24=yyt^.Ch DO
    
    
    
    
   With_24.Ch := pCh;
  END;
  RETURN yyt;
 END mCh;

PROCEDURE mSet (pSet: tSet): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Set] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Set;
  WITH With_25=yyt^.Set DO
    
    
    
    
   With_25.Set := pSet;
    
  END;
  RETURN yyt;
 END mSet;

PROCEDURE mString (pString: tStringRef): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [String] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := String;
  WITH With_26=yyt^.String DO
    
    
    
    
   With_26.String := pString;
  END;
  RETURN yyt;
 END mString;

PROCEDURE mRule (pPatterns: tTree0; pTargetCode: tText; pLine: SHORTCARD; pCodeMode: SHORTCARD; pRuleNr: SHORTCARD): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Rule] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Rule;
  WITH With_27=yyt^.Rule DO
    
    
    
    
   With_27.Patterns := pPatterns;
   With_27.TargetCode := pTargetCode;
   With_27.Line := pLine;
   With_27.CodeMode := pCodeMode;
   With_27.RuleNr := pRuleNr;
  END;
  RETURN yyt;
 END mRule;

PROCEDURE mPattern (pStartStates: tSet; pRegExpr: tTree0; pRightContext: tTree0; pPatternNr: SHORTCARD; pPosition: tPosition): tTree0 =
 VAR yyByteCount    : LONGINT;
 VAR yyt    : tTree0;
 BEGIN
   yyt  := yyPoolFreePtr; IF LOOPHOLE ( yyt ,ADDRESS) >= yyPoolMaxPtr THEN  yyt  := yyAlloc (); END; INC (yyPoolFreePtr,   yyNodeSize [Pattern] ); 
  yyt^.yyHead.yyMark := 0;
  yyt^.Kind := Pattern;
  WITH With_28=yyt^.Pattern DO
    
    
    
    
   With_28.StartStates := pStartStates;
   With_28.RegExpr := pRegExpr;
   With_28.RightContext := pRightContext;
   With_28.PatternNr := pPatternNr;
   With_28.Position := pPosition;
    
  END;
  RETURN yyt;
 END mPattern;

TYPE yyPtrtTree        = UNTRACED BRANDED REF  tTree0;

VAR yyf        : ReuseIO.tFile;
VAR yyLabel    : SHORTCARD;
VAR yyKind     : SHORTCARD;
VAR yyc        : CHAR;
VAR yys        : Strings.tString;

VAR topCallCt:INTEGER := 0;
VAR topCallStop := 0;
VAR recCallCt:INTEGER := 0;
VAR recCallStop := 36;

PROCEDURE yyMarkProc (yyt: tTree0; yyt2: tTree0 := NIL) =

VAR v0, v1, v2, v3, v4: tTree0; 
 BEGIN
  LOOP
   v0 := yyt;
   v1 := yyt2; 
   IF yyt = NoTree0 THEN RETURN; END;
   IF yyt2 # NIL AND yyt2 # yyt
   THEN
     v2 := yyt; 
   END;
   INC (yyt^.yyHead.yyMark);
   IF yyt^.yyHead.yyMark > 1 THEN RETURN; END;

   CASE yyt^.Kind OF
| Node1=>
yyt := yyt^.Node1.Son1;
| Option=>
yyt := yyt^.Option.Son1;
| Repetition=>
yyt := yyt^.Repetition.Son1;
| Node2=>
yyMarkProc (yyt^.Node2.Son1);
yyt := yyt^.Node2.Son2;
| List=>

IF recCallCt = recCallStop THEN
  v4 := v3;
END;
INC (recCallCt);

yyMarkProc (yyt^.List.Son1,yyt^.List.Son1);
yyt := yyt^.List.Son2;
| Sequence=>
yyMarkProc (yyt^.Sequence.Son1);
yyt := yyt^.Sequence.Son2;
| Alternative=>
yyMarkProc (yyt^.Alternative.Son1);
yyt := yyt^.Alternative.Son2;
| Rule=>
yyt := yyt^.Rule.Patterns;
| Pattern=>
yyMarkProc (yyt^.Pattern.RegExpr);
yyt := yyt^.Pattern.RightContext;
   ELSE RETURN;
   END;
  END;
 END yyMarkProc;

CONST yyInitTreeStoreSize      = 32;

VAR yyTreeStoreSize    : M2LONGINT;
VAR yyTreeStorePtr     : UNTRACED BRANDED REF  ARRAY [0..50000] OF tTree0;
VAR yyLabelCount       : INTEGER;
VAR yyRecursionLevel   : SHORTINT;

PROCEDURE yyMapToLabel (yyTree: tTree0): SHORTCARD =
 BEGIN
  FOR yyi := 1 TO yyLabelCount DO
   IF yyTreeStorePtr^[yyi] = yyTree THEN RETURN yyi; END;
  END;
  INC (yyLabelCount);
  IF yyLabelCount = yyTreeStoreSize THEN
   DynArray.ExtendArray
      (LOOPHOLE(yyTreeStorePtr,ADDRESS), yyTreeStoreSize, BYTESIZE (tTree0));
  END;
  yyTreeStorePtr^[yyLabelCount] := yyTree;
  RETURN yyLabelCount;
 END yyMapToLabel;

PROCEDURE yyMapToTree (yyLabel: SHORTCARD): tTree0 =
 BEGIN RETURN yyTreeStorePtr^[yyLabel]; END yyMapToTree;

PROCEDURE yyWriteNl() = BEGIN ReuseIO.WriteNl (yyf); END yyWriteNl;

PROCEDURE yyWriteSelector (yys: TEXT) =
 BEGIN ReuseIO.WriteT (yyf, yys);
 Layout.WriteSpaces (yyf, 14 - Text.Length(yys));
 ReuseIO.WriteT (yyf, " = ");
 END yyWriteSelector;

PROCEDURE yyWriteHex (VAR yyx: ARRAY OF SYSTEM.BYTE) =
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
  
IF topCallCt = topCallStop THEN
  topCallStop := topCallStop;
END;
INC (topCallCt);
recCallCt := 0;

  yyMarkProc (yyt);
  yySaveLevel := yyIndentLevel;
  yyIndentLevel := 0;
  yySetIndentInfo ( ) ;   yyWriteTree0 (yyt);
  yyIndentLevel := yySaveLevel;
  yySetIndentInfo ( ) ;   DEC (yyRecursionLevel);
 END WriteTree0;

PROCEDURE yyIndentSelector (yys: TEXT) =
 BEGIN    IF yyIndentQuotient > 0    THEN ReuseIO.WriteC ( yyf , '(' ); ReuseIO.WriteC ( yyf , '*' ); 
     ReuseIO.WriteN ( yyf , yyIndentQuotient * yyIndentFactor , 6 , 10 ); 
     ReuseIO.WriteC ( yyf , '*' ); ReuseIO.WriteC ( yyf , ')' ); 
     Layout.WriteSpaces (yyf, yyIndentRemainder ); 
   ELSE Layout.WriteSpaces (yyf, yyIndentRemainder); 
   END ;
   yyWriteSelector (yys); 
 END yyIndentSelector;

PROCEDURE yyIndentSelectorTree (yys: TEXT; yyt: tTree0) =
 BEGIN yyIndentSelector (yys); yyWriteTree0 ( yyt );
 END yyIndentSelectorTree;

PROCEDURE yWriteNode (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Node"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_8 =  yyt^.Node.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_8,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Node.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Node.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Node.NodeCount , 0);  yyWriteNl();
 END yWriteNode;

PROCEDURE yWriteNode1 (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Node1"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_11 =  yyt^.Node1.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_11,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Node1.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Node1.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Node1.NodeCount , 0);  yyWriteNl();
 END yWriteNode1;

PROCEDURE yWriteOption (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Option"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_7 =  yyt^.Option.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_7,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Option.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Option.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Option.NodeCount , 0);  yyWriteNl();
 END yWriteOption;

PROCEDURE yWriteRepetition (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Repetition"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_12 =  yyt^.Repetition.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_12,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Repetition.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Repetition.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Repetition.NodeCount , 0);  yyWriteNl();
 END yWriteRepetition;

PROCEDURE yWriteNode2 (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Node2"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_0 =  yyt^.Node2.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_0,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Node2.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Node2.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Node2.NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree ("Son1", yyt^.Node2.Son1);
 END yWriteNode2;

PROCEDURE yWriteList (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "List"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_10 =  yyt^.List.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_10,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.List.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.List.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.List.NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree ("Son1", yyt^.List.Son1);
 END yWriteList;

PROCEDURE yWriteSequence (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Sequence"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_1 =  yyt^.Sequence.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_1,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Sequence.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Sequence.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Sequence.NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree ("Son1", yyt^.Sequence.Son1);
 END yWriteSequence;

PROCEDURE yWriteAlternative (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Alternative"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_4 =  yyt^.Alternative.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_4,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Alternative.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Alternative.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Alternative.NodeCount , 0);  yyWriteNl();
  yyIndentSelectorTree ("Son1", yyt^.Alternative.Son1);
 END yWriteAlternative;

PROCEDURE yWriteCh (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Ch"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_5 =  yyt^.Ch.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_5,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Ch.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Ch.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Ch.NodeCount , 0);  yyWriteNl();
  yyIndentSelector ("Ch"); ReuseIO.WriteC (yyf,  yyt^.Ch.Ch );  yyWriteNl();
 END yWriteCh;

PROCEDURE yWriteSet (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Set"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_6 =  yyt^.Set.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_6,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Set.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Set.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Set.NodeCount , 0);  yyWriteNl();
  yyIndentSelector ("Set"); Sets.WriteSet (yyf,  yyt^.Set.Set );  yyWriteNl();
  yyIndentSelector ("card"); ReuseIO.WriteI (yyf,  yyt^.Set.card , 0);  yyWriteNl();
 END yWriteSet;

PROCEDURE yWriteString (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "String"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_9 =  yyt^.String.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_9,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.String.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.String.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.String.NodeCount , 0);  yyWriteNl();
  yyIndentSelector ("String"); StringMem.WriteString (yyf,  yyt^.String.String );  yyWriteNl();
 END yWriteString;

PROCEDURE yWriteRule (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Rule"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_2 =  yyt^.Rule.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_2,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Rule.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Rule.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Rule.NodeCount , 0);  yyWriteNl();
  yyIndentSelector ("TargetCode"); Texts.WriteText (yyf,  yyt^.Rule.TargetCode );  yyWriteNl();
  yyIndentSelector ("Line"); ReuseIO.WriteI (yyf,  yyt^.Rule.Line , 0);  yyWriteNl();
  yyIndentSelector ("CodeMode"); ReuseIO.WriteI (yyf,  yyt^.Rule.CodeMode , 0);  yyWriteNl();
  yyIndentSelector ("RuleNr"); ReuseIO.WriteI (yyf,  yyt^.Rule.RuleNr , 0);  yyWriteNl();
 END yWriteRule;

PROCEDURE yWritePattern (yyt: tTree0) =
 BEGIN
  ReuseIO.WriteT (yyf, "Pattern"); yyWriteNl();
  yyIndentSelector ("Tree"); WITH m2tom3_desig_3 =  yyt^.Pattern.Tree  DO
yyWriteHex (LOOPHOLE(m2tom3_desig_3,ARRAY OF BYTE))
END;  yyWriteNl();
  yyIndentSelector ("IsConstantRE"); ReuseIO.WriteB (yyf,  yyt^.Pattern.IsConstantRE );  yyWriteNl();
  yyIndentSelector ("LeafCount"); ReuseIO.WriteI (yyf,  yyt^.Pattern.LeafCount , 0);  yyWriteNl();
  yyIndentSelector ("NodeCount"); ReuseIO.WriteI (yyf,  yyt^.Pattern.NodeCount , 0);  yyWriteNl();
  yyIndentSelector ("StartStates"); Sets.WriteSet (yyf,  yyt^.Pattern.StartStates );  yyWriteNl();
  yyIndentSelectorTree ("RegExpr", yyt^.Pattern.RegExpr);
  yyIndentSelector ("PatternNr"); ReuseIO.WriteI (yyf,  yyt^.Pattern.PatternNr , 0);  yyWriteNl();
  yyIndentSelector ("Position"); Positions.WritePosition (yyf,  yyt^.Pattern.Position );  yyWriteNl();
  yyIndentSelector ("card"); ReuseIO.WriteI (yyf,  yyt^.Pattern.card , 0);  yyWriteNl();
 END yWritePattern;

PROCEDURE yyWriteTree0 (yyt: tTree0) =
 VAR yyLevel   : SHORTCARD;
 BEGIN
  yyLevel := yyIndentLevel;
  LOOP
   IF yyt = NoTree0 THEN
    ReuseIO.WriteT (yyf, " NoTree0"); yyWriteNl(); EXIT;
   ELSIF yyt^.yyHead.yyMark = 0 THEN
    ReuseIO.WriteC (yyf, '^'); ReuseIO.WriteI (yyf, yyMapToLabel (yyt), 0); yyWriteNl(); EXIT;
   ELSIF yyt^.yyHead.yyMark > 1 THEN
    yyWriteNl(); ReuseIO.WriteN (yyf, yyMapToLabel (yyt), 6, 10); ReuseIO.WriteC (yyf, ':');
    Layout.WriteSpaces (yyf, yyActualIndent - 7);
   ELSE
    ReuseIO.WriteC (yyf, ' ');
   END;
   yyt^.yyHead.yyMark := 0;
   INC (yyIndentLevel, 2);
   yySetIndentInfo ( ) ; 
   CASE yyt^.Kind OF
| Node=> yWriteNode (yyt); EXIT;
| Node1=> yWriteNode1 (yyt); yyIndentSelector ("Son1"); yyt := yyt^.Node1.Son1;
| Option=> yWriteOption (yyt); yyIndentSelector ("Son1"); yyt := yyt^.Option.Son1;
| Repetition=> yWriteRepetition (yyt); yyIndentSelector ("Son1"); yyt := yyt^.Repetition.Son1;
| Node2=> yWriteNode2 (yyt); yyIndentSelector ("Son2"); yyt := yyt^.Node2.Son2;
| List=> yWriteList (yyt); yyIndentSelector ("Son2"); yyt := yyt^.List.Son2;
| Sequence=> yWriteSequence (yyt); yyIndentSelector ("Son2"); yyt := yyt^.Sequence.Son2;
| Alternative=> yWriteAlternative (yyt); yyIndentSelector ("Son2"); yyt := yyt^.Alternative.Son2;
| Ch=> yWriteCh (yyt); EXIT;
| Set=> yWriteSet (yyt); EXIT;
| String=> yWriteString (yyt); EXIT;
| Rule=> yWriteRule (yyt); yyIndentSelector ("Patterns"); yyt := yyt^.Rule.Patterns;
| Pattern=> yWritePattern (yyt); yyIndentSelector ("RightContext"); yyt := yyt^.Pattern.RightContext;
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

IF topCallCt = topCallStop THEN
  topCallStop := topCallStop;
END;
INC (topCallCt);
recCallCt := 0;

  yyMarkProc (yyt);
  yyProc := yyyProc;
  yyTraverseTree0TD (yyt);
 END TraverseTree0TD;

PROCEDURE yyTraverseTree0TD (yyt: tTree0) =
 BEGIN
  LOOP
   IF (yyt = NoTree0) OR (yyt^.yyHead.yyMark = 0) THEN RETURN; END;
   yyt^.yyHead.yyMark := 0;
   yyProc (yyt);

   CASE yyt^.Kind OF
| Node1=>
yyt := yyt^.Node1.Son1;
| Option=>
yyt := yyt^.Option.Son1;
| Repetition=>
yyt := yyt^.Repetition.Son1;
| Node2=>
yyTraverseTree0TD (yyt^.Node2.Son1);
yyt := yyt^.Node2.Son2;
| List=>
yyTraverseTree0TD (yyt^.List.Son1);
yyt := yyt^.List.Son2;
| Sequence=>
yyTraverseTree0TD (yyt^.Sequence.Son1);
yyt := yyt^.Sequence.Son2;
| Alternative=>
yyTraverseTree0TD (yyt^.Alternative.Son1);
yyt := yyt^.Alternative.Son2;
| Rule=>
yyt := yyt^.Rule.Patterns;
| Pattern=>
yyTraverseTree0TD (yyt^.Pattern.RegExpr);
yyt := yyt^.Pattern.RightContext;
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


(* yyNodeSize [Node] := BYTESIZE (yNode);
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
  yyNodeSize [yyi]
    := Word.And(yyNodeSize [yyi] + General.MaxAlign - 1
               ,General.AlignMasks [General.MaxAlign]
               );
 (*CHECK: ^ Wow!*)
  yyMaxSize := General.Max (yyNodeSize [yyi], yyMaxSize);
*)

(* Account for flattening of variant record in size values: *)
 yyMaxSize := BYTESIZE(yyNode); 
 FOR yyi := 1 TO 13 DO
  yyNodeSize [yyi] := yyMaxSize;
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

