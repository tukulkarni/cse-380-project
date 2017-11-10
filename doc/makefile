include ../makefile.in

IMG := $(wildcard plots/%.eps)
project.pdf : $(IMG) project.tex
	@latex project.tex
	@latex project.tex
	@dvips project.dvi
	@ps2pdf project.ps

project.tex : 

.PHONY : clean

clean : 
	rm -f *.dvi *.ps *.pdf *.log *.out 
