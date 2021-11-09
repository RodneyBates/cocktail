(* $Id: GenTabs.md,v 3.2 1992/08/07 15:10:26 grosch rel $ *)

(* $Log: GenTabs.md,v $
 * Revision 3.2  1992/08/07  15:10:26  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 3.1  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.0  91/04/04  18:06:58  grosch
 * introduced partitioning of character set
 * 
 * Revision 2.1  91/03/26  18:26:45  grosch
 * improved generation time
 * introduced options n and o to control table size and generation time
 * increased limitation for table size from 64K to 256K
 * 
 * Revision 2.0  91/03/08  18:17:44  grosch
 * turned tables into initialized arrays (in C)
 * reduced case size
 * changed interface for source position
 * 
 * Revision 1.4  91/02/13  11:34:33  grosch
 * moved tables from file to initialization in C; reduced case size
 * 
 * Revision 1.3  89/11/06  12:38:35  grosch
 * renamed module Rex to GenTabs to avoid name clash with rex under VMS
 * 
 * Revision 1.2  89/02/23  15:55:30  grosch
 * added completeness check for the automaton
 * improved handling of right context
 * 
 * Revision 1.1  89/01/17  15:01:13  grosch
 * correction and redesign of source position handling
 * 
 * Revision 1.0  88/10/04  11:59:39  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

UNSAFE INTERFACE  GenTabs;

FROM SYSTEM IMPORT SHORTINT, SHORTCARD;
FROM Tree	IMPORT tTree	;
FROM Texts	IMPORT tText	;
FROM Sets	IMPORT tSet	;
FROM Positions	IMPORT tPosition;

CONST
   NoContext		= 0	;
   VariableContext	= 9999	;

TYPE
   PatternInfo		= RECORD
   			     Position	: tPosition	;
   			     Rule	: SHORTCARD	;
			     ContextLng	: SHORTINT	;
			     NContext	: tSet		;
			     DContext	: tSet		;
   			     Finals	: tSet		;
			  END;

   CodeInfo		= RECORD
			     Text	: tText		;
			     TextLine	: SHORTCARD	;
			     CodeMode	: SHORTCARD	;
			  END;

   PatternTable		= ARRAY [0 .. 100000] OF PatternInfo	;
   RuleToCode		= ARRAY [0 .. 100000] OF CodeInfo	;

VAR
   Root			: tTree		;
   NodeCount		,
   StartStateCount	: SHORTINT	;
   RuleCount		,
   PatternCount		,
   LeafCount		: SHORTCARD	;
   LeftJustUsed		: BOOLEAN	;
   EobAction		,
   DefaultAction	: SHORTCARD	;
   PatternTablePtr	: UNTRACED BRANDED REF  PatternTable;
   PatternTableSize	: LONGINT	;
   RuleToCodePtr	: UNTRACED BRANDED REF  RuleToCode;
   RuleToCodeSize	: LONGINT	;

PROCEDURE GenerateTables (DebugLevel: SHORTCARD; ReduceCaseSize, Warnings: BOOLEAN; Optimize: SHORTINT);

END GenTabs.

