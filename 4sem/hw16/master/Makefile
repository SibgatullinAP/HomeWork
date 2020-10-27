all: clean main

CFLASGS = -c -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
DBGFLAGS = #-g -pg -fsanitize=address
OPTFLASGS = -03 -DZACHET -mfpmath=sse#-m64 -Ofast -flto -march=native -funroll-loops

main: main.o command.o dataBase.o list.o RedBlackTreeName.o RedBlackTree.o AVLTree.o hash.o 
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