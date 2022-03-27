(* $Id: Tree.md,v 3.2 1992/08/07 15:10:26 grosch rel $ *) 

(* $Log: Tree.md,v $ 
 * Revision 3.2  1992/08/07  15:10:26  grosch 
 * allow several scanner and parsers; extend module Errors 
 * 
 * Revision 3.1  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.0  91/04/04  18:08:03  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 2.0  91/03/08  18:18:07  grosch 
 * turned tables into initialized arrays (in C) 
 * reduced case size 
 * changed interface for source position 
 * 
 * Revision 1.2  89/02/23  15:56:01  grosch 
 * added completeness check for the automaton 
 * 
 * Revision 1.1  89/01/17  15:01:41  grosch 
 * correction and redesign of source position handling 
 * 
 * Revision 1.0  88/10/04  11:59:54  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE INTERFACE Tree 

; IMPORT Word 

; FROM SYSTEM IMPORT SHORTCARD 

; FROM Sets IMPORT tSet 

; FROM Texts IMPORT tText 

; FROM StringMem IMPORT tStringRef 

; FROM Positions IMPORT tPosition 

; CONST NoTree = NIL 

  ; nList = 1 
  ; nRule = 2 
  ; nPattern = 3 
  ; nAlternative = 4 
  ; nSequence = 5 
  ; nRepetition = 6 
  ; nOption = 7 
  ; nChar = 8 
  ; nSet = 9 
  ; nString = 10 

; TYPE tTree = UNTRACED BRANDED REF Node 

  ; Node0 = RECORD zzRule : SHORTCARD END (* RECORD *) 

  ; Node1 = RECORD zzRule : SHORTCARD ; Son1 : tTree END (* RECORD *) 

  ; Node2 
    = RECORD zzRule : SHORTCARD ; Son1 : tTree ; Son2 : tTree END (* RECORD *) 

  ; NodeCh = RECORD zzRule : SHORTCARD ; Ch : CHAR END (* RECORD *) 

  ; NodeSet = RECORD zzRule : SHORTCARD ; Set : tSet END (* RECORD *) 

  ; NodeString 
    = RECORD zzRule : SHORTCARD ; String : tStringRef END (* RECORD *) 

  ; NodeRule 
    = RECORD 
        zzRule : SHORTCARD 
      ; Patterns : tTree 
      ; TargetCode : tText 
      ; Line : SHORTCARD 
      ; CodeMode : SHORTCARD 
      ; RuleNr : SHORTCARD 
      END (* RECORD *) 

  ; NodePattern 
    = RECORD 
        zzRule : SHORTCARD 
      ; StartStates : tSet 
      ; RegExpr : tTree 
      ; RightContext : tTree 
      ; IsConstantRE : BOOLEAN 
      ; PatternNr : SHORTCARD 
      ; Position : tPosition 
      END (* RECORD *) 

  ; Node 
    = RECORD 
        Rule : SHORTCARD 
      ; vNode0 : Node0 
      ; vNode1 : Node1 
      ; vNode2 : Node2 
      ; vNodeCh : NodeCh 
      ; vNodeSet : NodeSet 
      ; vNodeString : NodeString 
      ; vNodeRule : NodeRule 
      ; vNodePattern : NodePattern 

      END (* RECORD *) 

; PROCEDURE MakeTree1 ( pRule : SHORTCARD ; pSon1 : tTree ) : tTree 

; PROCEDURE MakeTree2 ( pRule : SHORTCARD ; pSon1 , pSon2 : tTree ) : tTree 

; PROCEDURE MakeTreeCh ( pRule : SHORTCARD ; pCh : CHAR ) : tTree 

; PROCEDURE MakeTreeSet ( pRule : SHORTCARD ; pSet : tSet ) : tTree 

; PROCEDURE MakeTreeString 
    ( pRule : SHORTCARD ; pString : tStringRef ) : tTree 

; PROCEDURE MakeTreeRule 
    ( pRule : SHORTCARD 
    ; pPatterns : tTree 
    ; pTargetCode : tText 
    ; pLine , pCodeMode , pRuleNr : SHORTCARD 
    ) 
    : tTree 

; PROCEDURE MakeTreePattern 
    ( pRule : SHORTCARD 
    ; pStartStates : tSet 
    ; pRegExpr , pRightContext : tTree 
    ; pIsConstantRE : BOOLEAN 
    ; pPatternNr : SHORTCARD 
    ; pPosition : tPosition 
    ) 
    : tTree 

; PROCEDURE WriteTree ( t : tTree ) 

; 
END Tree 
. 

