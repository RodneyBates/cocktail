(* generate output procedure for tokens *)

(* Rodney M. Bates, modifications: 
    3-2023 Add generation of Module-3 code. 
    Further changes in https://github.com/RodneyBates/cocktail
*) 

(* $Id: WriteTok.md,v 1.3 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: WriteTok.md,v $
 * Revision 1.3  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/11  18:45:51  grosch
 * layout improvements
 * 
 * Revision 1.1  89/01/12  17:45:26  vielsack
 * supply source file name
 * 
 * Revision 1.0  88/10/04  14:27:28  vielsack
 * Initial revision
 * 
 *)

INTERFACE  WriteTok;

  FROM ReuseIO IMPORT tFile;

  TYPE tLanguage = { Modula3, Modula2, C };
  
  VAR SourceFileName := "defaultSourceFile";
  
  VAR Language  : tLanguage;
  
  PROCEDURE GenTokNameAlts (f : tFile);

END WriteTok.

