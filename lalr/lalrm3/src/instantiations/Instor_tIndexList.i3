
UNSAFE INTERFACE Instor_tIndexList;

(* NOTE:  There is no such thing as an unsafe generic unit in Modula-3.
          To instantiate, we need a safe instantiating interface.
          But all the converted M3 code of Cocktail is a very tangled
          web of unsafe stuff.  We cut a piece out of this web by copying
          a minimal set of needed  type declarations from Automaton.i3
          and elsewhere, which, fortunately, all turn out safe.
*)


IMPORT Automaton;
(*
FROM SYSTEM     IMPORT SHORTCARD;
IMPORT IntSets;

(* BEWARE! The following must have not only same value sets, but same zizes
           as in the copied-from places: *)
CONST Infinite  = 65535;
      cMAXNonTerm = 2500;
TYPE
    tStateIndex = (*SHORTCARD*) [0..Infinite];
    tProdIndex  = (*SHORTCARD*) [0..Infinite];
    Vocabulary	= (*SHORTCARD*) [0..cMAXNonTerm+2];
(* END BEWARE*)

TYPE 
    tIndex      = CARDINAL;
    tItemIndex  = CARDINAL;

    tRep  = 
      {NoRep,        (* kein Repraesentant *)
       TermRep,      (* Repraesentant fuer einen Terminaluebergang *)
       NonTermRep,   (* Repraesentant fuer einen Nichtterminaluebergang *)
       RedRep};      (* Repraesentant fuer eine  Reduktion *)
     
    tItemIndexList = RECORD
        Used    : INTEGER;
        Array   : REF  ARRAY OF tItemIndex;
        Count   : INTEGER;
      END;
      
    tItem =
      RECORD
        Next    : tStateIndex;    (* Folgezustand *)
        Prod    : tProdIndex;     (* Index der Produktion *)
        Pos     : tIndex;         (* Position innerhalb der Produktion *)
        RepNo   : tItemIndex;     (* Itemindex des zug. Repraesentanten *)
        Rep     : tRep;           (* Art des Uebergans falls Repraesentant *)
        EmptyReadSet    : BOOLEAN;(* Read-Set ist leer *)
        Set     : IntSets.T;           (* DR / Read / Follow bzw Look AheadSet *)
        ReadSet : IntSets.T;           (* Read fuer Fehlerbehandlung *)
        Relation: tItemIndexList; (* reads / includes bzw. lookback *)
        Read    : Vocabulary;     (* Symbol hinter dem Punkt *)
        Number  : SHORTCARD;      (* Marke fuer Digraph *)
      END;

(*



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
*)
*)
  TYPE T = Automaton.tIndex;

  CONST Brand ="tIndexList"; 

 END Instor_tIndexList
.

