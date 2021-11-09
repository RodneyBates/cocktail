INTEGER
# define beginINTEGER(a)	
# define closeINTEGER(a)	
# define readINTEGER(a)		a := IO.ReadI (yyf);
# define writeINTEGER(a)	Wr.PutText(yyf,Fmt.Int(a));
# define getINTEGER(a)		yyGet (a);
# define putINTEGER(a)		yyPut (a);
# define copyINTEGER(a, b)	a := b
# define equalINTEGER(a, b)	a = b
CARDINAL
# define beginCARDINAL(a)	
# define closeCARDINAL(a)	
# define readCARDINAL(a)	a := Lex.Unsigned (yyf);
# define writeCARDINAL(a)	Wr.PutText(yyf,Fmt.Unsigned(a);
# define getCARDINAL(a)		yyGet (a);
# define putCARDINAL(a)		yyPut (a);
# define copyCARDINAL(a, b)	a := b
# define equalCARDINAL(a, b)	a = b
REAL
# define beginREAL(a)		
# define closeREAL(a)		
# define readREAL(a)		a := Lex.Real(yyf);
# define writeREAL(a)		Wr.PutText(yyf,Fmt.Real(a));
# define getREAL(a)		yyGet (a);
# define putREAL(a)		yyPut (a);
# define copyREAL(a, b)		a := b
# define equalREAL(a, b)	a = b
LONGREAL
# define beginLONGREAL(a)	
# define closeLONGREAL(a)	
# define readLONGREAL(a)	a := Lex.LongReal(yyf);
# define writeLONGREAL(a)	Wr.PutText(yyf,Fmt.LongReal(a));
# define getLONGREAL(a)		yyGet (a);
# define putLONGREAL(a)		yyPut (a);
# define copyLONGREAL(a, b)	a := b
# define equalLONGREAL(a, b)	a = b
EXTENDED
# define beginEXTENDED(a)		
# define closeEXTENDED(a)		
# define readEXTENDED(a)	a := Lex.Extended(yyf);
# define writeEXTENDED(a)	Wr.PutText(yyf,Fmt.Extended(a));
# define getEXTENDED(a)		yyGet (a);
# define putEXTENDED(a)		yyPut (a);
# define copyEXTENDED(a, b)     a := b
# define equalEXTENDED(a, b)	a = b
BOOLEAN
# define beginBOOLEAN(a)	
# define closeBOOLEAN(a)	
# define readBOOLEAN(a)		a := Lex.Bool (yyf);
# define writeBOOLEAN(a)	Wr.PutText(yyf,Fmt.Bool(a));
# define getBOOLEAN(a)		yyGet (a);
# define putBOOLEAN(a)		yyPut (a);
# define copyBOOLEAN(a, b)	a := b
# define equalBOOLEAN(a, b)	a = b
CHAR
# define beginCHAR(a)		
# define closeCHAR(a)		
# define readCHAR(a)		a := Rd.GetChar(yyf);
# define writeCHAR(a)		Wr.Putchar (yyf, a);
# define getCHAR(a)		yyGet (a);
# define putCHAR(a)		yyPut (a);
# define copyCHAR(a, b)		a := b
# define equalCHAR(a, b)	a = b
ADDRESS
# define beginADDRESS(a)	
# define closeADDRESS(a)	
# define readADDRESS(a)		yyReadHex ( LOOPHOLE ( a , ARRAY [ 0..3 ] OF CHAR));
# define writeADDRESS(a)	yyWriteHex (a , LOOPHOLE( ARRAY [ 0..3 ] 
# define getADDRESS(a)		yyGet (a);
# define putADDRESS(a)		yyPut (a);
# define copyADDRESS(a, b)      a := b
# define equalADDRESS(a, b)	a = b
