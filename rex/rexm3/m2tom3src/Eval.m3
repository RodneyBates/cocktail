

 UNSAFE MODULE Eval;

IMPORT Word, SYSTEM, Tree0;
(* line 61 "../src/rex.cg" *)

FROM Strings	IMPORT tString, AssignEmpty, Length, Append, Char;
FROM StringMem	IMPORT GetString, PutString;
FROM Sets	IMPORT tSet, MakeSet, Card, Assign, Intersection, Select, Minimum,
			IsEmpty, Union, Maximum, IsElement, Include;
FROM Classes	IMPORT ToClass, IsInSetMem, SetMemPtr, CharSet;
FROM Dfa	IMPORT LastCh;
IMPORT StringMem;

FROM Tree	IMPORT
   tTree	, NoTree	, MakeTree1	, MakeTree2	,
   MakeTreeRule	, MakeTreePattern, MakeTreeCh	, MakeTreeSet	,
   MakeTreeString, nList	, nRule		, nPattern	,
   nAlternative	, nSequence	, nRepetition	, nOption	,
   nChar	, nSet		, nString	;

VAR
   String1, String2	: tString;
   Set1, Set2		: tSet;
   i, j			: Word.T;


VAR yyb	: BOOLEAN;

PROCEDURE Eval (yyt: Tree0.tTree0) =
 BEGIN yyVisit1 (yyt); END Eval;

PROCEDURE yyVisit1 (yyt: Tree0.tTree0) =
 BEGIN
  CASE yyt^.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 36
 $$ *) OF
| Tree0.Node=>
(* line 200 "../src/rex.cg" *)
 yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 39
 $$ *).NodeCount := 0;
(* line 176 "../src/rex.cg" *)
 yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 41
 $$ *).LeafCount := 0;
(* line 159 "../src/rex.cg" *)
 yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 43
 $$ *).IsConstantRE := TRUE;
(* line 90 "../src/rex.cg" *)
 yyt^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 45
 $$ *).Tree := NoTree;
| Tree0.Node1=>
yyVisit1 (yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 47
 $$ *).Son1);
(* line 201 "../src/rex.cg" *)
 yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 49
 $$ *).NodeCount := yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 49
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 49
 $$ *).NodeCount;
(* line 177 "../src/rex.cg" *)
 yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 51
 $$ *).LeafCount := yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 51
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 51
 $$ *).LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 53
 $$ *).IsConstantRE := TRUE;
(* line 90 "../src/rex.cg" *)
 yyt^.Node1(* $$ m2tom3 warning: application of variant field, possible cast of 'Node1' in line 55
 $$ *).Tree := NoTree;
| Tree0.Option=>
yyVisit1 (yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 57
 $$ *).Son1);
(* line 201 "../src/rex.cg" *)
 yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 59
 $$ *).NodeCount := yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 59
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 59
 $$ *).NodeCount;
(* line 177 "../src/rex.cg" *)
 yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 61
 $$ *).LeafCount := yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 61
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 61
 $$ *).LeafCount;
(* line 160 "../src/rex.cg" *)
 yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 63
 $$ *).IsConstantRE := FALSE;
(* line 91 "../src/rex.cg" *)
 yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 65
 $$ *).Tree := MakeTree1 (nOption, yyt^.Option(* $$ m2tom3 warning: application of variant field, possible cast of 'Option' in line 65
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 65
 $$ *).Tree);
| Tree0.Repetition=>
yyVisit1 (yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 67
 $$ *).Son1);
(* line 201 "../src/rex.cg" *)
 yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 69
 $$ *).NodeCount := yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 69
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 69
 $$ *).NodeCount;
(* line 177 "../src/rex.cg" *)
 yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 71
 $$ *).LeafCount := yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 71
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 71
 $$ *).LeafCount;
(* line 161 "../src/rex.cg" *)
 yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 73
 $$ *).IsConstantRE := FALSE;
(* line 92 "../src/rex.cg" *)
 yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 75
 $$ *).Tree := MakeTree1 (nRepetition, yyt^.Repetition(* $$ m2tom3 warning: application of variant field, possible cast of 'Repetition' in line 75
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 75
 $$ *).Tree);
| Tree0.Node2=>
yyVisit1 (yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 77
 $$ *).Son2);
yyVisit1 (yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 78
 $$ *).Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 80
 $$ *).NodeCount := yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 80
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 80
 $$ *).NodeCount + yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 80
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 80
 $$ *).NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 82
 $$ *).LeafCount := yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 82
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 82
 $$ *).LeafCount + yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 82
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 82
 $$ *).LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 84
 $$ *).IsConstantRE := TRUE;
(* line 90 "../src/rex.cg" *)
 yyt^.Node2(* $$ m2tom3 warning: application of variant field, possible cast of 'Node2' in line 86
 $$ *).Tree := NoTree;
| Tree0.List=>
yyVisit1 (yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 88
 $$ *).Son2);
yyVisit1 (yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 89
 $$ *).Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 91
 $$ *).NodeCount := yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 91
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 91
 $$ *).NodeCount + yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 91
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 91
 $$ *).NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 93
 $$ *).LeafCount := yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 93
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 93
 $$ *).LeafCount + yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 93
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 93
 $$ *).LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 95
 $$ *).IsConstantRE := TRUE;
(* line 93 "../src/rex.cg" *)
 yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 97
 $$ *).Tree := MakeTree2 (nList, yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 97
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 97
 $$ *).Tree, yyt^.List(* $$ m2tom3 warning: application of variant field, possible cast of 'List' in line 97
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 97
 $$ *).Tree);
| Tree0.Sequence=>
yyVisit1 (yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 99
 $$ *).Son2);
yyVisit1 (yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 100
 $$ *).Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 102
 $$ *).NodeCount := yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 102
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 102
 $$ *).NodeCount + yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 102
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 102
 $$ *).NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 104
 $$ *).LeafCount := yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 104
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 104
 $$ *).LeafCount + yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 104
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 104
 $$ *).LeafCount;
(* line 162 "../src/rex.cg" *)
 yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 106
 $$ *).IsConstantRE := yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 106
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 106
 $$ *).IsConstantRE AND yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 106
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 106
 $$ *).IsConstantRE;
(* line 94 "../src/rex.cg" *)
 yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 108
 $$ *).Tree := MakeTree2 (nSequence, yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 108
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 108
 $$ *).Tree, yyt^.Sequence(* $$ m2tom3 warning: application of variant field, possible cast of 'Sequence' in line 108
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 108
 $$ *).Tree);
| Tree0.Alternative=>
yyVisit1 (yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 110
 $$ *).Son2);
yyVisit1 (yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 111
 $$ *).Son1);
(* line 202 "../src/rex.cg" *)
 yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 113
 $$ *).NodeCount := yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 113
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 113
 $$ *).NodeCount + yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 113
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 113
 $$ *).NodeCount;
(* line 178 "../src/rex.cg" *)
 yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 115
 $$ *).LeafCount := yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 115
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 115
 $$ *).LeafCount + yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 115
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 115
 $$ *).LeafCount;
(* line 163 "../src/rex.cg" *)
 yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 117
 $$ *).IsConstantRE := FALSE;
(* line 95 "../src/rex.cg" *)
 yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 119
 $$ *).Tree := MakeTree2 (nAlternative, yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 119
 $$ *).Son1^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 119
 $$ *).Tree, yyt^.Alternative(* $$ m2tom3 warning: application of variant field, possible cast of 'Alternative' in line 119
 $$ *).Son2^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 119
 $$ *).Tree);
| Tree0.Ch=>
(* line 203 "../src/rex.cg" *)
 yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 122
 $$ *).NodeCount := 1;
(* line 179 "../src/rex.cg" *)
 yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 124
 $$ *).LeafCount := 1;
(* line 164 "../src/rex.cg" *)
 yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 126
 $$ *).IsConstantRE := TRUE;
(* line 96 "../src/rex.cg" *)
 yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 128
 $$ *).Tree := MakeTreeCh (nChar, ToClass [yyt^.Ch(* $$ m2tom3 warning: application of variant field, possible cast of 'Ch' in line 128
 $$ *).Ch]);
| Tree0.Set=>
(* line 97 "../src/rex.cg" *)

		    j := IsInSetMem (yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 132
 $$ *).Set);
		    IF j # 0 THEN
		       yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 134
 $$ *).card := Card (SetMemPtr^[j].Classes);
		       Assign (Set1, yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 135
 $$ *).Set);
		       Intersection (Set1, CharSet);
		       INC (yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 137
 $$ *).card, Card (Set1));
		       IF yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 138
 $$ *).card = 1 THEN
			  IF Card (SetMemPtr^[j].Classes) = 1 THEN
			     yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 140
 $$ *).Tree := MakeTreeCh (nChar, VAL (Select (SetMemPtr^[j].Classes),CHAR));
			  ELSE
			     yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 142
 $$ *).Tree := MakeTreeCh (nChar, ToClass [VAL (Select (Set1),CHAR)]);
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
			  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 161
 $$ *).Tree := MakeTreeSet (nSet, Set2);
		       END;
		    ELSE
		       yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 164
 $$ *).card := Card (yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 164
 $$ *).Set);
		       IF yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 165
 $$ *).card = 1 THEN
			  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 166
 $$ *).Tree := MakeTreeCh (nChar, VAL (Select (yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 166
 $$ *).Set),CHAR));
		       ELSE
			  yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 168
 $$ *).Tree := MakeTreeSet (nSet, yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 168
 $$ *).Set);
		       END;
		    END;
		  
(* line 204 "../src/rex.cg" *)
 yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 173
 $$ *).NodeCount := 1;
(* line 180 "../src/rex.cg" *)
 yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 175
 $$ *).LeafCount := 1;
(* line 165 "../src/rex.cg" *)
 yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 177
 $$ *).IsConstantRE := yyt^.Set(* $$ m2tom3 warning: application of variant field, possible cast of 'Set' in line 177
 $$ *).card = 1;
| Tree0.String=>
(* line 205 "../src/rex.cg" *)
 yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 180
 $$ *).NodeCount := StringMem.Length (yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 180
 $$ *).String);
(* line 181 "../src/rex.cg" *)
 yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 182
 $$ *).LeafCount := StringMem.Length (yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 182
 $$ *).String);
(* line 166 "../src/rex.cg" *)
 yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 184
 $$ *).IsConstantRE := TRUE;
(* line 138 "../src/rex.cg" *)

		       GetString (yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 187
 $$ *).String, String1);
		       AssignEmpty (String2);
		       FOR i := 1 TO Length (String1) DO
			  Append (String2, ToClass [Char (String1, i)]);
		       END;
		       yyt^.String(* $$ m2tom3 warning: application of variant field, possible cast of 'String' in line 192
 $$ *).Tree := MakeTreeString (nString, PutString (String2));
		    
| Tree0.Rule=>
yyVisit1 (yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 195
 $$ *).Patterns);
(* line 206 "../src/rex.cg" *)
 yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 197
 $$ *).NodeCount := yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 197
 $$ *).Patterns^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 197
 $$ *).NodeCount;
(* line 182 "../src/rex.cg" *)
 yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 199
 $$ *).LeafCount := yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 199
 $$ *).Patterns^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 199
 $$ *).LeafCount;
(* line 159 "../src/rex.cg" *)
 yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 201
 $$ *).IsConstantRE := TRUE;
(* line 146 "../src/rex.cg" *)
 yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 203
 $$ *).Tree := MakeTreeRule (nRule, yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 203
 $$ *).Patterns^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 203
 $$ *).Tree, yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 203
 $$ *).TargetCode, yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 203
 $$ *).Line,
				yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 204
 $$ *).CodeMode, yyt^.Rule(* $$ m2tom3 warning: application of variant field, possible cast of 'Rule' in line 204
 $$ *).RuleNr);
| Tree0.Pattern=>
yyVisit1 (yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 206
 $$ *).RightContext);
yyVisit1 (yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 207
 $$ *).RegExpr);
(* line 207 "../src/rex.cg" *)

		       IF yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 210
 $$ *).RegExpr^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 210
 $$ *).IsConstantRE AND yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 210
 $$ *).RightContext^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 210
 $$ *).IsConstantRE THEN
			  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 211
 $$ *).card := Card (yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 211
 $$ *).StartStates);
			  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 212
 $$ *).NodeCount := (yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 212
 $$ *).RegExpr^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 212
 $$ *).NodeCount + yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 212
 $$ *).RightContext^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 212
 $$ *).NodeCount) * yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 212
 $$ *).card;
		       ELSE
			  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 214
 $$ *).NodeCount := 0;
		       END;
		    
(* line 183 "../src/rex.cg" *)

		       IF NOT (yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 219
 $$ *).RegExpr^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 219
 $$ *).IsConstantRE AND yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 219
 $$ *).RightContext^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 219
 $$ *).IsConstantRE) THEN
			  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 220
 $$ *).LeafCount := yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 220
 $$ *).RegExpr^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 220
 $$ *).LeafCount + yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 220
 $$ *).RightContext^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 220
 $$ *).LeafCount;
		       ELSE
			  yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 222
 $$ *).LeafCount := 0;
		       END;
		    
(* line 159 "../src/rex.cg" *)
 yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 226
 $$ *).IsConstantRE := TRUE;
(* line 148 "../src/rex.cg" *)
 yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 228
 $$ *).Tree := MakeTreePattern (nPattern, yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 228
 $$ *).StartStates, yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 228
 $$ *).RegExpr^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 228
 $$ *).Tree, yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 228
 $$ *).RightContext^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 228
 $$ *).Tree,
				yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 229
 $$ *).RegExpr^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 229
 $$ *).IsConstantRE AND yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 229
 $$ *).RightContext^.Node(* $$ m2tom3 warning: application of variant field, possible cast of 'Node' in line 229
 $$ *).IsConstantRE, yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 229
 $$ *).PatternNr, yyt^.Pattern(* $$ m2tom3 warning: application of variant field, possible cast of 'Pattern' in line 229
 $$ *).Position);
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

