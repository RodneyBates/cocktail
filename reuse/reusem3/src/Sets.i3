(* $Id: Sets.md,v 1.4 1991/11/21 14:33:17 grosch rel $ *)

(* $Log: Sets.md,v $

 * RMB July 98 Documentation/name changes. 

 * RMB 97/06/05 Added InitNullSet, since some tree dumps call
                WriteSet for sets which are not in use and need
                no allocated array. 

 * RMB 93/10/12 Regularized types to compile with WRL.

 * Revision 1.4  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.3  91/09/18  15:09:49  grosch
 * reduced size of set type
 * 
 * Revision 1.2  91/06/07  11:37:49  grosch
 * increased bounds of flexible arrays
 * 
 * Revision 1.1  89/01/09  17:13:03  grosch
 * added functions Size, Minimum, and Maximum
 * 
 * Revision 1.0  88/10/04  11:47:12  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

UNSAFE INTERFACE  Sets;

FROM SYSTEM IMPORT BITSET, SHORTCARD;
FROM ReuseIO IMPORT tFile;

TYPE
   tInternalElmt        = SHORTCARD;
   (* ^ Change this only, for different range of elements. *)
   tElement             = [ 0 .. LAST ( tInternalElmt ) - 1 ];
   ArrayOfBitset	= ARRAY [0 .. LAST ( SHORTCARD ) ] OF BITSET;
   ProcOftElement		= PROCEDURE (p0: tElement);
   ProcOftElementToBool	= PROCEDURE (p0: tElement): BOOLEAN;

   tSet = RECORD
      BitsetPtr		: UNTRACED BRANDED REF  ArrayOfBitset;
      LastBitset	: SHORTCARD;
      MaxElmt		: tInternalElmt;
      Card		: tInternalElmt;
      FirstElmt		: tInternalElmt;
      LastElmt		: tInternalElmt;
   END;

PROCEDURE InitNullSet   ( VAR Set : tSet ) ; 
PROCEDURE MakeSet	(VAR Set: tSet; MaxElement: tElement);
PROCEDURE ReleaseSet	(VAR Set: tSet);
PROCEDURE Union		(VAR Set1: tSet; Set2: tSet);
PROCEDURE Difference	(VAR Set1: tSet; Set2: tSet);
PROCEDURE Intersection	(VAR Set1: tSet; Set2: tSet);
PROCEDURE SymDiff	(VAR Set1: tSet; Set2: tSet);
PROCEDURE Complement	(VAR Set: tSet);
PROCEDURE Include	(VAR Set: tSet; Elmt: tElement);
PROCEDURE Exclude	(VAR Set: tSet; Elmt: tElement);
PROCEDURE Card		(VAR Set: tSet): tElement;
PROCEDURE Size		(VAR Set: tSet): tElement;
PROCEDURE Minimum	(VAR Set: tSet): tElement;
PROCEDURE Maximum	(VAR Set: tSet): tElement;
PROCEDURE Select	(VAR Set: tSet): tElement;
PROCEDURE Extract	(VAR Set: tSet): tElement;
PROCEDURE IsSubset	(Set1, Set2: tSet): BOOLEAN;
PROCEDURE IsStrictSubset (Set1, Set2: tSet): BOOLEAN;
PROCEDURE IsEqual	(VAR Set1, Set2: tSet): BOOLEAN;
PROCEDURE IsNotEqual	(Set1, Set2: tSet): BOOLEAN;
PROCEDURE IsElement	(Elmt: tElement; VAR Set: tSet): BOOLEAN;
PROCEDURE IsEmpty	(Set: tSet): BOOLEAN;
PROCEDURE Forall	(Set: tSet; Proc: ProcOftElementToBool): BOOLEAN;
PROCEDURE Exists	(Set: tSet; Proc: ProcOftElementToBool): BOOLEAN;
PROCEDURE Exists1	(Set: tSet; Proc: ProcOftElementToBool): BOOLEAN;
PROCEDURE Assign	(VAR Set1: tSet; Set2: tSet);
PROCEDURE AssignElmt	(VAR Set: tSet; Elmt: tElement); (* Singleton *)
PROCEDURE AssignEmpty	(VAR Set: tSet);
PROCEDURE ForallDo	(Set: tSet; Proc: ProcOftElement);
PROCEDURE ReadSet	(f: tFile; VAR Set: tSet);
PROCEDURE WriteSet	(f: tFile;     Set: tSet);

END Sets.



