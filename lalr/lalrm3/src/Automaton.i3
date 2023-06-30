(* handle LR automaton *)

(* $Id: Automaton.md,v 1.4 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Automaton.md,v $
 * Revision 1.4  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.3  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/12  16:53:35  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.1  89/01/12  18:08:36  vielsack
 * supply a line number for each action
 * 
 * Revision 1.0  88/10/04  14:35:49  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  Automaton;
  
IMPORT Word;
FROM Lists      IMPORT tList;
FROM SYSTEM     IMPORT SHORTCARD;
IMPORT IntSets;
FROM TokenTab   IMPORT PosType, cMAXNonTerm, Prio, Terminal, NonTerminal, Vocabulary;

CONST Infinite  = 65535;
CONST Infinite2 = 1000000;

TYPE
    tStateIndex = (*SHORTCARD*) [0..Infinite];
    tItemIndex  = CARDINAL;
    tProdIndex  = (*SHORTCARD*) [0..Infinite];
    tIndex      = CARDINAL;

    tIndexList = RECORD
        Used    : INTEGER;
        IlArray   : REF  ARRAY OF tIndex;
(* TODO: replace Count by NUMBER ( Array^) *)
        Count   : INTEGER;
      END;

    tItemIndexList = RECORD
        Used    : INTEGER;
        Array   : REF  ARRAY OF tItemIndex;
        Count   : INTEGER;
      END;

    tProdListElmt = RECORD
        Index   : tProdIndex;
        Value   : INTEGER;
      END;

    tProdListArrayRef = REF ARRAY OF tProdListElmt;

    tProdIndexList = RECORD
        Used    : INTEGER;
        Array   : tProdListArrayRef;
(* TODO: replace Count by NUMBER ( Array^) *)
        Count   : INTEGER;
      END;

    tAss = {right,left,none,nonassoc};

    tOper = RECORD
      Pri       : Prio;
      Ass       : tAss;
    END;

    (*****************************)
    (*   A C H T U N G !!        *)
    (*                           *)
    (* tProduction muss zu       *)
    (* tDummyProduction und      *)
    (* tRigth4 im                *)
    (* Implementationteil passen *)
    (*****************************)

    tProduction =
      UNTRACED REF  RECORD
        ProdNo  : tIndex;
        Reduce  : tIndexList;
        Act     : tList;
        ActPos  : PosType;
        Ass     : tAss;
        Pri     : Prio;
        Len     : tIndex;
        Left    : NonTerminal;
        Right   : ARRAY [0 .. Infinite]
                  OF BITS BITSIZE (SHORTCARD) FOR [0..cMAXNonTerm];
      END;

    tRep  = 
      {NoRep,        (* kein Repraesentant *)
       TermRep,      (* Repraesentant fuer einen Terminaluebergang *)
       NonTermRep,   (* Repraesentant fuer einen Nichtterminaluebergang *)
       RedRep};      (* Repraesentant fuer eine  Reduktion *)
     
    tStateKind =
      {sNone,         (* nicht eingetragen *)
       sRead,         (* Read *)
       sTerm,         (* Read Terminal, Reduce *)
       sNonterm};     (* Read Nonterminal, Reduce *)

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
    
    tState =
      RECORD
        Size    : tIndex;
        Items   : tItemIndex;
        NewNumber: tIndex;
        Kind    : tStateKind;
      END;

    tWordArrayRef = REF ARRAY OF Word.T;
    
VAR
    IsBnf       : BOOLEAN;
    ProdArrayPtr: tWordArrayRef (*tProdIndex*) (* alle Produktionen *);
    ProdIndex   : INTEGER;            (* Index akt. bzw naechste P. *)
    ProdCount   : Word.T;             (* Anzahl Produktionen *)
    ItemArrayPtr: REF  ARRAY    (* alle Items *) OF tItem;
    ItemIndex   : INTEGER;            (* Index akt. bzw. naechstes I *)
    StateArrayPtr: REF  ARRAY    (* alle States *)
                     OF tState;
    StateIndex  : INTEGER;            (* Index akt. bzw. naechste S. *)
    ProdList    : ARRAY               (* enthaelt Liste von Produk- *)
                     NonTerminal OF      (* tionen mit gleicher linken *)
                     tProdIndexList;         (* Seite *)
    OperArray   : ARRAY Terminal OF tOper;
    StartSymbol : NonTerminal;        (* neues Startsymbol, das nur in
                                            einer Regel auftritt *)

PROCEDURE InitAutomaton();

  (* Zur Initialisierung werden die Produktionen vom Module Rules
     eingelesen, hierbei wird (nebenbei) geprueft ob es sich nur 
     um BNF hendelt (IsBnf wird entsprechend gesetzt). Es wird geprueft
     ob die Regeln semantische Ankopplungen besitzen, die nicht am
     Ende der Regel stehen. Falls dies der Fall ist werden die 
     Regeln entspechend zerlegt *)

PROCEDURE MakeFirstState (): tStateIndex;

  (* Der erste Zustand wird gebildet und sein Index zurueckgegeben *)
     
PROCEDURE GotoSet (i: tStateIndex; VAR s: IntSets.T);

  (* Es wird die Menge der Vocabularzeichen 's' bestimmt fuer die ein
     von Zustand 'i' ein Folgezustand besteht *)

PROCEDURE Goto (i: tStateIndex; s: Vocabulary; VAR new: BOOLEAN): tStateIndex;

  (* Der Folgezustand von Zustand 'i' bei Eingabe 's' wird gebildet
     'new' gibt an ob es sich dabei um einen neuen Zustand handel,
     der zum ersten mal gebildet wurde *)

PROCEDURE NextProdIndex (Index: tProdIndex): tProdIndex;

  (* liefert den naechsten naechst groesseren ProdIndex *)

END Automaton.

