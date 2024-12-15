CC=gcc
CFLAGS=-O3 -Wall -Wextra
DEBUGFLAGS=-O0 -g
FILES=src/main.c src/*.h

all: mod2funcbeat

mod2funcbeat: $(FILES)
	$(CC) src/main.c -o mod2funcbeat $(CFLAGS)

debug: $(FILES)
	$(CC) src/main.c -o mod2funcbeat $(DEBUGFLAGS)
