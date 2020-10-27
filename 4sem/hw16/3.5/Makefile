all: clean main

CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O3 -g #-fsanitize=address -pg

main: main.o command.o dataBase.o list.o RedBlackTree.o RedBlackTreeName.o AVLTree.o hash.o 
	g++ $^ $(GDBFLAGS) -o a.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
dataBase.o: dataBase.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
RedBlackTree.o: RedBlackTree.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
RedBlackTreeName.o: RedBlackTreeName.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
hash.o: hash.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
list.o: list.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)		
AVLTree.o: AVLTree.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
command.o: command.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
