
UNSAFE MODULE Memory;

TYPE ByteTyp = [0..16_FF];
TYPE ByteArrTyp = ARRAY OF BITS 8 FOR ByteTyp;
TYPE ByteArrRefTyp = UNTRACED REF ByteArrTyp;

TYPE IntRefTyp = UNTRACED REF INTEGER;
TYPE AddrRefTyp = UNTRACED REF ADDRESS;

CONST DopeSize = BYTESIZE ( ADDRESS ) + BYTESIZE (INTEGER );
      (* ^ Beware! this is inside information. *)

PROCEDURE SanityCheck
  (HeapObjRef: ByteArrRefTyp; EltsAddr: ADDRESS; ByteCount: INTEGER) =

  VAR LEltsAddrRef: AddrRefTyp;
  BEGIN
    LEltsAddrRef := LOOPHOLE (HeapObjRef, AddrRefTyp);
    <* ASSERT EltsAddr = LEltsAddrRef ^ *>
    <* ASSERT NUMBER (HeapObjRef^) = ByteCount *>
    <* ASSERT ADR(HeapObjRef^[0]) = EltsAddr *> 
  END SanityCheck; 

(*EXPORTED*)
PROCEDURE Alloc	(ByteCount: INTEGER): ADDRESS =
(* Returns a pointer to dynamically allocated	*)
(* space of size 'ByteCount' bytes.		*)
  VAR LAlloc: ByteArrRefTyp;
  VAR LAllocSize: INTEGER;
  VAR LResultAddr: ADDRESS;
  BEGIN
    LAlloc := NEW (ByteArrRefTyp, ByteCount);
    LAllocSize := DopeSize + ByteCount;
    INC (MemoryUsed, LAllocSize);
    LResultAddr := LOOPHOLE(LAlloc, ADDRESS) + DopeSize;
    SanityCheck (LAlloc, LResultAddr, ByteCount);
    <*ASSERT ADR(LAlloc^[0]) = LResultAddr*> 
    RETURN LResultAddr;
  END Alloc;

(*EXPORTED*)
PROCEDURE Free (ByteCount: INTEGER; a: ADDRESS) =
(* The dynamically allocated space starting at
   address 'a' of size 'ByteCount' bytes is
   released. a must be the result of a prior call
   on Alloc, and not since passed to Free. *)

  VAR LAlloc: ByteArrRefTyp;
  VAR LAllocSize: INTEGER;
  BEGIN
    LAlloc := LOOPHOLE (a - DopeSize, ByteArrRefTyp);
    SanityCheck (LAlloc, a, ByteCount);
    LAllocSize := DopeSize + ByteCount;
    DEC (MemoryUsed, LAllocSize);
    DISPOSE (LAlloc);
  END Free;

BEGIN
   MemoryUsed	:= 0;
END Memory.

