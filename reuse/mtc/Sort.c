#include "SYSTEM_.h"

#ifndef DEFINITION_Sort
#include "Sort.h"
#endif


static void QuickSort ARGS((INTEGER Lwb, INTEGER Upb));


static void QuickSort
# ifdef __STDC__
(INTEGER Lwb, INTEGER Upb)
# else
(Lwb, Upb)
INTEGER Lwb, Upb;
# endif
{
  INTEGER i, j;

}

void Sort_Sort
# ifdef __STDC__
(INTEGER Lwb, INTEGER Upb, Sort_tProcIntIntBool IsLess, Sort_tProcIntInt Swap)
# else
(Lwb, Upb, IsLess, Swap)
INTEGER Lwb, Upb;
Sort_tProcIntIntBool IsLess;
Sort_tProcIntInt Swap;
# endif
{
  QuickSort(Lwb, Upb);
}

void Sort__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;


  }
}
