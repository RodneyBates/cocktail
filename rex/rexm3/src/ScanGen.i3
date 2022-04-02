(* $Id: ScanGen.md,v 3.3 1992/08/07 15:10:26 grosch rel $ *) 

(* $Log: ScanGen.md,v $ 
 * Revision 3.3  1992/08/07  15:10:26  grosch 
 * allow several scanner and parsers; extend module Errors 
 * 
 * Revision 3.2  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.1  91/09/18  15:05:27  grosch 
 * added option to control generation of # line directives 
 * 
 * Revision 3.0  91/04/04  18:07:36  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 1.3  91/02/13  11:34:45  grosch 
 * moved tables from file to initialization in C; reduced case size 
 * 
 * Revision 1.2  89/02/23  15:55:40  grosch 
 * added DEFAULT section 
 * 
 * Revision 1.1  89/01/17  15:01:20  grosch 
 * correction and redesign of source position handling 
 * 
 * Revision 1.0  88/10/04  11:59:42  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE INTERFACE ScanGen 

; FROM SYSTEM IMPORT SHORTCARD 

; FROM Texts IMPORT tText 

; FROM Strings IMPORT tString 

; FROM Idents IMPORT tIdent 

; CONST Position = 0 
  ; NoPosition = 1 

; TYPE tLanguage = { C , Modula2 , Modula3 , Schutz }
       (* Schutz is in Modula3, but uses Schutz' interface. *) 

; VAR Export , Global , Local , Begin , Close , Default , Eof , BlankText 
    , TabText 
    , EolText 
    : tText 
  ; ExportLine , GlobalLine , LocalLine , BeginLine , CloseLine , DefaultLine 
    , EofLine 
    : SHORTCARD 
  ; ScannerIdent : tIdent 
  ; Language : tLanguage 
  ; SourceFile : ARRAY [ 0 .. 127 ] OF CHAR 

; PROCEDURE InitScanGen ( ) 

; PROCEDURE GenerateScanner ( ReduceCaseSize , Warnings , GenLine : BOOLEAN ) 

; PROCEDURE GenerateInterface ( ) 

; PROCEDURE GenerateSupport ( ) 

; 
END ScanGen 
. 

