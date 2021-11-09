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
 * Revision 1.0	 88/10/04  14:35:57  vielsack
 * Initial revision
 * 
 *)

DEFINITION MODULE Compress;

FROM Automaton IMPORT tIndex, tStateIndex, Infinite, Infinite2;
FROM Gen IMPORT tTableLine;

  TYPE
    TableElmt	= SHORTCARD;
    ControlType = RECORD Check, Next: TableElmt; END;

  VAR
    Control	: POINTER TO ARRAY [0..Infinite2] OF ControlType;
    Base	: POINTER TO ARRAY [0..Infinite] OF TableElmt;
    Default	: POINTER TO ARRAY [0..Infinite] OF TableElmt;
    ControlCount,
    BaseCount	,
    DefaultCount: LONGINT;
    TableMax	: tIndex;
    TableSize	: tIndex;

    NNext	: POINTER TO ARRAY [0..Infinite] OF TableElmt;
    NBase	: POINTER TO ARRAY [0..Infinite] OF TableElmt;
    NNextCount	: LONGINT;
    NBaseCount	: LONGINT;
    NTableMax	: tIndex;
    NTableSize	: tIndex;

    ElmtSize	: TableElmt;

    Filling	: CARDINAL;
    NFilling	: CARDINAL;

PROCEDURE InitCompressTable;
PROCEDURE CompressTableLine (State: tStateIndex; DefaultState: tStateIndex; VAR TableLine: tTableLine);
PROCEDURE InitCompressNTable;
PROCEDURE CompressNTableLine (State: tStateIndex; VAR TableLine: tTableLine);

END Compress.
