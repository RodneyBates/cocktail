#define DEFINITION_ScanTabs

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#define ScanTabs_NoRule   0
#define ScanTabs_NoAction   0
#define ScanTabs_EofAction   1
#define ScanTabs_EolAction   2
#define ScanTabs_EobAction   3
#define ScanTabs_TabAction   4
#define ScanTabs_CopyAction   5
#define ScanTabs_BlankAction   6
typedef SHORTCARD ScanTabs_TableElmt;
typedef ScanTabs_TableElmt ScanTabs_StateRange;
typedef ScanTabs_TableElmt ScanTabs_RuleRange;
typedef ScanTabs_TableElmt ScanTabs_RuleType;
typedef CARDINAL ScanTabs_TableRange;
typedef ScanTabs_TableElmt ScanTabs_ActionType;
typedef struct ScanTabs_1 {
    ScanTabs_TableElmt Check, Next;
} ScanTabs_ControlType;
typedef struct ScanTabs_2 {
    ScanTabs_RuleRange A[100000 + 1];
} ScanTabs_RuleBase;
typedef struct ScanTabs_3 {
    ScanTabs_RuleType A[100000 + 1];
} ScanTabs_Rule;
typedef struct ScanTabs_4 {
    ScanTabs_TableElmt A[100000 + 1];
} ScanTabs_Base;
typedef struct ScanTabs_5 {
    ScanTabs_StateRange A[100000 + 1];
} ScanTabs_Default;
typedef struct ScanTabs_6 {
    ScanTabs_ControlType A[100000 + 1];
} ScanTabs_Control;
typedef struct ScanTabs_7 {
    ScanTabs_StateRange A[100000 + 1];
} ScanTabs_EobTrans;
typedef struct ScanTabs_8 {
    ScanTabs_StateRange A[100000 + 1];
} ScanTabs_Context;
typedef struct ScanTabs_9 {
    ScanTabs_ActionType A[100000 + 1];
} ScanTabs_Action;
extern ScanTabs_RuleBase *ScanTabs_RuleBasePtr;
extern LONGINT ScanTabs_RuleBaseSize;
extern ScanTabs_Rule *ScanTabs_RulePtr;
extern LONGINT ScanTabs_RuleSize;
extern ScanTabs_Base *ScanTabs_BasePtr;
extern LONGINT ScanTabs_BaseSize;
extern ScanTabs_Default *ScanTabs_DefaultPtr;
extern LONGINT ScanTabs_DefaultSize;
extern ScanTabs_Control *ScanTabs_ControlPtr;
extern LONGINT ScanTabs_ControlSize;
extern ScanTabs_EobTrans *ScanTabs_EobTransPtr;
extern LONGINT ScanTabs_EobTransSize;
extern ScanTabs_Context *ScanTabs_ContextPtr;
extern LONGINT ScanTabs_ContextSize;
extern ScanTabs_Action *ScanTabs_ActionPtr;
extern LONGINT ScanTabs_ActionSize;
extern ScanTabs_ActionType ScanTabs_ActionNr;
extern ScanTabs_TableRange ScanTabs_TableSize;
extern ScanTabs_TableRange ScanTabs_TableEntries;
extern void ScanTabs_MakeTables ARGS((BOOLEAN ReduceCaseSize));
extern void ScanTabs_CompressTables ARGS((SHORTINT Optimize));
extern void ScanTabs_PutTables ARGS((BOOLEAN ReduceCaseSize));
extern void ScanTabs_WriteTables ARGS(());
extern void ScanTabs_QueryTables ARGS(());
extern void ScanTabs_PutComb ARGS((IO_tFile File));
extern void ScanTabs_PutBase ARGS((IO_tFile File));
extern void ScanTabs_PutDefault ARGS((IO_tFile File));
extern void ScanTabs_PutEobTrans ARGS((IO_tFile File));
extern void ScanTabs_PutAction ARGS((IO_tFile File));
extern void ScanTabs__init();
