(* $Id: Memory.mi,v 1.8 1992/06/24 12:25:33 grosch rel $ *)

(* $Log: Memory.mi,v $

 * RMB 93/10/12 Various type conversions.

 * Revision 1.8  1992/06/24  12:25:33  grosch
 * changed cNoMoreSpace from -1 to 0
 *
 * Revision 1.7  1992/03/24  13:31:43  grosch
 * suppress warning message during compilation of C version
 *
 * Revision 1.6  1992/01/30  13:23:29  grosch
 * redesign of interface to operating system
 *
 * Revision 1.5  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.4  90/12/19  11:36:26  grosch
 * inlined procedure PoolAlloc
 * 
 * Revision 1.3  90/03/02  17:36:07  grosch
 * automized handling of machine independent alignment
 * 
 * Revision 1.2  90/02/28  22:07:02  grosch
 * comment for alignment on SPARC
 * 
 * Revision 1.1  89/12/08  20:12:45  grosch
 * introduced a machine dependent variant for MIPS
 * 
 * Revision 1.0  88/10/04  11:47:11  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Juli 1986 *)

 UNSAFE MODULE Memory;


FROM SYSTEM IMPORT M3LONGINT, M3LONGCARD;
FROM SYSTEM IMPORT BITSET;
IMPORT Word;
FROM General	IMPORT Log2, MaxAlign, AlignMasks;
FROM System	IMPORT SysAlloc;
(* FROM IO	IMPORT StdOutput, WriteI, WriteC, WriteN, WriteS, WriteNl; *)

CONST
   MinSizeSmallBlock	= 4	;
   MaxSizeSmallBlock	= 62	;   (* 64 - 2     *)
   MinSizeLargeBlockLog	= 6	;   (* Log2 64    *)
   MaxSizeLargeBlockLog = 24	;   (* Log2 2**24 *)
   PoolSize		= 10240	;

TYPE
   tBlockPtr		= UNTRACED BRANDED REF  tBlock;
   tBlock		= RECORD
			     Successor	: tBlockPtr	;
			     Size	: M3LONGINT	;
			  END;
   tSmallBlockRange	= [MinSizeSmallBlock    .. MaxSizeSmallBlock   ];
   tLargeBlockRange	= [MinSizeLargeBlockLog .. MaxSizeLargeBlockLog];

VAR
   SmallChain	: ARRAY tSmallBlockRange OF ADDRESS;
   LargeChain	: ARRAY tLargeBlockRange OF ADDRESS;
   PoolFreePtr	: ADDRESS;
   PoolEndPtr	: ADDRESS;
   i		: tSmallBlockRange;
   j		: tLargeBlockRange;

(* Returns a pointer to dynamically allocated	*)
(* space of size 'ByteCount' bytes.		*)

PROCEDURE Alloc	(ByteCount: M3LONGINT)		: ADDRESS =
VAR
   BlockPtr		,
   CurrentBlock		,
   PreviousBlock	,
   BestBlock		,
   PredecessorBlock	: tBlockPtr;
   ChainNumber		: Word.T;
   CurrentBlockSize	,
   BestBlockSize	: M3LONGINT;
   j			: tLargeBlockRange;
BEGIN
   ByteCount 
     := LOOPHOLE 
          (LOOPHOLE (ByteCount + VAL (   MaxAlign,M3LONGINT ) - 1,BITSET) 
           * AlignMasks [MaxAlign]
          ,M3LONGINT);

   IF ByteCount <= MaxSizeSmallBlock THEN	(* handle small block *)
      IF ByteCount < MinSizeSmallBlock THEN ByteCount := MinSizeSmallBlock; END;
      IF SmallChain [ VAL (   ByteCount,tSmallBlockRange ) ] # NIL 
      THEN	(* obtain block from freelist *)
	 BlockPtr := SmallChain [ VAL (   ByteCount,tSmallBlockRange ) ];
	 SmallChain [ VAL (   ByteCount,tSmallBlockRange ) ] 
           := BlockPtr^.Successor;
	 RETURN BlockPtr;
      ELSE (* obtain block from storage pool *)
	 IF LOOPHOLE (PoolEndPtr - PoolFreePtr,M3LONGINT) < ByteCount THEN
						(* release old pool *)
	    IF LOOPHOLE (PoolEndPtr - PoolFreePtr,M3LONGCARD) >= MinSizeSmallBlock THEN
	       Free (LOOPHOLE (PoolEndPtr - PoolFreePtr,M3LONGINT), PoolFreePtr);
	    END;
	    PoolFreePtr := Alloc (PoolSize);	(* allocate new pool *)
	    PoolEndPtr  := PoolFreePtr + PoolSize;
	 END;
	 INC (PoolFreePtr, LOOPHOLE (ByteCount,ADDRESS));
	 RETURN PoolFreePtr - LOOPHOLE (ByteCount,ADDRESS);
      END;
   ELSE						(* handle large block *)

      (* 1. search in LargeChain [Log2 (ByteCount)] using BEST FIT *)

      ChainNumber	:= Log2 (ByteCount);
      CurrentBlock	:= LargeChain [ChainNumber];
      PreviousBlock	:= ADR(* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 116
 $$ *) (LargeChain [ChainNumber]);
      BestBlock		:= NIL;
      BestBlockSize	:= 1000000000;

      WHILE CurrentBlock # NIL DO
	 CurrentBlockSize := CurrentBlock^.Size;
	 IF CurrentBlockSize >= ByteCount THEN	(* exact match *)
	    IF CurrentBlockSize = ByteCount THEN
	       PreviousBlock^.Successor := CurrentBlock^.Successor;
	       RETURN CurrentBlock;
	    END;

	    IF CurrentBlockSize < BestBlockSize 
            THEN	(* improve approximation *)
	       BestBlock	:= CurrentBlock;
	       BestBlockSize	:= CurrentBlockSize;
	       PredecessorBlock	:= PreviousBlock;
	    END;
	 END;
	 PreviousBlock	:= CurrentBlock;
	 CurrentBlock	:= CurrentBlock^.Successor;
      END;

      IF BestBlock # NIL THEN
	 PredecessorBlock^.Successor := BestBlock^.Successor;
	 IF (BestBlockSize - ByteCount) >= MinSizeSmallBlock THEN
	    Free (BestBlockSize - ByteCount,
		  LOOPHOLE (BestBlock,ADDRESS) + LOOPHOLE (ByteCount,ADDRESS));
	 END;
	 RETURN BestBlock;
      END;

      (* 2. search in LargeChain [j], j > Log2 (ByteCount), using FIRST FIT *)

      FOR j := ChainNumber+1 TO MaxSizeLargeBlockLog DO
	 CurrentBlock := LargeChain [j];
	 IF CurrentBlock # NIL THEN
	    LargeChain [j] := CurrentBlock^.Successor;
	    IF (CurrentBlock^.Size - ByteCount) >= MinSizeSmallBlock THEN
	       Free (CurrentBlock^.Size - ByteCount,
		     LOOPHOLE (CurrentBlock,ADDRESS) + LOOPHOLE (ByteCount,ADDRESS));
	    END;
	    RETURN CurrentBlock;
	 END;
      END;

      IF ByteCount < PoolSize THEN	(* 3. obtain block from storage pool *)
	 IF LOOPHOLE (PoolEndPtr - PoolFreePtr,M3LONGINT) < ByteCount THEN
						(* release old pool *)
	    IF LOOPHOLE (PoolEndPtr - PoolFreePtr,M3LONGCARD) >= MinSizeSmallBlock THEN
	       Free (LOOPHOLE (PoolEndPtr - PoolFreePtr,M3LONGINT), PoolFreePtr);
	    END;
	    PoolFreePtr := Alloc (PoolSize);	(* allocate new pool *)
	    PoolEndPtr  := PoolFreePtr + PoolSize;
	 END;
	 INC (PoolFreePtr, LOOPHOLE (ByteCount,ADDRESS));
	 RETURN PoolFreePtr - LOOPHOLE (ByteCount,ADDRESS);

      ELSE				(* 4. allocate individual block *)
	 BlockPtr := SysAlloc (ByteCount);
	 INC (MemoryUsed, VAL (   ByteCount,M3LONGCARD ) ); 
	 RETURN BlockPtr;
      END;
   END;
END Alloc;

(* The dynamically allocated space starting at	*)
(* address 'a' of size 'ByteCount' bytes is	*)
(* released.					*)

PROCEDURE Free	(ByteCount: M3LONGINT; a: ADDRESS) =
VAR
   BlockPtr	: tBlockPtr;
   ChainNumber	: tLargeBlockRange;
BEGIN
   ByteCount 
     := LOOPHOLE 
          (LOOPHOLE (ByteCount + VAL (   MaxAlign,M3LONGINT ) - 1,BITSET) 
           * AlignMasks [MaxAlign]
          ,M3LONGINT);

   BlockPtr := a;
   IF ByteCount <= MaxSizeSmallBlock THEN
      IF ByteCount < MinSizeSmallBlock THEN ByteCount := MinSizeSmallBlock; END;
      BlockPtr^.Successor	
        := SmallChain [ VAL (   ByteCount,tSmallBlockRange ) ];
      SmallChain [ VAL (   ByteCount,tSmallBlockRange ) ]	
        := BlockPtr;
   ELSE
      ChainNumber		:= Log2 (ByteCount);
      BlockPtr^.Successor	:= LargeChain [ChainNumber];
      BlockPtr^.Size		:= ByteCount;
      LargeChain [ChainNumber]	:= BlockPtr;
   END;
END Free;

(*
PROCEDURE WriteMemory;
   VAR
      BlockPtr	: tBlockPtr;
      Count	: INTEGER;
   BEGIN
      WriteS (StdOutput, "PoolFreePtr, PoolEndPtr = ");
      WriteN (StdOutput, INTEGER (PoolFreePtr), 8, 16);
      WriteN (StdOutput, INTEGER (PoolEndPtr ), 8, 16);
      WriteNl (StdOutput);
      WriteNl (StdOutput);

      WriteS (StdOutput, "SmallChain:");
      WriteNl (StdOutput);
      FOR i := MinSizeSmallBlock TO MaxSizeSmallBlock BY 2 DO
	 WriteI (StdOutput, i, 3);
	 WriteC (StdOutput, ':');
	 Count := 0;
	 BlockPtr := SmallChain [i];
	 WHILE BlockPtr # NIL DO
	    IF Count = 8 THEN
	       WriteNl (StdOutput);
	       WriteS (StdOutput, "    ");
	       Count := 0;
	    END;
	    INC (Count);
	    WriteC (StdOutput, ' ');
	    WriteN (StdOutput, INTEGER (BlockPtr), 8, 16);
	    BlockPtr := BlockPtr^.Successor;
	 END;
	 WriteNl (StdOutput);
      END;
      WriteNl (StdOutput);

      WriteS (StdOutput, "LargeChain:");
      WriteNl (StdOutput);
      FOR j := MinSizeLargeBlockLog TO MaxSizeLargeBlockLog DO
	 WriteI (StdOutput, j, 3);
	 WriteC (StdOutput, ':');
	 Count := 0;
	 BlockPtr := LargeChain [j];
	 WHILE BlockPtr # NIL DO
	    IF Count = 5 THEN
	       WriteNl (StdOutput);
	       WriteS (StdOutput, "    ");
	       Count := 0;
	    END;
	    INC (Count);
	    WriteC (StdOutput, ' ');
	    WriteN (StdOutput, INTEGER (BlockPtr), 8, 16);
	    WriteI (StdOutput, BlockPtr^.Size, 5);
	    BlockPtr := BlockPtr^.Successor;
	 END;
	 WriteNl (StdOutput);
      END;
      WriteNl (StdOutput);
   END WriteMemory;
*)

BEGIN
   FOR i := MinSizeSmallBlock TO MaxSizeSmallBlock BY 2 DO
      SmallChain [i] := NIL;
   END;
   FOR j := MinSizeLargeBlockLog TO MaxSizeLargeBlockLog DO
      LargeChain [j] := NIL;
   END;
   PoolFreePtr	:= NIL;
   PoolEndPtr	:= NIL;
   MemoryUsed	:= 0;
END Memory.

