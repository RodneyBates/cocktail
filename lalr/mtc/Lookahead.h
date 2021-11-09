#define DEFINITION_Lookahead

typedef void (*Lookahead_ConflictProc) ARGS((BOOLEAN));
extern BOOLEAN Lookahead_NoConflict;
extern void Lookahead_ComputeLALR ARGS(());
extern void Lookahead__init();
