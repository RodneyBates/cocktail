/* swap all word pairs of a file */

# include <stdio.h>

main () {
   short w1, w2, n;
   
   for (;;) {
      n = fread (& w1, 2, 1, stdin);
      n = fread (& w2, 2, 1, stdin);
      if (! n) break;
      fwrite (& w2, 2, 1, stdout);
      fwrite (& w1, 2, 1, stdout);
   }
   return 0;
}
