#define DEFINITION_Arguments

typedef struct Arguments_1 {
    struct Arguments_2 {
        CHAR A[999 + 1];
    } *A[999 + 1];
} *Arguments_ArgTable;
extern void GetArgs ARGS((INTEGER *argc, Arguments_ArgTable *argv));
extern void GetEnv ARGS((Arguments_ArgTable *env));
extern void Arguments__init();
