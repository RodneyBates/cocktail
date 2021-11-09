#include "SYSTEM_.h"

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Compress
#include "Compress.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Times
#include "Times.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_Infos
#include "Infos.h"
#endif




void Infos_WriteInfo
# ifdef __STDC__
(IO_tFile f)
# else
(f)
IO_tFile f;
# endif
{
  CARDINAL NSize;

  IO_WriteS(f, (STRING)"Statistik", 9L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"-------------------", 19L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Terminals   : ", 14L);
  IO_WriteI(f, (LONGINT)(TokenTab_MAXTerm - TokenTab_MINTerm + 1), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Nonterminals: ", 14L);
  IO_WriteI(f, (LONGINT)(TokenTab_MAXNonTerm - TokenTab_MINNonTerm + 1), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Productions : ", 14L);
  IO_WriteI(f, (LONGINT)Automaton_ProdCount, 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Prod (Bytes): ", 14L);
  IO_WriteI(f, Automaton_ProdIndex * sizeof(WORD), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Items       :", 13L);
  IO_WriteI(f, Automaton_ItemIndex, 6L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"LR(0)-States: ", 14L);
  IO_WriteI(f, Automaton_StateIndex, 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"ReadStates  : ", 14L);
  IO_WriteI(f, (LONGINT)(Gen_LastReadState - Gen_FirstReadState + 1), 5L);
  IO_WriteNl(f);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Base        : ", 14L);
  IO_WriteI(f, (LONGINT)((Gen_LastReadState + 1) * 2), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"NBase       : ", 14L);
  IO_WriteI(f, (LONGINT)((Gen_LastReadState + 1) * 2), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Default     : ", 14L);
  IO_WriteI(f, (LONGINT)((Gen_LastReadState + 1) * 2), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Terminals   : ", 14L);
  IO_WriteI(f, (LONGINT)((Compress_TableSize + 1) * 4), 5L);
  IO_WriteI(f, (LONGINT)((Compress_Filling * 100 + Compress_TableSize / 2) / Compress_TableSize), 4L);
  IO_WriteS(f, (STRING)"%", 1L);
  IO_WriteNl(f);
  NSize = Compress_NTableSize - Gen_LastTerminal;
  IO_WriteS(f, (STRING)"Nonterminals: ", 14L);
  IO_WriteI(f, (LONGINT)(NSize * 2), 5L);
  IO_WriteI(f, (LONGINT)((Compress_NFilling * 100 + NSize / 2) / NSize), 4L);
  IO_WriteS(f, (STRING)"%", 1L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Length      : ", 14L);
  IO_WriteI(f, (LONGINT)((Gen_LastReduceState - Gen_FirstReduceState + 1) * 2), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Left        : ", 14L);
  IO_WriteI(f, (LONGINT)((Gen_LastReduceState - Gen_FirstReduceState + 1) * 2), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Continuation: ", 14L);
  IO_WriteI(f, (LONGINT)((Gen_LastReadState + 1) * 2), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"FinalToProd : ", 14L);
  IO_WriteI(f, (LONGINT)((Gen_LastReadNonTermState - Gen_FirstReadTermState + 1) * 2), 5L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Cpu-Time [ms]", 13L);
  IO_WriteI(f, Times_CpuTime(), 6L);
  IO_WriteNl(f);
  IO_WriteS(f, (STRING)"Memory used  ", 13L);
  IO_WriteI(f, (LONGINT)Memory_MemoryUsed, 6L);
  IO_WriteNl(f);
}

void Infos__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Automaton__init();
    Compress__init();
    Gen__init();
    IO__init();
    Memory__init();
    Times__init();
    TokenTab__init();

  }
}
