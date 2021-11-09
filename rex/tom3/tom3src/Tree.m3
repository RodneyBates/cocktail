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

 UNSAFE MODULE Tree;


FROM SYSTEM IMPORT SHORTCARD;
FROM Memory	IMPORT Alloc;
FROM Texts	IMPORT tText, WriteText;
FROM Sets	IMPORT tSet, WriteSet;
FROM Strings	IMPORT tString, WriteL;
FROM StringMem	IMPORT tStringRef, GetString;
FROM IO		IMPORT StdOutput, WriteS, WriteI, WriteNl, WriteB;
FROM Layout	IMPORT WriteSpace, WriteChar;
FROM Positions	IMPORT tPosition;

IMPORT Strings;

PROCEDURE MakeTree1 (pRule: SHORTCARD; pSon1: tTree): tTree =
   VAR Tree : tTree;
   BEGIN
      Tree := Alloc (BYTESIZE (Node1));
      WITH m2tom3_with_14=Tree^.vNode1(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode1' in line 50
 $$ *) DO
	 m2tom3_with_14.Rule := pRule;
	 m2tom3_with_14.Son1 := pSon1;
      END;
      RETURN Tree;
   END MakeTree1;

PROCEDURE MakeTree2 (pRule: SHORTCARD; pSon1, pSon2: tTree): tTree =
   VAR Tree : tTree;
   BEGIN
      Tree := Alloc (BYTESIZE (Node2));
      WITH m2tom3_with_15=Tree^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 61
 $$ *) DO
	 m2tom3_with_15.Rule := pRule;
	 m2tom3_with_15.Son1 := pSon1;
	 m2tom3_with_15.Son2 := pSon2;
      END;
      RETURN Tree;
   END MakeTree2;

PROCEDURE MakeTreeCh (pRule: SHORTCARD; pCh: CHAR): tTree =
   VAR Tree : tTree;
   BEGIN
      Tree := Alloc (BYTESIZE (NodeCh));
      WITH m2tom3_with_16=Tree^.vNodeCh(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeCh' in line 73
 $$ *) DO
	 m2tom3_with_16.Rule := pRule;
	 m2tom3_with_16.Ch   := pCh;
      END;
      RETURN Tree;
   END MakeTreeCh;

PROCEDURE MakeTreeSet (pRule: SHORTCARD; pSet: tSet): tTree =
   VAR Tree : tTree;
   BEGIN
      Tree := Alloc (BYTESIZE (NodeSet));
      WITH m2tom3_with_17=Tree^.vNodeSet(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeSet' in line 84
 $$ *) DO
	 m2tom3_with_17.Rule := pRule;
	 m2tom3_with_17.Set  := pSet;
      END;
      RETURN Tree;
   END MakeTreeSet;

PROCEDURE MakeTreeString(pRule: SHORTCARD; pString: tStringRef): tTree =
   VAR Tree : tTree;
   BEGIN
      Tree := Alloc (BYTESIZE (NodeString));
      WITH m2tom3_with_18=Tree^.vNodeString(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeString' in line 95
 $$ *) DO
	 m2tom3_with_18.Rule	:= pRule;
	 m2tom3_with_18.String	:= pString;
      END;
      RETURN Tree;
   END MakeTreeString;

PROCEDURE MakeTreeRule	(pRule: SHORTCARD; pPatterns: tTree; pTargetCode:
			tText; pLine, pCodeMode, pRuleNr: SHORTCARD): tTree =
   VAR Tree : tTree;
   BEGIN
      Tree := Alloc (BYTESIZE (NodeRule));
      WITH m2tom3_with_19=Tree^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 107
 $$ *) DO
	 m2tom3_with_19.Rule		:= pRule;
	 m2tom3_with_19.Patterns	:= pPatterns;
	 m2tom3_with_19.TargetCode	:= pTargetCode;
	 m2tom3_with_19.Line		:= pLine;
	 m2tom3_with_19.CodeMode	:= pCodeMode;
	 m2tom3_with_19.RuleNr		:= pRuleNr;
      END;
      RETURN Tree;
   END MakeTreeRule;

PROCEDURE MakeTreePattern(pRule: SHORTCARD; pStartStates: tSet; pRegExpr,
			pRightContext: tTree; pIsConstantRE: BOOLEAN;
			pPatternNr: SHORTCARD; pPosition: tPosition): tTree =
   VAR Tree : tTree;
   BEGIN
      Tree := Alloc (BYTESIZE (NodePattern));
      WITH m2tom3_with_20=Tree^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 124
 $$ *) DO
	 m2tom3_with_20.Rule		:= pRule;
	 m2tom3_with_20.StartStates	:= pStartStates;
	 m2tom3_with_20.RegExpr	:= pRegExpr;
	 m2tom3_with_20.RightContext	:= pRightContext;
	 m2tom3_with_20.IsConstantRE	:= pIsConstantRE;
	 m2tom3_with_20.PatternNr	:= pPatternNr;
	 m2tom3_with_20.Position	:= pPosition;
      END;
      RETURN Tree;
   END MakeTreePattern;

PROCEDURE WriteTree (t: tTree) =
   VAR
      i		: SHORTCARD;
      string	: Strings.tString;
   BEGIN
      FOR i := 1 TO indent DO
	 WriteSpace (StdOutput);
      END;

      IF t = NoTree THEN
	 WriteS (StdOutput, ARRAY [0..6] OF CHAR{'N','o','T','r','e','e','\000'});	WriteNl (StdOutput);
	 RETURN;
      END;

      CASE t^.vNode0(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode0' in line 150
 $$ *).Rule OF
      |  nRule		=> WriteS (StdOutput, ARRAY [0..5] OF CHAR{'R','u','l','e',' ','\000'});
			  WriteI (StdOutput, t^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 152
 $$ *).RuleNr, 1);
								WriteNl (StdOutput);
			  WriteText (StdOutput, t^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 154
 $$ *).TargetCode);
      |  nList		=> WriteS (StdOutput, ARRAY [0..4] OF CHAR{'L','i','s','t','\000'});		WriteNl (StdOutput);
      |  nPattern	=> WriteS (StdOutput, ARRAY [0..8] OF CHAR{'P','a','t','t','e','r','n',' ','\000'});
			  WriteSet (StdOutput, t^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 157
 $$ *).StartStates);
	 		  WriteSpace (StdOutput);
			  WriteB (StdOutput, t^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 159
 $$ *).IsConstantRE);
			  WriteI (StdOutput, t^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 160
 $$ *).PatternNr, 5);
								WriteNl (StdOutput);
      |  nAlternative	=> WriteS (StdOutput, ARRAY [0..11] OF CHAR{'A','l','t','e','r','n','a','t','i','v','e','\000'});	WriteNl (StdOutput);
      |  nSequence	=> WriteS (StdOutput, ARRAY [0..8] OF CHAR{'S','e','q','u','e','n','c','e','\000'});	WriteNl (StdOutput);
      |  nRepetition	=> WriteS (StdOutput, ARRAY [0..10] OF CHAR{'R','e','p','e','t','i','t','i','o','n','\000'});	WriteNl (StdOutput);
      |  nOption	=> WriteS (StdOutput, ARRAY [0..6] OF CHAR{'O','p','t','i','o','n','\000'});		WriteNl (StdOutput);
      |  nChar		=> WriteS (StdOutput, ARRAY [0..5] OF CHAR{'C','h','a','r',' ','\000'});
			  WriteChar (StdOutput, t^.vNodeCh(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeCh' in line 167
 $$ *).Ch);	WriteNl (StdOutput);
      |  nSet		=> WriteS (StdOutput, ARRAY [0..4] OF CHAR{'S','e','t',' ','\000'});
			  WriteSet (StdOutput, t^.vNodeSet(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeSet' in line 169
 $$ *).Set);WriteNl (StdOutput);
      |  nString	=> WriteS (StdOutput, ARRAY [0..7] OF CHAR{'S','t','r','i','n','g',' ','\000'});
			  GetString (t^.vNodeString(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeString' in line 171
 $$ *).String, string);
			  Strings.WriteS (StdOutput, string);	WriteNl (StdOutput);
      END;

      IF t^.vNode0(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode0' in line 175
 $$ *).Rule # nList THEN
	 INC (indent, 2);
      END;
      CASE t^.vNode0(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode0' in line 178
 $$ *).Rule OF
      |  nRule		=> WriteTree (t^.vNodeRule(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodeRule' in line 179
 $$ *).Patterns);
      |  nList		=> WriteTree (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 180
 $$ *).Son1);
      			  WriteTree (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 181
 $$ *).Son2);
      |  nPattern	=> WriteTree (t^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 182
 $$ *).RegExpr);
      			  WriteTree (t^.vNodePattern(* $$ m2tom3 warning: application of variant field, possible cast of 'vNodePattern' in line 183
 $$ *).RightContext);
      |  nAlternative	=> WriteTree (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 184
 $$ *).Son1);
      			  WriteTree (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 185
 $$ *).Son2);
      |  nSequence	=> WriteTree (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 186
 $$ *).Son1);
      			  WriteTree (t^.vNode2(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode2' in line 187
 $$ *).Son2);
      |  nRepetition	=> WriteTree (t^.vNode1(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode1' in line 188
 $$ *).Son1);
      |  nOption	=> WriteTree (t^.vNode1(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode1' in line 189
 $$ *).Son1);
      ELSE
      END;
      IF t^.vNode0(* $$ m2tom3 warning: application of variant field, possible cast of 'vNode0' in line 192
 $$ *).Rule # nList THEN
	 DEC (indent, 2);
      END;
   END WriteTree;

VAR indent	: SHORTCARD;

BEGIN
   indent := 0;
END Tree.

