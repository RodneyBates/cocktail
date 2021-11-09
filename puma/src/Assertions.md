
DEFINITION MODULE Assertions

; FROM Positions IMPORT tPosition 

; PROCEDURE Assert 
    ( Condition : BOOLEAN ; Msg : ARRAY OF CHAR )

; PROCEDURE CantHappen ( Msg : ARRAY OF CHAR )

; PROCEDURE AssertPos 
    ( Condition : BOOLEAN ; Msg : ARRAY OF CHAR ; Position : tPosition )

; PROCEDURE CantHappenPos ( Msg : ARRAY OF CHAR ; Position : tPosition )

;
END Assertions
.
