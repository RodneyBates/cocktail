#define DEFINITION_Queues

typedef LONGCARD Queues_UnBounded;
typedef ADDRESS Queues_tElmt;
typedef struct Queues_1 {
    Queues_tElmt A[10000 + 1];
} *Queues_tArrayPtr;
typedef INTEGER Queues_tIndex;
typedef struct Queues_2 {
    INTEGER Size, First, Last;
    Queues_tArrayPtr Array;
} Queues_tQueue;
extern void Queues_MakeQueue ARGS((Queues_tQueue *Queue));
extern void Queues_ReleaseQueue ARGS((Queues_tQueue *Queue));
extern void Queues_AssignEmpty ARGS((Queues_tQueue *Queue));
extern void Queues_Append ARGS((Queues_tQueue *Queue, Queues_tElmt Elmt));
extern Queues_tElmt Queues_Head ARGS((Queues_tQueue Queue));
extern Queues_tElmt Queues_Last ARGS((Queues_tQueue Queue));
extern void Queues_ClearHead ARGS((Queues_tQueue *Queue));
extern void Queues_ClearLast ARGS((Queues_tQueue *Queue));
extern void Queues_Tail ARGS((Queues_tQueue *Queue));
extern void Queues_Insert ARGS((Queues_tQueue *Queue, Queues_tElmt Elmt));
extern BOOLEAN Queues_IsEmpty ARGS((Queues_tQueue Queue));
extern Queues_tIndex Queues_Length ARGS((Queues_tQueue Queue));
extern Queues_tElmt Queues_GetElement ARGS((Queues_tQueue Queue, Queues_tIndex Pos));
extern void Queues_Assign ARGS((Queues_tQueue *Queue1, Queues_tQueue Queue2));
extern Queues_tElmt Queues_TakeHead ARGS((Queues_tQueue *Queue));
extern Queues_tElmt Queues_TakeLast ARGS((Queues_tQueue *Queue));
extern void Queues__init();
