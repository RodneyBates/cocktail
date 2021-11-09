#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Convert
#include "Convert.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Environs
#include "Environs.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_Grammar
#include "Grammar.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Stack
#include "Stack.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif

#ifndef DEFINITION_Queues
#include "Queues.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_StdIO
#include "StdIO.h"
#endif

#ifndef DEFINITION_Match
#include "Match.h"
#endif

INTEGER Match_MaxMatchIndex, Match_CombSize;

static CHAR cTabPost [] = ".tab";
#define InitPatternTableSize   100
#define InitMatchSetTableSize   100
#define NoIndex   -1
#define BitsPerBitset   32
typedef struct S_1 {
    Patterns_tPattern Pat;
    Sets_tSet Numbers;
    struct S_3 {
        INTEGER A[100 + 1];
    } *SonNumbers;
} tPatternTableEntry;
typedef struct S_2 {
    Sets_tSet Set;
} tMatchSetTableEntry;
static struct S_4 {
    tPatternTableEntry A[1000 + 1];
} *PatternTable;
static LONGINT PatternTableSize, PatternTableCount;
static struct S_5 {
    tMatchSetTableEntry A[1000 + 1];
} *MatchSetTable;
static LONGINT MatchSetTableSize, MatchSetTableCount;
static struct S_6 {
    Sets_tSet A[100 + 1];
} *SonMatchSets;
static struct S_7 {
    INTEGER A[1000 + 1];
} *ClassToPattern;
static LONGINT mIndex;
static INTEGER PutPattern ARGS((Patterns_tPattern pat, INTEGER no));
static BOOLEAN Defined ARGS((Patterns_tPattern pat));
static void CollectPatterns ARGS(());
static void CollectSubPatterns ARGS(());
static void PutMatchSet ARGS((Sets_tSet set));
static INTEGER MatchSetIndex ARGS((Sets_tSet set));
static BOOLEAN InMatchSet ARGS((INTEGER elmt, INTEGER set));
static void MakeMatchSets ARGS(());
static void SynthesizeMatchSets ARGS((LONGINT last, Sets_tSet *set));
static void OutputMatchSets ARGS((System_tFile f));
static void MakeMatchTables ARGS(());
static void MakeMatchTable ARGS((Idents_tIdent node));
static void DefineSonMatchSets ARGS((INTEGER pos, INTEGER arity, Grammar_tLayout layout));
static void DefineMatchTable ARGS((Idents_tIdent node, Sets_tSet set, INTEGER pos, INTEGER arity, Queues_tQueue *indexes, Grammar_tLayout layout));
static void DefineEntry ARGS((Idents_tIdent node, Queues_tQueue *indexes, Sets_tSet set));
static BOOLEAN MatchClass ARGS((Idents_tIdent node, Grammar_tLayout layout, Queues_tQueue indexes, Idents_tIdent class));
struct S_8 {
    CHAR A[127 + 1];
};
static void WritePatternTable ARGS(());
static void WriteMatchSetTable ARGS(());
static void WriteEntry ARGS((Idents_tIdent node, Queues_tQueue indexes, Sets_tSet set));


static INTEGER PutPattern
# ifdef __STDC__
(Patterns_tPattern pat, INTEGER no)
# else
(pat, no)
Patterns_tPattern pat;
INTEGER no;
# endif
{
  LONGINT index;
  LONGINT size;
  Idents_tIdent ident;

  {
    LONGINT B_1 = 0, B_2 = PatternTableCount;

    if (B_1 <= B_2)
      for (index = B_1;; index += 1) {
        if (Patterns_IsEqual(pat, PatternTable->A[index].Pat)) {
          if (no != NoIndex) {
            Sets_Include(&PatternTable->A[index].Numbers, (Sets_tElement)no);
          }
          return index;
        }
        if (index >= B_2) break;
      }
  }
  INC(PatternTableCount);
  if (PatternTableSize == 0) {
    PatternTableSize = InitPatternTableSize;
    DynArray_MakeArray((ADDRESS *)&PatternTable, &PatternTableSize, (LONGINT)sizeof(tPatternTableEntry));
  } else if (PatternTableCount == PatternTableSize) {
    DynArray_ExtendArray((ADDRESS *)&PatternTable, &PatternTableSize, (LONGINT)sizeof(tPatternTableEntry));
  }
  {
    register tPatternTableEntry *W_1 = &PatternTable->A[PatternTableCount];

    W_1->Pat = pat;
    Sets_MakeSet(&W_1->Numbers, (Sets_tElement)Environs_MaxDirective());
    if (no != NoIndex) {
      Sets_Include(&W_1->Numbers, (Sets_tElement)no);
    }
    if (pat == NIL) {
      W_1->SonNumbers = NIL;
    } else {
      ident = Patterns_GetPatternId(pat);
      if (Types_Type(ident) == Types_cNode) {
        size = Grammar_Arity(ident) + 1;
        DynArray_MakeArray((ADDRESS *)&W_1->SonNumbers, &size, (LONGINT)sizeof(INTEGER));
      } else {
        W_1->SonNumbers = NIL;
        ClassToPattern->A[ident] = PatternTableCount;
      }
    }
  }
  return PatternTableCount;
}

static BOOLEAN Defined
# ifdef __STDC__
(Patterns_tPattern pat)
# else
(pat)
Patterns_tPattern pat;
# endif
{
  LONGINT index;

  {
    LONGINT B_3 = 0, B_4 = PatternTableCount;

    if (B_3 <= B_4)
      for (index = B_3;; index += 1) {
        if (Patterns_IsEqual(pat, PatternTable->A[index].Pat)) {
          return TRUE;
        }
        if (index >= B_4) break;
      }
  }
  return FALSE;
}

static void CollectPatterns
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER no;
  INTEGER index;

  if (Environs_MaxDirective() == 0) {
    index = PutPattern((Patterns_tPattern)NIL, (LONGINT)NoIndex);
  } else {
    {
      LONGINT B_5 = 1, B_6 = Environs_MaxDirective();

      if (B_5 <= B_6)
        for (no = B_5;; no += 1) {
          index = PutPattern(Environs_GetPattern(no), no);
          if (no >= B_6) break;
        }
    }
  }
}

static void CollectSubPatterns
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT index, i;
  Idents_tIdent id;
  INTEGER pos;
  Patterns_tPattern pat, sub;
  Stack_tStack pats;

  index = -1;
  Stack_MakeStack(&pats);
  while (index < PatternTableCount) {
    INC(index);
    pat = PatternTable->A[index].Pat;
    if (pat != NIL) {
      id = Patterns_GetPatternId(pat);
      if (Types_Type(id) == Types_cNode) {
        {
          LONGINT B_7 = 1, B_8 = Grammar_Arity(id);

          if (B_7 <= B_8)
            for (pos = B_7;; pos += 1) {
              sub = Patterns_GetPatternSon(pat, pos);
              PatternTable->A[index].SonNumbers->A[pos] = PutPattern(sub, (LONGINT)NoIndex);
              if (pos >= B_8) break;
            }
        }
      } else {
        Patterns_SynthesizePatterns(id, &pats);
        while (!Stack_IsEmptyStack(pats)) {
          i = PutPattern(Patterns_NormPattern((Patterns_tPattern)Stack_Pop(&pats)), (LONGINT)NoIndex);
        }
      }
    }
  }
  Stack_ReleaseStack(&pats);
}

static void PutMatchSet
# ifdef __STDC__
(Sets_tSet set)
# else
(set)
Sets_tSet set;
# endif
{
  INC(MatchSetTableCount);
  if (MatchSetTableSize == 0) {
    MatchSetTableSize = InitMatchSetTableSize;
    DynArray_MakeArray((ADDRESS *)&MatchSetTable, &MatchSetTableSize, (LONGINT)sizeof(tMatchSetTableEntry));
  } else if (MatchSetTableCount == MatchSetTableSize) {
    DynArray_ExtendArray((ADDRESS *)&MatchSetTable, &MatchSetTableSize, (LONGINT)sizeof(tMatchSetTableEntry));
  }
  {
    register tMatchSetTableEntry *W_2 = &MatchSetTable->A[MatchSetTableCount];

    Sets_MakeSet(&W_2->Set, (Sets_tElement)PatternTableCount);
    Sets_Assign(&W_2->Set, set);
  }
}

static INTEGER MatchSetIndex
# ifdef __STDC__
(Sets_tSet set)
# else
(set)
Sets_tSet set;
# endif
{
  if (Sets_IsEqual(&set, &MatchSetTable->A[mIndex].Set)) {
    return mIndex;
  }
  mIndex = 0;
  for (;;) {
    if (mIndex > MatchSetTableCount) {
      goto EXIT_1;
    }
    if (Sets_IsEqual(&set, &MatchSetTable->A[mIndex].Set)) {
      return mIndex;
    }
    INC(mIndex);
  } EXIT_1:;
  return NoIndex;
}

static BOOLEAN InMatchSet
# ifdef __STDC__
(INTEGER elmt, INTEGER set)
# else
(elmt, set)
INTEGER elmt;
INTEGER set;
# endif
{
  return Sets_IsElement((Sets_tElement)elmt, &MatchSetTable->A[set].Set);
}

static void MakeMatchSets
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet set;

  Sets_MakeSet(&set, (Sets_tElement)PatternTableCount);
  SynthesizeMatchSets(-1L, &set);
  Sets_ReleaseSet(&set);
}

static void SynthesizeMatchSets
# ifdef __STDC__
(LONGINT last, Sets_tSet *set)
# else
(last, set)
LONGINT last;
Sets_tSet *set;
# endif
{
  LONGINT i, index;
  Patterns_tPattern pat, oldpat;
  BOOLEAN in, notin;

  if (last == PatternTableCount) {
    PutMatchSet(*set);
  } else {
    index = last + 1;
    pat = PatternTable->A[index].Pat;
    if (pat == NIL) {
      in = TRUE;
      notin = FALSE;
    } else {
      in = TRUE;
      notin = TRUE;
      {
        LONGINT B_9 = 0, B_10 = last;

        if (B_9 <= B_10)
          for (i = B_9;; i += 1) {
            oldpat = PatternTable->A[i].Pat;
            if (Sets_IsElement((Sets_tElement)i, set)) {
              switch (Patterns_Relation(oldpat, pat)) {
              case Patterns_cIndependent:;
                break;
              case Patterns_cInconsistent:;
                in = FALSE;
                break;
              case Patterns_cSubsumes:;
                notin = FALSE;
                break;
              case Patterns_cSupersumes:;
                break;
              case Patterns_cEqual:;
                Errors_ERROR((STRING)"SynthesizeMatchSets", 19L);
                break;
              }
            } else {
              switch (Patterns_Relation(oldpat, pat)) {
              case Patterns_cIndependent:;
                break;
              case Patterns_cInconsistent:;
                break;
              case Patterns_cSubsumes:;
                break;
              case Patterns_cSupersumes:;
                in = FALSE;
                break;
              case Patterns_cEqual:;
                Errors_ERROR((STRING)"SynthesizeMatchSets", 19L);
                break;
              }
            }
            if (i >= B_10) break;
          }
      }
    }
    if (in) {
      Sets_Include(set, (Sets_tElement)index);
      SynthesizeMatchSets(index, set);
      Sets_Exclude(set, (Sets_tElement)index);
    }
    if (notin) {
      SynthesizeMatchSets(index, set);
    }
  }
}

static void OutputMatchSets
# ifdef __STDC__
(System_tFile f)
# else
(f)
System_tFile f;
# endif
{
  LONGINT lindex, index;
  BITSET bitset;
  INTEGER elmtno, bitno, setno;
  INTEGER i, max;
  Sets_tSet directives;

  max = Environs_MaxDirective();
  Sets_MakeSet(&directives, (Sets_tElement)max);
  {
    LONGINT B_11 = 0, B_12 = MatchSetTableCount;

    if (B_11 <= B_12)
      for (index = B_11;; index += 1) {
        Sets_AssignEmpty(&directives);
        {
          LONGINT B_13 = 0, B_14 = PatternTableCount;

          if (B_13 <= B_14)
            for (lindex = B_13;; lindex += 1) {
              if (Sets_IsElement((Sets_tElement)lindex, &MatchSetTable->A[index].Set)) {
                Sets_Union(&directives, PatternTable->A[lindex].Numbers);
              }
              if (lindex >= B_14) break;
            }
        }
        {
          LONGINT B_15 = 0, B_16 = Environs_MaxDirective() / BitsPerBitset;

          if (B_15 <= B_16)
            for (setno = B_15;; setno += 1) {
              bitset = 0X0L;
              for (bitno = 0; bitno <= BitsPerBitset - 1; bitno += 1) {
                elmtno = setno * BitsPerBitset + bitno;
                if (elmtno <= max && Sets_IsElement((Sets_tElement)elmtno, &directives)) {
                  INCL(bitset, bitno);
                }
              }
              i = Write(f, ADR(bitset), (LONGINT)sizeof(BITSET));
              if (setno >= B_16) break;
            }
        }
        if (index >= B_12) break;
      }
  }
  Sets_ReleaseSet(&directives);
}

static void MakeMatchTables
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet nodes;
  Idents_tIdent node;
  LONGINT size;
  INTEGER pos;

  size = Grammar_MaxArity() + 1;
  DynArray_MakeArray((ADDRESS *)&SonMatchSets, &size, (LONGINT)sizeof(Sets_tSet));
  {
    LONGINT B_17 = 1, B_18 = Grammar_MaxArity();

    if (B_17 <= B_18)
      for (pos = B_17;; pos += 1) {
        Sets_MakeSet(&SonMatchSets->A[pos], (Sets_tElement)MatchSetTableCount);
        if (pos >= B_18) break;
      }
  }
  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Types_AllNodes(&nodes);
  while (!Sets_IsEmpty(nodes)) {
    node = Sets_Extract(&nodes);
    MakeMatchTable(node);
  }
  Sets_ReleaseSet(&nodes);
  DynArray_ReleaseArray((ADDRESS *)&SonMatchSets, &size, (LONGINT)sizeof(Sets_tSet));
}

static void MakeMatchTable
# ifdef __STDC__
(Idents_tIdent node)
# else
(node)
Idents_tIdent node;
# endif
{
  INTEGER pos;
  Sets_tSet set;
  INTEGER arity, index;
  Queues_tQueue indexes;
  Patterns_tPattern pat;
  Grammar_tLayout layout;

  Sets_MakeSet(&set, (Sets_tElement)PatternTableCount);
  {
    LONGINT B_19 = 0, B_20 = PatternTableCount;

    if (B_19 <= B_20)
      for (index = B_19;; index += 1) {
        pat = PatternTable->A[index].Pat;
        if (pat != NIL && Patterns_GetPatternId(pat) == node) {
          Sets_Include(&set, (Sets_tElement)index);
        }
        if (index >= B_20) break;
      }
  }
  if (Grammar_MainClass(node) != Scanner_NoIdent) {
    arity = Grammar_Arity(node);
    layout = Grammar_Layout(node, Grammar_MainClass(node));
    Queues_MakeQueue(&indexes);
    DefineSonMatchSets(0L, arity, layout);
    DefineMatchTable(node, set, 0L, arity, &indexes, layout);
    Queues_ReleaseQueue(&indexes);
  }
  Sets_ReleaseSet(&set);
}

static void DefineSonMatchSets
# ifdef __STDC__
(INTEGER pos, INTEGER arity, Grammar_tLayout layout)
# else
(pos, arity, layout)
INTEGER pos;
INTEGER arity;
Grammar_tLayout layout;
# endif
{
  Idents_tIdent class;
  Patterns_tPattern classpat, pat;
  Sets_tSet IndexSet;
  LONGINT lindex;

  if (pos == arity) {
    return;
  }
  INC(pos);
  Sets_MakeSet(&IndexSet, (Sets_tElement)PatternTableCount);
  class = Grammar_SonClass(layout, pos);
  classpat = Patterns_NormPattern(Patterns_MakePattern(class));
  {
    LONGINT B_21 = 0, B_22 = PatternTableCount;

    if (B_21 <= B_22)
      for (lindex = B_21;; lindex += 1) {
        pat = PatternTable->A[lindex].Pat;
        if (Patterns_Relation(classpat, pat) != Patterns_cInconsistent) {
          Sets_Include(&IndexSet, (Sets_tElement)lindex);
        }
        if (lindex >= B_22) break;
      }
  }
  Patterns_ReleasePattern(&classpat);
  Sets_AssignEmpty(&SonMatchSets->A[pos]);
  {
    LONGINT B_23 = 0, B_24 = MatchSetTableCount;

    if (B_23 <= B_24)
      for (lindex = B_23;; lindex += 1) {
        if (Sets_IsSubset(MatchSetTable->A[lindex].Set, IndexSet)) {
          Sets_Include(&SonMatchSets->A[pos], (Sets_tElement)lindex);
        }
        if (lindex >= B_24) break;
      }
  }
  Sets_ReleaseSet(&IndexSet);
  DefineSonMatchSets(pos, arity, layout);
}

static void DefineMatchTable
# ifdef __STDC__
(Idents_tIdent node, Sets_tSet set, INTEGER pos, INTEGER arity, Queues_tQueue *indexes, Grammar_tLayout layout)
# else
(node, set, pos, arity, indexes, layout)
Idents_tIdent node;
Sets_tSet set;
INTEGER pos;
INTEGER arity;
Queues_tQueue *indexes;
Grammar_tLayout layout;
# endif
{
  LONGINT lindex;
  INTEGER index;
  Sets_tSet MatchSet, set2;
  Patterns_tPattern pat;

  if (pos == arity) {
    {
      LONGINT B_25 = 0, B_26 = PatternTableCount;

      if (B_25 <= B_26)
        for (lindex = B_25;; lindex += 1) {
          pat = PatternTable->A[lindex].Pat;
          if (pat == NIL) {
            Sets_Include(&set, (Sets_tElement)lindex);
          } else if (Types_Type(Patterns_GetPatternId(pat)) == Types_cClass) {
            if (MatchClass(node, layout, *indexes, Patterns_GetPatternId(pat))) {
              Sets_Include(&set, (Sets_tElement)lindex);
            }
          }
          if (lindex >= B_26) break;
        }
    }
    DefineEntry(node, indexes, set);
  } else {
    INC(pos);
    Sets_MakeSet(&MatchSet, (Sets_tElement)MatchSetTableCount);
    Sets_Assign(&MatchSet, SonMatchSets->A[pos]);
    Sets_MakeSet(&set2, (Sets_tElement)PatternTableCount);
    while (!Sets_IsEmpty(MatchSet)) {
      index = Sets_Extract(&MatchSet);
      Sets_Assign(&set2, set);
      lindex = -1;
      for (;;) {
        if (lindex == PatternTableCount) {
          goto EXIT_2;
        }
        INC(lindex);
        if (Sets_IsElement((Sets_tElement)lindex, &set2)) {
          if (!Sets_IsElement((Sets_tElement)PatternTable->A[lindex].SonNumbers->A[pos], &MatchSetTable->A[index].Set)) {
            Sets_Exclude(&set2, (Sets_tElement)lindex);
          }
        }
      } EXIT_2:;
      Queues_Append(indexes, (ADDRESS)index);
      DefineMatchTable(node, set2, pos, arity, indexes, layout);
      Queues_ClearLast(indexes);
    }
    Sets_ReleaseSet(&set2);
    Sets_ReleaseSet(&MatchSet);
  }
}

static void DefineEntry
# ifdef __STDC__
(Idents_tIdent node, Queues_tQueue *indexes, Sets_tSet set)
# else
(node, indexes, set)
Idents_tIdent node;
Queues_tQueue *indexes;
Sets_tSet set;
# endif
{
  INTEGER matchindex;

  matchindex = MatchSetIndex(set);
  Queues_Insert(indexes, Convert_IdToAdr(node));
  Automaton_DefineTransition(*indexes, matchindex);
  Queues_ClearHead(indexes);
}

static BOOLEAN MatchClass
# ifdef __STDC__
(Idents_tIdent node, Grammar_tLayout layout, Queues_tQueue indexes, Idents_tIdent class)
# else
(node, layout, indexes, class)
Idents_tIdent node;
Grammar_tLayout layout;
Queues_tQueue indexes;
Idents_tIdent class;
# endif
{
  Idents_tIdent mainclass;
  Sets_tSet classes, nodes;
  Grammar_tLayout nodelayout;
  Idents_tIdent sonclass;
  BOOLEAN match;
  INTEGER set, index, pos;

  mainclass = Grammar_MainClass(node);
  if (class == mainclass) {
    return TRUE;
  }
  Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Grammar_Subclasses(class, &classes);
  match = FALSE;
  for (;;) {
    Grammar_NodesOfClass(class, &nodes);
    if (Sets_IsElement((Sets_tElement)node, &nodes)) {
      match = TRUE;
      nodelayout = Grammar_Layout(node, class);
      {
        LONGINT B_27 = 1, B_28 = Grammar_Arity(node);

        if (B_27 <= B_28)
          for (pos = B_27;; pos += 1) {
            if (match) {
              sonclass = Grammar_SonClass(nodelayout, pos);
              if (sonclass != Grammar_SonClass(layout, pos)) {
                set = (INTEGER)Queues_GetElement(indexes, pos);
                index = ClassToPattern->A[sonclass];
                if (index == NoIndex) {
                  StdIO_WriteS((STRING)"MatchClass: ", 12L);
                  Idents_WriteIdent((System_tFile)IO_StdOutput, sonclass);
                  StdIO_WriteS((STRING)" is not defined", 15L);
                  StdIO_WriteNl();
                  Errors_ERROR((STRING)"MatchClass", 10L);
                }
                match = Sets_IsElement((Sets_tElement)index, &MatchSetTable->A[set].Set);
              }
            }
            if (pos >= B_28) break;
          }
      }
      if (match) {
        goto EXIT_3;
      }
    }
    if (Sets_IsEmpty(classes)) {
      goto EXIT_3;
    }
    class = Sets_Extract(&classes);
  } EXIT_3:;
  Sets_ReleaseSet(&nodes);
  Sets_ReleaseSet(&classes);
  return match;
}

void Match_MakeTables
# ifdef __STDC__
()
# else
()
# endif
{
  System_tFile file;
  struct S_8 filename;
  Strings_tString s;
  Idents_tIdent name;
  LONGINT size;
  Idents_tIdent id;

  if (ArgCheck_BU) {
    size = Scanner_MaxIdent + 1;
    DynArray_MakeArray((ADDRESS *)&ClassToPattern, &size, (LONGINT)sizeof(INTEGER));
    {
      SHORTCARD B_29 = 0, B_30 = Scanner_MaxIdent;

      if (B_29 <= B_30)
        for (id = B_29;; id += 1) {
          ClassToPattern->A[id] = NoIndex;
          if (id >= B_30) break;
        }
    }
    name = Parser_AST->U_1.V_4.Spec.name;
    if (name == Scanner_NoIdent) {
      Strings_AssignEmpty(&s);
    } else {
      Idents_GetString(name, &s);
    }
    Strings_Append(&s, '\0');
    Strings_StringToArray(&s, filename.A, 128L);
    Character_Concatenate(filename.A, 128L, cTabPost, 4L);
    file = OpenOutput(filename.A, 128L);
    Checks_CheckOpenOutput(&file, filename.A, 128L);
    CollectPatterns();
    CollectSubPatterns();
    MakeMatchSets();
    OutputMatchSets(file);
    if (ArgCheck_MATCH) {
      WritePatternTable();
      WriteMatchSetTable();
    }
    Automaton_BeginAutomaton(MatchSetTableCount, General_Max(MatchSetTableCount, (LONGINT)Scanner_MaxIdent));
    MakeMatchTables();
    if (ArgCheck_AUTO) {
      Automaton_WriteAutomaton();
    }
    Automaton_CloseAutomaton(file, &Match_CombSize);
    Match_MaxMatchIndex = MatchSetTableCount;
    Close(file);
    if (ArgCheck_AUTO) {
      Automaton_WriteAutomaton();
    }
    if (ArgCheck_MATCH) {
      Automaton_WriteFunction();
      Automaton_WriteComb();
    }
  }
}

static void WritePatternTable
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT index;
  INTEGER pos;

  StdIO_WriteS((STRING)" Pattern Table ", 15L);
  StdIO_WriteNl();
  {
    LONGINT B_31 = 0, B_32 = PatternTableCount;

    if (B_31 <= B_32)
      for (index = B_31;; index += 1) {
        {
          register tPatternTableEntry *W_3 = &PatternTable->A[index];

          StdIO_WriteI(index, 3L);
          StdIO_WriteS((STRING)"  ", 2L);
          Patterns_WritePattern((System_tFile)IO_StdOutput, W_3->Pat);
          StdIO_WriteNl();
          StdIO_WriteS((STRING)"     ", 5L);
          Sets_WriteSet((System_tFile)IO_StdOutput, W_3->Numbers);
          StdIO_WriteS((STRING)" - ", 3L);
          if (W_3->Pat != NIL && Types_Type(Patterns_GetPatternId(W_3->Pat)) == Types_cNode) {
            {
              LONGINT B_33 = 1, B_34 = Grammar_Arity(Patterns_GetPatternId(W_3->Pat));

              if (B_33 <= B_34)
                for (pos = B_33;; pos += 1) {
                  StdIO_WriteS((STRING)" ", 1L);
                  StdIO_WriteI(W_3->SonNumbers->A[pos], 1L);
                  if (pos >= B_34) break;
                }
            }
          }
          StdIO_WriteNl();
        }
        if (index >= B_32) break;
      }
  }
  StdIO_WriteNl();
}

static void WriteMatchSetTable
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT lindex, index;
  Sets_tSet directives;

  StdIO_WriteS((STRING)" Match-Set Table ", 17L);
  StdIO_WriteNl();
  Sets_MakeSet(&directives, (Sets_tElement)Environs_MaxDirective());
  {
    LONGINT B_35 = 0, B_36 = MatchSetTableCount;

    if (B_35 <= B_36)
      for (index = B_35;; index += 1) {
        StdIO_WriteI(index, 3L);
        {
          register tMatchSetTableEntry *W_4 = &MatchSetTable->A[index];

          StdIO_WriteS((STRING)" ", 1L);
          Sets_WriteSet((System_tFile)IO_StdOutput, W_4->Set);
        }
        StdIO_WriteS((STRING)"    ", 4L);
        Sets_AssignEmpty(&directives);
        {
          LONGINT B_37 = 0, B_38 = PatternTableCount;

          if (B_37 <= B_38)
            for (lindex = B_37;; lindex += 1) {
              if (Sets_IsElement((Sets_tElement)lindex, &MatchSetTable->A[index].Set)) {
                Sets_Union(&directives, PatternTable->A[lindex].Numbers);
              }
              if (lindex >= B_38) break;
            }
        }
        Sets_WriteSet((System_tFile)IO_StdOutput, directives);
        StdIO_WriteNl();
        if (index >= B_36) break;
      }
  }
  Sets_ReleaseSet(&directives);
  StdIO_WriteNl();
}

static void WriteEntry
# ifdef __STDC__
(Idents_tIdent node, Queues_tQueue indexes, Sets_tSet set)
# else
(node, indexes, set)
Idents_tIdent node;
Queues_tQueue indexes;
Sets_tSet set;
# endif
{
  INTEGER pos;
  INTEGER index;

  index = MatchSetIndex(set);
  Idents_WriteIdent((System_tFile)IO_StdOutput, node);
  StdIO_WriteS((STRING)"( ", 2L);
  {
    LONGINT B_39 = 1, B_40 = Queues_Length(indexes);

    if (B_39 <= B_40)
      for (pos = B_39;; pos += 1) {
        StdIO_WriteI((INTEGER)Queues_GetElement(indexes, pos), 1L);
        StdIO_WriteS((STRING)" ", 1L);
        if (pos >= B_40) break;
      }
  }
  StdIO_WriteS((STRING)")  = ", 5L);
  StdIO_WriteI(index, 1L);
  StdIO_WriteNl();
}

void Match__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    ArgCheck__init();
    Automaton__init();
    Character__init();
    Checks__init();
    Convert__init();
    DynArray__init();
    Environs__init();
    Errors__init();
    General__init();
    Grammar__init();
    Idents__init();
    Parser__init();
    Patterns__init();
    Queues__init();
    Scanner__init();
    Sets__init();
    Stack__init();
    Strings__init();
    System__init();
    Types__init();
    Patterns__init();
    Strings__init();
    ArgCheck__init();
    Automaton__init();
    Idents__init();
    IO__init();
    Patterns__init();
    Queues__init();
    Sets__init();
    StdIO__init();

    PatternTableSize = 0;
    PatternTableCount = -1;
    MatchSetTableSize = 0;
    MatchSetTableCount = -1;
    mIndex = 0;
  }
}
