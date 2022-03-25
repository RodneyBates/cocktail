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


FROM SYSTEM IMPORT M2LONGINT;
FROM SYSTEM IMPORT SHORTCARD;
FROM DynArray   IMPORT MakeArray, ExtendArray   ;
FROM Idents     IMPORT tIdent   ;
FROM Tree       IMPORT tTree    ;

CONST InitialDefTableSize       = 32;

TYPE
   DefType      = RECORD
                                Symbol          : tIdent        ;
                        Kind            : tKind;                
                        Tree            : tTree         ;
                                LeafCount       : SHORTCARD     ;
                                IsConstantRE    : BOOLEAN       ;
                        Number          : SHORTCARD     ;
                     
                  END;

   DefTable     = ARRAY [0 .. 100000] OF DefType;

VAR
   DefTablePtr  : UNTRACED BRANDED REF  DefTable;
   DefTableSize : M2LONGINT;

PROCEDURE MakeIdentDef  (
          pSymbol       : tIdent        ;
          pTree         : tTree         ;
          pLeafCount    : SHORTCARD     ;
          pIsConstantRE : BOOLEAN       ) =
   BEGIN
      INC (DefCount);
      IF DefCount = DefTableSize THEN
         ExtendArray (LOOPHOLE(DefTablePtr,ADDRESS), DefTableSize, BYTESIZE (DefType));
      END;
      WITH With_1=DefTablePtr^[DefCount] DO
         With_1.Symbol           := pSymbol      ;
         With_1.Kind          := tKind.Ident  ;
         With_1.Tree          := pTree        ;
         With_1.LeafCount  := pLeafCount   ;
         With_1.IsConstantRE  := pIsConstantRE;
      END;
   END MakeIdentDef;

PROCEDURE MakeStartDef  (
          pSymbol       : tIdent        ;
          pNumber       : SHORTCARD     ) =
   BEGIN
      INC (DefCount);
      IF DefCount = DefTableSize THEN
         ExtendArray (LOOPHOLE(DefTablePtr,ADDRESS), DefTableSize, BYTESIZE (DefType));
      END;
      WITH With_2=DefTablePtr^[DefCount] DO
         With_2.Symbol           := pSymbol      ;
         With_2.Kind          := tKind.Start  ;
         With_2.Number          := pNumber      ;
      END;
   END MakeStartDef;

PROCEDURE GetDef        (
          pSymbol       : tIdent        ): DefRange =
   BEGIN
      FOR Def := 1 TO DefCount DO
         IF DefTablePtr^[Def].Symbol = pSymbol THEN
            RETURN Def;
         END;
      END;
      RETURN NoDef;
   END GetDef;

PROCEDURE GetKind       (
          pDef          : DefRange      ): tKind =
   BEGIN
      RETURN DefTablePtr^[pDef].Kind;
   END GetKind;

PROCEDURE GetIdentDef   (
          pDef          : DefRange      ;
      VAR pSymbol       : tIdent        ;
      VAR pTree         : tTree         ;
      VAR pLeafCount    : SHORTCARD     ;
      VAR pIsConstantRE : BOOLEAN       ) =
   BEGIN
      WITH With_3=DefTablePtr^[pDef] DO
         pSymbol        := With_3.Symbol ;
         pTree          := With_3.Tree          ;
         pLeafCount     := With_3.LeafCount  ;
         pIsConstantRE  := With_3.IsConstantRE  ;
      END;
   END GetIdentDef;

PROCEDURE GetStartDef   (
          pDef          : DefRange      ;
      VAR pSymbol       : tIdent        ;
      VAR pNumber       : SHORTCARD     ) =
   BEGIN
      WITH With_4=DefTablePtr^[pDef] DO
         pSymbol        := With_4.Symbol ;
         pNumber        := With_4.Number  ;
      END;
   END GetStartDef;

BEGIN
   DefTableSize := InitialDefTableSize;
   MakeArray (LOOPHOLE(DefTablePtr,ADDRESS), DefTableSize, BYTESIZE (DefType));
   DefCount     := 0;
END DefTable.

