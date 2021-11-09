
(* Module IOUtils.  Utility procedures for IO. 
   Written to get backslashes out of .puma files.  puma sends its output
   through cpp.  The cpp on Linux treats '\' and "...\" as unclosed
   literals with disasterous consequences.  cpp's and Modula-2's rules
   are irreconciliable. 
   Rodney M. Bates Sept 97
*) 

DEFINITION MODULE IOUtils 

; IMPORT IO 

; PROCEDURE WriteBackslash ( f : IO . tFile ) 

; END IOUtils 
. 

