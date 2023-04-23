(* error listing *)

(* $Id: Listing.md,v 1.2 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: Listing.md,v $
 * Revision 1.2  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/11  18:45:02  grosch
 * layout improvements
 * 
 * Revision 1.0  88/10/04  14:26:48  vielsack
 * Initial revision
 * 
 *)

UNSAFE INTERFACE  Listing;

IMPORT Word;

IMPORT IntSets;

FROM    ReuseIO               IMPORT  tFile;


TYPE tListMode = {NoListing, Listing};

VAR
  SourceFile : tFile;
  ListFile   : tFile;
  ListMode   : tListMode;

PROCEDURE PutError
  (Code,Class,Line,Column,InfoClass: Word.T;
   Info: ADDRESS := NIL; InfoTraced: REFANY := NIL);
PROCEDURE HasError (): BOOLEAN;
PROCEDURE GetError
  (VAR Code,Class,Line,Column,InfoClass: Word.T;
   VAR Info: ADDRESS; VAR InfoTraced: REFANY);

END Listing.

