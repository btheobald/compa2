CC=g++
CFLAGS=-g -Wall -std=c++11
LIBS=-pthread

all: main.cpp
	$(CC) $(CFLAGS) $(LIBS) main.cpp -o main
gdb: main
	gdb -x "gdb.conf"
gdbt: main
	gdb -tui -x "gdb.conf"
run: main
	./main | xclip -i -selection clipboard


clean:
	rm main
