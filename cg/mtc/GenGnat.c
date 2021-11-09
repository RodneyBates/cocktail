#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_GenGnat
#include "GenGnat.h"
#endif

IO_tFile GenGnat_yyf;
PROC GenGnat_Exit;

static BOOLEAN debug1;
static Tree_tTree Node;
static Tree_tTree gNClassNonEmptyClass;
static Tree_tTree gEntityClass;
static Idents_tIdent gIdentNodeNumber;
static Idents_tIdent gIdentNext;
static Idents_tIdent gIdentPrev;
static Idents_tIdent gIdentIsListMember;
static Idents_tIdent gIdentLink;
static Idents_tIdent gIdentSloc;
static Idents_tIdent gIdentIsRewriteSubstitution;
static Idents_tIdent gIdentIsRewriteInsertion;
static Idents_tIdent gIdentComesFromSource;
static Idents_tIdent gIdentAnalyzed;
static Idents_tIdent gIdentErrorPosted;
static Idents_tIdent gIdentParenCount;
static Idents_tIdent gIdentHasDynamicLengthCheck;
static Idents_tIdent gIdentHasDynamicRangeCheck;
static Idents_tIdent gIdentDiscriminantConstraint;
static Idents_tIdent gIdentPrimitiveOperations;
static Idents_tIdent gIdentPrivalsChain;
static Idents_tIdent gIdentPrivateDependents;
static Idents_tIdent gIdentGirderConstraint;
static Idents_tIdent gIdentDefiningIdentifier;
static Idents_tIdent gIdentMechanism;
static Idents_tIdent gIdentChars;
static Idents_tIdent gIdentNextEntity;
static Idents_tIdent gIdentScope;
static Idents_tIdent gIdentHomonym;
static Idents_tIdent gIdentEtype;
static Idents_tIdent gIdentEinfo;
static Idents_tIdent gIdentSinfo;
static Idents_tIdent gIdentGnatUtils;
static Idents_tIdent gIdentGnatAdaUtils;
static Idents_tIdent gIdentAtree;
static Idents_tIdent gIdentNlists;
static Idents_tIdent gIdentNClassNonEmpty;
static Idents_tIdent gIdentNClassEntity;
static Idents_tIdent gFieldInterface;
static Strings_tString gString;
static void WG ARGS((Idents_tIdent Ident));
static BOOLEAN IsDescendedFrom ARGS((Tree_tTree Descendent, Tree_tTree Ancestor));
static Idents_tIdent PackageName ARGS((Idents_tIdent FieldName));
#define UseQualifiers   FALSE
static void WriteQualifier ARGS((Idents_tIdent Name));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
static void Convert ARGS((Tree_tTree t));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void ConvertAttrs ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


static void WG
# ifdef __STDC__
(Idents_tIdent Ident)
# else
(Ident)
Idents_tIdent Ident;
# endif
{
  CARDINAL I;
  Strings_tString LString;
  CHAR LPrevChar, LChar, LNextChar;
  CARDINAL LLength;

  Idents_GetString(Ident, &LString);
  LLength = Strings_Length(&LString);
  if (LLength > 0) {
    I = 1;
    LPrevChar = ' ';
    LChar = Strings_Char(&LString, 1);
    for (;;) {
      if (I < LLength) {
        INC(I);
        LNextChar = Strings_Char(&LString, (Strings_tStringIndex)I);
      } else if (I == LLength) {
        INC(I);
        LNextChar = ' ';
      } else {
        goto EXIT_1;
      }
      if ('a' <= LPrevChar && LPrevChar <= 'z' && ('0' <= LChar && LChar <= '9' || 'A' <= LChar && LChar <= 'Z') || 'A' <= LPrevChar && LPrevChar <= 'Z' && ('A' <= LChar && LChar <= 'Z') && ('a' <= LNextChar && LNextChar <= 'z')) {
        IO_WriteC(Tree_f, '_');
      }
      IO_WriteC(Tree_f, LChar);
      LPrevChar = LChar;
      LChar = LNextChar;
    } EXIT_1:;
  }
}

static BOOLEAN IsDescendedFrom
# ifdef __STDC__
(Tree_tTree Descendent, Tree_tTree Ancestor)
# else
(Descendent, Ancestor)
Tree_tTree Descendent;
Tree_tTree Ancestor;
# endif
{
  Tree_tTree LClass;

  if (Ancestor == Tree_NoTree) {
    return FALSE;
  } else if (Tree_IsType(Ancestor, Tree_NoClass)) {
    return FALSE;
  } else if (!Tree_IsType(Ancestor, Tree_Class)) {
    Errors_MessageI((STRING)"IsDescendedFrom, Ancestor not Class", 35L, (LONGCARD)Errors_Fatal, Positions_NoPosition, (LONGCARD)Errors_Integer, ADR(Ancestor->U_1.V_1.Kind));
  } else {
    LClass = Descendent;
    for (;;) {
      if (LClass == Ancestor) {
        return TRUE;
      } else if (LClass == Tree_NoTree) {
        return FALSE;
      } else if (Tree_IsType(LClass, Tree_NoClass)) {
        return FALSE;
      } else if (!Tree_IsType(LClass, Tree_Class)) {
        Errors_MessageI((STRING)"IsDescendedFrom, LClass not Class", 33L, (LONGCARD)Errors_Fatal, Positions_NoPosition, (LONGCARD)Errors_Integer, ADR(LClass->U_1.V_1.Kind));
      } else {
        LClass = LClass->U_1.V_5.Class.BaseClass;
      }
    } EXIT_2:;
  }
}

static Idents_tIdent PackageName
# ifdef __STDC__
(Idents_tIdent FieldName)
# else
(FieldName)
Idents_tIdent FieldName;
# endif
{
  if (FieldName == gIdentNext) {
    return gIdentNlists;
  } else if (FieldName == gIdentPrev) {
    return gIdentNlists;
  } else if (FieldName == gIdentLink) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentNextEntity) {
    return gIdentSinfo;
  } else if (FieldName == gIdentScope) {
    return gIdentSinfo;
  } else if (FieldName == gIdentHomonym) {
    return gIdentSinfo;
  } else if (FieldName == gIdentEtype) {
    return gIdentSinfo;
  } else if (FieldName == gIdentDiscriminantConstraint) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentPrimitiveOperations) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentPrivalsChain) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentPrivateDependents) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentGirderConstraint) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentDefiningIdentifier) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentMechanism) {
    return gIdentGnatAdaUtils;
  } else if (FieldName == gIdentIsListMember) {
    return gIdentNlists;
  } else if (FieldName == gIdentSloc) {
    return gIdentAtree;
  } else if (FieldName == gIdentIsRewriteSubstitution) {
    return gIdentAtree;
  } else if (FieldName == gIdentIsRewriteInsertion) {
    return gIdentAtree;
  } else if (FieldName == gIdentComesFromSource) {
    return gIdentAtree;
  } else if (FieldName == gIdentAnalyzed) {
    return gIdentAtree;
  } else if (FieldName == gIdentErrorPosted) {
    return gIdentAtree;
  } else if (FieldName == gIdentParenCount) {
    return gIdentAtree;
  } else if (FieldName == gIdentHasDynamicLengthCheck) {
    return gIdentSinfo;
  } else if (FieldName == gIdentHasDynamicRangeCheck) {
    return gIdentSinfo;
  } else if (FieldName == gIdentChars) {
    return gIdentSinfo;
  } else {
    return gFieldInterface;
  }
}

static void WriteQualifier
# ifdef __STDC__
(Idents_tIdent Name)
# else
(Name)
Idents_tIdent Name;
# endif
{
  if (Sets_IsElement(ORD('%'), &Tree_Options)) {
    Tree_WI(PackageName(Name));
    IO_WriteS(Tree_f, (STRING)" . ", 3L);
  }
}

static void yyAbort
# ifdef __STDC__
(CHAR yyFunction[], LONGCARD O_1)
# else
(yyFunction, O_1)
CHAR yyFunction[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yyFunction, O_1, CHAR)
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module GenGnat, routine ", 31L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*GenGnat_Exit)();
  FREE_OPEN_ARRAYS
}

static BOOLEAN yyIsEqual
# ifdef __STDC__
(BYTE yya[], LONGCARD O_3, BYTE yyb[], LONGCARD O_2)
# else
(yya, O_3, yyb, O_2)
BYTE yya[];
LONGCARD O_3;
BYTE yyb[];
LONGCARD O_2;
# endif
{
  INTEGER yyi;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(WORD) + O_3 * sizeof(WORD), 2)
  COPY_OPEN_ARRAY(yyb, O_2, WORD)
  COPY_OPEN_ARRAY(yya, O_3, WORD)
  {
    LONGINT B_1 = 0, B_2 = (INTEGER)(O_3 - 1);

    if (B_1 <= B_2)
      for (yyi = B_1;; yyi += 1) {
        if (yya[yyi] != yyb[yyi]) {
          FREE_OPEN_ARRAYS
          return FALSE;
        }
        if (yyi >= B_2) break;
      }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

void GenGnat_GnatModule
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_3 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Ag) {
    {
      register Tree_yAg *W_1 = &t->U_1.V_26.Ag;

      if (Sets_IsElement(ORD('~'), &Tree_Options)) {
        debug1 = Sets_IsElement(ORD('Z'), &Tree_Options);
        Strings_ArrayToString((STRING)"NodeNumber", 10L, &gString);
        gIdentNodeNumber = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Next", 4L, &gString);
        gIdentNext = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Prev", 4L, &gString);
        gIdentPrev = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"IsListMember", 12L, &gString);
        gIdentIsListMember = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Link", 4L, &gString);
        gIdentLink = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Sloc", 4L, &gString);
        gIdentSloc = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"IsRewriteSubstitution", 21L, &gString);
        gIdentIsRewriteSubstitution = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"IsRewriteInsertion", 18L, &gString);
        gIdentIsRewriteInsertion = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"ComesFromSource", 15L, &gString);
        gIdentComesFromSource = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Analyzed", 8L, &gString);
        gIdentAnalyzed = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"ErrorPosted", 11L, &gString);
        gIdentErrorPosted = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"ParenCount", 10L, &gString);
        gIdentParenCount = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"HasDynamicLengthCheck", 21L, &gString);
        gIdentHasDynamicLengthCheck = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"DiscriminantConstraint", 22L, &gString);
        gIdentDiscriminantConstraint = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"PrimitiveOperations", 19L, &gString);
        gIdentPrimitiveOperations = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"PrivalsChain", 12L, &gString);
        gIdentPrivalsChain = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"PrivateDependents", 17L, &gString);
        gIdentPrivateDependents = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"GirderConstraint", 16L, &gString);
        gIdentGirderConstraint = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"DefiningIdentifier", 18L, &gString);
        gIdentDefiningIdentifier = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Mechanism", 9L, &gString);
        gIdentMechanism = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"HasDynamicRangeCheck", 20L, &gString);
        gIdentHasDynamicRangeCheck = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Chars", 5L, &gString);
        gIdentChars = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"NextEntity", 10L, &gString);
        gIdentNextEntity = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Scope", 5L, &gString);
        gIdentScope = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Homonym", 7L, &gString);
        gIdentHomonym = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Etype", 5L, &gString);
        gIdentEtype = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Einfo", 5L, &gString);
        gIdentEinfo = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Sinfo", 5L, &gString);
        gIdentSinfo = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"GnatUtils", 9L, &gString);
        gIdentGnatUtils = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"GnatAdaUtils", 12L, &gString);
        gIdentGnatAdaUtils = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Atree", 5L, &gString);
        gIdentAtree = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"Nlists", 6L, &gString);
        gIdentNlists = Idents_MakeIdent(&gString);
        Strings_ArrayToString((STRING)"NClassNonEmpty", 14L, &gString);
        gIdentNClassNonEmpty = Idents_MakeIdent(&gString);
        gNClassNonEmptyClass = Tree_IdentifyClass((Tree_tTree)Tree_NoTree, gIdentNClassNonEmpty);
        Strings_ArrayToString((STRING)"NClassEntity", 12L, &gString);
        gIdentNClassEntity = Idents_MakeIdent(&gString);
        gEntityClass = Tree_IdentifyClass((Tree_tTree)Tree_NoTree, gIdentNClassEntity);
        IO_WriteS(Tree_f, (STRING)"TYPE yyPtrtTree	= UNTRACED REF ", 31L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE yytMapArray = ARRAY OF ", 28L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)" ;", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"TYPE yytMapRef = REF yytMapArray ;", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyNodeMapRef : yytMapRef ;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyListMapRef : yytMapRef ;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyElistMapRef : yytMapRef ;", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyElmtMapRef : yytMapRef ;", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"VAR yyNextNodeNumber : INTEGER := 1 ;", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"PROCEDURE yyConvert", 19L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ( FId : GnatTypes . Union_Id ", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ; FNew : yyPtrtTree ", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ; FCallerId : GnatTypes . Union_Id ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   ; FCallerField : TEXT ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   )", 4L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR LKind : ", 13L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . SHORTCARD ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)";VAR LId := FId", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)";VAR LNew := FNew", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)";VAR LCallerId := FCallerId", 27L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)";VAR LCallerField := FCallerField", 33L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)";BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  LOOP", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    IF GnatTypes . List_Low_Bound <= LId ", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"       AND LId < GnatTypes . List_Low_Bound + NUMBER ( yyListMapRef ^ )", 71L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    THEN (* This is a list node. *) ", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      IF LId = GnatTypes . No_List", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      THEN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        VAR LNewList := NEW ( ", 30L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . NoList )", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                   (* Multiple copies of NoList nodes *)", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; BEGIN", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          LNew ^ := LNewList", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNew ^ . Kind := Tree . NkNoList", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNewList . NodeNumber := yyNextNodeNumber", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; INC ( yyNextNodeNumber )", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; RETURN", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        END (* BEGIN *)", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* IF *) ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; WITH WNewRef = yyListMapRef ^ [ LId - GnatTypes . List_Low_Bound ] ", 73L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      DO", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        IF WNewRef # ", 21L);
        Tree_WI(Tree_iNoTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        THEN LNew ^ := WNewRef ; RETURN END (* IF *) ", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; VAR LNewList : Tree . List := NEW ( ", 44L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . List ) ", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; BEGIN", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"            WNewRef := LNewList", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew ^ := LNewList", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew ^ . Kind := Tree . NkList", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNewList . NodeNumber := yyNextNodeNumber", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; INC ( yyNextNodeNumber )", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; yyConvert", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               ( Nlists . Parent ( LId ) , ADR ( LNewList . Parent )", 68L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               , LId , \" Parent\" ) ", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; yyConvert", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               ( Nlists . Last ( LId ) , ADR ( LNewList . Last )", 64L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               , LId , \"Last\" ) ", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LCallerId := LId", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LCallerField := \"First\"", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LId := Nlists . First ( LId ) ", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew := ADR ( LNewList . First )", 44L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          END (* BEGIN *) ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* WITH WNewRef *) ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSIF GnatTypes . Elist_Low_Bound <= LId", 44L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          AND LId < GnatTypes . Elist_Low_Bound + NUMBER ( yyElistMapRef ^ )", 76L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    THEN (* This is an Elist node. *) ", 38L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      IF LId = GnatTypes . No_Elist", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      THEN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        VAR LNewElist := NEW ( ", 31L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . NoElist ) ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                   (* Multiple copies of NoElist nodes *)", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; BEGIN", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          LNew ^ := LNewElist", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNew ^ . Kind := Tree . NkNoElist", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNewElist . NodeNumber := yyNextNodeNumber", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; INC ( yyNextNodeNumber )", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; RETURN  ", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        END (* BEGIN *)", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* IF *) ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; WITH WNewRef = yyElistMapRef ^ [ LId - GnatTypes . Elist_Low_Bound ] ", 75L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      DO", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        IF WNewRef # ", 21L);
        Tree_WI(Tree_iNoTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        THEN LNew ^ := WNewRef ; RETURN END (* IF *) ", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; VAR LNewElist : Tree . Elist := NEW ( ", 46L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . Elist ) ", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; BEGIN", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"            WNewRef := LNewElist", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew ^ := LNewElist", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew ^ . Kind := Tree . NkElist", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNewElist . NodeNumber := yyNextNodeNumber", 54L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; INC ( yyNextNodeNumber )", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; yyConvert", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               ( Elists . Last_Elmt ( LId ) , ADR ( LNewElist . LastElmt )", 74L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               , LId , \"Last_Elmt\" ) ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LCallerId := LId", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LCallerField := \"First_Elmt\"", 40L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LId := Elists . First_Elmt ( LId ) ", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew := ADR ( LNewElist . FirstElmt )", 49L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          END (* BEGIN *) ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* WITH WNewRef *) ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSIF GnatTypes . Elmt_Low_Bound <= LId", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          AND LId < GnatTypes . Elmt_Low_Bound + NUMBER ( yyElmtMapRef ^ )", 74L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    THEN (* This is an Elmt node. *) ", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      IF LId = GnatTypes . No_Elmt", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      THEN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        VAR LNewElmt := NEW ( ", 30L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . NoElmt ) ", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                   (* Multiple copies of NoElmt nodes *)", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; BEGIN", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          LNew ^ := LNewElmt ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNew ^ . Kind := Tree . NkNoElmt", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNewElmt . NodeNumber := yyNextNodeNumber", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; INC ( yyNextNodeNumber )", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; RETURN ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        END (* BEGIN *)", 23L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* IF *) ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; WITH WNewRef = yyElmtMapRef ^ [ LId - GnatTypes . Elmt_Low_Bound ] ", 73L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      DO", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        IF WNewRef # ", 21L);
        Tree_WI(Tree_iNoTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        THEN LNew ^ := WNewRef", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; RETURN", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        END (* IF *) ", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; VAR LNewElmt : Tree . Elmt := NEW ( ", 44L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . Elmt ) ", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; BEGIN", 15L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"            WNewRef := LNewElmt", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew ^ := LNewElmt", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew ^ . Kind := Tree . NkElmt", 42L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNewElmt . NodeNumber := yyNextNodeNumber", 53L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; INC ( yyNextNodeNumber )", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; yyConvert", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               ( Elists . Node ( LId ) , ADR ( LNewElmt . Node )", 64L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               , LId , \"Node\" ) ", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LCallerId := LId", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LCallerField := \"Next_Elmt\"", 39L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LId := Elists . Next_Elmt ( LId ) ", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          ; LNew := ADR ( LNewElmt . NextElmt )", 47L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          END (* BEGIN *) ", 26L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* WITH WNewRef *) ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSIF GnatTypes . Node_Low_Bound <= LId", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          AND LId < GnatTypes . Node_Low_Bound + NUMBER ( yyNodeMapRef ^ )", 74L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    THEN (* This is an ordinary node. *) ", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      IF LId = GnatTypes . Empty", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      THEN", 10L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        VAR LNewNode := NEW ( ", 30L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . NNoNode ) ", 13L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                   (* Multiple copies of Empty nodes *)", 55L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; BEGIN ", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"          LNew ^ := LNewNode ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNew ^ . Kind := Tree . NkNNoNode", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; LNewNode . NodeNumber := yyNextNodeNumber", 51L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; INC ( yyNextNodeNumber )", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; RETURN ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        END (* BEGIN *) ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* IF *) ", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; WITH WNewRef = yyNodeMapRef [ LId - GnatTypes . Node_Low_Bound ] ", 71L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      DO", 8L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        IF WNewRef # ", 21L);
        Tree_WI(Tree_iNoTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        THEN LNew ^ := WNewRef", 30L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        ; RETURN", 16L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        END (* IF *) ", 21L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; LKind := GnatUtils . Kind ( LId )", 41L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      ; CASE LKind OF", 21L);
        IO_WriteNl(Tree_f);
        Tree_ForallClasses(W_1->Classes, (Tree_ProcOfT)Convert);
        IO_WriteS(Tree_f, (STRING)"        END (* CASE *)", 22L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      END (* WITH WNewRef *) ", 29L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ELSE (* Bad UnionId *)  ", 28L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"      Wr . PutText ( Stdio . stdout , \"Bad union id, \" )", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; Wr . PutText ( Stdio . stdout , Fmt . Int ( LCallerId ) )", 63L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; Wr . PutChar ( Stdio . stdout , ':' )", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; Wr . PutText ( Stdio . stdout , LCallerField )", 52L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; Wr . PutChar ( Stdio . stdout , '=' )", 43L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; Wr . PutText ( Stdio . stdout , Fmt . Int ( LId ) )", 57L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; Wr . PutText ( Stdio . stdout , Wr . EOL )", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; Wr . Flush ( Stdio . stdout )", 35L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; LNew ^ := NIL", 19L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ; RETURN", 12L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    END (* IF *) ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  END (* LOOP *) ", 17L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END yyConvert", 14L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        if (debug1) {
          IO_WriteS(Tree_f, (STRING)"PROCEDURE yyWriteHex ( VAR yyx : ARRAY OF CHAR ) ", 49L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"=BEGIN", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO NUMBER ( yyx ) - 1 DO", 39L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   Wr . PutText ( Stdio . stdout , Fmt . Pad ( Fmt . Int ( ORD ( yyx [ yyi ] ) , 16 ) , 2 , '0' ) ) ;", 101L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"   Wr . PutChar ( Stdio . stdout , ' ' ) ;", 42L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  END ;", 7L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" END yyWriteHex ;", 17L);
          IO_WriteNl(Tree_f);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"PROCEDURE GnatConvert", 21L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" ( GnatTree : GnatTypes . Node_Id ) ", 36L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" : ", 3L);
        Tree_WI(Tree_itTree);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"=VAR LNew	: ", 12L);
        Tree_WI(Tree_itTree);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyNodeMapRef := NEW ( yytMapRef , Atree . Last_Node_Id ( )  - GnatTypes . Node_Low_Bound + 1 ) ;", 98L);
        IO_WriteNl(Tree_f);
        if (debug1) {
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"Last_Node_Id = \" ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( Atree . Last_Node_Id ( ) ) ) ; ", 77L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"yyNodeMapRef = \" ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyWriteHex ( LOOPHOLE ( yyNodeMapRef , ARRAY [ 0..BYTESIZE ( yytMapRef ) - 1 ] OF CHAR ) ) ; ", 95L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"NUMBER = \" ) ; ", 50L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( NUMBER ( yyNodeMapRef ^ ) ) ) ; ", 78L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . Flush ( Stdio . stdout ) ; ", 34L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  yyListMapRef := NEW ( yytMapRef , Nlists . Last_List_Id ( ) - GnatTypes . List_Low_Bound + 1 ) ;", 98L);
        IO_WriteNl(Tree_f);
        if (debug1) {
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"Last_List_Id = \" ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( Nlists . Last_List_Id ( ) ) ) ; ", 78L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"yyListMapRef = \" ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyWriteHex ( LOOPHOLE ( yyListMapRef , ARRAY [ 0..BYTESIZE ( yytMapRef ) - 1 ] OF CHAR ) ) ; ", 95L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"NUMBER = \" ) ; ", 50L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( NUMBER ( yyListMapRef ^ ) ) ) ; ", 78L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . Flush ( Stdio . stdout ) ; ", 34L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  yyElistMapRef := NEW ( yytMapRef , Elists . Last_Elist_Id ( ) - GnatTypes . Elist_Low_Bound + 1 ) ;", 101L);
        IO_WriteNl(Tree_f);
        if (debug1) {
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"Last_Elist_Id = \" ) ; ", 57L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( Elists . Last_Elist_Id ( ) ) ) ; ", 79L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"yyElistMapRef = \" ) ; ", 57L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyWriteHex ( LOOPHOLE ( yyElistMapRef , ARRAY [ 0..BYTESIZE ( yytMapRef ) - 1 ] OF CHAR ) ) ; ", 96L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"NUMBER = \" ) ; ", 50L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( NUMBER ( yyElistMapRef ^ ) ) ) ; ", 79L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . Flush ( Stdio . stdout ) ; ", 34L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteS(Tree_f, (STRING)"  yyElmtMapRef := NEW ( yytMapRef , Elists . Last_Elmt_Id ( ) - GnatTypes . Elmt_Low_Bound + 1 ) ;", 98L);
        IO_WriteNl(Tree_f);
        if (debug1) {
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"Last_Elmt_Id = \" ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( Elists . Last_Elmt_Id ( ) ) ) ; ", 78L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"yyElmtMapRef = \" ) ; ", 56L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  yyWriteHex ( LOOPHOLE ( yyElmtMapRef , ARRAY [ 0..BYTESIZE ( yytMapRef ) - 1 ] OF CHAR ) ) ; ", 95L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , \"NUMBER = \" ) ; ", 50L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Fmt . Int ( NUMBER ( yyElmtMapRef ^ ) ) ) ; ", 78L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . PutText ( Stdio . stdout , Wr . EOL ) ; ", 47L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"  Wr . Flush ( Stdio . stdout ) ; ", 34L);
          IO_WriteNl(Tree_f);
        }
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyConvert", 11L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"    ( GnatTree , ADR ( LNew ) , 0 , \"<ROOT>\" ) ;", 48L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyNodeMapRef := NIL ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyListMapRef := NIL ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyElistMapRef := NIL ; ", 25L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  yyElmtMapRef := NIL ; ", 24L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  RETURN LNew;", 14L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)" END GnatConvert", 16L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void Convert
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_4 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_2 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_2->Properties) == 0X0L && W_2->Extensions->U_1.V_1.Kind == Tree_NoClass && IsDescendedFrom(t, gNClassNonEmptyClass)) {
        IO_WriteS(Tree_f, (STRING)"        | ", 10L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . Nk", 5L);
        Tree_WI(W_2->Name);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"        => VAR LNewNode := NEW ( ", 33L);
        Tree_WI(Tree_iMain);
        IO_WriteS(Tree_f, (STRING)" . ", 3L);
        Tree_WI(W_2->Name);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"           ; BEGIN", 18L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"               WNewRef := LNewNode", 34L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; LNew ^ := WNewRef", 32L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; LNew ^ . Kind := LKind", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; LNewNode . NodeNumber := yyNextNodeNumber", 56L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; INC ( yyNextNodeNumber )", 39L);
        IO_WriteNl(Tree_f);
        ConvertAttrs(t);
        IO_WriteS(Tree_f, (STRING)"             (* Field Next of Node is the builtin tail-recursion eliminated iterator *) ", 88L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; LCallerId := LId", 31L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; LCallerField := \"Next\"", 37L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; LId := Nlists . Next ( LId ) ", 44L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             ; LNew := ADR ( LNewNode . Next )", 46L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"             END (* BEGIN *) ", 29L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
}

static void ConvertAttrs
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Class:;
    {
      register Tree_yClass *W_3 = &t->U_1.V_5.Class;

      if ((Tree_NoCodeClass & W_3->Properties) == 0X0L) {
        ConvertAttrs(t->U_1.V_5.Class.BaseClass);
        if (IsDescendedFrom(t, gEntityClass)) {
          gFieldInterface = gIdentEinfo;
        } else {
          gFieldInterface = gIdentSinfo;
        }
        ConvertAttrs(t->U_1.V_5.Class.Attributes);
      }
      return;
    }
    break;
  case Tree_Child:;
    {
      register Tree_yChild *W_4 = &t->U_1.V_9.Child;

      if (W_4->Name == gIdentNext) {
        IO_WriteS(Tree_f, (STRING)"             (* Next is handled last, as tail recursion elimination *) ", 71L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"             ; yyConvert", 24L);
        Tree_WI(Tree_iMain);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                 ( ", 19L);
        WriteQualifier(W_4->Name);
        WG(W_4->Name);
        IO_WriteS(Tree_f, (STRING)" ( LId ) , ADR ( LNewNode . ", 28L);
        Tree_WI(W_4->Name);
        IO_WriteS(Tree_f, (STRING)" )", 2L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"                 , LId , \"", 26L);
        WG(W_4->Name);
        IO_WriteS(Tree_f, (STRING)"\" ) ", 4L);
        IO_WriteNl(Tree_f);
      }
      ConvertAttrs(t->U_1.V_9.Child.Next);
      return;
    }
    break;
  case Tree_Attribute:;
    {
      register Tree_yAttribute *W_5 = &t->U_1.V_10.Attribute;

      if ((Tree_NoCodeAttr & W_5->Properties) == 0X0L) {
        if (W_5->Name == gIdentNodeNumber) {
        } else if (IN(Tree_Link, W_5->Properties)) {
          IO_WriteS(Tree_f, (STRING)"             ; yyConvert", 24L);
          Tree_WI(Tree_iMain);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"                 ( ", 19L);
          WriteQualifier(W_5->Name);
          WG(W_5->Name);
          IO_WriteS(Tree_f, (STRING)" ( LId ) , ADR ( LNewNode . ", 28L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)" )", 2L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"                 , LId , \"", 26L);
          WG(W_5->Name);
          IO_WriteS(Tree_f, (STRING)"\" ) ", 4L);
          IO_WriteNl(Tree_f);
        } else {
          IO_WriteS(Tree_f, (STRING)"             ; copy", 19L);
          Tree_WI(W_5->Type);
          IO_WriteS(Tree_f, (STRING)" ( LNewNode . ", 14L);
          Tree_WI(W_5->Name);
          IO_WriteS(Tree_f, (STRING)" , ", 3L);
          WriteQualifier(W_5->Name);
          WG(W_5->Name);
          IO_WriteS(Tree_f, (STRING)" ( LId ) )", 10L);
          IO_WriteNl(Tree_f);
        }
      }
      ConvertAttrs(t->U_1.V_10.Attribute.Next);
      return;
    }
    break;
  default :
    break;
  }
}

void GenGnat_BeginGenGnat
# ifdef __STDC__
()
# else
()
# endif
{
}

void GenGnat_CloseGenGnat
# ifdef __STDC__
()
# else
()
# endif
{
}

static void yyExit
# ifdef __STDC__
()
# else
()
# endif
{
  IO_CloseIO();
  Exit(1L);
}

void GenGnat__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    Tree__init();
    System__init();
    IO__init();
    Tree__init();
    IO__init();
    Idents__init();
    Errors__init();
    Idents__init();
    Sets__init();
    Tree__init();
    Positions__init();
    Strings__init();

    GenGnat_yyf = IO_StdOutput;
    GenGnat_Exit = yyExit;
    GenGnat_BeginGenGnat();
  }
}
