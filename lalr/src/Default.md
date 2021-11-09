(* compute default states *)

(* $Id: Default.md,v 1.2 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Default.md,v $
 * Revision 1.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/12  16:54:00  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0	 88/10/04  14:36:09  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Default;

FROM Automaton	IMPORT tStateIndex;
FROM TokenTab	IMPORT Vocabulary;
FROM Gen	IMPORT tTableLine;

VAR NoDefault : BOOLEAN;

  PROCEDURE CreateDefaultList;

  (* Erzeugen / Initialisieren der Datenstruktur zur Berechnug der Default-
     zustaende *)


  PROCEDURE PutInDefaultList 
    (	 ReadState : tStateIndex;
     VAR TableLine : tTableLine);  (* read only *)

  (* Eintragen der in TableLine enthaltenen Zeile in die Datenstruktur *)

  
  PROCEDURE ComputeDefaults;

  (* Berechnung der variablen Defaultzustaende und entfernen, der dadurch
  in der Tabelle (Datenstruktur) ueberfluessigen Eintraege *)


  PROCEDURE GetNextState
    ( State : tStateIndex) : tStateIndex;
  
  (* Funktion zum weiterschalten des Zustandes nach interner Strategie *)

  PROCEDURE GetTSortState
    ( State : tStateIndex) : tStateIndex;
  
  (* Funktion zum weiterschalten des Zustandes nach interner Strategie *)

  PROCEDURE GetNSortState
    ( State : tStateIndex) : tStateIndex;
  
  (* Funktion zum weiterschalten des Zustandes nach interner Strategie *)


  PROCEDURE GetDefaultTableLine
    (	 ReadState : tStateIndex;
     VAR TableLine : tTableLine;
     VAR Default   : tStateIndex);

  (* Auslesen der durch 'ReadState' bezeichneten Zeile aus der
     Datenstruktur *)


END Default.
