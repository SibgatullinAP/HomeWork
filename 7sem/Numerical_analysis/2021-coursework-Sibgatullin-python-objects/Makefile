SRC_CW = coursework
SRC_PRES = presentation

all:
	pdflatex $(SRC_CW).tex; pdflatex $(SRC_CW).tex; pdflatex $(SRC_PRES).tex; pdflatex $(SRC_PRES).tex;
clean:
	rm -f $(SRC_CW).log $(SRC_CW).aux $(SRC_CW).out $(SRC_CW).toc 
	rm -f $(SRC_PRES).log $(SRC_PRES).aux $(SRC_PRES).out $(SRC_PRES).toc $(SRC_PRES).snm $(SRC_PRES).nav 

