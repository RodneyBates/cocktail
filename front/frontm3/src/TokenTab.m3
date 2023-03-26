(* map tokens to internal representation *)

(* $Id: TokenTab.mi,v 2.2 1992/08/07 15:13:51 grosch rel $ *)

(* $Log: TokenTab.mi,v $
 * Revision 2.2  1992/08/07  15:13:51  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:26:41  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.2  90/06/11  18:45:44  grosch
 * layout improvements
 * 
 * Revision 1.1  89/01/26  19:03:26  vielsack
 * better position handling for nonterminals
 * 
 * Revision 1.0  88/10/04  14:27:23  vielsack
 * Initial revision
 * 
 *)

 UNSAFE MODULE TokenTab;

(* Umsetzung der Vokabularzeichen (tIdent) in eine interne Darstellung
   (Vocabulary). Zusaetzlich besteht die Moeglichkeit, weitere Information
   ueber ein Vokabularzeichen aufzunehmen (Special). *)


IMPORT Word;
FROM Strings    IMPORT ArrayToString, TextToString, tString;
FROM Idents     IMPORT MakeIdent,tIdent,GetString;
FROM FrontErrors        IMPORT eFatal, eRestriction, eIdent, eString, eInternal, ErrorMessageI;
FROM Positions  IMPORT NoPosition;

CONST
    eNoIntCode          = 25;
    eTokenOverflow      = 26;

     (* Von der Symboltabelle duerfen nur Werte bis zu dieser Groesse geliefert werden. *)

    MaxTokens           = cMAXNonTerm;
    NoValue             = MaxTokens;
    DefValue            = MaxTokens + 1;

TYPE Symbols            = [0..MaxTokens];

VAR 
    (* Unter ExToInt[i] steht die interne Darstellung des Eintrags i der Symboltabelle *)

    ExToInt     : ARRAY Symbols OF Vocabulary;

    (* Unter IntToEx[i] steht der Eintrag in der Symboltabelle, die
       der internen Darstellung i entspricht *)
    
    ExToPos     : ARRAY Symbols OF PosType;
    ExPosSet    : ARRAY Symbols OF BOOLEAN;

    (* Fuer jedes Symbol wird die kleinste Position an der es auftritt festgehalten *)

    IntToEx     : ARRAY Vocabulary OF Symbols; 

    (* Eintrag der aktuellen Prioritaet eines Vocabularzeichens. Auf 0 initialisiert. *)

    PrioField   : ARRAY Vocabulary OF Prio;

    (* DefaultVoc enthaelt das zuletzt und damit hoechste mit Default-
       nummer eingetragene Terminal *)

    DefaultVoc  : [0..cMAXTerm+1];
    i           : Word.T;

    GetNextNonTerminalAllowed   : BOOLEAN;
    Actualnt    : [MINNonTerm..cMAXNonTerm];

    (* Variablen fuer main section *)
    ter         : Terminal;
    err         : TokenError;
    s           : tString;
    pos         : PosType;

  PROCEDURE MakeTerm (sym: tIdent; VAR ter: Terminal; VAR Error: TokenError; pos: PosType) =
  
  (* Fuege sym als NEUES Terminal in TokenTab mit vorgegebener Codierung
     ter ein. Falls s bereits in der TokenTab steht, wird der alte Code
     zurueckgeliefert und Error auf SymbolExists gesetzt.
     Error = CodeExists, falls der angegebene Code bereits vergeben ist . *)

  BEGIN
    IF sym > cMAXNonTerm THEN
      Error := TokenError.OutOfRange;
    ELSIF ExToInt[sym] # NoValue THEN 
      (* Es wurde schon ein Eintrag  mit vorgenommen *)
      Error:= TokenError.SymbolExists;
      ter  := ExToInt[sym];
    ELSIF IntToEx[ter] # NoValue THEN
      (* Es wurde einEintrag mit MakeDefTerm gemacht *)
      Error := TokenError.CodeExists;
    ELSE
      ExToInt[sym]      := ter;
      IntToEx[ter]      := sym;
      Error             := TokenError.NoError;
      ExToPos[sym]      := pos;
      IF ter > MAXTerm THEN
        MAXTerm := ter;
      END;
    END;
  END MakeTerm;

  PROCEDURE MakeDefTerm (VAR sym: tIdent; VAR Error: TokenError; pos: PosType) =

  (* Fuege sym als NEUES Terminal in TokenTab ohne interne Codierung
     ein. Die Codierung muss nach Abschluss aller Eintraege in die
     TokenTab mit CompleteDefTerm nachgeholt werden. 
     Falls s bereits in der TokenTab steht, wird der alte Code zurueck-
     geliefert und Error auf SymbolExists gesetzt. *)

  BEGIN
    IF (ExToInt [sym] # NoValue) THEN
     (* sym steht bereits in der TokenTab  *) 
      Error := TokenError.SymbolExists;
    ELSE
      ExToInt[sym]     := DefValue;
      Error            := TokenError.NoError;
      ExToPos[sym]     := pos;
    END;
  END MakeDefTerm;

  PROCEDURE CompleteDefTerm (sym: tIdent; VAR Error: TokenError) =

  (* Traegt die interne Codierung fuer bereits mit MakeDefTerm eingetragene
     Terminale nach .Moegliche Fehler:
     Error = NotExists     Noch gar nicht eingetragen
             CodeExists    Schon vollstaendig eingetragen
             NonTerm   sym ist Codierung fuer Nichtterminal; *)
  
  BEGIN
    IF ExToInt[sym] = NoValue THEN
      (* Symbol noch gar nicht eingetragen *)
      Error := TokenError.NotExists;
    ELSIF ExToInt[sym] # DefValue THEN
      (* Symbol schon vollstaendig eingetragen *)
      IF GetTokenType(ExToInt[sym]) = TokenType.NonTerm THEN
        Error := TokenError.NotTerm;
      ELSE
        Error := TokenError.CodeExists;
      END;
    ELSE
      (* alles ok *)
      NextDefault(); (* DefaultVoc weiterschalten *)
      IF DefaultVoc <= cMAXTerm THEN
        ExToInt[sym] := DefaultVoc;
        IntToEx[DefaultVoc] := sym;
        IF DefaultVoc > MAXTerm THEN
           MAXTerm := DefaultVoc;
        END;
        Error              := TokenError.NoError;
      ELSE
        ErrorMessageI(eTokenOverflow,eRestriction,NoPosition,eIdent,ADR(sym));
      END;
    END;
  END CompleteDefTerm;
  
  PROCEDURE MakeVoc (sym: tIdent; symPos: PosType): Vocabulary =

  (* falls s bereits vorhanden:
        die Codierung von sym wird zurueckgeliefert
     sonst:
        s wird als NichtTerminal in die TokenTab eingetragen und die
        Codierung zurueckgeliefert.
     Bei Tabellenueberlauf wird Error = TokenOverflow. *)

  BEGIN
    IF ExToInt[sym] = DefValue THEN
      ErrorMessageI(eNoIntCode,eFatal,symPos, eIdent, ADR(sym));
    ELSIF
      ExToInt[sym] # NoValue THEN (* s bereits vorhanden *)

      (* ist neue Position kleiner als bisher bekannte? *)

      IF (ExToPos[sym].Line > symPos.Line) OR
         (   (ExToPos[sym].Line = symPos.Line)
         AND (ExToPos[sym].Column > symPos.Column) ) THEN
        
        (* ist neue Position gueltig? *)

        IF (symPos.Line # 0) AND (symPos.Column # 0) THEN

          (* halte Positon fuer evtl. Fehlermeldungen fest *)

          ExToPos[sym] := symPos

        END;
      END;

      RETURN ExToInt[sym];
    ELSE
      (* Noch kein Eintrag *)
      INC(MAXNonTerm);
      IF MAXNonTerm >= MaxTokens THEN
        ErrorMessageI (eTokenOverflow,eRestriction,symPos, eIdent, ADR(sym));
      ELSE
        ExToPos[sym] := symPos;
        ExToInt[sym] := MAXNonTerm;
        IntToEx[MAXNonTerm] := sym ;
        RETURN MAXNonTerm;
      END;
    END;
  END MakeVoc;

  PROCEDURE SetNontermPos (sym: tIdent; pos: PosType) =

  (* setze Position eines Nichtterminals *)

  BEGIN
    IF NOT ExPosSet [sym] THEN
      ExToPos [sym] := pos;
      ExPosSet [sym] := TRUE;
    END;
  END SetNontermPos;
 
  PROCEDURE GetTokenType (voc: Vocabulary): TokenType =

  (* liefert den Typ des Tokens voc zurueck *)
  BEGIN
    IF (IntToEx[voc] = NoValue) OR (voc >= MaxTokens) THEN
      RETURN TokenType.None;
    ELSIF voc <= cMAXTerm THEN
      RETURN TokenType.Term;
    ELSE
      RETURN TokenType.NonTerm;
    END;
  END GetTokenType;

PROCEDURE SymbolToToken (sym: tIdent; VAR Error: TokenError): Vocabulary =
  
  (* liefert die zum SymboltabellenEintrag sym gehoerige interne Darstellung*)
  (* Moegliche Fehler:
     Error = NotExists    Es existiert ueberhaupt kein Eintrag
     Error = NoIntCode    Code muss noch mit CompleteDefToken eingetragen
                          werden.
     Error = NoError      Alles in Ordnung    *)

BEGIN 
  IF ExToInt[sym] = NoValue THEN
    Error := TokenError.NotExists;
  ELSIF ExToInt[sym] = DefValue THEN
    Error := TokenError.NoIntCode;
  ELSE
    Error := TokenError.NoError;
  END;
  RETURN ExToInt[sym];
END SymbolToToken;

PROCEDURE  TokenToSymbol (voc: Vocabulary; VAR Error: TokenError):tIdent =
  
  (* liefert die zum TokenTabeintrag voc gehoerige Darstellung
     in der Symboltabelle *)
  (* Moegliche Fehler:
     Error = NotExists    Es existiert ueberhaupt kein Eintrag
                          werden.
     Error = NoError      Alles in Ordnung    *)

BEGIN 
  IF IntToEx[voc] = NoValue THEN
    Error := TokenError.NotExists;
  ELSE
    Error := TokenError.NoError;
  END;
  RETURN IntToEx[voc];
END TokenToSymbol;
  
PROCEDURE GetTokenPos (voc: Vocabulary; VAR pos: PosType) =
VAR sym: tIdent;
BEGIN
  sym := IntToEx[voc];
  IF sym = NoValue THEN
    pos.Line := 0;
    pos.Column := 0;
  ELSE
    pos := ExToPos [sym];
  END;
END GetTokenPos;
  
  PROCEDURE PutPrio (voc: Vocabulary; p: Prio) =

  (* Setzen der Prioritaet von voc auf p *)
  BEGIN
    PrioField[voc] := p;
  END PutPrio;

  PROCEDURE GetPrio (voc: Vocabulary):Prio =

  (* liefert die mit PutPriority eingetragene Prioritaet von voc.
     Ist nichts eingetragen, wird 0 zurueckgegeben. *)
  BEGIN
    RETURN PrioField[voc];
  END GetPrio;

  PROCEDURE NextDefault() =
  BEGIN
    WHILE (IntToEx[DefaultVoc] # NoValue) AND
          (DefaultVoc < (cMAXTerm+1)) DO
      INC(DefaultVoc);
    END;
  END NextDefault;

  PROCEDURE InitTokenTable() =
  BEGIN
    GetNextNonTerminalAllowed := FALSE;
    FOR i := 0 TO MaxTokens DO
      IntToEx[i] := NoValue;
      ExToInt[i] := NoValue;
      ExPosSet[i] := FALSE;
      PrioField[i] := 0;
    END;
    DefaultVoc := 1;
    MAXNonTerm := cMAXTerm;
    TextToString ("_EndOfFile", s);
    ter := EndOfToken;
    pos.Line := 0;
    pos.Column := 0;
    MakeTerm (MakeIdent(s),ter,err,pos);
    IF err # TokenError.NoError THEN
      ErrorT ("TokenTab.InitTokenTable");
    END;
    MAXTerm := 0;
  END InitTokenTable;

  PROCEDURE ErrorT (Msg: TEXT) =
  VAR s: tString;
  BEGIN
    TextToString (Msg, s);
    ErrorMessageI (eInternal, eFatal, NoPosition, eString, ADR (s));
  END ErrorT;

BEGIN
END TokenTab.

