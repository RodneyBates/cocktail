MODULE SYSTEM;

(* For use in gmd. RMB. *)

IMPORT Process;

PROCEDURE HALT () =

  BEGIN
    Process . Exit ( 1 ) <* NORETURN *>
  END HALT;


PROCEDURE ODD (i: INTEGER): BOOLEAN =
  BEGIN
    RETURN i MOD 2 = 1;
  END ODD;

BEGIN
END SYSTEM.
