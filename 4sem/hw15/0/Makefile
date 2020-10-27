all: clean main

CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g -pg

main: main.o command.o 
	g++ $^ $(GDBFLAGS) -o 1.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
command.o: command.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
