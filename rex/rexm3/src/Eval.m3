
UNSAFE MODULE Eval 

; IMPORT Word , Tree0 
(* line 61 "../src/rex.cg" *) 

; FROM Strings IMPORT tString , AssignEmpty , Length , Append , Char 

; FROM StringMem IMPORT GetString , PutString

; IMPORT IntSets 

; IMPORT Sets 
(*
; FROM Sets 
  IMPORT tSet , MakeSet , Card , Assign , Intersection , Select , Minimum 
  , IsEmpty 
  , Maximum , IsElement , Include 
*)
; FROM Classes IMPORT ToClass , IsInSetMem , SetMemPtr
; IMPORT Classes 

; IMPORT Dfa  
; IMPORT StringMem 

; FROM Tree 
  IMPORT NoTree , MakeTree1 , MakeTree2 , MakeTreeRule , MakeTreePattern 
  , MakeTreeCh 
  , MakeTreeSet , MakeTreeString , nList , nRule , nPattern , nAlternative 
  , nSequence 
  , nRepetition , nOption , nChar , nSet , nString 

; VAR String1 , String2 : tString 
  ; Set1 , Set2 : Sets . tSet 
  ; j : Word . T 


; PROCEDURE Eval ( yyt : Tree0 . tTree0 ) 

  = BEGIN (* Eval *) 
      yyVisit1 ( yyt ) 
    END Eval 

; PROCEDURE yyVisit1 ( yyt : Tree0 . tTree0 ) 

  = VAR LCharSet : Sets . tSet
  
  ; BEGIN (* yyVisit1 *) 
      CASE yyt ^ . Kind 
      OF Tree0 . Node 
      => 
(* line 200 "../src/rex.cg" *) 
         yyt ^ . yyHead . NodeCount := 0 
(* line 176 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount := 0 
(* line 159 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 90 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree := NoTree 
      | Tree0 . Node1 
      => yyVisit1 ( yyt ^ . yyHead . Son1 ) 
(* line 201 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . NodeCount 
(* line 177 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . LeafCount 
(* line 159 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 90 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree := NoTree 
      | Tree0 . Option 
      => yyVisit1 ( yyt ^ . yyHead . Son1 ) 
(* line 201 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . NodeCount 
(* line 177 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . LeafCount 
(* line 160 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := FALSE 
(* line 91 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTree1 ( nOption , yyt ^ . yyHead . Son1 ^ . yyHead . Tree ) 
      | Tree0 . Repetition 
      => yyVisit1 ( yyt ^ . yyHead . Son1 ) 
(* line 201 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . NodeCount 
(* line 177 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . LeafCount 
(* line 161 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := FALSE 
(* line 92 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTree1 
               ( nRepetition , yyt ^ . yyHead . Son1 ^ . yyHead . Tree ) 
      | Tree0 . Node2 
      => yyVisit1 ( yyt ^ . yyHead . Son2 ) 
      ; yyVisit1 ( yyt ^ . yyHead . Son1 ) 
(* line 202 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . NodeCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . NodeCount 
(* line 178 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . LeafCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . LeafCount 
(* line 159 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 90 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree := NoTree 
      | Tree0 . List 
      => yyVisit1 ( yyt ^ . yyHead . Son2 ) 
      ; yyVisit1 ( yyt ^ . yyHead . Son1 ) 
(* line 202 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . NodeCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . NodeCount 
(* line 178 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . LeafCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . LeafCount 
(* line 159 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 93 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTree2 
               ( nList 
               , yyt ^ . yyHead . Son1 ^ . yyHead . Tree 
               , yyt ^ . yyHead . Son2 ^ . yyHead . Tree 
               ) 
      | Tree0 . Sequence 
      => yyVisit1 ( yyt ^ . yyHead . Son2 ) 
      ; yyVisit1 ( yyt ^ . yyHead . Son1 ) 
(* line 202 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . NodeCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . NodeCount 
(* line 178 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . LeafCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . LeafCount 
(* line 162 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE 
          := yyt ^ . yyHead . Son1 ^ . yyHead . IsConstantRE 
             AND yyt ^ . yyHead . Son2 ^ . yyHead . IsConstantRE 
(* line 94 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTree2 
               ( nSequence 
               , yyt ^ . yyHead . Son1 ^ . yyHead . Tree 
               , yyt ^ . yyHead . Son2 ^ . yyHead . Tree 
               ) 
      | Tree0 . Alternative 
      => yyVisit1 ( yyt ^ . yyHead . Son2 ) 
      ; yyVisit1 ( yyt ^ . yyHead . Son1 ) 
(* line 202 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . NodeCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . NodeCount 
(* line 178 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . yyHead . Son1 ^ . yyHead . LeafCount 
             + yyt ^ . yyHead . Son2 ^ . yyHead . LeafCount 
(* line 163 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := FALSE 
(* line 95 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTree2 
               ( nAlternative 
               , yyt ^ . yyHead . Son1 ^ . yyHead . Tree 
               , yyt ^ . yyHead . Son2 ^ . yyHead . Tree 
               ) 
      | Tree0 . Ch 
      => 
(* line 203 "../src/rex.cg" *) 
         yyt ^ . yyHead . NodeCount := 1 
(* line 179 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount := 1 
(* line 164 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 96 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTreeCh ( nChar , ToClass [ yyt ^ . Ch . Ch ] ) 
      | Tree0 . Set 
      => 
(* line 97 "../src/rex.cg" *) 

         j := IsInSetMem ( yyt ^ . Set . Set ) 
      ; IF j # 0 
        THEN 
          yyt ^ . Set . card := IntSets . Card ( SetMemPtr ^ [ j ] . Classes ) 
        ; Sets . Assign ( Set1 , yyt ^ . Set . Set )
        ; Sets . MakeSet ( LCharSet , ORD ( Dfa . LastCh ) ) 
        ; Sets . FromIntSet ( LCharSet , Classes . CharSet ) 
        ; Sets . Intersection ( Set1 , LCharSet )
        ; Sets . ReleaseSet ( LCharSet ) 
        ; INC ( yyt ^ . Set . card , Sets . Card ( Set1 ) ) 
        ; IF yyt ^ . Set . card = 1 
          THEN 
            IF IntSets . Card ( SetMemPtr ^ [ j ] . Classes ) = 1 
            THEN 
              yyt ^ . yyHead . Tree 
                := MakeTreeCh 
                     ( nChar 
                     , VAL ( IntSets . ArbitraryMember ( SetMemPtr ^ [ j ]
                             . Classes )
                           , CHAR
                           ) 
                     ) 
            ELSE 
              yyt ^ . yyHead . Tree 
                := MakeTreeCh 
                     ( nChar , ToClass [ VAL ( Sets . Select ( Set1 ) , CHAR ) ] ) 
            END (* IF *) 
          ELSE 
            Sets . MakeSet ( Set2 , ORD ( Dfa . LastCh ) ) 
          ; IF NOT Sets . IsEmpty ( Set1 ) 
            THEN 
              FOR i := Sets . Minimum ( Set1 ) TO Sets . Maximum ( Set1 ) 
              DO IF Sets . IsElement ( i , Set1 ) 
                 THEN 
                   Sets . Include
                     ( Set2 , ORD ( ToClass [ VAL ( i , CHAR ) ] ) ) 
                 END (* IF *) 
              END (* FOR *) 
            END (* IF *) 

          ; IF NOT IntSets . IsEmpty ( SetMemPtr ^ [ j ] . Classes ) 
            THEN 
              FOR i := IntSets . Minimum ( SetMemPtr ^ [ j ] . Classes ) 
                    TO IntSets . Maximum ( SetMemPtr ^ [ j ] . Classes ) 
              DO IF IntSets . IsElement ( i , SetMemPtr ^ [ j ] . Classes ) 
                 THEN 
                   Sets . Include ( Set2 , i ) 
                 END (* IF *) 
              END (* FOR *) 
            END (* IF *) 
          ; yyt ^ . yyHead . Tree := MakeTreeSet ( nSet , Set2 ) 
          END (* IF *) 
        ELSE 
          yyt ^ . Set . card := Sets . Card ( yyt ^ . Set . Set ) 
        ; IF yyt ^ . Set . card = 1 
          THEN 
            yyt ^ . yyHead . Tree 
              := MakeTreeCh 
                   ( nChar , VAL ( Sets . Select ( yyt ^ . Set . Set ) , CHAR ) ) 
          ELSE 
            yyt ^ . yyHead . Tree := MakeTreeSet ( nSet , yyt ^ . Set . Set ) 
          END (* IF *) 
        END (* IF *) 

(* line 204 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount := 1 
(* line 180 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount := 1 
(* line 165 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := yyt ^ . Set . card = 1 
      | Tree0 . String 
      => 
(* line 205 "../src/rex.cg" *) 
         yyt ^ . yyHead . NodeCount 
           := StringMem . Length ( yyt ^ . String . String ) 
(* line 181 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := StringMem . Length ( yyt ^ . String . String ) 
(* line 166 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 138 "../src/rex.cg" *) 

      ; GetString ( yyt ^ . String . String , String1 ) 
      ; AssignEmpty ( String2 ) 
      ; FOR i := 1 TO Length ( String1 ) 
        DO Append ( String2 , ToClass [ Char ( String1 , i ) ] ) 
        END (* FOR *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTreeString ( nString , PutString ( String2 ) ) 

      | Tree0 . Rule 
      => yyVisit1 ( yyt ^ . Rule . Patterns ) 
(* line 206 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . NodeCount 
          := yyt ^ . Rule . Patterns ^ . yyHead . NodeCount 
(* line 182 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . LeafCount 
          := yyt ^ . Rule . Patterns ^ . yyHead . LeafCount 
(* line 159 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 146 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTreeRule 
               ( nRule 
               , yyt ^ . Rule . Patterns ^ . yyHead . Tree 
               , yyt ^ . Rule . TargetCode 
               , yyt ^ . Rule . Line 
               , yyt ^ . Rule . CodeMode 
               , yyt ^ . Rule . RuleNr 
               ) 
      | Tree0 . Pattern 
      => yyVisit1 ( yyt ^ . Pattern . RightContext ) 
      ; yyVisit1 ( yyt ^ . Pattern . RegExpr ) 
(* line 207 "../src/rex.cg" *) 

      ; IF yyt ^ . Pattern . RegExpr ^ . yyHead . IsConstantRE 
           AND yyt ^ . Pattern . RightContext ^ . yyHead . IsConstantRE 
        THEN
          yyt ^ . Pattern . card
            := Sets . Card ( yyt ^ . Pattern . StartStates )
        ; yyt ^ . yyHead . NodeCount 
            := ( yyt ^ . Pattern . RegExpr ^ . yyHead . NodeCount 
                 + yyt ^ . Pattern . RightContext ^ . yyHead . NodeCount 
               ) 
               * yyt ^ . Pattern . card 
        ELSE 
          yyt ^ . yyHead . NodeCount := 0 
        END (* IF *) 

(* line 183 "../src/rex.cg" *) 

      ; IF NOT ( yyt ^ . Pattern . RegExpr ^ . yyHead . IsConstantRE 
                 AND yyt ^ . Pattern . RightContext ^ . yyHead . IsConstantRE 
               ) 
        THEN 
          yyt ^ . yyHead . LeafCount 
            := yyt ^ . Pattern . RegExpr ^ . yyHead . LeafCount 
               + yyt ^ . Pattern . RightContext ^ . yyHead . LeafCount 
        ELSE 
          yyt ^ . yyHead . LeafCount := 0 
        END (* IF *) 

(* line 159 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . IsConstantRE := TRUE 
(* line 148 "../src/rex.cg" *) 
      ; yyt ^ . yyHead . Tree 
          := MakeTreePattern 
               ( nPattern 
               , yyt ^ . Pattern . StartStates 
               , yyt ^ . Pattern . RegExpr ^ . yyHead . Tree 
               , yyt ^ . Pattern . RightContext ^ . yyHead . Tree 
               , yyt ^ . Pattern . RegExpr ^ . yyHead . IsConstantRE 
                 AND yyt ^ . Pattern . RightContext ^ . yyHead . IsConstantRE 
               , yyt ^ . Pattern . PatternNr 
               , yyt ^ . Pattern . Position 
               ) 
      ELSE 
      END (* CASE *) 
    END yyVisit1

; PROCEDURE BeginEval ( ) 

  = BEGIN (* BeginEval *) 
(* line 83 "../src/rex.cg" *) 
      Sets . MakeSet ( Set1 , ORD ( Dfa . LastCh ) ) 
    END BeginEval 

; PROCEDURE CloseEval ( ) 

  = BEGIN (* CloseEval *) 
    END CloseEval 

; BEGIN (* Eval *) 
  END Eval 
. 

