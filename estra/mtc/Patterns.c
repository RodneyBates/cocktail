#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
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

#ifndef DEFINITION_Memory
#include "Memory.h"
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

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Patterns
#include "Patterns.h"
#endif


static Patterns_tPattern vExtendPos;
static Patterns_tPattern Normalize ARGS((Patterns_tPattern pat, BOOLEAN reduce));
static BOOLEAN UniqNodeClass ARGS((Idents_tIdent class));
static void AllNodesOfClass ARGS((Idents_tIdent cl, Sets_tSet *nodesofclass));
static void Synthesize ARGS((Idents_tIdent class, Stack_tStack *out, Sets_tSet NodesIn));
static Patterns_tPattern Copy ARGS((Patterns_tPattern pat, Patterns_tPattern pos, Patterns_tPattern sub));


Patterns_tPattern Patterns_MakePattern
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  INTEGER arity;
  LONGINT size;
  Patterns_tPattern pat;
  INTEGER pos;

  pat = (Patterns_tPattern)Memory_Alloc((LONGINT)sizeof(Patterns_tPatternR));
  pat->Ident = id;
  Sets_MakeSet(&pat->Classes, (Sets_tElement)Scanner_MaxIdent);
  if (Types_Type(id) == Types_cNode) {
    arity = Grammar_Arity(id);
    size = arity + 1;
    DynArray_MakeArray((ADDRESS *)&pat->Sons, &size, (LONGINT)sizeof(Patterns_tPattern));
    {
      LONGINT B_1 = 1, B_2 = arity;

      if (B_1 <= B_2)
        for (pos = B_1;; pos += 1) {
          pat->Sons->A[pos] = NIL;
          if (pos >= B_2) break;
        }
    }
  } else {
    pat->Sons = NIL;
  }
  return pat;
}

void Patterns_PatternClasses
# ifdef __STDC__
(Patterns_tPattern pat, Sets_tSet *classes)
# else
(pat, classes)
Patterns_tPattern pat;
Sets_tSet *classes;
# endif
{
  Sets_Assign(classes, pat->Classes);
}

void Patterns_SetPatternSon
# ifdef __STDC__
(Patterns_tPattern pat, INTEGER pos, Patterns_tPattern son)
# else
(pat, pos, son)
Patterns_tPattern pat;
INTEGER pos;
Patterns_tPattern son;
# endif
{
  pat->Sons->A[pos] = son;
}

Patterns_tPattern Patterns_GetPatternSon
# ifdef __STDC__
(Patterns_tPattern pat, INTEGER pos)
# else
(pat, pos)
Patterns_tPattern pat;
INTEGER pos;
# endif
{
  return pat->Sons->A[pos];
}

Idents_tIdent Patterns_GetPatternId
# ifdef __STDC__
(Patterns_tPattern pat)
# else
(pat)
Patterns_tPattern pat;
# endif
{
  return pat->Ident;
}

void Patterns_ReleasePattern
# ifdef __STDC__
(Patterns_tPattern *pat)
# else
(pat)
Patterns_tPattern *pat;
# endif
{
  LONGINT size;
  INTEGER arity, pos;

  if (*pat != NIL) {
    Sets_ReleaseSet(&(*pat)->Classes);
    if (Types_Type((*pat)->Ident) == Types_cNode) {
      arity = Grammar_Arity((*pat)->Ident);
      {
        LONGINT B_3 = 1, B_4 = arity;

        if (B_3 <= B_4)
          for (pos = B_3;; pos += 1) {
            Patterns_ReleasePattern(&(*pat)->Sons->A[pos]);
            if (pos >= B_4) break;
          }
      }
      size = arity + 1;
      DynArray_ReleaseArray((ADDRESS *)&(*pat)->Sons, &size, (LONGINT)sizeof(Patterns_tPattern));
    }
    Memory_Free((LONGINT)sizeof(Patterns_tPatternR), (ADDRESS)(*pat));
    *pat = NIL;
  }
}

Patterns_tPattern Patterns_CopyPattern
# ifdef __STDC__
(Patterns_tPattern pat)
# else
(pat)
Patterns_tPattern pat;
# endif
{
  INTEGER pos;
  Patterns_tPattern copy;

  if (pat == NIL) {
    copy = NIL;
  } else {
    copy = Patterns_MakePattern(pat->Ident);
    Sets_Assign(&copy->Classes, pat->Classes);
    if (Types_Type(pat->Ident) == Types_cNode) {
      {
        LONGINT B_5 = 1, B_6 = Grammar_Arity(pat->Ident);

        if (B_5 <= B_6)
          for (pos = B_5;; pos += 1) {
            copy->Sons->A[pos] = Patterns_CopyPattern(pat->Sons->A[pos]);
            if (pos >= B_6) break;
          }
      }
    }
  }
  return copy;
}

Patterns_tPattern Patterns_NormPattern
# ifdef __STDC__
(Patterns_tPattern pat)
# else
(pat)
Patterns_tPattern pat;
# endif
{
  return Normalize(pat, TRUE);
}

static Patterns_tPattern Normalize
# ifdef __STDC__
(Patterns_tPattern pat, BOOLEAN reduce)
# else
(pat, reduce)
Patterns_tPattern pat;
BOOLEAN reduce;
# endif
{
  Idents_tIdent mainclass, class;
  Sets_tSet classes;
  Grammar_tLayout mainlayout, layout;
  INTEGER arity, pos;
  BOOLEAN ok;
  BOOLEAN nilsonly;
  Patterns_tPattern sonpat;

  if (pat == NIL) {
  } else {
    Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
    if (Types_Type(pat->Ident) == Types_cNode) {
      arity = Grammar_Arity(pat->Ident);
      mainclass = Grammar_MainClass(pat->Ident);
      mainlayout = Grammar_Layout(pat->Ident, mainclass);
      nilsonly = TRUE;
      {
        LONGINT B_7 = 1, B_8 = arity;

        if (B_7 <= B_8)
          for (pos = B_7;; pos += 1) {
            sonpat = Normalize(pat->Sons->A[pos], reduce);
            if (sonpat != NIL) {
              if (sonpat->Ident == Grammar_SonClass(mainlayout, pos)) {
                if (reduce) {
                  Patterns_ReleasePattern(&sonpat);
                  sonpat = NIL;
                }
              } else {
                nilsonly = FALSE;
              }
            }
            pat->Sons->A[pos] = sonpat;
            if (pos >= B_8) break;
          }
      }
      Sets_AssignEmpty(&pat->Classes);
      Grammar_ClassesOfNode(pat->Ident, &classes);
      while (!Sets_IsEmpty(classes)) {
        class = Sets_Extract(&classes);
        layout = Grammar_Layout(pat->Ident, class);
        ok = TRUE;
        {
          LONGINT B_9 = 1, B_10 = arity;

          if (B_9 <= B_10)
            for (pos = B_9;; pos += 1) {
              if (ok) {
                if (pat->Sons->A[pos] == NIL) {
                  ok = Grammar_SonClass(layout, pos) == Grammar_SonClass(mainlayout, pos);
                } else {
                  ok = Sets_IsElement((Sets_tElement)Grammar_SonClass(layout, pos), &pat->Sons->A[pos]->Classes);
                }
              }
              if (pos >= B_10) break;
            }
        }
        if (ok) {
          Sets_Include(&pat->Classes, (Sets_tElement)class);
        }
      }
      if (reduce && nilsonly && UniqNodeClass(mainclass)) {
        Patterns_ReleasePattern(&pat);
        pat = Patterns_MakePattern(mainclass);
      }
    }
    if (Types_Type(pat->Ident) == Types_cClass) {
      Sets_AssignElmt(&pat->Classes, (Sets_tElement)pat->Ident);
    }
    Sets_Assign(&classes, pat->Classes);
    while (!Sets_IsEmpty(classes)) {
      class = Grammar_SuperClass((SHORTCARD)Sets_Extract(&classes));
      while (class != Scanner_NoIdent && !Sets_IsElement((Sets_tElement)class, &pat->Classes)) {
        Sets_Include(&pat->Classes, (Sets_tElement)class);
        class = Grammar_SuperClass(class);
      }
    }
    Sets_ReleaseSet(&classes);
  }
  return pat;
}

static BOOLEAN UniqNodeClass
# ifdef __STDC__
(Idents_tIdent class)
# else
(class)
Idents_tIdent class;
# endif
{
  Sets_tSet classes, nodes;
  Idents_tIdent node;
  INTEGER count;

  Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Grammar_Subclasses(class, &classes);
  count = 0;
  for (;;) {
    Grammar_NodesOfClass(class, &nodes);
    while (!Sets_IsEmpty(nodes)) {
      node = Sets_Extract(&nodes);
      INC(count);
      if (count > 1) {
        goto EXIT_1;
      }
    }
    if (Sets_IsEmpty(classes)) {
      goto EXIT_1;
    }
    class = Sets_Extract(&classes);
  } EXIT_1:;
  Sets_ReleaseSet(&classes);
  Sets_ReleaseSet(&nodes);
  return count == 1;
}

Patterns_tRelation Patterns_Relation
# ifdef __STDC__
(Patterns_tPattern pat1, Patterns_tPattern pat2)
# else
(pat1, pat2)
Patterns_tPattern pat1, pat2;
# endif
{
  Idents_tIdent id1, id2;
  Types_tType t1, t2;
  INTEGER pos;
  Patterns_tRelation relation;
  Sets_tSet common, classes, nodes;

  if (pat1 == NIL && pat2 == NIL) {
    return Patterns_cEqual;
  }
  if (pat1 == NIL) {
    return Patterns_cSupersumes;
  }
  if (pat2 == NIL) {
    return Patterns_cSubsumes;
  }
  id1 = pat1->Ident;
  t1 = Types_Type(id1);
  id2 = pat2->Ident;
  t2 = Types_Type(id2);
  if (t1 == Types_cClass && t2 == Types_cClass) {
    if (id1 == id2) {
      return Patterns_cEqual;
    } else if (Sets_IsElement((Sets_tElement)id1, &pat2->Classes)) {
      vExtendPos = pat1;
      return Patterns_cSupersumes;
    } else if (Sets_IsElement((Sets_tElement)id2, &pat1->Classes)) {
      return Patterns_cSubsumes;
    } else {
      Sets_MakeSet(&common, (Sets_tElement)Scanner_MaxIdent);
      Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
      AllNodesOfClass(id1, &common);
      AllNodesOfClass(id2, &nodes);
      Sets_Intersection(&common, nodes);
      if (Sets_IsEmpty(common)) {
        relation = Patterns_cInconsistent;
      } else {
        relation = Patterns_cIndependent;
      }
      Sets_ReleaseSet(&nodes);
      Sets_ReleaseSet(&common);
      return relation;
    }
  } else if (t1 == Types_cClass) {
    if (Sets_IsElement((Sets_tElement)id1, &pat2->Classes)) {
      vExtendPos = pat1;
      return Patterns_cSupersumes;
    } else {
      Sets_MakeSet(&common, (Sets_tElement)Scanner_MaxIdent);
      Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
      Grammar_Subclasses(id1, &common);
      Grammar_ClassesOfNode(id2, &classes);
      Sets_Include(&common, (Sets_tElement)id1);
      Sets_Intersection(&common, classes);
      if (Sets_IsEmpty(common)) {
        relation = Patterns_cInconsistent;
      } else {
        vExtendPos = pat1;
        relation = Patterns_cIndependent;
      }
      Sets_ReleaseSet(&classes);
      Sets_ReleaseSet(&common);
      return relation;
    }
  } else if (t2 == Types_cClass) {
    if (Sets_IsElement((Sets_tElement)id2, &pat1->Classes)) {
      return Patterns_cSubsumes;
    } else {
      Sets_MakeSet(&common, (Sets_tElement)Scanner_MaxIdent);
      Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
      Grammar_Subclasses(id2, &common);
      Grammar_ClassesOfNode(id1, &classes);
      Sets_Include(&common, (Sets_tElement)id2);
      Sets_Intersection(&common, classes);
      if (Sets_IsEmpty(common)) {
        relation = Patterns_cInconsistent;
      } else {
        relation = Patterns_cIndependent;
      }
      Sets_ReleaseSet(&classes);
      Sets_ReleaseSet(&common);
      return relation;
    }
  } else {
    if (id1 == id2) {
      relation = Patterns_cEqual;
      {
        LONGINT B_11 = 1, B_12 = Grammar_Arity(id1);

        if (B_11 <= B_12)
          for (pos = B_11;; pos += 1) {
            switch (Patterns_Relation(pat1->Sons->A[pos], pat2->Sons->A[pos])) {
            case Patterns_cEqual:;
              break;
            case Patterns_cIndependent:;
              if (relation != Patterns_cInconsistent) {
                relation = Patterns_cIndependent;
              }
              break;
            case Patterns_cInconsistent:;
              return Patterns_cInconsistent;
              break;
            case Patterns_cSubsumes:;
              if (relation == Patterns_cEqual) {
                relation = Patterns_cSubsumes;
              } else if (relation == Patterns_cSupersumes) {
                relation = Patterns_cIndependent;
              }
              break;
            case Patterns_cSupersumes:;
              if (relation == Patterns_cEqual) {
                relation = Patterns_cSupersumes;
              } else if (relation == Patterns_cSubsumes) {
                relation = Patterns_cIndependent;
              }
              break;
            }
            if (pos >= B_12) break;
          }
      }
      return relation;
    } else {
      return Patterns_cInconsistent;
    }
  }
}

static void AllNodesOfClass
# ifdef __STDC__
(Idents_tIdent cl, Sets_tSet *nodesofclass)
# else
(cl, nodesofclass)
Idents_tIdent cl;
Sets_tSet *nodesofclass;
# endif
{
  Sets_tSet classes, nodes;

  Sets_AssignEmpty(nodesofclass);
  Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Grammar_Subclasses(cl, &classes);
  for (;;) {
    Grammar_NodesOfClass(cl, &nodes);
    Sets_Union(nodesofclass, nodes);
    if (Sets_IsEmpty(classes)) {
      goto EXIT_2;
    }
    cl = Sets_Extract(&classes);
  } EXIT_2:;
  Sets_ReleaseSet(&classes);
  Sets_ReleaseSet(&nodes);
}

void Patterns_ResetExtendPos
# ifdef __STDC__
()
# else
()
# endif
{
  vExtendPos = NIL;
}

Patterns_tPattern Patterns_ExtendPos
# ifdef __STDC__
()
# else
()
# endif
{
  return vExtendPos;
}

void Patterns_Extend
# ifdef __STDC__
(Patterns_tPattern pat, Patterns_tPattern pos, Queues_tQueue *out)
# else
(pat, pos, out)
Patterns_tPattern pat, pos;
Queues_tQueue *out;
# endif
{
  Stack_tStack pats;
  Sets_tSet EmptySet;

  Stack_MakeStack(&pats);
  Sets_MakeSet(&EmptySet, (Sets_tElement)Scanner_MaxIdent);
  Synthesize(pos->Ident, &pats, EmptySet);
  while (!Stack_IsEmptyStack(pats)) {
    Queues_Insert(out, (ADDRESS)Normalize(Copy(pat, pos, (Patterns_tPattern)Stack_Pop(&pats)), FALSE));
  }
  Sets_ReleaseSet(&EmptySet);
  Stack_ReleaseStack(&pats);
}

void Patterns_SynthesizePatterns
# ifdef __STDC__
(Idents_tIdent class, Stack_tStack *pats)
# else
(class, pats)
Idents_tIdent class;
Stack_tStack *pats;
# endif
{
  Sets_tSet EmptySet;

  Sets_MakeSet(&EmptySet, (Sets_tElement)Scanner_MaxIdent);
  Stack_ClearStack(pats);
  Synthesize(class, pats, EmptySet);
  Sets_ReleaseSet(&EmptySet);
}

static void Synthesize
# ifdef __STDC__
(Idents_tIdent class, Stack_tStack *out, Sets_tSet NodesIn)
# else
(class, out, NodesIn)
Idents_tIdent class;
Stack_tStack *out;
Sets_tSet NodesIn;
# endif
{
  Sets_tSet nodes, classes;
  Sets_tSet NodesOut;
  Idents_tIdent node;
  Grammar_tLayout layout;
  Patterns_tPattern pat;
  INTEGER i;
  Idents_tIdent mainclass;

  if (Types_Type(class) != Types_cClass) {
    Errors_ERROR((STRING)"Synthesize", 10L);
  }
  Sets_MakeSet(&nodes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&classes, (Sets_tElement)Scanner_MaxIdent);
  Sets_MakeSet(&NodesOut, (Sets_tElement)Scanner_MaxIdent);
  Sets_Assign(&NodesOut, NodesIn);
  Grammar_NodesOfClass(class, &nodes);
  Sets_Difference(&nodes, NodesIn);
  while (!Sets_IsEmpty(nodes)) {
    node = Sets_Extract(&nodes);
    mainclass = Grammar_MainClass(node);
    if (mainclass != Scanner_NoIdent) {
      if (class == mainclass) {
        Sets_Include(&NodesOut, (Sets_tElement)node);
      }
      layout = Grammar_Layout(node, class);
      pat = Patterns_MakePattern(node);
      {
        LONGINT B_13 = 1, B_14 = Grammar_Arity(node);

        if (B_13 <= B_14)
          for (i = B_13;; i += 1) {
            Patterns_SetPatternSon(pat, i, Patterns_MakePattern(Grammar_SonClass(layout, i)));
            if (i >= B_14) break;
          }
      }
      Stack_Push(out, (ADDRESS)pat);
    }
  }
  Grammar_DirectSubclasses(class, &classes);
  while (!Sets_IsEmpty(classes)) {
    class = Sets_Extract(&classes);
    Synthesize(class, out, NodesOut);
  }
  Sets_ReleaseSet(&classes);
  Sets_ReleaseSet(&nodes);
  Sets_ReleaseSet(&NodesOut);
}

static Patterns_tPattern Copy
# ifdef __STDC__
(Patterns_tPattern pat, Patterns_tPattern pos, Patterns_tPattern sub)
# else
(pat, pos, sub)
Patterns_tPattern pat, pos, sub;
# endif
{
  INTEGER p;
  Patterns_tPattern copy;

  if (pat == pos) {
    copy = sub;
  } else {
    copy = Patterns_MakePattern(pat->Ident);
    Sets_Assign(&copy->Classes, pat->Classes);
    if (Types_Type(pat->Ident) == Types_cNode) {
      {
        LONGINT B_15 = 1, B_16 = Grammar_Arity(pat->Ident);

        if (B_15 <= B_16)
          for (p = B_15;; p += 1) {
            copy->Sons->A[p] = Copy(pat->Sons->A[p], pos, sub);
            if (p >= B_16) break;
          }
      }
    }
  }
  return copy;
}

BOOLEAN Patterns_IsEqual
# ifdef __STDC__
(Patterns_tPattern pat1, Patterns_tPattern pat2)
# else
(pat1, pat2)
Patterns_tPattern pat1, pat2;
# endif
{
  return Patterns_Relation(pat1, pat2) == Patterns_cEqual;
}

void Patterns_WritePattern
# ifdef __STDC__
(IO_tFile f, Patterns_tPattern pat)
# else
(f, pat)
IO_tFile f;
Patterns_tPattern pat;
# endif
{
  INTEGER arity, pos;

  if (pat == NIL) {
    IO_WriteS(f, (STRING)":", 1L);
  } else {
    Idents_WriteIdent(f, pat->Ident);
    if (Types_Type(pat->Ident) == Types_cNode) {
      IO_WriteS(f, (STRING)" (", 2L);
      arity = Grammar_Arity(pat->Ident);
      if (arity > 0) {
        pos = 0;
        for (;;) {
          INC(pos);
          Patterns_WritePattern(f, pat->Sons->A[pos]);
          if (pos == arity) {
            goto EXIT_3;
          }
          IO_WriteS(f, (STRING)", ", 2L);
        } EXIT_3:;
      }
      IO_WriteS(f, (STRING)")", 1L);
    }
  }
}

void Patterns__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Idents__init();
    IO__init();
    Queues__init();
    Sets__init();
    Stack__init();
    DynArray__init();
    Errors__init();
    Grammar__init();
    Idents__init();
    IO__init();
    Memory__init();
    Queues__init();
    Scanner__init();
    Sets__init();
    Stack__init();
    Types__init();
    Scanner__init();

  }
}
