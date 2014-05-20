all: gilbert

gilbert:
	g++ -o gilbert gilbert.cpp

clean:
	rm -rf *o gilbert

install:
	cp gilbert /usr/local/bin

uninstall:
	rm /usr/local/bin/gilbert