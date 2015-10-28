CC=g++
CFLAGS=-g -Wall
LIBS=-pthread

all: main.cpp
	$(CC) $(CFLAGS) $(LIBS) main.cpp -o main
gdb: main
	gdb -x "gdb.conf"
gdbt: main
	gdb -tui -x "gdb.conf"

clean:
	rm main
