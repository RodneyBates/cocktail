#include "SYSTEM_.h"

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_DefTable
#include "DefTable.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_ScanTabs
#include "ScanTabs.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_ScanGen
#include "ScanGen.h"
#endif

Texts_tText ScanGen_Export, ScanGen_Global, ScanGen_Local, ScanGen_Begin, ScanGen_Close, ScanGen_Default, ScanGen_Eof, ScanGen_BlankText, ScanGen_TabText, ScanGen_EolText;
SHORTCARD ScanGen_ExportLine, ScanGen_GlobalLine, ScanGen_LocalLine, ScanGen_BeginLine, ScanGen_CloseLine, ScanGen_DefaultLine, ScanGen_EofLine;
Idents_tIdent ScanGen_ScannerName;
ScanGen_tLanguage ScanGen_Language;
Strings_tString ScanGen_RexLib;
struct ScanGen_1 ScanGen_SourceFile;

static CHAR ScannerMd [] = "Scanner.md";
static CHAR ScannerMi [] = "Scanner.mi";
static CHAR SourceMd [] = "Source.md";
static CHAR SourceMi [] = "Source.mi";
static CHAR ScanDrvMi [] = "ScanDrv.mi";
static CHAR ScannerH [] = "Scanner.h";
static CHAR ScannerC [] = "Scanner.c";
static CHAR SourceH [] = "Source.h";
static CHAR SourceC [] = "Source.c";
static CHAR ScanDrvC [] = "ScanDrv.c";
static CHAR Scanner [] = "Scanner";
static CHAR Source [] = "Source";
static CHAR Drv [] = "Drv";
static CHAR ExtMd [] = ".md";
static CHAR ExtMi [] = ".mi";
static CHAR ExtH [] = ".h";
static CHAR ExtC [] = ".c";
#define PatternNoMatch   15
#define Warning   4
static Texts_tText Case1, Case2, Context1, Context2, Context3, Context4, Leader, Trailer;
static CARDINAL LabelCount, DummyCount;
static BOOLEAN gGenLine;
static void ExpandLine ARGS((IO_tFile Out, Strings_tString Line));
static void CopyFile ARGS((CHAR InputA[], LONGCARD , Strings_tString OutputS, CHAR SuffixA[], LONGCARD ));
struct S_6 {
    CHAR A[127 + 1];
};
struct S_7 {
    CHAR A[127 + 1];
};
struct S_8 {
    CHAR A[127 + 1];
};
static void GenerateConstants ARGS((IO_tFile Out));
static void GenerateActions ARGS((IO_tFile Out, BOOLEAN ReduceCaseSize, BOOLEAN Warnings));
static void GenerateDecConstDef ARGS((IO_tFile Out, Strings_tString Name, INTEGER Value));
static void GenerateCharConstDef ARGS((IO_tFile Out, Strings_tString Name, CHAR Value));
static void GenerateDecrement ARGS((IO_tFile Out, Strings_tString Name, INTEGER Value));
static void GenerateCaseLabel ARGS((IO_tFile Out, INTEGER Label));
static void GenerateCaseLabels ARGS((IO_tFile Out, Sets_tSet Set));
static CARDINAL MakeLabel ARGS(());
static void GenerateGoto ARGS((IO_tFile Out, CARDINAL Label));
static void GenerateLabel ARGS((IO_tFile Out, CARDINAL Label));
static void WriteLine ARGS((IO_tFile Out, SHORTCARD Line));
static void ConvertAppend ARGS((CHAR a[], LONGCARD , Texts_tText *Text));
static void ConvertAppend2 ARGS((CHAR a1[], LONGCARD , CHAR a2[], LONGCARD , Texts_tText *Text));
static void ConvertAppend3 ARGS((CHAR a1[], LONGCARD , CHAR a2[], LONGCARD , CHAR a3[], LONGCARD , Texts_tText *Text));


static void ExpandLine
# ifdef __STDC__
(IO_tFile Out, Strings_tString Line)
# else
(Out, Line)
IO_tFile Out;
Strings_tString Line;
# endif
{
  CHAR Ch;
  CARDINAL i;

  i = 3;
  for (;;) {
    INC(i);
    if (i > Strings_Length(&Line)) {
      IO_WriteNl(Out);
      goto EXIT_1;
    }
    Ch = Strings_Char(&Line, (Strings_tStringIndex)i);
    switch (Ch) {
    case '@':;
      if (ScanGen_ScannerName == Idents_NoIdent) {
        IO_WriteS(Out, Scanner, 7L);
      } else {
        Idents_WriteIdent(Out, ScanGen_ScannerName);
      }
      break;
    case '$':;
      if (ScanGen_ScannerName == Idents_NoIdent) {
        if (Strings_Char(&Line, (Strings_tStringIndex)(i + 1)) == '_') {
          INC(i);
        }
      } else {
        Idents_WriteIdent(Out, ScanGen_ScannerName);
      }
      break;
    default :
      IO_WriteC(Out, Ch);
      break;
    }
  } EXIT_1:;
}

static void CopyFile
# ifdef __STDC__
(CHAR InputA[], LONGCARD O_2, Strings_tString OutputS, CHAR SuffixA[], LONGCARD O_1)
# else
(InputA, O_2, OutputS, SuffixA, O_1)
CHAR InputA[];
LONGCARD O_2;
Strings_tString OutputS;
CHAR SuffixA[];
LONGCARD O_1;
# endif
{
  IO_tFile In, Out;
  Strings_tString FileNameS, PathS, Line;
  struct S_6 PathA;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR) + O_2 * sizeof(CHAR), 2)
  COPY_OPEN_ARRAY(SuffixA, O_1, CHAR)
  COPY_OPEN_ARRAY(InputA, O_2, CHAR)
  Strings_ArrayToString(InputA, O_2, &FileNameS);
  Strings_Assign(&PathS, &ScanGen_RexLib);
  Strings_Concatenate(&PathS, &FileNameS);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 128L);
  In = IO_ReadOpen(PathA.A, 128L);
  Checks_ErrorCheck(PathA.A, 128L, In);
  Strings_ArrayToString(SuffixA, O_1, &FileNameS);
  Strings_Concatenate(&OutputS, &FileNameS);
  Strings_Append(&OutputS, '\0');
  Strings_StringToArray(&OutputS, PathA.A, 128L);
  Out = IO_WriteOpen(PathA.A, 128L);
  Checks_ErrorCheck(PathA.A, 128L, Out);
  while (!IO_EndOfFile(In)) {
    Strings_ReadL(In, &Line);
    if (Strings_Length(&Line) >= 2 && Strings_Char(&Line, 1) == '$' && Strings_Char(&Line, 2) == '@') {
      ExpandLine(Out, Line);
    } else {
      Strings_WriteL(Out, &Line);
    }
  }
  IO_ReadClose(In);
  IO_WriteClose(Out);
  FREE_OPEN_ARRAYS
}

void ScanGen_GenerateSupport
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString SourceName, DriverName, Suffix;

  Idents_GetString(ScanGen_ScannerName, &SourceName);
  Strings_ArrayToString(Source, 6L, &Suffix);
  Strings_Concatenate(&SourceName, &Suffix);
  if (ScanGen_ScannerName == Idents_NoIdent) {
    Strings_ArrayToString(Scanner, 7L, &DriverName);
  } else {
    Idents_GetString(ScanGen_ScannerName, &DriverName);
  }
  Strings_ArrayToString(Drv, 3L, &Suffix);
  Strings_Concatenate(&DriverName, &Suffix);
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    CopyFile(SourceMd, 9L, SourceName, ExtMd, 3L);
    CopyFile(SourceMi, 9L, SourceName, ExtMi, 3L);
    CopyFile(ScanDrvMi, 10L, DriverName, ExtMi, 3L);
    break;
  case ScanGen_C:;
    CopyFile(SourceH, 8L, SourceName, ExtH, 2L);
    CopyFile(SourceC, 8L, SourceName, ExtC, 2L);
    CopyFile(ScanDrvC, 9L, DriverName, ExtC, 2L);
    break;
  }
}

void ScanGen_GenerateInterface
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile In, Out;
  Strings_tString FileNameS, PathS, Line;
  struct S_7 PathA;

  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    Strings_ArrayToString(ScannerMd, 10L, &FileNameS);
    break;
  case ScanGen_C:;
    Strings_ArrayToString(ScannerH, 9L, &FileNameS);
    break;
  }
  Strings_Assign(&PathS, &ScanGen_RexLib);
  Strings_Concatenate(&PathS, &FileNameS);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 128L);
  In = IO_ReadOpen(PathA.A, 128L);
  Checks_ErrorCheck(PathA.A, 128L, In);
  if (ScanGen_ScannerName == Idents_NoIdent) {
    Strings_ArrayToString(Scanner, 7L, &PathS);
  } else {
    Idents_GetString(ScanGen_ScannerName, &PathS);
  }
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    Strings_ArrayToString(ExtMd, 3L, &FileNameS);
    break;
  case ScanGen_C:;
    Strings_ArrayToString(ExtH, 2L, &FileNameS);
    break;
  }
  Strings_Concatenate(&PathS, &FileNameS);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 128L);
  Out = IO_WriteOpen(PathA.A, 128L);
  Checks_ErrorCheck(PathA.A, 128L, Out);
  while (!IO_EndOfFile(In)) {
    Strings_ReadL(In, &Line);
    if (Strings_Length(&Line) >= 2 && Strings_Char(&Line, 1) == '$') {
      switch (Strings_Char(&Line, 2)) {
      case 'E':;
        WriteLine(Out, ScanGen_ExportLine);
        Texts_WriteText(Out, ScanGen_Export);
        break;
      case '@':;
        ExpandLine(Out, Line);
        break;
      }
    } else {
      Strings_WriteL(Out, &Line);
    }
  }
  IO_ReadClose(In);
  IO_WriteClose(Out);
}

void ScanGen_GenerateScanner
# ifdef __STDC__
(BOOLEAN ReduceCaseSize, BOOLEAN Warnings, BOOLEAN GenLine)
# else
(ReduceCaseSize, Warnings, GenLine)
BOOLEAN ReduceCaseSize, Warnings, GenLine;
# endif
{
  IO_tFile In, Out;
  Strings_tString FileNameS, PathS, Line;
  struct S_8 PathA;

  gGenLine = GenLine;
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    Strings_ArrayToString(ScannerMi, 10L, &FileNameS);
    break;
  case ScanGen_C:;
    Strings_ArrayToString(ScannerC, 9L, &FileNameS);
    break;
  }
  Strings_Assign(&PathS, &ScanGen_RexLib);
  Strings_Concatenate(&PathS, &FileNameS);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 128L);
  In = IO_ReadOpen(PathA.A, 128L);
  Checks_ErrorCheck(PathA.A, 128L, In);
  if (ScanGen_ScannerName == Idents_NoIdent) {
    Strings_ArrayToString(Scanner, 7L, &PathS);
  } else {
    Idents_GetString(ScanGen_ScannerName, &PathS);
  }
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    Strings_ArrayToString(ExtMi, 3L, &FileNameS);
    break;
  case ScanGen_C:;
    Strings_ArrayToString(ExtC, 2L, &FileNameS);
    break;
  }
  Strings_Concatenate(&PathS, &FileNameS);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 128L);
  Out = IO_WriteOpen(PathA.A, 128L);
  Checks_ErrorCheck(PathA.A, 128L, Out);
  while (!IO_EndOfFile(In)) {
    Strings_ReadL(In, &Line);
    if (Strings_Length(&Line) >= 2 && Strings_Char(&Line, 1) == '$') {
      switch (Strings_Char(&Line, 2)) {
      case 'G':;
        WriteLine(Out, ScanGen_GlobalLine);
        Texts_WriteText(Out, ScanGen_Global);
        break;
      case 'C':;
        GenerateConstants(Out);
        break;
      case 'M':;
        if (ReduceCaseSize) {
          Line.Chars.A[1] = ' ';
          Line.Chars.A[2] = ' ';
          Strings_WriteL(Out, &Line);
        }
        break;
      case 'L':;
        WriteLine(Out, ScanGen_LocalLine);
        Texts_WriteText(Out, ScanGen_Local);
        break;
      case 'J':;
        if (GenTabs_LeftJustUsed) {
          Line.Chars.A[1] = ' ';
          Line.Chars.A[2] = ' ';
          Strings_WriteL(Out, &Line);
        }
        break;
      case 'A':;
        GenerateActions(Out, ReduceCaseSize, Warnings);
        break;
      case 'N':;
        if (ReduceCaseSize) {
          GenerateCaseLabel(Out, (LONGINT)(GenTabs_PatternCount + 1));
        } else {
          GenerateCaseLabels(Out, GenTabs_PatternTablePtr->A[0].Finals);
        }
        break;
      case 'P':;
        if (ReduceCaseSize) {
          GenerateCaseLabel(Out, (LONGINT)GenTabs_DefaultAction);
        } else {
          GenerateCaseLabel(Out, (LONGINT)Sets_Select(&GenTabs_PatternTablePtr->A[GenTabs_DefaultAction].Finals));
        }
        break;
      case 'D':;
        WriteLine(Out, ScanGen_DefaultLine);
        Texts_WriteText(Out, ScanGen_Default);
        break;
      case 'O':;
        if (ReduceCaseSize) {
          GenerateCaseLabel(Out, (LONGINT)GenTabs_EobAction);
        } else {
          GenerateCaseLabel(Out, (LONGINT)Sets_Select(&GenTabs_PatternTablePtr->A[GenTabs_EobAction].Finals));
        }
        break;
      case 'E':;
        WriteLine(Out, ScanGen_EofLine);
        Texts_WriteText(Out, ScanGen_Eof);
        break;
      case 'I':;
        WriteLine(Out, ScanGen_BeginLine);
        Texts_WriteText(Out, ScanGen_Begin);
        break;
      case 'F':;
        WriteLine(Out, ScanGen_CloseLine);
        Texts_WriteText(Out, ScanGen_Close);
        break;
      case 'T':;
        ScanTabs_PutComb(Out);
        break;
      case 'B':;
        ScanTabs_PutBase(Out);
        break;
      case 'U':;
        ScanTabs_PutDefault(Out);
        break;
      case 'R':;
        ScanTabs_PutEobTrans(Out);
        break;
      case 'Q':;
        if (ReduceCaseSize) {
          ScanTabs_PutAction(Out);
        }
        break;
      case '@':;
        ExpandLine(Out, Line);
        break;
      }
    } else {
      Strings_WriteL(Out, &Line);
    }
  }
  IO_ReadClose(In);
  IO_WriteClose(Out);
}

static void GenerateConstants
# ifdef __STDC__
(IO_tFile Out)
# else
(Out)
IO_tFile Out;
# endif
{
  DefTable_DefRange Definition;
  Strings_tString String;
  Idents_tIdent Ident;
  SHORTCARD Number;

  Strings_ArrayToString((STRING)"yyFirstCh", 9L, &String);
  GenerateCharConstDef(Out, String, Dfa_FirstCh);
  Strings_ArrayToString((STRING)"yyLastCh", 8L, &String);
  GenerateCharConstDef(Out, String, Dfa_OldLastCh);
  Strings_ArrayToString((STRING)"yyEolCh", 7L, &String);
  GenerateCharConstDef(Out, String, Dfa_EolCh);
  Strings_ArrayToString((STRING)"yyEobCh", 7L, &String);
  GenerateCharConstDef(Out, String, Dfa_EobCh);
  Strings_ArrayToString((STRING)"yyDStateCount", 13L, &String);
  GenerateDecConstDef(Out, String, (LONGINT)Dfa_DStateCount);
  Strings_ArrayToString((STRING)"yyTableSize", 11L, &String);
  GenerateDecConstDef(Out, String, (LONGINT)ScanTabs_TableSize);
  Strings_ArrayToString((STRING)"yyEobState", 10L, &String);
  GenerateDecConstDef(Out, String, (LONGINT)Sets_Select(&GenTabs_PatternTablePtr->A[GenTabs_EobAction].Finals));
  Strings_ArrayToString((STRING)"yyDefaultState", 14L, &String);
  GenerateDecConstDef(Out, String, (LONGINT)Sets_Select(&GenTabs_PatternTablePtr->A[GenTabs_DefaultAction].Finals));
  {
    LONGINT B_1 = 1, B_2 = DefTable_DefCount;

    if (B_1 <= B_2)
      for (Definition = B_1;; Definition += 1) {
        if (DefTable_GetKind(Definition) == DefTable_Start) {
          DefTable_GetStartDef(Definition, &Ident, &Number);
          Idents_GetString(Ident, &String);
          GenerateDecConstDef(Out, String, (LONGINT)Number);
        }
        if (Definition >= B_2) break;
      }
  }
}

static void GenerateActions
# ifdef __STDC__
(IO_tFile Out, BOOLEAN ReduceCaseSize, BOOLEAN Warnings)
# else
(Out, ReduceCaseSize, Warnings)
IO_tFile Out;
BOOLEAN ReduceCaseSize, Warnings;
# endif
{
  SHORTCARD Rule, Pattern;
  Strings_tString String, String2;
  CARDINAL Label;

  if (ReduceCaseSize) {
    Texts_WriteText(Out, Case2);
  } else {
    Texts_WriteText(Out, Case1);
  }
  {
    SHORTCARD B_3 = 1, B_4 = GenTabs_PatternCount - 2;

    if (B_3 <= B_4)
      for (Pattern = B_3;; Pattern += 1) {
        if (!Sets_IsEmpty(GenTabs_PatternTablePtr->A[Pattern].Finals)) {
          if (ReduceCaseSize) {
            GenerateCaseLabel(Out, (LONGINT)Pattern);
          } else {
            GenerateCaseLabels(Out, GenTabs_PatternTablePtr->A[Pattern].Finals);
          }
          if (GenTabs_PatternTablePtr->A[Pattern].ContextLng == GenTabs_VariableContext) {
            if (Sets_Card(&GenTabs_PatternTablePtr->A[Pattern].DContext) == 1) {
              Texts_WriteText(Out, Context1);
              IO_WriteI(Out, (LONGINT)Sets_Select(&GenTabs_PatternTablePtr->A[Pattern].DContext), 0L);
              Texts_WriteText(Out, Context2);
            } else {
              Texts_WriteText(Out, Context3);
              GenerateCaseLabels(Out, GenTabs_PatternTablePtr->A[Pattern].DContext);
              if (ScanGen_Language == ScanGen_C) {
                Label = MakeLabel();
                GenerateGoto(Out, Label);
              }
              Texts_WriteText(Out, Context4);
              if (ScanGen_Language == ScanGen_C) {
                GenerateLabel(Out, Label);
              }
            }
          } else if (GenTabs_PatternTablePtr->A[Pattern].ContextLng > 0) {
            Strings_ArrayToString((STRING)"yyChBufferIndex", 15L, &String);
            GenerateDecrement(Out, String, (LONGINT)GenTabs_PatternTablePtr->A[Pattern].ContextLng);
            if (ScanGen_Language == ScanGen_C) {
              if (ScanGen_ScannerName == Idents_NoIdent) {
                Strings_ArrayToString((STRING)"TokenLength", 11L, &String);
              } else {
                Idents_GetString(ScanGen_ScannerName, &String);
                Strings_Append(&String, '_');
                Strings_ArrayToString((STRING)"TokenLength", 11L, &String2);
                Strings_Concatenate(&String, &String2);
              }
            } else {
              Strings_ArrayToString((STRING)"TokenLength", 11L, &String);
            }
            GenerateDecrement(Out, String, (LONGINT)GenTabs_PatternTablePtr->A[Pattern].ContextLng);
          } else if (GenTabs_PatternTablePtr->A[Pattern].ContextLng < 0) {
            IO_WriteS(Out, (STRING)"yyLess (", 8L);
            IO_WriteI(Out, (LONGINT)(-GenTabs_PatternTablePtr->A[Pattern].ContextLng), 0L);
            IO_WriteS(Out, (STRING)");", 2L);
            IO_WriteNl(Out);
          }
          Rule = GenTabs_PatternTablePtr->A[Pattern].Rule;
          if (GenTabs_RuleToCodePtr->A[Rule].CodeMode == ScanGen_Position) {
            Texts_WriteText(Out, Leader);
          }
          WriteLine(Out, GenTabs_RuleToCodePtr->A[Rule].TextLine);
          if (ScanGen_Language == ScanGen_C) {
            IO_WriteC(Out, '{');
          }
          Texts_WriteText(Out, GenTabs_RuleToCodePtr->A[Rule].Text);
          if (ScanGen_Language == ScanGen_C) {
            INC(DummyCount);
            IO_WriteS(Out, (STRING)"} yy", 4L);
            IO_WriteI(Out, (LONGINT)DummyCount, 0L);
            IO_WriteS(Out, (STRING)": ", 2L);
          }
          Texts_WriteText(Out, Trailer);
        } else if (GenTabs_PatternTablePtr->A[Pattern].Position.Line != 0 && Warnings) {
          Errors_ErrorMessage((LONGCARD)PatternNoMatch, (LONGCARD)Warning, GenTabs_PatternTablePtr->A[Pattern].Position);
        }
        if (Pattern >= B_4) break;
      }
  }
}

static void GenerateDecConstDef
# ifdef __STDC__
(IO_tFile Out, Strings_tString Name, INTEGER Value)
# else
(Out, Name, Value)
IO_tFile Out;
Strings_tString Name;
INTEGER Value;
# endif
{
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    Strings_WriteS(Out, &Name);
    IO_WriteS(Out, (STRING)"	= ", 3L);
    IO_WriteI(Out, Value, 0L);
    IO_WriteC(Out, ';');
    IO_WriteNl(Out);
    break;
  case ScanGen_C:;
    IO_WriteS(Out, (STRING)"# define ", 9L);
    Strings_WriteS(Out, &Name);
    IO_WriteC(Out, '\t');
    IO_WriteI(Out, Value, 0L);
    IO_WriteNl(Out);
    break;
  }
}

static void GenerateCharConstDef
# ifdef __STDC__
(IO_tFile Out, Strings_tString Name, CHAR Value)
# else
(Out, Name, Value)
IO_tFile Out;
Strings_tString Name;
CHAR Value;
# endif
{
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    Strings_WriteS(Out, &Name);
    IO_WriteS(Out, (STRING)"	= ", 3L);
    IO_WriteN(Out, ORD(Value), 1L, 8L);
    IO_WriteS(Out, (STRING)"C;", 2L);
    IO_WriteNl(Out);
    break;
  case ScanGen_C:;
    IO_WriteS(Out, (STRING)"# define ", 9L);
    Strings_WriteS(Out, &Name);
    IO_WriteS(Out, (STRING)"	(unsigned char) '\\", 19L);
    IO_WriteN(Out, ORD(Value), 1L, 8L);
    IO_WriteC(Out, '\'');
    IO_WriteNl(Out);
    break;
  }
}

static void GenerateDecrement
# ifdef __STDC__
(IO_tFile Out, Strings_tString Name, INTEGER Value)
# else
(Out, Name, Value)
IO_tFile Out;
Strings_tString Name;
INTEGER Value;
# endif
{
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    IO_WriteS(Out, (STRING)"DEC (", 5L);
    Strings_WriteS(Out, &Name);
    IO_WriteS(Out, (STRING)", ", 2L);
    IO_WriteI(Out, Value, 0L);
    IO_WriteS(Out, (STRING)");", 2L);
    IO_WriteNl(Out);
    break;
  case ScanGen_C:;
    Strings_WriteS(Out, &Name);
    IO_WriteS(Out, (STRING)" -= ", 4L);
    IO_WriteI(Out, Value, 0L);
    IO_WriteC(Out, ';');
    IO_WriteNl(Out);
    break;
  }
}

static void GenerateCaseLabel
# ifdef __STDC__
(IO_tFile Out, INTEGER Label)
# else
(Out, Label)
IO_tFile Out;
INTEGER Label;
# endif
{
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    IO_WriteS(Out, (STRING)"| ", 2L);
    IO_WriteI(Out, Label, 0L);
    IO_WriteC(Out, ':');
    IO_WriteNl(Out);
    break;
  case ScanGen_C:;
    IO_WriteS(Out, (STRING)"case ", 5L);
    IO_WriteI(Out, Label, 0L);
    IO_WriteC(Out, ':');
    IO_WriteNl(Out);
    break;
  }
}

static void GenerateCaseLabels
# ifdef __STDC__
(IO_tFile Out, Sets_tSet Set)
# else
(Out, Set)
IO_tFile Out;
Sets_tSet Set;
# endif
{
  BOOLEAN FirstTime;

  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    FirstTime = TRUE;
    IO_WriteC(Out, '|');
    while (!Sets_IsEmpty(Set)) {
      if (FirstTime) {
        FirstTime = FALSE;
      } else {
        IO_WriteC(Out, ',');
      }
      IO_WriteI(Out, (LONGINT)Sets_Extract(&Set), 0L);
      IO_WriteNl(Out);
    }
    IO_WriteC(Out, ':');
    IO_WriteNl(Out);
    break;
  case ScanGen_C:;
    while (!Sets_IsEmpty(Set)) {
      IO_WriteS(Out, (STRING)"case ", 5L);
      IO_WriteI(Out, (LONGINT)Sets_Extract(&Set), 0L);
      IO_WriteS(Out, (STRING)":;", 2L);
      IO_WriteNl(Out);
    }
    break;
  }
}

static CARDINAL MakeLabel
# ifdef __STDC__
()
# else
()
# endif
{
  INC(LabelCount);
  return LabelCount;
}

static void GenerateGoto
# ifdef __STDC__
(IO_tFile Out, CARDINAL Label)
# else
(Out, Label)
IO_tFile Out;
CARDINAL Label;
# endif
{
  IO_WriteS(Out, (STRING)"goto L", 6L);
  IO_WriteI(Out, (LONGINT)Label, 0L);
  IO_WriteC(Out, ';');
  IO_WriteNl(Out);
}

static void GenerateLabel
# ifdef __STDC__
(IO_tFile Out, CARDINAL Label)
# else
(Out, Label)
IO_tFile Out;
CARDINAL Label;
# endif
{
  IO_WriteC(Out, 'L');
  IO_WriteI(Out, (LONGINT)Label, 0L);
  IO_WriteS(Out, (STRING)": ;", 3L);
  IO_WriteNl(Out);
}

static void WriteLine
# ifdef __STDC__
(IO_tFile Out, SHORTCARD Line)
# else
(Out, Line)
IO_tFile Out;
SHORTCARD Line;
# endif
{
  if (Line != 0) {
    switch (ScanGen_Language) {
    case ScanGen_Modula:;
      IO_WriteS(Out, (STRING)"(* line ", 8L);
      IO_WriteI(Out, (LONGINT)Line, 0L);
      IO_WriteS(Out, (STRING)" \"", 2L);
      IO_WriteS(Out, ScanGen_SourceFile.A, 128L);
      IO_WriteS(Out, (STRING)"\" *)", 4L);
      IO_WriteNl(Out);
      break;
    case ScanGen_C:;
      if (gGenLine) {
        IO_WriteS(Out, (STRING)"# line ", 7L);
        IO_WriteI(Out, (LONGINT)Line, 0L);
        IO_WriteS(Out, (STRING)" \"", 2L);
        IO_WriteS(Out, ScanGen_SourceFile.A, 128L);
        IO_WriteS(Out, (STRING)"\"", 1L);
      } else {
        IO_WriteS(Out, (STRING)"/* line ", 8L);
        IO_WriteI(Out, (LONGINT)Line, 0L);
        IO_WriteS(Out, (STRING)" \"", 2L);
        IO_WriteS(Out, ScanGen_SourceFile.A, 128L);
        IO_WriteS(Out, (STRING)"\" */", 4L);
      }
      IO_WriteNl(Out);
      break;
    }
  }
}

static void ConvertAppend
# ifdef __STDC__
(CHAR a[], LONGCARD O_3, Texts_tText *Text)
# else
(a, O_3, Text)
CHAR a[];
LONGCARD O_3;
Texts_tText *Text;
# endif
{
  Strings_tString String;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_3, CHAR)
  Strings_ArrayToString(a, O_3, &String);
  Texts_Append(Text, &String);
  FREE_OPEN_ARRAYS
}

static void ConvertAppend2
# ifdef __STDC__
(CHAR a1[], LONGCARD O_5, CHAR a2[], LONGCARD O_4, Texts_tText *Text)
# else
(a1, O_5, a2, O_4, Text)
CHAR a1[];
LONGCARD O_5;
CHAR a2[];
LONGCARD O_4;
Texts_tText *Text;
# endif
{
  Strings_tString String1, String2;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR) + O_5 * sizeof(CHAR), 2)
  COPY_OPEN_ARRAY(a2, O_4, CHAR)
  COPY_OPEN_ARRAY(a1, O_5, CHAR)
  Strings_ArrayToString(a1, O_5, &String1);
  if (ScanGen_ScannerName != Idents_NoIdent) {
    Idents_GetString(ScanGen_ScannerName, &String2);
    Strings_Concatenate(&String1, &String2);
    Strings_Append(&String1, '_');
  }
  Strings_ArrayToString(a2, O_4, &String2);
  Strings_Concatenate(&String1, &String2);
  Texts_Append(Text, &String1);
  FREE_OPEN_ARRAYS
}

static void ConvertAppend3
# ifdef __STDC__
(CHAR a1[], LONGCARD O_8, CHAR a2[], LONGCARD O_7, CHAR a3[], LONGCARD O_6, Texts_tText *Text)
# else
(a1, O_8, a2, O_7, a3, O_6, Text)
CHAR a1[];
LONGCARD O_8;
CHAR a2[];
LONGCARD O_7;
CHAR a3[];
LONGCARD O_6;
Texts_tText *Text;
# endif
{
  Strings_tString String1, String2;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_6 * sizeof(CHAR) + O_7 * sizeof(CHAR) + O_8 * sizeof(CHAR), 3)
  COPY_OPEN_ARRAY(a3, O_6, CHAR)
  COPY_OPEN_ARRAY(a2, O_7, CHAR)
  COPY_OPEN_ARRAY(a1, O_8, CHAR)
  Strings_ArrayToString(a1, O_8, &String1);
  if (ScanGen_ScannerName != Idents_NoIdent) {
    Idents_GetString(ScanGen_ScannerName, &String2);
    Strings_Concatenate(&String1, &String2);
    Strings_Append(&String1, '_');
  }
  Strings_ArrayToString(a2, O_7, &String2);
  Strings_Concatenate(&String1, &String2);
  if (ScanGen_ScannerName != Idents_NoIdent) {
    Idents_GetString(ScanGen_ScannerName, &String2);
    Strings_Concatenate(&String1, &String2);
    Strings_Append(&String1, '_');
  }
  Strings_ArrayToString(a3, O_6, &String2);
  Strings_Concatenate(&String1, &String2);
  Texts_Append(Text, &String1);
  FREE_OPEN_ARRAYS
}

void ScanGen_InitScanGen
# ifdef __STDC__
()
# else
()
# endif
{
  switch (ScanGen_Language) {
  case ScanGen_Modula:;
    ConvertAppend((STRING)"CASE yyStateStack^ [TokenLength] OF", 35L, &Case1);
    ConvertAppend((STRING)"CASE yyAction [yyStateStack^ [TokenLength]] OF", 46L, &Case2);
    ConvertAppend((STRING)"Attribute.Position.Line   := yyLineCount;", 41L, &Leader);
    ConvertAppend((STRING)"Attribute.Position.Column := VAL(SHORTCARD,yyChBufferIndex - yyLineStart - TokenLength);", 88L, &Leader);
    ConvertAppend((STRING)"yyRestartFlag := FALSE; EXIT;", 29L, &Trailer);
    ConvertAppend((STRING)"(* BlankAction *)", 17L, &ScanGen_BlankText);
    ConvertAppend((STRING)"WHILE yyChBufferPtr^ [yyChBufferIndex] = ' ' DO INC (yyChBufferIndex); END;", 75L, &ScanGen_BlankText);
    ConvertAppend((STRING)"(* TabAction *)", 15L, &ScanGen_TabText);
    ConvertAppend((STRING)"DEC (yyLineStart, 7 - (yyChBufferIndex - yyLineStart - 2) MOD 8);", 65L, &ScanGen_TabText);
    ConvertAppend((STRING)"(* EolAction *)", 15L, &ScanGen_EolText);
    ConvertAppend((STRING)"INC (yyLineCount);", 18L, &ScanGen_EolText);
    ConvertAppend((STRING)"yyLineStart := yyChBufferIndex - 1;", 35L, &ScanGen_EolText);
    ConvertAppend((STRING)"WHILE yyStateStack^ [TokenLength] # ", 36L, &Context1);
    ConvertAppend((STRING)" DO", 3L, &Context2);
    ConvertAppend((STRING)"   DEC (yyChBufferIndex);", 25L, &Context2);
    ConvertAppend((STRING)"   DEC (TokenLength);", 21L, &Context2);
    ConvertAppend((STRING)"END;", 4L, &Context2);
    ConvertAppend((STRING)"LOOP", 4L, &Context3);
    ConvertAppend((STRING)"   CASE yyStateStack^ [TokenLength] OF", 38L, &Context3);
    ConvertAppend((STRING)"      EXIT;", 11L, &Context4);
    ConvertAppend((STRING)"   ELSE", 7L, &Context4);
    ConvertAppend((STRING)"      DEC (yyChBufferIndex);", 28L, &Context4);
    ConvertAppend((STRING)"      DEC (TokenLength);", 24L, &Context4);
    ConvertAppend((STRING)"   END;", 7L, &Context4);
    ConvertAppend((STRING)"END;", 4L, &Context4);
    if (Texts_IsEmpty(&ScanGen_Export)) {
      ConvertAppend((STRING)"IMPORT Positions;", 17L, &ScanGen_Export);
      ConvertAppend((STRING)"TYPE tScanAttribute	= RECORD Position: Positions.tPosition; END;", 64L, &ScanGen_Export);
      ConvertAppend((STRING)"PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attribute: tScanAttribute);", 73L, &ScanGen_Export);
    }
    if (Texts_IsEmpty(&ScanGen_Global)) {
      ConvertAppend((STRING)"PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attribute: tScanAttribute);", 73L, &ScanGen_Global);
      ConvertAppend((STRING)"   BEGIN", 8L, &ScanGen_Global);
      ConvertAppend((STRING)"   END ErrorAttribute;", 22L, &ScanGen_Global);
    }
    if (Texts_IsEmpty(&ScanGen_Default)) {
      ConvertAppend((STRING)"IO.WriteC (IO.StdOutput, yyChBufferPtr^ [yyChBufferIndex-1]);", 61L, &ScanGen_Default);
    }
    break;
  case ScanGen_C:;
    ConvertAppend((STRING)"switch (* -- yyStatePtr) {", 26L, &Case1);
    ConvertAppend((STRING)"switch (yyAction [* -- yyStatePtr]) {", 37L, &Case2);
    ConvertAppend2((STRING)"", 1L, (STRING)"Attribute.Position.Line   = yyLineCount;", 40L, &Leader);
    ConvertAppend3((STRING)"", 1L, (STRING)"Attribute.Position.Column = (unsigned char *) ", 46L, (STRING)"TokenPtr - yyLineStart;", 23L, &Leader);
    ConvertAppend((STRING)"goto yyBegin;", 13L, &Trailer);
    ConvertAppend((STRING)"/* BlankAction */", 17L, &ScanGen_BlankText);
    ConvertAppend((STRING)"while (* yyChBufferIndexReg ++ == ' ') ;", 40L, &ScanGen_BlankText);
    ConvertAppend2((STRING)"", 1L, (STRING)"TokenPtr = (char *) -- yyChBufferIndexReg;", 42L, &ScanGen_BlankText);
    ConvertAppend((STRING)"yyState = yyStartState;", 23L, &ScanGen_BlankText);
    ConvertAppend((STRING)"yyStatePtr = & yyStateStack [1];", 32L, &ScanGen_BlankText);
    ConvertAppend((STRING)"goto yyContinue;", 16L, &ScanGen_BlankText);
    ConvertAppend((STRING)"/* TabAction */", 15L, &ScanGen_TabText);
    ConvertAppend2((STRING)"yyLineStart -= 7 - ((unsigned char *) ", 38L, (STRING)"TokenPtr - yyLineStart - 1) & 0x7; /* % 8 */", 44L, &ScanGen_TabText);
    ConvertAppend((STRING)"/* EolAction */", 15L, &ScanGen_EolText);
    ConvertAppend((STRING)"yyLineCount ++;", 15L, &ScanGen_EolText);
    ConvertAppend((STRING)"yyLineStart = yyChBufferIndexReg - 1;", 37L, &ScanGen_EolText);
    ConvertAppend((STRING)"while (* yyStatePtr != ", 23L, &Context1);
    ConvertAppend((STRING)") {", 3L, &Context2);
    ConvertAppend((STRING)"   yyChBufferIndex --;", 22L, &Context2);
    ConvertAppend2((STRING)"   ", 3L, (STRING)"TokenLength --;", 15L, &Context2);
    ConvertAppend((STRING)"   yyStatePtr --;", 17L, &Context2);
    ConvertAppend((STRING)"}", 1L, &Context2);
    ConvertAppend((STRING)"for (;;) {", 10L, &Context3);
    ConvertAppend((STRING)"   switch (* yyStatePtr) {", 26L, &Context3);
    ConvertAppend((STRING)"   default:", 11L, &Context4);
    ConvertAppend((STRING)"      yyChBufferIndex --;", 25L, &Context4);
    ConvertAppend2((STRING)"      ", 6L, (STRING)"TokenLength --;", 15L, &Context4);
    ConvertAppend((STRING)"      yyStatePtr --;", 20L, &Context4);
    ConvertAppend((STRING)"   }", 4L, &Context4);
    ConvertAppend((STRING)"}", 1L, &Context4);
    if (Texts_IsEmpty(&ScanGen_Export)) {
      ConvertAppend((STRING)"# include \"Positions.h\"", 23L, &ScanGen_Export);
      ConvertAppend2((STRING)"typedef struct { tPosition Position; } ", 39L, (STRING)"tScanAttribute;", 15L, &ScanGen_Export);
      ConvertAppend3((STRING)"extern void ", 12L, (STRING)"ErrorAttribute ARGS((int Token, ", 32L, (STRING)"tScanAttribute * Attribute));", 29L, &ScanGen_Export);
    }
    if (Texts_IsEmpty(&ScanGen_Global)) {
      ConvertAppend2((STRING)"void ", 5L, (STRING)"ErrorAttribute (Token, Attribute)", 33L, &ScanGen_Global);
      ConvertAppend((STRING)"   int Token;", 13L, &ScanGen_Global);
      ConvertAppend2((STRING)"   ", 3L, (STRING)"tScanAttribute * Attribute;", 27L, &ScanGen_Global);
      ConvertAppend((STRING)"   { }", 6L, &ScanGen_Global);
    }
    if (Texts_IsEmpty(&ScanGen_Default)) {
      ConvertAppend((STRING)"(void) putchar ((int) yyChBufferIndexReg [-1]);", 47L, &ScanGen_Default);
    }
    break;
  }
}

void ScanGen__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Texts__init();
    Strings__init();
    Idents__init();
    Checks__init();
    IO__init();
    Texts__init();
    Sets__init();
    Strings__init();
    StringMem__init();
    Idents__init();
    Errors__init();
    DefTable__init();
    Dfa__init();
    ScanTabs__init();
    GenTabs__init();
    Texts__init();
    Strings__init();
    Idents__init();

    ScanGen_ScannerName = Idents_NoIdent;
    ScanGen_BeginLine = 0;
    ScanGen_CloseLine = 0;
    ScanGen_DefaultLine = 0;
    DummyCount = 0;
    ScanGen_EofLine = 0;
    ScanGen_ExportLine = 0;
    ScanGen_GlobalLine = 0;
    LabelCount = 0;
    ScanGen_LocalLine = 0;
    Texts_MakeText(&ScanGen_Begin);
    Texts_MakeText(&ScanGen_BlankText);
    Texts_MakeText(&Case1);
    Texts_MakeText(&Case2);
    Texts_MakeText(&ScanGen_Close);
    Texts_MakeText(&Context1);
    Texts_MakeText(&Context2);
    Texts_MakeText(&Context3);
    Texts_MakeText(&Context4);
    Texts_MakeText(&ScanGen_Default);
    Texts_MakeText(&ScanGen_Eof);
    Texts_MakeText(&ScanGen_EolText);
    Texts_MakeText(&ScanGen_Export);
    Texts_MakeText(&ScanGen_Global);
    Texts_MakeText(&Leader);
    Texts_MakeText(&ScanGen_Local);
    Texts_MakeText(&ScanGen_TabText);
    Texts_MakeText(&Trailer);
  }
}
