
INTERFACE Instor_tState;

(* NOTE:  There is no such thing as an unsafe generic unit in Modula-3.
          To instantiate, we need a safe instantiating interface.
          But all the converted M3 code of Cocktail is a very tangled
          web of unsafe stuff.  We cut a piece out of this web by copying
          a minimal set of needed  type declarations from Automaton.i3,
          which, fortunately, all turn out safe.
*)

TYPE 
    tStateKind =
      {sNone,         (* nicht eingetragen *)
       sRead,         (* Read *)
       sTerm,         (* Read Terminal, Reduce *)
       sNonterm};     (* Read Nonterminal, Reduce *)
       
    tItemIndex  = CARDINAL;

    tIndex      = CARDINAL;
    
    tState =
      RECORD
        Size    : tIndex;
        Items   : tItemIndex;
        NewNumber: tIndex;
        Kind    : tStateKind;
      END;

  TYPE T = tState;

  CONST Brand ="tState"; 

 END Instor_tState
.

