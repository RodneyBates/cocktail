
(* Ich, Doktor Josef Grosch, Informatiker, Juli 1986 *)

INTERFACE  Memory;

VAR       MemoryUsed    : INTEGER;
                        (* Holds the total amount of memory curently    *)
                        (* allocated by this module.                    *)

PROCEDURE Alloc         (ByteCount: INTEGER) : ADDRESS;
                        (* Returns a pointer to dynamically allocated   *)
                        (* space of size 'ByteCount' bytes.             *)
                        (* Returns NIL if space is exhausted.           *)


PROCEDURE Free          (ByteCount: INTEGER; a: ADDRESS);
                        (* The dynamically allocated space starting at
                           address 'a' of size 'ByteCount' bytes is
                           released. a must be the result of a prior call
                           on Alloc, and not since passed to Free. *)

END Memory.




