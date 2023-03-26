(* error listing *)

(* $Id: Listing.md,v 1.2 1991/11/21 14:47:50 grosch rel $ *)

(* $Log: Listing.md,v $
 * Revision 1.2  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/11  18:45:02  grosch
 * layout improvements
 * 
 * Revision 1.0	 88/10/04  14:26:48  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Listing;

FROM	IO		IMPORT	tFile;
FROM	SYSTEM		IMPORT	ADDRESS;

TYPE tListMode = (NoListing, Listing);

VAR
  SourceFile : tFile;
  ListFile   : tFile;
  ListMode   : tListMode;

PROCEDURE PutError (Code,Class,Line,Column,InfoClass: CARDINAL; Info: ADDRESS);
PROCEDURE HasError (): BOOLEAN;
PROCEDURE GetError (VAR Code,Class,Line,Column,InfoClass: CARDINAL; VAR Info: ADDRESS);

END Listing.
