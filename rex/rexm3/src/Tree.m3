(* $Id: Tree.mi,v 3.2 1992/08/07 15:10:26 grosch rel $ *) 

(* $Log: Tree.mi,v $ 
 * Revision 3.2  1992/08/07  15:10:26  grosch 
 * allow several scanner and parsers; extend module Errors 
 * 
 * Revision 3.1  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.0  91/04/04  18:08:05  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 2.0  91/03/08  18:18:09  grosch 
 * turned tables into initialized arrays (in C) 
 * reduced case size 
 * changed interface for source position 
 * 
 * Revision 1.2  89/02/23  15:56:03  grosch 
 * added completeness check for the automaton 
 * 
 * Revision 1.1  89/01/17  15:01:45  grosch 
 * correction and redesign of source position handling 
 * 
 * Revision 1.0  88/10/04  11:59:55  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE MODULE Tree 


; FROM SYSTEM IMPORT SHORTCARD 

; FROM Memory IMPORT Alloc 

; FROM Texts IMPORT tText , WriteText 

; FROM Sets IMPORT tSet , WriteSet 

; FROM Strings IMPORT tString , WriteL 

; FROM StringMem IMPORT tStringRef , GetString 

; FROM ReuseIO IMPORT StdOutput , WriteT , WriteI , WriteNl , WriteB 

; FROM Layout IMPORT WriteSpace , WriteChar 

; FROM Positions IMPORT tPosition 

; IMPORT Strings 

; PROCEDURE MakeTree1 ( pRule : SHORTCARD ; pSon1 : tTree ) : tTree 

  = VAR Tree : tTree 

  ; BEGIN (* MakeTree1 *) 
      Tree := Alloc ( BYTESIZE ( Node ) ) 
    ; WITH With_29 = Tree ^ . vNode1 
      DO With_29 . Rule := pRule 
      ; With_29 . Son1 := pSon1 
      END (* WITH *) 
    ; RETURN Tree 
    END MakeTree1 

; PROCEDURE MakeTree2 ( pRule : SHORTCARD ; pSon1 , pSon2 : tTree ) : tTree 

  = VAR Tree : tTree 

  ; BEGIN (* MakeTree2 *) 
      Tree := Alloc ( BYTESIZE ( Node ) ) 
    ; WITH With_30 = Tree ^ . vNode2 
      DO With_30 . Rule := pRule 
      ; With_30 . Son1 := pSon1 
      ; With_30 . Son2 := pSon2 
      END (* WITH *) 
    ; RETURN Tree 
    END MakeTree2 

; PROCEDURE MakeTreeCh ( pRule : SHORTCARD ; pCh : CHAR ) : tTree 

  = VAR Tree : tTree 

  ; BEGIN (* MakeTreeCh *) 
      Tree := Alloc ( BYTESIZE ( Node ) ) 
    ; WITH With_31 = Tree ^ . vNodeCh 
      DO With_31 . Rule := pRule 
      ; With_31 . Ch := pCh 
      END (* WITH *) 
    ; RETURN Tree 
    END MakeTreeCh 

; PROCEDURE MakeTreeSet ( pRule : SHORTCARD ; pSet : tSet ) : tTree 

  = VAR Tree : tTree 

  ; BEGIN (* MakeTreeSet *) 
      Tree := Alloc ( BYTESIZE ( Node ) ) 
    ; WITH With_32 = Tree ^ . vNodeSet 
      DO With_32 . Rule := pRule 
      ; With_32 . Set := pSet 
      END (* WITH *) 
    ; RETURN Tree 
    END MakeTreeSet 

; PROCEDURE MakeTreeString 
    ( pRule : SHORTCARD ; pString : tStringRef ) : tTree 

  = VAR Tree : tTree 

  ; BEGIN (* MakeTreeString *) 
      Tree := Alloc ( BYTESIZE ( Node ) ) 
    ; WITH With_33 = Tree ^ . vNodeString 
      DO With_33 . Rule := pRule 
      ; With_33 . String := pString 
      END (* WITH *) 
    ; RETURN Tree 
    END MakeTreeString 

; PROCEDURE MakeTreeRule 
    ( pRule : SHORTCARD 
    ; pPatterns : tTree 
    ; pTargetCode : tText 
    ; pLine , pCodeMode , pRuleNr : SHORTCARD 
    ) 
    : tTree 

  = VAR Tree : tTree 

  ; BEGIN (* MakeTreeRule *) 
      Tree := Alloc ( BYTESIZE ( Node ) ) 
    ; WITH With_34 = Tree ^ . vNodeRule 
      DO With_34 . Rule := pRule 
      ; With_34 . Patterns := pPatterns 
      ; With_34 . TargetCode := pTargetCode 
      ; With_34 . Line := pLine 
      ; With_34 . CodeMode := pCodeMode 
      ; With_34 . RuleNr := pRuleNr 
      END (* WITH *) 
    ; RETURN Tree 
    END MakeTreeRule 

; PROCEDURE MakeTreePattern 
    ( pRule : SHORTCARD 
    ; pStartStates : tSet 
    ; pRegExpr , pRightContext : tTree 
    ; pIsConstantRE : BOOLEAN 
    ; pPatternNr : SHORTCARD 
    ; pPosition : tPosition 
    ) 
    : tTree 

  = VAR Tree : tTree 

  ; BEGIN (* MakeTreePattern *) 
      Tree := Alloc ( BYTESIZE ( Node ) ) 
    ; WITH With_35 = Tree ^ . vNodePattern 
      DO With_35 . Rule := pRule 
      ; With_35 . StartStates := pStartStates 
      ; With_35 . RegExpr := pRegExpr 
      ; With_35 . RightContext := pRightContext 
      ; With_35 . IsConstantRE := pIsConstantRE 
      ; With_35 . PatternNr := pPatternNr 
      ; With_35 . Position := pPosition 
      END (* WITH *) 
    ; RETURN Tree 
    END MakeTreePattern 

; PROCEDURE WriteTree ( t : tTree ) 

  = VAR string : Strings . tString 

  ; BEGIN (* WriteTree *) 
      FOR i := 1 TO indent DO WriteSpace ( StdOutput ) END (* FOR *) 

    ; IF t = NoTree 
      THEN 
        WriteT ( StdOutput , "NoTree" ) 
      ; WriteNl ( StdOutput ) 
      ; RETURN 
      END (* IF *) 

    ; CASE t ^ . vNode0 . Rule 
      OF nRule 
      => WriteT ( StdOutput , "Rule " ) 
      ; WriteI ( StdOutput , t ^ . vNodeRule . RuleNr , 1 ) 
      ; WriteNl ( StdOutput ) 
      ; WriteText ( StdOutput , t ^ . vNodeRule . TargetCode ) 
      | nList 
      => WriteT ( StdOutput , "List" ) 
      ; WriteNl ( StdOutput ) 
      | nPattern 
      => WriteT ( StdOutput , "Pattern " ) 
      ; WriteSet ( StdOutput , t ^ . vNodePattern . StartStates ) 
      ; WriteSpace ( StdOutput ) 
      ; WriteB ( StdOutput , t ^ . vNodePattern . IsConstantRE ) 
      ; WriteI ( StdOutput , t ^ . vNodePattern . PatternNr , 5 ) 
      ; WriteNl ( StdOutput ) 
      | nAlternative 
      => WriteT ( StdOutput , "Alternative" ) 
      ; WriteNl ( StdOutput ) 
      | nSequence 
      => WriteT ( StdOutput , "Sequence" ) 
      ; WriteNl ( StdOutput ) 
      | nRepetition 
      => WriteT ( StdOutput , "Repetition" ) 
      ; WriteNl ( StdOutput ) 
      | nOption 
      => WriteT ( StdOutput , "Option" ) 
      ; WriteNl ( StdOutput ) 
      | nChar 
      => WriteT ( StdOutput , "Char " ) 
      ; WriteChar ( StdOutput , t ^ . vNodeCh . Ch ) 
      ; WriteNl ( StdOutput ) 
      | nSet 
      => WriteT ( StdOutput , "Set " ) 
      ; WriteSet ( StdOutput , t ^ . vNodeSet . Set ) 
      ; WriteNl ( StdOutput ) 
      | nString 
      => WriteT ( StdOutput , "String " ) 
      ; GetString ( t ^ . vNodeString . String , string ) 
      ; Strings . WriteS ( StdOutput , string ) 
      ; WriteNl ( StdOutput ) 
      END (* CASE *) 

    ; IF t ^ . vNode0 . Rule # nList THEN INC ( indent , 2 ) END (* IF *) 
    ; CASE t ^ . vNode0 . Rule 
      OF nRule 
      => WriteTree ( t ^ . vNodeRule . Patterns ) 
      | nList 
      => WriteTree ( t ^ . vNode2 . Son1 ) 
      ; WriteTree ( t ^ . vNode2 . Son2 ) 
      | nPattern 
      => WriteTree ( t ^ . vNodePattern . RegExpr ) 
      ; WriteTree ( t ^ . vNodePattern . RightContext ) 
      | nAlternative 
      => WriteTree ( t ^ . vNode2 . Son1 ) 
      ; WriteTree ( t ^ . vNode2 . Son2 ) 
      | nSequence 
      => WriteTree ( t ^ . vNode2 . Son1 ) 
      ; WriteTree ( t ^ . vNode2 . Son2 ) 
      | nRepetition 
      => WriteTree ( t ^ . vNode1 . Son1 ) 
      | nOption 
      => WriteTree ( t ^ . vNode1 . Son1 ) 
      ELSE 
      END (* CASE *) 
    ; IF t ^ . vNode0 . Rule # nList THEN DEC ( indent , 2 ) END (* IF *) 
    END WriteTree 

; VAR indent : SHORTCARD 

; BEGIN (* Tree *) 
    indent := 0 
  END Tree 
. 

