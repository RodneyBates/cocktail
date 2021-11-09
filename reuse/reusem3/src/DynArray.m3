(* $Id: DynArray.mi,v 1.6 1992/08/07 14:45:20 grosch rel $ *)

(* $Log: DynArray.mi,v $

 * RMB 93/10/11 Added two type conversions of (General.)MaxAlign to M3LONGINT
       in AlignedSize to compile under WRL.

 * Revision 1.6  1992/08/07  14:45:20  grosch
 * added error message if out of memory
 *
 * Revision 1.5  1991/11/21  14:33:17  grosch
 * new version of RCS on SPARC
 *
 * Revision 1.4  90/03/02  17:36:10  grosch
 * automized handling of machine independent alignment
 * 
 * Revision 1.3  90/02/28  22:07:00  grosch
 * comment for alignment on SPARC
 * 
 * Revision 1.2  89/12/08  20:12:44  grosch
 * introduced a machine dependent variant for MIPS
 * 
 * Revision 1.1  88/10/18  16:30:08  grosch
 * fixed bug: invariant must hold: ElmtCount * ElmtSize MOD 4 = 0
 * 
 * Revision 1.0  88/10/04  11:46:52  grosch
 * Initial revision
 * 
 *)

(* Ich, Doktor Josef Grosch, Informatiker, Sept. 1987 *)

 UNSAFE MODULE DynArray;

FROM SYSTEM IMPORT M3LONGINT;
FROM SYSTEM	IMPORT   ODD, WORD;
FROM General	IMPORT Log2, Exp2, MaxAlign;
FROM Memory	IMPORT Alloc, Free;
FROM IO		IMPORT StdError, WriteS, WriteNl;

(* INVARIANT ElmtCount * AlignedSize (ElmtSize) MOD TSIZE (M3LONGINT) = 0 *)

PROCEDURE MakeArray    (VAR ArrayPtr	: ADDRESS	;
			VAR ElmtCount	: M3LONGINT	;
			    ElmtSize	: M3LONGINT)	 =
   BEGIN
      ElmtSize := AlignedSize (ElmtSize);
      CASE ElmtSize MOD 4 OF
      | 0   =>
      | 2   => IF ODD (ElmtCount) THEN INC (ElmtCount); END;
      | 1, 3=> INC (ElmtCount, BYTESIZE (M3LONGINT) - 1 - ((ElmtCount - 1) MOD BYTESIZE (M3LONGINT)));
      END;
      ArrayPtr := Alloc (ElmtCount * ElmtSize);
      IF ArrayPtr = NIL THEN
	 WriteS (StdError, ARRAY [0..24] OF CHAR{'M','a','k','e','A','r','r','a','y',':',' ','o','u','t',' ','o','f',' ','m','e','m','o','r','y','\000'}); WriteNl (StdError);
      END;
   END MakeArray;

PROCEDURE ExtendArray  (VAR ArrayPtr	: ADDRESS	;
			VAR ElmtCount	: M3LONGINT	;
			    ElmtSize	: M3LONGINT)	 =
   VAR
      NewPtr		: ADDRESS;
      Source, Target	: UNTRACED BRANDED REF  M3LONGINT;
      i			: M3LONGINT;
   BEGIN
      ElmtSize := AlignedSize (ElmtSize);
      NewPtr := Alloc (ElmtCount * ElmtSize * 2);
      IF NewPtr = NIL THEN
	 WriteS (StdError, ARRAY [0..26] OF CHAR{'E','x','t','e','n','d','A','r','r','a','y',':',' ','o','u','t',' ','o','f',' ','m','e','m','o','r','y','\000'}); WriteNl (StdError);
      ELSE
	 Source := ArrayPtr;
	 Target := NewPtr;
	 FOR i := 1 TO ElmtCount * ElmtSize DIV BYTESIZE (M3LONGINT) DO
	    Target ^ := Source ^;
	    Source := LOOPHOLE (LOOPHOLE (Source,ADDRESS) + BYTESIZE (M3LONGINT),ADDRESS);
	    Target := LOOPHOLE (LOOPHOLE (Target,ADDRESS) + BYTESIZE (M3LONGINT),ADDRESS);
	 END;
	 Free (ElmtCount * ElmtSize, ArrayPtr);
	 INC (ElmtCount, ElmtCount);
      END;
      ArrayPtr := NewPtr;
   END ExtendArray;

PROCEDURE ReleaseArray (VAR ArrayPtr	: ADDRESS	;
			VAR ElmtCount	: M3LONGINT	;
			    ElmtSize	: M3LONGINT)	 =
   BEGIN
      ElmtSize := AlignedSize (ElmtSize);
      Free (ElmtCount * ElmtSize, ArrayPtr);
   END ReleaseArray;

PROCEDURE AlignedSize  (ElmtSize: M3LONGINT): M3LONGINT =
   VAR Align	: M3LONGINT;
   BEGIN
      IF ElmtSize >= VAL (   MaxAlign,M3LONGINT ) THEN
	 Align := VAL (   MaxAlign,M3LONGINT );
      ELSE
	 Align := Exp2 (Log2 (ElmtSize + ElmtSize - 2));
      END;
      RETURN ElmtSize + Align - 1 - ((ElmtSize - 1) MOD Align);
   END AlignedSize;

BEGIN
END DynArray.

