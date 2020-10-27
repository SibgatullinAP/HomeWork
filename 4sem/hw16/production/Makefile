all: clean main

CFLASGS = -c -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
GDBFLAGS = #-g -pg 
OPTFLAGS = -O3 -mfpmath=sse -Ofast -flto -march=native -funroll-loops -DZACHET

main: main.o command.o dataBase.o list.o RedBlackTree.o RedBlackTreeName.o AVLTree.o hash.o 
	g++ $^ $(GDBFLAGS) $(OPTFLAGS) -o a.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)
dataBase.o: dataBase.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)
RedBlackTree.o: RedBlackTree.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)
RedBlackTreeName.o: RedBlackTreeName.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)
hash.o: hash.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)
list.o: list.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)		
AVLTree.o: AVLTree.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)
command.o: command.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)

clean:
	rm -f *.o *.out