#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Classes
#include "Classes.h"
#endif

#ifndef DEFINITION_Eval
#include "Eval.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Tree0
#include "Tree0.h"
#endif

#ifndef DEFINITION_Dfa
#include "Dfa.h"
#endif

#ifndef DEFINITION_GenTabs
#include "GenTabs.h"
#endif

#ifndef DEFINITION_ScanGen
#include "ScanGen.h"
#endif

static struct S_1 {
    CHAR A[127 + 1];
} Argument;
static Strings_tString FileNameS, Path;
static SHORTINT optimize;
static SHORTCARD i, j, n;
static BOOLEAN d, s, r, h, w, g, b;
static CHAR ch;


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
  Strings__init();
  IO__init();
  StdIO__init();
  Scanner__init();
  Parser__init();
  Errors__init();
  Classes__init();
  Eval__init();
  Tree__init();
  Tree0__init();
  Dfa__init();
  GenTabs__init();
  ScanGen__init();

  d = FALSE;
  s = FALSE;
  r = FALSE;
  h = FALSE;
  w = TRUE;
  g = FALSE;
  b = TRUE;
  optimize = 40;
  n = 0;
  ScanGen_Language = ScanGen_Modula;
  Strings_AssignEmpty(&ScanGen_RexLib);
  ScanGen_SourceFile.A[0] = '\0';
  {
    SHORTCARD B_1 = 1, B_2 = GetArgCount() - 1;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        GetArgument((LONGINT)i, Argument.A, 128L);
        if (Argument.A[0] == '-') {
          if (Argument.A[1] == 'l') {
            Strings_AssignEmpty(&ScanGen_RexLib);
            j = 2;
            for (;;) {
              ch = Argument.A[j];
              if (ch == '\0') {
                goto EXIT_1;
              }
              Strings_Append(&ScanGen_RexLib, ch);
              INC(j);
            } EXIT_1:;
            Strings_Append(&ScanGen_RexLib, '/');
          } else {
            j = 0;
            for (;;) {
              INC(j);
              ch = Argument.A[j];
              switch (ch) {
              case '\0':;
                goto EXIT_2;
                break;
              case '?':;
                h = TRUE;
                break;
              case 'h':;
                h = TRUE;
                break;
              case 'c':;
                ScanGen_Language = ScanGen_C;
                break;
              case 'm':;
                ScanGen_Language = ScanGen_Modula;
                break;
              case 'd':;
                d = TRUE;
                break;
              case 's':;
                s = TRUE;
                break;
              case 'r':;
                r = TRUE;
                break;
              case 'a':;
                d = TRUE;
                s = TRUE;
                break;
              case 'i':;
                Dfa_LastCh = ((CHAR)'\377');
                break;
              case 'o':;
                optimize = 16000;
                break;
              case 'n':;
                optimize = 0;
                break;
              case 'w':;
                w = FALSE;
                break;
              case 'g':;
                g = TRUE;
                break;
              case 'b':;
                b = FALSE;
                break;
              case '0':;
              case '1':;
              case '2':;
              case '3':;
              case '4':;
              case '5':;
              case '6':;
              case '7':;
              case '8':;
              case '9':;
                n = n * 10 + ORD(ch) - ORD('0');
                break;
              default :
                break;
              }
            } EXIT_2:;
          }
        } else if (Argument.A[0] == '?') {
          h = TRUE;
        } else {
          j = 0;
          do {
            ch = Argument.A[j];
            ScanGen_SourceFile.A[j] = ch;
            INC(j);
          } while (!(ch == '\0'));
        }
        if (i >= B_2) break;
      }
  }
  if (h) {
    StdIO_WriteS((STRING)"usage: rex [-options] [file]", 28L);
    StdIO_WriteNl();
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" a generate all (= -dsm)", 24L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" m generate a lexical analyzer in Modula (default)", 50L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" c generate a lexical analyzer in C", 35L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" d generate a definition module for the lexical analyzer", 56L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" s generate support modules:", 28L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)"   . a source module for input", 30L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)"   . a main program to be used as test driver", 45L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" r reduce number of generated case/switch labels", 48L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" i use ISO 8 bit code (default: ASCII 7 bit code)", 49L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" o optimize table size", 22L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" n do not optimize table size", 29L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" w suppress warnings", 20L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" g generate # line directives", 29L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" b do not partition character set into blocks", 45L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" 1 print statistics about the generated lexical analyzer", 56L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" h print help information", 25L);
    StdIO_WriteNl();
    StdIO_WriteS((STRING)" ldir specify the directory dir where rex finds its data files", 62L);
    StdIO_WriteNl();
  } else {
    Strings_ArrayToString(Scanner_ScanTabName.A, 128L, &FileNameS);
    Strings_Assign(&Path, &ScanGen_RexLib);
    Strings_Concatenate(&Path, &FileNameS);
    Strings_Append(&Path, '\0');
    Strings_StringToArray(&Path, Scanner_ScanTabName.A, 128L);
    Strings_ArrayToString(Parser_ParsTabName.A, 129L, &FileNameS);
    Strings_Assign(&Path, &ScanGen_RexLib);
    Strings_Concatenate(&Path, &FileNameS);
    Strings_Append(&Path, '\0');
    Strings_StringToArray(&Path, Parser_ParsTabName.A, 129L);
    Scanner_BeginScanner();
    if (ScanGen_SourceFile.A[0] != '\0') {
      Scanner_BeginFile(ScanGen_SourceFile.A, 128L);
    }
    if (Parser_Parser() == 0 && Errors_ErrorCount == 0) {
      if (n >= 17) {
        Tree0_WriteTree0((System_tFile)IO_StdOutput, Tree0_Tree0Root);
      }
      Eval_BeginEval();
      Classes_ComputeClasses(b);
      Eval_Eval(Tree0_Tree0Root);
      if (n >= 16) {
        Tree0_WriteTree0((System_tFile)IO_StdOutput, Tree0_Tree0Root);
      }
      GenTabs_LeafCount = GenTabs_StartStateCount + Tree0_Tree0Root->U_1.V_8.List.LeafCount;
      GenTabs_NodeCount = Tree0_Tree0Root->U_1.V_8.List.NodeCount;
      GenTabs_Root = Tree0_Tree0Root->U_1.V_8.List.Tree;
      Classes_ReleaseSetMem();
      Tree0_ReleaseTree0Module();
      if (n >= 15) {
        Tree_WriteTree(GenTabs_Root);
      }
      GenTabs_GenerateTables(n, r, w, optimize);
      ScanGen_GenerateScanner(r, w, g);
    } else {
      IO_CloseIO();
      Exit(1L);
    }
  }
  if (d) {
    ScanGen_GenerateInterface();
  }
  if (s) {
    ScanGen_GenerateSupport();
  }
  IO_CloseIO();
  Exit(0L);
exit(0);
}
