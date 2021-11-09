#define DEFINITION_Compress

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

typedef SHORTCARD Compress_TableElmt;
typedef struct Compress_1 {
    Compress_TableElmt Check, Next;
} Compress_ControlType;
extern struct Compress_2 {
    Compress_ControlType A[Automaton_Infinite2 + 1];
} *Compress_Control;
extern struct Compress_3 {
    Compress_TableElmt A[Automaton_Infinite + 1];
} *Compress_Base;
extern struct Compress_4 {
    Compress_TableElmt A[Automaton_Infinite + 1];
} *Compress_Default;
extern LONGINT Compress_ControlCount, Compress_BaseCount, Compress_DefaultCount;
extern Automaton_tIndex Compress_TableMax;
extern Automaton_tIndex Compress_TableSize;
extern struct Compress_5 {
    Compress_TableElmt A[Automaton_Infinite + 1];
} *Compress_NNext;
extern struct Compress_6 {
    Compress_TableElmt A[Automaton_Infinite + 1];
} *Compress_NBase;
extern LONGINT Compress_NNextCount;
extern LONGINT Compress_NBaseCount;
extern Automaton_tIndex Compress_NTableMax;
extern Automaton_tIndex Compress_NTableSize;
extern Compress_TableElmt Compress_ElmtSize;
extern CARDINAL Compress_Filling;
extern CARDINAL Compress_NFilling;
extern void Compress_InitCompressTable ARGS(());
extern void Compress_CompressTableLine ARGS((Automaton_tStateIndex State, Automaton_tStateIndex DefaultState, Gen_tTableLine *TableLine));
extern void Compress_InitCompressNTable ARGS(());
extern void Compress_CompressNTableLine ARGS((Automaton_tStateIndex State, Gen_tTableLine *TableLine));
extern void Compress__init();
