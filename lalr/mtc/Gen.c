#include "SYSTEM_.h"

#ifndef DEFINITION_Actions
#include "Actions.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Compress
#include "Compress.h"
#endif

#ifndef DEFINITION_Continue
#include "Continue.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Default
#include "Default.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Final
#include "Final.h"
#endif

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_GenLang
#include "GenLang.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
#endif

#ifndef DEFINITION_Lists
#include "Lists.h"
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

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_SysError
#include "SysError.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Times
#include "Times.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

BOOLEAN Gen_Trace;
BOOLEAN Gen_CaseFlag;
INTEGER Gen_CaseLabels;
TokenTab_Vocabulary Gen_FirstSymbol, Gen_LastSymbol, Gen_FirstTerminal, Gen_LastTerminal;
CARDINAL Gen_NonTermOffset;
Automaton_tStateIndex Gen_FirstState, Gen_LastState, Gen_FirstReadState, Gen_LastReadState, Gen_FirstReadTermState, Gen_LastReadTermState, Gen_FirstReadNonTermState, Gen_LastReadNonTermState, Gen_FirstReduceState, Gen_LastReduceState, Gen_StopState;
Automaton_tStateIndex Gen_ReduceOffset;
Gen_TableElmt Gen_ElmtSize;
struct Gen_2 *Gen_Length;
LONGINT Gen_LengthCount;
struct Gen_3 *Gen_LeftHandSide;
LONGINT Gen_LeftHandSideCount;
struct Gen_4 *Gen_Continuation;
LONGINT Gen_ContinuationCount;
struct Gen_5 *Gen_FinalToProd;
LONGINT Gen_FinalToProdCount;

#define EOL   '\n'
#define InitReduceCount   4
typedef struct S_1 {
    Gen_TableElmt Check, Next;
} ControlType;
static Gen_tTableLine TableLine;
static Automaton_tStateIndex StateCnt;
static struct S_2 {
    CHAR A[128 + 1];
} FileName;
static void FindKind ARGS(());
static void MakeNumbers ARGS(());
static void MakeTable ARGS(());
static void InitTableLine ARGS(());
static Automaton_tStateIndex MakeTableLine ARGS((Automaton_tStateIndex state));
static void MakeLength ARGS(());
static void MakeLeftHandSide ARGS(());
static TokenTab_Vocabulary FindFirstTerminal ARGS(());
static TokenTab_Vocabulary FindLastTerminal ARGS(());
static TokenTab_Vocabulary FindLastSymbol ARGS(());
static void PrepareReduceCode ARGS(());
static void PutTables ARGS((System_tFile TableFile));
static void PutTable ARGS((Gen_TableElmt Length, ADDRESS Address));
static void PutBase ARGS((System_tFile File));
static void PutNBase ARGS((System_tFile File));
static void PutDefault ARGS((System_tFile File));
static void PutControl ARGS((System_tFile File));
static void PutNNext ARGS((System_tFile File));
static void PutLength ARGS((System_tFile File));
static void PutLeftHandSide ARGS((System_tFile File));
static void PutContinuation ARGS((System_tFile File));
static void PutFinalToProd ARGS((System_tFile File));

static BOOLEAN *G_1_InError;
static System_tFile *G_2_TableFile;

void Gen_GenDefaultActions
# ifdef __STDC__
()
# else
()
# endif
{
  Lists_tList act;
  TokenTab_PosType pos;
  Lists_tList com;
  TokenTab_PosType cpos;
  Strings_tString s;

  Lists_MakeList(&act);
  pos.Line = 0;
  pos.Column = 0;
  Lists_MakeList(&com);
  cpos.Line = 0;
  cpos.Column = 0;
  if ((WriteTok_Language == WriteTok_Modula3 || WriteTok_Language) == WriteTok_Modula2) {
    Strings_ArrayToString((STRING)"{", 1L, &s);
    Strings_Append(&s, EOL);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
    Strings_ArrayToString((STRING)"TYPE", 4L, &s);
    Strings_Append(&s, EOL);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
    Strings_ArrayToString((STRING)"   tParsAttribute = RECORD", 26L, &s);
    Strings_Append(&s, EOL);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
    Strings_ArrayToString((STRING)"                       Scan: Scanner.tScanAttribute", 51L, &s);
    Strings_Append(&s, EOL);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
    Strings_ArrayToString((STRING)"                    END;", 24L, &s);
    Strings_Append(&s, EOL);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
    Strings_ArrayToString((STRING)"}", 1L, &s);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
  } else {
    Strings_ArrayToString((STRING)"{", 1L, &s);
    Strings_Append(&s, EOL);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
    Strings_ArrayToString((STRING)"typedef struct    { tScanAttribute Scan; } tParsAttribute;", 58L, &s);
    Strings_Append(&s, EOL);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
    Strings_ArrayToString((STRING)"}", 1L, &s);
    Lists_Append(&act, (ADDRESS)StringMem_PutString(&s));
  }
  Actions_PutAction(Actions_Global, act, pos, com, cpos);
}

void Gen_GenCode
# ifdef __STDC__
(System_tFile Pars, System_tFile Def)
# else
(Pars, Def)
System_tFile Pars;
System_tFile Def;
# endif
{
  System_tFile out;
  Strings_tString C_1_line, rest, String1, String2;
  INTEGER N;

  FindKind();
  MakeNumbers();
  MakeLength();
  MakeLeftHandSide();
  Continue_MakeContinuation();
  Final_MakeFinalToProd();
  if (Gen_Trace) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)" Time :", 7L);
    IO_WriteI((System_tFile)IO_StdOutput, Times_StepTime(), 5L);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
  MakeTable();
  if (Gen_Trace) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)" Time :", 7L);
    IO_WriteI((System_tFile)IO_StdOutput, Times_StepTime(), 5L);
    IO_WriteNl((System_tFile)IO_StdOutput);
  }
  INC1(Compress_TableSize, Gen_LastTerminal);
  INC1(Compress_NTableSize, Gen_LastSymbol);
  if (WriteTok_Language == WriteTok_Modula3 || WriteTok_Language == WriteTok_Modula2) {
    ArgCheck_MakeFileName(Actions_ParserName, ArgCheck_Parser, 6L, (STRING)".Tab", 4L, FileName.A, 129L);
    out = OpenOutput(FileName.A, 129L);
    if (SysError_StatIsBad(out)) {
      Strings_ArrayToString(FileName.A, 129L, &String1);
      SysError_SysErrorMessageI(out, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(String1));
    } else {
      PutTables(out);
      Close(out);
    }
  }
  ArgCheck_MakeFileName(Actions_ParserName, ArgCheck_Parser, 6L, ArgCheck_ExtImp.A, 6L, FileName.A, 129L);
  out = IO_WriteOpen(FileName.A, 129L);
  Checks_CheckWriteOpen(&out, FileName.A, 129L);
  while (!IO_EndOfFile(Pars)) {
    Strings_ReadL(Pars, &C_1_line);
    if (Strings_Length(&C_1_line) >= 2 && Strings_Char(&C_1_line, 1) == '$') {
      switch (Strings_Char(&C_1_line, 2)) {
      case 'G':;
        Actions_WriteActions(Actions_Global, out, ArgCheck_LineFlag);
        break;
      case 'T':;
        GenLang_WriteConstants(out);
        break;
      case 'L':;
        Actions_WriteActions(Actions_Local, out, ArgCheck_LineFlag);
        break;
      case 'R':;
        PrepareReduceCode();
        GenLang_WriteReduceCode(out);
        break;
      case 'B':;
        Actions_WriteActions(Actions_Begin, out, ArgCheck_LineFlag);
        break;
      case 'C':;
        Actions_WriteActions(Actions_Close, out, ArgCheck_LineFlag);
        break;
      case 'X':;
        if (Gen_CaseFlag) {
          Strings_SubString(&C_1_line, 3, (Strings_tStringIndex)Strings_Length(&C_1_line), &rest);
          Strings_WriteL(out, &rest);
        }
        break;
      case 'W':;
        WriteTok_GenWrTo(out);
        break;
      case 'P':;
        PutBase(out);
        break;
      case 'Q':;
        PutNBase(out);
        break;
      case 'D':;
        PutDefault(out);
        break;
      case 'M':;
        PutControl(out);
        break;
      case 'N':;
        PutNNext(out);
        break;
      case 'K':;
        PutLength(out);
        break;
      case 'H':;
        PutLeftHandSide(out);
        break;
      case 'O':;
        PutContinuation(out);
        break;
      case 'F':;
        PutFinalToProd(out);
        break;
      case '@':;
        ArgCheck_ExpandLine(out, C_1_line);
        break;
      }
    } else {
      Strings_WriteL(out, &C_1_line);
    }
  }
  IO_WriteClose(out);
  if (ArgCheck_MakeDef && !IO_EndOfFile(Def)) {
    ArgCheck_MakeFileName(Actions_ParserName, ArgCheck_Parser, 6L, ArgCheck_ExtDef.A, 6L, FileName.A, 129L);
    out = IO_WriteOpen(FileName.A, 129L);
    Checks_CheckWriteOpen(&out, FileName.A, 129L);
    while (!IO_EndOfFile(Def)) {
      Strings_ReadL(Def, &C_1_line);
      if (Strings_Length(&C_1_line) >= 2 && Strings_Char(&C_1_line, 1) == '$') {
        switch (Strings_Char(&C_1_line, 2)) {
        case 'E':;
          Actions_WriteActions(Actions_Export, out, ArgCheck_LineFlag);
          break;
        case '@':;
          ArgCheck_ExpandLine(out, C_1_line);
          break;
        }
      } else {
        Strings_WriteL(out, &C_1_line);
      }
    }
    IO_WriteClose(out);
  }
}

static void FindKind
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex maxState, state;
  Automaton_tProduction prod;
  Automaton_tItemIndex item;
  CARDINAL RepCount;
  Automaton_tItemIndex LastItem;

  maxState = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_1 = 1, B_2 = maxState;

    if (B_1 <= B_2)
      for (state = B_1;; state += 1) {
        {
          register Automaton_tState *W_1 = &Automaton_StateArrayPtr->A[state - 1];

          if (W_1->Size == 1) {
            RepCount = 1;
            item = W_1->Items;
          } else {
            RepCount = 0;
            {
              LONGCARD B_3 = W_1->Items, B_4 = W_1->Items + W_1->Size - 1;

              if (B_3 <= B_4)
                for (item = B_3;; item += 1) {
                  {
                    register Automaton_tItem *W_2 = &Automaton_ItemArrayPtr->A[item - 1];

                    if (W_2->Rep != Automaton_NoRep) {
                      INC(RepCount);
                      LastItem = item;
                    }
                  }
                  if (item >= B_4) break;
                }
            }
            item = LastItem;
          }
          if (RepCount == 1) {
            {
              register Automaton_tItem *W_3 = &Automaton_ItemArrayPtr->A[item - 1];

              if (W_3->Rep == Automaton_RedRep) {
                prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_3->Prod]);
                {
                  register struct Automaton_9 *W_4 = prod;

                  if (W_4->Right.A[W_4->Len - 1] > TokenTab_MAXTerm) {
                    W_1->Kind = Automaton_sNonterm;
                  } else {
                    W_1->Kind = Automaton_sTerm;
                  }
                }
              } else {
                W_1->Kind = Automaton_sRead;
              }
            }
          } else {
            W_1->Kind = Automaton_sRead;
          }
        }
        if (state >= B_2) break;
      }
  }
}

static void MakeNumbers
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex maxState, state;
  Automaton_tProduction prod;
  Automaton_tStateIndex remember;

  Gen_FirstTerminal = FindFirstTerminal();
  Gen_LastTerminal = FindLastTerminal();
  Gen_NonTermOffset = TokenTab_MINNonTerm - Gen_LastTerminal - 1;
  Gen_FirstSymbol = Gen_FirstTerminal;
  Gen_LastSymbol = FindLastSymbol() - Gen_NonTermOffset;
  StateCnt = 0;
  maxState = Automaton_StateIndex;
  Gen_FirstState = 1;
  Gen_FirstReadState = StateCnt + 1;
  {
    Automaton_tStateIndex B_5 = 1, B_6 = maxState;

    if (B_5 <= B_6)
      for (state = B_5;; state += 1) {
        {
          register Automaton_tState *W_5 = &Automaton_StateArrayPtr->A[state - 1];

          if (W_5->Kind == Automaton_sRead) {
            INC(StateCnt);
            W_5->NewNumber = StateCnt;
          }
        }
        if (state >= B_6) break;
      }
  }
  Gen_LastReadState = StateCnt;
  Gen_FirstReadTermState = StateCnt + 1;
  {
    Automaton_tStateIndex B_7 = 1, B_8 = maxState;

    if (B_7 <= B_8)
      for (state = B_7;; state += 1) {
        {
          register Automaton_tState *W_6 = &Automaton_StateArrayPtr->A[state - 1];

          if (W_6->Kind == Automaton_sTerm) {
            prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[W_6->Items - 1].Prod]);
            if (prod->Left == Automaton_StartSymbol) {
              remember = state;
            } else {
              INC(StateCnt);
              W_6->NewNumber = StateCnt;
            }
          }
        }
        if (state >= B_8) break;
      }
  }
  Gen_LastReadTermState = StateCnt;
  Gen_FirstReadNonTermState = StateCnt + 1;
  {
    Automaton_tStateIndex B_9 = 1, B_10 = maxState;

    if (B_9 <= B_10)
      for (state = B_9;; state += 1) {
        {
          register Automaton_tState *W_7 = &Automaton_StateArrayPtr->A[state - 1];

          if (W_7->Kind == Automaton_sNonterm) {
            INC(StateCnt);
            W_7->NewNumber = StateCnt;
          }
        }
        if (state >= B_10) break;
      }
  }
  Gen_LastReadNonTermState = StateCnt;
  Gen_ReduceOffset = StateCnt;
  {
    register Automaton_tState *W_8 = &Automaton_StateArrayPtr->A[remember - 1];

    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[Automaton_ItemArrayPtr->A[W_8->Items - 1].Prod]);
    W_8->NewNumber = prod->ProdNo + Gen_ReduceOffset;
  }
  Gen_FirstReduceState = StateCnt + 1;
  Gen_LastReduceState = Gen_ReduceOffset + Automaton_ProdCount;
  Gen_StopState = Gen_FirstReduceState;
  Gen_LastState = Gen_LastReduceState;
}

static void MakeTable
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex maxState;
  Automaton_tStateIndex state;
  Automaton_tStateIndex index;
  Automaton_tStateIndex NewNum;
  Automaton_tStateIndex DefaultState;

  Default_CreateDefaultList();
  maxState = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_11 = 1, B_12 = maxState;

    if (B_11 <= B_12)
      for (state = B_11;; state += 1) {
        InitTableLine();
        NewNum = MakeTableLine(state);
        if (NewNum <= Gen_LastReadState) {
          Default_PutInDefaultList(NewNum, &TableLine);
        }
        if (state >= B_12) break;
      }
  }
  Default_ComputeDefaults();
  Compress_InitCompressTable();
  {
    Automaton_tStateIndex B_13 = 1, B_14 = Gen_LastReadState;

    if (B_13 <= B_14)
      for (index = B_13;; index += 1) {
        NewNum = Default_GetTSortState(index);
        Default_GetDefaultTableLine(NewNum, &TableLine, &DefaultState);
        Compress_CompressTableLine(NewNum, DefaultState, &TableLine);
        if (index >= B_14) break;
      }
  }
  Compress_InitCompressNTable();
  {
    Automaton_tStateIndex B_15 = 1, B_16 = Gen_LastReadState;

    if (B_15 <= B_16)
      for (index = B_15;; index += 1) {
        NewNum = Default_GetNSortState(index);
        Default_GetDefaultTableLine(NewNum, &TableLine, &DefaultState);
        Compress_CompressNTableLine(NewNum, &TableLine);
        if (index >= B_16) break;
      }
  }
}

static void InitTableLine
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tStateIndex state;
  TokenTab_Vocabulary symbol;

  {
    TokenTab_Vocabulary B_17 = Gen_FirstSymbol, B_18 = Gen_LastSymbol;

    if (B_17 <= B_18)
      for (symbol = B_17;; symbol += 1) {
        TableLine.A[symbol] = Gen_NoState;
        if (symbol >= B_18) break;
      }
  }
}

static Automaton_tStateIndex MakeTableLine
# ifdef __STDC__
(Automaton_tStateIndex state)
# else
(state)
Automaton_tStateIndex state;
# endif
{
  Automaton_tStateIndex RedState;
  Automaton_tStateIndex maxState;
  Automaton_tItemIndex item;
  Automaton_tProduction prod;
  Sets_tSet Look;
  TokenTab_Terminal t;

  Sets_MakeSet(&Look, (Sets_tElement)TokenTab_MAXTerm);
  {
    register Automaton_tState *W_9 = &Automaton_StateArrayPtr->A[state - 1];

    if (W_9->Kind == Automaton_sRead) {
      {
        LONGCARD B_19 = W_9->Items, B_20 = W_9->Items + W_9->Size - 1;

        if (B_19 <= B_20)
          for (item = B_19;; item += 1) {
            {
              register Automaton_tItem *W_10 = &Automaton_ItemArrayPtr->A[item - 1];

              switch (W_10->Rep) {
              case Automaton_TermRep:;
                TableLine.A[W_10->Read] = Automaton_StateArrayPtr->A[W_10->Next - 1].NewNumber;
                break;
              case Automaton_NonTermRep:;
                TableLine.A[W_10->Read - Gen_NonTermOffset] = Automaton_StateArrayPtr->A[W_10->Next - 1].NewNumber;
                break;
              case Automaton_RedRep:;
                prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[W_10->Prod]);
                RedState = Gen_ReduceOffset + prod->ProdNo;
                Sets_Assign(&Look, W_10->Set);
                while (!Sets_IsEmpty(Look)) {
                  t = Sets_Extract(&Look);
                  TableLine.A[t] = RedState;
                }
                break;
              default :
                break;
              }
            }
            if (item >= B_20) break;
          }
      }
    }
    Sets_ReleaseSet(&Look);
    return W_9->NewNumber;
  }
}

static void MakeLength
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tProduction prod;
  Automaton_tProdIndex index, prodno;

  Gen_LengthCount = Automaton_ProdCount;
  DynArray_MakeArray((ADDRESS *)&Gen_Length, &Gen_LengthCount, (LONGINT)Gen_ElmtSize);
  index = 0;
  {
    Automaton_tProdIndex B_21 = 1, B_22 = Automaton_ProdCount;

    if (B_21 <= B_22)
      for (prodno = B_21;; prodno += 1) {
        prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
        Gen_Length->A[prodno - 1] = prod->Len;
        index = Automaton_NextProdIndex(index);
        if (prodno >= B_22) break;
      }
  }
}

static void MakeLeftHandSide
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tProduction prod;
  Automaton_tProdIndex index, prodno;

  Gen_LeftHandSideCount = Automaton_ProdCount;
  DynArray_MakeArray((ADDRESS *)&Gen_LeftHandSide, &Gen_LeftHandSideCount, (LONGINT)Gen_ElmtSize);
  index = 0;
  {
    Automaton_tProdIndex B_23 = 1, B_24 = Automaton_ProdCount;

    if (B_23 <= B_24)
      for (prodno = B_23;; prodno += 1) {
        prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
        Gen_LeftHandSide->A[prodno - 1] = prod->Left - Gen_NonTermOffset;
        index = Automaton_NextProdIndex(index);
        if (prodno >= B_24) break;
      }
  }
}

static TokenTab_Vocabulary FindFirstTerminal
# ifdef __STDC__
()
# else
()
# endif
{
  return 0;
}

static TokenTab_Vocabulary FindLastTerminal
# ifdef __STDC__
()
# else
()
# endif
{
  TokenTab_Vocabulary sym;

  sym = TokenTab_MAXTerm;
  for (;;) {
    if (TokenTab_GetTokenType(sym) == TokenTab_Term) {
      return sym;
    }
    DEC(sym);
  } EXIT_1:;
}

static TokenTab_Vocabulary FindLastSymbol
# ifdef __STDC__
()
# else
()
# endif
{
  TokenTab_Vocabulary sym;

  sym = TokenTab_MAXNonTerm;
  for (;;) {
    if (TokenTab_GetTokenType(sym) != TokenTab_None) {
      return sym;
    }
    DEC(sym);
  } EXIT_2:;
}

CARDINAL Gen_StartState
# ifdef __STDC__
()
# else
()
# endif
{
  return Automaton_StateArrayPtr->A[1 - 1].NewNumber;
}

static void PrepareReduceCode
# ifdef __STDC__
()
# else
()
# endif
{
  Automaton_tProdIndex index;
  Automaton_tProduction prod;
  Automaton_tStateIndex maxState, state;
  Automaton_tProdIndex maxProdIndex;
  LONGINT u;
  Automaton_tItemIndex item;

  index = 0;
  state = Gen_ReduceOffset;
  maxProdIndex = Automaton_ProdIndex;
  while (index < maxProdIndex) {
    INC(state);
    prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
    {
      register Automaton_tIndexList *W_11 = &prod->Reduce;

      W_11->Count = InitReduceCount;
      DynArray_MakeArray((ADDRESS *)&W_11->Array, &W_11->Count, (LONGINT)sizeof(Automaton_tIndex));
      W_11->Used = 1;
      W_11->Array->A[1 - 1] = state;
    }
    index = Automaton_NextProdIndex(index);
  }
  maxState = Automaton_StateIndex;
  {
    Automaton_tStateIndex B_25 = 1, B_26 = maxState;

    if (B_25 <= B_26)
      for (state = B_25;; state += 1) {
        {
          register Automaton_tState *W_12 = &Automaton_StateArrayPtr->A[state - 1];

          if (W_12->Kind == Automaton_sTerm || W_12->Kind == Automaton_sNonterm) {
            item = W_12->Items;
            for (;;) {
              if (Automaton_ItemArrayPtr->A[item - 1].Rep != Automaton_NoRep) {
                goto EXIT_3;
              }
              INC(item);
            } EXIT_3:;
            if (W_12->NewNumber <= Gen_ReduceOffset) {
              index = Automaton_ItemArrayPtr->A[item - 1].Prod;
              prod = (Automaton_tProduction)ADR(Automaton_ProdArrayPtr->A[index]);
              {
                register Automaton_tIndexList *W_13 = &prod->Reduce;

                INC(W_13->Used);
                if (W_13->Used > W_13->Count) {
                  DynArray_ExtendArray((ADDRESS *)&W_13->Array, &W_13->Count, (LONGINT)sizeof(Automaton_tIndex));
                }
                W_13->Array->A[W_13->Used - 1] = W_12->NewNumber;
              }
            }
          }
        }
        if (state >= B_26) break;
      }
  }
}

static void PutTable
# ifdef __STDC__
(Gen_TableElmt Length, ADDRESS Address)
# else
(Length, Address)
Gen_TableElmt Length;
ADDRESS Address;
# endif
{
  INTEGER N;
  Strings_tString string;

  N = Write(*G_2_TableFile, ADR(Length), (LONGINT)Gen_ElmtSize);
  if (SysError_StatIsBad(N)) {
    Strings_ArrayToString(FileName.A, 129L, &string);
    SysError_SysErrorMessageI(N, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(string));
    *G_1_InError = TRUE;
    return;
  }
  N = Write(*G_2_TableFile, Address, (LONGINT)Length);
  if (SysError_StatIsBad(N)) {
    Strings_ArrayToString(FileName.A, 129L, &string);
    SysError_SysErrorMessageI(N, (LONGCARD)Errors_eError, (LONGCARD)Errors_eString, ADR(string));
    *G_1_InError = TRUE;
    return;
  }
}

static void PutTables
# ifdef __STDC__
(System_tFile TableFile)
# else
(TableFile)
System_tFile TableFile;
# endif
{
  BOOLEAN InError;
  CARDINAL BlockSize, i;
  BOOLEAN *L_1;
  System_tFile *L_2;

  L_1 = G_1_InError;
  G_1_InError = &InError;
  L_2 = G_2_TableFile;
  G_2_TableFile = &TableFile;
  BlockSize = 64000 / sizeof(ControlType);
  InError = FALSE;
  PutTable((Gen_LastReadState + 1) * Gen_ElmtSize, (ADDRESS)Compress_Base);
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  PutTable((Gen_LastReadState + 1) * Gen_ElmtSize, (ADDRESS)Compress_NBase);
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  PutTable((Gen_LastReadState + 1) * Gen_ElmtSize, (ADDRESS)Compress_Default);
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  PutTable((SHORTCARD)((Compress_NTableSize - Gen_LastTerminal) * sizeof(Gen_TableElmt)), ADR(Compress_NNext->A[Gen_LastTerminal + 1]));
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  PutTable((Gen_LastReduceState - Gen_FirstReduceState + 1) * Gen_ElmtSize, (ADDRESS)Gen_Length);
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  PutTable((Gen_LastReduceState - Gen_FirstReduceState + 1) * Gen_ElmtSize, (ADDRESS)Gen_LeftHandSide);
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  PutTable((Gen_LastReadState + 1) * Gen_ElmtSize, (ADDRESS)Gen_Continuation);
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  PutTable((Gen_LastReadNonTermState - Gen_FirstReadTermState + 1) * Gen_ElmtSize, (ADDRESS)Gen_FinalToProd);
  if (InError) {
    G_1_InError = L_1;
    G_2_TableFile = L_2;
    return;
  }
  i = 0;
  while (i <= Compress_TableSize) {
    PutTable((SHORTCARD)(General_Min((LONGINT)BlockSize, (LONGINT)(Compress_TableSize + 1 - i)) * sizeof(ControlType)), ADR(Compress_Control->A[i]));
    if (InError) {
      G_1_InError = L_1;
      G_2_TableFile = L_2;
      return;
    }
    INC1(i, BlockSize);
  }
  G_1_InError = L_1;
  G_2_TableFile = L_2;
}

static void PutBase
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_27 = 0, B_28 = Gen_LastReadState;

    if (B_27 <= B_28)
      for (i = B_27;; i += 1) {
        IO_WriteS(File, (STRING)"& yyTComb [", 11L);
        IO_WriteI(File, (LONGINT)Compress_Base->A[i], 0L);
        IO_WriteS(File, (STRING)"],", 2L);
        IO_WriteNl(File);
        if (i >= B_28) break;
      }
  }
}

static void PutNBase
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_29 = 0, B_30 = Gen_LastReadState;

    if (B_29 <= B_30)
      for (i = B_29;; i += 1) {
        IO_WriteS(File, (STRING)"& yyNComb [", 11L);
        IO_WriteI(File, (LONGINT)((SHORTINT)Compress_NBase->A[i] - (SHORTINT)Gen_LastTerminal - 1), 0L);
        IO_WriteS(File, (STRING)"],", 2L);
        IO_WriteNl(File);
        if (i >= B_30) break;
      }
  }
}

static void PutDefault
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_31 = 0, B_32 = Gen_LastReadState;

    if (B_31 <= B_32)
      for (i = B_31;; i += 1) {
        IO_WriteI(File, (LONGINT)Compress_Default->A[i], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_32) break;
      }
  }
}

static void PutControl
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  CARDINAL i;

  {
    LONGCARD B_33 = 0, B_34 = Compress_TableSize;

    if (B_33 <= B_34)
      for (i = B_33;; i += 1) {
        IO_WriteC(File, '{');
        IO_WriteI(File, (LONGINT)Compress_Control->A[i].Check, 0L);
        IO_WriteS(File, (STRING)", ", 2L);
        IO_WriteI(File, (LONGINT)Compress_Control->A[i].Next, 0L);
        IO_WriteS(File, (STRING)"},", 2L);
        IO_WriteNl(File);
        if (i >= B_34) break;
      }
  }
}

static void PutNNext
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_35 = Gen_LastTerminal + 1, B_36 = Compress_NTableSize;

    if (B_35 <= B_36)
      for (i = B_35;; i += 1) {
        IO_WriteI(File, (LONGINT)Compress_NNext->A[i], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_36) break;
      }
  }
}

static void PutLength
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_37 = 1, B_38 = Automaton_ProdCount;

    if (B_37 <= B_38)
      for (i = B_37;; i += 1) {
        IO_WriteI(File, (LONGINT)Gen_Length->A[i - 1], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_38) break;
      }
  }
}

static void PutLeftHandSide
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_39 = 1, B_40 = Automaton_ProdCount;

    if (B_39 <= B_40)
      for (i = B_39;; i += 1) {
        IO_WriteI(File, (LONGINT)Gen_LeftHandSide->A[i - 1], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_40) break;
      }
  }
}

static void PutContinuation
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_41 = 0, B_42 = Gen_LastReadState;

    if (B_41 <= B_42)
      for (i = B_41;; i += 1) {
        IO_WriteI(File, (LONGINT)Gen_Continuation->A[i], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_42) break;
      }
  }
}

static void PutFinalToProd
# ifdef __STDC__
(System_tFile File)
# else
(File)
System_tFile File;
# endif
{
  Automaton_tStateIndex i;

  {
    Automaton_tStateIndex B_43 = Gen_FirstReadTermState, B_44 = Gen_LastReadNonTermState;

    if (B_43 <= B_44)
      for (i = B_43;; i += 1) {
        IO_WriteI(File, (LONGINT)Gen_FinalToProd->A[i - Gen_FirstReadTermState], 0L);
        IO_WriteC(File, ',');
        IO_WriteNl(File);
        if (i >= B_44) break;
      }
  }
}

void Gen__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    TokenTab__init();
    Automaton__init();
    IO__init();
    TokenTab__init();
    Actions__init();
    ArgCheck__init();
    ArgCheck__init();
    Automaton__init();
    Compress__init();
    Continue__init();
    Checks__init();
    Default__init();
    DynArray__init();
    Errors__init();
    Final__init();
    General__init();
    GenLang__init();
    IO__init();
    Lists__init();
    Lists__init();
    Sets__init();
    Strings__init();
    StringMem__init();
    Strings__init();
    Idents__init();
    SysError__init();
    System__init();
    System__init();
    Times__init();
    TokenTab__init();
    WriteTok__init();

    Gen_ElmtSize = sizeof(Gen_TableElmt);
    Gen_Trace = FALSE;
    Gen_CaseFlag = FALSE;
  }
}
