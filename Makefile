all: gilbert

gilbert:
	g++ -c soundfeatureset.cpp
	g++ -c gilbertanalysis.cpp
	g++ -c gilbertdb.cpp
	g++ -c gilbertclassifier.cpp
	g++ -c gilbert.cpp
	g++ -c gilbertsignalutil.cpp
	g++ -lsndfile -lfftw3 -o gilbert gilbertanalysis.o gilbert.o gilbertdb.o soundfeatureset.o gilbertclassifier.o gilbertsignalutil.o

clean:
	rm -rf *.o gilbert

install:
	make
	cp gilbert /usr/local/bin

uninstall:
	rm /usr/local/bin/gilbert

docs:
	doxygen Doxyfile

docsclean:
	rm -R docs
