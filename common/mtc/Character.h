#define DEFINITION_Character

extern BOOLEAN Character_IsEqual ARGS((CHAR s1[], LONGCARD , CHAR s2[], LONGCARD ));
extern INTEGER Character_Length ARGS((CHAR s[], LONGCARD ));
extern CHAR Character_Char ARGS((CHAR s[], LONGCARD , INTEGER i));
extern void Character_Append ARGS((CHAR s[], LONGCARD , CHAR c));
extern void Character_Concatenate ARGS((CHAR s1[], LONGCARD , CHAR s2[], LONGCARD ));
extern void Character_SubString ARGS((CHAR s1[], LONGCARD , INTEGER from, INTEGER to, CHAR s2[], LONGCARD ));
extern void Character_Assign ARGS((CHAR s1[], LONGCARD , CHAR s2[], LONGCARD ));
extern void Character__init();
