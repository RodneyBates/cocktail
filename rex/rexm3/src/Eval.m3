

 UNSAFE MODULE Eval;

IMPORT Word, Tree0;
(* line 61 "../src/rex.cg" *)

FROM Strings    IMPORT tString, AssignEmpty, Length, Append, Char;
FROM StringMem  IMPORT GetString, PutString;
FROM Sets       IMPORT tSet, MakeSet, Card, Assign, Intersection, Select, Minimum,
                        IsEmpty, Maximum, IsElement, Include;
FROM Classes    IMPORT ToClass, IsInSetMem, SetMemPtr, CharSet;
FROM Dfa        IMPORT LastCh;
IMPORT StringMem;

FROM Tree       IMPORT
   NoTree       , MakeTree1     , MakeTree2     ,
   MakeTreeRule , MakeTreePattern, MakeTreeCh   , MakeTreeSet   ,
   MakeTreeString, nList        , nRule         , nPattern      ,
   nAlternative , nSequence     , nRepetition   , nOption       ,
   nChar        , nSet          , nString       ;

VAR
   String1, String2     : tString;
   Set1, Set2           : tSet;
   j                    : Word.T;


PROCEDURE Eval (yyt: Tree0.tTree0) =
 BEGIN yyVisit1 (yyt); END Eval;

PROCEDURE yyVisit1 (yyt: Tree0.tTree0) =
 BEGIN
  CASE yyt^.Kind OF
| Tree0.Node=>
(* line 200 "../src/rex.cg" *)
 yyt^.Node.NodeCount := 0;
(* line 176 "../src/rex.cg" *)
 yyt^.Node.LeafCount := 0;
(* line 159 "../src/rex.cg" *)
 yyt^.Node.IsConstantRE := TRUE;
(* line 90 "../src/rex.cg" *)
 yyt^.Node.Tree := NoTree;
| Tree0.Node1=>
yyVisit1 (yyt^.Node1.Son1);
(* line 201 "../src/rex.cg" *)
 yyt^.Node1.NodeCount := yyt^.Node1.Son1^.Node.NodeCount;
(* line 177 "../src/rex.cg" *)
 yyt^.Node1.LeafCount := yyt^.Node1.Son1^.Node.LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.Node1.IsConstantRE := TRUE;
(* line 90 "../src/rex.cg" *)
 yyt^.Node1.Tree := NoTree;
| Tree0.Option=>
yyVisit1 (yyt^.Option.Son1);
(* line 201 "../src/rex.cg" *)
 yyt^.Option.NodeCount := yyt^.Option.Son1^.Node.NodeCount;
(* line 177 "../src/rex.cg" *)
 yyt^.Option.LeafCount := yyt^.Option.Son1^.Node.LeafCount;
(* line 160 "../src/rex.cg" *)
 yyt^.Option.IsConstantRE := FALSE;
(* line 91 "../src/rex.cg" *)
 yyt^.Option.Tree := MakeTree1 (nOption, yyt^.Option.Son1^.Node.Tree);
| Tree0.Repetition=>
yyVisit1 (yyt^.Repetition.Son1);
(* line 201 "../src/rex.cg" *)
 yyt^.Repetition.NodeCount := yyt^.Repetition.Son1^.Node.NodeCount;
(* line 177 "../src/rex.cg" *)
 yyt^.Repetition.LeafCount := yyt^.Repetition.Son1^.Node.LeafCount;
(* line 161 "../src/rex.cg" *)
 yyt^.Repetition.IsConstantRE := FALSE;
(* line 92 "../src/rex.cg" *)
 yyt^.Repetition.Tree := MakeTree1 (nRepetition, yyt^.Repetition.Son1^.Node.Tree);
| Tree0.Node2=>
yyVisit1 (yyt^.Node2.Son2);
yyVisit1 (yyt^.Node2.Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.Node2.NodeCount := yyt^.Node2.Son1^.Node.NodeCount + yyt^.Node2.Son2^.Node.NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.Node2.LeafCount := yyt^.Node2.Son1^.Node.LeafCount + yyt^.Node2.Son2^.Node.LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.Node2.IsConstantRE := TRUE;
(* line 90 "../src/rex.cg" *)
 yyt^.Node2.Tree := NoTree;
| Tree0.List=>
yyVisit1 (yyt^.List.Son2);
yyVisit1 (yyt^.List.Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.List.NodeCount := yyt^.List.Son1^.Node.NodeCount + yyt^.List.Son2^.Node.NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.List.LeafCount := yyt^.List.Son1^.Node.LeafCount + yyt^.List.Son2^.Node.LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.List.IsConstantRE := TRUE;
(* line 93 "../src/rex.cg" *)
 yyt^.List.Tree := MakeTree2 (nList, yyt^.List.Son1^.Node.Tree, yyt^.List.Son2^.Node.Tree);
| Tree0.Sequence=>
yyVisit1 (yyt^.Sequence.Son2);
yyVisit1 (yyt^.Sequence.Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.Sequence.NodeCount := yyt^.Sequence.Son1^.Node.NodeCount + yyt^.Sequence.Son2^.Node.NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.Sequence.LeafCount := yyt^.Sequence.Son1^.Node.LeafCount + yyt^.Sequence.Son2^.Node.LeafCount;
(* line 162 "../src/rex.cg" *)
 yyt^.Sequence.IsConstantRE := yyt^.Sequence.Son1^.Node.IsConstantRE AND yyt^.Sequence.Son2^.Node.IsConstantRE;
(* line 94 "../src/rex.cg" *)
 yyt^.Sequence.Tree := MakeTree2 (nSequence, yyt^.Sequence.Son1^.Node.Tree, yyt^.Sequence.Son2^.Node.Tree);
| Tree0.Alternative=>
yyVisit1 (yyt^.Alternative.Son2);
yyVisit1 (yyt^.Alternative.Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.Alternative.NodeCount := yyt^.Alternative.Son1^.Node.NodeCount + yyt^.Alternative.Son2^.Node.NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.Alternative.LeafCount := yyt^.Alternative.Son1^.Node.LeafCount + yyt^.Alternative.Son2^.Node.LeafCount;
(* line 163 "../src/rex.cg" *)
 yyt^.Alternative.IsConstantRE := FALSE;
(* line 95 "../src/rex.cg" *)
 yyt^.Alternative.Tree := MakeTree2 (nAlternative, yyt^.Alternative.Son1^.Node.Tree, yyt^.Alternative.Son2^.Node.Tree);
| Tree0.Ch=>
(* line 203 "../src/rex.cg" *)
 yyt^.Ch.NodeCount := 1;
(* line 179 "../src/rex.cg" *)
 yyt^.Ch.LeafCount := 1;
(* line 164 "../src/rex.cg" *)
 yyt^.Ch.IsConstantRE := TRUE;
(* line 96 "../src/rex.cg" *)
 yyt^.Ch.Tree := MakeTreeCh (nChar, ToClass [yyt^.Ch.Ch]);
| Tree0.Set=>
(* line 97 "../src/rex.cg" *)

                    j := IsInSetMem (yyt^.Set.Set);
                    IF j # 0 THEN
                       yyt^.Set.card := Card (SetMemPtr^[j].Classes);
                       Assign (Set1, yyt^.Set.Set);
                       Intersection (Set1, CharSet);
                       INC (yyt^.Set.card, Card (Set1));
                       IF yyt^.Set.card = 1 THEN
                          IF Card (SetMemPtr^[j].Classes) = 1 THEN
                             yyt^.Set.Tree := MakeTreeCh (nChar, VAL (Select (SetMemPtr^[j].Classes),CHAR));
                          ELSE
                             yyt^.Set.Tree := MakeTreeCh (nChar, ToClass [VAL (Select (Set1),CHAR)]);
                          END;
                       ELSE
                          MakeSet (Set2, ORD (LastCh));
                          IF NOT IsEmpty (Set1) THEN
                             FOR i := Minimum (Set1) TO Maximum (Set1) DO
                                IF IsElement (i, Set1) THEN
                                   Include (Set2, ORD (ToClass [VAL (i,CHAR)]));
                                END;
                             END;
                          END;
                                        
                          IF NOT IsEmpty (SetMemPtr^[j].Classes) THEN
                             FOR i := Minimum (SetMemPtr^[j].Classes) TO Maximum (SetMemPtr^[j].Classes) DO
                                IF IsElement (i, SetMemPtr^[j].Classes) THEN
                                   Include (Set2, i);
                                END;
                             END;
                          END;
                          yyt^.Set.Tree := MakeTreeSet (nSet, Set2);
                       END;
                    ELSE
                       yyt^.Set.card := Card (yyt^.Set.Set);
                       IF yyt^.Set.card = 1 THEN
                          yyt^.Set.Tree := MakeTreeCh (nChar, VAL (Select (yyt^.Set.Set),CHAR));
                       ELSE
                          yyt^.Set.Tree := MakeTreeSet (nSet, yyt^.Set.Set);
                       END;
                    END;
                  
(* line 204 "../src/rex.cg" *)
 yyt^.Set.NodeCount := 1;
(* line 180 "../src/rex.cg" *)
 yyt^.Set.LeafCount := 1;
(* line 165 "../src/rex.cg" *)
 yyt^.Set.IsConstantRE := yyt^.Set.card = 1;
| Tree0.String=>
(* line 205 "../src/rex.cg" *)
 yyt^.String.NodeCount := StringMem.Length (yyt^.String.String);
(* line 181 "../src/rex.cg" *)
 yyt^.String.LeafCount := StringMem.Length (yyt^.String.String);
(* line 166 "../src/rex.cg" *)
 yyt^.String.IsConstantRE := TRUE;
(* line 138 "../src/rex.cg" *)

                       GetString (yyt^.String.String, String1);
                       AssignEmpty (String2);
                       FOR i := 1 TO Length (String1) DO
                          Append (String2, ToClass [Char (String1, i)]);
                       END;
                       yyt^.String.Tree := MakeTreeString (nString, PutString (String2));
                    
| Tree0.Rule=>
yyVisit1 (yyt^.Rule.Patterns);
(* line 206 "../src/rex.cg" *)
 yyt^.Rule.NodeCount := yyt^.Rule.Patterns^.Node.NodeCount;
(* line 182 "../src/rex.cg" *)
 yyt^.Rule.LeafCount := yyt^.Rule.Patterns^.Node.LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.Rule.IsConstantRE := TRUE;
(* line 146 "../src/rex.cg" *)
 yyt^.Rule.Tree := MakeTreeRule (nRule, yyt^.Rule.Patterns^.Node.Tree, yyt^.Rule.TargetCode, yyt^.Rule.Line,
                                yyt^.Rule.CodeMode, yyt^.Rule.RuleNr);
| Tree0.Pattern=>
yyVisit1 (yyt^.Pattern.RightContext);
yyVisit1 (yyt^.Pattern.RegExpr);
(* line 207 "../src/rex.cg" *)

                       IF yyt^.Pattern.RegExpr^.Node.IsConstantRE AND yyt^.Pattern.RightContext^.Node.IsConstantRE THEN
                          yyt^.Pattern.card := Card (yyt^.Pattern.StartStates);
                          yyt^.Pattern.NodeCount := (yyt^.Pattern.RegExpr^.Node.NodeCount + yyt^.Pattern.RightContext^.Node.NodeCount) * yyt^.Pattern.card;
                       ELSE
                          yyt^.Pattern.NodeCount := 0;
                       END;
                    
(* line 183 "../src/rex.cg" *)

                       IF NOT (yyt^.Pattern.RegExpr^.Node.IsConstantRE AND yyt^.Pattern.RightContext^.Node.IsConstantRE) THEN
                          yyt^.Pattern.LeafCount := yyt^.Pattern.RegExpr^.Node.LeafCount + yyt^.Pattern.RightContext^.Node.LeafCount;
                       ELSE
                          yyt^.Pattern.LeafCount := 0;
                       END;
                    
(* line 159 "../src/rex.cg" *)
 yyt^.Pattern.IsConstantRE := TRUE;
(* line 148 "../src/rex.cg" *)
 yyt^.Pattern.Tree := MakeTreePattern (nPattern, yyt^.Pattern.StartStates, yyt^.Pattern.RegExpr^.Node.Tree, yyt^.Pattern.RightContext^.Node.Tree,
                                yyt^.Pattern.RegExpr^.Node.IsConstantRE AND yyt^.Pattern.RightContext^.Node.IsConstantRE, yyt^.Pattern.PatternNr, yyt^.Pattern.Position);
  ELSE
  END;
 END yyVisit1;

PROCEDURE BeginEval() =
 BEGIN
(* line 83 "../src/rex.cg" *)
 MakeSet (Set1, ORD (LastCh)); 
 END BeginEval;

PROCEDURE CloseEval() =
 BEGIN
 END CloseEval;

BEGIN
END Eval.

