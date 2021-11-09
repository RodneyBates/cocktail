#define DEFINITION_Stack

#define Stack_NoBound   65535
typedef ADDRESS Stack_tElmt;
typedef struct Stack_1 {
    LONGINT StackPtr;
    LONGINT StackSize;
    struct Stack_2 {
        Stack_tElmt A[Stack_NoBound + 1];
    } *Array;
} Stack_tStack;
extern void Stack_MakeStack ARGS((Stack_tStack *s));
extern void Stack_ReleaseStack ARGS((Stack_tStack *s));
extern void Stack_ClearStack ARGS((Stack_tStack *s));
extern BOOLEAN Stack_IsEmptyStack ARGS((Stack_tStack s));
extern void Stack_Push ARGS((Stack_tStack *s, Stack_tElmt e));
extern Stack_tElmt Stack_Pop ARGS((Stack_tStack *s));
extern Stack_tElmt Stack_Top ARGS((Stack_tStack *s));
extern INTEGER Stack_Depth ARGS((Stack_tStack s));
extern void Stack_Assign ARGS((Stack_tStack *s1, Stack_tStack s2));
extern void Stack__init();
