#include "SYSTEM_.h"

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

WriteTok_tLanguage WriteTok_Language;
struct WriteTok_1 WriteTok_SourceFileName;



void WriteTok_GenWrTo
# ifdef __STDC__
(IO_tFile f)
# else
(f)
IO_tFile f;
# endif
{
  TokenTab_Terminal t;
  Idents_tIdent sym;
  Strings_tString s;
  TokenTab_TokenError error;
  CARDINAL l;
  CHAR del;

  {
    TokenTab_Terminal B_1 = TokenTab_MINTerm, B_2 = TokenTab_MAXTerm;

    if (B_1 <= B_2)
      for (t = B_1;; t += 1) {
        if (TokenTab_GetTokenType(t) == TokenTab_Term) {
          sym = TokenTab_TokenToSymbol(t, &error);
          Idents_GetString(sym, &s);
          if (WriteTok_Language == WriteTok_Modula2) {
            IO_WriteS(f, (STRING)"      | ", 8L);
            IO_WriteI(f, (LONGINT)t, 0L);
            IO_WriteS(f, (STRING)": Copy (", 8L);
            del = Strings_Char(&s, 1);
            if (del == '"' || del == '\'') {
              Idents_WriteIdent(f, sym);
            } else {
              IO_WriteC(f, '"');
              Idents_WriteIdent(f, sym);
              IO_WriteC(f, '"');
            }
            IO_WriteS(f, (STRING)", Name);", 8L);
            IO_WriteNl(f);
          } else {
            IO_WriteS(f, (STRING)"\"", 1L);
            if (Strings_Char(&s, 1) == '"' || Strings_Char(&s, 1) == '\'') {
              {
                LONGCARD B_3 = 2, B_4 = Strings_Length(&s) - 1;

                if (B_3 <= B_4)
                  for (l = B_3;; l += 1) {
                    if (Strings_Char(&s, (Strings_tStringIndex)l) == '\\' || Strings_Char(&s, (Strings_tStringIndex)l) == '"') {
                      IO_WriteC(f, '\\');
                    }
                    IO_WriteC(f, Strings_Char(&s, (Strings_tStringIndex)l));
                    if (l >= B_4) break;
                  }
              }
            } else {
              {
                LONGCARD B_5 = 1, B_6 = Strings_Length(&s);

                if (B_5 <= B_6)
                  for (l = B_5;; l += 1) {
                    if (Strings_Char(&s, (Strings_tStringIndex)l) == '\\' || Strings_Char(&s, (Strings_tStringIndex)l) == '"') {
                      IO_WriteC(f, '\\');
                    }
                    IO_WriteC(f, Strings_Char(&s, (Strings_tStringIndex)l));
                    if (l >= B_6) break;
                  }
              }
            }
            IO_WriteS(f, (STRING)"\",", 2L);
            IO_WriteNl(f);
          }
        } else if (WriteTok_Language == WriteTok_C) {
          IO_WriteS(f, (STRING)"0,", 2L);
          IO_WriteNl(f);
        }
        if (t >= B_2) break;
      }
  }
}

void WriteTok__init()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    IO__init();
    IO__init();
    Strings__init();
    Idents__init();
    TokenTab__init();

    WriteTok_Language = WriteTok_Modula2;
    (void)strncpy((char *)WriteTok_SourceFileName.A, " ", sizeof(WriteTok_SourceFileName.A));
  }
}
