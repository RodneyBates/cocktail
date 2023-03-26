(* handle system errors *)

(* $Id: SysError.md,v 1.2 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: SysError.md,v $
 * Revision 1.2  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/11  18:45:41  grosch
 * layout improvements
 * 
 * Revision 1.0	 88/10/04  14:27:19  vielsack
 * Initial revision
 * 
 *)

UNSAFE INTERFACE  SysError;



IMPORT Word;
PROCEDURE StatIsBad		(N: INTEGER): BOOLEAN;
PROCEDURE SysErrorMessageI	(N: INTEGER; ErrCl, InfCl: Word.T; Info: ADDRESS);
PROCEDURE SysErrorMessage	(N: INTEGER; ErrCl: Word.T);

END SysError.

