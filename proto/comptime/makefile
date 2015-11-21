CC=gcc
CFLAGS=-g -Wall -std=c++11
LIBS=-lm

all: main.c
	$(CC) $(CFLAGS) $(LIBS) main.c -o main
gdb: main
	gdb -x "gdb.conf"
gdbt: main
	gdb -tui -x "gdb.conf"
run: main
	./main >> broke.out
	gnuplot -p plot
	rm broke.out -f

clean:
	rm main
