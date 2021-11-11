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

 UNSAFE MODULE DefTable;


FROM SYSTEM IMPORT SHORTCARD;
FROM DynArray	IMPORT MakeArray, ExtendArray	;
FROM Idents	IMPORT tIdent	;
FROM Tree	IMPORT tTree	;

CONST InitialDefTableSize	= 32;

TYPE
   DefType	= RECORD
				Symbol	 	: tIdent	;
		     	Kind	 	: tKind;		
		       	Tree	 	: tTree		;
				LeafCount	: SHORTCARD	;
				IsConstantRE 	: BOOLEAN	;
		       	Number	 	: SHORTCARD	;
		     
		  END;

   DefTable	= ARRAY [0 .. 100000] OF DefType;

VAR
   DefTablePtr	: UNTRACED BRANDED REF  DefTable;
   DefTableSize	: M2LONGINT;

PROCEDURE MakeIdentDef	(
	  pSymbol 	: tIdent	;
	  pTree	 	: tTree		;
	  pLeafCount	: SHORTCARD	;
	  pIsConstantRE	: BOOLEAN	) =
   BEGIN
      INC (DefCount);
      IF DefCount = DefTableSize THEN
	 ExtendArray (DefTablePtr, DefTableSize, BYTESIZE (DefType));
      END;
      WITH m2tom3_with_1=DefTablePtr^[DefCount] DO
	 m2tom3_with_1.Symbol		:= pSymbol	;
	 m2tom3_with_1.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 61
 $$ *)		:= tKind.Ident	;
	 m2tom3_with_1.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 62
 $$ *)		:= pTree	;
	 m2tom3_with_1.LeafCount(* $$ m2tom3 warning: application of variant field, possible cast of 'LeafCount' in line 63
 $$ *)	:= pLeafCount	;
	 m2tom3_with_1.IsConstantRE(* $$ m2tom3 warning: application of variant field, possible cast of 'IsConstantRE' in line 64
 $$ *)	:= pIsConstantRE;
      END;
   END MakeIdentDef;

PROCEDURE MakeStartDef	(
          pSymbol 	: tIdent	;
          pNumber	: SHORTCARD	) =
   BEGIN
      INC (DefCount);
      IF DefCount = DefTableSize THEN
	 ExtendArray (DefTablePtr, DefTableSize, BYTESIZE (DefType));
      END;
      WITH m2tom3_with_2=DefTablePtr^[DefCount] DO
	 m2tom3_with_2.Symbol		:= pSymbol	;
	 m2tom3_with_2.Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 78
 $$ *)		:= tKind.Start	;
	 m2tom3_with_2.Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 79
 $$ *)		:= pNumber	;
      END;
   END MakeStartDef;

PROCEDURE GetDef	(
          pSymbol	: tIdent	): DefRange =
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
          pDef		: DefRange	): tKind =
   BEGIN
      RETURN DefTablePtr^[pDef].Kind(* $$ m2tom3 warning: application of variant field, possible cast of 'Kind' in line 98
 $$ *);
   END GetKind;

PROCEDURE GetIdentDef	(
          pDef	 	: DefRange	;
      VAR pSymbol	: tIdent	;
      VAR pTree	 	: tTree		;
      VAR pLeafCount	: SHORTCARD	;
      VAR pIsConstantRE : BOOLEAN	) =
   BEGIN
      WITH m2tom3_with_3=DefTablePtr^[pDef] DO
	 pSymbol	:= m2tom3_with_3.Symbol	;
	 pTree		:= m2tom3_with_3.Tree(* $$ m2tom3 warning: application of variant field, possible cast of 'Tree' in line 110
 $$ *)		;
	 pLeafCount	:= m2tom3_with_3.LeafCount(* $$ m2tom3 warning: application of variant field, possible cast of 'LeafCount' in line 111
 $$ *)	;
	 pIsConstantRE	:= m2tom3_with_3.IsConstantRE(* $$ m2tom3 warning: application of variant field, possible cast of 'IsConstantRE' in line 112
 $$ *)	;
      END;
   END GetIdentDef;

PROCEDURE GetStartDef	(
          pDef	 	: DefRange	;
      VAR pSymbol	: tIdent	;
      VAR pNumber	: SHORTCARD	) =
   BEGIN
      WITH m2tom3_with_4=DefTablePtr^[pDef] DO
	 pSymbol	:= m2tom3_with_4.Symbol	;
	 pNumber	:= m2tom3_with_4.Number(* $$ m2tom3 warning: application of variant field, possible cast of 'Number' in line 123
 $$ *)	;
      END;
   END GetStartDef;

BEGIN
   DefTableSize	:= InitialDefTableSize;
   MakeArray (DefTablePtr, DefTableSize, BYTESIZE (DefType));
   DefCount	:= 0;
END DefTable.

