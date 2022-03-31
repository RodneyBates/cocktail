(* $Id: ScanGen.mi,v 3.9 1992/08/18 09:06:44 grosch rel $ *) 

(* $Log: ScanGen.mi,v $ 
 * Revision 3.9  1992/08/18  09:06:44  grosch 
 * removed limitation for length of token and lookahead 
 * 
 * Revision 3.8  1992/08/07  15:10:26  grosch 
 * allow several scanner and parsers; extend module Errors 
 * 
 * Revision 3.7  1992/02/11  16:43:56  grosch 
 * replaced tString = unsigned char * by char * 
 * 
 * Revision 3.6  1992/01/30  15:29:14  grosch 
 * added labels to suppress warnings for unreachable statements 
 * 
 * Revision 3.5  1992/01/30  13:29:56  grosch 
 * redesign of interface to operating system 
 * 
 * Revision 3.4  1991/11/21  14:42:49  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.3  91/09/18  15:05:38  grosch 
 * added option to control generation of # line directives 
 * 
 * Revision 3.2  91/04/26  16:16:02  grosch 
 * introduced ARGS trick for ANSI C compatibility 
 * 
 * Revision 3.1  91/04/08  15:51:16  grosch 
 * corrected LastCh to OldLastCh 
 * 
 * Revision 3.0  91/04/04  18:07:40  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 2.0  91/03/08  18:18:10  grosch 
 * turned tables into initialized arrays (in C) 
 * reduced case size 
 * changed interface for source position 
 * 
 * Revision 1.11  91/02/13  11:35:17  grosch 
 * moved tables from file to initialization in C; reduced case size 
 * 
 * Revision 1.10  90/10/09  17:33:54  grosch 
 * output one case label per line, only 
 * 
 * Revision 1.9  90/09/20  10:12:20  grosch 
 * calmed down lint 
 * 
 * Revision 1.8  90/06/11  11:25:44  grosch 
 * minimal layout improvements 
 * 
 * Revision 1.7  89/11/06  12:36:26  grosch 
 * renamed module Rex to GenTabs to avoid name clash with rex under VMS 
 * 
 * Revision 1.6  89/08/29  11:44:47  grosch 
 * make all char constants unsigned 
 * 
 * Revision 1.5  89/03/01  10:59:43  grosch 
 * improve default action 
 * 
 * Revision 1.4  89/02/23  15:55:43  grosch 
 * added include files 
 * added DEFAULT section 
 * added completeness check for the automaton 
 * improved handling of right context 
 * 
 * Revision 1.3  89/01/17  15:01:50  grosch 
 * correction and redesign of source position handling 
 * 
 * Revision 1.2  88/11/22  19:19:25  grosch 
 * fixed bug: changed variables Context2 and Context4 for variable right context in Modula2 
 * 
 * Revision 1.1  88/11/06  14:55:00  grosch 
 * terminate case labels with superfluous ; to avoid yacc stack overflow with SUN's cc 
 * 
 * Revision 1.0  88/10/04  11:59:44  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE MODULE ScanGen 



; FROM SYSTEM IMPORT SHORTCARD 

; FROM Checks IMPORT ErrorCheckS 

; FROM ReuseIO 
  IMPORT ReadOpen , WriteOpen , WriteClose , ReadClose , EndOfFile , WriteN 
  , WriteT 
  , WriteNl , WriteC , WriteI , WriteS , tFile 

; FROM Texts IMPORT tText , MakeText , WriteText 

; FROM Sets IMPORT IsEmpty , Card , Select , Extract , tSet 

; FROM Strings 
  IMPORT tString , Char , ReadL , WriteL , Length , TextToString 
  , StringToArray 
  , Assign , Append , Concatenate 

; FROM Idents IMPORT tIdent , NoIdent , WriteIdent 

; FROM RexErrors IMPORT ErrorMessage 

; FROM DefTable IMPORT GetKind , DefCount , tKind , GetStartDef 

; FROM Dfa IMPORT FirstCh , EolCh , EobCh , DStateCount , OldLastCh 

; FROM ScanTabs 
  IMPORT TableSize , PutComb , PutBase , PutDefault , PutEobTrans , PutAction 

; FROM GenTabs 
  IMPORT RuleToCodePtr , PatternTablePtr , EobAction , DefaultAction 
  , PatternCount 
  , VariableContext , LeftJustUsed 

; IMPORT Word , Texts , Strings , Idents 

(* File names for Modula2:*) 
; CONST ScannerMd = "Scanner.md" 
  ; ScannerMi = "Scanner.mi" 
  ; SourceMd = "Source.md" 
  ; SourceMi = "Source.mi" 
  ; ScanDrvMi = "ScanDrv.mi" 

(* File names for Modula3: *)
; CONST ScannerM3 = "Scanner.m3"  
  ; ScannerI3 = "Scanner.i3" 
  ; SourceM3 = "Source.m3" 
  ; SourceI3 = "Source.i3" 
  ; ScanDrvM3 = "ScanDrv.m3" 

(* File names for C:*) 
; CONST ScannerH = "Scanner.h" 
  ; ScannerC = "Scanner.c" 
  ; SourceH = "Source.h" 
  ; SourceC = "Source.c" 
  ; ScanDrvC = "ScanDrv.c" 

(* File name fragments: *)
  ; Scanner = "Scanner" 
  ; Source = "Source" 
  ; Drv = "Drv" 
  ; ExtMd = ".md" 
  ; ExtMi = ".mi" 
  ; ExtM3 = ".m3" 
  ; ExtI3 = ".i3" 
  ; ExtH = ".h" 
  ; ExtC = ".c" 

  ; PatternNoMatch = 15 
  ; Warning = 4 

; VAR Case1 , Case2 , Context1 , Context2 , Context3 , Context4 , Leader 
    , Trailer 
    : tText 
  ; LabelCount , DummyCount : Word . T 
  ; gGenLine : BOOLEAN 

; PROCEDURE ExpandLine ( Out : tFile ; READONLY Line : tString ) 

  = VAR Ch : CHAR 
    ; i : Word . T 

  ; BEGIN (* ExpandLine *) 
      i := 3 
    ; LOOP 
        INC ( i ) 
      ; IF i > Length ( Line ) THEN WriteNl ( Out ) ; EXIT END (* IF *) 
      ; Ch := Char ( Line , i ) 
      ; CASE Ch 
        OF '@' 
        => IF ScannerName = NoIdent 
           THEN 
             WriteT ( Out , Scanner ) 
           ELSE 
             WriteIdent ( Out , ScannerName ) 
           END (* IF *) 
        | '$' 
        => IF ScannerName = NoIdent 
           THEN 
             IF Char ( Line , i + 1 ) = '_' THEN INC ( i ) END (* IF *) 
           ELSE 
             WriteIdent ( Out , ScannerName ) 
           END (* IF *) 
        ELSE 
          WriteC ( Out , Ch ) 
        END (* CASE *) 
      END (* LOOP *) 
    END ExpandLine 

; PROCEDURE GenerateSupport ( ) 

  = VAR SourceName , DriverName , Suffix : tString 

  ; PROCEDURE CopyFile 
      ( InputA : TEXT ; READONLY OutputS : tString ; SuffixA : TEXT ) 

    = VAR In , Out : tFile 
      ; FileNameS , PathS , Line : tString 
      ; LOutputS : tString 
      ; PathA : ARRAY [ 0 .. 127 ] OF CHAR 

    ; BEGIN (* CopyFile *) 
        TextToString ( InputA , FileNameS ) 
      ; Assign ( PathS , RexLib ) 
      ; Concatenate ( PathS , FileNameS ) 
      ; Append ( PathS , '\000' ) 
      ; StringToArray ( PathS , PathA ) 
      ; In := ReadOpen ( PathA ) 
      ; ErrorCheckS ( PathA , In ) 

      ; Assign ( LOutputS , OutputS ) 
      ; TextToString ( SuffixA , FileNameS ) 
      ; Concatenate ( LOutputS , FileNameS ) 
      ; Append ( LOutputS , '\000' ) 
      ; StringToArray ( LOutputS , PathA ) 
      ; Out := WriteOpen ( PathA ) 
      ; ErrorCheckS ( PathA , Out ) 

      ; WHILE NOT EndOfFile ( In ) 
        DO ReadL ( In , Line ) 
        ; IF ( Length ( Line ) >= 2 ) 
             AND ( Char ( Line , 1 ) = '$' ) 
             AND ( Char ( Line , 2 ) = '@' ) 
          THEN 
            ExpandLine ( Out , Line ) 
          ELSE 
            WriteL ( Out , Line ) 
          END (* IF *) 
        END (* WHILE *) 
      ; ReadClose ( In ) 
      ; WriteClose ( Out ) 
      END CopyFile 

  ; BEGIN (* GenerateSupport *) 
      Idents . GetString ( ScannerName , SourceName ) 
    ; TextToString ( Source , Suffix ) 
    ; Concatenate ( SourceName , Suffix ) 
    ; IF ScannerName = NoIdent 
      THEN 
        TextToString ( Scanner , DriverName ) 
      ELSE 
        Idents . GetString ( ScannerName , DriverName ) 
      END (* IF *) 
    ; TextToString ( Drv , Suffix ) 
    ; Concatenate ( DriverName , Suffix ) 
    ; CASE Language 
      OF tLanguage . Modula2 
      => CopyFile ( SourceMd , SourceName , ExtMd ) 
      ; CopyFile ( SourceMi , SourceName , ExtMi ) 
      ; CopyFile ( ScanDrvMi , DriverName , ExtMi ) 

      | tLanguage . Modula3 
      => CopyFile ( SourceM3 , SourceName , ExtM3 ) 
      ; CopyFile ( SourceI3 , SourceName , ExtI3 ) 
      ; CopyFile ( ScanDrvM3 , DriverName , ExtM3 ) 

      | tLanguage . Schutz 
      => 

      | tLanguage . C 
      => CopyFile ( SourceH , SourceName , ExtH ) 
      ; CopyFile ( SourceC , SourceName , ExtC ) 
      ; CopyFile ( ScanDrvC , DriverName , ExtC ) 
      END (* CASE *) 
    END GenerateSupport 

; PROCEDURE GenerateInterface ( ) 

  = VAR In , Out : tFile 
    ; FileNameS , PathS , Line : tString 
    ; PathA : ARRAY [ 0 .. 127 ] OF CHAR 

  ; BEGIN (* GenerateInterface *) 
      CASE Language 
      OF tLanguage . Modula2 
      => TextToString ( ScannerMd , FileNameS ) 
      | tLanguage . C 
      => TextToString ( ScannerH , FileNameS ) 
      END (* CASE *) 

    ; Assign ( PathS , RexLib ) 
    ; Concatenate ( PathS , FileNameS ) 
    ; Append ( PathS , '\000' ) 
    ; StringToArray ( PathS , PathA ) 
    ; In := ReadOpen ( PathA ) 
    ; ErrorCheckS ( PathA , In ) 

    ; IF ScannerName = NoIdent 
      THEN 
        TextToString ( Scanner , PathS ) 
      ELSE 
        Idents . GetString ( ScannerName , PathS ) 
      END (* IF *) 
    ; CASE Language 
      OF tLanguage . Modula2 
      => TextToString ( ExtMd , FileNameS ) 
      | tLanguage . C 
      => TextToString ( ExtH , FileNameS ) 
      END (* CASE *) 
    ; Concatenate ( PathS , FileNameS ) 
    ; Append ( PathS , '\000' ) 
    ; StringToArray ( PathS , PathA ) 
    ; Out := WriteOpen ( PathA ) 
    ; ErrorCheckS ( PathA , Out ) 

    ; WHILE NOT EndOfFile ( In ) 
      DO ReadL ( In , Line ) 
      ; IF ( Length ( Line ) >= 2 ) AND ( Char ( Line , 1 ) = '$' ) 
        THEN 
          CASE Char ( Line , 2 ) 
          OF 'E' 
          => WriteLine ( Out , ExportLine ) 
          ; WriteText ( Out , Export ) 
          | '@' 
          => ExpandLine ( Out , Line ) 
          END (* CASE *) 
        ELSE 
          WriteL ( Out , Line ) 
        END (* IF *) 
      END (* WHILE *) 
    ; ReadClose ( In ) 
    ; WriteClose ( Out ) 
    END GenerateInterface 

; PROCEDURE GenerateScanner ( ReduceCaseSize , Warnings , GenLine : BOOLEAN ) 

  = VAR In , Out : tFile 
    ; FileNameS , PathS , Line : tString 
    ; PathA : ARRAY [ 0 .. 127 ] OF CHAR 

  ; BEGIN (* GenerateScanner *) 
      gGenLine := GenLine 
    ; CASE Language 
      OF tLanguage . Modula2 
      => TextToString ( ScannerMi , FileNameS ) 
      | tLanguage . C 
      => TextToString ( ScannerC , FileNameS ) 
      END (* CASE *) 

    ; Assign ( PathS , RexLib ) 
    ; Concatenate ( PathS , FileNameS ) 
    ; Append ( PathS , '\000' ) 
    ; StringToArray ( PathS , PathA ) 
    ; In := ReadOpen ( PathA ) 
    ; ErrorCheckS ( PathA , In ) 

    ; IF ScannerName = NoIdent 
      THEN 
        TextToString ( Scanner , PathS ) 
      ELSE 
        Idents . GetString ( ScannerName , PathS ) 
      END (* IF *) 
    ; CASE Language 
      OF tLanguage . Modula2 
      => TextToString ( ExtMi , FileNameS ) 
      | tLanguage . C 
      => TextToString ( ExtC , FileNameS ) 
      END (* CASE *) 
    ; Concatenate ( PathS , FileNameS ) 
    ; Append ( PathS , '\000' ) 
    ; StringToArray ( PathS , PathA ) 
    ; Out := WriteOpen ( PathA ) 
    ; ErrorCheckS ( PathA , Out ) 

    ; WHILE NOT EndOfFile ( In ) 
      DO ReadL ( In , Line ) 
      ; IF ( Length ( Line ) >= 2 ) AND ( Char ( Line , 1 ) = '$' ) 
        THEN 
          CASE Char ( Line , 2 ) 
          OF 'G' 
          => WriteLine ( Out , GlobalLine ) 
          ; WriteText ( Out , Global ) 
          | 'C' 
          => GenerateConstants ( Out ) 
          | 'M' 
          => IF ReduceCaseSize 
             THEN 
               Line . Chars [ 1 ] := ' ' 
             ; Line . Chars [ 2 ] := ' ' 
             ; WriteL ( Out , Line ) 
             END (* IF *) 
          | 'L' 
          => WriteLine ( Out , LocalLine ) 
          ; WriteText ( Out , Local ) 
          | 'J' 
          => IF LeftJustUsed 
             THEN 
               Line . Chars [ 1 ] := ' ' 
             ; Line . Chars [ 2 ] := ' ' 
             ; WriteL ( Out , Line ) 
             END (* IF *) 
          | 'A' 
          => GenerateActions ( Out , ReduceCaseSize , Warnings ) 
          | 'N' 
          => IF ReduceCaseSize 
             THEN 
               GenerateCaseLabel ( Out , PatternCount + 1 ) 
             ELSE 
               GenerateCaseLabels ( Out , PatternTablePtr ^ [ 0 ] . Finals ) 
             END (* IF *) 
          | 'P' 
          => IF ReduceCaseSize 
             THEN 
               GenerateCaseLabel ( Out , DefaultAction ) 
             ELSE 
               GenerateCaseLabel 
                 ( Out 
                 , Select ( PatternTablePtr ^ [ DefaultAction ] . Finals ) 
                 ) 
             END (* IF *) 
          | 'D' 
          => WriteLine ( Out , DefaultLine ) 
          ; WriteText ( Out , Default ) 
          | 'O' 
          => IF ReduceCaseSize 
             THEN 
               GenerateCaseLabel ( Out , EobAction ) 
             ELSE 
               GenerateCaseLabel 
                 ( Out , Select ( PatternTablePtr ^ [ EobAction ] . Finals ) ) 
             END (* IF *) 
          | 'E' 
          => WriteLine ( Out , EofLine ) 
          ; WriteText ( Out , Eof ) 
          | 'I' 
          => WriteLine ( Out , BeginLine ) 
          ; WriteText ( Out , Begin ) 
          | 'F' 
          => WriteLine ( Out , CloseLine ) 
          ; WriteText ( Out , Close ) 
          | 'T' 
          => PutComb ( Out ) 
          | 'B' 
          => PutBase ( Out ) 
          | 'U' 
          => PutDefault ( Out ) 
          | 'R' 
          => PutEobTrans ( Out ) 
          | 'Q' 
          => IF ReduceCaseSize THEN PutAction ( Out ) END (* IF *) 
          | '@' 
          => ExpandLine ( Out , Line ) 
          END (* CASE *) 
        ELSE 
          WriteL ( Out , Line ) 
        END (* IF *) 
      END (* WHILE *) 
    ; ReadClose ( In ) 
    ; WriteClose ( Out ) 
    END GenerateScanner 

; PROCEDURE GenerateConstants ( Out : tFile ) 

  = VAR String : tString 
    ; Ident : tIdent 
    ; Number : SHORTCARD 

  ; BEGIN (* GenerateConstants *) 
      TextToString ( "yyFirstCh" , String ) 
    ; GenerateCharConstDef ( Out , String , FirstCh ) 
    ; TextToString ( "yyLastCh" , String ) 
    ; GenerateCharConstDef ( Out , String , OldLastCh ) 
    ; TextToString ( "yyEolCh" , String ) 
    ; GenerateCharConstDef ( Out , String , EolCh ) 
    ; TextToString ( "yyEobCh" , String ) 
    ; GenerateCharConstDef ( Out , String , EobCh ) 
    ; TextToString ( "yyDStateCount" , String ) 
    ; GenerateDecConstDef ( Out , String , DStateCount ) 
    ; TextToString ( "yyTableSize" , String ) 
    ; GenerateDecConstDef ( Out , String , TableSize ) 
    ; TextToString ( "yyEobState" , String ) 
    ; GenerateDecConstDef 
        ( Out , String , Select ( PatternTablePtr ^ [ EobAction ] . Finals ) ) 
    ; TextToString ( "yyDefaultState" , String ) 
    ; GenerateDecConstDef 
        ( Out 
        , String 
        , Select ( PatternTablePtr ^ [ DefaultAction ] . Finals ) 
        ) 

    ; FOR Definition := 1 TO DefCount 
      DO IF GetKind ( Definition ) = tKind . Start 
         THEN 
           GetStartDef ( Definition , Ident , Number ) 
         ; Idents . GetString ( Ident , String ) 
         ; GenerateDecConstDef ( Out , String , Number ) 
         END (* IF *) 
      END (* FOR *) 
    END GenerateConstants 

; PROCEDURE GenerateActions 
    ( Out : tFile ; ReduceCaseSize , Warnings : BOOLEAN ) 

  = VAR Rule : INTEGER 
    ; String , String2 : tString 
    ; Label : Word . T 

  ; BEGIN (* GenerateActions *) 
      IF ReduceCaseSize 
      THEN 
        WriteText ( Out , Case2 ) 
      ELSE 
        WriteText ( Out , Case1 ) 
      END (* IF *) 
    ; FOR Pattern := 1 TO PatternCount - 2 
      DO                                        (* omit special rules *) 
         IF NOT IsEmpty ( PatternTablePtr ^ [ Pattern ] . Finals ) 
         THEN 
           IF ReduceCaseSize 
           THEN 
             GenerateCaseLabel ( Out , Pattern ) 
           ELSE 
             GenerateCaseLabels 
               ( Out , PatternTablePtr ^ [ Pattern ] . Finals ) 
           END (* IF *) 
         ; IF PatternTablePtr ^ [ Pattern ] . ContextLng = VariableContext 
           THEN 
             IF Card ( PatternTablePtr ^ [ Pattern ] . DContext ) = 1 
             THEN 
               WriteText ( Out , Context1 ) 
             ; WriteI 
                 ( Out 
                 , Select ( PatternTablePtr ^ [ Pattern ] . DContext ) 
                 , 0 
                 ) 
             ; WriteText ( Out , Context2 ) 
             ELSE 
               WriteText ( Out , Context3 ) 
             ; GenerateCaseLabels 
                 ( Out , PatternTablePtr ^ [ Pattern ] . DContext ) 
             ; IF Language = tLanguage . C 
               THEN 
                 Label := MakeLabel ( ) 
               ; GenerateGoto ( Out , Label ) 
               END (* IF *) 
             ; WriteText ( Out , Context4 ) 
             ; IF Language = tLanguage . C 
               THEN 
                 GenerateLabel ( Out , Label ) 
               END (* IF *) 
             END (* IF *) 
           ELSIF PatternTablePtr ^ [ Pattern ] . ContextLng > 0 
           THEN 
             TextToString ( "yyChBufferIndex" , String ) 
           ; GenerateDecrement 
               ( Out , String , PatternTablePtr ^ [ Pattern ] . ContextLng ) 
           ; IF Language = tLanguage . C 
             THEN 
               IF ScannerName = NoIdent 
               THEN 
                 TextToString ( "TokenLength" , String ) 
               ELSE 
                 Idents . GetString ( ScannerName , String ) 
               ; Append ( String , '_' ) 
               ; TextToString ( "TokenLength" , String2 ) 
               ; Concatenate ( String , String2 ) 
               END (* IF *) 
             ELSE 
               TextToString ( "TokenLength" , String ) 
             END (* IF *) 
           ; GenerateDecrement 
               ( Out , String , PatternTablePtr ^ [ Pattern ] . ContextLng ) 
           ELSIF PatternTablePtr ^ [ Pattern ] . ContextLng < 0 
           THEN 
             WriteT ( Out , "yyLess (" ) 
           ; WriteI ( Out , - PatternTablePtr ^ [ Pattern ] . ContextLng , 0 ) 
           ; WriteT ( Out , ");" ) 
           ; WriteNl ( Out ) 
           END (* IF *) 
         ; Rule := PatternTablePtr ^ [ Pattern ] . Rule 
         ; IF RuleToCodePtr ^ [ Rule ] . CodeMode = Position 
           THEN 
             WriteText ( Out , Leader ) 
           END (* IF *) 
         ; WriteLine ( Out , RuleToCodePtr ^ [ Rule ] . TextLine ) 
         ; IF Language = tLanguage . C THEN WriteC ( Out , '{' ) END (* IF *) 
         ; WriteText ( Out , RuleToCodePtr ^ [ Rule ] . Text ) 
         ; IF Language = tLanguage . C 
           THEN 
             INC ( DummyCount ) 
           ; WriteT ( Out , "} yy" ) 
           ; WriteI ( Out , DummyCount , 0 ) 
           ; WriteT ( Out , ": " ) 
           END (* IF *) 
         ; WriteText ( Out , Trailer ) 
         ELSIF ( PatternTablePtr ^ [ Pattern ] . Position . Line # 0 ) 
               AND Warnings 
         THEN 
           ErrorMessage 
             ( PatternNoMatch 
             , Warning 
             , PatternTablePtr ^ [ Pattern ] . Position 
             ) 
         END (* IF *) 
      END (* FOR *) 
    END GenerateActions 

; PROCEDURE GenerateDecConstDef 
    ( Out : tFile ; READONLY Name : tString ; Value : INTEGER ) 

  = BEGIN (* GenerateDecConstDef *) 
      CASE Language 
      OF tLanguage . Modula2 
      => Strings . WriteS ( Out , Name ) 
      ; WriteT ( Out , " = " ) 
      ; WriteI ( Out , Value , 0 ) 
      ; WriteC ( Out , ';' ) 
      ; WriteNl ( Out ) 
      | tLanguage . C 
      => WriteT ( Out , "# define " ) 
      ; Strings . WriteS ( Out , Name ) 
      ; WriteC ( Out , ' ' ) 
      ; WriteI ( Out , Value , 0 ) 
      ; WriteNl ( Out ) 
      END (* CASE *) 
    END GenerateDecConstDef 

; PROCEDURE GenerateCharConstDef 
    ( Out : tFile ; READONLY Name : tString ; Value : CHAR ) 

  = BEGIN (* GenerateCharConstDef *) 
      CASE Language 
      OF tLanguage . Modula2 
      => Strings . WriteS ( Out , Name ) 
      ; WriteT ( Out , " = " ) 
      ; WriteN ( Out , ORD ( Value ) , 1 , 8 ) 
      ; WriteT ( Out , "C;" ) 
      ; WriteNl ( Out ) 
      | tLanguage . C 
      => WriteT ( Out , "# define " ) 
      ; Strings . WriteS ( Out , Name ) 
      ; WriteT ( Out , " (unsigned char) " ) 
      ; WriteN ( Out , ORD ( Value ) , 1 , 8 ) 
      ; WriteC ( Out , '\'' ) 
      ; WriteNl ( Out ) 
      END (* CASE *) 
    END GenerateCharConstDef 

; PROCEDURE GenerateDecrement 
    ( Out : tFile ; READONLY Name : tString ; Value : INTEGER ) 

  = BEGIN (* GenerateDecrement *) 
      CASE Language 
      OF tLanguage . Modula2 
      => WriteT ( Out , "DEC (" ) 
      ; Strings . WriteS ( Out , Name ) 
      ; WriteT ( Out , ", " ) 
      ; WriteI ( Out , Value , 0 ) 
      ; WriteT ( Out , ");" ) 
      ; WriteNl ( Out ) 
      | tLanguage . C 
      => Strings . WriteS ( Out , Name ) 
      ; WriteT ( Out , " -= " ) 
      ; WriteI ( Out , Value , 0 ) 
      ; WriteC ( Out , ';' ) 
      ; WriteNl ( Out ) 
      END (* CASE *) 
    END GenerateDecrement 

; PROCEDURE GenerateCaseLabel ( Out : tFile ; Label : INTEGER ) 

  = BEGIN (* GenerateCaseLabel *) 
      CASE Language 
      OF tLanguage . Modula2 
      => WriteT ( Out , "| " ) 
      ; WriteI ( Out , Label , 0 ) 
      ; WriteC ( Out , ':' ) 
      ; WriteNl ( Out ) 
      | tLanguage . C 
      => WriteT ( Out , "case " ) 
      ; WriteI ( Out , Label , 0 ) 
      ; WriteC ( Out , ':' ) 
      ; WriteNl ( Out ) 
      END (* CASE *) 
    END GenerateCaseLabel 

; PROCEDURE GenerateCaseLabels ( Out : tFile ; Set : tSet ) 

  = VAR FirstTime : BOOLEAN 

  ; BEGIN (* GenerateCaseLabels *) 
      CASE Language 
      OF tLanguage . Modula2 
      => FirstTime := TRUE 
      ; WriteC ( Out , '|' ) 
      ; WHILE NOT IsEmpty ( Set ) 
        DO IF FirstTime 
           THEN 
             FirstTime := FALSE 
           ELSE 
             WriteC ( Out , ',' ) 
           END (* IF *) 
        ; WriteI ( Out , Extract ( Set ) , 0 ) 
        ; WriteNl ( Out ) 
        END (* WHILE *) 
      ; WriteC ( Out , ':' ) 
      ; WriteNl ( Out ) 
      | tLanguage . C 
      => WHILE NOT IsEmpty ( Set ) 
         DO WriteT ( Out , "case " ) 
         ; WriteI ( Out , Extract ( Set ) , 0 ) 
         ; WriteT ( Out , ":;" )  (* ; helps to avoid yacc stack overflow in SUN's cc *) 
         ; WriteNl ( Out ) 
         END (* WHILE *) 
      END (* CASE *) 
    END GenerateCaseLabels 

; PROCEDURE MakeLabel ( ) : Word . T 

  = BEGIN (* MakeLabel *) 
      INC ( LabelCount ) 
    ; RETURN LabelCount 
    END MakeLabel 

; PROCEDURE GenerateGoto ( Out : tFile ; Label : Word . T ) 

  = BEGIN (* GenerateGoto *) 
      WriteT ( Out , "goto L" ) 
    ; WriteI ( Out , Label , 0 ) 
    ; WriteC ( Out , ';' ) 
    ; WriteNl ( Out ) 
    END GenerateGoto 

; PROCEDURE GenerateLabel ( Out : tFile ; Label : Word . T ) 

  = BEGIN (* GenerateLabel *) 
      WriteC ( Out , 'L' ) 
    ; WriteI ( Out , Label , 0 ) 
    ; WriteT ( Out , ": ;" ) 
    ; WriteNl ( Out ) 
    END GenerateLabel 

; PROCEDURE WriteLine ( Out : tFile ; Line : SHORTCARD ) 

  = BEGIN (* WriteLine *) 
      IF Line # 0 
      THEN 
        CASE Language 
        OF tLanguage . Modula2 
        => WriteT ( Out , "(* line " ) 
        ; WriteI ( Out , Line , 0 ) 
        ; WriteT ( Out , " \"" ) 
        ; WriteS ( Out , SourceFile ) 
        ; WriteT ( Out , "\" *)" ) 
        ; WriteNl ( Out ) 
        | tLanguage . C 
        => IF gGenLine 
           THEN 
             WriteT ( Out , "# line " ) 
           ; WriteI ( Out , Line , 0 ) 
           ; WriteT ( Out , " \"" ) 
           ; WriteS ( Out , SourceFile ) 
           ; WriteT ( Out , "\"\000" ) 
           ELSE 
             WriteT ( Out , "/* line " ) 
           ; WriteI ( Out , Line , 0 ) 
           ; WriteT ( Out , " \"" ) 
           ; WriteS ( Out , SourceFile ) 
           ; WriteT ( Out , "\" */" ) 
           END (* IF *) 
        ; WriteNl ( Out ) 
        END (* CASE *) 
      END (* IF *) 
    END WriteLine 

; PROCEDURE ConvertAppend ( a : TEXT ; VAR Text : tText ) 

  = VAR String : tString 

  ; BEGIN (* ConvertAppend *) 
      TextToString ( a , String ) 
    ; Texts . Append ( Text , String ) 
    END ConvertAppend 

; PROCEDURE ConvertAppend2 ( a1 , a2 : TEXT ; VAR Text : tText ) 

  = VAR String1 , String2 : tString 

  ; BEGIN (* ConvertAppend2 *) 
      TextToString ( a1 , String1 ) 
    ; IF ScannerName # NoIdent 
      THEN 
        Idents . GetString ( ScannerName , String2 ) 
      ; Concatenate ( String1 , String2 ) 
      ; Append ( String1 , '_' ) 
      END (* IF *) 
    ; TextToString ( a2 , String2 ) 
    ; Concatenate ( String1 , String2 ) 
    ; Texts . Append ( Text , String1 ) 
    END ConvertAppend2 

; PROCEDURE ConvertAppend3 ( a1 , a2 , a3 : TEXT ; VAR Text : tText ) 

  = VAR String1 , String2 : tString 

  ; BEGIN (* ConvertAppend3 *) 
      TextToString ( a1 , String1 ) 
    ; IF ScannerName # NoIdent 
      THEN 
        Idents . GetString ( ScannerName , String2 ) 
      ; Concatenate ( String1 , String2 ) 
      ; Append ( String1 , '_' ) 
      END (* IF *) 
    ; TextToString ( a2 , String2 ) 
    ; Concatenate ( String1 , String2 ) 
    ; IF ScannerName # NoIdent 
      THEN 
        Idents . GetString ( ScannerName , String2 ) 
      ; Concatenate ( String1 , String2 ) 
      ; Append ( String1 , '_' ) 
      END (* IF *) 
    ; TextToString ( a3 , String2 ) 
    ; Concatenate ( String1 , String2 ) 
    ; Texts . Append ( Text , String1 ) 
    END ConvertAppend3 

; PROCEDURE InitScanGen ( ) 

  = BEGIN (* InitScanGen *) 
      CASE Language 
      OF tLanguage . Modula2 
      => ConvertAppend ( "CASE yyStateStack^ [TokenLength] OF" , Case1 ) 

      ; ConvertAppend 
          ( "CASE yyAction [yyStateStack^ [TokenLength]] OF" , Case2 ) 

      ; ConvertAppend ( "Attribute.Position.Line   := yyLineCount;" , Leader ) 
      ; ConvertAppend 
          ( "Attribute.Position.Column := VAL(SHORTCARD,yyChBufferIndex - yyLineStart - TokenLength);" 
          , Leader 
          ) 

      ; ConvertAppend ( "yyRestartFlag := FALSE; EXIT;" , Trailer ) 

      ; ConvertAppend ( "(* BlankAction *)" , BlankText ) 
      ; ConvertAppend 
          ( "WHILE yyChBufferPtr^ [yyChBufferIndex] = ' ' DO INC (yyChBufferIndex); END;" 
          , BlankText 
          ) 

      ; ConvertAppend ( "(* TabAction *)" , TabText ) 
      ; ConvertAppend 
          ( "DEC (yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) MOD 8);" 
          , TabText 
          ) 

      ; ConvertAppend ( "(* EolAction *)" , EolText ) 
      ; ConvertAppend ( "INC (yyLineCount);" , EolText ) 
      ; ConvertAppend ( "yyLineStart := yyChBufferIndex - 1;" , EolText ) 

      ; ConvertAppend ( "WHILE yyStateStack^ [TokenLength] # " , Context1 ) 

      ; ConvertAppend ( " DO" , Context2 ) 
      ; ConvertAppend ( "   DEC (yyChBufferIndex);" , Context2 ) 
      ; ConvertAppend ( "   DEC (TokenLength);" , Context2 ) 
      ; ConvertAppend ( "END;" , Context2 ) 

      ; ConvertAppend ( "LOOP" , Context3 ) 
      ; ConvertAppend ( "   CASE yyStateStack^ [TokenLength] OF" , Context3 ) 

      ; ConvertAppend ( "      EXIT;" , Context4 ) 
      ; ConvertAppend ( "   ELSE" , Context4 ) 
      ; ConvertAppend ( "      DEC (yyChBufferIndex);" , Context4 ) 
      ; ConvertAppend ( "      DEC (TokenLength);" , Context4 ) 
      ; ConvertAppend ( "   END;" , Context4 ) 
      ; ConvertAppend ( "END;" , Context4 ) 

      ; IF Texts . IsEmpty ( Export ) 
        THEN 
          ConvertAppend ( "IMPORT Positions;" , Export ) 
        ; ConvertAppend 
            ( "TYPE tScanAttribute  = RECORD Position: Positions.tPosition; END;" 
            , Export 
            ) 
        ; ConvertAppend 
            ( "PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attribute: tScanAttribute);" 
            , Export 
            ) 
        END (* IF *) 
      ; IF Texts . IsEmpty ( Global ) 
        THEN 
          ConvertAppend 
            ( "PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attribute: tScanAttribute);" 
            , Global 
            ) 
        ; ConvertAppend ( "   BEGIN" , Global ) 
        ; ConvertAppend ( "   END ErrorAttribute;" , Global ) 
        END (* IF *) 
      ; IF Texts . IsEmpty ( Default ) 
        THEN 
          ConvertAppend 
            ( "IO.WriteC (IO.StdOutput, yyChBufferPtr^ [yyChBufferIndex-1]);" 
            , Default 
            ) 
        END (* IF *) 

      | tLanguage . C 
      => ConvertAppend ( "switch (* -- yyStatePtr) {" , Case1 ) 

      ; ConvertAppend ( "switch (yyAction [* -- yyStatePtr]) {" , Case2 ) 

      ; ConvertAppend2 
          ( "" , "Attribute.Position.Line   = yyLineCount;" , Leader ) 
      ; ConvertAppend3 
          ( "" 
          , "Attribute.Position.Column = (unsigned char *) " 
          , "TokenPtr - yyLineStart;" 
          , Leader 
          ) 

      ; ConvertAppend ( "goto yyBegin;" , Trailer ) 

      ; ConvertAppend ( "/* BlankAction */" , BlankText ) 
      ; ConvertAppend 
          ( "while (* yyChBufferIndexReg ++ == ' ') ;" , BlankText ) 
      ; ConvertAppend2 
          ( "" , "TokenPtr = (char *) -- yyChBufferIndexReg;" , BlankText ) 
      ; ConvertAppend ( "yyState = yyStartState;" , BlankText ) 
      ; ConvertAppend ( "yyStatePtr = & yyStateStack [1];" , BlankText ) 
      ; ConvertAppend ( "goto yyContinue;" , BlankText ) 

      ; ConvertAppend ( "/* TabAction */" , TabText ) 
      ; ConvertAppend2 
          ( "yyLineStart -= 7 - ((unsigned char *) " 
          , "TokenPtr - yyLineStart - 1) & 0x7; /* % 8 */" 
          , TabText 
          ) 

      ; ConvertAppend ( "/* EolAction */" , EolText ) 
      ; ConvertAppend ( "yyLineCount ++;" , EolText ) 
      ; ConvertAppend ( "yyLineStart = yyChBufferIndexReg - 1;" , EolText ) 

      ; ConvertAppend ( "while (* yyStatePtr != " , Context1 ) 

      ; ConvertAppend ( ") {" , Context2 ) 
      ; ConvertAppend ( "   yyChBufferIndex --;" , Context2 ) 
      ; ConvertAppend2 ( "   " , "TokenLength --;" , Context2 ) 
      ; ConvertAppend ( "   yyStatePtr --;" , Context2 ) 
      ; ConvertAppend ( "}" , Context2 ) 

      ; ConvertAppend ( "for (;;) {" , Context3 ) 
      ; ConvertAppend ( "   switch (* yyStatePtr) {" , Context3 ) 

      ; ConvertAppend ( "   default:" , Context4 ) 
      ; ConvertAppend ( "      yyChBufferIndex --;" , Context4 ) 
      ; ConvertAppend2 ( "      " , "TokenLength --;" , Context4 ) 
      ; ConvertAppend ( "      yyStatePtr --;" , Context4 ) 
      ; ConvertAppend ( "   }" , Context4 ) 
      ; ConvertAppend ( "}" , Context4 ) 

      ; IF Texts . IsEmpty ( Export ) 
        THEN 
          ConvertAppend ( "# include \"Positions.h\"" , Export ) 
        ; ConvertAppend2 
            ( "typedef struct { tPosition Position; } " 
            , "tScanAttribute;" 
            , Export 
            ) 
        ; ConvertAppend3 
            ( "extern void " 
            , "ErrorAttribute ARGS((int Token, " 
            , "tScanAttribute * Attribute));" 
            , Export 
            ) 
        END (* IF *) 
      ; IF Texts . IsEmpty ( Global ) 
        THEN 
          ConvertAppend2 
            ( "void " , "ErrorAttribute (Token, Attribute)" , Global ) 
        ; ConvertAppend ( "   int Token;" , Global ) 
        ; ConvertAppend2 ( "   " , "tScanAttribute * Attribute;" , Global ) 
        ; ConvertAppend ( "   { }" , Global ) 
        END (* IF *) 
      ; IF Texts . IsEmpty ( Default ) 
        THEN 
          ConvertAppend 
            ( "(void) putchar ((int) yyChBufferIndexReg [-1]);" , Default ) 
        END (* IF *) 

      END (* CASE *) 
    END InitScanGen 

; BEGIN (* ScanGen *) 
    ScannerName := NoIdent 
  ; BeginLine := 0 
  ; CloseLine := 0 
  ; DefaultLine := 0 
  ; DummyCount := 0 
  ; EofLine := 0 
  ; ExportLine := 0 
  ; GlobalLine := 0 
  ; LabelCount := 0 
  ; LocalLine := 0 
  ; MakeText ( Begin ) 
  ; MakeText ( BlankText ) 
  ; MakeText ( Case1 ) 
  ; MakeText ( Case2 ) 
  ; MakeText ( Close ) 
  ; MakeText ( Context1 ) 
  ; MakeText ( Context2 ) 
  ; MakeText ( Context3 ) 
  ; MakeText ( Context4 ) 
  ; MakeText ( Default ) 
  ; MakeText ( Eof ) 
  ; MakeText ( EolText ) 
  ; MakeText ( Export ) 
  ; MakeText ( Global ) 
  ; MakeText ( Leader ) 
  ; MakeText ( Local ) 
  ; MakeText ( TabText ) 
  ; MakeText ( Trailer ) 
  END ScanGen 
. 

