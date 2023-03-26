(* handle system errors *)

(* $Id: SysError.mi,v 2.3 1992/08/07 15:13:51 grosch rel $ *)

(* $Log: SysError.mi,v $
 * Revision 2.3  1992/08/07  15:13:51  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.2  1992/01/30  13:34:33  grosch
 * redesign of interface to operating system
 *
 * Revision 2.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:26:40  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/11  18:45:42  grosch
 * layout improvements
 * 
 * Revision 1.0	 88/10/04  14:27:20  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE SysError;

IMPORT Word;
FROM Errors	IMPORT ErrorMessage, ErrorMessageI, SysOffset;

FROM System	IMPORT ErrNum;
FROM Positions	IMPORT NoPosition;

PROCEDURE StatIsBad (N: INTEGER): BOOLEAN =
  BEGIN
    RETURN N < 0;
  END StatIsBad;

PROCEDURE SysErrorMessageI (N: INTEGER; ErrCl, InfCl: Word.T; Info: ADDRESS) =
  BEGIN
    IF StatIsBad (N) THEN
      ErrorMessageI (ErrNum () + SysOffset, ErrCl, NoPosition, InfCl, Info);
    END;
  END SysErrorMessageI;

PROCEDURE SysErrorMessage (N: INTEGER; ErrCl: Word.T) =
  BEGIN
    IF StatIsBad (N) THEN
      ErrorMessage (ErrNum () + SysOffset, ErrCl, NoPosition);
    END;
  END SysErrorMessage;

BEGIN
END SysError.

