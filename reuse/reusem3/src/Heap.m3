
(* $Id: Heap.mi,v 1.5 1991/11/21 14:33:17 grosch rel $ *) 

(* $Log: Heap.mi,v $ 
 
 * RMB 93/10/11 Type conversions for WRL. 
 
 * Revision 1.5  1991/11/21  14:33:17  grosch 
 * new version of RCS on SPARC 
 * 
 * Revision 1.4  90/03/02  17:36:09  grosch 
 * automized handling of machine independent alignment 
 * 
 * Revision 1.3  90/02/28  22:07:01  grosch 
 * comment for alignment on SPARC 
 * 
 * Revision 1.2  90/02/12  10:53:40  grosch 
 * introduced a machine dependent variant for MIPS 
 * 
 * Revision 1.1  89/07/13  11:27:01  grosch 
 * reset pointers to NIL in Free 
 * 
 * Revision 1.0  88/10/04  11:46:56  grosch 
 * Initial revision 
 * 
 *) 

(* Ich, Doktor Josef Grosch, Informatiker, 2.9.1988 *) 

UNSAFE MODULE Heap 

; IMPORT Word 

; FROM SYSTEM IMPORT M2LONGINT 

; FROM SYSTEM IMPORT BITSET 

; FROM General IMPORT MaxAlign , AlignMasks 

; IMPORT Memory 

; CONST PoolSize = 10240 

; TYPE tBlockPtr = UNTRACED BRANDED REF tBlock 
  ; tBlock 
    = RECORD 
        Successor : tBlockPtr 
      ; Block : ARRAY [ 1 .. PoolSize ] OF CHAR 
      END (* RECORD *) 

; VAR BlockList : tBlockPtr 
  ; PoolFreePtr : ADDRESS 
  ; PoolEndPtr : ADDRESS 

(* Returns a pointer to dynamically allocated   *) 
(* space of size 'ByteCount' bytes.             *) 

; PROCEDURE Alloc ( ByteCount : M2LONGINT ) : ADDRESS 

  = VAR BlockPtr : tBlockPtr 

  ; BEGIN (* Alloc *) 
      ByteCount 
        := Word . And ( ByteCount + MaxAlign - 1 , AlignMasks [ MaxAlign ] ) 
    ; IF LOOPHOLE ( PoolEndPtr - PoolFreePtr , M2LONGINT ) < ByteCount 
      THEN 
        BlockPtr := BlockList 
      ; BlockList := Memory . Alloc ( BYTESIZE ( tBlock ) ) 
      ; BlockList ^ . Successor := BlockPtr 
      ; PoolFreePtr 
          := ADR (* $$ m2tom3 warning: unhandled ADR parameter 'ADR' in line 64 
 $$ *)         ( BlockList ^ . Block ) 
      ; PoolEndPtr := PoolFreePtr + PoolSize 
      ; INC ( HeapUsed , PoolSize ) 
      END (* IF *) 

(* PoolFreePtr := PoolFreePtr + ADDRESS ( ByteCount ); *) 

    ; INC ( PoolFreePtr , ByteCount ) 
    ; RETURN PoolFreePtr - ByteCount 
    END Alloc 

(* The complete space allocated for the heap    *) 
(* is released.                                 *) 

; PROCEDURE Free ( ) 

  = VAR BlockPtr : tBlockPtr 

  ; BEGIN (* Free *) 
      WHILE BlockList # NIL 
      DO BlockPtr := BlockList 
      ; BlockList := BlockList ^ . Successor 
      ; Memory . Free ( BYTESIZE ( tBlock ) , BlockPtr ) 
      END (* WHILE *) 
    ; PoolFreePtr := NIL 
    ; PoolEndPtr := NIL 
    ; HeapUsed := 0 
    END Free 

; BEGIN (* Heap *) 
    BlockList := NIL 
  ; Free ( ) 
  END Heap 
. 

