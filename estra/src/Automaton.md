(* $Id: Automaton.md,v 2.0 1989/06/22 13:09:26 vielsack rel $ *)

DEFINITION MODULE Automaton;

FROM IO		IMPORT	tFile;
FROM Queues	IMPORT	tQueue;


PROCEDURE BeginAutomaton	(stopstates: INTEGER; MaxInput: INTEGER);
PROCEDURE DefineTransition	(path: tQueue; stop: INTEGER);
PROCEDURE CloseAutomaton	(f: tFile; VAR CombSize: INTEGER);
PROCEDURE StartIndex		(input: INTEGER): INTEGER;

(* AUTO_ *)
PROCEDURE WriteAutomaton;
PROCEDURE WriteFunction;
PROCEDURE WriteComb;
(* _AUTO *)

END Automaton.
