# Compiler
CC=g++
# Include Directory
INCLUDE=-Iinclude
# Librarys
LIBS=
# Source Directory
SRC_DIR=src
# Debugger
DB=gdb
DBOPT=
# Bin Dir
BIN_DIR=bin
# Compiler Flags
CPPFLAGS=-std=c++11 -g -Wall $(INCLUDE) -O3

# Compile Objects
OBJS = main.o body.o scenario.o sim_obj.o simEntry.o 

all: out

out: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -o $@

%.cpp.o:
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm *.o
