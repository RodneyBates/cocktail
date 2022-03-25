(* $Id: Nfa.md,v 3.1 1991/11/21 14:41:19 grosch rel $ *) 

(* $Log: Nfa.md,v $ 
 * Revision 3.1  1991/11/21  14:41:19  grosch 
 * fixed bug: interference of right context between constant and non-constant RE 
 * new version of RCS on SPARC 
 * 
 * Revision 3.0  91/04/04  18:07:08  grosch 
 * introduced partitioning of character set 
 * 
 * Revision 1.1  91/03/26  18:26:51  grosch 
 * improved generation time 
 * introduced options n and o to control table size and generation time 
 * increased limitation for table size from 64K to 256K 
 * 
 * Revision 1.0  88/10/04  11:59:35  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *) 

UNSAFE INTERFACE Nfa 

; FROM SYSTEM IMPORT M2LONGINT 

; FROM ScanTabs IMPORT RuleType 

; CONST NoTransition = 0 

; TYPE NStateRange = M2LONGINT 
  ; TransitionRange = M2LONGINT 

; VAR NStateCount : NStateRange 
  ; TransitionCount : TransitionRange 

; PROCEDURE BeginNfa ( ) 

; PROCEDURE MakeNState ( pTransitions : TransitionRange ) : NStateRange 

; PROCEDURE PutNSemantics ( State : NStateRange ; pSemantics : RuleType ) 

; PROCEDURE GetNSemantics ( State : NStateRange ) : RuleType 

; PROCEDURE PutTransitions 
    ( State : NStateRange ; pTransition : TransitionRange ) 

; PROCEDURE GetTransitions ( State : NStateRange ) : TransitionRange 

; PROCEDURE IsLastTransition ( Transition : TransitionRange ) : BOOLEAN 

; PROCEDURE NextTransition ( Transition : TransitionRange ) : TransitionRange 

; PROCEDURE MakeTransition 
    ( pCh : CHAR ; State : NStateRange ) : TransitionRange 

; PROCEDURE AddTransition 
    ( Transition , Transitions : TransitionRange ) : TransitionRange 

; PROCEDURE GetCh ( Transition : TransitionRange ) : CHAR 

; PROCEDURE GetNextState ( Transition : TransitionRange ) : NStateRange 

; PROCEDURE UniteTransitions ( t1 , t2 : TransitionRange ) : TransitionRange 

; PROCEDURE CopyTransitions ( t1 : TransitionRange ) : TransitionRange 

; PROCEDURE WriteNfa ( ) 

; PROCEDURE FinalizeNfa ( ) 

; 
END Nfa 
. 

