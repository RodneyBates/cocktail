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
  CARDINAL pos;
  CARDINAL len;
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

CARDINAL Character_Length
# ifdef __STDC__
(CHAR c[], LONGCARD O_3)
# else
(c, O_3)
CHAR c[];
LONGCARD O_3;
# endif
{
  CARDINAL len;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_3 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(c, O_3, CHAR)
  len = 0;
  for (;;) {
    if (len > (O_3 - 1)) {
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

void Character_Assign
# ifdef __STDC__
(CHAR s1[], LONGCARD O_4, CHAR s2[], LONGCARD O_5)
# else
(s1, O_4, s2, O_5)
CHAR s1[];
LONGCARD O_4;
CHAR s2[];
LONGCARD O_5;
# endif
{
  CARDINAL i;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_5 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(s2, O_5, CHAR)
  {
    LONGCARD B_1 = 0, B_2 = Character_Length(s2, O_5);

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        s1[i] = s2[i];
        if (i >= B_2) break;
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
