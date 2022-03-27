UNSAFE MODULE Tree0 

; IMPORT Text 

; FROM SYSTEM IMPORT BYTE , BITSET , SHORTINT , SHORTCARD , M2LONGINT 
; IMPORT Word , SYSTEM , System , General , Memory , DynArray , ReuseIO 
; IMPORT IO 
  , Layout 
  , StringMem 
  , Strings 
  , Idents 
  , Texts 
  , Sets 
  , Positions 
(* line 31 "../src/rex.cg" *) 

; FROM Sets IMPORT tSet 

; FROM Texts IMPORT tText 

; FROM StringMem IMPORT tStringRef 

; FROM Positions IMPORT tPosition 



















































































































































































































































; CONST yyBlockSize = 20480 

; TYPE yytBlockPtr = UNTRACED BRANDED REF yytBlock 
  ; yytBlock 
    = RECORD 
        yyBlock : ARRAY [ 1 .. yyBlockSize ] OF CHAR 
      ; yySuccessor : yytBlockPtr 
      END (* RECORD *) 

; VAR yyBlockList : yytBlockPtr 
; VAR yyMaxSize , yyi : SHORTCARD 
; VAR yyTypeRange : ARRAY [ 0 .. 13 ] OF SHORTCARD 

; PROCEDURE yyAlloc ( ) : tTree0 

  = VAR yyBlockPtr : yytBlockPtr 

  ; BEGIN (* yyAlloc *) 
      yyBlockPtr := yyBlockList 
    ; yyBlockList := Memory . Alloc ( BYTESIZE ( yytBlock ) ) 
    ; yyBlockList ^ . yySuccessor := yyBlockPtr 
    ; yyPoolFreePtr 
        := ADR        ( yyBlockList ^ . yyBlock ) 
    ; yyPoolMaxPtr := yyPoolFreePtr + yyBlockSize - yyMaxSize + 1 
    ; INC ( HeapUsed , yyBlockSize ) 
    ; RETURN yyPoolFreePtr 
    END yyAlloc 

; PROCEDURE MakeTree0 ( yyKind : SHORTCARD ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* MakeTree0 *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ yyKind ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := yyKind 
    ; RETURN yyt 
    END MakeTree0 

; PROCEDURE IsType ( yyTree : tTree0 ; yyKind : SHORTCARD ) : BOOLEAN 

  = BEGIN (* IsType *) 
      RETURN 
        ( yyTree # NoTree0 ) 
        AND ( yyKind <= yyTree ^ . Kind ) 
        AND ( yyTree ^ . Kind <= yyTypeRange [ yyKind ] ) 
    END IsType 


; PROCEDURE mNode ( ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mNode *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Node ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Node 
    ; WITH With_16 = yyt ^ . Node 
      DO 




      END (* WITH *) 
    ; RETURN yyt 
    END mNode 

; PROCEDURE mNode1 ( pSon1 : tTree0 ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mNode1 *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Node1 ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Node1 
    ; WITH With_17 = yyt ^ . Node1 . yyHead  
      DO 




         With_17 . Son1 := pSon1 
      END (* WITH *) 
    ; RETURN yyt 
    END mNode1 

; PROCEDURE mOption ( pSon1 : tTree0 ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mOption *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Option ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Option 
    ; WITH With_18 = yyt ^ . yyHead 
      DO 




         With_18 . Son1 := pSon1 
      END (* WITH *) 
    ; RETURN yyt 
    END mOption 

; PROCEDURE mRepetition ( pSon1 : tTree0 ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mRepetition *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Repetition ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Repetition 
    ; WITH With_19 = yyt ^ . yyHead 
      DO 




         With_19 . Son1 := pSon1 
      END (* WITH *) 
    ; RETURN yyt 
    END mRepetition 

; PROCEDURE mNode2 ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mNode2 *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Node2 ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Node2 
    ; WITH With_20 = yyt ^ . yyHead  
      DO 




         With_20 . Son1 := pSon1 
      ; With_20 . Son2 := pSon2 
      END (* WITH *) 
    ; RETURN yyt 
    END mNode2 

; PROCEDURE mList ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mList *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ List ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := List 
    ; WITH With_21 = yyt ^ . yyHead  
      DO 




         With_21 . Son1 := pSon1 
      ; With_21 . Son2 := pSon2 
      END (* WITH *) 
    ; RETURN yyt 
    END mList 

; PROCEDURE mSequence ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mSequence *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Sequence ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Sequence 
    ; WITH With_22 = yyt ^ . yyHead 
      DO 




         With_22 . Son1 := pSon1 
      ; With_22 . Son2 := pSon2 
      END (* WITH *) 
    ; RETURN yyt 
    END mSequence 

; PROCEDURE mAlternative ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mAlternative *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Alternative ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Alternative 
    ; WITH With_23 = yyt ^ . yyHead  
      DO 




         With_23 . Son1 := pSon1 
      ; With_23 . Son2 := pSon2 
      END (* WITH *) 
    ; RETURN yyt 
    END mAlternative 

; PROCEDURE mCh ( pCh : CHAR ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mCh *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Ch ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Ch 
    ; WITH With_24 = yyt ^ . Ch 
      DO 




         With_24 . Ch := pCh 
      END (* WITH *) 
    ; RETURN yyt 
    END mCh 

; PROCEDURE mSet ( pSet : tSet ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mSet *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Set ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Set 
    ; WITH With_25 = yyt ^ . Set 
      DO 




         With_25 . Set := pSet 

      END (* WITH *) 
    ; RETURN yyt 
    END mSet 

; PROCEDURE mString ( pString : tStringRef ) : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mString *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ String ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := String 
    ; WITH With_26 = yyt ^ . String 
      DO 




         With_26 . String := pString 
      END (* WITH *) 
    ; RETURN yyt 
    END mString 

; PROCEDURE mRule 
    ( pPatterns : tTree0 
    ; pTargetCode : tText 
    ; pLine : SHORTCARD 
    ; pCodeMode : SHORTCARD 
    ; pRuleNr : SHORTCARD 
    ) 
    : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mRule *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Rule ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Rule 
    ; WITH With_27 = yyt ^ . Rule 
      DO 




         With_27 . Patterns := pPatterns 
      ; With_27 . TargetCode := pTargetCode 
      ; With_27 . Line := pLine 
      ; With_27 . CodeMode := pCodeMode 
      ; With_27 . RuleNr := pRuleNr 
      END (* WITH *) 
    ; RETURN yyt 
    END mRule 

; PROCEDURE mPattern 
    ( pStartStates : tSet 
    ; pRegExpr : tTree0 
    ; pRightContext : tTree0 
    ; pPatternNr : SHORTCARD 
    ; pPosition : tPosition 
    ) 
    : tTree0 

  = VAR yyByteCount : LONGINT 
  ; VAR yyt : tTree0 

  ; BEGIN (* mPattern *) 
      yyt := yyPoolFreePtr 
    ; IF LOOPHOLE ( yyt , ADDRESS ) >= yyPoolMaxPtr 
      THEN 
        yyt := yyAlloc ( ) 
      END (* IF *) 
    ; INC ( yyPoolFreePtr , yyNodeSize [ Pattern ] ) 
    ; yyt ^ . yyHead . yyMark := 0 
    ; yyt ^ . Kind := Pattern 
    ; WITH With_28 = yyt ^ . Pattern 
      DO 




         With_28 . StartStates := pStartStates 
      ; With_28 . RegExpr := pRegExpr 
      ; With_28 . RightContext := pRightContext 
      ; With_28 . PatternNr := pPatternNr 
      ; With_28 . Position := pPosition 

      END (* WITH *) 
    ; RETURN yyt 
    END mPattern 

; TYPE yyPtrtTree = UNTRACED BRANDED REF tTree0 

; VAR yyf : ReuseIO . tFile 
; VAR yyLabel : SHORTCARD 
; VAR yyKind : SHORTCARD 
; VAR yyc : CHAR 
; VAR yys : Strings . tString 

; VAR topCallCt : INTEGER := 0 
; VAR topCallStop := 0 
; VAR recCallCt : INTEGER := 0 
; VAR recCallStop := 36 

; PROCEDURE yyMarkProc ( yyt : tTree0 ; yyt2 : tTree0 := NIL ) 

  = VAR v0 , v1 , v2 , v3 , v4 : tTree0 

  ; BEGIN (* yyMarkProc *) 
      LOOP 
        v0 := yyt 
      ; v1 := yyt2 
      ; IF yyt = NoTree0 THEN RETURN END (* IF *) 
      ; IF yyt2 # NIL AND yyt2 # yyt THEN v2 := yyt END (* IF *) 
      ; INC ( yyt ^ . yyHead . yyMark ) 
      ; IF yyt ^ . yyHead . yyMark > 1 THEN RETURN END (* IF *) 

      ; CASE yyt ^ . Kind 
        OF Node1 
        => yyt := yyt ^ . yyHead . Son1 
        | Option 
        => yyt := yyt ^ . yyHead . Son1 
        | Repetition 
        => yyt := yyt ^ . yyHead . Son1 
        | Node2 
        => yyMarkProc ( yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | List 
        => 

           IF recCallCt = recCallStop THEN v4 := v3 END (* IF *) 
        ; INC ( recCallCt ) 

        ; yyMarkProc ( yyt ^ . yyHead . Son1 , yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Sequence 
        => yyMarkProc ( yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Alternative 
        => yyMarkProc ( yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Rule 
        => yyt := yyt ^ . Rule . Patterns 
        | Pattern 
        => yyMarkProc ( yyt ^ . Pattern . RegExpr ) 
        ; yyt := yyt ^ . Pattern . RightContext 
        ELSE 
          RETURN 
        END (* CASE *) 
      END (* LOOP *) 
    END yyMarkProc 

; CONST yyInitTreeStoreSize = 32 

; VAR yyTreeStoreSize : M2LONGINT 
; VAR yyTreeStorePtr : UNTRACED BRANDED REF ARRAY [ 0 .. 50000 ] OF tTree0 
; VAR yyLabelCount : INTEGER 
; VAR yyRecursionLevel : SHORTINT 

; PROCEDURE yyMapToLabel ( yyTree : tTree0 ) : SHORTCARD 

  = BEGIN (* yyMapToLabel *) 
      FOR yyi := 1 TO yyLabelCount 
      DO IF yyTreeStorePtr ^ [ yyi ] = yyTree THEN RETURN yyi END (* IF *) 
      END (* FOR *) 
    ; INC ( yyLabelCount ) 
    ; IF yyLabelCount = yyTreeStoreSize 
      THEN 
        DynArray . ExtendArray 
          ( LOOPHOLE ( yyTreeStorePtr , ADDRESS ) 
          , yyTreeStoreSize 
          , BYTESIZE ( tTree0 ) 
          ) 
      END (* IF *) 
    ; yyTreeStorePtr ^ [ yyLabelCount ] := yyTree 
    ; RETURN yyLabelCount 
    END yyMapToLabel 

; PROCEDURE yyMapToTree ( yyLabel : SHORTCARD ) : tTree0 

  = BEGIN (* yyMapToTree *) 
      RETURN yyTreeStorePtr ^ [ yyLabel ] 
    END yyMapToTree 

; PROCEDURE yyWriteNl ( ) 

  = BEGIN (* yyWriteNl *) 
      ReuseIO . WriteNl ( yyf ) 
    END yyWriteNl 

; PROCEDURE yyWriteSelector ( yys : TEXT ) 

  = BEGIN (* yyWriteSelector *) 
      ReuseIO . WriteT ( yyf , yys ) 
    ; Layout . WriteSpaces ( yyf , 14 - Text . Length ( yys ) ) 
    ; ReuseIO . WriteT ( yyf , " = " ) 
    END yyWriteSelector 

; PROCEDURE yyWriteHex ( VAR yyx : ARRAY OF SYSTEM . BYTE ) 

  = BEGIN (* yyWriteHex *) 
      FOR yyi := 0 TO LOOPHOLE ( LAST ( yyx ) , INTEGER ) 
      DO ReuseIO . WriteN 
           ( yyf , ORD ( LOOPHOLE ( yyx [ yyi ] , CHAR ) ) , 2 , 16 ) 
      ; ReuseIO . WriteC ( yyf , ' ' ) 
      END (* FOR *) 
    END yyWriteHex 

; VAR yyIndentLevel : SHORTINT 
; VAR yyActualIndent , yyIndentQuotient , yyIndentRemainder : SHORTINT 

; CONST yyIndentFactor = 20 

; PROCEDURE yySetIndentInfo ( ) 

  = BEGIN (* yySetIndentInfo *) 
      yyIndentQuotient := yyIndentLevel DIV yyIndentFactor 
    ; yyIndentRemainder := yyIndentLevel MOD yyIndentFactor 
    ; yyActualIndent 
        := VAL ( 10 * ORD ( yyIndentQuotient > 0 ) , SHORTINT ) 
           + yyIndentRemainder 
    END yySetIndentInfo 

; PROCEDURE WriteTree0 ( yyyf : ReuseIO . tFile ; yyt : tTree0 ) 

  = VAR yySaveLevel : SHORTINT 

  ; BEGIN (* WriteTree0 *) 
      yyf := yyyf 
    ; IF yyRecursionLevel = 0 THEN yyLabelCount := 0 END (* IF *) 
    ; INC ( yyRecursionLevel ) 

    ; IF topCallCt = topCallStop THEN topCallStop := topCallStop END (* IF *) 
    ; INC ( topCallCt ) 
    ; recCallCt := 0 

    ; yyMarkProc ( yyt ) 
    ; yySaveLevel := yyIndentLevel 
    ; yyIndentLevel := 0 
    ; yySetIndentInfo ( ) 
    ; yyWriteTree0 ( yyt ) 
    ; yyIndentLevel := yySaveLevel 
    ; yySetIndentInfo ( ) 
    ; DEC ( yyRecursionLevel ) 
    END WriteTree0 

; PROCEDURE yyIndentSelector ( yys : TEXT ) 

  = BEGIN (* yyIndentSelector *) 
      IF yyIndentQuotient > 0 
      THEN 
        ReuseIO . WriteC ( yyf , '(' ) 
      ; ReuseIO . WriteC ( yyf , '*' ) 
      ; ReuseIO . WriteN ( yyf , yyIndentQuotient * yyIndentFactor , 6 , 10 ) 
      ; ReuseIO . WriteC ( yyf , '*' ) 
      ; ReuseIO . WriteC ( yyf , ')' ) 
      ; Layout . WriteSpaces ( yyf , yyIndentRemainder ) 
      ELSE 
        Layout . WriteSpaces ( yyf , yyIndentRemainder ) 
      END (* IF *) 
    ; yyWriteSelector ( yys ) 
    END yyIndentSelector 

; PROCEDURE yyIndentSelectorTree ( yys : TEXT ; yyt : tTree0 ) 

  = BEGIN (* yyIndentSelectorTree *) 
      yyIndentSelector ( yys ) 
    ; yyWriteTree0 ( yyt ) 
    END yyIndentSelectorTree 

; PROCEDURE yWriteNode ( yyt : tTree0 ) 

  = BEGIN (* yWriteNode *) 
      ReuseIO . WriteT ( yyf , "Node" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_8 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_8 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    END yWriteNode 

; PROCEDURE yWriteNode1 ( yyt : tTree0 ) 

  = BEGIN (* yWriteNode1 *) 
      ReuseIO . WriteT ( yyf , "Node1" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_11 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_11 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    END yWriteNode1 

; PROCEDURE yWriteOption ( yyt : tTree0 ) 

  = BEGIN (* yWriteOption *) 
      ReuseIO . WriteT ( yyf , "Option" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_7 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_7 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    END yWriteOption 

; PROCEDURE yWriteRepetition ( yyt : tTree0 ) 

  = BEGIN (* yWriteRepetition *) 
      ReuseIO . WriteT ( yyf , "Repetition" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_12 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_12 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    END yWriteRepetition 

; PROCEDURE yWriteNode2 ( yyt : tTree0 ) 

  = BEGIN (* yWriteNode2 *) 
      ReuseIO . WriteT ( yyf , "Node2" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_0 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_0 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelectorTree ( "Son1" , yyt ^ . yyHead . Son1 ) 
    END yWriteNode2 

; PROCEDURE yWriteList ( yyt : tTree0 ) 

  = BEGIN (* yWriteList *) 
      ReuseIO . WriteT ( yyf , "List" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_10 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_10 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelectorTree ( "Son1" , yyt ^ . yyHead . Son1 ) 
    END yWriteList 

; PROCEDURE yWriteSequence ( yyt : tTree0 ) 

  = BEGIN (* yWriteSequence *) 
      ReuseIO . WriteT ( yyf , "Sequence" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_1 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_1 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelectorTree ( "Son1" , yyt ^ . yyHead . Son1 ) 
    END yWriteSequence 

; PROCEDURE yWriteAlternative ( yyt : tTree0 ) 

  = BEGIN (* yWriteAlternative *) 
      ReuseIO . WriteT ( yyf , "Alternative" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_4 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_4 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelectorTree ( "Son1" , yyt ^ . yyHead . Son1 ) 
    END yWriteAlternative 

; PROCEDURE yWriteCh ( yyt : tTree0 ) 

  = BEGIN (* yWriteCh *) 
      ReuseIO . WriteT ( yyf , "Ch" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_5 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_5 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Ch" ) 
    ; ReuseIO . WriteC ( yyf , yyt ^ . Ch . Ch ) 
    ; yyWriteNl ( ) 
    END yWriteCh 

; PROCEDURE yWriteSet ( yyt : tTree0 ) 

  = BEGIN (* yWriteSet *) 
      ReuseIO . WriteT ( yyf , "Set" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_6 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_6 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Set" ) 
    ; Sets . WriteSet ( yyf , yyt ^ . Set . Set ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "card" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . Set . card , 0 ) 
    ; yyWriteNl ( ) 
    END yWriteSet 

; PROCEDURE yWriteString ( yyt : tTree0 ) 

  = BEGIN (* yWriteString *) 
      ReuseIO . WriteT ( yyf , "String" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_9 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_9 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "String" ) 
    ; StringMem . WriteString ( yyf , yyt ^ . String . String ) 
    ; yyWriteNl ( ) 
    END yWriteString 

; PROCEDURE yWriteRule ( yyt : tTree0 ) 

  = BEGIN (* yWriteRule *) 
      ReuseIO . WriteT ( yyf , "Rule" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_2 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_2 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "TargetCode" ) 
    ; Texts . WriteText ( yyf , yyt ^ . Rule . TargetCode ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Line" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . Rule . Line , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "CodeMode" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . Rule . CodeMode , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "RuleNr" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . Rule . RuleNr , 0 ) 
    ; yyWriteNl ( ) 
    END yWriteRule 

; PROCEDURE yWritePattern ( yyt : tTree0 ) 

  = BEGIN (* yWritePattern *) 
      ReuseIO . WriteT ( yyf , "Pattern" ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Tree" ) 
    ; WITH Desig_3 = yyt ^ . yyHead . Tree 
      DO yyWriteHex ( LOOPHOLE ( Desig_3 , ARRAY OF BYTE ) ) 
      END (* WITH *) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "IsConstantRE" ) 
    ; ReuseIO . WriteB ( yyf , yyt ^ . yyHead . IsConstantRE ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "LeafCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . LeafCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "NodeCount" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . yyHead . NodeCount , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "StartStates" ) 
    ; Sets . WriteSet ( yyf , yyt ^ . Pattern . StartStates ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelectorTree ( "RegExpr" , yyt ^ . Pattern . RegExpr ) 
    ; yyIndentSelector ( "PatternNr" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . Pattern . PatternNr , 0 ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "Position" ) 
    ; Positions . WritePosition ( yyf , yyt ^ . Pattern . Position ) 
    ; yyWriteNl ( ) 
    ; yyIndentSelector ( "card" ) 
    ; ReuseIO . WriteI ( yyf , yyt ^ . Pattern . card , 0 ) 
    ; yyWriteNl ( ) 
    END yWritePattern 

; PROCEDURE yyWriteTree0 ( yyt : tTree0 ) 

  = VAR yyLevel : SHORTCARD 

  ; BEGIN (* yyWriteTree0 *) 
      yyLevel := yyIndentLevel 
    ; LOOP 
        IF yyt = NoTree0 
        THEN 
          ReuseIO . WriteT ( yyf , " NoTree0" ) 
        ; yyWriteNl ( ) 
        ; EXIT 
        ELSIF yyt ^ . yyHead . yyMark = 0 
        THEN 
          ReuseIO . WriteC ( yyf , '^' ) 
        ; ReuseIO . WriteI ( yyf , yyMapToLabel ( yyt ) , 0 ) 
        ; yyWriteNl ( ) 
        ; EXIT 
        ELSIF yyt ^ . yyHead . yyMark > 1 
        THEN 
          yyWriteNl ( ) 
        ; ReuseIO . WriteN ( yyf , yyMapToLabel ( yyt ) , 6 , 10 ) 
        ; ReuseIO . WriteC ( yyf , ':' ) 
        ; Layout . WriteSpaces ( yyf , yyActualIndent - 7 ) 
        ELSE 
          ReuseIO . WriteC ( yyf , ' ' ) 
        END (* IF *) 
      ; yyt ^ . yyHead . yyMark := 0 
      ; INC ( yyIndentLevel , 2 ) 
      ; yySetIndentInfo ( ) 
      ; CASE yyt ^ . Kind 
        OF Node 
        => yWriteNode ( yyt ) 
        ; EXIT 
        | Node1 
        => yWriteNode1 ( yyt ) 
        ; yyIndentSelector ( "Son1" ) 
        ; yyt := yyt ^ . yyHead . Son1 
        | Option 
        => yWriteOption ( yyt ) 
        ; yyIndentSelector ( "Son1" ) 
        ; yyt := yyt ^ . yyHead . Son1 
        | Repetition 
        => yWriteRepetition ( yyt ) 
        ; yyIndentSelector ( "Son1" ) 
        ; yyt := yyt ^ . yyHead . Son1 
        | Node2 
        => yWriteNode2 ( yyt ) 
        ; yyIndentSelector ( "Son2" ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | List 
        => yWriteList ( yyt ) 
        ; yyIndentSelector ( "Son2" ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Sequence 
        => yWriteSequence ( yyt ) 
        ; yyIndentSelector ( "Son2" ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Alternative 
        => yWriteAlternative ( yyt ) 
        ; yyIndentSelector ( "Son2" ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Ch 
        => yWriteCh ( yyt ) 
        ; EXIT 
        | Set 
        => yWriteSet ( yyt ) 
        ; EXIT 
        | String 
        => yWriteString ( yyt ) 
        ; EXIT 
        | Rule 
        => yWriteRule ( yyt ) 
        ; yyIndentSelector ( "Patterns" ) 
        ; yyt := yyt ^ . Rule . Patterns 
        | Pattern 
        => yWritePattern ( yyt ) 
        ; yyIndentSelector ( "RightContext" ) 
        ; yyt := yyt ^ . Pattern . RightContext 
        ELSE 
          EXIT 
        END (* CASE *) 
      END (* LOOP *) 
    ; yyIndentLevel := yyLevel 
    ; yySetIndentInfo ( ) 
    END yyWriteTree0 

; CONST yyNil = '\374' 
; CONST yyNoLabel = '\375' 
; CONST yyLabelDef = '\376' 
; CONST yyLabelUse = '\377' 

; PROCEDURE ReleaseTree0Module ( ) 

  = VAR yyBlockPtr : yytBlockPtr 

  ; BEGIN (* ReleaseTree0Module *) 
      WHILE yyBlockList # NIL 
      DO yyBlockPtr := yyBlockList 
      ; yyBlockList := yyBlockList ^ . yySuccessor 
      ; Memory . Free ( BYTESIZE ( yytBlock ) , yyBlockPtr ) 
      END (* WHILE *) 
    ; yyPoolFreePtr := NIL 
    ; yyPoolMaxPtr := NIL 
    ; HeapUsed := 0 
    END ReleaseTree0Module 

; VAR yyProc : tProcTree 

; PROCEDURE TraverseTree0TD ( yyt : tTree0 ; yyyProc : tProcTree ) 

  = BEGIN (* TraverseTree0TD *) 

      IF topCallCt = topCallStop THEN topCallStop := topCallStop END (* IF *) 
    ; INC ( topCallCt ) 
    ; recCallCt := 0 

    ; yyMarkProc ( yyt ) 
    ; yyProc := yyyProc 
    ; yyTraverseTree0TD ( yyt ) 
    END TraverseTree0TD 

; PROCEDURE yyTraverseTree0TD ( yyt : tTree0 ) 

  = BEGIN (* yyTraverseTree0TD *) 
      LOOP 
        IF ( yyt = NoTree0 ) OR ( yyt ^ . yyHead . yyMark = 0 ) 
        THEN 
          RETURN 
        END (* IF *) 
      ; yyt ^ . yyHead . yyMark := 0 
      ; yyProc ( yyt ) 

      ; CASE yyt ^ . Kind 
        OF Node1 
        => yyt := yyt ^ . yyHead . Son1 
        | Option 
        => yyt := yyt ^ . yyHead . Son1 
        | Repetition 
        => yyt := yyt ^ . yyHead . Son1 
        | Node2 
        => yyTraverseTree0TD ( yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | List 
        => yyTraverseTree0TD ( yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Sequence 
        => yyTraverseTree0TD ( yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Alternative 
        => yyTraverseTree0TD ( yyt ^ . yyHead . Son1 ) 
        ; yyt := yyt ^ . yyHead . Son2 
        | Rule 
        => yyt := yyt ^ . Rule . Patterns 
        | Pattern 
        => yyTraverseTree0TD ( yyt ^ . Pattern . RegExpr ) 
        ; yyt := yyt ^ . Pattern . RightContext 
        ELSE 
          RETURN 
        END (* CASE *) 
      END (* LOOP *) 
    END yyTraverseTree0TD 

; PROCEDURE BeginTree0 ( ) 

  = BEGIN (* BeginTree0 *) 
    END BeginTree0 

; PROCEDURE CloseTree0 ( ) 

  = BEGIN (* CloseTree0 *) 
    END CloseTree0 

; PROCEDURE xxExit ( ) 

  = BEGIN (* xxExit *) 
      ReuseIO . CloseIO ( ) 
    ; System . Exit ( 1 ) 
    END xxExit 

; BEGIN (* Tree0 *) 
    yyBlockList := NIL 
  ; yyPoolFreePtr := NIL 
  ; yyPoolMaxPtr := NIL 
  ; HeapUsed := 0 
  ; yyExit := xxExit 


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
  ; yyMaxSize := BYTESIZE ( yyNode ) 
  ; FOR yyi := 1 TO 13 DO yyNodeSize [ yyi ] := yyMaxSize END (* FOR *) 


  ; yyTypeRange [ Node ] := Pattern 
  ; yyTypeRange [ Node1 ] := Repetition 
  ; yyTypeRange [ Option ] := Option 
  ; yyTypeRange [ Repetition ] := Repetition 
  ; yyTypeRange [ Node2 ] := Alternative 
  ; yyTypeRange [ List ] := List 
  ; yyTypeRange [ Sequence ] := Sequence 
  ; yyTypeRange [ Alternative ] := Alternative 
  ; yyTypeRange [ Ch ] := Ch 
  ; yyTypeRange [ Set ] := Set 
  ; yyTypeRange [ String ] := String 
  ; yyTypeRange [ Rule ] := Rule 
  ; yyTypeRange [ Pattern ] := Pattern 
  ; yyRecursionLevel := 0 
  ; yyTreeStoreSize := yyInitTreeStoreSize 
  ; DynArray . MakeArray 
      ( LOOPHOLE ( yyTreeStorePtr , ADDRESS ) 
      , yyTreeStoreSize 
      , BYTESIZE ( tTree0 ) 
      ) 
  ; BeginTree0 ( ) 
  END Tree0 
. 

