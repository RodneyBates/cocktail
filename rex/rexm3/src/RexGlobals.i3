INTERFACE RexGlobals 

; IMPORT Idents 

; VAR InputSuffix := "0"
      (* Input files rex expects to preexist and writes different versions of,
         have this suffix added to their names, to avoid danger of rex's
         overwriting of its needed input files.
      *)

; VAR ScannerDefaultNameT : TEXT := "NewScanner"
; VAR SourceDefaultNameT : TEXT := "NewSource"

; VAR DriverSuffix : TEXT := "Drv" 

; VAR RexLibDefault : TEXT := "../lib/" 
; VAR RexLib : TEXT := ""

; PROCEDURE IdentDefaultT ( Id : Idents . tIdent ; Default : TEXT ) : TEXT

; END RexGlobals
.


