(* compute debugging information *)

(* 2001-02-15, Rodney M. Bates Added ItemSets and PrintItemSets. *) 

(* $Id: Debug.md,v 1.4 1992/09/24 13:12:31 grosch rel $ *)

(* $Log: Debug.md,v $
 * Revision 1.4  1992/09/24  13:12:31  grosch
 * added option -f
 *
 * Revision 1.3  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/12  16:53:52  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.1  89/05/02  14:35:09  vielsack
 * new option: -v (verbose)
 * NoTrace is used instead of NoDebug
 * 
 * Revision 1.0  88/10/04  14:36:03  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  Debug;

IMPORT Word;

FROM ReuseIO IMPORT tFile;
IMPORT IntSets;
FROM Automaton IMPORT tItemIndex, tStateIndex, tProdIndex, tIndex;
FROM TokenTab IMPORT Terminal, Vocabulary;

TYPE tConflict = {ShRed, RedRed, ShRedRed};

VAR
  NoTrace, Fast, ItemSets       : BOOLEAN;
  dFile         : tFile;

PROCEDURE DebugHead     (State: tStateIndex);
PROCEDURE DebugState    (State: tStateIndex; VAR Set: IntSets.T);
PROCEDURE DebugEnd();

PROCEDURE WriteItemSets ( ) ; 
PROCEDURE WriteProd (p: tProdIndex; l: tIndex; VAR d: Word.T);
PROCEDURE WriteTable();
PROCEDURE WriteProdLength();
PROCEDURE WriteLeftHandSide();
PROCEDURE WriteVoc (voc: Vocabulary; VAR (*OUT*)length: Word.T);
    
(* Erzeuge Zusatzinformation zum Zustand 'State' mit Konfliktmenge 'Set' *)

PROCEDURE InformIgnored (Item: tItemIndex; t: Terminal);
PROCEDURE InformLowPri  (Item: tItemIndex; t: Terminal);
PROCEDURE InformLeftAss (Item: tItemIndex; t: Terminal);
PROCEDURE InformRightAss(Item: tItemIndex; t: Terminal);
PROCEDURE InformKept    (Item: tItemIndex; t: Terminal);
PROCEDURE InformConflict(kind: tConflict);
PROCEDURE NewLine();

END Debug.

