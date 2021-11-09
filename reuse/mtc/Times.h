#define DEFINITION_Times

extern LONGINT Times_CpuTime ARGS(());
extern LONGINT Times_StepTime ARGS(());
extern void Times_WriteStepTime ARGS((CHAR Text[], LONGCARD ));
extern void Times__init();
