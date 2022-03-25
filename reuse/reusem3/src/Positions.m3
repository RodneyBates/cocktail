(* $Id: Positions.mi,v 1.1 1992/08/13 13:47:25 grosch rel $ *) 

(* $Log: Positions.mi,v $ 
# RMB 93/01/12 Type conversions. 
 
# Revision 1.1  1992/08/13  13:47:25  grosch 
# increase format in WritePosition 
# 
# Revision 1.0  1992/08/07  14:42:00  grosch 
# Initial revision 
# 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Juli 1992 *) 

UNSAFE MODULE Positions 

; FROM ReuseIO IMPORT tFile , WriteC , WriteI 

; PROCEDURE Compare ( Position1 , Position2 : tPosition ) : INTEGER 

  = BEGIN (* Compare *) 
      WITH With_23 = Position1 
      DO IF With_23 . Line < Position2 . Line THEN RETURN - 1 END (* IF *) 
      ; IF With_23 . Line > Position2 . Line THEN RETURN 1 END (* IF *) 
      ; IF With_23 . Column < Position2 . Column THEN RETURN - 1 END (* IF *) 
      ; IF With_23 . Column > Position2 . Column THEN RETURN 1 END (* IF *) 
      ; RETURN 0 
      END (* WITH *) 
    END Compare 

; PROCEDURE WritePosition ( File : tFile ; Position : tPosition ) 

  = BEGIN (* WritePosition *) 
      WriteI ( File , VAL ( Position . Line , INTEGER ) , 4 ) 
    ; WriteC ( File , ',' ) 
    ; WriteI ( File , VAL ( Position . Column , INTEGER ) , 3 ) 
    END WritePosition 

; BEGIN (* Positions *) 
    NoPosition . Line := 0 
  ; NoPosition . Column := 0 
  END Positions 
. 

