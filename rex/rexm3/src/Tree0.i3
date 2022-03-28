UNSAFE INTERFACE Tree0 

; FROM SYSTEM IMPORT M2LONGCARD 

; FROM SYSTEM IMPORT SHORTINT , SHORTCARD 
; IMPORT SYSTEM , ReuseIO 
(* line 23 "../src/rex.cg" *) 

; FROM Sets IMPORT tSet 

; FROM Texts IMPORT tText 

; FROM StringMem IMPORT tStringRef 

; FROM Positions IMPORT tPosition 

; FROM Tree IMPORT tTree 


; CONST NoTree0 = NIL 

  ; Node = 1 
  ; Node1 = 2 
  ; Option = 3 
  ; Repetition = 4 
  ; Node2 = 5 
  ; List = 6 
  ; Sequence = 7 
  ; Alternative = 8 
  ; Ch = 9 
  ; Set = 10 
  ; String = 11 
  ; Rule = 12 
  ; Pattern = 13 

; TYPE tTree0 = UNTRACED BRANDED REF yyNode 
  ; tProcTree = PROCEDURE ( p0 : tTree0 ) 




; TYPE yytNodeHead
         = RECORD
             yyMark : SHORTCARD
           ; Tree : tTree 
           ; IsConstantRE : BOOLEAN 
           ; LeafCount : SHORTINT 
           ; NodeCount : SHORTINT 
           ; Son1 : tTree0 
           ; Son2 : tTree0 
           END (* RECORD *)

  ; yNode 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      END (* RECORD *) 
  ; yNode1 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; zzSon1 : tTree0 
      END (* RECORD *) 
  ; yOption 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; zzSon1 : tTree0 
      END (* RECORD *) 
  ; yRepetition 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; zzSon1 : tTree0 
      END (* RECORD *) 
  ; yNode2 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; zzSon1 : tTree0 
      ; zzSon2 : tTree0 
      END (* RECORD *) 
  ; yList 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; zzSon1 : tTree0 
      ; zzSon2 : tTree0 
      END (* RECORD *) 
  ; ySequence 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; zzSon1 : tTree0 
      ; zzSon2 : tTree0 
      END (* RECORD *) 
  ; yAlternative 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; zzSon1 : tTree0 
      ; zzSon2 : tTree0 
      END (* RECORD *) 
  ; yCh 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; Ch : CHAR 
      END (* RECORD *) 
  ; ySet 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; Set : tSet 
      ; card : SHORTCARD 
      END (* RECORD *) 
  ; yString 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; String : tStringRef 
      END (* RECORD *) 
  ; yRule 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; Patterns : tTree0 
      ; TargetCode : tText 
      ; Line : SHORTCARD 
      ; CodeMode : SHORTCARD 
      ; RuleNr : SHORTCARD 
      END (* RECORD *) 
  ; yPattern 
    = RECORD 
        zzHead : yytNodeHead 
      ; zzTree : tTree 
      ; zzIsConstantRE : BOOLEAN 
      ; zzLeafCount : SHORTINT 
      ; zzNodeCount : SHORTINT 
      ; StartStates : tSet 
      ; RegExpr : tTree0 
      ; RightContext : tTree0 
      ; PatternNr : SHORTCARD 
      ; Position : tPosition 
      ; card : SHORTINT 
      END (* RECORD *) 

  ; yyNode 
    = RECORD 

        Kind : SHORTCARD 
      ; yyHead : yytNodeHead 
      ; Node : yNode 
      ; Node1 : yNode1 
      ; Option : yOption 
      ; Repetition : yRepetition 
      ; Node2 : yNode2 
      ; List : yList 
      ; Sequence : ySequence 
      ; Alternative : yAlternative 
      ; Ch : yCh 
      ; Set : ySet 
      ; String : yString 
      ; Rule : yRule 
      ; Pattern : yPattern 

      END (* RECORD *) 

; VAR Tree0Root : tTree0 
; VAR HeapUsed : M2LONGCARD 
; VAR yyPoolFreePtr , yyPoolMaxPtr : ADDRESS 
; VAR yyNodeSize : ARRAY [ 0 .. 13 ] OF INTEGER 
; VAR yyExit : SYSTEM . PROC 

; PROCEDURE yyAlloc ( ) : tTree0 

; PROCEDURE MakeTree0 ( Kind : SHORTCARD ) : tTree0 

; PROCEDURE IsType ( Tree : tTree0 ; Kind : SHORTCARD ) : BOOLEAN 

; PROCEDURE mNode ( ) : tTree0 

; PROCEDURE mNode1 ( pSon1 : tTree0 ) : tTree0 

; PROCEDURE mOption ( pSon1 : tTree0 ) : tTree0 

; PROCEDURE mRepetition ( pSon1 : tTree0 ) : tTree0 

; PROCEDURE mNode2 ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

; PROCEDURE mList ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

; PROCEDURE mSequence ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

; PROCEDURE mAlternative ( pSon1 : tTree0 ; pSon2 : tTree0 ) : tTree0 

; PROCEDURE mCh ( pCh : CHAR ) : tTree0 

; PROCEDURE mSet ( pSet : tSet ) : tTree0 

; PROCEDURE mString ( pString : tStringRef ) : tTree0 

; PROCEDURE mRule 
    ( pPatterns : tTree0 
    ; pTargetCode : tText 
    ; pLine : SHORTCARD 
    ; pCodeMode : SHORTCARD 
    ; pRuleNr : SHORTCARD 
    ) 
    : tTree0 

; PROCEDURE mPattern 
    ( pStartStates : tSet 
    ; pRegExpr : tTree0 
    ; pRightContext : tTree0 
    ; pPatternNr : SHORTCARD 
    ; pPosition : tPosition 
    ) 
    : tTree0 

; PROCEDURE ReleaseTree0Module ( ) 

; PROCEDURE WriteTree0 ( f : ReuseIO . tFile ; Tree : tTree0 ) 

; PROCEDURE TraverseTree0TD ( Tree : tTree0 ; Proc : tProcTree ) 

; PROCEDURE BeginTree0 ( ) 

; PROCEDURE CloseTree0 ( ) 

; 
END Tree0 
. 

