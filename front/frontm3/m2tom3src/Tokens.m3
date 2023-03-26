(* handle token section *)

(* $Id: Tokens.mi,v 2.2 1992/08/07 15:13:51 grosch rel $ *)

(* $Log: Tokens.mi,v $
 * Revision 2.2  1992/08/07  15:13:51  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:26:43  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.1  90/06/11  18:45:48  grosch
 * layout improvements
 * 
 * Revision 1.0	 88/10/04  14:27:26  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE Tokens;

FROM Lists	IMPORT MakeList, tList;
FROM Strings	IMPORT tString, ArrayToString;
FROM StringMem	IMPORT tStringRef;
FROM TokenTab	IMPORT Vocabulary,PosType;
FROM Memory	IMPORT Alloc;
FROM Idents	IMPORT tIdent;

FROM TokenTab	IMPORT Terminal, MakeDefTerm,MakeTerm,CompleteDefTerm,TokenError;
FROM Errors	IMPORT eFatal, eError, eIdent, eString, eInternal, ErrorMessageI;
FROM Positions	IMPORT NoPosition;

  CONST
    eTokenDeclTwice	= 30;
    eCodeExists		= 31;

  TYPE
    Declarations = UNTRACED BRANDED REF  Declaration;

    Declaration = RECORD
	Token	  : tIdent;
	TokenPos  : PosType;
	 HasCoding : BOOLEAN; 
	  
	    EQUALPos  : PosType;
	    NumberPos : PosType;
	
	Comment	  : tList;
	CommPos	  : PosType;
	Next	  : Declarations;
      END;

  VAR
    TokensVars :
      RECORD
	GlobalComment: tList;
	GlobalCommPos: PosType;
	TOKENPos     : PosType;
	TOKENComment : tList;
	TOKENCommPos : PosType;
      END;
    
    StartDecl : Declarations;
    RDecl : Declarations;
    WDecl : Declarations;
    ReadyForReading : BOOLEAN;

  PROCEDURE  MakeGlobalHeader
    ( GlobalComment : tList;
      GlobalCommPos : PosType) =
  
  BEGIN
    TokensVars.GlobalComment := GlobalComment; 
    TokensVars.GlobalCommPos := GlobalCommPos;
  END MakeGlobalHeader;


  PROCEDURE  MakeTokensHeader
    ( TOKENPos	    : PosType;
      TOKENComment  : tList;
      TOKENCommPos  : PosType) =
  
  (* Speichert globale Informationen ueber den zu TOKEN gehoerigen
     Abschnitt *)

  BEGIN
    TokensVars.TOKENPos	     := TOKENPos;
    TokensVars.TOKENComment  := TOKENComment;
    TokensVars.TOKENCommPos  := TOKENCommPos;  
  END MakeTokensHeader;


  PROCEDURE MakeDeclaration
    (Token	: tIdent;
     TokenPos	: PosType; 
     HasCoding	: BOOLEAN;
     EQUALPos	: PosType;
     Number	: Terminal;
     NumberPos	: PosType;
     Comment	: tList;
     CommPos	: PosType) =
  
  (* Fuege neue Deklaration ein *)

  VAR HDecl : Declarations;
      Error : TokenError;

  BEGIN
    IF ReadyForReading THEN
      ERROR ("MakeDeclaration: do not write");
    END;
    HDecl := Alloc(BYTESIZE(Declaration));
    IF HDecl = NIL THEN
      ERROR ("MakeDeclaration: Heap overflow");
    END;
    HDecl^.Token       := Token;
    HDecl^.TokenPos    := TokenPos;
    HDecl^.HasCoding   := HasCoding;
    HDecl^.Next	       := NIL;
    IF HasCoding THEN
      MakeTerm(Token,Number,Error,TokenPos);
      IF Error = TokenError.SymbolExists THEN
	ErrorMessageI (eTokenDeclTwice,eError,TokenPos,eIdent, ADR (Token));
	RETURN;
      ELSIF Error = TokenError.CodeExists THEN
	ErrorMessageI (eCodeExists,eError,TokenPos,eIdent,ADR(Token));
	RETURN;
      END;
      HDecl^.EQUALPos  := EQUALPos;
      HDecl^.NumberPos := NumberPos;
    ELSE
      MakeDefTerm(Token,Error,TokenPos);
      IF Error = TokenError.SymbolExists THEN
	ErrorMessageI(eTokenDeclTwice,eError,TokenPos,eIdent,ADR(Token));
	RETURN;
      END;
    END;
    HDecl^.Comment     := Comment;
    HDecl^.CommPos     := CommPos;
    IF WDecl = NIL THEN
      (* Einfuegen des ersten Elementes *)
      StartDecl := HDecl;
    ELSE
      WDecl^.Next := HDecl;
    END;
    WDecl := HDecl;
  END MakeDeclaration;


  PROCEDURE CompleteDeclarations() =

  VAR Error : TokenError;

  BEGIN
    RDecl := StartDecl;
    WHILE RDecl # NIL DO
      IF NOT RDecl^.HasCoding THEN
	CompleteDefTerm(RDecl^.Token,Error);
	IF Error = TokenError.NotExists THEN
	  ERROR ("CompleteDeclarations: token does not exists");
	ELSIF Error = TokenError.CodeExists THEN
	  ERROR ("CompleteDeclarations: token already complete");
	ELSIF Error = TokenError.NotTerm  THEN
	  ERROR ("CompleteDeclarations: token is nonterminal");
	END;
      END;
      RDecl := RDecl^.Next;
    END;
    RDecl := StartDecl;
    ReadyForReading := TRUE;
  END CompleteDeclarations;


  PROCEDURE  GetGlobalHeader
    (VAR GlobalComment : tList;
     VAR GlobalCommPos : PosType) =

  (* liest die mit MakeGlobalHeader abgelegte Information *)

  BEGIN
    GlobalComment := TokensVars.GlobalComment; 
    GlobalCommPos := TokensVars.GlobalCommPos;
  END GetGlobalHeader;


  PROCEDURE  GetTokensHeader
    (VAR TOKENPos      : PosType;
     VAR TOKENComment  : tList;
     VAR TOKENCommPos  : PosType) =

  (* liest die mit MakeTokensHeader abgelegte Information *)

  BEGIN
    TOKENPos	  := TokensVars.TOKENPos;
    TOKENComment  := TokensVars.TOKENComment;
    TOKENCommPos  := TokensVars.TOKENCommPos;  
  END GetTokensHeader;

   
  PROCEDURE GetDeclaration
    (VAR Token	    : tIdent;
     VAR TokenPos   : PosType; 
     VAR HasCoding  : BOOLEAN;
     VAR EQUALPos   : PosType;
     VAR NumberPos  : PosType;
     VAR Comment    : tList;
     VAR CommPos    : PosType) : BOOLEAN  =
  
  (* liefert die naechste Deklaration, falls vorhanden. Ansonsten wird
     FALSE zurueckgegeben.  *)

  BEGIN
    IF NOT ReadyForReading THEN
      ERROR ("GetDeclaration: do not read");
    END;
    IF RDecl = NIL THEN
      RETURN FALSE;
    ELSE
      Token	  := RDecl^.Token;
      TokenPos	  := RDecl^.TokenPos;
      HasCoding	  := RDecl^.HasCoding;
      IF HasCoding THEN
	EQUALPos  := RDecl^.EQUALPos;
	NumberPos := RDecl^.NumberPos;
      ELSE
	EQUALPos.Line	 := 0;
	EQUALPos.Column	 := 0;
	NumberPos.Line	 := 0; 
	NumberPos.Column := 0; 
      END;
      Comment := RDecl^.Comment;
      CommPos := RDecl^.CommPos;
      RDecl   := RDecl^.Next;
      RETURN TRUE;
    END;
  END GetDeclaration;

  PROCEDURE ERROR (READONLY a: ARRAY OF CHAR) =
  VAR s: tString;
  BEGIN
    ArrayToString (a, s);
    ErrorMessageI (eInternal, eFatal, NoPosition, eString, ADR (s));
  END ERROR;

BEGIN
  StartDecl := NIL;  (* Anker fuer Declaration *)
  WDecl	    := NIL;  (* Schreibzeiger *)
  RDecl	    := NIL;  (* Lesezeiger    *)
  ReadyForReading := FALSE;
  WITH m2tom3_with_1=TokensVars DO
    MakeList (m2tom3_with_1.GlobalComment);
    m2tom3_with_1.GlobalCommPos.Line := 0;
    m2tom3_with_1.GlobalCommPos.Column := 0;
    MakeList (m2tom3_with_1.TOKENComment);
    m2tom3_with_1.TOKENCommPos.Line := 0;
    m2tom3_with_1.TOKENCommPos.Column := 0;
  END;
END Tokens.

