(* compress parse table *)

(* $Id: Compress.md,v 1.4 1992/08/12 06:53:34 grosch rel $ *)

(* $Log: Compress.md,v $
 * Revision 1.4  1992/08/12  06:53:34  grosch
 * extend parse table TComb over 65535 bytes
 *
 * Revision 1.3  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/12  16:53:47  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0  88/10/04  14:35:57  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE INTERFACE  Compress;

IMPORT Word;
FROM SYSTEM IMPORT SHORTCARD;
FROM SYSTEM IMPORT M2LONGINT;
FROM Automaton IMPORT tIndex, tStateIndex, Infinite, Infinite2;
FROM Gen IMPORT tTableLine;

  TYPE
    TableElmt   = SHORTCARD;
    ControlType = RECORD Check, Next: TableElmt; END;

  VAR
    Control     : REF ARRAY OF ControlType;
    Base        : REF ARRAY OF TableElmt;
    Default     : REF ARRAY  OF TableElmt;
    ControlCount,
    BaseCount   ,
    DefaultCount: INTEGER;
    TableMax    : tIndex;
    TableSize   : tIndex;

    NNext       : REF ARRAY OF TableElmt;
    NBase       : REF ARRAY OF TableElmt;
    NNextCount  : M2LONGINT;
    NBaseCount  : M2LONGINT;
    NTableMax   : tIndex;
    NTableSize  : tIndex;

    ElmtSize    : TableElmt;

    Filling     : Word.T;
    NFilling    : Word.T;

PROCEDURE InitCompressTable();
PROCEDURE CompressTableLine (State: tStateIndex; DefaultState: tStateIndex; VAR TableLine: tTableLine);
PROCEDURE InitCompressNTable();
PROCEDURE CompressNTableLine (State: tStateIndex; VAR TableLine: tTableLine);

END Compress.

