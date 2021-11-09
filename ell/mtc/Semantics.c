#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Codes
#include "Codes.h"
#endif

#ifndef DEFINITION_Derivable
#include "Derivable.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_First
#include "First.h"
#endif

#ifndef DEFINITION_Follow
#include "Follow.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Reachable
#include "Reachable.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

struct Semantics_1 Semantics_SemanticsTabName;

#define eAlreadyDeclared   40
#define eNotDeclared   41
#define eCodeExist   42
#define eNoRules   43
#define eNotReachable   44
#define eNotDerivable   45
#define eEnter   46
#define eByPass   48
#define eLeave   50
#define eLeftRec   52
static Idents_tIdent LeftSide;
static Sets_tSet EmptySet, EpsilonSet;
static void IdentError ARGS((INTEGER error, INTEGER class, Positions_tPosition pos, Idents_tIdent ident));
static void IntError ARGS((INTEGER error, INTEGER class, Positions_tPosition pos, INTEGER C_2_int));
static void Check ARGS((Sets_tSet *I, Sets_tSet E, INTEGER code, Positions_tPosition pos));
#define MinSetSizeC   2
#define MinCasesC   3
#define MinSetSizeM2   2
#define MinCasesM2   3
static CARDINAL MinSetSize;
static INTEGER MaxDepth;
static Sets_tSet AnySymbol;
static INTEGER Index ARGS((Sets_tSet set));
static INTEGER ExpIndex ARGS((Sets_tSet first, Sets_tSet follow, Sets_tSet recovery));
static void SetMinSetSize ARGS(());
#define yyInfinite   715827882
#define yyBitsPerBitset   32
#define yySetSize   70
#define yyMaxIndex   18
#define yyCombSize   136
#define yyStartState   0
#define yyPoolSize   10240
typedef struct S_1 *yytBlockPtr;
typedef struct S_1 {
    yytBlockPtr Successor;
    struct S_6 {
        CHAR A[yyPoolSize - 1 + 1];
    } Block;
} yytBlock;
typedef INTEGER yyStateType;
typedef struct S_2 {
    BITSET A[yySetSize / yyBitsPerBitset + 1];
} yySetType;
typedef struct S_3 {
    yySetType A[yyMaxIndex + 1];
} yySetsType;
typedef struct S_4 {
    yyStateType A[yyCombSize + 1];
} yyCombType;
typedef void (*yyPAnalyse) ARGS((Tree_tTree));
typedef void (*yyPDeclare) ARGS((Tree_tTree));
typedef void (*yyPDeclared) ARGS((Tree_tTree));
typedef void (*yyPReduced) ARGS((Tree_tTree));
typedef void (*yyPLL1) ARGS((Tree_tTree, Sets_tSet));
typedef void (*yyPRecovery) ARGS((Tree_tTree, Sets_tSet, Sets_tSet *));
typedef void (*yyPRecoveryAlt) ARGS((Tree_tTree, Sets_tSet, Sets_tSet, Sets_tSet *));
typedef void (*yyPPrepareCode) ARGS((Tree_tTree, Sets_tSet, BOOLEAN *));
typedef void (*yyPPrepareCodeAlt) ARGS((Tree_tTree, BOOLEAN, Sets_tSet, Sets_tSet, Tree_tTree, BOOLEAN *));
typedef struct S_5 *yyInfoPtr;
typedef struct S_5 {
    struct S_7 {
        INTEGER Cost;
        yyPAnalyse Proc;
    } Analyse;
    struct S_8 {
        INTEGER Cost;
        yyPDeclare Proc;
    } Declare;
    struct S_9 {
        INTEGER Cost;
        yyPDeclared Proc;
    } Declared;
    struct S_10 {
        INTEGER Cost;
        yyPReduced Proc;
    } Reduced;
    struct S_11 {
        INTEGER Cost;
        yyPLL1 Proc;
    } LL1;
    struct S_12 {
        INTEGER Cost;
        yyPRecovery Proc;
    } Recovery;
    struct S_13 {
        INTEGER Cost;
        yyPRecoveryAlt Proc;
    } RecoveryAlt;
    struct S_14 {
        INTEGER Cost;
        yyPPrepareCode Proc;
    } PrepareCode;
    struct S_15 {
        INTEGER Cost;
        yyPPrepareCodeAlt Proc;
    } PrepareCodeAlt;
} yyInfoType;
static yySetsType yySets;
static yyCombType yyComb;
static yyInfoType yyInfo;
static struct S_16 {
    BOOLEAN A[70 + 1];
} yyMatch;
static yytBlockPtr yyBlockList;
static ADDRESS yyPoolFreePtr, yyPoolEndPtr;
static ADDRESS yyAlloc ARGS(());
static void yyReleaseHeap ARGS(());
static void Analyse ARGS((Tree_tTree yyt));
static void Declare ARGS((Tree_tTree yyt));
static void Declared ARGS((Tree_tTree yyt));
static void Reduced ARGS((Tree_tTree yyt));
static void LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void RecoveryAlt ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut));
static void PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void PrepareCodeAlt ARGS((Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling));
static void yyEAnalyse ARGS((Tree_tTree yyt));
static void yyEDeclare ARGS((Tree_tTree yyt));
static void yyEDeclared ARGS((Tree_tTree yyt));
static void yyEReduced ARGS((Tree_tTree yyt));
static void yyELL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyERecovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyERecoveryAlt ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut));
static void yyEPrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyEPrepareCodeAlt ARGS((Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling));
static void yyF1Analyse ARGS((Tree_tTree yyt));
static void yyF2Analyse ARGS((Tree_tTree yyt));
static void yyF3Analyse ARGS((Tree_tTree yyt));
static void yyF4Declare ARGS((Tree_tTree yyt));
static void yyF5Declare ARGS((Tree_tTree yyt));
static void yyF6Declare ARGS((Tree_tTree yyt));
static void yyF7Declare ARGS((Tree_tTree yyt));
static void yyF8Declare ARGS((Tree_tTree yyt));
static void yyF9Declared ARGS((Tree_tTree yyt));
static void yyF10Declared ARGS((Tree_tTree yyt));
static void yyF11Declared ARGS((Tree_tTree yyt));
static void yyF12Declared ARGS((Tree_tTree yyt));
static void yyF13Declared ARGS((Tree_tTree yyt));
static void yyF14Declared ARGS((Tree_tTree yyt));
static void yyF15Declared ARGS((Tree_tTree yyt));
static void yyF16Declared ARGS((Tree_tTree yyt));
static void yyF17Declared ARGS((Tree_tTree yyt));
static void yyF18Declared ARGS((Tree_tTree yyt));
static void yyF19Declared ARGS((Tree_tTree yyt));
static void yyF20Declared ARGS((Tree_tTree yyt));
static void yyF21Declared ARGS((Tree_tTree yyt));
static void yyF22Declared ARGS((Tree_tTree yyt));
static void yyF23Declared ARGS((Tree_tTree yyt));
static void yyF24Reduced ARGS((Tree_tTree yyt));
static void yyF25Reduced ARGS((Tree_tTree yyt));
static void yyF26Reduced ARGS((Tree_tTree yyt));
static void yyF27Reduced ARGS((Tree_tTree yyt));
static void yyF28Reduced ARGS((Tree_tTree yyt));
static void yyF29Reduced ARGS((Tree_tTree yyt));
static void yyF30Reduced ARGS((Tree_tTree yyt));
static void yyF31LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF32LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF33LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF34LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF35LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF36LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF37LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF38LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF39LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF40LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF41LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF42LL1 ARGS((Tree_tTree yyt, Sets_tSet Exclude));
static void yyF43Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF44Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF45Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF46Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF47Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF48Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF49Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF50Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF51Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF52Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF53Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF54Recovery ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut));
static void yyF55RecoveryAlt ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut));
static void yyF56RecoveryAlt ARGS((Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut));
static void yyF57PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF58PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF59PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF60PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF61PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF62PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF63PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF64PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF65PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF66PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF67PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF68PrepareCode ARGS((Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling));
static void yyF69PrepareCodeAlt ARGS((Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling));
static void yyF70PrepareCodeAlt ARGS((Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling));
static INTEGER CostAnalyse ARGS((Tree_tTree yyt));
static INTEGER CostDeclare ARGS((Tree_tTree yyt));
static INTEGER CostDeclared ARGS((Tree_tTree yyt));
static INTEGER CostReduced ARGS((Tree_tTree yyt));
static INTEGER CostLL1 ARGS((Tree_tTree yyt));
static INTEGER CostRecovery ARGS((Tree_tTree yyt));
static INTEGER CostRecoveryAlt ARGS((Tree_tTree yyt));
static INTEGER CostPrepareCode ARGS((Tree_tTree yyt));
static INTEGER CostPrepareCodeAlt ARGS((Tree_tTree yyt));
static yyStateType yyTraverse ARGS((Tree_tTree yyt));
static void yyErrorCheck ARGS((INTEGER i, CHAR s1[], LONGCARD , CHAR s2[], LONGCARD ));


static void IdentError
# ifdef __STDC__
(INTEGER error, INTEGER class, Positions_tPosition pos, Idents_tIdent ident)
# else
(error, class, pos, ident)
INTEGER error, class;
Positions_tPosition pos;
Idents_tIdent ident;
# endif
{
  if (ident != Scanner_NoIdent) {
    Errors_ErrorMessageI((LONGCARD)error, (LONGCARD)class, pos, (LONGCARD)Errors_eIdent, ADR(ident));
  }
}

static void IntError
# ifdef __STDC__
(INTEGER error, INTEGER class, Positions_tPosition pos, INTEGER C_2_int)
# else
(error, class, pos, C_2_int)
INTEGER error, class;
Positions_tPosition pos;
INTEGER C_2_int;
# endif
{
  Errors_ErrorMessageI((LONGCARD)error, (LONGCARD)class, pos, (LONGCARD)Errors_eInteger, ADR(C_2_int));
}

static void Check
# ifdef __STDC__
(Sets_tSet *I, Sets_tSet E, INTEGER code, Positions_tPosition pos)
# else
(I, E, code, pos)
Sets_tSet *I;
Sets_tSet E;
INTEGER code;
Positions_tPosition pos;
# endif
{
  if (Sets_IsSubset(*I, E)) {
    Errors_ErrorMessage((LONGCARD)code, (LONGCARD)Errors_eError, pos);
  } else {
    Sets_Intersection(I, E);
    if (!Sets_IsEmpty(*I)) {
      Errors_ErrorMessageI((LONGCARD)(code + 1), (LONGCARD)Errors_eWarning, pos, (LONGCARD)Errors_eIdentSet, ADR(*I));
    }
  }
}

static INTEGER Index
# ifdef __STDC__
(Sets_tSet set)
# else
(set)
Sets_tSet set;
# endif
{
  Sets_Exclude(&set, (Sets_tElement)Scanner_Epsilon);
  if (Sets_Card(&set) < MinSetSize) {
    return Codes_cNoIndex;
  } else {
    return Codes_SetIndex(set);
  }
}

static INTEGER ExpIndex
# ifdef __STDC__
(Sets_tSet first, Sets_tSet follow, Sets_tSet recovery)
# else
(first, follow, recovery)
Sets_tSet first, follow, recovery;
# endif
{
  Sets_tSet LocalFollow;
  INTEGER result;

  Sets_MakeSet(&LocalFollow, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&LocalFollow, follow);
  Sets_Intersection(&LocalFollow, recovery);
  Sets_Union(&LocalFollow, first);
  Sets_Exclude(&LocalFollow, (Sets_tElement)Scanner_Epsilon);
  result = Codes_RecSetIndex(LocalFollow);
  Sets_ReleaseSet(&LocalFollow);
  return result;
}

static void SetMinSetSize
# ifdef __STDC__
()
# else
()
# endif
{
  switch (ArgCheck_LANGUAGE) {
  case ArgCheck_C:;
    MinSetSize = MinSetSizeC;
    MaxDepth = MinCasesC - 2;
    break;
  case ArgCheck_MODULA2:;
    MinSetSize = MinSetSizeM2;
    MaxDepth = MinCasesM2 - 2;
    break;
  }
}

static ADDRESS yyAlloc
# ifdef __STDC__
()
# else
()
# endif
{
  yytBlockPtr BlockPtr;

  if ((LONGINT)(yyPoolEndPtr - (LONGCARD)yyPoolFreePtr) < sizeof(yyInfoType)) {
    BlockPtr = yyBlockList;
    yyBlockList = (yytBlockPtr)Memory_Alloc((LONGINT)sizeof(yytBlock));
    yyBlockList->Successor = BlockPtr;
    yyPoolFreePtr = ADR(yyBlockList->Block);
    yyPoolEndPtr = (ADDRESS)(yyPoolFreePtr + yyPoolSize);
  }
  INC1(yyPoolFreePtr, (LONGCARD)(ADDRESS)sizeof(yyInfoType));
  return yyPoolFreePtr - (LONGCARD)(ADDRESS)sizeof(yyInfoType);
}

static void yyReleaseHeap
# ifdef __STDC__
()
# else
()
# endif
{
  yytBlockPtr BlockPtr;

  while (yyBlockList != NIL) {
    BlockPtr = yyBlockList;
    yyBlockList = yyBlockList->Successor;
    Memory_Free((LONGINT)sizeof(yytBlock), (ADDRESS)BlockPtr);
  }
  yyPoolFreePtr = (ADDRESS)NIL;
  yyPoolEndPtr = (ADDRESS)NIL;
}

static void Analyse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->Analyse.Proc)(yyt);
}

static void Declare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->Declare.Proc)(yyt);
}

static void Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->Declared.Proc)(yyt);
}

static void Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->Reduced.Proc)(yyt);
}

static void LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->LL1.Proc)(yyt, Exclude);
}

static void Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->Recovery.Proc)(yyt, RecIn, RecOut);
}

static void RecoveryAlt
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecUnion, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet RecUnion;
Sets_tSet *RecOut;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->RecoveryAlt.Proc)(yyt, RecIn, RecUnion, RecOut);
}

static void PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->PrepareCode.Proc)(yyt, PossibleTerms, IsCalling);
}

static void PrepareCodeAlt
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling)
# else
(yyt, Case, PossibleTerms, First, Default, IsCalling)
Tree_tTree yyt;
BOOLEAN Case;
Sets_tSet PossibleTerms;
Sets_tSet First;
Tree_tTree Default;
BOOLEAN *IsCalling;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->PrepareCodeAlt.Proc)(yyt, Case, PossibleTerms, First, Default, IsCalling);
}

static void yyEAnalyse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function Analyse is not defined for this tree", 45L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyEDeclare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function Declare is not defined for this tree", 45L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyEDeclared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function Declared is not defined for this tree", 46L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyEReduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function Reduced is not defined for this tree", 45L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyELL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function LL1 is not defined for this tree", 41L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyERecovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function Recovery is not defined for this tree", 46L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyERecoveryAlt
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecUnion, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet RecUnion;
Sets_tSet *RecOut;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function RecoveryAlt is not defined for this tree", 49L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyEPrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function PrepareCode is not defined for this tree", 49L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyEPrepareCodeAlt
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling)
# else
(yyt, Case, PossibleTerms, First, Default, IsCalling)
Tree_tTree yyt;
BOOLEAN Case;
Sets_tSet PossibleTerms;
Sets_tSet First;
Tree_tTree Default;
BOOLEAN *IsCalling;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function PrepareCodeAlt is not defined for this tree", 52L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyF1Analyse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Types_BeginTypes();
  Types_MakeTerm(Scanner_Epsilon);
  Types_MakeTerm(Scanner_EndOfToken);
  Codes_SetCode(Scanner_EndOfToken, 0L);
  Declare(yyt->U_1.V_3.Grammar.tokens);
  Declare(yyt->U_1.V_3.Grammar.rules);
  Table_InitTable();
  Declared(yyt->U_1.V_3.Grammar.tokens);
  Declared(yyt->U_1.V_3.Grammar.rules);
  Reduced(yyt);
  Analyse(yyt->U_1.V_3.Grammar.rules);
}

static void yyF2Analyse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Errors_ErrorMessage((LONGCARD)eNoRules, (LONGCARD)Errors_eError, Positions_NoPosition);
}

static void yyF3Analyse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Sets_tSet RecIn, RecOut, Empty;
  BOOLEAN IsCalling;

  First_Firsts();
  Follow_Follows(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  if (Errors_InError) {
    return;
  }
  Sets_MakeSet(&EmptySet, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&EpsilonSet, (Sets_tElement)Idents_MaxIdent());
  Sets_Include(&EpsilonSet, (Sets_tElement)Scanner_Epsilon);
  LL1(yyt, EmptySet);
  Sets_ReleaseSet(&EmptySet);
  Sets_ReleaseSet(&EpsilonSet);
  Sets_MakeSet(&RecIn, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&RecOut, (Sets_tElement)Idents_MaxIdent());
  Recovery(yyt, RecIn, &RecOut);
  Sets_ReleaseSet(&RecIn);
  Sets_ReleaseSet(&RecOut);
  SetMinSetSize();
  Sets_MakeSet(&AnySymbol, (Sets_tElement)Idents_MaxIdent());
  Types_Terminals(&AnySymbol);
  Sets_Include(&AnySymbol, (Sets_tElement)Scanner_EndOfToken);
  Sets_MakeSet(&Empty, (Sets_tElement)Idents_MaxIdent());
  Codes_EmptyRecSetIndex = Codes_RecSetIndex(Empty);
  PrepareCode(yyt, AnySymbol, &IsCalling);
  Sets_ReleaseSet(&AnySymbol);
  Sets_ReleaseSet(&Empty);
}

static void yyF4Declare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF5Declare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declare(yyt->U_1.V_20.Tokens.token);
  Declare(yyt->U_1.V_20.Tokens.tokens);
}

static void yyF6Declare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (Types_IsDeclared(yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident)) {
    IdentError((LONGINT)eAlreadyDeclared, (LONGINT)Errors_eError, yyt->U_1.V_21.Token.id->U_1.V_23.Id.pos, yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident);
    yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident = Scanner_NoIdent;
  } else if (yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident != Scanner_NoIdent) {
    Types_MakeTerm(yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident);
    if (yyt->U_1.V_21.Token.number->U_1.V_25.Number.value != Scanner_NoValue) {
      if (Codes_IsCode(yyt->U_1.V_21.Token.number->U_1.V_25.Number.value)) {
        IntError((LONGINT)eCodeExist, (LONGINT)Errors_eError, yyt->U_1.V_21.Token.number->U_1.V_25.Number.pos, yyt->U_1.V_21.Token.number->U_1.V_25.Number.value);
      } else {
        Codes_SetCode(yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident, yyt->U_1.V_21.Token.number->U_1.V_25.Number.value);
      }
    }
  }
}

static void yyF7Declare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF8Declare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (Types_IsDeclared(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident)) {
    IdentError((LONGINT)eAlreadyDeclared, (LONGINT)Errors_eError, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.pos, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
    yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident = Scanner_NoIdent;
  } else {
    Types_MakeNonterm(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  }
  Declare(yyt->U_1.V_29.Rules.rules);
}

static void yyF9Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF10Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declared(yyt->U_1.V_20.Tokens.token);
  Declared(yyt->U_1.V_20.Tokens.tokens);
}

static void yyF11Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident != Scanner_NoIdent && !Codes_IsCoded(yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident)) {
    Codes_SetDefCode(yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident);
  }
}

static void yyF12Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF13Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  LeftSide = yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident;
  Table_SetExpr(LeftSide, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr);
  Declared(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr);
  Declared(yyt->U_1.V_29.Rules.rules);
}

static void yyF14Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declared(yyt->U_1.V_33.Option.expr);
}

static void yyF15Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declared(yyt->U_1.V_34.Times.expr);
}

static void yyF16Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declared(yyt->U_1.V_35.Plus.expr);
}

static void yyF17Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declared(yyt->U_1.V_36.List.body);
  Declared(yyt->U_1.V_36.List.sep);
}

static void yyF18Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF19Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (!Types_IsDeclared(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident)) {
    IdentError((LONGINT)eNotDeclared, (LONGINT)Errors_eError, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.pos, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  } else {
    Table_SetLeaf(LeftSide, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  }
}

static void yyF20Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF21Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declared(yyt->U_1.V_41.Alternative.expr);
  Declared(yyt->U_1.V_41.Alternative.alternative);
}

static void yyF22Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF23Declared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Declared(yyt->U_1.V_44.Sequence.expr);
  Declared(yyt->U_1.V_44.Sequence.sequence);
}

static void yyF24Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF25Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Reachable_WindThrough(yyt->U_1.V_3.Grammar.rules->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  Derivable_TestDerivable();
  Reduced(yyt->U_1.V_3.Grammar.tokens);
  Reduced(yyt->U_1.V_3.Grammar.rules);
}

static void yyF26Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF27Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Reduced(yyt->U_1.V_20.Tokens.token);
  Reduced(yyt->U_1.V_20.Tokens.tokens);
}

static void yyF28Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (!Reachable_IsReachable(yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident)) {
    IdentError((LONGINT)eNotReachable, (LONGINT)Errors_eWarning, yyt->U_1.V_21.Token.id->U_1.V_23.Id.pos, yyt->U_1.V_21.Token.id->U_1.V_23.Id.ident);
  }
}

static void yyF29Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF30Reduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (!Reachable_IsReachable(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident)) {
    IdentError((LONGINT)eNotReachable, (LONGINT)Errors_eError, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.pos, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  }
  if (!Derivable_IsDerivable(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident)) {
    IdentError((LONGINT)eNotDerivable, (LONGINT)Errors_eError, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.pos, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  }
  Reduced(yyt->U_1.V_29.Rules.rules);
}

static void yyF31LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
}

static void yyF32LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  if (First_IsLeftRec(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident)) {
    IdentError((LONGINT)eLeftRec, (LONGINT)Errors_eError, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.pos, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  }
  LL1(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr, Exclude);
  LL1(yyt->U_1.V_29.Rules.rules, Exclude);
}

static void yyF33LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet In, ByPass, Set;

  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&ByPass, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Set, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, yyt->U_1.V_33.Option.expr->U_1.V_32.expr.fifo);
  Sets_Assign(&ByPass, yyt->U_1.V_33.Option.expr->U_1.V_32.expr.follow);
  Sets_Assign(&Set, yyt->U_1.V_33.Option.expr->U_1.V_32.expr.fifo);
  Sets_Union(&Set, Exclude);
  Check(&ByPass, Set, (LONGINT)eByPass, yyt->U_1.V_33.Option.pos);
  Check(&In, Exclude, (LONGINT)eEnter, yyt->U_1.V_33.Option.pos);
  Sets_ReleaseSet(&In);
  Sets_ReleaseSet(&ByPass);
  Sets_ReleaseSet(&Set);
  LL1(yyt->U_1.V_33.Option.expr, Exclude);
  Sets_Difference(&yyt->U_1.V_33.Option.fifo, Exclude);
}

static void yyF34LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet In, Leave, Set;

  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Leave, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Set, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, yyt->U_1.V_34.Times.expr->U_1.V_32.expr.fifo);
  Sets_Assign(&Leave, yyt->U_1.V_34.Times.follow);
  Sets_Assign(&Set, yyt->U_1.V_34.Times.expr->U_1.V_32.expr.fifo);
  Sets_Union(&Set, Exclude);
  Check(&Leave, Set, (LONGINT)eLeave, yyt->U_1.V_34.Times.pos);
  Check(&In, Exclude, (LONGINT)eEnter, yyt->U_1.V_34.Times.pos);
  Sets_ReleaseSet(&In);
  Sets_ReleaseSet(&Leave);
  Sets_ReleaseSet(&Set);
  LL1(yyt->U_1.V_34.Times.expr, EmptySet);
  Sets_Difference(&yyt->U_1.V_34.Times.fifo, Exclude);
}

static void yyF35LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet In, Leave;

  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Leave, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, yyt->U_1.V_35.Plus.fifo);
  Sets_Assign(&Leave, yyt->U_1.V_35.Plus.follow);
  Check(&Leave, In, (LONGINT)eLeave, yyt->U_1.V_35.Plus.pos);
  Check(&In, Exclude, (LONGINT)eEnter, yyt->U_1.V_35.Plus.pos);
  Sets_ReleaseSet(&In);
  Sets_ReleaseSet(&Leave);
  LL1(yyt->U_1.V_35.Plus.expr, EmptySet);
  Sets_Difference(&yyt->U_1.V_35.Plus.fifo, Exclude);
}

static void yyF36LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet In, Keep, Leave;

  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Keep, (Sets_tElement)Idents_MaxIdent());
  Sets_MakeSet(&Leave, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, yyt->U_1.V_36.List.fifo);
  Sets_Assign(&Keep, yyt->U_1.V_36.List.sep->U_1.V_32.expr.fifo);
  Sets_Assign(&Leave, yyt->U_1.V_36.List.follow);
  Check(&Leave, Keep, (LONGINT)eLeave, yyt->U_1.V_36.List.pos);
  Check(&In, Exclude, (LONGINT)eEnter, yyt->U_1.V_36.List.pos);
  Sets_ReleaseSet(&In);
  Sets_ReleaseSet(&Keep);
  Sets_ReleaseSet(&Leave);
  LL1(yyt->U_1.V_36.List.body, EmptySet);
  LL1(yyt->U_1.V_36.List.sep, EmptySet);
  Sets_Difference(&yyt->U_1.V_36.List.fifo, Exclude);
}

static void yyF37LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet In;

  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, yyt->U_1.V_37.Action.fifo);
  Check(&In, Exclude, (LONGINT)eEnter, yyt->U_1.V_37.Action.pos);
  Sets_ReleaseSet(&In);
  Sets_Difference(&yyt->U_1.V_37.Action.fifo, Exclude);
}

static void yyF38LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet In;

  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, yyt->U_1.V_38.Leaf.fifo);
  Check(&In, Exclude, (LONGINT)eEnter, yyt->U_1.V_38.Leaf.pos);
  Sets_ReleaseSet(&In);
  Sets_Difference(&yyt->U_1.V_38.Leaf.fifo, Exclude);
}

static void yyF39LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  yyt->U_1.V_40.Alternative0.depth = 0;
  Sets_Difference(&yyt->U_1.V_40.Alternative0.fifo, Exclude);
}

static void yyF40LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet E2;

  LL1(yyt->U_1.V_41.Alternative.expr, Exclude);
  Sets_MakeSet(&E2, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&E2, Exclude);
  Sets_Union(&E2, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  LL1(yyt->U_1.V_41.Alternative.alternative, E2);
  yyt->U_1.V_41.Alternative.depth = yyt->U_1.V_41.Alternative.alternative->U_1.V_39.alternative.depth + 1;
  Sets_ReleaseSet(&E2);
  Sets_Difference(&yyt->U_1.V_41.Alternative.fifo, Exclude);
}

static void yyF41LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  Sets_tSet In;

  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, yyt->U_1.V_43.Sequence0.fifo);
  Check(&In, Exclude, (LONGINT)eEnter, yyt->U_1.V_43.Sequence0.pos);
  Sets_Difference(&yyt->U_1.V_43.Sequence0.fifo, Exclude);
}

static void yyF42LL1
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet Exclude)
# else
(yyt, Exclude)
Tree_tTree yyt;
Sets_tSet Exclude;
# endif
{
  LL1(yyt->U_1.V_44.Sequence.expr, Exclude);
  if (Sets_IsEqual(&yyt->U_1.V_44.Sequence.expr->U_1.V_32.expr.first, &EpsilonSet)) {
    LL1(yyt->U_1.V_44.Sequence.sequence, Exclude);
  } else {
    LL1(yyt->U_1.V_44.Sequence.sequence, EmptySet);
  }
  Sets_Difference(&yyt->U_1.V_44.Sequence.fifo, Exclude);
}

static void yyF43Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
}

static void yyF44Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Recovery(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr, RecIn, RecOut);
  Recovery(yyt->U_1.V_29.Rules.rules, RecIn, RecOut);
}

static void yyF45Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_33.Option.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&yyt->U_1.V_33.Option.recovery, RecIn);
  Sets_Union(&yyt->U_1.V_33.Option.recovery, yyt->U_1.V_33.Option.first);
  Sets_Exclude(&yyt->U_1.V_33.Option.recovery, (Sets_tElement)Scanner_Epsilon);
  Recovery(yyt->U_1.V_33.Option.expr, RecIn, RecOut);
  Sets_Assign(RecOut, yyt->U_1.V_33.Option.recovery);
}

static void yyF46Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_34.Times.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&yyt->U_1.V_34.Times.recovery, RecIn);
  Sets_Union(&yyt->U_1.V_34.Times.recovery, yyt->U_1.V_34.Times.first);
  Sets_Exclude(&yyt->U_1.V_34.Times.recovery, (Sets_tElement)Scanner_Epsilon);
  Recovery(yyt->U_1.V_34.Times.expr, RecIn, RecOut);
  Sets_Assign(RecOut, yyt->U_1.V_34.Times.recovery);
}

static void yyF47Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_35.Plus.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&yyt->U_1.V_35.Plus.recovery, RecIn);
  Sets_Union(&yyt->U_1.V_35.Plus.recovery, yyt->U_1.V_35.Plus.first);
  Sets_Exclude(&yyt->U_1.V_35.Plus.recovery, (Sets_tElement)Scanner_Epsilon);
  Recovery(yyt->U_1.V_35.Plus.expr, RecIn, RecOut);
  Sets_Assign(RecOut, yyt->U_1.V_35.Plus.recovery);
}

static void yyF48Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_tSet In;

  Sets_MakeSet(&yyt->U_1.V_36.List.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&yyt->U_1.V_36.List.recovery, RecIn);
  Sets_Union(&yyt->U_1.V_36.List.recovery, yyt->U_1.V_36.List.body->U_1.V_32.expr.first);
  Sets_Union(&yyt->U_1.V_36.List.recovery, yyt->U_1.V_36.List.sep->U_1.V_32.expr.first);
  Sets_Exclude(&yyt->U_1.V_36.List.recovery, (Sets_tElement)Scanner_Epsilon);
  Sets_MakeSet(&In, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&In, RecIn);
  Sets_Union(&In, yyt->U_1.V_36.List.sep->U_1.V_32.expr.first);
  Sets_Exclude(&In, (Sets_tElement)Scanner_Epsilon);
  Recovery(yyt->U_1.V_36.List.body, In, RecOut);
  Sets_Assign(&In, RecIn);
  Sets_Union(&In, yyt->U_1.V_36.List.body->U_1.V_32.expr.first);
  Sets_Exclude(&In, (Sets_tElement)Scanner_Epsilon);
  Recovery(yyt->U_1.V_36.List.sep, In, RecOut);
  Sets_ReleaseSet(&In);
  Sets_Assign(RecOut, yyt->U_1.V_36.List.recovery);
}

static void yyF49Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_37.Action.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&yyt->U_1.V_37.Action.recovery, RecIn);
  Sets_Assign(RecOut, RecIn);
}

static void yyF50Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_38.Leaf.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(RecOut, RecIn);
  Sets_Union(RecOut, yyt->U_1.V_38.Leaf.first);
  Sets_Exclude(RecOut, (Sets_tElement)Scanner_Epsilon);
  if (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident)) {
    Sets_Assign(&yyt->U_1.V_38.Leaf.recovery, *RecOut);
  } else {
    Sets_Assign(&yyt->U_1.V_38.Leaf.recovery, RecIn);
  }
}

static void yyF51Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Errors_ERROR((STRING)"Sem.estra: Alternative0 unexpected", 34L);
}

static void yyF52Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_tSet RecUnion;

  Sets_MakeSet(&RecUnion, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&RecUnion, RecIn);
  RecoveryAlt(yyt, RecIn, RecUnion, RecOut);
  Sets_ReleaseSet(&RecUnion);
}

static void yyF53Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_43.Sequence0.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&yyt->U_1.V_43.Sequence0.recovery, RecIn);
  Sets_Assign(RecOut, RecIn);
}

static void yyF54Recovery
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_44.Sequence.recovery, (Sets_tElement)Idents_MaxIdent());
  Recovery(yyt->U_1.V_44.Sequence.sequence, RecIn, RecOut);
  Recovery(yyt->U_1.V_44.Sequence.expr, *RecOut, &yyt->U_1.V_44.Sequence.recovery);
  Sets_Assign(RecOut, yyt->U_1.V_44.Sequence.recovery);
}

static void yyF55RecoveryAlt
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecUnion, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet RecUnion;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_40.Alternative0.recovery, (Sets_tElement)Idents_MaxIdent());
  Sets_Exclude(&RecUnion, (Sets_tElement)Scanner_Epsilon);
  Sets_Assign(&yyt->U_1.V_40.Alternative0.recovery, RecUnion);
  Sets_Assign(RecOut, RecUnion);
}

static void yyF56RecoveryAlt
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet RecIn, Sets_tSet RecUnion, Sets_tSet *RecOut)
# else
(yyt, RecIn, RecUnion, RecOut)
Tree_tTree yyt;
Sets_tSet RecIn;
Sets_tSet RecUnion;
Sets_tSet *RecOut;
# endif
{
  Sets_MakeSet(&yyt->U_1.V_41.Alternative.recovery, (Sets_tElement)Idents_MaxIdent());
  Recovery(yyt->U_1.V_41.Alternative.expr, RecIn, RecOut);
  Sets_Union(&RecUnion, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.first);
  RecoveryAlt(yyt->U_1.V_41.Alternative.alternative, RecIn, RecUnion, RecOut);
  Sets_Assign(&yyt->U_1.V_41.Alternative.recovery, *RecOut);
}

static void yyF57PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
}

static void yyF58PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  PrepareCode(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr, PossibleTerms, &yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.iscalling);
  PrepareCode(yyt->U_1.V_29.Rules.rules, PossibleTerms, IsCalling);
}

static void yyF59PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  yyt->U_1.V_33.Option.index = Index(yyt->U_1.V_33.Option.first);
  yyt->U_1.V_33.Option.followindex = Index(yyt->U_1.V_33.Option.follow);
  yyt->U_1.V_33.Option.expindex = ExpIndex(yyt->U_1.V_33.Option.first, yyt->U_1.V_33.Option.follow, yyt->U_1.V_33.Option.recovery);
  yyt->U_1.V_33.Option.recindex = Codes_RecSetIndex(yyt->U_1.V_33.Option.recovery);
  PrepareCode(yyt->U_1.V_33.Option.expr, yyt->U_1.V_33.Option.expr->U_1.V_32.expr.fifo, IsCalling);
}

static void yyF60PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  yyt->U_1.V_34.Times.index = Index(yyt->U_1.V_34.Times.first);
  yyt->U_1.V_34.Times.followindex = Index(yyt->U_1.V_34.Times.follow);
  yyt->U_1.V_34.Times.expindex = ExpIndex(yyt->U_1.V_34.Times.first, yyt->U_1.V_34.Times.follow, yyt->U_1.V_34.Times.recovery);
  yyt->U_1.V_34.Times.recindex = Codes_RecSetIndex(yyt->U_1.V_34.Times.recovery);
  PrepareCode(yyt->U_1.V_34.Times.expr, yyt->U_1.V_34.Times.expr->U_1.V_32.expr.fifo, IsCalling);
}

static void yyF61PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  Sets_tSet set;

  yyt->U_1.V_35.Plus.index = Index(yyt->U_1.V_35.Plus.first);
  yyt->U_1.V_35.Plus.followindex = Index(yyt->U_1.V_35.Plus.follow);
  yyt->U_1.V_35.Plus.expindex = ExpIndex(yyt->U_1.V_35.Plus.first, yyt->U_1.V_35.Plus.follow, yyt->U_1.V_35.Plus.recovery);
  yyt->U_1.V_35.Plus.recindex = Codes_RecSetIndex(yyt->U_1.V_35.Plus.recovery);
  Sets_MakeSet(&set, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&set, PossibleTerms);
  Sets_Union(&set, yyt->U_1.V_35.Plus.expr->U_1.V_32.expr.fifo);
  PrepareCode(yyt->U_1.V_35.Plus.expr, set, IsCalling);
  Sets_ReleaseSet(&set);
}

static void yyF62PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  BOOLEAN iscalling;

  yyt->U_1.V_36.List.index = Index(yyt->U_1.V_36.List.first);
  yyt->U_1.V_36.List.followindex = Index(yyt->U_1.V_36.List.follow);
  yyt->U_1.V_36.List.expindex = ExpIndex(yyt->U_1.V_36.List.sep->U_1.V_32.expr.first, yyt->U_1.V_36.List.follow, yyt->U_1.V_36.List.recovery);
  yyt->U_1.V_36.List.recindex = Codes_RecSetIndex(yyt->U_1.V_36.List.recovery);
  PrepareCode(yyt->U_1.V_36.List.body, AnySymbol, &iscalling);
  PrepareCode(yyt->U_1.V_36.List.sep, AnySymbol, IsCalling);
  *IsCalling = *IsCalling || iscalling;
}

static void yyF63PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  *IsCalling = FALSE;
}

static void yyF64PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  yyt->U_1.V_38.Leaf.sure = Sets_IsSubset(PossibleTerms, yyt->U_1.V_38.Leaf.fifo);
  if (yyt->U_1.V_38.Leaf.sure || Types_IsNonterm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident)) {
    yyt->U_1.V_38.Leaf.index = Codes_cNoIndex;
  } else {
    yyt->U_1.V_38.Leaf.index = Index(yyt->U_1.V_38.Leaf.first);
  }
  yyt->U_1.V_38.Leaf.recindex = Codes_RecSetIndex(yyt->U_1.V_38.Leaf.recovery);
  *IsCalling = Types_IsNonterm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
}

static void yyF65PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  Errors_ERROR((STRING)"Sem.estra: Alternative0 unexpected", 34L);
}

static void yyF66PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  BOOLEAN C_1_case;
  INTEGER maxdepth;

  maxdepth = MaxDepth;
  if (Sets_IsSubset(PossibleTerms, yyt->U_1.V_41.Alternative.fifo)) {
    INC(maxdepth);
  }
  C_1_case = yyt->U_1.V_41.Alternative.depth > maxdepth;
  PrepareCodeAlt(yyt, C_1_case, PossibleTerms, yyt->U_1.V_41.Alternative.first, (Tree_tTree)Tree_NoTree, IsCalling);
}

static void yyF67PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  *IsCalling = FALSE;
}

static void yyF68PrepareCode
# ifdef __STDC__
(Tree_tTree yyt, Sets_tSet PossibleTerms, BOOLEAN *IsCalling)
# else
(yyt, PossibleTerms, IsCalling)
Tree_tTree yyt;
Sets_tSet PossibleTerms;
BOOLEAN *IsCalling;
# endif
{
  BOOLEAN iscalling;

  PrepareCode(yyt->U_1.V_44.Sequence.expr, PossibleTerms, &iscalling);
  if (Sets_IsElement((Sets_tElement)Scanner_Epsilon, &yyt->U_1.V_44.Sequence.expr->U_1.V_32.expr.first) && Sets_Card(&yyt->U_1.V_44.Sequence.expr->U_1.V_32.expr.first) == 1) {
    PrepareCode(yyt->U_1.V_44.Sequence.sequence, PossibleTerms, IsCalling);
  } else {
    PrepareCode(yyt->U_1.V_44.Sequence.sequence, AnySymbol, IsCalling);
  }
  *IsCalling = *IsCalling || iscalling;
}

static void yyF69PrepareCodeAlt
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling)
# else
(yyt, Case, PossibleTerms, First, Default, IsCalling)
Tree_tTree yyt;
BOOLEAN Case;
Sets_tSet PossibleTerms;
Sets_tSet First;
Tree_tTree Default;
BOOLEAN *IsCalling;
# endif
{
  Sets_tSet LocalFollow;

  Sets_MakeSet(&LocalFollow, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&LocalFollow, yyt->U_1.V_40.Alternative0.follow);
  Sets_Intersection(&LocalFollow, yyt->U_1.V_40.Alternative0.recovery);
  if (!Sets_IsEmpty(LocalFollow) || !Sets_IsElement((Sets_tElement)Scanner_Epsilon, &First)) {
    Sets_Union(&LocalFollow, First);
    Sets_Exclude(&LocalFollow, (Sets_tElement)Scanner_Epsilon);
    yyt->U_1.V_40.Alternative0.expindex = Codes_RecSetIndex(LocalFollow);
  } else {
    yyt->U_1.V_40.Alternative0.expindex = Codes_cNoIndex;
  }
  Sets_ReleaseSet(&LocalFollow);
  yyt->U_1.V_40.Alternative0.C_0_case = Case;
  yyt->U_1.V_40.Alternative0.C_0_default = Default;
  yyt->U_1.V_40.Alternative0.recindex = Codes_RecSetIndex(yyt->U_1.V_40.Alternative0.recovery);
  *IsCalling = FALSE;
}

static void yyF70PrepareCodeAlt
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN Case, Sets_tSet PossibleTerms, Sets_tSet First, Tree_tTree Default, BOOLEAN *IsCalling)
# else
(yyt, Case, PossibleTerms, First, Default, IsCalling)
Tree_tTree yyt;
BOOLEAN Case;
Sets_tSet PossibleTerms;
Sets_tSet First;
Tree_tTree Default;
BOOLEAN *IsCalling;
# endif
{
  Sets_tSet possible;
  BOOLEAN iscalling;

  yyt->U_1.V_41.Alternative.C_0_case = Case;
  PrepareCode(yyt->U_1.V_41.Alternative.expr, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo, &iscalling);
  Sets_MakeSet(&possible, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&possible, PossibleTerms);
  if (Default == Tree_NoTree || Default->U_1.V_32.expr.length > yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.length) {
    Default = yyt->U_1.V_41.Alternative.expr;
  }
  Sets_Difference(&possible, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  if (!Case) {
    yyt->U_1.V_41.Alternative.index = Index(yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  }
  PrepareCodeAlt(yyt->U_1.V_41.Alternative.alternative, Case, possible, First, Default, IsCalling);
  *IsCalling = *IsCalling || iscalling;
  Sets_ReleaseSet(&possible);
}

static INTEGER CostAnalyse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->Analyse.Cost;
}

static INTEGER CostDeclare
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->Declare.Cost;
}

static INTEGER CostDeclared
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->Declared.Cost;
}

static INTEGER CostReduced
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->Reduced.Cost;
}

static INTEGER CostLL1
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->LL1.Cost;
}

static INTEGER CostRecovery
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->Recovery.Cost;
}

static INTEGER CostRecoveryAlt
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->RecoveryAlt.Cost;
}

static INTEGER CostPrepareCode
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->PrepareCode.Cost;
}

static INTEGER CostPrepareCodeAlt
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->PrepareCodeAlt.Cost;
}

static yyStateType yyTraverse
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyStateType state;
  yySetType *match;
  INTEGER cost;
  yyInfoPtr info;
  BOOLEAN success;

  info = (yyInfoPtr)yyAlloc();
  *info = yyInfo;
  yyt->U_1.V_2.yyHead.yyEstraInfo = (ADDRESS)info;
  switch (yyt->U_1.V_1.Kind) {
  case Tree_Codes:;
    state = 0;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_15.Codes.code)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_15.Codes.codes)];
    break;
  case Tree_Grammar:;
    state = 12;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_3.Grammar.sections)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_3.Grammar.tokens)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_3.Grammar.rules)];
    match = (yySetType *)ADR(yySets.A[state]);
    yyMatch.A[24] = IN(24, match->A[0]);
    yyMatch.A[25] = IN(25, match->A[0]);
    if (yyMatch.A[24]) {
      cost = 1;
      if (cost < info->Reduced.Cost) {
        info->Reduced.Cost = cost;
        info->Reduced.Proc = yyF24Reduced;
      }
    }
    if (yyMatch.A[25]) {
      cost = 1 + CostReduced(yyt->U_1.V_3.Grammar.tokens) + CostReduced(yyt->U_1.V_3.Grammar.rules);
      if (cost < info->Reduced.Cost) {
        info->Reduced.Cost = cost;
        info->Reduced.Proc = yyF25Reduced;
      }
    }
    cost = 1 + CostReduced(yyt) + CostDeclare(yyt->U_1.V_3.Grammar.tokens) + CostDeclared(yyt->U_1.V_3.Grammar.tokens) + CostDeclare(yyt->U_1.V_3.Grammar.rules) + CostDeclared(yyt->U_1.V_3.Grammar.rules) + CostAnalyse(yyt->U_1.V_3.Grammar.rules);
    if (cost < info->Analyse.Cost) {
      info->Analyse.Cost = cost;
      info->Analyse.Proc = yyF1Analyse;
    }
    break;
  case Tree_Sections0:;
    state = 18;
    break;
  case Tree_Sections:;
    state = 0;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_6.Sections.section)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_6.Sections.sections)];
    break;
  case Tree_Export:;
    state = 11;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_8.Export.codes)];
    break;
  case Tree_Global:;
    state = 11;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_9.Global.codes)];
    break;
  case Tree_Local:;
    state = 11;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_10.Local.codes)];
    break;
  case Tree_Begin:;
    state = 11;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_11.Begin.codes)];
    break;
  case Tree_Close:;
    state = 11;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_12.Close.codes)];
    break;
  case Tree_Codes0:;
    state = 18;
    break;
  case Tree_Code:;
    state = 18;
    break;
  case Tree_Tokens0:;
    state = 5;
    cost = 1;
    if (cost < info->Declare.Cost) {
      info->Declare.Cost = cost;
      info->Declare.Proc = yyF4Declare;
    }
    cost = 1;
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF9Declared;
    }
    cost = 1;
    if (cost < info->Reduced.Cost) {
      info->Reduced.Cost = cost;
      info->Reduced.Proc = yyF26Reduced;
    }
    break;
  case Tree_Tokens:;
    state = 28;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_20.Tokens.token)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_20.Tokens.tokens)];
    cost = 1 + CostDeclare(yyt->U_1.V_20.Tokens.token) + CostDeclare(yyt->U_1.V_20.Tokens.tokens);
    if (cost < info->Declare.Cost) {
      info->Declare.Cost = cost;
      info->Declare.Proc = yyF5Declare;
    }
    cost = 1 + CostDeclared(yyt->U_1.V_20.Tokens.token) + CostDeclared(yyt->U_1.V_20.Tokens.tokens);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF10Declared;
    }
    cost = 1 + CostReduced(yyt->U_1.V_20.Tokens.token) + CostReduced(yyt->U_1.V_20.Tokens.tokens);
    if (cost < info->Reduced.Cost) {
      info->Reduced.Cost = cost;
      info->Reduced.Proc = yyF27Reduced;
    }
    break;
  case Tree_Token:;
    state = 20;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_21.Token.id)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_21.Token.number)];
    cost = 1;
    if (cost < info->Declare.Cost) {
      info->Declare.Cost = cost;
      info->Declare.Proc = yyF6Declare;
    }
    cost = 1;
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF11Declared;
    }
    cost = 1;
    if (cost < info->Reduced.Cost) {
      info->Reduced.Cost = cost;
      info->Reduced.Proc = yyF28Reduced;
    }
    break;
  case Tree_Id:;
    state = 18;
    break;
  case Tree_Number:;
    state = 18;
    break;
  case Tree_Rules0:;
    state = 3;
    cost = 1;
    if (cost < info->Analyse.Cost) {
      info->Analyse.Cost = cost;
      info->Analyse.Proc = yyF2Analyse;
    }
    cost = 1;
    if (cost < info->Declare.Cost) {
      info->Declare.Cost = cost;
      info->Declare.Proc = yyF7Declare;
    }
    cost = 1;
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF12Declared;
    }
    cost = 1;
    if (cost < info->Reduced.Cost) {
      info->Reduced.Cost = cost;
      info->Reduced.Proc = yyF29Reduced;
    }
    cost = 1;
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF31LL1;
    }
    cost = 1;
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF43Recovery;
    }
    cost = 1;
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF57PrepareCode;
    }
    break;
  case Tree_Rules:;
    state = 22;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_29.Rules.rule)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_29.Rules.rules)];
    cost = 1 + CostDeclare(yyt->U_1.V_29.Rules.rules);
    if (cost < info->Declare.Cost) {
      info->Declare.Cost = cost;
      info->Declare.Proc = yyF8Declare;
    }
    cost = 1 + CostDeclared(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostDeclared(yyt->U_1.V_29.Rules.rules);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF13Declared;
    }
    cost = 1 + CostReduced(yyt->U_1.V_29.Rules.rules);
    if (cost < info->Reduced.Cost) {
      info->Reduced.Cost = cost;
      info->Reduced.Proc = yyF30Reduced;
    }
    cost = 1 + CostLL1(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostLL1(yyt->U_1.V_29.Rules.rules);
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF32LL1;
    }
    cost = 1 + CostRecovery(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostRecovery(yyt->U_1.V_29.Rules.rules);
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF44Recovery;
    }
    cost = 1 + CostPrepareCode(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostPrepareCode(yyt->U_1.V_29.Rules.rules);
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF58PrepareCode;
    }
    cost = 1 + CostLL1(yyt) + CostRecovery(yyt) + CostPrepareCode(yyt);
    if (cost < info->Analyse.Cost) {
      info->Analyse.Cost = cost;
      info->Analyse.Proc = yyF3Analyse;
    }
    break;
  case Tree_Rule:;
    state = 25;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_30.Rule.id)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_30.Rule.codes)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_30.Rule.expr)];
    break;
  case Tree_Option:;
    state = 49;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_33.Option.expr)];
    cost = 1 + CostDeclared(yyt->U_1.V_33.Option.expr);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF14Declared;
    }
    cost = 1 + CostLL1(yyt->U_1.V_33.Option.expr);
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF33LL1;
    }
    cost = 1 + CostRecovery(yyt->U_1.V_33.Option.expr);
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF45Recovery;
    }
    cost = 1 + CostPrepareCode(yyt->U_1.V_33.Option.expr);
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF59PrepareCode;
    }
    break;
  case Tree_Times:;
    state = 60;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_34.Times.expr)];
    cost = 1 + CostDeclared(yyt->U_1.V_34.Times.expr);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF15Declared;
    }
    cost = 1 + CostLL1(yyt->U_1.V_34.Times.expr);
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF34LL1;
    }
    cost = 1 + CostRecovery(yyt->U_1.V_34.Times.expr);
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF46Recovery;
    }
    cost = 1 + CostPrepareCode(yyt->U_1.V_34.Times.expr);
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF60PrepareCode;
    }
    break;
  case Tree_Plus:;
    state = 71;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_35.Plus.expr)];
    cost = 1 + CostDeclared(yyt->U_1.V_35.Plus.expr);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF16Declared;
    }
    cost = 1 + CostLL1(yyt->U_1.V_35.Plus.expr);
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF35LL1;
    }
    cost = 1 + CostRecovery(yyt->U_1.V_35.Plus.expr);
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF47Recovery;
    }
    cost = 1 + CostPrepareCode(yyt->U_1.V_35.Plus.expr);
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF61PrepareCode;
    }
    break;
  case Tree_List:;
    state = 82;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_36.List.body)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_36.List.sep)];
    cost = 1 + CostDeclared(yyt->U_1.V_36.List.body) + CostDeclared(yyt->U_1.V_36.List.sep);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF17Declared;
    }
    cost = 1 + CostLL1(yyt->U_1.V_36.List.body) + CostLL1(yyt->U_1.V_36.List.sep);
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF36LL1;
    }
    cost = 1 + CostRecovery(yyt->U_1.V_36.List.body) + CostRecovery(yyt->U_1.V_36.List.sep);
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF48Recovery;
    }
    cost = 1 + CostPrepareCode(yyt->U_1.V_36.List.body) + CostPrepareCode(yyt->U_1.V_36.List.sep);
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF62PrepareCode;
    }
    break;
  case Tree_Action:;
    state = 27;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_37.Action.codes)];
    cost = 1;
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF18Declared;
    }
    cost = 1;
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF37LL1;
    }
    cost = 1;
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF49Recovery;
    }
    cost = 1;
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF63PrepareCode;
    }
    break;
  case Tree_Leaf:;
    state = 29;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_38.Leaf.id)];
    cost = 1;
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF19Declared;
    }
    cost = 1;
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF38LL1;
    }
    cost = 1;
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF50Recovery;
    }
    cost = 1;
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF64PrepareCode;
    }
    break;
  case Tree_Alternative0:;
    state = 14;
    cost = 1;
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF20Declared;
    }
    cost = 1;
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF39LL1;
    }
    cost = 1;
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF51Recovery;
    }
    cost = 1;
    if (cost < info->RecoveryAlt.Cost) {
      info->RecoveryAlt.Cost = cost;
      info->RecoveryAlt.Proc = yyF55RecoveryAlt;
    }
    cost = 1;
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF65PrepareCode;
    }
    cost = 1;
    if (cost < info->PrepareCodeAlt.Cost) {
      info->PrepareCodeAlt.Cost = cost;
      info->PrepareCodeAlt.Proc = yyF69PrepareCodeAlt;
    }
    break;
  case Tree_Alternative:;
    state = 104;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_41.Alternative.expr)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_41.Alternative.alternative)];
    cost = 1 + CostDeclared(yyt->U_1.V_41.Alternative.expr) + CostDeclared(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF21Declared;
    }
    cost = 1 + CostLL1(yyt->U_1.V_41.Alternative.expr) + CostLL1(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF40LL1;
    }
    cost = 1 + CostRecovery(yyt->U_1.V_41.Alternative.expr) + CostRecoveryAlt(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->RecoveryAlt.Cost) {
      info->RecoveryAlt.Cost = cost;
      info->RecoveryAlt.Proc = yyF56RecoveryAlt;
    }
    cost = 1 + CostPrepareCode(yyt->U_1.V_41.Alternative.expr) + CostPrepareCodeAlt(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->PrepareCodeAlt.Cost) {
      info->PrepareCodeAlt.Cost = cost;
      info->PrepareCodeAlt.Proc = yyF70PrepareCodeAlt;
    }
    do {
      success = FALSE;
      cost = 1 + CostRecoveryAlt(yyt);
      if (cost < info->Recovery.Cost) {
        info->Recovery.Cost = cost;
        info->Recovery.Proc = yyF52Recovery;
        success = TRUE;
      }
      cost = 1 + CostPrepareCodeAlt(yyt);
      if (cost < info->PrepareCode.Cost) {
        info->PrepareCode.Cost = cost;
        info->PrepareCode.Proc = yyF66PrepareCode;
        success = TRUE;
      }
    } while (!!success);
    break;
  case Tree_Sequence0:;
    state = 16;
    cost = 1;
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF22Declared;
    }
    cost = 1;
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF41LL1;
    }
    cost = 1;
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF53Recovery;
    }
    cost = 1;
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF67PrepareCode;
    }
    break;
  case Tree_Sequence:;
    state = 115;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_44.Sequence.expr)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_44.Sequence.sequence)];
    cost = 1 + CostDeclared(yyt->U_1.V_44.Sequence.expr) + CostDeclared(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->Declared.Cost) {
      info->Declared.Cost = cost;
      info->Declared.Proc = yyF23Declared;
    }
    cost = 1 + CostLL1(yyt->U_1.V_44.Sequence.expr) + CostLL1(yyt->U_1.V_44.Sequence.sequence) + CostLL1(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->LL1.Cost) {
      info->LL1.Cost = cost;
      info->LL1.Proc = yyF42LL1;
    }
    cost = 1 + CostRecovery(yyt->U_1.V_44.Sequence.expr) + CostRecovery(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->Recovery.Cost) {
      info->Recovery.Cost = cost;
      info->Recovery.Proc = yyF54Recovery;
    }
    cost = 1 + CostPrepareCode(yyt->U_1.V_44.Sequence.expr) + CostPrepareCode(yyt->U_1.V_44.Sequence.sequence) + CostPrepareCode(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->PrepareCode.Cost) {
      info->PrepareCode.Cost = cost;
      info->PrepareCode.Proc = yyF68PrepareCode;
    }
    break;
  }
  return state;
}

static void yyErrorCheck
# ifdef __STDC__
(INTEGER i, CHAR s1[], LONGCARD O_2, CHAR s2[], LONGCARD O_1)
# else
(i, s1, O_2, s2, O_1)
INTEGER i;
CHAR s1[];
LONGCARD O_2;
CHAR s2[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR) + O_2 * sizeof(CHAR), 2)
  COPY_OPEN_ARRAY(s2, O_1, CHAR)
  COPY_OPEN_ARRAY(s1, O_2, CHAR)
  if (i < 0) {
    IO_WriteS((System_tFile)IO_StdError, s1, O_2);
    IO_WriteS((System_tFile)IO_StdError, s2, O_1);
    IO_WriteNl((System_tFile)IO_StdError);
    IO_CloseIO();
    exit(1);
  }
  FREE_OPEN_ARRAYS
}

void Semantics_BeginSemantics
# ifdef __STDC__
()
# else
()
# endif
{
  System_tFile yyf;
  INTEGER yyi;

  yyf = OpenInput(Semantics_SemanticsTabName.A, 128L);
  yyErrorCheck(yyf, (STRING)"cannot open ", 12L, Semantics_SemanticsTabName.A, 128L);
  yyi = Read(yyf, ADR(yySets), (LONGINT)sizeof(yySetsType));
  yyErrorCheck(yyi, (STRING)"cannot read ", 12L, Semantics_SemanticsTabName.A, 128L);
  yyi = Read(yyf, ADR(yyComb), (LONGINT)sizeof(yyCombType));
  yyErrorCheck(yyi, (STRING)"cannot read ", 12L, Semantics_SemanticsTabName.A, 128L);
  Close(yyf);
}

void Semantics_DoSemantics
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyStateType yystate;

  yystate = yyTraverse(yyt);
  Analyse(yyt);
  yyReleaseHeap();
}

void Semantics_CloseSemantics
# ifdef __STDC__
()
# else
()
# endif
{
}

void Semantics__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    Tree__init();
    IO__init();
    Memory__init();
    System__init();
    Tree__init();
    ArgCheck__init();
    Codes__init();
    Derivable__init();
    Errors__init();
    Positions__init();
    First__init();
    Follow__init();
    Idents__init();
    Reachable__init();
    Scanner__init();
    Sets__init();
    Table__init();
    Tree__init();
    Types__init();

    (void)strncpy((char *)Semantics_SemanticsTabName.A, "Semantics.tab", sizeof(Semantics_SemanticsTabName.A));
    {
      register yyInfoType *W_1 = &yyInfo;

      W_1->Analyse.Cost = yyInfinite;
      W_1->Analyse.Proc = yyEAnalyse;
      W_1->Declare.Cost = yyInfinite;
      W_1->Declare.Proc = yyEDeclare;
      W_1->Declared.Cost = yyInfinite;
      W_1->Declared.Proc = yyEDeclared;
      W_1->Reduced.Cost = yyInfinite;
      W_1->Reduced.Proc = yyEReduced;
      W_1->LL1.Cost = yyInfinite;
      W_1->LL1.Proc = yyELL1;
      W_1->Recovery.Cost = yyInfinite;
      W_1->Recovery.Proc = yyERecovery;
      W_1->RecoveryAlt.Cost = yyInfinite;
      W_1->RecoveryAlt.Proc = yyERecoveryAlt;
      W_1->PrepareCode.Cost = yyInfinite;
      W_1->PrepareCode.Proc = yyEPrepareCode;
      W_1->PrepareCodeAlt.Cost = yyInfinite;
      W_1->PrepareCodeAlt.Proc = yyEPrepareCodeAlt;
    }
    yyBlockList = NIL;
    yyPoolFreePtr = (ADDRESS)NIL;
    yyPoolEndPtr = (ADDRESS)NIL;
  }
}
