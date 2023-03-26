#define DEFINITION_Character

extern BOOLEAN Character_IsEqual ARGS((CHAR c1[], LONGCARD , CHAR c2[], LONGCARD ));
extern CARDINAL Character_Length ARGS((CHAR c[], LONGCARD ));
extern void Character_Assign ARGS((CHAR s1[], LONGCARD , CHAR s2[], LONGCARD ));
extern void Character__init();
