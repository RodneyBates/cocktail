#define DEFINITION_Queue

extern void Queue_MakeQueue ARGS((SHORTCARD Size));
extern void Queue_ReleaseQueue ARGS(());
extern BOOLEAN Queue_IsEmpty ARGS(());
extern void Queue_Enqueue ARGS((SHORTCARD Elmt));
extern SHORTCARD Queue_Dequeue ARGS(());
extern BOOLEAN Queue_IsElement ARGS((SHORTCARD Elmt));
extern void Queue__init();
