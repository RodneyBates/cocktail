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

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  Infos;

  FROM ReuseIO IMPORT
    tFile;

  PROCEDURE WriteInfo (f: tFile);

  (* Ausgabe von statistischen Informationen auf file 'f' *)

END Infos.

