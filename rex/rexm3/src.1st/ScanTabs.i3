(* $Id: ScanTabs.md,v 3.1 1991/11/21 14:41:19 grosch rel $ *)

(* $Log: ScanTabs.md,v $
 * Revision 3.1  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.0  91/04/04  18:07:44  grosch
 * introduced partitioning of character set
 * 
 * Revision 1.3  91/03/26  18:27:13  grosch
 * improved generation time
 * introduced options n and o to control table size and generation time
 * increased limitation for table size from 64K to 256K
 * 
 * Revision 1.2  91/02/13  11:34:50  grosch
 * moved tables from file to initialization in C; reduced case size
 * 
 * Revision 1.1  90/06/11  11:27:59  grosch
 * extended character range to 8 bits, ChRange -> CHAR
 * 
 * Revision 1.0  88/10/04  11:59:46  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

UNSAFE INTERFACE  ScanTabs;

IMPORT Word;
FROM SYSTEM IMPORT M2LONGINT;
FROM SYSTEM IMPORT SHORTINT, SHORTCARD;
FROM ReuseIO	IMPORT tFile;

CONST
   NoRule	= 0	;
   NoAction	= 0	;
   EofAction	= 1	;
   EolAction	= 2	;
   EobAction	= 3	;
   TabAction	= 4	;
   CopyAction	= 5	;
   BlankAction	= 6	;

TYPE
   TableElmt	= SHORTCARD	;
   StateRange	= TableElmt	;
   RuleRange	= TableElmt	;
   RuleType	= TableElmt	;
   TableRange	= Word.T	;
   ActionType	= TableElmt	;
   ControlType	= RECORD Check, Next: TableElmt; END;

TYPE
   RuleBase	= ARRAY [0 .. 100000]	OF RuleRange	;
   Rule		= ARRAY [0 .. 100000]	OF RuleType	;
   Base		= ARRAY [0 .. 100000]	OF TableElmt	;
   Default	= ARRAY [0 .. 100000]	OF StateRange	;
   Control	= ARRAY [0 .. 100000]	OF ControlType	;
   EobTrans	= ARRAY [0 .. 100000]	OF StateRange	;
   Context	= ARRAY [0 .. 100000]	OF StateRange	;
   Action	= ARRAY [0 .. 100000]	OF ActionType	;

VAR
   RuleBasePtr	: UNTRACED BRANDED REF  RuleBase	;
   RuleBaseSize	: M2LONGINT		;
   RulePtr	: UNTRACED BRANDED REF  Rule	;
   RuleSize	: M2LONGINT		;
   BasePtr	: UNTRACED BRANDED REF  Base	;
   BaseSize	: M2LONGINT		;
   DefaultPtr	: UNTRACED BRANDED REF  Default	;
   DefaultSize	: M2LONGINT		;
   ControlPtr	: UNTRACED BRANDED REF  Control	;
   ControlSize	: M2LONGINT		;
   EobTransPtr	: UNTRACED BRANDED REF  EobTrans	;
   EobTransSize	: M2LONGINT		;
   ContextPtr	: UNTRACED BRANDED REF  Context	;
   ContextSize	: M2LONGINT		;
   ActionPtr	: UNTRACED BRANDED REF  Action	;
   ActionSize	: M2LONGINT		;

   ActionNr	: ActionType	;
   TableSize	: TableRange	;
   TableEntries	: TableRange	;

PROCEDURE MakeTables	(ReduceCaseSize: BOOLEAN);
PROCEDURE CompressTables (Optimize: SHORTINT);
(* PROCEDURE GetTables	; *)
PROCEDURE PutTables	(ReduceCaseSize: BOOLEAN);
PROCEDURE WriteTables()	;
PROCEDURE QueryTables()	;
PROCEDURE PutComb	(File: tFile);
PROCEDURE PutBase	(File: tFile);
PROCEDURE PutDefault	(File: tFile);
PROCEDURE PutEobTrans	(File: tFile);
PROCEDURE PutAction	(File: tFile);

END ScanTabs.

