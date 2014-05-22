all: gilbert

gilbert:
	g++ -lsndfile -lfftw3f -o gilbert gilbert.cpp

clean:
	rm -rf *o gilbert

install:
	make
	cp gilbert /usr/local/bin

uninstall:
	rm /usr/local/bin/gilbert
