CFLAGS=-std=c99 -ggdb -Wall
LDFLAGS=-lcurl -ljansson

all:
	mkdir -p bin
	$(CC) src/*.c -o bin/pomf $(CFLAGS) $(LDFLAGS)

clean:
	rm bin/pomf
