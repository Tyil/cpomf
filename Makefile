INSTALL_PATH=/home/$$USER/.local

CFLAGS=-std=c99 -ggdb -Wall
LDFLAGS=-lcurl -ljansson
DFLAGS=-DINSTALL_PATH="$(INSTALL_PATH)"

clean:
	rm bin/cpomf
	rm -rf share

debug:
	mkdir -p bin
	$(CC) src/*.c -o bin/cpomf $(CFLAGS) $(LDFLAGS)
	mkdir -p share/cpomf
	cp {CREDITS,LICENSE,README.md} share/cpomf/.

install:
	mkdir -p $(INSTALL_PATH)/bin
	$(CC) src/*.c -o $(INSTALL_PATH)/bin/cpomf $(CFLAGS) $(DFLAGS) $(LDFLAGS)
	mkdir -p $(INSTALL_PATH)/share/cpomf
	cp {CREDITS,LICENSE,README.md} $(INSTALL_PATH)/share/cpomf/.

uninstall:
	rm $(INSTALL_PATH)/bin/cpomf
	rm -rf $(INSTALL_PATH)/share/cpomf
