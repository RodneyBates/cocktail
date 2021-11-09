all:
	echo p Main | mc -O -noindex -norange -d ../../reuse/src
	rm -f Main Main.[dimor]

m2c:
	co RCS/*
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

clean:
	rm -f *.[dimor]
