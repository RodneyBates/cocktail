(* Ich, Doktor Josef Grosch, Informatiker, 8.1.1988 *)

MODULE cg;

FROM System	IMPORT GetArgCount, GetArgument, System, Exit;
FROM Memory	IMPORT MemoryUsed;
FROM IO		IMPORT StdOutput, StdError, WriteOpen, WriteClose, CloseIO,
			WriteI, WriteS, WriteNl,
			tFile, ReadOpen, ReadClose, EndOfFile, ReadNl;
FROM Strings	IMPORT tString, AssignEmpty, Assign, Append, Concatenate,
			ReadL, WriteL, ArrayToString, StringToArray;
FROM Idents	IMPORT tIdent, NoIdent, MakeIdent, GetString, WriteIdent;
FROM Sets	IMPORT tSet, MakeSet, ReleaseSet, Include, Exclude, IsEmpty,
			Extract, Complement, Union, IsElement;
FROM Errors	IMPORT StoreMessages, WriteMessages;
FROM Scanner	IMPORT ScanTabName, BeginFile, Attribute, CurArg, ArgCount;
FROM Parser	IMPORT Parser, ParsTabName;
FROM Tree	IMPORT NoTree, tTree, Trace, Options, TreeRoot, QueryTree, ErrorCount,
			HeapUsed, ModuleName, f, BeginTree2, ForallClasses, SourceFile,
			WI, TypeNames, itTree, iNoTree, iModule, iInteger, IdentifyClass,
			ViewName;
FROM Tree2	IMPORT PutTree2;
FROM Semantics	IMPORT Semantics, TypeCount;
FROM Order	IMPORT Order;
FROM Dialog	IMPORT Dialog;

IMPORT GramMod, TreeMod1, EvalMod, EvalMod2, EvalMod3;
IMPORT GramC, GramYacc, TreeC1, EvalC, EvalC2, EvalC3;

CONST
   DefExtMc	= ".md"	;	(* file extensions for Modula (mc)	*)
   ImpExtMc	= ".mi"	;
   LisExtMc	= ".imp";

   DefExtC	= ".h"	;	(* file extensions for C		*)
   ImpExtC	= ".c"	;

VAR
   CgLib	,
   DefFile	,
   TreeFile	,
   EvalFile	,
   String	,
   PathS	: tString;
   Argument	,
   PathA	: ARRAY [0..255] OF CHAR;
   j		: SHORTCARD;
   ch		: CHAR;
   AllOptions	: tSet;
   HasArgs	: BOOLEAN;

PROCEDURE GenerateMacros;
   VAR TypeTabFile	: tFile;
   VAR s		: tString;
   VAR i		: tIdent;
   VAR j		: INTEGER;
   BEGIN
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	("TypeTab.c", String);	(* name of type table for C *)
   ELSE
      ArrayToString	("TypeTab.m", String);	(* name of type table for Modula *)
   END;
      Assign		(PathS, CgLib);
      Concatenate 	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      TypeTabFile := ReadOpen (PathA);

      ArrayToString	("yy" , PathS);		(* name of macro file *)
      GetString		(iModule, ModuleName);
      Concatenate	(PathS, ModuleName);
      ArrayToString	(".w", String);
      Concatenate	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      f := WriteOpen (PathA);

      WHILE NOT EndOfFile (TypeTabFile) DO
	 ReadL (TypeTabFile, s);
	 i := MakeIdent (s);
	 IF (i <= TypeCount) AND IsElement (i, TypeNames) THEN
	    Exclude (TypeNames, i);
	    !# ifndef begin! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	    !# ifndef close! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	    !# ifndef read! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	    !# ifndef write! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	    !# ifndef get! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	    !# ifndef put! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	    !# ifndef copy! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	    !# ifndef equal! WI (i); !!
	    ReadL (TypeTabFile, s);
	    WriteL (f, s);
	    !# endif!
	 ELSE
	    FOR j := 1 TO 8 DO
	       ReadNl (TypeTabFile);
	    END;
	 END;
      END;
      ReadClose (TypeTabFile);

      IF itTree <= TypeCount THEN Exclude (TypeNames, itTree); END;
      WHILE NOT IsEmpty (TypeNames) DO
	 i := Extract (TypeNames);
   IF IsElement (ORD ('c'), Options) THEN
	 !# ifndef begin! WI (i); !!
	 !# define begin! WI (i); !(a)!
	 !# endif!
	 !# ifndef close! WI (i); !!
	 !# define close! WI (i); !(a)!
	 !# endif!
	 !# ifndef read! WI (i); !!
	 !# define read! WI (i); !(a)	yyReadHex ((unsigned char *) & a, sizeof (a));!
	 !# endif!
	 !# ifndef write! WI (i); !!
	 !# define write! WI (i); !(a)	yyWriteHex ((unsigned char *) & a, sizeof (a));!
	 !# endif!
	 !# ifndef get! WI (i); !!
	 !# define get! WI (i); !(a)	yyGet ((char *) & a, sizeof (a));!
	 !# endif!
	 !# ifndef put! WI (i); !!
	 !# define put! WI (i); !(a)	yyPut ((char *) & a, sizeof (a));!
	 !# endif!
	 !# ifndef copy! WI (i); !!
	 !# define copy! WI (i); !(a, b)!
	 !# endif!
	 !# ifndef equal! WI (i); !!
	 !# define equal! WI (i); !(a, b)	memcmp ((char *) & a, (char *) & b, sizeof (a)) == 0!
	 !# endif!
   ELSE
	 !# ifndef begin! WI (i); !!
	 !# define begin! WI (i); !(a)!
	 !# endif!
	 !# ifndef close! WI (i); !!
	 !# define close! WI (i); !(a)!
	 !# endif!
	 !# ifndef read! WI (i); !!
	 !# define read! WI (i); !(a)	yyReadHex (a);!
	 !# endif!
	 !# ifndef write! WI (i); !!
	 !# define write! WI (i); !(a)	yyWriteHex (a);!
	 !# endif!
	 !# ifndef get! WI (i); !!
	 !# define get! WI (i); !(a)	yyGet (a);!
	 !# endif!
	 !# ifndef put! WI (i); !!
	 !# define put! WI (i); !(a)	yyPut (a);!
	 !# endif!
	 !# ifndef copy! WI (i); !!
	 !# define copy! WI (i); !(a, b)!
	 !# endif!
	 !# ifndef equal! WI (i); !!
	 !# define equal! WI (i); !(a, b)	yyIsEqual (a, b)!
	 !# endif!
   END;
      END;

   IF IsElement (ORD ('c'), Options) THEN
      !# ifndef begin! WI (itTree); !!
      !# define begin! WI (itTree); !(a)	a = ! WI (iNoTree); !;!
      !# endif!
      !# ifndef close! WI (itTree); !!
      !# define close! WI (itTree); !(a)	yyChild = a; a = ! WI (iNoTree); !; yyRelease! WI (iModule); ! (yyChild);!
      !# endif!
      !# ifndef read! WI (itTree); !!
      !# define read! WI (itTree); !(a)	yyRead! WI (iModule); ! (a);!
      !# endif!
      !# ifndef write! WI (itTree); !!
      !# define write! WI (itTree); !(a)	yyWrite! WI (iModule); ! (a);!
      !# endif!
      !# ifndef get! WI (itTree); !!
      !# define get! WI (itTree); !(a)	yyGet! WI (iModule); ! (a);!
      !# endif!
      !# ifndef put! WI (itTree); !!
      !# define put! WI (itTree); !(a)	yyPut! WI (iModule); ! (a);!
      !# endif!
      !# ifndef copy! WI (itTree); !!
      !# define copy! WI (itTree); !(a, b)	yyCopy! WI (iModule); ! (b, & a);!
      !# endif!
      !# ifndef equal! WI (itTree); !!
      !# define equal! WI (itTree); !(a, b)	IsEqual! WI (iModule); ! (a, b)!
      !# endif!
   ELSE
      !# ifndef begin! WI (itTree); !!
      !# define begin! WI (itTree); !(a)	a := ! WI (iNoTree); !;!
      !# endif!
      !# ifndef close! WI (itTree); !!
      !# define close! WI (itTree); !(a)	yyChild := a; a := ! WI (iNoTree); !; yyRelease! WI (iModule); ! (yyChild);!
      !# endif!
      !# ifndef read! WI (itTree); !!
      !# define read! WI (itTree); !(a)	yyRead! WI (iModule); ! (a);!
      !# endif!
      !# ifndef write! WI (itTree); !!
      !# define write! WI (itTree); !(a)	yyWrite! WI (iModule); ! (a);!
      !# endif!
      !# ifndef get! WI (itTree); !!
      !# define get! WI (itTree); !(a)	yyGet! WI (iModule); ! (a);!
      !# endif!
      !# ifndef put! WI (itTree); !!
      !# define put! WI (itTree); !(a)	yyPut! WI (iModule); ! (a);!
      !# endif!
      !# ifndef copy! WI (itTree); !!
      !# define copy! WI (itTree); !(a, b)	yyCopy! WI (iModule); ! (b, SYSTEM.ADR (a));!
      !# endif!
      !# ifndef equal! WI (itTree); !!
      !# define equal! WI (itTree); !(a, b)	IsEqual! WI (iModule); ! (a, b)!
      !# endif!
   END;
      WriteClose (f);
   END GenerateMacros;

PROCEDURE ReadTraceTab;
   VAR TraceTabFile	: tFile;
   VAR s		: tString;
   VAR t		: tTree;
   BEGIN
      TraceTabFile := ReadOpen ("TraceTab");	(* name of trace table *)
      IF TraceTabFile >= 0 THEN
	 WHILE NOT EndOfFile (TraceTabFile) DO
	    ReadL (TraceTabFile, s);
	    t := IdentifyClass (TreeRoot^.Ag.Classes, MakeIdent (s));
	    IF t # NoTree THEN
	       SetTrace (t);
	       ForallClasses (t^.Class.Extensions, SetTrace);
	    END;
	 END;
	 ReadClose (TraceTabFile);
      END;
   END ReadTraceTab;

PROCEDURE SetTrace (t: tTree);
   BEGIN INCL (t^.Class.Properties, Trace); END SetTrace;

PROCEDURE SmartOpen (FileName: tString): tFile;
   VAR PathS: tString;
   BEGIN
      IF IsElement (ORD ('7'), Options) THEN
	 ArrayToString	("yy", PathS);
	 Concatenate	(PathS, FileName);
	 Append		(PathS, 0C);
	 StringToArray	(PathS, PathA);
      ELSE
	 Append		(FileName, 0C);
	 StringToArray	(FileName, PathA);
      END;
      RETURN WriteOpen	(PathA);
   END SmartOpen;

PROCEDURE SmartClose (FileName: tString; f: tFile);
   VAR PathS: tString;
   BEGIN
      WriteClose	(f);
      IF IsElement (ORD ('7'), Options) THEN
	 ArrayToString	("gmdupd ", PathS);
	 Concatenate	(PathS, FileName);
	 ArrayToString	(" yy", String);
	 Concatenate	(PathS, String);
	 Concatenate	(PathS, FileName);
	 Append		(PathS, 0C);
	 StringToArray	(PathS, PathA);
	 j := System	(PathA);
      END;
   END SmartClose;

BEGIN
   AssignEmpty (CgLib);
   SourceFile [0] := 0C;
   ArgCount := GetArgCount () - 1;
   HasArgs := FALSE;

   CurArg := 0;
   LOOP
      INC (CurArg);
      IF CurArg > ArgCount THEN EXIT; END;
      GetArgument (CurArg, Argument);
      IF Argument [0] = '-' THEN 
	 IF Argument [1] = 'l' THEN 
	    AssignEmpty (CgLib);
	    j := 2;
	    LOOP
	       ch := Argument [j];
	       IF ch = 0C THEN EXIT; END;
	       Append (CgLib, ch);
	       INC (j);
	    END;
	    Append (CgLib, '/');
	 ELSE
	    j := 0;
	    LOOP
	       INC (j);
	       ch := Argument [j];
	       IF ch = 0C THEN
		  EXIT;
	       ELSIF ch = '?' THEN
		  Include (Options, ORD ('h'));
		  Include (Options, ORD ('H'));
	       ELSE
		  Include (Options, ORD (ch));
	       END;
	    END;
	    HasArgs := TRUE;
	 END;
      ELSIF Argument [0] = '?' THEN 
	 Include (Options, ORD ('h'));
	 Include (Options, ORD ('H'));
	 HasArgs := TRUE;
      ELSE
	 j := 0;
	 REPEAT
            ch := Argument [j];
	    SourceFile [j] := ch;
	    INC (j);
	 UNTIL ch = 0C;
	 EXIT;
      END;
   END;

   IF NOT HasArgs THEN				(* {} -> {a, A}		*)
      Include (Options, ORD ('a'));
      Include (Options, ORD ('A'));
   END;

   IF IsElement (ORD ('a'), Options) THEN	(* a -> {a-z, F, R, =} - {c, h, u, x, z} *)
      MakeSet (AllOptions, 127);
      FOR ch := 'a' TO 'z' DO
	 Include (AllOptions, ORD (ch));
      END;
      Include (AllOptions, ORD ('F'));
      Include (AllOptions, ORD ('R'));
      Include (AllOptions, ORD ('='));
      Exclude (AllOptions, ORD ('c'));
      Exclude (AllOptions, ORD ('h'));
      Exclude (AllOptions, ORD ('u'));
      Exclude (AllOptions, ORD ('x'));
      Exclude (AllOptions, ORD ('z'));
      Union (Options, AllOptions);
      ReleaseSet (AllOptions);
   END;

   IF IsElement (ORD ('k'), Options) OR		(* {k, q} -> o		*)
      IsElement (ORD ('q'), Options) THEN
      Include (Options, ORD ('o'));
   END;

   IF IsElement (ORD ('w'), Options) OR		(* {w, p, f, k, t, b, y} -> , = Mark *)
      IsElement (ORD ('p'), Options) OR
      IsElement (ORD ('f'), Options) OR
      IsElement (ORD ('k'), Options) OR
      IsElement (ORD ('t'), Options) OR
      IsElement (ORD ('b'), Options) OR
      IsElement (ORD ('y'), Options) THEN
      Include (Options, ORD (','));
   END;

   IF IsElement (ORD ('w'), Options) OR		(* {w, r, p, g} -> ; = TreeStore *)
      IsElement (ORD ('r'), Options) OR
      IsElement (ORD ('p'), Options) OR
      IsElement (ORD ('g'), Options) THEN
      Include (Options, ORD (';'));
   END;

   IF IsElement (ORD ('A'), Options) THEN	(* A -> {D, I}		*)
      Include (Options, ORD ('D'));
      Include (Options, ORD ('I'));
   END;

   IF IsElement (ORD ('T'), Options) OR		(* {T, X, Y, Z} -> I	*)
      IsElement (ORD ('X'), Options) OR
      IsElement (ORD ('Y'), Options) OR
      IsElement (ORD ('Z'), Options) THEN
      Include (Options, ORD ('I'));
   END;

   IF IsElement (ORD ('I'), Options) OR		(* {I, V, M, P, S, N, O, G, E, C, J, x, z, u} -> . = Order *)
      IsElement (ORD ('V'), Options) OR
      IsElement (ORD ('M'), Options) OR
      IsElement (ORD ('P'), Options) OR
      IsElement (ORD ('S'), Options) OR
      IsElement (ORD ('N'), Options) OR
      IsElement (ORD ('O'), Options) OR
      IsElement (ORD ('G'), Options) OR
      IsElement (ORD ('E'), Options) OR
      IsElement (ORD ('C'), Options) OR
      IsElement (ORD ('J'), Options) OR
      IsElement (ORD ('x'), Options) OR
      IsElement (ORD ('z'), Options) OR
      IsElement (ORD ('u'), Options) THEN
      Include (Options, ORD ('.'));
   END;

   IF IsElement (ORD ('x'), Options) OR		(* {x, z, u} -> B	*)
      IsElement (ORD ('z'), Options) OR
      IsElement (ORD ('u'), Options) THEN
      Include (Options, ORD ('B'));
   END;

   IF IsElement (ORD ('T'), Options) THEN	(* T -> {X, Z}		*)
      Include (Options, ORD ('X'));
      Include (Options, ORD ('Z'));
   END;

   IF IsElement (ORD ('X'), Options) THEN	(* X -> Y		*)
      Include (Options, ORD ('Y'));
   END;

   IF IsElement (ORD ('h'), Options) THEN
      Exclude (Options, ORD ('h'));
      f := StdOutput;
      !!
      !usage: cg [-options] [-ldir] [files]!
      !!
      !options for tree/graph module!
      !!
      ! a generate all except -ch (default)!
      ! n generate node constructors    procedures n<node> (node)!
      ! m generate node constructors    procedures m<node> (make)!
      ! f generate node/graph destroyer procedure ReleaseTREE (free)!
      ! F generate general    destroyer procedure ReleaseTREEModule (FREE)!
      ! o generate ascii  node  writer  procedure WriteTREENode (output)!
      ! r generate ascii  graph reader  procedure ReadTREE!
      ! w generate ascii  graph writer  procedure WriteTREE!
      ! g generate binary graph reader  procedure GetTREE!
      ! p generate binary graph writer  procedure PutTREE!
      ! R generate list reverser        procedure ReverseTREE!
      ! t generate top down  traversal  procedure TraverseTREETD!
      ! b generate bottom up traversal  procedure TraverseTREEBU!
      ! y generate graph copy           procedure CopyTREE!
      ! k generate graph checker        procedure CheckTREE!
      ! q generate graph browser        procedure QueryTREE!
      ! = generate tree equality test   procedure IsEqualTREE!
      ! d generate definition     module!
      ! i generate implementation module!
      ! s generate import statements!
      ! 4 generate tree/graph description in file TREE.TS!
      ! 6 generate # line directives!
      ! 7 touch output files only if necessary!
      ! 8 report storage consumption!
      ! c generate C code (default is Modula-2)!
      ! h print help information for tree/graph module!
      ! H print help information for evaluator  module!
      ! -ldir specify the directory dir where cg finds its tables!
      !!
      !options for scanner and parser interface!
      !!
      ! x generate scanner specification!
      ! z generate parser  specification for lalr!
      ! u generate parser  specification for yacc!
      ! v omit actions in the generated parser specifications!
      ! j allow undefined node types; define implicitly as terminals!
   (* ! e free! *)
   END;

   IF IsElement (ORD ('H'), Options) THEN
      Exclude (Options, ORD ('H'));
      f := StdOutput;
      !!
      !usage: cg [-options] [-ldir] [files]!
      !!
      !options for evaluator module!
      !!
      ! A generate all, same as -DI (default)!
      ! D generate definition     module!
      ! I generate implementation module!
      ! L generate a (lazy) evaluator for WAG (default OAG)!
      ! W suppress warnings!
      ! B allow missing attribute computations in extended node types!
      ! V print visit sequences!
      ! M print summary of all node types (rules) from source!
      ! P print dependency relations DP!
      ! S print dependency relations SNC!
      ! N print dependency relations DNC!
      ! O print dependency relations OAG!
      ! G print attribute instances sorted by declaration order!
      ! E print attribute instances sorted by evaluation order!
      ! C print dependencies introduced for total order!
      ! T generate evaluator with trace output (all actions, T = XZ)!
      ! U trace only node types specified in file TraceTab!
      ! X trace attribute evaluation actions with    values!
      ! Y trace attribute evaluation actions without values!
      ! Z trace visit actions!
      ! J start dialog system!
      ! Q browse internal data structure!
      ! 0 optimize attribute storage!
      ! 1 print inserted copy rules!
      ! 2 print inherited attribute computation rules!
      ! 3 print attribute storage assignment!
      ! 5 generate code to check for cyclic dependencies!
      ! 6 generate # line directives!
      ! 7 touch output files only if necessary!
      ! 8 report storage consumption!
      ! 9 generate code to measure stack size!
      ! c generate C code (default is Modula-2)!
   (* ! . run order! *)
   (* ! , generate procedure yyMark! *)
   (* ! ; generate "TreeStore"! *)
   (* ! / follow as early as possible strategy instead of as late as possible! *)
      ! H print help information for evaluator  module!
      ! h print help information for tree/graph module!
      ! -ldir specify the directory dir where cg finds its tables!
   (* ! K free! *)
      !!
      !implications!
      !!
      ! {}              -> {a, A}!
      ! a               -> {a-z, F, R} - {c, e, h, u, x, z}!
      ! A               -> {D, I}!
      ! {L, T, X, Y, Z} -> I!
      ! T               -> {X, Z}!
   END;

   IF NOT IsEmpty (Options) THEN
      ArrayToString	(ScanTabName, String);	(* name of scanner table *)
      Assign		(PathS, CgLib);
      Concatenate	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, ScanTabName);

      ArrayToString	(ParsTabName, String);	(* name of parser table *)
      Assign		(PathS, CgLib);
      Concatenate	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, ParsTabName);

   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	("int", String);
   ELSE
      ArrayToString	("INTEGER", String);
   END;
      iInteger := MakeIdent (String);

      IF SourceFile [0] # 0C THEN
	 BeginFile (SourceFile);
	 ArrayToString (SourceFile, String);
	 Attribute.Position.File := MakeIdent (String);
      END;
      StoreMessages	(TRUE);
      ErrorCount := Parser ();
      BeginTree2;
      Semantics		(TreeRoot);
      IF ErrorCount > 0 THEN WriteMessages (StdError); CloseIO; Exit (1); END;
   END;

   IF IsElement (ORD ('x'), Options) THEN
      IF TreeRoot^.Ag.ScannerName = NoIdent THEN
	 ArrayToString	("Scanner", PathS);
      ELSE
	 GetString (TreeRoot^.Ag.ScannerName, PathS);
      END;
      ArrayToString	(".rpp", String);
      Concatenate	(PathS, String);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      GramC.ScanSpec	(TreeRoot);
   ELSE
      GramMod.ScanSpec	(TreeRoot);
   END;
      SmartClose	(PathS, f);
   END;

   IF IsElement (ORD ('z'), Options) THEN
      GetString		(TreeRoot^.Ag.ParserName, ModuleName);
      Assign		(PathS, ModuleName);
      ArrayToString	(".lalr", String);
      Concatenate	(PathS, String);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      GramC.ParsSpec	(TreeRoot);
   ELSE
      GramMod.ParsSpec	(TreeRoot);
   END;
      SmartClose	(PathS, f);
   ELSIF IsElement (ORD ('u'), Options) THEN
      GetString		(TreeRoot^.Ag.ParserName, ModuleName);
      Assign		(PathS, ModuleName);
      ArrayToString	(".y", String);
      Concatenate	(PathS, String);
      f := SmartOpen	(PathS);
      GramYacc.ParsSpec	(TreeRoot);
      SmartClose	(PathS, f);
   END;

   IF IsElement (ORD ('.'), Options) THEN
      Order		(TreeRoot);
   END;

      WriteMessages	(StdError);
      StoreMessages	(TRUE);

   IF IsElement (ORD ('Q'), Options) THEN
      QueryTree		(TreeRoot);
   END;

   IF IsElement (ORD ('J'), Options) THEN
      Dialog		(TreeRoot);
   END;

      IF ErrorCount > 0 THEN CloseIO; Exit (1); END;

   IF IsElement (ORD ('i'), Options) OR
      IsElement (ORD ('X'), Options) THEN
      GenerateMacros;
   END;

   IF IsElement (ORD ('d'), Options) THEN
      GetString		(iModule, ModuleName);
      Assign		(PathS, ModuleName);
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	(DefExtC , String);
   ELSE
      ArrayToString	(DefExtMc, String);
   END;
      Concatenate	(PathS, String);
      Assign		(DefFile, PathS);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      TreeC1.TreeDefC	(TreeRoot);
   ELSE
      TreeMod1.TreeDefMod (TreeRoot);
   END;
      SmartClose	(PathS, f);

   IF NOT IsElement (ORD ('c'), Options) THEN
      ArrayToString	("gmdcpp ", PathS);		(* call cpp *)
      Concatenate	(PathS, DefFile);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      j := System	(PathA);
   END;
   END;

   IF IsElement (ORD ('4'), Options) THEN
      GetString		(ViewName, PathS);
      ArrayToString	(".TS", String);
      Concatenate	(PathS, String);
      f := SmartOpen	(PathS);
      WriteIdent	(f, iModule); WriteNl (f);
      PutTree2		(f, TreeRoot^.Ag.Classes);
      SmartClose	(PathS, f);
   END;

   IF IsElement (ORD ('i'), Options) THEN
      GetString		(iModule, ModuleName);
      Assign		(PathS, ModuleName);
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	(ImpExtC , String);
   ELSE
      ArrayToString	(ImpExtMc, String);
   END;
      Concatenate	(PathS, String);
      Assign		(TreeFile, PathS);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      TreeC1.TreeImplC	(TreeRoot);
   ELSE
      TreeMod1.TreeImplMod (TreeRoot);
   END;
      SmartClose	(PathS, f);

   IF NOT IsElement (ORD ('c'), Options) THEN
      ArrayToString	("gmdcpp ", PathS);		(* call cpp *)
      Concatenate	(PathS, TreeFile);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      j := System	(PathA);
   END;
   END;

   IF IsElement (ORD ('s'), Options) AND NOT IsElement (ORD ('c'), Options) THEN
      GetString		(iModule, ModuleName);
      Assign		(PathS, ModuleName);
      ArrayToString	(LisExtMc, String);
      Concatenate	(PathS, String);
      f := SmartOpen	(PathS);
      TreeMod1.ImportList (TreeRoot);
      SmartClose	(PathS, f);
   END;

   IF IsElement (ORD ('U'), Options) THEN
      ReadTraceTab;
   ELSIF NOT IsEmpty (Options) THEN
      ForallClasses	(TreeRoot^.Ag.Classes, SetTrace);
   END;

   IF IsElement (ORD ('D'), Options) THEN
      GetString		(TreeRoot^.Ag.EvalName, ModuleName);
      Assign		(PathS, ModuleName);
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	(DefExtC , String);
   ELSE
      ArrayToString	(DefExtMc, String);
   END;
      Concatenate	(PathS, String);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      EvalC.EvalDefC	(TreeRoot);
   ELSE
      EvalMod.EvalDefMod (TreeRoot);
   END;
      SmartClose	(PathS, f);
   END;

   IF IsElement (ORD ('I'), Options) THEN
      GetString		(TreeRoot^.Ag.EvalName, ModuleName);
      Assign		(PathS, ModuleName);
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	(ImpExtC , String);
   ELSE
      ArrayToString	(ImpExtMc, String);
   END;
      Concatenate	(PathS, String);
      Assign		(EvalFile, PathS);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      IF IsElement (ORD ('L'), Options) THEN
	 EvalC3.EvalImplC (TreeRoot);
      ELSIF IsElement (ORD ('0'), Options) THEN
	 EvalC2.EvalImplC (TreeRoot);
      ELSE
	 EvalC.EvalImplC (TreeRoot);
      END;
   ELSE
      IF IsElement (ORD ('L'), Options) THEN
	 EvalMod3.EvalImplMod (TreeRoot);
      ELSIF IsElement (ORD ('0'), Options) THEN
	 EvalMod2.EvalImplMod (TreeRoot);
      ELSE
	 EvalMod.EvalImplMod (TreeRoot);
      END;
   END;
      SmartClose	(PathS, f);

   IF NOT IsElement (ORD ('c'), Options) THEN
      ArrayToString	("gmdcpp ", PathS);		(* call cpp *)
      Concatenate	(PathS, EvalFile);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      j := System	(PathA);
   END;
   END;

   IF NOT IsElement (ORD ('c'), Options) THEN
      IF IsElement (ORD ('i'), Options) OR
	 IsElement (ORD ('X'), Options) THEN
	 ArrayToString	("gmdrm yy" , PathS);		(* name of macro file *)
	 GetString	(iModule, ModuleName);
	 Concatenate	(PathS, ModuleName);
	 ArrayToString	(".w", String);
	 Concatenate	(PathS, String);
	 Append		(PathS, 0C);
	 StringToArray	(PathS, PathA);
	 j := System	(PathA);
      END;
   END;

   IF IsElement (ORD ('8'), Options) THEN
      WriteNl (StdError);
      WriteS  (StdError, "Memory"); WriteI (StdError, MemoryUsed, 8);
      WriteS  (StdError, "  Heap"); WriteI (StdError, HeapUsed  , 8);
      WriteNl (StdError);
   END;
   WriteMessages (StdError);
   CloseIO; Exit (0);
END cg.
