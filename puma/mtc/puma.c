#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Tree2
#include "Tree2.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_Optimize
#include "Optimize.h"
#endif

#ifndef DEFINITION_M2
#include "M2.h"
#endif

#ifndef DEFINITION_M3
#include "M3.h"
#endif

#ifndef DEFINITION_Ada
#include "Ada.h"
#endif

#ifndef DEFINITION_C
#include "C.h"
#endif

static CHAR DefExtMc [] = ".md";
static CHAR ImpExtMc [] = ".mi";
static CHAR DefExtM3 [] = ".i3";
static CHAR ImpExtM3 [] = ".m3";
static CHAR DefExtAda [] = ".ads";
static CHAR ImpExtAda [] = ".adb";
static CHAR DefExtC [] = ".h";
static CHAR ImpExtC [] = ".c";
static Strings_tString PumaLib, TrafoFile, String, PathS;
static struct S_1 {
    CHAR A[255 + 1];
} Argument, PathA;
static SHORTCARD i, j, n;
static CHAR ch;
static BOOLEAN OptionFound;
static Tree_tTree Node;
static IO_tFile SmartOpen ARGS((Strings_tString FileName));
static void SmartClose ARGS((Strings_tString FileName, IO_tFile f));
static void GenerateMacros ARGS(());
static INTEGER IndentLevel;
static void WriteClass ARGS((Tree_tTree t));
static BOOLEAN IsFirst;
static void WritePattern ARGS((Tree_tTree t));


static IO_tFile SmartOpen
# ifdef __STDC__
(Strings_tString FileName)
# else
(FileName)
Strings_tString FileName;
# endif
{
  Strings_tString LPathS;

  if (Sets_IsElement(ORD('7'), &Tree_Options)) {
    Strings_ArrayToString((STRING)"yy", 2L, &LPathS);
    Strings_Concatenate(&LPathS, &FileName);
    Strings_Append(&LPathS, '\0');
    Strings_StringToArray(&LPathS, PathA.A, 256L);
  } else {
    Strings_Append(&FileName, '\0');
    Strings_StringToArray(&FileName, PathA.A, 256L);
  }
  return IO_WriteOpen(PathA.A, 256L);
}

static void SmartClose
# ifdef __STDC__
(Strings_tString FileName, IO_tFile f)
# else
(FileName, f)
Strings_tString FileName;
IO_tFile f;
# endif
{
  Strings_tString LPathS;

  IO_WriteClose(f);
  if (Sets_IsElement(ORD('7'), &Tree_Options)) {
    Strings_Assign(&PathS, &PumaLib);
    Strings_ArrayToString((STRING)"gmdupd ", 7L, &String);
    Strings_Concatenate(&PathS, &String);
    Strings_Concatenate(&LPathS, &FileName);
    Strings_ArrayToString((STRING)" yy", 3L, &String);
    Strings_Concatenate(&LPathS, &String);
    Strings_Concatenate(&LPathS, &FileName);
    Strings_Append(&LPathS, '\0');
    Strings_StringToArray(&LPathS, PathA.A, 256L);
    n = System(PathA.A, 256L);
  }
}

static void GenerateMacros
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile TypeTabFile;
  Strings_tString s;
  Idents_tIdent i;
  INTEGER j;

  if (Sets_IsElement(ORD('c'), &Tree_Options)) {
    Strings_ArrayToString((STRING)"TypeTab.c", 9L, &String);
  } else if (Sets_IsElement(ORD('K'), &Tree_Options)) {
    Strings_ArrayToString((STRING)"TypeTab.m3", 10L, &String);
  } else if (Sets_IsElement(ORD('A'), &Tree_Options)) {
    Strings_ArrayToString((STRING)"TypeTab.a", 9L, &String);
  } else {
    Strings_ArrayToString((STRING)"TypeTab.m", 9L, &String);
  }
  Strings_Assign(&PathS, &PumaLib);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 256L);
  TypeTabFile = IO_ReadOpen(PathA.A, 256L);
  Strings_ArrayToString((STRING)"yy", 2L, &PathS);
  Idents_GetString(Tree_TreeRoot->U_1.V_26.Spec.TrafoName, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_ArrayToString((STRING)".w", 2L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 256L);
  Tree_f = IO_WriteOpen(PathA.A, 256L);
  while (!IO_EndOfFile(TypeTabFile)) {
    Strings_ReadL(TypeTabFile, &s);
    i = Idents_MakeIdent(&s);
    if (i <= Semantics_TypeCount && Sets_IsElement((Sets_tElement)i, &Semantics_TypeNames)) {
      Sets_Exclude(&Semantics_TypeNames, (Sets_tElement)i);
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      for (j = 2; j <= 7; j += 1) {
        IO_ReadNl(TypeTabFile);
      }
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    } else {
      for (j = 1; j <= 8; j += 1) {
        IO_ReadNl(TypeTabFile);
      }
    }
  }
  IO_ReadClose(TypeTabFile);
  Semantics_RemoveTreeTypes(Tree_TreeRoot);
  while (!Sets_IsEmpty(Semantics_TypeNames)) {
    i = Sets_Extract(&Semantics_TypeNames);
    Sets_Include(&Semantics_UserTypes, (Sets_tElement)i);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b)       memcmp ((char *) & a, (char *) & b, sizeof (a)) == 0", 65L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    } else if (Sets_IsElement(ORD('K'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b) ( a ) = ( b ) ", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    } else if (Sets_IsElement(ORD('A'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b) ( a ) = ( b ) ", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    } else {
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b)       yyIsEqual (a, b)", 29L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    }
  }
  if (Sets_IsElement(ORD('c'), &Tree_Options)) {
    C_MacroC(Tree_TreeRoot);
  } else if (Sets_IsElement(ORD('K'), &Tree_Options)) {
    M3_MacroM3(Tree_TreeRoot);
  } else if (Sets_IsElement(ORD('A'), &Tree_Options)) {
    Ada_MacroAda(Tree_TreeRoot);
  } else {
    M2_MacroMod(Tree_TreeRoot);
  }
  IO_WriteClose(Tree_f);
}

static void WriteClass
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  INTEGER i;

  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_1 = &t->U_1.V_5.Class;

      {
        LONGINT B_1 = 1, B_2 = IndentLevel;

        if (B_1 <= B_2)
          for (i = B_1;; i += 1) {
            IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   ", 3L);
            if (i >= B_2) break;
          }
      }
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_1->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   =", 4L);
      WriteClass(W_1->Attributes);
      if (W_1->Extensions->U_1.V_1.Kind != Tree_NoClass) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)" <", 2L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        INC(IndentLevel);
        WriteClass(W_1->Extensions);
        DEC(IndentLevel);
        {
          LONGINT B_3 = 1, B_4 = IndentLevel;

          if (B_3 <= B_4)
            for (i = B_3;; i += 1) {
              IO_WriteS((System_tFile)IO_StdOutput, (STRING)"   ", 3L);
              if (i >= B_4) break;
            }
        }
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)">", 1L);
      }
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)" .", 2L);
      IO_WriteNl((System_tFile)IO_StdOutput);
      WriteClass(W_1->Next);
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_2 = &t->U_1.V_9.Child;

      IO_WriteS((System_tFile)IO_StdOutput, (STRING)" ", 1L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_2->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)": ", 2L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_2->Type);
      WriteClass(W_2->Next);
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_3 = &t->U_1.V_10.Attribute;

      if (((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_3->Properties) == 0X0L) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)" [", 2L);
        Idents_WriteIdent((System_tFile)IO_StdOutput, W_3->Name);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)": ", 2L);
        Idents_WriteIdent((System_tFile)IO_StdOutput, W_3->Type);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"]", 1L);
      }
      WriteClass(W_3->Next);
    }
    break;
  case Tree_ActionPart:;
    {
      register Tree_yActionPart *W_4 = &t->U_1.V_11.ActionPart;

      WriteClass(W_4->Next);
    }
    break;
  default :
    break;
  }
}

static void WritePattern
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_5 = &t->U_1.V_5.Class;

      Idents_WriteIdent((System_tFile)IO_StdOutput, W_5->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)" (", 2L);
      IsFirst = TRUE;
      Tree_ForallAttributes(t, (Tree_ProcOfT)WritePattern);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)")", 1L);
      IO_WriteNl((System_tFile)IO_StdOutput);
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_6 = &t->U_1.V_9.Child;

      if (IsFirst) {
        IsFirst = FALSE;
      } else {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)", ", 2L);
      }
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_6->Name);
      IO_WriteS((System_tFile)IO_StdOutput, (STRING)":", 1L);
      Idents_WriteIdent((System_tFile)IO_StdOutput, W_6->Type);
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_7 = &t->U_1.V_10.Attribute;

      if (((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_7->Properties) == 0X0L) {
        if (IsFirst) {
          IsFirst = FALSE;
        } else {
          IO_WriteS((System_tFile)IO_StdOutput, (STRING)", ", 2L);
        }
        Idents_WriteIdent((System_tFile)IO_StdOutput, W_7->Name);
      }
    }
    break;
  default :
    break;
  }
}

extern int  parameters_argc;
extern char **parameters_argv;
extern char **parameters_envp;
# ifdef __STDC__
void main(int argc, char *argv[], char *envp[])
# else
void main(argc, argv, envp)
  int argc;
  char *argv[], *envp[];
# endif
{
parameters_argc = argc;
parameters_argv = argv;
parameters_envp = envp;
  System__init();
  Memory__init();
  IO__init();
  Strings__init();
  Idents__init();
  Sets__init();
  Errors__init();
  Scanner__init();
  Parser__init();
  Tree__init();
  Tree2__init();
  Semantics__init();
  Optimize__init();
  M2__init();
  M3__init();
  Ada__init();
  C__init();

  IndentLevel = 0;
  Strings_AssignEmpty(&PumaLib);
  Tree_SourceFile.A[0] = '\0';
  OptionFound = FALSE;
  n = GetArgCount() - 1;
  i = 1;
  while (i <= n) {
    GetArgument((LONGINT)i, Argument.A, 256L);
    if (Argument.A[0] == '-') {
      if (Argument.A[1] == 'l') {
        Strings_AssignEmpty(&PumaLib);
        if (Argument.A[2] == '\0') {
          INC(i);
          if (i <= n) {
            GetArgument((LONGINT)i, Argument.A, 256L);
          } else {
            Argument.A[0] = '\0';
          }
          j = 0;
        } else {
          j = 2;
        }
        for (;;) {
          ch = Argument.A[j];
          if (ch == '\0') {
            goto EXIT_1;
          }
          Strings_Append(&PumaLib, ch);
          INC(j);
        } EXIT_1:;
        Strings_Append(&PumaLib, '/');
      } else {
        j = 0;
        for (;;) {
          INC(j);
          ch = Argument.A[j];
          if (ch == '\0') {
            goto EXIT_2;
          } else {
            OptionFound = TRUE;
            if (ch == '?') {
              Sets_Include(&Tree_Options, ORD('h'));
            } else if (ch == 'c') {
              Sets_Include(&Tree_Options, ORD('c'));
              Sets_Exclude(&Tree_Options, ORD('K'));
              Sets_Exclude(&Tree_Options, ORD('A'));
            } else if (ch == 'K') {
              Sets_Include(&Tree_Options, ORD('K'));
              Sets_Exclude(&Tree_Options, ORD('c'));
              Sets_Exclude(&Tree_Options, ORD('A'));
            } else if (ch == 'A') {
              Sets_Include(&Tree_Options, ORD('A'));
              Sets_Exclude(&Tree_Options, ORD('c'));
              Sets_Exclude(&Tree_Options, ORD('K'));
            } else {
              Sets_Include(&Tree_Options, ORD(ch));
            }
          }
        } EXIT_2:;
      }
    } else if (Argument.A[0] == '?') {
      Sets_Include(&Tree_Options, ORD('h'));
    } else {
      j = 0;
      do {
        ch = Argument.A[j];
        Tree_SourceFile.A[j] = ch;
        INC(j);
      } while (!(ch == '\0'));
    }
    INC(i);
  }
  if (!OptionFound) {
    Sets_Include(&Tree_Options, ORD('a'));
  }
  if (Sets_IsElement(ORD('a'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('d'));
    Sets_Include(&Tree_Options, ORD('i'));
  }
  if (Sets_IsElement(ORD('h'), &Tree_Options)) {
    Sets_Exclude(&Tree_Options, ORD('h'));
    Tree_f = IO_StdOutput;
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"usage: puma [-options] [-ldir | -l dir] [file]", 46L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" a generate all, same as -di (default)", 38L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" b suppress optimization of multiple IFs into CASE statements", 61L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" c generate C code (default is Modula-2)", 40L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" d generate definition module", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" e treat undefined names as error", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" f signal a runtime error if none of the rules of a procedure matches", 69L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" g allow too few positional patterns in a rule", 46L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" h print help information", 25L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" i generate implementation module", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" j recognize unqualified names of children of decompose patterns", 64L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" k allow non-linear patterns", 28L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" -ldir or -l dir specify the directory dir where puma finds its tables", 70L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" m use procedure MakeTREE to construct nodes (default is inline code)", 69L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" n check parameters for NoTREE (NIL) and treat as failure (tg compatibility)", 76L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" o list undefined names on standard output", 42L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" p allow node constructors without parentheses", 46L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" q browse internal data structure", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" r print patterns", 17L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" s suppress warnings", 20L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" t print tree definitions", 25L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" u require ':' or ':>' after label", 34L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" v treat undefined names as warning", 35L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" w surround actions by WITH statements (Modula), or DECLARE", 59L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"   blocks with renames (Ada) (tg compatibility)", 47L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" A generate Ada code (default is Modula-2)", 42L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" J warn on duplicated names children of decompose patterns", 58L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" K generate Modula-3 code (default is Modula-2)", 47L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" X keep macro file and cpp input", 32L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 3 write puma internal data structure to std output, before semantics.", 70L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 4 write puma internal data structure to std output, after semantics.", 69L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 5 write puma internal data structure to std output, after optimize/RuleProperties.", 83L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 6 generate # line directives", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 7 touch output files only if necessary", 39L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 8 report storage consumption", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
  }
  if (Sets_IsEmpty(Tree_Options)) {
    IO_CloseIO();
    exit(1);
  }
  Strings_ArrayToString(Scanner_ScanTabName.A, 128L, &String);
  Strings_Assign(&PathS, &PumaLib);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, Scanner_ScanTabName.A, 128L);
  Strings_ArrayToString(Parser_ParsTabName.A, 129L, &String);
  Strings_Assign(&PathS, &PumaLib);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, Parser_ParsTabName.A, 129L);
  Errors_StoreMessages(TRUE);
  if (Tree_SourceFile.A[0] != '\0') {
    Scanner_BeginFile(Tree_SourceFile.A, 256L);
  }
  INC1(Tree_ErrorCount, Parser_Parser());
  Node = Tree_TreeRoot->U_1.V_26.Spec.TreeNames;
  while (Node->U_1.V_1.Kind == Tree_TreeName) {
    Idents_GetString(Node->U_1.V_29.TreeName.Name, &PathS);
    Strings_ArrayToString((STRING)".TS", 3L, &String);
    Strings_Concatenate(&PathS, &String);
    Strings_Append(&PathS, '\0');
    Strings_StringToArray(&PathS, PathA.A, 256L);
    Tree_f = IO_ReadOpen(PathA.A, 256L);
    if (Tree_f >= 0) {
      Strings_ReadL(Tree_f, &String);
      Node->U_1.V_29.TreeName.Name = Idents_MakeIdent(&String);
      Node->U_1.V_29.TreeName.Classes = Tree2_GetTree2(Tree_f);
      IO_ReadClose(Tree_f);
      if (Sets_IsElement(ORD('t'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Tree Definition: ", 17L);
        Idents_WriteIdent((System_tFile)IO_StdOutput, Node->U_1.V_29.TreeName.Name);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"----------------", 16L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        WriteClass(Node->U_1.V_29.TreeName.Classes);
        IO_WriteNl((System_tFile)IO_StdOutput);
      }
      if (Sets_IsElement(ORD('r'), &Tree_Options)) {
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Patterns: ", 10L);
        Idents_WriteIdent((System_tFile)IO_StdOutput, Node->U_1.V_29.TreeName.Name);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"---------", 9L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        Tree_ForallClasses(Node->U_1.V_29.TreeName.Classes, (Tree_ProcOfT)WritePattern);
        IO_WriteNl((System_tFile)IO_StdOutput);
      }
    } else {
      Node->U_1.V_29.TreeName.Classes = Tree_mNoClass();
      Scanner_ErrorI((STRING)"cannot read view file", 21L, Node->U_1.V_29.TreeName.Pos, Node->U_1.V_29.TreeName.Name);
    }
    Node = Node->U_1.V_29.TreeName.Next;
  }
  if (Sets_IsElement(ORD('3'), &Tree_Options)) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"puma data structure, before semantics:", 38L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    Tree_WriteTree((System_tFile)IO_StdOutput, Tree_TreeRoot);
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"End puma data structure.", 24L);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
  Semantics_Semantics(Tree_TreeRoot);
  if (Sets_IsElement(ORD('4'), &Tree_Options)) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"puma data structure, after semantics:", 37L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    Tree_WriteTree((System_tFile)IO_StdOutput, Tree_TreeRoot);
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"End puma data structure.", 24L);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
  Errors_WriteMessages((System_tFile)IO_StdError);
  if (Sets_IsElement(ORD('b'), &Tree_Options)) {
    Optimize_RuleProperties(Tree_TreeRoot);
  } else {
    Optimize_Optimize(Tree_TreeRoot);
  }
  if (Sets_IsElement(ORD('q'), &Tree_Options)) {
    Tree_QueryTree(Tree_TreeRoot);
  }
  if (Sets_IsElement(ORD('5'), &Tree_Options)) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"puma data structure, after optimize/RuleProperties:", 51L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    Tree_WriteTree((System_tFile)IO_StdOutput, Tree_TreeRoot);
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"End puma data structure.", 24L);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
  if (Tree_ErrorCount > 0) {
    IO_CloseIO();
    Exit(1L);
  }
  GenerateMacros();
  if (Sets_IsElement(ORD('d'), &Tree_Options)) {
    Idents_GetString(Tree_TreeRoot->U_1.V_26.Spec.TrafoName, &PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString(DefExtC, 2L, &String);
    } else if (Sets_IsElement(ORD('K'), &Tree_Options)) {
      Strings_ArrayToString(DefExtM3, 3L, &String);
    } else if (Sets_IsElement(ORD('A'), &Tree_Options)) {
      Strings_ArrayToString(DefExtAda, 4L, &String);
    } else {
      Strings_ArrayToString(DefExtMc, 3L, &String);
    }
    Strings_Concatenate(&PathS, &String);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      C_DefC(Tree_TreeRoot);
    } else if (Sets_IsElement(ORD('K'), &Tree_Options)) {
      M3_Interface(Tree_TreeRoot);
    } else if (Sets_IsElement(ORD('A'), &Tree_Options)) {
      Ada_PackSpec(Tree_TreeRoot);
    } else {
      M2_DefMod(Tree_TreeRoot);
    }
    SmartClose(PathS, Tree_f);
  }
  if (Sets_IsElement(ORD('i'), &Tree_Options)) {
    Idents_GetString(Tree_TreeRoot->U_1.V_26.Spec.TrafoName, &PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString(ImpExtC, 2L, &String);
    } else if (Sets_IsElement(ORD('K'), &Tree_Options)) {
      Strings_ArrayToString(ImpExtM3, 3L, &String);
    } else if (Sets_IsElement(ORD('A'), &Tree_Options)) {
      Strings_ArrayToString(ImpExtAda, 4L, &String);
    } else {
      Strings_ArrayToString(ImpExtMc, 3L, &String);
    }
    Strings_Concatenate(&PathS, &String);
    Strings_Assign(&TrafoFile, &PathS);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      C_ImplC(Tree_TreeRoot);
    } else if (Sets_IsElement(ORD('K'), &Tree_Options)) {
      M3_Module(Tree_TreeRoot);
    } else if (Sets_IsElement(ORD('A'), &Tree_Options)) {
      Ada_PackBody(Tree_TreeRoot);
    } else {
      M2_ImplMod(Tree_TreeRoot);
    }
    SmartClose(PathS, Tree_f);
    if (!Sets_IsElement(ORD('c'), &Tree_Options)) {
      if (Sets_IsElement(ORD('X'), &Tree_Options)) {
        Strings_Assign(&PathS, &PumaLib);
        Strings_ArrayToString((STRING)"gmdcp ", 6L, &String);
        Strings_Concatenate(&PathS, &String);
        Strings_Concatenate(&PathS, &TrafoFile);
        Strings_ArrayToString((STRING)" ", 1L, &String);
        Strings_Concatenate(&PathS, &String);
        Strings_Concatenate(&PathS, &TrafoFile);
        Strings_ArrayToString((STRING)".precpp", 7L, &String);
        Strings_Concatenate(&PathS, &String);
        Strings_StringToArray(&PathS, PathA.A, 256L);
        n = System(PathA.A, 256L);
      }
      Strings_Assign(&PathS, &PumaLib);
      Strings_ArrayToString((STRING)"gmdcpp ", 7L, &String);
      Strings_Concatenate(&PathS, &String);
      Strings_Concatenate(&PathS, &TrafoFile);
      Strings_Append(&PathS, '\0');
      Strings_StringToArray(&PathS, PathA.A, 256L);
      n = System(PathA.A, 256L);
      if (!Sets_IsElement(ORD('X'), &Tree_Options)) {
        Strings_Assign(&PathS, &PumaLib);
        Strings_ArrayToString((STRING)"gmdrm yy", 8L, &String);
        Strings_Concatenate(&PathS, &String);
        Idents_GetString(Tree_TreeRoot->U_1.V_26.Spec.TrafoName, &String);
        Strings_Concatenate(&PathS, &String);
        Strings_ArrayToString((STRING)".w", 2L, &String);
        Strings_Concatenate(&PathS, &String);
        Strings_Append(&PathS, '\0');
        Strings_StringToArray(&PathS, PathA.A, 256L);
        n = System(PathA.A, 256L);
      }
    }
  }
  if (Sets_IsElement(ORD('8'), &Tree_Options)) {
    IO_WriteNl((System_tFile)IO_StdError);
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Memory", 6L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)Memory_MemoryUsed, 8L);
    IO_WriteS((System_tFile)IO_StdError, (STRING)"  Heap", 6L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)Tree_HeapUsed, 8L);
    IO_WriteNl((System_tFile)IO_StdError);
  }
  IO_CloseIO();
  Exit(0L);
exit(0);
}
