all: clean main

CFLASGS = -c #-Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g -pg

main: main.o AVLTree.o hash.o
	g++ $^ -o 1.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
AVLTree.o: AVLTree.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
hash.o: hash.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
