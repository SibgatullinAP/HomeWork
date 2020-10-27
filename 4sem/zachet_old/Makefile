CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g

main: main.o list.o string.o addons.o 
	g++ $^ -o 1.out
	
main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
list.o: list.cpp list.h listNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
string.o: string.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
addons.o: addons.cpp addons.h 
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
