all: clean main

CFLASGS = -c #-Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g -pg

main: main.o RedBlackTreeName.o
	g++ $^ -o 1.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
RedBlackTreeName.o: RedBlackTreeName.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
