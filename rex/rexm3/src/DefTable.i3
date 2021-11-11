(* $Id: DefTable.md,v 3.1 1991/11/21 14:41:19 grosch rel $ *)

(* $Log: DefTable.md,v $
 * Revision 3.1  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.0  91/04/04  18:06:40  grosch
 * introduced partitioning of character set
 * 
 * Revision 1.0  88/10/04  11:59:29  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

UNSAFE INTERFACE  DefTable;

FROM SYSTEM IMPORT SHORTCARD;
FROM Idents	IMPORT tIdent	;
FROM Tree	IMPORT tTree	;

CONST
   NoDef	= 0	;

TYPE
   DefRange	= M2LONGINT;
   tKind	= {NoKind, Ident, Start};

VAR
   DefCount	: DefRange;

PROCEDURE MakeIdentDef	(
          pIdent	: tIdent	;
          pTree	 	: tTree		;
          pLeafCount	: SHORTCARD	;
          pIsConstantRE : BOOLEAN	);

PROCEDURE MakeStartDef	(
          pIdent	: tIdent	;
          pNumber	: SHORTCARD	);

PROCEDURE GetDef	(
          pIdent	: tIdent	): DefRange;

PROCEDURE GetKind	(
          pDef		: DefRange	): tKind;

PROCEDURE GetIdentDef	(
          pDef	 	: DefRange	;
      VAR pIdent	: tIdent	;
      VAR pTree	 	: tTree		;
      VAR pLeafCount	: SHORTCARD	;
      VAR pIsConstantRE : BOOLEAN	);

PROCEDURE GetStartDef	(
          pDef	 	: DefRange	;
      VAR pIdent	: tIdent	;
      VAR pNumber	: SHORTCARD	);

END DefTable.

