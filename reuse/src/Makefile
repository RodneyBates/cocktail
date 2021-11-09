# Makefile for reuse/src
# RMB 93/10/19 and earlier. 
#     Modified for installation on local system
#     Modified to support WRL compilation.
TARGET	= SUN
MC	= WRL
OPT	= -O
UNIX	= UNIX
CFLAGS	= $(OPT) -D$(UNIX)
CC	= cc

# targets

all:	$(MC)

MC:	System.o
	rm -f Main
	echo p Main | mc -noindex -norange
#       No library reference is here at all.

cleanm2c:
	cd ../m2c; rm -f Checks.[hc] DynArrDrv.c DynArray.[hc] General.[hc] \
	   Heap.[hc] IO.[hc] IODrv.c Idents.[hc] Layout.[hc] Lists.[hc] \
	   Main.c Memory.[hc] MemoryDrv.c RelDrv.c Relations.[hc] Sets.[hc] \
	   SetsC.[hc] SetsDrv.c StdIO.[hc] StringMem.[hc] Strings.[hc] \
	   SysIODrv.c System.[hc] Texts.[hc] Times.[hc] Positions.[hc] \
	   Errors.[hc] Source.[hc] Sort.[hc]
	rm -f ../m2c/System.c ../m2c/Arguments.c 

forcem2c: cleanm2c m2c

symlinks:
	for file in `ls *.md`; do ln -s $$file `basename $$file .md`.def; done
	for file in `ls *.mi`; do ln -s $$file `basename $$file .mi`.mod; done

WRL:	System.o
	rm -f Main
	make Main -f MakefileWRL

M2C:	System.o symlinks
	rm -f Main
	make Main -f MakefileM2C

m2c:    
#	co RCS/*
	ln -f *.m[id] ../m2c
	cp -p System.c ../m2c
	cp -p Arguments.c ../m2c
	cd ../m2c; make sources
# RMB?? Makefiles in other directories pass the equivalent of
#       MFLAGS=-d../../reuse/src here
#       This directory has these flags supplied inside .../m2c/Makefile.
#       This seems better, because make issued inside ../m2c can also
#       invoke mtc,  which  in this method will get the same flags.
	cd ../m2c; rm -f *.m[id]

test:	System.o
	echo p DynArrDrv| mc
	echo p IODrv	| mc
	echo p MemoryDrv| mc
	echo p RelDrv	| mc
	echo p SetsDrv	| mc
	echo p SysIODrv	| mc

lint:
	lint -u *.c

CLEAN:	clean
	rm -f *.[dimor] *.sym *.def *.mod

clean:
	rm -f *Drv.[dimor] *Drv.sym *Drv Main.[dimor] Main t *.bak

.c.o:
	$(CC) $(CFLAGS) -c $*.c;





