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

#ifndef DEFINITION_CodeM2
#include "CodeM2.h"
#endif

struct CodeM2_1 CodeM2_CodeM2TabName;

#define cBitsPerBitset   32
static CHAR cDefinition [] = ".md";
static CHAR cImplementation [] = ".mi";
static CHAR cTable [] = ".Tab";
static IO_tFile file;
static INTEGER SpaCo;
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
static void WriteParsTab ARGS(());
struct S_27 {
    Sets_tSet A[cBitsPerBitset - 1 + 1];
};
#define yyInfinite   715827882
#define yyBitsPerBitset   32
#define yySetSize   56
#define yyMaxIndex   32
#define yyCombSize   303
#define yyStartState   0
#define yyPoolSize   10240
typedef struct S_1 *yytBlockPtr;
typedef struct S_1 {
    yytBlockPtr Successor;
    struct S_10 {
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
typedef void (*yyPCodeRules) ARGS((Tree_tTree));
typedef void (*yyPCodeAltCase) ARGS((Tree_tTree));
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
    struct S_11 {
        INTEGER Cost;
        yyPCODE Proc;
    } CODE;
    struct S_12 {
        INTEGER Cost;
        yyPCodeDef Proc;
    } CodeDef;
    struct S_13 {
        INTEGER Cost;
        yyPCodeImp Proc;
    } CodeImp;
    struct S_14 {
        INTEGER Cost;
        yyPCodeRules Proc;
    } CodeRules;
    struct S_15 {
        INTEGER Cost;
        yyPCodeAltCase Proc;
    } CodeAltCase;
    struct S_16 {
        INTEGER Cost;
        yyPCodeAltIf Proc;
    } CodeAltIf;
    struct S_17 {
        INTEGER Cost;
        yyPSetNumbers Proc;
    } SetNumbers;
    struct S_18 {
        INTEGER Cost;
        yyPCodeExport Proc;
    } CodeExport;
    struct S_19 {
        INTEGER Cost;
        yyPCodeGlobal Proc;
    } CodeGlobal;
    struct S_20 {
        INTEGER Cost;
        yyPCodeLocal Proc;
    } CodeLocal;
    struct S_21 {
        INTEGER Cost;
        yyPCodeBegin Proc;
    } CodeBegin;
    struct S_22 {
        INTEGER Cost;
        yyPCodeClose Proc;
    } CodeClose;
    struct S_23 {
        INTEGER Cost;
        yyPCodeCodes Proc;
    } CodeCodes;
    struct S_24 {
        INTEGER Cost;
        yyPCodeCodes2 Proc;
    } CodeCodes2;
} yyInfoType;
static yySetsType yySets;
static yyCombType yyComb;
static yyInfoType yyInfo;
static struct S_25 {
    BOOLEAN A[56 + 1];
} yyMatch;
static yytBlockPtr yyBlockList;
static ADDRESS yyPoolFreePtr, yyPoolEndPtr;
static ADDRESS yyAlloc ARGS(());
static void yyReleaseHeap ARGS(());
static void CODE ARGS((Tree_tTree yyt));
static void CodeDef ARGS((Tree_tTree yyt));
static void CodeImp ARGS((Tree_tTree yyt));
static void CodeRules ARGS((Tree_tTree yyt));
static void CodeAltCase ARGS((Tree_tTree yyt));
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
static void yyECodeRules ARGS((Tree_tTree yyt));
static void yyECodeAltCase ARGS((Tree_tTree yyt));
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
static void yyF5CodeRules ARGS((Tree_tTree yyt));
static void yyF6CodeRules ARGS((Tree_tTree yyt));
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
static void yyF22CodeAltCase ARGS((Tree_tTree yyt));
static void yyF23CodeAltCase ARGS((Tree_tTree yyt));
static void yyF24CodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void yyF25CodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void yyF26CodeAltIf ARGS((Tree_tTree yyt, BOOLEAN started));
static void yyF27SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF28SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF29SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF30SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF31SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF32SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF33SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF34SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF35SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF36SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF37SetNumbers ARGS((Tree_tTree yyt, BOOLEAN start));
static void yyF38CodeExport ARGS((Tree_tTree yyt));
static void yyF39CodeExport ARGS((Tree_tTree yyt));
static void yyF40CodeExport ARGS((Tree_tTree yyt));
static void yyF41CodeGlobal ARGS((Tree_tTree yyt));
static void yyF42CodeGlobal ARGS((Tree_tTree yyt));
static void yyF43CodeGlobal ARGS((Tree_tTree yyt));
static void yyF44CodeLocal ARGS((Tree_tTree yyt));
static void yyF45CodeLocal ARGS((Tree_tTree yyt));
static void yyF46CodeLocal ARGS((Tree_tTree yyt));
static void yyF47CodeBegin ARGS((Tree_tTree yyt));
static void yyF48CodeBegin ARGS((Tree_tTree yyt));
static void yyF49CodeBegin ARGS((Tree_tTree yyt));
static void yyF50CodeClose ARGS((Tree_tTree yyt));
static void yyF51CodeClose ARGS((Tree_tTree yyt));
static void yyF52CodeClose ARGS((Tree_tTree yyt));
static void yyF53CodeCodes ARGS((Tree_tTree yyt));
static void yyF54CodeCodes ARGS((Tree_tTree yyt));
static void yyF55CodeCodes2 ARGS((Tree_tTree yyt));
static void yyF56CodeCodes2 ARGS((Tree_tTree yyt));
static INTEGER CostCODE ARGS((Tree_tTree yyt));
static INTEGER CostCodeDef ARGS((Tree_tTree yyt));
static INTEGER CostCodeImp ARGS((Tree_tTree yyt));
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
  } else {
    IO_WriteS(file, (STRING)"Scanner", 7L);
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

  if (index == Codes_cNoIndex) {
    Sets_MakeSet(&todo, (Sets_tElement)Idents_MaxIdent());
    Sets_Assign(&todo, set);
    Sets_Exclude(&todo, (Sets_tElement)Scanner_Epsilon);
    if (!Sets_IsEmpty(todo)) {
      for (;;) {
        id = Sets_Extract(&todo);
        IO_WriteS(file, (STRING)"(xxToken = ", 11L);
        IO_WriteI(file, Codes_Code(id), 0L);
        IO_WriteS(file, (STRING)" (* ", 4L);
        Idents_WriteIdent(file, id);
        IO_WriteS(file, (STRING)" *))", 4L);
        if (Sets_IsEmpty(todo)) {
          goto EXIT_1;
        }
        IO_WriteS(file, (STRING)" OR ", 4L);
      } EXIT_1:;
    }
    Sets_ReleaseSet(&todo);
  } else {
    IO_WriteS(file, (STRING)"(", 1L);
    IO_WriteI(file, index % cBitsPerBitset, 0L);
    IO_WriteS(file, (STRING)" IN xxVerticalSet", 17L);
    IO_WriteI(file, index / cBitsPerBitset, 0L);
    IO_WriteS(file, (STRING)" [xxToken] (* ", 14L);
    Codes_WriteIndex(file, index);
    IO_WriteS(file, (STRING)" *))", 4L);
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
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet); (* ", 27L);
    Codes_WriteRecIndex(file, recover);
    IO_WriteS(file, (STRING)" *)", 3L);
    IO_WriteNl(file);
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"xxExpected (", 12L);
    IO_WriteI(file, expect, 0L);
    IO_WriteS(file, (STRING)", ", 2L);
    IO_WriteI(file, recover, 0L);
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet); (* ", 27L);
    Codes_WriteRecIndex(file, expect);
    IO_WriteS(file, (STRING)" / ", 3L);
    Codes_WriteRecIndex(file, recover);
    IO_WriteS(file, (STRING)" *)", 3L);
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
  Spaces();
  IO_WriteS(file, (STRING)"| ", 2L);
  if (!Sets_IsEmpty(todo)) {
    for (;;) {
      id = Sets_Extract(&todo);
      IO_WriteI(file, Codes_Code(id), 0L);
      IO_WriteS(file, (STRING)" (* ", 4L);
      Idents_WriteIdent(file, id);
      IO_WriteS(file, (STRING)" *)", 3L);
      if (Sets_IsEmpty(todo)) {
        goto EXIT_2;
      }
      IO_WriteS(file, (STRING)", ", 2L);
    } EXIT_2:;
  }
  IO_WriteS(file, (STRING)":", 1L);
  IO_WriteNl(file);
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
          Spaces();
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
          IO_WriteS(file, (STRING)": ", 2L);
          if (Types_IsTerm(id)) {
            Prefix();
            IO_WriteS(file, (STRING)".tScanAttribute", 15L);
          } else {
            IO_WriteS(file, (STRING)"tParsAttribute", 14L);
          }
          IO_WriteS(file, (STRING)";", 1L);
          IO_WriteNl(file);
        }
        if (id >= B_6) break;
      }
  }
}

static void WriteParsTab
# ifdef __STDC__
()
# else
()
# endif
{
  BITSET bitset;
  Sets_tSet set;
  struct S_27 sets;
  INTEGER size;
  INTEGER code, i, bit;
  INTEGER index;

  Idents_GetString(Tree_ParserName, &PathS);
  Strings_ArrayToString(cTable, 4L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = OpenOutput(PathA.A, 129L);
  Checks_CheckOpenOutput(&file, PathA.A, 129L);
  Sets_MakeSet(&set, (Sets_tElement)Codes_MaxCode());
  {
    LONGINT B_9 = 0, B_10 = Codes_vMaxRecSetIndex;

    if (B_9 <= B_10)
      for (index = B_9;; index += 1) {
        Codes_GetRecSet(index, &set);
        {
          LONGINT B_11 = 0, B_12 = Codes_MaxCode() / cBitsPerBitset - 1;

          if (B_11 <= B_12)
            for (i = B_11;; i += 1) {
              bitset = 0X0L;
              for (bit = 0; bit <= cBitsPerBitset - 1; bit += 1) {
                if (Sets_IsElement((Sets_tElement)(i * cBitsPerBitset + bit), &set)) {
                  INCL(bitset, bit);
                }
              }
              size = Write(file, ADR(bitset), (LONGINT)sizeof(BITSET));
              if (i >= B_12) break;
            }
        }
        i = Codes_MaxCode() / cBitsPerBitset;
        bitset = 0X0L;
        {
          LONGINT B_13 = 0, B_14 = Codes_MaxCode() % cBitsPerBitset;

          if (B_13 <= B_14)
            for (bit = B_13;; bit += 1) {
              if (Sets_IsElement((Sets_tElement)(i * cBitsPerBitset + bit), &set)) {
                INCL(bitset, bit);
              }
              if (bit >= B_14) break;
            }
        }
        size = Write(file, ADR(bitset), (LONGINT)sizeof(BITSET));
        if (index >= B_10) break;
      }
  }
  Sets_ReleaseSet(&set);
  for (bit = 0; bit <= cBitsPerBitset - 1; bit += 1) {
    Sets_MakeSet(&sets.A[bit], (Sets_tElement)Codes_MaxCode());
  }
  {
    LONGINT B_15 = 0, B_16 = Codes_vMaxSetIndex / cBitsPerBitset;

    if (B_15 <= B_16)
      for (i = B_15;; i += 1) {
        for (bit = 0; bit <= cBitsPerBitset - 1; bit += 1) {
          index = i * cBitsPerBitset + bit;
          if (index <= Codes_vMaxSetIndex) {
            Codes_GetSet(index, &sets.A[bit]);
          }
        }
        {
          LONGINT B_17 = 0, B_18 = Codes_MaxCode();

          if (B_17 <= B_18)
            for (code = B_17;; code += 1) {
              bitset = 0X0L;
              for (bit = 0; bit <= cBitsPerBitset - 1; bit += 1) {
                if (Sets_IsElement((Sets_tElement)code, &sets.A[bit])) {
                  INCL(bitset, bit);
                }
              }
              size = Write(file, ADR(bitset), (LONGINT)sizeof(BITSET));
              if (code >= B_18) break;
            }
        }
        if (i >= B_16) break;
      }
  }
  for (bit = 0; bit <= cBitsPerBitset - 1; bit += 1) {
    Sets_ReleaseSet(&sets.A[bit]);
  }
  Close(file);
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
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  yyInfoPtr InfoPtr;

  InfoPtr = (yyInfoPtr)yyt->U_1.V_2.yyHead.yyEstraInfo;
  (*InfoPtr->CodeAltCase.Proc)(yyt);
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
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
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
    WriteParsTab();
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
  Strings_ArrayToString(cDefinition, 3L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  Spaces();
  IO_WriteS(file, (STRING)"DEFINITION MODULE ", 18L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  CodeExport(yyt->U_1.V_3.Grammar.sections);
  if (!vExport) {
    Spaces();
    IO_WriteS(file, (STRING)"IMPORT ", 7L);
    Prefix();
    IO_WriteS(file, (STRING)";", 1L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"TYPE tParsAttribute = ", 22L);
    Prefix();
    IO_WriteS(file, (STRING)".tScanAttribute;", 16L);
    IO_WriteNl(file);
  }
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"VAR", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  ParsAttribute	: tParsAttribute;", 33L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  ParsTabName	: ARRAY [0..128] OF CHAR;", 39L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE ", 10L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" (): INTEGER;", 13L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE Close", 15L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" ();", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxTokenName (Token: CARDINAL; VAR Name: ARRAY OF CHAR);", 65L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"END ", 4L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)".", 1L);
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
  Sets_tSet set;
  Idents_tIdent id;
  Strings_tString s;

  Idents_GetString(Tree_ParserName, &PathS);
  Strings_ArrayToString(cImplementation, 3L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 129L);
  file = IO_WriteOpen(PathA.A, 129L);
  Checks_CheckWriteOpen(&file, PathA.A, 129L);
  Spaces();
  IO_WriteS(file, (STRING)"IMPLEMENTATION MODULE ", 22L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"IMPORT Positions, Errors, ", 26L);
  Prefix();
  IO_WriteS(file, (STRING)", Strings, System, SYSTEM;", 26L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  CodeGlobal(yyt->U_1.V_3.Grammar.sections);
  lSections = yyt->U_1.V_3.Grammar.sections;
  Spaces();
  IO_WriteS(file, (STRING)"CONST xxEof = 0;", 16L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"TYPE", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxtUnionPtr	= POINTER TO xxtUnion;", 36L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxtUnion	= RECORD GlobalRecoverySet: xxtUnionPtr; LocalRecoverySet: SHORTCARD; END;", 85L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxtSet	= ARRAY [0..", 21L);
  IO_WriteI(file, Codes_MaxCode() / cBitsPerBitset, 0L);
  IO_WriteS(file, (STRING)"] OF BITSET;", 12L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"VAR", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxToken		: SHORTCARD;", 23L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxErrorCount		: INTEGER;", 26L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxIsInitialized	: BOOLEAN;", 28L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxIsRepairMode	: BOOLEAN;", 27L);
  IO_WriteNl(file);
  if (Codes_vMaxRecSetIndex == Codes_cNoIndex) {
    Spaces();
    IO_WriteS(file, (STRING)"  xxHorizontalSet	: ARRAY [0..0] OF xxtSet;", 43L);
    IO_WriteNl(file);
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"  xxHorizontalSet	: ARRAY [0..", 30L);
    IO_WriteI(file, Codes_vMaxRecSetIndex, 0L);
    IO_WriteS(file, (STRING)"] OF xxtSet;", 12L);
    IO_WriteNl(file);
  }
  {
    LONGINT B_19 = 0, B_20 = Codes_vMaxSetIndex / cBitsPerBitset;

    if (B_19 <= B_20)
      for (i = B_19;; i += 1) {
        Spaces();
        IO_WriteS(file, (STRING)"  xxVerticalSet", 15L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"	: ARRAY [0..", 13L);
        IO_WriteI(file, Codes_MaxCode(), 0L);
        IO_WriteS(file, (STRING)"] OF BITSET;", 12L);
        IO_WriteNl(file);
        if (i >= B_20) break;
      }
  }
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxTokenName (Token: CARDINAL; VAR Name: ARRAY OF CHAR);", 65L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  PROCEDURE Copy (Source: ARRAY OF CHAR; VAR Target: ARRAY OF CHAR);", 68L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    VAR i, j: CARDINAL;", 23L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    BEGIN", 9L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      IF HIGH (Source) < HIGH (Target)", 38L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      THEN j := HIGH (Source); ELSE j := HIGH (Target); END;", 60L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      FOR i := 0 TO j DO Target [i] := Source [i]; END;", 55L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      IF HIGH (Target) > j THEN Target [j + 1] := CHR (0); END;", 63L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END Copy;", 13L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    CASE Token OF", 17L);
  IO_WriteNl(file);
  Sets_MakeSet(&set, (Sets_tElement)Idents_MaxIdent());
  Types_Terminals(&set);
  Sets_Exclude(&set, (Sets_tElement)Scanner_Epsilon);
  while (!Sets_IsEmpty(set)) {
    id = Sets_Extract(&set);
    Idents_GetString(id, &s);
    if (Strings_Char(&s, 1) == '\'') {
      Spaces();
      IO_WriteS(file, (STRING)"    | ", 6L);
      IO_WriteI(file, Codes_Code(id), 0L);
      IO_WriteS(file, (STRING)": Copy (", 8L);
      Idents_WriteIdent(file, id);
      IO_WriteS(file, (STRING)", Name);", 8L);
      IO_WriteNl(file);
    } else if (Strings_Char(&s, 1) == '"') {
      Spaces();
      IO_WriteS(file, (STRING)"    | ", 6L);
      IO_WriteI(file, Codes_Code(id), 0L);
      IO_WriteS(file, (STRING)": Copy (", 8L);
      Idents_WriteIdent(file, id);
      IO_WriteS(file, (STRING)", Name);", 8L);
      IO_WriteNl(file);
    } else {
      Spaces();
      IO_WriteS(file, (STRING)"    | ", 6L);
      IO_WriteI(file, Codes_Code(id), 0L);
      IO_WriteS(file, (STRING)": Copy ('", 9L);
      Idents_WriteIdent(file, id);
      IO_WriteS(file, (STRING)"', Name);", 9L);
      IO_WriteNl(file);
    }
  }
  Sets_ReleaseSet(&set);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END xxTokenName;", 18L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE ", 10L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)" (): INTEGER;", 13L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"BEGIN", 5L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"xxErrorCount := 0;", 18L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"Begin", 5L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"xxToken := ", 11L);
  Prefix();
  IO_WriteS(file, (STRING)".GetToken (); xxIsRepairMode := FALSE;", 38L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"yy", 2L);
  Idents_WriteIdent(file, yyt->U_1.V_3.Grammar.rules->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" (ParsAttribute, NIL);", 22L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"IF xxToken # xxEof THEN xxRecoveryLiteral (xxEof, ", 50L);
  IO_WriteI(file, Codes_EmptyRecSetIndex, 0L);
  IO_WriteS(file, (STRING)", NIL); END;", 12L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"RETURN xxErrorCount;", 20L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END ", 4L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxIsElement (VAR Set: xxtSet; Element: SHORTCARD): BOOLEAN;", 69L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    RETURN Element MOD ", 23L);
  IO_WriteI(file, (LONGINT)cBitsPerBitset, 0L);
  IO_WriteS(file, (STRING)" IN Set [Element DIV ", 21L);
  IO_WriteI(file, (LONGINT)cBitsPerBitset, 0L);
  IO_WriteS(file, (STRING)"];", 2L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END xxIsElement;", 18L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxUnexpected (LocalRecoverySet: SHORTCARD; GlobalRecoverySet: xxtUnionPtr);", 85L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF NOT xxIsRepairMode THEN", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      INC (xxErrorCount);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.SyntaxError, Errors.Error, ", 61L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position);", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxSkipTokens (LocalRecoverySet, GlobalRecoverySet);", 57L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END xxUnexpected;", 19L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxExpected (ExpectedSet: SHORTCARD; LocalRecoverySet: SHORTCARD; GlobalRecoverySet: xxtUnionPtr);", 107L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  VAR", 5L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    Token		: SHORTCARD;", 23L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    TokenArray		: ARRAY [0..127] OF CHAR;", 41L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    TokenString		: Strings.tString;", 35L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ContinueString	: Strings.tString;", 37L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF NOT xxIsRepairMode THEN", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      INC (xxErrorCount);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.SyntaxError, Errors.Error, ", 61L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position);", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Strings.AssignEmpty (ContinueString);", 43L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      FOR Token := 0 TO ", 24L);
  IO_WriteI(file, Codes_MaxCode(), 0L);
  IO_WriteS(file, (STRING)" DO", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"        IF xxIsElement (xxHorizontalSet [ExpectedSet], Token) THEN", 66L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	  xxTokenName (Token, TokenArray);", 35L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	  Strings.ArrayToString (TokenArray, TokenString);", 51L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	  IF (Strings.Length (ContinueString) + Strings.Length (TokenString) + 1 <= Strings.cMaxStrLength) THEN", 104L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	    Strings.Concatenate (ContinueString, TokenString);", 55L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	    Strings.Append (ContinueString, ' ');", 42L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"	  END;", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"        END;", 12L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      END;", 10L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessageI (Errors.ExpectedTokens, Errors.Information, ", 71L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position, Errors.String, SYSTEM.ADR (ContinueString));", 65L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxSkipTokens (LocalRecoverySet, GlobalRecoverySet);", 57L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END xxExpected;", 17L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxRecoveryLiteral (Expected: SHORTCARD; LocalRecoverySet: SHORTCARD; GlobalRecoverySet: xxtUnionPtr);", 111L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  VAR TokenString: ARRAY [0..127] OF CHAR;", 42L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF NOT xxIsRepairMode THEN", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      INC (xxErrorCount);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.SyntaxError, Errors.Error, ", 61L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position);", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxTokenName (Expected, TokenString);", 42L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessageI (Errors.ExpectedTokens, Errors.Information, ", 71L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position, Errors.Array, SYSTEM.ADR (TokenString));", 61L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxSkipTokens (LocalRecoverySet, GlobalRecoverySet);", 57L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF xxToken # Expected THEN", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxTokenName (Expected, TokenString);", 42L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessageI (Errors.TokenInserted, Errors.Repair, ", 65L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position, Errors.Array, SYSTEM.ADR (TokenString));", 61L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ELSE", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      IF xxToken # xxEof THEN xxToken := ", 41L);
  Prefix();
  IO_WriteS(file, (STRING)".GetToken (); END;", 18L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxIsRepairMode := FALSE;", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END xxRecoveryLiteral;", 24L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxRecoveryTerminal (Expected: SHORTCARD; LocalRecoverySet: SHORTCARD; GlobalRecoverySet: xxtUnionPtr; VAR RepairAttribute: ", 133L);
  Prefix();
  IO_WriteS(file, (STRING)".tScanAttribute);", 17L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  VAR TokenString: ARRAY [0..127] OF CHAR;", 42L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF NOT xxIsRepairMode THEN", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      INC (xxErrorCount);", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.SyntaxError, Errors.Error, ", 61L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position);", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxTokenName (Expected, TokenString);", 42L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessageI (Errors.ExpectedTokens, Errors.Information, ", 71L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position, Errors.Array, SYSTEM.ADR (TokenString));", 61L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxSkipTokens (LocalRecoverySet, GlobalRecoverySet);", 57L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF xxToken # Expected THEN", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxTokenName (Expected, TokenString);", 42L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessageI (Errors.TokenInserted, Errors.Repair, ", 65L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position, Errors.Array, SYSTEM.ADR (TokenString));", 61L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      ", 6L);
  Prefix();
  IO_WriteS(file, (STRING)".ErrorAttribute (Expected, RepairAttribute);", 44L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    ELSE", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      RepairAttribute := ", 25L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute;", 11L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      IF xxToken # xxEof THEN xxToken := ", 41L);
  Prefix();
  IO_WriteS(file, (STRING)".GetToken (); END;", 18L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxIsRepairMode := FALSE;", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END xxRecoveryTerminal;", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE xxSkipTokens (LocalRecoverySet: SHORTCARD; GlobalRecoverySet: xxtUnionPtr);", 85L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  VAR RecoverySet: xxtSet;", 26L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      TokensSkipped: BOOLEAN;", 29L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    RecoverySet := xxHorizontalSet [LocalRecoverySet];", 54L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    INCL (RecoverySet [0], xxEof);", 34L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    WHILE GlobalRecoverySet # NIL DO", 36L);
  IO_WriteNl(file);
  {
    LONGINT B_21 = 0, B_22 = Codes_MaxCode() / cBitsPerBitset;

    if (B_21 <= B_22)
      for (i = B_21;; i += 1) {
        Spaces();
        IO_WriteS(file, (STRING)"      RecoverySet [", 19L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"] := RecoverySet [", 18L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"] + xxHorizontalSet [GlobalRecoverySet^.LocalRecoverySet] [", 59L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"];", 2L);
        IO_WriteNl(file);
        if (i >= B_22) break;
      }
  }
  Spaces();
  IO_WriteS(file, (STRING)"      GlobalRecoverySet := GlobalRecoverySet^.GlobalRecoverySet;", 64L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    TokensSkipped := FALSE;", 27L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    WHILE NOT xxIsElement (RecoverySet, xxToken) DO", 51L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      xxToken := ", 17L);
  Prefix();
  IO_WriteS(file, (STRING)".GetToken ();", 13L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      TokensSkipped := TRUE;", 28L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF TokensSkipped THEN", 25L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.RestartPoint, Errors.Information, ", 68L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute.Position);", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxIsRepairMode := TRUE;", 27L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END xxSkipTokens;", 19L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE Begin", 15L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  VAR", 5L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxTableFile: System.tFile;", 30L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxSize: CARDINAL;", 21L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF xxIsInitialized THEN RETURN; END;", 40L);
  IO_WriteNl(file);
  CodeBegin(yyt->U_1.V_3.Grammar.sections);
  Spaces();
  IO_WriteS(file, (STRING)"    xxTableFile := System.OpenInput (ParsTabName);", 50L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    IF xxTableFile < 0 THEN", 27L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.ReadParseTable, Errors.Fatal, Positions.NoPosition);", 86L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    END;", 8L);
  IO_WriteNl(file);
  if (Codes_vMaxRecSetIndex != Codes_cNoIndex) {
    Spaces();
    IO_WriteS(file, (STRING)"    xxSize := System.Read (xxTableFile, SYSTEM.ADR (xxHorizontalSet), SIZE (xxHorizontalSet));", 94L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"    IF xxSize # SIZE (xxHorizontalSet) THEN", 43L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.ReadParseTable, Errors.Fatal, Positions.NoPosition);", 86L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"    END;", 8L);
    IO_WriteNl(file);
  }
  {
    LONGINT B_23 = 0, B_24 = Codes_vMaxSetIndex / cBitsPerBitset;

    if (B_23 <= B_24)
      for (i = B_23;; i += 1) {
        Spaces();
        IO_WriteS(file, (STRING)"    xxSize := System.Read (xxTableFile, SYSTEM.ADR (xxVerticalSet", 65L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"), SIZE (xxVerticalSet", 22L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)"));", 3L);
        IO_WriteNl(file);
        Spaces();
        IO_WriteS(file, (STRING)"    IF xxSize # SIZE (xxVerticalSet", 35L);
        IO_WriteI(file, i, 0L);
        IO_WriteS(file, (STRING)") THEN", 6L);
        IO_WriteNl(file);
        Spaces();
        IO_WriteS(file, (STRING)"      Errors.ErrorMessage (Errors.ReadParseTable, Errors.Fatal, Positions.NoPosition);", 86L);
        IO_WriteNl(file);
        Spaces();
        IO_WriteS(file, (STRING)"    END;", 8L);
        IO_WriteNl(file);
        if (i >= B_24) break;
      }
  }
  Spaces();
  IO_WriteS(file, (STRING)"    System.Close (xxTableFile);", 31L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"    xxIsInitialized := TRUE;", 28L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  END Begin", 11L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"PROCEDURE Close", 15L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  BEGIN", 7L);
  IO_WriteNl(file);
  CodeClose(yyt->U_1.V_3.Grammar.sections);
  Spaces();
  IO_WriteS(file, (STRING)"  END Close", 11L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)";", 1L);
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
  Spaces();
  IO_WriteS(file, (STRING)"BEGIN", 5L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxIsInitialized := FALSE;", 27L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  ParsTabName := '", 18L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, cTable, 4L);
  IO_WriteS(file, (STRING)"';", 2L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"END ", 4L);
  Idents_WriteIdent(file, Tree_ParserName);
  IO_WriteS(file, (STRING)".", 1L);
  IO_WriteNl(file);
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

static void yyF5CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF6CodeRules
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
  IO_WriteS(file, (STRING)"PROCEDURE yy", 12L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" (VAR ", 6L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)"0: tParsAttribute; xxGlobalRecoverySet: xxtUnionPtr);", 53L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"VAR", 3L);
  IO_WriteNl(file);
  INC(SpaCo);
  WriteAttributes();
  if (yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.iscalling) {
    Spaces();
    IO_WriteS(file, (STRING)"xxUnion: xxtUnion;", 18L);
    IO_WriteNl(file);
  }
  CodeLocal(lSections);
  CodeCodes(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.codes);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"BEGIN", 5L);
  IO_WriteNl(file);
  INC(SpaCo);
  if (yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.iscalling) {
    Spaces();
    IO_WriteS(file, (STRING)"xxUnion.GlobalRecoverySet := xxGlobalRecoverySet;", 49L);
    IO_WriteNl(file);
  }
  CodeRules(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END yy", 6L);
  Idents_WriteIdent(file, yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)";", 1L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteNl(file);
  CodeRules(yyt->U_1.V_29.Rules.rules);
}

static void yyF7CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"LOOP", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"IF ", 3L);
  CodeIsElement(yyt->U_1.V_33.Option.index, yyt->U_1.V_33.Option.first);
  IO_WriteS(file, (STRING)" THEN", 5L);
  IO_WriteNl(file);
  INC(SpaCo);
  InDefault = FALSE;
  CodeRules(yyt->U_1.V_33.Option.expr);
  Spaces();
  IO_WriteS(file, (STRING)"EXIT;", 5L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"ELSIF ", 6L);
  CodeIsElement(yyt->U_1.V_33.Option.followindex, yyt->U_1.V_33.Option.follow);
  IO_WriteS(file, (STRING)" OR xxIsRepairMode THEN EXIT; END;", 34L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_33.Option.recindex, yyt->U_1.V_33.Option.expindex);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
}

static void yyF8CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"LOOP", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"IF ", 3L);
  CodeIsElement(yyt->U_1.V_34.Times.index, yyt->U_1.V_34.Times.first);
  IO_WriteS(file, (STRING)" THEN", 5L);
  IO_WriteNl(file);
  INC(SpaCo);
  InDefault = FALSE;
  CodeRules(yyt->U_1.V_34.Times.expr);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"ELSIF ", 6L);
  CodeIsElement(yyt->U_1.V_34.Times.followindex, yyt->U_1.V_34.Times.follow);
  IO_WriteS(file, (STRING)" OR xxIsRepairMode THEN EXIT;", 29L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"ELSE", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)" ", 1L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_34.Times.recindex, yyt->U_1.V_34.Times.expindex);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
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
  IO_WriteS(file, (STRING)"LOOP", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_35.Plus.expr);
  Spaces();
  IO_WriteS(file, (STRING)"IF NOT (", 8L);
  CodeIsElement(yyt->U_1.V_35.Plus.index, yyt->U_1.V_35.Plus.first);
  IO_WriteS(file, (STRING)") THEN", 6L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"IF ", 3L);
  CodeIsElement(yyt->U_1.V_35.Plus.followindex, yyt->U_1.V_35.Plus.follow);
  IO_WriteS(file, (STRING)" THEN EXIT; END;", 16L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_35.Plus.recindex, yyt->U_1.V_35.Plus.expindex);
  Spaces();
  IO_WriteS(file, (STRING)"IF NOT (", 8L);
  CodeIsElement(yyt->U_1.V_35.Plus.index, yyt->U_1.V_35.Plus.first);
  IO_WriteS(file, (STRING)") THEN EXIT; END;", 17L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
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
  IO_WriteS(file, (STRING)"LOOP", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_36.List.body);
  Spaces();
  IO_WriteS(file, (STRING)"IF NOT (", 8L);
  CodeIsElement(yyt->U_1.V_36.List.sep->U_1.V_32.expr.index, yyt->U_1.V_36.List.sep->U_1.V_32.expr.first);
  IO_WriteS(file, (STRING)") THEN", 6L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"IF ", 3L);
  CodeIsElement(yyt->U_1.V_36.List.followindex, yyt->U_1.V_36.List.follow);
  IO_WriteS(file, (STRING)" THEN EXIT; END;", 16L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_36.List.recindex, yyt->U_1.V_36.List.expindex);
  Spaces();
  IO_WriteS(file, (STRING)"IF NOT (", 8L);
  CodeIsElement(yyt->U_1.V_36.List.sep->U_1.V_32.expr.index, yyt->U_1.V_36.List.sep->U_1.V_32.expr.first);
  IO_WriteS(file, (STRING)" OR ", 4L);
  CodeIsElement(yyt->U_1.V_36.List.index, yyt->U_1.V_36.List.first);
  IO_WriteS(file, (STRING)") THEN EXIT; END;", 17L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
  CodeRules(yyt->U_1.V_36.List.sep);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
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
}

static void yyF12CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeCodes(yyt->U_1.V_37.Action.codes);
}

static void yyF13CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (InDefault) {
    Spaces();
    IO_WriteS(file, (STRING)"IF xxToken # ", 13L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)" (* ", 4L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteS(file, (STRING)" *) THEN", 8L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxRecoveryTerminal (", 22L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)", ", 2L);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet, ", 23L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
    IO_WriteS(file, (STRING)"); (* ", 6L);
    Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
    IO_WriteS(file, (STRING)" *)", 3L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"ELSE", 4L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  ", 2L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
    IO_WriteS(file, (STRING)" := ", 4L);
    Prefix();
    IO_WriteS(file, (STRING)".Attribute;", 11L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxToken := ", 13L);
    Prefix();
    IO_WriteS(file, (STRING)".GetToken (); xxIsRepairMode := FALSE;", 38L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"END;", 4L);
    IO_WriteNl(file);
    InDefault = FALSE;
  } else {
    Spaces();
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
    IO_WriteS(file, (STRING)" := ", 4L);
    Prefix();
    IO_WriteS(file, (STRING)".Attribute;", 11L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"xxToken := ", 11L);
    Prefix();
    IO_WriteS(file, (STRING)".GetToken (); xxIsRepairMode := FALSE;", 38L);
    IO_WriteNl(file);
  }
}

static void yyF14CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  if (InDefault) {
    Spaces();
    IO_WriteS(file, (STRING)"IF xxToken # ", 13L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)" (* ", 4L);
    Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    IO_WriteS(file, (STRING)" *) THEN", 8L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxRecoveryLiteral (", 21L);
    IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
    IO_WriteS(file, (STRING)", ", 2L);
    IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
    IO_WriteS(file, (STRING)", xxGlobalRecoverySet); (* ", 27L);
    Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
    IO_WriteS(file, (STRING)" *)", 3L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"ELSE", 4L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"  xxToken := ", 13L);
    Prefix();
    IO_WriteS(file, (STRING)".GetToken (); xxIsRepairMode := FALSE;", 38L);
    IO_WriteNl(file);
    Spaces();
    IO_WriteS(file, (STRING)"END;", 4L);
    IO_WriteNl(file);
    InDefault = FALSE;
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"xxToken := ", 11L);
    Prefix();
    IO_WriteS(file, (STRING)".GetToken (); xxIsRepairMode := FALSE;", 38L);
    IO_WriteNl(file);
  }
}

static void yyF15CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"IF xxToken # ", 13L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)" (* ", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" *) THEN", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxRecoveryTerminal (", 22L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)", ", 2L);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
  IO_WriteS(file, (STRING)", xxGlobalRecoverySet, ", 23L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
  IO_WriteS(file, (STRING)"); (* ", 6L);
  Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
  IO_WriteS(file, (STRING)" *)", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"ELSE", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  ", 2L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
  IO_WriteS(file, (STRING)" := ", 4L);
  Prefix();
  IO_WriteS(file, (STRING)".Attribute;", 11L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxToken := ", 13L);
  Prefix();
  IO_WriteS(file, (STRING)".GetToken (); xxIsRepairMode := FALSE;", 38L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
}

static void yyF16CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"IF xxToken # ", 13L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)" (* ", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" *) THEN", 8L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxRecoveryLiteral (", 21L);
  IO_WriteI(file, Codes_Code(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident), 0L);
  IO_WriteS(file, (STRING)", ", 2L);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
  IO_WriteS(file, (STRING)", xxGlobalRecoverySet); (* ", 27L);
  Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
  IO_WriteS(file, (STRING)" *)", 3L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"ELSE", 4L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"  xxToken := ", 13L);
  Prefix();
  IO_WriteS(file, (STRING)".GetToken (); xxIsRepairMode := FALSE;", 38L);
  IO_WriteNl(file);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
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
  IO_WriteS(file, (STRING)"xxUnion.LocalRecoverySet := ", 28L);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.recindex, 0L);
  IO_WriteS(file, (STRING)"; yy", 4L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteS(file, (STRING)" (", 2L);
  Idents_WriteIdent(file, yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
  IO_WriteI(file, yyt->U_1.V_38.Leaf.number, 0L);
  IO_WriteS(file, (STRING)", SYSTEM.ADR (xxUnion)); (* ", 28L);
  Codes_WriteRecIndex(file, yyt->U_1.V_38.Leaf.recindex);
  IO_WriteS(file, (STRING)" *)", 3L);
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
}

static void yyF19CodeRules
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

static void yyF20CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"LOOP", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"CASE xxToken OF", 15L);
  IO_WriteNl(file);
  CodeAltCase(yyt);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
}

static void yyF21CodeRules
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeAltIf(yyt, FALSE);
}

static void yyF22CodeAltCase
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"ELSE", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"IF xxIsRepairMode THEN", 22L);
  IO_WriteNl(file);
  INC(SpaCo);
  InDefault = TRUE;
  CodeRules(yyt->U_1.V_40.Alternative0.C_0_default);
  InDefault = FALSE;
  Spaces();
  IO_WriteS(file, (STRING)"EXIT;", 5L);
  IO_WriteNl(file);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
  CodeRecovery(yyt->U_1.V_40.Alternative0.recindex, yyt->U_1.V_40.Alternative0.expindex);
  DEC(SpaCo);
}

static void yyF23CodeAltCase
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  WriteLabels(yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_41.Alternative.expr);
  Spaces();
  IO_WriteS(file, (STRING)"EXIT;", 5L);
  IO_WriteNl(file);
  DEC(SpaCo);
  CodeAltCase(yyt->U_1.V_41.Alternative.alternative);
}

static void yyF24CodeAltIf
# ifdef __STDC__
(Tree_tTree yyt, BOOLEAN started)
# else
(yyt, started)
Tree_tTree yyt;
BOOLEAN started;
# endif
{
  Spaces();
  IO_WriteS(file, (STRING)"ELSE", 4L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRecovery(yyt->U_1.V_40.Alternative0.recindex, yyt->U_1.V_40.Alternative0.expindex);
  InDefault = TRUE;
  CodeRules(yyt->U_1.V_40.Alternative0.C_0_default);
  InDefault = FALSE;
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
}

static void yyF25CodeAltIf
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
    IO_WriteS(file, (STRING)"IF ", 3L);
    CodeIsElement(yyt->U_1.V_41.Alternative.index, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.first);
    IO_WriteS(file, (STRING)" THEN", 5L);
    IO_WriteNl(file);
  } else {
    Spaces();
    IO_WriteS(file, (STRING)"ELSE ", 5L);
    IO_WriteNl(file);
  }
  INC(SpaCo);
  CodeRules(yyt->U_1.V_41.Alternative.expr);
  DEC(SpaCo);
  Spaces();
  IO_WriteS(file, (STRING)"END;", 4L);
  IO_WriteNl(file);
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
  if (!started) {
    Spaces();
    IO_WriteS(file, (STRING)"IF ", 3L);
  } else {
    IO_WriteS(file, (STRING)"ELSIF ", 6L);
  }
  CodeIsElement(yyt->U_1.V_41.Alternative.index, yyt->U_1.V_41.Alternative.expr->U_1.V_32.expr.fifo);
  IO_WriteS(file, (STRING)" THEN", 5L);
  IO_WriteNl(file);
  INC(SpaCo);
  CodeRules(yyt->U_1.V_41.Alternative.expr);
  DEC(SpaCo);
  CodeAltIf(yyt->U_1.V_41.Alternative.alternative, TRUE);
}

static void yyF27SetNumbers
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

static void yyF28SetNumbers
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
  SetNumbers(yyt->U_1.V_35.Plus.expr, FALSE);
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
  SetNumbers(yyt->U_1.V_36.List.body, FALSE);
  SetNumbers(yyt->U_1.V_36.List.sep, FALSE);
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
  if (start) {
    ClearArray((*NumberArray).A, 1001L);
  }
  SetNumbers(yyt->U_1.V_44.Sequence.expr, FALSE);
  SetNumbers(yyt->U_1.V_44.Sequence.sequence, FALSE);
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
  SetNumbers(yyt->U_1.V_41.Alternative.expr, FALSE);
  SetNumbers(yyt->U_1.V_41.Alternative.alternative, start);
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
  yyt->U_1.V_38.Leaf.number = 0;
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
  yyt->U_1.V_38.Leaf.number = NumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident] + 1;
  NumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident] = yyt->U_1.V_38.Leaf.number;
  if (yyt->U_1.V_38.Leaf.number > MaxNumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident]) {
    MaxNumberArray->A[yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident] = yyt->U_1.V_38.Leaf.number;
  }
}

static void yyF38CodeExport
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

static void yyF39CodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeExport(yyt->U_1.V_6.Sections.sections);
}

static void yyF40CodeExport
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF41CodeGlobal
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

static void yyF42CodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeGlobal(yyt->U_1.V_6.Sections.sections);
}

static void yyF43CodeGlobal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF44CodeLocal
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

static void yyF45CodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeLocal(yyt->U_1.V_6.Sections.sections);
}

static void yyF46CodeLocal
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF47CodeBegin
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

static void yyF48CodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeBegin(yyt->U_1.V_6.Sections.sections);
}

static void yyF49CodeBegin
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF50CodeClose
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

static void yyF51CodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  CodeClose(yyt->U_1.V_6.Sections.sections);
}

static void yyF52CodeClose
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF53CodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
  IO_WriteS(file, (STRING)"(* '", 4L);
  IO_WriteS(file, ArgCheck_SourceFileName.A, 128L);
  IO_WriteS(file, (STRING)"' line ", 7L);
  IO_WriteI(file, (LONGINT)yyt->U_1.V_15.Codes.code->U_1.V_16.Code.pos.Line, 0L);
  IO_WriteS(file, (STRING)" *)", 3L);
  IO_WriteNl(file);
  StringMem_WriteString(file, yyt->U_1.V_15.Codes.code->U_1.V_16.Code.ref);
  CodeCodes2(yyt->U_1.V_15.Codes.codes);
  IO_WriteNl(file);
}

static void yyF54CodeCodes
# ifdef __STDC__
(Tree_tTree yyt)
# else
(yyt)
Tree_tTree yyt;
# endif
{
}

static void yyF55CodeCodes2
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

static void yyF56CodeCodes2
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
      info->CodeCodes.Proc = yyF53CodeCodes;
    }
    cost = 1 + CostCodeCodes2(yyt->U_1.V_15.Codes.codes);
    if (cost < info->CodeCodes2.Cost) {
      info->CodeCodes2.Cost = cost;
      info->CodeCodes2.Proc = yyF55CodeCodes2;
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
      cost = 1 + CostCodeGlobal(yyt->U_1.V_3.Grammar.sections) + CostCodeBegin(yyt->U_1.V_3.Grammar.sections) + CostCodeClose(yyt->U_1.V_3.Grammar.sections) + CostCodeRules(yyt->U_1.V_3.Grammar.rules);
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
      info->CodeExport.Proc = yyF40CodeExport;
    }
    cost = 1;
    if (cost < info->CodeGlobal.Cost) {
      info->CodeGlobal.Cost = cost;
      info->CodeGlobal.Proc = yyF43CodeGlobal;
    }
    cost = 1;
    if (cost < info->CodeLocal.Cost) {
      info->CodeLocal.Cost = cost;
      info->CodeLocal.Proc = yyF46CodeLocal;
    }
    cost = 1;
    if (cost < info->CodeBegin.Cost) {
      info->CodeBegin.Cost = cost;
      info->CodeBegin.Proc = yyF49CodeBegin;
    }
    cost = 1;
    if (cost < info->CodeClose.Cost) {
      info->CodeClose.Cost = cost;
      info->CodeClose.Proc = yyF52CodeClose;
    }
    break;
  case Tree_Sections:;
    state = 17;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_6.Sections.section)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_6.Sections.sections)];
    match = (yySetType *)ADR(yySets.A[state]);
    yyMatch.A[38] = IN(6, match->A[1]);
    yyMatch.A[39] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Export;
    yyMatch.A[41] = IN(9, match->A[1]);
    yyMatch.A[42] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Global;
    yyMatch.A[44] = IN(12, match->A[1]);
    yyMatch.A[45] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Local;
    yyMatch.A[47] = IN(15, match->A[1]);
    yyMatch.A[48] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Begin;
    yyMatch.A[50] = IN(18, match->A[1]);
    yyMatch.A[51] = TRUE && yyt->U_1.V_6.Sections.section->U_1.V_1.Kind != Tree_Close;
    if (yyMatch.A[38]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_8.Export.codes) + CostCodeExport(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeExport.Cost) {
        info->CodeExport.Cost = cost;
        info->CodeExport.Proc = yyF38CodeExport;
      }
    }
    if (yyMatch.A[39]) {
      cost = 1 + CostCodeExport(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeExport.Cost) {
        info->CodeExport.Cost = cost;
        info->CodeExport.Proc = yyF39CodeExport;
      }
    }
    if (yyMatch.A[41]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_9.Global.codes) + CostCodeGlobal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeGlobal.Cost) {
        info->CodeGlobal.Cost = cost;
        info->CodeGlobal.Proc = yyF41CodeGlobal;
      }
    }
    if (yyMatch.A[42]) {
      cost = 1 + CostCodeGlobal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeGlobal.Cost) {
        info->CodeGlobal.Cost = cost;
        info->CodeGlobal.Proc = yyF42CodeGlobal;
      }
    }
    if (yyMatch.A[44]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_10.Local.codes) + CostCodeLocal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeLocal.Cost) {
        info->CodeLocal.Cost = cost;
        info->CodeLocal.Proc = yyF44CodeLocal;
      }
    }
    if (yyMatch.A[45]) {
      cost = 1 + CostCodeLocal(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeLocal.Cost) {
        info->CodeLocal.Cost = cost;
        info->CodeLocal.Proc = yyF45CodeLocal;
      }
    }
    if (yyMatch.A[47]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_11.Begin.codes) + CostCodeBegin(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeBegin.Cost) {
        info->CodeBegin.Cost = cost;
        info->CodeBegin.Proc = yyF47CodeBegin;
      }
    }
    if (yyMatch.A[48]) {
      cost = 1 + CostCodeBegin(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeBegin.Cost) {
        info->CodeBegin.Cost = cost;
        info->CodeBegin.Proc = yyF48CodeBegin;
      }
    }
    if (yyMatch.A[50]) {
      cost = 1 + CostCodeCodes(yyt->U_1.V_6.Sections.section->U_1.V_12.Close.codes) + CostCodeClose(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeClose.Cost) {
        info->CodeClose.Cost = cost;
        info->CodeClose.Proc = yyF50CodeClose;
      }
    }
    if (yyMatch.A[51]) {
      cost = 1 + CostCodeClose(yyt->U_1.V_6.Sections.sections);
      if (cost < info->CodeClose.Cost) {
        info->CodeClose.Cost = cost;
        info->CodeClose.Proc = yyF51CodeClose;
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
      info->CodeCodes.Proc = yyF54CodeCodes;
    }
    cost = 1;
    if (cost < info->CodeCodes2.Cost) {
      info->CodeCodes2.Cost = cost;
      info->CodeCodes2.Proc = yyF56CodeCodes2;
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
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF5CodeRules;
    }
    break;
  case Tree_Rules:;
    state = 34;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_29.Rules.rule)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_29.Rules.rules)];
    cost = 1 + CostCodeCodes(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.codes) + CostSetNumbers(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostCodeRules(yyt->U_1.V_29.Rules.rule->U_1.V_30.Rule.expr) + CostCodeRules(yyt->U_1.V_29.Rules.rules);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF6CodeRules;
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
      info->CodeRules.Proc = yyF7CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_33.Option.expr);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF27SetNumbers;
    }
    break;
  case Tree_Times:;
    state = 168;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_34.Times.expr)];
    cost = 1 + CostCodeRules(yyt->U_1.V_34.Times.expr);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF8CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_34.Times.expr);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF28SetNumbers;
    }
    break;
  case Tree_Plus:;
    state = 181;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_35.Plus.expr)];
    cost = 1 + CostCodeRules(yyt->U_1.V_35.Plus.expr);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF9CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_35.Plus.expr);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF29SetNumbers;
    }
    break;
  case Tree_List:;
    state = 209;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_36.List.body)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_36.List.sep)];
    cost = 1 + CostCodeRules(yyt->U_1.V_36.List.body) + CostCodeRules(yyt->U_1.V_36.List.sep);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF10CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_36.List.body) + CostSetNumbers(yyt->U_1.V_36.List.sep);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF30SetNumbers;
    }
    break;
  case Tree_Action:;
    state = 135;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_37.Action.codes)];
    match = (yySetType *)ADR(yySets.A[state]);
    yyMatch.A[11] = IN(11, match->A[0]);
    if (yyMatch.A[11]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF11CodeRules;
      }
    }
    cost = 1 + CostCodeCodes(yyt->U_1.V_37.Action.codes);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF12CodeRules;
    }
    cost = 1;
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF31SetNumbers;
    }
    break;
  case Tree_Leaf:;
    state = 36;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_38.Leaf.id)];
    yyMatch.A[13] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && yyt->U_1.V_38.Leaf.sure && !yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[14] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && yyt->U_1.V_38.Leaf.sure && yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[15] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && !yyt->U_1.V_38.Leaf.sure && !yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[16] = TRUE && (Types_IsTerm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident) && !yyt->U_1.V_38.Leaf.sure && yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring);
    yyMatch.A[17] = TRUE && Types_IsNonterm(yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.ident);
    yyMatch.A[36] = TRUE && yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring;
    yyMatch.A[37] = TRUE && !yyt->U_1.V_38.Leaf.id->U_1.V_23.Id.isstring;
    if (yyMatch.A[13]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF13CodeRules;
      }
    }
    if (yyMatch.A[14]) {
      cost = 1;
      if (cost < info->CodeRules.Cost) {
        info->CodeRules.Cost = cost;
        info->CodeRules.Proc = yyF14CodeRules;
      }
    }
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
    if (yyMatch.A[36]) {
      cost = 1;
      if (cost < info->SetNumbers.Cost) {
        info->SetNumbers.Cost = cost;
        info->SetNumbers.Proc = yyF36SetNumbers;
      }
    }
    if (yyMatch.A[37]) {
      cost = 1;
      if (cost < info->SetNumbers.Cost) {
        info->SetNumbers.Cost = cost;
        info->SetNumbers.Proc = yyF37SetNumbers;
      }
    }
    break;
  case Tree_Alternative0:;
    state = 14;
    yyMatch.A[20] = TRUE && yyt->U_1.V_39.alternative.C_0_case;
    yyMatch.A[21] = TRUE && !yyt->U_1.V_39.alternative.C_0_case;
    cost = 1;
    if (cost < info->CodeAltCase.Cost) {
      info->CodeAltCase.Cost = cost;
      info->CodeAltCase.Proc = yyF22CodeAltCase;
    }
    cost = 1;
    if (cost < info->CodeAltIf.Cost) {
      info->CodeAltIf.Cost = cost;
      info->CodeAltIf.Proc = yyF24CodeAltIf;
    }
    cost = 1;
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF34SetNumbers;
    }
    do {
      success = FALSE;
      if (yyMatch.A[20]) {
        cost = 1 + CostCodeAltCase(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF20CodeRules;
          success = TRUE;
        }
      }
      if (yyMatch.A[21]) {
        cost = 1 + CostCodeAltIf(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF21CodeRules;
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
    yyMatch.A[20] = TRUE && yyt->U_1.V_39.alternative.C_0_case;
    yyMatch.A[21] = TRUE && !yyt->U_1.V_39.alternative.C_0_case;
    yyMatch.A[25] = IN(25, match->A[0]);
    cost = 1 + CostCodeRules(yyt->U_1.V_41.Alternative.expr) + CostCodeAltCase(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->CodeAltCase.Cost) {
      info->CodeAltCase.Cost = cost;
      info->CodeAltCase.Proc = yyF23CodeAltCase;
    }
    if (yyMatch.A[25]) {
      cost = 1 + CostCodeRules(yyt->U_1.V_41.Alternative.expr);
      if (cost < info->CodeAltIf.Cost) {
        info->CodeAltIf.Cost = cost;
        info->CodeAltIf.Proc = yyF25CodeAltIf;
      }
    }
    cost = 1 + CostCodeRules(yyt->U_1.V_41.Alternative.expr) + CostCodeAltIf(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->CodeAltIf.Cost) {
      info->CodeAltIf.Cost = cost;
      info->CodeAltIf.Proc = yyF26CodeAltIf;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_41.Alternative.expr) + CostSetNumbers(yyt->U_1.V_41.Alternative.alternative);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF35SetNumbers;
    }
    do {
      success = FALSE;
      if (yyMatch.A[20]) {
        cost = 1 + CostCodeAltCase(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF20CodeRules;
          success = TRUE;
        }
      }
      if (yyMatch.A[21]) {
        cost = 1 + CostCodeAltIf(yyt);
        if (cost < info->CodeRules.Cost) {
          info->CodeRules.Cost = cost;
          info->CodeRules.Proc = yyF21CodeRules;
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
      info->CodeRules.Proc = yyF18CodeRules;
    }
    cost = 1;
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF32SetNumbers;
    }
    break;
  case Tree_Sequence:;
    state = 264;
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_44.Sequence.expr)];
    state = yyComb.A[state + yyTraverse(yyt->U_1.V_44.Sequence.sequence)];
    cost = 1 + CostCodeRules(yyt->U_1.V_44.Sequence.expr) + CostCodeRules(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->CodeRules.Cost) {
      info->CodeRules.Cost = cost;
      info->CodeRules.Proc = yyF19CodeRules;
    }
    cost = 1 + CostSetNumbers(yyt->U_1.V_44.Sequence.expr) + CostSetNumbers(yyt->U_1.V_44.Sequence.sequence);
    if (cost < info->SetNumbers.Cost) {
      info->SetNumbers.Cost = cost;
      info->SetNumbers.Proc = yyF33SetNumbers;
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

void CodeM2_BeginCodeM2
# ifdef __STDC__
()
# else
()
# endif
{
  System_tFile yyf;
  INTEGER yyi;

  yyf = OpenInput(CodeM2_CodeM2TabName.A, 128L);
  yyErrorCheck(yyf, (STRING)"cannot open ", 12L, CodeM2_CodeM2TabName.A, 128L);
  yyi = Read(yyf, ADR(yySets), (LONGINT)sizeof(yySetsType));
  yyErrorCheck(yyi, (STRING)"cannot read ", 12L, CodeM2_CodeM2TabName.A, 128L);
  yyi = Read(yyf, ADR(yyComb), (LONGINT)sizeof(yyCombType));
  yyErrorCheck(yyi, (STRING)"cannot read ", 12L, CodeM2_CodeM2TabName.A, 128L);
  Close(yyf);
  vExport = FALSE;
  SpaCo = 0;
  InDefault = FALSE;
}

void CodeM2_DoCodeM2
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

void CodeM2_CloseCodeM2
# ifdef __STDC__
()
# else
()
# endif
{
}

void CodeM2__init()
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

    (void)strncpy((char *)CodeM2_CodeM2TabName.A, "CodeM2.tab", sizeof(CodeM2_CodeM2TabName.A));
    {
      register yyInfoType *W_1 = &yyInfo;

      W_1->CODE.Cost = yyInfinite;
      W_1->CODE.Proc = yyECODE;
      W_1->CodeDef.Cost = yyInfinite;
      W_1->CodeDef.Proc = yyECodeDef;
      W_1->CodeImp.Cost = yyInfinite;
      W_1->CodeImp.Proc = yyECodeImp;
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
