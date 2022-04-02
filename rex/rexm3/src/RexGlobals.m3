MODULE RexGlobals

; IMPORT Idents 

; PROCEDURE IdentDefaultT ( Id : Idents . tIdent ; Default : TEXT ) : TEXT

  = BEGIN
      IF Id = Idents . NoIdent
      THEN RETURN Default
      ELSE RETURN Idents . Text ( Id )
      END (* IF *) 
    END IdentDefaultT 

; BEGIN
  END RexGlobals
.


