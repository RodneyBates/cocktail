(* print some informations about the generation *)

(* $Id: Infos.md,v 1.1 1991/11/21 14:53:14 grosch rel $ *)

(* $Log: Infos.md,v $
 * Revision 1.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.0  88/10/04  14:36:25  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Infos;

  FROM IO IMPORT
    tFile;

  PROCEDURE WriteInfo (f: tFile);

  (* Ausgabe von statistischen Informationen auf file 'f' *)

END Infos.
