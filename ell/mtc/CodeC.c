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

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Codes
#include "Codes.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_CodeC
#include "CodeC.h"
#endif

struct CodeC_1 CodeC_CodeCTabName;

#define cBitsPerChar   8
#define cBitsPerLong   32
static CHAR cDefinition [] = ".h";
static CHAR cImplementation [] = ".c";
static IO_tFile file;
static INTEGER SpaCo, Label;
static BOOLEAN vExport;
static BOOLEAN InDefault;
static Tree_tTree lSections;
static Strings_tString PathS, String;
static struct S_6 {
    CHAR A[128 + 1];
} PathA;
static void Prefix ARGS(());
static void Spaces ARGS(());
static void CodeIsElement ARGS((INTEGER index, Sets_tSet set));
static void CodeRecovery ARGS((INTEGER recover, INTEGER expect));
static void WriteLabels ARGS((Sets_tSet set));
static struct S_7 {
    INTEGER A[1000 + 1];
} *NumberArray;
static LONGINT NumberArraySize;
static struct S_8 {
    INTEGER A[1000 + 1];
} *MaxNumberArray;
static LONGINT MaxNumberArraySize;
static void ClearArray ARGS((INTEGER a[], LONGCARD ));
static void WriteAttributes ARGS(());
static struct S_10 {
    CHAR A[15 + 1];
} Hex;
static void WriteRecSets ARGS(());
static void WriteVerticalSet ARGS((INTEGER no));
struct S_29 {
    Sets_tSet A[cBitsPerChar - 1 + 1];
};
#define yyInfinite   715827882
#define yyBitsPerBitset   32
#define yySetSize   58
#define yyMaxIndex   32
#define yyCombSize   303
#define yyStartState   0
#define yyPoolSize   10240
typedef struct S_1 *yytBlockPtr;
typedef struct S_1 {
    yytBlockPtr Successor;
    struct S_11 {
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
typedef void (*yyPCODE) ARGS((Tree_tTree));
typedef void (*yyPCodeDef) ARGS((Tree_tTree));
typedef void (*yyPCodeImp) ARGS((Tree_tTree));
typedef void (*yyPCodeForward) ARGS((Tree_tTree));
typedef void (*yyPCodeRules) ARGS((Tree_tTree));
typedef void (*yyPCodeAltCase) ARGS((Tree_tTree, INTEGER, Sets_tSet));
typedef void (*yyPCodeAltIf) ARGS((Tree_tTree, BOOLEAN));
typedef void (*yyPSetNumbers) ARGS((Tree_tTree, BOOLEAN));
typedef void (*yyPCodeExport) ARGS((Tree_tTree));
typedef void (*yyPCodeGlobal) ARGS((Tree_tTree));
typedef void (*yyPCodeLocal) ARGS((Tree_tTree));
typedef void (*yyPCodeBegin) ARGS((Tree_tTree));
typedef void (*yyPCodeClose) ARGS((Tree_tTree));
typedef void (*yyPCodeCodes) ARGS((Tree_tTree));
typedef void (*yyPCodeCodes2) ARGS((Tree_tTree));
typedef struct S_5 *yyInfoPtr;
typedef struct S_5 {
    struct S_12 {
        INTEGER Cost;
        yyPCODE Proc;
    } CODE;
    struct S_13 {
        INTEGER Cost;
        yyPCodeDef Proc;
    } CodeDef;
    struct S_14 {
        INTEGER Cost;
        yyPCodeImp Proc;
    } CodeImp;
    struct S_15 {
        INTEGER Cost;
        yyPCodeForward Proc;
    } CodeForward;
    struct S_16 {
        INTEGER Cost;
        yyPCodeRules Proc;
    } CodeRules;
    struct S_17 {
        INTEGER Cost;
        yyPCodeAltCase Proc;
    } CodeAltCase;
    struct S_18 {
        INTEGER Cost;
        yyPCodeAltIf Proc;
    } CodeAltIf;
    struct S_19 {
        INTEGER Cost;
        yyPSetNumbers Proc;
    } SetNumbers;
    struct S_20 {
        INTEGER Cost;
        yyPCodeExport Proc;
    } CodeExport;
    struct S_21 {
        INTEGER Cost;
        yyPCodeGlobal Proc;
    } CodeGlobal;
    struct S_22 {
        INTEGER Cost;
        yyPCodeLocal Proc;
    } CodeLocal;
    struct S_23 {
        INTEGER Cost;
        yyPCodeBegin Proc;
    } CodeBegin;
    struct S_24 {
        INTEGER Cost;
        yyPCodeClose Proc;
    } CodeClose;
    struct S_25 {
        INTEGER Cost;
        yyPCodeCodes Proc;
    } CodeCodes;
    struct S_26 {
        INTEGER Cost;
        yyPCodeCodes2 Proc;
    } CodeCodes2;
} yyInfoType;
static yySetsType yySets;
static yyCombType yyComb;
static yyInfoType yyInfo;
static struct S_27 {
    BOOLEAN A[58 + 1];
} yyMatch;
static yytBlockPtr yyBlockList;
static ADDRESS yyPoolFreePtr, yyPoolEndPtr;
static ADDRESS yyAlloc ARGS(());
static void yyReleaseHeap ARGS(());
static void CODE ARGS((Tree_tTree yyt));
static void CodeDef ARGS((Tree_tTree yyt));
static void CodeImp ARGS((Tree_tTree yyt));
static void CodeForward ARGS((Tree_tTree yyt));
static void CodeRules ARGS((Tree_tTree yyt));
static void CodeAltCase ARGS((Tree_tTree yyt, INTEGER label, Sets_tSet labels));
static void CodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void CodeExport ARGS((Tree_tTree yyt));
static void CodeGlobal ARGS((Tree_tTree yyt));
static void CodeLocal ARGS((Tree_tTree yyt));
static void CodeBegin ARGS((Tree_tTree yyt));
static void CodeClose ARGS((Tree_tTree yyt));
static void CodeCodes ARGS((Tree_tTree yyt));
static void CodeCodes2 ARGS((Tree_tTree yyt));
static void yyECODE ARGS((Tree_tTree yyt));
static void yyECodeDef ARGS((Tree_tTree yyt));
static void yyECodeImp ARGS((Tree_tTree yyt));
static void yyECodeForward ARGS((Tree_tTree yyt));
static void yyECodeRules ARGS((Tree_tTree yyt));
static void yyECodeAltCase ARGS((Tree_tTree yyt, INTEGER label, Sets_tSet labels));
static void yyECodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void yyESetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyECodeExport ARGS((Tree_tTree yyt));
static void yyECodeGlobal ARGS((Tree_tTree yyt));
static void yyECodeLocal ARGS((Tree_tTree yyt));
static void yyECodeBegin ARGS((Tree_tTree yyt));
static void yyECodeClose ARGS((Tree_tTree yyt));
static void yyECodeCodes ARGS((Tree_tTree yyt));
static void yyECodeCodes2 ARGS((Tree_tTree yyt));
static void yyF1CODE ARGS((Tree_tTree yyt));
static void yyF2CodeDef ARGS((Tree_tTree yyt));
static void yyF3CodeImp ARGS((Tree_tTree yyt));
static void yyF4CodeImp ARGS((Tree_tTree yyt));
static void yyF5CodeForward ARGS((Tree_tTree yyt));
static void yyF6CodeForward ARGS((Tree_tTree yyt));
static void yyF7CodeRules ARGS((Tree_tTree yyt));
static void yyF8CodeRules ARGS((Tree_tTree yyt));
static void yyF9CodeRules ARGS((Tree_tTree yyt));
static void yyF10CodeRules ARGS((Tree_tTree yyt));
static void yyF11CodeRules ARGS((Tree_tTree yyt));
static void yyF12CodeRules ARGS((Tree_tTree yyt));
static void yyF13CodeRules ARGS((Tree_tTree yyt));
static void yyF14CodeRules ARGS((Tree_tTree yyt));
static void yyF15CodeRules ARGS((Tree_tTree yyt));
static void yyF16CodeRules ARGS((Tree_tTree yyt));
static void yyF17CodeRules ARGS((Tree_tTree yyt));
static void yyF18CodeRules ARGS((Tree_tTree yyt));
static void yyF19CodeRules ARGS((Tree_tTree yyt));
static void yyF20CodeRules ARGS((Tree_tTree yyt));
static void yyF21CodeRules ARGS((Tree_tTree yyt));
static void yyF22CodeRules ARGS((Tree_tTree yyt));
static void yyF23CodeRules ARGS((Tree_tTree yyt));
static void yyF24CodeAltCase ARGS((Tree_tTree yyt, INTEGER label, Sets_tSet labels));
static void yyF25CodeAltCase ARGS((Tree_tTree yyt, INTEGER label, Sets_tSet labels));
static void yyF26CodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void yyF27CodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void yyF28CodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void yyF29SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF30SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF31SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF32SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF33SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF34SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF35SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF36SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF37SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF38SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF39SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF40CodeExport ARGS((Tree_tTree yyt));
static void yyF41CodeExport ARGS((Tree_tTree yyt));
static void yyF42CodeExport ARGS((Tree_tTree yyt));
static void yyF43CodeGlobal ARGS((Tree_tTree yyt));
static void yyF44CodeGlobal ARGS((Tree_tTree yyt));
static void yyF45CodeGlobal ARGS((Tree_tTree yyt));
static void yyF46CodeLocal ARGS((Tree_tTree yyt));
static void yyF47CodeLocal ARGS((Tree_tTree yyt));
static void yyF48CodeLocal ARGS((Tree_tTree yyt));
static void yyF49CodeBegin ARGS((Tree_tTree yyt));
static void yyF50CodeBegin ARGS((Tree_tTree yyt));
static void yyF51CodeBegin ARGS((Tree_tTree yyt));
static void yyF52CodeClose ARGS((Tree_tTree yyt));
static void yyF53CodeClose ARGS((Tree_tTree yyt));
static void yyF54CodeClose ARGS((Tree_tTree yyt));
static void yyF55CodeCodes ARGS((Tree_tTree yyt));
static void yyF56CodeCodes ARGS((Tree_tTree yyt));
static void yyF57CodeCodes2 ARGS((Tree_tTree yyt));
static void yyF58CodeCodes2 ARGS((Tree_tTree yyt));
static INTEGER CostCODE ARGS((Tree_tTree yyt));
static INTEGER CostCodeDef ARGS((Tree_tTree yyt));
static INTEGER CostCodeImp ARGS((Tree_tTree yyt));
static INTEGER CostCodeForward ARGS((Tree_tTree yyt));
static INTEGER CostCodeRules ARGS((Tree_tTree yyt));
static INTEGER CostCodeAltCase ARGS((Tree_tTree yyt));
static INTEGER CostCodeAltIf ARGS((Tree_tTree yyt));
static INTEGER CostSetNumbers ARGS((Tree_tTree yyt));
static INTEGER CostCodeExport ARGS((Tree_tTree yyt));
static INTEGER CostCodeGlobal ARGS((Tree_tTree yyt));
static INTEGER CostCodeLocal ARGS((Tree_tTree yyt));
static INTEGER CostCodeBegin ARGS((Tree_tTree yyt));
static INTEGER CostCodeClose ARGS((Tree_tTree yyt));
static INTEGER CostCodeCodes ARGS((Tree_tTree yyt));
static INTEGER CostCodeCodes2 ARGS((Tree_tTree yyt));
static yyStateType yyTraverse ARGS((Tree_tTree yyt));
static void yyErrorCheck ARGS((INTEGER i, CHAR s1[], LONGCARD , CHAR s2[], LONGCARD ));


static void Prefix
# ifdef __STDC__
()
# else
()
# endif
{
  if (Tree_ScannerName != Idents_NoIdent) {
    Spaces();
    Idents_WriteIdent(file, Tree_ScannerName);
    IO_WriteS(file, (STRING)"_", 1L);
  }
}

static void Spaces
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER i;

  {
    LONGINT B_1 = 1, B_2 = SpaCo;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        IO_WriteS(file, (STRING)"  ", 2L);
        if (i >= B_2) break;
      }
  }
}

static void CodeIsElement
# ifdef __STDC__
(INTEGER index, Sets_tSet set)
# else
(index, set)
INTEGER index;
Sets_tSet set;
# endif
{
  Sets_tSet todo;
  Idents_tIdent id;
  INTEGER sl;

  if (index == Codes_cNoIndex) {
    Sets_MakeSet(&todo, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&todo, set);
    Sets_Exclude(&todo, (Sets_tElement)Scanner_Epsilon);
    if (!Sets_IsEmpty(todo)) {
      for (;;) {
        id = Sets_Extract(&todo);
        IO_WriteS(file, (STRING)"(xxToken == ", 12L);
        IO_WriteI(file, Codes_Code(id), 0L);
        IO_WriteS(file, (STRING)" /* ", 4L);
        Idents_WriteIdent(file, id);
        IO_WriteS(file, (STRING)" */)", 4L);
        if (Sets_IsEmpty(todo)) {
          goto EXIT_1;
        }
        IO_WriteS(file, (STRING)" || ", 4L);
      } EXIT_1:;
    }
    Sets_ReleaseSet(&todo);
  } else {
    sl = index / cBitsPerChar;
    IO_WriteS(file, (STRING)"(xxVerticalSet [xxToken", 23L);
    if (sl != 0) {
      IO_WriteS(file, (STRING)" + ", 3L);
      IO_WriteI(file, sl * (Codes_MaxCode() + 1), 0L);
    }
    IO_WriteS(file, (STRING)"] & 1 << ", 9L);
    IO_WriteI(file, index % cBitsPerChar, 0L);
    IO_WriteS(file, (STRING)" /* ", 4L);
    Codes_WriteIndex(file, index);
    IO_WriteS(file, (STRING)" */)", 4L);
  }
}

static void CodeRecovery
# ifdef __STDC__
(INTEGER recover, INTEGER expect)
# else
(recover, expect)
INTEGER recover, expect;
# endif
{
  if (expect == Codes_cNoIndex) {
    IO_WriteS(file, (STRING)"xxUnexpected (", 14L);
    IO_WriteI(file, recover, 0L);
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet); /* ", 27L);
    Codes_WriteRecIndex(file, recover);
    IO_WriteS(file, (STRING)" */", 3L);
    IO_WriteNl(file);
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"xxExpected (", 12L);
    IO_WriteI(file, expect, 0L);
    IO_WriteS(file, (STRING)", ", 2L);
    IO_WriteI(file, recover, 0L);
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet); /* ", 27L);
    Codes_WriteRecIndex(file, expect);
    IO_WriteS(file, (STRING)" / ", 3L);
    Codes_WriteRecIndex(file, recover);
    IO_WriteS(file, (STRING)" */", 3L);
    IO_WriteNl(file);
  }
}

static void WriteLabels
# ifdef __STDC__
(Sets_tSet set)
# else
(set)
Sets_tSet set;
# endif
{
  Sets_tSet todo;
  Idents_tIdent id;

  Sets_MakeSet(&todo, (Sets_tElement)Idents_MaxIdent());
  Sets_Assign(&todo, set);
  while (!Sets_IsEmpty(todo)) {
    id = Sets_Extract(&todo);
    Spaces();
    IO_WriteS(file, (STRING)"case ", 5L);
    IO_WriteI(file, Codes_Code(id), 0L);
    IO_WriteS(file, (STRING)" /* ", 4L);
    Idents_WriteIdent(file, id);
    IO_WriteS(file, (STRING)" */ :; ", 7L);
    IO_WriteNl(file);
  }
  Sets_ReleaseSet(&todo);
}

static void ClearArray
# ifdef __STDC__
(INTEGER a[], LONGCARD O_1)
# else
(a, O_1)
INTEGER a[];
LONGCARD O_1;
# endif
{
  Idents_tIdent id;

  {
    SHORTCARD B_3 = 0, B_4 = Idents_MaxIdent();

    if (B_3 <= B_4)
      for (id = B_3;; id += 1) {
        a[id] = 0;
        if (id >= B_4) break;
      }
  }
}

static void WriteAttributes
# ifdef __STDC__
()
# else
()
# endif
{
  Idents_tIdent id;
  INTEGER i, max;

  {
    SHORTCARD B_5 = 0, B_6 = Idents_MaxIdent();

    if (B_5 <= B_6)
      for (id = B_5;; id += 1) {
        max = MaxNumberArray->A[id];
        if (max > 0) {
          if (Types_IsTerm(id)) {
            IO_WriteS(file, (STRING)"  ", 2L);
            Prefix();
            IO_WriteS(file, (STRING)"tScanAttribute ", 15L);
          } else {
            IO_WriteS(file, (STRING)"  ", 2L);
            Idents_WriteIdent(file, Tree_ParserName);
            IO_WriteS(file, (STRING)"_tParsAttribute ", 16L);
          }
          {
            LONGINT B_7 = 1, B_8 = max - 1;

            if (B_7 <= B_8)
              for (i = B_7;; i += 1) {
                Idents_WriteIdent(file, id);
                IO_WriteI(file, i, 0L);
                IO_WriteS(file, (STRING)", ", 2L);
                if (i >= B_8) break;
              }
          }
          Idents_WriteIdent(file, id);
          IO_WriteI(file, max, 0L);
          IO_WriteS(file, (STRING)";", 1L);
          IO_WriteNl(file);
        }
        if (id >= B_6) break;
      }
  }
}

static void WriteRecSets
# ifdef __STDC__
()
# else
()
# endif
{
  INTEGER value;
  Sets_tSet set;
  INTEGER no, bit, bitvalue;
  INTEGER index;

  Sets_MakeSet(&set, (Sets_tElement)Codes_MaxCode());
  {
    LONGINT B_9 = 0, B_10 = Codes_vMaxRecSetIndex;

    if (B_9 <= B_10)
      for (index = B_9;; index += 1) {
        Codes_GetRecSet(index, &set);
        IO_WriteS(file, (STRING)"  {", 3L);
        {
          LONGINT B_11 = 0, B_12 = Codes_MaxCode() / cBitsPerLong;

          if (B_11 <= B_12)
            for (no = B_11;; no += 1) {
              IO_WriteS(file, (STRING)" 0x", 3L);
              for (bit = 0; bit <= cBitsPerLong - 1; bit += 1) {
                if (bit % 4 == 0) {
                  value = 0;
                  bitvalue = 8;
                }
                if (Sets_IsElement((Sets_tElement)(no * cBitsPerLong + bit), &set)) {
                  INC1(value, bitvalue);
                }
                bitvalue = bitvalue / 2;
                if (bit % 4 == 3) {
                  IO_WriteC(file, Hex.A[value]);
                }
              }
              IO_WriteS(file, (STRING)"L,", 2L);
              if (no % 4 == 3) {
                IO_WriteNl(file);
              }
              if (no >= B_12) break;
            }
        }
        IO_WriteS(file, (STRING)" },", 3L);
        IO_WriteNl(file);
        if (index >= B_10) break;
      }
  }
  Sets_ReleaseSet(&set);
}

static void WriteVerticalSet
# ifdef __STDC__
(INTEGER no)
# else
(no)
INTEGER no;
# endif
{
  struct S_29 sets;
  INTEGER code, bit;
  INTEGER index;
  INTEGER value, bitvalue;

  for (bit = 0; bit <= cBitsPerChar - 1; bit += 1) {
    Sets_MakeSet(&sets.A[bit], (Sets_tElement)Codes_MaxCode());
    index = no * cBitsPerChar + bit;
    Codes_GetSet(index, &sets.A[bit]);
  }
  {
    LONGINT B_13 = 0, B_14 = Codes_MaxCode();

    if (B_13 <= B_14)
      for (code = B_13;; code += 1) {
        if (code % 8 == 0) {
          IO_WriteNl(file);
        }
        IO_WriteS(file, (STRING)" 0x", 3L);
        for (bit = cBitsPerChar - 1; bit >= 0; bit += -1) {
          if (bit % 4 == 3) {
            value = 0;
            bitvalue = 8;
          }
          if (Sets_IsElement((Sets_tElement)code, &sets.A[bit])) {
            INC1(value, bitvalue);
          }
          if (bit % 4 == 0) {
            IO_WriteC(file, Hex.A[value]);
          }
          bitvalue = bitvalue / 2;
        }
        IO_WriteS(file, (STRING)",", 1L);
        if (code >= B_14) break;
      }
  }
  IO_WriteNl(file);
  for (bit = 0; bit <= cBitsPerChar - 1; bit += 1) {
    Sets_ReleaseSet(&sets.A[bit]);
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

static void CODE
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CODE.Proc)(yyt);
}

static void CodeDef
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeDef.Proc)(yyt);
}

static void CodeImp
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeImp.Proc)(yyt);
}

static void CodeForward
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeForward.Proc)(yyt);
}

static void CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeRules.Proc)(yyt);
}

static void CodeAltCase
# ifdef __STDC__
(Tree_tTree yyt, INTEGER label, Sets_tSet labels)
# else
(yyt, label, labels)
Tree_tTree yyt;
INTEGER label;
Sets_tSet labels;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeAltCase.Proc)(yyt, label, labels);
}

static void CodeAltIf
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN started)
# else
(yyt, started)
Tree_tTree yyt;
BOOLEAN started;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeAltIf.Proc)(yyt, started);
}

static void SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->SetNumbers.Proc)(yyt, start);
}

static void CodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeExport.Proc)(yyt);
}

static void CodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeGlobal.Proc)(yyt);
}

static void CodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeLocal.Proc)(yyt);
}

static void CodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeBegin.Proc)(yyt);
}

static void CodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeClose.Proc)(yyt);
}

static void CodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeCodes.Proc)(yyt);
}

static void CodeCodes2
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeCodes2.Proc)(yyt);
}

static void yyECODE
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CODE is not defined for this tree", 42L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeDef
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeDef is not defined for this tree", 45L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeImp
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeImp is not defined for this tree", 45L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeForward
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeForward is not defined for this tree", 49L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeRules is not defined for this tree", 47L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeAltCase
# ifdef __STDC__
(Tree_tTree yyt, INTEGER label, Sets_tSet labels)
# else
(yyt, label, labels)
Tree_tTree yyt;
INTEGER label;
Sets_tSet labels;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeAltCase is not defined for this tree", 49L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeAltIf
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN started)
# else
(yyt, started)
Tree_tTree yyt;
BOOLEAN started;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeAltIf is not defined for this tree", 47L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyESetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function SetNumbers is not defined for this tree", 48L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeExport is not defined for this tree", 48L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeGlobal is not defined for this tree", 48L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeLocal is not defined for this tree", 47L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeBegin is not defined for this tree", 47L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeClose is not defined for this tree", 47L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeCodes is not defined for this tree", 47L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyECodeCodes2
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Function CodeCodes2 is not defined for this tree", 48L);
  IO_WriteNl((System_tFile)IO_StdError);
  IO_CloseIO();
  exit(1);
}

static void yyF1CODE
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (ArgCheck_DEF) {
    CodeDef(yyt);
  }
  if (ArgCheck_IMP) {
    CodeImp(yyt);
  }
}

static void yyF2CodeDef
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Idents_GetString(Tree_ParserName, &PathS);
  Strings_ArrayToString(cDefinition, 2L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  if (Tree_ScannerName != Idents_NoIdent) {
    Spaces();
    IO_WriteS(file, (STRING)"# include \"", 11L);
    Idents_WriteIdent(file, Tree_ScannerName);
    IO_WriteS(file, (STRING)".h\"", 3L);
    IO_WriteNl(file);
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"# include \"Scanner.h\"", 21L);
    IO_WriteNl(file);
  }
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# define ARGS(parameters)	parameters", 36L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# define ARGS(parameters)	()", 28L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  CodeExport(yyt->U_1.V_3.Grammar.sections);
  if (!vExport) {
    Spaces();
    IO_WriteS(file, (STRING)"typedef	", 8L);
    Prefix();
    IO_WriteS(file, (STRING)"tScanAttribute ", 15L);
    Idents_WriteIdent(file, Tree_ParserName);
    IO_WriteS(file, (STRING)"_tParsAttribute;", 16L);
    IO_WriteNl(file);
  }
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"extern	", 7L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_tParsAttribute ", 16L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_ParsAttribute;", 15L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"extern	char *	", 14L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_TokenName [];", 14L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"extern	int	", 11L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"		();", 5L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"extern	void	Close", 17L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"	();", 4L);
  IO_WriteNl(file);
  IO_WriteClose(file);
}

static void yyF3CodeImp
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  INTEGER i;
  CARDINAL j;
  Sets_tSet set;
  Idents_tIdent id;
  Strings_tString s;
  CHAR c;

  Idents_GetString(Tree_ParserName, &PathS);
  Strings_ArrayToString(cImplementation, 2L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  Spaces();
  IO_WriteS(file, (STRING)"# include	\"", 11L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)".h\"", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# include	\"Errors.h\"", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# define	xxbool	char", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# define	xxtrue	1", 17L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# define	xxfalse	0", 18L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# define	xxEof	0", 16L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  CodeGlobal(yyt->U_1.V_3.Grammar.sections);
  lSections = yyt->U_1.V_3.Grammar.sections;
  Spaces();
  IO_WriteS(file, (STRING)"typedef struct xxsUnion {", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	  struct xxsUnion *	xxGlobalRecoverySet;", 41L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	  unsigned short	xxLocalRecoverySet;", 37L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	} xxtUnion, * xxtUnionPtr;", 27L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"typedef	long	xxtSet [", 21L);
  IO_WriteI(file, Codes_MaxCode() / cBitsPerLong + 1, 0L);
  IO_WriteS(file, (STRING)"];", 2L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_tParsAttribute	", 16L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_ParsAttribute;", 15L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static short	xxToken;", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static int	xxErrorCount;", 24L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static xxbool	xxIsInitialized = xxfalse, xxIsRepairMode = xxfalse;", 66L);
  IO_WriteNl(file);
  if (Codes_vMaxRecSetIndex == Codes_cNoIndex) {
    Spaces();
    IO_WriteS(file, (STRING)"static long	xxHorizontalSet [] = { 0 };", 39L);
    IO_WriteNl(file);
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"static long	xxHorizontalSet [] [", 32L);
    IO_WriteI(file, Codes_MaxCode() / cBitsPerLong + 1, 0L);
    IO_WriteS(file, (STRING)"] = {", 5L);
    IO_WriteNl(file);
    WriteRecSets();
    Spaces();
    IO_WriteS(file, (STRING)"};", 2L);
    IO_WriteNl(file);
  }
  Spaces();
  IO_WriteS(file, (STRING)"static unsigned char xxVerticalSet [] = {", 41L);
  {
    LONGINT B_15 = 0, B_16 = Codes_vMaxSetIndex / cBitsPerChar;

    if (B_15 <= B_16)
      for (i = B_15;; i += 1) {
        WriteVerticalSet(i);
        if (i >= B_16) break;
      }
  }
  IO_WriteS(file, (STRING)"};", 2L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"char *		", 8L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_TokenName [] = {", 17L);
  IO_WriteNl(file);
  {
    LONGINT B_17 = 0, B_18 = Codes_MaxCode();

    if (B_17 <= B_18)
      for (i = B_17;; i += 1) {
        id = Codes_Term(i);
        if (id != Scanner_NoIdent) {
          Idents_GetString(id, &s);
          Spaces();
          IO_WriteS(file, (STRING)"\"", 1L);
          c = Strings_Char(&s, 1);
          if (c == '"' || c == '\'') {
            {
              LONGCARD B_19 = 2, B_20 = Strings_Length(&s) - 1;

              if (B_19 <= B_20)
                for (j = B_19;; j += 1) {
                  c = Strings_Char(&s, (Strings_tStringIndex)j);
                  if (c == '\\' || c == '"') {
                    IO_WriteC(file, '\\');
                  }
                  IO_WriteC(file, c);
                  if (j >= B_20) break;
                }
            }
          } else {
            {
              LONGCARD B_21 = 1, B_22 = Strings_Length(&s);

              if (B_21 <= B_22)
                for (j = B_21;; j += 1) {
                  c = Strings_Char(&s, (Strings_tStringIndex)j);
                  if (c == '\\' || c == '"') {
                    IO_WriteC(file, '\\');
                  }
                  IO_WriteC(file, c);
                  if (j >= B_22) break;
                }
            }
          }
          IO_WriteS(file, (STRING)"\",", 2L);
          IO_WriteNl(file);
        } else {
          Spaces();
          IO_WriteS(file, (STRING)"0,", 2L);
          IO_WriteNl(file);
        }
        if (i >= B_18) break;
      }
  }
  Spaces();
  IO_WriteS(file, (STRING)"};", 2L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  CodeForward(yyt->U_1.V_3.Grammar.rules);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static void Begin", 17L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" ()", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"if (xxIsInitialized) return;", 28L);
  IO_WriteNl(file);
  CodeBegin(yyt->U_1.V_3.Grammar.sections);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"void Close", 10L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" ()", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  CodeClose(yyt->U_1.V_3.Grammar.sections);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static xxbool xxIsElement", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(xxtSet xySet, short xxElement)", 31L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(xySet, xxElement) xxtSet xySet; short xxElement;", 49L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{ return xySet [xxElement / ", 28L);
  IO_WriteI(file, (LONGINT)cBitsPerLong, 0L);
  IO_WriteS(file, (STRING)"] << xxElement % ", 17L);
  IO_WriteI(file, (LONGINT)cBitsPerLong, 0L);
  IO_WriteS(file, (STRING)" < 0; }", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static void xxSkipTokens", 24L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(unsigned short xxLocalRecoverySet, xxtUnionPtr xxGlobalRecoverySet)", 68L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(xxLocalRecoverySet, xxGlobalRecoverySet)", 41L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"unsigned short	xxLocalRecoverySet;", 34L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxtUnionPtr	xxGlobalRecoverySet;", 32L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxbool xxTokensSkipped = xxfalse;", 35L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxtSet xxRecoverySet;", 23L);
  IO_WriteNl(file);
  {
    LONGINT B_23 = 0, B_24 = Codes_MaxCode() / cBitsPerLong;

    if (B_23 <= B_24)
      for (i = B_23;; i += 1) {
        Spaces();
        IO_WriteS(file, (STRING)"  xxRecoverySet [", 17L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"] = xxHorizontalSet [xxLocalRecoverySet] [", 42L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"];", 2L);
        IO_WriteNl(file);
        if (i >= B_24) break;
      }
  }
  Spaces();
  IO_WriteS(file, (STRING)"  xxRecoverySet [0] |= (unsigned long) 0x80000000L; /* INCL (xxRecoverySet [0], xxEof); */", 90L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  while (xxGlobalRecoverySet != (xxtUnionPtr) 0L) {", 51L);
  IO_WriteNl(file);
  {
    LONGINT B_25 = 0, B_26 = Codes_MaxCode() / cBitsPerLong;

    if (B_25 <= B_26)
      for (i = B_25;; i += 1) {
        Spaces();
        IO_WriteS(file, (STRING)"    xxRecoverySet [", 19L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"] |= xxHorizontalSet [xxGlobalRecoverySet->xxLocalRecoverySet] [", 64L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"];", 2L);
        IO_WriteNl(file);
        if (i >= B_26) break;
      }
  }
  Spaces();
  IO_WriteS(file, (STRING)"    xxGlobalRecoverySet = xxGlobalRecoverySet->xxGlobalRecoverySet;", 67L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  while (! xxIsElement (xxRecoverySet, xxToken)) {", 50L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxToken = ", 14L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken (); xxTokensSkipped = xxtrue;", 38L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (xxTokensSkipped) ErrorMessage (xxRestartPoint, xxInformation, ", 68L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position);", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxIsRepairMode = xxtrue;", 26L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static void xxUnexpected", 24L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(unsigned short xxLocalRecoverySet, xxtUnionPtr xxGlobalRecoverySet)", 68L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(xxLocalRecoverySet, xxGlobalRecoverySet)", 41L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"unsigned short	xxLocalRecoverySet;", 34L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxtUnionPtr	xxGlobalRecoverySet;", 32L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (! xxIsRepairMode) {", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxErrorCount ++;", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessage (xxSyntaxError, xxError, ", 42L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position);", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxSkipTokens (xxLocalRecoverySet, xxGlobalRecoverySet);", 59L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static void xxExpected", 22L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(unsigned short xxExpectedSet, unsigned short xxLocalRecoverySet, xxtUnionPtr xxGlobalRecoverySet)", 98L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(xxExpectedSet, xxLocalRecoverySet, xxGlobalRecoverySet)", 56L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"unsigned short	xxExpectedSet, xxLocalRecoverySet;", 49L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxtUnionPtr	xxGlobalRecoverySet;", 32L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (! xxIsRepairMode) {", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    short yxToken;", 18L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    int xxLength = 0;", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    char xxContinueString [256];", 32L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxErrorCount ++;", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessage (xxSyntaxError, xxError, ", 42L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position);", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxContinueString [0] = '\\0';", 32L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    for (yxToken = 0; yxToken <= ", 33L);
  IO_WriteI(file, Codes_MaxCode(), 0L);
  IO_WriteS(file, (STRING)"; yxToken ++)", 13L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      if (xxIsElement (xxHorizontalSet [xxExpectedSet], yxToken)) {", 67L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	char * xxTokenString = ", 24L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_TokenName [yxToken];", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	if ((xxLength += strlen (xxTokenString) + 1) >= 256) break;", 60L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	(void) strcat (xxContinueString, xxTokenString);", 49L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	(void) strcat (xxContinueString, \" \");", 39L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      }", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessageI (xxExpectedTokens, xxInformation, ", 52L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position, xxString, xxContinueString);", 48L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxSkipTokens (xxLocalRecoverySet, xxGlobalRecoverySet);", 59L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static void xxRecoveryLiteral", 29L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(unsigned short xxExpected, unsigned short xxLocalRecoverySet, xxtUnionPtr xxGlobalRecoverySet)", 95L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(xxExpected, xxLocalRecoverySet, xxGlobalRecoverySet)", 53L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"unsigned short	xxExpected, xxLocalRecoverySet;", 46L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxtUnionPtr	xxGlobalRecoverySet;", 32L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (! xxIsRepairMode) {", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxErrorCount ++;", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessage (xxSyntaxError, xxError, ", 42L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position);", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessageI (xxExpectedTokens, xxInformation, ", 52L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position, xxString, ", 30L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_TokenName [xxExpected]);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxSkipTokens (xxLocalRecoverySet, xxGlobalRecoverySet);", 59L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (xxToken != xxExpected) {", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessageI (xxTokenInserted, xxRepair, ", 46L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position, xxString, ", 30L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_TokenName [xxExpected]);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  } else {", 10L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    if (xxToken != xxEof) xxToken = ", 36L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken ();", 12L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxIsRepairMode = xxfalse;", 29L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"static void xxRecoveryTerminal", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(unsigned short xxExpected, unsigned short xxLocalRecoverySet,", 62L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxtUnionPtr xxGlobalRecoverySet, ", 33L);
  Prefix();
  IO_WriteS(file, (STRING)"tScanAttribute * xxRepairAttribute)", 35L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(xxExpected, xxLocalRecoverySet, xxGlobalRecoverySet, xxRepairAttribute)", 72L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"unsigned short	xxExpected, xxLocalRecoverySet;", 46L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxtUnionPtr	xxGlobalRecoverySet;", 32L);
  IO_WriteNl(file);
  Prefix();
  Spaces();
  IO_WriteS(file, (STRING)"tScanAttribute	* xxRepairAttribute;", 35L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (! xxIsRepairMode) {", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxErrorCount ++;", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessage (xxSyntaxError, xxError, ", 42L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position);", 20L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessageI (xxExpectedTokens, xxInformation, ", 52L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position, xxString, ", 30L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_TokenName [xxExpected]);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxSkipTokens (xxLocalRecoverySet, xxGlobalRecoverySet);", 59L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (xxToken != xxExpected) {", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ErrorMessageI (xxTokenInserted, xxRepair, ", 46L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute.Position, xxString, ", 30L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_TokenName [xxExpected]);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ", 4L);
  Prefix();
  IO_WriteS(file, (STRING)"ErrorAttribute ((int) xxExpected, xxRepairAttribute);", 53L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  } else {", 10L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    * xxRepairAttribute = ", 26L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute;", 10L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    if (xxToken != xxEof) xxToken = ", 36L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken ();", 12L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxIsRepairMode = xxfalse;", 29L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  }", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"int ", 4L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" ()", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxErrorCount = 0;", 19L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  Begin", 7L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" ();", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxToken = ", 12L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken ();", 12L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  yy", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_3.Grammar.rules->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" (& ", 4L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_ParsAttribute, (xxtUnionPtr) 0L);", 34L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  if (xxToken != xxEof) xxRecoveryLiteral (xxEof, 0, (xxtUnionPtr) 0L);", 71L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  return xxErrorCount;", 22L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  NumberArraySize = Idents_MaxIdent() + 1;
  MaxNumberArraySize = Idents_MaxIdent() + 1;
  DynArray_MakeArray((ADDRESS *)&NumberArray, &NumberArraySize, (LONGINT)sizeof(INTEGER));
  DynArray_MakeArray((ADDRESS *)&MaxNumberArray, &MaxNumberArraySize, (LONGINT)sizeof(INTEGER));
  CodeRules(yyt->U_1.V_3.Grammar.rules);
  DynArray_ReleaseArray((ADDRESS *)&NumberArray, &NumberArraySize, (LONGINT)sizeof(INTEGER));
  DynArray_ReleaseArray((ADDRESS *)&MaxNumberArray, &MaxNumberArraySize, (LONGINT)sizeof(INTEGER));
  IO_WriteClose(file);
}

static void yyF4CodeImp
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Errors_ERROR((STRING)"CodeM2.ESTRA: no rules", 22L);
}

static void yyF5CodeForward
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF6CodeForward
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"static void yy", 14L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" ARGS((", 7L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_tParsAttribute * ", 18L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)"0, xxtUnionPtr xxGlobalRecoverySet));", 37L);
  IO_WriteNl(file);
  CodeForward(yyt->U_1.V_29.Rules.rules);
}

static void yyF7CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF8CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  ClearArray((*MaxNumberArray).A, 1001L);
  SetNumbers(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr, TRUE);
  Spaces();
  IO_WriteS(file, (STRING)"static void yy", 14L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(", 1L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_tParsAttribute * ", 18L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)"0, xxtUnionPtr xxGlobalRecoverySet)", 35L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# else", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"(", 1L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)"0, xxGlobalRecoverySet)", 23L);
  IO_WriteNl(file);
  Spaces();
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)"_tParsAttribute	* ", 18L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)"0;", 2L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxtUnionPtr	xxGlobalRecoverySet;", 32L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"# endif", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"{", 1L);
  IO_WriteNl(file);
  INC(SpaCo);
  WriteAttributes();
  if (yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.iscalling) {
    Spaces();
    IO_WriteS(file, (STRING)"xxtUnion xxUnion;", 17L);
    IO_WriteNl(file);
  }
  CodeLocal(lSections);
  CodeCodes(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.codes);
  if (yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.iscalling) {
    Spaces();
    IO_WriteS(file, (STRING)"xxUnion.xxGlobalRecoverySet = xxGlobalRecoverySet;", 50L);
    IO_WriteNl(file);
  }
  CodeRules(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  CodeRules(yyt->U_1.V_29.Rules.rules);
}

static void yyF9CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"for (;;) {", 10L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"if (", 4L);
  CodeIsElement(yyt->U_1.V_33.Option.index, yyt->U_1.V_33.Option.expr->U_1.V_32.expr.first);
  IO_WriteS(file, (STRING)") {", 3L);
  IO_WriteNl(file);
  INC(SpaCo);
  InDefault = FALSE;
  CodeRules(yyt->U_1.V_33.Option.expr);
  Spaces();
  IO_WriteS(file, (STRING)"break;", 6L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"} else if (", 11L);
  CodeIsElement(yyt->U_1.V_33.Option.followindex, yyt->U_1.V_33.Option.follow);
  IO_WriteS(file, (STRING)" || xxIsRepairMode) break;", 26L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_33.Option.recindex, yyt->U_1.V_33.Option.expindex);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF10CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"for (;;) {", 10L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"if (", 4L);
  CodeIsElement(yyt->U_1.V_34.Times.index, yyt->U_1.V_34.Times.expr->U_1.V_32.expr.first);
  IO_WriteS(file, (STRING)") {", 3L);
  IO_WriteNl(file);
  INC(SpaCo);
  InDefault = FALSE;
  CodeRules(yyt->U_1.V_34.Times.expr);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"} else if (", 11L);
  CodeIsElement(yyt->U_1.V_34.Times.followindex, yyt->U_1.V_34.Times.follow);
  IO_WriteS(file, (STRING)" || xxIsRepairMode) break;", 26L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"else", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRecovery(yyt->U_1.V_34.Times.recindex, yyt->U_1.V_34.Times.expindex);
  DEC(SpaCo);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF11CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"for (;;) {", 10L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_35.Plus.expr);
  Spaces();
  IO_WriteS(file, (STRING)"if (! (", 7L);
  CodeIsElement(yyt->U_1.V_35.Plus.index, yyt->U_1.V_35.Plus.expr->U_1.V_32.expr.first);
  IO_WriteS(file, (STRING)")) {", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"if (", 4L);
  CodeIsElement(yyt->U_1.V_35.Plus.followindex, yyt->U_1.V_35.Plus.follow);
  IO_WriteS(file, (STRING)") break;", 8L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_35.Plus.recindex, yyt->U_1.V_35.Plus.expindex);
  Spaces();
  IO_WriteS(file, (STRING)"if (! (", 7L);
  CodeIsElement(yyt->U_1.V_35.Plus.index, yyt->U_1.V_35.Plus.first);
  IO_WriteS(file, (STRING)")) break;", 9L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF12CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"for (;;) {", 10L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_36.List.body);
  Spaces();
  IO_WriteS(file, (STRING)"if (! (", 7L);
  CodeIsElement(yyt->U_1.V_36.List.sep->U_1.V_32.expr.index, yyt->U_1.V_36.List.sep->U_1.V_32.expr.first);
  IO_WriteS(file, (STRING)")) {", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"if (", 4L);
  CodeIsElement(yyt->U_1.V_36.List.followindex, yyt->U_1.V_36.List.follow);
  IO_WriteS(file, (STRING)") break;", 8L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_36.List.recindex, yyt->U_1.V_36.List.expindex);
  Spaces();
  IO_WriteS(file, (STRING)"if (! (", 7L);
  CodeIsElement(yyt->U_1.V_36.List.sep->U_1.V_32.expr.index, yyt->U_1.V_36.List.sep->U_1.V_32.expr.first);
  IO_WriteS(file, (STRING)" || ", 4L);
  CodeIsElement(yyt->U_1.V_36.List.index, yyt->U_1.V_36.List.first);
  IO_WriteS(file, (STRING)")) break;", 9L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  CodeRules(yyt->U_1.V_36.List.sep);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF13CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF14CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeCodes(yyt->U_1.V_37.Action.codes);
}

static void yyF15CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (InDefault) {
    Spaces();
    IO_WriteS(file, (STRING)"if (xxToken != ", 15L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)" /* ", 4L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteS(file, (STRING)" */)", 4L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxRecoveryTerminal (", 22L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)", ", 2L);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet, & ", 25L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
    IO_WriteS(file, (STRING)"); /* ", 6L);
    Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
    IO_WriteS(file, (STRING)" */", 3L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"else {", 6L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  ", 2L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
    IO_WriteS(file, (STRING)" = ", 3L);
    Prefix();
    IO_WriteS(file, (STRING)"Attribute;", 10L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxToken = ", 12L);
    Prefix();
    IO_WriteS(file, (STRING)"GetToken (); xxIsRepairMode = xxfalse;", 38L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"}", 1L);
    IO_WriteNl(file);
    InDefault = FALSE;
  } else {
    Spaces();
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
    IO_WriteS(file, (STRING)" = ", 3L);
    Prefix();
    IO_WriteS(file, (STRING)"Attribute;", 10L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"xxToken = ", 10L);
    Prefix();
    IO_WriteS(file, (STRING)"GetToken (); xxIsRepairMode = xxfalse;", 38L);
    IO_WriteNl(file);
  }
}

static void yyF16CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (InDefault) {
    Spaces();
    IO_WriteS(file, (STRING)"if (xxToken != ", 15L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)" /* ", 4L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteS(file, (STRING)" */)", 4L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxRecoveryLiteral (", 21L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)", ", 2L);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet); /* ", 27L);
    Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
    IO_WriteS(file, (STRING)" */", 3L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"else {", 6L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxToken = ", 12L);
    Prefix();
    IO_WriteS(file, (STRING)"GetToken (); xxIsRepairMode = xxfalse;", 38L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"}", 1L);
    IO_WriteNl(file);
    InDefault = FALSE;
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"xxToken = ", 10L);
    Prefix();
    IO_WriteS(file, (STRING)"GetToken (); xxIsRepairMode = xxfalse;", 38L);
    IO_WriteNl(file);
  }
}

static void yyF17CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"if (xxToken != ", 15L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)" /* ", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" */)", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxRecoveryTerminal (", 22L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)", ", 2L);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
  IO_WriteS(file, (STRING)", xxGlobalRecoverySet, & ", 25L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
  IO_WriteS(file, (STRING)"); /* ", 6L);
  Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
  IO_WriteS(file, (STRING)" */", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"else {", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  ", 2L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
  IO_WriteS(file, (STRING)" = ", 3L);
  Prefix();
  IO_WriteS(file, (STRING)"Attribute;", 10L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxToken = ", 12L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken (); xxIsRepairMode = xxfalse;", 38L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF18CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"if (xxToken != ", 15L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)" /* ", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" */)", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxRecoveryLiteral (", 21L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)", ", 2L);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
  IO_WriteS(file, (STRING)", xxGlobalRecoverySet); /* ", 27L);
  Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
  IO_WriteS(file, (STRING)" */", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"else {", 6L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxToken = ", 12L);
  Prefix();
  IO_WriteS(file, (STRING)"GetToken (); xxIsRepairMode = xxfalse;", 38L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF19CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"xxUnion.xxLocalRecoverySet = ", 29L);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
  IO_WriteS(file, (STRING)"; yy", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" (& ", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
  IO_WriteS(file, (STRING)", & xxUnion); /* ", 17L);
  Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
  IO_WriteS(file, (STRING)" */", 3L);
  IO_WriteNl(file);
}

static void yyF20CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF21CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeRules(yyt->U_1.V_44.Sequence.expr);
  CodeRules(yyt->U_1.V_44.Sequence.sequence);
}

static void yyF22CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  INTEGER label;
  Sets_tSet labels;

  Sets_MakeSet(&labels, (Sets_tElement)Idents_MaxIdent());
  Spaces();
  IO_WriteS(file, (STRING)"for (;;) {", 10L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"switch (xxToken) {", 18L);
  IO_WriteNl(file);
  INC(Label);
  label = Label;
  CodeAltCase(yyt, label, labels);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xx", 2L);
  IO_WriteI(file, label, 0L);
  IO_WriteS(file, (STRING)":;", 2L);
  IO_WriteNl(file);
  Sets_ReleaseSet(&labels);
}

static void yyF23CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeAltIf(yyt, FALSE);
}

static void yyF24CodeAltCase
# ifdef __STDC__
(Tree_tTree yyt, INTEGER label, Sets_tSet labels)
# else
(yyt, label, labels)
Tree_tTree yyt;
INTEGER label;
Sets_tSet labels;
# endif
{
  CARDINAL l;
  Sets_tSet s;

  Sets_MakeSet(&s, (Sets_tElement)Codes_MaxCode());
  {
    LONGCARD B_27 = Sets_Minimum(&labels), B_28 = Sets_Maximum(&labels);

    if (B_27 <= B_28)
      for (l = B_27;; l += 1) {
        if (Sets_IsElement(l, &labels)) {
          Sets_Include(&s, (Sets_tElement)Codes_Code((SHORTCARD)l));
        }
        if (l >= B_28) break;
      }
  }
  {
    LONGCARD B_29 = Sets_Minimum(&s), B_30 = Sets_Maximum(&s);

    if (B_29 <= B_30)
      for (l = B_29;; l += 1) {
        if (!Sets_IsElement(l, &s)) {
          Spaces();
          IO_WriteS(file, (STRING)"case ", 5L);
          IO_WriteI(file, (LONGINT)l, 0L);
          IO_WriteS(file, (STRING)":;", 2L);
          IO_WriteNl(file);
        }
        if (l >= B_30) break;
      }
  }
  Spaces();
  IO_WriteS(file, (STRING)"default:", 8L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"if (xxIsRepairMode) {", 21L);
  IO_WriteNl(file);
  INC(SpaCo);
  InDefault = TRUE;
  CodeRules(yyt->U_1.V_40.Alternative0.C_0_default);
  InDefault = FALSE;
  Spaces();
  IO_WriteS(file, (STRING)"goto xx", 7L);
  IO_WriteI(file, label, 0L);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_40.Alternative0.recindex, yyt->U_1.V_40.Alternative0.expindex);
  DEC(SpaCo);
}

static void yyF25CodeAltCase
# ifdef __STDC__
(Tree_tTree yyt, INTEGER label, Sets_tSet labels)
# else
(yyt, label, labels)
Tree_tTree yyt;
INTEGER label;
Sets_tSet labels;
# endif
{
  WriteLabels(yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_41.Alternative.expr);
  Spaces();
  IO_WriteS(file, (STRING)"goto xx", 7L);
  IO_WriteI(file, label, 0L);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Sets_Union(&labels, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  CodeAltCase(yyt->U_1.V_41.Alternative.alternative, label, labels);
}

static void yyF26CodeAltIf
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN started)
# else
(yyt, started)
Tree_tTree yyt;
BOOLEAN started;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"} else {", 8L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRecovery(yyt->U_1.V_40.Alternative0.recindex, yyt->U_1.V_40.Alternative0.expindex);
  InDefault = TRUE;
  CodeRules(yyt->U_1.V_40.Alternative0.C_0_default);
  InDefault = FALSE;
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF27CodeAltIf
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN started)
# else
(yyt, started)
Tree_tTree yyt;
BOOLEAN started;
# endif
{
  if (!started) {
    Spaces();
    IO_WriteS(file, (STRING)"if (", 4L);
    CodeIsElement(yyt->U_1.V_41.Alternative.index, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.first);
    IO_WriteS(file, (STRING)") {", 3L);
    IO_WriteNl(file);
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"} else {", 8L);
    IO_WriteNl(file);
  }
  INC(SpaCo);
  CodeRules(yyt->U_1.V_41.Alternative.expr);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"}", 1L);
  IO_WriteNl(file);
}

static void yyF28CodeAltIf
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN started)
# else
(yyt, started)
Tree_tTree yyt;
BOOLEAN started;
# endif
{
  if (!started) {
    Spaces();
    IO_WriteS(file, (STRING)"if (", 4L);
  } else {
    IO_WriteS(file, (STRING)"} else if (", 11L);
  }
  CodeIsElement(yyt->U_1.V_41.Alternative.index, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  IO_WriteS(file, (STRING)") {", 3L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_41.Alternative.expr);
  DEC(SpaCo);
  CodeAltIf(yyt->U_1.V_41.Alternative.alternative, TRUE);
}

static void yyF29SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  SetNumbers(yyt->U_1.V_33.Option.expr, FALSE);
}

static void yyF30SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  SetNumbers(yyt->U_1.V_34.Times.expr, FALSE);
}

static void yyF31SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  SetNumbers(yyt->U_1.V_35.Plus.expr, FALSE);
}

static void yyF32SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  SetNumbers(yyt->U_1.V_36.List.body, FALSE);
  SetNumbers(yyt->U_1.V_36.List.sep, FALSE);
}

static void yyF33SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
}

static void yyF34SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
}

static void yyF35SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  SetNumbers(yyt->U_1.V_44.Sequence.expr, FALSE);
  SetNumbers(yyt->U_1.V_44.Sequence.sequence, FALSE);
}

static void yyF36SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
}

static void yyF37SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  SetNumbers(yyt->U_1.V_41.Alternative.expr, FALSE);
  SetNumbers(yyt->U_1.V_41.Alternative.alternative, start);
}

static void yyF38SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  yyt->U_1.V_38.Leaf.number = 0;
}

static void yyF39SetNumbers
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN start)
# else
(yyt, start)
Tree_tTree yyt;
BOOLEAN start;
# endif
{
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  yyt->U_1.V_38.Leaf.number = NumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident] + 1;
  NumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident] = yyt->U_1.V_38.Leaf.number;
  if (yyt->U_1.V_38.Leaf.number > MaxNumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident]) {
    MaxNumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident] = yyt->U_1.V_38.Leaf.number;
  }
}

static void yyF40CodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  vExport = TRUE;
  CodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_8.Export.codes);
  CodeExport(yyt->U_1.V_6.Sections.sections);
}

static void yyF41CodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeExport(yyt->U_1.V_6.Sections.sections);
}

static void yyF42CodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF43CodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_9.Global.codes);
  CodeGlobal(yyt->U_1.V_6.Sections.sections);
}

static void yyF44CodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeGlobal(yyt->U_1.V_6.Sections.sections);
}

static void yyF45CodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF46CodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_10.Local.codes);
  CodeLocal(yyt->U_1.V_6.Sections.sections);
}

static void yyF47CodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeLocal(yyt->U_1.V_6.Sections.sections);
}

static void yyF48CodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF49CodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_11.Begin.codes);
  CodeBegin(yyt->U_1.V_6.Sections.sections);
}

static void yyF50CodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeBegin(yyt->U_1.V_6.Sections.sections);
}

static void yyF51CodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF52CodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_12.Close.codes);
  CodeClose(yyt->U_1.V_6.Sections.sections);
}

static void yyF53CodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeClose(yyt->U_1.V_6.Sections.sections);
}

static void yyF54CodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF55CodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (ArgCheck_LINE) {
    IO_WriteS(file, (STRING)"# line ", 7L);
    IO_WriteI(file, (LONGINT)yyt->U_1.V_15.Codes.code->U_1.V_16.Code.pos.Line, 0L);
    IO_WriteS(file, (STRING)" \"", 2L);
    IO_WriteS(file, ArgCheck_SourceFileName.A, 128L);
    IO_WriteS(file, (STRING)"\"", 1L);
    IO_WriteNl(file);
  } else {
    IO_WriteS(file, (STRING)"/* line ", 8L);
    IO_WriteI(file, (LONGINT)yyt->U_1.V_15.Codes.code->U_1.V_16.Code.pos.Line, 0L);
    IO_WriteS(file, (STRING)" \"", 2L);
    IO_WriteS(file, ArgCheck_SourceFileName.A, 128L);
    IO_WriteS(file, (STRING)"\" */", 4L);
    IO_WriteNl(file);
  }
  StringMem_WriteString(file, yyt->U_1.V_15.Codes.code->U_1.V_16.Code.ref);
  CodeCodes2(yyt->U_1.V_15.Codes.codes);
  IO_WriteNl(file);
}

static void yyF56CodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF57CodeCodes2
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  StringMem_WriteString(file, yyt->U_1.V_15.Codes.code->U_1.V_16.Code.ref);
  CodeCodes2(yyt->U_1.V_15.Codes.codes);
}

static void yyF58CodeCodes2
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static INTEGER CostCODE
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CODE.Cost;
}

static INTEGER CostCodeDef
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeDef.Cost;
}

static INTEGER CostCodeImp
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeImp.Cost;
}

static INTEGER CostCodeForward
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeForward.Cost;
}

static INTEGER CostCodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeRules.Cost;
}

static INTEGER CostCodeAltCase
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeAltCase.Cost;
}

static INTEGER CostCodeAltIf
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeAltIf.Cost;
}

static INTEGER CostSetNumbers
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->SetNumbers.Cost;
}

static INTEGER CostCodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeExport.Cost;
}

static INTEGER CostCodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeGlobal.Cost;
}

static INTEGER CostCodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeLocal.Cost;
}

static INTEGER CostCodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeBegin.Cost;
}

static INTEGER CostCodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeClose.Cost;
}

static INTEGER CostCodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeCodes.Cost;
}

static INTEGER CostCodeCodes2
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  return InfoPtr->CodeCodes2.Cost;
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
    cost = 1 + CostCodeCodes2(yyt->U_1.V_15.Codes.codes);
    if (cost < info->CodeCodes.Cost) {
      info->CodeCodes.Cost = cost;
      info->CodeCodes.Proc = yyF55CodeCodes;
    }
    cost = 1 + CostCodeCodes2(yyt->U_1.V_15.Codes.codes);
    if (cost < info->CodeCodes2.Cost) {
      info->CodeCodes2.Cost = cost;
      info->CodeCodes2.Proc = yyF57CodeCodes2;
    }
    break;
  case Tree_Code:;
    state = 32;
    break;
  case Tree_Close:;
    state = 3;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_12.Close.codes)];
    break;
  case Tree_Grammar:;
    state = 18;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_3.Grammar.sections)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_3.Grammar.tokens)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_3.Grammar.rules)];
    match = (yySetType *)ADR(yySets.A[state]);
    yyMatch.A[3] = IN(3, match->A[0]);
    yyMatch.A[4] = IN(4, match->A[0]);
    cost = 1 + CostCodeExport(yyt->U_1.V_3.Grammar.sections);
    if (cost < info->CodeDef.Cost) {
      info->CodeDef.Cost = cost;
      info->CodeDef.Proc = yyF2CodeDef;
    }
    if (yyMatch.A[3]) {
      cost = 1 + CostCodeGlobal(yyt->U_1.V_3.Grammar.sections) + CostCodeBegin(yyt->U_1.V_3.Grammar.sections) + CostCodeClose(yyt->U_1.V_3.Grammar.sections) + CostCodeForward(yyt->U_1.V_3.Grammar.rules) + CostCodeRules(yyt->U_1.V_3.Grammar.rules);
      if (cost < info->CodeImp.Cost) {
        info->CodeImp.Cost = cost;
        info->CodeImp.Proc = yyF3CodeImp;
      }
    }
    if (yyMatch.A[4]) {
      cost = 1;
      if (cost < info->CodeImp.Cost) {
        info->CodeImp.Cost = cost;
        info->CodeImp.Proc = yyF4CodeImp;
      }
    }
    cost = 1 + CostCodeDef(yyt) + CostCodeImp(yyt);
    if (cost < info->CODE.Cost) {
      info->CODE.Cost = cost;
      info->CODE.Proc = yyF1CODE;
    }
    break;
  case Tree_Sections0:;
    state = 24;
    cost = 1;
    if (cost < info->CodeExport.Cost) {
      info->CodeExport.Cost = cost;
      info->CodeExport.Proc = yyF42CodeExport;
    }
    cost = 1;
    if (cost < info->CodeGlobal.Cost) {
      info->CodeGlobal.Cost = cost;
      info->CodeGlobal.Proc = yyF45CodeGlobal;
    }
    cost = 1;
    if (cost < info->CodeLocal.Cost) {
      info->CodeLocal.Cost = cost;
      info->CodeLocal.Proc = yyF48CodeLocal;
    }
    cost = 1;
    if (cost < info->CodeBegin.Cost) {
      info->CodeBegin.Cost = cost;
      info->CodeBegin.Proc = yyF51CodeBegin;
    }
    cost = 1;
    if (cost < info->CodeClose.Cost) {
      info->CodeClose.Cost = cost;
      info->CodeClose.Proc = yyF54CodeClose;
    }
    break;
  case Tree_Sections:;
    state = 17;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_6.Sections.section)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_6.Sections.sections)];
    match = (yySetType *)ADR(yySets.A[state]);
    yyMatch.A[40] = IN(8, match->A[1]);
    yyMatch.A[41] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Export;
    yyMatch.A[43] = IN(11, match->A[1]);
    yyMatch.A[44] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Global;
    yyMatch.A[46] = IN(14, match->A[1]);
    yyMatch.A[47] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Local;
    yyMatch.A[49] = IN(17, match->A[1]);
    yyMatch.A[50] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Begin;
    yyMatch.A[52] = IN(20, match->A[1]);
    yyMatch.A[53] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Close;
    if (yyMatch.A[40]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_8.Export.codes) + CostCodeExport(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeExport.Cost) {
        info->CodeExport.Cost = cost;
        info->CodeExport.Proc = yyF40CodeExport;
      }
    }
    if (yyMatch.A[41]) {
      cost = 1 + CostCodeExport(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeExport.Cost) {
        info->CodeExport.Cost = cost;
        info->CodeExport.Proc = yyF41CodeExport;
      }
    }
    if (yyMatch.A[43]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_9.Global.codes) + CostCodeGlobal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeGlobal.Cost) {
        info->CodeGlobal.Cost = cost;
        info->CodeGlobal.Proc = yyF43CodeGlobal;
      }
    }
    if (yyMatch.A[44]) {
      cost = 1 + CostCodeGlobal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeGlobal.Cost) {
        info->CodeGlobal.Cost = cost;
        info->CodeGlobal.Proc = yyF44CodeGlobal;
      }
    }
    if (yyMatch.A[46]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_10.Local.codes) + CostCodeLocal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeLocal.Cost) {
        info->CodeLocal.Cost = cost;
        info->CodeLocal.Proc = yyF46CodeLocal;
      }
    }
    if (yyMatch.A[47]) {
      cost = 1 + CostCodeLocal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeLocal.Cost) {
        info->CodeLocal.Cost = cost;
        info->CodeLocal.Proc = yyF47CodeLocal;
      }
    }
    if (yyMatch.A[49]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_11.Begin.codes) + CostCodeBegin(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeBegin.Cost) {
        info->CodeBegin.Cost = cost;
        info->CodeBegin.Proc = yyF49CodeBegin;
      }
    }
    if (yyMatch.A[50]) {
      cost = 1 + CostCodeBegin(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeBegin.Cost) {
        info->CodeBegin.Cost = cost;
        info->CodeBegin.Proc = yyF50CodeBegin;
      }
    }
    if (yyMatch.A[52]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_12.Close.codes) + CostCodeClose(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeClose.Cost) {
        info->CodeClose.Cost = cost;
        info->CodeClose.Proc = yyF52CodeClose;
      }
    }
    if (yyMatch.A[53]) {
      cost = 1 + CostCodeClose(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeClose.Cost) {
        info->CodeClose.Cost = cost;
        info->CodeClose.Proc = yyF53CodeClose;
      }
    }
    break;
  case Tree_Export:;
    state = 85;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_8.Export.codes)];
    break;
  case Tree_Global:;
    state = 87;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_9.Global.codes)];
    break;
  case Tree_Local:;
    state = 89;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_10.Local.codes)];
    break;
  case Tree_Begin:;
    state = 97;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_11.Begin.codes)];
    break;
  case Tree_Codes0:;
    state = 26;
    cost = 1;
    if (cost < info->CodeCodes.Cost) {
      info->CodeCodes.Cost = cost;
      info->CodeCodes.Proc = yyF56CodeCodes;
    }
    cost = 1;
    if (cost < info->CodeCodes2.Cost) {
      info->CodeCodes2.Cost = cost;
      info->CodeCodes2.Proc = yyF58CodeCodes2;
    }
    break;
  case Tree_Tokens0:;
    state = 32;
    break;
  case Tree_Tokens:;
    state = 99;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_20.Tokens.token)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_20.Tokens.tokens)];
    break;
  case Tree_Token:;
    state = 99;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_21.Token.id)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_21.Token.number)];
    break;
  case Tree_Id:;
    state = 32;
    break;
  case Tree_Number:;
    state = 32;
    break;
  case Tree_Rules0:;
    state = 3;
    cost = 1;
    if (cost < info->CodeForward.Cost) {
      info->CodeForward.Cost = cost;
      info->CodeForward.Proc = yyF5CodeForward;
    }
    cost = 1;
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF7CodeRules;
    }
    break;
  case Tree_Rules:;
    state = 34;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_29.Rules.rule)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_29.Rules.rules)];
    cost = 1 + CostCodeForward(yyt->U_1.V_29.Rules.rules);
    if (cost < info->CodeForward.Cost) {
      info->CodeForward.Cost = cost;
      info->CodeForward.Proc = yyF6CodeForward;
    }
    cost = 1 + CostCodeCodes(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.codes) + CostSetNumbers(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostCodeRules(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostCodeRules(yyt->U_1.V_29.Rules.rules);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF8CodeRules;
    }
    break;
  case Tree_Rule:;
    state = 35;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_30.Rule.id)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_30.Rule.codes)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_30.Rule.expr)];
    break;
  case Tree_Option:;
    state = 140;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_33.Option.expr)];
    cost = 1 + CostCodeRules(yyt->U_1.V_33.Option.expr);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF9CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_33.Option.expr);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF29SetNumbers;
    }
    break;
  case Tree_Times:;
    state = 168;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_34.Times.expr)];
    cost = 1 + CostCodeRules(yyt->U_1.V_34.Times.expr);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF10CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_34.Times.expr);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF30SetNumbers;
    }
    break;
  case Tree_Plus:;
    state = 181;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_35.Plus.expr)];
    cost = 1 + CostCodeRules(yyt->U_1.V_35.Plus.expr);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF11CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_35.Plus.expr);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF31SetNumbers;
    }
    break;
  case Tree_List:;
    state = 209;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_36.List.body)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_36.List.sep)];
    cost = 1 + CostCodeRules(yyt->U_1.V_36.List.body) + CostCodeRules(yyt->U_1.V_36.List.sep);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF12CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_36.List.body) + CostSetNumbers(yyt->U_1.V_36.List.sep);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF32SetNumbers;
    }
    break;
  case Tree_Action:;
    state = 135;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_37.Action.codes)];
    match = (yySetType *)ADR(yySets.A[state]);
    yyMatch.A[13] = IN(13, match->A[0]);
    if (yyMatch.A[13]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF13CodeRules;
      }
    }
    cost = 1 + CostCodeCodes(yyt->U_1.V_37.Action.codes);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF14CodeRules;
    }
    cost = 1;
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF33SetNumbers;
    }
    break;
  case Tree_Leaf:;
    state = 36;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_38.Leaf.id)];
    yyMatch.A[15] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && yyt->U_1.V_38.Leaf.sure && !yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[16] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && yyt->U_1.V_38.Leaf.sure && yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[17] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && !yyt->U_1.V_38.Leaf.sure && !yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[18] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && !yyt->U_1.V_38.Leaf.sure && yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[19] = TRUE && Types_IsNonterm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    yyMatch.A[38] = TRUE && yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring;
    yyMatch.A[39] = TRUE && !yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring;
    if (yyMatch.A[15]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF15CodeRules;
      }
    }
    if (yyMatch.A[16]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF16CodeRules;
      }
    }
    if (yyMatch.A[17]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF17CodeRules;
      }
    }
    if (yyMatch.A[18]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF18CodeRules;
      }
    }
    if (yyMatch.A[19]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF19CodeRules;
      }
    }
    if (yyMatch.A[38]) {
      cost = 1;
      if (cost < info->SetNumbers.Cost) {
        info->SetNumbers.Cost = cost;
        info->SetNumbers.Proc = yyF38SetNumbers;
      }
    }
    if (yyMatch.A[39]) {
      cost = 1;
      if (cost < info->SetNumbers.Cost) {
        info->SetNumbers.Cost = cost;
        info->SetNumbers.Proc = yyF39SetNumbers;
      }
    }
    break;
  case Tree_Alternative0:;
    state = 14;
    yyMatch.A[22] = TRUE && yyt->U_1.V_39.alternative.C_0_case;
    yyMatch.A[23] = TRUE && !yyt->U_1.V_39.alternative.C_0_case;
    cost = 1;
    if (cost < info->CodeAltCase.Cost) {
      info->CodeAltCase.Cost = cost;
      info->CodeAltCase.Proc = yyF24CodeAltCase;
    }
    cost = 1;
    if (cost < info->CodeAltIf.Cost) {
      info->CodeAltIf.Cost = cost;
      info->CodeAltIf.Proc = yyF26CodeAltIf;
    }
    cost = 1;
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF36SetNumbers;
    }
    do {
      success = FALSE;
      if (yyMatch.A[22]) {
        cost = 1 + CostCodeAltCase(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF22CodeRules;
          success = TRUE;
        }
      }
      if (yyMatch.A[23]) {
        cost = 1 + CostCodeAltIf(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF23CodeRules;
          success = TRUE;
        }
      }
    } while (!!success);
    break;
  case Tree_Alternative:;
    state = 250;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_41.Alternative.expr)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_41.Alternative.alternative)];
    match = (yySetType *)ADR(yySets.A[state]);
    yyMatch.A[22] = TRUE && yyt->U_1.V_39.alternative.C_0_case;
    yyMatch.A[23] = TRUE && !yyt->U_1.V_39.alternative.C_0_case;
    yyMatch.A[27] = IN(27, match->A[0]);
    cost = 1 + CostCodeRules(yyt->U_1.V_41.Alternative.expr) + CostCodeAltCase(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->CodeAltCase.Cost) {
      info->CodeAltCase.Cost = cost;
      info->CodeAltCase.Proc = yyF25CodeAltCase;
    }
    if (yyMatch.A[27]) {
      cost = 1 + CostCodeRules(yyt->U_1.V_41.Alternative.expr);
      if (cost < info->CodeAltIf.Cost) {
        info->CodeAltIf.Cost = cost;
        info->CodeAltIf.Proc = yyF27CodeAltIf;
      }
    }
    cost = 1 + CostCodeRules(yyt->U_1.V_41.Alternative.expr) + CostCodeAltIf(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->CodeAltIf.Cost) {
      info->CodeAltIf.Cost = cost;
      info->CodeAltIf.Proc = yyF28CodeAltIf;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_41.Alternative.expr) + CostSetNumbers(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF37SetNumbers;
    }
    do {
      success = FALSE;
      if (yyMatch.A[22]) {
        cost = 1 + CostCodeAltCase(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF22CodeRules;
          success = TRUE;
        }
      }
      if (yyMatch.A[23]) {
        cost = 1 + CostCodeAltIf(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF23CodeRules;
          success = TRUE;
        }
      }
    } while (!!success);
    break;
  case Tree_Sequence0:;
    state = 12;
    cost = 1;
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF20CodeRules;
    }
    cost = 1;
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF34SetNumbers;
    }
    break;
  case Tree_Sequence:;
    state = 264;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_44.Sequence.expr)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_44.Sequence.sequence)];
    cost = 1 + CostCodeRules(yyt->U_1.V_44.Sequence.expr) + CostCodeRules(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF21CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_44.Sequence.expr) + CostSetNumbers(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF35SetNumbers;
    }
    break;
  }
  return state;
}

static void yyErrorCheck
# ifdef __STDC__
(INTEGER i, CHAR s1[], LONGCARD O_3, CHAR s2[], LONGCARD O_2)
# else
(i, s1, O_3, s2, O_2)
INTEGER i;
CHAR s1[];
LONGCARD O_3;
CHAR s2[];
LONGCARD O_2;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(CHAR) + O_3 * sizeof(CHAR), 2)
  COPY_OPEN_ARRAY(s2, O_2, CHAR)
  COPY_OPEN_ARRAY(s1, O_3, CHAR)
  if (i < 0) {
    IO_WriteS((System_tFile)IO_StdError, s1, O_3);
    IO_WriteS((System_tFile)IO_StdError, s2, O_2);
    IO_WriteNl((System_tFile)IO_StdError);
    IO_CloseIO();
    exit(1);
  }
  FREE_OPEN_ARRAYS
}

void CodeC_BeginCodeC
# ifdef __STDC__
()
# else
()
# endif
{
  System_tFile yyf;
  INTEGER yyi;

  yyf = OpenInput(CodeC_CodeCTabName.A, 128L);
  yyErrorCheck(yyf, (STRING)"cannot open ", 12L, CodeC_CodeCTabName.A, 128L);
  yyi = Read(yyf, ADR(yySets), (LONGINT)sizeof(yySetsType));
  yyErrorCheck(yyi, (STRING)"cannot read ", 12L, CodeC_CodeCTabName.A, 128L);
  yyi = Read(yyf, ADR(yyComb), (LONGINT)sizeof(yyCombType));
  yyErrorCheck(yyi, (STRING)"cannot read ", 12L, CodeC_CodeCTabName.A, 128L);
  Close(yyf);
  vExport = FALSE;
  SpaCo = 0;
  Label = 0;
  Hex.A[0] = '0';
  Hex.A[1] = '1';
  Hex.A[2] = '2';
  Hex.A[3] = '3';
  Hex.A[4] = '4';
  Hex.A[5] = '5';
  Hex.A[6] = '6';
  Hex.A[7] = '7';
  Hex.A[8] = '8';
  Hex.A[9] = '9';
  Hex.A[10] = 'A';
  Hex.A[11] = 'B';
  Hex.A[12] = 'C';
  Hex.A[13] = 'D';
  Hex.A[14] = 'E';
  Hex.A[15] = 'F';
}

void CodeC_DoCodeC
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyStateType yystate;

  yystate = yyTraverse(yyt);
  CODE(yyt);
  yyReleaseHeap();
}

void CodeC_CloseCodeC
# ifdef __STDC__
()
# else
()
# endif
{
}

void CodeC__init()
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
    Checks__init();
    Codes__init();
    DynArray__init();
    Errors__init();
    IO__init();
    Idents__init();
    Sets__init();
    StringMem__init();
    System__init();
    Scanner__init();
    Types__init();
    Strings__init();
    Tree__init();
    Idents__init();

    (void)strncpy((char *)CodeC_CodeCTabName.A, "CodeC.tab", sizeof(CodeC_CodeCTabName.A));
    {
      register yyInfoType *W_1 = &yyInfo;

      W_1->CODE.Cost = yyInfinite;
      W_1->CODE.Proc = yyECODE;
      W_1->CodeDef.Cost = yyInfinite;
      W_1->CodeDef.Proc = yyECodeDef;
      W_1->CodeImp.Cost = yyInfinite;
      W_1->CodeImp.Proc = yyECodeImp;
      W_1->CodeForward.Cost = yyInfinite;
      W_1->CodeForward.Proc = yyECodeForward;
      W_1->CodeRules.Cost = yyInfinite;
      W_1->CodeRules.Proc = yyECodeRules;
      W_1->CodeAltCase.Cost = yyInfinite;
      W_1->CodeAltCase.Proc = yyECodeAltCase;
      W_1->CodeAltIf.Cost = yyInfinite;
      W_1->CodeAltIf.Proc = yyECodeAltIf;
      W_1->SetNumbers.Cost = yyInfinite;
      W_1->SetNumbers.Proc = yyESetNumbers;
      W_1->CodeExport.Cost = yyInfinite;
      W_1->CodeExport.Proc = yyECodeExport;
      W_1->CodeGlobal.Cost = yyInfinite;
      W_1->CodeGlobal.Proc = yyECodeGlobal;
      W_1->CodeLocal.Cost = yyInfinite;
      W_1->CodeLocal.Proc = yyECodeLocal;
      W_1->CodeBegin.Cost = yyInfinite;
      W_1->CodeBegin.Proc = yyECodeBegin;
      W_1->CodeClose.Cost = yyInfinite;
      W_1->CodeClose.Proc = yyECodeClose;
      W_1->CodeCodes.Cost = yyInfinite;
      W_1->CodeCodes.Proc = yyECodeCodes;
      W_1->CodeCodes2.Cost = yyInfinite;
      W_1->CodeCodes2.Proc = yyECodeCodes2;
    }
    yyBlockList = NIL;
    yyPoolFreePtr = (ADDRESS)NIL;
    yyPoolEndPtr = (ADDRESS)NIL;
  }
}
