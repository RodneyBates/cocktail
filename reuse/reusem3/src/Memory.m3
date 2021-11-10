
UNSAFE MODULE Memory;

TYPE ByteTyp = [0..16_FF];
TYPE ByteArrTyp = ARRAY OF ByteTyp;
TYPE ByteArrRefTyp = UNTRACED REF ByteArrTyp; 

(*EXPORTED*)
PROCEDURE Alloc	(ByteCount: INTEGER): ADDRESS =
(* Returns a pointer to dynamically allocated	*)
(* space of size 'ByteCount' bytes.		*)
  VAR LResult: ByteArrRefTyp;
  BEGIN
    LResult := NEW (ByteArrRefTyp, ByteCount);
    INC (MemoryUsed, BYTESIZE (LResult^));
    RETURN LResult;
  END Alloc;

(*EXPORTED*)
PROCEDURE Free	(<*UNUSED*> ByteCount: INTEGER; a: ADDRESS) =
(* The dynamically allocated space starting at
   address 'a' of size 'ByteCount' bytes is
   released. a must be the result of a prior call
   on Alloc, and not since passed to Free. *)

  VAR LRef: ByteArrRefTyp;
  BEGIN
    LRef := LOOPHOLE(a, ByteArrRefTyp);
    DEC (MemoryUsed, BYTESIZE (LRef^));
    DISPOSE (LRef);
  END Free;

BEGIN
   MemoryUsed	:= 0;
END Memory.

