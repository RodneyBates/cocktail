deflinks :
	for file in $(MODULADEFS); do ln -sf $$file `basename $$file .md`.def; done
implinks :
	for file in $(MODULAIMPS); do ln -sf $$file `basename $$file .mi`.mod; done
