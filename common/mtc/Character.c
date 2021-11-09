#include "SYSTEM_.h"

#ifndef DEFINITION_Character
#include "Character.h"
#endif




BOOLEAN Character_IsEqual
# ifdef __STDC__
(CHAR c1[], LONGCARD O_2, CHAR c2[], LONGCARD O_1)
# else
(c1, O_2, c2, O_1)
CHAR c1[];
LONGCARD O_2;
CHAR c2[];
LONGCARD O_1;
# endif
{
  INTEGER pos;
  INTEGER len;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR) + O_2 * sizeof(CHAR), 2)
  COPY_OPEN_ARRAY(c2, O_1, CHAR)
  COPY_OPEN_ARRAY(c1, O_2, CHAR)
  pos = 0;
  len = Character_Length(c1, O_2);
  if (len != Character_Length(c2, O_1)) {
    FREE_OPEN_ARRAYS
    return FALSE;
  }
  pos = 0;
  for (;;) {
    if (pos >= len) {
      goto EXIT_1;
    }
    if (c1[pos] != c2[pos]) {
      goto EXIT_1;
    }
    INC(pos);
  } EXIT_1:;
  FREE_OPEN_ARRAYS
  return pos == len;
}

INTEGER Character_Length
# ifdef __STDC__
(CHAR c[], LONGCARD O_3)
# else
(c, O_3)
CHAR c[];
LONGCARD O_3;
# endif
{
  INTEGER len;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(c, O_3, CHAR)
  len = 0;
  for (;;) {
    if (len > (INTEGER)(O_3 - 1)) {
      goto EXIT_2;
    }
    if (c[len] == '\0') {
      goto EXIT_2;
    }
    INC(len);
  } EXIT_2:;
  FREE_OPEN_ARRAYS
  return len;
}

CHAR Character_Char
# ifdef __STDC__
(CHAR s[], LONGCARD O_4, INTEGER i)
# else
(s, O_4, i)
CHAR s[];
LONGCARD O_4;
INTEGER i;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_4 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s, O_4, CHAR)
  {
    CHAR R_1 = s[i - 1];

    FREE_OPEN_ARRAYS
    return R_1;
  }
}

void Character_Append
# ifdef __STDC__
(CHAR s[], LONGCARD O_5, CHAR c)
# else
(s, O_5, c)
CHAR s[];
LONGCARD O_5;
CHAR c;
# endif
{
  INTEGER l;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_5 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s, O_5, CHAR)
  l = Character_Length(s, O_5);
  s[l] = c;
  s[l + 1] = '\0';
  FREE_OPEN_ARRAYS
}

void Character_Concatenate
# ifdef __STDC__
(CHAR s1[], LONGCARD O_6, CHAR s2[], LONGCARD O_7)
# else
(s1, O_6, s2, O_7)
CHAR s1[];
LONGCARD O_6;
CHAR s2[];
LONGCARD O_7;
# endif
{
  INTEGER l1, l2;
  INTEGER i1, i2;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_7 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s2, O_7, CHAR)
  l1 = Character_Length(s1, O_6);
  l2 = Character_Length(s2, O_7);
  if (l1 + l2 > (INTEGER)(O_6 - 1) + 1) {
    l2 = (INTEGER)(O_6 - 1) + 1 - l1;
  }
  i1 = l1;
  {
    LONGINT B_1 = 0, B_2 = l2 - 1;

    if (B_1 <= B_2)
      for (i2 = B_1;; i2 += 1) {
        s1[i1] = s2[i2];
        INC(i1);
        if (i2 >= B_2) break;
      }
  }
  if (i1 <= (INTEGER)(O_6 - 1)) {
    s1[i1] = '\0';
  }
  FREE_OPEN_ARRAYS
}

void Character_SubString
# ifdef __STDC__
(CHAR s1[], LONGCARD O_9, INTEGER from, INTEGER to, CHAR s2[], LONGCARD O_8)
# else
(s1, O_9, from, to, s2, O_8)
CHAR s1[];
LONGCARD O_9;
INTEGER from, to;
CHAR s2[];
LONGCARD O_8;
# endif
{
  INTEGER i;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_9 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s1, O_9, CHAR)
  {
    LONGINT B_3 = from - 1, B_4 = to - 1;

    if (B_3 <= B_4)
      for (i = B_3;; i += 1) {
        s2[i - from + 1] = s1[i];
        if (i >= B_4) break;
      }
  }
  s2[to] = '\0';
  FREE_OPEN_ARRAYS
}

void Character_Assign
# ifdef __STDC__
(CHAR s1[], LONGCARD O_10, CHAR s2[], LONGCARD O_11)
# else
(s1, O_10, s2, O_11)
CHAR s1[];
LONGCARD O_10;
CHAR s2[];
LONGCARD O_11;
# endif
{
  INTEGER i;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_11 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s2, O_11, CHAR)
  {
    LONGINT B_5 = 0, B_6 = Character_Length(s2, O_11);

    if (B_5 <= B_6)
      for (i = B_5;; i += 1) {
        s1[i] = s2[i];
        if (i >= B_6) break;
      }
  }
  FREE_OPEN_ARRAYS
}

void Character__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;


  }
}
