(* $Id: Dfa.md,v 3.1 1991/11/21 14:41:19 grosch rel $ *)

(* $Log: Dfa.md,v $
 * Revision 3.1  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.0  91/04/04  18:06:47  grosch
 * introduced partitioning of character set
 * 
 * Revision 1.2  90/06/11  11:27:23  grosch
 * extended character range to 8 bits, ChRange -> CHAR
 * 
 * Revision 1.1  90/05/17  11:21:33  grosch
 * extend character range to 8 bits
 * 
 * Revision 1.0  88/10/04  11:59:31  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

UNSAFE INTERFACE  Dfa;

FROM SYSTEM IMPORT SHORTINT;
FROM Sets(* $$ m2tom3 warning: unable to find interface for import 'Sets' in line 26
 $$ *)	IMPORT tSet	;

CONST
   DNoState     	= 0	;
   FirstCh		= '\000'	;
   BlankCh		= ' '	;
   TabCh		= '\011'	;
   EolCh		= '\012'	;
   EobCh		= '\177'	;

TYPE DStateRange	= SHORTINT;

VAR
   LastCh		: CHAR		;
   OldLastCh		: CHAR		;
   DStateCount		: DStateRange	;
   EobState		: DStateRange	;
   EobDefaultState	: DStateRange	;
   AmbiguousStates	: tSet		;
   CyclicStates		: tSet		;
   MaxAmbiguousState	: DStateRange	;
   MinimizeSavings	: INTEGER	;
   DefaultSavings	: INTEGER	;

PROCEDURE MakeDState	(): DStateRange;
PROCEDURE GetDefault	(State: DStateRange): DStateRange;
PROCEDURE PutDefault	(State, DefaultState: DStateRange);
PROCEDURE GetDSemantics	(State: DStateRange; VAR Semantics: tSet);
PROCEDURE PutDSemantics	(State: DStateRange;     Semantics: tSet);
PROCEDURE GetStartSet	(State: DStateRange; VAR StartSet: tSet);
PROCEDURE PutStartSet	(State: DStateRange;     StartSet: tSet);
PROCEDURE GetTable	(State: DStateRange; Ch: CHAR): DStateRange;
PROCEDURE PutTable	(State: DStateRange; Ch: CHAR; NextState: DStateRange);
PROCEDURE GetTableNoDef	(State: DStateRange; Ch: CHAR): DStateRange;
PROCEDURE GetFirst	(State: DStateRange): CHAR;
PROCEDURE GetLast	(State: DStateRange): CHAR;
PROCEDURE GetEobTrans	(State: DStateRange): DStateRange;

PROCEDURE MinimizeDfa();
PROCEDURE ComputeSuccGraph();
PROCEDURE ComputeAmbiguousStates();
PROCEDURE ComputeCyclicStates();
PROCEDURE ComputeStartSets();
PROCEDURE SaveEobTransitions();
PROCEDURE ComputeDefaults (From, To: DStateRange);
PROCEDURE WriteDfa();

END Dfa.

