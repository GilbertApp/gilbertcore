all: gilbert

gilbert:
	g++ -c gilbertanalysis.cpp
	g++ -c gilbert.cpp
	g++ -lsndfile -lfftw3 -o gilbert gilbertanalysis.o gilbert.o

clean:
	rm -rf *o gilbert

install:
	make
	cp gilbert /usr/local/bin

uninstall:
	rm /usr/local/bin/gilbert

documentation:
	doxygen Doxyfile
