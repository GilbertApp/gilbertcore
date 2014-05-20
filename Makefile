all: gilbert

gilbert:
	g++ -lfftw3 -o gilbert gilbert.cpp

clean:
	rm -rf *o gilbert

install:
	make
	cp gilbert /usr/local/bin

uninstall:
	rm /usr/local/bin/gilbert