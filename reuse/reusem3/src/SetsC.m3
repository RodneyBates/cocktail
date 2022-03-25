(* $Id: SetsC.mi,v 1.3 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: SetsC.mi,v $ 
 
 * RMB 97/06/05 Added InitNullSet, since some tree dumps call 
                WriteSet for sets which are not in use and need 
                no allocated array. 
 
Revision 1.3  1991/11/21  14:33:17  grosch 
new version of RCS on SPARC 
 
Revision 1.2  90/05/31  09:45:30  grosch 
turned Name parameter of Check procedures into value parameter for SUN m2c 
 
Revision 1.1  89/02/23  16:02:37  grosch 
Initial revision 
 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Feb. 1989 *) 

UNSAFE MODULE SetsC 

; IMPORT Word , Sets 

; FROM ReuseIO IMPORT tFile , StdError , WriteI , WriteN , WriteT , WriteNl 

; PROCEDURE CheckSetSet ( VAR Set1 , Set2 : tSet ; READONLY Name : TEXT ) 

  = BEGIN (* CheckSetSet *) 
      CheckSet ( Set1 , Name ) 
    ; CheckSet ( Set2 , Name ) 
    ; IF Set1 . MaxElmt # Set2 . MaxElmt 
      THEN 
        WriteT ( StdError , "Sets." ) 
      ; WriteT ( StdError , Name ) 
      ; WriteT ( StdError , ": incompatible sets" ) 
      ; WriteNl ( StdError ) 
      ; PrintSet ( Set1 ) 
      ; PrintSet ( Set2 ) 
      END (* IF *) 
    END CheckSetSet 

; PROCEDURE CheckSetElmt 
    ( VAR Set : tSet ; Elmt : INTEGER ; READONLY Name : TEXT ) 

  = BEGIN (* CheckSetElmt *) 
      CheckSet ( Set , Name ) 
    ; IF Elmt < 0 
      THEN 
        WriteT ( StdError , "Sets." ) 
      ; WriteT ( StdError , Name ) 
      ; WriteT ( StdError , ": negative element: " ) 
      ; WriteI ( StdError , Elmt , 0 ) 
      ; WriteNl ( StdError ) 
      ; PrintSet ( Set ) 
      END (* IF *) 
    ; IF Elmt > VAL ( Set . MaxElmt , INTEGER ) 
      THEN 
        WriteT ( StdError , "Sets." ) 
      ; WriteT ( StdError , Name ) 
      ; WriteT ( StdError , ": element out of range: " ) 
      ; WriteI ( StdError , Elmt , 0 ) 
      ; WriteNl ( StdError ) 
      ; PrintSet ( Set ) 
      END (* IF *) 
    END CheckSetElmt 

; PROCEDURE CheckSet ( VAR Set : tSet ; READONLY Name : TEXT ) 

  = BEGIN (* CheckSet *) 
      IF Set . BitsetPtr = NIL 
      THEN 
        WriteT ( StdError , "Sets." ) 
      ; WriteT ( StdError , Name ) 
      ; WriteT ( StdError , ": set probably not initialized" ) 
      ; WriteNl ( StdError ) 
      ; PrintSet ( Set ) 
      END (* IF *) 
    END CheckSet 

; PROCEDURE CheckNotEmpty ( VAR Set : tSet ; READONLY Name : TEXT ) 

  = BEGIN (* CheckNotEmpty *) 
      CheckSet ( Set , Name ) 
    ; IF Sets . IsEmpty ( Set ) 
      THEN 
        WriteT ( StdError , "Sets." ) 
      ; WriteT ( StdError , Name ) 
      ; WriteT ( StdError , ": applied to empty set" ) 
      ; WriteNl ( StdError ) 
      ; PrintSet ( Set ) 
      END (* IF *) 
    END CheckNotEmpty 

; PROCEDURE PrintSet ( Set : tSet ) 

  = BEGIN (* PrintSet *) 
      WITH With_25 = Set 
      DO WriteT ( StdError , "BitsetPtr = " ) 
      ; WriteN 
          ( StdError , LOOPHOLE ( With_25 . BitsetPtr , INTEGER ) , 0 , 16 ) 
      ; WriteNl ( StdError ) 
      ; WriteT ( StdError , "MaxElmt   = " ) 
      ; WriteI ( StdError , VAL ( With_25 . MaxElmt , INTEGER ) , 0 ) 
      ; WriteNl ( StdError ) 
      ; WriteT ( StdError , "LastBitset= " ) 
      ; WriteI ( StdError , VAL ( With_25 . LastBitset , INTEGER ) , 0 ) 
      ; WriteNl ( StdError ) 
      ; WriteT ( StdError , "Card      = " ) 
      ; WriteI ( StdError , VAL ( With_25 . Card , INTEGER ) , 0 ) 
      ; WriteNl ( StdError ) 
      ; WriteT ( StdError , "FirstElmt = " ) 
      ; WriteI ( StdError , VAL ( With_25 . FirstElmt , INTEGER ) , 0 ) 
      ; WriteNl ( StdError ) 
      ; WriteT ( StdError , "LastElmt  = " ) 
      ; WriteI ( StdError , VAL ( With_25 . LastElmt , INTEGER ) , 0 ) 
      ; WriteNl ( StdError ) 
      END (* WITH *) 
    END PrintSet 

; PROCEDURE InitNullSet ( VAR Set : tSet ) 

  = BEGIN (* InitNullSet *) 
      Sets . InitNullSet ( Set ) 
    END InitNullSet 

; PROCEDURE MakeSet ( VAR Set : tSet ; MaxSize : Word . T ) 

  = BEGIN (* MakeSet *) 
      Sets . MakeSet ( Set , MaxSize ) 
    ; CheckSet ( Set , "MakeSet" ) 
    END MakeSet 

; PROCEDURE ReleaseSet ( VAR Set : tSet ) 

  = BEGIN (* ReleaseSet *) 
      CheckSet ( Set , "ReleaseSet" ) 
    ; Sets . ReleaseSet ( Set ) 
    END ReleaseSet 

; PROCEDURE Union ( VAR Set1 : tSet ; Set2 : tSet ) 

  = BEGIN (* Union *) 
      CheckSetSet ( Set1 , Set2 , "Union" ) 
    ; Sets . Union ( Set1 , Set2 ) 
    END Union 

; PROCEDURE Difference ( VAR Set1 : tSet ; Set2 : tSet ) 

  = BEGIN (* Difference *) 
      CheckSetSet ( Set1 , Set2 , "Difference" ) 
    ; Sets . Difference ( Set1 , Set2 ) 
    END Difference 

; PROCEDURE Intersection ( VAR Set1 : tSet ; Set2 : tSet ) 

  = BEGIN (* Intersection *) 
      CheckSetSet ( Set1 , Set2 , "Intersection" ) 
    ; Sets . Intersection ( Set1 , Set2 ) 
    END Intersection 

; PROCEDURE SymDiff ( VAR Set1 : tSet ; Set2 : tSet ) 

  = BEGIN (* SymDiff *) 
      CheckSetSet ( Set1 , Set2 , "SymDiff" ) 
    ; Sets . SymDiff ( Set1 , Set2 ) 
    END SymDiff 

; PROCEDURE Complement ( VAR Set : tSet ) 

  = BEGIN (* Complement *) 
      CheckSet ( Set , "Complement" ) 
    ; Sets . Complement ( Set ) 
    END Complement 

; PROCEDURE Include ( VAR Set : tSet ; Elmt : Word . T ) 

  = BEGIN (* Include *) 
      CheckSetElmt ( Set , Elmt , "Include" ) 
    ; Sets . Include ( Set , Elmt ) 
    END Include 

; PROCEDURE Exclude ( VAR Set : tSet ; Elmt : Word . T ) 

  = BEGIN (* Exclude *) 
      CheckSetElmt ( Set , Elmt , "Exclude" ) 
    ; Sets . Exclude ( Set , Elmt ) 
    END Exclude 

; PROCEDURE Card ( VAR Set : tSet ) : Word . T 

  = BEGIN (* Card *) 
      CheckSet ( Set , "Card" ) 
    ; RETURN Sets . Card ( Set ) 
    END Card 

; PROCEDURE Size ( VAR Set : tSet ) : Word . T 

  = BEGIN (* Size *) 
      CheckSet ( Set , "Size" ) 
    ; RETURN Sets . Size ( Set ) 
    END Size 

; PROCEDURE Minimum ( VAR Set : tSet ) : Word . T 

  = BEGIN (* Minimum *) 
      CheckNotEmpty ( Set , "Minimum" ) 
    ; RETURN Sets . Minimum ( Set ) 
    END Minimum 

; PROCEDURE Maximum ( VAR Set : tSet ) : Word . T 

  = BEGIN (* Maximum *) 
      CheckNotEmpty ( Set , "Maximum" ) 
    ; RETURN Sets . Maximum ( Set ) 
    END Maximum 

; PROCEDURE Select ( VAR Set : tSet ) : Word . T 

  = BEGIN (* Select *) 
      CheckNotEmpty ( Set , "Select" ) 
    ; RETURN Sets . Select ( Set ) 
    END Select 

; PROCEDURE Extract ( VAR Set : tSet ) : Word . T 

  = BEGIN (* Extract *) 
      CheckNotEmpty ( Set , "Extract" ) 
    ; RETURN Sets . Extract ( Set ) 
    END Extract 

; PROCEDURE IsSubset ( Set1 , Set2 : tSet ) : BOOLEAN 

  = BEGIN (* IsSubset *) 
      CheckSetSet ( Set1 , Set2 , "IsSubset" ) 
    ; RETURN Sets . IsSubset ( Set1 , Set2 ) 
    END IsSubset 

; PROCEDURE IsStrictSubset ( Set1 , Set2 : tSet ) : BOOLEAN 

  = BEGIN (* IsStrictSubset *) 
      CheckSetSet ( Set1 , Set2 , "IsStrictSubset" ) 
    ; RETURN Sets . IsStrictSubset ( Set1 , Set2 ) 
    END IsStrictSubset 

; PROCEDURE IsEqual ( VAR Set1 , Set2 : tSet ) : BOOLEAN 

  = BEGIN (* IsEqual *) 
      CheckSetSet ( Set1 , Set2 , "IsEqual" ) 
    ; RETURN Sets . IsEqual ( Set1 , Set2 ) 
    END IsEqual 

; PROCEDURE IsNotEqual ( Set1 , Set2 : tSet ) : BOOLEAN 

  = BEGIN (* IsNotEqual *) 
      CheckSetSet ( Set1 , Set2 , "IsNotEqual" ) 
    ; RETURN Sets . IsNotEqual ( Set1 , Set2 ) 
    END IsNotEqual 

; PROCEDURE IsElement ( Elmt : Word . T ; VAR Set : tSet ) : BOOLEAN 

  = BEGIN (* IsElement *) 
      CheckSetElmt ( Set , Elmt , "IsElement" ) 
    ; RETURN Sets . IsElement ( Elmt , Set ) 
    END IsElement 

; PROCEDURE IsEmpty ( Set : tSet ) : BOOLEAN 

  = BEGIN (* IsEmpty *) 
      CheckSet ( Set , "IsEmpty" ) 
    ; RETURN Sets . IsEmpty ( Set ) 
    END IsEmpty 

; PROCEDURE Forall ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

  = BEGIN (* Forall *) 
      CheckSet ( Set , "Forall" ) 
    ; RETURN Sets . Forall ( Set , Proc ) 
    END Forall 

; PROCEDURE Exists ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

  = BEGIN (* Exists *) 
      CheckSet ( Set , "Exists" ) 
    ; RETURN Sets . Exists ( Set , Proc ) 
    END Exists 

; PROCEDURE Exists1 ( Set : tSet ; Proc : ProcOftElementToBool ) : BOOLEAN 

  = BEGIN (* Exists1 *) 
      CheckSet ( Set , "Exists1" ) 
    ; RETURN Sets . Exists1 ( Set , Proc ) 
    END Exists1 

; PROCEDURE Assign ( VAR Set1 : tSet ; Set2 : tSet ) 

  = BEGIN (* Assign *) 
      CheckSetSet ( Set1 , Set2 , "Assign" ) 
    ; Sets . Assign ( Set1 , Set2 ) 
    END Assign 

; PROCEDURE AssignElmt ( VAR Set : tSet ; Elmt : Word . T ) 

  = BEGIN (* AssignElmt *) 
      CheckSetElmt ( Set , Elmt , "AssignElmt" ) 
    ; Sets . AssignElmt ( Set , Elmt ) 
    END AssignElmt 

; PROCEDURE AssignEmpty ( VAR Set : tSet ) 

  = BEGIN (* AssignEmpty *) 
      CheckSet ( Set , "AssignEmpty" ) 
    ; Sets . AssignEmpty ( Set ) 
    END AssignEmpty 

; PROCEDURE ForallDo ( Set : tSet ; Proc : ProcOftElement ) 

  = BEGIN (* ForallDo *) 
      CheckSet ( Set , "ForallDo" ) 
    ; Sets . ForallDo ( Set , Proc ) 
    END ForallDo 

; PROCEDURE ReadSet ( f : tFile ; VAR Set : tSet ) 

  = BEGIN (* ReadSet *) 
      CheckSet ( Set , "ReadSet" ) 
    ; Sets . ReadSet ( f , Set ) 
    END ReadSet 

; PROCEDURE WriteSet ( f : tFile ; Set : tSet ) 

  = BEGIN (* WriteSet *) 
      CheckSet ( Set , "WriteSet" ) 
    ; Sets . WriteSet ( f , Set ) 
    END WriteSet 

; BEGIN (* SetsC *) 
  END SetsC 
. 

