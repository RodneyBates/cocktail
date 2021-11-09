(* $Id: DefTable.mi,v 3.1 1991/11/21 14:41:19 grosch rel $ *)

(* $Log: DefTable.mi,v $
 * Revision 3.1  1991/11/21  14:41:19  grosch
 * fixed bug: interference of right context between constant and non-constant RE
 * new version of RCS on SPARC
 *
 * Revision 3.0  91/04/04  18:06:45  grosch
 * introduced partitioning of character set
 * 
 * Revision 1.1  91/03/26  18:26:40  grosch
 * improved generation time
 * introduced options n and o to control table size and generation time
 * increased limitation for table size from 64K to 256K
 * 
 * Revision 1.0  88/10/04  11:59:30  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Nov. 1987 *)

IMPLEMENTATION MODULE DefTable;

FROM SYSTEM	IMPORT TSIZE	;
FROM DynArray	IMPORT MakeArray, ExtendArray	;
FROM Idents	IMPORT tIdent	;
FROM Tree	IMPORT tTree	;

CONST InitialDefTableSize	= 32;

TYPE
   DefType	= RECORD
				Symbol	 	: tIdent	;
		     CASE	Kind	 	: tKind		OF
		     |  Ident:	Tree	 	: tTree		;
				LeafCount	: SHORTCARD	;
				IsConstantRE 	: BOOLEAN	;
		     |  Start:	Number	 	: SHORTCARD	;
		     END;
		  END;

   DefTable	= ARRAY [0 .. 100000] OF DefType;

VAR
   DefTablePtr	: POINTER TO DefTable;
   DefTableSize	: LONGINT;

PROCEDURE MakeIdentDef	(
	  pSymbol 	: tIdent	;
	  pTree	 	: tTree		;
	  pLeafCount	: SHORTCARD	;
	  pIsConstantRE	: BOOLEAN	);
   BEGIN
      INC (DefCount);
      IF DefCount = DefTableSize THEN
	 ExtendArray (DefTablePtr, DefTableSize, TSIZE (DefType));
      END;
      WITH DefTablePtr^[DefCount] DO
	 Symbol		:= pSymbol	;
	 Kind		:= Ident	;
	 Tree		:= pTree	;
	 LeafCount	:= pLeafCount	;
	 IsConstantRE	:= pIsConstantRE;
      END;
   END MakeIdentDef;

PROCEDURE MakeStartDef	(
          pSymbol 	: tIdent	;
          pNumber	: SHORTCARD	);
   BEGIN
      INC (DefCount);
      IF DefCount = DefTableSize THEN
	 ExtendArray (DefTablePtr, DefTableSize, TSIZE (DefType));
      END;
      WITH DefTablePtr^[DefCount] DO
	 Symbol		:= pSymbol	;
	 Kind		:= Start	;
	 Number		:= pNumber	;
      END;
   END MakeStartDef;

PROCEDURE GetDef	(
          pSymbol	: tIdent	): DefRange;
   VAR Def	: DefRange;
   BEGIN
      FOR Def := 1 TO DefCount DO
	 IF DefTablePtr^[Def].Symbol = pSymbol THEN
	    RETURN Def;
	 END;
      END;
      RETURN NoDef;
   END GetDef;

PROCEDURE GetKind	(
          pDef		: DefRange	): tKind;
   BEGIN
      RETURN DefTablePtr^[pDef].Kind;
   END GetKind;

PROCEDURE GetIdentDef	(
          pDef	 	: DefRange	;
      VAR pSymbol	: tIdent	;
      VAR pTree	 	: tTree		;
      VAR pLeafCount	: SHORTCARD	;
      VAR pIsConstantRE : BOOLEAN	);
   BEGIN
      WITH DefTablePtr^[pDef] DO
	 pSymbol	:= Symbol	;
	 pTree		:= Tree		;
	 pLeafCount	:= LeafCount	;
	 pIsConstantRE	:= IsConstantRE	;
      END;
   END GetIdentDef;

PROCEDURE GetStartDef	(
          pDef	 	: DefRange	;
      VAR pSymbol	: tIdent	;
      VAR pNumber	: SHORTCARD	);
   BEGIN
      WITH DefTablePtr^[pDef] DO
	 pSymbol	:= Symbol	;
	 pNumber	:= Number	;
      END;
   END GetStartDef;

BEGIN
   DefTableSize	:= InitialDefTableSize;
   MakeArray (DefTablePtr, DefTableSize, TSIZE (DefType));
   DefCount	:= 0;
END DefTable.
