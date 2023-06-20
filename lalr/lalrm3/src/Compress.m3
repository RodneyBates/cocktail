(* compress parse table *)

(* $Id: Compress.mi,v 2.2 1992/08/07 15:22:49 grosch rel $ *)

(* $Log: Compress.mi,v $
 * Revision 2.2  1992/08/07  15:22:49  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.1  1991/11/21  14:53:14  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:31:39  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/12  16:53:48  grosch
 * renamed main program to lalr, added { } for actions, layout improvements
 * 
 * Revision 1.0  88/10/04  14:35:59  vielsack
 * Initial revision
 * 
 *)

(* Modified 2002/03/07 Rodney M. Bates 
   Two places ExtendArray is called, added increase of the array size.
*) 

(* Converted to Modula-3, beginning 2023-03-29,
   Rodney M. Bates, rodney.m.bates@acm.org *) 

UNSAFE MODULE Compress;

FROM SYSTEM IMPORT M2LONGINT;
FROM Automaton  IMPORT tIndex, tStateIndex;
FROM DynArray   IMPORT MakeArray, ExtendArray;
FROM Gen        IMPORT tTableLine, NoState, LastReadState, FirstTerminal, LastTerminal, FirstSymbol, LastSymbol;
FROM General    IMPORT Max, Min;

FROM TokenTab   IMPORT Vocabulary;

  CONST
    InitTableMax = 1500;
    InitNTableMax = 500;

PROCEDURE InitCompressTable() =
   VAR
      b         : tIndex;
      State     : tStateIndex;
   BEGIN
      BaseCount    := LastReadState+1;
      Base := NEW (REF ARRAY OF TableElmt, BaseCount+1);
(* See note in Debug.SearchPathC about MakeArray. *) 
(*WAS:MakeArray (Base,BaseCount,ElmtSize);*)

      DefaultCount := LastReadState+1;
      Default := NEW ( REF ARRAY OF TableElmt, DefaultCount+1);
(*WAS:MakeArray (Default,DefaultCount,ElmtSize);*)

      ControlCount := LastSymbol+InitTableMax;
      Control := NEW (REF ARRAY OF ControlType, ControlCount+1);
(*WAS:MakeArray (Control,ControlCount,BYTESIZE(ControlType));*)

      TableMax := ControlCount - 1;

      FOR State := 0 TO LastReadState DO
         Base^ [State] := 0;
         Default^ [State] := NoState;
      END;

      FOR b := 0 TO TableMax DO
         Control^ [b].Next  := NoState;
         Control^ [b].Check := NoState;
      END;

      TableSize := 0;
    END InitCompressTable;

PROCEDURE CompressTableLine (State: tStateIndex; DefaultState: tStateIndex; VAR TableLine: tTableLine) =

(* Terminale komprimieren *)

   VAR
      b         : tIndex;
      Success   : BOOLEAN;
      Symbol    : Vocabulary;
      index     : tIndex;
      OldTableMax : tIndex;
      NextSym   : ARRAY Vocabulary OF Vocabulary;
      StartSym  ,
      StopSym   ,
      PrevSym   : Vocabulary;
   
   BEGIN

      Default^ [State] := DefaultState;

      (* solution 2 *)
 
      (* turn the row Table [State, ...] into a list *)
 
      Symbol := FirstTerminal;
      Success := FALSE;
      LOOP
         IF Symbol > LastTerminal THEN EXIT; END;
         IF (TableLine [Symbol] # NoState) THEN
            StartSym := Symbol;
            PrevSym  := Symbol;
            Success  := TRUE;
            EXIT;
         END;
         INC (Symbol);
      END;
      INC (Symbol);
 
      LOOP
         IF Symbol > LastTerminal THEN EXIT; END;
         IF (TableLine [Symbol] # NoState) THEN
            NextSym [PrevSym] := Symbol;
            PrevSym := Symbol;
         END;
         INC (Symbol);
      END;
      StopSym := PrevSym;
 
      (* search for a usable base b *)
 
      b := 0;
      IF Success THEN
         LOOP
            Success := TRUE;
            Symbol := StartSym;
            LOOP
               IF (Control^ [b + Symbol].Check  # NoState) THEN
                  Success := FALSE;
                  EXIT;
               END;
               IF Symbol = StopSym THEN EXIT; END;
               Symbol := NextSym [Symbol];
            END;
 
            IF Success THEN EXIT; END;
            INC (b);
            IF (b + LastTerminal) > TableMax THEN
               OldTableMax := TableMax;
               ControlCount := b + LastTerminal + 1;  
               (*ExtendArray (Control,ControlCount,BYTESIZE(ControlType));*)
               TableMax := ControlCount - 1;
               FOR index := OldTableMax+1 TO TableMax DO
                  Control^ [index].Next  := NoState;
                  Control^ [index].Check := NoState;
               END;
            END;
         END;
      ELSE
         Success := TRUE;
      END;
 
      Base^ [State] := b;
      TableSize := Max (TableSize, b);
      FOR Symbol := FirstTerminal TO LastTerminal DO
         IF (TableLine [Symbol] # NoState) THEN
            Control^ [b + Symbol].Check := State;
            Control^ [b + Symbol].Next  := TableLine [Symbol];
            INC (Filling);
         END;
      END;
   END CompressTableLine;
 

PROCEDURE InitCompressNTable() =
   VAR
      b         : tIndex;
      State     : tStateIndex;
   BEGIN
      NBaseCount := LastReadState+1;
      NBase := NEW (REF ARRAY OF TableElmt, NBaseCount+1);
(* See note in Debug.SearchPathC about MakeArray. *) 
(*WAS:MakeArray (NBase,NBaseCount,ElmtSize);*)
      NNextCount := LastSymbol+InitNTableMax;
      NNext := NEW (REF ARRAY OF TableElmt ,NNextCount+1);
(*WAS:MakeArray (NNext,NNextCount,BYTESIZE(TableElmt));*)
      NTableMax := NNextCount - 1;
      FOR State := 0 TO LastReadState DO NBase^ [State] := 0; END;
      FOR b := 0 TO NTableMax DO NNext^ [b] := NoState; END;
      NTableSize := 0;
    END InitCompressNTable;

PROCEDURE CompressNTableLine (State: tStateIndex; VAR TableLine: tTableLine) =

(* Nichtterminale komprimieren *)

   VAR
      b         : tIndex;
      Success   : BOOLEAN;
      Symbol    : Vocabulary;
      index     : tIndex;
      OldTableMax : tIndex;
      NextSym   : ARRAY Vocabulary OF Vocabulary;
      StartSym  ,
      StopSym   ,
      PrevSym   : Vocabulary;
   
   BEGIN

      (* solution 2 *)
 
      (* turn the row Table [State, ...] into a list *)
 
      Symbol := LastTerminal+1; (* FirstNonterminal *)
      Success := FALSE;
      LOOP
         IF Symbol > LastSymbol THEN EXIT; END;
         IF (TableLine [Symbol] # NoState) THEN
            StartSym := Symbol;
            PrevSym  := Symbol;
            Success  := TRUE;
            EXIT;
         END;
         INC (Symbol);
      END;
      INC (Symbol);
 
      LOOP
         IF Symbol > LastSymbol THEN EXIT; END;
         IF (TableLine [Symbol] # NoState) THEN
            NextSym [PrevSym] := Symbol;
            PrevSym := Symbol;
         END;
         INC (Symbol);
      END;
      StopSym := PrevSym;
 
      (* search for a usable base b *)
 
      b := 0;
      IF Success THEN
         LOOP
            Success := TRUE;
            Symbol := StartSym;
            LOOP
               IF (NNext^ [b + Symbol] # NoState) AND
                  (NNext^ [b + Symbol] # TableLine [Symbol]) THEN
                  Success := FALSE;
                  EXIT;
               END;
               IF Symbol = StopSym THEN EXIT; END;
               Symbol := NextSym [Symbol];
            END;
 
            IF Success THEN EXIT; END;
            INC (b);
            IF (b + LastSymbol) > NTableMax THEN
               OldTableMax := NTableMax;
               NNextCount := b + LastSymbol + 1; 
               (*ExtendArray (NNext,NNextCount,BYTESIZE(TableElmt));*)
               NTableMax := NNextCount - 1;
               FOR index := OldTableMax+1 TO NTableMax DO
                  NNext^ [index] := NoState;
               END;
            END;
         END;
      ELSE
         Success := TRUE;
      END;
 
      NBase^ [State] := b;
      NTableSize := Max (NTableSize, b);
      FOR Symbol := LastTerminal+1 TO LastSymbol DO
         IF (TableLine [Symbol] # NoState) THEN
            NNext^ [b + Symbol] := TableLine [Symbol];
            INC (NFilling);
         END;
      END;
   END CompressNTableLine;

BEGIN
  ElmtSize      := BYTESIZE(TableElmt);
  Filling       := 0;
  NFilling      := 0;
END Compress.

