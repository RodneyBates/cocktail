(* print some informations about the generation *)

(* $Id: Infos.mi,v 1.3 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Infos.mi,v $
 * Revision 1.3  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 1.2  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.1  90/06/12  16:54:21  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0	 88/10/04  14:36:26  vielsack
 * Initial revision
 * 
 *)

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE Infos;

IMPORT Word;
FROM Automaton	IMPORT ProdCount, ProdIndex, ItemIndex, StateIndex;
FROM Compress	IMPORT Filling, TableSize, NFilling, NTableSize;
FROM Gen	IMPORT FirstReadState, LastReadState, LastTerminal,
			FirstReduceState, LastReduceState,
			FirstReadNonTermState, LastReadNonTermState,
			FirstReadTermState, LastReadTermState;
FROM ReuseIO		IMPORT WriteT, WriteI, WriteNl, tFile;
FROM Memory	IMPORT MemoryUsed;
FROM SYSTEM	IMPORT  WORD;
FROM Times	IMPORT CpuTime;
FROM TokenTab	IMPORT MINTerm, MAXTerm, MINNonTerm, MAXNonTerm;

  PROCEDURE WriteInfo (f: tFile) =

  (* Ausgabe von statistischen Informationen auf file 'f' *)

  VAR NSize	: Word.T;
  BEGIN
    WriteT (f, "Statistik");					WriteNl (f);
    WriteT (f, "-------------------");				WriteNl (f);
    WriteT (f, "Terminals   : "); 
       WriteI (f, MAXTerm-MINTerm+1, 5);			WriteNl (f);
    WriteT (f, "Nonterminals: "); 
       WriteI (f, MAXNonTerm-MINNonTerm+1, 5);			WriteNl (f);
    WriteT (f, "Productions : "); WriteI (f, ProdCount, 5);	WriteNl (f);
    WriteT (f, "Prod (Bytes): "); WriteI (f, ProdIndex*BYTESIZE (WORD), 5); 
								WriteNl (f);
    WriteT (f, "Items       :" ); WriteI (f, ItemIndex, 6);	WriteNl (f);
    WriteT (f, "LR(0)-States: "); WriteI (f, StateIndex, 5);	WriteNl (f);
    WriteT (f, "ReadStates  : "); 
       WriteI (f, LastReadState-FirstReadState+1, 5);		WriteNl (f);

    WriteNl (f);

    WriteT (f, "Base        : "); WriteI (f, (LastReadState+1)*2, 5); WriteNl (f);
    WriteT (f, "NBase       : "); WriteI (f, (LastReadState+1)*2, 5); WriteNl (f);
    WriteT (f, "Default     : "); WriteI (f, (LastReadState+1)*2, 5); WriteNl (f);

    WriteT (f, "Terminals   : "); WriteI (f, (TableSize+1)*4, 5); 
      WriteI (f, ((Filling*100)+(TableSize DIV 2)) DIV TableSize, 4);
      WriteC (f, '%'); WriteNl (f);

    NSize := NTableSize - LastTerminal;
    WriteT (f, "Nonterminals: "); WriteI (f, NSize*2, 5);
      WriteI (f, ((NFilling*100)+(NSize DIV 2)) DIV NSize, 4);
      WriteC (f, '%'); WriteNl (f);

    WriteT (f, "Length      : "); 
      WriteI (f, (LastReduceState-FirstReduceState+1)*2, 5); WriteNl (f);

    WriteT (f, "Left        : "); 
      WriteI (f, (LastReduceState-FirstReduceState+1)*2, 5); WriteNl (f);

    WriteT (f, "Continuation: "); 
      WriteI (f, (LastReadState+1)*2, 5); WriteNl (f);

    WriteT (f, "FinalToProd : "); 
      WriteI (f, (LastReadNonTermState-FirstReadTermState+1)*2, 5); WriteNl (f);

    WriteT (f, "Cpu-Time [ms]" ); WriteI (f, CpuTime (), 6); WriteNl (f);

    WriteT (f, "Memory used  " ); WriteI (f, MemoryUsed, 6); WriteNl (f);
  END WriteInfo;

BEGIN
END Infos.

