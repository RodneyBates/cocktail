#include "SYSTEM_.h"

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Layout
#include "Layout.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif


static SHORTCARD indent;


Tree_tTree Tree_MakeTree1
# ifdef __STDC__
(SHORTCARD pRule, Tree_tTree pSon1)
# else
(pRule, pSon1)
SHORTCARD pRule;
Tree_tTree pSon1;
# endif
{
  Tree_tTree Tree;

  Tree = (Tree_tTree)Memory_Alloc((LONGINT)sizeof(Tree_Node1));
  {
    register Tree_Node1 *W_1 = &Tree->U_1.V_2.vNode1;

    W_1->Rule = pRule;
    W_1->Son1 = pSon1;
  }
  return Tree;
}

Tree_tTree Tree_MakeTree2
# ifdef __STDC__
(SHORTCARD pRule, Tree_tTree pSon1, Tree_tTree pSon2)
# else
(pRule, pSon1, pSon2)
SHORTCARD pRule;
Tree_tTree pSon1, pSon2;
# endif
{
  Tree_tTree Tree;

  Tree = (Tree_tTree)Memory_Alloc((LONGINT)sizeof(Tree_Node2));
  {
    register Tree_Node2 *W_2 = &Tree->U_1.V_3.vNode2;

    W_2->Rule = pRule;
    W_2->Son1 = pSon1;
    W_2->Son2 = pSon2;
  }
  return Tree;
}

Tree_tTree Tree_MakeTreeCh
# ifdef __STDC__
(SHORTCARD pRule, CHAR pCh)
# else
(pRule, pCh)
SHORTCARD pRule;
CHAR pCh;
# endif
{
  Tree_tTree Tree;

  Tree = (Tree_tTree)Memory_Alloc((LONGINT)sizeof(Tree_NodeCh));
  {
    register Tree_NodeCh *W_3 = &Tree->U_1.V_4.vNodeCh;

    W_3->Rule = pRule;
    W_3->Ch = pCh;
  }
  return Tree;
}

Tree_tTree Tree_MakeTreeSet
# ifdef __STDC__
(SHORTCARD pRule, Sets_tSet pSet)
# else
(pRule, pSet)
SHORTCARD pRule;
Sets_tSet pSet;
# endif
{
  Tree_tTree Tree;

  Tree = (Tree_tTree)Memory_Alloc((LONGINT)sizeof(Tree_NodeSet));
  {
    register Tree_NodeSet *W_4 = &Tree->U_1.V_5.vNodeSet;

    W_4->Rule = pRule;
    W_4->Set = pSet;
  }
  return Tree;
}

Tree_tTree Tree_MakeTreeString
# ifdef __STDC__
(SHORTCARD pRule, StringMem_tStringRef pString)
# else
(pRule, pString)
SHORTCARD pRule;
StringMem_tStringRef pString;
# endif
{
  Tree_tTree Tree;

  Tree = (Tree_tTree)Memory_Alloc((LONGINT)sizeof(Tree_NodeString));
  {
    register Tree_NodeString *W_5 = &Tree->U_1.V_6.vNodeString;

    W_5->Rule = pRule;
    W_5->String = pString;
  }
  return Tree;
}

Tree_tTree Tree_MakeTreeRule
# ifdef __STDC__
(SHORTCARD pRule, Tree_tTree pPatterns, Texts_tText pTargetCode, SHORTCARD pLine, SHORTCARD pCodeMode, SHORTCARD pRuleNr)
# else
(pRule, pPatterns, pTargetCode, pLine, pCodeMode, pRuleNr)
SHORTCARD pRule;
Tree_tTree pPatterns;
Texts_tText pTargetCode;
SHORTCARD pLine, pCodeMode, pRuleNr;
# endif
{
  Tree_tTree Tree;

  Tree = (Tree_tTree)Memory_Alloc((LONGINT)sizeof(Tree_NodeRule));
  {
    register Tree_NodeRule *W_6 = &Tree->U_1.V_7.vNodeRule;

    W_6->Rule = pRule;
    W_6->Patterns = pPatterns;
    W_6->TargetCode = pTargetCode;
    W_6->Line = pLine;
    W_6->CodeMode = pCodeMode;
    W_6->RuleNr = pRuleNr;
  }
  return Tree;
}

Tree_tTree Tree_MakeTreePattern
# ifdef __STDC__
(SHORTCARD pRule, Sets_tSet pStartStates, Tree_tTree pRegExpr, Tree_tTree pRightContext, BOOLEAN pIsConstantRE, SHORTCARD pPatternNr, Positions_tPosition pPosition)
# else
(pRule, pStartStates, pRegExpr, pRightContext, pIsConstantRE, pPatternNr, pPosition)
SHORTCARD pRule;
Sets_tSet pStartStates;
Tree_tTree pRegExpr, pRightContext;
BOOLEAN pIsConstantRE;
SHORTCARD pPatternNr;
Positions_tPosition pPosition;
# endif
{
  Tree_tTree Tree;

  Tree = (Tree_tTree)Memory_Alloc((LONGINT)sizeof(Tree_NodePattern));
  {
    register Tree_NodePattern *W_7 = &Tree->U_1.V_8.vNodePattern;

    W_7->Rule = pRule;
    W_7->StartStates = pStartStates;
    W_7->RegExpr = pRegExpr;
    W_7->RightContext = pRightContext;
    W_7->IsConstantRE = pIsConstantRE;
    W_7->PatternNr = pPatternNr;
    W_7->Position = pPosition;
  }
  return Tree;
}

void Tree_WriteTree
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  SHORTCARD i;
  Strings_tString string;

  {
    SHORTCARD B_1 = 1, B_2 = indent;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        Layout_WriteSpace((System_tFile)IO_StdOutput);
        if (i >= B_2) break;
      }
  }
  if (t == Tree_NoTree) {
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"NoTree", 6L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    return;
  }
  switch (t->U_1.V_1.vNode0.Rule) {
  case Tree_nRule:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Rule ", 5L);
    IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)t->U_1.V_7.vNodeRule.RuleNr, 1L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    Texts_WriteText((System_tFile)IO_StdOutput, t->U_1.V_7.vNodeRule.TargetCode);
    break;
  case Tree_nList:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"List", 4L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nPattern:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Pattern ", 8L);
    Sets_WriteSet((System_tFile)IO_StdOutput, t->U_1.V_8.vNodePattern.StartStates);
    Layout_WriteSpace((System_tFile)IO_StdOutput);
    IO_WriteB((System_tFile)IO_StdOutput, t->U_1.V_8.vNodePattern.IsConstantRE);
    IO_WriteI((System_tFile)IO_StdOutput, (LONGINT)t->U_1.V_8.vNodePattern.PatternNr, 5L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nAlternative:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Alternative", 11L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nSequence:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Sequence", 8L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nRepetition:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Repetition", 10L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nOption:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Option", 6L);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nChar:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Char ", 5L);
    Layout_WriteChar((System_tFile)IO_StdOutput, t->U_1.V_4.vNodeCh.Ch);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nSet:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Set ", 4L);
    Sets_WriteSet((System_tFile)IO_StdOutput, t->U_1.V_5.vNodeSet.Set);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  case Tree_nString:;
    IO_WriteS((System_tFile)IO_StdOutput, (STRING)"String ", 7L);
    StringMem_GetString(t->U_1.V_6.vNodeString.String, &string);
    Strings_WriteS((System_tFile)IO_StdOutput, &string);
    IO_WriteNl((System_tFile)IO_StdOutput);
    break;
  }
  if (t->U_1.V_1.vNode0.Rule != Tree_nList) {
    INC1(indent, 2);
  }
  switch (t->U_1.V_1.vNode0.Rule) {
  case Tree_nRule:;
    Tree_WriteTree(t->U_1.V_7.vNodeRule.Patterns);
    break;
  case Tree_nList:;
    Tree_WriteTree(t->U_1.V_3.vNode2.Son1);
    Tree_WriteTree(t->U_1.V_3.vNode2.Son2);
    break;
  case Tree_nPattern:;
    Tree_WriteTree(t->U_1.V_8.vNodePattern.RegExpr);
    Tree_WriteTree(t->U_1.V_8.vNodePattern.RightContext);
    break;
  case Tree_nAlternative:;
    Tree_WriteTree(t->U_1.V_3.vNode2.Son1);
    Tree_WriteTree(t->U_1.V_3.vNode2.Son2);
    break;
  case Tree_nSequence:;
    Tree_WriteTree(t->U_1.V_3.vNode2.Son1);
    Tree_WriteTree(t->U_1.V_3.vNode2.Son2);
    break;
  case Tree_nRepetition:;
    Tree_WriteTree(t->U_1.V_2.vNode1.Son1);
    break;
  case Tree_nOption:;
    Tree_WriteTree(t->U_1.V_2.vNode1.Son1);
    break;
  default :
    break;
  }
  if (t->U_1.V_1.vNode0.Rule != Tree_nList) {
    DEC1(indent, 2);
  }
}

void Tree__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Sets__init();
    Texts__init();
    StringMem__init();
    Positions__init();
    Memory__init();
    Texts__init();
    Sets__init();
    Strings__init();
    StringMem__init();
    IO__init();
    Layout__init();
    Positions__init();
    Strings__init();

    indent = 0;
  }
}
