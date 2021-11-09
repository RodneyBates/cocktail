(* check and repair inconsitences *)

(* $Id: Check.md,v 1.3 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Check.md,v $
 * Revision 1.3  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.2  90/06/12  16:53:42  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.1	 89/05/02  14:34:00  vielsack
 * new option: -v (verbose)
 * 
 * Revision 1.0	 88/10/04  14:35:54  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Check;

  VAR Verbose: BOOLEAN;

  PROCEDURE CheckForConflicts (VAR ok: BOOLEAN);

  (* Pruefe ob die Zustaende Konflikte beinhalten,
     so weit moeglich werden Konflikte mit Hilfe von
     Prioritaeten und Assoziativitaeten geloest,
     falls keine Korektur moeglich ist wird ok auf FALSE gesetzt
     einer Fehlermeldung beendet, sonst steht ein konfliktfreier
     Automat zur Auswertung zur Verfuegung *)

END Check.
