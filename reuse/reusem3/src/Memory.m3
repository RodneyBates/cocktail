
UNSAFE MODULE Memory;

TYPE ByteTyp = [0..16_FF];
TYPE ByteArrTyp = ARRAY OF ByteTyp;
TYPE ByteArrRefTyp = UNTRACED REF ByteArrTyp;

CONST DopeSize = BYTESIZE ( ADDRESS ) + BYTESIZE (INTEGER );
      (* ^ Beware! this is inside information. *)

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
    <*ASSERT ADR(LAlloc^[0]) = a*> 
    LAllocSize := DopeSize + ByteCount;
    DEC (MemoryUsed, LAllocSize);
    DISPOSE (LAlloc);
  END Free;

BEGIN
   MemoryUsed	:= 0;
END Memory.

