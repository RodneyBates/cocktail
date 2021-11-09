#define DEFINITION_ArgCheck

extern CHAR ArgCheck_cVersion[];
extern BOOLEAN ArgCheck_TEST;
extern BOOLEAN ArgCheck_DEF;
extern BOOLEAN ArgCheck_IMP;
extern BOOLEAN ArgCheck_BU;
extern struct ArgCheck_1 {
    CHAR A[255 + 1];
} ArgCheck_SourceFileName;
extern BOOLEAN ArgCheck_TREE;
extern BOOLEAN ArgCheck_GRAM;
extern BOOLEAN ArgCheck_MATCH;
extern BOOLEAN ArgCheck_AUTO;
extern BOOLEAN ArgCheck_DEBUG;
extern void ArgCheck_CheckArgs ARGS(());
extern void ArgCheck__init();
