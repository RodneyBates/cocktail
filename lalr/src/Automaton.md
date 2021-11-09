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
 * Revision 1.1	 89/01/12  18:08:36  vielsack
 * supply a line number for each action
 * 
 * Revision 1.0	 88/10/04  14:35:49  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Automaton;
  
FROM Lists	IMPORT tList;
FROM SYSTEM	IMPORT WORD;
FROM Sets	IMPORT tSet;
FROM TokenTab	IMPORT PosType, cMAXNonTerm, Prio, Terminal, NonTerminal, Vocabulary;

CONST Infinite	= 65535;
CONST Infinite2	= 1000000;

TYPE
    tStateIndex = SHORTCARD [0..Infinite];
    tItemIndex	= LONGCARD;
    tProdIndex	= SHORTCARD [0..Infinite];
    tIndex	= LONGCARD;

    tIndexList = RECORD
	Used	: LONGINT;
	Array	: POINTER TO ARRAY [1..Infinite] OF tIndex;
	Count	: LONGINT;
      END;

    tItemIndexList = RECORD
	Used	: LONGINT;
	Array	: POINTER TO ARRAY [1..Infinite] OF tItemIndex;
	Count	: LONGINT;
      END;

    tProdListElmt = RECORD
	Index	: tProdIndex;
	Value	: SHORTCARD;
      END;

    tProdIndexList = RECORD
	Used	: LONGINT;
	Array	: POINTER TO ARRAY [1..Infinite] OF tProdListElmt;
	Count	: LONGINT;
      END;

    tAss = (right,left,none,nonassoc);

    tOper = RECORD
      Pri	: Prio;
      Ass	: tAss;
    END;

    (*****************************)
    (*	 A C H T U N G !!	 *)
    (*				 *)
    (* tProduction muss zu	 *)
    (* tDummyProduction und	 *)
    (* tRigth4 im		 *)
    (* Implementationteil passen *)
    (*****************************)

    tProduction =
      POINTER TO RECORD
	ProdNo	: tIndex;
	Reduce	: tIndexList;
	Act	: tList;
	ActPos	: PosType;
	Ass	: tAss;
	Pri	: Prio;
	Len	: tIndex;
	Left	: NonTerminal;
	Right	: ARRAY [1..Infinite] OF SHORTCARD [0..cMAXNonTerm];
      END;

    tRep  = 
      (NoRep,	     (* kein Repraesentant *)
       TermRep,	     (* Repraesentant fuer einen Terminaluebergang *)
       NonTermRep,   (* Repraesentant fuer einen Nichtterminaluebergang *)
       RedRep);	     (* Repraesentant fuer eine	 Reduktion *)
     
    tStateKind =
      (sNone,	      (* nicht eingetragen *)
       sRead,	      (* Read *)
       sTerm,	      (* Read Terminal, Reduce *)
       sNonterm);     (* Read Nonterminal, Reduce *)

    tItem =
      RECORD
	Next	: tStateIndex;	  (* Folgezustand *)
	Prod	: tProdIndex;	  (* Index der Produktion *)
	Pos	: tIndex;	  (* Position innerhalb der Produktion *)
	RepNo	: tItemIndex;	  (* Itemindex des zug. Repraesentanten *)
	Rep	: tRep;		  (* Art des Uebergans falls Repraesentant *)
	EmptyReadSet	: BOOLEAN;(* Read-Set ist leer *)
	Set	: tSet;		  (* DR / Read / Follow bzw Look AheadSet *)
	ReadSet : tSet;	     	  (* Read fuer Fehlerbehandlung *)
	Relation: tItemIndexList; (* reads / includes bzw. lookback *)
	Read	: Vocabulary;	  (* Symbol hinter dem Punkt *)
	Number	: SHORTCARD;	  (* Marke fuer Digraph *)
      END;
    
    tState =
      RECORD
	Size	: tIndex;
	Items	: tItemIndex;
	NewNumber: tIndex;
	Kind	: tStateKind;
      END;
    
VAR
    IsBnf	: BOOLEAN;
    ProdArrayPtr: POINTER TO ARRAY    (* alle Produktionen *)
		     tProdIndex OF WORD;
    ProdIndex	: LONGINT;	      (* Index akt. bzw naechste P. *)
    ProdCount	: CARDINAL;	      (* Anzahl Produktionen *)
    ItemArrayPtr: POINTER TO ARRAY    (* alle Items *)
		     [1..Infinite2] OF tItem;
    ItemIndex	: LONGINT;	      (* Index akt. bzw. naechstes I *)
    StateArrayPtr: POINTER TO ARRAY    (* alle States *)
		     [1..Infinite] OF tState;
    StateIndex	: LONGINT;	      (* Index akt. bzw. naechste S. *)
    ProdList	: ARRAY		      (* enthaelt Liste von Produk- *)
		     NonTerminal OF	 (* tionen mit gleicher linken *)
		     tProdIndexList;	     (* Seite *)
    OperArray	: ARRAY Terminal OF tOper;
    StartSymbol : NonTerminal;	      (* neues Startsymbol, das nur in
					    einer Regel auftritt *)

PROCEDURE InitAutomaton;

  (* Zur Initialisierung werden die Produktionen vom Module Rules
     eingelesen, hierbei wird (nebenbei) geprueft ob es sich nur 
     um BNF hendelt (IsBnf wird entsprechend gesetzt). Es wird geprueft
     ob die Regeln semantische Ankopplungen besitzen, die nicht am
     Ende der Regel stehen. Falls dies der Fall ist werden die 
     Regeln entspechend zerlegt *)

PROCEDURE MakeFirstState (): tStateIndex;

  (* Der erste Zustand wird gebildet und sein Index zurueckgegeben *)
     
PROCEDURE GotoSet (i: tStateIndex; VAR s: tSet);

  (* Es wird die Menge der Vocabularzeichen 's' bestimmt fuer die ein
     von Zustand 'i' ein Folgezustand besteht *)

PROCEDURE Goto (i: tStateIndex; s: Vocabulary; VAR new: BOOLEAN): tStateIndex;

  (* Der Folgezustand von Zustand 'i' bei Eingabe 's' wird gebildet
     'new' gibt an ob es sich dabei um einen neuen Zustand handel,
     der zum ersten mal gebildet wurde *)

PROCEDURE NextProdIndex (Index: tProdIndex): tProdIndex;

  (* liefert den naechsten naechst groesseren ProdIndex *)

END Automaton.
