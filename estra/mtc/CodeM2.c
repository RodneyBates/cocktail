#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Environs
#include "Environs.h"
#endif

#ifndef DEFINITION_Grammar
#include "Grammar.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Match
#include "Match.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_CodeM2
#include "CodeM2.h"
#endif


static CHAR cNullDevice [] = "/dev/null";
static CHAR cDefPost [] = ".md";
static CHAR cImpPost [] = ".mi";
static CHAR cTabPost [] = ".tab";
#define cDefaultCost   1
#define BitsPerBitset   32
static IO_tFile Out;
static INTEGER BlaCo;
static Idents_tIdent GrammarName;
static void Definition ARGS((Tree_tTree t));
static void OpenDef ARGS((Idents_tIdent name));
struct S_1 {
    CHAR A[128 + 1];
};
static void Implementation ARGS((Tree_tTree t));
static void OpenImp ARGS((Idents_tIdent name));
struct S_2 {
    CHAR A[128 + 1];
};
static void Traverse ARGS((Tree_tTree t));
static void TraverseNodes ARGS((Tree_tTree t));
static BOOLEAN NumbersAlwaysMatch ARGS((Sets_tSet numbers, Idents_tIdent node));
static void SetClasses ARGS((Idents_tIdent node));
static void MatchPatterns ARGS((Tree_tTree t, Idents_tIdent node, Sets_tSet numbers));
static void MatchPattern ARGS((Tree_tTree cond, Idents_tIdent node, INTEGER number, INTEGER no));
static void MinCost ARGS((Tree_tTree t, Idents_tIdent node, Sets_tSet patnums));
static void CondMinPatCost ARGS((Tree_tTree t, Idents_tIdent name, BOOLEAN report, INTEGER number));
static void MinPatCost ARGS((Tree_tTree t, Idents_tIdent name, BOOLEAN report));
static void Functions ARGS((Tree_tTree t));
static void Directives ARGS((Tree_tTree t, Tree_tTree f));
static void WriteCode ARGS((Tree_tTree t, INTEGER no));
static void CloseFunction ARGS((Tree_tTree f, INTEGER n));
static void ErrorFunctions ARGS((Tree_tTree t));
static void ErrorFunction ARGS((Tree_tTree f));
static void Distributers ARGS((Tree_tTree t));
static void Distributer ARGS((Tree_tTree f));
static void CostFunctions ARGS((Tree_tTree t));
static void CostFunction ARGS((Tree_tTree f));
static void WritePart ARGS((Tree_tTree t));
static void BeginDo ARGS((Tree_tTree t));
static void BeginFunction ARGS((Tree_tTree f, INTEGER n));
static void Blanks ARGS(());


void CodeM2_MakeCodeM2
# ifdef __STDC__
()
# else
()
# endif
{
  GrammarName = Parser_AST->U_1.V_4.Spec.grna;
  if (ArgCheck_DEF) {
    Definition(Parser_AST);
  }
  if (ArgCheck_IMP) {
    Implementation(Parser_AST);
  }
}

static void Definition
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  {
    register Tree_ySpec *W_1 = &t->U_1.V_4.Spec;

    OpenDef(W_1->name);
    Blanks();
    IO_WriteS(Out, (STRING)"(*", 2L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	\"", 4L);
    Idents_WriteIdent(Out, W_1->name);
    IO_WriteS(Out, (STRING)".md\"", 4L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	generated with estra/", 24L);
    IO_WriteS(Out, ArgCheck_cVersion, 4L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	from \"", 9L);
    IO_WriteS(Out, ArgCheck_SourceFileName.A, 256L);
    IO_WriteS(Out, (STRING)"\"", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *", 2L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	estra ", 9L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	was written by Bertram Vielsack in june 1989", 47L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *", 2L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *)", 3L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"DEFINITION MODULE ", 18L);
    Idents_WriteIdent(Out, W_1->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"IMPORT ", 7L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    WritePart(W_1->export);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"VAR ", 4L);
      Idents_WriteIdent(Out, W_1->name);
      IO_WriteS(Out, (STRING)"TabName: ARRAY [0..127] OF CHAR;", 32L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE Begin", 15L);
    Idents_WriteIdent(Out, W_1->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    BeginDo(Parser_AST);
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE Close", 15L);
    Idents_WriteIdent(Out, W_1->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"END ", 4L);
    Idents_WriteIdent(Out, W_1->name);
    IO_WriteS(Out, (STRING)".", 1L);
    IO_WriteNl(Out);
    IO_WriteClose(Out);
  }
}

static void OpenDef
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  Strings_tString s;
  struct S_1 a;

  if (name == Scanner_NoIdent) {
    (void)strncpy((char *)a.A, (char *)cNullDevice, sizeof(a.A));
  } else {
    Idents_GetString(name, &s);
    Strings_Append(&s, '\0');
    Strings_StringToArray(&s, a.A, 129L);
    Character_Concatenate(a.A, 129L, cDefPost, 3L);
  }
  Out = IO_WriteOpen(a.A, 129L);
  Checks_CheckWriteOpen(&Out, a.A, 129L);
}

static void Implementation
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Sets_tSet Classes;
  Idents_tIdent class;
  Tree_tTree f, tt;
  INTEGER i;

  {
    register Tree_ySpec *W_2 = &t->U_1.V_4.Spec;

    OpenImp(W_2->name);
    Blanks();
    IO_WriteS(Out, (STRING)"(*", 2L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	\"", 4L);
    Idents_WriteIdent(Out, W_2->name);
    IO_WriteS(Out, (STRING)".mi\"", 4L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	generated with estra/", 24L);
    IO_WriteS(Out, ArgCheck_cVersion, 4L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	from \"", 9L);
    IO_WriteS(Out, ArgCheck_SourceFileName.A, 256L);
    IO_WriteS(Out, (STRING)"\"", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *", 2L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	estra ", 9L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *	was written by Bertram Vielsack in june 1989", 47L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *", 2L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)" *)", 3L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"IMPLEMENTATION MODULE ", 22L);
    Idents_WriteIdent(Out, W_2->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"IMPORT SYSTEM, IO, Memory, System, ", 35L);
      Idents_WriteIdent(Out, GrammarName);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
    } else {
      Blanks();
      IO_WriteS(Out, (STRING)"IMPORT SYSTEM, IO, Memory, ", 27L);
      Idents_WriteIdent(Out, GrammarName);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteNl(Out);
    if (ArgCheck_DEBUG) {
      Blanks();
      IO_WriteS(Out, (STRING)"IMPORT Times;", 13L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteNl(Out);
    }
    WritePart(W_2->global);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"CONST", 5L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyInfinite = ", 15L);
    IO_WriteI(Out, (MAX_LONGINT - Scanner_MaxValue) / Environs_MaxCalls(), 1L);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyBitsPerBitset = 32;", 23L);
    IO_WriteNl(Out);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"  yySetSize = ", 14L);
      IO_WriteI(Out, Environs_MaxDirective(), 1L);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  yyMaxIndex = ", 15L);
      IO_WriteI(Out, Match_MaxMatchIndex, 1L);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  yyCombSize = ", 15L);
      IO_WriteI(Out, Match_CombSize, 1L);
      IO_WriteS(Out, (STRING)";      ", 7L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  yyStartState = 0;", 19L);
      IO_WriteNl(Out);
    } else {
      Sets_MakeSet(&Classes, (Sets_tElement)Scanner_MaxIdent);
      Types_AllClasses(&Classes);
      while (!Sets_IsEmpty(Classes)) {
        class = Sets_Extract(&Classes);
        Blanks();
        IO_WriteS(Out, (STRING)"  yyC", 5L);
        Idents_WriteIdent(Out, class);
        IO_WriteS(Out, (STRING)" = ", 3L);
        IO_WriteI(Out, Types_ClassCode(class), 1L);
        IO_WriteS(Out, (STRING)";", 1L);
        IO_WriteNl(Out);
      }
      Sets_ReleaseSet(&Classes);
      Blanks();
      IO_WriteS(Out, (STRING)"  yyMaxClass = ", 15L);
      IO_WriteI(Out, Types_MaxClassCode(), 1L);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyPoolSize = 10240;", 21L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"TYPE", 4L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yytBlockPtr = POINTER TO yytBlock;", 36L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yytBlock =", 12L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  RECORD", 8L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    Successor: yytBlockPtr;", 27L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    Block: ARRAY [1..yyPoolSize] OF CHAR;", 41L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  END;", 6L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"  yyStateType = INTEGER;", 24L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  yySetType = ARRAY [0..yySetSize DIV yyBitsPerBitset] OF BITSET;", 65L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  yySetsType = ARRAY [0..yyMaxIndex] OF yySetType;", 50L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  yyCombType = ARRAY [0..yyCombSize] OF yyStateType;", 52L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteNl(Out);
    }
    f = W_2->functions;
    INC(BlaCo);
    while (f->U_1.V_1.Kind == Tree_Function) {
      {
        register Tree_yFunction *W_3 = &f->U_1.V_19.Function;

        Blanks();
        IO_WriteS(Out, (STRING)"yyP", 3L);
        Idents_WriteIdent(Out, W_3->name);
        IO_WriteS(Out, (STRING)" = PROCEDURE (", 14L);
        Idents_WriteIdent(Out, GrammarName);
        IO_WriteS(Out, (STRING)".t", 2L);
        Idents_WriteIdent(Out, GrammarName);
        tt = W_3->in;
        while (tt->U_1.V_1.Kind == Tree_Attribute) {
          {
            register Tree_yAttribute *W_4 = &tt->U_1.V_16.Attribute;

            IO_WriteS(Out, (STRING)", ", 2L);
            if (W_4->mod != Scanner_NoIdent) {
              Idents_WriteIdent(Out, W_4->mod);
              IO_WriteS(Out, (STRING)".", 1L);
            }
            Idents_WriteIdent(Out, W_4->type);
            tt = W_4->attributes;
          }
        }
        tt = W_3->out;
        while (tt->U_1.V_1.Kind == Tree_Attribute) {
          {
            register Tree_yAttribute *W_5 = &tt->U_1.V_16.Attribute;

            IO_WriteS(Out, (STRING)", VAR ", 6L);
            if (W_5->mod != Scanner_NoIdent) {
              Idents_WriteIdent(Out, W_5->mod);
              IO_WriteS(Out, (STRING)".", 1L);
            }
            Idents_WriteIdent(Out, W_5->type);
            IO_WriteS(Out, (STRING)" ", 1L);
            tt = W_5->attributes;
          }
        }
        tt = W_3->result;
        if (tt->U_1.V_1.Kind == Tree_Type) {
          {
            register Tree_yType *W_6 = &tt->U_1.V_22.Type;

            IO_WriteS(Out, (STRING)"): ", 3L);
            if (W_6->mod != Scanner_NoIdent) {
              Idents_WriteIdent(Out, W_6->mod);
              IO_WriteS(Out, (STRING)".", 1L);
            }
            Idents_WriteIdent(Out, W_6->type);
            IO_WriteS(Out, (STRING)";", 1L);
          }
        } else {
          IO_WriteS(Out, (STRING)");", 2L);
        }
        IO_WriteNl(Out);
        f = W_3->functions;
      }
    }
    Blanks();
    IO_WriteNl(Out);
    DEC(BlaCo);
    f = W_2->functions;
    Blanks();
    IO_WriteS(Out, (STRING)"  yyInfoPtr  = POINTER TO yyInfoType;", 37L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyInfoType =", 14L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    RECORD", 10L);
    IO_WriteNl(Out);
    if (!ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"      yyClasses: ARRAY [0..yyMaxClass DIV yyBitsPerBitset] OF BITSET;", 69L);
      IO_WriteNl(Out);
    }
    while (f->U_1.V_1.Kind == Tree_Function) {
      {
        register Tree_yFunction *W_7 = &f->U_1.V_19.Function;

        Blanks();
        IO_WriteS(Out, (STRING)"      ", 6L);
        Idents_WriteIdent(Out, W_7->name);
        IO_WriteS(Out, (STRING)": RECORD Cost: INTEGER; Proc: yyP", 33L);
        Idents_WriteIdent(Out, W_7->name);
        IO_WriteS(Out, (STRING)"; END;", 6L);
        IO_WriteNl(Out);
        f = W_7->functions;
      }
    }
    Blanks();
    IO_WriteS(Out, (STRING)"    END;", 8L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"VAR", 3L);
    IO_WriteNl(Out);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"  yySets: yySetsType;", 21L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  yyComb: yyCombType;", 21L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"  yyInfo: yyInfoType;", 21L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyMatch: ARRAY [0..", 21L);
    IO_WriteI(Out, Environs_MaxDirective(), 1L);
    IO_WriteS(Out, (STRING)"] OF BOOLEAN;", 13L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyBlockList: yytBlockPtr;", 27L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyPoolFreePtr, yyPoolEndPtr: SYSTEM.ADDRESS;", 46L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    if (ArgCheck_DEBUG) {
      Blanks();
      IO_WriteS(Out, (STRING)"  yyTime, yyTime0, yyNodeCount: LONGINT;", 40L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteNl(Out);
    }
    if (!ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"PROCEDURE yyClass (yyt: ", 24L);
      Idents_WriteIdent(Out, GrammarName);
      IO_WriteS(Out, (STRING)".t", 2L);
      Idents_WriteIdent(Out, GrammarName);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteS(Out, (STRING)"Bit, Set: INTEGER): BOOLEAN;", 28L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"VAR info: yyInfoPtr;", 20L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"BEGIN", 5L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  info := yyt^.yyHead.yyEstraInfo;", 34L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  RETURN Bit IN info^.yyClasses [Set];", 38L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"END yyClass;", 12L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE yyAlloc (): SYSTEM.ADDRESS;", 37L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"VAR BlockPtr: yytBlockPtr;", 26L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  IF LONGINT (yyPoolEndPtr - yyPoolFreePtr) < SYSTEM.TSIZE (yyInfoType) THEN", 76L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    BlockPtr  := yyBlockList;", 29L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    yyBlockList  := Memory.Alloc (SYSTEM.TSIZE (yytBlock));", 59L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    yyBlockList^.Successor := BlockPtr;", 39L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    yyPoolFreePtr := SYSTEM.ADR (yyBlockList^.Block);", 53L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    yyPoolEndPtr  := yyPoolFreePtr + yyPoolSize;", 48L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  END;", 6L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  INC (yyPoolFreePtr, SYSTEM.ADDRESS (SYSTEM.TSIZE (yyInfoType)));", 66L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  RETURN yyPoolFreePtr - SYSTEM.ADDRESS (SYSTEM.TSIZE (yyInfoType));", 68L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"END yyAlloc;", 12L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE yyReleaseHeap;", 24L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"VAR BlockPtr: yytBlockPtr;", 26L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  WHILE yyBlockList # NIL DO", 28L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    BlockPtr:= yyBlockList;", 27L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    yyBlockList:= yyBlockList^.Successor;", 41L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"    Memory.Free (SYSTEM.TSIZE (yytBlock), BlockPtr);", 52L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  END;", 6L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyPoolFreePtr:= NIL;", 22L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyPoolEndPtr:= NIL;", 21L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"END yyReleaseHeap;", 18L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    Distributers(W_2->functions);
    ErrorFunctions(W_2->functions);
    Functions(W_2->functions);
    CostFunctions(W_2->functions);
    Traverse(W_2->functions);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"PROCEDURE yyErrorCheck (i: INTEGER; s1, s2: ARRAY OF CHAR);", 59L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"BEGIN", 5L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  IF i < 0 THEN", 15L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"    IO.WriteS (IO.StdError, s1);", 32L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"    IO.WriteS (IO.StdError, s2);", 32L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"    IO.WriteNl (IO.StdError); IO.CloseIO; HALT;", 47L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  END;", 6L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"END yyErrorCheck;", 17L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE Begin", 15L);
    Idents_WriteIdent(Out, W_2->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"VAR yyf: System.tFile; yyi: INTEGER;", 36L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    INC(BlaCo);
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"yyf := System.OpenInput (", 25L);
      Idents_WriteIdent(Out, W_2->name);
      IO_WriteS(Out, (STRING)"TabName);", 9L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyErrorCheck (yyf, 'cannot open ', ", 35L);
      Idents_WriteIdent(Out, W_2->name);
      IO_WriteS(Out, (STRING)"TabName);", 9L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyi := System.Read (yyf, SYSTEM.ADR (yySets), SYSTEM.TSIZE (yySetsType));", 73L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyErrorCheck (yyi, 'cannot read ', ", 35L);
      Idents_WriteIdent(Out, W_2->name);
      IO_WriteS(Out, (STRING)"TabName);", 9L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyi := System.Read (yyf, SYSTEM.ADR (yyComb), SYSTEM.TSIZE (yyCombType));", 73L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyErrorCheck (yyi, 'cannot read ', ", 35L);
      Idents_WriteIdent(Out, W_2->name);
      IO_WriteS(Out, (STRING)"TabName);", 9L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"System.Close (yyf);", 19L);
      IO_WriteNl(Out);
    }
    DEC(BlaCo);
    WritePart(W_2->begin);
    Blanks();
    IO_WriteS(Out, (STRING)"END Begin", 9L);
    Idents_WriteIdent(Out, W_2->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    BeginDo(t);
    {
      register Tree_yFunction *W_8 = &t->U_1.V_4.Spec.functions->U_1.V_19.Function;

      if (W_8->result->U_1.V_1.Kind == Tree_Type) {
        {
          register Tree_yType *W_9 = &W_8->result->U_1.V_22.Type;

          Blanks();
          IO_WriteS(Out, (STRING)"VAR yyresult :", 14L);
          if (W_9->mod != Scanner_NoIdent) {
            Idents_WriteIdent(Out, W_9->mod);
            IO_WriteS(Out, (STRING)".", 1L);
          }
          Idents_WriteIdent(Out, W_9->type);
          IO_WriteS(Out, (STRING)";", 1L);
          IO_WriteNl(Out);
        }
      }
    }
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"VAR yystate: yyStateType;", 25L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    INC(BlaCo);
    if (ArgCheck_DEBUG) {
      Blanks();
      IO_WriteS(Out, (STRING)"yyTime0 := Times.CpuTime ();", 28L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyNodeCount := 0;", 17L);
      IO_WriteNl(Out);
    }
    if (ArgCheck_BU) {
      Blanks();
      IO_WriteS(Out, (STRING)"yystate := yyTraverse (yyt);", 28L);
      IO_WriteNl(Out);
    } else {
      Blanks();
      IO_WriteS(Out, (STRING)"yyTraverse (yyt);", 17L);
      IO_WriteNl(Out);
    }
    if (ArgCheck_DEBUG) {
      Blanks();
      IO_WriteS(Out, (STRING)"yyTime := Times.CpuTime ();", 27L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyTime := yyTime - yyTime0;", 27L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteI (IO.StdError, yyNodeCount, 1);", 40L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteS (IO.StdError, ' Nodes');", 34L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteNl (IO.StdError);", 25L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteI (IO.StdError, yyTime, 1);", 35L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteS (IO.StdError, ' msec to traverse');", 45L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteNl (IO.StdError);", 25L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IF yyTime > 0 THEN", 18L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  IO.WriteI (IO.StdError, (yyNodeCount * 1000 + yyTime DIV 2) DIV yyTime, 1);", 77L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  IO.WriteS (IO.StdError, ' Nodes per sec');", 44L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  IO.WriteNl (IO.StdError);", 27L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"  IO.WriteNl (IO.StdError);", 27L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"END;", 4L);
      IO_WriteNl(Out);
    }
    if (t->U_1.V_4.Spec.functions->U_1.V_1.Kind == Tree_Function) {
      {
        register Tree_yFunction *W_10 = &t->U_1.V_4.Spec.functions->U_1.V_19.Function;

        Blanks();
        if (W_10->result->U_1.V_1.Kind == Tree_Type) {
          IO_WriteS(Out, (STRING)"yyresult := ", 12L);
        }
        Idents_WriteIdent(Out, W_10->name);
        IO_WriteS(Out, (STRING)" (yyt", 5L);
        tt = W_10->in;
        while (tt->U_1.V_1.Kind == Tree_Attribute) {
          IO_WriteS(Out, (STRING)", ", 2L);
          Idents_WriteIdent(Out, tt->U_1.V_16.Attribute.ident);
          tt = tt->U_1.V_16.Attribute.attributes;
        }
        tt = W_10->out;
        while (tt->U_1.V_1.Kind == Tree_Attribute) {
          IO_WriteS(Out, (STRING)", ", 2L);
          Idents_WriteIdent(Out, tt->U_1.V_16.Attribute.ident);
          tt = tt->U_1.V_16.Attribute.attributes;
        }
        IO_WriteS(Out, (STRING)");", 2L);
        IO_WriteNl(Out);
      }
    }
    if (ArgCheck_DEBUG) {
      Blanks();
      IO_WriteS(Out, (STRING)"yyTime0 := Times.CpuTime ();", 28L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"yyReleaseHeap;", 14L);
    IO_WriteNl(Out);
    if (ArgCheck_DEBUG) {
      Blanks();
      IO_WriteS(Out, (STRING)"yyTime := Times.CpuTime ();", 27L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"yyTime := yyTime - yyTime0;", 27L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteI (IO.StdError, yyTime, 1);", 35L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteS (IO.StdError, ' msec to release Heap');", 49L);
      IO_WriteNl(Out);
      Blanks();
      IO_WriteS(Out, (STRING)"IO.WriteNl (IO.StdError);", 25L);
      IO_WriteNl(Out);
    }
    if (t->U_1.V_4.Spec.functions->U_1.V_19.Function.result->U_1.V_1.Kind == Tree_Type) {
      Blanks();
      IO_WriteS(Out, (STRING)"RETURN yyresult;", 16L);
      IO_WriteNl(Out);
    }
    DEC(BlaCo);
    Blanks();
    IO_WriteS(Out, (STRING)"END Do", 6L);
    Idents_WriteIdent(Out, t->U_1.V_4.Spec.name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE Close", 15L);
    Idents_WriteIdent(Out, W_2->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    WritePart(W_2->close);
    Blanks();
    IO_WriteS(Out, (STRING)"END Close", 9L);
    Idents_WriteIdent(Out, W_2->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
    f = W_2->functions;
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    INC(BlaCo);
    if (ArgCheck_BU) {
      Blanks();
      Idents_WriteIdent(Out, W_2->name);
      IO_WriteS(Out, (STRING)"TabName := '", 12L);
      Idents_WriteIdent(Out, W_2->name);
      IO_WriteS(Out, cTabPost, 4L);
      IO_WriteS(Out, (STRING)"';", 2L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteS(Out, (STRING)"WITH yyInfo DO", 14L);
    IO_WriteNl(Out);
    INC(BlaCo);
    if (!ArgCheck_BU) {
      {
        LONGINT B_1 = 0, B_2 = Types_MaxClassCode() / BitsPerBitset;

        if (B_1 <= B_2)
          for (i = B_1;; i += 1) {
            Blanks();
            IO_WriteS(Out, (STRING)"yyClasses [", 11L);
            IO_WriteI(Out, i, 1L);
            IO_WriteS(Out, (STRING)"] := {};", 8L);
            IO_WriteNl(Out);
            if (i >= B_2) break;
          }
      }
    }
    while (f->U_1.V_1.Kind == Tree_Function) {
      {
        register Tree_yFunction *W_11 = &f->U_1.V_19.Function;

        Blanks();
        Idents_WriteIdent(Out, W_11->name);
        IO_WriteS(Out, (STRING)".Cost := yyInfinite;", 20L);
        IO_WriteNl(Out);
        Blanks();
        Idents_WriteIdent(Out, W_11->name);
        IO_WriteS(Out, (STRING)".Proc := yyE", 12L);
        Idents_WriteIdent(Out, W_11->name);
        IO_WriteS(Out, (STRING)";", 1L);
        IO_WriteNl(Out);
        f = W_11->functions;
      }
    }
    DEC(BlaCo);
    Blanks();
    IO_WriteS(Out, (STRING)"END;", 4L);
    IO_WriteNl(Out);
    DEC(BlaCo);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyBlockList:= NIL;", 20L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyPoolFreePtr:= NIL;", 22L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  yyPoolEndPtr:= NIL;", 21L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"END ", 4L);
    Idents_WriteIdent(Out, W_2->name);
    IO_WriteS(Out, (STRING)".", 1L);
    IO_WriteNl(Out);
    IO_WriteClose(Out);
  }
}

static void OpenImp
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  Strings_tString s;
  struct S_2 a;

  if (name == Scanner_NoIdent) {
    (void)strncpy((char *)a.A, (char *)cNullDevice, sizeof(a.A));
  } else {
    Idents_GetString(name, &s);
    Strings_Append(&s, '\0');
    Strings_StringToArray(&s, a.A, 129L);
    Character_Concatenate(a.A, 129L, cImpPost, 3L);
  }
  Out = IO_WriteOpen(a.A, 129L);
  Checks_CheckWriteOpen(&Out, a.A, 129L);
}

static void Traverse
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (ArgCheck_BU) {
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE yyTraverse (yyt: ", 27L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)".t", 2L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)"): yyStateType;", 15L);
    IO_WriteNl(Out);
  } else {
    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE yyTraverse (yyt: ", 27L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)".t", 2L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)");", 2L);
    IO_WriteNl(Out);
  }
  Blanks();
  IO_WriteS(Out, (STRING)"VAR", 3L);
  IO_WriteNl(Out);
  INC(BlaCo);
  if (ArgCheck_BU) {
    Blanks();
    IO_WriteS(Out, (STRING)"state: yyStateType;", 19L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"match: POINTER TO yySetType;", 28L);
    IO_WriteNl(Out);
  }
  Blanks();
  IO_WriteS(Out, (STRING)"cost: INTEGER;", 14L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteS(Out, (STRING)"info: yyInfoPtr;", 16L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteS(Out, (STRING)"success: BOOLEAN;", 17L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteNl(Out);
  DEC(BlaCo);
  Blanks();
  IO_WriteS(Out, (STRING)"BEGIN", 5L);
  IO_WriteNl(Out);
  INC(BlaCo);
  if (ArgCheck_DEBUG) {
    Blanks();
    IO_WriteS(Out, (STRING)"INC (yyNodeCount);", 18L);
    IO_WriteNl(Out);
  }
  Blanks();
  IO_WriteS(Out, (STRING)"info := yyAlloc ();", 19L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteS(Out, (STRING)"info^ := yyInfo;", 16L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteS(Out, (STRING)"yyt^.yyHead.yyEstraInfo := info;", 32L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteNl(Out);
  Blanks();
  IO_WriteNl(Out);
  Blanks();
  IO_WriteS(Out, (STRING)"CASE yyt^.Kind OF", 17L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteNl(Out);
  TraverseNodes(t);
  Blanks();
  IO_WriteS(Out, (STRING)"END;", 4L);
  IO_WriteNl(Out);
  if (ArgCheck_BU) {
    Blanks();
    IO_WriteS(Out, (STRING)"RETURN state;", 13L);
    IO_WriteNl(Out);
  }
  DEC(BlaCo);
  Blanks();
  IO_WriteS(Out, (STRING)"END yyTraverse;", 15L);
  IO_WriteNl(Out);
  Blanks();
  IO_WriteNl(Out);
}

static void TraverseNodes
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Sets_tSet nodes;
  Idents_tIdent node, ident, class;
  INTEGER p;
  Sets_tSet numbers;

  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&numbers, (Sets_tElement)Environs_MaxDirective());
  Types_AllNodes(&nodes);
  while (!Sets_IsEmpty(nodes)) {
    node = Sets_Extract(&nodes);
    class = Grammar_MainClass(node);
    if (class != Scanner_NoIdent) {
      ident = Grammar_NodeIdent(node);
      Blanks();
      IO_WriteS(Out, (STRING)"| ", 2L);
      Idents_WriteIdent(Out, GrammarName);
      IO_WriteS(Out, (STRING)".", 1L);
      Idents_WriteIdent(Out, ident);
      IO_WriteS(Out, (STRING)":", 1L);
      IO_WriteNl(Out);
      INC1(BlaCo, 2);
      if (ArgCheck_BU) {
        Blanks();
        IO_WriteS(Out, (STRING)"state := ", 9L);
        IO_WriteI(Out, Automaton_StartIndex((LONGINT)node), 1L);
        IO_WriteS(Out, (STRING)";", 1L);
        IO_WriteNl(Out);
      }
      {
        LONGINT B_3 = 1, B_4 = Grammar_Arity(node);

        if (B_3 <= B_4)
          for (p = B_3;; p += 1) {
            Blanks();
            if (ArgCheck_BU) {
              IO_WriteS(Out, (STRING)"state := yyComb [state + ", 25L);
            }
            IO_WriteS(Out, (STRING)"yyTraverse (yyt^.", 17L);
            Idents_WriteIdent(Out, ident);
            IO_WriteS(Out, (STRING)".", 1L);
            Idents_WriteIdent(Out, Grammar_SonName(node, p));
            if (ArgCheck_BU) {
              IO_WriteS(Out, (STRING)")];", 3L);
            } else {
              IO_WriteS(Out, (STRING)");", 2L);
            }
            IO_WriteNl(Out);
            if (p >= B_4) break;
          }
      }
      Grammar_PatsOfNode(node, &numbers);
      if (ArgCheck_BU) {
        if (!NumbersAlwaysMatch(numbers, node)) {
          Blanks();
          IO_WriteS(Out, (STRING)"match := SYSTEM.ADR (yySets [state]);", 37L);
          IO_WriteNl(Out);
          Blanks();
          IO_WriteNl(Out);
        }
      } else {
        SetClasses(node);
      }
      MatchPatterns(t, node, numbers);
      MinCost(t, node, numbers);
      DEC1(BlaCo, 2);
    }
  }
  Sets_ReleaseSet(&numbers);
  Sets_ReleaseSet(&nodes);
}

static BOOLEAN NumbersAlwaysMatch
# ifdef __STDC__
(Sets_tSet numbers, Idents_tIdent node)
# else
(numbers, node)
Sets_tSet numbers;
Idents_tIdent node;
# endif
{
  Idents_tIdent i;

  {
    SHORTCARD B_5 = Sets_Minimum(&numbers), B_6 = Sets_Maximum(&numbers);

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        if (Sets_IsElement((Sets_tElement)i, &numbers) && !Environs_AlwaysMatch((LONGINT)i, node)) {
          return FALSE;
        }
        if (i >= B_6) break;
      }
  }
  return TRUE;
}

static void SetClasses
# ifdef __STDC__
(Idents_tIdent node)
# else
(node)
Idents_tIdent node;
# endif
{
  Sets_tSet classes, nodes;
  Idents_tIdent class;
  INTEGER arity, pos;
  Grammar_tLayout layout;

  Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Grammar_ClassesOfNode(node, &classes);
  while (!Sets_IsEmpty(classes)) {
    class = Sets_Extract(&classes);
    arity = Grammar_Arity(node);
    if (arity == 0 || class == Grammar_MainClass(node)) {
      for (;;) {
        Blanks();
        IO_WriteS(Out, (STRING)"INCL (info^.yyClasses [yyC", 26L);
        Idents_WriteIdent(Out, class);
        IO_WriteS(Out, (STRING)" DIV yyBitsPerBitset], ", 23L);
        IO_WriteS(Out, (STRING)"yyC", 3L);
        Idents_WriteIdent(Out, class);
        IO_WriteS(Out, (STRING)" MOD yyBitsPerBitset); ", 23L);
        IO_WriteNl(Out);
        class = Grammar_SuperClass(class);
        if (class == Scanner_NoIdent) {
          goto EXIT_1;
        }
        Grammar_NodesOfClass(class, &nodes);
        if (Sets_IsElement((Sets_tElement)node, &nodes)) {
          goto EXIT_1;
        }
      } EXIT_1:;
    } else {
      layout = Grammar_Layout(node, class);
      if (layout != NIL) {
        Blanks();
        IO_WriteS(Out, (STRING)"IF ", 3L);
        {
          LONGINT B_7 = 1, B_8 = arity;

          if (B_7 <= B_8)
            for (pos = B_7;; pos += 1) {
              if (pos != 1) {
                IO_WriteNl(Out);
                Blanks();
                IO_WriteS(Out, (STRING)" & ", 3L);
              }
              IO_WriteS(Out, (STRING)"yyClass (yyt^.", 14L);
              Idents_WriteIdent(Out, Grammar_NodeIdent(node));
              IO_WriteS(Out, (STRING)".", 1L);
              Idents_WriteIdent(Out, Grammar_SonName(node, pos));
              IO_WriteS(Out, (STRING)", ", 2L);
              IO_WriteS(Out, (STRING)"yyC", 3L);
              Idents_WriteIdent(Out, class);
              IO_WriteS(Out, (STRING)" MOD yyBitsPerBitset, yyC", 25L);
              Idents_WriteIdent(Out, class);
              IO_WriteS(Out, (STRING)" DIV yyBitsPerBitset) ", 22L);
              if (pos >= B_8) break;
            }
        }
        IO_WriteS(Out, (STRING)"THEN", 4L);
        IO_WriteNl(Out);
        INC(BlaCo);
        for (;;) {
          Blanks();
          IO_WriteS(Out, (STRING)"INCL (info^.yyClasses [yyC", 26L);
          Idents_WriteIdent(Out, class);
          IO_WriteS(Out, (STRING)" DIV yyBitsPerBitset], ", 23L);
          IO_WriteS(Out, (STRING)"yyC", 3L);
          Idents_WriteIdent(Out, class);
          IO_WriteS(Out, (STRING)" MOD yyBitsPerBitset);", 22L);
          IO_WriteNl(Out);
          class = Grammar_SuperClass(class);
          if (class == Scanner_NoIdent || class == Grammar_MainClass(node)) {
            goto EXIT_2;
          }
        } EXIT_2:;
        DEC(BlaCo);
        Blanks();
        IO_WriteS(Out, (STRING)"END;", 4L);
        IO_WriteNl(Out);
      }
    }
  }
  IO_WriteNl(Out);
  Sets_ReleaseSet(&nodes);
  Sets_ReleaseSet(&classes);
}

static void MatchPatterns
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent node, Sets_tSet numbers)
# else
(t, node, numbers)
Tree_tTree t;
Idents_tIdent node;
Sets_tSet numbers;
# endif
{
  Tree_tTree d;

  while (t->U_1.V_1.Kind == Tree_Function) {
    d = t->U_1.V_19.Function.directives;
    while (d->U_1.V_1.Kind == Tree_Directive) {
      {
        register Tree_yDirective *W_12 = &d->U_1.V_28.Directive;

        if (W_12->correct && Sets_IsElement((Sets_tElement)W_12->number, &numbers)) {
          if (Environs_HasCondition(W_12->number) || !Environs_AlwaysMatch(W_12->number, node)) {
            MatchPattern(W_12->condition, node, W_12->number, W_12->number);
          }
        }
        d = W_12->directives;
      }
    }
    t = t->U_1.V_19.Function.functions;
  }
  IO_WriteNl(Out);
}

static void MatchPattern
# ifdef __STDC__
(Tree_tTree cond, Idents_tIdent node, INTEGER number, INTEGER no)
# else
(cond, node, number, no)
Tree_tTree cond;
Idents_tIdent node;
INTEGER number;
INTEGER no;
# endif
{
  BOOLEAN started;

  Blanks();
  IO_WriteS(Out, (STRING)"yyMatch [", 9L);
  IO_WriteI(Out, number, 1L);
  IO_WriteS(Out, (STRING)"] := ", 5L);
  if (Environs_AlwaysMatch(no, node)) {
    IO_WriteS(Out, (STRING)"TRUE", 4L);
  } else {
    if (ArgCheck_BU) {
      IO_WriteS(Out, (STRING)"(", 1L);
      IO_WriteI(Out, number % BitsPerBitset, 1L);
      IO_WriteS(Out, (STRING)" IN match^[", 11L);
      IO_WriteI(Out, number / BitsPerBitset, 1L);
      IO_WriteS(Out, (STRING)"])", 2L);
    } else {
      Environs_WriteMatch(Out, no, BlaCo, GrammarName);
    }
  }
  if (cond->U_1.V_1.Kind == Tree_CondF) {
    if (!ArgCheck_BU) {
      IO_WriteNl(Out);
      Blanks();
    }
    IO_WriteS(Out, (STRING)" & (", 4L);
    WriteCode(cond->U_1.V_37.CondF.code, no);
    IO_WriteS(Out, (STRING)")", 1L);
  }
  IO_WriteS(Out, (STRING)";", 1L);
  IO_WriteNl(Out);
}

static void MinCost
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent node, Sets_tSet patnums)
# else
(t, node, patnums)
Tree_tTree t;
Idents_tIdent node;
Sets_tSet patnums;
# endif
{
  Tree_tTree tt, d;
  Sets_tSet numbers;
  BOOLEAN report;

  report = FALSE;
  Sets_MakeSet(&numbers, (Sets_tElement)Environs_MaxDirective());
  Sets_Assign(&numbers, patnums);
  tt = t;
  while (tt->U_1.V_1.Kind == Tree_Function) {
    d = tt->U_1.V_19.Function.directives;
    while (d->U_1.V_1.Kind == Tree_Directive) {
      {
        register Tree_yDirective *W_13 = &d->U_1.V_28.Directive;

        if (W_13->correct && Sets_IsElement((Sets_tElement)W_13->number, &numbers) && !W_13->iter) {
          Sets_Exclude(&numbers, (Sets_tElement)W_13->number);
          if (Environs_HasCondition(W_13->number) || !Environs_AlwaysMatch(W_13->number, node)) {
            CondMinPatCost(d, tt->U_1.V_19.Function.name, report, W_13->number);
          } else {
            MinPatCost(d, tt->U_1.V_19.Function.name, report);
          }
          Blanks();
          IO_WriteNl(Out);
        }
        d = W_13->directives;
      }
    }
    tt = tt->U_1.V_19.Function.functions;
  }
  if (!Sets_IsEmpty(numbers)) {
    if (Sets_Card(&numbers) > 1) {
      Blanks();
      IO_WriteS(Out, (STRING)"REPEAT", 6L);
      IO_WriteNl(Out);
      INC(BlaCo);
      report = TRUE;
      Blanks();
      IO_WriteS(Out, (STRING)"success := FALSE;", 17L);
      IO_WriteNl(Out);
    }
    while (t->U_1.V_1.Kind == Tree_Function) {
      d = t->U_1.V_19.Function.directives;
      while (d->U_1.V_1.Kind == Tree_Directive) {
        {
          register Tree_yDirective *W_14 = &d->U_1.V_28.Directive;

          if (W_14->correct && Sets_IsElement((Sets_tElement)W_14->number, &numbers) && W_14->iter) {
            if (Environs_HasCondition(W_14->number) || !Environs_AlwaysMatch(W_14->number, node)) {
              CondMinPatCost(d, t->U_1.V_19.Function.name, report, W_14->number);
            } else {
              MinPatCost(d, t->U_1.V_19.Function.name, report);
            }
            Blanks();
            IO_WriteNl(Out);
          }
          d = W_14->directives;
        }
      }
      t = t->U_1.V_19.Function.functions;
    }
    if (Sets_Card(&numbers) > 1) {
      DEC(BlaCo);
      Blanks();
      IO_WriteS(Out, (STRING)"UNTIL NOT success;", 18L);
      IO_WriteNl(Out);
    }
  }
  Sets_ReleaseSet(&numbers);
}

static void CondMinPatCost
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent name, BOOLEAN report, INTEGER number)
# else
(t, name, report, number)
Tree_tTree t;
Idents_tIdent name;
BOOLEAN report;
INTEGER number;
# endif
{
  Blanks();
  IO_WriteS(Out, (STRING)"IF yyMatch [", 12L);
  IO_WriteI(Out, number, 1L);
  IO_WriteS(Out, (STRING)"] THEN", 6L);
  IO_WriteNl(Out);
  INC(BlaCo);
  MinPatCost(t, name, report);
  DEC(BlaCo);
  Blanks();
  IO_WriteS(Out, (STRING)"END;", 4L);
  IO_WriteNl(Out);
}

static void MinPatCost
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent name, BOOLEAN report)
# else
(t, name, report)
Tree_tTree t;
Idents_tIdent name;
BOOLEAN report;
# endif
{
  {
    register Tree_yDirective *W_15 = &t->U_1.V_28.Directive;

    Blanks();
    IO_WriteS(Out, (STRING)"cost := ", 8L);
    switch (W_15->costs->U_1.V_1.Kind) {
    case Tree_CostD:;
      IO_WriteI(Out, (LONGINT)cDefaultCost, 1L);
      Environs_WriteCost(Out, W_15->number, BlaCo);
      break;
    case Tree_CostN:;
      IO_WriteI(Out, W_15->costs->U_1.V_40.CostN.value, 1L);
      Environs_WriteCost(Out, W_15->number, BlaCo);
      break;
    case Tree_CostF:;
      WriteCode(W_15->costs->U_1.V_41.CostF.code, W_15->number);
      break;
    }
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"IF cost < info^.", 16L);
    Idents_WriteIdent(Out, name);
    IO_WriteS(Out, (STRING)".Cost THEN", 10L);
    IO_WriteNl(Out);
    INC(BlaCo);
    Blanks();
    IO_WriteS(Out, (STRING)"info^.", 6L);
    Idents_WriteIdent(Out, name);
    IO_WriteS(Out, (STRING)".Cost := cost;", 14L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"info^.", 6L);
    Idents_WriteIdent(Out, name);
    IO_WriteS(Out, (STRING)".Proc := yyF", 12L);
    IO_WriteI(Out, W_15->number, 1L);
    Idents_WriteIdent(Out, name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    if (report) {
      Blanks();
      IO_WriteS(Out, (STRING)"success := TRUE;", 16L);
      IO_WriteNl(Out);
    }
    DEC(BlaCo);
    Blanks();
    IO_WriteS(Out, (STRING)"END;", 4L);
    IO_WriteNl(Out);
  }
}

static void Functions
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_16 = &t->U_1.V_19.Function;

      Directives(W_16->directives, t);
      t = W_16->functions;
    }
  }
}

static void Directives
# ifdef __STDC__
(Tree_tTree t, Tree_tTree f)
# else
(t, f)
Tree_tTree t;
Tree_tTree f;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Directive) {
    {
      register Tree_yDirective *W_17 = &t->U_1.V_28.Directive;

      if (W_17->correct) {
        BeginFunction(f, W_17->number);
        WritePart(W_17->decl);
        Blanks();
        IO_WriteS(Out, (STRING)"BEGIN", 5L);
        WriteCode(W_17->instr, W_17->number);
        IO_WriteNl(Out);
        CloseFunction(f, W_17->number);
      }
      t = W_17->directives;
    }
  }
}

static void WriteCode
# ifdef __STDC__
(Tree_tTree t, INTEGER no)
# else
(t, no)
Tree_tTree t;
INTEGER no;
# endif
{
  if (t->U_1.V_1.Kind != Tree_CdEnd) {
    Blanks();
    IO_WriteS(Out, (STRING)"    (* line ", 12L);
    IO_WriteI(Out, (LONGINT)t->U_1.V_42.code.pos.Line, 1L);
    IO_WriteS(Out, (STRING)" ", 1L);
    IO_WriteS(Out, ArgCheck_SourceFileName.A, 256L);
    IO_WriteS(Out, (STRING)" *)", 3L);
    IO_WriteNl(Out);
  }
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdStr:;
      switch (t->U_1.V_43.CdStr.mode) {
      case Tree_cNoSel:;
        Idents_WriteIdent(Out, t->U_1.V_43.CdStr.ident);
        break;
      case Tree_cSel:;
        Environs_WriteAccess(Out, no, t->U_1.V_43.CdStr.ident);
        break;
      case Tree_cTreeSel:;
        Environs_WritePath(Out, no, t->U_1.V_43.CdStr.ident);
        break;
      }
      t = t->U_1.V_43.CdStr.code;
      break;
    case Tree_CdId:;
      switch (t->U_1.V_44.CdId.mode) {
      case Tree_cNoSel:;
        Idents_WriteIdent(Out, t->U_1.V_44.CdId.ident);
        break;
      case Tree_cSel:;
        Environs_WriteAccess(Out, no, t->U_1.V_44.CdId.ident);
        break;
      case Tree_cTreeSel:;
        Environs_WritePath(Out, no, t->U_1.V_44.CdId.ident);
        break;
      }
      t = t->U_1.V_44.CdId.code;
      break;
    case Tree_CdDot:;
      IO_WriteS(Out, (STRING)".", 1L);
      t = t->U_1.V_45.CdDot.code;
      break;
    case Tree_CdComma:;
      IO_WriteS(Out, (STRING)",", 1L);
      t = t->U_1.V_45.CdDot.code;
      break;
    case Tree_CdLPar:;
      IO_WriteS(Out, (STRING)"(", 1L);
      t = t->U_1.V_47.CdLPar.code;
      break;
    case Tree_CdRPar:;
      IO_WriteS(Out, (STRING)")", 1L);
      t = t->U_1.V_48.CdRPar.code;
      break;
    case Tree_CdLBra:;
      IO_WriteS(Out, (STRING)"{", 1L);
      t = t->U_1.V_49.CdLBra.code;
      break;
    case Tree_CdRBra:;
      IO_WriteS(Out, (STRING)"}", 1L);
      t = t->U_1.V_50.CdRBra.code;
      break;
    case Tree_CdSpa:;
      StringMem_WriteString(Out, t->U_1.V_51.CdSpa.ref);
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      StringMem_WriteString(Out, t->U_1.V_52.CdCom.ref);
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdRst:;
      StringMem_WriteString(Out, t->U_1.V_53.CdRst.ref);
      t = t->U_1.V_53.CdRst.code;
      break;
    case Tree_CdEnd:;
      goto EXIT_3;
      break;
    }
  } EXIT_3:;
}

static void CloseFunction
# ifdef __STDC__
(Tree_tTree f, INTEGER n)
# else
(f, n)
Tree_tTree f;
INTEGER n;
# endif
{
  {
    register Tree_yFunction *W_18 = &f->U_1.V_19.Function;

    if (n > 0) {
      Blanks();
      IO_WriteS(Out, (STRING)"END yyF", 7L);
      IO_WriteI(Out, n, 1L);
      Idents_WriteIdent(Out, W_18->name);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
    } else if (n == -1) {
      Blanks();
      IO_WriteS(Out, (STRING)"END yyE", 7L);
      Idents_WriteIdent(Out, W_18->name);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
    } else {
      Blanks();
      IO_WriteS(Out, (STRING)"END ", 4L);
      Idents_WriteIdent(Out, W_18->name);
      IO_WriteS(Out, (STRING)";", 1L);
      IO_WriteNl(Out);
    }
    Blanks();
    IO_WriteNl(Out);
  }
}

static void ErrorFunctions
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_19 = &t->U_1.V_19.Function;

      ErrorFunction(t);
      t = W_19->functions;
    }
  }
}

static void ErrorFunction
# ifdef __STDC__
(Tree_tTree f)
# else
(f)
Tree_tTree f;
# endif
{
  {
    register Tree_yFunction *W_20 = &f->U_1.V_19.Function;

    BeginFunction(f, -1L);
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    INC(BlaCo);
    Blanks();
    IO_WriteS(Out, (STRING)"IO.WriteS (IO.StdError, 'Function ", 34L);
    Idents_WriteIdent(Out, W_20->name);
    IO_WriteS(Out, (STRING)" is not defined for this tree');", 32L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"IO.WriteNl (IO.StdError); IO.CloseIO; HALT;", 43L);
    IO_WriteNl(Out);
    DEC(BlaCo);
    CloseFunction(f, -1L);
  }
}

static void Distributers
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_21 = &t->U_1.V_19.Function;

      Distributer(t);
      t = W_21->functions;
    }
  }
}

static void Distributer
# ifdef __STDC__
(Tree_tTree f)
# else
(f)
Tree_tTree f;
# endif
{
  Tree_tTree tt;

  {
    register Tree_yFunction *W_22 = &f->U_1.V_19.Function;

    BeginFunction(f, 0L);
    Blanks();
    IO_WriteS(Out, (STRING)"VAR InfoPtr: yyInfoPtr;", 23L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    INC(BlaCo);
    Blanks();
    IO_WriteS(Out, (STRING)"InfoPtr := yyInfoPtr (yyt^.yyHead.yyEstraInfo);", 47L);
    IO_WriteNl(Out);
    Blanks();
    if (W_22->result->U_1.V_1.Kind == Tree_Type) {
      IO_WriteS(Out, (STRING)"RETURN ", 7L);
    }
    IO_WriteS(Out, (STRING)"InfoPtr^.", 9L);
    Idents_WriteIdent(Out, W_22->name);
    IO_WriteS(Out, (STRING)".Proc (yyt", 10L);
    tt = W_22->in;
    while (tt->U_1.V_1.Kind == Tree_Attribute) {
      IO_WriteS(Out, (STRING)", ", 2L);
      Idents_WriteIdent(Out, tt->U_1.V_16.Attribute.ident);
      tt = tt->U_1.V_16.Attribute.attributes;
    }
    tt = W_22->out;
    while (tt->U_1.V_1.Kind == Tree_Attribute) {
      IO_WriteS(Out, (STRING)", ", 2L);
      Idents_WriteIdent(Out, tt->U_1.V_16.Attribute.ident);
      tt = tt->U_1.V_16.Attribute.attributes;
    }
    IO_WriteS(Out, (STRING)");", 2L);
    IO_WriteNl(Out);
    DEC(BlaCo);
    CloseFunction(f, 0L);
  }
}

static void CostFunctions
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  while (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_23 = &t->U_1.V_19.Function;

      CostFunction(t);
      t = W_23->functions;
    }
  }
}

static void CostFunction
# ifdef __STDC__
(Tree_tTree f)
# else
(f)
Tree_tTree f;
# endif
{
  {
    register Tree_yFunction *W_24 = &f->U_1.V_19.Function;

    Blanks();
    IO_WriteS(Out, (STRING)"PROCEDURE Cost", 14L);
    Idents_WriteIdent(Out, W_24->name);
    IO_WriteS(Out, (STRING)" (yyt: ", 7L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)".t", 2L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)"): INTEGER;", 11L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"VAR", 3L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  InfoPtr: yyInfoPtr;", 21L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"BEGIN", 5L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  InfoPtr := yyt^.yyHead.yyEstraInfo;", 37L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"  RETURN InfoPtr^.", 18L);
    Idents_WriteIdent(Out, W_24->name);
    IO_WriteS(Out, (STRING)".Cost;", 6L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteS(Out, (STRING)"END Cost", 8L);
    Idents_WriteIdent(Out, W_24->name);
    IO_WriteS(Out, (STRING)";", 1L);
    IO_WriteNl(Out);
    Blanks();
    IO_WriteNl(Out);
  }
}

static void WritePart
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (t->U_1.V_1.Kind != Tree_CdEnd) {
    Blanks();
    IO_WriteS(Out, (STRING)"    (* line ", 12L);
    IO_WriteI(Out, (LONGINT)t->U_1.V_42.code.pos.Line, 1L);
    IO_WriteS(Out, (STRING)" ", 1L);
    IO_WriteS(Out, ArgCheck_SourceFileName.A, 256L);
    IO_WriteS(Out, (STRING)" *)", 3L);
    IO_WriteNl(Out);
  }
  for (;;) {
    switch (t->U_1.V_1.Kind) {
    case Tree_CdStr:;
      Idents_WriteIdent(Out, t->U_1.V_43.CdStr.ident);
      t = t->U_1.V_43.CdStr.code;
      break;
    case Tree_CdId:;
      Idents_WriteIdent(Out, t->U_1.V_44.CdId.ident);
      t = t->U_1.V_44.CdId.code;
      break;
    case Tree_CdDot:;
      IO_WriteS(Out, (STRING)".", 1L);
      t = t->U_1.V_45.CdDot.code;
      break;
    case Tree_CdComma:;
      IO_WriteS(Out, (STRING)",", 1L);
      t = t->U_1.V_46.CdComma.code;
      break;
    case Tree_CdLPar:;
      IO_WriteS(Out, (STRING)"(", 1L);
      t = t->U_1.V_47.CdLPar.code;
      break;
    case Tree_CdRPar:;
      IO_WriteS(Out, (STRING)")", 1L);
      t = t->U_1.V_48.CdRPar.code;
      break;
    case Tree_CdLBra:;
      IO_WriteS(Out, (STRING)"{", 1L);
      t = t->U_1.V_49.CdLBra.code;
      break;
    case Tree_CdRBra:;
      IO_WriteS(Out, (STRING)"}", 1L);
      t = t->U_1.V_50.CdRBra.code;
      break;
    case Tree_CdSpa:;
      StringMem_WriteString(Out, t->U_1.V_51.CdSpa.ref);
      t = t->U_1.V_51.CdSpa.code;
      break;
    case Tree_CdCom:;
      StringMem_WriteString(Out, t->U_1.V_52.CdCom.ref);
      t = t->U_1.V_52.CdCom.code;
      break;
    case Tree_CdRst:;
      StringMem_WriteString(Out, t->U_1.V_53.CdRst.ref);
      t = t->U_1.V_53.CdRst.code;
      break;
    case Tree_CdEnd:;
      IO_WriteNl(Out);
      goto EXIT_4;
      break;
    }
  } EXIT_4:;
}

static void BeginDo
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Tree_tTree tt;

  Blanks();
  IO_WriteS(Out, (STRING)"PROCEDURE Do", 12L);
  Idents_WriteIdent(Out, t->U_1.V_4.Spec.name);
  IO_WriteS(Out, (STRING)" (yyt: ", 7L);
  Idents_WriteIdent(Out, GrammarName);
  IO_WriteS(Out, (STRING)".t", 2L);
  Idents_WriteIdent(Out, GrammarName);
  if (t->U_1.V_4.Spec.functions->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_25 = &t->U_1.V_4.Spec.functions->U_1.V_19.Function;

      tt = W_25->in;
      while (tt->U_1.V_1.Kind == Tree_Attribute) {
        {
          register Tree_yAttribute *W_26 = &tt->U_1.V_16.Attribute;

          IO_WriteS(Out, (STRING)";", 1L);
          Idents_WriteIdent(Out, W_26->ident);
          IO_WriteS(Out, (STRING)":", 1L);
          if (W_26->mod != Scanner_NoIdent) {
            Idents_WriteIdent(Out, W_26->mod);
            IO_WriteS(Out, (STRING)".", 1L);
          }
          Idents_WriteIdent(Out, W_26->type);
          tt = W_26->attributes;
        }
      }
      tt = W_25->out;
      while (tt->U_1.V_1.Kind == Tree_Attribute) {
        {
          register Tree_yAttribute *W_27 = &tt->U_1.V_16.Attribute;

          IO_WriteS(Out, (STRING)"; VAR ", 6L);
          Idents_WriteIdent(Out, W_27->ident);
          IO_WriteS(Out, (STRING)":", 1L);
          IO_WriteNl(Out);
          if (W_27->mod != Scanner_NoIdent) {
            Blanks();
            Idents_WriteIdent(Out, W_27->mod);
            IO_WriteS(Out, (STRING)".", 1L);
          }
          Idents_WriteIdent(Out, W_27->type);
          tt = W_27->attributes;
        }
      }
      tt = W_25->result;
      if (tt->U_1.V_1.Kind == Tree_Type) {
        {
          register Tree_yType *W_28 = &tt->U_1.V_22.Type;

          IO_WriteS(Out, (STRING)"): ", 3L);
          if (W_28->mod != Scanner_NoIdent) {
            Idents_WriteIdent(Out, W_28->mod);
            IO_WriteS(Out, (STRING)".", 1L);
          }
          Idents_WriteIdent(Out, W_28->type);
          IO_WriteS(Out, (STRING)";", 1L);
        }
      } else {
        IO_WriteS(Out, (STRING)");", 2L);
      }
      IO_WriteNl(Out);
    }
  }
}

static void BeginFunction
# ifdef __STDC__
(Tree_tTree f, INTEGER n)
# else
(f, n)
Tree_tTree f;
INTEGER n;
# endif
{
  Tree_tTree tt;

  {
    register Tree_yFunction *W_29 = &f->U_1.V_19.Function;

    IO_WriteS(Out, (STRING)"PROCEDURE ", 10L);
    if (n > 0) {
      IO_WriteS(Out, (STRING)"yyF", 3L);
      IO_WriteI(Out, n, 1L);
    } else if (n == -1) {
      IO_WriteS(Out, (STRING)"yyE", 3L);
    }
    Idents_WriteIdent(Out, W_29->name);
    Blanks();
    IO_WriteS(Out, (STRING)" (yyt: ", 7L);
    Idents_WriteIdent(Out, GrammarName);
    IO_WriteS(Out, (STRING)".t", 2L);
    Idents_WriteIdent(Out, GrammarName);
    tt = W_29->in;
    while (tt->U_1.V_1.Kind == Tree_Attribute) {
      {
        register Tree_yAttribute *W_30 = &tt->U_1.V_16.Attribute;

        IO_WriteS(Out, (STRING)";", 1L);
        Idents_WriteIdent(Out, W_30->ident);
        IO_WriteS(Out, (STRING)":", 1L);
        if (W_30->mod != Scanner_NoIdent) {
          Idents_WriteIdent(Out, W_30->mod);
          IO_WriteS(Out, (STRING)".", 1L);
        }
        Idents_WriteIdent(Out, W_30->type);
        tt = W_30->attributes;
      }
    }
    tt = W_29->out;
    while (tt->U_1.V_1.Kind == Tree_Attribute) {
      {
        register Tree_yAttribute *W_31 = &tt->U_1.V_16.Attribute;

        IO_WriteS(Out, (STRING)"; VAR ", 6L);
        Idents_WriteIdent(Out, W_31->ident);
        IO_WriteS(Out, (STRING)":", 1L);
        IO_WriteNl(Out);
        if (W_31->mod != Scanner_NoIdent) {
          Blanks();
          Idents_WriteIdent(Out, W_31->mod);
          IO_WriteS(Out, (STRING)".", 1L);
        }
        Idents_WriteIdent(Out, W_31->type);
        tt = W_31->attributes;
      }
    }
    tt = W_29->result;
    if (tt->U_1.V_1.Kind == Tree_Type) {
      {
        register Tree_yType *W_32 = &tt->U_1.V_22.Type;

        IO_WriteS(Out, (STRING)"): ", 3L);
        if (W_32->mod != Scanner_NoIdent) {
          Idents_WriteIdent(Out, W_32->mod);
          IO_WriteS(Out, (STRING)".", 1L);
        }
        Idents_WriteIdent(Out, W_32->type);
        IO_WriteS(Out, (STRING)";", 1L);
      }
    } else {
      IO_WriteS(Out, (STRING)");", 2L);
    }
    IO_WriteNl(Out);
  }
}

static void Blanks
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER i;

  {
    LONGINT B_9 = 1, B_10 = BlaCo;

    if (B_9 <= B_10)
      for (i = B_9;; i += 1) {
        IO_WriteS(Out, (STRING)"  ", 2L);
        if (i >= B_10) break;
      }
  }
}

void CodeM2__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    ArgCheck__init();
    Automaton__init();
    Checks__init();
    Character__init();
    Environs__init();
    Grammar__init();
    Idents__init();
    IO__init();
    Match__init();
    Parser__init();
    Scanner__init();
    Sets__init();
    StringMem__init();
    Strings__init();
    Tree__init();
    Types__init();
    ArgCheck__init();

    BlaCo = 0;
  }
}
