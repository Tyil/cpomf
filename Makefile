INSTALL_PATH=/home/$$USER/.local

DEBUGFLAGS=-ggdb -Wall
CFLAGS=-std=c99
LDFLAGS=-lcurl -ljansson
DIP=-DINSTALL_PATH=\"$(INSTALL_PATH)\"

clean:
	rm bin/cpomf
	rm -rf share

debug:
	mkdir -p bin
	$(CC) src/*.c -o bin/cpomf $(CFLAGS) $(DEBUGFLAGS) $(LDFLAGS)
	mkdir -p share/cpomf
	cp {CREDITS,LICENSE,README.md} share/cpomf/.

install:
	mkdir -p $(INSTALL_PATH)/bin
	$(CC) src/*.c -o $(INSTALL_PATH)/bin/cpomf $(DIP) $(CFLAGS) $(LDFLAGS)
	mkdir -p $(INSTALL_PATH)/share/cpomf
	cp {CREDITS,LICENSE,README.md} $(INSTALL_PATH)/share/cpomf/.

uninstall:
	rm $(INSTALL_PATH)/bin/cpomf
	rm -rf $(INSTALL_PATH)/share/cpomf
