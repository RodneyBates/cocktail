(* $Id: Classes.mi,v 3.2 1991/11/21 14:41:19 grosch rel $ *)

(* Rodney M. Bates
    Apr. 1999 Minor changes to compile, after changes to Sets
    Nov. 1999 Remove unused import of Layout . WriteChar 
*) 

(* $Log: Classes.mi,v $
Revision 3.2  1991/11/21  14:41:19  grosch
fixed bug: interference of right context between constant and non-constant RE
new version of RCS on SPARC

Revision 3.1  91/04/08  15:50:12  grosch
release memory after use in Classes and Tree0

Revision 3.0  91/04/04  18:26:37  grosch
Initial revision

 *)

(* Ich, Doktor Josef Grosch, Informatiker, March 1991 *)

 UNSAFE MODULE Classes;


IMPORT Word;
FROM DynArray	IMPORT MakeArray, ExtendArray, ReleaseArray;
FROM Strings	IMPORT tString, Char, Length;
FROM StringMem	IMPORT GetString;
FROM IO		IMPORT StdOutput, WriteC, WriteI, WriteS, WriteNl;
FROM Sets	IMPORT tSet, tElement, MakeSet, Assign, Include, IsEqual, ForallDo, WriteSet,
			Intersection, Union, Difference, Complement, ReleaseSet, IsEmpty,
			IsSubset;
FROM Tree0(* $$ m2tom3 warning: unable to find interface for import 'Tree0' in line 33
 $$ *)	IMPORT tTree0, Tree0Root, TraverseTree0TD, Ch, Set, String;
FROM Dfa	IMPORT FirstCh, LastCh, OldLastCh, EobCh;

PROCEDURE IsInSetMem (Set: tSet): INTEGER =
   VAR i : INTEGER;
   BEGIN
      FOR i := 1 TO SetCount DO
	 IF IsEqual (Set, SetMemPtr^[i].Set) THEN RETURN i; END;
      END;
      RETURN 0;
   END IsInSetMem;

PROCEDURE CollectSets (t: tTree0) =
   VAR i	: Word.T;
   VAR string	: tString;
   BEGIN
      CASE t(* $$ m2tom3 warning: unable to resolve qualification in designator 't' in line 49
 $$ *)^.Kind OF
      | Ch	=> Include (CharSet, ORD (t(* $$ m2tom3 warning: unable to resolve qualification in designator 't' in line 50
 $$ *)^.Ch(* $$ m2tom3 warning: unable to resolve qualification in designator 'Ch' in line 50
 $$ *).Ch));

      | Set	=> IF IsInSetMem (t(* $$ m2tom3 warning: unable to resolve qualification in designator 't' in line 52
 $$ *)^.Set(* $$ m2tom3 warning: unable to resolve qualification in designator 'Set' in line 52
 $$ *).Set) = 0 THEN
		     INC (SetCount);
		     IF SetCount = SetMemSize THEN
			ExtendArray (SetMemPtr, SetMemSize, BYTESIZE (ClassInfo));
		     END;
		     MakeSet (SetMemPtr^[SetCount].Set, ORD (LastCh));
		     Assign (SetMemPtr^[SetCount].Set, t(* $$ m2tom3 warning: unable to resolve qualification in designator 't' in line 58
 $$ *)^.Set(* $$ m2tom3 warning: unable to resolve qualification in designator 'Set' in line 58
 $$ *).Set);
		     Union (Unused, t(* $$ m2tom3 warning: unable to resolve qualification in designator 't' in line 59
 $$ *)^.Set(* $$ m2tom3 warning: unable to resolve qualification in designator 'Set' in line 59
 $$ *).Set);
		  END;

      | String	=> GetString (t(* $$ m2tom3 warning: unable to resolve qualification in designator 't' in line 62
 $$ *)^.String(* $$ m2tom3 warning: unable to resolve qualification in designator 'String' in line 62
 $$ *).String, string);
		  FOR i := Length (string) TO 1 BY -1 DO
		     Include (CharSet, ORD (Char (string, i)));
		  END;
      ELSE
      END;
   END CollectSets;

VAR Class: CHAR;

PROCEDURE CharToClass0 (Ch: tElement ) =
   BEGIN
      ToClass [VAL (Ch,CHAR)] := Class;
   END CharToClass0;

PROCEDURE CharToClass (Ch: tElement ) =
   BEGIN
      INC (LastCh);
      ToClass [VAL (Ch,CHAR)] := LastCh;
      ToChar [LastCh] := VAL (Ch,CHAR);
   END CharToClass;

PROCEDURE ComputeClasses (Blocking: BOOLEAN) =
   VAR i	: INTEGER;
   VAR j	: CHAR;
   VAR Set	: tSet;
   BEGIN
      OldLastCh := LastCh;
      MakeSet (CharSet, ORD (LastCh));
      MakeSet (Unused, ORD (LastCh));

      IF Blocking THEN
	 TraverseTree0TD (Tree0Root, CollectSets);
	 Include (CharSet, ORD (EobCh));
	 Union (Unused, CharSet);
	 Complement (Unused);
      ELSE
	 Include (CharSet, ORD (FirstCh));
	 Complement (CharSet);
      END;

      ClassCount := '\000';
      MakeSet (ClassMemPtr^['\000'], ORD (LastCh));
      Assign (ClassMemPtr^['\000'], CharSet);
      Union (ClassMemPtr^['\000'], Unused);
      Complement (ClassMemPtr^['\000']);

      MakeSet (Set, ORD (LastCh));
      FOR i := 1 TO SetCount DO
	 FOR j := '\000' TO ClassCount DO
	    Assign (Set, SetMemPtr^[i].Set);
	    Difference (Set, CharSet);
	    Intersection (Set, ClassMemPtr^[j]);
	    IF (NOT IsEmpty (Set)) AND (NOT IsEqual (Set, ClassMemPtr^[j])) THEN
	       INC (ClassCount);
	       IF ORD (ClassCount) = LOOPHOLE (ClassMemSize,Word.T) THEN
		  ExtendArray (ClassMemPtr, ClassMemSize, BYTESIZE (tSet));
	       END;
	       MakeSet (ClassMemPtr^[ClassCount], ORD (LastCh));
	       Assign (ClassMemPtr^[ClassCount], Set);
	       Difference (ClassMemPtr^[j], Set);
	    END;
	 END;
      END;
      ReleaseSet (Set);

      FOR i := 1 TO SetCount DO
	 MakeSet (SetMemPtr^[i].Classes, ORD (ClassCount));
	 FOR j := '\000' TO ClassCount DO
	    IF IsSubset (ClassMemPtr^[j], SetMemPtr^[i].Set) THEN
	       Include (SetMemPtr^[i].Classes, ORD (j));
	    END;
	 END;
      END;

      FOR j := '\000' TO ClassCount DO
	 Class := j;
	 ForallDo (ClassMemPtr^[j], CharToClass0);
      END;

      LastCh := ClassCount;
      ForallDo (CharSet, CharToClass);
   END ComputeClasses;

PROCEDURE ReleaseSetMem() =
   VAR i : INTEGER;
   BEGIN
      FOR i := 1 TO SetCount DO
	 ReleaseSet (SetMemPtr^[i].Set);
	 ReleaseSet (SetMemPtr^[i].Classes);
      END;
      ReleaseArray (SetMemPtr, SetMemSize, BYTESIZE (ClassInfo));
   END ReleaseSetMem;

BEGIN
   SetMemSize := 16;
   MakeArray (SetMemPtr, SetMemSize, BYTESIZE (ClassInfo));
   SetCount := 0;
   ClassMemSize := 16;
   MakeArray (ClassMemPtr, ClassMemSize, BYTESIZE (tSet));
END Classes.

