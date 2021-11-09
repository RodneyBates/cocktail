#define DEFINITION_ArgCheck

#define ArgCheck_C        0
#define ArgCheck_MODULA2        1
typedef unsigned char ArgCheck_tLanguage;
extern BOOLEAN ArgCheck_DEF, ArgCheck_IMP, ArgCheck_ERR, ArgCheck_SCA, ArgCheck_PAR, ArgCheck_LINE;
extern ArgCheck_tLanguage ArgCheck_LANGUAGE;
extern struct ArgCheck_1 {
    CHAR A[127 + 1];
} ArgCheck_SourceFileName;
extern BOOLEAN ArgCheck_TREE, ArgCheck_TABLE, ArgCheck_CODES, ArgCheck_QUERY;
extern void ArgCheck_CheckArgs ARGS(());
extern void ArgCheck__init();
