CSRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
SOURCES = $(CSRC:.c=.o)
BINARY=./bin/neshla

CFLAGS=-g -Isrc/ -m32 -O2
LDFLAGS=-m32

all: $(SOURCES) link

clean:
	find src/ -type f -name '*.o' -delete
	test -f $(BINARY) && rm $(BINARY)

link:
	$(CC) $(LDFLAGS) -o $(BINARY) $(SOURCES)
