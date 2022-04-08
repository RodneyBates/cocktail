
(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *) 

INTERFACE DynArray 

; FROM SYSTEM IMPORT M2LONGINT 


; PROCEDURE MakeArray 
    ( VAR ArrayPtr : ADDRESS 
    ; VAR ElmtCount : M2LONGINT 
    ; ElmtSize : M2LONGINT 
    ) 

; PROCEDURE ExtendArray 
    ( VAR ArrayPtr : ADDRESS 
    ; VAR ElmtCount : M2LONGINT 
    ; ElmtSize : M2LONGINT 
    ) 

; PROCEDURE ReleaseArray 
    ( ArrayPtr : ADDRESS ; ElmtCount : M2LONGINT ; ElmtSize : M2LONGINT ) 

; 
END DynArray 
. 

