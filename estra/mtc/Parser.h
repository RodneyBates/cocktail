#define DEFINITION_Parser

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern Tree_tTree Parser_AST;
extern struct Parser_1 {
    CHAR A[128 + 1];
} Parser_ParsTabName;
extern void Parser_TokenName ARGS((SHORTCARD Token, CHAR Name[], LONGCARD ));
extern CARDINAL Parser_Parser ARGS(());
extern void Parser_CloseParser ARGS(());
extern void Parser__init();
