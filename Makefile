INSTALL_PATH=/usr/local

DEBUGFLAGS=-ggdb -Wall
CFLAGS=-std=c11
LDFLAGS=-lcurl -ljansson
DIP=-DINSTALL_PATH=\"$(INSTALL_PATH)\" -D_POSIX_SOURCE

build:
	mkdir -p bin
	$(CC) src/*.c -o bin/cpomf $(DIP) $(CFLAGS) $(LDFLAGS)

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
	mkdir -p $(INSTALL_PATH)/share/cpomf
	cp bin/cpomf $(INSTALL_PATH)/bin/cpomf
	cp CREDITS $(INSTALL_PATH)/share/cpomf/.
	cp LICENSE $(INSTALL_PATH)/share/cpomf/.
	cp README.md $(INSTALL_PATH)/share/cpomf/.

uninstall:
	rm $(INSTALL_PATH)/bin/cpomf
	rm -rf $(INSTALL_PATH)/share/cpomf
