(* $Id: rex.mi,v 3.9 1992/09/29 19:02:45 grosch rel $ *) 

(* $Log: rex.mi,v $ 
 * Revision 3.9  1992/09/29  19:02:45  grosch 
 * abort execution upon errors during scanning 
 * 
 * Revision 3.8  1992/09/29  14:38:55  grosch 
 * abort execution upon errors during scanning 
 * 
 * Revision 3.7  1992/08/07  15:10:26  grosch 
 * allow several scanner and parsers; extend module Errors 
 * 
 * Revision 3.6  1992/01/30  13:29:56  grosch 
 * redesign of interface to operating system 
 * 
 * Revision 3.5  1992/01/14  10:42:44  grosch 
 * fixed bug: multiply NodeCount by Card (StartStates) 
 * 
 * Revision 3.4  1992/01/07  11:05:57  grosch 
 * corrected spelling error 
 * 
 * Revision 3.3  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.2  91/09/18  15:05:36  grosch 
 * added option to control generation of # line directives 
 * 
 * Revision 3.1  91/04/08  15:50:20  grosch 
 * release memory after use in Classes and Tree0 
 * 
 * Revision 3.0  91/04/04  18:08:09  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 1.6  91/03/26  18:27:22  grosch 
 * improved generation time 
 * introduced options n and o to control table size and generation time 
 * increased limitation for table size from 64K to 256K 
 * 
 * Revision 1.5  91/02/13  11:35:15  grosch 
 * moved tables from file to initialization in C; reduced case size 
 * 
 * Revision 1.4  90/06/11  11:28:09  grosch 
 * extended character range to 8 bits, ChRange -> CHAR 
 * 
 * Revision 1.3  90/05/17  11:18:51  grosch 
 * cosmetic changes 
 * 
 * Revision 1.2  89/11/06  12:36:34  grosch 
 * renamed module Rex to GenTabs to avoid name clash with rex under VMS 
 * 
 * Revision 1.1  89/02/23  15:56:10  grosch 
 * added include files 
 * added help facility 
 * improved handling of command line arguments 
 * 
 * Revision 1.0  88/10/04  11:59:56  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE MODULE rexm3 EXPORTS Main

; IMPORT Text 

; FROM SYSTEM IMPORT SHORTCARD , SHORTINT 
; IMPORT ReuseIO 
; IMPORT Strings 

; FROM System IMPORT GetArgCount , GetArgument , Exit 

; FROM Strings 
  IMPORT tString , AssignEmpty , Assign , Append , Concatenate 
  , ArrayToString 
  , StringToArray , TextToString , StringToText 

; FROM ReuseIO IMPORT StdOutput , CloseIO 

; FROM StdIO IMPORT WriteNl 

; FROM Scanner IMPORT BeginScanner , BeginFile , ScanTabName 

; FROM Parser IMPORT ParsTabName , Parser 

; FROM RexErrors IMPORT ErrorCount 

; FROM Classes IMPORT ComputeClasses , ReleaseSetMem 

; FROM Eval IMPORT BeginEval , Eval 

; FROM Tree IMPORT WriteTree 

; FROM Tree0 IMPORT Tree0Root , WriteTree0 , ReleaseTree0Module 

; FROM Dfa IMPORT LastCh 

; FROM GenTabs 
  IMPORT StartStateCount , LeafCount , NodeCount , Root , GenerateTables 

; FROM ScanGen 
  IMPORT GenerateScanner , GenerateInterface , GenerateSupport , Language 
  , tLanguage 
  , SourceFile

; IMPORT RexGlobals 

; PROCEDURE WriteT ( t : TEXT ) 

  = BEGIN (* WriteT *) 
      ReuseIO . WriteT ( ReuseIO . StdOutput , t ) 
    END WriteT 

; TYPE AOC = ARRAY OF CHAR

; VAR Argument : ARRAY [ 0 .. 127 ] OF CHAR 
  ; FileNameS , Path : tString 
  ; optimize : SHORTINT 
  ; j , n : SHORTCARD 
  ; d , s , r , h , w , g , b : BOOLEAN 
  ; ch : CHAR 

; BEGIN (* rexm3 *) 
    d := FALSE 
  ; s := FALSE 
  ; r := FALSE 
  ; h := FALSE 
  ; w := TRUE 
  ; g := FALSE 
  ; b := TRUE 
  ; optimize := 40 
  ; n := 0 
  ; Language := tLanguage . Modula3 
  ; RexGlobals . RexLib := RexGlobals . RexLibDefault  
  ; SourceFile [ 0 ] := '\000' 

  ; FOR i := 1 TO GetArgCount ( ) - 1 
    DO GetArgument ( i , Argument ) 
    ; IF Argument [ 0 ] = '-' 
      THEN 
        IF Argument [ 1 ] = 'l' 
        THEN 
          RexGlobals . RexLib := "" 
        ; j := 2 
        ; LOOP 
            ch := Argument [ j ] 
          ; IF ch = '\000' THEN EXIT END (* IF *)
          ; RexGlobals . RexLib := RexGlobals . RexLib & Text . FromChar ( ch ) 
          ; INC ( j ) 
          END (* LOOP *) 
        ; IF NOT Text . Equal ( RexGlobals . RexLib , "" )
          THEN
            RexGlobals . RexLib := RexGlobals . RexLib & Text . FromChar ( '/' )
          END (* IF *) 
        ELSE 
          j := 0 
        ; LOOP 
            INC ( j ) 
          ; ch := Argument [ j ] 
          ; CASE ch 
            OF '\000' 
            => EXIT 
            | '?' 
            => h := TRUE 
            | 'h' 
            => h := TRUE 
            | 'c' 
            => Language := tLanguage . C 
            | 'm' 
            => Language := tLanguage . Modula2 
            | 'M' 
            => Language := tLanguage . Modula3 
            | 'z' 
            => Language := tLanguage . Schutz 
            | 'd' 
            => d := TRUE 
            | 's' 
            => s := TRUE 
            | 'r' 
            => r := TRUE 
            | 'a' 
            => d := TRUE 
            ; s := TRUE
            ; Language := tLanguage . Modula2 
            | 'i' 
            => LastCh := '\377' 
            | 'o' 
            => optimize := 16000 
            | 'n' 
            => optimize := 0 
            | 'w' 
            => w := FALSE 
            | 'g' 
            => g := TRUE 
            | 'b' 
            => b := FALSE 
            | '0' .. '9' 
            => n := ( n * 10 ) + ORD ( ch ) - ORD ( '0' ) 
            ELSE 
            END (* CASE *) 
          END (* LOOP *) 
        END (* IF *) 
      ELSIF Argument [ 0 ] = '?' 
      THEN 
        h := TRUE 
      ELSE 
        j := 0 
      ; REPEAT 
          ch := Argument [ j ] 
        ; SourceFile [ j ] := ch 
        ; INC ( j ) 
        UNTIL ch = '\000' 
      END (* IF *) 
    END (* FOR *) 

  ; IF h 
    THEN 

      WriteT ( "usage: rex [-options] [file]" ) 
    ; WriteNl ( ) 
    ; WriteNl ( ) 
    ; WriteT ( " a generate all (= -dsm)" ) 
    ; WriteNl ( ) 
    ; WriteT ( " m generate source code in Modula2" ) 
    ; WriteNl ( ) 
    ; WriteT ( " M generate source code in Modula3 (default)" ) 
    ; WriteNl ( ) 
    ; WriteT ( " z generate source code in Modula3, with Schutz interface." ) 
    ; WriteNl ( ) 
    ; WriteT ( " c generate a lexical analyzer in C" ) 
    ; WriteNl ( ) 
    ; WriteT ( " d generate a definition module for the lexical analyzer" ) 
    ; WriteNl ( ) 
    ; WriteT ( " s generate support modules:" ) 
    ; WriteNl ( ) 
    ; WriteT ( "   . a source module for input" ) 
    ; WriteNl ( ) 
    ; WriteT ( "   . a main program to be used as test driver" ) 
    ; WriteNl ( ) 
    ; WriteT ( " r reduce number of generated case/switch labels" ) 
    ; WriteNl ( ) 
    ; WriteT ( " i use ISO 8 bit code (default: ASCII 7 bit code)" ) 
    ; WriteNl ( ) 
    ; WriteT ( " o optimize table size" ) 
    ; WriteNl ( ) 
    ; WriteT ( " n do not optimize table size" ) 
    ; WriteNl ( ) 
    ; WriteT ( " w suppress warnings" ) 
    ; WriteNl ( ) 
    ; WriteT ( " g generate # line directives" ) 
    ; WriteNl ( ) 
    ; WriteT ( " b do not partition character set into blocks" ) 
    ; WriteNl ( ) 
    ; WriteT ( " 1 print statistics about the generated lexical analyzer" ) 
    ; WriteNl ( ) 
    ; WriteT ( " h print help information" ) 
    ; WriteNl ( ) 
    ; WriteT ( " l<dir> specify directory <dir> where rex finds its data files" )
    ; WriteNl ( ) 
    ; WriteT ( "        (default: \"../lib\"" )
    ; WriteNl ( ) 
    ; WriteT ( " <number> set debug level to <number>. " ) 
    ; WriteNl ( ) 

    ELSE
      ScanTabName := RexGlobals . RexLib & ScanTabName & RexGlobals . InputSuffix 
    ; ParsTabName := RexGlobals . RexLib & ParsTabName & RexGlobals . InputSuffix 

    ; BeginScanner ( ) 
    ; IF SourceFile [ 0 ] # '\000' THEN BeginFile ( SourceFile ) END (* IF *) 
    ; IF ( Parser ( ) = 0 ) AND ( ErrorCount = 0 ) 
      THEN 
        IF n >= 17 THEN WriteTree0 ( StdOutput , Tree0Root ) END (* IF *) 
      ; BeginEval ( ) 
      ; ComputeClasses ( b ) 
      ; Eval ( Tree0Root ) 
      ; IF n >= 16 THEN WriteTree0 ( StdOutput , Tree0Root ) END (* IF *) 
      ; LeafCount := StartStateCount + Tree0Root ^ . yyHead . LeafCount 
      ; NodeCount := Tree0Root ^ . yyHead . NodeCount 
      ; Root := Tree0Root ^ . yyHead . Tree 
      ; ReleaseSetMem ( ) 
      ; ReleaseTree0Module ( ) 
      ; IF n >= 15 THEN WriteTree ( Root ) END (* IF *) 
      ; GenerateTables ( n , r , w , optimize ) 
      ; GenerateScanner ( r , w , g ) 
      ELSE 
        CloseIO ( ) 
      ; Exit ( 1 ) 
      END (* IF *) 
    END (* IF *) 

  ; IF d THEN GenerateInterface ( ) END (* IF *) 
  ; IF s THEN GenerateSupport ( ) END (* IF *) 
  ; CloseIO ( ) 
  ; Exit ( 0 ) 
  END rexm3 
. 

