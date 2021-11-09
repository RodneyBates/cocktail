#define DEFINITION_ArgCheck

extern BOOLEAN ArgCheck_Line;
extern BOOLEAN ArgCheck_Generate;
extern BOOLEAN ArgCheck_NoActionFlag;
extern struct ArgCheck_1 {
    CHAR A[127 + 1];
} ArgCheck_SourceFileName;
extern void ArgCheck_ArgCheck ARGS(());
extern void ArgCheck__init();
