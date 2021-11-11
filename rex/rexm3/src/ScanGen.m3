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
 * fixed bug: changed variables Context2 and Context4 for variable right context in Modula
 * 
 * Revision 1.1  88/11/06  14:55:00  grosch
 * terminate case labels with superfluous ; to avoid yacc stack overflow with SUN's cc
 * 
 * Revision 1.0  88/10/04  11:59:44  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

 UNSAFE MODULE ScanGen;



FROM SYSTEM IMPORT SHORTCARD;
FROM Checks     IMPORT
   ErrorCheck;

FROM ReuseIO         IMPORT
   ReadOpen     , WriteOpen     , WriteClose    , ReadClose     ,
   EndOfFile    , WriteN        , WriteS        , WriteNl       ,
   WriteC       , WriteI        , tFile         ;

FROM Texts      IMPORT
   tText        , MakeText      , WriteText     ;

FROM Sets       IMPORT
   IsEmpty      , Card          , Select        , Extract       ,
   tSet         ;

FROM Strings    IMPORT
   tString      , Char          , ReadL         , WriteL        ,
   Length       , ArrayToString , StringToArray , Assign        ,
   Append       , Concatenate   ;

FROM StringMem  IMPORT
   tStringRef   , PutString     , GetString     ;

FROM Idents     IMPORT
   tIdent       , NoIdent       , WriteIdent    ;

FROM Errors     IMPORT
   ErrorMessage ;

FROM DefTable   IMPORT
   GetKind      , DefRange      , DefCount      , tKind         ,
   GetStartDef  ;

FROM Dfa        IMPORT
   FirstCh      , LastCh        , EolCh         , EobCh         ,
   DStateCount  , OldLastCh     ;

FROM ScanTabs   IMPORT
   TableSize    , PutComb, PutBase, PutDefault, PutEobTrans, PutAction;

FROM GenTabs    IMPORT
   RuleToCodePtr, PatternTablePtr, EobAction    , DefaultAction ,
   PatternCount , VariableContext, LeftJustUsed ;

IMPORT Word, Texts, Strings, Idents;

CONST
   ScannerMd    = ARRAY [0..10] OF CHAR{'S','c','a','n','n','e','r','.','m','d','\000'}  ;       (* file names for Modula-2      *)
   ScannerMi    = ARRAY [0..10] OF CHAR{'S','c','a','n','n','e','r','.','m','i','\000'}  ;
   SourceMd     = ARRAY [0..9] OF CHAR{'S','o','u','r','c','e','.','m','d','\000'}   ;
   SourceMi     = ARRAY [0..9] OF CHAR{'S','o','u','r','c','e','.','m','i','\000'}   ;
   ScanDrvMi    = ARRAY [0..10] OF CHAR{'S','c','a','n','D','r','v','.','m','i','\000'}  ;

   ScannerH     = ARRAY [0..9] OF CHAR{'S','c','a','n','n','e','r','.','h','\000'}   ;       (* file names for C             *)
   ScannerC     = ARRAY [0..9] OF CHAR{'S','c','a','n','n','e','r','.','c','\000'}   ;
   SourceH      = ARRAY [0..8] OF CHAR{'S','o','u','r','c','e','.','h','\000'}    ;
   SourceC      = ARRAY [0..8] OF CHAR{'S','o','u','r','c','e','.','c','\000'}    ;
   ScanDrvC     = ARRAY [0..9] OF CHAR{'S','c','a','n','D','r','v','.','c','\000'}   ;

   Scanner      = ARRAY [0..7] OF CHAR{'S','c','a','n','n','e','r','\000'}; 
   Source       = ARRAY [0..6] OF CHAR{'S','o','u','r','c','e','\000'};
   Drv          = ARRAY [0..3] OF CHAR{'D','r','v','\000'};
   ExtMd        = ARRAY [0..3] OF CHAR{'.','m','d','\000'};
   ExtMi        = ARRAY [0..3] OF CHAR{'.','m','i','\000'};
   ExtH         = ARRAY [0..2] OF CHAR{'.','h','\000'};
   ExtC         = ARRAY [0..2] OF CHAR{'.','c','\000'};

   PatternNoMatch = 15  ;
   Warning        = 4   ;

VAR
   Case1        ,
   Case2        ,
   Context1     ,
   Context2     ,
   Context3     ,
   Context4     ,
   Leader       ,
   Trailer      : tText;
   LabelCount   ,
   DummyCount   : Word.T;
   gGenLine     : BOOLEAN;

PROCEDURE ExpandLine (Out: tFile; Line: tString) =
   VAR
      Ch        : CHAR;
      i         : Word.T;
   BEGIN
      i := 3;
      LOOP
         INC (i);
         IF i > Length (Line) THEN WriteNl (Out); EXIT; END;
         Ch := Char (Line, i);
         CASE Ch OF
         | '@' => IF ScannerName = NoIdent
                 THEN WriteS (Out, Scanner); 
                 ELSE WriteIdent (Out, ScannerName); END;
         | '$' => IF ScannerName = NoIdent
                 THEN IF Char (Line, i + 1) = '_' THEN INC (i); END;
                 ELSE WriteIdent (Out, ScannerName); END;
         ELSE    WriteC (Out, Ch);
         END;
      END;
   END ExpandLine;

PROCEDURE GenerateSupport() =
   VAR SourceName, DriverName, Suffix   : tString;

   PROCEDURE CopyFile (READONLY InputA: ARRAY OF CHAR; OutputS: tString;READONLY  SuffixA: ARRAY OF CHAR) =
      VAR
         In, Out        : tFile;
         FileNameS      ,
         PathS          ,
         Line           : tString;
         PathA          : ARRAY [0..127] OF CHAR;
      BEGIN
         ArrayToString  (InputA, FileNameS);
         Assign         (PathS, RexLib);
         Concatenate    (PathS, FileNameS);
         Append         (PathS, '\000');
         StringToArray  (PathS, PathA);
         In := ReadOpen (PathA);
         ErrorCheck     (PathA, In);

         ArrayToString  (SuffixA, FileNameS);
         Concatenate    (OutputS, FileNameS);
         Append         (OutputS, '\000');
         StringToArray  (OutputS, PathA);
         Out := WriteOpen (PathA);
         ErrorCheck     (PathA, Out);

         WHILE NOT EndOfFile (In) DO
            ReadL       (In, Line);
            IF (Length (Line) >= 2) AND (Char (Line, 1) = '$') AND (Char (Line, 2) = '@') THEN
               ExpandLine (Out, Line);
            ELSE
               WriteL   (Out, Line);
            END;
         END;
         ReadClose      (In);
         WriteClose     (Out);
      END CopyFile;

   BEGIN
      Idents.GetString (ScannerName, SourceName);
      ArrayToString (Source, Suffix);
      Concatenate (SourceName, Suffix);
      IF ScannerName = NoIdent THEN
         ArrayToString (Scanner, DriverName);
      ELSE
         Idents.GetString (ScannerName, DriverName);
      END;
      ArrayToString (Drv, Suffix);
      Concatenate (DriverName, Suffix);
      CASE Language OF
      | tLanguage.Modula  => CopyFile (SourceMd    , SourceName, ExtMd);
                  CopyFile (SourceMi    , SourceName, ExtMi);
                  CopyFile (ScanDrvMi   , DriverName, ExtMi);

      | tLanguage.C       => CopyFile (SourceH     , SourceName, ExtH);
                  CopyFile (SourceC     , SourceName, ExtC);
                  CopyFile (ScanDrvC    , DriverName, ExtC);
      END;
   END GenerateSupport;

PROCEDURE GenerateInterface() =
   VAR
      In, Out   : tFile;
      FileNameS ,
      PathS     ,
      Line      : tString;
      PathA     : ARRAY [0..127] OF CHAR;
   BEGIN
      CASE Language OF
      | tLanguage.Modula  => ArrayToString (ScannerMd, FileNameS);
      | tLanguage.C       => ArrayToString (ScannerH , FileNameS);
      END;

      Assign            (PathS, RexLib);
      Concatenate       (PathS, FileNameS);
      Append            (PathS, '\000');
      StringToArray     (PathS, PathA);
      In := ReadOpen    (PathA);
      ErrorCheck        (PathA, In);

      IF ScannerName = NoIdent THEN
         ArrayToString (Scanner, PathS);
      ELSE
         Idents.GetString (ScannerName, PathS);
      END;
      CASE Language OF
      | tLanguage.Modula  => ArrayToString (ExtMd, FileNameS);
      | tLanguage.C       => ArrayToString (ExtH , FileNameS);
      END;
      Concatenate       (PathS, FileNameS);
      Append            (PathS, '\000');
      StringToArray     (PathS, PathA);
      Out := WriteOpen  (PathA);
      ErrorCheck        (PathA, Out);

      WHILE NOT EndOfFile (In) DO
         ReadL (In, Line);
         IF (Length (Line) >= 2) AND (Char (Line, 1) = '$') THEN
            CASE Char (Line, 2) OF
            |  'E'=> WriteLine (Out, ExportLine);
                    WriteText (Out, Export);
            |  '@'=> ExpandLine (Out, Line);
            END;
         ELSE
            WriteL (Out, Line);
         END;
      END;
      ReadClose  (In);
      WriteClose (Out);
   END GenerateInterface;

PROCEDURE GenerateScanner       (ReduceCaseSize, Warnings, GenLine: BOOLEAN) =
   VAR
      In, Out   : tFile;
      FileNameS ,
      PathS     ,
      Line      : tString;
      PathA     : ARRAY [0..127] OF CHAR;
   BEGIN
      gGenLine := GenLine;
      CASE Language OF
      | tLanguage.Modula  => ArrayToString (ScannerMi, FileNameS);
      | tLanguage.C       => ArrayToString (ScannerC , FileNameS);
      END;

      Assign            (PathS, RexLib);
      Concatenate       (PathS, FileNameS);
      Append            (PathS, '\000');
      StringToArray     (PathS, PathA);
      In := ReadOpen    (PathA);
      ErrorCheck        (PathA, In);

      IF ScannerName = NoIdent THEN
         ArrayToString (Scanner, PathS);
      ELSE
         Idents.GetString (ScannerName, PathS);
      END;
      CASE Language OF
      | tLanguage.Modula  => ArrayToString (ExtMi, FileNameS);
      | tLanguage.C       => ArrayToString (ExtC , FileNameS);
      END;
      Concatenate       (PathS, FileNameS);
      Append            (PathS, '\000');
      StringToArray     (PathS, PathA);
      Out := WriteOpen  (PathA);
      ErrorCheck        (PathA, Out);

      WHILE NOT EndOfFile (In) DO
         ReadL (In, Line);
         IF (Length (Line) >= 2) AND (Char (Line, 1) = '$') THEN
            CASE Char (Line, 2) OF
            |  'G'=> WriteLine (Out, GlobalLine);
                    WriteText (Out, Global);
            |  'C'=> GenerateConstants (Out);
            |  'M'=> IF ReduceCaseSize THEN
                       Line.Chars [1] := ' ';
                       Line.Chars [2] := ' ';
                       WriteL (Out, Line);
                    END;
            |  'L'=> WriteLine (Out, LocalLine);
                    WriteText (Out, Local);
            |  'J'=> IF LeftJustUsed THEN
                       Line.Chars [1] := ' ';
                       Line.Chars [2] := ' ';
                       WriteL (Out, Line);
                    END;
            |  'A'=> GenerateActions (Out, ReduceCaseSize, Warnings);
            |  'N'=> IF ReduceCaseSize THEN
                       GenerateCaseLabel (Out, PatternCount + 1);
                    ELSE
                       GenerateCaseLabels (Out, PatternTablePtr^[0].Finals);
                    END;
            |  'P'=> IF ReduceCaseSize THEN
                       GenerateCaseLabel (Out, DefaultAction);
                    ELSE
                       GenerateCaseLabel (Out, Select (PatternTablePtr^[DefaultAction].Finals));
                    END;
            |  'D'=> WriteLine (Out, DefaultLine);
                    WriteText (Out, Default);
            |  'O'=> IF ReduceCaseSize THEN
                       GenerateCaseLabel (Out, EobAction);
                    ELSE
                       GenerateCaseLabel (Out, Select (PatternTablePtr^[EobAction].Finals));
                    END;
            |  'E'=> WriteLine (Out, EofLine);
                    WriteText (Out, Eof);
            |  'I'=> WriteLine (Out, BeginLine);
                    WriteText (Out, Begin);
            |  'F'=> WriteLine (Out, CloseLine);
                    WriteText (Out, Close);
            |  'T'=> PutComb     (Out);
            |  'B'=> PutBase     (Out);
            |  'U'=> PutDefault(* $$ m2tom3 warning: actual parameter list is too short for procedure 'PutDefault' in line 385
 $$ *)  (Out);
            |  'R'=> PutEobTrans (Out);
            |  'Q'=> IF ReduceCaseSize THEN PutAction (Out); END;
            |  '@'=> ExpandLine (Out, Line);
            END;
         ELSE
            WriteL (Out, Line);
         END;
      END;
      ReadClose  (In);
      WriteClose (Out);
   END GenerateScanner;

PROCEDURE GenerateConstants (Out: tFile) =
   VAR
      Definition: DefRange      ;
      String    : tString       ;
      Ident     : tIdent        ;
      Number    : SHORTCARD     ;
   BEGIN
      ArrayToString             (ARRAY [0..9] OF CHAR{'y','y','F','i','r','s','t','C','h','\000'}    , String);
      GenerateCharConstDef      (Out, String, FirstCh   );
      ArrayToString             (ARRAY [0..8] OF CHAR{'y','y','L','a','s','t','C','h','\000'}     , String);
      GenerateCharConstDef      (Out, String, OldLastCh );
      ArrayToString             (ARRAY [0..7] OF CHAR{'y','y','E','o','l','C','h','\000'}      , String);
      GenerateCharConstDef      (Out, String, EolCh     );
      ArrayToString             (ARRAY [0..7] OF CHAR{'y','y','E','o','b','C','h','\000'}      , String);
      GenerateCharConstDef      (Out, String, EobCh     );
      ArrayToString             (ARRAY [0..13] OF CHAR{'y','y','D','S','t','a','t','e','C','o','u','n','t','\000'}, String);
      GenerateDecConstDef       (Out, String, DStateCount);
      ArrayToString             (ARRAY [0..11] OF CHAR{'y','y','T','a','b','l','e','S','i','z','e','\000'}  , String);
      GenerateDecConstDef       (Out, String, TableSize );
      ArrayToString             (ARRAY [0..10] OF CHAR{'y','y','E','o','b','S','t','a','t','e','\000'}   , String);
      GenerateDecConstDef       (Out, String, Select (PatternTablePtr^[EobAction].Finals));
      ArrayToString             (ARRAY [0..14] OF CHAR{'y','y','D','e','f','a','u','l','t','S','t','a','t','e','\000'}, String);
      GenerateDecConstDef       (Out, String, Select (PatternTablePtr^[DefaultAction].Finals));

      FOR Definition := 1 TO DefCount DO
         IF GetKind (Definition) = tKind.Start THEN
            GetStartDef (Definition, Ident, Number);
            Idents.GetString (Ident, String);
            GenerateDecConstDef (Out, String, Number);
         END;
      END;
   END GenerateConstants;

PROCEDURE GenerateActions (Out: tFile; ReduceCaseSize, Warnings: BOOLEAN) =
   VAR
      Rule      ,
      Pattern   : SHORTCARD     ;
      String    ,
      String2   : tString       ;
      Label     : Word.T      ;
   BEGIN
      IF ReduceCaseSize THEN
         WriteText (Out, Case2);
      ELSE
         WriteText (Out, Case1);
      END;
      FOR Pattern := 1 TO PatternCount - 2 DO   (* omit special rules *)
         IF NOT IsEmpty (PatternTablePtr^[Pattern].Finals) THEN
            IF ReduceCaseSize THEN
               GenerateCaseLabel (Out, Pattern);
            ELSE
               GenerateCaseLabels (Out, PatternTablePtr^[Pattern].Finals);
            END;
            IF PatternTablePtr^[Pattern].ContextLng = VariableContext THEN
               IF Card (PatternTablePtr^[Pattern].DContext) = 1 THEN
                  WriteText (Out, Context1);
                  WriteI (Out, Select (PatternTablePtr^[Pattern].DContext), 0);
                  WriteText (Out, Context2);
               ELSE
                  WriteText (Out, Context3);
                  GenerateCaseLabels (Out, PatternTablePtr^[Pattern].DContext);
                  IF Language = tLanguage.C THEN
                     Label := MakeLabel ();
                     GenerateGoto (Out, Label);
                  END;
                  WriteText (Out, Context4);
                  IF Language = tLanguage.C THEN
                     GenerateLabel (Out, Label);
                  END;
               END;
            ELSIF PatternTablePtr^[Pattern].ContextLng > 0 THEN
               ArrayToString (ARRAY [0..15] OF CHAR{'y','y','C','h','B','u','f','f','e','r','I','n','d','e','x','\000'}, String);
               GenerateDecrement (Out, String, PatternTablePtr^[Pattern].ContextLng);
               IF Language = tLanguage.C THEN
                  IF ScannerName = NoIdent THEN
                     ArrayToString (ARRAY [0..11] OF CHAR{'T','o','k','e','n','L','e','n','g','t','h','\000'}, String);
                  ELSE
                     Idents.GetString (ScannerName, String);
                     Append (String, '_');
                     ArrayToString (ARRAY [0..11] OF CHAR{'T','o','k','e','n','L','e','n','g','t','h','\000'}, String2);
                     Concatenate (String, String2);
                  END;
               ELSE
                  ArrayToString (ARRAY [0..11] OF CHAR{'T','o','k','e','n','L','e','n','g','t','h','\000'}, String);
               END;
               GenerateDecrement (Out, String, PatternTablePtr^[Pattern].ContextLng);
            ELSIF PatternTablePtr^[Pattern].ContextLng < 0 THEN
               WriteS (Out, ARRAY [0..8] OF CHAR{'y','y','L','e','s','s',' ','(','\000'});
               WriteI (Out, - PatternTablePtr^[Pattern].ContextLng, 0);
               WriteS (Out, ARRAY [0..2] OF CHAR{')',';','\000'});
               WriteNl (Out);
            END;
            Rule := PatternTablePtr^[Pattern].Rule;
            IF RuleToCodePtr^[Rule].CodeMode = Position THEN
               WriteText (Out, Leader);
            END;
            WriteLine (Out, RuleToCodePtr^[Rule].TextLine);
            IF Language = tLanguage.C THEN WriteC (Out, '{'); END;
            WriteText (Out, RuleToCodePtr^[Rule].Text);
            IF Language = tLanguage.C THEN
               INC (DummyCount);
               WriteS (Out, ARRAY [0..4] OF CHAR{'}',' ','y','y','\000'});
               WriteI (Out, DummyCount, 0);
               WriteS (Out, ARRAY [0..2] OF CHAR{':',' ','\000'});
            END;
            WriteText (Out, Trailer);
         ELSIF (PatternTablePtr^[Pattern].Position.Line # 0) AND Warnings THEN
            ErrorMessage (PatternNoMatch, Warning, PatternTablePtr^[Pattern].Position);
         END;
      END;
   END GenerateActions;

PROCEDURE GenerateDecConstDef (Out: tFile; Name: tString; Value: INTEGER) =
   BEGIN
      CASE Language OF
      | tLanguage.Modula=>
         Strings.WriteS (Out, Name);
         WriteS (Out, ARRAY [0..3] OF CHAR{' ','=',' ','\000'});
         WriteI (Out, Value, 0);
         WriteC (Out, ';');
         WriteNl (Out);
      | tLanguage.C=>
         WriteS (Out, ARRAY [0..9] OF CHAR{'#',' ','d','e','f','i','n','e',' ','\000'});
         Strings.WriteS (Out, Name);
         WriteC (Out, ' ');
         WriteI (Out, Value, 0);
         WriteNl (Out);
      END;
   END GenerateDecConstDef;

PROCEDURE GenerateCharConstDef (Out: tFile; Name: tString; Value: CHAR) =
   BEGIN
      CASE Language OF
      | tLanguage.Modula=>
         Strings.WriteS (Out, Name);
         WriteS (Out, ARRAY [0..3] OF CHAR{' ','=',' ','\000'});
         WriteN (Out, ORD (Value), 1, 8);
         WriteS (Out, ARRAY [0..2] OF CHAR{'C',';','\000'});
         WriteNl (Out);
      | tLanguage.C=>
         WriteS (Out, ARRAY [0..9] OF CHAR{'#',' ','d','e','f','i','n','e',' ','\000'});
         Strings.WriteS (Out, Name);
         WriteS (Out, ARRAY [0..19] OF CHAR{' ','(','u','n','s','i','g','n','e','d',' ','c','h','a','r',')',' ','\'','\','\000'});
         WriteN (Out, ORD (Value), 1, 8);
         WriteC (Out, '\'');
         WriteNl (Out);
      END;
   END GenerateCharConstDef;

PROCEDURE GenerateDecrement (Out: tFile; Name: tString; Value: INTEGER) =
   BEGIN
      CASE Language OF
      | tLanguage.Modula=>
         WriteS (Out, ARRAY [0..5] OF CHAR{'D','E','C',' ','(','\000'});
         Strings.WriteS (Out, Name);
         WriteS (Out, ARRAY [0..2] OF CHAR{',',' ','\000'});
         WriteI (Out, Value, 0);
         WriteS (Out, ARRAY [0..2] OF CHAR{')',';','\000'});
         WriteNl (Out);
      | tLanguage.C=>
         Strings.WriteS (Out, Name);
         WriteS (Out, ARRAY [0..4] OF CHAR{' ','-','=',' ','\000'});
         WriteI (Out, Value, 0);
         WriteC (Out, ';');
         WriteNl (Out);
      END;
   END GenerateDecrement;

PROCEDURE GenerateCaseLabel (Out: tFile; Label: INTEGER) =
   BEGIN
      CASE Language OF
      | tLanguage.Modula=>
         WriteS (Out, ARRAY [0..2] OF CHAR{'|',' ','\000'});
         WriteI (Out, Label, 0);
         WriteC (Out, ':');
         WriteNl (Out);
      | tLanguage.C=>
         WriteS (Out, ARRAY [0..5] OF CHAR{'c','a','s','e',' ','\000'});
         WriteI (Out, Label, 0);
         WriteC (Out, ':');
         WriteNl (Out);
      END;
   END GenerateCaseLabel;

PROCEDURE GenerateCaseLabels (Out: tFile; Set: tSet) =
   VAR FirstTime        : BOOLEAN;
   BEGIN
      CASE Language OF
      | tLanguage.Modula=>
         FirstTime := TRUE;
         WriteC (Out, '|');
         WHILE NOT IsEmpty (Set) DO
            IF FirstTime THEN
               FirstTime := FALSE;
            ELSE
               WriteC (Out, ',');
            END;
            WriteI (Out, Extract (Set), 0);
            WriteNl (Out);
         END;
         WriteC (Out, ':');
         WriteNl (Out);
      | tLanguage.C=>
         WHILE NOT IsEmpty (Set) DO
            WriteS (Out, ARRAY [0..5] OF CHAR{'c','a','s','e',' ','\000'});
            WriteI (Out, Extract (Set), 0);
            WriteS (Out, ARRAY [0..2] OF CHAR{':',';','\000'});   (* ; helps to avoid yacc stack overflow in SUN's cc *)
            WriteNl (Out);
         END;
      END;
   END GenerateCaseLabels;

PROCEDURE MakeLabel (): Word.T =
   BEGIN
      INC (LabelCount);
      RETURN LabelCount;
   END MakeLabel;

PROCEDURE GenerateGoto (Out: tFile; Label: Word.T) =
   BEGIN
      WriteS (Out, ARRAY [0..6] OF CHAR{'g','o','t','o',' ','L','\000'});
      WriteI (Out, Label, 0);
      WriteC (Out, ';');
      WriteNl (Out);
   END GenerateGoto;

PROCEDURE GenerateLabel (Out: tFile; Label: Word.T) =
   BEGIN
      WriteC (Out, 'L');
      WriteI (Out, Label, 0);
      WriteS (Out, ARRAY [0..3] OF CHAR{':',' ',';','\000'});
      WriteNl (Out);
   END GenerateLabel;

PROCEDURE WriteLine (Out: tFile; Line: SHORTCARD) =
   BEGIN
      IF Line # 0 THEN
         CASE Language OF
         | tLanguage.Modula=>
            WriteS (Out, ARRAY [0..8] OF CHAR{'(','*',' ','l','i','n','e',' ','\000'});
            WriteI (Out, Line, 0);
            WriteS (Out, ARRAY [0..2] OF CHAR{' ','"','\000'});
            WriteS (Out, SourceFile);
            WriteS (Out, ARRAY [0..4] OF CHAR{'"',' ','*',')','\000'});
            WriteNl (Out);
         | tLanguage.C=>
            IF gGenLine THEN
               WriteS (Out, ARRAY [0..7] OF CHAR{'#',' ','l','i','n','e',' ','\000'});
               WriteI (Out, Line, 0);
               WriteS (Out, ARRAY [0..2] OF CHAR{' ','"','\000'});
               WriteS (Out, SourceFile);
               WriteS (Out, '"');
            ELSE
               WriteS (Out, ARRAY [0..8] OF CHAR{'/','*',' ','l','i','n','e',' ','\000'});
               WriteI (Out, Line, 0);
               WriteS (Out, ARRAY [0..2] OF CHAR{' ','"','\000'});
               WriteS (Out, SourceFile);
               WriteS (Out, ARRAY [0..4] OF CHAR{'"',' ','*','/','\000'});
            END;
            WriteNl (Out);
         END;
      END;
   END WriteLine;

PROCEDURE ConvertAppend (READONLY a: ARRAY OF CHAR; VAR Text: tText) =
   VAR String   : tString;
   BEGIN
      ArrayToString (a, String);
      Texts.Append  (Text, String);
   END ConvertAppend;

PROCEDURE ConvertAppend2 (READONLY a1, a2: ARRAY OF CHAR; VAR Text: tText) =
   VAR String1, String2 : tString;
   BEGIN
      ArrayToString (a1, String1);
      IF ScannerName # NoIdent THEN
         Idents.GetString (ScannerName, String2);
         Concatenate (String1, String2);
         Append (String1, '_');
      END;
      ArrayToString (a2, String2);
      Concatenate (String1, String2);
      Texts.Append  (Text, String1);
   END ConvertAppend2;

PROCEDURE ConvertAppend3 (READONLY a1, a2, a3: ARRAY OF CHAR; VAR Text: tText) =
   VAR String1, String2 : tString;
   BEGIN
      ArrayToString (a1, String1);
      IF ScannerName # NoIdent THEN
         Idents.GetString (ScannerName, String2);
         Concatenate (String1, String2);
         Append (String1, '_');
      END;
      ArrayToString (a2, String2);
      Concatenate (String1, String2);
      IF ScannerName # NoIdent THEN
         Idents.GetString (ScannerName, String2);
         Concatenate (String1, String2);
         Append (String1, '_');
      END;
      ArrayToString (a3, String2);
      Concatenate (String1, String2);
      Texts.Append  (Text, String1);
   END ConvertAppend3;

PROCEDURE InitScanGen() =
   BEGIN
CASE Language OF
| tLanguage.Modula=>
   ConvertAppend (ARRAY [0..35] OF CHAR{'C','A','S','E',' ','y','y','S','t','a','t','e','S','t','a','c','k','^',' ','[','T','o','k','e','n','L','e','n','g','t','h',']',' ','O','F','\000'} , Case1);

   ConvertAppend (ARRAY [0..46] OF CHAR{'C','A','S','E',' ','y','y','A','c','t','i','o','n',' ','[','y','y','S','t','a','t','e','S','t','a','c','k','^',' ','[','T','o','k','e','n','L','e','n','g','t','h',']',']',' ','O','F','\000'}, Case2);

   ConvertAppend (ARRAY [0..41] OF CHAR{'A','t','t','r','i','b','u','t','e','.','P','o','s','i','t','i','o','n','.','L','i','n','e',' ',' ',' ',':','=',' ','y','y','L','i','n','e','C','o','u','n','t',';','\000'}   , Leader);
   ConvertAppend (ARRAY [0..88] OF CHAR{'A','t','t','r','i','b','u','t','e','.','P','o','s','i','t','i','o','n','.','C','o','l','u','m','n',' ',':','=',' ','V','A','L','(','S','H','O','R','T','C','A','R','D',',','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',' ','-',' ','y','y','L','i','n','e','S','t','a','r','t',' ','-',' ','T','o','k','e','n','L','e','n','g','t','h',')',';','\000'}, Leader);

   ConvertAppend (ARRAY [0..29] OF CHAR{'y','y','R','e','s','t','a','r','t','F','l','a','g',' ',':','=',' ','F','A','L','S','E',';',' ','E','X','I','T',';','\000'}               , Trailer);

   ConvertAppend (ARRAY [0..17] OF CHAR{'(','*',' ','B','l','a','n','k','A','c','t','i','o','n',' ','*',')','\000'}                           , BlankText);
   ConvertAppend (ARRAY [0..75] OF CHAR{'W','H','I','L','E',' ','y','y','C','h','B','u','f','f','e','r','P','t','r','^',' ','[','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',']',' ','=',' ','\'',' ','\'',' ','D','O',' ','I','N','C',' ','(','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',')',';',' ','E','N','D',';','\000'}, BlankText);

   ConvertAppend (ARRAY [0..15] OF CHAR{'(','*',' ','T','a','b','A','c','t','i','o','n',' ','*',')','\000'}                             , TabText);
   ConvertAppend (ARRAY [0..65] OF CHAR{'D','E','C',' ','(','y','y','L','i','n','e','S','t','a','r','t',',',' ','7',' ','-',' ','(','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',' ','-',' ','y','y','L','i','n','e','S','t','a','r','t',' ','-',' ','2',')',' ','M','O','D',' ','8',')',';','\000'}, TabText);

   ConvertAppend (ARRAY [0..15] OF CHAR{'(','*',' ','E','o','l','A','c','t','i','o','n',' ','*',')','\000'}                             , EolText);
   ConvertAppend (ARRAY [0..18] OF CHAR{'I','N','C',' ','(','y','y','L','i','n','e','C','o','u','n','t',')',';','\000'}                          , EolText);
   ConvertAppend (ARRAY [0..35] OF CHAR{'y','y','L','i','n','e','S','t','a','r','t',' ',':','=',' ','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',' ','-',' ','1',';','\000'}         , EolText);

   ConvertAppend (ARRAY [0..36] OF CHAR{'W','H','I','L','E',' ','y','y','S','t','a','t','e','S','t','a','c','k','^',' ','[','T','o','k','e','n','L','e','n','g','t','h',']',' ','#',' ','\000'}        , Context1);

   ConvertAppend (ARRAY [0..3] OF CHAR{' ','D','O','\000'}                                         , Context2);
   ConvertAppend (ARRAY [0..25] OF CHAR{' ',' ',' ','D','E','C',' ','(','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',')',';','\000'}                   , Context2);
   ConvertAppend (ARRAY [0..21] OF CHAR{' ',' ',' ','D','E','C',' ','(','T','o','k','e','n','L','e','n','g','t','h',')',';','\000'}                       , Context2);
   ConvertAppend (ARRAY [0..4] OF CHAR{'E','N','D',';','\000'}                                        , Context2);

   ConvertAppend (ARRAY [0..4] OF CHAR{'L','O','O','P','\000'}                                        , Context3);
   ConvertAppend (ARRAY [0..38] OF CHAR{' ',' ',' ','C','A','S','E',' ','y','y','S','t','a','t','e','S','t','a','c','k','^',' ','[','T','o','k','e','n','L','e','n','g','t','h',']',' ','O','F','\000'}      , Context3);

   ConvertAppend (ARRAY [0..11] OF CHAR{' ',' ',' ',' ',' ',' ','E','X','I','T',';','\000'}                                 , Context4);
   ConvertAppend (ARRAY [0..7] OF CHAR{' ',' ',' ','E','L','S','E','\000'}                                     , Context4);
   ConvertAppend (ARRAY [0..28] OF CHAR{' ',' ',' ',' ',' ',' ','D','E','C',' ','(','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',')',';','\000'}                , Context4);
   ConvertAppend (ARRAY [0..24] OF CHAR{' ',' ',' ',' ',' ',' ','D','E','C',' ','(','T','o','k','e','n','L','e','n','g','t','h',')',';','\000'}                    , Context4);
   ConvertAppend (ARRAY [0..7] OF CHAR{' ',' ',' ','E','N','D',';','\000'}                                     , Context4);
   ConvertAppend (ARRAY [0..4] OF CHAR{'E','N','D',';','\000'}                                        , Context4);

IF Texts.IsEmpty (Export) THEN
   ConvertAppend (ARRAY [0..17] OF CHAR{'I','M','P','O','R','T',' ','P','o','s','i','t','i','o','n','s',';','\000'}                           , Export);
   ConvertAppend (ARRAY [0..65] OF CHAR{'T','Y','P','E',' ','t','S','c','a','n','A','t','t','r','i','b','u','t','e',' ',' ','=',' ','R','E','C','O','R','D',' ','P','o','s','i','t','i','o','n',':',' ','P','o','s','i','t','i','o','n','s','.','t','P','o','s','i','t','i','o','n',';',' ','E','N','D',';','\000'}, Export);
   ConvertAppend (ARRAY [0..73] OF CHAR{'P','R','O','C','E','D','U','R','E',' ','E','r','r','o','r','A','t','t','r','i','b','u','t','e',' ','(','T','o','k','e','n',':',' ','I','N','T','E','G','E','R',';',' ','V','A','R',' ','A','t','t','r','i','b','u','t','e',':',' ','t','S','c','a','n','A','t','t','r','i','b','u','t','e',')',';','\000'}, Export);
END;
IF Texts.IsEmpty (Global) THEN
   ConvertAppend (ARRAY [0..73] OF CHAR{'P','R','O','C','E','D','U','R','E',' ','E','r','r','o','r','A','t','t','r','i','b','u','t','e',' ','(','T','o','k','e','n',':',' ','I','N','T','E','G','E','R',';',' ','V','A','R',' ','A','t','t','r','i','b','u','t','e',':',' ','t','S','c','a','n','A','t','t','r','i','b','u','t','e',')',';','\000'}, Global);
   ConvertAppend (ARRAY [0..8] OF CHAR{' ',' ',' ','B','E','G','I','N','\000'}                                    , Global);
   ConvertAppend (ARRAY [0..22] OF CHAR{' ',' ',' ','E','N','D',' ','E','r','r','o','r','A','t','t','r','i','b','u','t','e',';','\000'}                      , Global);
END;
IF Texts.IsEmpty (Default) THEN
   ConvertAppend (ARRAY [0..61] OF CHAR{'I','O','.','W','r','i','t','e','C',' ','(','I','O','.','S','t','d','O','u','t','p','u','t',',',' ','y','y','C','h','B','u','f','f','e','r','P','t','r','^',' ','[','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x','-','1',']',')',';','\000'}, Default);
END;

| tLanguage.C=>
   ConvertAppend (ARRAY [0..26] OF CHAR{'s','w','i','t','c','h',' ','(','*',' ','-','-',' ','y','y','S','t','a','t','e','P','t','r',')',' ','{','\000'}                  , Case1);

   ConvertAppend (ARRAY [0..37] OF CHAR{'s','w','i','t','c','h',' ','(','y','y','A','c','t','i','o','n',' ','[','*',' ','-','-',' ','y','y','S','t','a','t','e','P','t','r',']',')',' ','{','\000'}       , Case2);

   ConvertAppend2(ARRAY [0..0] OF CHAR{'\000'}, ARRAY [0..40] OF CHAR{'A','t','t','r','i','b','u','t','e','.','P','o','s','i','t','i','o','n','.','L','i','n','e',' ',' ',' ','=',' ','y','y','L','i','n','e','C','o','u','n','t',';','\000'}, Leader);
   ConvertAppend3(ARRAY [0..0] OF CHAR{'\000'}, ARRAY [0..46] OF CHAR{'A','t','t','r','i','b','u','t','e','.','P','o','s','i','t','i','o','n','.','C','o','l','u','m','n',' ','=',' ','(','u','n','s','i','g','n','e','d',' ','c','h','a','r',' ','*',')',' ','\000'}, ARRAY [0..23] OF CHAR{'T','o','k','e','n','P','t','r',' ','-',' ','y','y','L','i','n','e','S','t','a','r','t',';','\000'}, Leader);

   ConvertAppend (ARRAY [0..13] OF CHAR{'g','o','t','o',' ','y','y','B','e','g','i','n',';','\000'}                               , Trailer);

   ConvertAppend (ARRAY [0..17] OF CHAR{'/','*',' ','B','l','a','n','k','A','c','t','i','o','n',' ','*','/','\000'}                           , BlankText);
   ConvertAppend (ARRAY [0..40] OF CHAR{'w','h','i','l','e',' ','(','*',' ','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x','R','e','g',' ','+','+',' ','=','=',' ','\'',' ','\'',')',' ',';','\000'}    , BlankText);
   ConvertAppend2(ARRAY [0..0] OF CHAR{'\000'}, ARRAY [0..42] OF CHAR{'T','o','k','e','n','P','t','r',' ','=',' ','(','c','h','a','r',' ','*',')',' ','-','-',' ','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x','R','e','g',';','\000'}      , BlankText);
   ConvertAppend (ARRAY [0..23] OF CHAR{'y','y','S','t','a','t','e',' ','=',' ','y','y','S','t','a','r','t','S','t','a','t','e',';','\000'}                     , BlankText);
   ConvertAppend (ARRAY [0..32] OF CHAR{'y','y','S','t','a','t','e','P','t','r',' ','=',' ','&',' ','y','y','S','t','a','t','e','S','t','a','c','k',' ','[','1',']',';','\000'}            , BlankText);
   ConvertAppend (ARRAY [0..16] OF CHAR{'g','o','t','o',' ','y','y','C','o','n','t','i','n','u','e',';','\000'}                            , BlankText);

   ConvertAppend (ARRAY [0..15] OF CHAR{'/','*',' ','T','a','b','A','c','t','i','o','n',' ','*','/','\000'}                             , TabText);
   ConvertAppend2(ARRAY [0..38] OF CHAR{'y','y','L','i','n','e','S','t','a','r','t',' ','-','=',' ','7',' ','-',' ','(','(','u','n','s','i','g','n','e','d',' ','c','h','a','r',' ','*',')',' ','\000'}, ARRAY [0..44] OF CHAR{'T','o','k','e','n','P','t','r',' ','-',' ','y','y','L','i','n','e','S','t','a','r','t',' ','-',' ','1',')',' ','&',' ','0','x','7',';',' ','/','*',' ','%',' ','8',' ','*','/','\000'}, TabText);

   ConvertAppend (ARRAY [0..15] OF CHAR{'/','*',' ','E','o','l','A','c','t','i','o','n',' ','*','/','\000'}                             , EolText);
   ConvertAppend (ARRAY [0..15] OF CHAR{'y','y','L','i','n','e','C','o','u','n','t',' ','+','+',';','\000'}                             , EolText);
   ConvertAppend (ARRAY [0..37] OF CHAR{'y','y','L','i','n','e','S','t','a','r','t',' ','=',' ','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x','R','e','g',' ','-',' ','1',';','\000'}       , EolText);

   ConvertAppend (ARRAY [0..23] OF CHAR{'w','h','i','l','e',' ','(','*',' ','y','y','S','t','a','t','e','P','t','r',' ','!','=',' ','\000'}                     , Context1);

   ConvertAppend (ARRAY [0..3] OF CHAR{')',' ','{','\000'}                                         , Context2);
   ConvertAppend (ARRAY [0..22] OF CHAR{' ',' ',' ','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',' ','-','-',';','\000'}                      , Context2);
   ConvertAppend2(ARRAY [0..3] OF CHAR{' ',' ',' ','\000'}, ARRAY [0..15] OF CHAR{'T','o','k','e','n','L','e','n','g','t','h',' ','-','-',';','\000'}                      , Context2);
   ConvertAppend (ARRAY [0..17] OF CHAR{' ',' ',' ','y','y','S','t','a','t','e','P','t','r',' ','-','-',';','\000'}                           , Context2);
   ConvertAppend ('}'                                           , Context2);

   ConvertAppend (ARRAY [0..10] OF CHAR{'f','o','r',' ','(',';',';',')',' ','{','\000'}                                  , Context3);
   ConvertAppend (ARRAY [0..26] OF CHAR{' ',' ',' ','s','w','i','t','c','h',' ','(','*',' ','y','y','S','t','a','t','e','P','t','r',')',' ','{','\000'}                  , Context3);

   ConvertAppend (ARRAY [0..11] OF CHAR{' ',' ',' ','d','e','f','a','u','l','t',':','\000'}                                 , Context4);
   ConvertAppend (ARRAY [0..25] OF CHAR{' ',' ',' ',' ',' ',' ','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x',' ','-','-',';','\000'}                   , Context4);
   ConvertAppend2(ARRAY [0..6] OF CHAR{' ',' ',' ',' ',' ',' ','\000'}, ARRAY [0..15] OF CHAR{'T','o','k','e','n','L','e','n','g','t','h',' ','-','-',';','\000'}                   , Context4);
   ConvertAppend (ARRAY [0..20] OF CHAR{' ',' ',' ',' ',' ',' ','y','y','S','t','a','t','e','P','t','r',' ','-','-',';','\000'}                        , Context4);
   ConvertAppend (ARRAY [0..4] OF CHAR{' ',' ',' ','}','\000'}                                        , Context4);
   ConvertAppend ('}'                                           , Context4);

IF Texts.IsEmpty (Export) THEN
   ConvertAppend (ARRAY [0..23] OF CHAR{'#',' ','i','n','c','l','u','d','e',' ','"','P','o','s','i','t','i','o','n','s','.','h','"','\000'}                     , Export);
   ConvertAppend2(ARRAY [0..39] OF CHAR{'t','y','p','e','d','e','f',' ','s','t','r','u','c','t',' ','{',' ','t','P','o','s','i','t','i','o','n',' ','P','o','s','i','t','i','o','n',';',' ','}',' ','\000'}, ARRAY [0..15] OF CHAR{'t','S','c','a','n','A','t','t','r','i','b','u','t','e',';','\000'}, Export);
   ConvertAppend3(ARRAY [0..12] OF CHAR{'e','x','t','e','r','n',' ','v','o','i','d',' ','\000'}, ARRAY [0..32] OF CHAR{'E','r','r','o','r','A','t','t','r','i','b','u','t','e',' ','A','R','G','S','(','(','i','n','t',' ','T','o','k','e','n',',',' ','\000'}, ARRAY [0..29] OF CHAR{'t','S','c','a','n','A','t','t','r','i','b','u','t','e',' ','*',' ','A','t','t','r','i','b','u','t','e',')',')',';','\000'}, Export);
END;
IF Texts.IsEmpty (Global) THEN
   ConvertAppend2(ARRAY [0..5] OF CHAR{'v','o','i','d',' ','\000'}, ARRAY [0..33] OF CHAR{'E','r','r','o','r','A','t','t','r','i','b','u','t','e',' ','(','T','o','k','e','n',',',' ','A','t','t','r','i','b','u','t','e',')','\000'}  , Global);
   ConvertAppend (ARRAY [0..13] OF CHAR{' ',' ',' ','i','n','t',' ','T','o','k','e','n',';','\000'}                               , Global);
   ConvertAppend2(ARRAY [0..3] OF CHAR{' ',' ',' ','\000'}, ARRAY [0..27] OF CHAR{'t','S','c','a','n','A','t','t','r','i','b','u','t','e',' ','*',' ','A','t','t','r','i','b','u','t','e',';','\000'}          , Global);
   ConvertAppend (ARRAY [0..6] OF CHAR{' ',' ',' ','{',' ','}','\000'}                                      , Global);
END;
IF Texts.IsEmpty (Default) THEN
   ConvertAppend (ARRAY [0..47] OF CHAR{'(','v','o','i','d',')',' ','p','u','t','c','h','a','r',' ','(','(','i','n','t',')',' ','y','y','C','h','B','u','f','f','e','r','I','n','d','e','x','R','e','g',' ','[','-','1',']',')',';','\000'}, Default);
END;

END;
   END InitScanGen;

BEGIN
   ScannerName  := NoIdent;
   BeginLine    := 0;
   CloseLine    := 0;
   DefaultLine  := 0;
   DummyCount   := 0;
   EofLine      := 0;
   ExportLine   := 0;
   GlobalLine   := 0;
   LabelCount   := 0;
   LocalLine    := 0;
   MakeText (Begin);
   MakeText (BlankText);
   MakeText (Case1);
   MakeText (Case2);
   MakeText (Close);
   MakeText (Context1);
   MakeText (Context2);
   MakeText (Context3);
   MakeText (Context4);
   MakeText (Default);
   MakeText (Eof);
   MakeText (EolText);
   MakeText (Export);
   MakeText (Global);
   MakeText (Leader);
   MakeText (Local);
   MakeText (TabText);
   MakeText (Trailer);
END ScanGen.

