all: clean main

CFLASGS = -c #-Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g -pg

main: main.o tree.o 
	g++ $^ -o 1.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
tree.o: tree.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
