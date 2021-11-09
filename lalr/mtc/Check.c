#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Debug
#include "Debug.h"
#endif

#ifndef DEFINITION_Debug
#include "Debug.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Check
#include "Check.h"
#endif

BOOLEAN Check_Verbose;

#define eState   70
#define eReadRed   71
#define eRedRed   72
#define eReadRedRed   73
#define eRepReadRed   74
#define eRepRedRed   75
#define eRepReadRedRed   76
#define eARepReadRed   77
#define eARepRedRed   78
#define eARepReadRedRed   79
static CHAR DevNull [] = "/dev/null";
static CHAR DEBUG [] = "_Debug";
static struct S_1 {
    CHAR A[128 + 1];
} FileName;
static void RepairConflict ARGS((Automaton_tStateIndex state, Sets_tSet *ConflictSet));
static void ERROR ARGS((CHAR a[], LONGCARD ));


void Check_CheckForConflicts
# ifdef __STDC__
(BOOLEAN *ok)
# else
(ok)
BOOLEAN *ok;
# endif
{
  Sets_tSet SymbolSet, ConflictSet, TempSet;
  Automaton_tStateIndex state, maxState;
  Automaton_tItemIndex item;
  BOOLEAN Error;
  Strings_tString string;

  Error = FALSE;
  Sets_MakeSet(&SymbolSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&ConflictSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&TempSet, (Sets_tElement)TokenTab_MAXTerm);
  if (Check_Verbose) {
    ArgCheck_MakeFileName(Idents_NoIdent, (STRING)"_Debug", 6L, (STRING)"", 1L, FileName.A, 129L);
    Debug_dFile = IO_WriteOpen(FileName.A, 129L);
    if (SysError_StatIsBad(Debug_dFile)) {
      Strings_ArrayToString(DEBUG, 6L, &string);
      SysError_SysErrorMessageI(Debug_dFile, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(string));
      ArgCheck_MakeFileName(Idents_NoIdent, (STRING)"/dev/null", 9L, (STRING)"", 1L, FileName.A, 129L);
      Debug_dFile = IO_WriteOpen(FileName.A, 129L);
      if (SysError_StatIsBad(Debug_dFile)) {
        Strings_ArrayToString(DevNull, 9L, &string);
        SysError_SysErrorMessageI(Debug_dFile, (LONGCARD)Errors_eFatal, (LONGCARD)Errors_eString, ADR(string));
      }
    }
  }
  maxState = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_1 = 1, B_2 = maxState;

    if (B_1 <= B_2)
      for (state = B_1;; state += 1) {
        {
          register Automaton_tState *W_1 = &Automaton_StateArrayPtr->A[state - 1];

          {
            LONGCARD B_3 = W_1->Items, B_4 = W_1->Items + W_1->Size - 1;

            if (B_3 <= B_4)
              for (item = B_3;; item += 1) {
                {
                  register Automaton_tItem *W_2 = &Automaton_ItemArrayPtr->A[item - 1];

                  W_2->Number = state;
                }
                if (item >= B_4) break;
              }
          }
        }
        if (state >= B_2) break;
      }
  }
  {
    Automaton_tStateIndex B_5 = 1, B_6 = maxState;

    if (B_5 <= B_6)
      for (state = B_5;; state += 1) {
        {
          register Automaton_tState *W_3 = &Automaton_StateArrayPtr->A[state - 1];

          Sets_AssignEmpty(&ConflictSet);
          Sets_AssignEmpty(&SymbolSet);
          {
            LONGCARD B_7 = W_3->Items, B_8 = W_3->Items + W_3->Size - 1;

            if (B_7 <= B_8)
              for (item = B_7;; item += 1) {
                {
                  register Automaton_tItem *W_4 = &Automaton_ItemArrayPtr->A[item - 1];

                  switch (W_4->Rep) {
                  case Automaton_TermRep:;
                    if (Sets_IsElement((Sets_tElement)W_4->Read, &SymbolSet)) {
                      Sets_Include(&ConflictSet, (Sets_tElement)W_4->Read);
                    } else {
                      Sets_Include(&SymbolSet, (Sets_tElement)W_4->Read);
                    }
                    break;
                  case Automaton_RedRep:;
                    Sets_Assign(&TempSet, W_4->Set);
                    Sets_Intersection(&TempSet, SymbolSet);
                    Sets_Union(&ConflictSet, TempSet);
                    Sets_Union(&SymbolSet, W_4->Set);
                    break;
                  default :
                    break;
                  }
                }
                if (item >= B_8) break;
              }
          }
          if (!Sets_IsEmpty(ConflictSet)) {
            RepairConflict(state, &ConflictSet);
            if (!Sets_IsEmpty(ConflictSet)) {
              Error = TRUE;
            }
          }
        }
        if (state >= B_6) break;
      }
  }
  Sets_ReleaseSet(&TempSet);
  Sets_ReleaseSet(&ConflictSet);
  Sets_ReleaseSet(&SymbolSet);
  if (Debug_ItemSets) {
    Debug_PrintItemSets();
  }
  *ok = !Error;
  if (Check_Verbose) {
    IO_WriteClose(Debug_dFile);
  }
}

static void RepairConflict
# ifdef __STDC__
(Automaton_tStateIndex state, Sets_tSet *ConflictSet)
# else
(state, ConflictSet)
Automaton_tStateIndex state;
Sets_tSet *ConflictSet;
# endif
{
  Sets_tSet todo;
  TokenTab_Terminal LookAhead;
  Sets_tSet ReadRedSet, RedRedSet, ReadRedRedSet, RepReadRedSet, RepRedRedSet, RepReadRedRedSet, ARepReadRedSet, ARepRedRedSet, ARepReadRedRedSet;
  TokenTab_Prio Priority, ReducePri, ShiftPri;
  Automaton_tAss Associativity, ReduceAss, ShiftAss;
  Automaton_tIndex MinProdNo;
  BOOLEAN OnlyOpers;
  CARDINAL ReduceCount, ShiftCount, ReduceRest, ShiftRest;
  Automaton_tItemIndex item;
  Automaton_tProduction prod;
  BOOLEAN ConflictFree;

  Sets_MakeSet(&ReadRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&RedRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&ReadRedRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&RepReadRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&RepRedRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&RepReadRedRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&ARepReadRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&ARepRedRedSet, (Sets_tElement)TokenTab_MAXTerm);
  Sets_MakeSet(&ARepReadRedRedSet, (Sets_tElement)TokenTab_MAXTerm);
  if (Check_Verbose) {
    Debug_DebugHead(state);
    Debug_DebugState(state, ConflictSet);
  }
  Sets_MakeSet(&todo, (Sets_tElement)TokenTab_MAXTerm);
  Sets_Assign(&todo, *ConflictSet);
  {
    register Automaton_tState *W_5 = &Automaton_StateArrayPtr->A[state - 1];

    while (!Sets_IsEmpty(todo)) {
      LookAhead = Sets_Extract(&todo);
      OnlyOpers = TRUE;
      ReduceCount = 0;
      ShiftCount = 0;
      ReduceRest = 0;
      ShiftRest = 0;
      ReducePri = 0;
      ReduceAss = Automaton_none;
      ShiftPri = 0;
      ShiftAss = Automaton_none;
      MinProdNo = 10000;
      {
        LONGCARD B_9 = W_5->Items, B_10 = W_5->Items + W_5->Size - 1;

        if (B_9 <= B_10)
          for (item = B_9;; item += 1) {
            {
              register Automaton_tItem *W_6 = &Automaton_ItemArrayPtr->A[item - 1];

              if (W_6->Rep == Automaton_RedRep && Sets_IsElement((Sets_tElement)LookAhead, &W_6->Set)) {
                INC(ReduceCount);
                prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_6->Prod]);
                if (prod->Pri == 0) {
                  OnlyOpers = FALSE;
                } else if (prod->Pri > ReducePri) {
                  ReducePri = prod->Pri;
                  ReduceAss = prod->Ass;
                }
                if (prod->ProdNo < MinProdNo) {
                  MinProdNo = prod->ProdNo;
                }
              } else if (W_6->Rep == Automaton_TermRep && W_6->Read == LookAhead) {
                INC(ShiftCount);
                if (Automaton_OperArray.A[LookAhead].Pri == 0) {
                  OnlyOpers = FALSE;
                } else {
                  ShiftPri = Automaton_OperArray.A[LookAhead].Pri;
                  ShiftAss = Automaton_OperArray.A[LookAhead].Ass;
                }
              }
            }
            if (item >= B_10) break;
          }
      }
      if (OnlyOpers) {
        if (ReducePri > ShiftPri) {
          Priority = ReducePri;
          Associativity = ReduceAss;
        } else {
          Priority = ShiftPri;
          Associativity = ShiftAss;
        }
        {
          LONGCARD B_11 = W_5->Items, B_12 = W_5->Items + W_5->Size - 1;

          if (B_11 <= B_12)
            for (item = B_11;; item += 1) {
              {
                register Automaton_tItem *W_7 = &Automaton_ItemArrayPtr->A[item - 1];

                if (W_7->Rep == Automaton_RedRep && Sets_IsElement((Sets_tElement)LookAhead, &W_7->Set)) {
                  prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_7->Prod]);
                  if (prod->Pri < Priority) {
                    if (Check_Verbose) {
                      Debug_InformLowPri(item, LookAhead);
                    }
                    Sets_Exclude(&W_7->Set, (Sets_tElement)LookAhead);
                    if (Sets_IsEmpty(W_7->Set)) {
                      W_7->Rep = Automaton_NoRep;
                    }
                  } else if (prod->Pri == Priority && (Associativity == Automaton_right || Associativity == Automaton_nonassoc) && ShiftPri == Priority) {
                    if (Check_Verbose) {
                      Debug_InformRightAss(item, LookAhead);
                    }
                    Sets_Exclude(&W_7->Set, (Sets_tElement)LookAhead);
                    if (Sets_IsEmpty(W_7->Set)) {
                      W_7->Rep = Automaton_NoRep;
                    }
                  } else {
                    if (Check_Verbose) {
                      Debug_InformKept(item, LookAhead);
                    }
                    INC(ReduceRest);
                  }
                } else if (W_7->Read == LookAhead) {
                  if (ShiftPri < Priority) {
                    if (Check_Verbose) {
                      Debug_InformLowPri(item, LookAhead);
                    }
                    W_7->Rep = Automaton_NoRep;
                  } else if (ShiftPri == Priority && (Associativity == Automaton_left || Associativity == Automaton_nonassoc) && ReducePri == Priority) {
                    if (Check_Verbose) {
                      Debug_InformLeftAss(item, LookAhead);
                    }
                    W_7->Rep = Automaton_NoRep;
                  } else {
                    if (Check_Verbose) {
                      Debug_InformKept(item, LookAhead);
                    }
                    INC(ShiftRest);
                  }
                }
              }
              if (item >= B_12) break;
            }
        }
      } else {
        if (ShiftCount > 0) {
          {
            LONGCARD B_13 = W_5->Items, B_14 = W_5->Items + W_5->Size - 1;

            if (B_13 <= B_14)
              for (item = B_13;; item += 1) {
                {
                  register Automaton_tItem *W_8 = &Automaton_ItemArrayPtr->A[item - 1];

                  if (W_8->Rep == Automaton_RedRep && Sets_IsElement((Sets_tElement)LookAhead, &W_8->Set)) {
                    if (Check_Verbose) {
                      Debug_InformIgnored(item, LookAhead);
                    }
                    Sets_Exclude(&W_8->Set, (Sets_tElement)LookAhead);
                    if (Sets_IsEmpty(W_8->Set)) {
                      W_8->Rep = Automaton_NoRep;
                    }
                  } else if (W_8->Read == LookAhead) {
                    if (Check_Verbose) {
                      Debug_InformKept(item, LookAhead);
                    }
                    INC(ShiftRest);
                  }
                }
                if (item >= B_14) break;
              }
          }
        } else {
          {
            LONGCARD B_15 = W_5->Items, B_16 = W_5->Items + W_5->Size - 1;

            if (B_15 <= B_16)
              for (item = B_15;; item += 1) {
                {
                  register Automaton_tItem *W_9 = &Automaton_ItemArrayPtr->A[item - 1];

                  if (W_9->Rep == Automaton_RedRep && Sets_IsElement((Sets_tElement)LookAhead, &W_9->Set)) {
                    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_9->Prod]);
                    if (prod->ProdNo == MinProdNo) {
                      if (Check_Verbose) {
                        Debug_InformKept(item, LookAhead);
                      }
                      INC(ReduceRest);
                    } else {
                      if (Check_Verbose) {
                        Debug_InformIgnored(item, LookAhead);
                      }
                      Sets_Exclude(&W_9->Set, (Sets_tElement)LookAhead);
                      if (Sets_IsEmpty(W_9->Set)) {
                        W_9->Rep = Automaton_NoRep;
                      }
                    }
                  }
                }
                if (item >= B_16) break;
              }
          }
        }
      }
      ConflictFree = FALSE;
      if (ReduceRest > 1) {
        if (ShiftRest > 0) {
          if (Check_Verbose) {
            Debug_InformConflict(Debug_ShRedRed);
          }
          Sets_Include(&ReadRedRedSet, (Sets_tElement)LookAhead);
        } else {
          if (Check_Verbose) {
            Debug_InformConflict(Debug_RedRed);
          }
          Sets_Include(&RedRedSet, (Sets_tElement)LookAhead);
        }
      } else if (ReduceRest == 1) {
        if (ShiftRest > 0) {
          if (Check_Verbose) {
            Debug_InformConflict(Debug_ShRed);
          }
          Sets_Include(&ReadRedSet, (Sets_tElement)LookAhead);
        } else {
          ConflictFree = TRUE;
        }
      } else {
        ConflictFree = TRUE;
      }
      if (Check_Verbose) {
        Debug_NewLine();
      }
      if (ConflictFree) {
        Sets_Exclude(ConflictSet, (Sets_tElement)LookAhead);
        if (ReduceCount > 1) {
          if (ShiftCount > 0) {
            if (OnlyOpers) {
              Sets_Include(&RepReadRedRedSet, (Sets_tElement)LookAhead);
            } else {
              Sets_Include(&ARepReadRedRedSet, (Sets_tElement)LookAhead);
            }
          } else {
            if (OnlyOpers) {
              Sets_Include(&RepRedRedSet, (Sets_tElement)LookAhead);
            } else {
              Sets_Include(&ARepRedRedSet, (Sets_tElement)LookAhead);
            }
          }
        } else if (ReduceCount == 1) {
          if (ShiftCount > 0) {
            if (OnlyOpers) {
              Sets_Include(&RepReadRedSet, (Sets_tElement)LookAhead);
            } else {
              Sets_Include(&ARepReadRedSet, (Sets_tElement)LookAhead);
            }
          } else {
            ERROR((STRING)"Check.RepairConflict: No Conflict (1)", 37L);
          }
        } else {
          ERROR((STRING)"Check.RepairConflict: No Conflict (2)", 37L);
        }
      }
    }
  }
  Errors_ErrorMessageI((LONGCARD)eState, (LONGCARD)Errors_eInformation, Positions_NoPosition, (LONGCARD)Errors_eShort, ADR(state));
  if (!Sets_IsEmpty(ReadRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eReadRed, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(ReadRedSet));
  }
  if (!Sets_IsEmpty(RedRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eRedRed, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(RedRedSet));
  }
  if (!Sets_IsEmpty(ReadRedRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eReadRedRed, (LONGCARD)Errors_eError, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(ReadRedRedSet));
  }
  if (!Sets_IsEmpty(RepReadRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eRepReadRed, (LONGCARD)Errors_eInformation, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(RepReadRedSet));
  }
  if (!Sets_IsEmpty(RepRedRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eRepRedRed, (LONGCARD)Errors_eInformation, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(RepRedRedSet));
  }
  if (!Sets_IsEmpty(RepReadRedRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eRepReadRedRed, (LONGCARD)Errors_eInformation, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(RepReadRedRedSet));
  }
  if (!Sets_IsEmpty(ARepReadRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eARepReadRed, (LONGCARD)Errors_eWarning, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(ARepReadRedSet));
  }
  if (!Sets_IsEmpty(ARepRedRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eARepRedRed, (LONGCARD)Errors_eWarning, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(ARepRedRedSet));
  }
  if (!Sets_IsEmpty(ARepReadRedRedSet)) {
    Errors_ErrorMessageI((LONGCARD)eARepReadRedRed, (LONGCARD)Errors_eWarning, Positions_NoPosition, (LONGCARD)Errors_eTermSet, ADR(ARepReadRedRedSet));
  }
  Sets_ReleaseSet(&ReadRedSet);
  Sets_ReleaseSet(&RedRedSet);
  Sets_ReleaseSet(&ReadRedRedSet);
  Sets_ReleaseSet(&RepReadRedSet);
  Sets_ReleaseSet(&RepRedRedSet);
  Sets_ReleaseSet(&RepReadRedRedSet);
  Sets_ReleaseSet(&ARepReadRedSet);
  Sets_ReleaseSet(&ARepRedRedSet);
  Sets_ReleaseSet(&ARepReadRedRedSet);
  Sets_ReleaseSet(&todo);
  if (Check_Verbose) {
    Debug_DebugEnd();
  }
}

static void ERROR
# ifdef __STDC__
(CHAR a[], LONGCARD O_1)
# else
(a, O_1)
CHAR a[];
LONGCARD O_1;
# endif
{
  Strings_tString s;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(a, O_1, CHAR)
  Strings_ArrayToString(a, O_1, &s);
  Errors_ErrorMessageI((LONGCARD)Errors_eInternal, (LONGCARD)Errors_eFatal, Positions_NoPosition, (LONGCARD)Errors_eString, ADR(s));
  FREE_OPEN_ARRAYS
}

void Check__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    ArgCheck__init();
    Idents__init();
    Automaton__init();
    Debug__init();
    Debug__init();
    Errors__init();
    Idents__init();
    IO__init();
    Sets__init();
    Strings__init();
    SysError__init();
    Positions__init();
    TokenTab__init();

    Check_Verbose = FALSE;
  }
}
